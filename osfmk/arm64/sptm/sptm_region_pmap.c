/* Recreated from sptm.t8142.release.im4p (SPTM, arm64e, image base 0) — the
 * Secure Page Table Monitor (GL2). Ground truth: Ghidra FUN_ names + addresses;
 * public API names from docs/sptm/headers/sptm_common.h. All names are
 * estimates unless header-matched.
 *
 * This file covers the SPTM pmap / guest-adjacent region
 * (0xeb000 - 0xf9000): the hibernation image restore path (sptm_hib_restore),
 * the page-table region update/restore helpers, and the SPTM panic printers.
 * Ghidra function names are in the per-function header comments; all body
 * identifiers are English reconstructions. */

#include "sptm_internal.h"

#include <stdint.h>
#include <stddef.h>
#include <stdarg.h>
#include <stdbool.h>

/* -------------------------------------------------------------------------
 * Shared extern contract for the SPTM recreation.  These are the canonical
 * signatures the whole region agrees on; each is defined in its own
 * reconstruction file (not here) unless noted "(defined in this file)".
 * ------------------------------------------------------------------------- */

/* Noreturn panic printers (defined in this file).  FUN_000f8804 is the core
 * printf-style panic; FUN_000f8844 prints with an explicit error code;
 * FUN_000f8824 / FUN_000f8834 are the shorter continuation variants. */
__attribute__((noreturn)) void sptm_panic(const char *fmt, ...);                 /* FUN_000f8804 */
__attribute__((noreturn)) void sptm_panic_code(unsigned int code, uintptr_t arg,
        const char *fmt, ...);                                                  /* FUN_000f8844 */
__attribute__((noreturn)) void sptm_panic_fmt(uint32_t code, ...);               /* FUN_000f8824 */
__attribute__((noreturn)) void sptm_panic_bad_dt(const char *fmt, ...);          /* FUN_000f8834 */

/* Formatting / console / panic-record helpers (defined elsewhere). */
extern uint32_t sptm_snprintf(char *dst, uint64_t dstsz, uint64_t n1, uint64_t n2,
        const char *fmt, ...);                                                  /* FUN_000ad278 */
extern void sptm_serial_str(const char *s);                                     /* FUN_000c15b4 */
extern void sptm_copy_format(void *dst, uint64_t dstsz, uint64_t n, const char *src); /* FUN_000c59b8 */
extern uint64_t sptm_strlcpy_chk(char *dst, const char *src, uint64_t dstsz,
        uint64_t max);                                                          /* FUN_000ae278 */
extern void sptm_bzero(void *dst, uint64_t n);                                  /* FUN_000abb60 */

/* Per-CPU / dispatch / guest-exit helpers. */
extern uint32_t sptm_get_panicking_cpu_id(void);                                /* FUN_000c5a18 */
extern const char *sptm_dispatch_name(uint64_t id);                             /* FUN_000e7678 */
extern void sptm_guest_exit_handoff(uint64_t buf, uint64_t a, uint64_t b,
        uint64_t c);                                                            /* FUN_000a1374 */
extern void sptm_record_panic_cpu(uint64_t cpu_id);                             /* FUN_000d6088 */

/* Panic-record / config globals (Ghidra DAT_000a5028 / DAT_000aa018 /
 * DAT_001012d8).  Declared here so this file is self-contained. */
extern uint64_t sptm_panic_record_base;       /* DAT_000a5028 — SPTM panic record */
extern uint64_t sptm_panic_record_alt;        /* DAT_000aa018 — alternate record base */
extern uint32_t sptm_panic_config_flags;      /* DAT_001012d8 — panic path config bits */
extern char sptm_panic_fallback_buf[];        /* DAT_00106183 — fallback panic buffer */

/* -------------------------------------------------------------------------
 * Hardware / intrinsic helpers.
 * ------------------------------------------------------------------------- */

/* SPTM per-CPU state pointer: EL2 system register (3,6,0xf,8,0) carries the
 * per-CPU state base; if 0, fall back to tpidr_el2; else the EL2 sysreg
 * (3,6,0xf,0xb,1).  Matches the pattern used throughout the decompile. */
static inline uint64_t sptm_per_cpu_base(void)
{
	uint64_t base;
	__asm__ volatile("mrs %0, s3_6_c15_c8_0" : "=r"(base));
	if (base == 0) {
		__asm__ volatile("mrs %0, tpidr_el2" : "=r"(base));
		return base;
	}
	__asm__ volatile("mrs %0, s3_6_c15_c11_1" : "=r"(base));
	return base;
}

static inline uint32_t sptm_spsel(void)
{
	uint64_t spsel;
	__asm__ volatile("mrs %0, spsel" : "=r"(spsel));
	return (uint32_t)spsel;
}

static inline uint64_t sptm_read_sctlr_el2(void)
{
	uint64_t v;
	__asm__ volatile("mrs %0, sctlr_el2" : "=r"(v));
	return v;
}

static inline void sptm_wfe(void)
{
	__asm__ volatile("wfe" ::: "memory");
}

/* SoftwareBreakpoint(op, addr): the SPTM debug/panic breakpoint primitive. */
static inline __attribute__((noreturn)) void sptm_sw_breakpoint(uint32_t op, uintptr_t addr)
{
	(void)op; (void)addr;
	__builtin_trap();
}

/* Per-CPU panic message buffer size (the 0xa28-byte region at cpu+3). */
#define SPTM_PANIC_BUF_SIZE   0xa28


/* ---- Shared types (added by orchestrator; used by the whole region). ---- */

/* A 16-byte return convention matching the decompiler's {x0, x1} pairs. */
typedef struct sptm_ret2 {
	uint64_t lo;    /* value / pointer */
	uint64_t hi;    /* error code */
} sptm_ret2_t;

typedef uint32_t sptm_return_t;

/* Frame table entry (FTE): one 16-byte entry per physical frame. */
typedef union sptm_frame_table_entry {
	struct {
		uint8_t b[16];
	} bytes;
	struct {
		uint16_t refcnt;        /* +0x00 rw-guard refcount (LOAcquire/LORelease) */
		uint8_t  type;          /* +0x02 frame type */
		uint8_t  flags_a;       /* +0x03 */
		uint32_t word4;         /* +0x04 */
		uint16_t sub_refcnt;    /* +0x08 (puVar[4]) */
		uint16_t parent_flags;  /* +0x0a (puVar[5]); bit15 = nested */
		uint16_t attr_idx;      /* +0x0c (puVar[6]) page-table attribute index */
		uint16_t flags_e;       /* +0x0e (puVar[7]) */
	} f;
} sptm_frame_table_entry_t;

/* Frame-type constants (values from docs/sptm/headers/sptm_common.h). */
#define SPTM_KERNEL_ROOT_TABLE        0x08
#define XNU_USER_ROOT_TABLE           0x12
#define XNU_SHARED_ROOT_TABLE         0x13
#define XNU_PAGE_TABLE                0x14
#define XNU_SUBPAGE_USER_ROOT_TABLES  0x28
/* sptm_region_1.c — SPTM hibernation image restore (sptm_hib_restore).
 * Ground truth: FUN_000eb004 @ 0x000eb004.  Appended to the shared preamble
 * (/tmp/sptm_region_preamble.c) for standalone compilation.
 *
 * All identifiers are English reconstructions; Ghidra names live only in
 * comments.  See the per-function header for details.
 *
 * NOTE on reconstruction scope: the decompiler re-reads tpidrro_el0 and
 * re-validates the three slides (restore_slide/hibtext_slide/fixup_slide) at
 * almost every step (panics 0x1ce/0x1cf/0x1d0 or fatal 0xcafebee5).  These
 * values do not change across the function, so they are validated once at
 * entry and cached.  The panic-record tail writes slide-relative SPTM globals
 * (DAT_00094000/0009e000/000a5000/000aa018/000a5028); the ones exposed by the
 * shared contract are captured directly, the rest are summarized in one
 * comment block. */

#include <stdint.h>
#include <stddef.h>

/* -------------------------------------------------------------------------
 * New externs for helpers NOT in the shared preamble (canonical signatures
 * agreed across the region slices).
 * ------------------------------------------------------------------------- */

/* Panic printers. */
__attribute__((noreturn)) void sptm_panic_code_msg(uint32_t code, const char *msg);   /* FUN_000e9ecc */
__attribute__((noreturn)) void sptm_panic_ctx(const char *file, uint32_t code,
        const char *msg, uint64_t val, uint64_t extra);                              /* FUN_000e9f28 */
__attribute__((noreturn)) void sptm_fatal(uint32_t code);                            /* FUN_0009c2c8 */

/* Allocator: returns pointer; kind=2, flags 0/1 observed. */
extern void *sptm_alloc(uint32_t kind, uint64_t flags);                              /* FUN_000eaa44 */

/* SHA / HMAC / ACE helpers. */
extern uint64_t sptm_sha_ctx_get(void);                                              /* FUN_000b25a0 */
extern void sptm_sha_init(uint64_t ctx, void *out);                                  /* FUN_000ae8b4 */
extern void sptm_sha_update(uint64_t ctx, void *out, uint64_t len, const void *src); /* FUN_000aeaa4 */
extern void sptm_ace_finalize(uint64_t ctx, void *in, void *out);                    /* FUN_000bf874 */

/* CTRR key derivation. */
extern void sptm_ctrr_key(uint64_t ctx, void *dst, const char *key, uint64_t len);   /* FUN_000becd0 */

/* Memory primitives. */
extern void sptm_memcpy(void *dst, const void *src, uint64_t n);                     /* FUN_000abeb0 */
extern int  sptm_memcmp(const void *a, const void *b, uint64_t n);                   /* FUN_000abcd0 */

/* Hibernation restore helpers. */
extern void sptm_hib_ctrr_region(uint64_t cpu, uint64_t region_start, uint64_t region_end,
        const void *key, uint32_t tag, const void *expected_hmac);              /* FUN_000ed244 */
extern void sptm_hib_disjoint_region(void *src, uint64_t size, void *dst, void *scratch,
        uint32_t dst_paddr_page);                                               /* FUN_000ecd20 */
extern void sptm_hib_disjoint_update(void *list, void *src, uint64_t size, uint32_t flag);/* FUN_000ed0f0 */

/* Slide-maintenance and key-zeroize helpers (observed signatures). */
extern void sptm_hib_slide_commit(uint64_t a, uint64_t b, uint64_t c);               /* FUN_000b7eec */
extern void sptm_crypto_zeroize(uint64_t len, void *buf);                            /* FUN_000b2584 */

/* GCM (exclave protected-metadata decryption) helpers. */
extern uint64_t sptm_crypto_gcm_handle(void);                                        /* FUN_000ae504 */
extern uint64_t sptm_crypto_gcm_ctx(uint64_t h);                                     /* FUN_000b2014 */
extern void (*sptm_crypto_ctx_init)(uint64_t ctx, uint64_t aligned);                 /* DAT_00100020 */
extern void sptm_gcm_init(uint64_t h, uint64_t ctx, uint64_t keylen, void *key, void *iv);  /* FUN_000b2020 */
extern void sptm_gcm_stream(uint64_t h, uint64_t ctx, uint64_t len, void *src, void *dst);  /* FUN_000b211c */
extern int  sptm_gcm_finalize(uint64_t h, uint64_t ctx, uint64_t taglen, void *tag);        /* FUN_000b2198 */

/* Assertion / debug printers (the assert path prints then fatals). */
extern void sptm_assert_print_str(const char *s);   /* FUN_000eadf4 */
extern void sptm_assert_print_num(uint32_t v);      /* FUN_000eae44 */
extern void sptm_assert_print_num2(uint32_t v);     /* FUN_000eae78 */

/* Signature magic (DAT_00013408) and CTRR key label strings. */
extern const uint8_t sptm_hib_magic[0x30];          /* DAT_00013408 */
extern const char sptm_key_ctrr_sptm[];             /* s_key_sptm_ctrr_00010f30 "key-sptm-ctrr" */
extern const char sptm_key_ctrr_xnu[];              /* s_key_xnu_ctrr_00010f3e "key-xnu-ctrr" */
extern const char sptm_key_exclave_orig[];          /* s_key_exclave_original_00010f4b */
extern const char sptm_key_exclave[];               /* s_key_exclave_00010f60 */

/* -------------------------------------------------------------------------
 * Local helpers used by the restore body.
 * ------------------------------------------------------------------------- */

/* Assertion-failure emission: mirrors the decompiler's
 * FUN_000eadf4(file) FUN_000eae44(':') FUN_000eae78(line)
 * FUN_000eadf4("Assertion failed: ") <msg> FUN_000eae44(10) then
 * FUN_0009c2c8(0xdebac1e) fatal sequence. */
#define SPTM_ASSERT_FAIL(line, msg) do {                                    \
    sptm_assert_print_str("AppleInternal/Library/BuildRoot/...");           \
    sptm_assert_print_num(0x3a);                                            \
    sptm_assert_print_num2((line));                                         \
    sptm_assert_print_str("Assertion failed: ");                            \
    sptm_assert_print_str((msg));                                           \
    sptm_assert_print_num(10);                                              \
    sptm_fatal(0xdebac1e);                                                  \
} while (0)

/* Hash finalize via the SHA context's method table (offset 0x38). */
#define SPTM_SHA_FINALIZE(sha_ctx, in, out)                                  \
    ((void (*)(uint64_t, void *, void *))(*(uint64_t *)((sha_ctx) + 0x38))) \
        ((sha_ctx), (void *)(in), (void *)(out))

/* Chunked append to a linked-page buffer.  A 0x4000-byte buffer page holds up
 * to 0x3ff8 bytes; at page end the first 8 bytes carry a PAC-tagged pointer to
 * the next page (allocated via sptm_alloc(2,1)).  Mirrors the decompiler's
 * 0x3ff8-chunked memcpy loop exactly (panic 0x91c / 0x92a on invariants). */
static inline long *sptm_buf_append(long *cursor, const void *src, uint64_t len,
                                    uint64_t *count)
{
    const uint8_t *sp = src;
    while (len != 0) {
        uint64_t off = (uint64_t)cursor & 0x3fff;
        if (off > 0x3ff8)
            sptm_panic_code_msg(0x91c, "cur_page_pos < max_page_size");
        long *chunk = cursor;
        if (off == 0x3ff8) {
            chunk = sptm_alloc(2, 1);
            *cursor = (long)chunk;
            if (chunk == NULL)
                sptm_panic_code_msg(0x92a, "next_page_ptr == NULL");
            off = 0;
        }
        uint64_t n = (len <= 0x3ff8 - off) ? len : (0x3ff8 - off);
        sptm_memcpy(chunk, sp, n);
        *count += n;
        long *next = (long *)((uint8_t *)chunk + n);
        if ((((uint64_t)chunk ^ (uint64_t)next) & 0xffc0000000000000) != 0)
            next = (long *)(((uint64_t)next & 0xffffffffffff) | 0xc8a2000000000000);
        cursor = next;
        sp += n;
        len -= n;
    }
    return cursor;
}

/* Chunked read from a linked-page buffer (the inverse walk). */
static inline long *sptm_buf_read(long *cursor, void *dst, uint64_t len,
                                  uint64_t *count)
{
    uint8_t *dp = dst;
    while (len != 0) {
        uint64_t off = (uint64_t)cursor & 0x3fff;
        if (off > 0x3ff8)
            sptm_panic_code_msg(0x91c, "cur_page_pos < max_page_size");
        long *chunk = cursor;
        if (off == 0x3ff8) {
            chunk = (long *)*cursor;
            if (chunk == NULL)
                sptm_panic_code_msg(0x92a, "next_page_ptr == NULL");
            off = 0;
        }
        uint64_t n = (len <= 0x3ff8 - off) ? len : (0x3ff8 - off);
        sptm_memcpy(dp, chunk, n);
        *count += n;
        long *next = (long *)((uint8_t *)chunk + n);
        if ((((uint64_t)chunk ^ (uint64_t)next) & 0xffc0000000000000) != 0)
            next = (long *)(((uint64_t)next & 0xffffffffffff) | 0xc8a2000000000000);
        cursor = next;
        dp += n;
        len -= n;
    }
    return cursor;
}

/* -------------------------------------------------------------------------
 * FUN_000eb004 @ 0x000eb004 (est. sptm_hib_restore)
 * Ghidra: long FUN_000eb004(ulong param_1)   (param_1 = image physical addr)
 *
 * Restores the SPTM hibernation image into the running monitor.  Copies the
 * 0x670-byte hibernation header from the image into the per-CPU hib_ctx,
 * validates every signature field (magic 0x13408) and the image1 size bounds,
 * computes an HMAC over the image header/counters, derives the SPTM/XNU/exclave
 * CTRR keys, iterates the region/paddr tables restoring pages (skipping
 * immutable pages and pre-set bitmap pages, recording in-image pages and
 * handling disjoint regions), hashes the restored page list, decrypts the
 * compressed/protected pages via GCM with the exclave key, reloads the CTRR
 * regions and zeroizes the derived keys, reinstalls the panic-record state, and
 * returns the populated hib_ctx.  Panics on any invalid header/size/immutable
 * page/bitmap/overflow condition.
 * Confidence: high
 * Notes: decompile succeeded (1311 lines).  tpidrro_el0 slide re-validation
 * collapsed to a single entry check.  Panic-record tail summarized.  The
 * double-buffer decrypt's copy-back uses hib_ctx (lVar24) in the decompile —
 * a register-aliasing artifact; reconstructed as copying the decrypted scratch
 * buffer back to the page.  FUN_000ecd20 appears with 4 and 5 args across
 * sites; declared 4-arg (extra 5th page arg dropped at the replay site).
 */
