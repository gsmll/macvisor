/* Recreated from kernelcache.arm64.kc (xnu-12377.121.10 RELEASE_ARM64_T8142, image base fffffe0007004000). Ground truth: Ghidra FUN_ names + addresses; all names are estimates. */

/*
 * hv_vcpu.c — vCPU lifecycle and the core vcpu run/exit dispatch path.
 *
 * Owned by the vcpu-core tree.
 * All names are estimates; ground truth is the FUN_ address in the header
 * comment of each function.  Shared kernel dependencies are declared as
 * externs in hv_vcpu.h and documented in docs/chain-map.md — never recreated.
 */

#include "hv_vcpu.h"

/* FATAL: kernel panic helper (FUN_fffffe000c0f86a4 / c0f8674 / c0f1874). */
static void __attribute__((noreturn)) panic_hv(const char *msg);

/*
 * Per-CPU access (FUN_fffffe000b866ec4).  The vcpu object bound to the
 * current CPU lives at tpidr_el1 + 0x4d8.  The cpu id is cached in
 * DAT_fffffe000c62c0c0; DAT_fffffe000c62b3d0 is a debug/lock-storm flag.
 */
#define PERCPU_VCPU_SLOT  0x4d8
#define PERCPU_CPU_ID     0x518

extern uint64_t DAT_fffffe000c62c0c0;  /* cached current cpu id */
extern uint64_t DAT_fffffe000c62b3d0;  /* debug flag */
extern uint64_t DAT_fffffe000c62c0b8;  /* per-cpu lock */
extern uint64_t DAT_fffffe000c716e40;  /* vcpu generation counter */

/* ------------------------------------------------------------------ */
/* FUN_fffffe000b989040 @ 0xfffffe000b989040   (est. hv_vcpu_create)
 * Ghidra: ulong FUN_fffffe000b989040(undefined8 param_1)
 * Copies a 16-byte guest request in, validates the vcpu id (< 64), requires
 * that no vcpu is already bound to this CPU, retains the current container
 * object, allocates+initialises a vcpu, builds the EL2 state, writes the
 * vcpu id into the container's per-slot table, and binds the vcpu into the
 * per-CPU slot (tpidr_el1 + 0x4d8).  On any failure it unwinds through the
 * error paths (destroy/release) and returns an 0xfae940xx error.
 * Confidence: medium
 * Notes: copyin FUN_fffffe000b95c144(.., 0x10); copyout FUN_fffffe000b95d6f4;
 *   container slot table stride 0x80, valid slot at +0x80, busy flag +0x90,
 *   state word +0x94; object refcount at plVar12[1]; quota flag
 *   DAT_fffffe000c5b83b0; per-cpu id cached in DAT_fffffe000c62c0c0; lock
 *   FUN_fffffe000b7f0afc/1e4c/1e80; panic FUN_fffffe000c0f86a4/c0f8674. */
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
    if (DAT_fffffe000c62c0c0 == 0)
        DAT_fffffe000c62c0c0 = *(uint32_t *)(cpu + PERCPU_CPU_ID);
    if (DAT_fffffe000c62b3d0 != 0)
        lock_acquire(&DAT_fffffe000c62c0b8, cpu);   /* FUN_fffffe000b7f0afc */

    /* resolve the current container from the per-cpu struct (FUN_fffffe000b866ec4) */
    container = *(void **)(FUN_fffffe000b866ec4(cpu) + 0x628);
    if (container == 0) {
        lock_release(&DAT_fffffe000c62c0b8);        /* FUN_fffffe000b7f1e4c */
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
    if (DAT_fffffe000c62b3d0 != 0)
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
    hv_el2_state_build(vcpu, vcpu_p[1], 0);         /* FUN_fffffe000b9895b8 */
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
    DAT_fffffe000c716e40 += 1;
    vcpu_p[0x1b] = DAT_fffffe000c716e40;            /* +0xd8 */
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
 * Ghidra: undefined8 FUN_fffffe000b989390(long *param_1,undefined8 param_2,int param_3)
 * Allocates the 0x100-byte vcpu object and a 0x8000-byte guest-memory
 * mapping (via the zone allocator FUN_fffffe000b8a6c14 and the map-enter
 * FUN_fffffe000b8b51c8 against the VM at param_2), then links them and
 * returns the vcpu through param_1.  On failure it unwinds the partial
 * allocations and returns an 0xfae940xx error.
 * Confidence: medium
 * Notes: alloc calls FUN_fffffe000b8a6c14(0,0x100,0,0x80,0x1c,0) and
 *   (0,0x8000,0,0x10080,0x1c,zone); two map-enters FUN_fffffe000b8b51c8 with
 *   flags 0x1c100008 (0x8000) and 0x1c104001 (0x4000); unwind FUN_fffffe000b8a8078
 *   (dealloc), FUN_fffffe000b7f62e8 (lock), FUN_fffffe000b8b6860 (free). */
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
        dealloc(guest, 0x8000);                     /* FUN_fffffe000b8a8078 */
        rc = 0xfae94001;
        goto fail_guest;
    }
    if (vm_map_enter(vm, &map, 0x4000, 0, 0x1c104001) != 0) {  /* FUN_fffffe000b8b51c8 */
        dealloc(guest, 0x8000);
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
    kfree(guest, 0x8000);                           /* FUN_fffffe000b8b6860 */
fail_vcpu:
    kfree(vcpu, 0x100);                             /* FUN_fffffe000b8b6860 */
    return rc;
}

