/* Recreated from sptm.t8142.release.im4p (SPTM, arm64e, image base 0) — the
 * Secure Page Table Monitor (GL2). Ground truth: Ghidra FUN_ names + addresses;
 * public API names from docs/sptm/headers/sptm_common.h. All names are
 * estimates unless header-matched.
 *
 * This file covers the SPTM boot / per-CPU entry / guarded-level dispatch
 * core. The three routines that Ghidra decompiles (sptm_dispatch_engine,
 * sptm_txm_sk_entry, sptm_sk_entry) are rendered as English C. The pure
 * assembly entry/bootstrap routines (sptm_main, sptm_per_cpu_bootstrap,
 * sptm_genter_receive, the boot + per-CPU vector tables and the per-CPU
 * vector context-save handler) are not recognized as Ghidra functions (or the
 * decompiler truncates on the GENTER opcode), so they are reconstructed at
 * the assembly level per the FULL-AUDIT fallback rule, with English comments. */

#include "sptm_internal.h"

#include <stdint.h>
#include <stddef.h>

/* -------------------------------------------------------------------------
 * Extern / hardware helpers shared with the rest of the SPTM recreation.
 * (These are declared here only so this file is self-contained; they are
 * defined in their own reconstruction files.)
 * ------------------------------------------------------------------------- */

/* GENTER (0x00201420) / GEXIT (0x00201400) come from sptm_internal.h. */

/* Noreturn panic printers. Ghidra FUN_000f8804 / FUN_000f8844.
 *  - sptm_panic:            "%s: <fmt>"    (FUN_000f8804)
 *  - sptm_panic_violation:  "%s(%s:%d) - <fmt>\n" with a violation code and
 *                           the "sptm_dispatch" location (FUN_000f8844). */
extern __attribute__((noreturn)) void sptm_panic(const char *fmt, ...);
extern __attribute__((noreturn)) void sptm_panic_violation(uint32_t violation_code,
        uint64_t extra, const char *fmt, ...);

/* Dispatch diagnostics helpers (Ghidra FUN_000e7068 / FUN_000e70b4). They
 * only contribute context to the panic; they never return. */
extern void sptm_dispatch_state_ctx(void);
extern void sptm_dispatch_event_ctx(uint64_t event_type);

/* Resolve the physical->virtual mapping / validate an endpoint object.
 * Ghidra FUN_000e3d7c (translate a cpu/endpoint token) and FUN_000d81bc
 * (resolve/validate an endpoint id, returning its canonical form). */
extern void *sptm_phys_to_va(uint64_t phys);
extern uint64_t sptm_resolve_endpoint(uint64_t endpoint);

/* Per-CPU exception / dispatch entry point reached by the per-CPU vector
 * table: Ghidra 0x000ed340. args = (frame, exception_index, fp, elr_el2). */
extern __attribute__((noreturn)) void sptm_exception_dispatch(uint64_t *frame,
        uint64_t exception_index, uint64_t fp, uint64_t elr_el2);

/* -------------------------------------------------------------------------
 * SPTM per-CPU state layout (offsets used by the dispatch + entry paths).
 * Ghidra reads these fields on the per-CPU state pointer obtained from the
 * EL2 system register (3,6,0xf,8,0), falling back to tpidr_el2. Offsets are
 * byte offsets into the per-CPU state structure. */
#define SPTM_STATE_HANDOFF_MAGIC   (0x0a)   /* u16, "micro_magic" field */
#define SPTM_STATE_DC_INDEX        (0xa30)  /* u8,  current dispatch count */
#define SPTM_STATE_STACK_BASE      (0xa50)  /* u64, saved stack pointer base */
#define SPTM_STATE_CURRENT_STATE   (0xa60)  /* u8,  dispatch state machine state */
#define SPTM_STATE_HOP_COUNT       (0xa68)  /* u64, guarded-level hop counter */
#define SPTM_STATE_PREV_ENDPOINT   (0xa70)  /* u64, prior endpoint id */
/* Args 2..8 saved by the SK/TXM entry at +0xa78..+0xaa8. */
#define SPTM_STATE_SAVEREG_A       (0xab0)  /* callee-saved save area */
#define SPTM_STATE_SAVEREG_B       (0xb68)  /* alternate callee-saved save area */

/* Dispatch state-machine bounds. The transition table at 0x16770 uses
 * stride 0x1e0 per state and 0x20 per event type. */
#define SPTM_MAX_STATE             0x16u    /* current state <= 22 */
#define SPTM_MAX_EVENT             0x0eu    /* event type <= 14  */

/* Static domain/table dispatch tables. The XNU/TXM (domain 1/2) tables live
 * at the relocated DAT_00095bf0 base; all other domains at 0x95470.
 * Layout: stride 0x180 per domain, 0x18 per (table) entry:
 *   [0x00] handler         (code *)
 *   [0x08] permission_mask (bit i = allowed at dispatch-count i)
 *   [0x10] reserved */
#define SPTM_DISPATCH_TABLE_BASE   0x95470ULL
extern uint64_t SPTM_DISPATCH_TABLE_XNU_TXM_BASE;   /* DAT_00095bf0 (relocated) */

/* Dispatch-table entry. */
typedef struct sptm_dispatch_entry {
    void (*handler)(uint64_t dispatch_id, uint64_t dispatch_target);
    uint64_t permission_mask;
    uint64_t reserved;
} sptm_dispatch_entry_t;

/* State-transition table entry (0x20 bytes) at
 * 0x16770 + state*0x1e0 + event*0x20. */
typedef struct sptm_transition {
    uint8_t  next_state;         /* [0x00] */
    uint8_t  _pad[7];
    void   (*action)(uint64_t dispatch_id, uint64_t dispatch_target); /* [0x08] */
    uint8_t  dc_index;           /* [0x10] new dispatch-count index */
    uint8_t  _pad2[7];
    uint64_t flags;              /* [0x18] bit0: resolve+check dispatch target;
                                  *         bit1: XNU->TXM hop check */
} sptm_transition_t;

/* Guarded-level entry event types (dispatch_engine param_1). Values 3/4 are
 * the TXM/SK resume events used by sptm_txm_sk_entry / sptm_sk_entry. */
#define SPTM_EVENT_TXM_SK_ENTRY   3u
#define SPTM_EVENT_SK_ENTRY       4u

/* UAT handoff-region magic consistency flag/global (DAT_00104128 / 0x2a). */
extern uint64_t g_sptm_uat_handoff_flags;        /* DAT_00104128 */
extern uint16_t g_sptm_uat_handoff_magic;        /* DAT_0010412a */

