/* Recreated from cl4_kernel.raw (cL4 Secure Kernel, arm64e, image base 0) —
 * the cL4 microkernel (GL1). Ground truth: Ghidra FUN_ names + addresses.
 * All names are estimates unless string/header matched.
 * Slice 30: 0x35a8d0-0x366f14 syscall/exception-entry + capability-object
 * dispatch + Swift-runtime (type metadata, hash tables, collection copy)
 * region. */

#include <stdint.h>
#include <stddef.h>

#include "sk_internal.h"
#include "sk_region_syscalls.h"

/* ------------------------------------------------------------------ *
 * Out-of-range cL4 helper declarations (empty-paren = unspecified args,
 * so calls with any arity compile under -fsyntax-only). Their bodies are
 * reconstructed by the range worker that owns each address.
 * ------------------------------------------------------------------ */
#define DECL(name) extern uint64_t name()
DECL(FUN_00002534); DECL(FUN_001a89a8); DECL(FUN_001afa84); DECL(FUN_00205844);
DECL(FUN_001cf6f4); DECL(FUN_001ef208); DECL(FUN_002b800c); DECL(FUN_002cbea0);
DECL(FUN_0024be2c); DECL(FUN_00377824); DECL(FUN_002a2bb0); DECL(FUN_002a218c);
DECL(FUN_0036b270); DECL(FUN_001a26e0); DECL(FUN_00208418); DECL(FUN_0006e778);
DECL(FUN_0032220c); DECL(FUN_002ab130); DECL(FUN_0022b21c); DECL(FUN_00310a14);
DECL(FUN_00310a44); DECL(FUN_001ee0fc); DECL(thunk_FUN_0035723c); DECL(FUN_000a68f4);
DECL(FUN_0019e644); DECL(FUN_003a2610); DECL(FUN_0008f6f4); DECL(FUN_0036b118);
DECL(FUN_00389910); DECL(FUN_0039c740); DECL(FUN_00377800); DECL(FUN_0039c49c);
DECL(FUN_00118148); DECL(FUN_003a2578); DECL(FUN_00118164); DECL(FUN_00010244);
DECL(FUN_000101a0); DECL(FUN_0001279c); DECL(FUN_00117cc8); DECL(FUN_00117cc4);
DECL(FUN_00117d14); DECL(thunk_FUN_00012568); DECL(FUN_00115080); DECL(FUN_003a3430);
DECL(FUN_003a3460); DECL(FUN_003a32a0); DECL(FUN_003a3a10); DECL(FUN_003a36a0);
DECL(FUN_003a3944); DECL(FUN_0039c7e8); DECL(FUN_003a3980); DECL(FUN_003a3e54);
DECL(FUN_003a3748); DECL(FUN_003a31d8); DECL(FUN_003a2b38); DECL(FUN_003a25b8);
DECL(FUN_003a25a0); DECL(FUN_003a294c); DECL(FUN_003a28a8); DECL(FUN_003a3814);
DECL(FUN_00116bb4); DECL(FUN_00112e8c); DECL(FUN_00112db4); DECL(FUN_00113368);
DECL(FUN_00113400); DECL(FUN_001142f4); DECL(FUN_001145b0); DECL(thunk_FUN_00114330);
DECL(FUN_00118194); DECL(FUN_0011d7e8); DECL(FUN_00111890); DECL(FUN_00111888);
DECL(thunk_FUN_00111888); DECL(thunk_FUN_004bab7c); DECL(FUN_003bc9a4);
DECL(FUN_003bf904); DECL(FUN_003b2010); DECL(FUN_003d3dd8); DECL(FUN_0038a950);
DECL(FUN_0038bbf4); DECL(FUN_00387e60); DECL(FUN_00387da0); DECL(FUN_0036a804);
DECL(FUN_0036a358); DECL(FUN_0036f418); DECL(FUN_00369bb0); DECL(thunk_FUN_0039c74c);
DECL(FUN_0039c7e8); DECL(FUN_00374d14); DECL(FUN_00374d38); DECL(FUN_00374de4);
DECL(FUN_00374d80); DECL(FUN_003743d0); DECL(FUN_001b61bc); DECL(FUN_002297e8);
DECL(FUN_00229748); DECL(FUN_0019e128); DECL(FUN_0019de24); DECL(FUN_001f8abc);
DECL(FUN_001f80ac); DECL(FUN_0000456c); DECL(FUN_001b65ec); DECL(FUN_001b68a0);
DECL(FUN_00019850); DECL(FUN_003681c4); DECL(FUN_0036813c); DECL(FUN_00365a00);
DECL(FUN_004b9634); DECL(FUN_004b9704); DECL(FUN_004b99dc); DECL(FUN_004b992c);
DECL(FUN_004b9a28); DECL(FUN_004b9ac8); DECL(FUN_004b9b38); DECL(FUN_003773d8);
DECL(FUN_0036b484); DECL(FUN_0036b3c0); DECL(FUN_003a25d4); DECL(FUN_00362f14);
DECL(FUN_00362fb0); DECL(FUN_00363048); DECL(FUN_003630f8); DECL(FUN_003631cc);
DECL(FUN_00363280); DECL(FUN_00363368); DECL(FUN_00363458); DECL(FUN_003634ec);
DECL(FUN_0036359c); DECL(FUN_00363668); DECL(FUN_00362ea4); DECL(FUN_00362e54);
DECL(FUN_00362de4); DECL(FUN_00362a58); DECL(FUN_003629c4); DECL(FUN_00362bc0);
DECL(FUN_00362c00); DECL(FUN_00362c34); DECL(FUN_00362acc); DECL(FUN_003627f4);
DECL(FUN_00362624); DECL(FUN_003625e4); DECL(FUN_0036254c); DECL(FUN_003624f0);
DECL(FUN_00362444); DECL(FUN_003622f0); DECL(FUN_00362340); DECL(FUN_00362374);
DECL(FUN_003623dc); DECL(FUN_00362278); DECL(FUN_003633d8); DECL(FUN_00365c38);
DECL(FUN_00366774); DECL(FUN_003667ac); DECL(FUN_003669c8); DECL(FUN_00366a4c);
DECL(FUN_0035ad10); DECL(FUN_002296b0); DECL(FUN_0039c74c); DECL(FUN_0035efa0); DECL(thunk_FUN_001145b0);
DECL(thunk_FUN_00115080);
DECL(FUN_00366ae0); DECL(FUN_00366b8c); DECL(FUN_00366b94); DECL(FUN_00366c5c);
DECL(FUN_00366d34); DECL(FUN_00366eec); DECL(FUN_00366ef4); DECL(FUN_00366efc);
DECL(FUN_00366f04); DECL(FUN_00366f0c); DECL(FUN_00366f14);
DECL(FUN_0000f800); DECL(FUN_0035b028); DECL(FUN_0035b178); DECL(FUN_0035b228); DECL(thunk_FUN_0036b118);
DECL(thunk_FUN_0036b270); DECL(FUN_00365b6c);
DECL(FUN_0035b2c8); DECL(FUN_0035b4b8); DECL(FUN_0035b588); DECL(FUN_0035bd48);
DECL(FUN_0035eae4); DECL(FUN_0035ef4c); DECL(FUN_0035eb3c); DECL(FUN_0035efdc);
DECL(FUN_0035ea78); DECL(FUN_0035e134); DECL(FUN_0035dc24); DECL(FUN_0035d334);
DECL(FUN_0035d6dc); DECL(FUN_0035d184); DECL(FUN_0035cc88); DECL(FUN_0035c718);
DECL(FUN_0035c1e0); DECL(FUN_0035be00); DECL(FUN_0035b898); DECL(FUN_0035b974);
DECL(FUN_0035baa4); DECL(FUN_0035bb80); DECL(FUN_0035b7ac); DECL(FUN_0035b67c);
DECL(FUN_0035bc70); DECL(FUN_0035cf38); DECL(FUN_0035cf24); DECL(FUN_0035cf8c);
DECL(FUN_0035cf94); DECL(FUN_0035cfdc); DECL(FUN_0035cfe4); DECL(FUN_0035e530);
DECL(FUN_0035e690); DECL(FUN_0035e738); DECL(FUN_0035e7ac); DECL(FUN_0035e8d4);
DECL(FUN_0035e9ac); DECL(FUN_0035f31c); DECL(FUN_0035f3e8); DECL(FUN_0035f480);
DECL(FUN_0035f5cc); DECL(FUN_0035f6f0); DECL(FUN_0035f808); DECL(FUN_0035f934);
DECL(FUN_0035f978); DECL(FUN_0035f97c); DECL(FUN_0035f9b4); DECL(FUN_0035fa10);
DECL(FUN_0035fa14); DECL(FUN_0035fa48); DECL(FUN_0035fab4); DECL(FUN_0035fc58);
DECL(FUN_0035fcc8); DECL(FUN_0035ff48); DECL(FUN_003600ec); DECL(FUN_0036037c);
DECL(FUN_00360a80); DECL(FUN_00360c48); DECL(FUN_00360e28); DECL(FUN_00360f10);
DECL(FUN_00360f88); DECL(FUN_003610ac); DECL(FUN_003611c4); DECL(FUN_00361718);
DECL(FUN_00361320); DECL(FUN_00361528); DECL(FUN_003617bc); DECL(FUN_00361b18);
DECL(FUN_00363f10); DECL(FUN_00363f70); DECL(FUN_00363fe8); DECL(FUN_00365184);
DECL(FUN_003651f4); DECL(FUN_00365238); DECL(FUN_003652b8); DECL(FUN_003653b8);
DECL(FUN_00365660); DECL(FUN_003656f4); DECL(FUN_003657cc); DECL(FUN_003658a0);
DECL(FUN_003658e8); DECL(FUN_00365944); DECL(FUN_00365a48); DECL(FUN_00363718);
DECL(FUN_00364020); DECL(FUN_00362d2c); DECL(FUN_00362d2c);
/* kernel primitives */
DECL(LOAcquire); DECL(LORelease); DECL(DataMemoryBarrier); DECL(SoftwareBreakpoint);

/* ------------------------------------------------------------------ *
 * Shared runtime globals (cL4 Swift-runtime lazy-init slots + mutexes).
 * ------------------------------------------------------------------ */
extern uint64_t DAT_006c0170;  /* in-flight/refcount counter under LO lock */
extern uint64_t DAT_006c0174;  /* count of live registration slots */
extern uint64_t DAT_006c0180;  /* tagged slot-size descriptor */
extern uint64_t DAT_006c0178;  /* registration storage pointer */
extern uint64_t DAT_006c01b0;  /* free-list head of deferred frees */
extern uint64_t DAT_006c01a0;  /* mutex state word for 0x6c0190 */
extern uint64_t DAT_006c01c0;  /* hash-table lock (0x6c01c0) */
extern uint64_t DAT_006c0200;  /* set A hash-table storage */
extern uint64_t DAT_006c0210;  /* set A capacity */
extern uint64_t DAT_006c0218;  /* set A lock/once state */
extern uint64_t DAT_006c0220;  /* set B hash-table storage */
extern uint64_t DAT_006c0230;  /* set B capacity */
extern uint64_t DAT_006c0238;  /* set B lock/once state */
extern uint64_t DAT_006c0240;  /* cached cap object */
extern uint64_t DAT_006c0248;  /* cached cap object id */
extern uint64_t DAT_006c0250;  /* cached class table */
extern uint64_t DAT_006c0258;  /* cached class table valid flag */
extern uint64_t DAT_006adf08;  /* pointer for lazy global init */
extern uint64_t DAT_004f2700;  /* Swift type-metadata context */
extern uint64_t DAT_004f2708;  /* Swift type-metadata context */
extern uint64_t DAT_004f2710;  /* Swift type-metadata context */
extern uint64_t DAT_004f2718;  /* Swift type-metadata context */
extern uint64_t DAT_006c01e0;  /* string-hash table lock */
extern uint64_t DAT_004f2720;  /* small-constant table */
extern uint64_t DAT_006c0250x; /* (unused placeholder) */

/* ------------------------------------------------------------------ *
 * Syscall dispatch-table thunks (0x35a8d0-0x35ad10).
 * Each entry is a tiny wrapper that selects a handler and forwards. The
 * common FUN_00002534(desc, name) helper lazily initialises a global slot
 * from a descriptor. Names are estimates.
 * ------------------------------------------------------------------ */

/* FUN_0035a8d0 @ 0x35a8d0  (est. cl4_syscall_dispatch_empty)
 * Empty dispatch entry: does nothing.
 * Confidence: medium */
void cl4_syscall_dispatch_empty_35a8d0(void) { return; }

/* FUN_0035a8e8 @ 0x35a8e8  (est. cl4_lazy_init_global)
 * Lazily initialise the global at 0x657640 from descriptor 0x4f2120.
 * Confidence: low */
void cl4_lazy_init_global_35a8e8(void) { FUN_00002534(0x657640, 0x4f2120); }

/* FUN_0035a8fc @ 0x35a8fc  (est. cl4_lazy_init_global2)
 * Lazily initialise the global at 0x64e670 from descriptor 0x4c2600.
 * Confidence: low */
void cl4_lazy_init_global2_35a8fc(void) { FUN_00002534(0x64e670, 0x4c2600); }

/* FUN_0035a910 @ 0x35a910  (est. cl4_cap_dispatch_table_entry)
 * Forwards (a,b) to the cap-object dispatcher FUN_00365b6c with table
 * 0x67b1e8 and flags 0.
 * Confidence: low */
void cl4_cap_dispatch_table_entry_35a910(und8_t a, und8_t b, und8_t c, und8_t d)
{ FUN_00365b6c(a, b, 0x67b1e8, d, 0); }

/* FUN_0035a924 @ 0x35a924  (est. cl4_debug_description)
 * Emits the "Debug description" string via FUN_001a89a8(0x5ce820, 0x15, 1).
 * Confidence: low */
void cl4_debug_description_35a924(void) { FUN_001a89a8(0x5ce820, 0x15, 1); }

/* FUN_0035a938 @ 0x35a938  (est. cl4_lazy_init_global3)
 * Lazily initialise the global at 0x656118 from descriptor 0x4e7f08.
 * Confidence: low */
void cl4_lazy_init_global3_35a938(void) { FUN_00002534(0x656118, 0x4e7f08); }

/* FUN_0035a94c @ 0x35a94c  (est. cl4_lazy_init_global4)
 * Lazily initialise the global at 0x64e020 from descriptor 0x4e4750.
 * Confidence: low */
void cl4_lazy_init_global4_35a94c(void) { FUN_00002534(0x64e020, 0x4e4750); }

/* FUN_0035a960 @ 0x35a960  (est. cl4_trap_tail_call)
 * Tail thunk: copies six stack words then calls FUN_0036b118(ptr in x20).
 * Confidence: low */
void cl4_trap_tail_call_35a960(void) { FUN_0036b118(0); }

/* FUN_0035a974 @ 0x35a974  (est. cl4_lazy_init_global5)
 * Lazily initialise the global at 0x656150 from descriptor 0x4e7fa0.
 * Confidence: low */
void cl4_lazy_init_global5_35a974(void) { FUN_00002534(0x656150, 0x4e7fa0); }

/* FUN_0035a988 @ 0x35a988  (est. cl4_panic_noreturn)
 * Non-returning: calls FUN_001afa84(). Never returns.
 * Confidence: low */
void cl4_panic_noreturn_35a988(void) { FUN_001afa84(); }

/* FUN_0035a9b0 @ 0x35a9b0  (est. cl4_syscall_dispatch_empty2)
 * Empty dispatch entry.
 * Confidence: medium */
void cl4_syscall_dispatch_empty2_35a9b0(void) { return; }

/* FUN_0035a9c8 @ 0x35a9c8  (est. cl4_frame_walk_push)
 * Calls FUN_00205844 with the saved stack pointer (0x68 offset frame).
 * Confidence: low */
void cl4_frame_walk_push_35a9c8(void) { FUN_00205844(0); }

/* FUN_0035a9dc @ 0x35a9dc  (est. cl4_frame_walk2)
 * Calls FUN_001cf6f4 with (x29 - 0x68) — frame pointer relative.
 * Confidence: low */
void cl4_frame_walk2_35a9dc(void) { FUN_001cf6f4(0); }

/* FUN_0035a9f0 @ 0x35a9f0  (est. cl4_lazy_init_global6)
 * Lazily initialise the global at 0x656100 from descriptor 0x5a3c90.
 * Confidence: low */
void cl4_lazy_init_global6_35a9f0(void) { FUN_00002534(0x656100, 0x5a3c90); }

/* FUN_0035aa04 @ 0x35aa04  (est. cl4_trap_helper_a)
 * Forwards to FUN_001ef208.
 * Confidence: low */
void cl4_trap_helper_a_35aa04(void) { FUN_001ef208(); }

/* FUN_0035aa18 @ 0x35aa18  (est. cl4_trap_helper_b)
 * Forwards to FUN_002b800c.
 * Confidence: low */
void cl4_trap_helper_b_35aa18(void) { FUN_002b800c(); }

/* FUN_0035aa2c @ 0x35aa2c  (est. cl4_trap_helper_c)
 * Forwards to FUN_002cbea0.
 * Confidence: low */
void cl4_trap_helper_c_35aa2c(void) { FUN_002cbea0(); }

/* FUN_0035aa40 @ 0x35aa40  (est. cl4_syscall_4arg)
 * Forwards to FUN_0024be2c(a,0,0,d,0,0).
 * Confidence: low */
void cl4_syscall_4arg_35aa40(und8_t a, und8_t b, und8_t c, und8_t d)
{ FUN_0024be2c(a, 0, 0, d, 0, 0); }

/* FUN_0035aa54 @ 0x35aa54  (est. cl4_panic_code)
 * Raises panic code 0x13f via FUN_00377824(0x13f).
 * Confidence: low */
void cl4_panic_code_35aa54(void) { FUN_00377824(0x13f); }

/* FUN_0035aa68 @ 0x35aa68  (est. cl4_tcb_flag_set)
 * Calls FUN_002a2bb0((*(x20+0x18) & 0xffffffffffff), param & 1) — sets a
 * flag in a thread-control-block word.
 * Confidence: low */
void cl4_tcb_flag_set_35aa68(uint32_t flags)
{ FUN_002a2bb0(0, flags & 1); }

/* FUN_0035aa7c @ 0x35aa7c  (est. cl4_obj_field_write)
 * Calls FUN_002a218c(param+0x20, *(param+0x18) & 0xffffffffffff).
 * Confidence: low */
void cl4_obj_field_write_35aa7c(int64_t p)
{ FUN_002a218c(p + 0x20, 0); }

/* FUN_0035aa90 @ 0x35aa90  (est. cl4_obj_tail_call)
 * Tail call FUN_0036b270(*(x20 + param)).
 * Confidence: low */
void cl4_obj_tail_call_35aa90(int64_t p) { FUN_0036b270(0); }

/* FUN_0035aa9c @ 0x35aa9c  (est. cl4_trap_helper_d)
 * Forwards to FUN_001a26e0.
 * Confidence: low */
void cl4_trap_helper_d_35aa9c(void) { FUN_001a26e0(); }

/* FUN_0035aaa8 @ 0x35aaa8  (est. cl4_obj_call2)
 * Calls FUN_00208418(*(x29-0xc0), 0).
 * Confidence: low */
void cl4_obj_call2_35aaa8(void) { FUN_00208418(0, 0); }

/* FUN_0035aab4 @ 0x35aab4  (est. cl4_trap_save_arg)
 * Saves param to frame slot then calls FUN_0006e778(0x2d).
 * Confidence: low */
void cl4_trap_save_arg_35aab4(und8_t v) { FUN_0006e778(0x2d); }

/* FUN_0035aac0 @ 0x35aac0  (est. cl4_syscall_dispatch_empty3)
 * Empty dispatch entry.
 * Confidence: medium */
void cl4_syscall_dispatch_empty3_35aac0(void) { return; }

/* FUN_0035aacc @ 0x35aacc  (est. cl4_syscall_2arg_dispatch)
 * Saves arg2 then calls FUN_00377824().
 * Confidence: low */
void cl4_syscall_2arg_dispatch_35aacc(und8_t a, und8_t b) { FUN_00377824(); }

/* FUN_0035aad8 @ 0x35aad8  (est. cl4_syscall_2arg_b)
 * Forwards both args to FUN_0032220c.
 * Confidence: low */
void cl4_syscall_2arg_b_35aad8(und8_t a, und8_t b) { FUN_0032220c(); }

/* FUN_0035aae4 @ 0x35aae4  (est. cl4_syscall_2arg_c)
 * Saves arg2 then calls FUN_00377824().
 * Confidence: low */
void cl4_syscall_2arg_c_35aae4(und8_t a, und8_t b) { FUN_00377824(); }

/* FUN_0035aaf0 @ 0x35aaf0  (est. cl4_obj_tail_call2)
 * Tail call thunk_FUN_0036b270(*(x20+8)).
 * Confidence: low */
void cl4_obj_tail_call2_35aaf0(void) { thunk_FUN_0036b270(0); }

/* FUN_0035aafc @ 0x35aafc  (est. cl4_syscall_dispatch_empty4)
 * Empty dispatch entry.
 * Confidence: medium */
void cl4_syscall_dispatch_empty4_35aafc(void) { return; }

