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
#include <stdbool.h>
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
/* FUN_003d11d4 - marshal a raw word value from desc (variadic: 3 or 4 args). */
extern void cL4_mr_wrap1(unsigned long a, unsigned long b, unsigned long c, ...);
/* FUN_003d01ac - marshal a word value from desc (variadic: 3 or 4 args). */
extern void cL4_mr_wrap2(unsigned long a, unsigned long b, unsigned long c, ...);
/* FUN_003d081c - marshal a nested object from desc. */
extern void cL4_mr_wrap3(unsigned long ctx, unsigned long desc, unsigned long depth);
/* FUN_003d0280 - marshal the i-th message-register word of desc (variadic). */
extern void cL4_mr_op(unsigned long a, ...);
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
/* FUN_003cba04 (in range) - marshal a descriptor word; defined below. */
void cL4_mr_cba04(int *out, long ctx, long *desc, int depth);
/* FUN_003cc324 (in range) - marshal all descriptor words; defined below. */
void cL4_mr_cc324(int *out, long ctx, long desc, int depth);
/* FUN_003a3430 / FUN_003a3460 - object field get/set by tag. */
extern unsigned long cL4_obj_get(unsigned long obj, unsigned long tag);
extern void cL4_obj_set(unsigned long field, unsigned long val, unsigned long obj);
/* strlen / strcmp thunks. */
extern unsigned long cL4_strlen(const char *s);
extern int cL4_strcmp(const char *a, const char *b);
/* FUN_004ba510 - report an unknown message element tag (noreturn-ish). */
extern void cL4_mr_4ba510(long desc);
/* FUN_00116d60 - kernel panic on invalid element (noreturn). */
extern void cL4_mr_116d60(void) __attribute__((noreturn));

/* Descriptor kind byte (at +0x12): 1=one word, 2=two words, 3=..., 5=array.
 * desc[1] holds the element count for kind 5; *desc is the array base. */
static inline unsigned char cL4_mr_kind(const unsigned long *desc)
{
    return *(const unsigned char *)((const char *)desc + 0x12);
}

/* ------------------------------------------------------------------ *
 * Function bodies (address order).
 * ------------------------------------------------------------------ */

/* FUN_003c7a80 @ 0x003c7a80   (est. cL4_mr_emit_MP)
 * Ghidra: void FUN_003c7a80(int *param_1,long param_2,undefined8 param_3,int param_4)
 * Marshals a message-register word via cL4_mr_wrap1, then emits the two-byte
 * type tag "MP". Clears the result word on success.
 * Confidence: medium
 */
void cL4_mr_emit_MP(int *out, unsigned long ctx, unsigned long desc, int depth)
{
    cL4_mr_wrap1(ctx, desc, (unsigned long)(depth + 1));
    if (*out == 0) {
        cL4_mr_emit(ctx + 0x2140, "MP", 2, *(unsigned long *)(ctx + 0x2150));
        *out = 0; out[2] = 0; out[3] = 0; out[4] = 0;
    }
}

/* FUN_003c7adc @ 0x003c7adc   (est. cL4_mr_dispatch_descriptor)
 * Ghidra: void FUN_003c7adc(undefined8 param_1,long *param_2,int param_3)
 * Resolves a descriptor to its payload word (following kind-5 chains) and
 * marshals it with the one-byte tag 'g' (DAT_005d92e3).
 * Confidence: medium
 */
void cL4_mr_dispatch_g(unsigned long out, long *desc, int depth)
{
    unsigned long val;
    if (1 < cL4_mr_kind((unsigned long *)desc) - 1) {
        if ((cL4_mr_kind((unsigned long *)desc) != 5) || ((int)desc[1] == 0)) {
            val = 0;
        } else {
            desc = (long *)*desc;
            val = *desc;
        }
    } else {
        val = *desc;
    }
    cL4_mr_tag(out, val, "g", 1, (unsigned long)(depth + 1));
}

/* FUN_003c7b24 @ 0x003c7b24   (est. cL4_mr_emit_switch)
 * Ghidra: void FUN_003c7b24(int *param_1,long param_2,long *param_3,int param_4)
 * Marshals a run of descriptor words. Depending on a state byte at ctx+0x2158
 * it first emits the "$s" or "$e" tag, then iterates the descriptor's word
 * span (kind 1/2 single element, kind 5 array of count desc[1]) and marshals
 * each element via cL4_mr_rec, following the reversed element chain for kind
 * 5. Element tags are 16-bit at (word+0x10). Clears the result on success.
 * Confidence: medium
 */
void cL4_mr_emit_switch(int *out, long ctx, long *desc, int depth)
{
    unsigned short elem_tag;
    unsigned char kind, walk_flag;
    unsigned char mask;
    long *start, *end, *base, *walk;

    if (*(char *)(ctx + 0x2158) == '\0') {
        cL4_mr_emit(ctx + 0x2140, "$s", 2, *(unsigned long *)(ctx + 0x2150));
    } else if (*(char *)(ctx + 0x2158) == '\x01') {
        cL4_mr_emit(ctx + 0x2140, "$e", 2, *(unsigned long *)(ctx + 0x2150));
    }
    kind = cL4_mr_kind((unsigned long *)desc);
    start = desc;
    if (kind - 1 < 2) {
        /* kind 1 or 2: the element span is one/two words past the descriptor */
        if (kind == 1)      { end = desc + 1; }
        else if (kind == 2) { end = desc + 2; }
        else if (kind == 5) { end = (long *)*desc; }
        else                { end = 0; }
    } else {
        /* kind >= 3: only kind 5 (array) is valid; span = *desc .. +count */
        if (kind != 5) {
            start = 0;
        } else {
            end = (long *)*desc;
            start = end;
        }
    }
    end = end + *(unsigned int *)(desc + 1);
    if (start != end) {
        walk_flag = 0;
        do {
            elem_tag = *(unsigned short *)(*start + 0x10);
            mask = 1;
            if (elem_tag < 0x99) {
                if (0x2b < (unsigned int)elem_tag - 0x37 ||
                    (1UL << ((unsigned long)((unsigned int)elem_tag - 0x37) & 0x3f) & 0xdc6010000efUL) == 0)
                    goto marshal;
            }
            else if (((0x28 < (unsigned int)elem_tag - 0x14e ||
                       (1UL << ((unsigned long)((unsigned int)elem_tag - 0x14e) & 0x3f) & 0x18000206e01UL) == 0) &&
                      (0x21 < (unsigned int)elem_tag - 0x10d ||
                       (1UL << ((unsigned long)((unsigned int)elem_tag - 0x10d) & 0x3f) & 0x300400001UL) == 0)) &&
                     (0x15 < (unsigned int)elem_tag - 0x99 ||
                      (1U << ((unsigned int)elem_tag - 0x99 & 0x1f) & 0x220001U) == 0)) {
                goto marshal;
            }
            /* otherwise the tag hits a dispatch bucket; still marshals below */
        marshal:
            cL4_mr_rec((unsigned long)out, ctx, *start, (unsigned long)(depth + 1));
            walk = start;
            if (*out != 0 || (walk_flag ^ 1)) {
                if (*out != 0) return;
                mask = 0;
            } else {
                /* walk the element chain backward down to the array base */
                while (1) {
                    base = desc;
                    if (1 < cL4_mr_kind((unsigned long *)desc) - 1) {
                        if (cL4_mr_kind((unsigned long *)desc) == 5) base = (long *)*desc;
                        else base = 0;
                    }
                    if (walk == base) break;
                    cL4_mr_rec((unsigned long)out, ctx, walk[-1], (unsigned long)(depth + 1));
                    walk = walk - 1;
                    if (*out != 0) return;
                }
                mask = 0;
            }
            walk_flag = mask;
            start = start + 1;
        } while (start != end);
    }
    *out = 0; out[2] = 0; out[3] = 0; out[4] = 0;
}

/* FUN_003c7d70 @ 0x003c7d70   (est. cL4_mr_dispatch_G)
 * Ghidra: void FUN_003c7d70(undefined8 param_1,long *param_2,int param_3)
 * Resolves descriptor payload word and marshals it with tag 'G' (DAT_005d37c4).
 * Confidence: medium
 */
void cL4_mr_dispatch_G(unsigned long out, long *desc, int depth)
{
    unsigned long val;
    if (1 < cL4_mr_kind((unsigned long *)desc) - 1) {
        if ((cL4_mr_kind((unsigned long *)desc) != 5) || ((int)desc[1] == 0)) {
            val = 0;
        } else {
            desc = (long *)*desc;
            val = *desc;
        }
    } else {
        val = *desc;
    }
    cL4_mr_tag(out, val, "G", 1, (unsigned long)(depth + 1));
}

/* FUN_003c7db8 @ 0x003c7db8   (est. cL4_mr_emit_fe)
 * Ghidra: void FUN_003c7db8(int *param_1,long param_2,undefined8 param_3,int param_4)
 * Marshals a word, then emits tag "fe". Clears result on success.
 * Confidence: medium
 */
void cL4_mr_emit_fe(int *out, unsigned long ctx, unsigned long desc, int depth)
{
    cL4_mr_wrap1(ctx, desc, (unsigned long)(depth + 1));
    if (*out == 0) {
        cL4_mr_emit(ctx + 0x2140, "fe", 2, *(unsigned long *)(ctx + 0x2150));
        *out = 0; out[2] = 0; out[3] = 0; out[4] = 0;
    }
}

/* FUN_003c7e14 @ 0x003c7e14   (est. cL4_mr_emit_fE)
 * Ghidra: void FUN_003c7e14(int *param_1,long param_2,undefined8 param_3,int param_4)
 * Marshals a word, then emits tag "fE". Clears result on success.
 * Confidence: medium
 */
void cL4_mr_emit_fE(int *out, unsigned long ctx, unsigned long desc, int depth)
{
    cL4_mr_wrap1(ctx, desc, (unsigned long)(depth + 1));
    if (*out == 0) {
        cL4_mr_emit(ctx + 0x2140, "fE", 2, *(unsigned long *)(ctx + 0x2150));
        *out = 0; out[2] = 0; out[3] = 0; out[4] = 0;
    }
}

/* FUN_003c7e70 @ 0x003c7e70   (est. cL4_mr_typed_string)
 * Ghidra: void FUN_003c7e70(undefined4 *param_1,long param_2,long *param_3)
 * Classifies a string descriptor by its length (13/18/15 bytes) against a set
 * of little-endian identifier patterns (@calllee_, @guarantee_... no:
 * "@calllee_", "@guarantee_" reversed) and emits the matching one-byte tag
 * ('x','g','y'). On mismatch sets error 0x792 with kind 0xf.
 * Confidence: medium
 */
void cL4_mr_typed_string(unsigned int *out, long ctx, long *desc)
{
    long len = desc[1];
    unsigned int err, kind;
    char tag;
    unsigned long slot = *(unsigned long *)(ctx + 0x2150);

    if (len == 0xd) {
        if (*desc == 0x5f65656c6c616340 && *(long *)((char *)desc + 5) == 0x64656e776f5f6565) {
            tag = 0x78;                    /* '@calllee_' -> 'x' */
            cL4_mr_emit_char(ctx + 0x2140, &tag, slot);
            err = 0; kind = 0; desc = 0;
            goto done;
        }
    } else if (len == 0x12) {
        if ((*desc == 0x5f65656c6c616340 && desc[1] == 0x65746e6172617567) &&
            (short)desc[2] == 0x6465) {   /* '@calllee_guarantee' -> 'g' */
            tag = 0x67;
            cL4_mr_emit_char(ctx + 0x2140, &tag, slot);
            err = 0; kind = 0; desc = 0;
            goto done;
        }
    } else if (len == 0xf) {
        if (*desc == 0x5f65656c6c616340 && *(long *)((char *)desc + 7) == 0x64656e776f6e755f) {
            tag = 0x79;                   /* '@calllee_unowned' -> 'y' */
            cL4_mr_emit_char(ctx + 0x2140, &tag, slot);
            err = 0; kind = 0; desc = 0;
            goto done;
        }
    }
    err = 0x792; kind = 0xf;
done:
    *out = kind;
    *(long *)(out + 2) = (long)desc;
    out[4] = err;
}

/* FUN_003c7fa8 @ 0x003c7fa8   (est. cL4_mr_kind3_dispatch)
 * Ghidra: void FUN_003c7fa8(undefined4 *param_1,long param_2,long *param_3)
 * For a kind-3 descriptor: if desc[1]==0 accept empty; if desc[1]==0xd and the
 * payload matches "@noDirective..." pattern ('@noDerive' reversed "@noDerivE"?)
 * emit 'w' and accept; else error 0x7a2/kind 0x10. Non-kind-3: error 0x79a/1.
 * Confidence: medium
 */
void cL4_mr_kind3_dispatch(unsigned int *out, long ctx, long *desc)
{
    char tag;
    unsigned long slot = *(unsigned long *)(ctx + 0x2150);

    if (*(char *)((char *)desc + 0x12) == '\x03') {
        if (desc[1] == 0) {
            out[0] = 0; *(long *)(out + 2) = 0; out[4] = 0;
            return;
        } else if ((desc[1] == 0xd) &&
                (*(long *)*desc == 0x76697265446f6e40 &&
                 *(long *)(*desc + 5) == 0x6576697461766972)) { /* '@noDerivativE' */
            tag = 0x77;
            cL4_mr_emit_char(ctx + 0x2140, &tag, slot);
            out[0] = 0; *(long *)(out + 2) = 0; out[4] = 0;
        } else {
            out[4] = 0x7a2; out[0] = 0x10; *(long *)(out + 2) = (long)desc;
        }
    } else {
        out[4] = 0x79a; out[0] = 1; *(long *)(out + 2) = (long)desc;
    }
}

/* FUN_003c807c @ 0x003c807c   (est. cL4_mr_kind3_send)
 * Ghidra: void FUN_003c807c(undefined4 *param_1,long param_2,undefined8 *param_3)
 * Kind-3 descriptor: if desc[1]==7 and payload matches "@send"+"ding" pattern
 * emit 'T'; else error 0x7ae/0x14. Non-kind-3: error 0x7aa/1.
 * Confidence: medium
 */
void cL4_mr_kind3_send(unsigned int *out, long ctx, unsigned long *desc)
{
    char tag;
    unsigned long slot = *(unsigned long *)(ctx + 0x2150);

    if (*(char *)((char *)desc + 0x12) == '\x03') {
        if ((desc[1] == 7) &&
            (*(int *)*desc == 0x646e6573 && *(int *)((char *)*desc + 3) == 0x676e6964)) { /* "send"+"ding" */
            tag = 0x54;
            cL4_mr_emit_char(ctx + 0x2140, &tag, slot);
            out[0] = 0; *(long *)(out + 2) = 0; out[4] = 0;
        } else {
            out[4] = 0x7ae; out[0] = 0x14; *(long *)(out + 2) = (long)desc;
        }
    } else {
        out[4] = 0x7aa; out[0] = 1; *(long *)(out + 2) = (long)desc;
    }
}

/* FUN_003c8130 @ 0x003c8130   (est. cL4_mr_kind3_isolation)
 * Ghidra: void FUN_003c8130(undefined4 *param_1,long param_2,undefined8 *param_3)
 * Kind-3 descriptor: if desc[1]==8 and payload matches "isolation" emit 'I';
 * else error 0x7ba/0x14. Non-kind-3: error 0x7b6/1.
 * Confidence: medium
 */
void cL4_mr_kind3_isolation(unsigned int *out, long ctx, unsigned long *desc)
{
    char tag;
    unsigned long slot = *(unsigned long *)(ctx + 0x2150);

    if (*(char *)((char *)desc + 0x12) == '\x03') {
        if ((desc[1] == 8) && (*(long *)*desc == 0x646574616c6f7369)) { /* "isolation" reversed */
            tag = 0x49;
            cL4_mr_emit_char(ctx + 0x2140, &tag, slot);
            out[0] = 0; *(long *)(out + 2) = 0; out[4] = 0;
        } else {
            out[4] = 0x7ba; out[0] = 0x14; *(long *)(out + 2) = (long)desc;
        }
    } else {
        out[4] = 0x7b6; out[0] = 1; *(long *)(out + 2) = (long)desc;
    }
}

/* FUN_003c81dc @ 0x003c81dc   (est. cL4_mr_kind3_implicit)
 * Ghidra: void FUN_003c81dc(undefined4 *param_1,long param_2,undefined8 *param_3)
 * Kind-3 descriptor: if desc[1]==0x1a and payload matches "implicit_linear_parm"
 * pattern emit 'L'; else error 0x7c6/0x14. Non-kind-3: error 0x7c2/1.
 * Confidence: medium
 */
void cL4_mr_kind3_implicit(unsigned int *out, long ctx, unsigned long *desc)
{
    char tag;
    long *p;
    unsigned long slot = *(unsigned long *)(ctx + 0x2150);

    if (*(char *)((char *)desc + 0x12) == '\x03') {
        if ((desc[1] == 0x1a) &&
            (p = (long *)*desc,
             ((*p == 0x6c706d695f6c6973 && p[1] == 0x61656c5f74696369) &&
              p[2] == 0x7261705f676e6964) && (short)p[3] == 0x6d61)) { /* "implicit_linear_parm" */
            tag = 0x4c;
            cL4_mr_emit_char(ctx + 0x2140, &tag, slot);
            out[0] = 0; *(long *)(out + 2) = 0; out[4] = 0;
        } else {
            out[4] = 0x7c6; out[0] = 0x14; *(long *)(out + 2) = (long)desc;
        }
    } else {
        out[4] = 0x7c2; out[0] = 1; *(long *)(out + 2) = (long)desc;
    }
}

/* FUN_003c82c0 @ 0x003c82c0   (est. cL4_mr_object_metadata)
 * Ghidra: void FUN_003c82c0(undefined4 *param_1,long param_2,long *param_3)
 * Classifies a message object by its payload type-name and emits the matching
 * single-byte type tag (C/B/M/K/O/W etc.). Recognizes: "c" (1), "bloc"+"k"
 * (5), "meth"+"od" (6), "clos"+"ure" (7), "objc_met"+"hod_s" (11), "twen?" (14),
 * and a 0x18-shaped object. On a match it emits the tag char (and 'z' first for
 * the 0x18 shape), then marshals the object's second word via cL4_mr_tail.
 * On mismatch sets error 0x7e0 with kind 1.
 * Confidence: medium
 */
