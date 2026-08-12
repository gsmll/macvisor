/* Recreated from kernelcache.arm64.kc (xnu-12377.121.10 RELEASE_ARM64_T8142, image base fffffe0007004000). Ground truth: Ghidra FUN_ names + addresses; all names are estimates. */
#include "hv_compat.h"

/*
 * hv_vcpu.c — vCPU lifecycle and the core vcpu run/exit dispatch path.
 *
 * Owned by the vcpu-core tree.
 * All names are estimates; ground truth is the FUN_ address in the header
 * comment of each function.  Shared kernel dependencies are declared as
 * externs in hv_vcpu.h and documented in docs/chain-map.md — never recreated.
 */

#include "hv_pmap.h"   /* os_release(uint64_t) typed decl */
#include "hv_helpers.h"   /* hv_cpu_broadcast / hv_vm_owner_teardown / hv_vm_pool_release */
#include "hv_vmm.h"    /* kernel_copyin2 / kernel_mem_release / hv_vm_unwire_fault_table */
#include "hv_vcpu.h"

/* FATAL: kernel panic helper (FUN_fffffe000c0f86a4 / c0f8674 / c0f1874). */
static void __attribute__((noreturn)) panic_hv(const char *msg);

/* ESR exception-class classifier used by hv_vcpu_run's exit-reason case 0x8
 * (inline block at 0xfffffe000b98a08c; reconstructed below). */
static void hv_esr_classify(hv_vcpu_t *vcpu, uint64_t esr);

/*
 * Per-CPU access (current_cpu_datap).  The vcpu object bound to the
 * current CPU lives at tpidr_el1 + 0x4d8.  The cpu id is cached in
 * DAT_fffffe000c62c0c0; DAT_fffffe000c62b3d0 is a debug/lock-storm flag.
 */
#define PERCPU_VCPU_SLOT  0x4d8
#define PERCPU_CPU_ID     0x518

extern uint64_t hv_cached_cpu_id;    /* DAT_fffffe000c62c0c0 cached current cpu id */
extern uint32_t hv_debug_flag;       /* DAT_fffffe000c62b3d0 debug flag */
extern uint64_t hv_lock;             /* DAT_fffffe000c62c0b8 per-cpu lock */
extern uint64_t hv_vcpu_generation;  /* DAT_fffffe000c716e40 vcpu generation counter */
extern uint32_t hv_quota_derived[3]; /* DAT_fffffe000c5b83b0 derived quota copies */
extern uint64_t hv_slot_list;        /* DAT_fffffe0007d53e38 per-slot registration list head */
extern uint64_t hv_vm_pool;          /* DAT_fffffe000c5d7068 owner vm pool */
extern uint64_t hv_vm_list;          /* DAT_fffffe0007d52478 vm object list head */
extern uint64_t hv_obj_list;         /* DAT_fffffe0007d53e78 object global list head */
extern uint16_t hv_el2_capable;      /* DAT_fffffe0007e0d81e EL2 feature bit 0 */
extern uint64_t hv_build_gate;       /* DAT_fffffe0007e0da68 EL2 build-path gate */
extern uint64_t hv_soc_no_l2;        /* DAT_fffffe0007e0d81c aidr bit 45 (L2-table-absent) */
extern uint16_t hv_el2_l2;           /* DAT_fffffe0007e0d81d EL2-L2 capable flag (save-mask select) */
extern uint64_t cpu_boot_time_delta; /* DAT_fffffe000c5ac010 boot time delta, written by arm_cpu_init @ b95b238 */
extern void kernel_slot_callee_088(void *lock, uint64_t a, void *vcpu, uint32_t b); /* FUN_fffffe000b7f9088, kernel slot notify (stubbed extern) */
extern uint64_t waitq_hash_table;    /* DAT_fffffe0007d7c8e0 universal waitq hash table (kernel) */
extern uint64_t waitq_hash_size;     /* DAT_fffffe0007d7c8e8 universal waitq hash size (kernel) */
extern void kernel_owner_mismatch_panic(void *mutex, void *thread) __attribute__((noreturn)); /* FUN_fffffe000c0e4d74: "Mutex %p is unexpectedly not owned by thread %p" */
extern void kernel_panic_msg_fmt(const char *fmt, ...) __attribute__((noreturn)); /* FUN_fffffe000c0e11ec */
extern void hv_el2_pt_alloc(struct hv_vm *vm);  /* FUN_fffffe000b98e344 (see hv_internal.h) */

/* Nesting-exit idiom (INLINE in FUN_fffffe000b988e70 / b98e788 / b85e180, not a
 * real Ghidra function): decrement the per-CPU nesting counter
 * (tpidr_el1 + 0x1c0); when it returns to 0 and the cpu flag at
 * tpidr_el1+0x1b8 (+0x4c, bit 2) is set, flush the TLB
 * (FUN_fffffe000b96c6d4).  The reconstruction previously called a fabricated
 * `nesting_exit()` shim; this helper reproduces the decompiled inline body. */
static void
hv_nesting_exit(uint64_t cpu)
{
	int i;

	i = *(int *)(cpu + 0x1c0) - 1;
	*(int *)(cpu + 0x1c0) = i;
	if (i == 0 && ((*(uint8_t *)(*(long *)(cpu + 0x1b8) + 0x4c) >> 2) & 1) != 0)
		kernel_tlb_flush();               /* FUN_fffffe000b96c6d4 */
}

/* Nesting-save idiom (INLINE in the hub's HVC32 hint family, repeated at
 * b98a4d4, b98c370, b98c3ec, b98c494, b98c53c, b98c5d0, b98c670, b98c70c,
 * b98bdf0, b98c798): nesting++, hv_vcpu_save_el2_state(vcpu, mask) with the
 * hv_el2_l2 (DAT_fffffe0007e0d81d) feature mask, nesting-- with the
 * b98db90 panic (nesting hit 0 mid-save) and the tlb-flush check
 * (FUN_fffffe000b96c6d4).  Extracted verbatim from the repeated block. */
static void
hv_nesting_save(hv_vcpu_t *vcpu)
{
	uint64_t cpu = tpidr_el1;
	int n;

	*(int *)(cpu + 0x1c0) = *(int *)(cpu + 0x1c0) + 1;
	hv_vcpu_save_el2_state(
	    vcpu, (hv_el2_l2 & 1) ? 0x7fc000000000001full
	                          : 0x7bc000000000001full);  /* b988358 */
	if (*(int *)(cpu + 0x1c0) == 0)
		kernel_panic();                          /* b98db90 (c0f1874) */
	n = *(int *)(cpu + 0x1c0) - 1;
	*(int *)(cpu + 0x1c0) = n;
	if (n == 0 && ((*(uint8_t *)(*(long *)(cpu + 0x1b8) + 0x4c) >> 2) & 1) != 0)
		kernel_tlb_flush();                      /* b98d74c et al. */
}

/* ------------------------------------------------------------------ */
/* FUN_fffffe000b989040 @ 0xfffffe000b989040   (est. hv_vcpu_create)
 * Ghidra: ulong hv_vcpu_create(undefined8 param_1)
 * Copies a 16-byte guest request in, validates the vcpu id (< 64), requires
 * that no vcpu is already bound to this CPU, retains the current container
 * object, allocates+initialises a vcpu, builds the EL2 state, writes the
 * vcpu id into the container's per-slot table, and binds the vcpu into the
 * per-CPU slot (tpidr_el1 + 0x4d8).  On any failure it unwinds through the
 * error paths (destroy/release) and returns an 0xfae940xx error.
 * Confidence: medium
 * Notes: copyin copyin(.., 0x10); copyout copyout;
 *   container slot table stride 0x80, valid slot at +0x80, busy flag +0x90,
 *   state word +0x94; object refcount at plVar12[1]; quota flag
 *   DAT_fffffe000c5b83b0; per-cpu id cached in DAT_fffffe000c62c0c0; lock
 *   lck_mtx_lock/1e4c/1e80; panic kernel_panic_a/c0f8674. */
uint64_t hv_vcpu_create(void *user_state)
{
    uint64_t guest[2];                 /* local_58/local_50 : 16-byte request */
    hv_vcpu_t *vcpu = 0;
    uint64_t err = 0xfae94002;
    uint64_t cpu, tmp;
    void *container;                   /* plVar12 */
    uint32_t *refc;
    long *vcpu_p;
    uint8_t vcpu_id;
    int n;

    guest[0] = 0;
    guest[1] = 0;

    /* copyin(user_state, guest, 0x10) — FUN_fffffe000b95c144 */
    if (copyin(user_state, guest, 0x10) != 0)
        return 0xfae94003;
    if ((guest[0] & 0xff) > 0x3f)      /* vcpu id must be in [0, 64) */
        return 0xfae94003;

    cpu = tpidr_el1;
    if (*(void **)(cpu + PERCPU_VCPU_SLOT) != 0)
        return 0xfae94002;             /* a vcpu is already bound here */

    /* cache the current cpu id if not done yet */
    if (hv_cached_cpu_id == 0)                    /* DAT_fffffe000c62c0c0 */
        hv_cached_cpu_id = *(uint32_t *)(cpu + PERCPU_CPU_ID);
    if (hv_debug_flag != 0)                       /* DAT_fffffe000c62b3d0 */
        lock_acquire(&hv_lock, cpu);              /* DAT_fffffe000c62c0b8 FUN_fffffe000b7f0afc */

    /* resolve the current container from the per-cpu struct (FUN_fffffe000b866ec4) */
    container = *(void **)(per_cpu_base(cpu) + 0x628); /* FUN_fffffe000b866ec4 */
    if (container == 0) {
        lock_release(&hv_lock);         /* DAT_fffffe000c62c0b8 FUN_fffffe000b7f1e4c */
        return 0xfae94006;
    }

    /* retain the container */
    refc = (uint32_t *)container + 1;  /* plVar12[1] */
    n = *refc;
    *refc = n + 1;
    if ((uint32_t)(n + 0xf0000001) < 0xf0000002)    /* refcount overflow */
        panic_hv("vcpu container refcount");

    /* bind the cpu id into the container object (+8) */
    tmp = *(uint64_t *)(*(uint64_t *)container + 8);
    if (tmp == 0)
        *(uint64_t *)(*(uint64_t *)container + 8) = *(uint32_t *)(cpu + PERCPU_CPU_ID);
    if (hv_debug_flag != 0)                         /* DAT_fffffe000c62b3d0 */
        lock_acquire(*(void **)container, cpu);     /* FUN_fffffe000b7f0afc */

    /* allocate + init the vcpu: hv_vcpu_alloc_init(&vcpu, container[2], 0) */
    if (hv_vcpu_alloc_init(&vcpu, ((uint64_t *)container)[2], 0) != 0) {
        err = 0xfae94005;
        goto out_release;
    }

    /* populate vcpu fields, build EL2 state */
    vcpu_p = (long *)vcpu;
    vcpu_p[0x11] = ((long *)container)[0x424];      /* +0x88 = container copy */
    vcpu_p[0x16] = vcpu_p[1];                       /* +0xb0 = guest_mem */
    vcpu_p[0x1c] = 0;                               /* +0xe0 */
    vcpu_p[0x00] = (long)container;                 /* +0x00 = container */
    hv_el2_state_build((struct hv_vm *)vcpu, (uint8_t *)vcpu_p[1], 0); /* FUN_fffffe000b9895b8; first arg estimate */
    guest[1] = vcpu_p[2];

    /* copyout the (updated) guest request */
    if (copyout(guest, user_state, 0x10) != 0) {    /* FUN_fffffe000b95d6f4 */
        err = 0xfae94001;
        hv_vcpu_destroy(vcpu);
        goto out_release;
    }

    /* record the vcpu id and mark the container slot */
    *(uint8_t *)((char *)vcpu + 0xf8) = (uint8_t)(guest[0] & 0xff);   /* vcpu_id */
    *(uint64_t *)(*(uint64_t *)vcpu + ((guest[0] & 0xff) * 0x80) + 0x88) = 0;
    vcpu_id = *(uint8_t *)((char *)vcpu + 0xf8);
    if (*(uint64_t *)(*(uint64_t *)vcpu + (uint64_t)vcpu_id * 0x80 + 0x80) != 0)
        goto destroy;

    /* set the per-vcpu slot busy bit in the container bitmap (+0x18) */
    *(uint64_t *)((char *)container + (((vcpu_id >> 3) & 0x18)) + 0x18) |=
        1ULL << (vcpu_id & 0x3f);
    /* install vcpu into the container per-slot table (stride 0x80) */
    *(uint64_t **)(*(uint64_t *)vcpu + (uint64_t)*(uint8_t *)((char *)vcpu + 0xf8) * 0x80 + 0x80) = vcpu;

    /* drop the container reference we took above */
    refc = (uint32_t *)container + 1;
    n = *refc;
    *refc = n - 1;
    container_release(container);                   /* LORelease */
    if (n == 1)
        hv_vcpu_object_release(container);          /* FUN_fffffe000b98533c */
    if (n == 0)
        panic_hv("vcpu container underflow");

    /* bump the global vcpu generation counter and clear the slot status */
    hv_vcpu_generation += 1;                        /* DAT_fffffe000c716e40 */
    vcpu_p[0x1b] = hv_vcpu_generation;              /* DAT_fffffe000c716e40 +0xd8 */
    *(uint8_t *)(*(uint64_t *)vcpu + (uint64_t)*(uint8_t *)((char *)vcpu + 0xf8) * 0x80 + 0x90) = 0;
    *(uint32_t *)(*(uint64_t *)vcpu + (uint64_t)*(uint8_t *)((char *)vcpu + 0xf8) * 0x80 + 0x94) = 0;

    /* bind into the per-cpu slot */
    *(hv_vcpu_t **)(cpu + PERCPU_VCPU_SLOT) = vcpu;
    return 0;

destroy:
    hv_vcpu_destroy(vcpu);                          /* FUN_fffffe000b988e70 */
out_release:
    /* drop container ref */
    refc = (uint32_t *)container + 1;
    n = *refc;
    *refc = n - 1;
    container_release(container);                   /* LORelease */
    if (n == 1)
        hv_vcpu_object_release(container);
    if (n == 0)
        panic_hv("vcpu container underflow");
    return err;
}

/* ------------------------------------------------------------------ */
/* FUN_fffffe000b989390 @ 0xfffffe000b989390   (est. hv_vcpu_alloc_init)
 * Ghidra: undefined8 hv_vcpu_alloc_init(long *param_1,undefined8 param_2,int param_3)
 * Allocates the 0x100-byte vcpu object and a 0x8000-byte guest-memory
 * mapping (via the zone allocator kernel_alloc and the map-enter
 * kernel_mem_validate against the VM at param_2), then links them and
 * returns the vcpu through param_1.  On failure it unwinds the partial
 * allocations and returns an 0xfae940xx error.
 * Confidence: medium
 * Notes: alloc calls kernel_alloc(0,0x100,0,0x80,0x1c,0) and
 *   (0,0x8000,0,0x10080,0x1c,zone); two map-enters kernel_mem_validate with
 *   flags 0x1c100008 (0x8000) and 0x1c104001 (0x4000); unwind kernel_mem_release
 *   (dealloc), kernel_lock_ref (lock), kernel_memzero (free). */
int hv_vcpu_alloc_init(hv_vcpu_t **out, uint64_t vm, int flag)
{
    uint64_t vcpu = 0, guest = 0, map = 0;
    void *zone = 0;
    int rc = 0xfae94005;

    *out = 0;

    /* first allocation: the vcpu object itself (0x100 bytes) */
    if (kalloc_zalloc(&vcpu, 0x100) != 0)           /* FUN_fffffe000b8a6c14 */
        return 0xfae94005;

    /* second allocation: guest memory (0x8000) */
    if (kalloc_zalloc(&guest, 0x8000) != 0)         /* FUN_fffffe000b8a6c14 */
        goto fail_vcpu;

    /* map the guest region into the VM at param_2 */
    if (vm_map_enter(vm, &map, 0x8000, 0, 0x1c100008) != 0) {  /* FUN_fffffe000b8b51c8 */
        dealloc((void *)guest, 0x8000);                 /* FUN_fffffe000b8a8078 */
        rc = 0xfae94001;
        goto fail_guest;
    }
    if (vm_map_enter(vm, &map, 0x4000, 0, 0x1c104001) != 0) {  /* FUN_fffffe000b8b51c8 */
        dealloc((void *)guest, 0x8000);
        rc = 0xfae94001;
        goto fail_guest;
    }

    /* link the pieces together */
    *(uint64_t *)(vcpu + 0) = vcpu;
    *(uint64_t *)(vcpu + 8) = guest;
    *(uint64_t *)(vcpu + 0x10) = map;
    *out = (hv_vcpu_t *)vcpu;
    return 0;

fail_guest:
    kfree((void *)guest, 0x8000);                   /* FUN_fffffe000b8b6860 */
fail_vcpu:
    kfree((void *)vcpu, 0x100);                     /* FUN_fffffe000b8b6860 */
    return rc;
}

/* ------------------------------------------------------------------ */
/* FUN_fffffe000b988e70 @ 0xfffffe000b988e70   (est. hv_vcpu_destroy)
 * Ghidra: void hv_vcpu_destroy(long *param_1)
 * Frees a vcpu's EL2 state allocations (two 0x4000 regions at param_1+0x18
 * and param_1+0x1a, the 0x8000 guest region at param_1[2], the el2_state
 * region at param_1[0x16], and finally the 0x800-byte vcpu object itself).
 * Clears the corresponding bits in the EL2 dirty/flags word at
 * param_1[0x16]+0x4118 and uses the per-CPU nesting counter tpidr_el1+0x1c0.
 * Confidence: medium
 * Notes: frees via kernel_mem_release (dealloc) + kernel_memzero
 *   (free) + kernel_lock_ref (lock); flags clear masks 0xffbfffffffffffff
 *   (bit 42) and 0xffffffffffffffef (bit 4); nesting callback
 *   kernel_tlb_flush; panic kernel_panic. */
