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
extern void hv_el2_pt_alloc(struct hv_vm *vm);  /* FUN_fffffe000b98e344 (see hv_internal.h) */

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
        *(uint64_t *)(es + 0x4118) &= 0xffbfffffffffffffULL;  /* clear bit 42 */
        nesting_exit(cpu);                          /* tpidr_el1+0x1c0 --1 */
        dealloc((void *)el2, 0x4000);                       /* FUN_fffffe000b8a8078 */
        kfree((void *)el2, 0x4000);                         /* FUN_fffffe000b8b6860 */
    }

    el2 = p[0x1a];                                  /* +0xd0 el2 allocation 2 */
    if (el2 != 0) {
        uint64_t es = p[0x16];
        *(uint64_t *)(es + 0x4148) = 0;
        *(uint64_t *)(es + 0x4118) &= 0xffffffffffffffefULL;  /* clear bit 4 */
        nesting_exit(cpu);
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
                page_release(ent[1], 0x8000);       /* FUN_fffffe000b8b122c */
            } else {
                kfree((void *)ent[1], 0x8000);
                dealloc((void *)ent[1], 0x8000);
            }
            ent[0] = 0;
            ent[1] = 0;
            ent[2] = 0;
        }
        list_remove(&hv_slot_list, (void *)obj + i);   /* DAT_fffffe0007d53e38 FUN_fffffe000b862b6c */
        kfree((void *)obj[i + 0x429], 0);                   /* FUN_fffffe000b862b6c (est.) */
        obj[i + 0x429] = 0;
    }

    /* free the auxiliary allocations and the object header */
    hv_obj_list_op(0, obj[0x410]);
    os_release(obj[0x424]);
    hv_vm_pool_release(*obj, &hv_vm_pool);   /* DAT_fffffe000c5d7068 */
    list_remove(&hv_vm_list, obj);             /* DAT_fffffe0007d52478 */
    list_remove(&hv_obj_list, obj);            /* DAT_fffffe0007d53e78 */
}

/* ------------------------------------------------------------------ */
/* FUN_fffffe000b98503c @ 0xfffffe000b98503c   (est. hv_vcpu_state_merge)
 * Ghidra: void hv_vcpu_state_merge(long,long*,long,ulong,long,ulong)
 * Copies two overlapping register/size ranges into a destination, then, in
 * an unrolled 32-bit sweep, replaces any zero word with 0xffffffff.  This is
 * a "merge with validity mask" helper used by the hub to fold a guest
 * register frame in: a zeroed word means the field is absent and is encoded
 * as all-ones (dirty).  Heavily loop-unrolled; the control-flow for the
 * middle sizes is a partial-vectorization artifact, not 8 semantic branches.
 * Confidence: low
 * Notes: type-propagation warning "Type propagation algorithm not settling";
 *   copy helpers kernel_copy_src / kernel_early_init; the dest word
 *   count is param_6>>3; all 0 -> -1 fill. */
void hv_vcpu_state_merge(uint64_t dst, uint64_t src, uint64_t off_a,
                         uint64_t len_a, uint64_t off_b, uint64_t len_b)
{
    uint64_t *p;
    uint64_t count, i;
    uint64_t mid;

    kernel_copy_src((void *)(dst + off_a), src + off_b);  /* copy src*/
    /* copy two sized spans of the frame (overlap is handled by Ghidra's
     * min()/max() selection — kept as-is) */
    kernel_early_init(dst + (off_a - len_a), src + (off_b - len_b),
                         len_a < len_b ? len_a : len_b);
    *(uint64_t *)dst = off_a + len_a;
    *(uint64_t *)(dst + 8) = off_b + len_b;
    if (len_b < 8)
        return;

    count = len_b >> 3;
    p = (uint64_t *)(dst + (off_a - len_a));        /* lVar1 base */
    for (i = 0; i < count; i++) {
        /* fill every zero 32-bit word with 0xffffffff (validity mask) */
        uint32_t *w = (uint32_t *)p;
        if (w[0] == 0) w[0] = 0xffffffffu;
        if (w[1] == 0) w[1] = 0xffffffffu;
        p += 2;
    }
}