void cL4_mr_object_metadata(unsigned int *out, long ctx, long *desc)
{
    long *inner, *p;
    long len;
    unsigned char kind, tag;
    unsigned char tag2;
    unsigned long slot = *(unsigned long *)(ctx + 0x2150);

    kind = cL4_mr_kind((unsigned long *)desc);
    if (1 < kind - 1) {
        if ((kind != 5) || ((int)desc[1] == 0)) goto mismatch;
        inner = (long *)*desc;
    } else {
        inner = desc;
    }
    if (*(char *)((char *)*inner + 0x12) != '\x03') goto mismatch;
    inner = desc;
    if (1 < kind - 1) {
        inner = (long *)*desc;
    }
    p = *(long **)*inner;
    len = ((long *)*inner)[1];
    if (6 < len) {
        if (len == 7) {
            if ((int)*p == 0x736f6c63 && *(int *)((char *)p + 3) == 0x65727573) { /* "clos"+"ure" */
                tag = 0x4b;                    /* 'K' */
                goto emit_tag;
            }
        } else {
            if (len != 0xb) {
                if ((len != 0xe) ||
                    (*p != 0x5f7373656e746977 || *(long *)((char *)p + 6) != 0x646f6874656d5f73)) /* "twitness_s..." */
                    goto mismatch;
                tag = 0x57;                    /* 'W' */
                goto emit_tag;
            }
            if (*p == 0x74656d5f636a626f && *(long *)((char *)p + 3) == 0x646f6874656d5f63) { /* "objc_met"+"hod_c" */
                tag = 0x4f;                    /* 'O' */
                goto emit_tag;
            }
        }
        goto mismatch;
    }
    if (len == 1) {
        if ((char)*p != 'c') goto mismatch;
        tag = 0x43;                           /* 'C' */
    } else {
        if (len != 5) {
            if ((len == 6) && ((int)*p == 0x6874656d && *(short *)((char *)p + 4) == 0x646f)) { /* "meth"+"od" */
                tag = 0x4d;                   /* 'M' */
                goto emit_tag;
            }
            goto mismatch;
        }
        if ((int)*p != 0x636f6c62 || *(char *)((char *)p + 4) != 'k') goto mismatch; /* "bloc"+"k" */
        tag = 0x42;                           /* 'B' */
    }
    inner = desc;
    if (kind != 2) {
        if ((kind != 5) || (*(unsigned int *)(desc + 1) < 2)) goto emit_tag;
        inner = (long *)*desc;
    }
    if (*(short *)(inner[1] + 0x10) != 0x18) {
        goto emit_tag;
    }
    tag2 = 0x7a;                              /* 'z' */
    cL4_mr_emit_char(ctx + 0x2140, &tag2, slot);
    goto emit_char_tag;
emit_tag:
    cL4_mr_emit_char(ctx + 0x2140, &tag, slot);
emit_char_tag:
    if (cL4_mr_kind((unsigned long *)desc) != 2) {
        if ((cL4_mr_kind((unsigned long *)desc) != 5) || (*(unsigned int *)(desc + 1) < 2)) {
            len = 0;
            goto marshal_tail;
        }
        desc = (long *)*desc;
    }
    len = desc[1];
marshal_tail:
    cL4_mr_tail((unsigned long)out, ctx, len);
    return;
mismatch:
    *out = 1;
    *(long *)(out + 2) = (long)desc;
    out[4] = 0x7e0;
}

/* FUN_003c856c @ 0x003c856c   (est. cL4_mr_object_dispatch)
 * Ghidra: void FUN_003c856c(int *param_1,long param_2,undefined8 *param_3,int param_4)
 *   WARNING: Type propagation algorithm not settling
 * The central message-object dispatcher. Walks the descriptor's word span and,
 * for each element, dispatches on its 16-bit type tag (at word+0x10) to the
 * appropriate per-type marshaller, emitting the correct type tag byte and
 * recursively marshalling nested objects (cL4_mr_rec/cL4_mr_val). Handles the
 * compact descriptor formats (kind 1/2 single/two-word, kind 5 array) and the
 * @calllee_/@convention(...)/etc. function metadata forms. On failure sets
 * out[0]/out[2]/out[4] and returns. Compiler warning reflects the large
 * switch that the decompiler could not fully settle.
 * Confidence: medium
 */
void cL4_mr_object_dispatch(int *out, long ctx, unsigned long *desc, int depth)
{
    /* Faithful translation of FUN_003c856c. The Ghidra decompiler emitted
     * "WARNING: Type propagation algorithm not settling" for this function;
     * the goto structure below mirrors the decompile exactly. */
    long *e1, *e2, *tmp;
    long e3;
    unsigned char kind;
    unsigned short etag;
    long *e6, *e8;
    const unsigned char *ustr;
    long *e18, *e20, *e21, *e22;
    bool flag9, flag16;
    int err10;
    unsigned long u11;
    long r12;
    unsigned int u13;
    unsigned long *span14;
    unsigned long u15, u17;
    unsigned char c61;
    long *local70;

    kind = cL4_mr_kind(desc);
    span14 = desc;
    if (kind - 1 < 2) {
        if (kind == 1)      span14 = desc + 1;
        else if (kind == 2) span14 = desc + 2;
        else if (kind == 5) { span14 = (unsigned long *)*desc; goto set_end; }
        else                span14 = 0;
    } else {
        if (kind != 5) { e22 = 0; goto set_end2; }
        span14 = (unsigned long *)*desc;
        e22 = (long *)span14;
    }
set_end2:
    if (kind - 1 < 2) {
        if (kind == 5) { span14 = (unsigned long *)*desc; }
    }
set_end:
    span14 = span14 + *(unsigned int *)(desc + 1);
    if (e22 == (long *)span14) {
        ustr = (const unsigned char *)0;   /* empty tag (&DAT_005be7c0) */
        flag16 = true;
        flag9 = true;
    } else {
        e20 = 0; local70 = 0; e21 = 0;
        ustr = (const unsigned char *)0;
        do {
            e18 = (long *)*e22;
            etag = *(unsigned short *)(e18 + 2);
            u13 = (unsigned int)etag;
            e8 = local70;
            if (etag < 0x7b) {
                e1 = e18;
                if (etag != 0x79) e1 = e21;
                e2 = e21;
                e6 = e18;
                tmp = (long *)0x5c9984;
                if (u13 != 0x2f) { e2 = e1; e6 = e20; tmp = (long *)ustr; }
                e20 = e18;
                if (u13 != 0x2c) { ustr = (const unsigned char *)tmp; e20 = e6; e21 = e2; }
            }
            else if ((u13 - 0x7d < 3) ||
                    ((e8 = e18, u13 != 0x7c && (e8 = local70, etag == 0x7b)))) {
                r12 = 1;
                if (*(char *)((char *)e18 + 0x12) != '\x02') {
                    if (*(char *)((char *)e18 + 0x12) != '\x05') { err10 = 0x813; goto result; }
                    if (*(unsigned int *)(e18 + 1) < 2) { err10 = 0x813; r12 = 1; goto result; }
                    r12 = (unsigned long)*(unsigned int *)(e18 + 1) - 1;
                    e18 = (long *)*e18;
                }
                cL4_mr_rec((unsigned long)out, ctx, e18[r12], (unsigned long)(depth + 1));
                e8 = local70;
                if (*out != 0) return;
            }
            local70 = e8;
            e22 = e22 + 1;
        } while (e22 != (long *)span14);
        if ((e20 != 0) && (cL4_mr_rec((unsigned long)out, ctx, (unsigned long)e20, (unsigned long)(depth + 1)), *out != 0)) return;
        flag9 = e21 == 0;
        if (e21 != 0) {
            c61 = 0x79;                        /* 'y' */
            cL4_mr_emit_char(ctx + 0x2140, &c61, *(unsigned long *)(ctx + 0x2150));
            e20 = e21;
            if (cL4_mr_kind((unsigned long *)e21) - 1 < 2) {
                r12 = *e20;
            } else {
                if ((cL4_mr_kind((unsigned long *)e21) == 5) && ((int)e21[1] != 0)) { e20 = (long *)*e21; r12 = *e20; }
                else r12 = 0;
            }
            cL4_mr_wrap2((unsigned long)out, ctx, (unsigned long)r12, (unsigned long)(depth + 1));
            if (*out != 0) return;
            if (*(char *)((char *)e21 + 0x12) != '\x02') {
                if ((*(char *)((char *)e21 + 0x12) != '\x05') || (*(unsigned int *)(e21 + 1) < 2)) goto after_e21;
                e21 = (long *)*e21;
            }
            cL4_mr_cba04(out, ctx, (long *)e21[1], (unsigned long)(depth + 1));
            if (*out != 0) return;
        }
after_e21:
        if (local70 == 0) {
            flag16 = true;
        } else {
            e20 = local70;
            if (cL4_mr_kind((unsigned long *)local70) - 1 < 2) {
                r12 = *e20;
            } else {
                if ((cL4_mr_kind((unsigned long *)local70) == 5) && ((int)local70[1] != 0)) { e20 = (long *)*local70; r12 = *e20; }
                else r12 = 0;
            }
            cL4_mr_rec((unsigned long)out, ctx, (unsigned long)r12, (unsigned long)(depth + 1));
            if (*out != 0) return;
            c61 = 0x79;                        /* 'y' */
            cL4_mr_emit_char(ctx + 0x2140, &c61, *(unsigned long *)(ctx + 0x2150));
            e20 = local70;
            if (*(char *)((char *)local70 + 0x12) == '\x02') {
                r12 = e20[1];
            } else {
                if ((*(char *)((char *)local70 + 0x12) == '\x05') && (1 < *(unsigned int *)(local70 + 1))) { e20 = (long *)*local70; r12 = e20[1]; }
                else r12 = 0;
            }
            cL4_mr_wrap2((unsigned long)out, ctx, (unsigned long)r12, (unsigned long)(depth + 1));
            if (*out != 0) return;
            if ((*(char *)((char *)local70 + 0x12) == '\x05') && (2 < *(unsigned int *)(local70 + 1))) {
                r12 = *(long *)(*local70 + 0x10);
                if (*(short *)(r12 + 0x10) == 0xf7) cL4_mr_wrap2((unsigned long)out, ctx, (unsigned long)r12, (unsigned long)(depth + 1));
                else cL4_mr_cba04(out, ctx, (long *)r12, (unsigned long)(depth + 1));
                if (*out != 0) return;
            }
            flag16 = false;
        }
    }
    c61 = 0x49;                                /* 'I' */
    cL4_mr_emit_char(ctx + 0x2140, &c61, *(unsigned long *)(ctx + 0x2150));
    if (flag16) {
        if (!flag9) goto emit_twice;
        /* fall through: emit ustr */
        if (ustr == 0) goto emit_zero;
        u11 = cL4_strlen((const char *)ustr);
    } else {
        c61 = 0x73;                            /* 's' */
        cL4_mr_emit_char(ctx + 0x2140, &c61, *(unsigned long *)(ctx + 0x2150));
        if (flag9) { if (ustr == 0) goto emit_zero; u11 = cL4_strlen((const char *)ustr); goto emit_str; }
emit_twice:
        c61 = 0x49;                            /* 'I' */
        cL4_mr_emit_char(ctx + 0x2140, &c61, *(unsigned long *)(ctx + 0x2150));
        if (ustr != 0) { u11 = cL4_strlen((const char *)ustr); goto emit_str; }
emit_zero:
        u11 = 0;
    }
emit_str:
    cL4_mr_emit(ctx + 0x2140, ustr, u11, *(unsigned long *)(ctx + 0x2150));

    /* second pass: re-walk the span and dispatch on each element's 16-bit tag */
    kind = cL4_mr_kind(desc);
    span14 = desc;
    if (kind - 1 < 2) {
        if (kind == 1)      { span14 = desc + 1; goto loop_setup; }
        if (kind == 2)      { span14 = desc + 2; goto loop_setup; }
        if (kind != 5)      { span14 = 0; goto loop_setup; }
        span14 = (unsigned long *)*desc;
    } else {
        if (kind != 5) { e22 = 0; goto loop_setup2; }
        span14 = (unsigned long *)*desc;
        e22 = (long *)span14;
    }
loop_setup2:
    span14 = span14 + *(unsigned int *)(desc + 1);
loop_setup:
    for (; e22 != (long *)span14; e22 = e22 + 1) {
        e18 = (long *)*e22;
        if (0x14 < *(unsigned short *)(e18 + 2) - 0x6b) goto loop_continue;
        switch (*(unsigned short *)(e18 + 2)) {
        default: c61 = 0x65; break;            /* 'e' */
        case 0x6c:
            e20 = (long *)*e18;
            e3 = e18[1];
            err10 = 0x85e;
            r12 = 0xf;
            if (e3 < 0x11) {
                if (e3 == 0xd) {
                    if (*e20 != 0x5f65656c6c616340 || *(long *)((char *)e20 + 5) != 0x64656e776f5f6565) goto case6c_miss;
                    c61 = 0x78;                /* 'x' */
                } else {
                    if (e3 != 0xf) goto result;
                    if (*e20 != 0x5f65656c6c616340 || *(long *)((char *)e20 + 7) != 0x64656e776f6e755f) {
case6c_miss:
                        err10 = 0x85e; r12 = 0xf; goto result;
                    }
                    c61 = 0x79;                /* 'y' */
                }
            }
            else if (e3 == 0x11) {
                if ((*e20 != 0x746e65766e6f6340 || e20[1] != 0x6e696874286e6f69) || (char)e20[2] != ')') goto case6c_miss;
                c61 = 0x74;                    /* 't' */
            }
            else {
                if (e3 != 0x12) goto result;
                if ((*e20 != 0x5f65656c6c616340 || e20[1] != 0x65746e6172617567) || (short)e20[2] != 0x6465) goto case6c_miss;
                c61 = 0x67;                    /* 'g' */
            }
            break;
        case 0x6d:
            c61 = (unsigned char)*e18;
            break;
        case 0x6e:
            c61 = 0x41;                        /* 'A' */
            break;
        case 0x6f:
            c61 = 0x54;                        /* 'T' */
            break;
        case 0x70: case 0x71: case 0x72: case 0x73:
        case 0x76: case 0x77: case 0x79: case 0x7a: case 0x7c:
            goto loop_continue;
        case 0x74:
            e20 = (long *)*e18;
            if (e18[1] == 6) {
                if ((int)*e20 != 0x79736140 || *(short *)((char *)e20 + 4) != 0x636e) goto case74_miss;
                c61 = 0x48;                    /* 'H' */
            } else {
                if ((e18[1] != 9) || (*e20 != 0x6c6261646e655340 || (char)e20[1] != 'e')) {
case74_miss:
                    err10 = 0x87b; r12 = 0x12; goto result;
                }
                c61 = 0x68;                    /* 'h' */
            }
            break;
        case 0x75:
            cL4_mr_object_metadata((unsigned int *)out, ctx, e18);
            goto post_field;
        case 0x78:
            e20 = (long *)*e18;
            if (e18[1] == 0xc) {
                if (*e20 == 0x6e6f5f646c656979 && (int)e20[1] == 0x325f6563) {
                    c61 = 0x49;                /* 'I' */
                    break;
                }
            }
            else if (e18[1] == 10) {
                if (*e20 == 0x6e6f5f646c656979 && (short)e20[1] == 0x6563) { c61 = 0x41; break; }
                if (*e20 == 0x616d5f646c656979 && (short)e20[1] == 0x796e) { c61 = 0x47; break; }
            }
            err10 = 0x86f; r12 = 0x11; goto result;
        case 0x7b: goto case7b;
        case 0x7d: goto case7d;
        case 0x7e:
            c61 = 0x59;                        /* 'Y' */
            cL4_mr_emit_char(ctx + 0x2140, &c61, *(unsigned long *)(ctx + 0x2150));
            goto case7b;
        case 0x7f:
            c61 = 0x7a;                        /* 'z' */
            cL4_mr_emit_char(ctx + 0x2140, &c61, *(unsigned long *)(ctx + 0x2150));
            goto case7d;
        }
        cL4_mr_emit_char(ctx + 0x2140, &c61, *(unsigned long *)(ctx + 0x2150));
        goto loop_continue;

    case7b:
        kind = cL4_mr_kind((unsigned long *)e18);
        u13 = kind - 1;
        e20 = e18;
        if (1 < u13) e20 = (long *)*e18;
        e21 = *(long **)*e20;
        r12 = ((long *)*e20)[1];
        if (r12 < 0xc) {
            if (r12 == 3) {
                if ((short)*e21 == 0x6940 && *(char *)((char *)e21 + 2) == 'n') { c61 = 0x69; goto emit7b; }
            }
            else if (r12 == 6) {
                if ((int)*e21 == 0x6f6e6940 && *(short *)((char *)e21 + 4) == 0x7475) { c61 = 0x6c; goto emit7b; }
                err10 = cL4_strcmp((const char *)e21, "@owned");
                if (err10 == 0) { c61 = 0x78; goto emit7b; }
            }
            else if (r12 == 7) {
                if ((int)*e21 == 0x5f6e6940 && *(int *)((char *)e21 + 3) == 0x7878635f) { c61 = 0x58; goto emit7b; }
            }
            else {
                if (r12 == 0xb) {
                    if (*e21 == 0x746e617261756740 && *(long *)((char *)e21 + 3) == 0x646565746e617261) { c61 = 0x67; goto emit7b; }
                    if (*e21 == 0x776f5f6b63617040 && *(long *)((char *)e21 + 3) == 0x64656e776f5f6b63) { c61 = 0x76; goto emit7b_loop; }
                    err10 = cL4_strcmp((const char *)e21, "@pack_inout");
                    if (err10 == 0) { c61 = 0x6d; goto emit7b; }
                }
                else if (r12 == 8) {
                    if (*e21 == 0x64656e776f6e7540) { c61 = 0x79; goto emit7b; }
                }
                else {
                    if (r12 == 0x10) goto pack_guaranteed;
                    if (r12 != 0xd) goto pack_inout;
                    if (*e21 == 0x636f6c6c61656440 && *(long *)((char *)e21 + 5) == 0x676e697461636f6c) { c61 = 0x65; goto emit7b; }
                }
            }
            goto pack_inout;
        }
        else if (r12 == 0xc) {
            if (*e21 == 0x736e6f635f6e6940 && (int)e21[1] == 0x746e6174) { c61 = 99; goto emit7b; }
        }
        else if (r12 == 0xe) {
            if (*e21 == 0x726175675f6e6940 && *(long *)((char *)e21 + 6) == 0x646565746e617261) { c61 = 0x6e; goto emit7b; }
        }
        else {
            if (r12 != 0x10) goto pack_inout;
            if (*e21 == 0x615f74756f6e6940 && e21[1] == 0x656c62617361696c) { c61 = 0x62; goto emit7b; }
pack_guaranteed:
            err10 = cL4_strcmp((const char *)e21, "@pack_guaranteed");
            if (err10 == 0) { c61 = 0x70; goto emit7b; }
        }
    pack_inout:
        if (u13 < 2) {
            e18 = (long *)*e18;
        } else {
            if ((kind == 5) && ((int)e18[1] != 0)) { e18 = (long *)*e18; }
            else e18 = 0;
        }
        err10 = 0x897;
        r12 = 0x13;
        goto result;
    emit7b_loop:
        cL4_mr_emit_char(ctx + 0x2140, &c61, *(unsigned long *)(ctx + 0x2150));
        u17 = 1;
        do {
            if (cL4_mr_kind((unsigned long *)e18) == 5) u15 = (unsigned long)*(unsigned int *)(e18 + 1) - 1;
            else {
                if (cL4_mr_kind((unsigned long *)e18) - 1 < 2) goto loop_continue;
                u15 = 0xffffffffffffffffUL;
            }
            if (u15 <= u17) goto loop_continue;
            etag = *(unsigned short *)(*(long *)(*e18 + u17 * 8) + 0x10);
            if (etag < 0x72) {
                if (etag == 0x70) cL4_mr_kind3_dispatch((unsigned int *)out, ctx, 0); /* decompiler dropped desc arg */
                else {
                    if (etag != 0x71) { cL4_mr_4ba510((long)e18); cL4_mr_116d60(); }
                    cL4_mr_kind3_send((unsigned int *)out, ctx, 0); /* decompiler dropped desc arg */
                }
            }
            else if (etag == 0x72) cL4_mr_kind3_isolation((unsigned int *)out, ctx, 0); /* decompiler dropped desc arg */
            else {
                if (etag != 0x73) { cL4_mr_4ba510((long)e18); cL4_mr_116d60(); }
                cL4_mr_kind3_implicit((unsigned int *)out, ctx, 0); /* decompiler dropped desc arg */
            }
            if (*out != 0) return;
            u17 = u17 + 1;
        } while (1);
    emit7b:
        cL4_mr_emit_char(ctx + 0x2140, &c61, *(unsigned long *)(ctx + 0x2150));
        goto loop_continue;

    case7d:
        kind = cL4_mr_kind((unsigned long *)e18);
        u13 = kind - 1;
        e20 = e18;
        if (1 < u13) e20 = (long *)*e18;
        e21 = *(long **)*e20;
        r12 = ((long *)*e20)[1];
        if (10 < r12) {
            if (r12 < 0x13) {
                if (r12 == 0xb) {
                    if (*e21 != 0x746e617261756740 || *(long *)((char *)e21 + 3) != 0x646565746e617261) goto case7d_miss;
                    c61 = 0x67;                /* 'g' */
                } else {
                    if ((r12 != 0xd) || (*e21 != 0x6c65726f74756140 || *(long *)((char *)e21 + 5) != 0x64657361656c6572)) goto case7d_miss;
                    c61 = 0x61;                /* 'a' */
                }
            }
            else if (r12 == 0x13) {
                if ((*e21 != 0x746e617261756740 || e21[1] != 0x726464615f646565) || *(long *)((char *)e21 + 0xb) != 0x737365726464615f) goto case7d_miss;
                c61 = 0x6c;                    /* 'l' */
            }
            else {
                if ((r12 != 0x16) || ((*e21 != 0x64656e776f6e7540 || e21[1] != 0x705f72656e6e695f) || *(long *)((char *)e21 + 0xe) != 0x7265746e696f705f)) goto case7d_miss;
                c61 = 0x75;                    /* 'u' */
            }
            goto case7d_emit;
        }
        if (r12 < 8) {
            if (r12 == 4) {
                if ((int)*e21 == 0x74756f40) { c61 = 0x72; goto case7d_emit; }
            }
            else if (r12 == 6) {
                if ((int)*e21 == 0x6e776f40 && *(short *)((char *)e21 + 4) == 0x6465) c61 = 0x6f;
                else {
                    err10 = cL4_strcmp((const char *)e21, "@inout");
                    if (err10 != 0) goto case7d_miss;
                    c61 = 0x6d;
                }
                goto case7d_emit;
            }
            goto case7d_miss;
        }
        if (r12 == 8) {
            if (*e21 != 0x64656e776f6e7540) goto case7d_miss;
            c61 = 100;                         /* 'd' */
        } else {
            if ((r12 != 9) || (*e21 != 0x756f5f6b63617040 || (char)e21[1] != 't')) goto case7d_miss;
            c61 = 0x6b;                        /* 'k' */
        }
    case7d_emit:
        cL4_mr_emit_char(ctx + 0x2140, &c61, *(unsigned long *)(ctx + 0x2150));
        if (*(char *)((char *)e18 + 0x12) == '\x05') {
            if ((int)e18[1] == 4) {
                cL4_mr_kind3_dispatch((unsigned int *)out, ctx, (long *)*(unsigned long *)(*e18 + 8));
                if (*out != 0) return;
                if ((*(char *)((char *)e18 + 0x12) == '\x05') && (2 < *(unsigned int *)(e18 + 1))) u11 = *(unsigned long *)(*e18 + 0x10);
                else u11 = 0;
                cL4_mr_kind3_send((unsigned int *)out, ctx, (unsigned long *)u11);
            } else {
                if ((int)e18[1] != 3) goto loop_continue;
                cL4_mr_kind3_dispatch((unsigned int *)out, ctx, (long *)*(unsigned long *)(*e18 + 8));
            }
        post_field:
            if (*out != 0) return;
        }
        goto loop_continue;
    case7d_miss:
        if (u13 < 2) {
            e18 = (long *)*e18;
        } else {
            if ((kind == 5) && ((int)e18[1] != 0)) { e18 = (long *)*e18; }
            else e18 = 0;
        }
        err10 = 0x8c9;
        r12 = 0x13;
        goto result;
loop_continue:
        ;
    }
    c61 = 0x5f;                                /* '_' */
    cL4_mr_emit_char(ctx + 0x2140, &c61, *(unsigned long *)(ctx + 0x2150));
    r12 = 0; e18 = 0; err10 = 0;
result:
    *out = (int)r12;
    *(long *)(out + 2) = (long)e18;
    out[4] = err10;
}

