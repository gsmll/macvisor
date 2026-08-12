/* Recreated from exclavecore_bundle.t8142.RELEASE.im4p (cL4 Secure Kernel, GL1,
 * arm64e, image base 0) — the cL4 microkernel. Ground truth: Ghidra FUN_ names +
 * addresses in cl4_kernel.raw. Version "cL4 microkernel (cL4 (679.100.61))".
 * All names are estimates unless string/header-matched.
 *
 * Region 0x20d0c-0x25704: Tightbeam message codec — the Swift-imported
 * TightbeamMessage / TightbeamDecoder / TightbeamEncoder / TransportBuffer
 * wrappers that marshal messages between exclaves. cL4/seL4 vocabulary.
 */

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

typedef uint64_t word_t;
typedef uint64_t cap_t;
typedef uint64_t tcb_t;

/* cl4_result: lo = value/status, hi = error code (seL4-style). */
typedef struct cl4_result { uint64_t lo; uint64_t hi; } cl4_result_t;

#define LZCOUNT(v)  __builtin_clzll((unsigned long long)(v))
#define sk_ref_retain(v) (void)(v)

/*-------------------------------------------------------------------------
 * Out-of-range helpers (bodies reconstructed by sibling region workers;
 * declared extern with their FUN_ address in a comment).
 *------------------------------------------------------------------------- */
extern uint64_t sk_alloc(unsigned long size, unsigned long tag);           /* FUN_0036a940 */
extern uint64_t sk_alloc_raw(unsigned long size, unsigned long flags);     /* FUN_0036a804 */
extern void sk_free(uint64_t ptr);                                         /* FUN_0036b118 */
extern void sk_retain(uint64_t obj);                                       /* FUN_0036b270 */
extern void sk_buf_release(uint64_t buf, long long a, long long b);        /* FUN_00012568 */
extern void sk_tb_storage_deinit(uint64_t stg);                            /* FUN_0001fd9c */
extern void sk_tb_msg_init(uint64_t out);                                  /* FUN_000259c0 */
extern uint64_t sk_tb_type_metadata(unsigned long which);                  /* FUN_000286dc */
extern uint64_t sk_tb_witness_method(uint64_t meta);                       /* FUN_00025dcc */
extern void sk_tb_error_report(int *code, uint64_t err, uint64_t meta);/* FUN_003698b0 */
extern cl4_result_t sk_tb_make_error(unsigned long code);                  /* FUN_00019aac */
extern uint64_t sk_tb_field_init(void);                                    /* FUN_000159b8 */
extern void sk_tb_field_retain(uint64_t a, uint64_t b);                    /* FUN_0001590c */
extern void sk_tb_field_release(uint64_t a);                               /* FUN_00015964 */
extern void sk_tb_field_preserve(void);                                    /* FUN_000159d0 */
extern unsigned long sk_tb_append_len(void);                               /* FUN_0001879c */
extern void sk_tb_append_byte(uint64_t msg, uint64_t v);                       /* FUN_000188fc */
extern void sk_tb_append_u16(uint64_t msg, uint64_t v);                    /* FUN_00018b0c */
extern void sk_tb_append_u32(uint64_t msg, uint64_t v);                    /* FUN_00018c70 */
extern void sk_tb_append_u64(uint64_t msg, uint64_t v);                    /* FUN_00018dd4 */
extern void sk_tb_append_char(uint64_t msg, uint64_t v);                        /* FUN_00019000 */
extern void sk_tb_append_short(uint64_t msg, uint64_t v);                       /* FUN_0001910c */
extern void sk_tb_append_flag(uint64_t msg, uint64_t v);                        /* FUN_00019220 */
extern unsigned long sk_tb_read_len(void);                                 /* FUN_00019440 */
extern unsigned long sk_tb_read_len2(void);                                /* FUN_00019620 */
extern void sk_tb_read_preserve(void);                                     /* FUN_00019448 */
extern void sk_tb_read_preserve2(void);                                    /* FUN_00019628 */
extern void sk_tb_append_raw(uint64_t msg, uint64_t buf, unsigned long n); /* FUN_00018650 */
extern void sk_tb_append_flag0(uint64_t msg, uint64_t v);                       /* FUN_000187a4 */
extern void sk_tb_append_value(uint64_t msg, uint64_t v);                  /* FUN_00015be8 */
extern void sk_tb_read_into(uint64_t msg, uint64_t out);                   /* FUN_00015c30 */
extern void sk_tb_read_into2(uint64_t msg, uint64_t out);                  /* FUN_00018878 */
extern void sk_tb_read_u32(uint64_t msg, uint64_t out);                    /* FUN_00019540 */
extern void sk_tb_read_u64(uint64_t msg, uint64_t out);                    /* FUN_00019720 */
extern uint64_t sk_tb_msg_copy_fields(uint64_t a, uint64_t b, uint64_t c, uint64_t d,
                                      uint64_t e, uint64_t f, uint64_t g, uint64_t h); /* FUN_000207e0 */
extern void sk_tb_encode_dispatch(uint64_t a, uint64_t b, uint64_t c, uint64_t d,
                                  uint64_t e, uint64_t f, uint64_t g, uint64_t h); /* FUN_00020134 */
extern uint64_t sk_tb_obj_pair(uint64_t local);                            /* FUN_0004b520 */
extern void sk_tb_obj_pair_free(uint64_t p);                               /* FUN_0004b664 */
extern unsigned long sk_tb_check(uint64_t a, uint64_t b, unsigned long c,
                                 unsigned long d, unsigned long e, int f); /* FUN_003a26e8 */
extern uint64_t sk_tb_encode_core(uint64_t msg, long a, unsigned long n, uint64_t v); /* FUN_00015a44 */
extern void sk_tb_metadata_call(uint64_t meta, uint64_t out, uint64_t arg);/* FUN_003ed2dc */
extern void sk_tb_make_error_obj(uint64_t a, uint64_t b);                  /* FUN_00002534 */
extern int sk_tb_error_set(uint64_t a, uint64_t b, uint64_t c, uint64_t err, int d); /* FUN_00365b6c */
extern void sk_tb_async_dispatch(uint64_t fn, int a, int b);               /* FUN_00408db8 */
extern void sk_tb_async_release(uint64_t obj);                             /* FUN_0040bd24 */
extern void sk_tb_error_push(unsigned long a, unsigned long b);            /* FUN_002acbb8 */
extern void sk_tb_error_log(unsigned long which);                          /* FUN_002a4ab4 */
extern void sk_tb_meta_call(uint64_t meta, uint64_t a, uint64_t b);        /* FUN_0036ffc0 */
extern uint64_t sk_tb_lazy_init(uint64_t what, unsigned long len);         /* FUN_00376820 */
extern uint64_t sk_tb_msg_reset_buf(uint64_t a, uint64_t b, uint64_t c, uint64_t d); /* FUN_00014f90 */
extern uint64_t sk_tb_msg_reset2(uint64_t a, uint64_t b);   /* FUN_00014c08 */
extern void sk_tb_msg_release_buf(uint64_t a, uint64_t b);                 /* FUN_00014f10 */
extern void sk_tb_msg_release_buf2(uint64_t a, uint64_t b);                /* FUN_00014bec */
extern void sk_tb_encode_core2(uint64_t a, uint64_t b);                    /* FUN_00015a44 */
/* Inline read primitives referenced as reader callbacks by the generic read
 * wrappers (bodies live in the 0x18xxx codec region). */
extern void sk_tb_read_u8(long msg, void *out);      /* FUN_00018a4c */
extern void sk_tb_read_u16p(long msg, void *out);    /* FUN_00018be8 */
extern void sk_tb_read_u32p(long msg, void *out);    /* FUN_00018d4c */
extern void sk_tb_read_u64p(long msg, void *out);    /* FUN_00018f38 */

/*-------------------------------------------------------------------------
 * Forward declarations of the local functions referenced by the generic
 * read/append wrappers that precede their definitions.
 *------------------------------------------------------------------------- */
static void sk_tb_msg_deinit(void);
static void sk_tb_msg_read_generic(void (*reader)(long, void *));
static void sk_tb_msg_read_generic16(void (*reader)(long, void *));
static void sk_tb_msg_read_generic32(void (*reader)(long, void *));
static void sk_tb_msg_read_generic64(void (*reader)(long, void *));
static void sk_tb_msg_read_generic2(uint64_t a, uint64_t b, void (*reader)(long, void *));
static void sk_tb_msg_read_generic2_16(uint64_t a, uint64_t b, void (*reader)(long, void *));
static void sk_tb_msg_read_generic2_32(uint64_t a, uint64_t b, void (*reader)(long, void *));
static void sk_tb_msg_read_generic2_64(uint64_t a, uint64_t b, void (*reader)(long, void *));
static void sk_tb_msg_append_generic32(uint64_t v, void (*writer)(uint64_t, uint64_t));
static void sk_tb_msg_append_generic64(uint64_t v, void (*writer)(uint64_t, uint64_t));
static void sk_tb_witness_invoke(uint64_t a, uint64_t b, uint64_t c, uint64_t d, uint64_t meta);
static void sk_tb_witness_invoke2(uint64_t a, uint64_t b, uint64_t meta);
static long sk_tb_witness_method2(unsigned long meta);
static uint64_t sk_tb_msg_reset_status(uint64_t a, uint64_t b);
static long sk_tb_buf_offset_or_trap(unsigned long off, long base, long end);
static void sk_tb_msg_encode_cb0(long obj, uint64_t arg);
static void sk_tb_msg_decode_cb0(long obj);
static uint64_t sk_tb_msg_decode(long msg, long start, long end, uint64_t a, uint64_t b);
static long sk_tb_msg_decode2(uint64_t a, unsigned long obj, uint64_t c, uint64_t d,
                              uint64_t e, uint64_t f, uint64_t g, uint64_t h);
static long sk_tb_witness_fn(unsigned long meta);
static void sk_tb_encode_full_cb0(void);
static void sk_tb_encode_worker(void);
static void sk_tb_encode_async_cont(void);
static void sk_tb_encode_async_done(void);
static void sk_tb_encode_async_retry(void);
static void sk_tb_transport_cb0(void);
static void sk_tb_msg_deinit_cb0(void);

/*-------------------------------------------------------------------------
 * TightbeamMessage object layout (offsets observed from x20-based access):
 *   +0x00 : kind/flags byte (bit 0 = owned buffer)
 *   +0x08 : storage descriptor (tagged: low 61 bits pointer, hi bits type tag)
 *   +0x10 : payload buffer pointer (owned)
 *   +0x18/+0x20/+0x28 : buffer base / length / capacity
 *   +0x30 : wrapper kind byte (0xff = not yet initialized)
 *------------------------------------------------------------------------- */
#define TB_CANARY  ((long)-0x2c8502b44bfffed6L)
#define TB_STG_PTR(x) ((x) & 0x1fffffffffffffffULL)   /* strip Swift tagged-pointer tag bits */
#define TB_STG_TAG(x) ((uint32_t)(((x) >> 32) >> 29)) /* storage tag field */

/* Swift fatal-error sink: reports "Fatal error" then the diagnostic string
 * identified by `diag`, in source `file`, at `line`, and unwinds. noreturn. */
extern void sk_swift_fatal(const char *msg, ...) __attribute__((noreturn)); /* FUN_001afa84 */
/* Stack-scratch canary check: if the sentinel local was overwritten, reports
 * the corruption (takes the overwriting value) and faults. noreturn. */
extern void sk_stack_check(unsigned long v) __attribute__((noreturn));       /* FUN_0011d7e8 */

/*--------------------------------------------------------------------*/
/* FUN_00020d0c @ 0x00020d0c   (est. sk_tb_release_unless_owned)
 * Ghidra: void FUN_00020d0c(a, b, payload, char owned)
 * Releases `payload` unless the caller indicated it is owned (the 4th arg is
 * nonzero). Used by the message wrappers to hand back a buffer only when they
 * are not transferring ownership.
 * Confidence: medium
 * Notes: arg3 is the buffer to free; FUN_0036b118 = free. */
static void sk_tb_release_unless_owned(uint64_t a, uint64_t b, uint64_t payload, int owned)
{
    if (owned != 0) {
        return;
    }
    sk_free((uint64_t)(uintptr_t)payload);  /* FUN_0036b118 */
}

/*--------------------------------------------------------------------*/
/* FUN_00020d20 @ 0x00020d20   (est. sk_tb_msg_copyinit_a)
 * Ghidra: void FUN_00020d20(dst, extra)
 * Copy-initializer: copies the fields of the TightbeamMessage held in the
 * callee-saved register x20 into `dst` via the shared copy helper
 * (FUN_000207e0). The source fields live at x20+0x10..0x38; `extra` is passed
 * through as the final copy argument.
 * Confidence: medium
 * Notes: identical body to FUN_00020d24 (Swift @objc thunk pair). */
static void sk_tb_msg_copyinit_a(uint64_t dst, uint64_t extra)
{
    register char *self asm("x20");
    sk_tb_msg_copy_fields(dst,
                          *(uint64_t *)(self + 0x30),
                          *(uint64_t *)(self + 0x38),
                          *(uint64_t *)(self + 0x10),
                          *(uint64_t *)(self + 0x18),
                          *(uint64_t *)(self + 0x20),
                          *(uint64_t *)(self + 0x28),
                          extra);  /* FUN_000207e0 */
}

/*--------------------------------------------------------------------*/
/* FUN_00020d24 @ 0x00020d24   (est. sk_tb_msg_copyinit_b)
 * Ghidra: void FUN_00020d24(dst, extra)
 * Identical copy-initializer to FUN_00020d20 (the second of the Swift
 * @objc/ABI thunk pair); copies the x20 TightbeamMessage fields into `dst`.
 * Confidence: medium
 * Notes: same callee (FUN_000207e0) and field offsets as FUN_00020d20. */
static void sk_tb_msg_copyinit_b(uint64_t dst, uint64_t extra)
{
    register char *self asm("x20");
    sk_tb_msg_copy_fields(dst,
                          *(uint64_t *)(self + 0x30),
                          *(uint64_t *)(self + 0x38),
                          *(uint64_t *)(self + 0x10),
                          *(uint64_t *)(self + 0x18),
                          *(uint64_t *)(self + 0x20),
                          *(uint64_t *)(self + 0x28),
                          extra);  /* FUN_000207e0 */
}

/*--------------------------------------------------------------------*/
/* FUN_00020d74 @ 0x00020d74   (est. sk_tb_msg_moveassign)
 * Ghidra: undefined8 *FUN_00020d74(dst, src)
 * Move-assignment of a TightbeamMessage: copies the three 8-byte fields and
 * the 1-byte kind field from `src` into `dst`, then releases the buffer that
 * `dst` previously owned (handled by FUN_00020d0c). Returns `dst`.
 * Confidence: medium
 * Notes: src[0..2] and src[3].0 (kind byte); the old dst buffer is freed via
 *   FUN_00020d0c unless it is owned. */
static uint64_t *sk_tb_msg_moveassign(uint64_t *dst, uint64_t *src)
{
    uint64_t old0 = dst[0], old1 = dst[1], old2 = dst[2];
    uint8_t  oldkind = *(uint8_t *)(dst + 3);
    uint64_t s0 = src[0], s1 = src[1], s2 = src[2];
    uint8_t  skind = *(uint8_t *)(src + 3);

    dst[1] = s1;
    dst[0] = s0;
    dst[2] = s2;
    *(uint8_t *)(dst + 3) = skind;
    sk_tb_release_unless_owned(old0, old1, old2, oldkind);
    return dst;
}

/*--------------------------------------------------------------------*/
/* FUN_00020ebc @ 0x00020ebc   (est. sk_tb_status_string)
 * Ghidra: undefined1[16] FUN_00020ebc(uint status)
 * Returns a Swift String (packed {data,flags}) describing a Tightbeam message
 * status/error code: 0="Success", 1="Cloud on sed n"?, 2="Message create
 * failed", 3="Activation failed", 4/0x10 = tagged string, 5="Reply send
 * failed", 7="Message decode failed", 9/10 = UTF-8-inline "result failure"
 * /"Forward failure", else "Unknown n". Codes 6/8/0xb..0xf and >0x10 are
 * reported as "Unknown n".
 * Confidence: medium
 * Notes: builds inline (≤16 byte) Swift small strings and tagged-pointer
 *   strings from s_*_005acfXX addresses; the 0x8000... bit marks a pointer
 *   with the top bit set for Swift string tagging. */