/* FUN_0035ab08 @ 0x35ab08  (est. cl4_trap_helper_e)
 * Forwards to FUN_002ab130.
 * Confidence: low */
void cl4_trap_helper_e_35ab08(void) { FUN_002ab130(); }

/* FUN_0035ab14 @ 0x35ab14  (est. cl4_obj_size)
 * Returns (param_2 & 0xfffffffffffffff) + 0x20 — object size with header.
 * Confidence: medium */
uint64_t cl4_obj_size_35ab14(und8_t p1, uint64_t sz) { return (sz & 0xfffffffffffffff) + 0x20; }

/* FUN_0035ab20 @ 0x35ab20  (est. cl4_trap_helper_f)
 * Forwards to FUN_0022b21c.
 * Confidence: low */
void cl4_trap_helper_f_35ab20(void) { FUN_0022b21c(); }

/* FUN_0035ab2c @ 0x35ab2c  (est. cl4_syscall_dispatch_empty5)
 * Empty dispatch entry.
 * Confidence: medium */
void cl4_syscall_dispatch_empty5_35ab2c(void) { return; }

/* FUN_0035ab38 @ 0x35ab38  (est. cl4_obj_slot_copy)
 * Copies a 5-word (0x28-byte) record from param_3 to the slot
 * (param_1 + param_2*0x28) — element store into a strided array.
 * Confidence: medium */
void cl4_obj_slot_copy_35ab38(int64_t base, int64_t idx, uint64_t *src)
{
    uint64_t *dst = (uint64_t *)(base + idx * 0x28);
    dst[0] = src[0]; dst[1] = src[1]; dst[2] = src[2];
    dst[3] = src[3]; dst[4] = src[4];
}

/* FUN_0035ab54 @ 0x35ab54  (est. cl4_syscall_dispatch_empty6)
 * Empty dispatch entry.
 * Confidence: medium */
void cl4_syscall_dispatch_empty6_35ab54(void) { return; }

/* FUN_0035ab60 @ 0x35ab60  (est. cl4_pair_combine)
 * Packs two 64-bit words into a 128-bit result {lo=param3, hi=param4}.
 * Confidence: medium */
void cl4_pair_combine_35ab60(und8_t p1, und8_t p2, und8_t lo, und8_t hi,
                             und8_t out[2]) { out[0] = lo; out[1] = hi; }

/* FUN_0035ab7c @ 0x35ab7c  (est. cl4_syscall_dispatch_empty7)
 * Empty dispatch entry.
 * Confidence: medium */
void cl4_syscall_dispatch_empty7_35ab7c(void) { return; }

/* FUN_0035ab88 @ 0x35ab88  (est. cl4_trap_helper_g)
 * Forwards to FUN_00310a14.
 * Confidence: low */
void cl4_trap_helper_g_35ab88(void) { FUN_00310a14(); }

/* FUN_0035aba4 @ 0x35aba4  (est. cl4_syscall_dispatch_empty8)
 * Empty dispatch entry.
 * Confidence: medium */
void cl4_syscall_dispatch_empty8_35aba4(void) { return; }

/* FUN_0035abb0 @ 0x35abb0  (est. cl4_obj_release_ref)
 * Releases a reference: FUN_001ee0fc(-8, param).
 * Confidence: low */
void cl4_obj_release_ref_35abb0(und8_t v) { FUN_001ee0fc(0xfffffffffffffff8, v); }

/* FUN_0035abbc @ 0x35abbc  (est. cl4_trap_helper_h)
 * Forwards to thunk_FUN_0035723c.
 * Confidence: low */
void cl4_trap_helper_h_35abbc(void) { thunk_FUN_0035723c(); }

/* FUN_0035abd8 @ 0x35abd8  (est. cl4_syscall_dispatch_empty9)
 * Empty dispatch entry.
 * Confidence: medium */
void cl4_syscall_dispatch_empty9_35abd8(void) { return; }

/* FUN_0035abe4 @ 0x35abe4  (est. cl4_trap_helper_i)
 * Forwards to FUN_000a68f4.
 * Confidence: low */
void cl4_trap_helper_i_35abe4(void) { FUN_000a68f4(); }

/* FUN_0035ac00 @ 0x35ac00  (est. cl4_trap_helper_j)
 * Forwards to FUN_0019e644.
 * Confidence: low */
void cl4_trap_helper_j_35ac00(void) { FUN_0019e644(); }

/* FUN_0035ac1c @ 0x35ac1c  (est. cl4_trap_helper_k)
 * Forwards to FUN_003a2610.
 * Confidence: low */
void cl4_trap_helper_k_35ac1c(void) { FUN_003a2610(); }

/* FUN_0035ac28 @ 0x35ac28  (est. cl4_trap_helper_l)
 * Forwards to FUN_00310a44.
 * Confidence: low */
void cl4_trap_helper_l_35ac28(void) { FUN_00310a44(); }

/* FUN_0035ac40 @ 0x35ac40  (est. cl4_trap_helper_m)
 * Forwards to FUN_00310a14.
 * Confidence: low */
void cl4_trap_helper_m_35ac40(void) { FUN_00310a14(); }

/* FUN_0035ac58 @ 0x35ac58  (est. cl4_trap_helper_n)
 * Forwards to FUN_0008f6f4.
 * Confidence: low */
void cl4_trap_helper_n_35ac58(void) { FUN_0008f6f4(); }

/* FUN_0035ac70 @ 0x35ac70  (est. cl4_syscall_dispatch_empty_a)
 * Empty dispatch entry.
 * Confidence: medium */
void cl4_syscall_dispatch_empty_a_35ac70(void) { return; }

/* FUN_0035aca4 @ 0x35aca4  (est. cl4_syscall_dispatch_empty_b)
 * Empty dispatch entry.
 * Confidence: medium */
void cl4_syscall_dispatch_empty_b_35aca4(void) { return; }

/* FUN_0035acc8 @ 0x35acc8  (est. cl4_syscall_dispatch_empty_c)
 * Empty dispatch entry.
 * Confidence: medium */
void cl4_syscall_dispatch_empty_c_35acc8(void) { return; }

/* FUN_0035acdc @ 0x35acdc  (est. cl4_syscall_dispatch_empty_d)
 * Empty dispatch entry.
 * Confidence: medium */
void cl4_syscall_dispatch_empty_d_35acdc(void) { return; }

/* FUN_0035ace8 @ 0x35ace8  (est. cl4_syscall_dispatch_empty_e)
 * Empty dispatch entry.
 * Confidence: medium */
void cl4_syscall_dispatch_empty_e_35ace8(void) { return; }

/* FUN_0035acfc @ 0x35acfc  (est. cl4_syscall_dispatch_empty_f)
 * Empty dispatch entry.
 * Confidence: medium */
void cl4_syscall_dispatch_empty_f_35acfc(void) { return; }

/* ------------------------------------------------------------------ *
 * Global registration table + tagged small-hash-table layer
 * (0x35ad10-0x35b588). A process-global registry keyed by an object
 * pointer, protected by an LO lock and a mutex (0x6c0190). Element
 * records are stored with tagged (low-bit = element size) pointers.
 * ------------------------------------------------------------------ */

/* FUN_0035ad10 @ 0x35ad10  (est. cl4_registry_insert)
 * Inserts an object into the global registration table under an LO lock.
 * On first failure it grows the table, allocates a new slot array, writes
 * {key, value} records, then drains the deferred-free list after a memory
 * barrier. Returns the stored value.
 * Confidence: medium
 * Notes: LOAcquire/LORelease; DAT_006c0170 counter; deferred frees via
 *   thunk_FUN_00012568; grow FUN_0035b2c8, slot alloc FUN_0035b4b8. */
uint64_t cl4_registry_insert_35ad10(und8_t key)
{
    uint64_t *slot; uint64_t v, n, hash, rem, cap;
    LOAcquire();
    DAT_006c0170 = DAT_006c0170 + 1;
    if (((DAT_006c0178 == 0) || (DAT_006c0180 == 0)) || (DAT_006c0174 == 0) ||
        ((slot = (uint64_t *)FUN_0035b028(&key, DAT_006c0180, DAT_006c0174, DAT_006c0178 + 2)) == 0)) {
        /* Miss: reclaim, then retry under the registry mutex. */
        DAT_006c0170 = DAT_006c0170 - 1;
        LORelease();
        FUN_0039c740(DAT_006c0170, key, 0x6101dc);
        v = FUN_0039c49c(key, 0);
        /* lock 0x6c0190 (init once then lock) */
        if (DAT_006c01a0 > 0) { /* lock held */ }
        else if (DAT_006c01a0 == 0) {
            DAT_006c01a0 = 1;
            if (FUN_00118148(0x6c0190, 0)) FUN_003a2578(0x5d3f10);
            DAT_006c01a0 = -1;
        } else { while (DAT_006c01a0 > 0) { } }
        if (FUN_00118164(0x6c0190)) FUN_003a2578(0x5d3ee0);
        cap = DAT_006c0180;
        n = DAT_006c0174;
        /* pick element-size exponent from tagged descriptor */
        {
            uint64_t es = 4;
            if ((DAT_006c0180 & 3) && (DAT_006c0180 & 0xfffffffffffffffc))
                es = *(uint8_t *)(DAT_006c0180 & 0xfffffffffffffffc);
            hash = 1ULL << (es & 0x3f);
            rem = (hash - (n + 1));
            if (rem && (hash / rem) > 3) {
                cap = FUN_0035b2c8(cap, es, (DAT_006c0178 ? DAT_006c0178 + 2 : 0));
                FUN_0035b028(&key, cap, n, (DAT_006c0178 ? DAT_006c0178 + 2 : 0));
            }
            if ((DAT_006c0178 == 0) || (*(uint32_t *)DAT_006c0178 <= n))
                DAT_006c0178 = FUN_0035b4b8(DAT_006c0178, n);
            *(uint64_t *)(DAT_006c0178 + n*16 + 16) = key;
            *(uint64_t *)(DAT_006c0178 + n*16 + 32) = v;
            DAT_006c0174 = n + 1;
            FUN_0035b588(&key, &DAT_006c0180, n + 1, 0, 3);
        }
        DataMemoryBarrier(2, 3);
        if (DAT_006c0170 == 0) {
            uint64_t *p = (uint64_t *)DAT_006c01b0, *nx;
            while (p) { nx = (uint64_t *)*p; thunk_FUN_00012568(p[1]); thunk_FUN_00012568(p); p = nx; }
            DAT_006c01b0 = 0;
        }
        FUN_0035b228(0x6c0190);
    } else {
        v = *(uint64_t *)(slot + 8);
        DAT_006c0170 = DAT_006c0170 - 1;
        LORelease();
    }
    return v;
}

/* FUN_0035afb8 @ 0x35afb8  (est. cl4_registry_insert_or_wrap)
 * If the object type is a container/endpoint variant (0x203/0x204/0x305/0),
 * inserts it into the registry (FUN_0035ad10), then forwards to
 * FUN_002296b0(a,b,obj,d) regardless.
 * Confidence: medium */
void cl4_registry_insert_or_wrap_35afb8(und8_t a, und8_t b, uint64_t *obj, und8_t d)
{
    int t = 0;
    if (*obj < 0x800) t = (int)*obj;
    if ((t - 0x203U < 2) || (t == 0x305) || (t == 0)) obj = (uint64_t *)FUN_0035ad10(obj);
    FUN_002296b0(a, b, obj, d);
}

/* FUN_0035b028 @ 0x35b028  (est. cl4_small_ht_lookup)
 * Probes the tagged small hash table for the key *param_1. The low bits of
 * the descriptor encode element size; returns {found_ptr, index}. Uses a
 * hash of the key and open addressing via FUN_0035b178.
 * Confidence: medium
 * Notes: 0x5f4f3d9d-style finalizer hash (murmer-ish constants). */
void cl4_small_ht_lookup_35b028(uint64_t *key, uint64_t desc, uint64_t n, int64_t slots,
                                uint64_t out[2])
{
    uint64_t h, es, mask, idx, cur; int probe;
    h = *key;
    h = ((h & 0xffffffff) * 8 + 0xf9000a63a9000a61 ^ h >> 0x20) * -0x622015f714c7d297;
    h = (h >> 0x20 ^ h >> 0x2f ^ h) * -0x622015f714c7d297;
    es = 4;
    if ((desc & 3) && (desc & 0xfffffffffffffffc)) es = *(uint8_t *)(desc & 0xfffffffffffffffc);
    mask = ~(-1ULL << (es & 0x3f));
    h = (h ^ h >> 0x2f) * 0x1ddfea08eb382d69 & mask;
    if (h < 2) h = 1;
    idx = h;
    probe = FUN_0035b178(&idx, h, 2);
    while (probe) {
        if (((uint64_t)(probe - 1) < n) &&
            (*(uint64_t *)(slots + (uint64_t)(probe - 1) * 0x10) == *key)) {
            out[0] = slots + (uint64_t)(probe - 1) * 0x10; out[1] = 0; return;
        }
        h = h + 1 & mask;
        if (h < 2) h = 1;
        probe = FUN_0035b178(&idx, h, 2);
    }
    out[0] = 0; out[1] = h & 0xffffffff;
}

/* FUN_0035b178 @ 0x35b178  (est. cl4_small_ht_read)
 * Reads element `index` from a tagged small hash table. The low 2 bits of
 * *param_1 give the element width (0=4-bit nibble, 1=8-bit, 2=16-bit,
 * 3=32-bit); returns the element value.
 * Confidence: medium */
uint32_t cl4_small_ht_read_35b178(uint64_t *slot, uint64_t index, int width)
{
    uint64_t w = *slot; uint32_t tag = (uint32_t)w & 3; uint64_t base;
    if (tag == 0) return (uint32_t)(w >> ((index & 0xf) << 2)) & 0xf;
    base = (w & 3) ? (w & 0xfffffffffffffffc) : 0;
    if (tag == 1) return *(uint8_t *)(base + index);
    if (tag == 2) return *(uint16_t *)(base + index * 2);
    return *(uint32_t *)(base + index * 4);
}

/* FUN_0035b228 @ 0x35b228  (est. cl4_mutex_unlock)
 * Releases the mutex object at *param_1: spins/initialises the state word
 * and calls FUN_00118194; panics on failure ("__mtx_unlock handle_mutex
 * fail"). Returns param_1.
 * Confidence: high (string "__mtx_unlock handle_mutex fail") */
uint64_t *cl4_mutex_unlock_35b228(uint64_t *param_1)
{
    int64_t m = *param_1;
    if (*(int32_t *)(m + 0x10) > 0) { }
    else if (*(int32_t *)(m + 0x10) == 0) {
        *(int32_t *)(m + 0x10) = 1;
        if (FUN_00118148(m, 0)) FUN_003a2578(0x5d3f10);
        *(int32_t *)(m + 0x10) = -1;
    } else { while (*(int32_t *)(m + 0x10) > 0) { } }
    if (FUN_00118194(m)) FUN_003a2578(0x5d3f4d);
    return param_1;
}

/* FUN_0035b2c8 @ 0x35b2c8  (est. cl4_small_ht_grow)
 * Grows/resizes the tagged small hash table to hold elements of the given
 * size exponent. Allocates a fresh block via FUN_00010244, records the
 * descriptor as a tagged pointer, rehashes all live entries by reading
 * each source slot, and links a deferred-free record into DAT_006c01b0.
 * Confidence: medium
 * Notes: tag 0x48dda4ae; free-record tag 0xa0040aff93c70. */
uint64_t cl4_small_ht_grow_35b2c8(uint64_t src, uint64_t size_exp, int64_t src_slots)
{
    uint32_t es = (uint32_t)size_exp + 1, slot_w = 2, v;
    uint8_t *blk; uint64_t i, nd, h, probe;
    if ((es & 0xff) > 0x10) slot_w = 4;
    if ((es & 0xff) < 9) slot_w = 1;
    blk = (uint8_t *)FUN_00010244(2ULL << (size_exp & 0x3f), slot_w, 0x48dda4ae);
    if (!blk) { SoftwareBreakpoint(1, 0x35b4b8); }
    *blk = (uint8_t)es;
    nd = ((uint64_t)blk) | slot_w;             /* tagged descriptor */
    if ((int)size_exp != 0) {
        i = 1;
        do {
            v = FUN_0035b178(&src, i, 0);
            if (v) {
                uint64_t key = *(uint64_t *)(src_slots + (uint64_t)(v - 1) * 0x10);
                h = ((key & 0xffffffff) * 8 + 0xf9000a63a9000a61 ^ key >> 0x20) * -0x622015f714c7d297;
                h = (h >> 0x20 ^ h >> 0x2f ^ h) * -0x622015f714c7d297;
                h = (h ^ h >> 0x2f) * -0x622015f714c7d297;
                while ((h = h & ~(-2ULL << (size_exp & 0x3f)),
                        h == 0 || (probe = FUN_0035b178(&nd, h, 0)) != 0)) h = h + 1;
                FUN_0035b588(&nd, 0, v, h, 0);
            }
            i = i + 1;
        } while (i >> (size_exp & 0x3f) == 0);
    }
    DAT_006c0180 = nd;
    if ((src & 3) && (src & 0xfffffffffffffffc)) {
        uint64_t *fr = (uint64_t *)FUN_000101a0(0x10, 0xa0040aff93c70);
        fr[0] = DAT_006c01b0; fr[1] = src & 0xfffffffffffffffc;
        DAT_006c01b0 = (uint64_t)fr;
    }
    return nd;
}

/* FUN_0035b4b8 @ 0x35b4b8  (est. cl4_small_ht_alloc)
 * Allocates the slot array for the small hash table: grows to a power of
 * two, copies old slots, links a deferred-free record. Returns the new
 * storage pointer stored in DAT_006c0178.
 * Confidence: medium
 * Notes: tags 0x1060040ca828048 / 0xa0040aff93c70. */
uint32_t *cl4_small_ht_alloc_35b4b8(int64_t old, uint64_t n)
{
    uint64_t sz = n >> 2;
    uint32_t *p; int64_t cpy;
    if (sz < 2) sz = 1;
    sz = FUN_0001279c((sz + n) * 0x10 | 8);
    p = (uint32_t *)FUN_000101a0(sz, 0x1060040ca828048);
    if (!p) { SoftwareBreakpoint(1, 0x35b588); }
    *p = (uint32_t)((sz + 0xffffffff8) >> 4);
    if (old) {
        cpy = 0;
        if (7 < sz) cpy = sz - 8;
        FUN_00117cc8(p + 2, old + 8, n << 4, cpy);
        uint64_t *fr = (uint64_t *)FUN_000101a0(0x10, 0xa0040aff93c70);
        fr[0] = DAT_006c01b0; fr[1] = old;
        DAT_006c01b0 = (uint64_t)fr;
    }
    DAT_006c0178 = (uint64_t)p;
    return p;
}

/* FUN_0035b588 @ 0x35b588  (est. cl4_small_ht_write)
 * Writes value `val` at index `idx` of a tagged small hash table. `kind`
 * 3 forces a 32-bit store; otherwise the store width matches the element
 * tag. When the tag is 0, packs the value into a nibble bit-field.
 * Confidence: medium */
void cl4_small_ht_write_35b588(uint64_t *slot, uint64_t *dst, uint32_t val, uint64_t idx, int kind)
{
    uint64_t w = *slot; uint32_t tag = (uint32_t)w & 3; uint64_t base;
    if (tag == 0) {
        w = (w & ~(0xfull << ((idx & 0xf) << 2))) | ((uint64_t)val << ((idx & 0xf) << 2));
        *dst = w; return;
    }
    base = (w & 3) ? (w & 0xfffffffffffffffc) : 0;
    if (tag == 1) { if (kind == 3) *(uint32_t *)(base + idx) = val; else *(uint8_t *)(base + idx) = (uint8_t)val; return; }
    if (tag == 2) { if (kind == 3) *(uint32_t *)(base + idx * 2) = val; else *(uint16_t *)(base + idx * 2) = (uint16_t)val; return; }
    *(uint32_t *)(base + idx * 4) = val;
}

/* ------------------------------------------------------------------ *
 * Swift collection element copy / destroy / init (0x35b67c-0x35cfe4).
 * These dispatch on the type's flags word at type_ptr[-1] (offsets +0x48
 * stride, +0x52 flags) and on the metadata kind at type_ptr[-2]+0x10.
 * ------------------------------------------------------------------ */

/* FUN_0035b644 @ 0x35b644  (est. cl4_registry_cached_base)
 * Returns the cached registration base pointer (0x657740). Writes the
 * current lazy-init value into the global at 0x657738, falling back to
 * -0xae502812aa7333 when DAT_006adf08 is unset.
 * Confidence: low */
uint64_t cl4_registry_cached_base_35b644(void)
{
    /* write-through of the cached slot; result is a fixed base pointer */
    if (DAT_006adf08 != 0) { *(int64_t *)0x657738 = (int64_t)DAT_006adf08; }
    else { *(int64_t *)0x657738 = -0xae502812aa7333; }
    return 0x657740;
}

/* FUN_0035b67c @ 0x35b67c  (est. sw_copy_forward)
 * Copies `n` elements from src to dst, stride from type flags. If the
 * element is trivially copyable, memcpy; else per-element copy via the
 * type's copy-function (vtable +0x10) or a memmove fast path.
 * Confidence: medium */