/* FUN_003c949c @ 0x003c949c   (est. cL4_mr_op_fu)
 * Ghidra: void FUN_003c949c(int *param_1,long param_2,undefined8 param_3,int param_4)
 * Marshals MR words 0 and 2 via cL4_mr_op, emits "fu", then marshals word 1.
 * Confidence: medium
 */
void cL4_mr_op_fu(int *out, long ctx, unsigned long desc, int depth)
{
    cL4_mr_op(ctx, desc, 0, (unsigned long)(depth + 1));
    if ((*out == 0) && (cL4_mr_op((unsigned long)out, ctx, desc, 2, (unsigned long)(depth + 1)), *out == 0)) {
        cL4_mr_emit(ctx + 0x2140, "fu", 2, *(unsigned long *)(ctx + 0x2150));
        cL4_mr_op((unsigned long)out, ctx, desc, 1, (unsigned long)(depth + 1));
    }
}

/* FUN_003c9548 @ 0x003c9548   (est. cL4_mr_char_z)
 * Ghidra: void FUN_003c9548(int *param_1,long param_2,undefined8 param_3,int param_4)
 * Marshals a word, then emits the single tag byte 'z'. Clears result.
 * Confidence: medium
 */
void cL4_mr_char_z(int *out, long ctx, unsigned long desc, int depth)
{
    char tag = 0x7a;
    cL4_mr_wrap1(ctx, desc, (unsigned long)(depth + 1));
    if (*out == 0) {
        cL4_mr_emit_char(ctx + 0x2140, &tag, *(unsigned long *)(ctx + 0x2150));
        *out = 0; out[2] = 0; out[3] = 0; out[4] = 0;
    }
}

/* FUN_003c95ac @ 0x003c95ac   (est. cL4_mr_init_oi)
 * Ghidra: void FUN_003c95ac(undefined4 *param_1,long param_2,undefined8 param_3)
 * Initializes a message slot (cL4_mr_init) and emits tag "oi". Clears result.
 * Confidence: medium
 */
void cL4_mr_init_oi(unsigned int *out, long ctx, unsigned long desc)
{
    cL4_mr_init(ctx, desc, 1);
    cL4_mr_emit(ctx + 0x2140, "oi", 2, *(unsigned long *)(ctx + 0x2150));
    *out = 0; *(unsigned long *)(out + 2) = 0; out[4] = 0;
}

/* FUN_003c9600 @ 0x003c9600   (est. cL4_mr_op_fi)
 * Ghidra: void FUN_003c9600(int *param_1,long param_2,undefined8 param_3,int param_4)
 * Marshals a word then emits tag "fi". Clears result.
 * Confidence: medium
 */
void cL4_mr_op_fi(int *out, long ctx, unsigned long desc, int depth)
{
    cL4_mr_wrap2(ctx, desc, (unsigned long)(depth + 1));
    if (*out == 0) {
        cL4_mr_emit(ctx + 0x2140, "fi", 2, *(unsigned long *)(ctx + 0x2150));
        *out = 0; out[2] = 0; out[3] = 0; out[4] = 0;
    }
}

/* FUN_003c965c @ 0x003c965c   (est. cL4_mr_dispatch_i)
 * Ghidra: void FUN_003c965c(undefined8 param_1,long *param_2,int param_3)
 * Resolves descriptor payload word and marshals it with tag 'i' (DAT_005d6fcb).
 * Confidence: medium
 */
void cL4_mr_dispatch_i(unsigned long out, long *desc, int depth)
{
    unsigned long val;
    if (1 < cL4_mr_kind((unsigned long *)desc) - 1) {
        if ((cL4_mr_kind((unsigned long *)desc) != 5) || ((int)desc[1] == 0)) {
            val = 0;
        } else {
            desc = (long *)*desc;
            val = *desc;
        }
    } else {
        val = *desc;
    }
    cL4_mr_tag(out, val, "i", 1, (unsigned long)(depth + 1));
}

/* FUN_003c96a4 @ 0x003c96a4   (est. cL4_mr_emit_Yi)
 * Ghidra: void FUN_003c96a4(int *param_1,long param_2,undefined8 param_3,int param_4)
 * Marshals a word then emits tag "Yi". Clears result.
 * Confidence: medium
 */
void cL4_mr_emit_Yi(int *out, long ctx, unsigned long desc, int depth)
{
    cL4_mr_wrap1(ctx, desc, (unsigned long)(depth + 1));
    if (*out == 0) {
        cL4_mr_emit(ctx + 0x2140, "Yi", 2, *(unsigned long *)(ctx + 0x2150));
        *out = 0; out[2] = 0; out[3] = 0; out[4] = 0;
    }
}

/* FUN_003c9700 @ 0x003c9700   (est. cL4_mr_op_fZ)
 * Ghidra: void FUN_003c9700(int *param_1,long param_2,undefined8 param_3,int param_4)
 * Marshals a word then emits tag "fZ". Clears result.
 * Confidence: medium
 */
void cL4_mr_op_fZ(int *out, long ctx, unsigned long desc, int depth)
{
    cL4_mr_wrap2(ctx, desc, (unsigned long)(depth + 1));
    if (*out == 0) {
        cL4_mr_emit(ctx + 0x2140, "fZ", 2, *(unsigned long *)(ctx + 0x2150));
        *out = 0; out[2] = 0; out[3] = 0; out[4] = 0;
    }
}

/* FUN_003c975c @ 0x003c975c   (est. cL4_mr_emit_Yu)
 * Ghidra: void FUN_003c975c(int *param_1,long param_2,undefined8 param_3,int param_4)
 * Marshals a word then emits tag "Yu". Clears result.
 * Confidence: medium
 */
void cL4_mr_emit_Yu(int *out, long ctx, unsigned long desc, int depth)
{
    cL4_mr_wrap1(ctx, desc, (unsigned long)(depth + 1));
    if (*out == 0) {
        cL4_mr_emit(ctx + 0x2140, "Yu", 2, *(unsigned long *)(ctx + 0x2150));
        *out = 0; out[2] = 0; out[3] = 0; out[4] = 0;
    }
}

/* FUN_003c97b8 @ 0x003c97b8   (est. cL4_mr_op_Wl)
 * Ghidra: void FUN_003c97b8(int *param_1,long param_2,undefined8 param_3,int param_4)
 * Marshals a word then emits tag "Wl". Clears result.
 * Confidence: medium
 */
void cL4_mr_op_Wl(int *out, long ctx, unsigned long desc, int depth)
{
    cL4_mr_wrap2(ctx, desc, (unsigned long)(depth + 1));
    if (*out == 0) {
        cL4_mr_emit(ctx + 0x2140, "Wl", 2, *(unsigned long *)(ctx + 0x2150));
        *out = 0; out[2] = 0; out[3] = 0; out[4] = 0;
    }
}

/* FUN_003c9814 @ 0x003c9814   (est. cL4_mr_op_WL)
 * Ghidra: void FUN_003c9814(int *param_1,long param_2,undefined8 param_3,int param_4)
 * Marshals a word then emits tag "WL". Clears result.
 * Confidence: medium
 */
void cL4_mr_op_WL(int *out, long ctx, unsigned long desc, int depth)
{
    cL4_mr_wrap2(ctx, desc, (unsigned long)(depth + 1));
    if (*out == 0) {
        cL4_mr_emit(ctx + 0x2140, "WL", 2, *(unsigned long *)(ctx + 0x2150));
        *out = 0; out[2] = 0; out[3] = 0; out[4] = 0;
    }
}

/* FUN_003c9870 @ 0x003c9870   (est. cL4_mr_op_L)
 * Ghidra: void FUN_003c9870(int *param_1,long param_2,undefined8 param_3,int param_4)
 * Marshals MR word 1, emits 'L', then marshals word 0.
 * Confidence: medium
 */
void cL4_mr_op_L(int *out, long ctx, unsigned long desc, int depth)
{
    char tag = 0x4c;
    cL4_mr_op(ctx, desc, 1, (unsigned long)(depth + 1));
    if (*out == 0) {
        cL4_mr_emit_char(ctx + 0x2140, &tag, *(unsigned long *)(ctx + 0x2150));
        cL4_mr_op((unsigned long)out, ctx, desc, 0, (unsigned long)(depth + 1));
    }
}

/* FUN_003c98f4 @ 0x003c98f4   (est. cL4_mr_op_fm)
 * Ghidra: void FUN_003c98f4(int *param_1,long param_2,undefined8 param_3,int param_4)
 * Marshals a word then emits tag "fm". Clears result.
 * Confidence: medium
 */
void cL4_mr_op_fm(int *out, long ctx, unsigned long desc, int depth)
{
    cL4_mr_wrap2(ctx, desc, (unsigned long)(depth + 1));
    if (*out == 0) {
        cL4_mr_emit(ctx + 0x2140, "fm", 2, *(unsigned long *)(ctx + 0x2150));
        *out = 0; out[2] = 0; out[3] = 0; out[4] = 0;
    }
}

/* FUN_003c9950 @ 0x003c9950   (est. cL4_mr_op_fMX)
 * Ghidra: void FUN_003c9950(int *param_1,long param_2,long *param_3,int param_4)
 * Marshals MR words 0 and 1, then reads two pointer fields out of the
 * descriptor payload (*desc at +0x10 and +0x18), emits tag "fMX", and marshals
 * both as 64-bit values. Clears result.
 * Confidence: medium
 */
void cL4_mr_op_fMX(int *out, long ctx, long *desc, int depth)
{
    unsigned long a, b;
    cL4_mr_op(ctx, desc, 0, (unsigned long)(depth + 1));
    if ((*out == 0) && (cL4_mr_op((unsigned long)out, ctx, desc, 1, (unsigned long)(depth + 1)), *out == 0)) {
        a = **(unsigned long **)(*desc + 0x10);
        b = **(unsigned long **)(*desc + 0x18);
        cL4_mr_emit(ctx + 0x2140, "fMX", 3, *(unsigned long *)(ctx + 0x2150));
        cL4_mr_emit_u64(ctx, a);
        cL4_mr_emit_u64(ctx, b);
        *out = 0; out[2] = 0; out[3] = 0; out[4] = 0;
    }
}

/* FUN_003c9a08 @ 0x003c9a08   (est. cL4_mr_op_fMu)
 * Ghidra: void FUN_003c9a08(int *param_1,long param_2,long *param_3,int param_4)
 * Marshals MR words 0 and 1; if the descriptor is a kind-5 array of >=4 and its
 * payload +0x18 is nonzero, recursively marshals that word too; emits tag
 * "fMu", then marshals MR word 2.
 * Confidence: medium
 */
void cL4_mr_op_fMu(int *out, long ctx, long *desc, int depth)
{
    cL4_mr_op(ctx, desc, 0, (unsigned long)(depth + 1));
    if (((*out == 0) &&
         ((((cL4_mr_kind((unsigned long *)desc) != 5) || (*(unsigned int *)(desc + 1) < 4)) ||
           (*(long *)(*desc + 0x18) == 0)) ||
          (cL4_mr_rec((unsigned long)out, ctx, *(long *)(*desc + 0x18), (unsigned long)(depth + 1)), *out == 0)))) {
        if ((cL4_mr_op((unsigned long)out, ctx, desc, 1, (unsigned long)(depth + 1)), *out == 0)) {
            cL4_mr_emit(ctx + 0x2140, "fMu", 3, *(unsigned long *)(ctx + 0x2150));
            cL4_mr_op((unsigned long)out, ctx, desc, 2, (unsigned long)(depth + 1));
        }
    }
}

/* FUN_003c9af0 @ 0x003c9af0   (est. cL4_mr_dispatch_e)
 * Ghidra: void FUN_003c9af0(undefined8 param_1,long *param_2,int param_3)
 * Resolves descriptor payload word and marshals it with tag 'e' (DAT_005d6c15).
 * Confidence: medium
 */
void cL4_mr_dispatch_e(unsigned long out, long *desc, int depth)
{
    unsigned long val;
    if (1 < cL4_mr_kind((unsigned long *)desc) - 1) {
        if ((cL4_mr_kind((unsigned long *)desc) != 5) || ((int)desc[1] == 0)) {
            val = 0;
        } else {
            desc = (long *)*desc;
            val = *desc;
        }
    } else {
        val = *desc;
    }
    cL4_mr_tag(out, val, "e", 1, (unsigned long)(depth + 1));
}

