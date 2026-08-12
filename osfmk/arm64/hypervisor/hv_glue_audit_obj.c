/* Recreated from kernelcache.arm64.kc (xnu-12377.121.10 RELEASE_ARM64_T8142, image base fffffe0007004000). Ground truth: Ghidra FUN_ names + addresses; all names are estimates. */
/* hv_glue_audit_obj.c — kernel object/refcount touch-set recreation (tree hv-deps, FULL-AUDIT). */

#include <stdint.h>
#include <stddef.h>

/*
 * Recreated kernel object / refcount primitives the hypervisor calls directly
 * (its object touch set). Each is transcribed faithfully from a fresh Ghidra
 * decompile of kernelcache.arm64.kc; the hypervisor's own callees (2+ levels
 * into XNU) are declared as externs below — that is the audit boundary.
 *
 * Prototype notes vs. the existing tree headers:
 *   - os_ref_retain: hv_internal.h / hv_vmapple.c declare it 1-arg
 *     `void *os_ref_retain(void *)`, but the fresh decompile of b7f089c is a
 *     2-arg `void (int*, byte*)`. Header needs correcting (shared-utils owns
 *     hv_internal.h, so this file cannot edit it). Faithful body kept here.
 *   - kernel_fault_post: hv_el2.h declares `int (void*,uint64_t,uint64_t,int,int)`;
 *     decompile is 5 args with param4 uint64_t and param5 int* (out flag),
 *     returning uint64_t. Faithful body kept here; header 5th arg should be `int *`.
 *   - kernel_obj_lookup_core: hv_kernel_shims.h declares old-style
 *     `int kernel_obj_lookup_core();`; faithful 7-arg body is compatible.
 *   - kernel_obj_release: hv_el2.h declares `void (uint64_t)`; decompile's
 *     char* param is ABI-compatible, kept as uint64_t to match.
 */

/* ---- Local Ghidra-compat typedefs (file is self-contained; no shared header
 *      is included so the corrected os_ref_retain signature can be defined). */
typedef unsigned long ulong;
typedef unsigned int  uint;
typedef unsigned char byte;
typedef unsigned short ushort;
typedef struct { uint64_t lo, hi; } hv_u128_t;   /* Ghidra 16-byte return (auVar6) */

/* ======================================================================== *
 * Shared globals referenced by the bodies (naming table in hv_internal.h).
 * ======================================================================== */
extern uint64_t hv_vm_list;           /* DAT_fffffe0007d52478 vm object list head */
extern uint8_t  hv_registry_flag;     /* DAT_fffffe0007d790f8 retain flag byte (est.) */
extern uint64_t tpidr_el1;            /* per-CPU data base (raw register value) */
extern uint64_t *waitq_table;         /* PTR_s_waitq_fffffe0007d7c8f0 waitq registration table */
extern uint64_t hv_fault_meta;        /* DAT_fffffe000c5b2930 fault-record meta (est.) */
extern uint64_t refcount_hash_table;  /* DAT_fffffe000c608b80 refcount hash table */
extern uint8_t  zone_type_table[];    /* DAT_fffffe0007d800b0 zone-type/tag table */

/* ======================================================================== *
 * Kernel panics / ARC-release hook (universal XNU, noreturn, NOT recreated).
 * ======================================================================== */
extern void LORelease(void);   /* ARC-style object release (kernel) */
extern void kernel_panic_a(void) __attribute__((noreturn));            /* FUN_fffffe000c0f86a4 (refcount overflow) */
extern void kernel_panic_b(void) __attribute__((noreturn));            /* FUN_fffffe000c0f8674 (refcount hit 0) */
extern void panic_dyn(int code, ...) __attribute__((noreturn));        /* FUN_fffffe000c0eae24 (zone-tag validation) */
extern void kernel_panic_d(void *obj, void *ref, unsigned int n) __attribute__((noreturn)); /* FUN_fffffe000c0e0d40 */
extern void kernel_panic_e(void *p) __attribute__((noreturn));         /* FUN_fffffe000c0ea524 (refcount hash) */
extern void SoftwareBreakpoint(uint32_t imm, uint64_t addr) __attribute__((noreturn)); /* XNU brk assert */

