/* Recreated from cl4_kernel.raw (cL4 Secure Kernel, arm64e, image base 0) --
 * the cL4 microkernel (GL1), "cL4 (679.100.61)". Ground truth: Ghidra FUN_
 * names + addresses in program cl4_kernel.raw.
 * Slice 28: 0x358f54-0x359c84 syscall/exception-entry region.
 * All names are estimates unless string/header-matched.
 *
 * This region is a dense table of small syscall/exception-entry thunks and
 * wrappers that forward to the reconstructed syscall engines (msg, cap, obj,
 * sched, ipc, vspace). Most are register-preserving stubs whose arguments
 * arrive in callee-saved registers and are re-passed to a single callee;
 * Ghidra models these via unaff_/in_ registers. Where a body reads or writes
 * a caller-frame register (unaff_xNN / in_wNN / in_stack_*), that access is
 * preserved as the register semantics below. Because the carried value is not
 * statically resolvable at the thunk, register-sourced names (x9,x10,x19..x28,
 * w8,w9,w22, x29_frame and the *_ptr / rec_* / pair_* / stack_* record slots)
 * are declared as file-scope placeholders so the C compiles; they denote the
 * actual ABI register / caller-frame slot at runtime. */

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "sk_internal.h"

/* ------------------------------------------------------------------ *
 * Out-of-slice cL4 helpers (declared extern with a one-line note; their
 * bodies are reconstructed by the range worker that owns them).
 * ------------------------------------------------------------------ */
extern void FUN_000026e8();  /* out of slice, @ 0x000026e8 (unspecified args) */
extern void FUN_00077070();  /* out of slice, @ 0x00077070 (unspecified args) */
extern void FUN_0008f6f4();  /* out of slice, @ 0x0008f6f4 (unspecified args) */
extern void FUN_001a84f4();  /* out of slice, @ 0x001a84f4 (unspecified args) */
extern void FUN_001a89a8();  /* out of slice, @ 0x001a89a8 (unspecified args) */
extern void FUN_001debac();  /* out of slice, @ 0x001debac (unspecified args) */
extern void FUN_001fb05c();  /* out of slice, @ 0x001fb05c (unspecified args) */
extern void FUN_00208418();  /* out of slice, @ 0x00208418 (unspecified args) */
extern void FUN_002085fc();  /* out of slice, @ 0x002085fc (unspecified args) */
extern void FUN_0020c5b0();  /* out of slice, @ 0x0020c5b0 (unspecified args) */
extern void FUN_002445ac();  /* out of slice, @ 0x002445ac (unspecified args) */
extern void FUN_0024c82c();  /* out of slice, @ 0x0024c82c (unspecified args) */
extern void FUN_002a0d50();  /* out of slice, @ 0x002a0d50 (unspecified args) */
extern void FUN_002a200c();  /* out of slice, @ 0x002a200c (unspecified args) */
extern void FUN_002aaf80();  /* out of slice, @ 0x002aaf80 (unspecified args) */
extern void FUN_00310a74();  /* out of slice, @ 0x00310a74 (unspecified args) */
extern void FUN_0031a1dc();  /* out of slice, @ 0x0031a1dc (unspecified args) */
extern void FUN_0031b560();  /* out of slice, @ 0x0031b560 (unspecified args) */
extern void FUN_00344ca8();  /* out of slice, @ 0x00344ca8 (unspecified args) */
extern void FUN_0035bc70();  /* out of slice, @ 0x0035bc70 (unspecified args) */
extern void FUN_0036986c();  /* out of slice, @ 0x0036986c (unspecified args) */
extern void FUN_00369a30();  /* out of slice, @ 0x00369a30 (unspecified args) */
extern void FUN_0036a940();  /* out of slice, @ 0x0036a940 (unspecified args) */
extern void FUN_0036a9a0();  /* out of slice, @ 0x0036a9a0 (unspecified args) */
extern void FUN_0036b270();  /* out of slice, @ 0x0036b270 (unspecified args) */
extern void FUN_003722e4();  /* out of slice, @ 0x003722e4 (unspecified args) */
extern void FUN_0037233c();  /* out of slice, @ 0x0037233c (unspecified args) */
extern void FUN_00377824();  /* out of slice, @ 0x00377824 (unspecified args) */
extern void FUN_003a25d4();  /* out of slice, @ 0x003a25d4 (unspecified args) */
extern void FUN_003a2610();  /* out of slice, @ 0x003a2610 (unspecified args) */
extern void FUN_003a261c();  /* out of slice, @ 0x003a261c (unspecified args) */
extern void thunk_FUN_00012568();  /* out of slice, @ 0xk_FUN_00012568 (unspecified args) */
extern void thunk_FUN_0036b270();  /* out of slice, @ 0xk_FUN_0036b270 (unspecified args) */

/* Register-sourced value placeholders (see header note). These are NOT globals;
 * they stand for the ABI register / caller-frame slot of the same name. */
extern uint64_t x9;  /* register/caller-frame slot placeholder */
extern uint64_t x10;  /* register/caller-frame slot placeholder */
extern uint64_t x19;  /* register/caller-frame slot placeholder */
extern uint64_t x20;  /* register/caller-frame slot placeholder */
extern uint64_t x21;  /* register/caller-frame slot placeholder */
extern uint64_t x22;  /* register/caller-frame slot placeholder */
extern uint64_t x23;  /* register/caller-frame slot placeholder */
extern uint64_t x24;  /* register/caller-frame slot placeholder */
extern uint64_t x25;  /* register/caller-frame slot placeholder */
extern uint64_t x26;  /* register/caller-frame slot placeholder */
extern uint64_t x27;  /* register/caller-frame slot placeholder */
extern uint64_t x28;  /* register/caller-frame slot placeholder */
extern uint32_t in_w8;  /* register/caller-frame slot placeholder */
extern uint32_t in_w9;  /* register/caller-frame slot placeholder */
extern uint64_t in_x9;  /* register/caller-frame slot placeholder */
extern uint32_t w22;  /* register/caller-frame slot placeholder */
extern uint64_t x29_frame;  /* register/caller-frame slot placeholder */
extern uint64_t * x20_ptr;  /* register/caller-frame slot placeholder */
extern uint64_t * obj;  /* register/caller-frame slot placeholder */
extern uint64_t * obj_x21;  /* register/caller-frame slot placeholder */
extern uint64_t * obj_x24;  /* register/caller-frame slot placeholder */
extern uint64_t * rec_x20;  /* register/caller-frame slot placeholder */
extern uint64_t * dst_x20;  /* register/caller-frame slot placeholder */
extern uint64_t * src_x19;  /* register/caller-frame slot placeholder */
extern uint64_t * rec_x19;  /* register/caller-frame slot placeholder */
extern uint64_t * rec_x21;  /* register/caller-frame slot placeholder */
extern uint64_t * pair_x20;  /* register/caller-frame slot placeholder */
extern uint64_t * pair_x19;  /* register/caller-frame slot placeholder */
extern uint64_t * trip_x19;  /* register/caller-frame slot placeholder */
extern uint64_t * tbl;  /* register/caller-frame slot placeholder */
extern uint64_t * x25_ptr;  /* register/caller-frame slot placeholder */
extern uint64_t stack_word_0;  /* register/caller-frame slot placeholder */
extern uint64_t stack_word_8;  /* register/caller-frame slot placeholder */
extern uint64_t stack_word_10;  /* register/caller-frame slot placeholder */
extern uint64_t stack_word_18;  /* register/caller-frame slot placeholder */
extern uint64_t stack_word_68;  /* register/caller-frame slot placeholder */
extern uint64_t * stack_buf;  /* register/caller-frame slot placeholder */
extern uint64_t * stack_buf_170;  /* register/caller-frame slot placeholder */
extern uint64_t stack_slot_20;  /* register/caller-frame slot placeholder */
extern uint64_t * stack_arg;  /* register/caller-frame slot placeholder */
extern char s_fatal_error[];  /* data symbol */
extern uint8_t DAT_005d3566[];  /* data symbol */
extern uint64_t DAT_0064c2d8;  /* register/caller-frame slot placeholder */
extern uint64_t DAT_004bbe30;  /* register/caller-frame slot placeholder */

/* FUN_00358f54 @ 0x00358f54   (est. cl4_syscall_noop)
 * Ghidra: void cl4_r28_358f54(void)  (Ghidra FUN_00358f54)
 * Empty stub: returns immediately. Likely a no-op syscall/exception-entry slot.
 * Confidence: low
 * Notes: Empty body; no callees.
 */
void cl4_r28_358f54(void)
{
    return;
}

/* FUN_00358f60 @ 0x00358f60   (est. cl4_syscall_ret_zero)
 * Ghidra: uint64_t cl4_r28_358f60(void)  (Ghidra FUN_00358f60)
 * Trivial stub returning 0 (success).
 * Confidence: low
 * Notes: Returns 0.
 */
uint64_t cl4_r28_358f60(void)
{
    return 0;
}

/* FUN_00358f78 @ 0x00358f78   (est. cl4_syscall_noop)
 * Ghidra: void cl4_r28_358f78(void)  (Ghidra FUN_00358f78)
 * Confidence: low
 * Notes: Empty.
 */
void cl4_r28_358f78(void)
{ return; }

/* FUN_00358f84 @ 0x00358f84   (est. cl4_syscall_noop)
 * Ghidra: void cl4_r28_358f84(void)  (Ghidra FUN_00358f84)
 * Confidence: low
 * Notes: Empty.
 */
void cl4_r28_358f84(void)
{ return; }

/* FUN_00358f90 @ 0x00358f90   (est. cl4_syscall_noop)
 * Ghidra: void cl4_r28_358f90(void)  (Ghidra FUN_00358f90)
 * Confidence: low
 * Notes: Empty.
 */
void cl4_r28_358f90(void)
{ return; }

/* FUN_00358f9c @ 0x00358f9c   (est. cl4_syscall_noop)
 * Ghidra: void cl4_r28_358f9c(void)  (Ghidra FUN_00358f9c)
 * Confidence: low
 * Notes: Empty.
 */
void cl4_r28_358f9c(void)
{ return; }

/* FUN_00358fa8 @ 0x00358fa8   (est. cl4_syscall_noop)
 * Ghidra: void cl4_r28_358fa8(void)  (Ghidra FUN_00358fa8)
 * Confidence: low
 * Notes: Empty.
 */
void cl4_r28_358fa8(void)
{ return; }

/* FUN_00358fb4 @ 0x00358fb4   (est. cl4_syscall_noop)
 * Ghidra: void cl4_r28_358fb4(void)  (Ghidra FUN_00358fb4)
 * Confidence: low
 * Notes: Empty.
 */
void cl4_r28_358fb4(void)
{ return; }

/* FUN_00358fc8 @ 0x00358fc8   (est. cl4_syscall_noop)
 * Ghidra: void cl4_r28_358fc8(void)  (Ghidra FUN_00358fc8)
 * Confidence: low
 * Notes: Empty.
 */
void cl4_r28_358fc8(void)
{ return; }

/* FUN_00358fdc @ 0x00358fdc   (est. cl4_syscall_wrapper_77070)
 * Ghidra: void cl4_r28_358fdc(void)  (Ghidra FUN_00358fdc)
 * Forwards two caller-frame stack words (registers x29-relative) to FUN_00077070,
 * an out-of-slice misc helper. The two arguments are the caller frame slots at
 * x29-0xb0 and x29-0x80.
 * Confidence: low
 * Notes: Passes caller-frame registers (unaff_x29) as args; callee out of slice.
 */