/* FUN_003c9b38 @ 0x003c9b38   (est. cL4_mr_op_fMm)
 * Ghidra: void FUN_003c9b38(int *param_1,long param_2,undefined8 param_3,int param_4)
 * Marshals MR words 0,1,2, emits tag "fMm", then marshals word 3.
 * Confidence: medium
 */
void cL4_mr_op_fMm(int *out, long ctx, unsigned long desc, int depth)
{
    cL4_mr_op(ctx, desc, 0, (unsigned long)(depth + 1));
    if (((*out == 0) && (cL4_mr_op((unsigned long)out, ctx, desc, 1, (unsigned long)(depth + 1)), *out == 0)) &&
        (cL4_mr_op((unsigned long)out, ctx, desc, 2, (unsigned long)(depth + 1)), *out == 0)) {
        cL4_mr_emit(ctx + 0x2140, "fMm", 3, *(unsigned long *)(ctx + 0x2150));
        cL4_mr_op((unsigned long)out, ctx, desc, 3, (unsigned long)(depth + 1));
    }
}

/* FUN_003c9c04 @ 0x003c9c04   (est. cL4_mr_op_fMr)
 * Ghidra: void FUN_003c9c04(int *param_1,long param_2,undefined8 param_3,int param_4)
 * Marshals MR words 0,1,2, emits tag "fMr", then marshals word 3.
 * Confidence: medium
 */
void cL4_mr_op_fMr(int *out, long ctx, unsigned long desc, int depth)
{
    cL4_mr_op(ctx, desc, 0, (unsigned long)(depth + 1));
    if (((*out == 0) && (cL4_mr_op((unsigned long)out, ctx, desc, 1, (unsigned long)(depth + 1)), *out == 0)) &&
        (cL4_mr_op((unsigned long)out, ctx, desc, 2, (unsigned long)(depth + 1)), *out == 0)) {
        cL4_mr_emit(ctx + 0x2140, "fMr", 3, *(unsigned long *)(ctx + 0x2150));
        cL4_mr_op((unsigned long)out, ctx, desc, 3, (unsigned long)(depth + 1));
    }
}

/* FUN_003c9cd0 @ 0x003c9cd0   (est. cL4_mr_op_XM)
 * Ghidra: void FUN_003c9cd0(int *param_1,long param_2,long *param_3,int param_4)
 * If the descriptor payload's tag (at +0x10) is 0x9b, marshals MR word 1,
 * emits "XM", marshals word 0. Otherwise marshals a word and emits 'm'.
 * Confidence: medium
 */
void cL4_mr_op_XM(int *out, long ctx, long *desc, int depth)
{
    long *inner;
    char tag = 0x6d;
    inner = desc;
    if (1 < cL4_mr_kind((unsigned long *)desc) - 1) {
        inner = (long *)*desc;
    }
    if (*(short *)(*inner + 0x10) == 0x9b) {
        cL4_mr_op((unsigned long)out, ctx, desc, 1, (unsigned long)(depth + 1));
        if (*out != 0) return;
        cL4_mr_emit(ctx + 0x2140, "XM", 2, *(unsigned long *)(ctx + 0x2150));
        cL4_mr_op((unsigned long)out, ctx, desc, 0, (unsigned long)(depth + 1));
        if (*out != 0) return;
    } else {
        cL4_mr_wrap1((unsigned long)out, ctx, (unsigned long)desc, (unsigned long)(depth + 1));
        if (*out != 0) return;
        cL4_mr_emit_char(ctx + 0x2140, &tag, *(unsigned long *)(ctx + 0x2150));
    }
    *out = 0; out[2] = 0; out[3] = 0; out[4] = 0;
}

/* FUN_003c9dd8 @ 0x003c9dd8   (est. cL4_mr_objc_metatype)
 * Ghidra: void FUN_003c9dd8(undefined4 *param_1,long param_2,long *param_3)
 * Classifies a descriptor by length against "@objc_metatype", "thick", and
 * "@thi"+"n" patterns and emits the matching tag ('o','T','t'). On mismatch
 * error 0x981 with kind 0x15.
 * Confidence: medium
 */
void cL4_mr_objc_metatype(unsigned int *out, long ctx, long *desc)
{
    int *p;
    long len;
    unsigned int err, kind;
    char tag;
    unsigned long slot = *(unsigned long *)(ctx + 0x2150);

    p = (int *)*desc;
    len = desc[1];
    if (len == 0xe) {
        if (cL4_strcmp((const char *)p, "@objc_metatype") == 0) {
            tag = 0x6f;                       /* 'o' */
            cL4_mr_emit_char(ctx + 0x2140, &tag, slot);
            err = 0; kind = 0; desc = 0;
            goto done;
        }
    } else if (len == 6) {
        if (cL4_strcmp((const char *)p, "thick") == 0) {
            tag = 0x54;                       /* 'T' */
            cL4_mr_emit_char(ctx + 0x2140, &tag, slot);
            err = 0; kind = 0; desc = 0;
            goto done;
        }
    } else if ((len == 5) && (*p == 0x69687440 && (char)p[1] == 'n')) { /* "@thi"+"n" */
        tag = 0x74;                           /* 't' */
        cL4_mr_emit_char(ctx + 0x2140, &tag, slot);
        err = 0; kind = 0; desc = 0;
        goto done;
    }
    err = 0x981; kind = 0x15;
done:
    *out = kind;
    *(long *)(out + 2) = (long)desc;
    out[4] = err;
}

/* FUN_003c9ee4 @ 0x003c9ee4   (est. cL4_mr_op_Mm)
 * Ghidra: void FUN_003c9ee4(int *param_1,long param_2,undefined8 param_3,int param_4)
 * Marshals a word then emits tag "Mm". Clears result.
 * Confidence: medium
 */
void cL4_mr_op_Mm(int *out, long ctx, unsigned long desc, int depth)
{
    cL4_mr_wrap2(ctx, desc, (unsigned long)(depth + 1));
    if (*out == 0) {
        cL4_mr_emit(ctx + 0x2140, "Mm", 2, *(unsigned long *)(ctx + 0x2150));
        *out = 0; out[2] = 0; out[3] = 0; out[4] = 0;
    }
}

/* FUN_003c9f40 @ 0x003c9f40   (est. cL4_mr_emit_Mu)
 * Ghidra: void FUN_003c9f40(int *param_1,long param_2,undefined8 param_3,int param_4)
 * Marshals a word then emits tag "Mu". Clears result.
 * Confidence: medium
 */
void cL4_mr_emit_Mu(int *out, long ctx, unsigned long desc, int depth)
{
    cL4_mr_wrap1(ctx, desc, (unsigned long)(depth + 1));
    if (*out == 0) {
        cL4_mr_emit(ctx + 0x2140, "Mu", 2, *(unsigned long *)(ctx + 0x2150));
        *out = 0; out[2] = 0; out[3] = 0; out[4] = 0;
    }
}

/* FUN_003c9f9c @ 0x003c9f9c   (est. cL4_mr_emit_MU)
 * Ghidra: void FUN_003c9f9c(int *param_1,long param_2,undefined8 param_3,int param_4)
 * Marshals a word then emits tag "MU". Clears result.
 * Confidence: medium
 */
void cL4_mr_emit_MU(int *out, long ctx, unsigned long desc, int depth)
{
    cL4_mr_wrap1(ctx, desc, (unsigned long)(depth + 1));
    if (*out == 0) {
        cL4_mr_emit(ctx + 0x2140, "MU", 2, *(unsigned long *)(ctx + 0x2150));
        *out = 0; out[2] = 0; out[3] = 0; out[4] = 0;
    }
}

/* FUN_003c9ff8 @ 0x003c9ff8   (est. cL4_mr_emit_Ms)
 * Ghidra: void FUN_003c9ff8(int *param_1,long param_2,undefined8 param_3,int param_4)
 * Marshals a word then emits tag "Ms". Clears result.
 * Confidence: medium
 */
void cL4_mr_emit_Ms(int *out, long ctx, unsigned long desc, int depth)
{
    cL4_mr_wrap1(ctx, desc, (unsigned long)(depth + 1));
    if (*out == 0) {
        cL4_mr_emit(ctx + 0x2140, "Ms", 2, *(unsigned long *)(ctx + 0x2150));
        *out = 0; out[2] = 0; out[3] = 0; out[4] = 0;
    }
}

/* FUN_003ca054 @ 0x003ca054   (est. cL4_mr_emit_Mt)
 * Ghidra: void FUN_003ca054(int *param_1,long param_2,undefined8 param_3,int param_4)
 * Marshals a word then emits tag "Mt". Clears result.
 * Confidence: medium
 */
void cL4_mr_emit_Mt(int *out, long ctx, unsigned long desc, int depth)
{
    cL4_mr_wrap1(ctx, desc, (unsigned long)(depth + 1));
    if (*out == 0) {
        cL4_mr_emit(ctx + 0x2140, "Mt", 2, *(unsigned long *)(ctx + 0x2150));
        *out = 0; out[2] = 0; out[3] = 0; out[4] = 0;
    }
}

/* FUN_003ca0b0 @ 0x003ca0b0   (est. cL4_mr_dispatch_M)
 * Ghidra: void FUN_003ca0b0(undefined8 param_1,long *param_2,int param_3)
 * Resolves descriptor payload word and marshals it with tag 'M' (DAT_005d37d0).
 * Confidence: medium
 */
void cL4_mr_dispatch_M(unsigned long out, long *desc, int depth)
{
    unsigned long val;
    if (1 < cL4_mr_kind((unsigned long *)desc) - 1) {
        if ((cL4_mr_kind((unsigned long *)desc) != 5) || ((int)desc[1] == 0)) {
            val = 0;
        } else {
            desc = (long *)*desc;
            val = *desc;
        }
    } else {
        val = *desc;
    }
    cL4_mr_tag(out, val, "M", 1, (unsigned long)(depth + 1));
}

/* FUN_003ca0f8 @ 0x003ca0f8   (est. cL4_mr_dispatch_x)
 * Ghidra: void FUN_003ca0f8(undefined8 param_1,long *param_2,int param_3)
 * Resolves descriptor payload word and marshals it with tag 'x' (DAT_005d6fef).
 * Confidence: medium
 */
void cL4_mr_dispatch_x(unsigned long out, long *desc, int depth)
{
    unsigned long val;
    if (1 < cL4_mr_kind((unsigned long *)desc) - 1) {
        if ((cL4_mr_kind((unsigned long *)desc) != 5) || ((int)desc[1] == 0)) {
            val = 0;
        } else {
            desc = (long *)*desc;
            val = *desc;
        }
    } else {
        val = *desc;
    }
    cL4_mr_tag(out, val, "x", 1, (unsigned long)(depth + 1));
}

/* FUN_003ca140 @ 0x003ca140   (est. cL4_mr_type_name)
 * Ghidra: void FUN_003ca140(undefined4 *param_1,long param_2,long *param_3)
 * Classifies a descriptor by length against "__C" (3), "__C_Synthezied" (15),
 * and "Swift" (5) and emits the matching tag ("So"/"SC"/'s'). Otherwise it
 * begins marshalling (cL4_mr_init) with no tag. Clears result.
 * Confidence: medium
 */
void cL4_mr_type_name(unsigned int *out, long ctx, long *desc)
{
    long len = desc[1];
    char tag;
    unsigned long slot = *(unsigned long *)(ctx + 0x2150);

    if (len == 3) {
        if ((short)*desc == 0x5f5f && *(char *)((char *)desc + 2) == 'C') {  /* "__C" */
            cL4_mr_emit(ctx + 0x2140, "So", 2, slot);
            goto done;
        }
    } else if (len == 0xf) {
        if (*desc == 0x746e79535f435f5f && *(long *)((char *)desc + 7) == 0x64657a6973656874) { /* "__C_Synthesized" */
            cL4_mr_emit(ctx + 0x2140, "SC", 2, slot);
            goto done;
        }
    } else if ((len == 5) && ((int)*desc == 0x66697753 && *(char *)((char *)desc + 4) == 't')) { /* "Swift" */
        tag = 0x73;                          /* 's' */
        cL4_mr_emit_char(ctx + 0x2140, &tag, slot);
        goto done;
    }
    cL4_mr_init(ctx, (unsigned long)desc, 0);
done:
    *out = 0; *(unsigned long *)(out + 2) = 0; out[4] = 0;
}

/* FUN_003ca25c @ 0x003ca25c   (est. cL4_mr_dispatch_lo)
 * Ghidra: void FUN_003ca25c(undefined8 param_1,long *param_2,int param_3)
 * Resolves descriptor payload word and marshals it with tag "lo" (2 bytes).
 * Confidence: medium
 */
void cL4_mr_dispatch_lo(unsigned long out, long *desc, int depth)
{
    unsigned long val;
    if (1 < cL4_mr_kind((unsigned long *)desc) - 1) {
        if ((cL4_mr_kind((unsigned long *)desc) != 5) || ((int)desc[1] == 0)) {
            val = 0;
        } else {
            desc = (long *)*desc;
            val = *desc;
        }
    } else {
        val = *desc;
    }
    cL4_mr_tag(out, val, "lo", 2, (unsigned long)(depth + 1));
}

/* FUN_003ca2a4 @ 0x003ca2a4   (est. cL4_mr_dispatch_ao)
 * Ghidra: void FUN_003ca2a4(undefined8 param_1,long *param_2,int param_3)
 * Resolves descriptor payload word and marshals it with tag "ao".
 * Confidence: medium
 */
void cL4_mr_dispatch_ao(unsigned long out, long *desc, int depth)
{
    unsigned long val;
    if (1 < cL4_mr_kind((unsigned long *)desc) - 1) {
        if ((cL4_mr_kind((unsigned long *)desc) != 5) || ((int)desc[1] == 0)) {
            val = 0;
        } else {
            desc = (long *)*desc;
            val = *desc;
        }
    } else {
        val = *desc;
    }
    cL4_mr_tag(out, val, "ao", 2, (unsigned long)(depth + 1));
}

/* FUN_003ca2ec @ 0x003ca2ec   (est. cL4_mr_dispatch_lp)
 * Ghidra: void FUN_003ca2ec(undefined8 param_1,long *param_2,int param_3)
 * Resolves descriptor payload word and marshals it with tag "lp".
 * Confidence: medium
 */
void cL4_mr_dispatch_lp(unsigned long out, long *desc, int depth)
{
    unsigned long val;
    if (1 < cL4_mr_kind((unsigned long *)desc) - 1) {
        if ((cL4_mr_kind((unsigned long *)desc) != 5) || ((int)desc[1] == 0)) {
            val = 0;
        } else {
            desc = (long *)*desc;
            val = *desc;
        }
    } else {
        val = *desc;
    }
    cL4_mr_tag(out, val, "lp", 2, (unsigned long)(depth + 1));
}

/* FUN_003ca334 @ 0x003ca334   (est. cL4_mr_dispatch_aP)
 * Ghidra: void FUN_003ca334(undefined8 param_1,long *param_2,int param_3)
 * Resolves descriptor payload word and marshals it with tag "aP".
 * Confidence: medium
 */
void cL4_mr_dispatch_aP(unsigned long out, long *desc, int depth)
{
    unsigned long val;
    if (1 < cL4_mr_kind((unsigned long *)desc) - 1) {
        if ((cL4_mr_kind((unsigned long *)desc) != 5) || ((int)desc[1] == 0)) {
            val = 0;
        } else {
            desc = (long *)*desc;
            val = *desc;
        }
    } else {
        val = *desc;
    }
    cL4_mr_tag(out, val, "aP", 2, (unsigned long)(depth + 1));
}

/* FUN_003ca37c @ 0x003ca37c   (est. cL4_mr_emit_Mn)
 * Ghidra: void FUN_003ca37c(int *param_1,long param_2,undefined8 param_3,int param_4)
 * Marshals a word then emits tag "Mn". Clears result.
 * Confidence: medium
 */
void cL4_mr_emit_Mn(int *out, long ctx, unsigned long desc, int depth)
{
    cL4_mr_wrap1(ctx, desc, (unsigned long)(depth + 1));
    if (*out == 0) {
        cL4_mr_emit(ctx + 0x2140, "Mn", 2, *(unsigned long *)(ctx + 0x2150));
        *out = 0; out[2] = 0; out[3] = 0; out[4] = 0;
    }
}

/* FUN_003ca3d8 @ 0x003ca3d8   (est. cL4_mr_emit_Hn)
 * Ghidra: void FUN_003ca3d8(int *param_1,long param_2,undefined8 param_3,int param_4)
 * Marshals a word then emits tag "Hn". Clears result.
 * Confidence: medium
 */
void cL4_mr_emit_Hn(int *out, long ctx, unsigned long desc, int depth)
{
    cL4_mr_wrap1(ctx, desc, (unsigned long)(depth + 1));
    if (*out == 0) {
        cL4_mr_emit(ctx + 0x2140, "Hn", 2, *(unsigned long *)(ctx + 0x2150));
        *out = 0; out[2] = 0; out[3] = 0; out[4] = 0;
    }
}

/* FUN_003ca434 @ 0x003ca434   (est. cL4_mr_op_Tz)
 * Ghidra: void FUN_003ca434(int *param_1,long param_2,long param_3,int param_4)
 * Marshals MR words 0 and 1; if the descriptor is a kind-5 array with exactly 4
 * words, also marshals word 3; emits tag "Tz", then marshals word 2.
 * Confidence: medium
 */
void cL4_mr_op_Tz(int *out, long ctx, long desc, int depth)
{
    cL4_mr_op(ctx, desc, 0, (unsigned long)(depth + 1));
    if (((*out == 0) && (cL4_mr_op((unsigned long)out, ctx, desc, 1, (unsigned long)(depth + 1)), *out == 0)) &&
        ((*(char *)(desc + 0x12) != '\x05' ||
          ((*(int *)(desc + 8) != 4 || (cL4_mr_op((unsigned long)out, ctx, desc, 3, (unsigned long)(depth + 1)), *out == 0)))))) {
        cL4_mr_emit(ctx + 0x2140, "Tz", 2, *(unsigned long *)(ctx + 0x2150));
        cL4_mr_op((unsigned long)out, ctx, desc, 2, (unsigned long)(depth + 1));
    }
}

/* FUN_003ca518 @ 0x003ca518   (est. cL4_mr_op_TZ)
 * Ghidra: void FUN_003ca518(int *param_1,long param_2,long param_3,int param_4)
 * Same shape as cL4_mr_op_Tz but emits tag "TZ".
 * Confidence: medium
 */
