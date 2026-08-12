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
