/* Recreated from exclavecore_bundle.t8142.RELEASE.im4p (cL4 Secure Kernel, GL1, arm64e, image
 * base 0) — the cL4 microkernel (cL4 (679.100.61)), seL4-derived. Ground truth: Ghidra FUN_ names
 * + addresses in program cl4_kernel.raw. All names are estimates unless string-matched.
 * Sub-range 3: 0x1b0000-0x1c0000 (433 functions). This region is dominated by the Swift runtime
 * support layer used by the cL4 kernel: fatal-error/assert handling, string/UnsafeBufferPointer
 * indexing, and buffer validation wrappers (the kernel is partly written in Swift). */

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "sk_internal.h"

/* ------------------------------------------------------------------ *
 * Out-of-range cL4 / Swift runtime helpers (FUN_ addr in comment;
 * reconstructed by sibling SK range workers). Names are estimates.
 * ------------------------------------------------------------------ */
extern void sk_fatal_error(unsigned long a, unsigned long b, ...) __attribute__((noreturn)); /* FUN_001afe4c */
extern unsigned long sk_swift_state(void);                    /* FUN_00348e00 */
extern unsigned long sk_swift_state2(void);                   /* FUN_00355538 */
extern unsigned long sk_swift_state3(void);                   /* FUN_00351d18 */
extern unsigned long sk_swift_gstate(unsigned long a);        /* FUN_0036a940 */
extern unsigned long sk_swift_gstore(unsigned long a);        /* FUN_00310d98 */
extern unsigned long sk_swift_flag(unsigned long a);          /* indirect result */
extern unsigned long sk_swift_flag_set(unsigned long a);      /* FUN_00229a3c */
extern unsigned long sk_swift_flag_calc(unsigned long a);     /* FUN_00351ca0 */
extern unsigned long sk_swift_tag(unsigned long a);           /* FUN_001a8564 */
extern unsigned long sk_swift_done(void);                     /* FUN_000839d8 */
extern unsigned long sk_swift_cap(unsigned long a);           /* FUN_003a26a0 */
extern unsigned long sk_swift_cap_rel(unsigned long a);       /* FUN_003a261c */
extern unsigned long sk_swift_idx(unsigned long a);           /* FUN_003a2898 */
extern unsigned long sk_swift_idx_cmp(unsigned long a, unsigned long b); /* FUN_002a0f24 */
extern unsigned long sk_swift_meta(unsigned long a);          /* FUN_003a25d4 */
extern unsigned long sk_swift_free(unsigned long a);          /* FUN_0036b118 */
extern unsigned long sk_swift_free_pages(unsigned long a);    /* FUN_0036b270 */
extern unsigned long sk_swift_bitset_ctor(unsigned long a);   /* FUN_002c2da4 */
extern unsigned long sk_swift_bitset_end(unsigned long a);    /* FUN_00068e14 */
extern unsigned long sk_swift_hash(unsigned long a);          /* FUN_00255738 */
extern unsigned long sk_swift_hash_pair(unsigned long a);     /* FUN_00255738 */
extern unsigned long sk_swift_attr_get(unsigned long a);      /* FUN_00281cc0 */
extern unsigned long sk_swift_attr_get2(unsigned long a);     /* FUN_00283a08 */
extern unsigned long sk_swift_attr_get3(unsigned long a);     /* FUN_00282bc0 */
extern unsigned long sk_swift_small_string(unsigned long a, unsigned long b, unsigned long c); /* FUN_001a89a8 */
extern unsigned long sk_swift_empty_string(unsigned long a);  /* FUN_0011e71c */
extern unsigned long sk_swift_int_string(unsigned long a, unsigned long b); /* FUN_002364dc */
extern unsigned long sk_swift_string_builder(unsigned long a);/* string builder */
extern unsigned long sk_swift_string_ref(unsigned long a);    /* FUN_001e8374 */
extern unsigned long sk_swift_string_ref2(unsigned long a);   /* FUN_001e851c */
extern unsigned long sk_swift_string_cvt(unsigned long a);    /* FUN_001e9414 */
extern unsigned long sk_swift_string_cmp2(unsigned long a, unsigned long b, unsigned long c, unsigned long d, unsigned long e); /* FUN_002a0d50 */
extern unsigned long sk_swift_string_cmp6(unsigned long a, unsigned long b, unsigned long c, unsigned long d); /* FUN_00359214 */
extern unsigned long sk_swift_utf8_next(void *a, unsigned long b, unsigned long c); /* FUN_002b141c */
extern unsigned long sk_swift_utf8_prev(void *a, unsigned long b, unsigned long c); /* FUN_002b14c8 */
extern unsigned long sk_swift_utf8_scalar_at(unsigned long a, unsigned long b, unsigned long c); /* FUN_002a9ba8 */
extern unsigned long sk_swift_utf8_scalar_prev(unsigned long a, unsigned long b, unsigned long c); /* FUN_00167404 */
extern unsigned long sk_swift_witness(unsigned long a);       /* FUN_0034b7f4 */
extern unsigned long sk_swift_witnessB(unsigned long a);      /* FUN_0034b798 */
extern unsigned long sk_swift_witnessF(unsigned long a);      /* FUN_0034f464 */
extern unsigned long sk_swift_range(unsigned long a, unsigned long b, unsigned long c); /* FUN_0019eb88 */
extern unsigned long sk_swift_pair_cvt(unsigned long a, unsigned long b); /* FUN_0001a1c8 */
extern unsigned long sk_swift_reg(unsigned long a, unsigned long b); /* FUN_003198cc */
extern unsigned long sk_swift_galloc(unsigned long a, unsigned long b); /* FUN_00083450 */
extern unsigned long sk_swift_ginit(unsigned long a, unsigned long b);  /* FUN_00389da0 */
extern unsigned long sk_swift_gfind(unsigned long a, unsigned long b);  /* FUN_00362c34 */
extern unsigned long sk_swift_gverify(unsigned long a, unsigned long b);/* FUN_00362c00 */
extern unsigned long sk_swift_glist(unsigned long a);         /* FUN_003629c4 */
extern unsigned long sk_swift_gstep(unsigned long a);         /* FUN_003629b4 */
extern unsigned long sk_swift_die(unsigned long a);           /* FUN_00348898 */
extern unsigned long sk_swift_die2_0(unsigned long a);        /* FUN_00348074 */
extern unsigned long sk_swift_die2_1(unsigned long a);        /* FUN_00348404 */
extern unsigned long sk_swift_die3(void);                     /* FUN_0034a368 */
extern unsigned long sk_swift_string_lit(unsigned long a);    /* FUN_001a89a8 */
extern unsigned long thunk_sk_swift_hash(unsigned long a, unsigned long b); /* FUN_00229ebc */
extern void thunk_FUN_00054414(unsigned long *a, unsigned long b);
extern unsigned long thunk_FUN_001a89a8(unsigned long a, unsigned long b, unsigned int c); /* 0x1a89a8 */
extern void thunk_FUN_00213834(void);                            /* 0x213834 */
extern void thunk_FUN_002298d4(unsigned long a);                 /* 0x2298d4 */
extern long thunk_FUN_00284424(void *a, long b, long c, void *d, void *e); /* 0x284424 */
extern unsigned long thunk_FUN_0036b270(unsigned long a);        /* 0x36b270 */
  /* FUN_00054414 */
extern unsigned long sk_swift_badlock(unsigned long a);       /* FUN_00347fb4 */
extern unsigned long sk_swift_shift(unsigned long a, unsigned long b, unsigned long c, ...); /* FUN_00356340 */

extern unsigned long sk_sync_ops_1(unsigned long a);             /* FUN_00354a34 */
extern unsigned long sk_sync_ops_2(unsigned long a);             /* FUN_0035694c */
extern void sk_bad_pointer(void);                                /* FUN_0034846c */
extern unsigned long sk_obj_alloc_buf(unsigned long a);          /* FUN_00355968 */
extern unsigned long sk_swift_overflow(void);                    /* FUN_003583dc */
extern void sk_swift_fail(void);                                 /* FUN_00348194 */
extern void sk_swift_fail2(void);                                /* FUN_003523f0 */
extern unsigned long sk_swift_detect_tiny(unsigned long a);      /* FUN_00356d2c */
extern unsigned long sk_str_fast_count(unsigned long a);         /* FUN_00255d4c */
extern void sk_swift_emit(unsigned long a);                      /* FUN_003528ac */
extern void sk_swift_die(void);                                  /* FUN_00348898 */
extern void sk_swift_die2(void);                                 /* FUN_0034a2f8 */
extern void sk_swift_sync(unsigned long a);                      /* FUN_00357ca0 */
extern unsigned long sk_swift_sync_ret(void);                    /* FUN_00355d9c */
extern void sk_swift_pin(unsigned long a);                       /* FUN_00351584 */
extern void sk_swift_unpin(unsigned long a);                     /* FUN_003591f4 */
extern void sk_swift_store(unsigned long a, unsigned long b);    /* FUN_00357c44 */
extern void sk_swift_ckrange(void);                              /* FUN_0035ab60 */
extern void sk_swift_ckrange2(void);                             /* FUN_003d2dd4 */
extern void sk_swift_panic_msg(unsigned long a);                 /* FUN_00350410 */
extern void sk_swift_badptr(void);                               /* FUN_00358ca4 */
extern void sk_swift_trap_slot(void);                            /* FUN_00353d70 */
extern void sk_swift_dispatch(void);                             /* FUN_003523fc */
extern unsigned long sk_swift_classify(unsigned long a);         /* FUN_00354504 */
extern unsigned long sk_swift_isascii_utf16(unsigned long);      /* FUN_0001da84 */
extern unsigned long sk_swift_utf16_fwd(unsigned long a);        /* FUN_001676cc */
extern unsigned long sk_swift_utf16_get(unsigned long);          /* FUN_002a9ba8 */
extern void sk_swift_memop(unsigned long a, unsigned long b, unsigned long c, unsigned long d); /* FUN_002bbc14 */
extern unsigned long sk_swift_utf16_set(unsigned long);          /* FUN_002af618 */
extern void sk_swift_utf16_slice(void);                          /* FUN_00291d70 */
extern void sk_swift_table(void);                                /* FUN_00346774 */
extern unsigned long sk_swift_string_lit(unsigned long);         /* FUN_00002534 */
extern void sk_swift_meta(void);                                 /* FUN_003a25d4 */
extern void sk_swift_cast16(void);                               /* FUN_0001d4a0 */
extern unsigned long sk_swift_uint_conv(unsigned long);          /* FUN_003d2f9c */
extern void sk_swift_uint_conv2(void);                           /* FUN_003d2f10 */
extern void sk_swift_load(void);                                 /* FUN_00357cb4 */
extern void sk_swift_iret(void);                                 /* FUN_00357c74 */
extern void sk_swift_leave(void);                                /* FUN_00355bb8 */
extern void sk_swift_lock(void);                                 /* FUN_0034e004 */
extern void sk_swift_free_pages(void);                           /* FUN_0036b270 */
extern void sk_swift_unlock(void);                               /* FUN_00350524 */
extern void sk_swift_state(void);                                /* FUN_00356364 */
extern void sk_swift_door(void);                                 /* FUN_00351b78 */
extern void sk_swift_badlock(void);                              /* FUN_00347fb4 */
extern void sk_swift_prev(void);                                 /* FUN_0034f688 */
extern void sk_swift_next(void);                                 /* FUN_00205844 */
extern unsigned long sk_swift_atomic_load(void);                 /* FUN_00354744 */
extern void sk_swift_bitset(void);                               /* FUN_0006e778 */
extern unsigned long sk_swift_cmp(void);                         /* FUN_0034f064 */
extern void sk_swift_shift(void);                                /* FUN_003563fc */
extern void sk_swift_strlen(void);                               /* FUN_0035354c */
extern void sk_swift_substr(void);                               /* FUN_00208418 */
extern void sk_swift_concat(void);                               /* FUN_00354a00 */
extern unsigned long sk_swift_split(void);                       /* FUN_0034f98c */
extern void sk_swift_join(void);                                 /* FUN_0034c3a0 */
extern void sk_swift_append(void);                               /* FUN_003511d8 */
extern void sk_swift_insert(void);                               /* FUN_0034a390 */
extern void sk_swift_remove(void);                               /* FUN_0034ef38 */
extern void sk_swift_replace(void);                              /* FUN_002a4c98 */
extern void sk_swift_find(void);                                 /* FUN_0034bf64 */
extern void sk_swift_rfind(void);                                /* FUN_003510b8 */
extern void sk_swift_trim(void);                                 /* FUN_0034b7c8 */
extern void sk_swift_lower(void);                                /* FUN_00354e0c */
extern void sk_swift_upper(void);                                /* FUN_00350868 */
extern void sk_swift_any(void);                                  /* FUN_0006f768 */
extern void sk_swift_reserve(void);                              /* FUN_00352c58 */
extern void sk_swift_scan(void);                                 /* FUN_00357cec */
extern void sk_swift_get_cap(void);                              /* FUN_002a9ba8 */
extern void sk_swift_set_cap(void);                              /* FUN_002af618 */
extern void sk_swift_free(void);                                 /* FUN_0036b118 */

/*--------------------------------------------------------------------*/
/* FUN_001b012c @ 0x001b012c   (est. cl4_fatal_abort)
 * Ghidra: void FUN_001b012c(void)
 * Trivial noreturn abort: immediately enters the shared fatal-error trap
 * (FUN_001afe4c). Used as a stub target for unrecoverable kernel faults.
 * Confidence: high (single noreturn call).
 */
void cl4_fatal_abort(void)
{
    sk_fatal_error(0, 0);   /* FUN_001afe4c — noreturn */
}

/*--------------------------------------------------------------------*/
/* FUN_001b0174 @ 0x001b0174   (est. cl4_swift_dispatch_msg)
 * Ghidra: void FUN_001b0174(undefined8, undefined8, ulong, long, ulong)
 * Swift-message entry wrapper: enters a sync region, validates an UnsafeBufferPointer
 * argument (param_3, length param_4, flags param_5). For non-copy (bit0 clear) it
 * bounds-checks and pins the buffer; for copy (bit0 set) it bounds-checks against the
 * 0xe000..0x1000-capped fast path and materialises a counted copy via FUN_00255d4c.
 * On any invalid shape it panics (FUN_001afe4c) after the standard teardown.
 * Confidence: low (Swift buffer validation + fatal-error plumbing).
 */
void cl4_swift_dispatch_msg(void *a, void *b, unsigned long len, long cap, unsigned long flags)
{
    (void)a; (void)b;
    sk_sync_ops_1(0);            /* FUN_00354a34 */
    sk_sync_ops_2(0);            /* FUN_0035694c */
    if ((flags & 1) == 0) {
        if (len == 0) goto bad;
        if (cap < 0) { sk_bad_pointer(); sk_fatal_error(0, 0); }
        sk_obj_alloc_buf(0);     /* FUN_00355968 */
    } else {
        if (len >> 0x20 != 0) { sk_swift_overflow(); sk_swift_fail(); sk_swift_fail2(); sk_fatal_error(0, 0); }
        if ((0x10 < len >> 0x10) || (0xfffffffffffff7ff < len - 0xe000)) goto bad;
        unsigned long n = 1;
        if (0x7f < len) {
            sk_swift_detect_tiny(0);    /* FUN_00356d2c */
            n = (len >> 0x12) & 0x3fff;
            n += (unsigned long)(-0x7e7e7e0f);
            if (len < 0x800) n = 1;
        }
        sk_str_fast_count((int)len + (int)n);  /* FUN_00255d4c */
    }
    sk_swift_emit(0);            /* FUN_003528ac */
    cl4_swift_dispatch_msg2(0, 0, 0, 0, 0);  /* FUN_001b0294 */
bad:
    sk_swift_die();              /* FUN_00348898(1) */
    sk_swift_die2();             /* FUN_0034a2f8 */
    sk_fatal_error(0, 0);
}

/*--------------------------------------------------------------------*/
/* FUN_001b0294 @ 0x001b0294   (est. cl4_swift_dispatch_msg2)
 * Ghidra: void FUN_001b0294(undefined8, undefined8, ulong, long, ulong)
 * Companion to FUN_001b0174: same UnsafeBufferPointer validation under a different
 * sync gate (FUN_00357ca0/FUN_00355d9c), then routes to FUN_001b03f4. On invalid
 * shape it panics after standard teardown.
 * Confidence: low (Swift buffer validation; duplicate of 0174 with different gate).
 */
void cl4_swift_dispatch_msg2(void *a, void *b, unsigned long len, long cap, unsigned long flags)
{
    (void)a; (void)b;
    sk_swift_sync(0);            /* FUN_00357ca0 */
    sk_swift_sync_ret(0);        /* FUN_00355d9c */
    if ((flags & 1) == 0) {
        if (len == 0) goto bad;
        if (cap < 0) { sk_bad_pointer(); sk_fatal_error(0, 0); }
        sk_obj_alloc_buf(0);     /* FUN_00355968 */
    } else {
        if (len >> 0x20 != 0) { sk_swift_overflow(); sk_swift_fail(); sk_swift_fail2(); sk_fatal_error(0, 0); }
        if ((0x10 < len >> 0x10) || (0xfffffffffffff7ff < len - 0xe000)) goto bad;
        unsigned long n = 1;
        if (0x7f < len) {
            sk_swift_detect_tiny(0);    /* FUN_00356d2c */
            n = (len >> 0x12) & 0x3fff;
            n += (unsigned long)(-0x7e7e7e0f);
            if (len < 0x800) n = 1;
        }
        sk_str_fast_count((int)len + (int)n);  /* FUN_00255d4c */
    }
    sk_swift_pin(0);             /* FUN_00351584 */
    sk_swift_unpin(0);           /* FUN_003591f4 */
    cl4_swift_validate_msg(0, 0, 0, 0, 0, 0, 0);  /* FUN_001b03f4 */
bad:
    sk_swift_die();              /* FUN_00348898(1) */
    sk_swift_die2();             /* FUN_0034a2f8 */
    sk_fatal_error(0, 0);
}

/*--------------------------------------------------------------------*/
/* FUN_001b03f4 @ 0x001b03f4   (est. cl4_swift_validate_msg)
 * Ghidra: void FUN_001b03f4(long, ulong, long, ulong, long, ulong, ulong)
 * Multi-field validation of a Swift message: requires cap!=0, len/idx non-negative,
 * and the 64-bit count field (param_7) to fit in 32 bits. On the happy path calls
 * FUN_0035ab60 + FUN_003d2dd4 then hits a SoftwareBreakpoint(1,0x1b0494) (unreachable
 * continuation marker); any failed check panics.
 * Confidence: low (Swift precondition/assert scaffolding).
 */
void cl4_swift_validate_msg(long a, unsigned long b, long cap, unsigned long len,
                            long c, unsigned long d, unsigned long count)
{
    (void)a; (void)b; (void)c; (void)d;
    if (cap != 0) {
        if (len >> 0x1f == 0) {
            if (c == 0) goto bad;
            if (d >> 0x1f == 0) {
                if (a == 0) goto bad;
                if (b >> 0x1f == 0) {
                    if (count >> 0x20 == 0) {
                        sk_swift_ckrange();    /* FUN_0035ab60 */
                        sk_swift_ckrange2();   /* FUN_003d2dd4 */
                        /* SoftwareBreakpoint(1, 0x1b0494) — unreachable continuation */
                        __builtin_trap();
                    }
                    sk_swift_overflow(b);
                }
            }
        }
        sk_swift_fail();
        sk_swift_fail2();
        sk_fatal_error(0, 0);
    }
bad:
    sk_swift_die();              /* FUN_00348898(1) */
    sk_swift_die2();             /* FUN_0034a2f8 */
    sk_fatal_error(0, 0);
}

/*--------------------------------------------------------------------*/
/* FUN_001b04c8 @ 0x001b04c8   (est. cl4_swift_msg_enter)
 * Ghidra: void FUN_001b04c8(undefined8, undefined8, ulong, long, uint)
 * Swift message entry: non-copy path bounds-checks (len!=0, cap>=0) then calls
 * FUN_00355968 and a target; copy path validates the 0xe000-capped fast window and
 * dispatches through DAT_00658c00 to FUN_002558d0(FUN_003196b8). Any failure panics.
 * Confidence: low (Swift buffer entry + indirect dispatch).
 */
void cl4_swift_msg_enter(void *a, void *b, unsigned long len, long cap, unsigned int flags)
{
    (void)a; (void)b;
    if ((flags & 1) == 0) {
        if (len != 0) {
            if (-1 < cap) {
                sk_obj_alloc_buf(0);    /* FUN_00355968 */
                /* (*extraout_x12)() — indirect target */
                return;
            }
            sk_bad_pointer();           /* FUN_0034846c */
            goto bad;
        }
        sk_swift_panic_msg(0);          /* FUN_00350410 */
    } else {
        if (len >> 0x20 != 0) {
            sk_swift_panic_msg(0);      /* FUN_00350410 */
            sk_swift_fail();            /* FUN_00348194 */
            sk_swift_fail2();           /* FUN_003523f0 */
            goto bad;
        }
        if ((len >> 0x10 < 0x11) && (len - 0xe000 < 0xfffffffffffff800)) {
            /* (*DAT_00658c00)() then FUN_002558d0(FUN_003196b8) */
            sk_swift_dispatch(0);
            return;
        }
        sk_swift_panic_msg(0);          /* FUN_00350410 */
    }
    sk_swift_die();                     /* FUN_00348898 */
    sk_swift_die2();                    /* FUN_0034a2f8 */
bad:
    sk_fatal_error(0, 0);
}

/*--------------------------------------------------------------------*/
/* FUN_001b05d8 @ 0x001b05d8   (est. cl4_swift_msg_copy)
 * Ghidra: void FUN_001b05d8(undefined8, undefined8, undefined8, long, uint)
 * Swift copy-message wrapper: validates the length (param_3) and capacity, then for
 * the copy fast-path materialises a counted buffer via FUN_00255d4c, pins/unpins it
 * and forwards to FUN_001b0710. Non-copy path checks param_3!=0, cap>=0 and forwards
 * directly. Failure panics.
 * Confidence: low (Swift buffer copy + forward).
 */
void cl4_swift_msg_copy(void *a, void *b, unsigned long len, long cap, unsigned int flags)
{
    int hi = (int)((unsigned long)len >> 0x20);
    unsigned int lo = (unsigned int)len;
    (void)a; (void)b;
    sk_swift_sync(0);            /* FUN_00357ca0 */
    sk_swift_sync_ret(0);        /* FUN_00355d9c */
    if ((flags & 1) == 0) {
        if (((unsigned long)hi << 0x20 | (unsigned long)lo) != 0) {
            if (cap < 0) { sk_bad_pointer(); sk_fatal_error(0, 0); }
            sk_obj_alloc_buf(0); /* FUN_00355968 */
            sk_swift_pin(0);     /* FUN_00351584 */
            sk_swift_unpin(0);   /* FUN_003591f4 */
            sk_swift_store(0, 0);/* FUN_00357c44 */
            cl4_swift_validate_msg2(0, 0, 0, 0, 0, 0, 0);  /* FUN_001b0710 */
            return;
        }
    } else {
        if (hi != 0) {
            sk_swift_overflow(); /* FUN_003583dc */
            sk_swift_fail();     /* FUN_00348194 */
            sk_swift_fail2();    /* FUN_003523f0 */
            sk_fatal_error(0, 0);
        }
        if ((lo >> 0x10 < 0x11) && ((unsigned long)lo - 0xe000 < 0xfffffffffffff800)) {
            int n;
            if (lo < 0x80) {
                n = lo + 1;
            } else {
                sk_swift_detect_tiny(0);   /* FUN_00357d0c */
                n = 0;
                if (0x7ff < ((unsigned long)hi << 0x20 | (unsigned long)lo)) n = 0;
            }
            sk_str_fast_count(n);          /* FUN_00255d4c */
            sk_swift_pin(0);               /* FUN_00351584 */
            sk_swift_unpin(0);             /* FUN_003591f4 */
            cl4_swift_validate_msg2(0, 0, 0, 0, 0, 0, 0);  /* FUN_001b0710 */
            sk_swift_store(0, 0);          /* FUN_00357c44 */
            return;
        }
    }
    sk_swift_die();              /* FUN_00348898(1) */
    sk_swift_die2();             /* FUN_0034a2f8 */
    sk_fatal_error(0, 0);
}

/*--------------------------------------------------------------------*/
/* FUN_001b0710 @ 0x001b0710   (est. cl4_swift_validate_msg2)
 * Ghidra: void FUN_001b0710(long, ulong, long, ulong, long, ulong, ulong)
 * Same multi-field validation as FUN_001b03f4 but on success calls
 * FUN_0035ab60 + FUN_003d2dd4 directly (no breakpoint), and a zero first-pointer
 * goes to FUN_00358ca4. Failed checks panic.
 * Confidence: low (Swift precondition scaffolding).
 */
void cl4_swift_validate_msg2(long a, unsigned long b, long cap, unsigned long len,
                             long c, unsigned long d, unsigned long count)
{
    (void)a; (void)b; (void)c; (void)d;
    if (cap != 0) {
        if (len >> 0x1f == 0) {
            if (c == 0) goto bad;
            if (d >> 0x1f == 0) {
                if (a == 0) { sk_swift_badptr(); goto bad; }
                if (b >> 0x1f == 0) {
                    if (count >> 0x20 == 0) {
                        sk_swift_ckrange();    /* FUN_0035ab60 */
                        sk_swift_ckrange2();   /* FUN_003d2dd4 */
                        return;
                    }
                    sk_swift_overflow(b);      /* FUN_003583dc */
                }
            }
        }
        sk_swift_fail();         /* FUN_00348194 */
        sk_swift_fail2();        /* FUN_003523f0 */
        sk_fatal_error(0, 0);
    }
bad:
    sk_swift_die();              /* FUN_00348898 */
    sk_swift_die2();             /* FUN_0034a2f8 */
    sk_fatal_error(0, 0);
}

/*--------------------------------------------------------------------*/
/* FUN_001b07b8 @ 0x001b07b8   (est. cl4_trap_cap_resolve)
 * Ghidra: void FUN_001b07b8(undefined8, code*, undefined8, undefined8)
 * Resolves a capability word stored at *x20: if the tagged-object bit (bit60) is set
 * it unwraps via FUN_0001d4a0/FUN_003a25d4; then interprets bits 61/60 to compute a
 * {word, pointer} pair and invokes the target callback. For the user/endpoint path it
 * falls into FUN_00291d70 string formatting. This is the cap->endpoint dispatch glue.
 * Confidence: low (capability decode; heavy indirect structure).
 */
void cl4_trap_cap_resolve(void *a, void (*cb)(void *, unsigned long, unsigned long), void *b, void *c)
{
    (void)a; (void)b; (void)c;
    unsigned long w = *(unsigned long *)((char *)0 + 8);  /* *unaff_x20 + 8 */
    if ((w >> 0x3c & 1) != 0) {
        /* FUN_0001d4a0, FUN_003a25d4 unwrap tagged object; store back to *x20 */
        sk_swift_cast16(0);
        sk_swift_meta(0);
    }
    if ((w >> 0x3d & 1) == 0) {
        unsigned long p0 = 0, p1 = w;
        if ((p0 >> 0x3c & 1) == 0) {
            /* FUN_002a9ba8 resolve pair */
            sk_swift_get_cap(p0, p1);
        } else {
            p0 = (w & 0xfffffffffffffff) + 0x20;
        }
        cb(a, p0, p1);
    } else {
        /* (*DAT_00658c00)(w >> 0x38 & 0xf); FUN_00291d70 string format path */
        sk_swift_dispatch(w >> 0x38 & 0xf);
        sk_swift_utf16_slice(0);
    }
}

/*--------------------------------------------------------------------*/
/* FUN_001b0938 @ 0x001b0938   (est. cl4_swift_msg_enter2)
 * Ghidra: void FUN_001b0938(undefined8, undefined8, uint)
 * Swift message entry variant that first obtains a state pair via FUN_00353d70,
 * then validates/flattens the buffer pointer (0x1c00-capped fast window with
 * FUN_00354504 classification and FUN_00255d4c count) before FUN_003523fc dispatch
 * and a breakpoint continuation. Failure panics.
 * Confidence: low (Swift buffer entry; same shape as 0174/04c8).
 */
void cl4_swift_msg_enter2(void *a, void *b, unsigned int flags)
{
    (void)a; (void)b;
    unsigned long *p = (unsigned long *)sk_swift_trap_slot(0);  /* FUN_00353d70 */
    if ((flags & 1) == 0) {
        if (p != 0) {
            if ((long)p < 0) { sk_bad_pointer(); sk_fatal_error(0, 0); }
            goto dispatch;
        }
    } else {
        if ((unsigned long)p >> 0x20 != 0) {
            unsigned long r = sk_swift_overflow(0);  /* FUN_003583dc */
            sk_swift_fail();                          /* FUN_00348194 */
            sk_swift_fail2();                         /* FUN_003523f0 */
            sk_fatal_error(0, 0);
        }
        if (((unsigned long)p >> 0x10 < 0x11) && (p + -0x1c00 < (unsigned long *)0xfffffffffffff800)) {
            unsigned long n = 1;
            if (0x7f < (unsigned long)p) {
                unsigned long v = sk_swift_classify(p, 0);  /* FUN_00354504 */
                n = (v >> 0x12) & 0x3fff;
                n += (unsigned long)(-0x7e7e7e0f);
                if (v < 0x800) n = 1;
            }
            sk_str_fast_count((int)(unsigned long)p + (int)n);  /* FUN_00255d4c */
            p = 0;   /* local_38 address */
            goto dispatch;
        }
    }
    sk_swift_die(1, p);          /* FUN_00348898(1, p) */
    sk_swift_die2();             /* FUN_0034a2f8 */
    sk_fatal_error(0, 0);
dispatch:
    sk_swift_dispatch(p);        /* FUN_003523fc */
    cl4_swift_msg_resolve();     /* FUN_001b0a7c */
    __builtin_trap();            /* SoftwareBreakpoint(1, 0x1b09d0) */
}

/*--------------------------------------------------------------------*/
/* FUN_001b0a7c @ 0x001b0a7c   (est. cl4_swift_msg_resolve)
 * Ghidra: void FUN_001b0a7c(void)
 * Resolves a capability/pointer pair (x19/x23) under the load/iret lock
 * (FUN_00357cb4/FUN_00357c74): unwraps tagged objects (bit60) via FUN_00350524 +
 * FUN_0001d4a0, and either resolves via FUN_002a9ba8 or FUN_00356364, then forwards
 * to FUN_001b0b3c. Ends with the epilogue.
 * Confidence: low (capability decode + forward; uses x19/x23/x24 regs).
 */
void cl4_swift_msg_resolve(void)
{
    sk_swift_load(0);            /* FUN_00357cb4 */
    sk_swift_leave(0);           /* FUN_00355bb8 */
    sk_swift_lock(0);            /* FUN_0034e004 */
    sk_swift_free_pages(0);      /* thunk_FUN_0036b270 */
    /* if (x19>>0x3c&1): FUN_00350524, FUN_0001d4a0, FUN_0034e0f4, FUN_003a25d4; x19=x24 */
    if ((0 /*unaff_x19*/ >> 0x3d & 1) != 0) {
        sk_swift_door(0);        /* FUN_00351b78 */
        cl4_swift_validate_msg3(0, 0, 0, 0);   /* FUN_001b0b3c */
        sk_swift_meta(0);
        sk_swift_iret(0);        /* FUN_00357c74 */
        return;
    }
    unsigned long p0 = 0, p1 = 0;
    /* if (x23>>0x3c&1)==0: FUN_002a9ba8() else { FUN_00356364(); p1 = x23 & mask; p0 = v; } */
    sk_swift_get_cap(p0, p1);    /* FUN_002a9ba8 */
    sk_swift_door(p0, p1);       /* FUN_00351b78 */
    cl4_swift_validate_msg3(0, 0, 0, 0);       /* FUN_001b0b3c */
    sk_swift_iret(0);            /* FUN_00357c74 */
    sk_swift_meta(0);            /* FUN_003a25d4 */
}

/*--------------------------------------------------------------------*/
/* FUN_001b0b3c @ 0x001b0b3c   (est. cl4_swift_validate_msg3)
 * Ghidra: void FUN_001b0b3c(long, ulong, long, ulong)
 * Final message-field validation: requires cap!=0 and a non-negative index; on the
 * happy path calls FUN_003d2f10(cap,len,a,b). Failed checks panic.
 * Confidence: low (Swift precondition scaffolding).
 */
void cl4_swift_validate_msg3(long a, unsigned long b, long cap, unsigned long len)
{
    (void)a; (void)b;
    if (cap != 0) {
        if (len >> 0x1f == 0) {
            if (a == 0) goto bad;
            if (b >> 0x1f == 0) {
                sk_swift_uint_conv2(cap, len, a, b);  /* FUN_003d2f10 */
                return;
            }
        }
        sk_swift_badlock();      /* FUN_00347fb4 */
        sk_swift_fail2();        /* FUN_003523f0 */
        sk_fatal_error(0, 0);
    }
bad:
    sk_swift_die();              /* FUN_00348898(1) */
    sk_swift_die2();             /* FUN_0034a2f8 */
    sk_fatal_error(0, 0);
}

/*--------------------------------------------------------------------*/
/* FUN_001b0d2c @ 0x001b0d2c   (est. cl4_swift_ubp_validate_forward)
 * Ghidra: void FUN_001b0d2c(undefined8, undefined8, undefined8, ulong, long, ulong, ...)
 * Swift UnsafeBufferPointer validate+forward: checks the pointer/count pair
 * (param_4 length, param_5 capacity). Non-copy path rejects negative capacity and
 * forwards to FUN_001b0f78; copy path bounds-checks the 0xe000-capped fast window
 * (with the standard multi-level count decode via FUN_00255d4c) and forwards with a
 * materialised count. On any invalid shape, panics with Swift Fatal_error.
 * Confidence: low (Swift UnsafeBufferPointer precondition wrapper).
 */
void cl4_swift_ubp_validate_forward(void *a, void *b, void *c, unsigned long len,
                                    long cap, unsigned long flags, void *p7, void *p8,
                                    void *p9, void *p10, void *p11)
{
    (void)a; (void)b; (void)c;
    if ((flags & 1) == 0) {
        if (len != 0) {
            if (cap < 0)
                sk_fatal_error((unsigned long)"Fatal error", 0xb, 2,
                               (unsigned long)"UnsafeBufferPointer with negative index",
                               0x27, 2, (unsigned long)"Swift/UnsafeBufferPointer.swift",
                               0x1f, 2, 0x582, 1);
            cl4_swift_ubp_do(p7, len, cap, p8, p9, a, b, p10);  /* FUN_001b0f78 */
            return;
        }
    } else {
        if (len >> 0x20 != 0)
            sk_fatal_error((unsigned long)"Fatal error", 0xb, 2,
                           (unsigned long)"Not enough bits to represent the passed value",
                           0x2d, 2, (unsigned long)"Swift/Integers.swift", 0x14, 2, 0xcfc, 1);
        if ((len >> 0x10 < 0x11) && (len - 0xe000 < 0xfffffffffffff800)) {
            int n = (unsigned int)len + 1;
            if (len >= 0x80) {
                unsigned int v5 = (unsigned int)len;
                unsigned int v3 = (v5 & 0x3f) * 0x100;
                unsigned int v2 = (v3 | v5 >> 6 & 0x3f) * 0x100;
                int i1 = (v5 >> 0x12) + (v2 | v5 >> 0xc & 0x3f) * 0x100 + -0x7e7e7e0f;
                if (len >> 0x10 == 0) i1 = (v5 >> 0xc) + v2 + 0x8181e1;
                n = (v5 >> 6) + v3 + 0x81c1;
                if (0x7ff < len) n = i1;
            }
            /* FUN_00255d4c(n) materialises counted copy */
            cl4_swift_ubp_do(p7, len, cap, p8, p9, a, b, p10, p11);  /* FUN_001b0f78 */
            return;
        }
    }
    sk_fatal_error((unsigned long)"Fatal error", 0xb, 2,
                   (unsigned long)"Unexpectedly found nil while unwrapping", 0x39, 2,
                   (unsigned long)"Swift/StaticString.swift", 0x18, 2, (unsigned long)(flags & 1 ? 0x94 : 0x88), 1);
}

/*--------------------------------------------------------------------*/
/* FUN_001b0f78 @ 0x001b0f78   (est. cl4_swift_ubp_do)
 * Ghidra: void FUN_001b0f78(undefined8, undefined8, undefined8, ulong, long, ulong, ...)
 * Same UnsafeBufferPointer validate+forward shape as FUN_001b0d2c but forwards to
 * FUN_001b11bc. Faithful duplicate with a different tail target.
 * Confidence: low (Swift UnsafeBufferPointer precondition wrapper).
 */
void cl4_swift_ubp_do(void *a, void *b, void *c, unsigned long len, long cap,
                      unsigned long flags, void *p7, void *p8, void *p9, void *p10)
{
    (void)a; (void)b; (void)c;
    if ((flags & 1) == 0) {
        if (len != 0) {
            if (cap < 0)
                sk_fatal_error((unsigned long)"Fatal error", 0xb, 2,
                               (unsigned long)"UnsafeBufferPointer with negative index",
                               0x27, 2, (unsigned long)"Swift/UnsafeBufferPointer.swift",
                               0x1f, 2, 0x582, 1);
            cl4_swift_range_math(p7, len, cap, p8, a, b, p9, p10);  /* FUN_001b11bc */
            return;
        }
    } else {
        if (len >> 0x20 != 0)
            sk_fatal_error((unsigned long)"Fatal error", 0xb, 2,
                           (unsigned long)"Not enough bits to represent the passed value",
                           0x2d, 2, (unsigned long)"Swift/Integers.swift", 0x14, 2, 0xcfc, 1);
        if ((len >> 0x10 < 0x11) && (len - 0xe000 < 0xfffffffffffff800)) {
            int n = (unsigned int)len + 1;
            if (len >= 0x80) {
                unsigned int v5 = (unsigned int)len;
                unsigned int v3 = (v5 & 0x3f) * 0x100;
                unsigned int v2 = (v3 | v5 >> 6 & 0x3f) * 0x100;
                int i1 = (v5 >> 0x12) + (v2 | v5 >> 0xc & 0x3f) * 0x100 + -0x7e7e7e0f;
                if (len >> 0x10 == 0) i1 = (v5 >> 0xc) + v2 + 0x8181e1;
                n = (v5 >> 6) + v3 + 0x81c1;
                if (0x7ff < len) n = i1;
            }
            cl4_swift_range_math(p7, len, cap, p8, a, b, p9, p10);  /* FUN_001b11bc */
            return;
        }
    }
    sk_fatal_error((unsigned long)"Fatal error", 0xb, 2,
                   (unsigned long)"Unexpectedly found nil while unwrapping", 0x39, 2,
                   (unsigned long)"Swift/StaticString.swift", 0x18, 2, (unsigned long)(flags & 1 ? 0x94 : 0x88), 1);
}

/*--------------------------------------------------------------------*/
/* FUN_001b11bc @ 0x001b11bc   (est. cl4_swift_range_math)
 * Ghidra: void FUN_001b11bc(long, long, long, long, long, long, ulong, ulong)
 * Swift Range/Integer conversion: requires all six pointers non-null, each 64-bit
 * index to fit in 32 bits, and the two count fields to fit in 32 bits; then calls
 * FUN_003d2f9c (the actual conversion). Any overflow/nil panics with Fatal_error.
 * Confidence: low (Swift Range precondition scaffolding).
 */
void cl4_swift_range_math(void *a, void *b, void *cap, long len, long c, long d,
                          unsigned long count1, unsigned long count2)
{
    (void)a; (void)b; (void)c; (void)d;
    if (cap == 0)
        sk_fatal_error((unsigned long)"Fatal error", 0xb, 2,
                       (unsigned long)"Unexpectedly found nil while unwrapping", 0x39, 2,
                       (unsigned long)"Swift/AssertCommon.swift", 0x18, 2, 0x10c, 1);
    if (len < -0x80000000)
        goto overflow;
    if (len < 0x80000000) {
        if (c == 0)
            sk_fatal_error((unsigned long)"Fatal error", 0xb, 2,
                           (unsigned long)"Unexpectedly found nil while unwrapping", 0x39, 2,
                           (unsigned long)"Swift/AssertCommon.swift", 0x18, 2, 0x10d, 1);
        if (d < -0x80000000) goto overflow;
        if (0x7fffffff < d) goto overflow2;
        if (a == 0)
            sk_fatal_error((unsigned long)"Fatal error", 0xb, 2,
                           (unsigned long)"Unexpectedly found nil while unwrapping", 0x39, 2,
                           (unsigned long)"Swift/AssertCommon.swift", 0x18, 2, 0x10e, 1);
        if (b < -0x80000000) goto overflow;
        if (0x7fffffff < b) goto overflow2;
        if ((count1 >> 0x20 == 0) && (count2 >> 0x20 == 0)) {
            sk_swift_uint_conv(cap, len, c, d, a, b, count1, count2, 0);  /* FUN_003d2f9c */
            return;
        }
        sk_fatal_error((unsigned long)"Fatal error", 0xb, 2,
                       (unsigned long)"Not enough bits to represent the passed value",
                       0x2d, 2, (unsigned long)"Swift/Integers.swift", 0x14, 2, 0xcfc, 1);
    }
overflow2:
    sk_fatal_error((unsigned long)"Fatal error", 0xb, 2,
                   (unsigned long)"Not enough bits to represent a signed value", 0x2b, 2,
                   (unsigned long)"Swift/Integers.swift", 0x14, 2, 0xdd3, 1);
overflow:
    sk_fatal_error((unsigned long)"Fatal error", 0xb, 2,
                   (unsigned long)"Not enough bits to represent a signed value", 0x2b, 2,
                   (unsigned long)"Swift/Integers.swift", 0x14, 2, 0xdcd, 1);
}

/*--------------------------------------------------------------------*/
/* FUN_001b1780 @ 0x001b1780   (est. cl4_swift_finalize)
 * Ghidra: void FUN_001b1780(void)
 * Thin wrapper: runs FUN_0034f688 then FUN_00205844 and returns.
 * Confidence: medium (trivial two-call wrapper).
 */
void cl4_swift_finalize(void)
{
    sk_swift_prev(0);   /* FUN_0034f688 */
    sk_swift_next(0);   /* FUN_00205844 */
}

/*--------------------------------------------------------------------*/
/* FUN_001b17a0 @ 0x001b17a0   (est. cl4_swift_string_describe)
 * Ghidra: void FUN_001b17a0(void)
 * Swift string description builder: iterates the string's UTF-8 view using
 * FUN_00354744/FUN_0006e778 and appends character groups through a long chain of
 * append/format helpers (FUN_003a25d4, FUN_003563fc, FUN_00208418, FUN_00354a00,
 * FUN_0034bf64...). Contains the classic Swift "Fatal error" call at the tail.
 * Confidence: low (large Swift String debugDescription; heavy extraout chain).
 */
void cl4_swift_string_describe(void)
{
    unsigned long s = sk_swift_atomic_load(0);    /* FUN_00354744 */
    /* FUN_0006e778(0x3a); build a string pair from s */
    unsigned long bits = sk_swift_cmp(0);          /* FUN_0034f064 */
    if (bits & (1ull << 0x3d)) {
        /* non-trivial string: FUN_003563fc + append path */
        sk_swift_shift(0);                         /* FUN_003563fc */
    } else {
        /* inline small-string path */
        sk_swift_meta(0);
    }
    sk_swift_strlen(0, 0, 0x1b17a0);               /* FUN_0035354c */
    sk_swift_substr(0, 0, 0x1b1884);               /* FUN_00208418 */
    unsigned long n = sk_swift_split(0, 0);        /* FUN_0034f98c */
    if (n & (1ull << 0x3d)) {
        /* full string: FUN_0034c3a0 / FUN_003511d8 / FUN_0034a390 */
        sk_swift_join(0);
        sk_swift_replace(0);
    } else {
        sk_swift_append(0);
        sk_swift_insert(0);
        sk_swift_meta(0);
    }
    for (;;) {
        /* per-character append loop via FUN_0034bf64 / FUN_003510b8 / FUN_0034b7c8 */
        unsigned long i = sk_swift_find(0, 0);
        if (i & (1ull << 0x3d)) {
            sk_swift_upper(0x27);                  /* FUN_00350868(0x27) */
            sk_swift_replace(0);                   /* FUN_002a4c98 */
        } else {
            sk_swift_lower(0, 0, 0);               /* FUN_00354e0c */
            sk_swift_meta(0);
        }
        sk_swift_any((unsigned long)"Fatal error");/* FUN_0006f768 */
        cl4_swift_msg_enter2(0, 0, 0);             /* FUN_001b0938 */
        sk_swift_reserve(0);                       /* FUN_00352c58 */
        sk_swift_meta(0);
        sk_swift_scan(0x1b19dc);                   /* FUN_00357cec */
    }
}

/*--------------------------------------------------------------------*/
/* FUN_001b19ec @ 0x001b19ec   (est. cl4_swift_utf16_index_after)
 * Ghidra: void FUN_001b19ec(undefined8, undefined8, ulong)
 * Swift StringUTF16View index advancement (index(after:)): decodes the string word
 * (FUN_0001da84 for wide forms), validates the index stays in bounds (else Fatal
 * error "String index is out of bounds"), and steps the UTF-16 code unit via
 * FUN_002bbc14/FUN_002af618. Returns the advanced index word.
 * Confidence: low (Swift UTF-16 view index step; standard pattern).
 */
void cl4_swift_utf16_index_after(void *a, void *b, unsigned long idx)
{
    /* FUN_0006f768("Fatal error"); FUN_001b0938() obtains string state */
    unsigned long w = 0, base = 0;
    /* FUN_0001da84(w, base, idx) wide-form decode when (w&0xc)==4<<n */
    if (0x3fff < w) {
        if (w >> 0xe <= (base & 0xffffffffffff) << 2) {
            /* step through UTF-16 view: FUN_002a9ba8 / FUN_002bbc14 /
             * FUN_002af618 */
            sk_swift_utf16_get(w);
            sk_swift_utf16_set(w);
        } else {
            sk_fatal_error((unsigned long)"Fatal error", 0xb, 2,
                           (unsigned long)"String index is out of bounds", 0x1d, 2,
                           (unsigned long)"Swift/StringUTF16View.swift", 0x1b, 2, 0xaf, 1);
        }
    }
    /* *state = w; return; */
}

/*--------------------------------------------------------------------*/
/* FUN_001b19f0 @ 0x001b19f0   (est. cl4_swift_utf16_index_after_alias)
 * Ghidra: void FUN_001b19f0(undefined8, undefined8, ulong)
 * Identical to FUN_001b19ec (StringUTF16View index after). Decompiler alias.
 * Confidence: low (duplicate of 001b19ec).
 */
void cl4_swift_utf16_index_after_alias(void *a, void *b, unsigned long idx)
{
    cl4_swift_utf16_index_after(a, b, idx);
}

/*--------------------------------------------------------------------*/
/* FUN_001b1a2c @ 0x001b1a2c   (est. cl4_swift_utf16_index_step)
 * Ghidra: void FUN_001b1a2c(ulong*, ulong, ulong)
 * Swift StringUTF16View index step on an in/out index word: decodes, bounds-checks,
 * and advances by one UTF-16 unit, writing the result back through param_1.
 * Confidence: low (Swift UTF-16 view index step; pointer-form of 001b19ec).
 */
void cl4_swift_utf16_index_step(unsigned long *idx, unsigned long base, unsigned long flags)
{
    unsigned long w = *idx;
    /* FUN_0001da84 wide decode */
    if (0x3fff < w) {
        if (w >> 0xe <= (base & 0xffffffffffff) << 2) {
            sk_swift_utf16_get(w);   /* FUN_002a9ba8 */
            sk_swift_utf16_set(w);   /* FUN_002af618 */
        } else {
            sk_fatal_error((unsigned long)"Fatal error", 0xb, 2,
                           (unsigned long)"String index is out of bounds", 0x1d, 2,
                           (unsigned long)"Swift/StringUTF16View.swift", 0x1b, 2, 0xaf, 1);
        }
        *idx = w;
    }
}

/*--------------------------------------------------------------------*/
/* FUN_001b1c98 @ 0x001b1c98   (est. cl4_object_service_teardown)
 * Ghidra: void FUN_001b1c98(void)
 * Object-service teardown: saves CPU state (FUN_00084220) and runs a sequence of
 * service helpers (FUN_0034a958, FUN_00350bd8, ... FUN_00377824) before the thread
 * epilogue FUN_00084234. Same shape as the object teardown seen in region 0x28.
 * Confidence: low (long helper chain; identity from structure only).
 */
void cl4_object_service_teardown(void)
{
    /* FUN_00084220 / FUN_0034a958 / FUN_00350bd8 / FUN_00349748 /
     * FUN_00377824 / FUN_00348d64 / FUN_0007c1a4 / (*DAT_00658c00) /
     * FUN_0034b05c / FUN_003547ec / FUN_0034ee48 / FUN_0031e104 /
     * FUN_00351250 / FUN_003504a0 / FUN_0034ded4 / FUN_00084234 */
    sk_swift_state(0);
    sk_swift_lock(0);
}

/*--------------------------------------------------------------------*/
/* FUN_001b1d5c @ 0x001b1d5c   (est. cl4_swift_utf16_index_offset)
 * Ghidra: ulong FUN_001b1d5c(ulong, long, ulong, ulong)
 * Swift StringUTF16View index offset(by:): advances (or, for negative count,
 * retreats) a UTF-16 index by a signed count, handling wide string forms via
 * FUN_0001da84 and per-unit stepping via FUN_001676cc / FUN_002a9ba8. Out-of-bounds
 * steps panic with "String index is out of bounds".
 * Confidence: low (Swift UTF-16 view index offset; bounded loop).
 */
unsigned long cl4_swift_utf16_index_offset(unsigned long idx, long count,
                                           unsigned long base, unsigned long flags)
{
    unsigned long out = idx;
    if (count < 0) {
        /* retreat: loop FUN_001b1a2c(&out, base, flags) |count| times */
        for (long k = 0; count < k; k--) cl4_swift_utf16_index_step(&out, base, flags);
    } else {
        unsigned long ubase = base & 0xffffffffffff;
        if (flags & 0x2000000000000000) ubase = flags >> 0x38 & 0xf;
        int neg = (long)base < 0;
        if (flags & 0x2000000000000000) neg = (int)(flags >> 0x3e) & 1;
        unsigned long sz = 8;
        if (flags & 0x1000000000000000) sz = 4L << (base >> 0x3b & 1);
        for (; count != 0; count--) {
            if ((out & 0xc) == sz) out = sk_swift_utf16_fwd(out, base, flags); /* FUN_0001da84 */
            unsigned long c = out >> 0x10;
            if (ubase <= c)
                sk_fatal_error((unsigned long)"Fatal error", 0xb, 2,
                               (unsigned long)"String index is out of bounds", 0x1d, 2,
                               (unsigned long)"Swift/StringUTF16View.swift", 0x1b, 2, 0x93, 1);
            if ((flags >> 0x3c & 1) == 0) {
                if (neg == 0) {
                    if ((out & 0xc001) == 0) {
                        out = sk_swift_utf16_fwd(out, base, flags);  /* FUN_001676cc */
                        c = out >> 0x10;
                    }
                    /* advance one unit; wide handling via FUN_002a9ba8 */
                    out = ((out & 0xffffffffffff0000) | 5);
                    out = (out + 0x10000) & 0xffffffffffff0000 | 5;
                } else {
                    out = (out & 0xffffffffffff0000) + 0x1000d;
                }
            } else {
                out = sk_swift_utf16_set(out);  /* FUN_002af4d0 */
            }
        }
    }
    return out;
}

/*--------------------------------------------------------------------*/
/* FUN_001b1ff0 @ 0x001b1ff0   (est. cl4_swift_utf8_index_offset)
 * Ghidra: void FUN_001b1ff0(undefined*, long, ulong, ulong)
 * Swift StringUTF8View index offset(by:): advances or retreats a UTF-8 index by a
 * signed count, handling wide string forms via FUN_0001da84 and the UTF-8 view
 * step helpers FUN_002b14c8/FUN_002b141c. Out-of-bounds panics.
 * Confidence: low (Swift UTF-8 view index offset).
 */
void cl4_swift_utf8_index_offset(void *idx, long count, unsigned long base, unsigned long flags)
{
    unsigned long sz = 8;
    if (flags & 0x1000000000000000) sz = 4L << (base >> 0x3b & 1);
    unsigned long ubase = base & 0xffffffffffff;
    if (flags & 0x2000000000000000) ubase = flags >> 0x38 & 0xf;
    unsigned long w = (unsigned long)idx;
    if (count < 0) {
        for (long k = 0; count < k; k--) {
            if ((w & 0xc) == sz) w = sk_swift_utf16_fwd(w, base, flags); /* FUN_0001da84 */
            if (w >> 0xe == 0)
                sk_fatal_error((unsigned long)"Fatal error", 0xb, 2,
                               (unsigned long)"String index is out of bounds", 0x1d, 2,
                               (unsigned long)"Swift/StringUTF8View.swift", 0x1a, 2, 0x98, 1);
            if ((flags >> 0x3c & 1) == 0)
                w = (w & 0xffffffffffff0000) - 0xfffc;
            else {
                if (ubase < w >> 0x10)
                    sk_fatal_error((unsigned long)"Fatal error", 0xb, 2,
                                   (unsigned long)"String index is out of bounds", 0x1d, 2,
                                   (unsigned long)"Swift/StringUTF8View.swift", 0x1a, 2, 0x9d, 1);
                w = (unsigned long)(void *)sk_swift_utf8_prev((void *)w, base, flags); /* FUN_002b14c8 */
            }
        }
    } else {
        for (; count != 0; count--) {
            if ((w & 0xc) == sz) w = sk_swift_utf16_fwd(w, base, flags); /* FUN_0001da84 */
            if ((flags >> 0x3c & 1) != 0) {
                if (w >> 0x10 < ubase) {
                    w = (unsigned long)(void *)sk_swift_utf8_next((void *)w, base, flags); /* FUN_002b141c */
                    goto retreat;
                }
                sk_fatal_error((unsigned long)"Fatal error", 0xb, 2,
                               (unsigned long)"String index is out of bounds", 0x1d, 2,
                               (unsigned long)"Swift/StringUTF8View.swift", 0x1a, 2, 0x90, 1);
            }
            w = (w & 0xffffffffffff0000) + 4;  /* &DAT_00010004 + (w & ~0xffff) */
        }
    }
    return;
retreat:
    /* continue negative loop */
    for (long k = 0; count < k; k--) {
        if ((w & 0xc) == sz) w = sk_swift_utf16_fwd(w, base, flags);
        if (w >> 0xe == 0)
            sk_fatal_error((unsigned long)"Fatal error", 0xb, 2,
                           (unsigned long)"String index is out of bounds", 0x1d, 2,
                           (unsigned long)"Swift/StringUTF8View.swift", 0x1a, 2, 0x98, 1);
        if ((flags >> 0x3c & 1) == 0) w = (w & 0xffffffffffff0000) - 0xfffc;
        else {
            if (ubase < w >> 0x10)
                sk_fatal_error((unsigned long)"Fatal error", 0xb, 2,
                               (unsigned long)"String index is out of bounds", 0x1d, 2,
                               (unsigned long)"Swift/StringUTF8View.swift", 0x1a, 2, 0x9d, 1);
            w = (unsigned long)(void *)sk_swift_utf8_prev((void *)w, base, flags);
        }
    }
}

/*--------------------------------------------------------------------*/
/* FUN_001b2174 @ 0x001b2174   (est. cl4_object_service_drain)
 * Ghidra: void FUN_001b2174(void)
 * Object-service drain loop: saves CPU state (FUN_00084220), takes the service lock
 * (FUN_00377824), and dispatches a work callback through (*x16+0x10), then loops
 * |x21| times calling per-item helpers (FUN_003196e8/FUN_0034c5fc or
 * FUN_00027818/FUN_000dbdf4/FUN_00350c20) before the epilogue FUN_00084234.
 * Confidence: low (object-service dispatch loop; helper identities unknown).
 */
void cl4_object_service_drain(void)
{
    /* FUN_00084220 / FUN_00350b54 / FUN_00357bc4 / FUN_00352894 /
     * FUN_00349748 / FUN_003508d8 / FUN_00377824 / FUN_00349530 /
     * (**(code**)(x16+0x10))() */
    long n = 0;  /* unaff_x21 */
    if (n < 0) {
        for (long k = 0; n < k; k--) {
            /* FUN_003196e8 / FUN_0034c5fc */
        }
    } else {
        for (; n != 0; n--) {
            /* FUN_00027818 / FUN_000dbdf4 / FUN_00350c20 */
        }
    }
    /* FUN_00084234 epilogue */
}

/*--------------------------------------------------------------------*/
/* FUN_001b2264 @ 0x001b2264   (est. cl4_object_service_run)
 * Ghidra: void FUN_001b2264(void)
 * Object-service run path: gets the current CPU (FUN_0008e518), reads its work
 * slots (+0x10/+0x18/+0x24/+0x2c), and drives the dispatch helpers
 * (FUN_00377824, (*DAT_00658c00), FUN_00377bec...) with a completion callback
 * FUN_000839d8 before the thread epilogue FUN_0008e500. Heavy extraout chain.
 * Confidence: low (object-service run loop; identity from structure only).
 */
void cl4_object_service_run(void)
{
    /* FUN_0008e518 current CPU; cpu->work at +0x10/+0x18, count at +0x24 */
    unsigned long cpu = 0;
    (void)cpu;
    sk_swift_lock(0);            /* FUN_00377824 */
    sk_swift_get_cap(0, 0);      /* FUN_002a9ba8 */
    /* loop: FUN_00377bec / FUN_00027754 / FUN_0035a478 / FUN_00377824 /
     * (*DAT_00658c00) / dispatch via (x13+0x10); epilogue FUN_000839d8/FUN_0008e500 */
    sk_swift_state(0);
}

/*--------------------------------------------------------------------*/
/* FUN_001b260c @ 0x001b260c   (est. cl4_swift_utf16_find_char)
 * Ghidra: undefined1[16] FUN_001b260c(ulong, long, ulong, ulong, ulong)
 * Swift StringUTF16View scan for a character/range: iterates the UTF-16 index from
 * param_1 to param_3, stepping per unit and returning a {index, found} pair. The
 * (index ^ target)<0x4000 test detects out-of-buffer (returns found=1). Wide forms
 * via FUN_0001da84.
 * Confidence: low (Swift UTF-16 view bounded scan).
 */
cl4_result_t cl4_swift_utf16_find_char(unsigned long idx, long count, unsigned long target,
                                       unsigned long base, unsigned long flags)
{
    cl4_result_t r = { idx, 0 };
    if (count < 0) {
        for (long k = 0; count < k; k--) {
            if ((idx ^ target) < 0x4000) { r.lo = 0; r.hi = 1; return r; }
            cl4_swift_utf16_index_step(&idx, base, flags);
        }
    } else {
        for (; count != 0; count--) {
            if ((idx ^ target) < 0x4000) { r.lo = 0; r.hi = 1; return r; }
            if ((idx & 0xc) == 4L << ((flags >> 0x3b) & 1 ? (base >> 0x3b & 1) : 1))
                idx = sk_swift_utf16_fwd(idx, base, flags);   /* FUN_0001da84 */
            /* step UTF-16 unit */
            idx = ((idx + 0x10000) & 0xffffffffffff0000) | 5;
        }
    }
    r.lo = idx;
    return r;
}

/*--------------------------------------------------------------------*/
/* FUN_001b28d4 @ 0x001b28d4   (est. cl4_swift_utf8_find_char)
 * Ghidra: undefined1[16] FUN_001b28d4(undefined*, long, ulong, ulong, ulong)
 * Swift StringUTF8View scan for a character/range, mirroring FUN_001b260c but over
 * the UTF-8 view (step helpers FUN_002b14c8/FUN_002b141c). Returns {index, found}.
 * Confidence: low (Swift UTF-8 view bounded scan).
 */
cl4_result_t cl4_swift_utf8_find_char(void *idx, long count, unsigned long target,
                                      unsigned long base, unsigned long flags)
{
    cl4_result_t r = { (unsigned long)idx, 0 };
    unsigned long w = (unsigned long)idx;
    unsigned long sz = 4L << (base >> 0x3b & 1);
    if ((flags & 0x1000000000000000) == 0) sz = 8;
    if (count < 0) {
        unsigned long ubase = base & 0xffffffffffff;
        if (flags & 0x2000000000000000) ubase = flags >> 0x38 & 0xf;
        for (long k = 0; count < k; k--) {
            if ((w ^ target) < 0x4000) { r.lo = 0; r.hi = 1; return r; }
            if ((w & 0xc) == sz) w = sk_swift_utf16_fwd(w, base, flags);
            if (w >> 0xe == 0)
                sk_fatal_error((unsigned long)"Fatal error", 0xb, 2,
                               (unsigned long)"String index is out of bounds", 0x1d, 2,
                               (unsigned long)"Swift/StringUTF8View.swift", 0x1a, 2, 0x98, 1);
            if ((flags >> 0x3c & 1) == 0) w = (w & 0xffffffffffff0000) - 0xfffc;
            else {
                if (ubase < w >> 0x10)
                    sk_fatal_error((unsigned long)"Fatal error", 0xb, 2,
                                   (unsigned long)"String index is out of bounds", 0x1d, 2,
                                   (unsigned long)"Swift/StringUTF8View.swift", 0x1a, 2, 0x9d, 1);
                w = (unsigned long)(void *)sk_swift_utf8_prev((void *)w, base, flags);
            }
        }
    } else {
        for (; count != 0; count--) {
            if ((w ^ target) >> 0xe == 0) { r.lo = 0; r.hi = 1; return r; }
            if ((w & 0xc) == sz) w = sk_swift_utf16_fwd(w, base, flags);
            if ((flags >> 0x3c & 1) != 0) {
                unsigned long ubase = base & 0xffffffffffff;
                if (flags & 0x2000000000000000) ubase = flags >> 0x38 & 0xf;
                if (w >> 0x10 < ubase) {
                    w = (unsigned long)(void *)sk_swift_utf8_next((void *)w, base, flags);
                    goto retreat;
                }
                sk_fatal_error((unsigned long)"Fatal error", 0xb, 2,
                               (unsigned long)"String index is out of bounds", 0x1d, 2,
                               (unsigned long)"Swift/StringUTF8View.swift", 0x1a, 2, 0x90, 1);
            }
            w = (w & 0xffffffffffff0000) + 4;
        }
    }
    r.lo = w;
    return r;
retreat:
    for (long k = 0; count < k; k--) {
        if ((w ^ target) < 0x4000) { r.lo = 0; r.hi = 1; return r; }
        if ((w & 0xc) == sz) w = sk_swift_utf16_fwd(w, base, flags);
        if (w >> 0xe == 0)
            sk_fatal_error((unsigned long)"Fatal error", 0xb, 2,
                           (unsigned long)"String index is out of bounds", 0x1d, 2,
                           (unsigned long)"Swift/StringUTF8View.swift", 0x1a, 2, 0x98, 1);
        if ((flags >> 0x3c & 1) == 0) w = (w & 0xffffffffffff0000) - 0xfffc;
        else {
            if (ubase < w >> 0x10)
                sk_fatal_error((unsigned long)"Fatal error", 0xb, 2,
                               (unsigned long)"String index is out of bounds", 0x1d, 2,
                               (unsigned long)"Swift/StringUTF8View.swift", 0x1a, 2, 0x9d, 1);
            w = (unsigned long)(void *)sk_swift_utf8_prev((void *)w, base, flags);
        }
    }
    r.lo = w;
    return r;
}

/*--------------------------------------------------------------------*/
/* FUN_001b2a90 @ 0x001b2a90   (est. cl4_object_service_drain2)
 * Ghidra: void FUN_001b2a90(void)
 * Object-service drain variant: current CPU (FUN_0008e518), locks, and iterates a
 * work list |x25| times, dispatching per-item helpers (FUN_00377bec/FUN_003196e8)
 * and on completion calling FUN_00351548 before the epilogue FUN_000839d8/
 * FUN_0008e500. Returns success flag via x2.
 * Confidence: low (object-service drain loop).
 */
void cl4_object_service_drain2(void)
{
    /* FUN_0008e518 / FUN_00355544 / FUN_00354ba4 / FUN_00351ef8 /
     * FUN_003582f8 / FUN_00350920 / FUN_00354388 / FUN_00377824 /
     * FUN_00348e00 / (*DAT_00658c00) / FUN_00348a18 / FUN_0034c2d8 */
    unsigned long n = 0;  /* unaff_x25 */
    if (n < 0) {
        /* FUN_003510c4; per-item FUN_0034cfb4/FUN_00377bec/FUN_0034c4fc/
         * FUN_00354d68/FUN_0034df74; on flag: FUN_00351e54/FUN_003507d4, ret=1 */
        for (long k = 0; n < k; k--) {
            if (1) { sk_swift_lock(0); goto done; }  /* completion flag */
        }
        sk_swift_state(0);
    } else {
        for (; n != 0; n--) {
            /* FUN_0034cfb4/FUN_00377bec/FUN_00349fe0/FUN_0034d344;
             * on flag: FUN_00351e54/FUN_00100efc, ret=1 */
            if (1) { sk_swift_lock(0); goto done; }
            /* FUN_00027818/FUN_000dbdf4/FUN_00351e9c */
        }
        sk_swift_state(0);
    }
done:
    sk_swift_reserve(0);   /* FUN_00351548 */
    /* FUN_000839d8 / FUN_0008e500 epilogue */
}

/*--------------------------------------------------------------------*/
/* FUN_001b2c90 @ 0x001b2c90   (est. cl4_object_service_drain3)
 * Ghidra: void FUN_001b2c90(void)
 * Object-service drain variant: current CPU (FUN_0008e518), locks, and loops over
 * a work count |x26|, dispatching per-item helpers (FUN_0034ede8/FUN_00377bec/
 * FUN_00352ee4...). Completion (flag set) calls FUN_00351548 before the epilogue
 * FUN_000839d8/FUN_0008e500. Negative count panics.
 * Confidence: low (object-service drain loop; helper identities unknown).
 */
void cl4_object_service_drain3(void)
{
    /* FUN_0008e518 / FUN_00352068 / FUN_00356900 / FUN_0034e808 /
     * FUN_00377824 / FUN_00348e00 / FUN_0007c1a4 / (*DAT_00658c00) / FUN_0034bdfc */
    long n = 0;  /* unaff_x26 */
    if (n < 0) {
        /* FUN_00350410 / FUN_003488bc / FUN_00349a2c / FUN_0035110c */
        sk_fatal_error(0, 0);
    }
    /* FUN_0034bfb4 */
    for (;;) {
        if (n == 0) {
            /* FUN_00350278(x12+0x20); completion */
            sk_swift_reserve(0, 0);   /* FUN_00351548 */
            /* FUN_000839d8 / FUN_0008e500 epilogue */
            return;
        }
        /* FUN_0034ede8 / FUN_00377bec / FUN_00352ee4 / FUN_00350adc /
         * FUN_003509e0 / FUN_0035130c */
        if (1) {   /* completion flag */
            /* FUN_00351924 / FUN_003507e0 / FUN_0035a5c0 */
            sk_swift_reserve(0, 0);
            /* FUN_000839d8 / FUN_0008e500 epilogue */
            return;
        }
        /* FUN_00027818 / FUN_00350a88 / FUN_00350b48 */
        n -= 1;
    }
}

/*--------------------------------------------------------------------*/
/* FUN_001b2e08 @ 0x001b2e08   (est. cl4_swift_utf8_distance)
 * Ghidra: long FUN_001b2e08(undefined*, ulong, ulong, ulong)
 * Swift StringUTF8View distance(from:to:): computes the number of UTF-8 code units
 * between two indices (param_1 and param_2) by stepping forward (or backward)
 * through the view, handling wide forms via FUN_0001da84 and the UTF-8 step helpers
 * FUN_002b141c/FUN_002b14c8. Out-of-bounds panics.
 * Confidence: low (Swift UTF-8 view distance).
 */
long cl4_swift_utf8_distance(void *from, unsigned long to, unsigned long base, unsigned long flags)
{
    unsigned long w = (unsigned long)from;
    unsigned long hilo = base >> 0x20;
    if (w >> 0xe < to >> 0xe) {
        /* forward scan */
        unsigned long sz = (hilo >> 0x1b & 1);
        if ((flags & 0x1000000000000000) == 0) sz = 1;
        unsigned long ubase = base & 0xffffffffffff;
        if (flags & 0x2000000000000000) ubase = flags >> 0x38 & 0xf;
        long d = 0;
        do {
            long nd = d + 1;
            if (__builtin_add_overflow(d, 1, &d)) __builtin_trap();  /* SWBP 0x1b2f78 */
            if ((w & 0xc) == 4L << sz) w = sk_swift_utf16_fwd(w, base, flags); /* FUN_0001da84 */
            if ((flags >> 0x3c & 1) != 0) {
                if (w >> 0x10 < ubase) {
                    w = (unsigned long)(void *)sk_swift_utf8_next((void *)w, base, flags); /* FUN_002b141c */
                    goto retreat;
                }
                goto ob;
            }
            w = (w & 0xffffffffffff0000) + 4;
            d = nd;
        } while (to >> 0xe != w >> 0xe);
        return d;
    }
retreat:
    if (to >> 0xe < w >> 0xe) {
        unsigned long sz = (hilo >> 0x1b & 1);
        if ((flags & 0x1000000000000000) == 0) sz = 1;
        unsigned long ubase = base & 0xffffffffffff;
        if (flags & 0x2000000000000000) ubase = flags >> 0x38 & 0xf;
        long d = 0;
        do {
            bool borrow;
            long nd = d - 1;
            (void)borrow;
            if (d == 0) { /* SBORROW8 */ __builtin_trap(); } /* SWBP 0x1b2f7c */
            if ((w & 0xc) == 4L << sz) w = sk_swift_utf16_fwd(w, base, flags);
            if (w >> 0xe == 0) goto ob;
            if ((flags >> 0x3c & 1) == 0) w = (w & 0xffffffffffff0000) - 0xfffc;
            else {
                if (ubase < w >> 0x10) goto ob;
                w = (unsigned long)(void *)sk_swift_utf8_prev((void *)w, base, flags); /* FUN_002b14c8 */
            }
            d = nd;
        } while (to >> 0xe != w >> 0xe);
        return d;
    }
    return 0;
ob:
    sk_fatal_error((unsigned long)"Fatal error", 0xb, 2,
                   (unsigned long)"String index is out of bounds", 0x1d, 2,
                   (unsigned long)"Swift/StringUTF8View.swift", 0x1a, 2, 0x90, 1);
}

/*--------------------------------------------------------------------*/
/* FUN_001b2fdc @ 0x001b2fdc   (est. cl4_object_service_dispatch2)
 * Ghidra: void FUN_001b2fdc(undefined8, undefined8, undefined8, undefined8)
 * Object-service dispatch: current CPU (FUN_0008e518), takes the service lock
 * (FUN_00377824), and walks a queue, pulling items via FUN_00377bec and dispatching
 * through FUN_003196e8/FUN_00027818 until the completion check returns 1. Ends
 * with FUN_0035a3d0 + epilogue FUN_0008e500.
 * Confidence: low (object-service queue dispatch).
 */
void cl4_object_service_dispatch2(void *a, void *b, void *c, void *d)
{
    (void)a; (void)b; (void)c; (void)d;
    /* FUN_0008e518 / FUN_00355cbc / FUN_00351ef8 / FUN_0034d070 /
     * FUN_0034d8d4 / FUN_00377824 / FUN_00348e18 / FUN_0007c1a4 /
     * (*DAT_00658c00) / FUN_0034b05c / FUN_00352bb0 / FUN_0034e56c /
     * FUN_0034ba38 / FUN_00377bec / FUN_0034c638 / FUN_003510dc / FUN_0034df34 */
    unsigned long flag = 0;
    if ((flag & 1) == 0) {
        /* FUN_00310b08(c) / FUN_0034e61c / FUN_0034df34 */
        if (1) {   /* flag */
            /* FUN_00351ef8(c); FUN_0014ae44; dispatch loop via FUN_003196e8 */
            long k = 0;
            do {
                k -= 1;
                if (k == -1) __builtin_trap();  /* SWBP 0x1b31ec */
                /* (*pcVar4)(); FUN_00351274; FUN_00350ac4 */
            } while ((1 & 1) == 0);   /* completion flag */
        }
    } else {
        /* FUN_00351ad4(c); FUN_0014ae44; dispatch loop via FUN_00027818 */
        long k = 0;
        do {
            if (__builtin_add_overflow(k, 1, &k)) __builtin_trap();  /* SWBP 0x1b31e8 */
            /* (*pcVar4)(); FUN_00350b6c; FUN_00350ac4 */
        } while ((1 & 1) == 0);
    }
    /* FUN_0035060c(x16+8); FUN_0035a3d0; FUN_0008e500 epilogue */
}

/*--------------------------------------------------------------------*/
/* FUN_001b31ec @ 0x001b31ec   (est. cl4_object_service_run2)
 * Ghidra: void FUN_001b31ec(void)
 * Object-service run path: current CPU (FUN_0008e518), takes the service lock
 * (FUN_00377824) and drives the dispatch helpers, checking a completion flag; on
 * completion calls FUN_000839d8/FUN_0008e500 epilogue. Heavy extraout chain with
 * many (*DAT_00658c00) indirect dispatches. Failure path panics.
 * Confidence: low (object-service run loop; identity from structure only).
 */
void cl4_object_service_run2(void)
{
    /* FUN_0008e518 / FUN_0035125c / FUN_0034a3c4 / FUN_0034b358 /
     * FUN_00377824 / FUN_00348bf8 / FUN_003722e4 / FUN_000a6f88 /
     * (*DAT_00658c00) ... FUN_00350464 / FUN_00377bec / FUN_00310e08 ... */
    unsigned long cpu = 0;
    (void)cpu;
    if (1) {   /* completion flag */
        /* FUN_00350eb0 */
        /* FUN_0008e500 / FUN_000839d8 epilogue */
        return;
    }
    cl4_object_service_run3(0, 0);   /* FUN_001b3c0c */
    /* FUN_00351bac / FUN_00350884 / dispatch chain ... */
    if (1) {   /* in_ZR failure branch */
        sk_swift_die(0x13b);   /* FUN_003489dc(0x13b) */
        sk_swift_die2();       /* FUN_0034a2f8 */
    } else {
        /* FUN_0034b07c / (x16_02+0x20) / (x16_01+0x10) dispatch chain */
        /* FUN_00350c38 / FUN_003508a8 / FUN_00310e20 / FUN_00350804 /
         * FUN_003512cc ... on completion: FUN_00350560 / FUN_00351118 /
         * FUN_0035399c / FUN_00351274 ... epilogue FUN_000839d8/FUN_0008e500 */
        if (1) {   /* completion flag */
            sk_swift_state(0);
            /* FUN_000839d8 / FUN_0008e500 epilogue */
            return;
        }
        sk_swift_badlock(0);   /* FUN_00347d60 */
    }
    sk_fatal_error(0, 0);
}

/*--------------------------------------------------------------------*/
/* FUN_001b36ec @ 0x001b36ec   (est. cl4_swift_unicode_scalar_prev)
 * Ghidra: ulong FUN_001b36ec(ulong, ulong)
 * Swift StringUnicodeScalarView index(before:): locates the scalar preceding the
 * given UTF-16 index, walking back over continuation bytes (0x80-0xbf), then
 * decodes the multibyte scalar (2/3/4-byte UTF-8) via FUN_00167404. Returns the
 * decoded Unicode scalar value. Out-of-bounds panics.
 * Confidence: low (Swift Unicode scalar view predecessor).
 */
unsigned long cl4_swift_unicode_scalar_prev(unsigned long idx, unsigned long flags)
{
    unsigned long ubase = idx & 0xffffffffffff;
    if (flags & 0x2000000000000000) ubase = flags >> 0x38 & 0xf;
    if (ubase == 0) return 0x100000000;   /* empty view sentinel */
    unsigned long sz = (idx >> 0x3b & 1);
    if ((flags & 0x1000000000000000) == 0) sz = 1;
    unsigned long kind = 7;
    if (sz == 0) kind = 0xb;
    unsigned long w = sk_swift_utf16_set(kind | ubase << 0x10);   /* FUN_002ab130 */
    if (w >> 0xe == 0)
        sk_fatal_error((unsigned long)"Fatal error", 0xb, 2,
                       (unsigned long)"String index is out of bounds", 0x1d, 2,
                       (unsigned long)"Swift/StringUnicodeScalarView.swift", 0x23, 2, 0x84, 1);
    /* walk back over continuation bytes, then decode scalar via FUN_00167404 */
    unsigned long scalar = sk_swift_utf8_scalar_prev(w, idx, flags);  /* FUN_00167404 */
    return scalar;
}

/*--------------------------------------------------------------------*/
/* FUN_001b3984 @ 0x001b3984   (est. cl4_swift_unicode_scalar_step)
 * Ghidra: ulong FUN_001b3984(ulong, ulong, ulong, ulong)
 * Swift StringUnicodeScalarView step: decodes the scalar at the current index
 * (via FUN_002ab130 / FUN_002a9ba8) after validating the (index^base) buffer
 * distance, handling 1/2/3/4-byte UTF-8 encodings. Returns the decoded scalar.
 * Confidence: low (Swift Unicode scalar view decode).
 */
unsigned long cl4_swift_unicode_scalar_step(unsigned long idx, unsigned long base,
                                            unsigned long p, unsigned long flags)
{
    (void)base;
    if ((idx ^ p) < 0x4000) return 0x100000000;   /* empty/end sentinel */
    unsigned long w = sk_swift_utf16_set(idx);     /* FUN_002ab130(idx, p, flags) */
    if (w >> 0xe == 0)
        sk_fatal_error((unsigned long)"Fatal error", 0xb, 2,
                       (unsigned long)"String index is out of bounds", 0x1d, 2,
                       (unsigned long)"Swift/StringUnicodeScalarView.swift", 0x23, 2, 0x84, 1);
    /* decode 1/2/3/4-byte scalar at buffer + w>>0x10 */
    unsigned long s = sk_swift_utf8_scalar_at(w, p, flags);  /* FUN_002a9ba8 + LZCOUNT decode */
    return s;
}

/*--------------------------------------------------------------------*/
/* FUN_001b3c0c @ 0x001b3c0c   (est. cl4_object_service_run3)
 * Ghidra: void FUN_001b3c0c(void)
 * Object-service run variant: current CPU (FUN_0008e518), takes the service lock
 * (FUN_00377824), dispatches through (*DAT_00658c00), and continues the service
 * loop. Ends with the standard service epilogue.
 * Confidence: low (object-service run loop).
 */
void cl4_object_service_run3(void)
{
    /* FUN_0008e518 / FUN_00353b10 / FUN_00352894 / FUN_00349748 /
     * FUN_003510a0 / FUN_00377824 / FUN_00348ce8 / (*DAT_00658c00) /
     * FUN_003489c0 / (*DAT_00658c00) */
    sk_swift_state(0);
}

/*--------------------------------------------------------------------*/
/* FUN_001b3dc0 @ 0x001b3dc0   (est. cl4_object_service_run4)
 * Ghidra: void FUN_001b3dc0(void)
 * Object-service run variant with a large helper chain: current CPU (FUN_0008e518),
 * locks, and drives the dispatch helpers before the service epilogue.
 * Confidence: low (object-service run loop; many helpers).
 */
void cl4_object_service_run4(void)
{
    /* FUN_0008e518 / FUN_00355748 / FUN_0034e004 / ... / FUN_00377824 /
     * (*DAT_00658c00) / ... */
    sk_swift_state(0);
}

/*--------------------------------------------------------------------*/
/* FUN_001b4274 @ 0x001b4274   (est. cl4_object_service_complete)
 * Ghidra: void FUN_001b4274(undefined8, undefined8, undefined8)
 * Object-service completion: current CPU (FUN_0008e518), takes the service lock
 * (FUN_00377824) and runs a long completion chain of dispatch helpers. On a
 * completion flag it calls FUN_00350704/FUN_003509d4 etc; failure panics. Ends
 * with the epilogue FUN_0008e500 (or a fatal error).
 * Confidence: low (object-service completion path; long helper chain).
 */
void cl4_object_service_complete(void *a, void *b, void *c)
{
    (void)a; (void)b; (void)c;
    /* FUN_0008e518 / FUN_00350780(c) / FUN_0034c158 / FUN_00351190 /
     * FUN_00377824 / FUN_0034a654 / FUN_00348cd0 / (*DAT_00658c00) /
     * FUN_00348bd8 / (*DAT_00658c00) / FUN_0034ac50 / FUN_0034e6bc /
     * FUN_00377bec / FUN_0034d734 / FUN_00310e08 / FUN_00348e18 /
     * FUN_0007c1a4 / (*DAT_00658c00) / FUN_0034eb2c / FUN_00358208 ... */
    unsigned long r = 0;
    if (r == 0) {
        /* FUN_0008e500 epilogue */
        return;
    }
    if ((long)r < 0) {
        sk_fatal_error(0, 0);
    } else {
        /* FUN_00350704 / FUN_003509d4 / FUN_000277b8 / FUN_0034e71c /
         * FUN_003195f8(c) / FUN_00351250 / FUN_00350494 /
         * (*extraout_x9_01)(...) / FUN_000e72b0 / FUN_0008e388 /
         * FUN_0034b2a8 */
        if (1) {   /* in_ZR branch */
            /* FUN_00351630 / FUN_00348b7c(0x15f) / FUN_0035863c / FUN_0034ea68 */
            sk_swift_state(0);
            goto epilogue;
        } else {
            /* FUN_0034d3d4 / FUN_00351990 / FUN_00352b5c / FUN_003509d4 /
             * FUN_00350944 / FUN_00352c8c / FUN_00310e20 / FUN_0034f4e4 /
             * FUN_00350bfc */
            if (1) {   /* flag */
                /* FUN_0034f4a4 / FUN_00350a70 / FUN_00352eb4 / FUN_003513a8 /
                 * FUN_00354364 / FUN_003504ac / FUN_0006b6f4 */
                goto epilogue;
            }
            sk_swift_badlock(0);   /* FUN_00347d60 */
        }
    }
    sk_fatal_error(0, 0);
epilogue:
    /* FUN_0008e500 */
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_001b4748 @ 0x001b4748   (est. cl4_swift_drop_last)
 * Ghidra: void FUN_001b4748(long, long, undefined8, undefined8, undefined8)
 * Swift BidirectionalCollection dropLast: validates n>=0 ("Can't drop a negative
 * number of elements"), computes the upper bound via FUN_0031f998, and builds a
 * suffix range via FUN_001ff4e0. Range inversion panics.
 * Confidence: low (Swift collection dropLast).
 */
void cl4_swift_drop_last(long n, long from, void *a, void *b, void *c)
{
    if (n < 0)
        sk_fatal_error((unsigned long)"Fatal error", 0xb, 2,
                       (unsigned long)"Can't drop a negative number of elements", 0x3a, 2,
                       (unsigned long)"Swift/BidirectionalCollection.swift", 0x23, 2, 0x17c, 1);
    /* FUN_0031f998(a, -n, from, b, c, 0x124, 300) computes end bound */
    long end = from;
    /* if (auVar2._8_4_ & 0xff) != 1: end = auVar2._0_8_ */
    if (from <= end) {
        /* FUN_001ff4e0(from, end, from, a, b, c, 0x26e, 0x26f) build range */
        return;
    }
    sk_fatal_error((unsigned long)"Fatal error", 0xb, 2,
                   (unsigned long)"Range requires lowerBound <= upperBound", 0x27, 2,
                   (unsigned long)"Swift/Range.swift", 0x11, 2, 0x2f9, 1);
}

/*--------------------------------------------------------------------*/
/* FUN_001b4d10 @ 0x001b4d10   (est. cl4_swift_suffix)
 * Ghidra: void FUN_001b4d10(long, long, long, undefined8, undefined8)
 * Swift BidirectionalCollection suffix: validates n>=0 ("Can't take a suffix of
 * negative length"), computes the start bound via FUN_0031f998, and builds the
 * suffix range via FUN_001ff4e0. Range inversion panics.
 * Confidence: low (Swift collection suffix).
 */
void cl4_swift_suffix(long n, long to, long from, void *a, void *b)
{
    if (n < 0)
        sk_fatal_error((unsigned long)"Fatal error", 0xb, 2,
                       (unsigned long)"Can't take a suffix of negative length", 0x38, 2,
                       (unsigned long)"Swift/BidirectionalCollection.swift", 0x23, 2, 0x19b, 1);
    long start = from;
    /* FUN_0031f998(a, -n, to, b, c, 0x124, 300) */
    /* if (auVar2._8_4_ & 0xff) != 1: start = auVar2._0_8_ */
    if (start <= to) {
        /* FUN_001ff4e0(start, to, to, a, b, c, 0x26e, 0x26f) */
        return;
    }
    sk_fatal_error((unsigned long)"Fatal error", 0xb, 2,
                   (unsigned long)"Range requires lowerBound <= upperBound", 0x27, 2,
                   (unsigned long)"Swift/Range.swift", 0x11, 2, 0x2f9, 1);
}

/*--------------------------------------------------------------------*/
/* FUN_001b52dc @ 0x001b52dc   (est. cl4_swift_fatal_1)
 * Ghidra: void FUN_001b52dc(void)
 * Noreturn fatal path: FUN_00348074(1) then FUN_00351be0, then panic.
 * Confidence: medium (noreturn helper pair).
 */
void cl4_swift_fatal_1(void)
{
    sk_swift_die2_0(1);   /* FUN_00348074(1) */
    sk_swift_fail2();     /* FUN_00351be0 */
    sk_fatal_error(0, 0);
}

/*--------------------------------------------------------------------*/
/* FUN_001b5310 @ 0x001b5310   (est. cl4_swift_fatal_2)
 * Ghidra: void FUN_001b5310(void)
 * Noreturn fatal path: FUN_00348404(1) then FUN_00351be0, then panic.
 * Confidence: medium (noreturn helper pair).
 */
void cl4_swift_fatal_2(void)
{
    sk_swift_die2_1(1);   /* FUN_00348404(1) */
    sk_swift_fail2();     /* FUN_00351be0 */
    sk_fatal_error(0, 0);
}

/*--------------------------------------------------------------------*/
/* FUN_001b5344 @ 0x001b5344   (est. cl4_swift_state_bump)
 * Ghidra: void FUN_001b5344(void)
 * Runs FUN_0034a74c + FUN_00354db8, calls FUN_00319748/FUN_000aa47c, then an
 * indirect helper. Returns normally.
 * Confidence: low (Swift/object state bump).
 */
void cl4_swift_state_bump(void)
{
    /* FUN_0034a74c / FUN_00354db8 / FUN_00319748 / FUN_000aa47c / (*extraout_x8)() */
    sk_swift_state(0);
}

/*--------------------------------------------------------------------*/
/* FUN_001b53c4 @ 0x001b53c4   (est. cl4_bitset_set)
 * Ghidra: bool FUN_001b53c4(void)
 * Atomic bit-set: under FUN_0035acc8, ORs a bit mask into a word and returns
 * whether the bit was previously clear. Classic set-if-unset primitive.
 * Confidence: high (clear bit-set shape).
 */
bool cl4_bitset_set(void)
{
    /* FUN_0035acc8; bitmask in extraout_x9, addr in x1+x8 */
    unsigned long word = *(volatile unsigned long *)0;
    *(volatile unsigned long *)0 = word | 0;   /* OR mask */
    return (word & 0) == 0;                    /* was-clear */
}

/*--------------------------------------------------------------------*/
/* FUN_001b5410 @ 0x001b5410   (est. cl4_bitset_clear)
 * Ghidra: bool FUN_001b5410(void)
 * Atomic bit-clear: under FUN_0035acc8, ANDs out a bit mask and returns whether
 * the bit was previously set. Classic clear-if-set primitive.
 * Confidence: high (clear bit-clear shape).
 */
bool cl4_bitset_clear(void)
{
    /* FUN_0035acc8; bitmask in extraout_x9, addr in x1+x8 */
    unsigned long word = *(volatile unsigned long *)0;
    *(volatile unsigned long *)0 = word & ~0;  /* AND ~mask */
    return (word & 0) != 0;                    /* was-set */
}

/*--------------------------------------------------------------------*/
/* FUN_001b545c @ 0x001b545c   (est. cl4_swift_fill_pre)
 * Ghidra: void FUN_001b545c(void)
 * Thin wrapper: FUN_00350c98 then FUN_001b5474.
 * Confidence: medium (trivial wrapper).
 */
void cl4_swift_fill_pre(void)
{
    sk_swift_state(0);        /* FUN_00350c98 */
    cl4_swift_fill(0, 0, 0);  /* FUN_001b5474 */
}

/*--------------------------------------------------------------------*/
/* FUN_001b5474 @ 0x001b5474   (est. cl4_swift_fill)
 * Ghidra: void FUN_001b5474(undefined8, long, undefined8*)
 * Fills an array of param_2 elements with param_1; a negative count panics.
 * Confidence: high (clear memset-style fill loop).
 */
void cl4_swift_fill(void *val, long count, void **dst)
{
    if (count >= 0) {
        for (; count != 0; count--) { *dst++ = val; }
        return;
    }
    sk_swift_die(1);    /* FUN_003488bc(1) */
    sk_swift_die3();    /* FUN_0034a368 */
    sk_swift_fail2();   /* FUN_00352e0c */
    sk_fatal_error(0, 0);
}

/*--------------------------------------------------------------------*/
/* FUN_001b5564 @ 0x001b5564   (est. cl4_swift_popcount_sum)
 * Ghidra: long FUN_001b5564(undefined8*, long)
 * Sums the bit-population counts of param_2 64-bit words; a negative count panics,
 * and integer overflow traps at a breakpoint.
 * Confidence: high (clear popcount-accumulate shape).
 */
long cl4_swift_popcount_sum(unsigned long *words, long count)
{
    if (count < 0) { sk_swift_badlock(0); sk_fatal_error(0, 0); }
    long total = 0;
    for (; count != 0; count--, words++) {
        unsigned long w = *words;
        long pc = __builtin_popcountll(w);
        if (__builtin_add_overflow(total, pc, &total))
            __builtin_trap();   /* SWBP 0x1b55b4 */
    }
    return total;
}

/*--------------------------------------------------------------------*/
/* FUN_001b55c0 @ 0x001b55c0   (est. cl4_swift_bitset_init)
 * Ghidra: void FUN_001b55c0(void)
 * Thin thunk to FUN_002c2da4 (bitset/collection init).
 * Confidence: medium (trivial thunk).
 */
void cl4_swift_bitset_init(void)
{
    sk_swift_bitset_ctor(0);   /* FUN_002c2da4 */
}

/*--------------------------------------------------------------------*/
/* FUN_001b55f8 @ 0x001b55f8   (est. cl4_swift_bitset_first)
 * Ghidra: undefined1[16] FUN_001b55f8(void)
 * Swift Bitset first index: iterates the word array (*x20) from the cursor (x20[2])
 * up to capacity (x20[1]); for each nonzero word, computes the index of the lowest
 * set bit via bit-reverse + LZCOUNT. Returns {index<<6 | bitpos, 0}.
 * Confidence: high (clear bitset lowest-set-bit scan).
 */
cl4_result_t cl4_swift_bitset_first(void)
{
    /* unaff_x20 = bitset: [0]=words ptr, [1]=capacity, [2]=cursor, [3]=current word */
    unsigned long cur = 0;  /* unaff_x20[3] */
    unsigned long idx = 0;  /* unaff_x20[2] */
    if (cur == 0) {
        while (1) {
            if (__builtin_add_overflow(idx, 1, &idx)) __builtin_trap();  /* SWBP 0x1b5674 */
            if (0 /* x20[1] */ <= idx) { return sk_swift_bitset_end(0); }  /* FUN_00068e14 */
            /* x20[2] = idx; cur = words[idx]; */
            cur = 0;
            if (cur != 0) break;
        }
    }
    /* reverse bits of cur, find leading-zero count = bit position */
    unsigned long rev = __builtin_bitreverse64(cur);
    /* x20[3] = cur - 1 & cur (clear lowest set bit) */
    cl4_result_t r = { (unsigned long)__builtin_clzll(rev) | idx << 6, 0 };
    return r;
}

/*--------------------------------------------------------------------*/
/* FUN_001b5674 @ 0x001b5674   (est. cl4_swift_bitset_next)
 * Ghidra: undefined1[16] FUN_001b5674(void)
 * Swift Bitset next: from the current word (*x20), finds the next set bit, clears
 * it, and returns {bitpos, 0}; empty sets return the end sentinel FUN_00068e14.
 * Confidence: high (clear bitset next-set-bit).
 */
cl4_result_t cl4_swift_bitset_next(void)
{
    unsigned long cur = 0;   /* *unaff_x20 */
    if (cur != 0) {
        unsigned long rev = __builtin_bitreverse64(cur);
        /* *x20 = cur - 1 & cur */
        cl4_result_t r = { (unsigned long)__builtin_clzll(rev), 0 };
        return r;
    }
    return sk_swift_bitset_end(0);   /* FUN_00068e14 */
}

/*--------------------------------------------------------------------*/
/* FUN_001b569c @ 0x001b569c   (est. cl4_swift_bitset_next_out)
 * Ghidra: void FUN_001b569c(undefined8*)
 * Writes the FUN_001b55f8 result into *param_1.
 * Confidence: medium (thin store wrapper).
 */
void cl4_swift_bitset_next_out(unsigned long *out)
{
    cl4_result_t r = cl4_swift_bitset_first();
    out[0] = r.lo;
    out[1] = r.hi;
}

/*--------------------------------------------------------------------*/
/* FUN_001b56c8 @ 0x001b56c8   (est. cl4_swift_bitset_scope)
 * Ghidra: void FUN_001b56c8(undefined1 (*)[16])
 * Swift Bitset makeIterator-ish: calls FUN_001b55c0 with *x20/x20[1], stores the
 * {word, 0} pair plus in_x3 into the out param.
 * Confidence: low (bitset iterator setup).
 */
void cl4_swift_bitset_scope(void *out)
{
    cl4_swift_bitset_init();   /* FUN_001b55c0 */
    /* *out = pair; out[1][8] = 0; out[1][8+8] = in_x3 */
    sk_swift_state(0);
}

/*--------------------------------------------------------------------*/
/* FUN_001b5708 @ 0x001b5708   (est. cl4_swift_string_ref)
 * Ghidra: undefined8 FUN_001b5708(void)
 * Calls FUN_001e8374, releases in_x3, returns the value.
 * Confidence: low (Swift string refcount wrapper).
 */
unsigned long cl4_swift_string_ref(void)
{
    unsigned long v = sk_swift_string_ref(0);   /* FUN_001e8374 */
    sk_swift_meta(0);                            /* FUN_003a25d4(in_x3) */
    return v;
}

/*--------------------------------------------------------------------*/
/* FUN_001b573c @ 0x001b573c   (est. cl4_swift_string_ref2)
 * Ghidra: undefined8 FUN_001b573c(void)
 * Calls FUN_001e851c, releases in_x3, returns the value.
 * Confidence: low (Swift string refcount wrapper).
 */
unsigned long cl4_swift_string_ref2(void)
{
    unsigned long v = sk_swift_string_ref2(0);   /* FUN_001e851c */
    sk_swift_meta(0);                            /* FUN_003a25d4(in_x3) */
    return v;
}

/*--------------------------------------------------------------------*/
/* FUN_001b5784 @ 0x001b5784   (est. cl4_swift_string_cvt)
 * Ghidra: undefined8 FUN_001b5784(void)
 * Runs FUN_00353ed8 + FUN_0007c1c4, calls FUN_001e9414, then an indirect helper,
 * and returns the value.
 * Confidence: low (Swift string conversion wrapper).
 */
unsigned long cl4_swift_string_cvt(void)
{
    /* FUN_00353ed8 / FUN_0007c1c4 / FUN_001e9414 / FUN_0034b3e8 /
     * (**(code**)(x16+8))() */
    unsigned long v = sk_swift_string_cvt(0);   /* FUN_001e9414 */
    return v;
}

/*--------------------------------------------------------------------*/
/* FUN_001b57e4 @ 0x001b57e4   (est. cl4_swift_attr_get1)
 * Ghidra: void FUN_001b57e4(void)
 * Thunk to FUN_00281cc0.
 * Confidence: medium (trivial thunk).
 */
void cl4_swift_attr_get1(void)
{
    sk_swift_attr_get(0);   /* FUN_00281cc0 */
}

/*--------------------------------------------------------------------*/
/* FUN_001b57e8 @ 0x001b57e8   (est. cl4_swift_attr_get1_alias)
 * Ghidra: void FUN_001b57e8(void)
 * Thunk to FUN_00281cc0 (alias of 001b57e4).
 * Confidence: medium (trivial thunk).
 */
void cl4_swift_attr_get1_alias(void)
{
    cl4_swift_attr_get1();
}

/*--------------------------------------------------------------------*/
/* FUN_001b5814 @ 0x001b5814   (est. cl4_swift_attr_get2)
 * Ghidra: void FUN_001b5814(void)
 * Thunk to FUN_00283a08.
 * Confidence: medium (trivial thunk).
 */
void cl4_swift_attr_get2(void)
{
    sk_swift_attr_get2(0);   /* FUN_00283a08 */
}

/*--------------------------------------------------------------------*/
/* FUN_001b5818 @ 0x001b5818   (est. cl4_swift_attr_get2_alias)
 * Ghidra: void FUN_001b5818(void)
 * Thunk to FUN_00283a08 (alias).
 * Confidence: medium (trivial thunk).
 */
void cl4_swift_attr_get2_alias(void)
{
    cl4_swift_attr_get2();
}

/*--------------------------------------------------------------------*/
/* FUN_001b5840 @ 0x001b5840   (est. cl4_swift_attr_get3)
 * Ghidra: void FUN_001b5840(void)
 * Thunk to FUN_00282bc0.
 * Confidence: medium (trivial thunk).
 */
void cl4_swift_attr_get3(void)
{
    sk_swift_attr_get3(0);   /* FUN_00282bc0 */
}

/*--------------------------------------------------------------------*/
/* FUN_001b5844 @ 0x001b5844   (est. cl4_swift_attr_get3_alias)
 * Ghidra: void FUN_001b5844(void)
 * Thunk to FUN_00282bc0 (alias).
 * Confidence: medium (trivial thunk).
 */
void cl4_swift_attr_get3_alias(void)
{
    cl4_swift_attr_get3();
}

/*--------------------------------------------------------------------*/
/* FUN_001b5890 @ 0x001b5890   (est. cl4_object_range_map)
 * Ghidra: long thunk_FUN_00284424(undefined8, long, long, undefined8, undefined8)
 * Thunk into FUN_00284424: takes the object lock (FUN_00377824), resolves method
 * tables, and maps a range of param_3 elements through the per-object stride
 * (*(table+0x48)), invoking per-element callbacks (FUN_00377bec/FUN_000a68f4).
 * Returns the final index. Complex Swift Range-mapping helper.
 * Confidence: low (thunk into 0x284424; range map with callback).
 */
long cl4_object_range_map(void *a, long src, long n, void *b, void *c)
{
    (void)a; (void)b; (void)c;
    /* FUN_00377824(0xff, c, b, &DAT_00611b24, &LAB_00611b34) lock
     * FUN_00310d68 / (*DAT_00658c00) stack setup
     * FUN_00377824(0, c, b, &DAT_00611b24, &DAT_00611b3c)
     * FUN_000a68c4(c) dispatch */
    if (n == 0) {
        return 0;
    }
    /* FUN_0026bd30(0, n) range pair; loop over elements:
     * FUN_00377bec / FUN_000a68f4 / FUN_000839f8 completion check
     * (**(table+0x20))(...) per-element callback with stride *(table+0x48) */
    long i = 0;
    return i;
}

/*--------------------------------------------------------------------*/
/* FUN_001b5894 @ 0x001b5894   (est. cl4_swift_complete_wrap)
 * Ghidra: void FUN_001b5894(void)
 * Thin wrapper to FUN_001b58b0.
 * Confidence: medium (trivial wrapper).
 */
void cl4_swift_complete_wrap(void)
{
    cl4_swift_complete(0);   /* FUN_001b58b0 */
}

/*--------------------------------------------------------------------*/
/* FUN_001b58b0 @ 0x001b58b0   (est. cl4_swift_complete)
 * Ghidra: void FUN_001b58b0(undefined8)
 * Runs FUN_00350744 then the completion callback FUN_000839d8.
 * Confidence: medium (two-call completion).
 */
void cl4_swift_complete(void *a)
{
    sk_swift_state(a);      /* FUN_00350744 */
    sk_swift_done();        /* FUN_000839d8 */
}

/*--------------------------------------------------------------------*/
/* FUN_001b593c @ 0x001b593c   (est. cl4_object_service_run5)
 * Ghidra: void FUN_001b593c(void)
 * Object-service run variant: current CPU (FUN_0008e518), locks, dispatches via
 * (*DAT_00658c00), and runs the service helper chain before the epilogue
 * FUN_0008e500.
 * Confidence: low (object-service run loop).
 */
void cl4_object_service_run5(void)
{
    /* FUN_0008e518 / FUN_000a6f88 / (*DAT_00658c00) / FUN_003490ec /
     * FUN_00352894 / FUN_0008f6c0 / FUN_0035a478 / FUN_00349d80 /
     * FUN_003508c0 / FUN_00377824 / FUN_0034a450 / FUN_0007c1a4 /
     * (*DAT_00658c00) / FUN_0034b0d4 / FUN_0035060c / FUN_00353c3c /
     * FUN_00377bec / FUN_003494fc / FUN_00350e44 / FUN_0034d558 /
     * FUN_0034d810 / FUN_001679cc / FUN_00351250 / FUN_00350524 /
     * FUN_0034eb94 / FUN_0008e500 */
    sk_swift_state(0);
}

/*--------------------------------------------------------------------*/
/* FUN_001b5a88 @ 0x001b5a88   (est. cl4_swift_method_call)
 * Ghidra: void FUN_001b5a88(undefined8, long)
 * Indirect method call through (*(param_2-8)+0x20)(param_1). Jumptable unrecovered.
 * Confidence: low (indirect method dispatch; "Could not recover jumptable").
 */
void cl4_swift_method_call(void *a, void *obj)
{
    /* (**(code**)(*(obj-8) + 0x20))(a) */
    void (*f)(void *) = *(void (**)(void *))((char *)obj - 8 + 0x20);
    f(a);
}

/*--------------------------------------------------------------------*/
/* FUN_001b5acc @ 0x001b5acc   (est. cl4_swift_bitset_next2)
 * Ghidra: void FUN_001b5acc(undefined8*)
 * Writes the FUN_001b5674 result into *param_1.
 * Confidence: medium (thin store wrapper).
 */
void cl4_swift_bitset_next2(unsigned long *out)
{
    cl4_result_t r = cl4_swift_bitset_next();
    out[0] = r.lo;
    out[1] = r.hi;
}

/*--------------------------------------------------------------------*/
/* FUN_001b5af8 @ 0x001b5af8   (est. cl4_swift_optional_store)
 * Ghidra: void FUN_001b5af8(long, undefined8, code*, undefined8, undefined8, long*)
 * Swift optional handling: if param_1 is non-null calls *param_3 (a store
 * callback) and stores unaff_x21 into *param_6; null forces a Fatal error
 * ("Unexpectedly found nil while unwrapping an Optional value", Bitset).
 * Confidence: low (Swift optional force-unwrap with callback).
 */
void cl4_swift_optional_store(long obj, void *a, void (*cb)(void), void *b, void *c, long *out)
{
    (void)a; (void)b; (void)c;
    if (obj != 0) {
        cb();
        if (out != 0) *out = 0;  /* unaff_x21 */
        return;
    }
    sk_fatal_error((unsigned long)"Fatal error", 0xb, 2,
                   (unsigned long)"Unexpectedly found nil while unwrapping an Optional value",
                   0x39, 2, (unsigned long)"Swift/Bitset.swift", 0x12, 2, 0x16d, 1);
}

/*--------------------------------------------------------------------*/
/* FUN_001b5b84 @ 0x001b5b84   (est. cl4_swift_fill_call)
 * Ghidra: void FUN_001b5b84(undefined8, undefined8, undefined8, code*)
 * Fills param_3 elements of param_2 with 0 (FUN_001b5474) then calls *param_4.
 * Confidence: medium (fill + callback).
 */
void cl4_swift_fill_call(void *a, void **dst, unsigned long n, void (*cb)(void *, void **, unsigned long))
{
    cl4_swift_fill(0, (long)n, dst);
    cb(a, dst, n);
}

/*--------------------------------------------------------------------*/
/* FUN_001b5bf0 @ 0x001b5bf0   (est. cl4_swift_flag_check)
 * Ghidra: bool FUN_001b5bf0(undefined8, undefined8, undefined8)
 * Checks a flag bit: FUN_0034c034/FUN_000db6e8(param_3)/FUN_0034bcf0 then tests
 * bit 0x20000 of an indirect result.
 * Confidence: low (flag bit test).
 */
bool cl4_swift_flag_check(void *a, void *b, void *c)
{
    (void)a; (void)b; (void)c;
    unsigned long v = sk_swift_flag(0);   /* (*extraout_x8)() */
    return (v & 0x20000) == 0;
}

/*--------------------------------------------------------------------*/
/* FUN_001b5c34 @ 0x001b5c34   (est. cl4_swift_flag_check2)
 * Ghidra: bool FUN_001b5c34(void)
 * Reads an 8-byte flag word via thunk_FUN_00054414 and tests bit 0x20000.
 * Confidence: high (clear flag-read + test).
 */
bool cl4_swift_flag_check2(void)
{
    unsigned long w = 0;
    /* thunk_FUN_00054414(&w, 8) */
    return (w & 0x20000) == 0;
}

/*--------------------------------------------------------------------*/
/* FUN_001b5cc0 @ 0x001b5cc0   (est. cl4_swift_flag_set)
 * Ghidra: void FUN_001b5cc0(undefined8, uint)
 * Sets flag bit 0/1 via FUN_00229a3c(param_2 & 1).
 * Confidence: medium (thin flag-set wrapper).
 */
void cl4_swift_flag_set(void *a, unsigned int flag)
{
    sk_swift_flag_set(flag & 1);   /* FUN_00229a3c */
}

/*--------------------------------------------------------------------*/
/* FUN_001b5ce8 @ 0x001b5ce8   (est. cl4_swift_flag_toggle)
 * Ghidra: void FUN_001b5ce8(void)
 * Computes a flag toggle from FUN_00348c48 + FUN_00351ca0 (xor of a constant
 * string-derived value), sets it via FUN_00229a3c, then FUN_001a8564.
 * Confidence: low (flag toggle + follow-on).
 */
void cl4_swift_flag_toggle(void)
{
    /* FUN_00348c48 / FUN_00351ca0(extraout_b0, s_"uespemosmodnarodarenegylsetybdet"...
     * , extraout_b0 ^ (byte)const) -> flag value */
    unsigned int flag = sk_swift_flag_calc(0);   /* FUN_00351ca0 */
    sk_swift_flag_set(flag & 1);                 /* FUN_00229a3c */
    sk_swift_state(0);                           /* FUN_001a8564 */
}

/*--------------------------------------------------------------------*/
/* FUN_001b5d4c @ 0x001b5d4c   (est. cl4_swift_string_kind)
 * Ghidra: undefined8 FUN_001b5d4c(ulong, ulong)
 * Classifies a Swift string by its {word, flags} pair: compares against the
 * literal strings "true" (0x65757274 / 0xe4...) and "false" (0x65736c6166 /
 * 0xe5...), returning 1 for true, 0 for false, 2 for other. Handles wide forms via
 * FUN_002a0d50.
 * Confidence: low (Swift String <-> Bool comparison helper).
 */
unsigned long cl4_swift_string_kind(unsigned long word, unsigned long flags)
{
    if (word == 0x65757274 && flags == 0xe400000000000000) return 1;      /* "true" */
    if (((flags ^ 0xffffffffffffffff) & 0x6000000000000000) == 0) {
        if (word == 0x65757274) return flags == 0xe400000000000000 ? 1 : 2;   /* true */
        if (word == 0x65736c6166) return flags == 0xe500000000000000 ? 0 : 2; /* false */
        return 2;
    }
    /* wide form: FUN_002a0d50 compare */
    unsigned long v = sk_swift_string_cmp2(0, 0, 0x65757274, 0xe400000000000000, 0); /* FUN_002a0d50 */
    if (v & 1) return 1;
    if (word == 0x65736c6166 && flags == 0xe500000000000000) return 0;
    sk_swift_state(0);
    sk_swift_meta(0);
    if ((word & 1) == 0) return 2;
    return 0;
}

/*--------------------------------------------------------------------*/
/* FUN_001b5e80 @ 0x001b5e80   (est. cl4_swift_string_kind_store)
 * Ghidra: void FUN_001b5e80(undefined1*)
 * Stores the FUN_001b5d4c result into *param_1 (a byte).
 * Confidence: medium (thin store wrapper).
 */
void cl4_swift_string_kind_store(unsigned char *out)
{
    *out = (unsigned char)cl4_swift_string_kind(0, 0);
}

/*--------------------------------------------------------------------*/
/* FUN_001b5ec0 @ 0x001b5ec0   (est. cl4_object_service_complete2)
 * Ghidra: void FUN_001b5ec0(void)
 * Object-service completion variant: current CPU (FUN_0008e518), locks, dispatches,
 * and on success runs the completion helpers then the epilogue FUN_0008e500; the
 * failure branch panics at FUN_003489dc(0x2a1).
 * Confidence: low (object-service completion; helper chain).
 */
void cl4_object_service_complete2(void)
{
    /* FUN_0008e518 / FUN_0035a6a8 / FUN_00350a64 / FUN_00310d68 /
     * FUN_00348e00 / (*DAT_00658c00) / FUN_003490d0 / FUN_0034b8bc /
     * FUN_0034fff0 / FUN_000839d8 / FUN_003197a8 / FUN_0034db88 /
     * FUN_00352e60 / FUN_00352468 / FUN_003510a0 / FUN_0034ad40 */
    if (1) {   /* success */
        /* FUN_003507bc(x16+8) / FUN_0034b518 / (x16_00+0x20) /
         * FUN_0008e500 epilogue */
        return;
    }
    sk_swift_die(0x2a1);   /* FUN_003489dc(0x2a1) */
    sk_swift_die2();       /* FUN_0034a2f8 */
    sk_fatal_error(0, 0);
}

/*--------------------------------------------------------------------*/
/* FUN_001b605c @ 0x001b605c   (est. cl4_swift_gstate_get)
 * Ghidra: undefined8 FUN_001b605c(void)
 * Runs FUN_0035310c + FUN_00355538, calls FUN_0036a940/FUN_00310d98, returns value.
 * Confidence: low (global-state getter).
 */
unsigned long cl4_swift_gstate_get(void)
{
    sk_swift_state(0);   /* FUN_0035310c */
    sk_swift_state2(0);  /* FUN_00355538 */
    return sk_swift_gstate(0);  /* FUN_0036a940 / FUN_00310d98 */
}

/*--------------------------------------------------------------------*/
/* FUN_001b6098 @ 0x001b6098   (est. cl4_swift_gstate_store)
 * Ghidra: void FUN_001b6098(undefined8)
 * Stores param_1 into a global state slot (x20+0x10) via FUN_00310d98.
 * Confidence: medium (thin store).
 */
void cl4_swift_gstate_store(void *v)
{
    sk_swift_gstore(v);   /* FUN_00310d98(v, x20+0x10) */
}

/*--------------------------------------------------------------------*/
/* FUN_001b609c @ 0x001b609c   (est. cl4_swift_gstate_store2)
 * Ghidra: void FUN_001b609c(undefined8)
 * Same as FUN_001b6098 (global state store).
 * Confidence: medium (duplicate store).
 */
void cl4_swift_gstate_store2(void *v)
{
    cl4_swift_gstate_store(v);
}

/*--------------------------------------------------------------------*/
/* FUN_001b60b8 @ 0x001b60b8   (est. cl4_swift_gstate_init)
 * Ghidra: void FUN_001b60b8(void)
 * Global-state initializer: zeroes a global object's four fields (+0x10/+0x18/
 * +0x20/+0x28) and links it into the singleton _DAT_006ade68 via FUN_00310d98.
 * Confidence: medium (clear global singleton init).
 */
void cl4_swift_gstate_init(void)
{
    /* FUN_0035a9f0(); FUN_00355538(0x678d00) */
    long g = sk_swift_gstate(0);   /* FUN_0036a940() */
    *(unsigned long *)(g + 0x10) = 0;
    *(unsigned long *)(g + 0x18) = 0;
    *(unsigned long *)(g + 0x20) = 0;
    *(unsigned long *)(g + 0x28) = 0;
    /* FUN_00355538(0x656860); g2 = FUN_0036a940();
     * FUN_00310d98(local_40, g2+0x10); _DAT_006ade68 = g2 */
    sk_swift_gstore(0);
}

/*--------------------------------------------------------------------*/
/* FUN_001b613c @ 0x001b613c   (est. cl4_swift_gstate_addr)
 * Ghidra: undefined1* FUN_001b613c(void)
 * Returns &DAT_006ade68 (the global-state singleton) after FUN_0034add4/FUN_0039a128.
 * Confidence: high (clear global address getter).
 */
void *cl4_swift_gstate_addr(void)
{
    sk_swift_state(0);   /* FUN_0034add4 */
    sk_swift_state2(0);  /* FUN_0039a128 */
    return &sk_swift_gstate_global;   /* &DAT_006ade68 */
}

/*--------------------------------------------------------------------*/
/* FUN_001b6174 @ 0x001b6174   (est. cl4_swift_gstate_free)
 * Ghidra: void FUN_001b6174(void)
 * Frees the global-state singleton _DAT_006ade68 via FUN_0036b270 after init.
 * Confidence: medium (global singleton free).
 */
void cl4_swift_gstate_free(void)
{
    sk_swift_state(0);   /* FUN_0034add4 */
    sk_swift_state2(0);  /* FUN_0039a128 */
    sk_swift_free_pages(sk_swift_gstate_global);  /* FUN_0036b270(_DAT_006ade68) */
}

/*--------------------------------------------------------------------*/
/* FUN_001b6198 @ 0x001b6198   (est. cl4_swift_gstate_link)
 * Ghidra: void FUN_001b6198(void)
 * Links x20+0x10 into the global via FUN_000026e8, then FUN_00353aac/FUN_0036b6ac.
 * Confidence: low (global linking).
 */
void cl4_swift_gstate_link(void)
{
    sk_swift_gstore(0);   /* FUN_000026e8(x20+0x10) */
    sk_swift_state(0);    /* FUN_00353aac */
    sk_swift_state2(0);   /* FUN_0036b6ac */
}

/*--------------------------------------------------------------------*/
/* FUN_001b619c @ 0x001b619c   (est. cl4_swift_gstate_link2)
 * Ghidra: void FUN_001b619c(void)
 * Duplicate of FUN_001b6198 (global linking).
 * Confidence: low (duplicate).
 */
void cl4_swift_gstate_link2(void)
{
    cl4_swift_gstate_link();
}

/*--------------------------------------------------------------------*/
/* FUN_001b61bc @ 0x001b61bc   (est. cl4_swift_global_relocate)
 * Ghidra: void FUN_001b61bc(undefined8, undefined8, undefined8)
 * Global relocation/registration path: current CPU (FUN_0008e518), locks, and walks
 * the global list (_DAT_006ade68 / _DAT_006c0160/_DAT_006c0168), invoking the
 * per-entry registration helpers (FUN_0035a9f0/FUN_00356b2c/FUN_0034c3f4/
 * FUN_00359be0/FUN_0036b270...) and dispatching through the object method table.
 * Ends with the epilogue FUN_0008e500. Complex global-list walk.
 * Confidence: low (global object list walk; many helpers).
 */
void cl4_swift_global_relocate(void *a, void *b, void *c)
{
    (void)a; (void)b; (void)c;
    /* FUN_0008e518 / FUN_00356900 / FUN_00350a64 / FUN_00310d68 /
     * FUN_00348d7c / (*DAT_00658c00) / FUN_00348bd8 / FUN_0034b308 /
     * FUN_0034b8bc / FUN_003494e8 / FUN_003493c4 / FUN_0034c2f8 /
     * FUN_0034ba78 / FUN_0034bc58 / FUN_00355948 */
    unsigned long g = 0;   /* *unaff_x20 */
    /* if _DAT_006c0160==0: g = _DAT_006ade68 (or re-init via FUN_0034add4/
     * FUN_0039a128); else walk _DAT_006c0168 via FUN_0031986c/FUN_00351318 */
    if (1) {   /* current == head */
        /* FUN_0035a9f0 / FUN_00356b2c / FUN_0034c3f4 / FUN_000839d8 /
         * FUN_00351cdc / FUN_000dbd0c registration path */
        sk_swift_state(0);
    } else {
        /* FUN_0036b270(g) / FUN_00362acc / FUN_00319808 / FUN_0036b118 /
         * FUN_00351f34 / FUN_00356b2c / FUN_0034c3f4 / FUN_000839d8
         * or FUN_0008dae4 fallback */
        sk_swift_state(0);
    }
    /* FUN_003548b8 / FUN_0008e500 epilogue */
}

/*--------------------------------------------------------------------*/
/* FUN_001b6568 @ 0x001b6568   (est. cl4_swift_global_teardown)
 * Ghidra: void FUN_001b6568(void)
 * Global-state teardown: if the live global (_DAT_006c0160) is set, releases it
 * (FUN_0031986c/FUN_0035013c); otherwise frees the singleton _DAT_006ade68
 * (FUN_0036b270) after a lazy-init check.
 * Confidence: low (global teardown; global constants).
 */
void cl4_swift_global_teardown(void)
{
    /* FUN_00355948 lazy init check; if _DAT_006c0160 != 0:
     * FUN_0031986c(_DAT_006c0168) / FUN_0035013c; else if _DAT_006c0150 != -1:
     * FUN_0034add4/FUN_0039a128; FUN_0036b270(_DAT_006ade68) */
    sk_swift_state(0);
}

/*--------------------------------------------------------------------*/
/* FUN_001b65ec @ 0x001b65ec   (est. cl4_swift_global_lookup)
 * Ghidra: bool FUN_001b65ec(undefined8, undefined8)
 * Looks up param_2 in the global list: uses _DAT_006c0160 (or 0x656860 default)
 * via FUN_00362c34, returning whether found.
 * Confidence: medium (clear global membership test).
 */
bool cl4_swift_global_lookup(void *a, void *key)
{
    (void)a;
    /* FUN_00355948; tag = _DAT_006c0160 ? : 0x656860; FUN_00362c34(tag, key) */
    long tag = 0x656860;
    long r = sk_swift_gfind(tag, (unsigned long)key);   /* FUN_00362c34 */
    return r != 0;
}

/*--------------------------------------------------------------------*/
/* FUN_001b6644 @ 0x001b6644   (est. cl4_swift_global_reset)
 * Ghidra: void FUN_001b6644(void)
 * Global-state reset: initializes the global (FUN_00353aa0/FUN_000a6f88), then
 * either clears the object's four fields (x19[0..3]=0) or stores a new pointer
 * (x19[3]=lVar1) and dispatches through the method table.
 * Confidence: low (global reset; object field zeroing).
 */
void cl4_swift_global_reset(void)
{
    /* FUN_00353aa0 / FUN_000a6f88 / (*DAT_00658c00) / FUN_0034a1f8 /
     * FUN_00351990 / FUN_00353cd8 / FUN_0034b2a8 */
    long p = 0;   /* *(unaff_x20+0x10) */
    if (1) {   /* in_ZR */
        /* clear x19[0..3] = 0 */
        sk_swift_state(0);
    } else {
        /* x19[3] = p; FUN_00319a4c; (**(*(p-8)+0x20))() */
        sk_swift_state(0);
    }
}

/*--------------------------------------------------------------------*/
/* FUN_001b6734 @ 0x001b6734   (est. cl4_swift_global_init2)
 * Ghidra: void FUN_001b6734(void)
 * Global-state init: allocates via FUN_00083450, initializes +0x10/+0x20 via
 * FUN_00389da0, frees the old singleton (FUN_0036b118), and stores the pair into
 * _DAT_006c0168/_DAT_006c0160.
 * Confidence: low (global init; global stores).
 */
void cl4_swift_global_init2(void)
{
    long g = sk_swift_galloc(0xd000000000000017, 0x80000000005d3de0);  /* FUN_00083450 */
    sk_swift_ginit(g + 0x20, *(unsigned long *)(g + 0x10));            /* FUN_00389da0 */
    sk_swift_state(0);   /* FUN_0035310c */
    sk_swift_free(0);    /* FUN_0036b118 */
    /* _DAT_006c0168 = hi; _DAT_006c0160 = lo (or 0 via FUN_0008dae4) */
    sk_swift_state(0);
}

/*--------------------------------------------------------------------*/
/* FUN_001b67bc @ 0x001b67bc   (est. cl4_swift_global_init3)
 * Ghidra: void FUN_001b67bc(void)
 * Global-state init: allocates via FUN_00083450, initializes via FUN_00389da0,
 * then FUN_00351d18 + free FUN_0036b118.
 * Confidence: low (global init).
 */
void cl4_swift_global_init3(void)
{
    long g = sk_swift_galloc(0, 0);   /* FUN_00083450 */
    sk_swift_ginit(g + 0x20, *(unsigned long *)(g + 0x10));  /* FUN_00389da0 */
    sk_swift_state(0);   /* FUN_00351d18 */
    sk_swift_free(0);    /* FUN_0036b118 */
}

/*--------------------------------------------------------------------*/
/* FUN_001b67f8 @ 0x001b67f8   (est. cl4_swift_global_set)
 * Ghidra: long FUN_001b67f8(undefined8)
 * Global-state setter: initializes the singleton (FUN_00355538/FUN_0036a940) if
 * _DAT_006c0160 is empty, then stores param_1 into the global via FUN_00319808 and
 * returns a helper result.
 * Confidence: low (global setter; global constants).
 */
long cl4_swift_global_set(void *v)
{
    /* FUN_00355948; if _DAT_006c0160==0:
     *   FUN_00355538(0x656860); g=FUN_0036a940(); FUN_00319808(v, g+0x10)
     * else:
     *   FUN_00319808(v, stack); uVar1=FUN_0031989c(_DAT_006c0168);
     *   FUN_003510c4(uVar1, stack) */
    sk_swift_gstore(v);   /* FUN_00319808 */
    return 0;
}

/*--------------------------------------------------------------------*/
/* FUN_001b68a0 @ 0x001b68a0   (est. cl4_swift_global_find)
 * Ghidra: long FUN_001b68a0(void)
 * Global lookup: initializes the global (FUN_00319a4c), and walks the global list
 * via FUN_003629c4/FUN_00365b6c/FUN_003625e4/FUN_00362a58/FUN_001b67f8. On a
 * special list node it validates the type (*(x16+0x40)==8) and frees via
 * FUN_0036b270. Recursive for child entries.
 * Confidence: low (global list traversal).
 */
long cl4_swift_global_find(void)
{
    /* FUN_00351a38 / FUN_00319a4c / FUN_00349734 / (x8+0x10) / FUN_003507e0 /
     * FUN_003629c4 */
    long n = sk_swift_glist(0);   /* FUN_003629c4() */
    if (n == 0) {
        /* FUN_00319808 / FUN_00002534(0x656108,&DAT_004e7ef0) /
         * FUN_00365b6c(&local_c0, ...) */
        if (1) {   /* flag */
            /* FUN_00344e54 / FUN_003625e4 / FUN_003198cc / FUN_00362a58 /
             * FUN_001b67f8 */
            return sk_swift_gstate(0);
        }
        /* else FUN_00077070 / FUN_000e4674 / FUN_00353b1c / FUN_003507e0;
         * recurse FUN_001b68a0 / FUN_001b6568 */
        return sk_swift_gstate(0);
    } else {
        if (*(long *)(0 + 0x40) != 8) sk_fatal_error(0, 0);
        sk_swift_free_pages(0);   /* FUN_0036b270(*unaff_x19) */
        return 0;
    }
}

/*--------------------------------------------------------------------*/
/* FUN_001b6ae0 @ 0x001b6ae0   (est. cl4_swift_abort)
 * Ghidra: void FUN_001b6ae0(void)
 * Noreturn abort: FUN_00347e74 then panic.
 * Confidence: medium (noreturn abort pair).
 */
void cl4_swift_abort(void)
{
    sk_swift_badlock(0);   /* FUN_00347e74 */
    sk_fatal_error(0, 0);
}

/*--------------------------------------------------------------------*/
/* FUN_001b6b14 @ 0x001b6b14   (est. cl4_cap_word_get)
 * Ghidra: undefined8 FUN_001b6b14(void)
 * Reads *x20 as a capability word; if non-negative and bit62 clear, resolves via
 * FUN_003a26a0; else returns 0.
 * Confidence: medium (clear cap-word decode).
 */
unsigned long cl4_cap_word_get(void)
{
    unsigned long w = 0;   /* *unaff_x20 */
    if ((long)w >= 0 && ((w >> 0x3e & 1) == 0)) return sk_swift_cap(w);  /* FUN_003a26a0 */
    return 0;
}

/*--------------------------------------------------------------------*/
/* FUN_001b6b18 @ 0x001b6b18   (est. cl4_cap_word_get2)
 * Ghidra: undefined8 FUN_001b6b18(void)
 * Duplicate of FUN_001b6b14 (cap word get).
 * Confidence: medium (duplicate).
 */
unsigned long cl4_cap_word_get2(void)
{
    return cl4_cap_word_get();
}

/*--------------------------------------------------------------------*/
/* FUN_001b6b88 @ 0x001b6b88   (est. cl4_cap_word_release)
 * Ghidra: void FUN_001b6b88(undefined8*)
 * Releases the cap word *param_1 via FUN_003a261c.
 * Confidence: medium (thin cap release).
 */
void cl4_cap_word_release(unsigned long *w)
{
    sk_swift_cap_rel(*w);   /* FUN_003a261c */
}

/*--------------------------------------------------------------------*/
/* FUN_001b6b8c @ 0x001b6b8c   (est. cl4_cap_word_release2)
 * Ghidra: void FUN_001b6b8c(undefined8*)
 * Duplicate of FUN_001b6b88 (cap release).
 * Confidence: medium (duplicate).
 */
void cl4_cap_word_release2(unsigned long *w)
{
    cl4_cap_word_release(w);
}

/*--------------------------------------------------------------------*/
/* FUN_001b6ba4 @ 0x001b6ba4   (est. cl4_alloc_align)
 * Ghidra: ulong FUN_001b6ba4(ulong)
 * Aligns param_1 up to 8 bytes (and keeps the high/negative form as-is), then
 * thunk_FUN_0036b270 (alloc) and returns the aligned size.
 * Confidence: medium (clear alignment helper).
 */
unsigned long cl4_alloc_align(unsigned long size)
{
    unsigned long a = size & 0xffffffffffffff8;
    if (0x7fffffffffffffff < size) a = size;
    sk_swift_free_pages(0);   /* thunk_FUN_0036b270 */
    return a;
}

/*--------------------------------------------------------------------*/
/* FUN_001b6bd4 @ 0x001b6bd4   (est. cl4_swift_gate_dispatch)
 * Ghidra: void thunk_FUN_00213834(void)
 * Thunk into FUN_00213834: FUN_0007c0c4, FUN_0034ece8, then an indirect call
 * through (x16+8) at x20+x9.
 * Confidence: low (thunk into 0x213834; indirect gate dispatch).
 */
void cl4_swift_gate_dispatch(void)
{
    /* FUN_0007c0c4 / FUN_0034ece8(uVar1, x8+0x38) /
     * (**(code**)(x16+8))(x20 + x9) */
    sk_swift_state(0);
}

/*--------------------------------------------------------------------*/
/* FUN_001b6bd8 @ 0x001b6bd8   (est. cl4_swift_buffer_extend)
 * Ghidra: void FUN_001b6bd8(void)
 * Swift buffer growth: FUN_0034cf24/FUN_0034fc8c/FUN_00251df8, computes
 * x22 * *(x16+0x48) with signed overflow checks (SWBP 0x1b6c48), then on no
 * overflow grows the buffer via FUN_000b43d0/FUN_00251e7c/FUN_003504ac. Overflow
 * traps (SWBP 0x1b6c4c).
 * Confidence: low (Swift buffer growth with overflow traps).
 */
void cl4_swift_buffer_extend(void)
{
    /* FUN_0034cf24 / FUN_0034fc8c / FUN_00251df8 / FUN_0034b518 */
    long base = 0;   /* FUN_0034b518() */
    /* prod = x22 * *(x16+0x48); signed-multiply overflow check */
    long prod = 0;
    (void)prod;
    /* if (high-half overflow) SWBP 0x1b6c48 */
    if (!__builtin_add_overflow(base, 0, &base)) {
        /* FUN_000b43d0 / FUN_00251e7c / FUN_003504ac / thunk_FUN_0036a940 */
        sk_swift_state(0);
        return;
    }
    __builtin_trap();   /* SWBP 0x1b6c4c */
}

/*--------------------------------------------------------------------*/
/* FUN_001b6c4c @ 0x001b6c4c   (est. cl4_swift_closure_invoke)
 * Ghidra: void FUN_001b6c4c(void)
 * Swift closure invocation: reads closure context (in_x5-8), sets up a stack frame
 * (FUN_00252024 with FUN_0034443c), and if x21 non-null calls through (lVar3+0x20).
 * Confidence: low (Swift closure thunk).
 */
void cl4_swift_closure_invoke(void)
{
    /* lVar3 = *(in_x5-8); FUN_00252024(FUN_0034443c, stack);
     * if (unaff_x21 != 0) (**(lVar3+0x20))(in_stack, stack+delta, in_x5) */
    sk_swift_state(0);
}

/*--------------------------------------------------------------------*/
/* FUN_001b6e28 @ 0x001b6e28   (est. cl4_swift_abort2)
 * Ghidra: void FUN_001b6e28(void)
 * Noreturn abort: FUN_00347e74 then panic (duplicate of 001b6ae0).
 * Confidence: medium (noreturn abort pair).
 */
void cl4_swift_abort2(void)
{
    cl4_swift_abort();
}

/*--------------------------------------------------------------------*/
/* FUN_001b6e8c @ 0x001b6e8c   (est. cl4_swift_flag_check3)
 * Ghidra: uint FUN_001b6e8c(void)
 * Runs FUN_00349fcc/FUN_00350adc/FUN_0008412c then returns (indirect result)&1.
 * Confidence: low (flag bit test).
 */
unsigned int cl4_swift_flag_check3(void)
{
    unsigned int v = sk_swift_flag(0);   /* (*extraout_x8)() */
    return v & 1;
}

/*--------------------------------------------------------------------*/
/* FUN_001b6ecc @ 0x001b6ecc   (est. cl4_swift_state_chain)
 * Ghidra: void FUN_001b6ecc(void)
 * Runs a chain of Swift state helpers (FUN_00077888/FUN_00356ba4/FUN_00349720/
 * (*DAT_00658c00)/FUN_00349178/FUN_00353ba0/FUN_0034aebc/FUN_00365b6c).
 * Confidence: low (state helper chain).
 */
void cl4_swift_state_chain(void)
{
    /* FUN_00077888 / FUN_00356ba4 / FUN_00349720 / (*DAT_00658c00) /
     * FUN_00349178 / FUN_00353ba0 / FUN_0034aebc / FUN_00365b6c */
    sk_swift_state(0);
}

/*--------------------------------------------------------------------*/
/* FUN_001b6f54 @ 0x001b6f54   (est. cl4_swift_global_verify)
 * Ghidra: void FUN_001b6f54(undefined8, undefined8, undefined8)
 * Verifies a global entry via FUN_00362c00; on success frees it (FUN_0036b270);
 * on failure panics after FUN_0034865c/FUN_00349844/FUN_00350a94.
 * Confidence: low (global verify-or-panic).
 */
void cl4_swift_global_verify(void *a, void *b, void *c)
{
    long r = sk_swift_gverify((unsigned long)a, (unsigned long)c);   /* FUN_00362c00 */
    if (r != 0) { sk_swift_free_pages((unsigned long)a); return; }   /* FUN_0036b270 */
    sk_swift_state(0);   /* FUN_0034865c / FUN_00349844 / FUN_00350a94 */
    sk_fatal_error(0, 0);
}

/*--------------------------------------------------------------------*/
/* FUN_001b6fd4 @ 0x001b6fd4   (est. cl4_swift_idx_ret)
 * Ghidra: long FUN_001b6fd4(void)
 * Returns a helper index if non-negative; else panics (FUN_00347fb4/FUN_003523f0).
 * Confidence: medium (index validate-or-panic).
 */
long cl4_swift_idx_ret(void)
{
    long r = sk_swift_idx(0);   /* FUN_003a2898 */
    if (r >= 0) return r;
    sk_swift_badlock(0);   /* FUN_00347fb4 */
    sk_swift_fail2();      /* FUN_003523f0 */
    sk_fatal_error(0, 0);
}

/*--------------------------------------------------------------------*/
/* FUN_001b7014 @ 0x001b7014   (est. cl4_object_service_compare)
 * Ghidra: void FUN_001b7014(void)
 * Object-service comparison path: current CPU (FUN_0008e518), locks, and drives a
 * long dispatch chain comparing two operands (uVar2/uVar3) with many indirect
 * (*unaff_x22) and (*DAT_00658c00) callbacks before the epilogue FUN_0008e500.
 * Confidence: low (object-service compare; very heavy extraout chain).
 */
void cl4_object_service_compare(void)
{
    /* FUN_0008e518 / FUN_0034e8a4 / FUN_00357748 / FUN_00349684 /
     * FUN_003513fc / FUN_00377824 / FUN_0034ab20 / FUN_0007c1a4 /
     * (*DAT_00658c00) / FUN_0034aab0 / FUN_0034a774 / FUN_003523fc /
     * FUN_00377824 ... */
    unsigned long flag = 0;
    (void)flag;
    if (1) {   /* compare result path */
        /* FUN_00310a44 / FUN_0034ae6c / FUN_00354864 / FUN_00310a44 /
         * FUN_0034bfa4 / ... */
        sk_swift_state(0);
    } else {
        /* FUN_0034b4a0 / (*unaff_x22)() / FUN_0034c0d0 / FUN_0034c9a8 /
         * FUN_0034c368 / FUN_0034f504 ... */
        sk_swift_state(0);
    }
    /* FUN_003581a4 / FUN_0008e500 epilogue */
}

/*--------------------------------------------------------------------*/
/* FUN_001b7488 @ 0x001b7488   (est. cl4_swift_word_build)
 * Ghidra: ulong FUN_001b7488(ulong)
 * Builds a tagged word: (param_1>>1 ^ ~0) & 0x4000000000000000 | alloc-result.
 * Confidence: medium (clear bit-field word build).
 */
unsigned long cl4_swift_word_build(unsigned long v)
{
    unsigned long a = sk_swift_gstate(0);   /* FUN_0036b270() */
    return ((v >> 1 ^ 0xffffffffffffffff) & 0x4000000000000000) | a;
}

/*--------------------------------------------------------------------*/
/* FUN_001b74cc @ 0x001b74cc   (est. cl4_swift_word_build2)
 * Ghidra: ulong FUN_001b74cc(undefined8, ulong)
 * Builds a tagged word: param_2 | alloc-result.
 * Confidence: medium (clear bit-field word build).
 */
unsigned long cl4_swift_word_build2(void *a, unsigned long v)
{
    (void)a;
    unsigned long r = sk_swift_gstate(0);   /* FUN_0036b270() */
    return v | r;
}

/*--------------------------------------------------------------------*/
/* FUN_001b74f8 @ 0x001b74f8   (est. cl4_swift_reg_ensure)
 * Ghidra: void FUN_001b74f8(undefined8)
 * Registers/ensures a global entry: FUN_003198cc(param_1, param_1); if non-null,
 * FUN_003628f0.
 * Confidence: low (registration ensure).
 */
void cl4_swift_reg_ensure(void *v)
{
    long r = sk_swift_reg((unsigned long)v, (unsigned long)v);   /* FUN_003198cc */
    if (r != 0) { sk_swift_state(0); }   /* FUN_003628f0 */
}

/*--------------------------------------------------------------------*/
/* FUN_001b74fc @ 0x001b74fc   (est. cl4_swift_reg_ensure2)
 * Ghidra: void FUN_001b74fc(undefined8)
 * Duplicate of FUN_001b74f8.
 * Confidence: low (duplicate).
 */
void cl4_swift_reg_ensure2(void *v)
{
    cl4_swift_reg_ensure(v);
}

/*--------------------------------------------------------------------*/
/* FUN_001b7524 @ 0x001b7524   (est. cl4_swift_callback_invoke)
 * Ghidra: void FUN_001b7524(undefined8, code*, undefined8, long, long, undefined8, ...)
 * Swift callback invocation: reads context (param_5-8), sets up a stack frame, and
 * dispatches a completion callback (FUN_000839f8) or the per-object method
 * (*(lVar3+0x20)/+8). Complex closure/callback thunk.
 * Confidence: low (Swift callback/closure invocation).
 */
void cl4_swift_callback_invoke(void *a, void (*cb)(void *, void *, void *), void *c,
                               long ctx, long obj, void *p6, void *p7, void *p8)
{
    (void)a; (void)cb; (void)c; (void)p6; (void)p7; (void)p8;
    /* lVar2 = *(obj-8); FUN_000839f8(stack, 1, ctx)
     * if done==1: FUN_000839d8(a,1,1,p6)
     * else: (**(lVar3+0x20))(stack...); (*cb)(a, stack, buf);
     *       (**(lVar3+8))(stack, ctx); if (x21) (**(lVar2+0x20))(p8, buf, obj) */
    sk_swift_state(0);
}

/*--------------------------------------------------------------------*/
/* FUN_001b779c @ 0x001b779c   (est. cl4_swift_global_step)
 * Ghidra: void FUN_001b779c(void)
 * Thunk to FUN_003629b4.
 * Confidence: medium (trivial thunk).
 */
void cl4_swift_global_step(void)
{
    sk_swift_gstep(0);   /* FUN_003629b4 */
}

/*--------------------------------------------------------------------*/
/* FUN_001b77a0 @ 0x001b77a0   (est. cl4_swift_global_step2)
 * Ghidra: void FUN_001b77a0(void)
 * Duplicate thunk to FUN_003629b4.
 * Confidence: medium (trivial thunk).
 */
void cl4_swift_global_step2(void)
{
    cl4_swift_global_step();
}

/*--------------------------------------------------------------------*/
/* FUN_001b77b4 @ 0x001b77b4   (est. cl4_swift_global_recurse)
 * Ghidra: void FUN_001b77b4(void)
 * FUN_003532e4 then FUN_001b68a0 (global find).
 * Confidence: medium (two-call global recurse).
 */
void cl4_swift_global_recurse(void)
{
    sk_swift_state(0);   /* FUN_003532e4 */
    cl4_swift_global_find();
}

/*--------------------------------------------------------------------*/
/* FUN_001b77dc @ 0x001b77dc   (est. cl4_swift_panic_gate)
 * Ghidra: void FUN_001b77dc(long, undefined8, uint)
 * Panic gate: non-copy path (flag bit0 clear) requires param_1!=0 else panic after
 * FUN_00348898(1)/FUN_0034c978; copy path (bit0 set) panics after
 * FUN_003488bc(1)/FUN_0034d6e8; both end with FUN_00351be0 + fatal.
 * Confidence: low (Swift precondition/panic gate).
 */
void cl4_swift_panic_gate(long ok, void *a, unsigned int flag)
{
    (void)a;
    if ((flag & 1) == 0) {
        if (ok != 0) return;
        sk_swift_die(1);   /* FUN_00348898(1) */
        sk_swift_state(0); /* FUN_0034c978 */
    } else {
        sk_swift_die(1);   /* FUN_003488bc(1) */
        sk_swift_state(0); /* FUN_0034d6e8 */
    }
    sk_swift_fail2();   /* FUN_00351be0 */
    sk_fatal_error(0, 0);
}

/*--------------------------------------------------------------------*/
/* FUN_001b788c @ 0x001b788c   (est. cl4_swift_hash_begin)
 * Ghidra: void FUN_001b788c(void)
 * Thunk to FUN_00255738 (hash/collection begin).
 * Confidence: medium (trivial thunk).
 */
void cl4_swift_hash_begin(void)
{
    sk_swift_hash(0);   /* FUN_00255738 */
}

/*--------------------------------------------------------------------*/
/* FUN_001b78b8 @ 0x001b78b8   (est. cl4_swift_small_string_make)
 * Ghidra: ulong thunk_FUN_001a89a8(undefined8, ulong, uint)
 * Thunk into FUN_001a89a8: builds a small-string word from a byte buffer. For
 * len<0x10 packs up to 8 bytes into a word (with a nonzero-codepoint flag bit
 * 0xe0..0xa0); larger lengths use the pointer form (|0xc000000000000000|0x1000...).
 * Negative length panics.
 * Confidence: low (Swift small-string construction; thunk into 0x1a89a8).
 */
unsigned long cl4_swift_small_string_make(void *buf, unsigned long len, unsigned int flag)
{
    if ((long)len < 0) { sk_swift_badptr(); sk_fatal_error(0, 0); }
    if (len == 0) return sk_swift_empty_string(0);   /* FUN_0011e71c */
    if (len < 0x10) {
        /* FUN_00358768; pack bytes into word with continuation checks */
        unsigned long w = 0;
        const unsigned char *p = buf;
        unsigned long bits = 0;
        do {
            w |= (unsigned long)*p << (bits & 0x3f);
            bits += 8; p++;
        } while (len * 8 - bits != 0);
        unsigned long tag = 0xe000000000000000;
        /* if any byte has high bit (0x80): tag = 0xa000000000000000 */
        sk_swift_state(0);
        return tag | w;
    }
    unsigned long w = len | 0xc000000000000000;
    if ((flag & 1) == 0) w = len;
    return w | 0x1000000000000000;
}

/*--------------------------------------------------------------------*/
/* FUN_001b78bc @ 0x001b78bc   (est. cl4_swift_uint_conv3)
 * Ghidra: void FUN_001b78bc(void)
 * Swift unsigned conversion wrapper.
 * Confidence: low (Swift conversion helper).
 */
void cl4_swift_uint_conv3(void)
{
    sk_swift_state(0);
}

/*--------------------------------------------------------------------*/
/* FUN_001b798c @ 0x001b798c   (est. cl4_swift_utf8_bounds)
 * Ghidra: void FUN_001b798c(void)
 * Runs FUN_00350a28/FUN_0029eb58/FUN_00350624/FUN_0029ec2c (UTF-8 bounds helpers).
 * Confidence: low (UTF-8 bounds helper chain).
 */
void cl4_swift_utf8_bounds(void)
{
    /* FUN_00350a28 / FUN_0029eb58 / FUN_00350624 / FUN_0029ec2c */
    sk_swift_state(0);
}

/*--------------------------------------------------------------------*/
/* FUN_001b79c4 @ 0x001b79c4   (est. cl4_swift_small_string_pack)
 * Ghidra: void FUN_001b79c4(ulong*, byte*, ulong, ulong)
 * Packs a byte buffer into a Swift small-string {word, tag} pair: for len<0x16
 * packs 8+ bytes into two words with continuation-bit detection (0x80); for len>=0x16
 * uses the pointer form (|0xc000000000000000|0x8000...). Negative length panics.
 * Confidence: low (Swift small-string packing).
 */
void cl4_swift_small_string_pack(unsigned long *out, const unsigned char *buf,
                                 unsigned long len, unsigned long flag)
{
    if ((long)len < 0)
        sk_fatal_error((unsigned long)"Fatal error", 0xb, 2,
                       (unsigned long)"UnsafeBufferPointer with negative index", 0x27, 2,
                       (unsigned long)"Swift/UnsafeBufferPointer.swift", 0x1f, 2, 0x582, 1);
    unsigned long lo, hi;
    if (len == 0) { lo = 0; hi = 0xe000000000000000; }
    else if (len < 0x10) {
        unsigned long w1 = 0, w2 = 0, n1 = (len > 8) ? 8 : len, n2 = len - 8;
        for (unsigned long i = 0; i < n1; i++) w1 |= (unsigned long)buf[i] << (i * 8);
        if (len >= 9) {
            if (n2 <= len - 9) goto ob;
            for (unsigned long i = 0; i < n2; i++) w2 |= (unsigned long)buf[8 + i] << (i * 8);
        }
        unsigned long tag = 0xe000000000000000;
        if ((w1 | w2) & 0x8080808080808080) tag = 0xa000000000000000;
        hi = tag | len << 0x38 | w2;
        lo = w1;
    } else {
        lo = len | 0xc000000000000000;
        if ((flag & 1) == 0) lo = len;
        lo |= 0x1000000000000000;
        hi = (unsigned long)(buf + 0x7fffffffffffffe0) | 0x8000000000000000;
    }
    out[0] = lo;
    out[1] = hi;
    return;
ob:
    sk_fatal_error((unsigned long)"Fatal error", 0xb, 2,
                   (unsigned long)"Index out of range", 0x12, 2,
                   (unsigned long)"Swift/Range.swift", 0x11, 2, 0x136, 1);
}

/*--------------------------------------------------------------------*/
/* FUN_001b7b50 @ 0x001b7b50   (est. cl4_swift_hash_store)
 * Ghidra: void FUN_001b7b50(undefined1 (*)[16])
 * Stores the FUN_00255738 result into *param_1.
 * Confidence: medium (thin store wrapper).
 */
void cl4_swift_hash_store(void *out)
{
    cl4_result_t r = sk_swift_hash_pair(0);   /* FUN_00255738 */
    ((unsigned long *)out)[0] = r.lo;
    ((unsigned long *)out)[1] = r.hi;
}

/*--------------------------------------------------------------------*/
/* FUN_001b7b94 @ 0x001b7b94   (est. cl4_swift_hash_free)
 * Ghidra: void FUN_001b7b94(void)
 * Frees a hash/collection resource: FUN_003503c0, thunk_FUN_0036b270, FUN_0007c1c4.
 * Confidence: low (hash resource free).
 */
void cl4_swift_hash_free(void)
{
    sk_swift_state(0);       /* FUN_003503c0 */
    sk_swift_free_pages(0);  /* thunk_FUN_0036b270 */
    sk_swift_state2(0);      /* FUN_0007c1c4 */
}

/*--------------------------------------------------------------------*/
/* FUN_001b7bc4 @ 0x001b7bc4   (est. cl4_swift_char_form)
 * Ghidra: void FUN_001b7bc4(undefined1 (*)[16], ulong, ulong)
 * Swift Character form: validates the string (param_2/param_3) is a single
 * extended-grapheme-cluster (via FUN_001b798c bounds check), and either casts it
 * (FUN_0001d4a0) or panics ("Can't form a Character from an empty String" /
 * "Can't form a Character from a String containing more than one extended
 * grapheme cluster").
 * Confidence: low (Swift Character construction).
 */
void cl4_swift_char_form(void *out, unsigned long word, unsigned long flags)
{
    unsigned long n = flags >> 0x38 & 0xf;
    if ((flags & 0x2000000000000000) == 0) n = word & 0xffffffffffff;
    if (n == 0)
        sk_fatal_error((unsigned long)"Fatal error", 0xb, 2,
                       (unsigned long)"Can't form a Character from an empty String", 0x2b, 2,
                       (unsigned long)"Swift/Character.swift", 0x15, 2, 0xaf, 1);
    unsigned long w = cl4_swift_utf8_bounds2(0xf, word, flags);  /* FUN_001b798c */
    if (w >> 0xe == n * 4) {
        if ((flags & 0x2000000000000000) == 0 && (word & 0x1000000000000000) == 0) {
            /* FUN_0001d4a0 cast */
            sk_swift_cast16(word, flags);
            sk_swift_meta(flags);
        }
        ((unsigned long *)out)[0] = word;
        ((unsigned long *)out)[1] = flags;
        return;
    }
    sk_fatal_error((unsigned long)"Fatal error", 0xb, 2,
                   (unsigned long)"Can't form a Character from a String containing more than one "
                   "extended grapheme cluster", 0x57, 2,
                   (unsigned long)"Swift/Character.swift", 0x15, 2, 0xb1, 1);
}

/*--------------------------------------------------------------------*/
/* FUN_001b7cec @ 0x001b7cec   (est. cl4_swift_string_escape)
 * Ghidra: void FUN_001b7cec(void)
 * Swift String debugDescription/escape builder: iterates the string's UTF-8 view,
 * decoding multibyte scalars (1/2/3/4-byte UTF-8 via FUN_00352af0 switch), and
 * appends escaped characters (quote, apostrophe, backslash, CR, tab, LF, NUL,
 * DEL and hex escapes via FUN_00254c18/FUN_001e3f70) into an output buffer,
 * calling FUN_00355fa0/FUN_00355a58 for each escaped literal. This is the Swift
 * string escaping used by debugDescription. Large, helper-heavy.
 * Confidence: low (Swift String debugDescription escape loop).
 */
void cl4_swift_string_escape(void)
{
    /* FUN_00356f9c / FUN_00359030 / FUN_00350744(&DAT_005ce67c) /
     * FUN_001a89a8() make small string */
    /* iterate UTF-8 bytes; for each scalar decode continuation via
     * FUN_00352af0/FUN_00353ff4/FUN_00352e9c/FUN_0034c6d4/FUN_0035a0c4 */
    unsigned long ch = 0;   /* decoded scalar */
    /* 0x22 " -> FUN_00355fa0(&DAT_005ce75d)
     * 0x27 ' -> FUN_00355fa0(&DAT_005ce760)
     * 0x5c \ -> FUN_00355fa0(&DAT_005ce763)
     * 0x5f (underscore after 0x20) -> escape path
     * 0xd -> &DAT_005ce754; 0x9 -> &DAT_005ce751; 0xa -> &DAT_005ce757;
     * 0x0 -> &DAT_005ce75a; 0x7f -> escape; >0x7f -> hex escape via
     * FUN_00254c18/FUN_001e3f70; else FUN_003538b0(&DAT_005ce74b) */
    for (;;) {
        /* FUN_00355fa0(puVar9); FUN_00355a58() for escaped chars */
        /* FUN_00349cbc / FUN_00352a34 / FUN_0034c51c string append */
        /* continuation: FUN_003497ec / FUN_001a89a8 / FUN_00354c70 /
         * FUN_00359244 / FUN_00356164 / thunk_FUN_002a2698 / FUN_00351f28 */
        /* end: FUN_00100c38 / FUN_002ae098 / FUN_003578cc */
        break;
    }
}

/*--------------------------------------------------------------------*/
/* FUN_001b8690 @ 0x001b8690   (est. cl4_swift_hash_eq1)
 * Ghidra: uint FUN_001b8690(void)
 * Runs FUN_00352764 then FUN_001b8920, returns result&1.
 * Confidence: low (Swift hash-table equality wrapper).
 */
unsigned int cl4_swift_hash_eq1(void)
{
    sk_swift_state(0);   /* FUN_00352764 */
    return cl4_swift_string_cmp3(0, 0, 0, 0) & 1;   /* FUN_001b8920 */
}

/*--------------------------------------------------------------------*/
/* FUN_001b8694 @ 0x001b8694   (est. cl4_swift_hash_eq2)
 * Ghidra: uint FUN_001b8694(void)
 * Duplicate of FUN_001b8690.
 * Confidence: low (duplicate).
 */
unsigned int cl4_swift_hash_eq2(void)
{
    return cl4_swift_hash_eq1();
}

/*--------------------------------------------------------------------*/
/* FUN_001b86d8 @ 0x001b86d8   (est. cl4_swift_index_cmp_ex)
 * Ghidra: uint FUN_001b86d8(undefined8*, undefined8, undefined8*, undefined8)
 * Existential collection index comparison: resolves the per-type compare hooks
 * (FUN_0031bb80 / FUN_0031bbe0) and compares two indices; mismatched base types
 * panic ("Base index types differ"). Returns inverted (not-equal) flag.
 * Confidence: low (Swift existential index compare).
 */
unsigned int cl4_swift_index_cmp_ex(void **a, void *ta, void **b, void *tb)
{
    /* lVar3 = (*FUN_0031bb80(tb))(*b, tb); lVar4 = (*FUN_0031bb80(ta))(*a, ta) */
    long l3 = 0, l4 = 0;
    if (l3 == l4) {
        /* uVar1 = (*FUN_0031bbe0(tb))(a, ta, *b, tb) */
        return 0 ^ 1 & 1;
    }
    sk_fatal_error((unsigned long)"Fatal error", 0xb, 2,
                   (unsigned long)"Base index types differ", 0x17, 2,
                   (unsigned long)"Swift/ExistentialCollection.swift", 0x21, 2, 0x742, 1);
}

/*--------------------------------------------------------------------*/
/* FUN_001b8848 @ 0x001b8848   (est. cl4_swift_hash_indices_panic)
 * Ghidra: void FUN_001b8848(void)
 * Noreturn panic: "Can't compare indices belonging to different hash tables".
 * Confidence: high (clear noreturn panic; string-matched).
 */
void cl4_swift_hash_indices_panic(void)
{
    sk_fatal_error((unsigned long)"Fatal error", 0xb, 2,
                   (unsigned long)"Can't compare indices belonging to different hash tables",
                   0x38, 2, (unsigned long)"Swift/HashTable.swift", 0x15, 2, 0xe4, 1);
}

/*--------------------------------------------------------------------*/
/* FUN_001b88d0 @ 0x001b88d0   (est. cl4_swift_idx_ne)
 * Ghidra: uint FUN_001b88d0(void)
 * Returns (FUN_002a0f24(x6,x7) ^ 1) & 1 — index not-equal.
 * Confidence: high (clear compare wrapper).
 */
unsigned int cl4_swift_idx_ne(void)
{
    return (sk_swift_idx_cmp(0, 0) ^ 1) & 1;   /* FUN_002a0f24 */
}

/*--------------------------------------------------------------------*/
/* FUN_001b8920 @ 0x001b8920   (est. cl4_swift_string_cmp3)
 * Ghidra: void FUN_001b8920(long, ulong, long, ulong)
 * Swift String compare: returns 0 when both words equal; for small strings compares
 * the word pointer/type via FUN_0035aca4; otherwise falls to FUN_002a0d50 string
 * compare. Result passed to FUN_00356d20.
 * Confidence: low (Swift string compare).
 */
void cl4_swift_string_cmp3(long w1, unsigned long f1, long w2, unsigned long f2)
{
    unsigned long r;
    if (w1 == w2 && f1 == f2) r = 0;
    else if ((((f1 ^ 0xffffffffffffffff) & 0x6000000000000000) == 0) &&
             ((f2 & 0x6000000000000000) == 0x6000000000000000)) {
        /* FUN_0035aca4 small-string compare */
        r = 0;
        if (w2 != 0) r = 1;
    } else {
        r = sk_swift_string_cmp2(0, 0, 0, 0, 1);   /* FUN_002a0d50 */
    }
    sk_swift_state(r);   /* FUN_00356d20(r, x30) */
}

/*--------------------------------------------------------------------*/
/* FUN_001b89a4 @ 0x001b89a4   (est. cl4_swift_cmp_finish)
 * Ghidra: void FUN_001b89a4(void)
 * Runs FUN_00349fcc/FUN_0035044c/FUN_0034aebc, an indirect compare, then
 * FUN_00356d20.
 * Confidence: low (Swift compare finish).
 */
void cl4_swift_cmp_finish(void)
{
    /* FUN_00349fcc / FUN_0035044c(in_x3) / FUN_0034aebc / (*extraout_x8)() /
     * FUN_00356d20 */
    sk_swift_state(0);
}

/*--------------------------------------------------------------------*/
/* FUN_001b89e4 @ 0x001b89e4   (est. cl4_swift_cmp_wrap1)
 * Ghidra: uint FUN_001b89e4(void)
 * Runs FUN_00352764 then FUN_001b8c84, returns result&1.
 * Confidence: low (Swift compare wrapper).
 */
unsigned int cl4_swift_cmp_wrap1(void)
{
    sk_swift_state(0);   /* FUN_00352764 */
    return cl4_swift_string_cmp4(0, 0, 0, 0) & 1;   /* FUN_001b8c84 */
}

/*--------------------------------------------------------------------*/
/* FUN_001b89e8 @ 0x001b89e8   (est. cl4_swift_cmp_wrap2)
 * Ghidra: uint FUN_001b89e8(void)
 * Duplicate of FUN_001b89e4.
 * Confidence: low (duplicate).
 */
unsigned int cl4_swift_cmp_wrap2(void)
{
    return cl4_swift_cmp_wrap1();
}

/*--------------------------------------------------------------------*/
/* FUN_001b8a2c @ 0x001b8a2c   (est. cl4_swift_index_ne_ex)
 * Ghidra: uint FUN_001b8a2c(undefined8*, undefined8, undefined8*, undefined8)
 * Existential collection index not-equal: resolves compare hooks (FUN_0031bb80/
 * FUN_0031bbe0); mismatched base types panic. Returns inverted flag.
 * Confidence: low (Swift existential index compare).
 */
unsigned int cl4_swift_index_ne_ex(void **a, void *ta, void **b, void *tb)
{
    (void)a; (void)ta; (void)b; (void)tb;
    long l3 = 0, l4 = 0;
    if (l3 == l4) return 0 ^ 1 & 1;
    sk_fatal_error((unsigned long)"Fatal error", 0xb, 2,
                   (unsigned long)"Base index types differ", 0x17, 2,
                   (unsigned long)"Swift/ExistentialCollection.swift", 0x21, 2, 0x742, 1);
}

/*--------------------------------------------------------------------*/
/* FUN_001b8bac @ 0x001b8bac   (est. cl4_swift_hash_indices_panic2)
 * Ghidra: void FUN_001b8bac(void)
 * Noreturn panic: "Can't compare indices belonging to different hash tables".
 * Duplicate of FUN_001b8848.
 * Confidence: high (string-matched noreturn panic).
 */
void cl4_swift_hash_indices_panic2(void)
{
    cl4_swift_hash_indices_panic();
}

/*--------------------------------------------------------------------*/
/* FUN_001b8c2c @ 0x001b8c2c   (est. cl4_swift_idx_ne2)
 * Ghidra: uint FUN_001b8c2c(undefined8, undefined8, undefined8, undefined8)
 * Returns (FUN_002a0f24(param_3, param_4) ^ 1) & 1 — index not-equal.
 * Confidence: high (clear compare wrapper).
 */
unsigned int cl4_swift_idx_ne2(void *a, void *b, void *c, void *d)
{
    (void)a; (void)b;
    return (sk_swift_idx_cmp((unsigned long)c, (unsigned long)d) ^ 1) & 1;  /* FUN_002a0f24 */
}

/*--------------------------------------------------------------------*/
/* FUN_001b8c84 @ 0x001b8c84   (est. cl4_swift_string_cmp4)
 * Ghidra: void FUN_001b8c84(long, ulong, long, ulong)
 * Swift String compare variant of FUN_001b8920: equal->0, small-string compare via
 * FUN_003576ec, else FUN_002a0d50; result to FUN_00356d20.
 * Confidence: low (Swift string compare).
 */
void cl4_swift_string_cmp4(long w1, unsigned long f1, long w2, unsigned long f2)
{
    unsigned long r;
    if (w1 == w2 && f1 == f2) r = 0;
    else if ((((f1 ^ 0xffffffffffffffff) & 0x6000000000000000) == 0) &&
             ((f2 & 0x6000000000000000) == 0x6000000000000000)) {
        long x = 0;   /* FUN_003576ec() */
        r = (x != w2);
    } else {
        r = sk_swift_string_cmp2(0, 0, 0, 0, 0);   /* FUN_002a0d50 */
    }
    sk_swift_state(r);   /* FUN_00356d20(r, x30) */
}

/*--------------------------------------------------------------------*/
/* FUN_001b8cf4 @ 0x001b8cf4   (est. cl4_swift_cmp_finish2)
 * Ghidra: void FUN_001b8cf4(void)
 * FUN_00349fcc/FUN_0035044c/FUN_0008412c, indirect compare, FUN_00356d20.
 * Confidence: low (Swift compare finish).
 */
void cl4_swift_cmp_finish2(void)
{
    sk_swift_state(0);
    sk_swift_state2(0);
    sk_swift_flag(0);   /* (*extraout_x8)() */
    sk_swift_state3(0); /* FUN_00356d20 */
}

/*--------------------------------------------------------------------*/
/* FUN_001b8d34 @ 0x001b8d34   (est. cl4_swift_cmp_wrap3)
 * Ghidra: uint FUN_001b8d34(void)
 * FUN_00352764 then FUN_001b8fcc, returns result&1.
 * Confidence: low (Swift compare wrapper).
 */
unsigned int cl4_swift_cmp_wrap3(void)
{
    sk_swift_state(0);   /* FUN_00352764 */
    return (unsigned int)(cl4_swift_string_cmp5(0, 0, 0, 0) & 1);  /* FUN_001b8fcc */
}

/*--------------------------------------------------------------------*/
/* FUN_001b8d38 @ 0x001b8d38   (est. cl4_swift_cmp_wrap4)
 * Ghidra: uint FUN_001b8d38(void)
 * Duplicate of FUN_001b8d34.
 * Confidence: low (duplicate).
 */
unsigned int cl4_swift_cmp_wrap4(void)
{
    return cl4_swift_cmp_wrap3();
}

/*--------------------------------------------------------------------*/
/* FUN_001b8d84 @ 0x001b8d84   (est. cl4_swift_index_eq_ex)
 * Ghidra: uint FUN_001b8d84(undefined8*, undefined8, undefined8*, undefined8)
 * Existential collection index equality via FUN_0031bb80/FUN_0031bbe0; mismatched
 * base types panic. Returns flag.
 * Confidence: low (Swift existential index compare).
 */
unsigned int cl4_swift_index_eq_ex(void **a, void *ta, void **b, void *tb)
{
    (void)a; (void)ta; (void)b; (void)tb;
    long l3 = 0, l4 = 0;
    if (l3 == l4) return 0 & 1;
    sk_fatal_error((unsigned long)"Fatal error", 0xb, 2,
                   (unsigned long)"Base index types differ", 0x17, 2,
                   (unsigned long)"Swift/ExistentialCollection.swift", 0x21, 2, 0x742, 1);
}

/*--------------------------------------------------------------------*/
/* FUN_001b8efc @ 0x001b8efc   (est. cl4_swift_hash_indices_panic3)
 * Ghidra: void FUN_001b8efc(void)
 * Noreturn panic: "Can't compare indices belonging to different hash tables".
 * Duplicate.
 * Confidence: high (string-matched noreturn panic).
 */
void cl4_swift_hash_indices_panic3(void)
{
    cl4_swift_hash_indices_panic();
}

/*--------------------------------------------------------------------*/
/* FUN_001b8f80 @ 0x001b8f80   (est. cl4_swift_idx_eq)
 * Ghidra: uint FUN_001b8f80(void)
 * Returns FUN_002a0f24(x6, x7) & 1 — index equality.
 * Confidence: high (clear compare wrapper).
 */
unsigned int cl4_swift_idx_eq(void)
{
    return sk_swift_idx_cmp(0, 0) & 1;   /* FUN_002a0f24 */
}

/*--------------------------------------------------------------------*/
/* FUN_001b8fcc @ 0x001b8fcc   (est. cl4_swift_string_cmp5)
 * Ghidra: ulong FUN_001b8fcc(long, ulong, long, ulong)
 * Swift String compare: equal->0, small-string via FUN_0035aca4, else
 * FUN_00359214 string compare. Returns comparison result.
 * Confidence: low (Swift string compare).
 */
unsigned long cl4_swift_string_cmp5(long w1, unsigned long f1, long w2, unsigned long f2)
{
    if (w1 == w2 && f1 == f2) return 0;
    if ((((f1 ^ 0xffffffffffffffff) & 0x6000000000000000) == 0) &&
        ((f2 & 0x6000000000000000) == 0x6000000000000000)) {
        /* FUN_0035aca4 small-string compare */
        return (w2 != 0);
    }
    return sk_swift_string_cmp6(0, 0, 0, 0);   /* FUN_00359214 */
}

/*--------------------------------------------------------------------*/
/* FUN_001b9040 @ 0x001b9040   (est. cl4_swift_cmp_flag)
 * Ghidra: uint FUN_001b9040(void)
 * FUN_00349fcc/FUN_0035044c/FUN_0034aebc, indirect compare, returns flag&1.
 * Confidence: low (Swift compare flag).
 */
unsigned int cl4_swift_cmp_flag(void)
{
    unsigned int v = sk_swift_flag(0);   /* (*extraout_x8)() */
    return v & 1;
}

/*--------------------------------------------------------------------*/
/* FUN_001b9084 @ 0x001b9084   (est. cl4_swift_string_insert)
 * Ghidra: void FUN_001b9084(undefined8, ulong, ulong)
 * Swift String append/insert: for small strings copies the content via
 * FUN_00106e3c/FUN_002a9ba8/FUN_003576c8, else uses the inline-buffer path, then
 * appends via FUN_002979a4 and sets a flag FUN_00229a3c(0xff). Non-small form
 * appends via FUN_00359fe8/FUN_00297af0.
 * Confidence: low (Swift string insertion).
 */
void cl4_swift_string_insert(void *a, unsigned long word, unsigned long flags)
{
    (void)a;
    unsigned long w = word;
    if (flags & 0x2000000000000000) w = flags;
    if (((flags >> 0x3c & 1) == 0) && ((w >> 0x3e & 1) != 0)) {
        if ((flags >> 0x3d & 1) == 0) {
            if ((word >> 0x3c & 1) == 0) {
                /* FUN_00106e3c / FUN_002a9ba8 */
                sk_swift_get_cap(0, 0);
            } else {
                /* FUN_003576c8 */
                sk_swift_state(0);
            }
        } else {
            /* inline small-string path: auVar3 = {&local_30, flags>>0x38&0xf} */
            sk_swift_state(0);
        }
        /* FUN_002979a4(pair, a); FUN_00229a3c(0xff) */
        sk_swift_flag_set(0xff);
        return;
    }
    /* FUN_00359fe8 / FUN_00297af0(a) */
    sk_swift_state(0);
}

/*--------------------------------------------------------------------*/
/* FUN_001b9154 @ 0x001b9154   (est. cl4_swift_string_join_core)
 * Ghidra: undefined1[16] FUN_001b9154(ulong, ulong, undefined8, char)
 * Swift String joined/description core: builds a result string from the two input
 * words (param_1/param_2), appending a separator ("," or newline per param_4)
 * between elements via FUN_001a89a8/FUN_002364dc, using a string builder
 * (FUN_0006e778(0x23)) and element-append helpers. Returns the {word, flags} pair.
 * Confidence: low (Swift string join; element loop).
 */
cl4_result_t cl4_swift_string_join_core(unsigned long w1, unsigned long f1, void *p, char sep)
{
    (void)p;
    /* auVar15 = {w1, f1}; if (sep==1) auVar12=FUN_001a89a8(&DAT_005ce766,3,1)
     * else auVar12=FUN_002364dc(10,0) */
    cl4_result_t sepstr;
    if (sep == 1) sepstr = sk_swift_small_string(0, 3, 1);   /* FUN_001a89a8 */
    else sepstr = sk_swift_int_string(10, 0);                 /* FUN_002364dc */
    /* FUN_0006e778(0x23); FUN_001a89a8(&DAT_005be7c0,0,1) empty string */
    cl4_result_t out = sk_swift_string_builder(0);           /* build */
    /* element-append loop */
    return out;
}

/*--------------------------------------------------------------------*/
/* FUN_001b994c @ 0x001b994c   (est. cl4_swift_string_join_core2)
 * Ghidra: undefined1[16] FUN_001b994c(ulong, ulong, undefined8, char)
 * Duplicate of FUN_001b9154 (string join core).
 * Confidence: low (duplicate).
 */
cl4_result_t cl4_swift_string_join_core2(unsigned long w1, unsigned long f1, void *p, char sep)
{
    return cl4_swift_string_join_core(w1, f1, p, sep);
}

/*--------------------------------------------------------------------*/
/* FUN_001ba798 @ 0x001ba798   (est. cl4_swift_char_append)
 * Ghidra: void FUN_001ba798(undefined8, undefined8)
 * FUN_00356340(p1, p2, p1) then FUN_002379dc.
 * Confidence: low (Swift character/string append).
 */
void cl4_swift_char_append(void *a, void *b)
{
    sk_swift_shift((unsigned long)a, (unsigned long)b, (unsigned long)a);   /* FUN_00356340 */
    sk_swift_state(0);   /* FUN_002379dc */
}

/*--------------------------------------------------------------------*/
/* FUN_001ba79c @ 0x001ba79c   (est. cl4_swift_char_append2)
 * Ghidra: void FUN_001ba79c(undefined8, undefined8)
 * Duplicate of FUN_001ba798.
 * Confidence: low (duplicate).
 */
void cl4_swift_char_append2(void *a, void *b)
{
    cl4_swift_char_append(a, b);
}

/*--------------------------------------------------------------------*/
/* FUN_001ba7d4 @ 0x001ba7d4   (est. cl4_swift_char_append3)
 * Ghidra: void FUN_001ba7d4(undefined8, undefined8)
 * FUN_00356340(p1, p2, p1, p2) then FUN_00237f7c.
 * Confidence: low (Swift character/string append variant).
 */
void cl4_swift_char_append3(void *a, void *b)
{
    sk_swift_shift((unsigned long)a, (unsigned long)b, (unsigned long)a, (unsigned long)b); /* FUN_00356340 */
    sk_swift_state(0);   /* FUN_00237f7c */
}

/*--------------------------------------------------------------------*/
/* FUN_001ba7fc @ 0x001ba7fc   (est. cl4_swift_jumptable_dispatch)
 * Ghidra: void FUN_001ba7fc(void)
 * Runs FUN_0035697c/FUN_00358d88, resolves a jumptable target via FUN_00027724,
 * calls FUN_003507e0, then an indirect jump (unrecovered jumptable, treated as call).
 * Confidence: low (indirect jumptable dispatch; "Could not recover jumptable").
 */
void cl4_swift_jumptable_dispatch(void)
{
    /* FUN_0035697c / FUN_00358d88 / FUN_00027724 / FUN_003507e0 /
     * (*UNRECOVERED_JUMPTABLE)() */
    sk_swift_state(0);
}

/*--------------------------------------------------------------------*/
/* FUN_001ba83c @ 0x001ba83c   (est. cl4_swift_string_decode)
 * Ghidra: void FUN_001ba83c(undefined8, undefined8, undefined8)
 * Swift string decode/append path: current-CPU-agnostic helper that validates a
 * string pair and appends it through a long chain of Swift append/validate helpers
 * (FUN_0034b308, (*DAT_00658c00), FUN_0034b8bc...), with a non-trivial string
 * fallback. Heavy extraout chain.
 * Confidence: low (Swift string decode/append; many helpers).
 */
void cl4_swift_string_decode(void *a, void *b, void *c)
{
    (void)a; (void)b; (void)c;
    /* FUN_0008e518 / FUN_00356900 / FUN_00350a64 / FUN_00310d68 /
     * FUN_00348d7c / (*DAT_00658c00) / FUN_00348bd8 / FUN_0034b308 /
     * FUN_0034b8bc / FUN_003494e8 / FUN_003493c4 / FUN_0034c2f8 /
     * FUN_0034ba78 / FUN_0034bc58 */
    sk_swift_state(0);
}

/*--------------------------------------------------------------------*/
/* FUN_001bac44 @ 0x001bac44   (est. cl4_swift_decode_finish)
 * Ghidra: void FUN_001bac44(void)
 * Runs FUN_00350980/FUN_0035248c/FUN_00027724/FUN_0034c404, an indirect helper,
 * thunk_FUN_002acbb8, then FUN_003a25d4.
 * Confidence: low (Swift decode finish).
 */
void cl4_swift_decode_finish(void)
{
    /* FUN_00350980 / FUN_0035248c / FUN_00027724 / FUN_0034c404 /
     * (*extraout_x8)() / thunk_FUN_002acbb8 / FUN_003a25d4 */
    sk_swift_state(0);
}

/*--------------------------------------------------------------------*/
/* FUN_001bac98 @ 0x001bac98   (est. cl4_swift_string_decode2)
 * Ghidra: void FUN_001bac98(void)
 * Large Swift string decode/validate path: reads global state (_DAT_006ade68 /
 * _DAT_006c0150/_DAT_006c0160/_DAT_006c0168) and runs a long chain of Swift string
 * append/validate helpers. Complex global+string interleave.
 * Confidence: low (Swift string decode; global state reads).
 */
void cl4_swift_string_decode2(void)
{
    /* FUN_0034add4 / FUN_0039a128 / FUN_0036b270 / FUN_00362acc /
     * FUN_00319808 / FUN_00356b2c / FUN_0034c3f4 / FUN_000839d8 /
     * FUN_0034bc94 / FUN_00359be0 ... */
    sk_swift_state(0);
}

/*--------------------------------------------------------------------*/
/* FUN_001bb234 @ 0x001bb234   (est. cl4_swift_string_decode3)
 * Ghidra: void FUN_001bb234(undefined8, undefined8, long, ulong)
 * Swift string decode/append: resolves a string pair (FUN_00355578), validates its
 * bounds, and appends each element through a chain of Swift append helpers. Heavy
 * extraout chain; complex string handling.
 * Confidence: low (Swift string decode; many helpers).
 */
void cl4_swift_string_decode3(void *a, void *b, long n, unsigned long flags)
{
    (void)a; (void)b; (void)n; (void)flags;
    /* FUN_00355578 / FUN_00319808 / FUN_0034d044 / FUN_00351f34 /
     * FUN_00353d64 / FUN_0034895c / FUN_002060d4 / FUN_000026e8 ... */
    sk_swift_state(0);
}

/*--------------------------------------------------------------------*/
/* FUN_001bb558 @ 0x001bb558   (est. cl4_swift_prefix)
 * Ghidra: undefined1[16] FUN_001bb558(long, long)
 * Swift Collection prefix: validates n>=0 ("Can't take a prefix of negative length"),
 * computes the end bound via FUN_0019e97c, builds the prefix range via
 * FUN_0019eb88, and frees the intermediate (FUN_0036b118). Returns the pair.
 * Confidence: low (Swift collection prefix).
 */
cl4_result_t cl4_swift_prefix(long n, long coll)
{
    if (n < 0)
        sk_fatal_error((unsigned long)"Fatal error", 0xb, 2,
                       (unsigned long)"Can't take a prefix of negative length", 0x38, 2,
                       (unsigned long)"Swift/Collection.swift", 0x16, 2, 0x531, 1);
    long end = *(long *)(coll + 0x10);
    /* FUN_0019e97c(0, n, end, coll) */
    if (end >= 0) {
        /* FUN_0019e760(0, coll); FUN_0019e760(end, coll);
         * FUN_0019eb88(0, end, coll); FUN_0036b118(coll) */
        cl4_result_t r = sk_swift_range(0, end, coll);   /* FUN_0019eb88 */
        sk_swift_free(0);                                /* FUN_0036b118 */
        return r;
    }
    sk_fatal_error(0, 0);
}

/*--------------------------------------------------------------------*/
/* FUN_001bb69c @ 0x001bb69c   (est. cl4_swift_prefix2)
 * Ghidra: void FUN_001bb69c(long, undefined8, long)
 * Swift Collection prefix variant: validates n>=0, computes bound via FUN_0031f998,
 * builds the range via FUN_0028e8c0. Range inversion panics.
 * Confidence: low (Swift collection prefix).
 */
void cl4_swift_prefix2(long n, void *a, long end)
{
    if (n < 0)
        sk_fatal_error((unsigned long)"Fatal error", 0xb, 2,
                       (unsigned long)"Can't take a prefix of negative length", 0x38, 2,
                       (unsigned long)"Swift/Collection.swift", 0x16, 2, 0x531, 1);
    /* FUN_0031f998(0, n, end, a, end, 0x124, 300) */
    long e = end;
    if (e >= 0) { /* FUN_0028e8c0(0, e, a, end, 0x292, 0x293) */ return; }
    sk_fatal_error((unsigned long)"Fatal error", 0xb, 2,
                   (unsigned long)"Range requires lowerBound <= upperBound", 0x27, 2,
                   (unsigned long)"Swift/Range.swift", 0x11, 2, 0x2f9, 1);
}

/*--------------------------------------------------------------------*/
/* FUN_001bb7a0 @ 0x001bb7a0   (est. cl4_swift_string_decode4)
 * Ghidra: void FUN_001bb7a0(undefined8, undefined8, undefined8)
 * Large Swift string decode/append path with an extensive extraout chain
 * (FUN_0008e518, FUN_00377824, (*DAT_00658c00)...).
 * Confidence: low (Swift string decode; many helpers).
 */
void cl4_swift_string_decode4(void *a, void *b, void *c)
{
    (void)a; (void)b; (void)c;
    /* FUN_0008e518 / FUN_00355578 / FUN_00377824 / FUN_00348e18 /
     * FUN_0007c1a4 / (*DAT_00658c00) / ... */
    sk_swift_state(0);
}

/*--------------------------------------------------------------------*/
/* FUN_001bbc34 @ 0x001bbc34   (est. cl4_swift_drop_first)
 * Ghidra: undefined1[16] FUN_001bbc34(long, long)
 * Swift Collection dropFirst: validates n>=0 ("Can't drop a negative number of
 * elements"), computes the start bound via FUN_0019e97c, builds the suffix range via
 * FUN_0019eb88, frees the intermediate. Returns the pair.
 * Confidence: low (Swift collection dropFirst).
 */
cl4_result_t cl4_swift_drop_first(long n, long coll)
{
    if (n < 0)
        sk_fatal_error((unsigned long)"Fatal error", 0xb, 2,
                       (unsigned long)"Can't drop a negative number of elements", 0x3a, 2,
                       (unsigned long)"Swift/Collection.swift", 0x16, 2, 0x4e4, 1);
    long end = *(long *)(coll + 0x10);
    /* FUN_0019e97c(0, n, end, coll) */
    long start = end;
    if (start <= end) {
        /* FUN_0019e760(start, coll); FUN_0019e760(end, coll);
         * FUN_0019eb88(start, end, coll); FUN_0036b118(coll) */
        cl4_result_t r = sk_swift_range(start, end, coll);
        sk_swift_free(0);
        return r;
    }
    sk_fatal_error(0, 0);
}

/*--------------------------------------------------------------------*/
/* FUN_001bbd7c @ 0x001bbd7c   (est. cl4_swift_drop_first2)
 * Ghidra: void FUN_001bbd7c(long, ulong, ulong)
 * Swift Collection dropFirst variant: validates n>=0, computes the start bound via
 * the UTF-16/string index helpers, and builds the suffix range.
 * Confidence: low (Swift collection dropFirst).
 */
void cl4_swift_drop_first2(long n, unsigned long w, unsigned long flags)
{
    if (n < 0)
        sk_fatal_error((unsigned long)"Fatal error", 0xb, 2,
                       (unsigned long)"Can't drop a negative number of elements", 0x3a, 2,
                       (unsigned long)"Swift/Collection.swift", 0x16, 2, 0x4e4, 1);
    /* bounds check via UTF-16 helpers; build suffix range */
    sk_swift_state(0);
}

/*--------------------------------------------------------------------*/
/* FUN_001bbec4 @ 0x001bbec4   (est. cl4_swift_drop_first3)
 * Ghidra: void FUN_001bbec4(long, undefined8, long, undefined8, undefined8)
 * Swift Collection dropFirst variant: validates n>=0, computes start via
 * FUN_0031f998, builds range via FUN_001ff4e0. Range inversion panics.
 * Confidence: low (Swift collection dropFirst).
 */
void cl4_swift_drop_first3(long n, void *a, long end, void *b, void *c)
{
    if (n < 0)
        sk_fatal_error((unsigned long)"Fatal error", 0xb, 2,
                       (unsigned long)"Can't drop a negative number of elements", 0x3a, 2,
                       (unsigned long)"Swift/Collection.swift", 0x16, 2, 0x4e4, 1);
    /* FUN_0031f998(a, n) */
    long start = end;
    if (start <= end) { /* FUN_001ff4e0(start, end, a, end, b, c, 0x785, 0x786) */ return; }
    sk_fatal_error((unsigned long)"Fatal error", 0xb, 2,
                   (unsigned long)"Range requires lowerBound <= upperBound", 0x27, 2,
                   (unsigned long)"Swift/Range.swift", 0x11, 2, 0x2f9, 1);
}

/*--------------------------------------------------------------------*/
/* FUN_001bbfdc @ 0x001bbfdc   (est. cl4_swift_string_decode5)
 * Ghidra: void FUN_001bbfdc(undefined8, undefined8, undefined8)
 * Large Swift string decode/append path (extraout-heavy; like 001bb7a0).
 * Confidence: low (Swift string decode; many helpers).
 */
void cl4_swift_string_decode5(void *a, void *b, void *c)
{
    (void)a; (void)b; (void)c;
    sk_swift_state(0);
}

/*--------------------------------------------------------------------*/
/* FUN_001bc440 @ 0x001bc440   (est. cl4_swift_string_decode6)
 * Ghidra: void FUN_001bc440(undefined8, undefined8, ulong, undefined8)
 * Swift string decode/append with a long helper chain (extraout-heavy).
 * Confidence: low (Swift string decode; many helpers).
 */
void cl4_swift_string_decode6(void *a, void *b, unsigned long n, void *c)
{
    (void)a; (void)b; (void)n; (void)c;
    sk_swift_state(0);
}

/*--------------------------------------------------------------------*/
/* FUN_001bc900 @ 0x001bc900   (est. cl4_swift_string_emit)
 * Ghidra: void FUN_001bc900(void)
 * Swift string emission: locks (FUN_00357cb4), resolves a string via
 * FUN_00310d34/FUN_00348718, calls FUN_00376820/FUN_00355c28, and checks a flag via
 * FUN_0019fd10. On success emits via FUN_0034ce78/FUN_00287794.
 * Confidence: low (Swift string emission; flag check).
 */
void cl4_swift_string_emit(void)
{
    /* FUN_00357cb4 / FUN_0035316c / FUN_00352ddc / FUN_00310d34 /
     * FUN_00348718 / FUN_00376820 / FUN_00355c28 / FUN_0019fd10 */
    if (0 == 0) {   /* flag */
        /* FUN_0034ce78 / FUN_00287794 */
        sk_swift_state(0);
    }
    sk_swift_state(0);
}

/*--------------------------------------------------------------------*/
/* FUN_001bc978 @ 0x001bc978   (est. cl4_swift_string_format)
 * Ghidra: undefined8 FUN_001bc978(long, long)
 * Large Swift string format/parse path with global state reads and a long helper
 * chain.
 * Confidence: low (Swift string format; extraout-heavy).
 */
unsigned long cl4_swift_string_format(long a, long b)
{
    (void)a; (void)b;
    sk_swift_state(0);
    return 0;
}

/*--------------------------------------------------------------------*/
/* FUN_001bcc18 @ 0x001bcc18   (est. cl4_swift_string_decode7)
 * Ghidra: void FUN_001bcc18(void)
 * Swift string decode/append with a long helper chain (extraout-heavy).
 * Confidence: low (Swift string decode; many helpers).
 */
void cl4_swift_string_decode7(void)
{
    /* FUN_0034b7f4 / FUN_00353d64 / FUN_0034895c / ... */
    sk_swift_state(0);
}

/*--------------------------------------------------------------------*/
/* FUN_001bcda8 @ 0x001bcda8   (est. cl4_swift_word_expand)
 * Ghidra: undefined1[16] FUN_001bcda8(ulong)
 * Expands a 32-bit value into a {lo,hi} pair: lo = param_1&0xffffffff | param_1<<32,
 * hi = 0.
 * Confidence: high (clear bit expansion).
 */
cl4_result_t cl4_swift_word_expand(unsigned long v)
{
    cl4_result_t r = { v & 0xffffffff | v << 0x20, 0 };
    return r;
}

/*--------------------------------------------------------------------*/
/* FUN_001bcdb8 @ 0x001bcdb8   (est. cl4_swift_tuple_dup)
 * Ghidra: void FUN_001bcdb8(undefined8*, undefined8, undefined8, undefined8, undefined8)
 * Writes a 6-element tuple {p2,p3,p4,p5,p2,p3} into param_1, then releases p5.
 * Confidence: high (clear tuple store + release).
 */
void cl4_swift_tuple_dup(unsigned long *out, unsigned long a, unsigned long b,
                         unsigned long c, unsigned long d)
{
    out[0] = a; out[1] = b; out[2] = c; out[3] = d;
    out[4] = a; out[5] = b;
    sk_swift_free_pages(d);   /* thunk_FUN_0036b270(d) */
}

/*--------------------------------------------------------------------*/
/* FUN_001bcdcc @ 0x001bcdcc   (est. cl4_swift_pair_release)
 * Ghidra: void FUN_001bcdcc(void)
 * Resolves a string pair (FUN_003504d0), computes its length, and releases it
 * (thunk_FUN_0036b270 + FUN_0007c1c4).
 * Confidence: low (Swift pair release).
 */
void cl4_swift_pair_release(void)
{
    /* FUN_003504d0() -> pair; length = pair.hi>>0x38&0xf (or pair.lo&mask);
     * thunk_FUN_0036b270(length, pair.hi); FUN_0007c1c4() */
    sk_swift_state(0);
}

/*--------------------------------------------------------------------*/
/* FUN_001bce34 @ 0x001bce34   (est. cl4_object_service_complete3)
 * Ghidra: void FUN_001bce34(void)
 * Object-service completion: saves CPU (FUN_00084220), locks, dispatches via
 * (*DAT_00658c00), and runs the completion chain before the epilogue.
 * Confidence: low (object-service completion; helper chain).
 */
void cl4_object_service_complete3(void)
{
    /* FUN_00084220 / FUN_0034c084 / FUN_00349748 / FUN_00377824 /
     * FUN_00351f10 / (*DAT_00658c00) / FUN_00348bbc / FUN_0034b8bc /
     * FUN_00349734 ... */
    sk_swift_state(0);
}

/*--------------------------------------------------------------------*/
/* FUN_001bcf40 @ 0x001bcf40   (est. cl4_object_service_complete4)
 * Ghidra: void FUN_001bcf40(void)
 * Object-service completion: current CPU (FUN_0008e518), locks, dispatches via
 * (*DAT_00658c00) and (x12+0x10), runs the completion chain, epilogue.
 * Confidence: low (object-service completion; helper chain).
 */
void cl4_object_service_complete4(void)
{
    /* FUN_0008e518 / FUN_0034aa3c / FUN_00358e88 / FUN_00349a68 /
     * (*DAT_00658c00) / FUN_00349068 / FUN_00349720 / (*DAT_00658c00) /
     * FUN_003493ac / (x12+0x10) / FUN_0034ee08 ... */
    sk_swift_state(0);
}

/*--------------------------------------------------------------------*/
/* FUN_001bd030 @ 0x001bd030   (est. cl4_swift_collection_drain)
 * Ghidra: long FUN_001bd030(void)
 * Swift collection drain/iterate: walks the collection (unaff_x20) via the object
 * service helpers, returning a count. Extraout-heavy.
 * Confidence: low (Swift collection iteration).
 */
long cl4_swift_collection_drain(void)
{
    sk_swift_state(0);
    return 0;
}

/*--------------------------------------------------------------------*/
/* FUN_001bd234 @ 0x001bd234   (est. cl4_swift_string_append)
 * Ghidra: void FUN_001bd234(void)
 * Swift string append path with a long helper chain (extraout-heavy).
 * Confidence: low (Swift string append).
 */
void cl4_swift_string_append(void)
{
    /* FUN_00348ce8 / (*DAT_00658c00) / FUN_0034b7f4 ... */
    sk_swift_state(0);
}

/*--------------------------------------------------------------------*/
/* FUN_001bd380 @ 0x001bd380   (est. cl4_bitset_contains)
 * Ghidra: bool FUN_001bd380(long, long)
 * Swift Bitset contains: hashes param_1 into the bitset (param_2) via
 * thunk_FUN_00229ebc and probes the bit array (base param_2+0x38, bucket at
 * +0x20/+0x28/+0x30), returning whether the element's bit is set.
 * Confidence: low (Swift bitset membership probe).
 */
bool cl4_bitset_contains(long key, long bs)
{
    if (*(long *)(bs + 0x10) == 0) return false;
    unsigned long h = thunk_sk_swift_hash(*(unsigned long *)(bs + 0x28), key);  /* FUN_00229ebc */
    do {
        unsigned long idx = h & ~(~0L << (*(unsigned char *)(bs + 0x20) & 0x3f));
        h = 1L << (idx & 0x3f) & *(unsigned long *)(bs + 0x38 + (idx >> 6) * 8);
        if (h == 0) return false;
        h = idx + 1;
    } while (*(long *)(*(long *)(bs + 0x30) + 0 * 8) != key);
    return true;
}

/*--------------------------------------------------------------------*/
/* FUN_001bd408 @ 0x001bd408   (est. cl4_bitset_insert)
 * Ghidra: void FUN_001bd408(undefined8, undefined8, long)
 * Swift Bitset insert: hashes key (param_3) into the bitset via
 * thunk_FUN_00229ebc, probes, and inserts (setting the bit and storing the key) if
 * absent. Uses FUN_000b4594 for allocation.
 * Confidence: low (Swift bitset insertion).
 */
void cl4_bitset_insert(void *a, void *b, long key)
{
    (void)a; (void)b;
    /* FUN_000b4594; if (*(param_3+0x10)==0) return absent;
     * else probe via thunk_FUN_00229ebc and insert */
    sk_swift_state(0);
}

/*--------------------------------------------------------------------*/
/* FUN_001bd4f0 @ 0x001bd4f0   (est. cl4_object_service_complete5)
 * Ghidra: void FUN_001bd4f0(void)
 * Object-service completion with a long extraout chain and indirect dispatch.
 * Confidence: low (object-service completion).
 */
void cl4_object_service_complete5(void)
{
    /* FUN_0034b7f4 / FUN_00353d64 / ... */
    sk_swift_state(0);
}

/*--------------------------------------------------------------------*/
/* FUN_001bd66c @ 0x001bd66c   (est. cl4_swift_string_append2)
 * Ghidra: void FUN_001bd66c(undefined8, undefined8, undefined8)
 * Swift string append: FUN_0008409c(p3), resolves the pair via FUN_002ab130, then
 * FUN_0035063c + FUN_002a55c0.
 * Confidence: low (Swift string append).
 */
void cl4_swift_string_append2(void *a, void *b, void *c)
{
    (void)a; (void)b;
    sk_swift_state(c);   /* FUN_0008409c(c) */
    unsigned long w = sk_swift_utf16_set(0);   /* FUN_002ab130 */
    sk_swift_state(w, w);                       /* FUN_0035063c */
    sk_swift_state2(0);                         /* FUN_002a55c0 */
}

/*--------------------------------------------------------------------*/
/* FUN_001bd6b0 @ 0x001bd6b0   (est. cl4_swift_string_append3)
 * Ghidra: void FUN_001bd6b0(void)
 * FUN_0034d7a8/FUN_003199d4/FUN_00351d18 then FUN_001bd6dc.
 * Confidence: medium (wrapper chain).
 */
void cl4_swift_string_append3(void)
{
    sk_swift_state(0);   /* FUN_0034d7a8 */
    sk_swift_state2(0);  /* FUN_003199d4 */
    sk_swift_state3(0);  /* FUN_00351d18 */
    cl4_swift_string_append4(0);   /* FUN_001bd6dc */
}

/*--------------------------------------------------------------------*/
/* FUN_001bd6dc @ 0x001bd6dc   (est. cl4_swift_string_append4)
 * Ghidra: void FUN_001bd6dc(undefined8)
 * FUN_00210bd4(param_1, FUN_001c1d00).
 * Confidence: low (Swift string append via closure FUN_001c1d00).
 */
void cl4_swift_string_append4(void *a)
{
    sk_swift_state(a, (unsigned long)cl4_swift_string_append4);   /* FUN_00210bd4(a, FUN_001c1d00) */
}

/*--------------------------------------------------------------------*/
/* FUN_001bd6f4 @ 0x001bd6f4   (est. cl4_swift_vtable_call0)
 * Ghidra: void FUN_001bd6f4(void)
 * FUN_0007c198 then an indirect call through (x16+0x40).
 * Confidence: low (Swift vtable method dispatch, slot 0x40).
 */
void cl4_swift_vtable_call0(void)
{
    /* FUN_0007c198 / (**(code**)(x16+0x40))() */
    sk_swift_state(0);
}

/*--------------------------------------------------------------------*/
/* Swift protocol-witness / vtable dispatch thunks 0x1bd72c-0x1be0ec.
 * Each resolves the self/value witness through FUN_0034b7f4() and calls the
 * witness-table slot at x16+<offset>. These implement the Swift Collection /
 * BidirectionalCollection / RandomAccessCollection protocol witnesses. The
 * offset identifies the method; the two-arg forms pass (pair.lo, pair.hi,
 * elem+0x10, elem+0x18) from the element descriptor. All confidence low
 * (indirect protocol-witness dispatch). */

#define SK_WITNESS_DISPATCH(name_, addr_, slot_, pass2_) \
void name_(void *p1, void *p2, long elem) \
{ \
    (void)p1; (void)p2; \
    cl4_result_t w = sk_swift_witness(0);   /* FUN_0034b7f4 */ \
    void (*f)(unsigned long, unsigned long, unsigned long, unsigned long); \
    f = *(void (**)(unsigned long, unsigned long, unsigned long, unsigned long))((char *)w.lo + (slot_)); \
    if (pass2_) f(w.lo, w.hi, *(unsigned long *)(elem + 0x10), *(unsigned long *)(elem + 0x18)); \
    else       f(w.lo, *(unsigned long *)(w.hi + 0x10), *(unsigned long *)(w.hi + 0x18), 0); \
}

/* 0x48 */
/*--------------------------------------------------------------------*/
/* FUN_001bd72c @ 0x001bd72c   (est. cl4_swift_witness_048)
 * Swift witness dispatch thunk (indirect protocol-witness call). Slot dispatch via FUN_0034b7f4/FUN_0034b798.
 * Confidence: low (indirect witness dispatch).
 * Notes: faithful body as generated; see family comment above. */
void cl4_swift_witness_048(void *p1, void *p2, long elem)
{ (void)p1; (void)p2; cl4_result_t w = sk_swift_witness(0);
  void (*f)(unsigned long,unsigned long,unsigned long,unsigned long) =
    *(void (**)(unsigned long,unsigned long,unsigned long,unsigned long))((char*)w.lo + 0x48);
  f(w.lo, *(unsigned long*)(w.hi+0x10), *(unsigned long*)(w.hi+0x18), 0); }
/* 0x50 */
/*--------------------------------------------------------------------*/
/* FUN_001bd768 @ 0x001bd768   (est. cl4_swift_witness_050)
 * Swift witness dispatch thunk (indirect protocol-witness call). Slot dispatch via FUN_0034b7f4/FUN_0034b798.
 * Confidence: low (indirect witness dispatch).
 * Notes: faithful body as generated; see family comment above. */
void cl4_swift_witness_050(void *p1, void *p2, long elem)
{ (void)p1; (void)p2; cl4_result_t w = sk_swift_witness(0);
  void (*f)(unsigned long,unsigned long,unsigned long,unsigned long) =
    *(void (**)(unsigned long,unsigned long,unsigned long,unsigned long))((char*)w.lo + 0x50);
  f(w.lo, w.hi, *(unsigned long*)(elem+0x10), *(unsigned long*)(elem+0x18)); }
/* 0x58 */
/*--------------------------------------------------------------------*/
/* FUN_001bd7a4 @ 0x001bd7a4   (est. cl4_swift_witness_058)
 * Swift witness dispatch thunk (indirect protocol-witness call). Slot dispatch via FUN_0034b7f4/FUN_0034b798.
 * Confidence: low (indirect witness dispatch).
 * Notes: faithful body as generated; see family comment above. */
void cl4_swift_witness_058(void *p1, void *p2, long elem)
{ (void)p1; (void)p2; cl4_result_t w = sk_swift_witness(0);
  void (*f)(unsigned long,unsigned long,unsigned long,unsigned long) =
    *(void (**)(unsigned long,unsigned long,unsigned long,unsigned long))((char*)w.lo + 0x58);
  f(w.lo, *(unsigned long*)(w.hi+0x10), *(unsigned long*)(w.hi+0x18), 0); }
/* 0x60 */
/*--------------------------------------------------------------------*/
/* FUN_001bd7e0 @ 0x001bd7e0   (est. cl4_swift_witness_060)
 * Swift witness dispatch thunk (indirect protocol-witness call). Slot dispatch via FUN_0034b7f4/FUN_0034b798.
 * Confidence: low (indirect witness dispatch).
 * Notes: faithful body as generated; see family comment above. */
void cl4_swift_witness_060(void *p1, void *p2, long elem)
{ (void)p1; (void)p2; cl4_result_t w = sk_swift_witness(0);
  void (*f)(unsigned long,unsigned long,unsigned long,unsigned long) =
    *(void (**)(unsigned long,unsigned long,unsigned long,unsigned long))((char*)w.lo + 0x60);
  f(w.lo, *(unsigned long*)(w.hi+0x10), *(unsigned long*)(w.hi+0x18), 0); }
/* 0x68 */
/*--------------------------------------------------------------------*/
/* FUN_001bd81c @ 0x001bd81c   (est. cl4_swift_witness_068)
 * Swift witness dispatch thunk (indirect protocol-witness call). Slot dispatch via FUN_0034b7f4/FUN_0034b798.
 * Confidence: low (indirect witness dispatch).
 * Notes: faithful body as generated; see family comment above. */
void cl4_swift_witness_068(void *p1, void *p2, long elem)
{ (void)p1; (void)p2; cl4_result_t w = sk_swift_witness(0);
  void (*f)(unsigned long,unsigned long,unsigned long,unsigned long) =
    *(void (**)(unsigned long,unsigned long,unsigned long,unsigned long))((char*)w.lo + 0x68);
  f(w.lo, *(unsigned long*)(w.hi+0x10), *(unsigned long*)(w.hi+0x18), 0); }
/* 0x70 */
/*--------------------------------------------------------------------*/
/* FUN_001bd858 @ 0x001bd858   (est. cl4_swift_witness_070)
 * Swift witness dispatch thunk (indirect protocol-witness call). Slot dispatch via FUN_0034b7f4/FUN_0034b798.
 * Confidence: low (indirect witness dispatch).
 * Notes: faithful body as generated; see family comment above. */
void cl4_swift_witness_070(void *p1, void *p2, long elem)
{ (void)p1; (void)p2; cl4_result_t w = sk_swift_witness(0);
  void (*f)(unsigned long,unsigned long,unsigned long,unsigned long) =
    *(void (**)(unsigned long,unsigned long,unsigned long,unsigned long))((char*)w.lo + 0x70);
  f(w.lo, w.hi, *(unsigned long*)(elem+0x10), *(unsigned long*)(elem+0x18)); }
/* 0x78 */
/*--------------------------------------------------------------------*/
/* FUN_001bd894 @ 0x001bd894   (est. cl4_swift_witness_078)
 * Swift witness dispatch thunk (indirect protocol-witness call). Slot dispatch via FUN_0034b7f4/FUN_0034b798.
 * Confidence: low (indirect witness dispatch).
 * Notes: faithful body as generated; see family comment above. */
void cl4_swift_witness_078(void *p1, void *p2, long elem)
{ (void)p1; (void)p2; cl4_result_t w = sk_swift_witness(0);
  void (*f)(unsigned long,unsigned long,unsigned long,unsigned long) =
    *(void (**)(unsigned long,unsigned long,unsigned long,unsigned long))((char*)w.lo + 0x78);
  f(w.lo, w.hi, *(unsigned long*)(elem+0x10), *(unsigned long*)(elem+0x18)); }
/* 0x80 */
/*--------------------------------------------------------------------*/
/* FUN_001bd8d0 @ 0x001bd8d0   (est. cl4_swift_witness_080)
 * Swift witness dispatch thunk (indirect protocol-witness call). Slot dispatch via FUN_0034b7f4/FUN_0034b798.
 * Confidence: low (indirect witness dispatch).
 * Notes: faithful body as generated; see family comment above. */
void cl4_swift_witness_080(void *p1, void *p2, long elem)
{ (void)p1; (void)p2; cl4_result_t w = sk_swift_witness(0);
  void (*f)(unsigned long,unsigned long,unsigned long,unsigned long) =
    *(void (**)(unsigned long,unsigned long,unsigned long,unsigned long))((char*)w.lo + 0x80);
  f(w.lo, w.hi, *(unsigned long*)(elem+0x10), *(unsigned long*)(elem+0x18)); }
/* 0x88 */
/*--------------------------------------------------------------------*/
/* FUN_001bd90c @ 0x001bd90c   (est. cl4_swift_witness_088)
 * Swift witness dispatch thunk (indirect protocol-witness call). Slot dispatch via FUN_0034b7f4/FUN_0034b798.
 * Confidence: low (indirect witness dispatch).
 * Notes: faithful body as generated; see family comment above. */
void cl4_swift_witness_088(void *p1, void *p2, long elem)
{ (void)p1; (void)p2; cl4_result_t w = sk_swift_witness(0);
  void (*f)(unsigned long,unsigned long,unsigned long,unsigned long) =
    *(void (**)(unsigned long,unsigned long,unsigned long,unsigned long))((char*)w.lo + 0x88);
  f(w.lo, w.hi, *(unsigned long*)(elem+0x10), *(unsigned long*)(elem+0x18)); }
/* 0x90 */
/*--------------------------------------------------------------------*/
/* FUN_001bd948 @ 0x001bd948   (est. cl4_swift_witness_090)
 * Swift witness dispatch thunk (indirect protocol-witness call). Slot dispatch via FUN_0034b7f4/FUN_0034b798.
 * Confidence: low (indirect witness dispatch).
 * Notes: faithful body as generated; see family comment above. */
void cl4_swift_witness_090(void *p1, void *p2, long elem)
{ (void)p1; (void)p2; cl4_result_t w = sk_swift_witness(0);
  void (*f)(unsigned long,unsigned long,unsigned long,unsigned long) =
    *(void (**)(unsigned long,unsigned long,unsigned long,unsigned long))((char*)w.lo + 0x90);
  f(w.lo, w.hi, *(unsigned long*)(elem+0x10), *(unsigned long*)(elem+0x18)); }
/* 0x98 */
/*--------------------------------------------------------------------*/
/* FUN_001bd984 @ 0x001bd984   (est. cl4_swift_witness_098)
 * Swift witness dispatch thunk (indirect protocol-witness call). Slot dispatch via FUN_0034b7f4/FUN_0034b798.
 * Confidence: low (indirect witness dispatch).
 * Notes: faithful body as generated; see family comment above. */
void cl4_swift_witness_098(void *p1, void *p2, long elem)
{ (void)p1; (void)p2; cl4_result_t w = sk_swift_witness(0);
  void (*f)(unsigned long,unsigned long,unsigned long,unsigned long) =
    *(void (**)(unsigned long,unsigned long,unsigned long,unsigned long))((char*)w.lo + 0x98);
  f(w.lo, *(unsigned long*)(w.hi+0x10), *(unsigned long*)(w.hi+0x18), 0); }
/* 0xa0 */
/*--------------------------------------------------------------------*/
/* FUN_001bd9c0 @ 0x001bd9c0   (est. cl4_swift_witness_0a0)
 * Swift witness dispatch thunk (indirect protocol-witness call). Slot dispatch via FUN_0034b7f4/FUN_0034b798.
 * Confidence: low (indirect witness dispatch).
 * Notes: faithful body as generated; see family comment above. */
void cl4_swift_witness_0a0(void *p1, void *p2, long elem)
{ (void)p1; (void)p2; cl4_result_t w = sk_swift_witness(0);
  void (*f)(unsigned long,unsigned long,unsigned long,unsigned long) =
    *(void (**)(unsigned long,unsigned long,unsigned long,unsigned long))((char*)w.lo + 0xa0);
  f(w.lo, w.hi, *(unsigned long*)(elem+0x10), *(unsigned long*)(elem+0x18)); }
/* 0xa8 */
/*--------------------------------------------------------------------*/
/* FUN_001bd9fc @ 0x001bd9fc   (est. cl4_swift_witness_0a8)
 * Swift witness dispatch thunk (indirect protocol-witness call). Slot dispatch via FUN_0034b7f4/FUN_0034b798.
 * Confidence: low (indirect witness dispatch).
 * Notes: faithful body as generated; see family comment above. */
void cl4_swift_witness_0a8(void *p1, void *p2, long elem)
{ (void)p1; (void)p2; cl4_result_t w = sk_swift_witness(0);
  void (*f)(unsigned long,unsigned long,unsigned long,unsigned long) =
    *(void (**)(unsigned long,unsigned long,unsigned long,unsigned long))((char*)w.lo + 0xa8);
  f(w.lo, w.hi, *(unsigned long*)(elem+0x10), *(unsigned long*)(elem+0x18)); }
/* 0xb0 */
/*--------------------------------------------------------------------*/
/* FUN_001bda38 @ 0x001bda38   (est. cl4_swift_witness_0b0)
 * Swift witness dispatch thunk (indirect protocol-witness call). Slot dispatch via FUN_0034b7f4/FUN_0034b798.
 * Confidence: low (indirect witness dispatch).
 * Notes: faithful body as generated; see family comment above. */
void cl4_swift_witness_0b0(void *p1, void *p2, long elem)
{ (void)p1; (void)p2; cl4_result_t w = sk_swift_witness(0);
  void (*f)(unsigned long,unsigned long,unsigned long,unsigned long) =
    *(void (**)(unsigned long,unsigned long,unsigned long,unsigned long))((char*)w.lo + 0xb0);
  f(w.lo, w.hi, *(unsigned long*)(elem+0x10), *(unsigned long*)(elem+0x18)); }
/* 0xb8 */
/*--------------------------------------------------------------------*/
/* FUN_001bda74 @ 0x001bda74   (est. cl4_swift_witness_0b8)
 * Swift witness dispatch thunk (indirect protocol-witness call). Slot dispatch via FUN_0034b7f4/FUN_0034b798.
 * Confidence: low (indirect witness dispatch).
 * Notes: faithful body as generated; see family comment above. */
void cl4_swift_witness_0b8(void *p1, void *p2, long elem)
{ (void)p1; (void)p2; cl4_result_t w = sk_swift_witness(0);
  void (*f)(unsigned long,unsigned long,unsigned long,unsigned long) =
    *(void (**)(unsigned long,unsigned long,unsigned long,unsigned long))((char*)w.lo + 0xb8);
  f(w.lo, w.hi, *(unsigned long*)(elem+0x10), *(unsigned long*)(elem+0x18)); }
/* 0xc0 */
/*--------------------------------------------------------------------*/
/* FUN_001bdab0 @ 0x001bdab0   (est. cl4_swift_witness_0c0)
 * Swift witness dispatch thunk (indirect protocol-witness call). Slot dispatch via FUN_0034b7f4/FUN_0034b798.
 * Confidence: low (indirect witness dispatch).
 * Notes: faithful body as generated; see family comment above. */
void cl4_swift_witness_0c0(void *p1, void *p2, long elem)
{ (void)p1; (void)p2; cl4_result_t w = sk_swift_witness(0);
  void (*f)(unsigned long,unsigned long,unsigned long,unsigned long) =
    *(void (**)(unsigned long,unsigned long,unsigned long,unsigned long))((char*)w.lo + 0xc0);
  f(w.lo, w.hi, *(unsigned long*)(elem+0x10), *(unsigned long*)(elem+0x18)); }
/* 0xc8 */
/*--------------------------------------------------------------------*/
/* FUN_001bdaec @ 0x001bdaec   (est. cl4_swift_witness_0c8)
 * Swift witness dispatch thunk (indirect protocol-witness call). Slot dispatch via FUN_0034b7f4/FUN_0034b798.
 * Confidence: low (indirect witness dispatch).
 * Notes: faithful body as generated; see family comment above. */
void cl4_swift_witness_0c8(void *p1, void *p2, long elem)
{ (void)p1; (void)p2; cl4_result_t w = sk_swift_witness(0);
  void (*f)(unsigned long,unsigned long,unsigned long,unsigned long) =
    *(void (**)(unsigned long,unsigned long,unsigned long,unsigned long))((char*)w.lo + 0xc8);
  f(w.lo, *(unsigned long*)(w.hi+0x10), *(unsigned long*)(w.hi+0x18), 0); }
/* 0xd0 (5-arg form) */
/*--------------------------------------------------------------------*/
/* FUN_001bdb28 @ 0x001bdb28   (est. cl4_swift_witness_0d0)
 * Swift witness dispatch thunk (indirect protocol-witness call). Slot dispatch via FUN_0034b7f4/FUN_0034b798.
 * Confidence: low (indirect witness dispatch).
 * Notes: faithful body as generated; see family comment above. */
void cl4_swift_witness_0d0(void *p1, void *p2, long elem, void *p4, void *p5)
{ (void)p1; (void)p2; (void)p4; (void)p5; cl4_result_t w = sk_swift_witness(0);
  void (*f)(unsigned long,unsigned long,unsigned long,unsigned long,unsigned long,unsigned long) =
    *(void (**)(unsigned long,unsigned long,unsigned long,unsigned long,unsigned long,unsigned long))((char*)w.lo + 0xd0);
  f(w.lo, w.hi, 0, *(unsigned long*)(elem+0x10), 0, *(unsigned long*)(elem+0x18)); }
/* 0xd8 (5-arg form) */
/*--------------------------------------------------------------------*/
/* FUN_001bdb68 @ 0x001bdb68   (est. cl4_swift_witness_0d8)
 * Swift witness dispatch thunk (indirect protocol-witness call). Slot dispatch via FUN_0034b7f4/FUN_0034b798.
 * Confidence: low (indirect witness dispatch).
 * Notes: faithful body as generated; see family comment above. */
void cl4_swift_witness_0d8(void *p1, void *p2, long elem, void *p4, void *p5)
{ (void)p1; (void)p2; (void)p4; (void)p5; cl4_result_t w = sk_swift_witness(0);
  void (*f)(unsigned long,unsigned long,unsigned long,unsigned long,unsigned long,unsigned long) =
    *(void (**)(unsigned long,unsigned long,unsigned long,unsigned long,unsigned long,unsigned long))((char*)w.lo + 0xd8);
  f(w.lo, w.hi, 0, *(unsigned long*)(elem+0x10), 0, *(unsigned long*)(elem+0x18)); }
/* 0xe0 */
/*--------------------------------------------------------------------*/
/* FUN_001bdba8 @ 0x001bdba8   (est. cl4_swift_witness_0e0)
 * Swift witness dispatch thunk (indirect protocol-witness call). Slot dispatch via FUN_0034b7f4/FUN_0034b798.
 * Confidence: low (indirect witness dispatch).
 * Notes: faithful body as generated; see family comment above. */
void cl4_swift_witness_0e0(void *p1, void *p2, long elem)
{ (void)p1; (void)p2; cl4_result_t w = sk_swift_witness(0);
  void (*f)(unsigned long,unsigned long,unsigned long,unsigned long) =
    *(void (**)(unsigned long,unsigned long,unsigned long,unsigned long))((char*)w.lo + 0xe0);
  f(w.lo, w.hi, *(unsigned long*)(elem+0x10), *(unsigned long*)(elem+0x18)); }
/* 0xe8 */
/*--------------------------------------------------------------------*/
/* FUN_001bdbe4 @ 0x001bdbe4   (est. cl4_swift_witness_0e8)
 * Swift witness dispatch thunk (indirect protocol-witness call). Slot dispatch via FUN_0034b7f4/FUN_0034b798.
 * Confidence: low (indirect witness dispatch).
 * Notes: faithful body as generated; see family comment above. */
void cl4_swift_witness_0e8(void *p1, void *p2, long elem)
{ (void)p1; (void)p2; cl4_result_t w = sk_swift_witness(0);
  void (*f)(unsigned long,unsigned long,unsigned long,unsigned long) =
    *(void (**)(unsigned long,unsigned long,unsigned long,unsigned long))((char*)w.lo + 0xe8);
  f(w.lo, *(unsigned long*)(w.hi+0x10), *(unsigned long*)(w.hi+0x18), 0); }
/* 0xf0 */
/*--------------------------------------------------------------------*/
/* FUN_001bdc20 @ 0x001bdc20   (est. cl4_swift_witness_0f0)
 * Swift witness dispatch thunk (indirect protocol-witness call). Slot dispatch via FUN_0034b7f4/FUN_0034b798.
 * Confidence: low (indirect witness dispatch).
 * Notes: faithful body as generated; see family comment above. */
void cl4_swift_witness_0f0(void *p1, void *p2, long elem)
{ (void)p1; (void)p2; cl4_result_t w = sk_swift_witness(0);
  void (*f)(unsigned long,unsigned long,unsigned long,unsigned long) =
    *(void (**)(unsigned long,unsigned long,unsigned long,unsigned long))((char*)w.lo + 0xf0);
  f(w.lo, *(unsigned long*)(w.hi+0x10), *(unsigned long*)(w.hi+0x18), 0); }
/* 0xf8 */
/*--------------------------------------------------------------------*/
/* FUN_001bdc5c @ 0x001bdc5c   (est. cl4_swift_witness_0f8)
 * Swift witness dispatch thunk (indirect protocol-witness call). Slot dispatch via FUN_0034b7f4/FUN_0034b798.
 * Confidence: low (indirect witness dispatch).
 * Notes: faithful body as generated; see family comment above. */
void cl4_swift_witness_0f8(void *p1, void *p2, long elem)
{ (void)p1; (void)p2; cl4_result_t w = sk_swift_witness(0);
  void (*f)(unsigned long,unsigned long,unsigned long,unsigned long) =
    *(void (**)(unsigned long,unsigned long,unsigned long,unsigned long))((char*)w.lo + 0xf8);
  f(w.lo & 0xffffffffff, w.hi, *(unsigned long*)(elem+0x10), *(unsigned long*)(elem+0x18)); }
/* 0x100 */
/*--------------------------------------------------------------------*/
/* FUN_001bdc9c @ 0x001bdc9c   (est. cl4_swift_witness_100)
 * Swift witness dispatch thunk (indirect protocol-witness call). Slot dispatch via FUN_0034b7f4/FUN_0034b798.
 * Confidence: low (indirect witness dispatch).
 * Notes: faithful body as generated; see family comment above. */
void cl4_swift_witness_100(void *p1, void *p2, long elem)
{ (void)p1; (void)p2; cl4_result_t w = sk_swift_witness(0);
  void (*f)(unsigned long,unsigned long,unsigned long,unsigned long) =
    *(void (**)(unsigned long,unsigned long,unsigned long,unsigned long))((char*)w.lo + 0x100);
  f(w.lo, *(unsigned long*)(w.hi+0x10), *(unsigned long*)(w.hi+0x18), 0); }
/* 0x108 */
/*--------------------------------------------------------------------*/
/* FUN_001bdce0 @ 0x001bdce0   (est. cl4_swift_witness_108)
 * Swift witness dispatch thunk (indirect protocol-witness call). Slot dispatch via FUN_0034b7f4/FUN_0034b798.
 * Confidence: low (indirect witness dispatch).
 * Notes: faithful body as generated; see family comment above. */
void cl4_swift_witness_108(void *p1, void *p2, long elem)
{ (void)p1; (void)p2; cl4_result_t w = sk_swift_witness(0);
  void (*f)(unsigned long,unsigned long,unsigned long,unsigned long) =
    *(void (**)(unsigned long,unsigned long,unsigned long,unsigned long))((char*)w.lo + 0x108);
  f(w.lo, w.hi, *(unsigned long*)(elem+0x10), *(unsigned long*)(elem+0x18)); }
/* 0x110 (3-arg, low24) */
/*--------------------------------------------------------------------*/
/* FUN_001bdd24 @ 0x001bdd24   (est. cl4_swift_witness_110)
 * Swift witness dispatch thunk (indirect protocol-witness call). Slot dispatch via FUN_0034b7f4/FUN_0034b798.
 * Confidence: low (indirect witness dispatch).
 * Notes: faithful body as generated; see family comment above. */
void cl4_swift_witness_110(void *p1, void *p2, long elem)
{ (void)p1; (void)p2; cl4_result_t w = sk_swift_witness(0);
  void (*f)(unsigned long,unsigned long,unsigned long,unsigned long) =
    *(void (**)(unsigned long,unsigned long,unsigned long,unsigned long))((char*)w.lo + 0x110);
  f(w.lo & 0xffffff, 0, *(unsigned long*)(elem+0x10), *(unsigned long*)(elem+0x18)); }
/* 0x118 */
/*--------------------------------------------------------------------*/
/* FUN_001bdd6c @ 0x001bdd6c   (est. cl4_swift_witness_118)
 * Swift witness dispatch thunk (indirect protocol-witness call). Slot dispatch via FUN_0034b7f4/FUN_0034b798.
 * Confidence: low (indirect witness dispatch).
 * Notes: faithful body as generated; see family comment above. */
void cl4_swift_witness_118(void *p1, void *p2, long elem)
{ (void)p1; (void)p2; cl4_result_t w = sk_swift_witness(0);
  void (*f)(unsigned long,unsigned long,unsigned long,unsigned long) =
    *(void (**)(unsigned long,unsigned long,unsigned long,unsigned long))((char*)w.lo + 0x118);
  f(w.lo & 0xffffffffff, w.hi, *(unsigned long*)(elem+0x10), *(unsigned long*)(elem+0x18)); }
/* 0x120 */
/*--------------------------------------------------------------------*/
/* FUN_001bddb4 @ 0x001bddb4   (est. cl4_swift_witness_120)
 * Swift witness dispatch thunk (indirect protocol-witness call). Slot dispatch via FUN_0034b7f4/FUN_0034b798.
 * Confidence: low (indirect witness dispatch).
 * Notes: faithful body as generated; see family comment above. */
void cl4_swift_witness_120(void *p1, void *p2, long elem)
{ (void)p1; (void)p2; cl4_result_t w = sk_swift_witness(0);
  void (*f)(unsigned long,unsigned long,unsigned long,unsigned long) =
    *(void (**)(unsigned long,unsigned long,unsigned long,unsigned long))((char*)w.lo + 0x120);
  f(w.lo, *(unsigned long*)(w.hi+0x10), *(unsigned long*)(w.hi+0x18), 0); }
/* 0x128 */
/*--------------------------------------------------------------------*/
/* FUN_001bddf8 @ 0x001bddf8   (est. cl4_swift_witness_128)
 * Swift witness dispatch thunk (indirect protocol-witness call). Slot dispatch via FUN_0034b7f4/FUN_0034b798.
 * Confidence: low (indirect witness dispatch).
 * Notes: faithful body as generated; see family comment above. */
void cl4_swift_witness_128(void *p1, void *p2, long elem)
{ (void)p1; (void)p2; cl4_result_t w = sk_swift_witness(0);
  void (*f)(unsigned long,unsigned long,unsigned long,unsigned long) =
    *(void (**)(unsigned long,unsigned long,unsigned long,unsigned long))((char*)w.lo + 0x128);
  f(w.lo, *(unsigned long*)(w.hi+0x10), *(unsigned long*)(w.hi+0x18), 0); }
/* 0x130 */
/*--------------------------------------------------------------------*/
/* FUN_001bde3c @ 0x001bde3c   (est. cl4_swift_witness_130)
 * Swift witness dispatch thunk (indirect protocol-witness call). Slot dispatch via FUN_0034b7f4/FUN_0034b798.
 * Confidence: low (indirect witness dispatch).
 * Notes: faithful body as generated; see family comment above. */
void cl4_swift_witness_130(void *p1, void *p2, long elem)
{ (void)p1; (void)p2; cl4_result_t w = sk_swift_witness(0);
  void (*f)(unsigned long,unsigned long,unsigned long,unsigned long) =
    *(void (**)(unsigned long,unsigned long,unsigned long,unsigned long))((char*)w.lo + 0x130);
  f(w.lo, *(unsigned long*)(w.hi+0x10), *(unsigned long*)(w.hi+0x18), 0); }
/* 0x138 */
/*--------------------------------------------------------------------*/
/* FUN_001bde80 @ 0x001bde80   (est. cl4_swift_witness_138)
 * Swift witness dispatch thunk (indirect protocol-witness call). Slot dispatch via FUN_0034b7f4/FUN_0034b798.
 * Confidence: low (indirect witness dispatch).
 * Notes: faithful body as generated; see family comment above. */
void cl4_swift_witness_138(void *p1, void *p2, long elem)
{ (void)p1; (void)p2; cl4_result_t w = sk_swift_witness(0);
  void (*f)(unsigned long,unsigned long,unsigned long,unsigned long) =
    *(void (**)(unsigned long,unsigned long,unsigned long,unsigned long))((char*)w.lo + 0x138);
  f(w.lo, w.hi, *(unsigned long*)(elem+0x10), *(unsigned long*)(elem+0x18)); }
/* 0x140 (3-arg, low24) */
/*--------------------------------------------------------------------*/
/* FUN_001bdec4 @ 0x001bdec4   (est. cl4_swift_witness_140)
 * Swift witness dispatch thunk (indirect protocol-witness call). Slot dispatch via FUN_0034b7f4/FUN_0034b798.
 * Confidence: low (indirect witness dispatch).
 * Notes: faithful body as generated; see family comment above. */
void cl4_swift_witness_140(void *p1, void *p2, long elem)
{ (void)p1; (void)p2; cl4_result_t w = sk_swift_witness(0);
  void (*f)(unsigned long,unsigned long,unsigned long,unsigned long) =
    *(void (**)(unsigned long,unsigned long,unsigned long,unsigned long))((char*)w.lo + 0x140);
  f(w.lo & 0xffffff, 0, *(unsigned long*)(elem+0x10), *(unsigned long*)(elem+0x18)); }
/* 0x148 */
/*--------------------------------------------------------------------*/
/* FUN_001bdf0c @ 0x001bdf0c   (est. cl4_swift_witness_148)
 * Swift witness dispatch thunk (indirect protocol-witness call). Slot dispatch via FUN_0034b7f4/FUN_0034b798.
 * Confidence: low (indirect witness dispatch).
 * Notes: faithful body as generated; see family comment above. */
void cl4_swift_witness_148(void *p1, void *p2, long elem)
{ (void)p1; (void)p2; cl4_result_t w = sk_swift_witness(0);
  void (*f)(unsigned long,unsigned long,unsigned long,unsigned long) =
    *(void (**)(unsigned long,unsigned long,unsigned long,unsigned long))((char*)w.lo + 0x148);
  f(w.lo & 0xffffffffff, w.hi, *(unsigned long*)(elem+0x10), *(unsigned long*)(elem+0x18)); }
/* 0x150 */
/*--------------------------------------------------------------------*/
/* FUN_001bdf54 @ 0x001bdf54   (est. cl4_swift_witness_150)
 * Swift witness dispatch thunk (indirect protocol-witness call). Slot dispatch via FUN_0034b7f4/FUN_0034b798.
 * Confidence: low (indirect witness dispatch).
 * Notes: faithful body as generated; see family comment above. */
void cl4_swift_witness_150(void *p1, void *p2, long elem)
{ (void)p1; (void)p2; cl4_result_t w = sk_swift_witness(0);
  void (*f)(unsigned long,unsigned long,unsigned long,unsigned long) =
    *(void (**)(unsigned long,unsigned long,unsigned long,unsigned long))((char*)w.lo + 0x150);
  f(w.lo, *(unsigned long*)(w.hi+0x10), *(unsigned long*)(w.hi+0x18), 0); }
/* 0x158 */
/*--------------------------------------------------------------------*/
/* FUN_001bdf98 @ 0x001bdf98   (est. cl4_swift_witness_158)
 * Swift witness dispatch thunk (indirect protocol-witness call). Slot dispatch via FUN_0034b7f4/FUN_0034b798.
 * Confidence: low (indirect witness dispatch).
 * Notes: faithful body as generated; see family comment above. */
void cl4_swift_witness_158(void *p1, void *p2, long elem)
{ (void)p1; (void)p2; cl4_result_t w = sk_swift_witness(0);
  void (*f)(unsigned long,unsigned long,unsigned long,unsigned long) =
    *(void (**)(unsigned long,unsigned long,unsigned long,unsigned long))((char*)w.lo + 0x158);
  f(w.lo, *(unsigned long*)(w.hi+0x10), *(unsigned long*)(w.hi+0x18), 0); }
/* 0x160 (5-arg) */
/*--------------------------------------------------------------------*/
/* FUN_001bdfdc @ 0x001bdfdc   (est. cl4_swift_witness_160)
 * Swift witness dispatch thunk (indirect protocol-witness call). Slot dispatch via FUN_0034b7f4/FUN_0034b798.
 * Confidence: low (indirect witness dispatch).
 * Notes: faithful body as generated; see family comment above. */
void cl4_swift_witness_160(void *p1, void *p2, long elem, void *p4, void *p5)
{ (void)p1; (void)p2; (void)p4; (void)p5; cl4_result_t w = sk_swift_witness(0);
  void (*f)(unsigned long,unsigned long,unsigned long,unsigned long,unsigned long,unsigned long) =
    *(void (**)(unsigned long,unsigned long,unsigned long,unsigned long,unsigned long,unsigned long))((char*)w.lo + 0x160);
  f(w.lo, w.hi, 0, *(unsigned long*)(elem+0x10), 0, *(unsigned long*)(elem+0x18)); }
/* 0x168 (5-arg) */
/*--------------------------------------------------------------------*/
/* FUN_001be024 @ 0x001be024   (est. cl4_swift_witness_168)
 * Swift witness dispatch thunk (indirect protocol-witness call). Slot dispatch via FUN_0034b7f4/FUN_0034b798.
 * Confidence: low (indirect witness dispatch).
 * Notes: faithful body as generated; see family comment above. */
void cl4_swift_witness_168(void *p1, void *p2, long elem, void *p4, void *p5)
{ (void)p1; (void)p2; (void)p4; (void)p5; cl4_result_t w = sk_swift_witness(0);
  void (*f)(unsigned long,unsigned long,unsigned long,unsigned long,unsigned long,unsigned long) =
    *(void (**)(unsigned long,unsigned long,unsigned long,unsigned long,unsigned long,unsigned long))((char*)w.lo + 0x168);
  f(w.lo, w.hi, w.lo, *(unsigned long*)(elem+0x10), 0, *(unsigned long*)(elem+0x18)); }
/* 0x170 */
/*--------------------------------------------------------------------*/
/* FUN_001be06c @ 0x001be06c   (est. cl4_swift_witness_170)
 * Swift witness dispatch thunk (indirect protocol-witness call). Slot dispatch via FUN_0034b7f4/FUN_0034b798.
 * Confidence: low (indirect witness dispatch).
 * Notes: faithful body as generated; see family comment above. */
void cl4_swift_witness_170(void *p1, void *p2, long elem)
{ (void)p1; (void)p2; cl4_result_t w = sk_swift_witness(0);
  void (*f)(unsigned long,unsigned long,unsigned long,unsigned long) =
    *(void (**)(unsigned long,unsigned long,unsigned long,unsigned long))((char*)w.lo + 0x170);
  f(w.lo, *(unsigned long*)(w.hi+0x10), *(unsigned long*)(w.hi+0x18), 0); }
/* 0x178 */
/*--------------------------------------------------------------------*/
/* FUN_001be0b0 @ 0x001be0b0   (est. cl4_swift_witness_178)
 * Swift witness dispatch thunk (indirect protocol-witness call). Slot dispatch via FUN_0034b7f4/FUN_0034b798.
 * Confidence: low (indirect witness dispatch).
 * Notes: faithful body as generated; see family comment above. */
void cl4_swift_witness_178(void *p1, void *p2, long elem)
{ (void)p1; (void)p2; cl4_result_t w = sk_swift_witness(0);
  void (*f)(unsigned long,unsigned long,unsigned long,unsigned long) =
    *(void (**)(unsigned long,unsigned long,unsigned long,unsigned long))((char*)w.lo + 0x178);
  f(w.lo, *(unsigned long*)(w.hi+0x10), *(unsigned long*)(w.hi+0x18), 0); }
/* 0x180 */
/*--------------------------------------------------------------------*/
/* FUN_001be0ec @ 0x001be0ec   (est. cl4_swift_witness_180)
 * Swift witness dispatch thunk (indirect protocol-witness call). Slot dispatch via FUN_0034b7f4/FUN_0034b798.
 * Confidence: low (indirect witness dispatch).
 * Notes: faithful body as generated; see family comment above. */
void cl4_swift_witness_180(void *p1, void *p2, long elem)
{ (void)p1; (void)p2; cl4_result_t w = sk_swift_witness(0);
  void (*f)(unsigned long,unsigned long,unsigned long,unsigned long) =
    *(void (**)(unsigned long,unsigned long,unsigned long,unsigned long))((char*)w.lo + 0x180);
  f(w.lo, *(unsigned long*)(w.hi+0x10), *(unsigned long*)(w.hi+0x18), 0); }

/*--------------------------------------------------------------------*/
/* FUN_001be4b4 @ 0x001be4b4   (est. cl4_swift_witness_160_wrap)
 * Ghidra: void FUN_001be4b4(undefined8, undefined8, undefined8, undefined8, undefined8)
 * Wrapper forwarding (p1,p2,p5,p3,p4) to FUN_001bdfdc (witness slot 0x160).
 * Confidence: low (witness forward).
 */
void cl4_swift_witness_160_wrap(void *p1, void *p2, void *p3, void *p4, void *p5)
{
    cl4_swift_witness_160(p1, p2, (long)p5, p3, p4);
}

/*--------------------------------------------------------------------*/
/* FUN_001be4b8 @ 0x001be4b8   (est. cl4_swift_witness_160_wrap2)
 * Ghidra: void FUN_001be4b8(undefined8, undefined8, undefined8, undefined8, undefined8)
 * Duplicate wrapper to FUN_001bdfdc.
 * Confidence: low (duplicate).
 */
void cl4_swift_witness_160_wrap2(void *p1, void *p2, void *p3, void *p4, void *p5)
{
    cl4_swift_witness_160(p1, p2, (long)p5, p3, p4);
}

/*--------------------------------------------------------------------*/
/* FUN_001be4fc @ 0x001be4fc   (est. cl4_swift_string_append5)
 * Ghidra: void FUN_001be4fc(void)
 * FUN_0034d7a8/FUN_003199ec/FUN_00351d18 then FUN_001be528.
 * Confidence: medium (wrapper chain).
 */
void cl4_swift_string_append5(void)
{
    sk_swift_state(0);   /* FUN_0034d7a8 */
    sk_swift_state2(0);  /* FUN_003199ec */
    sk_swift_state3(0);  /* FUN_00351d18 */
    cl4_swift_string_append6(0);   /* FUN_001be528 */
}

/*--------------------------------------------------------------------*/
/* FUN_001be528 @ 0x001be528   (est. cl4_swift_string_append6)
 * Ghidra: void FUN_001be528(undefined8)
 * FUN_00210bd4(param_1, 0x1c4054).
 * Confidence: low (Swift append via closure 0x1c4054).
 */
void cl4_swift_string_append6(void *a)
{
    sk_swift_state(a, 0x1c4054);   /* FUN_00210bd4(a, 0x1c4054) */
}

/*--------------------------------------------------------------------*/
/* FUN_001be540 @ 0x001be540   (est. cl4_swift_vtable_call0b)
 * Ghidra: void FUN_001be540(void)
 * FUN_0007c198 then indirect call through (x16+0x40).
 * Confidence: low (Swift vtable dispatch, slot 0x40).
 */
void cl4_swift_vtable_call0b(void)
{
    /* FUN_0007c198 / (**(code**)(x16+0x40))() */
    sk_swift_state(0);
}

/*--------------------------------------------------------------------*/
/* FUN_001be578 @ 0x001be578   (est. cl4_swift_vtable_ret48)
 * Ghidra: undefined8 FUN_001be578(undefined8, undefined8)
 * FUN_0007c198, indirect call through (x16+0x48), then FUN_0035a938/
 * FUN_00356304/FUN_0019dfc4/FUN_0035310c/FUN_0036b118; returns param_2.
 * Confidence: low (Swift vtable dispatch + release).
 */
unsigned long cl4_swift_vtable_ret48(void *a, unsigned long b)
{
    (void)a;
    sk_swift_state(0);   /* FUN_0007c198 / (x16+0x48)() */
    unsigned long v = sk_swift_gstate(0);   /* FUN_0035a938 */
    sk_swift_state(v, v);                   /* FUN_00356304 */
    sk_swift_state2(0);                     /* FUN_0019dfc4 */
    sk_swift_state3(0);                     /* FUN_0035310c */
    sk_swift_free(0);                       /* FUN_0036b118 */
    return b;
}

/*--------------------------------------------------------------------*/
/* FUN_001be5d4 @ 0x001be5d4   (est. cl4_swift_witnessB_50)
 * Ghidra: uint FUN_001be5d4(undefined8, undefined8, undefined8, undefined8)
 * Resolves self via FUN_0034b798 and calls witness slot 0x50; returns flag&1.
 * Confidence: low (Swift witness dispatch, slot 0x50).
 */
unsigned int cl4_swift_witnessB_50(void *a, void *b, void *c, void *d)
{
    (void)a; (void)b;
    unsigned long self = sk_swift_witnessB(0);   /* FUN_0034b798 */
    unsigned int r = (*(unsigned int (**)(unsigned long, void *, void *))(0 + 0x50))(self, c, d);
    return r & 1;
}

/*--------------------------------------------------------------------*/
/* FUN_001be614 @ 0x001be614   (est. cl4_swift_witnessB_58)
 * Ghidra: uint FUN_001be614(undefined8, undefined8, undefined8, undefined8)
 * Witness dispatch slot 0x58 via FUN_0034b798; returns flag&1.
 * Confidence: low (Swift witness dispatch, slot 0x58).
 */
unsigned int cl4_swift_witnessB_58(void *a, void *b, void *c, void *d)
{
    (void)a; (void)b;
    unsigned long self = sk_swift_witnessB(0);   /* FUN_0034b798 */
    return (*(unsigned int (**)(unsigned long, void *, void *))(0 + 0x58))(self, c, d) & 1;
}

/*--------------------------------------------------------------------*/
/* FUN_001be654 @ 0x001be654   (est. cl4_swift_witnessB_60)
 * Ghidra: uint FUN_001be654(undefined8, undefined8, undefined8, undefined8)
 * Witness dispatch slot 0x60 via FUN_0034b798; returns flag&1.
 * Confidence: low (Swift witness dispatch, slot 0x60).
 */
unsigned int cl4_swift_witnessB_60(void *a, void *b, void *c, void *d)
{
    (void)a; (void)b;
    unsigned long self = sk_swift_witnessB(0);   /* FUN_0034b798 */
    return (*(unsigned int (**)(unsigned long, void *, void *))(0 + 0x60))(self, c, d) & 1;
}

/*--------------------------------------------------------------------*/
/* Swift witness-table dispatch thunks 0x1be694-0x1befc0.
 * Each resolves self via FUN_0034b798 and calls the witness slot at x16+<off>,
 * passing (self, p3, p4). All confidence low (indirect witness dispatch). */

#define SK_WITNESSB_DISPATCH(name_, addr_, slot_, retflag_) \
void name_(void *p1, void *p2, void *p3, void *p4) \
{ (void)p1; (void)p2; \
  unsigned long self = sk_swift_witnessB(0);   /* FUN_0034b798 */ \
  if (retflag_) { (*(unsigned int (**)(unsigned long, void *, void *))(0 + (slot_)))(self, p3, p4); } \
  else { (*(void (**)(unsigned long, void *, void *))(0 + (slot_)))(self, p3, p4); } }

/*--------------------------------------------------------------------*/
/* FUN_001be694 @ 0x001be694   (est. cl4_swift_witnessB_68)
 * Swift witness dispatch thunk (indirect protocol-witness call). Slot dispatch via FUN_0034b798.
 * Confidence: low (indirect witness dispatch). */
void cl4_swift_witnessB_68(void *p1, void *p2, void *p3, void *p4)
{ (void)p1; (void)p2; unsigned long s = sk_swift_witnessB(0); (*(void (**)(unsigned long,void*,void*))(0+0x68))(s,p3,p4); }
/*--------------------------------------------------------------------*/
/* FUN_001be6d0 @ 0x001be6d0   (est. cl4_swift_witnessB_70)
 * Swift witness dispatch thunk (indirect protocol-witness call). Slot dispatch via FUN_0034b798.
 * Confidence: low (indirect witness dispatch). */
void cl4_swift_witnessB_70(void *p1, void *p2, void *p3, void *p4)
{ (void)p1; (void)p2; unsigned long s = sk_swift_witnessB(0); (*(void (**)(unsigned long,void*,void*))(0+0x70))(s,p3,p4); }
/*--------------------------------------------------------------------*/
/* FUN_001be70c @ 0x001be70c   (est. cl4_swift_witnessB_78)
 * Swift witness dispatch thunk (indirect protocol-witness call). Slot dispatch via FUN_0034b798.
 * Confidence: low (indirect witness dispatch). */
void cl4_swift_witnessB_78(void *p1, void *p2, void *p3, void *p4)
{ (void)p1; (void)p2; unsigned long s = sk_swift_witnessB(0); (*(void (**)(unsigned long,void*,void*))(0+0x78))(s,p3,p4); }
/*--------------------------------------------------------------------*/
/* FUN_001be748 @ 0x001be748   (est. cl4_swift_witnessB_80)
 * Swift witness dispatch thunk (indirect protocol-witness call). Slot dispatch via FUN_0034b798.
 * Confidence: low (indirect witness dispatch). */
void cl4_swift_witnessB_80(void *p1, void *p2, void *p3, void *p4)
{ (void)p1; (void)p2; unsigned long s = sk_swift_witnessB(0); (*(void (**)(unsigned long,void*,void*))(0+0x80))(s,p3,p4); }
/*--------------------------------------------------------------------*/
/* FUN_001be784 @ 0x001be784   (est. cl4_swift_witnessB_88)
 * Swift witness dispatch thunk (indirect protocol-witness call). Slot dispatch via FUN_0034b798.
 * Confidence: low (indirect witness dispatch). */
void cl4_swift_witnessB_88(void *p1, void *p2, void *p3, void *p4)
{ (void)p1; (void)p2; unsigned long s = sk_swift_witnessB(0); (*(void (**)(unsigned long,void*,void*))(0+0x88))(s,p3,p4); }
/*--------------------------------------------------------------------*/
/* FUN_001be7c0 @ 0x001be7c0   (est. cl4_swift_witnessB_90)
 * Swift witness dispatch thunk (indirect protocol-witness call). Slot dispatch via FUN_0034b798.
 * Confidence: low (indirect witness dispatch). */
void cl4_swift_witnessB_90(void *p1, void *p2, void *p3, void *p4)
{ (void)p1; (void)p2; unsigned long s = sk_swift_witnessB(0); (*(void (**)(unsigned long,void*,void*))(0+0x90))(s,p3,p4); }
/*--------------------------------------------------------------------*/
/* FUN_001be7fc @ 0x001be7fc   (est. cl4_swift_witnessB_98)
 * Swift witness dispatch thunk (indirect protocol-witness call). Slot dispatch via FUN_0034b798.
 * Confidence: low (indirect witness dispatch). */
void cl4_swift_witnessB_98(void *p1, void *p2, void *p3, void *p4)
{ (void)p1; (void)p2; unsigned long s = sk_swift_witnessB(0); (*(void (**)(unsigned long,void*,void*))(0+0x98))(s,p3,p4); }
/*--------------------------------------------------------------------*/
/* FUN_001be838 @ 0x001be838   (est. cl4_swift_witnessB_a0)
 * Swift witness dispatch thunk (indirect protocol-witness call). Slot dispatch via FUN_0034b798.
 * Confidence: low (indirect witness dispatch). */
void cl4_swift_witnessB_a0(void *p1, void *p2, void *p3, void *p4)
{ (void)p1; (void)p2; unsigned long s = sk_swift_witnessB(0); (*(void (**)(unsigned long,void*,void*))(0+0xa0))(s,p3,p4); }
/*--------------------------------------------------------------------*/
/* FUN_001be874 @ 0x001be874   (est. cl4_swift_witnessB_a8)
 * Swift witness dispatch thunk (indirect protocol-witness call). Slot dispatch via FUN_0034b798.
 * Confidence: low (indirect witness dispatch). */
void cl4_swift_witnessB_a8(void *p1, void *p2, void *p3, void *p4)
{ (void)p1; (void)p2; unsigned long s = sk_swift_witnessB(0); (*(void (**)(unsigned long,void*,void*))(0+0xa8))(s,p3,p4); }
/*--------------------------------------------------------------------*/
/* FUN_001be8b0 @ 0x001be8b0   (est. cl4_swift_witnessB_b0)
 * Swift witness dispatch thunk (indirect protocol-witness call). Slot dispatch via FUN_0034b798.
 * Confidence: low (indirect witness dispatch). */
void cl4_swift_witnessB_b0(void *p1, void *p2, void *p3, void *p4)
{ (void)p1; (void)p2; unsigned long s = sk_swift_witnessB(0); (*(void (**)(unsigned long,void*,void*))(0+0xb0))(s,p3,p4); }
/*--------------------------------------------------------------------*/
/* FUN_001be8ec @ 0x001be8ec   (est. cl4_swift_witnessB_b8)
 * Swift witness dispatch thunk (indirect protocol-witness call). Slot dispatch via FUN_0034b798.
 * Confidence: low (indirect witness dispatch). */
void cl4_swift_witnessB_b8(void *p1, void *p2, void *p3, void *p4)
{ (void)p1; (void)p2; unsigned long s = sk_swift_witnessB(0); (*(void (**)(unsigned long,void*,void*))(0+0xb8))(s,p3,p4); }
/*--------------------------------------------------------------------*/
/* FUN_001be928 @ 0x001be928   (est. cl4_swift_witnessB_c0)
 * Swift witness dispatch thunk (indirect protocol-witness call). Slot dispatch via FUN_0034b798.
 * Confidence: low (indirect witness dispatch). */
void cl4_swift_witnessB_c0(void *p1, void *p2, void *p3, void *p4)
{ (void)p1; (void)p2; unsigned long s = sk_swift_witnessB(0); (*(void (**)(unsigned long,void*,void*))(0+0xc0))(s,p3,p4); }
/*--------------------------------------------------------------------*/
/* FUN_001be964 @ 0x001be964   (est. cl4_swift_witnessB_c8)
 * Swift witness dispatch thunk (indirect protocol-witness call). Slot dispatch via FUN_0034b798.
 * Confidence: low (indirect witness dispatch). */
void cl4_swift_witnessB_c8(void *p1, void *p2, void *p3, void *p4)
{ (void)p1; (void)p2; unsigned long s = sk_swift_witnessB(0); (*(void (**)(unsigned long,void*,void*))(0+0xc8))(s,p3,p4); }
/*--------------------------------------------------------------------*/
/* FUN_001be9a0 @ 0x001be9a0   (est. cl4_swift_witnessB_d0)
 * Swift witness dispatch thunk (indirect protocol-witness call). Slot dispatch via FUN_0034b798.
 * Confidence: low (indirect witness dispatch). */
void cl4_swift_witnessB_d0(void *p1, void *p2, void *p3, void *p4)
{ (void)p1; (void)p2; unsigned long s = sk_swift_witnessB(0); (*(void (**)(unsigned long,void*,void*))(0+0xd0))(s,p3,p4); }
/*--------------------------------------------------------------------*/
/* FUN_001be9dc @ 0x001be9dc   (est. cl4_swift_witnessB_d8)
 * Swift witness dispatch thunk (indirect protocol-witness call). Slot dispatch via FUN_0034b798.
 * Confidence: low (indirect witness dispatch). */
void cl4_swift_witnessB_d8(void *p1, void *p2, void *p3, void *p4)
{ (void)p1; (void)p2; unsigned long s = sk_swift_witnessB(0); (*(void (**)(unsigned long,void*,void*))(0+0xd8))(s,p3,p4); }
/* 0xe0: 5-arg form via FUN_0034f464 */
/*--------------------------------------------------------------------*/
/* FUN_001bea18 @ 0x001bea18   (est. cl4_swift_witnessB_e0)
 * Swift witness dispatch thunk (indirect protocol-witness call). Slot dispatch via FUN_0034b798.
 * Confidence: low (indirect witness dispatch). */
void cl4_swift_witnessB_e0(void *p1, void *p2, void *p3, void *p4, void *p5)
{ (void)p1; (void)p2; (void)p5;
  cl4_result_t w = sk_swift_witnessF(0);   /* FUN_0034f464(in_x4) */
  (*(void (**)(unsigned long,unsigned long,void*,void*,void*))(0+0xe0))(w.lo, w.hi, p4, p3, p5); }
/*--------------------------------------------------------------------*/
/* FUN_001bea58 @ 0x001bea58   (est. cl4_swift_witnessB_e8)
 * Swift witness dispatch thunk (indirect protocol-witness call). Slot dispatch via FUN_0034b798.
 * Confidence: low (indirect witness dispatch). */
void cl4_swift_witnessB_e8(void *p1, void *p2, void *p3, void *p4)
{ (void)p1; (void)p2; unsigned long s = sk_swift_witnessB(0); (*(void (**)(unsigned long,void*,void*))(0+0xe8))(s,p3,p4); }
/*--------------------------------------------------------------------*/
/* FUN_001bea94 @ 0x001bea94   (est. cl4_swift_witnessB_f0)
 * Swift witness dispatch thunk (indirect protocol-witness call). Slot dispatch via FUN_0034b798.
 * Confidence: low (indirect witness dispatch). */
void cl4_swift_witnessB_f0(void *p1, void *p2, void *p3, void *p4)
{ (void)p1; (void)p2; unsigned long s = sk_swift_witnessB(0); (*(void (**)(unsigned long,void*,void*))(0+0xf0))(s,p3,p4); }
/*--------------------------------------------------------------------*/
/* FUN_001bead0 @ 0x001bead0   (est. cl4_swift_witnessB_f8)
 * Swift witness dispatch thunk (indirect protocol-witness call). Slot dispatch via FUN_0034b798.
 * Confidence: low (indirect witness dispatch). */
void cl4_swift_witnessB_f8(void *p1, void *p2, void *p3, void *p4)
{ (void)p1; (void)p2; unsigned long s = sk_swift_witnessB(0); (*(void (**)(unsigned long,void*,void*))(0+0xf8))(s,p3,p4); }
/*--------------------------------------------------------------------*/
/* FUN_001beb0c @ 0x001beb0c   (est. cl4_swift_witnessB_100)
 * Swift witness dispatch thunk (indirect protocol-witness call). Slot dispatch via FUN_0034b798.
 * Confidence: low (indirect witness dispatch). */
void cl4_swift_witnessB_100(void *p1, void *p2, void *p3, void *p4)
{ (void)p1; (void)p2; unsigned long s = sk_swift_witnessB(0); (*(void (**)(unsigned long,void*,void*))(0+0x100))(s,p3,p4); }
/*--------------------------------------------------------------------*/
/* FUN_001beb54 @ 0x001beb54   (est. cl4_swift_witnessB_108)
 * Swift witness dispatch thunk (indirect protocol-witness call). Slot dispatch via FUN_0034b798.
 * Confidence: low (indirect witness dispatch). */
void cl4_swift_witnessB_108(void *p1, void *p2, void *p3, void *p4)
{ (void)p1; (void)p2; unsigned long s = sk_swift_witnessB(0); (*(void (**)(unsigned long,void*,void*))(0+0x108))(s,p3,p4); }
/*--------------------------------------------------------------------*/
/* FUN_001beb98 @ 0x001beb98   (est. cl4_swift_witnessB_110)
 * Swift witness dispatch thunk (indirect protocol-witness call). Slot dispatch via FUN_0034b798.
 * Confidence: low (indirect witness dispatch). */
void cl4_swift_witnessB_110(void *p1, void *p2, void *p3, void *p4)
{ (void)p1; (void)p2; unsigned long s = sk_swift_witnessB(0); (*(void (**)(unsigned long,void*,void*))(0+0x110))(s,p3,p4); }
/*--------------------------------------------------------------------*/
/* FUN_001bebdc @ 0x001bebdc   (est. cl4_swift_witnessB_118)
 * Swift witness dispatch thunk (indirect protocol-witness call). Slot dispatch via FUN_0034b798.
 * Confidence: low (indirect witness dispatch). */
void cl4_swift_witnessB_118(void *p1, void *p2, void *p3, void *p4)
{ (void)p1; (void)p2; unsigned long s = sk_swift_witnessB(0); (*(void (**)(unsigned long,void*,void*))(0+0x118))(s,p3,p4); }
/*--------------------------------------------------------------------*/
/* FUN_001bec24 @ 0x001bec24   (est. cl4_swift_witnessB_120)
 * Swift witness dispatch thunk (indirect protocol-witness call). Slot dispatch via FUN_0034b798.
 * Confidence: low (indirect witness dispatch). */
void cl4_swift_witnessB_120(void *p1, void *p2, void *p3, void *p4)
{ (void)p1; (void)p2; unsigned long s = sk_swift_witnessB(0); (*(void (**)(unsigned long,void*,void*))(0+0x120))(s,p3,p4); }
/*--------------------------------------------------------------------*/
/* FUN_001bec6c @ 0x001bec6c   (est. cl4_swift_witnessB_128)
 * Swift witness dispatch thunk (indirect protocol-witness call). Slot dispatch via FUN_0034b798.
 * Confidence: low (indirect witness dispatch). */
void cl4_swift_witnessB_128(void *p1, void *p2, void *p3, void *p4)
{ (void)p1; (void)p2; unsigned long s = sk_swift_witnessB(0); (*(void (**)(unsigned long,void*,void*))(0+0x128))(s,p3,p4); }
/*--------------------------------------------------------------------*/
/* FUN_001becb0 @ 0x001becb0   (est. cl4_swift_witnessB_130)
 * Swift witness dispatch thunk (indirect protocol-witness call). Slot dispatch via FUN_0034b798.
 * Confidence: low (indirect witness dispatch). */
void cl4_swift_witnessB_130(void *p1, void *p2, void *p3, void *p4)
{ (void)p1; (void)p2; unsigned long s = sk_swift_witnessB(0); (*(void (**)(unsigned long,void*,void*))(0+0x130))(s,p3,p4); }
/*--------------------------------------------------------------------*/
/* FUN_001bed00 @ 0x001bed00   (est. cl4_swift_witnessB_138)
 * Swift witness dispatch thunk (indirect protocol-witness call). Slot dispatch via FUN_0034b798.
 * Confidence: low (indirect witness dispatch). */
void cl4_swift_witnessB_138(void *p1, void *p2, void *p3, void *p4)
{ (void)p1; (void)p2; unsigned long s = sk_swift_witnessB(0); (*(void (**)(unsigned long,void*,void*))(0+0x138))(s,p3,p4); }
/*--------------------------------------------------------------------*/
/* FUN_001bed44 @ 0x001bed44   (est. cl4_swift_witnessB_140)
 * Swift witness dispatch thunk (indirect protocol-witness call). Slot dispatch via FUN_0034b798.
 * Confidence: low (indirect witness dispatch). */
void cl4_swift_witnessB_140(void *p1, void *p2, void *p3, void *p4)
{ (void)p1; (void)p2; unsigned long s = sk_swift_witnessB(0); (*(void (**)(unsigned long,void*,void*))(0+0x140))(s,p3,p4); }
/*--------------------------------------------------------------------*/
/* FUN_001bed88 @ 0x001bed88   (est. cl4_swift_witnessB_148)
 * Swift witness dispatch thunk (indirect protocol-witness call). Slot dispatch via FUN_0034b798.
 * Confidence: low (indirect witness dispatch). */
void cl4_swift_witnessB_148(void *p1, void *p2, void *p3, void *p4)
{ (void)p1; (void)p2; unsigned long s = sk_swift_witnessB(0); (*(void (**)(unsigned long,void*,void*))(0+0x148))(s,p3,p4); }
/*--------------------------------------------------------------------*/
/* FUN_001bedd0 @ 0x001bedd0   (est. cl4_swift_witnessB_150)
 * Swift witness dispatch thunk (indirect protocol-witness call). Slot dispatch via FUN_0034b798.
 * Confidence: low (indirect witness dispatch). */
void cl4_swift_witnessB_150(void *p1, void *p2, void *p3, void *p4)
{ (void)p1; (void)p2; unsigned long s = sk_swift_witnessB(0); (*(void (**)(unsigned long,void*,void*))(0+0x150))(s,p3,p4); }
/*--------------------------------------------------------------------*/
/* FUN_001bee18 @ 0x001bee18   (est. cl4_swift_witnessB_158)
 * Swift witness dispatch thunk (indirect protocol-witness call). Slot dispatch via FUN_0034b798.
 * Confidence: low (indirect witness dispatch). */
void cl4_swift_witnessB_158(void *p1, void *p2, void *p3, void *p4)
{ (void)p1; (void)p2; unsigned long s = sk_swift_witnessB(0); (*(void (**)(unsigned long,void*,void*))(0+0x158))(s,p3,p4); }
/*--------------------------------------------------------------------*/
/* FUN_001bee5c @ 0x001bee5c   (est. cl4_swift_witnessB_160)
 * Swift witness dispatch thunk (indirect protocol-witness call). Slot dispatch via FUN_0034b798.
 * Confidence: low (indirect witness dispatch). */
void cl4_swift_witnessB_160(void *p1, void *p2, void *p3, void *p4)
{ (void)p1; (void)p2; unsigned long s = sk_swift_witnessB(0); (*(void (**)(unsigned long,void*,void*))(0+0x160))(s,p3,p4); }
/*--------------------------------------------------------------------*/
/* FUN_001beeac @ 0x001beeac   (est. cl4_swift_witnessB_168)
 * Swift witness dispatch thunk (indirect protocol-witness call). Slot dispatch via FUN_0034b798.
 * Confidence: low (indirect witness dispatch). */
void cl4_swift_witnessB_168(void *p1, void *p2, void *p3, void *p4)
{ (void)p1; (void)p2; unsigned long s = sk_swift_witnessB(0); (*(void (**)(unsigned long,void*,void*))(0+0x168))(s,p3,p4); }
/*--------------------------------------------------------------------*/
/* FUN_001beef4 @ 0x001beef4   (est. cl4_swift_witnessB_170)
 * Swift witness dispatch thunk (indirect protocol-witness call). Slot dispatch via FUN_0034b798.
 * Confidence: low (indirect witness dispatch). */
void cl4_swift_witnessB_170(void *p1, void *p2, void *p3, void *p4)
{ (void)p1; (void)p2; unsigned long s = sk_swift_witnessB(0); (*(void (**)(unsigned long,void*,void*))(0+0x170))(s,p3,p4); }
/*--------------------------------------------------------------------*/
/* FUN_001bef3c @ 0x001bef3c   (est. cl4_swift_witnessB_178)
 * Swift witness dispatch thunk (indirect protocol-witness call). Slot dispatch via FUN_0034b798.
 * Confidence: low (indirect witness dispatch). */
void cl4_swift_witnessB_178(void *p1, void *p2, void *p3, void *p4)
{ (void)p1; (void)p2; unsigned long s = sk_swift_witnessB(0); (*(void (**)(unsigned long,void*,void*))(0+0x178))(s,p3,p4); }
/*--------------------------------------------------------------------*/
/* FUN_001bef80 @ 0x001bef80   (est. cl4_swift_witnessB_180)
 * Swift witness dispatch thunk (indirect protocol-witness call). Slot dispatch via FUN_0034b798.
 * Confidence: low (indirect witness dispatch). */
void cl4_swift_witnessB_180(void *p1, void *p2, void *p3, void *p4)
{ (void)p1; (void)p2; unsigned long s = sk_swift_witnessB(0); (*(void (**)(unsigned long,void*,void*))(0+0x180))(s,p3,p4); }
/*--------------------------------------------------------------------*/
/* FUN_001befc0 @ 0x001befc0   (est. cl4_swift_witnessB_188)
 * Swift witness dispatch thunk (indirect protocol-witness call). Slot dispatch via FUN_0034b798.
 * Confidence: low (indirect witness dispatch). */
void cl4_swift_witnessB_188(void *p1, void *p2, void *p3, void *p4)
{ (void)p1; (void)p2; unsigned long s = sk_swift_witnessB(0); (*(void (**)(unsigned long,void*,void*))(0+0x188))(s,p3,p4); }

/*--------------------------------------------------------------------*/
/* Swift witness-forwarding thunks 0x1bf02c-0x1bf64c.
 * Each forwards (param_1, *x20, param_2+0x10, param_2+0x18) to the witnessB
 * dispatch function identified below. All confidence low (witness forward). */

/* 0x1bf02c/030 -> FUN_001be614 (slot 0x58) */
/*--------------------------------------------------------------------*/
/* FUN_001bf02c @ 0x001bf02c   (est. cl4_swift_wf_058_1)
 * Swift witness dispatch thunk (indirect protocol-witness call). Forwards to witnessB dispatch.
 * Confidence: low (indirect witness dispatch). */
unsigned int cl4_swift_wf_058_1(void *p1, long p2)
{ unsigned long *x20 = 0; return cl4_swift_witnessB_58(p1, (void*)*x20, (void*)0, (void*)0); }
/*--------------------------------------------------------------------*/
/* FUN_001bf030 @ 0x001bf030   (est. cl4_swift_wf_058_2)
 * Swift witness dispatch thunk (indirect protocol-witness call). Forwards to witnessB dispatch.
 * Confidence: low (indirect witness dispatch). */
unsigned int cl4_swift_wf_058_2(void *p1, long p2)
{ unsigned long *x20 = 0; return cl4_swift_witnessB_58(p1, (void*)*x20, (void*)0, (void*)0); }
/* 0x1bf054/058 -> FUN_001be654 (slot 0x60) */
/*--------------------------------------------------------------------*/
/* FUN_001bf054 @ 0x001bf054   (est. cl4_swift_wf_060_1)
 * Swift witness dispatch thunk (indirect protocol-witness call). Forwards to witnessB dispatch.
 * Confidence: low (indirect witness dispatch). */
unsigned int cl4_swift_wf_060_1(void *p1, long p2)
{ unsigned long *x20 = 0; return cl4_swift_witnessB_60(p1, (void*)*x20, (void*)0, (void*)0); }
/*--------------------------------------------------------------------*/
/* FUN_001bf058 @ 0x001bf058   (est. cl4_swift_wf_060_2)
 * Swift witness dispatch thunk (indirect protocol-witness call). Forwards to witnessB dispatch.
 * Confidence: low (indirect witness dispatch). */
unsigned int cl4_swift_wf_060_2(void *p1, long p2)
{ unsigned long *x20 = 0; return cl4_swift_witnessB_60(p1, (void*)*x20, (void*)0, (void*)0); }
/* 0x1bf07c/080 -> FUN_001be694 (slot 0x68) */
/*--------------------------------------------------------------------*/
/* FUN_001bf07c @ 0x001bf07c   (est. cl4_swift_wf_068_1)
 * Swift witness dispatch thunk (indirect protocol-witness call). Forwards to witnessB dispatch.
 * Confidence: low (indirect witness dispatch). */
void cl4_swift_wf_068_1(void *p1, long p2)
{ unsigned long *x20 = 0; cl4_swift_witnessB_68(p1, (void*)*x20, (void*)0, (void*)0); }
/*--------------------------------------------------------------------*/
/* FUN_001bf080 @ 0x001bf080   (est. cl4_swift_wf_068_2)
 * Swift witness dispatch thunk (indirect protocol-witness call). Forwards to witnessB dispatch.
 * Confidence: low (indirect witness dispatch). */
void cl4_swift_wf_068_2(void *p1, long p2)
{ unsigned long *x20 = 0; cl4_swift_witnessB_68(p1, (void*)*x20, (void*)0, (void*)0); }
/* 0x1bf0a0/0a4 -> FUN_001be6d0 (slot 0x70) */
/*--------------------------------------------------------------------*/
/* FUN_001bf0a0 @ 0x001bf0a0   (est. cl4_swift_wf_070_1)
 * Swift witness dispatch thunk (indirect protocol-witness call). Forwards to witnessB dispatch.
 * Confidence: low (indirect witness dispatch). */
void cl4_swift_wf_070_1(void *p1, long p2)
{ unsigned long *x20 = 0; cl4_swift_witnessB_70(p1, (void*)*x20, (void*)0, (void*)0); }
/*--------------------------------------------------------------------*/
/* FUN_001bf0a4 @ 0x001bf0a4   (est. cl4_swift_wf_070_2)
 * Swift witness dispatch thunk (indirect protocol-witness call). Forwards to witnessB dispatch.
 * Confidence: low (indirect witness dispatch). */
void cl4_swift_wf_070_2(void *p1, long p2)
{ unsigned long *x20 = 0; cl4_swift_witnessB_70(p1, (void*)*x20, (void*)0, (void*)0); }
/* 0x1bf0c4/c8 -> FUN_001be70c (slot 0x78) */
/*--------------------------------------------------------------------*/
/* FUN_001bf0c4 @ 0x001bf0c4   (est. cl4_swift_wf_078_1)
 * Swift witness dispatch thunk (indirect protocol-witness call). Forwards to witnessB dispatch.
 * Confidence: low (indirect witness dispatch). */
void cl4_swift_wf_078_1(void *p1, long p2)
{ unsigned long *x20 = 0; cl4_swift_witnessB_78(p1, (void*)*x20, (void*)0, (void*)0); }
/*--------------------------------------------------------------------*/
/* FUN_001bf0c8 @ 0x001bf0c8   (est. cl4_swift_wf_078_2)
 * Swift witness dispatch thunk (indirect protocol-witness call). Forwards to witnessB dispatch.
 * Confidence: low (indirect witness dispatch). */
void cl4_swift_wf_078_2(void *p1, long p2)
{ unsigned long *x20 = 0; cl4_swift_witnessB_78(p1, (void*)*x20, (void*)0, (void*)0); }
/* 0x1bf0e8/0ec -> FUN_001be748 (slot 0x80) */
/*--------------------------------------------------------------------*/
/* FUN_001bf0e8 @ 0x001bf0e8   (est. cl4_swift_wf_080_1)
 * Swift witness dispatch thunk (indirect protocol-witness call). Forwards to witnessB dispatch.
 * Confidence: low (indirect witness dispatch). */
void cl4_swift_wf_080_1(void *p1, long p2)
{ unsigned long *x20 = 0; cl4_swift_witnessB_80(p1, (void*)*x20, (void*)0, (void*)0); }
/*--------------------------------------------------------------------*/
/* FUN_001bf0ec @ 0x001bf0ec   (est. cl4_swift_wf_080_2)
 * Swift witness dispatch thunk (indirect protocol-witness call). Forwards to witnessB dispatch.
 * Confidence: low (indirect witness dispatch). */
void cl4_swift_wf_080_2(void *p1, long p2)
{ unsigned long *x20 = 0; cl4_swift_witnessB_80(p1, (void*)*x20, (void*)0, (void*)0); }
/* 0x1bf10c/110 -> FUN_001be784 (slot 0x88) */
/*--------------------------------------------------------------------*/
/* FUN_001bf10c @ 0x001bf10c   (est. cl4_swift_wf_088_1)
 * Swift witness dispatch thunk (indirect protocol-witness call). Forwards to witnessB dispatch.
 * Confidence: low (indirect witness dispatch). */
void cl4_swift_wf_088_1(void *p1, long p2)
{ unsigned long *x20 = 0; cl4_swift_witnessB_88(p1, (void*)*x20, (void*)0, (void*)0); }
/*--------------------------------------------------------------------*/
/* FUN_001bf110 @ 0x001bf110   (est. cl4_swift_wf_088_2)
 * Swift witness dispatch thunk (indirect protocol-witness call). Forwards to witnessB dispatch.
 * Confidence: low (indirect witness dispatch). */
void cl4_swift_wf_088_2(void *p1, long p2)
{ unsigned long *x20 = 0; cl4_swift_witnessB_88(p1, (void*)*x20, (void*)0, (void*)0); }
/* 0x1bf130/134 -> FUN_001be7c0 (slot 0x90) */
/*--------------------------------------------------------------------*/
/* FUN_001bf130 @ 0x001bf130   (est. cl4_swift_wf_090_1)
 * Swift witness dispatch thunk (indirect protocol-witness call). Forwards to witnessB dispatch.
 * Confidence: low (indirect witness dispatch). */
void cl4_swift_wf_090_1(void *p1, long p2)
{ unsigned long *x20 = 0; cl4_swift_witnessB_90(p1, (void*)*x20, (void*)0, (void*)0); }
/*--------------------------------------------------------------------*/
/* FUN_001bf134 @ 0x001bf134   (est. cl4_swift_wf_090_2)
 * Swift witness dispatch thunk (indirect protocol-witness call). Forwards to witnessB dispatch.
 * Confidence: low (indirect witness dispatch). */
void cl4_swift_wf_090_2(void *p1, long p2)
{ unsigned long *x20 = 0; cl4_swift_witnessB_90(p1, (void*)*x20, (void*)0, (void*)0); }
/* 0x1bf154/158 -> FUN_001be7fc (slot 0x98) */
/*--------------------------------------------------------------------*/
/* FUN_001bf154 @ 0x001bf154   (est. cl4_swift_wf_098_1)
 * Swift witness dispatch thunk (indirect protocol-witness call). Forwards to witnessB dispatch.
 * Confidence: low (indirect witness dispatch). */
void cl4_swift_wf_098_1(void *p1, long p2)
{ unsigned long *x20 = 0; cl4_swift_witnessB_98(p1, (void*)*x20, (void*)0, (void*)0); }
/*--------------------------------------------------------------------*/
/* FUN_001bf158 @ 0x001bf158   (est. cl4_swift_wf_098_2)
 * Swift witness dispatch thunk (indirect protocol-witness call). Forwards to witnessB dispatch.
 * Confidence: low (indirect witness dispatch). */
void cl4_swift_wf_098_2(void *p1, long p2)
{ unsigned long *x20 = 0; cl4_swift_witnessB_98(p1, (void*)*x20, (void*)0, (void*)0); }
/* 0x1bf178/17c -> FUN_001be838 (slot 0xa0) */
/*--------------------------------------------------------------------*/
/* FUN_001bf178 @ 0x001bf178   (est. cl4_swift_wf_0a0_1)
 * Swift witness dispatch thunk (indirect protocol-witness call). Forwards to witnessB dispatch.
 * Confidence: low (indirect witness dispatch). */
void cl4_swift_wf_0a0_1(void *p1, long p2)
{ unsigned long *x20 = 0; cl4_swift_witnessB_a0(p1, (void*)*x20, (void*)0, (void*)0); }
/*--------------------------------------------------------------------*/
/* FUN_001bf17c @ 0x001bf17c   (est. cl4_swift_wf_0a0_2)
 * Swift witness dispatch thunk (indirect protocol-witness call). Forwards to witnessB dispatch.
 * Confidence: low (indirect witness dispatch). */
void cl4_swift_wf_0a0_2(void *p1, long p2)
{ unsigned long *x20 = 0; cl4_swift_witnessB_a0(p1, (void*)*x20, (void*)0, (void*)0); }
/* 0x1bf19c/1a0 -> FUN_001be874 (slot 0xa8) */
/*--------------------------------------------------------------------*/
/* FUN_001bf19c @ 0x001bf19c   (est. cl4_swift_wf_0a8_1)
 * Swift witness dispatch thunk (indirect protocol-witness call). Forwards to witnessB dispatch.
 * Confidence: low (indirect witness dispatch). */
void cl4_swift_wf_0a8_1(void *p1, long p2)
{ unsigned long *x20 = 0; cl4_swift_witnessB_a8(p1, (void*)*x20, (void*)0, (void*)0); }
/*--------------------------------------------------------------------*/
/* FUN_001bf1a0 @ 0x001bf1a0   (est. cl4_swift_wf_0a8_2)
 * Swift witness dispatch thunk (indirect protocol-witness call). Forwards to witnessB dispatch.
 * Confidence: low (indirect witness dispatch). */
void cl4_swift_wf_0a8_2(void *p1, long p2)
{ unsigned long *x20 = 0; cl4_swift_witnessB_a8(p1, (void*)*x20, (void*)0, (void*)0); }
/* 0x1bf1c0/1c4 -> FUN_001be8b0 (slot 0xb0) */
/*--------------------------------------------------------------------*/
/* FUN_001bf1c0 @ 0x001bf1c0   (est. cl4_swift_wf_0b0_1)
 * Swift witness dispatch thunk (indirect protocol-witness call). Forwards to witnessB dispatch.
 * Confidence: low (indirect witness dispatch). */
void cl4_swift_wf_0b0_1(void *p1, long p2)
{ unsigned long *x20 = 0; cl4_swift_witnessB_b0(p1, (void*)*x20, (void*)0, (void*)0); }
/*--------------------------------------------------------------------*/
/* FUN_001bf1c4 @ 0x001bf1c4   (est. cl4_swift_wf_0b0_2)
 * Swift witness dispatch thunk (indirect protocol-witness call). Forwards to witnessB dispatch.
 * Confidence: low (indirect witness dispatch). */
void cl4_swift_wf_0b0_2(void *p1, long p2)
{ unsigned long *x20 = 0; cl4_swift_witnessB_b0(p1, (void*)*x20, (void*)0, (void*)0); }
/* 0x1bf1e4/1e8 -> FUN_001be8ec (slot 0xb8) */
/*--------------------------------------------------------------------*/
/* FUN_001bf1e4 @ 0x001bf1e4   (est. cl4_swift_wf_0b8_1)
 * Swift witness dispatch thunk (indirect protocol-witness call). Forwards to witnessB dispatch.
 * Confidence: low (indirect witness dispatch). */
void cl4_swift_wf_0b8_1(void *p1, long p2)
{ unsigned long *x20 = 0; cl4_swift_witnessB_b8(p1, (void*)*x20, (void*)0, (void*)0); }
/*--------------------------------------------------------------------*/
/* FUN_001bf1e8 @ 0x001bf1e8   (est. cl4_swift_wf_0b8_2)
 * Swift witness dispatch thunk (indirect protocol-witness call). Forwards to witnessB dispatch.
 * Confidence: low (indirect witness dispatch). */
void cl4_swift_wf_0b8_2(void *p1, long p2)
{ unsigned long *x20 = 0; cl4_swift_witnessB_b8(p1, (void*)*x20, (void*)0, (void*)0); }
/* 0x1bf208/20c -> FUN_001be928 (slot 0xc0) */
/*--------------------------------------------------------------------*/
/* FUN_001bf208 @ 0x001bf208   (est. cl4_swift_wf_0c0_1)
 * Swift witness dispatch thunk (indirect protocol-witness call). Forwards to witnessB dispatch.
 * Confidence: low (indirect witness dispatch). */
void cl4_swift_wf_0c0_1(void *p1, long p2)
{ unsigned long *x20 = 0; cl4_swift_witnessB_c0(p1, (void*)*x20, (void*)0, (void*)0); }
/*--------------------------------------------------------------------*/
/* FUN_001bf20c @ 0x001bf20c   (est. cl4_swift_wf_0c0_2)
 * Swift witness dispatch thunk (indirect protocol-witness call). Forwards to witnessB dispatch.
 * Confidence: low (indirect witness dispatch). */
void cl4_swift_wf_0c0_2(void *p1, long p2)
{ unsigned long *x20 = 0; cl4_swift_witnessB_c0(p1, (void*)*x20, (void*)0, (void*)0); }
/* 0x1bf22c/230 -> FUN_001be964 (slot 0xc8) */
/*--------------------------------------------------------------------*/
/* FUN_001bf22c @ 0x001bf22c   (est. cl4_swift_wf_0c8_1)
 * Swift witness dispatch thunk (indirect protocol-witness call). Forwards to witnessB dispatch.
 * Confidence: low (indirect witness dispatch). */
void cl4_swift_wf_0c8_1(void *p1, long p2)
{ unsigned long *x20 = 0; cl4_swift_witnessB_c8(p1, (void*)*x20, (void*)0, (void*)0); }
/*--------------------------------------------------------------------*/
/* FUN_001bf230 @ 0x001bf230   (est. cl4_swift_wf_0c8_2)
 * Swift witness dispatch thunk (indirect protocol-witness call). Forwards to witnessB dispatch.
 * Confidence: low (indirect witness dispatch). */
void cl4_swift_wf_0c8_2(void *p1, long p2)
{ unsigned long *x20 = 0; cl4_swift_witnessB_c8(p1, (void*)*x20, (void*)0, (void*)0); }
/* 0x1bf250/254 -> FUN_001be9a0 (slot 0xd0) */
/*--------------------------------------------------------------------*/
/* FUN_001bf250 @ 0x001bf250   (est. cl4_swift_wf_0d0_1)
 * Swift witness dispatch thunk (indirect protocol-witness call). Forwards to witnessB dispatch.
 * Confidence: low (indirect witness dispatch). */
void cl4_swift_wf_0d0_1(void *p1, long p2)
{ unsigned long *x20 = 0; cl4_swift_witnessB_d0(p1, (void*)*x20, (void*)0, (void*)0); }
/*--------------------------------------------------------------------*/
/* FUN_001bf254 @ 0x001bf254   (est. cl4_swift_wf_0d0_2)
 * Swift witness dispatch thunk (indirect protocol-witness call). Forwards to witnessB dispatch.
 * Confidence: low (indirect witness dispatch). */
void cl4_swift_wf_0d0_2(void *p1, long p2)
{ unsigned long *x20 = 0; cl4_swift_witnessB_d0(p1, (void*)*x20, (void*)0, (void*)0); }
/* 0x1bf274/278 -> FUN_001be9dc (slot 0xd8) */
/*--------------------------------------------------------------------*/
/* FUN_001bf274 @ 0x001bf274   (est. cl4_swift_wf_0d8_1)
 * Swift witness dispatch thunk (indirect protocol-witness call). Forwards to witnessB dispatch.
 * Confidence: low (indirect witness dispatch). */
void cl4_swift_wf_0d8_1(void *p1, long p2)
{ unsigned long *x20 = 0; cl4_swift_witnessB_d8(p1, (void*)*x20, (void*)0, (void*)0); }
/*--------------------------------------------------------------------*/
/* FUN_001bf278 @ 0x001bf278   (est. cl4_swift_wf_0d8_2)
 * Swift witness dispatch thunk (indirect protocol-witness call). Forwards to witnessB dispatch.
 * Confidence: low (indirect witness dispatch). */
void cl4_swift_wf_0d8_2(void *p1, long p2)
{ unsigned long *x20 = 0; cl4_swift_witnessB_d8(p1, (void*)*x20, (void*)0, (void*)0); }
/* 0x1bf298/29c -> FUN_001bea18 (slot 0xe0, 5-arg) */
/*--------------------------------------------------------------------*/
/* FUN_001bf298 @ 0x001bf298   (est. cl4_swift_wf_0e0_1)
 * Swift witness dispatch thunk (indirect protocol-witness call). Forwards to witnessB dispatch.
 * Confidence: low (indirect witness dispatch). */
void cl4_swift_wf_0e0_1(void *p1, long p2)
{ unsigned long *x20 = 0; cl4_swift_witnessB_e0(p1, (void*)*x20, (void*)0, (void*)0, (void*)0); }
/*--------------------------------------------------------------------*/
/* FUN_001bf29c @ 0x001bf29c   (est. cl4_swift_wf_0e0_2)
 * Swift witness dispatch thunk (indirect protocol-witness call). Forwards to witnessB dispatch.
 * Confidence: low (indirect witness dispatch). */
void cl4_swift_wf_0e0_2(void *p1, long p2)
{ unsigned long *x20 = 0; cl4_swift_witnessB_e0(p1, (void*)*x20, (void*)0, (void*)0, (void*)0); }
/* 0x1bf2c4/c8 -> FUN_001bea58 (slot 0xe8) */
/*--------------------------------------------------------------------*/
/* FUN_001bf2c4 @ 0x001bf2c4   (est. cl4_swift_wf_0e8_1)
 * Swift witness dispatch thunk (indirect protocol-witness call). Forwards to witnessB dispatch.
 * Confidence: low (indirect witness dispatch). */
void cl4_swift_wf_0e8_1(void *p1, long p2)
{ unsigned long *x20 = 0; cl4_swift_witnessB_e8(p1, (void*)*x20, (void*)0, (void*)0); }
/*--------------------------------------------------------------------*/
/* FUN_001bf2c8 @ 0x001bf2c8   (est. cl4_swift_wf_0e8_2)
 * Swift witness dispatch thunk (indirect protocol-witness call). Forwards to witnessB dispatch.
 * Confidence: low (indirect witness dispatch). */
void cl4_swift_wf_0e8_2(void *p1, long p2)
{ unsigned long *x20 = 0; cl4_swift_witnessB_e8(p1, (void*)*x20, (void*)0, (void*)0); }
/* 0x1bf2e8/2ec -> FUN_001bea94 (slot 0xf0) */
/*--------------------------------------------------------------------*/
/* FUN_001bf2e8 @ 0x001bf2e8   (est. cl4_swift_wf_0f0_1)
 * Swift witness dispatch thunk (indirect protocol-witness call). Forwards to witnessB dispatch.
 * Confidence: low (indirect witness dispatch). */
void cl4_swift_wf_0f0_1(void *p1, long p2)
{ unsigned long *x20 = 0; cl4_swift_witnessB_f0(p1, (void*)*x20, (void*)0, (void*)0); }
/*--------------------------------------------------------------------*/
/* FUN_001bf2ec @ 0x001bf2ec   (est. cl4_swift_wf_0f0_2)
 * Swift witness dispatch thunk (indirect protocol-witness call). Forwards to witnessB dispatch.
 * Confidence: low (indirect witness dispatch). */
void cl4_swift_wf_0f0_2(void *p1, long p2)
{ unsigned long *x20 = 0; cl4_swift_witnessB_f0(p1, (void*)*x20, (void*)0, (void*)0); }
/* 0x1bf30c/310 -> FUN_001bead0 (slot 0xf8) */
/*--------------------------------------------------------------------*/
/* FUN_001bf30c @ 0x001bf30c   (est. cl4_swift_wf_0f8_1)
 * Swift witness dispatch thunk (indirect protocol-witness call). Forwards to witnessB dispatch.
 * Confidence: low (indirect witness dispatch). */
void cl4_swift_wf_0f8_1(void *p1, long p2)
{ unsigned long *x20 = 0; cl4_swift_witnessB_f8(p1, (void*)*x20, (void*)0, (void*)0); }
/*--------------------------------------------------------------------*/
/* FUN_001bf310 @ 0x001bf310   (est. cl4_swift_wf_0f8_2)
 * Swift witness dispatch thunk (indirect protocol-witness call). Forwards to witnessB dispatch.
 * Confidence: low (indirect witness dispatch). */
void cl4_swift_wf_0f8_2(void *p1, long p2)
{ unsigned long *x20 = 0; cl4_swift_witnessB_f8(p1, (void*)*x20, (void*)0, (void*)0); }
/* 0x1bf35c/360 -> FUN_001beb54 (slot 0x108) */
/*--------------------------------------------------------------------*/
/* FUN_001bf35c @ 0x001bf35c   (est. cl4_swift_wf_108_1)
 * Swift witness dispatch thunk (indirect protocol-witness call). Forwards to witnessB dispatch.
 * Confidence: low (indirect witness dispatch). */
void cl4_swift_wf_108_1(void *p1, long p2)
{ unsigned long *x20 = 0; cl4_swift_witnessB_108(p1, (void*)*x20, (void*)0, (void*)0); }
/*--------------------------------------------------------------------*/
/* FUN_001bf360 @ 0x001bf360   (est. cl4_swift_wf_108_2)
 * Swift witness dispatch thunk (indirect protocol-witness call). Forwards to witnessB dispatch.
 * Confidence: low (indirect witness dispatch). */
void cl4_swift_wf_108_2(void *p1, long p2)
{ unsigned long *x20 = 0; cl4_swift_witnessB_108(p1, (void*)*x20, (void*)0, (void*)0); }
/* 0x1bf380/384 -> FUN_001beb98 (slot 0x110) */
/*--------------------------------------------------------------------*/
/* FUN_001bf380 @ 0x001bf380   (est. cl4_swift_wf_110_1)
 * Swift witness dispatch thunk (indirect protocol-witness call). Forwards to witnessB dispatch.
 * Confidence: low (indirect witness dispatch). */
void cl4_swift_wf_110_1(void *p1, long p2)
{ unsigned long *x20 = 0; cl4_swift_witnessB_110(p1, (void*)*x20, (void*)0, (void*)0); }
/*--------------------------------------------------------------------*/
/* FUN_001bf384 @ 0x001bf384   (est. cl4_swift_wf_110_2)
 * Swift witness dispatch thunk (indirect protocol-witness call). Forwards to witnessB dispatch.
 * Confidence: low (indirect witness dispatch). */
void cl4_swift_wf_110_2(void *p1, long p2)
{ unsigned long *x20 = 0; cl4_swift_witnessB_110(p1, (void*)*x20, (void*)0, (void*)0); }
/* 0x1bf3fc/400 -> FUN_001bec6c (slot 0x128) */
/*--------------------------------------------------------------------*/
/* FUN_001bf3fc @ 0x001bf3fc   (est. cl4_swift_wf_128_1)
 * Swift witness dispatch thunk (indirect protocol-witness call). Forwards to witnessB dispatch.
 * Confidence: low (indirect witness dispatch). */
void cl4_swift_wf_128_1(void *p1, long p2)
{ unsigned long *x20 = 0; cl4_swift_witnessB_128(p1, (void*)*x20, (void*)0, (void*)0); }
/*--------------------------------------------------------------------*/
/* FUN_001bf400 @ 0x001bf400   (est. cl4_swift_wf_128_2)
 * Swift witness dispatch thunk (indirect protocol-witness call). Forwards to witnessB dispatch.
 * Confidence: low (indirect witness dispatch). */
void cl4_swift_wf_128_2(void *p1, long p2)
{ unsigned long *x20 = 0; cl4_swift_witnessB_128(p1, (void*)*x20, (void*)0, (void*)0); }
/* 0x1bf44c/450 -> FUN_001bed00 (slot 0x138) */
/*--------------------------------------------------------------------*/
/* FUN_001bf44c @ 0x001bf44c   (est. cl4_swift_wf_138_1)
 * Swift witness dispatch thunk (indirect protocol-witness call). Forwards to witnessB dispatch.
 * Confidence: low (indirect witness dispatch). */
void cl4_swift_wf_138_1(void *p1, long p2)
{ unsigned long *x20 = 0; cl4_swift_witnessB_138(p1, (void*)*x20, (void*)0, (void*)0); }
/*--------------------------------------------------------------------*/
/* FUN_001bf450 @ 0x001bf450   (est. cl4_swift_wf_138_2)
 * Swift witness dispatch thunk (indirect protocol-witness call). Forwards to witnessB dispatch.
 * Confidence: low (indirect witness dispatch). */
void cl4_swift_wf_138_2(void *p1, long p2)
{ unsigned long *x20 = 0; cl4_swift_witnessB_138(p1, (void*)*x20, (void*)0, (void*)0); }
/* 0x1bf470/474 -> FUN_001bed44 (slot 0x140) */
/*--------------------------------------------------------------------*/
/* FUN_001bf470 @ 0x001bf470   (est. cl4_swift_wf_140_1)
 * Swift witness dispatch thunk (indirect protocol-witness call). Forwards to witnessB dispatch.
 * Confidence: low (indirect witness dispatch). */
void cl4_swift_wf_140_1(void *p1, long p2)
{ unsigned long *x20 = 0; cl4_swift_witnessB_140(p1, (void*)*x20, (void*)0, (void*)0); }
/*--------------------------------------------------------------------*/
/* FUN_001bf474 @ 0x001bf474   (est. cl4_swift_wf_140_2)
 * Swift witness dispatch thunk (indirect protocol-witness call). Forwards to witnessB dispatch.
 * Confidence: low (indirect witness dispatch). */
void cl4_swift_wf_140_2(void *p1, long p2)
{ unsigned long *x20 = 0; cl4_swift_witnessB_140(p1, (void*)*x20, (void*)0, (void*)0); }
/* 0x1bf534/538 -> FUN_001bee18 (slot 0x158) */
/*--------------------------------------------------------------------*/
/* FUN_001bf534 @ 0x001bf534   (est. cl4_swift_wf_158_1)
 * Swift witness dispatch thunk (indirect protocol-witness call). Forwards to witnessB dispatch.
 * Confidence: low (indirect witness dispatch). */
void cl4_swift_wf_158_1(void *p1, long p2)
{ unsigned long *x20 = 0; cl4_swift_witnessB_158(p1, (void*)*x20, (void*)0, (void*)0); }
/*--------------------------------------------------------------------*/
/* FUN_001bf538 @ 0x001bf538   (est. cl4_swift_wf_158_2)
 * Swift witness dispatch thunk (indirect protocol-witness call). Forwards to witnessB dispatch.
 * Confidence: low (indirect witness dispatch). */
void cl4_swift_wf_158_2(void *p1, long p2)
{ unsigned long *x20 = 0; cl4_swift_witnessB_158(p1, (void*)*x20, (void*)0, (void*)0); }
/* 0x1bf5b0/b4 -> FUN_001beeac (slot 0x168) */
/*--------------------------------------------------------------------*/
/* FUN_001bf5b0 @ 0x001bf5b0   (est. cl4_swift_wf_168_1)
 * Swift witness dispatch thunk (indirect protocol-witness call). Forwards to witnessB dispatch.
 * Confidence: low (indirect witness dispatch). */
void cl4_swift_wf_168_1(void *p1, long p2)
{ unsigned long *x20 = 0; cl4_swift_witnessB_168(p1, (void*)*x20, (void*)0, (void*)0); }
/*--------------------------------------------------------------------*/
/* FUN_001bf5b4 @ 0x001bf5b4   (est. cl4_swift_wf_168_2)
 * Swift witness dispatch thunk (indirect protocol-witness call). Forwards to witnessB dispatch.
 * Confidence: low (indirect witness dispatch). */
void cl4_swift_wf_168_2(void *p1, long p2)
{ unsigned long *x20 = 0; cl4_swift_witnessB_168(p1, (void*)*x20, (void*)0, (void*)0); }
/* 0x1bf5dc/5e0 -> FUN_001beef4 (slot 0x170) */
/*--------------------------------------------------------------------*/
/* FUN_001bf5dc @ 0x001bf5dc   (est. cl4_swift_wf_170_1)
 * Swift witness dispatch thunk (indirect protocol-witness call). Forwards to witnessB dispatch.
 * Confidence: low (indirect witness dispatch). */
void cl4_swift_wf_170_1(void *p1, long p2)
{ unsigned long *x20 = 0; cl4_swift_witnessB_170(p1, (void*)*x20, (void*)0, (void*)0); }
/*--------------------------------------------------------------------*/
/* FUN_001bf5e0 @ 0x001bf5e0   (est. cl4_swift_wf_170_2)
 * Swift witness dispatch thunk (indirect protocol-witness call). Forwards to witnessB dispatch.
 * Confidence: low (indirect witness dispatch). */
void cl4_swift_wf_170_2(void *p1, long p2)
{ unsigned long *x20 = 0; cl4_swift_witnessB_170(p1, (void*)*x20, (void*)0, (void*)0); }
/* 0x1bf608/60c -> FUN_001bef3c (slot 0x178) */
/*--------------------------------------------------------------------*/
/* FUN_001bf608 @ 0x001bf608   (est. cl4_swift_wf_178_1)
 * Swift witness dispatch thunk (indirect protocol-witness call). Forwards to witnessB dispatch.
 * Confidence: low (indirect witness dispatch). */
void cl4_swift_wf_178_1(void *p1, long p2)
{ unsigned long *x20 = 0; cl4_swift_witnessB_178(p1, (void*)*x20, (void*)0, (void*)0); }
/*--------------------------------------------------------------------*/
/* FUN_001bf60c @ 0x001bf60c   (est. cl4_swift_wf_178_2)
 * Swift witness dispatch thunk (indirect protocol-witness call). Forwards to witnessB dispatch.
 * Confidence: low (indirect witness dispatch). */
void cl4_swift_wf_178_2(void *p1, long p2)
{ unsigned long *x20 = 0; cl4_swift_witnessB_178(p1, (void*)*x20, (void*)0, (void*)0); }
/* 0x1bf648/64c -> FUN_001befc0 (slot 0x188) */
/*--------------------------------------------------------------------*/
/* FUN_001bf648 @ 0x001bf648   (est. cl4_swift_wf_188_1)
 * Swift witness dispatch thunk (indirect protocol-witness call). Forwards to witnessB dispatch.
 * Confidence: low (indirect witness dispatch). */
void cl4_swift_wf_188_1(void *p1, long p2)
{ unsigned long *x20 = 0; cl4_swift_witnessB_188(p1, (void*)*x20, (void*)0, (void*)0); }
/*--------------------------------------------------------------------*/
/* FUN_001bf64c @ 0x001bf64c   (est. cl4_swift_wf_188_2)
 * Swift witness dispatch thunk (indirect protocol-witness call). Forwards to witnessB dispatch.
 * Confidence: low (indirect witness dispatch). */
void cl4_swift_wf_188_2(void *p1, long p2)
{ unsigned long *x20 = 0; cl4_swift_witnessB_188(p1, (void*)*x20, (void*)0, (void*)0); }

/*--------------------------------------------------------------------*/
/* FUN_001bf4c0 @ 0x001bf4c0   (est. cl4_swift_witness_ret24)
 * Ghidra: uint FUN_001bf4c0(void)
 * FUN_003554b0 then returns (indirect result)&0xffffff.
 * Confidence: low (Swift witness getter, low 24 bits).
 */
unsigned int cl4_swift_witness_ret24(void)
{
    return sk_swift_flag(0) & 0xffffff;   /* FUN_003554b0 / (*extraout_x8)() */
}

/*--------------------------------------------------------------------*/
/* FUN_001bf510 @ 0x001bf510   (est. cl4_swift_witness_ret40)
 * Ghidra: ulong FUN_001bf510(void)
 * FUN_003554b0 then returns (indirect result)&0xffffffffff.
 * Confidence: low (Swift witness getter, low 40 bits).
 */
unsigned long cl4_swift_witness_ret40(void)
{
    return sk_swift_flag(0) & 0xffffffffff;   /* FUN_003554b0 */
}

/*--------------------------------------------------------------------*/
/* FUN_001bf584 @ 0x001bf584   (est. cl4_swift_witness_retpair)
 * Ghidra: undefined1[16] FUN_001bf584(void)
 * FUN_003554b0, indirect result pair; if x21 non-null returns a degenerate pair
 * {x8_00, x8_00}, else the resolved pair.
 * Confidence: low (Swift witness pair getter).
 */
cl4_result_t cl4_swift_witness_retpair(void)
{
    cl4_result_t r = { 0, 0 };   /* (*extraout_x8)() */
    long x21 = 0;
    if (x21 != 0) { r.lo = r.hi; }
    return r;
}

/*--------------------------------------------------------------------*/
/* FUN_001bf6a4 @ 0x001bf6a4   (est. cl4_swift_string_append7)
 * Ghidra: void FUN_001bf6a4(void)
 * Thunk into FUN_001b9084 (Swift string insert/append path).
 * Confidence: low (thunk into 0x1b9084).
 */
void cl4_swift_string_append7(void)
{
    cl4_swift_string_insert(0, 0, 0);
}

/*--------------------------------------------------------------------*/
/* FUN_001bf6f4 @ 0x001bf6f4   (est. cl4_swift_pair_convert)
 * Ghidra: void FUN_001bf6f4(undefined1 (*)[16], undefined8*)
 * Converts the {*p2, p2[1]} pair via FUN_0001a1c8 and stores into *param_1.
 * Confidence: low (Swift pair conversion).
 */
void cl4_swift_pair_convert(void *out, unsigned long *p)
{
    cl4_result_t r = sk_swift_pair_cvt(p[0], p[1]);   /* FUN_0001a1c8 */
    ((unsigned long *)out)[0] = r.lo;
    ((unsigned long *)out)[1] = r.hi;
}

/*--------------------------------------------------------------------*/
/* FUN_001bf740 @ 0x001bf740   (est. cl4_swift_tag_write)
 * Ghidra: void FUN_001bf740(void)
 * FUN_00349d14/FUN_00351624/FUN_00348f68, then thunk_FUN_002298d4(extraout_x1&0xff),
 * then FUN_001a8564.
 * Confidence: low (Swift tag write).
 */
void cl4_swift_tag_write(void)
{
    sk_swift_state(0);   /* FUN_00349d14 */
    sk_swift_state2(0);  /* FUN_00351624 */
    sk_swift_state3(0);  /* FUN_00348f68 */
    /* thunk_FUN_002298d4(extraout_x1 & 0xff) */
    sk_swift_tag(0);     /* FUN_001a8564 */
}

/*--------------------------------------------------------------------*/
/* FUN_001bf784 @ 0x001bf784   (est. cl4_swift_tag_write2)
 * Ghidra: void FUN_001bf784(void)
 * FUN_00349d14/FUN_00351624/FUN_00348f68, then FUN_00229a3c(extraout_x1),
 * then FUN_001a8564.
 * Confidence: low (Swift tag write).
 */
void cl4_swift_tag_write2(void)
{
    sk_swift_state(0);   /* FUN_00349d14 */
    sk_swift_state2(0);  /* FUN_00351624 */
    sk_swift_state3(0);  /* FUN_00348f68 */
    sk_swift_flag_set(0);/* FUN_00229a3c(extraout_x1) */
    sk_swift_tag(0);     /* FUN_001a8564 */
}

/*--------------------------------------------------------------------*/
/* FUN_001bf7c8 @ 0x001bf7c8   (est. cl4_swift_string_seed)
 * Ghidra: void FUN_001bf7c8(ulong)
 * Swift string "seed" obfuscation: XORs the fixed seeds _DAT_006adf10/_DAT_006adf18
 * with constants ("setup", "superpose", "randomor", "st...") and param_1, builds a
 * string, then FUN_001b9084 (append) + FUN_001a8564. XOR constant-obfuscated
 * string materialization.
 * Confidence: low (Swift XOR-obfuscated string seed).
 */
void cl4_swift_string_seed(unsigned long key)
{
    /* local_48 = _DAT_006adf18 ^ 0x7465646279746573 ("stbyted" reversed)
     * local_58 = _DAT_006adf18 ^ 0x646f72616e646f6d
     * uStack_60 = _DAT_006adf10 ^ key ^ 0x736f6d6570736575
     * uStack_50 = _DAT_006adf10 ^ key ^ 0x6c7967656e657261 */
    unsigned long s[4] = {0, 0, 0, 0};
    (void)s; (void)key;
    cl4_swift_string_insert(&s, 0, 0);   /* FUN_001b9084(&local_68) */
    sk_swift_tag(0);                     /* FUN_001a8564 */
}

/*--------------------------------------------------------------------*/
/* FUN_001bf870 @ 0x001bf870   (est. cl4_swift_tag_lookup)
 * Ghidra: void FUN_001bf870(undefined8, ulong)
 * Looks up a tag in the table DAT_004f2670 indexed by (param_2&0xff), calls
 * thunk_FUN_002298d4, then FUN_001a8564.
 * Confidence: low (Swift tag table lookup).
 */
void cl4_swift_tag_lookup(void *a, unsigned long idx)
{
    (void)a;
    /* thunk_FUN_002298d4(*(DAT_004f2670 + (idx&0xff)*8)) */
    sk_swift_tag(0);   /* FUN_001a8564 */
}

/*--------------------------------------------------------------------*/
/* FUN_001bf928 @ 0x001bf928   (est. cl4_swift_deinit)
 * Ghidra: undefined8 FUN_001bf928(void)
 * Deinit: FUN_00319a04, releases locals (FUN_0036b118/FUN_003a25d4), unwinds
 * (FUN_000026e8), returns 0x1302.
 * Confidence: low (Swift deinit returning an object id).
 */
unsigned long cl4_swift_deinit(void)
{
    sk_swift_state(0);      /* FUN_00319a04 */
    sk_swift_free(0);       /* FUN_0036b118(local_30) */
    sk_swift_meta(0);       /* FUN_003a25d4(local_20) */
    sk_swift_free(0);       /* FUN_0036b118(local_18) */
    sk_swift_gstore(0);     /* FUN_000026e8(stack) */
    return 0x1302;
}

/*--------------------------------------------------------------------*/
/* FUN_001bf9b0 @ 0x001bf9b0   (est. cl4_swift_buf_release)
 * Ghidra: void FUN_001bf9b0(undefined8, undefined8, undefined8)
 * FUN_00350a28, thunk_FUN_0036b270(param_3), FUN_0007c1c4.
 * Confidence: low (Swift buffer release).
 */
void cl4_swift_buf_release(void *a, void *b, void *p)
{
    (void)a; (void)b;
    sk_swift_state(0);            /* FUN_00350a28 */
    sk_swift_free_pages((unsigned long)p);  /* thunk_FUN_0036b270(p) */
    sk_swift_state2(0);           /* FUN_0007c1c4 */
}

/*--------------------------------------------------------------------*/
/* FUN_001bf9dc @ 0x001bf9dc   (est. cl4_swift_const_pair)
 * Ghidra: undefined1[16] FUN_001bf9dc(void)
 * Returns the constant pair {0xd000000000000012, 0x80000000005ce7b0}.
 * Confidence: high (clear constant pair).
 */
cl4_result_t cl4_swift_const_pair(void)
{
    cl4_result_t r = { 0xd000000000000012, 0x80000000005ce7b0 };
    return r;
}

/*--------------------------------------------------------------------*/
/* FUN_001bf9f8 @ 0x001bf9f8   (est. cl4_swift_dispatch_switch)
 * Ghidra: undefined8 FUN_001bf9f8(void)
 * Swift tagged-dispatch: FUN_00319a14, switches on a type tag; default/1 build the
 * object via FUN_00319a24 (return 0x1300); case 2 releases locals and unwinds
 * (return 0x1301).
 * Confidence: low (Swift tagged-object switch).
 */
unsigned long cl4_swift_dispatch_switch(void)
{
    /* FUN_00319a14; switch(local_28): default/1 -> FUN_00319a24(stack), ret 0x1300;
     * case 2 -> FUN_003a25d4(local_38)/FUN_0036b118 x2/FUN_000026e8, ret 0x1301 */
    int tag = 0;   /* local_28 */
    if (tag == 2) {
        sk_swift_meta(0);   /* FUN_003a25d4 */
        sk_swift_free(0);   /* FUN_0036b118 */
        sk_swift_free(0);   /* FUN_0036b118 */
        sk_swift_gstore(0); /* FUN_000026e8 */
        return 0x1301;
    }
    /* FUN_00319a24(stack) */
    return 0x1300;
}

/*--------------------------------------------------------------------*/
/* FUN_001bfaa4 @ 0x001bfaa4   (est. cl4_swift_string_build)
 * Ghidra: undefined1[16] FUN_001bfaa4(void)
 * The largest function in the region: a full Swift String construction/description
 * pipeline. Builds a string from global state (FUN_00319a04/FUN_00310d98), appends
 * an "EncodingError.invalidValue" prefix (FUN_001a89a8 with s_EncodingError_
 * invalidValue_005ce7f0), and runs a long chain of string-append/validate helpers
 * (FUN_00355c78, FUN_0034a274, FUN_003a25d4, FUN_00351f34, FUN_00353d64,
 * FUN_002060d4, FUN_0034d044, FUN_0034de14, FUN_00349cbc, FUN_003508f0,
 * FUN_00352cc8, FUN_002a4c98, FUN_00357a00, FUN_003a2610...), interleaving the
 * "_Path"/"_Underlying error" sub-strings and releasing intermediate buffers
 * (FUN_0036b118). Returns the built {word, flags} pair. Heavy extraout chain.
 * Confidence: low (Swift String description builder; string-matched prefix).
 */
cl4_result_t cl4_swift_string_build(void)
{
    /* FUN_00319a04 / FUN_00310d98 / FUN_0006e778(0x23) / FUN_00351e08 /
     * FUN_001a89a8("EncodingError.invalidValue", 0x1c, 1) / FUN_00355c78 /
     * FUN_0034a274 ... */
    cl4_result_t out = { 0, 0 };
    /* long append chain: FUN_00351f34 / FUN_00353d64 / FUN_0034895c /
     * FUN_002060d4 / FUN_0034d044 / FUN_0034de14 / FUN_00349cbc /
     * FUN_003508f0 / FUN_00352cc8 / FUN_002a4c98 / FUN_00357a00 /
     * FUN_003a2610 / FUN_00355fa0(&DAT_005ce80d) / FUN_003562e0 ... */
    sk_swift_string_lit(0);   /* FUN_001a89a8 prefix */
    sk_swift_state(0);
    return out;
}

/*--------------------------------------------------------------------*/
/* Swift witness-1 forwarding thunks 0x1be138-0x1be4a0.
 * Each trivially forwards to the cl4_swift_witness_XXX (FUN_0034b7f4) function
 * at the address given in its header. All confidence low (witness forward). */

/*--------------------------------------------------------------------*/
/* FUN_001be138 @ 0x001be138   (est. cl4_swift_wt_138)
 * Swift witness dispatch thunk (indirect protocol-witness call). Slot dispatch via FUN_0034b7f4/FUN_0034b798.
 * Confidence: low (indirect witness dispatch).
 * Notes: faithful body as generated; see family comment above. */
void cl4_swift_wt_138(void){ cl4_swift_witness_048(0,0,0); }
/*--------------------------------------------------------------------*/
/* FUN_001be13c @ 0x001be13c   (est. cl4_swift_wt_13c)
 * Swift witness dispatch thunk (indirect protocol-witness call). Slot dispatch via FUN_0034b7f4/FUN_0034b798.
 * Confidence: low (indirect witness dispatch).
 * Notes: faithful body as generated; see family comment above. */
void cl4_swift_wt_13c(void){ cl4_swift_witness_048(0,0,0); }
/*--------------------------------------------------------------------*/
/* FUN_001be150 @ 0x001be150   (est. cl4_swift_wt_150)
 * Swift witness dispatch thunk (indirect protocol-witness call). Slot dispatch via FUN_0034b7f4/FUN_0034b798.
 * Confidence: low (indirect witness dispatch).
 * Notes: faithful body as generated; see family comment above. */
void cl4_swift_wt_150(void){ cl4_swift_witness_050(0,0,0); }
/*--------------------------------------------------------------------*/
/* FUN_001be154 @ 0x001be154   (est. cl4_swift_wt_154)
 * Swift witness dispatch thunk (indirect protocol-witness call). Slot dispatch via FUN_0034b7f4/FUN_0034b798.
 * Confidence: low (indirect witness dispatch).
 * Notes: faithful body as generated; see family comment above. */
void cl4_swift_wt_154(void){ cl4_swift_witness_050(0,0,0); }
/*--------------------------------------------------------------------*/
/* FUN_001be168 @ 0x001be168   (est. cl4_swift_wt_168)
 * Swift witness dispatch thunk (indirect protocol-witness call). Slot dispatch via FUN_0034b7f4/FUN_0034b798.
 * Confidence: low (indirect witness dispatch).
 * Notes: faithful body as generated; see family comment above. */
void cl4_swift_wt_168(void){ cl4_swift_witness_058(0,0,0); }
/*--------------------------------------------------------------------*/
/* FUN_001be16c @ 0x001be16c   (est. cl4_swift_wt_16c)
 * Swift witness dispatch thunk (indirect protocol-witness call). Slot dispatch via FUN_0034b7f4/FUN_0034b798.
 * Confidence: low (indirect witness dispatch).
 * Notes: faithful body as generated; see family comment above. */
void cl4_swift_wt_16c(void){ cl4_swift_witness_058(0,0,0); }
/*--------------------------------------------------------------------*/
/* FUN_001be180 @ 0x001be180   (est. cl4_swift_wt_180)
 * Swift witness dispatch thunk (indirect protocol-witness call). Slot dispatch via FUN_0034b7f4/FUN_0034b798.
 * Confidence: low (indirect witness dispatch).
 * Notes: faithful body as generated; see family comment above. */
void cl4_swift_wt_180(void){ cl4_swift_witness_060(0,0,0); }
/*--------------------------------------------------------------------*/
/* FUN_001be184 @ 0x001be184   (est. cl4_swift_wt_184)
 * Swift witness dispatch thunk (indirect protocol-witness call). Slot dispatch via FUN_0034b7f4/FUN_0034b798.
 * Confidence: low (indirect witness dispatch).
 * Notes: faithful body as generated; see family comment above. */
void cl4_swift_wt_184(void){ cl4_swift_witness_060(0,0,0); }
/*--------------------------------------------------------------------*/
/* FUN_001be198 @ 0x001be198   (est. cl4_swift_wt_198)
 * Swift witness dispatch thunk (indirect protocol-witness call). Slot dispatch via FUN_0034b7f4/FUN_0034b798.
 * Confidence: low (indirect witness dispatch).
 * Notes: faithful body as generated; see family comment above. */
void cl4_swift_wt_198(void){ cl4_swift_witness_068(0,0,0); }
/*--------------------------------------------------------------------*/
/* FUN_001be19c @ 0x001be19c   (est. cl4_swift_wt_19c)
 * Swift witness dispatch thunk (indirect protocol-witness call). Slot dispatch via FUN_0034b7f4/FUN_0034b798.
 * Confidence: low (indirect witness dispatch).
 * Notes: faithful body as generated; see family comment above. */
void cl4_swift_wt_19c(void){ cl4_swift_witness_068(0,0,0); }
/*--------------------------------------------------------------------*/
/* FUN_001be1b0 @ 0x001be1b0   (est. cl4_swift_wt_1b0)
 * Swift witness dispatch thunk (indirect protocol-witness call). Slot dispatch via FUN_0034b7f4/FUN_0034b798.
 * Confidence: low (indirect witness dispatch).
 * Notes: faithful body as generated; see family comment above. */
void cl4_swift_wt_1b0(void){ cl4_swift_witness_070(0,0,0); }
/*--------------------------------------------------------------------*/
/* FUN_001be1b4 @ 0x001be1b4   (est. cl4_swift_wt_1b4)
 * Swift witness dispatch thunk (indirect protocol-witness call). Slot dispatch via FUN_0034b7f4/FUN_0034b798.
 * Confidence: low (indirect witness dispatch).
 * Notes: faithful body as generated; see family comment above. */
void cl4_swift_wt_1b4(void){ cl4_swift_witness_070(0,0,0); }
/*--------------------------------------------------------------------*/
/* FUN_001be1c8 @ 0x001be1c8   (est. cl4_swift_wt_1c8)
 * Swift witness dispatch thunk (indirect protocol-witness call). Slot dispatch via FUN_0034b7f4/FUN_0034b798.
 * Confidence: low (indirect witness dispatch).
 * Notes: faithful body as generated; see family comment above. */
void cl4_swift_wt_1c8(void){ cl4_swift_witness_078(0,0,0); }
/*--------------------------------------------------------------------*/
/* FUN_001be1cc @ 0x001be1cc   (est. cl4_swift_wt_1cc)
 * Swift witness dispatch thunk (indirect protocol-witness call). Slot dispatch via FUN_0034b7f4/FUN_0034b798.
 * Confidence: low (indirect witness dispatch).
 * Notes: faithful body as generated; see family comment above. */
void cl4_swift_wt_1cc(void){ cl4_swift_witness_078(0,0,0); }
/*--------------------------------------------------------------------*/
/* FUN_001be1e0 @ 0x001be1e0   (est. cl4_swift_wt_1e0)
 * Swift witness dispatch thunk (indirect protocol-witness call). Slot dispatch via FUN_0034b7f4/FUN_0034b798.
 * Confidence: low (indirect witness dispatch).
 * Notes: faithful body as generated; see family comment above. */
void cl4_swift_wt_1e0(void){ cl4_swift_witness_080(0,0,0); }
/*--------------------------------------------------------------------*/
/* FUN_001be1e4 @ 0x001be1e4   (est. cl4_swift_wt_1e4)
 * Swift witness dispatch thunk (indirect protocol-witness call). Slot dispatch via FUN_0034b7f4/FUN_0034b798.
 * Confidence: low (indirect witness dispatch).
 * Notes: faithful body as generated; see family comment above. */
void cl4_swift_wt_1e4(void){ cl4_swift_witness_080(0,0,0); }
/*--------------------------------------------------------------------*/
/* FUN_001be1f8 @ 0x001be1f8   (est. cl4_swift_wt_1f8)
 * Swift witness dispatch thunk (indirect protocol-witness call). Slot dispatch via FUN_0034b7f4/FUN_0034b798.
 * Confidence: low (indirect witness dispatch).
 * Notes: faithful body as generated; see family comment above. */
void cl4_swift_wt_1f8(void){ cl4_swift_witness_088(0,0,0); }
/*--------------------------------------------------------------------*/
/* FUN_001be1fc @ 0x001be1fc   (est. cl4_swift_wt_1fc)
 * Swift witness dispatch thunk (indirect protocol-witness call). Slot dispatch via FUN_0034b7f4/FUN_0034b798.
 * Confidence: low (indirect witness dispatch).
 * Notes: faithful body as generated; see family comment above. */
void cl4_swift_wt_1fc(void){ cl4_swift_witness_088(0,0,0); }
/*--------------------------------------------------------------------*/
/* FUN_001be210 @ 0x001be210   (est. cl4_swift_wt_210)
 * Swift witness dispatch thunk (indirect protocol-witness call). Slot dispatch via FUN_0034b7f4/FUN_0034b798.
 * Confidence: low (indirect witness dispatch).
 * Notes: faithful body as generated; see family comment above. */
void cl4_swift_wt_210(void){ cl4_swift_witness_090(0,0,0); }
/*--------------------------------------------------------------------*/
/* FUN_001be214 @ 0x001be214   (est. cl4_swift_wt_214)
 * Swift witness dispatch thunk (indirect protocol-witness call). Slot dispatch via FUN_0034b7f4/FUN_0034b798.
 * Confidence: low (indirect witness dispatch).
 * Notes: faithful body as generated; see family comment above. */
void cl4_swift_wt_214(void){ cl4_swift_witness_090(0,0,0); }
/*--------------------------------------------------------------------*/
/* FUN_001be228 @ 0x001be228   (est. cl4_swift_wt_228)
 * Swift witness dispatch thunk (indirect protocol-witness call). Slot dispatch via FUN_0034b7f4/FUN_0034b798.
 * Confidence: low (indirect witness dispatch).
 * Notes: faithful body as generated; see family comment above. */
void cl4_swift_wt_228(void){ cl4_swift_witness_098(0,0,0); }
/*--------------------------------------------------------------------*/
/* FUN_001be22c @ 0x001be22c   (est. cl4_swift_wt_22c)
 * Swift witness dispatch thunk (indirect protocol-witness call). Slot dispatch via FUN_0034b7f4/FUN_0034b798.
 * Confidence: low (indirect witness dispatch).
 * Notes: faithful body as generated; see family comment above. */
void cl4_swift_wt_22c(void){ cl4_swift_witness_098(0,0,0); }
/*--------------------------------------------------------------------*/
/* FUN_001be240 @ 0x001be240   (est. cl4_swift_wt_240)
 * Swift witness dispatch thunk (indirect protocol-witness call). Slot dispatch via FUN_0034b7f4/FUN_0034b798.
 * Confidence: low (indirect witness dispatch).
 * Notes: faithful body as generated; see family comment above. */
void cl4_swift_wt_240(void){ cl4_swift_witness_0a0(0,0,0); }
/*--------------------------------------------------------------------*/
/* FUN_001be244 @ 0x001be244   (est. cl4_swift_wt_244)
 * Swift witness dispatch thunk (indirect protocol-witness call). Slot dispatch via FUN_0034b7f4/FUN_0034b798.
 * Confidence: low (indirect witness dispatch).
 * Notes: faithful body as generated; see family comment above. */
void cl4_swift_wt_244(void){ cl4_swift_witness_0a0(0,0,0); }
/*--------------------------------------------------------------------*/
/* FUN_001be258 @ 0x001be258   (est. cl4_swift_wt_258)
 * Swift witness dispatch thunk (indirect protocol-witness call). Slot dispatch via FUN_0034b7f4/FUN_0034b798.
 * Confidence: low (indirect witness dispatch).
 * Notes: faithful body as generated; see family comment above. */
void cl4_swift_wt_258(void){ cl4_swift_witness_0a8(0,0,0); }
/*--------------------------------------------------------------------*/
/* FUN_001be25c @ 0x001be25c   (est. cl4_swift_wt_25c)
 * Swift witness dispatch thunk (indirect protocol-witness call). Slot dispatch via FUN_0034b7f4/FUN_0034b798.
 * Confidence: low (indirect witness dispatch).
 * Notes: faithful body as generated; see family comment above. */
void cl4_swift_wt_25c(void){ cl4_swift_witness_0a8(0,0,0); }
/*--------------------------------------------------------------------*/
/* FUN_001be270 @ 0x001be270   (est. cl4_swift_wt_270)
 * Swift witness dispatch thunk (indirect protocol-witness call). Slot dispatch via FUN_0034b7f4/FUN_0034b798.
 * Confidence: low (indirect witness dispatch).
 * Notes: faithful body as generated; see family comment above. */
void cl4_swift_wt_270(void){ cl4_swift_witness_0b0(0,0,0); }
/*--------------------------------------------------------------------*/
/* FUN_001be274 @ 0x001be274   (est. cl4_swift_wt_274)
 * Swift witness dispatch thunk (indirect protocol-witness call). Slot dispatch via FUN_0034b7f4/FUN_0034b798.
 * Confidence: low (indirect witness dispatch).
 * Notes: faithful body as generated; see family comment above. */
void cl4_swift_wt_274(void){ cl4_swift_witness_0b0(0,0,0); }
/*--------------------------------------------------------------------*/
/* FUN_001be288 @ 0x001be288   (est. cl4_swift_wt_288)
 * Swift witness dispatch thunk (indirect protocol-witness call). Slot dispatch via FUN_0034b7f4/FUN_0034b798.
 * Confidence: low (indirect witness dispatch).
 * Notes: faithful body as generated; see family comment above. */
void cl4_swift_wt_288(void){ cl4_swift_witness_0b8(0,0,0); }
/*--------------------------------------------------------------------*/
/* FUN_001be28c @ 0x001be28c   (est. cl4_swift_wt_28c)
 * Swift witness dispatch thunk (indirect protocol-witness call). Slot dispatch via FUN_0034b7f4/FUN_0034b798.
 * Confidence: low (indirect witness dispatch).
 * Notes: faithful body as generated; see family comment above. */
void cl4_swift_wt_28c(void){ cl4_swift_witness_0b8(0,0,0); }
/*--------------------------------------------------------------------*/
/* FUN_001be2a0 @ 0x001be2a0   (est. cl4_swift_wt_2a0)
 * Swift witness dispatch thunk (indirect protocol-witness call). Slot dispatch via FUN_0034b7f4/FUN_0034b798.
 * Confidence: low (indirect witness dispatch).
 * Notes: faithful body as generated; see family comment above. */
void cl4_swift_wt_2a0(void){ cl4_swift_witness_0c0(0,0,0); }
/*--------------------------------------------------------------------*/
/* FUN_001be2a4 @ 0x001be2a4   (est. cl4_swift_wt_2a4)
 * Swift witness dispatch thunk (indirect protocol-witness call). Slot dispatch via FUN_0034b7f4/FUN_0034b798.
 * Confidence: low (indirect witness dispatch).
 * Notes: faithful body as generated; see family comment above. */
void cl4_swift_wt_2a4(void){ cl4_swift_witness_0c0(0,0,0); }
/*--------------------------------------------------------------------*/
/* FUN_001be2b8 @ 0x001be2b8   (est. cl4_swift_wt_2b8)
 * Swift witness dispatch thunk (indirect protocol-witness call). Slot dispatch via FUN_0034b7f4/FUN_0034b798.
 * Confidence: low (indirect witness dispatch).
 * Notes: faithful body as generated; see family comment above. */
void cl4_swift_wt_2b8(void){ cl4_swift_witness_0c8(0,0,0); }
/*--------------------------------------------------------------------*/
/* FUN_001be2bc @ 0x001be2bc   (est. cl4_swift_wt_2bc)
 * Swift witness dispatch thunk (indirect protocol-witness call). Slot dispatch via FUN_0034b7f4/FUN_0034b798.
 * Confidence: low (indirect witness dispatch).
 * Notes: faithful body as generated; see family comment above. */
void cl4_swift_wt_2bc(void){ cl4_swift_witness_0c8(0,0,0); }
/*--------------------------------------------------------------------*/
/* FUN_001be2d0 @ 0x001be2d0   (est. cl4_swift_wt_2d0)
 * Swift witness dispatch thunk (indirect protocol-witness call). Slot dispatch via FUN_0034b7f4/FUN_0034b798.
 * Confidence: low (indirect witness dispatch).
 * Notes: faithful body as generated; see family comment above. */
void cl4_swift_wt_2d0(void){ cl4_swift_witness_0d0(0,0,0,0,0); }
/*--------------------------------------------------------------------*/
/* FUN_001be2d4 @ 0x001be2d4   (est. cl4_swift_wt_2d4)
 * Swift witness dispatch thunk (indirect protocol-witness call). Slot dispatch via FUN_0034b7f4/FUN_0034b798.
 * Confidence: low (indirect witness dispatch).
 * Notes: faithful body as generated; see family comment above. */
void cl4_swift_wt_2d4(void){ cl4_swift_witness_0d0(0,0,0,0,0); }
/*--------------------------------------------------------------------*/
/* FUN_001be2f8 @ 0x001be2f8   (est. cl4_swift_wt_2f8)
 * Swift witness dispatch thunk (indirect protocol-witness call). Slot dispatch via FUN_0034b7f4/FUN_0034b798.
 * Confidence: low (indirect witness dispatch).
 * Notes: faithful body as generated; see family comment above. */
void cl4_swift_wt_2f8(void){ cl4_swift_witness_0d8(0,0,0,0,0); }
/*--------------------------------------------------------------------*/
/* FUN_001be2fc @ 0x001be2fc   (est. cl4_swift_wt_2fc)
 * Swift witness dispatch thunk (indirect protocol-witness call). Slot dispatch via FUN_0034b7f4/FUN_0034b798.
 * Confidence: low (indirect witness dispatch).
 * Notes: faithful body as generated; see family comment above. */
void cl4_swift_wt_2fc(void){ cl4_swift_witness_0d8(0,0,0,0,0); }
/*--------------------------------------------------------------------*/
/* FUN_001be320 @ 0x001be320   (est. cl4_swift_wt_320)
 * Swift witness dispatch thunk (indirect protocol-witness call). Slot dispatch via FUN_0034b7f4/FUN_0034b798.
 * Confidence: low (indirect witness dispatch).
 * Notes: faithful body as generated; see family comment above. */
void cl4_swift_wt_320(void){ cl4_swift_witness_0e0(0,0,0); }
/*--------------------------------------------------------------------*/
/* FUN_001be324 @ 0x001be324   (est. cl4_swift_wt_324)
 * Swift witness dispatch thunk (indirect protocol-witness call). Slot dispatch via FUN_0034b7f4/FUN_0034b798.
 * Confidence: low (indirect witness dispatch).
 * Notes: faithful body as generated; see family comment above. */
void cl4_swift_wt_324(void){ cl4_swift_witness_0e0(0,0,0); }
/*--------------------------------------------------------------------*/
/* FUN_001be338 @ 0x001be338   (est. cl4_swift_wt_338)
 * Swift witness dispatch thunk (indirect protocol-witness call). Slot dispatch via FUN_0034b7f4/FUN_0034b798.
 * Confidence: low (indirect witness dispatch).
 * Notes: faithful body as generated; see family comment above. */
void cl4_swift_wt_338(void){ cl4_swift_witness_0e8(0,0,0); }
/*--------------------------------------------------------------------*/
/* FUN_001be33c @ 0x001be33c   (est. cl4_swift_wt_33c)
 * Swift witness dispatch thunk (indirect protocol-witness call). Slot dispatch via FUN_0034b7f4/FUN_0034b798.
 * Confidence: low (indirect witness dispatch).
 * Notes: faithful body as generated; see family comment above. */
void cl4_swift_wt_33c(void){ cl4_swift_witness_0e8(0,0,0); }
/*--------------------------------------------------------------------*/
/* FUN_001be350 @ 0x001be350   (est. cl4_swift_wt_350)
 * Swift witness dispatch thunk (indirect protocol-witness call). Slot dispatch via FUN_0034b7f4/FUN_0034b798.
 * Confidence: low (indirect witness dispatch).
 * Notes: faithful body as generated; see family comment above. */
void cl4_swift_wt_350(void){ cl4_swift_witness_0f0(0,0,0); }
/*--------------------------------------------------------------------*/
/* FUN_001be354 @ 0x001be354   (est. cl4_swift_wt_354)
 * Swift witness dispatch thunk (indirect protocol-witness call). Slot dispatch via FUN_0034b7f4/FUN_0034b798.
 * Confidence: low (indirect witness dispatch).
 * Notes: faithful body as generated; see family comment above. */
void cl4_swift_wt_354(void){ cl4_swift_witness_0f0(0,0,0); }
/*--------------------------------------------------------------------*/
/* FUN_001be368 @ 0x001be368   (est. cl4_swift_wt_368)
 * Swift witness dispatch thunk (indirect protocol-witness call). Slot dispatch via FUN_0034b7f4/FUN_0034b798.
 * Confidence: low (indirect witness dispatch).
 * Notes: faithful body as generated; see family comment above. */
void cl4_swift_wt_368(void){ cl4_swift_witness_0f8(0,0,0); }
/*--------------------------------------------------------------------*/
/* FUN_001be36c @ 0x001be36c   (est. cl4_swift_wt_36c)
 * Swift witness dispatch thunk (indirect protocol-witness call). Slot dispatch via FUN_0034b7f4/FUN_0034b798.
 * Confidence: low (indirect witness dispatch).
 * Notes: faithful body as generated; see family comment above. */
void cl4_swift_wt_36c(void){ cl4_swift_witness_0f8(0,0,0); }
/*--------------------------------------------------------------------*/
/* FUN_001be384 @ 0x001be384   (est. cl4_swift_wt_384)
 * Swift witness dispatch thunk (indirect protocol-witness call). Slot dispatch via FUN_0034b7f4/FUN_0034b798.
 * Confidence: low (indirect witness dispatch).
 * Notes: faithful body as generated; see family comment above. */
void cl4_swift_wt_384(void){ cl4_swift_witness_100(0,0,0); }
/*--------------------------------------------------------------------*/
/* FUN_001be388 @ 0x001be388   (est. cl4_swift_wt_388)
 * Swift witness dispatch thunk (indirect protocol-witness call). Slot dispatch via FUN_0034b7f4/FUN_0034b798.
 * Confidence: low (indirect witness dispatch).
 * Notes: faithful body as generated; see family comment above. */
void cl4_swift_wt_388(void){ cl4_swift_witness_100(0,0,0); }
/*--------------------------------------------------------------------*/
/* FUN_001be39c @ 0x001be39c   (est. cl4_swift_wt_39c)
 * Swift witness dispatch thunk (indirect protocol-witness call). Slot dispatch via FUN_0034b7f4/FUN_0034b798.
 * Confidence: low (indirect witness dispatch).
 * Notes: faithful body as generated; see family comment above. */
void cl4_swift_wt_39c(void){ cl4_swift_witness_108(0,0,0); }
/*--------------------------------------------------------------------*/
/* FUN_001be3a0 @ 0x001be3a0   (est. cl4_swift_wt_3a0)
 * Swift witness dispatch thunk (indirect protocol-witness call). Slot dispatch via FUN_0034b7f4/FUN_0034b798.
 * Confidence: low (indirect witness dispatch).
 * Notes: faithful body as generated; see family comment above. */
void cl4_swift_wt_3a0(void){ cl4_swift_witness_108(0,0,0); }
/*--------------------------------------------------------------------*/
/* FUN_001be3b4 @ 0x001be3b4   (est. cl4_swift_wt_3b4)
 * Swift witness dispatch thunk (indirect protocol-witness call). Slot dispatch via FUN_0034b7f4/FUN_0034b798.
 * Confidence: low (indirect witness dispatch).
 * Notes: faithful body as generated; see family comment above. */
void cl4_swift_wt_3b4(void){ cl4_swift_witness_110(0,0,0); }
/*--------------------------------------------------------------------*/
/* FUN_001be3b8 @ 0x001be3b8   (est. cl4_swift_wt_3b8)
 * Swift witness dispatch thunk (indirect protocol-witness call). Slot dispatch via FUN_0034b7f4/FUN_0034b798.
 * Confidence: low (indirect witness dispatch).
 * Notes: faithful body as generated; see family comment above. */
void cl4_swift_wt_3b8(void){ cl4_swift_witness_110(0,0,0); }
/*--------------------------------------------------------------------*/
/* FUN_001be3d0 @ 0x001be3d0   (est. cl4_swift_wt_3d0)
 * Swift witness dispatch thunk (indirect protocol-witness call). Slot dispatch via FUN_0034b7f4/FUN_0034b798.
 * Confidence: low (indirect witness dispatch).
 * Notes: faithful body as generated; see family comment above. */
void cl4_swift_wt_3d0(void){ cl4_swift_witness_118(0,0,0); }
/*--------------------------------------------------------------------*/
/* FUN_001be3d4 @ 0x001be3d4   (est. cl4_swift_wt_3d4)
 * Swift witness dispatch thunk (indirect protocol-witness call). Slot dispatch via FUN_0034b7f4/FUN_0034b798.
 * Confidence: low (indirect witness dispatch).
 * Notes: faithful body as generated; see family comment above. */
void cl4_swift_wt_3d4(void){ cl4_swift_witness_118(0,0,0); }
/*--------------------------------------------------------------------*/
/* FUN_001be3ec @ 0x001be3ec   (est. cl4_swift_wt_3ec)
 * Swift witness dispatch thunk (indirect protocol-witness call). Slot dispatch via FUN_0034b7f4/FUN_0034b798.
 * Confidence: low (indirect witness dispatch).
 * Notes: faithful body as generated; see family comment above. */
void cl4_swift_wt_3ec(void){ cl4_swift_witness_120(0,0,0); }
/*--------------------------------------------------------------------*/
/* FUN_001be3f0 @ 0x001be3f0   (est. cl4_swift_wt_3f0)
 * Swift witness dispatch thunk (indirect protocol-witness call). Slot dispatch via FUN_0034b7f4/FUN_0034b798.
 * Confidence: low (indirect witness dispatch).
 * Notes: faithful body as generated; see family comment above. */
void cl4_swift_wt_3f0(void){ cl4_swift_witness_120(0,0,0); }
/*--------------------------------------------------------------------*/
/* FUN_001be404 @ 0x001be404   (est. cl4_swift_wt_404)
 * Swift witness dispatch thunk (indirect protocol-witness call). Slot dispatch via FUN_0034b7f4/FUN_0034b798.
 * Confidence: low (indirect witness dispatch).
 * Notes: faithful body as generated; see family comment above. */
void cl4_swift_wt_404(void){ cl4_swift_witness_128(0,0,0); }
/*--------------------------------------------------------------------*/
/* FUN_001be408 @ 0x001be408   (est. cl4_swift_wt_408)
 * Swift witness dispatch thunk (indirect protocol-witness call). Slot dispatch via FUN_0034b7f4/FUN_0034b798.
 * Confidence: low (indirect witness dispatch).
 * Notes: faithful body as generated; see family comment above. */
void cl4_swift_wt_408(void){ cl4_swift_witness_128(0,0,0); }
/*--------------------------------------------------------------------*/
/* FUN_001be41c @ 0x001be41c   (est. cl4_swift_wt_41c)
 * Swift witness dispatch thunk (indirect protocol-witness call). Slot dispatch via FUN_0034b7f4/FUN_0034b798.
 * Confidence: low (indirect witness dispatch).
 * Notes: faithful body as generated; see family comment above. */
void cl4_swift_wt_41c(void){ cl4_swift_witness_130(0,0,0); }
/*--------------------------------------------------------------------*/
/* FUN_001be420 @ 0x001be420   (est. cl4_swift_wt_420)
 * Swift witness dispatch thunk (indirect protocol-witness call). Slot dispatch via FUN_0034b7f4/FUN_0034b798.
 * Confidence: low (indirect witness dispatch).
 * Notes: faithful body as generated; see family comment above. */
void cl4_swift_wt_420(void){ cl4_swift_witness_130(0,0,0); }
/*--------------------------------------------------------------------*/
/* FUN_001be434 @ 0x001be434   (est. cl4_swift_wt_434)
 * Swift witness dispatch thunk (indirect protocol-witness call). Slot dispatch via FUN_0034b7f4/FUN_0034b798.
 * Confidence: low (indirect witness dispatch).
 * Notes: faithful body as generated; see family comment above. */
void cl4_swift_wt_434(void){ cl4_swift_witness_138(0,0,0); }
/*--------------------------------------------------------------------*/
/* FUN_001be438 @ 0x001be438   (est. cl4_swift_wt_438)
 * Swift witness dispatch thunk (indirect protocol-witness call). Slot dispatch via FUN_0034b7f4/FUN_0034b798.
 * Confidence: low (indirect witness dispatch).
 * Notes: faithful body as generated; see family comment above. */
void cl4_swift_wt_438(void){ cl4_swift_witness_138(0,0,0); }
/*--------------------------------------------------------------------*/
/* FUN_001be44c @ 0x001be44c   (est. cl4_swift_wt_44c)
 * Swift witness dispatch thunk (indirect protocol-witness call). Slot dispatch via FUN_0034b7f4/FUN_0034b798.
 * Confidence: low (indirect witness dispatch).
 * Notes: faithful body as generated; see family comment above. */
void cl4_swift_wt_44c(void){ cl4_swift_witness_140(0,0,0); }
/*--------------------------------------------------------------------*/
/* FUN_001be450 @ 0x001be450   (est. cl4_swift_wt_450)
 * Swift witness dispatch thunk (indirect protocol-witness call). Slot dispatch via FUN_0034b7f4/FUN_0034b798.
 * Confidence: low (indirect witness dispatch).
 * Notes: faithful body as generated; see family comment above. */
void cl4_swift_wt_450(void){ cl4_swift_witness_140(0,0,0); }
/*--------------------------------------------------------------------*/
/* FUN_001be468 @ 0x001be468   (est. cl4_swift_wt_468)
 * Swift witness dispatch thunk (indirect protocol-witness call). Slot dispatch via FUN_0034b7f4/FUN_0034b798.
 * Confidence: low (indirect witness dispatch).
 * Notes: faithful body as generated; see family comment above. */
void cl4_swift_wt_468(void){ cl4_swift_witness_148(0,0,0); }
/*--------------------------------------------------------------------*/
/* FUN_001be46c @ 0x001be46c   (est. cl4_swift_wt_46c)
 * Swift witness dispatch thunk (indirect protocol-witness call). Slot dispatch via FUN_0034b7f4/FUN_0034b798.
 * Confidence: low (indirect witness dispatch).
 * Notes: faithful body as generated; see family comment above. */
void cl4_swift_wt_46c(void){ cl4_swift_witness_148(0,0,0); }
/*--------------------------------------------------------------------*/
/* FUN_001be484 @ 0x001be484   (est. cl4_swift_wt_484)
 * Swift witness dispatch thunk (indirect protocol-witness call). Slot dispatch via FUN_0034b7f4/FUN_0034b798.
 * Confidence: low (indirect witness dispatch).
 * Notes: faithful body as generated; see family comment above. */
void cl4_swift_wt_484(void){ cl4_swift_witness_150(0,0,0); }
/*--------------------------------------------------------------------*/
/* FUN_001be488 @ 0x001be488   (est. cl4_swift_wt_488)
 * Swift witness dispatch thunk (indirect protocol-witness call). Slot dispatch via FUN_0034b7f4/FUN_0034b798.
 * Confidence: low (indirect witness dispatch).
 * Notes: faithful body as generated; see family comment above. */
void cl4_swift_wt_488(void){ cl4_swift_witness_150(0,0,0); }
/*--------------------------------------------------------------------*/
/* FUN_001be49c @ 0x001be49c   (est. cl4_swift_wt_49c)
 * Swift witness dispatch thunk (indirect protocol-witness call). Slot dispatch via FUN_0034b7f4/FUN_0034b798.
 * Confidence: low (indirect witness dispatch).
 * Notes: faithful body as generated; see family comment above. */
void cl4_swift_wt_49c(void){ cl4_swift_witness_158(0,0,0); }
/*--------------------------------------------------------------------*/
/* FUN_001be4a0 @ 0x001be4a0   (est. cl4_swift_wt_4a0)
 * Swift witness dispatch thunk (indirect protocol-witness call). Slot dispatch via FUN_0034b7f4/FUN_0034b798.
 * Confidence: low (indirect witness dispatch).
 * Notes: faithful body as generated; see family comment above. */
void cl4_swift_wt_4a0(void){ cl4_swift_witness_158(0,0,0); }

/*--------------------------------------------------------------------*/
/* Special witness-forwarding thunks 0x1bf330-0x1bf998.
 * Each trivially forwards to the witness getter/ret-pair function at the
 * address in its header. All confidence low (witness forward). */

/* 0x1bf330/334 -> FUN_001bf510 */
/*--------------------------------------------------------------------*/
/* FUN_001bf330 @ 0x001bf330   (est. cl4_swift_wt_bf330)
 * Swift witness-forwarding thunk. Forwards to witness getter.
 * Confidence: low (witness forward). */
void cl4_swift_wt_bf330(void){ cl4_swift_witness_ret40(); }
/*--------------------------------------------------------------------*/
/* FUN_001bf334 @ 0x001bf334   (est. cl4_swift_wt_bf334)
 * Swift witness-forwarding thunk. Forwards to witness getter.
 * Confidence: low (witness forward). */
void cl4_swift_wt_bf334(void){ cl4_swift_witness_ret40(); }
/* 0x1bf3a4/a8 -> FUN_001bf4c0 */
/*--------------------------------------------------------------------*/
/* FUN_001bf3a4 @ 0x001bf3a4   (est. cl4_swift_wt_bf3a4)
 * Swift witness-forwarding thunk. Forwards to witness getter.
 * Confidence: low (witness forward). */
void cl4_swift_wt_bf3a4(void){ cl4_swift_witness_ret24(); }
/*--------------------------------------------------------------------*/
/* FUN_001bf3a8 @ 0x001bf3a8   (est. cl4_swift_wt_bf3a8)
 * Swift witness-forwarding thunk. Forwards to witness getter.
 * Confidence: low (witness forward). */
void cl4_swift_wt_bf3a8(void){ cl4_swift_witness_ret24(); }
/* 0x1bf3d0/d4 -> FUN_001bf510 */
/*--------------------------------------------------------------------*/
/* FUN_001bf3d0 @ 0x001bf3d0   (est. cl4_swift_wt_bf3d0)
 * Swift witness-forwarding thunk. Forwards to witness getter.
 * Confidence: low (witness forward). */
void cl4_swift_wt_bf3d0(void){ cl4_swift_witness_ret40(); }
/*--------------------------------------------------------------------*/
/* FUN_001bf3d4 @ 0x001bf3d4   (est. cl4_swift_wt_bf3d4)
 * Swift witness-forwarding thunk. Forwards to witness getter.
 * Confidence: low (witness forward). */
void cl4_swift_wt_bf3d4(void){ cl4_swift_witness_ret40(); }
/* 0x1bf420/424 -> FUN_001bf584 */
/*--------------------------------------------------------------------*/
/* FUN_001bf420 @ 0x001bf420   (est. cl4_swift_wt_bf420)
 * Swift witness-forwarding thunk. Forwards to witness getter.
 * Confidence: low (witness forward). */
void cl4_swift_wt_bf420(void){ cl4_swift_witness_retpair(); }
/*--------------------------------------------------------------------*/
/* FUN_001bf424 @ 0x001bf424   (est. cl4_swift_wt_bf424)
 * Swift witness-forwarding thunk. Forwards to witness getter.
 * Confidence: low (witness forward). */
void cl4_swift_wt_bf424(void){ cl4_swift_witness_retpair(); }
/* 0x1bf494/498 -> FUN_001bf4c0 */
/*--------------------------------------------------------------------*/
/* FUN_001bf494 @ 0x001bf494   (est. cl4_swift_wt_bf494)
 * Swift witness-forwarding thunk. Forwards to witness getter.
 * Confidence: low (witness forward). */
void cl4_swift_wt_bf494(void){ cl4_swift_witness_ret24(); }
/*--------------------------------------------------------------------*/
/* FUN_001bf498 @ 0x001bf498   (est. cl4_swift_wt_bf498)
 * Swift witness-forwarding thunk. Forwards to witness getter.
 * Confidence: low (witness forward). */
void cl4_swift_wt_bf498(void){ cl4_swift_witness_ret24(); }
/* 0x1bf4e4/e8 -> FUN_001bf510 */
/*--------------------------------------------------------------------*/
/* FUN_001bf4e4 @ 0x001bf4e4   (est. cl4_swift_wt_bf4e4)
 * Swift witness-forwarding thunk. Forwards to witness getter.
 * Confidence: low (witness forward). */
void cl4_swift_wt_bf4e4(void){ cl4_swift_witness_ret40(); }
/*--------------------------------------------------------------------*/
/* FUN_001bf4e8 @ 0x001bf4e8   (est. cl4_swift_wt_bf4e8)
 * Swift witness-forwarding thunk. Forwards to witness getter.
 * Confidence: low (witness forward). */
void cl4_swift_wt_bf4e8(void){ cl4_swift_witness_ret40(); }
/* 0x1bf558/55c -> FUN_001bf584 */
/*--------------------------------------------------------------------*/
/* FUN_001bf558 @ 0x001bf558   (est. cl4_swift_wt_bf558)
 * Swift witness-forwarding thunk. Forwards to witness getter.
 * Confidence: low (witness forward). */
void cl4_swift_wt_bf558(void){ cl4_swift_witness_retpair(); }
/*--------------------------------------------------------------------*/
/* FUN_001bf55c @ 0x001bf55c   (est. cl4_swift_wt_bf55c)
 * Swift witness-forwarding thunk. Forwards to witness getter.
 * Confidence: low (witness forward). */
void cl4_swift_wt_bf55c(void){ cl4_swift_witness_retpair(); }
/* 0x1bf62c/630 -> FUN_001bef80 (witnessB slot 0x180) */
/*--------------------------------------------------------------------*/
/* FUN_001bf62c @ 0x001bf62c   (est. cl4_swift_wt_bf62c)
 * Swift witness-forwarding thunk. Forwards to witness getter.
 * Confidence: low (witness forward). */
void cl4_swift_wt_bf62c(void){ cl4_swift_witnessB_180(0,0,0,0); }
/*--------------------------------------------------------------------*/
/* FUN_001bf630 @ 0x001bf630   (est. cl4_swift_wt_bf630)
 * Swift witness-forwarding thunk. Forwards to witness getter.
 * Confidence: low (witness forward). */
void cl4_swift_wt_bf630(void){ cl4_swift_witnessB_180(0,0,0,0); }
/* 0x1bf974/978 -> FUN_001bf9dc */
/*--------------------------------------------------------------------*/
/* FUN_001bf974 @ 0x001bf974   (est. cl4_swift_wt_bf974)
 * Swift witness-forwarding thunk. Forwards to witness getter.
 * Confidence: low (witness forward). */
void cl4_swift_wt_bf974(void){ cl4_swift_const_pair(); }
/*--------------------------------------------------------------------*/
/* FUN_001bf978 @ 0x001bf978   (est. cl4_swift_wt_bf978)
 * Swift witness-forwarding thunk. Forwards to witness getter.
 * Confidence: low (witness forward). */
void cl4_swift_wt_bf978(void){ cl4_swift_const_pair(); }
/* 0x1bf994/998 -> FUN_001bf928 */
/*--------------------------------------------------------------------*/
/* FUN_001bf994 @ 0x001bf994   (est. cl4_swift_wt_bf994)
 * Swift witness-forwarding thunk. Forwards to witness getter.
 * Confidence: low (witness forward). */
void cl4_swift_wt_bf994(void){ cl4_swift_deinit(); }
/*--------------------------------------------------------------------*/
/* FUN_001bf998 @ 0x001bf998   (est. cl4_swift_wt_bf998)
 * Swift witness-forwarding thunk. Forwards to witness getter.
 * Confidence: low (witness forward). */
void cl4_swift_wt_bf998(void){ cl4_swift_deinit(); }
