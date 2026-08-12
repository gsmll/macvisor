/* Recreated from cl4_kernel.raw (cL4 Secure Kernel, arm64e, image base 0) —
 * the cL4 microkernel (GL1), "cL4 (679.100.61)".
 * Ground truth: Ghidra FUN_ names + addresses in program cl4_kernel.raw.
 * Slice 16: 0xdd9e8-0xe0824, caps region — the EC (Exclave) memory-region
 * registration / teardown subsystem (EC = execution context / exclave).
 * All names are estimates unless string-matched. */

#include <stdint.h>
#include <stddef.h>

/* ------------------------------------------------------------------ *
 * Out-of-slice cL4 helpers (extern; bodies owned by the slice that
 * contains them). Exact Ghidra FUN_ names retained.
 * ------------------------------------------------------------------ */

/* FUN_0006b2ec — cL4 guarded-entry prologue: save caller context / enter the
 * guarded (GENTER) region. Always paired with FUN_000651bc. */
extern void cL4_enter_guard(void);
/* FUN_000651bc — cL4 guarded-exit epilogue: restore context (GEXIT); returns
 * a condition flag describing whether the exit is clean (Z set). */
extern void cL4_exit_guard(void);
/* FUN_0011d7e8 — cL4 fatal: noreturn error/panic path taken when the guarded
 * exit flag is clear. */
extern void cL4_fatal(void) __attribute__((noreturn));
/* FUN_00086410 — read the caller's capability/feature bitmask (bits tested:
 * 3,4,5,0xc,0x10,0x13 = which EC/memory subsystems are present). */
extern unsigned int cL4_cap_feature_mask(void);
/* FUN_0006e6dc — read the last error / status word set by the preceding call
 * (nonzero = failure). */
extern int cL4_last_error(void);
/* FUN_0036a940 — push/save the current error/return value; returns the
 * previous one (used to propagate errors across calls). */
extern unsigned long cL4_save_result(void);
/* FUN_0036986c — fetch the current error/status result word. */
extern unsigned long cL4_get_result(void);
/* FUN_00085b68 — record an error result (2 8-byte words) for return. */
extern unsigned long cL4_set_result(unsigned long lo, unsigned long hi);
/* FUN_0001a1c8 — bitwise-and/check helper used to test capability masks. */
extern unsigned long cL4_mask_test(unsigned long);
/* FUN_0036a1a0 — acquire/release a reference on the global at `addr`
 * (lock/unlock guard around the mutable EC globals). */
extern void cL4_global_lock(unsigned long addr, void *saved, unsigned long mode, unsigned long unused);
/* FUN_0036a20c — release the guard taken by FUN_0036a1a0. */
extern void cL4_global_unlock(void *saved);
/* FUN_0036b118 / FUN_0036b270 — object refcount release/acquire (LO style). */
extern void cL4_release(unsigned long obj);
extern void cL4_acquire(unsigned long obj);
/* FUN_0039a128 — object-lookup by capability pointer; resolves `cap` (or its
 * alternative `alt` when *cap == -1). */
extern unsigned long cL4_cap_lookup(unsigned long *cap, unsigned long alt);
/* FUN_0014b644 — read a kernel page-size / granule count for selector `sel`
 * (sel 3 used for page-granule arithmetic). */
extern unsigned long cL4_pagesize(unsigned long sel);
/* FUN_00153270 / FUN_0015327c / FUN_00153264 — per-CPU / per-domain state
 * word pointers (capability masks for EC memory regions A and B). */
extern unsigned long *cL4_regionA_mask(void);
extern unsigned long *cL4_regionB_mask(void);
extern unsigned long *cL4_regionC_mask(void);
/* FUN_001071f4 / FUN_00107200 / FUN_0010720c — per-region present-flag
 * pointers (32-bit). */
extern unsigned int *cL4_regionA_present(void);
extern unsigned int *cL4_regionB_present(void);
extern unsigned int *cL4_regionC_present(void);
/* FUN_00167c48 / 3c / 60 / 54 — 8-bit subsystem-enable flags (four EC
 * sub-features). */
extern unsigned char *cL4_sysflag0(void);
extern unsigned char *cL4_sysflag1(void);
extern unsigned char *cL4_sysflag2(void);
extern unsigned char *cL4_sysflag3(void);
/* FUN_000e1458 — helper: read the current object's feature/cap mask register. */
extern unsigned int cL4_obj_feature_mask(void);
/* FUN_000e1640 / FUN_000e164c — per-region helper: refresh/check a region's
 * capability word and return it (or its low byte). */
extern unsigned long cL4_region_refresh(unsigned long region);
extern unsigned char cL4_region_refresh_byte(unsigned long region);
/* FUN_000e1558 / FUN_000e15c8 / FUN_000e15a4 / FUN_000e15d8 / FUN_000e1514 /
 * FUN_000e15f4 / FUN_000e15b8 / FUN_000e1430 / FUN_000e14e0 / FUN_000e1498 /
 * FUN_000e1470 / FUN_000e14b8 / FUN_000e14f0 / FUN_000e1584 / FUN_000e1600 /
 * FUN_000e15e4 / FUN_000e15f4 / FUN_000e16e8 / FUN_000e1528 / FUN_000e1540 /
 * FUN_000e1024 / FUN_000e100c / FUN_000e10b8 / FUN_000e0fe4 / FUN_000e0ff8 /
 * FUN_000e166c / FUN_000e0fcc / FUN_000e1658 / FUN_000e166c
 * — out-of-slice EC subroutines (this slice's helpers live just above
 * 0xe0824 / owned by slice 17). */
extern void cL4_ec_sub1558(void);
extern void cL4_ec_sub15c8(void);
extern void cL4_ec_sub1458(void);
extern void cL4_ec_sub1640(void);
extern void cL4_ec_sub15a4(unsigned long v);
extern void cL4_ec_sub15d8(void);
extern void cL4_ec_sub1514(void);
extern void cL4_ec_sub15f4(void);
extern void cL4_ec_sub15b8(void);
extern void cL4_ec_sub1430(void);
extern void cL4_ec_sub14e0(unsigned long a, void *b);
extern void cL4_ec_sub1498(void);
extern void cL4_ec_sub1470(void);
extern void cL4_ec_sub14b8(void);
extern void cL4_ec_sub14f0(const char *msg);
extern void cL4_ec_sub1584(void);
extern void cL4_ec_sub1600(unsigned int code);
extern unsigned long cL4_ec_sub15e4(void);
extern unsigned long cL4_ec_sub1528(unsigned long);
extern unsigned long cL4_ec_sub1540(unsigned long, unsigned long, unsigned long);
extern unsigned long cL4_ec_sub1024(unsigned long, unsigned long);
extern unsigned long cL4_ec_sub100c(unsigned long, unsigned long, unsigned char);
extern void cL4_ec_sub10b8(unsigned long *a, unsigned long *b);
extern unsigned long cL4_ec_sub0fe4(unsigned long, unsigned long, unsigned long *, unsigned long *);
extern unsigned long cL4_ec_sub0ff8(unsigned long, unsigned long, unsigned long *, unsigned long *);
extern void cL4_ec_sub166c(void);
extern void cL4_ec_sub0fcc(void);
extern void cL4_ec_sub1658(void);
/* FUN_000e14f0(+0x10) — print/format an error message string. */
extern void cL4_ec_printmsg(const char *msg);
/* FUN_001afa84 — noreturn fatal error printer (variadic, args as given). */
extern void cL4_ec_fatal(void) __attribute__((noreturn));
/* FUN_000027e8 / FUN_0000276c — task/context helpers (suspend/abort). */
extern unsigned long cL4_ctx_get(void);
extern void cL4_ctx_abort(unsigned long *ctx, unsigned long *msg, unsigned long *fmt);
/* FUN_0006a4c0 / FUN_0008644c / FUN_0008647c / FUN_000864f0 / FUN_00086434 /
 * FUN_000864c4 — cL4 capability-word constructors / vtable invoke helpers. */
extern unsigned long cL4_cap_build(unsigned long *slot, unsigned long word);
extern unsigned long cL4_cap_invoke(unsigned long w);
extern unsigned long cL4_cap_invoke7(unsigned long a, unsigned long b, unsigned long c, void *d, unsigned long *e);
extern unsigned long cL4_cap_invoke4(unsigned long a, unsigned long b, unsigned long c, unsigned long d);
extern void cL4_cap_store4(unsigned long a, unsigned long b);
extern void cL4_cap_set4(unsigned int a, unsigned long b, unsigned long c);
/* FUN_0014aea4 / FUN_00077070 / FUN_00002534 / FUN_00167f44 — object type
 * descriptors / allocation. */
extern unsigned long cL4_objdesc(unsigned long a, unsigned long b);
extern void cL4_obj_setup(unsigned long param, unsigned long *obj);
extern unsigned long cL4_typedesc(unsigned long str, unsigned long *tab);
extern unsigned long cL4_obj_alloc(void);
/* FUN_0007c0e0 / FUN_0009455c / FUN_00084100 / FUN_000026e8 / FUN_0008396c /
 * FUN_00117cc4 — generic object accessor helpers (lock/unlock + field). */
extern void cL4_obj_access(unsigned long *slot, void *saved);
extern void cL4_obj_read(unsigned long *slot);
extern unsigned long cL4_obj_readval(unsigned long *slot);
extern void cL4_obj_dtor(unsigned long *slot);
extern void cL4_obj_field3(unsigned long a, unsigned long b, unsigned char c);
extern void cL4_copy_to_user(unsigned long param, void *buf, unsigned int kind);
/* FUN_0003d2b8 — invoke an operation with 4 args. */
extern void cL4_op4(unsigned long a, unsigned long b, unsigned long c, unsigned long d);
/* FUN_002a4ab4 / thunk_FUN_002acbb8 / FUN_00027724 / FUN_003a25d4 /
 * FUN_00205844 — kernel-printf machinery (panic/error formatting). */
extern void cL4_panic_fmt(unsigned int code);
extern void cL4_panic_str(unsigned long a, unsigned long b);
extern unsigned long cL4_panic_obj(unsigned long fmt);
extern void cL4_panic_end(void);
extern void cL4_report(unsigned long *a, unsigned long *b, unsigned long c, unsigned long d, unsigned long e);
/* FUN_00082524 / FUN_0009e18c — memory-region allocation bookkeeping. */
extern void cL4_alloc_pages(unsigned long pages, unsigned long count, unsigned long mode);
extern void cL4_page_commit(unsigned long *tbl, unsigned long index);

/* EC memory-region object globals. */
extern unsigned long cL4_ec_regA_word;    /* _DAT_006ad9d0 : granule count / page size for region A */
extern unsigned long cL4_ec_regB_word;    /* _DAT_006ad9d8 : region B */

/* Forward declarations (defined in this file). */
void ec_region_setup(unsigned long a, unsigned long b);
void ec_region_slot_setup(unsigned long a);
extern unsigned long cL4_ec_typeinfo;     /* 0x6512e0 : EC region type info pointer */
extern unsigned long cL4_ec_global;       /* 0x6513c8 : mutable EC region global (guard) */
extern unsigned long cL4_ec_globalB;      /* 0x6513d0 */
extern unsigned long cL4_ec_globalC;      /* 0x6513d8 */
extern unsigned long cL4_ec_globalD;      /* 0x6513e0 */

/* EC memory-region object (the `self` at x20 in most of this file).
 * Offsets observed: +0x10 link/state, +0x18 size/refcount, +0x20/+0x28/+0x30
 * 16-byte memattr/param triple, +0x28 name, +0x38 vtable/next. */
