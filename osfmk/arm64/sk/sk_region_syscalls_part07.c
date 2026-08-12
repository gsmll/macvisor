/* Recreated from cl4_kernel.raw (cL4 Secure Kernel, arm64e, image base 0) —
 * the cL4 microkernel (GL1). Ground truth: Ghidra FUN_ names + addresses.
 * All names are estimates unless string/header matched.
 * Slice 07: 0x32cc70-0x33979c syscall/exception-entry region. */

#include <stdint.h>
#include <stddef.h>
#include "sk_internal.h"

/* Fixed-width aliases for Ghidra primitive names used in bodies. */
typedef uint32_t uint;
typedef uint64_t ulong;
typedef uint8_t  byte;
typedef uint16_t ushort;
typedef uint8_t  uint1_t;
typedef uint16_t uint2_t;
typedef uint32_t uint3_t;
typedef uint32_t uint4_t;
typedef uint8_t  und1_t;
typedef uint16_t und2_t;
typedef uint32_t und4_t;

/* =====================================================================
 * Out-of-range callee declarations (bodies reconstructed by their range
 * workers). All are in the 0x300000-0x380000 region or low boot helpers.
 * ===================================================================== */

/* --- syscall/entry setup helpers (0x34xxxx / 0x35xxxx range) --- */
extern cl4_result_t FUN_0034d724(word_t, ...);
extern cl4_result_t FUN_00348d94(word_t, ...);     /* arg/cap fetch */
extern void FUN_00348c64(word_t, ...);
extern void FUN_00348ce8(word_t, ...);
extern void FUN_00348e00(word_t, ...);
extern void FUN_00348f14(word_t, ...);
extern void FUN_00349104(word_t, ...);
extern void FUN_00349394(word_t, ...);
extern void FUN_00349530(word_t, ...);
extern void FUN_00349734(word_t, ...);
extern word_t FUN_00349830(word_t, ...);
extern void FUN_00349928(word_t, ...);
extern void FUN_00349a9c(word_t, ...);
extern void FUN_00349ae0(word_t, ...);
extern void FUN_00349b00(word_t, ...);
extern void FUN_00349cd0(word_t, ...);
extern void FUN_00349d3c(word_t, ...);
extern void FUN_00349e24(word_t, ...);
extern cl4_result_t FUN_0034a054(word_t, ...);
extern void FUN_0034a32c(word_t, ...);
extern void FUN_0034a6c4(word_t, ...);
extern void FUN_0034a708(word_t, ...);
extern void FUN_0034a820(word_t, ...);
extern void FUN_0034a914(word_t, ...);
extern void FUN_0034ab20(word_t, ...);
extern void FUN_0034ac8c(word_t, ...);
extern word_t FUN_0034ada0(word_t, ...);
extern void FUN_0034aed0(word_t, ...);
extern void FUN_0034b044(word_t, ...);
extern void FUN_0034b07c(word_t, ...);
extern word_t FUN_0034b264(word_t, ...);
extern word_t FUN_0034b3c8(word_t, ...);
extern void FUN_0034b3e8(word_t, ...);
extern void FUN_0034b430(word_t, ...);
extern cl4_result_t FUN_0034b57c(word_t, ...);
extern void FUN_0034b7e4(word_t, ...);
extern void FUN_0034bb74(word_t, ...);
extern void FUN_0034bbb4(word_t, ...);
extern void FUN_0034bd80(word_t, ...);
extern void FUN_0034be0c(word_t, ...);
extern void FUN_0034befc(word_t, ...);
extern void FUN_0034bf0c(word_t, ...);
extern void FUN_0034bf1c(word_t, ...);
extern void FUN_0034bfb4(word_t, ...);
extern void FUN_0034c11c(word_t, ...);
extern cl4_result_t FUN_0034c144(word_t, ...);
extern cl4_result_t FUN_0034c16c(word_t, ...);
extern word_t FUN_0034c1e4(word_t, ...);
extern void FUN_0034c444(word_t, ...);
extern void FUN_0034c654(word_t, ...);
extern void FUN_0034c7c4(word_t, ...);
extern void FUN_0034c920(word_t, ...);
extern void FUN_0034c9e8(word_t, ...);
extern cl4_result_t FUN_0034cb60(word_t, ...);
extern void FUN_0034cc38(word_t, ...);
extern void FUN_0034cc5c(word_t, ...);
extern void FUN_0034ccbc(word_t, ...);
extern word_t FUN_0034cdb4(word_t, ...);
extern cl4_result_t FUN_0034cdf8(word_t, ...);
extern void FUN_0034d034(word_t, ...);
extern void FUN_0034d1c0(word_t, ...);
extern void FUN_0034d3d4(word_t, ...);
extern cl4_result_t FUN_0034d454(word_t, ...);
extern void FUN_0034d4d4(word_t, ...);
extern void FUN_0034d5b8(word_t, ...);
extern word_t FUN_0034d5d8(word_t, ...);
extern void FUN_0034d668(word_t, ...);
extern void FUN_0034d734(word_t, ...);
extern void FUN_0034da78(word_t, ...);
extern void FUN_0034db28(word_t, ...);
extern void FUN_0034dbd8(word_t, ...);
extern void FUN_0034de44(word_t, ...);
extern void FUN_0034de54(word_t, ...);
extern void FUN_0034de74(word_t, ...);
extern void FUN_0034df04(word_t, ...);
extern void FUN_0034df14(word_t, ...);
extern void FUN_0034dfc4(word_t, ...);
extern void FUN_0034e094(word_t, ...);
extern int FUN_0034e178(word_t, ...);
extern void FUN_0034e32c(word_t, ...);
extern void FUN_0034e5bc(word_t, ...);
extern void FUN_0034e6dc(word_t, ...);
extern void FUN_0034e7e0(word_t, ...);
extern void FUN_0034e850(word_t, ...);
extern void FUN_0034e888(word_t, ...);
extern void FUN_0034e974(word_t, ...);
extern void FUN_0034e9a4(word_t, ...);
extern void FUN_0034ebe0(word_t, ...);
extern void FUN_0034ece8(word_t, ...);
extern void FUN_0034ee88(word_t, ...);
extern int FUN_0034f138(word_t, ...);
extern void FUN_0034f20c(word_t, ...);
extern void FUN_0034f22c(word_t, ...);
extern void FUN_0034f2f4(word_t, ...);
extern void FUN_0034f828(word_t, ...);
extern cl4_result_t FUN_0034f8f4(word_t, ...);
extern cl4_result_t FUN_0034f924(word_t, ...);
extern void FUN_0034fa0c(word_t, ...);
extern void FUN_0034fc7c(word_t, ...);
extern void FUN_00350198(word_t, ...);
extern void FUN_003502c8(word_t, ...);
extern void FUN_003503b0(word_t, ...);
extern void FUN_00350404(word_t, ...);
extern void FUN_00350488(word_t, ...);
extern word_t FUN_003504d0(word_t, ...);
extern cl4_result_t FUN_003504f4(word_t, ...);
extern void FUN_00350500(word_t, ...);
extern void FUN_00350548(word_t, ...);
extern cl4_result_t FUN_0035060c(word_t, ...);
extern void FUN_00350624(word_t, ...);
extern void FUN_00350630(word_t, ...);
extern void FUN_00350798(word_t, ...);
extern cl4_result_t FUN_003507e0(word_t, ...);
extern void FUN_00350878(word_t, ...);
extern void FUN_0035098c(word_t, ...);
extern void FUN_00350bb4(word_t, ...);
extern cl4_result_t FUN_00350bd8(word_t, ...);
extern void FUN_00350bfc(word_t, ...);
extern word_t FUN_00350c5c(word_t, ...);
extern void FUN_00350d74(word_t, ...);
extern word_t FUN_00350e04(word_t, ...);
extern void FUN_00350e74(word_t, ...);
extern void FUN_00350ed0(word_t, ...);
extern void FUN_00350fbc(word_t, ...);
extern void FUN_003510c4(word_t, ...);
extern void FUN_00351178(word_t, ...);
extern void FUN_003511b4(word_t, ...);
extern cl4_result_t FUN_00351244(word_t, ...);
extern cl4_result_t FUN_00351330(word_t, ...);
extern void FUN_00351390(word_t, ...);
extern void FUN_003513a8(word_t, ...);
extern void FUN_003513e4(word_t, ...);
extern word_t FUN_00351538(word_t, ...);
extern void FUN_00351608(word_t, ...);
extern void FUN_0035163c(word_t, ...);
extern void FUN_00351774(word_t, ...);
extern void FUN_003518dc(word_t, ...);
extern void FUN_00351930(word_t, ...);
extern cl4_result_t FUN_0035193c(word_t, ...);
extern void FUN_00351978(word_t, ...);
extern void FUN_003519fc(word_t, ...);
extern cl4_result_t FUN_00351a38(word_t, ...);
extern cl4_result_t FUN_00351d24(word_t, ...);
extern void FUN_00351d30(word_t, ...);
extern void FUN_00351e20(word_t, ...);
extern void FUN_003520e8(word_t, ...);
extern void FUN_003524bc(word_t, ...);
extern void FUN_003525a4(word_t, ...);
extern void FUN_003525b8(word_t, ...);
extern void FUN_0035270c(word_t, ...);
extern word_t FUN_00352758(word_t, ...);
extern void FUN_00352778(word_t, ...);
extern void FUN_00352820(word_t, ...);
extern void FUN_0035295c(word_t, ...);
extern void FUN_0035298c(word_t, ...);
extern void FUN_00352b38(word_t, ...);
extern void FUN_00352c04(word_t, ...);
extern void FUN_00352dac(word_t, ...);
extern cl4_result_t FUN_00352e90(word_t, ...);
extern cl4_result_t FUN_00352f3c(word_t, ...);
extern word_t FUN_00352f78(word_t, ...);
extern void FUN_00352ff4(word_t, ...);
extern void FUN_00353424(word_t, ...);
extern void FUN_00353498(word_t, ...);
extern void FUN_00353504(word_t, ...);
extern void FUN_003535cc(word_t, ...);
extern void FUN_003535e4(word_t, ...);
extern void FUN_0035376c(word_t, ...);
extern word_t FUN_00353844(word_t, ...);
extern void FUN_003538d4(word_t, ...);
extern void FUN_00353a00(word_t, ...);
extern cl4_result_t FUN_00353af8(word_t, ...);
extern void FUN_00353b7c(word_t, ...);
extern void FUN_00353c0c(word_t, ...);
extern cl4_result_t FUN_00353fac(word_t, ...);
extern void FUN_00353fb8(word_t, ...);
extern void FUN_00354034(word_t, ...);
extern cl4_result_t FUN_00354070(word_t, ...);
extern void FUN_003544c8(word_t, ...);
extern void FUN_003546b4(word_t, ...);
extern void FUN_00354744(word_t, ...);
extern void FUN_00354924(word_t, ...);
extern void FUN_00354c58(word_t, ...);
extern cl4_result_t FUN_00354ce4(word_t, ...);
extern void FUN_00354fd0(word_t, ...);
extern void FUN_00354fe0(word_t, ...);
extern cl4_result_t FUN_00355008(word_t, ...);
extern void FUN_003550cc(word_t, ...);
extern void FUN_003550e0(word_t, ...);
extern void FUN_0035510c(word_t, ...);
extern word_t FUN_00355150(word_t, ...);
extern void FUN_00355160(word_t, ...);
extern void FUN_003551b0(word_t, ...);
extern void FUN_00355208(word_t, ...);
extern void FUN_0035549c(word_t, ...);
extern cl4_result_t FUN_0035556c(word_t, ...);
extern cl4_result_t FUN_00355694(word_t, ...);
extern void FUN_00355780(word_t, ...);
extern void FUN_00355800(word_t, ...);
extern void FUN_00355868(word_t, ...);
extern void FUN_003558b8(word_t, ...);
extern void FUN_00355928(word_t, ...);
extern void FUN_003559c8(word_t, ...);
extern void FUN_00355d34(word_t, ...);
extern void FUN_00355d60(word_t, ...);
extern cl4_result_t FUN_00355e44(word_t, ...);
extern void FUN_00355e98(word_t, ...);
extern void FUN_00356054(word_t, ...);
extern void FUN_003561f4(word_t, ...);
extern void FUN_0035631c(word_t, ...);
extern void FUN_00356328(word_t, ...);
extern void FUN_00356358(word_t, ...);
extern void FUN_0035660c(word_t, ...);
extern void FUN_00356638(word_t, ...);
extern void FUN_00356694(word_t, ...);
extern void FUN_003566cc(word_t, ...);
extern void FUN_00356bd4(word_t, ...);
extern word_t FUN_00356e64(word_t, ...);
extern void FUN_00356e74(word_t, ...);
extern void FUN_00356eb4(word_t, ...);
extern void FUN_00357028(word_t, ...);
extern cl4_result_t FUN_00357104(word_t, ...);
extern void FUN_00357154(word_t, ...);
extern word_t FUN_00357acc(word_t, ...);
extern void FUN_00357c74(word_t, ...);
extern void FUN_00357cb4(word_t, ...);
extern void FUN_00357d34(word_t, ...);
extern void FUN_00357d44(word_t, ...);
extern void FUN_00357d74(word_t, ...);
extern void FUN_00357d94(word_t, ...);
extern void FUN_00357dd4(word_t, ...);
extern void FUN_00357e04(word_t, ...);
extern void FUN_00357ef4(word_t, ...);
extern void FUN_003580f4(word_t, ...);
extern void FUN_00358184(word_t, ...);
extern void FUN_00358194(word_t, ...);
extern cl4_result_t FUN_00358410(word_t, ...);
extern word_t FUN_003584d8(word_t, ...);
extern word_t FUN_003585dc(word_t, ...);
extern void FUN_00358750(word_t, ...);
extern void FUN_0035884c(word_t, ...);
extern cl4_result_t FUN_00358bb4(word_t, ...);
extern void FUN_00358c20(word_t, ...);
extern void FUN_00358f30(word_t, ...);
extern cl4_result_t FUN_003592b0(word_t, ...);
extern cl4_result_t FUN_0035944c(word_t, ...);
extern void FUN_003594a8(word_t, ...);
extern void FUN_003594d4(word_t, ...);
extern cl4_result_t FUN_00359588(word_t, ...);
extern cl4_result_t FUN_003595b4(word_t, ...);
extern void FUN_003597cc(word_t, ...);
extern void FUN_00359d2c(word_t, ...);
extern void FUN_0035a464(word_t, ...);
extern void FUN_0035a4a8(word_t, ...);
extern cl4_result_t FUN_0035aa54(word_t, ...);
extern void FUN_0036851c(word_t, ...);
extern void FUN_00368980(word_t, ...);
extern void FUN_0036b118(word_t, ...);
extern void FUN_0036b270(word_t, ...);
extern void FUN_00370f2c(word_t, ...);
extern void FUN_00371758(word_t, ...);
extern void FUN_003728b8(word_t, ...);
extern void FUN_00374104(word_t, ...);
extern cl4_result_t FUN_00377824(word_t, ...);
extern cl4_result_t FUN_00377dcc(word_t, ...);

/* --- low-memory boot/utility helpers --- */
extern void FUN_000026e8(word_t, ...);
extern cl4_result_t FUN_00019858(word_t, ...);
extern void FUN_00021480(word_t, ...);
extern void FUN_0006b6f4(word_t, ...);
extern void FUN_0007767c(word_t, ...);
extern void FUN_00077698(word_t, ...);
extern cl4_result_t FUN_0007c1c4(word_t, ...);
extern void FUN_000839d8(word_t, ...);
extern word_t FUN_000839f8(word_t, ...);
extern void FUN_00084180(word_t, ...);
extern void FUN_000841a0(word_t, ...);
extern void FUN_00084220(word_t, ...);
extern void FUN_00084234(word_t, ...);
extern void FUN_0008e388(word_t, ...);
extern void FUN_0008e500(word_t, ...);
extern void FUN_0008e518(word_t, ...);
extern cl4_result_t FUN_0009461c(word_t, ...);
extern void FUN_000a6f88(word_t, ...);
extern void FUN_000b4390(word_t, ...);
extern cl4_result_t FUN_000b43d0(word_t, ...);
extern void FUN_00114330(word_t, ...);
extern word_t FUN_00117cc4(word_t, ...);
extern void FUN_0031d5a8(word_t, ...);

/* SoftwareBreakpoint intrinsic (unreachable trap). */
#define SK_BREAKPOINT() __builtin_trap()



/* FUN_0032cc70 @ 0x32cc70   (est. sk_exception_entry)
 * Top-level exception/syscall entry dispatcher. Runs the pre-entry
 * setup sequence (timer/cpu setup helpers), then branches on the
 * carry/zero flag state left by the earlier result: on the success
 * path it performs a capability-transfer/write (copies the incoming
 * value through the x19/x20 frame words), invokes the copy helper and
 * calls a completion routine; on the failure path it releases the
 * incoming word and runs a cleanup/return helper.
 * Ghidra: void FUN_0032cc70(void)
 * Confidence: low (flag-driven entry, decompiler lost input flag state)
 * Notes: callees FUN_0034d724/348d94/377824/34b57c (setup),
 *   FUN_00357104 (result), FUN_00358750 (copy),
 *   FUN_0034e974 (release), FUN_0036b270 (cleanup). */
void sk_exception_entry(void)
{
    FUN_0034d724(0);          /* pre-entry setup */
    FUN_00348d94(0);
    FUN_00377824(0);
    FUN_0034b57c(0);
    cl4_result_t r = FUN_00357104(0);   /* obtain entry result/selector */

    if (/* carry clear && !zero */1 && 0xffffffffffffffe6 < (int64_t)r.lo) {
        /* success path: commit capability write through frame words */
        *((word_t *)/* x19 */0) = *((word_t *)/* x20 */0);
        FUN_00358750(r.lo, r.hi, r.lo);   /* capability copy helper */
        ((void (*)(void))/* completion dispatch */0)();
    } else {
        FUN_0034e974(*((word_t *)/* x20 */0));   /* release incoming word */
        FUN_0036b270(0);                         /* cleanup/return */
    }
}

/* =====================================================================
/* Forward declarations of in-range callees defined below. */
void sk_cap_move(word_t *dst, word_t *src);
long sk_cap_pair_update(long dst, long src);
void sk_cap_release_commit(void);
void sk_cap_release_regs(void);
long sk_cap_swap_and_retain(long p1, long p2);
void sk_cap_validate_commit(void);
void sk_cap_validate_commit_b(void);
void sk_cap_validate_commit_c(void);
void sk_cap_validate_commit_d(void);
void sk_common_finalize(void);
void sk_dispatch2_10(void);
void sk_dispatch2_18(void);
void sk_dispatch2_20(void);
void sk_dispatch2_28(void);
void sk_dispatch3_18(void);
void sk_dispatch3_20(void);
void sk_dispatch3_28(void);
void sk_dispatch4_18(void);
void sk_dispatch4_20(void);
void sk_dispatch4_28(void);
void sk_dispatch5_18(word_t p1, word_t p2, long frame);
void sk_dispatch5_20(word_t p1, word_t p2, long frame);
void sk_dispatch5_28(word_t p1, word_t p2, long frame);
void sk_dispatch6_10(void);
void sk_dispatch6_18(void);
void sk_dispatch6_20(void);
void sk_dispatch6_28(void);
void sk_dispatch7_10(void);
void sk_dispatch7_18(void);
void sk_dispatch7_20(void);
void sk_dispatch7_28(void);
void sk_dispatch8_10(void);
void sk_dispatch8_18(void);
void sk_dispatch8_20(void);
void sk_dispatch8_28(void);
void sk_dispatch9_18(void);
void sk_dispatch9_20(void);
void sk_dispatch9_28(void);
void sk_dispatch_loop_10(void);
void sk_dispatch_loop_18(void);
void sk_dispatch_loop_20(void);
void sk_dispatch_loop_28(void);
void sk_dispatch_resume_0(void);
void sk_dispatch_resume_1(void);
void sk_dispatch_resume_2(void);
void sk_dispatch_resume_3(void);
void sk_dispatch_resume_4(void);
void sk_dispatch_resume_5(void);
void sk_dispatch_slot_10(void);
void sk_dispatch_slot_18(void);
void sk_dispatch_slot_18_3(void);
void sk_dispatch_slot_20(void);
void sk_dispatch_slot_20_3(void);
void sk_dispatch_slot_28(void);
void sk_dispatch_slot_28_3(void);
void sk_entry_commit_b(void);
void sk_entry_commit_c(void);
void sk_entry_commit_d(void);
void sk_entry_commit_store(void);
void sk_entry_copy_commit(void);
void sk_entry_dispatch_commit(void);
void sk_exception_entry(void);
void sk_fetch_and_release(void);
void sk_msg_array_copy(word_t p1, word_t p2, long frame);
word_t sk_msg_cap_validate_1(word_t p1, word_t p2, long frame);
ulong sk_msg_cap_validate_2(void);
word_t sk_msg_cap_validate_3(word_t p1, word_t p2, long frame);
word_t sk_msg_cap_validate_4(word_t p1, word_t p2, long frame);
word_t sk_msg_cap_validate_5(void);
void sk_msg_cap_validate_write(void);
void sk_msg_cap_validate_write_c(word_t p1, word_t p2, long frame);
void sk_msg_cap_validate_write_d(void);
ulong sk_msg_count_cap(void);
ulong sk_msg_count_cap_b(word_t p1, uint count);
void sk_msg_fill_loop(word_t p1, long frame);
void sk_msg_notify(word_t p1, word_t p2, long frame);
void sk_msg_peek(void);
void sk_msg_peek_dispatch(void);
void sk_msg_read_commit(void);
word_t sk_msg_recv_cap(void);
void sk_msg_slot_read(void);
word_t sk_msg_slot_read_b(void);
ulong sk_msg_slot_read_c(word_t p1, word_t p2, long frame);
void sk_msg_slot_read_d(void);
void sk_msg_slot_read_e(void);
void sk_msg_slot_write(word_t p1, word_t p2, uint count);
long sk_msg_tag_store(long frame);
void sk_msg_write_commit(void);
long sk_msg_write_commit_b(void);
void sk_null_0(void);
void sk_null_1(void);
void sk_pair_load_store(void);
void sk_pair_store_release(void);
void sk_release_common(void);
void sk_release_common_b(void);
void sk_release_fetch(void);
long sk_result_return_1(long frame);
word_t sk_result_return_2(word_t p1, long p2);
void sk_resume_2a(void);
void sk_resume_2b(void);
void sk_resume_2c(void);
void sk_resume_2d(void);
void sk_resume_2e(void);
void sk_resume_common(void);
void sk_resume_common_0(void);
void sk_resume_common_1(void);
void sk_resume_common_2(void);
void sk_resume_common_3(void);
void sk_resume_common_4(void);
void sk_resume_common_5(void);
void sk_resume_common_6(void);
void sk_resume_common_7(void);
void sk_sched_yield_common_0(void);
void sk_sched_yield_common_1(void);
void sk_sched_yield_common_2(void);
void sk_sched_yield_common_3(void);
void sk_sched_yield_common_d(void);
void sk_slot3_dispatch_10(void);
void sk_slot3_dispatch_18(void);
void sk_slot3_dispatch_20(void);
void sk_slot3_dispatch_28(void);
void sk_slot4_dispatch_10(word_t p1, word_t p2, long frame);
void sk_slot4_dispatch_18(word_t p1, word_t p2, long frame);
void sk_slot4_dispatch_20(word_t p1, word_t p2, long frame);
void sk_slot4_dispatch_28(word_t p1, word_t p2, long frame);
void sk_slot_dispatch_10(void);
void sk_slot_dispatch_18(void);
void sk_slot_dispatch_28(void);
void sk_slot_read_commit(void);
void sk_slot_setup_dispatch(word_t p1, long frame);
void sk_slot_setup_dispatch_b(void);
void sk_slot_setup_release(word_t p1, long frame);
void sk_slot_setup_release_b(word_t p1, long frame);
void sk_slot_validate_commit(long slot);
void sk_slot_validate_commit_b(long slot);
void sk_slot_write_value(void);
void sk_slot_write_value_b(void);
void sk_slot_write_value_c(word_t p1, word_t p2, uint count, long frame);
void sk_syscall_cap_copy2_10(void);
void sk_syscall_cap_copy2_20(void);
void sk_syscall_cap_copy3_18(word_t p1, word_t p2, long frame);
void sk_syscall_cap_copy3_28(word_t p1, word_t p2, long frame);
void sk_syscall_cap_copy4_18(void);
void sk_syscall_cap_copy4_28(void);
void sk_syscall_cap_copy5_10(word_t p1, word_t p2, long frame);
void sk_syscall_cap_copy5_20(word_t p1, word_t p2, long frame);
void sk_syscall_cap_copy6_18(word_t p1, word_t p2, long frame);
void sk_syscall_cap_copy6_28(word_t p1, word_t p2, long frame);
void sk_syscall_cap_copy7_18(word_t p1, word_t p2, long frame);
void sk_syscall_cap_copy7_20(word_t p1, word_t p2, long frame);
void sk_syscall_cap_copy7_28(word_t p1, word_t p2, long frame);
void sk_syscall_cap_copy_18(void);
void sk_syscall_cap_copy_18b(void);
void sk_syscall_cap_copy_20(void);
void sk_syscall_cap_copy_20b(void);
void sk_syscall_cap_copy_28(void);
void sk_syscall_cap_copy_28b(void);
void sk_syscall_enter_release(void);
void sk_syscall_entry_a(void);
void sk_syscall_entry_b(word_t p1, word_t p2, long frame);
void sk_syscall_entry_c(void);
void sk_syscall_entry_commit(void);
void sk_syscall_entry_dispatch_0(void);
void sk_syscall_entry_dispatch_1(void);
void sk_syscall_entry_dispatch_2(word_t p1, word_t p2, long frame);
void sk_syscall_entry_dispatch_3(word_t p1, word_t p2, long frame);
void sk_syscall_entry_dispatch_4(word_t p1, word_t p2, long frame);
void sk_syscall_msg_read(void);
void sk_syscall_msg_read_b(void);
void sk_syscall_msg_read_c(void);
void sk_syscall_msg_read_d(void);
void sk_syscall_msg_read_e(void);
void sk_syscall_msg_read_f(long p1, long frame);
void sk_syscall_msg_read_g(void);
void sk_syscall_msg_write(void);
void sk_syscall_msg_write_b(word_t p1, word_t p2, long frame);
void sk_syscall_msg_write_d(word_t p1, word_t p2, long frame);
void sk_syscall_msg_write_e(word_t p1, word_t p2, long frame);
void sk_syscall_msg_write_f(void);
void sk_syscall_msg_write_g(word_t p1, word_t p2, long frame);
void sk_syscall_msg_write_h(word_t p1, word_t p2, long frame);
void sk_syscall_msg_write_i(word_t p1, word_t p2, long frame);
void sk_tcb_finalize_a(void);
void sk_tcb_finalize_b(long tcb);
cl4_result_t sk_tcb_lookup(void);
long sk_tcb_lookup_commit(word_t p1, word_t p2, long code);
long sk_tcb_lookup_commit_b(word_t p1, word_t p2, long code);
void sk_tcb_release_extra(long tcb);
void sk_tcb_release_extra_b(void);
void sk_tcb_release_pair(long tcb);
void sk_tcb_release_regs_0(long tcb);
void sk_tcb_release_regs_1(long tcb);
void sk_tcb_release_regs_2(long tcb);
void sk_tcb_release_regs_3(long tcb);
void sk_tcb_release_regs_4(long tcb);
void sk_tcb_release_regs_c(long tcb);
void sk_tcb_release_regs_d(long tcb);
void sk_tcb_release_regs_e(void);
void sk_tcb_validate_1(long tcb);
void sk_tcb_validate_1b(long tcb);
void sk_tcb_validate_1c(void);
word_t sk_tcb_validate_3(word_t p1, word_t p2, word_t code);
void sk_tcb_validate_commit(void);
word_t sk_wrapper_f970(word_t p1);

/* =====================================================================
 * Function bodies, in address order.
 * ===================================================================== */

/* FUN_0032cc70 @ 0x32cc70 (est. sk_syscall_entry_dispatch_0)
 * Top-level syscall entry. Runs the entry prelude, fetches the result
 * selector, then on the success path (carry-clear, zero-count == 0 and a
 * large returned word) commits the capability write through the frame
 * words (copy x20 slot into x19 slot), invokes the copy helper with the
 * result pair, and calls the completion dispatch. On failure it releases
 * the incoming word and runs the cleanup helper.
 * Confidence: low (flag-driven entry; decompiler lost input flag state).
 * Notes: callees FUN_0034d724/348d94/377824/34b57c (prelude),
 *   FUN_00357104 (selector), FUN_00358750 (copy),
 *   FUN_0034e974 (release), FUN_0036b270 (cleanup). */