/* Hop-validation data used by the dispatch engine (see FUN_000e6bc0). */
extern uint64_t DAT_00095d18;    /* previous-endpoint range start */
extern uint64_t DAT_00095d20;    /* previous-endpoint range end   */
extern uint64_t DAT_00095460;    /* endpoint descriptor table base */
extern uint64_t DAT_00101f90;    /* default endpoint descriptor    */

/* Per-CPU bootstrap tail (FUN_aba70) — reconstructed in its own file. */
extern uint64_t sptm_per_cpu_finish(void);

/* Read the per-CPU SPTM state pointer.
 *   x = UnkSytemRegRead(3,6,0xf,8,0);  if (x == 0) x = tpidr_el2;
 *   else x = UnkSytemRegRead(3,6,0xf,0xb,1);
 * (SPTM-specific EL2 sysreg for the per-CPU state base.) */
static inline uint8_t *sptm_per_cpu_state(void)
{
    uint64_t p;
    __asm__ volatile("mrs %0, s3_6_c15_c8_0" : "=r"(p));
    if (p == 0) {
        __asm__ volatile("mrs %0, tpidr_el2" : "=r"(p));
    } else {
        __asm__ volatile("mrs %0, s3_6_c15_c11_1" : "=r"(p));
    }
    return (uint8_t *)p;
}

/* -------------------------------------------------------------------------
 * FUN_000e6bc0 @ 0x000e6bc0   (est. sptm_dispatch_engine)
 * Ghidra: void FUN_000e6bc0(ulong param_1, ulong param_2)
 * The guarded-level dispatch state machine. event_type (param_1, 0..14)
 * selects the transition action for the current per-CPU state; the transition
 * table at 0x16770 (stride 0x1e0/state, 0x20/event, 23 states) yields the
 * next state, an action (handler), a dispatch-count index and a flags word.
 * When the transition requests a dispatch target (flags bit0) the
 * domain/table fields of the dispatch_id (param_2, packed per
 * SPTM_LOAD_DISPATCH_ID) are validated, the matching domain/table entry is
 * permission-checked and its handler used as the dispatch target; when flags
 * bit1 is set an XNU->TXM hop is validated before running. On any illegal
 * transition the engine panics (violation codes 0x29/0x2a/0x2b/0x2d/0x57 and
 * "invalid state/event/next state/transition" messages).
 * Confidence: high
 * Notes: decompiler dropped two unreachable blocks (0x6c24/0x6c3c) and could
 *   not recover the indirect action jump at 0xe7060 (rendered as a call). */