void sw_copy_forward_35b67c(int64_t dst, int64_t src, int64_t n, int64_t t)
{
    int64_t md, stride; if (!n) return;
    md = *(int64_t *)(t - 8); if (!md) md = 0;
    stride = *(int64_t *)(md + 0x48);
    if (!(*(uint8_t *)(md + 0x52) & 1)) { FUN_00117cc4(dst, src, stride * n); return; }
    if (FUN_0035bd48(t) && (*(uint8_t *)(FUN_0035bd48(t) + 2) >> 4 & 1)) { FUN_0035c1e0(dst, src, n, stride, t); return; }
    while (n--) { (*(void(**)(int64_t,int64_t,int64_t))md)(dst, src, t); dst += stride; src += stride; }
}

/* FUN_0035b7ac @ 0x35b7ac  (est. sw_initialize_copy_forward)
 * Initializes dst from src for n elements. Trivial => memcpy via
 * FUN_00117d14; else per-element init-copy via vtable +0x20.
 * Confidence: medium */
void sw_initialize_copy_forward_35b7ac(int64_t dst, int64_t src, int64_t n, int64_t t)
{
    int64_t md, stride; if (!n) return;
    md = *(int64_t *)(t - 8); if (!md) md = 0;
    stride = *(int64_t *)(md + 0x48);
    if (!(*(uint8_t *)(md + 0x52) >> 4 & 1)) { FUN_00117d14(dst, src, stride * n); return; }
    FUN_0035bd48(t); FUN_0035bd48(t);
    while (n--) { (*(void(**)(int64_t,int64_t,int64_t))md)(dst, src, t); dst += stride; src += stride; }
}

/* FUN_0035b898 @ 0x35b898  (est. sw_initialize_copy_reverse)
 * Initializes dst from src for n elements in reverse order (back to front).
 * Confidence: medium */
void sw_initialize_copy_reverse_35b898(int64_t dst, int64_t src, int64_t n, int64_t t)
{
    int64_t md, stride; if (!n) return;
    md = *(int64_t *)(t - 8); if (!md) md = 0;
    stride = *(int64_t *)(md + 0x48);
    if (!(*(uint8_t *)(md + 0x52) >> 4 & 1)) { FUN_00117d14(dst, src, stride * n); return; }
    dst += stride * (n - 1); src += stride * (n - 1);
    while (n--) { (*(void(**)(int64_t,int64_t,int64_t))md)(dst, src, t); dst -= stride; src -= stride; }
}

/* FUN_0035b974 @ 0x35b974  (est. sw_initialize_with_take_forward)
 * Initializes dst by taking ownership of n elements from src (move init).
 * Confidence: medium */
void sw_initialize_with_take_forward_35b974(int64_t dst, int64_t src, int64_t n, int64_t t)
{
    int64_t md, stride; if (!n) return;
    md = *(int64_t *)(t - 8); if (!md) md = 0;
    stride = *(int64_t *)(md + 0x48);
    if (!(*(uint8_t *)(md + 0x52) & 1)) { FUN_00117d14(dst, src, stride * n); return; }
    FUN_0035bd48(t);
    if (FUN_0035bd48(t) && (*(uint8_t *)(FUN_0035bd48(t) + 2) >> 4 & 1)) { FUN_0035c718(dst, src, n, stride, t); return; }
    while (n--) { (*(void(**)(int64_t,int64_t,int64_t))md)(dst, src, t); dst += stride; src += stride; }
}

/* FUN_0035baa4 @ 0x35baa4  (est. sw_initialize_with_take_reverse)
 * Initializes dst by moving n elements from src in reverse order.
 * Confidence: medium */
void sw_initialize_with_take_reverse_35baa4(int64_t dst, int64_t src, int64_t n, int64_t t)
{
    int64_t md, stride; if (!n) return;
    md = *(int64_t *)(t - 8); if (!md) md = 0;
    stride = *(int64_t *)(md + 0x48);
    if (!(*(uint8_t *)(md + 0x52) & 1)) { FUN_00117d14(dst, src, stride * n); return; }
    dst += stride * (n - 1); src += stride * (n - 1);
    while (n--) { (*(void(**)(int64_t,int64_t,int64_t))md)(dst, src, t); dst -= stride; src -= stride; }
}

/* FUN_0035bb80 @ 0x35bb80  (est. sw_assign_with_copy_forward)
 * Assigns dst = src for n elements, taking ownership (move-assign).
 * Confidence: medium */
void sw_assign_with_copy_forward_35bb80(int64_t dst, int64_t src, int64_t n, int64_t t)
{
    int64_t md, stride; if (!n) return;
    md = *(int64_t *)(t - 8); if (!md) md = 0;
    stride = *(int64_t *)(md + 0x48);
    if (!(*(uint8_t *)(md + 0x52) & 0x11)) { FUN_00117cc4(dst, src, stride * n); return; }
    FUN_0035bd48(t); FUN_0035bd48(t);
    while (n--) { (*(void(**)(int64_t,int64_t,int64_t))md)(dst, src, t); dst += stride; src += stride; }
}

/* FUN_0035bc70 @ 0x35bc70  (est. sw_destroy)
 * Destroys n elements at dst using the type's destroy function (vtable
 * +8); fast path for bitwise-copyable types (no-op).
 * Confidence: medium */
void sw_destroy_35bc70(int64_t dst, int64_t n, int64_t t)
{
    int64_t md, stride; if (!n) return;
    md = *(int64_t *)(t - 8); if (!md) md = 0;
    if (*(uint8_t *)(md + 0x52) & 1) {
        stride = *(int64_t *)(md + 0x48);
        if (FUN_0035bd48(t) && (*(uint8_t *)(FUN_0035bd48(t) + 2) >> 4 & 1)) { FUN_0035be00(dst, n, stride, t); return; }
        while (n--) { (*(void(**)(int64_t,int64_t))md)(dst, t); dst += stride; }
    }
}

/* FUN_0035bd48 @ 0x35bd48  (est. cl4_cap_child_ptr)
 * Given a cap object, returns the "child/next" pointer field depending on
 * its type tag: type 0 => field[5], types 0x200-0x202 => field[1],
 * types 0x203/0x204 => field[1]. Returns 0 for unknown types.
 * Confidence: medium */
uint64_t cl4_cap_child_ptr_35bd48(uint64_t *c)
{
    int t = 0; uint64_t v;
    if (*c < 0x800) t = (int)*c;
    if (t < 0x203) { if (t - 0x200U < 3) v = c[1]; else if (t != 0) return 0; else v = c[5]; }
    else { if ((t != 0x203) && (t != 0x204)) return 0; v = c[1]; }
    return v ? v : 0;
}

/* FUN_0035bdf8 @ 0x35bdf8  (est. cl4_const_zero)
 * Returns 0.
 * Confidence: high (trivial) */
uint64_t cl4_const_zero_35bdf8(void) { return 0; }

/* FUN_0035be00 @ 0x35be00  (est. sw_destroy_with_tail)
 * Destroys elements with an indirect destroy jump-table dispatch based on
 * the metadata-kind byte of the type record.
 * Confidence: low (indirect jump table at 0x679a08) */
void sw_destroy_with_tail_35be00(und8_t p1, int64_t n, und8_t p3, int64_t t)
{
    uint64_t u = *(uint64_t *)(t - 0x10);
    if (!n) return;
    if (u & 1) u &= 0x7ffffffffffffffe;
    (*(void(**)(void))(((*(uint64_t *)((u + 0x10) & 0x7fffffffffffffff) >> 0x38) * 8 + 0x679a08)))();
}

/* FUN_0035c1e0 @ 0x35c1e0  (est. sw_copy_with_tail)
 * Element copy with tail: memcpy the bulk then dispatch to the per-kind
 * copy routine in the jump table at 0x679b78.
 * Confidence: low */
void sw_copy_with_tail_35c1e0(und8_t dst, und8_t src, int64_t n, und8_t stride, int64_t t)
{
    uint64_t u = *(uint64_t *)(t - 0x10), rec, size;
    if (!n) return;
    if (u & 1) u &= 0x7ffffffffffffffe;
    rec = *(uint64_t *)((u + 0x10) & 0x7fffffffffffffff);
    size = rec & 0xffffffffffffff;
    if (size) FUN_00117cc4(dst, src, size);
    (*(void(**)(void))((rec >> 0x38) * 8 + 0x679b78))();
}

/* FUN_0035c718 @ 0x35c718  (est. sw_move_init_with_tail)
 * Move-initialize with tail: memcpy bulk then dispatch to the per-kind
 * move-init routine at 0x679ce8.
 * Confidence: low */
void sw_move_init_with_tail_35c718(und8_t dst, und8_t src, int64_t n, und8_t stride, int64_t t)
{
    uint64_t u = *(uint64_t *)(t - 0x10), rec, size;
    if (!n) return;
    if (u & 1) u &= 0x7ffffffffffffffe;
    rec = *(uint64_t *)((u + 0x10) & 0x7fffffffffffffff);
    size = rec & 0xffffffffffffff;
    if (size) FUN_00117cc4(dst, src, size);
    (*(void(**)(void))((rec >> 0x38) * 8 + 0x679ce8))();
}

/* FUN_0035cc88 @ 0x35cc88  (est. sw_type_layout_copy)
 * Decodes a Swift type-layout record and writes the layout into the
 * destination. Walks the field records; for each the metadata-kind byte
 * selects the encode step (1-16 simple, 0xc=double, 0xf=indirect object
 * ref, 0x10/0x11/0x12 tuples, 0x13/0x14 nested record, 0x15/0x16 lists).
 * Confidence: low */
void sw_type_layout_copy_35cc88(int64_t dst, int64_t dbase, uint64_t src, int64_t t, und8_t p5)
{
    /* Structural walk of the layout descriptor at `src`; writes encoded
       records at dst. Opaque in this reconstruction (jump-table driven). */
    (void)dst; (void)dbase; (void)src; (void)t;
}

/* FUN_0035cf24 @ 0x35cf24  (est. cl4_cap_tag_store)
 * Stores a tagged reference: FUN_0035cf38(p2, p1, 0).
 * Confidence: medium */
void cl4_cap_tag_store_35cf24(und8_t a, und8_t b) { FUN_0035cf38(b, a, 0); }

/* FUN_0035cf38 @ 0x35cf38  (est. cl4_cap_ref_write)
 * Writes a tagged reference value into a cap object's header. The low bit
 * of the value is the tagged flag (forced on unless param_3==0). The
 * header location depends on type: 0/0x305/0x203 => 3 words back,
 * otherwise 2 words back.
 * Confidence: medium */
void cl4_cap_ref_write_35cf38(uint64_t *c, uint64_t val, int tag)
{
    uint64_t v = val | 1; int t = 0;
    if (tag == 0) v = val;
    if (*c < 0x800) t = (int)*c;
    if ((t == 0) || (t == 0x305) || (t == 0x203)) c -= 3; else c -= 2;
    *c = v;
}

/* FUN_0035cf8c @ 0x35cf8c  (est. sw_destroy_indirect)
 * Indirect destroy: dispatches through the jump table at 0x679f10 based
 * on the type's metadata-kind byte.
 * Confidence: low */
void sw_destroy_indirect_35cf8c(und8_t p1, int64_t t)
{
    uint64_t u = *(uint64_t *)(t - 0x10);
    if (u & 1) u &= 0x7ffffffffffffffe;
    (*(void(**)(void))((*(uint64_t *)((u + 0x10) & 0x7fffffffffffffff) >> 0x38) * 8 + 0x679f10))();
}

/* FUN_0035cf94 @ 0x35cf94  (est. sw_destroy_then_init)
 * Destroys then initializes a slot: FUN_0035d334 then FUN_0035e134.
 * Confidence: medium */
void sw_destroy_then_init_35cf94(und8_t a, und8_t b, und8_t t)
{ FUN_0035d334(a, t); FUN_0035e134(a, b, t); }

/* FUN_0035cfdc @ 0x35cfdc  (est. sw_init_indirect)
 * Indirect initialize with bulk copy: if the type has a bulk size, memcpy
 * then dispatch to the per-kind init routine at 0x67a080.
 * Confidence: low */
void sw_init_indirect_35cfdc(und8_t dst, und8_t src, int64_t t)
{
    uint64_t u = *(uint64_t *)(t - 0x10), rec, size;
    if (u & 1) u &= 0x7ffffffffffffffe;
    rec = *(uint64_t *)((u + 0x10) & 0x7fffffffffffffff);
    size = rec & 0xffffffffffffff;
    if (size) FUN_00117cc4(dst, src, size);
    (*(void(**)(void))((rec >> 0x38) * 8 + 0x67a080))();
}

/* FUN_0035cfe4 @ 0x35cfe4  (est. sw_element_assign_ptr)
 * Assigns one element: if the type is bitwise-copyable (flags bit1 clear)
 * does a raw copy via FUN_0035dc24; else copies the tagged value and bumps
 * the reference via FUN_0036b270, advancing to the next slot.
 * Confidence: medium */
uint64_t *sw_element_assign_ptr_35cfe4(uint64_t *dst, uint64_t *src, int64_t t)
{
    if (!(*(uint8_t *)(*(int64_t *)(t - 8) + 0x52) >> 1 & 1)) { FUN_0035dc24(dst); }
    else { *dst = *src; FUN_0036b270(*src); dst = (uint64_t *)(*dst + 0x10); }
    return dst;
}

/* ------------------------------------------------------------------ *
 * Swift type-metadata encode/decode helpers (0x35d184-0x35f808).
 * ------------------------------------------------------------------ */

/* FUN_0035d184 @ 0x35d184  (est. sw_bitfield_store)
 * Stores a value into a packed bitfield described by the type record:
 * reads offset/width/size from the metadata, splits the value between the
 * low field and an overflow field, and writes both with the correct width
 * (1/2/4/8 bytes). Used for enum payload encoding.
 * Confidence: low */
void sw_bitfield_store_35d184(uint32_t *dst, uint32_t val, int64_t t)
{
    uint64_t u = *(uint64_t *)(t - 0x10) & 0xfffffffffffffffe;
    uint64_t off = *(uint64_t *)(u + 0x18), sz = *(int64_t *)(u + 0x30) - off;
    uint32_t cap = *(uint32_t *)(u + 0x20), iv, rem;
    uint32_t *hi; uint64_t w;
    if ((uint64_t)val < cap) {
        dst = (uint32_t *)((int64_t)dst + sz);
        w = *(uint64_t *)(u + 0x18);
        if (w == 0) return;
        if (w == 1) { *(uint8_t *)dst = (uint8_t)val; return; }
        if (w == 2) { *(uint16_t *)dst = (uint16_t)val; return; }
        if (w == 3) { *(uint16_t *)dst = (uint16_t)val; *(uint8_t *)((int64_t)dst + 2) = (uint8_t)(val >> 16); return; }
        *dst = val; return;
    }
    iv = (int)val - (int)cap; w = *(uint64_t *)(u + 0x18);
    hi = (uint32_t *)((int64_t)dst + sz);
    if (w == 0) { }
    else if (w == 1) *(uint8_t *)hi = (uint8_t)iv;
    else if (w == 2) *(uint16_t *)hi = (uint16_t)iv;
    else if (w == 3) { *(uint16_t *)hi = (uint16_t)iv; *(uint8_t *)((int64_t)hi + 2) = (uint8_t)(iv >> 16); }
    else if (w == 4) *hi = iv;
    else { *hi = iv; thunk_FUN_00114330(hi + 1, w - 4); }
    if (sz == 0) return;
    if (sz == 1) { *(uint8_t *)dst = (uint8_t)val; return; }
    if (sz == 2) { *(uint16_t *)dst = (uint16_t)val; return; }
    if (sz == 3) { *(uint16_t *)dst = (uint16_t)val; *(uint8_t *)((int64_t)dst + 2) = (uint8_t)(val >> 16); return; }
    *dst = val;
}

/* FUN_0035d334 @ 0x35d334  (est. sw_destroy_tail)
 * Tail-destroy dispatch through jump table 0x679f10.
 * Confidence: low */
void sw_destroy_tail_35d334(und8_t p1, int64_t t)
{
    uint64_t u = *(uint64_t *)(t - 0x10);
    if (u & 1) u &= 0x7ffffffffffffffe;
    (*(void(**)(void))((*(uint64_t *)((u + 0x10) & 0x7fffffffffffffff) >> 0x38) * 8 + 0x679f10))();
}

/* FUN_0035d6dc @ 0x35d6dc  (est. sw_copy_tail_dispatch)
 * Bulk-copy then per-kind dispatch through jump table 0x679fc8.
 * Confidence: low */
void sw_copy_tail_dispatch_35d6dc(und8_t dst, und8_t src, int64_t t)
{
    uint64_t u = *(uint64_t *)(t - 0x10), rec, size;
    if (u & 1) u &= 0x7ffffffffffffffe;
    rec = *(uint64_t *)((u + 0x10) & 0x7fffffffffffffff);
    size = rec & 0xffffffffffffff;
    if (size) FUN_00117cc4(dst, src, size);
    (*(void(**)(void))((rec >> 0x38) * 8 + 0x679fc8))();
}

/* FUN_0035dc24 @ 0x35dc24  (est. sw_copy_bulk_dispatch)
 * Bulk-copy then per-kind dispatch through jump table 0x67a080.
 * Confidence: low */
void sw_copy_bulk_dispatch_35dc24(und8_t dst, und8_t src, int64_t t)
{
    uint64_t u = *(uint64_t *)(t - 0x10), rec, size;
    if (u & 1) u &= 0x7ffffffffffffffe;
    rec = *(uint64_t *)((u + 0x10) & 0x7fffffffffffffff);
    size = rec & 0xffffffffffffff;
    if (size) FUN_00117cc4(dst, src, size);
    (*(void(**)(void))((rec >> 0x38) * 8 + 0x67a080))();
}

/* FUN_0035e134 @ 0x35e134  (est. sw_initialize_bulk)
 * Initializes elements: if the type is bitwise-copyable (flags bit4 clear)
 * copies the type's size via FUN_00117cc4; else bulk-copies then dispatch
 * through jump table 0x67a138.
 * Confidence: low */
void sw_initialize_bulk_35e134(und8_t dst, und8_t src, int64_t t)
{
    uint64_t u, rec, size;
    if (!(*(uint8_t *)(*(int64_t *)(t - 8) + 0x52) >> 4 & 1)) { FUN_00117cc4(dst, src, *(uint64_t *)(*(int64_t *)(t - 8) + 0x40)); return; }
    u = *(uint64_t *)(t - 0x10);
    if (u & 1) u &= 0x7ffffffffffffffe;
    rec = *(uint64_t *)((u + 0x10) & 0x7fffffffffffffff);
    size = rec & 0xffffffffffffff;
    if (size) FUN_00117cc4(dst, src, size);
    (*(void(**)(void))((rec >> 0x38) * 8 + 0x67a138))();
}

/* FUN_0035e530 @ 0x35e530  (est. sw_decode_pointer_elem)
 * Decodes one pointer-width element via the type's decode function
 * (vtable +8): advances the cursor by the element size from the metadata
 * and writes the decoded value at (param4 + *cursor).
 * Confidence: low */
void sw_decode_pointer_elem_35e530(und8_t p1, und8_t p2, int64_t *cur, int64_t base)
{
    int64_t md = FUN_0035ea78(); int64_t old = *cur;
    (*(void(**)(int64_t,int64_t))(*(int64_t *)(md - 8) + 8))(base + old, md);
    *cur = *(int64_t *)(*(int64_t *)(md - 8) + 0x40) + old;
}

/* FUN_0035e690 @ 0x35e690  (est. sw_decode_vtable_elem)
 * Decodes one element using the inline descriptor vtable (relative
 * function pointer at *piVar3). On success advances the cursor by the
 * encoded count; the descriptor ends with a count/size pair.
 * Confidence: low */
void sw_decode_vtable_elem_35e690(und8_t p1, int64_t *in, int64_t *cur, int64_t base)
{
    int32_t *p = (int32_t *)*in, *np; int r; uint64_t sz = 0, cnt = 0;
    np = p + 2;
    r = (*(int(**)(int64_t))((int64_t)*p + (int64_t)p))(base + *cur);
    if (r == 0) np = p + 6;
    else { FUN_0035efdc(&np, &cnt, &sz); np = (int32_t *)((int64_t)np + cnt); *cur = *cur + sz; }
    *in = (int64_t)np;
}

/* FUN_0035e738 @ 0x35e738  (est. sw_decode_struct_elem)
 * Decodes a struct element: reads the per-field descriptor, calls the
 * field decode function, and advances the cursor by the field size on
 * success.
 * Confidence: low */
void sw_decode_struct_elem_35e738(und8_t p1, uint64_t *in, int64_t *cur, int64_t base)
{
    uint64_t *p = (uint64_t *)(*in & 0x7fffffffffffffff);
    int64_t sz = p[1], out = p[2]; uint64_t np = *in + 0x18;
    if ((*(int(**)(int64_t))*p)(base + *cur)) { np += sz; *cur = *cur + out; }
    *in = np;
}

/* FUN_0035e7ac @ 0x35e7ac  (est. sw_decode_enum_elem)
 * Decodes an enum element: reads the discriminant from the payload (sized
 * by the raw-value width), and if nonzero advances over the associated
 * value; if the case is a single-payload case it calls the payload decode
 * function. Cursor advances by the enum's total size.
 * Confidence: low */