uint64_t sptm_hib_restore(uint64_t image_paddr)
{
    uint64_t cpu = sptm_per_cpu_base();
    if (cpu == 0)
        sptm_fatal(0xcafebee5);

    uint64_t restore_slide = *(uint64_t *)(cpu + 0x10);
    uint64_t hibtext_slide = *(uint64_t *)(cpu + 0x18);
    uint64_t fixup_slide   = *(uint64_t *)(cpu + 0x20);
    if (restore_slide == 0) sptm_panic_code_msg(0x1ce, "hib_ctx->restore_slide == 0");
    if (hibtext_slide == 0) sptm_panic_code_msg(0x1cf, "hib_ctx->hibtext_slide == 0");
    if (fixup_slide   == 0) sptm_panic_code_msg(0x1d0, "hib_ctx->hibtext_fixup_slide == 0");

    sptm_hib_slide_commit(fixup_slide - hibtext_slide, 0, 0);   /* FUN_000b7eec */

    uint64_t hib_ctx = *(uint64_t *)(cpu + 0x70);
    sptm_memcpy((void *)hib_ctx, (const void *)image_paddr, 0x670);   /* copy hib header */

    /* Validate every signature field against the magic constant. */
    if (sptm_memcmp((const void *)(hib_ctx + 0x1e4), sptm_hib_magic, 0x30) == 0)
        sptm_panic_code_msg(0xc01, "memcmp hib_header_copy->imageHeader");
    if (sptm_memcmp((const void *)(hib_ctx + 0x214), sptm_hib_magic, 0x30) == 0)
        sptm_panic_code_msg(0xc02, "memcmp hib_header_copy->handoffHeader");
    if (sptm_memcmp((const void *)(hib_ctx + 0x244), sptm_hib_magic, 0x30) == 0)
        sptm_panic_code_msg(0xc03, "memcmp hib_header_copy->image1Paddr");
    if (sptm_memcmp((const void *)(hib_ctx + 0x274), sptm_hib_magic, 0x30) == 0)
        sptm_panic_code_msg(0xc04, "memcmp hib_header_copy->image2Paddr");
    if (sptm_memcmp((const void *)(hib_ctx + 0x570), sptm_hib_magic, 0x30) == 0)
        sptm_panic_code_msg(0xc05, "memcmp hib_header_copy->protected");
    if (sptm_memcmp((const void *)(hib_ctx + 0x5a0), sptm_hib_magic, 0x30) == 0)
        sptm_panic_code_msg(0xc0c, "memcmp hib_header_copy->sptm_ror");
    if (sptm_memcmp((const void *)(hib_ctx + 0x600), sptm_hib_magic, 0x30) == 0)
        sptm_panic_code_msg(0xc0e, "memcmp hib_header_copy->hib_segs");
    if (*(uint64_t *)(hib_ctx + 0x530) != 0 &&
        sptm_memcmp((const void *)(hib_ctx + 0x5d0), sptm_hib_magic, 0x30) == 0)
        sptm_panic_code_msg(0xc11, "memcmp hib_header_copy->xnu_rorg");

    /* image1 size bounds: nonzero, no address wrap, within the 0x3fffffffc000 cap. */
    uint64_t image1_size = *(uint64_t *)(hib_ctx + 8);
    uint32_t *image_end;
    if (image1_size == 0 ||
        (image_end = (uint32_t *)(image_paddr + image1_size), image_paddr + image1_size < image_paddr) ||
        (uint64_t)image_end > 0x3fffffffc000)
        sptm_panic_ctx("AppleInternal/Library/BuildRoot/...", 0xc19,
                       "Invalid image1 size", image1_size, 0);

    /* Accumulate the slide into the per-CPU CTRR counter (128-bit, carries). */
    {
        uint64_t acc = hibtext_slide + *(uint64_t *)(cpu + 0x1b8);
        if (acc + *(uint64_t *)(cpu + 0x1c0) < acc)          /* CARRY8 */
            sptm_panic_bad_dt("CTRR slide counter overflow");
        *(uint64_t *)(cpu + 0x1b8) = acc;
    }

    uint64_t sha_ctx = sptm_sha_ctx_get();
    *(uint64_t *)(cpu + 0x640) = sha_ctx;

    uint32_t img_base_pg = *(uint32_t *)(hib_ctx + 0xa0);
    uint32_t img_len_pg  = *(uint32_t *)(hib_ctx + 0xa4);
    uint32_t hoff = 0x484f4646;   /* 'HOFF' */
    uint32_t cur_paddr = img_base_pg;
    uint32_t page_size = img_len_pg;

    /* Hash the image header + counters + image data ('HOFF' | base | len | data). */
    sptm_sha_init(sha_ctx, (void *)(cpu + 0x698));
    sptm_sha_update(sha_ctx, (void *)(cpu + 0x698), 4, &hoff);
    sptm_sha_update(sha_ctx, (void *)(cpu + 0x698), 4, &cur_paddr);
    sptm_sha_update(sha_ctx, (void *)(cpu + 0x698), 4, &page_size);
    sptm_sha_update(sha_ctx, (void *)(cpu + 0x698),
                    (uint64_t)img_len_pg << 0xe, (const void *)((uint64_t)img_base_pg << 0xe));
    SPTM_SHA_FINALIZE(sha_ctx, cpu + 0x698, cpu + 0x648);
    sptm_ace_finalize(*(uint64_t *)(cpu + 0x1c8), (void *)(cpu + 0x648), (void *)(cpu + 0x668));
    if (sptm_memcmp((const void *)(cpu + 0x668), (const void *)(hib_ctx + 0x214), 0x30) != 0)
        sptm_panic_code_msg(0x993, "memcmp hib_ctx->hmac_buf, hib_header handoffHeader");

    /* Derive the SPTM and XNU CTRR keys. */
    sptm_ctrr_key(cpu + 0x1b8, (void *)(cpu + 0x728), sptm_key_ctrr_sptm, 0x30);
    sptm_ctrr_key(cpu + 0x1b8, (void *)(cpu + 0x758), sptm_key_ctrr_xnu, 0x30);

    /* Zero the exclave key buffer (0x20 bytes at cpu+0x788). */
    void *exclave_key = (void *)(cpu + 0x788);
    sptm_bzero(exclave_key, 0x20);

    if (*(uint64_t *)(hib_ctx + 0x548) != 0) {
        /* Exclave protected metadata present: derive its key. */
        sptm_ctrr_key(cpu + 0x1b8, exclave_key, sptm_key_exclave_orig, 0x20);
        sptm_ctrr_key(cpu + 0x1b8, (void *)(restore_slide + *(uint64_t *)(hib_ctx + 0x548)),
                      sptm_key_exclave, 0x20);
    }

    /* Restore bookkeeping state. */
    void *page_buf  = sptm_alloc(2, 0);   /* local_130 */
    void *page_buf2 = sptm_alloc(2, 0);   /* local_138 */
    *(uint32_t *)(hib_ctx + 0x90)  = (uint32_t)(image_paddr >> 0xe);
    *(uint32_t *)(hib_ctx + 0x1c4) = 0;
    *(uint32_t *)(hib_ctx + 0x4c)  = 0;   /* disjoint count */
    *(uint32_t *)(hib_ctx + 0x50)  = 0;   /* recorded-region count */

    uint32_t preview_count = *(uint32_t *)(hib_ctx + 0x8c);
    uint64_t src_region_base = *(uint64_t *)(cpu + 0x38);
    uint32_t *preview;
    uint32_t *src_list;
    int use_preview;
    if (preview_count == 0) {
        preview = NULL;
        src_list = (uint32_t *)(src_region_base + *(uint32_t *)(hib_ctx + 0x30));
        use_preview = 0;
    } else {
        preview = *(uint32_t **)(cpu + 0x30);
        src_list = (uint32_t *)((uint8_t *)preview + preview_count);
        use_preview = 1;
    }

    /* Linked-page buffers for recorded pages and compressed-source paddrs. */
    void *record_head = sptm_alloc(2, 1);
    long *record_cursor = (long *)record_head;
    uint64_t record_bytes = 0;
    uint64_t saved_record_bytes = 0;
    long *page_data_cursor = (long *)sptm_alloc(2, 1);   /* plVar9 */
    uint64_t page_data_bytes = 0;
    uint64_t saved_page_data = 0;
    void *page_list = (void *)(cpu + 0x708);   /* list head at cpu+0x708/0x710 */
    *(void **)(cpu + 0x710) = page_list;
    *(uint64_t *)(cpu + 0x718) = 0;
    *(uint64_t *)(cpu + 0x720) = 0;

    int encrypted_pages = 0;     /* local_144 */
    uint32_t entry_pages = 0;
    uint32_t page_idx = 0;
    uint32_t *cur = src_list;
    uint32_t *cur_preview = preview;
    uint32_t *tag_slot;
    void *replay_buffer = NULL;

    uint64_t image1_end_page   = ((uint64_t)image_end + 0x3fff) >> 0xe;      /* local_108 */
    uint64_t src_region_end_page = (src_region_base + *(uint32_t *)(hib_ctx + 0x30) + 0x3fff) >> 0xe; /* local_110 */
    uint64_t preview_end_page   = ((uint64_t)src_list + 0x3fff) >> 0xe;      /* local_128 */
    uint64_t preview_base_page  = 0;                                          /* local_120 */

    /* ---- main region/paddr-table walk ---- */
    if (src_list <= image_end) {
        do {
            cur_paddr = 0;
            if (use_preview != 1) {
                tag_slot = cur + 2;
                if (image_end < tag_slot)
                    sptm_panic_code_msg(0xcd5, "sptm_add overflow src_paddr (2)");
                cur_paddr  = cur[0];
                entry_pages = cur[1];
                cur = cur_preview;
                if (entry_pages != 0) goto process_pages;
                /* zero-count entry: replay the recorded regions, or finish. */
                if (*(int32_t *)(hib_ctx + 0x50) == 0) goto page_hash;
                replay_buffer = sptm_alloc(2, 0);
                saved_record_bytes = record_bytes;
                record_bytes = 0;
                record_cursor = (long *)record_head;
                if (*(int32_t *)(hib_ctx + 0x50) == 0) goto page_hash;
                page_idx = 0;
                goto replay_loop;
            }
            /* preview mode */
            if (preview == NULL)
                sptm_panic_code_msg(0xcc1, "preview_list paddr == 0");
            cur_paddr  = cur_preview[0];
            entry_pages = cur_preview[1];
            tag_slot = cur;
            cur = cur_preview + 2;
            if (entry_pages != 0) goto process_pages;
            tag_slot = (uint32_t *)(src_region_base + *(uint32_t *)(hib_ctx + 0x30));
            if (image_end < tag_slot)
                sptm_panic_code_msg(0xce7, "sptm_add overflow src_paddr (0)");
            use_preview = 0;
            preview += 2;
            cur_preview += 2;
loop_cont:
            cur = tag_slot;
        } while (tag_slot <= image_end);
    }
    sptm_panic_code_msg(0xcbd, "sptm_add overflow src_paddr (0)");   /* list exhausted w/o terminator */

process_pages:
    page_idx = 0;
    preview_base_page = (uint64_t)(uintptr_t)preview >> 0xe;   /* local_120 */
page_loop:
    page_size = 0x4000;
    if (image_end < tag_slot)
        SPTM_ASSERT_FAIL(0xcf5, "sptm_add overflow src_paddr (0)");

    /* destination address must fall within [cpu+0x10, cpu+0x18). */
    {
        uint64_t dst_va = restore_slide + (uint64_t)cur_paddr * 0x4000;
        if (dst_va < *(uint64_t *)(cpu + 0x10) || *(uint64_t *)(cpu + 0x18) <= dst_va)
            SPTM_ASSERT_FAIL(0xd01, "probable dst raddr > hib_ctx");
    }

    /* immutable-page exclusion: panic if the page sits in the immutable range
     * (cpu+0x80..+0x88) but outside the carved exception (cpu+0x90..+0x98). */
    {
        uint64_t paddr_bytes = (uint64_t)cur_paddr << 0xe;
        if (*(uint64_t *)(cpu + 0x80) <= paddr_bytes && paddr_bytes < *(uint64_t *)(cpu + 0x88) &&
            (paddr_bytes < *(uint64_t *)(cpu + 0x90) || *(uint64_t *)(cpu + 0x98) <= paddr_bytes))
            sptm_panic_ctx("AppleInternal/Library/BuildRoot/...", 0xd0a,
                           "attempting to restore immutable page", cur_paddr, 0);
    }

    if (use_preview == 0) {
        /* parse the page tag: signature 0x53, compressed size, compressed bit. */
        uint32_t *scratch = tag_slot + 1;
        if (image_end < scratch)
            SPTM_ASSERT_FAIL(0xd13, "sptm_add overflow src_paddr (s)");
        uint32_t tag = *scratch;
        if (tag >> 0x18 != 0x53)
            SPTM_ASSERT_FAIL(0xd15, "tag & kIOHibernateTagSigMask");
        page_size = tag & 0x7fff;
        if (0x4000 < page_size)
            SPTM_ASSERT_FAIL(0xd1a, "compressed_size < SPTM_PAGE_SIZE");
        if ((tag >> 0x17 & 1) != 0) {
            /* compressed page: record its 4-byte src paddr for later decryption. */
            page_data_cursor = sptm_buf_append(page_data_cursor, &cur_paddr, 4, &page_data_bytes);
            encrypted_pages++;
        }
        tag_slot = scratch;
    }

    /* range/bitmap check: if this page is already present in a recorded range's
     * bitmap, it must not be re-restored. */
    {
        uint64_t *range_list = *(uint64_t **)(cpu + 0x28);
        if (range_list == NULL)
            sptm_panic_code_msg(0x2d0, "list == NULL");
        int n_ranges = *(int32_t *)((uint8_t *)range_list + 8);
        uint32_t *rcur = (uint32_t *)((uint8_t *)range_list + 0xc);
        uint32_t *matched = NULL;
        if (n_ranges != 0) {
            int i = n_ranges;
            do {
                if (rcur[0] <= cur_paddr && cur_paddr <= rcur[1]) { matched = rcur; break; }
                rcur = rcur + 3 + rcur[2];
                i--;
            } while (i != 0);
        }
        if (matched != NULL) {
            uint32_t bit_off = cur_paddr - matched[0];
            if ((int32_t)(matched[(bit_off >> 5) + 3] << (bit_off & 0x1f)) < 0)
                SPTM_ASSERT_FAIL(0xd34, "probable hib page bitmap hib_ctx");
        }
    }

    /* boundary check: is cur_paddr inside one of the recorded/source regions? */
    {
        uint64_t tag_page = (uint64_t)tag_slot >> 0xe;
        uint64_t src_base_page = *(uint64_t *)(cpu + 0x38) >> 0xe;
        int bb3 = 0, bb5 = 1, bb4 = 0, bb6 = 1;
        if (tag_page <= cur_paddr) {
            bb5 = (image1_end_page <= cur_paddr);
            bb3 = (cur_paddr == image1_end_page);
        }
        if (src_base_page <= cur_paddr) {
            bb6 = (src_region_end_page <= cur_paddr);
            bb4 = (cur_paddr == src_region_end_page);
        }
        int in_region = ((!bb6) || bb4) || ((!bb5) || bb3);
        if (use_preview != 0) {
            int pb5 = 0, pb4 = 1;
            if (preview_base_page <= cur_paddr) {
                pb4 = (preview_end_page <= cur_paddr);
                pb5 = (cur_paddr == preview_end_page);
            }
            in_region = ((!pb4) || pb5) || in_region;
        }
        if ((uint64_t)image_end < (uint64_t)((uint8_t *)tag_slot + page_size))
            SPTM_ASSERT_FAIL(0xd49, "sptm_add overflow src_paddr (c)");

        if (in_region) {
            *(int32_t *)(hib_ctx + 0x50) += 1;
            record_cursor = sptm_buf_append(record_cursor, &cur_paddr, 4, &record_bytes);
            record_cursor = sptm_buf_append(record_cursor, &page_size, 4, &record_bytes);
            sptm_hib_disjoint_update(&record_head, tag_slot, page_size, 1);
        } else {
            sptm_hib_disjoint_region(tag_slot, page_size, page_buf, page_buf2, cur_paddr);
            *(int32_t *)(hib_ctx + 0x4c) += 1;
        }
    }

    tag_slot = (uint32_t *)((uint8_t *)tag_slot + ((page_size + 3) & ~3));
    sptm_hib_disjoint_update(page_list, &cur_paddr, 4, 1);
    page_idx++;
    cur_paddr++;
    if (page_idx == entry_pages) goto loop_cont;
    goto page_loop;

replay_loop:
    page_size = 0;
    cur_paddr = 0;
    if (saved_record_bytes < record_bytes + 4)
        sptm_panic_code_msg(0x90b, "serialize > bytes_accessed > size");
    record_cursor = sptm_buf_read(record_cursor, &cur_paddr, 4, &record_bytes);
    if (saved_record_bytes < record_bytes + 4)
        sptm_panic_code_msg(0x90b, "serialize > bytes_accessed > size");
    record_cursor = sptm_buf_read(record_cursor, &page_size, 4, &record_bytes);
    if (0x4000 < page_size)
        sptm_panic_code_msg(0xd7a, "compressed_size < SPTM_PAGE_SIZE");
    sptm_hib_disjoint_update(&record_head, replay_buffer, page_size, 0);
    sptm_hib_disjoint_region(replay_buffer, page_size, page_buf, page_buf2, cur_paddr);
    *(int32_t *)(hib_ctx + 0x4c) += 1;
    page_idx++;
    if (*(uint32_t *)(hib_ctx + 0x50) <= page_idx) goto page_hash;
    goto replay_loop;

page_hash:
    *(void **)(cpu + 0x710) = *(void **)(cpu + 0x708);
    {
        uint64_t page_list_bytes = *(uint64_t *)(cpu + 0x718);
        *(uint64_t *)(cpu + 0x720) = page_list_bytes;
        *(uint64_t *)(cpu + 0x718) = 0;

        uint32_t pag1 = 0x50414731;   /* 'PAG1' */
        sptm_sha_init(sha_ctx, (void *)(cpu + 0x698));
        sptm_sha_update(sha_ctx, (void *)(cpu + 0x698), 4, &pag1);
        if (3 < page_list_bytes) {
            uint64_t idx = 0;
            do {
                cur_paddr = 0;
                sptm_hib_disjoint_update(page_list, &cur_paddr, 4, 0);
                uint64_t *sp = (uint64_t *)(restore_slide + (uint64_t)cur_paddr * 0x4000);
                uint64_t *dp = (uint64_t *)page_buf;
                uint64_t k;
                for (k = 0; k < 0x4000; k += 8) dp[k >> 3] = sp[k >> 3];
                sptm_sha_update(sha_ctx, (void *)(cpu + 0x698), 4, &cur_paddr);
                sptm_sha_update(sha_ctx, (void *)(cpu + 0x698), 0x4000, page_buf);
                idx++;
            } while (idx != page_list_bytes >> 2);
        }
        SPTM_SHA_FINALIZE(sha_ctx, cpu + 0x698, cpu + 0x648);
        sptm_ace_finalize(*(uint64_t *)(cpu + 0x1c8), (void *)(cpu + 0x648), (void *)(cpu + 0x668));
        if (sptm_memcmp((const void *)(cpu + 0x668), (const void *)(hib_ctx + 0x244), 0x30) != 0)
            sptm_panic_code_msg(0xa7c, "memcmp hib_ctx->hmac_buf, hib_header image1Paddr");
    }

    if (encrypted_pages != 0) {
        /* Exclave protected metadata: decrypt the compressed pages with GCM. */
        if (*(uint64_t *)(hib_ctx + 0x548) == 0)
            sptm_panic_code_msg(0xd8e, "hib_header_copy->protected_metadata.exclave_key_phys != 0");
        uint64_t gcm_handle = sptm_crypto_gcm_handle();
        uint64_t gcm_ctx    = sptm_crypto_gcm_ctx(0);
        sptm_crypto_ctx_init(gcm_ctx, (gcm_ctx + 0xf) & ~0xf);
        sptm_bzero((void *)gcm_ctx, 0x40);   /* Ghidra: thunk_FUN_000abb60(ctx) drops the length */
        sptm_crypto_zeroize(sptm_crypto_gcm_ctx(gcm_handle), (void *)gcm_ctx);
        sptm_gcm_init(gcm_handle, gcm_ctx, 0x20, exclave_key, (void *)(hib_ctx + 0x630));

        saved_page_data = page_data_bytes;
        page_data_bytes = 0;
        long *cursor = page_data_cursor;
        int i;
        for (i = 0; i < encrypted_pages; i++) {
            cur_paddr = 0;
            if (saved_page_data < page_data_bytes + 4)
                sptm_panic_code_msg(0x90b, "serialize > bytes_accessed > size");
            cursor = sptm_buf_read(cursor, &cur_paddr, 4, &page_data_bytes);
            uint64_t dst_page_va = restore_slide + (uint64_t)cur_paddr * 0x4000;
            int64_t n_io = *(int64_t *)(cpu + 0x7a8);   /* io-range table count */
            uint32_t *ior = (uint32_t *)(cpu + 0x7b0);
            if (n_io != 0) {
                int handled = 0;
                while (n_io != 0) {
                    if (cur_paddr < ior[0] || (ior[0] + ior[1]) - 1 < cur_paddr) {
                        n_io--;
                        ior += 4;
                        continue;
                    }
                    if ((ior[3] >> 3 & 1) != 0)
                        sptm_panic_code_msg(0xda1, "io range == NULL");
                    if ((ior[3] >> 2 & 1) != 0) {
                        /* double-buffer decrypt (avoid in-place alias). */
                        uint64_t k;
                        uint64_t *sp = (uint64_t *)dst_page_va;
                        uint64_t *dp = (uint64_t *)page_buf;
                        for (k = 0; k < 0x4000; k += 8) dp[k >> 3] = sp[k >> 3];
                        sptm_gcm_stream(gcm_handle, gcm_ctx, 0x4000, page_buf, page_buf);
                        sp = (uint64_t *)page_buf;
                        dp = (uint64_t *)dst_page_va;
                        for (k = 0; k < 0x4000; k += 8) dp[k >> 3] = sp[k >> 3];
                        handled = 1;
                    }
                    break;
                }
                if (!handled)
                    sptm_gcm_stream(gcm_handle, gcm_ctx, 0x4000,
                                    (void *)dst_page_va, (void *)dst_page_va);
            }
            /* NOTE: if n_io == 0 (empty io-range table) no decryption is
             * performed for this page — matches the decompile (LAB_000ec054 is
             * only reached from within the n_io != 0 block). */
        }
        int rc = sptm_gcm_finalize(gcm_handle, gcm_ctx, 0x10, (void *)(hib_ctx + 0x63c));
        if (rc != 0)
            sptm_panic_code_msg(0xdb0, "ccgcm_finalize(gcm, ctx, sizeof(...), ...) == 0");
        sptm_crypto_zeroize(0x20, exclave_key);
    }

    /* ---- re-install restored SPTM runtime state ---- */
    sptm_hib_slide_commit(restore_slide - hibtext_slide,
                          *(uint64_t *)(hib_ctx + 0x19c) - hibtext_slide,
                          restore_slide + *(uint64_t *)(hib_ctx + 0x4d8));   /* FUN_000b7eec */

    /* Restore per-CPU flags / state at slide-relocated globals (DAT_00094000,
     * DAT_0009e000, DAT_000a5000, DAT_000aa018, DAT_000a5028): the exception
     * vector state (DAT_0009e020 = hib_ctx->0x4f0), the panic-record image
     * (DAT_000a5000 from hib_ctx->0x4c0/0x4c8/0x4d0), the alternate record base
     * (DAT_000aa018 = hib_ctx->0x4f8, tagged active), and the primary panic
     * record base (DAT_000a5028 = hib_ctx->0x500). */
    sptm_panic_record_alt = *(uint64_t *)(hib_ctx + 0x4f8);
    *(uint64_t *)((char *)&sptm_panic_record_alt + 8) = 1;
    sptm_panic_record_base = *(uint64_t *)(hib_ctx + 0x500);

    /* Load the SPTM CTRR region and zeroize its derived key. */
    sptm_hib_ctrr_region(cpu, restore_slide + *(uint64_t *)(hib_ctx + 0x520),
                         restore_slide + *(uint64_t *)(hib_ctx + 0x528),
                         (void *)(cpu + 0x728), 0x5350544d /* 'SPTM' */,
                         (void *)(hib_ctx + 0x5a0));
    sptm_crypto_zeroize(0x30, (void *)(cpu + 0x728));

    if (*(uint64_t *)(hib_ctx + 0x530) != 0) {
        sptm_hib_ctrr_region(cpu, restore_slide + *(uint64_t *)(hib_ctx + 0x530),
                             restore_slide + *(uint64_t *)(hib_ctx + 0x538),
                             (void *)(cpu + 0x758), 0x4b45524e /* 'KERN' */,
                             (void *)(hib_ctx + 0x5d0));
    }
    sptm_crypto_zeroize(0x30, (void *)(cpu + 0x758));

    return hib_ctx;
}
/* -------------------------------------------------------------------------
 * sptm_region_2.c — SPTM pmap / guest-adjacent region slice 2.
 * Functions: 000ecd20 (wkdm disjoint-region decompress), 000ed0f0
 * (serialize/disjoint-update), 000ed244 (CTRR-region HMAC), 000ed340
 * (exception register dump + halt), 000ed464 (CTRR hex printer), 000eefd4
 * (FTE acquire), 000ef1f8 (FTE address validate), 000ef468 (FTE next paddr).
 *
 * This fragment contains ONLY new extern declarations (not in the shared
 * preamble) and the function bodies for this slice.  Panic printers come
 * from the preamble (sptm_panic / sptm_panic_code / sptm_panic_fmt /
 * sptm_panic_bad_dt) and are never redefined here.
 * ------------------------------------------------------------------------- */