void cl4_r28_358fdc(void)
{
    FUN_00077070((void *)(x29_frame - 0xb0), (void *)(x29_frame - 0x80));
    return;
}

/* FUN_00358fe8 @ 0x00358fe8   (est. cl4_syscall_wrapper_a940)
 * Ghidra: void cl4_r28_358fe8(uint64_t p_a)  (Ghidra FUN_00358fe8)
 * Wrapper: forwards one argument with constants (0x50, 7) to FUN_0036a940,
 * the region's syscall helper.
 * Confidence: low
 * Notes: Callee FUN_0036a940 out of slice.
 */
void cl4_r28_358fe8(uint64_t p_a)
{
    FUN_0036a940(p_a, 0x50, 7);
    return;
}

/* FUN_00358ff4 @ 0x00358ff4   (est. cl4_syscall_wrapper_7824)
 * Ghidra: void cl4_r28_358ff4(void)  (Ghidra FUN_00358ff4)
 * Wrapper: calls FUN_00377824 with the sentinel 0xff (all-ones byte).
 * Confidence: low
 * Notes: Callee FUN_00377824 out of slice.
 */
void cl4_r28_358ff4(void)
{
    FUN_00377824(0xff);
    return;
}

/* FUN_00359000 @ 0x00359000   (est. cl4_syscall_wrapper_22e4)
 * Ghidra: void cl4_r28_359000(uint64_t p_a,uint64_t p_b,uint64_t p_c,uint64_t p_d)  (Ghidra FUN_00359000)
 * Wrapper: forwards (p_a, p_c, p_c, p_d, 0) to FUN_003722e4. Note the middle
 * argument is passed twice (p_c), an argument-dup pattern common in syscall
 * thunks that alias the tag/type field.
 * Confidence: low
 * Notes: Callee FUN_003722e4 out of slice; arg p_b unused.
 */
void cl4_r28_359000(uint64_t p_a,uint64_t p_b,uint64_t p_c,uint64_t p_d)
{
    FUN_003722e4(p_a, p_c, p_c, p_d, 0);
    return;
}

/* FUN_0035900c @ 0x0035900c   (est. cl4_syscall_wrapper_a2610)
 * Ghidra: void cl4_r28_35900c(void)  (Ghidra FUN_0035900c)
 * Wrapper: calls FUN_003a2610(), the msg syscall dispatch, with no args.
 * Confidence: low
 * Notes: Callee FUN_003a2610 out of slice.
 */
void cl4_r28_35900c(void)
{
    FUN_003a2610();
    return;
}

/* FUN_00359018 @ 0x00359018   (est. cl4_syscall_noop)
 * Ghidra: void cl4_r28_359018(void)  (Ghidra FUN_00359018)
 * Confidence: low
 * Notes: Empty.
 */
void cl4_r28_359018(void)
{ return; }

/* FUN_00359024 @ 0x00359024   (est. cl4_syscall_noop)
 * Ghidra: void cl4_r28_359024(void)  (Ghidra FUN_00359024)
 * Confidence: low
 * Notes: Empty.
 */
void cl4_r28_359024(void)
{ return; }

/* FUN_00359030 @ 0x00359030   (est. cl4_syscall_noop)
 * Ghidra: void cl4_r28_359030(void)  (Ghidra FUN_00359030)
 * Confidence: low
 * Notes: Empty.
 */
void cl4_r28_359030(void)
{ return; }

/* FUN_0035903c @ 0x0035903c   (est. cl4_syscall_noop)
 * Ghidra: void cl4_r28_35903c(void)  (Ghidra FUN_0035903c)
 * Confidence: low
 * Notes: Empty.
 */
void cl4_r28_35903c(void)
{ return; }

/* FUN_00359054 @ 0x00359054   (est. cl4_syscall_noop)
 * Ghidra: void cl4_r28_359054(void)  (Ghidra FUN_00359054)
 * Confidence: low
 * Notes: Empty.
 */
void cl4_r28_359054(void)
{ return; }

/* FUN_00359088 @ 0x00359088   (est. cl4_syscall_build_cap_descriptor)
 * Ghidra: void cl4_r28_359088(uint64_t p_a)  (Ghidra FUN_00359088)
 * Builds a capability/frame descriptor at a caller-frame object (x22):
 * - word at +0x10 = (incoming x9 & 0xffffffffffff) | 0xd000000000000000  (tagged ptr)
 * - word at +0x18 = p_a
 * - word at +0x20 = 0
 * - byte at +0x48 = 0
 * then calls FUN_0036986c() to install the descriptor.
 * Confidence: low
 * Notes: Register x9 source for the tagged pointer (in_x9); object at caller frame x22 (unaff_x22).
 */
void cl4_r28_359088(uint64_t p_a)
{
    uint64_t *o = (uint64_t *)obj;
    uint8_t *ob = (uint8_t *)obj;
    o[0x10/8] = (in_x9 & 0xffffffffffffull) | 0xd000000000000000ull;
    o[0x18/8] = p_a;
    o[0x20/8] = 0;
    ob[0x48] = 0;
    FUN_0036986c();
    return;
}

/* FUN_003590ac @ 0x003590ac   (est. cl4_syscall_noop)
 * Ghidra: void cl4_r28_3590ac(void)  (Ghidra FUN_003590ac)
 * Confidence: low
 * Notes: Empty.
 */
void cl4_r28_3590ac(void)
{ return; }

/* FUN_003590cc @ 0x003590cc   (est. cl4_syscall_vspace_index_table)
 * Ghidra: void cl4_r28_3590cc(uint64_t p_idx)  (Ghidra FUN_003590cc)
 * Indexes a per-object table: base = object(x21)->field_48; index =
 * (p_idx | x23<<6). Passes base + field_48*index and 1 to FUN_0035bc70
 * (vspace helper).
 * Confidence: low
 * Notes: Registers x21/x23/x24 (unaff) carry object base / index high bits.
 */
void cl4_r28_3590cc(uint64_t p_idx)
{
    uint64_t base = *(uint64_t *)(obj_x21 + 0x48);
    FUN_0035bc70(base * (p_idx | (x23 << 6)) + (uint64_t)obj_x24, 1);
    return;
}

/* FUN_003590e4 @ 0x003590e4   (est. cl4_syscall_wrapper_4c82c)
 * Ghidra: void cl4_r28_3590e4(void)  (Ghidra FUN_003590e4)
 * Calls FUN_0024c82c(8, 8), a TCB helper with two size/count args of 8.
 * Confidence: low
 * Notes: Callee FUN_0024c82c out of slice.
 */
void cl4_r28_3590e4(void)
{
    FUN_0024c82c(8, 8);
    return;
}

/* FUN_0035911c @ 0x0035911c   (est. cl4_add)
 * Ghidra: int64_t cl4_r28_35911c(int64_t p_a,int64_t p_b)  (Ghidra FUN_0035911c)
 * Returns p_a + p_b (plain addition thunk).
 * Confidence: low
 * Notes: Trivial add.
 */
int64_t cl4_r28_35911c(int64_t p_a,int64_t p_b)
{
    return p_b + p_a;
}

/* FUN_00359124 @ 0x00359124   (est. cl4_msg_reg_load_and_dispatch)
 * Ghidra: void cl4_r28_359124(int64_t p_obj,uint64_t *p_src)  (Ghidra FUN_00359124)
 * Copies a 16-byte (2-word) value from p_src into a caller-frame slot (x20),
 * then calls FUN_003a25d4 with the word at p_obj+8 (a message-register helper).
 * Confidence: low
 * Notes: Destination slot at caller frame x20 (unaff_x20).
 */
void cl4_r28_359124(int64_t p_obj,uint64_t *p_src)
{
    uint64_t v0 = p_src[0];
    uint64_t v1 = p_src[1];
    uint64_t mreg = *(uint64_t *)(p_obj + 8);
    dst_x20[0] = v0;
    dst_x20[1] = v1;
    FUN_003a25d4(mreg);
    return;
}

/* FUN_00359134 @ 0x00359134   (est. cl4_syscall_wrapper_a84f4)
 * Ghidra: void cl4_r28_359134(void)  (Ghidra FUN_00359134)
 * Calls FUN_001a84f4 with the caller stack top (&stack0x8).
 * Confidence: low
 * Notes: Callee FUN_001a84f4 out of slice.
 */
void cl4_r28_359134(void)
{
    FUN_001a84f4(&stack_arg);
    return;
}

/* FUN_00359144 @ 0x00359144   (est. cl4_syscall_wrapper_445ac)
 * Ghidra: void cl4_r28_359144(void)  (Ghidra FUN_00359144)
 * Calls FUN_002445ac with the caller-frame word at x29-0xb8.
 * Confidence: low
 * Notes: Arg read from caller frame (unaff_x29).
 */
void cl4_r28_359144(void)
{
    FUN_002445ac(*(uint64_t *)(x29_frame - 0xb8));
    return;
}

/* FUN_00359178 @ 0x00359178   (est. cl4_syscall_build_record)
 * Ghidra: void cl4_r28_359178(uint64_t p_a)  (Ghidra FUN_00359178)
 * Fills a 6-word record at caller frame (x21):
 * [0]=p_a, [1]=x22, [2]=x19, [3]=0, byte[9]=3; then calls thunk_FUN_0036b270.
 * Confidence: low
 * Notes: Record at caller frame x21; regs x19/x22 sources (unaff).
 */
void cl4_r28_359178(uint64_t p_a)
{
    rec_x21[0] = p_a;
    rec_x21[1] = x22;
    rec_x21[2] = x19;
    rec_x21[3] = 0;
    *(uint8_t *)&rec_x21[9] = 3;
    thunk_FUN_0036b270();
    return;
}

/* FUN_00359198 @ 0x00359198   (est. cl4_syscall_wrapper_8418)
 * Ghidra: void cl4_r28_359198(void)  (Ghidra FUN_00359198)
 * Calls FUN_00208418(*x25, 0): object helper with the word at caller frame x25.
 * Confidence: low
 * Notes: Arg from caller frame x25 (unaff).
 */
void cl4_r28_359198(void)
{
    FUN_00208418(*x25_ptr, 0);
    return;
}

/* FUN_003591b4 @ 0x003591b4   (est. cl4_syscall_wrapper_026e8)
 * Ghidra: void cl4_r28_3591b4(void)  (Ghidra FUN_003591b4)
 * Calls FUN_000026e8(x29-0x78), a boot helper with a caller-frame buffer.
 * Confidence: low
 * Notes: Callee FUN_000026e8 out of slice.
 */
void cl4_r28_3591b4(void)
{
    FUN_000026e8((void *)(x29_frame - 0x78));
    return;
}

/* FUN_003591d0 @ 0x003591d0   (est. cl4_syscall_wrapper_b270)
 * Ghidra: void cl4_r28_3591d0(int64_t p_off)  (Ghidra FUN_003591d0)
 * Calls FUN_0036b270 with the word at x20 + p_off + 8.
 * Confidence: low
 * Notes: Base at caller frame x20 (unaff).
 */
void cl4_r28_3591d0(int64_t p_off)
{
    FUN_0036b270(*(uint64_t *)(x20 + p_off + 8));
    return;
}

/* FUN_003591e0 @ 0x003591e0   (est. cl4_field_store_10)
 * Ghidra: void cl4_r28_3591e0(uint64_t p_a,uint64_t p_b,uint64_t p_c,int64_t p_rec)  (Ghidra FUN_003591e0)
 * Writes p_a into record slot +0x10. Field store thunk.
 * Confidence: low
 * Notes: Simple field store.
 */
