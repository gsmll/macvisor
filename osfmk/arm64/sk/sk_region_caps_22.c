/* Recreated from exclavecore_bundle.t8142.RELEASE.im4p (cL4 Secure Kernel,
 * arm64e, image base 0) — the cL4 (Apple seL4-derived) microkernel (GL1).
 * Ground truth: Ghidra FUN_ names + addresses in program cl4_kernel.raw.
 * All names are estimates unless string/header-matched.
 *
 * Slice 22: 0x000f66a4 - 0x000f9b28.
 *
 * This region is the ExclaveKit resource capability broker: functions that
 * mint/allocate component resource capabilities (untyped, frame, hypercall
 * resource, ExclaveKitImageResource, AddressSpaceIDResource), walk and sort
 * capability ranges, and report cL4 exception/error results.  cL4/seL4
 * vocabulary is used for naming.  Confidence is medium unless a string
 * (Swift class/vtable descriptor) matches (high).
 */
#include "sk_internal.h"

/* ---- Shared kernel helpers (out of slice) ----
 * FUN_002a4ab4    — enter monitored/trap context, recording an exception code.
 * FUN_003a25d4    — monitor lock/save primitive (takes a status word).
 * FUN_00027724    — resolve a PC-relative branch/jump slot to its code target.
 * thunk_FUN_002acbb8 — completion/return primitive used after error logging.
 * FUN_000fc85c    — formatted kernel panic/log (fmt, ...) varargs.
 * FUN_0036a940    — typed allocation/zone get (name, size, kind) -> object.
 * FUN_0036b270    — retain/reference helper.
 * FUN_0036b118    — release/reference drop helper.
 * FUN_0036b6f4    — panic on corrupted state.
 * FUN_0036b6ac / FUN_0036b21c / FUN_0036986c / FUN_0036b8c0 / FUN_0036b8b0 /
 * FUN_0036a1a0 / FUN_00365b6c / FUN_0036993c / FUN_003625e4 / FUN_003a261c —
 * container/vector/refcount utilities used across the broker.
 * FUN_001000b8, FUN_0006cf50, FUN_000fd6cc, FUN_000fd268, FUN_000fd854,
 * FUN_000fd6cc, FUN_000fe594, FUN_000fe618, FUN_0006e7c0, FUN_00077070,
 * FUN_0006a4c0, FUN_00072570, FUN_00258c60, FUN_0006f078, FUN_002591b4,
 * FUN_000730a4, FUN_00082464, FUN_000a022c, FUN_000026e8, FUN_0004e220,
 * FUN_0004e314, FUN_0004e138, FUN_0004e074, FUN_0004e104, FUN_0004b520,
 * FUN_0004b664, FUN_000a5b60, FUN_000aa3ac, FUN_00075624, FUN_00069970,
 * FUN_0007201c, FUN_00117d14, FUN_0029369c, FUN_0007be74, FUN_000f6530,
 * FUN_000f6518, FUN_000f9b4c, FUN_0004e220, FUN_0036a940, FUN_0036b7f8,
 * FUN_0036b8c0, FUN_00077770, FUN_000f9a0c, FUN_0036a1a0 — deep kernel/
 * container machinery recreated elsewhere; used verbatim here.
 */