void sk_syscall_entry_dispatch_0(void)
{
    FUN_0034d724(0);                 /* entry prelude */
    FUN_00348d94(0);                 /* fetch arg/cap word */
    FUN_00377824(0);                 /* fetch entry context */
    FUN_0034b57c(0);                 /* dispatch prelude */
    cl4_result_t sel = FUN_00357104(0);   /* result selector */

    if (/* carry clear && !zero */1 && 0xffffffffffffffe6 < (int64_t)sel.lo) {
        *((word_t *)/* x19 */0) = *((word_t *)/* x20 */0);
        FUN_00358750(sel.lo, sel.hi, sel.lo);
        ((void (*)(void))/* completion dispatch */0)();
    } else {
        FUN_0034e974(*((word_t *)/* x20 */0));   /* release incoming word */
        FUN_0036b270(0);                          /* cleanup */
    }
}

/* FUN_0032cd0c @ 0x32cd0c (est. sk_syscall_entry_dispatch_1)
 * Syscall entry: runs prelude, then dispatches through the capability
 * table entry at (table+8). The final indirect call is a jump through
 * the syscall dispatch table selected by the selector byte in the
 * entry context (table+0x50), with the destination slot's offset added
 * to the frame word.
 * Confidence: low (indirect jump table not recovered).
 * Notes: callees FUN_003561f4/348d94/377824/34bf0c; jumptable at 0x32cd60. */
void sk_syscall_entry_dispatch_1(void)
{
    FUN_003561f4(0);                 /* entry setup */
    word_t w = FUN_00348d94(0).lo;   /* fetch word */
    FUN_00377824(0);                 /* entry context */
    FUN_0034bf0c(0);                 /* setup continuation */
    /* dispatch via capability table (table+8), offsetting into frame */
    ((void (*)(word_t))0)(0);       /* indirect jump — table recovered */
}

/* FUN_0032cdc4 @ 0x32cdc4 (est. sk_syscall_entry_dispatch_2)
 * Syscall entry variant with an explicit caller frame (param_3). Pulls
 * the message words from param_3+0x18/+0x10, fetches the cap, then
 * dispatches through table slot (table+0x18) with two frame-addressed
 * arguments.
 * Confidence: low (indirect jump).
 * Notes: callees FUN_0034b264/348d94/377824/349530. */
void sk_syscall_entry_dispatch_2(word_t p1, word_t p2, long frame)
{
    word_t w = FUN_0034b264(0);
    FUN_00348d94(w, *(word_t *)(frame + 0x18), *(word_t *)(frame + 0x10));
    FUN_00377824(0);
    FUN_00349530(0);
    /* dispatch through table+0x18 with frame-addressed args */
    ((void (*)(word_t, word_t))0)(0, 0);
}

/* FUN_0032ce24 @ 0x32ce24 (est. sk_syscall_entry_dispatch_3)
 * Same shape as 0x32cdc4 but dispatches through table slot (table+0x20).
 * Confidence: low.
 * Notes: callees FUN_0034b264/348d94/377824/349530. */
void sk_syscall_entry_dispatch_3(word_t p1, word_t p2, long frame)
{
    word_t w = FUN_0034b264(0);
    FUN_00348d94(w, *(word_t *)(frame + 0x18), *(word_t *)(frame + 0x10));
    FUN_00377824(0);
    FUN_00349530(0);
    ((void (*)(word_t, word_t))0)(0, 0);   /* table+0x20 */
}

/* FUN_0032ce84 @ 0x32ce84 (est. sk_syscall_entry_dispatch_4)
 * Same shape as 0x32cdc4 but dispatches through table slot (table+0x28).
 * Confidence: low.
 * Notes: callees FUN_0034b264/348d94/377824/349530. */
void sk_syscall_entry_dispatch_4(word_t p1, word_t p2, long frame)
{
    word_t w = FUN_0034b264(0);
    FUN_00348d94(w, *(word_t *)(frame + 0x18), *(word_t *)(frame + 0x10));
    FUN_00377824(0);
    FUN_00349530(0);
    ((void (*)(word_t, word_t))0)(0, 0);   /* table+0x28 */
}

/* FUN_0032cee4 @ 0x32cee4 (est. sk_msg_recv_cap)
 * Receives/validates an incoming message capability. Runs the prelude,
 * fetches the result word and the entry limit (table+0x54) and selector
 * byte (table+0x50). If the caller word (w20) is zero, returns 0. If the
 * caller word is within the valid range it validates the capability slot
 * at the computed offset (sizes 1/2/4 via FUN_00356694), and on success
 * returns a resolved capability (FUN_00352f78) or falls through to the
 * out-of-range handler (FUN_000839f8).
 * Confidence: medium (seL4 message-cap validation pattern).
 * Notes: callees FUN_0034d724/348d94/377824/34ada0/356694/352f78/839f8;
 *   SoftwareBreakpoint on 4-byte mismatch. */
word_t sk_msg_recv_cap(void)
{
    FUN_0034d724(0);
    FUN_00348d94(0);
    FUN_00377824(0);
    word_t r = FUN_0034ada0(0);
    unsigned int limit = *(unsigned int *)/* table+0x54 */0;
    uint64_t sel  = (uint64_t)*(uint8_t *)/* table+0x50 */0;
    unsigned int caller = /* w20 */0;

    if (caller == 0) return 0;
    if (caller <= limit) goto out_of_range;
    long off = (long)(sel + 8 & ~sel) + *(long *)/* x8+0x40 */0;
    unsigned int sz = (unsigned int)off;
    int slot_width = /* extraout_w11 */0;   /* Ghidra register artifact */
    if (sz < 4) {
        FUN_00356694(r, limit, r);
        if (2 < sz && sz != 3) {
            unsigned int v = (slot_width >> 0x10) == 0
                ? (unsigned int)*(uint16_t *)((long)/* x19 */0 + off)
                : *(unsigned int *)((long)/* x19 */0 + off);
            if (v != 0) {
                r = FUN_00352f78(0);
                return r;
            }
        } else if (1 < slot_width) {
            unsigned int v = (unsigned int)*(uint8_t *)((long)/* x19 */0 + off);
            if (v != 0) {
                r = FUN_00352f78(0);
                return r;
            }
        }
    } else {
        unsigned int v = (unsigned int)*(uint8_t *)((long)/* x19 */0 + off);
        if (v != 0) {
            r = FUN_00352f78(0);
            return r;
        }
    }
    if (/* extraout */0 == 0) return 0;
out_of_range:
    r = FUN_000839f8((word_t)/* x19 */0 + sel + 8 & ~sel);
    return r;
}

/* FUN_0032d328 @ 0x32d328 (est. sk_dispatch_resume_0) */
void sk_dispatch_resume_0(void) { FUN_0034a32c(0); sk_entry_commit_d(); }
/* FUN_0032d354 @ 0x32d354 (est. sk_dispatch_resume_1) */
void sk_dispatch_resume_1(void) { FUN_0034a32c(0); sk_dispatch7_10(); }
/* FUN_0032d36c @ 0x32d36c (est. sk_dispatch_resume_2) */
void sk_dispatch_resume_2(void) { FUN_0034a32c(0); sk_dispatch7_18(); }
/* FUN_0032d384 @ 0x32d384 (est. sk_dispatch_resume_3) */
void sk_dispatch_resume_3(void) { FUN_0034a32c(0); sk_dispatch7_20(); }
/* FUN_0032d39c @ 0x32d39c (est. sk_dispatch_resume_4) */
void sk_dispatch_resume_4(void) { FUN_0034a32c(0); sk_dispatch7_28(); }
/* FUN_0032d3b4 @ 0x32d3b4 (est. sk_dispatch_resume_5) */
void sk_dispatch_resume_5(void) { FUN_0034a32c(0); sk_msg_cap_validate_5(); }
/* FUN_0032d3e0 @ 0x32d3e0 (est. sk_resume_common) */
void sk_resume_common(void) { FUN_00021480(0); }

/* FUN_0032d3f8 @ 0x32d3f8 (est. sk_result_return_2)
 * Returns a result word: releases the message word at param_2+8, runs
 * the cleanup helper, and passes the caller word back unchanged.
 * Confidence: medium. Notes: callees FUN_00355e98, FUN_0036b270. */
word_t sk_result_return_2(word_t p1, long p2)
{
    FUN_00355e98(*(word_t *)(p2 + 8));
    FUN_0036b270(0);
    return p1;
}

/* FUN_0032d434 @ 0x32d434 (est. sk_result_return_1)
 * Like 0x32d3f8 but uses the other cleanup helper and takes one frame arg.
 * Confidence: medium. Notes: callees FUN_00355e98, FUN_0036b118. */
long sk_result_return_1(long frame)
{
    FUN_00355e98(*(word_t *)(frame + 8));
    FUN_0036b118(0);
    return frame;
}

/* FUN_0032d47c @ 0x32d47c (est. sk_tcb_release_regs_0)
 * Releases a TCB's register save at the given offset: looks up the
 * register cap (tag 0x13f) for param_1+0x50; if present (<0x40 size),
 * releases the saved registers and runs the completion helpers.
 * Confidence: medium. Notes: callees FUN_00377dcc, 353424, 34d034,
 *   374104, 354c58. */
void sk_tcb_release_regs_0(long tcb)
{
    cl4_result_t r = FUN_00377dcc(0x13f, *(word_t *)(tcb + 0x50));
    if (r.hi < 0x40) {
        FUN_00353424(*(long *)(r.lo + -8) + 0x40);
        FUN_0034d034(0);
        FUN_00374104(0);
        FUN_00354c58(0);
    }
}

/* FUN_0032d4f0 @ 0x32d4f0 (est. sk_sched_yield_common_0) */
void sk_sched_yield_common_0(void) { FUN_00353498(0); FUN_00374104(0); FUN_003546b4(0); }
/* FUN_0032d538 @ 0x32d538 (est. sk_sched_yield_common_1) */
void sk_sched_yield_common_1(void) { FUN_00352b38(0); FUN_00374104(0); FUN_003546b4(0); }
/* FUN_0032d58c @ 0x32d58c (est. sk_sched_yield_common_2) */
void sk_sched_yield_common_2(void) { FUN_00353498(0); FUN_00374104(0); FUN_003546b4(0); }
/* FUN_0032d5bc @ 0x32d5bc (est. sk_sched_yield_common_3) */
void sk_sched_yield_common_3(void) { FUN_00353498(0); FUN_00374104(0); FUN_003546b4(0); }

/* FUN_0032d5ec @ 0x32d5ec (est. sk_tcb_release_regs_1)
 * Same as 0x32d47c but register-save offset param_1+0xb8.
 * Confidence: medium. */
void sk_tcb_release_regs_1(long tcb)
{
    cl4_result_t r = FUN_00377dcc(0x13f, *(word_t *)(tcb + 0xb8));
    if (r.hi < 0x40) {
        FUN_00353424(*(long *)(r.lo + -8) + 0x40);
        FUN_0034d034(0);
        FUN_00374104(0);
        FUN_00354c58(0);
    }
}

/* FUN_0032d65c @ 0x32d65c (est. sk_tcb_release_regs_2) offset +0x140 */
void sk_tcb_release_regs_2(long tcb)
{
    cl4_result_t r = FUN_00377dcc(0x13f, *(word_t *)(tcb + 0x140));
    if (r.hi < 0x40) {
        FUN_00353424(*(long *)(r.lo + -8) + 0x40);
        FUN_0034d034(0);
        FUN_00374104(0);
        FUN_00354c58(0);
    }
}

/* FUN_0032d6cc @ 0x32d6cc (est. sk_tcb_release_regs_3) offset +0x158 */
void sk_tcb_release_regs_3(long tcb)
{
    cl4_result_t r = FUN_00377dcc(0x13f, *(word_t *)(tcb + 0x158));
    if (r.hi < 0x40) {
        FUN_00353424(*(long *)(r.lo + -8) + 0x40);
        FUN_0034d034(0);
        FUN_00374104(0);
        FUN_00354c58(0);
    }
}

/* FUN_0032d73c @ 0x32d73c (est. sk_tcb_release_regs_4) offset +0x160 */
void sk_tcb_release_regs_4(long tcb)
{
    cl4_result_t r = FUN_00377dcc(0x13f, *(word_t *)(tcb + 0x160));
    if (r.hi < 0x40) {
        FUN_00353424(*(long *)(r.lo + -8) + 0x40);
        FUN_0034d034(0);
        FUN_00374104(0);
        FUN_00354c58(0);
    }
}

/* FUN_0032d7ac @ 0x32d7ac (est. sk_cap_swap_and_retain)
 * Swaps two capability words: releases the message word at param_2+8,
 * retains the one at param_1+8, returns param_1.
 * Confidence: medium. Notes: callees FUN_00355e98/36b270/36b118. */
long sk_cap_swap_and_retain(long p1, long p2)
{
    word_t w = *(word_t *)(p1 + 8);
    FUN_00355e98(*(word_t *)(p2 + 8));
    FUN_0036b270(0);
    FUN_0036b118(w);
    return p1;
}

/* FUN_0032d800 @ 0x32d800 (est. sk_fetch_and_release)
 * Fetches the current word, releases it.
 * Confidence: medium. Notes: callees FUN_00350e04, FUN_0036b270. */
void sk_fetch_and_release(void)
{
    word_t w = FUN_00350e04(0);
    FUN_0036b270(w);
}

/* FUN_0032d82c @ 0x32d82c (est. sk_pair_swap)
 * Swaps two 16-byte pairs: stores src words into dst, releases the old
 * dst words.
 * Confidence: medium. Notes: callees FUN_0036b270/36b118. */
word_t *sk_pair_swap(word_t *dst, word_t *src)
{
    word_t d0 = dst[0], s1 = src[1];
    dst[0] = src[0];
    FUN_0036b270(0);
    FUN_0036b118(d0);
    dst[1] = s1;
    return dst;
}

/* FUN_0032d874 @ 0x32d874 (est. sk_pair_load_store)
 * Loads the current 16-byte pair (via FUN_003504d0), releases the first
 * stored word, and stores the pair into the frame.
 * Confidence: medium. Notes: callees FUN_003504d0/36b118. */
void sk_pair_load_store(void)
{
    word_t *cur = (word_t *)FUN_003504d0(0);
    FUN_0036b118(*cur);
    word_t w = *(word_t *)/* x19 */0;
    *(word_t *)/* x20 */1 = *(word_t *)/* x19 */1;
    *(word_t *)/* x20 */0 = w;
}

/* FUN_0032d924 @ 0x32d924 (est. sk_syscall_entry_a)
 * Syscall entry variant: prelude, fetch result; on success path (zero-set
 * and result word < 0x19) commit via FUN_0034df14, call the dispatch
 * helper, then run FUN_00349cd0/3535e4. On failure runs FUN_00349a9c.
 * Confidence: low (flag-driven entry).
 * Notes: callees FUN_0034d724/349830/377824/34b57c/35510c/34c144. */
void sk_syscall_entry_a(void)
{
    FUN_0034d724(0);
    FUN_00349830(0);
    FUN_00377824(0);
    FUN_0034b57c(0);
    FUN_0035510c(/* x16 */0);
    cl4_result_t r = FUN_0034c144(0);
    if (/* zero-set && */ (ulong)0 < 0x19) {
        FUN_0034df14(r.lo, r.hi, r.lo);
        ((void (*)(void))/* dispatch */0)();
        FUN_00349cd0(0);
        FUN_003535e4(0);
    } else {
        FUN_00349a9c(0);
    }
    FUN_0036b270(0);
}

/* FUN_0032d9c8 @ 0x32d9c8 (est. sk_dispatch_slot_10)
 * Dispatch entry: setup, then call table slot (table+0x10), then
 * FUN_00349104(table+0x40), FUN_0034f22c, cleanup.
 * Confidence: low (indirect table dispatch). */
void sk_dispatch_slot_10(void)
{
    FUN_0034dbd8(0);
    FUN_00349830(0);
    FUN_00377824(0);
    FUN_00349530(0);
    ((void (*)(void))0)();
    FUN_00349104(*(word_t *)/* table+0x40 */0);
    FUN_0034f22c(0);
    FUN_0036b270(0);
}

/* FUN_0032da30 @ 0x32da30 (est. sk_dispatch_slot_18) */
void sk_dispatch_slot_18(void)
{
    FUN_0034dbd8(0);
    FUN_00349830(0);
    FUN_00377824(0);
    FUN_00349530(0);
    ((void (*)(void))0)();
    FUN_00349104(*(word_t *)/* table+0x40 */0);
    word_t w = *(word_t *)/* x9+8 */0;
    FUN_0034f22c(0);
    FUN_0036b270(0);
    FUN_0036b118(w);
}

/* FUN_0032daa4 @ 0x32daa4 (est. sk_dispatch_slot_20) */
void sk_dispatch_slot_20(void)
{
    FUN_0034dbd8(0);
    FUN_00349830(0);
    FUN_00377824(0);
    FUN_00349530(0);
    ((void (*)(void))0)();
    FUN_00349104(*(word_t *)/* table+0x40 */0);
    FUN_00352dac(0);
}

/* FUN_0032db08 @ 0x32db08 (est. sk_dispatch_slot_28) */
void sk_dispatch_slot_28(void)
{
    FUN_0034dbd8(0);
    FUN_00349830(0);
    FUN_00377824(0);
    FUN_00349530(0);
    ((void (*)(void))0)();
    FUN_00349104(*(word_t *)/* table+0x40 */0);
    FUN_00352dac(*(word_t *)/* x9+8 */0);
    FUN_0036b118(0);
}

/* FUN_0032db74 @ 0x32db74 (est. sk_msg_count_cap)
 * Reads/validates a message count capability from the frame. Runs the
 * prelude, fetches the result and limit. If the caller word (w20) is
 * nonzero and exceeds the limit, resolves the capability slot at the
 * computed offset (size 1/2/4 via FUN_00356638), returning
 * FUN_00356e64 result. Otherwise, on a small result (<0x1000) returns
 * the incremented count, else falls to the out-of-range handler.
 * Confidence: medium (seL4 message-count validation).
 * Notes: callees FUN_0034d724/349830/377824/34ada0/355008/356638/
 *   356e64/34de54/839f8; SoftwareBreakpoint on size-3. */
ulong sk_msg_count_cap(void)
{
    FUN_0034d724(0);
    FUN_00349830(0);
    FUN_00377824(0);
    word_t r = FUN_0034ada0(0);
    cl4_result_t c = FUN_00355008(r, *(uint *)/* table+0x54 */0);
    word_t count = c.hi;
    uint caller = /* w20 */0;
    if (caller == 0) return 0;
    if (/* extraout_w9 */0 < caller) {
        FUN_00356638(*(word_t *)/* x8+0x40 */0, c.lo, count, c.lo);
        ulong off = /* x10 */0 + 0x10;
        uint size = 2;
        if ((off & 0xfffffff8) == 0) size = /* w12 */0 + 1;
        if (0xffff < size) size = 4;
        if (size < 0x100) size = 1;
        uint sel = (1 < size) ? size : 0;
        count = /* x1 */0;
        switch (sel) {
        case 1:
            if (*(byte *)((long)/* x19 */0 + off) != 0) {
                int i = (off & 0xfffffff8) ? 0 : (int)*(byte *)((long)/* x19 */0 + off) - 1;
                return FUN_00356e64(i);
            }
            break;
        case 2:
            if (*(ushort *)((long)/* x19 */0 + off) != 0) {
                int i = (off & 0xfffffff8) ? 0 : (int)*(ushort *)((long)/* x19 */0 + off) - 1;
                return FUN_00356e64(i);
            }
            break;
        case 3:
            SK_BREAKPOINT();   /* SoftwareBreakpoint(1,0x32dc94) */
        case 4:
            if (*(uint *)((long)/* x19 */0 + off) != 0) {
                int i = (off & 0xfffffff8) ? 0 : (int)*(uint *)((long)/* x19 */0 + off) - 1;
                return FUN_00356e64(i);
            }
        }
    }
    if ((uint)count < 0x1000) {
        FUN_0034de54(0);
        ulong v = 0;
        if (/* *x8_00 */0 < 0x1000) v = (int)/* *x8_00 */0 + 1;
        return v;
    }
    return FUN_000839f8(0);
}

/* FUN_0032de58 @ 0x32de58 (est. sk_syscall_enter_release)
 * Syscall entry with release: runs setup, fetches the result pair; if
 * the size word is < 0x40, releases the message, resolves and commits
 * (FUN_0035298c), then on the success/size==0x3f path releases the
 * saved registers and runs the completion helpers. Otherwise forces the
 * size to 0x3f and returns the pair.
 * Confidence: medium.
 * Notes: callees FUN_00357cb4/355160/3502c8/377824/34de44/35298c/
 *   357acc/3558b8/34d1c0/3728b8/19858/357c74. */
void sk_syscall_enter_release(void)
{
    FUN_00357cb4(0);
    FUN_00355160(0);
    FUN_003502c8(0x13f);
    cl4_result_t r = FUN_00377824(0);
    ulong sz = r.hi, base = r.lo;
    int is_big = 0x3e < sz, is_3f = (sz == 0x3f);
    if (sz < 0x40) {
        FUN_0034de44(0);
        cl4_result_t r2 = FUN_00377824(0);
        FUN_0035298c(r2.lo, r2.hi, r2.lo);
        FUN_00377824(0);
        long l = FUN_00357acc(0);
        if (!is_big || is_3f) {
            FUN_003558b8(*(long *)(l + -8) + 0x40);
            FUN_0034d1c0(0);
            FUN_003728b8(0);
            cl4_result_t r3 = FUN_00019858(0);
            sz = r3.hi; base = r3.lo;
        }
    } else {
        sz = 0x3f;
    }
    FUN_00357c74(base, sz, /* x1 */0);
}

/* FUN_0032df20 @ 0x32df20 (est. sk_syscall_msg_write)
 * Syscall message write path. Runs the prelude (FUN_0008e518/350c5c/
 * 353b7c/34c920/377824/348e00/356bd4/34e5bc/377824/350500/377824/
 * 000a6f88), computes the destination offset from the entry context, and
 * on the success path writes the message words through the dispatch
 * helper, else runs the fault handler.
 * Confidence: low (flag-driven).
 * Notes: callees include FUN_000839f8/3595b4/34ee88/839d8/117cc4/34de74. */
void sk_syscall_msg_write(void)
{
    FUN_0008e518(0);
    FUN_00350c5c(0);
    FUN_00353b7c(0);
    FUN_0034c920(0);
    FUN_00377824(0);
    FUN_00348e00(0);
    long dst = *(long *)/* x8+0x40 */0;
    FUN_00356bd4(0);
    FUN_0034e5bc(0);
    cl4_result_t r = FUN_00377824(0);
    FUN_00350500(r.lo, r.hi, r.lo);
    FUN_00377824(0);
    FUN_000a6f88(0);
    dst = dst + (ulong)(byte)*(uint *)/* table+0x50 */0;
    long lim = *(long *)/* x8_00+0x40 */0;
    int zero = (*(int *)/* table+0x54 */0 == 0);
    if (zero) lim = lim + 1;
    word_t sz = FUN_0034d5d8(*(uint *)/* table+0x50 */0 & 0xff);
    if ((zero /* && ... */) && (ulong)/* x11 */0 < 0x19) {
        FUN_0034bfb4(*(word_t *)/* table+0x10 */0);
        ((void (*)(void))0)();
        FUN_003518dc(dst + /* x20 */0);
        if (FUN_000839f8(0) == 0) {
            cl4_result_t r2 = FUN_003595b4(*(word_t *)/* table+0x10 */0);
            ((void (*)(word_t, word_t, word_t))0)(r2.lo, r2.hi, sz);
            FUN_0034ee88(dst + /* x19 */0);
            FUN_000839d8(0);
        } else {
            cl4_result_t r2 = FUN_003595b4(0);
            FUN_00117cc4(r2.lo, r2.hi, lim);
        }
    } else {
        FUN_0034de74(0);
    }
    FUN_0008e500(0);
}

/* FUN_0032e07c @ 0x32e07c (est. sk_syscall_msg_read)
 * Syscall message read path. Runs setup, reads the message word at the
 * destination, and on success commits the read result, else returns the
 * current state.
 * Confidence: low (indirect jump table).
 * Notes: callees FUN_00357cb4/350c5c/34e7e0/34c444/377824/841a0/
 *   350798/350fbc/35163c/839f8/35631c/357c74. */
void sk_syscall_msg_read(void)
{
    FUN_00357cb4(0);
    FUN_00350c5c(0);
    FUN_0034e7e0(0);
    FUN_0034c444(0);
    FUN_00377824(0);
    FUN_000841a0(0);
    ((void (*)(void))0)();
    long dst = *(long *)/* table+0x40 */0;
    word_t extra = *(word_t *)/* x20+0x20 */0;
    FUN_0034c444(0xff);
    void *jt = (void *)FUN_00377824(0).lo;
    FUN_00350798(0);
    FUN_00377824(0);
    FUN_00350fbc(0);
    ulong sel = (ulong)*(byte *)/* table+0x50 */0;
    ulong addr = dst + /* x19 */0 + sel;
    FUN_0035163c(addr & ~sel);
    if (FUN_000839f8(0) != 0) {
        FUN_00357c74(/* x30 */0);
        return;
    }
    FUN_0035631c(0);
    FUN_00357c74(addr & ~sel, extra);
    ((void (*)(void))jt)();   /* indirect jump */
}

/* FUN_0032e234 @ 0x32e234 (est. sk_syscall_cap_copy_18)
 * Capability copy path (table slot 0x18). Runs setup, copies the message
 * cap via FUN_0034e6dc, resolves the target slot (FUN_0034f138); on the
 * success path installs the cap (FUN_0034f828) and dispatch, on the
 * error path resolves/commits the error result.
 * Confidence: low (indirect dispatch).
 * Notes: callees FUN_00084220/34a914/349530/355780/34be0c/377824/
 *   34e6dc/3503b0/34f138/34f828/355868/355e44/354070/352f3c/117cc4. */
void sk_syscall_cap_copy_18(void)
{
    FUN_00084220(0);
    FUN_0034a914(0);
    FUN_00349530(0);
    ((void (*)(void))0)();
    long dst = *(long *)/* table+0x40 */0;
    FUN_00355780(0);
    FUN_0034be0c(0);
    cl4_result_t r = FUN_00377824(0);
    FUN_0034e6dc(r.lo, r.hi, r.lo);
    FUN_00377824(0);
    FUN_003503b0(0);
    byte sel = *(byte *)/* table+0x50 */0;
    int st = FUN_0034f138(dst + (ulong)sel);
    if (/* w20 */0 == 0) {
        if (st == 0) {
            FUN_0034f828(*(word_t *)/* table+0x18 */0);
            ((void (*)(void))0)();
            goto done;
        }
        FUN_00355868(0);
        ((void (*)(void))0)();
        r = FUN_00355e44(0);
    } else {
        if (st == 0) {
            FUN_0034f828(*(word_t *)/* table+0x10 */0);
            ((void (*)(void))0)();
            FUN_0034befc(/* x24 */0 & ~(ulong)sel);
            FUN_000839d8(0);
            goto done;
        }
        r = FUN_00354070(0);
    }
    long idx = /* x9 */0;
    if (/* extraout */0 == 0) idx = idx + 1;
    FUN_00352f3c(r.lo, r.hi, idx);
    FUN_00117cc4(0);
done:
    FUN_00084234(0);
}

/* FUN_0032e340 @ 0x32e340 (est. sk_syscall_cap_copy_20) table slot 0x20 */
void sk_syscall_cap_copy_20(void)
{
    FUN_00084220(0);
    FUN_0034a914(0);
    FUN_00349530(0);
    ((void (*)(void))0)();
    long dst = *(long *)/* table+0x40 */0;
    FUN_00355780(0);
    FUN_0034be0c(0);
    cl4_result_t r = FUN_00377824(0);
    FUN_0034e6dc(r.lo, r.hi, r.lo);
    FUN_00377824(0);
    FUN_003503b0(0);
    ulong sel = (ulong)*(byte *)/* table+0x50 */0;
    long addr = dst + sel;
    FUN_003513e4(addr + /* x20 */0 & ~sel);
    if (FUN_000839f8(0) == 0) {
        FUN_003550e0(*(word_t *)/* table+0x20 */0);
        ((void (*)(void))0)();
        FUN_0034befc(addr + /* x19 */0 & ~sel);
        FUN_000839d8(0);
    } else {
        FUN_00351608(0);
    }
    FUN_00084234(0);
}