void cl4_r28_3591e0(uint64_t p_a,uint64_t p_b,uint64_t p_c,int64_t p_rec)
{
    *(uint64_t *)(p_rec + 0x10) = p_a;
    return;
}

/* FUN_003591e8 @ 0x003591e8   (est. cl4_syscall_wrapper_debac)
 * Ghidra: void cl4_r28_3591e8(void)  (Ghidra FUN_003591e8)
 * Calls FUN_001debac(), a cap helper.
 * Confidence: low
 * Notes: Callee FUN_001debac out of slice.
 */
void cl4_r28_3591e8(void)
{
    FUN_001debac();
    return;
}

/* FUN_003591f4 @ 0x003591f4   (est. cl4_syscall_noop)
 * Ghidra: void cl4_r28_3591f4(void)  (Ghidra FUN_003591f4)
 * Confidence: low
 * Notes: Empty.
 */
void cl4_r28_3591f4(void)
{ return; }

/* FUN_00359208 @ 0x00359208   (est. cl4_syscall_wrapper_12568)
 * Ghidra: void cl4_r28_359208(uint64_t p_a)  (Ghidra FUN_00359208)
 * Calls thunk_FUN_00012568(p_a, ~0ull, ~0ull) — a boot helper with two
 * all-ones sentinel args (likely 'any capability' markers).
 * Confidence: low
 * Notes: Callee thunk_FUN_00012568 out of slice.
 */
void cl4_r28_359208(uint64_t p_a)
{
    thunk_FUN_00012568(p_a, 0xffffffffffffffffull, 0xffffffffffffffffull);
    return;
}

/* FUN_00359214 @ 0x00359214   (est. cl4_syscall_wrapper_a0d50)
 * Ghidra: void cl4_r28_359214(void)  (Ghidra FUN_00359214)
 * Calls FUN_002a0d50(), a sched helper.
 * Confidence: low
 * Notes: Callee FUN_002a0d50 out of slice.
 */
void cl4_r28_359214(void)
{
    FUN_002a0d50();
    return;
}

/* FUN_0035921c @ 0x0035921c   (est. cl4_syscall_wrapper_9a30)
 * Ghidra: void cl4_r28_35921c(void)  (Ghidra FUN_0035921c)
 * Calls FUN_00369a30(*x20, &stack0x18): passes the word at caller frame x20
 * and a stack buffer.
 * Confidence: low
 * Notes: Args from caller frame x20 / stack.
 */
void cl4_r28_35921c(void)
{
    FUN_00369a30(*x20_ptr, &stack_buf);
    return;
}

/* FUN_0035922c @ 0x0035922c   (est. cl4_fold_mul)
 * Ghidra: uint32_t cl4_r28_35922c(void)  (Ghidra FUN_0035922c)
 * Register-sourced word multiply with byte-swap folding:
 * (w8*w9 & 0xff00ff00)>>8 | (w8*w9 & 0xff00ff)<<8.
 * A constant-time-ish folding multiply (likely a hash/checksum primitive).
 * Operands arrive in registers w8/w9 (not modeled as params).
 * Confidence: low
 * Notes: Operands in regs w8/w9 (in_w8/in_w9).
 */
uint32_t cl4_r28_35922c(void)
{
    uint32_t prod = in_w8 * in_w9;
    return ((prod & 0xff00ff00u) >> 8) | ((prod & 0xff00ffu) << 8);
}

/* FUN_00359238 @ 0x00359238   (est. cl4_fold_mul_rot)
 * Ghidra: uint32_t cl4_r28_359238(void)  (Ghidra FUN_00359238)
 * Register-sourced word multiply folding the two halves:
 * (prod>>16) | prod*0x10000. A 32-bit rotation-ish hash primitive.
 * Operands in regs w8/w9.
 * Confidence: low
 * Notes: Operands in regs w8/w9 (in_w8/in_w9).
 */
uint32_t cl4_r28_359238(void)
{
    uint32_t prod = (uint32_t)(in_w8 * in_w9);
    return (prod >> 16) | (prod * 0x10000);
}

/* FUN_00359244 @ 0x00359244   (est. cl4_syscall_wrapper_a200c)
 * Ghidra: void cl4_r28_359244(void)  (Ghidra FUN_00359244)
 * Calls FUN_002a200c(), a sched helper.
 * Confidence: low
 * Notes: Callee FUN_002a200c out of slice.
 */
void cl4_r28_359244(void)
{
    FUN_002a200c();
    return;
}

/* FUN_00359284 @ 0x00359284   (est. cl4_syscall_noop)
 * Ghidra: void cl4_r28_359284(void)  (Ghidra FUN_00359284)
 * Confidence: low
 * Notes: Empty.
 */
void cl4_r28_359284(void)
{ return; }

/* FUN_00359290 @ 0x00359290   (est. cl4_syscall_wrapper_a940)
 * Ghidra: void cl4_r28_359290(void)  (Ghidra FUN_00359290)
 * Calls FUN_0036a940() with no args.
 * Confidence: low
 * Notes: Callee FUN_0036a940 out of slice.
 */
void cl4_r28_359290(void)
{
    FUN_0036a940();
    return;
}

/* FUN_003592a0 @ 0x003592a0   (est. cl4_syscall_noop)
 * Ghidra: void cl4_r28_3592a0(void)  (Ghidra FUN_003592a0)
 * Confidence: low
 * Notes: Empty.
 */
void cl4_r28_3592a0(void)
{ return; }

/* FUN_003592b0 @ 0x003592b0   (est. cl4_syscall_wrapper_b270)
 * Ghidra: void cl4_r28_3592b0(void)  (Ghidra FUN_003592b0)
 * Register-sourced: calls FUN_0036b270 with a transformed mask value
 * (in_w8 & 0xf8 ^ 0x1f8) & (in_w8 + 0x10).
 * Confidence: low
 * Notes: Operand from reg w8 (in_w8).
 */
void cl4_r28_3592b0(void)
{
    FUN_0036b270(((in_w8 & 0xf8u) ^ 0x1f8u) & (in_w8 + 0x10));
    return;
}

/* FUN_003592c8 @ 0x003592c8   (est. cl4_syscall_wrapper_10a74)
 * Ghidra: void cl4_r28_3592c8(void)  (Ghidra FUN_003592c8)
 * Stashes x24 into caller frame x29-0x60, then calls FUN_00310a74() (sched).
 * Confidence: low
 * Notes: Register x24 (unaff) stashed to caller frame.
 */
void cl4_r28_3592c8(void)
{
    *(uint64_t *)(x29_frame - 0x60) = x24;
    FUN_00310a74();
    return;
}

/* FUN_003592d4 @ 0x003592d4   (est. cl4_result_one)
 * Ghidra: cl4_result_t cl4_r28_3592d4(void)  (Ghidra FUN_003592d4)
 * Returns a 128-bit constant 1 (ZEXT816(1)): a (lo=1, hi=0) vector.
 * Confidence: low
 * Notes: Returns ZEXT816(1).
 */
cl4_result_t cl4_r28_3592d4(void)
{
    cl4_result_t r;
    r.lo = 1; r.hi = 0;
    return r;
}

/* FUN_003592f0 @ 0x003592f0   (est. cl4_syscall_wrapper_a261c)
 * Ghidra: void cl4_r28_3592f0(void)  (Ghidra FUN_003592f0)
 * Calls FUN_003a261c(*x20): msg dispatch with the word at caller frame x20.
 * Confidence: low
 * Notes: Arg from caller frame x20 (unaff).
 */
void cl4_r28_3592f0(void)
{
    FUN_003a261c(*x20_ptr);
    return;
}

/* FUN_00359308 @ 0x00359308   (est. cl4_ret_one)
 * Ghidra: uint32_t cl4_r28_359308(void)  (Ghidra FUN_00359308)
 * Returns constant 1.
 * Confidence: low
 * Notes: Trivial.
 */
uint32_t cl4_r28_359308(void)
{
    return 1;
}

/* FUN_00359338 @ 0x00359338   (est. cl4_syscall_wrapper_8f6f4)
 * Ghidra: void cl4_r28_359338(void)  (Ghidra FUN_00359338)
 * Calls FUN_0008f6f4(), a cap helper.
 * Confidence: low
 * Notes: Callee FUN_0008f6f4 out of slice.
 */
void cl4_r28_359338(void)
{
    FUN_0008f6f4();
    return;
}

/* FUN_00359350 @ 0x00359350   (est. cl4_syscall_noop)
 * Ghidra: void cl4_r28_359350(void)  (Ghidra FUN_00359350)
 * Confidence: low
 * Notes: Empty.
 */
void cl4_r28_359350(void)
{ return; }

/* FUN_00359360 @ 0x00359360   (est. cl4_add_base)
 * Ghidra: int64_t cl4_r28_359360(int64_t p_a)  (Ghidra FUN_00359360)
 * Returns x20 + p_a: pointer-offset add thunk (base in x20).
 * Confidence: low
 * Notes: Base in reg x20 (unaff).
 */
int64_t cl4_r28_359360(int64_t p_a)
{
    return x20 + p_a;
}

/* FUN_00359368 @ 0x00359368   (est. cl4_obj_zero_and_call_fb05c)
 * Ghidra: void cl4_r28_359368(int64_t p_obj)  (Ghidra FUN_00359368)
 * Zeroes word at p_obj+0x10, then calls FUN_001fb05c().
 * Confidence: low
 * Notes: Callee FUN_001fb05c out of slice.
 */
void cl4_r28_359368(int64_t p_obj)
{
    *(uint64_t *)(p_obj + 0x10) = 0;
    FUN_001fb05c();
    return;
}

/* FUN_00359380 @ 0x00359380   (est. cl4_syscall_noop)
 * Ghidra: void cl4_r28_359380(void)  (Ghidra FUN_00359380)
 * Confidence: low
 * Notes: Empty.
 */
void cl4_r28_359380(void)
{ return; }

/* FUN_00359388 @ 0x00359388   (est. cl4_syscall_wrapper_85fc)
 * Ghidra: void cl4_r28_359388(void)  (Ghidra FUN_00359388)
 * Calls FUN_002085fc().
 * Confidence: low
 * Notes: Callee FUN_002085fc out of slice.
 */
void cl4_r28_359388(void)
{
    FUN_002085fc();
    return;
}

/* FUN_00359398 @ 0x00359398   (est. cl4_syscall_wrapper_22e4)
 * Ghidra: void cl4_r28_359398(void)  (Ghidra FUN_00359398)
 * Calls FUN_003722e4() with no args.
 * Confidence: low
 * Notes: Callee FUN_003722e4 out of slice.
 */
void cl4_r28_359398(void)
{
    FUN_003722e4();
    return;
}

/* FUN_003593a8 @ 0x003593a8   (est. cl4_syscall_wrapper_a2610)
 * Ghidra: void cl4_r28_3593a8(void)  (Ghidra FUN_003593a8)
 * Calls FUN_003a2610().
 * Confidence: low
 * Notes: Callee FUN_003a2610 out of slice.
 */
void cl4_r28_3593a8(void)
{
    FUN_003a2610();
    return;
}

/* FUN_003593c0 @ 0x003593c0   (est. cl4_fatal_error_string)
 * Ghidra: char *cl4_r28_3593c0(void)  (Ghidra FUN_003593c0)
 * Returns the pointer to the string 'Fatal error' (Ghidra s_Fatal_error_005accd0).
 * Confidence: high
 * Notes: String s_Fatal_error_005accd0 @ 0x5accd0.
 */
char *cl4_r28_3593c0(void)
{
    return s_fatal_error;
}