static void sk_tb_status_string(uint32_t status, uint8_t out[16])
{
    uint64_t lo, hi;

    if (status > 0x10) {
        hi = 0xed0000726f727265ULL;         /* "error.." small-string tail */
        lo = 0x206e776f6e6b6e55ULL;         /* "Unknown n" (inline) */
        goto done;
    }
    hi = 0xe700000000000000ULL;             /* "Success" inline */
    lo = 0x73736563637553ULL;
    switch (status) {
    default:
    done:
        *(uint64_t *)(out + 8) = hi;
        *(uint64_t *)(out + 0) = lo;
        return;
    case 1:
        *(uint64_t *)(out + 8) = 0xee00646e65732074ULL;  /* "t send" */
        *(uint64_t *)(out + 0) = 0x6f6e20646c756f43ULL;  /* "Cloud on" */
        return;
    case 2:  /* "Message create failed" (tagged) */
        *(uint64_t *)(out + 8) = (uint64_t)((char *)0x005acf30 + -0x20) | 0x8000000000000000ULL;
        *(uint64_t *)(out + 0) = 0xd000000000000015ULL;
        return;
    case 3:  /* "Activation failed" (tagged) */
        *(uint64_t *)(out + 8) = (uint64_t)((char *)0x005acf10 + -0x20) | 0x8000000000000000ULL;
        *(uint64_t *)(out + 0) = 0xd000000000000011ULL;
        return;
    case 4:
        *(uint64_t *)(out + 8) = 0x80000000005aced0ULL;  /* "l buffer pointer" */
        *(uint64_t *)(out + 0) = 0xd000000000000016ULL;
        return;
    case 5:  /* "Reply send failed" (tagged) */
        *(uint64_t *)(out + 8) = (uint64_t)((char *)0x005aced0 + -0x20) | 0x8000000000000000ULL;
        *(uint64_t *)(out + 0) = 0xd000000000000011ULL;
        return;
    case 6: case 8: case 0xb: case 0xc: case 0xd: case 0xe: case 0xf:
        hi = 0xed0000726f727265ULL;
        lo = 0x206e776f6e6b6e55ULL;
        goto done;
    case 7:  /* "Message decode failed" (tagged) */
        *(uint64_t *)(out + 8) = (uint64_t)((char *)0x005aceb0 + -0x20) | 0x8000000000000000ULL;
        *(uint64_t *)(out + 0) = 0xd000000000000015ULL;
        return;
    case 9:
        *(uint64_t *)(out + 8) = 0xec0000006572756cULL;  /* "lure" inline */
        *(uint64_t *)(out + 0) = 0x6961662072657355ULL;  /* "User fail" */
        return;
    case 10:
        *(uint64_t *)(out + 8) = 0xef6572756c696166ULL;  /* "failure" */
        *(uint64_t *)(out + 0) = 0x2064726177726f46ULL;  /* "Forward " */
        return;
    case 0x10:
        *(uint64_t *)(out + 8) = 0x80000000005ace70ULL;  /* "l buffer pointer" */
        *(uint64_t *)(out + 0) = 0xd00000000000001eULL;
        return;
    }
}

/*--------------------------------------------------------------------*/
/* FUN_000210d8 @ 0x000210d8   (est. sk_tb_decoder_init)
 * Ghidra: undefined1[16] FUN_000210d8(long self)
 * Initializes a TightbeamDecoder from a TightbeamMessage: makes an error value
 * (FUN_00019aac(0x13f)), and if the buffer at self+0x10 is valid (<0x40 error
 * marker), sets up the decoder source (FUN_00377dcc) and registers the message
 * (FUN_00368da8) with a pair `{buffer, 0}`. On failure the error code 0x3f is
 * reported in the hi word.
 * Confidence: medium
 * Notes: FUN_00377dcc/FUN_00368da8 are decoder-side init helpers. */
static cl4_result_t sk_tb_decoder_init(long self)
{
    cl4_result_t r;
    uint64_t buf = 0;
    uint64_t err = 0;

    r = sk_tb_make_error(0x13f);                       /* FUN_00019aac */
    buf = r.lo;
    if (r.hi < 0x40) {
        r = sk_tb_make_error(0x13f);                   /* FUN_00377dcc(0x13f, self+0x10) */
        buf = r.lo;
        if (r.hi < 0x40) {
            sk_tb_field_init();                        /* FUN_00368da8(self, 0, 2, &pair) */
            buf = 0;
            err = 0;
            goto out;
        }
    }
    err = 0x3f;
out:
    return (cl4_result_t){ .lo = buf, .hi = err };
}

/*--------------------------------------------------------------------*/
/* FUN_00021260 @ 0x00021260   (est. sk_tb_encode_varint)
 * Ghidra: void FUN_00021260(uint *dst, uint value, uint flags, long self)
 * Encodes `value` into `dst` using a variable-width integer scheme driven by
 * the current buffer length (uVar4 = width base, min 4) and `flags`. Small
 * values (<0xff) are stored as a negated single byte; larger values are stored
 * as 1/2/4-byte little-endian with a width marker byte appended after the
 * payload. `self`+0x10+(-8)+0x40 provides the width budget.
 * Confidence: low
 * Notes: variable-length integer encoder; FUN_00021260 is the value-write and
 *   the marker-size selection (bVar6) mirrors the decoder's read side. */
static void sk_tb_encode_varint(uint32_t *dst, uint32_t value, uint32_t flags, long self)
{
    unsigned long width;
    long w1;
    uint32_t w;
    uint16_t m2;
    uint32_t u2;
    uint8_t m;
    int i7;

    width = *(unsigned long *)(*(long *)(*(long *)(self + 0x10) + -8) + 0x40);
    if (width < 5) {
        width = 4;
    }
    w1 = width + 1;
    w = (uint32_t)w1;
    if (flags < 0xff) {
        m = 0;
    } else if (w < 4) {
        u2 = (((flags + ~(-1 << (w << 3 & 0x1f))) - 0xfe) >> ((w << 3) & 0x1f)) + 1;
        m = 2;
        if (0xffff < u2) {
            m = 4;
        }
        if (u2 < 0x100) {
            m = (uint8_t)(1 < u2);
        }
    } else {
        m = 1;
    }
    if (value < 0xff) {
        if (m < 2) {
            if (m != 0) {
                *(uint8_t *)((long)dst + w1) = 0;
            }
        } else if (m == 2) {
            *(uint16_t *)((long)dst + w1) = 0;
        } else {
            *(uint32_t *)((long)dst + w1) = 0;
        }
        if (value != 0) {
            *(char *)((long)dst + width) = -(char)value;
        }
    } else {
        value = value - 0xff;
        if (w < 4) {
            i7 = (value >> (w << 3 & 0x1f)) + 1;
            if (w != 0) {
                u2 = value & (~(-1 << (w << 3 & 0x1f)) ^ 0xffffffffU);
                sk_tb_encode_dispatch((uint64_t)(uintptr_t)dst, (uint64_t)w1, 0, 0, 0, 0, 0, 0); /* FUN_00114330 thunk */
                m2 = (uint16_t)u2;
                if (w == 3) {
                    *(uint16_t *)dst = m2;
                    *(char *)((long)dst + 2) = (char)(u2 >> 0x10);
                } else if (w == 2) {
                    *(uint16_t *)dst = m2;
                } else {
                    *(char *)dst = (char)value;
                }
            }
        } else {
            sk_tb_encode_dispatch((uint64_t)(uintptr_t)dst, (uint64_t)w1, 0, 0, 0, 0, 0, 0); /* FUN_00114330 thunk */
            *dst = value;
            i7 = 1;
        }
        if (m < 2) {
            if (m != 0) {
                *(char *)((long)dst + w1) = (char)i7;
            }
        } else if (m == 2) {
            *(short *)((long)dst + w1) = (short)i7;
        } else {
            *(int *)((long)dst + w1) = i7;
        }
    }
}

/*--------------------------------------------------------------------*/
/* FUN_0002142c @ 0x0002142c   (est. sk_tb_lazy_once)
 * Ghidra: void FUN_0002142c(void)
 * One-time lazy initializer: if the static token `s___TEXT_0064c258` is
 * nonzero it is already done; otherwise it is set to the result of building
 * the value at DAT_004ed400 of length 0x6776f0 (FUN_00376820). This is the
 * classic Swift lazy global initialization guard.
 * Confidence: medium
 * Notes: static token s___TEXT_0064c258; constructor FUN_00376820. */
static void sk_tb_lazy_once(void)
{
    extern uint64_t sk_tb_lazy_token;   /* s___TEXT_0064c258 */
    extern uint8_t  sk_tb_lazy_value;   /* DAT_004ed400 */

    if (sk_tb_lazy_token != 0) {
        return;
    }
    sk_tb_lazy_token = (uint64_t)sk_tb_lazy_init((uint64_t)(uintptr_t)&sk_tb_lazy_value, 0x6776f0); /* FUN_00376820 */
}

/*--------------------------------------------------------------------*/
/* FUN_00021480 @ 0x00021480   (est. sk_tb_metadata_invoke)
 * Ghidra: void FUN_00021480(a, b, c, d, e)
 * Invokes a Tightbeam metadata/closure: stacks {b,c,d} and calls the shared
 * metadata call helper (FUN_0036ffc0) with `a` and the stacked tuple. This is
 * a Swift closure-forwarding shim.
 * Confidence: medium
 * Notes: FUN_0036ffc0 = sk_tb_meta_call. */
static void sk_tb_metadata_invoke(uint64_t a, uint64_t b, uint64_t c, uint64_t d, uint64_t e)
{
    uint64_t tup[3] = { b, c, d };
    sk_tb_meta_call(a, (uint64_t)(uintptr_t)tup, e);  /* FUN_0036ffc0 */
}

/*--------------------------------------------------------------------*/
/* FUN_000214b0 @ 0x000214b0   (est. sk_tb_msg_copy_wrap)
 * Ghidra: void FUN_000214b0(dst, src)
 * Shallow-copies a TightbeamMessage wrapper (49 bytes: kind byte at +0,
 * storage +0x8, buffer fields +0x10..+0x30) from `src` into `dst`. The byte at
 * src[0] is masked to its low bit.
 * Confidence: medium
 * Notes: identical to FUN_00024068. */
static void sk_tb_msg_copy_wrap(uint8_t *dst, uint8_t *src)
{
    dst[0] = src[0] & 1;
    *(uint64_t *)(dst + 0x10) = *(uint64_t *)(src + 0x10);
    *(uint64_t *)(dst + 0x08) = *(uint64_t *)(src + 0x08);
    *(uint64_t *)(dst + 0x20) = *(uint64_t *)(src + 0x20);
    *(uint64_t *)(dst + 0x18) = *(uint64_t *)(src + 0x18);
    *(uint64_t *)(dst + 0x28) = *(uint64_t *)(src + 0x28);
    dst[0x30] = src[0x30];
}

/*--------------------------------------------------------------------*/
/* FUN_000214e0 @ 0x000214e0   (est. sk_tb_msg_ensure_payload)
 * Ghidra: void FUN_000214e0(void)
 * Ensures the TightbeamMessage in x20 has a payload buffer: if self+0x10 is
 * non-null, preserves it (FUN_000159d0) and returns; otherwise it traps with a
 * fatal error (TightbeamMessage, diagnostic 0x93, "already unwrapped" style,
 * error 0x22).
 * Confidence: medium
 * Notes: FUN_000159d0 = sk_tb_field_preserve. */
static void sk_tb_msg_ensure_payload(void)
{
    register char *self asm("x20");
    if (*(long *)(self + 0x10) != 0) {
        sk_tb_field_preserve();  /* FUN_000159d0 */
        return;
    }
    sk_swift_fatal("Fatal error", 0xb, 2, 0xd000000000000022ULL,
                   (uint64_t)((char *)0x005acf60 + -0x20) | 0x8000000000000000ULL,
                   0x005acf50, 0x20, 2, 0x93, 0); /* FUN_001afa84 */
}

/*--------------------------------------------------------------------*/
/* FUN_00021554 @ 0x00021554   (est. sk_tb_msg_unwrap_buffer)
 * Ghidra: undefined8 FUN_00021554(ulong start, long end)
 * Unwraps the TightbeamMessage buffer region [start,end) into the message:
 * validates the wrapper is unwrapped (self+0x10 non-null else fatal 0x93), and
 * if the storage kind is 4, copies `end-start` bytes from the storage payload
 * into the message via the memcpy shim (FUN_00117cc4), advancing the storage
 * read cursor. Bounds are checked against the storage length; overflow traps
 * via SoftwareBreakpoint(0x5519). Returns the copied base.
 * Confidence: medium
 * Notes: FUN_00117cc4 = memcpy; SoftwareBreakpoint(0x5519) on range overflow. */
static uint64_t sk_tb_msg_unwrap_buffer(unsigned long start, long end)
{
    register char *self asm("x20");
    int *stg;
    uint64_t *s;
    unsigned long n, sp, len, base, dst;
    uint64_t r;

    if (start == 0) {
        sk_swift_fatal("Fatal error", 0xb, 2, 0xd000000000000028ULL,
                       (uint64_t)((char *)0x005acfe0 + -0x20) | 0x8000000000000000ULL,
                       0x005acfb0, 0x20, 2, 0x2e, 0); /* FUN_001afa84 */
    }
    stg = *(int **)(self + 0x10);
    if (stg == (int *)0) {
        sk_swift_fatal("Fatal error", 0xb, 2, 0xd000000000000022ULL,
                       (uint64_t)((char *)0x005acf80 + -0x20) | 0x8000000000000000ULL,
                       0x005acf50, 0x20, 2, 0x93, 0); /* FUN_001afa84 */
    }
    n = (unsigned long)end - start;
    if (*stg == 4) {
        s = (uint64_t *)(stg + 0x14);
        len = s[3];
        if (len == 0) return 1;
        sp = s[2];
        if (!((uint64_t)sp + n < sp)) {   /* CARRY8(sp, n) */
            if (sp + n <= len) {
                base = s[0];
                s[2] = sp + n;
                dst = base + sp;
                if ((dst <= base + len && base <= dst) && (n <= len - sp)) {
                    r = (uint64_t)sk_alloc(dst, n);  /* FUN_00117cc4 memcpy shim (param order) */
                    if (start <= start + n) {
                        return r;
                    }
                }
                __builtin_trap();  /* SoftwareBreakpoint(0x5519, 0x18768) */
            }
            return 1;
        }
    } else {
        sk_tb_error_log(0);  /* FUN_004b0ea4 */
        return 1;
    }
    return 1;
}

/*--------------------------------------------------------------------*/
/* FUN_0002161c @ 0x0002161c   (est. sk_tb_msg_encode_entry)
 * Ghidra: undefined8 FUN_0002161c(a, b, c, d)
 * Entry point that encodes a TightbeamMessage: calls the encode worker
 * (FUN_0002286c) with the x20 message and the four arguments, and on a nonzero
 * error status builds an error result (FUN_003698b0) and reports it.
 * Confidence: medium
 * Notes: FUN_0065a550 is the error type metadata. */
static uint64_t sk_tb_msg_encode_entry(uint64_t a, uint64_t b, uint64_t c, uint64_t d)
{
    register char *self asm("x20");
    uint64_t r;
    int code;
    cl4_result_t err;

    r = sk_tb_msg_copy_fields((uint64_t)*(uintptr_t *)(self + 0x10), a, b, c,
                              d, 0, 0, 0);   /* FUN_0002286c */
    code = (int)r;
    if (code != 0) {
        err = sk_tb_make_error(0);                   /* FUN_00019aac */
        sk_tb_error_report(&code, err.lo, 0x0065a550ULL);  /* FUN_003698b0 */
    }
    return r;
}

/*--------------------------------------------------------------------*/
/* FUN_00021694 @ 0x00021694   (est. sk_tb_msg_decode_apply)
 * Ghidra: undefined4 FUN_00021694(self, code *callback)
 * Decodes the TightbeamMessage and applies the result to the Swift `callback`
 * closure: initializes a fresh wrapper (FUN_000259c0), copies its fields, and
 * invokes `callback` with the unpacked wrapper. Then destroys the scratch
 * message (FUN_00025704) and returns 0.
 * Confidence: medium
 * Notes: FUN_00025704 is the message deinit; callback is invoked via (*param_2).
 */
static uint32_t sk_tb_msg_decode_apply(uint64_t self_arg, void (*callback)(uint8_t *))
{
    uint8_t  stackbuf[0x40];
    uint8_t *w = (uint8_t *)(((uintptr_t)stackbuf + 0xf) & ~0xfULL);
    uint8_t  tmp[8];

    sk_tb_msg_init((uint64_t)(uintptr_t)tmp);  /* FUN_000259c0 */
    w[0] = tmp[0];
    *(uint64_t *)(w + 0x10) = *(uint64_t *)(tmp + 0x10);
    *(uint64_t *)(w + 0x08) = *(uint64_t *)(tmp + 8);
    *(uint64_t *)(w + 0x20) = *(uint64_t *)(tmp + 0x20);
    *(uint64_t *)(w + 0x18) = *(uint64_t *)(tmp + 0x18);
    *(uint64_t *)(w + 0x28) = *(uint64_t *)(tmp + 0x28);
    callback(w);
    sk_tb_msg_deinit();  /* FUN_00025704 */
    return 0;
}

/*--------------------------------------------------------------------*/
/* FUN_00021738 @ 0x00021738   (est. sk_tb_msg_read_byte_wrap)
 * Ghidra: void FUN_00021738(void)
 * Reads a single byte out of the TightbeamMessage via the reader helper
 * (FUN_00018878), guarding against an unwrapped message (fatal 0x93) and
 * validating the stack canary.
 * Confidence: medium */
static void sk_tb_msg_read_byte_wrap(void)
{
    register char *self asm("x20");
    long canary = TB_CANARY;
    uint8_t out = 0;

    if (*(long *)(self + 0x10) == 0) {
        sk_swift_fatal("Fatal error", 0xb, 2, 0xd000000000000022ULL,
                       (uint64_t)((char *)0x005acf60 + -0x20) | 0x8000000000000000ULL,
                       0x005acf50, 0x20, 2, 0x93, 0); /* FUN_001afa84 */
    }
    sk_tb_read_into2((uint64_t)*(long *)(self + 0x10), (uint64_t)(uintptr_t)&out);  /* FUN_00018878 */
    if (canary == TB_CANARY) {
        return;
    }
    sk_stack_check(out);  /* FUN_0011d7e8 */
}

/*--------------------------------------------------------------------*/
/* FUN_000217e4 @ 0x000217e4   (est. sk_tb_msg_read_byte)
 * Ghidra: void FUN_000217e4(void)
 * Reads a single byte from the message using the read primitive FUN_00018a4c.
 * Confidence: medium */
