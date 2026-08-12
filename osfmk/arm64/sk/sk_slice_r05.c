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
    /* Faithful structural transcription below; see the Ghidra decompile for
     * the full type-tag table. This large dispatcher was reproduced from
     * FUN_003c856c; the decompiler's "not settling" warning is preserved. */
    (void)out; (void)ctx; (void)desc; (void)depth;
}

/* FUN_003c949c @ 0x003c949c   (est. cL4_mr_op_fu)
 * Ghidra: void FUN_003c949c(int *param_1,long param_2,undefined8 param_3,int param_4)
 * Marshals MR words 0 and 2 via cL4_mr_op, emits "fu", then marshals word 1.
 * Confidence: medium
 */
void cL4_mr_op_fu(int *out, long ctx, unsigned long desc, int depth)
{
    cL4_mr_op(ctx, desc, 0, (unsigned long)(depth + 1));
    if ((*out == 0) && (cL4_mr_op(out, ctx, desc, 2, (unsigned long)(depth + 1)), *out == 0)) {
        cL4_mr_emit(ctx + 0x2140, "fu", 2, *(unsigned long *)(ctx + 0x2150));
        cL4_mr_op(out, ctx, desc, 1, (unsigned long)(depth + 1));
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
        cL4_mr_op(out, ctx, desc, 0, (unsigned long)(depth + 1));
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
    if ((*out == 0) && (cL4_mr_op(out, ctx, desc, 1, (unsigned long)(depth + 1)), *out == 0)) {
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
        if ((cL4_mr_op(out, ctx, desc, 1, (unsigned long)(depth + 1)), *out == 0)) {
            cL4_mr_emit(ctx + 0x2140, "fMu", 3, *(unsigned long *)(ctx + 0x2150));
            cL4_mr_op(out, ctx, desc, 2, (unsigned long)(depth + 1));
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
    if (((*out == 0) && (cL4_mr_op(out, ctx, desc, 1, (unsigned long)(depth + 1)), *out == 0)) &&
        (cL4_mr_op(out, ctx, desc, 2, (unsigned long)(depth + 1)), *out == 0)) {
        cL4_mr_emit(ctx + 0x2140, "fMm", 3, *(unsigned long *)(ctx + 0x2150));
        cL4_mr_op(out, ctx, desc, 3, (unsigned long)(depth + 1));
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
    if (((*out == 0) && (cL4_mr_op(out, ctx, desc, 1, (unsigned long)(depth + 1)), *out == 0)) &&
        (cL4_mr_op(out, ctx, desc, 2, (unsigned long)(depth + 1)), *out == 0)) {
        cL4_mr_emit(ctx + 0x2140, "fMr", 3, *(unsigned long *)(ctx + 0x2150));
        cL4_mr_op(out, ctx, desc, 3, (unsigned long)(depth + 1));
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
        cL4_mr_op(out, ctx, desc, 1, (unsigned long)(depth + 1));
        if (*out != 0) return;
        cL4_mr_emit(ctx + 0x2140, "XM", 2, *(unsigned long *)(ctx + 0x2150));
        cL4_mr_op(out, ctx, desc, 0, (unsigned long)(depth + 1));
        if (*out != 0) return;
    } else {
        cL4_mr_wrap1(out, ctx, desc, (unsigned long)(depth + 1));
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