/* FUN_003593d0 @ 0x003593d0   (est. cl4_syscall_noop)
 * Ghidra: void cl4_r28_3593d0(void)  (Ghidra FUN_003593d0)
 * Confidence: low
 * Notes: Empty.
 */
void cl4_r28_3593d0(void)
{ return; }

/* FUN_003593dc @ 0x003593dc   (est. cl4_ret_const)
 * Ghidra: uint64_t cl4_r28_3593dc(void)  (Ghidra FUN_003593dc)
 * Returns the constant 0x6753a0 (a data/table address constant).
 * Confidence: low
 * Notes: Trivial constant return.
 */
uint64_t cl4_r28_3593dc(void)
{
    return 0x6753a0ull;
}

/* FUN_003593e8 @ 0x003593e8   (est. cl4_syscall_noop)
 * Ghidra: void cl4_r28_3593e8(void)  (Ghidra FUN_003593e8)
 * Confidence: low
 * Notes: Empty.
 */
void cl4_r28_3593e8(void)
{ return; }

/* FUN_003593f4 @ 0x003593f4   (est. cl4_syscall_wrapper_44ca8)
 * Ghidra: void cl4_r28_3593f4(void)  (Ghidra FUN_003593f4)
 * Calls FUN_00344ca8(in_stack_0x68, &stack0x170): IPC helper with a stack
 * word and buffer.
 * Confidence: low
 * Notes: Args from stack (in_stack).
 */
void cl4_r28_3593f4(void)
{
    FUN_00344ca8(stack_word_68, &stack_buf_170);
    return;
}

/* FUN_00359400 @ 0x00359400   (est. cl4_syscall_wrapper_aaf80)
 * Ghidra: void cl4_r28_359400(void)  (Ghidra FUN_00359400)
 * Calls FUN_002aaf80().
 * Confidence: low
 * Notes: Callee FUN_002aaf80 out of slice.
 */
void cl4_r28_359400(void)
{
    FUN_002aaf80();
    return;
}

/* FUN_0035940c @ 0x0035940c   (est. cl4_syscall_wrapper_a89a8)
 * Ghidra: void cl4_r28_35940c(uint64_t p_a)  (Ghidra FUN_0035940c)
 * Calls FUN_001a89a8(p_a, 8, 1).
 * Confidence: low
 * Notes: Callee FUN_001a89a8 out of slice.
 */
void cl4_r28_35940c(uint64_t p_a)
{
    FUN_001a89a8(p_a, 8, 1);
    return;
}

/* FUN_00359418 @ 0x00359418   (est. cl4_syscall_wrapper_c5b0)
 * Ghidra: void cl4_r28_359418(uint64_t p_a)  (Ghidra FUN_00359418)
 * Calls FUN_0020c5b0(p_a, 0).
 * Confidence: low
 * Notes: Callee FUN_0020c5b0 out of slice.
 */
void cl4_r28_359418(uint64_t p_a)
{
    FUN_0020c5b0(p_a, 0);
    return;
}

/* FUN_00359424 @ 0x00359424   (est. cl4_result_pair)
 * Ghidra: cl4_result_t cl4_r28_359424(uint64_t *p_a,uint64_t *p_b)  (Ghidra FUN_00359424)
 * Returns a 128-bit pair {*p_a, *p_b} (lo from first, hi from second).
 * Confidence: low
 * Notes: Returns 16-byte pair.
 */
cl4_result_t cl4_r28_359424(uint64_t *p_a,uint64_t *p_b)
{
    cl4_result_t r;
    r.lo = *p_a;
    r.hi = *p_b;
    return r;
}

/* FUN_00359434 @ 0x00359434   (est. cl4_syscall_wrapper_a9a0)
 * Ghidra: void cl4_r28_359434(void)  (Ghidra FUN_00359434)
 * Calls FUN_0036a9a0().
 * Confidence: low
 * Notes: Callee FUN_0036a9a0 out of slice.
 */
void cl4_r28_359434(void)
{
    FUN_0036a9a0();
    return;
}

/* FUN_00359440 @ 0x00359440   (est. cl4_syscall_wrapper_233c)
 * Ghidra: void cl4_r28_359440(void)  (Ghidra FUN_00359440)
 * Calls FUN_0037233c().
 * Confidence: low
 * Notes: Callee FUN_0037233c out of slice.
 */
void cl4_r28_359440(void)
{
    FUN_0037233c();
    return;
}

/* FUN_0035944c @ 0x0035944c   (est. cl4_syscall_noop)
 * Ghidra: void cl4_r28_35944c(void)  (Ghidra FUN_0035944c)
 * Confidence: low
 * Notes: Empty.
 */
void cl4_r28_35944c(void)
{ return; }

/* FUN_00359460 @ 0x00359460   (est. cl4_frame_store)
 * Ghidra: void cl4_r28_359460(void)  (Ghidra FUN_00359460)
 * Stashes x24 into caller frame x29-0x78.
 * Confidence: low
 * Notes: Register x24 (unaff) to caller frame.
 */
void cl4_r28_359460(void)
{
    *(uint64_t *)(x29_frame - 0x78) = x24;
    return;
}

/* FUN_0035946c @ 0x0035946c   (est. cl4_syscall_noop)
 * Ghidra: void cl4_r28_35946c(void)  (Ghidra FUN_0035946c)
 * Confidence: low
 * Notes: Empty.
 */
void cl4_r28_35946c(void)
{ return; }

/* FUN_00359478 @ 0x00359478   (est. cl4_syscall_noop)
 * Ghidra: void cl4_r28_359478(void)  (Ghidra FUN_00359478)
 * Confidence: low
 * Notes: Empty.
 */
void cl4_r28_359478(void)
{ return; }

/* FUN_00359484 @ 0x00359484   (est. cl4_syscall_noop)
 * Ghidra: void cl4_r28_359484(void)  (Ghidra FUN_00359484)
 * Confidence: low
 * Notes: Empty.
 */
void cl4_r28_359484(void)
{ return; }

/* FUN_00359490 @ 0x00359490   (est. cl4_get_field_18)
 * Ghidra: uint64_t cl4_r28_359490(uint64_t p_a,int64_t p_obj)  (Ghidra FUN_00359490)
 * Returns the word at p_obj+0x18 (a getter).
 * Confidence: low
 * Notes: Simple getter.
 */
uint64_t cl4_r28_359490(uint64_t p_a,int64_t p_obj)
{
    return *(uint64_t *)(p_obj + 0x18);
}

/* FUN_0035949c @ 0x0035949c   (est. cl4_frame_ptr)
 * Ghidra: int64_t cl4_r28_35949c(void)  (Ghidra FUN_0035949c)
 * Returns x29 - 0x70 (a caller-frame pointer thunk).
 * Confidence: low
 * Notes: Frame base in x29.
 */
int64_t cl4_r28_35949c(void)
{
    return x29_frame - 0x70;
}

/* FUN_003594a8 @ 0x003594a8   (est. cl4_syscall_noop)
 * Ghidra: void cl4_r28_3594a8(void)  (Ghidra FUN_003594a8)
 * Confidence: low
 * Notes: Empty.
 */
void cl4_r28_3594a8(void)
{ return; }

/* FUN_003594bc @ 0x003594bc   (est. cl4_syscall_noop)
 * Ghidra: void cl4_r28_3594bc(void)  (Ghidra FUN_003594bc)
 * Confidence: low
 * Notes: Empty.
 */
void cl4_r28_3594bc(void)
{ return; }

/* FUN_003594c8 @ 0x003594c8   (est. cl4_syscall_noop)
 * Ghidra: void cl4_r28_3594c8(void)  (Ghidra FUN_003594c8)
 * Confidence: low
 * Notes: Empty.
 */
void cl4_r28_3594c8(void)
{ return; }

/* FUN_003594d4 @ 0x003594d4   (est. cl4_field_copy_byte)
 * Ghidra: void cl4_r28_3594d4(int64_t p_src)  (Ghidra FUN_003594d4)
 * Copies byte at p_src+0x10 into the byte at x9+0x10 (frame-target store).
 * Confidence: low
 * Notes: Target base in reg x9 (in_x9).
 */
void cl4_r28_3594d4(int64_t p_src)
{
    *(uint8_t *)(x9 + 0x10) = *(uint8_t *)(p_src + 0x10);
    return;
}

/* FUN_003594e0 @ 0x003594e0   (est. cl4_frame_load16)
 * Ghidra: cl4_result_t cl4_r28_3594e0(void)  (Ghidra FUN_003594e0)
 * Returns the 16-byte value at caller frame x29-0x88.
 * Confidence: low
 * Notes: Reads caller frame (unaff_x29).
 */
cl4_result_t cl4_r28_3594e0(void)
{
    cl4_result_t r;
    r.lo = *(uint64_t *)(x29_frame - 0x88);
    r.hi = *(uint64_t *)(x29_frame - 0x80);
    return r;
}

/* FUN_003594f4 @ 0x003594f4   (est. cl4_syscall_noop)
 * Ghidra: void cl4_r28_3594f4(void)  (Ghidra FUN_003594f4)
 * Confidence: low
 * Notes: Empty.
 */
void cl4_r28_3594f4(void)
{ return; }

/* FUN_00359500 @ 0x00359500   (est. cl4_syscall_noop)
 * Ghidra: void cl4_r28_359500(void)  (Ghidra FUN_00359500)
 * Confidence: low
 * Notes: Empty.
 */
void cl4_r28_359500(void)
{ return; }

/* FUN_0035950c @ 0x0035950c   (est. cl4_syscall_noop)
 * Ghidra: void cl4_r28_35950c(void)  (Ghidra FUN_0035950c)
 * Confidence: low
 * Notes: Empty.
 */
void cl4_r28_35950c(void)
{ return; }

/* FUN_00359518 @ 0x00359518   (est. cl4_syscall_noop)
 * Ghidra: void cl4_r28_359518(void)  (Ghidra FUN_00359518)
 * Confidence: low
 * Notes: Empty.
 */
void cl4_r28_359518(void)
{ return; }

/* FUN_00359524 @ 0x00359524   (est. cl4_syscall_noop)
 * Ghidra: void cl4_r28_359524(void)  (Ghidra FUN_00359524)
 * Confidence: low
 * Notes: Empty.
 */
void cl4_r28_359524(void)
{ return; }

/* FUN_00359530 @ 0x00359530   (est. cl4_ret_ff)
 * Ghidra: uint64_t cl4_r28_359530(void)  (Ghidra FUN_00359530)
 * Returns constant 0xff.
 * Confidence: low
 * Notes: Trivial.
 */
uint64_t cl4_r28_359530(void)
{
    return 0xff;
}

/* FUN_0035953c @ 0x0035953c   (est. cl4_syscall_noop)
 * Ghidra: void cl4_r28_35953c(void)  (Ghidra FUN_0035953c)
 * Confidence: low
 * Notes: Empty.
 */
void cl4_r28_35953c(void)
{ return; }

/* FUN_00359550 @ 0x00359550   (est. cl4_syscall_noop)
 * Ghidra: void cl4_r28_359550(void)  (Ghidra FUN_00359550)
 * Confidence: low
 * Notes: Empty.
 */
void cl4_r28_359550(void)
{ return; }

/* FUN_0035955c @ 0x0035955c   (est. cl4_frame_store)
 * Ghidra: void cl4_r28_35955c(void)  (Ghidra FUN_0035955c)
 * Stashes x24 into caller frame x29-0x130.
 * Confidence: low
 * Notes: Register x24 (unaff) to caller frame.
 */
