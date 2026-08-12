/* Recreated from cl4_kernel.raw (cL4 Secure Kernel, arm64e, image base 0) — the
 * cL4 microkernel (GL1). Ground truth: Ghidra FUN_ names + addresses in program
 * cl4_kernel.raw. All names are estimates unless string/header matched.
 *
 * This master covers the syscall / exception-entry machinery region
 * 0x300000 - 0x380000. The range was decompiled in 32 contiguous per-slice
 * translation units (sk_region_syscalls_part01.c .. part32.c); each slice
 * compiles independently with clang -fsyntax-only (0 errors). This file
 * includes them for a single-unit view.
 *
 * SeL4/cL4 vocabulary is used: TCB, cap, CNode, IPC, notification, endpoint,
 * vspace, sched, syscall trap, etc. Confidence medium unless string-matched.
 */
#include "sk_region_syscalls_part01.c"
#include "sk_region_syscalls_part02.c"
#include "sk_region_syscalls_part03.c"
#include "sk_region_syscalls_part04.c"
#include "sk_region_syscalls_part05.c"
#include "sk_region_syscalls_part06.c"
#include "sk_region_syscalls_part07.c"
#include "sk_region_syscalls_part08.c"
#include "sk_region_syscalls_part09.c"
#include "sk_region_syscalls_part10.c"
#include "sk_region_syscalls_part11.c"
#include "sk_region_syscalls_part12.c"
#include "sk_region_syscalls_part13.c"
#include "sk_region_syscalls_part14.c"
#include "sk_region_syscalls_part15.c"
#include "sk_region_syscalls_part16.c"
#include "sk_region_syscalls_part17.c"
#include "sk_region_syscalls_part18.c"
#include "sk_region_syscalls_part19.c"
#include "sk_region_syscalls_part20.c"
#include "sk_region_syscalls_part21.c"
#include "sk_region_syscalls_part22.c"
#include "sk_region_syscalls_part23.c"
#include "sk_region_syscalls_part24.c"
#include "sk_region_syscalls_part25.c"
#include "sk_region_syscalls_part26.c"
#include "sk_region_syscalls_part27.c"
#include "sk_region_syscalls_part28.c"
#include "sk_region_syscalls_part29.c"
#include "sk_region_syscalls_part30.c"
#include "sk_region_syscalls_part31.c"
#include "sk_region_syscalls_part32.c"
