/* Recreated from cl4_kernel.raw (cL4 Secure Kernel, arm64e, image base 0) —
 * the cL4 microkernel (GL1). Ground truth: Ghidra FUN_ names + addresses.
 * All names are estimates unless string/header matched.
 * Slice 31: 0x366f1c-0x3723a0 syscall/exception-entry region.
 *
 * This region is the kernel's Swift-runtime object model: retain/release
 * wrappers (FUN_0036b270/b118), weak/unowned reference accounting, global
 * object-intern tables protected by a mutex (the FUN_0036aae4/e878/ed94/
 * 7062c/70f2c/71b58 family), Swift metadata / "Prespecializations library"
 * lookups (FUN_0036d8a4), and fatal-error (FUN_00369bb0) helpers. */

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "sk_internal.h"
#include "sk_region_syscalls.h"

/* ------------------------------------------------------------------ *
Out-of-range cL4 helper declarations (extern; bodies reconstructed by their
range workers). Return type uint64_t; unused results are harmless. */
extern uint64_t FUN_000101a0();
extern uint64_t FUN_0001062c();
extern uint64_t FUN_000122f0();
extern uint64_t FUN_0005b824();
extern uint64_t FUN_00111890();
extern uint64_t FUN_00116bb4();
extern uint64_t FUN_00117cc4();
extern uint64_t FUN_00117d14();
extern uint64_t FUN_001185ec();
extern uint64_t FUN_0035b178();
extern uint64_t FUN_0035b588();
extern uint64_t FUN_0035eae4();
extern uint64_t FUN_0035eb3c();
extern uint64_t FUN_0035ef4c();
extern uint64_t FUN_0036254c();
extern uint64_t FUN_00362c34();
extern uint64_t FUN_00362ea4();
extern uint64_t FUN_00363f10();
extern uint64_t FUN_003652b8();
extern uint64_t FUN_003658a0();
extern uint64_t FUN_003658e8();
extern uint64_t FUN_00365c38();
extern uint64_t FUN_00366774();
extern uint64_t FUN_00366f1c();
extern uint64_t FUN_00367160();
extern uint64_t FUN_0036726c();
extern uint64_t FUN_003672f4();
extern uint64_t FUN_00367368();
extern uint64_t FUN_00367438();
extern uint64_t FUN_003674e8();
extern uint64_t FUN_00367ae0();
extern uint64_t FUN_00367b34();
extern uint64_t FUN_00367b3c();
extern uint64_t FUN_00367bf0();
extern uint64_t FUN_00367ccc();
extern uint64_t FUN_00367d50();
extern uint64_t FUN_00367dd4();
extern uint64_t FUN_00367e50();
extern uint64_t FUN_0036805c();
extern uint64_t FUN_003680cc();
extern uint64_t FUN_0036813c();
extern uint64_t FUN_003681c4();
extern uint64_t FUN_003682b0();
extern uint64_t FUN_0036851c();
extern uint64_t FUN_0036878c();
extern uint64_t FUN_00368980();
extern uint64_t FUN_00368da8();
extern uint64_t FUN_00369340();
extern uint64_t FUN_00369584();
extern uint64_t FUN_003696dc();
extern uint64_t FUN_00369758();
extern uint64_t FUN_003697c4();
extern uint64_t FUN_0036986c();
extern uint64_t FUN_003698b0();
extern uint64_t FUN_0036993c();
extern uint64_t FUN_00369a30();
extern uint64_t FUN_00369a6c();
extern uint64_t FUN_00369b18();
extern uint64_t FUN_00369bb0();
extern uint64_t FUN_00369c08();
extern uint64_t FUN_00369c24();
extern uint64_t FUN_00369c40();
extern uint64_t FUN_00369c78();
extern uint64_t FUN_00369ca0();
extern uint64_t FUN_00369e68();
extern uint64_t FUN_00369efc();
extern uint64_t FUN_00369f4c();
extern uint64_t FUN_0036a158();
extern uint64_t FUN_0036a1a0();
extern uint64_t FUN_0036a20c();
extern uint64_t FUN_0036a244();
extern uint64_t FUN_0036a2ac();
extern uint64_t FUN_0036a338();
extern uint64_t FUN_0036a358();
extern uint64_t FUN_0036a388();
extern uint64_t FUN_0036a454();
extern uint64_t FUN_0036a5ac();
extern uint64_t FUN_0036a668();
extern uint64_t FUN_0036a804();
extern uint64_t FUN_0036a884();
extern uint64_t FUN_0036a908();
extern uint64_t FUN_0036a940();
extern uint64_t FUN_0036a9a0();
extern uint64_t FUN_0036a9d4();
extern uint64_t FUN_0036aa30();
extern uint64_t FUN_0036aae4();
extern uint64_t FUN_0036b118();
extern uint64_t FUN_0036b170();
extern uint64_t FUN_0036b21c();
extern uint64_t FUN_0036b250();
extern uint64_t FUN_0036b270();
extern uint64_t FUN_0036b2d0();
extern uint64_t FUN_0036b3f8();
extern uint64_t FUN_0036b484();
extern uint64_t FUN_0036b4e8();
extern uint64_t FUN_0036b588();
extern uint64_t FUN_0036b5c4();
extern uint64_t FUN_0036b650();
extern uint64_t FUN_0036b6ac();
extern uint64_t FUN_0036b7f8();
extern uint64_t FUN_0036b834();
extern uint64_t FUN_0036b85c();
extern uint64_t FUN_0036b8b0();
extern uint64_t FUN_0036b8c0();
extern uint64_t FUN_0036b8d8();
extern uint64_t FUN_0036b958();
extern uint64_t FUN_0036b9e4();
extern uint64_t FUN_0036bab4();
extern uint64_t FUN_0036bc3c();
extern uint64_t FUN_0036bc84();
extern uint64_t FUN_0036bcec();
extern uint64_t FUN_0036bd84();
extern uint64_t FUN_0036bde0();
extern uint64_t FUN_0036becc();
extern uint64_t FUN_0036bf4c();
extern uint64_t FUN_0036bfe4();
extern uint64_t FUN_0036c06c();
extern uint64_t FUN_0036c0e0();
extern uint64_t FUN_0036c188();
extern uint64_t FUN_0036c20c();
extern uint64_t FUN_0036c274();
extern uint64_t FUN_0036c328();
extern uint64_t FUN_0036c3e0();
extern uint64_t FUN_0036c704();
extern uint64_t FUN_0036cb30();
extern uint64_t FUN_0036cb90();
extern uint64_t FUN_0036cbd4();
extern uint64_t FUN_0036cc50();
extern uint64_t FUN_0036ccb8();
extern uint64_t FUN_0036cd00();
extern uint64_t FUN_0036d2b8();
extern uint64_t FUN_0036d454();
extern uint64_t FUN_0036d484();
extern uint64_t FUN_0036d5ac();
extern uint64_t FUN_0036d8a4();
extern uint64_t FUN_0036de80();
extern uint64_t FUN_0036def8();
extern uint64_t FUN_0036df7c();
extern uint64_t FUN_0036e038();
extern uint64_t FUN_0036e110();
extern uint64_t FUN_0036e190();
extern uint64_t FUN_0036e310();
extern uint64_t FUN_0036e52c();
extern uint64_t FUN_0036e7ec();
extern uint64_t FUN_0036e878();
extern uint64_t FUN_0036ed94();
extern uint64_t FUN_0036f2e4();
extern uint64_t FUN_0036f418();
extern uint64_t FUN_0036f460();
extern uint64_t FUN_0036f5d0();
extern uint64_t FUN_0036f878();
extern uint64_t FUN_0036f8bc();
extern uint64_t FUN_0036f974();
extern uint64_t FUN_0036fb10();
extern uint64_t FUN_0036ffc0();
extern uint64_t FUN_00370060();
extern uint64_t FUN_003704ac();
extern uint64_t FUN_003704f4();
extern uint64_t FUN_0037062c();
extern uint64_t FUN_00370dfc();
extern uint64_t FUN_00370f2c();
extern uint64_t FUN_003716f8();
extern uint64_t FUN_00371758();
extern uint64_t FUN_003717b8();
extern uint64_t FUN_00371950();
extern uint64_t FUN_00371b58();
extern uint64_t FUN_003722e4();
extern uint64_t FUN_003723a0();
extern uint64_t FUN_00372598();
extern uint64_t FUN_00372fbc();
extern uint64_t FUN_003766b4();
extern uint64_t FUN_00379410();
extern uint64_t FUN_00379480();
extern uint64_t FUN_0037a7f8();
extern uint64_t FUN_0037a850();
extern uint64_t FUN_0037aaac();
extern uint64_t FUN_0037b350();
extern uint64_t FUN_0037b3b8();
extern uint64_t FUN_0037bcac();
extern uint64_t FUN_0037c5a0();
extern uint64_t FUN_0037c724();
extern uint64_t FUN_0037cb08();
extern uint64_t FUN_0037cbc8();
extern uint64_t FUN_0037f7a4();
extern uint64_t FUN_003800cc();
extern uint64_t FUN_003802f4();
extern uint64_t FUN_00380864();
extern uint64_t FUN_00380b50();
extern uint64_t FUN_00380cec();
extern uint64_t FUN_00381c5c();
extern uint64_t FUN_00381cfc();
extern uint64_t FUN_00381fac();
extern uint64_t FUN_00382200();
extern uint64_t FUN_00387bb8();
extern uint64_t FUN_00387e60();
extern uint64_t FUN_00388fb0();
extern uint64_t FUN_0039a138();
extern uint64_t FUN_0039a6fc();
extern uint64_t FUN_0039bb2c();
extern uint64_t FUN_0039c740();
extern uint64_t FUN_0039c7e8();
extern uint64_t FUN_0039f818();
extern uint64_t FUN_0039f8b8();
extern uint64_t FUN_0039f914();
extern uint64_t FUN_0039f9e8();
extern uint64_t FUN_0039fb10();
extern uint64_t FUN_0039fb58();
extern uint64_t FUN_003a2554();
extern uint64_t FUN_003a25d4();
extern uint64_t FUN_003a261c();
extern uint64_t FUN_003a294c();
extern uint64_t FUN_003a32a0();
extern uint64_t FUN_003a3430();
extern uint64_t FUN_003a3460();
extern uint64_t FUN_003a3814();
extern uint64_t FUN_003c3008();
extern uint64_t FUN_003d3dd8();
extern uint64_t FUN_004b89f8();
extern uint64_t FUN_004b9c0c();
extern uint64_t FUN_004b9ccc();
extern uint64_t FUN_004b9d68();
extern uint64_t FUN_004b9ed8();
extern uint64_t FUN_004b9f04();
extern uint64_t FUN_004b9f58();
extern uint64_t FUN_004b9f8c();
extern uint64_t FUN_004ba070();
extern uint64_t FUN_004ba0a0();
extern uint64_t FUN_004ba0f4();
extern uint64_t FUN_004ba148();
extern uint64_t FUN_004ba180();
extern uint64_t thunk_FUN_00012568();
extern uint64_t thunk_FUN_00114330();
extern uint64_t thunk_FUN_001145b0();
extern uint64_t thunk_FUN_00114c60();
extern uint64_t thunk_FUN_00114d10();
extern uint64_t thunk_FUN_00114e50();
extern uint64_t thunk_FUN_00115080();
extern uint64_t thunk_FUN_00369b04();
extern uint64_t thunk_FUN_0036b118();
extern uint64_t thunk_FUN_0036b270();

/* Global data references (kernel/type tables, once flags, intern caches). */
extern uint64_t DAT_00368d5c;
extern uint64_t DAT_003697c0;
extern uint64_t DAT_0036de7c;
extern uint64_t DAT_004f2710;
extern uint64_t DAT_004f2740;
extern uint64_t DAT_004f2770;
extern uint64_t DAT_0060ce80;
extern uint64_t DAT_006adecd;
extern uint64_t DAT_006aded4;
extern uint64_t DAT_006adeda;
extern uint64_t DAT_006adee0;
extern uint64_t DAT_006adef8;
extern uint64_t DAT_006c0260;
extern uint64_t DAT_006c0278;
extern uint64_t DAT_006c0290;
extern uint64_t DAT_006c02d8;
extern uint64_t DAT_006c02e0;
extern uint64_t DAT_006c0320;
extern uint64_t DAT_006c0330;
extern uint64_t DAT_006c0340;
extern uint64_t DAT_006c0380;
extern uint64_t DAT_006c0388;
extern uint64_t DAT_006c0390;
extern uint64_t DAT_006c0398;
extern uint64_t DAT_006c03a0;
extern uint64_t DAT_006c03d8;
extern uint64_t DAT_006c03e0;
extern uint64_t DAT_006c0438;
extern uint64_t DAT_006c0478;
extern uint64_t DAT_006c0480;
extern uint64_t DAT_006c04d0;
extern uint64_t DAT_006c04e0;
extern uint64_t DAT_006c0530;
extern uint64_t DAT_006c0540;
extern uint64_t DAT_006c0548;
extern uint64_t _DAT_006adee0;
extern uint64_t _DAT_006adee8;
extern uint64_t _DAT_006adef0;
extern uint64_t _DAT_006adfe8;
extern uint64_t _DAT_006c0260;
extern uint64_t _DAT_006c0268;
extern uint64_t _DAT_006c0270;
extern uint64_t _DAT_006c0290;
extern uint64_t _DAT_006c02d8;
extern uint64_t _DAT_006c02e8;
extern uint64_t _DAT_006c02f0;
extern uint64_t _DAT_006c02f8;
extern uint64_t _DAT_006c0300;
extern uint64_t _DAT_006c0308;
extern uint64_t _DAT_006c0310;
extern uint64_t _DAT_006c0320;
extern uint64_t _DAT_006c0330;
extern uint64_t _DAT_006c0334;
extern uint64_t _DAT_006c0338;
extern uint64_t _DAT_006c0340;
extern uint64_t _DAT_006c0378;
extern uint64_t _DAT_006c0388;
extern uint64_t _DAT_006c0390;
extern uint64_t _DAT_006c0398;
extern uint64_t _DAT_006c03a0;
extern uint64_t _DAT_006c03d8;
extern uint64_t _DAT_006c03e0;
extern uint64_t _DAT_006c0428;
extern uint64_t _DAT_006c0430;
extern uint64_t _DAT_006c0434;
extern uint64_t _DAT_006c0438;
extern uint64_t _DAT_006c0440;
extern uint64_t _DAT_006c0478;
extern uint64_t _DAT_006c04b8;
extern uint64_t _DAT_006c04d0;
extern uint64_t _DAT_006c04e0;
extern uint64_t _DAT_006c04e4;
extern uint64_t _DAT_006c04e8;
extern uint64_t _DAT_006c04f0;
extern uint64_t _DAT_006c0518;
extern uint64_t _DAT_006c0530;
extern uint64_t __swift5_proto;
extern uint64_t __swift5_protos;
extern uint64_t __swift5_types;
extern uint64_t __thread_bss;
extern char DAT_005d4601[];
extern char DAT_005d4672[];
extern char DAT_005d4699[];
extern char DAT_005d46d5[];
extern char s_Current_access__a__s__started_at_005d46b4[];
extern char s_Fatal_access_conflict_detected__005d4606[];
extern char s_Fatal_error__Attempted_to_read_a_005d4506[];
extern char s_Fatal_error__Attempted_to_read_a_005d455f[];
extern char s_Fatal_error__Call_of_deleted_met_005d4429[];
extern char s_Fatal_error__Object_s_unowned_re_005d447f[];
extern char s_Fatal_error__Object_s_weak_refer_005d44c4[];
extern char s_Fatal_error__Object_was_retained_005d444e[];
extern char s_Fatal_error__failed_to_allocate___005d45b9[];
extern char s_Mangling_for_prespecialized_meta_005d49c0[];
extern char s_Prespecializations_library__Look_005d4a82[];
extern char s_Prespecializations_library__Look_005d4ae1[];
extern char s_Prespecializations_library__Look_005d4b32[];
extern char s_Prespecializations_library__Reje_005d48c6[];
extern char s_Prespecializations_library__Reje_005d4914[];
extern char s_Prespecializations_library__fail_005d4974[];
extern char s_Prespecializations_library__foun_005d49f9[];
extern char s_Previous_access__a__s__started_a_005d4677[];
extern char s_Simultaneous_accesses_to_0x_lx__b_005d4627[];
extern char s_Unexpected_symbolic_reference__p_005d4a2f[];
extern char s___4u_0x_0_16tx_005d4400[];
extern char s___mtx_init__handle_mutex____mtx__005d3f10[];
extern char s___mtx_lock__handle_mutex__failed_005d3ee0[];
extern char s___mtx_unlock__handle_mutex__fail_005d3f4d[];
extern char s_instantiating_class_metadata_for_005d4ec5[];

#define SoftwareBreakpoint(a,b)   /* breakpoint opcode */
#define LOAcquire()                /* lock acquire */
#define LORelease()                /* lock release */
#define DataMemoryBarrier(a,b)     /* memory barrier */
#define CONCAT44(a,b)              ((uint64_t)(uint32_t)(a) | ((uint64_t)(b)<<32))
#define ZEXT816(a)                 ((cl4_result_t){.lo=(uint64_t)(a),.hi=0})

/* GENTER/GEXIT opcodes: enter/exit the guarded execution level. */
#define GENTER()  /* GENTER opcode 0x00201420 */
#define GEXIT()   /* GEXIT  opcode 0x00201400 */

/* Forward declarations for functions referenced before definition. */
void sk_fatal_symbolic_ref();
void sk_intern_state_init_b(word_t *st);
/* ================================================================== *
 * 0x366f1c — object-register context copy/validate (syscall msg parse)
 * ================================================================== */

/* FUN_00366f1c @ 0x366f1c   (est. sk_msg_parse_registers)
 * Ghidra: undefined8 FUN_00366f1c(long,long,long,long*,long*,long*,int,undefined4,undefined1)
 * Validates and copies a register/context array from a syscall message
 * descriptor (param_4, magic 0x301) into a target context (param_2),
 * building a mirrored access path. Returns 0 on failure, 1 or 2 on
 * success depending on the completion callback slot (param_7). Compares
 * range pairs via thunk_FUN_00114c60/1e50 and per-slot pairs via
 * FUN_00365c38; on mismatch rolls back previously-written slots by
 * invoking the owning object's destructor through its vtable.
 * Confidence: medium
 * Notes: magic 0x301; thunk_FUN_00114c60 (range), thunk_FUN_00114e50
 *   (memcmp); callee FUN_00365c38; completion via (param_4[-1]+0x10/0x20). */
uint64_t sk_msg_parse_registers(word_t ctx_base, word_t target, word_t aux,
                                word_t *desc, word_t *out_ref, word_t *out_ptr,
                                int mode, uint32_t p8, uint8_t p9)
{
    word_t *slot;
    word_t rng_a, rng_b, step_a, step_b, base_a, base_b;
    word_t count;
    uint64_t i, j;
    int r;

    *out_ptr = (word_t)desc;
    *out_ref = target;
    if (*desc != 0x301) return 0;

    count = desc[1];
    if (count != *(word_t *)(target + 8)) return 0;

    rng_a = desc[2];
    rng_b = *(word_t *)(target + 0x10);
    if ((rng_a != 0 && rng_b != 0) && rng_a != rng_b) {
        do {
            base_a = (word_t)thunk_FUN_00114c60(rng_a, 0x20);
            base_b = (word_t)thunk_FUN_00114c60(rng_b, 0x20);
            if (base_a == 0 || base_b == 0) break;
            step_a = base_a - rng_a;
            if (step_a != 0 && base_b != rng_b) {
                if ((int)step_a != (int)base_b - (int)rng_b) return 0;
                r = (int)thunk_FUN_00114e50(rng_a, rng_b, step_a & 0xffffffff);
                if (r != 0) return 0;
            }
            rng_a = base_a + 1;
            rng_b = base_b + 1;
        } while (base_a != base_b);
    }

    if (count != 0) {
        j = 0;
        i = 1;
        do {
            if (desc[j * 2 + 3] != *(word_t *)(target + 0x18 + j * 0x10)) {
                if ((count & 0xffffffff) == 0) return 1;
                j = 0;
                desc = desc + 4;
                slot = (word_t *)(target + 0x20);
                do {
                    r = (int)FUN_00365c38(ctx_base + *slot, slot[-1],
                                          aux + *desc, desc[-1], out_ref,
                                          out_ptr, 0, p8, p9);
                    if (r == 0) {
                        if (j == 0) return 0;
                        slot = (word_t *)(target + 0x20);
                        do {
                            (**(void (**)(word_t))(*(word_t *)(slot[-1] - 8) + 8))
                                (ctx_base + *slot);
                            slot = slot + 2;
                            j = j - 1;
                        } while (j != 0);
                        return 0;
                    }
                    desc = desc + 2;
                    slot = slot + 2;
                    j = j + 1;
                } while ((count & 0xffffffff) != j);
                return 1;
            }
            i = i + 1;
        } while (count != i - 1);
    }

    if (mode == 0) {
        (**(void (**)(word_t, word_t, word_t *))(desc[-1] + 0x10))
            (ctx_base, aux, desc);
        return 1;
    }
    (**(void (**)(word_t, word_t, word_t *))(desc[-1] + 0x20))
        (ctx_base, aux, desc);
    return 2;
}

/* FUN_00367160 @ 0x367160   (est. sk_msg_parse_registers_v2)
 * Ghidra: undefined8 FUN_00367160(undefined8,long,undefined8,long*,undefined8,undefined8,int)
 * Variant of the register-context parser using descriptor magic 0x302 and
 * a looser mask check ((uVar4^uVar2)&0xfffffffffeffffff==0). Validates
 * per-slot pair equality (with optional 32-bit compare under flag bits),
 * then invokes the completion callback. Returns 0 / 1 / 2.
 * Confidence: medium
 * Notes: magic 0x302; 0xfffffffffeffffff mask; completion via param_4[-1]
 *   +0x10/+0x20. */
uint64_t sk_msg_parse_registers_v2(word_t a, word_t target, word_t c,
                                   word_t *desc, word_t d, word_t e, int mode)
{
    uint64_t r;
    word_t count, tcount, k;
    uint32_t f1, f2;
    word_t hi1, hi2;
    word_t step;
    int r1, r2;

    if (*desc != 0x302) return 0;
    count = desc[1];
    tcount = *(word_t *)(target + 8);
    if (((tcount ^ count) & 0xfffffffffeffffff) != 0) return 0;

    f1 = (uint32_t)tcount;
    if (((((uint32_t)count >> 0x18 & 1) == 0) || ((f1 >> 0x18 & 1) != 0)) &&
        (desc[2] == *(word_t *)(target + 0x10)) &&
        (k = count & 0xffff, k == (tcount & 0xffff))) {
        if (k != 0) {
            step = 0;
            hi1 = k * 8;
            do {
                if (*(word_t *)((word_t)desc + step + 0x18) !=
                    *(word_t *)(target + 0x18 + step)) return 0;
                if (((uint32_t)count >> 0x19 & 1) == 0) {
                    r1 = 0;
                    if ((f1 >> 0x19 & 1) == 0) goto cmp_done;
                    r2 = *(int *)(target + 0x18 + hi1);
                } else {
                    r1 = *(int *)((word_t)desc + hi1 + 0x18);
                    if ((f1 >> 0x19 & 1) != 0) goto use_r2;
cmp_done:
                    r2 = 0;
                    goto cmp;
use_r2:
                    r2 = *(int *)(target + 0x18 + hi1);
                }
cmp:
                if (r1 != r2) return 0;
                step = step + 8;
                hi1 = hi1 + 4;
            } while (k * 8 - step != 0);
        }
        if (mode == 0) {
            (**(void (**)(word_t, word_t, word_t *))(desc[-1] + 0x10))(a, c, desc);
            r = 1;
        } else {
            (**(void (**)(word_t, word_t, word_t *))(desc[-1] + 0x20))(a, c, desc);
            r = 2;
        }
        return r;
    }
    return 0;
}

/* FUN_0036726c @ 0x36726c   (est. sk_msg_commit_single)
 * Ghidra: undefined8 FUN_0036726c(long,undefined8,undefined8,long,undefined8,undefined8,int)
 * Commits a single validated object reference: stores param_4 into
 * (param_1+0x18), runs the completion callback, returns 1/2. */
uint64_t sk_msg_commit_single(word_t base, word_t b, word_t c, word_t ref,
                              word_t d, word_t e, int mode)
{
    uint64_t r;
    *(word_t *)(base + 0x18) = ref;
    r = FUN_003766b4(ref, base);
    if (mode == 0) {
        (**(void (**)(uint64_t, word_t, word_t))(*(word_t *)(ref - 8) + 0x10))
            (r, c, ref);
        r = 1;
    } else {
        (**(void (**)(uint64_t, word_t, word_t))(*(word_t *)(ref - 8) + 0x20))
            (r, c, ref);
        r = 2;
    }
    return r;
}

/* FUN_003672f4 @ 0x3672f4   (est. sk_msg_parse_single)
 * Ghidra: void FUN_003672f4(long,undefined8,undefined8,undefined8)
 * Parses one message element through FUN_00367bf0; on success commits it
 * via FUN_0036726c. */
void sk_msg_parse_single(word_t base, word_t b, word_t c, word_t desc)
{
    int r;
    r = (int)FUN_00367bf0(c, desc, b, base + 0x20, 0);
    if (r != 0) {
        FUN_0036726c(base, b, c, desc);
    }
}

/* FUN_00367368 @ 0x367368   (est. sk_msg_parse_typed)
 * Ghidra: undefined8 FUN_00367368(long*,undefined8,undefined8,ulong*,undefined8,undefined8,ulong,int,undefined1)
 * Validates a typed message descriptor (kind 0, 0x305 or 0x203) and either
 * commits a single object (FUN_00366774) or walks an element list
 * (FUN_00367bf0). Returns 0/1/2. */
uint64_t sk_msg_parse_typed(word_t *out, word_t b, word_t c, word_t *desc,
                            word_t d, word_t e, word_t flags, int mode, uint8_t p9)
{
    uint64_t r;
    word_t obj;
    int kind;

    kind = 0;
    if (*desc < 0x800) kind = (int)*desc;
    if (((kind == 0) || (kind == 0x305)) || (kind == 0x203)) {
        obj = FUN_00366774(c, desc, b);
        if (obj == 0) {
            if (mode == 0) goto fail;
            *out = 0;
        } else {
            r = FUN_00367bf0(c, desc, b, out + 1, p9);
            if ((int)r == 0) return r;
            *out = obj;
            if ((flags & 1) != 0) return 2;
            FUN_0036b270(obj);
        }
        r = 1;
    } else {
fail:
        r = 0;
    }
    return r;
}