void cl4_r28_35955c(void)
{
    *(uint64_t *)(x29_frame - 0x130) = x24;
    return;
}

/* FUN_00359568 @ 0x00359568   (est. cl4_frame_store)
 * Ghidra: void cl4_r28_359568(void)  (Ghidra FUN_00359568)
 * Stashes x24 into caller frame x29-0x138.
 * Confidence: low
 * Notes: Register x24 (unaff) to caller frame.
 */
void cl4_r28_359568(void)
{
    *(uint64_t *)(x29_frame - 0x138) = x24;
    return;
}

/* FUN_00359574 @ 0x00359574   (est. cl4_syscall_noop)
 * Ghidra: void cl4_r28_359574(void)  (Ghidra FUN_00359574)
 * Confidence: low
 * Notes: Empty.
 */
void cl4_r28_359574(void)
{ return; }

/* FUN_00359588 @ 0x00359588   (est. cl4_and_not_pair)
 * Ghidra: cl4_result_t cl4_r28_359588(void)  (Ghidra FUN_00359588)
 * Register-sourced: returns { x24 & ~x23, x22 & ~x23 } — a bit-clear pair.
 * All operands in regs x22/x23/x24.
 * Confidence: low
 * Notes: Regs x22/x23/x24 (unaff).
 */
cl4_result_t cl4_r28_359588(void)
{
    cl4_result_t r;
    r.lo = x24 & ~x23;
    r.hi = x22 & ~x23;
    return r;
}

/* FUN_00359594 @ 0x00359594   (est. cl4_addr_pair)
 * Ghidra: cl4_result_t cl4_r28_359594(void)  (Ghidra FUN_00359594)
 * Register-sourced: returns { x21 + *(int*)(x26+0x30), x20 + x19 }.
 * Confidence: low
 * Notes: Regs x19/x20/x21/x26 (unaff).
 */
cl4_result_t cl4_r28_359594(void)
{
    cl4_result_t r;
    r.lo = x21 + *(int32_t *)(x26 + 0x30);
    r.hi = x20 + x19;
    return r;
}

/* FUN_003595a8 @ 0x003595a8   (est. cl4_field_offset_add)
 * Ghidra: int64_t cl4_r28_3595a8(void)  (Ghidra FUN_003595a8)
 * Returns x19 + *(int*)(x26+0x30): offset add.
 * Confidence: low
 * Notes: Regs x19/x26 (unaff).
 */
int64_t cl4_r28_3595a8(void)
{
    return x19 + *(int32_t *)(x26 + 0x30);
}

/* FUN_003595b4 @ 0x003595b4   (est. cl4_and_pair)
 * Ghidra: cl4_result_t cl4_r28_3595b4(void)  (Ghidra FUN_003595b4)
 * Register-sourced: returns { x21 & x26, x20 & x26 } — a mask pair.
 * Confidence: low
 * Notes: Regs x20/x21/x26 (unaff).
 */
cl4_result_t cl4_r28_3595b4(void)
{
    cl4_result_t r;
    r.lo = x21 & x26;
    r.hi = x20 & x26;
    return r;
}

/* FUN_003595c0 @ 0x003595c0   (est. cl4_syscall_noop)
 * Ghidra: void cl4_r28_3595c0(void)  (Ghidra FUN_003595c0)
 * Confidence: low
 * Notes: Empty.
 */
void cl4_r28_3595c0(void)
{ return; }

/* FUN_003595d8 @ 0x003595d8   (est. cl4_addr_pair)
 * Ghidra: cl4_result_t cl4_r28_3595d8(int64_t p_a)  (Ghidra FUN_003595d8)
 * Register-sourced: returns { x22 + *(int*)(x19+0x24), x28 + p_a }.
 * Confidence: low
 * Notes: Regs x19/x22/x28 (unaff).
 */
cl4_result_t cl4_r28_3595d8(int64_t p_a)
{
    cl4_result_t r;
    r.lo = x22 + *(int32_t *)(x19 + 0x24);
    r.hi = x28 + p_a;
    return r;
}

/* FUN_00359614 @ 0x00359614   (est. cl4_syscall_noop)
 * Ghidra: void cl4_r28_359614(void)  (Ghidra FUN_00359614)
 * Confidence: low
 * Notes: Empty.
 */
void cl4_r28_359614(void)
{ return; }

/* FUN_00359628 @ 0x00359628   (est. cl4_syscall_noop)
 * Ghidra: void cl4_r28_359628(void)  (Ghidra FUN_00359628)
 * Confidence: low
 * Notes: Empty.
 */
void cl4_r28_359628(void)
{ return; }

/* FUN_00359634 @ 0x00359634   (est. cl4_frame_store)
 * Ghidra: void cl4_r28_359634(void)  (Ghidra FUN_00359634)
 * Stashes x20 into caller frame x29-0x58.
 * Confidence: low
 * Notes: Register x20 (unaff).
 */
void cl4_r28_359634(void)
{
    *(uint64_t *)(x29_frame - 0x58) = x20;
    return;
}

/* FUN_00359640 @ 0x00359640   (est. cl4_syscall_noop)
 * Ghidra: void cl4_r28_359640(void)  (Ghidra FUN_00359640)
 * Confidence: low
 * Notes: Empty.
 */
void cl4_r28_359640(void)
{ return; }

/* FUN_0035964c @ 0x0035964c   (est. cl4_syscall_noop)
 * Ghidra: void cl4_r28_35964c(void)  (Ghidra FUN_0035964c)
 * Confidence: low
 * Notes: Empty.
 */
void cl4_r28_35964c(void)
{ return; }

/* FUN_00359658 @ 0x00359658   (est. cl4_frame_store_byte)
 * Ghidra: void cl4_r28_359658(void)  (Ghidra FUN_00359658)
 * Stashes byte w8 into caller frame x29-0x68.
 * Confidence: low
 * Notes: Register w8 (in_w8).
 */
void cl4_r28_359658(void)
{
    *(uint8_t *)(x29_frame - 0x68) = (uint8_t)in_w8;
    return;
}

/* FUN_0035966c @ 0x0035966c   (est. cl4_frame_load)
 * Ghidra: uint64_t cl4_r28_35966c(void)  (Ghidra FUN_0035966c)
 * Returns the word at caller frame x29-0x88.
 * Confidence: low
 * Notes: Reads caller frame.
 */
uint64_t cl4_r28_35966c(void)
{
    return *(uint64_t *)(x29_frame - 0x88);
}

/* FUN_00359678 @ 0x00359678   (est. cl4_syscall_wrapper_a1dc)
 * Ghidra: void cl4_r28_359678(void)  (Ghidra FUN_00359678)
 * Calls FUN_0031a1dc().
 * Confidence: low
 * Notes: Callee FUN_0031a1dc out of slice.
 */
void cl4_r28_359678(void)
{
    FUN_0031a1dc();
    return;
}

/* FUN_00359690 @ 0x00359690   (est. cl4_field_zero_byte)
 * Ghidra: void cl4_r28_359690(void)  (Ghidra FUN_00359690)
 * Zeroes byte at x20+6.
 * Confidence: low
 * Notes: Base in reg x20 (unaff).
 */
void cl4_r28_359690(void)
{
    *(uint8_t *)(x20 + 6) = 0;
    return;
}

/* FUN_003596a4 @ 0x003596a4   (est. cl4_syscall_noop)
 * Ghidra: void cl4_r28_3596a4(void)  (Ghidra FUN_003596a4)
 * Confidence: low
 * Notes: Empty.
 */
void cl4_r28_3596a4(void)
{ return; }

/* FUN_003596b8 @ 0x003596b8   (est. cl4_frame_load)
 * Ghidra: uint64_t cl4_r28_3596b8(void)  (Ghidra FUN_003596b8)
 * Returns the word at caller frame x29-0x60.
 * Confidence: low
 * Notes: Reads caller frame.
 */
uint64_t cl4_r28_3596b8(void)
{
    return *(uint64_t *)(x29_frame - 0x60);
}

/* FUN_003596c4 @ 0x003596c4   (est. cl4_syscall_noop)
 * Ghidra: void cl4_r28_3596c4(void)  (Ghidra FUN_003596c4)
 * Confidence: low
 * Notes: Empty.
 */
void cl4_r28_3596c4(void)
{ return; }

/* FUN_003596d0 @ 0x003596d0   (est. cl4_load16_ptr)
 * Ghidra: cl4_result_t cl4_r28_3596d0(void)  (Ghidra FUN_003596d0)
 * Returns the 16-byte value pointed to by caller-frame register x20.
 * Confidence: low
 * Notes: Pointer in reg x20 (unaff).
 */
cl4_result_t cl4_r28_3596d0(void)
{
    cl4_result_t r;
    r.lo = ((uint64_t *)x20)[0];
    r.hi = ((uint64_t *)x20)[1];
    return r;
}

/* FUN_003596e4 @ 0x003596e4   (est. cl4_fill_record5)
 * Ghidra: void cl4_r28_3596e4(void)  (Ghidra FUN_003596e4)
 * Fills a 5-word record at caller frame x20 from stack words + registers:
 * [0]=stack0, [1]=stack8, [2]=x22, [3]=x23, [4]=x24.
 * Confidence: low
 * Notes: Stack words (in_stack) + regs x22/x23/x24 (unaff).
 */
void cl4_r28_3596e4(void)
{
    rec_x20[0] = stack_word_0;
    rec_x20[1] = stack_word_8;
    rec_x20[2] = x22;
    rec_x20[3] = x23;
    rec_x20[4] = x24;
    return;
}

/* FUN_003596f8 @ 0x003596f8   (est. cl4_syscall_noop)
 * Ghidra: void cl4_r28_3596f8(void)  (Ghidra FUN_003596f8)
 * Confidence: low
 * Notes: Empty.
 */
void cl4_r28_3596f8(void)
{ return; }

/* FUN_00359704 @ 0x00359704   (est. cl4_table_load16)
 * Ghidra: cl4_result_t cl4_r28_359704(void)  (Ghidra FUN_00359704)
 * Returns the 16-byte value at [*(x24+0x30)] + x23*0x10 — a table element
 * load (element stride 16).
 * Confidence: low
 * Notes: Regs x23/x24 (unaff); stride 0x10.
 */
cl4_result_t cl4_r28_359704(void)
{
    cl4_result_t r;
    uint64_t *tbl = *(uint64_t **)(x24 + 0x30);
    r.lo = tbl[x23*2];
    r.hi = tbl[x23*2 + 1];
    return r;
}

/* FUN_0035972c @ 0x0035972c   (est. cl4_syscall_noop)
 * Ghidra: void cl4_r28_35972c(void)  (Ghidra FUN_0035972c)
 * Confidence: low
 * Notes: Empty.
 */
void cl4_r28_35972c(void)
{ return; }

/* FUN_00359738 @ 0x00359738   (est. cl4_syscall_noop)
 * Ghidra: void cl4_r28_359738(void)  (Ghidra FUN_00359738)
 * Confidence: low
 * Notes: Empty.
 */
void cl4_r28_359738(void)
{ return; }

/* FUN_0035974c @ 0x0035974c   (est. cl4_table_elem_addr)
 * Ghidra: int64_t cl4_r28_35974c(uint64_t p_idx)  (Ghidra FUN_0035974c)
 * Returns *(x19+0x30) + (p_idx | x23<<6)*0x28: table element address
 * (element stride 0x28).
 * Confidence: low
 * Notes: Regs x19/x23 (unaff); stride 0x28.
 */
int64_t cl4_r28_35974c(uint64_t p_idx)
{
    return *(int64_t *)(x19 + 0x30) + ((p_idx | (x23 << 6)) * 0x28);
}

