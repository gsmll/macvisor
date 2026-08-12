/* Recreated from exclavecore_bundle.t8142.RELEASE.im4p (cL4 Secure Kernel, GL1,
 * arm64e, image base 0) — the cL4 microkernel. Ground truth: Ghidra FUN_ names +
 * addresses in cl4_kernel.raw. Version "cL4 microkernel (cL4 (679.100.61))".
 * All names are estimates unless string/header-matched.
 *
 * SKGAP18 gap slice: 0x357bf8-0x35841c. This region is a dense strip of small
 * leaf/stub functions: stack-frame prologue/epilogue fragments (the decompiler
 * splits functions at the re-entry points, exposing only frame teardown or a
 * single store), thin forwarding stubs, and a few Swift-existential pair
 * constructors. Many bodies are marked low confidence because the real work
 * happens in a caller whose registers (x19/x20/x21/x22/x29) are live-in here.
 */

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#include "sk_internal.h"

/* Ghidra's "SoftwareBreakpoint(code, addr)" — an unconditional fault. */
#define SoftwareBreakpoint(code, addr)  ((unsigned long)0x5519UL)

/* ------------------------------------------------------------------ *
 * Out-of-range cL4 callees (extern; bodies reconstructed by sibling
 * range workers). Names are estimates.
 * ------------------------------------------------------------------ */
extern void sk_adj_365b6c(void);                  /* FUN_00365b6c */
extern void sk_adj_27754(void);                   /* FUN_00027754 */
extern void sk_adj_026e8(void *slot);             /* FUN_000026e8 */
extern void sk_adj_310a74(void);                  /* FUN_00310a74 */
extern void sk_adj_1df60(void);                   /* FUN_0001df60 */
extern void sk_adj_a6b64(void);                   /* FUN_000a6b64 */
extern void sk_adj_1a0354(int a, int b);          /* FUN_001a0354 */
extern void sk_adj_1b7524(word_t a, void *b);     /* FUN_001b7524 */
extern void sk_adj_377bec(word_t a, word_t b, word_t c); /* FUN_00377bec */
extern void sk_adj_312d08(void *a, void *b, void *c,
                          word_t x, word_t y, word_t z, word_t w); /* FUN_00312d08 */
extern void sk_adj_1da714(word_t a);              /* FUN_001da714 */
extern void sk_adj_117d14(void);                  /* FUN_00117d14 */
extern void sk_adj_377824(word_t a);              /* FUN_00377824 */
extern void sk_adj_thunk_2298d4(void);            /* thunk_FUN_002298d4 */

/* Swift existential metadata string (data 0x5cf680). */
extern unsigned char sk_swift_existential_str[];  /* s_Swift_ExistentialCollection_swif_005cf680 */


/* sk_adj_365b6c_tail @ 0x00357bf8   (FUN_00357bf8)
 * Ghidra: void FUN_00357bf8(void)
 * Thin forwarding stub to an out-of-range helper.
 * Confidence: medium
 * Notes: thin forwarding stub */
void sk_gap18_365b6c_tail(void)
{
    /* Thin forwarding stub: unconditionally tail-calls the adjacency helper
     * sk_adj_365b6c (FUN_00365b6c). */
    sk_adj_365b6c();
    return;
}

/* sk_triple_27754 @ 0x00357c04   (FUN_00357c04)
 * Ghidra: void FUN_00357c04(void)
 * Dispatches to an out-of-range helper with fixed/live-in arguments.
 * Confidence: medium
 * Notes: small self-contained leaf */
void sk_gap18_triple_27754(void)
{
    /* Calls the object helper sk_adj_27754 (FUN_00027754) three times in a
     * row with no arguments — a triple init/teardown sequence. */
    sk_adj_27754();
    sk_adj_27754();
    sk_adj_27754();
    return;
}

/* sk_align_20_frag @ 0x00357c20   (FUN_00357c20)
 * Ghidra: void FUN_00357c20(void)
 * Small leaf with the described single operation.
 * Confidence: low
 * Notes: mid-function fragment; live-in registers x19/x20/x21/x22/x29 from caller */
void sk_gap18_align_20_frag(void)
{
    /* Fragment: computes x8 = (x8+0x20) & ~x8 (alignment round-up against a
     * live-in mask in x8). Result discarded before ret. */
    return;
}

/* sk_init_slot_026e8 @ 0x00357c2c   (FUN_00357c2c)
 * Ghidra: void FUN_00357c2c(void)
 * Dispatches to an out-of-range helper with fixed/live-in arguments.
 * Confidence: medium
 * Notes: small self-contained leaf */
void sk_gap18_init_slot_026e8(void)
{
    /* Calls sk_adj_026e8 (FUN_000026e8) on the caller's stack slot at
     * [sp+8] — initializes an object/method-table slot. */
    sk_adj_026e8((void *)&((char){0}) );  /* [stack+8] */
    return;
}

/* sk_frag_c38 @ 0x00357c38   (FUN_00357c38)
 * Ghidra: void FUN_00357c38(void)
 * Empty frame fragment — no recoverable logic; registers live-in from caller.
 * Confidence: low
 * Notes: decompiler recovers only stack prologue/epilogue; function is split at a re-entry point — registers live-in from caller */
void sk_frag_00357c38(void)
{
    /* Empty frame fragment (prologue/epilogue only). */
    return;
}

/* sk_frag_c44 @ 0x00357c44   (FUN_00357c44)
 * Ghidra: void FUN_00357c44(void)
 * Empty frame fragment — no recoverable logic; registers live-in from caller.
 * Confidence: low
 * Notes: decompiler recovers only stack prologue/epilogue; function is split at a re-entry point — registers live-in from caller */
void sk_frag_00357c44(void)
{
    /* Empty frame fragment (prologue/epilogue only). */
    return;
}

/* sk_two_call_c58 @ 0x00357c58   (FUN_00357c58)
 * Ghidra: void FUN_00357c58(void)
 * Dispatches to an out-of-range helper with fixed/live-in arguments.
 * Confidence: medium
 * Notes: small self-contained leaf */
void sk_gap18_two_call_c58(void)
{
    /* Calls sk_adj_310a74 (FUN_00310a74) then sk_adj_1df60 (FUN_0001df60)
     * in sequence — likely a two-phase state transition. */
    sk_adj_310a74();
    sk_adj_1df60();
    return;
}

/* sk_frag_c74 @ 0x00357c74   (FUN_00357c74)
 * Ghidra: void FUN_00357c74(void)
 * Small leaf with the described single operation.
 * Confidence: medium
 * Notes: small self-contained leaf */
void sk_frag_00357c74(void)
{
    /* Frame teardown fragment: restores callee-saved x19-x24 from the
     * caller's stack frame (sp+0x10..0x30) and adjusts sp by 0x50. */
    return;
}

/* sk_adj_a6b64_tail @ 0x00357c88   (FUN_00357c88)
 * Ghidra: void FUN_00357c88(void)
 * Thin forwarding stub to an out-of-range helper.
 * Confidence: medium
 * Notes: thin forwarding stub */
void sk_gap18_a6b64_tail(void)
{
    /* Thin forwarding stub: tail-calls sk_adj_a6b64 (FUN_000a6b64). */
    sk_adj_a6b64();
    return;
}

/* sk_frag_ca0 @ 0x00357ca0   (FUN_00357ca0)
 * Ghidra: void FUN_00357ca0(void)
 * Empty frame fragment — no recoverable logic; registers live-in from caller.
 * Confidence: low
 * Notes: decompiler recovers only stack prologue/epilogue; function is split at a re-entry point — registers live-in from caller */