/* FUN_0032e414 @ 0x32e414 (est. sk_syscall_cap_copy_28) table slot 0x28 */
void sk_syscall_cap_copy_28(void)
{
    FUN_00084220(0);
    FUN_0034a914(0);
    FUN_00349530(0);
    ((void (*)(void))0)();
    long dst = *(long *)/* table+0x40 */0;
    FUN_00355780(0);
    FUN_0034be0c(0);
    cl4_result_t r = FUN_00377824(0);
    FUN_0034e6dc(r.lo, r.hi, r.lo);
    FUN_00377824(0);
    FUN_003503b0(0);
    byte sel = *(byte *)/* table+0x50 */0;
    int st = FUN_0034f138(dst + (ulong)sel);
    if (/* w20 */0 == 0) {
        if (st == 0) {
            FUN_0034f828(*(word_t *)/* table+0x28 */0);
            ((void (*)(void))0)();
            goto done;
        }
        FUN_00355868(0);
        ((void (*)(void))0)();
        r = FUN_00355e44(0);
    } else {
        if (st == 0) {
            FUN_0034f828(*(word_t *)/* table+0x20 */0);
            ((void (*)(void))0)();
            FUN_0034befc(/* x24 */0 & ~(ulong)sel);
            FUN_000839d8(0);
            goto done;
        }
        r = FUN_00354070(0);
    }
    long idx = /* x9 */0;
    if (/* extraout */0 == 0) idx = idx + 1;
    FUN_00352f3c(r.lo, r.hi, idx);
    FUN_00117cc4(0);
done:
    FUN_00084234(0);
}

/* FUN_0032e520 @ 0x32e520 (est. sk_msg_cap_validate_write)
 * Validates a message capability for write. Runs setup and the size/
 * limit checks; on a valid non-empty slot resolves and returns the
 * capability, else falls through to fault/out-of-range handling.
 * Confidence: medium (seL4 msg-cap validation pattern).
 * Notes: callees FUN_0008e518/352758/353b7c/34c920/377824/352820/
 *   356bd4/34e5bc/377824/350500/377824/34c11c/358194/3550cc/34d5b8/
 *   3525b8/3538d4/34e32c/351538/34bf1c/3520e8/839f8/3585dc/8e500. */
void sk_msg_cap_validate_write(void)
{
    FUN_0008e518(0);
    FUN_00352758(0);
    FUN_00353b7c(0);
    FUN_0034c920(0);
    FUN_00377824(0);
    FUN_00352820(0);
    uint limit = *(uint *)/* table+0x54 */0;
    FUN_00356bd4(0);
    FUN_0034e5bc(0);
    cl4_result_t r = FUN_00377824(0);
    FUN_00350500(r.lo, r.hi, r.lo);
    FUN_00377824(0);
    FUN_0034c11c(0);
    int zero = (*(int *)/* table2+0x54 */0 == 0);
    word_t out = 0;
    if (/* w22 */0 == 0) {
        out = 0;
    } else {
        FUN_00358194(*(word_t *)/* x8+0x40 */0);
        uint v = /* extraout_w11 */0;
        if (1 /* bVar2 && !bVar3 */) {
            FUN_003550cc(0);
            long off = /* x12 */0;
            int st = /* w10 */0;
            v = /* w11_00 */0;
            if (!1 || zero) {
                FUN_0034d5b8(0);
                st = /* w10_00 */0;
                v = /* w11_01 */0;
                if (1 && !zero) {
                    uint b = ((/* w14 */0 >> 0x10) == 0)
                        ? (uint)*(ushort *)((long)/* x19 */0 + /* x12_00 */0)
                        : *(uint *)((long)/* x19 */0 + /* x12_00 */0);
                    if (b != 0) {
                        FUN_003525b8(0);
                        if (/* w12 */0 != 0) {
                            FUN_003538d4(0);
                            switch (/* w9 */0) { default: case 2: case 3: FUN_0034e32c(0); case 4: break; }
                        }
                        out = FUN_00351538(0);
                        goto done;
                    }
                } else {
                    long o2 = /* x12_00 */0;
                    if (1 < /* w14 */0) {
                        uint b = (uint)*(byte *)((long)/* x19 */0 + o2);
                        if (b != 0) {
                            FUN_003525b8(0);
                            if (/* w12 */0 != 0) {
                                FUN_003538d4(0);
                                switch (/* w9 */0) { default: case 2: case 3: FUN_0034e32c(0); case 4: break; }
                            }
                            out = FUN_00351538(0);
                            goto done;
                        }
                    }
                }
            } else {
                uint b = (uint)*(byte *)((long)/* x19 */0 + off);
                if (b != 0) {
                    FUN_003525b8(0);
                    if (/* w12 */0 != 0) {
                        FUN_003538d4(0);
                        switch (/* w9 */0) { default: case 2: case 3: FUN_0034e32c(0); case 4: break; }
                    }
                    out = FUN_00351538(0);
                    goto done;
                }
            }
            if (st == 0) { out = 0; goto done; }
        }
        if (v <= limit) {
            FUN_0034bf1c(0);
            FUN_0008e500(0);
            FUN_000839f8(0);
            return;
        }
        FUN_003520e8(0);
        FUN_000839f8(0);
        out = FUN_003585dc(0);
    }
done:
    FUN_0008e500(out, /* x30 */0);
}

/* FUN_0032e9dc @ 0x32e9dc (est. sk_tcb_release_extra)
 * Releases extra TCB state: validates register caps (tag 0x13f) at
 * param_1+0x10/+0x18, releases and completes on success.
 * Confidence: medium.
 * Notes: callees FUN_0034a32c/350548/377824/348f14/351930/357acc/
 *   3558b8/34d1c0/3728b8/19858. */
void sk_tcb_release_extra(long tcb)
{
    word_t r1 = *(word_t *)(tcb + 0x10);
    word_t r2 = *(word_t *)(tcb + 0x18);
    FUN_0034a32c(0);
    FUN_00350548(0x13f);
    FUN_00377824(0);
    int is_big = 0x3e < /* x1 */0;
    int is_3f = (/* x1 */0 == 0x3f);
    if (/* x1 */0 < 0x40) {
        FUN_00348f14(r2);
        cl4_result_t r = FUN_00377824(0xff, /* x1_00 */0, r1);
        FUN_0034a32c(r.lo, r.hi, r.lo);
        FUN_00351930(0);
        FUN_00377824(0);
        long l = FUN_00357acc(0);
        if (!is_big || is_3f) {
            FUN_003558b8(*(long *)(l + -8) + 0x40);
            FUN_0034d1c0(0);
            FUN_003728b8(0);
            FUN_00019858(0);
        }
    }
}

/* FUN_0032eaa0 @ 0x32eaa0 (est. sk_syscall_msg_write_b)
 * Message write path variant (like 0x32df20 but different prelude).
 * Confidence: low.
 * Notes: callees FUN_0008e518/350c5c/34c920/353504/377824/348e00/
 *   348f14/377824/34d734/353504/377824/000a6f88/34d5d8/34bfb4/
 *   3518dc/839f8/3595b4/34ee88/839d8/117cc4/34de74/8e500. */
void sk_syscall_msg_write_b(word_t p1, word_t p2, long frame)
{
    FUN_0008e518(0);
    FUN_00350c5c(0);
    word_t u5 = *(word_t *)(frame + 0x10);
    word_t u1 = *(word_t *)(frame + 0x18);
    FUN_0034c920(0);
    FUN_00353504(0);
    FUN_00377824(0);
    FUN_00348e00(0);
    long dst = *(long *)/* x8+0x40 */0;
    FUN_00348f14(u1);
    FUN_00377824(0xff, /* x1 */0, u5);
    FUN_0034d734(0);
    FUN_00353504(0);
    FUN_00377824(0);
    FUN_000a6f88(0);
    dst = dst + (ulong)(byte)*(uint *)/* table+0x50 */0;
    long lim = *(long *)/* x8_00+0x40 */0;
    int zero = (*(int *)/* table+0x54 */0 == 0);
    if (zero) lim = lim + 1;
    word_t sz = FUN_0034d5d8(*(uint *)/* table+0x50 */0 & 0xff);
    if ((zero /*&&...*/) && (ulong)/* x11 */0 < 0x19) {
        FUN_0034bfb4(*(word_t *)/* table+0x10 */0);
        ((void (*)(void))0)();
        FUN_003518dc(dst + /* x20 */0);
        if (FUN_000839f8(0) == 0) {
            cl4_result_t r = FUN_003595b4(*(word_t *)/* table+0x10 */0);
            ((void (*)(word_t, word_t, word_t))0)(r.lo, r.hi, sz);
            FUN_0034ee88(dst + /* x19 */0);
            FUN_000839d8(0);
        } else {
            cl4_result_t r = FUN_003595b4(0);
            FUN_00117cc4(r.lo, r.hi, lim);
        }
    } else {
        FUN_0034de74(0);
    }
    FUN_0008e500(0);
}

/* FUN_0032ec04 @ 0x32ec04 (est. sk_syscall_msg_read_b)
 * Message read path variant.
 * Confidence: low (indirect jump).
 * Notes: callees FUN_00354744/350c5c/34c444/377824/841a0/348f14/
 *   377824/350798/351978/377824/350fbc/35163c/839f8/35631c/3544c8. */
void sk_syscall_msg_read_b(void)
{
    FUN_00354744(0);
    FUN_00350c5c(0);
    word_t u2 = *(word_t *)/* x1+0x10 */0;
    word_t u3 = *(word_t *)/* x1+0x18 */0;
    FUN_0034c444(0);
    FUN_00377824(0);
    FUN_000841a0(0);
    ((void (*)(void))0)();
    long dst = *(long *)/* table+0x40 */0;
    word_t extra = *(word_t *)/* x20+0x20 */0;
    FUN_00348f14(u3);
    void *jt = (void *)FUN_00377824(0xff, 0, u2).lo;
    FUN_00350798(0);
    FUN_00351978(0);
    FUN_00377824(0);
    FUN_00350fbc(0);
    ulong sel = (ulong)*(byte *)/* table+0x50 */0;
    ulong addr = dst + /* x19 */0 + sel;
    FUN_0035163c(addr & ~sel);
    if (FUN_000839f8(0) != 0) {
        FUN_003544c8(/* x30 */0);
        return;
    }
    FUN_0035631c(0);
    FUN_003544c8(addr & ~sel, extra);
    ((void (*)(void))jt)();   /* indirect jump */
}

/* FUN_0032edec @ 0x32edec (est. sk_syscall_cap_copy_18b) table slot 0x18 */
void sk_syscall_cap_copy_18b(void)
{
    FUN_00084220(0);
    FUN_0034bbb4(0);
    FUN_0034ac8c(0);
    FUN_00377824(0);
    FUN_00349530(0);
    ((void (*)(void))0)();
    long dst = *(long *)/* table+0x40 */0;
    FUN_00348f14(0);
    cl4_result_t r = FUN_00358410(0);
    FUN_0034e6dc(r.lo, r.hi, r.lo);
    FUN_00377824(0);
    FUN_003503b0(0);
    byte sel = *(byte *)/* table+0x50 */0;
    int st = FUN_0034f138(dst + (ulong)sel);
    if (/* w20 */0 == 0) {
        if (st == 0) {
            FUN_0034f828(*(word_t *)/* table+0x18 */0);
            ((void (*)(void))0)();
            goto done;
        }
        FUN_00355868(0);
        ((void (*)(void))0)();
        r = FUN_00355e44(0);
    } else {
        if (st == 0) {
            FUN_0034f828(*(word_t *)/* table+0x10 */0);
            ((void (*)(void))0)();
            FUN_0034befc(~(ulong)sel & 0x60e208);
            FUN_000839d8(0);
            goto done;
        }
        r = FUN_00354070(0);
    }
    long idx = /* x9 */0;
    if (/* extraout */0 == 0) idx = idx + 1;
    FUN_00352f3c(r.lo, r.hi, idx);
    FUN_00117cc4(0);
done:
    FUN_00084234(0);
}

/* FUN_0032ef14 @ 0x32ef14 (est. sk_syscall_cap_copy_20b) table slot 0x20 */
void sk_syscall_cap_copy_20b(void)
{
    FUN_00084220(0);
    FUN_0034bbb4(0);
    FUN_0034ac8c(0);
    FUN_00377824(0);
    FUN_00349530(0);
    ((void (*)(void))0)();
    long dst = *(long *)/* table+0x40 */0;
    FUN_00348f14(0);
    cl4_result_t r = FUN_00358410(0);
    FUN_0034e6dc(r.lo, r.hi, r.lo);
    FUN_00377824(0);
    FUN_003503b0(0);
    ulong sel = (ulong)*(byte *)/* table+0x50 */0;
    long addr = dst + sel;
    FUN_003513e4(addr + /* x20 */0 & ~sel);
    if (FUN_000839f8(0) == 0) {
        FUN_003550e0(*(word_t *)/* table+0x20 */0);
        ((void (*)(void))0)();
        FUN_0034befc(addr + /* x19 */0 & ~sel);
        FUN_000839d8(0);
    } else {
        FUN_00351608(0);
    }
    FUN_00084234(0);
}

/* FUN_0032f004 @ 0x32f004 (est. sk_syscall_cap_copy_28b) table slot 0x28 */
void sk_syscall_cap_copy_28b(void)
{
    FUN_00084220(0);
    FUN_0034bbb4(0);
    FUN_0034ac8c(0);
    FUN_00377824(0);
    FUN_00349530(0);
    ((void (*)(void))0)();
    long dst = *(long *)/* table+0x40 */0;
    FUN_00348f14(0);
    cl4_result_t r = FUN_00358410(0);
    FUN_0034e6dc(r.lo, r.hi, r.lo);
    FUN_00377824(0);
    FUN_003503b0(0);
    byte sel = *(byte *)/* table+0x50 */0;
    int st = FUN_0034f138(dst + (ulong)sel);
    if (/* w20 */0 == 0) {
        if (st == 0) {
            FUN_0034f828(*(word_t *)/* table+0x28 */0);
            ((void (*)(void))0)();
            goto done;
        }
        FUN_00355868(0);
        ((void (*)(void))0)();
        r = FUN_00355e44(0);
    } else {
        if (st == 0) {
            FUN_0034f828(*(word_t *)/* table+0x20 */0);
            ((void (*)(void))0)();
            FUN_0034befc(~(ulong)sel & 0x60e208);
            FUN_000839d8(0);
            goto done;
        }
        r = FUN_00354070(0);
    }
    long idx = /* x9 */0;
    if (/* extraout */0 == 0) idx = idx + 1;
    FUN_00352f3c(r.lo, r.hi, idx);
    FUN_00117cc4(0);
done:
    FUN_00084234(0);
}

/* FUN_0032f12c @ 0x32f12c (est. sk_msg_cap_validate_write_c)
 * Message-capability validate/write variant.
 * Confidence: medium.
 * Notes: callees FUN_00077698/352758/34c920/353504/377824/352ff4/
 *   348f14/377824/34d734/353504/377824/34c11c/358194/3550cc/34d5b8/
 *   3525b8/3538d4/34e32c/351538/34bf1c/3520e8/839f8/3585dc/3507e0/
 *   7767c. */
void sk_msg_cap_validate_write_c(word_t p1, word_t p2, long frame)
{
    FUN_00077698(0);
    FUN_00352758(0);
    word_t u6 = *(word_t *)(frame + 0x10);
    word_t u1 = *(word_t *)(frame + 0x18);
    FUN_0034c920(0);
    FUN_00353504(0);
    word_t u5 = FUN_00377824(0).lo;
    FUN_00352ff4(0);
    uint limit = *(uint *)/* table+0x54 */0;
    FUN_00348f14(u1);
    FUN_00377824(0xff, /* x1 */0, u6);
    FUN_0034d734(0);
    FUN_00353504(0);
    FUN_00377824(0);
    FUN_0034c11c(0);
    int zero = (*(int *)/* table+0x54 */0 == 0);
    word_t out = 0;
    if (/* w22 */0 == 0) {
        out = 0;
    } else {
        uint v = /* w11 */0;
        if (1 /*&& !zero*/) {
            FUN_003550cc(0);
            long off = /* x12 */0;
            int st = /* w10 */0;
            v = /* w11_00 */0;
            if (!1 || zero) {
                FUN_0034d5b8(0);
                st = /* w10_00 */0;
                v = /* w11_01 */0;
                if (1 && !zero) {
                    uint b = ((/* w14 */0 >> 0x10) == 0) ? (uint)*(ushort *)((long)/* x19 */0 + /* x12_00 */0) : *(uint *)((long)/* x19 */0 + /* x12_00 */0);
                    if (b != 0) {
                        FUN_003525b8(0);
                        if (/* w12 */0 != 0) {
                            FUN_003538d4(0);
                            switch (/* w9 */0) { default: case 2: case 3: FUN_0034e32c(0); case 4: break; }
                        }
                        out = FUN_00351538(0);
                        goto done;
                    }
                } else {
                    long o2 = /* x12_00 */0;
                    if (1 < /* w14 */0) {
                        uint b = (uint)*(byte *)((long)/* x19 */0 + o2);
                        if (b != 0) {
                            FUN_003525b8(0);
                            if (/* w12 */0 != 0) {
                                FUN_003538d4(0);
                                switch (/* w9 */0) { default: case 2: case 3: FUN_0034e32c(0); case 4: break; }
                            }
                            out = FUN_00351538(0);
                            goto done;
                        }
                    }
                }
            } else {
                uint b = (uint)*(byte *)((long)/* x19 */0 + off);
                if (b != 0) {
                    FUN_003525b8(0);
                    if (/* w12 */0 != 0) {
                        FUN_003538d4(0);
                        switch (/* w9 */0) { default: case 2: case 3: FUN_0034e32c(0); case 4: break; }
                    }
                    out = FUN_00351538(0);
                    goto done;
                }
            }
            if (st == 0) { out = 0; goto done; }
        }
        if (v <= limit) {
            cl4_result_t r = FUN_003507e0(0);
            FUN_0007767c(r.lo, r.hi, u5, /* x30 */0);
            FUN_000839f8(0);
            return;
        }
        FUN_003520e8(0);
        FUN_000839f8(0);
        out = FUN_003585dc(0);
    }
done:
    FUN_0007767c(out, /* x30 */0);
}

/* FUN_0032f8e8 @ 0x32f8e8 (est. sk_null_0) */
void sk_null_0(void) { FUN_000026e8(0); }
/* FUN_0032f8ec @ 0x32f8ec (est. sk_null_1) */
void sk_null_1(void) { FUN_000026e8(0); }

/* FUN_0032f900 @ 0x32f900 (est. sk_cap_pair_update)
 * Updates a capability pair: copies words from param_2 to param_1,
 * invokes the setup helper, then calls the dispatch.
 * Confidence: low.
 * Notes: callees FUN_0034b07c. */
long sk_cap_pair_update(long dst, long src)
{
    word_t w = *(word_t *)(src + 0x18);
    *(word_t *)(dst + 0x20) = *(word_t *)(src + 0x20);
    *(word_t *)(dst + 0x18) = w;
    FUN_0034b07c(dst, src, w);
    ((void (*)(void))0)();
    return dst;
}

/* FUN_0032f948 @ 0x32f948 (est. sk_wrapper_f970)
 * Thin wrapper: calls sk_cap_move and returns the argument.
 * Confidence: medium (in-range target). */
word_t sk_wrapper_f970(word_t p1) { sk_cap_move((word_t *)p1, 0); return p1; }

/* sk_cap_move @ 0x32f970 (est. sk_cap_move)
 * Capability move/copy with type-aware dispatch. If both source and
 * destination have the same type (param_1[3]==param_2[3]): if the type
 * is "non-dispatchable" it simply overwrites the word and releases the
 * old value; otherwise it calls the type's copy handler
 * (type+0x18). If the types differ it updates the type fields, then
 * releases the old destination word and calls the appropriate release/
 * copy handlers (type+0x10 / type+0x20 / type+8).
 * Confidence: medium (seL4 cap_move with per-type vtable).
 * Notes: type vtable at *(type-8): +8/+0x10/+0x18/+0x20; dispatch
 *   through 0x32fa7c. */
void sk_cap_move(word_t *dst, word_t *src)
{
    if (dst == src) return;
    long td = dst[3], ts = src[3];
    if (td == ts) {
        if ((*(byte *)(*(long *)(td + -8) + 0x52) >> 1 & 1) == 0) {
            ((void (*)(word_t *, word_t *, long))0)(dst, src, td);
            return;
        }
        word_t old = dst[0], new = src[0];
        FUN_0036b270(new);
        FUN_0036b118(old);
        dst[0] = new;
    } else {
        dst[3] = ts;
        dst[4] = src[4];
        long dt = *(long *)(td + -8);
        long st = *(long *)(ts + -8);
        uint sw = *(uint *)(st + 0x50);
        if ((*(byte *)(dt + 0x52) >> 1 & 1) != 0) {
            word_t old = dst[0];
            if ((sw >> 0x11 & 1) == 0) {
                ((void (*)(word_t *, word_t *, long))0)(dst, src, ts);
            } else {
                dst[0] = src[0];
                FUN_0036b270(0);
            }
            FUN_0036b118(old);
            return;
        }
        ((void (*)(void *, word_t *, long))0)(/* stack */0, dst, td);
        if ((sw >> 0x11 & 1) == 0) {
            ((void (*)(word_t *, word_t *, long))0)(dst, src, ts);
        } else {
            dst[0] = src[0];
            FUN_0036b270(0);
        }
        ((void (*)(void *, long))0)(/* stack */0, td);
    }
}

/* FUN_0032fb38 @ 0x32fb38 (est. sk_common_finalize) */
void sk_common_finalize(void) { FUN_003504d0(0); FUN_000026e8(0); FUN_003597cc(0); FUN_00357d34(0); }

/* FUN_0032fd7c @ 0x32fd7c (est. sk_tcb_validate_3)
 * TCB register-state validation with tag 0x13f; on success commits with
 * error code 3.
 * Confidence: medium.
 * Notes: callees FUN_0034c7c4/377dcc/354ce4/34a32c/377824/34c16c/
 *   3728b8/35884c. */
word_t sk_tcb_validate_3(word_t p1, word_t p2, word_t code)
{
    FUN_0034c7c4(0);
    FUN_00377dcc(0);
    word_t w = FUN_00354ce4(0).lo;
    if (/* carry clear && !zero */1) {
        FUN_0034a32c(w, *(word_t *)/* x19+0x18 */0);
        FUN_00377824(0x13f);
        FUN_00354ce4(0);
        if (/* carry clear && !zero */1) {
            cl4_result_t r = FUN_0034c16c(0);
            code = 3;
            FUN_003728b8(r.lo, r.hi, 3);
            FUN_0035884c(0);
        }
    }
    return code;
}

/* FUN_0032fe14 @ 0x32fe14 (est. sk_syscall_msg_write_d)
 * Message write variant.
 * Confidence: low.
 * Notes: callees FUN_0008e518/350c5c/349734/348d94/377824/000a6f88/
 *   34d5d8/34bfb4/355800/000b43d0/34de74/8e500. */
void sk_syscall_msg_write_d(word_t p1, word_t p2, long frame)
{
    FUN_0008e518(0);
    word_t w = FUN_00350c5c(0);
    long u = *(long *)(frame + 0x10);
    FUN_00349734(w, *(word_t *)(frame + 0x18));
    cl4_result_t r = FUN_00348d94(0);
    FUN_00377824(r.lo, r.hi, u);
    FUN_000a6f88(0);
    long dst = *(long *)/* x8+0x40 */0 + (ulong)(byte)*(uint *)/* table+0x50 */0;
    word_t sz = FUN_0034d5d8(*(uint *)/* table+0x50 */0 & 0xff);
    if ((/* carry clear && !zero */1) && (ulong)/* x11 */0 < 0x19) {
        FUN_0034bfb4(*(word_t *)/* table+0x10 */0);
        ((void (*)(void))0)();
        FUN_00355800(0);
        void *pc = 0;
        cl4_result_t r2 = FUN_000b43d0(0);
        ((void (*)(word_t, word_t, word_t))pc)(r2.lo, r2.hi, sz);
        ((void (*)(word_t, word_t, word_t))pc)(dst + u & ~/* x8_00 */0, dst + /* x20 */0 & ~/* x8_00 */0, sz);
    } else {
        FUN_0034de74(0);
    }
    FUN_0008e500(0);
}

/* FUN_0032ff34 @ 0x32ff34 (est. sk_syscall_msg_read_c)
 * Message read variant with two-stage dispatch.
 * Confidence: low (indirect jump).
 * Notes: callees FUN_003504d0/34b3c8/348d94/377824/34ab20. */
void sk_syscall_msg_read_c(void)
{
    FUN_003504d0(0);
    word_t u4 = *(word_t *)/* x1+0x10 */0;
    word_t w = FUN_0034b3c8(0);
    w = ((word_t (*)(word_t, word_t))0)(w, u4);
    long dst = *(long *)/* table+0x40 */0;
    cl4_result_t r = FUN_00348d94(w, *(word_t *)/* x19+0x18 */0);
    w = FUN_00377824(r.lo, r.hi, u4).lo;
    FUN_0034ab20(0);
    void *jt = 0;
    ulong sel = (ulong)*(byte *)/* table2+0x50 */0;
    ulong addr = dst + /* x20 */0 + sel & ~sel;
    ((void (*)(word_t, word_t, void *, void *))jt)(addr, w, jt, /* table2+8 */0);
    ((void (*)(word_t, word_t))jt)(*(long *)/* table2+0x40 */0 + sel + addr & ~sel, w);
}

/* FUN_003300c0 @ 0x3300c0 (est. sk_dispatch_slot_18_3) table+0x18 */
void sk_dispatch_slot_18_3(void)
{
    FUN_00084220(0);
    FUN_00348c64(0);
    word_t w = ((word_t (*)(void))0)();
    long dst = *(long *)/* table+0x40 */0;
    FUN_00348d94(w, *(word_t *)/* x19+0x18 */0);
    w = FUN_00377824(0).lo;
    FUN_0034ab20(0);
    void *pc = 0;
    ulong sel = (ulong)*(byte *)/* table2+0x50 */0;
    long addr = dst + sel;
    ((void (*)(word_t, word_t, word_t))pc)(addr + /* x21 */0 & ~sel, addr + /* x20 */0 & ~sel, w);
    FUN_0034e850(*(word_t *)/* table2+0x40 */0);
    ((void (*)(void))pc)();
    FUN_00084234(0);
}

/* FUN_0033017c @ 0x33017c (est. sk_dispatch_slot_20_3) table+0x20 */
void sk_dispatch_slot_20_3(void)
{
    FUN_00084220(0);
    FUN_00348c64(0);
    word_t w = ((word_t (*)(void))0)();
    long dst = *(long *)/* table+0x40 */0;
    FUN_00348d94(w, *(word_t *)/* x19+0x18 */0);
    w = FUN_00377824(0).lo;
    FUN_0034ab20(0);
    void *pc = 0;
    ulong sel = (ulong)*(byte *)/* table2+0x50 */0;
    long addr = dst + sel;
    ((void (*)(word_t, word_t, word_t))pc)(addr + /* x21 */0 & ~sel, addr + /* x20 */0 & ~sel, w);
    FUN_0034e850(*(word_t *)/* table2+0x40 */0);
    ((void (*)(void))pc)();
    FUN_00084234(0);
}

/* FUN_00330238 @ 0x330238 (est. sk_dispatch_slot_28_3) table+0x28 */
void sk_dispatch_slot_28_3(void)
{
    FUN_00084220(0);
    FUN_00348c64(0);
    word_t w = ((word_t (*)(void))0)();
    long dst = *(long *)/* table+0x40 */0;
    FUN_00348d94(w, *(word_t *)/* x19+0x18 */0);
    w = FUN_00377824(0).lo;
    FUN_0034ab20(0);
    void *pc = 0;
    ulong sel = (ulong)*(byte *)/* table2+0x50 */0;
    long addr = dst + sel;
    ((void (*)(word_t, word_t, word_t))pc)(addr + /* x21 */0 & ~sel, addr + /* x20 */0 & ~sel, w);
    FUN_0034e850(*(word_t *)/* table2+0x40 */0);
    ((void (*)(void))pc)();
    FUN_00084234(0);
}