/* ---- New externs required by this slice (not present in the preamble) ----
 *
 * The batch contract names are used where the region slices agree:
 *   sptm_alloc = FUN_000eaa44, sptm_memcpy = FUN_000abeb0,
 *   sptm_memcmp = FUN_000abcd0, sptm_panic_code_msg = FUN_000e9ecc,
 *   sptm_panic_ctx = FUN_000e9f28, sptm_fatal = FUN_0009c2c8. */

__attribute__((noreturn)) void sptm_panic_code_msg(uint32_t code, const char *msg);   /* FUN_000e9ecc */
__attribute__((noreturn)) void sptm_panic_ctx(const char *file, uint32_t code,
        const char *msg, uint64_t val, uint64_t extra);                              /* FUN_000e9f28 */
__attribute__((noreturn)) void sptm_fatal(uint32_t code);                            /* FUN_0009c2c8 */

/* Allocator (kind=2, flags 0/1 observed): returns a page-list buffer VA. */
extern void *sptm_alloc(uint32_t kind, uint64_t flags);                              /* FUN_000eaa44 */

/* SHA-2 hash object helpers (FUN_000ae8b4 reset / FUN_000aeaa4 update). */
extern void sptm_sha_init(uint64_t ctx, void *out);                                  /* FUN_000ae8b4 */
extern void sptm_sha_update(uint64_t ctx, void *out, uint64_t len, const void *src); /* FUN_000aeaa4 */

/* Crypto finalize producing the protected digest from a SHA digest. */
extern void sptm_crypto_finalize(void *ace_ctx, const uint8_t *digest, uint8_t *out);/* FUN_000bf4bc */

/* Memory primitives. */
extern void sptm_memcpy(void *dst, const void *src, uint64_t n);                     /* FUN_000abeb0 */
extern int  sptm_memcmp(const void *a, const void *b, uint64_t n);                   /* FUN_000abcd0 */

/* Load-exclusive acquire / release barrier guarding the 16-bit shared ref in
 * each FTE descriptor word[0] (the pmap FTE tables). */
extern void LOAcquire(void);
extern void LORelease(void);

/* FTE type-specific nested-lookup helpers (the '(' 0x28 / 0x12 and 0x13
 * leaf/nested types delegate to these; both take (paddr, arg)). */
extern sptm_ret2_t sptm_root_ft(uint64_t root_paddr);  /* FUN_000ef4e0 */
extern sptm_ret2_t sptm_shared_ft(uint64_t va);        /* FUN_000ef8c8 */

/* pmap FTE / DRAM globals (Ghidra DAT_* addresses).  Names follow region_5/6
 * so the orchestrator can reconcile; the exact DAT_ slot is in the comment. */
extern uint64_t sptm_dram_start;        /* DAT_00095d18 — DRAM/FTE window start */
extern uint64_t sptm_dram_end;          /* DAT_00095d20 — DRAM/FTE window end   */
extern uint8_t  sptm_fte_desc[];        /* DAT_00095460 — per-paddr FTE desc tbl */
extern const uint8_t sptm_ftype_valid[];/* DAT_00095d51 — per-type class, stride 0x90, [type*0x90]==1 valid */
extern const uint64_t sptm_class_table[];/* DAT_00019c68 — per-type-class info ptrs, indexed type*8 */

/* CTRR trace output buffer (DAT_00003fe6) and its config-gate word
 * (DAT_0000400d); byte slot selected by per-CPU +0x608. */
extern char sptm_ctrr_buf[];            /* DAT_00003fe6 */
extern char sptm_ctrr_cfg[];            /* DAT_0000400d */

/* ---- Panic format strings (Ghidra string addresses). ---- */
static const char sptm_fmt_gen3[] = "%s(%s:%d) - %s(%#llx), %s(%#llx), %s(%#llx)\n";       /* 0x112f5 */
static const char sptm_fmt_gen1[] = "%s(%s:%d) - %s(%#llx)\n";                             /* 0x11410 */
static const char sptm_fmt_gen2[] = "%s(%s:%d) - %s(%#llx), %s(%#llx)\n";                  /* 0x11690 */
static const char sptm_fmt_gen5[] =
	"%s(%s:%d) - %s(%#llx), %s(%#llx), %s(%#llx), %s(%#llx), %s(%#llx)\n";               /* 0x11254 */
static const char sptm_fmt_bad_type[] =
	"%s: Type (%d) class of FTE (%p) does not match the type class of the "
	"type-specific-data trying to be retrieved: actual (%d) != requested (%d).";         /* 0x12b43 */
static const char sptm_fmt_rw_release[] = "%s: rw_guard_release_shared: %p";             /* 0x115f3 */

/* CTRR hex printer: writes "LABEL=0xVALUE\r\n" into the per-CPU CTRR trace
 * output slot, gated on the per-CPU CTRR enable flag and config mask. */
static void sptm_ctrr_print_hex(uint32_t label, uint64_t value);

/* -------------------------------------------------------------------------
 * FUN_000ed464 @ 0x000ed464   (est. sptm_ctrr_print_hex)
 * Ghidra: void FUN_000ed464(uint param_1, ulong param_2)
 * Low-level CTRR (config trace) hex formatter.  Appends the 4 label bytes
 * (skipping zero bytes), then "=0x", the value in lowercase hex with leading
 * zeros suppressed, then CR/LF into the per-CPU CTRR output buffer
 * (DAT_00003fe6 + per_cpu[0x608] + 0x1e).  Every byte write is gated on the
 * per-CPU CTRR enable (per_cpu+0x600 bit 0) and the config mask
 * (per_cpu+0x61c & word at DAT_0000400d + per_cpu[0x608] + 7).
 * Confidence: high
 * Notes: only caller is 000ed340 (register dump); per-CPU offsets +0x600 /
 *   +0x608 / +0x61c; label constants encode "fp/lr/sp/pc/cpsr/far/esr" and
 *   "xNN" register names. */
static void sptm_ctrr_print_hex(uint32_t label, uint64_t value)
{
	uint64_t cpu = sptm_per_cpu_base();
	uint64_t off;
	uint8_t  ch;
	int      started = 0;
	int      sh;

	if (cpu == 0) {
		return;
	}
	off = *(volatile uint64_t *)(cpu + 0x608);

	/* Guard: CTRR logging enabled (per_cpu+0x600 bit 0) and the per-CPU mask
	 * matches the selected config word. */
	if (((*(volatile uint8_t *)(cpu + 0x600) & 1) == 0) ||
	    ((*(volatile uint32_t *)(cpu + 0x61c) &
	      *(volatile uint32_t *)(uintptr_t)(sptm_ctrr_cfg + off + 7)) == 0)) {
		return;
	}

#define CTRR_PUT(c)  do {                                        \
	*(volatile uint32_t *)(uintptr_t)(sptm_ctrr_buf + off + 0x1e) = (c); \
} while (0)

	/* 4 label bytes, high to low, skipping zero bytes. */
	ch = (uint8_t)(label >> 24); if (ch) CTRR_PUT(ch);
	ch = (uint8_t)(label >> 16); if (ch) CTRR_PUT(ch);
	ch = (uint8_t)(label >> 8);  if (ch) CTRR_PUT(ch);
	ch = (uint8_t)(label >> 0);  if (ch) CTRR_PUT(ch);
	CTRR_PUT('=');
	CTRR_PUT('0');
	CTRR_PUT('x');
	/* Hex value, 16 nibbles, high to low, leading zeros suppressed. */
	for (sh = 60; sh >= 0; sh -= 4) {
		uint32_t nib = (uint32_t)((value >> sh) & 0xf);
		if (nib == 0 && !started && sh != 0) {
			continue;
		}
		started = 1;
		CTRR_PUT(nib < 10 ? '0' + nib : 'a' + (nib - 10));
	}
	CTRR_PUT('\n');
	CTRR_PUT('\r');
#undef CTRR_PUT
}

/* -------------------------------------------------------------------------
 * FUN_000ed340 @ 0x000ed340   (est. sptm_exception_dispatch)
 * Ghidra: void FUN_000ed340(ulong param_1)   [noreturn]
 * Per-CPU exception register-dump + halt terminal.  Takes the 0x330-byte
 * exception frame pointer; prints x0-x28 (labels "x00".."x28"), then
 * fp/lr/sp/pc/cpsr/far/esr from the frame tail offsets (+0xe8..+0x118), and
 * finally spins forever in a WaitForEvent loop (fatal 0xc0ffee).  This is
 * the terminal reached after sptm_vector_context_save (0009c2dc) builds the
 * frame for an unhandled EL2 exception.
 * Confidence: high
 * Notes: frame layout matches sptm_boot.c's sptm_vector_context_save;
 *   register-name labels 0x20206670="  fp" 0x20206c72="  lr" 0x20207370="  sp"
 *   0x20207063="  pc" 0x63707372="cpsr" 0x20666172=" far" 0x20657372=" esr";
 *   final WaitForEvent halt via FUN_0009c2c8. */
__attribute__((noreturn))
void sptm_exception_dispatch(uint64_t *frame, uint64_t exception_index,
                             uint64_t fp, uint64_t elr_el2)
{
	uint32_t i;

	(void)exception_index;
	(void)fp;
	(void)elr_el2;

	for (i = 0; i < 0x1d; i++) {
		uint64_t *r = &frame[i];
		if ((((uint64_t)frame ^ (uint64_t)r) & 0xffc0000000000000) != 0) {
			r = (uint64_t *)(((uint64_t)r & 0xffffffffffff) | 0xc8a2000000000000);
		}
		sptm_ctrr_print_hex((i % 10 | (i / 10) << 8) + 0x20723030, *r);
	}
	sptm_ctrr_print_hex(0x20206670, frame[0xe8 / 8]);          /* fp  */
	sptm_ctrr_print_hex(0x20206c72, frame[0xf0 / 8]);          /* lr  */
	sptm_ctrr_print_hex(0x20207370, frame[0xf8 / 8]);          /* sp  */
	sptm_ctrr_print_hex(0x20207063, frame[0x100 / 8]);         /* pc  */
	sptm_ctrr_print_hex(0x63707372, *(uint32_t *)((uint8_t *)frame + 0x108)); /* cpsr */
	sptm_ctrr_print_hex(0x20666172, frame[0x110 / 8]);         /* far */
	sptm_ctrr_print_hex(0x20657372, frame[0x118 / 8]);         /* esr */

	sptm_fatal(0xc0ffee);
}

/* -------------------------------------------------------------------------
 * FUN_000ed244 @ 0x000ed244   (est. sptm_hib_ctrr_region)
 * Ghidra: void FUN_000ed244(long param_1, ulong param_2, ulong param_3,
 *         undefined8 param_4, undefined4 param_5, undefined6 param_6)
 * Computes and verifies the CTRR HMAC over a hibernation image region.
 * The hib_ctx (per-CPU base) at param_1 carries a SHA object at +0x640 and
 * working buffer at +0x698; a 4-byte tag (param_5, e.g. "SPTM"/"KERN") is
 * absorbed first, then the region [param_2, param_3) in 16 KB pages.  The
 * SHA digest is finalized at +0x648, keyed with param_4 (the CTRR key
 * buffer) via the crypto finalize into +0x668, and compared against the
 * expected HMAC param_6 (0x30 bytes).  On mismatch panics with
 * "memory region HMAC mismatch!".  Called by the hib restore (000eb004).
 * Confidence: high
 * Notes: sha object method-table finalize at +0x38; panic_ctx with code 0x9d8;
 *   key tag param_5 is 0x5350544d "SPTM" or 0x4b45524e "KERN" at call sites. */
void sptm_hib_ctrr_region(uint64_t cpu, uint64_t region_start, uint64_t region_end,
                          const void *key, uint32_t tag, const void *expected_hmac)
{
	uint64_t sha_ctx = *(uint64_t *)(cpu + 0x640);
	uint8_t *sha_buf = (uint8_t *)(cpu + 0x698);
	uint8_t *digest  = (uint8_t *)(cpu + 0x648);
	uint8_t *hmac    = (uint8_t *)(cpu + 0x668);
	uint32_t tag_word = tag;
	uint64_t p;

	sptm_sha_init(sha_ctx, sha_buf);
	sptm_sha_update(sha_ctx, sha_buf, 4, &tag_word);
	for (p = region_start; p < region_end; p += 0x4000) {
		sptm_sha_update(sha_ctx, sha_buf, 0x4000, (const void *)p);
	}
	/* Finalize the SHA digest via the object's method table (+0x38). */
	((void (*)(uint64_t, void *, void *))(*(uint64_t *)(sha_ctx + 0x38)))
	    (sha_ctx, sha_buf, digest);
	/* Key the digest with the CTRR key buffer into the HMAC output. */
	sptm_crypto_finalize((void *)key, digest, hmac);

	if (sptm_memcmp(hmac, expected_hmac, 0x30) != 0) {
		uint8_t zero = 0;
		uint32_t t = tag;
		sptm_panic_ctx("/AppleInternal/Library/BuildRoots/4~CNpkugDokUBw2y1uBkumzghEAPJKWjG1_x4-3Vo/"
		               "Library/Caches/com.apple.xbs/TemporaryDirectory.vAPWY4/Sources/SPTM/sptm/boot/hib/"
		               "hibernate_restore.c",
		               0x9d8, "memory region HMAC mismatch!", (uint64_t)(uintptr_t)hmac,
		               (uint64_t)(uintptr_t)&t);
		(void)zero;
	}
}

/* -------------------------------------------------------------------------
 * FUN_000ed0f0 @ 0x000ed0f0   (est. sptm_hib_disjoint_update)
 * Ghidra: void FUN_000ed0f0(long param_1, undefined8 *param_2, ulong param_3,
 *         uint param_4)
 * Appends (param_4 != 0) or reads back (param_4 == 0) a byte stream from a
 * linked-page serialize buffer.  The serialize object at param_1 has its
 * current page cursor at +8, bytes-accessed counter at +0x10, and total
 * length at +0x18.  Each 0x4000-byte page holds up to 0x3ff8 data bytes; at
 * page end the first 8 bytes carry a PAC-tagged pointer to the next page,
 * allocated on demand via sptm_alloc(2,1) when writing.  Invariants panic
 * (0x903/0x904/0x90b/0x91c/0x92a).  Called by the hib restore (000eb004) to
 * serialize compressed disjoint-region page data.
 * Confidence: high
 * Notes: 0x3ff8-chunked memcpy loop mirrors FUN_000eb004's use; cursor
 *   advancement re-tags the pointer with 0xc8a2. */
void sptm_hib_disjoint_update(void *list, void *buffer, uint64_t size, uint32_t flag)
{
	uint8_t *cursor;
	uint8_t *src = buffer;
	uint64_t remaining = size;

	if (list == NULL || buffer == NULL) {
		sptm_panic_code_msg(0x903, "(serialize != NULL) && (buffer != NULL)");
	}
	if (size == 0) {
		sptm_panic_code_msg(0x904, "size == 0");
	}
	if (((flag & 1) == 0) &&
	    (*(uint64_t *)((uint8_t *)list + 0x18) < *(uint64_t *)((uint8_t *)list + 0x10) + size)) {
		sptm_panic_code_msg(0x90b, "(serialize->bytes_accessed + size) <= serialize->total_length");
	}

	cursor = *(uint8_t **)((uint8_t *)list + 8);
	while (remaining != 0) {
		uint64_t off = (uint64_t)cursor & 0x3fff;
		if (off > 0x3ff8) {
			sptm_panic_code_msg(0x91c, "cur_page_pos <= max_page_size");
		}
		uint8_t *chunk = cursor;
		if (off == 0x3ff8) {
			if (flag == 0) {
				chunk = *(uint8_t **)cursor;
			} else {
				chunk = sptm_alloc(2, 1);
				*(uint8_t **)cursor = chunk;
			}
			if (chunk == NULL) {
				sptm_panic_code_msg(0x92a, "*next_page_ptr != NULL");
			}
			*(uint8_t **)((uint8_t *)list + 8) = chunk;
			off = 0;
		}
		uint64_t n = (remaining <= (0x3ff8 - off)) ? remaining : (0x3ff8 - off);
		if (flag != 0) {
			sptm_memcpy(chunk, src, n);
		} else {
			sptm_memcpy(src, chunk, n);
		}
		*(uint64_t *)((uint8_t *)list + 0x10) += n;
		cursor = chunk + n;
		if ((((uint64_t)chunk ^ (uint64_t)cursor) & 0xffc0000000000000) != 0) {
			cursor = (uint8_t *)(((uint64_t)cursor & 0xffffffffffff) | 0xc8a2000000000000);
		}
		*(uint8_t **)((uint8_t *)list + 8) = cursor;
		src += n;
		remaining -= n;
	}
}