/* ------------------------------------------------------------------ */
/* FUN_fffffe000b988e70 @ 0xfffffe000b988e70   (est. hv_vcpu_destroy)
 * Ghidra: void FUN_fffffe000b988e70(long *param_1)
 * Frees a vcpu's EL2 state allocations (two 0x4000 regions at param_1+0x18
 * and param_1+0x1a, the 0x8000 guest region at param_1[2], the el2_state
 * region at param_1[0x16], and finally the 0x800-byte vcpu object itself).
 * Clears the corresponding bits in the EL2 dirty/flags word at
 * param_1[0x16]+0x4118 and uses the per-CPU nesting counter tpidr_el1+0x1c0.
 * Confidence: medium
 * Notes: frees via FUN_fffffe000b8a8078 (dealloc) + FUN_fffffe000b8b6860
 *   (free) + FUN_fffffe000b7f62e8 (lock); flags clear masks 0xffbfffffffffffff
 *   (bit 42) and 0xffffffffffffffef (bit 4); nesting callback
 *   FUN_fffffe000b96c6d4; panic FUN_fffffe000c0f1874. */
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
        dealloc(el2, 0x4000);                       /* FUN_fffffe000b8a8078 */
        kfree(el2, 0x4000);                         /* FUN_fffffe000b8b6860 */
    }

    el2 = p[0x1a];                                  /* +0xd0 el2 allocation 2 */
    if (el2 != 0) {
        uint64_t es = p[0x16];
        *(uint64_t *)(es + 0x4148) = 0;
        *(uint64_t *)(es + 0x4118) &= 0xffffffffffffffefULL;  /* clear bit 4 */
        nesting_exit(cpu);
        dealloc(el2, 0x4000);                       /* FUN_fffffe000b8a8078 */
        kfree(el2, 0x4000);                         /* FUN_fffffe000b8b6860 */
    }

    dealloc(p[2], 0x8000);                          /* guest_mem */
    kfree(p[0x16], 0x8000);                         /* el2_state */
    kfree(vcpu, 0x800);                             /* the vcpu object */
}