/* FUN_003302f4 @ 0x3302f4 (est. sk_msg_cap_validate_1)
 * Message-capability validate returning a capability. Runs setup, then
 * on a valid non-empty slot resolves and returns the capability, else
 * falls to fault/out-of-range handling.
 * Confidence: medium.
 * Notes: callees FUN_00352758/35549c/348d94/377824/34f924/355d34/
 *   358184/357ef4/34e888/3551b0/3580f4/34e32c/351538/3520e8/34bf1c/
 *   839f8. */
word_t sk_msg_cap_validate_1(word_t p1, word_t p2, long frame)
{
    word_t w = FUN_00352758(0);
    word_t u5 = *(word_t *)(frame + 0x10);
    FUN_0035549c(w, *(word_t *)(frame + 0x18));
    uint limit = *(uint *)/* table+0x54 */0;
    cl4_result_t r = FUN_00348d94(0);
    FUN_00377824(r.lo, r.hi, u5);
    FUN_0034f924(0);
    uint lim2 = *(uint *)/* table2+0x54 */0;
    int le = (limit <= lim2), eq = (lim2 == limit);
    FUN_00355d34(0);
    if (/* w22 */0 == 0) return 0;
    FUN_00358184(0);
    uint v = /* w1 */0;
    if (!le || eq) goto out;
    FUN_00357ef4(0);
    long off = /* x11 */0;
    int st = /* w10 */0;
    v = /* w1_00 */0;
    if (!le || eq) {
        FUN_0034e888(0);
        st = /* w10_00 */0;
        v = /* w1_01 */0;
        if (0xff < /* w13 */0) {
            uint b = ((/* w13 */0 >> 0x10) == 0)
                ? (uint)*(ushort *)((long)/* x19 */0 + /* x11_00 */0)
                : *(uint *)((long)/* x19 */0 + /* x11_00 */0);
            if (b != 0) {
                FUN_003551b0(0);
                if (/* w11 */0 != 0) {
                    FUN_003580f4(0);
                    switch (/* w9 */0) { default: case 2: case 3: FUN_0034e32c(0); case 4: break; }
                }
                return FUN_00351538(0);
            }
        } else {
            long o2 = /* x11_00 */0;
            if (1 < /* w13 */0) {
                uint b = (uint)*(byte *)((long)/* x19 */0 + o2);
                if (b != 0) {
                    FUN_003551b0(0);
                    if (/* w11 */0 != 0) {
                        FUN_003580f4(0);
                        switch (/* w9 */0) { default: case 2: case 3: FUN_0034e32c(0); case 4: break; }
                    }
                    return FUN_00351538(0);
                }
            }
        }
    } else {
        uint b = (uint)*(byte *)((long)/* x19 */0 + off);
        if (b != 0) {
            FUN_003551b0(0);
            if (/* w11 */0 != 0) {
                FUN_003580f4(0);
                switch (/* w9 */0) { default: case 2: case 3: FUN_0034e32c(0); case 4: break; }
            }
            return FUN_00351538(0);
        }
    }
    if (st == 0) return 0;
out:
    if (limit < v) FUN_003520e8(0);
    else FUN_0034bf1c(0);
    return FUN_000839f8(0);
}

/* FUN_00330698 @ 0x330698 (est. sk_tcb_validate_1)
 * TCB validate; on success commits with error code 1.
 * Confidence: medium. Notes: callees FUN_00370f2c/34c16c/3728b8/19858. */
void sk_tcb_validate_1(long tcb)
{
    FUN_00370f2c(0x13f, *(word_t *)(tcb + 0x10), *(word_t *)(tcb + 0x18));
    if (/* x1 */0 < 0x40) {
        cl4_result_t r = FUN_0034c16c(0);
        FUN_003728b8(r.lo, r.hi, 1);
        FUN_00019858(0);
    }
}

/* FUN_00330704 @ 0x330704 (est. sk_msg_array_copy)
 * Copies an array of message words (count from param_3+0x10, element
 * stride from table+0x48) via the per-element copy handler
 * (table+0x10), bounds-checked (count*stride < 0x19). On overflow runs
 * the fault handler.
 * Confidence: medium.
 * Notes: callees FUN_00084220/350c5c/349734/34de74/84234. */
void sk_msg_array_copy(word_t p1, word_t p2, long frame)
{
    FUN_00084220(0);
    FUN_00350c5c(0);
    word_t w = *(word_t *)(frame + 0x18);
    FUN_00349734(0);
    long stride = *(long *)/* x8+0x48 */0;
    ulong cnt = *(ulong *)(frame + 0x10);
    ulong n = cnt & (~(ulong)((long)cnt >> 0x3f) ^ 0xffffffffffffffffU);
    if (((*(uint *)/* table+0x50 */0 & 0xff) < 8 &&
         (*(uint *)/* table+0x50 */0 & 0x100000) == 0) && n * (ulong)stride < 0x19) {
        if (0 < (long)cnt) {
            long i = 0;
            void *pc = 0;
            do {
                ((void (*)(word_t, word_t, word_t))pc)(/* x19 */0 + i, /* x20 */0 + i, w);
                i = i + stride;
                n = n - 1;
            } while (n != 0);
        }
    } else {
        FUN_0034de74(0);
    }
    FUN_00084234(0);
}

/* FUN_003307c0 @ 0x3307c0 (est. sk_msg_fill_loop)
 * Loops count (param_2+0x10) times calling the fill helper.
 * Confidence: low. Notes: callees FUN_00349b00/9461c. */
void sk_msg_fill_loop(word_t p1, long frame)
{
    long n = *(long *)(frame + 0x10);
    if (0 < n) {
        FUN_00349b00(0);
        void *pc = 0;
        do {
            FUN_0009461c(0);
            ((void (*)(void))pc)();
            n = n - 1;
        } while (n != 0);
    }
}

/* FUN_00330844 @ 0x330844 (est. sk_dispatch_loop_10) table+0x10, loop */
void sk_dispatch_loop_10(void)
{
    FUN_00084220(0);
    FUN_00355928(0);
    if (/* NG==OV */1) {
        FUN_00349734(0);
        void *pc = 0;
        do {
            FUN_00350e74(0);
            ((void (*)(void))pc)();
            FUN_003525a4(0);
        } while (/* !zero */1);
    }
    FUN_00084234(0);
}

/* FUN_003308c4 @ 0x3308c4 (est. sk_dispatch_loop_18) table+0x18, loop */
void sk_dispatch_loop_18(void)
{
    FUN_00084220(0);
    FUN_00355928(0);
    if (1) {
        FUN_00349734(0);
        void *pc = 0;
        do {
            FUN_00350e74(0);
            ((void (*)(void))pc)();
            FUN_003525a4(0);
        } while (1);
    }
    FUN_00084234(0);
}

/* FUN_00330944 @ 0x330944 (est. sk_dispatch_loop_20) table+0x20, loop */
void sk_dispatch_loop_20(void)
{
    FUN_00084220(0);
    FUN_00355928(0);
    if (1) {
        FUN_00349734(0);
        void *pc = 0;
        do {
            FUN_00350e74(0);
            ((void (*)(void))pc)();
            FUN_003525a4(0);
        } while (1);
    }
    FUN_00084234(0);
}

/* FUN_003309c4 @ 0x3309c4 (est. sk_dispatch_loop_28) table+0x28, loop */
void sk_dispatch_loop_28(void)
{
    FUN_00084220(0);
    FUN_00355928(0);
    if (1) {
        FUN_00349734(0);
        void *pc = 0;
        do {
            FUN_00350e74(0);
            ((void (*)(void))pc)();
            FUN_003525a4(0);
        } while (1);
    }
    FUN_00084234(0);
}

/* FUN_00330ab4 @ 0x330ab4 (est. sk_entry_commit_store)
 * Entry commit with a store to the frame.
 * Confidence: low. Notes: callees FUN_00349d3c/35510c/34c144/34df14/
 *   349cd0/349a9c/36b270. */
void sk_entry_commit_store(void)
{
    FUN_00349d3c(0);
    FUN_0035510c(/* x16 */0);
    FUN_0034c144(0);
    if (/* zero && x10<0x19 */1) {
        FUN_0034df14(0);
        ((void (*)(void))0)();
        FUN_00349cd0(0);
        /* register copy (extraout_x8 = extraout_x9_00) */
    } else {
        FUN_00349a9c(0);
    }
    FUN_0036b270(0);
}

/* FUN_00330b44 @ 0x330b44 (est. sk_slot_setup_release) */
void sk_slot_setup_release(word_t p1, long frame)
{
    FUN_0034ece8(p1, *(word_t *)(frame + 0x10));
    ((void (*)(void))0)();
    FUN_0034de54(*(word_t *)/* table+0x40 */0);
    FUN_0036b118(0);
}

/* FUN_00330b98 @ 0x330b98 (est. sk_slot_dispatch_10) table+0x10 */
void sk_slot_dispatch_10(void)
{
    FUN_00349928(0);
    ((void (*)(void))0)();
    FUN_00349104(*(word_t *)/* table+0x40 */0);
    /* register copy (extraout_x9 = extraout_x8) */
    FUN_0036b270(0);
}

/* FUN_00330bf4 @ 0x330bf4 (est. sk_slot_dispatch_18) table+0x18 */
void sk_slot_dispatch_18(void)
{
    FUN_00349928(0);
    ((void (*)(void))0)();
    FUN_00349104(*(word_t *)/* table+0x40 */0);
    word_t old = 0;
    /* register copy (extraout_x9 = extraout_x8) */
    FUN_0036b270(0);
    FUN_0036b118(old);
}

/* FUN_00330c60 @ 0x330c60 (est. sk_slot_dispatch_28) table+0x28 */
void sk_slot_dispatch_28(void)
{
    FUN_00349928(0);
    ((void (*)(void))0)();
    FUN_00349104(*(word_t *)/* table+0x40 */0);
    word_t old = 0;
    /* register copy (extraout_x9 = extraout_x8) */
    FUN_0036b118(old);
}

/* FUN_00330df4 @ 0x330df4 (est. sk_slot_write_value)
 * Writes a small integer value into the frame slot at the computed
 * offset (width 1/2/4 selected by the resolved size). Zero-fills the
 * slot for the no-value case, then updates the count/size bookkeeping.
 * Confidence: medium.
 * Notes: callees FUN_0034d668/357d94/356e74/9461c/114330/839d8/34fe0;
 *   SoftwareBreakpoint on 3-byte width. */
void sk_slot_write_value(void)
{
    FUN_0034d668(0);
    uint limit = *(uint *)/* table+0x54 */0;
    FUN_00357d94(0);
    long off = (*(long *)/* x9+0x40 */0 + 7U & 0xfffffffffffffff8) + 8;
    FUN_00356e74(0);
    uint width = (/* w11 */0 < 0x100) ? /* w12 */0 : 1;
    uint sel = (1 < /* w11 */0) ? width : 0;
    width = 0;
    if (/* w10 */0 < /* w8 */0) width = sel;
    int diff = /* w1 */0 - /* w10 */0;
    if (/* w10 */0 <= /* w1 */0 && diff != 0) {
        if ((int)off != 0) {
            diff = 1;
            FUN_0009461c(0);
            FUN_00114330(0);
            /* reg store: *x19 = w1 + ~w10 */
        }
        switch (width) {
        default: return;
        case 1: *(char *)((long)/* x19 */0 + off) = (char)diff; return;
        case 2: *(short *)((long)/* x19 */0 + off) = (short)diff; return;
        case 3: SK_BREAKPOINT();   /* SoftwareBreakpoint(1,0x330f6c) */
        case 4: *(int *)((long)/* x19 */0 + off) = diff; return;
        }
    }
    switch (width) {
    case 1:
        *(uint1_t *)((long)/* x19 */0 + off) = 0;
        if (/* w1 */0 == 0) return;
        break;
    case 2:
        *(uint2_t *)((long)/* x19 */0 + off) = 0;
        break;
    case 3: SK_BREAKPOINT();   /* SoftwareBreakpoint(1,0x330f6c) */
    case 4:
        *(uint4_t *)((long)/* x19 */0 + off) = 0;
    default:
        if (/* w1 */0 != 0) {
            int big = 0xfff < limit, eq = (limit == 0x1000);
            if (big) { FUN_000839d8(0); return; }
            FUN_00354fe0(0);
            int inc = (big && !eq) ? -0x1001 : -1;
            /* reg store: *x8 = w1_00 + inc */
        }
    }
}

/* FUN_00331084 @ 0x331084 (est. sk_msg_write_commit)
 * Message write/commit path. Runs setup, writes the message, and on
 * success commits the result pair into the frame (32-byte copy),
 * else runs the fault/error path.
 * Confidence: medium.
 * Notes: callees FUN_0008e518/350c5c/353b7c/34c920/377824/348e00/
 *   356bd4/34e5bc/377824/350488/377824/000a6f88/353844/34bfb4/
 *   355800/351d24/839f8/000b43d0/34e094/839d8/117cc4/355d60/353844/
 *   36b270/358bb4/8e500. */
void sk_msg_write_commit(void)
{
    FUN_0008e518(0);
    FUN_00350c5c(0);
    FUN_00353b7c(0);
    FUN_0034c920(0);
    FUN_00377824(0);
    FUN_00348e00(0);
    FUN_00356bd4(0);
    FUN_0034e5bc(0);
    cl4_result_t r = FUN_00377824(0);
    FUN_00350488(r.lo, r.hi, r.lo);
    FUN_00377824(0);
    FUN_000a6f88(0);
    long dst = *(long *)/* x8+0x40 */0;
    if (*(int *)/* table+0x54 */0 == 0) dst = dst + 1;
    word_t sz = FUN_00353844(*(uint *)/* table+0x50 */0 & 0xff);
    uint szb = /* w8 */0 | *(uint *)/* table+0x50 */0 & 0xf8;
    if ((szb < 8 && ((*(uint *)/* table+0x50 */0 | /* extraout_w10 */0) & 0x100000) == 0) &&
        (/* x9 */0 + 0xfU & 0xfffffffffffffff8) + 0x11 < 0x19) {
        FUN_0034bfb4(*(word_t *)/* table+0x10 */0);
        ((void (*)(void))0)();
        FUN_00355800(0);
        cl4_result_t rr = FUN_00351d24(0);
        if (FUN_000839f8(rr.lo, rr.hi, sz) == 0) {
            cl4_result_t r2 = FUN_000b43d0(*(word_t *)/* table+0x10 */0);
            ((void (*)(word_t, word_t, word_t))0)(r2.lo, r2.hi, sz);
            FUN_0034e094(0);
            FUN_000839d8(0);
        } else {
            cl4_result_t r2 = FUN_000b43d0(0);
            FUN_00117cc4(r2.lo, r2.hi, dst);
        }
        FUN_00355d60(/* x21 */0 + dst);
        FUN_00353844(0);
        word_t *dst2 = 0, *src = 0;
        /* copy 32-byte message header */
        *dst2 = *src;
        word_t *pd = (word_t *)((long)dst2 + 0xfU & 0xfffffffffffffff8);
        word_t *ps = (word_t *)((long)src + 0xfU & 0xfffffffffffffff8);
        long w = *ps;
        *pd = w;
        pd[1] = ps[1];
        *(char *)(pd + 2) = (char)ps[2];
        FUN_0036b270(0);
    } else {
        long w = 0;
        /* reg copy: *x19 = *x20 */
        FUN_00358bb4(szb | 7);
    }
    FUN_0036b270(0);
    FUN_0008e500(/* x19 */0);
}

/* FUN_00331250 @ 0x331250 (est. sk_msg_read_commit)
 * Message read/commit path.
 * Confidence: low.
 * Notes: callees FUN_00350c5c/34e7e0/34c444/377824/841a0/34c444/
 *   377824/350798/377824/350fbc/351330/839f8/353c0c/9461c/357d74/
 *   36b118. */
void sk_msg_read_commit(void)
{
    FUN_00350c5c(0);
    FUN_0034e7e0(0);
    FUN_0034c444(0);
    FUN_00377824(0);
    FUN_000841a0(0);
    ((void (*)(void))0)();
    long dst = *(long *)/* table+0x40 */0;
    word_t extra = *(word_t *)/* x20+0x20 */0;
    FUN_0034c444(0xff);
    cl4_result_t r = FUN_00377824(0);
    FUN_00350798(r.lo, r.hi, r.lo);
    FUN_00377824(0);
    FUN_00350fbc(0);
    byte sel = *(byte *)/* table+0x50 */0;
    cl4_result_t rr = FUN_00351330(0);
    if (FUN_000839f8(rr.lo, rr.hi, extra) == 0) {
        FUN_00353c0c(0);
        FUN_0009461c(0);
        ((void (*)(void))0)();
    }
    FUN_00357d74(0);
    long addr = (dst + /* x19 */0 + (ulong)sel & ~(ulong)sel) + /* extraout_x9_00 */0;
    if (/* zero */1) addr = addr + 1;
    word_t *p = (word_t *)(addr + 7U & 0xfffffffffffffff8);
    FUN_0036b118(*p);
    FUN_0036b118(p[1]);
}

/* FUN_00331348 @ 0x331348 (est. sk_syscall_cap_copy2_10) table+0x10 */
void sk_syscall_cap_copy2_10(void)
{
    FUN_00084220(0);
    FUN_0034a914(0);
    FUN_00349530(0);
    ((void (*)(void))0)();
    word_t extra = *(word_t *)/* x21+0x20 */0;
    FUN_00355780(0);
    FUN_0034be0c(0);
    cl4_result_t r = FUN_00377824(0);
    FUN_0034e6dc(r.lo, r.hi, r.lo);
    FUN_00377824(0);
    FUN_0035295c(0);
    FUN_00354fd0(*(und1_t *)/* table+0x50 */0);
    ulong addr = /* x9 */0 & ~/* x8 */0;
    FUN_003518dc(addr);
    word_t rr = FUN_000839f8(0);
    int st;
    long dst;
    if (rr == 0) {
        FUN_00350ed0(*(word_t *)/* table+0x10 */0, extra);
        ((void (*)(void))0)();
        FUN_0034e094(0);
        FUN_000839d8(0);
        st = *(int *)/* table+0x54 */0;
        dst = *(long *)/* table+0x40 */0;
    } else {
        st = *(int *)/* table+0x54 */0;
        dst = *(long *)/* table+0x40 */0;
        long d2 = (st == 0) ? dst + 1 : dst;
        FUN_000b43d0(rr, 0, d2);
        FUN_00117cc4(0);
    }
    if (st == 0) dst = dst + 1;
    FUN_00353844(dst);
    FUN_00355d60(addr + /* x8_01 */0);
    word_t *d = 0, *s = 0;
    word_t *pd = (word_t *)((long)d + 0xfU & 0xfffffffffffffff8);
    word_t *ps = (word_t *)((long)s + 0xfU & 0xfffffffffffffff8);
    word_t w = *ps;
    *pd = w;
    pd[1] = ps[1];
    FUN_003594d4(0);
    FUN_0036b270(0);
    FUN_0036b270(w);
    FUN_00084234(0);
}

/* FUN_00331488 @ 0x331488 (est. sk_syscall_cap_copy3_18) table+0x18 */
void sk_syscall_cap_copy3_18(word_t p1, word_t p2, long frame)
{
    FUN_00084220(0);
    FUN_00352758(0);
    word_t u4 = *(word_t *)(frame + 0x18);
    word_t w = FUN_0034c1e4(0);
    FUN_00350bfc(w, u4);
    FUN_00377824(0);
    FUN_00349530(0);
    ((void (*)(void))0)();
    FUN_003519fc(0);
    FUN_00350bfc(0);
    cl4_result_t r = FUN_00377824(0);
    FUN_00350798(r.lo, r.hi, r.lo);
    FUN_00377824(0);
    FUN_0035295c(0);
    FUN_00354fd0(*(und1_t *)/* table+0x50 */0);
    FUN_003518dc(u4);
    int i1 = FUN_000839f8(0);
    FUN_00350198(0);
    word_t rr = FUN_000839f8(0);
    int st; long dst;
    if (i1 == 0) {
        if (rr == 0) {
            FUN_0034d3d4(0);
            ((void (*)(void))0)();
            goto tail;
        }
        FUN_0008e388(*(word_t *)/* table+8 */0);
        rr = ((word_t (*)(void))0)();
        st = *(int *)/* table+0x54 */0;
        dst = *(long *)/* table+0x40 */0;
    } else {
        if (rr == 0) {
            FUN_00353a00(0);
            FUN_0034d3d4(0);
            ((void (*)(void))0)();
            FUN_0034e094(0);
            FUN_000839d8(0);
            goto tail;
        }
        st = *(int *)/* table+0x54 */0;
        dst = *(long *)/* table+0x40 */0;
    }
    if (st == 0) dst = dst + 1;
    FUN_000b4390(rr, 0, dst);
    FUN_00117cc4(0);
tail:
    FUN_00357028(0);
    word_t *pd = (word_t *)(/* x9_02 */0 & 0xfffffffffffffff8);
    word_t *ps = (word_t *)((/* x9 */0 + /* x22 */0 & ~/* x8 */0) + /* x8_01 */0 + 7 & 0xfffffffffffffff8);
    word_t w0 = *pd;
    *pd = *ps;
    FUN_0036b270(0);
    FUN_0036b118(w0);
    w0 = pd[1];
    pd[1] = ps[1];
    FUN_0036b270(0);
    FUN_0036b118(w0);
    pd[2] = ps[2];
    *(und1_t *)(pd + 3) = *(und1_t *)(ps + 3);
    FUN_00084234(0);
}

/* FUN_00331644 @ 0x331644 (est. sk_syscall_cap_copy2_20) table+0x20 */
void sk_syscall_cap_copy2_20(void)
{
    FUN_00084220(0);
    FUN_0034a914(0);
    FUN_00349530(0);
    ((void (*)(void))0)();
    word_t extra = *(word_t *)/* x21+0x20 */0;
    FUN_00355780(0);
    FUN_0034be0c(0);
    cl4_result_t r = FUN_00377824(0);
    FUN_0034e6dc(r.lo, r.hi, r.lo);
    FUN_00377824(0);
    FUN_0035295c(0);
    FUN_00354fd0(*(und1_t *)/* table+0x50 */0);
    ulong addr = /* x9 */0 & ~/* x8 */0;
    FUN_003518dc(addr);
    word_t rr = FUN_000839f8(0);
    int st; long dst;
    if (rr == 0) {
        FUN_00350ed0(*(word_t *)/* table+0x20 */0, extra);
        ((void (*)(void))0)();
        FUN_0034e094(0);
        FUN_000839d8(0);
        st = *(int *)/* table+0x54 */0;
        dst = *(long *)/* table+0x40 */0;
    } else {
        st = *(int *)/* table+0x54 */0;
        dst = *(long *)/* table+0x40 */0;
        long d2 = (st == 0) ? dst + 1 : dst;
        FUN_000b43d0(rr, 0, d2);
        FUN_00117cc4(0);
    }
    if (st == 0) dst = dst + 1;
    FUN_00353844(dst);
    FUN_00355d60(addr + /* x8_01 */0);
    word_t *d = 0, *s = 0;
    FUN_00352dac((long)s + 0xfU & 0xfffffffffffffff8);
    FUN_003594d4(0);
    FUN_00084234(0);
}

/* FUN_0033176c @ 0x33176c (est. sk_syscall_cap_copy3_28) table+0x28 */
void sk_syscall_cap_copy3_28(word_t p1, word_t p2, long frame)
{
    FUN_00084220(0);
    FUN_00352758(0);
    word_t u3 = *(word_t *)(frame + 0x18);
    word_t w = FUN_0034c1e4(0);
    FUN_00350bfc(w, u3);
    FUN_00377824(0);
    FUN_00349530(0);
    ((void (*)(void))0)();
    FUN_003519fc(0);
    FUN_00350bfc(0);
    cl4_result_t r = FUN_00377824(0);
    FUN_00350798(r.lo, r.hi, r.lo);
    FUN_00377824(0);
    FUN_0035295c(0);
    FUN_00354fd0(*(und1_t *)/* table+0x50 */0);
    FUN_003518dc(u3);
    int i1 = FUN_000839f8(0);
    FUN_00350198(0);
    word_t rr = FUN_000839f8(0);
    int st; long dst;
    if (i1 == 0) {
        if (rr == 0) {
            FUN_0034d3d4(0);
            ((void (*)(void))0)();
            goto tail;
        }
        FUN_0008e388(*(word_t *)/* table+8 */0);
        rr = ((word_t (*)(void))0)();
        st = *(int *)/* table+0x54 */0;
        dst = *(long *)/* table+0x40 */0;
    } else {
        if (rr == 0) {
            FUN_0034d3d4(0);
            ((void (*)(void))0)();
            FUN_0034e094(0);
            FUN_000839d8(0);
            goto tail;
        }
        st = *(int *)/* table+0x54 */0;
        dst = *(long *)/* table+0x40 */0;
    }
    if (st == 0) dst = dst + 1;
    FUN_000b4390(rr, 0, dst);
    FUN_00117cc4(0);
tail:
    FUN_00357028(0);
    word_t *pd = (word_t *)(/* x9_02 */0 & 0xfffffffffffffff8);
    word_t *ps = (word_t *)((/* x9 */0 + /* x22 */0 & ~/* x8 */0) + /* x8_01 */0 + 7 & 0xfffffffffffffff8);
    word_t w0 = *pd;
    *pd = *ps;
    FUN_0036b118(w0);
    w0 = pd[1];
    pd[1] = ps[1];
    FUN_0036b118(w0);
    pd[2] = ps[2];
    *(und1_t *)(pd + 3) = *(und1_t *)(ps + 3);
    FUN_00084234(0);
}

/* FUN_0033191c @ 0x33191c (est. sk_msg_slot_read)
 * Reads a message slot value with size selection (1/2/4) and computes
 * the result count. Runs the prelude and slot resolution; on a valid
 * non-empty slot returns the resolved count, else falls to the
 * fault/out-of-range path.
 * Confidence: medium.
 * Notes: callees FUN_0008e518/352758/353b7c/34c920/377824/352820/
 *   356bd4/34e5bc/377824/350500/377824/34cb60/351538/34bf1c/3584d8/
 *   839f8/8e500. */
void sk_msg_slot_read(void)
{
    FUN_0008e518(0);
    FUN_00352758(0);
    FUN_00353b7c(0);
    FUN_0034c920(0);
    FUN_00377824(0);
    FUN_00352820(0);
    uint lim1 = *(uint *)/* table+0x54 */0;
    FUN_00356bd4(0);
    FUN_0034e5bc(0);
    cl4_result_t r = FUN_00377824(0);
    FUN_00350500(r.lo, r.hi, r.lo);
    FUN_00377824(0);
    cl4_result_t cw = FUN_0034cb60(0);
    uint lim2 = *(uint *)/* table+0x54 */0;
    uint a = (lim2 != 0) ? lim2 - 1 : 0;
    uint top = (a <= lim1) ? lim1 : a;
    if (top < 0x1001) top = 0x1000;
    ulong sel = (ulong)*(byte *)/* table+0x50 */0;
    long dst = *(long *)/* x8+0x40 */0;
    if (lim2 == 0) dst = dst + 1;
    ulong res = 0;
    if (/* w22 */0 != 0) {
        ulong base = *(long *)/* x27+0x40 */0 + sel;
        if (top <= /* w22 */0 && /* w22 */0 - top != 0) {
            long off = (dst + 7 + (base & ~sel) & 0xfffffffffffffff8) + 0x19;
            uint p = (uint)off;
            uint size = 2;
            uint sv = (p < 4) ? ((/* w22 */0 - top) + 0xff >> 8) + 1 : size;
            if (0xffff < sv) size = 4;
            if (sv < 0x100) size = 1;
            uint v = 0;
            if (1 < sv) v = size;
            switch (v) {
            case 1:
                if (*(byte *)((long)/* x19 */0 + off) != 0) {
                    int sh = (p & 3) << 3;
                    int bit = (p < 4) ? (int)*(byte *)((long)/* x19 */0 + off) - 1 << sh : 0;
                    res = FUN_00351538(bit, cw.lo, lim2, cw.lo);
                    goto done;
                }
                break;
            case 2:
                if (*(ushort *)((long)/* x19 */0 + off) != 0) {
                    int sh = (p & 3) << 3;
                    int bit = (p < 4) ? (int)*(ushort *)((long)/* x19 */0 + off) - 1 << sh : 0;
                    res = FUN_00351538(bit, cw.lo, lim2, cw.lo);
                    goto done;
                }
                break;
            case 3: SK_BREAKPOINT();   /* SoftwareBreakpoint(1,0x331b30) */
            case 4:
                if (*(uint *)((long)/* x19 */0 + off) != 0) {
                    int sh = (p & 3) << 3;
                    int bit = (p < 4) ? (int)*(uint *)((long)/* x19 */0 + off) - 1 << sh : 0;
                    res = FUN_00351538(bit, cw.lo, lim2, cw.lo);
                    goto done;
                }
            }
        }
        if (lim1 == top) {
            FUN_0034bf1c(0);
            FUN_0008e500(0);
            FUN_000839f8(0);
            return;
        }
        if (a != top) {
            res = FUN_003584d8(dst + 7 + (base + /* x19 */0 & ~sel));
            goto done;
        }
        if (1 < lim2) {
            int x = FUN_000839f8(0);
            uint n = (x != 0) ? (uint)x - 1 : 0;
            res = (ulong)n;
            goto done;
        }
    }
done:
    FUN_0008e500(res, /* x30 */0);
}