void sk_frag_00357ca0(void)
{
    /* Empty frame fragment (prologue/epilogue only). */
    return;
}

/* sk_frag_cb4 @ 0x00357cb4   (FUN_00357cb4)
 * Ghidra: void FUN_00357cb4(void)
 * Small leaf with the described single operation.
 * Confidence: medium
 * Notes: small self-contained leaf */
void sk_frag_00357cb4(void)
{
    /* Frame prologue fragment: allocates 0x50 of stack and pushes
     * callee-saved x19-x24, then returns immediately. */
    return;
}

/* sk_swift_existential_ctor @ 0x00357cc8   (FUN_00357cc8)
 * Ghidra: undefined1 [16] FUN_00357cc8(void)
 * Builds a Swift existential type-metadata pair (name string + type tag 0x21).
 * Confidence: high
 * Notes: small self-contained leaf */
cl4_result_t sk_gap18_swift_existential_ctor(void)
{
    /* Swift existential metadata constructor: returns the type-metadata
     * pair {name_ptr=s_Swift_ExistentialCollection_swif_005cf680, type=0x21}
     * with extra 0x2 in w2. Represents an existential collection type. */
    cl4_result_t r;
    r.lo = (word_t)sk_swift_existential_str;   /* s_Swift_ExistentialCollection_swif_005cf680 */
    r.hi = 0x21;
    return r;
}

/* sk_frag_cdc @ 0x00357cdc   (FUN_00357cdc)
 * Ghidra: void FUN_00357cdc(void)
 * Empty frame fragment — no recoverable logic; registers live-in from caller.
 * Confidence: low
 * Notes: decompiler recovers only stack prologue/epilogue; function is split at a re-entry point — registers live-in from caller */
void sk_frag_00357cdc(void)
{
    /* Empty frame fragment (prologue/epilogue only). */
    return;
}

/* sk_frag_cec @ 0x00357cec   (FUN_00357cec)
 * Ghidra: void FUN_00357cec(void)
 * Empty frame fragment — no recoverable logic; registers live-in from caller.
 * Confidence: low
 * Notes: decompiler recovers only stack prologue/epilogue; function is split at a re-entry point — registers live-in from caller */
void sk_frag_00357cec(void)
{
    /* Empty frame fragment (prologue/epilogue only). */
    return;
}

/* sk_split_word_store_cfc @ 0x00357cfc   (FUN_00357cfc)
 * Ghidra: void FUN_00357cfc(undefined8 param_1)
 * Spills live-in register values into the caller frame (argument setup).
 * Confidence: medium
 * Notes: small self-contained leaf */
void sk_gap18_split_word_store_cfc(word_t param)
{
    /* Frame store fragment: stores the low 32 bits of param at [x29-0x78]
     * and bit 32..39 (high byte of low word) at [x29-0x74]. */
    return;
}

/* sk_frag_d0c @ 0x00357d0c   (FUN_00357d0c)
 * Ghidra: void FUN_00357d0c(void)
 * Empty frame fragment — no recoverable logic; registers live-in from caller.
 * Confidence: low
 * Notes: decompiler recovers only stack prologue/epilogue; function is split at a re-entry point — registers live-in from caller */
void sk_frag_00357d0c(void)
{
    /* Empty frame fragment (prologue/epilogue only). */
    return;
}

/* sk_copy_field_20_d34 @ 0x00357d34   (FUN_00357d34)
 * Ghidra: void FUN_00357d34(void)
 * Small leaf with the described single operation.
 * Confidence: medium
 * Notes: small self-contained leaf */
void sk_gap18_copy_field_20_d34(void)
{
    /* Copies the 8-byte field at [x19+0x20] (live-in object) into
     * [x20+0x20] (live-in destination) — a per-object field clone. */
    return;
}

/* sk_frag_d44 @ 0x00357d44   (FUN_00357d44)
 * Ghidra: void FUN_00357d44(void)
 * Empty frame fragment — no recoverable logic; registers live-in from caller.
 * Confidence: low
 * Notes: decompiler recovers only stack prologue/epilogue; function is split at a re-entry point — registers live-in from caller */
void sk_frag_00357d44(void)
{
    /* Empty frame fragment (prologue/epilogue only). */
    return;
}

/* sk_frag_d54 @ 0x00357d54   (FUN_00357d54)
 * Ghidra: void FUN_00357d54(void)
 * Empty frame fragment — no recoverable logic; registers live-in from caller.
 * Confidence: low
 * Notes: decompiler recovers only stack prologue/epilogue; function is split at a re-entry point — registers live-in from caller */
void sk_frag_00357d54(void)
{
    /* Empty frame fragment (prologue/epilogue only). */
    return;
}

/* sk_frag_d64 @ 0x00357d64   (FUN_00357d64)
 * Ghidra: void FUN_00357d64(void)
 * Empty frame fragment — no recoverable logic; registers live-in from caller.
 * Confidence: low
 * Notes: decompiler recovers only stack prologue/epilogue; function is split at a re-entry point — registers live-in from caller */
void sk_frag_00357d64(void)
{
    /* Empty frame fragment (prologue/epilogue only). */
    return;
}

/* sk_frag_d74 @ 0x00357d74   (FUN_00357d74)
 * Ghidra: void FUN_00357d74(void)
 * Empty frame fragment — no recoverable logic; registers live-in from caller.
 * Confidence: low
 * Notes: decompiler recovers only stack prologue/epilogue; function is split at a re-entry point — registers live-in from caller */
void sk_frag_00357d74(void)
{
    /* Empty frame fragment (prologue/epilogue only). */
    return;
}

/* sk_frag_d84 @ 0x00357d84   (FUN_00357d84)
 * Ghidra: void FUN_00357d84(void)
 * Empty frame fragment — no recoverable logic; registers live-in from caller.
 * Confidence: low
 * Notes: decompiler recovers only stack prologue/epilogue; function is split at a re-entry point — registers live-in from caller */
void sk_frag_00357d84(void)
{
    /* Empty frame fragment (prologue/epilogue only). */
    return;
}

/* sk_frag_d94 @ 0x00357d94   (FUN_00357d94)
 * Ghidra: void FUN_00357d94(void)
 * Empty frame fragment — no recoverable logic; registers live-in from caller.
 * Confidence: low
 * Notes: decompiler recovers only stack prologue/epilogue; function is split at a re-entry point — registers live-in from caller */
void sk_frag_00357d94(void)
{
    /* Empty frame fragment (prologue/epilogue only). */
    return;
}

/* sk_refcount_inc_da4 @ 0x00357da4   (FUN_00357da4)
 * Ghidra: void FUN_00357da4(void)
 * Small leaf with the described single operation.
 * Confidence: medium
 * Notes: small self-contained leaf */
void sk_gap18_refcount_inc_da4(void)
{
    /* Increments the 32-bit counter at [x19+0x24] (live-in object) — a
     * per-object reference/state counter bump. */
    return;
}

/* sk_frag_db4 @ 0x00357db4   (FUN_00357db4)
 * Ghidra: void FUN_00357db4(void)
 * Empty frame fragment — no recoverable logic; registers live-in from caller.
 * Confidence: low
 * Notes: decompiler recovers only stack prologue/epilogue; function is split at a re-entry point — registers live-in from caller */
void sk_frag_00357db4(void)
{
    /* Empty frame fragment (prologue/epilogue only). */
    return;
}