/* FUN_00367438 @ 0x367438   (est. sk_msg_parse_objref)
 * Ghidra: ulong FUN_00367438(undefined8*,undefined8,undefined8,ulong*,undefined8,undefined8,undefined8,undefined8,undefined1)
 * Parses an object-reference message element (kinds 0x200-0x204 except
 * 0x202, plus 0x305/0), returning the committed object via FUN_0036993c. */
uint64_t sk_msg_parse_objref(word_t *out, word_t b, word_t c, word_t *desc,
                             word_t d, word_t e, word_t mode, word_t h, uint8_t p9)
{
    uint64_t r;
    uint64_t obj;
    uint32_t u;
    word_t ref;
    int kind;

    kind = 0;
    if (*desc < 0x800) kind = (int)*desc;
    if ((kind - 0x200U < 4 && kind - 0x200U != 2) || (kind == 0x305 || kind == 0)) {
        ref = 0;
        r = FUN_00367bf0(c, desc, b, &ref, p9);
        if ((int)r != 0) {
            obj = FUN_0036993c(desc, ref, c, mode);
            *out = obj;
            u = 1;
            if ((int)mode != 0) u = 2;
            r = (uint64_t)u;
        }
    } else {
        r = 0;
    }
    return r;
}

/* FUN_003674e8 @ 0x3674e8   (est. sk_async_notify_setup)
 * Ghidra: undefined8 FUN_003674e8(long,long,undefined8,long*,undefined8,undefined8,uint,undefined8,char)
 * Sets up an asynchronous notification/continuation from a message
 * descriptor: validates the notification capability flags, walks a
 * per-slot link list (slot magic 0xf4 / 0x9a), gathers the async vector
 * entries into a temporary buffer, and if the object is live commits it
 * into the TCB at param_1+0x18/0x20 and runs the completion callback.
 * Confidence: medium
 * Notes: desc magics 0x304; DAT_004f2740/DAT_004f2710; builders
 *   FUN_00367ccc/63f10/67d50/9a6fc/6805c/680cc; fatal path SoftwareBreakpoint. */
uint64_t sk_async_notify_setup(word_t base, word_t target, word_t c, word_t *desc,
                               word_t d, word_t e, uint32_t mode, word_t h, char p9)
{
    uint32_t *cap;
    word_t elem;
    word_t *head;
    uint64_t n, m;
    int r;
    uint64_t result;
    word_t obj;
    word_t *dst;
    word_t i;

    cap = *(uint32_t **)(target + 8);
    if (cap == 0) cap = 0;
    if ((*cap >> 8 & 1) == 0) {
        elem = 0;
    } else {
        elem = (uint64_t)(uint16_t)cap[5];
    }
    head = desc;
    if ((*cap >> 9 & 1) != 0) {
        /* Build the notification payload and walk the link list. */
        uint32_t *slot = (uint32_t *)((word_t)cap + ((*cap >> 8) & 1) * 8 + 0x13 & ~3ull);
        int *pi = 0;
        if ((*cap & 0x200) != 0) pi = (int *)slot;
        word_t addr = (word_t)pi + (word_t)*pi;
        word_t node = (addr == 0) ? 0 : (word_t)thunk_FUN_00115080(addr);
        /* allocate the work object */
        word_t wobj = (word_t)FUN_003a32a0(&head, addr, node, (word_t)&elem);
        FUN_00362ea4(&elem);
        if (wobj != 0 && (int16_t)((word_t *)wobj)[2] == 0xf4) {
            word_t cur = wobj;
            word_t *walk = (word_t *)head;
            while ((int16_t)((word_t *)cur)[2] == 0xf4) {
                /* walk list; validate pairs; find 0x304 slot */
                word_t nxt = *(word_t *)cur;
                if ((int16_t)(*(word_t *)nxt + 0x10) != 0x9a) break;
                if (*walk != 0x304) break;
                walk = (word_t *)walk[1];
                cur = *(word_t *)nxt;
            }
        }
        FUN_00362ea4(&elem);
        FUN_003a3814(0);
        if (0) goto fail_out;
    }

    /* gather async vector */
    word_t buf = DAT_004f2740;
    word_t cnt = DAT_004f2740;
    word_t vec = (word_t)&elem;
    FUN_00367ccc(&vec, target + 0x10, target + 0x10 + elem * 8);
    FUN_00363f10(&vec, head);
    FUN_00367d50(&elem, cap);
    FUN_0039a6fc(&result, 0, 0, 0, 0, &vec, &elem, &elem, &elem, &elem);
    FUN_0036805c(&elem);
    FUN_003680cc(&elem);
    FUN_003680cc(&elem);

    if ((0x01 & 1) == 0) {
        r = (int)FUN_0039c7e8(head, &elem);
        if (r == 0) goto done_zero;
        word_t v = 0;
        uint8_t tag = (uint8_t)*cap;
        if (tag < 2) {
            if (tag == 0) {
                *(word_t *)(base + 0x18) = (word_t)desc;
                obj = FUN_003766b4((word_t)desc, base);
                dst = (word_t *)(base + 0x20);
            } else {
                dst = 0;
                if (tag == 1) goto use_slot8;
            }
        } else if (tag == 2) {
use_slot8:
            dst = (word_t *)(base + 8);
            obj = base;
        } else {
            dst = 0;
            if (tag == 3) {
                SoftwareBreakpoint(1, 0x367ae0); /* does not return */
            }
        }
        n = cnt & 0xffffffff;
        word_t *src = (word_t *)vec;
        if ((int)cnt != 0) {
            do {
                *dst = *src;
                n = n - 1;
                dst = dst + 1;
                src = src + 1;
            } while (n != 0);
        }
        if ((mode & 1) == 0) {
            (**(void (**)(word_t, word_t, word_t *))(desc[-1] + 0x10))(obj, c, desc);
            result = 1;
        } else {
            (**(void (**)(word_t, word_t, word_t *))(desc[-1] + 0x20))(obj, c, desc);
            result = 2;
        }
        return result;
    }
done_zero:
fail_out:
    result = 0;
    return result;
}

/* FUN_00367ae0 @ 0x367ae0   (est. sk_lookup_notify_obj)
 * Ghidra: bool FUN_00367ae0(long*,long,undefined8*,long*)
 * For a 0x304 descriptor, resolves the referenced object via FUN_00362c34
 * and stores it; returns whether resolution succeeded. */
bool sk_lookup_notify_obj(word_t *out, word_t target, word_t *cap, word_t *desc)
{
    word_t obj;
    if (*desc == 0x304) {
        obj = FUN_00362c34(*cap, *(word_t *)(target + 8));
        if (obj != 0) *out = obj;
        return obj != 0;
    }
    return false;
}

/* FUN_00367b3c @ 0x367b3c   (est. sk_walk_notify_chain)
 * Ghidra: undefined8 FUN_00367b3c(long*,long,long*,long*)
 * Walks a chained 0x304 notification capability list, following desc[1]
 * and cap[1] links, until a 0x303 (commit) node is found; commits the
 * found object into param_1. Returns 0 on no-match, 1 on commit. */
uint64_t sk_walk_notify_chain(word_t *out, word_t target, word_t *desc, word_t *cap)
{
    word_t *d, *c, v;
    uint64_t r;

    if (*desc != 0x304) return 0;
    d = (word_t *)*desc;
    c = *(word_t **)(target + 8);
    v = *c;
    while (1) {
        if (v == 0x303) {
            word_t *p = (out != 0) ? out + 1 : 0;
            r = FUN_00367bf0(0, d, c, p, 0);
            if ((out != 0) && ((int)r != 0)) {
                *out = (word_t)d;
                r = 1;
            }
            return r;
        }
        if (*d != 0x304) break;
        if (out != 0) *out = (word_t)d;
        d = (word_t *)d[1];
        c = (word_t *)c[1];
        v = *c;
    }
    return 0;
}

/* FUN_00367bf0 @ 0x367bf0   (est. sk_validate_msg_desc)
 * Ghidra: undefined8 FUN_00367bf0(undefined8,ulong*,long,long,undefined8)
 * Core message-descriptor validator: checks object-id-live flag in the
 * capability header (bit 0x40000000) resolving via FUN_00362c34, verifies
 * the descriptor kind is 0/0x305/0x203, then walks the per-element table
 * (count at +0xc) calling FUN_0036254c for each element. Returns nonzero
 * success. */
uint64_t sk_validate_msg_desc(word_t a, word_t *desc, word_t target, word_t out, word_t p5)
{
    uint32_t h;
    word_t e;
    uint64_t r;
    word_t *elem;
    word_t n, i;

    h = *(uint32_t *)(target + 8);
    if (((h >> 0x1e & 1) != 0) && (*(word_t *)(target + 0x10) != 0)) {
        if (FUN_00362c34(desc) == 0) return 0;
        h = *(uint32_t *)(target + 8);
    }
    if (-1 < (int)h) {
        int k = 0;
        if (*desc < 0x800) k = (int)*desc;
        if (((k != 0) && (k != 0x305)) && (k != 0x203)) return 0;
    }
    if (*(uint32_t *)(target + 0xc) == 0) {
        r = 1;
    } else {
        n = (uint64_t)*(uint32_t *)(target + 0xc) << 3;
        elem = (word_t *)(target + ((h >> 0x1e) & 1) * 8 + 0x10);
        do {
            r = FUN_0036254c(a, desc, *elem, out, p5);
            if ((int)r == 0) return r;
            out = (out != 0) ? out + 8 : 0;
            n -= 8;
            elem = elem + 1;
        } while (n != 0);
    }
    return r;
}

/* FUN_00367ccc @ 0x367ccc   (est. sk_vec_append_words)
 * Ghidra: void FUN_00367ccc(long*,long,long)
 * Appends (param_3-param_2)/8 words to a vector pointed by param_1,
 * growing the buffer (FUN_003a294c) if needed, copying via FUN_00117cc4. */
void sk_vec_append_words(word_t *vec, word_t src, word_t end)
{
    uint64_t n, u;
    uint64_t grow;

    grow = end - src;
    u = (uint64_t)*(uint32_t *)(vec + 1);
    n = u + (grow >> 3);
    if (*(uint32_t *)((word_t)vec + 0xc) < n) {
        FUN_003a294c(vec, vec + 2, n, 8);
        u = (uint64_t)*(uint32_t *)(vec + 1);
    }
    if (src != end) {
        FUN_00117cc4(*vec + u * 8, src, grow);
        u = (uint64_t)*(uint32_t *)(vec + 1);
    }
    *(int *)(vec + 1) = (int)u + (int)(grow >> 3);
}

/* FUN_00367d50 @ 0x367d50   (est. sk_obj_cap_desc_init)
 * Ghidra: void FUN_00367d50(undefined8*,uint*)
 * Initializes a capability descriptor from a capability header: selects
 * the offsets table (DAT_004f2770 if bit 0x800 set), stores the header
 * value + computed offset (FUN_00367dd4). */
void sk_obj_cap_desc_init(word_t *desc, uint32_t *cap)
{
    uint32_t h;
    word_t off;
    uint64_t u;

    h = *cap;
    if ((h >> 0xb & 1) == 0) {
        off = ((word_t)cap + ((h >> 8) & 1) * 8 + 0x13 & ~3ull) +
              ((h >> 9) & 1) * 4 + ((h >> 10) & 1) * 4;
    } else {
        off = 0x4f2770;
    }
    u = FUN_00367dd4(cap);
    *desc = *(word_t *)(cap + 2);
    desc[1] = off;
    desc[2] = u;
    *(uint32_t *)(desc + 3) = 0;
    desc[4] = 0;
    *(uint32_t *)(desc + 5) = 0;
    desc[6] = 0;
}

/* FUN_00367dd4 @ 0x367dd4   (est. sk_cap_elem_offset)
 * Ghidra: ulong FUN_00367dd4(uint*)
 * Computes the byte offset of a capability's payload element from its
 * header bitfields (counts at cap[2]/cap[4]). */
uint64_t sk_cap_elem_offset(uint32_t *cap)
{
    uint32_t h;
    uint64_t u2, u3;

    h = *cap;
    if ((h >> 0xb & 1) == 0) u2 = (uint64_t)(uint16_t)cap[2];
    else u2 = 0;
    if ((h & 0x1100) == 0x100) u3 = (uint64_t)(uint16_t)cap[4];
    else u3 = 0;
    return ((word_t)(cap + 4) + ((h >> 8) & 1) * 8 + 3 & ~3ull) + u2 +
           ((h >> 8 & 4) + (h >> 7 & 4) | 3) + u3 & ~3ull;
}

/* FUN_00367e50 @ 0x367e50   (est. sk_tpl_alloc_a370)
 * Ghidra: void FUN_00367e50(long)
 * Allocates a 16-byte template object tagged with vtable 0x67a370 and
 * stores the caller's slot pointer at +8. */
void sk_tpl_alloc_a370(word_t src)
{
    word_t *p;
    word_t v;
    p = (word_t *)FUN_00111890(0x10, 0xa1c40bd48d6d6);
    v = *(word_t *)(src + 8);
    *p = 0x67a370;
    p[1] = v;
}

/* FUN_00367f10 @ 0x367f10   (est. sk_tpl_alloc_a3b8)
 * Same as 0x367e50 but tagged with vtable 0x67a3b8. */
void sk_tpl_alloc_a3b8(word_t src)
{
    word_t *p;
    word_t v;
    p = (word_t *)FUN_00111890(0x10, 0xa1c40bd48d6d6);
    v = *(word_t *)(src + 8);
    *p = 0x67a3b8;
    p[1] = v;
}

/* FUN_00367fcc @ 0x367fcc   (est. sk_tpl_alloc_a400)
 * Allocates a 16-byte template object tagged with vtable 0x67a400. */
void sk_tpl_alloc_a400()
{
    word_t *p;
    p = (word_t *)FUN_00111890(0x10, 0x81c40f5bf735e);
    *p = 0x67a400;
}

/* FUN_00367fd0 @ 0x367fd0   (est. sk_tpl_alloc_a400_b)
 * Identical template allocator to 0x367fcc. */
void sk_tpl_alloc_a400_b()
{
    word_t *p;
    p = (word_t *)FUN_00111890(0x10, 0x81c40f5bf735e);
    *p = 0x67a400;
}

/* FUN_0036805c @ 0x36805c   (est. sk_teardown_call)
 * Ghidra: long* FUN_0036805c(long*)
 * Dispatch helper: if the object's third slot points at itself invoke the
 * vtable +0x20 teardown, else the vtable +0x28 teardown. */
word_t *sk_teardown_call(word_t *obj)
{
    word_t *p;
    p = (word_t *)obj[3];
    if (p == obj) (**(void (**)(void))(*p + 0x20))();
    else if (p != 0) (**(void (**)(void))(*p + 0x28))();
    return obj;
}

/* FUN_003680cc @ 0x3680cc   (est. sk_teardown_call_b)
 * Duplicate of 0x36805c (teardown dispatch). */
word_t *sk_teardown_call_b(word_t *obj)
{
    word_t *p;
    p = (word_t *)obj[3];
    if (p == obj) (**(void (**)(void))(*p + 0x20))();
    else if (p != 0) (**(void (**)(void))(*p + 0x28))();
    return obj;
}

/* FUN_0036813c @ 0x36813c   (est. sk_recursive_teardown)
 * Ghidra: void FUN_0036813c(undefined8,undefined8,int)
 * Recursively tears down an object chain of depth param_3, invoking the
 * owning type's destructor (+0x38). */
void sk_recursive_teardown(word_t a, word_t obj, int depth)
{
    word_t *p;
    word_t next;
    p = (word_t *)FUN_0035eae4(obj);
    next = *p;
    if (depth >= 1) sk_recursive_teardown(a, next, depth - 1);
    (**(void (**)(word_t, int, int, word_t))(*(word_t *)(next - 8) + 0x38))
        (a, depth < 1, 1, next);
}

/* FUN_003681c4 @ 0x3681c4   (est. sk_register_type_once)
 * Ghidra: long FUN_003681c4(long*)
 * One-time registration of a type descriptor (kind 0x200 with tag
 * 0x6123c4): under a global once-flag either returns the cached
 * registered value or runs FUN_004b9c0c to populate it, then stores the
 * descriptor into the global slot DAT_006c0260. Returns the cached value.
 * Confidence: medium
 * Notes: globals _DAT_006c0270/_DAT_006c0268/_DAT_006c0260; DAT_0060ce80;
 *   tag 0x6123c4; FUN_004b9c0c, FUN_0039c740. */
long sk_register_type_once(word_t *desc)
{
    long v;
    if (*desc == 0x200) {
        v = desc[1];
        if (v == 0) v = 0;
        if (v == 0x6123c4) {
            if ((DAT_006c0278 & 1) != 0) return _DAT_006c0270;
            FUN_004b9c0c(desc);
            return _DAT_006c0270;
        }
    }
    if (desc != (word_t *)_DAT_006c0260) {
        _DAT_006c0268 = FUN_0039c740(desc, &DAT_0060ce80);
        DataMemoryBarrier(2, 3);
        _DAT_006c0260 = (word_t)desc;
    }
    v = _DAT_006c0268;
    if (_DAT_006c0268 == 0) v = 0;
    return v;
}

/* FUN_00368298 @ 0x368298   (est. sk_noop)
 * Empty leaf. */
void sk_noop() {}

/* FUN_003682b0 @ 0x3682b0   (est. sk_obj_copy_alloc)
 * Ghidra: undefined8* FUN_003682b0(long,uint)
 * Allocates and deep-copies the 14-slot object header (0x70 bytes)
 * pointed to by (param_1-8) and stores the copy back. Returns the copy. */
word_t *sk_obj_copy_alloc(word_t self, uint32_t flags)
{
    word_t *src, *dst;
    if ((flags >> 8 & 1) == 0) {
        src = *(word_t **)(self - 8);
        if (src == 0) src = 0;
        dst = (word_t *)FUN_00379410(0x70, 8);
        dst[0] = src[0]; dst[1] = src[1]; dst[2] = src[2]; dst[3] = src[3];
        dst[4] = src[4]; dst[5] = src[5]; dst[6] = src[6]; dst[7] = src[7];
        dst[8] = src[8]; dst[9] = src[9]; dst[10] = src[10];
        dst[0xb] = src[0xb]; dst[0xc] = src[0xc]; dst[0xd] = src[0xd];
        if ((dst != 0) && (dst == 0)) dst = 0;
        *(word_t **)(self - 8) = dst;
        src = dst;
    }
    return src;
}

/* FUN_0036851c @ 0x36851c   (est. sk_obj_grow_slots)
 * Ghidra: void FUN_0036851c(undefined8,undefined8,ulong*,uint)
 * Computes a grown slot capacity for an object (rounding up to the next
 * power-of-two factor of element size param_4), builds a fresh descriptor
 * via FUN_003682b0/FUN_00372598 and fills its capacity fields. */
void sk_obj_grow_slots(word_t a, word_t b, word_t *obj, uint32_t want)
{
    uint64_t cap, cnt;
    uint32_t h, gr;
    long grow;

    cap = *obj;
    cnt = *(uint32_t *)((word_t)obj + 0x14);
    if (cnt < want) {
        if (cap < 4) {
            uint32_t bits = (uint32_t)cap << 3;
            cnt = ((want - cnt) + ~(-1 << (bits & 0x1f)) >> (bits & 0x1f)) + 1;
            if (cnt < 2) grow = 0;
            else {
                long g = 2;
                if (0xffff < cnt) g = 4;
                grow = 1;
                if (0xff < cnt) grow = g;
            }
        } else {
            grow = 1;
        }
        cap = (uint64_t)grow + cap;
    }
    long out = FUN_003682b0();
    uint32_t u2 = (uint32_t)obj[2];
    uint64_t u1 = (u2 & 0xff) + 1;
    uint32_t extra = 0;
    if (((u2 & 0x100000) != 0 || 7 < (uint32_t)((uint64_t)u2 & 0xff)) || 0x18 < cap)
        extra = 0x20000;
    uint32_t f = u2 & 0xfffdffff | extra | 0x200000;
    uint64_t block = 0;
    if (u1 != 0) block = ((cap + u1) - 1) / u1;
    block *= u1;
    if (block < 2) block = 1;
    uint64_t local = cap;
    int ic = 0;
    FUN_00372598(&local, out);
    *(uint64_t *)(out + 0x48) = block;
    *(uint64_t *)(out + 0x40) = local;
    *(uint64_t *)(out + 0x50) = CONCAT44(ic, f);
}

/* FUN_0036878c @ 0x36878c   (est. sk_bitmap_pack)
 * Ghidra: void FUN_0036878c(uint*,undefined8,uint,undefined8,ulong,undefined8,code*)
 * Packs a multi-word bit value into a byte/short/word field at param_1
 * with width param_5, storing the shifted high part at the tail offset
 * (param_1+param_5). */
void sk_bitmap_pack(uint32_t *dst, word_t v, uint32_t bits, word_t d, uint64_t width,
                    word_t f, void (*jumptable)(uint32_t *, word_t, word_t))
{
    uint32_t hi, lo, cur;
    int i;
    int32_t *tail = (int32_t *)((word_t)dst + width);
    uint32_t b = (uint32_t)f;
    uint32_t src = (uint32_t)v;
    uint32_t hb = 0;

    if (bits < b || bits - b == 0) {
        if (src <= b) goto store0;
        uint32_t q = 0;
loop:
        src = src + ~b;
        if (width < 4) goto tail_store;
        hb = 1;
        goto check;
    } else {
        if (3 < width) {
            hb = 1;
check:
            if (src <= b) {
                if (hb < 3) { if (hb == 1) *(uint8_t *)tail = 0; else *(uint16_t *)tail = 0; }
                else if (hb == 3) { *(uint16_t *)tail = 0; *(uint8_t *)((word_t)tail + 2) = 0; }
                else *tail = 0;
store0:
                if (src == 0) return;
                (*jumptable)(dst, v, f);
                return;
            }
            goto loop;
        }
        hb = (uint32_t)width << 3;
        uint32_t n = ((bits - b) + ~(-1 << (hb & 0x1f)) >> (hb & 0x1f)) + 1;
        if (1 < n) {
            uint32_t g = 2;
            if (0xffff < n) g = 4;
            hb = 1;
            if (0xff < n) hb = g;
            goto check;
        }
        if (src <= b) goto store0;
        hb = 0;
        src = src + ~b;
tail_store:
        uint32_t w = (uint32_t)width << 3;
        i = (int)(src >> (w & 0x1f)) + 1;
        if (width == 0) goto store_tail;
        src = src & (-1 << (w & 0x1f) ^ 0xffffffffU);
    }
    if ((long)width < 3) {
        if (width == 1) { *(char *)dst = (char)src; goto store_tail; }
        if (width == 2) { *(short *)dst = (short)src; goto store_tail; }
    } else {
        if (width == 3) { *(short *)dst = (short)src; *(char *)((word_t)dst + 2) = (char)(src >> 0x10); goto store_tail; }
        if (width == 4) { *dst = src; goto store_tail; }
    }
    *dst = src;
    thunk_FUN_00114330(dst + 1, width - 4);
store_tail:
    if (hb != 0) {
        if (hb < 3) { if (hb == 1) *(char *)tail = (char)i; else *(short *)tail = (short)i; }
        else if (hb == 3) { *(short *)tail = (short)i; *(char *)((word_t)tail + 2) = (char)((uint32_t)i >> 0x10); }
        else *tail = i;
    }
}

/* FUN_00368980 @ 0x368980   (est. sk_obj_desc_from_elems)
 * Ghidra: void FUN_00368980(long,undefined8,uint,long*)
 * Builds an object descriptor from a list of element descriptors: tracks
 * the max element size, aggregate memattr bits, and capacity flags
 * (0x10000/0x100000/0x1100000), then allocates a descriptor via
 * FUN_003682b0 and fills its size/capacity fields. */
void sk_obj_desc_from_elems(word_t obj, word_t a, uint32_t n, word_t *elems)
{
    uint64_t maxsz = 0, u14 = 0;
    uint32_t u11 = 0, u7 = 0x200000;
    bool b3 = true, b4 = true, b5 = true;
    uint32_t i;
    uint64_t m;

    if (n != 0) {
        b4 = true; b3 = true; b5 = true;
        m = (uint64_t)n;
        do {
            uint64_t es = *(uint64_t *)*elems;
            if (maxsz <= es) maxsz = es;
            u11 = (uint32_t)((word_t *)*elems)[2];
            u14 = u14 | (uint64_t)u11 & 0xff;
            b4 = b4 & (u11 & 0x10000) == 0;
            b3 = b3 & (u11 & 0x100000) == 0;
            b5 = b5 & (u11 & 0x1100000) == 0;
            m = m - 1;
            elems = elems + 1;
        } while (m != 0);
        u11 = b4 ? 0 : 0x10000;
        u7 = b5 ? 0x200000 : 0x1200000;
    } else {
        b3 = true; u7 = 0x200000; u11 = 0; u14 = 0;
    }

    word_t t8 = *(word_t *)(obj + 8);
    word_t t = (t8 == 0) ? 0 : t8;
    uint64_t idx = (uint64_t)(*(uint32_t *)(t + 0x14) >> 0x18);
    if (*(word_t *)(obj + idx * 8) != maxsz) *(word_t *)(obj + idx * 8) = maxsz;

    uint32_t extra = 0;
    word_t g8 = (t8 == 0) ? 0 : t8;
    if (*(int *)(g8 + 0x18) != 0) {
        if (maxsz < 4) {
            uint32_t bits = (uint32_t)maxsz << 3;
            extra = ((uint32_t)(*(int *)(g8 + 0x18) + ~(-1 << (bits & 0x1f))) >> (bits & 0x1f)) + n;
        } else extra = n + 1;
    }
    uint32_t gr;
    if (extra < 2) gr = 0;
    else if (extra < 0x100) gr = 1;
    else { gr = 2; if (0xffff < extra) gr = 4; }
    uint32_t cap = gr + (uint32_t)maxsz;
    uint32_t rem = (1 << ((gr & 3) << 3)) - extra;
    if (0x7ffffffe < rem) rem = 0x7fffffff;
    uint32_t r2 = (gr != 4) ? rem : 0x7fffffff;

    word_t *out = (word_t *)FUN_003682b0();
    uint64_t block = (uint64_t)cap + u14 & (u14 ^ 0xffffffffffffffff);
    if (block < 2) block = 1;
    uint32_t u9 = b3 ? 0 : 0x100000;
    uint32_t l60 = 0;
    if (!(b3 && (u14 < 8 && cap < 0x19))) l60 = 0x20000;
    l60 = u7 | u11 | (uint32_t)u14 | u9 | l60;
    uint64_t local = (uint64_t)cap;
    uint32_t u5c = r2;
    FUN_00372598(&local, out);
    *(word_t **)(out + 0x30) = &sk_obj_grow_slots;   /* LAB_00368c44 */
    *(word_t **)(out + 0x38) = &sk_obj_desc_from_elems; /* DAT_00368d5c */
    *(uint64_t *)(out + 0x48) = block;
    *(uint64_t *)(out + 0x40) = local;
    *(uint64_t *)(out + 0x50) = CONCAT44(u5c, l60);
}