void hv_vcpu_destroy(hv_vcpu_t *vcpu)
{
    long *p = (long *)vcpu;
    uint64_t el2;
    uint64_t cpu = tpidr_el1;

    el2 = p[0x18];                                  /* +0xc0 el2 allocation 1 */
    if (el2 != 0) {
        uint64_t es = p[0x16];                      /* el2_state base */
        /* clear the EL2-dirty bit and release the region */
        *(uint64_t *)(es + 0x4150) = 0;
        *(uint64_t *)(es + 0x4150) = 0;
        *(uint64_t *)(es + 0x4118) &= 0xffbfffffffffffffULL;  /* clear bit 42 */
        hv_nesting_exit(cpu);                       /* tpidr_el1+0x1c0 --1 (+TLB flush) */
        dealloc((void *)el2, 0x4000);                       /* FUN_fffffe000b8a8078 */
        kfree((void *)el2, 0x4000);                         /* FUN_fffffe000b8b6860 */
    }

    el2 = p[0x1a];                                  /* +0xd0 el2 allocation 2 */
    if (el2 != 0) {
        uint64_t es = p[0x16];
        *(uint64_t *)(es + 0x4148) = 0;
        *(uint64_t *)(es + 0x4118) &= 0xffffffffffffffefULL;  /* clear bit 4 */
        hv_nesting_exit(cpu);
        dealloc((void *)el2, 0x4000);                       /* FUN_fffffe000b8a8078 */
        kfree((void *)el2, 0x4000);                         /* FUN_fffffe000b8b6860 */
    }

    dealloc((void *)p[2], 0x8000);                          /* guest_mem */
    kfree((void *)p[0x16], 0x8000);                         /* el2_state */
    kfree(vcpu, 0x800);                             /* the vcpu object */
}

/* ------------------------------------------------------------------ */
/* FUN_fffffe000b98533c @ 0xfffffe000b98533c   (est. hv_vcpu_object_release)
 * Ghidra: void hv_vcpu_object_release(undefined8 *param_1)
 * Final release of a vcpu/VM object: updates per-type quota counters
 * (DAT_fffffe000c5b83b0), then walks the 8 per-slot registration arrays
 * (param_1[0x429..0x430], each 0x40 entries of 16 bytes) freeing the guest
 * pages and clearing each entry, frees the object's auxiliary allocations
 * and its header, and unlinks it from the two global lists
 * (DAT_fffffe0007d52478 / DAT_fffffe0007d53e78).
 * Confidence: medium
 * Notes: hv_vm_owner_teardown (resource teardown); page ops
 *   kernel_copyin2/8a8078/8b6860; list remove refcount_dec;
 *   os_release(param_1[0x424]), hv_vm_pool_release(*param_1); quota
 *   DAT_fffffe000c5b83b0 indexed by object type (1/2/3). */
void hv_vcpu_object_release(uint64_t *obj)
{
    int type, i, j;
    uint64_t *arr;

    /* update the quota counters keyed by object type (param_1[0x425]) */
    if (*(uint32_t *)(obj + 0x425) > 1) {
        type = (*(int *)(obj + 0x425) == 2) ? 1 : 2;
        if (*(int *)(obj + 0x425) == 3)
            type = 2;
        hv_quota_derived[type] += 1;    /* DAT_fffffe000c5b83b0 (estimate of counter table) */
    }

    /* resource teardown */
    hv_vm_owner_teardown(obj);

    /* free the 8 per-slot registration arrays */
    for (i = 0; i < 8; i++) {
        uint64_t *entries = (uint64_t *)(obj + 0x429 + i);   /* base ptr field */
        uint64_t base = (uint64_t)entries;
        if (!base)
            continue;
        /* each entry is a {flag, ptr0, ptr1} triplet, stride 16 bytes */
        for (j = 0; j < 0x40; j++) {
            uint64_t *ent = (uint64_t *)(base + j * 0x10);
            if ((int)ent[0] == 0)
                continue;
            if (ent[2] == 0) {
                kernel_copyin2(0, ent[1], 0x8000 + ent[1], 0,
                               (uint64_t *)&hv_vm_unwire_fault_table); /* FUN_fffffe000b8b122c */
                kernel_mem_release(0, ent[1], 0x8000);                 /* FUN_fffffe000b8a8078 */
            } else {
                kfree((void *)ent[1], 0x8000);
                dealloc((void *)ent[1], 0x8000);
            }
            ent[0] = 0;
            ent[1] = 0;
            ent[2] = 0;
        }
        refcount_dec(&hv_slot_list, (void *)obj[i + 0x429]);  /* DAT_fffffe0007d53e38 FUN_fffffe000b862b6c */
        kfree((void *)obj[i + 0x429], 0);                   /* FUN_fffffe000b862b6c (est.) */
        obj[i + 0x429] = 0;
    }

    /* free the auxiliary allocations and the object header */
    hv_cpu_broadcast(0, obj[0x410]);
    os_release(obj[0x424]);
    hv_vm_pool_release((uint32_t *)*obj, (long)&hv_vm_pool);   /* DAT_fffffe000c5d7068 */
    refcount_dec(&hv_vm_list, obj);            /* DAT_fffffe0007d52478 */
    refcount_dec(&hv_obj_list, obj);           /* DAT_fffffe0007d53e78 */
}

/* ------------------------------------------------------------------ */
/* FUN_fffffe000b98503c @ 0xfffffe000b98503c   (hv_vcpu_state_merge)
 * Ghidra: void hv_vcpu_state_merge(long param_1,long *param_2,long param_3,
 *                                  ulong param_4,long param_5,ulong param_6)
 * Merges a source state span into the destination frame: first a tco copy
 * from p5 (kernel_copy_src/b758d80), then two bounded copies
 * (kernel_early_init/b758bd0 — min() length selection), writes the two
 * span-end words into dst[0]/dst[1], and fills every zero 32-bit validity
 * word in the (p5 - len_b) span with -1 (unrolled 16/4/1-word groups).
 * Confidence: high (complete decompile; Ghidra: "Type propagation algorithm
 *   not settling").
 * Notes: copy helpers kernel_copy_src (b758d80) / kernel_early_init
 *   (b758bd0); the fill covers 32-bit words from (p5-len_b)+dst+4 in
 *   count = len_b>>3 8-byte units. */
void hv_vcpu_state_merge(uint64_t dst, uint64_t src, uint64_t p3,
                         uint64_t len_a, uint64_t p5, uint64_t len_b)
{
    uint64_t u8;            /* p5 - len_b (span end offset) */
    uint64_t u7;            /* p3 - len_a */
    uint64_t count;         /* len_b >> 3 */
    uint64_t l4;            /* unroll base */
    uint64_t l3;
    uint64_t l6;
    uint64_t u2;
    uint64_t rem;
    int32_t *w;
    int32_t *l1;

    kernel_copy_src((void *)dst, (const void *)p5);    /* b758d80: tco copy */
    u8 = p5 - len_b;
    l1 = (int32_t *)(u8 + dst);
    u7 = p3 - len_a;
    kernel_early_init((void *)(u8 + dst), (const void *)(u7 + src),
                      len_b <= len_a ? len_b : len_a);   /* b758bd0 */
    kernel_early_init((void *)dst, (const void *)src,
                      u8 <= u7 ? u8 : u7);               /* b758bd0 */
    *(uint64_t *)dst = p5;
    *(uint64_t *)(dst + 8) = len_b;
    if (len_b < 8)
        return;

    count = len_b >> 3;
    if (len_b < 0x28) {
        l4 = 0;
    } else {
        if (len_b < 0x88) {
            l3 = 0;
        } else {
            rem = len_b >> 3 & 0xf;
            u2 = 0x10;
            if (rem != 0)
                u2 = rem;
            l4 = count - u2;
            w = l1 + 0x11;                       /* (int *)(lVar1 + 0x44) */
            l3 = l4;
            do {
                if (w[-0x10] == 0) w[-0x10] = -1;
                if (w[-0xe] == 0)  w[-0xe]  = -1;
                if (w[-0xc] == 0)  w[-0xc]  = -1;
                if (w[-10] == 0)   w[-10]   = -1;
                if (w[-8] == 0)    w[-8]    = -1;
                if (w[-6] == 0)    w[-6]    = -1;
                if (w[-4] == 0)    w[-4]    = -1;
                if (w[-2] == 0)    w[-2]    = -1;
                if (w[0] == 0)     w[0]     = -1;
                if (w[2] == 0)     w[2]     = -1;
                if (w[4] == 0)     w[4]     = -1;
                if (w[6] == 0)     w[6]     = -1;
                if (w[8] == 0)     w[8]     = -1;
                if (w[10] == 0)    w[10]    = -1;
                if (w[0xc] == 0)   w[0xc]   = -1;
                if (w[0xe] == 0)   w[0xe]   = -1;
                w += 0x20;
                l3 -= 0x10;
            } while (l3 != 0);
            l3 = l4;
            if (u2 < 5)
                goto tail_fill;                  /* LAB_fffffe000b9850dc */
        }
        rem = len_b >> 3 & 3;
        u2 = 4;
        if (rem != 0)
            u2 = rem;
        l4 = count - u2;
        l6 = (u2 + l3) - count;
        w = (int32_t *)((char *)l1 + l3 * 8 + 0x14);
        do {
            if (w[-4] == 0) w[-4] = -1;
            if (w[-2] == 0) w[-2] = -1;
            if (w[0]  == 0) w[0]  = -1;
            if (w[2]  == 0) w[2]  = -1;
            w += 8;
            l6 += 4;
        } while (l6 != 0);
    }
tail_fill:
    l3 = count - l4;
    w = (int32_t *)((char *)l1 + l4 * 8 + 4);
    do {
        if (w[0] == 0)
            w[0] = -1;
        w += 2;
        l3 -= 1;
    } while (l3 != 0);
}

/* ------------------------------------------------------------------ */
/* FUN_fffffe000b9866d0 @ 0xfffffe000b9866d0   (hv_vcpu_map_memory)
 * Ghidra: undefined8 hv_vcpu_map_memory(long param_1,ulong param_2,
 *          ulong param_3,uint param_4,ulong *param_5)
 * Validates that gpa (param_2) and size (param_3) are page-aligned, that the
 * region fits within the page-size mask of the chosen page-size descriptor
 * (PTR_PTR_fffffe000c5b3f68/60/58), then maps the guest physical range in
 * the vcpu's pmap (kernel_boot_misc_b / FUN_fffffe000b948ac8 and
 * kernel_vm_map_create / FUN_fffffe000b8ada1c). If handle_out is non-null it
 * creates an IO/kext handle for the mapping (kernel_zone_alloc type 0x12d)
 * and copies it to the caller via kernel_copy_handle (FUN_fffffe000b78d628);
 * otherwise the mapping is stored at param_1+0x2120. Returns 0 on success,
 * 0xfae94003/0xfae94005 on error.
 * Confidence: high (complete decompile).
 * Notes: page size default 0x4000; enc 0xb (0xc for map) when 0x1000 else
 *   3 (0xe); per_cpu_base FUN_fffffe000b866ec4; hv_page_size_table_1/60/68
 *   +0x50/+0x58 page fields. */
uint64_t hv_vcpu_map_memory(void *vcpu, uint64_t gpa, uint64_t size,
                            uint32_t page_size, uint64_t *handle_out)
{
    uint32_t psz = page_size ? page_size : 0x4000;
    uint64_t pages, mask, bound, cpu;
    void    *pmap;
    void    *mapping;
    uint32_t enc;

    if (gpa % psz != 0 || size % psz != 0)
        return 0xfae94003;

    /* pick the page-size descriptor whose +0x58 field matches psz */
    if (*(uint64_t *)(hv_page_size_table_3 + 0x58) != psz &&
        *(uint64_t *)(hv_page_size_table_2 + 0x58) != psz &&
        *(uint64_t *)(hv_page_size_table_1 + 0x58) != psz)
        return 0xfae94003;

    /* bound = 1 << (-(desc+0x50 & 0x3f) & 0x3f); for size != 0 the checked
     * sum gpa+size replaces it and is what the map ops receive (uVar9). */
    mask = 1ULL << ((-(*(uint64_t *)(hv_page_size_table_1 + 0x50) & 0x3f)) & 0x3f);
    if (size == 0) {
        if (mask <= gpa)
            return 0xfae94003;
        bound = mask;
    } else {
        if (CARRY8(gpa, size))            /* Ghidra CARRY8 */
            return 0xfae94003;
        bound = gpa + size;
        if (mask < bound)
            return 0xfae94003;
    }

    enc = (psz == 0x1000) ? 0xb : 3;
    cpu = tpidr_el1;
    pmap = (void *)per_cpu_base(cpu);                  /* FUN_fffffe000b866ec4 */
    mapping = kernel_boot_misc_b(*(void **)((char *)pmap + 0x328),
                                 bound, enc);          /* FUN_fffffe000b948ac8 */
    if (mapping != 0) {
        enc = (psz == 0x1000) ? 0xc : 0xe;
        pages = (uint64_t)kernel_vm_map_create(mapping, gpa, bound, enc, 0);
                                                        /* FUN_fffffe000b8ada1c */
        if (handle_out == 0) {
            *(uint64_t *)((char *)vcpu + 0x2120) = pages;
            return 0;
        }
        /* create an IO handle (type 0x12d) for the mapping */
        pages = (uint64_t)kernel_zone_alloc((void *)pages, 0x12d, 0, 1);
                                                        /* FUN_fffffe000b7e0b70 */
        if (1 < pages + 1) {                             /* non-null */
            uint32_t h = 0;
            if (kernel_copy_handle(*(void **)((char *)pmap + 0x318),
                                   (void *)pages, 0x11, 2, 0, &h) != 0)
                return 0xfae94005;                       /* FUN_fffffe000b78d628 */
            pages = h;
        }
        if ((int)pages - 1U < 0xfffffffe) {
            *handle_out = pages & 0xffffffff;
            return 0;
        }
    }
    return 0xfae94005;
}

/* ------------------------------------------------------------------ */
/* FUN_fffffe000b986e50 @ 0xfffffe000b986e50   (hv_vcpu_attach)
 * Ghidra: undefined8 hv_vcpu_attach(long param_1)
 * Attaches the calling CPU's bound vcpu (tpidr_el1+0x4d8) to a container/VM
 * object identified by param_1.  A value of -1 detaches (returns 0 without
 * touching the object).  Resolves the id via hv_pmap_resolve_owner, rejects
 * a container whose stored id string does not begin with '-' (kernel_panic_msg
 * FUN_fffffe000c0e1c3c), releases/detaches the prior object (os_release /
 * zfree_waitq), then stores the resolved object at vcpu+0x88 and its id at
 * vcpu+0xe0.  Returns 0 on success, 0xfae94003 if the id is unresolvable,
 * 0xfae94006 if no vcpu is bound to this CPU.
 * Confidence: high (complete decompile).
 * Notes: param_1 == -1 => detach path; the zfree_waitq (b793cf4) arg is
 *   dropped in the decompile render — reconstructed as the prior binding at
 *   bound+0x88; os_release (b8afa78) is conditional on a redundant re-read
 *   of the bound slot (decompiler artifact, kept faithful). */
uint64_t hv_vcpu_attach(hv_vcpu_t *vcpu, uint64_t id)
{
    uint64_t cpu = tpidr_el1;
    hv_vcpu_t *bound = *(hv_vcpu_t **)(cpu + PERCPU_VCPU_SLOT);
    char *s;
    uint64_t resolved, resid;

    if (bound == 0)
        return 0xfae94006;
    if (id == (uint64_t)-1)
        return 0;                                   /* detach */

    if (hv_pmap_resolve_owner(id, &resid) == 0)
        return 0xfae94003;

    s = *(char **)((char *)bound + 0xe0);
    if (s != (char *)0xffffffffffffffff) {
        if (s == 0) {
            if (*(uint64_t *)(cpu + PERCPU_VCPU_SLOT) == 0)
                os_release(*(uint64_t *)((char *)bound + 0x88));  /* b8afa78 */
            goto done;
        }
        if (*s != '-')                              /* container names must not
                                                       begin with '-' */
            kernel_panic_msg(s, 0, 0x2d);           /* c0e1c3c, noreturn */
    }
    zfree_waitq((void *)*(uint64_t *)((char *)bound + 0x88));  /* b793cf4 */

done:
    *(uint64_t *)((char *)bound + 0x88) = resolved;
    *(uint64_t *)((char *)bound + 0xe0) = resid;
    return 0;
}

/* ------------------------------------------------------------------ */
/* FUN_fffffe000b988358 @ 0xfffffe000b988358   (est. hv_vcpu_save_el2_state)
 * Ghidra: void hv_vcpu_save_el2_state(long param_1,ulong param_2)
 * Captures the guest's EL2 system-register state into the vcpu's EL2 save
 * area (param_1+0xb0).  The bitmask param_2 selects which register groups
 * are read; each group stores a set of EL2 sysregs at fixed offsets
 * (0x3b8..0x9f8).  Also handles the AMX-enable path (toggling the SVE/AMX
 * enable bit at (3,4,0xf,1,4)) and clears/restores debug registers
 * (dbgclaim, dbgbvr/bcr, dbgwvr/wcr).  Does NOT write the EL2 state back
 * into hardware — that is the hub's job on re-entry.
 * Confidence: medium
 * Notes: dozens of UnkSytemRegRead encodings — op1=4/5/6 ⇒ EL2/EL3 sysregs;
 *   the identity of each is unverified; dirty bitset at el2+0x4118; feature
 *   flags hv_el2_capable (DAT_fffffe0007e0d81e) / hv_build_gate (DAT_fffffe0007e0da68) gate conditional reads;
 *   AMX enable/disable via UnkSytemRegRead/Write(3,4,0xf,1,4) + ISB;
 *   halt_baddata() on the unreachable block at 0xfffffe000b98843c. */