/* FUN_00331e20..0x331ee0: scheduler/resume wrapper family.
 * Each calls a resume/commit helper then the common completion helpers. */
/* FUN_00331e20 @ 0x331e20 (est. sk_resume_common_0) */
void sk_resume_common_0(void) { FUN_00353498(0); FUN_00374104(0); FUN_003546b4(0); }
/* FUN_00331e50 @ 0x331e50 (est. sk_resume_common_1) */
void sk_resume_common_1(void) { FUN_00353498(0); FUN_00374104(0); FUN_003546b4(0); }
/* FUN_00331e80 @ 0x331e80 (est. sk_resume_common_2) */
void sk_resume_common_2(void) { FUN_00353498(0); FUN_00374104(0); FUN_003546b4(0); }
/* FUN_00331eb0 @ 0x331eb0 (est. sk_resume_common_3) */
void sk_resume_common_3(void) { FUN_00353498(0); FUN_00374104(0); FUN_003546b4(0); }
/* FUN_00331ee0 @ 0x331ee0 (est. sk_resume_common_4) */
void sk_resume_common_4(void) { FUN_00352b38(0); FUN_00374104(0); FUN_003546b4(0); }
/* FUN_00331f28 @ 0x331f28 (est. sk_resume_common_5) */
void sk_resume_common_5(void) { FUN_00021480(0); }
/* FUN_00331fdc @ 0x331fdc (est. sk_resume_common_7) */
void sk_resume_common_7(void) { FUN_00021480(0); }

/* FUN_00331f40 @ 0x331f40 (est. sk_tcb_finalize_a)
 * Finalizes a TCB: validates the register cap at +0x40, then commits
 * with error code 6.
 * Confidence: medium. Notes: callees FUN_00355150/377dcc/351244/
 *   374104/354c58. */
void sk_tcb_finalize_a(void)
{
    long tcb = FUN_00355150(0);
    FUN_00377dcc(0x13f, *(word_t *)(tcb + 0x40));
    if (/* x1 */0 < 0x40) {
        cl4_result_t r = FUN_00351244(0);
        FUN_00374104(r.lo, r.hi, 6);
        FUN_00354c58(0);
    }
}

/* FUN_00331ff4 @ 0x331ff4 (est. sk_tcb_finalize_b)
 * Finalizes a TCB: validates caps at +0x38 then +0x40, commits code 6.
 * Confidence: medium. Notes: callees FUN_00377dcc/355150/351244/
 *   374104/354c58. */
void sk_tcb_finalize_b(long tcb)
{
    FUN_00377dcc(0x13f, *(word_t *)(tcb + 0x38));
    if (/* x1 */0 < 0x40) {
        FUN_00355150(0);
        FUN_00377dcc(0x13f, *(word_t *)(tcb + 0x40));
        if (/* x1_00 */0 < 0x40) {
            cl4_result_t r = FUN_00351244(0);
            FUN_00374104(r.lo, r.hi, 6);
            FUN_00354c58(0);
        }
    }
}

/* FUN_003320b8 @ 0x3320b8 (est. sk_tcb_release_regs_c) */
void sk_tcb_release_regs_c(long tcb)
{
    cl4_result_t r = FUN_00377dcc(0x13f, *(word_t *)(tcb + 0x38));
    if (r.hi < 0x40) {
        FUN_00353424(*(long *)(r.lo + -8) + 0x40);
        FUN_0034d034(0);
        FUN_00374104(0);
        FUN_00354c58(0);
    }
}

/* FUN_003320f8 @ 0x3320f8 (est. sk_tcb_release_regs_d) offset +0x38 */
void sk_tcb_release_regs_d(long tcb)
{
    cl4_result_t r = FUN_00377dcc(0x13f, *(word_t *)(tcb + 0x38));
    if (r.hi < 0x40) {
        FUN_00353424(*(long *)(r.lo + -8) + 0x40);
        FUN_0034d034(0);
        FUN_00374104(0);
        FUN_00354c58(0);
    }
}

/* FUN_00332168 @ 0x332168 (est. sk_resume_common_6) */
void sk_resume_common_6(void) { FUN_00021480(0); }

/* FUN_00332190 @ 0x332190 (est. sk_cap_validate_commit)
 * Validates a capability (tag 0x13f); on success commits.
 * Confidence: medium. Notes: callees FUN_0034c7c4/377dcc/34d1c0/
 *   3728b8/19858. */
void sk_cap_validate_commit(void)
{
    FUN_0034c7c4(0);
    FUN_00377dcc(0);
    if (/* x1 */0 < 0x40) {
        FUN_0034d1c0(0);
        FUN_003728b8(0);
        FUN_00019858(0);
    }
}

/* FUN_0033221c @ 0x33221c (est. sk_slot_validate_commit)
 * Validates a slot cap; on success commits.
 * Confidence: medium. Notes: callees FUN_0035aa54/357d44/34d1c0/
 *   3728b8/19858. */
void sk_slot_validate_commit(long slot)
{
    cl4_result_t r = FUN_0035aa54(slot, *(word_t *)(slot + 0x20), *(word_t *)(slot + 0x10));
    if (r.hi < 0x40) {
        FUN_00357d44(*(long *)(r.lo + -8) + 0x40);
        FUN_0034d1c0(0);
        FUN_003728b8(0);
        FUN_00019858(0);
    }
}

/* FUN_00332290 @ 0x332290 (est. sk_entry_dispatch_commit)
 * Entry dispatch commit variant.
 * Confidence: low. Notes: callees FUN_0034fc7c/349830/377824/34b57c/
 *   35510c/34c144/34df14/349cd0/3535e4/349a9c/36b270. */
void sk_entry_dispatch_commit(void)
{
    FUN_0034fc7c(0);
    FUN_00349830(0);
    FUN_00377824(0);
    FUN_0034b57c(0);
    FUN_0035510c(/* x16 */0);
    cl4_result_t r = FUN_0034c144(0);
    if (/* zero && x10<0x19 */1) {
        FUN_0034df14(r.lo, r.hi, r.lo);
        ((void (*)(void))0)();
        FUN_00349cd0(0);
        FUN_003535e4(0);
    } else {
        FUN_00349a9c(0);
    }
    FUN_0036b270(0);
}

/* FUN_00332328 @ 0x332328 (est. sk_slot_setup_dispatch) */
void sk_slot_setup_dispatch(word_t p1, long frame)
{
    word_t w = FUN_00349830(*(word_t *)(frame + 0x20), p1, frame, *(word_t *)(frame + 0x10));
    FUN_00377824(w, /* x8 */0);
    FUN_000841a0(0);
    ((void (*)(word_t))0)(p1);
    FUN_0034de54(*(word_t *)/* table+0x40 */0);
    FUN_0036b118(*(word_t *)/* x8_00+8 */0);
}

/* FUN_0033238c @ 0x33238c (est. sk_dispatch2_10) table+0x10 */
void sk_dispatch2_10(void)
{
    FUN_003504d0(0);
    FUN_00354034(0);
    FUN_00349830(0);
    FUN_00377824(0);
    FUN_00349530(0);
    ((void (*)(void))0)();
    FUN_00349104(*(word_t *)/* table+0x40 */0);
    FUN_0034f22c(0);
    FUN_0036b270(0);
}

/* FUN_003323f8 @ 0x3323f8 (est. sk_dispatch2_18) table+0x18 */
void sk_dispatch2_18(void)
{
    FUN_003504d0(0);
    FUN_00354034(0);
    FUN_00349830(0);
    FUN_00377824(0);
    FUN_00349530(0);
    ((void (*)(void))0)();
    FUN_00349104(*(word_t *)/* table+0x40 */0);
    word_t w = *(word_t *)/* x9+8 */0;
    FUN_0034f22c(0);
    FUN_0036b270(0);
    FUN_0036b118(w);
}

/* FUN_00332470 @ 0x332470 (est. sk_dispatch2_20) table+0x20 */
void sk_dispatch2_20(void)
{
    FUN_003504d0(0);
    FUN_00354034(0);
    FUN_00349830(0);
    FUN_00377824(0);
    FUN_00349530(0);
    ((void (*)(void))0)();
    FUN_00349104(*(word_t *)/* table+0x40 */0);
    FUN_00352dac(0);
}

/* FUN_003324d8 @ 0x3324d8 (est. sk_dispatch2_28) table+0x28 */
void sk_dispatch2_28(void)
{
    FUN_003504d0(0);
    FUN_00354034(0);
    FUN_00349830(0);
    FUN_00377824(0);
    FUN_00349530(0);
    ((void (*)(void))0)();
    FUN_00349104(*(word_t *)/* table+0x40 */0);
    FUN_00352dac(*(word_t *)/* x9+8 */0);
    FUN_0036b118(0);
}

/* FUN_00332548 @ 0x332548 (est. sk_msg_count_cap_b)
 * Message-count capability validate (like 0x32db74 but takes count arg).
 * Confidence: medium.
 * Notes: callees FUN_0034fc7c/349830/377824/34ada0/355008/356638/
 *   356e64/34de54/839f8. */
ulong sk_msg_count_cap_b(word_t p1, uint count)
{
    FUN_0034fc7c(0);
    FUN_00349830(0);
    FUN_00377824(0);
    word_t r = FUN_0034ada0(0);
    cl4_result_t c = FUN_00355008(r, *(uint *)/* table+0x54 */0);
    word_t cnt = c.hi;
    if (count == 0) return 0;
    if (/* w9 */0 < count) {
        FUN_00356638(*(word_t *)/* x8+0x40 */0, c.lo, cnt, c.lo);
        ulong off = /* x10 */0 + 0x10;
        uint size = 2;
        if ((off & 0xfffffff8) == 0) size = /* w12 */0 + 1;
        if (0xffff < size) size = 4;
        if (size < 0x100) size = 1;
        uint sel = (1 < size) ? size : 0;
        cnt = /* x1 */0;
        switch (sel) {
        case 1:
            if (*(byte *)((long)/* x19 */0 + off) != 0) {
                int i = (off & 0xfffffff8) ? 0 : (int)*(byte *)((long)/* x19 */0 + off) - 1;
                return FUN_00356e64(i);
            }
            break;
        case 2:
            if (*(ushort *)((long)/* x19 */0 + off) != 0) {
                int i = (off & 0xfffffff8) ? 0 : (int)*(ushort *)((long)/* x19 */0 + off) - 1;
                return FUN_00356e64(i);
            }
            break;
        case 3: SK_BREAKPOINT();   /* SoftwareBreakpoint(1,0x33266c) */
        case 4:
            if (*(uint *)((long)/* x19 */0 + off) != 0) {
                int i = (off & 0xfffffff8) ? 0 : (int)*(uint *)((long)/* x19 */0 + off) - 1;
                return FUN_00356e64(i);
            }
        }
    }
    if ((uint)cnt < 0x1000) {
        FUN_0034de54(0);
        ulong v = 0;
        if (/* *x8_00 */0 < 0x1000) v = (int)/* *x8_00 */0 + 1;
        return v;
    }
    return FUN_000839f8(0);
}

/* FUN_003328ac @ 0x3328ac (est. sk_cap_validate_commit_b)
 * Validates a cap and commits.
 * Confidence: medium. Notes: callees FUN_0034c7c4/377dcc/351244/
 *   36851c/19858. */
void sk_cap_validate_commit_b(void)
{
    FUN_0034c7c4(0);
    cl4_result_t r = FUN_00377dcc(0);
    if (r.hi < 0x40) {
        long *p = (long *)(r.lo + -8);
        FUN_00351244((word_t)p, r.hi, *p + 0x40);
        FUN_0036851c(0);
        FUN_00019858(0);
    }
}

/* FUN_00332924 @ 0x332924 (est. sk_entry_commit_b)
 * Entry commit variant.
 * Confidence: low. Notes: callees FUN_00349d3c/35510c/34c144/34df14/
 *   349cd0/3535e4/349a9c/36b270. */
void sk_entry_commit_b(void)
{
    FUN_00349d3c(0);
    FUN_0035510c(/* x16 */0);
    FUN_0034c144(0);
    if (/* zero && x10<0x19 */1) {
        FUN_0034df14(0);
        ((void (*)(void))0)();
        FUN_00349cd0(0);
        FUN_003535e4(0);
    } else {
        FUN_00349a9c(0);
    }
    FUN_0036b270(0);
}

/* FUN_003329ac @ 0x3329ac (est. sk_slot_setup_release_b) */
void sk_slot_setup_release_b(word_t p1, long frame)
{
    FUN_0034ece8(p1, *(word_t *)(frame + 0x10));
    ((void (*)(void))0)();
    FUN_0034de54(*(word_t *)/* table+0x40 */0);
    FUN_0036b118(*(word_t *)/* x8+8 */0);
}

/* FUN_003329fc @ 0x3329fc (est. sk_slot3_dispatch_10) table+0x10 */
void sk_slot3_dispatch_10(void)
{
    FUN_00349928(0);
    ((void (*)(void))0)();
    FUN_00349104(*(word_t *)/* table+0x40 */0);
    FUN_0034f22c(0);
    FUN_0036b270(0);
}

/* FUN_00332a50 @ 0x332a50 (est. sk_slot3_dispatch_18) table+0x18 */
void sk_slot3_dispatch_18(void)
{
    FUN_00349928(0);
    ((void (*)(void))0)();
    FUN_00349104(*(word_t *)/* table+0x40 */0);
    word_t w = *(word_t *)/* x9+8 */0;
    FUN_0034f22c(0);
    FUN_0036b270(0);
    FUN_0036b118(w);
}

/* FUN_00332ab0 @ 0x332ab0 (est. sk_slot3_dispatch_20) table+0x20 */
void sk_slot3_dispatch_20(void)
{
    FUN_00349928(0);
    ((void (*)(void))0)();
    FUN_00349104(*(word_t *)/* table+0x40 */0);
    FUN_00352dac(0);
}

/* FUN_00332b00 @ 0x332b00 (est. sk_slot3_dispatch_28) table+0x28 */
void sk_slot3_dispatch_28(void)
{
    FUN_00349928(0);
    ((void (*)(void))0)();
    FUN_00349104(*(word_t *)/* table+0x40 */0);
    FUN_00352dac(*(word_t *)/* x9+8 */0);
    FUN_0036b118(0);
}

/* FUN_00332e2c @ 0x332e2c (est. sk_slot_validate_commit_b) */
void sk_slot_validate_commit_b(long slot)
{
    cl4_result_t r = FUN_0035aa54(slot, *(word_t *)(slot + 0x18), *(word_t *)(slot + 0x10));
    if (r.hi < 0x40) {
        FUN_00357d44(*(long *)(r.lo + -8) + 0x40);
        cl4_result_t r2 = FUN_0034c16c(0);
        FUN_003728b8(r2.lo, r2.hi, 3);
        FUN_00019858(0);
    }
}

/* FUN_00332ea4 @ 0x332ea4 (est. sk_entry_copy_commit)
 * Entry copy/commit: copies one byte via the helper, dispatches.
 * Confidence: low.
 * Notes: callees FUN_0034d724/349830/377824/34b57c/0006b6f4/3535e4/
 *   34e974/36b270. */
void sk_entry_copy_commit(void)
{
    FUN_0034d724(0);
    FUN_00349830(0);
    FUN_00377824(0);
    cl4_result_t r = FUN_0034b57c(0);
    ulong sel = (ulong)*(uint *)/* table+0x50 */0 & 0xff;
    long base = *(long *)/* x9+0x40 */0 + 7;
    if ((sel < 8 && (/*...*/0 & 0x100000) == 0) &&
        (base + (sel + 1 & ~sel) & 0xfffffffffffffff8) + 0x10 < 0x19) {
        /* reg copy: *x19 = *x20 */
        FUN_0006b6f4(r.lo, r.hi, r.lo);
        ((void (*)(void))0)();
        FUN_003535e4(base + ((ulong)(/* x19 */0 + sel + 1) & ~sel) & 0xfffffffffffffff8);
    } else {
        FUN_0034e974(0);
    }
    FUN_0036b270(0);
}

/* FUN_00332f90 @ 0x332f90 (est. sk_slot_read_commit) */
void sk_slot_read_commit(void)
{
    FUN_003561f4(0);
    word_t w = FUN_00349830(0);
    FUN_00377824(w, /* x8 */0);
    FUN_000841a0(0);
    ulong sel = (ulong)*(byte *)/* table+0x50 */0;
    ulong addr = /* x19 */0 + sel + 1 & ~sel;
    ((void (*)(ulong))0)(addr);
    FUN_00355d60(*(long *)/* table+0x40 */0 + addr);
    FUN_0036b118(*(word_t *)/* x8_00+8 */0);
}

/* FUN_00333000 @ 0x333000 (est. sk_slot4_dispatch_10) table+0x10 */
void sk_slot4_dispatch_10(word_t p1, word_t p2, long frame)
{
    word_t w = FUN_0034cdb4(0);
    FUN_00349830(w, *(word_t *)(frame + 0x18), *(word_t *)(frame + 0x10));
    FUN_00377824(0);
    FUN_00349530(0);
    ulong sel = (ulong)*(byte *)/* table+0x50 */0;
    ((void (*)(word_t, word_t))0)
        (sel + 1 + /* x20 */0 & ~sel, sel + 1 + /* x19 */0 & ~sel);
    FUN_0034bb74(*(long *)/* table+0x40 */0 + 7);
    FUN_0034f22c(0);
    FUN_0036b270(0);
}

/* FUN_0033308c @ 0x33308c (est. sk_slot4_dispatch_18) table+0x18 */
void sk_slot4_dispatch_18(word_t p1, word_t p2, long frame)
{
    word_t w = FUN_0034cdb4(0);
    FUN_00349830(w, *(word_t *)(frame + 0x18), *(word_t *)(frame + 0x10));
    FUN_00377824(0);
    FUN_00349530(0);
    ulong sel = (ulong)*(byte *)/* table+0x50 */0;
    ((void (*)(word_t, word_t))0)
        (sel + 1 + /* x20 */0 & ~sel, sel + 1 + /* x19 */0 & ~sel);
    FUN_0034bb74(*(long *)/* table+0x40 */0 + 7);
    word_t w2 = *(word_t *)/* x9+8 */0;
    FUN_0034f22c(0);
    FUN_0036b270(0);
    FUN_0036b118(w2);
}

/* FUN_00333124 @ 0x333124 (est. sk_slot4_dispatch_20) table+0x20 */
void sk_slot4_dispatch_20(word_t p1, word_t p2, long frame)
{
    word_t w = FUN_0034cdb4(0);
    FUN_00349830(w, *(word_t *)(frame + 0x18), *(word_t *)(frame + 0x10));
    FUN_00377824(0);
    FUN_00349530(0);
    ulong sel = (ulong)*(byte *)/* table+0x50 */0;
    ((void (*)(word_t, word_t))0)
        (sel + 1 + /* x20 */0 & ~sel, sel + 1 + /* x19 */0 & ~sel);
    FUN_0034bb74(*(long *)/* table+0x40 */0 + 7);
    FUN_00352dac(0);
}

/* FUN_003331ac @ 0x3331ac (est. sk_slot4_dispatch_28) table+0x28 */
void sk_slot4_dispatch_28(word_t p1, word_t p2, long frame)
{
    word_t w = FUN_0034cdb4(0);
    FUN_00349830(w, *(word_t *)(frame + 0x18), *(word_t *)(frame + 0x10));
    FUN_00377824(0);
    FUN_00349530(0);
    ulong sel = (ulong)*(byte *)/* table+0x50 */0;
    ((void (*)(word_t, word_t))0)
        (sel + 1 + /* x20 */0 & ~sel, sel + 1 + /* x19 */0 & ~sel);
    FUN_0034bb74(*(long *)/* table+0x40 */0 + 7);
    FUN_00352dac(*(word_t *)/* x9+8 */0);
    FUN_0036b118(0);
}

/* FUN_0033323c @ 0x33323c (est. sk_msg_slot_read_b)
 * Message slot read (like 0x33191c but 4-byte slot).
 * Confidence: medium.
 * Notes: callees FUN_0034d724/349830/377824/34f924/356e64/3584d8/
 *   839f8. */
word_t sk_msg_slot_read_b(void)
{
    FUN_0034d724(0);
    FUN_00349830(0);
    FUN_00377824(0);
    word_t w = FUN_0034f924(0).lo;
    uint lim = *(uint *)/* table+0x54 */0;
    uint top = (lim < 0x1001) ? 0x1000 : lim;
    ulong sel = (ulong)*(byte *)/* table+0x50 */0;
    if (/* w20 */0 == 0) return 0;
    long base = *(long *)/* x8+0x40 */0 + 7;
    if (top <= /* w20 */0 - top != 0) {
        ulong off = (base + (sel + 1 & ~sel) & 0xfffffffffffffff8) + 0x10;
        uint size = 2;
        uint sv = ((off & 0xfffffff8) == 0) ? (/* w20 */0 - top) + 1 : size;
        if (0xffff < sv) size = 4;
        if (sv < 0x100) size = 1;
        uint v = (1 < sv) ? size : 0;
        switch (v) {
        case 1:
            if (*(byte *)((long)/* x19 */0 + off) != 0) {
                int i = (off & 0xfffffff8) ? 0 : (int)*(byte *)((long)/* x19 */0 + off) - 1;
                return FUN_00356e64(i, w, lim, w);
            }
            break;
        case 2:
            if (*(ushort *)((long)/* x19 */0 + off) != 0) {
                int i = (off & 0xfffffff8) ? 0 : (int)*(ushort *)((long)/* x19 */0 + off) - 1;
                return FUN_00356e64(i, w, lim, w);
            }
            break;
        case 3: SK_BREAKPOINT();   /* SoftwareBreakpoint(1,0x333384) */
        case 4:
            if (*(uint *)((long)/* x19 */0 + off) != 0) {
                int i = (off & 0xfffffff8) ? 0 : (int)*(uint *)((long)/* x19 */0 + off) - 1;
                return FUN_00356e64(i, w, lim, w);
            }
        }
    }
    if (lim < 0x1000) return FUN_003584d8(base + (/* x19 */0 + sel + 1 & ~sel));
    return FUN_000839f8(0);
}

/* FUN_00333608 @ 0x333608 (est. sk_msg_peek) */
void sk_msg_peek(void)
{
    FUN_003561f4(0);
    word_t w = FUN_00348d94(0).lo;
    cl4_result_t r = FUN_00377824(w, /* x8 */0);
    FUN_00351330(r.lo, r.hi, r.lo);
    FUN_000839f8(0);
}

/* FUN_00333640 @ 0x333640 (est. sk_msg_notify)
 * Notifies: fetches, dispatches, returns code 1.
 * Confidence: medium. Notes: callees FUN_003504d0/348d94/377824/
 *   0007c1c4/839d8. */
void sk_msg_notify(word_t p1, word_t p2, long frame)
{
    word_t w = FUN_003504d0(0);
    FUN_00348d94(w, *(word_t *)(frame + 0x18), *(word_t *)(frame + 0x10));
    FUN_00377824(0);
    cl4_result_t r = FUN_0007c1c4(0);
    FUN_000839d8(r.lo, r.hi, 1);
}

/* FUN_0033367c @ 0x33367c (est. sk_tcb_validate_1b) */
void sk_tcb_validate_1b(long tcb)
{
    FUN_0031d5a8(0x13f, *(word_t *)(tcb + 0x10), *(word_t *)(tcb + 0x18));
    if (/* x1 */0 < 0x40) {
        cl4_result_t r = FUN_0034c16c(0);
        FUN_003728b8(r.lo, r.hi, 1);
        FUN_00019858(0);
    }
}

/* FUN_003336e8 @ 0x3336e8 (est. sk_msg_write_commit_b)
 * Message write/commit variant returning the destination frame word.
 * Confidence: low.
 * Notes: callees FUN_0034d724/348d94/377824/000a6f88/3594a8/356328/
 *   3513e4/839f8/9461c/117cc4/34bfb4/34aed0/839d8/352778/358bb4/36b270. */
long sk_msg_write_commit_b(void)
{
    FUN_0034d724(0);
    FUN_00348d94(0);
    FUN_00377824(0);
    FUN_000a6f88(0);
    ulong dst = *(ulong *)/* x8+0x40 */0;
    int zero = (*(int *)/* table+0x54 */0 == 0);
    if (zero) dst = dst + 1;
    FUN_003594a8(0);
    long frame;
    /* condition: (!carry_set || zero) && w9==0 && dst < 0x19 */
    if (((!0 || zero) && /* w9 */0 == 0) && dst < 0x19) {
        FUN_00356328(0);
        FUN_003513e4(0);
        if (FUN_000839f8(0) != 0) {
            cl4_result_t r = FUN_0009461c(0);
            frame = FUN_00117cc4(r.lo, r.hi, dst);
            return frame;
        }
        FUN_0034bfb4(*(word_t *)/* table+0x10 */0);
        ((void (*)(void))0)();
        FUN_0034aed0(0);
        FUN_000839d8(0);
    } else {
        FUN_00352778(0);
        long r = FUN_00358bb4(0).lo;
        /* x19 = r + x8_00 (accumulated frame word) */
        frame = r + /* x8_00 */0;
        FUN_0036b270(0);
    }
    return frame;
}

/* FUN_003337c4 @ 0x3337c4 (est. sk_msg_peek_dispatch)
 * Peek + conditional dispatch.
 * Confidence: low. Notes: callees FUN_003561f4/348d94/377824/351330/
 *   839f8/3511b4. */
void sk_msg_peek_dispatch(void)
{
    FUN_003561f4(0);
    word_t w = FUN_00348d94(0).lo;
    w = FUN_00377824(w, /* x8 */0);
    cl4_result_t r = FUN_00351330(0);
    if (FUN_000839f8(r.lo, r.hi, w) != 0) return;
    FUN_003511b4(0);
    ((void (*)(void))0)();
}

/* FUN_003338d0 @ 0x3338d0 (est. sk_syscall_cap_copy4_18) table+0x18 */
void sk_syscall_cap_copy4_18(void)
{
    FUN_0034d724(0);
    FUN_00348d94(0);
    FUN_00377824(0);
    FUN_00354924(0);
    int st = FUN_0034e178(0);
    cl4_result_t r;
    long idx;
    if (/* w23 */0 == 0) {
        if (st == 0) {
            FUN_0034bfb4(*(word_t *)/* table+0x18 */0);
            ((void (*)(void))0)();
            return;
        }
        FUN_003507e0(*(word_t *)/* table+8 */0);
        ((void (*)(void))0)();
        r = FUN_00355e44(0);
        idx = /* x9_00 */0;
        st = /* w8_00 */0;
    } else {
        if (st == 0) {
            FUN_0034bfb4(*(word_t *)/* table+0x10 */0);
            ((void (*)(void))0)();
            FUN_0034aed0(0);
            FUN_000839d8(0);
            return;
        }
        r = FUN_00354070(0);
        idx = /* x9 */0;
        st = /* w8 */0;
    }
    if (st == 0) idx = idx + 1;
    FUN_0009461c(r.lo, r.hi, idx);
    FUN_00117cc4(0);
}

/* FUN_003339a4 @ 0x3339a4 (est. sk_cap_release_commit)
 * Cap release/commit path.
 * Confidence: low. Notes: callees FUN_0034d724/348d94/377824/356328/
 *   3513e4/839f8/9461c/117cc4/34aed0/839d8. */
void sk_cap_release_commit(void)
{
    FUN_0034d724(0);
    FUN_00348d94(0);
    FUN_00377824(0);
    FUN_00356328(0);
    FUN_003513e4(0);
    word_t r = FUN_000839f8(0);
    long t = *(long *)/* x21+-8 */0;
    if (r != 0) {
        long dst = *(long *)(t + 0x40);
        if (*(int *)(t + 0x54) == 0) dst = dst + 1;
        FUN_0009461c(r, 0, dst);   /* .hi dropped under word_t convention */
        FUN_00117cc4(0);
        return;
    }
    ((void (*)(void))*(void **)(t + 0x20))();   /* indirect dispatch through table+0x20 */
    FUN_0034aed0(0);
    FUN_000839d8(0);
}