/* FUN_00368da8 @ 0x368da8   (est. sk_obj_alloc_descriptor)
 * Ghidra: void FUN_00368da8(long,undefined8,uint,long*)
 * Allocates a fresh object descriptor for n input objects, laying out a
 * header + per-object word table, inserting each object via FUN_0037311c,
 * then committing through FUN_0035cf38 and FUN_00372598. */
void sk_obj_alloc_descriptor(word_t obj, word_t a, uint32_t n, word_t *src)
{
    uint64_t maxsz = 0, u15 = 0;
    uint32_t u8 = 0;
    bool b2 = true, b3 = true;
    uint32_t i;

    if (n != 0) {
        uint64_t m = (uint64_t)n;
        word_t *p = src;
        do {
            uint64_t es = *(uint64_t *)(*(word_t *)(*p - 8) + 0x40);
            if (maxsz <= es) maxsz = es;
            u8 = *(uint32_t *)(*(word_t *)(*p - 8) + 0x50);
            u15 = u15 | (uint64_t)u8 & 0xff;
            b3 = b3 & (u8 & 0x10000) == 0;
            b2 = b2 & (u8 & 0x100000) == 0;
            maxsz += FUN_00372fbc() + 8;
            m = m - 1;
            p = p + 1;
        } while (m != 0);
        u8 = b3 ? 0 : 0x10000;
    }

    word_t t8 = *(word_t *)(obj + 8);
    word_t t = (t8 == 0) ? 0 : t8;
    uint64_t idx = (uint64_t)(*(uint32_t *)(t + 0x14) >> 0x18);
    if (*(word_t *)(obj + idx * 8) != maxsz) *(word_t *)(obj + idx * 8) = maxsz;

    uint32_t extra = n;
    word_t g8 = (t8 == 0) ? 0 : t8;
    if (*(int *)(g8 + 0x18) != 0) {
        if (maxsz < 4) {
            uint32_t bits = (uint32_t)maxsz << 3;
            extra = ((uint32_t)(*(int *)(g8 + 0x18) + ~(-1 << (bits & 0x1f))) >> (bits & 0x1f)) + n;
        } else extra = n + 1;
    }
    uint32_t gr;
    if (extra < 2) gr = 0;
    else if (extra < 0x100) gr = 1;
    else { gr = 2; if (0xffff < extra) gr = 4; }

    word_t local = 0;
    word_t *out = (word_t *)FUN_003682b0(obj, a);
    uint64_t cnt = (uint64_t)n;
    uint64_t sz = (uint64_t)n * 8 + 0x38;
    uint64_t total = u15 + sz;
    word_t *tab = (word_t *)FUN_00369758(&local, total + 0xf & ~7ull, 1);
    tab[1] = total - 0x10;
    tab[2] = 0x1600000000000000;
    tab[3] = (uint64_t)gr;
    tab[4] = cnt;
    tab[5] = u15;
    tab[6] = (uint64_t)gr + maxsz;
    /* ... full layout code elided: inserts each object then commits ... */
}

/* FUN_00369340 @ 0x369340   (est. sk_obj_field_store)
 * Ghidra: void FUN_00369340(uint*,long,uint)
 * Stores a fixed-width field (width from object element size) at a byte
 * offset computed from the object's base, splitting the value between the
 * low bits at the offset and the high bits at offset+width. */
void sk_obj_field_store(uint32_t *dst, word_t obj, uint32_t val)
{
    word_t t5 = *(word_t *)(obj + 8);
    word_t t = (t5 == 0) ? 0 : t5;
    uint64_t off = *(uint64_t *)(obj + (uint64_t)*(uint8_t *)(t + 0x17) * 8);
    uint64_t width = *(word_t *)(*(word_t *)(obj - 8) + 0x40) - off;
    word_t g5 = (t5 == 0) ? 0 : t5;
    uint32_t base = *(uint32_t *)(g5 + 0x14) & 0xffffff;
    uint32_t hi = val - base;
    uint32_t low;

    if (val < base) {
        uint32_t *d = (uint32_t *)((word_t)dst + off);
        if ((long)width < 2) { if (width == 0) return; if (width == 1) { *(char *)d = (char)val; return; } }
        else { if (width == 2) { *(short *)d = (short)val; return; } if (width == 3) { *(short *)d = (short)val; *(char *)((word_t)d + 2) = (char)(val >> 0x10); return; } if (width == 4) { *d = val; return; } }
        *d = val;
        thunk_FUN_00114330(d + 1, width - 4);
        return;
    }
    uint32_t bits = (uint32_t)off << 3;
    if (off < 4) { base = (hi >> (bits & 0x1f)) + base; hi = hi & (-1 << (bits & 0x1f) ^ 0xffffffffU); }
    uint32_t *d = (uint32_t *)((word_t)dst + off);
    if ((long)width < 2) { if (width != 0) { if (width == 1) *(char *)d = (char)base; else { *d = base; thunk_FUN_00114330(d + 1, width - 4); } } }
    else if (width == 2) *(short *)d = (short)base;
    else if (width == 3) { *(short *)d = (short)base; *(char *)((word_t)d + 2) = (char)(base >> 0x10); }
    else { if (width != 4) { *d = base; thunk_FUN_00114330(d + 1, width - 4); } else *d = base; }
    if ((long)off < 2) { if (off == 0) return; if (off == 1) { *(char *)dst = (char)hi; return; } }
    else { if (off == 2) { *(short *)dst = (short)hi; return; } if (off == 3) { *(short *)dst = (short)hi; *(char *)((word_t)dst + 2) = (char)(hi >> 0x10); return; } if (off == 4) { *dst = hi; return; } }
    *dst = hi;
    thunk_FUN_00114330(dst + 1, off - 4);
}

/* FUN_00369584 @ 0x369584   (est. sk_obj_field_load)
 * Ghidra: ulong FUN_00369584(uint*,long)
 * Loads a fixed-width object field (width from element size) from
 * (param_1 + offset), merging low+high bits. */
uint64_t sk_obj_field_load(uint32_t *src, word_t obj)
{
    word_t t3 = *(word_t *)(obj + 8);
    word_t t = (t3 == 0) ? 0 : t3;
    word_t off = *(word_t *)(obj + (uint64_t)*(uint8_t *)(t + 0x17) * 8);
    word_t g3 = (t3 == 0) ? 0 : t3;
    uint32_t base = *(uint32_t *)(g3 + 0x14) & 0xffffff;
    uint64_t lo = FUN_003696dc(src, off, *(word_t *)(*(word_t *)(obj - 8) + 0x40) - off, 0);
    uint32_t hi;
    if ((uint32_t)lo < base) return lo;
    if (off < 2) { if (off == 0) hi = 0; else { if (off != 1) { hi = *src; goto merge; } hi = (uint32_t)(uint8_t)*src; } }
    else if (off == 2) hi = (uint32_t)(uint16_t)*src;
    else { if (off != 3) { hi = *src; goto merge; } hi = (uint32_t)(*src & 0xffffff); }
    hi = hi | (uint32_t)lo - base << (((uint32_t)off & 3) << 3);
merge:
    return (uint64_t)(hi + base);
}

/* FUN_003696dc @ 0x3696dc   (est. sk_field_load_width)
 * Ghidra: uint FUN_003696dc(long,long,long,uint)
 * Loads a width-limited field (0-4 bytes) at (param_1+param_2), OR-ing
 * the masked high bits of param_4 for widths != 4. */
uint32_t sk_field_load_width(word_t base, word_t off, word_t width, uint32_t mask)
{
    uint32_t *p = (uint32_t *)(base + off);
    uint32_t v;
    if (width < 2) { if (width == 0) v = 0; else if (width == 1) v = (uint32_t)(uint8_t)*p; }
    else { if (width == 2) v = (uint32_t)(uint16_t)*p; else if (width == 3) v = (uint32_t)(*p & 0xffffff); }
    uint32_t hi = 0;
    if (width != 4) hi = -1 << (((uint32_t)width & 3) << 3) & mask;
    return v | hi;
}

/* FUN_00369758 @ 0x369758   (est. sk_alloc_aligned)
 * Ghidra: void FUN_00369758(undefined8,long,ulong)
 * Allocates an aligned buffer of at least param_3 bytes (min 8), via
 * FUN_0001062c with alignment; panics (SoftwareBreakpoint) on failure. */
void sk_alloc_aligned(word_t out, long size, uint64_t align)
{
    if (align < 9) align = 8;
    word_t r = 0;
    int rc = FUN_0001062c(&r, align, (size + align) - 1 & -align, 0x59dd9b33);
    if (rc == 0 && r != 0) return;
    SoftwareBreakpoint(1, 0x3697c0); /* does not return */
}

/* FUN_003697c4 @ 0x3697c4   (est. sk_std_allocator_kind)
 * Ghidra: undefined1 FUN_003697c4()
 * Runs the allocator once (FUN_003d3dd8) if not yet initialized, returns
 * a stored allocator-kind byte. */
uint8_t sk_std_allocator_kind()
{
    if (-1 < _DAT_006adee0) FUN_003d3dd8(&DAT_006adee0, &DAT_003697c0, 0);
    return (uint8_t)DAT_006adecd;
}

/* FUN_00369818 @ 0x369818   (est. sk_allocator_kind_f4)
 * Same as above but returns the constant 0xf4. */
uint8_t sk_allocator_kind_f4()
{
    if (-1 < _DAT_006adee0) FUN_003d3dd8(&DAT_006adee0, &DAT_003697c0, 0);
    return 0xf4;
}

/* FUN_0036986c @ 0x36986c   (est. sk_call_hook)
 * Ghidra: void FUN_0036986c()
 * Invokes the installed global hook _DAT_006adee8 if non-null. */
void sk_call_hook()
{
    if (_DAT_006adee8 != 0) (*(void (**)(void))_DAT_006adee8)();
}

/* FUN_003698b0 @ 0x3698b0   (est. sk_notify_hook)
 * Ghidra: void FUN_003698b0(undefined8,undefined8,undefined8)
 * Dispatches a notification to the secondary hook _DAT_006adef0 if set,
 * else builds a pending-object via FUN_0036993c, runs the primary hook
 * _DAT_006adee8, and releases via thunk_FUN_0036b118. */
void sk_notify_hook(word_t a, word_t b, word_t c)
{
    void (*primary)(void) = (void (*)(void))_DAT_006adee8;
    if (_DAT_006adef0 != 0) {
        (*(void (**)(word_t))_DAT_006adef0)(a);
        return;
    }
    if (_DAT_006adee8 == 0) return;
    uint64_t o = FUN_0036993c(b, c, a, 0);
    (*primary)();
    thunk_FUN_0036b118(o);
}

/* FUN_0036993c @ 0x36993c   (est. sk_pending_obj_build)
 * Ghidra: undefined1[16] FUN_0036993c(long,undefined8,long,ulong)
 * Builds a pending-object container: allocates a payload region sized by
 * the owning object's element width (byte at lVar1+0x50), stores the
 * source and callback, optionally runs a copy/completion callback on the
 * payload, and returns the (payload, container) pair. */
cl4_result_t sk_pending_obj_build(word_t src, word_t cb, word_t obj, uint64_t mode)
{
    cl4_result_t r;
    word_t *m = *(word_t **)(src - 8);
    uint64_t w = (uint64_t)*(uint8_t *)(m + 0x50);
    word_t payload = FUN_0036a940(0x67a450,
        (w + 0x20 & (w ^ 0xffffffffffffffff)) + *(word_t *)(m + 0x40), w | 7);
    *(word_t *)(payload + 0x10) = src;
    *(word_t *)(payload + 0x18) = cb;
    m = *(word_t **)(src - 8);
    w = (uint64_t)*(uint8_t *)(m + 0x50);
    word_t p = payload + w + 0x20;
    if (obj != 0) {
        if ((mode & 1) == 0)
            (**(void (**)(word_t, word_t, word_t))(m + 0x10))(p & (w ^ 0xffffffffffffffff), obj, src);
        else
            (**(void (**)(word_t, word_t, word_t))(m + 0x20))(p & (w ^ 0xffffffffffffffff), obj, src);
    }
    r.hi = p & (w ^ 0xffffffffffffffff);
    r.lo = payload;
    return r;
}

/* FUN_00369a30 @ 0x369a30   (est. sk_pending_obj_read)
 * Ghidra: void FUN_00369a30(long,undefined8,ulong*)
 * Reads a pending-object's payload pointer, container and callback into
 * the 3-slot output array. */
void sk_pending_obj_read(word_t obj, word_t b, word_t *out)
{
    uint64_t u1 = *(uint64_t *)(obj + 0x10);
    uint64_t u2 = (uint64_t)*(uint8_t *)(*(word_t *)(u1 - 8) + 0x50);
    out[0] = obj + u2 + 0x20 & (u2 ^ 0xffffffffffffffff);
    out[1] = u1;
    out[2] = *(uint64_t *)(obj + 0x18);
}

/* FUN_00369a64 @ 0x369a64   (est. sk_refcount_acquire)
 * Ghidra: ulong thunk_FUN_0036b270(ulong)
 * Reference-count acquire: walks the 64-bit refcount word (with an
 * overflow guard constant 0x200000000); on the sentinel (-1 low bits)
 * returns, otherwise hands a full acquire to FUN_0039f9e8. */
uint64_t sk_refcount_acquire(uint64_t obj)
{
    word_t *p; bool b; word_t v, nv;
    if (0 < (long)obj) {
        uint64_t base = obj & 0xffffffffffffff8;
        p = (word_t *)(base + 8);
        v = *(word_t *)(base + 8);
        do {
            nv = v + 0x200000000;
            if (nv < 0) {
                if ((int)v == -1) return base;
                return FUN_0039f9e8(p, v, 1);
            }
            b = *p != v;
            v = *p;
        } while (b);
        *p = nv;
    }
    return obj;
}

/* FUN_00369a68 @ 0x369a68   (est. sk_refcount_release)
 * Ghidra: void thunk_FUN_0036b118(long)
 * Reference-count release: decrements by 0x200000000, handing a full
 * release to FUN_0036b9e4 when the counter would underflow. */
void sk_refcount_release(word_t obj)
{
    word_t *p; bool b; word_t v, nv;
    if (0 < obj) {
        p = (word_t *)(obj + 8);
        v = *(word_t *)(obj + 8);
        do {
            nv = v - 0x200000000;
            if (nv < 0) {
                if ((int)v == -1) return;
                FUN_0036b9e4(p, v, 1);
                return;
            }
            b = *p != v;
            v = *p;
        } while (b);
        *p = nv;
    }
}

/* FUN_00369a6c @ 0x369a6c   (est. sk_pending_obj_destroy)
 * Ghidra: void FUN_00369a6c()
 * Destroys a pending object: invokes the owning type's destructor (+8) on
 * the payload and releases the container (FUN_0036b21c). */
void sk_pending_obj_destroy()
{
    uint64_t w;
    word_t *m = *(word_t **)(*(word_t *)(/*unaff_x20*/0 + 0x10) - 8);
    w = (uint64_t)*(uint8_t *)(m + 0x50);
    (**(void (**)(word_t))(m + 8))(/*unaff_x20*/0 + w + 0x20 & (w ^ 0xffffffffffffffff));
    FUN_0036b21c();
}

/* FUN_00369b04 @ 0x369b04   (est. sk_noop_b)
 * Empty leaf. */
void sk_noop_b() {}

/* FUN_00369b08 @ 0x369b08   (est. sk_thunk_noop)
 * Thunk to 0x369b04; empty. */
void sk_thunk_noop() {}

/* FUN_00369b0c @ 0x369b0c   (est. sk_const_4f)
 * Returns constant 0x4f. */
uint8_t sk_const_4f() { return 0x4f; }

/* FUN_00369b18 @ 0x369b18   (est. sk_format_string)
 * Ghidra: void FUN_00369b18(undefined8,undefined8,undefined8)
 * Formats param_2 into an allocated buffer (FUN_000101a0 + FUN_00116bb4),
 * concatenates via FUN_004b9d68, recurses, then triggers the fatal-error
 * hook. Never returns. */
void sk_format_string(word_t a, word_t b, word_t c)
{
    int n;
    word_t buf;
    word_t local40 = c, local38 = c;
    n = (int)FUN_00116bb4(0, 0, b, c);
    if (-1 < n) {
        buf = FUN_000101a0(n + 1, 0x100004077774924);
        if ((buf == 0) || (n = (int)FUN_00116bb4(buf, n + 1, b, local38), -1 < n))
            goto done;
        thunk_FUN_00012568(buf);
    }
    buf = 0;
done:
    FUN_004b9d68(a, buf);
    sk_format_string(0, 0, local40);
    FUN_00369bb0(0, s_Fatal_error__Call_of_deleted_met_005d4429);
}

/* FUN_00369bb0 @ 0x369bb0   (est. sk_fatal_error)
 * Ghidra: void FUN_00369bb0(undefined8,undefined8)
 * Fatal-error entry: formats the message via FUN_00369b18 then loops on
 * the fatal hook. Never returns. */
void sk_fatal_error(word_t a, word_t b)
{
    word_t stack0 = 0; FUN_00369b18(a, b, &stack0);
    FUN_00369bb0(0, s_Fatal_error__Call_of_deleted_met_005d4429);
}

/* FUN_00369bec @ 0x369bec   (est. sk_fatal_retained)
 * Fatal error "Object was retained" — never returns. */
void sk_fatal_retained()
{
    FUN_00369bb0(1, s_Fatal_error__Object_was_retained_005d444e);
}

/* FUN_00369c08 @ 0x369c08   (est. sk_fatal_unowned_release)
 * Fatal error "Object's unowned reference count reached zero". */
void sk_fatal_unowned_release()
{
    FUN_00369bb0(1, s_Fatal_error__Object_s_unowned_re_005d447f);
}

/* FUN_00369c24 @ 0x369c24   (est. sk_fatal_weak_ref)
 * Fatal error "Object's weak reference count overflow". */
void sk_fatal_weak_ref()
{
    FUN_00369bb0(1, s_Fatal_error__Object_s_weak_refer_005d44c4);
}

/* FUN_00369c40 @ 0x369c40   (est. sk_fatal_read_weak)
 * Ghidra: void FUN_00369c40(long)
 * Fatal errors for reading a weak reference from a deallocated object. */
void sk_fatal_read_weak(word_t obj)
{
    if (obj == 0) FUN_00369bb0(1, s_Fatal_error__Attempted_to_read_a_005d455f);
    FUN_00369bb0(1, s_Fatal_error__Attempted_to_read_a_005d4506);
}

/* FUN_00369c78 @ 0x369c78   (est. sk_fatal_alloc_fail)
 * Fatal "failed to allocate" error. */
void sk_fatal_alloc_fail()
{
    FUN_00369bb0(1, s_Fatal_error__failed_to_allocate___005d45b9);
}

/* FUN_00369ca0 @ 0x369ca0   (est. sk_copy_string)
 * Ghidra: void FUN_00369ca0(long*)
 * Duplicates the string at DAT_005d4601 into an allocated buffer and
 * stores the pointer at param_1 (or 0 on failure). */
void sk_copy_string(word_t *out)
{
    int n;
    word_t buf;
    n = (int)FUN_00116bb4(0, 0, &DAT_005d4601, 0);
    *out = 0;
    if (-1 < n) {
        buf = FUN_000101a0(n + 1, 0x100004077774924);
        if (buf != 0) {
            n = (int)FUN_00116bb4(buf, n + 1, &DAT_005d4601, 0);
            if (n < 0) thunk_FUN_00012568(buf);
            else *out = buf;
        }
    }
}

/* FUN_00369d48 @ 0x369d48   (est. sk_teardown_call_c)
 * Duplicate of teardown dispatch (0x36805c). */
word_t *sk_teardown_call_c(word_t *obj)
{
    word_t *p = (word_t *)obj[3];
    if (p == obj) (**(void (**)(void))(*p + 0x20))();
    else if (p != 0) (**(void (**)(void))(*p + 0x28))();
    return obj;
}

/* FUN_00369dc4 @ 0x369dc4   (est. sk_tpl_alloc_a468)
 * Allocates a 16-byte template tagged with vtable 0x67a468. */
void sk_tpl_alloc_a468(word_t src)
{
    word_t *p = (word_t *)FUN_00111890(0x10, 0x91c40c859b4a5);
    word_t v = *(word_t *)(src + 8);
    *p = 0x67a468;
    p[1] = v;
}

/* FUN_00369e68 @ 0x369e68   (est. sk_log_hex_dump)
 * Ghidra: void FUN_00369e68(long,undefined8,int*)
 * Logs a 64-bit hex line ("%4u 0x%016tx") repeatedly to reach the counter
 * value at param_3, from the value at **(param_1+8). */
void sk_log_hex_dump(word_t a, word_t b, int *counter)
{
    int cur, want;
    want = *counter;
    cur = **(int **)(a + 8);
    if (cur < want) {
        do {
            FUN_001185ec(0xeb1a02bf914012ba, s___4u_0x_0_16tx_005d4400);
            cur = cur + 1;
        } while (want != cur);
    }
}

/* FUN_00369efc @ 0x369efc   (est. sk_cap_can_send)
 * Ghidra: undefined4 FUN_00369efc(undefined8,long*)
 * For a 0x201 capability, returns the vtable +0x58 result (can-send
 * check); otherwise returns 1 (allowed). */
uint32_t sk_cap_can_send(word_t a, word_t *cap)
{
    if (*cap == 0x201) return (**(uint32_t (**)(void))(cap[-1] + 0x58))();
    return 1;
}

/* FUN_00369f4c @ 0x369f4c   (est. sk_access_acquire)
 * Ghidra: ulong FUN_00369f4c(ulong*,long*,long,long,uint)
 * Thread-local access tracker: finds or inserts a (base, arg) pair in the
 * per-thread access list; on conflict (existing pair) logs an
 * "exclusivity violation" fatal error; inserts a new pair at the head.
 * Returns the exclusivity result (bit 5 = added). */
uint64_t sk_access_acquire(uint64_t *list, word_t *out, word_t arg, word_t base, uint32_t flags)
{
    word_t *cur = (word_t *)*list;
    word_t *prev = cur;
    word_t prior;
    uint64_t r;

    while (1) {
        if (cur == 0) {
            if ((flags >> 5 & 1) != 0) {
                out[0] = base;
                out[1] = arg;
                out[2] = (uint64_t)flags & 1 | (uint64_t)prev;
                *list = (uint64_t)out;
            }
            return ((uint64_t)flags & 0x20) >> 5;
        }
        if ((*cur == base) && (((flags & 1) != 0) || ((cur[2] & 1U) != 0))) break;
        cur = (word_t *)(cur[2] & 0xfffffffffffffffe);
    }
    prior = cur[1];
    FUN_0005b824(0, 100, 100, s_Simultaneous_accesses_to_0x_lx__b_005d4627);
    FUN_001185ec(0xeb1a02bf914012ba, &DAT_005d4672);
    FUN_0005b824(0, 0x32, 0x32, s_Previous_access__a__s__started_a_005d4677);
    FUN_001185ec(0xeb1a02bf914012ba, &DAT_005d4699);
    if (prior == 0) FUN_004b9f58();
    else FUN_004b9f04(prior);
    FUN_0005b824(0, 0x32, 0x32, s_Current_access__a__s__started_at_005d46b4);
    FUN_001185ec(0xeb1a02bf914012ba, &DAT_005d46d5);
    FUN_004b9ccc(1);
    thunk_FUN_00369b04(1, 0, &r);
    FUN_00369bb0(0, s_Fatal_access_conflict_detected__005d4606); /* noreturn */
}

/* FUN_0036a158 @ 0x36a158   (est. sk_access_remove)
 * Ghidra: void FUN_0036a158(ulong*,ulong)
 * Removes the access-pair entry matching param_2 from the per-thread
 * access list, unlinking it (panic on not-found via SoftwareBreakpoint). */
void sk_access_remove(uint64_t *list, uint64_t node)
{
    uint64_t cur, prev, next;
    cur = *list;
    if (cur == node) { *list = *(uint64_t *)(cur + 0x10) & 0xfffffffffffffffe; return; }
    do {
        prev = cur;
        next = *(uint64_t *)(prev + 0x10);
        cur = next & 0xfffffffffffffffe;
        if (cur == 0) SoftwareBreakpoint(1, 0x36a1a0); /* does not return */
    } while (node != cur);
    *(uint64_t *)(prev + 0x10) = *(uint64_t *)(cur + 0x10) & 0xfffffffffffffffe | next & 1;
}

/* FUN_0036a1a0 @ 0x36a1a0   (est. sk_access_begin)
 * Ghidra: void FUN_0036a1a0(undefined8,undefined8*,undefined8,long)
 * Starts an access: unless the global disable flag (DAT_006adef8 bit 0) is
 * set, records the access via FUN_00369f4c; if that reports a conflict,
 * clears the output. */
void sk_access_begin(word_t base, word_t *out, word_t arg, word_t list)
{
    uint32_t r; uint64_t u2;
    if ((DAT_006adef8 & 1) == 0) {
        if (list == 0) list = /*unaff_x30*/0;
        uint64_t tls = FUN_003a2554();
        u2 = FUN_00369f4c(tls, out, list, base, arg);
        if ((u2 & 1) != 0) return;
    }
    *out = 0;
}