void cL4_mr_op_TZ(int *out, long ctx, long desc, int depth)
{
    cL4_mr_op(ctx, desc, 0, (unsigned long)(depth + 1));
    if (((*out == 0) && (cL4_mr_op((unsigned long)out, ctx, desc, 1, (unsigned long)(depth + 1)), *out == 0)) &&
        ((*(char *)(desc + 0x12) != '\x05' ||
          ((*(int *)(desc + 8) != 4 || (cL4_mr_op((unsigned long)out, ctx, desc, 3, (unsigned long)(depth + 1)), *out == 0)))))) {
        cL4_mr_emit(ctx + 0x2140, "TZ", 2, *(unsigned long *)(ctx + 0x2150));
        cL4_mr_op((unsigned long)out, ctx, desc, 2, (unsigned long)(depth + 1));
    }
}

/* FUN_003ca5fc @ 0x003ca5fc   (est. cL4_mr_op_XB)
 * Ghidra: void FUN_003ca5fc(int *param_1,long param_2,long *param_3,int param_4)
 * If the payload tag is not 0x18, marshals via cL4_mr_wrap3 then emits "XB".
 * Otherwise marshals all element words in reverse, emits "XzB", and marshals
 * the descriptor's first word via cL4_mr_tail.
 * Confidence: medium
 */
void cL4_mr_op_XB(int *out, long ctx, long *desc, int depth)
{
    unsigned char kind;
    unsigned long n;
    long *inner;
    long i;

    kind = cL4_mr_kind((unsigned long *)desc);
    n = kind;
    inner = desc;
    if (1 < kind - 1) {
        if ((kind != 5) || ((int)desc[1] == 0)) goto not_shape;
        inner = (long *)*desc;
    }
    if (*(short *)(*inner + 0x10) != 0x18) {
not_shape:
        cL4_mr_wrap3(ctx, (unsigned long)desc, (unsigned long)(depth + 1));
        if (*out == 0) {
            cL4_mr_emit(ctx + 0x2140, "XB", 2, *(unsigned long *)(ctx + 0x2150));
            *out = 0; out[2] = 0; out[3] = 0; out[4] = 0;
        }
        return;
    }
    if (kind != 1) {
        if (kind == 5) n = (unsigned long)*(unsigned int *)(desc + 1);
        else { n = 0; if (kind == 2) n = 2; }
    }
    i = (int)n;
    while (1) {
        i = i - 1;
        if (i < 0) break;
        cL4_mr_op((unsigned long)out, ctx, (unsigned long)desc, i, (unsigned long)(depth + 1));
        if (*out != 0) return;
    }
    cL4_mr_emit(ctx + 0x2140, "XzB", 3, *(unsigned long *)(ctx + 0x2150));
    inner = desc;
    if (1 < cL4_mr_kind((unsigned long *)desc) - 1) {
        if ((cL4_mr_kind((unsigned long *)desc) != 5) || ((int)desc[1] == 0)) {
            i = 0;
            goto tail;
        }
        inner = (long *)*desc;
    }
    i = *inner;
tail:
    cL4_mr_tail((unsigned long)out, ctx, i);
}

/* FUN_003ca780 @ 0x003ca780   (est. cL4_mr_emit_XL)
 * Ghidra: void FUN_003ca780(int *param_1,long param_2,undefined8 param_3,int param_4)
 * Marshals a nested object (cL4_mr_wrap3) then emits tag "XL". Clears result.
 * Confidence: medium
 */
void cL4_mr_emit_XL(int *out, long ctx, unsigned long desc, int depth)
{
    cL4_mr_wrap3(ctx, desc, (unsigned long)(depth + 1));
    if (*out == 0) {
        cL4_mr_emit(ctx + 0x2140, "XL", 2, *(unsigned long *)(ctx + 0x2150));
        *out = 0; out[2] = 0; out[3] = 0; out[4] = 0;
    }
}

/* FUN_003ca7dc @ 0x003ca7dc   (est. cL4_mr_dispatch_lO)
 * Ghidra: void FUN_003ca7dc(undefined8 param_1,long *param_2,int param_3)
 * Resolves descriptor payload word and marshals it with tag "lO".
 * Confidence: medium
 */
void cL4_mr_dispatch_lO(unsigned long out, long *desc, int depth)
{
    unsigned long val;
    if (1 < cL4_mr_kind((unsigned long *)desc) - 1) {
        if ((cL4_mr_kind((unsigned long *)desc) != 5) || ((int)desc[1] == 0)) {
            val = 0;
        } else {
            desc = (long *)*desc;
            val = *desc;
        }
    } else {
        val = *desc;
    }
    cL4_mr_tag(out, val, "lO", 2, (unsigned long)(depth + 1));
}

/* FUN_003ca824 @ 0x003ca824   (est. cL4_mr_dispatch_aO)
 * Ghidra: void FUN_003ca824(undefined8 param_1,long *param_2,int param_3)
 * Resolves descriptor payload word and marshals it with tag "aO".
 * Confidence: medium
 */
void cL4_mr_dispatch_aO(unsigned long out, long *desc, int depth)
{
    unsigned long val;
    if (1 < cL4_mr_kind((unsigned long *)desc) - 1) {
        if ((cL4_mr_kind((unsigned long *)desc) != 5) || ((int)desc[1] == 0)) {
            val = 0;
        } else {
            desc = (long *)*desc;
            val = *desc;
        }
    } else {
        val = *desc;
    }
    cL4_mr_tag(out, val, "aO", 2, (unsigned long)(depth + 1));
}

/* FUN_003ca86c @ 0x003ca86c   (est. cL4_mr_emit_TA)
 * Ghidra: void FUN_003ca86c(int *param_1,long param_2,undefined8 param_3,int param_4)
 * Marshals a nested object then emits tag "TA". Clears result.
 * Confidence: medium
 */
void cL4_mr_emit_TA(int *out, long ctx, unsigned long desc, int depth)
{
    cL4_mr_wrap3(ctx, desc, (unsigned long)(depth + 1));
    if (*out == 0) {
        cL4_mr_emit(ctx + 0x2140, "TA", 2, *(unsigned long *)(ctx + 0x2150));
        *out = 0; out[2] = 0; out[3] = 0; out[4] = 0;
    }
}

/* FUN_003ca8c8 @ 0x003ca8c8   (est. cL4_mr_emit_Ta)
 * Ghidra: void FUN_003ca8c8(int *param_1,long param_2,undefined8 param_3,int param_4)
 * Marshals a nested object then emits tag "Ta". Clears result.
 * Confidence: medium
 */
void cL4_mr_emit_Ta(int *out, long ctx, unsigned long desc, int depth)
{
    cL4_mr_wrap3(ctx, desc, (unsigned long)(depth + 1));
    if (*out == 0) {
        cL4_mr_emit(ctx + 0x2140, "Ta", 2, *(unsigned long *)(ctx + 0x2150));
        *out = 0; out[2] = 0; out[3] = 0; out[4] = 0;
    }
}

/* FUN_003ca924 @ 0x003ca924   (est. cL4_mr_op_fMp)
 * Ghidra: void FUN_003ca924(int *param_1,long param_2,undefined8 param_3,int param_4)
 * Marshals MR words 0,1,2, emits tag "fMp", then marshals word 3.
 * Confidence: medium
 */
void cL4_mr_op_fMp(int *out, long ctx, unsigned long desc, int depth)
{
    cL4_mr_op(ctx, desc, 0, (unsigned long)(depth + 1));
    if (((*out == 0) && (cL4_mr_op((unsigned long)out, ctx, desc, 1, (unsigned long)(depth + 1)), *out == 0)) &&
        (cL4_mr_op((unsigned long)out, ctx, desc, 2, (unsigned long)(depth + 1)), *out == 0)) {
        cL4_mr_emit(ctx + 0x2140, "fMp", 3, *(unsigned long *)(ctx + 0x2150));
        cL4_mr_op((unsigned long)out, ctx, desc, 3, (unsigned long)(depth + 1));
    }
}

/* FUN_003ca9f0 @ 0x003ca9f0   (est. cL4_mr_init_oP)
 * Ghidra: void FUN_003ca9f0(undefined4 *param_1,long param_2,undefined8 param_3)
 * Begins marshalling (cL4_mr_init) and emits tag "oP". Clears result.
 * Confidence: medium
 */
void cL4_mr_init_oP(unsigned int *out, long ctx, unsigned long desc)
{
    cL4_mr_init(ctx, desc, 1);
    cL4_mr_emit(ctx + 0x2140, "oP", 2, *(unsigned long *)(ctx + 0x2150));
    *out = 0; *(unsigned long *)(out + 2) = 0; out[4] = 0;
}

/* FUN_003caa44 @ 0x003caa44   (est. cL4_mr_op_fMq)
 * Ghidra: void FUN_003caa44(int *param_1,long param_2,undefined8 param_3,int param_4)
 * Marshals MR words 0,1,2, emits tag "fMq", then marshals word 3.
 * Confidence: medium
 */
void cL4_mr_op_fMq(int *out, long ctx, unsigned long desc, int depth)
{
    cL4_mr_op(ctx, desc, 0, (unsigned long)(depth + 1));
    if (((*out == 0) && (cL4_mr_op((unsigned long)out, ctx, desc, 1, (unsigned long)(depth + 1)), *out == 0)) &&
        (cL4_mr_op((unsigned long)out, ctx, desc, 2, (unsigned long)(depth + 1)), *out == 0)) {
        cL4_mr_emit(ctx + 0x2140, "fMq", 3, *(unsigned long *)(ctx + 0x2150));
        cL4_mr_op((unsigned long)out, ctx, desc, 3, (unsigned long)(depth + 1));
    }
}

/* FUN_003cab10 @ 0x003cab10   (est. cL4_mr_init_op)
 * Ghidra: void FUN_003cab10(undefined4 *param_1,long param_2,undefined8 param_3)
 * Begins marshalling (cL4_mr_init) and emits tag "op". Clears result.
 * Confidence: medium
 */
void cL4_mr_init_op(unsigned int *out, long ctx, unsigned long desc)
{
    cL4_mr_init(ctx, desc, 1);
    cL4_mr_emit(ctx + 0x2140, "op", 2, *(unsigned long *)(ctx + 0x2150));
    *out = 0; *(unsigned long *)(out + 2) = 0; out[4] = 0;
}

/* FUN_003cab64 @ 0x003cab64   (est. cL4_mr_emit_Ll_LL)
 * Ghidra: void FUN_003cab64(int *param_1,long param_2,long param_3,int param_4)
 * Marshals a nested object, then emits tag "Ll" (or "LL" when the descriptor
 * kind is 1 or kind-5 count 1). Clears result.
 * Confidence: medium
 */
void cL4_mr_emit_Ll_LL(int *out, long ctx, long desc, int depth)
{
    const char *tag;
    cL4_mr_wrap3(ctx, desc, (unsigned long)(depth + 1));
    if (*out == 0) {
        if ((*(char *)(desc + 0x12) == '\x01') ||
            ((*(char *)(desc + 0x12) == '\x05' && (*(int *)(desc + 8) == 1)))) tag = "Ll";
        else tag = "LL";
        cL4_mr_emit(ctx + 0x2140, tag, 2, *(unsigned long *)(ctx + 0x2150));
        *out = 0; out[2] = 0; out[3] = 0; out[4] = 0;
    }
}

/* FUN_003cabf8 @ 0x003cabf8   (est. cL4_mr_emit_MV)
 * Ghidra: void FUN_003cabf8(int *param_1,long param_2,undefined8 param_3,int param_4)
 * Marshals a word then emits tag "MV". Clears result.
 * Confidence: medium
 */
void cL4_mr_emit_MV(int *out, long ctx, unsigned long desc, int depth)
{
    cL4_mr_wrap1(ctx, desc, (unsigned long)(depth + 1));
    if (*out == 0) {
        cL4_mr_emit(ctx + 0x2140, "MV", 2, *(unsigned long *)(ctx + 0x2150));
        *out = 0; out[2] = 0; out[3] = 0; out[4] = 0;
    }
}

/* FUN_003cac54 @ 0x003cac54   (est. cL4_mr_op_fP)
 * Ghidra: void FUN_003cac54(int *param_1,long param_2,undefined8 param_3,int param_4)
 * Marshals a word then emits tag "fP". Clears result.
 * Confidence: medium
 */
void cL4_mr_op_fP(int *out, long ctx, unsigned long desc, int depth)
{
    cL4_mr_wrap2(ctx, desc, (unsigned long)(depth + 1));
    if (*out == 0) {
        cL4_mr_emit(ctx + 0x2140, "fP", 2, *(unsigned long *)(ctx + 0x2150));
        *out = 0; out[2] = 0; out[3] = 0; out[4] = 0;
    }
}

/* FUN_003cacb0 @ 0x003cacb0   (est. cL4_mr_op_fF)
 * Ghidra: void FUN_003cacb0(int *param_1,long param_2,undefined8 param_3,int param_4)
 * Marshals a word then emits tag "fF". Clears result.
 * Confidence: medium
 */
void cL4_mr_op_fF(int *out, long ctx, unsigned long desc, int depth)
{
    cL4_mr_wrap2(ctx, desc, (unsigned long)(depth + 1));
    if (*out == 0) {
        cL4_mr_emit(ctx + 0x2140, "fF", 2, *(unsigned long *)(ctx + 0x2150));
        *out = 0; out[2] = 0; out[3] = 0; out[4] = 0;
    }
}

/* FUN_003cad0c @ 0x003cad0c   (est. cL4_mr_op_fW)
 * Ghidra: void FUN_003cad0c(int *param_1,long param_2,undefined8 param_3,int param_4)
 * Marshals a word then emits tag "fW". Clears result.
 * Confidence: medium
 */
void cL4_mr_op_fW(int *out, long ctx, unsigned long desc, int depth)
{
    cL4_mr_wrap2(ctx, desc, (unsigned long)(depth + 1));
    if (*out == 0) {
        cL4_mr_emit(ctx + 0x2140, "fW", 2, *(unsigned long *)(ctx + 0x2150));
        *out = 0; out[2] = 0; out[3] = 0; out[4] = 0;
    }
}

/* FUN_003cad68 @ 0x003cad68   (est. cL4_mr_object_ref)
 * Ghidra: void FUN_003cad68(int *param_1,undefined8 param_2,long *param_3,int param_4)
 * Marshals a descriptor word, then a guarded second word; if the descriptor is
 * a kind-5 array of 4, also marshals word 3, then MR word 2, and the resolved
 * first-word value (or its second element for kind 2/5). On failure keeps the
 * error in the result word; on success clears it.
 * Confidence: medium
 */
void cL4_mr_object_ref(int *out, unsigned long ctx, long *desc, int depth)
{
    unsigned char kind;
    char c;
    long r1;
    long *d1, *d2;
    unsigned long *p1;
    long r7;

    d1 = desc;
    if (cL4_mr_kind((unsigned long *)desc) - 1 < 2) {
        p1 = (unsigned long *)*d1;
    } else {
        if ((cL4_mr_kind((unsigned long *)desc) == 5) && ((int)desc[1] != 0)) { d1 = (long *)*desc; p1 = (unsigned long *)*d1; }
        else p1 = 0;
    }
    if (cL4_mr_kind((unsigned long *)p1) - 1 < 2) {
        d1 = (long *)*p1;
    } else {
        if ((cL4_mr_kind((unsigned long *)p1) == 5) && (*(int *)(p1 + 1) != 0)) { p1 = (unsigned long *)*p1; d1 = (long *)*p1; }
        else d1 = 0;
    }
    if ((short)d1[2] == 0x2d) {
        kind = cL4_mr_kind((unsigned long *)d1);
        d2 = d1;
        if (kind - 1 < 2) {
            r7 = *d2;
        } else {
            if (kind == 5) {
                if ((int)d1[1] == 0) { d1 = 0; goto post_resolve; }
                d2 = (long *)*d1;
                r7 = *d2;
            } else {
                r7 = 0;
            }
        }
        if (kind != 2) {
            if ((kind != 5) || (*(unsigned int *)(d1 + 1) < 2)) { d1 = 0; goto post_resolve2; }
            d1 = (long *)*d1;
        }
        d1 = *(long **)((char *)d1 + 8);
    } else {
post_resolve:
        r7 = 0;
    }
post_resolve2:
    cL4_mr_rec((unsigned long)out, ctx, (unsigned long)d1, (unsigned long)(depth + 1));
    if (*out != 0) return;
    c = *(char *)((char *)desc + 0x12);
    if (c == '\x05') {
        if ((int)desc[1] == 4) {
            cL4_mr_op((unsigned long)out, ctx, (unsigned long)desc, 3, (unsigned long)(depth + 1));
            if (*out != 0) return;
            c = *(char *)((char *)desc + 0x12);
            d1 = desc;
            if (c == '\x02') { r1 = d1[1]; goto marshal2; }
            if (c == '\x05') goto kind5;
            r1 = 0;
        } else {
kind5:
            if (1 < *(unsigned int *)(desc + 1)) { d1 = (long *)*desc; r1 = d1[1]; goto marshal2; }
            r1 = 0;
        }
    } else {
        d1 = desc;
        if (c == '\x02') { r1 = d1[1]; goto marshal2; }
        if (c == '\x05') goto kind5;
        r1 = 0;
    }
marshal2:
    cL4_mr_val((unsigned long)out, ctx, (unsigned long)r1, (unsigned long)(depth + 1));
    if (((*out == 0) && (cL4_mr_op((unsigned long)out, ctx, (unsigned long)desc, 2, (unsigned long)(depth + 1)), *out == 0)) &&
        ((r7 == 0 || (cL4_mr_rec((unsigned long)out, ctx, (unsigned long)r7, (unsigned long)(depth + 1)), *out == 0)))) {
        *out = 0; out[2] = 0; out[3] = 0; out[4] = 0;
    }
}

/* FUN_003caf68 @ 0x003caf68   (est. cL4_mr_val_HP)
 * Ghidra: void FUN_003caf68(int *param_1,long param_2,long *param_3,int param_4)
 * Resolves descriptor payload word, marshals it via cL4_mr_val, then emits
 * tag "HP". Clears result.
 * Confidence: medium
 */
void cL4_mr_val_HP(int *out, long ctx, long *desc, int depth)
{
    unsigned long val;
    if (1 < cL4_mr_kind((unsigned long *)desc) - 1) {
        if ((cL4_mr_kind((unsigned long *)desc) != 5) || ((int)desc[1] == 0)) {
            val = 0;
        } else {
            desc = (long *)*desc;
            val = *desc;
        }
    } else {
        val = *desc;
    }
    cL4_mr_val((unsigned long)out, ctx, val, (unsigned long)(depth + 1));
    if (*out == 0) {
        cL4_mr_emit(ctx + 0x2140, "HP", 2, *(unsigned long *)(ctx + 0x2150));
        *out = 0; out[2] = 0; out[3] = 0; out[4] = 0;
    }
}