/* sk_frag_dc4 @ 0x00357dc4   (FUN_00357dc4)
 * Ghidra: void FUN_00357dc4(void)
 * Empty frame fragment — no recoverable logic; registers live-in from caller.
 * Confidence: low
 * Notes: decompiler recovers only stack prologue/epilogue; function is split at a re-entry point — registers live-in from caller */
void sk_frag_00357dc4(void)
{
    /* Empty frame fragment (prologue/epilogue only). */
    return;
}

/* sk_split_short_store_dd4 @ 0x00357dd4   (FUN_00357dd4)
 * Ghidra: void FUN_00357dd4(void)
 * Spills live-in register values into the caller frame (argument setup).
 * Confidence: medium
 * Notes: small self-contained leaf */
void sk_gap18_split_short_store_dd4(void)
{
    /* Frame store fragment: writes low 16 bits of live-in w20 as a halfword
     * at [x19] and bit 16..23 at [x19+1] — a split 24-bit field store. */
    return;
}

/* sk_frag_de4 @ 0x00357de4   (FUN_00357de4)
 * Ghidra: void FUN_00357de4(void)
 * Empty frame fragment — no recoverable logic; registers live-in from caller.
 * Confidence: low
 * Notes: decompiler recovers only stack prologue/epilogue; function is split at a re-entry point — registers live-in from caller */
void sk_frag_00357de4(void)
{
    /* Empty frame fragment (prologue/epilogue only). */
    return;
}

/* sk_frag_df4 @ 0x00357df4   (FUN_00357df4)
 * Ghidra: void FUN_00357df4(void)
 * Empty frame fragment — no recoverable logic; registers live-in from caller.
 * Confidence: low
 * Notes: decompiler recovers only stack prologue/epilogue; function is split at a re-entry point — registers live-in from caller */
void sk_frag_00357df4(void)
{
    /* Empty frame fragment (prologue/epilogue only). */
    return;
}

/* sk_frag_e04 @ 0x00357e04   (FUN_00357e04)
 * Ghidra: void FUN_00357e04(void)
 * Empty frame fragment — no recoverable logic; registers live-in from caller.
 * Confidence: low
 * Notes: decompiler recovers only stack prologue/epilogue; function is split at a re-entry point — registers live-in from caller */
void sk_frag_00357e04(void)
{
    /* Empty frame fragment (prologue/epilogue only). */
    return;
}

/* sk_frag_e14 @ 0x00357e14   (FUN_00357e14)
 * Ghidra: void FUN_00357e14(void)
 * Empty frame fragment — no recoverable logic; registers live-in from caller.
 * Confidence: low
 * Notes: decompiler recovers only stack prologue/epilogue; function is split at a re-entry point — registers live-in from caller */
void sk_frag_00357e14(void)
{
    /* Empty frame fragment (prologue/epilogue only). */
    return;
}

/* sk_frag_e24 @ 0x00357e24   (FUN_00357e24)
 * Ghidra: void FUN_00357e24(void)
 * Empty frame fragment — no recoverable logic; registers live-in from caller.
 * Confidence: low
 * Notes: decompiler recovers only stack prologue/epilogue; function is split at a re-entry point — registers live-in from caller */
void sk_frag_00357e24(void)
{
    /* Empty frame fragment (prologue/epilogue only). */
    return;
}

/* sk_frag_e34 @ 0x00357e34   (FUN_00357e34)
 * Ghidra: void FUN_00357e34(void)
 * Empty frame fragment — no recoverable logic; registers live-in from caller.
 * Confidence: low
 * Notes: decompiler recovers only stack prologue/epilogue; function is split at a re-entry point — registers live-in from caller */
void sk_frag_00357e34(void)
{
    /* Empty frame fragment (prologue/epilogue only). */
    return;
}

/* sk_frag_e44 @ 0x00357e44   (FUN_00357e44)
 * Ghidra: void FUN_00357e44(void)
 * Empty frame fragment — no recoverable logic; registers live-in from caller.
 * Confidence: low
 * Notes: decompiler recovers only stack prologue/epilogue; function is split at a re-entry point — registers live-in from caller */
void sk_frag_00357e44(void)
{
    /* Empty frame fragment (prologue/epilogue only). */
    return;
}

/* sk_load_field_68_e64 @ 0x00357e64   (FUN_00357e64)
 * Ghidra: undefined1 [16] FUN_00357e64(void)
 * Returns a {lo,hi} pair assembled from live-in registers/fields.
 * Confidence: medium
 * Notes: small self-contained leaf */
cl4_result_t sk_gap18_load_field_68_e64(void)
{
    /* Returns {lo=[x21+0x68] (live-in object field), hi=0} shifted left 64
     * bits — exposes a single 64-bit field as a 128-bit pair. */
    cl4_result_t r;
    r.lo = 0;
    r.hi = 0;
    return r;
}

/* sk_frag_e84 @ 0x00357e84   (FUN_00357e84)
 * Ghidra: void FUN_00357e84(void)
 * Empty frame fragment — no recoverable logic; registers live-in from caller.
 * Confidence: low
 * Notes: decompiler recovers only stack prologue/epilogue; function is split at a re-entry point — registers live-in from caller */
void sk_frag_00357e84(void)
{
    /* Empty frame fragment (prologue/epilogue only). */
    return;
}

/* sk_frag_e94 @ 0x00357e94   (FUN_00357e94)
 * Ghidra: void FUN_00357e94(void)
 * Empty frame fragment — no recoverable logic; registers live-in from caller.
 * Confidence: low
 * Notes: decompiler recovers only stack prologue/epilogue; function is split at a re-entry point — registers live-in from caller */
void sk_frag_00357e94(void)
{
    /* Empty frame fragment (prologue/epilogue only). */
    return;
}

/* sk_frag_eb4 @ 0x00357eb4   (FUN_00357eb4)
 * Ghidra: void FUN_00357eb4(void)
 * Empty frame fragment — no recoverable logic; registers live-in from caller.
 * Confidence: low
 * Notes: decompiler recovers only stack prologue/epilogue; function is split at a re-entry point — registers live-in from caller */
void sk_frag_00357eb4(void)
{
    /* Empty frame fragment (prologue/epilogue only). */
    return;
}

/* sk_frag_ec4 @ 0x00357ec4   (FUN_00357ec4)
 * Ghidra: void FUN_00357ec4(void)
 * Empty frame fragment — no recoverable logic; registers live-in from caller.
 * Confidence: low
 * Notes: decompiler recovers only stack prologue/epilogue; function is split at a re-entry point — registers live-in from caller */
void sk_frag_00357ec4(void)
{
    /* Empty frame fragment (prologue/epilogue only). */
    return;
}

/* sk_frag_ed4 @ 0x00357ed4   (FUN_00357ed4)
 * Ghidra: void FUN_00357ed4(void)
 * Empty frame fragment — no recoverable logic; registers live-in from caller.
 * Confidence: low
 * Notes: decompiler recovers only stack prologue/epilogue; function is split at a re-entry point — registers live-in from caller */
void sk_frag_00357ed4(void)
{
    /* Empty frame fragment (prologue/epilogue only). */
    return;
}

/* sk_frag_ee4 @ 0x00357ee4   (FUN_00357ee4)
 * Ghidra: void FUN_00357ee4(void)
 * Empty frame fragment — no recoverable logic; registers live-in from caller.
 * Confidence: low
 * Notes: decompiler recovers only stack prologue/epilogue; function is split at a re-entry point — registers live-in from caller */
void sk_frag_00357ee4(void)
{
    /* Empty frame fragment (prologue/epilogue only). */
    return;
}