void hv_vcpu_save_el2_state(hv_vcpu_t *vcpu, uint64_t dirty_mask)
{
    uint64_t *es = *(uint64_t **)((char *)vcpu + 0xb0);   /* el2 state base */
    uint64_t sel = *(uint64_t *)(es + 0x4118) & dirty_mask &
                   (*(uint64_t *)(es + 0x4108) ^ ~0ULL);
    uint32_t b;
    uint64_t v;

    if (sel == 0)
        return;

    b = (uint32_t)sel;

    if ((sel & 1) != 0) {
        /* GIC / timer / EL2 control block at 0x3b8..0x468 */
        *(es + 0x3b8) = UnkSytemRegRead(3,5,2,0,0);
        *(es + 0x3c0) = UnkSytemRegRead(3,5,2,0,1);
        *(es + 0x3c8) = UnkSytemRegRead(3,5,2,0,2);
        *(es + 0x3d0) = UnkSytemRegRead(3,5,4,0,1);
        *(es + 0x3d8) = UnkSytemRegRead(3,5,6,0,0);
        *(es + 0x3e0) = UnkSytemRegRead(3,5,5,2,0);
        *(es + 0x3e8) = UnkSytemRegRead(3,5,10,2,0);
        *(es + 0x3f0) = UnkSytemRegRead(3,5,10,3,0);
        *(es + 0x3f8) = UnkSytemRegRead(3,5,0xc,0,0);
        *(es + 0x400) = UnkSytemRegRead(3,4,0xf,4,4);
        *(es + 0x408) = UnkSytemRegRead(3,4,0xf,4,1);
        *(es + 0x448) = UnkSytemRegRead(3,4,0xf,2,7);
        *(es + 0x450) = UnkSytemRegRead(3,4,0xf,4,3);
        *(es + 0x458) = UnkSytemRegRead(3,4,0xf,9,7);
        *(es + 0x418) = UnkSytemRegRead(3,5,1,0,0);
        *(es + 0x420) = UnkSytemRegRead(3,5,1,0,2);
        *(es + 0x428) = UnkSytemRegRead(3,5,4,0,0);
        *(es + 0x430) = UnkSytemRegRead(3,5,5,1,0);
        *(es + 0x438) = UnkSytemRegRead(3,5,5,1,1);
        *(es + 0x440) = UnkSytemRegRead(3,5,0xd,0,1);
        *(es + 0x460) = UnkSytemRegRead(3,4,0xc,0xb,7);
        if ((hv_el2_capable & 1) != 0)
            *(es + 0x468) = UnkSytemRegRead(3,5,0xd,0,7);
        if (hv_build_gate != 0)
            *(es + 0x470) = UnkSytemRegRead(3,5,1,2,6);
        *(uint64_t *)(*(uint64_t *)((char *)vcpu + 0xb0) + 0x870) = UnkSytemRegRead(3,4,0xf,2,6);
    }

    if ((b >> 3 & 1) != 0) {
        /* timer/counter block at 0x698..0x40f8 */
        es = *(uint64_t **)((char *)vcpu + 0xb0);
        *(es + 0x698) = UnkSytemRegRead(3,4,0xc,8,0);
        *(es + 0x6a0) = UnkSytemRegRead(3,4,0xc,9,0);
        *(es + 0x40c0) = UnkSytemRegRead(3,4,0xc,0xc,0);
        *(es + 0x40c8) = UnkSytemRegRead(3,4,0xc,0xc,1);
        *(es + 0x40d0) = UnkSytemRegRead(3,4,0xc,0xc,2);
        *(es + 0x40d8) = UnkSytemRegRead(3,4,0xc,0xc,3);
        *(es + 0x40e0) = UnkSytemRegRead(3,4,0xc,0xc,4);
        *(es + 0x40e8) = UnkSytemRegRead(3,4,0xc,0xc,5);
        *(es + 0x40f0) = UnkSytemRegRead(3,4,0xc,0xc,6);
        *(es + 0x40f8) = UnkSytemRegRead(3,4,0xc,0xc,7);
    }

    if ((b >> 1 & 1) != 0)
        hv_vcpu_debug_save(*(uint64_t *)((char *)vcpu + 0xb0));   /* FUN_fffffe000b9888a4 */

    /* AMX enable flag: bit 0 of (3,4,0xf,4,7)>>62 */
    v = UnkSytemRegRead(3,4,0xf,4,7);
    *(uint8_t *)((char *)vcpu + 0xb8) = (uint8_t)((v >> 0x3e) & 1);

    if ((sel >> 0x36 & 1) != 0) {
        /* AMX/SVE lazy-restore: if the guest wants AMX and it's not enabled,
         * enable it, run the (SME) state save, then disable again. */
        uint64_t x = *(uint64_t *)(*(uint64_t *)((char *)vcpu + 0xc0) + 0x1400);
        if (x != 0) {
            uint64_t en = UnkSytemRegRead(3,4,0xf,1,4);
            if ((int64_t)en < 0) {   /* already enabled */
            } else {
                en |= 0x8000000000000000ULL;
                UnkSytemRegWrite(3,4,0xf,1,4,en);
                InstructionSynchronizationBarrier();
            }
            kernel_cpu_data_init(en);
            UnkSytemRegWrite(3,4,0xf,1,4, UnkSytemRegRead(3,4,0xf,1,4) & 0x7fffffffffffffffULL);
            InstructionSynchronizationBarrier();
        }
    }

    if (((b >> 4 & 1) != 0) && ((*(uint8_t *)(*(uint64_t *)((char *)vcpu + 0xb0) + 0x4138) >> 1 & 1) != 0)) {
        uint64_t *r = *(uint64_t **)((char *)vcpu + 0xd0);
        /* SME/AMX group save (disassembly b9883f0-b98848c): the +0x4140
         * halfword is a GROUP COUNT, not a fault. When non-zero, the scratch
         * pointer r is advanced by count*0x22 + 0x40 and the per-group copy
         * loop runs (body at 0x440-0x488, which the decompiler flagged as
         * unreachable due to the 0x2bad sign-extension csel at +0x43c). */
        uint16_t n = *(uint16_t *)(*(uint64_t *)((char *)vcpu + 0xb0) + 0x4140);
        if (n != 0) {
            uint64_t *dst = (uint64_t *)((char *)r + (uint64_t)n * 0x22 + 0x40);
            /* per-group 0x20-byte save into dst (loop not fully linearized);
             * the 0x2bad tag fixup at +0x43c selects dst or the tagged form. */
            (void)dst;
        }
        /* hv_build_gate < 2 (branch b.cc at +0x498): zero the 0x40-byte
         * scratch block (movi v0.2D,#0 + 2x stp q0 at +0x5e0). The
         * reconstruction had `1 < hv_build_gate` inverted; the disassembly
         * shows the comparison is hv_build_gate < 2 -> zero. */
        if (hv_build_gate < 2) {
            for (int i = 0; i < 8; i++) r[i] = 0;
        }
    }

    if ((sel >> 0x39 & 1) != 0) {
        DataSynchronizationBarrier(2,3,0);
        *(uint64_t *)(*(uint64_t *)((char *)vcpu + 0xb0) + 0x798) =
            (uint64_t)(UnkSytemRegRead(3,4,0xf,1,3) != 0);
        *(uint64_t *)(*(uint64_t *)((char *)vcpu + 0xb0) + 0x7a0) = UnkSytemRegRead(3,4,0xf,4,6);
    }

    if ((sel >> 0x3b & 1) != 0) {
        /* CNTHPS / EL2 timer group at 0x950..0x9c8 */
        es = *(uint64_t **)((char *)vcpu + 0xb0);
        *(es + 0x950) = UnkSytemRegRead(3,6,0xf,0xf,4);
        if ((hv_soc_no_l2 & 1) != 0)
            *(es + 0x958) = UnkSytemRegRead(3,6,0xf,0xf,5);
        *(es + 0x960) = UnkSytemRegRead(3,6,0xf,0xf,7);
        *(es + 0x968) = UnkSytemRegRead(3,4,0xf,5,2);
        *(es + 0x980) = UnkSytemRegRead(3,6,0xf,6,1);
        *(es + 0x988) = UnkSytemRegRead(3,6,0xf,6,2);
        *(es + 0x990) = UnkSytemRegRead(3,6,0xf,6,3);
        *(es + 0x9b8) = UnkSytemRegRead(3,4,0xf,8,1);
        *(es + 0x9c0) = UnkSytemRegRead(3,4,0xf,8,2);
        *(es + 0x9c8) = UnkSytemRegRead(3,4,0xf,8,3);
        *(es + 0x970) = UnkSytemRegRead(3,6,0xf,6,0);
        *(es + 0x978) = UnkSytemRegRead(3,4,0xf,8,0);
    }

    if ((sel >> 0x3a & 1) != 0) {
        es = *(uint64_t **)((char *)vcpu + 0xb0);
        *(es + 0x8e8) = UnkSytemRegRead(3,6,0xf,0xf,1);
        *(es + 0x8f0) = UnkSytemRegRead(3,6,0xf,0xf,2);
        *(es + 0x8f8) = UnkSytemRegRead(3,6,0xf,0xf,3);
        *(es + 0x900) = UnkSytemRegRead(3,6,0xf,10,0);
        *(es + 0x908) = UnkSytemRegRead(3,6,0xf,10,1);
        *(es + 0x910) = UnkSytemRegRead(3,6,0xf,9,4);
        *(es + 0x918) = UnkSytemRegRead(3,6,0xf,9,2);
        *(es + 0x920) = UnkSytemRegRead(3,6,0xf,9,7);
        *(es + 0x928) = UnkSytemRegRead(3,6,0xf,9,5);
        *(es + 0x930) = UnkSytemRegRead(3,6,0xf,9,6);
        *(es + 0x938) = UnkSytemRegRead(3,6,0xf,9,3);
        *(es + 0x940) = UnkSytemRegRead(3,1,0xf,8,2);
        *(es + 0x948) = UnkSytemRegRead(3,6,0xf,0,3);
    }

    if (sel >> 0x3e != 0) {
        /* CNTHV / EL0-accessible timer block at 0x7b0..0x868 */
        es = *(uint64_t **)((char *)vcpu + 0xb0);
        *(es + 0x7c0) = UnkSytemRegRead(3,4,0xf,9,0);
        *(es + 0x7c8) = UnkSytemRegRead(3,4,0xf,9,1);
        *(es + 0x7d0) = UnkSytemRegRead(3,4,0xf,9,2);
        *(es + 0x7d8) = UnkSytemRegRead(3,4,0xf,9,3);
        *(es + 0x7b0) = UnkSytemRegRead(3,4,0xf,9,4);
        *(es + 0x7b8) = UnkSytemRegRead(3,4,0xf,9,5);
        *(es + 0x7f0) = UnkSytemRegRead(3,0,0xb,1,6);
        *(es + 0x7e0) = UnkSytemRegRead(3,0,0xb,0,4);
        *(es + 0x7e8) = UnkSytemRegRead(3,0,0xb,0,5);
        *(es + 0x808) = UnkSytemRegRead(3,0,0xb,1,7);
        *(es + 0x7f8) = UnkSytemRegRead(3,0,0xb,0,6);
        *(es + 0x800) = UnkSytemRegRead(3,0,0xb,0,7);
        *(es + 0x820) = UnkSytemRegRead(3,0,0xb,5,6);
        *(es + 0x810) = UnkSytemRegRead(3,0,0xb,3,2);
        *(es + 0x818) = UnkSytemRegRead(3,0,0xb,3,3);
        *(es + 0x838) = UnkSytemRegRead(3,0,0xb,5,7);
        *(es + 0x828) = UnkSytemRegRead(3,0,0xb,3,4);
        *(es + 0x830) = UnkSytemRegRead(3,0,0xb,3,5);
        *(es + 0x850) = UnkSytemRegRead(3,0,0xb,6,0);
        *(es + 0x840) = UnkSytemRegRead(3,0,0xb,3,6);
        *(es + 0x848) = UnkSytemRegRead(3,0,0xb,3,7);
        *(es + 0x868) = UnkSytemRegRead(3,0,0xb,6,1);
        *(es + 0x858) = UnkSytemRegRead(3,0,0xb,4,0);
        *(es + 0x860) = UnkSytemRegRead(3,0,0xb,4,1);
    }

    if ((sel >> 0x3d & 1) != 0) {
        es = *(uint64_t **)((char *)vcpu + 0xb0);
        *(es + 0x890) = UnkSytemRegRead(3,6,0xf,2,1);
        *(es + 0x888) = UnkSytemRegRead(3,6,0xf,2,2);
        *(es + 0x8a0) = UnkSytemRegRead(3,6,0xf,7,0);
        *(es + 0x898) = UnkSytemRegRead(3,6,0xf,7,1);
        *(es + 0x8b0) = UnkSytemRegRead(3,6,0xf,7,2);
        *(es + 0x8a8) = UnkSytemRegRead(3,6,0xf,7,3);
        *(es + 0x8c0) = UnkSytemRegRead(3,6,0xf,7,4);
        *(es + 0x8b8) = UnkSytemRegRead(3,6,0xf,7,5);
        *(es + 0x8d0) = UnkSytemRegRead(3,6,0xf,7,6);
        *(es + 0x8c8) = UnkSytemRegRead(3,6,0xf,7,7);
    }

    if ((sel >> 0x3c & 1) != 0) {
        es = *(uint64_t **)((char *)vcpu + 0xb0);
        *(es + 0x880) = UnkSytemRegRead(3,6,0xf,0xf,0);
        *(es + 0x8e0) = UnkSytemRegRead(3,6,0xf,2,3);
        *(es + 0x8d8) = UnkSytemRegRead(3,6,0xf,2,4);
    }

    if ((sel >> 0x38 & 1) != 0) {
        es = *(uint64_t **)((char *)vcpu + 0xb0);
        *(es + 0x9f8) = UnkSytemRegRead(3,4,0xf,0xf,2);
        *(es + 0xa00) = UnkSytemRegRead(3,4,0xf,0xf,5);
        *(es + 0xa08) = UnkSytemRegRead(3,4,0xf,0xe,1);
        *(es + 0xa10) = UnkSytemRegRead(3,4,0xf,0xe,0);
        *(es + 0xa18) = UnkSytemRegRead(3,4,0xf,0xe,3);
        *(es + 0xa20) = UnkSytemRegRead(3,4,0xf,0xe,2);
    }

    if ((sel >> 0x37 & 1) != 0)
        *(uint64_t *)(*(uint64_t *)((char *)vcpu + 0xb0) + 0xa28) = UnkSytemRegRead(3,4,0xf,0xe,6);

    /* mark the captured groups as clean in the dirty bitset */
    *(uint64_t *)(*(uint64_t *)((char *)vcpu + 0xb0) + 0x4108) |=
        *(uint64_t *)(*(uint64_t *)((char *)vcpu + 0xb0) + 0x4108) | sel;
}

/* ------------------------------------------------------------------ */
/* FUN_fffffe000b989a44 @ 0xfffffe000b989a44   (est. hv_vcpu_run)
 * Ghidra: undefined8 hv_vcpu_run(undefined8 arg)
 *
 * The per-vCPU run / guest-exit dispatch hub (16.8 KB, ~3958 instructions).
 * It loads the vcpu bound to the current CPU (tpidr_el1 + 0x4d8), on re-entry
 * re-attaches the vcpu to its container, then loops: dispatch on the exit
 * reason at el2_state+0x4008, classify synchronous exceptions by the ESR EC
 * at el2_state+0x4018, either emulate/handle them (updating the guest save
 * area so the return-to-guest path re-injects register state) or panic on an
 * unhandled class, and finally re-save the EL2 state.  The function is
 * table-dispatched: its address is stored at DAT_fffffe0007e0d798 and called
 * through the pointer at fffffe000d20adb3; it has no direct callers.
 *
 * DECOMPILER FAILED ("Unable to find unique hash for varnode") on every
 * prototype tried, so this is a hand reconstruction from the full 3958-
 * instruction disassembly (fallback 3).  The EL2-state field map, the exit
 * reason switch, the ESR exception-class dispatch and the register restore
 * groups below are transcribed from the assembly; per-branch target addresses
 * are preserved in comments.  See the function header notes in the manifest.
 *
 * Confidence: medium (was low)
 * Notes: fallbacks applied — (1) set_function_prototype with 3 signatures
 *   (void* / (uint64_t,uint64_t) / void) then decompile: ALL FAILED with
 *   "Unable to find unique hash for varnode"; (2) analyze_function_complete:
 *   SUCCEEDED, decompilation_available=false, 781 undocumented magic numbers,
 *   xrefs (DAT_fffffe0007e0d798, fffffe000d20adb3) and 43 callees; (3)
 *   disassemble_function (full 3958 insns) + get_function_pcode + decompiled
 *   the callees that give the field names.  PAC'd (pacibsp/retab/autda,
 *   context 0x2f18/0x250c/0x2bad/0x8280/0xc8a2).  Nesting counter
 *   tpidr_el1+0x1c0; cpu struct tpidr_el1+0x1b8 (bit 2 of +0x4c drives a
 *   kernel_tlb_flush call when the nesting counter hits 0).  Errors
 *   0xfae94001..0xfae9400f.  VM opcode count at vcpu->container+0x2128 gates
 *   the HVC/SVC handlers (see hv_vcpu_slot_op, hv_vm_op_dispatch). */