/* ------------------------------------------------------------------ */
/* FUN_fffffe000b98533c @ 0xfffffe000b98533c   (est. hv_vcpu_object_release)
 * Ghidra: void FUN_fffffe000b98533c(undefined8 *param_1)
 * Final release of a vcpu/VM object: updates per-type quota counters
 * (DAT_fffffe000c5b83b0), then walks the 8 per-slot registration arrays
 * (param_1[0x429..0x430], each 0x40 entries of 16 bytes) freeing the guest
 * pages and clearing each entry, frees the object's auxiliary allocations
 * and its header, and unlinks it from the two global lists
 * (DAT_fffffe0007d52478 / DAT_fffffe0007d53e78).
 * Confidence: medium
 * Notes: FUN_fffffe000b987c44 (resource teardown); page ops
 *   FUN_fffffe000b8b122c/8a8078/8b6860; list remove FUN_fffffe000b862b6c;
 *   FUN_fffffe000b8afa78(param_1[0x424]), FUN_fffffe000b7f09dc(*param_1); quota
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
        DAT_fffffe000c5b83b0[type] += 1;            /* (estimate of counter table) */
    }

    /* resource teardown */
    FUN_fffffe000b987c44(obj);

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
                kfree(ent[1], 0x8000);
                dealloc(ent[1], 0x8000);
            }
            ent[0] = 0;
            ent[1] = 0;
            ent[2] = 0;
        }
        list_remove(&DAT_fffffe0007d53e38, (void *)obj + i);   /* FUN_fffffe000b862b6c */
        kfree(obj[i + 0x429], 0);                   /* FUN_fffffe000b862b6c (est.) */
        obj[i + 0x429] = 0;
    }

    /* free the auxiliary allocations and the object header */
    FUN_fffffe000b8627ac(0, obj[0x410]);
    FUN_fffffe000b8afa78(obj[0x424]);
    FUN_fffffe000b7f09dc(*obj, &DAT_fffffe000c5d7068);
    list_remove(&DAT_fffffe0007d52478, obj);
    list_remove(&DAT_fffffe0007d53e78, obj);
}

/* ------------------------------------------------------------------ */
/* FUN_fffffe000b98503c @ 0xfffffe000b98503c   (est. hv_vcpu_state_merge)
 * Ghidra: void FUN_fffffe000b98503c(long,long*,long,ulong,long,ulong)
 * Copies two overlapping register/size ranges into a destination, then, in
 * an unrolled 32-bit sweep, replaces any zero word with 0xffffffff.  This is
 * a "merge with validity mask" helper used by the hub to fold a guest
 * register frame in: a zeroed word means the field is absent and is encoded
 * as all-ones (dirty).  Heavily loop-unrolled; the control-flow for the
 * middle sizes is a partial-vectorization artifact, not 8 semantic branches.
 * Confidence: low
 * Notes: type-propagation warning "Type propagation algorithm not settling";
 *   copy helpers FUN_fffffe000b758d80 / FUN_fffffe000b758bd0; the dest word
 *   count is param_6>>3; all 0 -> -1 fill. */