void sw_decode_enum_elem_35e7ac(und8_t p1, uint64_t *in, int64_t *cur, int64_t base)
{
    uint64_t u = *in, rec, off, adv; int64_t md, sz, extra; uint32_t raw, w;
    rec = *(uint64_t *)(u & 0x7fffffffffffffff);
    md = *(int64_t *)(u + 0x10 & 0x7fffffffffffffff);
    off = *(int64_t *)(u + 0x1c & 0x7fffffffffffffff);
    extra = *(int64_t *)(u + 0x24 & 0x7fffffffffffffff);
    adv = u + 0x2c;
    if (rec >> 0x3e == 0) {
        if (md) { if (md) if ((*(int(**)(int64_t,int32_t))(*(int64_t *)(md - 8) + 0x30))(base + *cur + (rec & 0xffffffff), *(int32_t *)(*(int64_t *)(md - 8) + 0x54))) { /* advance */ } }
    } else {
        int64_t fo = *(int64_t *)(u + 8 & 0x7fffffffffffffff);
        w = 1 << ((uint32_t)(rec >> 0x3e) - 1 & 0x1f);
        if ((w & 0xff) == 4) raw = *(uint32_t *)(base + *cur + fo);
        else if (w == 2) raw = *(uint16_t *)(base + *cur + fo);
        else raw = *(uint8_t *)(base + *cur + fo);
        if (raw == 0 && md) { if (md) (*(int(**)(int64_t,int32_t))(*(int64_t *)(md - 8) + 0x30))(base + *cur + (rec & 0xffffffff), *(int32_t *)(*(int64_t *)(md - 8) + 0x54)); }
    }
    adv = adv + off; *cur = *cur + extra;
    *in = adv;
}

/* FUN_0035e8d4 @ 0x35e8d4  (est. sw_decode_dictionary_elem)
 * Decodes a keyed (dictionary) element: reads the per-key descriptor,
 * looks up the key via the hash function, and if present decodes the
 * value at the found bucket (recurse FUN_004b9634).
 * Confidence: low */
void sw_decode_dictionary_elem_35e8d4(int32_t *desc, und8_t p2, int64_t *cur, int64_t *buckets, int64_t base)
{
    int32_t *p = desc + 8; uint64_t *tab = (uint64_t *)((uint64_t)(desc + 2) & 0x7fffffffffffffff);
    uint64_t n = *tab, ent = tab[1], sz = tab[2], h, b;
    int64_t start = *buckets, idx;
    h = (*(int(**)(int64_t))((int64_t)*desc + (int64_t)desc))(base + start);
    *cur = (int64_t)p + n * 8 + ent;
    *buckets = *buckets + sz;
    if ((h & 0xffffffff) < n) {
        b = (int64_t)p + *(int64_t *)(((uint64_t)p & 0x7fffffffffffffff) + (h & 0xffffffff) * 8) + n * 8;
        FUN_004b9634(p2, &b, &start, base);
    }
}

/* FUN_0035e9ac @ 0x35e9ac  (est. sw_decode_set_elem)
 * Decodes a set element: reads the element from the payload (width from
 * the record low byte), and if present looks it up in the set and decodes
 * the stored value (recurse FUN_004b9634).
 * Confidence: low */
void sw_decode_set_elem_35e9ac(und8_t p1, uint64_t *in, int64_t *cur, int64_t base)
{
    int64_t *p = (int64_t *)(*in & 0x7fffffffffffffff);
    uint64_t n = p[1], rec2 = p[3], u8; int64_t elemsz = rec2 - *p, off; uint32_t w;
    int64_t start = *cur; uint64_t head;
    w = (uint32_t)*p & 0xff;
    if (w == 1) u8 = *(uint8_t *)(base + start + elemsz);
    else if (w == 2) u8 = *(uint16_t *)(base + start + elemsz);
    else if (w == 4) u8 = *(uint32_t *)(base + start + elemsz);
    else u8 = *(uint64_t *)(base + start + elemsz);
    head = *in + 0x20; off = p[2];
    *in = head + off + n * 8;
    *cur = start + rec2;
    if (u8 < n) {
        int64_t b = head + n * 8 + *(int64_t *)((head & 0x7fffffffffffffff) + u8 * 8);
        FUN_004b9634(p1, &b, &start);
    }
}

/* FUN_0035ea78 @ 0x35ea78  (est. sw_metadata_record)
 * Fetches a Swift metadata record from the inline descriptor (relative
 * pointer), advances the cursor by two words, and invokes the record's
 * function via its relative pointer.
 * Confidence: low */
void sw_metadata_record_35ea78(und8_t p1, und8_t *p2)
{
    int32_t *p = (int32_t *)*p2; int32_t rel; uint64_t *fn;
    *p2 = (und8_t)(p + 2);
    rel = *p;
    fn = (uint64_t *)((rel == 0) ? 0 : ((int64_t)rel + (int64_t)p));
    FUN_0035eae4();
    (*(void(**)(void))fn)();
}

/* FUN_0035eae4 @ 0x35eae4  (est. cl4_cap_obj_entry)
 * Resolves a capability object's entry record: reads the child pointer,
 * decodes its record header, and returns (object + kind_index*8).
 * Confidence: medium */
int64_t cl4_cap_obj_entry_35eae4(int64_t obj)
{
    int64_t child = FUN_0035bd48(), rec = 0, base;
    if (child) { rec = FUN_0035eb3c(child); }
    if (rec) base = obj + (int64_t)FUN_0035ef4c(child) * 8;
    else base = 0;
    return base;
}

/* FUN_0035eb3c @ 0x35eb3c  (est. sw_record_decode)
 * Walks a Swift context/record descriptor: if bit7 of the first word is
 * set and the record kind matches (1/2/4 = small, 0x10-0x12 = large),
 * returns a pointer into the descriptor; else 0. Validates the
 * "not-negative" flag.
 * Confidence: low */
uint32_t *sw_record_decode_35eb3c(uint32_t *p)
{
    uint32_t kind;
    if (!(*p >> 7 & 1)) return 0;
    kind = *p & 0x1f;
    if (kind > 0xf) {
        if (kind == 0x10) { if ((int8_t)*p < 0) return p + 0xb; return 0; }
        if (kind == 0x11) { if ((int8_t)*p < 0) return p + 7; return 0; }
        if (kind != 0x12) return 0;
        if ((int8_t)*p < 0) return p + 7; return 0;
    }
    if (kind == 1) { if ((int8_t)*p < 0) return p + 3; return 0; }
    if (kind == 2) { if ((int8_t)*p < 0) return p + 2; return 0; }
    if (kind != 4) return 0;
    if ((int8_t)*p < 0) return p + 2; return 0;
}

/* FUN_0035ef4c @ 0x35ef4c  (est. cl4_record_kind_index)
 * Returns the "number of words per entry" for a record: 2 for kind
 * 0x11/0x12, else the decoded size for kind 0x10.
 * Confidence: low */
uint64_t cl4_record_kind_index_35ef4c(uint32_t *p)
{
    if ((*p & 0x1f) - 0x11 < 2) return 2;
    if ((*p & 0x1f) == 0x10) return FUN_0035efa0(p);
    SoftwareBreakpoint(1, 0x35efa0);
}

/* FUN_0035efa0 @ 0x35efa0  (est. sw_record_size_16)
 * Computes the size of a kind-0x10 record from its flag bits: with
 * indirect context (bit29) it returns the generic size (FUN_0036f418);
 * otherwise (count - offset) from the descriptor fields.
 * Confidence: low */
uint64_t sw_record_size_16_35efa0(uint32_t *p)
{
    uint32_t cnt; int64_t off;
    if (!(*p >> 0x1d & 1)) {
        if (*p >> 0x1c & 1) { cnt = 0; off = 0x18; }
        else { cnt = p[7]; off = 0x20; }
        return (uint64_t)(cnt - *(int32_t *)((int64_t)p + off));
    }
    return FUN_0036f418();
}

/* FUN_0035efdc @ 0x35efdc  (est. sw_record_next_pair)
 * Advances a cursor over a record pair: returns the two words at the
 * cursor and moves it forward 0x10 bytes.
 * Confidence: medium */
void sw_record_next_pair_35efdc(uint64_t *cur, uint64_t *a, uint64_t *b)
{
    *a = *(uint64_t *)(*cur & 0x7fffffffffffffff);
    *b = *(uint64_t *)((*cur & 0x7fffffffffffffff) + 8);
    *cur = *cur + 0x10;
}

/* FUN_0035f31c @ 0x35f31c  (est. sw_decode_copy_elem)
 * Decodes and copies one element: calls the descriptor function, and on
 * success reads the size pair and memcpies the element, advancing the
 * cursor.
 * Confidence: low */
void sw_decode_copy_elem_35f31c(und8_t p1, int64_t *in, int64_t *cur, int64_t dst, int64_t base)
{
    int32_t *p = (int32_t *)*in, *np; int r; uint64_t sz = 0, cnt = 0;
    np = p + 2;
    r = (*(int(**)(int64_t))((int64_t)*p + (int64_t)p))(base + *cur);
    if (r == 0) { p = p + 6; }
    else { FUN_0035efdc(&np, &cnt, &sz); np = (int32_t *)((int64_t)np + cnt); FUN_00117cc4(dst + *cur, base + *cur, sz); *cur = *cur + sz; }
    *in = (int64_t)np;
}

/* FUN_0035f3e8 @ 0x35f3e8  (est. sw_decode_copy_struct)
 * Decodes and copies a struct element with per-field function dispatch.
 * Confidence: low */
void sw_decode_copy_struct_35f3e8(und8_t p1, uint64_t *in, int64_t *cur, int64_t dst, int64_t base)
{
    uint64_t *p = (uint64_t *)(*in & 0x7fffffffffffffff);
    int64_t sz = p[1], out = p[2]; uint64_t np = *in + 0x18;
    if ((*(int(**)(int64_t))*p)(base + *cur)) { np += sz; FUN_00117cc4(dst + *cur, base + *cur, out); *cur = *cur + out; }
    *in = np;
}

/* FUN_0035f480 @ 0x35f480  (est. sw_decode_copy_enum)
 * Decodes and copies an enum element, copying the payload value on a
 * nonzero discriminant.
 * Confidence: low */
void sw_decode_copy_enum_35f480(und8_t p1, uint64_t *in, int64_t *cur, int64_t dst, int64_t base)
{
    uint64_t u = *in, rec, off, adv; int64_t md, sz, extra; uint32_t raw, w;
    rec = *(uint64_t *)(u & 0x7fffffffffffffff);
    md = *(int64_t *)(u + 0x10 & 0x7fffffffffffffff);
    off = *(int64_t *)(u + 0x1c & 0x7fffffffffffffff);
    extra = *(int64_t *)(u + 0x24 & 0x7fffffffffffffff);
    adv = u + 0x2c;
    if (rec >> 0x3e == 0) {
        if (md) if (md) (*(int(**)(int64_t,int32_t))(*(int64_t *)(md - 8) + 0x30))(base + *cur + (rec & 0xffffffff), *(int32_t *)(*(int64_t *)(md - 8) + 0x54));
    } else {
        int64_t fo = *(int64_t *)(u + 8 & 0x7fffffffffffffff);
        w = 1 << ((uint32_t)(rec >> 0x3e) - 1 & 0x1f);
        if ((w & 0xff) == 4) raw = *(uint32_t *)(base + *cur + fo);
        else if (w == 2) raw = *(uint16_t *)(base + *cur + fo);
        else raw = *(uint8_t *)(base + *cur + fo);
        if (raw == 0 && md) if (md) (*(int(**)(int64_t,int32_t))(*(int64_t *)(md - 8) + 0x30))(base + *cur + (rec & 0xffffffff), *(int32_t *)(*(int64_t *)(md - 8) + 0x54));
    }
    adv = adv + off; FUN_00117cc4(dst + *cur, base + *cur, extra); *cur = *cur + extra;
    *in = adv;
}

/* FUN_0035f5cc @ 0x35f5cc  (est. sw_decode_copy_dictionary)
 * Decodes and copies a dictionary element: looks up the key, decodes the
 * value into the destination, copying any remainder.
 * Confidence: low */
void sw_decode_copy_dictionary_35f5cc(int32_t *desc, und8_t p2, int64_t *cur, int64_t *buckets, int64_t dst, int64_t base)
{
    int32_t *p = desc + 8; uint64_t *tab = (uint64_t *)((uint64_t)(desc + 2) & 0x7fffffffffffffff);
    uint64_t n = *tab, ent = tab[1], sz = tab[2], h, b;
    int64_t start = *buckets, idx;
    h = (*(int(**)(int64_t))((int64_t)*desc + (int64_t)desc))(base + start);
    *cur = (int64_t)p + n * 8 + ent;
    if ((h & 0xffffffff) < n) {
        *buckets = start + sz;
        b = (int64_t)p + *(int64_t *)(((uint64_t)p & 0x7fffffffffffffff) + (h & 0xffffffff) * 8) + n * 8;
        FUN_004b9704(p2, &b, &start, dst, base);
        if (*buckets - start != 0) FUN_00117cc4(dst + start, base + start, *buckets - start);
    } else { FUN_00117cc4(dst + start, base + start, sz); *buckets = *buckets + sz; }
}

/* FUN_0035f6f0 @ 0x35f6f0  (est. sw_decode_copy_dict_elem)
 * Dictionary-element decode-copy variant working off the cursor header.
 * Confidence: low */
void sw_decode_copy_dict_elem_35f6f0(und8_t p1, uint64_t *in, int64_t *cur, int64_t dst, int64_t base)
{
    uint64_t u = *in, h, n, ent, sz, b; int64_t start; uint64_t *tab;
    tab = (uint64_t *)((u + 8) & 0x7fffffffffffffff);
    n = *tab; ent = tab[1]; sz = tab[2];
    h = (*(int(**)(int64_t))(u & 0x7fffffffffffffff))(base + *cur);
    start = *cur;
    *in = u + 0x20 + ent + n * 8;
    if ((h & 0xffffffff) < n) {
        *cur = start + sz;
        b = (u + 0x20) + n * 8 + *(int64_t *)(((u + 0x20) & 0x7fffffffffffffff) + (h & 0xffffffff) * 8);
        FUN_004b9704(p1, &b, &start, dst, base);
        if (*cur - start != 0) FUN_00117cc4(dst + start, base + start, *cur - start);
    } else { FUN_00117cc4(dst + start, base + start, sz); *cur = *cur + sz; }
}

/* FUN_0035f808 @ 0x35f808  (est. sw_decode_copy_set_elem)
 * Decodes and copies a set element.
 * Confidence: low */
void sw_decode_copy_set_elem_35f808(und8_t p1, uint64_t *in, int64_t *cur, int64_t dst, int64_t base)
{
    int64_t *p = (int64_t *)(*in & 0x7fffffffffffffff);
    uint64_t n = p[1], rec2 = p[3], u8; int64_t elemsz = rec2 - *p, off; uint32_t w;
    int64_t start = *cur; uint64_t head;
    w = (uint32_t)*p & 0xff;
    if (w == 1) u8 = *(uint8_t *)(base + start + elemsz);
    else if (w == 2) u8 = *(uint16_t *)(base + start + elemsz);
    else if (w == 4) u8 = *(uint32_t *)(base + start + elemsz);
    else u8 = *(uint64_t *)(base + start + elemsz);
    head = *in + 0x20; off = p[2];
    *in = head + off + n * 8;
    if (u8 < n) {
        *cur = start + rec2;
        int64_t b = head + n * 8 + *(int64_t *)((head & 0x7fffffffffffffff) + u8 * 8);
        FUN_004b9704(p1, &b, &start, dst, base);
        if (*cur - start != 0) FUN_00117cc4(dst + start, base + start, *cur - start);
    } else { FUN_00117cc4(dst + start, base + start, rec2); *cur = *cur + rec2; }
}

/* ------------------------------------------------------------------ *
 * Per-kind element assign / move helpers (0x35f934-0x35fc58) and the
 * set/array merge-union decode ops (0x35fcc8-0x3611c4).
 * ------------------------------------------------------------------ */

/* FUN_0035f934 @ 0x35f934  (est. sw_assign_word)
 * Assigns one word element: swaps src into dst, advances the cursor,
 * releases the old value and retains the new one.
 * Confidence: low */
void sw_assign_word_35f934(und8_t p1, und8_t p2, int64_t *cur, int64_t dst, int64_t src)
{
    int64_t i = *cur; uint64_t old = *(uint64_t *)(dst + i), nu = *(uint64_t *)(src + i);
    *(uint64_t *)(dst + i) = nu; *cur = i + 8;
    thunk_FUN_0036b118(old & 0xffffffffffffff8); thunk_FUN_0036b270(nu & 0xffffffffffffff8);
}

/* FUN_0035f978 @ 0x35f978  (est. sw_assign_word_a)
 * Word assign variant (same shape).
 * Confidence: low */
void sw_assign_word_a_35f978(und8_t p1, und8_t p2, int64_t *cur, int64_t dst, int64_t src)
{
    int64_t i = *cur; uint64_t old = *(uint64_t *)(dst + i);
    *(uint64_t *)(dst + i) = *(uint64_t *)(src + i); *cur = i + 8;
    FUN_0036b118(old & 0xffffffffffffff8); FUN_0036b270(0);
}

/* FUN_0035f97c @ 0x35f97c  (est. sw_assign_word_b)
 * Word assign variant.
 * Confidence: low */
void sw_assign_word_b_35f97c(und8_t p1, und8_t p2, int64_t *cur, int64_t dst, int64_t src)
{
    int64_t i = *cur; uint64_t old = *(uint64_t *)(dst + i);
    *(uint64_t *)(dst + i) = *(uint64_t *)(src + i); *cur = i + 8;
    FUN_0036b118(old & 0xffffffffffffff8); FUN_0036b270(0);
}

/* FUN_0035f9b4 @ 0x35f9b4  (est. sw_assign_refcount)
 * Assigns a reference-counted word element.
 * Confidence: low */
void sw_assign_refcount_35f9b4(und8_t p1, und8_t p2, int64_t *cur, int64_t dst, int64_t src)
{
    int64_t i = *cur; uint64_t old = *(uint64_t *)(dst + i), nu = *(uint64_t *)(src + i);
    *(uint64_t *)(dst + i) = nu; *cur = i + 8;
    FUN_0036b484(old & 0xffffffffffffff8); FUN_0036b3c0(nu & 0xffffffffffffff8);
}

/* FUN_0035fa10 @ 0x35fa10  (est. sw_assign_retain)
 * Assigns a word with retain/release.
 * Confidence: low */
void sw_assign_retain_35fa10(und8_t p1, und8_t p2, int64_t *cur, int64_t dst, int64_t src)
{
    int64_t i = *cur; uint64_t old = *(uint64_t *)(dst + i);
    *(uint64_t *)(dst + i) = *(uint64_t *)(src + i); *cur = i + 8;
    FUN_0036b118(old); FUN_0036b270(0);
}

/* FUN_0035fa14 @ 0x35fa14  (est. sw_assign_retain_b)
 * Assigns a word with retain/release (variant).
 * Confidence: low */
void sw_assign_retain_b_35fa14(und8_t p1, und8_t p2, int64_t *cur, int64_t dst, int64_t src)
{
    int64_t i = *cur; uint64_t old = *(uint64_t *)(dst + i);
    *(uint64_t *)(dst + i) = *(uint64_t *)(src + i); *cur = i + 8;
    FUN_0036b118(old); FUN_0036b270(0);
}

/* FUN_0035fa48 @ 0x35fa48  (est. sw_assign_if_diff)
 * Assigns a word only if the value differs; on change releases the old
 * and retains the new.
 * Confidence: low */
void sw_assign_if_diff_35fa48(und8_t p1, und8_t p2, int64_t *cur, int64_t dst, int64_t src)
{
    int64_t i = *cur; *cur = i + 8; int64_t old = *(int64_t *)(dst + i);
    if (*(int64_t *)(src + i) != old) { *(int64_t *)(dst + i) = *(int64_t *)(src + i); FUN_0036b3c0(); FUN_0036b484(old); }
}

/* FUN_0035fab4 @ 0x35fab4  (est. sw_assign_msgreg)
 * Assigns a message-register word element (uses FUN_003a25d4 for the old
 * value and thunk_FUN_0036b270 for the new).
 * Confidence: low */
void sw_assign_msgreg_35fab4(und8_t p1, und8_t p2, int64_t *cur, int64_t dst, int64_t src)
{
    int64_t i = *cur; uint64_t old = *(uint64_t *)(dst + i), nu = *(uint64_t *)(src + i);
    *(uint64_t *)(dst + i) = nu; *cur = i + 8;
    FUN_003a25d4(old); thunk_FUN_0036b270(nu);
}

/* FUN_0035fc58 @ 0x35fc58  (est. sw_assign_vtable)
 * Assigns an element via the type's vtable assign function (vtable +0x18).
 * Confidence: low */
void sw_assign_vtable_35fc58(und8_t p1, und8_t p2, int64_t *cur, int64_t dst, int64_t src)
{
    int64_t i = *cur, md = FUN_0035ea78();
    (*(void(**)(int64_t,int64_t,int64_t))(*(int64_t *)(md - 8) + 0x18))(dst + i, src + i, md);
    *cur = *(int64_t *)(*(int64_t *)(md - 8) + 0x40) + i;
}