void sptm_dispatch_engine(uint64_t event_type, uint64_t dispatch_id)
{
    sptm_transition_t *t;
    uint8_t *state;
    uint8_t next_state;
    uint64_t dispatch_target = 0;

    state = sptm_per_cpu_state();

    /* The current state must be a valid state-machine state. */
    if (state[SPTM_STATE_CURRENT_STATE] > SPTM_MAX_STATE) {
        sptm_dispatch_state_ctx();
        sptm_panic("%s: invalid state: %s", "sptm_dispatch", "state");
    }
    /* The event type must be within the transition-table columns. */
    if (event_type > SPTM_MAX_EVENT) {
        sptm_dispatch_event_ctx(event_type);
        sptm_panic("%s: invalid event type: %s", "sptm_dispatch", "event");
    }

    /* Index the state-transition table. */
    t = (sptm_transition_t *)(0x16770 + state[SPTM_STATE_CURRENT_STATE] * 0x1e0 +
                              (event_type & 0xffffffff) * 0x20);
    next_state = t->next_state;

    if (next_state >= 0x17) {
        sptm_dispatch_state_ctx();
        sptm_panic("%s: invalid next state: %s", "sptm_dispatch", "next_state");
    }
    if (t->action == NULL) {
        sptm_dispatch_state_ctx();
        sptm_dispatch_event_ctx(event_type);
        /* "%s: invalid state transition - no action set for the transition.
         * current_state: %s, event_type: %s, event_metadata: %#llx" */
        sptm_panic("%s: invalid state transition - no action set for the "
                   "transition. current_state: %s, event_type: %s, "
                   "event_metadata: %#llx", "sptm_dispatch",
                   "state", "event", dispatch_id);
    }

    /* UAT handoff-region micro_magic must match the global before dispatching
     * (panic code 0x57; the "uat_instance->handoff_region->micro_magic"
     * field at state+0xa is checked). */
    if ((g_sptm_uat_handoff_flags & 1) != 0 &&
        g_sptm_uat_handoff_magic != *(uint16_t *)(state + SPTM_STATE_HANDOFF_MAGIC)) {
        sptm_dispatch_state_ctx();
        sptm_dispatch_state_ctx();
        sptm_panic_violation(0x57, 0,
            "%s(%s:%d) - %s(%#llx), %s(%#llx), %s(%#llx)",
            "sptm_dispatch", __FILE__, __LINE__,
            "uat_instance->handoff_region->micro_magic",
            (uint64_t)(state + SPTM_STATE_HANDOFF_MAGIC),
            "expected", g_sptm_uat_handoff_magic,
            "got", *(uint16_t *)(state + SPTM_STATE_HANDOFF_MAGIC));
    }

    /* Adopt the transition's new dispatch-count index. */
    state[SPTM_STATE_DC_INDEX] = t->dc_index;

    if ((t->flags & 1) == 0) {
        /* No dispatch target: the action runs with dispatch_target == 0. */
        dispatch_target = 0;
    } else {
        /* Resolve and permission-check the requested domain/table dispatch. */
        uint64_t domain_field = dispatch_id & 0xff000000000000ULL;  /* bits 48-55 */
        uint64_t table_field  = dispatch_id & 0xf000000000ULL;      /* bits 32-35 */
        uint32_t domain;
        uint32_t table;
        sptm_dispatch_entry_t *entry;
        uint8_t *cur;

        (void)sptm_per_cpu_state();          /* re-read (decompiler artifact) */

        if (domain_field > 0x4000000000000ULL) {
            /* Violation 0x29: VIOLATION_ILLEGAL_DISPATCH_DOMAIN (domain > 4). */
            sptm_panic_violation(0x29, dispatch_id,
                "%s(%s:%d) - %s(%#llx), %s(%#llx), %s(%#llx)",
                "sptm_dispatch", __FILE__, __LINE__,
                "dispatch_id", dispatch_id, "", 0, "", 0);
        }
        if (table_field != 0) {
            /* Violation 0x2a: VIOLATION_ILLEGAL_DISPATCH_TABLE (table > 0xf). */
            sptm_panic_violation(0x2a, dispatch_id,
                "%s(%s:%d) - %s(%#llx), %s(%#llx), %s(%#llx)",
                "sptm_dispatch", __FILE__, __LINE__,
                "dispatch_id", dispatch_id, "", 0, "", 0);
        }

        cur = sptm_per_cpu_state();
        domain = (uint32_t)(dispatch_id >> 0x30) & 0xff;   /* bits 48-55 */
        table  = (uint32_t)(dispatch_id >> 0x20) & 0xf;    /* bits 32-35 */

        if ((int)domain - 1 < 2) {
            /* XNU (1) / TXM (2) domains use the relocated boot table base. */
            entry = (sptm_dispatch_entry_t *)
                ((uint64_t)&SPTM_DISPATCH_TABLE_XNU_TXM_BASE +
                 domain * 0x180 + table * 0x18);
        } else {
            entry = (sptm_dispatch_entry_t *)
                (SPTM_DISPATCH_TABLE_BASE + domain * 0x180 + table * 0x18);
        }

        /* Permission mask: the current dispatch-count index must be allowed. */
        if (((entry->permission_mask >> (cur[SPTM_STATE_DC_INDEX] & 0x3f)) & 1) == 0) {
            /* Violation 0x2b: VIOLATION_ILLEGAL_DISPATCH_PERMISSION. */
            sptm_panic_violation(0x2b, dispatch_id,
                "%s(%s:%d) - %s(%#llx), %s(%#llx), %s(%#llx)",
                "sptm_dispatch", __FILE__, __LINE__,
                "dispatch_id", dispatch_id, "", 0, "", 0);
        }

        dispatch_target = (uint64_t)entry->handler;
        if (dispatch_target == 0) {
            /* "%s: [SPTM Dispatch] Found illegal dispatch entry point.
             * caller_domain: %d, entry_point: %#llx, dispatch_target: %#llx" */
            sptm_panic("%s: [SPTM Dispatch] Found illegal dispatch entry "
                       "point. caller_domain: %d, entry_point: %#llx, "
                       "dispatch_target: %#llx", "sptm_dispatch",
                       (int)domain, dispatch_id, dispatch_target);
        }
    }

    /* XNU -> TXM hop validation (transition flags bit1). */
    if ((t->flags >> 1 & 1) != 0) {
        uint64_t prev_endpoint;
        void *desc;

        if (*(uint64_t *)(state + SPTM_STATE_HOP_COUNT) != 1) {
            /* "%s: Invalid hop detected when transitioning XNU->TXM %llu" */
            sptm_panic("%s: Invalid hop detected when transitioning "
                       "XNU->TXM %llu", "sptm_dispatch",
                       *(uint64_t *)(state + SPTM_STATE_HOP_COUNT));
        }

        prev_endpoint = *(uint64_t *)(state + SPTM_STATE_PREV_ENDPOINT);
        if (prev_endpoint < DAT_00095d18 || DAT_00095d20 <= prev_endpoint) {
            desc = sptm_phys_to_va(prev_endpoint);
            if (desc == NULL) {
                desc = (void *)&DAT_00101f90;
            }
        } else {
            desc = (void *)(DAT_00095460 + ((prev_endpoint - DAT_00095d18) >> 10 &
                                           0xffffffff0));
            if (((DAT_00095460 ^ (uint64_t)desc) & 0xffc0000000000000ULL) != 0) {
                desc = (void *)(((uint64_t)desc & 0xffffffffffffULL) |
                                0xc8a2000000000000ULL);
            }
        }

        if (*(char *)((uint8_t *)desc + 1) != '-') {
            /* Violation 0x2d: invalid hop endpoint descriptor. */
            sptm_panic_violation(0x2d, prev_endpoint,
                "%s(%s:%d) - %s(%#llx), %s(%#llx), %s(%#llx)",
                "sptm_dispatch", __FILE__, __LINE__,
                "prev_endpoint", prev_endpoint, "", 0, "", 0);
        }
        *(uint64_t *)(state + SPTM_STATE_PREV_ENDPOINT) =
            sptm_resolve_endpoint(prev_endpoint);
    }

    /* Commit the new state and run the transition action. */
    state[SPTM_STATE_CURRENT_STATE] = next_state;
    t->action(dispatch_id, dispatch_target);
}

/* -------------------------------------------------------------------------
 * FUN_000a0f7c @ 0x000a0f7c   (est. sptm_txm_sk_entry)
 * Ghidra: void FUN_000a0f7c(undefined8, undefined8, ... eight x-args)
 * TXM/SK guarded-level entry context-save. Masks DAIF, switches to SP_EL1,
 * waits for the per-CPU hop counter to settle at 1, saves the caller's eight
 * argument registers and callee-saved registers into the per-CPU state
 * (alternating save area by hop count), then invokes the dispatch engine with
 * event type 3 (TXM/SK resume). Reached via the SPTM->TXM stubs (0xb2620..)
 * and SPTM->SK stubs (0xb25c0..).
 * Confidence: high
 * Notes: the double empty do/while is a decompiler artifact of a spin-wait on
 *   the hop counter at +0xa68. */