/* ======================================================================== *
 * Stubbed kernel callees (audit boundary — their internals are 2+ levels in).
 * ======================================================================== */
extern void *hv_zone_alloc(void *zone, int kind);       /* FUN_fffffe000b7eb624 hv zone alloc */
extern void  obj_release_free(void *obj);               /* FUN_fffffe000b8a9fb0 refcount-1 object free */
extern void  waitq_lock_register(uint64_t lock, uint64_t **table);  /* FUN_fffffe000b7f78ec waitq lock register */
extern void  waitq_lock_release(uint64_t lock);         /* FUN_fffffe000b7f7538 waitq lock release */
extern hv_u128_t kernel_waitq_ctx_get(void *obj);       /* FUN_fffffe000b78c940 12-byte {waitq,handle,flags} ctx */
extern void  container_handle_notify(void *obj, uint64_t handle);  /* FUN_fffffe000b78ca94 */
extern void  container_fault_notify(void *obj);         /* FUN_fffffe000b791dc0 */
extern void  obj_release_vm(void);                      /* FUN_fffffe000b794224 (kernel_obj_release type A) */
extern void  obj_release_region(void);                  /* FUN_fffffe000b7961a0 (kernel_obj_release type B) */
extern void  refcount_table_get(void *obj, ushort key); /* FUN_fffffe000b758d80 refcount table validate */
extern void  refcount_table_dec(uint64_t *node, uint64_t handle, void *obj, ushort key); /* FUN_fffffe000b85d440 */
extern ulong container_entry_find(ulong container, ulong handle, ulong *entry_out); /* FUN_fffffe000b7968e8 */
extern ulong container_lookup_core(ulong container, ulong handle, ulong type,
                                   uint32_t flags, ulong arg5, ulong entry,
                                   ulong *out, void *aux16, ulong *extra); /* FUN_fffffe000b798c24 */
extern void  container_lock_release(ulong container); /* FUN_fffffe000b7f7dd8 */
extern void  container_post_waitq(void *aux16, ulong handle);   /* FUN_fffffe000b798b38 */
extern void  container_post_ref(ulong *extra);       /* FUN_fffffe000b798bb8 */

/* Forward declarations for the cross-referenced bodies defined below. */
void kernel_obj_release(ulong obj);
ulong kernel_obj_lookup_core(ulong container, ulong handle, ulong type, uint flags,
                             ulong arg5, ulong arg6, ulong *out);
ulong kernel_fault_post(void *rec, ulong size, ulong type, ulong arg4, int *out);
extern ulong fault_record_lookup(void *rec, ulong size, ulong flags, ulong *out); /* FUN_fffffe000b78a2a4 */
extern uint64_t fault_record_validate(uint64_t fault);  /* FUN_fffffe000b78a500 */
extern uint64_t fault_record_post(uint64_t fault, uint64_t flags, uint64_t arg); /* FUN_fffffe000b78aa38 */
extern void  fault_record_release(uint64_t fault, int n);  /* FUN_fffffe000b7867a4 */
extern void  fault_record_free(uint64_t fault);         /* FUN_fffffe000b7864d0 */

/* ======================================================================== *
 * Recreated bodies
 * ======================================================================== */

/* FUN_fffffe000b8afa78 @ 0xfffffe000b8afa78   (est. os_release)
 * Ghidra: void FUN_fffffe000b8afa78(ulong param_1)
 * ARC-style object refcount release. Validates the object's zone magic (tag
 * 0xf, OSObject zone) and the address-range bound, then decrements the
 * refcount at obj+0x88. If it was 0 it underflowed (panic c0f8674); if it was
 * 1 the object is freed via obj_release_free (b8a9fb0). LORelease is invoked
 * unconditionally on a live object.
 * Confidence: high
 * Notes: zone-tag validation panic c0eae24(0xf); refcount-0 panic c0f8674;
 *   refcount-1 release b8a9fb0; LORelease stub. */