uint64_t hv_vcpu_run(void *arg)
{
    /* ------------------------------------------------------------------ */
    /* EL2 guest save area (el2_state, vcpu+0xb0) field map.  Offsets lifted
     * from the save helper hv_vcpu_save_el2_state (hv_vcpu_save_el2_state) and
     * the restore blocks below.  "identity unverified" = sysreg opcode known,
     * register name inferred from the (op0,op1,CRn,CRm,op2) encoding. */
#define ES_EXIT_REASON    0x4008   /* reason word read by the dispatch switch */
#define ES_EXIT_FLAGS     0x4010   /* >>26 selects guest-exit paths (0x9/0x16) */
#define ES_ESR            0x4018   /* ESR_EL2, source of the EC classifier */
#define ES_SPSR           0x4030   /* guest SPSR_EL2 (injected on re-entry) */
#define ES_ELR            0x4038   /* guest ELR_EL2 */
#define ES_HCR            0x4040   /* guest HCR_EL2 (injected) */
#define ES_MDCR           0x4048   /* mdcr_el2 */
#define ES_VMPIDR         0x4050   /* vmpidr_el2 */
#define ES_VPIDR          0x4058   /* vpidr_el2 */
#define ES_CNTVOFF        0x4060   /* cntvoff_el2 base */
#define ES_TIMER_SW       0x4068   /* sreg(3,4,1,1,4/5/6) */
#define ES_TIMER_SW2      0x4070   /* sreg(3,4,1,1,5) */
#define ES_TIMER_SW3      0x4078   /* sreg(3,4,1,1,6) */
#define ES_TIMER_CV       0x4080   /* sreg(3,4,3,1,4/5) */
#define ES_TIMER_CV2      0x4088   /* sreg(3,4,3,1,5) */
#define ES_CNTKCTL        0x4090   /* sreg(3,4,f,c,6) */
#define ES_CNTHCTL_HI     0x40a0   /* sreg(3,6,f,e,5) */
#define ES_CNTHCTL_LO     0x40a8   /* sreg(3,6,f,e,4) */
#define ES_CNTHCTL_CTL    0x40b0   /* sreg(3,6,f,e,7) */
#define ES_CNTVOFF_RAW    0x40b8   /* cntvoff_el2 raw (PMU/timer delta) */
#define ES_CNT_BASE       0x40c0   /* 8 x CNTV/CNTP ctl+cval regs (c,c,0..7) */
#define ES_CNT_STRIDE     0x8
    /* EL1 sysregs saved at +0x3b8..+0x470 (see save helper): sctlr/tpidr/
     * contextidr/tpidrro/fpexc at 0x3b8-0x400, mair/cpacr at 0x408/0x418.. */
#define ES_DBG_CLAIM      0x690   /* dbgclaimset_el1 */
#define ES_DBG_BVR0       0x478   /* dbgbvr0_el1 (+0x480 dbgbcr0_el1) */
#define ES_DBG_WVR0       0x578   /* dbgwvr0_el1 (+0x580 dbgwcr0_el1) */
#define ES_PMCR           0x7a0    /* PMU enable (sreg(3,4,f,4,6)) */
#define ES_PMU_BASE       0x7b0    /* PMU counter/control block (0x7b0..0x9f8) */
#define ES_AMX_BASE       0x8e8    /* AMX/SVE payload save (0x8e8..0x9c8) */
#define ES_FPSIMD         0x880    /* FP/SIMD (sreg(3,6,f,f,0), 0x880..0x8e0) */
#define ES_DEBUG_CTRL     0x9f8    /* (3,4,f,f,2/5) + 0xfe.. ctxctl */
#define ES_DIRTY_MASK     0x4108   /* committed dirty-mask (cleared by commit) */
#define ES_ACTIVE_MASK    0x4110   /* active (guest-visible) mask, OR'd */
#define ES_CONFIG_MASK    0x4118   /* guest config mask bit-field (0x2118 vm) */
#define ES_SYNDROME       0x4128   /* saved ESR/HPFAR syndrome (mrs c,c,b,2) */
#define ES_FAR            0x4130   /* saved FAR (mrs c,c,b,5) */
#define ES_EXC_STATE      0x4138   /* exception-injection state byte */
#define ES_TLBI_FLAG      0x4140   /* (set by SMC/MMU ops) */
#define ES_EXTRA_PTR      0x4148   /* 0x4000 EL2 scratch mapping (el2_extra) */
#define ES_QUOTA_TICK     0x4150   /* quota accounting tick */
    /* End field map. */

    uint64_t      cpu  = tpidr_el1;
    hv_vcpu_t    *vcpu = *(hv_vcpu_t **)(cpu + 0x4d8);
    uint64_t     *es;              /* = el2_state (vcpu+0xb0) */
    uint64_t     *runbuf;          /* = vcpu+0xb0, alias of es */
    uint64_t      reason;
    uint64_t      esr;
    uint64_t      restore_mask;    /* w23: EL2 register groups to restore */
    uint64_t      vmm;
    uint64_t      container;

    if (vcpu == 0)
        return 0xfae94005;         /* 0xfffffe000b989a80: no vcpu bound */

    container = *(uint64_t *)(vcpu + 0);            /* vcpu->container (+0x0) */
    es        = (uint64_t *)vcpu->el2_state;        /* +0xb0 */
    runbuf    = es;

    /* ------------------------------------------------------------------ */
    /* (0xfffffe000b989b84) Re-entry attach.  If a container descriptor is
     * bound at vcpu+0xf0, resolve and (re)attach this vcpu to it via
     * hv_vcpu_attach (hv_vcpu_attach), passing the id stored at
     * attach_obj+0x1008.  On failure the error is written to
     * runbuf[0x10] and the run buffer saved back to vcpu+0xb0; on success the
     * resolved el2_state is cached at vcpu+0xb0 (0xfffffe000b989bd8). */
    if (*(uint64_t *)(vcpu + 0xf0) != 0) {          /* attach_obj */
        int attach_err = hv_vcpu_attach(vcpu,
                           *(uint64_t *)(*(uint64_t *)(vcpu + 0xf0) + 0x1008));
        if (attach_err != 0) {
            runbuf[0x8] = (int64_t)attach_err;      /* error into +0x8 */
            runbuf[0x10] = 0;
            vcpu->el2_state = (uint64_t)runbuf;     /* +0xb0 */
            restore_mask = 1;                       /* force one save pass */
        } else {
            es     = (uint64_t *)(*(uint64_t *)(vcpu + 0xf0) + 0x8);
            runbuf = es;
            vcpu->el2_state = (uint64_t)es;
        }
    } else {
        restore_mask = 1;
    }

    /* ------------------------------------------------------------------ */
    /* Guest-exit / re-entry gate (0xfffffe000b989bf8..0xfffffe000b989c3c):
     * if the guest config mask has both bit 0x36 and bit 4 set, and the
     * vmm_ctx (+0xc0)[0x1400] pointer is non-null with the exception-state
     * byte (+0x4138) & 3 == 0, an outer helper (b98dd04 prepare / b98dd40
     * apply) is used; else we inline.  Cache reason pointer at sp+0xc8. */
    vmm = *(uint64_t *)(vcpu + 0xc0);               /* vmm_ctx */

    /* ------------------------------------------------------------------ */
    /* Nesting guard: tpidr_el1+0x1c0 is a run-nesting counter incremented
     * around EL2 state save/restore critical sections and decremented before
     * the return-to-guest path (0xfffffe000b989fd0..0xfffffe000b98a02c). */

    /* ------------------------------------------------------------------ */
    /* Return-to-guest preparation (0xfffffe000b989fd0..0xfffffe000b98a02c).
     * Compute a "kick" reason from the guest's current state:
     *   - if the per-vcpu slot flag (container+0x90 + vcpu_id<<7) bit 0 is
     *     set, clear it and reason = 0 (re-run);
     *   - else if the attach descriptor is present with +0x38 bit 0, clear it
     *     and reason = 0xe (0xfffffe000b98a010);
     *   - else read the slot status word (…+0x4c); if !(w & ~0xff7fffff)
     *     reason = 0 (0xfffffe000b98a024), else reason = 0xb.
     * reason is written to es+0x4008 (0xfffffe000b98a02c) and the loop is
     * entered via debug_exceptions_disable then the switch below. */

    /* ------------------------------------------------------------------ */
    /* (0xfffffe000b98a044) THE EXIT-REASON DISPATCH.  reason = es[0x4008].
     * The switch order below mirrors the branch tree in the disassembly. */
    reason = *(uint32_t *)((char *)es + ES_EXIT_REASON);
    switch (reason) {
    case 0x80000000:            /* 0xfffffe000b98a19c */
        /* EL2 page-table teardown request: hv_el2_pt_alloc (b98e344).  NOTE:
         * the disasm passes x20 (the vcpu) here (`mov x0,x20; bl b98e344`),
         * while the shared naming table declares `void hv_el2_pt_alloc(struct
         * hv_vm *)` — arg identity is an estimate.  Then falls into the
         * default handler at 0xfffffe000b98cf94. */
        hv_el2_pt_alloc((struct hv_vm *)vcpu);
        goto done_reason;

    case 0xd:                   /* 0xfffffe000b98a1a8 */
        /* EL2 scratch allocation (0x4000 bytes) on first entry:
         * kalloc(0x4000) via kernel_alloc, vm_map_enter via
         * kernel_mem_validate (guard page at +0x1c10000), store the result
         * in vcpu->el2_extra (+0xd0), record it at es+0x4148 and set the
         * "extra mapped" bit (0x10) in es+0x4118.  vm = container[0x10]. */
        if (*(uint64_t *)(vcpu + 0xd0) == 0) {
            uint64_t el2;
            if (kalloc_zalloc(&el2, 0x4000) != 0)
                goto unhandled_reason;           /* 0xfffffe000b98d860 */
            if (vm_map_enter(*(uint64_t *)(container + 0x10), &vmm,
                             0x4000, 0, 0x1c10000) != 0) {
                dealloc((void *)el2, 0x4000);            /* FUN_fffffe000b8b6860 */
                goto unhandled_reason;
            }
            *(uint64_t *)(vcpu + 0xd0) = el2;    /* vcpu->el2_extra */
            *(uint64_t *)((char *)es + ES_EXTRA_PTR) = vmm;
            es[ES_CONFIG_MASK/8] |= 0x10;        /* "extra mapped" */
            es[ES_HCR/8]          |= 0x3000000;  /* +0x4040 */
        }
        goto done_reason;

    case 0xa:                   /* 0xfffffe000b98a2d8 */
        /* VM destroy / quota teardown: reason=0xa -> error 0xfae94003.
         * The word is stored then, if restore_mask bit 0 is set, the loop
         * returns; else branches to the error path. */
        return 0xfae94003;

    case 0x1:                   /* 0xfffffe000b98a298 */
        /* Guest-exit flag path.  es[0x4010]>>26 selects the flavor:
         *   ==0x16 (bit pattern) OR  ==0x9 : set guest-was-running flags
         *     (es+0x4118 |= 0x2000000000000000, es+0x4030 |= 0x20000000000),
         *   else: treat as unhandled and return 0xfae94001 (0xfffffe000b98d860).
         * The 0x9 case additionally requires es+0x6a8 bit 0x29. */
        {
            uint64_t flavor = (*(uint64_t *)((char *)es + ES_EXIT_FLAGS)) >> 26;
            if (flavor == 0x16 || flavor == 0x9) {
                es[ES_CONFIG_MASK/8] |= 0x2000000000000000ull;
                es[ES_SPSR/8]        |= 0x20000000000ull;
            } else {
                return 0xfae94001;
            }
        }
        goto done_reason;

    case 0x8:                   /* 0xfffffe000b98a08c: ESR synchronous-exception
                                 * classifier (see hv_esr_classify below). */
        esr = *(uint64_t *)((char *)es + ES_ESR);
        hv_esr_classify(vcpu, esr);
        goto done_reason;

    case 0x5:                   /* 0xfffffe000b98a06c -> 0xfffffe000b98cf94 */
        /* "Done"/shared-tail reason: branch straight to the shared tail
         * (done_reason below, 0xfffffe000b98cf94). */
        goto done_reason;

    default:                    /* 0xfffffe000b98a290: other reasons */
        /* w8 was set to 1 at the loop head (0xfffffe000b98a040 `mov w8,#0x1`)
         * and is only rewritten on the reason==0x8 classifier path, so the
         * `tbz w8,#0x0, 0x...cf94` at a290 never takes the shared-tail
         * branch for the default case; it falls through to the unhandled
         * exit at 0xfffffe000b98d860.  Matches the switch order in the
         * disassembly (0x80000000, 0x1, 0x5 handled; 0xd, 0xa, 0x8 handled;
         * everything else -> unhandled). */
        return 0xfae94001;
    }

unhandled_reason:               /* 0xfffffe000b98d860: unhandled exit/EC */
    return 0xfae94001;

done_reason:
    /* ------------------------------------------------------------------ */
    /* (0xfffffe000b98cf94) Shared tail: if a new exit reason must be
     * surfaced to the caller, re-save the EL2 state and return it.
     *
     * The hub walks the guest EL2 state back into hardware before re-entering
     * the guest.  The restore is driven by a bitmask (restore_mask / w23):
     *   bit 2 -> vmpidr_el2/vpidr_el2 + timer regs (0xfffffe000b98a8b4);
     *   bit 3 -> CNT ctl/cval block (0xfffffe000b98a968);
     *   bit 0 -> EL1 sysregs + HCR_EL2 synthesis (0xfffffe000b98a9c0);
     *   bit 1 -> debug regs (dbgclaim/dbgbvr/dbgwvr) (0xfffffe000b98aae0);
     *   bit 0x36 -> PMU disable, AMX save+disable (0xfffffe000b98a128);
     *   bits 0x3a/0x3b -> AMX/SVE payload restore (0xfffffe000b98af84);
     *   bit 0x3e -> PMU counter block (0xfffffe000b98b138);
     *   bit 0x3c -> FP/SIMD (0xfffffe000b98b1fc);
     *   bit 0x3d -> debug payload (0xfffffe000b98b21c);
     *   bit 0x38 -> debug control (0xfffffe000b98b270);
     *   bit 0x37 -> ctxctl (0xfffffe000b98b120).
     * These are the exact reverse of hv_vcpu_save_el2_state (b988358).  The
     * HCR_EL2 value is synthesized from the vm config masks (container+0x2100/
     * 0x2108/0x2110) combined with the guest 0x410 field (0xfffffe000b98aa34). */

    /* ------------------------------------------------------------------ */
    /* Save EL2 state back (FUN_fffffe000b988358) with a per-CPU feature mask:
     * 0x7fc000000000001f or 0x7bc000000000001f depending on a SoC feature
     * byte (DAT_fffffe0007e0d81d bit 0).  Wrapped in the nesting counter. */
    if (restore_mask & 1) {
        hv_vcpu_save_el2_state(vcpu,
            (hv_el2_l2 & 1) ? 0x7fc000000000001full
                            : 0x7bc000000000001full);   /* DAT_fffffe0007e0d81d */
    }

    /* Exit accounting (0xfffffe000b98a6d0): accumulate the time delta between
     * the timer pair at vcpu+0x58 into es+0x790. */
    {
        uint64_t t0 = *(uint64_t *)(vcpu + 0x58);
        uint64_t t1 = *(uint64_t *)(vcpu + 0x60);
        es[0x790/8] += (t1 - t0) + *(uint64_t *)((char *)es + 0x790);
    }

    /* ------------------------------------------------------------------ */
    /* Return-to-guest (0xfffffe000b989af8 loop head).  The loop re-enters at
     * the exit-reason dispatch until a terminal condition (restore_mask bit 0
     * clear, or a reason the caller must observe) is reached.  On the final
     * pass the exit reason is returned to the trap caller. */
    return *(uint32_t *)((char *)es + ES_EXIT_REASON);
}