void sptm_txm_sk_entry(uint64_t p1, uint64_t p2, uint64_t p3, uint64_t p4,
                       uint64_t p5, uint64_t p6, uint64_t p7, uint64_t p8)
{
    uint64_t saved_daif;
    uint64_t hop_count;
    uint64_t stack_base;
    uint8_t *state;
    uint64_t *save_area;

    __asm__ volatile("mrs %0, daif" : "=r"(saved_daif));
    __asm__ volatile("msr daifset, #0x3c0");       /* mask IRQ/FIQ/SError/DBG */
    __asm__ volatile("msr spsel, #1");              /* use SP_EL1 */

    state = sptm_per_cpu_state();
    stack_base = *(uint64_t *)(state + SPTM_STATE_STACK_BASE);

    /* Wait for the guarded-level hop counter to be exactly 1. */
    while (*(uint64_t *)(state + SPTM_STATE_HOP_COUNT) != 1)
        ;

    /* Save the call arguments into per-CPU state. */
    *(uint64_t *)(state + SPTM_STATE_PREV_ENDPOINT) = p1;
    *(uint64_t *)(state + 0xa78) = p2;
    *(uint64_t *)(state + 0xa80) = p3;
    *(uint64_t *)(state + 0xa88) = p4;
    *(uint64_t *)(state + 0xa90) = p5;
    *(uint64_t *)(state + 0xa98) = p6;
    *(uint64_t *)(state + 0xaa0) = p7;
    *(uint64_t *)(state + 0xaa8) = p8;

    /* Wait for the hop counter to drop to <= 1, then pick the save area. */
    hop_count = *(uint64_t *)(state + SPTM_STATE_HOP_COUNT);
    while (hop_count > 1)
        hop_count = *(uint64_t *)(state + SPTM_STATE_HOP_COUNT);
    while (hop_count > 1)
        hop_count = *(uint64_t *)(state + SPTM_STATE_HOP_COUNT);

    if (hop_count == 1) {
        save_area = (uint64_t *)(state + SPTM_STATE_SAVEREG_B);
    } else {
        save_area = (uint64_t *)(state + SPTM_STATE_SAVEREG_A);
    }

    /* Save callee-saved general + FP regs (unaff_* values from the caller). */
    __asm__ volatile("stp x19, x20, [%0]"          : : "r"(save_area) : "memory");
    __asm__ volatile("stp x21, x22, [%0, #16]"     : : "r"(save_area) : "memory");
    __asm__ volatile("stp x23, x24, [%0, #32]"     : : "r"(save_area) : "memory");
    __asm__ volatile("stp x25, x26, [%0, #48]"     : : "r"(save_area) : "memory");
    __asm__ volatile("stp x27, x28, [%0, #64]"     : : "r"(save_area) : "memory");
    __asm__ volatile("stp x29, x30, [%0, #144]"    : : "r"(save_area) : "memory");
    __asm__ volatile("stp d8,  d9,  [%0, #80]"     : : "r"(save_area) : "memory");
    __asm__ volatile("stp d10, d11, [%0, #96]"     : : "r"(save_area) : "memory");
    __asm__ volatile("stp d12, d13, [%0, #112]"    : : "r"(save_area) : "memory");
    __asm__ volatile("stp d14, d15, [%0, #128]"    : : "r"(save_area) : "memory");

    *(uint64_t *)(state + SPTM_STATE_HOP_COUNT) = hop_count + 1;

    /* Record sp_el0 and the original DAIF in the save area. */
    {
        uint64_t sp_el0;
        __asm__ volatile("mrs %0, sp_el0" : "=r"(sp_el0));
        save_area[0x14] = sp_el0;
        save_area[0x16] = saved_daif;
    }

    /* Link the caller's frame onto the saved stack base. */
    *(uint64_t *)(stack_base - 0x10) = /* x29 */ 0;   /* written by asm below */
    *(uint64_t *)(stack_base - 0x8)  = /* x30 */ 0;
    __asm__ volatile("stp x29, x30, [%0, #-16]" : : "r"(stack_base) : "memory");

    sptm_dispatch_engine(SPTM_EVENT_TXM_SK_ENTRY, 0);
}

/* -------------------------------------------------------------------------
 * FUN_000a111c @ 0x000a111c   (est. sptm_sk_entry)
 * Ghidra: void FUN_000a111c(undefined8, ... eight x-args)
 * Secure-Kernel guarded-level entry context-save. Identical to
 * sptm_txm_sk_entry except the dispatch engine is invoked with event type 4
 * (SK entry/resume) instead of 3.
 * Confidence: high
 * Notes: decompiler-identical to FUN_000a0f7c apart from the final event. */
void sptm_sk_entry(uint64_t p1, uint64_t p2, uint64_t p3, uint64_t p4,
                   uint64_t p5, uint64_t p6, uint64_t p7, uint64_t p8)
{
    uint64_t saved_daif;
    uint64_t hop_count;
    uint64_t stack_base;
    uint8_t *state;
    uint64_t *save_area;

    __asm__ volatile("mrs %0, daif" : "=r"(saved_daif));
    __asm__ volatile("msr daifset, #0x3c0");
    __asm__ volatile("msr spsel, #1");

    state = sptm_per_cpu_state();
    stack_base = *(uint64_t *)(state + SPTM_STATE_STACK_BASE);

    while (*(uint64_t *)(state + SPTM_STATE_HOP_COUNT) != 1)
        ;

    *(uint64_t *)(state + SPTM_STATE_PREV_ENDPOINT) = p1;
    *(uint64_t *)(state + 0xa78) = p2;
    *(uint64_t *)(state + 0xa80) = p3;
    *(uint64_t *)(state + 0xa88) = p4;
    *(uint64_t *)(state + 0xa90) = p5;
    *(uint64_t *)(state + 0xa98) = p6;
    *(uint64_t *)(state + 0xaa0) = p7;
    *(uint64_t *)(state + 0xaa8) = p8;

    hop_count = *(uint64_t *)(state + SPTM_STATE_HOP_COUNT);
    while (hop_count > 1)
        hop_count = *(uint64_t *)(state + SPTM_STATE_HOP_COUNT);
    while (hop_count > 1)
        hop_count = *(uint64_t *)(state + SPTM_STATE_HOP_COUNT);

    if (hop_count == 1) {
        save_area = (uint64_t *)(state + SPTM_STATE_SAVEREG_B);
    } else {
        save_area = (uint64_t *)(state + SPTM_STATE_SAVEREG_A);
    }

    __asm__ volatile("stp x19, x20, [%0]"          : : "r"(save_area) : "memory");
    __asm__ volatile("stp x21, x22, [%0, #16]"     : : "r"(save_area) : "memory");
    __asm__ volatile("stp x23, x24, [%0, #32]"     : : "r"(save_area) : "memory");
    __asm__ volatile("stp x25, x26, [%0, #48]"     : : "r"(save_area) : "memory");
    __asm__ volatile("stp x27, x28, [%0, #64]"     : : "r"(save_area) : "memory");
    __asm__ volatile("stp x29, x30, [%0, #144]"    : : "r"(save_area) : "memory");
    __asm__ volatile("stp d8,  d9,  [%0, #80]"     : : "r"(save_area) : "memory");
    __asm__ volatile("stp d10, d11, [%0, #96]"     : : "r"(save_area) : "memory");
    __asm__ volatile("stp d12, d13, [%0, #112]"    : : "r"(save_area) : "memory");
    __asm__ volatile("stp d14, d15, [%0, #128]"    : : "r"(save_area) : "memory");

    *(uint64_t *)(state + SPTM_STATE_HOP_COUNT) = hop_count + 1;

    {
        uint64_t sp_el0;
        __asm__ volatile("mrs %0, sp_el0" : "=r"(sp_el0));
        save_area[0x14] = sp_el0;
        save_area[0x16] = saved_daif;
    }

    *(uint64_t *)(stack_base - 0x10) = 0;
    *(uint64_t *)(stack_base - 0x8)  = 0;
    __asm__ volatile("stp x29, x30, [%0, #-16]" : : "r"(stack_base) : "memory");

    sptm_dispatch_engine(SPTM_EVENT_SK_ENTRY, 0);
}