void
os_release(void *object)
{
    ulong addr = (ulong)object;
    ulong probe;
    int old;                              /* iVar1 */

    if (addr != 0) {
        probe = addr | 0xf00000000000000UL;
        if ((0xffffffffffffff1fUL < probe) ||
            (probe != 0xffffffffffffff20UL) ||
            ((*(ushort *)((addr >> 10) & 0xffffffff0UL) & 0x3ffUL) != 0xfUL)) {
            panic_dyn(0xf);               /* FUN_fffffe000c0eae24, noreturn */
        }
        old = *(int *)(addr + 0x88);
        *(int *)(addr + 0x88) = old - 1;
        LORelease();
        if (old == 0) {
            kernel_panic_b();             /* FUN_fffffe000c0f8674, noreturn */
        }
        if (old == 1) {
            obj_release_free(object);     /* FUN_fffffe000b8a9fb0 */
        }
    }
}

/* FUN_fffffe000b7f089c @ 0xfffffe000b7f089c   (est. os_ref_retain)
 * Ghidra: void FUN_fffffe000b7f089c(int *param_1,byte *param_2)
 * Object refcount retain. Allocates a registry node from the vm-list zone
 * (hv_zone_alloc on &hv_vm_list), tags it 0x22, sets an ownership flag bit
 * from a global or the caller-supplied byte, then bumps the caller object's
 * counters (obj[4]++, and obj[0]++ with an overflow guard when obj[1] is
 * negative).
 * Confidence: low
 * Notes: registry node DAT_fffffe0007d52478 (hv_vm_list); flag default
 *   DAT_fffffe0007d790f8; overflow panic c0f86a4. NOTE: hv_internal.h and
 *   hv_vmapple.c declare this 1-arg `void *`; the fresh decompile is 2-arg
 *   `void (int*,byte*)` — header needs correction (shared-utils owns it). */
void
os_ref_retain(int *obj, byte *flag)
{
    uint *node;                           /* puVar4 */
    byte *pb;                             /* pbVar1 */
    uint u;                               /* uVar2 */
    int i;                                /* iVar3 */

    node = (uint *)hv_zone_alloc(&hv_vm_list, 0);   /* FUN_fffffe000b7eb624; &DAT_7d52478 */
    pb = &hv_registry_flag;               /* DAT_fffffe0007d790f8 */
    if (flag != (byte *)0x0) {
        pb = flag;
    }
    u = obj[1];
    *node = (u & 0xffffff) | 0x22000000;
    node[1] = 0;
    node[2] = 0;
    node[3] = 0;
    if ((*pb & 1) != 0) {
        node[2] = 0x80000000;
    }
    obj[4] = obj[4] + 1;
    if ((int)u < 0) {
        i = *obj;
        *obj = i + 1;
        if ((i + 0xf0000001U) < 0xf0000002U) {
            kernel_panic_a();             /* FUN_fffffe000c0f86a4, noreturn */
        }
    }
}

/* FUN_fffffe000b793cf4 @ 0xfffffe000b793cf4   (est. zfree_waitq)
 * Ghidra: void FUN_fffffe000b793cf4(ulong param_1)
 * Zone free with waitq teardown. Validates zone magic (tag 0x15), registers
 * the object's embedded waitq lock (obj+0x14), decrements the refcount at
 * obj+0x88 (panic c0e0d40 on 0), fetches the current waitq/thread context
 * when the object reaches its final refcount, asserts on a pending flag,
 * tears down the waitq, decrements the obj+4 refcount (panic c0f8674 on 0,
 * kernel_obj_release b78cc20 at 1), then posts a fault record when a waitq
 * context remains.
 * Confidence: high
 * Notes: tag-0x15 validation panic c0eae24(0x15,obj); waitq ops b7f78ec /
 *   b7f7538; refcount-1 release b78cc20 (= kernel_obj_release); ctx getter
 *   b78c940; fault post b7e16f0 (= kernel_fault_post) with record base at
 *   local_60; SoftwareBreakpoint(0xbffc, 0xfffffe000b793e88) noreturn assert. */