/* FUN_00333a40 @ 0x333a40 (est. sk_syscall_cap_copy4_28) table+0x28 */
void sk_syscall_cap_copy4_28(void)
{
    FUN_0034d724(0);
    FUN_00348d94(0);
    FUN_00377824(0);
    FUN_00354924(0);
    int st = FUN_0034e178(0);
    cl4_result_t r;
    long idx;
    if (/* w23 */0 == 0) {
        if (st == 0) {
            FUN_0034bfb4(*(word_t *)/* table+0x28 */0);
            ((void (*)(void))0)();
            return;
        }
        FUN_003507e0(*(word_t *)/* table+8 */0);
        ((void (*)(void))0)();
        r = FUN_00355e44(0);
        idx = /* x9_00 */0;
        st = /* w8_00 */0;
    } else {
        if (st == 0) {
            FUN_0034bfb4(*(word_t *)/* table+0x20 */0);
            ((void (*)(void))0)();
            FUN_0034aed0(0);
            FUN_000839d8(0);
            return;
        }
        r = FUN_00354070(0);
        idx = /* x9 */0;
        st = /* w8 */0;
    }
    if (st == 0) idx = idx + 1;
    FUN_0009461c(r.lo, r.hi, idx);
    FUN_00117cc4(0);
}

/* FUN_00333b14 @ 0x333b14 (est. sk_msg_cap_validate_2)
 * Message-capability validate returning a count (like 0x32cee4 variant).
 * Confidence: medium.
 * Notes: callees FUN_0034d724/348d94/377824/34ada0/356694/34e32c/
 *   839f8/3585dc. */
ulong sk_msg_cap_validate_2(void)
{
    FUN_0034d724(0);
    FUN_00348d94(0);
    FUN_00377824(0);
    word_t r = FUN_0034ada0(0);
    uint lim = *(uint *)/* table+0x54 */0;
    uint a = (lim != 0) ? lim - 1 : 0;
    long base = *(long *)/* x8+0x40 */0;
    if (lim == 0) base = base + 1;
    if (/* w20 */0 == 0) return 0;
    if (/* w20 */0 <= a) goto fault;
    uint p = (uint)base;
    uint sh = p << 3;
    if (p < 4) {
        FUN_00356694(r, lim, r);
        a = /* w8 */0;
        base = /* x9 */0;
        sh = /* w10 */0;
        lim = /* w1 */0;
        if (!(2 < p) || p == 3) {
            if (/* w11 */0 < 2) goto fault;
            p = (uint)*(byte *)((long)/* x19 */0 + base);
        } else if ((/* w11 */0 >> 0x10) == 0) {
            p = (uint)*(ushort *)((long)/* x19 */0 + base);
        } else {
            p = *(uint *)((long)/* x19 */0 + base);
        }
    } else {
        p = (uint)*(byte *)((long)/* x19 */0 + base);
    }
    uint idx = (uint)base;
    if (p != 0) {
        uint bit = (idx < 4) ? p - 1 << (sh & 0x1f) : 0;
        uint val = 0;
        if (idx != 0) {
            val = 4;
            if (idx < 4) val = idx;
            switch (val) {
            default: val = (uint)(byte)*((uint *)/* x19 */0); break;
            case 2:   val = (uint)(ushort)*((uint *)/* x19 */0); break;
            case 3:   FUN_0034e32c(0); val = /* w9 */0; bit = /* w10_00 */0; a = /* w8_00 */0; break;
            case 4:   val = *((uint *)/* x19 */0); break;
            }
        }
        return (ulong)(a + (val | bit) + 1);
    }
fault:
    if (lim < 2) return 0;
    FUN_000839f8(0);
    return FUN_003585dc(0);
}

/* FUN_00333e68 @ 0x333e68 (est. sk_cap_validate_commit_c) code 2 */
void sk_cap_validate_commit_c(void)
{
    FUN_0034c7c4(0);
    FUN_00377dcc(0);
    if (/* x1 */0 < 0x40) {
        cl4_result_t r = FUN_0034cdf8(0);
        FUN_003728b8(r.lo, r.hi, 2);
        FUN_00019858(0);
    }
}

/* FUN_00333ed0 @ 0x333ed0 (est. sk_cap_release_regs) */
void sk_cap_release_regs(void)
{
    FUN_0034c7c4(0);
    cl4_result_t r = FUN_00377dcc(0);
    if (r.hi < 0x40) {
        FUN_00353424(*(long *)(r.lo + -8) + 0x40);
        FUN_0034d034(0);
        FUN_003728b8(0);
        FUN_00019858(0);
    }
}

/* FUN_003340d4 @ 0x3340d4 (est. sk_tcb_release_regs_e) */
void sk_tcb_release_regs_e(void)
{
    long tcb = FUN_00355150(0);
    cl4_result_t r = FUN_00377dcc(0x13f, *(word_t *)(tcb + 0x10));
    if (r.hi < 0x40) {
        FUN_003558b8(*(long *)(r.lo + -8) + 0x40);
        FUN_0034d1c0(0);
        FUN_003728b8(0);
        FUN_00019858(0);
    }
}

/* FUN_00334148 @ 0x334148 (est. sk_syscall_entry_commit)
 * Syscall entry commit (like 0x32cc70 variant).
 * Confidence: low.
 * Notes: callees FUN_00349d3c/357104/358750/34e974/36b270. */
void sk_syscall_entry_commit(void)
{
    FUN_00349d3c(0);
    FUN_00357104(0);
    /* condition: (!carry_set || zero) && w12==0 && x10 has high bit set */
    if (((/* carry */0 == 0 || /* zero */0 != 0) && /* w12 */0 == 0)
        && (ulong)/* x10 */0 > 0xffffffffffffffe6) {
        /* *x19 = *x1 (copy incoming word) */
        *(word_t *)/* x19 */0 = *(word_t *)/* x1 */0;
        FUN_00358750(0);
        ((void (*)(void))0)();
    } else {
        FUN_0034e974(0);
        FUN_0036b270(0);
    }
}

/* FUN_0033425c @ 0x33425c (est. sk_dispatch3_18) table+0x18 */
void sk_dispatch3_18(void)
{
    FUN_0034f2f4(0);
    cl4_result_t r = FUN_0034a054(0);
    ulong sel = (ulong)*(byte *)/* table+0x50 */0;
    ((void (*)(word_t, word_t))0)
        (sel + 8 + r.lo & ~sel, sel + 8 + r.hi & ~sel);
}

/* FUN_003342b0 @ 0x3342b0 (est. sk_dispatch3_20) table+0x20 */
void sk_dispatch3_20(void)
{
    FUN_0034f2f4(0);
    cl4_result_t r = FUN_0034a054(0);
    ulong sel = (ulong)*(byte *)/* table+0x50 */0;
    ((void (*)(word_t, word_t))0)
        (sel + 8 + r.lo & ~sel, sel + 8 + r.hi & ~sel);
}

/* FUN_00334304 @ 0x334304 (est. sk_dispatch3_28) table+0x28 */
void sk_dispatch3_28(void)
{
    FUN_0034f2f4(0);
    cl4_result_t r = FUN_0034a054(0);
    ulong sel = (ulong)*(byte *)/* table+0x50 */0;
    ((void (*)(word_t, word_t))0)
        (sel + 8 + r.lo & ~sel, sel + 8 + r.hi & ~sel);
}

/* FUN_00334680 @ 0x334680 (est. sk_tcb_validate_commit)
 * TCB validate + commit.
 * Confidence: medium. Notes: callees FUN_0034c7c4/377dcc/377dcc/
 *   3558b8/34d1c0/368980/19858. */
void sk_tcb_validate_commit(void)
{
    FUN_0034c7c4(0);
    cl4_result_t r = FUN_00377dcc(0);
    if (r.hi < 0x40) {
        cl4_result_t r2 = FUN_00377dcc(0x13f, *(word_t *)/* x19+0x18 */0);
        if (r2.hi < 0x40) {
            FUN_003558b8(*(long *)(r2.lo + -8) + 0x40);
            FUN_0034d1c0(0);
            FUN_00368980(0);
            FUN_00019858(0);
        }
    }
}

/* FUN_0033470c @ 0x33470c (est. sk_msg_tag_store)
 * Stores a message tag/flag into the frame at the computed offset. Reads
 * the current byte value at the slot; if >1, merges the tag bits (width
 * 1-4) and increments; if the resulting value is 1 it dispatches the
 * type handler, else clears the flag.
 * Confidence: medium.
 * Notes: callees FUN_00356eb4/35556c/36b270/352c04; SoftwareBreakpoint
 *   on 3-byte case handled by default. */
long sk_msg_tag_store(long frame)
{
    FUN_00356eb4(0);
    long t = *(long *)(*(long *)/* x9+0x18 */0 + -8);
    ulong dst = *(ulong *)(t + 0x40);
    if (dst <= *(ulong *)/* x10+0x40 0;
    uint sel = *(uint *)(t + 0x50) | *(uint *)/* table+0x50 */0;
    if ((7 < (sel & 0xff) || 0x18 < dst + 1) || (sel & 0x100000) != 0) {
        long r = FUN_0035556c(0);
        FUN_0036b270(0);
        return r + (/* x11 */0);
    }
    byte b = *(byte *)((long)/* x1 */0 + dst);
    uint v = (uint)b;
    if (1 < b) {
        uint w = 4;
        if (dst < 4) w = (uint)dst;
        uint lo;
        switch (w) {
        default: lo = (uint)(byte)0; break;
        case 1:  lo = (uint)(byte)0; break;
        case 2:  lo = (uint)(ushort)0; break;
        case 3:  lo = (uint)/* uint3 */0; break;
        case 4:  lo = 0; break;
        }
        v = lo | (uint)(b - 2) << (((uint)dst & 3) << 3);
        if (3 < dst) v = lo;
        v = v + 2;
    }
    if (v == 1) {
        ((void (*)(word_t, word_t, long))0)(frame, /* x1 */0);
        *(und1_t *)(frame + dst) = 1;
    } else {
        FUN_00352c04(0);
        ((void (*)(void))0)();
        *(und1_t *)(frame + dst) = 0;
    }
    return frame;
}

/* FUN_00335418 @ 0x335418 (est. sk_tcb_lookup)
 * Looks up and validates a TCB register cap (tag 0x13f); returns the
 * resolved capability pair, or the 0x3f error code on failure.
 * Confidence: medium.
 * Notes: callees FUN_0034c7c4/377dcc/350bd8/34a32c/377824/3558b8/
 *   34cdf8/3728b8. Returns a 16-byte struct. */
cl4_result_t sk_tcb_lookup(void)
{
    FUN_0034c7c4(0);
    cl4_result_t r = FUN_00377dcc(0);
    long base = r.lo;
    if (r.hi < 0x40) {
        FUN_00350bd8(*(word_t *)/* x19+0x18 */0);
        FUN_0034a32c(0);
        r = FUN_00377824(0x13f, /* x1 */0, base);
        base = r.lo;
        if (r.hi < 0x40) {
            FUN_003558b8(*(long *)(base + -8) + 0x40);
            cl4_result_t r2 = FUN_0034cdf8(0);
            FUN_003728b8(r2.lo, r2.hi, 2);
            base = 0;
            r.hi = 0;
            return r;
        }
    }
    r.hi = 0x3f;
    r.lo = base;
    return r;
}

/* FUN_003354c4 @ 0x3354c4 (est. sk_syscall_msg_write_e)
 * Message write variant.
 * Confidence: low. Notes: callees FUN_00084220/350c5c/349734/350bd8/
 *   348d94/377824/000a6f88/34d5d8/34bfb4/357154/34de74/84234. */
void sk_syscall_msg_write_e(word_t p1, word_t p2, long frame)
{
    FUN_00084220(0);
    FUN_00350c5c(0);
    word_t u = *(word_t *)(frame + 0x10);
    FUN_00349734(*(word_t *)(frame + 0x18));
    FUN_00350bd8(0);
    cl4_result_t r = FUN_00348d94(0);
    FUN_00377824(r.lo, r.hi, u);
    FUN_000a6f88(0);
    FUN_0034d5d8(*(uint *)/* table+0x50 */0 & 0xff);
    if ((/* carry clear && !zero 0 < 0x19) {
        FUN_0034bfb4(*(word_t *)/* table+0x10 */0);
        ((void (*)(void))0)();
        FUN_00357154(0);
        ((void (*)(void))0)();
    } else {
        FUN_0034de74(0);
    }
    FUN_00084234(0);
}

/* FUN_003355b0 @ 0x3355b0 (est. sk_syscall_msg_read_d)
 * Message read variant.
 * Confidence: low. Notes: callees FUN_003504d0/34b3c8/350bd8/348d94/
 *   377824/34bf0c. */
void sk_syscall_msg_read_d(void)
{
    FUN_003504d0(0);
    word_t u3 = *(word_t *)/* x1+0x10 */0;
    word_t w = FUN_0034b3c8(0);
    ((word_t (*)(word_t, word_t))0)(w, u3);
    long dst = *(long *)/* table+0x40 */0;
    FUN_00350bd8(*(word_t *)/* x19+0x18 */0);
    cl4_result_t r = FUN_00348d94(0);
    FUN_00377824(r.lo, r.hi, u3);
    FUN_0034bf0c(0);
    ulong sel = (ulong)*(byte *)/* table2+0x50 */0;
    ((void (*)(ulong))0)(dst + /* x20 */0 + sel & ~sel);
}

/* FUN_003356d8 @ 0x3356d8 (est. sk_dispatch4_18) table+0x18 */
void sk_dispatch4_18(void)
{
    FUN_00348c64(0);
    ((void (*)(void))0)();
    long dst = *(long *)/* table+0x40 */0;
    FUN_00350bd8(*(word_t *)/* x19+0x18 */0);
    FUN_00348d94(0);
    FUN_00377824(0);
    FUN_00349530(0);
    ulong sel = (ulong)*(byte *)/* table2+0x50 */0;
    long addr = dst + sel;
    ((void (*)(word_t, word_t))0)(addr + /* x21 */0 & ~sel, addr + /* x20 */0 & ~sel);
}

/* FUN_00335770 @ 0x335770 (est. sk_dispatch4_20) table+0x20 */
void sk_dispatch4_20(void)
{
    FUN_00348c64(0);
    ((void (*)(void))0)();
    long dst = *(long *)/* table+0x40 */0;
    FUN_00350bd8(*(word_t *)/* x19+0x18 */0);
    FUN_00348d94(0);
    FUN_00377824(0);
    FUN_00349530(0);
    ulong sel = (ulong)*(byte *)/* table2+0x50 */0;
    long addr = dst + sel;
    ((void (*)(word_t, word_t))0)(addr + /* x21 */0 & ~sel, addr + /* x20 */0 & ~sel);
}

/* FUN_00335808 @ 0x335808 (est. sk_dispatch4_28) table+0x28 */
void sk_dispatch4_28(void)
{
    FUN_00348c64(0);
    ((void (*)(void))0)();
    long dst = *(long *)/* table+0x40 */0;
    FUN_00350bd8(*(word_t *)/* x19+0x18 */0);
    FUN_00348d94(0);
    FUN_00377824(0);
    FUN_00349530(0);
    ulong sel = (ulong)*(byte *)/* table2+0x50 */0;
    long addr = dst + sel;
    ((void (*)(word_t, word_t))0)(addr + /* x21 */0 & ~sel, addr + /* x20 */0 & ~sel);
}

/* FUN_003358a0 @ 0x3358a0 (est. sk_msg_cap_validate_3)
 * Message-cap validate variant.
 * Confidence: medium.
 * Notes: callees FUN_00352758/35549c/350bd8/348d94/377824/34f924/
 *   355d34/358184/357ef4/34e888/3551b0/3580f4/34e32c/351538/3520e8/
 *   34bf1c/839f8. */
word_t sk_msg_cap_validate_3(word_t p1, word_t p2, long frame)
{
    FUN_00352758(0);
    word_t u4 = *(word_t *)(frame + 0x10);
    FUN_0035549c(*(word_t *)(frame + 0x18));
    uint limit = *(uint *)/* table+0x54 */0;
    FUN_00350bd8(0);
    cl4_result_t r = FUN_00348d94(0);
    FUN_00377824(r.lo, r.hi, u4);
    FUN_0034f924(0);
    uint lim2 = *(uint *)/* table2+0x54 */0;
    int le = (limit <= lim2), eq = (lim2 == limit);
    FUN_00355d34(0);
    if (/* w22 */0 == 0) return 0;
    FUN_00358184(0);
    uint v = /* w1 */0;
    if (!le || eq) goto out;
    FUN_00357ef4(0);
    long off = /* x11 */0;
    int st = /* w10 */0;
    v = /* w1_00 */0;
    if (!le || eq) {
        FUN_0034e888(0);
        st = /* w10_00 */0;
        v = /* w1_01 */0;
        if (0xff < /* w13 */0) {
            uint b = ((/* w13 */0 >> 0x10) == 0)
                ? (uint)*(ushort *)((long)/* x19 */0 + /* x11_00 */0)
                : *(uint *)((long)/* x19 */0 + /* x11_00 */0);
            if (b != 0) {
                FUN_003551b0(0);
                if (/* w11 */0 != 0) {
                    FUN_003580f4(0);
                    switch (/* w9 */0) { default: case 2: case 3: FUN_0034e32c(0); case 4: break; }
                }
                return FUN_00351538(0);
            }
        } else {
            long o2 = /* x11_00 */0;
            if (1 < /* w13 */0) {
                uint b = (uint)*(byte *)((long)/* x19 */0 + o2);
                if (b != 0) {
                    FUN_003551b0(0);
                    if (/* w11 */0 != 0) {
                        FUN_003580f4(0);
                        switch (/* w9 */0) { default: case 2: case 3: FUN_0034e32c(0); case 4: break; }
                    }
                    return FUN_00351538(0);
                }
            }
        }
    } else {
        uint b = (uint)*(byte *)((long)/* x19 */0 + off);
        if (b != 0) {
            FUN_003551b0(0);
            if (/* w11 */0 != 0) {
                FUN_003580f4(0);
                switch (/* w9 */0) { default: case 2: case 3: FUN_0034e32c(0); case 4: break; }
            }
            return FUN_00351538(0);
        }
    }
    if (st == 0) return 0;
out:
    if (limit < v) FUN_003520e8(0);
    else FUN_0034bf1c(0);
    return FUN_000839f8(0);
}

/* FUN_00335c34 @ 0x335c34 (est. sk_tcb_validate_1c) */
void sk_tcb_validate_1c(void)
{
    FUN_00358c20(0);
    cl4_result_t r = FUN_00350bd8(0);
    FUN_0034a32c(r.lo, r.hi, *(word_t *)/* x19+0x10 */0);
    FUN_00377824(0x13f);
    if (/* x1 */0 < 0x40) {
        cl4_result_t r2 = FUN_0034c16c(0);
        FUN_003728b8(r2.lo, r2.hi, 1);
        FUN_00019858(0);
    }
}

/* FUN_00335ca8 @ 0x335ca8 (est. sk_syscall_entry_b)
 * Syscall entry variant.
 * Confidence: low. Notes: callees FUN_0034da78/350bd8/348d94/377824/
 *   34b57c/35944c/34df14/34de74. */
void sk_syscall_entry_b(word_t p1, word_t p2, long frame)
{
    FUN_0034da78(0);
    cl4_result_t r = FUN_00350bd8(*(word_t *)(frame + 0x18));
    FUN_00348d94(r.lo, r.hi, *(word_t *)/* x21+0x10 */0);
    FUN_00377824(0);
    FUN_0034b57c(0);
    r = FUN_0035944c(/* x16 */0);
    if ((/* carry clear && !zero 0 == 0) {
        FUN_0034df14(r.lo, r.hi, r.lo);
        ((void (*)(void))0)();
    } else {
        FUN_0034de74(0);
    }
}

/* FUN_00335d38 @ 0x335d38 (est. sk_syscall_entry_c)
 * Syscall entry variant.
 * Confidence: low. Notes: callees FUN_003504d0/350bd8/348d94/377824/
 *   350404. */
void sk_syscall_entry_c(void)
{
    FUN_003504d0(0);
    cl4_result_t r = FUN_00350bd8(*(word_t *)/* x1+0x18 */0);
    FUN_00348d94(r.lo, r.hi, *(word_t *)/* x19+0x10 */0);
    FUN_00377824(0);
    FUN_00350404(0);
    ((void (*)(void))0)();
}

/* FUN_00335df0 @ 0x335df0 (est. sk_dispatch5_18) table+0x18 */
void sk_dispatch5_18(word_t p1, word_t p2, long frame)
{
    FUN_0034b430(0);
    cl4_result_t r = FUN_00350bd8(*(word_t *)(frame + 0x18));
    FUN_00348d94(r.lo, r.hi, *(word_t *)/* x19+0x10 */0);
    FUN_00377824(0);
    FUN_00349530(0);
    ((void (*)(void))0)();
}

/* FUN_00335e50 @ 0x335e50 (est. sk_dispatch5_20) table+0x20 */
void sk_dispatch5_20(word_t p1, word_t p2, long frame)
{
    FUN_0034b430(0);
    cl4_result_t r = FUN_00350bd8(*(word_t *)(frame + 0x18));
    FUN_00348d94(r.lo, r.hi, *(word_t *)/* x19+0x10 */0);
    FUN_00377824(0);
    FUN_00349530(0);
    ((void (*)(void))0)();
}

/* FUN_00335eb0 @ 0x335eb0 (est. sk_dispatch5_28) table+0x28 */
void sk_dispatch5_28(word_t p1, word_t p2, long frame)
{
    FUN_0034b430(0);
    cl4_result_t r = FUN_00350bd8(*(word_t *)(frame + 0x18));
    FUN_00348d94(r.lo, r.hi, *(word_t *)/* x19+0x10 */0);
    FUN_00377824(0);
    FUN_00349530(0);
    ((void (*)(void))0)();
}

/* FUN_00335f10 @ 0x335f10 (est. sk_msg_cap_validate_4)
 * Message-cap validate returning capability.
 * Confidence: medium.
 * Notes: callees FUN_00350c5c/350bd8/348d94/377824/000a6f88/355208/
 *   352f78/839f8. */
word_t sk_msg_cap_validate_4(word_t p1, word_t p2, long frame)
{
    long fr = frame;
    FUN_00350c5c(0);
    cl4_result_t r = FUN_00350bd8(*(word_t *)(fr + 0x18));
    FUN_00348d94(r.lo, r.hi, *(word_t *)(frame + 0x10));
    FUN_00377824(0);
    word_t w = FUN_000a6f88(0);
    uint limit = *(uint *)/* table+0x54 */0;
    long base = *(long *)/* x8+0x40 */0;
    if (/* w20 */0 == 0) return 0;
    if (/* w20 */0 <= limit) goto out;
    if ((uint)base < 4) {
        FUN_00355208(w, limit, w);
        base = /* x8_00 */0;
        limit = /* w1 */0;
        if (0xff < /* w10 */0 >> 0x10) == 0)
                ? (uint)*(ushort *)((long)/* x19 */0)
                : *(uint *)((long)/* x19 */0);
            if (b != 0) {
                uint sz = (uint)base;
                if (sz != 0) {
                    sz = 4;
                    if (sz < 4) sz = sz;
                    switch (sz) { default: case 2: case 3: case 4: break; }
                }
                return FUN_00352f78(0);
            }
        } else if (1 < /* w10 */0) {
            if (b != 0) {
                uint sz = (uint)base;
                if (sz != 0) {
                    sz = 4;
                    if (sz < 4) sz = sz;
                    switch (sz) { default: case 2: case 3: case 4: break; }
                }
                return FUN_00352f78(0);
            }
        }
    } else {
        uint b = (uint)*(byte *)((long)/* x19 */0 + base);
        if (b != 0) {
            uint sz = (uint)base;
            if (sz != 0) {
                sz = 4;
                if (sz < 4) sz = sz;
                switch (sz) { default: case 2: case 3: case 4: break; }
            }
            return FUN_00352f78(0);
        }
    }
    if (limit == 0) return 0;
out:
    return FUN_000839f8(0);
}

/* FUN_003362c8 @ 0x3362c8 (est. sk_cap_validate_commit_d) code 2 */
void sk_cap_validate_commit_d(void)
{
    FUN_0034c7c4(0);
    FUN_00377dcc(0);
    if (/* x1 */0 < 0x40) {
        cl4_result_t r = FUN_0034cdf8(0);
        FUN_003728b8(r.lo, r.hi, 2);
        FUN_00019858(0);
    }
}

/* FUN_00336338 @ 0x336338 (est. sk_entry_commit_c)
 * Entry commit variant.
 * Confidence: low. Notes: callees FUN_00349d3c/35510c/34c144/34df14/
 *   349cd0/349a9c/36b270. */
void sk_entry_commit_c(void)
{
    FUN_00349d3c(0);
    FUN_0035510c(/* x16 */0);
    FUN_0034c144(0);
    if (/* zero && x10<0x19 */1) {
        FUN_0034df14(0);
        ((void (*)(void))0)();
        FUN_00349cd0(0);
        0 = 0;
    } else {
        FUN_00349a9c(0);
        FUN_0036b270(0);
    }
}

/* FUN_003363c8 @ 0x3363c8 (est. sk_dispatch6_10) table+0x10 */
void sk_dispatch6_10(void)
{
    FUN_00349928(0);
    ((void (*)(void))0)();
    FUN_00349104(*(word_t *)/* table+0x40 */0);
    FUN_0034fa0c(0);
}
/* FUN_00336418 @ 0x336418 (est. sk_dispatch6_18) table+0x18 */
void sk_dispatch6_18(void)
{
    FUN_00349928(0);
    ((void (*)(void))0)();
    FUN_00349104(*(word_t *)/* table+0x40 */0);
    FUN_0034fa0c(0);
}
/* FUN_00336464 @ 0x336464 (est. sk_dispatch6_20) table+0x20 */
void sk_dispatch6_20(void)
{
    FUN_00349928(0);
    ((void (*)(void))0)();
    FUN_00349104(*(word_t *)/* table+0x40 */0);
    FUN_0034fa0c(0);
}
/* FUN_003364b4 @ 0x3364b4 (est. sk_dispatch6_28) table+0x28 */
void sk_dispatch6_28(void)
{
    FUN_00349928(0);
    ((void (*)(void))0)();
    FUN_00349104(*(word_t *)/* table+0x40 */0);
    FUN_0034fa0c(0);
}

/* FUN_0033660c @ 0x33660c (est. sk_slot_write_value_b)
 * Writes a small value into the slot at a computed offset (like 0x330df4).
 * Confidence: medium.
 * Notes: callees FUN_00356054/34b7e4/353844/9461c/114330/839d8;
 *   SoftwareBreakpoint on 3-byte width. */
void sk_slot_write_value_b(void)
{
    FUN_00356054(0);
    FUN_0034b7e4(0);
    uint limit = *(uint *)/* table+0x54 */0;
    FUN_00353844(0);
    long off = /* x9 */0 + 8;
    uint width = 0;
    if (/* w8 */0 - limit != 0) {
        uint size = 2;
        uint sv = ((int)off == 0) ? (/* w8 */0 - limit) + 1 : size;
        if (0xffff < sv) size = 4;
        if (sv < 0x100) size = 1;
        width = (1 < sv) ? size : 0;
    }
    int diff = /* w1 */0 - limit;
    if (/* w1 */0 + off) = 0;
            if (/* w1 */0 == 0) return;
            break;
        case 2:
            *(und2_t *)((long)/* x19 */0 + off) = 0;
            break;
        case 3: SK_BREAKPOINT();   /* SoftwareBreakpoint(1,0x33676c) 0 + off) = 0;
        default:
            if (/* w1 */0 != 0) { FUN_000839d8(0); return; }
        }
    } else {
        if ((int)off != 0) {
            diff = 1;
            FUN_0009461c(0);
            FUN_00114330(0);
            0 = /* w1 */0 + ~limit;
        }
        switch (width) {
        case 1: *(char *)((long)/* x19 */0 + off) = (char)diff; break;
        case 2: *(short *)((long)/* x19 */0 + off) = (short)diff; break;
        case 3: SK_BREAKPOINT();   /* SoftwareBreakpoint(1,0x33676c) 0 + off) = diff; break;
        }
    }
}

/* FUN_003367b4 @ 0x3367b4 (est. sk_resume_2a) */
void sk_resume_2a(void) { FUN_0034d4d4(0); sk_entry_commit_d(); }

/* sk_entry_commit_d @ 0x3367cc (est. sk_entry_commit_d)
 * Entry commit variant with a store.
 * Confidence: low. Notes: callees FUN_0034d724/377824/34b57c/35510c/
 *   34c144/34df14/349cd0/349a9c/36b270. */
void sk_entry_commit_d(void)
{
    FUN_0034d724(0);
    FUN_00377824(0);
    FUN_0034b57c(0);
    FUN_0035510c(/* x16 */0);
    cl4_result_t r = FUN_0034c144(0);
    if (/* zero && x10<0x19 */1) {
        FUN_0034df14(r.lo, r.hi, r.lo);
        ((void (*)(void))0)();
        FUN_00349cd0(0);
        0 = 0;
    } else {
        FUN_00349a9c(0);
        FUN_0036b270(0);
    }
}

/* FUN_00336878 @ 0x336878 (est. sk_slot_setup_dispatch_b) */
void sk_slot_setup_dispatch_b(void)
{
    cl4_result_t r = FUN_00355694(0);
    long base = r.hi;
    FUN_003524bc(*(word_t *)(base + 0x18), r.lo, base, *(word_t *)(base + 0x10));
    FUN_00377824(0);
    FUN_00350404(0);
    ((void (*)(void))0)();
}

/* sk_dispatch7_10 @ 0x3368e0 (est. sk_dispatch7_10) table+0x10 */
void sk_dispatch7_10(void)
{
    FUN_0034dbd8(0);
    FUN_00377824(0);
    FUN_00349530(0);
    ((void (*)(void))0)();
    FUN_00349104(*(word_t *)/* table+0x40 */0);
    FUN_0034fa0c(0);
}
/* FUN_00336940 @ 0x336940 (est. sk_resume_2b) */
void sk_resume_2b(void) { FUN_0034d4d4(0); sk_dispatch7_18(); }
/* sk_dispatch7_18 @ 0x336958 (est. sk_dispatch7_18) table+0x18 */
void sk_dispatch7_18(void)
{
    FUN_0034dbd8(0);
    FUN_00377824(0);
    FUN_00349530(0);
    ((void (*)(void))0)();
    FUN_00349104(*(word_t *)/* table+0x40 */0);
    FUN_0034fa0c(0);
}
/* FUN_003369b8 @ 0x3369b8 (est. sk_resume_2c) */
void sk_resume_2c(void) { FUN_0034d4d4(0); sk_dispatch7_20(); }
/* sk_dispatch7_20 @ 0x3369d0 (est. sk_dispatch7_20) table+0x20 */
void sk_dispatch7_20(void)
{
    FUN_0034dbd8(0);
    FUN_00377824(0);
    FUN_00349530(0);
    ((void (*)(void))0)();
    FUN_00349104(*(word_t *)/* table+0x40 */0);
    FUN_0034fa0c(0);
}
/* FUN_00336a30 @ 0x336a30 (est. sk_resume_2d) */
void sk_resume_2d(void) { FUN_0034d4d4(0); sk_dispatch7_28(); }
/* sk_dispatch7_28 @ 0x336a48 (est. sk_dispatch7_28) table+0x28 */
void sk_dispatch7_28(void)
{
    FUN_0034dbd8(0);
    FUN_00377824(0);
    FUN_00349530(0);
    ((void (*)(void))0)();
    FUN_00349104(*(word_t *)/* table+0x40 */0);
    FUN_0034fa0c(0);
}
/* FUN_00336aa8 @ 0x336aa8 (est. sk_resume_2e) */
void sk_resume_2e(void) { FUN_0034d4d4(0); sk_msg_cap_validate_5(); }

/* sk_msg_cap_validate_5 @ 0x336ac0 (est. sk_msg_cap_validate_5)
 * Message-cap validate returning capability.
 * Confidence: medium.
 * Notes: callees FUN_0034d724/377824/000a6f88/355d60/357e04/352f78/
 *   839f8; SoftwareBreakpoint on 3-byte. */
word_t sk_msg_cap_validate_5(void)
{
    FUN_0034d724(0);
    FUN_00377824(0);
    word_t w = FUN_000a6f88(0);
    if (/* w20 */0 == 0) return 0;
    if (*(uint *)/* table+0x54 0) {
        FUN_00355d60(*(word_t *)/* x8+0x40 0, w);
        FUN_00357e04(/* x8_00 */0 + 8U & 0xfffffff8);
        uint width = (/* w10 */0;
        uint sel = (1 < /* w10 */0) ? width : 0;
        switch (sel) {
        case 1:
            if (*(char *)(/* x19 */0) != '\0') return FUN_00352f78(0);
            break;
        case 2:
            if (*(short *)(/* x19 */0) != 0) return FUN_00352f78(0);
            break;
        case 3: SK_BREAKPOINT();   /* SoftwareBreakpoint(1,0x336bbc) 0 + /* x9 */0) != 0) return FUN_00352f78(0);
        }
        if (/* w1 */0 == 0) return 0;
    }
    return FUN_000839f8(0);
}