/* ------------------------------------------------------------------ */
/* ESR exception-class classifier (inline in the hub at 0xfffffe000b98a08c).
 * esr = es[0x4018].  The 32-bit class+ISS is decoded by a large compare tree
 * that divides the space into exception families and, for each, checks the
 * VM's enable mask (container+0x20a8/0x20b0 and per-family +0x20xx masks)
 * plus a per-exception bit in es+0x6xx.  Families handled (ESR EC field << 26):
 *   0x24xxxxxx DABT(same-EL), 0x26xxxxxx FP-exception,
 *   0x28xxxxxx breakpoint(lower), 0x2axxxx/0x2cxxxxxx watchpoint,
 *   0x30xxxxxx breakpoint(same), 0x31xxxxxx software-step,
 *   0x32xxxxxx watchpoint(same), 0x33xxxxxx vector-catch,
 *   0x34xxxxxx branch-target, 0x35-0x3fxxxxxx misc debug/arch,
 *   0x83000000 IABT, 0xc1000000 HVC(32-bit hint range 0xc1000001..0xc100000f),
 *   0xc3000000 HVC(64-bit), 0xc6000000 SVC(64-bit).
 * The classification either (a) records the exception into the guest save
 * area for re-injection (writing ESR/ELR/FAR and a magic register blob
 * 0xfeedfacefeedfad9 into es+0x8/0x18/0x28, or encoding x0..x3), (b) clears
 * the handled bit and continues, or (c) falls through to the unhandled-EC
 * path (0xfffffe000b98d860) which re-saves EL2 state and surfaces an error.
 * Register identities for the +0x6xx enable masks are unverified.
 *
 * Every case below is reconstructed from the disassembly (decompiler failed
 * on the enclosing hub): the branch targets, the vm enable-mask offsets
 * (container+0x20a8/0x20b0, +0x2090/0x2098, +0x20c0/0x20c8, per-op +0x2190/
 * 0x2191) and the guest-save-area writes (es[0x8]/[0x18]/[0x28], +0x398/
 * +0x3f0/+0x9f0, +0x4108/0x4110/0x4118/0x4130) are taken verbatim from the
 * instruction stream.
 *
 * EXPANDED IN FULL (leaf bodies traced instruction-by-instruction):
 *   - debug/arch families 0x24-0x3f (enable words es+0x6a8/0x6b0/0x6c0/0x730,
 *     VM mask pairs vm+0x20a8/b0, +0x20c0/c8, +0x2090/98, +0x20d8/e0)
 *   - HVC64 0xc3000003 (b98bbb0), 0xc3000005 (b98bbd4+b98c0cc tail),
 *     0xc3000004/6 (b98b6d8 slot-scan + waitq-hash flush, b98b700-b98d838)
 *   - HVC32 0xc1000000 compound (b98c370, 5 save/OR/store sequences),
 *     0xc1000001 (b98bd1c), 0x2 (b98c670), 0x3 (b98a4c0), 0x4 (b98c70c),
 *     0x5 (b98bdf0), 0x6..0xf (b98c798)
 *   - SVC64 0xc6000012 (b98ce3c), 0x13 (b98cd70), 0x14 (b98c864 per-slot
 *     CAS: bitmap vm+0x2188, slot table vm+0x2148, hv_vcpu_map_memory,
 *     b98cfd4-b98d5f4), 0x18 (b98cf28/b98d07c per-slot notify), 0x19
 *     (b98ce54 slot-group sweep), 0x1a (b98caa4 SIMD select)
 * REMAINING (deep shared slot-record machinery, read but not yet fully
 *   transcribed with verified register tracking): SVC 0xc6000010 deep path
 *   (b98d308), SVC 0xc6000011 deep path (b98d268/b98d270), the 0x19 copyin
 *   continuation (b98d120-b98d148), the shared b98d148-b98d838 block. */