void
zfree_waitq(ulong obj)
{
    ulong probe;
    hv_u128_t ctx;                        /* auVar6: 16-byte {waitq,handle,flags} */
    ulong waitq;                          /* lVar3 = ctx.lo (auVar6._0_8_) */
    int old88;                            /* iVar5 (refcount @ +0x88) */
    int new88;                            /* iVar2 */
    int old4;                             /* iVar5 (refcount @ +4) */
    byte flag;                            /* bVar1 = *(byte*)(obj+2) */
    ulong rec60;                          /* local_60 = 0x12 */
    ulong rec50;                          /* uStack_50 = 0 */
    ulong rec48;                          /* local_48 = 0x4600000000 */
    ulong rec58;                          /* local_58 = waitq */
    ulong rec40;                          /* local_40 = hv_fault_meta (DAT_c5b2930) */
    uint  rec38;                          /* local_38 = (uint)ctx.hi */

    if (1 < obj + 1) {
        probe = obj | 0xf00000000000000UL;
        if ((0xffffffffffffff6fUL < probe) ||
            (probe != 0xffffffffffffff70UL) ||
            ((*(ushort *)((obj >> 10) & 0xffffffff0UL) & 0x3ffUL) != 0x15UL)) {
            panic_dyn(0x15, obj);         /* FUN_fffffe000c0eae24, noreturn */
        }
        waitq_lock_register(obj + 0x14, &waitq_table);   /* FUN_fffffe000b7f78ec */
        old88 = *(int *)(obj + 0x88);
        new88 = old88 - 1;
        *(int *)(obj + 0x88) = new88;
        if (old88 == 0) {
            kernel_panic_d((void *)obj, (void *)(obj + 0x88), 0xffffffff); /* FUN_fffffe000c0e0d40, noreturn */
        }
        ctx.lo = 0;
        ctx.hi = 0;
        if (new88 == 0) {
            if ((*(byte *)(obj + 1) & 7) != 0) {
                ctx = kernel_waitq_ctx_get((void *)obj);   /* FUN_fffffe000b78c940 */
            }
            flag = *(byte *)(obj + 2);
        }
        else {
            flag = *(byte *)(obj + 2);
        }
        waitq = ctx.lo;
        if ((flag & 1) != 0) {
            SoftwareBreakpoint(0xbffc, 0xfffffe000b793e88);   /* noreturn */
        }
        waitq_lock_release(obj + 0x14);   /* FUN_fffffe000b7f7538 */
        old4 = *(int *)(obj + 4);
        *(int *)(obj + 4) = old4 - 1;
        LORelease();
        if (old4 == 0) {
            kernel_panic_b();             /* FUN_fffffe000c0f8674, noreturn */
        }
        if (old4 == 1) {
            kernel_obj_release(obj);      /* FUN_fffffe000b78cc20 */
        }
        if (waitq != 0) {
            if ((ctx.hi >> 0x20) != 0) {
                container_handle_notify((void *)waitq, ctx.hi);  /* FUN_fffffe000b78ca94 */
                return;
            }
            if ((*(byte *)(waitq + 1) & 7) == 0) {
                container_fault_notify((void *)waitq);   /* FUN_fffffe000b791dc0 */
                return;
            }
            rec38 = (uint)ctx.hi;         /* auVar6._8_4_ */
            rec60 = 0x12;
            rec50 = 0;
            rec48 = 0x4600000000UL;
            rec58 = waitq;
            rec40 = hv_fault_meta;        /* DAT_fffffe000c5b2930 */
            kernel_fault_post(&rec60, 0x2c, 0x50001, 0, 0);   /* FUN_fffffe000b7e16f0 */
        }
    }
}

/* FUN_fffffe000b862b6c @ 0xfffffe000b862b6c   (est. refcount_dec)
 * Ghidra: void FUN_fffffe000b862b6c(undefined8 *param_1,ulong param_2)
 * Refcount-hash decrement + free of `param_2` (obj) tracked in the container
 * `param_1` (a refcount-hash table). Looks up the hash bucket for the obj's
 * zone tag, walks the container entry (validating the zone/tag tables,
 * PAC-restoring the slot), then performs the refcount table get (b758d80)
 * and decrement (b85d440). Panics c0ea524 on a bad container/entry.
 * Confidence: high
 * Notes: hash table DAT_fffffe000c608b80 (stride via tag), zone/tag table
 *   DAT_fffffe0007d800b0 (Ghidra renders its element size inconsistently —
 *   byte-offset interpretation used here); refcount overflow panic c0ea524;
 *   the `tco=1/0` pseudo-register around the two tail calls is dropped. */