/* FUN_00359760 @ 0x00359760   (est. cl4_syscall_noop)
 * Ghidra: void cl4_r28_359760(void)  (Ghidra FUN_00359760)
 * Confidence: low
 * Notes: Empty.
 */
void cl4_r28_359760(void)
{ return; }

/* FUN_0035976c @ 0x0035976c   (est. cl4_syscall_noop)
 * Ghidra: void cl4_r28_35976c(void)  (Ghidra FUN_0035976c)
 * Confidence: low
 * Notes: Empty.
 */
void cl4_r28_35976c(void)
{ return; }

/* FUN_00359778 @ 0x00359778   (est. cl4_syscall_noop)
 * Ghidra: void cl4_r28_359778(void)  (Ghidra FUN_00359778)
 * Confidence: low
 * Notes: Empty.
 */
void cl4_r28_359778(void)
{ return; }

/* FUN_0035978c @ 0x0035978c   (est. cl4_syscall_noop)
 * Ghidra: void cl4_r28_35978c(void)  (Ghidra FUN_0035978c)
 * Confidence: low
 * Notes: Empty.
 */
void cl4_r28_35978c(void)
{ return; }

/* FUN_003597a0 @ 0x003597a0   (est. cl4_ret_ff)
 * Ghidra: uint64_t cl4_r28_3597a0(void)  (Ghidra FUN_003597a0)
 * Returns constant 0xff.
 * Confidence: low
 * Notes: Trivial.
 */
uint64_t cl4_r28_3597a0(void)
{
    return 0xff;
}

/* FUN_003597b4 @ 0x003597b4   (est. cl4_syscall_noop)
 * Ghidra: void cl4_r28_3597b4(void)  (Ghidra FUN_003597b4)
 * Confidence: low
 * Notes: Empty.
 */
void cl4_r28_3597b4(void)
{ return; }

/* FUN_003597c0 @ 0x003597c0   (est. cl4_syscall_noop)
 * Ghidra: void cl4_r28_3597c0(void)  (Ghidra FUN_003597c0)
 * Confidence: low
 * Notes: Empty.
 */
void cl4_r28_3597c0(void)
{ return; }

/* FUN_003597cc @ 0x003597cc   (est. cl4_copy_record4)
 * Ghidra: void cl4_r28_3597cc(void)  (Ghidra FUN_003597cc)
 * Copies a 4-word record from caller frame x19 to caller frame x20
 * (order [0],[1],[2],[3] -> [0],[1],[2],[3]).
 * Confidence: low
 * Notes: Src/dst in regs x19/x20 (unaff).
 */
void cl4_r28_3597cc(void)
{
    dst_x20[0] = src_x19[0];
    dst_x20[1] = src_x19[1];
    dst_x20[2] = src_x19[2];
    dst_x20[3] = src_x19[3];
    return;
}

/* FUN_003597d8 @ 0x003597d8   (est. cl4_syscall_noop)
 * Ghidra: void cl4_r28_3597d8(void)  (Ghidra FUN_003597d8)
 * Confidence: low
 * Notes: Empty.
 */
void cl4_r28_3597d8(void)
{ return; }

/* FUN_003597e4 @ 0x003597e4   (est. cl4_syscall_noop)
 * Ghidra: void cl4_r28_3597e4(void)  (Ghidra FUN_003597e4)
 * Confidence: low
 * Notes: Empty.
 */
void cl4_r28_3597e4(void)
{ return; }

/* FUN_003597f0 @ 0x003597f0   (est. cl4_syscall_noop)
 * Ghidra: void cl4_r28_3597f0(void)  (Ghidra FUN_003597f0)
 * Confidence: low
 * Notes: Empty.
 */
void cl4_r28_3597f0(void)
{ return; }

/* FUN_00359804 @ 0x00359804   (est. cl4_fill_record4)
 * Ghidra: void cl4_r28_359804(void)  (Ghidra FUN_00359804)
 * Fills a 4-word record at caller frame x20 from stack words 0..18.
 * Confidence: low
 * Notes: Stack words (in_stack).
 */
void cl4_r28_359804(void)
{
    rec_x20[0] = stack_word_0;
    rec_x20[1] = stack_word_8;
    rec_x20[2] = stack_word_10;
    rec_x20[3] = stack_word_18;
    return;
}

/* FUN_00359810 @ 0x00359810   (est. cl4_syscall_noop)
 * Ghidra: void cl4_r28_359810(void)  (Ghidra FUN_00359810)
 * Confidence: low
 * Notes: Empty.
 */
void cl4_r28_359810(void)
{ return; }

/* FUN_0035981c @ 0x0035981c   (est. cl4_syscall_noop)
 * Ghidra: void cl4_r28_35981c(void)  (Ghidra FUN_0035981c)
 * Confidence: low
 * Notes: Empty.
 */
void cl4_r28_35981c(void)
{ return; }

/* FUN_00359828 @ 0x00359828   (est. cl4_syscall_noop)
 * Ghidra: void cl4_r28_359828(void)  (Ghidra FUN_00359828)
 * Confidence: low
 * Notes: Empty.
 */
void cl4_r28_359828(void)
{ return; }

/* FUN_00359834 @ 0x00359834   (est. cl4_frame_load16)
 * Ghidra: cl4_result_t cl4_r28_359834(void)  (Ghidra FUN_00359834)
 * Returns the 16-byte pair { *(x29-400), *(x29-0x168) } from the caller frame.
 * Confidence: low
 * Notes: Reads caller frame.
 */
cl4_result_t cl4_r28_359834(void)
{
    cl4_result_t r;
    r.lo = *(uint64_t *)(x29_frame - 400);
    r.hi = *(uint64_t *)(x29_frame - 0x168);
    return r;
}

/* FUN_00359848 @ 0x00359848   (est. cl4_syscall_noop)
 * Ghidra: void cl4_r28_359848(void)  (Ghidra FUN_00359848)
 * Confidence: low
 * Notes: Empty.
 */
void cl4_r28_359848(void)
{ return; }

/* FUN_0035985c @ 0x0035985c   (est. cl4_frame_load)
 * Ghidra: uint64_t cl4_r28_35985c(void)  (Ghidra FUN_0035985c)
 * Returns the word at caller frame x29-0x1c8.
 * Confidence: low
 * Notes: Reads caller frame.
 */
uint64_t cl4_r28_35985c(void)
{
    return *(uint64_t *)(x29_frame - 0x1c8);
}

/* FUN_00359868 @ 0x00359868   (est. cl4_syscall_noop)
 * Ghidra: void cl4_r28_359868(void)  (Ghidra FUN_00359868)
 * Confidence: low
 * Notes: Empty.
 */
void cl4_r28_359868(void)
{ return; }

/* FUN_00359874 @ 0x00359874   (est. cl4_syscall_noop)
 * Ghidra: void cl4_r28_359874(void)  (Ghidra FUN_00359874)
 * Confidence: low
 * Notes: Empty.
 */
void cl4_r28_359874(void)
{ return; }

/* FUN_00359880 @ 0x00359880   (est. cl4_data_addr_pair)
 * Ghidra: cl4_result_t cl4_r28_359880(void)  (Ghidra FUN_00359880)
 * Returns the 16-byte pair { &DAT_0064c2d8, &DAT_004bbe30 } — two data/table
 * addresses.
 * Confidence: low
 * Notes: Refs DAT_0064c2d8, DAT_004bbe30.
 */
cl4_result_t cl4_r28_359880(void)
{
    cl4_result_t r;
    r.lo = (uint64_t)&DAT_0064c2d8;
    r.hi = (uint64_t)&DAT_004bbe30;
    return r;
}

/* FUN_00359894 @ 0x00359894   (est. cl4_syscall_noop)
 * Ghidra: void cl4_r28_359894(void)  (Ghidra FUN_00359894)
 * Confidence: low
 * Notes: Empty.
 */
void cl4_r28_359894(void)
{ return; }

/* FUN_003598a0 @ 0x003598a0   (est. cl4_syscall_noop)
 * Ghidra: void cl4_r28_3598a0(void)  (Ghidra FUN_003598a0)
 * Confidence: low
 * Notes: Empty.
 */
void cl4_r28_3598a0(void)
{ return; }

/* FUN_003598b4 @ 0x003598b4   (est. cl4_syscall_noop)
 * Ghidra: void cl4_r28_3598b4(void)  (Ghidra FUN_003598b4)
 * Confidence: low
 * Notes: Empty.
 */
void cl4_r28_3598b4(void)
{ return; }

/* FUN_003598c0 @ 0x003598c0   (est. cl4_syscall_noop)
 * Ghidra: void cl4_r28_3598c0(void)  (Ghidra FUN_003598c0)
 * Confidence: low
 * Notes: Empty.
 */
void cl4_r28_3598c0(void)
{ return; }

/* FUN_003598cc @ 0x003598cc   (est. cl4_syscall_noop)
 * Ghidra: void cl4_r28_3598cc(void)  (Ghidra FUN_003598cc)
 * Confidence: low
 * Notes: Empty.
 */
void cl4_r28_3598cc(void)
{ return; }

/* FUN_003598d8 @ 0x003598d8   (est. cl4_frame_load)
 * Ghidra: uint64_t cl4_r28_3598d8(void)  (Ghidra FUN_003598d8)
 * Returns the word at caller frame x29-0x78.
 * Confidence: low
 * Notes: Reads caller frame.
 */
uint64_t cl4_r28_3598d8(void)
{
    return *(uint64_t *)(x29_frame - 0x78);
}

/* FUN_003598ec @ 0x003598ec   (est. cl4_syscall_noop)
 * Ghidra: void cl4_r28_3598ec(void)  (Ghidra FUN_003598ec)
 * Confidence: low
 * Notes: Empty.
 */
void cl4_r28_3598ec(void)
{ return; }

/* FUN_003598f8 @ 0x003598f8   (est. cl4_syscall_noop)
 * Ghidra: void cl4_r28_3598f8(void)  (Ghidra FUN_003598f8)
 * Confidence: low
 * Notes: Empty.
 */
void cl4_r28_3598f8(void)
{ return; }

/* FUN_0035990c @ 0x0035990c   (est. cl4_syscall_ret_zero)
 * Ghidra: uint64_t cl4_r28_35990c(void)  (Ghidra FUN_0035990c)
 * Returns 0 (success).
 * Confidence: low
 * Notes: Trivial.
 */
uint64_t cl4_r28_35990c(void)
{
    return 0;
}

/* FUN_00359920 @ 0x00359920   (est. cl4_syscall_noop)
 * Ghidra: void cl4_r28_359920(void)  (Ghidra FUN_00359920)
 * Confidence: low
 * Notes: Empty.
 */
void cl4_r28_359920(void)
{ return; }

/* FUN_0035992c @ 0x0035992c   (est. cl4_syscall_noop)
 * Ghidra: void cl4_r28_35992c(void)  (Ghidra FUN_0035992c)
 * Confidence: low
 * Notes: Empty.
 */
void cl4_r28_35992c(void)
{ return; }

/* FUN_00359938 @ 0x00359938   (est. cl4_syscall_noop)
 * Ghidra: void cl4_r28_359938(void)  (Ghidra FUN_00359938)
 * Confidence: low
 * Notes: Empty.
 */
void cl4_r28_359938(void)
{ return; }