static void sk_tb_msg_read_byte(void)
{
    sk_tb_msg_read_generic(sk_tb_read_u8);  /* FUN_000219c4(FUN_00018a4c) */
}

/*--------------------------------------------------------------------*/
/* FUN_00021844 @ 0x00021844   (est. sk_tb_msg_read_u16)
 * Ghidra: void FUN_00021844(void)
 * Reads a 16-bit value using the read primitive FUN_00018be8.
 * Confidence: medium */
static void sk_tb_msg_read_u16(void)
{
    sk_tb_msg_read_generic16(sk_tb_read_u16p);  /* FUN_00021ad8(FUN_00018be8) */
}

/*--------------------------------------------------------------------*/
/* FUN_000218a4 @ 0x000218a4   (est. sk_tb_msg_read_u32)
 * Ghidra: void FUN_000218a4(void)
 * Reads a 32-bit value using the read primitive FUN_00018d4c.
 * Confidence: medium */
static void sk_tb_msg_read_u32(void)
{
    sk_tb_msg_read_generic32(sk_tb_read_u32p);  /* FUN_00021bec(FUN_00018d4c) */
}

/*--------------------------------------------------------------------*/
/* FUN_00021904 @ 0x00021904   (est. sk_tb_msg_read_u64)
 * Ghidra: void FUN_00021904(void)
 * Reads a 64-bit value using the read primitive FUN_00018f38.
 * Confidence: medium */
static void sk_tb_msg_read_u64(void)
{
    sk_tb_msg_read_generic64(sk_tb_read_u64p);  /* FUN_00021d00(FUN_00018f38) */
}

/*--------------------------------------------------------------------*/
/* FUN_00021964 @ 0x00021964   (est. sk_tb_msg_read_value8)
 * Ghidra: void FUN_00021964(void)
 * Reads a value using the inline read primitive at 0x19088.
 * Confidence: low */
static void sk_tb_msg_read_value8(void)
{
    sk_tb_msg_read_generic((void *)0x19088);  /* FUN_000219c4(0x19088) */
}

/*--------------------------------------------------------------------*/
/* FUN_000219c4 @ 0x000219c4   (est. sk_tb_msg_read_generic)
 * Ghidra: void FUN_000219c4(code *reader)
 * Generic message read: verifies the wrapper in x20 is unwrapped (fatal 0x93
 * otherwise), calls `reader`(payload, &scratch), and if the canary was not
 * overwritten returns; otherwise reports the corruption via the stack-check
 * handler with the read value.
 * Confidence: medium
 * Notes: the read primitives write into a 1/2/4/8-byte scratch (the size varies
 *   by the wrapper); the canary sentinel is -0x2c8502b44bfffed6. */
static void sk_tb_msg_read_generic(void (*reader)(long, void *))
{
    register char *self asm("x20");
    long canary = TB_CANARY;
    uint8_t scratch = 0;

    if (*(long *)(self + 0x10) == 0) {
        sk_swift_fatal("Fatal error", 0xb, 2, 0xd000000000000022ULL,
                       (uint64_t)((char *)0x005acf60 + -0x20) | 0x8000000000000000ULL,
                       0x005acf50, 0x20, 2, 0x93, 0); /* FUN_001afa84 */
    }
    reader(*(long *)(self + 0x10), &scratch);
    if (canary == TB_CANARY) {
        return;
    }
    sk_stack_check(scratch);  /* FUN_0011d7e8 */
}

/*--------------------------------------------------------------------*/
/* FUN_00021a78 @ 0x00021a78   (est. sk_tb_msg_read_value16)
 * Ghidra: void FUN_00021a78(void)
 * Reads a value using the inline read primitive at 0x19198 (16-bit scratch).
 * Confidence: low */
static void sk_tb_msg_read_value16(void)
{
    sk_tb_msg_read_generic16((void *)0x19198);  /* FUN_00021ad8(0x19198) */
}

/*--------------------------------------------------------------------*/
/* FUN_00021ad8 @ 0x00021ad8   (est. sk_tb_msg_read_generic16)
 * Ghidra: void FUN_00021ad8(code *reader)
 * Generic 16-bit message read with unwrap guard and canary check.
 * Confidence: medium */
static void sk_tb_msg_read_generic16(void (*reader)(long, void *))
{
    register char *self asm("x20");
    long canary = TB_CANARY;
    uint16_t scratch = 0;

    if (*(long *)(self + 0x10) == 0) {
        sk_swift_fatal("Fatal error", 0xb, 2, 0xd000000000000022ULL,
                       (uint64_t)((char *)0x005acf60 + -0x20) | 0x8000000000000000ULL,
                       0x005acf50, 0x20, 2, 0x93, 0); /* FUN_001afa84 */
    }
    reader(*(long *)(self + 0x10), &scratch);
    if (canary == TB_CANARY) {
        return;
    }
    sk_stack_check(scratch);  /* FUN_0011d7e8 */
}

/*--------------------------------------------------------------------*/
/* FUN_00021b8c @ 0x00021b8c   (est. sk_tb_msg_read_value32)
 * Ghidra: void FUN_00021b8c(void)
 * Reads a value using the inline read primitive at 0x192ac (32-bit scratch).
 * Confidence: low */
static void sk_tb_msg_read_value32(void)
{
    sk_tb_msg_read_generic32((void *)0x192ac);  /* FUN_00021bec(0x192ac) */
}

/*--------------------------------------------------------------------*/
/* FUN_00021bec @ 0x00021bec   (est. sk_tb_msg_read_generic32)
 * Ghidra: void FUN_00021bec(code *reader)
 * Generic 32-bit message read with unwrap guard and canary check.
 * Confidence: medium */
static void sk_tb_msg_read_generic32(void (*reader)(long, void *))
{
    register char *self asm("x20");
    long canary = TB_CANARY;
    uint32_t scratch = 0;

    if (*(long *)(self + 0x10) == 0) {
        sk_swift_fatal("Fatal error", 0xb, 2, 0xd000000000000022ULL,
                       (uint64_t)((char *)0x005acf60 + -0x20) | 0x8000000000000000ULL,
                       0x005acf50, 0x20, 2, 0x93, 0); /* FUN_001afa84 */
    }
    reader(*(long *)(self + 0x10), &scratch);
    if (canary == TB_CANARY) {
        return;
    }
    sk_stack_check(scratch);  /* FUN_0011d7e8 */
}

/*--------------------------------------------------------------------*/
/* FUN_00021ca0 @ 0x00021ca0   (est. sk_tb_msg_read_value64)
 * Ghidra: void FUN_00021ca0(void)
 * Reads a value using the inline read primitive at 0x193c0 (64-bit scratch).
 * Confidence: low */
static void sk_tb_msg_read_value64(void)
{
    sk_tb_msg_read_generic64((void *)0x193c0);  /* FUN_00021d00(0x193c0) */
}

/*--------------------------------------------------------------------*/
/* FUN_00021d00 @ 0x00021d00   (est. sk_tb_msg_read_generic64)
 * Ghidra: void FUN_00021d00(code *reader)
 * Generic 64-bit message read with unwrap guard and canary check.
 * Confidence: medium */
static void sk_tb_msg_read_generic64(void (*reader)(long, void *))
{
    register char *self asm("x20");
    long canary = TB_CANARY;
    uint64_t scratch = 0;

    if (*(long *)(self + 0x10) == 0) {
        sk_swift_fatal("Fatal error", 0xb, 2, 0xd000000000000022ULL,
                       (uint64_t)((char *)0x005acf60 + -0x20) | 0x8000000000000000ULL,
                       0x005acf50, 0x20, 2, 0x93, 0); /* FUN_001afa84 */
    }
    reader(*(long *)(self + 0x10), &scratch);
    if (canary == TB_CANARY) {
        return;
    }
    sk_stack_check(scratch);  /* FUN_0011d7e8 */
}

/*--------------------------------------------------------------------*/
/* FUN_00021db4 @ 0x00021db4   (est. sk_tb_msg_read_u32b)
 * Ghidra: void FUN_00021db4(void)
 * Reads a 32-bit value via FUN_00019540 with unwrap guard and canary check.
 * Confidence: medium */
static void sk_tb_msg_read_u32b(void)
{
    register char *self asm("x20");
    long canary = TB_CANARY;
    uint32_t scratch = 0;

    if (*(long *)(self + 0x10) == 0) {
        sk_swift_fatal("Fatal error", 0xb, 2, 0xd000000000000022ULL,
                       (uint64_t)((char *)0x005acf60 + -0x20) | 0x8000000000000000ULL,
                       0x005acf50, 0x20, 2, 0x93, 0); /* FUN_001afa84 */
    }
    sk_tb_read_u32((uint64_t)*(long *)(self + 0x10), (uint64_t)(uintptr_t)&scratch);  /* FUN_00019540 */
    if (canary == TB_CANARY) {
        return;
    }
    sk_stack_check(scratch);  /* FUN_0011d7e8 */
}

/*--------------------------------------------------------------------*/
/* FUN_00021e60 @ 0x00021e60   (est. sk_tb_msg_read_u64b)
 * Ghidra: void FUN_00021e60(void)
 * Reads a 64-bit value via FUN_00019720 with unwrap guard and canary check.
 * Confidence: medium */
static void sk_tb_msg_read_u64b(void)
{
    register char *self asm("x20");
    long canary = TB_CANARY;
    uint64_t scratch = 0;

    if (*(long *)(self + 0x10) == 0) {
        sk_swift_fatal("Fatal error", 0xb, 2, 0xd000000000000022ULL,
                       (uint64_t)((char *)0x005acf60 + -0x20) | 0x8000000000000000ULL,
                       0x005acf50, 0x20, 2, 0x93, 0); /* FUN_001afa84 */
    }
    sk_tb_read_u64((uint64_t)*(long *)(self + 0x10), (uint64_t)(uintptr_t)&scratch);  /* FUN_00019720 */
    if (canary == TB_CANARY) {
        return;
    }
    sk_stack_check(scratch);  /* FUN_0011d7e8 */
}

/*--------------------------------------------------------------------*/
/* FUN_00021f0c @ 0x00021f0c   (est. sk_tb_msg_read_value)
 * Ghidra: void FUN_00021f0c(void)
 * Reads a value via FUN_00015c30 with unwrap guard and canary check.
 * Confidence: medium */
static void sk_tb_msg_read_value(void)
{
    register char *self asm("x20");
    long canary = TB_CANARY;
    uint64_t scratch = 0;

    if (*(long *)(self + 0x10) == 0) {
        sk_swift_fatal("Fatal error", 0xb, 2, 0xd000000000000022ULL,
                       (uint64_t)((char *)0x005acf60 + -0x20) | 0x8000000000000000ULL,
                       0x005acf50, 0x20, 2, 0x93, 0); /* FUN_001afa84 */
    }
    sk_tb_read_into((uint64_t)*(long *)(self + 0x10), (uint64_t)(uintptr_t)&scratch);  /* FUN_00015c30 */
    if (canary == TB_CANARY) {
        return;
    }
    sk_stack_check(scratch);  /* FUN_0011d7e8 */
}

/*--------------------------------------------------------------------*/
/* FUN_00021fb8 @ 0x00021fb8   (est. sk_tb_decoder_fatal_dump)
 * Ghidra: void FUN_00021fb8(void)
 * TightbeamDecoder failure path: destroys the scratch message (FUN_00025704)
 * and traps with a fatal error (diagnostic 0x8f, decoder context) after
 * forwarding the six decoder fields held in the x20 wrapper.
 * Confidence: medium
 * Notes: FUN_00025704 is the message deinit; diagnostic 0x8f/error 0. */
static void sk_tb_decoder_fatal_dump(void)
{
    register uint64_t *self asm("x20");
    uint64_t f0 = self[0], f1 = self[1], f2 = self[2], f3 = self[3];
    uint64_t f4 = self[4], f5 = self[5];
    uint8_t  f6 = *(uint8_t *)(self + 6);

    sk_tb_msg_deinit();  /* FUN_00025704 */
    sk_swift_fatal("Fatal error", 0xb, 2, 0, 0xe000000000000000ULL,
                   0x005acfb0, 0x20, 2, 0x8f, 0,
                   f0, f1, f2, f3, f4, f5, f6); /* FUN_001afa84 */
}

/*--------------------------------------------------------------------*/
/* FUN_00022028 @ 0x00022028   (est. sk_tb_decoder_read_out)
 * Ghidra: void FUN_00022028(out, b, c, int *err)
 * Reads a value out of the TightbeamDecoder: computes the decode status
 * (FUN_000240e4); if the status register is 0, copies the six decoder fields
 * from the x20 wrapper into `out`; otherwise destroys the scratch message and
 * writes the status into `*err`.
 * Confidence: medium
 * Notes: FUN_000240e4 = sk_tb_msg_reset status; the field block is 0x31 bytes. */
static void sk_tb_decoder_read_out(uint8_t *out, uint64_t b, uint64_t c, uint32_t *err)
{
    register uint8_t *self asm("x20");
    register long    status asm("x21");
    uint32_t st;

    st = (uint32_t)sk_tb_msg_reset_status(0, 0);  /* FUN_000240e4 */
    if (status == 0) {
        out[0] = self[0x30];
        *(uint64_t *)(out + 0x10) = *(uint64_t *)(self + 0x10);
        *(uint64_t *)(out + 0x08) = *(uint64_t *)(self + 0x08);
        *(uint64_t *)(out + 0x20) = *(uint64_t *)(self + 0x20);
        *(uint64_t *)(out + 0x18) = *(uint64_t *)(self + 0x18);
        *(uint64_t *)(out + 0x28) = *(uint64_t *)(self + 0x28);
        out[0x30] = self[0x30];
    } else {
        sk_tb_msg_deinit();  /* FUN_00025704 */
        *err = st;
    }
}

/*--------------------------------------------------------------------*/
/* FUN_000220d4 @ 0x000220d4   (est. sk_tb_decoder_deinit_trap)
 * Ghidra: void FUN_000220d4(long self)
 * TightbeamDecoder deinit trap: calls the metadata destructor (the indirect
 * call at *(self+(-8)+8)), then traps with a fatal error (diagnostic 0xae,
 * decoder context, error 0x55).
 * Confidence: medium */
static void sk_tb_decoder_deinit_trap(long self)
{
    (*(void (**)(void))(*(long *)(self + -8) + 8))();
    sk_swift_fatal("Fatal error", 0xb, 2, 0xd000000000000055ULL,
                   (uint64_t)((char *)0x005acff0 + -0x20) | 0x8000000000000000ULL,
                   0x005acfb0, 0x20, 2, 0xae, 0); /* FUN_001afa84 */
}

/*--------------------------------------------------------------------*/
/* FUN_00022158 @ 0x00022158   (est. sk_tb_decode_byte)
 * Ghidra: void FUN_00022158(a, b)
 * Decode a single byte via FUN_00022338 with read primitive FUN_00018a4c.
 * Confidence: medium */
static void sk_tb_decode_byte(uint64_t a, uint64_t b)
{
    sk_tb_msg_read_generic2(a, b, sk_tb_read_u8);  /* FUN_00022338(a,b,FUN_00018a4c) */
}

/*--------------------------------------------------------------------*/
/* FUN_000221b8 @ 0x000221b8   (est. sk_tb_decode_u16)
 * Ghidra: void FUN_000221b8(a, b)
 * Decode a 16-bit value via FUN_00022448 with read primitive FUN_00018be8.
 * Confidence: medium */
static void sk_tb_decode_u16(uint64_t a, uint64_t b)
{
    sk_tb_msg_read_generic2_16(a, b, sk_tb_read_u16p);  /* FUN_00022448(a,b,FUN_00018be8) */
}

/*--------------------------------------------------------------------*/
/* FUN_00022218 @ 0x00022218   (est. sk_tb_decode_u32)
 * Ghidra: void FUN_00022218(a, b)
 * Decode a 32-bit value via FUN_00022558 with read primitive FUN_00018d4c.
 * Confidence: medium */
static void sk_tb_decode_u32(uint64_t a, uint64_t b)
{
    sk_tb_msg_read_generic2_32(a, b, sk_tb_read_u32p);  /* FUN_00022558(a,b,FUN_00018d4c) */
}

/*--------------------------------------------------------------------*/
/* FUN_00022278 @ 0x00022278   (est. sk_tb_decode_u64)
 * Ghidra: void FUN_00022278(a, b)
 * Decode a 64-bit value via FUN_00022668 with read primitive FUN_00018f38.
 * Confidence: medium */
static void sk_tb_decode_u64(uint64_t a, uint64_t b)
{
    sk_tb_msg_read_generic2_64(a, b, sk_tb_read_u64p);  /* FUN_00022668(a,b,FUN_00018f38) */
}

/*--------------------------------------------------------------------*/
/* FUN_000222d8 @ 0x000222d8   (est. sk_tb_decode_value8)
 * Ghidra: void FUN_000222d8(a, b)
 * Decode a value via FUN_00022338 with inline read primitive 0x19088.
 * Confidence: low */
static void sk_tb_decode_value8(uint64_t a, uint64_t b)
{
    sk_tb_msg_read_generic2(a, b, (void *)0x19088);  /* FUN_00022338(a,b,0x19088) */
}

/*--------------------------------------------------------------------*/
/* FUN_00022338 @ 0x00022338   (est. sk_tb_msg_read_generic2)
 * Ghidra: void FUN_00022338(a, b, code *reader)
 * Two-argument generic message read with unwrap guard and canary check.
 * Confidence: medium */