/* -------------------------------------------------------------------------
 * FUN_000ecd20 @ 0x000ecd20   (est. sptm_hib_disjoint_region)
 * Ghidra: void FUN_000ecd20(int *param_1, int param_2, undefined8 *param_3,
 *         int *param_4, uint param_5)   [WARNING: bad-instruction truncation]
 * Restores one disjoint hibernation region page.  param_1 = compressed src,
 * param_2 = compressed size, param_3 = destination, param_4 = wkdm scratch,
 * param_5 = destination page index (dst_paddr = param_5 << 14).  Validates
 * the destination is not immutable and lies in a permissible hib/io range
 * against the per-CPU state, then for size 4 fills a page with a pattern, for
 * size 0x4000 memcpy's a full page, and for any other size runs the wkdm
 * decompressor (scratch copy + alignment checks; the expansion loop itself is
 * a bad-instruction region Ghidra could not follow and is truncated here).
 * Confidence: low (wkdm expansion loop truncated by decompiler)
 * Notes: decompiler "Bad instruction - Truncating control flow here" at the
 *   general wkdm path; fallback = disassemble_function + get_function_pcode
 *   for the expansion loop.  Per-CPU offsets +0x80/0x88/0x90/0x98 (immutable
 *   ranges), +0x58 (hibtext_stack_paddr), +0x7a8/+0x7b0 (io ranges),
 *   +0x48/+0x50 (dst range), +0x10/0x18/0x20 (slides). */
void sptm_hib_disjoint_region(void *src, uint64_t size, void *dst, void *scratch,
                              uint32_t dst_paddr_page)
{
	uint64_t cpu = sptm_per_cpu_base();
	uint64_t dst_paddr;
	uint64_t dst_va;
	uint32_t *io;
	int64_t   num_io;
	int       io_found;

	if (src == NULL || scratch == NULL) {
		sptm_panic_code_msg(0xb6b, "(src != NULL) && (wkdm_scratch != NULL)");
	}
	if (size == 0) {
		sptm_panic_code_msg(0xb6c, "compressed_size > 0");
	}

	if (cpu != 0) {
		dst_paddr = (uint64_t)dst_paddr_page * 0x4000;
		/* Immutable range check: [cpu+0x80,cpu+0x88) with exception
		 * [cpu+0x90,cpu+0x98). */
		if ((*(volatile uint64_t *)(cpu + 0x80) <= dst_paddr) &&
		    (dst_paddr < *(volatile uint64_t *)(cpu + 0x88)) &&
		    ((dst_paddr < *(volatile uint64_t *)(cpu + 0x90)) ||
		     (*(volatile uint64_t *)(cpu + 0x98) <= dst_paddr))) {
			sptm_panic_code_msg(0xb75, "!is_immutable(dst_paddr)");
		}
		if (dst_paddr == *(volatile uint64_t *)(cpu + 0x58)) {
			sptm_panic_code_msg(0xb79, "dst_paddr != hib_ctx->hibtext_stack_paddr");
		}
		/* Find the dst page index among the registered io ranges. */
		num_io = *(volatile int64_t *)(cpu + 0x7a8);
		io = (uint32_t *)(cpu + 0x7b0);
		if (num_io != 0) {
			do {
				if ((*io <= dst_paddr_page) &&
				    (dst_paddr_page <= (*io + io[1]) - 1)) {
					if (((io[3] >> 3) & 1) != 0) {
						sptm_panic_code_msg(0xb7f,
						    "io_range == NULL || !(io_range->flags & HIB_PHYS_RANGE_FLAG_PROHIBITED)");
					}
					io_found = 0;
					goto range_checked;
				}
				io += 4;
				num_io--;
			} while (num_io != 0);
		}
		io = NULL;
		io_found = 1;
range_checked:
		/* dst must be in the DRAM range [cpu+0x48,cpu+0x50) or a NEEDS_HIB
		 * io range. */
		if (((dst_paddr < *(volatile uint64_t *)(cpu + 0x48)) ||
		     (*(volatile uint64_t *)(cpu + 0x50) <= dst_paddr)) &&
		    (io_found || ((io[3] & 1) == 0))) {
			sptm_panic_code_msg(0xb8b,
			    "io_range != NULL && (io_range->flags & HIB_PHYS_RANGE_FLAG_NEEDS_HIB)");
		}
		/* Slides must be established. */
		if (*(volatile uint64_t *)(cpu + 0x10) == 0) {
			sptm_panic_code_msg(0x1ce, "hib_ctx->restore_slide != 0");
		}
		if (*(volatile uint64_t *)(cpu + 0x18) == 0) {
			sptm_panic_code_msg(0x1cf, "hib_ctx->hibtext_slide != 0");
		}
		if (*(volatile uint64_t *)(cpu + 0x20) == 0) {
			sptm_panic_code_msg(0x1d0, "hib_ctx->hibtext_fixup_slide != 0");
		}
		dst_va = *(volatile uint64_t *)(cpu + 0x10) + dst_paddr;

		{
			uint8_t *w = (uint8_t *)dst_va;
			uint8_t *x = NULL;
			if (!io_found && (io[3] & 4) != 0) {
				w = dst;
				x = (uint8_t *)dst_va;
			}

			if (size == 4) {
				/* Fill a full page with the 4-byte pattern. */
				uint32_t pat = *(uint32_t *)src;
				if (pat == 0) {
					uint64_t i;
					for (i = 0; i < 0x4000; i++) {
						((uint8_t *)w)[i] = 0;
					}
				} else {
					uint32_t i;
					for (i = 0; i < 0x4000 / 4; i++) {
						((uint32_t *)w)[i] = pat;
					}
				}
			} else if (size != 0x4000) {
				/* General wkdm decompress: scratch copy + alignment
				 * checks; the expansion loop is a bad-instruction
				 * region (see header notes) — truncated here. */
				uintptr_t s;
				if (w == NULL) {
					sptm_panic_code_msg(0xb0c, "(src != NULL) && (dst != NULL) && (scratch != NULL)");
				}
				if (((uintptr_t)src & 0x3f) != 0) {
					sptm_memcpy(scratch, src, size);
					src = scratch;
				}
				s = (uintptr_t)src;
				if ((s & 0x3f) != 0) {
					sptm_panic_code_msg(0xb1b, "(((uintptr_t)wkdm_src) & 63) == 0");
				}
				if (((uintptr_t)w & 0x3fff) != 0) {
					sptm_panic_code_msg(0xb1c, "(((uintptr_t)dst) & SPTM_PAGE_MASK) == 0");
				}
				/* wkdm decompress(w, src) — expansion loop not
				 * recovered (decompiler bad-instruction truncation). */
				__builtin_trap();
			} else {
				sptm_memcpy(w, src, 0x4000);
			}

			/* If the destination also maps to the restore VA, copy the
			 * restored page there as well. */
			if (x != NULL) {
				uint64_t i;
				for (i = 0; i < 0x4000; i++) {
					x[i] = w[i];
				}
			}
		}
		return;
	}

	sptm_fatal(0xcafebee5);
}

/* -------------------------------------------------------------------------
 * FUN_000eefd4 @ 0x000eefd4   (est. sptm_fte_acquire)
 * Ghidra: ushort * FUN_000eefd4(ulong param_1, undefined8 param_2)
 * Acquires / validates the pmap frame-table-entry (FTE) descriptor for a
 * physical address.  Checks the paddr is within the DRAM/FTE window
 * [sptm_dram_start, sptm_dram_end), indexes the per-paddr FTE descriptor
 * table (sptm_fte_desc + ((paddr - start) >> 10 & ~0xf)), takes the
 * load-exclusive guard, and increments the 16-bit shared reference by 2
 * (overflow > 0xffe9 or odd → panic).  Then dispatches on the FTE type byte:
 * '(' (0x28) and 0x12 delegate to sptm_root_ft; 0x13 delegates to
 * sptm_shared_ft; any other type requires 16 KB alignment and a valid class
 * (else returns the held FTE).  On the delegated paths the reference is
 * decremented by 2 and released before returning the nested FTE; an invalid
 * final refcount panics "rw_guard_release_shared".
 * Confidence: high
 * Notes: FTE layout word[0]=u16 ref, byte[2]=type; LOAcquire/LORelease guard
 *   the 16-bit ref; class table sptm_ftype_valid[type*0x90]==1. */
uint16_t *sptm_fte_acquire(uint64_t paddr, uint64_t arg)
{
	uint16_t *fte;
	uint16_t  ref;
	uint8_t   type;
	uint16_t *result;

	if (paddr < sptm_dram_start || sptm_dram_end <= paddr) {
		sptm_panic_code(0, arg, sptm_fmt_gen3);
	}

	fte = (uint16_t *)(sptm_fte_desc + ((paddr - sptm_dram_start) >> 10 & ~0xfUL));
	if ((((uint64_t)(uintptr_t)sptm_fte_desc ^ (uint64_t)(uintptr_t)fte) &
	     0xffc0000000000000) != 0) {
		fte = (uint16_t *)(((uint64_t)(uintptr_t)fte & 0xffffffffffff) | 0xc8a2000000000000);
	}

	LOAcquire();
	ref = *fte;
	*fte = ref + 2;
	if (ref > 0xffe9 || (ref & 1) != 0) {
		sptm_panic_code(0x3d, arg, sptm_fmt_gen3);
	}

	type = *(uint8_t *)((uint8_t *)fte + 2);
	if (type != 0x28) {
		if (type == 0x13) {
			result = (uint16_t *)sptm_shared_ft(paddr).lo;
			goto release;
		}
		if (type != 0x12) {
			if ((paddr & 0x3fff) != 0) {
				sptm_panic_code(0, arg, sptm_fmt_gen1);
			}
			if (sptm_ftype_valid[type * 0x90] == 1) {
				return fte;
			}
			sptm_panic_code(0, arg, sptm_fmt_gen2);
		}
	}
	result = (uint16_t *)sptm_root_ft(paddr).lo;

release:
	ref = *fte;
	*fte = ref - 2;
	LORelease();
	if (ref != 0 && (ref & 1) == 0) {
		return result;
	}
	sptm_panic(sptm_fmt_rw_release, (void *)fte);
}

/* -------------------------------------------------------------------------
 * FUN_000ef468 @ 0x000ef468   (est. sptm_fte_next_paddr)
 * Ghidra: long FUN_000ef468(long param_1)
 * Returns the next free physical address in an FTE's type class: if the FTE
 * type class is valid (sptm_ftype_valid[type*0x90]==1, type at byte +2) it
 * returns sptm_class_table[fte[0xc]]->limit (+0x60) + 1; otherwise panics
 * "Type (%d) class of FTE".  Called by 000ef1f8 to advance past a validated
 * region.
 * Confidence: high
 * Notes: class descriptor limit at +0x60; type-class index byte at +0xc. */
uint64_t sptm_fte_next_paddr(uint8_t *fte)
{
	uint8_t type = *(fte + 2);
	uint8_t cls  = *(fte + 0xc);

	if (sptm_ftype_valid[type * 0x90] == 1) {
		const uint64_t *class_info = (const uint64_t *)(uintptr_t)sptm_class_table[cls];
		return class_info[0xc] + 1;   /* +0x60 */
	}
	sptm_panic(sptm_fmt_bad_type, (void *)fte);
}

/* -------------------------------------------------------------------------
 * FUN_000ef1f8 @ 0x000ef1f8   (est. sptm_fte_validate)
 * Ghidra: void FUN_000ef1f8(ulong param_1, long param_2, uint param_3)
 * Validates that a physical address belongs to an FTE type-class region.
 * param_1 = paddr, param_2 = FTE descriptor, param_3 = index/flavor.  Checks
 * the FTE's type class is valid, derives the class info from
 * sptm_class_table[fte[0xc]], and verifies the paddr is aligned to the class
 * granule (cls[0x48]) and falls within the class's page bitmap (mask at
 * descriptor offset +0x18, shift at +0x10, granule count = 0x4000/granule).
 * Then enforces the class paddr limit (cls[0x60]): for type 8 it must be
 * above the wrapped limit, for other types below it; out-of-range addresses
 * advance via sptm_fte_next_paddr and panic.  Called by sptm_map_page (ee278)
 * and other pmap paths.
 * Confidence: high
 * Notes: per-kind descriptors indexed *cls + param_3*0x38; panics use
 *   sptm_panic_code with code 7 and the generic gen3/gen5 formats. */
void sptm_fte_validate(uint64_t paddr, uint8_t *fte, uint32_t index)
{
	const uint64_t *class_info;
	uint64_t granule, limit, mask, shift, lv;
	int      count;

	if (sptm_ftype_valid[*(fte + 2) * 0x90] != 1) {
		sptm_panic(sptm_fmt_bad_type, (void *)fte);
	}
	class_info = (const uint64_t *)(uintptr_t)sptm_class_table[*(fte + 0xc)];
	granule = class_info[9];            /* +0x48 */
	if ((granule - 1) & paddr) {
		sptm_panic_code(7, (uint64_t)(uintptr_t)fte, sptm_fmt_gen3);
	}

	if (index == 3) {
		limit = class_info[0xc];        /* +0x60 */
	} else {
		count = 0;
		if (granule != 0) {
			count = (int)(0x4000 / granule);
		}
		limit = class_info[0xc];
		lv = (uint64_t)(uintptr_t)(class_info[0]) + (uint64_t)index * 0x38;
		mask  = *(const uint64_t *)(uintptr_t)(lv + 0x18);
		shift = *(const uint64_t *)(uintptr_t)(lv + 0x10) & 0x3f;
		if ((count - 1U) & (uint32_t)((limit & paddr & mask) >> shift)) {
			sptm_panic_code(7, (uint64_t)(uintptr_t)fte, sptm_fmt_gen3);
		}
	}

	if (*(fte + 2) == 8) {
		if ((uint64_t)(0 - limit - 2) < paddr) {
			return;
		}
		sptm_fte_next_paddr(fte);
	} else {
		if (paddr < limit + 1) {
			return;
		}
		sptm_fte_next_paddr(fte);
	}
	sptm_panic_code(7, (uint64_t)(uintptr_t)fte, sptm_fmt_gen5);
}
/* ============================================================================
 * Region slice 3 — SPTM pmap root/shared/SURT FTE validators + region parser.
 * Function bodies only (plus new externs NOT in the shared preamble).
 *
 * These are the "root table FTE getters" the pmap core (sptm_pmap.c) declares
 * extern: sptm_root_ft (FUN_000ef4e0), sptm_shared_ft (FUN_000ef8c8),
 * sptm_root_attr (FUN_000f0584), sptm_surt_ft (FUN_000f175c),
 * sptm_parse_region (FUN_000f2304), plus the two thin leaf-table
 * condemn/uncondemn wrappers (FUN_000f0d44 / FUN_000f1284) that tail-branch
 * into sptm_leaf_table_condemn_op (FUN_000f0d50).
 *
 * English-first reconstruction; Ghidra names/addresses only in comments.
 * ========================================================================== */

/* Frame-type constants and shared types now come from the preamble. */

/* Per-frame-type parameter table stride (0x90) and class offset (+0x01). */
#define SPTM_TYPE_PARAM_STRIDE        0x90
#define SPTM_TYPE_CLASS_OFF           0x01

/* -------------------------------------------------------------------------
 * Globals used by these validators (Ghidra DAT_ bases in comments).
 * ------------------------------------------------------------------------- */
extern sptm_frame_table_entry_t *g_frame_table;   /* DAT_00095460 phys frame table */
extern uint64_t g_sptm_first_phys;                /* DAT_00095d18 */
extern uint64_t g_sptm_last_phys;                 /* DAT_00095d20 */
extern uint64_t g_physmap_base;                   /* DAT_00095110 */
extern uint32_t g_feature_flags;                  /* DAT_001012d8 bit8=physmap_ranges */
extern uint64_t g_n_physmap_ranges;               /* DAT_00101ac8 */
extern uint64_t g_physmap_ranges[];               /* DAT_00101ad0 {paddr,vaddr,uint count}* */
extern uint64_t g_cpu_pt_attr[];                  /* DAT_00019c68 per-cpu pt-attr table */
extern uint8_t  g_type_params[];                  /* DAT_00095d50 type-params, stride 0x90 */

/* FTE rw-guard (read) lock primitives. */
extern void LOAcquire(void);
extern void LORelease(void);

/* Physical -> virtual (physmap) helper: FUN_000e40ec {va, err}. */
extern sptm_ret2_t sptm_phys_to_virt(uint64_t paddr);

/* Root-geometry helper: validates the root FTE class and returns max_va+1
 * (FUN_000ef468). Used by sptm_parse_region on the out-of-range path. */
extern uint64_t sptm_root_max_va(sptm_frame_table_entry_t *root);

/* The condemn/un-condemn core these two wrappers tail-branch into
 * (FUN_000f0d50, defined in sptm_pmap.c). */
extern sptm_return_t sptm_leaf_table_condemn_op(sptm_paddr_t root_pt_paddr,
		sptm_vaddr_t vaddr, bool condemn);

/* Convenience: byte at FTE offset +4 is puVar[2]; +6 is puVar[3]; etc. */
#define FTE_B4(ft)      ((uint8_t)((ft)->f.word4))
#define FTE_B6(ft)      ((uint8_t)((ft)->f.word4 >> 16))
#define FTE_B12(ft)     ((uint8_t)((ft)->f.attr_idx))

/* Frame-table entry for a physical address (direct index). */
static inline sptm_frame_table_entry_t *
sptm_ft_index(uint64_t paddr)
{
	return (sptm_frame_table_entry_t *)((uint8_t *)g_frame_table +
		(((paddr - g_sptm_first_phys) >> 10) & ~0xfULL));
}

/* Physical -> virtual (physmap): if physmap ranges are enabled scan
 * DAT_00101ad0, else linear physmap, else sptm_phys_to_virt. */
static uint64_t
sptm_paddr_to_vaddr(uint64_t paddr)
{
	uint64_t n;
	const uint64_t *r;

	if (((g_feature_flags >> 8) & 1) == 0) {
		return (paddr - g_sptm_first_phys) + g_physmap_base;
	}
	n = g_n_physmap_ranges;
	r = g_physmap_ranges;
	while (n--) {
		uint64_t rp = r[0];
		if (rp <= paddr && paddr < rp + (uint64_t)(uint32_t)r[2] * 0x4000) {
			return (paddr - rp) + r[1];
		}
		r += 3;
	}
	return sptm_phys_to_virt(paddr).lo;
}

/* Type-class lookup: g_type_params[type].type_class (class at +0x01). */
static inline uint8_t
sptm_type_class(uint8_t type)
{
	return g_type_params[(uint64_t)type * SPTM_TYPE_PARAM_STRIDE +
	                      SPTM_TYPE_CLASS_OFF];
}

/* ============================================================================
 * sptm_root_ft — FUN_000ef4e0 (est. sptm_root_ft)
 *
 * Ghidra: void FUN_000ef4e0(ulong root_paddr, undefined8 err)
 *
 * Validates and read-locks the FTE of a root page-table physical address and
 * returns the frame-table entry pointer.  Handles XNU_SUBPAGE_USER_ROOT_TABLES
 * frames (physmap-translated) and XNU_USER_ROOT_TABLE frames; panics on any
 * misalignment, out-of-range, type-class, or refcount violation.
 * Confidence: high (full decompile + FTE struct from sptm_pmap.c)
 */