struct ec_mem_region {
    unsigned long *vtable;    /* *(long*)*x20 : dispatch table */
    unsigned long pad;
    unsigned long link;       /* +0x10 */
    unsigned long size;       /* +0x18 */
    unsigned long param_a;    /* +0x20 */
    unsigned long param_b;    /* +0x28 */
    unsigned char param_c;    /* +0x30 */
    unsigned long next;       /* +0x38 */
};

/* ------------------------------------------------------------------ *
 * Functions
 * ------------------------------------------------------------------ */

/* Small helper: fetch the method pointer at vtable-relative offset `off`
 * from an object whose first word is the vtable pointer (defined later).
 * Forward-declared here because several functions below use it. */
static void *ec_vt_method(struct ec_mem_region *self, unsigned long off);

/* FUN_000dd9e8 @ 0x000dd9e8   (est. ec_region_dtor_wrap_a)
 * Ghidra: void FUN_000dd9e8(void)
 * Thin wrapper: runs the out-of-slice EC-memory-region teardown helper
 * FUN_000dd6c8 (owned by slice 15). No arguments, no return.
 * Confidence: high
 * Notes: tail call to FUN_000dd6c8 (0xdd6c8, below slice). */
void ec_region_dtor_wrap_a(void)
{
    /* FUN_000dd6c8 (slice 15): EC region destructor. */
    extern void FUN_000dd6c8(void);
    FUN_000dd6c8();
}

/* FUN_000dd9fc @ 0x000dd9fc   (est. ec_region_dtor_wrap_b)
 * Ghidra: void FUN_000dd9fc(void)
 * Thin wrapper: runs the out-of-slice EC helper FUN_000dd75c (slice 15).
 * Confidence: high */
void ec_region_dtor_wrap_b(void)
{
    extern void FUN_000dd75c(void);
    FUN_000dd75c();
}

/* FUN_000dda68 @ 0x000dda68   (est. ec_region_typeinfo)
 * Ghidra: undefined1 [16] FUN_000dda68(void)
 * Returns a 16-byte value formed from the constant EC-region type-info
 * pointer 0x6512e0 (zero-extended into the hi word). Used to identify the
 * EC memory-region object class.
 * Confidence: medium
 * Notes: ZEXT816(0x6512e0) -> {lo=0x6512e0, hi=0}. */
unsigned long ec_region_typeinfo_lo(void)
{
    return cL4_ec_typeinfo;
}

/* FUN_000dda78 @ 0x000dda78   (est. ec_region_section_cap_type)
 * Ghidra: ulong FUN_000dda78(ulong,long,char)
 * Classifies a (name_lo, name_hi, kind) triple into an EC memory-region
 * capability type. Recognises the Mach-O section-name encodings:
 *   "__TEXT"   -> 0x10
 *   "__DATA" / "__DATA_C" -> 0x11
 *   "__LINKED" -> 0x12
 * Returns 0xf for anything unrecognised, 0xc for kind==0, and a per-index
 * bit pattern for kind==2 (indexed table). The name words are byte-reversed
 * Mach-O section constants.
 * Confidence: medium
 * Notes: name constants 0x545845545f5f="__TEXT", 0x415441445f5f="__DATA",
 *   0x435f415441445f5f="__DATA_C", 0x44454b4e494c5f5f="__LINKED";
 *   FUN_000e15e4 consulted for the alternative encodings. */
unsigned long ec_region_section_cap_type(unsigned long name_lo, long name_hi, char kind)
{
    unsigned long result;

    if (kind == '\0') {
        result = 0xc;
    } else if (kind == '\x01') {
        if ((name_lo == 0x545845545f5fULL && name_hi == -0x1a00000000000000LL) ||
            (cL4_ec_sub15e4() & 1) != 0) {
            result = 0x10;
        } else if (((name_lo == 0x415441445f5fULL && name_hi == -0x1a00000000000000LL) ||
                    (cL4_ec_sub15e4() & 1) != 0) ||
                   (name_lo == 0x435f415441445f5fULL && name_hi == -0x13ffffffabacb1b1LL) ||
                   (cL4_ec_sub15e4() & 1) != 0) {
            result = 0x11;
        } else {
            result = 0x12;
            if (name_lo != 0x44454b4e494c5f5fULL || name_hi != -0x15ffffffffffabb7LL) {
                unsigned int t = 0x12;
                if ((cL4_ec_sub15e4() & 1) == 0)
                    t = 0xf;
                result = t;
            }
        }
    } else if (kind != '\x02' || name_hi != 0 ||
               (unsigned long)(name_hi - 1) < (unsigned long)(7 < name_lo)) {
        result = 0xf;
    } else {
        result = 0xff07fdff0f0f0f0fULL >> ((name_lo & 7) << 3);
    }
    return result;
}

/* FUN_000ddbc4 @ 0x000ddbc4   (est. ec_region_presence_flags)
 * Ghidra: uint FUN_000ddbc4(ulong)
 * Given a capability-mask `mask`, reports which EC memory regions are
 * present/absent. Reads the region A and region B present-mask words; the
 * result is 0 if a region is absent, 8 (bit 3) if present, plus 0x10 (bit 4)
 * OR'd when region B is present.
 * Confidence: medium
 * Notes: reads *cL4_regionA_mask() and *cL4_regionB_mask() masked against
 *   ~mask. */
unsigned int ec_region_presence_flags(unsigned long mask)
{
    unsigned long *pa = cL4_regionA_mask();
    unsigned int r = 8;
    if ((*pa & ~mask) != 0)
        r = 0;
    {
        unsigned long *pb = cL4_regionB_mask();
        unsigned int rb = r | 0x10;
        if ((*pb & ~mask) != 0)
            rb = r;
        return rb;
    }
}

/* FUN_000ddc0c @ 0x000ddc0c   (est. ec_region_ctor_save)
 * Ghidra: undefined8 FUN_000ddc0c(undefined8,undefined8)
 * Saves the previous result via cL4_save_result, then invokes the EC
 * memory-region constructor FUN_000dfd3c (in this slice) with the two
 * arguments. Returns the previously saved result (error propagation).
 * Confidence: medium */
unsigned long ec_region_ctor_save(unsigned long a, unsigned long b)
{
    unsigned long saved = cL4_save_result();
    ec_region_setup(a, b);
    return saved;
}

/* FUN_000ddc5c @ 0x000ddc5c   (est. ec_region_init_present_masks)
 * Ghidra: ulong FUN_000ddc5c(uint)
 * Initialises the EC-memory-region present-mask words from the accumulated
 * capability mask `mask`. For each of the three regions (A/B/C), if its
 * present flag is clear, OR `mask` into that region's stored word so the
 * region is marked present. Returns the union of the three words.
 * Confidence: medium
 * Notes: builds up uVar1 across FUN_001071f4/00200/020c present flags and
 *   FUN_00153264/70/7c mask words. */
unsigned long ec_region_init_present_masks(unsigned int mask)
{
    unsigned long acc = cL4_mask_test(0);

    if ((*cL4_regionA_present() & (mask ^ 0xffffffffu)) == 0) {
        unsigned long *w = cL4_regionC_mask();
        unsigned long v = *w;
        acc = cL4_mask_test(v);
        cL4_mask_test(acc & acc);
        acc = cL4_mask_test(v | acc);
    }
    if ((*cL4_regionB_present() & (mask ^ 0xffffffffu)) == 0) {
        unsigned long *w = cL4_regionA_mask();
        unsigned long v = *w;
        cL4_mask_test(cL4_mask_test(v));
        acc = cL4_mask_test(v | acc);
    }
    if ((*cL4_regionC_present() & (mask ^ 0xffffffffu)) == 0) {
        unsigned long *w = cL4_regionB_mask();
        unsigned long v = *w;
        cL4_mask_test(cL4_mask_test(v));
        acc = cL4_mask_test(v | acc);
        return acc;
    }
    return acc;
}

/* FUN_000ddd54 @ 0x000ddd54   (est. ec_region_mode_switch)
 * Ghidra: void FUN_000ddd54(void)
 * Branches on the caller's mode byte (w3): if (mode+5) < 0x19 invoke the
 * 0xe1558 helper, otherwise the 0xe15c8 helper. Selects one of two EC
 * region-handling modes.
 * Confidence: low
 * Notes: uses un-decoded input register w3. */
void ec_region_mode_switch(void)
{
    /* in_w3: caller mode byte; not recoverable as a C param in decompile. */
    if ((unsigned char)(/* in_w3 */ 0 + 5u) < 0x19)
        cL4_ec_sub1558();
    else
        cL4_ec_sub15c8();
}

/* FUN_000ddd6c @ 0x000ddd6c   (est. ec_region_guard_op_a)
 * Ghidra: void FUN_000ddd6c(void)
 * Guarded EC operation: enters the guard, reads the caller's feature mask,
 * and returns cleanly; on a failing feature/state check (mask word negative)
 * trips a SoftwareBreakpoint(1) fatal, and on a dirty guard exit calls the
 * noreturn fatal path. Skeleton of the shared EC-region guard wrapper.
 * Confidence: low
 * Notes: SoftwareBreakpoint(1,0xdddb0); FUN_000651bc exit flag gates
 *   FUN_0011d7e8. */
void ec_region_guard_op_a(void)
{
    cL4_enter_guard();
    cL4_ec_sub1458();
    cL4_cap_feature_mask();
    /* local_30<0 -> SoftwareBreakpoint(1,0xdddb0) fatal */
    if (0 < 0) { /* decompiler: local_30 (feature word) < 0 */ }
    cL4_exit_guard();
    /* if (!ZR) cL4_fatal(); */
}

/* FUN_000dddb4 @ 0x000dddb4   (est. ec_region_guard_op_b)
 * Ghidra: void FUN_000dddb4(void)
 * Mirror of ec_region_guard_op_a with a distinct breakpoint address
 * (0xdddf8). Same guarded EC-region skeleton.
 * Confidence: low
 * Notes: SoftwareBreakpoint(1,0xdddf8). */
void ec_region_guard_op_b(void)
{
    cL4_enter_guard();
    cL4_ec_sub1458();
    cL4_cap_feature_mask();
    if (0 < 0) { /* SoftwareBreakpoint(1,0xdddf8) */ }
    cL4_exit_guard();
    /* if (!ZR) cL4_fatal(); */
}

/* FUN_000dddfc @ 0x000dddfc   (est. ec_region_present_state)
 * Ghidra: undefined8 FUN_000dddfc(void)
 * Reads the caller's feature mask; if bit 3 (region A) is set, refreshes the
 * A mask word via cL4_region_refresh; if bit 4 (region B) is set, refreshes
 * the B mask word. Returns the accumulated refreshed mask.
 * Confidence: medium
 * Notes: uses cL4_regionA_mask()/cL4_regionB_mask() + FUN_000e1640. */
unsigned long ec_region_present_state(void)
{
    unsigned int fm = cL4_cap_feature_mask();
    unsigned long acc = cL4_mask_test(0);
    if ((fm >> 3 & 1) != 0) {
        cL4_regionA_mask();
        cL4_ec_sub1640();
        acc = cL4_mask_test(acc);
    }
    if ((fm >> 4 & 1) != 0) {
        cL4_regionB_mask();
        cL4_ec_sub1640();
        acc = cL4_mask_test(acc);
    }
    return acc;
}

/* FUN_000dde7c @ 0x000dde7c   (est. ec_region_present_state_sub)
 * Ghidra: undefined8 FUN_000dde7c(uint)
 * Subset of ec_region_present_state driven by an explicit feature mask
 * argument: refreshes region A when bit 3 is set, region B when bit 4 is
 * set, returning the accumulated refreshed mask.
 * Confidence: medium */
unsigned long ec_region_present_state_sub(unsigned int fm)
{
    unsigned long acc = cL4_mask_test(0);
    if ((fm >> 3 & 1) != 0) {
        cL4_regionA_mask();
        cL4_ec_sub1640();
        acc = cL4_mask_test(acc);
    }
    if ((fm >> 4 & 1) == 0)
        return acc;
    cL4_regionB_mask();
    cL4_ec_sub1640();
    acc = cL4_mask_test(acc);
    return acc;
}