/* FUN_00336be4 @ 0x336be4 (est. sk_slot_write_value_c)
 * Slot write value variant with explicit param_3 count.
 * Confidence: medium.
 * Notes: callees FUN_00350c5c/356358/377824/000a6f88/355d60/9461c/
 *   114330/839d8/3507e0; SoftwareBreakpoint on 3-byte. */
void sk_slot_write_value_c(word_t p1, word_t p2, uint count, long frame)
{
    FUN_00350c5c(0);
    FUN_00356358(0, *(word_t *)(frame + 0x18), *(word_t *)(frame + 0x10));
    FUN_00377824(0);
    FUN_000a6f88(0);
    uint limit = *(uint *)/* table+0x54 */0;
    FUN_00355d60(*(word_t *)/* x8+0x40 */0);
    long off = /* x8_00 */0 + 8;
    uint width = 0;
    if (count >= limit && count - limit != 0) {
        uint size = 2;
        uint sv = ((int)off == 0) ? (count - limit) + 1 : size;
        if (0xffff < sv) size = 4;
        if (sv < 0x100) size = 1;
        width = (1 < sv) ? size : 0;
    }
    int diff = /* w20 */0 - limit;
    if (/* w20 */0 + off) = 0;
            if (/* w20 */0 == 0) return;
            break;
        case 2:
            *(und2_t *)((long)/* x19 */0 + off) = 0;
            break;
        case 3: SK_BREAKPOINT();   /* SoftwareBreakpoint(1,0x336d54) 0 + off) = 0;
        default:
            if (/* w20 */0 != 0) { FUN_0009461c(0); FUN_000839d8(0); return; }
        }
    } else {
        if ((int)off != 0) {
            diff = 1;
            FUN_003507e0(0);
            FUN_00114330(0);
            0 = /* w20 */0 + ~limit;
        }
        switch (width) {
        case 1: *(char *)((long)/* x19 */0 + off) = (char)diff; break;
        case 2: *(short *)((long)/* x19 */0 + off) = (short)diff; break;
        case 3: SK_BREAKPOINT();   /* SoftwareBreakpoint(1,0x336d54) 0 + off) = diff; break;
        }
    }
}

/* FUN_00336d80 @ 0x336d80 (est. sk_tcb_release_extra_b)
 * Releases extra TCB state; commits code 2.
 * Confidence: medium. Notes: callees FUN_0034d4d4/3510c4/377824/34a820/
 *   3510c4/377824/357acc/3558b8/34cdf8/3728b8/19858. */
void sk_tcb_release_extra_b(void)
{
    FUN_0034d4d4(0);
    FUN_003510c4(0x13f);
    FUN_00377824(0);
    int is_big = 0x3e < /* x1 */0;
    int is_3f = (/* x1 */0 == 0x3f);
    if (/* x1 */0 < 0x40) {
        FUN_0034a820(0);
        FUN_003510c4(0xff);
        FUN_00377824(0);
        long l = FUN_00357acc(0);
        if (!is_big || is_3f) {
            FUN_003558b8(*(long *)(l + -8) + 0x40);
            cl4_result_t r = FUN_0034cdf8(0);
            FUN_003728b8(r.lo, r.hi, 2);
            FUN_00019858(0);
        }
    }
}

/* FUN_00336e30 @ 0x336e30 (est. sk_syscall_msg_write_f)
 * Message write variant.
 * Confidence: low.
 * Notes: callees FUN_0008e518/350c5c/34bd80/3513a8/377824/348ce8/
 *   34c654/3513a8/377824/000a6f88/34d5d8/9461c/3513e4/839f8/34befc/
 *   839d8/117cc4/34de74/8e500. */
void sk_syscall_msg_write_f(void)
{
    FUN_0008e518(0);
    FUN_00350c5c(0);
    FUN_0034bd80(0);
    FUN_003513a8(0);
    FUN_00377824(0);
    FUN_00348ce8(0);
    long dst = *(long *)/* x8+0x40 */0;
    FUN_0034c654(0);
    FUN_003513a8(0);
    FUN_00377824(0);
    FUN_000a6f88(0);
    dst = dst + (ulong)(byte)*(uint *)/* table+0x50 */0;
    long lim = *(long *)/* x8_00+0x40 */0;
    int zero = (*(int *)/* table+0x54 */0 == 0);
    if (zero) lim = lim + 1;
    word_t sz = FUN_0034d5d8(*(uint *)/* table+0x50 */0 & 0xff);
    if ((zero /*&&...*/) && (ulong)/* x11 */0 < 0x19) {
        ulong mask = ~/* x8_01 */0;
        FUN_0009461c(*(word_t *)/* table+0x10 */0);
        ((void (*)(void))0)();
        ulong a = dst + /* x19 */0;
        FUN_003513e4(b & mask);
        if (FUN_000839f8(0) == 0) {
            ((void (*)(word_t, word_t, word_t))0)(a & mask, b & mask, sz);
            FUN_0034befc(a & mask);
            FUN_000839d8(0);
        } else {
            FUN_00117cc4(a & mask, b & mask, lim);
        }
    } else {
        FUN_0034de74(0);
    }
    FUN_0008e500(0);
}

/* FUN_00336f88 @ 0x336f88 (est. sk_syscall_msg_read_e)
 * Message read variant.
 * Confidence: low (indirect jump).
 * Notes: callees FUN_00357cb4/34bd80/350878/377824/841a0/34c654/
 *   350878/377824/35295c/351390/839f8/35631c/357c74. */
void sk_syscall_msg_read_e(void)
{
    long base = FUN_00357cb4(0);
    void *jt = /* x30 */0;
    FUN_0034bd80(0);
    FUN_00350878(0);
    FUN_00377824(0);
    FUN_000841a0(0);
    ((void (*)(long))0)(base);
    long dst = *(long *)/* table+0x40 */0;
    FUN_0034c654(0);
    FUN_00350878(0);
    word_t w = FUN_00377824(0);
    FUN_0035295c(0);
    ulong sel = (ulong)*(byte *)/* table+0x50 */0;
    ulong addr = dst + base + sel;
    FUN_00351390(addr & ~sel);
    if (FUN_000839f8(0) != 0) {
        FUN_00357c74(/* x30 */0);
        return;
    }
    FUN_0035631c(0);
    FUN_00357c74(addr & ~sel, w);
    ((void (*)(void))jt)();   /* indirect jump */
}

/* FUN_00337068 @ 0x337068 (est. sk_syscall_cap_copy5_10) table+0x10 */
void sk_syscall_cap_copy5_10(word_t p1, word_t p2, long frame)
{
    FUN_00352758(0);
    word_t u2 = *(word_t *)(frame + 0x18);
    FUN_0034bd80(0);
    FUN_003510c4(0);
    FUN_00377824(0);
    FUN_00349530(0);
    ((void (*)(void))0)();
    ulong dst = *(ulong *)/* table+0x40 */0;
    FUN_0034c654(0);
    FUN_003510c4(0);
    FUN_00377824(0);
    FUN_00350fbc(0);
    byte sel = *(byte *)/* table+0x50 */0;
    FUN_00359d2c(0);
    FUN_0035163c(/* x8 */0 & ~(ulong)sel);
    if (FUN_000839f8(0) == 0) {
        cl4_result_t r = FUN_00359588(*(word_t *)/* table+0x10 */0);
        ((void (*)(word_t, word_t, word_t))0)(r.lo, r.hi, u2);
        FUN_0034c9e8(dst & ~(ulong)sel);
        FUN_000839d8(0);
    } else {
        cl4_result_t r = FUN_00357d74(0);
        long l = /* x9 */0;
        if (/* zero */0 + 1;
        FUN_00359588(r.lo, r.hi, l);
        FUN_00117cc4(0);
    }
}

/* FUN_00337158 @ 0x337158 (est. sk_syscall_cap_copy6_18) table+0x18 */
void sk_syscall_cap_copy6_18(word_t p1, word_t p2, long frame)
{
    FUN_00084220(0);
    FUN_00352758(0);
    word_t u1 = *(word_t *)(frame + 0x18);
    FUN_0034bd80(0);
    FUN_003510c4(0);
    FUN_00377824(0);
    FUN_00349530(0);
    ((void (*)(void))0)();
    ulong dst = *(ulong *)/* table+0x40 */0;
    FUN_0034c654(0);
    FUN_003510c4(0);
    FUN_00377824(0);
    FUN_00350fbc(0);
    ulong sel = (ulong)*(byte *)/* table+0x50 */0;
    FUN_00359d2c(0);
    FUN_0035163c(dst & ~sel);
    int i2 = FUN_000839f8(0);
    FUN_0035163c(/* x8 */0 & ~sel);
    word_t rr = FUN_000839f8(0);
    cl4_result_t r;
    int st; long l3;
    if (i2 == 0) {
        if (rr == 0) {
            r = FUN_00352f3c(*(word_t *)/* table+0x18 */0);
            ((void (*)(word_t, word_t, word_t))0)(r.lo, r.hi, u1);
            goto tail;
        }
        rr = ((cl4_result_t (*)(word_t, word_t))0)(dst & ~sel, u1);
        st = *(int *)/* table+0x54 */0;
        l3 = *(long *)/* table+0x40 */0;
    } else {
        if (rr == 0) {
            r = FUN_00352f3c(*(word_t *)/* table+0x10 */0);
            ((void (*)(word_t, word_t, word_t))0)(r.lo, r.hi, u1);
            FUN_0034c9e8(dst & ~sel);
            FUN_000839d8(0);
            goto tail;
        }
        st = *(int *)/* table+0x54 */0;
        l3 = *(long *)/* table+0x40 */0;
    }
    if (st == 0) l3 = l3 + 1;
    FUN_00352f3c(rr.lo, rr.hi, l3);
    FUN_00117cc4(0);
tail:
    FUN_00084234(0);
}

/* FUN_003372a8 @ 0x3372a8 (est. sk_syscall_cap_copy5_20) table+0x20 */
void sk_syscall_cap_copy5_20(word_t p1, word_t p2, long frame)
{
    FUN_00352758(0);
    word_t u2 = *(word_t *)(frame + 0x18);
    FUN_0034bd80(0);
    FUN_003510c4(0);
    FUN_00377824(0);
    FUN_00349530(0);
    ((void (*)(void))0)();
    ulong dst = *(ulong *)/* table+0x40 */0;
    FUN_0034c654(0);
    FUN_003510c4(0);
    FUN_00377824(0);
    FUN_00350fbc(0);
    byte sel = *(byte *)/* table+0x50 */0;
    FUN_00359d2c(0);
    FUN_0035163c(/* x8 */0 & ~(ulong)sel);
    if (FUN_000839f8(0) == 0) {
        cl4_result_t r = FUN_00359588(*(word_t *)/* table+0x20 */0);
        ((void (*)(word_t, word_t, word_t))0)(r.lo, r.hi, u2);
        FUN_0034c9e8(dst & ~(ulong)sel);
        FUN_000839d8(0);
    } else {
        cl4_result_t r = FUN_00357d74(0);
        long l = /* x9 */0;
        if (/* zero */0 + 1;
        FUN_00359588(r.lo, r.hi, l);
        FUN_00117cc4(0);
    }
}

/* FUN_00337398 @ 0x337398 (est. sk_syscall_cap_copy6_28) table+0x28 */
void sk_syscall_cap_copy6_28(word_t p1, word_t p2, long frame)
{
    FUN_00084220(0);
    FUN_00352758(0);
    word_t u1 = *(word_t *)(frame + 0x18);
    FUN_0034bd80(0);
    FUN_003510c4(0);
    FUN_00377824(0);
    FUN_00349530(0);
    ((void (*)(void))0)();
    ulong dst = *(ulong *)/* table+0x40 */0;
    FUN_0034c654(0);
    FUN_003510c4(0);
    FUN_00377824(0);
    FUN_00350fbc(0);
    ulong sel = (ulong)*(byte *)/* table+0x50 */0;
    FUN_00359d2c(0);
    FUN_0035163c(dst & ~sel);
    int i2 = FUN_000839f8(0);
    FUN_0035163c(/* x8 */0 & ~sel);
    word_t rr = FUN_000839f8(0);
    cl4_result_t r;
    int st; long l3;
    if (i2 == 0) {
        if (rr == 0) {
            r = FUN_00352f3c(*(word_t *)/* table+0x28 */0);
            ((void (*)(word_t, word_t, word_t))0)(r.lo, r.hi, u1);
            goto tail;
        }
        rr = ((cl4_result_t (*)(word_t, word_t))0)(dst & ~sel, u1);
        st = *(int *)/* table+0x54 */0;
        l3 = *(long *)/* table+0x40 */0;
    } else {
        if (rr == 0) {
            r = FUN_00352f3c(*(word_t *)/* table+0x20 */0);
            ((void (*)(word_t, word_t, word_t))0)(r.lo, r.hi, u1);
            FUN_0034c9e8(dst & ~sel);
            FUN_000839d8(0);
            goto tail;
        }
        st = *(int *)/* table+0x54 */0;
        l3 = *(long *)/* table+0x40 */0;
    }
    if (st == 0) l3 = l3 + 1;
    FUN_00352f3c(rr.lo, rr.hi, l3);
    FUN_00117cc4(0);
tail:
    FUN_00084234(0);
}

/* FUN_003374e8 @ 0x3374e8 (est. sk_msg_cap_validate_write_d)
 * Message-cap validate/write variant (like 0x32e520).
 * Confidence: medium.
 * Notes: callees FUN_0008e518/352758/34bd80/34db28/377824/358f30/
 *   34c654/34db28/377824/34c11c/358194/3550cc/34d5b8/3525b8/3538d4/
 *   34e32c/351538/34bf1c/3520e8/839f8/3585dc/8e500. */
void sk_msg_cap_validate_write_d(void)
{
    FUN_0008e518(0);
    FUN_00352758(0);
    FUN_0034bd80(0);
    FUN_0034db28(0);
    FUN_00377824(0);
    FUN_00358f30(0);
    uint limit = *(uint *)/* table+0x54 */0;
    FUN_0034c654(0);
    FUN_0034db28(0);
    FUN_00377824(0);
    FUN_0034c11c(0);
    int zero = (*(int *)/* table+0x54 */0 == 0);
    word_t out = 0;
    if (/* w22 */0);
        uint v = /* w11 */0;
        if (1 /*&& !zero*/) {
            FUN_003550cc(0);
            long off = /* x12 */0;
            int st = /* w10 */0;
            v = /* w11_00 */0;
            if (!1 || zero) {
                FUN_0034d5b8(0);
                st = /* w10_00 */0;
                v = /* w11_01 */0;
                if (1 && !zero) {
                    uint b = ((/* w14 */0 >> 0x10) == 0) ? (uint)*(ushort *)((long)/* x19 */0 + /* x12_00 */0) : *(uint *)((long)/* x19 */0 + /* x12_00 */0);
                    if (b != 0) {
                        FUN_003525b8(0);
                        if (/* w12 */0 != 0) {
                            FUN_003538d4(0);
                            switch (/* w9 */0) { default: case 2: case 3: FUN_0034e32c(0); case 4: break; }
                        }
                        out = FUN_00351538(0);
                        goto done;
                    }
                } else {
                    long o2 = /* x12_00 */0;
                    if (1 < /* w14 */0) {
                        if (b != 0) {
                            FUN_003525b8(0);
                            if (/* w12 */0 != 0) {
                                FUN_003538d4(0);
                                switch (/* w9 */0) { default: case 2: case 3: FUN_0034e32c(0); case 4: break; }
                            }
                            out = FUN_00351538(0);
                            goto done;
                        }
                    }
                }
            } else {
                uint b = (uint)*(byte *)((long)/* x19 */0 + off);
                if (b != 0) {
                    FUN_003525b8(0);
                    if (/* w12 */0 != 0) {
                        FUN_003538d4(0);
                        switch (/* w9 */0) { default: case 2: case 3: FUN_0034e32c(0); case 4: break; }
                    }
                    out = FUN_00351538(0);
                    goto done;
                }
            }
            if (st == 0) { out = 0; goto done; }
        }
        if (v <= limit) {
            FUN_0034bf1c(0);
            FUN_0008e500(0);
            FUN_000839f8(0);
            return;
        }
        FUN_003520e8(0);
        FUN_000839f8(0);
        out = FUN_003585dc(0);
    }
done:
    FUN_0008e500(out, /* x30 */0);
}

/* FUN_00337694 @ 0x337694 (est. sk_msg_slot_write)
 * Message slot write with size selection and count bookkeeping.
 * Confidence: medium.
 * Notes: callees FUN_0008e518/350c5c/34bd80/351178/377824/352820/
 *   34c654/351178/377824/34cb60/34ebe0/34e9a4/114330/34f20c/3507e0/
 *   3535cc/353fb8/357dd4/9461c/839d8/8e500. */
void sk_msg_slot_write(word_t p1, word_t p2, uint count)
{
    FUN_0008e518(0);
    FUN_00350c5c(0);
    FUN_0034bd80(0);
    FUN_00351178(0);
    FUN_00377824(0);
    FUN_00352820(0);
    uint lim = *(uint *)/* table+0x54 */0;
    FUN_0034c654(0);
    FUN_00351178(0);
    FUN_00377824(0);
    bool set = false;
    FUN_0034cb60(0);
    int lim2 = *(int *)/* table+0x54 */0;
    uint a = (lim2 != 0) ? (uint)lim2 - 1 : 0;
    uint top = (a <= lim) ? lim : a;
    ulong sel = (ulong)*(byte *)/* table+0x50 */0;
    ulong base = *(long *)/* x27+0x40 */0 + sel;
    long dst = *(long *)/* x8+0x40 */0;
    if (lim2 == 0) dst = dst + 1;
    long off = (base & ~sel) + dst;
    uint p = (uint)off;
    uint sh = p << 3;
    if (top < count) {
        if (p < 4) {
            FUN_0034ebe0(0);
            base = /* x9 */0;
            sel = /* x12 */0;
            top = /* w11 */0;
            sh = /* w8 */0;
            a = /* w10 */0;
            if (/* w13 */0;
        } else {
            set = true;
        }
    }
    char cv;
    if (top < /* w20 */0 + ~top;
        if (p < 4) {
            cv = (char)(diff >> (sh & 0x1f)) + '\x01';
            if (p != 0) {
                word_t w = FUN_0034e9a4(0);
                FUN_00114330(w, off);
                if (p == 3) FUN_0034f20c(0);
                else if (p == 2) *(short *)/* x19 */0 = (short)lim;
                else *(char *)/* x19 */0 = (char)diff;
            }
        } else {
            FUN_003507e0(0);
            FUN_00114330(0);
            0 = diff;
            cv = '\x01';
        }
        if (set) *(char *)((long)/* x19 */0 + off) = cv;
    } else {
        if (set) *(und1_t *)((long)/* x19 */0 + off) = 0;
        if (/* w20 */0 & ~sel);
                if (a < /* w20 */0) {
                    FUN_003535cc(0);
                    if (/* w1 */0 != 0) {
                        FUN_00353fb8(0);
                        switch (p) {
                        default: *(char *)p2 = (char)/* w20 */0; break;
                        case 2:  *(short *)p2 = (short)/* w20 */0; break;
                        case 3:  FUN_00357dd4(0); break;
                        case 4:  *p2 = /* w20 */0; break;
                        }
                    }
                    goto tail;
                }
                cl4_result_t r = { .lo = (word_t)p2, .hi = (uint)/* w20 */0 + 1, };
                FUN_0008e500(r.lo, r.hi);
                FUN_000839d8(0);
                return;
            } else {
                cl4_result_t r = FUN_0009461c(0);
                FUN_0008e500(r.lo, r.hi);
                FUN_000839d8(0);
                return;
            }
        }
    }
tail:
    FUN_0008e500(/* x30 */0);
}

/* FUN_003379a8 @ 0x3379a8 (est. sk_release_common) */
void sk_release_common(void)
{
    FUN_0034b044(0);
    FUN_0036b270(0);
    FUN_0036b118(0);
    FUN_003566cc(0);
    FUN_0035270c(0);
    FUN_00357d34(0);
}

/* FUN_003379e8 @ 0x3379e8 (est. sk_release_fetch) */
void sk_release_fetch(void)
{
    word_t *cur = (word_t *)FUN_003504d0(0);
    FUN_0036b118(*cur);
    FUN_003597cc(0);
    FUN_00357d34(0);
}

/* FUN_00337a60 @ 0x337a60 (est. sk_pair_copy)
 * Copies a 16-byte pair and runs the release helper.
 * Confidence: medium. Notes: callees FUN_0036b270. */
word_t *sk_pair_copy(word_t *dst, word_t *src)
{
    word_t s1 = src[1];
    dst[0] = src[0];
    dst[1] = s1;
    FUN_0036b270(0);
    return dst;
}

/* FUN_00337a94 @ 0x337a94 (est. sk_release_common_b) */
void sk_release_common_b(void)
{
    FUN_0034b044(0);
    FUN_0036b270(0);
    FUN_0036b118(0);
    FUN_003566cc(0);
}

/* FUN_00337ad0 @ 0x337ad0 (est. sk_pair_store_release) */
void sk_pair_store_release(void)
{
    word_t *cur = (word_t *)FUN_0034d454(0);
    word_t w = *cur;
    0 = /* x8 */0;
    FUN_0036b118(w);
    FUN_003566cc(0);
}

/* FUN_00337b44 @ 0x337b44 (est. sk_sched_yield_common_d) */
void sk_sched_yield_common_d(void) { FUN_00353498(0); FUN_00374104(0); FUN_003546b4(0); }

/* FUN_00337b74 @ 0x337b74 (est. sk_tcb_release_pair)
 * Releases TCB state: validates both register caps (tag 0x13f) at
 * +0x10 and +0x18; on success commits with code 3.
 * Confidence: medium.
 * Notes: callees FUN_0034a32c/377824/377dcc/34c16c/3728b8/19858. */
void sk_tcb_release_pair(long tcb)
{
    word_t w = *(word_t *)(tcb + 0x10);
    FUN_0034a32c(tcb, *(word_t *)(tcb + 0x18));
    FUN_00377824(0x13f, /* x1 */0, w);
    if ((/* x1_00 */0 < 0x40)) {
        cl4_result_t r = FUN_0034c16c(0);
        FUN_003728b8(r.lo, r.hi, 3);
        FUN_00019858(0);
    }
}

/* FUN_00337c14 @ 0x337c14 (est. sk_syscall_msg_write_g)
 * Message write variant with copy.
 * Confidence: low.
 * Notes: callees FUN_00351e20/353fac/348d94/377824/000a6f88/34df04/
 *   352e90/35060c/3504f4/358bb4/36b270/351d30. */
void sk_syscall_msg_write_g(word_t p1, word_t p2, long frame)
{
    FUN_00351e20(0);
    word_t u2 = FUN_00353fac(0);
    word_t u1 = *(word_t *)(frame + 0x10);
    cl4_result_t r = FUN_00348d94(u2, *(word_t *)(frame + 0x18));
    FUN_00377824(r.lo, r.hi, u1);
    FUN_000a6f88(0);
    long base = *(long *)/* x8+0x40 */0;
    long dst = base + (ulong)(byte)*(uint *)/* table+0x50 */0;
    FUN_0034df04(0);
    ulong sel = (ulong)*(uint *)/* table2+0x50 */0 & 0xff;
    word_t u2b = FUN_00352e90(0);
    if (((sel | /* x9 */0x100000 & 0) == 0) &&
        (ulong)(/* x11 */0) < 0x19) {
        void *pc = 0;
        cl4_result_t a = FUN_0035060c(0);
        ((void (*)(word_t, word_t, word_t))pc)(a.lo, a.hi, u2b);
        cl4_result_t b = FUN_003504f4(0);
        ((void (*)(word_t, word_t, word_t))pc)(b.lo, b.hi, u2b);
        long dst2 = base + sel;
        ((void (*)(word_t, word_t, word_t))0)
            ((dst + (long)/* x25 */0) + dst2 & ~sel,
             (dst + (long)/* x19 */0) + dst2 & ~sel, u1);
    } else {
        0 = 0;
        long r2 = FUN_00358bb4(0);
        /* x25 */0);
        FUN_0036b270(0);
    }
    FUN_00351d30(/* x25 */0);
}

/* FUN_00337d78 @ 0x337d78 (est. sk_syscall_msg_read_f)
 * Message read variant.
 * Confidence: low (indirect jump).
 * Notes: callees FUN_00348d94/377824/34ab20/3507e0/3511b4. */
void sk_syscall_msg_read_f(long p1, long frame)
{
    word_t u1 = *(word_t *)(frame + 0x10);
    word_t w = FUN_00348d94(*(word_t *)(frame + 0x18));
    w = FUN_00377824(w, /* x8 */0, u1);
    FUN_0034ab20(0);
    void *pc = 0;
    ((void (*)(long, word_t))pc)(p1, w);
    long dst = *(long *)/* table+0x40 */0;
    byte sel = *(byte *)/* table+0x50 */0;
    FUN_003507e0(0);
    ((void (*)(void))pc)();
    FUN_003511b4(0);
    ulong sel2 = (ulong)*(byte *)/* table2+0x50 */0;
    ((void (*)(word_t, word_t))0)
        ((dst + p1 + (ulong)sel & ~(ulong)sel) + dst + (ulong)sel2 & ~sel2, u1);
}

/* FUN_00337ef4 @ 0x337ef4 (est. sk_syscall_cap_copy7_18) table+0x18 */
void sk_syscall_cap_copy7_18(word_t p1, word_t p2, long frame)
{
    FUN_00084220(0);
    word_t u2 = FUN_003504d0(0);
    word_t u1 = *(word_t *)(frame + 0x10);
    cl4_result_t r = FUN_00348d94(u2, *(word_t *)(frame + 0x18));
    FUN_00377824(r.lo, r.hi, u1);
    FUN_0034ab20(0);
    void *pc = 0;
    ((void (*)(void))pc)();
    long dst = *(long *)/* table+0x40 */0;
    FUN_0034ccbc(*(und1_t *)/* table+0x50 */0);
    ((void (*)(void))pc)();
    FUN_0034b3c8(0);
    ulong sel = (ulong)*(byte *)/* table2+0x50 */0;
    long addr = dst + sel;
    ((void (*)(word_t, word_t, word_t))0)
        (addr + /* x24 */0 & ~sel, u1);
    FUN_00084234(0);
}

/* FUN_00337fb0 @ 0x337fb0 (est. sk_syscall_cap_copy7_20) table+0x20 */
void sk_syscall_cap_copy7_20(word_t p1, word_t p2, long frame)
{
    FUN_00084220(0);
    word_t u2 = FUN_003504d0(0);
    word_t u1 = *(word_t *)(frame + 0x10);
    cl4_result_t r = FUN_00348d94(u2, *(word_t *)(frame + 0x18));
    FUN_00377824(r.lo, r.hi, u1);
    FUN_0034ab20(0);
    void *pc = 0;
    ((void (*)(void))pc)();
    long dst = *(long *)/* table+0x40 */0;
    FUN_0034ccbc(*(und1_t *)/* table+0x50 */0);
    ((void (*)(void))pc)();
    FUN_0034b3c8(0);
    ulong sel = (ulong)*(byte *)/* table2+0x50 */0;
    long addr = dst + sel;
    ((void (*)(word_t, word_t, word_t))0)
        (addr + /* x24 */0 & ~sel, u1);
    FUN_00084234(0);
}

/* FUN_0033806c @ 0x33806c (est. sk_syscall_cap_copy7_28) table+0x28 */
void sk_syscall_cap_copy7_28(word_t p1, word_t p2, long frame)
{
    FUN_00084220(0);
    word_t u2 = FUN_003504d0(0);
    word_t u1 = *(word_t *)(frame + 0x10);
    cl4_result_t r = FUN_00348d94(u2, *(word_t *)(frame + 0x18));
    FUN_00377824(r.lo, r.hi, u1);
    FUN_0034ab20(0);
    void *pc = 0;
    ((void (*)(void))pc)();
    long dst = *(long *)/* table+0x40 */0;
    FUN_0034ccbc(*(und1_t *)/* table+0x50 */0);
    ((void (*)(void))pc)();
    FUN_0034b3c8(0);
    ulong sel = (ulong)*(byte *)/* table2+0x50 */0;
    long addr = dst + sel;
    ((void (*)(word_t, word_t, word_t))0)
        (addr + /* x24 */0 & ~sel, u1);
    FUN_00084234(0);
}

/* FUN_00338128 @ 0x338128 (est. sk_msg_slot_read_c)
 * Message slot read with size selection.
 * Confidence: medium.
 * Notes: callees FUN_00351a38/348d94/377824/3538d4/35376c/839f8. */
ulong sk_msg_slot_read_c(word_t p1, word_t p2, long frame)
{
    word_t w = FUN_00351a38(0);
    long u = *(long *)(frame + 0x10);
    cl4_result_t r = FUN_00348d94(w, *(word_t *)(frame + 0x18));
    long d = FUN_00377824(r.lo, r.hi, u);
    long dst = *(long *)(d + -8);
    long src = *(long *)(u + -8);
    uint lim1 = *(uint *)(src + 0x54);
    uint lim2 = *(uint *)(dst + 0x54);
    if (lim1 <= lim2) lim1 = lim2;   /* max of the two limits 0 == 0) return 0;
    if (/* w21 */0 - lim1 == 0) goto out;
    long off = (*(long *)(dst + 0x40) + (ulong)*(byte *)(src + 0x50) +
                (*(long *)(dst + 0x40) + (ulong)*(byte *)(dst + 0x50) & ~(ulong)*(byte *)(dst + 0x50)) &
                ~(ulong)*(byte *)(src + 0x50)) + *(long *)(src + 0x40);
    uint p = (uint)off;
    uint sh = p << 3;
    uint v;
    if (p < 4) {
        uint n = ((/* w21 */0 - lim1) + ~(-1 << (sh & 0x1f)) >> (sh & 0x1f)) + 1;
        if (0xff < n) {
            v = (n >> 0x10 == 0) ? (uint)*(ushort *)((long)/* x19 */0 + off);
            goto chk;
        }
        if (1 < n) goto byt;
    } else {
byt:
        v = (uint)*(byte *)((long)/* x19 */0 + off);
chk:
        if (v != 0) {
            uint bit = (p < 4) ? v - 1 << (sh & 0x1f) : 0;
            uint val;
            if (p == 0) {
                val = 0;
            } else {
                FUN_003538d4(0);
                uint e8 = /* w8 */0;
                switch (/* w9 */0; break;
                case 2:  val = (uint)(ushort)0; break;
                case 3:  FUN_0035376c(0); val = /* w9_00 */0; bit = /* w8_00 */0; e13 = /* w13_00 */0; break;
                case 4:  val = 0; break;
                }
                return (ulong)(e13 + (val | bit) + 1);
            }
        }
    }
    if (lim1 == 0) return 0;
out:
    return FUN_000839f8(0);
}