sptm_ret2_t
sptm_root_ft(uint64_t root_paddr)
{
	sptm_frame_table_entry_t *ft;
	uint16_t rc;
	uint8_t type;
	uint64_t root_va;
	sptm_ret2_t pv;

	if (root_paddr < g_sptm_first_phys || g_sptm_last_phys <= root_paddr) {
		sptm_panic_code(0xd, root_paddr, "%s(%s:%d) - %s(%#llx), %s(%#llx), %s(%#llx)\n");
	}
	ft = sptm_ft_index(root_paddr);
	/* PAC/memory-tag recovery on the frame-table pointer. */
	if ((((uint64_t)g_frame_table ^ (uint64_t)ft) & 0xffc0000000000000ULL) != 0) {
		ft = (sptm_frame_table_entry_t *)((uint64_t)ft | 0xc8a2000000000000ULL);
	}
	LOAcquire();
	rc = ft->f.refcnt;
	ft->f.refcnt = rc + 2;
	if (0xffe9 < rc || (rc & 1) != 0) {
		sptm_panic_code(0x3d, root_paddr, "%s(%s:%d) - %s(%#llx), %s(%#llx), %s(%#llx)\n");
	}
	type = ft->f.type;
	if (type == XNU_SUBPAGE_USER_ROOT_TABLES) {
		if ((root_paddr & 0x7f) != 0) {
			sptm_panic_code(0xd, root_paddr, "%s(%s:%d) - %s(%#llx)\n");
		}
		root_va = sptm_paddr_to_vaddr(root_paddr);
		/* The SURT frame FTE lives at va+0x40; lock and validate it. */
		sptm_frame_table_entry_t *sft =
			(sptm_frame_table_entry_t *)(root_va + 0x40);
		LOAcquire();
		rc = sft->f.refcnt;
		sft->f.refcnt = rc + 2;
		if (0xffe9 < rc || (rc & 1) != 0) {
			sptm_panic_code(0x3d, root_paddr, "%s(%s:%d) - %s(%#llx), %s(%#llx), %s(%#llx)\n");
		}
		if ((*(uint8_t *)(root_va + 0x50) & 1) == 0) {
			sptm_panic_code(0x6a, root_paddr, "%s(%s:%d) - %s(%#llx), %s(%#llx)\n");
		}
		type = *(uint8_t *)(root_va + 0x42);
	} else if (type == XNU_USER_ROOT_TABLE) {
		if ((root_paddr & 0x3fff) != 0) {
			sptm_panic_code(0xd, root_paddr, "%s(%s:%d) - %s(%#llx)\n");
		}
		type = XNU_USER_ROOT_TABLE;
	} else {
		sptm_panic_code(0xd, root_paddr, "%s(%s:%d) - %s(%#llx), %s(%#llx)\n");
	}
	if (sptm_type_class(type) == 1) {
		if (((ft->f.parent_flags >> 2) & 1) != 0) {
			if (sptm_type_class(ft->f.type) != 1) {
				sptm_panic("%s: Type (%d) class of FTE (%p) does not match the type class "
				           "of the type-specific-data trying to be retrieved: actual (%d) != requested (%d).",
				           "sptm_root_ft", ft->f.type, (void *)ft,
				           sptm_type_class(ft->f.type), 1);
			}
			if (((ft->f.parent_flags >> 5) & 1) != 0) {
				sptm_panic_code(0x10, root_paddr, "%s(%s:%d) - %s(%#llx), %s(%#llx)\n");
			}
		}
		return (sptm_ret2_t){ (uint64_t)ft, 0 };
	}
	sptm_panic("%s: Type (%d) class of FTE (%p) does not match the type class "
	           "of the type-specific-data trying to be retrieved: actual (%d) != requested (%d).",
	           "sptm_root_ft", type, (void *)ft, sptm_type_class(type), 1);
}

/* ============================================================================
 * sptm_shared_ft — FUN_000ef8c8 (est. sptm_shared_ft)
 *
 * Ghidra: void FUN_000ef8c8(ulong va, undefined8 err)
 *
 * Validates and read-locks the FTE of a shared-root-table VA (0x4000-aligned,
 * type XNU_SHARED_ROOT_TABLE) and returns the frame-table entry pointer.
 * Panics on misalignment, range, type, or refcount violations.
 * Confidence: high (full decompile)
 */
sptm_ret2_t
sptm_shared_ft(uint64_t va)
{
	sptm_frame_table_entry_t *ft;
	uint16_t rc;

	if ((va & 0x3fff) != 0) {
		sptm_panic_code(0xc, va, "%s(%s:%d) - %s(%#llx)\n");
	}
	if (g_sptm_first_phys <= va && va < g_sptm_last_phys) {
		ft = sptm_ft_index(va);
		if ((((uint64_t)g_frame_table ^ (uint64_t)ft) & 0xffc0000000000000ULL) != 0) {
			ft = (sptm_frame_table_entry_t *)((uint64_t)ft | 0xc8a2000000000000ULL);
		}
		LOAcquire();
		rc = ft->f.refcnt;
		ft->f.refcnt = rc + 2;
		if (rc < 0xffea && (rc & 1) == 0) {
			if (ft->f.type == XNU_SHARED_ROOT_TABLE) {
				return (sptm_ret2_t){ (uint64_t)ft, 0 };
			}
			sptm_panic_code(0xc, va, "%s(%s:%d) - %s(%#llx), %s(%#llx)\n");
		}
		sptm_panic_code(0x3d, va, "%s(%s:%d) - %s(%#llx), %s(%#llx), %s(%#llx)\n");
	}
	sptm_panic_code(0xc, va, "%s(%s:%d) - %s(%#llx), %s(%#llx), %s(%#llx)\n");
}

/* ============================================================================
 * sptm_root_attr — FUN_000f0584 (est. sptm_root_attr)
 *
 * Ghidra: long FUN_000f0584(long root)
 *
 * Returns a pointer just past the root FTE (root + 4) where the page-table
 * attribute/geometry data lives, after asserting the root's type class is 1.
 * Confidence: high (full decompile)
 */
sptm_ret2_t
sptm_root_attr(sptm_frame_table_entry_t *root)
{
	if (sptm_type_class(root->f.type) == 1) {
		return (sptm_ret2_t){ (uint64_t)root + 4, 0 };
	}
	sptm_panic("%s: Type (%d) class of FTE (%p) does not match the type class "
	           "of the type-specific-data trying to be retrieved: actual (%d) != requested (%d).",
	           "sptm_root_attr", root->f.type, (void *)root,
	           sptm_type_class(root->f.type), 1);
}

/* ============================================================================
 * sptm_surt_ft — FUN_000f175c (est. sptm_surt_ft)
 *
 * Ghidra: ushort * FUN_000f175c(ulong surt_frame, undefined8 err)
 *
 * Validates and read-locks the FTE of a XNU_SUBPAGE_USER_ROOT_TABLES (SURT)
 * frame physical address (0x4000-aligned) and returns the frame-table entry
 * pointer.  Panics on misalignment, range, type, or refcount violations.
 * Confidence: high (full decompile + header name sptm_surt_alloc)
 */
sptm_ret2_t
sptm_surt_ft(uint64_t surt_frame)
{
	sptm_frame_table_entry_t *ft;
	uint16_t rc;

	if ((surt_frame & 0x3fff) != 0) {
		sptm_panic_code(0x67, surt_frame, "%s(%s:%d) - %s(%#llx)\n");
	}
	if (g_sptm_first_phys <= surt_frame && surt_frame < g_sptm_last_phys) {
		ft = sptm_ft_index(surt_frame);
		if ((((uint64_t)g_frame_table ^ (uint64_t)ft) & 0xffc0000000000000ULL) != 0) {
			ft = (sptm_frame_table_entry_t *)((uint64_t)ft | 0xc8a2000000000000ULL);
		}
		LOAcquire();
		rc = ft->f.refcnt;
		ft->f.refcnt = rc + 2;
		if (rc < 0xffea && (rc & 1) == 0) {
			if (ft->f.type == XNU_SUBPAGE_USER_ROOT_TABLES) {
				return (sptm_ret2_t){ (uint64_t)ft, 0 };
			}
			sptm_panic_code(0x67, surt_frame, "%s(%s:%d) - %s(%#llx), %s(%#llx)\n");
		}
		sptm_panic_code(0x3d, surt_frame, "%s(%s:%d) - %s(%#llx), %s(%#llx), %s(%#llx)\n");
	}
	sptm_panic_code(0x67, surt_frame, "%s(%s:%d) - %s(%#llx), %s(%#llx), %s(%#llx)\n");
}

/* ============================================================================
 * sptm_parse_region — FUN_000f2304 (est. sptm_parse_region)
 *
 * Ghidra: void FUN_000f2304(ulong va, uint count, ulong max, long root,
 *                           ulong *count_out)
 *
 * Validates that a [va, va+count) mapping region is legal against the root
 * table's page-table geometry: the VA must be page-aligned, the byte count
 * must not overflow and must sit within the root's VA range, and the root's
 * type class must be 1.  On success writes count to *count_out and returns
 * {va, 0}.  Panics (noreturn) on any violation.
 * Confidence: high (full decompile + sptm_pmap.c callers)
 */
sptm_ret2_t
sptm_parse_region(uint64_t va, uint32_t count, uint64_t max,
		sptm_frame_table_entry_t *root, uint64_t *count_out)
{
	uint64_t n = (uint64_t)count;
	uint64_t page_size, total, max_va;
	__uint128_t prod;
	const char *fmt;

	if (count == 0 || max < n) {
		sptm_panic_code(0xa, count, "%s(%s:%d) - %s(%#llx), %s(%#llx)\n");
	}
	if (sptm_type_class(root->f.type) != 1) {
		sptm_panic("%s: Type (%d) class of FTE (%p) does not match the type class "
		           "of the type-specific-data trying to be retrieved: actual (%d) != requested (%d).",
		           "sptm_parse_region", root->f.type, (void *)root,
		           sptm_type_class(root->f.type), 1);
	}
	page_size = *(uint64_t *)(g_cpu_pt_attr[FTE_B12(root)] + 0x48);
	if ((page_size - 1) & va) {
		sptm_panic_code(8, count, "%s(%s:%d) - %s(%#llx), %s(%#llx)\n");
	}
	/* 128-bit product check: count * page_size must not overflow 64 bits. */
	prod = (__uint128_t)n * page_size;
	if ((uint64_t)(prod >> 64) == 0) {
		total = n * page_size - page_size;          /* (count-1) * page_size */
		if (va + total < va) {                       /* carry out of va+total */
			fmt = "%s(%s:%d) - %s(%#llx), %s(%#llx), %s(%#llx), %s(%#llx)\n";
		} else {
			max_va = *(uint64_t *)(g_cpu_pt_attr[FTE_B12(root)] + 0x60);
			if (root->f.type == SPTM_KERNEL_ROOT_TABLE) {
				if ((uint64_t)(-max_va - 2) < va) {
					*count_out = n;
					return (sptm_ret2_t){ va, 0 };
				}
				(void)sptm_root_max_va(root);
			} else {
				if (va + total < max_va + 1) {
					*count_out = n;
					return (sptm_ret2_t){ va, 0 };
				}
				(void)sptm_root_max_va(root);
			}
			fmt = "%s(%s:%d) - %s(%#llx), %s(%#llx), %s(%#llx), %s(%#llx), %s(%#llx), %s(%#llx)\n";
		}
	} else {
		fmt = "%s(%s:%d) - %s(%#llx), %s(%#llx), %s(%#llx)\n";
	}
	sptm_panic_code(8, count, fmt);
}

/* ============================================================================
 * sptm_condemn_leaf_table — FUN_000f0d44 (est. sptm_condemn_leaf_table)
 *
 * Ghidra: void FUN_000f0d44(undefined8 root_pt_paddr, undefined8 vaddr)
 *
 * 12-byte wrapper: loads condemn=1 into w2 and tail-branches into
 * FUN_000f0d50 (sptm_leaf_table_condemn_op).  Condemns a leaf page table
 * under a user/stage-2 root.  Confidence: high (SDK header name).
 */
sptm_return_t
sptm_condemn_leaf_table(uint64_t root_pt_paddr, uint64_t vaddr)
{
	return sptm_leaf_table_condemn_op(root_pt_paddr, vaddr, true);
}

/* ============================================================================
 * sptm_uncondemn_leaf_table — FUN_000f1284 (est. sptm_uncondemn_leaf_table)
 *
 * Ghidra: void FUN_000f1284(undefined8 root_pt_paddr, undefined8 vaddr)
 *
 * 12-byte wrapper: loads condemn=0 into w2 and tail-branches into
 * FUN_000f0d50 (sptm_leaf_table_condemn_op).  Un-condemns a leaf page table.
 * Confidence: high (SDK header name).
 */
sptm_return_t
sptm_uncondemn_leaf_table(uint64_t root_pt_paddr, uint64_t vaddr)
{
	return sptm_leaf_table_condemn_op(root_pt_paddr, vaddr, false);
}
/* =========================================================================
 * Region 4 (slice 4): SPTM pmap PTE enter/remove/update helpers.
 * Functions: 000f25fc 000f2878 000f29f0 000f2eec 000f2f54 000f2fb4
 * =========================================================================
 * New externs required by these bodies (NOT already in the shared preamble).
 * Canonical SPTM helpers:
 */
#include <stdbool.h>
extern void LOAcquire(void);              /* opaque rw-guard acquire  */
extern void LORelease(void);              /* opaque rw-guard release (release barrier) */
extern uint64_t sptm_cacheattr(uint64_t ft);            /* FUN_000e0a10 — acquire cache-attr/tag for an FTE */
extern void sptm_write_pte(void *leaf, void *data, uint64_t old_pte, uint64_t new_pte); /* FUN_000e2e2c — update refcounts for old->new pte */

/* FTE class / permission / refcount tables (Ghidra DAT_ addresses). */
extern uint8_t sptm_fte_class[];          /* DAT_00095d51 — per-type class, stride 0x90 */
extern uint8_t sptm_fte_mapper[];         /* DAT_00095d81 — per-type map/unmap perms, stride 0x90 */
extern uint8_t sptm_fte_shared2[];        /* DAT_00095d84 — per-type shared/owned flag, stride 0x90 */
extern uint8_t sptm_fte_ref[];            /* DAT_00095d54 — per-type refcount-flag word, stride 0x90 (16-bit reads) */

/* PTE permission-transition tables (Ghidra DAT_000134f8 / 13578 / 13478),
 * uint32 arrays indexed by the combined permission code. */
extern uint32_t sptm_pte_trans_allow[];   /* DAT_000134f8 — transitions allowed outright */
extern uint32_t sptm_pte_trans_cond[];    /* DAT_00013578 — transitions allowed with flag bit 11 set */
extern uint32_t sptm_pte_trans_merge[];   /* DAT_00013478 — transitions that force the merge path */

/* -------------------------------------------------------------------------
 * FUN_000f25fc @ 0x000f25fc   (est. sptm_pte_enter)
 * Ghidra: uint FUN_000f25fc(undefined8 *param_1, ulong param_2, ulong param_3,
 *                           uint param_4, ulong *param_5)
 * Validates that the mapping's data-frame FTE has been acquired (shared),
 * then computes the new leaf PTE for a PTE entry.  On the leaf path (low
 * PTE bits == 3) it sets the context type byte to 3, ORs in the access-flag
 * bit, rejects a dangling tag-storage reference, and (for a 0x10 entry type)
 * acquires the cache-attribute tag into the context tag slot.  On the
 * non-leaf path it propagates the VA's valid bits and may promote the type
 * to 3 when the access-flag bit is set.  Returns the "present/keep" flag.
 * Confidence: high
 * Notes: panics sptm_panic_code (FUN_000f8844) 0x1d/0x1e/0xe and
 *   sptm_panic (FUN_000f8804); helper FUN_000e0a10 = sptm_cacheattr; FTE
 *   class table DAT_00095d51, map-perm table DAT_00095d81. */
uint32_t sptm_pte_enter(uint64_t *ctx, uint64_t va, uint64_t pte,
                        uint32_t flags, uint64_t *out)
{
	uint32_t vlo = (uint32_t)va;
	uint16_t *fte = (uint16_t *)ctx[0];
	uint8_t type;
	uint8_t shared;
	uint64_t u;
	uint32_t ret;
	uint64_t mask;

	/* The leaf-table FTE type must not be condemned (0x17). */
	if (*(char *)(ctx[1] + 2) == 0x17) {
		sptm_panic_code(0x1d, vlo, "%s(%s:%d) - %s(%llx) - %s(%llx)");
	}

	if (fte != NULL) {
		type = *(uint8_t *)((uintptr_t)fte + 2);
		/* A non-shared frame must already have been acquired. */
		if ((sptm_fte_class[(uintptr_t)type * 0x90] != 6) && (*fte == 0)) {
			sptm_panic("%s: Frame expected to have been acquired has not been acquired %p %u %d");
		}
		/* Shared/owned tracking: derive the shared flag from the map-perm
		 * table and the FTE byte-3 state. */
		if (((sptm_fte_mapper[(uintptr_t)type * 0x90] >> 2) & 1) == 0) {
			shared = (uint8_t)(*(uint8_t *)((uintptr_t)fte + 3) >> 1) & 1;
		} else {
			shared = 1;
		}
		if ((sptm_fte_mapper[(uintptr_t)type * 0x90] & 1) != 0 && shared != 0) {
			sptm_panic_code(0x1e, vlo, "%s(%s:%d) - %s(%llx) - %s(%llx)");
		}
	}

	if ((flags >> 8 & 1) != 0) {
		sptm_panic_code(0xe, vlo, "%s(%s:%d) - %s(%llx) - %s(%llx)");
	}

	*out = pte & 0xc000000000000000ULL;
	if ((~vlo & 3) == 0) {
		/* Leaf PTE: promote type, set access-flag bit, acquire the tag. */
		*(uint8_t *)(ctx + 5) = 3;
		*out = (pte & 0xc000000000000000ULL) | 0x80;
		if (ctx[2] != 0) {
			sptm_panic("%s: Dangling tag storage reference from previous mapping attempt");
		}
		if ((vlo & 0x1c) == 0x10) {
			ctx[2] = sptm_cacheattr((uint64_t)fte);
		}
		ret = 1;
	} else {
		/* Non-leaf: keep the VA valid/table bits; maybe promote to leaf. */
		*(uint8_t *)(ctx + 5) = 0;
		u = va >> 0x3e;
		ret = (u != 0) & flags;
		if ((u != 0) || ((flags & 1) == 0)) {
			mask = 0x80;
			if (ret == 0) {
				mask = 0xc000000000000000ULL;
			}
			*out = va & mask;
		}
		if ((vlo >> 7 & 1) != 0) {
			*(uint8_t *)(ctx + 5) = 3;
		}
	}
	return ret;
}

/* -------------------------------------------------------------------------
 * FUN_000f2878 @ 0x000f2878   (est. sptm_pte_remove)
 * Ghidra: void FUN_000f2878(undefined8 *param_1, long param_2, ulong param_3)
 * Removes an existing PTE: clears the PTEP (via a CAS that keeps only the
 * VA valid/table bits), updates the leaf/data FTE refcounts through
 * sptm_write_pte, then drops the rw-guard reference held on the tag-storage
 * FTE (class must be 4) and its refcount, panicking on underflow or a bad
 * shared release.
 * Confidence: high
 * Notes: panics sptm_panic (FUN_000f8804); helper FUN_000e2e2c =
 *   sptm_write_pte (new_pte = param_3 & 0xc000000000000000); tag release uses
 *   the rw-guard word (+0) decrement-by-2 + LORelease and the sub-refcount
 *   (+4) decrement-by-1; class table DAT_00095d51. */
void sptm_pte_remove(uint64_t *ctx, uint64_t prev_pte, uint64_t new_pte)
{
	uint64_t *ptep = (uint64_t *)ctx[3];
	uint16_t *tag;
	uint8_t type;
	uint32_t rc;
	uint16_t u;

	if (ptep == NULL) {
		sptm_panic("%s: PTEP is somehow NULL");
	}
	if (prev_pte == 0) {
		sptm_panic("%s: prev_pte is somehow empty");
	}
	if (ctx[1] == 0) {
		sptm_panic("%s: Leaf page table FTE is somehow NULL even though prev_pte is valid");
	}

	/* Clear the PTE if it still holds the value we expect. */
	if (*ptep == new_pte) {
		*ptep = new_pte & 0xc000000000000000ULL;
	}
	sptm_write_pte((void *)ctx[1], (void *)ctx[0], prev_pte,
	    new_pte & 0xc000000000000000ULL);

	/* Drop the rw-guard reference on the tag-storage FTE. */
	tag = (uint16_t *)ctx[2];
	if (tag != NULL) {
		type = *(uint8_t *)((uintptr_t)tag + 2);
		if (sptm_fte_class[(uintptr_t)type * 0x90] != 4) {
			sptm_panic("%s: Type %d class of FTE %p %d");
		}
		rc = *(uint32_t *)((uintptr_t)tag + 4);
		*(uint32_t *)((uintptr_t)tag + 4) = rc - 1;
		if (rc == 0) {
			sptm_panic("%s: refcnt underflow: rc %p old_value %lld value %lld");
		}
		u = *tag;
		*tag = (uint16_t)(u - 2);
		LORelease();
		if (u == 0 || (u & 1) != 0) {
			sptm_panic("%s: rw_guard_release_shared: %p");
		}
	}
}