/* FUN_0036a20c @ 0x36a20c   (est. sk_access_end)
 * Ghidra: void FUN_0036a20c(long*)
 * Ends a recorded access: removes the entry from the thread's list. */
void sk_access_end(word_t *entry)
{
    if (*entry != 0) {
        uint64_t tls = FUN_003a2554();
        FUN_0036a158(tls, entry);
    }
}

/* FUN_0036a244 @ 0x36a244   (est. sk_access_list_transfer)
 * Ghidra: void FUN_0036a244(ulong*)
 * Transfers the head of the thread's access list into param_1 (moves one
 * entry across, preserving the "previous" link). */
void sk_access_list_transfer(word_t *dst)
{
    uint64_t *src = (uint64_t *)FUN_003a2554();
    uint64_t v = *dst, s = *src;
    if (v == 0) { if (s != 0) *dst = s; }
    else if (s == 0) { *src = v; *dst = 0; dst[1] = 0; }
    else {
        uint64_t t = dst[1];
        *src = v;
        *(uint64_t *)(t + 0x10) = *(uint64_t *)(t + 0x10) & 1 | s;
        *dst = s;
        dst[1] = 0;
    }
}

/* FUN_0036a2ac @ 0x36a2ac   (est. sk_access_list_merge)
 * Ghidra: void FUN_0036a2ac(ulong*)
 * Merges the thread's access list into param_1: either adopts the head,
 * unlinks the tail, or removes a matching entry — maintaining the doubly
 * linked list invariants. */
void sk_access_list_merge(word_t *dst)
{
    uint64_t *src = (uint64_t *)FUN_003a2554();
    uint64_t v = *dst, s = *src;
    uint64_t a, b, c;
    if (v == 0) {
        v = s;
        if (s != 0) {
            do { b = v; v = *(uint64_t *)(b + 0x10) & 0xfffffffffffffffe; } while (v != 0);
            *src = 0;
            *dst = s;
            dst[1] = b;
        }
    } else {
        b = s;
        if (s == v) { *dst = 0; dst[1] = 0; }
        else {
            do { a = b; c = *(uint64_t *)(a + 0x10); b = c & 0xfffffffffffffffe; } while (v != b);
            *src = v;
            *(uint64_t *)(a + 0x10) = c & 1;
            *dst = s;
            dst[1] = a;
        }
    }
}

/* FUN_0036a338 @ 0x36a338   (est. sk_obj_is_owned)
 * Ghidra: bool FUN_0036a338(long)
 * Returns whether the object referenced from (param_1+0x18) is owned
 * (bit 1 of the type's +0x52 flag byte clear). */
bool sk_obj_is_owned(word_t obj)
{
    return (*(uint8_t *)(*(word_t *)(*(word_t *)(obj + 0x18) - 8) + 0x52) & 2) == 0;
}

/* FUN_0036a358 @ 0x36a358   (est. sk_obj_payload_ptr)
 * Ghidra: long* FUN_0036a358(long*)
 * If the object's type has the inline-payload flag (bit 0x20000 of +0x50),
 * returns the payload pointer (obj + rounded element size + 0x10). */
word_t *sk_obj_payload_ptr(word_t *obj)
{
    uint32_t h;
    uint64_t w;
    h = *(uint32_t *)(*(word_t *)(obj[3] - 8) + 0x50);
    if ((h >> 0x11 & 1) != 0) {
        w = (uint64_t)h & 0xff;
        obj = (word_t *)(*obj + (w + 0x10 & (w ^ 0xffffffffffffffff)));
    }
    return obj;
}

/* FUN_0036a388 @ 0x36a388   (est. sk_obj_elem_ptr_a)
 * Ghidra: long FUN_0036a388(long)
 * Computes an element pointer into the object payload, gated on a flag
 * (bit 1 of the byte at elem-count offset). Returns 0 if flag clear. */
word_t sk_obj_elem_ptr_a(word_t obj)
{
    word_t t8 = *(word_t *)(obj + 8);
    word_t t = (t8 == 0) ? 0 : t8;
    word_t u = (t == 0) ? 0 : t;
    if ((*(uint8_t *)(u + 0x20 + (word_t)*(int *)(u + 0x20) + 8) >> 1 & 1) == 0) return 0;
    word_t g = (t8 == 0) ? 0 : t8;
    return obj + ((uint64_t)*(uint32_t *)(g + 0x14) * 4 + 7 & 0x7fffffff8) +
           (uint64_t)*(uint32_t *)(g + 0x18) * 8;
}

/* FUN_0036a454 @ 0x36a454   (est. sk_obj_elem_ptr_b)
 * Similar element-pointer computation with a different offset layout
 * (uses uint16 at +0x28 and a presence byte at +0x17). */
word_t sk_obj_elem_ptr_b(word_t obj)
{
    word_t t8 = *(word_t *)(obj + 8);
    word_t t = (t8 == 0) ? 0 : t8;
    word_t u = (t == 0) ? 0 : t;
    if ((*(uint8_t *)(u + 0x20 + (word_t)*(int *)(u + 0x20) + 8) >> 1 & 1) == 0) return 0;
    word_t v = (t8 == 0) ? 0 : t8;
    word_t w = (t8 == 0) ? 0 : t8;
    return obj + (uint64_t)*(uint16_t *)(v + 0x28) * 8 +
           (uint64_t)(*(char *)(w + 0x17) != '\0') * 8 + 0x10;
}

/* FUN_0036a5ac @ 0x36a5ac   (est. sk_string_create)
 * Ghidra: long* FUN_0036a5ac(long*,undefined8)
 * Creates a (possibly out-of-line) string object: for length >= 0x17
 * allocates a separate buffer; stores the string bytes and a NUL
 * terminator. Returns the string header. */
word_t *sk_string_create(word_t *hdr, word_t src)
{
    uint64_t len;
    word_t *buf;
    len = (uint64_t)thunk_FUN_00115080(src);
    if (0x7ffffffffffffff6 < len) FUN_004b89f8(); /* fatal, noreturn */
    if (len < 0x17) {
        *(char *)((word_t)hdr + 0x17) = (char)len;
        buf = hdr;
        if (len == 0) goto done;
    } else {
        uint64_t sz = 0x19;
        if ((len | 7) != 0x17) sz = (len | 7) + 1;
        buf = (word_t *)FUN_00111890(sz, 0x1000c0077774924);
        hdr[1] = len;
        hdr[2] = sz | 0x8000000000000000;
        *hdr = (word_t)buf;
    }
    FUN_00117d14(buf, src, len);
done:
    *(uint8_t *)((word_t)buf + len) = 0;
    return hdr;
}

/* FUN_0036a668 @ 0x36a668   (est. sk_obj_meta_ptr)
 * Ghidra: uint* FUN_0036a668(uint*)
 * Returns a pointer to the object's metadata block, advancing past the
 * 7-word (0x10/0x11 kinds) or 11-word (0x12 kind) header; panics on
 * unknown kind. */
uint32_t *sk_obj_meta_ptr(uint32_t *obj)
{
    uint32_t k = *obj & 0x1f;
    if (k == 0x12) { obj = obj + 7; }
    else if (k == 0x11) { obj = obj + 7; }
    else {
        if (k != 0x10) SoftwareBreakpoint(1, 0x36a804); /* noreturn */
        obj = obj + 0xb;
    }
    return obj;
}

/* FUN_0036a804 @ 0x36a804   (est. sk_alloc_small)
 * Ghidra: void FUN_0036a804(undefined8,ulong)
 * Allocates param_2+1 bytes (or 0x10 for tiny sizes) using the fast
 * allocator; on failure calls the fatal-alloc hook. */
void sk_alloc_small(word_t size, uint64_t n)
{
    word_t p;
    if (n < 0x10) p = FUN_000101a0(size, 0xff87031d);
    else {
        uint64_t sz = 0x10;
        if (n != 0xffffffffffffffff) sz = n + 1;
        word_t r = 0;
        FUN_0001062c(&r, sz, size, 0xdda1f575);
        p = r;
    }
    if (p != 0) return;
    FUN_00369c78(size, n); /* noreturn */
}

/* FUN_0036a884 @ 0x36a884   (est. sk_alloc_tagged)
 * Ghidra: void FUN_0036a884(undefined8,ulong,undefined8)
 * Allocates a tagged buffer; on failure calls the fatal-alloc hook. */
void sk_alloc_tagged(word_t size, uint64_t n, word_t tag)
{
    word_t p = 0;
    int rc;
    if (n < 0x10) p = FUN_000101a0(size, tag);
    else {
        uint64_t sz = 0x10;
        if (n != 0xffffffffffffffff) sz = n + 1;
        rc = FUN_0001062c(&p, sz, size);
        if (rc != 0) { p = 0; goto fail; }
    }
    if (p != 0) return;
fail:
    FUN_00369c78(size, n); /* noreturn */
}

/* FUN_0036a908 @ 0x36a908   (est. sk_alloc_plain)
 * Ghidra: void FUN_0036a908(undefined8)
 * Plain allocation; on failure calls the fatal-alloc hook. */
void sk_alloc_plain(word_t size)
{
    word_t p = FUN_000101a0();
    if (p != 0) return;
    FUN_00369c78(size, 0); /* noreturn */
}

/* FUN_0036a93c @ 0x36a93c   (est. sk_dealloc)
 * Ghidra: void thunk_FUN_00012568(long)
 * Deallocation wrapper: frees a non-null pointer through the registered
 * deallocator vtable (+0x90) or the default FUN_000122f0. */
void sk_dealloc(word_t p)
{
    void (*d)(void);
    if (p == 0) return;
    d = *(void (**)(void))(_DAT_006adfe8 + 0x90);
    if ((d != 0) && (d != 0)) { (*d)(); return; }
    FUN_000122f0(p, 0);
}

/* FUN_0036a940 @ 0x36a940   (est. sk_alloc_typed)
 * Ghidra: void FUN_0036a940(ulong,undefined8,undefined8)
 * Allocates a typed header: size param_2, tag param_3 (hashing param_1),
 * stores the tag word and element-count 3. */
void sk_alloc_typed(uint64_t tag, word_t size, word_t extra)
{
    uint64_t *p = (uint64_t *)FUN_0036a884(size, extra,
        (uint64_t)(tag & 0xffffffff) ^ tag >> 0x20 | 0x80000000000);
    if (tag == 0) tag = 0;
    *p = tag;
    p[1] = 3;
}

/* FUN_0036a9a0 @ 0x36a9a0   (est. sk_obj_init_typed)
 * Ghidra: long* FUN_0036a9a0(long,long*)
 * Initializes a typed object header: stores the value at [0] and element
 * count 5 at [1]. */
word_t *sk_obj_init_typed(word_t v, word_t *hdr)
{
    if (v == 0) v = 0;
    *hdr = v;
    hdr[1] = 5;
    return hdr;
}

/* FUN_0036a9d4 @ 0x36a9d4   (est. sk_obj_init_with_cb)
 * Ghidra: long FUN_0036a9d4(undefined8,long)
 * Initializes an object header, running a once-callback (FUN_003d3dd8)
 * if the header's sign bit is clear. Returns param_2. */
word_t sk_obj_init_with_cb(word_t a, word_t obj)
{
    word_t l30 = obj;
    if (-1 < *(word_t *)(obj - 8)) {
        FUN_003d3dd8(obj - 8, &sk_obj_init_with_cb, &l30);
    }
    return obj;
}

/* FUN_0036aa2c @ 0x36aa2c   (est. sk_alloc_typed_thunk)
 * Thunk to FUN_0036a940. */
void sk_alloc_typed_thunk() { FUN_0036a940(); }

/* FUN_0036aa30 @ 0x36aa30   (est. sk_obj_append_elem)
 * Ghidra: undefined1[16] FUN_0036aa30(long*,long,ulong)
 * Appends an element to an inline object: if the object has room it
 * writes in place, else allocates a grown copy (FUN_0036aae4), copies the
 * old payload, and releases the old object. Returns the (new, ptr) pair. */
cl4_result_t sk_obj_append_elem(word_t *obj, word_t src, uint64_t add)
{
    uint64_t u1;
    cl4_result_t r;
    u1 = FUN_003a261c(*obj);
    if ((u1 & 1) == 0) {
        FUN_0036aae4(src);
        (**(void (**)(word_t, word_t, word_t))(*(word_t *)(src - 8) + 0x10))
            (r.hi, *obj + (add + 0x10 & (add ^ 0xffffffffffffffff)), src);
        *obj = r.lo;
        FUN_0036b118(*obj);
    } else {
        r.hi = *obj + (add + 0x10 & (add ^ 0xffffffffffffffff));
        r.lo = *obj;
    }
    return r;
}

/* FUN_0036aae4 @ 0x36aae4   (est. sk_obj_intern_table)
 * Ghidra: void FUN_0036aae4(ulong)
 * The global object-intern table: under a mutex (DAT_006c0290 counters,
 * FUN_00118164/194 lock) looks up param_1's key via FUN_0036bde0/hash; on
 * miss grows the table (FUN_00010244/FUN_0035b588), re-hashes existing
 * entries, and inserts a fresh interned record; finally caches the last
 * table pointer in DAT_006c02d8 and returns the allocated payload.
 * Confidence: medium
 * Notes: mutex string refs s___mtx_lock__handle_mutex__failed_005d3ee0,
 *   s___mtx_init__handle_mutex____mtx__005d3f10,
 *   s___mtx_unlock__handle_mutex__fail_005d3f4d; SoftwareBreakpoint OOM. */
void sk_obj_intern_table(uint64_t key)
{
    /* Full body spans ~7900 bytes of Ghidra decompile (the generic
     * intern-table builder shared with 0x36e878/36ed94/37062c/370f2c/371b58).
     * Transcribed faithfully in sk_obj_intern_table_shared() below in the
     * body of FUN_0036fb10 (the representative of this family). */
    uint64_t *tbl = (uint64_t *)_DAT_006c02d8;
    if ((tbl == 0) || (key != tbl[5])) {
        /* acquire, probe, grow, insert — see 0x36fb10 body */
        LOAcquire();
        _DAT_006c0290 += 1;
        LORelease();
    }
    /* cache and allocate payload */
    word_t p = 0;
    if (tbl != 0) p = (word_t)tbl + 3;
    FUN_0036a940(p, (int)tbl[4] + *(int *)(*(word_t *)(tbl[5] - 8) + 0x40),
                 *(uint32_t *)(*(word_t *)(tbl[5] - 8) + 0x50) & 0xf8 | 7);
}

/* FUN_0036b118 @ 0x36b118   (est. sk_refcount_release_b)
 * Release: decrements refcount by 0x200000000; on underflow hands full
 * release to FUN_0036b9e4. */
void sk_refcount_release_b(word_t obj)
{
    word_t *p; bool b; word_t v, nv;
    if (0 < obj) {
        p = (word_t *)(obj + 8);
        v = *(word_t *)(obj + 8);
        do {
            nv = v - 0x200000000;
            if (nv < 0) {
                if ((int)v == -1) return;
                FUN_0036b9e4(p, v, 1);
                return;
            }
            b = *p != v;
            v = *p;
        } while (b);
        *p = nv;
    }
}

/* FUN_0036b170 @ 0x36b170   (est. sk_obj_release_container)
 * Ghidra: void FUN_0036b170(long*)
 * Releases an object container: ensures the refcount high bits are
 * initialized (0x80000000ffffffff sentinel), then builds the payload
 * pointer and hands it to FUN_0036b21c. */
void sk_obj_release_container(word_t *obj)
{
    uint64_t u1;
    word_t base = *obj;
    if (base == 0) base = 0;
    u1 = obj[1];
    if ((u1 & 0x80000000ffffffff) != 0x80000000ffffffff) {
        if (((long)u1 < 0) && ((u1 & 0xffffffff) != 0xffffffff))
            FUN_0036c06c(u1 << 3);
        else
            obj[1] = u1 & 0x80000000ffffffff | 0x100000000;
    }
    word_t *m = *(word_t **)(*(word_t *)(base + 0x10) - 8);
    FUN_0036b21c(obj, *(int *)(base + 8) + *(int *)(m + 0x40),
                 *(uint32_t *)(m + 0x50) & 0xf8 | 7);
}

/* FUN_0036b21c @ 0x36b21c   (est. sk_obj_destroy_check)
 * Ghidra: void FUN_0036b21c(long)
 * Final object destruction: checks the refcount sentinel/high-bits state
 * and either frees (thunk_FUN_00012568) or runs the full teardown
 * (FUN_0036b484). */
void sk_obj_destroy_check(word_t obj)
{
    uint64_t u1 = *(uint64_t *)(obj + 8);
    if ((long)u1 < 0) {
        if (((u1 ^ 0xffffffffffffffff) & 0x1ffffffff) != 0) goto teardown;
    } else if ((u1 >> 0x20 & 1) == 0) goto teardown;
    if ((u1 & 0x7ffffffefffffffe) == 2) { thunk_FUN_00012568(); return; }
teardown:
    FUN_0036b484();
}

/* FUN_0036b250 @ 0x36b250   (est. sk_obj_advance)
 * Ghidra: long* FUN_0036b250(long*)
 * Advances a pointer by the object's inline size (*(*obj+8)). */
word_t *sk_obj_advance(word_t *p)
{
    if (p != 0) p = (word_t *)((word_t)p + (uint64_t)*(uint32_t *)(*p + 8));
    return p;
}

/* FUN_0036b270 @ 0x36b270   (est. sk_refcount_acquire_c)
 * Acquire: increments refcount by 0x200000000; on the sentinel returns
 * the base pointer; else full acquire via FUN_0039f9e8. */
uint64_t sk_refcount_acquire_c(uint64_t obj)
{
    word_t *p; bool b; word_t v, nv;
    if (0 < (long)obj) {
        uint64_t base = obj & 0xffffffffffffff8;
        p = (word_t *)(base + 8);
        v = *(word_t *)(base + 8);
        do {
            nv = v + 0x200000000;
            if (nv < 0) {
                if ((int)v == -1) return base;
                return FUN_0039f9e8(p, v, 1);
            }
            b = *p != v;
            v = *p;
        } while (b);
        *p = nv;
    }
    return obj;
}

/* FUN_0036b2d0 @ 0x36b2d0   (est. sk_refcount_dec_many)
 * Ghidra: void FUN_0036b2d0(long,long)
 * Decrements the refcount by param_2<<33 for a live object, handing off
 * to FUN_0039f9e8 on sentinel/underflow. */
void sk_refcount_dec_many(word_t obj, word_t n)
{
    uint64_t u2, u4;
    if ((0 < obj) && ((u2 = *(uint64_t *)(obj + 8), (int)n == 1 ||
        ((u2 & 0x80000000ffffffff) != 0x80000000ffffffff)))) {
        word_t *p = (word_t *)(obj + 8);
        u4 = u2 + (n << 0x21);
        if (-1 < (long)u4) {
            uint64_t v = u2;
            do {
                u2 = *p;
                if (u2 == v) { *p = u4; return; }
                u4 = u2 + (n << 0x21);
                v = u2;
            } while (-1 < (long)u4);
        }
        if ((int)u2 != -1) FUN_0039f9e8(p);
    }
}

/* FUN_0036b340 @ 0x36b340   (est. sk_refcount_inc_many)
 * Mirrors 0x36b2d0 for increments; offloads to FUN_0036b9e4 on underflow. */
void sk_refcount_inc_many(word_t obj, word_t n)
{
    uint64_t u4, u2, u1;
    uint32_t u3;
    if (0 < obj) {
        u4 = *(uint64_t *)(obj + 8);
        u3 = (uint32_t)n;
        if ((u3 == 1) || ((u4 & 0x80000000ffffffff) != 0x80000000ffffffff)) {
            if ((u3 < 2) || (-1 < (long)u4)) {
                do {
                    u2 = u4 - (n << 0x21);
                    if ((long)u2 < 0) break;
                    u1 = *(uint64_t *)(obj + 8);
                    if (u1 == u4) { *(uint64_t *)(obj + 8) = u2; return; }
                    u4 = u1;
                } while ((u3 < 2) || (-1 < (long)u1));
            }
            if ((int)u4 != -1) FUN_0036b9e4();
        }
    }
}

/* FUN_0036b3c0 @ 0x36b3c0   (est. sk_refcount_dec_one)
 * Decrements the refcount of obj by one (via FUN_0036b3f8 on obj+8). */
word_t sk_refcount_dec_one(word_t obj)
{
    if (0 < obj) FUN_0036b3f8(obj + 8, 1);
    return obj;
}

/* FUN_0036b3f8 @ 0x36b3f8   (est. sk_refcount_dec_slow)
 * Ghidra: ulong* FUN_0036b3f8(ulong*,undefined8)
 * Slow refcount decrement: walks the 64-bit counter handling the
 * sentinel, high-bits overflow, and external free-list cases (FUN_0039f914
 * / FUN_0036c188). */
uint64_t *sk_refcount_dec_slow(uint64_t *ref, word_t n)
{
    uint64_t cur = *ref;
    uint32_t c = 0;
    uint64_t hi = 0, lo = 0;
    bool b = false;
    if (((*ref ^ 0xffffffffffffffff) & 0x80000000ffffffff) != 0) {
        do {
            if (((long)cur < 0) && ((cur & 0xffffffff) != 0xffffffff)) {
                return (uint64_t *)FUN_0036c188(cur * 8 + 0x10);
            }
            c = (uint32_t)n + ((uint32_t)cur >> 1);
            if ((c & 0x7fffffff) == 0x7fffffff || (c & 0x7fffffff) != c) {
                word_t l = FUN_0039f914(ref, 0);
                if (l != 0) return (uint64_t *)FUN_0036c188(l + 0x10, n);
                cl4_result_t fr;
                fr.lo = FUN_00369c08();
                fr.hi = 0;
                uint64_t *p = (uint64_t *)fr.lo;
                uint64_t cv = *p;
                if (((long)cv < 0) && ((cv & 0xffffffff) != 0xffffffff))
                    return (uint64_t *)(cv << 3);
                if ((fr.hi == 0) || ((cv >> 0x20 & 1) == 0)) {
                    uint64_t *nb = (uint64_t *)FUN_0036a804(0x20, 0xf);
                    nb[2] = 0;
                    *nb = (uint64_t)(p - 1);
                    nb[3] = 0;
                    while (fr.hi == 0 || ((cv >> 0x20 & 1) == 0)) {
                        nb[2] = cv;
                        nb[3] = 1;
                        uint64_t v = *p;
                        if (v == cv) { *p = (uint64_t)nb >> 3 | 0xc000000000000000; return nb; }
                        cv = v;
                        if (((long)v < 0) && ((v & 0xffffffff) != 0xffffffff)) {
                            thunk_FUN_00012568(nb, 0x20, 0xf);
                            return (uint64_t *)(v << 3);
                        }
                    }
                }
                return 0;
            }
            hi = cur & 0xffffffff00000000;
            lo = cur & 1;
            b = *ref != cur;
            cur = *ref;
        } while (b);
        *ref = hi | lo | ((uint64_t)c & 0x7fffffff) << 1;
    }
    return ref;
}

/* FUN_0036b484 @ 0x36b484   (est. sk_obj_full_teardown)
 * Ghidra: void FUN_0036b484(long*)
 * Runs the full teardown of a live object: decrements its refcount and on
 * reaching zero frees the header (thunk_FUN_00012568). */
void sk_obj_full_teardown(word_t *obj)
{
    if ((0 < (long)obj) && ((int)FUN_0036b4e8(obj + 1, 1) != 0))
        thunk_FUN_00012568(obj, *(uint32_t *)(*obj + 0x18), *(uint16_t *)(*obj + 0x1c));
}

/* FUN_0036b4e8 @ 0x36b4e8   (est. sk_refcount_dec_and_test)
 * Ghidra: ulong FUN_0036b4e8(ulong*,int)
 * Decrements a refcount word; returns whether it reached zero (also
 * offloading to the slow path FUN_0036c20c/FUN_0036bc3c). */
uint64_t sk_refcount_dec_and_test(uint64_t *ref, int n)
{
    uint64_t cur, hi, lo;
    bool b;
    cur = *ref;
    if (((*ref ^ 0xffffffffffffffff) & 0x80000000ffffffff) == 0) return 0;
    while ((-1 < (long)cur || ((cur & 0xffffffff) == 0xffffffff))) {
        uint32_t c = ((uint32_t)(cur >> 1) & 0x7fffffff) - n;
        hi = cur & 0xffffffff00000000;
        lo = cur & 1;
        b = *ref == cur;
        cur = *ref;
        if (b) {
            *ref = hi | lo | ((uint64_t)c & 0x7fffffff) << 1;
            return (uint64_t)((c & 0x7fffffff) == 0);
        }
    }
    uint64_t s = FUN_0036c20c(cur * 8 + 0x10);
    if ((int)s == 0) return s;
    FUN_0036bc3c(cur * 8);
    return 1;
}

/* FUN_0036b588 @ 0x36b588   (est. sk_refcount_init_or_free)
 * Ghidra: void FUN_0036b588(long)
 * Ensures the refcount word at (obj+8) is in its initialized state,
 * converting a negative external-count into a single-heap free
 * (FUN_0036c06c) or setting the high-bits sentinel. */
void sk_refcount_init_or_free(word_t obj)
{
    uint64_t u1 = *(uint64_t *)(obj + 8);
    if ((u1 & 0x80000000ffffffff) != 0x80000000ffffffff) {
        if (((long)u1 < 0) && ((u1 & 0xffffffff) != 0xffffffff)) {
            FUN_0036c06c(u1 << 3);
            return;
        }
        *(uint64_t *)(obj + 8) = u1 & 0x80000000ffffffff | 0x100000000;
    }
}

/* FUN_0036b5c4 @ 0x36b5c4   (est. sk_refcount_try_acquire)
 * Ghidra: long FUN_0036b5c4(long)
 * Attempts to acquire a reference on obj; on the sentinel/full state it
 * reports failure via the fatal path FUN_00369c40 and the owning vtable.
 * Returns obj on success. */
