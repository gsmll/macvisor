/* Recreated from exclavecore_bundle.t8142.RELEASE.im4p (cL4 Secure Kernel,
 * arm64e, image base 0) — the cL4 (Apple seL4-derived) microkernel (GL1),
 * "cL4 (679.100.61)".
 * Ground truth: Ghidra FUN_ names + addresses in program cl4_kernel.raw.
 * All names are estimates unless string/header-matched.
 *
 * Slice 17: 0x000e0000-0x000e341c — the RegionResource / memory-region
 * resource subsystem (boot memory regions, component lookup, resource object
 * methods, bitmap/min-max search helpers, MMIO untyped resolution, ASan
 * shadow/dylib handling).
 *
 * SeL4/cL4 vocabulary is used for naming. Confidence is medium unless a
 * string matches. GENTER/GEXIT and SoftwareBreakpoint render as comments. */

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#include "sk_internal.h"

/* ------------------------------------------------------------------ *
 * Shared message-buffer shape: 6 words + 1 status byte (49 bytes). Used
 * by the resource-method dispatch wrappers to marshal an IPC-style message
 * through a vtable slot.
 * ------------------------------------------------------------------ */
typedef struct __attribute__((packed)) {
    uint64_t w[6];
    uint8_t  b;
} cl4_msg49_t;

/* Leading-zero count over the two 32-bit halves swapped — the code searches
 * bit positions with a half-swap before counting (used by bitmap finders). */
static inline unsigned clz64_swapped(uint64_t x)
{
    return x ? __builtin_clzll(((x >> 32) | (x << 32))) : 64;
}

/* Bitmap search scratch (filled by thunk_FUN_0006afb4, released by
 * FUN_000e4614): a bitmap word array, the current word index, the total
 * size, and a parallel value array indexed by bit position at +0x30. */
typedef struct {
    uint64_t field0;   /* +0x00 */
    uint64_t field8;   /* +0x08 */
    uint64_t cur_word; /* +0x10 (uStack_38) */
    uint64_t size;     /* +0x18 (lStack_48) */
    uint64_t bitmap;   /* +0x20 (local_50) */
    uint64_t word_idx; /* +0x28 (local_40) */
    uint64_t values;   /* +0x30 */
} sk_bitmap_scratch_t;

/* ------------------------------------------------------------------ *
 * Out-of-range cL4 globals (declared extern; owned by the range workers
 * that own their addresses).
 * ------------------------------------------------------------------ */
/* 0x657778 — scratch RegionResource object used as a "found element" slot. */
extern uint64_t DAT_00657778[];
/* 0x657788 — element count of the global search scratch array. */
extern uint64_t DAT_00657788;
/* 0x657790 — capacity of the global search scratch array. */
extern uint64_t DAT_00657790;
/* 0x657798 — global search scratch array (indexed by DAT_00657788). */
extern uint64_t DAT_00657798[];
/* 0x4c29c0 / 0x4c2a88 — two lookup tables (byte-indexed). */
extern uint64_t DAT_004c29c0[];
extern uint64_t DAT_004c2a88[];
/* 0x4baeb0 / 0x4baeb8 — adjacent global words copied into a fresh object. */
extern uint64_t DAT_004baeb0;
extern uint64_t DAT_004baeb8;
/* 0x7bf58 — a data/type-name label used as a {name, obj} return. */
extern uint8_t DAT_0007bf58;
/* 0x4c2600 — array-allocator tag table. */
extern uint64_t DAT_004c2600[];

/* ------------------------------------------------------------------ *
 * Out-of-slice cL4 helpers (declared extern with one-line notes; bodies are
 * reconstructed by the range workers that own them). Calls use old-style
 * unspecified-argument prototypes where the binary passes differing arg
 * counts (the decompiler drops trailing registers).
 * ------------------------------------------------------------------ */