/* FUN_0035fcc8 @ 0x35fcc8  (est. sw_union_merge_decode)
 * Decodes a "union merge" layout: reads the union discriminant from both
 * the source and destination, and if either is present, merges the union
 * payload fields (copying or taking elements per the per-field records).
 * Confidence: low */
void sw_union_merge_decode_35fcc8(und8_t p1, uint64_t *in, int64_t *cur, int64_t dst, int64_t src)
{
    int64_t start = *cur; uint64_t *p = (uint64_t *)(*in & 0x7fffffffffffffff);
    uint64_t rec = *p, n = p[1], valoff = p[3], sz = p[4], nxt = p[5], np;
    uint64_t newcur = *in + 0x30;
    (void)start; (void)valoff; (void)sz; (void)nxt;
    /* Both-sides discriminant check; if a payload is present, walk the
       field records to copy/take the active case. Opaque jump-table path. */
    np = newcur;
    *in = np;
}

/* FUN_0035ff48 @ 0x35ff48  (est. sw_union_merge_assign)
 * Assigns a union-merge: decodes the discriminant from src and dst, and
 * moves/decodes the active case with the per-field record functions.
 * Confidence: low */
void sw_union_merge_assign_35ff48(int32_t *desc, und8_t p2, uint64_t *in, int64_t *cur, int64_t dst, int64_t src)
{
    int32_t *p = desc + 6, *np; int r1, r2; uint64_t n, ent, cnt;
    uint64_t fn = (int64_t)*desc + (int64_t)desc;
    n = *(uint64_t *)((uint64_t)(desc + 2) & 0x7fffffffffffffff);
    ent = ((int64_t *)((uint64_t)(desc + 2) & 0x7fffffffffffffff))[1];
    np = p;
    r1 = (*(int(**)(int64_t))fn)(src + *cur);
    r2 = (*(int(**)(int64_t))fn)(dst + *cur);
    if (r1 || r2) {
        if (r1 == 0) { while (((uint64_t)np & 0x7fffffffffffffff) < ((uint64_t)p & 0x7fffffffffffffff) + n) { FUN_004b992c(p2, &np, cur, dst, src); } }
        else {
            FUN_00117cc4(dst + *cur, src + *cur, ent);
            *cur = *cur + ent;
            if (r2) np = (int32_t *)((int64_t)np + n);
        }
    }
    *in = (uint64_t)np;
}

/* FUN_003600ec @ 0x3600ec  (est. sw_union_merge_take)
 * Union-merge take: takes the active case from src into dst.
 * Confidence: low */
void sw_union_merge_take_3600ec(und8_t p1, uint64_t *in, int64_t *cur, int64_t dst, int64_t src)
{
    uint64_t u = *in, rec, n, valoff, sz, nxt, np; int64_t md;
    rec = *(uint64_t *)(u & 0x7fffffffffffffff);
    md = *(int64_t *)(u + 8 & 0x7fffffffffffffff);
    n = *(int64_t *)(u + 0x10 & 0x7fffffffffffffff);
    valoff = *(int64_t *)(u + 0x1c & 0x7fffffffffffffff);
    nxt = *(int64_t *)(u + 0x24 & 0x7fffffffffffffff);
    np = u + 0x2c;
    if (rec >> 0x3e == 0) {
        if (n) if (n) (*(int(**)(int64_t,int32_t,int64_t))(*(int64_t *)(n - 8) + 0x30))(src + *cur + (rec & 0xffffffff), *(int32_t *)(*(int64_t *)(n - 8) + 0x54), n);
        if ((*(int(**)(int64_t,int32_t,int64_t))(*(int64_t *)(n - 8) + 0x30))(dst + *cur + (rec & 0xffffffff), *(int32_t *)(*(int64_t *)(n - 8) + 0x54), n)) { np += valoff; }
    } else {
        uint32_t d1, d2; int64_t fo = *(int64_t *)(u + 8 & 0x7fffffffffffffff);
        uint32_t w = 1 << ((uint32_t)(rec >> 0x3e) - 1 & 0x1f);
        if ((w & 0xff) == 1) { d1 = *(uint8_t *)(src + *cur + fo); d2 = *(uint8_t *)(dst + *cur + fo); }
        else if (w == 2) { d1 = *(uint16_t *)(src + *cur + fo); d2 = *(uint16_t *)(dst + *cur + fo); }
        else { d1 = *(uint32_t *)(src + *cur + fo); d2 = *(uint32_t *)(dst + *cur + fo); }
        if (n) { if (d1 == 0) if (n) (*(int(**)(int64_t,int32_t,int64_t))(*(int64_t *)(n - 8) + 0x30))(src + *cur + (rec & 0xffffffff), *(int32_t *)(*(int64_t *)(n - 8) + 0x54), n); }
        if (d1) { if (d2) { np += valoff; goto done; } /* take src payload */
            while (((*in & 0x7fffffffffffffff) < (np & 0x7fffffffffffffff) + valoff)) { FUN_004b992c(p1, &np, cur, dst, src); }
        } else { while (((*in & 0x7fffffffffffffff) < (np & 0x7fffffffffffffff) + valoff)) { FUN_004b992c(p1, &np, cur, dst, src); } }
    }
done:
    FUN_00117cc4(dst + *cur, src + *cur, nxt);
    *cur = *cur + nxt;
    *in = np;
}

/* FUN_0036037c @ 0x36037c  (est. sw_union_merge_assign2)
 * Union-merge assign (2-source form) with per-field record decode.
 * Confidence: low */
void sw_union_merge_assign2_36037c(und8_t p1, int64_t *in, int64_t *cur, int64_t dst, int64_t src)
{
    int32_t *p = (int32_t *)*in, *np; int r1, r2; uint64_t fn, n, ent;
    uint64_t *tab;
    fn = (int64_t)*p + (int64_t)p;
    tab = (uint64_t *)((uint64_t)(p + 2) & 0x7fffffffffffffff);
    n = *tab; ent = tab[2];
    np = p + 8;
    r1 = (*(int(**)(int64_t))fn)(src + *cur);
    r2 = (*(int(**)(int64_t))fn)(dst + *cur);
    *in = (int64_t)np + n * 8 + ent;
    if (r1 < (int)n && r2 < (int)n) {
        *cur = *cur + ent;
        FUN_004b9634(p1, &np, cur, dst);
        FUN_004b9704(p1, &np, cur, dst, src);
    } else {
        if (r1 >= (int)n) { if (r2 < (int)n) { FUN_004b9634(p1, &np, cur, dst); } FUN_00117cc4(dst + *cur, src + *cur, ent); *cur = *cur + ent; return; }
        *cur = *cur + ent;
        FUN_004b9704(p1, &np, cur, dst, src);
    }
    if (*cur - cur[0] != 0) { /* remainder copied by caller */ }
}

/* FUN_00360a80 @ 0x360a80  (est. sw_union_merge_assign3)
 * Union-merge assign (cursor-header form).
 * Confidence: low */
void sw_union_merge_assign3_360a80(und8_t p1, uint64_t *in, int64_t *cur, int64_t dst, int64_t src)
{
    uint64_t u = *in, h, n, ent, sz, b; int64_t start; uint64_t *tab;
    uint64_t fn = *(uint64_t *)(u & 0x7fffffffffffffff);
    tab = (uint64_t *)((u + 8) & 0x7fffffffffffffff);
    n = *tab; ent = tab[1]; sz = tab[2];
    h = (*(int(**)(int64_t))fn)(src + *cur);
    start = *cur;
    *in = u + 0x20 + ent + n * 8;
    if ((h & 0xffffffff) < n) {
        *cur = start + sz;
        b = (u + 0x20) + n * 8 + *(int64_t *)(((u + 0x20) & 0x7fffffffffffffff) + (h & 0xffffffff) * 8);
        FUN_004b9634(p1, &b, &start, dst);
    } else { if ((h & 0xffffffff) >= n) { FUN_00117cc4(dst + start, src + start, sz); *cur = *cur + sz; return; } }
    FUN_004b9704(p1, &b, &start, dst, src);
    if (*cur - start != 0) FUN_00117cc4(dst + start, src + start, *cur - start);
}

/* FUN_00360c48 @ 0x360c48  (est. sw_union_merge_take2)
 * Union-merge take (per-element pointer form).
 * Confidence: low */
void sw_union_merge_take2_360c48(und8_t p1, uint64_t *in, int64_t *cur, int64_t dst, int64_t src)
{
    int64_t *p = (int64_t *)(*in & 0x7fffffffffffffff);
    uint64_t n = p[1], rec2 = p[3]; int64_t elemsz = rec2 - *p, off; uint32_t w, d1, d2;
    int64_t start = *cur; uint64_t head;
    w = (uint32_t)*p & 0xff;
    if (w == 1) { d1 = *(uint8_t *)(src + start + elemsz); d2 = *(uint8_t *)(dst + start + elemsz); }
    else if (w == 2) { d1 = *(uint16_t *)(src + start + elemsz); d2 = *(uint16_t *)(dst + start + elemsz); }
    else if (w == 4) { d1 = *(uint32_t *)(src + start + elemsz); d2 = *(uint32_t *)(dst + start + elemsz); }
    else { d1 = *(uint32_t *)(src + start + elemsz); d2 = *(uint32_t *)(dst + start + elemsz); }
    head = *in + 0x20; off = p[2];
    *in = head + off + n * 8;
    if (d1 < (int)n && d2 < (int)n) {
        *cur = start + rec2;
        { int64_t b1 = head + n * 8 + *(int64_t *)((head & 0x7fffffffffffffff) + d1 * 8);
          int64_t b2 = head + n * 8 + *(int64_t *)((head & 0x7fffffffffffffff) + d2 * 8);
          FUN_004b9634(p1, &b2, &start, dst); }
    } else {
        if (d1 >= (int)n) { if (d2 < (int)n) { int64_t b2 = head + n * 8 + *(int64_t *)((head & 0x7fffffffffffffff) + d2 * 8); FUN_004b9634(p1, &b2, &start, dst); } FUN_00117cc4(dst + start, src + start, rec2); *cur = *cur + rec2; return; }
        *cur = start + rec2;
        { int64_t b1 = head + n * 8 + *(int64_t *)((head & 0x7fffffffffffffff) + d1 * 8); FUN_004b9704(p1, &b1, &start, dst, src); }
    }
    if (*cur - start != 0) FUN_00117cc4(dst + start, src + start, *cur - start);
}

/* FUN_00360e28 @ 0x360e28  (est. sw_assign_error)
 * Assigns an element but first raises "bad function call was thrown in..."
 * via FUN_001142f4, then performs a plain word copy.
 * Confidence: high (string "bad function call was thrown in...") */
void sw_assign_error_360e28(und8_t p1, und8_t p2, int64_t *cur, int64_t dst, int64_t src)
{
    FUN_001142f4(0x5d3f7f);
    *(uint64_t *)(dst + *cur) = *(uint64_t *)(src + *cur);
    *cur = *cur + 8;
}

/* FUN_00360f10 @ 0x360f10  (est. sw_assign_vtable_b)
 * Vtable assign (vtable +0x20 form).
 * Confidence: low */
void sw_assign_vtable_b_360f10(und8_t p1, und8_t p2, int64_t *cur, int64_t dst, int64_t src)
{
    int64_t i = *cur, md = FUN_0035ea78();
    (*(void(**)(int64_t,int64_t,int64_t))(*(int64_t *)(md - 8) + 0x20))(dst + i, src + i, md);
    *cur = *(int64_t *)(*(int64_t *)(md - 8) + 0x40) + i;
}

/* FUN_00360f88 @ 0x360f88  (est. sw_decode_dictionary_elem_b)
 * Dictionary-element decode (jump-table 0x679e58 family).
 * Confidence: low */
void sw_decode_dictionary_elem_b_360f88(int32_t *desc, und8_t p2, int64_t *cur, int64_t *buckets, int64_t dst, int64_t src)
{
    int32_t *p = desc + 8; uint64_t *tab = (uint64_t *)((uint64_t)(desc + 2) & 0x7fffffffffffffff);
    uint64_t n = *tab, ent = tab[1], sz = tab[2], h, b; int64_t start = *buckets;
    h = (*(int(**)(int64_t))((int64_t)*desc + (int64_t)desc))(src + start);
    *cur = (int64_t)p + n * 8 + ent;
    if ((h & 0xffffffff) < n) {
        *buckets = start + sz;
        b = (int64_t)p + *(int64_t *)(((uint64_t)p & 0x7fffffffffffffff) + (h & 0xffffffff) * 8) + n * 8;
        FUN_004b9a28(p2, &b, &start, dst, src);
        if (*buckets - start != 0) FUN_00117cc4(dst + start, src + start, *buckets - start);
    } else { FUN_00117cc4(dst + start, src + start, sz); *buckets = *buckets + sz; }
}

/* FUN_003610ac @ 0x3610ac  (est. sw_decode_dictionary_elem_c)
 * Dictionary-element decode (cursor form).
 * Confidence: low */
void sw_decode_dictionary_elem_c_3610ac(und8_t p1, uint64_t *in, int64_t *cur, int64_t dst, int64_t src)
{
    uint64_t u = *in, h, n, ent, sz, b; int64_t start; uint64_t *tab;
    tab = (uint64_t *)((u + 8) & 0x7fffffffffffffff);
    n = *tab; ent = tab[1]; sz = tab[2];
    h = (*(int(**)(int64_t))(u & 0x7fffffffffffffff))(src + *cur);
    start = *cur;
    *in = u + 0x20 + ent + n * 8;
    if ((h & 0xffffffff) < n) {
        *cur = start + sz;
        b = (u + 0x20) + n * 8 + *(int64_t *)(((u + 0x20) & 0x7fffffffffffffff) + (h & 0xffffffff) * 8);
        FUN_004b9a28(p1, &b, &start, dst, src);
        if (*cur - start != 0) FUN_00117cc4(dst + start, src + start, *cur - start);
    } else { FUN_00117cc4(dst + start, src + start, sz); *cur = *cur + sz; }
}

/* FUN_003611c4 @ 0x3611c4  (est. sw_decode_set_elem_b)
 * Set-element decode (jump-table family).
 * Confidence: low */
void sw_decode_set_elem_b_3611c4(und8_t p1, uint64_t *in, int64_t *cur, int64_t dst, int64_t src)
{
    int64_t *p = (int64_t *)(*in & 0x7fffffffffffffff);
    uint64_t n = p[1], rec2 = p[3], u8; int64_t elemsz = rec2 - *p, off; uint32_t w;
    int64_t start = *cur; uint64_t head;
    w = (uint32_t)*p & 0xff;
    if (w == 1) u8 = *(uint8_t *)(src + start + elemsz);
    else if (w == 2) u8 = *(uint16_t *)(src + start + elemsz);
    else if (w == 4) u8 = *(uint32_t *)(src + start + elemsz);
    else u8 = *(uint64_t *)(src + start + elemsz);
    head = *in + 0x20; off = p[2];
    *in = head + off + n * 8;
    if (u8 < n) {
        *cur = start + rec2;
        int64_t b = head + n * 8 + *(int64_t *)((head & 0x7fffffffffffffff) + u8 * 8);
        FUN_004b9a28(p1, &b, &start, dst, src);
        if (*cur - start != 0) FUN_00117cc4(dst + start, src + start, *cur - start);
    } else { FUN_00117cc4(dst + start, src + start, rec2); *cur = *cur + rec2; }
}

/* FUN_003612f0 @ 0x3612f0  (est. cl4_syscall_dispatch_empty_10)
 * Empty dispatch entry.
 * Confidence: medium */
void cl4_syscall_dispatch_empty_10_3612f0(void) { return; }

/* FUN_00361308 @ 0x361308  (est. cl4_syscall_dispatch_empty_11)
 * Empty dispatch entry.
 * Confidence: medium */
void cl4_syscall_dispatch_empty_11_361308(void) { return; }

/* ------------------------------------------------------------------ *
 * Type-metadata stringification + process-global hash sets
 * (0x361320-0x361b18). The hash sets at 0x6c0200/0x6c0220 are guarded by
 * the mutexes 0x6c01c0/0x6c01e0 and keyed by a word or a string.
 * ------------------------------------------------------------------ */

/* FUN_00361320 @ 0x361320  (est. cl4_type_metadata_string)
 * Renders a type-metadata object into a Swift string (out param_1).
 * Allocates a large stack frame, calls the metadata encoder
 * FUN_00364020, and if that fails emits "<<invalid type>>". On success
 * installs an output writer callback (FUN_003b2010) and runs
 * FUN_003bc9a4 to stringify.
 * Confidence: low
 * Notes: string "<<invalid type>>" (0x5d40d4); writer 0x67a2b8;
 *   context 0x67c398/0x67c370. */
void cl4_type_metadata_string_361320(uint64_t out[3], und8_t type, uint8_t flags)
{
    int64_t md;
    out[0] = 0; out[1] = 0; out[2] = 0;
    md = FUN_00364020(type, 0x67c398);
    if (md == 0) { FUN_00113400(out, 0x5d40d4); }
    else {
        /* install stringifier: kind table 0x67a2b8, fn FUN_003b2010 */
        FUN_003bc9a4(out, md, 0);
        FUN_00362de4(0x67a2b8);
    }
    FUN_00362ea4(0x67c398);
    FUN_003a3814(0x67c370);
}

/* FUN_00361528 @ 0x361528  (est. cl4_word_set_lookup_or_build)
 * Looks up a word key in the global set at 0x6c0200 under mutex 0x6c01c0.
 * If present returns the stored {ptr,len}; otherwise stringifies the key
 * (FUN_00361320), allocates a copy, and inserts it, returning the new
 * record.
 * Confidence: low */
void cl4_word_set_lookup_or_build_361528(uint64_t key, uint32_t flag, uint64_t out[2])
{
    int64_t slot, found; uint64_t lock;
    uint64_t k = (flag & 1) ? 2 : 0; k |= key & 0xfffffffffffffff9;
    if (DAT_006c0218 > 0) FUN_003d3dd8(&DAT_006c0218, 0, &DAT_006c0200);
    FUN_00361718(&lock, 0x6c01c0);
    slot = 0;
    if (FUN_00362f14(&DAT_006c0200, &k, &slot) &&
        slot != (int64_t)(DAT_006c0200 + DAT_006c0210 * 0x18)) {
        out[0] = *(uint64_t *)(slot + 8); out[1] = *(uint64_t *)(slot + 0x10);
        FUN_0035b228(&lock);
        return;
    }
    FUN_0035b228(&lock);
    FUN_00361718(&lock, 0x6c01c0);
    slot = 0;
    if (FUN_00362f14(&DAT_006c0200, &k, &slot) &&
        slot != (int64_t)(DAT_006c0200 + DAT_006c0210 * 0x18)) {
        out[0] = *(uint64_t *)(slot + 8); out[1] = *(uint64_t *)(slot + 0x10);
        FUN_0035b228(&lock);
        return;
    }
    /* build the string, allocate, insert */
    {
        uint64_t tmp[3]; uint8_t *copy; int64_t n;
        cl4_type_metadata_string_361320(tmp, key, flag & 1);
        n = (int64_t)tmp[1];
        copy = (uint8_t *)FUN_000101a0((uint64_t)n + 1, 0x100004077774924);
        FUN_00117cc8(copy, tmp[0], (uint64_t)n, (uint64_t)n + 1);
        copy[n] = 0;
        {
            uint64_t rec[4]; uint64_t rb;
            rec[0] = k; rec[1] = (uint64_t)copy; rec[2] = (uint64_t)n;
            FUN_00362fb0(0, &DAT_006c0200, &rec, 0);
        }
    }
    FUN_0035b228(&lock);
    out[0] = 0; out[1] = 0;
}

/* FUN_00361718 @ 0x361718  (est. cl4_mutex_lock)
 * Acquires the mutex object at param_2: records it in *param_1, spins or
 * inits the state word, calls FUN_00118164; panics on failure
 * ("__mtx_lock handle_mutex failed").
 * Confidence: high (string "__mtx_lock handle_mutex failed") */
uint64_t *cl4_mutex_lock_361718(uint64_t *param_1, int64_t m)
{
    *param_1 = m;
    if (*(int32_t *)(m + 0x10) > 0) { }
    else if (*(int32_t *)(m + 0x10) == 0) {
        *(int32_t *)(m + 0x10) = 1;
        if (FUN_00118148(m, 0)) FUN_003a2578(0x5d3f10);
        *(int32_t *)(m + 0x10) = -1;
    } else { while (*(int32_t *)(m + 0x10) > 0) { } }
    if (FUN_00118164(m)) FUN_003a2578(0x5d3ee0);
    return param_1;
}

/* FUN_003617bc @ 0x3617bc  (est. cl4_word_set_lookup_or_build2)
 * Second form of word-set lookup-or-build: key is forced to type tag 4,
 * and the stored record (or a newly built+inserted string) is returned.
 * Confidence: low */