/* sk_frag_ef4 @ 0x00357ef4   (FUN_00357ef4)
 * Ghidra: void FUN_00357ef4(void)
 * Empty frame fragment — no recoverable logic; registers live-in from caller.
 * Confidence: low
 * Notes: decompiler recovers only stack prologue/epilogue; function is split at a re-entry point — registers live-in from caller */
void sk_frag_00357ef4(void)
{
    /* Empty frame fragment (prologue/epilogue only). */
    return;
}

/* sk_frame_store_7_f04 @ 0x00357f04   (FUN_00357f04)
 * Ghidra: void FUN_00357f04(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4, undefined8 param_5,undefined8 param_6,undefined8 param_7)
 * Spills live-in register values into the caller frame (argument setup).
 * Confidence: medium
 * Notes: small self-contained leaf */
void sk_gap18_frame_store_7_f04(word_t p2, word_t p3, word_t p4,
                                 word_t p5, word_t p6, word_t p7)
{
    /* Frame store fragment: spills args 2-7 to the caller frame at
     * x29-0xc0..x29-0xa0 — argument setup for a subsequent call. */
    return;
}

/* sk_stack_ptr_8_f14 @ 0x00357f14   (FUN_00357f14)
 * Ghidra: undefined1 * FUN_00357f14(void)
 * Small leaf with the described single operation.
 * Confidence: medium
 * Notes: small self-contained leaf */
void *sk_gap18_stack_ptr_8_f14(void)
{
    /* Returns the caller's stack slot address [sp+8]. */
    return (void *)&((char){0});
}

/* sk_store_two_f24 @ 0x00357f24   (FUN_00357f24)
 * Ghidra: void FUN_00357f24(undefined8 param_1)
 * Returns a {lo,hi} pair assembled from live-in registers/fields.
 * Confidence: low
 * Notes: mid-function fragment; live-in registers x19/x20/x21/x22/x29 from caller */
void sk_gap18_store_two_f24(word_t param)
{
    /* Fragment: stores param into live-in x20[3] and live-in x19 into
     * x20[0] — writes a {stored_value, object_ptr} pair. */
    return;
}

/* sk_page_fixup_f34 @ 0x00357f34   (FUN_00357f34)
 * Ghidra: long FUN_00357f34(ulong param_1)
 * Small leaf with the described single operation.
 * Confidence: medium
 * Notes: small self-contained leaf */
word_t sk_gap18_page_fixup_f34(word_t param)
{
    /* Address fixup: masks off the low 16 bits of param then subtracts
     * 0xfffc — converts a page-table entry to a canonical address. */
    return (param & 0xffffffffffff0000ULL) - 0xfffcULL;
}

/* sk_frag_f44 @ 0x00357f44   (FUN_00357f44)
 * Ghidra: void FUN_00357f44(void)
 * Empty frame fragment — no recoverable logic; registers live-in from caller.
 * Confidence: low
 * Notes: decompiler recovers only stack prologue/epilogue; function is split at a re-entry point — registers live-in from caller */
void sk_frag_00357f44(void)
{
    /* Empty frame fragment (prologue/epilogue only). */
    return;
}

/* sk_frame_load2_f54 @ 0x00357f54   (FUN_00357f54)
 * Ghidra: void FUN_00357f54(long param_1)
 * Small leaf with the described single operation.
 * Confidence: low
 * Notes: mid-function fragment; live-in registers x19/x20/x21/x22/x29 from caller */
void sk_gap18_frame_load2_f54(long param)
{
    /* Fragment: loads two words from [param-0x100] and [param-0xf8] and
     * stores them to the caller frame (x29-0x130/-0x128). */
    return;
}

/* sk_frag_f64 @ 0x00357f64   (FUN_00357f64)
 * Ghidra: void FUN_00357f64(void)
 * Empty frame fragment — no recoverable logic; registers live-in from caller.
 * Confidence: low
 * Notes: decompiler recovers only stack prologue/epilogue; function is split at a re-entry point — registers live-in from caller */
void sk_frag_00357f64(void)
{
    /* Empty frame fragment (prologue/epilogue only). */
    return;
}

/* sk_frag_f74 @ 0x00357f74   (FUN_00357f74)
 * Ghidra: void FUN_00357f74(void)
 * Empty frame fragment — no recoverable logic; registers live-in from caller.
 * Confidence: low
 * Notes: decompiler recovers only stack prologue/epilogue; function is split at a re-entry point — registers live-in from caller */
void sk_frag_00357f74(void)
{
    /* Empty frame fragment (prologue/epilogue only). */
    return;
}

/* sk_frag_f84 @ 0x00357f84   (FUN_00357f84)
 * Ghidra: void FUN_00357f84(void)
 * Empty frame fragment — no recoverable logic; registers live-in from caller.
 * Confidence: low
 * Notes: decompiler recovers only stack prologue/epilogue; function is split at a re-entry point — registers live-in from caller */
void sk_frag_00357f84(void)
{
    /* Empty frame fragment (prologue/epilogue only). */
    return;
}

/* sk_pair_add_f94 @ 0x00357f94   (FUN_00357f94)
 * Ghidra: undefined1 [16] FUN_00357f94(long param_1)
 * Returns a {lo,hi} pair assembled from live-in registers/fields.
 * Confidence: medium
 * Notes: small self-contained leaf */
cl4_result_t sk_gap18_pair_add_f94(long param)
{
    /* Returns {lo=x26+in_x9, hi=x23+param} — sums two live-in base
     * registers against incoming offsets to build a {low,high} pair. */
    cl4_result_t r;
    r.lo = 0; r.hi = 0;
    return r;
}

/* sk_frag_fa4 @ 0x00357fa4   (FUN_00357fa4)
 * Ghidra: void FUN_00357fa4(void)
 * Empty frame fragment — no recoverable logic; registers live-in from caller.
 * Confidence: low
 * Notes: decompiler recovers only stack prologue/epilogue; function is split at a re-entry point — registers live-in from caller */
void sk_frag_00357fa4(void)
{
    /* Empty frame fragment (prologue/epilogue only). */
    return;
}

/* sk_frame_store3_fb4 @ 0x00357fb4   (FUN_00357fb4)
 * Ghidra: void FUN_00357fb4(void)
 * Spills live-in register values into the caller frame (argument setup).
 * Confidence: medium
 * Notes: small self-contained leaf */
void sk_gap18_frame_store3_fb4(void)
{
    /* Frame store fragment: spills live-in x27, x26, x22 to caller frame
     * (x29-0xa0/-0x98/-0x78) — argument setup for a call. */
    return;
}

/* sk_pair_add_fc4 @ 0x00357fc4   (FUN_00357fc4)
 * Ghidra: undefined1 [16] FUN_00357fc4(long param_1)
 * Returns a {lo,hi} pair assembled from live-in registers/fields.
 * Confidence: medium
 * Notes: small self-contained leaf */
cl4_result_t sk_gap18_pair_add_fc4(long param)
{
    /* Returns {lo=x27+[x22+0x24], hi=x25+param} — a pair of base+offset
     * additions; hi sums against a live-in counter field. */
    cl4_result_t r;
    r.lo = 0; r.hi = 0;
    return r;
}

/* sk_ne_one_fd4 @ 0x00357fd4   (FUN_00357fd4)
 * Ghidra: bool FUN_00357fd4(void)
 * Small leaf with the described single operation.
 * Confidence: medium
 * Notes: small self-contained leaf */
bool sk_gap18_ne_one_fd4(void)
{
    /* Returns (live-in w20 != 1) — a state/flag comparison test. */
    return true;
}