extern void  FUN_00087150(void);
extern void  FUN_0036b6ac();               /* release/teardown (0-3 args) */
extern void  FUN_0036a1a0();               /* ref/lock acquire (0-3 args) */
extern void  FUN_0036a20c();               /* ref/lock release partner of a1a0 */
extern void* FUN_0036a940();               /* allocate object (0-3 args) */
extern uint64_t thunk_FUN_0036b270();      /* object retain (1 arg) */
extern void  FUN_0036b118();               /* object release (1-2 args) */
extern void  FUN_0036b588();               /* object release variant */
extern void  FUN_0036b6f4(void);
extern void  FUN_0036b270();               /* retain helper at 0x36b270 */
extern void  FUN_0036993c();               /* message/log emit (4 args) */
extern void  FUN_0036986c(void);           /* complete/commit message */
extern void* FUN_0036a9a0();               /* alloc with tag (2-3 args) */
extern uint64_t FUN_002a0cf8();            /* string/word compare (0-5 args) */
extern uint64_t FUN_002abe60();            /* string-prefix compare helper */
extern void  thunk_FUN_002acbb8();         /* printf-style output (0-2 args) */
extern void  FUN_003a25d4();               /* print 64-bit hex (1 arg) */
extern uint64_t FUN_003a261c(uint64_t);    /* realloc/validate array */
extern void  FUN_0009455c(uint64_t);       /* ref/init object at +0x28 */
extern void  FUN_000dfb64(void);
extern void  FUN_000dfb6c(void);
extern void  FUN_000dfb74(void);
extern void  FUN_000dfb7c(void);
extern void  FUN_000df928(void);
extern void  FUN_000df970(void);
extern int   FUN_0006e6dc(void);
extern uint32_t FUN_0008cc7c(uint32_t, uint32_t);
extern void  FUN_00077770(uint64_t);       /* invoke code pointer (0x651428/0x651518) */
extern uint64_t FUN_000027e8();            /* fetch current object/vtable base (x16) */
extern uint64_t FUN_0008e328();            /* fetch current object/vtable base (x16) */
extern uint64_t FUN_0008e0d4(void);        /* allocate object handle */
extern uint64_t FUN_000bd4f0(void);        /* allocate region resource */
extern uint64_t FUN_00096f78(uint64_t);    /* resolve dispatch/function pointer */
extern uint64_t FUN_00027724(uint64_t);    /* resolve global function pointer */
extern void  FUN_0001e790(void);
extern void  FUN_000bde98(void);           /* print hex value (1 arg) */
extern void  FUN_001e9c00();               /* serialize buffer (1 arg) */
extern void  FUN_0011d7e8();               /* noreturn stack-protector handler */
extern cl4_result_t FUN_00160888();        /* construct pair (5 args) */
extern cl4_result_t FUN_00163b38();        /* construct pair (6 args) */
extern void  FUN_000fdd78(uint8_t *);      /* init scratch buffer */
extern int   FUN_000a9ae8(uint8_t *);      /* check scratch buffer state */
extern void  FUN_000aa3ac(void);
extern void  FUN_000e46ec(void);           /* resource list lock acquire */
extern void  FUN_000e46d0(uint64_t);       /* consume found element value */
extern void  FUN_000e46d8(void);           /* resource list lock release */
extern void  FUN_000e46a4(void);
extern void  FUN_000e4614(uint64_t *);     /* release bitmap scratch */
extern void  FUN_000e37ec(uint64_t, uint64_t); /* grow/append array */
extern void  FUN_00082484(int, uint64_t, int);  /* grow scratch array (bounds) */
extern uint64_t FUN_0039f9e8(uint64_t *, uint64_t, int); /* refcount overflow alloc */
extern void  FUN_0010562c(uint64_t, uint64_t); /* register resource under name */
extern void  FUN_00068e14(void);           /* empty-list handling */
extern uint64_t FUN_000a6fe0(uint64_t);    /* fetch list object (x8) */
extern void  FUN_001dd77c(void);
extern uint64_t FUN_00002834(uint64_t);    /* assert/panic helper */
extern void  FUN_000867a8(uint64_t, void *); /* snapshot/lock array region */
extern uint64_t FUN_000e3eb4(uint64_t, uint64_t, uint64_t); /* alloc array */
extern void  thunk_FUN_00114330(void *, uint64_t); /* zero-fill */
extern uint64_t FUN_0007bea4(uint64_t);    /* array normalize/compact */
extern void  FUN_001b9084(void *, uint64_t, uint64_t); /* append name pair */
extern void  FUN_001a84f4(void *, uint64_t); /* init resource builder */
extern void  FUN_001a8564(void);           /* commit/publish builder */
extern uint64_t FUN_0001a1c8();            /* destroy resource (5 args) */
extern uint64_t FUN_0014b1f8();            /* destroy resource variant */
extern void  FUN_004b23d8(void);
extern void  FUN_00117cc4(uint64_t, void *, uint64_t); /* copy result buffer */
extern uint64_t FUN_0006cf50(uint64_t);    /* find MMIO untyped for paddr */
extern uint64_t FUN_0006d024(uint64_t);    /* paddr base/cap query */
extern uint64_t FUN_001000b8(uint64_t);    /* resolve boot region */
extern uint64_t FUN_000fd41c(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t FUN_000aa6d0(uint64_t);    /* alloc handle */
extern uint64_t FUN_000ec964(uint64_t);    /* alloc handle */
extern uint64_t FUN_0006f800(uint64_t);    /* alloc handle */
extern void  FUN_002a4ab4(uint64_t);       /* debug/trace op (1 arg) */
extern void  FUN_0026b434(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t); /* format */
extern uint64_t FUN_00002688(void);
extern void  thunk_FUN_0006afb4(uint64_t *); /* init bitmap scratch */
extern void  FUN_001ebfb0(void);
extern void  FUN_000df114(void);
extern void  FUN_000df77c(void);

/* Forward declarations for in-slice functions used before their definition
 * (Ghidra order has thin forwarding stubs before the bodies they forward to). */
extern void FUN_000e16ec(uint64_t *out);
extern cl4_result_t FUN_000e174c(void);
extern long FUN_000e18a0(uint64_t, uint64_t, uint64_t *, uint64_t);
extern void FUN_000e1c90(uint64_t *, uint64_t);
extern void FUN_000e1d24(void);
extern void FUN_000e2fc4(uint64_t);
extern void FUN_000e1fa4(void);
extern void FUN_000e1f74(void);
extern void FUN_000e1fb4(void);
extern void FUN_000e1fc4(void);
extern cl4_result_t FUN_000e250c(uint64_t *);
extern cl4_result_t FUN_000e254c(uint64_t *);
extern cl4_result_t FUN_000e258c(uint64_t *);
extern void FUN_000e25d8(uint64_t *);
extern uint32_t FUN_000e2618(uint64_t *);

/* ------------------------------------------------------------------ *
 * RegionResource / memory-region resource methods (slice 17).
 * ------------------------------------------------------------------ */

/* FUN_000e085c @ 0x000e085c   (est. resource_named_ref_get)
 * Ghidra: undefined1 [16] FUN_000e085c(void)
 * Returns a {name-label, object} pair: it acquires/initializes the object
 * stored at this->+0x28 (via FUN_0009455c) and returns that object pointer
 * tagged with the static label DAT_0007bf58.
 * Confidence: medium
 * Notes: unaff_x20 = this; DAT_0007bf58 is a data/type label. */
cl4_result_t FUN_000e085c(void)
{
    uint64_t this_obj;            /* unaff_x20 */
    cl4_result_t r;

    this_obj = 0;                 /* caller-supplied this (unaff_x20) */
    FUN_0009455c(this_obj + 0x28);
    r.lo = (uint64_t)(uintptr_t)&DAT_0007bf58;
    r.hi = this_obj + 0x28;
    return r;
}

/* FUN_000e08a0 @ 0x000e08a0   (est. resource_release_teardown)
 * Ghidra: void FUN_000e08a0(void)
 * Runs the shared resource teardown: FUN_00087150() then the release step
 * FUN_0036b6ac(). Identical body to FUN_000e08a4.
 * Confidence: medium */
void FUN_000e08a0(void)
{
    FUN_00087150();
    FUN_0036b6ac();
}

/* FUN_000e08a4 @ 0x000e08a4   (est. resource_release_teardown2)
 * Ghidra: void FUN_000e08a4(void)
 * Same teardown sequence as FUN_000e08a0 (FUN_00087150 + FUN_0036b6ac).
 * Confidence: medium */
void FUN_000e08a4(void)
{
    FUN_00087150();
    FUN_0036b6ac();
}

/* FUN_000e08c8 @ 0x000e08c8   (est. resource_vt_e8)
 * Ghidra: void FUN_000e08c8(void)
 * Calls the resource vtable slot at +0xe8 with no arguments.
 * Confidence: medium */
void FUN_000e08c8(void)
{
    void *this_obj;              /* unaff_x20 */
    void *vtable;

    this_obj = 0;
    vtable = *(void **)this_obj;
    ((void (*)(void))*(void **)((uintptr_t)vtable + 0xe8))();
}

/* FUN_000e0904 @ 0x000e0904   (est. resource_op_vt78)
 * Ghidra: void FUN_000e0904(undefined8 *param_1, undefined8 *param_2)
 * Marshals the 49-byte message in param_2 into a local, dispatches the
 * resource vtable slot at +0x78 with (out, msg), and on success copies the
 * resulting 49-byte message back into param_1.
 * Confidence: medium */
void FUN_000e0904(cl4_msg49_t *out, const cl4_msg49_t *in)
{
    void *this_obj;              /* unaff_x20 */
    void *vtable;
    int success;                 /* unaff_x21 */
    cl4_msg49_t local;
    cl4_msg49_t result;

    this_obj = 0;
    local.w[0] = in->w[0];
    local.w[1] = in->w[1];
    local.w[2] = in->w[2];
    local.w[3] = in->w[3];
    local.w[4] = in->w[4];
    local.w[5] = in->w[5];
    local.b   = in->b;
    vtable = *(void **)this_obj;
    ((void (*)(cl4_msg49_t *, cl4_msg49_t *))*(void **)((uintptr_t)vtable + 0x78))(&result, &local);
    if (success == 0) {
        out->w[0] = result.w[0];
        out->w[1] = result.w[1];
        out->w[2] = result.w[2];
        out->w[3] = result.w[3];
        out->w[4] = result.w[4];
        out->w[5] = result.w[5];
        out->b    = result.b;
    }
}

/* FUN_000e098c @ 0x000e098c   (est. resource_op_vt80)
 * Ghidra: void FUN_000e098c(undefined8 *param_1, undefined8 *param_2, ...)
 * Marshals param_3's message, dispatches vtable slot +0x80 with two out
 * buffers, and on success copies the two resulting messages into param_1 and
 * param_2.
 * Confidence: medium
 * Notes: Verified vs decompile: 49B marshal, vtable +0x80 dispatch
 *   (out,msg,p4,p5), copy r1->out1 / r2->out2 on success. unaff_x20 this
 *   rendered as 0 (opaque); success=unaff_x21 uninitialized per decompile. */
void FUN_000e098c(cl4_msg49_t *out1, cl4_msg49_t *out2,
                  const cl4_msg49_t *in, uint64_t p4, uint64_t p5)
{
    void *this_obj;              /* unaff_x20 */
    void *vtable;
    int success;                 /* unaff_x21 */
    cl4_msg49_t local;
    cl4_msg49_t r1;
    cl4_msg49_t r2;

    this_obj = 0;
    local.w[0] = in->w[0];
    local.w[1] = in->w[1];
    local.w[2] = in->w[2];
    local.w[3] = in->w[3];
    local.w[4] = in->w[4];
    local.w[5] = in->w[5];
    local.b   = in->b;
    vtable = *(void **)this_obj;
    ((void (*)(cl4_msg49_t *, cl4_msg49_t *, uint64_t, uint64_t))
        *(void **)((uintptr_t)vtable + 0x80))(&r1, &local, p4, p5);
    if (success == 0) {
        out1->w[0] = r1.w[0];
        out1->w[1] = r1.w[1];
        out1->w[2] = r1.w[2];
        out1->w[3] = r1.w[3];
        out1->w[4] = r1.w[4];
        out1->w[5] = r1.w[5];
        out1->b    = r1.b;
        out2->w[0] = r2.w[0];
        out2->w[1] = r2.w[1];
        out2->w[2] = r2.w[2];
        out2->w[3] = r2.w[3];
        out2->w[4] = r2.w[4];
        out2->w[5] = r2.w[5];
        out2->b    = r2.b;
    }
}

/* FUN_000e0a40 @ 0x000e0a40   (est. resource_op_vt88)
 * Ghidra: void FUN_000e0a40(undefined8 *param_1, undefined8 *param_2)
 * Same shape as FUN_000e0904 but dispatches vtable slot +0x88.
 * Confidence: medium */
void FUN_000e0a40(cl4_msg49_t *out, const cl4_msg49_t *in)
{
    void *this_obj;              /* unaff_x20 */
    void *vtable;
    int success;                 /* unaff_x21 */
    cl4_msg49_t local;
    cl4_msg49_t result;

    this_obj = 0;
    local.w[0] = in->w[0];
    local.w[1] = in->w[1];
    local.w[2] = in->w[2];
    local.w[3] = in->w[3];
    local.w[4] = in->w[4];
    local.w[5] = in->w[5];
    local.b   = in->b;
    vtable = *(void **)this_obj;
    ((void (*)(cl4_msg49_t *, cl4_msg49_t *))*(void **)((uintptr_t)vtable + 0x88))(&result, &local);
    if (success == 0) {
        out->w[0] = result.w[0];
        out->w[1] = result.w[1];
        out->w[2] = result.w[2];
        out->w[3] = result.w[3];
        out->w[4] = result.w[4];
        out->w[5] = result.w[5];
        out->b    = result.b;
    }
}

/* FUN_000e0ac8 @ 0x000e0ac8   (est. resource_op_vt90)
 * Ghidra: void FUN_000e0ac8(undefined8 *param_1, undefined8 *param_2)
 * Same shape as FUN_000e0904 but dispatches vtable slot +0x90.
 * Confidence: medium */
void FUN_000e0ac8(cl4_msg49_t *out, const cl4_msg49_t *in)
{
    void *this_obj;              /* unaff_x20 */
    void *vtable;
    int success;                 /* unaff_x21 */
    cl4_msg49_t local;
    cl4_msg49_t result;

    this_obj = 0;
    local.w[0] = in->w[0];
    local.w[1] = in->w[1];
    local.w[2] = in->w[2];
    local.w[3] = in->w[3];
    local.w[4] = in->w[4];
    local.w[5] = in->w[5];
    local.b   = in->b;
    vtable = *(void **)this_obj;
    ((void (*)(cl4_msg49_t *, cl4_msg49_t *))*(void **)((uintptr_t)vtable + 0x90))(&result, &local);
    if (success == 0) {
        out->w[0] = result.w[0];
        out->w[1] = result.w[1];
        out->w[2] = result.w[2];
        out->w[3] = result.w[3];
        out->w[4] = result.w[4];
        out->w[5] = result.w[5];
        out->b    = result.b;
    }
}

/* FUN_000e0b50 @ 0x000e0b50   (est. resource_op_vt98)
 * Ghidra: void FUN_000e0b50(undefined8 *param_1)
 * Dispatches vtable slot +0x98 with a single out buffer; on success copies
 * the resulting 49-byte message into param_1.
 * Confidence: medium */
void FUN_000e0b50(cl4_msg49_t *out)
{
    void *this_obj;              /* unaff_x20 */
    void *vtable;
    int success;                 /* unaff_x21 */
    cl4_msg49_t result;

    this_obj = 0;
    vtable = *(void **)this_obj;
    ((void (*)(cl4_msg49_t *))*(void **)((uintptr_t)vtable + 0x98))(&result);
    if (success == 0) {
        out->w[0] = result.w[0];
        out->w[1] = result.w[1];
        out->w[2] = result.w[2];
        out->w[3] = result.w[3];
        out->w[4] = result.w[4];
        out->w[5] = result.w[5];
        out->b    = result.b;
    }
}

/* FUN_000e0bbc @ 0x000e0bbc   (est. resource_op_vtA0)
 * Ghidra: void FUN_000e0bbc(undefined8 *param_1)
 * Marshals param_1's message into a local and dispatches vtable slot +0xa0
 * (no result copied back).
 * Confidence: medium */
void FUN_000e0bbc(cl4_msg49_t *msg)
{
    void *this_obj;              /* unaff_x20 */
    void *vtable;
    cl4_msg49_t local;

    this_obj = 0;
    local.w[0] = msg->w[0];
    local.w[1] = msg->w[1];
    local.w[2] = msg->w[2];
    local.w[3] = msg->w[3];
    local.w[4] = msg->w[4];
    local.w[5] = msg->w[5];
    local.b   = msg->b;
    vtable = *(void **)this_obj;
    ((void (*)(cl4_msg49_t *))*(void **)((uintptr_t)vtable + 0xa0))(&local);
}

/* FUN_000e0c1c @ 0x000e0c1c   (est. resource_op_vtA8)
 * Ghidra: void FUN_000e0c1c(undefined8 *param_1)
 * Same shape as FUN_000e0bbc but dispatches vtable slot +0xa8.
 * Confidence: medium */
void FUN_000e0c1c(cl4_msg49_t *msg)
{
    void *this_obj;              /* unaff_x20 */
    void *vtable;
    cl4_msg49_t local;

    this_obj = 0;
    local.w[0] = msg->w[0];
    local.w[1] = msg->w[1];
    local.w[2] = msg->w[2];
    local.w[3] = msg->w[3];
    local.w[4] = msg->w[4];
    local.w[5] = msg->w[5];
    local.b   = msg->b;
    vtable = *(void **)this_obj;
    ((void (*)(cl4_msg49_t *))*(void **)((uintptr_t)vtable + 0xa8))(&local);
}

/* FUN_000e0c7c @ 0x000e0c7c   (est. resource_op_vtC8_copy)
 * Ghidra: void FUN_000e0c7c(undefined8 param_1)
 * Dispatches vtable slot 200 (0xc8) into a 104-byte scratch buffer, then
 * copies 0x61 bytes of it into the object at param_1.
 * Confidence: medium */
void FUN_000e0c7c(uint64_t param_1)
{
    void *this_obj;              /* unaff_x20 */
    void *vtable;
    uint8_t scratch[104];

    this_obj = 0;
    vtable = *(void **)this_obj;
    ((void (*)(uint8_t *))*(void **)((uintptr_t)vtable + 200))(scratch);
    FUN_00117cc4(param_1, scratch, 0x61);
}

/* FUN_000e0cd8 @ 0x000e0cd8   (est. resource_vtD0)
 * Ghidra: void FUN_000e0cd8(void)
 * Calls the resource vtable slot at +0xd0 with no arguments.
 * Confidence: medium */
void FUN_000e0cd8(void)
{
    void *this_obj;              /* unaff_x20 */
    void *vtable;

    this_obj = 0;
    vtable = *(void **)this_obj;
    ((void (*)(void))*(void **)((uintptr_t)vtable + 0xd0))();
}

/* FUN_000e0d14 @ 0x000e0d14   (est. resource_op_vtB0)
 * Ghidra: void FUN_000e0d14(undefined8 *param_1)
 * Same shape as FUN_000e0bbc but dispatches vtable slot +0xb0.
 * Confidence: medium */
void FUN_000e0d14(cl4_msg49_t *msg)
{
    void *this_obj;              /* unaff_x20 */
    void *vtable;
    cl4_msg49_t local;

    this_obj = 0;
    local.w[0] = msg->w[0];
    local.w[1] = msg->w[1];
    local.w[2] = msg->w[2];
    local.w[3] = msg->w[3];
    local.w[4] = msg->w[4];
    local.w[5] = msg->w[5];
    local.b   = msg->b;
    vtable = *(void **)this_obj;
    ((void (*)(cl4_msg49_t *))*(void **)((uintptr_t)vtable + 0xb0))(&local);
}

/* FUN_000e0dd4 @ 0x000e0dd4   (est. resource_op_vtC0)
 * Ghidra: void FUN_000e0dd4(undefined8 *param_1)
 * Same shape as FUN_000e0bbc but dispatches vtable slot +0xc0.
 * Confidence: medium */
void FUN_000e0dd4(cl4_msg49_t *msg)
{
    void *this_obj;              /* unaff_x20 */
    void *vtable;
    cl4_msg49_t local;

    this_obj = 0;
    local.w[0] = msg->w[0];
    local.w[1] = msg->w[1];
    local.w[2] = msg->w[2];
    local.w[3] = msg->w[3];
    local.w[4] = msg->w[4];
    local.w[5] = msg->w[5];
    local.b   = msg->b;
    vtable = *(void **)this_obj;
    ((void (*)(cl4_msg49_t *))*(void **)((uintptr_t)vtable + 0xc0))(&local);
}

/* FUN_000e0e34 @ 0x000e0e34   (est. resource_op_vtD8)
 * Ghidra: void FUN_000e0e34(undefined8 *param_1)
 * Same shape as FUN_000e0bbc but dispatches vtable slot +0xd8.
 * Confidence: medium */
void FUN_000e0e34(cl4_msg49_t *msg)
{
    void *this_obj;              /* unaff_x20 */
    void *vtable;
    cl4_msg49_t local;

    this_obj = 0;
    local.w[0] = msg->w[0];
    local.w[1] = msg->w[1];
    local.w[2] = msg->w[2];
    local.w[3] = msg->w[3];
    local.w[4] = msg->w[4];
    local.w[5] = msg->w[5];
    local.b   = msg->b;
    vtable = *(void **)this_obj;
    ((void (*)(cl4_msg49_t *))*(void **)((uintptr_t)vtable + 0xd8))(&local);
}

/* FUN_000e0e94 @ 0x000e0e94   (est. resource_op_vtE0)
 * Ghidra: void FUN_000e0e94(undefined8 *param_1)
 * Same shape as FUN_000e0bbc but dispatches vtable slot +0xe0.
 * Confidence: medium */
void FUN_000e0e94(cl4_msg49_t *msg)
{
    void *this_obj;              /* unaff_x20 */
    void *vtable;
    cl4_msg49_t local;

    this_obj = 0;
    local.w[0] = msg->w[0];
    local.w[1] = msg->w[1];
    local.w[2] = msg->w[2];
    local.w[3] = msg->w[3];
    local.w[4] = msg->w[4];
    local.w[5] = msg->w[5];
    local.b   = msg->b;
    vtable = *(void **)this_obj;
    ((void (*)(cl4_msg49_t *))*(void **)((uintptr_t)vtable + 0xe0))(&local);
}

/* FUN_000e0efc @ 0x000e0efc   (est. resource_step1)
 * Ghidra: void FUN_000e0efc(void)
 * One step of the resource lifecycle: calls FUN_000dfb64.
 * Confidence: medium */
void FUN_000e0efc(void)
{
    FUN_000dfb64();
}

/* FUN_000e0f14 @ 0x000e0f14   (est. resource_step2)
 * Ghidra: void FUN_000e0f14(void)
 * Calls FUN_000dfb6c (lifecycle step).
 * Confidence: medium */
void FUN_000e0f14(void)
{
    FUN_000dfb6c();
}

/* FUN_000e0f18 @ 0x000e0f18   (est. resource_step2b)
 * Ghidra: void FUN_000e0f18(void)
 * Calls FUN_000dfb6c — identical body to FUN_000e0f14.
 * Confidence: medium */
void FUN_000e0f18(void)
{
    FUN_000dfb6c();
}

/* FUN_000e0f2c @ 0x000e0f2c   (est. resource_step3)
 * Ghidra: void FUN_000e0f2c(void)
 * Calls FUN_000dfb74 (lifecycle step).
 * Confidence: medium */
void FUN_000e0f2c(void)
{
    FUN_000dfb74();
}

/* FUN_000e0f30 @ 0x000e0f30   (est. resource_step3b)
 * Ghidra: void FUN_000e0f30(void)
 * Calls FUN_000dfb74 — identical body to FUN_000e0f2c.
 * Confidence: medium */
void FUN_000e0f30(void)
{
    FUN_000dfb74();
}

/* FUN_000e0f44 @ 0x000e0f44   (est. resource_step4)
 * Ghidra: void FUN_000e0f44(void)
 * Calls FUN_000dfb7c (lifecycle step).
 * Confidence: medium */
void FUN_000e0f44(void)
{
    FUN_000dfb7c();
}

/* FUN_000e0f48 @ 0x000e0f48   (est. resource_step4b)
 * Ghidra: void FUN_000e0f48(void)
 * Calls FUN_000dfb7c — identical body to FUN_000e0f44.
 * Confidence: medium */
void FUN_000e0f48(void)
{
    FUN_000dfb7c();
}

/* FUN_000e0f5c @ 0x000e0f5c   (est. resource_is_ready)
 * Ghidra: bool FUN_000e0f5c(void)
 * Returns true when the readiness probe FUN_0006e6dc() returns 0.
 * Confidence: medium */
bool FUN_000e0f5c(void)
{
    return FUN_0006e6dc() == 0;
}

/* FUN_000e0f60 @ 0x000e0f60   (est. resource_is_ready2)
 * Ghidra: bool FUN_000e0f60(void)
 * Returns true when FUN_0006e6dc() returns 0 — identical body to 0xe0f5c.
 * Confidence: medium */
bool FUN_000e0f60(void)
{
    return FUN_0006e6dc() == 0;
}

/* FUN_000e0f7c @ 0x000e0f7c   (est. resource_field_get32)
 * Ghidra: void FUN_000e0f7c(undefined4 *param_1, undefined4 *param_2)
 * Reads a 32-bit field from *param_2 combined with this's word, converts via
 * FUN_0008cc7c, and stores the result into *param_1.
 * Confidence: medium */
void FUN_000e0f7c(uint32_t *out, uint32_t *in)
{
    uint32_t v;
    uint32_t this_word;          /* unaff_x20 */

    this_word = 0;
    v = FUN_0008cc7c(*in, this_word);
    *out = v;
}

/* FUN_000e0fcc @ 0x000e0fcc   (est. dispatch_indirect38)
 * Ghidra: void FUN_000e0fcc(undefined8 param_1, long param_2, ...)
 * Indirect dispatch: calls the function pointer at param_2+0x38 with
 * (param_1, param_3, param_4, param_5). Ghidra warns the jump table at
 * 0xe0fe0 was not recovered (treated as a call).
 * Confidence: low
 * Notes: "Could not recover jumptable ... treating indirect jump as call" */
void FUN_000e0fcc(uint64_t p1, uint64_t p2, uint64_t p3, uint64_t p4, uint64_t p5)
{
    ((void (*)(uint64_t, uint64_t, uint64_t, uint64_t))*(void **)(p2 + 0x38))(p1, p3, p4, p5);
}

/* FUN_000e0fe4 @ 0x000e0fe4   (est. dispatch_indirect20)
 * Ghidra: void FUN_000e0fe4(undefined8 param_1, long param_2, ...)
 * Indirect dispatch: calls the function pointer at param_2+0x20 with
 * (param_1, param_3, param_4). Jump-table warning at 0xe0ff4.
 * Confidence: low */
void FUN_000e0fe4(uint64_t p1, uint64_t p2, uint64_t p3, uint64_t p4)
{
    ((void (*)(uint64_t, uint64_t, uint64_t))*(void **)(p2 + 0x20))(p1, p3, p4);
}

/* FUN_000e0ff8 @ 0x000e0ff8   (est. dispatch_indirect30)
 * Ghidra: void FUN_000e0ff8(undefined8 param_1, long param_2, ...)
 * Indirect dispatch: calls the function pointer at param_2+0x30 with
 * (param_1, param_3, param_4). Jump-table warning at 0xe1008.
 * Confidence: low */
void FUN_000e0ff8(uint64_t p1, uint64_t p2, uint64_t p3, uint64_t p4)
{
    ((void (*)(uint64_t, uint64_t, uint64_t))*(void **)(p2 + 0x30))(p1, p3, p4);
}

/* FUN_000e100c @ 0x000e100c   (est. maybe_release_if_marked)
 * Ghidra: void FUN_000e100c(undefined8 param_1, undefined8 param_2, char param_3)
 * When the flag param_3 == 1, releases param_2 via thunk_FUN_0036b270.
 * Confidence: medium */
void FUN_000e100c(uint64_t p1, uint64_t p2, char flag)
{
    if (flag == 1) {
        thunk_FUN_0036b270(p2);
    }
}

/* FUN_000e1024 @ 0x000e1024   (est. resource_init_from_pair)
 * Ghidra: void FUN_000e1024(undefined8 param_1)
 * Constructs a pair via FUN_00160888(1, param_1, 0, 0, 0x661720, 0x661600),
 * refs this->+0x10, stores the pair into this->+0x10, and zeroes the low
 * flags at +0x20 (masked &0xff) and +0x28.
 * Confidence: low
 * Notes: 0x661720 / 0x661600 are code/data addresses passed as constructors. */
void FUN_000e1024(uint64_t param_1)
{
    uint64_t this_obj;           /* unaff_x20 */
    cl4_result_t pair;
    uint64_t flags;              /* uVar1 */
    uint64_t extra;              /* uVar2 */

    this_obj = 0;
    flags = 0;
    extra = 0;
    pair = FUN_00160888(1, param_1, 0, 0, 0x661720, 0x661600);
    FUN_0036a1a0(this_obj + 0x10);
    *(cl4_result_t *)(this_obj + 0x10) = pair;
    *(uint64_t *)(this_obj + 0x20) = flags & 0xff;
    *(uint64_t *)(this_obj + 0x28) = extra;
}

/* FUN_000e10b8 @ 0x000e10b8   (est. indirect_fp_call)
 * Ghidra: undefined8 FUN_000e10b8(undefined8 param_1, undefined8 param_2)
 * Calls the global function pointer _DAT_aa1503e0f900074f with (param_2,
 * param_1) and returns param_2.
 * Confidence: low
 * Notes: _DAT_aa1503e0f900074f is a direct global address reference; globals
 *   starting with '_' overlap smaller symbols at the same address. */
uint64_t FUN_000e10b8(uint64_t p1, uint64_t p2)
{
    (*(void (*)(uint64_t, uint64_t))(uintptr_t)0xaa1503e0f900074f)(p2, p1);
    return p2;
}

/* FUN_000e1124 @ 0x000e1124   (est. resource_vtC0_get)
 * Ghidra: void FUN_000e1124(undefined8 *param_1)
 * Fetches the current object via FUN_000027e8 (vtable base in x16), calls
 * its slot +0xc0, and stores the result into *param_1.
 * Confidence: low
 * Notes: extraout_x16 = object pointer returned in x16. */
void FUN_000e1124(uint64_t *out)
{
    uint64_t obj;

    obj = FUN_000027e8();
    *out = ((uint64_t (*)(void))*(void **)(obj + 0xc0))();
}

/* FUN_000e1164 @ 0x000e1164   (est. resource_vtC8_call)
 * Ghidra: void FUN_000e1164(undefined8 *param_1)
 * Fetches the current object via FUN_000027e8 and calls its slot 200 (0xc8)
 * passing *param_1.
 * Confidence: low */
void FUN_000e1164(uint64_t *in)
{
    uint64_t obj;

    obj = FUN_000027e8();
    ((void (*)(uint64_t))*(void **)(obj + 200))(*in);
}

/* FUN_000e11a0 @ 0x000e11a0   (est. resource_step_a)
 * Ghidra: void FUN_000e11a0(void)
 * Calls FUN_000df928 (lifecycle step).
 * Confidence: medium */
void FUN_000e11a0(void)
{
    FUN_000df928();
}

/* FUN_000e11a4 @ 0x000e11a4   (est. resource_step_a2)
 * Ghidra: void FUN_000e11a4(void)
 * Calls FUN_000df928 — identical body to FUN_000e11a0.
 * Confidence: medium */
void FUN_000e11a4(void)
{
    FUN_000df928();
}

/* FUN_000e11d4 @ 0x000e11d4   (est. resource_step_b)
 * Ghidra: void FUN_000e11d4(void)
 * Calls FUN_000df970 (lifecycle step).
 * Confidence: medium */
void FUN_000e11d4(void)
{
    FUN_000df970();
}

/* FUN_000e11d8 @ 0x000e11d8   (est. resource_step_b2)
 * Ghidra: void FUN_000e11d8(void)
 * Calls FUN_000df970 — identical body to FUN_000e11d4.
 * Confidence: medium */
void FUN_000e11d8(void)
{
    FUN_000df970();
}

/* FUN_000e1228 @ 0x000e1228   (est. resource_step_a3)
 * Ghidra: void FUN_000e1228(void)
 * Calls FUN_000df928.
 * Confidence: medium */
void FUN_000e1228(void)
{
    FUN_000df928();
}

/* FUN_000e122c @ 0x000e122c   (est. resource_step_a4)
 * Ghidra: void FUN_000e122c(void)
 * Calls FUN_000df928.
 * Confidence: medium */
void FUN_000e122c(void)
{
    FUN_000df928();
}

/* FUN_000e125c @ 0x000e125c   (est. resource_step_b3)
 * Ghidra: void FUN_000e125c(void)
 * Calls FUN_000df970.
 * Confidence: medium */
void FUN_000e125c(void)
{
    FUN_000df970();
}

/* FUN_000e1260 @ 0x000e1260   (est. resource_step_b4)
 * Ghidra: void FUN_000e1260(void)
 * Calls FUN_000df970.
 * Confidence: medium */
void FUN_000e1260(void)
{
    FUN_000df970();
}

/* FUN_000e1290 @ 0x000e1290   (est. resource_vt58_get)
 * Ghidra: void FUN_000e1290(undefined8 *param_1)
 * Fetches the current object via FUN_000027e8 and stores its slot +0x58
 * result into *param_1.
 * Confidence: low */
void FUN_000e1290(uint64_t *out)
{
    uint64_t obj;

    obj = FUN_000027e8();
    *out = ((uint64_t (*)(void))*(void **)(obj + 0x58))();
}

/* FUN_000e12d4 @ 0x000e12d4   (est. resource_vtE8_get)
 * Ghidra: void FUN_000e12d4(undefined8 *param_1)
 * Fetches the current object via FUN_000027e8 and stores its slot +0xe8
 * result into *param_1.
 * Confidence: low */
void FUN_000e12d4(uint64_t *out)
{
    uint64_t obj;

    obj = FUN_000027e8();
    *out = ((uint64_t (*)(void))*(void **)(obj + 0xe8))();
}

/* FUN_000e1314 @ 0x000e1314   (est. resource_vtF0_call)
 * Ghidra: void FUN_000e1314(undefined8 *param_1)
 * Fetches the current object via FUN_000027e8 and calls its slot +0xf0
 * passing *param_1.
 * Confidence: low */
void FUN_000e1314(uint64_t *in)
{
    uint64_t obj;

    obj = FUN_000027e8();
    ((void (*)(uint64_t))*(void **)(obj + 0xf0))(*in);
}

/* FUN_000e1350 @ 0x000e1350   (est. run_code_651428)
 * Ghidra: void FUN_000e1350(void)
 * Invokes the code pointer at 0x651428 via FUN_00077770.
 * Confidence: low */
void FUN_000e1350(void)
{
    FUN_00077770(0x651428);
}

/* FUN_000e1368 @ 0x000e1368   (est. run_code_651518)
 * Ghidra: void FUN_000e1368(void)
 * Invokes the code pointer at 0x651518 via FUN_00077770.
 * Confidence: low */
void FUN_000e1368(void)
{
    FUN_00077770(0x651518);
}

/* FUN_000e1430 @ 0x000e1430   (est. emit_message_65fa88)
 * Ghidra: void FUN_000e1430(void)
 * Emits a message with the two code addresses 0x65fa88 / 0x65f980 via
 * FUN_0036993c.
 * Confidence: low */
void FUN_000e1430(void)
{
    FUN_0036993c(0x65fa88, 0x65f980, 0, 0);
}

/* FUN_000e1458 @ 0x000e1458   (est. resource_nop)
 * Ghidra: void FUN_000e1458(void)
 * Empty method (no-op vtable slot).
 * Confidence: medium */
void FUN_000e1458(void)
{
}

/* FUN_000e1498 @ 0x000e1498   (est. resource_pair_6513f0)
 * Ghidra: undefined1 [16] FUN_000e1498(void)
 * Returns the pair {0x6513f0, &FUN_000df114} (a code label + function
 * pointer).
 * Confidence: low
 * Notes: 0x6513f0 is code; FUN_000df114 is a function pointer. */
cl4_result_t FUN_000e1498(void)
{
    cl4_result_t r;

    r.lo = 0x6513f0;
    r.hi = (uint64_t)(uintptr_t)&FUN_000df114;
    return r;
}

/* FUN_000e14b8 @ 0x000e14b8   (est. resource_nop2)
 * Ghidra: void FUN_000e14b8(void)
 * Empty method (no-op vtable slot).
 * Confidence: medium */
void FUN_000e14b8(void)
{
}

/* FUN_000e14e0 @ 0x000e14e0   (est. resource_nop3)
 * Ghidra: void FUN_000e14e0(void)
 * Empty method (no-op vtable slot).
 * Confidence: medium */
void FUN_000e14e0(void)
{
}

/* FUN_000e14f0 @ 0x000e14f0   (est. resource_fatal_error_result)
 * Ghidra: undefined1 [16] FUN_000e14f0(void)
 * Returns the fatal-error result {&"Fatal error", 0xb}.
 * Confidence: high (string-matched "Fatal error" at 0x5accd0) */
cl4_result_t FUN_000e14f0(void)
{
    cl4_result_t r;

    r.lo = (uint64_t)(uintptr_t)"Fatal error";
    r.hi = 0xb;
    return r;
}

/* FUN_000e1514 @ 0x000e1514   (est. resource_ref_acquire)
 * Ghidra: void FUN_000e1514(void)
 * Acquires a reference/lock via FUN_0036a1a0.
 * Confidence: medium */
void FUN_000e1514(void)
{
    FUN_0036a1a0();
}

/* FUN_000e1528 @ 0x000e1528   (est. resource_nop4)
 * Ghidra: void FUN_000e1528(void)
 * Empty method (no-op vtable slot).
 * Confidence: medium */
void FUN_000e1528(void)
{
}

/* FUN_000e1540 @ 0x000e1540   (est. resource_nop5)
 * Ghidra: void FUN_000e1540(void)
 * Empty method (no-op vtable slot).
 * Confidence: medium */
void FUN_000e1540(void)
{
}

/* FUN_000e1558 @ 0x000e1558   (est. table_lookup_pair)
 * Ghidra: undefined1 [16] FUN_000e1558(ulong param_1)
 * Returns {DAT_004c29c0[param_1&0xff], DAT_004c2a88[param_1&0xff]} — indexes
 * two byte-indexed lookup tables in parallel.
 * Confidence: medium */
cl4_result_t FUN_000e1558(uint64_t param_1)
{
    cl4_result_t r;
    unsigned idx = (unsigned)(param_1 & 0xff);

    r.lo = DAT_004c29c0[idx];
    r.hi = DAT_004c2a88[idx];
    return r;
}

/* FUN_000e1584 @ 0x000e1584   (est. resource_pair_6513f8)
 * Ghidra: undefined1 [16] FUN_000e1584(void)
 * Returns the pair {0x6513f8, &FUN_000df77c}.
 * Confidence: low */
cl4_result_t FUN_000e1584(void)
{
    cl4_result_t r;

    r.lo = 0x6513f8;
    r.hi = (uint64_t)(uintptr_t)&FUN_000df77c;
    return r;
}

/* FUN_000e15a4 @ 0x000e15a4   (est. resource_ref_acquire2)
 * Ghidra: void FUN_000e15a4(void)
 * Acquires a reference/lock via FUN_0036a1a0.
 * Confidence: medium */
void FUN_000e15a4(void)
{
    FUN_0036a1a0();
}

/* FUN_000e15b8 @ 0x000e15b8   (est. resource_flags16_out)
 * Ghidra: void FUN_000e15b8(undefined8 param_1, undefined4 *param_2)
 * Stores this's 32-bit flag (unaff_w20) into *param_2 and 16-bit flag
 * (unaff_w22) into the halfword after it.
 * Confidence: low
 * Notes: unaff_w20 / unaff_w22 are caller registers. */
void FUN_000e15b8(uint64_t p1, uint32_t *out)
{
    uint32_t w20;                /* unaff_w20 */
    uint16_t w22;                /* unaff_w22 */

    w20 = 0;
    w22 = 0;
    *out = w20;
    *(uint16_t *)(out + 1) = w22;
}

/* FUN_000e15c8 @ 0x000e15c8   (est. result_const_9)
 * Ghidra: undefined1 [16] FUN_000e15c8(void)
 * Returns the constant result {9, 0}.
 * Confidence: high */
cl4_result_t FUN_000e15c8(void)
{
    cl4_result_t r;

    r.lo = 9;
    r.hi = 0;
    return r;
}

/* FUN_000e15d8 @ 0x000e15d8   (est. resource_nop6)
 * Ghidra: void FUN_000e15d8(void)
 * Empty method (no-op vtable slot).
 * Confidence: medium */
void FUN_000e15d8(void)
{
}

/* FUN_000e15e4 @ 0x000e15e4   (est. resource_compare_helper)
 * Ghidra: void FUN_000e15e4(void)
 * Calls the word-compare helper FUN_002a0cf8.
 * Confidence: medium */
void FUN_000e15e4(void)
{
    FUN_002a0cf8();
}

/* FUN_000e15f4 @ 0x000e15f4   (est. resource_nop7)
 * Ghidra: void FUN_000e15f4(void)
 * Empty method (no-op vtable slot).
 * Confidence: medium */
void FUN_000e15f4(void)
{
}

/* FUN_000e1600 @ 0x000e1600   (est. resource_fatal_error_result2)
 * Ghidra: undefined1 [16] FUN_000e1600(void)
 * Returns the fatal-error result {&"Fatal error", 0xb} — identical to
 * FUN_000e14f0.
 * Confidence: high (string-matched) */
cl4_result_t FUN_000e1600(void)
{
    cl4_result_t r;

    r.lo = (uint64_t)(uintptr_t)"Fatal error";
    r.hi = 0xb;
    return r;
}

/* FUN_000e1628 @ 0x000e1628   (est. resource_nop8)
 * Ghidra: void FUN_000e1628(void)
 * Empty method (no-op vtable slot).
 * Confidence: medium */
void FUN_000e1628(void)
{
}

/* FUN_000e1640 @ 0x000e1640   (est. resource_word_or_flags)
 * Ghidra: ulong FUN_000e1640(ulong *param_1)
 * Returns *param_1 ORed with this's word (unaff_x19).
 * Confidence: low */
uint64_t FUN_000e1640(uint64_t *in)
{
    uint64_t this_word;          /* unaff_x19 */

    this_word = 0;
    return *in | this_word;
}

/* FUN_000e164c @ 0x000e164c   (est. resource_nop9)
 * Ghidra: void FUN_000e164c(void)
 * Empty method (no-op vtable slot).
 * Confidence: medium */
void FUN_000e164c(void)
{
}

/* FUN_000e1658 @ 0x000e1658   (est. resource_flags32_out)
 * Ghidra: void FUN_000e1658(undefined8 param_1, undefined4 *param_2)
 * Stores this's 32-bit (unaff_w23) and 16-bit (unaff_w20) flags into the
 * output, then completes via FUN_0036986c.
 * Confidence: low */
void FUN_000e1658(uint64_t p1, uint32_t *out)
{
    uint16_t w20;                /* unaff_w20 */
    uint32_t w23;                /* unaff_w23 */

    w20 = 0;
    w23 = 0;
    *out = w23;
    *(uint16_t *)(out + 1) = w20;
    FUN_0036986c();
}

/* FUN_000e166c @ 0x000e166c   (est. resource_status8_out)
 * Ghidra: void FUN_000e166c(undefined8 param_1, undefined1 *param_2)
 * Stores the constant 8 into *param_2, then completes via FUN_0036986c.
 * Confidence: medium */
void FUN_000e166c(uint64_t p1, uint8_t *out)
{
    *out = 8;
    FUN_0036986c();
}

/* FUN_000e1680 @ 0x000e1680   (est. resource_build_dispatch)
 * Ghidra: void FUN_000e1680(undefined8 param_1, undefined8 param_2, ...)
 * Completes a build step via FUN_0036a940 then dispatches to FUN_000e18a0
 * with the four arguments.
 * Confidence: medium */
void FUN_000e1680(uint64_t p1, uint64_t p2, uint64_t p3, uint64_t p4)
{
    FUN_0036a940();
    FUN_000e18a0(p1, p2, (uint64_t *)p3, p4);
}

/* FUN_000e16ec @ 0x000e16ec   (est. resource_copyout_state)
 * Ghidra: void FUN_000e16ec(undefined8 *param_1)
 * Copies the 36-word state structure at this->+0x10 into the output param_1
 * array: out[0..33] = src[+0x10..+0x120], out[34] = src[+0x128],
 * out[35] = this->+0x20.
 * Confidence: medium */
void FUN_000e16ec(uint64_t *out)
{
    uint64_t this_obj;           /* unaff_x20 */
    uint64_t *src;

    this_obj = 0;
    src = (uint64_t *)*(uint64_t *)(this_obj + 0x10);
    out[0]  = src[0x10 / 8];
    out[1]  = src[0x18 / 8];
    out[2]  = src[0x20 / 8];
    out[3]  = src[0x28 / 8];
    out[4]  = src[0x30 / 8];
    out[5]  = src[0x38 / 8];
    out[6]  = src[0x40 / 8];
    out[7]  = src[0x48 / 8];
    out[8]  = src[0x50 / 8];
    out[9]  = src[0x58 / 8];
    out[10] = src[0x60 / 8];
    out[11] = src[0x68 / 8];
    out[12] = src[0x70 / 8];
    out[13] = src[0x78 / 8];
    out[14] = src[0x80 / 8];
    out[15] = src[0x88 / 8];
    out[16] = src[0x90 / 8];
    out[17] = src[0x98 / 8];
    out[18] = src[0xa0 / 8];
    out[19] = src[0xa8 / 8];
    out[20] = src[0xb0 / 8];
    out[21] = src[0xb8 / 8];
    out[22] = src[0xc0 / 8];
    out[23] = src[0xc8 / 8];
    out[24] = src[0xd0 / 8];
    out[25] = src[0xd8 / 8];
    out[26] = src[0xe0 / 8];
    out[27] = src[0xe8 / 8];
    out[28] = src[0xf0 / 8];
    out[29] = src[0xf8 / 8];
    out[30] = src[0x100 / 8];
    out[31] = src[0x108 / 8];
    out[32] = src[0x110 / 8];
    out[33] = src[0x118 / 8];
    out[34] = src[0x120 / 8];
    out[35] = *(uint64_t *)(this_obj + 0x20);
}

/* FUN_000e174c @ 0x000e174c   (est. region_provision_failure)
 * Ghidra: undefined1 [16] FUN_000e174c(void)
 * Logs a fatal provisioning failure: "RegionResource(name: ... , physical:
 * 0x..., size: 0x...)" then returns the constant {0x646572656b6f7242
 * ("Brokered" LE), 0xe900000000000028}.
 * Confidence: high (string-matched "Brokered" + region strings)
 * Notes: funky_leak: FUN_002a4ab4(0x1d) trace op; prints 0x5c4300
 *   ("RegionResource(name: ") / 0x5c42d0 and code pointers 0x671df8/0x677830. */
cl4_result_t FUN_000e174c(void)
{
    cl4_result_t r;

    FUN_002a4ab4(0x1d);
    FUN_003a25d4(0xe000000000000000);
    FUN_000e1d24();
    thunk_FUN_002acbb8();
    FUN_003a25d4(0xe000000000000000);
    thunk_FUN_002acbb8(0x2065646f6e63202c, 0xef203a7865646e69); /* ", code 0x.." */
    (*(void (*)(uint64_t, uint64_t))FUN_00027724(0x671df8))(0x677830, 0x671df8);
    thunk_FUN_002acbb8();
    FUN_003a25d4(0xe000000000000000);
    thunk_FUN_002acbb8(0x29, 0xe100000000000000); /* ")" */
    r.lo = 0x646572656b6f7242;   /* "Brokered" little-endian */
    r.hi = 0xe900000000000028;
    return r;
}

/* FUN_000e1858 @ 0x000e1858   (est. resource_copyout_wrapper)
 * Ghidra: void FUN_000e1858(void)
 * Thin forwarding stub: copies out the resource state via FUN_000e16ec.
 * The out pointer register was dropped by the decompiler; passed as 0.
 * Confidence: medium */
void FUN_000e1858(void)
{
    FUN_000e16ec((uint64_t *)0);
}

/* FUN_000e187c @ 0x000e187c   (est. region_failure_wrapper)
 * Ghidra: void FUN_000e187c(void)
 * Thin forwarding stub: FUN_000e174c (region provisioning failure log).
 * Confidence: medium */
void FUN_000e187c(void)
{
    FUN_000e174c();
}

/* FUN_000e18a0 @ 0x000e18a0   (est. component_memory_region_provision)
 * Ghidra: long FUN_000e18a0(undefined8 param_1, undefined8 param_2, ulong *param_3, ...)
 * Provides a memory region for a boot component. Populates a scratch buffer,
 * dispatches a vtable slot with the component, and handles the outcomes:
 *   - "Component will not be provided a memory region for ... does not exist."
 *   - "was not populated (iBoot didn't load it?).Component will not be
 *     provided a memory region for ..." (physical address missing,
 *     result_lo == -1)
 *   - success: resolves the MMIO untyped for the physical address, records
 *     the region (this->+0x110/0x118/0x120/0x128), warns ", not page aligned"
 *     when misaligned.
 * Confidence: low
 * Notes: strings s_does_not_exist_... (0x5c4240), s_was_not_populated_...
 *   (0x5c4290), ", not page aligned" (0x5c2be0); SoftwareBreakpoint at
 *   0xe1c8c / 0xe1c90; refs 0x6673a0/0x6672a8/0x6753a0. */
long FUN_000e18a0(uint64_t p1, uint64_t p2, uint64_t *p3, uint64_t p4)
{
    uint8_t scratch[256];
    uint64_t result_buf[7];
    cl4_result_t r;
    uint64_t result_lo;          /* uVar4 */
    uint64_t result_hi;          /* uVar7 */
    uint64_t value;              /* uVar10 */
    uint64_t cap;
    uint64_t base;
    uint64_t alloc;
    uint64_t final;
    long this_obj;               /* unaff_x20 */
    int success;                 /* unaff_x21 */

    this_obj = 0;
    FUN_000fdd78(scratch);
    if (FUN_000a9ae8(scratch) == 1) {
        FUN_003a25d4(p2);
        FUN_000aa3ac();
        /* fixed failure result {0xd00000000000002e, 0x80000000005c41d0} */
        result_buf[0] = 0xd00000000000002e;
        result_buf[1] = 0x80000000005c41d0;
        FUN_0036986c();
        FUN_0036b118(p3);
        FUN_000e1fc4();
        return this_obj;
    }
    FUN_00117cc4(this_obj + 0x10, scratch, 0x100);
    value = *p3;
    {
        cl4_result_t (*fn)(uint64_t, uint64_t, uint64_t *, uint64_t, uint64_t) =
            (cl4_result_t (*)(uint64_t, uint64_t, uint64_t *, uint64_t, uint64_t))FUN_00096f78(p4);
        r = fn(p1, p2, result_buf, value, p4);
    }
    result_hi = r.hi;
    result_lo = r.lo;
    if (success != 0) {
        FUN_003a25d4(p2);
        FUN_0036993c(0x6673a0, 0x6672a8, 0, 0);
        FUN_0036b118(p3);
        FUN_000e1fc4();
        return this_obj;
    }
    /* Component does not exist: result_buf[0] low byte == 1 */
    if (((uintptr_t)result_buf & 0xff) == 1) {
        cap = FUN_0008e0d4();
        FUN_0036a9a0(cap, 0, 0);
        FUN_000e1fa4();
        FUN_002a4ab4(0x66);
        FUN_000e1f74();
        FUN_000e1fb4();
        value = value + 0x25;
        thunk_FUN_002acbb8(value, (uint64_t)(uintptr_t)" does not exist." | 0x8000000000000000);
        FUN_000e1fb4();
        FUN_003a25d4(p2);
        thunk_FUN_002acbb8(0x2e, 0xe100000000000000); /* "." */
        FUN_0036b118(p3);
        FUN_0036b588(0);
        (void)FUN_00002688();
        FUN_0036b6ac(0, 0x20, 7);
        FUN_000e1fc4();
        return 0;
    }
    if (result_lo == 0xffffffffffffffff) {
        /* was not populated (iBoot didn't load it?) */
        cap = FUN_0008e0d4();
        FUN_0036a940(cap, 0x40, 7);
        FUN_000e1fa4();
        FUN_002a4ab4(0x81);
        FUN_000e1f74();
        FUN_000e1fb4();
        value = value | 0x40;
        thunk_FUN_002acbb8(value, (uint64_t)(uintptr_t)" was not populated (iBoot didn't load it?)." | 0x8000000000000000);
        FUN_000e1fb4();
        FUN_003a25d4(p2);
        thunk_FUN_002acbb8(0x2e, 0xe100000000000000); /* "." */
        FUN_0036b118(p3);
        FUN_0036b588(0);
        (void)FUN_00002688();
        FUN_0036b6ac(0, 0x20, 7);
        FUN_000e1fc4();
        return 0;
    }
    FUN_003a25d4(p2);
    *(uint64_t *)(this_obj + 0x118) = result_lo;
    *(uint64_t *)(this_obj + 0x128) = result_hi;
    if (result_hi > 0xffffffffffffc000) {
        /* SoftwareBreakpoint(1, 0xe1c8c): size overflows canonical range */
        __builtin_trap();
    }
    value = (result_hi + 0x3fff) & 0xffffffffffffc000;
    *(uint64_t *)(this_obj + 0x120) = value;
    cap = FUN_0006cf50(result_lo);
    if (cap != 0) {
        base = FUN_0006d024(result_lo);
        if (base <= result_lo) {
            alloc = FUN_001000b8(0);
            final = FUN_000fd41c(alloc, cap, result_lo - base, value, result_lo);
            FUN_0036b118(p3);
            *(uint64_t *)(this_obj + 0x110) = final;
            return this_obj;
        }
        /* SoftwareBreakpoint(1, 0xe1c90): base above paddr */
        __builtin_trap();
    }
    FUN_000e1fa4();
    FUN_002a4ab4(0x33);
    thunk_FUN_002acbb8(0xd000000000000031, 0x80000000005c2be0); /* ", not page aligned" */
    (*(void (*)(uint64_t, uint64_t))FUN_00027724(0x671848))(0x677790, 0x671848);
    thunk_FUN_002acbb8();
    FUN_003a25d4(0);
    FUN_000aa3ac();
    result_buf[0] = 0;
    result_buf[1] = 0;
    FUN_0036986c();
    FUN_0036b118(p3);
    FUN_000e1fc4();
    return this_obj;
}

/* FUN_000e1c90 @ 0x000e1c90   (est. region_resource_get)
 * Ghidra: void FUN_000e1c90(undefined8 *param_1, undefined8 param_2)
 * Allocates a region resource tagged with 0x6516b0 (name) and 0x6617d8
 * (entrypoint), retains param_2, and on success stores into param_1:
 *   [0]=uVar1 (from FUN_000bd4f0), [3]=0x6516b0, [4]=0x6617d8.
 * Confidence: low */
void FUN_000e1c90(uint64_t *out, uint64_t param_2)
{
    uint64_t h;
    int success;                 /* unaff_x21 */

    FUN_0036a940(0x6516b0, 0x51, 7);
    FUN_0036b270();
    FUN_0036b270(param_2);
    h = FUN_000bd4f0();
    if (success == 0) {
        out[3] = 0x6516b0;
        out[4] = 0x6617d8;
        out[0] = h;
    }
}

/* FUN_000e1d24 @ 0x000e1d24   (est. region_resource_describe)
 * Ghidra: void FUN_000e1d24(void)
 * Serializes and logs the region resource: prints "RegionResource(name: ",
 * the physical address ("physical: 0x"), the size ("size: 0x"), and the
 * entrypoint. Uses a stack canary (local_48) validated on exit.
 * Confidence: medium
 * Notes: prints 0x5c42d0 ("DeviceTreeMemoryRegionResource(name: ") and
 *   0x5c4300; FUN_001e9c00 serializes; FUN_0011d7e8 is the canary-fail path. */
void FUN_000e1d24(void)
{
    uint64_t this_obj;           /* unaff_x20 */
    uint8_t  buf[0x160];
    uint64_t canary = 0xd3ca4b4b4b3d7a2a;   /* -0x2c8502b44bfffed6 */
    int i;
    uint64_t *src;
    uint64_t *dst;

    this_obj = 0;
    FUN_002a4ab4(0x44);
    thunk_FUN_002acbb8(0xd000000000000025, 0x80000000005c42d0);
    src = (uint64_t *)*(uint64_t *)(this_obj + 0x10);
    dst = (uint64_t *)buf;
    for (i = 0; i < 34; i++) {
        dst[i] = src[i + 2];    /* +0x10..+0x118 */
    }
    FUN_001e9c00(buf);
    thunk_FUN_002acbb8();
    FUN_003a25d4(0);
    thunk_FUN_002acbb8(0x646173796870202c, 0xee007830203a7264); /* ", physical: 0x.." */
    *(uint64_t *)(buf + 0) = *(uint64_t *)(this_obj + 0x118);
    FUN_0001e790();
    FUN_000bde98();
    thunk_FUN_002acbb8();
    FUN_003a25d4(0);
    thunk_FUN_002acbb8(0x203a657a6973202c, 0xea00000000007830); /* ", size: 0x.." */
    *(uint64_t *)(buf + 0) = *(uint64_t *)(this_obj + 0x120);
    FUN_000bde98();
    thunk_FUN_002acbb8();
    FUN_003a25d4(0);
    thunk_FUN_002acbb8(0x29, 0xe100000000000000); /* ")" */
    if (canary != 0xd3ca4b4b4b3d7a2a) {
        /* canary corrupted — noreturn */
        FUN_0011d7e8(0, 0xe000000000000000);
    }
}

/* FUN_000e1eb4 @ 0x000e1eb4   (est. resource_release_region)
 * Ghidra: void FUN_000e1eb4(void)
 * Releases the region object at this->+0x110 (FUN_0036b118) then completes
 * via FUN_0036b6ac.
 * Confidence: medium */
void FUN_000e1eb4(void)
{
    uint64_t this_obj;           /* unaff_x20 */

    this_obj = 0;
    FUN_0036b118(*(uint64_t *)(this_obj + 0x110));
    FUN_0036b6ac();
}

/* FUN_000e1eb8 @ 0x000e1eb8   (est. resource_release_region2)
 * Ghidra: void FUN_000e1eb8(void)
 * Same as FUN_000e1eb4 (release this->+0x110, then complete).
 * Confidence: medium */
void FUN_000e1eb8(void)
{
    uint64_t this_obj;           /* unaff_x20 */

    this_obj = 0;
    FUN_0036b118(*(uint64_t *)(this_obj + 0x110));
    FUN_0036b6ac();
}

/* FUN_000e1ee0 @ 0x000e1ee0   (est. region_get_wrapper)
 * Ghidra: void FUN_000e1ee0(void)
 * Thin forwarding stub: FUN_000e1c90. The dropped out/param registers are
 * passed as 0.
 * Confidence: medium */
void FUN_000e1ee0(void)
{
    FUN_000e1c90((uint64_t *)0, 0);
}

/* FUN_000e1ee4 @ 0x000e1ee4   (est. region_get_wrapper2)
 * Ghidra: void FUN_000e1ee4(void)
 * Thin forwarding stub: FUN_000e1c90.
 * Confidence: medium */
void FUN_000e1ee4(void)
{
    FUN_000e1c90((uint64_t *)0, 0);
}

/* FUN_000e1ef8 @ 0x000e1ef8   (est. region_describe_wrapper)
 * Ghidra: void FUN_000e1ef8(void)
 * Wraps FUN_000e1d24 (region describe/log).
 * Confidence: medium */
void FUN_000e1ef8(void)
{
    FUN_000e1d24();
}

/* FUN_000e1f64 @ 0x000e1f64   (est. result_codeptr_651630)
 * Ghidra: undefined1 [16] FUN_000e1f64(void)
 * Returns the pair {0x651630, 0} (a code pointer label).
 * Confidence: low */
cl4_result_t FUN_000e1f64(void)
{
    cl4_result_t r;

    r.lo = 0x651630;
    r.hi = 0;
    return r;
}

/* FUN_000e1f74 @ 0x000e1f74   (est. region_warn_noalign)
 * Ghidra: void FUN_000e1f74(void)
 * Prints a warning: ", not page aligned" (0x5c2be0 string reference via
 * thunk_FUN_002acbb8 with the pair 0xd00000000000001e, 0x80000000005c4200).
 * Confidence: low */
void FUN_000e1f74(void)
{
    thunk_FUN_002acbb8(0xd00000000000001e, 0x80000000005c4200);
}

/* FUN_000e1fa4 @ 0x000e1fa4   (est. resource_step_noop)
 * Ghidra: void FUN_000e1fa4(void)
 * Empty step (no-op marker).
 * Confidence: medium */
void FUN_000e1fa4(void)
{
}

/* FUN_000e1fb4 @ 0x000e1fb4   (est. resource_flush_output)
 * Ghidra: void FUN_000e1fb4(void)
 * Flushes output via thunk_FUN_002acbb8() with no arguments.
 * Confidence: medium */
void FUN_000e1fb4(void)
{
    thunk_FUN_002acbb8();
}

/* FUN_000e1fc4 @ 0x000e1fc4   (est. resource_complete)
 * Ghidra: void FUN_000e1fc4(void)
 * Completes the operation via FUN_0036b6f4.
 * Confidence: medium */
void FUN_000e1fc4(void)
{
    FUN_0036b6f4();
}

/* FUN_000e1fd8 @ 0x000e1fd8   (est. resource_alloc_triple)
 * Ghidra: undefined1 [16] FUN_000e1fd8(void)
 * Allocates three handles (via FUN_000aa6d0 / FUN_000ec964 / FUN_0006f800),
 * each ref'd with size 0x10, and returns {first_alloc, second_handle}.
 * Confidence: low */
cl4_result_t FUN_000e1fd8(void)
{
    uint64_t a, b, c;
    cl4_result_t r;

    a = FUN_000aa6d0(0);
    r.lo = (uint64_t)(uintptr_t)FUN_0036a940(a, 0x10, 7);
    b = FUN_000ec964(0);
    r.hi = (uint64_t)(uintptr_t)FUN_0036a940(b, 0x10, 7);
    c = FUN_0006f800(0);
    FUN_0036a940(c, 0x10, 7);
    return r;
}

/* thunk_FUN_0036b270 @ 0x000e2044   (est. cL4_obj_ref_acquire)
 * Ghidra: ulong thunk_FUN_0036b270(ulong param_1)
 * Acquires a reference on a cL4 object (refcount stored at obj+8). When the
 * count is positive it adds 0x200000000 with overflow detection; on overflow
 * (count already -1) it returns the aligned object, otherwise it allocates a
 * fresh copy via FUN_0039f9e8.
 * Confidence: medium
 * Notes: aligned base = param_1 & ~7; count overflow path calls FUN_0039f9e8. */
uint64_t thunk_FUN_0036b270(uint64_t obj)
{
    uint64_t base;
    uint64_t *cnt_slot;
    uint64_t cnt;
    uint64_t next;
    bool changed;

    if ((long)obj > 0) {
        base = obj & 0xfffffffffffffff8;
        cnt_slot = (uint64_t *)(base + 8);
        cnt = *(uint64_t *)(base + 8);
        do {
            next = cnt + 0x200000000;
            if (next > 0xffffffffffffffff) {  /* overflow into high bit */
                if ((int)cnt == -1) {
                    return base;
                }
                base = FUN_0039f9e8(cnt_slot, cnt, 1);
                return base;
            }
            changed = *cnt_slot != cnt;
            cnt = *cnt_slot;
        } while (changed);
        *cnt_slot = next;
    }
    return obj;
}

/* FUN_000e20c4 @ 0x000e20c4   (est. resource_collect_min)
 * Ghidra: undefined8 FUN_000e20c4(void)
 * Collects the per-object "cost" words from this's resource list into the
 * global scratch array (DAT_00657798), then finds the minimum via
 * FUN_000e250c and returns it (0 on empty/error).
 * Confidence: medium */
uint64_t FUN_000e20c4(void)
{
    uint64_t *this_obj;          /* unaff_x20 */
    uint64_t list;
    uint64_t count;
    uint64_t *slot;
    uint64_t idx;                /* uVar5 */
    uint64_t val;
    cl4_result_t r;

    this_obj = 0;
    list = *this_obj;
    count = *(uint64_t *)(list + 0x10);
    if (count != 0) {
        FUN_000e46ec();
        slot = (uint64_t *)(list + 0x20);
        idx = DAT_00657788;
        do {
            val = *(uint64_t *)(*slot + 0x10);
            if (DAT_00657790 >> 1 <= idx) {
                FUN_00082484(1 < DAT_00657790, idx + 1, 1);
            }
            DAT_00657788 = idx + 1;
            DAT_00657798[idx] = val;
            count = count - 1;
            slot = slot + 1;
            idx = idx + 1;
        } while (count != 0);
    }
    r = FUN_000e250c(&DAT_00657778[0]);
    FUN_0036b118(&DAT_00657778[0]);
    if (((r.hi >> 32) & 0xff) == 1) {
        return 0;
    }
    return r.lo;
}

/* FUN_000e2198 @ 0x000e2198   (est. resource_register2)
 * Ghidra: void FUN_000e2198(void)
 * Registers the two name pairs at this->+0x28/+0x30 via FUN_0010562c.
 * Confidence: medium */
void FUN_000e2198(void)
{
    uint64_t this_obj;           /* unaff_x20 */

    this_obj = 0;
    FUN_0010562c(*(uint64_t *)(this_obj + 0x28), *(uint64_t *)(this_obj + 0x30));
}

/* FUN_000e219c @ 0x000e219c   (est. resource_register2b)
 * Ghidra: void FUN_000e219c(void)
 * Same as FUN_000e2198 (register two name pairs).
 * Confidence: medium */
void FUN_000e219c(void)
{
    uint64_t this_obj;           /* unaff_x20 */

    this_obj = 0;
    FUN_0010562c(*(uint64_t *)(this_obj + 0x28), *(uint64_t *)(this_obj + 0x30));
}

/* FUN_000e21b4 @ 0x000e21b4   (est. resource_sum_cost)
 * Ghidra: undefined8 FUN_000e21b4(void)
 * Sums the cost words of this's resources into the global scratch array and
 * returns the minimum via FUN_000e258c (0 on empty/error).
 * Confidence: medium */
uint64_t FUN_000e21b4(void)
{
    uint64_t *this_obj;          /* unaff_x20 */
    uint64_t list;
    uint64_t count;
    uint64_t *slot;
    uint64_t cost;
    uint64_t obj;
    uint64_t add;
    uint64_t total;
    uint64_t idx;
    cl4_result_t r;

    this_obj = 0;
    list = *this_obj;
    count = *(uint64_t *)(list + 0x10);
    if (count != 0) {
        FUN_000e46ec();
        slot = (uint64_t *)(list + 0x20);
        do {
            obj = *slot;
            cost = *(uint64_t *)(obj + 0x10);
            {
                uint64_t vbase = FUN_000027e8();
                (*(void (*)(void))*(void **)(vbase + 0x58))();
            }
            thunk_FUN_0036b270(obj);
            add = 0;   /* the per-element addend register was dropped */
            FUN_0036b118(obj);
            idx = DAT_00657788;
            total = cost + add;
            if (total < cost) {
                /* SoftwareBreakpoint(1, 0xe22c0): sum overflow */
                __builtin_trap();
            }
            if (DAT_00657790 >> 1 <= DAT_00657788) {
                FUN_00082484(1 < DAT_00657790, DAT_00657788 + 1, 1);
            }
            DAT_00657788 = DAT_00657788 + 1;
            DAT_00657798[idx] = total;
            count = count - 1;
            slot = slot + 1;
        } while (count != 0);
    }
    r = FUN_000e258c(&DAT_00657778[0]);
    FUN_0036b118(&DAT_00657778[0]);
    if (((r.hi >> 32) & 0xff) == 1) {
        return 0;
    }
    return r.lo;
}

/* FUN_000e22c0 @ 0x000e22c0   (est. resource_search_component)
 * Ghidra: undefined8 FUN_000e22c0(void)
 * Searches this's resource list (and a secondary list) for an element whose
 * identity matches the magic 0x455a454741505f5f / marker 0xea00000000004f52
 * (a __PAGEZERO-like segment), collecting matching entries into the scratch
 * array and returning the minimum.
 * Confidence: low
 * Notes: SoftwareBreakpoint(1, 0xe248c); __PAGEZERO magic 0x455a454741505f5f. */
uint64_t FUN_000e22c0(void)
{
    uint64_t *this_obj;          /* unaff_x20 */
    uint64_t list;
    uint64_t count;
    uint64_t idx;
    uint64_t *slot;
    uint64_t obj;
    uint64_t val;
    uint64_t r_hi;
    cl4_result_t r;

    this_obj = 0;
    idx = 0;
    {
        uint64_t l = FUN_000a6fe0(*this_obj);
        list = l;
        count = *(uint64_t *)(l + 0x10);
    }
    for (;;) {
        slot = (uint64_t *)(list + 0x20 + idx * 8);
        while (true) {
            if (count == idx) {
                /* exhausted this list: move to the secondary list */
                idx = *(uint64_t *)((uint64_t)this_obj + 0x10);
                if (idx == 0) {
                    FUN_0036b118(this_obj);
                } else {
                    FUN_00082484(0, idx, 0);
                    count = 0;
                    {
                        uint64_t i = 0;
                        uint64_t u3 = DAT_00657788;
                        do {
                            val = *(uint64_t *)(*(uint64_t *)((uint64_t)this_obj + count * 8 + 0x20) + 0x10);
                            if (DAT_00657790 >> 1 <= u3) {
                                FUN_00082484(1 < DAT_00657790, u3 + 1, 1);
                            }
                            count = count + 1;
                            DAT_00657788 = u3 + 1;
                            DAT_00657798[u3] = val;
                            u3 = u3 + 1;
                            i = i + 1;
                        } while (idx != i);
                        count = *(uint64_t *)((uint64_t)this_obj + 0x10);
                        FUN_0036b118(this_obj);
                        if (idx != count) {
                            /* SoftwareBreakpoint(1, 0xe248c) */
                            __builtin_trap();
                        }
                    }
                }
                r = FUN_000e250c(&DAT_00657778[0]);
                FUN_0036b118(&DAT_00657778[0]);
                if (((r.hi >> 32) & 0xff) == 1) {
                    return 0;
                }
                return r.lo;
            }
            idx = idx + 1;
            obj = *slot;
            FUN_0008e328();
            {
                uint64_t vbase = FUN_000027e8();
                (void)vbase;
            }
            thunk_FUN_0036b270(obj);
            {
                cl4_result_t er;
                uint64_t vbase = FUN_0008e328();
                er = ((cl4_result_t (*)(void))*(void **)(vbase + 0x50))();
                r.lo = er.lo;
                r_hi = er.hi;
            }
            if (r.lo == 0x455a454741505f5f && r_hi == 0xea00000000004f52) {
                FUN_0036b118(obj);
                FUN_003a25d4(r_hi);
            } else {
                uint64_t u3 = FUN_002a0cf8(r.lo, r_hi, 0x455a454741505f5f, 0xea00000000004f52, 0);
                FUN_003a25d4(r_hi);
                if ((u3 & 1) == 0) {
                    FUN_0036b118(obj);
                    break;
                }
                FUN_0036b118(obj);
            }
            slot = slot + 1;
            count = count - 1;
        }
        FUN_001dd77c();
        FUN_000e46d8();
        {
            uint64_t u3 = DAT_00657788;
            *(uint64_t *)((uint64_t)this_obj + 0x10) = u3 + 1;
            *(uint64_t *)((uint64_t)this_obj + u3 * 8 + 0x20) = obj;
        }
        return FUN_000e22c0();
    }
}

/* FUN_000e250c @ 0x000e250c   (est. cL4_find_min_consume)
 * Ghidra: void FUN_000e250c(long param_1)   [decompiler dropped return]
 * Finds the minimum element in the array at param_1+0x28 (count at +0x10,
 * seed at +0x20), consumes it via FUN_000e46d0, and returns it. The caller
 * (0xe20c4) consumes a 16-byte result {value, status}; the return was
 * reconstructed from that caller.
 * Confidence: low
 * Notes: empty list -> FUN_00068e14. */
cl4_result_t FUN_000e250c(uint64_t *param_1)
{
    uint64_t count;
    uint64_t min;
    uint64_t *arr;
    uint64_t i;
    uint64_t v;
    uint64_t cur;
    cl4_result_t r;

    count = *(uint64_t *)((uintptr_t)param_1 + 0x10);
    if (count == 0) {
        FUN_00068e14();
        r.lo = 0;
        r.hi = 1;
        return r;
    }
    min = *(uint64_t *)((uintptr_t)param_1 + 0x20);
    i = count - 1;
    if (i != 0) {
        arr = (uint64_t *)((uintptr_t)param_1 + 0x28);
        v = min;
        do {
            cur = *arr;
            if (v <= cur) {
                cur = v;
            } else {
                v = cur;
            }
            min = v;
            i = i - 1;
            arr = arr + 1;
        } while (i != 0);
    }
    FUN_000e46d0(min);
    r.lo = min;
    r.hi = 0;
    return r;
}

/* FUN_000e254c @ 0x000e254c   (est. cL4_find_min_consume_signed)
 * Ghidra: void FUN_000e254c(long param_1)   [decompiler dropped return]
 * Signed twin of FUN_000e250c: finds the minimum element and consumes it via
 * FUN_000e46d0. Return reconstructed from the min-search shape.
 * Confidence: low */
cl4_result_t FUN_000e254c(uint64_t *param_1)
{
    uint64_t count;
    uint64_t min;
    uint64_t *arr;
    uint64_t i;
    uint64_t v;
    uint64_t cur;
    cl4_result_t r;

    count = *(uint64_t *)((uintptr_t)param_1 + 0x10);
    if (count == 0) {
        FUN_00068e14();
        r.lo = 0;
        r.hi = 1;
        return r;
    }
    min = *(uint64_t *)((uintptr_t)param_1 + 0x20);
    i = count - 1;
    if (i != 0) {
        arr = (uint64_t *)((uintptr_t)param_1 + 0x28);
        v = min;
        do {
            cur = *arr;
            if (v <= cur) {
                cur = v;
            } else {
                v = cur;
            }
            min = v;
            i = i - 1;
            arr = arr + 1;
        } while (i != 0);
    }
    FUN_000e46d0(min);
    r.lo = min;
    r.hi = 0;
    return r;
}

/* FUN_000e258c @ 0x000e258c   (est. cL4_find_minmax)
 * Ghidra: undefined1 [16] FUN_000e258c(long param_1)
 * Finds the minimum (and maximum) elements in the array; returns
 * {min, 0} on success, or {0, 1} when the list is empty.
 * Confidence: high (shape matches all callers) */
cl4_result_t FUN_000e258c(uint64_t *param_1)
{
    uint64_t count;
    uint64_t lo, hi;
    uint64_t *arr;
    uint64_t i;
    uint64_t cur;
    uint64_t v;
    cl4_result_t r;

    count = *(uint64_t *)((uintptr_t)param_1 + 0x10);
    if (count != 0) {
        lo = *(uint64_t *)((uintptr_t)param_1 + 0x20);
        i = count - 1;
        hi = lo;
        v = lo;
        if (i != 0) {
            arr = (uint64_t *)((uintptr_t)param_1 + 0x28);
            do {
                cur = *arr;
                if (cur <= v) {
                    lo = cur;
                }
                if (v <= cur) {
                    hi = cur;
                }
                i = i - 1;
                v = lo;
                arr = arr + 1;
            } while (i != 0);
        }
        r.lo = v;
        r.hi = 0;
        return r;
    }
    r.lo = 0;
    r.hi = 1;
    return r;
}

/* FUN_000e25d8 @ 0x000e25d8   (est. cL4_find_minmax_consume)
 * Ghidra: void FUN_000e25d8(long param_1)
 * Finds the min (and max) element, then consumes the min via FUN_000e46d0;
 * empty list -> FUN_00068e14.
 * Confidence: medium */
void FUN_000e25d8(uint64_t *param_1)
{
    uint64_t count;
    uint64_t lo, hi;
    uint64_t *arr;
    uint64_t i;
    uint64_t cur;
    uint64_t v;

    count = *(uint64_t *)((uintptr_t)param_1 + 0x10);
    if (count != 0) {
        lo = *(uint64_t *)((uintptr_t)param_1 + 0x20);
        i = count - 1;
        hi = lo;
        v = lo;
        if (i != 0) {
            arr = (uint64_t *)((uintptr_t)param_1 + 0x28);
            do {
                cur = *arr;
                if (cur <= v) {
                    lo = cur;
                }
                if (v <= cur) {
                    hi = cur;
                }
                i = i - 1;
                v = lo;
                arr = arr + 1;
            } while (i != 0);
        }
        FUN_000e46d0(v);
        return;
    }
    FUN_00068e14();
}

/* FUN_000e2618 @ 0x000e2618   (est. cL4_find_minmax_u16)
 * Ghidra: uint FUN_000e2618(long param_1)
 * Finds the min and max of a ushort array (count at +0x10, seed at +0x20,
 * elements at +0x22); returns min | (empty ? 0x10000 : 0).
 * Confidence: high
 * Notes: Verified: body matches decompile exactly. */
uint32_t FUN_000e2618(uint64_t *param_1)
{
    uint32_t lo, hi, seed;
    uint16_t *arr;
    uint64_t i;
    uint16_t cur;
    uint32_t v;

    if (*(uint64_t *)((uintptr_t)param_1 + 0x10) == 0) {
        lo = 0;
        hi = 0x10000;
    } else {
        seed = (uint32_t)*(uint16_t *)((uintptr_t)param_1 + 0x20);
        i = *(uint64_t *)((uintptr_t)param_1 + 0x10) - 1;
        hi = 0;
        lo = seed;
        if (i != 0) {
            arr = (uint16_t *)((uintptr_t)param_1 + 0x22);
            v = seed;
            do {
                cur = *arr;
                lo = (uint32_t)cur;
                if (cur <= seed) {
                    lo = v;
                }
                if (seed <= (uint32_t)cur) {
                    seed = (uint32_t)cur;
                }
                i = i - 1;
                arr = arr + 1;
                v = lo;
            } while (i != 0);
            hi = 0;
        }
    }
    return hi | lo;
}

/* FUN_000e2668 @ 0x000e2668   (est. cL4_bitmap_find_extreme)
 * Ghidra: undefined1 [16] FUN_000e2668(undefined8 param_1)
 * Scans a bitmap (array of 64-bit words) and a parallel value array for the
 * set bit with the extreme (lowest) value, using a bit-reversal trick (swap
 * the halves, LZCOUNT) to locate bits. Returns {value, status}.
 * Confidence: low
 * Notes: SoftwareBreakpoint(1, 0xe27a4 / 0xe27a0); bit-reversal via masks;
 *   scratch filled by thunk_FUN_0006afb4, released by FUN_000e4614. */
cl4_result_t FUN_000e2668(uint64_t param_1)
{
    sk_bitmap_scratch_t sc;
    uint64_t count_words;
    uint64_t idx;
    uint64_t word;
    uint64_t pos;
    uint64_t cur_val;
    uint64_t best;
    uint64_t status;
    cl4_result_t r;

    thunk_FUN_0006afb4((uint64_t *)&sc);
    if (sc.cur_word == 0) {
        count_words = (sc.size + 0x40U) >> 6;
        idx = sc.word_idx;
        do {
            idx = idx + 1;
            if (idx == 0) {
                /* SoftwareBreakpoint(1, 0xe27a4): index overflow */
                __builtin_trap();
            }
            if ((long)count_words <= (long)idx) {
                thunk_FUN_0036b270(param_1);
                FUN_000e4614((uint64_t *)&sc);
                r.lo = 0;
                r.hi = 1;
                return r;
            }
            word = *(uint64_t *)(sc.bitmap + idx * 8);
        } while (word == 0);
        pos = clz64_swapped(word) | idx * 0x40;
        word = word - 1 & word;
        best = *(uint64_t *)(*(uint64_t *)(sc.values) + pos * 8);
        cur_val = best;
        for (;;) {
            while (word != 0) {
                uint64_t wp = clz64_swapped(word) | idx * 0x200;
                word = word - 1 & word;
                cur_val = *(uint64_t *)(*(uint64_t *)(sc.values) + wp);
                if (cur_val > best) {
                    best = cur_val;
                }
            }
            idx = idx + 1;
            if (idx == 0) {
                /* SoftwareBreakpoint(1, 0xe27a0): index overflow */
                __builtin_trap();
            }
            if ((long)count_words <= (long)idx) break;
            word = *(uint64_t *)(sc.bitmap + idx * 8);
        }
        thunk_FUN_0036b270(param_1);
        FUN_0036b118((uint64_t)sc.field0);
        status = 0;
        r.lo = cur_val;
        r.hi = status;
        return r;
    }
    /* first word already nonzero */
    word = sc.cur_word;
    pos = clz64_swapped(word) | 0;
    word = word - 1 & word;
    count_words = (sc.size + 0x40U) >> 6;
    idx = sc.word_idx;
    best = *(uint64_t *)(*(uint64_t *)(sc.values) + pos * 8);
    cur_val = best;
    for (;;) {
        while (word != 0) {
            uint64_t wp = clz64_swapped(word) | idx * 0x200;
            word = word - 1 & word;
            cur_val = *(uint64_t *)(*(uint64_t *)(sc.values) + wp);
            if (cur_val > best) {
                best = cur_val;
            }
        }
        idx = idx + 1;
        if (idx == 0) {
            /* SoftwareBreakpoint(1, 0xe27a0): index overflow */
            __builtin_trap();
        }
        if ((long)count_words <= (long)idx) break;
        word = *(uint64_t *)(sc.bitmap + idx * 8);
    }
    thunk_FUN_0036b270(param_1);
    FUN_0036b118((uint64_t)sc.field0);
    status = 0;
    r.lo = cur_val;
    r.hi = status;
    return r;
}

/* FUN_000e27a4 @ 0x000e27a4   (est. resource_append_bound)
 * Ghidra: undefined8 FUN_000e27a4(ulong param_1)
 * Bounds-checked append of param_1 into this->+0x10 count; on carry/overflow
 * it asserts via FUN_00002834(0x651838) and grows the array via FUN_000e37ec.
 * Overflow -> SoftwareBreakpoint(1, 0xe2804).
 * Confidence: low */
uint64_t FUN_000e27a4(uint64_t param_1)
{
    uint64_t this_obj;           /* unaff_x20 */
    uint64_t count;
    uint64_t sum;

    this_obj = 0;
    count = *(uint64_t *)(this_obj + 0x10);
    if (!__builtin_add_overflow(count, param_1, &sum)) {
        FUN_00002834(0x651838);
        (void)FUN_0036a940();
        (void)thunk_FUN_0036b270(sum);
        FUN_000e37ec(thunk_FUN_0036b270(sum), sum);
        return (uint64_t)(uintptr_t)FUN_0036a940();
    }
    /* SoftwareBreakpoint(1, 0xe2804): count overflow */
    __builtin_trap();
}

/* FUN_000e282c @ 0x000e282c   (est. component_asan_dylib_create)
 * Ghidra: void FUN_000e282c(long *param_1)
 * Creates a component descriptor that looks up the ASan dylib. It first
 * resolves the "_asan" and "_asan.dylib" component names via FUN_00163b38
 * (string/word construction), checks their presence via FUN_002abe60, then
 * allocates a descriptor (0x6618e0 name, size 0x49, tag 7) and fills its
 * fields (+0x10..+0x48) with the resolved component, names, and a flag.
 * Confidence: low
 * Notes: "_asan"=0x6e6173615f, "_asan.dylib"=0x79642e6e6173615f,
 *   "libdy"=0x62696c79642e; refs 0x6619c0/0x661940/0x6618e0. */
void FUN_000e282c(uint64_t *out)
{
    uint64_t this_obj;           /* unaff_x20 */
    cl4_result_t first;
    cl4_result_t second;
    uint64_t name1;
    uint64_t name2;
    uint64_t h;
    uint64_t v1, v2, v3;
    uint8_t  b;
    bool has_asan;

    this_obj = 0;
    name1 = *(uint64_t *)*(uint64_t *)(this_obj + 8);
    name2 = *(uint64_t *)(this_obj + 0x10);
    first = *(cl4_result_t *)(this_obj + 8);
    thunk_FUN_0036b270(name2);
    second = FUN_00163b38(0x6e6173615f, 0xe500000000000000, 0, 0xe000000000000000, name1, name2);
    if (second.hi == 0) {
        thunk_FUN_0036b270(name2);
    } else {
        FUN_003a25d4(name2);
        first = second;
    }
    {
        uint64_t f2 = first.hi;
        thunk_FUN_0036b270(first.hi);
        second = FUN_00163b38(0x79642e6e6173615f, 0xeb0000000062696c, 0x62696c79642e, 0xe600000000000000, first.lo, f2);
        FUN_003a25d4(f2);
        if (second.hi != 0) {
            FUN_003a25d4(f2);
            first = second;
        }
    }
    {
        uint64_t this_word = *(uint64_t *)(this_obj + 0);
        thunk_FUN_0036b270(first.hi);
        thunk_FUN_0036b270(this_word);
    }
    {
        uint64_t u6 = FUN_002abe60(0x6e6173615f, 0xe500000000000000, name1, name2);
        if ((u6 & 1) == 0) {
            has_asan = (FUN_002abe60(0x79642e6e6173615f, 0xeb0000000062696c, name1, name2) & 1) != 0;
        } else {
            has_asan = true;
        }
    }
    v1 = *(uint64_t *)(this_obj + 0x18);
    v2 = *(uint64_t *)(this_obj + 0x28);
    v3 = *(uint64_t *)(this_obj + 0x30);
    b  = *(uint8_t *)(this_obj + 0x38);
    out[3] = 0x6619c0;
    out[4] = 0x661940;
    h = (uint64_t)(uintptr_t)FUN_0036a940(0x6618e0, 0x49, 7);
    *out = h;
    thunk_FUN_0036b270(v3);
    FUN_003a25d4(first.hi);
    *(uint64_t *)(h + 0x10) = *(uint64_t *)(this_obj + 0);
    *(cl4_result_t *)(h + 0x18) = first;
    *(uint64_t *)(h + 0x28) = v1;
    *(uint8_t *)(h + 0x30) = has_asan ? 1 : 0;
    *(uint64_t *)(h + 0x38) = v2;
    *(uint64_t *)(h + 0x40) = v3;
    *(uint8_t *)(h + 0x48) = b;
}

/* FUN_000e29f4 @ 0x000e29f4   (est. resource_state_get16)
 * Ghidra: undefined1 [16] FUN_000e29f4(void)
 * Returns the 16-byte state at this->+0x28, retaining this->+0x30.
 * Confidence: low */
cl4_result_t FUN_000e29f4(void)
{
    uint64_t this_obj;           /* unaff_x20 */
    cl4_result_t r;

    this_obj = 0;
    r = *(cl4_result_t *)(this_obj + 0x28);
    thunk_FUN_0036b270(*(uint64_t *)(this_obj + 0x30));
    return r;
}

/* FUN_000e2a34 @ 0x000e2a34   (est. region_resource_print)
 * Ghidra: undefined1 [16] FUN_000e2a34(void)
 * Prints a RegionResource: "{name: <name>, entrypoint: 0x..., needsASANShadow:
 * "true"/"false"", uid: <uid>}" and returns {0xe000000000000000, 0}.
 * Confidence: high (string-matched "name: ", "needsASANShadow")
 * Notes: strings 0x5c4300 ("RegionResource(name: ") / 0x5c4320. */
cl4_result_t FUN_000e2a34(void)
{
    uint64_t this_obj;           /* unaff_x20 */
    bool fake;
    uint64_t name_word, name_word2;
    cl4_result_t r;

    this_obj = 0;
    FUN_002a4ab4(0x40);
    thunk_FUN_002acbb8(0x22203a656d616e7b, 0xe800000000000000); /* "{name: " */
    thunk_FUN_002acbb8(*(uint64_t *)(this_obj + 8), *(uint64_t *)(this_obj + 0x10));
    thunk_FUN_002acbb8(0xd000000000000011, 0x80000000005c4300);
    FUN_0001e790();
    FUN_000e46a4();
    FUN_001ebfb0();
    thunk_FUN_002acbb8();
    FUN_003a25d4(0);
    thunk_FUN_002acbb8(0xd000000000000014, 0x80000000005c4320); /* ", entrypoint: 0x" */
    fake = (*(uint8_t *)(this_obj + 0x20) & 1) == 0;
    name_word  = fake ? 0x65736c6166 : 0x65757274;      /* "false" / "true" */
    name_word2 = fake ? 0xe500000000000000 : 0xe400000000000000;
    thunk_FUN_002acbb8(name_word, name_word2);
    FUN_003a25d4(name_word2);
    thunk_FUN_002acbb8(0x3d64697575202c22, 0xe900000000000022); /* ", "uid=" */
    thunk_FUN_002acbb8(*(uint64_t *)(this_obj + 0x28), *(uint64_t *)(this_obj + 0x30));
    thunk_FUN_002acbb8(0x7d22, 0xe200000000000000);             /* "}" */
    r.lo = 0xe000000000000000;
    r.hi = 0;
    return r;
}

/* FUN_000e2ba0 @ 0x000e2ba0   (est. component_find_text_segment)
 * Ghidra: undefined8 FUN_000e2ba0(void)
 * Searches this's resource list for an element whose magic is __TEXT
 * (0x545845545f5f) with marker 0xe600000000000000; collects matching entries
 * and returns a value; on empty logs a build-root path (0x5c4390,
 * /AppleInternal/Library/BuildRoots/...).
 * Confidence: low
 * Notes: SoftwareBreakpoint(1, 0xe2c88); __TEXT magic 0x545845545f5f. */
uint64_t FUN_000e2ba0(void)
{
    uint64_t *this_obj;          /* unaff_x20 */
    uint64_t list;
    uint64_t count;
    uint64_t idx;
    uint64_t *slot;
    uint64_t obj;
    uint64_t r_hi;
    uint64_t result;
    cl4_result_t er;

    this_obj = 0;
    idx = 0;
    list = *this_obj;
    count = *(uint64_t *)(list + 0x10);
    do {
        slot = (uint64_t *)(list + 0x20 + idx * 8);
        for (;;) {
            if (count == idx) {
                uint64_t h = thunk_FUN_0036b270((uint64_t)(uintptr_t)FUN_0036a940(0xd000000000000020, 0x80000000005c4340,
                                      0x5c4390, 0xef, 2, 0x50, &DAT_00657778[0]));
                FUN_0036b118(&DAT_00657778[0]);
                result = *(uint64_t *)(h + 0x10);
                FUN_0036b118(h);
                return result;
            }
            idx = idx + 1;
            obj = *slot;
            FUN_0008e328();
            {
                uint64_t vbase = FUN_000027e8();
                (void)vbase;
            }
            thunk_FUN_0036b270(obj);
            {
                uint64_t vbase = FUN_0008e328();
                er = ((cl4_result_t (*)(void))*(void **)(vbase + 0x50))();
            }
            r_hi = er.hi;
            if (er.lo == 0x545845545f5f && r_hi == 0xe600000000000000) {
                FUN_003a25d4(r_hi);
                goto found;
            }
            {
                uint64_t u3 = FUN_002a0cf8(er.lo, r_hi, 0x545845545f5f, 0xe600000000000000, 0);
                FUN_003a25d4(r_hi);
                if ((u3 & 1) == 0) {
                    FUN_0036b118(obj);
                    count = count - 1;
                    slot = slot + 1;
                    continue;
                }
            }
        found:
            FUN_001dd77c();
            FUN_000e46d8();
            DAT_00657788 = DAT_00657788 + 1;
            DAT_00657798[DAT_00657788 - 1] = obj;
            return DAT_00657788 - 1;
        }
    } while (true);
}

/* FUN_000e2d20 @ 0x000e2d20   (est. component_find_by_name)
 * Ghidra: undefined8 FUN_000e2d20(undefined8 param_1, undefined8 param_2)
 * Searches this's resource list for an element whose 16-byte identity equals
 * {param_1, param_2}; returns the matching element pointer, or 0.
 * Confidence: medium */
uint64_t FUN_000e2d20(uint64_t param_1, uint64_t param_2)
{
    uint64_t *this_obj;          /* unaff_x20 */
    uint64_t list;
    uint64_t count;
    uint64_t *slot;
    uint64_t obj;
    cl4_result_t er;

    this_obj = 0;
    list = *this_obj;
    count = *(uint64_t *)(list + 0x10);
    slot = (uint64_t *)(list + 0x20);
    while (true) {
        if (count == 0) {
            return 0;
        }
        obj = *slot;
        FUN_000027e8();
        thunk_FUN_0036b270(obj);
        {
            uint64_t vbase = FUN_000027e8();
            er = ((cl4_result_t (*)(void))*(void **)(vbase + 0x50))();
        }
        if (er.lo == param_1 && er.hi == param_2) {
            FUN_003a25d4(er.hi);
            return obj;
        }
        {
            uint64_t u3 = FUN_002a0cf8(er.lo, er.hi, param_1, param_2, 0);
            FUN_003a25d4(er.hi);
            if ((u3 & 1) != 0) {
                return obj;
            }
        }
        FUN_0036b118(obj);
        count = count - 1;
        slot = slot + 1;
    }
}

/* FUN_000e2df0 @ 0x000e2df0   (est. resource_publish2)
 * Ghidra: void FUN_000e2df0(undefined8 param_1)
 * Publishes param_1's two name pairs (this->+8/+0x10 and +0x28/+0x30) via
 * FUN_001b9084.
 * Confidence: medium */
void FUN_000e2df0(uint64_t param_1)
{
    uint64_t this_obj;           /* unaff_x20 */

    this_obj = 0;
    FUN_001b9084((void *)param_1, *(uint64_t *)(this_obj + 8), *(uint64_t *)(this_obj + 0x10));
    FUN_001b9084((void *)param_1, *(uint64_t *)(this_obj + 0x28), *(uint64_t *)(this_obj + 0x30));
}

/* FUN_000e2e24 @ 0x000e2e24   (est. resource_compare_eq)
 * Ghidra: undefined8 FUN_000e2e24(long param_1, long param_2)
 * Compares two resources: returns 1 when both name pairs match; otherwise
 * consults FUN_002a0cf8 (a string/word comparison) for the first pair.
 * Confidence: medium */
uint64_t FUN_000e2e24(uint64_t p1, uint64_t p2)
{
    uint64_t u;

    if ((*(uint64_t *)(p1 + 8) != *(uint64_t *)(p2 + 8) ||
         *(uint64_t *)(p1 + 0x10) != *(uint64_t *)(p2 + 0x10)) &&
        ((u = FUN_002a0cf8(), (u & 1) == 0))) {
        return 0;
    }
    if (*(uint64_t *)(p1 + 0x28) == *(uint64_t *)(p2 + 0x28) &&
        *(uint64_t *)(p1 + 0x30) == *(uint64_t *)(p2 + 0x30)) {
        return 1;
    }
    return FUN_002a0cf8();
}

/* FUN_000e2ea0 @ 0x000e2ea0   (est. resource_build_publish)
 * Ghidra: void FUN_000e2ea0(void)
 * Builds a resource (via FUN_001a84f4), fills its two name pairs from
 * this->+8/+0x10 and +0x28/+0x30, then commits via FUN_001a8564.
 * Confidence: medium */
void FUN_000e2ea0(void)
{
    uint64_t this_obj;           /* unaff_x20 */
    uint8_t  builder[72];

    this_obj = 0;
    FUN_001a84f4(builder, 0);
    FUN_001b9084(builder, *(uint64_t *)(this_obj + 8), *(uint64_t *)(this_obj + 0x10));
    FUN_001b9084(builder, *(uint64_t *)(this_obj + 0x28), *(uint64_t *)(this_obj + 0x30));
    FUN_001a8564();
}

/* FUN_000e2efc @ 0x000e2efc   (est. resource_build_publish2)
 * Ghidra: void FUN_000e2efc(void)
 * Builds a resource, fills its two name pairs via FUN_000e2df0, then commits
 * via FUN_001a8564.
 * Confidence: medium */
void FUN_000e2efc(void)
{
    uint8_t builder[72];

    FUN_001a84f4(builder, 0);
    FUN_000e2df0((uint64_t)(uintptr_t)builder);
    FUN_001a8564();
}

/* FUN_000e2f4c @ 0x000e2f4c   (est. resource_vt78_call)
 * Ghidra: void FUN_000e2f4c(void)
 * Fetches the current object via FUN_000027e8 and calls its slot +0x78.
 * Confidence: low */
void FUN_000e2f4c(void)
{
    uint64_t obj;

    obj = FUN_000027e8();
    ((void (*)(void))*(void **)(obj + 0x78))();
}

/* FUN_000e2f84 @ 0x000e2f84   (est. resource_alloc_init)
 * Ghidra: undefined8 FUN_000e2f84(undefined8 param_1)
 * Allocates a resource handle via FUN_0036a940, initializes it via
 * FUN_000e2fc4(param_1), and returns the handle.
 * Confidence: medium */
uint64_t FUN_000e2f84(uint64_t param_1)
{
    uint64_t h;

    h = (uint64_t)(uintptr_t)FUN_0036a940();
    FUN_000e2fc4(param_1);
    return h;
}

/* FUN_000e2fc4 @ 0x000e2fc4   (est. resource_array_init)
 * Ghidra: void FUN_000e2fc4(long param_1)
 * Initializes a resource's element array from param_1: sets this->+0x18 = 0,
 * this->+0x10 = param_1, and this->+0x20 to a freshly allocated array of
 * param_1->+0x20 entries (or the global scratch DAT_00657778 when empty).
 * Negative count -> SoftwareBreakpoint(1, 0xe3040).
 * Confidence: medium
 * Notes: FUN_000e3eb4 allocs the array; thunk_FUN_00114330 zero-fills it. */
void FUN_000e2fc4(uint64_t param_1)
{
    uint64_t this_obj;           /* unaff_x20 */
    uint64_t count;
    uint8_t *arr;

    this_obj = 0;
    *(uint8_t *)(this_obj + 0x18) = 0;
    *(uint64_t *)(this_obj + 0x10) = param_1;
    count = *(uint64_t *)(param_1 + 0x20);
    if ((long)count >= 0) {
        if (count == 0) {
            arr = (uint8_t *)&DAT_00657778[0];
        } else {
            arr = (uint8_t *)FUN_000e3eb4(count, 0x64e670, (uint64_t)&DAT_004c2600[0]);
            *(uint64_t *)(arr + 0x10) = count;
            thunk_FUN_00114330(arr + 0x20, count << 3);
        }
        *(uint8_t **)(this_obj + 0x20) = arr;
        return;
    }
    /* SoftwareBreakpoint(1, 0xe3040): negative count */
    __builtin_trap();
}

/* FUN_000e3040 @ 0x000e3040   (est. resource_element_get)
 * Ghidra: undefined8 FUN_000e3040(ulong param_1)
 * Returns the element at index param_1 of this's array, lazily populating it
 * via vtable slot +0x88 when not yet present. Bounds-checked; out-of-range ->
 * SoftwareBreakpoint.
 * Confidence: medium
 * Notes: SoftwareBreakpoint(1, 0xe3158/0xe315c/0xe3160/0xe3164). */
uint64_t FUN_000e3040(uint64_t param_1)
{
    uint64_t this_obj;           /* unaff_x20 */
    uint8_t  snap1[24];
    uint8_t  snap2[24];
    uint64_t arr;
    uint64_t count;
    uint64_t val;
    int success;                 /* unaff_x21 */

    this_obj = 0;
    if ((long)param_1 < 0) {
        /* SoftwareBreakpoint(1, 0xe3158) */
        __builtin_trap();
    }
    FUN_000867a8(this_obj + 0x20, snap1);
    FUN_0036a1a0();
    arr = *(uint64_t *)(this_obj + 0x20);
    count = *(uint64_t *)(arr + 0x10);
    if (count <= param_1) {
        /* SoftwareBreakpoint(1, 0xe315c): index past count */
        __builtin_trap();
    }
    if (*(uint64_t *)(arr + param_1 * 8 + 0x20) == 0) {
        uint64_t vbase = FUN_000027e8();
        val = ((uint64_t (*)(uint64_t))*(void **)(vbase + 0x88))(param_1);
        if (success != 0) {
            return val;
        }
        FUN_0036a1a0(this_obj + 0x20, snap2, 0x21, 0);
        arr = *(uint64_t *)(this_obj + 0x20);
        count = FUN_003a261c(arr);
        *(uint64_t *)(this_obj + 0x20) = arr;
        if ((count & 1) == 0) {
            arr = FUN_0007bea4(arr);
        }
        if (*(uint64_t *)(arr + 0x10) <= param_1) {
            /* SoftwareBreakpoint(1, 0xe3164) */
            __builtin_trap();
        }
        *(uint64_t *)(arr + param_1 * 8 + 0x20) = val;
        *(uint64_t *)(this_obj + 0x20) = arr;
        FUN_0036a20c(snap2);
        count = *(uint64_t *)(arr + 0x10);
    }
    if (param_1 < count) {
        return *(uint64_t *)(arr + param_1 * 8 + 0x20);
    }
    /* SoftwareBreakpoint(1, 0xe3160) */
    __builtin_trap();
}

/* FUN_000e3164 @ 0x000e3164   (est. resource_fill_all)
 * Ghidra: void FUN_000e3164(void)
 * Populates every element of this's array (calling vtable slot +0x88 for
 * each empty slot), then retains the array. When this->+0x18 == 1 it is
 * already populated and just re-validates.
 * Confidence: medium */
void FUN_000e3164(void)
{
    uint64_t this_obj;           /* unaff_x20 */
    uint8_t  snap[24];
    uint64_t arr;
    uint64_t count;
    uint64_t i;
    int success;                 /* unaff_x21 */

    this_obj = 0;
    if (*(uint8_t *)(this_obj + 0x18) == 1) {
        FUN_000867a8(this_obj + 0x20, snap);
        FUN_0036a1a0();
        arr = *(uint64_t *)(this_obj + 0x20);
    } else {
        FUN_000867a8(this_obj + 0x20, snap);
        FUN_0036a1a0();
        arr = *(uint64_t *)(this_obj + 0x20);
        count = *(uint64_t *)(arr + 0x10);
        if (count != 0) {
            for (i = 0; i < count; i++) {
                if (*(uint64_t *)(*(uint64_t *)(this_obj + 0x20) + 0x10) <= i) {
                    /* SoftwareBreakpoint(1, 0xe3238) */
                    __builtin_trap();
                }
                if (*(uint64_t *)(*(uint64_t *)(this_obj + 0x20) + i * 8 + 0x20) == 0) {
                    uint64_t vbase = FUN_000027e8();
                    ((void (*)(uint64_t))*(void **)(vbase + 0x88))(i);
                    if (success != 0) {
                        return;
                    }
                }
            }
            arr = *(uint64_t *)(this_obj + 0x20);
        }
        *(uint8_t *)(this_obj + 0x18) = 1;
    }
    thunk_FUN_0036b270(arr);
}

/* FUN_000e3238 @ 0x000e3238   (est. resource_destroy_all)
 * Ghidra: void FUN_000e3238(void)
 * Destroys every element of this's array (via FUN_0001a1c8 /
 * FUN_0014b1f8 with 5 tag addresses), then releases the array and the
 * backing objects at this->+0x10 / +0x20.
 * Confidence: low
 * Notes: SoftwareBreakpoint(1, 0xe3358); tags 0x666920/0x665f60/0x6667d8/
 *   0x665cd8. */
void FUN_000e3238(void)
{
    uint64_t this_obj;           /* unaff_x20 */
    uint8_t  snap[24];
    uint64_t arr;
    uint64_t count;
    uint64_t i;
    uint64_t obj;

    this_obj = 0;
    FUN_000867a8(this_obj + 0x20, snap);
    FUN_0036a1a0();
    arr = *(uint64_t *)(this_obj + 0x20);
    count = *(uint64_t *)(arr + 0x10);
    if (count != 0) {
        thunk_FUN_0036b270(arr);
        for (i = 0; i < count; i++) {
            if (*(uint64_t *)(arr + 0x10) <= i) {
                /* SoftwareBreakpoint(1, 0xe3358) */
                __builtin_trap();
            }
            obj = *(uint64_t *)(arr + i * 8 + 0x20);
            if (obj != 0) {
                uint64_t h = FUN_0001a1c8(obj, 0x666920, 0x665f60, 0x6667d8, 0x665cd8);
                FUN_0014b1f8(h, 0x666920, 0x665f60, 0x6667d8, 0x665cd8);
                FUN_004b23d8();
            }
        }
        FUN_0036b118(arr);
    }
    FUN_0036b118(*(uint64_t *)(this_obj + 0x10));
    FUN_0036b118(*(uint64_t *)(this_obj + 0x20));
}

/* FUN_000e3418 @ 0x000e3418   (est. resource_destroy_all_release)
 * Ghidra: void FUN_000e3418(void)
 * Destroys all elements (FUN_000e3238) then completes via FUN_0036b6ac.
 * Confidence: medium */
void FUN_000e3418(void)
{
    FUN_000e3238();
    FUN_0036b6ac();
}

/* FUN_000e341c @ 0x000e341c   (est. resource_destroy_all_release2)
 * Ghidra: void FUN_000e341c(void)
 * Same as FUN_000e3418 (destroy all, then complete).
 * Confidence: medium */
void FUN_000e341c(void)
{
    FUN_000e3238();
    FUN_0036b6ac();
}