/* FUN_000ddedc @ 0x000ddedc   (est. ec_region_sysfeature_byte)
 * Ghidra: byte FUN_000ddedc(void)
 * Aggregates the four EC sub-feature enable bytes into a single byte. Reads
 * the caller's feature mask: bit 0xc -> sysflag0, bit 5 -> sysflag1, bit
 * 0x10 -> sysflag2, bit 0x13 -> sysflag3; the returned byte is the OR of the
 * enabled flags (0 if none of those bits are set).
 * Confidence: medium
 * Notes: sysflags at FUN_00167c48/3c/60/54. */
unsigned char ec_region_sysfeature_byte(void)
{
    unsigned int fm = cL4_cap_feature_mask();
    unsigned char b = 0;
    if ((fm >> 0xc & 1) != 0)
        b = *cL4_sysflag0();
    if ((fm >> 5 & 1) != 0)
        b = (unsigned char)(*cL4_sysflag1() | b);
    if ((fm >> 0x10 & 1) != 0)
        b = (unsigned char)(*cL4_sysflag2() | b);
    if ((fm >> 0x13 & 1) != 0)
        b = (unsigned char)(*cL4_sysflag3() | b);
    return b;
}

/* FUN_000ddf78 @ 0x000ddf78   (est. ec_region_cap_lookup_tbl)
 * Ghidra: void FUN_000ddf78(void)
 * Looks up the caller's EC-region capability in a 20-entry dispatch table.
 * Reads the feature-mask byte `k` (from a stack local); when (k+5) < 0x19 it
 * indexes tables at 0x4c29c0/0x4c2a88/0x4c2b50 by k, otherwise returns the
 * default triple {op=9, arg=0, mode=2}. Delivers the triple via the exit
 * helper; when (k+5)==0x18 it returns cleanly, else falls to fatal.
 * Confidence: medium
 * Notes: DAT_004c29c0 (op), DAT_004c2a88 (arg), DAT_004c2b50 (mode byte). */
void ec_region_cap_lookup_tbl(void)
{
    unsigned char k;
    cL4_enter_guard();
    cL4_ec_sub1458();
    cL4_cap_feature_mask();
    k = /* local_20 */ 0;
    if ((unsigned char)(k + 5u) < 0x19) {
        /* indexed: op=DAT_004c29c0[k], arg=DAT_004c2a88[k], mode=DAT_004c2b50[k] */
    } else {
        /* default op=9, arg=0, mode=2 */
    }
    /* FUN_000651bc exit with (op,arg,mode); if (k+5)!=0x18 cL4_fatal() */
}

/* FUN_000de000 @ 0x000de000   (est. ec_region_commit_fault)
 * Ghidra: void FUN_000de000(void)
 * Commit/fault path for an EC memory region. Reads a word from the object's
 * +0x30, rebuilds the capability slot at self+0x10 from the word at +0x28,
 * invokes the capability, publishes via the 0xe15d8 helper, runs a queued
 * callback, then the 0xe0fcc helper, and trips SoftwareBreakpoint(1,0xde200)
 * (noreturn). Most of the body's blocks were unreachable per Ghidra.
 * Confidence: low
 * Notes: "Removing unreachable block" x26; SoftwareBreakpoint(1,0xde200). */
void ec_region_commit_fault(void)
{
    extern unsigned long FUN_0008644c(unsigned long);
    extern void FUN_000e15d8(unsigned long);
    extern void FUN_000e0fcc(void);
    /* self = x20; word = *(self+0x30); cL4_cap_build(self+0x10, *(self+0x28)); */
    cL4_enter_guard();
    cL4_cap_build((unsigned long *)0 /* self+0x10 */, 0 /* *(self+0x28) */);
    /* FUN_0008644c(word) -> FUN_000e15d8 -> (*callback)() -> FUN_000e0fcc() */
    /* SoftwareBreakpoint(1,0xde200) noreturn */
}

/* FUN_000de208 @ 0x000de208   (est. ec_launcher_lookup)
 * Ghidra: void FUN_000de208(void)
 * EC launcher lookup/registration. Fetches a context, calls the +0x48
 * vtable method into a stack buffer; if the result marker byte is not -1 the
 * capability is stored (0x86434) and the launcher context is committed
 * (0x0276c with 0x6513e8 + string table 0x4c2870); otherwise it prints the
 * "InternalExclaveLauncher_Exclaves" message and enters the noreturn fatal.
 * Confidence: medium
 * Notes: string s_InternalExclaveLauncher_Exclaves_005c40e0+0x10. */
void ec_launcher_lookup(void)
{
    extern unsigned long FUN_000027e8(void);
    extern void FUN_00086434(unsigned long, unsigned long);
    extern void FUN_0000276c(unsigned long *, unsigned long, unsigned long *);
    /* buf[24] at stack; marker byte local_18 */
    cL4_ctx_get();
    /* (**(vtable+0x48))(buf) */
    if (/* local_18 */ 0 != -1) {
        /* FUN_00086434(a,b); FUN_0000276c(buf,0x6513e8,&DAT_004c2870) */
        return;
    }
    cL4_ec_printmsg("InternalExclaveLauncher_Exclaves");
    cL4_ec_fatal();
}

/* FUN_000de29c @ 0x000de29c   (est. ec_region_mask_presence)
 * Ghidra: uint FUN_000de29c(ulong)
 * Checks whether `mask` is fully present in the region A and B mask words.
 * Returns 8 if region A is present (mask bits all set), plus 0x10 when
 * region B is also present; 0 if region A is missing.
 * Confidence: medium */
unsigned int ec_region_mask_presence(unsigned long mask)
{
    long *pa = (long *)cL4_regionA_mask();
    long va = *pa;
    unsigned int r = 8;
    if ((cL4_mask_test(cL4_mask_test(va) & mask) & (unsigned long)pa) != va)
        r = 0;
    {
        long *pb = (long *)cL4_regionB_mask();
        long vb = *pb;
        unsigned int rb = r | 0x10;
        if (cL4_mask_test(cL4_mask_test(vb) & mask) != vb)
            rb = r;
        return rb;
    }
}

/* FUN_000de30c @ 0x000de30c   (est. ec_region_sysflag_mask)
 * Ghidra: uint FUN_000de30c(void)
 * Builds a bitmask from the four EC sub-feature enable bytes: bit 0x1800 for
 * sysflag0, 0x120 for sysflag1, 0x90800 for sysflag2, 0x10000 for sysflag3;
 * a flag contributes only when its byte is nonzero. Returns the union.
 * Confidence: medium
 * Notes: per-byte refresh via FUN_000e164c. */
unsigned int ec_region_sysflag_mask(void)
{
    unsigned int r = 0x1800;
    if ((cL4_region_refresh_byte(0) & 0xff) != 0) r = 0;
    {
        unsigned int t = r | 0x120;
        if ((cL4_region_refresh_byte(1) & 0xff) != 0) t = r;
        r = t | 0x90800;
        if ((cL4_region_refresh_byte(2) & 0xff) != 0) r = t;
        t = r | 0x10000;
        if ((cL4_region_refresh_byte(3) & 0xff) != 0) t = r;
        return t;
    }
}

/* FUN_000de388 @ 0x000de388   (est. ec_region_slot_save)
 * Ghidra: undefined8 FUN_000de388(undefined8)
 * Saves the previous result, then runs the EC slot-constructor FUN_000de3c8
 * with the argument. Returns the saved result.
 * Confidence: medium */
unsigned long ec_region_slot_save(unsigned long a)
{
    unsigned long saved = cL4_save_result();
    ec_region_slot_setup(a);
    return saved;
}

/* FUN_000de3c8 @ 0x000de3c8   (est. ec_region_slot_setup)
 * Ghidra: void FUN_000de3c8(undefined8)
 * EC region slot setup: fetches an object descriptor for (0x665f60,
 * 0x665cd8), stores it into the object's +0x38, then runs FUN_00077070 with
 * the argument into the object's +0x10 slot.
 * Confidence: medium */
void ec_region_slot_setup(unsigned long a)
{
    unsigned long d = cL4_objdesc(0x665f60, 0x665cd8);
    /* *(self+0x38) = d */
    cL4_obj_setup(a, (unsigned long *)0 /* self+0x10 */);
}

/* FUN_000de42c @ 0x000de42c   (est. ec_region_guard_check)
 * Ghidra: void FUN_000de42c(void)
 * Guarded EC check: enters guard, reads feature mask; if the feature word is
 * negative trips SoftwareBreakpoint(1,0xde478); if the second state word is
 * negative trips SoftwareBreakpoint(1,0xde47c); otherwise returns cleanly or
 * falls to the noreturn fatal on a dirty exit.
 * Confidence: low
 * Notes: SoftwareBreakpoint(1,0xde478 / 0xde47c). */
void ec_region_guard_check(void)
{
    cL4_enter_guard();
    cL4_ec_sub1458();
    cL4_cap_feature_mask();
    if (0 < 0) { /* SoftwareBreakpoint(1,0xde478) */ }
    if (0 <= 0) { /* ok */
        cL4_exit_guard();
        return;
    }
    /* SoftwareBreakpoint(1,0xde47c) */
}

/* FUN_000de480 @ 0x000de480   (est. ec_region_fatal_norelease)
 * Ghidra: void FUN_000de480(void)
 * Noreturn fatal: prints the "Fatal error" banner and the
 * "InternalExclaveLauncher_Exclaves" string via the variadic fatal printer
 * (FUN_001afa84) with code 0xd7. Never returns.
 * Confidence: high
 * Notes: strings s_Fatal_error_005accd0, s_InternalExclaveLauncher_Exclaves_005c40e0. */
void ec_region_fatal_norelease(void)
{
    cL4_ec_fatal();
}

/* FUN_000de4e4 @ 0x000de4e4   (est. ec_region_release_vaddrs)
 * Ghidra: void FUN_000de4e4(undefined8,undefined8,ulong,long,long)
 * Releases a set of EC memory-region virtual addresses back to the kernel.
 * Validates that `size` is an exact multiple of the page size
 * (FUN_0014b644(3)); if `region_list` is null, releases a single contiguous
 * [size] range via FUN_000e0fe4; otherwise iterates the region descriptor
 * list at region_list+0x20 (count at +0x10), computing each region's byte
 * offset (index * page) and invoking the 0xc0 vtable method to release each
 * range, faulting (SoftwareBreakpoint) on overflow/misalignment. Records any
 * error via FUN_00085b68 and returns.
 * Confidence: medium
 * Notes: SoftwareBreakpoint(1, 0xde6a0/4/8/b0/b4/ac); FUN_000e1430 + 0xe15b8
 *   error publish; FUN_0036986c final result. */