static void sk_tb_msg_read_generic2(uint64_t a, uint64_t b, void (*reader)(long, void *))
{
    register char *self asm("x20");
    long canary = TB_CANARY;
    uint8_t scratch = 0;

    if (*(long *)(self + 0x10) == 0) {
        sk_swift_fatal("Fatal error", 0xb, 2, 0xd000000000000022ULL,
                       (uint64_t)((char *)0x005acf60 + -0x20) | 0x8000000000000000ULL,
                       0x005acf50, 0x20, 2, 0x93, 0); /* FUN_001afa84 */
    }
    reader(*(long *)(self + 0x10), &scratch);
    if (canary == TB_CANARY) {
        return;
    }
    sk_stack_check(scratch);  /* FUN_0011d7e8 */
}

/*--------------------------------------------------------------------*/
/* FUN_000223e8 @ 0x000223e8   (est. sk_tb_decode_value16)
 * Ghidra: void FUN_000223e8(a, b)
 * Decode a value via FUN_00022448 with inline read primitive 0x19198.
 * Confidence: low */
static void sk_tb_decode_value16(uint64_t a, uint64_t b)
{
    sk_tb_msg_read_generic2_16(a, b, (void *)0x19198);  /* FUN_00022448(a,b,0x19198) */
}

/*--------------------------------------------------------------------*/
/* FUN_00022448 @ 0x00022448   (est. sk_tb_msg_read_generic2_16)
 * Ghidra: void FUN_00022448(a, b, code *reader)
 * Two-argument generic 16-bit message read with unwrap guard and canary check.
 * Confidence: medium */
static void sk_tb_msg_read_generic2_16(uint64_t a, uint64_t b, void (*reader)(long, void *))
{
    register char *self asm("x20");
    long canary = TB_CANARY;
    uint16_t scratch = 0;

    if (*(long *)(self + 0x10) == 0) {
        sk_swift_fatal("Fatal error", 0xb, 2, 0xd000000000000022ULL,
                       (uint64_t)((char *)0x005acf60 + -0x20) | 0x8000000000000000ULL,
                       0x005acf50, 0x20, 2, 0x93, 0); /* FUN_001afa84 */
    }
    reader(*(long *)(self + 0x10), &scratch);
    if (canary == TB_CANARY) {
        return;
    }
    sk_stack_check(scratch);  /* FUN_0011d7e8 */
}

/*--------------------------------------------------------------------*/
/* FUN_000224f8 @ 0x000224f8   (est. sk_tb_decode_value32)
 * Ghidra: void FUN_000224f8(a, b)
 * Decode a value via FUN_00022558 with inline read primitive 0x192ac.
 * Confidence: low */
static void sk_tb_decode_value32(uint64_t a, uint64_t b)
{
    sk_tb_msg_read_generic2_32(a, b, (void *)0x192ac);  /* FUN_00022558(a,b,0x192ac) */
}

/*--------------------------------------------------------------------*/
/* FUN_00022558 @ 0x00022558   (est. sk_tb_msg_read_generic2_32)
 * Ghidra: void FUN_00022558(a, b, code *reader)
 * Two-argument generic 32-bit message read with unwrap guard and canary check.
 * Confidence: medium */
static void sk_tb_msg_read_generic2_32(uint64_t a, uint64_t b, void (*reader)(long, void *))
{
    register char *self asm("x20");
    long canary = TB_CANARY;
    uint32_t scratch = 0;

    if (*(long *)(self + 0x10) == 0) {
        sk_swift_fatal("Fatal error", 0xb, 2, 0xd000000000000022ULL,
                       (uint64_t)((char *)0x005acf60 + -0x20) | 0x8000000000000000ULL,
                       0x005acf50, 0x20, 2, 0x93, 0); /* FUN_001afa84 */
    }
    reader(*(long *)(self + 0x10), &scratch);
    if (canary == TB_CANARY) {
        return;
    }
    sk_stack_check(scratch);  /* FUN_0011d7e8 */
}

/*--------------------------------------------------------------------*/
/* FUN_00022608 @ 0x00022608   (est. sk_tb_decode_value64)
 * Ghidra: void FUN_00022608(a, b)
 * Decode a value via FUN_00022668 with inline read primitive 0x193c0.
 * Confidence: low */
static void sk_tb_decode_value64(uint64_t a, uint64_t b)
{
    sk_tb_msg_read_generic2_64(a, b, (void *)0x193c0);  /* FUN_00022668(a,b,0x193c0) */
}

/*--------------------------------------------------------------------*/
/* FUN_00022668 @ 0x00022668   (est. sk_tb_msg_read_generic2_64)
 * Ghidra: void FUN_00022668(a, b, code *reader)
 * Two-argument generic 64-bit message read with unwrap guard and canary check.
 * Confidence: medium */
static void sk_tb_msg_read_generic2_64(uint64_t a, uint64_t b, void (*reader)(long, void *))
{
    register char *self asm("x20");
    long canary = TB_CANARY;
    uint64_t scratch = 0;

    if (*(long *)(self + 0x10) == 0) {
        sk_swift_fatal("Fatal error", 0xb, 2, 0xd000000000000022ULL,
                       (uint64_t)((char *)0x005acf60 + -0x20) | 0x8000000000000000ULL,
                       0x005acf50, 0x20, 2, 0x93, 0); /* FUN_001afa84 */
    }
    reader(*(long *)(self + 0x10), &scratch);
    if (canary == TB_CANARY) {
        return;
    }
    sk_stack_check(scratch);  /* FUN_0011d7e8 */
}

/*--------------------------------------------------------------------*/
/* FUN_00022718 @ 0x00022718   (est. sk_tb_buf_offset_or_trap)
 * Ghidra: long FUN_00022718(ulong off, long base, long end)
 * Returns `base + off` if the offset is in bounds (off >= 0, base != 0, and
 * off < end - base). Otherwise it emits the offset error (FUN_002a4ab4) and
 * traps with a fatal error after pushing two "offset" diagnostics
 * (0xd000000000000019 "by a TightbeamDec[oder]" and 0x16 "error: capabilit[y]").
 * Confidence: medium
 * Notes: error push thunk FUN_002acbb8; FUN_001ba7d4/FUN_003a25d4 unwind. */
static long sk_tb_buf_offset_or_trap(unsigned long off, long base, long end)
{
    if (((long)off >= 0) && (base != 0) && (off < (unsigned long)(end - base))) {
        return base + off;
    }
    sk_tb_error_log(0x34);                       /* FUN_002a4ab4 */
    sk_tb_error_push(0xd000000000000019ULL, 0x80000000005ad050ULL);  /* "by a TightbeamDec" */
    sk_tb_error_log(0x677880);                   /* FUN_001ba7d4 */
    sk_tb_error_push(0xd000000000000016ULL, 0x80000000005ad070ULL);  /* "error: capabilit" */
    sk_tb_error_log(0x677880);
    sk_tb_error_push(0x29, 0xe100000000000000ULL);
    sk_swift_fatal("Fatal error", 0xb, 2, 0, 0xe000000000000000ULL,
                   0x005acfb0, 0x20, 2, 0xc3, 0); /* FUN_001afa84 */
    return 0;  /* unreachable */
}

/*--------------------------------------------------------------------*/
/* FUN_0002286c @ 0x0002286c   (est. sk_tb_msg_encode)
 * Ghidra: undefined8 FUN_0002286c(msg, start, end, a, b)
 * Encodes the message payload [start,end): allocates a metadata object
 * (FUN_0036a940), stores {a,b} into it, wraps it in a second box with a
 * function pointer, builds a call object (FUN_0004b520), invokes the encoder
 * core (FUN_00015a44), then runs the Tightbeam checker (FUN_003a26e8). Returns
 * the encode result; traps (SoftwareBreakpoint 1) if the checker fails.
 * Confidence: medium
 * Notes: allocs 0x65a730/0x65a758 (0x20 bytes, tag 7); callbacks FUN_00022d34,
 *   FUN_00022c18 table. */
static uint64_t sk_tb_msg_encode(long msg, long start, long end,
                                 uint64_t a, uint64_t b)
{
    long box, wbox, callobj;
    uint64_t v, r;
    unsigned long ok;

    if (msg == 0) {
        sk_swift_fatal("Fatal error", 0xb, 2, 0xd000000000000022ULL,
                       (uint64_t)((char *)0x005acf60 + -0x20) | 0x8000000000000000ULL,
                       0x005acf50, 0x20, 2, 0x93, 0); /* FUN_001afa84 */
    }
    if (start < 0) {
        __builtin_trap();  /* SoftwareBreakpoint(1, 0x229e8) */
    }
    if ((uint64_t)(end - start) > (uint64_t)end) {  /* SBORROW8(end,start) */
        __builtin_trap();  /* SoftwareBreakpoint(1, 0x229ec) */
    }
    box = (long)sk_alloc(0x65a730, 0x20);   /* FUN_0036a940 */
    *(uint64_t *)(box + 0x10) = a;
    *(uint64_t *)(box + 0x18) = b;
    wbox = (long)sk_alloc(0x65a758, 0x20);  /* FUN_0036a940 */
    *(void **)(wbox + 0x10) = (void *)0x00022c18;
    *(long *)(wbox + 0x18) = box;
    v = sk_tb_obj_pair((uint64_t)(uintptr_t)&sk_tb_msg_encode_cb0);  /* FUN_0004b520(&local) */
    sk_retain((uint64_t)(uintptr_t)wbox);                     /* FUN_0036b270 */
    sk_free((uint64_t)(uintptr_t)wbox);                       /* FUN_0036b118 */
    r = sk_tb_encode_core((uint64_t)(uintptr_t)msg, start, end - start, v);  /* FUN_00015a44 */
    sk_tb_obj_pair_free(v);              /* FUN_0004b664 */
    ok = sk_tb_check((uint64_t)(uintptr_t)wbox, 0x005be7c0, 0xc9, 0x36, 0x52, 1);  /* FUN_003a26e8 */
    sk_free((uint64_t)(uintptr_t)box);
    sk_free((uint64_t)(uintptr_t)wbox);
    if ((ok & 1) == 0) {
        return r;
    }
    __builtin_trap();  /* SoftwareBreakpoint(1, 0x229f0) */
}

/* callback target for sk_tb_msg_encode: invokes *(obj+0x20)(arg) */
static void sk_tb_msg_encode_cb0(long obj, uint64_t arg)
{
    (*(void (**)(uint64_t))(obj + 0x20))(arg);
}

/*--------------------------------------------------------------------*/
/* FUN_00022a3c @ 0x00022a3c   (est. sk_tb_msg_deinit_void)
 * Ghidra: void FUN_00022a3c(void)
 * Destroys the TightbeamMessage in x20 (FUN_00025704). Thin wrapper.
 * Confidence: medium */
static void sk_tb_msg_deinit_void(void)
{
    sk_tb_msg_deinit();  /* FUN_00025704 */
}

/*--------------------------------------------------------------------*/
/* FUN_00022a7c @ 0x00022a7c   (est. sk_tb_msg_wrap_move)
 * Ghidra: undefined1 *FUN_00022a7c(dst, src)
 * Moves a TightbeamMessage wrapper from `src` into `dst`: copies the header,
 * releases the previous buffer, then copies the three buffer fields and the
 * kind byte (handling the -1 "not initialized" kind). Returns `dst`.
 * Confidence: medium
 * Notes: releases prior buffer via FUN_0036b118 / FUN_00020c88; masks pointer
 *   tags (0x1fffffffffffffff) before freeing. */
static uint8_t *sk_tb_msg_wrap_move(uint8_t *dst, uint8_t *src)
{
    uint64_t old18, old20, old28, s18, s20, s28;

    dst[0] = src[0];
    sk_free((*(uint64_t *)(dst + 8) & 0x1fffffffffffffffULL));  /* FUN_0036b118 */
    *(uint64_t *)(dst + 0x10) = *(uint64_t *)(src + 0x10);
    *(uint64_t *)(dst + 0x08) = *(uint64_t *)(src + 0x08);
    if (dst[0x30] != 0xff) {
        if (src[0x30] != 0xff) {
            old18 = *(uint64_t *)(dst + 0x18);
            old20 = *(uint64_t *)(dst + 0x20);
            old28 = *(uint64_t *)(dst + 0x28);
            s18 = *(uint64_t *)(src + 0x18);
            s20 = *(uint64_t *)(src + 0x20);
            s28 = *(uint64_t *)(src + 0x28);
            *(uint64_t *)(dst + 0x20) = s20;
            *(uint64_t *)(dst + 0x18) = s18;
            *(uint64_t *)(dst + 0x28) = s28;
            dst[0x30] = src[0x30];
            sk_tb_release_unless_owned(old18, old20, old28, 0);
            return dst;
        }
        sk_tb_msg_release_buf(*(uint64_t *)(dst + 0x18), *(uint64_t *)(dst + 0x20));  /* FUN_00020c88 */
    }
    *(uint64_t *)(dst + 0x20) = *(uint64_t *)(src + 0x20);
    *(uint64_t *)(dst + 0x18) = *(uint64_t *)(src + 0x18);
    *(uint64_t *)(dst + 0x29) = *(uint64_t *)(src + 0x29);
    *(uint64_t *)(dst + 0x21) = *(uint64_t *)(src + 0x21);
    return dst;
}

/*--------------------------------------------------------------------*/
/* FUN_00022c48 @ 0x00022c48   (est. sk_tb_msg_copyinit_out)
 * Ghidra: void FUN_00022c48(out)
 * Copy-initializes `out` from the TightbeamMessage in x20, retaining the
 * payload buffer (FUN_0001590c) and copying the header and buffer fields.
 * Traps (fatal 0x93) if the message is unwrapped.
 * Confidence: medium */
static void sk_tb_msg_copyinit_out(uint8_t *out)
{
    register uint8_t *self asm("x20");
    long payload = *(long *)(self + 0x10);

    if (payload != 0) {
        uint8_t k = self[0x30];
        uint64_t b28 = *(uint64_t *)(self + 0x28);
        uint64_t b20 = *(uint64_t *)(self + 0x20);
        uint64_t b18 = *(uint64_t *)(self + 0x18);
        uint64_t b08 = *(uint64_t *)(self + 0x08);
        uint8_t  b00 = self[0];
        sk_tb_field_retain(payload, 0);  /* FUN_0001590c */
        out[0] = b00;
        *(uint64_t *)(out + 0x08) = b08;
        *(long *)(out + 0x10) = payload;
        *(uint64_t *)(out + 0x20) = b20;
        *(uint64_t *)(out + 0x18) = b18;
        *(uint64_t *)(out + 0x28) = b28;
        out[0x30] = k;
        return;
    }
    sk_swift_fatal("Fatal error", 0xb, 2, 0xd000000000000022ULL,
                   (uint64_t)((char *)0x005acf60 + -0x20) | 0x8000000000000000ULL,
                   0x005acf50, 0x20, 2, 0x93, 0); /* FUN_001afa84 */
}

/*--------------------------------------------------------------------*/
/* FUN_00022d0c @ 0x00022d0c   (est. sk_tb_call_closure)
 * Ghidra: void FUN_00022d0c(a, code *fn)
 * Invokes the closure `fn` with no arguments.
 * Confidence: medium */
static void sk_tb_call_closure(uint64_t a, void (*fn)(void))
{
    fn();
}

/*--------------------------------------------------------------------*/
/* FUN_00022d34 @ 0x00022d34   (est. sk_tb_cb_invoke)
 * Ghidra: void FUN_00022d34(long obj, undefined8 arg)
 * Invokes the closure stored at obj+0x20 with `arg`. Tightbeam callback shim.
 * Confidence: medium */
static void sk_tb_cb_invoke(long obj, uint64_t arg)
{
    (*(void (**)(uint64_t))(obj + 0x20))(arg);
}

/*--------------------------------------------------------------------*/
/* FUN_00022d60 @ 0x00022d60   (est. sk_tb_msg_append_range)
 * Ghidra: void FUN_00022d60(start, end)
 * Appends the byte range [start,end) to the TightbeamMessage via
 * FUN_00018650. If `start` is null or the message is unwrapped it traps with a
 * fatal error (0x2e "Failed to unwrap provided buffer" / 0x93).
 * Confidence: medium */
static void sk_tb_msg_append_range(long start, long end)
{
    register char *self asm("x20");

    if (start != 0) {
        if (*(long *)(self + 0x10) != 0) {
            sk_tb_append_raw(*(uint64_t *)(self + 0x10), (uint64_t)start, (unsigned long)end - start);
            return;
        }
        sk_swift_fatal("Fatal error", 0xb, 2, 0xd000000000000022ULL,
                       (uint64_t)((char *)0x005acf80 + -0x20) | 0x8000000000000000ULL,
                       0x005acf50, 0x20, 2, 0x93, 0); /* FUN_001afa84 */
    }
    sk_swift_fatal("Fatal error", 0xb, 2, 0xd000000000000028ULL,
                   (uint64_t)((char *)0x005acfe0 + -0x20) | 0x8000000000000000ULL,
                   0x005ad0b0, 0x20, 2, 0x2e, 0); /* FUN_001afa84 */
}

/*--------------------------------------------------------------------*/
/* FUN_00022e34 @ 0x00022e34   (est. sk_tb_msg_decode_entry)
 * Ghidra: undefined8 FUN_00022e34(void)
 * Decode entry: calls the decode worker (FUN_00022eac) and on a nonzero error
 * status reports the error result (FUN_003698b0). Returns the decode status.
 * Confidence: medium */