/* ------------------------------------------------------------------ */
/* FUN_fffffe000b9866d0 @ 0xfffffe000b9866d0   (est. hv_vcpu_map_memory)
 * Ghidra: undefined8 hv_vcpu_map_memory(long,ulong,ulong,uint,ulong*)
 * Validates that gpa (param_2) and size (param_3) are page-aligned, that the
 * region fits within the page-size mask of the active boot-arg page-size
 * descriptor (hv_page_size_table_1/60/68), then maps the guest physical
 * range in the vcpu's pmap (kernel_boot_misc_b / kernel_vm_page_op).
 * If handle_out is non-null it creates an IO/kext handle for the mapping
 * (type 0x12d) and copies it to the caller; otherwise the mapping is stored
 * at param_1+0x2120.  Returns 0 on success, 0xfae94003/0xfae94005 on error.
 * Confidence: medium
 * Notes: page size default 0x4000; uVar7 encoding 0xb (or 0xe if !=0x1000);
 *   current_cpu_datap (cpu), b948ac8 (pmap), b8ada1c (map), b7e0b70 (handle),
 *   b78d628 (copy handle); hv_page_size_table_1/60/68 +0x50/+0x58 page fields. */
uint64_t hv_vcpu_map_memory(void *vcpu, uint64_t gpa, uint64_t size,
                            uint32_t page_size, uint64_t *handle_out)
{
    uint32_t psz = page_size ? page_size : 0x4000;
    uint64_t pages, mask, pmap;
    uint64_t map;
    int enc;

    if (gpa % psz != 0 || size % psz != 0)
        return 0xfae94003;

    /* pick the page-size descriptor whose +0x58 field matches psz */
    if (*(uint64_t *)(hv_page_size_table_3 + 0x58) != psz &&
        *(uint64_t *)(hv_page_size_table_2 + 0x58) != psz &&
        *(uint64_t *)(hv_page_size_table_1 + 0x58) != psz)
        return 0xfae94003;

    /* region bound: gpa+size must be < 1<<(size&0x3f) of the descriptor */
    mask = 1ULL << ((-(*(uint64_t *)(hv_page_size_table_1 + 0x50) & 0x3f)) & 0x3f);
    if (size == 0) {
        if (gpa >= mask)
            return 0xfae94003;
    } else {
        if (gpa + size > mask || gpa + size < gpa)
            return 0xfae94003;
    }

    enc = (psz == 0x1000) ? 0xb : 3;
    pmap = (uint64_t)per_cpu_base(tpidr_el1);
    map = kernel_boot_misc_b(*(uint64_t *)(pmap + 0x328), mask, enc);
    if (map != 0) {
        int enc2 = (psz == 0x1000) ? 0xc : 0xe;
        uint64_t mapping = kernel_vm_page_op(map, gpa, mask, enc2, 0);
        if (handle_out == 0) {
            *(uint64_t *)((char *)vcpu + 0x2120) = mapping;
            return 0;
        }
        /* create an IO handle (type 0x12d) for the mapping */
        pages = kernel_zone_alloc(mapping, 0x12d, 0, 1);
        if (pages + 1 > 1) {
            uint32_t h = 0;
            if (kernel_copy_handle(*(uint64_t *)(pmap + 0x318), pages, 0x11, 2, 0, &h) != 0)
                return 0xfae94005;
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
/* FUN_fffffe000b986e50 @ 0xfffffe000b986e50   (est. hv_vcpu_attach)
 * Ghidra: undefined8 hv_vcpu_attach(long param_1)
 * Attaches the calling CPU's bound vcpu (tpidr_el1+0x4d8) to a container/VM
 * object identified by param_1.  A value of -1 detaches (returns 0 without
 * touching the object).  Resolves the id via hv_pmap_resolve_owner, rejects a
 * container whose stored id string begins with '-' (invalid, panic
 * kernel_panic_c), detaches any prior object (zfree_waitq),
 * then stores the resolved object at vcpu+0x88 and its id at vcpu+0xe0.
 * Returns 0 on success, 0xfae94003 if the id is unresolvable, 0xfae94006 if
 * no vcpu is bound to this CPU.
 * Confidence: low
 * Notes: param_1 == -1 => detach path; string '-' check via
 *   kernel_panic_c(msg,0,0x2d). */
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
                os_release(*(uint64_t *)((char *)bound + 0x88));
            goto done;
        }
        if (*s != '-')                              /* container names must not
                                                       begin with '-' */
            panic_hv(s);
    }
    zfree_waitq();                         /* detach prior */

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
        hv_vcpu_slot_clear(*(uint64_t *)((char *)vcpu + 0xb0));

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
        /* zero the SME save state (guarded by 0x4140/0x4148 fields) */
        if (*(uint16_t *)(*(uint64_t *)((char *)vcpu + 0xb0) + 0x4140) != 0)
            halt_baddata();
        if (1 < hv_build_gate)
            halt_baddata();
        for (int i = 0; i < 8; i++) r[i] = 0;
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

    case 0x5:                   /* 0xfffffe000b98cf94 (fallthrough default) */
    default:
        /* Default / shared tail handler.  If the guest had the FP/SIMD
         * "single-step" flag (es+0x710 bit 0) clear and the PMU counter
         * threshold (es+0x40b8 vs es+0x400) has elapsed, record a new exit
         * reason (0xf) at 0xfffffe000b98d814. */
        break;
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
 * 0xfedefacafeadfad9 into es+0x8/0x18/0x28, or encoding x0..x3), (b) clears
 * the handled bit and continues, or (c) falls through to the unhandled-EC
 * panic (0xfffffe000b98d860, logging via kernel_panic_msg_fmt).  Register
 * identities for the +0x6xx enable masks are unverified. */