/* -------------------------------------------------------------------------
 * FUN_000f2f54 @ 0x000f2f54   (est. sptm_fte_ptep)
 * Ghidra: long FUN_000f2f54(long param_1)
 * Returns a pointer to the page-table-entry field within an FTE of class 3
 * (leaf/CPU frame): the PTE value lives 4 bytes into the FTE.  Any other
 * class is fatal.
 * Confidence: high
 * Notes: panics sptm_panic (FUN_000f8804); class table DAT_00095d51. */
long sptm_fte_ptep(long fte)
{
	uint8_t type = *(uint8_t *)((uintptr_t)fte + 2);
	if (sptm_fte_class[(uintptr_t)type * 0x90] == 3) {
		return fte + 4;
	}
	sptm_panic("%s: Type %d class of FTE %p %d");
}

/* -------------------------------------------------------------------------
 * FUN_000f2eec @ 0x000f2eec   (est. sptm_pte_perm_check)
 * Ghidra: bool FUN_000f2eec(ulong param_1, ulong param_2)
 * Permission/attribute compatibility check used by sptm_pte_update: returns
 * true when the old and new PTEs carry incompatible "nested/guard" attribute
 * indices (neither equal and the new one is not the unrestricted 3), or when
 * the nested-permission bits (0x60000000000000) differ in a disallowed way.
 * Caller panics (code 0x20) if this returns true.
 * Confidence: high
 * Notes: pure bit-mask logic; no helper calls.  Called from FUN_000f29f0 as
 *   (new_pte, old_pte). */
bool sptm_pte_perm_check(uint64_t new_pte, uint64_t old_pte)
{
	uint64_t a = (old_pte >> 6 & 3) | (old_pte >> 0x3a & 2);
	uint64_t b = (new_pte >> 6 & 3) | (new_pte >> 0x3a & 2);

	if (a != 0 && b != 3 && b != a) {
		return true;
	}
	return (old_pte & 0x60000000000000ULL) != 0x40000000000000ULL &&
	    (((old_pte ^ new_pte) & 0x60000000000000ULL) != 0 &&
	     (new_pte & 0x60000000000000ULL) != 0);
}

/* -------------------------------------------------------------------------
 * FUN_000f29f0 @ 0x000f29f0   (est. sptm_pte_update)
 * Ghidra: bool FUN_000f29f0(long *param_1, ulong param_2, ulong param_3,
 *                           uint param_4, ulong *param_5)
 * Merges the new PTE (param_3) into the existing one (param_2) under the
 * flag bits (param_4), enforcing the frame-type permission-transition rules
 * against the three transition tables, and returns whether the resulting PTE
 * differs.  The final PTE is written to *out; a byte at ctx+0x28 records the
 * "changed" flag.  Handles address relocation (bit 0), per-attribute masks
 * (bits 3/4/5/2), permission-code transitions (bit 1) and, on a shared FTE,
 * the shared/accessed-flag side effect via sptm_fte_ptep.
 * Confidence: high
 * Notes: panics sptm_panic_code (FUN_000f8844) 0x1c/0x25/0x24/0x20; helper
 *   FUN_000f2eec = sptm_pte_perm_check, FUN_000f2f54 = sptm_fte_ptep; FTE
 *   class DAT_00095d51, ref table DAT_00095d54 (16-bit), shared2 table
 *   DAT_00095d84; transition tables DAT_000134f8/13578/13478. */
bool sptm_pte_update(uint64_t *ctx, uint64_t old_pte, uint64_t new_pte,
                     uint32_t flags, uint64_t *out)
{
	uint32_t olo = (uint32_t)old_pte;
	uint8_t leaf_type = *(uint8_t *)(ctx[1] + 2);
	uint64_t fte = ctx[0];
	uint64_t merged = old_pte;
	uint32_t operm, nperm, nattr, oattr, code, bit, idx;
	uint32_t t1, t2;
	uint64_t mask;
	int r;
	uint8_t *pb;

	*out = old_pte;
	if ((~olo & 3) != 0) {
		return false;
	}

	/* Bit 0: relocate — take the frame/attribute bit 0x3a from the new PTE. */
	if ((flags & 1) != 0) {
		merged = (old_pte & 0xf800000000000000ULL) |
		    (old_pte & 0x3ffffffffffffffULL) |
		    ((new_pte >> 0x3a & 1) << 0x3a);
		*out = merged;
	}

	/* Bit 3: clear bit 0xb unless the source has it or the flag forces it. */
	if ((flags >> 3 & 1) != 0) {
		merged &= 0xfffffffffffffbffULL;
		*out = merged;
		if (((olo >> 10 & 1) != 0) || ((flags >> 0xb & 1) != 0)) {
			merged |= new_pte & 0x400;
			*out = merged;
		}
	}

	/* Bit 4: carry the two attribute-index bits (8..9) from the new PTE. */
	if ((flags >> 4 & 1) != 0) {
		merged = (merged & 0xfffffffffffffc00ULL) | (merged & 0xff) |
		    ((new_pte >> 8 & 3) << 8);
		*out = merged;
	}

	/* Bit 5: merge the entry-type field (bits 2..4), widened for 0x22. */
	if ((flags >> 5 & 1) != 0) {
		if (((old_pte & 0x1c) == 0x10) || ((new_pte & 0x1c) == 0x10)) {
			sptm_panic_code(0x1c, old_pte, "%s(%s:%d) - %s(%llx) - %s(%llx)");
		}
		mask = merged & 0xffffffffffffffc0ULL;
		{
			uint64_t lo = merged & 3;
			merged = (merged & 0xffffffffffffffe3ULL) | (new_pte & 0x1c);
			if (leaf_type == 0x22) {
				merged = mask | lo | ((new_pte >> 2 & 0xf) << 2);
			}
		}
		*out = merged;
	}

	/* Bit 2: force the access bit (0x800) on (0x22 not allowed). */
	if ((flags >> 2 & 1) != 0) {
		if ((((uint32_t)new_pte >> 0xb & 1) == 0) || (leaf_type == 0x22)) {
			sptm_panic_code(0x25, old_pte, "%s(%s:%d) - %s(%llx) - %s(%llx)");
		}
		merged |= 0x800;
		*out = merged;
	}

	/* Bit 1: permission-code transition enforcement. */
	if ((flags >> 1 & 1) != 0) {
		oattr = (uint32_t)(old_pte >> 4) & 0xc;
		operm = oattr | ((uint32_t)(old_pte >> 0x35) & 3);
		nattr = (uint32_t)(new_pte >> 4) & 0xc;
		nperm = nattr | ((uint32_t)(new_pte >> 0x35) & 3);

		if (leaf_type == 0x22) {
			nperm = ((uint32_t)(new_pte >> 6) & 3) | ((uint32_t)(new_pte >> 0x3a) & 2);
			if (((nperm != 0 && ((operm = ((uint32_t)(old_pte >> 6) & 3) |
			    ((uint32_t)(old_pte >> 0x3a) & 2)) != 3) && operm != nperm)) ||
			    (((new_pte & 0x60000000000000ULL) != 0x40000000000000ULL &&
			      (old_pte & 0x60000000000000ULL) != 0) &&
			     ((new_pte ^ old_pte) & 0x60000000000000ULL) != 0)) {
				r = sptm_pte_perm_check(new_pte, old_pte);
				if (r != 0) {
					sptm_panic_code(0x20, old_pte, "%s(%s:%d) - %s(%llx) - %s(%llx)");
				}
				goto done;
			}
		} else {
			uint8_t ftype = *(uint8_t *)((uintptr_t)fte + 2);
			if ((operm != nperm) &&
			    (((*(uint16_t *)&sptm_fte_ref[(uintptr_t)ftype * 0x90] >> nperm) & 1) == 0)) {
				sptm_panic_code(0x24, old_pte, "%s(%s:%d) - %s(%llx) - %s(%llx)");
			}
			code = ((uint32_t)(old_pte >> 0x37) & 0x10) | operm;
			idx = ((uint32_t)(new_pte >> 0x37) & 0x10);
			if ((code == (idx | nperm)) ||
			    (bit = 1U << (idx | nperm),
			     (sptm_pte_trans_allow[code] & bit) != 0)) {
				goto done;
			}
			if ((sptm_pte_trans_cond[code] & bit) == 0) {
				if ((sptm_pte_trans_merge[code] & bit) == 0) {
					sptm_panic_code(0x20, old_pte, "%s(%s:%d) - %s(%llx) - %s(%llx)");
				}
			} else if ((flags >> 0xb & 1) == 0) {
				goto done;
			}
		}

		/* Merge the guarded attributes/permissions into the PTE. */
		merged = (new_pte & 0x860000000000080ULL) |
		    ((nattr >> 2 & 1) << 6) | (merged & 0xf79fffffffffff3fULL);
		*out = merged;

		/* Shared/owned FTE: propagate the shared/accessed flag. */
		{
			uint8_t ftype = *(uint8_t *)((uintptr_t)fte + 2);
			if ((sptm_fte_shared2[(uintptr_t)ftype * 0x90] & 1) != 0) {
				if (leaf_type == 0x22) {
					if ((olo >> 7 & 1) == 0) {
						goto done;
					}
					new_pte = new_pte & 0x80;
				} else {
					if ((1ULL << (oattr | ((uint32_t)(old_pte >> 0x35) & 3)) & 0x2a8U) == 0) {
						goto done;
					}
					new_pte = 1ULL << (nattr | ((uint32_t)(new_pte >> 0x35) & 3)) & 0x2a8;
				}
				if (((flags >> 8 & 1) != 0) && (new_pte == 0)) {
					pb = (uint8_t *)sptm_fte_ptep((long)fte);
					*pb = *pb | 1;
					merged = *out;
				}
			}
		}
	}

done:
	*(uint8_t *)(ctx + 5) = ((merged ^ old_pte) & 0xf3ffffffffffffffULL) != 0;
	*out = merged;
	return old_pte != merged;
}

/* -------------------------------------------------------------------------
 * FUN_000f2fb4 @ 0x000f2fb4   (est. sptm_pte_remove_final)
 * Ghidra: void FUN_000f2fb4(undefined8 *param_1, long param_2, undefined8 param_3,
 *                           uint param_4)
 * Final-pass PTE removal: when flag bit 1 is set, updates the leaf/data FTE
 * refcounts for the old->new PTE transition via sptm_write_pte.  Both the
 * previous PTE and the leaf-table FTE must be present.
 * Confidence: high
 * Notes: panics sptm_panic (FUN_000f8804); helper FUN_000e2e2c =
 *   sptm_write_pte (tail call, 4 args). */
void sptm_pte_remove_final(uint64_t *ctx, uint64_t prev_pte, uint64_t new_pte,
                           uint32_t flags)
{
	if ((flags >> 1 & 1) == 0) {
		return;
	}
	if (prev_pte != 0) {
		if (ctx[1] != 0) {
			sptm_write_pte((void *)ctx[1], (void *)ctx[0], prev_pte, new_pte);
			return;
		}
		sptm_panic("%s: Leaf page table FTE is somehow NULL");
	}
	sptm_panic("%s: prev_pte is somehow empty in the final pass");
}
/* -------------------------------------------------------------------------
 * sptm_region_5.c — SPTM pmap / guest-adjacent region: per-CPU root-FT
 * guard/refcount helpers, region range validation (sptm_parse_region2), and
 * the EL1 TLB maintenance traps (0xf4d60 - 0xf7108).
 *
 * This fragment contains ONLY new extern declarations (not in the shared
 * preamble) and the function bodies for this slice.  All panic printers come
 * from the preamble (sptm_panic / sptm_panic_code / sptm_panic_fmt /
 * sptm_panic_bad_dt) and are never redefined here.
 * ------------------------------------------------------------------------- */

/* ---- New externs required by this slice (not present in the preamble) ----
 *
 * These are the shared SPTM pmap-region helpers this slice calls into.  The
 * "obj/ctx" pair return is how the decompiler models the 16-byte struct
 * (low 8 = object pointer / value, high 8 = error-context token). */

/* (obj/ctx pair folded into sptm_ret2_t {lo,hi}) */

extern sptm_ret2_t sptm_root_ft(uint64_t root_paddr);     /* FUN_000ef4e0 */
extern sptm_ret2_t sptm_parse_region(uint64_t va, uint32_t count,
        uint64_t max, sptm_frame_table_entry_t *root, uint64_t *count_out);  /* FUN_000f2304 */
extern uint64_t sptm_papt_to_phys(uint64_t addr);         /* FUN_000d8a58 */
extern void *sptm_ft_dynamic(uint64_t addr);              /* FUN_000e3d7c */
extern void sptm_tlb_op(uint64_t va, uint64_t size,
        uint64_t span, uint32_t flavor);                  /* FUN_000d76fc */

/* PMAP configuration / per-CPU region globals (Ghidra DAT_* addresses). */
extern const uint64_t sptm_class_table[];       /* DAT_00019c68 — per-type-class info ptrs */
extern const uint8_t  sptm_type_valid_table[];  /* DAT_00095d51 — 0x90-byte entries, [0]==1 valid */
extern uint64_t sptm_per_cpu_obj_base;          /* DAT_00095460 — per-CPU object region base */
extern uint64_t sptm_per_cpu_va_start;          /* DAT_00095d18 — per-CPU VA range start */
extern uint64_t sptm_per_cpu_va_end;            /* DAT_00095d20 — per-CPU VA range end */
extern uint16_t sptm_fallback_obj[];            /* DAT_00101f90 — fallback per-CPU object */

/* Per-type-class descriptor (each sptm_class_table[] entry points to one) and
 * the root-table metadata it references.  Offsets match the decompile:
 * class: meta=+0, vtcr=+0x40, root_page_mask=+0x48, shift=+0x50, limit=+0x60;
 * meta: span_mask=+0x50, shift=+0x80, block_mask=+0x88. */
struct sptm_root_meta {
	uint64_t pad0[10];           /* +0x00 .. +0x48 */
	uint64_t span_mask;          /* +0x50 */
	uint64_t pad1[5];            /* +0x58 .. +0x78 */
	uint64_t shift;              /* +0x80 */
	uint64_t block_mask;         /* +0x88 */
};
struct sptm_ft_class {
	struct sptm_root_meta *meta; /* +0x00 */
	uint64_t pad[7];             /* +0x08 .. +0x38 */
	uint64_t vtcr;               /* +0x40 */
	uint64_t root_page_mask;     /* +0x48 */
	uint64_t shift;              /* +0x50 */
	uint64_t size;               /* +0x58 */
	uint64_t limit;              /* +0x60 */
};

/* ---- Panic format strings (Ghidra string addresses).  These are the panic
 * wrappers used with sptm_panic / sptm_panic_code.  The shared code-prefix
 * appears at 0x111dc / 0x112f5 / 0x11410 / 0x11690 / 0x11254 / 0x11452. */
static const char sptm_panic_fmt_gen[] = "%s(%s:%d) - %s(%s:%llx)";
static const char sptm_fmt_bad_type_f[]  = "%s: Type (%d) class_of_FTE: %p %d";   /* 0x12b43 */
static const char sptm_fmt_rw_release_f[] = "%s: rw_guard_release_shared: %p";    /* 0x115f3 */
static const char sptm_fmt_refcnt_ovf[] =
	"%s: refcnt overflow: rc %p old_value %lld value %lld";                     /* 0x1220a */
static const char sptm_fmt_refcnt_udf[] =
	"%s: refcnt underflow: rc %p old_value %lld value %lld";                    /* 0x124da */

/* ---- Local intrinsics for this slice ---- */

/* LOAcquire/LORelease: the load-exclusive acquire/release barrier guarding the
 * 16-bit shared reference in each per-CPU object word[0]. */
static inline void sptm_lse_acquire(void)
{
	__asm__ volatile("dmb ish" ::: "memory");
}
static inline void sptm_lse_release(void)
{
	__asm__ volatile("dmb ish" ::: "memory");
}

static inline uint64_t sptm_read_daif(void)
{
	uint64_t v;
	__asm__ volatile("mrs %0, daif" : "=r"(v));
	return v;
}
static inline void sptm_write_daif(uint64_t v)
{
	__asm__ volatile("msr daif, %0" :: "r"(v) : "memory");
}

/* Custom SPTM sysreg (3,4,0xf,0,4): bit 1 gates the EL1 TLB maintenance path. */
static inline uint64_t sptm_read_s3_4_c15_c0_4(void)
{
	uint64_t v;
	__asm__ volatile("mrs %0, s3_4_c15_c0_4" : "=r"(v));
	return v;
}
static inline void sptm_write_s3_4_c15_c0_4(uint64_t v)
{
	__asm__ volatile("msr s3_4_c15_c0_4, %0" :: "r"(v) : "memory");
}

/* Resolve a physical address to its per-CPU object, applying the physical
 * address high-bit canonicalization (0xc8a2...) used throughout SPTM. */
static inline uint16_t *sptm_percpu_obj(uint64_t phys)
{
	uint16_t *obj;
	if (phys < sptm_per_cpu_va_start || sptm_per_cpu_va_end <= phys) {
		void *alt = sptm_ft_dynamic(phys);
		obj = (uint16_t *)sptm_fallback_obj;
		if (alt != 0)
			obj = (uint16_t *)alt;
	} else {
		obj = (uint16_t *)(sptm_per_cpu_obj_base +
			(((phys - sptm_per_cpu_va_start) >> 10) & 0xffffffff0ULL));
		if ((sptm_per_cpu_obj_base ^ (uint64_t)obj) & 0xffc0000000000000ULL)
			obj = (uint16_t *)(((uint64_t)obj & 0xffffffffffffULL) |
						0xc8a2000000000000ULL);
	}
	return obj;
}

/* Release the shared rw-guard reference on the owning CPU's copy of the
 * object (used when the current root's bit-7 "shared" flag is set). */
static inline void sptm_release_percpu_shared(uint64_t phys)
{
	uint16_t *obj = sptm_percpu_obj(phys);
	uint16_t old = obj[0];
	obj[0] = (uint16_t)(old - 2);
	sptm_lse_release();
	if (old == 0 || (old & 1) != 0)
		sptm_panic(sptm_fmt_rw_release_f);
}

/* -------------------------------------------------------------------------
 * FUN_000f4d60 @ 0x000f4d60   (est. sptm_parse_region2)
 * Ghidra: void FUN_000f4d60(undefined8 param_1, undefined8 param_2,
 *        undefined4 param_3, long param_4, long *param_5)
 * Variant of sptm_parse_region (FUN_000f2304) that additionally bounds the
 * resulting region against the root table's VA span and block-alignment.
 * Validates that [start, start+span) fits inside the root's span_mask and is
 * block-aligned; returns the region size (low half of the parse result) on
 * success, panicking with code 0x27 / 7 otherwise.  Called by sptm_nest_region
 * (FUN_000f458c) and sptm_unnest_region (FUN_000f4eec), which use the return
 * as the region VA for the page-table walk.
 * Confidence: medium
 * Notes: decompiler drops the tail args of the inner FUN_000f2304 call (root
 *   object + out pointer are threaded through); param_5[0] is written by
 *   sptm_parse_region to the region size. */