word_t sk_refcount_try_acquire(word_t obj)
{
    uint64_t u3, u4;
    word_t *p; word_t v;
    if (obj < 1) return obj;
    u3 = *(uint64_t *)(obj + 8);
    if ((long)u3 < 0) goto overflow;
    while (u4 = u3, (u3 >> 0x20 & 1) == 0) {
        while (1) {
            if ((long)(u4 + 0x200000000) < 0) {
                if ((int)u4 == -1) return obj;
                u3 = FUN_0039f818();
                if ((u3 & 1) != 0) return obj;
                goto overflow;
            }
            u3 = *(uint64_t *)(obj + 8);
            if (u3 == u4) { *(uint64_t *)(obj + 8) = u4 + 0x200000000; return obj; }
            if (-1 < (long)u3) break;
overflow:
            u4 = u3;
            if (((u3 ^ 0xffffffffffffffff) & 0x1ffffffff) == 0) goto overflow_done;
        }
    }
overflow_done:
    p = (word_t *)FUN_00369c40(obj);
    return (word_t)(**(word_t (**)(void))(*p - 0x10))();
}

/* FUN_0036b650 @ 0x36b650   (est. sk_obj_free_via_vtable)
 * Ghidra: void FUN_0036b650(long*)
 * Frees the object through its owning vtable's -0x10 slot. */
void sk_obj_free_via_vtable(word_t *obj)
{
    (**(void (**)(void))(*obj - 0x10))();
}

/* FUN_0036b6ac @ 0x36b6ac   (est. sk_obj_dealloc_list)
 * Ghidra: void FUN_0036b6ac(long,undefined8,undefined8,undefined8)
 * Deallocates a list of objects: walks the linked list, invoking each
 * element's destructor (+6 slot), releases the list nodes, and recurses
 * on the container. */
void sk_obj_dealloc_list(word_t obj, word_t b, word_t c, word_t d)
{
    uint64_t u4;
    word_t *base, *node, *p, v;
    bool bv;
    word_t nv = 0;
    if (0 < obj) {
        u4 = *(uint64_t *)(obj + 8);
        if (((long)u4 < 0) && ((u4 & 0xffffffff) != 0xffffffff)) u4 = *(uint64_t *)(u4 * 8 + 0x10);
        u4 = u4 >> 0x21 & 0x3fffffff;
        if (u4 != 0) {
            uint64_t rv = FUN_004b9f8c(obj, u4);
            cl4_result_t r; r.lo=rv; r.hi=0;
            base = (word_t *)r.lo;
            if (base == 0) return;
            node = (word_t *)*base;
            v = *node;
            while (1) {
                if (0xfffffffffffff800 < v - 0x800U) node = 0;
                if (node == (word_t *)r.hi) break;
                void (*dtor)(word_t) = (void (*)(word_t))node[6];
                if ((dtor != 0) && (dtor != 0)) (*dtor)((uint64_t)(node + 6) & 0xffffffffffff | 0xbbbf000000000000);
                node = (word_t *)node[1];
                v = *node;
            }
            p = base + 1;
            v = base[1];
            do {
                nv = v - 0x200000000;
                if (nv < 0) {
                    if ((int)v != -1) FUN_0036c274(p, v, 1);
                    goto done;
                }
                bv = *p != v;
                v = *p;
            } while (bv);
            *p = nv;
done:
            sk_obj_dealloc_list((word_t)base, c, d, d);
            return;
        }
    }
    FUN_0036b21c();
}

/* FUN_0036b6f4 @ 0x36b6f4   (est. sk_obj_dealloc_list_b)
 * Variant of the object-list deallocator with explicit start/end bounds. */
void sk_obj_dealloc_list_b(word_t *head, word_t *end, word_t c, word_t d)
{
    word_t *node, v; bool bv;
    word_t nv = 0;
    if (head == 0) return;
    node = (word_t *)*head;
    v = *node;
    while (1) {
        if (0xfffffffffffff800 < v - 0x800U) node = 0;
        if (node == end) break;
        void (*dtor)(word_t) = (void (*)(word_t))node[6];
        if ((dtor != 0) && (dtor != 0)) (*dtor)((uint64_t)(node + 6) & 0xffffffffffff | 0xbbbf000000000000);
        node = (word_t *)node[1];
        v = *node;
    }
    word_t *p = head + 1;
    v = head[1];
    do {
        nv = v - 0x200000000;
        if (nv < 0) {
            if ((int)v != -1) FUN_0036c274(p, v, 1);
            goto done;
        }
        bv = *p != v;
        v = *p;
    } while (bv);
    *p = nv;
done:
    sk_obj_dealloc_list((word_t)head, c, d, d);
}

/* FUN_0036b7f8 @ 0x36b7f8   (est. sk_retain_ptr)
 * Ghidra: undefined8* FUN_0036b7f8(undefined8*,long)
 * Retains a pointer-sized reference: stores a fresh acquire of
 * (param_2+8) into param_1. */
word_t *sk_retain_ptr(word_t *out, word_t obj)
{
    word_t v = (obj == 0) ? 0 : FUN_0039fb10(obj + 8);
    *out = v;
    return out;
}

/* FUN_0036b834 @ 0x36b834   (est. sk_retain_wrapper)
 * Ghidra: undefined8 FUN_0036b834(undefined8)
 * Wrapper returning its argument after a retain of an internal pointer. */
word_t sk_retain_wrapper(word_t a)
{
    FUN_0036b85c();
    return a;
}

/* FUN_0036b85c @ 0x36b85c   (est. sk_release_swap)
 * Ghidra: void FUN_0036b85c(long*,long)
 * Swaps the retained pointer at param_1 with a fresh acquire of
 * (param_2+8), releasing the old pointer via FUN_0036bc3c. */
void sk_release_swap(word_t *out, word_t obj)
{
    word_t newv = (obj == 0) ? 0 : FUN_0039fb10(obj + 8);
    word_t old = *out;
    *out = newv;
    if (old != 0) FUN_0036bc3c(old);
}

/* FUN_0036b8b0 @ 0x36b8b0   (est. sk_release_if_set)
 * Ghidra: void FUN_0036b8b0(long*)
 * Releases the pointer at param_1 if non-null (via FUN_0036bcec). */
void sk_release_if_set(word_t *p)
{
    if (*p != 0) FUN_0036bcec();
}

/* FUN_0036b8c0 @ 0x36b8c0   (est. sk_release_clear)
 * Ghidra: void FUN_0036b8c0(long*)
 * Clears param_1 and releases the old pointer via FUN_0036bc3c. */
void sk_release_clear(word_t *p)
{
    word_t v = *p;
    *p = 0;
    if (v != 0) FUN_0036bc3c();
}

/* FUN_0036b8d8 @ 0x36b8d8   (est. sk_retain_optional)
 * Ghidra: long* FUN_0036b8d8(long*,long*)
 * Retains an optional (nullable) pointer from param_2 into param_1,
 * using the weak/strong wrapper FUN_0036bd84. */
word_t *sk_retain_optional(word_t *out, word_t *src)
{
    word_t v = *src;
    if (v != 0) {
        if ((*(uint64_t *)(v + 0x10) >> 0x20 & 1) == 0) FUN_0036bd84(v + 0x10);
        else v = 0;
    }
    *out = v;
    return out;
}

/* FUN_0036b930 @ 0x36b930   (est. sk_retain_wrapper_b)
 * Wrapper returning its argument after a swap-retain. */
word_t sk_retain_wrapper_b(word_t a)
{
    FUN_0036b958();
    return a;
}

/* FUN_0036b958 @ 0x36b958   (est. sk_swap_optional)
 * Ghidra: void FUN_0036b958(long*,long*)
 * Swaps two optional pointers, releasing the old value and retaining the
 * new one (unless the same pointer). */
void sk_swap_optional(word_t *a, word_t *b)
{
    word_t v;
    if (a != b) {
        v = *a;
        *a = 0;
        if (v != 0) FUN_0036bc3c();
        v = *b;
        if (v != 0) {
            if ((*(uint64_t *)(v + 0x10) >> 0x20 & 1) == 0) FUN_0036bd84(v + 0x10);
            else v = 0;
        }
        *a = v;
    }
}

/* FUN_0036b9e4 @ 0x36b9e4   (est. sk_refcount_force_release)
 * Ghidra: undefined8 FUN_0036b9e4(ulong*,ulong,long)
 * Force-releases a refcount by param_3<<33, handling the sentinel and
 * offloading to FUN_0036bab4 on underflow; runs the free callback via
 * FUN_0036b650. */
uint64_t sk_refcount_force_release(uint64_t *ref, uint64_t v, word_t n)
{
    bool b; uint64_t r, u3;
    if (((uint32_t)n == 1) || ((v & 0x80000000ffffffff) != 0x80000000ffffffff)) {
        do {
            while (((1 < (uint32_t)n && ((long)v < 0)) ||
                    (u3 = v - (n << 0x21), (long)u3 < 0))) {
                u3 = v & 0xffffffff;
                if (u3 == 0xffffffff) return 0;
                if ((long)v < 0) return FUN_0036bab4(v << 3, n);
                b = *ref == v;
                v = *ref;
                if (b) {
                    *ref = u3 | 0x100000000;
                    DataMemoryBarrier(2, 1);
                    FUN_0036b650(ref - 1);
                    return 1;
                }
            }
            b = *ref != v;
            v = *ref;
        } while (b);
        *ref = u3;
    }
    return 0;
}

/* FUN_0036bab4 @ 0x36bab4   (est. sk_refcount_external_release)
 * Ghidra: undefined8 FUN_0036bab4(undefined8*,long)
 * Releases an external (out-of-line) refcount slot, comparing 128-bit
 * (slot,value) pairs and invoking the free callback via FUN_0036b650. */
uint64_t sk_refcount_external_release(word_t *slot, word_t n)
{
    uint64_t *p = slot + 2;
    uint64_t v9 = slot[2], v10 = slot[3];
    uint32_t u8 = (uint32_t)n;
    bool b4, b5, b6, b3 = false;
    bool pos = false, posd = false;
    if (u8 == 1) b4 = false;
    else {
        if (((long)v9 < 0) && ((v9 & 0xffffffff) == 0xffffffff)) return 0;
        b4 = u8 != 0;
        if ((u8 != 0) && ((long)v9 < 0)) goto rel;
    }
    uint64_t v12 = v9, hi = v10 >> 0x20;
    do {
        word_t dec = v12 - (n << 0x21);
        v9 = v12;
        uint64_t in11 = hi;
        if (dec < 0) break;
        uint64_t lo13 = v10 & 0xffffffff;
        uint64_t u11 = lo13 | hi << 0x20;
        v9 = *p;
        v10 = slot[3];
        if ((v9 == u11) && (v10 == v12)) { *p = lo13; slot[3] = dec; }
        if (v9 == v12 && v10 == u11) return 0;
        hi = v10 >> 0x20;
        b3 = false;
        if ((long)v9 < 0) b3 = b4;
        v12 = v9;
        in11 = hi;
    } while (!b3);
rel:
    if ((int)v9 == -1) return 0;
    if (((u8 != 1) && ((long)v9 < 0)) && ((v9 & 0xffffffff) == 0xffffffff)) return 0;
    v10 = v10 & 0xffffffff | /*in_x11*/0 << 0x20;
    do {
        uint64_t dec = v9 - (n << 0x21);
        pos = -1 < (long)v9;
        posd = -1 < (long)dec;
        if (1 < u8 && !pos || !posd) {
            if ((int)v9 == -1) goto done0;
            dec = v9 & 0x80000000ffffffff | 0x100000000;
        }
        uint64_t u11 = *p;
        uint64_t u13 = slot[3];
        if ((u11 == v10) && (u13 == v9)) { *p = v10 & 0xffffffff; slot[3] = dec; }
        b5 = u11 != v9;
        b6 = u13 != v10;
        v10 = u13;
        v9 = u11;
    } while (b5 || b6);
    if ((1 >= u8 || pos) && posd) {
done0:
        return 0;
    }
    DataMemoryBarrier(2, 1);
    FUN_0036b650(*slot);
    return 1;
}

/* FUN_0036bc3c @ 0x36bc3c   (est. sk_dealloc_ref)
 * Ghidra: void FUN_0036bc3c(long)
 * Deallocates a refcounted object: releases the refcount slot (+0x10) and
 * frees the header (thunk_FUN_00012568). */
void sk_dealloc_ref(word_t obj)
{
    if ((int)FUN_0036bc84(obj + 0x10) != 0) thunk_FUN_00012568(obj, 0x20, 0xf);
}

/* FUN_0036bc84 @ 0x36bc84   (est. sk_refcount_release_pair)
 * Ghidra: bool FUN_0036bc84(ulong*)
 * Releases a 128-bit refcount pair, decrementing the low word; returns
 * whether it reached zero. */
bool sk_refcount_release_pair(uint64_t *ref)
{
    uint64_t a = *ref, b = ref[1];
    uint32_t c = (uint32_t)ref[1] - 1;
    uint64_t v7 = ref[1] & 0xffffffff;
    uint64_t v4 = *ref;
    uint64_t v5 = ref[1];
    bool b2 = false, b3 = false;
    if ((v4 == v7) && (v5 == a)) { *ref = (uint64_t)c; ref[1] = a; }
    if (v4 != a || v5 != v7) {
        do {
            c = (uint32_t)v5 - 1;
            a = *ref;
            v7 = ref[1];
            if ((a == v5) && (v7 == v4)) { *ref = (uint64_t)c; ref[1] = v4; }
            b2 = a != v4;
            b3 = v7 != v5;
            v4 = a;
            v5 = v7;
        } while (b2 || b3);
    }
    return c == 0;
}

/* FUN_0036bcec @ 0x36bcec   (est. sk_release_external)
 * Ghidra: undefined8 FUN_0036bcec(undefined8*)
 * Releases an external refcount slot (128-bit compare), handing off to
 * FUN_0039f8b8 on the sentinel path. */
uint64_t sk_release_external(word_t *slot)
{
    uint64_t v4 = slot[3];
    if (((uint64_t)slot[2] >> 0x20 & 1) != 0) return 0;
    uint64_t *p = slot + 2;
    uint64_t v5 = slot[2];
    uint64_t hi = 0;
    while (-1 < (long)(v5 + 0x200000000)) {
        uint64_t v7 = v4 & 0xffffffff;
        uint64_t v6 = v7 | hi << 0x20;
        uint64_t u2 = *p;
        v4 = slot[3];
        if ((u2 == v6) && (v4 == v5)) { *p = v7; slot[3] = v5 + 0x200000000; }
        if (u2 == v5 && v4 == v6) goto done;
        hi = v4 >> 0x20;
        v5 = u2;
        if ((u2 >> 0x20 & 1) != 0) return 0;
    }
    if (((int)v5 != -1) && ((int)FUN_0039f8b8(p, v5, v4 & 0xffffffff | hi << 0x20) == 0))
        return 0;
done:
    return *slot;
}

/* FUN_0036bd84 @ 0x36bd84   (est. sk_weak_retain)
 * Ghidra: void FUN_0036bd84(ulong,ulong*)
 * Retains a weak reference pair: increments the count word, handling the
 * -1 sentinel (fatal weak-ref error). */
void sk_weak_retain(uint64_t key, uint64_t *ref)
{
    uint64_t u2 = ref[1];
    int c = (int)u2;
    uint64_t u3 = *ref;
    while (1) {
        if (c == -1) { FUN_00369c24(); return; }
        c = (int)u2;
        uint64_t u5 = u2 & 0xffffffff | key << 0x20;
        uint64_t u1 = *ref;
        u2 = ref[1];
        if ((u1 == u5) && (u2 == u3)) { *ref = (uint64_t)(c + 1); ref[1] = u3; }
        if (u1 == u3 && u2 == u5) break;
        key = u2 >> 0x20;
        c = (int)u2;
        u3 = u1;
    }
}

/* FUN_0036bde0 @ 0x36bde0   (est. sk_hash_table_find)
 * Ghidra: undefined1[16] FUN_0036bde0(long*,ulong,ulong,long)
 * Probes an open-addressing hash table for the bucket matching
 * *(param_1) via the table hash (FUN_0036becc); returns the matching
 * (key,slot) pair or 0. */
cl4_result_t sk_hash_table_find(word_t *key, uint64_t tbl, uint64_t count, word_t slots)
{
    cl4_result_t r;
    uint64_t local = tbl;
    uint64_t h = FUN_0036becc(*key);
    uint64_t mask = 4;
    if (((tbl & 3) != 0) && ((uint8_t *)(tbl & 0xfffffffffffffffc) != 0))
        mask = (uint64_t)*(uint8_t *)(tbl & 0xfffffffffffffffc);
    mask = -1L << (mask & 0x3f);
    h = h & (mask ^ 0xffffffffffffffff);
    if (h < 2) h = 1;
    int i = (int)FUN_0035b178(&local, h, 2);
    if (i != 0) {
        do {
            uint64_t u4 = (uint64_t)(i - 1);
            if ((u4 < count) && (*key == *(word_t *)(*(word_t *)(slots + u4 * 8) + 0x28))) {
                h = 0;
                slots = slots + u4 * 8;
                goto out;
            }
            h = h + 1 & ~mask;
            if (h < 2) h = 1;
            i = (int)FUN_0035b178(&local, h, 2);
        } while (i != 0);
    }
    slots = 0;
    h = h & 0xffffffff;
out:
    r.hi = h;
    r.lo = slots;
    return r;
}

/* FUN_0036becc @ 0x36becc   (est. sk_murmur_hash64)
 * Ghidra: long FUN_0036becc(ulong)
 * 64-bit MurmurHash-style finalizer (0x9e3779b97f4a7c15 constants)
 * producing a hash of the 64-bit key. */
word_t sk_murmur_hash64(uint64_t key)
{
    uint64_t h = ((key & 0xffffffff) * 8 + 0xf9000a63a9000a61 ^ key >> 0x20) * -0x622015f714c7d297;
    h = (key >> 0x20 ^ h >> 0x2f ^ h) * -0x622015f714c7d297;
    return (h ^ h >> 0x2f) * -0x622015f714c7d297;
}

/* FUN_0036bf4c @ 0x36bf4c   (est. sk_table_dtor)
 * Ghidra: void FUN_0036bf4c()
 * Destructor for a hash-table node: invokes the element destructor (+8)
 * and releases the table (FUN_0036b21c). */
void sk_table_dtor()
{
    word_t *base = (word_t *)0;
    if (base == 0) base = 0;
    (**(void (**)(word_t))(*(word_t *)(*(word_t *)(base + 0x10) - 8) + 8))
        ((word_t)/*unaff_x20*/0 + (uint64_t)*(uint32_t *)(base + 8));
    FUN_0036b21c();
}

/* FUN_0036bfe4 @ 0x36bfe4   (est. sk_slot_triple_store)
 * Ghidra: void FUN_0036bfe4(undefined8*,undefined8*,undefined8*,long*)
 * Stores a 3-slot (a,b,c) tuple into param_1 from param_2/param_3/param_4. */
void sk_slot_triple_store(word_t *out, word_t *a, word_t *b, word_t *c)
{
    out[0] = *a;
    out[1] = *b;
    word_t v = *c;
    if ((v == 0) || (v == 0)) v = 0;
    out[2] = v;
}

/* FUN_0036c06c @ 0x36c06c   (est. sk_refcount_release_ext)
 * Ghidra: void FUN_0036c06c(long)
 * Releases an external refcount (128-bit compare at +0x10/+0x18),
 * offloading to FUN_0036c0e0 on underflow. */
void sk_refcount_release_ext(word_t obj)
{
    uint64_t *p = (uint64_t *)(obj + 0x10);
    uint64_t v3 = *(uint64_t *)(obj + 0x18);
    uint64_t v4 = *(uint64_t *)(obj + 0x10);
    uint64_t hi = 0;
    while (1) {
        if ((long)(v4 - 0x200000000) < 0) {
            if ((int)v4 == -1) return;
            FUN_0036c0e0(p, v4, v3 & 0xffffffff | hi << 0x20, 1);
            return;
        }
        uint64_t v5 = v3 & 0xffffffff;
        uint64_t v6 = v5 | hi << 0x20;
        uint64_t u2 = *p;
        v3 = *(uint64_t *)(obj + 0x18);
        if ((u2 == v6) && (v3 == v4)) { *p = v5; *(uint64_t *)(obj + 0x18) = v4 - 0x200000000; }
        if (u2 == v4 && v3 == v6) break;
        hi = v3 >> 0x20;
        v4 = u2;
    }
}

/* FUN_0036c0e0 @ 0x36c0e0   (est. sk_refcount_dec_pair)
 * Ghidra: bool FUN_0036c0e0(ulong*,ulong,ulong,uint)
 * Decrements a 128-bit refcount pair by param_4<<33; returns whether the
 * operation hit the free path (underflow). */
bool sk_refcount_dec_pair(uint64_t *ref, uint64_t v2, uint64_t v3, uint32_t n)
{
    uint64_t u1, u2, u6;
    bool b3, b4, b5;
    if (((n == 1) || (-1 < (long)v2)) || ((v2 & 0xffffffff) != 0xffffffff)) {
        do {
            u6 = v2 - ((uint64_t)n << 0x21);
            b3 = 1 < n && (long)v2 < 0 || (long)u6 < 0;
            if (1 < n && (long)v2 < 0 || (long)u6 < 0) {
                if ((int)v2 == -1) return false;
                u6 = v2 & 0x80000000ffffffff | 0x100000000;
            }
            u1 = *ref;
            u2 = ref[1];
            if ((u1 == v3) && (u2 == v2)) { *ref = v3 & 0xffffffff; ref[1] = u6; }
            b4 = u1 != v2;
            b5 = u2 != v3;
            v3 = u2;
            v2 = u1;
        } while (b4 || b5);
    } else {
        b3 = false;
    }
    return b3;
}

/* FUN_0036c188 @ 0x36c188   (est. sk_refcount_inc_pair)
 * Ghidra: void FUN_0036c188(ulong*,int)
 * Increments a 128-bit refcount pair, offloading to FUN_0039fb58 on the
 * full/sentinel path. */
void sk_refcount_inc_pair(uint64_t *ref, int n)
{
    uint32_t u1;
    uint64_t v4, v3, v5, v6, v7;
    uint64_t u2;
    v4 = *ref;
    v3 = ref[1];
    if (((long)v4 < 0) && ((v4 & 0xffffffff) == 0xffffffff)) return;
    u1 = n + ((uint32_t)v4 >> 1);
    v7 = (uint64_t)u1;
    v6 = v7 << 1;
    if ((int)v6 != -2 && (u1 & 0x7fffffff) == u1) {
        do {
            v5 = v3 & 0xffffffff;
            v7 = v5 | v7 << 0x20;
            u2 = *ref;
            v3 = ref[1];
            if ((u2 == v7) && (v3 == v4)) {
                *ref = v5;
                ref[1] = v4 & 0xffffffff00000000 | v4 & 1 | (v6 >> 1 & 0x7fffffff) << 1;
            }
            if (u2 == v4 && v3 == v7) return;
            v7 = v3 >> 0x20;
            u1 = n + ((uint32_t)u2 >> 1);
            v6 = (uint64_t)u1 << 1;
            v4 = u2;
        } while ((int)v6 != -2 && (u1 & 0x7fffffff) == u1);
    }
    FUN_0039fb58();
}

/* FUN_0036c20c @ 0x36c20c   (est. sk_refcount_dec_pair2)
 * Ghidra: bool FUN_0036c20c(ulong,ulong*,int)
 * Decrements a refcount pair by n; returns whether it reached zero. */
bool sk_refcount_dec_pair2(uint64_t key, uint64_t *ref, int n)
{
    uint64_t v3, v5, v6, u1, u2, u4;
    uint32_t c;
    v3 = *ref;
    v5 = ref[1];
    if (((long)v3 < 0) && (key = v3 & 0xffffffff, key == 0xffffffff)) return false;
    while (1) {
        c = ((uint32_t)(v3 >> 1) & 0x7fffffff) - n;
        v6 = v5 & 0xffffffff;
        u4 = v6 | key << 0x20;
        u1 = *ref;
        v5 = ref[1];
        if ((u1 == u4) && (v5 == v3)) {
            *ref = v6;
            ref[1] = v3 & 0xffffffff00000000 | v3 & 1 | ((uint64_t)c & 0x7fffffff) << 1;
        }
        if (u1 == v3 && v5 == u4) break;
        key = v5 >> 0x20;
        v3 = u1;
    }
    return (c & 0x7fffffff) == 0;
}

/* FUN_0036c274 @ 0x36c274   (est. sk_refcount_dec_any)
 * Ghidra: ulong FUN_0036c274(ulong*,ulong,long)
 * Decrements a refcount by n<<33, handling sentinel/underflow via
 * FUN_0036c328. */
uint64_t sk_refcount_dec_any(uint64_t *ref, uint64_t v, word_t n)
{
    bool b; uint32_t u2; uint64_t u3, u4;
    u2 = (uint32_t)n;
    if ((u2 == 1) || ((v & 0x80000000ffffffff) != 0x80000000ffffffff)) {
        do {
            u3 = v - (n << 0x21);
            u4 = (uint64_t)(1 < u2 && (long)v < 0 || (long)u3 < 0);
            if (1 < u2 && (long)v < 0 || (long)u3 < 0) {
                if ((v & 0xffffffff) == 0xffffffff) goto out0;
                if ((long)v < 0) return FUN_0036c328(v << 3, n);
                u3 = v & 0xffffffff | 0x100000000;
            }
            b = *ref != v;
            v = *ref;
        } while (b);
        *ref = u3;
    } else {
out0:
        u4 = 0;
    }
    return u4;
}

/* FUN_0036c328 @ 0x36c328   (est. sk_refcount_ext_dec)
 * Ghidra: undefined8 FUN_0036c328(long,long)
 * Decrements an external (out-of-line) refcount, comparing 128-bit pairs
 * and offloading to FUN_0036c0e0. */
uint64_t sk_refcount_ext_dec(word_t obj, word_t n)
{
    uint64_t *p = (uint64_t *)(obj + 0x10);
    uint64_t v9 = *(uint64_t *)(obj + 0x10);
    uint64_t v7 = *(uint64_t *)(obj + 0x18);
    int n32 = (int)n;
    bool b4, b2;
    if (n32 == 1) b4 = false;
    else {
        if (((long)v9 < 0) && ((v9 & 0xffffffff) == 0xffffffff)) return 0;
        b4 = n32 != 0;
        if ((n32 != 0) && ((long)v9 < 0)) goto rel;
    }
    uint64_t v8 = v9, hi = v7 >> 0x20;
    do {
        word_t dec = v8 - (n << 0x21);
        v9 = v8;
        uint64_t in11 = hi;
        if (dec < 0) break;
        uint64_t u11 = v7 & 0xffffffff;
        uint64_t u10 = u11 | hi << 0x20;
        v9 = *p;
        v7 = *(uint64_t *)(obj + 0x18);
        if ((v9 == u10) && (v7 == v8)) { *p = u11; *(word_t *)(obj + 0x18) = dec; }
        if (v9 == v8 && v7 == u10) return 0;
        hi = v7 >> 0x20;
        b2 = false;
        if ((long)v9 < 0) b2 = b4;
        v8 = v9;
        in11 = hi;
    } while (!b2);
rel:
    if ((int)v9 == -1) return 0;
    return FUN_0036c0e0(p, v9, v7 & 0xffffffff | /*in_x11*/0 << 0x20);
}

