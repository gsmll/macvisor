/* Recreated from kernelcache.arm64.kc (xnu-12377.121.10 RELEASE_ARM64_T8142, image base fffffe0007004000). Ground truth: Ghidra FUN_ names + addresses; all names are estimates. */

/*
 * start.s — kernel entry annotated reconstruction (est.).
 *
 * Owned by the boot-audit tree. This file is an ANNOTATED disassembly of the
 * kernel entry FUN_fffffe000c110000 (est. kernel_entry — the Mach-O program
 * entry point, body 0xfffffe000c110000 - 0xfffffe000c11400f). The task is to document the early
 * boot sequence and the transfer into arm_cpu_init / kernel_bootstrap; per
 * the BOOT-AUDIT rule this is assembly-level annotation, not a decompile into
 * C (raw hand-written entry assembly is not recreated beyond these notes).
 *
 * The annotated C bodies for the functions reached from here live in
 * osfmk/kern/startup.c: arm_cpu_init (FUN_fffffe000b95af80), kernel_bootstrap
 * (FUN_fffffe000b8243f0) and kernel_bootstrap_thread (FUN_fffffe000b8239e0).
 *
 * Registers at entry (AArch64 calling convention from the bootloader / iBoot):
 *   x0 = boot-mode / cpu identifier (see the dispatch below)
 *   x1 = secondary boot arg
 *   x2 = secondary boot arg
 *   x3 = secondary boot arg (used on the secondary-cpu path)
 */