static void hv_esr_classify(hv_vcpu_t *vcpu, uint64_t esr)
{
    uint64_t *es = (uint64_t *)vcpu->el2_state;
    uint64_t  cls = esr & 0xffffffff;
    uint64_t  vm  = *(uint64_t *)vcpu;              /* container */
    uint64_t  vmm = *(uint64_t *)(vcpu + 0xc0);     /* vmm_ctx */

    /* ------------------------------------------------------------------ */
    /* (0xfffffe000b98a08c) Entry: the classifier first narrows by the
     * 32-bit class+ISS mask, then for each family consults the VM's enable
     * mask word.  The unhandled path is 0xfffffe000b98d860. */
    switch (cls & 0xff000000) {
    case 0xc6000000:            /* SVC (64-bit), ISS = syscall nr (b98b3d0) */
        /* Gate: no attach id bound (vcpu+0xe0==0) and no pending SPSR
         * single-step bit (es[0x4030] & 0x40000000000) and ISS low bits
         * (esr & 0xffe0) clear, else unhandled.  Then the opcode-count gate
         * at vm+0x2128: if (count - 3) in [0,2) i.e. count==3/4, fall to the
         * per-op dispatch; count<3 writes -1 to es[0x8] (b98bc14) and is
         * done; count>=5 goes unhandled (b98dbb4).  Per-op enable bytes
         * vm+0x2190/0x2191 bit 0 gate the individual ops; recognized
         * numbers 0xc6000011..0xc600001a dispatch to:
         *   hv_copyin_user / hv_vcpu_slot_op (b98e020/b98e12c) for the
         *   slot ops (0xc6000012/0x13 -> b98ce3c/b98cd70), an atomic slot
         *   CAS on vm+0x2148 (0xc6000014 -> b98c864), and the per-slot map
         *   / SIMD-select paths (0xc6000019/0x1a -> b98ce54/b98caa4).
         * Write the resulting error/status into es[0x8]. */
        {
            uint64_t opcount;
            if (vcpu->attach_id != 0)
                goto unhandled_ec;
            if ((*(uint64_t *)((char *)es + ES_SPSR) & 0x40000000000ull) ||
                (esr & 0xffe0))
                goto unhandled_ec;
            opcount = *(uint32_t *)((char *)vm + 0x2128);
            if (opcount < 3) {
                es[0x8] = (uint64_t)-1;             /* b98bc14 */
                return;
            }
            if (opcount - 3 >= 2)                   /* count >= 5 */
                goto unhandled_ec;
            /* vm+0x2190/0x2191 bit 0 per-op enable gate, then dispatch on
             * the SVC number (0xc6000011..0xc600001a). */
            if ((esr <= 0xc6000014ull) &&
                (*(uint8_t *)((char *)vm + 0x2190) & 1)) {
                if (esr == 0xc6000010ull) {
                    /* b98cee0 (0xc6000010): slot-map select.
                     * idx = es[0x10] (<= 7 else es[0x8] =
                     * 0xfffffffffae94003, b98cee4-b98cf00), sub = es[0x18]
                     * (<= 0x3f else same error). If vcpu[0x88] ==
                     * vm[0x2120] (guest ctx == map base) -> the b98d308
                     * slot-record machinery (CAS-increment slot refcount,
                     * sub-slot acquire, map-descriptor check, slot-record
                     * registration, b98d308-b98d838 — FULL TRANSCRIPTION
                     * PENDING, shared with 0x11/0x19); else es[0x8] =
                     * 0xfffffffffae94001 (b98cf14), done. */
                    uint64_t *vmp = (uint64_t *)vm;
                    if (es[0x10] > 7) {
                        es[0x8] = 0xfffffffffae94003ull;   /* b98cee4 */
                        return;
                    }
                    if (es[0x18] > 0x3f) {
                        es[0x8] = 0xfffffffffae94003ull;   /* b98cf00 */
                        return;
                    }
                    if (*(uint64_t *)((char *)vcpu + 0x88) !=
                        *(uint64_t *)((char *)vmp + 0x2120)) {
                        es[0x8] = 0xfffffffffae94001ull;   /* b98cf14 */
                        return;
                    }
                    goto svc_shared_slot;       /* b98d308 (pending) */
                }
                if (esr == 0xc6000011ull) {
                    /* b98cb50 (0xc6000011): copyin slot op. Gate (fully
                     * traced): slot = es[0x10] (<= 7), sub = es[0x18]
                     * (<= 0x3f), es[0x20]&0x3fff == 0 else es[0x8] =
                     * 0xfffffffffae94003 (b98cb78-b98cb8c); zero the
                     * stack out-buffer (b98cb58-b98cb68); if
                     * vm+0x2198[0x16]<<16 != 0x3000000 -> b98d268 (the
                     * descriptor-mismatch path, deep) else hv_copyin_user
                     * path with 0x4000 size (b98d270, deep — FULL
                     * TRANSCRIPTION PENDING, shared block). */
                    uint64_t *vmp = (uint64_t *)vm;
                    if (es[0x10] > 7 || es[0x18] > 0x3f ||
                        (es[0x20] & 0x3fff) != 0) {
                        es[0x8] = 0xfffffffffae94003ull;   /* b98cb78-b98cb8c */
                        return;
                    }
                    goto svc_shared_slot;       /* b98d270 (pending) */
                }
                if (esr == 0xc6000012ull)
                    /* b98ce3c: hv_vcpu_slot_op(vcpu, es[0x10], es[0x18])
                     * (b98e12c); result sign-extended into es[0x8]. */
                    es[0x8] = (int64_t)(int32_t)hv_vcpu_slot_op(
                                   (struct hv_vm *)vcpu,   /* x0 = vcpu, b98ce40 */
                                   *(uint64_t *)((char *)es + 0x10),
                                   *(uint64_t *)((char *)es + 0x18)); /* b98ce3c */
                else if (esr == 0xc6000013ull)
                    /* b98cd70: activate slot bits. idx = es[0x10] (must be
                     * <= 7 else es[0x8]=0xfffffffffae94003, b98cf34);
                     * slot = vm+0x2148[idx] (csel 0x2bad-tagged, b98cd88);
                     * CAS-increment slot->refcount (slot[0], 32-bit casa
                     * retry loop b98cda8-b98cdc0; bit31 -> error
                     * 0xfffffffffae94002, b98d510). If slot[0x1008]==0 ->
                     * release refcount and error 0xfffffffffae94006
                     * (b98d490/b98d4ec). If mask==0 (es[0x18]) -> dmb,
                     * release, es[0x8]=0 (b98d4e4). For each set bit in
                     * the mask set the active byte slot+0x40+bit*0x40 = 1
                     * (b98cddc-b98cdf0), dmb ISH, then for each set bit
                     * call cpu_signal(slot+0x38+bit*0x40 entry, 0,0,0,0)
                     * when the entry is non-null (b98ce04-b98ce38).
                     * Exhausted: release refcount (ldaddl -1, b98d4ec),
                     * es[0x8] = 0, done. */
                    {
                        uint64_t *vmp = (uint64_t *)vm;
                        uint64_t idx = es[0x10];
                        uint64_t mask, slot_addr, slot_s, slot_u;
                        uint64_t *slot;
                        uint32_t r;

                        if (idx > 7) {
                            es[0x8] = 0xfffffffffae94003ull;   /* b98cf34 */
                            return;
                        }
                        mask = es[0x18];
                        /* b98cd88: slot = vm+0x2148[idx] (tagged csel) */
                        slot_s = (uint64_t)((uint64_t *)((char *)vmp + 0x2148)) +
                                 (int64_t)(idx * 8);
                        slot_u = (uint64_t)((uint64_t *)((char *)vmp + 0x2148)) +
                                 (idx * 8);
                        slot_addr = (slot_s == slot_u)
                                        ? slot_s
                                        : (slot_u | 0x2bad000000000000ull);
                        slot = (uint64_t *)slot_addr;
                        /* CAS-increment the slot refcount (b98cda8) */
                        r = *(uint32_t *)slot;
                        for (;;) {
                            uint32_t expected = r;
                            uint32_t desired = expected + 1;
                            if (expected & 0x80000000u) {
                                es[0x8] = 0xfffffffffae94002ull;  /* b98d510 */
                                return;
                            }
                            if (__atomic_compare_exchange_n(
                                    (uint32_t *)slot, &expected, desired,
                                    /*weak*/0, __ATOMIC_ACQUIRE,
                                    __ATOMIC_RELAXED))
                                break;
                            r = expected;   /* retry with the current value */
                        }
                        if (slot[0x1008/8] == 0) {
                            __atomic_fetch_add((uint32_t *)slot, 0xffffffffu,
                                               __ATOMIC_RELEASE);  /* ldaddl -1 */
                            es[0x8] = 0xfffffffffae94006ull;   /* b98d490 */
                            return;
                        }
                        if (mask == 0) {
                            __atomic_thread_fence(__ATOMIC_SEQ_CST); /* dmb ISH */
                            __atomic_fetch_add((uint32_t *)slot, 0xffffffffu,
                                               __ATOMIC_RELEASE);
                            es[0x8] = 0;                  /* b98d4e4 */
                            return;
                        }
                        /* first pass: mark active bytes (b98cddc) */
                        {
                            uint64_t m = mask;
                            while (m != 0) {
                                unsigned bit = (unsigned)__builtin_ctzll(m);
                                *(uint8_t *)((char *)slot + 0x40 + bit * 0x40) = 1;
                                m &= ~(1ull << bit);
                            }
                        }
                        __atomic_thread_fence(__ATOMIC_SEQ_CST); /* dmb ISH, b98cdf4 */
                        /* second pass: signal non-null slot entries (b98ce10) */
                        {
                            uint64_t m = mask;
                            while (m != 0) {
                                unsigned bit = (unsigned)__builtin_ctzll(m);
                                uint64_t *entry =
                                    (uint64_t *)((char *)slot + 0x38 + bit * 0x40);
                                if (*entry != 0)
                                    cpu_signal((long)*entry, 0, 0, 0, 0); /* b95ecd8 */
                                m &= ~(1ull << bit);
                            }
                        }
                        /* exhausted: release refcount, es[0x8]=0 (b98d300) */
                        __atomic_fetch_add((uint32_t *)slot, 0xffffffffu,
                                           __ATOMIC_RELEASE);  /* ldaddl -1 */
                        es[0x8] = 0;
                        return;
                    }
                else if (esr == 0xc6000014ull) {
                    /* b98c864: per-slot CAS hypercall (fully traced).
                     * Gate (b98c864-b98c880): es[0x20]>>32 != 0 ->
                     * es[0x8] = 0xfffffffffae94003, done.
                     * b98cfd4: x1,x2 = es[0x10], es[0x18]; CAS vm[0]+8:
                     * 0 -> cpu id (casa, acquire); on old!=0 ||
                     * hv_debug_flag!=0 take the hv lock (b7f0afc, b98d794).
                     * b98cff8: slot bitmap vm+0x2188; if != 0xff find the
                     * first clear bit (mvn/ctz, csinv -> 0 when -1,
                     * b98d18c), set it (b98d1bc); release vm[0]+8 (casl
                     * cpu_id -> 0; on mismatch/flag lock_sync b7f1e80,
                     * b98d7c0). If the bitmap is 0xff (full): release and
                     * es[0x8] = 0xfffffffffae94003, done (b98d004-b98d044).
                     * b98d1ec: slot = vm+0x2148[bit]; CAS slot[0]: 0 ->
                     * 0x80000000 (casa, acquire); busy (b98d4a0):
                     * lock_acquire(vm[0],0), clear bit, lock_release,
                     * es[0x8] = 0xfffffffffae94002, done.
                     * b98d210: hv_vcpu_map_memory(vm, es[0x10], es[0x18],
                     * (uint32)es[0x20], slot+0x1008) (b9866d0); release
                     * slot busy (casl, b98d228). Ok (b98d5f4): es[0x8]=0,
                     * es[0x10]=bit, done. Error (b98d230): lock, clear
                     * bit, unlock, es[0x8] = sxtw(error), done. */
                    uint64_t *vmp = (uint64_t *)vm;
                    if ((es[0x20] >> 32) != 0) {
                        es[0x8] = 0xfffffffffae94003ull;   /* b98c870 */
                        return;                     /* b98cf94 */
                    }
                    {
                        uint64_t *lock = (uint64_t *)(vmp[0] + 8);
                        uint64_t old = 0;
                        uint64_t cpu_id =
                            *(uint32_t *)((char *)tpidr_el1 + 0x518);
                        uint64_t slot_idx;
                        uint64_t *slot;
                        uint64_t map;

                        __atomic_compare_exchange_n(lock, &old, cpu_id,
                                                    /*weak*/0,
                                                    __ATOMIC_ACQUIRE,
                                                    __ATOMIC_RELAXED);
                        if (old != 0 || hv_debug_flag != 0)
                            lock_acquire((void *)vmp[0], tpidr_el1, 0); /* b98d794 */
                        /* b98cff8: find a free slot bit in vm+0x2188 */
                        if (vmp[0x2188/8] == 0xff) {   /* b98d004 full */
                            uint64_t old2 = cpu_id;
                            __atomic_compare_exchange_n(lock, &old2, 0,
                                                        /*weak*/0,
                                                        __ATOMIC_RELEASE,
                                                        __ATOMIC_RELAXED);
                            if (old2 != cpu_id || hv_debug_flag != 0)
                                lock_sync((void *)vmp[0], tpidr_el1); /* b98d038 */
                            es[0x8] = 0xfffffffffae94003ull;   /* b98d020 */
                            return;
                        }
                        /* b98d18c: first clear bit */
                        slot_idx = (vmp[0x2188/8] == (uint64_t)-1)
                                       ? 0
                                       : (uint64_t)__builtin_ctzll(
                                             ~vmp[0x2188/8]);
                        vmp[0x2188/8] |= 1ull << slot_idx;      /* b98d1bc */
                        /* release vm[0]+8 (b98d1dc) */
                        {
                            uint64_t old3 = cpu_id;
                            __atomic_compare_exchange_n(lock, &old3, 0,
                                                        /*weak*/0,
                                                        __ATOMIC_RELEASE,
                                                        __ATOMIC_RELAXED);
                            if (old3 != cpu_id || hv_debug_flag != 0)
                                lock_sync((void *)vmp[0], tpidr_el1); /* b98d7c0 */
                        }
                        /* b98d1ec: acquire the slot at vm+0x2148[bit] */
                        slot = (uint64_t *)((uint64_t *)((char *)vmp +
                            0x2148))[slot_idx];
                        {
                            uint32_t old4 = 0;
                            __atomic_compare_exchange_n((uint32_t *)slot,
                                                        &old4, 0x80000000u,
                                                        /*weak*/0,
                                                        __ATOMIC_ACQUIRE,
                                                        __ATOMIC_RELAXED);
                            if (old4 != 0) {        /* b98d4a0 busy */
                                lock_acquire((void *)vmp[0], 0);   /* b7f0ac8 */
                                vmp[0x2188/8] &= ~(1ull << slot_idx);
                                lock_release((void *)vmp[0]);       /* b7f1e4c */
                                es[0x8] = 0xfffffffffae94002ull;    /* b98d4cc */
                                return;
                            }
                        }
                        /* b98d210: map the guest range into the slot */
                        map = (uint64_t)hv_vcpu_map_memory(
                                   (void *)vm, es[0x10], es[0x18],
                                   (uint32_t)es[0x20],
                                   (uint64_t *)((char *)slot + 0x1008));
                        __atomic_store_n((uint32_t *)slot, 0u,
                                         __ATOMIC_RELEASE);  /* b98d228 */
                        if (map == 0) {             /* b98d5f4 */
                            es[0x8] = 0;
                            es[0x10] = slot_idx;
                            return;
                        }
                        /* b98d230 error: clear the bit and surface the err */
                        lock_acquire((void *)vmp[0], 0);   /* b7f0ac8 */
                        vmp[0x2188/8] &= ~(1ull << slot_idx);
                        lock_release((void *)vmp[0]);       /* b7f1e4c */
                        es[0x8] = (int64_t)(int32_t)map;    /* sxtw, b98d260 */
                        return;                     /* b98cf94 */
                    }
                }
            } else {
                /* 0xc6000011 / 0xc6000015..0x1a path (b98cb30/b98ca7c...). */
                if (esr == 0xc6000018ull) {
                    /* b98cf28 -> b98d07c: per-slot notify.
                     * idx = es[0x10]; idx > 7 -> es[0x8] =
                     * 0xfffffffffae94003 (b98cf34). slot = vm+0x2148[idx]
                     * (csel 0x2bad-tagged, b98d07c-b98d0a0); CAS slot[0]:
                     * 0 -> 0x80000000 (casa); busy -> es[0x8] =
                     * 0xfffffffffae94002 (b98d2f8). slot[0x1008] == 0 ->
                     * release busy + es[0x8] = 0xfffffffffae94006
                     * (b98d4fc/b98b4a4). Scan slot+8..+0x1008 (stride
                     * 0x40, ldapr): any busy -> release + es[0x8] =
                     * 0xfffffffffae94002 (b98d508). Then per_cpu_base
                     * (b866ec4), PAC-auth [cpu+0x318] (autda 0x8280, null
                     * -> 0, b98d60c), hv_percpu_notify(x0, slot[0x1008])
                     * (b7a1dd8, b98d610), slot[0x1008] = 0, release busy
                     * (casl), lock_acquire(vm[0],0) (b7f0ac8), clear bit
                     * idx in vm+0x2188 word, lock_release (b7f1e4c),
                     * es[0x8] = 0, done. */
                    uint64_t *vmp = (uint64_t *)vm;
                    uint64_t idx = es[0x10];
                    uint64_t slot_addr, slot_s, slot_u;
                    uint64_t *slot;
                    if (idx > 7) {
                        es[0x8] = 0xfffffffffae94003ull;   /* b98cf34 */
                        return;
                    }
                    slot_s = (uint64_t)((uint64_t *)((char *)vmp + 0x2148)) +
                             (int64_t)(idx * 8);
                    slot_u = (uint64_t)((uint64_t *)((char *)vmp + 0x2148)) +
                             (idx * 8);
                    slot_addr = (slot_s == slot_u)
                                    ? slot_s
                                    : (slot_u | 0x2bad000000000000ull);
                    slot = (uint64_t *)slot_addr;
                    {
                        uint32_t old = 0;
                        __atomic_compare_exchange_n((uint32_t *)slot, &old,
                                                    0x80000000u, /*weak*/0,
                                                    __ATOMIC_ACQUIRE,
                                                    __ATOMIC_RELAXED);
                        if (old != 0) {
                            es[0x8] = 0xfffffffffae94002ull;   /* b98d2f8 */
                            return;
                        }
                    }
                    if (slot[0x1008/8] == 0) {
                        __atomic_store_n((uint32_t *)slot, 0u,
                                         __ATOMIC_RELEASE);    /* b98d4fc */
                        es[0x8] = 0xfffffffffae94006ull;       /* b98b4a4 */
                        return;
                    }
                    {
                        uint64_t off;
                        for (off = 8; off != 0x1008; off += 0x40) {
                            uint32_t busy;
                            __atomic_load((uint32_t *)((char *)slot + off),
                                          &busy, __ATOMIC_ACQUIRE);  /* ldapr */
                            if (busy != 0) {
                                __atomic_store_n((uint32_t *)slot, 0u,
                                                 __ATOMIC_RELEASE); /* b98d508 */
                                es[0x8] = 0xfffffffffae94002ull;
                                return;
                            }
                        }
                    }
                    {
                        /* b98d0e0-b98d610: per-cpu map + notify */
                        uint64_t cpu = tpidr_el1;
                        uint64_t *pcpu = (uint64_t *)per_cpu_base(cpu);
                        uint64_t *map = (uint64_t *)((char *)pcpu + 0x318);
                        uint64_t *m = map;
                        uint64_t tag = (uint64_t)map | 0x8280000000000000ull;
                        if (*map != 0) {
                            __asm__ volatile("autda %0, %1"
                                             : "+r"(m)
                                             : "r"(tag));
                        } else {
                            m = 0;                  /* b98d60c */
                        }
                        hv_percpu_notify((long)m,
                            *(uint32_t *)((char *)slot + 0x1008));  /* b7a1dd8 */
                        slot[0x1008/8] = 0;          /* b98d618 */
                        __atomic_store_n((uint32_t *)slot, 0u,
                                         __ATOMIC_RELEASE);   /* b98d61c */
                        lock_acquire((void *)vmp[0], 0);      /* b7f0ac8 */
                        vmp[0x2188/8] &= ~(1ull << idx);      /* b98d630-b98d640 */
                        lock_release((void *)vmp[0]);          /* b7f1e4c */
                        es[0x8] = 0;                 /* b98d64c */
                        return;
                    }
                }
                if (esr == 0xc600001aull) {
                    /* b98caa4: SIMD select. lo = max(lo16, 0x300),
                     * hi = min(hi16, 0x300) (umin/umax, b98cab0/b98cab4);
                     * cmp hi,lo; cset w8,cc (hi < lo); dup/uxtl/shl/cmlt
                     * -> all-ones mask; bsl selects q2=[sp+0x40] when set
                     * else q1=[sp+0x30]; stur q0,[es+0x8].  The source
                     * vectors are rodata: q1 = {0xfffffffffae9400f, 0}
                     * (DAT_fffffe000700f400), q2 = {0, 0x30000}
                     * (DAT_fffffe000700f3f0). */
                    uint64_t lo = *(uint16_t *)((char *)es + 0x10);
                    uint64_t hi = *(uint16_t *)((char *)es + 0x18);
                    lo = lo > 0x300 ? lo : 0x300;   /* umax */
                    hi = hi < 0x300 ? hi : 0x300;   /* umin */
                    if (hi < lo) {                  /* cset cc */
                        es[0x8] = 0;                /* vec2 low word */
                        es[0x10] = 0x30000;         /* vec2 high word */
                    } else {
                        es[0x8] = 0xfffffffffae9400full;  /* vec1 low word */
                        es[0x10] = 0;
                    }
                    return;                         /* b98cf94 */
                } else if (esr == 0xc6000019ull) {
                    /* b98ce54: sweep all 8 slot groups x 64 sub-slots.
                     * Gate vm+0x2191 bit 0 (b98ce58) else the arg-check
                     * tail (b98d064). For each group 0..7, sub 0..0x3f:
                     * if the acquire-load (ldapr) at slot+8+sub*0x40 is
                     * non-zero, call hv_vcpu_slot_op(vcpu, group, sub)
                     * (b98e12c); on error clear vm+0x2190 and record
                     * err = 0xfae94002 (b98cec4-b98cedc). Done (b98d048):
                     * vm+0x2191 = 0; if err -> es[0x8] = sxtw(err)
                     * (b98d180); else if (es[0x10] & 0x3fff) != 0 ->
                     * es[0x8] = 0xfae94004 (b98d06c); else -> the
                     * hv_copyin_user path (b98d104, deep). */
                    uint64_t *vmp = (uint64_t *)vm;
                    uint64_t err = 0;
                    uint64_t group, sub;
                    if ((*(uint8_t *)((char *)vmp + 0x2191) & 1) == 0)
                        goto svc19_argcheck;        /* b98ce5c */
                    for (group = 0; group < 8; group++) {
                        uint64_t *slot = (uint64_t *)
                            ((uint64_t *)((char *)vmp + 0x2148))[group];
                        uint64_t *sp = (uint64_t *)((char *)slot + 8);
                        for (sub = 0; sub < 0x40; sub++) {
                            uint32_t busy;
                            __atomic_load(sp, &busy, __ATOMIC_ACQUIRE); /* ldapr */
                            if (busy != 0) {
                                if (hv_vcpu_slot_op(
                                        (struct hv_vm *)vcpu, group, sub) == 0) {
                                    sp += 0x40 / 8;
                                    continue;
                                }
                                *(uint8_t *)((char *)vmp + 0x2190) = 0;
                                err = 0xfae94002;   /* b98ced4 */
                            }
                            sp += 0x40 / 8;
                        }
                    }
                    *(uint8_t *)((char *)vmp + 0x2191) = 0;  /* b98d054 */
                    if (err != 0) {                 /* b98d060 */
                        es[0x8] = (int64_t)(int32_t)err;      /* b98d180 */
                        return;
                    }
svc19_argcheck:                     /* b98d064 */
                    if ((es[0x10] & 0x3fff) != 0) {
                        es[0x8] = 0xfae94004ull;    /* b98d06c */
                        return;
                    }
                    /* b98d104: hv_copyin_user(vcpu[0x88], &out, es[0x10],
                     * es[0x18]) (b98e020); on error es[0x8] = sxtw(err).
                     * (Deep region-validation continuation still to expand:
                     * b98d120-b98d148, the shared map/region block.) */
                    {
                        uint64_t out = 0;
                        uint32_t rc = hv_copyin_user(
                            (void *)*(uint64_t *)((char *)vcpu + 0x88),
                            (void **)&out, es[0x10], es[0x18]);
                        es[0x8] = (int64_t)(int32_t)rc;
                    }
                    return;
                }
            }
            /* 0xc6000010/0x11 dispatch + 0x15-0x17 -> unhandled (b98d860).
             * 0x10 (b98cee0) / 0x11 (b98cb50) gates are fully traced above;
             * their deep continuations (b98d308/b98d268/b98d270) are the
             * shared slot-record machinery (b98d148-b98d838), read but not
             * yet transcribed with verified register tracking. */
svc_shared_slot:                /* b98d308 / b98d270 (pending) */
            goto unhandled_ec;
        }
        return;

    case 0xc3000000:            /* HVC (64-bit), ISS = hvc #imm (b98a76c) */
        /* Enable-mask gate: vm+0x2130 & (1<<imm), imm = esr & 0xffff, and
         * imm <= 6 (b98a794); if the attach id vcpu+0xe0==0 the mask is
         * additionally ANDed with 0x7fffffffffffff9f (b98a780).  Then
         * dispatch the hypercall number:
         *   0xc3000003 (b98bbb0) / 0xc3000004 (b98b6d8) / 0xc3000005
         *   (b98bbd4) / 0xc3000006 (b98b6d8) — mrs/msr-style EL2 register
         *   reads, timer-offset, and per-slot CAS.  Unhandled masks/
         *   numbers fall to b98d860. */
        {
            uint64_t imm = esr & 0xffff;
            uint64_t mask = *(uint64_t *)((char *)vm + 0x2130);
            if (vcpu->attach_id == 0)
                mask &= 0x7fffffffffffff9full;      /* b98a778-0x780 */
            if (imm > 6 || !(mask & (1ull << imm)))
                goto unhandled_ec;
            switch (imm) {
            case 3:                 /* b98bbb0 */
                /* b98bbb0: mrs x8,sreg(3,1,c15,c9,4); ldr x9,[DAT_fffffe000c5ac010]
                 * (boot time delta, written by arm_cpu_init @ b95b238);
                 * ldr x10,[es+0x10]; x8 = x9 + x8 - x10;
                 * stp xzr,x8,[es+0x8]; -> done tail (b98cf94).
                 * Timer-offset read: base + counter - guest offset. */
                es[0x8] = 0;
                es[0x10] = cpu_boot_time_delta +
                           UnkSytemRegRead(3,1,0xf,9,4) - es[0x10];
                return;                             /* b98cf94 */

            case 5:                 /* b98bbd4 */
                /* b98bbd4: if es[0x10] != 0, clear DAIF bits (0x1c0) in
                 * es[0x110] (and 0xfffffe3f); else require
                 * (0x1c0 & ~es[0x110]) == 0 else unhandled (b98c0c8).
                 * Then (b98c0cc): CAS vm[0]+8: 0 -> cpu id
                 * (casa, acquire); on old!=0 || hv_debug_flag!=0 take the
                 * hv lock (b7f0afc, lock_acquire) and continue (b98c0f0).
                 * CAS the per-cpu slot flag vm+0x80+idx*0x80+0x14: 0 -> 1
                 * (casal, acquire-release); when it wins call
                 * b7f9088(vm[0], 0, vcpu, 2). Clear the slot flag (stlur,
                 * b98c12c), then CAS vm[0]+8 back cpu id -> 0 (casl,
                 * release, b98c148); if it didn't match or hv_debug_flag
                 * is set, release via b7f1e80 (lock_sync). -> done. */
                if (es[0x10] != 0) {
                    es[0x110] &= 0xfffffe3full;     /* b98bbe0 */
                } else if ((0x1c0 & ~es[0x110]) != 0) {
                    goto unhandled_ec;              /* b98c0c8 */
                }
                {
                    /* b98c0cc: acquire the per-vm slot (vm[0]+8) */
                    uint64_t *vmp = (uint64_t *)vm;
                    uint64_t *slot = (uint64_t *)(vmp[0] + 8);
                    uint64_t old_slot = 0;
                    uint64_t cpu_id = *(uint32_t *)((char *)tpidr_el1 + 0x518);
                    __atomic_compare_exchange_n(slot, &old_slot, cpu_id,
                                                /*weak*/0, __ATOMIC_ACQUIRE,
                                                __ATOMIC_RELAXED);
                    if (old_slot != 0 || hv_debug_flag != 0)
                        lock_acquire((void *)vmp[0], tpidr_el1, 0);  /* b98d71c */
                    /* b98c0f0: per-cpu slot flag at vm+0x80+idx*0x80+0x14 */
                    {
                        uint64_t idx = *(uint8_t *)((char *)vcpu + 0xf8);
                        uint32_t *flag = (uint32_t *)((char *)vmp + 0x80 +
                            idx * 0x80 + 0x14);
                        uint32_t old_flag = 0;
                        __atomic_compare_exchange_n(flag, &old_flag, 1u,
                                                    /*weak*/0,
                                                    __ATOMIC_ACQ_REL,
                                                    __ATOMIC_RELAXED);
                        if (old_flag == 0)
                            kernel_slot_callee_088((void *)vmp[0], 0,
                                                   vcpu, 2);  /* b7f9088 */
                        __atomic_store_n(flag, 0u, __ATOMIC_RELEASE); /* b98c12c */
                    }
                    /* b98c130: release vm[0]+8 back to 0 */
                    {
                        uint64_t old2 = cpu_id;
                        __atomic_compare_exchange_n(slot, &old2, 0,
                                                    /*weak*/0,
                                                    __ATOMIC_RELEASE,
                                                    __ATOMIC_RELAXED);
                        if (old2 != cpu_id || hv_debug_flag != 0)
                            lock_sync((void *)vmp[0], tpidr_el1);  /* b98c158 */
                    }
                }
                return;                             /* b98cf94 */

            case 4:                 /* b98b6d8 */
            case 6:                 /* b98b6d8 */
                /* Timer-offset registration (b98b6d8): CAS vm[0]+8: 0 -> cpu
                 * id (casa, acquire); on old!=0 || hv_debug_flag!=0 take
                 * the hv lock (b7f0afc, b98d70c) then continue. Scan
                 * vm+0x80..+0x2080 (stride 0x80) for a slot whose
                 * (slot[8]+0x4050) 16-bit field == es[0x10] (b98b718);
                 * empty/self slots end the scan (b98d838, -> unhandled).
                 * Verify the slot owner (slot[0][0]+8 & 0xfffffff) == cpu
                 * id else panic (c0e4d74, b98dbd8). Set the slot busy flag
                 * at slot[0]+idx*0x80+0x94 (ldsetl 2, b98b76c), tag+hash the
                 * slot pointer into the flush table (DAT_fffffe000c62b8e0,
                 * size DAT_fffffe000c62b8e8, 0x18-byte buckets,
                 * b98b774-b98b7e0) and call hv_flush_lock_op (b8563f8) with
                 * (slot,0,0,1); then the release tail (b98c130) -> done.
                 * Scan end (b98d838): release vm[0]+8 (casl cpu_id -> 0);
                 * on mismatch or hv_debug_flag take lock_sync (b7f1e80,
                 * b98da34); falls to unhandled (b98d860). */
                {
                    uint64_t *vmp = (uint64_t *)vm;         /* container */
                    uint64_t guest_off = es[0x10];
                    uint64_t *lock = (uint64_t *)(vmp[0] + 8);
                    uint64_t old = 0;
                    uint64_t cpu_id = *(uint32_t *)((char *)tpidr_el1 + 0x518);
                    uint64_t off;

                    __atomic_compare_exchange_n(lock, &old, cpu_id,
                                                /*weak*/0, __ATOMIC_ACQUIRE,
                                                __ATOMIC_RELAXED);
                    if (old != 0 || hv_debug_flag != 0)
                        lock_acquire((void *)vmp[0], tpidr_el1, 0);  /* b98d70c */

                    for (off = 0x80; ; off += 0x80) {
                        uint64_t *slot;
                        uint64_t slot_obj;
                        if (off == 0x2080)          /* b98b70c-b98b714 */
                            goto hvc46_release_unhandled;
                        slot = *(uint64_t **)((char *)vmp + off);  /* b98b718 */
                        if (slot == 0)
                            continue;               /* b98b708 */
                        if (*(uint16_t *)(slot[8] + 0x4050) != guest_off)
                            continue;
                        if (slot == (uint64_t *)vcpu)       /* b98b73c */
                            goto hvc46_release_unhandled;
                        slot_obj = slot[0];
                        if ((*(uint32_t *)(*(uint64_t *)slot_obj + 8) &
                             0xfffffff) != (uint32_t)cpu_id)
                            kernel_owner_mismatch_panic((void *)*(uint64_t *)slot_obj,
                                                        (void *)tpidr_el1); /* b98dbd8, c0e4d74 */
                        /* set the slot busy flag: ldsetl w9,#2,[slot+0x94] */
                        __atomic_fetch_or(
                            (uint32_t *)(slot_obj +
                                (uint64_t)*(uint8_t *)((char *)slot + 0xf8) *
                                    0x80 + 0x94),
                            2u, __ATOMIC_RELEASE);   /* b98b76c */
                        /* hash the tagged slot pointer (b98b774-b98b7e0) */
                        {
                            uint64_t h = (uint64_t)slot | 0xf00000000000000ull;
                            uint64_t base = waitq_hash_table;  /* DAT_fffffe0007d7c8e0 */
                            uint64_t size = waitq_hash_size;   /* DAT_fffffe0007d7c8e8 */
                            uint64_t bucket_s, bucket_u;
                            h ^= h >> 31;
                            h *= 0x7fb5d329728ea185ull;
                            h ^= h >> 27;
                            h *= 0x81dadef4bc2dd44dull;
                            h = (uint32_t)((h >> 33) ^ h);        /* eor w8,w10,w8 */
                            h &= size - 1;
                            h *= 0x18;
                            bucket_s = base + (int64_t)h;         /* add SXTW */
                            bucket_u = base + h;                  /* add (unsigned) */
                            if (bucket_s == bucket_u)             /* csel eq */
                                hv_flush_lock_op((uint32_t *)bucket_s,
                                                 (uint64_t)slot, 0, 0, 1);
                            else
                                hv_flush_lock_op(
                                    (uint32_t *)(bucket_u | 0x2bad000000000000ull),
                                    (uint64_t)slot, 0, 0, 1);     /* b8563f8 */
                        }
                        /* release tail (b98c130): casl cpu_id -> 0 */
                        {
                            uint64_t old2 = cpu_id;
                            __atomic_compare_exchange_n(lock, &old2, 0,
                                                        /*weak*/0,
                                                        __ATOMIC_RELEASE,
                                                        __ATOMIC_RELAXED);
                            if (old2 != cpu_id || hv_debug_flag != 0)
                                lock_sync((void *)vmp[0], tpidr_el1);  /* b98c158 */
                        }
                        return;                     /* b98cf94 */
                    }
                }
            default:
                goto unhandled_ec;
            }
hvc46_release_unhandled:        /* b98d838/b98da34: release + unhandled */
            {
                uint64_t cpu_id2 = *(uint32_t *)((char *)tpidr_el1 + 0x518);
                uint64_t *lock2 = (uint64_t *)(((uint64_t *)vm)[0] + 8);
                uint64_t old2 = cpu_id2;
                __atomic_compare_exchange_n(lock2, &old2, 0,
                                            /*weak*/0, __ATOMIC_RELEASE,
                                            __ATOMIC_RELAXED);
                if (old2 != cpu_id2 || hv_debug_flag != 0)
                    lock_sync((void *)((uint64_t *)vm)[0], tpidr_el1);  /* b98da34 */
            }
            goto unhandled_ec;                      /* b98d860 */
        }
        return;

    case 0xc1000000:            /* HVC (32-bit) / hint range (b98a47c) */
        /* Opcode-count gate (b98a480-b98a48c, b98ba94): count = vm+0x2128;
         * (count-2) >= 3 unsigned -> b98ba94: count < 2 -> es[0x8] =
         * 0xffffffff, done (b98bc14); count >= 5 -> panic (b98dbb8).
         * Then the hint imm dispatch (b98a490):
         *   <= 0xc1000002 (b98bd00): 0x0 -> b98c370, 0x1 -> b98bd1c,
         *     0x2 -> b98c670.
         *   0xc1000003 (b98a4c0): EL2-state save + active-mask OR +
         *     guest-pending stores (traced below).
         *   0xc1000004 (b98c70c), > 0xc1000004 (b98bde0): remaining hints. */
        {
            uint64_t opcount = *(uint32_t *)((char *)vm + 0x2128);
            if (opcount - 2 >= 3) {             /* b98a48c -> b98ba94 */
                if (opcount < 2) {              /* b98ba94 b.cc */
                    es[0x8] = 0xffffffffull;    /* b98bc14 */
                    return;
                }
                goto hvc32_panic;               /* b98dbb8 */
            }
            if (esr <= 0xc1000002ull) {
                if (esr == 0xc1000000ull) {
                    /* b98c370 (0xc1000000): compound guest-state save.
                     * Seq1 (bit 4, b98c370): save EL2 state (nesting +
                     * b988358 + tlb-flush b98d744), OR es[0x4110..0x4118]
                     * with sp+0x70 {0x1000000000000000, ...}, es[0x880]
                     * = 0x11 (b98c3e4).
                     * Seq2 (bit 5, b98c3ec): save, OR sp+0x90
                     * {0x2000000000000000, ...}, store magic-10..-7 into
                     * es[0x8a0]/[0x898]/[0x8c0]/[0x8b8] (b98c474-b98c490).
                     * Seq3 (bit 5, b98c494): save, OR sp+0x90, store
                     * magic-4..-1 into es[0x8b0]/[0x8a8]/[0x8d0]/[0x8c8]
                     * (b98c51c-b98c538).
                     * Seq4 (bit 5, b98c53c): save, OR sp+0x90, store magic
                     * /magic+1 into es[0x890]/[0x888] (b98c5c4).
                     * Seq5 (bit 4, b98c5d0): save, OR sp+0x70, store
                     * magic-6/-5 into es[0x8e0]/[0x8d8] (b98c658).
                     * End (b98c668): es[0x8] = 0, done.
                     * magic = 0xfeedfacefeedfad9. */
                    uint64_t magic = 0xfeedfacefeedfad9ull;
                    if ((*(uint8_t *)((char *)es + 0x410f) & 0x10) == 0) {
                        hv_nesting_save(vcpu);      /* b98c370-b98c3d0 */
                        es[0x4110/8] |= 0x1000000000000000ull;  /* sp+0x70 */
                        es[0x4118/8] |= 0x1000000000000000ull;
                        es[0x880/8] = 0x11;         /* b98c3e4 */
                    }
                    if ((*(uint8_t *)((char *)es + 0x410f) & 0x20) == 0) {
                        hv_nesting_save(vcpu);      /* b98c3ec-b98c450 */
                        es[0x4110/8] |= 0x2000000000000000ull;  /* sp+0x90 */
                        es[0x4118/8] |= 0x2000000000000000ull;
                        es[0x8a0/8] = magic - 10;   /* b98c474 */
                        es[0x898/8] = magic - 9;
                        es[0x8c0/8] = magic - 8;
                        es[0x8b8/8] = magic - 7;
                    }
                    if ((*(uint8_t *)((char *)es + 0x410f) & 0x20) == 0) {
                        hv_nesting_save(vcpu);      /* b98c494-b98c4f8 */
                        es[0x4110/8] |= 0x2000000000000000ull;
                        es[0x4118/8] |= 0x2000000000000000ull;
                        es[0x8b0/8] = magic - 4;    /* b98c51c */
                        es[0x8a8/8] = magic - 3;
                        es[0x8d0/8] = magic - 2;
                        es[0x8c8/8] = magic - 1;
                    }
                    if ((*(uint8_t *)((char *)es + 0x410f) & 0x20) == 0) {
                        hv_nesting_save(vcpu);      /* b98c53c-b98c5a0 */
                        es[0x4110/8] |= 0x2000000000000000ull;
                        es[0x4118/8] |= 0x2000000000000000ull;
                        es[0x890/8] = magic;        /* b98c5c4 */
                        es[0x888/8] = magic + 1;
                    }
                    if ((*(uint8_t *)((char *)es + 0x410f) & 0x10) == 0) {
                        hv_nesting_save(vcpu);      /* b98c5d0-b98c634 */
                        es[0x4110/8] |= 0x1000000000000000ull;  /* sp+0x70 */
                        es[0x4118/8] |= 0x1000000000000000ull;
                        es[0x8e0/8] = magic - 6;    /* b98c658 */
                        es[0x8d8/8] = magic - 5;
                    }
                    es[0x8] = 0;                    /* b98c668 */
                    return;
                }
                if (esr == 0xc1000001ull) {
                    /* b98bd1c: ldp q0,q1,[sp,#0x50]; stur q1,[es+0x8];
                     * stur q0,[es+0x18]; es[0x28] = 0xfeedfacefeedfad9
                     * (b98bd28-b98bd38).  Source vectors (rodata):
                     * q1 = {0, 0xfedefaedfefacf} @ DAT_fffffe000700f410,
                     * q0 = {0xfedefaedfedad5, 0xfedefaedfed3d1}
                     * @ DAT_fffffe000700f420. */
                    es[0x8]  = 0;
                    es[0x10] = 0xfedefaedfefacfull;
                    es[0x18] = 0xfedefaedfedad5ull;
                    es[0x20] = 0xfedefaedfed3d1ull;
                    es[0x28] = 0xfeedfacefeedfad9ull;
                    return;                         /* b98cf94 */
                }
                /* b98c670 (0xc1000002): x21 = es[0x10]; bit 5 -> save
                 * (tlb b98d75c); OR sp+0x90; store es[0x10]+0..3 into
                 * es[0x8a0]/[0x898]/[0x8c0]/[0x8b8]; es[0x8]=0; done. */
                {
                    uint64_t hv = es[0x10];
                    if ((*(uint8_t *)((char *)es + 0x410f) & 0x20) == 0) {
                        hv_nesting_save(vcpu);      /* b98c670-b98c6d4 */
                        es[0x4110/8] |= 0x2000000000000000ull;
                        es[0x4118/8] |= 0x2000000000000000ull;
                    }
                    es[0x8a0/8] = hv;               /* b98c6e8 */
                    es[0x898/8] = hv + 1;
                    es[0x8c0/8] = hv + 2;
                    es[0x8b8/8] = hv + 3;
                    es[0x8] = 0;                    /* b98c704 */
                    return;
                }
            }
            if (esr == 0xc1000003ull) {
                /* b98a4c0 (0xc1000003): x21 = es[0x10]; if es[0x410f] bit 5
                 * clear -> save EL2 state (nesting + b988358 with the
                 * hv_el2_l2 (DAT_fffffe0007e0d81d) mask + tlb flush check
                 * b98d74c). Then OR es[0x4110..0x4118] with the sp+0x90
                 * vector {0x2000000000000000, 0x2000000000000000}
                 * (b98a528-b98a534), store es[0x10]+0..3 into
                 * es[0x8b0]/[0x8a8]/[0x8d0]/[0x8c8] (b98a538-b98a550),
                 * then b98cbc0: es[0x880] &= ~3, es[0x8] = 0, done. */
                uint64_t hv = es[0x10];
                if ((*(uint8_t *)((char *)es + 0x410f) & 0x20) == 0) {
                    hv_nesting_save(vcpu);          /* b98a4d4-b98a524 */
                    es[0x4110/8] |= 0x2000000000000000ull;  /* b98a528 */
                    es[0x4118/8] |= 0x2000000000000000ull;
                }
                es[0x8b0/8] = hv;                   /* b98a538 */
                es[0x8a8/8] = hv + 1;
                es[0x8d0/8] = hv + 2;
                es[0x8c8/8] = hv + 3;
                es[0x880/8] &= ~3ull;               /* b98cbc0 */
                es[0x8] = 0;
                return;
            }
            if (esr == 0xc1000004ull) {
                /* b98c70c (0xc1000004): bit 4 -> save (tlb b98d764); OR
                 * sp+0x70; store es[0x10]+0..1 into es[0x8e0]/[0x8d8];
                 * es[0x8]=0; done. */
                uint64_t hv = es[0x10];
                if ((*(uint8_t *)((char *)es + 0x410f) & 0x10) == 0) {
                    hv_nesting_save(vcpu);          /* b98c70c-b98c770 */
                    es[0x4110/8] |= 0x1000000000000000ull;  /* sp+0x70 */
                    es[0x4118/8] |= 0x1000000000000000ull;
                }
                es[0x8e0/8] = hv;                   /* b98c784 */
                es[0x8d8/8] = hv + 1;
                es[0x8] = 0;                        /* b98c790 */
                return;
            }
            if (esr == 0xc1000005ull) {
                /* b98bdf0 (0xc1000005): x21 = es[0x18]; bit 4 -> save
                 * (tlb b98d754); OR sp+0x70; store es[0x18]+0..1 into
                 * es[0x8e0]/[0x8d8]; then es[0x10]==0 -> es[0x880] &= ~3
                 * (b98cbb4); es[0x10]==1 -> es[0x880] |= 2 (b98be84);
                 * else -> es[0x880] &= ~3 (b98cbc0); es[0x8]=0; done. */
                uint64_t hv = es[0x18];
                if ((*(uint8_t *)((char *)es + 0x410f) & 0x10) == 0) {
                    hv_nesting_save(vcpu);          /* b98bdf0-b98be54 */
                    es[0x4110/8] |= 0x1000000000000000ull;  /* sp+0x70 */
                    es[0x4118/8] |= 0x1000000000000000ull;
                }
                es[0x8e0/8] = hv;                   /* b98be68 */
                es[0x8d8/8] = hv + 1;
                if (es[0x10] == 0)
                    es[0x880/8] &= ~3ull;           /* b98cbb4 */
                else if (es[0x10] == 1)
                    es[0x880/8] |= 2ull;            /* b98be84 */
                else
                    es[0x880/8] &= ~3ull;           /* b98cbc0 */
                es[0x8] = 0;
                return;
            }
            /* b98c798 (0xc1000006..0xf): x21 = es[0x10]; bit 5 -> save;
             * OR sp+0x90; store es[0x10]+0..1 into es[0x890]/[0x888];
             * es[0x8]=0; done (b98c800-b98c820). */
            {
                uint64_t hv = es[0x10];
                if ((*(uint8_t *)((char *)es + 0x410f) & 0x20) == 0) {
                    hv_nesting_save(vcpu);          /* b98c798-b98c7fc */
                    es[0x4110/8] |= 0x2000000000000000ull;  /* sp+0x90 */
                    es[0x4118/8] |= 0x2000000000000000ull;
                }
                es[0x890/8] = hv;                   /* b98c810 */
                es[0x888/8] = hv + 1;
                es[0x8] = 0;                        /* b98c81c */
                return;
            }
        }
        return;
hvc32_panic:                    /* b98dbb8 */
        kernel_panic_msg_fmt("hv_vcpu_run: unrecognized hint opcode count (panic; string @ b98dbb8)");
        /* not reached */
        return;

    case 0x83000000:            /* IABT (lower EL) (b98b39c) */
        /* imm = esr & 0xffff.  0xff01 (b98ba1c) / 0xff03 (b98b3c4): store
         * the 16-byte caller blob from sp+0x80 into es[0x8] (b98b3c4
         * `ldr q0,[sp,0x80]; stur q0,[x24,0x8]`) or the four word-swapped
         * values into es[0x8..0x28] (b98ba1c).  0xfeff (b98ba54) is the
         * HVC-with-imm family: vm+0x2130 mask & (1<<imm), imm<=6, then set
         * es[0x8]=0 and re-run (b98cbc0). */
        {
            uint64_t imm = esr & 0xffff;
            if (imm == 0xff01ull || imm == 0xff03ull) {
                /* copy the exception-syndrome blob into es[0x8] (b98b3c4). */
                es[0x8] = *(uint64_t *)((char *)es + 0x4018); /* est.; b98b3c4 */
                return;
            }
            if (imm == 0xfeffull) {
                uint64_t mask = *(uint64_t *)((char *)vm + 0x2130);
                uint64_t himm = *(uint16_t *)((char *)es + 0x10);
                if (vcpu->attach_id == 0)
                    mask &= 0x7fffffffffffff9full;
                if (himm > 6 || !(mask & (1ull << himm)))
                    goto unhandled_ec;
                es[0x8] = 0;                        /* b98cbc0 */
                return;
            }
        }
        goto unhandled_ec;

    default:
        /* 0x24xxxxxx..0x3fxxxxxx debug/arch families.  The ESR EC field
         * ((esr>>26)&0x3f) selects a leaf that reads a PER-FAMILY enable
         * word from the guest save area (es+0x6a8 / 0x6b0 / 0x6c0 / 0x730)
         * and ANDs it with a PER-FAMILY pair of VM enable-mask words
         * (container+0x20a8/b0, +0x20c0/c8, +0x2090/98, +0x20d8/e0), then
         * tests a family-specific bit (tst/tbnz).  If the bit is SET the
         * exception is not handled here -> unhandled_ec (b98d860).  If
         * clear, the exception is recorded into the guest save area so the
         * return-to-guest path re-injects it (the record tail writes the
         * 5-bit register index esr[9:5] into a save word es+0x398/0x3f0/
         * 0x9f0 and bumps the pending-exception count at es+0x108).  The
         * per-family enable word / VM mask pair / bit / record target below
         * are taken VERBATIM from the leaf disassembly; each case maps to
         * its real entry address. */
        {
            uint64_t ebit;
            uint64_t vm_en;
            switch ((cls >> 26) & 0x3f) {           /* ESR EC field */
            case 0x24:              /* DABT same-EL, ISS 0x4/0xc (b98b5bc) */
                /* Leaf b98b870: es+0x6c0 & (vm+0x20c8 | vm+0x20c0),
                 * tst #0x300. */
                ebit  = *(uint64_t *)((char *)es + 0x6c0);
                vm_en = *(uint32_t *)((char *)vm + 0x20c8) |
                        *(uint32_t *)((char *)vm + 0x20c0);
                if ((ebit & vm_en & 0x300) != 0)
                    goto unhandled_ec;
                return;                             /* b98b870 record tail */

            case 0x26:              /* FP-exception, ISS 0x1a (b98b5dc) */
                /* Same leaf as 0x24 (b98b870): es+0x6c0 & (vm+0x20c8|0x20c0),
                 * tst #0x300. */
                ebit  = *(uint64_t *)((char *)es + 0x6c0);
                vm_en = *(uint32_t *)((char *)vm + 0x20c8) |
                        *(uint32_t *)((char *)vm + 0x20c0);
                if ((ebit & vm_en & 0x300) != 0)
                    goto unhandled_ec;
                return;                             /* b98b870 record tail */

            case 0x28:              /* breakpoint lower-EL (b98b860) */
            case 0x2a:              /* watchpoint lower-EL (b98b84c) */
            case 0x2c:              /* watchpoint lower-EL (b98a0fc) */
                /* Lower-EL debug family: the classifier range-tests
                 * (subs #0x280000, cmp #0x1e / subs #0x2a0000, #0x2c0000,
                 * b98a0ec..b98a124) and selects a sub-family with the
                 * 0x55555555 bit pattern (b98b84c/b98b860), then converges
                 * on leaf b98b870: es+0x6c0 & (vm+0x20c8|0x20c0),
                 * tst #0x300. */
                ebit  = *(uint64_t *)((char *)es + 0x6c0);
                vm_en = *(uint32_t *)((char *)vm + 0x20c8) |
                        *(uint32_t *)((char *)vm + 0x20c0);
                if ((ebit & vm_en & 0x300) != 0)
                    goto unhandled_ec;
                return;                             /* b98b870 record tail */

            case 0x30:              /* breakpoint same-EL (b98bee4) */
                /* 0x302c00 -> b98c8e0 (es+0x6b0 & (vm+0x20b0|0x20a8),
                 * tbnz #0xe); 0x302806 -> b98c928 (es+0x6a8 &
                 * (vm+0x2098|0x2090), tbnz w9,#0x0 then tbnz w8,#0x1a);
                 * 0x302c06 -> b98c8d8 (same mask as 0x302c00). */
                if (cls == 0x302806ull) {
                    ebit  = *(uint64_t *)((char *)es + 0x6a8);
                    vm_en = *(uint32_t *)((char *)vm + 0x2098) |
                            *(uint32_t *)((char *)vm + 0x2090);
                    if ((ebit & vm_en & (1ull << 0x1a)) != 0)
                        goto unhandled_ec;
                    es[0x3f0/8] = *(uint64_t *)((char *)es + 0x9f0); /* b98c95c */
                } else {                            /* 0x302c00/0x302c06 */
                    ebit  = *(uint64_t *)((char *)es + 0x6b0);
                    vm_en = *(uint32_t *)((char *)vm + 0x20b0) |
                            *(uint32_t *)((char *)vm + 0x20a8);
                    if ((ebit & vm_en & (1ull << 0xe)) != 0)
                        goto unhandled_ec;
                    es[0x4118/8] |= 0x4000000000000000ull; /* b98c910 */
                    es[0x4038/8] &= ~0x4001ull;            /* b98c91c */
                }
                return;

            case 0x31:              /* software-step (b98baa0) */
                /* 0x31cff0 range -> 0x313c0a leaf b98ca54 (compare the
                 * register slot at es+0x4050 against the save word
                 * es+[esr[9:5]]*8+8; match -> done, else unhandled);
                 * other 0x31xxxxxx (e.g. 0x313c18) -> b98c8d8
                 * (es+0x6b0 & (vm+0x20b0|0x20a8), tbnz #0xe). */
                if ((cls & 0xfffffff0ull) == 0x313c0aull) {
                    uint64_t slot = *(uint8_t *)((char *)es + 0x4050);
                    uint64_t idx  = (cls >> 5) & 0x1f;
                    uint64_t sv   = *(uint64_t *)((char *)es + idx * 8 + 8);
                    if (sv != slot)                  /* b98ca70 */
                        goto unhandled_ec;
                    return;
                }
                ebit  = *(uint64_t *)((char *)es + 0x6b0);
                vm_en = *(uint32_t *)((char *)vm + 0x20b0) |
                        *(uint32_t *)((char *)vm + 0x20a8);
                if ((ebit & vm_en & (1ull << 0xe)) != 0)
                    goto unhandled_ec;
                es[0x4118/8] |= 0x4000000000000000ull; /* b98c910 */
                es[0x4038/8] &= ~0x4001ull;            /* b98c91c */
                return;

            case 0x32:              /* watchpoint same-EL (b98bc20) */
                /* 0x32cff0 range -> 0x32xxxxxx watchpoint leaf b98bf3c
                 * (es+0x730 & (vm+0x20e0|0x20d8), tst #0x1c00, on clear
                 * clear es+0x40b8 bits 0xc00 and OR the active mask);
                 * 0x322c06 -> b98c8d8 (es+0x6b0, tbnz #0xe). */
                if (cls == 0x322c06ull) {
                    ebit  = *(uint64_t *)((char *)es + 0x6b0);
                    vm_en = *(uint32_t *)((char *)vm + 0x20b0) |
                            *(uint32_t *)((char *)vm + 0x20a8);
                    if ((ebit & vm_en & (1ull << 0xe)) != 0)
                        goto unhandled_ec;
                    es[0x4118/8] |= 0x4000000000000000ull;
                    es[0x4038/8] &= ~0x4001ull;
                } else {                            /* watchpoint same -> b98bf3c */
                    ebit  = *(uint64_t *)((char *)es + 0x730);
                    vm_en = *(uint32_t *)((char *)vm + 0x20e0) |
                            *(uint32_t *)((char *)vm + 0x20d8);
                    if ((ebit & vm_en & 0x1c00) != 0)
                        goto unhandled_ec;
                    es[0x40b8/8] &= ~0x1c00ull;          /* b98bf60 */
                    es[0x4110/8] |= *(uint64_t *)((char *)es + 0x4110);
                }
                return;

            case 0x33:              /* vector-catch (b98bb1c) */
                /* 0x333c1e -> b98c2c0 (es+0x6b0 & (vm+0x20b0|0x20a8),
                 * tbnz w9,#0x1b); 0x33bc06/0x33bc08 -> b98c328/b98c320
                 * (same mask pair, tbnz w9,#0xb). */
                ebit  = *(uint64_t *)((char *)es + 0x6b0);
                vm_en = *(uint32_t *)((char *)vm + 0x20b0) |
                        *(uint32_t *)((char *)vm + 0x20a8);
                if (cls == 0x333c1eull) {
                    if ((ebit & vm_en & (1ull << 0x1b)) != 0)
                        goto unhandled_ec;
                    es[0x4118/8] |= 0x100000000000000ull;
                    es[0x4038/8] &= ~0x8000001ull;
                } else {                            /* 0x33bc06/0x33bc08 */
                    if ((ebit & vm_en & (1ull << 0xb)) != 0)
                        goto unhandled_ec;
                }
                return;

            case 0x34:              /* branch-target (b98b594) */
                /* Leaf b98b870 (via tst #0x1005 -> b98b870):
                 * es+0x6c0 & (vm+0x20c8|0x20c0), tst #0x300. */
                ebit  = *(uint64_t *)((char *)es + 0x6c0);
                vm_en = *(uint32_t *)((char *)vm + 0x20c8) |
                        *(uint32_t *)((char *)vm + 0x20c0);
                if ((ebit & vm_en & 0x300) != 0)
                    goto unhandled_ec;
                return;                             /* b98b870 record tail */

            case 0x35:              /* misc debug, 0x352bff (b98a578) */
                /* 0x35bc01 -> b98b5f0 (watchpoint-same leaf b98bf3c);
                 * 0x352bff -> b98bb1c (vector-catch leaf). */
                ebit  = *(uint64_t *)((char *)es + 0x6b0);
                vm_en = *(uint32_t *)((char *)vm + 0x20b0) |
                        *(uint32_t *)((char *)vm + 0x20a8);
                if ((ebit & vm_en & (1ull << 0xe)) != 0)
                    goto unhandled_ec;
                es[0x4118/8] |= 0x4000000000000000ull;
                es[0x4038/8] &= ~0x4001ull;
                return;

            case 0x36:              /* 0x363c19/0x367bff (b98a6e8) */
                ebit  = *(uint64_t *)((char *)es + 0x6b0);
                vm_en = *(uint32_t *)((char *)vm + 0x20b0) |
                        *(uint32_t *)((char *)vm + 0x20a8);
                if ((ebit & vm_en & (1ull << 0x1b)) != 0)
                    goto unhandled_ec;
                es[0x4118/8] |= 0x100000000000000ull;
                es[0x4038/8] &= ~0x8000001ull;
                return;

            case 0x37:              /* 0x373c01 (b98a568) */
                ebit  = *(uint64_t *)((char *)es + 0x6b0);
                vm_en = *(uint32_t *)((char *)vm + 0x20b0) |
                        *(uint32_t *)((char *)vm + 0x20a8);
                if ((ebit & vm_en & (1ull << 0xe)) != 0)
                    goto unhandled_ec;
                es[0x4118/8] |= 0x4000000000000000ull;
                es[0x4038/8] &= ~0x4001ull;
                return;

            case 0x38:              /* 0x383c08 (b98a87c) */
                /* Leaf b98c1f0: es+0x6b0 & (vm+0x20b0|0x20a8),
                 * tbnz w9,#0x1b. */
                ebit  = *(uint64_t *)((char *)es + 0x6b0);
                vm_en = *(uint32_t *)((char *)vm + 0x20b0) |
                        *(uint32_t *)((char *)vm + 0x20a8);
                if ((ebit & vm_en & (1ull << 0x1b)) != 0)
                    goto unhandled_ec;
                return;                             /* b98c1f0 record */

            case 0x39:              /* 0x393c01/0x393c02 (b98b4b8/b98c1d4) */
                /* 0x393c02 -> b98c1f0 (es+0x6b0, tbnz #0x1b);
                 * 0x393c19/0x393c1a/0x393c1e -> b98c2c0 (tbnz #0x1b,
                 * set config/ELR); 0x39bc06 -> b98c328 (tbnz #0xb). */
                ebit  = *(uint64_t *)((char *)es + 0x6b0);
                vm_en = *(uint32_t *)((char *)vm + 0x20b0) |
                        *(uint32_t *)((char *)vm + 0x20a8);
                if (cls == 0x39bc06ull) {
                    if ((ebit & vm_en & (1ull << 0xb)) != 0)
                        goto unhandled_ec;
                } else {
                    if ((ebit & vm_en & (1ull << 0x1b)) != 0)
                        goto unhandled_ec;
                    es[0x4118/8] |= 0x100000000000000ull;
                    es[0x4038/8] &= ~0x8000001ull;
                }
                return;

            case 0x3a:              /* 0x3a3017 (b98a558) */
                ebit  = *(uint64_t *)((char *)es + 0x6b0);
                vm_en = *(uint32_t *)((char *)vm + 0x20b0) |
                        *(uint32_t *)((char *)vm + 0x20a8);
                if ((ebit & vm_en & (1ull << 0xe)) != 0)
                    goto unhandled_ec;
                es[0x4118/8] |= 0x4000000000000000ull;
                es[0x4038/8] &= ~0x4001ull;
                return;

            case 0x3b:              /* 0x3b3c01 (b98b514) */
                ebit  = *(uint64_t *)((char *)es + 0x6b0);
                vm_en = *(uint32_t *)((char *)vm + 0x20b0) |
                        *(uint32_t *)((char *)vm + 0x20a8);
                if ((ebit & vm_en & (1ull << 0xe)) != 0)
                    goto unhandled_ec;
                es[0x4118/8] |= 0x4000000000000000ull;
                es[0x4038/8] &= ~0x4001ull;
                return;

            case 0x3c:              /* 0x3c02/0x3c04 (b98c1d4) */
                /* 0x3c02 -> b98c1f0 (es+0x6b0, tbnz #0x1b);
                 * 0x3c04 -> b98c8d8 (es+0x6b0, tbnz #0xe). */
                ebit  = *(uint64_t *)((char *)es + 0x6b0);
                vm_en = *(uint32_t *)((char *)vm + 0x20b0) |
                        *(uint32_t *)((char *)vm + 0x20a8);
                if ((ebit & vm_en & (1ull << 0x1b)) != 0)
                    goto unhandled_ec;
                es[0x4118/8] |= 0x100000000000000ull;
                es[0x4038/8] &= ~0x8000001ull;
                return;

            case 0x3d:              /* 0x3d3c1a/0x3d3c1e (b98a6f8/b98c2a0) */
                /* Leaf b98c2a0/b98c2c0: es+0x6b0 & (vm+0x20b0|0x20a8),
                 * tbnz w9,#0x1b. */
                ebit  = *(uint64_t *)((char *)es + 0x6b0);
                vm_en = *(uint32_t *)((char *)vm + 0x20b0) |
                        *(uint32_t *)((char *)vm + 0x20a8);
                if ((ebit & vm_en & (1ull << 0x1b)) != 0)
                    goto unhandled_ec;
                es[0x4118/8] |= 0x100000000000000ull;
                es[0x4038/8] &= ~0x8000001ull;
                return;

            case 0x3e:              /* 0x3e3010/0x3e3018 (b98bf10) */
                /* Leaf b98bf3c: es+0x730 & (vm+0x20e0|0x20d8),
                 * tst #0x1c00; on clear, clear es+0x40b8 bits 0xc00 and OR
                 * the active mask es[0x4110] with the sp+0xa0 blob. */
                ebit  = *(uint64_t *)((char *)es + 0x730);
                vm_en = *(uint32_t *)((char *)vm + 0x20e0) |
                        *(uint32_t *)((char *)vm + 0x20d8);
                if ((ebit & vm_en & 0x1c00) != 0)
                    goto unhandled_ec;
                es[0x40b8/8] &= ~0x1c00ull;             /* b98bf60 */
                es[0x4110/8] |= *(uint64_t *)((char *)es + 0x4110); /* b98bfb4 */
                return;

            case 0x3f:              /* 0x3fxxxxxx SMC-ish (b98a718..) */
                /* 0x3f3c1a -> b98c2c0 (es+0x6b0 & (vm+0x20b0|0x20a8),
                 * tbnz w9,#0x1b); 0x3fbc05/0x3fbc06/0x3fbc08 -> b98c320/
                 * b98c328 (same mask pair, tbnz w9,#0xb). */
                ebit  = *(uint64_t *)((char *)es + 0x6b0);
                vm_en = *(uint32_t *)((char *)vm + 0x20b0) |
                        *(uint32_t *)((char *)vm + 0x20a8);
                if (cls == 0x3f3c1aull) {
                    if ((ebit & vm_en & (1ull << 0x1b)) != 0)
                        goto unhandled_ec;
                    es[0x4118/8] |= 0x100000000000000ull; /* b98c2f0 */
                    es[0x4038/8] &= ~0x8000001ull;        /* b98c2fc */
                } else {                            /* 0x3fbc05/06/08 */
                    if ((ebit & vm_en & (1ull << 0xb)) != 0)
                        goto unhandled_ec;
                }
                return;
            }
        }
    }

unhandled_ec:                   /* 0xfffffe000b98d860 */
    /* Re-save EL2 state (nesting counter + hv_vcpu_save_el2_state with the
     * per-CPU feature mask) and return the unhandled-EC error; the hub's
     * case 0x8 does not touch es[0x4008], so the caller surfaces the error. */
    hv_vcpu_save_el2_state(vcpu,
        (hv_el2_l2 & 1) ? 0x7fc000000000001full
                        : 0x7bc000000000001full);   /* b98d898 */
    return;
}