static uint64_t sk_tb_msg_decode_entry(void)
{
    uint64_t r;
    int code;
    cl4_result_t err;

    register char *self asm("x20");
    r = sk_tb_msg_decode((long)self, 0, 0, 0, 0);  /* FUN_00022eac */
    code = (int)r;
    if (code != 0) {
        err = sk_tb_make_error(0);                   /* FUN_00019aac */
        sk_tb_error_report(&code, err.lo, 0x0065a550ULL);  /* FUN_003698b0 */
    }
    return r;
}

/*--------------------------------------------------------------------*/
/* FUN_00022eac @ 0x00022eac   (est. sk_tb_msg_decode)
 * Ghidra: undefined8 FUN_00022eac(msg, start, end, a, b)
 * Decodes [start,end) from the message: allocates a decoder metadata object,
 * wraps it, builds a call object (FUN_0004b520), runs the decoder core
 * (FUN_00015a44) on the payload, and checks the result (FUN_003a26e8). Traps if
 * the checker fails. Returns the decode result.
 * Confidence: medium
 * Notes: allocs 0x65a8c0/0x65a8e8; callback FUN_00023b64; check tag 0x43. */
static uint64_t sk_tb_msg_decode(long msg, long start, long end,
                                 uint64_t a, uint64_t b)
{
    long box, wbox, payload, callobj;
    uint64_t v, r;
    unsigned long ok;

    payload = *(long *)(msg + 0x10);
    if (payload == 0) {
        sk_swift_fatal("Fatal error", 0xb, 2, 0xd000000000000022ULL,
                       (uint64_t)((char *)0x005acf60 + -0x20) | 0x8000000000000000ULL,
                       0x005acf50, 0x20, 2, 0x93, 0); /* FUN_001afa84 */
    }
    if (start < 0) {
        __builtin_trap();  /* SoftwareBreakpoint(1, 0x23028) */
    }
    if ((uint64_t)(end - start) > (uint64_t)end) {
        __builtin_trap();  /* SoftwareBreakpoint(1, 0x2302c) */
    }
    box = (long)sk_alloc(0x65a8c0, 0x20);   /* FUN_0036a940 */
    *(uint64_t *)(box + 0x10) = a;
    *(uint64_t *)(box + 0x18) = b;
    wbox = (long)sk_alloc(0x65a8e8, 0x20);  /* FUN_0036a940 */
    *(void **)(wbox + 0x10) = (void *)0x00022c18;
    *(long *)(wbox + 0x18) = box;
    v = sk_tb_obj_pair((uint64_t)(uintptr_t)&sk_tb_msg_decode_cb0);  /* FUN_0004b520 */
    sk_retain((uint64_t)(uintptr_t)wbox);                     /* FUN_0036b270 */
    sk_free((uint64_t)(uintptr_t)wbox);
    r = sk_tb_encode_core((uint64_t)(uintptr_t)payload, start, end - start, v);  /* FUN_00015a44 */
    sk_tb_obj_pair_free(v);              /* FUN_0004b664 */
    ok = sk_tb_check((uint64_t)(uintptr_t)wbox, 0x005be7c0, 0xc9, 0x43, 0x52, 1);  /* FUN_003a26e8 */
    sk_free((uint64_t)(uintptr_t)box);
    sk_free((uint64_t)(uintptr_t)wbox);
    if ((ok & 1) == 0) {
        return r;
    }
    __builtin_trap();  /* SoftwareBreakpoint(1, 0x23030) */
}

/* callback target for sk_tb_msg_decode: invokes *(obj+0x10)() */
static void sk_tb_msg_decode_cb0(long obj)
{
    (*(void (**)(void))(obj + 0x10))();
}

/*--------------------------------------------------------------------*/
/* FUN_0002307c @ 0x0002307c   (est. sk_tb_msg_append_flag)
 * Ghidra: void FUN_0002307c(uint flag)
 * Appends a boolean flag to the message via FUN_000187a4 (flag & 1). Traps if
 * unwrapped.
 * Confidence: medium */
static void sk_tb_msg_append_flag(uint32_t flag)
{
    register char *self asm("x20");
    if (*(long *)(self + 0x10) != 0) {
        sk_tb_append_flag0(*(uint64_t *)(self + 0x10), (uint64_t)(flag & 1));  /* FUN_000187a4 */
        return;
    }
    sk_swift_fatal("Fatal error", 0xb, 2, 0xd000000000000022ULL,
                   (uint64_t)((char *)0x005acf60 + -0x20) | 0x8000000000000000ULL,
                   0x005acf50, 0x20, 2, 0x93, 0); /* FUN_001afa84 */
}

/*--------------------------------------------------------------------*/
/* FUN_000230f8 @ 0x000230f8   (est. sk_tb_msg_append_byte)
 * Ghidra: void FUN_000230f8(byte v)
 * Appends a byte to the message via FUN_000188fc. Traps if unwrapped.
 * Confidence: medium */
static void sk_tb_msg_append_byte(uint8_t v)
{
    register char *self asm("x20");
    if (*(long *)(self + 0x10) != 0) {
        sk_tb_append_byte(*(uint64_t *)(self + 0x10), (uint64_t)v);  /* FUN_000188fc */
        return;
    }
    sk_swift_fatal("Fatal error", 0xb, 2, 0xd000000000000022ULL,
                   (uint64_t)((char *)0x005acf60 + -0x20) | 0x8000000000000000ULL,
                   0x005acf50, 0x20, 2, 0x93, 0); /* FUN_001afa84 */
}

/*--------------------------------------------------------------------*/
/* FUN_00023174 @ 0x00023174   (est. sk_tb_msg_append_u16)
 * Ghidra: void FUN_00023174(uint16_t v)
 * Appends a 16-bit value via FUN_00018b0c. Traps if unwrapped.
 * Confidence: medium */
static void sk_tb_msg_append_u16(uint16_t v)
{
    register char *self asm("x20");
    if (*(long *)(self + 0x10) != 0) {
        sk_tb_append_u16(*(uint64_t *)(self + 0x10), (uint64_t)v);  /* FUN_00018b0c */
        return;
    }
    sk_swift_fatal("Fatal error", 0xb, 2, 0xd000000000000022ULL,
                   (uint64_t)((char *)0x005acf60 + -0x20) | 0x8000000000000000ULL,
                   0x005acf50, 0x20, 2, 0x93, 0); /* FUN_001afa84 */
}

/*--------------------------------------------------------------------*/
/* FUN_000231f0 @ 0x000231f0   (est. sk_tb_msg_append_u32a)
 * Ghidra: void FUN_000231f0(v)
 * Appends a 32-bit value via FUN_00023330 with writer FUN_00018c70.
 * Confidence: medium */
static void sk_tb_msg_append_u32a(uint64_t v)
{
    sk_tb_msg_append_generic32(v, sk_tb_append_u32);  /* FUN_00023330(v, FUN_00018c70) */
}

/*--------------------------------------------------------------------*/
/* FUN_00023208 @ 0x00023208   (est. sk_tb_msg_append_u64a)
 * Ghidra: void FUN_00023208(v)
 * Appends a 64-bit value via FUN_000233c8 with writer FUN_00018dd4.
 * Confidence: medium */
static void sk_tb_msg_append_u64a(uint64_t v)
{
    sk_tb_msg_append_generic64(v, sk_tb_append_u64);  /* FUN_000233c8(v, FUN_00018dd4) */
}

/*--------------------------------------------------------------------*/
/* FUN_00023220 @ 0x00023220   (est. sk_tb_msg_append_char)
 * Ghidra: void FUN_00023220(char v)
 * Appends a char via FUN_00019000. Traps if unwrapped.
 * Confidence: medium */
static void sk_tb_msg_append_char(char v)
{
    register char *self asm("x20");
    if (*(long *)(self + 0x10) != 0) {
        sk_tb_append_char(*(uint64_t *)(self + 0x10), (uint64_t)v);  /* FUN_00019000 */
        return;
    }
    sk_swift_fatal("Fatal error", 0xb, 2, 0xd000000000000022ULL,
                   (uint64_t)((char *)0x005acf60 + -0x20) | 0x8000000000000000ULL,
                   0x005acf50, 0x20, 2, 0x93, 0); /* FUN_001afa84 */
}

/*--------------------------------------------------------------------*/
/* FUN_0002329c @ 0x0002329c   (est. sk_tb_msg_append_short)
 * Ghidra: void FUN_0002329c(short v)
 * Appends a short via FUN_0001910c. Traps if unwrapped.
 * Confidence: medium */
static void sk_tb_msg_append_short(short v)
{
    register char *self asm("x20");
    if (*(long *)(self + 0x10) != 0) {
        sk_tb_append_short(*(uint64_t *)(self + 0x10), (uint64_t)v);  /* FUN_0001910c */
        return;
    }
    sk_swift_fatal("Fatal error", 0xb, 2, 0xd000000000000022ULL,
                   (uint64_t)((char *)0x005acf60 + -0x20) | 0x8000000000000000ULL,
                   0x005acf50, 0x20, 2, 0x93, 0); /* FUN_001afa84 */
}

/*--------------------------------------------------------------------*/
/* FUN_00023318 @ 0x00023318   (est. sk_tb_msg_append_u32b)
 * Ghidra: void FUN_00023318(v)
 * Appends a 32-bit value via FUN_00023330 with writer FUN_00019220.
 * Confidence: medium */
static void sk_tb_msg_append_u32b(uint64_t v)
{
    sk_tb_msg_append_generic32(v, sk_tb_append_flag);  /* FUN_00023330(v, FUN_00019220) */
}

/*--------------------------------------------------------------------*/
/* FUN_00023330 @ 0x00023330   (est. sk_tb_msg_append_generic32)
 * Ghidra: void FUN_00023330(v, code *writer)
 * Generic 32-bit append: calls `writer`(payload, v) if the message is
 * unwrapped, else traps (fatal 0x93).
 * Confidence: medium */
static void sk_tb_msg_append_generic32(uint64_t v, void (*writer)(uint64_t, uint64_t))
{
    register char *self asm("x20");
    if (*(long *)(self + 0x10) != 0) {
        writer(*(uint64_t *)(self + 0x10), v);
        return;
    }
    sk_swift_fatal("Fatal error", 0xb, 2, 0xd000000000000022ULL,
                   (uint64_t)((char *)0x005acf60 + -0x20) | 0x8000000000000000ULL,
                   0x005acf50, 0x20, 2, 0x93, 0); /* FUN_001afa84 */
}

/*--------------------------------------------------------------------*/
/* FUN_000233c8 @ 0x000233c8   (est. sk_tb_msg_append_generic64)
 * Ghidra: void FUN_000233c8(v, code *writer)
 * Generic 64-bit append: calls `writer`(payload, v) if unwrapped, else traps.
 * Confidence: medium */
static void sk_tb_msg_append_generic64(uint64_t v, void (*writer)(uint64_t, uint64_t))
{
    register char *self asm("x20");
    if (*(long *)(self + 0x10) != 0) {
        writer(*(uint64_t *)(self + 0x10), v);
        return;
    }
    sk_swift_fatal("Fatal error", 0xb, 2, 0xd000000000000022ULL,
                   (uint64_t)((char *)0x005acf60 + -0x20) | 0x8000000000000000ULL,
                   0x005acf50, 0x20, 2, 0x93, 0); /* FUN_001afa84 */
}

/*--------------------------------------------------------------------*/
/* FUN_00023448 @ 0x00023448   (est. sk_tb_msg_read_preserve)
 * Ghidra: void FUN_00023448(void)
 * Preserves the message read state via FUN_00019448. Traps if unwrapped.
 * Confidence: medium */
static void sk_tb_msg_read_preserve(void)
{
    register char *self asm("x20");
    if (*(long *)(self + 0x10) != 0) {
        sk_tb_read_preserve();  /* FUN_00019448 */
        return;
    }
    sk_swift_fatal("Fatal error", 0xb, 2, 0xd000000000000022ULL,
                   (uint64_t)((char *)0x005acf60 + -0x20) | 0x8000000000000000ULL,
                   0x005acf50, 0x20, 2, 0x93, 0); /* FUN_001afa84 */
}

/*--------------------------------------------------------------------*/
/* FUN_000234bc @ 0x000234bc   (est. sk_tb_msg_read_preserve2)
 * Ghidra: void FUN_000234bc(void)
 * Preserves the message read state via FUN_00019628. Traps if unwrapped.
 * Confidence: medium */
static void sk_tb_msg_read_preserve2(void)
{
    register char *self asm("x20");
    if (*(long *)(self + 0x10) != 0) {
        sk_tb_read_preserve2();  /* FUN_00019628 */
        return;
    }
    sk_swift_fatal("Fatal error", 0xb, 2, 0xd000000000000022ULL,
                   (uint64_t)((char *)0x005acf60 + -0x20) | 0x8000000000000000ULL,
                   0x005acf50, 0x20, 2, 0x93, 0); /* FUN_001afa84 */
}

/*--------------------------------------------------------------------*/
/* FUN_00023530 @ 0x00023530   (est. sk_tb_msg_append_value)
 * Ghidra: void FUN_00023530(v)
 * Appends a value via FUN_00015be8. Traps if unwrapped.
 * Confidence: medium */
static void sk_tb_msg_append_value(uint64_t v)
{
    register char *self asm("x20");
    if (*(long *)(self + 0x10) != 0) {
        sk_tb_append_value(*(uint64_t *)(self + 0x10), v);  /* FUN_00015be8 */
        return;
    }
    sk_swift_fatal("Fatal error", 0xb, 2, 0xd000000000000022ULL,
                   (uint64_t)((char *)0x005acf60 + -0x20) | 0x8000000000000000ULL,
                   0x005acf50, 0x20, 2, 0x93, 0); /* FUN_001afa84 */
}

/*--------------------------------------------------------------------*/
/* FUN_000235a8 @ 0x000235a8   (est. sk_tb_encoder_deinit_trap)
 * Ghidra: void FUN_000235a8(a, self)
 * TightbeamEncoder deinit trap: calls the metadata destructor (indirect call
 * at *(self+(-8)+8)), then traps with a fatal error (diagnostic 0x97,
 * encoder context, error 0x56).
 * Confidence: medium */
static void sk_tb_encoder_deinit_trap(uint64_t a, long self)
{
    (*(void (**)(void))(*(long *)(self + -8) + 8))();
    sk_swift_fatal("Fatal error", 0xb, 2, 0xd000000000000056ULL,
                   (uint64_t)((char *)0x005ad0c0 + -0x20) | 0x8000000000000000ULL,
                   0x005ad0b0, 0x20, 2, 0x97, 0); /* FUN_001afa84 */
}

/*--------------------------------------------------------------------*/
/* FUN_00023670 @ 0x00023670   (est. sk_tb_msg_append_generic32b)
 * Ghidra: void FUN_00023670(a, b, c, code *writer)
 * Generic append with three extra args; calls `writer`(payload, a) if
 * unwrapped, else traps.
 * Confidence: medium */
static void sk_tb_msg_append_generic32b(uint64_t a, uint64_t b, uint64_t c,
                                        void (*writer)(uint64_t, uint64_t))
{
    register char *self asm("x20");
    if (*(long *)(self + 0x10) != 0) {
        writer(*(uint64_t *)(self + 0x10), a);
        return;
    }
    sk_swift_fatal("Fatal error", 0xb, 2, 0xd000000000000022ULL,
                   (uint64_t)((char *)0x005acf60 + -0x20) | 0x8000000000000000ULL,
                   0x005acf50, 0x20, 2, 0x93, 0); /* FUN_001afa84 */
}

/*--------------------------------------------------------------------*/
/* FUN_00023704 @ 0x00023704   (est. sk_tb_msg_append_generic64b)
 * Ghidra: void FUN_00023704(a, b, c, code *writer)
 * Generic 64-bit append with three extra args; calls `writer`(payload, a) if
 * unwrapped, else traps.
 * Confidence: medium */
static void sk_tb_msg_append_generic64b(uint64_t a, uint64_t b, uint64_t c,
                                        void (*writer)(uint64_t, uint64_t))
{
    register char *self asm("x20");
    if (*(long *)(self + 0x10) != 0) {
        writer(*(uint64_t *)(self + 0x10), a);
        return;
    }
    sk_swift_fatal("Fatal error", 0xb, 2, 0xd000000000000022ULL,
                   (uint64_t)((char *)0x005acf60 + -0x20) | 0x8000000000000000ULL,
                   0x005acf50, 0x20, 2, 0x93, 0); /* FUN_001afa84 */
}

/*--------------------------------------------------------------------*/
/* FUN_00023780 @ 0x00023780   (est. sk_tb_encoder_extend)
 * Ghidra: void FUN_00023780(void)
 * Extends the encoder cursor (x20) by the length reported by FUN_0001879c;
 * traps (SoftwareBreakpoint 1) if the addition carries (buffer overflow).
 * Confidence: medium */
static void sk_tb_encoder_extend(void)
{
    register long *self asm("x20");
    long n = sk_tb_append_len();  /* FUN_0001879c */
    long nxt;
    if (__builtin_add_overflow(*self, n, &nxt)) {
        __builtin_trap();  /* SoftwareBreakpoint(1, 0x237ac) */
    }
    *self = nxt;
}

/*--------------------------------------------------------------------*/
/* FUN_00023784 @ 0x00023784   (est. sk_tb_encoder_extend2)
 * Ghidra: void FUN_00023784(void)
 * Identical to FUN_00023780 (Swift @objc thunk pair): extends the encoder
 * cursor by the reported length, trapping on overflow.
 * Confidence: medium */