/* FUN_003caffc @ 0x003caffc   (est. cL4_mr_val_Hp)
 * Ghidra: void FUN_003caffc(int *param_1,long param_2,long *param_3,int param_4)
 * Same as cL4_mr_val_HP but emits tag "Hp".
 * Confidence: medium
 */
void cL4_mr_val_Hp(int *out, long ctx, long *desc, int depth)
{
    unsigned long val;
    if (1 < cL4_mr_kind((unsigned long *)desc) - 1) {
        if ((cL4_mr_kind((unsigned long *)desc) != 5) || ((int)desc[1] == 0)) {
            val = 0;
        } else {
            desc = (long *)*desc;
            val = *desc;
        }
    } else {
        val = *desc;
    }
    cL4_mr_val((unsigned long)out, ctx, val, (unsigned long)(depth + 1));
    if (*out == 0) {
        cL4_mr_emit(ctx + 0x2140, "Hp", 2, *(unsigned long *)(ctx + 0x2150));
        *out = 0; out[2] = 0; out[3] = 0; out[4] = 0;
    }
}

/* FUN_003cb090 @ 0x003cb090   (est. cL4_mr_val_then_word1)
 * Ghidra: void FUN_003cb090(int *param_1,undefined8 param_2,long *param_3,int param_4)
 * Marshals the descriptor's first payload word via cL4_mr_val, then marshals
 * MR word 1. Does not clear the result (no tag emitted).
 * Confidence: medium
 */
void cL4_mr_val_then_word1(int *out, unsigned long ctx, long *desc, int depth)
{
    unsigned long val;
    long *d;
    d = desc;
    if (1 < cL4_mr_kind((unsigned long *)desc) - 1) {
        if ((cL4_mr_kind((unsigned long *)desc) != 5) || ((int)desc[1] == 0)) {
            val = 0;
        } else {
            d = (long *)*desc;
            val = *d;
        }
    } else {
        val = *d;
    }
    cL4_mr_val((unsigned long)out, ctx, val, (unsigned long)(depth + 1));
    if (*out != 0) return;
    cL4_mr_op((unsigned long)out, ctx, (unsigned long)desc, 1, (unsigned long)(depth + 1));
}

/* FUN_003cb138 @ 0x003cb138   (est. cL4_mr_val_Mp)
 * Ghidra: void FUN_003cb138(int *param_1,long param_2,long *param_3,int param_4)
 * Same as cL4_mr_val_HP but emits tag "Mp".
 * Confidence: medium
 */
void cL4_mr_val_Mp(int *out, long ctx, long *desc, int depth)
{
    unsigned long val;
    if (1 < cL4_mr_kind((unsigned long *)desc) - 1) {
        if ((cL4_mr_kind((unsigned long *)desc) != 5) || ((int)desc[1] == 0)) {
            val = 0;
        } else {
            desc = (long *)*desc;
            val = *desc;
        }
    } else {
        val = *desc;
    }
    cL4_mr_val((unsigned long)out, ctx, val, (unsigned long)(depth + 1));
    if (*out == 0) {
        cL4_mr_emit(ctx + 0x2140, "Mp", 2, *(unsigned long *)(ctx + 0x2150));
        *out = 0; out[2] = 0; out[3] = 0; out[4] = 0;
    }
}

/* FUN_003cb1cc @ 0x003cb1cc   (est. cL4_mr_val_Hr)
 * Ghidra: void FUN_003cb1cc(int *param_1,long param_2,long *param_3,int param_4)
 * Same as cL4_mr_val_HP but emits tag "Hr".
 * Confidence: medium
 */
void cL4_mr_val_Hr(int *out, long ctx, long *desc, int depth)
{
    unsigned long val;
    if (1 < cL4_mr_kind((unsigned long *)desc) - 1) {
        if ((cL4_mr_kind((unsigned long *)desc) != 5) || ((int)desc[1] == 0)) {
            val = 0;
        } else {
            desc = (long *)*desc;
            val = *desc;
        }
    } else {
        val = *desc;
    }
    cL4_mr_val((unsigned long)out, ctx, val, (unsigned long)(depth + 1));
    if (*out == 0) {
        cL4_mr_emit(ctx + 0x2140, "Hr", 2, *(unsigned long *)(ctx + 0x2150));
        *out = 0; out[2] = 0; out[3] = 0; out[4] = 0;
    }
}

/* FUN_003cb260 @ 0x003cb260   (est. cL4_mr_ref_Mc)
 * Ghidra: void FUN_003cb260(int *param_1,long param_2,long *param_3,int param_4)
 * Resolves descriptor payload word, marshals it via cL4_mr_object_ref, then
 * emits tag "Mc". Clears result.
 * Confidence: medium
 */
void cL4_mr_ref_Mc(int *out, long ctx, long *desc, int depth)
{
    unsigned long val;
    if (1 < cL4_mr_kind((unsigned long *)desc) - 1) {
        if ((cL4_mr_kind((unsigned long *)desc) != 5) || ((int)desc[1] == 0)) {
            val = 0;
        } else {
            desc = (long *)*desc;
            val = *desc;
        }
    } else {
        val = *desc;
    }
    cL4_mr_object_ref(out, ctx, (long *)val, (unsigned long)(depth + 1));
    if (*out == 0) {
        cL4_mr_emit(ctx + 0x2140, "Mc", 2, *(unsigned long *)(ctx + 0x2150));
        *out = 0; out[2] = 0; out[3] = 0; out[4] = 0;
    }
}

/* FUN_003cb2f4 @ 0x003cb2f4   (est. cL4_mr_ref_Hc)
 * Ghidra: void FUN_003cb2f4(int *param_1,long param_2,long *param_3,int param_4)
 * Same as cL4_mr_ref_Mc but emits tag "Hc".
 * Confidence: medium
 */
void cL4_mr_ref_Hc(int *out, long ctx, long *desc, int depth)
{
    unsigned long val;
    if (1 < cL4_mr_kind((unsigned long *)desc) - 1) {
        if ((cL4_mr_kind((unsigned long *)desc) != 5) || ((int)desc[1] == 0)) {
            val = 0;
        } else {
            desc = (long *)*desc;
            val = *desc;
        }
    } else {
        val = *desc;
    }
    cL4_mr_object_ref(out, ctx, (long *)val, (unsigned long)(depth + 1));
    if (*out == 0) {
        cL4_mr_emit(ctx + 0x2140, "Hc", 2, *(unsigned long *)(ctx + 0x2150));
        *out = 0; out[2] = 0; out[3] = 0; out[4] = 0;
    }
}

/* FUN_003cb388 @ 0x003cb388   (est. cL4_mr_pair0)
 * Ghidra: void FUN_003cb388(undefined8 param_1,long *param_2,int param_3)
 * Marshals the descriptor's (lo,hi) word pair via cL4_mr_pair with flag 0.
 * Confidence: medium
 */
void cL4_mr_pair0(unsigned long out, long *desc, int depth)
{
    unsigned char kind;
    unsigned long lo, hi;
    long *d;
    kind = cL4_mr_kind((unsigned long *)desc);
    d = desc;
    if (kind - 1 < 2) {
        lo = *d;
    } else {
        if (kind != 5) { lo = 0; goto get_hi; }
        if ((int)desc[1] != 0) { d = (long *)*desc; lo = *d; }
        else { lo = 0; goto get_hi; }
    }
get_hi:
    if (kind != 2) {
        if ((kind != 5) || (*(unsigned int *)(desc + 1) < 2)) { hi = 0; goto done; }
        desc = (long *)*desc;
    }
    hi = desc[1];
done:
    cL4_mr_pair(out, lo, hi, 0, (unsigned long)(depth + 1));
}

/* FUN_003cb400 @ 0x003cb400   (est. cL4_mr_pair1)
 * Ghidra: void FUN_003cb400(undefined8 param_1,long *param_2,int param_3)
 * Marshals the descriptor's first payload word via cL4_mr_pair (hi=0, flag 1).
 * Confidence: medium
 */
void cL4_mr_pair1(unsigned long out, long *desc, int depth)
{
    unsigned long val;
    if (1 < cL4_mr_kind((unsigned long *)desc) - 1) {
        if ((cL4_mr_kind((unsigned long *)desc) != 5) || ((int)desc[1] == 0)) {
            val = 0;
        } else {
            desc = (long *)*desc;
            val = *desc;
        }
    } else {
        val = *desc;
    }
    cL4_mr_pair(out, val, 0, 1, (unsigned long)(depth + 1));
}

/* FUN_003cb440 @ 0x003cb440   (est. cL4_mr_val_MS)
 * Ghidra: void FUN_003cb440(int *param_1,long param_2,long *param_3,int param_4)
 * Same as cL4_mr_val_HP but emits tag "MS".
 * Confidence: medium
 */
void cL4_mr_val_MS(int *out, long ctx, long *desc, int depth)
{
    unsigned long val;
    if (1 < cL4_mr_kind((unsigned long *)desc) - 1) {
        if ((cL4_mr_kind((unsigned long *)desc) != 5) || ((int)desc[1] == 0)) {
            val = 0;
        } else {
            desc = (long *)*desc;
            val = *desc;
        }
    } else {
        val = *desc;
    }
    cL4_mr_val((unsigned long)out, ctx, val, (unsigned long)(depth + 1));
    if (*out == 0) {
        cL4_mr_emit(ctx + 0x2140, "MS", 2, *(unsigned long *)(ctx + 0x2150));
        *out = 0; out[2] = 0; out[3] = 0; out[4] = 0;
    }
}

/* FUN_003cb4d4 @ 0x003cb4d4   (est. cL4_mr_emit_TS)
 * Ghidra: void FUN_003cb4d4(int *param_1,long param_2,undefined8 param_3,int param_4)
 * Marshals a word then emits tag "TS". Clears result.
 * Confidence: medium
 */
void cL4_mr_emit_TS(int *out, long ctx, unsigned long desc, int depth)
{
    cL4_mr_wrap1(ctx, desc, (unsigned long)(depth + 1));
    if (*out == 0) {
        cL4_mr_emit(ctx + 0x2140, "TS", 2, *(unsigned long *)(ctx + 0x2150));
        *out = 0; out[2] = 0; out[3] = 0; out[4] = 0;
    }
}

/* FUN_003cb530 @ 0x003cb530   (est. cL4_mr_val_WS)
 * Ghidra: void FUN_003cb530(int *param_1,long param_2,long *param_3,int param_4)
 * Same as cL4_mr_val_HP but emits tag "WS".
 * Confidence: medium
 */
void cL4_mr_val_WS(int *out, long ctx, long *desc, int depth)
{
    unsigned long val;
    if (1 < cL4_mr_kind((unsigned long *)desc) - 1) {
        if ((cL4_mr_kind((unsigned long *)desc) != 5) || ((int)desc[1] == 0)) {
            val = 0;
        } else {
            desc = (long *)*desc;
            val = *desc;
        }
    } else {
        val = *desc;
    }
    cL4_mr_val((unsigned long)out, ctx, val, (unsigned long)(depth + 1));
    if (*out == 0) {
        cL4_mr_emit(ctx + 0x2140, "WS", 2, *(unsigned long *)(ctx + 0x2150));
        *out = 0; out[2] = 0; out[3] = 0; out[4] = 0;
    }
}

/* FUN_003cb5c4 @ 0x003cb5c4   (est. cL4_mr_op_TW)
 * Ghidra: void FUN_003cb5c4(int *param_1,long param_2,undefined8 param_3,int param_4)
 * Marshals a word then emits tag "TW". Clears result.
 * Confidence: medium
 */
void cL4_mr_op_TW(int *out, long ctx, unsigned long desc, int depth)
{
    cL4_mr_wrap2(ctx, desc, (unsigned long)(depth + 1));
    if (*out == 0) {
        cL4_mr_emit(ctx + 0x2140, "TW", 2, *(unsigned long *)(ctx + 0x2150));
        *out = 0; out[2] = 0; out[3] = 0; out[4] = 0;
    }
}

/* FUN_003cb620 @ 0x003cb620   (est. cL4_mr_emit_WP)
 * Ghidra: void FUN_003cb620(int *param_1,long param_2,undefined8 param_3,int param_4)
 * Marshals a word then emits tag "WP". Clears result.
 * Confidence: medium
 */
void cL4_mr_emit_WP(int *out, long ctx, unsigned long desc, int depth)
{
    cL4_mr_wrap1(ctx, desc, (unsigned long)(depth + 1));
    if (*out == 0) {
        cL4_mr_emit(ctx + 0x2140, "WP", 2, *(unsigned long *)(ctx + 0x2150));
        *out = 0; out[2] = 0; out[3] = 0; out[4] = 0;
    }
}

/* FUN_003cb67c @ 0x003cb67c   (est. cL4_mr_emit_Wa)
 * Ghidra: void FUN_003cb67c(int *param_1,long param_2,undefined8 param_3,int param_4)
 * Marshals a word then emits tag "Wa". Clears result.
 * Confidence: medium
 */
void cL4_mr_emit_Wa(int *out, long ctx, unsigned long desc, int depth)
{
    cL4_mr_wrap1(ctx, desc, (unsigned long)(depth + 1));
    if (*out == 0) {
        cL4_mr_emit(ctx + 0x2140, "Wa", 2, *(unsigned long *)(ctx + 0x2150));
        *out = 0; out[2] = 0; out[3] = 0; out[4] = 0;
    }
}

/* FUN_003cb6d8 @ 0x003cb6d8   (est. cL4_mr_emit_Wp)
 * Ghidra: void FUN_003cb6d8(int *param_1,long param_2,undefined8 param_3,int param_4)
 * Marshals a word then emits tag "Wp". Clears result.
 * Confidence: medium
 */
void cL4_mr_emit_Wp(int *out, long ctx, unsigned long desc, int depth)
{
    cL4_mr_wrap1(ctx, desc, (unsigned long)(depth + 1));
    if (*out == 0) {
        cL4_mr_emit(ctx + 0x2140, "Wp", 2, *(unsigned long *)(ctx + 0x2150));
        *out = 0; out[2] = 0; out[3] = 0; out[4] = 0;
    }
}

/* FUN_003cb734 @ 0x003cb734   (est. cL4_mr_emit_Tr)
 * Ghidra: void FUN_003cb734(int *param_1,long param_2,undefined8 param_3,int param_4)
 * Marshals a nested object then emits tag "Tr". Clears result.
 * Confidence: medium
 */
void cL4_mr_emit_Tr(int *out, long ctx, unsigned long desc, int depth)
{
    cL4_mr_wrap3(ctx, desc, (unsigned long)(depth + 1));
    if (*out == 0) {
        cL4_mr_emit(ctx + 0x2140, "Tr", 2, *(unsigned long *)(ctx + 0x2150));
        *out = 0; out[2] = 0; out[3] = 0; out[4] = 0;
    }
}

/* FUN_003cb790 @ 0x003cb790   (est. cL4_mr_emit_TR)
 * Ghidra: void FUN_003cb790(int *param_1,long param_2,undefined8 param_3,int param_4)
 * Marshals a nested object then emits tag "TR". Clears result.
 * Confidence: medium
 */
void cL4_mr_emit_TR(int *out, long ctx, unsigned long desc, int depth)
{
    cL4_mr_wrap3(ctx, desc, (unsigned long)(depth + 1));
    if (*out == 0) {
        cL4_mr_emit(ctx + 0x2140, "TR", 2, *(unsigned long *)(ctx + 0x2150));
        *out = 0; out[2] = 0; out[3] = 0; out[4] = 0;
    }
}

/* FUN_003cb7ec @ 0x003cb7ec   (est. cL4_mr_emit_Ty)
 * Ghidra: void FUN_003cb7ec(int *param_1,long param_2,undefined8 param_3,int param_4)
 * Marshals a nested object then emits tag "Ty". Clears result.
 * Confidence: medium
 */
void cL4_mr_emit_Ty(int *out, long ctx, unsigned long desc, int depth)
{
    cL4_mr_wrap3(ctx, desc, (unsigned long)(depth + 1));
    if (*out == 0) {
        cL4_mr_emit(ctx + 0x2140, "Ty", 2, *(unsigned long *)(ctx + 0x2150));
        *out = 0; out[2] = 0; out[3] = 0; out[4] = 0;
    }
}

/* FUN_003cb848 @ 0x003cb848   (est. cL4_mr_op_TU)
 * Ghidra: void FUN_003cb848(int *param_1,long param_2,undefined8 param_3,int param_4)
 * Marshals a word then emits tag "TU". Clears result.
 * Confidence: medium
 */
void cL4_mr_op_TU(int *out, long ctx, unsigned long desc, int depth)
{
    cL4_mr_wrap2(ctx, desc, (unsigned long)(depth + 1));
    if (*out == 0) {
        cL4_mr_emit(ctx + 0x2140, "TU", 2, *(unsigned long *)(ctx + 0x2150));
        *out = 0; out[2] = 0; out[3] = 0; out[4] = 0;
    }
}

/* FUN_003cb8a4 @ 0x003cb8a4   (est. cL4_mr_dispatch_r)
 * Ghidra: void FUN_003cb8a4(undefined8 param_1,long *param_2,int param_3)
 * Resolves descriptor payload word and marshals it with tag 'r' (DAT_005d6fd1).
 * Confidence: medium
 */
void cL4_mr_dispatch_r(unsigned long out, long *desc, int depth)
{
    unsigned long val;
    if (1 < cL4_mr_kind((unsigned long *)desc) - 1) {
        if ((cL4_mr_kind((unsigned long *)desc) != 5) || ((int)desc[1] == 0)) {
            val = 0;
        } else {
            desc = (long *)*desc;
            val = *desc;
        }
    } else {
        val = *desc;
    }
    cL4_mr_tag(out, val, "r", 1, (unsigned long)(depth + 1));
}

/* FUN_003cb8ec @ 0x003cb8ec   (est. cL4_mr_dispatch_y)
 * Ghidra: void FUN_003cb8ec(undefined8 param_1,long *param_2,int param_3)
 * Resolves descriptor payload word and marshals it with tag 'y' (DAT_005d6ff3).
 * Confidence: medium
 */