void
refcount_dec(void *ref, void *free_fn)
{
    uint64_t *container = (uint64_t *)ref;   /* param_1 */
    ulong obj = (ulong)free_fn;              /* param_2 */
    uint64_t *node;                          /* puVar6 */
    uint64_t *table;                         /* puVar4 */
    ulong tag;                               /* uVar5 */
    ulong idx;                               /* uVar2 */
    ulong h;                                 /* hash idx */
    uint8_t *slot;                           /* puVar3 */
    ulong handle;                            /* uVar7 */
    ushort key;                              /* uVar1 */

    if (obj == 0) {
        return;
    }
    node = (uint64_t *)*container;
    if (((ulong)(node + 0x3ffe73ee90UL) >> 7) < 0x40bUL) {
        tag = (ulong)*(ushort *)((obj >> 10) & 0xffffffff0UL) & 0x3ffUL;
        table = &refcount_hash_table + tag * 0xc0UL;   /* &DAT_c608b80 + tag*0xc0 (8B elems) */
        h = (ulong)((long)(node + 0x3ffe73ee90UL) * 0x1555556UL) >> 0x1e;
        if (((*(uint32_t *)(zone_type_table + (h & 0x3fffffffcUL)) & 0x600UL) != 0x200UL) &&
            (table != node)) {
            idx = container[7] + 0x1fff39f7480UL;
            if (0x2057fUL < idx) {
                kernel_panic_e((void *)container[7]);   /* FUN_fffffe000c0ea524, noreturn */
            }
            slot = zone_type_table + ((idx * 0x1555556UL >> 0x1e) & 0x3fffffffcUL);
            if ((((ulong)slot ^ 0xfffffe0007d800b0UL) & 0xffc0000000000000UL) != 0) {
                slot = (uint8_t *)(((ulong)slot & 0xffffffffffffUL) | 0xc8a2000000000000UL);
            }
            if (*(short *)(slot + 2) == *(short *)(zone_type_table + 2 + tag * 4UL)) {
                node = (uint64_t *)*table;
                container = table;
            }
            else {
                container = (uint64_t *)container[6];
                node = (uint64_t *)*container;
            }
        }
        handle = container[1];
        key = *(ushort *)((ulong)node + 0x34);
        refcount_table_get((void *)obj, key);   /* FUN_fffffe000b758d80 */
        refcount_table_dec(node, handle, (void *)obj, key);   /* FUN_fffffe000b85d440 */
        return;
    }
    kernel_panic_e((void *)node);   /* FUN_fffffe000c0ea524, noreturn */
}

/* FUN_fffffe000b8af98c @ 0xfffffe000b8af98c   (est. kernel_refcount_inc)
 * Ghidra: void FUN_fffffe000b8af98c(ulong param_1)
 * Kernel refcount increment with zone-magic (tag 0xf) validation. Validates
 * the object zone + address-range bound, then increments the refcount at
 * obj+0x88, panicking c0f86a4 on overflow.
 * Confidence: high
 * Notes: tag-0xf validation panic c0eae24(0xf); overflow panic c0f86a4. */
void
kernel_refcount_inc(ulong obj)
{
    ulong probe;
    int old;                              /* iVar1 */

    if (obj != 0) {
        probe = obj | 0xf00000000000000UL;
        if ((0xffffffffffffff1fUL < probe) ||
            (probe != 0xffffffffffffff20UL) ||
            ((*(ushort *)((obj >> 10) & 0xffffffff0UL) & 0x3ffUL) != 0xfUL)) {
            panic_dyn(0xf);               /* FUN_fffffe000c0eae24, noreturn */
        }
        old = *(int *)(obj + 0x88);
        *(int *)(obj + 0x88) = old + 1;
        if ((old + 0xf0000001U) < 0xf0000002U) {
            kernel_panic_a();             /* FUN_fffffe000c0f86a4, noreturn */
        }
    }
}

/* FUN_fffffe000b78cc20 @ 0xfffffe000b78cc20   (est. kernel_obj_release)
 * Ghidra: void FUN_fffffe000b78cc20(char *param_1)
 * Object release dispatched on the object's first type byte at refcount 1:
 * non-zero dispatches to the VM object release (b794224), zero to the region
 * object release (b7961a0). Called from zfree_waitq at refcount == 1.
 * Confidence: medium
 * Notes: dispatch reads *(byte*)obj; callees b794224 / b7961a0 stubbed. */