void ec_region_release_vaddrs(unsigned long a, unsigned long b, unsigned long size,
                              long base, long region_list)
{
    extern unsigned long FUN_000e0fe4(unsigned long, unsigned long, unsigned long *, unsigned long *);
    extern void FUN_000e1430(void);
    extern void FUN_000e15b8(void);
    unsigned long page, n, i;
    long lo, hi;

    cL4_enter_guard();
    cL4_ctx_get();
    page = (*(unsigned long (*)(void)) ec_vt_method(0, 0xc0))(); /* ctx vtable+0xc0: page size */
    if (page == 0) { /* SoftwareBreakpoint(1,0xde6ac) */ }
    n = (page != 0) ? size / page : 0;
    if (size != n * page) {
        cL4_ec_printmsg("Trying to release released vaddr");
        cL4_ec_fatal();
    }
    if (region_list == 0) {
        if ((long)size < 0) { /* SoftwareBreakpoint(1,0xde6b0) */ }
        lo = (long)size;
        if (base < 0) { /* SoftwareBreakpoint(1,0xde6b4) */ }
        hi = base;
        cL4_ec_sub0fe4(a, b, (unsigned long *)&lo, (unsigned long *)&hi);
        if (cL4_last_error() == 0) {
            /* success */
        } else {
            cL4_set_result(0, 0);
            cL4_ec_sub1430();
            cL4_ec_sub15b8();
        }
    } else {
        i = 0;
        n = *(unsigned long *)(region_list + 0x10);
        while (n != i) {
            unsigned long r = *(unsigned long *)(region_list + 0x20 + i * 8);
            unsigned long p = (*(unsigned long (**)(void))(/* ctx vtable */ 0 + 0xc0))();
            unsigned long off = i * p;
            if (i * p /* overflow hi */ != 0) { /* SoftwareBreakpoint(1,0xde6a0) */ }
            lo = (long)(size + i * p);
            if (/* carry */ (unsigned long)(size) > (unsigned long)(size + i * p)) {
                /* SoftwareBreakpoint(1,0xde6a4) */
            }
            if (lo < 0) { /* SoftwareBreakpoint(1,0xde6a8) */ }
            cL4_ec_sub0fe4(a, b, (unsigned long *)&lo, (unsigned long *)&r);
            i += 1;
        }
    }
    cL4_exit_guard();
}

/* FUN_000de6e8 @ 0x000de6e8   (est. ec_region_alloc)
 * Ghidra: undefined1 [16] FUN_000de6e8(undefined8,undefined8,long,long)
 * Allocates an EC memory region of `size` bytes at virtual `vaddr`. Validates
 * both are non-negative, invokes the region allocator FUN_000e0ff8, and
 * returns the 16-byte {result, status}. On failure records the error via
 * FUN_00085b68 and publishes via 0xe1430/0xe1658.
 * Confidence: medium
 * Notes: returns 16-byte pair (auVar4); SoftwareBreakpoint on negatives. */
unsigned long ec_region_alloc_lo(unsigned long a, unsigned long b, long size, long vaddr)
{
    extern unsigned long FUN_000e0ff8(unsigned long, unsigned long, unsigned long *, unsigned long *);
    extern void FUN_000e1658(void);
    long lo = size, hi = vaddr;
    unsigned long result;

    if (size < 0) { /* SoftwareBreakpoint(1,0xde794) */ }
    if (vaddr < 0) { /* SoftwareBreakpoint(1,0xde798) */ }
    cL4_ec_sub0ff8(a, b, (unsigned long *)&lo, (unsigned long *)&hi);
    if (cL4_last_error() != 0) {
        result = cL4_set_result(0, 0);
        cL4_ec_sub1430();
        cL4_ec_sub1658();
    }
    return /* auVar4._0_8_ */ 0;
}

/* FUN_000de79c @ 0x000de79c   (est. ec_region_query)
 * Ghidra: undefined1 [16] FUN_000de79c(undefined8,undefined8,undefined8)
 * Queries an EC memory region: combines the caller's feature mask with the
 * region-presence flags for `mask`, runs the capability query FUN_000864f0,
 * and returns the 16-byte {result, status}.
 * Confidence: medium */
unsigned long ec_region_query_lo(unsigned long a, unsigned long b, unsigned long mask)
{
    extern unsigned long FUN_000864f0(unsigned long, unsigned long, unsigned long);
    unsigned int fm = cL4_cap_feature_mask();
    unsigned int pf = ec_region_mask_presence(mask);
    unsigned long r = FUN_000864f0(a, b, pf | fm);
    if (cL4_last_error() != 0) {
        cL4_set_result(0, 0);
        cL4_ec_sub1430();
        cL4_ec_sub1658();
    }
    return r;
}

/* FUN_000de854 @ 0x000de854   (est. ec_region_register)
 * Ghidra: void FUN_000de854(long,long,undefined8,undefined8,undefined8,undefined8,ulong)
 * Registers a new EC memory region into the EC object. Computes the region
 * presence flags (0xde29c on param_3) and sysflag mask (0xde30c on param_4),
 * classifies the region's section name via 0xdda78 into a capability type,
 * then builds a capability word (1, or 0x4000001 when the name is zero) and
 * invokes the EC capability constructor FUN_0008647c. Publishes the result
 * via 0xe15d8/0x85b68/0xe1430/0xe15b8; records final result via 0x36986c.
 * Confidence: medium
 * Notes: local_98[0]=0x11 (kind); SoftwareBreakpoint on negative base/size. */
void ec_region_register(long base, long size, unsigned long a, unsigned long b,
                        unsigned long name_lo, unsigned long name_hi, unsigned long kind)
{
    extern unsigned long FUN_0008647c(unsigned long, unsigned long, unsigned long, void *, unsigned long *);
    unsigned int pf = ec_region_mask_presence(a);
    unsigned int sf = ec_region_sysflag_mask();
    unsigned char ctype;
    unsigned long capword;
    unsigned long out[2] = {0, 0};
    unsigned char lkind[8];

    if (size < 0) { /* SoftwareBreakpoint(1,0xde9a8) */ }
    ctype = (unsigned char)ec_region_section_cap_type(name_lo, name_hi, (char)kind);
    if (base < 0) { /* SoftwareBreakpoint(1,0xde9ac) */ }
    lkind[0] = 0x11;
    capword = (((kind & 0xff) == 0) & (name_lo != 0)) ? 1u : 0x4000001u;
    /* build slot at self+0x10 from *(self+0x28); invoke via 0x8644c; publish */
    FUN_0008647c(0, 0, pf | sf | capword, lkind, out);
    if (cL4_last_error() != 0) {
        cL4_ec_sub15d8();
        cL4_set_result(0, 0);
        cL4_ec_sub1430();
        cL4_ec_sub15b8();
    }
    cL4_exit_guard();
}

/* FUN_000de9b0 @ 0x000de9b0   (est. ec_region_unregister)
 * Ghidra: void FUN_000de9b0(undefined8,undefined8,undefined8)
 * Unregisters an EC memory region. Locks the global at 0x64e128, invokes the
 * removal operation FUN_0003d2b8, unlocks, and publishes the result.
 * Confidence: medium
 * Notes: lock guard via FUN_0036a1a0(0x64e128). */
void ec_region_unregister(unsigned long a, unsigned long b, unsigned long c)
{
    extern void FUN_0003d2b8(unsigned long, unsigned long, unsigned long, unsigned long);
    unsigned char saved[24];
    cL4_global_lock(0x64e128, saved, 0x20, 0);
    FUN_0003d2b8(a, b, 0x64e128, c);
    cL4_global_unlock(saved);
    if (cL4_last_error() != 0) {
        cL4_ec_sub15d8();
        cL4_set_result(0, 0);
        cL4_ec_sub1430();
        cL4_ec_sub15b8();
        cL4_get_result();
    }
}

/* FUN_000dea64 @ 0x000dea64   (est. ec_region_flag_set)
 * Ghidra: void FUN_000dea64(undefined4,undefined8,ulong)
 * Sets an EC region flag/capability word: calls FUN_000864c4 with mode 4
 * (or 0 when bit 0 of param_3 is set), then publishes the result.
 * Confidence: medium */
void ec_region_flag_set(unsigned int a, unsigned long b, unsigned long c)
{
    extern void FUN_000864c4(unsigned int, unsigned long, unsigned long);
    unsigned int mode = (c & 1) == 0 ? 4 : 0;
    FUN_000864c4(a, b, mode);
    if (cL4_last_error() != 0) {
        cL4_ec_sub15d8();
        cL4_set_result(0, 0);
        cL4_ec_sub1430();
        cL4_ec_sub15b8();
        cL4_get_result();
    }
}

/* FUN_000dead0 @ 0x000dead0   (est. ec_region_get_field)
 * Ghidra: undefined8 FUN_000dead0(void)
 * Returns the value stored in the EC object's +0x38 field (after a read
 * accessor FUN_00084100).
 * Confidence: medium */
unsigned long ec_region_get_field(void)
{
    cL4_obj_readval((unsigned long *)0 /* self+0x38 */);
    return 0; /* *(self+0x38) */
}

/* FUN_000deaf8 @ 0x000deaf8   (est. ec_region_set_field)
 * Ghidra: void FUN_000deaf8(undefined8)
 * Stores `val` into the EC object's +0x38 field under the access lock.
 * Confidence: medium */
void ec_region_set_field(unsigned long val)
{
    cL4_obj_access((unsigned long *)0 /* self+0x38 */, 0);
    /* *(self+0x38) = val */
}

/* FUN_000deb30 @ 0x000deb30   (est. ec_region_read_pair)
 * Ghidra: undefined1 [16] FUN_000deb30(void)
 * Reads the EC object's +0x38 field and returns the 16-byte pair
 * {handler=0x6f910, ptr=self+0x38} used as a callback closure.
 * Confidence: medium
 * Notes: LAB_0006f910 is the callback function pointer. */
unsigned long ec_region_read_pair_lo(void)
{
    cL4_obj_read((unsigned long *)0 /* self+0x38 */);
    return 0x6f910; /* auVar1._0_8_ = &LAB_0006f910 */
}

/* FUN_000deb74 / FUN_000deb78 @ 0xdeb74/0xdeb78   (est. ec_region_obj_dtor_a/b)
 * Ghidra: void FUN_000deb74(void)
 * Runs the object destructor FUN_000026e8 on the EC object's +0x10 slot.
 * Confidence: medium */
void ec_region_obj_dtor_a(void)
{
    cL4_obj_dtor((unsigned long *)0 /* self+0x10 */);
}

void ec_region_obj_dtor_b(void)
{
    cL4_obj_dtor((unsigned long *)0 /* self+0x10 */);
}

/* FUN_000deb94 / FUN_000deb98 @ 0xdeb94/0xdeb98   (est. ec_region_obj_dtor_extra_a/b)
 * Ghidra: void FUN_000deb94(void)
 * Object destructor on +0x10 followed by an extra teardown (FUN_0036b6ac).
 * Confidence: medium */
void ec_region_obj_dtor_extra_a(void)
{
    extern void FUN_0036b6ac(void);
    cL4_obj_dtor((unsigned long *)0 /* self+0x10 */);
    FUN_0036b6ac();
}

void ec_region_obj_dtor_extra_b(void)
{
    extern void FUN_0036b6ac(void);
    cL4_obj_dtor((unsigned long *)0 /* self+0x10 */);
    FUN_0036b6ac();
}

/* Small helper: fetch the method pointer at vtable-relative offset `off`
 * from the EC region object `self`. The object's first word (self[0]) is the
 * vtable pointer; the method address is stored at (vtable + off). */
static void *ec_vt_method(struct ec_mem_region *self, unsigned long off)
{
    unsigned long *vt = self ? (unsigned long *)self->vtable : 0;
    return (void *)*(unsigned long *)((unsigned char *)vt + off);
}

/* FUN_000debc0 @ 0x000debc0   (est. ec_region_vtable_c0)
 * Ghidra: void FUN_000debc0(void)
 * Invokes the +0xc0 slot of the EC object's vtable (the release-range
 * method) with no extra arguments.
 * Confidence: medium */
void ec_region_vtable_c0(void)
{
    void (*m)(void) = (void (*)(void)) ec_vt_method(0, 0xc0);
    m();
}

/* FUN_000debfc @ 0x000debfc   (est. ec_region_vtable_88)
 * Ghidra: void FUN_000debfc(undefined1(*)[16],undefined8*,undefined8,undefined8,undefined8)
 * Vtable dispatch: calls the +0x88 slot with (param_2[0],param_2[1],param_3,
 * param_4,param_5); when the status word (x21) is 0, stores the 16-byte
 * result into *param_1.
 * Confidence: medium */