void cL4_mr_dispatch_y(unsigned long out, long *desc, int depth)
{
    unsigned long val;
    if (1 < cL4_mr_kind((unsigned long *)desc) - 1) {
        if ((cL4_mr_kind((unsigned long *)desc) != 5) || ((int)desc[1] == 0)) {
            val = 0;
        } else {
            desc = (long *)*desc;
            val = *desc;
        }
    } else {
        val = *desc;
    }
    cL4_mr_tag(out, val, "y", 1, (unsigned long)(depth + 1));
}

/* FUN_003cb934 @ 0x003cb934   (est. cL4_mr_string_L)
 * Ghidra: void FUN_003cb934(int *param_1,long param_2,undefined8 *param_3,int param_4)
 * Marshals MR word 1, then if the descriptor payload length is 1 emits the
 * tag 'L' and the one-byte string payload. On length!=1 sets error 0xc63 with
 * kind 0x16.
 * Confidence: medium
 */
void cL4_mr_string_L(int *out, long ctx, unsigned long *desc, int depth)
{
    unsigned long *p;
    int err, kind;
    unsigned long slot = *(unsigned long *)(ctx + 0x2150);

    cL4_mr_op(ctx, desc, 1, (unsigned long)(depth + 1));
    if (*out != 0) return;
    p = desc;
    if (1 < cL4_mr_kind((unsigned long *)desc) - 1) {
        if ((cL4_mr_kind((unsigned long *)desc) != 5) || (*(int *)(desc + 1) == 0)) {
            p = 0;
            goto check;
        }
        p = (unsigned long *)*desc;
    }
    p = (unsigned long *)*p;
check:
    if (p[1] == 1) {
        cL4_mr_emit(ctx + 0x2140, "L", 1, slot);
        cL4_mr_emit(ctx + 0x2140, (const void *)*p, p[1], slot);
        kind = 0; err = 0; p = 0;
    } else {
        err = 0xc63; kind = 0x16;
    }
    *out = kind;
    *(unsigned long *)(out + 2) = (unsigned long)p;
    out[4] = err;
}

/* FUN_003cba04 @ 0x003cba04   (est. cL4_mr_cba04)
 * Ghidra: void FUN_003cba04(int *param_1,long param_2,long *param_3,int param_4)
 * Marshals the descriptor's second word (for kind 2, or kind-5 array >=2) via
 * cL4_mr_gword, emits 'g', then marshals the descriptor's first payload word
 * as a 64-bit value. Clears result.
 * Confidence: medium
 */
void cL4_mr_cba04(int *out, long ctx, long *desc, int depth)
{
    unsigned long val;
    long *d;
    char tag = 0x67;                           /* 'g' */
    d = desc;
    if (*(char *)((char *)desc + 0x12) != '\x02') {
        if ((*(char *)((char *)desc + 0x12) != '\x05') || (*(unsigned int *)(desc + 1) < 2)) {
            val = 0;
            goto marshal;
        }
        d = (long *)*desc;
    }
    val = *(unsigned long *)((char *)d + 8);
marshal:
    cL4_mr_gword((unsigned long)out, ctx, val, (unsigned long)(depth + 1));
    if (*out == 0) {
        cL4_mr_emit_char(ctx + 0x2140, &tag, *(unsigned long *)(ctx + 0x2150));
        if (1 < cL4_mr_kind((unsigned long *)desc) - 1) {
            desc = (long *)*desc;
        }
        cL4_mr_emit_u64(ctx, *desc);
        *out = 0; out[2] = 0; out[3] = 0; out[4] = 0;
    }
}

/* FUN_003cbad4 @ 0x003cbad4   (est. cL4_mr_char_h)
 * Ghidra: void FUN_003cbad4(int *param_1,long param_2,undefined8 param_3,int param_4)
 * Marshals a word then emits the single tag byte 'h'. Clears result.
 * Confidence: medium
 */
void cL4_mr_char_h(int *out, long ctx, unsigned long desc, int depth)
{
    char tag = 0x68;
    cL4_mr_wrap1(ctx, desc, (unsigned long)(depth + 1));
    if (*out == 0) {
        cL4_mr_emit_char(ctx + 0x2140, &tag, *(unsigned long *)(ctx + 0x2150));
        *out = 0; out[2] = 0; out[3] = 0; out[4] = 0;
    }
}

/* FUN_003cbb38 @ 0x003cbb38   (est. cL4_mr_char_n)
 * Ghidra: void FUN_003cbb38(int *param_1,long param_2,undefined8 param_3,int param_4)
 * Marshals a word then emits the single tag byte 'n'. Clears result.
 * Confidence: medium
 */
void cL4_mr_char_n(int *out, long ctx, unsigned long desc, int depth)
{
    char tag = 0x6e;
    cL4_mr_wrap1(ctx, desc, (unsigned long)(depth + 1));
    if (*out == 0) {
        cL4_mr_emit_char(ctx + 0x2140, &tag, *(unsigned long *)(ctx + 0x2150));
        *out = 0; out[2] = 0; out[3] = 0; out[4] = 0;
    }
}

/* FUN_003cbb9c @ 0x003cbb9c   (est. cL4_mr_emit_Xb)
 * Ghidra: void FUN_003cbb9c(int *param_1,long param_2,undefined8 param_3,int param_4)
 * Marshals a word then emits tag "Xb". Clears result.
 * Confidence: medium
 */
void cL4_mr_emit_Xb(int *out, long ctx, unsigned long desc, int depth)
{
    cL4_mr_wrap1(ctx, desc, (unsigned long)(depth + 1));
    if (*out == 0) {
        cL4_mr_emit(ctx + 0x2140, "Xb", 2, *(unsigned long *)(ctx + 0x2150));
        *out = 0; out[2] = 0; out[3] = 0; out[4] = 0;
    }
}

/* FUN_003cc004 @ 0x003cc004   (est. cL4_mr_char_Z)
 * Ghidra: void FUN_003cc004(int *param_1,long param_2,undefined8 param_3,int param_4)
 * Marshals a word then emits the single tag byte 'Z'. Clears result.
 * Confidence: medium
 */
void cL4_mr_char_Z(int *out, long ctx, unsigned long desc, int depth)
{
    char tag = 0x5a;
    cL4_mr_wrap1(ctx, desc, (unsigned long)(depth + 1));
    if (*out == 0) {
        cL4_mr_emit_char(ctx + 0x2140, &tag, *(unsigned long *)(ctx + 0x2150));
        *out = 0; out[2] = 0; out[3] = 0; out[4] = 0;
    }
}

/* FUN_003cc068 @ 0x003cc068   (est. cL4_mr_emit_Xf)
 * Ghidra: void FUN_003cc068(int *param_1,long param_2,undefined8 param_3,int param_4)
 * Marshals a nested object then emits tag "Xf". Clears result.
 * Confidence: medium
 */
void cL4_mr_emit_Xf(int *out, long ctx, unsigned long desc, int depth)
{
    cL4_mr_wrap3(ctx, desc, (unsigned long)(depth + 1));
    if (*out == 0) {
        cL4_mr_emit(ctx + 0x2140, "Xf", 2, *(unsigned long *)(ctx + 0x2150));
        *out = 0; out[2] = 0; out[3] = 0; out[4] = 0;
    }
}

/* FUN_003cc0c4 @ 0x003cc0c4   (est. cL4_mr_char_t)
 * Ghidra: void FUN_003cc0c4(int *param_1,long param_2,undefined8 param_3,int param_4)
 * Marshals a nested object (cL4_mr_cc324) then emits the tag byte 't'.
 * Confidence: medium
 */
void cL4_mr_char_t(int *out, long ctx, unsigned long desc, int depth)
{
    char tag = 0x74;
    cL4_mr_cc324(out, ctx, (long)desc, (unsigned long)(depth + 1));
    if (*out == 0) {
        cL4_mr_emit_char(ctx + 0x2140, &tag, *(unsigned long *)(ctx + 0x2150));
        *out = 0; out[2] = 0; out[3] = 0; out[4] = 0;
    }
}

/* FUN_003cc128 @ 0x003cc128   (est. cL4_mr_cc324_QP)
 * Ghidra: void FUN_003cc128(int *param_1,long param_2,undefined8 param_3,int param_4)
 * Marshals a nested object via cL4_mr_cc324 then emits tag "QP".
 * Confidence: medium
 */
void cL4_mr_cc324_QP(int *out, long ctx, unsigned long desc, int depth)
{
    cL4_mr_cc324(out, ctx, (long)desc, (unsigned long)(depth + 1));
    if (*out == 0) {
        cL4_mr_emit(ctx + 0x2140, "QP", 2, *(unsigned long *)(ctx + 0x2150));
        *out = 0; out[2] = 0; out[3] = 0; out[4] = 0;
    }
}

/* FUN_003cc184 @ 0x003cc184   (est. cL4_mr_cc324_QSd)
 * Ghidra: void FUN_003cc184(int *param_1,long param_2,undefined8 param_3,int param_4)
 * Marshals a nested object via cL4_mr_cc324 then emits tag "QSd" (3 bytes).
 * Confidence: medium
 */
void cL4_mr_cc324_QSd(int *out, long ctx, unsigned long desc, int depth)
{
    cL4_mr_cc324(out, ctx, (long)desc, (unsigned long)(depth + 1));
    if (*out == 0) {
        cL4_mr_emit(ctx + 0x2140, "QSd", 3, *(unsigned long *)(ctx + 0x2150));
        *out = 0; out[2] = 0; out[3] = 0; out[4] = 0;
    }
}

/* FUN_003cc1e0 @ 0x003cc1e0   (est. cL4_mr_cc324_QSi)
 * Ghidra: void FUN_003cc1e0(int *param_1,long param_2,undefined8 param_3,int param_4)
 * Marshals a nested object via cL4_mr_cc324 then emits tag "QSi" (3 bytes).
 * Confidence: medium
 */
void cL4_mr_cc324_QSi(int *out, long ctx, unsigned long desc, int depth)
{
    cL4_mr_cc324(out, ctx, (long)desc, (unsigned long)(depth + 1));
    if (*out == 0) {
        cL4_mr_emit(ctx + 0x2140, "QSi", 3, *(unsigned long *)(ctx + 0x2150));
        *out = 0; out[2] = 0; out[3] = 0; out[4] = 0;
    }
}

/* FUN_003cc23c @ 0x003cc23c   (est. cL4_mr_op_Qp)
 * Ghidra: void FUN_003cc23c(int *param_1,long param_2,undefined8 param_3,int param_4)
 * Marshals a word then emits tag "Qp". Clears result.
 * Confidence: medium
 */
void cL4_mr_op_Qp(int *out, long ctx, unsigned long desc, int depth)
{
    cL4_mr_wrap2(ctx, desc, (unsigned long)(depth + 1));
    if (*out == 0) {
        cL4_mr_emit(ctx + 0x2140, "Qp", 2, *(unsigned long *)(ctx + 0x2150));
        *out = 0; out[2] = 0; out[3] = 0; out[4] = 0;
    }
}

/* FUN_003cc298 @ 0x003cc298   (est. cL4_mr_op_Qe)
 * Ghidra: void FUN_003cc298(int *param_1,long param_2,undefined8 param_3,int param_4)
 * Marshals MR words 0 and 1, emits tag "Qe". On success clears the result
 * words but leaves out[0] untouched by the caller semantics.
 * Confidence: medium
 */
void cL4_mr_op_Qe(int *out, long ctx, unsigned long desc, int depth)
{
    cL4_mr_op(ctx, desc, 0, (unsigned long)(depth + 1));
    if (*out == 0) {
        cL4_mr_emit(ctx + 0x2140, "Qe", 2, *(unsigned long *)(ctx + 0x2150));
        cL4_mr_op((unsigned long)out, ctx, desc, 1, (unsigned long)(depth + 1));
        if (*out == 0) {
            out[2] = 0; out[3] = 0; out[4] = 0;
        }
    }
}

/* FUN_003cc324 @ 0x003cc324   (est. cL4_mr_cc324)
 * Ghidra: void FUN_003cc324(int *param_1,long param_2,long param_3,int param_4)
 * Marshals all N message-register words of the descriptor (N = kind count: 1,
 * 2, or kind-5 array count), inserting the separator tag '_' between words.
 * If the descriptor kind is invalid, emits 'y' instead. Clears result.
 * Confidence: medium
 */
void cL4_mr_cc324(int *out, long ctx, long desc, int depth)
{
    unsigned char kind;
    unsigned long n, i;
    bool first;
    char c;

    kind = *(unsigned char *)(desc + 0x12);
    n = kind;
    if (kind != 1) {
        if (kind == 5) {
            n = (unsigned long)*(unsigned int *)(desc + 8);
            if (*(unsigned int *)(desc + 8) == 0) goto invalid;
        } else {
            if (kind != 2) {
invalid:
                c = 0x79;                      /* 'y' */
                cL4_mr_emit_char(ctx + 0x2140, &c, *(unsigned long *)(ctx + 0x2150));
                goto done;
            }
            n = 2;
        }
    }
    i = 0;
    first = true;
    do {
        cL4_mr_op((unsigned long)out, ctx, (unsigned long)desc, i, (unsigned long)(depth + 1));
        if (*out != 0) return;
        if (first) {
            c = 0x5f;                          /* '_' */
            cL4_mr_emit_char(ctx + 0x2140, &c, *(unsigned long *)(ctx + 0x2150));
        }
        first = false;
        i = i + 1;
    } while (n != i);
done:
    *out = 0; out[2] = 0; out[3] = 0; out[4] = 0;
}

/* FUN_003cc428 @ 0x003cc428   (est. cL4_mr_char_D)
 * Ghidra: void FUN_003cc428(int *param_1,long param_2,undefined8 param_3,int param_4)
 * Marshals a word then emits the single tag byte 'D'. Clears result.
 * Confidence: medium
 */
void cL4_mr_char_D(int *out, long ctx, unsigned long desc, int depth)
{
    char tag = 0x44;
    cL4_mr_wrap2(ctx, desc, (unsigned long)(depth + 1));
    if (*out == 0) {
        cL4_mr_emit_char(ctx + 0x2140, &tag, *(unsigned long *)(ctx + 0x2150));
        *out = 0; out[2] = 0; out[3] = 0; out[4] = 0;
    }
}

/* FUN_003cc48c @ 0x003cc48c   (est. cL4_mr_char_N)
 * Ghidra: void FUN_003cc48c(int *param_1,long param_2,undefined8 param_3,int param_4)
 * Marshals a word then emits the single tag byte 'N'. Clears result.
 * Confidence: medium
 */
void cL4_mr_char_N(int *out, long ctx, unsigned long desc, int depth)
{
    cL4_mr_wrap1(ctx, desc, (unsigned long)(depth + 1));
    if (*out == 0) {
        cL4_mr_emit(ctx + 0x2140, "N", 1, *(unsigned long *)(ctx + 0x2150));
        *out = 0; out[2] = 0; out[3] = 0; out[4] = 0;
    }
}

/* FUN_003cc4e8 @ 0x003cc4e8   (est. cL4_mr_emit_Ma)
 * Ghidra: void FUN_003cc4e8(int *param_1,long param_2,undefined8 param_3,int param_4)
 * Marshals a word then emits tag "Ma". Clears result.
 * Confidence: medium
 */
void cL4_mr_emit_Ma(int *out, long ctx, unsigned long desc, int depth)
{
    cL4_mr_wrap1(ctx, desc, (unsigned long)(depth + 1));
    if (*out == 0) {
        cL4_mr_emit(ctx + 0x2140, "Ma", 2, *(unsigned long *)(ctx + 0x2150));
        *out = 0; out[2] = 0; out[3] = 0; out[4] = 0;
    }
}

/* FUN_003cc544 @ 0x003cc544   (est. cL4_mr_emit_Mr)
 * Ghidra: void FUN_003cc544(int *param_1,long param_2,undefined8 param_3,int param_4)
 * Marshals a word then emits tag "Mr". Clears result.
 * Confidence: medium
 */
void cL4_mr_emit_Mr(int *out, long ctx, unsigned long desc, int depth)
{
    cL4_mr_wrap1(ctx, desc, (unsigned long)(depth + 1));
    if (*out == 0) {
        cL4_mr_emit(ctx + 0x2140, "Mr", 2, *(unsigned long *)(ctx + 0x2150));
        *out = 0; out[2] = 0; out[3] = 0; out[4] = 0;
    }
}

/* FUN_003cc5a0 @ 0x003cc5a0   (est. cL4_mr_emit_MI)
 * Ghidra: void FUN_003cc5a0(int *param_1,long param_2,undefined8 param_3,int param_4)
 * Marshals a word then emits tag "MI". Clears result.
 * Confidence: medium
 */
void cL4_mr_emit_MI(int *out, long ctx, unsigned long desc, int depth)
{
    cL4_mr_wrap1(ctx, desc, (unsigned long)(depth + 1));
    if (*out == 0) {
        cL4_mr_emit(ctx + 0x2140, "MI", 2, *(unsigned long *)(ctx + 0x2150));
        *out = 0; out[2] = 0; out[3] = 0; out[4] = 0;
    }
}

/* FUN_003cc5fc @ 0x003cc5fc   (est. cL4_mr_emit_Mi)
 * Ghidra: void FUN_003cc5fc(int *param_1,long param_2,undefined8 param_3,int param_4)
 * Marshals a word then emits tag "Mi". Clears result.
 * Confidence: medium
 */
void cL4_mr_emit_Mi(int *out, long ctx, unsigned long desc, int depth)
{
    cL4_mr_wrap1(ctx, desc, (unsigned long)(depth + 1));
    if (*out == 0) {
        cL4_mr_emit(ctx + 0x2140, "Mi", 2, *(unsigned long *)(ctx + 0x2150));
        *out = 0; out[2] = 0; out[3] = 0; out[4] = 0;
    }
}

/* FUN_003cc658 @ 0x003cc658   (est. cL4_mr_emit_Ml)
 * Ghidra: void FUN_003cc658(int *param_1,long param_2,undefined8 param_3,int param_4)
 * Marshals a word then emits tag "Ml". Clears result.
 * Confidence: medium
 */
void cL4_mr_emit_Ml(int *out, long ctx, unsigned long desc, int depth)
{
    cL4_mr_wrap1(ctx, desc, (unsigned long)(depth + 1));
    if (*out == 0) {
        cL4_mr_emit(ctx + 0x2140, "Ml", 2, *(unsigned long *)(ctx + 0x2150));
        *out = 0; out[2] = 0; out[3] = 0; out[4] = 0;
    }
}

/* FUN_003cc6b4 @ 0x003cc6b4   (est. cL4_mr_op_Md)
 * Ghidra: void FUN_003cc6b4(int *param_1,long param_2,undefined8 param_3,int param_4)
 * Marshals a word then emits tag "Md". Clears result.
 * Confidence: medium
 */