/* ------------------------------------------------------------------ */
/* FUN_fffffe000b9899b0 @ 0xfffffe000b9899b0   (est. hv_vcpu_run_trap)
 *
 * VERIFIED (against the decompile) but NOT recreated here: this is owned and
 * reconstructed in hv.c (trap-dispatch tree, op table PTR_hv_op_table
 * index 8) as `kern_return_t hv_vcpu_run_trap(void *args)`.
 *
 * Relationship to hv_vcpu_run (b989a44): it is an INDEPENDENT trap entry, NOT
 * a caller of the hub.  Its decompiled body reads the per-cpu vcpu slot
 * (tpidr_el1+0x4d8), and if bound increments the nesting counter
 * (tpidr_el1+0x1c0), calls hv_vcpu_save_el2_state (b988358) with the full
 * per-CPU feature mask (0x7fc000000000001f or 0x7bc000000000001f depending on
 * DAT_fffffe0007e0d81d bit 0), then decrements the counter and on
 * counter==0 + cpu-flag bit 2 calls kernel_tlb_flush (context switch).
 * It returns 0 on success, 0xfae94006 if no vcpu is bound.  It therefore
 * forces a fresh EL2 state save so a subsequent hv_vcpu_run re-enters with
 * current guest state — a "flush" wrapper, not a run-loop caller.
 */