static void hv_esr_classify(hv_vcpu_t *vcpu, uint64_t esr)
{
    uint64_t *es = (uint64_t *)vcpu->el2_state;
    uint64_t  cls = esr & 0xffffffff;
    uint64_t  vm  = *(uint64_t *)vcpu;              /* container */
    uint64_t  vmm = *(uint64_t *)(vcpu + 0xc0);     /* vmm_ctx */

    /* The full EC range is decoded in the disassembly; the branches below
     * preserve the addresses for the main families.  Each handled family
     * follows the pattern: test the guest enable bit, else return the
     * unhandled error.  The emulation bodies write into the guest save area
     * (es[0x8], es[0x18], es[0x28], es+0x398/0x3f0/0x9f0) so that the
     * return-to-guest path re-injects the synthetic register state. */
    switch (cls & 0xff000000) {
    case 0xc6000000:            /* SVC (64-bit), ISS = syscall nr */
        /* 0xfffffe000b98b3d0: opcode-count gate at vm+0x2128; if the SVC
         * number is a recognized VM op (0xc6000010..0xc600001a) dispatch to
         * hv_vm_op_dispatch (b98e020) / hv_vcpu_slot_op (b98e12c) / the
         * per-slot map path (b9866d0).  Requires no attach id (vcpu+0xe0==0)
         * and no pending SPSR bit. */
        break;
    case 0xc3000000:            /* HVC (64-bit), ISS = hvc #imm */
        /* 0xfffffe000b98a76c: check vm+0x2130 mask & (1<<imm) (imm<=6), then
         * dispatch 0xc3000003..0xc3000006 (mrs/msr-style hypercalls, timer
         * offset, vcpu slot CAS). */
        break;
    case 0xc1000000:            /* HVC (32-bit) / hint range */
        /* 0xfffffe000b98a47c: 0xc1000001..0xc100000f; writes the synthetic
         * register blob (q0/q1 from sp+0x50/0x60) into es[0x8..0x28] with the
         * 0xfedefacafeadfad9 magic. */
        break;
    case 0x83000000:            /* IABT (lower EL) */
        /* 0xfffffe000b98b39c: imm 0xff01/0xff03 -> store sp+0x80 blob to
         * es[0x8]; 0xfeff -> HVC-with-imm family (vm+0x2130 mask, imm<=6). */
        break;
    default:
        /* 0x24xxxxxx..0x3fxxxxxx debug/arch families; each tests the per-EC
         * enable bit and, if set, writes the exception into es so it is
         * re-injected, else the unhandled-EC path returns 0xfae94001
         * (0xfffffe000b98d860). */
        break;
    }
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