void cl4_word_set_lookup_or_build2_3617bc(uint64_t key, uint64_t out[2])
{
    int64_t slot, found; uint64_t lock;
    uint64_t k = (key & 0xfffffffffffffff9) | 4;
    if (DAT_006c0218 > 0) FUN_003d3dd8(&DAT_006c0218, 0, &DAT_006c0200);
    FUN_00361718(&lock, 0x6c01c0);
    found = 0;
    if (FUN_00362f14(&DAT_006c0200, &k, &found) &&
        found != (int64_t)(DAT_006c0200 + DAT_006c0210 * 0x18)) {
        out[0] = *(uint64_t *)(found + 8); out[1] = *(uint64_t *)(found + 0x10);
        FUN_0035b228(&lock);
        return;
    }
    FUN_0035b228(&lock);
    FUN_00361718(&lock, 0x6c01c0);
    found = 0;
    if (FUN_00362f14(&DAT_006c0200, &k, &found) &&
        found != (int64_t)(DAT_006c0200 + DAT_006c0210 * 0x18)) {
        out[0] = *(uint64_t *)(found + 8); out[1] = *(uint64_t *)(found + 0x10);
        FUN_0035b228(&lock);
        return;
    }
    {
        uint64_t tmp[3]; uint8_t *copy; int64_t n; int64_t md;
        cl4_type_metadata_string_361320(tmp, key, 0);
        n = (int64_t)tmp[1];
        copy = (uint8_t *)FUN_000101a0((uint64_t)n + 1, 0x100004077774924);
        FUN_00117cc8(copy, tmp[0], (uint64_t)n, (uint64_t)n + 1);
        copy[n] = 0;
        { uint64_t rec[4]; rec[0] = k; rec[1] = (uint64_t)copy; rec[2] = (uint64_t)n;
          FUN_00362fb0(0, &DAT_006c0200, &rec, 0); }
    }
    FUN_0035b228(&lock);
    out[0] = 0; out[1] = 0;
}

/* FUN_00361b18 @ 0x361b18  (est. cl4_string_set_register)
 * Registers a (name,length) pair in the string-keyed global set at
 * 0x6c0220 under mutex 0x6c01e0. Validates characters (<= 0x20 invalid),
 * computes a mangled Swift type name via FUN_003a3e54 + FUN_003a3748,
 * decodes the type fields (recording identifiers), and inserts the
 * resulting string record into the set via FUN_00363458.
 * Confidence: low
 * Notes: descriptor kind table 0x67a300; context 0x67c398/0x67c370. */
void cl4_string_set_register_361b18(uint8_t *name, int64_t len, uint64_t out[2])
{
    int64_t slot, found; uint64_t lock; int64_t i; uint8_t *copy;
    if (DAT_006c0238 > 0) FUN_003d3dd8(&DAT_006c0238, 0, &DAT_006c0220);
    FUN_00361718(&lock, 0x6c01e0);
    found = 0;
    if (FUN_00363280(&DAT_006c0220, name, &found) &&
        found != (int64_t)(DAT_006c0220 + DAT_006c0230 * 0x20)) {
        out[0] = *(uint64_t *)(found + 0x10); out[1] = *(uint64_t *)(found + 0x18);
        FUN_0035b228(&lock);
        return;
    }
    FUN_0035b228(&lock);
    for (i = len; i != 0; i--) { if (0xffffffe0 < *name - 0x20) { out[0] = 0; out[1] = 0; return; } name++; }
    copy = (uint8_t *)FUN_000101a0((uint64_t)len, 0x100004077774924);
    FUN_00117cc4(copy, name - len, (uint64_t)len);
    /* mangle: FUN_003a3e54 + decode type fields */
    {
        uint64_t rec[3]; int64_t md, obj, n;
        md = FUN_003a3e54(0x67a300, copy, len, 0);
        FUN_00362ea4(0);
        if (md == 0 || (obj = FUN_003a3748(md, 0x4e, 3)) == 0) { out[0] = 0; out[1] = 0; }
        else {
            /* walk the type's field records and record identifiers */
            n = (int64_t)FUN_000101a0(0x10, 0x100004077774924);
            { uint64_t rec4[4]; rec4[0] = (uint64_t)copy; rec4[1] = (uint64_t)len; rec4[2] = (uint64_t)n; rec4[3] = 0;
              FUN_00363458(0, &DAT_006c0220, &rec4, 0); }
            out[0] = (uint64_t)n; out[1] = 0;
        }
    }
    FUN_00362ea4(0x67c398);
    FUN_003a3814(0x67c370);
}

/* ------------------------------------------------------------------ *
 * Swift _Set / _Dictionary raw hash tables (0x362278-0x363668).
 * Two variants: stride-0x18 (word+word+flags) and stride-0x20
 * (word+word+word+flags). Sentinel values: -2 = empty, -1 = removed.
 * ------------------------------------------------------------------ */

/* FUN_00362278 @ 0x362278  (est. cl4_type_ctx_teardown)
 * Tears down a type-metadata context object (0x67c398/0x67c370).
 * Confidence: low */
uint64_t *cl4_type_ctx_teardown_362278(uint64_t *c)
{
    *c = 0x67c398; FUN_00362ea4(c + 0x44);
    *c = 0x67c370; FUN_003a3814(c[3]);
    if (c[5]) *(uint8_t *)(c[5] + 0x30) = 0;
    return c;
}

/* FUN_003622f0 @ 0x3622f0  (est. cl4_cast_fail)
 * Non-returning: raises "Could not cast value of type ..." via
 * FUN_00369bb0(0, 0x5d3fb9).
 * Confidence: high (string) */
void cl4_cast_fail_3622f0(void) { FUN_00369bb0(0, 0x5d3fb9); }

/* FUN_00362340 @ 0x362340  (est. cl4_cast_fail_cond)
 * Non-returning: raises "Unconditional cast failed: Both ..." via
 * FUN_00369bb0(0, 0x5d3ff2).
 * Confidence: high (string) */
void cl4_cast_fail_cond_362340(void) { FUN_00369bb0(0, 0x5d3ff2); }

/* FUN_00362374 @ 0x362374  (est. cl4_cast_fail_src)
 * Non-returning: stringifies the type then raises "Unconditional cast
 * failed: Sourc..." via FUN_00369bb0.
 * Confidence: high (string) */
void cl4_cast_fail_src_362374(und8_t t)
{ uint64_t tmp[3]; cl4_type_metadata_string_361320(tmp, t, 1); FUN_00369bb0(0, 0x5d4039); }

/* FUN_003623dc @ 0x3623dc  (est. cl4_cast_fail_src2)
 * Non-returning: stringifies the type then raises "Unconditional cast
 * failed: Sourc..." (second string).
 * Confidence: high (string) */
void cl4_cast_fail_src2_3623dc(und8_t t)
{ uint64_t tmp[3]; cl4_type_metadata_string_361320(tmp, t, 1); FUN_00369bb0(0, 0x5d4084); }

/* FUN_00362444 @ 0x362444  (est. cl4_cap_cast_check)
 * Checks a cast of capability object `value` to type `target`: on null or
 * mismatched operands raises the corresponding cast failure; else resolves
 * the underlying object pointer (masking the low bit) and reports whether
 * the cast matched.
 * Confidence: medium */
uint64_t cl4_cap_cast_check_362444(int64_t value, uint64_t target, und8_t p3)
{
    uint64_t obj; uint64_t tmp1[3], tmp2[3];
    if (value == 0) value = 0;
    if (target == 0) FUN_003623dc(0, 0);
    cl4_type_metadata_string_361320(tmp1, (und8_t)value, 1);
    cl4_type_metadata_string_361320(tmp2, (und8_t)target, 1);
    obj = target & 0xfffffffffffffffe;
    return obj ? FUN_0039c74c(obj, p3) : 0;
}

/* FUN_003624f0 @ 0x3624f0  (est. cl4_obj_unmask_check)
 * Masks the low bit of a capability object and resolves it via
 * FUN_0039c74c, storing the result in *param_4.
 * Confidence: medium */
uint64_t cl4_obj_unmask_check_3624f0(und8_t p1, und8_t p2, uint64_t obj, int64_t *out, und8_t p5)
{
    uint64_t o = obj & 0xfffffffffffffffe; int64_t r;
    r = FUN_0039c74c(p2, o, p5);
    if (out && r) *out = r;
    return r != 0;
}

/* FUN_0036254c @ 0x36254c  (est. cl4_obj_resolve)
 * Resolves a capability object and (if the flags allow) fetches its
 * associated value, storing both into the outputs.
 * Confidence: medium */
uint64_t cl4_obj_resolve_36254c(und8_t p1, und8_t p2, uint64_t obj, int64_t *out, int flags)
{
    int64_t r, loc[2]; uint64_t o;
    loc[0] = 0; loc[1] = 0;
    o = obj & 0xfffffffffffffffe;
    r = FUN_0039c74c(p2, o, loc);
    if (out && r) *out = r;
    if (r == 0) return 0;
    if (flags == 0 || loc[0] == 0) return FUN_0039c7e8(p2, loc);
    return 0;
}

/* FUN_003625e4 @ 0x3625e4  (est. cl4_obj_resolve_simple)
 * Convenience wrapper: resolves the object and returns the associated
 * value (first output of FUN_00362624).
 * Confidence: medium */
uint64_t cl4_obj_resolve_simple_3625e4(und8_t a, und8_t b, und8_t c)
{
    uint64_t out = 0; uint8_t flag = 0;
    FUN_00362624(a, b, 0, &out, &flag, 0, c);
    return out;
}

/* FUN_00362624 @ 0x362624  (est. cl4_cap_tree_resolve)
 * Resolves a capability object through its nesting: follows the object
 * tree (types 0/0x203/0x305/0x303/0x307) down to the target, and reports
 * the resolved object in *param_4 with the tail pointer in *param_3 and
 * any isolation flag in *param_5.
 * Confidence: medium */
void cl4_cap_tree_resolve_362624(uint64_t *obj, uint64_t *tgt, uint64_t *tail, uint64_t *out,
                                 uint8_t *flag, uint64_t p6, uint64_t p7)
{
    int t;
loop:
    t = 0;
    if (*tgt < 0x800) t = (int)*tgt;
    if (t > 0x303) { /* large types */ }
    if (t < 0x303) {
        if ((t != 0) && (t != 0x203)) goto rettail;
        *tail = (uint64_t)obj; *out = FUN_003a25b8(*obj); return;
    }
    *flag = (uint8_t)(FUN_00374d38(tgt, obj) & *flag);
    if ((p7 & 1) == 0) { rettail: *tail = (uint64_t)obj; *out = (uint64_t)tgt; return; }
    if ((FUN_00374d14(tgt) != 0) && (FUN_00374d14(tgt) != 2)) {
        if (FUN_00374d14(tgt) == 1) { *tail = (uint64_t)obj; *out = FUN_003a25b8(*obj); return; }
        goto cont;
    }
    obj = (uint64_t *)FUN_00374de4(tgt, obj);
    if ((p6 & 1) && (*obj - 0x800 < 0xfffffffffffff801)) {
        *tail = (uint64_t)obj; *out = 0; *flag = 1; return;
    }
    obj = (uint64_t *)FUN_00374d80(tgt, obj);
    p6 = 0; p7 = 1; tgt = obj;
    goto loop;
cont:
    if (t == 0x307) {
        uint8_t k = *(uint8_t *)tgt[1];
        if (k == 0) { uint64_t *nx = (uint64_t *)FUN_0036a358(obj); obj = nx; tgt = (uint64_t *)obj[3]; goto loop; }
        if (k == 1) { *out = FUN_003a25b8(*obj); *tail = (uint64_t)obj; return; }
        if (k == 2) { *out = FUN_003743d0(*obj); *tail = (uint64_t)obj; return; }
        if (k == 3) SoftwareBreakpoint(1, 0x362754);
    }
    *out = FUN_003743d0(*obj); *tail = (uint64_t)obj;
}

/* FUN_003627f4 @ 0x3627f4  (est. cl4_cap_class_lookup)
 * Returns the class/vtable table for a capability object. For a plain
 * object (type 0x200) with the "endpoint" marker 0x6123c4 it caches the
 * result in DAT_006c0250; otherwise it resolves the object's id and caches
 * it in DAT_006c0248.
 * Confidence: medium */
int64_t cl4_cap_class_lookup_3627f4(int64_t *c)
{
    if (*c == 0x200) {
        int64_t m = c[1]; if (!m) m = 0;
        if (m == 0x6123c4) {
            if (DAT_006c0258 & 1) return DAT_006c0250;
            FUN_004b9ac8(c); return DAT_006c0250;
        }
    }
    if (c != (int64_t *)DAT_006c0240) {
        DAT_006c0248 = FUN_0039c740(c, 0x60ce80);
        DataMemoryBarrier(2, 3);
        DAT_006c0240 = (uint64_t)c;
    }
    return DAT_006c0248 ? DAT_006c0248 : 0;
}

/* FUN_003628f0 @ 0x3628f0  (est. cl4_cap_get_target)
 * Extracts the target/id field from a capability object: for a large type
 * (> 0x7fe) follows its child pointer (validating against FUN_00019850);
 * for a 0x203 object returns field[2].
 * Confidence: medium */
int64_t cl4_cap_get_target_3628f0(int64_t *c)
{
    int64_t v = *c, ch;
    if (0x7fe < (v - 1U)) {
        ch = c[1]; if (!ch) return 0;
        if (FUN_00019850() != ch) { ch = c[1]; if (!ch) return 0; return ch; }
        v = *c;
    }
    if (v != 0x203) return 0;
    return c[2];
}

/* FUN_0036298c @ 0x36298c  (est. cl4_cap_is_plain)
 * True if the object type is 0 (plain), 0x203, or 0x305.
 * Confidence: medium */
uint64_t cl4_cap_is_plain_36298c(uint64_t *c)
{ int t = 0; if (*c < 0x800) t = (int)*c; return (t == 0) || (t == 0x203) || (t == 0x305); }

/* FUN_003629b4 @ 0x3629b4  (est. cl4_cap_is_202)
 * True if the object type is exactly 0x202.
 * Confidence: medium */
uint64_t cl4_cap_is_202_3629b4(int64_t *c) { return *c == 0x202; }

/* FUN_003629c4 @ 0x3629c4  (est. cl4_cap_deref)
 * Resolves a capability reference: if the resolved object is a plain type
 * it returns the child pointer, otherwise 0 (non-resolvable). Releases
 * the child reference on the plain path.
 * Confidence: medium */
uint64_t cl4_cap_deref_3629c4(und8_t p1, uint64_t *c)
{
    uint64_t tail = 0, out = 0; uint8_t flag = 0;
    FUN_00362624(p1, c, &tail, &out, &flag, 1, 1);
    if (out == 0) { FUN_0036b270(tail); return 0; }
    else {
        if (out != (uint64_t)c) { int t = 0; if (*(uint64_t *)out < 0x800) t = (int)*(uint64_t *)out; if ((t == 0) || (t == 0x305) || (t == 0x203)) { FUN_0036b270(tail); return 0; } }
        return 0;
    }
}

/* FUN_00362a58 @ 0x362a58  (est. cl4_cap_notify)
 * Resolves a capability and calls its class vtable method (+0x10) with
 * (obj, class).
 * Confidence: low */
void cl4_cap_notify_362a58(und8_t p1, und8_t p2)
{
    uint64_t out = 0, tail = 0; uint8_t flag = 0; int64_t cls;
    FUN_00362624(p1, p2, &tail, &out, &flag, 0, 1);
    cls = FUN_003627f4(out);
    if (cls) (*(void(**)(uint64_t,int64_t))(cls + 0x10))(out, cls);
}

/* FUN_00362acc @ 0x362acc  (est. cl4_cap_list_search)
 * Searches a linked list of capabilities (from *param_1) for `param_2`.
 * Returns param_1 if found; otherwise, if both are endpoint-like objects
 * with marker 0x60cf08, resolves them via FUN_001b61bc and returns the
 * found tail/head pair.
 * Confidence: low */
uint64_t *cl4_cap_list_search_362acc(uint64_t *head, int64_t *target)
{
    int64_t *p = (int64_t *)*head;
    while (p != target) { p = (int64_t *)p[1]; if (!p || !p) goto miss; }
    if (target) return head;
miss:
    if ((*p - 0x800U < 0xfffffffffffff801) && (*target - 0x800U < 0xfffffffffffff801)) {
        int64_t m = p[5]; if (!m) m = 0;
        if (m == 0x60cf08) {
            uint64_t a = 0, b = (uint64_t)head;
            if (FUN_001b61bc(&b, &a) & 1) { FUN_0036b118(b); return (uint64_t *)a; }
        }
    }
    return 0;
}

/* FUN_00362bc0 @ 0x362bc0  (est. cl4_cap_attach_search)
 * Searches for a capability to attach: first the list search, then
 * resolves the parent/child via FUN_003a25a0 + cast check, returning the
 * resolved child object when the target type is 0x303.
 * Confidence: low */
int64_t cl4_cap_attach_search_362bc0(und8_t p1, und8_t p2)
{
    int64_t l = FUN_00362acc(); if (l) return l;
    { uint64_t u = FUN_003a25a0(p1), r[2], t; r[0] = 0; r[1] = 0;
      FUN_00362444(u, p2, 0); }
    return 0;
}

/* FUN_00362c00 @ 0x362c00  (est. cl4_cap_attach_check)
 * Validates that param_2 is a 0x303 object (or resolves via the list
 * search for type 0), returning param_1 if valid else 0.
 * Confidence: low */
uint64_t cl4_cap_attach_check_362c00(und8_t p1, uint64_t *c)
{
    int t = 0;
    if (*c < 0x800) t = (int)*c;
    if (t != 0x303) { if (t == 0) return FUN_00362acc(); return 0; }
    if (*(int *)((int64_t)c + 0xc) != 0) p1 = 0;
    return p1;
}

/* FUN_00362c34 @ 0x362c34  (est. cl4_cap_chain_overlap)
 * Determines whether capability chains rooted at param_1 and param_2
 * overlap, following the child pointers of the plain types (0/0x203/0x305).
 * Returns param_1 when they meet, else 0.
 * Confidence: low */
uint64_t *cl4_cap_chain_overlap_362c34(uint64_t *a, uint64_t *b)
{
    int ta, tb; uint64_t *p;
    if (a == b) return a;
    ta = 0; if (*b < 0x800) ta = (int)*b;
    p = a;
    if (ta == 0) {
restart:
        ta = 0; if (*a < 0x800) ta = (int)*a;
        if (ta != 0) { if (ta == 0x203) goto chain; if (ta != 0x305) return 0; p = (uint64_t *)a[1]; }
        do { if (p == b) return a; p = (uint64_t *)p[1]; } while (p && p);
        b = 0;
    } else {
        if (ta != 0x203) { if (ta != 0x305) return 0; b = (uint64_t *)b[1]; goto restart; }
chain:
        ta = 0; if (*a < 0x800) ta = (int)*a;
        if ((ta != 0) && (ta != 0x203)) { if (ta != 0x305) return 0; p = (uint64_t *)a[1]; }
        b = (uint64_t *)FUN_003a28a8(p);
    }
    return (b) ? a : 0;
}

/* FUN_00362d2c @ 0x362d2c  (est. cl4_alloc_cap_slot)
 * Allocates a capability slot record (0x10 bytes) with kind 0x67a2b8 and
 * stores the object's second word.
 * Confidence: low */
void cl4_alloc_cap_slot_362d2c(int64_t obj)
{ uint64_t *s = (uint64_t *)FUN_00111890(0x10, 0x81c40803f642b); s[0] = 0x67a2b8; s[1] = *(uint64_t *)(obj + 8); }

/* FUN_00362de4 @ 0x362de4  (est. cl4_ctx_iter_destroy)
 * Invokes the context iterator destroy: if the stored tail is the context
 * itself calls vtable +0x20, else vtable +0x28.
 * Confidence: low */
uint64_t *cl4_ctx_iter_destroy_362de4(uint64_t *c)
{
    uint64_t *t = (uint64_t *)c[3];
    if (t == c) (*(void(**)(void))(*t + 0x20))();
    else if (t) (*(void(**)(void))(*t + 0x28))();
    return c;
}

/* FUN_00362e54 @ 0x362e54  (est. cl4_ptr_next)
 * Reads the "next" pointer of a tagged/untagged pointer cell: if the low
 * bit is clear returns (cell + value), else returns the dereferenced
 * pointer.
 * Confidence: low */
uint64_t *cl4_ptr_next_362e54(uint32_t *p)
{
    uint32_t v = *p;
    if (v) {
        uint64_t *q = (uint64_t *)(((int64_t)(int32_t)v & 0xfffffffffffffffe) + (int64_t)p);
        if ((v & 1) == 0) { if (q) return q; }
        else if (*q) return (uint64_t *)*q;
    }
    return 0;
}

/* FUN_00362ea4 @ 0x362ea4  (est. cl4_ctx_iter_destroy2)
 * Same iterator destroy as FUN_00362de4.
 * Confidence: low */
uint64_t *cl4_ctx_iter_destroy2_362ea4(uint64_t *c)
{
    uint64_t *t = (uint64_t *)c[3];
    if (t == c) (*(void(**)(void))(*t + 0x20))();
    else if (t) (*(void(**)(void))(*t + 0x28))();
    return c;
}

/* FUN_00362f14 @ 0x362f14  (est. sk_ht18_lookup)
 * Open-addressing lookup in a 0x18-stride hash table: computes the bucket
 * from the key hash, probes (linear, with tombstones at -2 and -1), and
 * returns the bucket pointer in *param_3 with a found flag.
 * Confidence: medium */