void cL4_mr_op_Md(int *out, long ctx, unsigned long desc, int depth)
{
    cL4_mr_wrap2(ctx, desc, (unsigned long)(depth + 1));
    if (*out == 0) {
        cL4_mr_emit(ctx + 0x2140, "Md", 2, *(unsigned long *)(ctx + 0x2150));
        *out = 0; out[2] = 0; out[3] = 0; out[4] = 0;
    }
}

/* FUN_003cc710 @ 0x003cc710   (est. cL4_mr_op_MR)
 * Ghidra: void FUN_003cc710(int *param_1,long param_2,undefined8 param_3,int param_4)
 * Marshals a word then emits tag "MR". Clears result.
 * Confidence: medium
 */
void cL4_mr_op_MR(int *out, long ctx, unsigned long desc, int depth)
{
    cL4_mr_wrap2(ctx, desc, (unsigned long)(depth + 1));
    if (*out == 0) {
        cL4_mr_emit(ctx + 0x2140, "MR", 2, *(unsigned long *)(ctx + 0x2150));
        *out = 0; out[2] = 0; out[3] = 0; out[4] = 0;
    }
}

/* FUN_003cc76c @ 0x003cc76c   (est. cL4_mr_op_ML)
 * Ghidra: void FUN_003cc76c(int *param_1,long param_2,undefined8 param_3,int param_4)
 * Marshals a word then emits tag "ML". Clears result.
 * Confidence: medium
 */
void cL4_mr_op_ML(int *out, long ctx, unsigned long desc, int depth)
{
    cL4_mr_wrap2(ctx, desc, (unsigned long)(depth + 1));
    if (*out == 0) {
        cL4_mr_emit(ctx + 0x2140, "ML", 2, *(unsigned long *)(ctx + 0x2150));
        *out = 0; out[2] = 0; out[3] = 0; out[4] = 0;
    }
}

/* FUN_003cc7c8 @ 0x003cc7c8   (est. cL4_mr_emit_Xw)
 * Ghidra: void FUN_003cc7c8(int *param_1,long param_2,undefined8 param_3,int param_4)
 * Marshals a word then emits tag "Xw". Clears result.
 * Confidence: medium
 */
void cL4_mr_emit_Xw(int *out, long ctx, unsigned long desc, int depth)
{
    cL4_mr_wrap1(ctx, desc, (unsigned long)(depth + 1));
    if (*out == 0) {
        cL4_mr_emit(ctx + 0x2140, "Xw", 2, *(unsigned long *)(ctx + 0x2150));
        *out = 0; out[2] = 0; out[3] = 0; out[4] = 0;
    }
}

/* FUN_003cc824 @ 0x003cc824   (est. cL4_mr_emit_Xo)
 * Ghidra: void FUN_003cc824(int *param_1,long param_2,undefined8 param_3,int param_4)
 * Marshals a word then emits tag "Xo". Clears result.
 * Confidence: medium
 */
void cL4_mr_emit_Xo(int *out, long ctx, unsigned long desc, int depth)
{
    cL4_mr_wrap1(ctx, desc, (unsigned long)(depth + 1));
    if (*out == 0) {
        cL4_mr_emit(ctx + 0x2140, "Xo", 2, *(unsigned long *)(ctx + 0x2150));
        *out = 0; out[2] = 0; out[3] = 0; out[4] = 0;
    }
}

/* FUN_003cc880 @ 0x003cc880   (est. cL4_mr_emit_Xu)
 * Ghidra: void FUN_003cc880(int *param_1,long param_2,undefined8 param_3,int param_4)
 * Marshals a word then emits tag "Xu". Clears result.
 * Confidence: medium
 */
void cL4_mr_emit_Xu(int *out, long ctx, unsigned long desc, int depth)
{
    cL4_mr_wrap1(ctx, desc, (unsigned long)(depth + 1));
    if (*out == 0) {
        cL4_mr_emit(ctx + 0x2140, "Xu", 2, *(unsigned long *)(ctx + 0x2150));
        *out = 0; out[2] = 0; out[3] = 0; out[4] = 0;
    }
}

/* FUN_003cc8dc @ 0x003cc8dc   (est. cL4_mr_dispatch_lu)
 * Ghidra: void FUN_003cc8dc(undefined8 param_1,long *param_2,int param_3)
 * Resolves descriptor payload word and marshals it with tag "lu".
 * Confidence: medium
 */
void cL4_mr_dispatch_lu(unsigned long out, long *desc, int depth)
{
    unsigned long val;
    if (1 < cL4_mr_kind((unsigned long *)desc) - 1) {
        if ((cL4_mr_kind((unsigned long *)desc) != 5) || ((int)desc[1] == 0)) {
            val = 0;
        } else {
            desc = (long *)*desc;
            val = *desc;
        }
    } else {
        val = *desc;
    }
    cL4_mr_tag(out, val, "lu", 2, (unsigned long)(depth + 1));
}

/* FUN_003cc924 @ 0x003cc924   (est. cL4_mr_dispatch_au)
 * Ghidra: void FUN_003cc924(undefined8 param_1,long *param_2,int param_3)
 * Resolves descriptor payload word and marshals it with tag "au".
 * Confidence: medium
 */
void cL4_mr_dispatch_au(unsigned long out, long *desc, int depth)
{
    unsigned long val;
    if (1 < cL4_mr_kind((unsigned long *)desc) - 1) {
        if ((cL4_mr_kind((unsigned long *)desc) != 5) || ((int)desc[1] == 0)) {
            val = 0;
        } else {
            desc = (long *)*desc;
            val = *desc;
        }
    } else {
        val = *desc;
    }
    cL4_mr_tag(out, val, "au", 2, (unsigned long)(depth + 1));
}

/* FUN_003cc96c @ 0x003cc96c   (est. cL4_mr_small_type)
 * Ghidra: void FUN_003cc96c(int *param_1,long param_2,undefined8 *param_3,int param_4)
 * Marshals MR word 1, then maps the descriptor payload's type index (0..0x17)
 * to a two-letter type tag ("al","ca","ta","de","xx","XX","Xx","CP","Cp",
 * "cp","Tk","tk","pr","TK","Cc","Tt","tT","xs","xg","ug","up","ui","et","st")
 * from a string table at 0x5d6f79. Emits 'w' then the tag string. Indices
 * >=0x18 yield an empty tag. Clears result.
 * Confidence: medium
 */
void cL4_mr_small_type(int *out, long ctx, unsigned long *desc, int depth)
{
    static const char *small_tags[24] = {
        "al","ca","ta","de","xx","XX","Xx","CP","Cp","cp","Tk","tk","pr",
        "TK","Cc","Tt","tT","xs","xg","ug","up","ui","et","st"
    };
    unsigned long *p;
    const char *tag;
    unsigned long taglen;
    bool big;
    char w = 0x77;                             /* 'w' */
    unsigned long slot = *(unsigned long *)(ctx + 0x2150);

    cL4_mr_op(ctx, desc, 1, (unsigned long)(depth + 1));
    if (*out == 0) {
        p = desc;
        if (1 < cL4_mr_kind((unsigned long *)desc) - 1) {
            p = (unsigned long *)*desc;
        }
        if (*(unsigned int *)*p < 0x18) {
            tag = small_tags[*(unsigned int *)*p];
            big = false;
        } else {
            tag = 0;
            big = true;
        }
        cL4_mr_emit_char(ctx + 0x2140, &w, slot);
        if (big) taglen = 0;
        else taglen = cL4_strlen(tag);
        cL4_mr_emit(ctx + 0x2140, tag, taglen, slot);
        *out = 0; out[2] = 0; out[3] = 0; out[4] = 0;
    }
}

/* FUN_003ccc3c @ 0x003ccc3c   (est. cL4_mr_emit_WV)
 * Ghidra: void FUN_003ccc3c(int *param_1,long param_2,undefined8 param_3,int param_4)
 * Marshals a word then emits tag "WV". Clears result.
 * Confidence: medium
 */
void cL4_mr_emit_WV(int *out, long ctx, unsigned long desc, int depth)
{
    cL4_mr_wrap1(ctx, desc, (unsigned long)(depth + 1));
    if (*out == 0) {
        cL4_mr_emit(ctx + 0x2140, "WV", 2, *(unsigned long *)(ctx + 0x2150));
        *out = 0; out[2] = 0; out[3] = 0; out[4] = 0;
    }
}

/* FUN_003ccc98 @ 0x003ccc98   (est. cL4_mr_op_TV)
 * Ghidra: void FUN_003ccc98(int *param_1,long param_2,undefined8 param_3,int param_4)
 * Marshals a word then emits tag "TV". Clears result.
 * Confidence: medium
 */
void cL4_mr_op_TV(int *out, long ctx, unsigned long desc, int depth)
{
    cL4_mr_wrap2(ctx, desc, (unsigned long)(depth + 1));
    if (*out == 0) {
        cL4_mr_emit(ctx + 0x2140, "TV", 2, *(unsigned long *)(ctx + 0x2150));
        *out = 0; out[2] = 0; out[3] = 0; out[4] = 0;
    }
}

/* FUN_003cbfbc @ 0x003cbfbc   (est. cL4_mr_dispatch_r2)
 * Ghidra: void FUN_003cbfbc(undefined8 param_1,long *param_2,int param_3)
 * Resolves descriptor payload word and marshals it with tag 'r' (DAT_005d6fd3).
 * Confidence: medium
 */
void cL4_mr_dispatch_r2(unsigned long out, long *desc, int depth)
{
    unsigned long val;
    if (1 < cL4_mr_kind((unsigned long *)desc) - 1) {
        if ((cL4_mr_kind((unsigned long *)desc) != 5) || ((int)desc[1] == 0)) {
            val = 0;
        } else {
            desc = (long *)*desc;
            val = *desc;
        }
    } else {
        val = *desc;
    }
    cL4_mr_tag(out, val, "r", 1, (unsigned long)(depth + 1));
}

/* FUN_003cbbf8 @ 0x003cbbf8   (est. cL4_mr_descriptor_e0)
 * Ghidra: void FUN_003cbbf8(int *param_1,undefined8 *param_2,long *param_3,int param_4)
 * Handles a descriptor whose payload tag is 0xe0. Walks the element array and
 * for each 0xe1/e2-tagged element that is a 0xf4 reference, marshals an
 * object-field chain via cL4_obj_get / cL4_obj_set into the message object at
 * ctx[0] (field tags 0xf7, 0x80, 0xf4), then marshals the accumulated object
 * via cL4_mr_cc324. For a kind-5 descriptor of 3 words it also dispatches on
 * the payload at +8 (tag 0x2c) and +0x10 (tag 0xf7) via cL4_mr_chain, and
 * writes the "XX"/"Xx" state string into ctx+0x428. On invalid descriptors
 * sets out[0]=1 and out[4] to 0xebf..0xede.
 * Confidence: medium
 */
void cL4_mr_descriptor_e0(int *out, unsigned long *ctx, long *desc, int depth)
{
    unsigned int kind, ek, cnt;
    unsigned long i, span_cnt;
    unsigned long *arr, *inner;
    long *d, *e, *e2p;
    unsigned long obj, obj80, v;
    long elen, fv;
    bool is_arr;
    const unsigned char *st;
    unsigned int err, ecode;

    kind = (unsigned int)cL4_mr_kind((unsigned long *)desc);
    d = desc;
    if (kind == 1) {
chk_e0:
        if (*(short *)(*d + 0x10) == 0xe0) {
            d = desc;
            if (kind - 1 < 2) {
                arr = (unsigned long *)*d;
            } else {
                if ((cL4_mr_kind((unsigned long *)desc) == 5) && ((int)desc[1] != 0)) { d = (long *)*desc; arr = (unsigned long *)*d; }
                else arr = 0;
            }
            obj = cL4_obj_get(*ctx, 0xf7);
            ek = cL4_mr_kind((unsigned long *)arr);
            kind = ek;
            if (ek == 1) {
                i = 0;
                do {
                    ek = cL4_mr_kind((unsigned long *)arr);
                    span_cnt = (unsigned long)ek;
                    is_arr = 1 < ek - 1;
                    inner = arr;
                    if (is_arr) inner = (unsigned long *)*arr;
                    if (*(short *)(inner[i] + 0x10) != 0xe2) {
                        inner = arr;
                        if (is_arr) inner = (unsigned long *)*arr;
                        if (*(short *)(inner[i] + 0x10) != 0xe1) {
                            if (ek == 1) {
                                if (span_cnt <= i) { desc = 0; }
                                else {
                                    if (is_arr) arr = (unsigned long *)*arr;
                                    desc = (long *)arr[i];
                                }
                            } else {
                                if (ek == 5) span_cnt = (unsigned long)*(unsigned int *)(arr + 1);
                                else if (ek == 2) span_cnt = 2;
                                else { desc = 0; }
                                if (span_cnt <= i) desc = 0;
                                else {
                                    if (is_arr) arr = (unsigned long *)*arr;
                                    desc = (long *)arr[i];
                                }
                            }
                            ecode = 0xec8;
                            err = 1; desc = 0;
                            goto res;
                        }
                    }
                    if (ek == 1) {
                        if (span_cnt <= i) { e = 0; }
                        else {
                            inner = arr;
                            if (is_arr) inner = (unsigned long *)*arr;
                            e = (long *)inner[i];
                        }
                    } else {
                        if (ek == 5) span_cnt = (unsigned long)*(unsigned int *)(arr + 1);
                        else if (ek == 2) span_cnt = 2;
                        else { e = 0; }
                        if (span_cnt <= i) e = 0;
                        else {
                            if (is_arr) arr = (unsigned long *)*arr;
                            e = (long *)arr[i];
                        }
                    }
                    cnt = (unsigned int)cL4_mr_kind((unsigned long *)e);
                    e2p = e;
                    if (cnt != 1) {
                        if ((cnt == 5) && ((int)e[1] == 1)) { e2p = (long *)*e; goto f4chk; }
                        ecode = 0xecc; err = 1; desc = 0; goto res;
                    }
f4chk:
                    if (*(short *)(*e2p + 0x10) != 0xf4) { ecode = 0xecc; err = 1; desc = 0; goto res; }
                    e2p = e;
                    if (cnt - 1 < 2) {
                        inner = (unsigned long *)*e2p;
                    } else {
                        if ((cL4_mr_kind((unsigned long *)e) == 5) && ((int)e[1] != 0)) { e2p = (long *)*e; inner = (unsigned long *)*e2p; }
                        else inner = 0;
                    }
                    if ((short)e[2] == 0xe1) {
                        obj80 = cL4_obj_get(*ctx, 0x80);
                        if (cL4_mr_kind((unsigned long *)inner) - 1 < 2) {
                            v = *inner;
                        } else {
                            if ((cL4_mr_kind((unsigned long *)inner) == 5) && (*(int *)(inner + 1) != 0)) { inner = (unsigned long *)*inner; v = *inner; }
                            else v = 0;
                        }
                        cL4_obj_set(obj80, v, *ctx);
                        inner = (unsigned long *)cL4_obj_get(*ctx, 0xf4);
                        cL4_obj_set((unsigned long)inner, obj80, *ctx);
                    }
                    cL4_obj_set(obj, (unsigned long)inner, *ctx);
                    i = i + 1;
                } while (kind != i);
            }
            else if (ek == 5) {
                kind = *(unsigned int *)(arr + 1);
                if (kind != 0) goto loop5;
            }
            else if (ek == 2) goto loop5;
            goto after_loop;
loop5:
            i = 0;
            cnt = kind;
            do {
                inner = (unsigned long *)*arr;
                e = (long *)inner[i];
                if (cL4_mr_kind((unsigned long *)e) == 1 && *(short *)(*e + 0x10) == 0xf4) {
                    if (i >= cnt) e = 0;
                    else e = (long *)((unsigned long *)*arr)[i];
                    if (cL4_mr_kind((unsigned long *)e) == 1 && *(short *)(*e + 0x10) == 0xf4) {
                        e2p = e;
                        inner = (unsigned long *)*e2p;
                        if ((short)e[2] == 0xe1) {
                            obj80 = cL4_obj_get(*ctx, 0x80);
                            if (cL4_mr_kind((unsigned long *)inner) - 1 < 2) v = *inner;
                            else {
                                if ((cL4_mr_kind((unsigned long *)inner) == 5) && (*(int *)(inner + 1) != 0)) { inner = (unsigned long *)*inner; v = *inner; }
                                else v = 0;
                            }
                            cL4_obj_set(obj80, v, *ctx);
                            inner = (unsigned long *)cL4_obj_get(*ctx, 0xf4);
                            cL4_obj_set((unsigned long)inner, obj80, *ctx);
                        }
                        cL4_obj_set(obj, (unsigned long)inner, *ctx);
                    }
                }
                i = i + 1;
            } while (i < cnt);
after_loop:
            cL4_mr_cc324(out, (long)ctx, (long)obj, (unsigned long)(depth + 1));
            if (*out != 0) return;
            if ((*(char *)((char *)desc + 0x12) != '\x05') || ((int)desc[1] != 3)) {
                st = (const unsigned char *)0x5d6f8b;   /* "Xx" */
                cL4_mr_emit((unsigned long)ctx + 0x428, st, 2, ctx[0x42a]);
                err = 0; ecode = 0; desc = 0;
                goto res;
            }
            elen = *(long *)(*desc + 8);
            if (*(short *)(elen + 0x10) == 0x2c) {
                fv = *(long *)(*desc + 0x10);
                if (*(short *)(fv + 0x10) == 0xf7) {
                    cL4_mr_cc324(out, (long)ctx, (long)fv, (unsigned long)(depth + 1));
                    if (*out != 0) return;
                    cL4_mr_chain((unsigned long)out, (unsigned long)ctx, (unsigned long)elen, (unsigned long)(depth + 1));
                    if (*out != 0) return;
                    st = (const unsigned char *)0x5d6f88;   /* "XX" */
                    cL4_mr_emit((unsigned long)ctx + 0x428, st, 2, ctx[0x42a]);
                    err = 0; ecode = 0; desc = 0;
                    goto res;
                }
                ecode = 0xede;
            } else {
                ecode = 0xedd;
            }
        } else {
            ecode = 0xec1;
        }
    } else {
        if ((kind == 5) && ((*(unsigned int *)(desc + 1) | 2) == 3)) {
            d = (long *)*desc;
            goto chk_e0;
        }
        ecode = 0xebf;
    }
    err = 1;
    desc = 0;
    goto res;
res:
    *out = (int)err;
    *(long *)(out + 2) = (long)desc;
    out[4] = (int)ecode;
}