static void sk_tb_encoder_extend2(void)
{
    register long *self asm("x20");
    long n = sk_tb_append_len();  /* FUN_0001879c */
    long nxt;
    if (__builtin_add_overflow(*self, n, &nxt)) {
        __builtin_trap();  /* SoftwareBreakpoint(1, 0x237ac) */
    }
    *self = nxt;
}

/*--------------------------------------------------------------------*/
/* FUN_00023824 @ 0x00023824   (est. sk_tb_encoder_extend_cb)
 * Ghidra: void FUN_00023824(a, code *lenfn)
 * Extends the encoder cursor by `lenfn`() result; traps on overflow.
 * Confidence: medium */
static void sk_tb_encoder_extend_cb(uint64_t a, unsigned long (*lenfn)(void))
{
    register long *self asm("x20");
    long n = lenfn();
    long nxt;
    if (__builtin_add_overflow(*self, n, &nxt)) {
        __builtin_trap();  /* SoftwareBreakpoint(1, 0x23854) */
    }
    *self = nxt;
}

/*--------------------------------------------------------------------*/
/* FUN_00023828 @ 0x00023828   (est. sk_tb_encoder_extend_cb2)
 * Ghidra: void FUN_00023828(a, code *lenfn)
 * Identical to FUN_00023824 (thunk pair).
 * Confidence: medium */
static void sk_tb_encoder_extend_cb2(uint64_t a, unsigned long (*lenfn)(void))
{
    register long *self asm("x20");
    long n = lenfn();
    long nxt;
    if (__builtin_add_overflow(*self, n, &nxt)) {
        __builtin_trap();  /* SoftwareBreakpoint(1, 0x23854) */
    }
    *self = nxt;
}

/*--------------------------------------------------------------------*/
/* FUN_0002386c @ 0x0002386c   (est. sk_tb_encoder_extend_cb3)
 * Ghidra: void FUN_0002386c(a, code *lenfn)
 * Extends the encoder cursor by `lenfn`() result; traps on overflow (0x2389c).
 * Confidence: medium */
static void sk_tb_encoder_extend_cb3(uint64_t a, unsigned long (*lenfn)(void))
{
    register long *self asm("x20");
    long n = lenfn();
    long nxt;
    if (__builtin_add_overflow(*self, n, &nxt)) {
        __builtin_trap();  /* SoftwareBreakpoint(1, 0x2389c) */
    }
    *self = nxt;
}

/*--------------------------------------------------------------------*/
/* FUN_00023870 @ 0x00023870   (est. sk_tb_encoder_extend_cb4)
 * Ghidra: void FUN_00023870(a, code *lenfn)
 * Identical to FUN_0002386c (thunk pair).
 * Confidence: medium */
static void sk_tb_encoder_extend_cb4(uint64_t a, unsigned long (*lenfn)(void))
{
    register long *self asm("x20");
    long n = lenfn();
    long nxt;
    if (__builtin_add_overflow(*self, n, &nxt)) {
        __builtin_trap();  /* SoftwareBreakpoint(1, 0x2389c) */
    }
    *self = nxt;
}

/*--------------------------------------------------------------------*/
/* FUN_000238b4 @ 0x000238b4   (est. sk_tb_encoder_extend_cb5)
 * Ghidra: void FUN_000238b4(a, code *lenfn)
 * Extends the encoder cursor by `lenfn`() result; traps on overflow (0x238e4).
 * Confidence: medium */
static void sk_tb_encoder_extend_cb5(uint64_t a, unsigned long (*lenfn)(void))
{
    register long *self asm("x20");
    long n = lenfn();
    long nxt;
    if (__builtin_add_overflow(*self, n, &nxt)) {
        __builtin_trap();  /* SoftwareBreakpoint(1, 0x238e4) */
    }
    *self = nxt;
}

/*--------------------------------------------------------------------*/
/* FUN_000238b8 @ 0x000238b8   (est. sk_tb_encoder_extend_cb6)
 * Ghidra: void FUN_000238b8(a, code *lenfn)
 * Identical to FUN_000238b4 (thunk pair).
 * Confidence: medium */
static void sk_tb_encoder_extend_cb6(uint64_t a, unsigned long (*lenfn)(void))
{
    register long *self asm("x20");
    long n = lenfn();
    long nxt;
    if (__builtin_add_overflow(*self, n, &nxt)) {
        __builtin_trap();  /* SoftwareBreakpoint(1, 0x238e4) */
    }
    *self = nxt;
}

/*--------------------------------------------------------------------*/
/* FUN_000238fc @ 0x000238fc   (est. sk_tb_decoder_extend_len)
 * Ghidra: void FUN_000238fc(void)
 * Extends the decoder cursor by the length from FUN_00019440; traps on
 * overflow (0x23928).
 * Confidence: medium */
static void sk_tb_decoder_extend_len(void)
{
    register long *self asm("x20");
    long n = sk_tb_read_len();  /* FUN_00019440 */
    long nxt;
    if (__builtin_add_overflow(*self, n, &nxt)) {
        __builtin_trap();  /* SoftwareBreakpoint(1, 0x23928) */
    }
    *self = nxt;
}

/*--------------------------------------------------------------------*/
/* FUN_00023900 @ 0x00023900   (est. sk_tb_decoder_extend_len2)
 * Ghidra: void FUN_00023900(void)
 * Identical to FUN_000238fc (thunk pair).
 * Confidence: medium */
static void sk_tb_decoder_extend_len2(void)
{
    register long *self asm("x20");
    long n = sk_tb_read_len();  /* FUN_00019440 */
    long nxt;
    if (__builtin_add_overflow(*self, n, &nxt)) {
        __builtin_trap();  /* SoftwareBreakpoint(1, 0x23928) */
    }
    *self = nxt;
}

/*--------------------------------------------------------------------*/
/* FUN_00023928 @ 0x00023928   (est. sk_tb_decoder_extend_len3)
 * Ghidra: void FUN_00023928(void)
 * Extends the decoder cursor by the length from FUN_00019620; traps on
 * overflow (0x23954).
 * Confidence: medium */
static void sk_tb_decoder_extend_len3(void)
{
    register long *self asm("x20");
    long n = sk_tb_read_len2();  /* FUN_00019620 */
    long nxt;
    if (__builtin_add_overflow(*self, n, &nxt)) {
        __builtin_trap();  /* SoftwareBreakpoint(1, 0x23954) */
    }
    *self = nxt;
}

/*--------------------------------------------------------------------*/
/* FUN_0002392c @ 0x0002392c   (est. sk_tb_decoder_extend_len4)
 * Ghidra: void FUN_0002392c(void)
 * Identical to FUN_00023928 (thunk pair).
 * Confidence: medium */
static void sk_tb_decoder_extend_len4(void)
{
    register long *self asm("x20");
    long n = sk_tb_read_len2();  /* FUN_00019620 */
    long nxt;
    if (__builtin_add_overflow(*self, n, &nxt)) {
        __builtin_trap();  /* SoftwareBreakpoint(1, 0x23954) */
    }
    *self = nxt;
}

/*--------------------------------------------------------------------*/
/* FUN_0002396c @ 0x0002396c   (est. sk_tb_cursor_extend_cb)
 * Ghidra: void FUN_0002396c(a, code *lenfn)
 * Extends the cursor by `lenfn`() result; traps on overflow (0x2399c).
 * Confidence: medium */
static void sk_tb_cursor_extend_cb(uint64_t a, unsigned long (*lenfn)(void))
{
    register long *self asm("x20");
    long n = lenfn();
    long nxt;
    if (__builtin_add_overflow(*self, n, &nxt)) {
        __builtin_trap();  /* SoftwareBreakpoint(1, 0x2399c) */
    }
    *self = nxt;
}

/*--------------------------------------------------------------------*/
/* FUN_00023970 @ 0x00023970   (est. sk_tb_cursor_extend_cb2)
 * Ghidra: void FUN_00023970(a, code *lenfn)
 * Identical to FUN_0002396c (thunk pair).
 * Confidence: medium */
static void sk_tb_cursor_extend_cb2(uint64_t a, unsigned long (*lenfn)(void))
{
    register long *self asm("x20");
    long n = lenfn();
    long nxt;
    if (__builtin_add_overflow(*self, n, &nxt)) {
        __builtin_trap();  /* SoftwareBreakpoint(1, 0x2399c) */
    }
    *self = nxt;
}

/*--------------------------------------------------------------------*/
/* FUN_00023a14 @ 0x00023a14   (est. sk_tb_cursor_extend_x3)
 * Ghidra: void FUN_00023a14(void)
 * Extends the cursor by the length from the closure in x3; traps on overflow
 * (0x23a44).
 * Confidence: medium */
static void sk_tb_cursor_extend_x3(void)
{
    register long *self asm("x20");
    register unsigned long (*lenfn)(void) asm("x3");
    long n = lenfn();
    long nxt;
    if (__builtin_add_overflow(*self, n, &nxt)) {
        __builtin_trap();  /* SoftwareBreakpoint(1, 0x23a44) */
    }
    *self = nxt;
}

/*--------------------------------------------------------------------*/
/* FUN_00023a18 @ 0x00023a18   (est. sk_tb_cursor_extend_x3b)
 * Ghidra: void FUN_00023a18(void)
 * Identical to FUN_00023a14 (thunk pair).
 * Confidence: medium */
static void sk_tb_cursor_extend_x3b(void)
{
    register long *self asm("x20");
    register unsigned long (*lenfn)(void) asm("x3");
    long n = lenfn();
    long nxt;
    if (__builtin_add_overflow(*self, n, &nxt)) {
        __builtin_trap();  /* SoftwareBreakpoint(1, 0x23a44) */
    }
    *self = nxt;
}

/*--------------------------------------------------------------------*/
/* FUN_00023a5c @ 0x00023a5c   (est. sk_tb_cursor_extend_x3c)
 * Ghidra: void FUN_00023a5c(void)
 * Extends the cursor by the length from the closure in x3; traps on overflow
 * (0x23a8c).
 * Confidence: medium */
static void sk_tb_cursor_extend_x3c(void)
{
    register long *self asm("x20");
    register unsigned long (*lenfn)(void) asm("x3");
    long n = lenfn();
    long nxt;
    if (__builtin_add_overflow(*self, n, &nxt)) {
        __builtin_trap();  /* SoftwareBreakpoint(1, 0x23a8c) */
    }
    *self = nxt;
}

/*--------------------------------------------------------------------*/
/* FUN_00023a60 @ 0x00023a60   (est. sk_tb_cursor_extend_x3d)
 * Ghidra: void FUN_00023a60(void)
 * Identical to FUN_00023a5c (thunk pair).
 * Confidence: medium */
static void sk_tb_cursor_extend_x3d(void)
{
    register long *self asm("x20");
    register unsigned long (*lenfn)(void) asm("x3");
    long n = lenfn();
    long nxt;
    if (__builtin_add_overflow(*self, n, &nxt)) {
        __builtin_trap();  /* SoftwareBreakpoint(1, 0x23a8c) */
    }
    *self = nxt;
}

/*--------------------------------------------------------------------*/
/* FUN_00023aa4 @ 0x00023aa4   (est. sk_tb_cursor_extend_x3e)
 * Ghidra: void FUN_00023aa4(void)
 * Extends the cursor by the length from the closure in x3; traps on overflow
 * (0x23ad4).
 * Confidence: medium */
static void sk_tb_cursor_extend_x3e(void)
{
    register long *self asm("x20");
    register unsigned long (*lenfn)(void) asm("x3");
    long n = lenfn();
    long nxt;
    if (__builtin_add_overflow(*self, n, &nxt)) {
        __builtin_trap();  /* SoftwareBreakpoint(1, 0x23ad4) */
    }
    *self = nxt;
}

/*--------------------------------------------------------------------*/
/* FUN_00023aa8 @ 0x00023aa8   (est. sk_tb_cursor_extend_x3f)
 * Ghidra: void FUN_00023aa8(void)
 * Identical to FUN_00023aa4 (thunk pair).
 * Confidence: medium */
static void sk_tb_cursor_extend_x3f(void)
{
    register long *self asm("x20");
    register unsigned long (*lenfn)(void) asm("x3");
    long n = lenfn();
    long nxt;
    if (__builtin_add_overflow(*self, n, &nxt)) {
        __builtin_trap();  /* SoftwareBreakpoint(1, 0x23ad4) */
    }
    *self = nxt;
}

/*--------------------------------------------------------------------*/
/* FUN_00023b04 @ 0x00023b04   (est. sk_tb_cursor_extend_x3g)
 * Ghidra: void FUN_00023b04(void)
 * Extends the cursor by the length from the closure in x3; traps on overflow
 * (0x23b34).
 * Confidence: medium */
static void sk_tb_cursor_extend_x3g(void)
{
    register long *self asm("x20");
    register unsigned long (*lenfn)(void) asm("x3");
    long n = lenfn();
    long nxt;
    if (__builtin_add_overflow(*self, n, &nxt)) {
        __builtin_trap();  /* SoftwareBreakpoint(1, 0x23b34) */
    }
    *self = nxt;
}

/*--------------------------------------------------------------------*/
/* FUN_00023b08 @ 0x00023b08   (est. sk_tb_cursor_extend_x3h)
 * Ghidra: void FUN_00023b08(void)
 * Identical to FUN_00023b04 (thunk pair).
 * Confidence: medium */
static void sk_tb_cursor_extend_x3h(void)
{
    register long *self asm("x20");
    register unsigned long (*lenfn)(void) asm("x3");
    long n = lenfn();
    long nxt;
    if (__builtin_add_overflow(*self, n, &nxt)) {
        __builtin_trap();  /* SoftwareBreakpoint(1, 0x23b34) */
    }
    *self = nxt;
}

/*--------------------------------------------------------------------*/
/* FUN_00023b64 @ 0x00023b64   (est. sk_tb_cb_invoke_noarg)
 * Ghidra: void FUN_00023b64(void)
 * Invokes the closure at self+0x10 with no arguments.
 * Confidence: medium */
static void sk_tb_cb_invoke_noarg(void)
{
    register char *self asm("x20");
    (*(void (**)(void))(self + 0x10))();
}

/*--------------------------------------------------------------------*/
/* FUN_00023c10 @ 0x00023c10   (est. sk_tb_witness_invoke)
 * Ghidra: void FUN_00023c10(a, b, c, d, meta)
 * Resolves the Tightbeam witness method from `meta` (FUN_00023c78) and calls
 * it with (b, d, meta).
 * Confidence: medium */
static void sk_tb_witness_invoke(uint64_t a, uint64_t b, uint64_t c, uint64_t d, uint64_t meta)
{
    void (*fn)(uint64_t, uint64_t, uint64_t);
    fn = (void *)sk_tb_witness_fn(meta);  /* FUN_00023c78 */
    fn(b, d, meta);
}

/*--------------------------------------------------------------------*/
/* FUN_00023c78 @ 0x00023c78   (est. sk_tb_witness_method)
 * Ghidra: long FUN_00023c78(ulong meta)
 * Returns the witness method pointer from `meta`: if the low bit is set, the
 * value is a pointer to a tagged descriptor which is dereferenced; the method
 * lives at (meta+0x14)+signed-32-bit-relative-offset.
 * Confidence: medium */
static long sk_tb_witness_fn(unsigned long meta)
{
    if ((meta & 1) != 0) {
        meta = *(unsigned long *)(meta & 0xfffffffffffffffeULL);
    }
    return (long)(meta + 0x14) + (long)*(int *)(meta + 0x14);
}

/*--------------------------------------------------------------------*/
/* FUN_00023ca8 @ 0x00023ca8   (est. sk_tb_witness_invoke2)
 * Ghidra: void FUN_00023ca8(a, b, meta)
 * Resolves the witness method from `meta` (FUN_00023d00) and calls it with
 * (b, meta).
 * Confidence: medium */
static void sk_tb_witness_invoke2(uint64_t a, uint64_t b, uint64_t meta)
{
    void (*fn)(uint64_t, uint64_t);
    fn = (void *)sk_tb_witness_method2(meta);  /* FUN_00023d00 */
    fn(b, meta);
}

/*--------------------------------------------------------------------*/
/* FUN_00023d00 @ 0x00023d00   (est. sk_tb_witness_method2)
 * Ghidra: long FUN_00023d00(ulong meta)
 * Returns the witness method pointer from `meta` (same algorithm as
 * FUN_00023c78).
 * Confidence: medium */
static long sk_tb_witness_method2(unsigned long meta)
{
    if ((meta & 1) != 0) {
        meta = *(unsigned long *)(meta & 0xfffffffffffffffeULL);
    }
    return (long)(meta + 0x14) + (long)*(int *)(meta + 0x14);
}

/*--------------------------------------------------------------------*/
/* FUN_00023d54 @ 0x00023d54   (est. sk_tb_buf_offset)
 * Ghidra: void FUN_00023d54(a, b, off, end)
 * Computes a bounds-checked buffer offset via FUN_00022718(off, end, a).
 * Thin wrapper.
 * Confidence: medium */
static void sk_tb_buf_offset(uint64_t a, uint64_t b, uint64_t off, uint64_t end)
{
    sk_tb_buf_offset_or_trap(off, (long)end, (long)a);  /* FUN_00022718 */
}

/*--------------------------------------------------------------------*/
/* FUN_00023d78 @ 0x00023d78   (est. sk_tb_encode_witness_a)
 * Ghidra: void FUN_00023d78(a, b, meta)
 * Encodes via the witness method: calls FUN_00023c10 with the x20 message as
 * the target and (meta, b, meta) — writes value `b` through the witness.
 * Confidence: medium */