void ec_region_vtable_88(unsigned long *out, unsigned long *args, unsigned long c,
                         unsigned long d, unsigned long e)
{
    unsigned long (*m)(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long) =
        (unsigned long (*)(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long))
        ec_vt_method(0, 0x88);
    unsigned long r = m(args[0], args[1], c, d, e);
    if (/* x21 */ 0 == 0)
        out[0] = r;
}

/* FUN_000dec58 @ 0x000dec58   (est. ec_region_vtable_80)
 * Ghidra: void FUN_000dec58(undefined1(*)[16],undefined8*,undefined8*,undefined8,undefined8)
 * Vtable dispatch: calls the +0x80 slot with (param_3[0],param_3[1]); when
 * the status word is 0, stores the result into *param_1 and the two extra
 * words into param_2[0..1].
 * Confidence: medium */
void ec_region_vtable_80(unsigned long *out, unsigned long *dst, unsigned long *args,
                         unsigned long d, unsigned long e)
{
    unsigned long (*m)(unsigned long, unsigned long) =
        (unsigned long (*)(unsigned long, unsigned long)) ec_vt_method(0, 0x80);
    unsigned long r = m(args[0], args[1]);
    if (/* x21 */ 0 == 0) {
        out[0] = r;
        dst[0] = d;
        dst[1] = e;
    }
}

/* FUN_000decbc @ 0x000decbc   (est. ec_region_vtable_90)
 * Ghidra: void FUN_000decbc(undefined1(*)[16],undefined8*,undefined8,undefined8)
 * Vtable dispatch: +0x90 slot with (param_2[0],param_2[1],param_3,param_4);
 * stores 16-byte result into *param_1 when status word is 0.
 * Confidence: medium */
void ec_region_vtable_90(unsigned long *out, unsigned long *args, unsigned long c, unsigned long d)
{
    unsigned long (*m)(unsigned long, unsigned long, unsigned long, unsigned long) =
        (unsigned long (*)(unsigned long, unsigned long, unsigned long, unsigned long))
        ec_vt_method(0, 0x90);
    unsigned long r = m(args[0], args[1], c, d);
    if (/* x21 */ 0 == 0)
        out[0] = r;
}

/* FUN_000ded14 @ 0x000ded14   (est. ec_region_vtable_98)
 * Ghidra: void FUN_000ded14(undefined1(*)[16],undefined8*,undefined8)
 * Vtable dispatch: +0x98 slot with (param_2[0],param_2[1],param_3); stores
 * 16-byte result into *param_1 when status word is 0.
 * Confidence: medium */
void ec_region_vtable_98(unsigned long *out, unsigned long *args, unsigned long c)
{
    unsigned long (*m)(unsigned long, unsigned long, unsigned long) =
        (unsigned long (*)(unsigned long, unsigned long, unsigned long)) ec_vt_method(0, 0x98);
    unsigned long r = m(args[0], args[1], c);
    if (/* x21 */ 0 == 0)
        out[0] = r;
}

/* FUN_000ded68 @ 0x000ded68   (est. ec_region_vtable_a0)
 * Ghidra: void FUN_000ded68(undefined1(*)[16])
 * Vtable dispatch: +0xa0 slot (no args); stores 16-byte result into *param_1
 * when status word is 0.
 * Confidence: medium */
void ec_region_vtable_a0(unsigned long *out)
{
    unsigned long (*m)(void) = (unsigned long (*)(void)) ec_vt_method(0, 0xa0);
    unsigned long r = m();
    if (/* x21 */ 0 == 0)
        out[0] = r;
}

/* FUN_000dedb0 @ 0x000dedb0   (est. ec_region_vtable_a8)
 * Ghidra: void FUN_000dedb0(undefined8*)
 * Vtable dispatch: +0xa8 slot with (param_1[0],param_1[1]).
 * Confidence: medium */
void ec_region_vtable_a8(unsigned long *args)
{
    void (*m)(unsigned long, unsigned long) =
        (void (*)(unsigned long, unsigned long)) ec_vt_method(0, 0xa8);
    m(args[0], args[1]);
}

/* FUN_000dedf4 @ 0x000dedf4   (est. ec_region_vtable_78)
 * Ghidra: void FUN_000dedf4(undefined8*)
 * Vtable dispatch: +0x78 slot with (param_1[0],param_1[1]).
 * Confidence: medium */
void ec_region_vtable_78(unsigned long *args)
{
    void (*m)(unsigned long, unsigned long) =
        (void (*)(unsigned long, unsigned long)) ec_vt_method(0, 0x78);
    m(args[0], args[1]);
}

/* FUN_000dee38 @ 0x000dee38   (est. ec_region_vtable_48)
 * Ghidra: void FUN_000dee38(undefined8)
 * Vtable dispatch: +0x48 slot into a 72-byte stack buffer, then copies
 * `param_1` to the user with kind 0x41.
 * Confidence: medium */
void ec_region_vtable_48(unsigned long param)
{
    unsigned char buf[72];
    void (*m)(unsigned char *) = (void (*)(unsigned char *)) ec_vt_method(0, 0x48);
    m(buf);
    cL4_copy_to_user(param, buf, 0x41);
}

/* FUN_000dee94 @ 0x000dee94   (est. ec_region_vtable_50)
 * Ghidra: void FUN_000dee94(void)
 * Vtable dispatch: +0x50 slot (no args).
 * Confidence: medium */
void ec_region_vtable_50(void)
{
    void (*m)(void) = (void (*)(void)) ec_vt_method(0, 0x50);
    m();
}

/* FUN_000deed0 @ 0x000deed0   (est. ec_region_vtable_58)
 * Ghidra: void FUN_000deed0(undefined8*,undefined8* x7)
 * Vtable dispatch: +0x58 slot with (args[0],args[1],c..j) — 9 args total.
 * Confidence: medium */
void ec_region_vtable_58(unsigned long *args, unsigned long c, unsigned long d, unsigned long e,
                         unsigned long f, unsigned long g, unsigned long h, unsigned long j)
{
    void (*m)(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long,
              unsigned long, unsigned long, unsigned long, unsigned long) =
        (void (*)(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long,
                  unsigned long, unsigned long, unsigned long, unsigned long)) ec_vt_method(0, 0x58);
    m(args[0], args[1], c, d, e, f, g, h, j);
}

/* FUN_000def3c @ 0x000def3c   (est. ec_region_vtable_60)
 * Ghidra: void FUN_000def3c(undefined8*,undefined8* x4)
 * Vtable dispatch: +0x60 slot with (args[0],args[1],c,d,e).
 * Confidence: medium */
void ec_region_vtable_60(unsigned long *args, unsigned long c, unsigned long d, unsigned long e)
{
    void (*m)(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long) =
        (void (*)(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long))
        ec_vt_method(0, 0x60);
    m(args[0], args[1], c, d, e);
}

/* FUN_000def90 @ 0x000def90   (est. ec_region_vtable_68)
 * Ghidra: void FUN_000def90(undefined8*,undefined8*)
 * Vtable dispatch: +0x68 slot with (args[0],args[1],c,d).
 * Confidence: medium */
void ec_region_vtable_68(unsigned long *args, unsigned long c, unsigned long d)
{
    void (*m)(unsigned long, unsigned long, unsigned long, unsigned long) =
        (void (*)(unsigned long, unsigned long, unsigned long, unsigned long)) ec_vt_method(0, 0x68);
    m(args[0], args[1], c, d);
}

/* FUN_000defdc @ 0x000defdc   (est. ec_region_vtable_b0)
 * Ghidra: void FUN_000defdc(undefined8*,undefined8)
 * Vtable dispatch: +0xb0 slot with (args[0],args[1],c).
 * Confidence: medium */
void ec_region_vtable_b0(unsigned long *args, unsigned long c)
{
    void (*m)(unsigned long, unsigned long, unsigned long) =
        (void (*)(unsigned long, unsigned long, unsigned long)) ec_vt_method(0, 0xb0);
    m(args[0], args[1], c);
}

/* FUN_000df024 @ 0x000df024   (est. ec_region_vtable_b8)
 * Ghidra: void FUN_000df024(undefined8*,undefined8* x3)
 * Vtable dispatch: +0xb8 slot with (args[0],args[1],c,d).
 * Confidence: medium */
void ec_region_vtable_b8(unsigned long *args, unsigned long c, unsigned long d)
{
    void (*m)(unsigned long, unsigned long, unsigned long, unsigned long) =
        (void (*)(unsigned long, unsigned long, unsigned long, unsigned long)) ec_vt_method(0, 0xb8);
    m(args[0], args[1], c, d);
}

/* FUN_000df074 / FUN_000df078 @ 0xdf074/0xdf078   (est. ec_region_wrap_guard_a/b)
 * Ghidra: void FUN_000df074(undefined8*)
 * Forwards to ec_region_guard_op_a with the two argument words.
 * Confidence: high */
void ec_region_wrap_guard_a(unsigned long *args)
{
    ec_region_guard_op_a();
}

void ec_region_wrap_guard_b(unsigned long *args)
{
    ec_region_guard_op_a();
}

/* FUN_000df094 / FUN_000df098 @ 0xdf094/0xdf098   (est. ec_region_wrap_guard_c/d)
 * Ghidra: void FUN_000df094(undefined8*)
 * Forwards to ec_region_guard_op_b.
 * Confidence: high */
void ec_region_wrap_guard_c(unsigned long *args)
{
    ec_region_guard_op_b();
}

void ec_region_wrap_guard_d(unsigned long *args)
{
    ec_region_guard_op_b();
}

/* FUN_000df0b4 / FUN_000df0b8 @ 0xdf0b4/0xdf0b8   (est. ec_region_wrap_state_a/b)
 * Ghidra: void FUN_000df0b4(undefined8*)
 * Forwards to ec_region_present_state.
 * Confidence: high */
void ec_region_wrap_state_a(unsigned long *args)
{
    ec_region_present_state();
}

void ec_region_wrap_state_b(unsigned long *args)
{
    ec_region_present_state();
}

/* FUN_000df0d4 / FUN_000df0d8 @ 0xdf0d4/0xdf0d8   (est. ec_region_wrap_sysbyte_a/b)
 * Ghidra: void FUN_000df0d4(undefined8*)
 * Forwards to ec_region_sysfeature_byte.
 * Confidence: high */
void ec_region_wrap_sysbyte_a(unsigned long *args)
{
    ec_region_sysfeature_byte();
}

void ec_region_wrap_sysbyte_b(unsigned long *args)
{
    ec_region_sysfeature_byte();
}

/* FUN_000df0f4 / FUN_000df0f8 @ 0xdf0f4/0xdf0f8   (est. ec_region_wrap_lookup_a/b)
 * Ghidra: void FUN_000df0f4(undefined8*)
 * Forwards to ec_region_cap_lookup_tbl.
 * Confidence: high */
void ec_region_wrap_lookup_a(unsigned long *args)
{
    ec_region_cap_lookup_tbl();
}

void ec_region_wrap_lookup_b(unsigned long *args)
{
    ec_region_cap_lookup_tbl();
}

/* FUN_000df114 / FUN_000df118 @ 0xdf114/0xdf118   (est. ec_region_set_granule_a/b)
 * Ghidra: void FUN_000df114(void)
 * Stores the page-size (FUN_0014b644(3)) into the region-A granule-count
 * global _DAT_006ad9d0.
 * Confidence: high
 * Notes: _DAT_006ad9d0 (cL4_ec_regA_word). */
void ec_region_set_granule_a(void)
{
    cL4_ec_regA_word = cL4_pagesize(3);
}

void ec_region_set_granule_b(void)
{
    cL4_ec_regA_word = cL4_pagesize(3);
}