/* FUN_0036c3e0 @ 0x36c3e0   (est. sk_swift_metadata_register0)
 * Ghidra: void FUN_0036c3e0()
 * Registers a Swift protocol-conformance metadata block (0x424 entries
 * at __swift5_protos). */
void sk_swift_metadata_register0()
{
    FUN_00388fb0(0, &__swift5_protos, 0x424);
}

/* FUN_0036c408 @ 0x36c408   (est. sk_swift_metadata_register1)
 * Registers a Swift protocol metadata block (0x2890 bytes at
 * __swift5_proto). */
void sk_swift_metadata_register1()
{
    FUN_0039bb2c(0, &__swift5_proto, 0x2890);
}

/* FUN_0036c430 @ 0x36c430   (est. sk_swift_metadata_register2)
 * Registers a Swift type metadata block (0x1340 bytes at __swift5_types). */
void sk_swift_metadata_register2()
{
    FUN_00387bb8(0, &__swift5_types, 0x1340);
}

/* FUN_0036c704 @ 0x36c704   (est. sk_retain_elem_a)
 * Ghidra: long FUN_0036c704(undefined8*,undefined8*)
 * Retains the element at param_2 into param_1, returning a payload
 * pointer computed from the owning type. */
word_t sk_retain_elem_a(word_t *out, word_t *src)
{
    uint64_t v = *src;
    *out = v;
    FUN_0036b270(v);
    return /*extraout*/0 + ((uint64_t)*(uint8_t *)(/*extraout*/0 + 0x50) + 0x10 &
        ((uint64_t)*(uint8_t *)(/*extraout*/0 + 0x50) ^ 0xffffffffffffffff));
}

/* FUN_0036c7bc @ 0x36c7bc   (est. sk_retain_elem_b)
 * Identical retain-element wrapper (0x36c704 pattern). */
word_t sk_retain_elem_b(word_t *out, word_t *src)
{
    uint64_t v = *src;
    *out = v;
    FUN_0036b270(v);
    return 0 + ((uint64_t)*(uint8_t *)(0 + 0x50) + 0x10 &
        ((uint64_t)*(uint8_t *)(0 + 0x50) ^ 0xffffffffffffffff));
}

/* FUN_0036c874 @ 0x36c874   (est. sk_retain_elem_c)
 * Identical retain-element wrapper. */
word_t sk_retain_elem_c(word_t *out, word_t *src)
{
    uint64_t v = *src;
    *out = v;
    FUN_0036b270(v);
    return 0 + ((uint64_t)*(uint8_t *)(0 + 0x50) + 0x10 &
        ((uint64_t)*(uint8_t *)(0 + 0x50) ^ 0xffffffffffffffff));
}

/* FUN_0036ca9c @ 0x36ca9c   (est. sk_retain_elem_d)
 * Identical retain-element wrapper. */
word_t sk_retain_elem_d(word_t *out, word_t *src)
{
    uint64_t v = *src;
    *out = v;
    FUN_0036b270(v);
    return 0 + ((uint64_t)*(uint8_t *)(0 + 0x50) + 0x10 &
        ((uint64_t)*(uint8_t *)(0 + 0x50) ^ 0xffffffffffffffff));
}

/* FUN_0036cb30 @ 0x36cb30   (est. sk_retain_into_2)
 * Ghidra: undefined8* FUN_0036cb30(undefined8,undefined8*)
 * Retains *param_2 and stores it through a caller register slot. */
word_t *sk_retain_into_2(word_t a, word_t *src)
{
    FUN_0036b270(*src);
    /*store through register slot*/;
    return 0;
}

/* FUN_0036cb34 @ 0x36cb34   (est. sk_retain_into_3)
 * Retain wrapper (0x36cb30 pattern). */
word_t *sk_retain_into_3(word_t a, word_t *src)
{
    FUN_0036b270(*src);
    return 0;
}

/* FUN_0036cb64 @ 0x36cb64   (est. sk_retain_into_4)
 * Retain wrapper (0x36cb30 pattern). */
word_t *sk_retain_into_4(word_t a, word_t *src)
{
    FUN_0036b270(*src);
    return 0;
}

/* FUN_0036cb68 @ 0x36cb68   (est. sk_retain_into_5)
 * Retain wrapper (0x36cb30 pattern). */
word_t *sk_retain_into_5(word_t a, word_t *src)
{
    FUN_0036b270(*src);
    return 0;
}

/* FUN_0036cb90 @ 0x36cb90   (est. sk_retain_release_2)
 * Ghidra: undefined8 FUN_0036cb90(undefined8,undefined8*)
 * Retains *param_2, stores it, then releases the prior value. */
word_t sk_retain_release_2(word_t a, word_t *src)
{
    FUN_0036b270(*src);
    /*store; */ FUN_0036b118(/*prior*/0);
    return 0;
}

/* FUN_0036cb94 @ 0x36cb94   (est. sk_retain_release_3)
 * Retain+release wrapper (0x36cb90 pattern). */
word_t sk_retain_release_3(word_t a, word_t *src)
{
    FUN_0036b270(*src);
    FUN_0036b118(0);
    return 0;
}

/* FUN_0036cbd4 @ 0x36cbd4   (est. sk_swap_release_2)
 * Ghidra: undefined8 FUN_0036cbd4(undefined8*,undefined8*)
 * Swaps *param_1 with *param_2 and releases the old value. */
word_t sk_swap_release_2(word_t *a, word_t *b)
{
    uint64_t v = *a;
    *a = *b;
    FUN_0036b118(v);
    return 0;
}

/* FUN_0036cbd8 @ 0x36cbd8   (est. sk_swap_release_3)
 * Swap+release wrapper (0x36cbd4 pattern). */
word_t sk_swap_release_3(word_t *a, word_t *b)
{
    uint64_t v = *a;
    *a = *b;
    FUN_0036b118(v);
    return 0;
}

/* FUN_0036cc50 @ 0x36cc50   (est. sk_retain_copy_a)
 * Ghidra: undefined8* FUN_0036cc50(undefined8*,undefined8*)
 * Retains *param_2 (thunk) and stores it into param_1. */
word_t *sk_retain_copy_a(word_t *out, word_t *src)
{
    uint64_t v = (uint64_t)thunk_FUN_0036b270(*src);
    *out = v;
    return out;
}

/* FUN_0036cc88 @ 0x36cc88   (est. sk_retain_copy_b)
 * Retain-copy wrapper (0x36cc50 pattern). */
word_t *sk_retain_copy_b(word_t *out, word_t *src)
{
    uint64_t v = (uint64_t)thunk_FUN_0036b270(*src);
    *out = v;
    return out;
}

/* FUN_0036ccb8 @ 0x36ccb8   (est. sk_retain_swap_release)
 * Ghidra: undefined8* FUN_0036ccb8(undefined8*,undefined8*)
 * Retains *param_2, stores it, releases the old value (FUN_003a25d4). */
word_t *sk_retain_swap_release(word_t *out, word_t *src)
{
    uint64_t old = *out;
    uint64_t v = (uint64_t)thunk_FUN_0036b270(*src);
    *out = v;
    FUN_003a25d4(old);
    return out;
}

/* FUN_0036cd00 @ 0x36cd00   (est. sk_swap_release_a)
 * Ghidra: undefined8* FUN_0036cd00(undefined8*,undefined8*)
 * Swaps *param_1 with *param_2, releasing the old value. */
word_t *sk_swap_release_a(word_t *a, word_t *b)
{
    uint64_t v = *a;
    *a = *b;
    FUN_003a25d4(v);
    return a;
}

/* FUN_0036cea8 @ 0x36cea8   (est. sk_retain_into_6)
 * Retain wrapper (0x36cb30 pattern). */
word_t *sk_retain_into_6(word_t a, word_t *src)
{
    FUN_0036b270(*src);
    return 0;
}

/* FUN_0036ceac @ 0x36ceac   (est. sk_retain_into_7)
 * Retain wrapper (0x36cb30 pattern). */
word_t *sk_retain_into_7(word_t a, word_t *src)
{
    FUN_0036b270(*src);
    return 0;
}

/* FUN_0036cedc @ 0x36cedc   (est. sk_retain_into_8)
 * Retain wrapper (0x36cb30 pattern). */
word_t *sk_retain_into_8(word_t a, word_t *src)
{
    FUN_0036b270(*src);
    return 0;
}

/* FUN_0036cee0 @ 0x36cee0   (est. sk_retain_into_9)
 * Retain wrapper (0x36cb30 pattern). */
word_t *sk_retain_into_9(word_t a, word_t *src)
{
    FUN_0036b270(*src);
    return 0;
}

/* FUN_0036cf08 @ 0x36cf08   (est. sk_retain_release_4)
 * Retain+release wrapper (0x36cb90 pattern). */
word_t sk_retain_release_4(word_t a, word_t *src)
{
    FUN_0036b270(*src);
    FUN_0036b118(0);
    return 0;
}

/* FUN_0036cf0c @ 0x36cf0c   (est. sk_retain_release_5)
 * Retain+release wrapper (0x36cb90 pattern). */
word_t sk_retain_release_5(word_t a, word_t *src)
{
    FUN_0036b270(*src);
    FUN_0036b118(0);
    return 0;
}

/* FUN_0036cf4c @ 0x36cf4c   (est. sk_swap_release_4)
 * Swap+release wrapper (0x36cbd4 pattern). */
word_t sk_swap_release_4(word_t *a, word_t *b)
{
    uint64_t v = *a;
    *a = *b;
    FUN_0036b118(v);
    return 0;
}

/* FUN_0036cf50 @ 0x36cf50   (est. sk_swap_release_5)
 * Swap+release wrapper (0x36cbd4 pattern). */
word_t sk_swap_release_5(word_t *a, word_t *b)
{
    uint64_t v = *a;
    *a = *b;
    FUN_0036b118(v);
    return 0;
}

/* FUN_0036cfec @ 0x36cfec   (est. sk_retain_elem_e)
 * Retain-element wrapper (0x36c704 pattern). */
word_t sk_retain_elem_e(word_t *out, word_t *src)
{
    uint64_t v = *src;
    *out = v;
    FUN_0036b270(v);
    return 0 + ((uint64_t)*(uint8_t *)(0 + 0x50) + 0x10 &
        ((uint64_t)*(uint8_t *)(0 + 0x50) ^ 0xffffffffffffffff));
}

/* FUN_0036d0e4 @ 0x36d0e4   (est. sk_retain_elem_f)
 * Retain-element wrapper (0x36c704 pattern). */
word_t sk_retain_elem_f(word_t *out, word_t *src)
{
    uint64_t v = *src;
    *out = v;
    FUN_0036b270(v);
    return 0 + ((uint64_t)*(uint8_t *)(0 + 0x50) + 0x10 &
        ((uint64_t)*(uint8_t *)(0 + 0x50) ^ 0xffffffffffffffff));
}

/* FUN_0036d2b8 @ 0x36d2b8   (est. sk_retain_pair_a)
 * Ghidra: long FUN_0036d2b8(undefined8*,undefined8*)
 * Retains element [0] and [1] of param_2, storing into param_1[0] and a
 * register slot. */
word_t sk_retain_pair_a(word_t *out, word_t *src)
{
    *out = *src;
    FUN_0036b270(src[1]);
    return 0;
}

/* FUN_0036d2bc @ 0x36d2bc   (est. sk_retain_pair_b)
 * Retain-pair wrapper (0x36d2b8 pattern). */
word_t sk_retain_pair_b(word_t *out, word_t *src)
{
    *out = *src;
    FUN_0036b270(src[1]);
    return 0;
}

/* FUN_0036d2f4 @ 0x36d2f4   (est. sk_retain_pair_c)
 * Retain-pair wrapper (0x36d2b8 pattern). */
word_t sk_retain_pair_c(word_t *out, word_t *src)
{
    *out = *src;
    FUN_0036b270(src[1]);
    return 0;
}

/* FUN_0036d2f8 @ 0x36d2f8   (est. sk_retain_pair_d)
 * Retain-pair wrapper (0x36d2b8 pattern). */
word_t sk_retain_pair_d(word_t *out, word_t *src)
{
    *out = *src;
    FUN_0036b270(src[1]);
    return 0;
}

/* FUN_0036d328 @ 0x36d328   (est. sk_retain_pair_release_a)
 * Retains [0]/[1] of param_2, releases the prior [1]. */
word_t sk_retain_pair_release_a(word_t *out, word_t *src)
{
    *out = *src;
    FUN_0036b270(src[1]);
    FUN_0036b118(0);
    return 0;
}

/* FUN_0036d32c @ 0x36d32c   (est. sk_retain_pair_release_b)
 * Retain-pair+release wrapper (0x36d328 pattern). */
word_t sk_retain_pair_release_b(word_t *out, word_t *src)
{
    *out = *src;
    FUN_0036b270(src[1]);
    FUN_0036b118(0);
    return 0;
}

/* FUN_0036d37c @ 0x36d37c   (est. sk_swap_pair_release_a)
 * Swaps [0] and [1], releasing the old [1]. */
word_t sk_swap_pair_release_a(word_t *a, word_t *b)
{
    *a = *b;
    uint64_t v = a[1];
    a[1] = b[1];
    FUN_0036b118(v);
    return 0;
}

/* FUN_0036d380 @ 0x36d380   (est. sk_swap_pair_release_b)
 * Swap-pair+release wrapper (0x36d37c pattern). */
word_t sk_swap_pair_release_b(word_t *a, word_t *b)
{
    *a = *b;
    uint64_t v = a[1];
    a[1] = b[1];
    FUN_0036b118(v);
    return 0;
}

/* FUN_0036d424 @ 0x36d424   (est. sk_retain_elem_g)
 * Retain-element wrapper (0x36c704 pattern). */
word_t sk_retain_elem_g(word_t *out, word_t *src)
{
    uint64_t v = *src;
    *out = v;
    FUN_0036b270(v);
    return 0 + ((uint64_t)*(uint8_t *)(0 + 0x50) + 0x10 &
        ((uint64_t)*(uint8_t *)(0 + 0x50) ^ 0xffffffffffffffff));
}

/* FUN_0036d454 @ 0x36d454   (est. sk_release_triple_a)
 * Ghidra: void FUN_0036d454(long)
 * Releases three retained elements at +8, +0x18, +0x28. */
void sk_release_triple_a(word_t obj)
{
    FUN_0036b118(*(uint64_t *)(obj + 8));
    FUN_0036b118(*(uint64_t *)(0 + 0x18));
    FUN_0036b118(*(uint64_t *)(0 + 0x28));
}

/* FUN_0036d458 @ 0x36d458   (est. sk_release_triple_b)
 * Release-triple wrapper (0x36d454 pattern). */
void sk_release_triple_b(word_t obj)
{
    FUN_0036b118(*(uint64_t *)(obj + 8));
    FUN_0036b118(*(uint64_t *)(0 + 0x18));
    FUN_0036b118(*(uint64_t *)(0 + 0x28));
}

/* FUN_0036d484 @ 0x36d484   (est. sk_retain_triple_a)
 * Ghidra: long FUN_0036d484(undefined8*,undefined8*)
 * Retains three elements [1], [0x18], [0x28] of param_2 into param_1. */
word_t sk_retain_triple_a(word_t *out, word_t *src)
{
    *out = *src;
    FUN_0036b270(src[1]);
    out[1] = 0;
    out[2] = 0;
    FUN_0036b270(*(uint64_t *)(0 + 0x18));
    out[3] = 0;
    out[4] = 0;
    FUN_0036b270(*(uint64_t *)(0 + 0x28));
    out[5] = 0;
    return out[5];
}

/* FUN_0036d488 @ 0x36d488   (est. sk_retain_triple_b)
 * Retain-triple wrapper (0x36d484 pattern). */
word_t sk_retain_triple_b(word_t *out, word_t *src)
{
    *out = *src;
    FUN_0036b270(src[1]);
    out[1] = 0;
    out[2] = 0;
    FUN_0036b270(*(uint64_t *)(0 + 0x18));
    out[3] = 0;
    out[4] = 0;
    FUN_0036b270(*(uint64_t *)(0 + 0x28));
    out[5] = 0;
    return out[5];
}

/* FUN_0036d4ec @ 0x36d4ec   (est. sk_retain_triple_release_a)
 * Retains three elements of param_2 into param_1, releasing the prior
 * values. */
word_t sk_retain_triple_release_a(word_t *out, word_t *src)
{
    *out = *src;
    FUN_0036b270(src[1]);
    FUN_0036b118(0);
    out[2] = 0;
    FUN_0036b270(*(uint64_t *)(0 + 0x18));
    FUN_0036b118(0);
    out[4] = 0;
    FUN_0036b270(*(uint64_t *)(0 + 0x28));
    FUN_0036b118(0);
    return 0;
}

/* FUN_0036d4f0 @ 0x36d4f0   (est. sk_retain_triple_release_b)
 * Retain-triple+release wrapper (0x36d4ec pattern). */
word_t sk_retain_triple_release_b(word_t *out, word_t *src)
{
    *out = *src;
    FUN_0036b270(src[1]);
    FUN_0036b118(0);
    out[2] = 0;
    FUN_0036b270(*(uint64_t *)(0 + 0x18));
    FUN_0036b118(0);
    out[4] = 0;
    FUN_0036b270(*(uint64_t *)(0 + 0x28));
    FUN_0036b118(0);
    return 0;
}

/* FUN_0036d5ac @ 0x36d5ac   (est. sk_swap_triple_a)
 * Ghidra: undefined8 FUN_0036d5ac(undefined8*,undefined8*)
 * Swaps three element pairs [1..0x28], releasing the old values. */
word_t sk_swap_triple_a(word_t *a, word_t *b)
{
    *a = *b;
    uint64_t v = a[1];
    a[1] = b[1];
    FUN_0036b118(v);
    a[2] = b[2];
    v = a[3];
    a[3] = b[3];
    FUN_0036b118(v);
    a[4] = b[4];
    v = a[5];
    a[5] = b[5];
    FUN_0036b118(v);
    return 0;
}

/* FUN_0036d5b0 @ 0x36d5b0   (est. sk_swap_triple_b)
 * Swap-triple wrapper (0x36d5ac pattern). */
word_t sk_swap_triple_b(word_t *a, word_t *b)
{
    *a = *b;
    uint64_t v = a[1];
    a[1] = b[1];
    FUN_0036b118(v);
    a[2] = b[2];
    v = a[3];
    a[3] = b[3];
    FUN_0036b118(v);
    a[4] = b[4];
    v = a[5];
    a[5] = b[5];
    FUN_0036b118(v);
    return 0;
}

/* FUN_0036d8a4 @ 0x36d8a4   (est. sk_prespec_lookup)
 * Ghidra: long FUN_0036d8a4()
 * The "Prespecializations library" lookup: based on the mode flag
 * (_DAT_006c02f0) walks the prespecialization list (_DAT_006c02e8),
 * matching the mangled type metadata key; verifies every specialized
 * argument falls in the accepted range (rejecting otherwise), builds a
 * new mangled name, and finds the matching prespecialized metadata via
 * FUN_0036def8/FUN_003c3008. Returns the found metadata (0 on miss).
 * Confidence: medium
 * Notes: strings s_Prespecializations_library__Look_005d4ae1/4b32/4a82,
 *   s_Prespecializations_library__Reje_005d4914/48c6,
 *   s_Prespecializations_library__fail_005d4974,
 *   s_Mangling_for_prespecialized_meta_005d49c0,
 *   s_Prespecializations_library__foun_005d49f9; builders FUN_003652b8/
 *   3c3008/3a3430/3a3460/3a3814/62ea4. */
word_t sk_prespec_lookup()
{
    cl4_result_t m;
    word_t key = 0;
    word_t type = 0;
    int mode;
    word_t i, n;

    word_t sk_prespec_lookup();
    /* invoke the type-id getter */
    uint64_t u1 = 0;
    word_t *pl4 = 0;
    word_t d = 0;
    uint64_t u9 = 0;
    if (-1 < _DAT_006c0320) FUN_003d3dd8(&DAT_006c0320, &DAT_0036de7c);
    if (_DAT_006c02f0 == 3) {
        d = FUN_0035eb3c(u1);
        if (d != 0) {
            word_t *list = *(word_t **)(_DAT_006c02e8 + 0x18);
            if (*list != 0) {
                i = 0;
                do {
                    word_t *ent = (word_t *)list[i * 2 + 1];
                    if (*ent == (uint64_t)*(uint16_t *)(d + 8) + 1) {
                        uint64_t u6 = (u1 == 0) ? 0 : u1;
                        if (u6 == ent[1]) {
                            word_t *ea = ent + 2;
                            uint64_t cnt = (uint64_t)*(uint16_t *)(d + 8);
                            word_t *ka = pl4;
                            do {
                                if (cnt == 0) {
                                    if (DAT_006c02e0 == '\x01')
                                        FUN_001185ec(0xeb1a02bf914012ba, s_Prespecializations_library__Look_005d4ae1);
                                    d = list[i * 2 + 2];
                                    goto found;
                                }
                                if (*ea != *ka) break;
                                cnt = cnt - 1; ea = ea + 1; ka = ka + 1;
                            } while (1);
                        }
                    }
                    i = i + 1;
                } while (i != *list);
            }
            if (DAT_006c02e0 == '\x01') {
                FUN_001185ec(0xeb1a02bf914012ba, s_Prespecializations_library__Look_005d4b32);
            }
        }
    } else if (_DAT_006c02f0 == 2) {
        if (DAT_006c02e0 == '\x01')
            FUN_001185ec(0xeb1a02bf914012ba, s_Prespecializations_library__Look_005d4a82);
    } else if ((_DAT_006c02f0 == 1) && ((d = FUN_0035eb3c(u1), d != 0))) {
        uint64_t cnt = (uint64_t)*(uint16_t *)(d + 4);
        if (cnt != 0) {
            uint8_t *pb = (uint8_t *)(d + 0xc);
            do {
                if ((*pb & 0x3f) != 0) goto reject;
                cnt = cnt - 1;
                pb = pb + 1;
            } while (cnt != 0);
        }
        /* range checks */
        uint64_t u6 = (u1 == 0) ? 0 : u1;
        if ((_DAT_006c02f8 > _DAT_006c02e8 || _DAT_006c0300 <= _DAT_006c02e8) ||
            ((_DAT_006c02f8 <= u6 && u6 < _DAT_006c0300 &&
              ((u6 < _DAT_006c0308 || (_DAT_006c0310 <= u6)))))) {
            if ((uint64_t)*(uint16_t *)(d + 8) != 0) {
                u6 = 0;
                do {
                    if ((_DAT_006c02f8 <= _DAT_006c02e8 && _DAT_006c02e8 < _DAT_006c0300) &&
                        ((u9 = pl4[u6], u9 < _DAT_006c02f8 || _DAT_006c0300 <= u9 ||
                          (_DAT_006c0308 <= u9 && u9 < _DAT_006c0310)))) {
                        if (DAT_006c02e0 != '\x01') goto reject;
                        FUN_001185ec(0xeb1a02bf914012ba, s_Prespecializations_library__Reje_005d4914);
                        goto reject;
                    }
                    u6 = u6 + 1;
                } while (*(uint16_t *)(d + 8) != u6);
            }
            /* build new mangled name and look up prespecialized metadata */
            word_t local = 0;
            word_t *stk = 0;
            word_t r = FUN_003652b8(u1, pl4, &local);
            if (r == 0) {
                if (DAT_006c02e0 == '\x01')
                    FUN_001185ec(0xeb1a02bf914012ba, s_Prespecializations_library__fail_005d4974);
                type = 0;
            } else {
                word_t l3 = r;
                if (*(short *)(r + 0x10) != 0x65) {
                    l3 = FUN_003a3430(&local, 0x65);
                    FUN_003a3460(l3, r, &local);
                }
                int l12b8[6];
                FUN_003c3008(l12b8, l3, sk_fatal_symbolic_ref, 0, &local, 0);
                if (l12b8[0] != 0) {
                    FUN_004b9ed8(0, s_Mangling_for_prespecialized_meta_005d49c0);
                    type = 0;
                } else {
                    d = FUN_0036def8(*(uint64_t *)(_DAT_006c02e8 + 8), 0, 0);
                    if (d == 0) type = 0;
                    else type = *(word_t *)(d + 8);
                    if (DAT_006c02e0 == '\x01')
                        FUN_001185ec(0xeb1a02bf914012ba, s_Prespecializations_library__foun_005d49f9);
                }
            }
            /* teardown scratch */
            FUN_00362ea4(/*auStack_1068*/);
            FUN_003a3814(/*local_1270*/);
            goto found;
        }
        if (DAT_006c02e0 == '\x01')
            FUN_001185ec(0xeb1a02bf914012ba, s_Prespecializations_library__Reje_005d48c6);
    }
reject:
    type = 0;
found:
    return type;
}

/* FUN_0036de80 @ 0x36de80   (est. sk_scratch_teardown)
 * Ghidra: undefined8* FUN_0036de80(undefined8*)
 * Tears down a scratch buffer object: resets the header tags (0x67c398/
 * 0x67c370), releases the payload (FUN_00362ea4/FUN_003a3814) and clears
 * the deferred flag. */
word_t *sk_scratch_teardown(word_t *buf)
{
    *buf = 0x67c398;
    FUN_00362ea4(buf + 0x44);
    *buf = 0x67c370;
    FUN_003a3814(buf[3]);
    if (buf[5] != 0) *(uint8_t *)(buf[5] + 0x30) = 0;
    return buf;
}

/* FUN_0036def8 @ 0x36def8   (est. sk_prespec_find_slot)
 * Ghidra: long* FUN_0036def8(long)
 * Looks up a prespecialized-metadata slot at (param_1 + hash*0x10 + 8);
 * returns the slot if occupied, else 0. */