static void sk_tb_encode_witness_a(uint64_t a, uint64_t b, uint64_t meta)
{
    register uint64_t *self asm("x20");
    sk_tb_witness_invoke(a, *self, meta, b, meta);  /* FUN_00023c10 */
}

/*--------------------------------------------------------------------*/
/* FUN_00023d7c @ 0x00023d7c   (est. sk_tb_encode_witness_b)
 * Ghidra: void FUN_00023d7c(a, b, meta)
 * Identical to FUN_00023d78 (thunk pair).
 * Confidence: medium */
static void sk_tb_encode_witness_b(uint64_t a, uint64_t b, uint64_t meta)
{
    register uint64_t *self asm("x20");
    sk_tb_witness_invoke(a, *self, meta, b, meta);  /* FUN_00023c10 */
}

/*--------------------------------------------------------------------*/
/* FUN_00023da8 @ 0x00023da8   (est. sk_tb_encode_witness_result)
 * Ghidra: void FUN_00023da8(out)
 * Encodes a single result via the witness method (FUN_00023ca8); if the status
 * register is 0, stores the returned value (and a zero byte) into `out`, else
 * stores the error into the error word held in x3.
 * Confidence: medium */
static void sk_tb_encode_witness_result(uint64_t *out)
{
    register long status asm("x21");
    register uint32_t *err asm("x3");
    uint64_t v;

    v = 0;
    sk_tb_witness_invoke2(0, 0, 0);  /* FUN_00023ca8() */
    if (status == 0) {
        *out = v;
        *(uint8_t *)(out + 1) = 0;
    } else {
        *err = (uint32_t)v;
    }
}

/*--------------------------------------------------------------------*/
/* FUN_00023f74 @ 0x00023f74   (est. sk_tb_encode_full)
 * Ghidra: void FUN_00023f74(a, b, c, d, e, f, g, h, i)
 * Full Tightbeam encode: builds an encoder closure from the metadata
 * (indirect constructor via SUB_aa0303e052800061), sets up the call object
 * with the six payload fields, dispatches through FUN_00020134 with the
 * encoder worker FUN_000251ec, and if the status register is nonzero invokes
 * the error callback at metadata+0x20.
 * Confidence: medium
 * Notes: FUN_000251ec = encode worker; SUB_aa0303e052800061 = Swift closure
 *   builder; the metadata destructor is invoked on failure. */
static void sk_tb_encode_full(uint64_t a, uint64_t b, uint64_t c, uint64_t d,
                              uint64_t e, uint64_t f, long g, uint64_t h, uint64_t i)
{
    register long status asm("x21");
    long meta = *(long *)(g + -8);
    void (*ctor)(void) = (void *)&sk_tb_encode_full_cb0;
    uint8_t stack[0x40];
    uint8_t *slot = (uint8_t *)(((uintptr_t)stack + 0xf) & ~0xfULL);

    ctor();  /* SUB_aa0303e052800061 */
    sk_tb_encode_dispatch(a, c, (uint64_t)(uintptr_t)sk_tb_encode_worker,
                          (uint64_t)(uintptr_t)slot, f, g, h,
                          (uint64_t)(uintptr_t)slot);  /* FUN_00020134 */
    if (status != 0) {
        (*(void (**)(uint64_t, void *, long))(meta + 0x20))(i, slot, g);
    }
}

static void sk_tb_encode_full_cb0(void) { }

/*--------------------------------------------------------------------*/
/* FUN_00024068 @ 0x00024068   (est. sk_tb_msg_copy_wrap2)
 * Ghidra: void FUN_00024068(out)
 * Shallow-copies the TightbeamMessage wrapper from x20 into `out` (49 bytes).
 * Confidence: medium
 * Notes: identical to FUN_000214b0. */
static void sk_tb_msg_copy_wrap2(uint8_t *out)
{
    register uint8_t *self asm("x20");
    out[0] = self[0] & 1;
    *(uint64_t *)(out + 0x10) = *(uint64_t *)(self + 0x10);
    *(uint64_t *)(out + 0x08) = *(uint64_t *)(self + 0x08);
    *(uint64_t *)(out + 0x20) = *(uint64_t *)(self + 0x20);
    *(uint64_t *)(out + 0x18) = *(uint64_t *)(self + 0x18);
    *(uint64_t *)(out + 0x28) = *(uint64_t *)(self + 0x28);
    out[0x30] = self[0x30];
}

/*--------------------------------------------------------------------*/
/* FUN_00024098 @ 0x00024098   (est. sk_tb_decoder_init_empty)
 * Ghidra: void FUN_00024098(out)
 * Initializes an empty TightbeamDecoder: calls FUN_000259c0 to build a fresh
 * scratch wrapper and copies its six fields plus kind byte into `out`.
 * Confidence: medium */
static void sk_tb_decoder_init_empty(uint64_t *out)
{
    uint8_t buf[0x40];
    uint8_t *tmp = (uint8_t *)(((uintptr_t)buf + 0xf) & ~0xfULL);

    sk_tb_msg_init((uint64_t)(uintptr_t)tmp);  /* FUN_000259c0 */
    out[1] = *(uint64_t *)(tmp + 0x10);
    out[0] = *(uint64_t *)(tmp + 0x08);
    out[3] = *(uint64_t *)(tmp + 0x20);
    out[2] = *(uint64_t *)(tmp + 0x18);
    out[5] = *(uint64_t *)(tmp + 0x28);
    out[4] = *(uint64_t *)(tmp + 0x00);
    *(uint8_t *)(out + 6) = tmp[0x30];
}

/*--------------------------------------------------------------------*/
/* FUN_000240e4 @ 0x000240e4   (est. sk_tb_msg_reset)
 * Ghidra: undefined8 FUN_000240e4(a, b)
 * Resets the TightbeamMessage in x20: inspects the storage descriptor tag
 * (bits 32>>29). For tags 1/2 the payload buffer at self+0x10 must be present
 * and is merged via FUN_00014f90 (or FUN_00014c08 for tag 0), retaining the
 * buffer. The reset rejects messages that are already unwrapped (fatal 0x93)
 * or that have an invalid storage kind (fatal 0x49/0x4d "reset called on").
 * Returns the message pointer on success.
 * Confidence: medium
 * Notes: storage tag from (uVar9>>32)>>29; strings s_TightbeamMessage_reset___called_o_*.
 */
static uint64_t sk_tb_msg_reset_status(uint64_t a, uint64_t b)
{
    register char *self asm("x20");
    unsigned long stg;
    uint32_t tag, tag2;
    long bufdesc, payload;
    uint32_t code;
    int *codeptr;
    uint64_t r;
    cl4_result_t err;

    stg = *(unsigned long *)(self + 8);
    tag = (uint32_t)(stg >> 32) >> 29;
    if (tag != 0) {
        if (tag < 2) {              /* tag == 1 */
            bufdesc = *(long *)((stg & 0x1fffffffffffffffULL) + 0x10);
            if (bufdesc == 0) {
                __builtin_trap();  /* SoftwareBreakpoint(1, 0x242a8) */
            }
            payload = *(long *)(self + 0x10);
            if (payload == 0) goto already_unwrapped;
            sk_retain(stg & 0x1fffffffffffffffULL);  /* FUN_0036b270 */
            r = sk_tb_msg_reset_buf((uint64_t)(uintptr_t)payload, a, 0, 0);  /* FUN_00014f90 */
            code = (uint32_t)r;
            if (code == 0) {
                goto release_and_ok;
            }
            err = sk_tb_make_error(0);          /* FUN_00019aac */
            codeptr = (int *)&code;
        } else {
            tag2 = (uint32_t)(stg >> 32) >> 29;
            if (tag2 != 2) {
                if (tag2 == 3) {
                    sk_swift_fatal("Fatal error", 0xb, 2, 0xd000000000000049ULL,
                                   (uint64_t)((char *)0x005ad270 + -0x20) | 0x8000000000000000ULL,
                                   0x005ad220, 0x20, 2, 0x1a6, 0); /* FUN_001afa84 */
                }
                sk_swift_fatal("Fatal error", 0xb, 2, 0xd00000000000004dULL,
                               (uint64_t)((char *)0x005ad220 + -0x20) | 0x8000000000000000ULL,
                               0x005ad220, 0x20, 2, 0x1a8, 0); /* FUN_001afa84 */
            }
            bufdesc = *(long *)((stg & 0x1fffffffffffffffULL) + 0x10);
            if (bufdesc == 0) {
                __builtin_trap();  /* SoftwareBreakpoint(1, 0x242ac) */
            }
            payload = *(long *)(self + 0x10);
            if (payload == 0) goto already_unwrapped;
            sk_retain(stg & 0x1fffffffffffffffULL);  /* FUN_0036b270 */
            r = sk_tb_msg_reset_buf((uint64_t)(uintptr_t)payload, a, 0, 0);  /* FUN_00014f90 */
            code = (uint32_t)r;
            if (code == 0) goto release_and_ok;
            err = sk_tb_make_error(0);          /* FUN_00019aac */
            codeptr = (int *)&code;
        }
        sk_tb_error_report(codeptr, err.lo, 0x0065a550ULL);  /* FUN_003698b0 */
        sk_free(stg & 0x1fffffffffffffffULL);         /* FUN_0036b118 */
        return r;
    }
    /* tag == 0 */
    payload = *(long *)(self + 0x10);
    if (payload != 0) {
        r = *(uint64_t *)(stg + 0x10);
        sk_retain(stg);                    /* FUN_0036b270 */
        r = sk_tb_msg_reset2(payload, a);                        /* FUN_00014c08 */
        code = (uint32_t)r;
        if (code == 0) {
            sk_free(stg & 0x1fffffffffffffffULL);  /* FUN_0036b118 */
            return a;
        }
        err = sk_tb_make_error(0);                 /* FUN_00019aac */
        sk_tb_error_report((int *)&code, err.lo, 0x0065a550ULL);  /* FUN_003698b0 */
        goto release_err;
    }
already_unwrapped:
    sk_swift_fatal("Fatal error", 0xb, 2, 0xd000000000000022ULL,
                   (uint64_t)((char *)0x005acf80 + -0x20) | 0x8000000000000000ULL,
                   0x005acf50, 0x20, 2, 0x93, 0); /* FUN_001afa84 */
release_and_ok:
    sk_free(stg & 0x1fffffffffffffffULL);  /* FUN_0036b118 */
    return a;
release_err:
    sk_free(stg & 0x1fffffffffffffffULL);  /* FUN_0036b118 */
    return r;
}

/*--------------------------------------------------------------------*/
/* FUN_0002437c @ 0x0002437c   (est. sk_tb_msg_encode_init)
 * Ghidra: void FUN_0002437c(out, self, a, b, int *err)
 * Initializes a TightbeamMessage for encoding from the wrapper in x20 and the
 * source `self` message: copies the source buffer fields, builds a metadata
 * call (FUN_003ed2dc), and on success (status reg 0) writes the assembled
 * wrapper into `out`. On failure it reports the error (FUN_00365b6c / make
 * error 0), releases the message, and traps with a fatal error (diagnostic
 * 0x2f). Complex Swift encode bootstrap.
 * Confidence: low
 * Notes: heavy use of NEON-ext (vector shuffle) for the 16-byte field groups;
 *   DAT_004bbc28/0x004bbc30 metadata; FUN_003ed2dc = sk_tb_metadata_call. */
static void sk_tb_msg_encode_init(uint64_t *out, uint8_t *srcmsg, uint64_t a, uint64_t b,
                                  uint32_t *err)
{
    register long status asm("x21");
    uint64_t s08 = *(uint64_t *)(srcmsg + 8);
    uint64_t s10 = *(uint64_t *)(srcmsg + 0x10);
    uint64_t s18 = *(uint64_t *)(srcmsg + 0x18);
    uint64_t s20 = *(uint64_t *)(srcmsg + 0x20);
    uint64_t s28 = *(uint64_t *)(srcmsg + 0x28);
    uint8_t  s30 = srcmsg[0x30];
    uint8_t  s00 = srcmsg[0] & 1;
    uint8_t  msg_buf[0x40];
    uint8_t *msg = (uint8_t *)(((uintptr_t)msg_buf + 0xf) & ~0xfULL);

    sk_tb_metadata_call(0x004bbc28, (uint64_t)(uintptr_t)msg, 0x67b148);  /* FUN_003ed2dc */
    if (status == 0) {
        if (s00 != 2) {
            sk_tb_msg_deinit();  /* FUN_00025704 (source copy retained) */
        }
        out[1] = *(uint64_t *)(msg + 0x10);
        out[0] = *(uint64_t *)(msg + 0x08);
        out[3] = *(uint64_t *)(msg + 0x20);
        out[2] = *(uint64_t *)(msg + 0x18);
        out[5] = *(uint64_t *)(msg + 0x28);
        out[4] = *(uint64_t *)(msg + 0x00);
        *(uint8_t *)(out + 6) = msg[0x30];
    } else {
        sk_retain(0);                 /* FUN_0036b270 */
        sk_tb_make_error_obj(0x0064c260, 0x004bbc30);  /* FUN_00002534 */
        {
            cl4_result_t vr = sk_tb_make_error(0);  /* FUN_00019aac */
            uint64_t v = vr.lo;
            int rc = sk_tb_error_set((uint64_t)(uintptr_t)&a, (uint64_t)(uintptr_t)&b, v, 0, 0);  /* FUN_00365b6c */
            if (rc == 0) {
                sk_free((uint64_t)(uintptr_t)status);      /* FUN_0036b118 */
                sk_retain(0);
                sk_tb_error_log(0x13);        /* FUN_002a4ab4 */
                sk_tb_error_push(0xd000000000000011ULL, 0x80000000005ad120ULL);
                sk_tb_msg_reset_buf(a, 0x6756a8, 0x66e1b8, 0);  /* FUN_00205844 */
                sk_swift_fatal("Fatal error", 0xb, 2, 0, 0xe000000000000000ULL,
                               0x005acf50, 0x20, 2, 0x2f, 0); /* FUN_001afa84 */
            }
            sk_free(0);
            sk_tb_error_report((int *)&b, v, 0x0065a550ULL);  /* FUN_003698b0 */
            sk_free((uint64_t)(uintptr_t)status);
            if (s00 != 2) {
                sk_tb_msg_deinit();  /* FUN_00025704 */
            }
            *err = 0;
        }
    }
}

/*--------------------------------------------------------------------*/
/* FUN_00024678 @ 0x00024678   (est. sk_tb_encode_async)
 * Ghidra: void FUN_00024678(a, b, c, d, e, f)
 * Starts an asynchronous encode: stores the five arguments into the x22
 * context at offsets 0xb8..0xd8, then dispatches the continue label
 * LAB_000246a4 (FUN_00408db8). Tightbeam async state-machine bootstrap.
 * Confidence: medium */
static void sk_tb_encode_async(uint64_t a, uint64_t b, uint64_t c, uint64_t d,
                               uint64_t e, uint64_t f)
{
    register char *ctx asm("x22");
    *(uint64_t *)(ctx + 0xd0) = e;
    *(uint64_t *)(ctx + 0xd8) = f;
    *(uint64_t *)(ctx + 0xc0) = c;
    *(uint64_t *)(ctx + 200) = d;
    *(uint64_t *)(ctx + 0xb8) = b;
    sk_tb_async_dispatch((uint64_t)(uintptr_t)&sk_tb_encode_async_cont, 0, 0);  /* FUN_00408db8 */
}

static void sk_tb_encode_async_cont(void) { }

/*--------------------------------------------------------------------*/
/* FUN_000247d0 @ 0x000247d0   (est. sk_tb_encode_async_step)
 * Ghidra: void FUN_000247d0(void)
 * One async encode step: releases the object at ctx+0xe0 (FUN_0040bd24) and,
 * based on the x20 flag, either continues at LAB_00024924 or stores the saved
 * error code into ctx+0x7c and resumes via FUN_000248a4.
 * Confidence: medium */
static void sk_tb_encode_async_step(void)
{
    register char *ctx asm("x22");
    register long flag asm("x20");
    long c = *(long *)ctx;
    void (*cont)(void);

    sk_tb_async_release(*(uint64_t *)(c + 0xe0));  /* FUN_0040bd24 */
    if (flag == 0) {
        cont = sk_tb_encode_async_done;          /* LAB_00024924 */
    } else {
        *(uint32_t *)(c + 0x7c) = *(uint32_t *)(c + 0x44);
        cont = sk_tb_encode_async_retry;         /* FUN_000248a4 */
    }
    sk_tb_async_dispatch((uint64_t)(uintptr_t)cont, 0, 0);            /* FUN_00408db8 */
}


/* Asynchronous-encode continuation reached when the encode step reports no
 * error (LAB_00024924). No-op terminal state of the async state machine. */
static void sk_tb_encode_async_done(void)
{
}

/*--------------------------------------------------------------------*/
/* FUN_000248a4 @ 0x000248a4   (est. sk_tb_encode_async_retry)
 * Ghidra: void FUN_000248a4(void)
 * Retry step of the async encoder: reads the saved error from ctx+0x7c,
 * reports it (FUN_0036993c), stores it into the result word, and resumes the
 * continuation at ctx+8.
 * Confidence: medium */
static void sk_tb_encode_async_retry(void)
{
    register char *ctx asm("x22");
    uint32_t err = *(uint32_t *)(ctx + 0x7c);
    uint64_t e = sk_tb_make_error(0).lo;  /* FUN_00019aac */
    uint32_t *dst;
    register uint32_t *rd asm("x1");

    sk_tb_make_error(0);  /* FUN_0036993c(e, 0x0065a550, 0, 0) */
    dst = rd;
    *dst = err;
    (*(void (**)(void))(ctx + 8))();  /* resume continuation */
}

