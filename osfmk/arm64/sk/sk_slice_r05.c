/* Recreated from exclavecore_bundle.t8142.RELEASE.im4p (cL4 Secure Kernel,
 * arm64e, image base 0) - the cL4 microkernel (GL1), "cL4 (679.100.61)".
 * Ground truth: Ghidra FUN_ names + addresses in program cl4_kernel.raw.
 * This slice (0x3c7a80-0x3ccc98, wave SKR05) is the message-register
 * marshalling subsystem: each function serializes one cL4 object type into a
 * kernel message-register buffer (at ctx+0x2140, with the word-count slot at
 * ctx+0x2150) as a run of type-tag bytes followed by the object fields. The
 * helper calls below are owned by adjacent range slices and are declared
 * extern; in-range helpers (003cc324) have real bodies here.
 * All names are estimates unless string-matched. */

#include <stdint.h>
#include <stddef.h>
#include <string.h>

/* ------------------------------------------------------------------ *
 * External marshalling helpers (owned by adjacent range slices).
 * ------------------------------------------------------------------ */
/* FUN_003a3a70 - append n raw bytes from src to the message buffer at buf. */
extern void cL4_mr_emit(unsigned long buf, const void *src, unsigned long n, unsigned long slot);
/* FUN_003acd3c - append a single tag byte to the message buffer at buf. */
extern void cL4_mr_emit_char(unsigned long buf, const void *ch, unsigned long slot);
/* FUN_003d05e0 - append a 64-bit value to the message buffer at buf. */
extern void cL4_mr_emit_u64(unsigned long buf, unsigned long val);
/* FUN_003d11d4 - marshal a raw word value from desc. */
extern void cL4_mr_wrap1(unsigned long ctx, unsigned long desc, unsigned long depth);
/* FUN_003d01ac - marshal a word value from desc. */
extern void cL4_mr_wrap2(unsigned long ctx, unsigned long desc, unsigned long depth);
/* FUN_003d081c - marshal a nested object from desc. */
extern void cL4_mr_wrap3(unsigned long ctx, unsigned long desc, unsigned long depth);
/* FUN_003d0280 - marshal the i-th message-register word of desc (variadic). */
extern void cL4_mr_op(unsigned long a, unsigned long b, unsigned long c, unsigned long d, ...);
/* FUN_003d174c - marshal val then append tag (n bytes) to the message buffer. */
extern void cL4_mr_tag(unsigned long out, unsigned long val, const void *tag, unsigned long n, unsigned long depth);
/* FUN_003d1218 - marshal a value at depth. */
extern void cL4_mr_val(unsigned long out, unsigned long ctx, unsigned long val, unsigned long depth);
/* FUN_003d23c4 - marshal a (lo,hi) pair with a flag. */
extern void cL4_mr_pair(unsigned long out, unsigned long a, unsigned long b, unsigned long flag, unsigned long depth);
/* FUN_003d02dc - marshal a guarded word value. */
extern void cL4_mr_gword(unsigned long out, unsigned long ctx, unsigned long val, unsigned long depth);
/* FUN_003d1ad4 - begin marshalling of an object (init slot). */
extern void cL4_mr_init(unsigned long ctx, unsigned long desc, unsigned long x);
/* FUN_003bfae4 - recursively marshal a nested descriptor. */
extern void cL4_mr_rec(unsigned long out, unsigned long ctx, unsigned long desc, unsigned long depth);
/* FUN_003c4b0c - terminate/commit the current message word. */
extern void cL4_mr_tail(unsigned long out, unsigned long ctx, unsigned long val);
/* FUN_003c5af4 - marshal a chained descriptor element. */
extern void cL4_mr_chain(unsigned long out, unsigned long ctx, unsigned long desc, unsigned long depth);
/* FUN_003a3430 / FUN_003a3460 - object field get/set by tag. */
extern unsigned long cL4_obj_get(unsigned long obj, unsigned long tag);
extern void cL4_obj_set(unsigned long field, unsigned long val, unsigned long obj);
/* strlen / strcmp thunks. */
extern unsigned long cL4_strlen(const char *s);
extern int cL4_strcmp(const char *a, const char *b);

/* Descriptor kind byte (at +0x12): 1=one word, 2=two words, 3=..., 5=array.
 * desc[1] holds the element count for kind 5; *desc is the array base. */
static inline unsigned char cL4_mr_kind(const unsigned long *desc)
{
    return *(const unsigned char *)((const char *)desc + 0x12);
}

/* ------------------------------------------------------------------ *
 * Function bodies (address order).
 * ------------------------------------------------------------------ */