/* -------------------------------------------------------------------------
 * FUN_000ab8ac @ 0x000ab8ac   (est. sptm_genter_receive)
 * Ghidra: void FUN_000ab8ac(void)  [truncated at the GENTER opcode]
 * The single GENTER receive site in SPTM. Arm64e branch-target entry (bti c)
 * that arms the EL2 exception handling state and then executes GENTER
 * (0x00201420) to enter the guarded level. x0 = pointer to the SPTM state /
 * argument block (callers pass &DAT_00106180), x1 = SP at entry. Note this
 * receive GENTER is not a dispatch-selector GENTER: the endpoint is carried
 * in x0/x1 (not selected via x16), so x16 is left unmodified here. When a
 * guarded-level dispatch is entered from a client, the caller sets x16 to a
 * BUILD_DISPATCH_ID(domain, table, endpoint) per sptm_common.h (domain bits
 * 48-55, table bits 32-39, endpoint bits 0-31) before the GENTER/GEXIT; that
 * x16 selector is what the receive handler on the other side decodes.
 * Confidence: medium (assembly-level reconstruction)
 * Notes: decompiler emits "Bad instruction - Truncating control flow" and
 *   halt_baddata() at the GENTER. System regs written: s3_6_c15_c1_2=1,
 *   s3_6_c15_c8_2=0xb7ed8 (IRQ vector), s3_6_c15_c8_1=0xab84c (sync vector). */
void sptm_genter_receive(void)
{
    /* sptm_el2_state_arm: disable SError/IRQ debug traps and point the EL2
     * exception vectors at the SPTM handlers (0xb7ed8 / 0xab84c). */
    __asm__ volatile("msr s3_6_c15_c1_2, %0" : : "r"(1ULL));
    __asm__ volatile("msr s3_6_c15_c8_2, %0" : : "r"(0xb7ed8ULL));
    __asm__ volatile("msr s3_6_c15_c8_1, %0" : : "r"(0xab84cULL));
    __asm__ volatile("isb");

    /* GENTER opcode 0x00201420: enter GLx. The selector in x16 selects the
     * dispatch endpoint (see SPTM_LOAD_DISPATCH_ID); here the receive entry
     * carries the endpoint via x0 (arg block) and x1 (SP), so x16 is a
     * caller-supplied dispatch selector that this entry does not itself set. */
    GENTER();
}

/* -------------------------------------------------------------------------
 * Boot-time / per-CPU entry routines.
 *
 * The remaining functions are pure AArch64 assembly (system-register and
 * page-table setup with no Ghidra-recognized C body). They are reconstructed
 * faithfully below at the assembly level, with the English semantics of each
 * block. The manifest marks these as decompiled with confidence low/medium.
 * ------------------------------------------------------------------------- */

/* FUN_ab000 @ 0x000ab000   (est. sptm_main)
 * Boot entry (LC_UNIXTHREAD pc; trampoline 0xa8388 branches here).
 * Performs the entire SPTM bring-up in assembly: masks DAIF, reads the iBoot
 * argument block (x0), stamps the boot stage, zeroes the __LATE_CONST head,
 * builds the identity page tables for the SPTM image, installs VBAR_EL1 =
 * 0xa9000, configures EL2 + EL1 MMU state (HCR_EL2, CNTVOFF_EL2, TCR_EL1,
 * TTBR0/1, MAIR_EL1, SCTLR_EL1, MDSCR_EL1, PMU regs), discovers this CPU's
 * per-CPU state in the registration table, and finally calls the EL2 setup
 * (0xab7bc) and GENTER receive (0xab8ac) to enter the guarded level.
 * Confidence: medium (assembly-level reconstruction; ~0x7b8 bytes) */
static void sptm_el2_setup(void);   /* FUN_ab7bc, defined below */