/* ================================================================== *
 * FUN_fffffe000c110000   kernel entry (est. _start / _start_secondary)
 * Ghidra: undefined entry(void)
 *
 * Early boot sequence (each instruction annotated):
 *
 *   fffffe000c110000  bti c                     ; branch-target identification
 *   fffffe000c110004  mov x8, #0x4
 *   fffffe000c110008  cmp x0, x8                ; x0 == 4?
 *   fffffe000c11000c  b.ne 0xfffffe000c110024   ; no  -> normal path
 *   ; --- x0 == 4: early-panic path (rare "already entered" abort) ---
 *   fffffe000c110010  adrp x8, ...              ; compute byte global
 *   fffffe000c110014  strb w2, [x8, #0xf90]     ; store x2 (byte) into global
 *   fffffe000c110018  mov x0, x1
 *   fffffe000c11001c  b 0xfffffe000c114000      ; -> panic stub (below)
 *
 *   ; --- normal path ---
 *   fffffe000c110024  msr tpidr_el0, xzr        ; clear TPIDR_EL0
 *   fffffe000c110028  msr tpidr_el1, xzr        ; clear TPIDR_EL1 (per-cpu base)
 *   fffffe000c11002c  msr tpidrro_el0, xzr      ; clear TPIDRRO_EL0
 *   fffffe000c110030  mov x20, #0x0
 *   fffffe000c110034  cmp x0, x20               ; x0 == 0 (primary / boot CPU)?
 *   fffffe000c110038  b.eq 0xfffffe000c110040   ; yes -> primary-CPU setup
 *   fffffe000c11003c  b 0xfffffe000c110098      ; no  -> secondary-cpu path
 *
 *   ; --- primary (boot) CPU setup ---
 *   fffffe000c110040  msr PState.SP, #0x1       ; select EL1 stack pointer
 *   fffffe000c110044  adrp x10, ...
 *   fffffe000c110048  add x10, x10, #0x0        ; x10 = boot EL1 stack
 *   fffffe000c11004c  mov sp, x10               ; set SP_EL1
 *   fffffe000c110050  msr PState.SP, #0x0       ; select EL0 stack pointer
 *   fffffe000c110054  adrp x10, ...
 *   fffffe000c110058  add x10, x10, #0x0        ; x10 = boot EL0 stack
 *   fffffe000c11005c  mov sp, x10               ; set SP_EL0
 *   fffffe000c110060  mov x26, x1               ; save x1
 *   fffffe000c110064  mov x27, x2               ; save x2
 *   fffffe000c110068  bl 0xfffffe000c114488     ; FUN_fffffe000c114488: parse Mach-O
 *                                                ;   header / load commands, record
 *                                                ;   __LINKEDIT bounds, MACH_HEADER
 *   fffffe000c11006c  mov x0, x26
 *   fffffe000c110070  bl 0xfffffe000c114a34     ; FUN_fffffe000c114a34: run early
 *                                                ;   init funcs (PTR_FUN_fffffe000c7c3dc0),
 *                                                ;   then IC_IALLUIS/DSB/ISB (apply
 *                                                ;   early i-cache invalidation)
 *   fffffe000c110074  adrp x9, ...              ; compute exception-vector base
 *   fffffe000c110078  add x9, x9, #0x0
 *   fffffe000c11007c  msr vbar_el1, x9          ; set VBAR_EL1 (exception vectors)
 *   fffffe000c110080  isb                        ; synchronize
 *   fffffe000c110084  mov x16, #0xf             ; (entry continuation bookkeeping)
 *   ;   ... (a small inline block then branches into the secondary path;
 *   ;        Ghidra's control flow renders the primary path as falling into
 *   ;        FUN_fffffe000c110098 below)
 *
 *   ; --- common / secondary-cpu path: find this cpu in the cpu table ---
 *   fffffe000c110098  mov x20, x3               ; save x3
 *   fffffe000c11009c  msr tpidr_el0, xzr
 *   fffffe000c1100a0  mrs x15, mpidr_el1
 *   fffffe000c1100a4  and x0, x15, #0xffff      ; x0 = cpu id = mpidr & 0xffff
 *   fffffe000c1100a8  adrp x1, ...
 *   fffffe000c1100ac  add x1, x1, #0xee8        ; x1 = cpu table base
 *   fffffe000c1100b0  movk x19, #0x0, LSL #48
 *   fffffe000c1100b4  movk x19, #0x0, LSL #32
 *   fffffe000c1100b8  movk x19, #0x0, LSL #16
 *   fffffe000c1100bc  movk x19, #0x10           ; x19 = stride 0x10
 *   fffffe000c1100c0  mov x4, #0xa
 *   fffffe000c1100c4  mul x3, x19, x4           ; x3 = 0xa0 = 10 entries * 0x10
 *   fffffe000c1100c8  add x3, x1, x3            ; x3 = end of table
 *   fffffe000c1100cc  ldr x21, [x1, #0x8]       ; x21 = table[i].cpu (ptr at +8)
 *   fffffe000c1100d0  cbz x21, 0xfffffe000c1100d0 ; spin while NULL
 *   fffffe000c1100d4  ldr w2, [x21, #0x1d0]     ; w2 = cpu->mpidr
 *   fffffe000c1100d8  cmp x0, x2
 *   fffffe000c1100dc  b.eq 0xfffffe000c1100f0   ; match -> found
 *   fffffe000c1100e0  add x1, x1, x19           ; next entry
 *   fffffe000c1100e4  cmp x1, x3
 *   fffffe000c1100e8  b.eq 0xfffffe000c110158   ; exhausted -> deadb002 spin
 *   fffffe000c1100ec  b 0xfffffe000c1100cc
 *
 *   ; --- found this cpu: set up stacks and call its boot function ---
 *   fffffe000c1100f0  msr PState.SP, #0x1       ; select EL1 SP
 *   fffffe000c1100f4  ldr x10, [x21, #0x28]
 *   fffffe000c1100f8  mov sp, x10               ; SP_EL1 = cpu->el1_sp
 *   fffffe000c1100fc  msr PState.SP, #0x0
 *   fffffe000c110100  ldr x10, [x21, #0x18]
 *   fffffe000c110104  mov sp, x10               ; SP_EL0 = cpu->el0_sp
 *   fffffe000c110108  mov x0, x21               ; arg0 = cpu struct
 *   fffffe000c11010c  mov x1, x20               ; arg1 = saved x3 (boot arg)
 *   fffffe000c110110  ldr x2, [x21, #0xb8]      ; x2 = cpu->boot_func (offset 0xb8)
 *   fffffe000c110114  cbz x2, 0xfffffe000c110144   ; NULL -> deadb001 spin
 *   fffffe000c110118  adrp x3, ...
 *   fffffe000c11011c  add x3, x3, #0xf80        ; compare to FUN_fffffe000c73e??f80
 *   fffffe000c110120  cmp x2, x3
 *   fffffe000c110124  b.eq 0xfffffe000c11013c   ; == arm_cpu_init -> jump
 *   fffffe000c110128  adrp x3, ...
 *   fffffe000c11012c  add x3, x3, #0x520        ; compare to FUN_fffffe000c73e??520
 *   fffffe000c110130  cmp x2, x3
 *   fffffe000c110134  b.eq 0xfffffe000c110140   ; == b95b520 -> jump
 *   fffffe000c110138  b 0xfffffe000c110144      ; unknown boot func -> deadb001
 *   fffffe000c11013c  b 0xfffffe000b95af80      ; -> arm_cpu_init (kernel_bootstrap)
 *   fffffe000c110140  b 0xfffffe000b95b520      ; -> FUN_fffffe000b95b520 (secondary)
 *   fffffe000c110144  movk x0, #0xdead, LSL #16 ; x0 = 0xdeadb001
 *   fffffe000c110148  movk x0, #0x0, LSL #32
 *   fffffe000c11014c  movk x0, #0x0, LSL #48
 *   fffffe000c110150  movk x0, #0xb001
 *   fffffe000c110154  b 0xfffffe000c110154      ; spin forever (deadb001)
 *   fffffe000c110158  movk x0, #0xdead, LSL #16 ; x0 = 0xdeadb002
 *   fffffe000c11015c  movk x0, #0x0, LSL #32
 *   fffffe000c110160  movk x0, #0x0, LSL #16
 *   fffffe000c110164  movk x0, #0xb002
 *   fffffe000c110168  b 0xfffffe000c110168      ; spin forever (deadb002)
 *
 *   ; --- panic stub (reached from the x0==4 path) ---
 *   fffffe000c114000  pacibsp                    ; sign the LR (pointer auth)
 *   fffffe000c114004  stp x29, x30, [sp, #-0x10]!
 *   fffffe000c114008  mov x29, sp
 *   fffffe000c11400c  bl 0xfffffe000c0e11ec      ; FUN_fffffe000c0e11ec: kernel panic
 *
 * Confidence: high (for the dispatch/table-walk structure; the primary-CPU
 *   tail after fffffe000c110084 is partly inferred).
 *
 * Notes:
 *   - The cpu table (base @ +0xee8, stride 0x10, 10 entries) holds per-entry
 *     { +8: cpu struct ptr, ... } and the per-cpu boot function pointer is
 *     loaded from cpu->+0xb8 — the same +0xb8 slot that arm_cpu_init writes
 *     (FUN_fffffe000b95af80 sets *(cpu_base+0x1b8)+0xb8 = FUN_fffffe000b95b520).
 *   - arm_cpu_init (FUN_fffffe000b95af80) is the boot-CPU path and calls
 *     kernel_bootstrap (FUN_fffffe000b8243f0) with 0; kernel_bootstrap runs
 *     kernel_bootstrap_thread (FUN_fffffe000b8239e0), which runs hv_support_init.
 *   - Primary-CPU setup calls FUN_fffffe000c114488 (Mach-O header/load-command
 *     scan: records MACH_HEADER @ DAT_fffffe0007e9d280 and __LINKEDIT bounds;
 *     warning "Removing unreachable block") and FUN_fffffe000c114a34 (runs the
 *     PTR_FUN_fffffe000c7c3dc0 init-func table then IC_IALLUIS/DSB/ISB).
 *   - The deadb001 / deadb002 constants are the classic XNU "CPU not found" /
 *     "unknown boot function" halt codes.
 *   - Ghidra: disassemble_function shows the primary path falling into the
 *     common path at 0xfffffe000c110098; the 4 raw instructions between
 *     0xfffffe000c110084 and 0xfffffe000c110098 (a small inline block ending
 *     in a branch) are not individually rendered by the listing. This file
 *     documents the verified structure and marks the uncertain tail
 *     [INFERENCE]. */