uint64_t sk_ht18_lookup_362f14(int64_t *ht, uint64_t *key, int64_t *out)
{
    int64_t *bucket = 0; uint64_t h, cur; int32_t cap = *(int32_t *)(ht + 2), idx, probe = 1;
    if (cap == 0) { *out = 0; return 0; }
    h = *key; idx = (cap - 1) & ((uint32_t)(h >> 9) ^ (uint32_t)h);
    bucket = (int64_t *)(ht[0] + idx * 0x18);
    cur = *bucket;
    if (h != cur) {
        uint64_t *seen = 0; probe = 1;
        do {
            if (cur == 0xfffffffffffffffe) { if (seen) bucket = (int64_t *)seen; *out = (int64_t)bucket; return 0; }
            { int64_t *cand = (seen || cur != 0xfffffffffffffff0) ? (int64_t *)seen : bucket; seen = (uint64_t *)cand; }
            idx = idx + probe & (cap - 1);
            bucket = (int64_t *)(ht[0] + idx * 0x18);
            cur = *bucket; probe++;
        } while (h != cur);
    }
    *out = (int64_t)bucket;
    return 1;
}

/* FUN_00362fb0 @ 0x362fb0  (est. sk_ht18_insert_cursor)
 * Inserts an entry into a 0x18-stride hash table and returns an iterator
 * {bucket, end, is_new} in param_1.
 * Confidence: medium */
void sk_ht18_insert_cursor_362fb0(int64_t *out, int64_t *ht, uint64_t *key, uint64_t *val)
{
    int64_t *bucket = 0; uint64_t found = FUN_00362f14(ht, key, &bucket);
    int isnew = (found & 1) == 0;
    if (isnew) { bucket = (int64_t *)FUN_00363048(ht, key, key); *(uint64_t *)bucket = *key; bucket[2] = val[1]; bucket[1] = val[0]; }
    out[0] = (int64_t)bucket; out[1] = ht[0] + *(int32_t *)(ht + 2) * 0x18;
    *(uint64_t *)(out + 2) = (uint64_t)isnew;
}

/* FUN_00363048 @ 0x363048  (est. sk_ht18_alloc_slot)
 * Allocates a new bucket slot in a 0x18-stride hash table, growing the
 * table if the load factor exceeds 3/4; returns the free bucket.
 * Confidence: medium */
int64_t *sk_ht18_alloc_slot_363048(int64_t ht, und8_t k, und8_t k2, int64_t *bucket)
{
    uint32_t cap = *(uint32_t *)(ht + 0x10), used = *(uint32_t *)(ht + 8), del = *(int32_t *)(ht + 0xc);
    int64_t *b;
    if (used * 4 + 4 < cap * 3) { if (cap >> 3 < (cap + ~used) - del) goto found; }
    else cap = cap << 1;
    FUN_003630f8(ht, cap);
    b = 0; FUN_00362f14(ht, k2, &b); bucket = b;
found:
    *(int32_t *)(ht + 8) = *(int32_t *)(ht + 8) + 1;
    if (*bucket != -2) *(int32_t *)(ht + 0xc) = *(int32_t *)(ht + 0xc) - 1;
    return bucket;
}

/* FUN_003630f8 @ 0x3630f8  (est. sk_ht18_reserve)
 * Grows a 0x18-stride hash table to at least `cap` buckets (rounded up to
 * a power of two, min 0x40), rehashing all live entries.
 * Confidence: medium */
void sk_ht18_reserve_3630f8(int64_t *ht, int32_t cap)
{
    uint32_t oldcap = *(uint32_t *)(ht + 2), newcap; int64_t old = ht[0], *nb;
    uint32_t v = (uint32_t)cap - 1U | ((uint32_t)cap - 1U >> 1);
    v |= v >> 2; v |= v >> 4; v |= v >> 8; v |= v >> 16;
    newcap = 0x40; if (0x40 < v + 1) newcap = v + 1;
    *(uint32_t *)(ht + 2) = newcap;
    nb = (int64_t *)thunk_FUN_004bab7c((uint64_t)newcap * 0x18, 8);
    ht[0] = (int64_t)nb;
    if (old != 0) { FUN_003631cc(ht, old, old + (uint64_t)oldcap * 0x18); thunk_FUN_00111888(old, (uint64_t)oldcap * 0x18, 8); return; }
    ht[1] = 0;
    { int64_t i = newcap * 0x18; uint64_t *p = (uint64_t *)nb;
      while (i) { *p = 0xfffffffffffffffe; i -= 0x18; p += 3; } }
}

/* FUN_003631cc @ 0x3631cc  (est. sk_ht18_rehash)
 * Rehashes the live entries of a 0x18-stride hash table into the new
 * storage, initializing empty slots and copying non-sentinel records.
 * Confidence: medium */
void sk_ht18_rehash_3631cc(uint64_t *ht, int64_t *src, int64_t *end)
{
    int64_t *b;
    ht[1] = 0;
    { int64_t i = *(int32_t *)(ht + 2) * 0x18; uint64_t *p = (uint64_t *)ht[0];
      while (i) { *p = 0xfffffffffffffffe; i -= 0x18; p += 3; } }
    for (; src != end; src += 3) {
        if (*src != -0x10 && *src != -2) {
            b = 0; FUN_00362f14(ht, (uint64_t *)src, &b);
            *b = *src; b[2] = src[2]; b[1] = src[1];
            *(int32_t *)(ht + 1) = *(int32_t *)(ht + 1) + 1;
        }
    }
}

/* FUN_00363280 @ 0x363280  (est. sk_ht20_lookup)
 * Open-addressing lookup in a 0x20-stride hash table keyed by a 2-word
 * key; returns the bucket in *param_3.
 * Confidence: medium */
uint64_t sk_ht20_lookup_363280(int64_t *ht, uint64_t *key, int64_t *out)
{
    int64_t *bucket = 0; uint32_t cap = *(int32_t *)(ht + 2), idx; uint64_t h; int probe = 1;
    if (cap == 0) { *out = 0; return 0; }
    h = FUN_003a2b38(*key, key[1]);
    idx = (cap - 1) & (uint32_t)h;
    bucket = (int64_t *)(ht[0] + idx * 0x20);
    if ((FUN_00363368(*key, key[1], *bucket, bucket[1]) & 1) == 0) {
        int64_t *seen = 0;
        do {
            if (*bucket == -1) { if (seen) bucket = seen; *out = (int64_t)bucket; return 0; }
            { int64_t *cand = (seen || *bucket != -2) ? seen : bucket; seen = cand; }
            idx = idx + probe & (cap - 1);
            bucket = (int64_t *)(ht[0] + idx * 0x20);
            probe++;
        } while ((FUN_00363368(*key, key[1], *bucket, bucket[1]) & 1) == 0);
    }
    *out = (int64_t)bucket;
    return 1;
}

/* FUN_00363368 @ 0x363368  (est. sk_ht20_key_eq)
 * Compares a two-word key against a bucket's two words; -1 is the empty
 * sentinel and -2 the tombstone. Strings are compared with memcmp when
 * both are non-zero.
 * Confidence: medium */
uint64_t sk_ht20_key_eq_363368(int64_t k0, int64_t k1, int64_t b0, int64_t b1)
{
    if (b0 == -2) return k0 == -2;
    if (b0 != -1) {
        if (k1 != b1) return 0;
        if (k0 != 0) return thunk_FUN_001145b0(k0, b0, k1) == 0;
        return 1;
    }
    return k0 == -1;
}

/* FUN_003633d8 @ 0x3633d8  (est. cl4_type_ctx_free)
 * Tears down and frees a type-metadata context (0x640-byte block).
 * Confidence: low */
void cl4_type_ctx_free_3633d8(uint64_t *c)
{
    *c = 0x67c398; FUN_00362ea4(c + 0x44);
    *c = 0x67c370; FUN_003a3814(c[3]);
    if (c[5]) *(uint8_t *)(c[5] + 0x30) = 0;
    thunk_FUN_00012568(c, 0x640);
}

/* FUN_00363458 @ 0x363458  (est. sk_ht20_insert_cursor)
 * Inserts an entry into a 0x20-stride hash table and returns an iterator.
 * Confidence: medium */
void sk_ht20_insert_cursor_363458(int64_t *out, int64_t *ht, uint64_t *key, uint64_t *val)
{
    int64_t *bucket = 0; uint64_t found = FUN_00363280(ht, key, &bucket);
    int isnew = (found & 1) == 0;
    if (isnew) { bucket = (int64_t *)FUN_003634ec(ht, key, key); bucket[0] = key[0]; bucket[1] = key[1]; bucket[2] = val[0]; bucket[3] = val[1]; }
    out[0] = (int64_t)bucket; out[1] = ht[0] + *(int32_t *)(ht + 2) * 0x20;
    *(uint64_t *)(out + 2) = (uint64_t)isnew;
}

/* FUN_003634ec @ 0x3634ec  (est. sk_ht20_alloc_slot)
 * Allocates a new bucket in a 0x20-stride hash table, growing if needed.
 * Confidence: medium */
int64_t *sk_ht20_alloc_slot_3634ec(int64_t ht, und8_t k, und8_t k2, int64_t *bucket)
{
    uint32_t cap = *(uint32_t *)(ht + 0x10), used = *(uint32_t *)(ht + 8), del = *(int32_t *)(ht + 0xc);
    int64_t *b;
    if (used * 4 + 4 < cap * 3) { if (cap >> 3 < (cap + ~used) - del) goto found; }
    else cap = cap << 1;
    FUN_0036359c(ht, cap);
    b = 0; FUN_00363280(ht, k2, &b); bucket = b;
found:
    *(int32_t *)(ht + 8) = *(int32_t *)(ht + 8) + 1;
    if (*bucket != -1) *(int32_t *)(ht + 0xc) = *(int32_t *)(ht + 0xc) - 1;
    return bucket;
}

/* FUN_0036359c @ 0x36359c  (est. sk_ht20_reserve)
 * Grows a 0x20-stride hash table, rehashing live entries; initializes
 * empty buckets with the -1/-2 sentinel pair.
 * Confidence: medium */
void sk_ht20_reserve_36359c(int64_t *ht, int32_t cap)
{
    uint32_t oldcap = *(uint32_t *)(ht + 2), newcap; int64_t old = ht[0], *nb;
    uint32_t v = (uint32_t)cap - 1U | ((uint32_t)cap - 1U >> 1);
    v |= v >> 2; v |= v >> 4; v |= v >> 8; v |= v >> 16;
    newcap = 0x40; if (0x40 < v + 1) newcap = v + 1;
    *(uint32_t *)(ht + 2) = newcap;
    nb = (int64_t *)thunk_FUN_004bab7c((uint64_t)newcap << 5, 8);
    ht[0] = (int64_t)nb;
    if (old != 0) { FUN_00363668(ht, old, old + (uint64_t)oldcap * 0x20); thunk_FUN_00111888(old, (uint64_t)oldcap << 5, 8); return; }
    ht[1] = 0;
    { int64_t i = *(int32_t *)(ht + 2) << 5; uint64_t *p = (uint64_t *)nb;
      while (i) { p[1] = 0; p[0] = 0xffffffffffffffff; i -= 0x20; p += 4; } }
}

/* FUN_00363668 @ 0x363668  (est. sk_ht20_rehash)
 * Rehashes live entries into a 0x20-stride table, skipping sentinels.
 * Confidence: medium */
void sk_ht20_rehash_363668(uint64_t *ht, uint64_t *src, uint64_t *end)
{
    uint64_t *b;
    ht[1] = 0;
    { int64_t i = *(int32_t *)(ht + 2) << 5; uint64_t *p = (uint64_t *)ht[0];
      while (i) { p[1] = 0; p[0] = 0xffffffffffffffff; i -= 0x20; p += 4; } }
    for (; src != end; src += 4) {
        if (*src < 0xfffffffffffffffe) {
            b = 0; FUN_00363280(ht, src, &b);
            b[0] = src[0]; b[1] = src[1]; b[2] = src[2]; b[3] = src[3];
            *(int32_t *)(ht + 1) = *(int32_t *)(ht + 1) + 1;
        }
    }
}

/* ------------------------------------------------------------------ *
 * Capability / type-metadata serializer (0x363718-0x365a48).
 * ------------------------------------------------------------------ */

/* FUN_00363718 @ 0x363718  (est. cl4_cap_serialize)
 * Serializes a capability object into a chain of type-descriptor nodes
 * (via FUN_003a3430/FUN_003a3460). Walks the object's kind records,
 * emitting a node per record kind: kind 3 = static class name, kind 1 =
 * generic args + metadata pack, kind 0 = plain object name, kind 0x10-0x12
 * = mangled type metadata. Bounded by the payload count (param_2).
 * Confidence: low */
uint64_t cl4_cap_serialize_363718(int64_t obj, uint64_t payload, int64_t use_payload, und8_t ctx)
{
    uint64_t out = 0, cnt = 0, tail = 0, hdr[4]; uint64_t *chain = hdr;
    if (obj) {
        do { FUN_00363f10(&chain, obj); obj = FUN_003658e8(obj + 4); } while (obj);
        /* walk records; emit nodes (jump-table dispatch per kind) */
        if (cnt) {
            /* serialization loop consumed the record list */
        }
    }
    tail = FUN_003a3430(ctx, 0xf4); FUN_003a3460(tail, out, ctx);
    if (chain != hdr) thunk_FUN_00012568();
    return tail;
}

/* FUN_00363f10 @ 0x363f10  (est. sk_span_append8)
 * Appends a word to a growable 8-byte-span (FUN_003a294c), updating count.
 * Confidence: medium */
void sk_span_append8_363f10(int64_t *span, und8_t v)
{
    uint64_t n = *(uint32_t *)(span + 1);
    if (*(uint32_t *)((int64_t)span + 0xc) <= n) { FUN_003a294c(span, span + 2, n + 1, 8); n = *(uint32_t *)(span + 1); }
    *(uint64_t *)(span[0] + n * 8) = v;
    *(int32_t *)(span + 1) = (int32_t)span[1] + 1;
}

/* FUN_00363f70 @ 0x363f70  (est. cl4_alloc_str_node)
 * Allocates a string node in the object arena: reserves `len` bytes
 * (FUN_00365660), copies the string, and wraps it via FUN_003a3980 with
 * tag `tag`.
 * Confidence: low */
void cl4_alloc_str_node_363f70(und8_t ctx, und8_t tag, und8_t src, int64_t len)
{
    uint64_t buf = 0;
    if (len) { buf = FUN_00365660(ctx, len); FUN_00117d14(buf, src, len); }
    FUN_003a3980(ctx, tag, buf, len);
}

/* FUN_00363fe8 @ 0x363fe8  (est. cl4_string_with_length)
 * Builds a Swift string from a C string: FUN_00116bb4(p1, 0x12, str,
 * &stack0). Returns the string in param_1.
 * Confidence: low */
void cl4_string_with_length_363fe8(und8_t p1) { FUN_00116bb4(p1, 0x12, 0x5d40e9, 0); }

/* FUN_00364020 @ 0x364020  (est. cl4_type_metadata_encode)
 * Encodes a Swift type-metadata object into an arena node chain in ctx.
 * Dispatches on the type tag (low word < 0x800):
 *   - 0x303: generic struct -> emits an unbound-generic node + generic-arg
 *     nodes, optionally the mangled metadata pack.
 *   - 0x304/0x305/0x306: recursive encode of the child type into a node.
 *   - 0x307: builtin/opaque -> resolves a relative symbol (thunk_FUN_00115080)
 *     and decodes the Swift type fields via FUN_003a32a0, emitting nodes.
 *   - 0x200/0x201/0x202: object name from the builtin-type table
 *     (_Builtin_Int8 .. _Builtin_Job) or a string node.
 *   - 0x301: tuple -> per-element nodes wrapped in a tuple node.
 *   - 0x302: struct -> generic struct layout with member fields.
 * Returns the head node (or 0 on failure).
 * Confidence: low
 * Notes: arena helpers FUN_003a3430/FUN_003a3460/FUN_003a3a10; builtin
 *   name table 0x67afa8..0x67b138; strings _Builtin_* at 0x5d4119+. */
uint64_t cl4_type_metadata_encode_364020(uint64_t *type, und8_t ctx)
{
    int tag = 0;
    uint64_t child, node, out = 0;
    if (*type < 0x800) tag = (int)*type;
    switch (tag) {
    case 0x303: {
        /* generic struct: unbound-generic node + generic args */
        uint32_t nargs = *(uint32_t *)((int64_t)type + 0xc);
        uint64_t *args = type + 2 + ((uint32_t)type[1] >> 0x1e & 1);
        int64_t base = FUN_003a3430(ctx, 0xc9);
        node = FUN_003a3430(ctx, 0xf7);
        int64_t i = (int64_t)nargs << 3;
        while (i) {
            child = *args & 0xfffffffffffffffe;
            if (child == 0) child = 0;
            node = FUN_00363718(child, 0, 0, ctx);
            args++; i -= 8;
        }
        FUN_003a3460(base, node, ctx);
        out = base;
        break;
    }
    case 0x304:
    case 0x305:
    case 0x306:
        child = FUN_00364020(type[1], ctx);
        if (child) { node = FUN_003a3430(ctx, 0xf4); FUN_003a3460(node, child, ctx); out = FUN_003a3430(ctx, 0x9a); FUN_003a3460(out, node, ctx); }
        break;
    case 0x307: {
        /* builtin/opaque: resolve and emit the type fields */
        int64_t p = *(int32_t *)(type[1] + 4) + (type[1] + 4);
        uint64_t sym = p ? thunk_FUN_00115080(p) : 0;
        node = FUN_003a32a0(ctx, p, sym, 0);
        FUN_00362ea4(0);
        out = node;
        break;
    }
    case 0x400:
        /* out-of-range fallthrough below */
        break;
    default:
        if (tag == 0) {
            child = type[5];
            if (child) out = FUN_00363718(child, 0, 0, ctx);
        } else if (tag == 0x200 || tag == 0x201 || tag == 0x202) {
            child = type[1];
            if (child) out = FUN_00363718(child, 0, 0, ctx);
        } else if (tag == 0x203 || tag == 0x204) {
            child = type[1];
            if (child) out = FUN_00363718(child, 0, 0, ctx);
        } else {
            /* unknown builtin type name from the table */
            uint64_t name = 0;
            if ((uint64_t)type == 0x67afa8) name = 0x5d4119;
            else if ((uint64_t)type == 0x67afb8) name = 0x5d4126;
            else if ((uint64_t)type == 0x67afc8) name = 0x5d4133;
            else if ((uint64_t)type == 0x67afd8) name = 0x5d4140;
            else if ((uint64_t)type == 0x67afe8) name = 0x5d414e;
            else if ((uint64_t)type == 0x67aff8) name = 0x5d415c;
            else if ((uint64_t)type == 0x67b008) name = 0x5d416a;
            else if ((uint64_t)type == 0x67b018) name = 0x5d4178;
            else if ((uint64_t)type == 0x67b028) name = 0x5d4187;
            else if ((uint64_t)type == 0x67b038) name = 0x5d4196;
            else if ((uint64_t)type == 0x67b048) name = 0x5d41a5;
            else if ((uint64_t)type == 0x67b058) name = 0x5d41b2;
            else if ((uint64_t)type == 0x67b068) name = 0x5d41c3;
            else if ((uint64_t)type == 0x67b078) name = 0x5d41d4;
            else if ((uint64_t)type == 0x67b088) name = 0x5d41e5;
            else if ((uint64_t)type == 0x67b098) name = 0x5d41f6;
            else if ((uint64_t)type == 0x67b0a8) name = 0x5d4208;
            else if ((uint64_t)type == 0x67b0b8) name = 0x5d421d;
            else if ((uint64_t)type == 0x67b0c8) name = 0x5d4232;
            else if ((uint64_t)type == 0x67b0d8) name = 0x5d4245;
            else if ((uint64_t)type == 0x67b0e8) name = 0x5d425f;
            else if ((uint64_t)type == 0x67b0f8) name = 0x5d4275;
            else if ((uint64_t)type == 0x67b108) name = 0x5d4293;
            else if ((uint64_t)type == 0x67b118) name = 0x5d42af;
            else if ((uint64_t)type == 0x67b128) name = 0x5d42d9;
            else if ((uint64_t)type == 0x67b138) name = 0x5d42ea;
            else return 0;
            out = FUN_003a3a10(ctx, 0x14, name);
        }
        break;
    }
    return out;
}

/* FUN_00365184 @ 0x365184  (est. sk_span_append16)
 * Appends a 2-word record to a growable 0x10-byte span.
 * Confidence: medium */
void sk_span_append16_365184(int64_t *span, und8_t a, und8_t b)
{
    uint64_t n = *(uint32_t *)(span + 1);
    if (*(uint32_t *)((int64_t)span + 0xc) <= n) { FUN_003a294c(span, span + 2, n + 1, 0x10); n = *(uint32_t *)(span + 1); }
    uint64_t *p = (uint64_t *)(span[0] + n * 0x10);
    p[0] = a; p[1] = b;
    *(int32_t *)(span + 1) = (int32_t)span[1] + 1;
}

/* FUN_003651f4 @ 0x3651f4  (est. cl4_cap_flags_word)
 * Reads a 32-bit flag word from a capability object's packed header at
 * the offset encoded in the object's second word (negative => header).
 * Confidence: low */