void
kernel_obj_release(ulong obj)
{
    if (*(char *)obj != '\0') {
        obj_release_vm();                 /* FUN_fffffe000b794224 */
        return;
    }
    obj_release_region();                 /* FUN_fffffe000b7961a0 */
    return;
}

/* FUN_fffffe000b78fd40 @ 0xfffffe000b78fd40   (est. kernel_region_lock)
 * Ghidra: void FUN_fffffe000b78fd40(ulong param_1)
 * Region reference lock. When the region passes the tag-0x15 zone validation
 * it increments the region refcount at region+4 (overflow panic c0f86a4);
 * otherwise it panics c0eae24(0x15). Used by hv_el2_guest_fault_retry to hold
 * a region reference.
 * Confidence: medium
 * Notes: the decompiler rendered the range check as an always-false
 *   conjunction (`X < 0xffffffffffffff70 && X == 0xffffffffffffff70`); kept
 *   verbatim (artifact). Refcount here is at +0x4 (region), not +0x88. */
void
kernel_region_lock(ulong region)
{
    ulong probe;
    int old;                              /* iVar1 */

    probe = region | 0xf00000000000000UL;
    if ((probe < 0xffffffffffffff70UL) &&
        (probe == 0xffffffffffffff70UL) &&
        ((*(ushort *)((region >> 10) & 0xffffffff0UL) & 0x3ffUL) == 0x15UL)) {
        old = *(int *)(region + 4);
        *(int *)(region + 4) = old + 1;
        if ((old + 0xf0000001U) < 0xf0000002U) {
            kernel_panic_a();             /* FUN_fffffe000c0f86a4, noreturn */
        }
        return;
    }
    panic_dyn(0x15);                      /* FUN_fffffe000c0eae24, noreturn */
}

/* FUN_fffffe000b7e0f30 @ 0xfffffe000b7e0f30   (est. kernel_obj_lookup)
 * Ghidra: undefined8 FUN_fffffe000b7e0f30(undefined8 param_1,undefined8 param_2,
 *                                         uint param_3,undefined8 *param_4)
 * Container/object-registry lookup by handle + type. Runs the lookup core
 * (b78d064) with type 0x13; on a clean return it accepts the object when the
 * requested type is the wildcard 0xff, the name is too short (<2 bytes), or
 * the name's type byte matches; otherwise it releases the found object via
 * zfree_waitq (b793cf4) and returns error 0x14. On any non-clean core result
 * the out slot is cleared and the core status returned.
 * Confidence: high
 * Notes: wraps kernel_obj_lookup_core (b78d064) with (0x13,1,7,0); release
 *   of the found object via zfree_waitq (b793cf4) — its arg is dropped in the
 *   render and reconstructed as *out; error code 0x14. */
ulong
kernel_obj_lookup(ulong container, ulong handle, uint type, char **out)
{
    ulong rc;                             /* uVar1 */

    rc = kernel_obj_lookup_core(container, handle, 0x13, 1, 7, 0, (ulong *)out);
    if ((int)rc == 0) {
        if ((type == 0xff) ||
            (((char *)*out + 1) < (char *)0x2) ||
            ((byte)**out == (byte)type)) {
            return 0;
        }
        zfree_waitq((ulong)*out);         /* FUN_fffffe000b793cf4; arg dropped by decompiler */
        rc = 0x14;
    }
    *out = 0;
    return rc;
}

/* FUN_fffffe000b78d064 @ 0xfffffe000b78d064   (est. kernel_obj_lookup_core)
 * Ghidra: undefined8 FUN_fffffe000b78d064(undefined8 param_1,undefined8 param_2,
 *         undefined8 param_3,uint param_4,undefined8 param_5,undefined8 param_6,
 *         undefined8 param_7)
 * Lookup core. Finds the container entry by (container,handle) via
 * container_entry_find (b7968e8), then runs the container lookup core
 * (b798c24) with flags `(param_4 & 1) | 2`, releasing the container lock
 * (b7f7dd8) and post-processing the aux/extra out-regions (b798b38/b798bb8).
 * The b798c24 core is where the type<=0x15 table (DAT_7d78658), live bit
 * 0x10000, present bits 0x700, and SoftwareBreakpoint(0xbffc) asserts live.
 * Confidence: high
 * Notes: callee chain b7968e8 -> b798c24 -> b7f7dd8/b798b38/b798bb8 stubbed;
 *   the 16-byte aux (auStack_68) is modeled as hv_u128_t; param_6 is stored
 *   to local_48 and unused. */