extern uint64_t FUN_002a4ab4(uint64_t);
extern uint64_t FUN_003a25d4(uint64_t);
extern uint64_t FUN_00027724(uint64_t);
extern void thunk_FUN_002acbb8(void);
extern void thunk_FUN_002acbb8_2(uint64_t, uint64_t);
extern uint64_t FUN_000fc85c(void);
extern uint64_t FUN_0036a940(void);
extern uint64_t FUN_0036a940_3(uint64_t, uint64_t, uint64_t);
extern void FUN_0036b270(void);
extern void FUN_0036b270_1(uint64_t);
extern void FUN_0036b118(void);
extern void FUN_0036b118_1(uint64_t);
extern void FUN_0036b6f4(void);
extern void FUN_0036b6ac(void);
extern void FUN_0036b21c(void);
extern void FUN_0036986c(void);
extern void FUN_0036b8c0(uint64_t);
extern uint64_t FUN_0036b8b0(uint64_t);
extern void FUN_0036a1a0(uint64_t, uint64_t, uint64_t, uint64_t);
extern void FUN_00365b6c(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern void FUN_0036993c(uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t FUN_003625e4(void);
extern uint64_t FUN_003a261c(uint64_t);
extern uint64_t FUN_001000b8(uint64_t);
extern uint64_t FUN_0006cf50(void);
extern uint64_t FUN_000fd6cc(uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t FUN_000fd268(uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t FUN_000fd854(uint64_t, uint64_t);
extern uint64_t FUN_000fe594(void);
extern uint64_t FUN_000fe618(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern void FUN_0006e7c0(uint64_t, uint64_t);
extern void FUN_00077070(uint64_t, uint64_t);
extern uint64_t FUN_0006a4c0(uint64_t, uint64_t);
extern uint64_t FUN_00072570(void);
extern uint64_t FUN_00258c60(void);
extern void FUN_0006f078(uint64_t);
extern void FUN_002591b4(void);
extern uint64_t FUN_000730a4(void);
extern void FUN_00082464(void);
extern uint64_t FUN_000a022c(uint64_t, uint64_t);
extern void FUN_000026e8(uint64_t);
extern uint64_t FUN_0004e220(void);
extern uint64_t FUN_0004e314(uint64_t, uint64_t, uint64_t, uint64_t);
extern void FUN_0004e138(uint64_t, uint64_t, uint64_t);
extern uint64_t FUN_0004e074(void);
extern void FUN_0004e104(uint64_t);
extern uint64_t FUN_0004b520(void);
extern void FUN_0004b664(uint64_t);
extern uint64_t FUN_000a5b60(void);
extern void FUN_000aa3ac(void);
extern void FUN_00075624(uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t FUN_00069970(uint64_t, uint64_t, uint64_t);
extern void FUN_0007201c(uint64_t, uint64_t, uint64_t);
extern void FUN_00117d14(void);
extern uint64_t FUN_0029369c(uint64_t);
extern uint64_t FUN_0007be74(uint64_t);
extern uint64_t FUN_000f6530(void);
extern void FUN_000f6518(void);
extern void FUN_000f9b4c(void);
extern void FUN_0036b7f8(uint64_t, uint64_t);
extern void FUN_00077770(uint64_t);
extern void FUN_0036a1a0_2(void);
extern uint64_t FUN_0036a940_1(void);
extern void FUN_0036b270_2(void);
extern void FUN_000f9a0c(uint64_t, uint64_t);
extern void FUN_000f99d4(void);
extern void FUN_000f99f8(void);
extern uint64_t FUN_000f9680(uint64_t, uint64_t, uint64_t, uint64_t);
extern void FUN_000f9930(uint64_t);
extern void *FUN_000f946c(int64_t, uint64_t, uint64_t);
extern void *FUN_000f9514(int64_t);
extern void *FUN_000f958c(int64_t);
extern void *thunk_FUN_000f9608(int64_t);
extern void *FUN_000f9608(int64_t);
extern void *FUN_000f9944(int64_t, int64_t);
extern void FUN_000f8c94(uint64_t *);
extern void FUN_000f8dd8(uint64_t *, uint64_t, uint64_t *, uint64_t);
extern void FUN_000f9194(int64_t, int64_t, int64_t, uint64_t *);
extern uint64_t FUN_000f920c(uint64_t *, uint64_t, uint64_t *);
extern uint64_t FUN_000f9734(uint32_t *, uint32_t *, uint32_t *, uint32_t *);
extern uint32_t FUN_000f8a14(uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t FUN_000f81d4(uint64_t);
extern void FUN_000f7de8(uint64_t *, uint64_t);
extern void FUN_000f79fc(uint64_t *);
extern uint64_t FUN_000f7154(uint64_t, uint64_t, uint64_t);
extern void FUN_000f7184(uint64_t, uint64_t);
extern uint64_t FUN_00002534(uint64_t, uint64_t);
extern uint64_t thunk_FUN_000126e8(void);
extern uint64_t FUN_0006d52c(void);
extern void FUN_000fca7c(void);
extern void FUN_001004f0(void);
extern void thunk_FUN_0036b270(uint64_t);
extern void FUN_0036b118_2(void);
extern void FUN_0036b118_3(uint64_t);
extern void FUN_0036b270_3(uint64_t);

/* Type/vtable descriptor symbols (data, out of slice). */
extern uint64_t DAT_00657778;
extern uint64_t DAT_00657798;
extern uint64_t DAT_004bb180;
extern uint64_t DAT_000f8c6c;
extern uint64_t DAT_0064e8c8;
extern uint64_t DAT_004c0720;
extern uint64_t DAT_0064e8c0;
extern uint64_t DAT_004c0718;
extern uint64_t DAT_004c3e80;
extern uint64_t DAT_004c3ec0;
extern uint64_t DAT_004c04b8;
extern uint64_t DAT_0064e838;
extern uint64_t DAT_004c0690;
extern uint64_t DAT_004c3ec8;

/* Forward declarations for functions defined later in this file. */
cl4_result_t FUN_000f66a4(void);
cl4_result_t FUN_000f6a54(void);
cl4_result_t FUN_000f6ae8(void);
cl4_result_t FUN_000f6b74(void);
cl4_result_t FUN_000f6d10(void);
cl4_result_t FUN_000f7604(void);
cl4_result_t FUN_000f76bc(void);
cl4_result_t FUN_000f776c(void);
cl4_result_t FUN_000f7af4(void);
cl4_result_t FUN_000f7ce0(void);
cl4_result_t FUN_000f7e84(void);
cl4_result_t FUN_000f8dc8(void);
cl4_result_t FUN_000f9a5c(void);
cl4_result_t FUN_000f98ac(uint64_t);
void FUN_000f69c0(uint64_t *, uint64_t);
void FUN_000f6af8(uint64_t *);
void FUN_000f7214(uint32_t *);
uint64_t FUN_000f722c(uint64_t, uint64_t *, uint64_t);
void FUN_000f73e8(uint64_t, uint64_t, uint64_t, uint64_t, uint32_t);
void FUN_000f748c(void);
void FUN_000f7520(uint64_t);
void FUN_000f754c(uint64_t);
void FUN_000f7550(uint64_t);
void FUN_000f7568(uint64_t *, uint64_t);
void FUN_000f76cc(uint64_t);
void FUN_000f76e4(uint64_t, uint64_t);
void FUN_000f775c(uint64_t *);
void FUN_000f78ac(void);
void FUN_000f79c0(uint64_t);
void FUN_000f7a30(uint64_t *);
uint64_t FUN_000f7b48(uint64_t, uint64_t *, uint64_t);
void FUN_000f7dcc(uint64_t *);
void FUN_000f7f64(void);
uint64_t FUN_000f7f90(uint64_t);
uint64_t FUN_000f7fe0(void);
void FUN_000f7ff8(uint64_t, uint64_t);
uint64_t FUN_000f87c8(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
void FUN_000f8a80(uint64_t, uint64_t, uint64_t);
void FUN_000f8acc(uint64_t, uint64_t, uint64_t);
void FUN_000f8b20(void);
void FUN_000f8bd0(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
void FUN_000f8c94(uint64_t *);
void FUN_000f8dd8(uint64_t *, uint64_t, uint64_t *, uint64_t);
void FUN_000f9194(int64_t, int64_t, int64_t, uint64_t *);
uint64_t FUN_000f920c(uint64_t *, uint64_t, uint64_t *);
void *FUN_000f946c(int64_t, uint64_t, uint64_t);
void *FUN_000f9514(int64_t);
void *FUN_000f958c(int64_t);
void *FUN_000f9608(int64_t);
uint64_t FUN_000f9680(uint64_t, uint64_t, uint64_t, uint64_t);
uint64_t FUN_000f9734(uint32_t *, uint32_t *, uint32_t *, uint32_t *);
void FUN_000f9930(uint64_t);
void *FUN_000f9944(int64_t, int64_t);
void FUN_000f99d4(void);
void FUN_000f99f8(void);
void FUN_000f9a0c(uint64_t, uint64_t);
uint64_t FUN_000f9a1c(void);

/* ========================================================================
 * FUN_000f66a4 @ 0x000f66a4   (est. exclave_image_frame_map_error)
 * Ghidra: undefined1 [16] FUN_000f66a4(void)
 * Reports an "ExclaveKitImageResource tree frame to map" failure (error
 * 0x2f) through the monitored trap context and returns the packed cL4
 * exception result {hi=message vtable 0x5c5bc0, lo=0xd00000000000002f}.
 * Used to signal that a requested resource tree frame cannot be mapped.
 * Confidence: medium
 * Notes: resolves slot 0x671df8, logs via string 0x677830, error pair matches
 *   the "tree frame to map" / "Brokered(ExclaveKitImageResource..." region. */
cl4_result_t FUN_000f66a4(void)
{
    uint64_t slot = 0x671df8;
    cl4_result_t res;
    uint64_t (*logfn)(uint64_t, uint64_t);

    FUN_002a4ab4(0x1d);                       /* enter trap ctx, code 0x1d */
    FUN_003a25d4(0xe000000000000000);         /* monitor lock */
    logfn = (void *)FUN_00027724(0x671df8);   /* resolve log slot */
    logfn(0x677830, slot);                    /* log format str + slot */
    thunk_FUN_002acbb8();                     /* return from logging */
    FUN_003a25d4(0);                          /* unlock */
    thunk_FUN_002acbb8_2(0x29, 0xe100000000000000);
    res.hi = 0x80000000005c5bc0;              /* "tree frame to map" vtable */
    res.lo = 0xd00000000000002f;              /* cL4 error 0x2f */
    return res;
}

/* FUN_000f676c @ 0x000f676c   (est. exclave_image_frame_map_error_entry)
 * Ghidra: void FUN_000f676c(void)
 * Thin entry that forwards to the shared trap error helper at 0x000f6518.
 * Confidence: medium */
void FUN_000f676c(void)
{
    FUN_000f6518();
}

/* FUN_000f6790 @ 0x000f6790   (est. exclave_image_frame_map_error_alias)
 * Ghidra: void FUN_000f6790(void)
 * Wrapper around FUN_000f66a4 (the tree-frame-map error reporter).
 * Confidence: medium */
void FUN_000f6790(void)
{
    FUN_000f66a4();
}

/* FUN_000f67b4 @ 0x000f67b4   (est. record_cap_fault)
 * Ghidra: void FUN_000f67b4(undefined8, undefined8)
 * Records a capability-fault/op into the frame at x20: captures the op result
 * (via FUN_000fd6cc) plus the two operand words into slots +0x10/+0x18/+0x20.
 * On a corrupted frame state (x21 != 0) panics instead.
 * Confidence: low (unaff frame registers x20/x21 not recovered)
 * Notes: stores into * (x20+0x18)=param2, *(x20+0x20)=result, *(x20+0x10)=param1 */
void FUN_000f67b4(uint64_t arg1, uint64_t arg2)
{
    uint64_t r;
    uint64_t base = 0;   /* unaff_x20: frame base */

    r = FUN_0006cf50();
    r = FUN_000fd6cc(FUN_001000b8(0), r, arg1, arg2);
    if (/*unaff_x21*/ 0 == 0) {
        *(uint64_t *)(base + 0x18) = arg2;
        *(uint64_t *)(base + 0x20) = r;
        *(uint64_t *)(base + 0x10) = arg1;
    } else {
        FUN_0036b6f4();
    }
}

/* FUN_000f6854 @ 0x000f6854   (est. exclave_image_mint_untyped_failed)
 * Ghidra: void FUN_000f6854(undefined8,undefined8,undefined8,undefined8)
 * Reports "Could not mint untyped for ExclaveKitImageResource, cnode index:"
 * plus init(physicalAddress:size:) failure (error 0x2c). Logs through the
 * monitored trap context twice, then calls the formatted panic FUN_000fc85c
 * with the cnode-index/init message and four arguments.
 * Confidence: medium
 * Notes: string 0x5c5bf0 "Could not mint untyped...", 0x5c5c40 build root,
 *   0x5c5d60 "init(physicalAddress:size:)" */
void FUN_000f6854(uint64_t a1, uint64_t a2, uint64_t a3, uint64_t a4)
{
    uint64_t slot = 0x671848;
    uint64_t (*logfn)(uint64_t, uint64_t);

    FUN_002a4ab4(0x31);
    FUN_003a25d4(0xe000000000000000);
    logfn = (void *)FUN_00027724(0x671848);
    logfn(0x677790, slot);
    thunk_FUN_002acbb8();
    FUN_003a25d4(0);
    thunk_FUN_002acbb8_2(0x3a, 0xe100000000000000);
    logfn(0x677790, slot);
    thunk_FUN_002acbb8();
    FUN_003a25d4(0);
    FUN_000fc85c();  /* formatted panic: msg + cnode index + init(fmt) + args */
    FUN_003a25d4(0x80000000005c5bf0);
}

/* FUN_000f69c0 @ 0x000f69c0   (est. alloc_hypercall_resource)
 * Ghidra: void FUN_000f69c0(undefined8 *, undefined8)
 * Allocates a HypercallResource object: reserves a typed zone object
 * (tag 0x652590, size 0x51), retains it, computes its result, and stores the
 * object plus its vtable (0x6624a0) into the caller's slot array.
 * Confidence: medium
 * Notes: slot[3]=0x652590 (type tag), slot[4]=0x6624a0 (vtable) */
void FUN_000f69c0(uint64_t *slot, uint64_t param2)
{
    uint64_t obj;

    FUN_0036a940_3(0x652590, 0x51, 7);
    FUN_0036b270();
    FUN_0036b270_1(param2);
    obj = FUN_000f6530();
    if (/*unaff_x21*/ 0 == 0) {
        slot[3] = 0x652590;
        slot[4] = 0x6624a0;
        slot[0] = obj;
    }
}

/* FUN_000f6a54 @ 0x000f6a54   (est. exclave_image_resource_error)
 * Ghidra: undefined1 [16] FUN_000f6a54(void)
 * Returns packed cL4 error for ExclaveKitImageResource (hi = vtable
 * 0x4c3a40, lo = error 0x17).
 * Confidence: high (vtable string "ExclaveKitImageResource" at 0x4c3a40) */
cl4_result_t FUN_000f6a54(void)
{
    cl4_result_t res;
    res.hi = 0x80000000004c3a40;
    res.lo = 0xd000000000000017;
    return res;
}

/* FUN_000f6a70 @ 0x000f6a70   (est. alloc_hypercall_resource_a)
 * Ghidra: void FUN_000f6a70(void)
 * Alias of FUN_000f69c0 (HypercallResource allocation).
 * Confidence: medium */
void FUN_000f6a70(void)
{
    FUN_000f69c0(0, 0);
}

/* FUN_000f6a74 @ 0x000f6a74   (est. alloc_hypercall_resource_b)
 * Ghidra: void FUN_000f6a74(void)
 * Alias of FUN_000f69c0 (HypercallResource allocation).
 * Confidence: medium */
void FUN_000f6a74(void)
{
    FUN_000f69c0(0, 0);
}

/* FUN_000f6a88 @ 0x000f6a88   (est. exclave_image_resource_error_code)
 * Ghidra: undefined8 FUN_000f6a88(void)
 * Emits the ExclaveKitImageResource error and returns its lo code 0x17.
 * Confidence: high */
uint64_t FUN_000f6a88(void)
{
    FUN_000f6a54();
    return 0xd000000000000017;
}

/* FUN_000f6a8c @ 0x000f6a8c   (est. exclave_image_resource_error_code_b)
 * Ghidra: undefined8 FUN_000f6a8c(void)
 * Duplicate of FUN_000f6a88.
 * Confidence: high */
uint64_t FUN_000f6a8c(void)
{
    FUN_000f6a54();
    return 0xd000000000000017;
}

/* FUN_000f6ae8 @ 0x000f6ae8   (est. type_tag_652520)
 * Ghidra: undefined1 [16] FUN_000f6ae8(void)
 * Returns the type tag 0x652520 zero-extended as a 16-byte value.
 * Confidence: medium */
cl4_result_t FUN_000f6ae8(void)
{
    cl4_result_t res;
    res.lo = 0x652520;
    res.hi = 0;
    return res;
}

/* FUN_000f6af8 @ 0x000f6af8   (est. alloc_hypercall_resource_obj)
 * Ghidra: void FUN_000f6af8(long *)
 * Allocates a HypercallResource object with frame capture: reserves a zone
 * object (tag 0x652660, size 0x18), stores the frame base into +0x10, and
 * publishes {tag, vtable 0x6624f8, obj} into the caller slot array.
 * Confidence: medium */
void FUN_000f6af8(uint64_t *slot)
{
    uint64_t obj;

    obj = FUN_0036a940_3(0x652660, 0x18, 7);
    *(uint64_t *)(obj + 0x10) = /*unaff_x20*/ 0;
    slot[3] = 0x652660;
    slot[4] = 0x6624f8;
    slot[0] = obj;
    FUN_0036b270();
}

/* FUN_000f6b74 @ 0x000f6b74   (est. exclave_cap_validate_failed)
 * Ghidra: undefined1 [16] FUN_000f6b74(void)
 * Reports a capability-validate failure: logs through the trap context the
 * message region 0x5c5d60 (error 0x24), prints an ASCII chunk, and returns a
 * 16-byte result {hi = 0xe0..., lo = 0}.
 * Confidence: medium
 * Notes: ASCII chunk 0x76616c637865202c / 0xee00203a74694b65 ("Key it: , exclva") */
cl4_result_t FUN_000f6b74(void)
{
    uint64_t slot = 0x671848;
    uint64_t (*logfn)(uint64_t, uint64_t);
    cl4_result_t res;

    FUN_002a4ab4(0x37);
    thunk_FUN_002acbb8_2(0xd000000000000024, 0x80000000005c5d60);
    logfn = (void *)FUN_00027724(0x671848);
    logfn(0x677790, slot);
    thunk_FUN_002acbb8();
    FUN_003a25d4(0);
    thunk_FUN_002acbb8_2(0x76616c637865202c, 0xee00203a74694b65);
    logfn(0x677790, slot);
    thunk_FUN_002acbb8();
    FUN_003a25d4(0);
    thunk_FUN_002acbb8_2(0x29, 0xe100000000000000);
    res.lo = 0;
    res.hi = 0xe000000000000000 << 1;   /* ZEXT816(0xe0...)<<0x40 */
    return res;
}

/* FUN_000f6c9c @ 0x000f6c9c   (est. alloc_hypercall_resource_obj_a)
 * Ghidra: void FUN_000f6c9c(void)
 * Alias of FUN_000f6af8.
 * Confidence: medium */
void FUN_000f6c9c(void)
{
    FUN_000f6af8(0);
}

/* FUN_000f6ca0 @ 0x000f6ca0   (est. alloc_hypercall_resource_obj_b)
 * Ghidra: void FUN_000f6ca0(void)
 * Alias of FUN_000f6af8.
 * Confidence: medium */
void FUN_000f6ca0(void)
{
    FUN_000f6af8(0);
}

/* FUN_000f6cb4 @ 0x000f6cb4   (est. exclave_cap_validate_failed_entry)
 * Ghidra: void FUN_000f6cb4(void)
 * Alias of FUN_000f6b74.
 * Confidence: medium */
void FUN_000f6cb4(void)
{
    FUN_000f6b74();
}

/* FUN_000f6d10 @ 0x000f6d10   (est. type_tag_6525f8)
 * Ghidra: undefined1 [16] FUN_000f6d10(void)
 * Returns the type tag 0x6525f8 zero-extended as a 16-byte value.
 * Confidence: medium */
cl4_result_t FUN_000f6d10(void)
{
    cl4_result_t res;
    res.lo = 0x6525f8;
    res.hi = 0;
    return res;
}

/* FUN_000f6d20 @ 0x000f6d20   (est. sched_retire_cap_3)
 * Ghidra: void FUN_000f6d20(void)
 * Retires a capability with priority 3: fetches a new cap via FUN_000f7154
 * and dispatches it with kind 3 through the (post-branch) target.
 * Confidence: low (extraout_x8 branch target not recovered) */
void FUN_000f6d20(void)
{
    uint64_t cap = FUN_000f7154(0, 0, 0);
    FUN_000f7184(cap, 3);
    /* (*extraout_x8)();  branch-computed continuation */
}

/* FUN_000f6d58 @ 0x000f6d58   (est. resolve_pc_relative_slot)
 * Ghidra: long FUN_000f6d58(ulong)
 * Resolves a possibly-tagged PC-relative branch slot to its target address:
 * clears the tag bit (dereferencing an indirection when set) and applies the
 * relative displacement.
 * Confidence: medium
 * Notes: identical to the shared resolver FUN_00027724. */
uint64_t FUN_000f6d58(uint64_t slot)
{
    if ((slot & 1) != 0)
        slot = *(uint64_t *)(slot & ~1ull);
    return (uint64_t)(slot + 4) + (int64_t)*(int32_t *)(slot + 4);
}

/* FUN_000f6d88 @ 0x000f6d88   (est. sched_retire_cap_0)
 * Ghidra: void FUN_000f6d88(void)
 * Retires a capability with kind 0.
 * Confidence: low */
void FUN_000f6d88(void)
{
    uint64_t cap = FUN_000f7154(0, 0, 0);
    FUN_000f7184(cap, 0);
    /* (*extraout_x8)(); */
}

/* FUN_000f6dec @ 0x000f6dec   (est. sched_retire_cap_1)
 * Ghidra: void FUN_000f6dec(void)
 * Retires a capability with kind 1.
 * Confidence: low */
void FUN_000f6dec(void)
{
    uint64_t cap = FUN_000f7154(0, 0, 0);
    FUN_000f7184(cap, 1);
    /* (*extraout_x8)(); */
}

/* FUN_000f6f04 @ 0x000f6f04   (est. sched_retire_cap_2)
 * Ghidra: void FUN_000f6f04(void)
 * Retires a capability with kind 2.
 * Confidence: low */
void FUN_000f6f04(void)
{
    uint64_t cap = FUN_000f7154(0, 0, 0);
    FUN_000f7184(cap, 2);
    /* (*extraout_x8)(); */
}

/* FUN_000f6f3c @ 0x000f6f3c   (est. sched_retire_cap_7)
 * Ghidra: void FUN_000f6f3c(void)
 * Retires a capability with kind 7.
 * Confidence: low */
void FUN_000f6f3c(void)
{
    uint64_t cap = FUN_000f7154(0, 0, 0);
    FUN_000f7184(cap, 7);
    /* (*extraout_x8)(); */
}

/* FUN_000f6f74 @ 0x000f6f74   (est. sched_retire_cap_5)
 * Ghidra: void FUN_000f6f74(void)
 * Retires a capability with kind 5.
 * Confidence: low */
void FUN_000f6f74(void)
{
    uint64_t cap = FUN_000f7154(0, 0, 0);
    FUN_000f7184(cap, 5);
    /* (*extraout_x8)(); */
}

/* FUN_000f6fac @ 0x000f6fac   (est. sched_retire_cap_6)
 * Ghidra: void FUN_000f6fac(void)
 * Retires a capability with kind 6.
 * Confidence: low */
void FUN_000f6fac(void)
{
    uint64_t cap = FUN_000f7154(0, 0, 0);
    FUN_000f7184(cap, 6);
    /* (*extraout_x8)(); */
}

/* FUN_000f7154 @ 0x000f7154   (est. cap_retire_next)
 * Ghidra: undefined8 FUN_000f7154(undefined8,undefined8,undefined8)
 * Returns its first argument after resolving/checking the third through
 * FUN_000f6d58 (the slot resolver).
 * Confidence: medium */
uint64_t FUN_000f7154(uint64_t a1, uint64_t a2, uint64_t a3)
{
    FUN_000f6d58(a3);
    return a1;
}

/* FUN_000f7184 @ 0x000f7184   (est. cap_retire_dispatch_noop)
 * Ghidra: void FUN_000f7184(void)
 * No-op dispatch marker (empty body).  Ghidra signature is (void) but all
 * callers pass (cap, kind) in registers; the function ignores them.
 * Confidence: medium */
void FUN_000f7184(uint64_t cap, uint64_t kind)
{
    (void)cap; (void)kind;
}

/* FUN_000f7194 @ 0x000f7194   (est. resource_op_5arg)
 * Ghidra: undefined8 FUN_000f7194(undefined8 x5)
 * Invokes the 5-argument resource operation FUN_000f73e8 and returns the
 * reserved object handle.
 * Confidence: medium */
uint64_t FUN_000f7194(uint64_t a1, uint64_t a2, uint64_t a3, uint64_t a4, uint64_t a5)
{
    uint64_t obj = FUN_0036a940();
    FUN_000f73e8(a1, a2, a3, a4, a5);
    return obj;
}

/* FUN_000f7214 @ 0x000f7214   (est. read_owner_cap_info)
 * Ghidra: void FUN_000f7214(undefined8 *)
 * Reads the owner's capability info: copies the word at (x20+0x20) into the
 * caller slot and the 32-bit code at ((x20+0x10)->+0x20) into slot+1.
 * Confidence: low (unaff frame registers) */
void FUN_000f7214(uint32_t *slot)
{
    uint64_t base = /*unaff_x20*/ 0;
    uint32_t code = *(uint32_t *)(*(uint64_t *)(base + 0x10) + 0x20);
    slot[0] = (uint32_t)(uint64_t)*(uint64_t *)(base + 0x20);
    slot[1] = code;
}

/* FUN_000f722c @ 0x000f722c   (est. build_component_resource)
 * Ghidra: void FUN_000f722c(undefined8, long *, ulong)
 * Builds a component resource: stores the caller token at (x20+0x10), calls
 * the object's method at vtable+0x1b8 with a large descriptor, copies the
 * returned fields into the frame, then (depending on param_3 bit 0) invokes
 * either the vtable+0x70 or vtable+0x68 builder on the child object.  All
 * intermediate objects are released on success or on the panic path.
 * Confidence: low (unaff frame, unreachable block at 0x000f7390)
 * Notes: writes frame slots +0x18..+0x49; warning "removing unreachable block" */
uint64_t FUN_000f722c(uint64_t token, uint64_t *obj, uint64_t flag)
{
    uint64_t frame = /*unaff_x20*/ 0;
    uint64_t *child;
    uint64_t (*m)(uint64_t, int, int, int, int, int);
    uint64_t (*build)(uint64_t);

    *(uint64_t *)(frame + 0x10) = token;
    m = *(void **)(*obj + 0x1b8);
    FUN_0036b270();
    m((uint64_t)(void *)&frame, 1, 0, 0, 0, 0);
    if (/*unaff_x21*/ 0 == 0) {
        *(uint64_t *)(frame + 0x20) = 0;   /* uStack_88 */
        *(uint64_t *)(frame + 0x18) = 0;   /* local_90 */
        *(uint64_t *)(frame + 0x30) = 0;
        *(uint64_t *)(frame + 0x28) = 0;
        *(uint64_t *)(frame + 0x40) = 0;
        *(uint64_t *)(frame + 0x38) = 0;
        *(uint8_t *)(frame + 0x49) = 0;
        *(uint64_t *)(frame + 0x41) = 0;
        child = *(uint64_t **)(*(uint64_t *)(frame + 0x10) + 0x18);
        if ((flag & 1) == 0)
            build = *(void **)(*child + 0x70);
        else
            build = *(void **)(*child + 0x68);
        FUN_0036b270_1((uint64_t)child);
        build((uint64_t)(void *)&frame);
        FUN_0036b118_1((uint64_t)child);
        FUN_0036b118_1((uint64_t)obj);
        FUN_0036b118_1(token);
    } else {
        FUN_0036b118_1(token);
        FUN_0036b118_1((uint64_t)obj);
        FUN_0036b118_1(*(uint64_t *)(frame + 0x10));
        FUN_0036b6f4();
    }
    return frame;
}

/* FUN_000f73c4 @ 0x000f73c4   (est. read_owner_cap_info_entry)
 * Ghidra: void FUN_000f73c4(void)
 * Alias of FUN_000f7214.
 * Confidence: medium */
void FUN_000f73c4(void)
{
    FUN_000f7214(0);
}

/* FUN_000f73e8 @ 0x000f73e8   (est. register_component_resource)
 * Ghidra: void FUN_000f73e8(undefined8,undefined8,undefined8,undefined8,undefined4)
 * Registers a component resource: stores the token at (x20+0x10), computes a
 * capability result through FUN_000fd268, and records it plus a 32-bit tag
 * into the frame.  Panics if the frame is in a bad state.
 * Confidence: low (unaff frame registers) */
void FUN_000f73e8(uint64_t token, uint64_t a2, uint64_t a3, uint64_t a4, uint32_t tag)
{
    uint64_t frame = /*unaff_x20*/ 0;
    uint64_t r;

    *(uint64_t *)(frame + 0x10) = token;
    r = FUN_001000b8(0);
    r = FUN_000fd268(r, a2, a4, a3);
    if (/*unaff_x21*/ 0 == 0) {
        *(uint64_t *)(frame + 0x18) = r;
        *(uint32_t *)(frame + 0x20) = tag;
    } else {
        FUN_0036b6f4();
    }
}

/* FUN_000f748c @ 0x000f748c   (est. get_or_alloc_component_resource_cap)
 * Ghidra: void FUN_000f748c(void)
 * getOrAllocateComponentResourceCapFromEdge: requests an edge capability;
 * on failure reports error 0x17 ("edge requested but cannot be satisfied")
 * and on a second failure error 0x1c (component resource allocation).
 * Confidence: medium
 * Notes: strings 0x5c08c0 / 0x5c0910 confirm the ExclaveKit edge-broker role */
void FUN_000f748c(void)
{
    uint64_t st;

    FUN_000f76cc(/* "edge requested but cannot be satisfied" + 0x10 */ 0x5c08d0);
    FUN_000f76e4(0xd000000000000017, 0x8000000000000000);
    FUN_000fca7c();
    if (/*unaff_x21*/ 0 == 0) {
        FUN_000f76cc(/* "getOrAllocateComponentResourceCapFromEdge(edge:)" + 0x20 */ 0x5c0930);
        FUN_000f76e4(0xd00000000000001c, 0x8000000000000000);
        FUN_001004f0();
    }
}

/* FUN_000f7520 @ 0x000f7520   (est. build_resource_cap_0)
 * Ghidra: void FUN_000f7520(undefined8)
 * Builds a resource capability with flag 0.
 * Confidence: medium */
void FUN_000f7520(uint64_t slot)
{
    FUN_000f7568((uint64_t *)slot, 0);
}

/* FUN_000f754c @ 0x000f754c   (est. build_resource_cap_1)
 * Ghidra: void FUN_000f754c(undefined8)
 * Builds a resource capability with flag 1.
 * Confidence: medium */
void FUN_000f754c(uint64_t slot)
{
    FUN_000f7568((uint64_t *)slot, 1);
}

/* FUN_000f7550 @ 0x000f7550   (est. build_resource_cap_1b)
 * Ghidra: void FUN_000f7550(undefined8)
 * Duplicate of FUN_000f754c.
 * Confidence: medium */
void FUN_000f7550(uint64_t slot)
{
    FUN_000f7568((uint64_t *)slot, 1);
}

/* FUN_000f7568 @ 0x000f7568   (est. build_resource_cap_core)
 * Ghidra: void FUN_000f7568(undefined8 *, undefined8)
 * Core resource-cap builder: reserves a zone object (tag 0x652730, size 0x51),
 * retains it, runs FUN_000f722c to build the component resource, and publishes
 * {tag, vtable 0x6626a8, obj} into the caller slot array.
 * Confidence: medium */
void FUN_000f7568(uint64_t *slot, uint64_t flag)
{
    uint64_t obj;

    FUN_0036a940_3(0x652730, 0x51, 7);
    FUN_0036b270();
    FUN_0036b270_1(flag);
    obj = FUN_000f722c(0, 0, 0);
    if (/*unaff_x21*/ 0 == 0) {
        slot[3] = 0x652730;
        slot[4] = 0x6626a8;
        slot[0] = obj;
    }
}

/* FUN_000f7604 @ 0x000f7604   (est. hypercall_resource_error)
 * Ghidra: undefined1 [16] FUN_000f7604(void)
 * Returns packed cL4 error for a hypercall resource (hi = vtable 0x5c5db0,
 * lo = error 0x1c).
 * Confidence: medium */
cl4_result_t FUN_000f7604(void)
{
    cl4_result_t res;
    res.hi = 0x80000000005c5db0;
    res.lo = 0xd00000000000001c;
    return res;
}

/* FUN_000f7620 @ 0x000f7620   (est. release_saved_resource)
 * Ghidra: void FUN_000f7620(void)
 * Releases the resource at (x20+0x18) and re-enters the completion path.
 * Confidence: medium */
void FUN_000f7620(void)
{
    FUN_0036b118_1(*(uint64_t *)(/*unaff_x20*/ 0 + 0x18));
    FUN_0036b6ac();
}

/* FUN_000f7624 @ 0x000f7624   (est. release_saved_resource_b)
 * Ghidra: void FUN_000f7624(void)
 * Duplicate of FUN_000f7620.
 * Confidence: medium */
void FUN_000f7624(void)
{
    FUN_0036b118_1(*(uint64_t *)(/*unaff_x20*/ 0 + 0x18));
    FUN_0036b6ac();
}

/* FUN_000f764c @ 0x000f764c   (est. build_resource_cap_0_entry)
 * Ghidra: void FUN_000f764c(void)
 * Alias of FUN_000f7520.
 * Confidence: medium */
void FUN_000f764c(void)
{
    FUN_000f7520(0);
}

/* FUN_000f7650 @ 0x000f7650   (est. build_resource_cap_0_entry_b)
 * Ghidra: void FUN_000f7650(void)
 * Alias of FUN_000f7520.
 * Confidence: medium */
void FUN_000f7650(void)
{
    FUN_000f7520(0);
}

/* FUN_000f7664 @ 0x000f7664   (est. hypercall_resource_error_code)
 * Ghidra: undefined8 FUN_000f7664(void)
 * Emits the hypercall-resource error and returns its lo code 0x1c.
 * Confidence: medium */
uint64_t FUN_000f7664(void)
{
    FUN_000f7604();
    return 0xd00000000000001c;
}

/* FUN_000f7668 @ 0x000f7668   (est. hypercall_resource_error_code_b)
 * Ghidra: undefined8 FUN_000f7668(void)
 * Duplicate of FUN_000f7664.
 * Confidence: medium */
uint64_t FUN_000f7668(void)
{
    FUN_000f7604();
    return 0xd00000000000001c;
}

/* FUN_000f76bc @ 0x000f76bc   (est. type_tag_6526c0)
 * Ghidra: undefined1 [16] FUN_000f76bc(void)
 * Returns the type tag 0x6526c0 zero-extended as a 16-byte value.
 * Confidence: medium */
cl4_result_t FUN_000f76bc(void)
{
    cl4_result_t res;
    res.lo = 0x6526c0;
    res.hi = 0;
    return res;
}

/* FUN_000f76cc @ 0x000f76cc   (est. edge_error_note)
 * Ghidra: void FUN_000f76cc(void)
 * No-op note marker for an edge/component-resource error message.
 * Confidence: medium */
void FUN_000f76cc(uint64_t msg)
{
    (void)msg;
}

/* FUN_000f76e4 @ 0x000f76e4   (est. edge_error_emit)
 * Ghidra: void FUN_000f76e4(void)
 * No-op error-emit marker (error word + tagged address).
 * Confidence: medium */
void FUN_000f76e4(uint64_t err, uint64_t desc)
{
    (void)err; (void)desc;
}

/* FUN_000f76f8 @ 0x000f76f8   (est. resource_op_lookup)
 * Ghidra: undefined8 FUN_000f76f8(void)
 * Reserves an object and runs the lookup FUN_000f78ac.
 * Confidence: medium */
uint64_t FUN_000f76f8(void)
{
    uint64_t obj = FUN_0036a940();
    FUN_000f78ac();
    return obj;
}

/* FUN_000f775c @ 0x000f775c   (est. read_owner_cap_word)
 * Ghidra: void FUN_000f775c(undefined8 *)
 * Copies the word at ((x20+0x18)->+0x20) into the caller slot.
 * Confidence: low (unaff frame register) */
void FUN_000f775c(uint64_t *slot)
{
    *slot = *(uint64_t *)(*(uint64_t *)(/*unaff_x20*/ 0 + 0x18) + 0x20);
}

/* FUN_000f776c @ 0x000f776c   (est. hypercall_resource_bad_error)
 * Ghidra: undefined1 [16] FUN_000f776c(void)
 * Reports a hypercall-resource error (0x29) through the trap context and
 * returns {hi = vtable 0x5c5f50, lo = error 0x29}.
 * Confidence: medium */
cl4_result_t FUN_000f776c(void)
{
    uint64_t slot = 0x671df8;
    uint64_t (*logfn)(uint64_t, uint64_t);
    cl4_result_t res;

    FUN_002a4ab4(0x1d);
    FUN_003a25d4(0xe000000000000000);
    logfn = (void *)FUN_00027724(0x671df8);
    logfn(0x677830, slot);
    thunk_FUN_002acbb8();
    FUN_003a25d4(0);
    thunk_FUN_002acbb8_2(0x29, 0xe100000000000000);
    res.hi = 0x80000000005c5f50;
    res.lo = 0xd000000000000029;
    return res;
}

/* FUN_000f7838 @ 0x000f7838   (est. thunk_release_pair)
 * Ghidra: void thunk_FUN_000a91ec(void)
 * Releases the two words at (x20+0x10) and (x20+0x18).
 * Confidence: medium */
void thunk_FUN_000a91ec(void)
{
    FUN_0036b118_1(*(uint64_t *)(/*unaff_x20*/ 0 + 0x10));
    FUN_0036b118_1(*(uint64_t *)(/*unaff_x20*/ 0 + 0x18));
}

/* FUN_000f783c @ 0x000f783c   (est. release_pair_complete)
 * Ghidra: void FUN_000f783c(void)
 * Releases the frame pair then enters the completion path.
 * Confidence: medium */
void FUN_000f783c(void)
{
    thunk_FUN_000a91ec();
    FUN_0036b6ac();
}

/* FUN_000f7840 @ 0x000f7840   (est. release_pair_complete_b)
 * Ghidra: void FUN_000f7840(void)
 * Duplicate of FUN_000f783c.
 * Confidence: medium */
void FUN_000f7840(void)
{
    thunk_FUN_000a91ec();
    FUN_0036b6ac();
}

/* FUN_000f7864 @ 0x000f7864   (est. hypercall_resource_bad_error_entry)
 * Ghidra: void FUN_000f7864(void)
 * Alias of FUN_000f776c.
 * Confidence: medium */
void FUN_000f7864(void)
{
    FUN_000f776c();
}

/* FUN_000f7888 @ 0x000f7888   (est. read_owner_cap_word_entry)
 * Ghidra: void FUN_000f7888(void)
 * Alias of FUN_000f775c.
 * Confidence: medium */
void FUN_000f7888(void)
{
    FUN_000f775c(0);
}

/* FUN_000f78ac @ 0x000f78ac   (est. resource_cap_lookup)
 * Ghidra: void FUN_000f78ac(void)
 * Looks up a resource capability: fetches a current entry via FUN_0006d52c;
 * if none, publishes error 0x23 with a tagged descriptor; otherwise computes
 * a capability result through FUN_000fd854, reserves a zone object
 * (tag 0x652868, size 0x18), links the result into +0x10, records it at
 * (x20+0x18), and retains it.  Panics if the frame is corrupt.
 * Confidence: low (unaff frame registers, unresolved FUN_0006d52c) */
void FUN_000f78ac(void)
{
    uint64_t cur = FUN_0006d52c();
    uint64_t frame = /*unaff_x20*/ 0;
    uint64_t cap, obj;

    if (cur == 0) {
        FUN_0036993c(0x662d28, 0x662a78, 0, 0);
        /* publish error 0x23 + tagged desc via extraout_x1 */
        FUN_0036986c();
    } else {
        cap = FUN_001000b8(0);
        cap = FUN_000fd854(cur, cap);
        if (/*unaff_x21*/ 0 == 0) {
            *(uint64_t *)(frame + 0x10) = cap;
            obj = FUN_0036a940_3(0x652868, 0x18, 7);
            *(uint64_t *)(obj + 0x10) = cap;
            *(uint64_t *)(frame + 0x18) = obj;
            FUN_0036b270_1(cap);
            return;
        }
    }
    FUN_0036b6f4();
}

/* FUN_000f79c0 @ 0x000f79c0   (est. resource_attach_token)
 * Ghidra: void FUN_000f79c0(undefined8)
 * Reserves a zone object and stores the token into its +0x10 slot.
 * Confidence: medium */
void FUN_000f79c0(uint64_t token)
{
    uint64_t obj = FUN_0036a940();
    *(uint64_t *)(obj + 0x10) = token;
}

/* FUN_000f79fc @ 0x000f79fc   (est. build_hypercall_resource_0)
 * Ghidra: void FUN_000f79fc(undefined8)
 * Builds a hypercall resource with flag 0.
 * Confidence: medium */
void FUN_000f79fc(uint64_t *slot)
{
    FUN_000f7de8(slot, 0);
}

/* FUN_000f7a18 @ 0x000f7a18   (est. build_brokered_resource)
 * Ghidra: void FUN_000f7a18(void)
 * Entry into the brokered-resource builder.
 * Confidence: medium */
void FUN_000f7a18(void)
{
    FUN_000f7a30(0);
}

/* FUN_000f7a30 @ 0x000f7a30   (est. build_brokered_resource_core)
 * Ghidra: void FUN_000f7a30(long *)
 * Builds a brokered resource: constructs a child via FUN_000f79fc, looks up a
 * class entry (FUN_00002534) and a string builder (FUN_00365b6c), reserves a
 * zone object (tag 0x652800, size 0x20), links frame + child into +0x10/+0x18,
 * and publishes {tag, vtable 0x6626e8, obj}.
 * Confidence: low (unaff frame registers) */
void FUN_000f7a30(uint64_t *slot)
{
    uint8_t child[40];
    uint64_t local_38;
    uint64_t cls, obj;

    FUN_000f79fc((uint64_t *)child);
    if (/*unaff_x21*/ 0 == 0) {
        cls = FUN_00002534((uint64_t)&DAT_0064e8c8, (uint64_t)&DAT_004c0720);
        FUN_00365b6c((uint64_t)&local_38, (uint64_t)child, cls, 0x6528c8, 7);
        obj = FUN_0036a940_3(0x652800, 0x20, 7);
        *(uint64_t *)(obj + 0x10) = /*unaff_x20*/ 0;
        *(uint64_t *)(obj + 0x18) = local_38;
        slot[3] = 0x652800;
        slot[4] = 0x6626e8;
        slot[0] = obj;
        FUN_0036b270();
    }
}

/* FUN_000f7af4 @ 0x000f7af4   (est. brokered_hypercall_resource_error)
 * Ghidra: undefined1 [16] FUN_000f7af4(void)
 * Returns packed cL4 error for a brokered hypercall resource (hi = vtable
 * 0x4c3d10, lo = error 0x11).
 * Confidence: high (vtable string "HypercallResource"/"Brokered" at 0x4c3d10) */
cl4_result_t FUN_000f7af4(void)
{
    cl4_result_t res;
    res.hi = 0x80000000004c3d10;
    res.lo = 0xd000000000000011;
    return res;
}

/* FUN_000f7b10 @ 0x000f7b10   (est. build_brokered_resource_entry)
 * Ghidra: void FUN_000f7b10(void)
 * Alias of FUN_000f7a18.
 * Confidence: medium */
void FUN_000f7b10(void)
{
    FUN_000f7a18();
}

/* FUN_000f7b28 @ 0x000f7b28   (est. brokered_resource_error_code)
 * Ghidra: undefined8 FUN_000f7b28(void)
 * Emits the brokered-hypercall-resource error and returns its lo code 0x11.
 * Confidence: high */
uint64_t FUN_000f7b28(void)
{
    FUN_000f7af4();
    return 0xd000000000000011;
}

/* FUN_000f7b2c @ 0x000f7b2c   (est. brokered_resource_error_code_b)
 * Ghidra: undefined8 FUN_000f7b2c(void)
 * Duplicate of FUN_000f7b28.
 * Confidence: high */
uint64_t FUN_000f7b2c(void)
{
    FUN_000f7af4();
    return 0xd000000000000011;
}

/* FUN_000f7b48 @ 0x000f7b48   (est. build_brokered_hypercall_resource)
 * Ghidra: void FUN_000f7b48(undefined8, long *, ulong)
 * Builds a brokered hypercall resource: calls the object's vtable+0x1b8 method
 * with a 0xf descriptor, copies the returned fields into the frame, and (by
 * flag bit 0) invokes vtable+0x70 or vtable+0x68 on the child object.  All
 * intermediate objects are released on success or on the panic path.
 * Confidence: low (unaff frame, unreachable block at 0x000f7cac) */
uint64_t FUN_000f7b48(uint64_t token, uint64_t *obj, uint64_t flag)
{
    uint64_t frame = /*unaff_x20*/ 0;
    uint64_t *child;
    uint64_t (*m)(uint64_t, int, int, int, int, int);
    uint64_t (*build)(uint64_t);

    *(uint64_t *)(frame + 0x10) = token;
    m = *(void **)(*obj + 0x1b8);
    FUN_0036b270();
    m((uint64_t)(void *)&frame, 0xf, 0, 0, 0, 0);
    if (/*unaff_x21*/ 0 == 0) {
        *(uint64_t *)(frame + 0x20) = 0;
        *(uint64_t *)(frame + 0x18) = 0;
        *(uint64_t *)(frame + 0x30) = 0;
        *(uint64_t *)(frame + 0x28) = 0;
        *(uint64_t *)(frame + 0x40) = 0;
        *(uint64_t *)(frame + 0x38) = 0;
        *(uint8_t *)(frame + 0x49) = 0;
        *(uint64_t *)(frame + 0x41) = 0;
        child = *(uint64_t **)(*(uint64_t *)(frame + 0x10) + 0x10);
        if ((flag & 1) == 0)
            build = *(void **)(*child + 0x70);
        else
            build = *(void **)(*child + 0x68);
        FUN_0036b270_1((uint64_t)child);
        build((uint64_t)(void *)&frame);
        FUN_0036b118_1((uint64_t)child);
        FUN_0036b118_1((uint64_t)obj);
        FUN_0036b118_1(token);
    } else {
        FUN_0036b118_1(token);
        FUN_0036b118_1((uint64_t)obj);
        FUN_0036b118_1(*(uint64_t *)(frame + 0x10));
        FUN_0036b6f4();
    }
    return frame;
}

/* FUN_000f7ce0 @ 0x000f7ce0   (est. brokered_hypercall_error)
 * Ghidra: undefined1 [16] FUN_000f7ce0(void)
 * Reports a brokered-hypercall error (0x32) through the trap context and
 * returns {hi = vtable 0x5c5f80, lo = error 0x32}.
 * Confidence: medium */
cl4_result_t FUN_000f7ce0(void)
{
    uint64_t slot = 0x671df8;
    uint64_t (*logfn)(uint64_t, uint64_t);
    cl4_result_t res;

    FUN_002a4ab4(0x1d);
    FUN_003a25d4(0xe000000000000000);
    logfn = (void *)FUN_00027724(0x671df8);
    logfn(0x677830, slot);
    thunk_FUN_002acbb8();
    FUN_003a25d4(0);
    thunk_FUN_002acbb8_2(0x29, 0xe100000000000000);
    res.hi = 0x80000000005c5f80;
    res.lo = 0xd000000000000032;
    return res;
}

/* FUN_000f7da8 @ 0x000f7da8   (est. brokered_hypercall_error_entry)
 * Ghidra: void FUN_000f7da8(void)
 * Alias of FUN_000f7ce0.
 * Confidence: medium */
void FUN_000f7da8(void)
{
    FUN_000f7ce0();
}

/* FUN_000f7dcc @ 0x000f7dcc   (est. build_hypercall_resource_1)
 * Ghidra: void FUN_000f7dcc(undefined8)
 * Builds a hypercall resource with flag 1.
 * Confidence: medium */
void FUN_000f7dcc(uint64_t *slot)
{
    FUN_000f7de8(slot, 1);
}

/* FUN_000f7de8 @ 0x000f7de8   (est. build_hypercall_resource_core)
 * Ghidra: void FUN_000f7de8(undefined8 *, undefined8)
 * Core hypercall-resource builder: reserves a zone object (tag 0x6528c8,
 * size 0x51), retains it, runs FUN_000f7b48, and publishes
 * {tag, vtable 0x662750, obj} into the caller slot array.
 * Confidence: medium */
void FUN_000f7de8(uint64_t *slot, uint64_t flag)
{
    uint64_t obj;

    FUN_0036a940_3(0x6528c8, 0x51, 7);
    FUN_0036b270();
    FUN_0036b270_1(flag);
    obj = FUN_000f7b48(0, 0, 0);
    if (/*unaff_x21*/ 0 == 0) {
        slot[3] = 0x6528c8;
        slot[4] = 0x662750;
        slot[0] = obj;
    }
}

/* FUN_000f7e84 @ 0x000f7e84   (est. delegated_hypercall_resource_error)
 * Ghidra: undefined1 [16] FUN_000f7e84(void)
 * Returns packed cL4 error for a delegated hypercall resource (hi = vtable
 * 0x4c3d30, lo = error 0x1a).
 * Confidence: high (vtable string "DelegatedHypercallResource" at 0x4c3d30) */
cl4_result_t FUN_000f7e84(void)
{
    cl4_result_t res;
    res.hi = 0x80000000004c3d30;
    res.lo = 0xd00000000000001a;
    return res;
}

/* FUN_000f7ea0 @ 0x000f7ea0   (est. build_hypercall_resource_1_entry)
 * Ghidra: void FUN_000f7ea0(void)
 * Alias of FUN_000f7dcc.
 * Confidence: medium */
void FUN_000f7ea0(void)
{
    FUN_000f7dcc((uint64_t *)0);
}

/* FUN_000f7ea4 @ 0x000f7ea4   (est. build_hypercall_resource_1_entry_b)
 * Ghidra: void FUN_000f7ea4(void)
 * Alias of FUN_000f7dcc.
 * Confidence: medium */
void FUN_000f7ea4(void)
{
    FUN_000f7dcc((uint64_t *)0);
}

/* FUN_000f7eb8 @ 0x000f7eb8   (est. build_hypercall_resource_0_entry)
 * Ghidra: void FUN_000f7eb8(void)
 * Alias of FUN_000f79fc.
 * Confidence: medium */
void FUN_000f7eb8(void)
{
    FUN_000f79fc((uint64_t *)0);
}

/* FUN_000f7ebc @ 0x000f7ebc   (est. build_hypercall_resource_0_entry_b)
 * Ghidra: void FUN_000f7ebc(void)
 * Alias of FUN_000f79fc.
 * Confidence: medium */
void FUN_000f7ebc(void)
{
    FUN_000f79fc((uint64_t *)0);
}

/* FUN_000f7ed0 @ 0x000f7ed0   (est. delegated_resource_error_code)
 * Ghidra: undefined8 FUN_000f7ed0(void)
 * Emits the delegated-hypercall-resource error and returns its lo code 0x1a.
 * Confidence: high */
uint64_t FUN_000f7ed0(void)
{
    FUN_000f7e84();
    return 0xd00000000000001a;
}

/* FUN_000f7ed4 @ 0x000f7ed4   (est. delegated_resource_error_code_b)
 * Ghidra: undefined8 FUN_000f7ed4(void)
 * Duplicate of FUN_000f7ed0.
 * Confidence: high */
uint64_t FUN_000f7ed4(void)
{
    FUN_000f7e84();
    return 0xd00000000000001a;
}

/* FUN_000f7f64 @ 0x000f7f64   (est. resource_tag_dump)
 * Ghidra: void FUN_000f7f64(void)
 * Dumps the resource type tag 0x652798 via FUN_00077770.
 * Confidence: medium */
void FUN_000f7f64(void)
{
    FUN_00077770(0x652798);
}

/* FUN_000f7f74 @ 0x000f7f74   (est. build_brokered_resource_entry_b)
 * Ghidra: void FUN_000f7f74(void)
 * Alias of FUN_000f7b10.
 * Confidence: medium */
void FUN_000f7f74(void)
{
    FUN_000f7b10();
}

/* FUN_000f7f78 @ 0x000f7f78   (est. build_brokered_resource_entry_c)
 * Ghidra: void FUN_000f7f78(void)
 * Alias of FUN_000f7b10.
 * Confidence: medium */
void FUN_000f7f78(void)
{
    FUN_000f7b10();
}

/* FUN_000f7f90 @ 0x000f7f90   (est. resource_cap_check)
 * Ghidra: undefined8 FUN_000f7f90(undefined8)
 * Reserves an object and runs the capability-check FUN_000f81d4.
 * Confidence: medium */
uint64_t FUN_000f7f90(uint64_t param1)
{
    uint64_t obj = FUN_0036a940();
    FUN_000f81d4(param1);
    return obj;
}

/* FUN_000f7fe0 @ 0x000f7fe0   (est. get_cap_buffer)
 * Ghidra: undefined8 FUN_000f7fe0(void)
 * Returns the capability buffer word (x20+0x20); if the frame is in the
 * "done/failed" state (x20+0x28 == 1) it hits a software breakpoint trap.
 * Confidence: low (unaff frame register)
 * Notes: SoftwareBreakpoint(1, 0xf7ff8) on state==1 */
uint64_t FUN_000f7fe0(void)
{
    uint64_t frame = /*unaff_x20*/ 0;

    if (*(char *)(frame + 0x28) != '\x01')
        return *(uint64_t *)(frame + 0x20);
    /* trap: SoftwareBreakpoint(1, 0xf7ff8) */
    ((void (*)(void))0)();
    return 0;
}

/* FUN_000f7ff8 @ 0x000f7ff8   (est. build_exclave_image_resource)
 * Ghidra: void FUN_000f7ff8(long, long)
 * Builds an ExclaveKitImageResource capability over the range [param_1, param_2):
 * validates the range against the buffer size, reserves zone objects
 * (0x6627c8 size 0x11, 0x6627f0 size 0x30), links frame/range into the image
 * descriptor, marshals it through FUN_000f99f8/FUN_0004b520, performs the
 * capability install via FUN_0004e138, and reports errors 0x47/0x24 if the
 * range or marshal fails.
 * Confidence: low (unaff frame, heavy marshalling)
 * Notes: SoftwareBreakpoint(1,0xf81d0/0xf81d4) on state/absent image; error
 *   descriptors 0x5c5fc0 / 0x5c6010 */
void FUN_000f7ff8(uint64_t start, uint64_t end)
{
    uint64_t frame = /*unaff_x20*/ 0;
    uint64_t len, img, imgop, desc, m;

    if (*(char *)(frame + 0x28) == '\x01')
        ((void (*)(void))0)();   /* SoftwareBreakpoint(1, 0xf81d0) */

    len = 0;
    if (start != 0)
        len = end - start;
    if (len < *(int64_t *)(frame + 0x20)) {
        FUN_000aa3ac();
        /* publish error 0x47 + desc 0x5c5fc0 */
        FUN_000f9a0c(0, 0);
    } else {
        img = FUN_0036a940_3(0x6627c8, 0x11, 7);
        *(uint8_t *)(img + 0x10) = 0;
        imgop = *(uint64_t *)(frame + 0x10);
        if (imgop == 0)
            ((void (*)(void))0)();   /* SoftwareBreakpoint(1, 0xf81d4) */
        m = *(uint64_t *)(imgop + 0x10);
        desc = FUN_0036a940_3(0x6627f0, 0x30, 7);
        *(uint64_t *)(desc + 0x10) = start;
        *(uint64_t *)(desc + 0x18) = end;
        *(uint64_t *)(desc + 0x20) = frame;
        *(uint64_t *)(desc + 0x28) = img;
        FUN_000f99f8();
        m = FUN_0004b520();
        FUN_0036b270_1(imgop);
        FUN_0036b270();
        FUN_0036b270_1(img);
        FUN_0036b118_1(desc);
        FUN_0004e138(imgop + 0x20, m, 0);
        FUN_0004b664(m);
        FUN_0036b118_1(imgop);
        FUN_0036a1a0(img + 0x10, 0, 0, 0);
        if (*(char *)(img + 0x10) == '\x01') {
            FUN_000aa3ac();
            /* publish error 0x24 + desc 0x5c6010 */
            FUN_000f9a0c(0, 0);
        }
        FUN_0036b118_1(img);
    }
}

/* FUN_000f81d4 @ 0x000f81d4   (est. collect_component_capabilities)
 * Ghidra: long FUN_000f81d4(long)
 * Collects all component resource capabilities reachable from param_1 into a
 * per-capability collection: iterates the input cap vector (elems at +0x20),
 * builds a bit-set indexed collection with type tags and object pointers, then
 * re-serializes the collected caps into the frame and validates the final
 * marshalled result, reporting error 0x44 on failure.
 * Confidence: low (large, heavy hashing/serialization)
 * Notes: SoftwareBreakpoint traps at 0xf8790/0xf8794/0xf8798/0xf87b8/0xf879c;
 *   error descriptor 0x5c6040; type tags 0x662840/0x662868/0x6628b8 */
uint64_t FUN_000f81d4(uint64_t caps_in)
{
    uint64_t frame = /*unaff_x20*/ 0;
    uint64_t count, i;
    uint64_t slot = (uint64_t)&DAT_00657798;

    *(uint64_t *)(frame + 0x10) = 0;
    *(uint64_t *)(frame + 0x20) = 0;
    *(uint8_t *)(frame + 0x28) = 1;

    count = *(uint64_t *)(caps_in + 0x10);
    if (count == 0) {
        FUN_0036b118_1(caps_in);
    } else {
        for (i = 0; i < count; i++) {
            /* per-cap: decode via FUN_0006e7c0/FUN_00077070/FUN_0006a4c0,
             * hash through FUN_003625e4, resolve cap key, and either
             * insert into the bit-set collection or grow the existing entry
             * (FUN_000730a4) in the cap table at slot[7]. */
            /* collect entry; on the "used" branch append into the entry
             * vector at (lVar9 + uVar10*0x28 + 0x20). */
        }
        FUN_0036b118_1(caps_in);
    }
    /* publish the collected table into the frame and re-serialize: */
    FUN_0036b118_1(*(uint64_t *)(frame + 0x10));
    *(uint64_t *)(frame + 0x18) = slot;
    FUN_0036b118_1(*(uint64_t *)(frame + 0x20));
    *(uint8_t *)(frame + 0x28) = 1;
    thunk_FUN_0036b270(*(uint64_t *)(frame + 0x18));
    /* build output cap vector (0x6628b8) and marshal via FUN_000f99d4/
     * FUN_000f99f8/FUN_0004b520/FUN_0004e138; if final flag set, error 0x44. */
    return frame;
}

/* FUN_000f87c8 @ 0x000f87c8   (est. component_cap_range_get)
 * Ghidra: undefined8 FUN_000f87c8(long,long,ulong,long,undefined8)
 * Fetches capability range [param_3] from the component's cap vector
 * (param_4): validates the index, decodes the range descriptor, and copies
 * it into [param_1, param_1+param_2) via FUN_000fe618.  Returns 1 on success,
 * 0 if the lookup finds nothing.
 * Confidence: low (unreachable block at 0x000f88a4)
 * Notes: traps at 0xf8a0c/0xf8a10/0xf8a14 on out-of-range indices */
uint64_t FUN_000f87c8(uint64_t dst, uint64_t len, uint64_t idx, uint64_t src, uint64_t token)
{
    uint64_t entry, r;

    FUN_0036a1a0(src + 0x10, 0, 0, 0);
    entry = FUN_0036b8b0(src + 0x10);
    if (entry == 0)
        return 0;
    r = FUN_000a022c(token, *(uint64_t *)(entry + 0x18));
    if (r == 0) {
        FUN_0036b118_1(entry);
        return 0;
    }
    /* idx bounds-checked against r->+0x10 */
    FUN_0006e7c0(r + idx * 0x28 + 0x20, (uint64_t)(void *)&dst);
    FUN_0036b118_1(r);
    FUN_00077070((uint64_t)(void *)&dst, 0);
    r = FUN_0006a4c0(0, 0);
    FUN_000fe618(dst, dst + len, 0, 0, r);
    FUN_0036b118_1(entry);
    FUN_000026e8(0);
    return 1;
}

/* FUN_000f8a14 @ 0x000f8a14   (est. cap_range_cmp_callback)
 * Ghidra: uint FUN_000f8a14(long, undefined8, undefined8, undefined8)
 * Callback that invokes the comparator stored at (param_1+0x20) while holding
 * the context (param_1+0x28), returning its low bit.
 * Confidence: medium */
uint32_t FUN_000f8a14(uint64_t self, uint64_t a, uint64_t b, uint64_t c)
{
    uint64_t (*cmp)(uint64_t, uint64_t, uint64_t);
    uint64_t ctx;

    cmp = *(void **)(self + 0x20);
    ctx = *(uint64_t *)(self + 0x28);
    FUN_0036b270_1(ctx);
    uint32_t r = (uint32_t)(uint64_t)cmp(a, b, c) & 1;
    FUN_0036b118_1(ctx);
    return r;
}

/* FUN_000f8a80 @ 0x000f8a80   (est. cap_range_comparator_destroy)
 * Ghidra: void FUN_000f8a80(undefined8, undefined8, long)
 * Destroys a cap-range comparator: releases the wrapped object and resets the
 * state flag at param_3+0x18 to 0.
 * Confidence: medium */
void FUN_000f8a80(uint64_t a, uint64_t b, uint64_t self)
{
    uint64_t obj = FUN_0004e220();

    FUN_0036a1a0(self + 0x10, 0, 1, 0);
    *(uint64_t *)(self + 0x10) = obj;
    *(uint8_t *)(self + 0x18) = 0;
}

/* FUN_000f8acc @ 0x000f8acc   (est. cap_range_cmp_invoke)
 * Ghidra: void FUN_000f8acc(long, undefined8, undefined8)
 * Invokes the comparator function pointer at (param_1+0x20) with (param_2,
 * param_3) while retaining the context (param_1+0x28).
 * Confidence: medium */
void FUN_000f8acc(uint64_t self, uint64_t a, uint64_t b)
{
    uint64_t (*cmp)(uint64_t, uint64_t);
    uint64_t ctx;

    cmp = *(void **)(self + 0x20);
    ctx = *(uint64_t *)(self + 0x28);
    FUN_0036b270_1(ctx);
    cmp(a, b);
    FUN_0036b118_1(ctx);
}

/* FUN_000f8b20 @ 0x000f8b20   (est. cap_range_table_teardown)
 * Ghidra: void FUN_000f8b20(void)
 * Tears down a capability-range table: for each live element in the vector at
 * (x20+0x10) releases the per-cap entries, releases the vector, and re-enters
 * the lock-released completion path.
 * Confidence: low (unaff frame register)
 * Notes: traps at 0xf8b98 when the vector is absent */
void FUN_000f8b20(void)
{
    uint64_t vec, n, i;

    vec = *(uint64_t *)(/*unaff_x20*/ 0 + 0x10);
    if (vec != 0) {
        n = *(uint64_t *)(vec + 0x10);
        if (n != 0) {
            FUN_0036b270_1(vec);
            for (i = 0x20; n != 0; n--) {
                FUN_0004e104(*(uint64_t *)(vec + i));
                i += 8;
            }
            FUN_0036b118_1(vec);
            vec = *(uint64_t *)(/*unaff_x20*/ 0 + 0x10);
        }
        FUN_0036b118_1(vec);
        FUN_003a25d4(*(uint64_t *)(/*unaff_x20*/ 0 + 0x18));
        return;
    }
    /* trap: SoftwareBreakpoint(1, 0xf8b98) */
    ((void (*)(void))0)();
}

/* FUN_000f8b98 @ 0x000f8b98   (est. cap_range_table_teardown_entry)
 * Ghidra: void FUN_000f8b98(void)
 * Tears down the cap-range table then enters the completion path.
 * Confidence: medium */
void FUN_000f8b98(void)
{
    FUN_000f8b20();
    FUN_0036b6ac();
}

/* FUN_000f8b9c @ 0x000f8b9c   (est. cap_range_table_teardown_entry_b)
 * Ghidra: void FUN_000f8b9c(void)
 * Duplicate of FUN_000f8b98.
 * Confidence: medium */
void FUN_000f8b9c(void)
{
    FUN_000f8b20();
    FUN_0036b6ac();
}

/* FUN_000f8bd0 @ 0x000f8bd0   (est. cap_range_merge_apply)
 * Ghidra: void FUN_000f8bd0(undefined8 x4, long, long)
 * Applies a capability merge: if the merge operation (FUN_0004e314) succeeds,
 * sets the "done" flag at param_6+0x10 to 1.
 * Confidence: medium */
void FUN_000f8bd0(uint64_t a, uint64_t b, uint64_t c, uint64_t d, uint64_t p5, uint64_t self)
{
    uint64_t r = FUN_0004e314(c, *(uint64_t *)(p5 + 0x20), a, b);
    if (r == 0) {
        FUN_0036a1a0(self + 0x10, 0, 1, 0);
        *(uint8_t *)(self + 0x10) = 1;
    }
}

/* FUN_000f8c38 @ 0x000f8c38   (est. cap_range_ctx_release)
 * Ghidra: void FUN_000f8c38(void)
 * Releases the two context words at (x20+0x20)/(x20+0x28) and enters the
 * completion path.
 * Confidence: medium */
void FUN_000f8c38(void)
{
    FUN_0036b118_1(*(uint64_t *)(/*unaff_x20*/ 0 + 0x20));
    FUN_0036b118_1(*(uint64_t *)(/*unaff_x20*/ 0 + 0x28));
    FUN_0036b21c();
}

/* FUN_000f8c3c @ 0x000f8c3c   (est. cap_range_ctx_release_b)
 * Ghidra: void FUN_000f8c3c(void)
 * Duplicate of FUN_000f8c38.
 * Confidence: medium */
void FUN_000f8c3c(void)
{
    FUN_0036b118_1(*(uint64_t *)(/*unaff_x20*/ 0 + 0x20));
    FUN_0036b118_1(*(uint64_t *)(/*unaff_x20*/ 0 + 0x28));
    FUN_0036b21c();
}

/* FUN_000f8c94 @ 0x000f8c94   (est. cap_range_vector_grow)
 * Ghidra: void FUN_000f8c94(long *)
 * Ensures the capability-range vector has room: if the live count is at the
 * capacity threshold, reallocates to the next power of two via FUN_000f946c,
 * otherwise fills any slack via FUN_000f9194.
 * Confidence: medium */
void FUN_000f8c94(uint64_t *vec)
{
    uint64_t v = *vec;
    uint64_t n, cap;

    if ((FUN_003a261c(v) & 1) == 0)
        v = FUN_0007be74(v);
    n = *(uint64_t *)(v + 0x10);
    cap = FUN_0029369c(n);
    if ((int64_t)cap < (int64_t)n) {
        FUN_000f946c(n >> 1, (uint64_t)(void *)&v, cap);
        if (/*unaff_x21*/ 0 == 0)
            FUN_0036b118();
    } else if (n != 0) {
        FUN_000f9194(0, n, 1, &v);
    }
    *vec = v;
}

/* FUN_000f8d4c @ 0x000f8d4c   (est. cap_range_vec_destroy)
 * Ghidra: void FUN_000f8d4c(void)
 * Destroys the cap-range vector at x20+0x10 and enters the completion path.
 * Confidence: medium */
void FUN_000f8d4c(void)
{
    FUN_0036b8c0(/*unaff_x20*/ 0 + 0x10);
    FUN_0036b21c();
}

/* FUN_000f8d50 @ 0x000f8d50   (est. cap_range_vec_destroy_b)
 * Ghidra: void FUN_000f8d50(void)
 * Duplicate of FUN_000f8d4c.
 * Confidence: medium */
void FUN_000f8d50(void)
{
    FUN_0036b8c0(/*unaff_x20*/ 0 + 0x10);
    FUN_0036b21c();
}

/* FUN_000f8d78 @ 0x000f8d78   (est. cap_range_vec_release)
 * Ghidra: void FUN_000f8d78(void)
 * Releases the word at (x20+0x10) and enters the completion path.
 * Confidence: medium */
void FUN_000f8d78(void)
{
    FUN_0036b118_1(*(uint64_t *)(/*unaff_x20*/ 0 + 0x10));
    FUN_0036b21c();
}

/* FUN_000f8d7c @ 0x000f8d7c   (est. cap_range_vec_release_b)
 * Ghidra: void FUN_000f8d7c(void)
 * Duplicate of FUN_000f8d78.
 * Confidence: medium */
void FUN_000f8d7c(void)
{
    FUN_0036b118_1(*(uint64_t *)(/*unaff_x20*/ 0 + 0x10));
    FUN_0036b21c();
}

/* FUN_000f8dc8 @ 0x000f8dc8   (est. type_tag_652938)
 * Ghidra: undefined1 [16] FUN_000f8dc8(void)
 * Returns the type tag 0x652938 zero-extended as a 16-byte value.
 * Confidence: medium */
cl4_result_t FUN_000f8dc8(void)
{
    cl4_result_t res;
    res.lo = 0x652938;
    res.hi = 0;
    return res;
}

/* FUN_000f8dd8 @ 0x000f8dd8   (est. cap_range_multi_sort)
 * Ghidra: void FUN_000f8dd8(long *, undefined8, long *, long)
 * Sorts capability ranges in param_3 (counts at +1) and records the resulting
 * index/length pairs into the output vector param_1.  Implements an
 * insertion/partition sort with a limit of param_4; runs until the vector has
 * < 2 entries, then re-sorts the remainder via FUN_000f9734.  Uses vector
 * growth FUN_000f9680 and per-segment helpers FUN_000f920c/FUN_000f9194.
 * Confidence: low (complex multi-way sort with many bounds checks)
 * Notes: traps at 0xf9114..0xf918c; output vector tag 0x657778 */
void FUN_000f8dd8(uint64_t *out, uint64_t a2, uint64_t *seg, uint64_t limit)
{
    uint64_t outv = (uint64_t)&DAT_00657778;
    uint64_t i = 0;
    uint64_t n, s, len;

    do {
        n = seg[1];
        if ((int64_t)n <= (int64_t)i) {
            /* terminal: sort via FUN_000f9734 then done */
            break;
        }
        /* partition/sort pass over seg->[i..n), recording runs; emits
         * [i, run_end) pairs into outv (growing via FUN_000f9680) and calls
         * FUN_000f920c to continue the multi-way merge until x21 signals end. */
        i = /* run end */ 0;
    } while (/*unaff_x21*/ 0 == 0);
    FUN_0036b118_1(outv);
}

/* FUN_000f9194 @ 0x000f9194   (est. cap_range_sift)
 * Ghidra: void FUN_000f9194(long, long, long, long *)
 * Sifts/sorts the uint32 run within [param_1, param_2) of the array pointed
 * to by param_4: bubble-style in-place swap of out-of-order adjacent entries
 * (sinking larger values down), stopping at the run boundary.
 * Confidence: low (bounds-check heavy)
 * Notes: traps at 0xf9200..0xf920c */
void FUN_000f9194(int64_t lo, int64_t hi, int64_t cur, uint64_t *arr)
{
    uint32_t a, b;
    int64_t nxt, j;

    if (cur == hi)
        return;
    {
        uint64_t base = *arr;
        uint64_t cnt = arr[1];
        j = cur;
        do {
            nxt = cur - 1;
            if (cur < 0 || cnt <= (uint64_t)j || nxt < 0 || cnt <= (uint64_t)nxt)
                ((void (*)(void))0)();   /* trap */
            a = *(uint32_t *)(base + cur * 4);
            b = *(uint32_t *)(base + nxt * 4);
            if (a < b) {
                *(uint32_t *)(base + cur * 4) = b;
                *(uint32_t *)(base + nxt * 4) = a;
                cur = nxt;
                if (nxt != lo)
                    continue;
            }
            cur = j + 1;
            j = cur;
        } while (cur != hi);
    }
}

/* FUN_000f920c @ 0x000f920c   (est. cap_range_merge_pass)
 * Ghidra: undefined8 FUN_000f920c(long *, undefined8, long *)
 * One pass of the multi-way cap-range merge: while the output vector at
 * param_1 holds more than two run records, picks the merge-adjacent runs,
 * sorts them together via FUN_000f9734, and replaces them with their merged
 * run.  Returns 1.
 * Confidence: low (complex run-record bookkeeping)
 * Notes: traps at 0xf9424..0xf946c */
uint64_t FUN_000f920c(uint64_t *out, uint64_t a2, uint64_t *seg)
{
    uint64_t v = *out;

    if (*(uint64_t *)(v + 0x10) > 1) {
        /* while more than 2 records: pick adjacent runs (uVar11,uVar12),
         * merge them with FUN_000f9734 against the seg array, then compact
         * the record vector via FUN_00117d14. */
        *out = v;
    }
    return 1;
}

/* FUN_000f946c @ 0x000f946c   (est. cap_range_vector_realloc)
 * Ghidra: undefined * FUN_000f946c(long, undefined8, undefined8)
 * Reallocates a cap-range vector to hold param_1 entries: allocates the
 * backing store (via FUN_000f9514), runs the sort FUN_000f8dd8, then resets
 * the live count to 0.  Returns the vector; on the error path releases it.
 * Confidence: medium
 * Notes: traps at 0xf9514 for negative size */
void *FUN_000f946c(int64_t n, uint64_t a2, uint64_t a3)
{
    void *vec;

    if (n < 0)
        ((void (*)(void))0)();   /* trap: SoftwareBreakpoint(1, 0xf9514) */
    if (n == 0) {
        vec = (void *)&DAT_00657778;
    } else {
        vec = (void *)FUN_000f9514(n);
        *(uint64_t *)(vec + 0x10) = n;
    }
    {
        uint64_t tmp = (uint64_t)vec + 0x20;
        FUN_000f8dd8(&tmp, a2, (uint64_t *)a2, a3);
        *(uint64_t *)(vec + 0x10) = 0;
        if (/*unaff_x21*/ 0 != 0)
            FUN_0036b118_1((uint64_t)vec);
    }
    return vec;
}

/* FUN_000f9514 @ 0x000f9514   (est. vector_u32_alloc)
 * Ghidra: undefined * FUN_000f9514(long)
 * Allocates a uint32 vector with room for param_1 elements: reserves a zone
 * object (name 0x64e638, size param_1*4+0x20), computes the capacity from the
 * allocation size, and returns it (empty static vector 0x657778 when n < 1).
 * Confidence: medium */
void *FUN_000f9514(int64_t n)
{
    void *v;

    if (n < 1)
        return (void *)&DAT_00657778;
    {
        uint64_t sz = FUN_0036a940_3(FUN_00002534(0x64e638, (uint64_t)&DAT_004c3ec0), n * 4 + 0x20, 7);
        uint64_t l3 = thunk_FUN_000126e8();
        v = (void *)sz;
        *(uint64_t *)(v + 0x10) = 0;
        *(uint64_t *)(v + 0x18) = ((l3 - 0x20) / 4) << 1;
    }
    return v;
}

/* FUN_000f958c @ 0x000f958c   (est. vector_pair_alloc)
 * Ghidra: undefined * FUN_000f958c(long)
 * Allocates a 16-byte-pair vector with room for param_1 elements (zone name
 * 0x64e660); capacity from allocation size; empty static vector 0x657778 when
 * n < 1.
 * Confidence: medium */
void *FUN_000f958c(int64_t n)
{
    void *v;

    if (n < 1)
        return (void *)&DAT_00657778;
    {
        uint64_t sz = FUN_0036a940_3(FUN_00002534(0x64e660, (uint64_t)&DAT_004c04b8), n * 0x10 + 0x20, 7);
        uint64_t l3 = thunk_FUN_000126e8();
        v = (void *)sz;
        *(uint64_t *)(v + 0x10) = 0;
        *(uint64_t *)(v + 0x18) = ((l3 - 0x20) / 0x10) << 1;
    }
    return v;
}

/* FUN_000f9604 @ 0x000f9604   (est. vector_word_alloc_thunk)
 * Ghidra: undefined * thunk_FUN_000f9608(long)
 * Thunk to FUN_000f9608 (uint64 vector allocator).
 * Confidence: medium */
void *thunk_FUN_000f9608(int64_t n)
{
    return FUN_000f9608(n);
}

/* FUN_000f9608 @ 0x000f9608   (est. vector_word_alloc)
 * Ghidra: undefined * FUN_000f9608(long)
 * Allocates a uint64 vector with room for param_1 elements (zone name
 * 0x64e838); capacity from allocation size; empty static vector 0x657778 when
 * n < 1.
 * Confidence: medium */
void *FUN_000f9608(int64_t n)
{
    void *v;

    if (n < 1)
        return (void *)&DAT_00657778;
    {
        uint64_t sz = FUN_0036a940_3(FUN_00002534((uint64_t)&DAT_0064e838, (uint64_t)&DAT_004c0690), n * 8 + 0x20, 7);
        uint64_t l3 = thunk_FUN_000126e8();
        v = (void *)sz;
        *(uint64_t *)(v + 0x10) = 0;
        *(uint64_t *)(v + 0x18) = ((l3 - 0x20) / 8) << 1;
    }
    return v;
}

/* FUN_000f9680 @ 0x000f9680   (est. vector_grow)
 * Ghidra: long FUN_000f9680(ulong,ulong,ulong,long)
 * Grows a vector to hold at least param_2 elements: optionally rounds up to
 * the next power-of-two capacity (param_3 bit 0), allocates the backing store
 * via FUN_000f9944, and either copies the old contents (param_1 bit 0 clear)
 * or moves the caller-owned buffer and releases the old vector (param_1 bit 0
 * set).  Returns the new backing store.
 * Confidence: medium
 * Notes: traps at 0xf9734 on overflow */
uint64_t FUN_000f9680(uint64_t copy, uint64_t need, uint64_t flags, uint64_t vec)
{
    uint64_t n = need;

    if ((flags & 1) != 0) {
        n = *(uint64_t *)(vec + 0x18) >> 1;
        if ((int64_t)n < (int64_t)need) {
            if ((int64_t)(n + 0x4000000000000000) < 0)
                ((void (*)(void))0)();   /* trap: SoftwareBreakpoint(1, 0xf9734) */
            n = *(uint64_t *)(vec + 0x18) & ~1ull;
            if ((int64_t)n <= (int64_t)need)
                n = need;
        }
    }
    {
        uint64_t count = *(uint64_t *)(vec + 0x10);
        uint64_t new = (uint64_t)FUN_000f9944(count, n);
        if ((copy & 1) == 0) {
            FUN_00075624(0, count, new + 0x20, vec);
        } else {
            FUN_00069970(vec + 0x20, count, new + 0x20);
            *(uint64_t *)(vec + 0x10) = 0;
            FUN_0036b118_1(vec);
        }
        return new;
    }
}

/* FUN_000f9734 @ 0x000f9734   (est. cap_range_two_way_merge)
 * Ghidra: undefined8 FUN_000f9734(uint *,...)
 * Merges two sorted uint32 runs [param_1,param_2) and [param_2,param_3) into
 * the output run starting at param_4 (in-place merge via FUN_0007201c and
 * FUN_00117d14), choosing the merge order by the smaller run.
 * Confidence: low (classic merge; bounds check at 0xf98ac)
 * Notes: traps at 0xf98ac */
uint64_t FUN_000f9734(uint32_t *lo, uint32_t *mid, uint32_t *hi, uint32_t *out)
{
    int64_t l2 = (mid - lo);
    int64_t l3 = (hi - mid);

    if (l2 < l3) {
        FUN_0007201c((uint64_t)lo, l2, (uint64_t)out);
        /* merge the two runs into out; then tail-copy via FUN_00117d14 */
        return 1;
    }
    FUN_0007201c((uint64_t)mid, l3, (uint64_t)out);
    /* backward merge */
    return 1;
}

/* FUN_000f98ac @ 0x000f98ac   (est. vector_pair_pop)
 * Ghidra: undefined1 [16] FUN_000f98ac(ulong)
 * Removes the pair element at index param_1 from the vector at x20, shifting
 * the tail down and decrementing the count; returns the popped pair.
 * Confidence: low (unaff frame register)
 * Notes: traps at 0xf9930 for out-of-range index */
cl4_result_t FUN_000f98ac(uint64_t idx)
{
    uint64_t v = /*unaff_x20*/ 0;
    uint64_t n, tail;
    cl4_result_t pair;

    if ((FUN_003a261c(v) & 1) == 0)
        FUN_000f9930(v);
    if (idx < *(uint64_t *)(v + 0x10)) {
        tail = *(uint64_t *)(v + 0x10) - 1;
        pair.lo = *(uint64_t *)(v + idx * 0x10 + 0x20);
        pair.hi = *(uint64_t *)(v + idx * 0x10 + 0x28);
        FUN_00069970(v + idx * 0x10 + 0x30, tail - idx, (uint64_t)&pair);
        *(uint64_t *)(v + 0x10) = tail;
        /* unaff_x20 = v; (frame register write not representable) */
        return pair;
    }
    /* trap: SoftwareBreakpoint(1, 0xf9930) */
    ((void (*)(void))0)();
    pair.lo = pair.hi = 0;
    return pair;
}

/* FUN_000f9930 @ 0x000f9930   (est. vector_compact)
 * Ghidra: void FUN_000f9930(long)
 * Compacts the vector: reallocates via FUN_000f9680 (copy semantics).
 * Confidence: medium */
void FUN_000f9930(uint64_t vec)
{
    FUN_000f9680(0, *(uint64_t *)(vec + 0x10), 0, vec);
}

/* FUN_000f9944 @ 0x000f9944   (est. vector_pair_alloc_raw)
 * Ghidra: undefined * FUN_000f9944(long, long)
 * Allocates a 16-byte-pair vector backing store sized to hold param_2
 * elements (at least param_1), returning the empty static vector 0x657778
 * when param_2 is 0.
 * Confidence: medium */
void *FUN_000f9944(int64_t min, int64_t n)
{
    void *v;

    if (n <= min)
        n = min;
    if (n == 0)
        return (void *)&DAT_00657778;
    {
        uint64_t sz = FUN_0036a940_3(FUN_00002534(0x652990, (uint64_t)&DAT_004c3ec8), n * 0x10 + 0x20, 7);
        uint64_t l3 = thunk_FUN_000126e8();
        v = (void *)sz;
        *(uint64_t *)(v + 0x10) = min;
        *(uint64_t *)(v + 0x18) = ((l3 - 0x20) / 0x10) << 1;
    }
    return v;
}

/* FUN_000f99d0 @ 0x000f99d0   (est. vector_word_alloc_thunk_b)
 * Ghidra: undefined * thunk_FUN_000f9608(long)
 * Thunk to FUN_000f9608.
 * Confidence: medium */
void *thunk_FUN_000f9608_b(int64_t n)
{
    return FUN_000f9608(n);
}

/* FUN_000f99d4 @ 0x000f99d4   (est. vector_noop)
 * Ghidra: void FUN_000f99d4(void)
 * No-op marker.
 * Confidence: medium */
void FUN_000f99d4(void)
{
}

/* FUN_000f99f8 @ 0x000f99f8   (est. marshal_noop)
 * Ghidra: void FUN_000f99f8(void)
 * No-op marshalling marker.
 * Confidence: medium */
void FUN_000f99f8(void)
{
}

/* FUN_000f9a0c @ 0x000f9a0c   (est. publish_error_result)
 * Ghidra: void FUN_000f9a0c(undefined8, long)
 * Publishes an error result: sets the state flag at param_2+0x10 to 3 and
 * raises the error-completion callback.
 * Confidence: medium */
void FUN_000f9a0c(uint64_t err, uint64_t slot)
{
    *(uint8_t *)(slot + 0x10) = 3;
    FUN_0036986c();
}

/* FUN_000f9a1c @ 0x000f9a1c   (est. resource_op_finalize)
 * Ghidra: undefined8 FUN_000f9a1c(void)
 * Reserves an object and runs the finalize helper FUN_000f9b4c.
 * Confidence: medium */
uint64_t FUN_000f9a1c(void)
{
    uint64_t obj = FUN_0036a940();
    FUN_000f9b4c();
    return obj;
}

/* FUN_000f9a5c @ 0x000f9a5c   (est. resource_bad_error)
 * Ghidra: undefined1 [16] FUN_000f9a5c(void)
 * Reports a generic resource error (0x25) through the trap context and
 * returns {hi = vtable 0x5c60b0, lo = error 0x25}.
 * Confidence: medium */
cl4_result_t FUN_000f9a5c(void)
{
    uint64_t slot = 0x671df8;
    uint64_t (*logfn)(uint64_t, uint64_t);
    cl4_result_t res;

    FUN_002a4ab4(0x1d);
    FUN_003a25d4(0xe000000000000000);
    logfn = (void *)FUN_00027724(0x671df8);
    logfn(0x677830, slot);
    thunk_FUN_002acbb8();
    FUN_003a25d4(0);
    thunk_FUN_002acbb8_2(0x29, 0xe100000000000000);
    res.hi = 0x80000000005c60b0;
    res.lo = 0xd000000000000025;
    return res;
}

/* FUN_000f9b28 @ 0x000f9b28   (est. resource_bad_error_entry)
 * Ghidra: void FUN_000f9b28(void)
 * Alias of FUN_000f9a5c.
 * Confidence: medium */
void FUN_000f9b28(void)
{
    FUN_000f9a5c();
}