/* FUN_003386dc @ 0x3386dc (est. sk_tcb_lookup_commit)
 * TCB lookup + commit with a fault-address setup (uses &DAT_004effd8).
 * Confidence: low.
 * Notes: callees FUN_0034c7c4/377dcc/354ce4/349e24/377824/354ce4/
 *   371758/34cdf8/3728b8/35884c; string ref DAT_004effd8. */
long sk_tcb_lookup_commit(word_t p1, word_t p2, long code)
{
    FUN_0034c7c4(0);
    FUN_00377dcc(0);
    word_t w = FUN_00354ce4(0).lo;
    if (/* carry clear && !zero */1) {
        long base = *(long *)(code + -8) + 0x40;
        FUN_00349e24(w, *(word_t *)/* x19+0x18 */0);
        FUN_00377824(0x13f);
        FUN_00354ce4(0);
        if (/* carry clear && !zero */1) {
            long f2 = *(long *)(code + -8) + 0x40;
            FUN_00371758(/* stack */0, base);
            cl4_result_t r = FUN_0034cdf8(0);
            code = 4;
            FUN_003728b8(r.lo, r.hi, 4);
            FUN_0035884c(0);
        }
    }
    return code;
}

/* FUN_0033879c @ 0x33879c (est. sk_syscall_msg_write_h)
 * Message write variant with array copy.
 * Confidence: low.
 * Notes: callees FUN_0035193c/349b00/349394/377824/000a6f88/350624/
 *   34dfc4/350630/3592b0/351774. */
void sk_syscall_msg_write_h(word_t p1, word_t p2, long frame)
{
    cl4_result_t r0 = FUN_0035193c(0);
    word_t *buf = (word_t *)r0.lo;
    word_t u2 = *(word_t *)(frame + 0x10);
    FUN_00349b00(buf, *(word_t *)(frame + 0x18));
    long base = *(long *)/* x8+0x40 */0;
    uint sel1 = *(uint *)/* table+0x50 */0;
    ulong s1 = (ulong)sel1 & 0xff;
    ulong dst = base + (ulong)(byte)sel1;
    word_t *pd = (word_t *)(dst & ~s1);
    cl4_result_t r = FUN_00349394(0);
    FUN_00377824(r.lo, r.hi, u2);
    word_t w = FUN_000a6f88(0);
    uint sel2 = *(uint *)/* table2+0x50 */0;
    ulong s2 = (ulong)sel2 & 0xff;
    if (((s2 | s1) < 8 && ((sel2 | sel1) & 0x100000) == 0) &&
        0xffffffffffffffe6 <
        ((-(ulong)(byte)sel1 - 10 | s1) - base) -
        (*(long *)/* x8_00+0x40 */0 + (s1 | 7) +
         (base + (ulong)(byte)sel2 + (long)pd & ~s2) & ~(s1 | 7))) {
        ulong m = ~s1;
        void *pc = 0;
        FUN_00350624(buf);
        ((void (*)(void))pc)();
        FUN_0034dfc4(0);
        cl4_result_t a = ((cl4_result_t (*)(void))0)();
        FUN_00350630(*(word_t *)/* table2+0x10 */0, a.lo, a.hi, w);
        ((void (*)(void))0)();
        word_t *src1 = (word_t *)(/* x12 */0 + 7 + ((dst + (long)buf & m) + base + s2 & ~s2) & 0xfffffffffffffff8);
        word_t *src2 = (word_t *)(/* x12 */0 + 7 + ((dst + (long)r0.hi & m) + base + s2 & ~s2) & 0xfffffffffffffff8);
        und1_t b = *(und1_t *)(src2 + 1);
        *src1 = *src2;
        *(und1_t *)(src1 + 1) = b;
        ((void (*)(word_t, word_t, word_t))0)(s1 + 9 + (long)src1 & m, s1 + 9 + (long)src2 & m, u2);
    } else {
        *buf = *r0.hi_word;
        FUN_003592b0(0);
        buf = pd;
    }
    FUN_00351774((word_t)buf, /* x30 */0);
}

/* FUN_0033898c @ 0x33898c (est. sk_dispatch8_10) table+0x10 */
void sk_dispatch8_10(void)
{
    FUN_0008e518(0);
    FUN_00349ae0(0);
    void *pc = 0;
    ((void (*)(void))pc)();
    long dst = *(long *)/* table+0x40 */0;
    FUN_0034cc5c(0);
    word_t w = ((word_t (*)(void))pc)();
    FUN_00349394(w, *(word_t *)/* x22+0x18 */0);
    FUN_00377824(0);
    FUN_00349530(0);
    ulong sel = (ulong)*(byte *)/* table2+0x50 */0;
    long addr = dst + sel;
    ((void (*)(word_t, word_t))0)(addr + /* x24 */0 & ~sel);
    FUN_0034a708(*(word_t *)/* table2+0x40 */0);
    ((void (*)(void))pc)();
    FUN_0008e500(0);
}

/* FUN_00338a54 @ 0x338a54 (est. sk_dispatch8_18) table+0x18 */
void sk_dispatch8_18(void)
{
    FUN_0008e518(0);
    FUN_00349ae0(0);
    void *pc = 0;
    ((void (*)(void))pc)();
    long dst = *(long *)/* table+0x40 */0;
    FUN_0034cc5c(0);
    word_t w = ((word_t (*)(void))pc)();
    FUN_00349394(w, *(word_t *)/* x22+0x18 */0);
    FUN_00377824(0);
    FUN_00349530(0);
    ulong sel = (ulong)*(byte *)/* table2+0x50 */0;
    long addr = dst + sel;
    ((void (*)(word_t, word_t))0)(addr + /* x24 */0 & ~sel);
    FUN_0034a708(*(word_t *)/* table2+0x40 */0);
    ((void (*)(void))pc)();
    FUN_0008e500(0);
}

/* FUN_00338b1c @ 0x338b1c (est. sk_dispatch8_20) table+0x20 */
void sk_dispatch8_20(void)
{
    FUN_0008e518(0);
    FUN_00349ae0(0);
    void *pc = 0;
    ((void (*)(void))pc)();
    long dst = *(long *)/* table+0x40 */0;
    FUN_0034cc5c(0);
    word_t w = ((word_t (*)(void))pc)();
    FUN_00349394(w, *(word_t *)/* x22+0x18 */0);
    FUN_00377824(0);
    FUN_00349530(0);
    ulong sel = (ulong)*(byte *)/* table2+0x50 */0;
    long addr = dst + sel;
    ((void (*)(word_t, word_t))0)(addr + /* x24 */0 & ~sel);
    FUN_0034a708(*(word_t *)/* table2+0x40 */0);
    ((void (*)(void))pc)();
    FUN_0008e500(0);
}

/* FUN_00338be4 @ 0x338be4 (est. sk_dispatch8_28) table+0x28 */
void sk_dispatch8_28(void)
{
    FUN_0008e518(0);
    FUN_00349ae0(0);
    void *pc = 0;
    ((void (*)(void))pc)();
    long dst = *(long *)/* table+0x40 */0;
    FUN_0034cc5c(0);
    word_t w = ((word_t (*)(void))pc)();
    FUN_00349394(w, *(word_t *)/* x22+0x18 */0);
    FUN_00377824(0);
    FUN_00349530(0);
    ulong sel = (ulong)*(byte *)/* table2+0x50 */0;
    long addr = dst + sel;
    ((void (*)(word_t, word_t))0)(addr + /* x24 */0 & ~sel);
    FUN_0034a708(*(word_t *)/* table2+0x40 */0);
    ((void (*)(void))pc)();
    FUN_0008e500(0);
}

/* FUN_00338cac @ 0x338cac (est. sk_msg_slot_read_d)
 * Message slot read with size selection.
 * Confidence: medium.
 * Notes: callees FUN_00084220/350d74/349394/377824/34cb60/353af8/
 *   35a4a8/35a464/34e32c/351538/35660c/34bf1c/84234/839f8. */
void sk_msg_slot_read_d(void)
{
    FUN_00084220(0);
    FUN_00350d74(0);
    uint limit = *(uint *)/* table+0x54 */0;
    FUN_00349394(0);
    FUN_00377824(0);
    FUN_0034cb60(0);
    cl4_result_t r = FUN_00353af8(0);
    word_t cnt = r.hi;
    if (/* w22 */0 <= /* w10 */0) goto out;
        FUN_0035a4a8(/* x11 */0, r.lo, cnt, r.lo);
        long off = (/* x12_00 */0) + /* x11_00 */0 | 7) + /* x13 */0 & ~(/* x12_00 */0 | 7));
        uint p = (uint)off << 3;
        uint v;
        if ((uint)off < 4) {
            uint n = ((uint)(/* w15 */0 + ~(-1 << (p & 0x1f))) >> (p & 0x1f)) + 1;
            if (0xff < n) {
                v = (n >> 0x10 == 0) ? (uint)*(ushort *)(/* x19 */0 + off);
                goto chk;
            }
            if (1 < n) goto byt;
        } else {
byt:
            v = (uint)*(byte *)(/* x19 */0 + off);
chk:
            if (v != 0) {
                FUN_0035a464(0);
                if (/* w13 */0 != 0) {
                    uint sel = 4;
                    if (/* w13 */0;
                    switch (sel) { default: case 2: case 3: FUN_0034e32c(0); case 4: break; }
                }
                cnt = FUN_00351538(0);
                goto done;
            }
        }
        cnt = /* x1 */0;
        if (/* w10_00 */0 != 0) {
out:
            if (limit < (uint)cnt) FUN_0035660c(0);
            else FUN_0034bf1c(0);
            FUN_00084234(0);
            FUN_000839f8(0);
            return;
        }
    }
    cnt = 0;
done:
    FUN_00084234(cnt, /* x30 */0);
}

/* FUN_003390c4 @ 0x3390c4 (est. sk_tcb_lookup_commit_b)
 * TCB lookup + commit (like 0x3386dc, error code 5, uses DAT_004eed48).
 * Confidence: low.
 * Notes: callees FUN_0034c7c4/377dcc/354ce4/349e24/377824/354ce4/
 *   371758/34cdf8/3728b8/35884c; DAT_004effd8, DAT_004eed48. */
long sk_tcb_lookup_commit_b(word_t p1, word_t p2, long code)
{
    FUN_0034c7c4(0);
    FUN_00377dcc(0);
    word_t w = FUN_00354ce4(0).lo;
    if (/* carry clear && !zero */1) {
        long base = *(long *)(code + -8) + 0x40;
        FUN_00349e24(w, *(word_t *)/* x19+0x18 */0);
        FUN_00377824(0x13f);
        FUN_00354ce4(0);
        if (/* carry clear && !zero */1) {
            long f2 = *(long *)(code + -8) + 0x40;
            FUN_00371758(/* stack */0, base);
            code = 5;
            FUN_003728b8(/* r */0, 5);
            FUN_0035884c(0);
        }
    }
    return code;
}

/* FUN_0033918c @ 0x33918c (est. sk_syscall_msg_write_i)
 * Message write variant with copy (like 0x33879c).
 * Confidence: low.
 * Notes: callees FUN_0035193c/349b00/349394/377824/000a6f88/350bb4/
 *   350630/3592b0/351774. */
void sk_syscall_msg_write_i(word_t p1, word_t p2, long frame)
{
    cl4_result_t r0 = FUN_0035193c(0);
    word_t *buf = (word_t *)r0.lo;
    word_t u8 = *(word_t *)(frame + 0x10);
    FUN_00349b00(buf, *(word_t *)(frame + 0x18));
    long base = *(long *)/* x8+0x40 */0;
    uint sel1 = *(uint *)/* table+0x50 */0;
    ulong s1 = (ulong)sel1 & 0xff;
    ulong dst = base + (ulong)(byte)sel1;
    cl4_result_t r = FUN_00349394(0);
    FUN_00377824(r.lo, r.hi, u8);
    word_t w = FUN_000a6f88(0);
    uint sel2 = *(uint *)/* table2+0x50 */0;
    ulong s2 = (ulong)sel2 & 0xff;
    long base2 = *(long *)/* x8_00+0x40 */0;
    ulong dst2 = s1 + 9;
    long d3 = (dst2 & ~s1) + base;
    if (((s2 | s1) < 8 && ((sel2 | sel1) & 0x100000) == 0) &&
        d3 + (base2 + (s1 | 7) +
              (base + (ulong)(byte)sel2 + (dst & ~s1) & ~s2) & ~(s1 | 7)) + 1 < 0x19) {
        ulong m = ~s1;
        void *pc = 0;
        FUN_00350bb4(buf);
        cl4_result_t a = ((cl4_result_t (*)(void))pc)();
        FUN_00350630(a.lo, a.hi, u8);
        ((void (*)(void))pc)();
        cl4_result_t b = FUN_00350630(*(word_t *)/* table2+0x10 */0);
        ((void (*)(word_t, word_t, word_t))0)(b.lo, b.hi, w);
        long o2 = base2 + 7;
        word_t *s1p = (word_t *)(o2 + ((dst + (long)r0.hi & m) + base + s2 & ~s2) & 0xfffffffffffffff8);
        und1_t bb = *(und1_t *)(s1p + 1);
        word_t *s2p = (word_t *)(o2 + ((dst + (long)buf & m) + base + s2 & ~s2) & 0xfffffffffffffff8);
        *s2p = *s1p;
        *(und1_t *)(s2p + 1) = bb;
        ((void (*)(word_t, word_t, word_t))pc)((long)dst2 + (long)s2p & m, (long)dst2 + (long)s1p & m, u8);
        *(und1_t *)((long)s2p + d3) = *(und1_t *)((long)s1p + d3);
    } else {
        *buf = *r0.hi_word;
        FUN_003592b0(0);
        buf = (word_t *)dst2;
    }
    FUN_00351774((word_t)buf, /* x30 */0);
}

/* FUN_00339378 @ 0x339378 (est. sk_syscall_msg_read_g)
 * Message read variant.
 * Confidence: low (indirect jump).
 * Notes: callees FUN_00357cb4/35098c/34b3e8/84180/349394/377824/
 *   841a0/357c74. */
void sk_syscall_msg_read_g(void)
{
    FUN_00357cb4(0);
    FUN_0035098c(0);
    word_t u3 = *(word_t *)/* x1+0x10 */0;
    FUN_0034b3e8(0);
    void *jt = 0;
    ((void (*)(void))jt)();
    long dst = *(long *)/* table+0x40 */0;
    ulong sel = (ulong)*(byte *)/* table+0x50 */0;
    FUN_00084180(0);
    word_t w = ((word_t (*)(void))jt)();
    cl4_result_t r = FUN_00349394(w, *(word_t *)/* x20+0x18 */0);
    FUN_00377824(r.lo, r.hi, u3);
    FUN_000841a0(0);
    ulong sel2 = (ulong)*(byte *)/* table2+0x50 */0;
    ulong addr = (dst + /* x21 */0 + sel & ~sel) + dst + sel2 & ~sel2;
    ((void (*)(ulong))0)(addr);
    FUN_00357c74(sel + (*(long *)/* table2+0x40 0, /* x30 */0);
    ((void (*)(void))jt)();   /* indirect jump */
}

/* FUN_00339544 @ 0x339544 (est. sk_dispatch9_18) table+0x18 */
void sk_dispatch9_18(void)
{
    FUN_0008e518(0);
    FUN_00349ae0(0);
    void *pc = 0;
    ((void (*)(void))pc)();
    long dst = *(long *)/* table+0x40 */0;
    FUN_0034cc38(0);
    word_t w = ((word_t (*)(void))pc)();
    FUN_00349394(w, *(word_t *)/* x22+0x18 */0);
    FUN_00377824(0);
    FUN_00349530(0);
    ulong sel = (ulong)*(byte *)/* table2+0x50 */0;
    long addr = dst + sel;
    ((void (*)(word_t, word_t))0)(addr + /* x24 */0 & ~sel);
    FUN_0034a6c4(*(word_t *)/* table2+0x40 */0);
    ((void (*)(void))pc)();
    word_t w2 = FUN_0034f8f4(0);
    FUN_0008e500(w2, /* x30 */0);
}

/* FUN_0033960c @ 0x33960c (est. sk_dispatch9_20) table+0x20 */
void sk_dispatch9_20(void)
{
    FUN_0008e518(0);
    FUN_00349ae0(0);
    void *pc = 0;
    ((void (*)(void))pc)();
    long dst = *(long *)/* table+0x40 */0;
    FUN_0034cc38(0);
    word_t w = ((word_t (*)(void))pc)();
    FUN_00349394(w, *(word_t *)/* x22+0x18 */0);
    FUN_00377824(0);
    FUN_00349530(0);
    ulong sel = (ulong)*(byte *)/* table2+0x50 */0;
    long addr = dst + sel;
    ((void (*)(word_t, word_t))0)(addr + /* x24 */0 & ~sel);
    FUN_0034a6c4(*(word_t *)/* table2+0x40 */0);
    ((void (*)(void))pc)();
    word_t w2 = FUN_0034f8f4(0);
    FUN_0008e500(w2, /* x30 */0);
}

/* FUN_003396d4 @ 0x3396d4 (est. sk_dispatch9_28) table+0x28 */
void sk_dispatch9_28(void)
{
    FUN_0008e518(0);
    FUN_00349ae0(0);
    void *pc = 0;
    ((void (*)(void))pc)();
    long dst = *(long *)/* table+0x40 */0;
    FUN_0034cc38(0);
    word_t w = ((word_t (*)(void))pc)();
    FUN_00349394(w, *(word_t *)/* x22+0x18 */0);
    FUN_00377824(0);
    FUN_00349530(0);
    ulong sel = (ulong)*(byte *)/* table2+0x50 */0;
    long addr = dst + sel;
    ((void (*)(word_t, word_t))0)(addr + /* x24 */0 & ~sel);
    FUN_0034a6c4(*(word_t *)/* table2+0x40 */0);
    ((void (*)(void))pc)();
    word_t w2 = FUN_0034f8f4(0);
    FUN_0008e500(w2, /* x30 */0);
}

/* FUN_0033979c @ 0x33979c (est. sk_msg_slot_read_e)
 * Message slot read with size selection and bookkeeping.
 * Confidence: medium.
 * Notes: callees FUN_00084220/350d74/349394/377824/34c11c/3559c8/
 *   352e90/34bf1c/34e32c/84234/839f8. */
void sk_msg_slot_read_e(void)
{
    FUN_00084220(0);
    FUN_00350d74(0);
    uint limit = *(uint *)/* table+0x54 */0;
    FUN_00349394(0);
    FUN_00377824(0);
    FUN_0034c11c(0);
    FUN_003559c8(0);
    cl4_result_t r = FUN_00352e90(0);
    int res;
    if (/* w22 */0 == 0) {
        res = 0;
    } else {
        ulong mask = /* x14 */0 | 7;
        long o2 = mask + *(long *)/* table2+0x40 */0;
        long o3 = (/* x14 */0) + /* x11 */0;
        uint diff = /* w22 */0;
        if (/* w22 */0 || diff == 0) {
            if (limit == /* w10 */0) {
                FUN_0034bf1c(diff, r.hi, r.lo);
                FUN_00084234(0);
                FUN_000839f8(0);
                return;
            }
            if (r.hi == /* w10 */0) goto finish;
            uint b = (uint)*(byte *)((o2 + ((ulong)(/* x11 */0 + (long)/* x19 */0) + /* x11 */0 & ~/* x9 */0) & ~mask) + o3);
            if (b < 2) { res = 0; goto out; }
            b = b + 0x7ffffffe & 0x7fffffff;
        } else {
            long off = o3 + (o2 + (/* x11 */0 + (/* x11 */0 & ~/* x14 */0) & ~mask) + 1;
            uint p = (uint)off;
            uint sh = p << 3;
            uint v;
            if (p < 4) {
                uint n = (diff + ~(-1 << (sh & 0x1f)) >> (sh & 0x1f)) + 1;
                if (n < 0x100) {
                    if (n < 2) { goto fault2; }
                    v = (uint)*(byte *)((long)/* x19 */0 + off);
                } else {
                    v = (n >> 0x10 == 0) ? (uint)*(ushort *)((long)/* x19 */0 + off);
                }
            } else {
                v = (uint)*(byte *)((long)/* x19 */0 + off);
            }
            uint bit = 0;
            if (v == 0) goto fault2;
            bit = (p < 4) ? v - 1 << (sh & 0x1f) : 0;
            uint vv = /* w10 */0;
            uint val;
            if (p == 0) {
                val = 0;
            } else {
                val = 4;
                if (p < 4) val = p;
                switch (val) {
                default: val = (uint)(byte)0; break;
                case 2:  val = (uint)(ushort)0; break;
                case 3:  FUN_0034e32c(0); bit = /* w8 */0; val = /* w9 */0; vv = /* w10_00 */0; break;
                case 4:  val = 0; break;
                }
            }
            vv = vv + (val | bit);
            res = vv + 1;
            goto out;
        }
fault2:
        if (limit == /* w10 */0) { FUN_0034bf1c(0); FUN_00084234(0); FUN_000839f8(0); return; }
        if (r.hi != /* w10 */0) {
            /* read byte at computed addr; treat as count 0 + /* off */0);
            if (b >= 2) { res = (int)(b + 0x7ffffffe & 0x7fffffff); goto out; }
        }
        res = 0;
    }
finish:
    res = 0;
out:
    FUN_00084234(res, /* x30 */0);
}