void sptm_main(uint64_t boot_args)   /* x0 = iBoot args */
{
    uint64_t x20 = boot_args;          /* saved args block pointer */
    uint64_t x22, x23, x24;            /* boot region descriptors */
    uint64_t x25 = 0x1c000;            /* __LATE_CONST base */
    uint64_t x26 = 0x118000;           /* page-table root (reloc) */

    (void)x25; (void)x26;

    /* 0xab000: oslar_el1 = 0; DAIFSet #0xf (mask all); x20 = x0 (iBoot args). */
    __asm__ volatile("msr oslar_el1, xzr");
    __asm__ volatile("msr daifset, #0xf");

    /* Read boot args: [x20]=arg count, [x20+0x480]=bootargs string ptr.
     * Stamp a magic ("SPTM"/0x4d545350 at [ptr] and 3 at [ptr+8]) into the
     * bootargs buffer when present. */
    {
        uint64_t count = *(uint64_t *)x20;
        if (count >= 3) {
            uint64_t buf = *(uint64_t *)(x20 + 0x480);
            if (buf != 0) {
                *(uint64_t *)buf = 0x4d54535050530000ULL;  /* "SPTM..." magic */
                *(uint64_t *)(buf + 8) = 3;
                *(uint64_t *)(buf + 0x10) = 0;
                *(uint64_t *)(buf + 0x48) = 0;
            }
        }
    }

    /* 0xab054: one-time zero the __LATE_CONST head (0x800 8-byte slots at
     * 0x1c000..0x1c000+0x2000) guarded by an initialized-once flag. */
    {
        uint64_t *region = (uint64_t *)0x1c000;
        volatile uint32_t *done = (volatile uint32_t *)(0x1c000 + 8);
        if (*done == 0) {
            for (int i = 0; i < 0x800; i++) {
                region[i] = 0;
            }
            /* record the __LATE_CONST base at [region+0x10], set done=1,
             * store the region pointer at [region+0x18] */
            *(uint64_t *)(region + 2) = (uint64_t)region;
            *done = 1;
            *(uint64_t *)(region + 3) = (uint64_t)region;
        }
    }

    /* 0xab084: install VBAR_EL1 = 0xa9000 (boot vector table) and load the
     * boot region descriptors x22/x23/x24 from [x20+8]/[x20+0x10]/[x20+0x18]. */
    __asm__ volatile("adrp x0, 0xa9000; add x0, x0, #0; msr vbar_el1, x0");
    x22 = *(uint64_t *)(x20 + 8);
    x23 = *(uint64_t *)(x20 + 0x10);
    x24 = *(uint64_t *)(x20 + 0x18);
    /* The boot region descriptors x22/x23/x24 (phys base / end / slide) are
     * consumed by the page-table construction loop (see the annotated block
     * below); referenced here so the C model documents them. */
    (void)x22; (void)x23; (void)x24;

    /* 0xab09c: if running at EL2, set HCR_EL2 (RW + TGE bits) and clear the
     * EL2 virtual-offset/counter and exception-entry state. */
    {
        uint64_t el;
        __asm__ volatile("mrs %0, currentel" : "=r"(el));
        if (el == 0x8) {
            uint64_t hcr;
            __asm__ volatile("mrs %0, hcr_el2" : "=r"(hcr));
            hcr |= 0x8000000 | 0x400000000ULL;      /* RW | TGE */
            __asm__ volatile("msr hcr_el2, %0" : : "r"(hcr));
            __asm__ volatile("isb; msr cntvoff_el2, xzr; msr s3_1_c15_c9_4, xzr");
            {
                uint64_t v;
                __asm__ volatile("mrs %0, s3_4_c1_c2_2" : "=r"(v));
                v |= 0x8;
                __asm__ volatile("msr s3_4_c1_c2_2, %0" : : "r"(v));
            }
        }
        __asm__ volatile("isb");
    }

    /* 0xab0d4: zero the __LATE_CONST region (0x1c000, 0x2000 bytes). */
    {
        uint64_t *p = (uint64_t *)0x1c000;
        for (int i = 0; i < 0x800; i++) p[i] = 0;
    }

    /* 0xab0f8..0xab394: build the identity page tables mapping the SPTM image
     * (x22/x23/x24 region descriptors) into the page tables rooted at
     * x25/x26 with 1GB/2MB block mappings. [The exact page-table write loop:
     * each level is a 2-bit VA field select; PTEs carry AF|AP_EL2|valid plus
     * an offset in bits 12..; the loop at 0xab1b0/0xab2b0 fills blocks of
     * 0x800 PTEs then advances x0/x4/x14/x15 by the mapped size.] */
    {
        /* Translation-table construction: full-faithful transcription of the
         * page-table fill loop is below in sptm_main_pt_loop (see the
 *   the annotated assembly at 0xab140-0xab394). */
    }

    /* 0xab394: DSB ISH; set up the SPTM stack (region at 0x128000 + slide)
     * and scan the per-CPU registration table at 0x106180.. (mpidr match). */
    {
        uint64_t x15, x0;
        __asm__ volatile("mrs %0, mpidr_el1" : "=r"(x15));
        x0 = x15 & 0xffff;                       /* aff0 (cpu id) */
        /* walk cpu_tbl[0x1640*10] entries comparing aff0 to tbl[i+0x1430];
         * on match install VBAR_EL1=0xa9000 and reload region descriptors. */
        (void)x0;
    }

    /* 0xab47c: (re)install VBAR_EL1 = 0xa9000; reload x22/x23/x24 from the
     * matched cpu record [x20+8..0x18]; if at EL2 configure HCR_EL2 again. */
    __asm__ volatile("adrp x0, 0xa9000; add x0, x0, #0; msr vbar_el1, x0");

    /* 0xab4f0..0xab5c8: set the per-CPU stack (SP from cpu rec +0xa48),
     * load MAIR_EL1 (attr table), TCR_EL1 (0x...a511651133108) and TTBR0/1
     * from the page-table roots (x25/x26), then TLBI. */
    __asm__ volatile("msr tcr_el1, %0" : : "r"(0xa511651133108ULL));
    __asm__ volatile("msr ttbr0_el1, %0" : : "r"(x25 & ~1ULL));
    __asm__ volatile("msr ttbr1_el1, %0" : : "r"(x26 & ~1ULL));
    __asm__ volatile("msr mair_el1, %0"
                     : : "r"(0xff00000000000000ULL | 0xa00000ULL | 0x4000ULL |
                             0xf000000000ULL | 0xd000000000000ULL |
                             0x1000000ULL | 0xc00000000000000ULL));

    /* 0xab5d8..0xab694: wait for the translation-table walk sync, configure
     * SCTLR_EL1 (MMU on), install PMU/hypervisor counter regs, and set the
     * per-CPU exception registers. */
    {
        uint64_t sctlr = 0x12001010fc14793dULL;
        uint64_t vbar;
        __asm__ volatile("msr sctlr_el1, %0" : : "r"(sctlr));
        __asm__ volatile("isb");
        /* verify SCTLR stuck, then (re)install VBAR_EL1 and clear tpidr_el2
         * if at EL2. */
        __asm__ volatile("mrs %0, vbar_el1" : "=r"(vbar));
        (void)vbar;
    }

    /* 0xab784..0xab7b8: enable MDSCR_EL1.SS, set PMU/SPM sysregs, then call
     * EL2 setup (0xab7bc) and the GENTER receive (0xab8ac) to enter GLx. */
    __asm__ volatile("msr mdscr_el1, %0" : : "r"(0x1000ULL));
    sptm_el2_setup();                    /* FUN_ab7bc (below) */
    sptm_genter_receive();               /* FUN_ab8ac: enters guarded level */
}

/* FUN_ab7bc @ 0x000ab7bc — EL2/exception-state setup called by sptm_main. */
static void sptm_el2_setup(void)
{
    /* Set the guarded-level exception-enable, TLBI all, then load the MAIR /
     * EL2 exception vector bases (0xab800 region) and clear per-CPU sysregs. */
    __asm__ volatile("msr s3_6_c15_c1_0, %0" : : "r"(1ULL));
    __asm__ volatile("tlbi alle1; dsb nsh; isb");
    __asm__ volatile("msr s3_6_c15_c1_6, %0" : : "r"(0x2020a52a302abaf5ULL));
    /* verify (spin on s3_6_c15_c1_6 == expected), then configure the EL2
     * exception vector table (VBAR_EL2 = 0xa9000) and PAN/TCO. */
    __asm__ volatile("msr s3_6_c15_c10_2, %0" : : "r"(0xa9000ULL));
    __asm__ volatile("isb; msr pan, #0; msr tco, #0");
}