/* FUN_000df14c @ 0x000df14c   (est. ec_region_granuleA_ptr)
 * Ghidra: undefined1 * FUN_000df14c(void)
 * Runs the 0xe1498 setup helper, resolves the EC object via cL4_cap_lookup,
 * and returns a pointer to the region-A granule global _DAT_006ad9d0.
 * Confidence: medium */
unsigned long ec_region_granuleA_ptr(void)
{
    cL4_ec_sub1498();
    cL4_cap_lookup(0, 0);
    return (unsigned long)&cL4_ec_regA_word;
}

/* FUN_000df1c0 @ 0x000df1c0   (est. ec_region_teardownA)
 * Ghidra: void FUN_000df1c0(void)
 * Teardown for region A: runs the 0xe1498 setup helper, resolves the EC
 * object, then the 0xe1514/0xe15f4 cleanup helpers.
 * Confidence: medium */
void ec_region_teardownA(void)
{
    cL4_ec_sub1498();
    cL4_cap_lookup(0, 0);
    cL4_ec_sub1514();
    cL4_ec_sub15f4();
}

/* FUN_000df228 @ 0x000df228   (est. ec_region_global_getA)
 * Ghidra: undefined8 FUN_000df228(undefined8)
 * Locked read of the region-A global: runs FUN_000e14e0, acquires the global
 * guard (0x36a1a0), and returns the constant magic 0xaa0921493944232a.
 * Confidence: medium
 * Notes: magic value returned unchanged (decompiler lost the actual read). */
unsigned long ec_region_global_getA(unsigned long a)
{
    unsigned char saved[24];
    cL4_ec_sub14e0(a, saved);
    cL4_global_lock(0, saved, 0, 0);
    return 0xaa0921493944232aULL;
}

/* FUN_000df264 @ 0x000df264   (est. ec_region_global_setA)
 * Ghidra: void FUN_000df264(undefined8)
 * Writes `val` into the read-only-tagged global at 0x6513c8
 * (cL4_ec_global) after the 0xe15a4 helper.
 * Confidence: medium
 * Notes: uRam...6513c8 = param_1 (0x6513c8 == cL4_ec_global). */
void ec_region_global_setA(unsigned long val)
{
    cL4_ec_sub15a4(val);
    cL4_ec_global = val;
}

/* FUN_000df29c @ 0x000df29c   (est. ec_region_global_cleanupA)
 * Ghidra: void FUN_000df29c(void)
 * Cleanup helpers 0xe1514 + 0xe15f4 for the region-A global.
 * Confidence: medium */
void ec_region_global_cleanupA(void)
{
    cL4_ec_sub1514();
    cL4_ec_sub15f4();
}

/* FUN_000df2e0 @ 0x000df2e0   (est. ec_region_global_ctorA)
 * Ghidra: void FUN_000df2e0(undefined8*)
 * Constructor for the region-A global: locks the guard at 0x6513c8 and
 * stores the magic 0xaa0921493944232a into *param_1.
 * Confidence: medium */
void ec_region_global_ctorA(unsigned long *out)
{
    unsigned char saved[24];
    cL4_global_lock(0x6513c8, saved, 0, 0);
    *out = 0xaa0921493944232aULL;
}

/* FUN_000df32c @ 0x000df32c   (est. ec_region_global_dtorA)
 * Ghidra: void FUN_000df32c(undefined8*)
 * Destructor for the region-A global: saves *param_1, locks the guard at
 * 0x6513c8 (mode 1), then writes the saved value back to 0x6513c8.
 * Confidence: medium */
void ec_region_global_dtorA(unsigned long *in)
{
    unsigned char saved[24];
    unsigned long v = *in;
    cL4_global_lock(0x6513c8, saved, 1, 0);
    cL4_ec_global = v;
}

/* FUN_000df380 @ 0x000df380   (est. ec_region_global_getB)
 * Ghidra: undefined8 FUN_000df380(undefined8)
 * Mirror of ec_region_global_getA for the region-B global 0x6513d0; returns
 * magic 0x39442b2b39442f2a.
 * Confidence: medium */
unsigned long ec_region_global_getB(unsigned long a)
{
    unsigned char saved[24];
    cL4_ec_sub14e0(a, saved);
    cL4_global_lock(0, saved, 0, 0);
    return 0x39442b2b39442f2aULL;
}

/* FUN_000df3bc @ 0x000df3bc   (est. ec_region_global_setB)
 * Ghidra: void FUN_000df3bc(undefined8)
 * Writes `val` into the global at 0x6513d0 (cL4_ec_globalB).
 * Confidence: medium */
void ec_region_global_setB(unsigned long val)
{
    cL4_ec_sub15a4(val);
    cL4_ec_globalB = val;
}

/* FUN_000df3f4 @ 0x000df3f4   (est. ec_region_global_cleanupB)
 * Ghidra: void FUN_000df3f4(void)
 * Cleanup helpers 0xe1514 + 0xe15f4 for the region-B global.
 * Confidence: medium */
void ec_region_global_cleanupB(void)
{
    cL4_ec_sub1514();
    cL4_ec_sub15f4();
}

/* FUN_000df438 @ 0x000df438   (est. ec_region_global_ctorB)
 * Ghidra: void FUN_000df438(undefined8*)
 * Constructor for the region-B global 0x6513d0; stores magic
 * 0x39442b2b39442f2a.
 * Confidence: medium */
void ec_region_global_ctorB(unsigned long *out)
{
    unsigned char saved[24];
    cL4_global_lock(0x6513d0, saved, 0, 0);
    *out = 0x39442b2b39442f2aULL;
}

/* FUN_000df484 @ 0x000df484   (est. ec_region_global_dtorB)
 * Ghidra: void FUN_000df484(undefined8*)
 * Destructor for the region-B global 0x6513d0.
 * Confidence: medium */
void ec_region_global_dtorB(unsigned long *in)
{
    unsigned char saved[24];
    unsigned long v = *in;
    cL4_global_lock(0x6513d0, saved, 1, 0);
    cL4_ec_globalB = v;
}

/* FUN_000df4d8 @ 0x000df4d8   (est. ec_region_global_getC)
 * Ghidra: undefined8 FUN_000df4d8(undefined8)
 * Region-C global getter (0x6513d8); returns magic 0xaa0a616ad370bd6b.
 * Confidence: medium */
unsigned long ec_region_global_getC(unsigned long a)
{
    unsigned char saved[24];
    cL4_ec_sub14e0(a, saved);
    cL4_global_lock(0, saved, 0, 0);
    return 0xaa0a616ad370bd6bULL;
}

/* FUN_000df514 @ 0x000df514   (est. ec_region_global_setC)
 * Ghidra: void FUN_000df514(undefined8)
 * Writes `val` into the global at 0x6513d8 (cL4_ec_globalC).
 * Confidence: medium */
void ec_region_global_setC(unsigned long val)
{
    cL4_ec_sub15a4(val);
    cL4_ec_globalC = val;
}

/* FUN_000df54c @ 0x000df54c   (est. ec_region_global_cleanupC)
 * Ghidra: void FUN_000df54c(void)
 * Cleanup helpers 0xe1514 + 0xe15f4 for the region-C global.
 * Confidence: medium */
void ec_region_global_cleanupC(void)
{
    cL4_ec_sub1514();
    cL4_ec_sub15f4();
}

/* FUN_000df590 @ 0x000df590   (est. ec_region_global_ctorC)
 * Ghidra: void FUN_000df590(undefined8*)
 * Constructor for the region-C global 0x6513d8; stores magic 0xaa0a616ad370bd6b.
 * Confidence: medium */
void ec_region_global_ctorC(unsigned long *out)
{
    unsigned char saved[24];
    cL4_global_lock(0x6513d8, saved, 0, 0);
    *out = 0xaa0a616ad370bd6bULL;
}

/* FUN_000df5dc @ 0x000df5dc   (est. ec_region_global_dtorC)
 * Ghidra: void FUN_000df5dc(undefined8*)
 * Destructor for the region-C global 0x6513d8.
 * Confidence: medium */
void ec_region_global_dtorC(unsigned long *in)
{
    unsigned char saved[24];
    unsigned long v = *in;
    cL4_global_lock(0x6513d8, saved, 1, 0);
    cL4_ec_globalC = v;
}

/* FUN_000df630 @ 0x000df630   (est. ec_region_global_getD)
 * Ghidra: undefined8 FUN_000df630(undefined8)
 * Region-D global getter (0x6513e0); returns magic 0x3944372aaa090149.
 * Confidence: medium */
unsigned long ec_region_global_getD(unsigned long a)
{
    unsigned char saved[24];
    cL4_ec_sub14e0(a, saved);
    cL4_global_lock(0, saved, 0, 0);
    return 0x3944372aaa090149ULL;
}

/* FUN_000df66c @ 0x000df66c   (est. ec_region_global_setD)
 * Ghidra: void FUN_000df66c(undefined8)
 * Writes `val` into the global at 0x6513e0 (cL4_ec_globalD).
 * Confidence: medium */
void ec_region_global_setD(unsigned long val)
{
    cL4_ec_sub15a4(val);
    cL4_ec_globalD = val;
}

/* FUN_000df6a4 @ 0x000df6a4   (est. ec_region_global_cleanupD)
 * Ghidra: void FUN_000df6a4(void)
 * Cleanup helpers 0xe1514 + 0xe15f4 for the region-D global.
 * Confidence: medium */
void ec_region_global_cleanupD(void)
{
    cL4_ec_sub1514();
    cL4_ec_sub15f4();
}

/* FUN_000df6e8 @ 0x000df6e8   (est. ec_region_global_ctorD)
 * Ghidra: void FUN_000df6e8(undefined8*)
 * Constructor for the region-D global 0x6513e0; stores magic 0x3944372aaa090149.
 * Confidence: medium */
void ec_region_global_ctorD(unsigned long *out)
{
    unsigned char saved[24];
    cL4_global_lock(0x6513e0, saved, 0, 0);
    *out = 0x3944372aaa090149ULL;
}

/* FUN_000df734 @ 0x000df734   (est. ec_region_global_dtorD)
 * Ghidra: void FUN_000df734(undefined8*)
 * Destructor for the region-D global 0x6513e0.
 * Confidence: medium */
void ec_region_global_dtorD(unsigned long *in)
{
    unsigned char saved[24];
    unsigned long v = *in;
    cL4_global_lock(0x6513e0, saved, 1, 0);
    cL4_ec_globalD = v;
}

/* FUN_000df77c / FUN_000df780 @ 0xdf77c/0xdf780   (est. ec_region_set_granuleB_a/b)
 * Ghidra: void FUN_000df77c(void)
 * Stores (page_size(3) >> 3) into the region-B granule global
 * _DAT_006ad9d8.
 * Confidence: high
 * Notes: _DAT_006ad9d8 (cL4_ec_regB_word). */
void ec_region_set_granuleB_a(void)
{
    cL4_ec_regB_word = cL4_pagesize(3) >> 3;
}

void ec_region_set_granuleB_b(void)
{
    cL4_ec_regB_word = cL4_pagesize(3) >> 3;
}

/* FUN_000df7b8 @ 0x000df7b8   (est. ec_region_granuleB_ptr)
 * Ghidra: undefined1 * FUN_000df7b8(void)
 * Runs the 0xe1584 setup helper, resolves the EC object, and returns a
 * pointer to the region-B granule global _DAT_006ad9d8.
 * Confidence: medium */
unsigned long ec_region_granuleB_ptr(void)
{
    cL4_ec_sub1584();
    cL4_cap_lookup(0, 0);
    return (unsigned long)&cL4_ec_regB_word;
}

/* FUN_000df804 @ 0x000df804   (est. ec_region_cap_resolve)
 * Ghidra: undefined8 FUN_000df804(long*,undefined8*,undefined8)
 * Resolves a capability: when *param_1 != -1, looks it up via
 * cL4_cap_lookup(param_1, param_3); runs the 0xe14e0 setup, locks the global
 * guard, and returns *param_2.
 * Confidence: medium */