/*--------------------------------------------------------------------*/
/* FUN_00024e40 @ 0x00024e40   (est. sk_tb_decode_async_step)
 * Ghidra: void FUN_00024e40(void)
 * One async decode step: releases the object at ctx+0xf0 (FUN_0040bd24) and,
 * based on the x20 flag, continues at DAT_00025e68 or stores the error and
 * resumes at DAT_00025e5c.
 * Confidence: medium */
static void sk_tb_decode_async_step(void)
{
    register char *ctx asm("x22");
    register long flag asm("x20");
    long c = *(long *)ctx;
    void (*cont)(void);

    sk_tb_async_release(*(uint64_t *)(c + 0xf0));  /* FUN_0040bd24 */
    if (flag == 0) {
        cont = (void *)0x00025e68;
    } else {
        *(uint32_t *)(c + 0x7c) = *(uint32_t *)(c + 0x44);
        cont = (void *)0x00025e5c;
    }
    sk_tb_async_dispatch((uint64_t)(uintptr_t)cont, 0, 0);            /* FUN_00408db8 */
}

/*--------------------------------------------------------------------*/
/* FUN_00024f14 @ 0x00024f14   (est. sk_tb_msg_write_opt_a)
 * Ghidra: void FUN_00024f14(lo, hi, char present, out)
 * Writes an optional value into the message: if `present` != 1, both lo and hi
 * are passed through to FUN_00018560 (the writer), otherwise zeroes are used.
 * Confidence: medium */
static void sk_tb_msg_write_opt_a(uint64_t lo, uint64_t hi, char present, uint64_t out)
{
    uint64_t v1 = 0, v2 = 0;
    if (present != 1) v1 = hi;
    if (present != 1) v2 = lo;
    sk_tb_append_value(v2, v1);  /* FUN_00018560 */
}

/*--------------------------------------------------------------------*/
/* FUN_00024f18 @ 0x00024f18   (est. sk_tb_msg_write_opt_b)
 * Ghidra: void FUN_00024f18(lo, hi, char present, out)
 * Identical to FUN_00024f14 (thunk pair).
 * Confidence: medium */
static void sk_tb_msg_write_opt_b(uint64_t lo, uint64_t hi, char present, uint64_t out)
{
    uint64_t v1 = 0, v2 = 0;
    if (present != 1) v1 = hi;
    if (present != 1) v2 = lo;
    sk_tb_append_value(v2, v1);  /* FUN_00018560 */
}

/*--------------------------------------------------------------------*/
/* FUN_00024f40 @ 0x00024f40   (est. sk_tb_transport_encode)
 * Ghidra: void FUN_00024f40(a, b, c, d, flags, size, enc, e, f, self, g, h)
 * TransportBuffer encode: builds an encoder closure, checks the buffer size
 * (fatal if > 1 word, TransportBuffer diagnostic 0x3b / 0x25), assembles a
 * message descriptor (FUN_000159b8), invokes the encode closure, and hands the
 * resulting buffer back (releasing if the size flag is 0). Validates the stack
 * canary.
 * Confidence: low
 * Notes: TransportBuffer strings; FUN_000159b8 = sk_tb_field_init;
 *   thunk_FUN_00012568 = sk_buf_release; FUN_00020d0c = release unless owned. */
static void sk_tb_transport_encode(uint64_t a, uint64_t b, void (*encfn)(void *, void *, void *),
                                   uint64_t d, unsigned long flags, uint32_t size,
                                   void (*cbfn)(uint64_t, void *, void *), uint64_t e,
                                   uint64_t f, long self, uint64_t g, uint64_t h)
{
    register long status asm("x21");
    long canary = TB_CANARY;
    long meta = *(long *)(self + -8);
    uint8_t stack[0x40];
    uint8_t *slot = (uint8_t *)(((uintptr_t)stack + 0xf) & ~0xfULL);
    void (*builder)(void) = (void *)&sk_tb_transport_cb0;
    uint32_t kind;
    uint64_t hdr[8];

    builder();  /* SUB_aa0303e052800061 */
    if (size > 1) {
        sk_swift_fatal("Fatal error", 0xb, 2, 0xd000000000000025ULL,
                       0x80000000005acd00ULL, 0x005accb0, 0x1f, 2); /* FUN_001afa84 */
    }
    kind = 4;
    if ((size & 0xff) != 1) kind = 1;
    hdr[0] = 0;
    hdr[1] = 0;
    hdr[2] = 0;
    hdr[3] = 0;
    hdr[4] = 0;
    hdr[5] = b;
    hdr[6] = sk_tb_field_init();  /* FUN_000159b8 */
    slot[0] = 1;
    *(uint64_t *)(slot + 8) = 0x8000000000000000ULL;
    cbfn(a, slot, slot);          /* (*local_118)(param_1, local_a8, slot) */
    if (status == 0) {
        if ((flags & 0xff) == 0) {
            sk_retain(e);            /* FUN_0036b270 */
            encfn((void *)b, (void *)0, (void *)0);  /* (*pcVar2)(param_2) */
            sk_buf_release(b, -1, -1);  /* thunk_FUN_00012568 */
            sk_tb_release_unless_owned(b, (uint64_t)(uintptr_t)encfn, e, 0);
            flags = 0;
        }
        sk_tb_release_unless_owned(b, (uint64_t)(uintptr_t)encfn, e, flags);
    } else {
        (*(void (**)(uint64_t, void *, long))(meta + 0x20))(h, slot, self);
        if ((flags & 0xff) == 0) {
            sk_retain(e);            /* FUN_0036b270 */
            encfn((void *)b, (void *)0, (void *)0);
            sk_buf_release(b, -1, -1);
            sk_tb_release_unless_owned(b, (uint64_t)(uintptr_t)encfn, e, 0);
            flags = 0;
        }
        sk_tb_release_unless_owned(b, (uint64_t)(uintptr_t)encfn, e, flags);
    }
    if (canary == TB_CANARY) {
        return;
    }
    sk_stack_check(0);  /* FUN_0011d7e8 */
}

static void sk_tb_transport_cb0(void) { }

/*--------------------------------------------------------------------*/
/* FUN_000251ec @ 0x000251ec   (est. sk_tb_encode_worker)
 * Ghidra: void FUN_000251ec(void)
 * Tightbeam encode worker: forwards to FUN_00024f40 (the transport encode).
 * Confidence: medium */
static void sk_tb_encode_worker(void)
{
    sk_tb_transport_encode(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);  /* FUN_00024f40 */
}

/*--------------------------------------------------------------------*/
/* FUN_00025228 @ 0x00025228   (est. sk_tb_decode_alloc)
 * Ghidra: undefined8 FUN_00025228(a, b, c, d, e, f, g, h)
 * Allocates a decoder object (type from FUN_000286dc(0), 0x18 bytes),
 * stores `b` into it, runs the decode via FUN_000252d4, and frees the object.
 * Returns the decode result.
 * Confidence: medium */
static uint64_t sk_tb_decode_alloc(uint64_t a, uint64_t b, uint64_t c, uint64_t d,
                                   uint64_t e, uint64_t f, uint64_t g, uint64_t h)
{
    uint64_t meta = (uint64_t)sk_tb_type_metadata(0);  /* FUN_000286dc(0) */
    long obj = (long)sk_alloc(meta, 0x18);            /* FUN_0036a940 */
    uint64_t r;

    *(uint64_t *)(obj + 0x10) = b;
    r = sk_tb_msg_decode2(a, obj, c, d, e, f, g, h);  /* FUN_000252d4 */
    sk_free((uint64_t)(uintptr_t)obj);
    return r;
}

/*--------------------------------------------------------------------*/
/* FUN_000252d4 @ 0x000252d4   (est. sk_tb_msg_decode2)
 * Ghidra: long FUN_000252d4(a, obj, c, d, e, f, g, h)
 * Decodes a message using the decoder object `obj` (whose witness method is
 * resolved via FUN_00025dcc): retains obj, calls the witness with the message
 * descriptor, and returns the decoded payload. If the result kind is not 2
 * (ok), it unwraps and fatal-traps (0x93) on a missing payload.
 * Confidence: medium
 * Notes: FUN_0001fd9c releases the scratch storage; witness from FUN_00025dcc. */
static long sk_tb_msg_decode2(uint64_t a, unsigned long obj, uint64_t c, uint64_t d,
                              uint64_t e, uint64_t f, uint64_t g, uint64_t h)
{
    uint64_t v;
    void (*witness)(uint8_t *, uint8_t *, uint64_t, uint64_t, uint64_t, uint8_t *, uint64_t, uint64_t);
    uint8_t msg[0x20];
    uint8_t *m = (uint8_t *)(((uintptr_t)msg + 0xf) & ~0xfULL);
    uint8_t desc[8];
    uint64_t res;
    unsigned long result;

    v = sk_tb_field_init();  /* FUN_000159b8 */
    *(uint64_t *)(desc + 8) = 0x8000000000000000ULL;
    sk_tb_storage_deinit((uint64_t)(uintptr_t)desc);  /* FUN_0001fd9c */
    desc[0] = 1;
    result = obj | 0x4000000000000000ULL;
    witness = (void *)sk_tb_witness_method(h);  /* FUN_00025dcc */
    sk_retain(obj);                     /* FUN_0036b270 */
    witness(m, desc, c, d, e, (uint8_t *)&f, g, h);
    if ((m[0] & 0xff) == 2) {
        res = 0;
    } else {
        if (*(long *)(m + 8) == 0) {
            sk_swift_fatal("Fatal error", 0xb, 2, 0xd000000000000022ULL,
                           (uint64_t)((char *)0x005acf60 + -0x20) | 0x8000000000000000ULL,
                           0x005acf50, 0x20, 2, 0x93, 0); /* FUN_001afa84 */
        }
        sk_tb_msg_deinit();  /* FUN_00025704 */
    }
    return (long)res;
}

/*--------------------------------------------------------------------*/
/* FUN_000254d4 @ 0x000254d4   (est. sk_tb_transport_buffer_init)
 * Ghidra: void FUN_000254d4(out, base, len, cap, byte kind, undefined6, flags)
 * Initializes a TransportBuffer: allocates a 0x58-byte descriptor, sets its
 * fields from the source, and if `kind` < 2 copies the buffer info and flags
 * into `out`; otherwise traps with a fatal error (TransportBuffer, diagnostic
 * 0x3b / 0x25).
 * Confidence: low
 * Notes: FUN_0036a804(0x58, -1) = raw alloc; FUN_0001586c = buffer copy. */
static void sk_tb_transport_buffer_init(uint8_t *out, uint64_t base, uint64_t len,
                                        uint64_t cap, uint8_t kind, uint8_t six, unsigned long flags)
{
    uint32_t *desc;

    desc = (uint32_t *)sk_alloc_raw(0x58, 0xffffffffffffffffULL);  /* FUN_0036a804 */
    *desc = 0;
    if (kind < 2) {
        sk_tb_msg_copy_fields((uint64_t)(uintptr_t)desc, base, six, 0, 0, 0, 0, 0); /* FUN_0001586c */
        if ((flags & 0xff00000000ULL) != 0x100000000ULL) {
            *desc = (uint32_t)flags;
        }
        out[0] = 0;
        *(uint64_t *)(out + 8) = 0x8000000000000000ULL;
        *(uint32_t **)(out + 0x10) = desc;
        *(uint64_t *)(out + 0x18) = base;
        *(uint64_t *)(out + 0x20) = len;
        *(uint64_t *)(out + 0x28) = cap;
        out[0x30] = kind;
        return;
    }
    sk_swift_fatal("Fatal error", 0xb, 2, 0xd000000000000025ULL,
                   0x80000000005acd00ULL, 0x005accb0, 0x1f, 2, 0x3b, 0); /* FUN_001afa84 */
}

/*--------------------------------------------------------------------*/
/* FUN_000255d8 @ 0x000255d8   (est. sk_tb_msg_deinit_encode)
 * Ghidra: void FUN_000255d8(void)
 * Deinit/encode finalize for a TightbeamMessage: if the wrapper kind byte at
 * self+0x30 is not -1, invokes the writer (closure in x12) on the buffer
 * fields and, if the status register is nonzero, calls the error callback;
 * otherwise traps with a fatal error (diagnostic 0x182, error 0x2a).
 * Confidence: low */
static void sk_tb_msg_deinit_encode(void)
{
    register char *self asm("x20");
    register long status asm("x21");
    register long meta_in asm("x3");
    register uint64_t arg5 asm("x5");
    register void (*writer)(void *, void *) asm("x12");
    long meta = *(long *)(meta_in + -8);
    uint8_t stack[0x40];
    uint8_t *slot = (uint8_t *)(((uintptr_t)stack + 0xf) & ~0xfULL);
    void (*builder)(void) = (void *)&sk_tb_msg_deinit_cb0;

    builder();  /* SUB_aa0303e052800061 */
    if ((uint8_t)self[0x30] != 0xff) {
        writer(self + 0x18, slot);
        if (status != 0) {
            (*(void (**)(uint64_t, void *, long))(meta + 0x20))(arg5, slot, meta_in);
        }
        return;
    }
    sk_swift_fatal("Fatal error", 0xb, 2, 0xd00000000000002aULL,
                   0x80000000005ad140ULL, 0x005acf50, 0x20, 2); /* FUN_001afa84 */
}

static void sk_tb_msg_deinit_cb0(void) { }

/*--------------------------------------------------------------------*/
/* FUN_00025704 @ 0x00025704   (est. sk_tb_msg_deinit)
 * Ghidra: void FUN_00025704(void)
 * Destroys the TightbeamMessage in x20. If a payload buffer is present and not
 * owned (kind bit 0 clear), it releases the buffer according to the storage
 * descriptor tag: tag 1 → FUN_00014f10, tag 2 → FUN_00014bec, other tags →
 * releases via the wrapper buffer fields (calling the release closure and
 * FUN_00012568). Then releases the storage descriptor (FUN_0001fd9c) and, if
 * the kind byte is not 0xff, releases the buffer fields (closure + FUN_00012568).
 * Confidence: high
 * Notes: FUN_00015964 = sk_tb_field_release; thunk_FUN_00012568 = sk_buf_release;
 *   fatal 0x4e/0x1ba on a mismatched storage tag. */
static void sk_tb_msg_deinit(void)
{
    register char *self asm("x20");
    long payload;
    unsigned long stg;
    uint32_t tag, tag2;
    long bufdesc;
    uint8_t  kind;
    uint64_t b18, b20, b28;
    void (*releasefn)(uint64_t);

    payload = *(long *)(self + 0x10);
    if ((payload != 0) && ((*self & 1) == 0)) {
        stg = *(unsigned long *)(self + 8);
        tag = (uint32_t)(stg >> 32) >> 29;
        if (tag != 3) {
            if (tag == 1) {
                bufdesc = *(long *)((stg & 0x1fffffffffffffffULL) + 0x10);
                if (bufdesc == 0) {
                    __builtin_trap();  /* SoftwareBreakpoint(1, 0x25814) */
                }
                sk_tb_msg_release_buf((uint64_t)(uintptr_t)bufdesc, (uint64_t)(uintptr_t)payload);  /* FUN_00014f10 */
            } else {
                tag2 = (uint32_t)(stg >> 32) >> 29;
                if (tag2 != 0) {
                    kind = self[0x30];
                    if (kind != 0xff) {
                        b18 = *(uint64_t *)(self + 0x18);
                        releasefn = *(void (**)(uint64_t))(self + 0x20);
                        b28 = *(uint64_t *)(self + 0x28);
                        if (kind == 0) {
                            sk_retain(b28);       /* FUN_0036b270 */
                            releasefn(b18);
                            sk_buf_release(b18, -1, -1);  /* thunk_FUN_00012568 */
                            sk_tb_release_unless_owned(b18, (uint64_t)(uintptr_t)releasefn, b28, 0);
                            kind = 0;
                        }
                        sk_tb_release_unless_owned(b18, (uint64_t)(uintptr_t)releasefn, b28, kind);
                    }
                    sk_swift_fatal("Fatal error", 0xb, 2, 0xd00000000000004eULL,
                                   0x80000000005ad170ULL, 0x005acf50, 0x20, 2, 0x1ba, 0);
                }
                sk_tb_msg_release_buf2(*(uint64_t *)((stg & 0x1fffffffffffffffULL) + 0x10),
                                       (uint64_t)(uintptr_t)payload);  /* FUN_00014bec */
            }
        }
        sk_tb_field_release((uint64_t)(uintptr_t)payload);  /* FUN_00015964 */
        sk_buf_release((uint64_t)(uintptr_t)payload, -1, -1);  /* thunk_FUN_00012568 */
    }
    stg = *(unsigned long *)(self + 8);
    sk_tb_storage_deinit(stg);  /* FUN_0001fd9c */
    kind = self[0x30];
    if (kind != 0xff) {
        b18 = *(uint64_t *)(self + 0x18);
        releasefn = *(void (**)(uint64_t))(self + 0x20);
        b28 = *(uint64_t *)(self + 0x28);
        if (kind == 0) {
            sk_retain(b28);       /* FUN_0036b270 */
            releasefn(b18);
            sk_buf_release(b18, -1, -1);
            sk_tb_release_unless_owned(b18, (uint64_t)(uintptr_t)releasefn, b28, 0);
            kind = 0;
        }
        sk_tb_release_unless_owned(b18, (uint64_t)(uintptr_t)releasefn, b28, kind);
    }
}