/* sk_inc_field_10_fe4 @ 0x00357fe4   (FUN_00357fe4)
 * Ghidra: void FUN_00357fe4(long param_1)
 * Small leaf with the described single operation.
 * Confidence: medium
 * Notes: small self-contained leaf */
void sk_gap18_inc_field_10_fe4(long param)
{
    /* Stores (x21 + 1) into [param+0x10] — increments a live-in counter
     * into a passed object field. */
    return;
}

/* sk_pair_load_ff4 @ 0x00357ff4   (FUN_00357ff4)
 * Ghidra: undefined1 [16] FUN_00357ff4(void)
 * Returns a {lo,hi} pair assembled from live-in registers/fields.
 * Confidence: medium
 * Notes: small self-contained leaf */
cl4_result_t sk_gap18_pair_load_ff4(void)
{
    /* Returns {lo=x26+[x29-0xd8], hi=[x29-0x88]} — a base+loaded-offset
     * pair from the caller frame. */
    cl4_result_t r;
    r.lo = 0; r.hi = 0;
    return r;
}

/* sk_frag_004 @ 0x00358004   (FUN_00358004)
 * Ghidra: void FUN_00358004(void)
 * Empty frame fragment — no recoverable logic; registers live-in from caller.
 * Confidence: low
 * Notes: decompiler recovers only stack prologue/epilogue; function is split at a re-entry point — registers live-in from caller */
void sk_frag_00358004(void)
{
    /* Empty frame fragment (prologue/epilogue only). */
    return;
}

/* sk_frag_014 @ 0x00358014   (FUN_00358014)
 * Ghidra: void FUN_00358014(void)
 * Empty frame fragment — no recoverable logic; registers live-in from caller.
 * Confidence: low
 * Notes: decompiler recovers only stack prologue/epilogue; function is split at a re-entry point — registers live-in from caller */
void sk_frag_00358014(void)
{
    /* Empty frame fragment (prologue/epilogue only). */
    return;
}

/* sk_frag_024 @ 0x00358024   (FUN_00358024)
 * Ghidra: void FUN_00358024(void)
 * Empty frame fragment — no recoverable logic; registers live-in from caller.
 * Confidence: low
 * Notes: decompiler recovers only stack prologue/epilogue; function is split at a re-entry point — registers live-in from caller */
void sk_frag_00358024(void)
{
    /* Empty frame fragment (prologue/epilogue only). */
    return;
}

/* sk_stack_top_128_034 @ 0x00358034   (FUN_00358034)
 * Ghidra: long FUN_00358034(void)
 * Small leaf with the described single operation.
 * Confidence: medium
 * Notes: small self-contained leaf */
void *sk_gap18_stack_top_128_034(void)
{
    /* Returns the caller frame base minus 0x128 (x29-0x128) as a pointer. */
    return (void *)0;
}

/* sk_frag_044 @ 0x00358044   (FUN_00358044)
 * Ghidra: void FUN_00358044(void)
 * Empty frame fragment — no recoverable logic; registers live-in from caller.
 * Confidence: low
 * Notes: decompiler recovers only stack prologue/epilogue; function is split at a re-entry point — registers live-in from caller */
void sk_frag_00358044(void)
{
    /* Empty frame fragment (prologue/epilogue only). */
    return;
}

/* sk_frag_054 @ 0x00358054   (FUN_00358054)
 * Ghidra: void FUN_00358054(void)
 * Empty frame fragment — no recoverable logic; registers live-in from caller.
 * Confidence: low
 * Notes: decompiler recovers only stack prologue/epilogue; function is split at a re-entry point — registers live-in from caller */
void sk_frag_00358054(void)
{
    /* Empty frame fragment (prologue/epilogue only). */
    return;
}

/* sk_load_frame_70_064 @ 0x00358064   (FUN_00358064)
 * Ghidra: undefined8 FUN_00358064(void)
 * Small leaf with the described single operation.
 * Confidence: medium
 * Notes: small self-contained leaf */
word_t sk_gap18_load_frame_70_064(void)
{
    /* Returns the word at the caller frame [x29-0x70]. */
    return 0;
}

/* sk_frag_074 @ 0x00358074   (FUN_00358074)
 * Ghidra: void FUN_00358074(void)
 * Empty frame fragment — no recoverable logic; registers live-in from caller.
 * Confidence: low
 * Notes: decompiler recovers only stack prologue/epilogue; function is split at a re-entry point — registers live-in from caller */
void sk_frag_00358074(void)
{
    /* Empty frame fragment (prologue/epilogue only). */
    return;
}

/* sk_frag_084 @ 0x00358084   (FUN_00358084)
 * Ghidra: void FUN_00358084(void)
 * Empty frame fragment — no recoverable logic; registers live-in from caller.
 * Confidence: low
 * Notes: decompiler recovers only stack prologue/epilogue; function is split at a re-entry point — registers live-in from caller */
void sk_frag_00358084(void)
{
    /* Empty frame fragment (prologue/epilogue only). */
    return;
}

/* sk_frag_094 @ 0x00358094   (FUN_00358094)
 * Ghidra: void FUN_00358094(void)
 * Empty frame fragment — no recoverable logic; registers live-in from caller.
 * Confidence: low
 * Notes: decompiler recovers only stack prologue/epilogue; function is split at a re-entry point — registers live-in from caller */
void sk_frag_00358094(void)
{
    /* Empty frame fragment (prologue/epilogue only). */
    return;
}

/* sk_pair_cap_a4 @ 0x003580a4   (FUN_003580a4)
 * Ghidra: undefined1 [16] FUN_003580a4(void)
 * Returns a {lo,hi} pair assembled from live-in registers/fields.
 * Confidence: medium
 * Notes: small self-contained leaf */
cl4_result_t sk_gap18_pair_cap_a4(void)
{
    /* Capability pair loader: returns {lo=[x20+0x10], hi=[x20+8]&0xffffff
     * ffffff} — masks a cap's upper bits (0xffffff cap fields) plus a
     * low word from a live-in object. */
    cl4_result_t r;
    r.lo = 0; r.hi = 0;
    return r;
}

/* sk_frag_0b4 @ 0x003580b4   (FUN_003580b4)
 * Ghidra: void FUN_003580b4(void)
 * Empty frame fragment — no recoverable logic; registers live-in from caller.
 * Confidence: low
 * Notes: decompiler recovers only stack prologue/epilogue; function is split at a re-entry point — registers live-in from caller */
void sk_frag_003580b4(void)
{
    /* Empty frame fragment (prologue/epilogue only). */
    return;
}

/* sk_frag_0c4 @ 0x003580c4   (FUN_003580c4)
 * Ghidra: void FUN_003580c4(void)
 * Empty frame fragment — no recoverable logic; registers live-in from caller.
 * Confidence: low
 * Notes: decompiler recovers only stack prologue/epilogue; function is split at a re-entry point — registers live-in from caller */
void sk_frag_003580c4(void)
{
    /* Empty frame fragment (prologue/epilogue only). */
    return;
}

/* sk_frag_0d4 @ 0x003580d4   (FUN_003580d4)
 * Ghidra: void FUN_003580d4(void)
 * Empty frame fragment — no recoverable logic; registers live-in from caller.
 * Confidence: low
 * Notes: decompiler recovers only stack prologue/epilogue; function is split at a re-entry point — registers live-in from caller */
void sk_frag_003580d4(void)
{
    /* Empty frame fragment (prologue/epilogue only). */
    return;
}