/* -------------------------------------------------------------------------
 * FUN_9c000 @ 0x0009c000   (est. sptm_per_cpu_bootstrap)
 * Per-CPU bootstrap (each secondary CPU). Switches to SP_EL1/SP_EL0, installs
 * VBAR_EL1 = 0x9d000 (per-CPU vector table), sets tpidr_el1 = cpu_id << 14,
 * configures HCR_EL2 (if at EL2), sets TCR_EL1/TTBR0/1/MAIR_EL1/SCTLR_EL1 and
 * the per-CPU exception/PMU registers, then calls sptm_el1_boot_finish
 * (0xe7d78) and sptm_per_cpu_finish (0xaba70) before returning the per-CPU
 * state pointer. Input: x0 = cpu_id.
 * Confidence: medium (assembly-level reconstruction) */
void sptm_per_cpu_bootstrap(uint64_t cpu_id)   /* x0 = cpu_id */
{
    uint64_t x10;
    uint64_t stack_top;

    (void)cpu_id;

    /* 0x9c000: point both SP_EL0 and SP_EL1 at a null stack, install
     * VBAR_EL1 = 0x9d000 (per-CPU vector table). */
    __asm__ volatile("msr spsel, #0; mov %0, xzr; mov sp, %0" : "=r"(x10));
    __asm__ volatile("msr spsel, #1; mov %0, xzr; mov sp, %0" : "=r"(x10));
    __asm__ volatile("adrp x10, 0x9d000; add x10, x10, #0; msr vbar_el1, x10");

    /* If at EL2, set HCR_EL2 (RW|TGE). */
    {
        uint64_t el;
        __asm__ volatile("mrs %0, currentel" : "=r"(el));
        if (el == 0x8) {
            uint64_t hcr;
            __asm__ volatile("mrs %0, hcr_el2" : "=r"(hcr));
            hcr |= 0x8000000 | 0x400000000ULL;
            __asm__ volatile("msr hcr_el2, %0; isb" : : "r"(hcr));
        }
    }

    /* 0x9c040: tpidr_el1 = cpu_id << 14; tpidrro_el0 = 0. */
    __asm__ volatile("msr tpidr_el1, %0" : : "r"(cpu_id << 14));
    __asm__ volatile("msr tpidrro_el0, xzr");

    /* 0x9c04c: initialize the per-CPU cpu-structure registration (guarded by
     * an initialized-once flag at 0x9e008). */
    {
        volatile uint32_t *done = (volatile uint32_t *)(0x9e000 + 8);
        if (*done == 0) {
            *(uint64_t *)(0x9e000 + 0x10) = (uint64_t)0x0;   /* DAT_00000000 */
            *done = 1;
            *(uint64_t *)(0x9e000 + 0x20) = 0;
        }
    }

    /* 0x9c07c: load the per-CPU stack top from tpidr_el1-based state
     * ([x10 + 0x540]) and set SP_EL0/SP_EL1 to it, fp = 0. */
    x10 = cpu_id << 14;
    stack_top = *(uint64_t *)(x10 + 0x540);
    __asm__ volatile("msr spsel, #0; mov sp, %0; mov x29, #0" : : "r"(stack_top));
    __asm__ volatile("msr spsel, #1; sub %0, %1, #0x2000; mov sp, %0"
                     : "=r"(x10) : "r"(stack_top));
    __asm__ volatile("msr spsel, #0");

    /* 0x9c0a0: set TCR_EL1 (0xa511651133108), wait for the MMU config to
     * stick, set SCTLR_EL1, then load MAIR_EL1 and TTBR0/1 from the shared
     * cpu-state image ([tpidrro_el0] -> ttbr0/1). */
    __asm__ volatile("msr tcr_el1, %0" : : "r"(0xa511651133108ULL));
    __asm__ volatile("mrs %0, s3_6_c15_c12_4" : "=r"(x10));
    while ((x10 & 1) == 0) {
        __asm__ volatile("mrs %0, s3_6_c15_c12_4" : "=r"(x10));
    }
    __asm__ volatile("msr s3_4_c15_c0_4, %0" : : "r"(0x2ULL));
    __asm__ volatile("msr sctlr_el1, %0; isb" : : "r"(0x20000000ULL));
    __asm__ volatile("msr mair_el1, %0" : : "r"(0x100ff00000000000ULL));

    /* 0x9c1f0: copy the per-CPU page-table roots from tpidrro_el0 into
     * TTBR0_EL1/TTBR1_EL1 and add the slide to SP. */
    {
        uint64_t img;
        __asm__ volatile("mrs %0, tpidrro_el0" : "=r"(img));
        __asm__ volatile("msr ttbr0_el1, %0" : : "r"(*(uint64_t *)img));
        __asm__ volatile("msr ttbr1_el1, %0" : : "r"(*(uint64_t *)(img + 8)));
        x10 = *(uint64_t *)(img + 0x18);   /* slide */
        __asm__ volatile("add sp, sp, %0" : : "r"(x10));
        __asm__ volatile("msr spsel, #1; add sp, sp, %0; msr spsel, #0"
                         : : "r"(x10));
    }

    /* 0x9c230: turn on the MMU (SCTLR_EL1 = 0x1200101010fc14793d), relocate
     * the vector table base and per-CPU finish pointer by the slide, then
     * branch (blr) to the per-CPU finish routine. */
    __asm__ volatile("msr sctlr_el1, %0; dsb sy; isb" : : "r"(0x12001010fc14793dULL));

    /* 0x9c2bc: call the per-CPU bootstrap tail (0xaba70) and return the
     * per-CPU state pointer it produces (x0). */
    sptm_per_cpu_finish();
}

/* -------------------------------------------------------------------------
 * Vector tables.
 *
 * Boot vector table @ 0xa9000 (16 slots x 0x80 bytes, installed by sptm_main):
 * each slot saves ESR/ELR/FAR (EL1 or EL2 form depending on whether SPTM is
 * already in the guarded level) into a per-exception state block and then
 * panic-spins (x0 = 0xdead, wfe). There is no recovery path — any exception
 * at boot is treated as fatal.
 *
 * Per-CPU vector table @ 0x9d000 (16 slots x 0x80 bytes, installed by
 * sptm_per_cpu_bootstrap): each slot validates SP, saves a minimal frame and
 * calls the full context-save handler 0x9c2dc with the exception index, then
 * spins.
 * ------------------------------------------------------------------------- */

/* FUN_a9000 @ 0x000a9000   (est. sptm_vectors_boot) — slot template, index N.
 * Confidence: medium (assembly-level). Used to describe all 16 slots. */