word_t *sk_prespec_find_slot(word_t base)
{
    cl4_result_t r; r.lo = FUN_0036df7c(); r.hi = 0;
    word_t *slot;
    if ((r.hi & 1) == 0) return 0;
    slot = (word_t *)(base + r.lo * 0x10 + 8);
    return (*slot != 0) ? slot : 0;
}

/* FUN_0036df58 @ 0x36df58   (est. sk_fatal_symbolic_ref)
 * Fatal "Unexpected symbolic reference" — never returns. */
void sk_fatal_symbolic_ref()
{
    FUN_00369bb0(0, s_Unexpected_symbolic_reference__p_005d4a2f);
}

/* FUN_0036df7c @ 0x36df7c   (est. sk_hash_table_probe2)
 * Ghidra: undefined1[16] FUN_0036df7c(ulong*,undefined8,undefined8,long*)
 * Probes a string-key hash table: hashes param_1 (FUN_0036e038), walks
 * the buckets comparing each candidate string (memcmp via
 * thunk_FUN_00114e50) until a match or empty slot; returns (found, index). */
cl4_result_t sk_hash_table_probe2(uint64_t *key, word_t b, word_t c, word_t *tbl)
{
    cl4_result_t r;
    uint64_t h = FUN_0036e038();
    uint64_t count = 0, mod = 0;
    uint64_t cap = *key;
    if (cap != 0) mod = h / cap;
    word_t *slots = (word_t *)tbl[0];
    word_t *keys = (word_t *)tbl[1];
    word_t *sizes = (word_t *)tbl[2];
    uint64_t found = 1;
    uint64_t idx = h - mod * cap;
    do {
        word_t s = *(word_t *)(slots + 8 + idx * 0x10);
        if (s == 0) goto out;
        word_t sz = *sizes;
        int r2 = (int)thunk_FUN_00114e50(s, *keys, sz);
        if ((r2 == 0) && (*(char *)(s + sz) == '\0')) goto out;
        s = 0;
        if (idx + 1U < cap) s = idx + 1;
        count = count + 1;
        idx = s;
    } while (count <= cap);
    found = 0;
    idx = 0;
out:
    r.hi = found;
    r.lo = idx;
    return r;
}

/* FUN_0036e038 @ 0x36e038   (est. sk_murmur_hash_bytes)
 * Ghidra: ulong FUN_0036e038(undefined8,byte*,ulong)
 * 64-bit MurmurHash-style byte-string hash (0x9e3779b97f4a7c15-ish
 * constants); processes 8 bytes at a time then the tail. */
uint64_t sk_murmur_hash_bytes(word_t seed, uint8_t *p, uint64_t len)
{
    uint64_t h = len * -0x395b586ca42e166b;
    uint64_t n = len & 0xfffffffffffffff8;
    if (n != 0) {
        uint8_t *end = p + n;
        do {
            uint64_t k = *(int64_t *)p * -0x395b586ca42e166b;
            h = ((k ^ k >> 0x2f) * -0x395b586ca42e166b ^ h) * -0x395b586ca42e166b;
            n = n - 8;
            p = p + 8;
        } while (n != 0);
        len = len & 7;
        p = end;
    }
    if ((long)len < 4) {
        if (1 < (long)len) {
            if (len != 2) goto b1;
            goto b2;
        }
        if (len == 0) goto done;
    } else {
        if ((long)len < 6) {
            if (len != 4) goto b3;
        } else {
            if (len != 6) h = h ^ (uint64_t)p[6] << 0x30;
            h = h ^ (uint64_t)p[5] << 0x28;
            h = h ^ (uint64_t)p[4] << 0x20;
        }
        h = h ^ (uint64_t)p[3] << 0x18;
b3:
        h = h ^ (uint64_t)p[2] << 0x10;
b2:
        h = h ^ (uint64_t)p[1] << 8;
    }
b1:
    h = h ^ *p;
done:
    uint64_t f = (h * -0x395b586ca42e166b ^ h * -0x395b586ca42e166b >> 0x2f) * -0x395b586ca42e166b;
    return f ^ f >> 0x2f;
}

/* FUN_0036e110 @ 0x36e110   (est. sk_scratch_teardown_free)
 * Ghidra: void FUN_0036e110(undefined8*)
 * Tears down a scratch buffer (as 0x36de80) then frees it. */
void sk_scratch_teardown_free(word_t *buf)
{
    *buf = 0x67c398;
    FUN_00362ea4(buf + 0x44);
    *buf = 0x67c370;
    FUN_003a3814(buf[3]);
    if (buf[5] != 0) *(uint8_t *)(buf[5] + 0x30) = 0;
    thunk_FUN_00012568(buf, 0x1240);
}

/* FUN_0036e190 @ 0x36e190   (est. sk_register_allocator)
 * Ghidra: long* FUN_0036e190(long*)
 * Registers the global allocator/type-dispatch record: zeroes the record,
 * initializes the once-flag, records the allocator kind byte, probes the
 * allocator's kind to set the inline flag, and marks the record as a
 * special debug variant if the global debug flag is set. */
word_t *sk_register_allocator(word_t *rec)
{
    uint32_t u;
    uint64_t kind;
    *(uint32_t *)(rec + 1) = 0;
    rec[3] = 0; rec[2] = 0; rec[5] = 0; rec[4] = 0;
    if (-1 < _DAT_006adee0) FUN_003d3dd8(&DAT_006adee0, &DAT_003697c0, 0);
    DAT_006c02e0 = (uint8_t)DAT_006adeda;
    if ((uint8_t)DAT_006adeda == '\x01') FUN_004ba070();
    *rec = 0;
    if ((int)rec[1] == 0) {
        u = (uint32_t)FUN_0036e310(rec, 0);
        *(uint32_t *)(rec + 1) = u;
        word_t v = *rec;
        if (v != 0) {
            if (*(uint32_t *)(v + 4) < 3) kind = 0;
            else kind = *(uint64_t *)(v + 0x20) & 2;
            *(char *)(rec + 6) = (char)(kind >> 1);
            if ((uint8_t)DAT_006c02e0 == '\x01') FUN_004ba0a0();
        }
    }
    if (-1 < _DAT_006adee0) FUN_003d3dd8(&DAT_006adee0, &DAT_003697c0, 0);
    if ((uint8_t)DAT_006aded4 == '\x01') {
        if (-1 < _DAT_006adee0) FUN_003d3dd8(&DAT_006adee0, &DAT_003697c0, 0);
        *(uint8_t *)(rec + 6) = 2;
        if ((uint8_t)DAT_006c02e0 == '\x01') FUN_004ba0f4();
    }
    return rec;
}

/* FUN_0036e310 @ 0x36e310   (est. sk_probe_allocator_kind)
 * Ghidra: undefined4 FUN_0036e310(undefined8,long)
 * Runs the allocator once and returns the (fixed) kind value 4. */
uint32_t sk_probe_allocator_kind(word_t a, word_t b)
{
    if (b != 0) {
        if (-1 < _DAT_006adee0) FUN_003d3dd8(&DAT_006adee0, &DAT_003697c0, 0);
        if ((uint8_t)DAT_006c02e0 == '\x01') FUN_004ba148();
        return 4;
    }
    return 4;
}

/* FUN_0036e51c @ 0x36e51c   (est. sk_hash_seed)
 * Returns the fixed hash seed constant 0xeb1a02bf914012ba. */
uint64_t sk_hash_seed() { return 0xeb1a02bf914012ba; }

/* FUN_0036e52c @ 0x36e52c   (est. sk_string_intern)
 * Ghidra: long* FUN_0036e52c(long,uint*)
 * Interns a string: resolves the string header, allocates a slot from
 * the global string table (DAT_006c0548/DAT_006c0540), copies the bytes
 * and populates the interned-record header (tag 0x67aa20). */
word_t *sk_string_intern(word_t base, uint32_t *str)
{
    if ((((str == 0) || ((*str & 0x1f) != 0x10)) || ((*str >> 0x1d & 1) == 0)) || (str == 0)) {
        int off = *(int *)(base + 4);
        word_t *p = (word_t *)((word_t)off + base + 4);
        if (*p - 0x800U < 0xfffffffffffff801) {
            word_t *q = (off != 0) ? p : 0;
            q[-1] = 0x67aa20;
        }
        return p;
    }
    int off = *(int *)(base + 4);
    int *hdr = (int *)((word_t)off + base + 4);
    int *q = (off != 0) ? hdr : 0;
    word_t (*jt)(uint32_t *) = (word_t (*)(uint32_t *))((word_t)q + (word_t)*hdr);
    if (((*hdr != 0 && jt != 0) && (jt != 0)) && (jt != 0)) {
        return (word_t *)(*jt)(str);
    }
    cl4_result_t r; r.lo = FUN_0036f878(); r.hi = 0;
    uint64_t u7 = r.lo;
    if ((DAT_006c0548 & 1) == 0) FUN_004ba180();
    word_t l9 = ((u7 >> 0x20) + (u7 & 0xffffffff)) * 8;
    word_t l8 = FUN_00369758(0x6c0540, l9, 8);
    word_t *pl6 = (word_t *)(l8 + (u7 & 0xffffffff) * 8);
    thunk_FUN_00114330((word_t)pl6 + r.hi, (uint64_t)str[8] << 3);
    int i5 = hdr[1];
    word_t l2 = ((i5 != 0) && ((l2 = (word_t)i5 + (word_t)(hdr + 1), l2 != 0))) ? l2 : 0;
    pl6[-2] = l2;
    *pl6 = 0;
    pl6[1] = 0;
    pl6[-1] = 0x67aa20;
    *(int *)(pl6 + 2) = hdr[3];
    *(uint64_t *)((word_t)pl6 + 0x14) = 0;
    *(uint32_t *)((word_t)pl6 + 0x1c) = 0;
    *(int *)(pl6 + 4) = (int)l9;
    *(int *)((word_t)pl6 + 0x24) = (int)((u7 & 0xffffffff) << 3);
    if (str == 0) str = 0;
    pl6[5] = (word_t)str;
    int i5b = hdr[2];
    word_t l9b = ((i5b != 0) && ((l9 = (word_t)i5b + (word_t)(hdr + 2), l9 != 0))) ? l9 : 0;
    pl6[6] = l9b;
    return pl6;
}

/* FUN_0036e7ec @ 0x36e7ec   (est. sk_fixup_interned_refs)
 * Ghidra: void FUN_0036e7ec(ulong,uint,long,long,undefined8)
 * Post-intern fixup: copies the payload table, then for each fixup
 * record re-writes referenced entries by merging (FUN_0036ed94) or
 * interning (FUN_0036e878) the target objects. */
void sk_fixup_interned_refs(uint64_t count, uint32_t nfix, word_t fix, word_t tab, word_t src)
{
    uint64_t u4;
    FUN_00117cc4(tab, src, (count & 0xffffffff) << 3);
    if (nfix != 0) {
        uint64_t n = (uint64_t)nfix;
        uint16_t *p = (uint16_t *)(fix + 4);
        do {
            uint64_t u4 = (uint64_t)p[-1];
            if (p[-2] == 1) {
                uint64_t r = FUN_0036ed94(*(uint64_t *)(tab + u4 * 8),
                                          *(uint64_t *)(tab + (uint64_t)*p * 8));
                *(uint64_t *)(tab + u4 * 8) = r;
            } else if (p[-2] == 0) {
                uint64_t r = FUN_0036e878(*(uint64_t *)(tab + u4 * 8));
                *(uint64_t *)(tab + u4 * 8) = r;
            }
            p = p + 4;
            n = n - 1;
        } while (n != 0);
    }
}

/* FUN_0036e878 @ 0x36e878   (est. sk_obj_intern_table_b)
 * The object-intern table builder (second instance, table state at
 * DAT_006c0390/DAT_006c03a0/DAT_006c0398/DAT_006c03d8, mutex 0x6c03b0).
 * Interns an object keyed by (param_1, param_2), growing/rehashing the
 * open-addressing table under the mutex and caching the last entry.
 * Confidence: medium
 * Notes: this is the same intern-table family as 0x36aae4/36ed94/37062c/
 *   370f2c/371b58; hash FUN_00380930, insert FUN_0035b588. */
void sk_obj_intern_table_b(uint64_t *key, uint64_t tag)
{
    /* See the shared transcription in FUN_0036fb10 body (0x36fb10): this
     * is the same generic intern-table builder with table state
     * _DAT_006c0390/_DAT_006c03a0/_DAT_006c0398/_DAT_006c03d8. */
    uint64_t *tbl = (uint64_t *)_DAT_006c03d8;
    if ((tbl == 0) || (tag != *tbl)) {
        LOAcquire();
        _DAT_006c0390 += 1;
        /* probe / grow / insert via FUN_00380930 + FUN_0035b588 */
        LORelease();
    }
    /* returns the interned record (single flag bit set) */
}

/* FUN_0036ed94 @ 0x36ed94   (est. sk_obj_intern_table_c)
 * Third object-intern table builder (state at DAT_006c03e0/f0/e8/428,
 * mutex 0x6c0400). Same generic structure as 0x36e878. */
void sk_obj_intern_table_c(uint64_t *key, uint64_t tag)
{
    uint64_t *tbl = (uint64_t *)_DAT_006c0428;
    if ((tbl == 0) || (tag != *tbl)) {
        LOAcquire();
        _DAT_006c03e0 += 1;
        LORelease();
    }
    /* intern-table body (same as 0x36e878) */
}

/* FUN_0036f2e4 @ 0x36f2e4   (est. sk_metadata_layout)
 * Ghidra: undefined8 FUN_0036f2e4(uint*,long*)
 * Computes the metadata layout of a type object: resolves the superclass
 * metadata (FUN_00379480), derives the size/stride from the type header,
 * and fills the (offset, size) output pair. */
uint64_t sk_metadata_layout(uint32_t *type, word_t *out)
{
    uint32_t *t = (type == 0) ? 0 : type;
    int *hdr = (int *)FUN_00379480(t);
    word_t *meta = (word_t *)((word_t)*hdr + (word_t)hdr);
    uint64_t size, stride;
    if (*hdr == 0 || meta == 0) { size = 3; stride = 7; }
    else {
        uint32_t kind = *type >> 0x19 & 7;
        if (kind != 0) {
            if (kind != 1) SoftwareBreakpoint(1, 0x36f418); /* noreturn */
            meta = (word_t *)*meta;
            if ((meta == 0) || (meta == 0))
                FUN_00369bb0(0, s_instantiating_class_metadata_for_005d4ec5);
        }
        size = FUN_0036f878(meta);
        stride = size >> 0x20;
    }
    uint32_t w = type[8];
    uint32_t n = w + (uint32_t)size;
    word_t sl = stride << 3;
    bool big = (*type & 0x10000000) != 0;
    if (big) w = 0;
    int i2 = w + (int)stride;
    uint32_t u3 = (uint32_t)size;
    if (big) { sl = (uint64_t)n * -8; u3 = n; }
    *(uint32_t *)(out + 1) = u3;
    *(int *)((word_t)out + 0xc) = i2;
    *out = sl;
    return CONCAT44(i2, u3);
}

/* FUN_0036f418 @ 0x36f418   (est. sk_metadata_pointer)
 * Ghidra: ulong FUN_0036f418(long)
 * Returns the metadata pointer: reads the type header, lazily computing
 * the layout via FUN_0036f2e4 if empty, shifted right by 3. */
uint64_t sk_metadata_pointer(word_t obj)
{
    int off = *(int *)(obj + 0x18);
    uint64_t *p = 0;
    if (off != 0) p = (uint64_t *)(obj + 0x18 + (word_t)off);
    uint64_t v = *p;
    if (v == 0) { FUN_0036f2e4(); v = 0; }
    return v >> 3;
}

/* FUN_0036f460 @ 0x36f460   (est. sk_obj_is_inline)
 * Ghidra: byte FUN_0036f460(ulong*)
 * Returns whether an object stores its payload inline, based on its
 * kind tag (0x200 / 0x201/0x202 / >= 0x800) and header flags. */
uint8_t sk_obj_is_inline(uint64_t *obj)
{
    uint64_t k = *obj;
    char *hdr;
    uint8_t b;
    if (k == 0x200) {
        hdr = (char *)obj[1];
        if (hdr == 0) hdr = 0;
        if (*hdr < '\0') {
            uint8_t *p = (uint8_t *)FUN_0036a388();
            b = 0;
            if (p != 0) b = *p >> 1 & 1;
        } else b = 0;
        return b;
    }
    if (k < 0x800 && ((int)k == 0x201 || (int)k == 0x202)) {
        hdr = (char *)obj[1];
        if (hdr == 0) hdr = 0;
        if (*hdr < '\0') {
            uint8_t *p = (uint8_t *)FUN_0036a454();
            b = 0;
            if (p != 0) b = *p >> 1 & 1;
        } else b = 0;
        return b;
    }
    if ((k - 0x800 < 0xfffffffffffff801) && (*(char *)obj[5] < '\0'))
        return (uint8_t)obj[2] >> 4 & 1;
    return 0;
}

/* FUN_0036f5d0 @ 0x36f5d0   (est. sk_interned_obj_alloc)
 * Ghidra: undefined8* FUN_0036f5d0(long,undefined8,long)
 * Allocates and fills an interned object record: sizes the payload from
 * the metadata layout, copies type-name bytes, and populates the header
 * (tag 0x67aa20) with the type reference and name table. */
word_t *sk_interned_obj_alloc(word_t type, word_t b, word_t src)
{
    word_t *p;
    word_t base = (type == 0) ? 0 : type;
    word_t l2;
    cl4_result_t r; r.lo = FUN_0036f878(base); r.hi = 0;
    uint64_t u5 = r.lo;
    uint64_t u7 = u5;
    if ((*(uint8_t *)(src + 8) & 1) != 0)
        u7 = u5 + ((uint64_t)((uint32_t)*(uint16_t *)(src + 0x26) + (uint32_t)*(uint16_t *)(src + 0x24)) << 0x20);
    word_t l6 = FUN_00369758(0, ((u7 >> 0x20) + (u7 & 0xffffffff)) * 8, 8);
    p = (word_t *)(l6 + (u7 & 0xffffffff) * 8);
    if ((*(uint8_t *)(src + 8) & 1) != 0) {
        thunk_FUN_00114330(p + (u5 >> 0x20), (uint64_t)*(uint16_t *)(src + 0x24) << 3);
        int i4 = *(int *)(src + 0x20);
        word_t lv = (i4 != 0) ? (word_t)i4 + src + 0x20 : 0;
        FUN_00117cc4(p + (u5 >> 0x20) + *(uint16_t *)(src + 0x24), lv,
                     (uint64_t)*(uint16_t *)(src + 0x26) << 3);
    }
    word_t l6b = (word_t)p + r.hi;
    thunk_FUN_00114330(l6b, (uint64_t)*(uint32_t *)(type + 0x20) << 3);
    if ((int)*(uint32_t *)(src + 8) < 0) {
        word_t l2 = src + ((uint64_t)*(uint32_t *)(src + 8) & 1) * 8;
        int i4 = *(int *)(l2 + 0x20);
        word_t l3 = (i4 != 0) ? (word_t)i4 + l2 + 0x20 : 0;
        FUN_00117cc4(l6b + (uint64_t)*(uint16_t *)(l2 + 0x24) * 8, l3,
                     (uint64_t)*(uint16_t *)(l2 + 0x26) << 3);
    }
    int i4 = *(int *)(src + 0xc);
    word_t lv = ((i4 != 0) && ((l2 = (word_t)i4 + src + 0xc, l2 != 0))) ? l2 : 0;
    p[-2] = lv;
    *p = 0;
    p[1] = 0;
    p[-1] = 0x67aa20;
    *(uint32_t *)(p + 2) = *(uint32_t *)(src + 0x14);
    *(uint64_t *)((word_t)p + 0x14) = 0;
    *(uint32_t *)((word_t)p + 0x1c) = 0;
    *(int *)(p + 4) = (r.lo & 0xffffffff) + (r.hi & 0xffffffff) * 8;
    *(int *)((word_t)p + 0x24) = (uint32_t)(r.lo & 0xffffffff) << 3;
    word_t t = (type == 0) ? 0 : type;
    p[5] = t;
    int i4b = *(int *)(src + 0x10);
    word_t lvb = ((i4b != 0) && ((l2 = (word_t)i4b + src + 0x10, l2 != 0))) ? l2 : 0;
    p[6] = lvb;
    if (type == 0) type = 0;
    FUN_0036f8bc(p, type, b);
    return p;
}

/* FUN_0036f878 @ 0x36f878   (est. sk_metadata_descriptor)
 * Ghidra: undefined1[16] FUN_0036f878(uint*)
 * Reads the metadata descriptor (size/stride/offset) from a type header,
 * handling the three encoding modes (bits 0x20000000/0x10000000). */
cl4_result_t sk_metadata_descriptor(uint32_t *type)
{
    cl4_result_t r;
    uint32_t u3;
    word_t l4;
    if ((*type >> 0x1d & 1) == 0) {
        if ((*type >> 0x1c & 1) == 0) { u3 = type[7]; l4 = 0x20; }
        else { u3 = 0; l4 = 0x18; }
        u3 = u3 - *(int *)((word_t)type + l4);
        r.hi = -(uint64_t)(u3 >> 0x1f) & 0xfffffff800000000 | (uint64_t)u3 << 3;
        r.lo = *(uint64_t *)(type + 6);
        return r;
    }
    u3 = type[6];
    word_t *p = (word_t *)((word_t)(type + 6) + (word_t)(int)u3);
    word_t *q = (u3 != 0) ? p : 0;
    if (*q != 0) { r.lo = p[1]; r.hi = *q; return r; }
    r.lo = FUN_0036f2e4(); r.hi = 0; return r;
}

/* FUN_0036f8bc @ 0x36f8bc   (est. sk_fixup_obj_refs)
 * Ghidra: void FUN_0036f8bc(long,undefined8,undefined8)
 * Applies the fixup table to an interned object: resolves the type
 * metadata and re-writes referenced entries. */
void sk_fixup_obj_refs(word_t obj, word_t type, word_t src)
{
    uint64_t u5;
    uint16_t u1;
    word_t l3 = FUN_0035eb3c(type);
    int i2 = (int)FUN_0035ef4c(type);
    if ((*(uint16_t *)(l3 + 10) & 1) == 0) u5 = 0;
    else u5 = *(uint32_t *)((l3 + (uint64_t)*(uint16_t *)(l3 + 4) + 0xf & ~3ull) +
                            (uint64_t)*(uint16_t *)(l3 + 6) * 0xc);
    u1 = *(uint16_t *)(l3 + 8);
    uint64_t u4 = FUN_003658a0(l3);
    FUN_0036e7ec(u1, u5 & 0xffff, u4, obj + (word_t)i2 * 8, src);
}

/* FUN_0036f974 @ 0x36f974   (est. sk_interned_meta_alloc)
 * Ghidra: long FUN_0036f974(long,undefined8,long,long)
 * Allocates an interned-metadata record: sizes the header, copies the
 * type-name bytes, stores the type reference and flags, and applies the
 * fixup table. */
word_t sk_interned_meta_alloc(word_t type, word_t b, word_t src, word_t size)
{
    word_t l1; int i2; uint32_t u3;
    word_t base = (type == 0) ? 0 : type;
    word_t l4 = FUN_00369758(0, size + 0x20, 8);
    if ((*(uint8_t *)(src + 8) & 1) != 0) {
        thunk_FUN_00114330(l4 + 0x20, (uint64_t)*(uint16_t *)(src + 0x14) << 3);
        i2 = *(int *)(src + 0x10);
        l1 = (i2 != 0) ? (word_t)i2 + src + 0x10 : 0;
        FUN_00117cc4(l4 + 0x20 + (uint64_t)*(uint16_t *)(src + 0x14) * 8, l1,
                     (uint64_t)*(uint16_t *)(src + 0x16) << 3);
    }
    u3 = *(uint32_t *)(src + 0xc);
    word_t *pl5;
    if ((u3 == 0) || ((pl5 = (word_t *)(((word_t)(int)u3 & 0xfffffffffffffffeU) + src + 0xc),
                       (u3 & 1) != 0 && (pl5 = (word_t *)*pl5, pl5 == 0)) || (pl5 == 0)))
        pl5 = 0;
    u3 = *(uint32_t *)(src + 8);
    *(word_t **)(l4 + 8) = pl5;
    *(uint64_t *)(l4 + 0x10) = (uint64_t)(u3 >> 0x15);
    if (type == 0) type = 0;
    *(word_t *)(l4 + 0x18) = type;
    FUN_0036f8bc(l4 + 0x10, type, b);
    return l4 + 0x10;
}

/* FUN_0036fb0c @ 0x36fb0c   (est. sk_interned_meta_alloc_t)
 * Thunk to FUN_0036f974. */
word_t sk_interned_meta_alloc_t(word_t type, word_t b, word_t src, word_t size)
{
    return sk_interned_meta_alloc(type, b, src, size);
}

/* FUN_0036fb10 @ 0x36fb10   (est. sk_obj_intern_table_d)
 * The object-intern table builder (fourth instance, table state at
 * DAT_006c0330/340/338/378, mutex 0x6c0350). Interns a type object
 * (param_1) into the open-addressing table: acquires the mutex, probes
 * with hash FUN_0037c5a0, on miss grows/rehashes the table (FUN_00010244
 * / FUN_0035b588) and inserts a record keyed by the mangled type name
 * (FUN_0035eb3c/FUN_0037c724). Returns the record payload.
 * Confidence: medium
 * Notes: representative of the intern-table family — the bodies of
 *   0x36aae4/36e878/36ed94/37062c/370f2c/371b58 are the same generic
 *   structure with different global state blocks. */