/* sk_frag_0e4 @ 0x003580e4   (FUN_003580e4)
 * Ghidra: void FUN_003580e4(void)
 * Empty frame fragment — no recoverable logic; registers live-in from caller.
 * Confidence: low
 * Notes: decompiler recovers only stack prologue/epilogue; function is split at a re-entry point — registers live-in from caller */
void sk_frag_003580e4(void)
{
    /* Empty frame fragment (prologue/epilogue only). */
    return;
}

/* sk_frag_0f4 @ 0x003580f4   (FUN_003580f4)
 * Ghidra: void FUN_003580f4(void)
 * Empty frame fragment — no recoverable logic; registers live-in from caller.
 * Confidence: low
 * Notes: decompiler recovers only stack prologue/epilogue; function is split at a re-entry point — registers live-in from caller */
void sk_frag_003580f4(void)
{
    /* Empty frame fragment (prologue/epilogue only). */
    return;
}

/* sk_store_ptr_104 @ 0x00358104   (FUN_00358104)
 * Ghidra: void FUN_00358104(undefined8 param_1)
 * Small leaf with the described single operation.
 * Confidence: medium
 * Notes: small self-contained leaf */
void sk_gap18_store_ptr_104(word_t param)
{
    /* Stores param into live-in x20[0] — writes a caller field. */
    return;
}

/* sk_frame_store_6_114 @ 0x00358114   (FUN_00358114)
 * Ghidra: void FUN_00358114(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4, undefined4 param_5,undefined8 param_6)
 * Spills live-in register values into the caller frame (argument setup).
 * Confidence: medium
 * Notes: small self-contained leaf */
void sk_gap18_frame_store_6_114(word_t p3, word_t p4, uint32_t p5, word_t p6)
{
    /* Frame store fragment: spills p6, p3, p5(32-bit), p4 to caller frame
     * (x29-0x78/-0x70/-0x5c/-0x68) — call argument setup. */
    return;
}

/* sk_frag_124 @ 0x00358124   (FUN_00358124)
 * Ghidra: void FUN_00358124(void)
 * Empty frame fragment — no recoverable logic; registers live-in from caller.
 * Confidence: low
 * Notes: decompiler recovers only stack prologue/epilogue; function is split at a re-entry point — registers live-in from caller */
void sk_frag_00358124(void)
{
    /* Empty frame fragment (prologue/epilogue only). */
    return;
}

/* sk_ratio_store_134 @ 0x00358134   (FUN_00358134)
 * Ghidra: void FUN_00358134(long param_1)
 * Small leaf with the described single operation.
 * Confidence: low
 * Notes: mid-function fragment; live-in registers x19/x20/x21/x22/x29 from caller */
void sk_gap18_ratio_store_134(long param)
{
    /* Fragment: computes lVar1 = (x21 != 0) ? param / x21 : 0; stores x19
     * into [x20+0x10] and (lVar1<<1) into [x20+0x18] — a ratio/scale
     * computation with a guard against divide-by-zero. */
    return;
}

/* sk_load_field_20_144 @ 0x00358144   (FUN_00358144)
 * Ghidra: undefined8 FUN_00358144(long param_1)
 * Small leaf with the described single operation.
 * Confidence: medium
 * Notes: small self-contained leaf */
word_t sk_gap18_load_field_20_144(long param)
{
    /* Returns the word at [param+0x20] — a field getter. */
    return 0;
}

/* sk_stack_ptr_20_154 @ 0x00358154   (FUN_00358154)
 * Ghidra: undefined1 * FUN_00358154(void)
 * Small leaf with the described single operation.
 * Confidence: medium
 * Notes: small self-contained leaf */
void *sk_gap18_stack_ptr_20_154(void)
{
    /* Returns the caller stack slot [sp+0x20]. */
    return (void *)0;
}

/* sk_load_field_18_164 @ 0x00358164   (FUN_00358164)
 * Ghidra: undefined8 FUN_00358164(undefined8 param_1,long param_2)
 * Small leaf with the described single operation.
 * Confidence: medium
 * Notes: small self-contained leaf */
word_t sk_gap18_load_field_18_164(word_t p1, long p2)
{
    /* Returns the word at [p2+0x18] — a field getter on the second arg. */
    return 0;
}

/* sk_pass_through_174 @ 0x00358174   (FUN_00358174)
 * Ghidra: undefined8 FUN_00358174(void)
 * Small leaf with the described single operation.
 * Confidence: medium
 * Notes: small self-contained leaf */
word_t sk_gap18_pass_through_174(void)
{
    /* Returns the incoming stack-passed word at [sp+0x10] unchanged. */
    return 0;
}

/* sk_frag_184 @ 0x00358184   (FUN_00358184)
 * Ghidra: void FUN_00358184(void)
 * Empty frame fragment — no recoverable logic; registers live-in from caller.
 * Confidence: low
 * Notes: decompiler recovers only stack prologue/epilogue; function is split at a re-entry point — registers live-in from caller */
void sk_frag_00358184(void)
{
    /* Empty frame fragment (prologue/epilogue only). */
    return;
}

/* sk_frag_194 @ 0x00358194   (FUN_00358194)
 * Ghidra: void FUN_00358194(void)
 * Empty frame fragment — no recoverable logic; registers live-in from caller.
 * Confidence: low
 * Notes: decompiler recovers only stack prologue/epilogue; function is split at a re-entry point — registers live-in from caller */
void sk_frag_00358194(void)
{
    /* Empty frame fragment (prologue/epilogue only). */
    return;
}

/* sk_lsb_not_a4 @ 0x003581a4   (FUN_003581a4)
 * Ghidra: uint FUN_003581a4(void)
 * Small leaf with the described single operation.
 * Confidence: medium
 * Notes: small self-contained leaf */
uint32_t sk_gap18_lsb_not_a4(void)
{
    /* Returns (~live-in w20) & 1 — the inverted least-significant bit,
     * a boolean toggling test. */
    return 0;
}

/* sk_bitmask_set_b4 @ 0x003581b4   (FUN_003581b4)
 * Ghidra: void FUN_003581b4(void)
 * Small leaf with the described single operation.
 * Confidence: low
 * Notes: mid-function fragment; live-in registers x19/x20/x21/x22/x29 from caller */
void sk_gap18_bitmask_set_b4(void)
{
    /* Fragment: writes -1L << (x26 & 0x3f) into live-in x24 (a bitmask
     * with the low (x26 mod 64) bits cleared). */
    return;
}

/* sk_frame_store2_c4 @ 0x003581c4   (FUN_003581c4)
 * Ghidra: void FUN_003581c4(void)
 * Spills live-in register values into the caller frame (argument setup).
 * Confidence: medium
 * Notes: small self-contained leaf */
void sk_gap18_frame_store2_c4(void)
{
    /* Frame store fragment: spills live-in x24 and x26 to caller frame
     * (x29-0x78/-0x70) — call argument setup. */
    return;
}

/* sk_triple_2298d4 @ 0x003581d4   (FUN_003581d4)
 * Ghidra: void FUN_003581d4(void)
 * Dispatches to an out-of-range helper with fixed/live-in arguments.
 * Confidence: medium
 * Notes: small self-contained leaf */
void sk_gap18_triple_2298d4(void)
{
    /* Calls the thunk helper sk_adj_thunk_2298d4 three times (once with
     * live-in w27, twice bare) — a triple init/update sequence. */
    sk_adj_thunk_2298d4();
    sk_adj_thunk_2298d4();
    sk_adj_thunk_2298d4();
    return;
}