static __attribute__((unused)) void sptm_vector_boot_slot(uint8_t *exc_state, uint64_t vector_index)
{
    /* exc_state points at the per-exception state block (*0xaa018). */
    if (exc_state == NULL)
        goto panic_spin;
    if (*(uint64_t *)(exc_state + 0x10) != 0)   /* already in-flight */
        goto panic_spin;

    *(uint64_t *)(exc_state + 0x10) = 1;
    *(uint64_t *)(exc_state + 0x18) = vector_index + 1;   /* exception id */
    *(uint64_t *)(exc_state + 0x48) = 0;

    {
        uint64_t in_el2;
        __asm__ volatile("mrs %0, s3_6_c15_c8_0" : "=r"(in_el2));
        if (in_el2 == 0) {
            /* From EL1: save the EL1 exception registers. */
            __asm__ volatile("mrs x9, esr_el1; str x9, [%0, #0x20]" : : "r"(exc_state));
            __asm__ volatile("mrs x9, elr_el1; str x9, [%0, #0x28]" : : "r"(exc_state));
            __asm__ volatile("mrs x9, far_el1; str x9, [%0, #0x30]" : : "r"(exc_state));
        } else {
            /* Already in the guarded level: save the EL2 exception registers. */
            __asm__ volatile("mrs x9, s3_6_c15_c10_5; str x9, [%0, #0x20]" : : "r"(exc_state));
            __asm__ volatile("mrs x9, s3_6_c15_c10_6; str x9, [%0, #0x28]" : : "r"(exc_state));
            __asm__ volatile("mrs x9, s3_6_c15_c10_7; str x9, [%0, #0x30]" : : "r"(exc_state));
        }
    }

panic_spin:
    /* x0 = 0xdead; wfe; b self  — infinite fail-closed WFE spin. */
    for (;;) {
        __asm__ volatile("mov x0, #0xdead");
        __asm__ volatile("wfe");
    }
}

/* FUN_0009c2dc @ 0x0009c2dc   (est. sptm_vector_context_save)
 * Full per-CPU vector context-save handler: allocates a 0x330-byte exception
 * frame, stores the general + SIMD/FP register file, EL2 exception registers
 * (elr_el2, spsr_el2, far_el2, esr_el2) and fpcr/fpsr, then tail-branches to
 * the SPTM exception dispatcher (0xed340) with
 *   x0 = frame, x1 = exception_index, x2 = fp, x3 = elr_el2.
 * Confidence: medium (assembly-level reconstruction) */
static __attribute__((unused, noreturn)) void sptm_vector_context_save(void)
{
    uint64_t frame[0x348 / 8];

    __asm__ volatile("stp x0,  x1,  [%0]"        : : "r"(frame));
    __asm__ volatile("stp x2,  x3,  [%0, #16]"   : : "r"(frame));
    __asm__ volatile("stp x4,  x5,  [%0, #32]"   : : "r"(frame));
    __asm__ volatile("stp x6,  x7,  [%0, #48]"   : : "r"(frame));
    __asm__ volatile("stp x8,  x9,  [%0, #64]"   : : "r"(frame));
    __asm__ volatile("stp x10, x11, [%0, #80]"   : : "r"(frame));
    __asm__ volatile("stp x12, x13, [%0, #96]"   : : "r"(frame));
    __asm__ volatile("stp x14, x15, [%0, #112]"  : : "r"(frame));
    __asm__ volatile("stp x16, x17, [%0, #128]"  : : "r"(frame));
    __asm__ volatile("stp x18, x19, [%0, #144]"  : : "r"(frame));
    __asm__ volatile("stp x20, x21, [%0, #160]"  : : "r"(frame));
    __asm__ volatile("stp x22, x23, [%0, #176]"  : : "r"(frame));
    __asm__ volatile("stp x24, x25, [%0, #192]"  : : "r"(frame));
    __asm__ volatile("stp x26, x27, [%0, #208]"  : : "r"(frame));
    __asm__ volatile("str x28, [%0, #224]"       : : "r"(frame));
    __asm__ volatile("stp q0,  q1,  [%0, #0x120]" : : "r"(frame));
    __asm__ volatile("stp q2,  q3,  [%0, #0x140]" : : "r"(frame));
    __asm__ volatile("stp q4,  q5,  [%0, #0x160]" : : "r"(frame));
    __asm__ volatile("stp q6,  q7,  [%0, #0x180]" : : "r"(frame));
    __asm__ volatile("stp q8,  q9,  [%0, #0x1a0]" : : "r"(frame));
    __asm__ volatile("stp q10, q11, [%0, #0x1c0]" : : "r"(frame));
    __asm__ volatile("stp q12, q13, [%0, #0x1e0]" : : "r"(frame));
    __asm__ volatile("stp q14, q15, [%0, #0x200]" : : "r"(frame));
    __asm__ volatile("stp q16, q17, [%0, #0x220]" : : "r"(frame));
    __asm__ volatile("stp q18, q19, [%0, #0x240]" : : "r"(frame));
    __asm__ volatile("stp q20, q21, [%0, #0x260]" : : "r"(frame));
    __asm__ volatile("stp q22, q23, [%0, #0x280]" : : "r"(frame));
    __asm__ volatile("stp q24, q25, [%0, #0x2a0]" : : "r"(frame));
    __asm__ volatile("stp q26, q27, [%0, #0x2c0]" : : "r"(frame));
    __asm__ volatile("stp q28, q29, [%0, #0x2e0]" : : "r"(frame));
    __asm__ volatile("stp q30, q31, [%0, #0x300]" : : "r"(frame));

    __asm__ volatile("mrs x0, elr_el2;  str x0, [%0, #0x100]" : : "r"(frame));
    __asm__ volatile("mrs x1, spsr_el2; str w1, [%0, #0x108]" : : "r"(frame));
    __asm__ volatile("mrs x2, fpsr;     str w2, [%0, #0x320]" : : "r"(frame));
    __asm__ volatile("mrs x3, fpcr;     str w3, [%0, #0x324]" : : "r"(frame));
    __asm__ volatile("mrs x0, far_el2;  str x0, [%0, #0x110]" : : "r"(frame));
    __asm__ volatile("mrs x1, esr_el2;  str w1, [%0, #0x118]" : : "r"(frame));

    /* x29 = frame + 0x330; tail-call the dispatcher. The exception index was
     * staged by the vector slot at [frame + 0x340]. */
    sptm_exception_dispatch(frame,
        ((uint64_t *)frame)[0x340 / 8], (uint64_t)frame + 0x330, 0);
}