/* FUN_0035994c @ 0x0035994c   (est. cl4_addr_pair)
 * Ghidra: cl4_result_t cl4_r28_35994c(void)  (Ghidra FUN_0035994c)
 * Returns { x25 + *(int*)(x21+0x50), *(x29-0x90) } — addr+field pair.
 * Confidence: low
 * Notes: Regs x21/x25 + caller frame.
 */
cl4_result_t cl4_r28_35994c(void)
{
    cl4_result_t r;
    r.lo = x25 + *(int32_t *)(x21 + 0x50);
    r.hi = *(uint64_t *)(x29_frame - 0x90);
    return r;
}

/* FUN_00359960 @ 0x00359960   (est. cl4_addr_pair)
 * Ghidra: cl4_result_t cl4_r28_359960(void)  (Ghidra FUN_00359960)
 * Returns { x25 + *(int*)(x21+0x40), *(x29-0xa0) }.
 * Confidence: low
 * Notes: Regs x21/x25 + caller frame.
 */
cl4_result_t cl4_r28_359960(void)
{
    cl4_result_t r;
    r.lo = x25 + *(int32_t *)(x21 + 0x40);
    r.hi = *(uint64_t *)(x29_frame - 0xa0);
    return r;
}

/* FUN_00359974 @ 0x00359974   (est. cl4_syscall_noop)
 * Ghidra: void cl4_r28_359974(void)  (Ghidra FUN_00359974)
 * Confidence: low
 * Notes: Empty.
 */
void cl4_r28_359974(void)
{ return; }

/* FUN_00359988 @ 0x00359988   (est. cl4_mul)
 * Ghidra: int64_t cl4_r28_359988(int64_t p_a,int64_t p_b)  (Ghidra FUN_00359988)
 * Returns p_a * p_b (multiply thunk).
 * Confidence: low
 * Notes: Trivial multiply.
 */
int64_t cl4_r28_359988(int64_t p_a,int64_t p_b)
{
    return p_b * p_a;
}

/* FUN_00359994 @ 0x00359994   (est. cl4_syscall_noop)
 * Ghidra: void cl4_r28_359994(void)  (Ghidra FUN_00359994)
 * Confidence: low
 * Notes: Empty.
 */
void cl4_r28_359994(void)
{ return; }

/* FUN_003599a0 @ 0x003599a0   (est. cl4_syscall_noop)
 * Ghidra: void cl4_r28_3599a0(void)  (Ghidra FUN_003599a0)
 * Confidence: low
 * Notes: Empty.
 */
void cl4_r28_3599a0(void)
{ return; }

/* FUN_003599ac @ 0x003599ac   (est. cl4_addr_pair)
 * Ghidra: cl4_result_t cl4_r28_3599ac(void)  (Ghidra FUN_003599ac)
 * Returns { x24 + *(int*)(x19+0x30), *(x29-0x78) }.
 * Confidence: low
 * Notes: Regs x19/x24 + caller frame.
 */
cl4_result_t cl4_r28_3599ac(void)
{
    cl4_result_t r;
    r.lo = x24 + *(int32_t *)(x19 + 0x30);
    r.hi = *(uint64_t *)(x29_frame - 0x78);
    return r;
}

/* FUN_003599c0 @ 0x003599c0   (est. cl4_syscall_noop)
 * Ghidra: void cl4_r28_3599c0(void)  (Ghidra FUN_003599c0)
 * Confidence: low
 * Notes: Empty.
 */
void cl4_r28_3599c0(void)
{ return; }

/* FUN_003599cc @ 0x003599cc   (est. cl4_syscall_noop)
 * Ghidra: void cl4_r28_3599cc(void)  (Ghidra FUN_003599cc)
 * Confidence: low
 * Notes: Empty.
 */
void cl4_r28_3599cc(void)
{ return; }

/* FUN_003599d8 @ 0x003599d8   (est. cl4_syscall_noop)
 * Ghidra: void cl4_r28_3599d8(void)  (Ghidra FUN_003599d8)
 * Confidence: low
 * Notes: Empty.
 */
void cl4_r28_3599d8(void)
{ return; }

/* FUN_003599e4 @ 0x003599e4   (est. cl4_frame_store2)
 * Ghidra: void cl4_r28_3599e4(void)  (Ghidra FUN_003599e4)
 * Stores x27, x28 into caller frame x29-0x78, x29-0x70.
 * Confidence: low
 * Notes: Regs x27/x28 (unaff).
 */
void cl4_r28_3599e4(void)
{
    *(uint64_t *)(x29_frame - 0x78) = x27;
    *(uint64_t *)(x29_frame - 0x70) = x28;
    return;
}

/* FUN_003599f8 @ 0x003599f8   (est. cl4_frame_store2)
 * Ghidra: void cl4_r28_3599f8(void)  (Ghidra FUN_003599f8)
 * Stores x22, x25 into caller frame x29-0x78, x29-0x70.
 * Confidence: low
 * Notes: Regs x22/x25 (unaff).
 */
void cl4_r28_3599f8(void)
{
    *(uint64_t *)(x29_frame - 0x78) = x22;
    *(uint64_t *)(x29_frame - 0x70) = x25;
    return;
}

/* FUN_00359a04 @ 0x00359a04   (est. cl4_syscall_noop)
 * Ghidra: void cl4_r28_359a04(void)  (Ghidra FUN_00359a04)
 * Confidence: low
 * Notes: Empty.
 */
void cl4_r28_359a04(void)
{ return; }

/* FUN_00359a10 @ 0x00359a10   (est. cl4_syscall_noop)
 * Ghidra: void cl4_r28_359a10(void)  (Ghidra FUN_00359a10)
 * Confidence: low
 * Notes: Empty.
 */
void cl4_r28_359a10(void)
{ return; }

/* FUN_00359a24 @ 0x00359a24   (est. cl4_field_store_2d)
 * Ghidra: void cl4_r28_359a24(void)  (Ghidra FUN_00359a24)
 * Stores the constant 0x2d (45, '-' as a 16-bit word) into caller frame
 * x29-0x5a. Likely initialises a small tag/flag field.
 * Confidence: low
 * Notes: Frame-relative store.
 */
void cl4_r28_359a24(void)
{
    *(uint16_t *)(x29_frame - 0x5a) = 0x2d;
    return;
}

/* FUN_00359a30 @ 0x00359a30   (est. cl4_syscall_noop)
 * Ghidra: void cl4_r28_359a30(void)  (Ghidra FUN_00359a30)
 * Confidence: low
 * Notes: Empty.
 */
void cl4_r28_359a30(void)
{ return; }

/* FUN_00359a3c @ 0x00359a3c   (est. cl4_syscall_noop)
 * Ghidra: void cl4_r28_359a3c(void)  (Ghidra FUN_00359a3c)
 * Confidence: low
 * Notes: Empty.
 */
void cl4_r28_359a3c(void)
{ return; }

/* FUN_00359a48 @ 0x00359a48   (est. cl4_syscall_noop)
 * Ghidra: void cl4_r28_359a48(void)  (Ghidra FUN_00359a48)
 * Confidence: low
 * Notes: Empty.
 */
void cl4_r28_359a48(void)
{ return; }

/* FUN_00359a54 @ 0x00359a54   (est. cl4_syscall_noop)
 * Ghidra: void cl4_r28_359a54(void)  (Ghidra FUN_00359a54)
 * Confidence: low
 * Notes: Empty.
 */
void cl4_r28_359a54(void)
{ return; }

/* FUN_00359a60 @ 0x00359a60   (est. cl4_syscall_noop)
 * Ghidra: void cl4_r28_359a60(void)  (Ghidra FUN_00359a60)
 * Confidence: low
 * Notes: Empty.
 */
void cl4_r28_359a60(void)
{ return; }

/* FUN_00359a6c @ 0x00359a6c   (est. cl4_syscall_noop)
 * Ghidra: void cl4_r28_359a6c(void)  (Ghidra FUN_00359a6c)
 * Confidence: low
 * Notes: Empty.
 */
void cl4_r28_359a6c(void)
{ return; }

/* FUN_00359a78 @ 0x00359a78   (est. cl4_syscall_noop)
 * Ghidra: void cl4_r28_359a78(void)  (Ghidra FUN_00359a78)
 * Confidence: low
 * Notes: Empty.
 */
void cl4_r28_359a78(void)
{ return; }

/* FUN_00359a84 @ 0x00359a84   (est. cl4_syscall_noop)
 * Ghidra: void cl4_r28_359a84(void)  (Ghidra FUN_00359a84)
 * Confidence: low
 * Notes: Empty.
 */
void cl4_r28_359a84(void)
{ return; }

/* FUN_00359a90 @ 0x00359a90   (est. cl4_const_pair)
 * Ghidra: cl4_result_t cl4_r28_359a90(void)  (Ghidra FUN_00359a90)
 * Returns { 1, &stack0x20 } — a (lo=1, hi=stack-addr) constant pair.
 * Confidence: low
 * Notes: hi is &stack0x20.
 */
cl4_result_t cl4_r28_359a90(void)
{
    cl4_result_t r;
    r.lo = 1;
    r.hi = (uint64_t)&stack_slot_20;
    return r;
}

/* FUN_00359aa4 @ 0x00359aa4   (est. cl4_syscall_noop)
 * Ghidra: void cl4_r28_359aa4(void)  (Ghidra FUN_00359aa4)
 * Confidence: low
 * Notes: Empty.
 */
void cl4_r28_359aa4(void)
{ return; }

/* FUN_00359ab0 @ 0x00359ab0   (est. cl4_data_addr)
 * Ghidra: uint8_t *cl4_r28_359ab0(void)  (Ghidra FUN_00359ab0)
 * Returns the address of data symbol DAT_005d3566.
 * Confidence: low
 * Notes: Refs DAT_005d3566 @ 0x5d3566.
 */
uint8_t *cl4_r28_359ab0(void)
{
    return &DAT_005d3566[0];
}

/* FUN_00359abc @ 0x00359abc   (est. cl4_syscall_noop)
 * Ghidra: void cl4_r28_359abc(void)  (Ghidra FUN_00359abc)
 * Confidence: low
 * Notes: Empty.
 */
void cl4_r28_359abc(void)
{ return; }

/* FUN_00359ac8 @ 0x00359ac8   (est. cl4_syscall_noop)
 * Ghidra: void cl4_r28_359ac8(void)  (Ghidra FUN_00359ac8)
 * Confidence: low
 * Notes: Empty.
 */
void cl4_r28_359ac8(void)
{ return; }

/* FUN_00359ad4 @ 0x00359ad4   (est. cl4_frame_load)
 * Ghidra: uint64_t cl4_r28_359ad4(void)  (Ghidra FUN_00359ad4)
 * Returns the word at caller frame x29-0x110.
 * Confidence: low
 * Notes: Reads caller frame.
 */
uint64_t cl4_r28_359ad4(void)
{
    return *(uint64_t *)(x29_frame - 0x110);
}

/* FUN_00359ae0 @ 0x00359ae0   (est. cl4_syscall_noop)
 * Ghidra: void cl4_r28_359ae0(void)  (Ghidra FUN_00359ae0)
 * Confidence: low
 * Notes: Empty.
 */
void cl4_r28_359ae0(void)
{ return; }

/* FUN_00359aec @ 0x00359aec   (est. cl4_store_sign_bit)
 * Ghidra: void cl4_r28_359aec(void)  (Ghidra FUN_00359aec)
 * Stores the sign-bit sentinel 0x8000000000000000 into the word at x20
 * (caller-frame pointer). A flag/tag initialiser.
 * Confidence: low
 * Notes: Stores 1<<63.
 */
void cl4_r28_359aec(void)
{
    *x20_ptr = 0x8000000000000000ull;
    return;
}