unsigned long ec_region_cap_resolve(long *cap, unsigned long *dst, unsigned long alt)
{
    unsigned char saved[24];
    if (*cap != -1)
        cap = (long *)cL4_cap_lookup((unsigned long *)cap, alt);
    cL4_ec_sub14e0((unsigned long)cap, saved);
    cL4_global_lock(0, saved, 0, 0);
    return *dst;
}

/* FUN_000df878 @ 0x000df878   (est. ec_region_cap_store)
 * Ghidra: void FUN_000df878(undefined8,long*,undefined8*,undefined8)
 * Stores `val` into *param_3 under the access lock, after resolving
 * *param_2 via cL4_cap_lookup when it is not -1.
 * Confidence: medium */
void ec_region_cap_store(unsigned long val, long *cap, unsigned long *dst, unsigned long alt)
{
    unsigned char saved[24];
    if (*cap != -1)
        cL4_cap_lookup((unsigned long *)cap, alt);
    cL4_obj_access(dst, saved);
    *dst = val;
}

/* FUN_000df8cc @ 0x000df8cc   (est. ec_region_teardownB)
 * Ghidra: void FUN_000df8cc(void)
 * Teardown for region B: 0xe1584 setup, resolve EC object, then
 * 0xe1514/0xe15f4 cleanup.
 * Confidence: medium */
void ec_region_teardownB(void)
{
    cL4_ec_sub1584();
    cL4_cap_lookup(0, 0);
    cL4_ec_sub1514();
    cL4_ec_sub15f4();
}

/* FUN_000df928 @ 0x000df928   (est. ec_region_vtable_indirect_get)
 * Ghidra: void FUN_000df928(undefined8*)
 * Runs the 0xe14e0 setup, resolves the EC object, locks the guard, then
 * stores the value from an indirect source (in_x4) into *param_1.
 * Confidence: low
 * Notes: reads via register-passed function pointer in_x3 and pointer in_x4. */
void ec_region_vtable_indirect_get(unsigned long *out)
{
    unsigned char saved[24];
    unsigned long v = (*(unsigned long (**)(void))/* in_x3 */ 0)();
    cL4_ec_sub14e0(v, saved);
    cL4_global_lock(0, saved, 0, 0);
    *out = /* *in_x4 */ 0;
}

/* FUN_000df970 @ 0x000df970   (est. ec_region_vtable_indirect_set)
 * Ghidra: void FUN_000df970(undefined8*)
 * Stores *param_1 into the target (in_x5) under the access lock, after
 * running the register-passed function (in_x4).
 * Confidence: low
 * Notes: register-passed in_x4/in_x5. */
void ec_region_vtable_indirect_set(unsigned long *in)
{
    unsigned char saved[24];
    unsigned long v = *in;
    (*(void (**)(void))/* in_x4 */ 0)();
    cL4_obj_access(/* in_x5 */ 0, saved);
    /* *in_x5 = v */
}

/* FUN_000df9dc / FUN_000dfa20 / FUN_000dfa64 / FUN_000dfaa8
 *   @ 0xdf9dc/0xdfa20/0xdfa64/0xdfaa8   (est. ec_region_global_valueA/B/C/D)
 * Ghidra: undefined8 FUN_000df9dc(void)
 * Reads the region global under the guard and returns its magic constant
 * (A=0xaa0921493944232a, B=0x39442b2b39442f2a, C=0xaa0a616ad370bd6b,
 * D=0x3944372aaa090149).
 * Confidence: medium */
unsigned long ec_region_global_valueA(void)
{
    unsigned char saved[24];
    cL4_global_lock(0x6513c8, saved, 0, 0);
    return 0xaa0921493944232aULL;
}

unsigned long ec_region_global_valueB(void)
{
    unsigned char saved[24];
    cL4_global_lock(0x6513d0, saved, 0, 0);
    return 0x39442b2b39442f2aULL;
}

unsigned long ec_region_global_valueC(void)
{
    unsigned char saved[24];
    cL4_global_lock(0x6513d8, saved, 0, 0);
    return 0xaa0a616ad370bd6bULL;
}

unsigned long ec_region_global_valueD(void)
{
    unsigned char saved[24];
    cL4_global_lock(0x6513e0, saved, 0, 0);
    return 0x3944372aaa090149ULL;
}

/* FUN_000dfb14 @ 0x000dfb14   (est. ec_region_cap_resolve2)
 * Ghidra: undefined8 FUN_000dfb14(undefined8,undefined8,long*,undefined8*,undefined8)
 * Resolves a capability (via cL4_cap_lookup when *param_3 != -1), runs the
 * 0xe14e0 setup, locks the guard, and returns *param_4.
 * Confidence: medium */
unsigned long ec_region_cap_resolve2(unsigned long a, unsigned long b, long *cap,
                                     unsigned long *dst, unsigned long alt)
{
    unsigned char saved[24];
    if (*cap != -1)
        a = cL4_cap_lookup((unsigned long *)cap, alt);
    cL4_ec_sub14e0(a, saved);
    cL4_global_lock(0, saved, 0, 0);
    return *dst;
}

/* FUN_000dfb64 @ 0x000dfb64   (est. ec_region_ptr_deref0)
 * Ghidra: undefined8 FUN_000dfb64(undefined8*)
 * Returns *param_1.
 * Confidence: high */
unsigned long ec_region_ptr_deref0(unsigned long *p)
{
    return *p;
}

/* FUN_000dfb6c @ 0x000dfb6c   (est. ec_region_ptr_field8)
 * Ghidra: undefined8 FUN_000dfb6c(long)
 * Returns *(param_1 + 8).
 * Confidence: high */
unsigned long ec_region_ptr_field8(long p)
{
    return *(unsigned long *)(p + 8);
}

/* FUN_000dfb74 @ 0x000dfb74   (est. ec_region_ptr_field18)
 * Ghidra: undefined8 FUN_000dfb74(long)
 * Returns *(param_1 + 0x18).
 * Confidence: high */
unsigned long ec_region_ptr_field18(long p)
{
    return *(unsigned long *)(p + 0x18);
}

/* FUN_000dfb7c @ 0x000dfb7c   (est. ec_region_read_triple)
 * Ghidra: undefined1 [16] FUN_000dfb7c(long)
 * Reads a 16-byte value plus a trailing byte at param_1+0x20/+0x28/+0x30 and
 * re-publishes them via the 0xe100c helper, returning the 16-byte value.
 * Confidence: medium */
unsigned long ec_region_read_triple_lo(long p)
{
    unsigned long lo = *(unsigned long *)(p + 0x20);
    unsigned long hi = *(unsigned long *)(p + 0x28);
    unsigned char c = *(unsigned char *)(p + 0x30);
    cL4_ec_sub100c(lo, hi, c);
    return lo;
}

/* FUN_000dfbc4 @ 0x000dfbc4   (est. ec_region_vtable_release)
 * Ghidra: void FUN_000dfbc4(undefined8*,undefined8*)
 * Acquires *param_1 (0x36b270) then invokes the +0x60 vtable slot of the
 * object referenced by *param_2.
 * Confidence: medium */
void ec_region_vtable_release(unsigned long *a, unsigned long *b)
{
    void (*m)(void) = (void (*)(void)) ec_vt_method((struct ec_mem_region *)b, 0x60);
    cL4_acquire(*a);
    m();
}

/* FUN_000dfc18 @ 0x000dfc18   (est. ec_region_swap_field10)
 * Ghidra: void FUN_000dfc18(undefined8)
 * Swaps the EC object's +0x10 field: reads the old value under the access
 * lock, stores `param_1`, then releases the old value (0x36b118).
 * Confidence: medium */
void ec_region_swap_field10(unsigned long val)
{
    unsigned char saved[24];
    cL4_obj_access((unsigned long *)0 /* self+0x10 */, saved);
    /* old = *(self+0x10); *(self+0x10) = val */
    cL4_release(/* old */ 0);
}

/* FUN_000dfc58 @ 0x000dfc58   (est. ec_region_read_pair10)
 * Ghidra: undefined1 [16] FUN_000dfc58(void)
 * Reads the EC object's +0x10 field and returns the callback-closure pair
 * {handler=0x7bf58, ptr=self+0x10}.
 * Confidence: medium
 * Notes: DAT_0007bf58 callback pointer. */
unsigned long ec_region_read_pair10_lo(void)
{
    cL4_obj_read((unsigned long *)0 /* self+0x10 */);
    return 0x7bf58; /* auVar1._0_8_ = &DAT_0007bf58 */
}

/* FUN_000dfc9c @ 0x000dfc9c   (est. ec_region_read_triple_self)
 * Ghidra: undefined1 [16] FUN_000dfc9c(void)
 * Reads the EC object's +0x20/+0x28/+0x30 triple and re-publishes via
 * 0xe100c, returning the 16-byte value.
 * Confidence: medium */
unsigned long ec_region_read_triple_self_lo(void)
{
    unsigned long lo = *(unsigned long *)(0 /* self+0x20 */);
    unsigned long hi = *(unsigned long *)(0 /* self+0x28 */);
    unsigned char c = *(unsigned char *)(0 /* self+0x30 */);
    cL4_ec_sub100c(lo, hi, c);
    return lo;
}

/* FUN_000dfce4 @ 0x000dfce4   (est. ec_region_set_triple)
 * Ghidra: void FUN_000dfce4(undefined8,undefined8,undefined1)
 * Stores the 16-byte+byte triple into the EC object's +0x20/+0x28/+0x30
 * after releasing the old triple (0x8396c).
 * Confidence: medium */
void ec_region_set_triple(unsigned long a, unsigned long b, unsigned char c)
{
    /* FUN_0008396c(*(self+0x20),*(self+0x28),*(self+0x30)) release old */
    /* *(self+0x20)=a; *(self+0x28)=b; *(self+0x30)=c */
}

/* FUN_000dfd3c @ 0x000dfd3c   (est. ec_region_setup)
 * Ghidra: void FUN_000dfd3c(undefined8,undefined8,undefined8,undefined8)
 * EC memory-region object constructor. Allocates an object descriptor
 * (0x665f60/0x665cd8) into +0x28, a type descriptor (0x651400 via table
 * 0x4c2878, size 0x18) into a local, a new object via 0x167f44 into +0x20,
 * builds the region via 0xe1540, and links the descriptor (0x1024) into
 * +0x10; stores the second argument into +0x18.
 * Confidence: medium
 * Notes: string tables 0x4c2878/0x4c2880; FUN_00002534 typedesc. */
void ec_region_setup(unsigned long a, unsigned long b)
{
    unsigned long desc = cL4_objdesc(0x665f60, 0x665cd8);
    /* *(self+0x28) = desc */
    /* t = FUN_00002534(0x651400,&DAT_004c2878); FUN_0036a940(t,0x18,7) */
    unsigned long o = cL4_obj_alloc();
    /* *(self+0x20) = o */
    unsigned long r = cL4_mask_test(a);
    /* r = FUN_000e1540(r,0x666cf0) */
    /* link = cL4_mask_test(r,0x665f60,d,0x665cd8) */
    /* t2 = FUN_00002534(0x651408,&DAT_004c2880); t2 = FUN_0036a940(t2,0x30,7) */
    /* *(self+0x10) = FUN_000e1024(r,t2) */
    /* *(self+0x18) = b */
}