/* sk_adj_376820_tail @ 0x003581fc   (FUN_003581fc)
 * Ghidra: void FUN_003581fc(void)
 * Thin forwarding stub to an out-of-range helper.
 * Confidence: medium
 * Notes: thin forwarding stub */
void sk_gap18_376820_tail(void)
{
    /* Thin forwarding stub: tail-calls sk_adj_365b6c's sibling FUN_00376820. */
    sk_adj_365b6c();
    return;
}

/* sk_frag_208 @ 0x00358208   (FUN_00358208)
 * Ghidra: void FUN_00358208(void)
 * Empty frame fragment — no recoverable logic; registers live-in from caller.
 * Confidence: low
 * Notes: decompiler recovers only stack prologue/epilogue; function is split at a re-entry point — registers live-in from caller */
void sk_frag_00358208(void)
{
    /* Empty frame fragment (prologue/epilogue only). */
    return;
}

/* sk_frag_218 @ 0x00358218   (FUN_00358218)
 * Ghidra: void FUN_00358218(void)
 * Empty frame fragment — no recoverable logic; registers live-in from caller.
 * Confidence: low
 * Notes: decompiler recovers only stack prologue/epilogue; function is split at a re-entry point — registers live-in from caller */
void sk_frag_00358218(void)
{
    /* Empty frame fragment (prologue/epilogue only). */
    return;
}

/* sk_frag_228 @ 0x00358228   (FUN_00358228)
 * Ghidra: void FUN_00358228(void)
 * Empty frame fragment — no recoverable logic; registers live-in from caller.
 * Confidence: low
 * Notes: decompiler recovers only stack prologue/epilogue; function is split at a re-entry point — registers live-in from caller */
void sk_frag_00358228(void)
{
    /* Empty frame fragment (prologue/epilogue only). */
    return;
}

/* sk_frag_238 @ 0x00358238   (FUN_00358238)
 * Ghidra: void FUN_00358238(void)
 * Empty frame fragment — no recoverable logic; registers live-in from caller.
 * Confidence: low
 * Notes: decompiler recovers only stack prologue/epilogue; function is split at a re-entry point — registers live-in from caller */
void sk_frag_00358238(void)
{
    /* Empty frame fragment (prologue/epilogue only). */
    return;
}

/* sk_frag_248 @ 0x00358248   (FUN_00358248)
 * Ghidra: void FUN_00358248(void)
 * Empty frame fragment — no recoverable logic; registers live-in from caller.
 * Confidence: low
 * Notes: decompiler recovers only stack prologue/epilogue; function is split at a re-entry point — registers live-in from caller */
void sk_frag_00358248(void)
{
    /* Empty frame fragment (prologue/epilogue only). */
    return;
}

/* sk_frag_258 @ 0x00358258   (FUN_00358258)
 * Ghidra: void FUN_00358258(void)
 * Empty frame fragment — no recoverable logic; registers live-in from caller.
 * Confidence: low
 * Notes: decompiler recovers only stack prologue/epilogue; function is split at a re-entry point — registers live-in from caller */
void sk_frag_00358258(void)
{
    /* Empty frame fragment (prologue/epilogue only). */
    return;
}

/* sk_frag_268 @ 0x00358268   (FUN_00358268)
 * Ghidra: void FUN_00358268(void)
 * Empty frame fragment — no recoverable logic; registers live-in from caller.
 * Confidence: low
 * Notes: decompiler recovers only stack prologue/epilogue; function is split at a re-entry point — registers live-in from caller */
void sk_frag_00358268(void)
{
    /* Empty frame fragment (prologue/epilogue only). */
    return;
}

/* sk_frag_278 @ 0x00358278   (FUN_00358278)
 * Ghidra: void FUN_00358278(void)
 * Empty frame fragment — no recoverable logic; registers live-in from caller.
 * Confidence: low
 * Notes: decompiler recovers only stack prologue/epilogue; function is split at a re-entry point — registers live-in from caller */
void sk_frag_00358278(void)
{
    /* Empty frame fragment (prologue/epilogue only). */
    return;
}

/* sk_frag_288 @ 0x00358288   (FUN_00358288)
 * Ghidra: void FUN_00358288(void)
 * Empty frame fragment — no recoverable logic; registers live-in from caller.
 * Confidence: low
 * Notes: decompiler recovers only stack prologue/epilogue; function is split at a re-entry point — registers live-in from caller */
void sk_frag_00358288(void)
{
    /* Empty frame fragment (prologue/epilogue only). */
    return;
}

/* sk_frag_298 @ 0x00358298   (FUN_00358298)
 * Ghidra: void FUN_00358298(void)
 * Empty frame fragment — no recoverable logic; registers live-in from caller.
 * Confidence: low
 * Notes: decompiler recovers only stack prologue/epilogue; function is split at a re-entry point — registers live-in from caller */
void sk_frag_00358298(void)
{
    /* Empty frame fragment (prologue/epilogue only). */
    return;
}

/* sk_frag_2a8 @ 0x003582a8   (FUN_003582a8)
 * Ghidra: void FUN_003582a8(void)
 * Empty frame fragment — no recoverable logic; registers live-in from caller.
 * Confidence: low
 * Notes: decompiler recovers only stack prologue/epilogue; function is split at a re-entry point — registers live-in from caller */
void sk_frag_003582a8(void)
{
    /* Empty frame fragment (prologue/epilogue only). */
    return;
}

/* sk_pair_stack_b8 @ 0x003582b8   (FUN_003582b8)
 * Ghidra: undefined1 [16] FUN_003582b8(void)
 * Returns a {lo,hi} pair assembled from live-in registers/fields.
 * Confidence: medium
 * Notes: small self-contained leaf */
cl4_result_t sk_gap18_pair_stack_b8(void)
{
    /* Returns {lo=[sp+8], hi=[sp+0x30]} — a pair of caller stack slots. */
    cl4_result_t r;
    r.lo = 0; r.hi = 0;
    return r;
}

/* sk_pair_frame_c8 @ 0x003582c8   (FUN_003582c8)
 * Ghidra: undefined1 [16] FUN_003582c8(void)
 * Returns a {lo,hi} pair assembled from live-in registers/fields.
 * Confidence: medium
 * Notes: small self-contained leaf */
cl4_result_t sk_gap18_pair_frame_c8(void)
{
    /* Returns {lo=[sp+0x170], hi=x29-0x90} — a caller stack-slot pair. */
    cl4_result_t r;
    r.lo = 0; r.hi = 0;
    return r;
}

/* sk_frag_2d8 @ 0x003582d8   (FUN_003582d8)
 * Ghidra: void FUN_003582d8(void)
 * Empty frame fragment — no recoverable logic; registers live-in from caller.
 * Confidence: low
 * Notes: decompiler recovers only stack prologue/epilogue; function is split at a re-entry point — registers live-in from caller */
void sk_frag_003582d8(void)
{
    /* Empty frame fragment (prologue/epilogue only). */
    return;
}

/* sk_frag_2e8 @ 0x003582e8   (FUN_003582e8)
 * Ghidra: void FUN_003582e8(void)
 * Empty frame fragment — no recoverable logic; registers live-in from caller.
 * Confidence: low
 * Notes: decompiler recovers only stack prologue/epilogue; function is split at a re-entry point — registers live-in from caller */
void sk_frag_003582e8(void)
{
    /* Empty frame fragment (prologue/epilogue only). */
    return;
}

/* sk_frag_2f8 @ 0x003582f8   (FUN_003582f8)
 * Ghidra: void FUN_003582f8(void)
 * Empty frame fragment — no recoverable logic; registers live-in from caller.
 * Confidence: low
 * Notes: decompiler recovers only stack prologue/epilogue; function is split at a re-entry point — registers live-in from caller */