/* FUN_00359af8 @ 0x00359af8   (est. cl4_syscall_noop)
 * Ghidra: void cl4_r28_359af8(void)  (Ghidra FUN_00359af8)
 * Confidence: low
 * Notes: Empty.
 */
void cl4_r28_359af8(void)
{ return; }

/* FUN_00359b0c @ 0x00359b0c   (est. cl4_frame_load16)
 * Ghidra: cl4_result_t cl4_r28_359b0c(void)  (Ghidra FUN_00359b0c)
 * Returns the 16-byte value at caller frame x29+0x10.
 * Confidence: low
 * Notes: Reads caller frame.
 */
cl4_result_t cl4_r28_359b0c(void)
{
    cl4_result_t r;
    r.lo = *(uint64_t *)(x29_frame + 0x10);
    r.hi = *(uint64_t *)(x29_frame + 0x18);
    return r;
}

/* FUN_00359b18 @ 0x00359b18   (est. cl4_syscall_noop)
 * Ghidra: void cl4_r28_359b18(void)  (Ghidra FUN_00359b18)
 * Confidence: low
 * Notes: Empty.
 */
void cl4_r28_359b18(void)
{ return; }

/* FUN_00359b24 @ 0x00359b24   (est. cl4_syscall_noop)
 * Ghidra: void cl4_r28_359b24(void)  (Ghidra FUN_00359b24)
 * Confidence: low
 * Notes: Empty.
 */
void cl4_r28_359b24(void)
{ return; }

/* FUN_00359b30 @ 0x00359b30   (est. cl4_syscall_noop)
 * Ghidra: void cl4_r28_359b30(void)  (Ghidra FUN_00359b30)
 * Confidence: low
 * Notes: Empty.
 */
void cl4_r28_359b30(void)
{ return; }

/* FUN_00359b3c @ 0x00359b3c   (est. cl4_fill_record6)
 * Ghidra: void cl4_r28_359b3c(void)  (Ghidra FUN_00359b3c)
 * Fills a 6-word record at caller frame x21:
 * [0]=x19, [1]=x20, byte[2]=w22, [3]=x23, [4]=x24, byte[5]=w8.
 * Confidence: low
 * Notes: Regs x19/x20/x23/x24/w22/w8 (unaff).
 */
void cl4_r28_359b3c(void)
{
    rec_x21[0] = x19;
    rec_x21[1] = x20;
    *(uint8_t *)&rec_x21[2] = (uint8_t)w22;
    rec_x21[3] = x23;
    rec_x21[4] = x24;
    *(uint8_t *)&rec_x21[5] = (uint8_t)in_w8;
    return;
}

/* FUN_00359b50 @ 0x00359b50   (est. cl4_field_copy_3840)
 * Ghidra: void cl4_r28_359b50(void)  (Ghidra FUN_00359b50)
 * Copies a 8-byte word at x19+0x38 and a byte at x19+0x40 into x20+0x38 and
 * x20+0x40 (struct field copy).
 * Confidence: low
 * Notes: Src/dst in regs x19/x20 (unaff).
 */
void cl4_r28_359b50(void)
{
    *(uint64_t *)(x20 + 0x38) = *(uint64_t *)(x19 + 0x38);
    *(uint8_t *)(x20 + 0x40) = *(uint8_t *)(x19 + 0x40);
    return;
}

/* FUN_00359b64 @ 0x00359b64   (est. cl4_syscall_noop)
 * Ghidra: void cl4_r28_359b64(void)  (Ghidra FUN_00359b64)
 * Confidence: low
 * Notes: Empty.
 */
void cl4_r28_359b64(void)
{ return; }

/* FUN_00359b70 @ 0x00359b70   (est. cl4_inc)
 * Ghidra: int64_t cl4_r28_359b70(void)  (Ghidra FUN_00359b70)
 * Returns in_x10 + 1 (increment thunk; operand in register x10).
 * Confidence: low
 * Notes: Operand in reg x10 (in_x10).
 */
int64_t cl4_r28_359b70(void)
{
    return x10 + 1;
}

/* FUN_00359b90 @ 0x00359b90   (est. cl4_syscall_noop)
 * Ghidra: void cl4_r28_359b90(void)  (Ghidra FUN_00359b90)
 * Confidence: low
 * Notes: Empty.
 */
void cl4_r28_359b90(void)
{ return; }

/* FUN_00359ba4 @ 0x00359ba4   (est. cl4_syscall_wrapper_b560)
 * Ghidra: void cl4_r28_359ba4(void)  (Ghidra FUN_00359ba4)
 * Calls FUN_0031b560().
 * Confidence: low
 * Notes: Callee FUN_0031b560 out of slice.
 */
void cl4_r28_359ba4(void)
{
    FUN_0031b560();
    return;
}

/* FUN_00359bbc @ 0x00359bbc   (est. cl4_syscall_noop)
 * Ghidra: void cl4_r28_359bbc(void)  (Ghidra FUN_00359bbc)
 * Confidence: low
 * Notes: Empty.
 */
void cl4_r28_359bbc(void)
{ return; }

/* FUN_00359bc8 @ 0x00359bc8   (est. cl4_syscall_noop)
 * Ghidra: void cl4_r28_359bc8(void)  (Ghidra FUN_00359bc8)
 * Confidence: low
 * Notes: Empty.
 */
void cl4_r28_359bc8(void)
{ return; }

/* FUN_00359bd4 @ 0x00359bd4   (est. cl4_store_range_pair)
 * Ghidra: void cl4_r28_359bd4(int64_t p_a)  (Ghidra FUN_00359bd4)
 * Stores { p_a, p_a + x9 } into a caller-frame pair (x20): a base and
 * end pointer pair (range descriptor).
 * Confidence: low
 * Notes: Offset in reg x9 (in_x9).
 */
void cl4_r28_359bd4(int64_t p_a)
{
    pair_x20[0] = p_a;
    pair_x20[1] = p_a + x9;
    return;
}

/* FUN_00359be0 @ 0x00359be0   (est. cl4_syscall_noop)
 * Ghidra: void cl4_r28_359be0(void)  (Ghidra FUN_00359be0)
 * Confidence: low
 * Notes: Empty.
 */
void cl4_r28_359be0(void)
{ return; }

/* FUN_00359bec @ 0x00359bec   (est. cl4_frame_store)
 * Ghidra: void cl4_r28_359bec(void)  (Ghidra FUN_00359bec)
 * Stashes x20 into caller frame x29-0x58.
 * Confidence: low
 * Notes: Register x20 (unaff).
 */
void cl4_r28_359bec(void)
{
    *(uint64_t *)(x29_frame - 0x58) = x20;
    return;
}

/* FUN_00359bf8 @ 0x00359bf8   (est. cl4_merge_record6)
 * Ghidra: void cl4_r28_359bf8(uint8_t a[16],uint8_t b[16])  (Ghidra FUN_00359bf8)
 * Fills a 6-word record at caller frame x19 from two 16-byte inputs plus
 * byte regs w8/w9:
 * [0]=a.lo, [1]=a.hi, byte[2]=w9, [3]=b.lo, [4]=b.hi, byte[5]=w8.
 * Confidence: low
 * Notes: Byte regs w8/w9 (in_w8/in_w9); record at x19.
 */
void cl4_r28_359bf8(uint8_t a[16],uint8_t b[16])
{
    rec_x19[0] = ((uint64_t *)a)[0];
    rec_x19[1] = ((uint64_t *)a)[1];
    *(uint8_t *)&rec_x19[2] = (uint8_t)in_w9;
    rec_x19[3] = ((uint64_t *)b)[0];
    rec_x19[4] = ((uint64_t *)b)[1];
    *(uint8_t *)&rec_x19[5] = (uint8_t)in_w8;
    return;
}

/* FUN_00359c0c @ 0x00359c0c   (est. cl4_addr_pair)
 * Ghidra: cl4_result_t cl4_r28_359c0c(int64_t p_a)  (Ghidra FUN_00359c0c)
 * Returns { x19 + x9, x22 + p_a } — two address sums.
 * Confidence: low
 * Notes: Regs x9/x19/x22 (in/unaff).
 */
cl4_result_t cl4_r28_359c0c(int64_t p_a)
{
    cl4_result_t r;
    r.lo = x19 + x9;
    r.hi = x22 + p_a;
    return r;
}

/* FUN_00359c18 @ 0x00359c18   (est. cl4_syscall_noop)
 * Ghidra: void cl4_r28_359c18(void)  (Ghidra FUN_00359c18)
 * Confidence: low
 * Notes: Empty.
 */
void cl4_r28_359c18(void)
{ return; }

/* FUN_00359c2c @ 0x00359c2c   (est. cl4_syscall_noop)
 * Ghidra: void cl4_r28_359c2c(void)  (Ghidra FUN_00359c2c)
 * Confidence: low
 * Notes: Empty.
 */
void cl4_r28_359c2c(void)
{ return; }

/* FUN_00359c40 @ 0x00359c40   (est. cl4_store_pair)
 * Ghidra: void cl4_r28_359c40(uint64_t p_a,uint64_t p_b)  (Ghidra FUN_00359c40)
 * Stores { p_a, p_b } into a caller-frame pair (x19).
 * Confidence: low
 * Notes: Pair at caller frame x19 (unaff).
 */
void cl4_r28_359c40(uint64_t p_a,uint64_t p_b)
{
    pair_x19[0] = p_a;
    pair_x19[1] = p_b;
    return;
}

/* FUN_00359c4c @ 0x00359c4c   (est. cl4_store_triple)
 * Ghidra: void cl4_r28_359c4c(uint64_t p_a,uint64_t p_b,uint64_t p_c)  (Ghidra FUN_00359c4c)
 * Stores { p_a, p_b, p_c } into a caller-frame triple (x19).
 * Confidence: low
 * Notes: Triple at caller frame x19 (unaff).
 */
void cl4_r28_359c4c(uint64_t p_a,uint64_t p_b,uint64_t p_c)
{
    trip_x19[0] = p_a;
    trip_x19[1] = p_b;
    trip_x19[2] = p_c;
    return;
}

/* FUN_00359c58 @ 0x00359c58   (est. cl4_syscall_noop)
 * Ghidra: void cl4_r28_359c58(void)  (Ghidra FUN_00359c58)
 * Confidence: low
 * Notes: Empty.
 */
void cl4_r28_359c58(void)
{ return; }

/* FUN_00359c64 @ 0x00359c64   (est. cl4_syscall_noop)
 * Ghidra: void cl4_r28_359c64(void)  (Ghidra FUN_00359c64)
 * Confidence: low
 * Notes: Empty.
 */
void cl4_r28_359c64(void)
{ return; }

/* FUN_00359c70 @ 0x00359c70   (est. cl4_indexed_addr)
 * Ghidra: int64_t cl4_r28_359c70(int64_t p_a)  (Ghidra FUN_00359c70)
 * Returns x9 + p_a + *(x10+0x48)*x20: an indexed address computation.
 * (base x9 + param + element_size(x10+0x48) * index x20).
 * Confidence: low
 * Notes: Regs x9/x10/x20 (in/unaff).
 */
int64_t cl4_r28_359c70(int64_t p_a)
{
    return x9 + p_a + (*(int64_t *)(x10 + 0x48) * x20);
}

/* FUN_00359c84 @ 0x00359c84   (est. cl4_syscall_noop)
 * Ghidra: void cl4_r28_359c84(void)  (Ghidra FUN_00359c84)
 * Confidence: low
 * Notes: Empty.
 */
void cl4_r28_359c84(void)
{ return; }