/* FUN_000dfe2c @ 0x000dfe2c   (est. ec_region_map_vaddrs)
 * Ghidra: void FUN_000dfe2c(ulong*,ulong*,undefined8,undefined8,undefined*)
 * Maps a set of EC memory-region virtual addresses into the EC's vspace and
 * copies the region descriptor set back into *param_1.
 *
 * Fast path (param_5 == 0): computes the granule count from the region's
 * byte size (param_2[1]) divided by the page size; allocates the region
 * pages (0x82524), then for each granule invokes the +0x1f0 vtable method to
 * map the corresponding physical range into the vspace, appending each
 * returned block pointer into the region descriptor list (param_5 = the
 * region object, entries at +0x20, count at +0x10). Faults (SoftwareBreak-
 * point) on overflow.
 *
 * Slow path (param_5 != 0): acquires the existing region object.
 *
 * Both then run the shared 0xe1498/0x39a128/0xe14e0/0x36a1a0 publish
 * sequence. A subsequent consistency check verifies the recorded granule
 * count matches (size / _DAT_006ad9d0) and, on mismatch, prints a "cannot
 * deallocate EC memory region" style error via the kernel printf machinery
 * (0x2a4ab4/0x2acbb8/0x27724/0x3a25d4) and enters the noreturn fatal.
 *
 * Finally it walks the mapped granules, invoking the +0x58 vtable method per
 * region entry (handling a failure by un-mapping via the +0x1f0 and +0x70
 * slots), releases the region, and copies the full descriptor set
 * (param_2[0..6]) into *param_1.
 * Confidence: medium
 * Notes: uses _DAT_006ad9d0 granule word; SoftwareBreakpoint(1, ...) guards;
 *   error strings "...but are..." and "...were app..." in printf stream. */
void ec_region_map_vaddrs(unsigned long *dst, unsigned long *src, unsigned long c,
                          unsigned long d, unsigned long *region_list)
{
    unsigned long pagesize, gran, i, addr;

    if (region_list == 0) {
        /* fast path: fresh allocation */
        pagesize = cL4_pagesize(3);
        if (pagesize == 0) { /* SoftwareBreakpoint(1,0xe0364) */ }
        gran = (pagesize != 0) ? src[1] / pagesize : 0;
        if ((long)gran < 0) { /* SoftwareBreakpoint(1,0xe0368) */ }
        region_list = (unsigned long *)&cL4_ec_global; /* &DAT_00657778 */
        if (pagesize <= src[1]) {
            /* DAT_00657778 seed */
            cL4_alloc_pages(0, gran, 0);
            i = 0;
            addr = src[0];
            while (gran != i) {
                if (i == 0x7fffffffffffffffULL) { /* SoftwareBreakpoint(1,0xe0350) */ }
                if (gran <= i) { /* SoftwareBreakpoint(1,0xe0354) */ }
                unsigned long p = cL4_pagesize(3);
                if (i * p /* hi */ != 0) { /* SoftwareBreakpoint(1,0xe0358) */ }
                if (/* carry */ addr > addr + i * p) { /* SoftwareBreakpoint(1,0xe035c) */ }
                unsigned long blk = 0;
                void (*m)(unsigned long*, unsigned long, unsigned long, unsigned long,
                          unsigned long*) = (void (*)(unsigned long*, unsigned long,
                          unsigned long, unsigned long, unsigned long*)) ec_vt_method(0, 0x1f0);
                m((unsigned long*)&blk, 3, addr + i * p, 0, &blk);
                /* publish via 0x9e18c/0x276c/0x36b118 on error path */
                cL4_page_commit((unsigned long *)&blk, i);
                if (region_list[2] >> 1 <= region_list[1])
                    cL4_alloc_pages(1 < region_list[2], region_list[1] + 1, 1);
                i += 1;
                region_list[1] = region_list[1] + 1;
                region_list[i * 8 + 4] = blk; /* +0x20 */
            }
        }
    } else {
        cL4_acquire((unsigned long)region_list);
    }
    /* shared publish: 0xe1498/0x39a128/0xe14e0/0x36a1a0 */
    if (cL4_ec_regA_word == 0) { /* SoftwareBreakpoint(1,0xe0360) */ }
    gran = (cL4_ec_regA_word != 0) ? src[1] / cL4_ec_regA_word : 0;
    if (region_list[1] != gran) {
        /* printf "...cannot deallocate EC memory region..." + noreturn fatal(0x39) */
        cL4_ec_fatal();
    }
    if (cL4_ec_regA_word <= src[1]) {
        i = 0;
        addr = src[0];
        unsigned long n = src[3];
        do {
            if (region_list[1] <= i) { /* SoftwareBreakpoint(1,0xe0344) */ }
            if (i * cL4_ec_regA_word /* hi */ != 0) { /* SoftwareBreakpoint(1,0xe0348) */ }
            unsigned long va = addr + i * cL4_ec_regA_word;
            if (/* carry */ addr > va) { /* SoftwareBreakpoint(1,0xe034c) */ }
            unsigned long entry = region_list[i * 8 + 4];
            /* vtable+0x58 method per entry */
            if (/* x21 */ 0 != 0) {
                /* failure: un-map via +0x1f0 and +0x70, release */
            }
            i += 1;
            cL4_release(/* r */ 0);
        } while (gran != i);
    }
    cL4_release((unsigned long)region_list);
    /* copy descriptor set src[0..6] into dst[0..6] */
    dst[0] = src[0];
    dst[1] = src[1];
    dst[2] = src[2];
    dst[3] = src[3];
    dst[4] = src[4];
    dst[5] = src[5];
    *(unsigned char *)(dst + 6) = (unsigned char)src[6];
}

/* FUN_000e04c4 @ 0x000e04c4   (est. ec_region_reset)
 * Ghidra: void FUN_000e04c4(void)
 * Resets the EC region: runs the 0xe1470 helper, clears the output byte
 * (0x36_mem set 0), then the 0x36986c result fetch.
 * Confidence: low
 * Notes: writes 0 via extraout_x1 pointer. */
void ec_region_reset(void)
{
    cL4_ec_sub1470();
    /* *extraout_x1 = 0 */
    cL4_get_result();
}

/* FUN_000e04f8 @ 0x000e04f8   (est. ec_region_teardown_all)
 * Ghidra: void FUN_000e04f8(void)
 * Runs the 0xe1470 and 0xe166c teardown helpers.
 * Confidence: medium */
void ec_region_teardown_all(void)
{
    cL4_ec_sub1470();
    cL4_ec_sub166c();
}

/* FUN_000e0520 @ 0x000e0520   (est. ec_region_copy_desc)
 * Ghidra: void FUN_000e0520(undefined8*,undefined8* x6)
 * Copies an EC region descriptor: re-publishes the triple (f,g,h), stores
 * b/c/d into out[0..2], repeats d into out[3], stores f/g/h into out[4..5]
 * and the byte into out+6.
 * Confidence: medium
 * Notes: out[3]=out[2]=param_4 (decompiler quirk: both equal param_4). */
void ec_region_copy_desc(unsigned long *out, unsigned long b, unsigned long c,
                         unsigned long d, unsigned long e, unsigned long f,
                         unsigned long g, unsigned long h)
{
    cL4_ec_sub100c(f, g, (unsigned char)h);
    out[0] = b;
    out[1] = c;
    out[2] = d;
    out[3] = d;
    out[4] = f;
    out[5] = g;
    *(unsigned char *)(out + 6) = (unsigned char)h;
}

/* FUN_000e0598 @ 0x000e0598   (est. ec_region_panic_report)
 * Ghidra: void FUN_000e0598(undefined8*)
 * Formats and reports an EC region fatal condition. Builds a printf-style
 * message stream (0x2a4ab4 + 0x2acbb8 with a format string at 0x5c4180),
 * loads the region descriptor from *param_1 into a stack frame, and calls
 * the report helper 0x205844 with format addresses 0x661798/0x6756a8/
 * 0x66e1b8, then enters the noreturn fatal (code 0x1c2). Never returns.
 * Confidence: medium
 * Notes: strings/format table at 0x5c4180, 0x661798, 0x6756a8, 0x66e1b8. */
void ec_region_panic_report(unsigned long *desc)
{
    /* printf stream (0x2a4ab4(0x25), thunk 0x2acbb8(0xd..., &DAT_005c4180)) */
    /* load desc[0..6] into locals; FUN_00205844(&frame,0x661798,0x6756a8,0x66e1b8) */
    cL4_ec_sub1600(0x1c2);
    cL4_ec_fatal();
}

/* FUN_000e0654 @ 0x000e0654   (est. ec_region_copy16)
 * Ghidra: undefined1 [16] FUN_000e0654(undefined1(*)[16])
 * Returns *param_1 (16-byte value pass-through).
 * Confidence: high */
unsigned long ec_region_copy16_lo(unsigned long *p)
{
    return *p;
}

/* FUN_000e0660 @ 0x000e0660   (est. ec_region_vtable_88_2)
 * Ghidra: void FUN_000e0660(void)
 * Runs the 0xe14b8 setup helper, then invokes the +0x88 vtable slot into a
 * 64-byte stack buffer.
 * Confidence: medium */
void ec_region_vtable_88_2(void)
{
    unsigned char buf[64];
    cL4_ec_sub14b8();
    ((void (*)(unsigned char *)) ec_vt_method(0, 0x88))(buf);
}

/* FUN_000e06a0 @ 0x000e06a0   (est. ec_region_vtable_90_2)
 * Ghidra: void FUN_000e06a0(void)
 * Runs the 0xe14b8 setup helper, then invokes the +0x90 vtable slot into a
 * 64-byte stack buffer.
 * Confidence: medium */
void ec_region_vtable_90_2(void)
{
    unsigned char buf[64];
    cL4_ec_sub14b8();
    ((void (*)(unsigned char *)) ec_vt_method(0, 0x90))(buf);
}

/* FUN_000e06e0 @ 0x000e06e0   (est. ec_region_vtable_98_2)
 * Ghidra: void FUN_000e06e0(void)
 * Runs the 0xe14b8 setup helper, then invokes the +0x98 vtable slot into a
 * 64-byte stack buffer.
 * Confidence: medium */
void ec_region_vtable_98_2(void)
{
    unsigned char buf[64];
    cL4_ec_sub14b8();
    ((void (*)(unsigned char *)) ec_vt_method(0, 0x98))(buf);
}

/* FUN_000e0720 @ 0x000e0720   (est. ec_region_vtable_78_copy)
 * Ghidra: void FUN_000e0720(undefined8)
 * Fetches a context, invokes the +0x78 vtable slot into a 104-byte stack
 * buffer, then copies `param_1` to the user with kind 0x61.
 * Confidence: medium */
void ec_region_vtable_78_copy(unsigned long param)
{
    unsigned char buf[104];
    cL4_ctx_get();
    ((void (*)(unsigned char *)) ec_vt_method(0, 0x78))(buf);
    cL4_copy_to_user(param, buf, 0x61);
}

/* FUN_000e0794 / FUN_000e07dc @ 0xe0794/0xe07dc   (est. ec_region_fatal_dealloc_a/b)
 * Ghidra: void FUN_000e0794(void)
 * Prints the "Cannot deallocate EC memory region" message (0x5c41a0+0x10)
 * then enters the noreturn fatal. Never returns.
 * Confidence: high
 * Notes: string s_Cannot_deallocate_EC_memory_regi_005c41a0+0x10. */
void ec_region_fatal_dealloc_a(void)
{
    cL4_ec_printmsg("Cannot deallocate EC memory region");
    cL4_ec_fatal();
}

void ec_region_fatal_dealloc_b(void)
{
    cL4_ec_printmsg("Cannot deallocate EC memory region");
    cL4_ec_fatal();
}

/* FUN_000e0824 @ 0x000e0824   (est. ec_region_set_field28)
 * Ghidra: void FUN_000e0824(undefined8)
 * Stores `val` into the EC object's +0x28 field under the access lock.
 * Confidence: medium */
void ec_region_set_field28(unsigned long val)
{
    cL4_obj_access((unsigned long *)0 /* self+0x28 */, 0);
    /* *(self+0x28) = val */
}