void hv_vcpu_state_merge(uint64_t dst, uint64_t src, uint64_t off_a,
                         uint64_t len_a, uint64_t off_b, uint64_t len_b)
{
    uint64_t *p;
    uint64_t count, i;
    uint64_t mid;

    FUN_fffffe000b758d80((void *)(dst + off_a), src + off_b);  /* copy src*/
    /* copy two sized spans of the frame (overlap is handled by Ghidra's
     * min()/max() selection — kept as-is) */
    FUN_fffffe000b758bd0(dst + (off_a - len_a), src + (off_b - len_b),
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
 * Ghidra: undefined8 FUN_fffffe000b9866d0(long,ulong,ulong,uint,ulong*)
 * Validates that gpa (param_2) and size (param_3) are page-aligned, that the
 * region fits within the page-size mask of the active boot-arg page-size
 * descriptor (PTR_PTR_fffffe000c5b3f58/60/68), then maps the guest physical
 * range in the vcpu's pmap (FUN_fffffe000b948ac8 / FUN_fffffe000b8ada1c).
 * If handle_out is non-null it creates an IO/kext handle for the mapping
 * (type 0x12d) and copies it to the caller; otherwise the mapping is stored
 * at param_1+0x2120.  Returns 0 on success, 0xfae94003/0xfae94005 on error.
 * Confidence: medium
 * Notes: page size default 0x4000; uVar7 encoding 0xb (or 0xe if !=0x1000);
 *   FUN_fffffe000b866ec4 (cpu), b948ac8 (pmap), b8ada1c (map), b7e0b70 (handle),
 *   b78d628 (copy handle); PTR_PTR_fffffe000c5b3f58/60/68 +0x50/+0x58 page fields. */
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
    if (*(uint64_t *)(PTR_PTR_fffffe000c5b3f68 + 0x58) != psz &&
        *(uint64_t *)(PTR_PTR_fffffe000c5b3f60 + 0x58) != psz &&
        *(uint64_t *)(PTR_PTR_fffffe000c5b3f58 + 0x58) != psz)
        return 0xfae94003;

    /* region bound: gpa+size must be < 1<<(size&0x3f) of the descriptor */
    mask = 1ULL << ((-(*(uint64_t *)(PTR_PTR_fffffe000c5b3f58 + 0x50) & 0x3f)) & 0x3f);
    if (size == 0) {
        if (gpa >= mask)
            return 0xfae94003;
    } else {
        if (gpa + size > mask || gpa + size < gpa)
            return 0xfae94003;
    }

    enc = (psz == 0x1000) ? 0xb : 3;
    pmap = FUN_fffffe000b866ec4(tpidr_el1);
    map = FUN_fffffe000b948ac8(*(uint64_t *)(pmap + 0x328), mask, enc);
    if (map != 0) {
        int enc2 = (psz == 0x1000) ? 0xc : 0xe;
        uint64_t mapping = FUN_fffffe000b8ada1c(map, gpa, mask, enc2, 0);
        if (handle_out == 0) {
            *(uint64_t *)((char *)vcpu + 0x2120) = mapping;
            return 0;
        }
        /* create an IO handle (type 0x12d) for the mapping */
        pages = FUN_fffffe000b7e0b70(mapping, 0x12d, 0, 1);
        if (pages + 1 > 1) {
            uint32_t h = 0;
            if (FUN_fffffe000b78d628(*(uint64_t *)(pmap + 0x318), pages, 0x11, 2, 0, &h) != 0)
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
 * Ghidra: undefined8 FUN_fffffe000b986e50(long param_1)
 * Attaches the calling CPU's bound vcpu (tpidr_el1+0x4d8) to a container/VM
 * object identified by param_1.  A value of -1 detaches (returns 0 without
 * touching the object).  Resolves the id via FUN_fffffe000b986b34, rejects a
 * container whose stored id string begins with '-' (invalid, panic
 * FUN_fffffe000c0e1c3c), detaches any prior object (FUN_fffffe000b793cf4),
 * then stores the resolved object at vcpu+0x88 and its id at vcpu+0xe0.
 * Returns 0 on success, 0xfae94003 if the id is unresolvable, 0xfae94006 if
 * no vcpu is bound to this CPU.
 * Confidence: low
 * Notes: param_1 == -1 => detach path; string '-' check via
 *   FUN_fffffe000c0e1c3c(msg,0,0x2d). */
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

    if (FUN_fffffe000b986b34(id, &resid) == 0)
        return 0xfae94003;

    s = *(char **)((char *)bound + 0xe0);
    if (s != (char *)0xffffffffffffffff) {
        if (s == 0) {
            if (*(uint64_t *)(cpu + PERCPU_VCPU_SLOT) == 0)
                FUN_fffffe000b8afa78(*(uint64_t *)((char *)bound + 0x88));
            goto done;
        }
        if (*s != '-')                              /* container names must not
                                                       begin with '-' */
            panic_hv(s);
    }
    FUN_fffffe000b793cf4();                         /* detach prior */

done:
    *(uint64_t *)((char *)bound + 0x88) = resolved;
    *(uint64_t *)((char *)bound + 0xe0) = resid;
    return 0;
}

/* ------------------------------------------------------------------ */
/* FUN_fffffe000b988358 @ 0xfffffe000b988358   (est. hv_vcpu_save_el2_state)
 * Ghidra: void FUN_fffffe000b988358(long param_1,ulong param_2)
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
 *   flags DAT_fffffe0007e0d81e / DAT_fffffe0007e0da68 gate conditional reads;
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
        if ((DAT_fffffe0007e0d81e & 1) != 0)
            *(es + 0x468) = UnkSytemRegRead(3,5,0xd,0,7);
        if (DAT_fffffe0007e0da68 != 0)
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
        FUN_fffffe000b9888a4(*(uint64_t *)((char *)vcpu + 0xb0));

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
            FUN_fffffe000b75f118(en);
            UnkSytemRegWrite(3,4,0xf,1,4, UnkSytemRegRead(3,4,0xf,1,4) & 0x7fffffffffffffffULL);
            InstructionSynchronizationBarrier();
        }
    }

    if (((b >> 4 & 1) != 0) && ((*(uint8_t *)(*(uint64_t *)((char *)vcpu + 0xb0) + 0x4138) >> 1 & 1) != 0)) {
        uint64_t *r = *(uint64_t **)((char *)vcpu + 0xd0);
        /* zero the SME save state (guarded by 0x4140/0x4148 fields) */
        if (*(uint16_t *)(*(uint64_t *)((char *)vcpu + 0xb0) + 0x4140) != 0)
            halt_baddata();
        if (1 < DAT_fffffe0007e0da68)
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
        if ((DAT_fffffe0007e0d81c & 1) != 0)
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
 * Ghidra: undefined8 FUN_fffffe000b989a44(undefined8 arg)
 * This is the per-vCPU run loop and guest-exit dispatch hub (16.8 KB, ~3960
 * instructions).  It loads the vcpu bound to the current CPU (tpidr_el1 +
 * 0x4d8), restores the guest's EL2 system-register state into hardware, runs
 * the guest, then on each exit saves the EL2 state back (hv_vcpu_save_el2_state)
 * and dispatches on the exit reason / ESR EC.  The exit reason lives at
 * el2_state+0x4008; synchronous-exception classes (0xc3000000=HVC, 0x83000000,
 * 0xc1xxxxxx data aborts, 0xc6000000 SVC) select the handler.  The function is
 * table-dispatched: its address is stored at DAT_fffffe0007e0d798 and called
 * through the pointer at fffffe000d20adb3; it has no direct callers.
 *
 * DECOMPILER FAILED ("Unable to find unique hash for varnode") — this is a
 * PARTIAL reconstruction from assembly (fallback 3).  Structure below is
 * faithful to the disassembly; per-instruction offsets are preserved.
 *
 * Confidence: low
 * Notes: fallbacks applied — (1) set_function_prototype(undefined8 arg) then
 *   retry decompile FAILED; (2) analyze_function_complete SUCCEEDED giving
 *   xrefs (DAT_fffffe0007e0d798 data, fffffe000d20adb3 dispatch table) and 43
 *   callees; (3) disassemble_function reconstructed the control flow.  PAC'd
 *   (pacibsp/retab/autda).  Nesting counter tpidr_el1+0x1c0, cpu struct
 *   tpidr_el1+0x1b8 (+0x4c flag).  Error codes 0xfae94001..0xfae9400f.  Calls
 *   my-tree helpers FUN_fffffe000b988358 (save el2), b986e50 (attach),
 *   b9866d0 (map), b98503c (merge); el2-state helpers b98dd04/b98dd40/b98ded4/
 *   b98e344; el2 build b9895b8; panic FUN_fffffe000c0e11ec/c0f1874/c0e0620/
 *   c0e4d74. */
uint64_t hv_vcpu_run(void *arg)
{
    uint64_t cpu = tpidr_el1;
    hv_vcpu_t *vcpu = *(hv_vcpu_t **)(cpu + 0x4d8);
    uint64_t *es;                 /* el2_state (guest save area) */
    uint32_t reason;              /* exit reason / ESR at es+0x4008 */
    uint64_t dirty, pending;

    if (vcpu == 0)
        return 0xfae94005;        /* no vcpu bound to this CPU */

    /* (prologue: PAC, stack canary, EL2 feature mask load, etc.) */
    es = (uint64_t *)vcpu->el2_state;

    /* Re-entry: if a container is bound (vcpu->attach_obj), attach this vcpu
     * to it (FUN_fffffe000b986e50) and resolve the vm pointer.  FUN at
     * 0xfffffe000b989b44 / 0xfffffe000b989b8c. */
    if (vcpu->attach_obj != 0) {
        if (hv_vcpu_attach(vcpu, *(uint64_t *)(vcpu->attach_obj + 0x1008)) != 0) {
            /* error path: set exit reason, store error */
            vcpu->guest_ctx = (uint64_t)vcpu->attach_obj;   /* +0x8 */
            /* ... falls through to save + return */
        }
    }

    /* Guest-exit dispatch: reason = es[0x4008].  Cases observed: */
    reason = *(uint32_t *)((char *)es + 0x4008);
    switch (reason) {
    case 0x80000000:            /* FUN_fffffe000b98a19c */
        hv_el2_state_teardown(vcpu);            /* FUN_fffffe000b98e344 */
        break;
    case 0x1:                   /* FUN_fffffe000b98a298 */
        /* read es[0x4010]>>26: 0x16/0x9 select guest-exit flag paths */
        break;
    case 0x5:                   /* fallthrough default handler */
        break;
    case 0x8:                   /* FUN_fffffe000b98a08c: HCR/ESR decode */
        /* mask es[0x4018] against 0x332c00..0x30fc1e families and dispatch
         * on the encoded exception class (see jump table at 0xfffffe000b989cf4) */
        break;
    case 0xa:                   /* FUN_fffffe000b98a2d8: error */
        return 0xfae94003;
    case 0xd:                   /* FUN_fffffe000b98a1a8: alloc 0x4000 EL2 */
        /* alloc via FUN_fffffe000b8a6c14, vm_map_enter FUN_fffffe000b8b51c8,
         * store at vcpu->el2_extra and es+0x4148, set es+0x4118 bit 4 */
        break;
    default:
        break;
    }

    /* EL2 register restore on re-entry: a bitmask (w23) selects which groups
     * are written back into hardware — vmpidr_el2/vpidr_el2 (es+0x4050/0x58),
     * mdcr_el2, cnthctl_el2, CNTV/CONTROL timer regs, dbgclaim/dbgbvr/dbgwvr,
     * AMX enable, PMU regs (0x7b0..0x9f8).  Mirror of hv_vcpu_save_el2_state
     * in reverse (FUN_fffffe000b98a8b4..0xfffffe000b98b2a4). */

    /* Run the guest and loop back to the dispatch on the next exit
     * (0xfffffe000b98a044..0xfffffe000b98a6e4). */

    /* On exit: capture the EL2 state back (FUN_fffffe000b988358), then return
     * the exit reason to the caller.  Nesting counter tpidr_el1+0x1c0 is
     * incremented around the save/restore critical sections. */
    hv_vcpu_save_el2_state(vcpu, dirty_mask);

    /* The hub also exercises the guest-memory map path (FUN_fffffe000b9866d0)
     * and register merge path (FUN_fffffe000b98503c) for certain exits. */

    return *(uint32_t *)((char *)es + 0x4008);
}