ulong
kernel_obj_lookup_core(ulong container, ulong handle, ulong type, uint flags,
                       ulong arg5, ulong arg6, ulong *out)
{
    ulong rc;                             /* uVar1 */
    ulong entry;                          /* local_70 */
    hv_u128_t aux;                        /* auStack_68 [16] */
    ulong extra;                          /* local_58 */
    ulong arg6_saved;                     /* local_48 */
    ulong stack_50;                       /* uStack_50 */

    entry = 0;
    stack_50 = 0;
    extra = 0;
    arg6_saved = arg6;
    rc = container_entry_find(container, handle, &entry);   /* FUN_fffffe000b7968e8 */
    if ((int)rc == 0) {
        rc = container_lookup_core(container, handle, type, (flags & 1) | 2,
                                   arg5, entry, out, &aux, &extra);  /* FUN_fffffe000b798c24 */
        container_lock_release(container);   /* FUN_fffffe000b7f7dd8 */
        container_post_waitq(&aux, handle);  /* FUN_fffffe000b798b38 */
        container_post_ref(&extra);          /* FUN_fffffe000b798bb8 */
    }
    return rc;
}

/* FUN_fffffe000b7e16f0 @ 0xfffffe000b7e16f0   (est. kernel_fault_post)
 * Ghidra: undefined8 FUN_fffffe000b7e16f0(undefined8 param_1,undefined8 param_2,
 *         ulong param_3,undefined8 param_4,undefined4 *param_5)
 * Posts a fault record. Clears *out (param_5), looks up a fault record
 * (b78a2a4) with the fault type flags masked by 0xffffffdfffffffff, validates
 * it (b78a500), and when valid sets *out=1, computes a per-CPU-adjusted flag
 * word (reading tpidr_el1+0xc0 bit 0x800), posts it (b78aa38), releasing the
 * record (b7867a4) on post failure. Invalid records are freed (b7864d0).
 * Called by hv_el2_guest_fault_retry as (rec, size, type, 0, 0).
 * Confidence: high
 * Notes: per-CPU flag adjustment reads tpidr_el1 (per-cpu base); callees
 *   b78a2a4/b78a500/b78aa38/b7867a4/b7864d0 stubbed. NOTE: hv_el2.h declares
 *   the 4th arg `int` and 5th arg `int` returning `int`; the fresh decompile
 *   has param4 uint64_t, param5 int* (out), return uint64_t — header needs
 *   correcting. */
ulong
kernel_fault_post(void *rec, ulong size, ulong type, ulong arg4, int *out)
{
    ulong fault;                          /* local_48 */
    ulong rc;                             /* uVar4 */
    ulong cpu;                            /* lVar2 (tpidr_el1) */
    ulong flags;                          /* uVar1 */

    if (out != (int *)0x0) {
        *out = 0;
    }
    fault = 0;
    rc = fault_record_lookup(rec, size, type & 0xffffffdfffffffffUL, &fault);  /* FUN_fffffe000b78a2a4 */
    if ((int)rc == 0) {
        rc = fault_record_validate(fault);   /* FUN_fffffe000b78a500 */
        if ((int)rc == 0) {
            if (out != (int *)0x0) {
                *out = 1;
            }
            cpu = tpidr_el1;
            flags = ((ulong)((uint)type >> 1 ^ 0xffffffffUL) & 0x40000UL) |
                    (type & 0xffffffdfffffffffUL);
            if ((*(ushort *)(cpu + 0xc0) & 0x800) != 0) {
                flags = type & 0xffffffdffffbffffUL;
            }
            rc = fault_record_post(fault, flags, arg4);   /* FUN_fffffe000b78aa38 */
            if ((int)rc != 0) {
                fault_record_release(fault, 0);   /* FUN_fffffe000b7867a4 */
            }
        }
        else {
            fault_record_free(fault);   /* FUN_fffffe000b7864d0 */
        }
    }
    return rc;
}