uint64_t sptm_parse_region2(uint64_t va, uint64_t size, uint32_t span,
		uint16_t *root_obj, uint64_t *out)
{
	sptm_ret2_t pr = sptm_parse_region(va, (uint32_t)size, (uint64_t)span,
						(sptm_frame_table_entry_t *)root_obj, out);
	uint64_t region_size = pr.lo;
	uint64_t ctx = pr.hi;
	struct sptm_ft_class *cls;
	struct sptm_root_meta *meta;
	uint64_t root_page_mask;
	uint64_t end_va;
	uint64_t blockmask;
	int root_pages;
	uint32_t lo, hi;

	if (sptm_type_valid_table[(uint8_t)root_obj[1] * 0x90] != 1)
		sptm_panic(sptm_fmt_bad_type_f);

	cls = (struct sptm_ft_class *)sptm_class_table[(uint8_t)root_obj[6]];
	root_page_mask = cls->root_page_mask;
	end_va = out[0] * root_page_mask + region_size;
	meta = cls->meta;

	if (((end_va - root_page_mask) ^ region_size) & meta->span_mask) {
		/* region extends beyond the root's VA span */
		sptm_panic_code(0x27, ctx, sptm_panic_fmt_gen);
	}

	root_pages = (root_page_mask != 0) ? (int)(0x4000 / root_page_mask) : 0;
	blockmask = meta->block_mask & cls->limit;
	lo = (uint32_t)((blockmask & region_size) >> (meta->shift & 0x3f));
	hi = (uint32_t)((blockmask & end_va) >> (meta->shift & 0x3f));
	if (((uint32_t)(root_pages - 1) & (lo | hi)) != 0)
		sptm_panic_code(7, ctx, sptm_panic_fmt_gen);

	return region_size;
}

/* -------------------------------------------------------------------------
 * FUN_000f55f4 @ 0x000f55f4   (est. sptm_region_flags_update)
 * Ghidra: void FUN_000f55f4(undefined8 param_1, ushort param_2, ushort param_3)
 * Update the modifiable flag word (offset 10) of the current per-CPU root
 * object: sets param_2's bits and clears param_3's bits.  Rejects writes to
 * the reserved flag bits (0xfea4 mask, panic code 0x10).  On release, if the
 * object is flagged shared (bit 7) the mirrored reference on the owning CPU's
 * copy is released.
 * Confidence: medium
 * Notes: no callers found (trap/entry point); the `while (puVar4[5] !=
 *   puVar4[5])` in the decompile is a volatile self-read barrier — rendered
 *   as a single type check. */
void sptm_region_flags_update(uint64_t va, uint16_t set_bits, uint16_t clear_bits)
{
	sptm_ret2_t rc = sptm_root_ft(va);
	uint16_t *obj = (uint16_t *)rc.lo;
	uint16_t old;

	if ((set_bits & 0xfea4) != 0 || (clear_bits & 0xfea4) != 0)
		sptm_panic_code(0x10, rc.hi, sptm_panic_fmt_gen);

	/* decompile: do { type check } while (obj[5] != obj[5]) — the self-read
	 * loop runs exactly once; keep the single type validation. */
	if (sptm_type_valid_table[(uint8_t)obj[1] * 0x90] != 1)
		sptm_panic(sptm_fmt_bad_type_f);

	obj[5] = (uint16_t)((obj[5] & ~clear_bits) | (clear_bits & set_bits));

	old = obj[0];
	obj[0] = (uint16_t)(old - 2);
	sptm_lse_release();
	if (old == 0 || (old & 1) != 0)
		sptm_panic(sptm_fmt_rw_release_f);

	if (sptm_type_valid_table[(uint8_t)obj[1] * 0x90] != 1)
		sptm_panic(sptm_fmt_bad_type_f);

	if ((obj[5] >> 7) & 1)
		sptm_release_percpu_shared(sptm_papt_to_phys((uint64_t)(uintptr_t)obj));
}

/* -------------------------------------------------------------------------
 * FUN_000f61c0 @ 0x000f61c0   (est. sptm_root_acquire_shared)
 * Ghidra: void FUN_000f61c0(ulong param_1, undefined8 param_2)
 * Acquire a shared rw-guard reference (word[0] += 2) on the per-CPU object at
 * the given 16KB-aligned VA, requiring the object to be a root-table type
 * (0x21, '!').  Returns the object pointer.  Overflows (> 0xffe9) or an
 * already-locked (odd) guard panic with code 0x3d.  Called by the root-switch
 * and TLB helpers (FUN_000f5f2c / FUN_000f6368 / FUN_000f6634 /
 * FUN_000f6aec) as `sptm_root_acquire_shared()`.
 * Confidence: medium
 * Notes: decompiler shows `void` but callers capture the returned object;
 *   the decompiled `return` leaves the object pointer in x0. */
uint16_t *sptm_root_acquire_shared(uint64_t va, uint64_t ctx)
{
	uint16_t *obj;
	uint16_t old;

	if ((va & 0x3fff) != 0)
		sptm_panic_code(0, ctx, sptm_panic_fmt_gen);

	if (va < sptm_per_cpu_va_start || sptm_per_cpu_va_end <= va) {
		/* out of the per-CPU VA range */
		sptm_panic_code(0, ctx, sptm_panic_fmt_gen);
	}

	obj = (uint16_t *)(sptm_per_cpu_obj_base +
		(((va - sptm_per_cpu_va_start) >> 10) & 0xffffffff0ULL));
	if ((sptm_per_cpu_obj_base ^ (uint64_t)obj) & 0xffc0000000000000ULL)
		obj = (uint16_t *)(((uint64_t)obj & 0xffffffffffffULL) |
					0xc8a2000000000000ULL);

	sptm_lse_acquire();
	old = obj[0];
	obj[0] = (uint16_t)(old + 2);
	if (old > 0xffe9 || (old & 1) != 0)
		sptm_panic_code(0x3d, ctx, sptm_panic_fmt_gen);

	if ((uint8_t)obj[1] != 0x21)   /* '!' — root-table type */
		sptm_panic_code(0, ctx, sptm_panic_fmt_gen);

	return obj;
}

/* -------------------------------------------------------------------------
 * FUN_000f6aec @ 0x000f6aec   (est. sptm_region_tlb_flush)
 * Ghidra: void FUN_000f6aec(undefined8 param_1, undefined8 param_2,
 *        undefined8 param_3, int param_4)
 * Acquire the current per-CPU root, parse the region [va, va+size) against the
 * root's limit, bump the object's sub-refcount (word[3]) and issue a TLB
 * invalidation for the region's VA range via sptm_tlb_op.  param_4 selects
 * the TLB flavor (0 = plain VA, nonzero = VAALE1IS-class flush).  Unwinds the
 * refcount and shared guard on exit.
 * Confidence: medium
 * Notes: no callers found (trap/entry point); the first argument to
 *   FUN_000f61c0 (root locator VA = param_1) is dropped by the decompiler. */
void sptm_region_tlb_flush(uint64_t root_va, uint64_t va, uint64_t size, int tlb_mode)
{
	uint16_t *obj = sptm_root_acquire_shared(root_va, 0);
	uint16_t *rc = &obj[3];
	uint16_t old;
	uint16_t rco;
	uint64_t out_pages = 0;
	uint32_t flavor;
	struct sptm_ft_class *cls;
	uint64_t span;
	sptm_ret2_t pr;
	uint64_t region_size;
	uint8_t t;

	if (sptm_type_valid_table[(uint8_t)obj[1] * 0x90] != 1)
		sptm_panic(sptm_fmt_bad_type_f);

	cls = (struct sptm_ft_class *)sptm_class_table[(uint8_t)obj[6]];
	span = (cls->limit + 1) >> (cls->shift & 0x3f);
	pr = sptm_parse_region(va, (uint32_t)size, span, (sptm_frame_table_entry_t *)obj, &out_pages);
	region_size = pr.lo;

	rco = *rc;
	*rc = (uint16_t)(rco + 1);
	if (rco > 0x812)
		sptm_panic(sptm_fmt_refcnt_ovf);

	flavor = (tlb_mode != 0) ? 5U : 0U;
	sptm_tlb_op((((uint64_t)(uintptr_t)obj - sptm_per_cpu_obj_base) * 0x400ULL
				& 0x3fffffffc000ULL) + sptm_per_cpu_va_start,
			region_size, out_pages, flavor);

	rco = *rc;
	*rc = (uint16_t)(rco - 1);
	if (rco == 0)
		sptm_panic(sptm_fmt_refcnt_udf);

	old = obj[0];
	obj[0] = (uint16_t)(old - 2);
	sptm_lse_release();
	t = (uint8_t)obj[1];
	if (t == 0x13 || t != 0x12) {
		if (((old & 1) == 0) && old != 0)
			return;
	} else if (((old & 1) == 0) && old != 0) {
		if (sptm_type_valid_table[t * 0x90] == 1) {
			if ((obj[5] >> 7) & 1)
				sptm_release_percpu_shared(
					sptm_papt_to_phys((uint64_t)(uintptr_t)obj));
			return;
		}
		sptm_panic(sptm_fmt_bad_type_f);
	}
	sptm_panic(sptm_fmt_rw_release_f);
}

/* -------------------------------------------------------------------------
 * FUN_000f6d54 @ 0x000f6d54   (est. sptm_tlb_maintenance)
 * Ghidra: undefined8 FUN_000f6d54(undefined8 param_1, uint param_2)
 * EL1 TLB-maintenance trap: with interrupts masked (DAIF.AIF), toggle bit 1 of
 * the SPTM sysreg s3_4_c15_c0_4 around an ISB to gate a TLB invalidation.
 * param_2 may only have bit 1 (0x2) set (mask 0xfffffffd); any other bits
 * panic with code 0x31.  Returns param_1 on success.
 * Confidence: low
 * Notes: no callers found; the specific sysreg bit's meaning (TLB-cache
 *   disable) is inferred from the surrounding ISB/maintenance pattern. */
uint64_t sptm_tlb_maintenance(uint64_t arg, uint32_t op)
{
	uint64_t saved;
	uint64_t v;

	if ((op & 0xfffffffdU) != 0)
		sptm_panic_code(0x31, op, sptm_panic_fmt_gen);

	saved = sptm_read_daif();
	if ((~(uint32_t)saved & 0x1c0U) != 0)
		sptm_write_daif(saved | 0x1c0);

	v = sptm_read_s3_4_c15_c0_4();
	sptm_write_s3_4_c15_c0_4(v | 2);
	__asm__ volatile("isb" ::: "memory");
	v = sptm_read_s3_4_c15_c0_4();
	sptm_write_s3_4_c15_c0_4(v & ~2ULL);
	__asm__ volatile("isb" ::: "memory");

	if (saved != 0x1c0)
		sptm_write_daif(saved);
	return arg;
}

/* -------------------------------------------------------------------------
 * FUN_000f7108 @ 0x000f7108   (est. sptm_invalid_op)
 * Ghidra: void FUN_000f7108(undefined8 param_1, undefined4 param_2)
 * Degenerate trap handler: always panics with code 0x31, carrying param_2.
 * Pair of FUN_000f6d54 — represents an invalid/unimplemented EL1 TLB
 * maintenance operation selector.
 * Confidence: low
 * Notes: no callers found; single instruction path straight into
 *   sptm_panic_code(0x31, param_2, ...). */
void sptm_invalid_op(uint64_t arg, uint32_t op)
{
	(void)arg;   /* only the selector is meaningful on the panic path */
	sptm_panic_code(0x31, op, sptm_panic_fmt_gen);
}
/* -------------------------------------------------------------------------
 * Slice 6 (0xf7d60 - 0xf84b3): one pmap frame-descriptor validator and the
 * AES-GCM context setup / key+IV / streaming-update API.  The three crypto
 * functions drive the AES-GCM engine whose low-level helpers (GHASH steps,
 * counter bump, bulk AES-GCM core, table build, context init) are defined in
 * the crypto reconstruction; only the high-level wrappers are reconstructed
 * here.  All Ghidra FUN_/DAT_ identifiers are kept in comments.
 *
 * New externs required beyond the shared preamble (the preamble already
 * declares the sptm_panic* family, sptm_snprintf, the per-CPU/guest-exit
 * helpers and the SPTM_PANIC_BUF_SIZE define; none of those are repeated).
 * ------------------------------------------------------------------------- */

/* 16-byte (x0:x1) return convention used by the FTE lookups. */
typedef struct sptm_ret16 { uintptr_t va; uintptr_t pa; } sptm_ret16_t;

/* FUN_000e3d7c — translate a physical address to its SPTM virtual/FTE form. */
extern void *sptm_phystokv(uint64_t paddr);

/* SPTM pmap globals (Ghidra DAT_ symbols; addresses in comments). */
extern uint64_t sptm_mem_low;        /* DAT_00095d18 — DRAM/FTE window start */
extern uint64_t sptm_mem_high;       /* DAT_00095d20 — DRAM/FTE window end   */
extern uint64_t sptm_window_base;    /* DAT_00095460 — FTE/PAPT VA base      */
extern uint64_t sptm_boot_root_fte;  /* DAT_00095d48 — current/root FTE paddr */
extern uint8_t  sptm_invalid_fte[];  /* DAT_00101f90 — fallback invalid FTE  */
extern uint8_t  sptm_fte_class[];    /* DAT_00095d51 — per-FTE-class table (stride 0x90) */
extern uint64_t sptm_level_table[];  /* DAT_00019c68 — FTE level/type-expected table */

/* Stack canary (DAT_00100000) and the noreturn canary-fail panic (FUN_000ae44c). */
extern uint64_t sptm_stack_canary;
extern __attribute__((noreturn)) void sptm_stack_chk_fail(void);

/* AES-GCM crypto helpers (defined in the crypto reconstruction files). */
extern int  sptm_gcm_ctx_init(uint64_t ctx);                       /* FUN_000b0cc8 */
extern void sptm_bzero_block(size_t n, void *dst);                 /* FUN_000b2584 */
extern void sptm_ghash_step(uint64_t ctx, const uint8_t *block);   /* FUN_000b0cb4 */
extern void sptm_ghash_table_build(uint8_t table[256], const uint8_t H[16]); /* FUN_000b1140 */
extern void sptm_gcm_state_advance(uint64_t ctx);                  /* FUN_000b2204 */
extern void sptm_uat_counter_bump(uint8_t *obj);                   /* FUN_000b20d0 */
/* FUN_000afad0 — AES-GCM bulk keystream+GHASH core.  Per the decompile the
 * argument order at this callsite is (input, output, ctx, len, H table, round
 * keys); the repo's crypto file declares a 7-arg (out,in,...) variant. */
extern void sptm_aes_gcm_core(const uint8_t *in, uint8_t *out, uint64_t ctx,
    size_t len, const uint8_t Ht[256], const uint32_t *rk);

/* -------------------------------------------------------------------------
 * FUN_000f7d60 @ 0x000f7d60   (est. sptm_frame_descriptor)
 * Ghidra: undefined FUN_000f7d60(ulong param_1, undefined8 param_2)
 * Validates that `paddr` is a 16 KiB-aligned address below 0xffffffffffffc000
 * and resolves the FTE descriptor covering it.  The current/root FTE paddr
 * (DAT_00095d48) is looked up either through the direct-window computation
 * (DAT_00095460 + index) or, when it falls outside the SPTM window, via
 * sptm_phystokv with the fixed invalid-FTE (DAT_00101f90) as fallback.  The
 * descriptor's frame type must be class 1 (else panic "Type %d class_of_FTE"),
 * and the paddr must lie within the region described by the frame's level
 * entry (DAT_00019c68[level] -> +0x60 size field), else panic.  Returns the
 * descriptor VA plus the validated paddr as a 16-byte pair.
 * Confidence: medium
 * Notes: called by FUN_000bd120/FUN_000bd57c (region start/size guards);
 *   sptm_phystokv is modelled as void* so the second return half is the input
 *   paddr; size bound is (uint64)(-size)-2 < paddr. */
sptm_ret16_t
sptm_frame_descriptor(uint64_t paddr)             /* param_1 */
{
	sptm_ret16_t result;
	uint64_t root_fte = sptm_boot_root_fte;       /* DAT_00095d48 */
	uint16_t *fte;
	uint64_t parent;
	const uint8_t *f;

	result.pa = paddr;

	if ((paddr & 0x3fff) == 0 && paddr < (uint64_t)0xffffffffffffc000) {
		if (root_fte < sptm_mem_low || sptm_mem_high <= root_fte) {
			/* Out of the direct window: look the frame up via the FTE tables. */
			fte = (uint16_t *)sptm_phystokv(root_fte);   /* FUN_000e3d7c */
			if (fte == NULL)
				fte = (uint16_t *)sptm_invalid_fte;      /* DAT_00101f90 */
		} else {
			/* Direct window: base + ((fte_pa - mem_low) >> 10 & ~0xf). */
			fte = (uint16_t *)(sptm_window_base +
			    ((root_fte - sptm_mem_low) >> 10 & 0xffffffff0));
			if (((sptm_window_base ^ (uint64_t)fte) & 0xffc0000000000000) != 0)
				fte = (uint16_t *)(((uint64_t)fte & 0xffffffffffff) |
				    0xc8a2000000000000);
		}
		f = (const uint8_t *)fte;
		if (sptm_fte_class[f[2] * 0x90] != 1)          /* class of FTE */
			sptm_panic("s: Type %d class of FTE %p %d");  /* FUN_000f8804 */
		parent = sptm_level_table[f[12]];              /* level entry */
		if ((uint64_t)(-*(int64_t *)(parent + 0x60)) - 2 < paddr) {
			result.va = (uintptr_t)fte;
			return result;
		}
	}
	sptm_panic_code(0x8000004, result.pa, "s: %s %s %d");  /* FUN_000f8844 */
}

/* -------------------------------------------------------------------------
 * FUN_000f7ff4 @ 0x000f7ff4   (est. sptm_gcm_ctx_setup)
 * Ghidra: undefined8 FUN_000f7ff4(long param_1, long param_2)
 * Initializes an AES-GCM context at `ctx` from an algorithm descriptor at
 * `descriptor`.  Reads the descriptor's method/ops table (descriptor+0x48)
 * and requires a 16-byte key length (ops[8] == 0x10, i.e. AES-128); otherwise
 * returns -1.  On success it stores the ops table into ctx+0x68 and the key
 * schedule workspace pointer (ctx+0x180) into ctx+0x70, copies the descriptor
 * key field into ctx+0x78, invokes the ops "prepare" method (ops+0x10),
 * resets the ctx flags (ctx+0x52 = 0), runs sptm_gcm_ctx_init, invokes the
 * ops key-schedule method (ops+0x18) over the key, and finally builds the
 * GHASH table at ctx+0x80 from the hash key at ctx.  Returns 0.
 * Confidence: high
 * Notes: ops methods (ops+0x10 / ops+0x18) are the PAC'd crypto-table
 *   function pointers; sptm_ghash_table_build is FUN_000b1140. */
int
sptm_gcm_ctx_setup(uint64_t descriptor, uint64_t ctx)   /* param_1, param_2 */
{
	uint64_t ops = *(uint64_t *)(descriptor + 0x48);

	if (*(uint64_t *)(ops + 8) != 0x10)          /* 16-byte key: AES-128 */
		return -1;

	*(uint64_t *)(ctx + 0x68) = ops;             /* method table */
	*(uint64_t *)(ctx + 0x70) = ctx + 0x180;     /* key-schedule workspace */
	*(uint32_t *)(ctx + 0x78) = *(uint32_t *)(descriptor + 8);
	(*(void (**)(uint64_t))(ops + 0x10))(ops);   /* ops->prepare(ops) */
	*(uint16_t *)(ctx + 0x52) = 0;
	sptm_gcm_ctx_init(ctx);                      /* FUN_000b0cc8 */
	(*(void (**)(uint64_t, uint64_t, uint64_t, uint64_t))(ops + 0x18))(
	    *(uint64_t *)(ctx + 0x70), 1, ctx + 0x10, ctx);   /* ops->keysched */
	sptm_ghash_table_build((uint8_t *)(ctx + 0x80),
	    (const uint8_t *)ctx);                   /* FUN_000b1140 */
	return 0;
}