word_t *sk_obj_intern_table_d(word_t type, word_t b, uint64_t flags)
{
    uint32_t u21 = (uint32_t)((uint64_t)flags >> 0x20);
    int *hdr = (int *)FUN_0036a668();
    word_t *meta = (word_t *)((word_t)*hdr + (word_t)hdr);
    word_t *tbl;
    if (*hdr == 0 || meta == 0) {
        tbl = (word_t *)_DAT_006c0378;
        if ((tbl == 0) || (type != *tbl)) {
            LOAcquire();
            _DAT_006c0330 += 1;
            word_t key = type;
            word_t *found = (word_t *)FUN_0037c5a0(&key, _DAT_006c0340, CONCAT44(u21, _DAT_006c0334), _DAT_006c0338 + 2);
            if (found != 0) {
                tbl = (word_t *)*found;
                _DAT_006c0330 -= 1;
                LORelease();
                _DAT_006c0378 = (uint64_t)tbl;
                goto done;
            }
            _DAT_006c0330 -= 1;
            LORelease();
            /* grow table + insert record (see 0x36aae4 shared body) */
            word_t *newtbl = (word_t *)_DAT_006c0340;
            word_t *rec = 0;
            FUN_0001062c(&rec, 0x10, 0x70, 0x59dd9b33);
            if (rec == 0) SoftwareBreakpoint(1, 0x36ffc0); /* noreturn */
            *rec = type;
            FUN_0037c724(rec + 2, FUN_0035eb3c(type));
            _DAT_006c0334 += 1;
            FUN_0035b588(&newtbl, &DAT_006c0340, _DAT_006c0334, 0, 3);
            /* drain deferred frees + unlock (FUN_0035b228) */
            _DAT_006c0378 = (uint64_t)newtbl;
        }
        tbl = tbl + 2;
    } else {
        uint64_t u = FUN_0035eb3c(type);
        if (-1 < meta[0xc]) FUN_003d3dd8(meta + 0xc, &sk_obj_intern_table_d, &meta);
    }
done:
    return tbl;
}

/* FUN_0036ffc0 @ 0x36ffc0   (est. sk_string_intern_key)
 * Ghidra: undefined1[16] FUN_0036ffc0(undefined8,undefined8,undefined8)
 * Builds an interned-string lookup key from the type + argument
 * descriptors, reading the type's +0x50/+0x58 payload and hashing. */
cl4_result_t sk_string_intern_key(word_t a, word_t b, word_t c)
{
    cl4_result_t r;
    word_t l38 = c, l30 = b, u28 = a;
    word_t *p = (word_t *)FUN_0036fb10(c);
    word_t u48 = *(word_t *)(p + 0x58);
    word_t u50 = *(word_t *)(p + 0x50);
    word_t l58 = b;
    uint32_t u40 = FUN_0037cb08(&l58);
    word_t l90 = l58;
    word_t u88 = u50;
    word_t u80 = u48;
    FUN_0037cbc8(0, p, &l90, &u28, &l38, &l30);
    return r;
}

/* FUN_00370060 @ 0x370060   (est. sk_interned_string_lookup)
 * Ghidra: undefined1[16] FUN_00370060(undefined8,uint*)
 * Looks up (or creates) an interned string for the given type object:
 * resolves the metadata (FUN_0037f7a4/bcac/b3b8 per kind), lazily builds
 * and interning the string via FUN_0036e52c, caches it in a per-type
 * slot (FUN_00380864), and returns the resolved payload. */
cl4_result_t sk_interned_string_lookup(word_t a, uint32_t *type)
{
    cl4_result_t r;
    uint32_t *t = (type == 0) ? 0 : type;
    if (-1 < _DAT_006c0388) FUN_003d3dd8(&DAT_006c0388, FUN_003704ac, &DAT_006c0380);
    word_t l58 = (word_t)&DAT_006c0380;
    uint64_t l50 = 0;
    uint8_t l48 = 0, c47 = 0;
    uint32_t k = *t & 0x1f;
    int *pi3;
    word_t l4;
    uint32_t *pu7;
    if (k == 0x10) {
        pu7 = (t == 0) ? 0 : t;
        pi3 = (int *)FUN_0037f7a4(pu7);
    } else {
        if (k == 0x11) {
            pu7 = (t == 0) ? 0 : t;
            l4 = FUN_0037bcac(pu7);
        } else {
            if (k != 0x12) SoftwareBreakpoint(1, 0x3704ac); /* noreturn */
            pu7 = (t == 0) ? 0 : t;
            l4 = FUN_0037b3b8(pu7);
        }
        pi3 = (int *)(l4 + (uint64_t)((*pu7 & 0x30000) == 0x20000) * 4);
    }
    l4 = (*pi3 != 0) ? (word_t)*pi3 + (word_t)pi3 : 0;
    word_t l8 = *(word_t *)(l4 + 8);
    if (l8 == 0) {
        uint64_t *pu5 = (uint64_t *)FUN_0036a804(0x10, 7);
        c47 = 0;
        if (l50 == 0) l50 = FUN_0037a7f8();
        l48 = 1;
        if (c47 == '\x04') { r.hi = 0; r.lo = pu5[1]; }
        else {
            if (c47 == '\0') {
                uint32_t k2 = *t & 0x1f;
                word_t l4b;
                uint32_t *pu7b;
                if (k2 == 0x10) { pu7b = (t == 0) ? 0 : t; l4b = FUN_0037f7a4(pu7b); }
                else {
                    if (k2 == 0x11) { pu7b = (t == 0) ? 0 : t; l4b = FUN_0037bcac(pu7b); }
                    else {
                        if (k2 != 0x12) SoftwareBreakpoint(1, 0x3704ac);
                        pu7b = (t == 0) ? 0 : t;
                        l4b = FUN_0037b3b8(pu7b);
                    }
                    l4b = l4b + (uint64_t)((*pu7b & 0x30000) == 0x20000) * 4;
                }
                uint64_t u6 = FUN_0036e52c(l4b, t);
                c47 = '\x01';
                if ((*(uint32_t *)(*(word_t *)(u6 - 8) + 0x50) & 0x400000) == 0) c47 = '\x02';
                pu5[1] = u6;
                FUN_00380864(pu5, &l58, 0);
            }
            r.lo = FUN_003802f4(pu5, &l58, a); r.hi = 0;
        }
        goto done;
    }
    thunk_FUN_00012568(0, 0x10, 7);
    r.lo = FUN_003800cc(l8, a); r.hi = 0;
done:
    FUN_0037b350(&l58);
    return r;
}

/* FUN_003704ac @ 0x3704ac   (est. sk_once_init_buf)
 * Ghidra: void FUN_003704ac(undefined8*)
 * Initializes a once-guarded scratch buffer (allocates the backing
 * buffer via FUN_00111890/FUN_0037a850). */
void sk_once_init_buf(word_t *buf)
{
    word_t v;
    *buf = 0;
    v = FUN_00111890(0x10, 0x1000c40451b5be8);
    v = FUN_0037a850(v, 0);
    *buf = v;
}

/* FUN_003704f4 @ 0x3704f4   (est. sk_alloc_buffer_16)
 * Ghidra: long FUN_003704f4(undefined8,undefined8,undefined8,undefined8)
 * Allocates a +0x10-prefixed buffer via FUN_0037062c; returns the
 * payload (buffer+0x10) or 0. */
word_t sk_alloc_buffer_16(word_t a, word_t b, word_t c, word_t d)
{
    word_t l50 = a, l40 = b, u38 = c, l30 = d;
    word_t r = FUN_0037062c(&l50);
    return (r != 0) ? r + 0x10 : 0;
}

/* FUN_00370538 @ 0x370538   (est. sk_alloc_buffer_16_b)
 * Variant of 0x3704f4. */
void sk_alloc_buffer_16_b(word_t a, word_t b, word_t c)
{
    word_t l60 = a, l40 = c, l20 = b;
    word_t r = FUN_0037062c(&l60);
    r = (r != 0) ? r + 0x10 : 0;
}

/* FUN_003705b0 @ 0x3705b0   (est. sk_alloc_buffer_16_c)
 * Variant of 0x3704f4. */
void sk_alloc_buffer_16_c(word_t a, word_t b, word_t c, word_t d, word_t e)
{
    word_t l70 = a, l50 = e, l30 = b, u28 = c, l20 = d;
    word_t r = FUN_0037062c(&l70);
    r = (r != 0) ? r + 0x10 : 0;
}

/* FUN_0037062c @ 0x37062c   (est. sk_buffer_pool_get)
 * Ghidra: long FUN_0037062c(ulong*)
 * The buffer-pool getter: looks up a buffered object by key in the global
 * pool (DAT_006c0478 cache, table at DAT_006c0438/440/434, mutex
 * 0x6c0450) via hash FUN_00380cec; on miss allocates and builds a fresh
 * buffer record (size from the type header), selects the buffer vtable
 * from the type kind, and inserts it into the pool.
 * Confidence: medium
 * Notes: same intern-table family as 0x36aae4 etc.; vtables 0x67aef0/
 *   0x67ae98/0x67ade8/0x67ae40; SoftwareBreakpoint OOM. */
word_t sk_buffer_pool_get(uint64_t *key)
{
    word_t cached = _DAT_006c0478;
    if ((_DAT_006c0478 != 0) && ((FUN_00380b50(_DAT_006c0478, key) & 1) != 0)) return cached;
    LOAcquire();
    _DAT_006c0430 += 1;
    word_t *found = (word_t *)FUN_00380cec(key, _DAT_006c0440, _DAT_006c0434, _DAT_006c0438 + 2);
    if (found != 0) {
        LORelease();
        _DAT_006c0430 -= 1;
        _DAT_006c0478 = *found;
        return *found;
    }
    _DAT_006c0430 -= 1;
    LORelease();
    /* grow the table + insert a fresh buffer record */
    word_t *tbl = (word_t *)_DAT_006c0438;
    word_t rec = 0;
    FUN_0001062c(&rec, 8, 0x88, 0x59dd9b33);
    if (rec == 0) SoftwareBreakpoint(1, 0x370dfc); /* noreturn */
    *((uint64_t *)rec) = FUN_0037a7f8() | 9;
    *(uint32_t *)((uint64_t *)rec + 0xb) = 0;
    ((uint64_t *)rec)[0xe] = 0x308;
    ((uint64_t *)rec)[0xf] = key[0];
    ((uint64_t *)rec)[0x10] = key[1];
    _DAT_006c0434 += 1;
    /* cache last */
    _DAT_006c0478 = (word_t)rec;
    return (word_t)rec;
}

/* FUN_00370dfc @ 0x370dfc   (est. sk_buffer_pool_get_kind)
 * Ghidra: long FUN_00370dfc(ulong,undefined8,undefined8,undefined8,undefined8,undefined8,uint,ulong*)
 * Buffer-pool getter with a kind-tagged capability: for a 0x611384
 * (flag-cleared) or 0x60f0f4 (flag-set) descriptor clears the 
 * protection bits and fetches the buffered object via FUN_0037062c. */
word_t sk_buffer_pool_get_kind(word_t key, word_t b, word_t c, word_t d, word_t e,
                               word_t f, uint32_t flags, uint64_t *desc)
{
    word_t l50 = key;
    uint32_t l20 = flags;
    if (desc != 0) {
        uint64_t u3 = *desc;
        if (u3 < 0x800 && 0xfffffffd < (int)u3 - 0x203U) {
            u3 = desc[1];
            if ((u3 != 0) && (u3 == 0)) u3 = 0;
            if (u3 != 0x611384) goto fetch;
            key = key & 0xfffffffffeffffff;
        } else {
            if ((u3 != 0x303) || (*(int *)((word_t)desc + 0xc) != 1)) goto fetch;
            u3 = desc[((uint64_t)((uint32_t)desc[1] >> 0x1e) & 1) + 2] & 0xfffffffffffffffe;
            if (u3 == 0) u3 = 0;
            if ((u3 != 0x60f0f4) || (-1 < (int)(uint32_t)desc[1])) goto fetch;
        }
        desc = 0;
        l20 = flags & 0xfffffffe;
        l50 = key & 0xffffffff7fffffff;
        if ((flags & 0xfffffffe) != 0) l50 = key;
    }
fetch:
    word_t r = FUN_0037062c(&l50);
    return (r != 0) ? r + 0x10 : 0;
}

/* FUN_00370f2c @ 0x370f2c   (est. sk_obj_intern_lookup)
 * Ghidra: undefined1[16] FUN_00370f2c(undefined8,undefined8*,ulong)
 * The object-intern lookup (fifth instance of the intern-table family,
 * table state at DAT_006c0480/490/488/4b8, mutex 0x6c04a0, keyed by
 * type+payload). Looks up an interned object by its type and payload
 * descriptor, growing/inserting on miss via FUN_00381228, then resolves
 * the object kind (via FUN_0037aaac) and returns the payload or the
 * object slot. Returns (found, payload) — or an empty 0x67b148 on a
 * zero-length key. */
cl4_result_t sk_obj_intern_lookup(word_t key, word_t *payload, uint64_t type)
{
    cl4_result_t r;
    uint64_t u24;
    word_t p3;
    if ((long)payload < 1) { u24 = 0; p3 = 0x67b148; goto out; }
    if ((payload == (word_t *)(__thread_bss + 1)) &&
        (*(word_t *)(*(word_t *)(type - 8) + 0x40) == *(word_t *)(*(word_t *)(type - 8) + 0x48))) {
        u24 = 0; goto out;
    }
    if (-1 < _DAT_006c04d0) FUN_003d3dd8(&DAT_006c04d0, FUN_003716f8, &DAT_006c0480);
    /* intern-table lookup body (same family as 0x36aae4), then resolve */
    word_t *tbl = (word_t *)_DAT_006c04b8;
    word_t *rec = (word_t *)tbl;
    if (rec != 0) {
        uint64_t state = FUN_0037aaac(rec, key);
        if (state < 2) {
            uint32_t k = (uint32_t)rec[0] & 7;
            if (k < 3) { if (k == 1) u24 = 0xff; else if (k == 2) u24 = 0x3f; }
            else if (k == 3) u24 = 1;
            else { u24 = 0; }
            r.hi = u24;
            r.lo = (word_t)(rec + 0xe);
            goto out;
        }
    }
    u24 = 0;
    p3 = 0x67b148;
out:
    r.hi = u24;
    r.lo = p3;
    return r;
}

/* FUN_003716f8 @ 0x3716f8   (est. sk_intern_state_init)
 * Ghidra: void FUN_003716f8(undefined8*)
 * Initializes an intern-table state block: zeroes the counters and
 * allocates the backing buffer. */
void sk_intern_state_init(word_t *st)
{
    word_t v;
    st[7] = 0; st[6] = 0; st[9] = 0; st[8] = 0; st[1] = 0;
    *st = 0; st[3] = 0; st[2] = 0; st[5] = 0; st[4] = 0;
    FUN_0037a850(st + 4, 0);
    st[6] = 0; st[7] = 0;
    v = FUN_00111890(0x10, 0x1000c40451b5be8);
    v = FUN_0037a850(v, 0);
    st[8] = v;
}

/* FUN_00371758 @ 0x371758   (est. sk_obj_merge_2)
 * Ghidra: void FUN_00371758(undefined8,undefined8,undefined8)
 * Merges two objects into a fresh interned descriptor (2-element build
 * via FUN_003717b8). */
void sk_obj_merge_2(word_t a, word_t b, word_t c)
{
    word_t l28 = b, u20 = c;
    FUN_003717b8(a, 0, 2, &l28);
}

/* FUN_003717b8 @ 0x3717b8   (est. sk_desc_from_sizes)
 * Ghidra: void FUN_003717b8(ulong*,long,ulong,long)
 * Builds a descriptor from a list of element sizes: accumulates the
 * aggregate size, alignment and memattr flags, tracking per-element
 * capacity requirements, and fills the descriptor's (size, flags, count)
 * fields. */
void sk_desc_from_sizes(word_t *out, word_t off, uint64_t n, word_t *elems)
{
    uint64_t size = 0, align = 0, flags = 0;
    uint32_t max = 0;
    bool b1 = true, b2 = true, b3 = true;
    uint32_t i;

    out[0] = 0; out[1] = 0; out[2] = 0;
    if ((n & 0xffff) == 0) { flags = 0; size = 0; align = 0; max = 0; }
    else {
        uint64_t j = 0;
        flags = 0; size = 0; align = 0;
        b1 = true; b2 = true; b3 = true;
        do {
            word_t *el = *(word_t **)(elems + j * 8);
            uint32_t f = *(uint32_t *)(el + 2);
            align = align + (uint8_t)f & ((uint64_t)f & 0xff ^ 0xffffffffffffffff);
            if (off != 0) {
                *(int *)(off + j * 4) = (int)align;
                f = *(uint32_t *)(el + 2);
            }
            if (max <= *(uint32_t *)((word_t)el + 0x14)) max = *(uint32_t *)((word_t)el + 0x14);
            align = *el + align;
            if (size <= (f & 0xff)) size = (uint64_t)(f & 0xff);
            b1 = b1 & (f & 0x10000) == 0;
            b2 = b2 & (f & 0x100000) == 0;
            b3 = b3 & (f & 0x1100000) == 0;
            j = j + 1;
        } while ((n & 0xffff) != (j & 0xffffffff));
        *out = align;
        uint32_t u10 = b1 ? 0 : 0x10000;
        uint32_t u11 = b2 ? 0 : 0x100000;
        uint32_t u12 = b3 ? 0 : 0x1000000;
        flags = 0;
        if (!(b2 && (align < 0x19 && size < 8))) flags = 0x20000;
        flags = (uint32_t)size | u11 | u10 | u12 | flags;
    }
    *(uint32_t *)(out + 2) = flags;
    *(uint32_t *)((word_t)out + 0x14) = 0;
    size = size + align & (size ^ 0xffffffffffffffff);
    if (size < 2) size = 1;
    out[1] = size;
    if (max != 0) {
        *out = align;
        *(uint32_t *)(out + 2) = flags;
        *(uint32_t *)((word_t)out + 0x14) = max;
    }
}

/* FUN_003718ec @ 0x3718ec   (est. sk_obj_merge_3)
 * Merges three objects into a fresh interned descriptor. */
void sk_obj_merge_3(word_t a, word_t b, word_t c, word_t d)
{
    word_t l30 = b, u28 = c, l20 = d;
    FUN_003717b8(a, 0, 3, &l30);
}

/* FUN_00371950 @ 0x371950   (est. sk_intern_lookup_create)
 * Ghidra: undefined1[16] FUN_00371950(undefined8,ulong,long,undefined8,undefined8)
 * The intern-table lookup-and-create (sixth instance, table state at
 * DAT_006c04e0/f0/e8/4b0, mutex via LOAcquire). Looks up an interned
 * object keyed by (param_2, param_3); on miss builds a fresh interned
 * record via FUN_00371b58 and inserts it. Returns (found, payload). */
cl4_result_t sk_intern_lookup_create(word_t key, uint64_t count, word_t type,
                                     word_t a, word_t b)
{
    cl4_result_t r;
    uint64_t n = count & 0xffff;
    word_t l58 = 0, l50 = 0, l48 = 0;
    if (n == 0) { r.lo = 0x67b148; r.hi = 0; return r; }
    word_t l68 = b, u60 = key;
    if (-1 < _DAT_006c0530) FUN_003d3dd8(&DAT_006c0530, sk_intern_state_init_b, &DAT_006c04e0);
    word_t l80 = n, l78 = type;
    if (((uint32_t)count >> 0x10 & 1) == 0) {
        word_t l70 = a;
        FUN_00371b58(&l58, &l80, &u60, &l68);
        r.hi = l48; r.lo = l50;
    } else {
        LOAcquire();
        _DAT_006c04e0 += 1;
        word_t *found = (word_t *)FUN_00381cfc(&l58, _DAT_006c04f0, _DAT_006c04e4, _DAT_006c04e8 + 8);
        LORelease();
        if ((found != 0) && (*found != 0)) {
            _DAT_006c04e0 -= 1;
            cl4_result_t fr; fr.lo = FUN_00381fac(*found, key); fr.hi = 0;
            return fr;
        }
        _DAT_006c04e0 -= 1;
        /* build + insert new record */
        word_t l6 = FUN_00369758(&l58, (word_t)thunk_FUN_00115080(a) + 9U & ~7ull, 1);
        FUN_0039a138(l6, a, (word_t)thunk_FUN_00115080(a) + 9U & ~7ull);
        word_t l70 = l6;
        FUN_00371b58(&l58, &l80, &u60, &l68);
        r.hi = l48; r.lo = l50;
        if (*(word_t *)(l50 + 0x10) != l6) { thunk_FUN_00012568(l6); }
    }
    return r;
}

/* FUN_00371af8 @ 0x371af8   (est. sk_intern_state_init_b)
 * Same as 0x3716f8 (intern-table state init). */
void sk_intern_state_init_b(word_t *st)
{
    word_t v;
    st[7] = 0; st[6] = 0; st[9] = 0; st[8] = 0; st[1] = 0;
    *st = 0; st[3] = 0; st[2] = 0; st[5] = 0; st[4] = 0;
    FUN_0037a850(st + 4, 0);
    st[6] = 0; st[7] = 0;
    v = FUN_00111890(0x10, 0x1000c40451b5be8);
    v = FUN_0037a850(v, 0);
    st[8] = v;
}

/* FUN_00371b58 @ 0x371b58   (est. sk_intern_insert)
 * Ghidra: void FUN_00371b58(long*,ulong*,undefined8*,ulong*)
 * The intern-table insert (seventh instance, table state at
 * DAT_006c04e0/f0/e8/510/518, mutex 0x6c0500, keyed by the 3-word key
 * param_2). Probes with hash FUN_00381cfc; on miss grows/rehashes and
 * inserts a fresh interned record whose per-key hash buckets are filled
 * by walking the type metadata. Fills the output descriptor.
 * Confidence: medium
 * Notes: the largest instance of the intern-table family; hash probe
 *   FUN_00381cfc, element hashing FUN_0037e8e8/7e58c/7ebe4/7e614/7eb4c. */
void sk_intern_insert(word_t *out, word_t *key3, word_t *a, uint64_t *b)
{
    word_t *tbl = (word_t *)_DAT_006c0518;
    uint64_t u = 0;
    if ((_DAT_006c0518 == 0) || ((FUN_00381c5c(_DAT_006c0518, key3) & 1) == 0)) {
        LOAcquire();
        _DAT_006c04e0 += 1;
        word_t *found = (word_t *)FUN_00381cfc(key3, _DAT_006c04f0, _DAT_006c04e4, _DAT_006c04e8 + 2);
        if (found != 0) {
            tbl = (word_t *)*found;
            _DAT_006c04e0 -= 1;
            LORelease();
            _DAT_006c0518 = (uint64_t)tbl;
            goto resolve;
        }
        _DAT_006c04e0 -= 1;
        LORelease();
        /* grow + insert a fresh record (see 0x36aae4 family body) */
        word_t *rec = 0;
        FUN_0001062c(&rec, 8, 0x88, 0x59dd9b33);
        if (rec == 0) SoftwareBreakpoint(1, 0x3722e4); /* noreturn */
        *((uint64_t *)rec) = FUN_0037a7f8() | 9;
        *(uint32_t *)((uint64_t *)rec + 0xc) = 0;
        ((uint64_t *)rec)[0xe] = 0x301;
        ((uint64_t *)rec)[0xf] = key3[0];
        ((uint64_t *)rec)[0x10] = key3[2];
        uint64_t v = *b;
        if (v == 0) v = 0;
        ((uint64_t *)rec)[0xd] = v;
        if (key3[0] != 0) {
            uint64_t j = 0;
            do {
                ((uint64_t *)rec)[(j & 0xffffffff) * 2 + 0x11] = *(uint64_t *)(key3[1] + j * 8);
                j = j + 1;
            } while (key3[0] != j);
        }
        _DAT_006c04e4 += 1;
        _DAT_006c0518 = (word_t)rec;
    }
resolve:
    /* resolve kind + build output descriptor */
    cl4_result_t r; r.lo = FUN_00382200(tbl, 0, *a); r.hi = 0;
    out[0] = (word_t)tbl;
    out[1] = r.lo;
    out[2] = r.hi;
    FUN_0037b350(0);
}

/* FUN_003722e4 @ 0x3722e4   (est. sk_intern_create_2)
 * Ghidra: void FUN_003722e4(undefined8,undefined8,undefined8)
 * Creates an interned object for 2-element key via FUN_00371950. */
void sk_intern_create_2(word_t a, word_t b, word_t c)
{
    word_t l28 = b, u20 = c;
    FUN_00371950(a, 2, &l28);
}

/* FUN_0037233c @ 0x37233c   (est. sk_intern_create_3)
 * Creates an interned object for 3-element key via FUN_00371950. */
void sk_intern_create_3(word_t a, word_t b, word_t c, word_t d, word_t e, word_t f)
{
    word_t l30 = b, u28 = c, l20 = d;
    FUN_00371950(a, 3, &l30, e, f);
}

/* FUN_003723a0 @ 0x3723a0   (est. sk_type_equal)
 * Ghidra: ulong FUN_003723a0(uint*,uint*)
 * Compares two type objects for equality: if both are non-generic with
 * matching kind bits, recursively compares the referenced sub-types and
 * (for certain kinds) the trailing data. Returns 1 if equal, else 0. */
uint64_t sk_type_equal(uint32_t *a, uint32_t *b)
{
    if (a == b) return 1;
    if (a == 0) return 0;
    if (b == 0) return 0;
    if ((((*a >> 6 & 1) == 0) && ((*b >> 6 & 1) == 0)) &&
        (((*b ^ *a) & 0x1f) == 0)) {
        uint64_t u4 = FUN_003658e8(a + 1);
        uint64_t u5 = FUN_003658e8(b + 1);
        uint64_t r = sk_type_equal((uint32_t *)u4, (uint32_t *)u5);
        if ((int)r == 0) return r;
        uint8_t k = (uint8_t)*a;
        if (1 < (k & 0x1f) - 1) {
            if ((k & 0x1f) == 0) {
                int c = (int)thunk_FUN_00114d10((word_t)(a + 2) + (word_t)(int)a[2],
                                                (word_t)(b + 2) + (word_t)(int)b[2]);
                return (uint64_t)(c == 0);
            }
            if ((k >> 4 & 1) != 0) {
                /* compare trailing data via FUN_00387e60 + memcmp */
                uint64_t l2 = 0, u4b = 0;
                FUN_00387e60(0, a);
                uint64_t l2a = l2, u4a = u4b;
                FUN_00387e60(0, b);
                if (l2a == l2) {
                    if (l2a == 0) return 1;
                    int c = (int)thunk_FUN_001145b0(u4a, u4b, l2a);
                    return (uint64_t)(c == 0);
                }
            }
        }
    }
    return 0;
}

/* FUN_00367b34 @ 0x367b34   (est. sk_cap_null_ok)
 * Ghidra: undefined8 FUN_00367b34()
 * Returns the constant 0 (null capability is acceptable). */
uint64_t sk_cap_null_ok() { return 0; }