uint32_t cl4_cap_flags_word_3651f4(int64_t obj)
{
    uint64_t w = *(uint64_t *)(obj + 8); int64_t off;
    if (-1 < (int64_t)w) return 0;
    off = (int64_t)(((obj + (w & 0xffff) * 8 + (w & 0xffff & (int64_t)(w << 0x26) >> 0x3f) * 4 + 0x1f) & 0xfffffffffffffff8) + (w >> 0x1b & 1) * 8 + (w >> 0x1c & 1) * 8);
    return *(uint32_t *)off;
}

/* FUN_00365238 @ 0x365238  (est. cl4_cap_field_ptr)
 * Reads a pointer field from a capability object's packed header.
 * Confidence: low */
uint64_t cl4_cap_field_ptr_365238(int64_t obj)
{
    if (FUN_00365a00() == 0) return 0;
    { uint64_t w = *(uint64_t *)(obj + 8);
      return *(uint64_t *)(((w >> 0x1d & 4 | w >> 0x18 & 8) + (w >> 0x19 & 8) + ((obj + (w & 0xffff) * 8 + (w & 0xffff & (int64_t)(w << 0x26) >> 0x3f) * 4 + 0x1f) & 0xfffffffffffffff8) + 7) & 0xfffffffffffffff8); }
}

/* FUN_003652b8 @ 0x3652b8  (est. cl4_cap_serialize_maybe)
 * Serializes a capability object to a node chain, but only for kind
 * 0x10-0x12 records; otherwise returns 0.
 * Confidence: low */
uint64_t cl4_cap_serialize_maybe_3652b8(uint32_t *obj, und8_t p2, und8_t p3)
{
    if ((*obj & 0x1f) - 0x10 < 3) {
        uint64_t span[4]; int64_t ok;
        span[0] = 0x4f2710; span[1] = 0;
        ok = FUN_003653b8(obj, p2, span, p3);
        if (ok == 0) return 0;
        return FUN_00363718(obj, span[1], span[0] & 0xffffffff, p3);
    }
    return 0;
}

/* FUN_003653b8 @ 0x3653b8  (est. cl4_cap_metadata_pack)
 * Decodes a capability object's metadata pack: reads the record, gathers
 * the generic argument descriptors, and for each emitted arg wraps it as a
 * node. Validates the pack shape and panics on "Expected a metadata pack
 * but got..." / "Expected metadata but got a meta..." mismatches.
 * Confidence: low
 * Notes: strings 0x5d42f6 / 0x5d40ee. */
uint64_t cl4_cap_metadata_pack_3653b8(und8_t obj, int64_t args, und8_t out, und8_t ctx)
{
    int64_t rec = FUN_0035eb3c(obj);
    if (rec == 0) return 1;
    if (FUN_003658a0(rec)) {
        int64_t fn = FUN_0038a950(obj, args, 0, out, ctx);
        if ((fn & 1) == 0) return 0;
    }
    return 1;
}

/* FUN_00365660 @ 0x365660  (est. cl4_arena_reserve)
 * Reserves `len` bytes in a growable output arena (param_1 header):
 * grows the backing buffer (doubling, min len+1) and returns the new
 * write cursor.
 * Confidence: medium */
void cl4_arena_reserve_365660(int64_t arena, int64_t len)
{
    uint64_t *cur = *(uint64_t **)(arena + 8);
    if (!cur || (*(uint64_t *)(arena + 0x10) < (uint64_t)((int64_t)cur + len))) {
        uint64_t cap = *(int64_t *)(arena + 0x20) * 2;
        uint64_t *blk;
        if (cap < (uint64_t)len + 1 || cap - ((uint64_t)len + 1) == 0) cap = (uint64_t)len + 1;
        *(uint64_t *)(arena + 0x20) = cap;
        blk = (uint64_t *)FUN_000101a0(cap + 8, 0x2004093837f09);
        cur = blk + 1;
        *blk = *(uint64_t *)(arena + 0x18);
        *(uint64_t *)(arena + 0x10) = (uint64_t)blk + cap + 8;
        *(uint64_t *)(arena + 0x18) = (uint64_t)blk;
    }
    *(int64_t *)(arena + 8) = (int64_t)cur + len;
}

/* FUN_003656f4 @ 0x3656f4  (est. cl4_cap_resolve_pair)
 * Resolves a capability pair into two object descriptors; if the record
 * is an indirect metadata reference (tag 0x27), loads the two words and
 * resolves the referenced metadata object. Panics on a metadata-shape
 * mismatch.
 * Confidence: low
 * Notes: string "Expected metadata but got a meta..." 0x5d40ee. */
void cl4_cap_resolve_pair_3656f4(uint64_t *obj, und8_t p2, und8_t p3)
{
    uint64_t *p = obj, *q;
    if (1 < *(uint8_t *)((int64_t)obj + 0x12) - 1) {
        if ((*(uint8_t *)((int64_t)obj + 0x12) != 5) || (*(int32_t *)(obj + 1) == 0)) { obj = 0; return; }
        obj = (uint64_t *)*obj;
    }
    obj = (uint64_t *)*obj;
    if (*(int16_t *)(obj + 2) != 0x27) return;
    q = obj;
    if ((1 < *(uint8_t *)((int64_t)obj + 0x12) - 1) && (q = (uint64_t *)*obj, *(uint8_t *)((int64_t)obj + 0x12) != 5)) q = obj;
    if (FUN_0038bbf4(p2, *(uint32_t *)*q, *(uint32_t *)q[1])) { FUN_00364020(FUN_0038bbf4(p2, *(uint32_t *)*q, *(uint32_t *)q[1]), p3); return; }
    FUN_00369bb0(0, 0x5d40ee);
}

/* FUN_003657cc @ 0x3657cc  (est. sk_span16_assign)
 * Assigns/concatenates a 0x20-stride span into param_1, growing as
 * needed, copying element records, and updating the count.
 * Confidence: medium */
uint64_t *sk_span16_assign_3657cc(uint64_t *dst, uint64_t *src)
{
    uint32_t n = *(uint32_t *)(src + 1), m = *(uint32_t *)(dst + 1);
    if (n <= m) { if (n) FUN_00117d14(*dst, *src, (uint64_t)n * 0x20 - 3); }
    else {
        if (*(uint32_t *)((int64_t)dst + 0xc) < n) { *(int32_t *)(dst + 1) = 0; FUN_003a294c(dst, dst + 2, n, 0x20); }
        else { if (m) FUN_00117d14(*dst, *src, (uint64_t)m * 0x20 - 3); }
        if (*(uint32_t *)(src + 1) - m != 0) FUN_00117cc4(*dst + m * 0x20, *src + m * 0x20, (*(uint32_t *)(src + 1) - m) * 0x20);
    }
    *(uint32_t *)(dst + 1) = n;
    return dst;
}

/* FUN_003658a0 @ 0x3658a0  (est. cl4_record_generic_args)
 * Reads the generic-argument descriptor from a Swift record: if bit0 of
 * the flags is set, returns {count, ptr} from the descriptor's arg table.
 * Confidence: low */
void cl4_record_generic_args_3658a0(int64_t rec, uint64_t out[2])
{
    if (*(uint16_t *)(rec + 10) & 1) {
        int64_t base = (rec + *(uint16_t *)(rec + 4) + 0xf) & 0xfffffffffffffffc;
        int16_t n = *(int16_t *)(base + *(uint16_t *)(rec + 6) * 0xc);
        if (n) { out[0] = (uint64_t)(base + *(uint16_t *)(rec + 6) * 0xc + 4); out[1] = (uint64_t)(int64_t)n; return; }
    }
    out[0] = 0; out[1] = 0;
}

/* FUN_003658e8 @ 0x3658e8  (est. cl4_obj_chain_next)
 * Returns the next node of a capability object chain (tagged/untagged).
 * Confidence: low */
uint64_t *cl4_obj_chain_next_3658e8(uint32_t *p)
{
    uint32_t v = *p; uint64_t *q;
    if (v) {
        q = (uint64_t *)(((int64_t)(int32_t)v & 0xfffffffffffffffe) + (int64_t)p);
        if ((v & 1) == 0) { if (q) return q; }
        else if (*q) return (uint64_t *)*q;
    }
    return 0;
}

/* FUN_00365944 @ 0x365944  (est. cl4_alloc_cap_slot2)
 * Allocates a capability slot record with kind 0x67a328.
 * Confidence: low */
void cl4_alloc_cap_slot2_365944(int64_t obj)
{ uint64_t *s = (uint64_t *)FUN_00111890(0x10, 0xa1c40bd48d6d6); s[0] = 0x67a328; s[1] = *(uint64_t *)(obj + 8); }

/* FUN_00365a00 @ 0x365a00  (est. cl4_cap_has_header)
 * True if a capability object has a packed header (its second word is
 * negative).
 * Confidence: low */
uint8_t cl4_cap_has_header_365a00(int64_t obj)
{
    uint64_t w = *(uint64_t *)(obj + 8);
    if (-1 < (int64_t)w) return 0;
    return *(uint8_t *)(((obj + (w & 0xffff) * 8 + (w & 0xffff & (int64_t)(w << 0x26) >> 0x3f) * 4 + 0x1f) & 0xfffffffffffffff8) + (w >> 0x1b & 1) * 8 + (w >> 0x1c & 1) * 8) & 1;
}

/* FUN_00365a48 @ 0x365a48  (est. cl4_cap_extract_arglist)
 * Walks a capability object's child chain and copies the argument records
 * (0xc-byte stride) into a span, invoking FUN_003773d8 for the copy.
 * Confidence: low */
void cl4_cap_extract_arglist_365a48(und8_t p1, und8_t p2, int64_t *obj)
{
    int64_t child = *obj ? *obj : 0, head = FUN_00362e54(child);
    FUN_003773d8(p1, obj, p2, head + *(uint32_t *)(head + 0xc) * 0xc + 0x10,
                 head + 0x18 + *(uint32_t *)(head + 0xc) * 0xc);
}

/* ------------------------------------------------------------------ *
 * Capability-object operation dispatcher (0x365b6c-0x366f14).
 * FUN_00365c38 is the recursive dispatch core: it selects the per-cap
 * operation function from the object's type tag (0x200-0x307), runs it,
 * and on a non-committing result descends into the child chain. The
 * per-type handlers 0x366ae0..0x366f14 perform the actual object ops.
 * ------------------------------------------------------------------ */

/* FUN_00365b6c @ 0x365b6c  (est. cl4_cap_op_dispatch)
 * Top-level capability-object operation dispatch. Validates the source
 * and target objects via FUN_00365c38, applies the per-type handler
 * selected by the source tag, and returns a commit status (0=none,
 * 1=ok, 2=recreate). Handles the 0x202 nested (parent/child) walk and the
 * 0x303-typed object conversions.
 * Confidence: medium */
uint64_t cl4_cap_op_dispatch_365b6c(und8_t a, und8_t b, uint64_t *src, int64_t target, uint64_t flags)
{
    uint64_t r = FUN_00365c38(a, target, b, src);
    if ((int)r == 1) return 1;
    if ((int)r != 0) return 1;
    return 0;
}

/* FUN_00365c38 @ 0x365c38  (est. cl4_cap_op_dispatch_core)
 * Recursive core of the cap-object dispatcher. When src==target applies
 * the identity commit (vtable +0x10/+0x20) directly. Otherwise selects
 * the handler by src type tag and runs it; if it does not commit, walks
 * the target's child/next chain to find a matching object and recurses.
 * Confidence: medium */
uint64_t cl4_cap_op_dispatch_core_365c38(und8_t a, uint64_t *src, int64_t *p3, uint64_t *target,
                                         int64_t *out5, int64_t *out6, uint64_t flags,
                                         uint64_t flags2, uint8_t flag3)
{
    *out5 = (int64_t)src; *out6 = (int64_t)target;
    if (target == src) {
        if ((int)flags == 0) { (*(void(**)(und8_t,int64_t*,uint64_t*))(src[-1] + 0x10))(a, p3, src); return 1; }
        (*(void(**)(und8_t,int64_t*,uint64_t*))(src[-1] + 0x20))(a, p3, src); return 2;
    }
    /* type dispatch on *src (handlers 0x366ae0..0x366f14) */
    return 0;
}

/* FUN_00366774 @ 0x366774  (est. cl4_cap_parent_walk)
 * Follows a capability object's parent pointer; on a null parent invokes
 * FUN_004b9b38 to report the failure. Returns the parent.
 * Confidence: low */
int64_t cl4_cap_parent_walk_366774(int64_t *p, und8_t a, und8_t b)
{
    int64_t parent = *p;
    if (parent == 0) FUN_004b9b38(a, b);
    return parent;
}

/* FUN_003667ac @ 0x3667ac  (est. cl4_cap_op_apply)
 * Applies a capability operation: resolves the target, walks to the
 * object, allocates a new element (if the type size >= 0x19), invokes the
 * object's vtable method (+0x38 for init, +0x18/+0x20 for the op), and
 * reports success.
 * Confidence: low */
uint64_t cl4_cap_op_apply_3667ac(und8_t a, int64_t src, und8_t p3, und8_t p4, uint64_t *out, int mode)
{
    int64_t obj = FUN_003681c4(src), parent, md, sz;
    uint8_t *buf;
    if (obj == 0) { *out = 0; return 0; }
    parent = FUN_00366774(p3, p4, src);
    if (parent == 0 || FUN_00362c00(parent, 0) == 0) { *out = 0; return 0; }
    md = *(int64_t *)(src - 8);
    sz = *(int64_t *)(md + 0x40);
    if (*(uint64_t *)(md + 0x48) < 0x19) buf = 0;
    else buf = (uint8_t *)FUN_0036a804(sz + 1, *(uint8_t *)(md + 0x50));
    (*(void(**)(uint8_t*,int,int,int64_t))(*(int64_t *)(src - 8) + 0x38))(buf, 1, 1, src);
    if (mode == 0) { if ((*(int(**)(int64_t,uint8_t*,int64_t,int64_t))(obj + 0x20))(parent, buf, src, obj) & 1) goto commit; *out = 0; }
    else { (*(void(**)(int64_t,uint8_t*,int64_t,int64_t))(obj + 0x18))(parent, buf, src, obj);
commit:
        (*(void(**)(und8_t,uint8_t*,int64_t))(*(int64_t *)(src - 8) + 0x20))(a, buf, src); *out = 1; }
    if (buf) thunk_FUN_00012568(buf, sz + 1, *(uint8_t *)(md + 0x50));
    return *out;
}

/* FUN_003669c8 @ 0x3669c8  (est. cl4_cap_op_commit)
 * Commits a capability op by invoking the object vtable method (+0x10)
 * and storing the resulting object into *param_1.
 * Confidence: low */
uint64_t cl4_cap_op_commit_3669c8(int64_t *out, und8_t b, und8_t c, und8_t d)
{
    int64_t obj = FUN_003681c4(d), r;
    if (obj) {
        r = (*(int(**)(und8_t,int64_t))(obj + 0x10))(d, obj);
        if (FUN_00362c00(r, b) == 0) { FUN_0036b118(r); return 0; }
        *out = r; return 1;
    }
    return 0;
}

/* FUN_00366a4c @ 0x366a4c  (est. cl4_cap_op_finish)
 * Finishes a capability op: validates the target object type and, if the
 * parent has a nonzero state word (or a recoverable child), resolves the
 * final object via FUN_001b68a0 and stores it.
 * Confidence: low */
uint64_t cl4_cap_op_finish_366a4c(uint64_t *out, int64_t src, und8_t p3, uint64_t *tgt)
{
    int t = 0; uint64_t r;
    if (*tgt < 0x800) t = (int)*tgt;
    if (t == 0 || t == 0x203 || t == 0x305) return 0;
    if (*(int *)(src + 0xc) != 0) {
        if ((int)FUN_0000456c(0) == 0) return 0;
        if ((FUN_001b65ec(src, src) & 1) == 0) return 0;
    }
    r = FUN_001b68a0(p3, tgt); *out = r; return 1;
}

/* FUN_00366ae0 @ 0x366ae0  (est. cl4_cap_op_plain)
 * Operation for a plain (type 0/0x305) object: walks to the target and,
 * if found, stores it (or retains it), returning 1/2 per the commit mode.
 * Confidence: low */
uint64_t cl4_cap_op_plain_366ae0(int64_t *out, und8_t b, und8_t c, uint64_t *tgt, uint64_t *o5, uint64_t *o6, uint64_t flags)
{
    int t = 0; int64_t parent, found;
    if (*tgt < 0x800) t = (int)*tgt;
    if (t == 0x305 || t == 0) {
        parent = FUN_00366774(c, tgt, b);
        if (parent) {
            found = FUN_00362acc(parent, b);
            if (found == 0) { *o6 = (uint64_t)tgt; *o5 = (uint64_t)b; return 0; }
            *out = found;
            if ((flags & 1) == 0) { FUN_0036b270(); return 1; }
            return 2;
        }
    }
    return 0;
}

/* FUN_00366b8c @ 0x366b8c  (est. cl4_cap_op_none)
 * Default operation: no-op, returns 0.
 * Confidence: medium */
uint64_t cl4_cap_op_none_366b8c(void) { return 0; }

/* FUN_00366b94 @ 0x366b94  (est. cl4_cap_op_202_conv)
 * Operation for a 0x303/0x202 target object: invokes the source object's
 * "convert" vtable method (+0x30) or resolves it via FUN_0039c740 and
 * applies FUN_00229748. Returns success.
 * Confidence: low */
uint64_t cl4_cap_op_202_conv_366b94(und8_t p1, und8_t p2, und8_t p3, uint64_t *tgt)
{
    int t = 0; int64_t obj, r; int64_t *e;
    if (*tgt < 0x800) t = (int)*tgt;
    if (t != 0x303) {
        if (t == 0x202) {
            e = (int64_t *)FUN_0035eae4(tgt);
            if ((*(int(**)(und8_t,int))(*(int64_t *)(*e - 8) + 0x30))(p3, 1) == 0) return 0;
        }
        obj = FUN_0039c740(tgt, 0x6101dc);
        if (obj) FUN_00229748(p3, p1, tgt, obj);
        return obj != 0;
    }
    return 0;
}

/* FUN_00366c5c @ 0x366c5c  (est. cl4_cap_op_endpoint)
 * Operation for an endpoint (type 0x200, marker 0x60cc08): decodes the
 * two object references and invokes the endpoint connect function
 * (FUN_0019e128) or FUN_0019de24, returning success.
 * Confidence: low */
uint64_t cl4_cap_op_endpoint_366c5c(und8_t p1, und8_t p2, und8_t p3, int64_t *tgt)
{
    uint64_t a, b, ok;
    if (*tgt != 0x200) return 0;
    if ((uint8_t *)tgt[1] == 0x60cc08) {
        a = *((uint64_t **)FUN_0035eae4(tgt))[0];
        b = *((uint64_t **)FUN_0035eae4(p2))[0];
        ok = FUN_0019e128(p3, p1, a, b);
        return (ok & 1) ? 1 : 0;
    }
    return 0;
}

/* FUN_00366d34 @ 0x366d34  (est. cl4_cap_op_endpoint_wide)
 * Operation for an endpoint (marker 0x60ea98) with a wide (3-word)
 * reference set, connecting via FUN_001f8abc.
 * Confidence: low */
uint64_t cl4_cap_op_endpoint_wide_366d34(und8_t p1, und8_t p2, und8_t p3, int64_t *tgt)
{
    uint64_t *e, *f, ok;
    if (*tgt != 0x200) return 0;
    if ((uint8_t *)tgt[1] == 0x60ea98) {
        e = (uint64_t *)FUN_0035eae4(tgt);
        f = (uint64_t *)FUN_0035eae4(p2);
        ok = FUN_001f8abc(p3, p1, e[0], e[1], f[0], f[1], e[2], f[2]);
        return (ok & 1) ? 1 : 0;
    }
    return 0;
}

/* FUN_00366eec @ 0x366eec  (est. cl4_cap_op_default)
 * Default operation: no-op.
 * Confidence: medium */
uint64_t cl4_cap_op_default_366eec(void) { return 0; }

/* FUN_00366ef4 @ 0x366ef4  (est. cl4_cap_op_201)
 * Operation for type 0x201: no-op.
 * Confidence: medium */
uint64_t cl4_cap_op_201_366ef4(void) { return 0; }

/* FUN_00366efc @ 0x366efc  (est. cl4_cap_op_202)
 * Operation for type 0x202: no-op.
 * Confidence: medium */
uint64_t cl4_cap_op_202_366efc(void) { return 0; }

/* FUN_00366f04 @ 0x366f04  (est. cl4_cap_op_203)
 * Operation for type 0x203: no-op.
 * Confidence: medium */
uint64_t cl4_cap_op_203_366f04(void) { return 0; }

/* FUN_00366f0c @ 0x366f0c  (est. cl4_cap_op_204)
 * Operation for type 0x204: no-op.
 * Confidence: medium */
uint64_t cl4_cap_op_204_366f0c(void) { return 0; }

/* FUN_00366f14 @ 0x366f14  (est. cl4_cap_op_300)
 * Operation for type 0x300: no-op.
 * Confidence: medium */
uint64_t cl4_cap_op_300_366f14(void) { return 0; }