/* -------------------------------------------------------------------------
 * FUN_000f8084 @ 0x000f8084   (est. sptm_gcm_key_iv_setup)
 * Ghidra: void FUN_000f8084(long param_1, ulong param_2, undefined8 *param_3)
 * Loads the key/IV material into an initialized (state==1, flag bit0 clear)
 * GCM context at `ctx`.  A length of 0xc (12 bytes) sets a GCM IV: the first
 * 8 bytes into the counter word at ctx+0x20, the next 4 bytes at ctx+0x28 and
 * the big-endian counter start 0x01000000 at ctx+0x2c.  Otherwise `length`
 * bytes from `data` are folded (XOR) into the 16-byte GHASH state at ctx+0x20
 * in block/partial steps (ghash_step after each block), then the bit-length
 * block {0, bswap64(length<<3)} is XORed in and hashed.  Both paths then copy
 * the counter word into ctx+0x30/0x38, bump the counter, and move the state
 * to 2 (AAD phase).  Returns void; invalid state/empty input falls through
 * to the stack-canary check and returns.
 * Confidence: medium
 * Notes: byte-swap via bswap64(length<<3); the sptm_uat_counter_bump /
 *   ghash_step helpers are FUN_000b20d0 / FUN_000b0cb4; stack canary via
 *   FUN_000ae44c on mismatch. */
void
sptm_gcm_key_iv_setup(uint64_t ctx, uint64_t length, const uint8_t *data)
{
	uint64_t canary = sptm_stack_canary;          /* __data */
	uint64_t keyblock_hi = 0, keyblock_lo = 0;    /* local_50 / uStack_48 */
	uint64_t rem;

	if (*(uint16_t *)(ctx + 0x50) != 1 || (*(uint16_t *)(ctx + 0x52) & 1) != 0)
		goto done;
	if (length == 0 || data == NULL)
		goto done;

	if (length == 0xc) {
		/* 12-byte IV: counter word + 32-bit big-endian counter at 1. */
		*(uint64_t *)(ctx + 0x20) = *(const uint64_t *)data;         /* *param_3 */
		*(uint32_t *)(ctx + 0x28) = *(const uint32_t *)(data + 8);   /* *(param_3+1) */
		*(uint32_t *)(ctx + 0x2c) = 0x1000000;
	} else {
		/* Fold the key material into the GHASH state, then hash the length
		 * block {0, bswap64(bitlen)}. */
		sptm_bzero_block(8, &keyblock_hi);                       /* FUN_000b2584 */
		keyblock_lo = __builtin_bswap64(length << 3);            /* uStack_48 */
		sptm_bzero_block(0x10, (void *)(ctx + 0x20));            /* FUN_000b2584 */
		rem = length;
		if (rem < 0x10) {
partial:
			do {
				*(uint8_t *)(ctx + rem + 0x1f) ^= data[rem - 1];
				rem--;
			} while (rem != 0);
			sptm_ghash_step(ctx, (const uint8_t *)(ctx + 0x20));
		} else {
			do {
				int i = 0;
				do {
					*(uint8_t *)(ctx + i + 0x2f) ^= data[i + 0xf];
					i--;
				} while (i != -0x10);
				sptm_ghash_step(ctx, (const uint8_t *)(ctx + 0x20));
				data += 0x10;
				rem -= 0x10;
			} while (0xf < rem);
			if (rem != 0)
				goto partial;
		}
		*(uint64_t *)(ctx + 0x28) ^= keyblock_lo;    /* uStack_48 */
		*(uint64_t *)(ctx + 0x20) ^= keyblock_hi;    /* local_50 */
		sptm_ghash_step(ctx, (const uint8_t *)(ctx + 0x20));
	}

	*(uint64_t *)(ctx + 0x38) = *(uint64_t *)(ctx + 0x28);
	*(uint64_t *)(ctx + 0x30) = *(uint64_t *)(ctx + 0x20);
	sptm_uat_counter_bump((uint8_t *)ctx);           /* FUN_000b20d0 */
	*(uint16_t *)(ctx + 0x50) = 2;
done:
	if (canary != sptm_stack_canary)
		sptm_stack_chk_fail();                       /* FUN_000ae44c */
}

/* -------------------------------------------------------------------------
 * FUN_000f8214 @ 0x000f8214   (est. sptm_gcm_update)
 * Ghidra: undefined8 FUN_000f8214(long param_1, ulong param_2, long param_3, long param_4)
 * Streams `length` bytes of data from `in` to `out` through the AES-GCM
 * context at `ctx`, authenticating while producing keystream.  Advances the
 * GCM state machine (state 2 -> 3); requires state 3 else returns 0xffffffbc,
 * and rejects an overflowing byte count (ctx+0x60 + length wraps, or exceeds
 * 0xfffffffe0) with 0xffffffbd.  Handles a partial leading block by XORing
 * input into the keystream buffer at ctx+0x1f/ctx+0x4f (ghash_step + counter
 * bump), processes full blocks through the bulk AES-GCM core
 * (sptm_aes_gcm_core over ctx+0x80 table / ctx+0x70 keys) followed by the
 * block callback (method table +0x18) and per-block ghash/counter steps, then
 * finishes the trailing partial block.  Updates the running byte count at
 * ctx+0x60 and returns 0.
 * Confidence: medium
 * Notes: helpers are FUN_000b2204 (state advance), FUN_000b0cb4 (ghash step),
 *   FUN_000b20d0 (counter bump), FUN_000afad0 (bulk AES-GCM core). */
int
sptm_gcm_update(uint64_t ctx, uint64_t length, const uint8_t *in, uint8_t *out)
{
	uint64_t pos = *(uint64_t *)(ctx + 0x60);   /* running byte count */
	uint32_t offset;                            /* uVar3: current block offset */
	uint64_t n, i;

	sptm_gcm_state_advance(ctx);                /* FUN_000b2204 */
	if (*(uint16_t *)(ctx + 0x50) != 3)
		return 0xffffffbc;
	if (pos + length < pos)                     /* CARRY8(pos, length) */
		return 0xffffffbd;
	if (0xfffffffe0 < pos + length)
		return 0xffffffbd;

	offset = (uint32_t)pos & 0xf;
	if ((pos & 0xf) != 0) {
		n = 0x10 - offset;                      /* bytes to next block boundary */
		if (length < n)
			goto tail;
		i = n;
		do {
			*(uint8_t *)(ctx + offset + 0xf + i) ^= in[i - 1];
			i--;
		} while (i != 0);
		sptm_ghash_step(ctx, (const uint8_t *)(ctx + 0x10));
		i = n;
		do {
			out[i - 1] = *(uint8_t *)(ctx + offset + 0x3f + i) ^ in[i - 1];
			i--;
		} while (i != 0);
		length -= n;
		in += n;
		out += n;
		*(uint64_t *)(ctx + 0x60) += n;
		sptm_uat_counter_bump((uint8_t *)ctx);  /* FUN_000b20d0 */
	}

	if (0xf < length) {
		sptm_aes_gcm_core(in, out, ctx, (uint32_t)length & 0xfffffff0,
		    (const uint8_t *)(ctx + 0x80),
		    *(const uint32_t **)(ctx + 0x70));  /* FUN_000afad0 */
		n = length & 0xfffffff0;
		in += n;
		out += n;
		*(uint64_t *)(ctx + 0x60) += n;
		/* Invoke the block callback (method table +0x18). */
		(*(void (**)(uint64_t, uint64_t, uint64_t, uint64_t))
		    (*(uint64_t *)(ctx + 0x68) + 0x18))
		    (*(uint64_t *)(ctx + 0x70), 1, ctx + 0x20, ctx + 0x40);
		length &= 0xffffffff0000000f;
		while (0xf < length) {
			int k = 0;
			do {
				*(uint8_t *)(ctx + k + 0x1f) ^= in[k + 0xf];
				k--;
			} while (k != -0x10);
			sptm_ghash_step(ctx, (const uint8_t *)(ctx + 0x10));
			k = 0;
			do {
				out[k + 0xf] = *(uint8_t *)(ctx + k + 0x4f) ^ in[k + 0xf];
				k--;
			} while (k != -0x10);
			in += 0x10;
			out += 0x10;
			*(uint64_t *)(ctx + 0x60) += 0x10;
			sptm_uat_counter_bump((uint8_t *)ctx);
			length -= 0x10;
		}
	}
	offset = 0;
tail:
	if (length != 0) {
		n = length;
		do {
			*(uint8_t *)(ctx + offset + 0xf + n) ^= in[n - 1];
			n--;
		} while (n != 0);
		n = length;
		do {
			out[n - 1] = *(uint8_t *)(ctx + offset + 0x3f + n) ^ in[n - 1];
			n--;
		} while (n != 0);
		*(uint64_t *)(ctx + 0x60) += length;
	}
	return 0;
}
/* -------------------------------------------------------------------------
 * SPTM panic printers (region 0xf8 - 0xf9).
 * ------------------------------------------------------------------------- */

/* FUN_000f84e4 @ 0x000f84e4   (est. sptm_panic_format)
 * Ghidra: void FUN_000f84e4(undefined8 fmt, undefined8 args)
 * Formats the panic message into the per-CPU panic buffer (0xa28 bytes at
 * cpu+3), announces it on the console, flags the panic record, then halts the
 * CPU in an unbounded WFE spin.  On a format overflow it emits the
 * "PANIC_BUF_SIZE ..." truncation message instead of the banner.
 * Confidence: medium
 * Notes: helper calls FUN_000ad278 (sptm_snprintf), FUN_000c15b4 (serial),
 *   FUN_000c59b8 (copy), FUN_000ae278 (strlcpy_chk), FUN_000a1374
 *   (sptm_guest_exit_handoff), SoftwareBreakpoint(1,0xf8714); config bits
 *   DAT_001012d8 0x12/0x17; SCTLR==0x2f selects the alternate record base
 *   DAT_000aa018 vs the primary DAT_000a5028. */
static void sptm_panic_format(const char *fmt, ...)
{
	uint64_t cpu = sptm_per_cpu_base();
	char *pbuf = (char *)(cpu ? (uintptr_t)(cpu + 3) : (uintptr_t)sptm_panic_fallback_buf);
	uint32_t n;
	uint64_t record;
	va_list args;

	/* Format the message into the per-CPU 0xa28-byte panic buffer. */
	va_start(args, fmt);
	n = sptm_snprintf(pbuf, SPTM_PANIC_BUF_SIZE, 0, (uint64_t)-1, fmt, args);
	va_end(args);
	if (n < SPTM_PANIC_BUF_SIZE) {
		sptm_serial_str("\nSPTM PANIC:\n");                 /* 0x54bd */
	} else {
		/* Overflow: report the truncation instead of the banner. */
		char trunc[0x80];
		sptm_copy_format(trunc, sizeof trunc, sizeof trunc,
		    "PANIC_BUF_SIZE %u > %u" /* 0x5432 */);
		sptm_serial_str("PANIC_BUF_SIZE");                   /* 0x549e prefix */
		sptm_serial_str("TRUNCATED ORIGINAL PANIC");         /* 0x54a1 */
	}

	/* On the guarded-dispatch / guest-exit violating path, hand off first. */
	if ((sptm_panic_config_flags & (1U << 0x12)) &&
	    (sptm_spsel() != 1 || (sptm_panic_config_flags & (1U << 0x17)))) {
		sptm_guest_exit_handoff((uintptr_t)pbuf, 0, 0, 0);
		sptm_sw_breakpoint(1, 0xf8714);
	}

	/* Record the panic and copy the formatted message into the record. */
	record = (sptm_panic_record_alt == 0 || sptm_read_sctlr_el2() == 0x2f)
	    ? sptm_panic_record_base : sptm_panic_record_alt;
	if (record != 0) {
		uint64_t count = *(uint64_t *)(record + 0x40);
		if (1 < (count - 1))          /* count==0 or count>=3 */
			sptm_bzero((void *)(record + 0x40), 8);
		*(uint8_t *)(record + 0x10) = 1;
		sptm_bzero((void *)(record + 0x11), 7);
		sptm_strlcpy_chk((char *)(record + 0x48), pbuf,
		    SPTM_PANIC_BUF_SIZE, (uint64_t)-1);
		sptm_bzero((void *)(record + 0x38), 8);
	}

	/* Panic is terminal: halt this CPU. */
	for (;;)
		sptm_wfe();
}

/* FUN_000f8714 @ 0x000f8714   (est. sptm_panic_record)
 * Ghidra: void FUN_000f8714(undefined8 cpu_id, undefined8 arg, undefined8 fp)
 * Formats a secondary panic frame into a 0xa28-byte stack buffer, then copies
 * it into the per-CPU panic buffer and hands off / breaks.  Also records the
 * panicking CPU and panics if the violation flag is not yet set.
 * Confidence: low
 * Notes: helper calls FUN_000abb60 (sptm_bzero), FUN_000ad278 (snprintf),
 *   FUN_000d6088 (record panic cpu), FUN_000c59b8 (copy), FUN_000a1374
 *   (sptm_guest_exit_handoff), SoftwareBreakpoint(1,0xf8804); the 0x54cb
 *   string reads "%s: [SPTM]: somehow a violation ...". */
static void sptm_panic_record(uint64_t cpu_id, uint64_t arg, uintptr_t fp)
{
	char stack[SPTM_PANIC_BUF_SIZE];   /* auStack_a68[2600] */
	uint64_t cpu;

	sptm_bzero(stack, SPTM_PANIC_BUF_SIZE);
	sptm_snprintf(stack, SPTM_PANIC_BUF_SIZE, 0, SPTM_PANIC_BUF_SIZE,
	    (const char *)arg, fp);
	if ((sptm_panic_config_flags & (1U << 0x12)) == 0) {
		sptm_record_panic_cpu(cpu_id);
		sptm_panic("%s: [SPTM]: somehow a violation with panic state", "sptm");
	}
	cpu = sptm_per_cpu_base();
	sptm_record_panic_cpu(cpu_id);
	sptm_copy_format((char *)(cpu + 3), SPTM_PANIC_BUF_SIZE,
	    SPTM_PANIC_BUF_SIZE, stack);
	cpu = sptm_per_cpu_base();
	sptm_guest_exit_handoff((uintptr_t)(cpu + 3), 0, 0, 0);
	sptm_sw_breakpoint(1, 0xf8804);
}

/* FUN_000f8804 @ 0x000f8804   (est. sptm_panic)
 * Ghidra: void FUN_000f8804(undefined8 fmt, undefined8 arg2, undefined8 arg3)
 * Noreturn printf-style SPTM panic.  Formats the message via
 * sptm_panic_format, records the panicking-cpu dispatch name, and prints the
 * final "%s: [%s] %s at pc 0x%016llx lr 0x%016llx" line before halting.
 * Confidence: medium
 * Notes: the two continuation printers FUN_000f8824 / FUN_000f8834 are
 *   installed as a follow-up frame; helper calls FUN_000c5a18 (panicking
 *   cpu), FUN_000f8714, FUN_000e7678 (dispatch name); the recursive format
 *   string at 0xf0b7. */
void sptm_panic(const char *fmt, ...)
{
	uintptr_t fp = (uintptr_t)__builtin_frame_address(0);
	uint32_t pcpu;
	uint64_t cpu;

	/* Format the primary message (sptm_panic_format halts in the common
	 * path; the continuation printers below record CPU + dispatch name). */
	sptm_panic_format(fmt, (uintptr_t)&fmt);
	pcpu = sptm_get_panicking_cpu_id();
	sptm_panic_record(pcpu, 0, fp);
	cpu = sptm_per_cpu_base();
	(void)sptm_dispatch_name(*(uint64_t *)(cpu + 0xa38));
	/* Terminal tail print (only reachable if the format path did not halt). */
	sptm_panic("%s: [%s] %s at pc 0x%016llx lr 0x%016llx",
	    "sptm", "panic", "panic", 0ULL, 0ULL);
}

/* FUN_000f8824 @ 0x000f8824   (est. sptm_panic_fmt)
 * Ghidra: void FUN_000f8824(undefined8 fmt, undefined8 arg2, undefined8 arg3)
 * Noreturn panic continuation: records the panicking-cpu dispatch name and
 * prints the same "%s: [%s] %s at pc ..." tail.  Smaller variant of
 * sptm_panic used as the first continuation printer.
 * Confidence: low
 * Notes: helper calls FUN_000f84e4, FUN_000c5a18, FUN_000f8714, FUN_000e7678;
 *   recurses into FUN_000f8804 with the 0xf0b7 format string. */
void sptm_panic_fmt(uint32_t code, ...)
{
	uintptr_t fp = (uintptr_t)__builtin_frame_address(0);
	uint32_t pcpu;
	uint64_t cpu;

	(void)code;
	sptm_panic_format(0, 0);
	pcpu = sptm_get_panicking_cpu_id();
	sptm_panic_record(pcpu, 0, fp);
	cpu = sptm_per_cpu_base();
	(void)sptm_dispatch_name(*(uint64_t *)(cpu + 0xa38));
	sptm_panic("%s: [%s] %s at pc 0x%016llx lr 0x%016llx",
	    "sptm", "panic", "panic", 0ULL, 0ULL);
}

/* FUN_000f8834 @ 0x000f8834   (est. sptm_panic_bad_dt)
 * Ghidra: void FUN_000f8834(undefined8 fmt, undefined8 arg2, undefined8 arg3)
 * Noreturn panic continuation used for a bad device-tree panic: records the
 * panicking-cpu dispatch name then prints the panic tail.  Second
 * continuation printer.
 * Confidence: low
 * Notes: helper calls FUN_000c5a18, FUN_000f8714, FUN_000e7678; recurses into
 *   FUN_000f8804 with the 0xf0b7 format string.  sptm_init.c declares this as
 *   "void sptm_panic_bad_dt(void)" — a signature guess to reconcile. */
void sptm_panic_bad_dt(const char *fmt, ...)
{
	uintptr_t fp = (uintptr_t)__builtin_frame_address(0);
	uint32_t pcpu;
	uint64_t cpu;

	(void)fmt;
	pcpu = sptm_get_panicking_cpu_id();
	sptm_panic_record(pcpu, 0, fp);
	cpu = sptm_per_cpu_base();
	(void)sptm_dispatch_name(*(uint64_t *)(cpu + 0xa38));
	sptm_panic("%s: [%s] %s at pc 0x%016llx lr 0x%016llx",
	    "sptm", "panic", "panic", 0ULL, 0ULL);
}

/* FUN_000f8844 @ 0x000f8844   (est. sptm_panic_code)
 * Ghidra: void FUN_000f8844(undefined8 code, undefined8 arg, undefined8 fmt)
 * Noreturn SPTM panic with an explicit error code: records the panicking-cpu
 * dispatch name then prints the panic tail.  The code and arg are carried
 * into the record path.
 * Confidence: medium
 * Notes: helper calls FUN_000f8714 (which receives code+fmt), FUN_000e7678;
 *   recurses into FUN_000f8804 with the 0xf0b7 format string. */
void sptm_panic_code(unsigned int code, uintptr_t arg, const char *fmt, ...)
{
	uintptr_t fp = (uintptr_t)__builtin_frame_address(0);
	uint64_t cpu;

	sptm_panic_record(code, arg, fp);
	(void)fmt;
	cpu = sptm_per_cpu_base();
	(void)sptm_dispatch_name(*(uint64_t *)(cpu + 0xa38));
	sptm_panic("%s: [%s] %s at pc 0x%016llx lr 0x%016llx",
	    "sptm", "panic", "panic", 0ULL, 0ULL);
}

/* FUN_000f89b4 @ 0x000f89b4   (est. sptm_invalid_genter)
 * Ghidra: void FUN_000f89b4(void)
 * Noreturn handler for an invalid guarded (GENTER) entry into SPTM: calls the
 * aux routine FUN_000c59f4 then panics with the "SPTM_Dispatch: Invalid
 * GENTER" message.  This is the ring-1 gate's hard rejection path.
 * Confidence: high
 * Notes: body is `FUN_000c59f4(); sptm_panic("%s: [SPTM Dispatch] Invalid
 *   GENTER");` — the 0xf352 string reads "%s: [SPTM Dispatch] Invalid
 *   GENTER". */
void sptm_invalid_genter(void)
{
	sptm_guest_exit_handoff(0, 0, 0, 0);   /* FUN_000c59f4 (aux) */
	sptm_panic("%s: [SPTM Dispatch] Invalid GENTER", "sptm");
}