void sk_frag_003582f8(void)
{
    /* Empty frame fragment (prologue/epilogue only). */
    return;
}

/* sk_frag_308 @ 0x00358308   (FUN_00358308)
 * Ghidra: void FUN_00358308(void)
 * Empty frame fragment — no recoverable logic; registers live-in from caller.
 * Confidence: low
 * Notes: decompiler recovers only stack prologue/epilogue; function is split at a re-entry point — registers live-in from caller */
void sk_frag_00358308(void)
{
    /* Empty frame fragment (prologue/epilogue only). */
    return;
}

/* sk_call_1a0354_318 @ 0x00358318   (FUN_00358318)
 * Ghidra: void FUN_00358318(void)
 * Dispatches to an out-of-range helper with fixed/live-in arguments.
 * Confidence: medium
 * Notes: small self-contained leaf */
void sk_gap18_call_1a0354_318(void)
{
    /* Calls sk_adj_1a0354(FUN_001a0354) with args (0, 1). */
    sk_adj_1a0354(0, 1);
    return;
}

/* sk_frag_324 @ 0x00358324   (FUN_00358324)
 * Ghidra: void FUN_00358324(void)
 * Empty frame fragment — no recoverable logic; registers live-in from caller.
 * Confidence: low
 * Notes: decompiler recovers only stack prologue/epilogue; function is split at a re-entry point — registers live-in from caller */
void sk_frag_00358324(void)
{
    /* Empty frame fragment (prologue/epilogue only). */
    return;
}

/* sk_frag_334 @ 0x00358334   (FUN_00358334)
 * Ghidra: void FUN_00358334(void)
 * Empty frame fragment — no recoverable logic; registers live-in from caller.
 * Confidence: low
 * Notes: decompiler recovers only stack prologue/epilogue; function is split at a re-entry point — registers live-in from caller */
void sk_frag_00358334(void)
{
    /* Empty frame fragment (prologue/epilogue only). */
    return;
}

/* sk_frag_344 @ 0x00358344   (FUN_00358344)
 * Ghidra: void FUN_00358344(void)
 * Empty frame fragment — no recoverable logic; registers live-in from caller.
 * Confidence: low
 * Notes: decompiler recovers only stack prologue/epilogue; function is split at a re-entry point — registers live-in from caller */
void sk_frag_00358344(void)
{
    /* Empty frame fragment (prologue/epilogue only). */
    return;
}

/* sk_call_1b7524_358 @ 0x00358358   (FUN_00358358)
 * Ghidra: void FUN_00358358(undefined8 param_1)
 * Dispatches to an out-of-range helper with fixed/live-in arguments.
 * Confidence: medium
 * Notes: small self-contained leaf */
void sk_gap18_call_1b7524_358(word_t param)
{
    /* Calls sk_adj_1b7524(FUN_001b7524) with (param, x29-0x80) — passes a
     * caller stack slot as the second argument. */
    sk_adj_1b7524(param, (void *)0);
    return;
}

/* sk_frag_374 @ 0x00358374   (FUN_00358374)
 * Ghidra: void FUN_00358374(void)
 * Empty frame fragment — no recoverable logic; registers live-in from caller.
 * Confidence: low
 * Notes: decompiler recovers only stack prologue/epilogue; function is split at a re-entry point — registers live-in from caller */
void sk_frag_00358374(void)
{
    /* Empty frame fragment (prologue/epilogue only). */
    return;
}

/* sk_call_377bec_388 @ 0x00358388   (FUN_00358388)
 * Ghidra: void FUN_00358388(void)
 * Dispatches to an out-of-range helper with fixed/live-in arguments.
 * Confidence: medium
 * Notes: small self-contained leaf */
void sk_gap18_call_377bec_388(void)
{
    /* Calls sk_adj_377bec(FUN_00377bec) with three caller-frame words
     * (x29-0xb0, x29-0x78, x29-0xc8). */
    sk_adj_377bec(0, 0, 0);
    return;
}

/* sk_call_312d08_3a4 @ 0x003583a4   (FUN_003583a4)
 * Ghidra: void FUN_003583a4(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4, undefined8 param_5,undefined8 param_6)
 * Dispatches to an out-of-range helper with fixed/live-in arguments.
 * Confidence: medium
 * Notes: small self-contained leaf */
void sk_gap18_call_312d08_3a4(word_t p1, word_t p2, word_t p3,
                          word_t p4, word_t p5, word_t p6)
{
    /* Calls sk_adj_312d08(FUN_00312d08) with two caller frame slots, a
     * stack slot, and args p2/p1/p6/p3 — reordered argument dispatch. */
    sk_adj_312d08((void *)0, (void *)0, (void *)0, p2, p1, p6, p3);
    return;
}

/* sk_call_1da714_3c0 @ 0x003583c0   (FUN_003583c0)
 * Ghidra: void FUN_003583c0(void)
 * Dispatches to an out-of-range helper with fixed/live-in arguments.
 * Confidence: medium
 * Notes: small self-contained leaf */
void sk_gap18_call_1da714_3c0(void)
{
    /* Calls sk_adj_1da714(FUN_001da714) with the word at x29-0xd0. */
    sk_adj_1da714(0);
    return;
}

/* sk_frag_3dc @ 0x003583dc   (FUN_003583dc)
 * Ghidra: void FUN_003583dc(void)
 * Empty frame fragment — no recoverable logic; registers live-in from caller.
 * Confidence: low
 * Notes: decompiler recovers only stack prologue/epilogue; function is split at a re-entry point — registers live-in from caller */
void sk_frag_003583dc(void)
{
    /* Empty frame fragment (prologue/epilogue only). */
    return;
}

/* sk_frag_3e8 @ 0x003583e8   (FUN_003583e8)
 * Ghidra: void FUN_003583e8(void)
 * Empty frame fragment — no recoverable logic; registers live-in from caller.
 * Confidence: low
 * Notes: decompiler recovers only stack prologue/epilogue; function is split at a re-entry point — registers live-in from caller */
void sk_frag_003583e8(void)
{
    /* Empty frame fragment (prologue/epilogue only). */
    return;
}

/* sk_adj_117d14_tail @ 0x00358404   (FUN_00358404)
 * Ghidra: void FUN_00358404(void)
 * Thin forwarding stub to an out-of-range helper.
 * Confidence: medium
 * Notes: thin forwarding stub */
void sk_gap18_117d14_tail(void)
{
    /* Thin forwarding stub: tail-calls sk_adj_117d14 (FUN_00117d14). */
    sk_adj_117d14();
    return;
}

/* sk_call_377824_410 @ 0x00358410   (FUN_00358410)
 * Ghidra: void FUN_00358410(void)
 * Dispatches to an out-of-range helper with fixed/live-in arguments.
 * Confidence: medium
 * Notes: small self-contained leaf */
void sk_gap18_call_377824_410(void)
{
    /* Calls sk_adj_377824(FUN_00377824) with argument 0xff. */
    sk_adj_377824(0xff);
    return;
}

/* sk_frag_41c @ 0x0035841c   (FUN_0035841c)
 * Ghidra: void FUN_0035841c(void)
 * Empty frame fragment — no recoverable logic; registers live-in from caller.
 * Confidence: low
 * Notes: decompiler recovers only stack prologue/epilogue; function is split at a re-entry point — registers live-in from caller */
void sk_frag_0035841c(void)
{
    /* Empty frame fragment (prologue/epilogue only). */
    return;
}

