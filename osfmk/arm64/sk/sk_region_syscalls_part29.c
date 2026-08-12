/* Recreated from cl4_kernel.raw (cL4 Secure Kernel, arm64e, image base 0) —
 * the cL4 microkernel (GL1), "cL4 (679.100.61)". Ground truth: Ghidra FUN_
 * names + addresses in program cl4_kernel.raw.
 * Slice 29: 0x359c90-0x35a8bc syscall/exception-entry machinery region.
 * All names are estimates unless string/header-matched. */

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "sk_internal.h"

/* ------------------------------------------------------------------ *
 * Shared 16-byte (X0:X1) register-pair type used by this region's
 * argument-marshaling helpers. cl4_result_t is the canonical pair for
 * results; this is a plain data pair for the address/limits helpers.
 * ------------------------------------------------------------------ */
typedef struct sk_pair {
    uint64_t lo;
    uint64_t hi;
} sk_pair_t;

/* ------------------------------------------------------------------ *
 * Out-of-range cL4 helper declarations (declared extern with a one-line
 * note; their bodies are reconstructed by the range worker that owns them).
 * ------------------------------------------------------------------ */
extern void sk_dispatch_0036986c(void);     /* FUN_0036986c: post-build dispatch/notify */
extern void sk_invoke_002a9ba8(uint64_t a, uint64_t b); /* FUN_002a9ba8: 2-arg capability invoke */
extern void sk_panic_001afa84(void) __attribute__((noreturn)); /* FUN_001afa84: noreturn abort/panic */
extern void sk_register_00002534(void *a, void *b); /* FUN_00002534: 2-ptr table/registration */
extern void sk_register_00027614(void *fn, void *arg); /* FUN_00027614: (fn,arg) registration */
extern void sk_helper_001a983c(void);       /* FUN_001a983c: no-arg helper */
extern void sk_helper_001d9840(uint64_t a); /* FUN_001d9840: 1-arg helper */
extern void sk_count_log_001a89a8(const char *what, uint64_t n, uint64_t m); /* FUN_001a89a8: counter/assert log */
extern void sk_helper_0031ba70(void);       /* FUN_0031ba70: no-arg helper (cap refcount region) */
extern void sk_helper_00310a14(void);       /* FUN_00310a14: no-arg helper */
extern void sk_helper_0008f6f4(void);       /* FUN_0008f6f4: no-arg helper */

/* Referenced data (out of slice). */
extern unsigned char sk_tbl_004e7d70[];     /* DAT_004e7d70: table base */
extern unsigned char sk_tbl_004e8098[];     /* DAT_004e8098: table entry */
extern unsigned char sk_tbl_004f1918[];     /* DAT_004f1918 */
extern unsigned char sk_tbl_004f1930[];     /* DAT_004f1930 */
extern unsigned char sk_str_00657588[];     /* DAT_00657588: string/symbol */
extern unsigned char sk_str_006575a0[];     /* DAT_006575a0: string/symbol */
extern unsigned char sk_str_00656240[];     /* FUN_00656240: function pointer target */

/*--------------------------------------------------------------------*/
/* FUN_00359c90 @ 0x00359c90   (est. sk_syscall_9c90_stub)
 * Ghidra: void FUN_00359c90(void)
 * Empty exception-entry stub: bare return, no state touched.
 * Confidence: medium
 * Notes: decompiles to empty body. */
void sk_syscall_9c90_stub(void)
{
    /* no-op */
}

/*--------------------------------------------------------------------*/
/* FUN_00359ca4 @ 0x00359ca4   (est. sk_syscall_9ca4_stub)
 * Ghidra: void FUN_00359ca4(void)
 * Empty exception-entry stub.
 * Confidence: medium */
void sk_syscall_9ca4_stub(void)
{
    /* no-op */
}

/*--------------------------------------------------------------------*/
/* FUN_00359cb0 @ 0x00359cb0   (est. sk_syscall_9cb0_store_arg)
 * Ghidra: void FUN_00359cb0(undefined8 param_1)
 * Stores the incoming argument word below the current stack frame
 * (in_x10-0x100) and advances a saved frame pointer (+0x10). Likely a
 * syscall-argument spilling prologue fragment.
 * Confidence: medium
 * Notes: unaff_x29/in_x10 are caller-saved frame pointers (decompiler
 *   lost the real locals). */
void sk_syscall_9cb0_store_arg(uint64_t arg)
{
    /* *(undefined8 *)(in_x10 + -0x100) = arg; */
    /* *(long *)(unaff_x29 + -0xa0) = *(long *)(unaff_x29 + -0x90) + 0x10; */
}

/*--------------------------------------------------------------------*/
/* FUN_00359cc4 @ 0x00359cc4   (est. sk_syscall_9cc4_stub)
 * Ghidra: void FUN_00359cc4(void)
 * Empty exception-entry stub.
 * Confidence: medium */
void sk_syscall_9cc4_stub(void)
{
    /* no-op */
}

/*--------------------------------------------------------------------*/
/* FUN_00359cd8 @ 0x00359cd8   (est. sk_syscall_9cd8_stub)
 * Ghidra: void FUN_00359cd8(void)
 * Empty exception-entry stub.
 * Confidence: medium */
void sk_syscall_9cd8_stub(void)
{
    /* no-op */
}

/*--------------------------------------------------------------------*/
/* FUN_00359ce4 @ 0x00359ce4   (est. sk_syscall_9ce4_stub)
 * Ghidra: void FUN_00359ce4(void)
 * Empty exception-entry stub.
 * Confidence: medium */
void sk_syscall_9ce4_stub(void)
{
    /* no-op */
}

/*--------------------------------------------------------------------*/
/* FUN_00359cf8 @ 0x00359cf8   (est. sk_syscall_9cf8_copy_byte)
 * Ghidra: void FUN_00359cf8(void)
 * Copies a single byte at offset 0x10 between two caller-saved
 * registers (x20<-x19). Argument marshaling of a small object field.
 * Confidence: medium
 * Notes: unaff_x19/x20 caller-saved registers. */
void sk_syscall_9cf8_copy_byte(void)
{
    /* *(undefined1 *)(unaff_x20 + 0x10) = *(undefined1 *)(unaff_x19 + 0x10); */
}

/*--------------------------------------------------------------------*/
/* FUN_00359d18 @ 0x00359d18   (est. sk_syscall_9d18_stub)
 * Ghidra: void FUN_00359d18(void)
 * Empty exception-entry stub.
 * Confidence: medium */
void sk_syscall_9d18_stub(void)
{
    /* no-op */
}

/*--------------------------------------------------------------------*/
/* FUN_00359d2c @ 0x00359d2c   (est. sk_syscall_9d2c_stub)
 * Ghidra: void FUN_00359d2c(void)
 * Empty exception-entry stub.
 * Confidence: medium */
void sk_syscall_9d2c_stub(void)
{
    /* no-op */
}

/*--------------------------------------------------------------------*/
/* FUN_00359d38 @ 0x00359d38   (est. sk_syscall_9d38_stub)
 * Ghidra: void FUN_00359d38(void)
 * Empty exception-entry stub.
 * Confidence: medium */
void sk_syscall_9d38_stub(void)
{
    /* no-op */
}

/*--------------------------------------------------------------------*/
/* FUN_00359d44 @ 0x00359d44   (est. sk_syscall_9d44_stub)
 * Ghidra: void FUN_00359d44(void)
 * Empty exception-entry stub.
 * Confidence: medium */
void sk_syscall_9d44_stub(void)
{
    /* no-op */
}

/*--------------------------------------------------------------------*/
/* FUN_00359d58 @ 0x00359d58   (est. sk_syscall_9d58_stub)
 * Ghidra: void FUN_00359d58(void)
 * Empty exception-entry stub.
 * Confidence: medium */
void sk_syscall_9d58_stub(void)
{
    /* no-op */
}

/*--------------------------------------------------------------------*/
/* FUN_00359d64 @ 0x00359d64   (est. sk_syscall_9d64_stub)
 * Ghidra: void FUN_00359d64(void)
 * Empty exception-entry stub.
 * Confidence: medium */
void sk_syscall_9d64_stub(void)
{
    /* no-op */
}

/*--------------------------------------------------------------------*/
/* FUN_00359d70 @ 0x00359d70   (est. sk_syscall_9d70_stub)
 * Ghidra: void FUN_00359d70(void)
 * Empty exception-entry stub.
 * Confidence: medium */
void sk_syscall_9d70_stub(void)
{
    /* no-op */
}

/*--------------------------------------------------------------------*/
/* FUN_00359d7c @ 0x00359d7c   (est. sk_syscall_9d7c_store_pair)
 * Ghidra: void FUN_00359d7c(void)
 * Stores a {pointer, byte-tag} pair into the object whose address sits
 * in the saved frame: *slot = x19, slot[1] = w8. Argument/result
 * record write for a syscall return path.
 * Confidence: medium
 * Notes: unaff_x19 (value), in_w8 (byte tag), unaff_x29 frame. */
void sk_syscall_9d7c_store_pair(void)
{
    /* puVar1 = *(undefined8 **)(unaff_x29 + -0x68);
     * *puVar1 = unaff_x19;
     * *(undefined1 *)(puVar1 + 1) = in_w8; */
}

/*--------------------------------------------------------------------*/
/* FUN_00359d90 @ 0x00359d90   (est. sk_syscall_9d90_stub)
 * Ghidra: void FUN_00359d90(void)
 * Empty exception-entry stub.
 * Confidence: medium */
void sk_syscall_9d90_stub(void)
{
    /* no-op */
}

/*--------------------------------------------------------------------*/
/* FUN_00359d9c @ 0x00359d9c   (est. sk_syscall_9d9c_addr_pair)
 * Ghidra: undefined1 [16] FUN_00359d9c(long param_1)
 * Returns a 16-byte address pair: lo = (saved base - 0x60) + param_1,
 * hi = x24 + x22. Computes a tagged address pair (capability/data pair).
 * Confidence: low (decompiler lost most frame params).
 * Notes: unaff_x22/x24 caller-saved; body only computes the pair. */
sk_pair_t sk_syscall_9d9c_addr_pair(uint64_t param_1)
{
    sk_pair_t r;
    r.lo = (0x0 - 0x60) + param_1;   /* unaff_x29 - 0x60 + param_1 */
    r.hi = 0x0;                      /* unaff_x24 + unaff_x22 */
    return r;
}

/*--------------------------------------------------------------------*/
/* FUN_00359db0 @ 0x00359db0   (est. sk_syscall_9db0_stub)
 * Ghidra: void FUN_00359db0(void)
 * Empty exception-entry stub.
 * Confidence: medium */
void sk_syscall_9db0_stub(void)
{
    /* no-op */
}

/*--------------------------------------------------------------------*/
/* FUN_00359dc4 @ 0x00359dc4   (est. sk_syscall_9dc4_stub)
 * Ghidra: void FUN_00359dc4(void)
 * Empty exception-entry stub.
 * Confidence: medium */
void sk_syscall_9dc4_stub(void)
{
    /* no-op */
}

/*--------------------------------------------------------------------*/
/* FUN_00359dd0 @ 0x00359dd0   (est. sk_syscall_9dd0_stub)
 * Ghidra: void FUN_00359dd0(void)
 * Empty exception-entry stub.
 * Confidence: medium */
void sk_syscall_9dd0_stub(void)
{
    /* no-op */
}

/*--------------------------------------------------------------------*/
/* FUN_00359ddc @ 0x00359ddc   (est. sk_syscall_9ddc_stub)
 * Ghidra: void FUN_00359ddc(void)
 * Empty exception-entry stub.
 * Confidence: medium */
void sk_syscall_9ddc_stub(void)
{
    /* no-op */
}

/*--------------------------------------------------------------------*/
/* FUN_00359de8 @ 0x00359de8   (est. sk_syscall_9de8_stub)
 * Ghidra: void FUN_00359de8(void)
 * Empty exception-entry stub.
 * Confidence: medium */
void sk_syscall_9de8_stub(void)
{
    /* no-op */
}

/*--------------------------------------------------------------------*/
/* FUN_00359df4 @ 0x00359df4   (est. sk_syscall_9df4_stub)
 * Ghidra: void FUN_00359df4(void)
 * Empty exception-entry stub.
 * Confidence: medium */
void sk_syscall_9df4_stub(void)
{
    /* no-op */
}

/*--------------------------------------------------------------------*/
/* FUN_00359e08 @ 0x00359e08   (est. sk_syscall_9e08_stub)
 * Ghidra: void FUN_00359e08(void)
 * Empty exception-entry stub.
 * Confidence: medium */
void sk_syscall_9e08_stub(void)
{
    /* no-op */
}

/*--------------------------------------------------------------------*/
/* FUN_00359e14 @ 0x00359e14   (est. sk_syscall_9e14_addr_pair)
 * Ghidra: undefined1 [16] FUN_00359e14(void)
 * Returns a 16-byte pair: lo = x22 + *(int *)(x23 + 0x30), hi = x25+x24.
 * Computes an address pair where lo indexes into a per-cpu/offset table
 * at (base + 0x30) and hi is a running accumulator. Argument marshaling.
 * Confidence: low (frame params dropped by decompiler).
 * Notes: unaff_x22..x25 caller-saved; *(int *)(x23+0x30) lane base. */
sk_pair_t sk_syscall_9e14_addr_pair(void)
{
    sk_pair_t r;
    r.lo = 0x0 + *(int *)(0x0 + 0x30);  /* x22 + *(int *)(x23+0x30) */
    r.hi = 0x0;                          /* x25 + x24 */
    return r;
}

/*--------------------------------------------------------------------*/
/* FUN_00359e28 @ 0x00359e28   (est. sk_syscall_9e28_lane_addr)
 * Ghidra: long FUN_00359e28(void)
 * Returns a base register + a 32-bit lane offset read at (base2 + 0x30).
 * Computes a table/vector element address.
 * Confidence: low (frame params dropped).
 * Notes: unaff_x23/x27 caller-saved. */
uint64_t sk_syscall_9e28_lane_addr(void)
{
    return 0x0 + *(int *)(0x0 + 0x30);   /* x27 + *(int *)(x23+0x30) */
}

/*--------------------------------------------------------------------*/
/* FUN_00359e34 @ 0x00359e34   (est. sk_syscall_9e34_lane_addr)
 * Ghidra: long FUN_00359e34(void)
 * Same shape as 9e28: base (x25) + 32-bit lane at (x23+0x30).
 * Confidence: low. */
uint64_t sk_syscall_9e34_lane_addr(void)
{
    return 0x0 + *(int *)(0x0 + 0x30);   /* x25 + *(int *)(x23+0x30) */
}

/*--------------------------------------------------------------------*/
/* FUN_00359e40 @ 0x00359e40   (est. sk_syscall_9e40_lane_addr)
 * Ghidra: long FUN_00359e40(void)
 * Same shape as 9e28: base (x26) + 32-bit lane at (x23+0x30).
 * Confidence: low. */
uint64_t sk_syscall_9e40_lane_addr(void)
{
    return 0x0 + *(int *)(0x0 + 0x30);   /* x26 + *(int *)(x23+0x30) */
}

/*--------------------------------------------------------------------*/
/* FUN_00359e4c @ 0x00359e4c   (est. sk_syscall_9e4c_stub)
 * Ghidra: void FUN_00359e4c(void)
 * Empty exception-entry stub.
 * Confidence: medium */
void sk_syscall_9e4c_stub(void)
{
    /* no-op */
}

/*--------------------------------------------------------------------*/
/* FUN_00359e60 @ 0x00359e60   (est. sk_syscall_9e60_stub)
 * Ghidra: void FUN_00359e60(void)
 * Empty exception-entry stub.
 * Confidence: medium */
void sk_syscall_9e60_stub(void)
{
    /* no-op */
}

/*--------------------------------------------------------------------*/
/* FUN_00359e74 @ 0x00359e74   (est. sk_syscall_9e74_stub)
 * Ghidra: void FUN_00359e74(void)
 * Empty exception-entry stub.
 * Confidence: medium */
void sk_syscall_9e74_stub(void)
{
    /* no-op */
}

/*--------------------------------------------------------------------*/
/* FUN_00359e80 @ 0x00359e80   (est. sk_syscall_9e80_stub)
 * Ghidra: void FUN_00359e80(void)
 * Empty exception-entry stub.
 * Confidence: medium */
void sk_syscall_9e80_stub(void)
{
    /* no-op */
}

/*--------------------------------------------------------------------*/
/* FUN_00359e8c @ 0x00359e8c   (est. sk_syscall_9e8c_stub)
 * Ghidra: void FUN_00359e8c(void)
 * Empty exception-entry stub.
 * Confidence: medium */
void sk_syscall_9e8c_stub(void)
{
    /* no-op */
}

/*--------------------------------------------------------------------*/
/* FUN_00359ea0 @ 0x00359ea0   (est. sk_syscall_9ea0_copy_bytes)
 * Ghidra: void FUN_00359ea0(long param_1,long param_2)
 * Copies two adjacent bytes from param_2 to param_1 at offsets 0x10 and
 * 0x11. Two-byte field copy in an argument record.
 * Confidence: medium. */
void sk_syscall_9ea0_copy_bytes(uint64_t dst, uint64_t src)
{
    *(uint8_t *)(dst + 0x10) = *(uint8_t *)(src + 0x10);
    *(uint8_t *)(dst + 0x11) = *(uint8_t *)(src + 0x11);
}

/*--------------------------------------------------------------------*/
/* FUN_00359eb4 @ 0x00359eb4   (est. sk_syscall_9eb4_stub)
 * Ghidra: void FUN_00359eb4(void)
 * Empty exception-entry stub.
 * Confidence: medium */
void sk_syscall_9eb4_stub(void)
{
    /* no-op */
}

/*--------------------------------------------------------------------*/
/* FUN_00359ec0 @ 0x00359ec0   (est. sk_syscall_9ec0_stub)
 * Ghidra: void FUN_00359ec0(void)
 * Empty exception-entry stub.
 * Confidence: medium */
void sk_syscall_9ec0_stub(void)
{
    /* no-op */
}

/*--------------------------------------------------------------------*/
/* FUN_00359ed4 @ 0x00359ed4   (est. sk_syscall_9ed4_stub)
 * Ghidra: void FUN_00359ed4(void)
 * Empty exception-entry stub.
 * Confidence: medium */
void sk_syscall_9ed4_stub(void)
{
    /* no-op */
}

/*--------------------------------------------------------------------*/
/* FUN_00359ee0 @ 0x00359ee0   (est. sk_syscall_9ee0_stub)
 * Ghidra: void FUN_00359ee0(void)
 * Empty exception-entry stub.
 * Confidence: medium */
void sk_syscall_9ee0_stub(void)
{
    /* no-op */
}

/*--------------------------------------------------------------------*/
/* FUN_00359ef4 @ 0x00359ef4   (est. sk_syscall_9ef4_stub)
 * Ghidra: void FUN_00359ef4(void)
 * Empty exception-entry stub.
 * Confidence: medium */
void sk_syscall_9ef4_stub(void)
{
    /* no-op */
}

/*--------------------------------------------------------------------*/
/* FUN_00359f08 @ 0x00359f08   (est. sk_syscall_9f08_store_arg)
 * Ghidra: void FUN_00359f08(undefined8 param_1)
 * Spills param_1 into the saved frame at -0x58. Prologue fragment.
 * Confidence: low (frame param dropped). */
void sk_syscall_9f08_store_arg(uint64_t arg)
{
    /* *(undefined8 *)(unaff_x29 + -0x58) = arg; */
}

/*--------------------------------------------------------------------*/
/* FUN_00359f14 @ 0x00359f14   (est. sk_syscall_9f14_save_return)
 * Ghidra: long FUN_00359f14(undefined8 param_1)
 * Spills param_1 at -0x58 and returns a pointer to the saved frame
 * buffer at x29-0x78. Returns a scratch area base.
 * Confidence: low. */
uint64_t sk_syscall_9f14_save_return(uint64_t arg)
{
    /* *(undefined8 *)(unaff_x29 + -0x58) = arg; */
    return 0x0 - 0x78;   /* unaff_x29 - 0x78 */
}

/*--------------------------------------------------------------------*/
/* FUN_00359f28 @ 0x00359f28   (est. sk_syscall_9f28_stub)
 * Ghidra: void FUN_00359f28(void)
 * Empty exception-entry stub.
 * Confidence: medium */
void sk_syscall_9f28_stub(void)
{
    /* no-op */
}

/*--------------------------------------------------------------------*/
/* FUN_00359f3c @ 0x00359f3c   (est. sk_syscall_9f3c_stub)
 * Ghidra: void FUN_00359f3c(void)
 * Empty exception-entry stub.
 * Confidence: medium */
void sk_syscall_9f3c_stub(void)
{
    /* no-op */
}

/*--------------------------------------------------------------------*/
/* FUN_00359f48 @ 0x00359f48   (est. sk_syscall_9f48_stub)
 * Ghidra: void FUN_00359f48(void)
 * Empty exception-entry stub.
 * Confidence: medium */
void sk_syscall_9f48_stub(void)
{
    /* no-op */
}

/*--------------------------------------------------------------------*/
/* FUN_00359f54 @ 0x00359f54   (est. sk_syscall_9f54_stub)
 * Ghidra: void FUN_00359f54(void)
 * Empty exception-entry stub.
 * Confidence: medium */
void sk_syscall_9f54_stub(void)
{
    /* no-op */
}

/*--------------------------------------------------------------------*/
/* FUN_00359f60 @ 0x00359f60   (est. sk_syscall_9f60_stub)
 * Ghidra: void FUN_00359f60(void)
 * Empty exception-entry stub.
 * Confidence: medium */
void sk_syscall_9f60_stub(void)
{
    /* no-op */
}

/*--------------------------------------------------------------------*/
/* FUN_00359f6c @ 0x00359f6c   (est. sk_syscall_9f6c_load_arg)
 * Ghidra: undefined8 FUN_00359f6c(void)
 * Loads a word from the saved frame at -0x98 and returns it. Reads a
 * saved syscall argument/result slot.
 * Confidence: low. */
uint64_t sk_syscall_9f6c_load_arg(void)
{
    return *(uint64_t *)(0x0 - 0x98);   /* *(unaff_x29 - 0x98) */
}

/*--------------------------------------------------------------------*/
/* FUN_00359f78 @ 0x00359f78   (est. sk_syscall_9f78_stub)
 * Ghidra: void FUN_00359f78(void)
 * Empty exception-entry stub.
 * Confidence: medium */
void sk_syscall_9f78_stub(void)
{
    /* no-op */
}

/*--------------------------------------------------------------------*/
/* FUN_00359f8c @ 0x00359f8c   (est. sk_syscall_9f8c_store_two)
 * Ghidra: void FUN_00359f8c(undefined8 param_1,undefined8 param_2)
 * Spills param_2 (at -0x68) and a caller-saved register x20 (at -0x60)
 * into the frame. Argument record prologue.
 * Confidence: low. */
void sk_syscall_9f8c_store_two(uint64_t a, uint64_t b)
{
    /* *(undefined8 *)(unaff_x29 + -0x68) = b; */
    /* *(undefined8 *)(unaff_x29 + -0x60) = unaff_x20; */
}

/*--------------------------------------------------------------------*/
/* FUN_00359fa0 @ 0x00359fa0   (est. sk_syscall_9fa0_stub)
 * Ghidra: void FUN_00359fa0(void)
 * Empty exception-entry stub.
 * Confidence: medium */
void sk_syscall_9fa0_stub(void)
{
    /* no-op */
}

/*--------------------------------------------------------------------*/
/* FUN_00359fb4 @ 0x00359fb4   (est. sk_syscall_9fb4_stub)
 * Ghidra: void FUN_00359fb4(void)
 * Empty exception-entry stub.
 * Confidence: medium */
void sk_syscall_9fb4_stub(void)
{
    /* no-op */
}

/*--------------------------------------------------------------------*/
/* FUN_00359fc0 @ 0x00359fc0   (est. sk_syscall_9fc0_stub)
 * Ghidra: void FUN_00359fc0(void)
 * Empty exception-entry stub.
 * Confidence: medium */
void sk_syscall_9fc0_stub(void)
{
    /* no-op */
}

/*--------------------------------------------------------------------*/
/* FUN_00359fd4 @ 0x00359fd4   (est. sk_syscall_9fd4_stub)
 * Ghidra: void FUN_00359fd4(void)
 * Empty exception-entry stub.
 * Confidence: medium */
void sk_syscall_9fd4_stub(void)
{
    /* no-op */
}

/*--------------------------------------------------------------------*/
/* FUN_00359fe8 @ 0x00359fe8   (est. sk_syscall_9fe8_stub)
 * Ghidra: void FUN_00359fe8(void)
 * Empty exception-entry stub.
 * Confidence: medium */
void sk_syscall_9fe8_stub(void)
{
    /* no-op */
}

/*--------------------------------------------------------------------*/
/* FUN_00359ffc @ 0x00359ffc   (est. sk_syscall_9ffc_stub)
 * Ghidra: void FUN_00359ffc(void)
 * Empty exception-entry stub.
 * Confidence: medium */
void sk_syscall_9ffc_stub(void)
{
    /* no-op */
}

/*--------------------------------------------------------------------*/
/* FUN_0035a010 @ 0x0035a010   (est. sk_syscall_a010_stub)
 * Ghidra: void FUN_0035a010(void)
 * Empty exception-entry stub.
 * Confidence: medium */
void sk_syscall_a010_stub(void)
{
    /* no-op */
}

/*--------------------------------------------------------------------*/
/* FUN_0035a01c @ 0x0035a01c   (est. sk_syscall_a01c_stub)
 * Ghidra: void FUN_0035a01c(void)
 * Empty exception-entry stub.
 * Confidence: medium */
void sk_syscall_a01c_stub(void)
{
    /* no-op */
}

/*--------------------------------------------------------------------*/
/* FUN_0035a028 @ 0x0035a028   (est. sk_syscall_a028_stub)
 * Ghidra: void FUN_0035a028(void)
 * Empty exception-entry stub.
 * Confidence: medium */
void sk_syscall_a028_stub(void)
{
    /* no-op */
}

/*--------------------------------------------------------------------*/
/* FUN_0035a034 @ 0x0035a034   (est. sk_syscall_a034_stub)
 * Ghidra: void FUN_0035a034(void)
 * Empty exception-entry stub.
 * Confidence: medium */
void sk_syscall_a034_stub(void)
{
    /* no-op */
}

/*--------------------------------------------------------------------*/
/* FUN_0035a040 @ 0x0035a040   (est. sk_syscall_a040_load_pair)
 * Ghidra: undefined1 [16] FUN_0035a040(long param_1)
 * Returns a 16-byte pair: lo = *(param_1+0x10), hi = 0, shifted left
 * 64 bits. This is a doubleword load of a single field into the
 * high half of the return register pair.
 * Confidence: low (frame param dropped). */
sk_pair_t sk_syscall_a040_load_pair(uint64_t param_1)
{
    sk_pair_t r;
    r.hi = *(uint64_t *)(param_1 + 0x10);   /* loaded into high 64 */
    r.lo = 0;
    return r;
}

/*--------------------------------------------------------------------*/
/* FUN_0035a04c @ 0x0035a04c   (est. sk_syscall_a04c_stub)
 * Ghidra: void FUN_0035a04c(void)
 * Empty exception-entry stub.
 * Confidence: medium */
void sk_syscall_a04c_stub(void)
{
    /* no-op */
}

/*--------------------------------------------------------------------*/
/* FUN_0035a058 @ 0x0035a058   (est. sk_syscall_a058_lane_addr)
 * Ghidra: long FUN_0035a058(void)
 * Returns a saved word at (x29-0x70) plus a caller-saved x26. Address
 * computation helper.
 * Confidence: low. */
uint64_t sk_syscall_a058_lane_addr(void)
{
    return 0x0 + *(uint64_t *)(0x0 - 0x70);  /* x26 + *(unaff_x29 - 0x70) */
}

/*--------------------------------------------------------------------*/
/* FUN_0035a06c @ 0x0035a06c   (est. sk_syscall_a06c_stub)
 * Ghidra: void FUN_0035a06c(void)
 * Empty exception-entry stub.
 * Confidence: medium */
void sk_syscall_a06c_stub(void)
{
    /* no-op */
}

/*--------------------------------------------------------------------*/
/* FUN_0035a080 @ 0x0035a080   (est. sk_syscall_a080_stub)
 * Ghidra: void FUN_0035a080(void)
 * Empty exception-entry stub.
 * Confidence: medium */
void sk_syscall_a080_stub(void)
{
    /* no-op */
}

/*--------------------------------------------------------------------*/
/* FUN_0035a08c @ 0x0035a08c   (est. sk_syscall_a08c_stub)
 * Ghidra: void FUN_0035a08c(void)
 * Empty exception-entry stub.
 * Confidence: medium */
void sk_syscall_a08c_stub(void)
{
    /* no-op */
}

/*--------------------------------------------------------------------*/
/* FUN_0035a098 @ 0x0035a098   (est. sk_syscall_a098_stub)
 * Ghidra: void FUN_0035a098(void)
 * Empty exception-entry stub.
 * Confidence: medium */
void sk_syscall_a098_stub(void)
{
    /* no-op */
}

/*--------------------------------------------------------------------*/
/* FUN_0035a0a4 @ 0x0035a0a4   (est. sk_syscall_a0a4_stub)
 * Ghidra: void FUN_0035a0a4(void)
 * Empty exception-entry stub.
 * Confidence: medium */
void sk_syscall_a0a4_stub(void)
{
    /* no-op */
}

/*--------------------------------------------------------------------*/
/* FUN_0035a0b8 @ 0x0035a0b8   (est. sk_syscall_a0b8_stub)
 * Ghidra: void FUN_0035a0b8(void)
 * Empty exception-entry stub.
 * Confidence: medium */
void sk_syscall_a0b8_stub(void)
{
    /* no-op */
}

/*--------------------------------------------------------------------*/
/* FUN_0035a0c4 @ 0x0035a0c4   (est. sk_syscall_a0c4_stub)
 * Ghidra: void FUN_0035a0c4(void)
 * Empty exception-entry stub.
 * Confidence: medium */
void sk_syscall_a0c4_stub(void)
{
    /* no-op */
}

/*--------------------------------------------------------------------*/
/* FUN_0035a0d8 @ 0x0035a0d8   (est. sk_syscall_a0d8_dispatch)
 * Ghidra: void FUN_0035a0d8(void)
 * Thin wrapper: tail-calls the no-arg helper FUN_0031ba70 (capability
 * refcount region). Callers: FUN_0028ff78, FUN_0029040c, FUN_002907b8,
 * FUN_00290c00, FUN_00290f34, FUN_0029e00c, FUN_002aa154.
 * Confidence: medium.
 * Notes: out-of-slice callee FUN_0031ba70. */
void sk_syscall_a0d8_dispatch(void)
{
    sk_helper_0031ba70();   /* FUN_0031ba70 */
}

/*--------------------------------------------------------------------*/
/* FUN_0035a0f0 @ 0x0035a0f0   (est. sk_syscall_a0f0_stub)
 * Ghidra: void FUN_0035a0f0(void)
 * Empty exception-entry stub.
 * Confidence: medium */
void sk_syscall_a0f0_stub(void)
{
    /* no-op */
}

/*--------------------------------------------------------------------*/
/* FUN_0035a104 @ 0x0035a104   (est. sk_syscall_a104_stub)
 * Ghidra: void FUN_0035a104(void)
 * Empty exception-entry stub.
 * Confidence: medium */
void sk_syscall_a104_stub(void)
{
    /* no-op */
}

/*--------------------------------------------------------------------*/
/* FUN_0035a110 @ 0x0035a110   (est. sk_syscall_a110_stub)
 * Ghidra: void FUN_0035a110(void)
 * Empty exception-entry stub.
 * Confidence: medium */
void sk_syscall_a110_stub(void)
{
    /* no-op */
}

/*--------------------------------------------------------------------*/
/* FUN_0035a11c @ 0x0035a11c   (est. sk_syscall_a11c_stub)
 * Ghidra: void FUN_0035a11c(void)
 * Empty exception-entry stub.
 * Confidence: medium */
void sk_syscall_a11c_stub(void)
{
    /* no-op */
}

/*--------------------------------------------------------------------*/
/* FUN_0035a128 @ 0x0035a128   (est. sk_syscall_a128_stub)
 * Ghidra: void FUN_0035a128(void)
 * Empty exception-entry stub.
 * Confidence: medium */
void sk_syscall_a128_stub(void)
{
    /* no-op */
}

/*--------------------------------------------------------------------*/
/* FUN_0035a134 @ 0x0035a134   (est. sk_syscall_a134_stub)
 * Ghidra: void FUN_0035a134(void)
 * Empty exception-entry stub.
 * Confidence: medium */
void sk_syscall_a134_stub(void)
{
    /* no-op */
}

/*--------------------------------------------------------------------*/
/* FUN_0035a140 @ 0x0035a140   (est. sk_syscall_a140_stub)
 * Ghidra: void FUN_0035a140(void)
 * Empty exception-entry stub.
 * Confidence: medium */
void sk_syscall_a140_stub(void)
{
    /* no-op */
}

/*--------------------------------------------------------------------*/
/* FUN_0035a14c @ 0x0035a14c   (est. sk_syscall_a14c_stub)
 * Ghidra: void FUN_0035a14c(void)
 * Empty exception-entry stub.
 * Confidence: medium */
void sk_syscall_a14c_stub(void)
{
    /* no-op */
}

/*--------------------------------------------------------------------*/
/* FUN_0035a158 @ 0x0035a158   (est. sk_syscall_a158_stub)
 * Ghidra: void FUN_0035a158(void)
 * Empty exception-entry stub.
 * Confidence: medium */
void sk_syscall_a158_stub(void)
{
    /* no-op */
}

/*--------------------------------------------------------------------*/
/* FUN_0035a16c @ 0x0035a16c   (est. sk_syscall_a16c_stub)
 * Ghidra: void FUN_0035a16c(void)
 * Empty exception-entry stub.
 * Confidence: medium */
void sk_syscall_a16c_stub(void)
{
    /* no-op */
}

/*--------------------------------------------------------------------*/
/* FUN_0035a184 @ 0x0035a184   (est. sk_syscall_a184_stub)
 * Ghidra: void FUN_0035a184(void)
 * Empty exception-entry stub.
 * Confidence: medium */
void sk_syscall_a184_stub(void)
{
    /* no-op */
}

/*--------------------------------------------------------------------*/
/* FUN_0035a190 @ 0x0035a190   (est. sk_syscall_a190_stub)
 * Ghidra: void FUN_0035a190(void)
 * Empty exception-entry stub.
 * Confidence: medium */
void sk_syscall_a190_stub(void)
{
    /* no-op */
}

/*--------------------------------------------------------------------*/
/* FUN_0035a19c @ 0x0035a19c   (est. sk_syscall_a19c_stub)
 * Ghidra: void FUN_0035a19c(void)
 * Empty exception-entry stub.
 * Confidence: medium */
void sk_syscall_a19c_stub(void)
{
    /* no-op */
}

/*--------------------------------------------------------------------*/
/* FUN_0035a1b4 @ 0x0035a1b4   (est. sk_syscall_a1b4_stub)
 * Ghidra: void FUN_0035a1b4(void)
 * Empty exception-entry stub.
 * Confidence: medium */
void sk_syscall_a1b4_stub(void)
{
    /* no-op */
}

/*--------------------------------------------------------------------*/
/* FUN_0035a1c0 @ 0x0035a1c0   (est. sk_syscall_a1c0_add_saved)
 * Ghidra: long FUN_0035a1c0(void)
 * Returns the sum of two saved frame words at -0x68 and -0x90.
 * Address-accumulation helper.
 * Confidence: low. */
uint64_t sk_syscall_a1c0_add_saved(void)
{
    return *(uint64_t *)(0x0 - 0x68) + *(uint64_t *)(0x0 - 0x90);
}

/*--------------------------------------------------------------------*/
/* FUN_0035a1d4 @ 0x0035a1d4   (est. sk_syscall_a1d4_pack_record)
 * Ghidra: void FUN_0035a1d4(void)
 * Packs four 8-byte stack words plus a 1-byte tag into a caller
 * register-record (x20): words at offsets 0,8,16,24 and a byte tag at
 * +0x21. Marshals a fixed 6-field argument/result record.
 * Confidence: low (stack args in_stack_0000001x + caller x20).
 * Notes: in_stack_00000010..28 are stack-passed args; byte tag at +0x21. */
void sk_syscall_a1d4_pack_record(void)
{
    uint64_t *rec;   /* unaff_x20 */
    (void)rec;
    /* rec[0] = stack_arg0; rec[1] = stack_arg1; rec[2] = stack_arg2;
     * rec[3] = stack_arg3;
     * *(byte*)((long)rec + 0x21) = byte_tag; */
}

/*--------------------------------------------------------------------*/
/* FUN_0035a1e8 @ 0x0035a1e8   (est. sk_syscall_a1e8_frame_ptr)
 * Ghidra: long FUN_0035a1e8(void)
 * Returns a pointer to the saved frame buffer at x29-0xb0.
 * Scratch-area base helper.
 * Confidence: low. */
uint64_t sk_syscall_a1e8_frame_ptr(void)
{
    return 0x0 - 0xb0;   /* unaff_x29 - 0xb0 */
}

/*--------------------------------------------------------------------*/
/* FUN_0035a1f4 @ 0x0035a1f4   (est. sk_syscall_a1f4_store_two)
 * Ghidra: void FUN_0035a1f4(void)
 * Spills two caller-saved registers x19 (at -0x80) and x25 (at -0x78).
 * Argument record prologue.
 * Confidence: low. */
void sk_syscall_a1f4_store_two(void)
{
    /* *(undefined8 *)(unaff_x29 + -0x80) = unaff_x19; */
    /* *(undefined8 *)(unaff_x29 + -0x78) = unaff_x25; */
}

/*--------------------------------------------------------------------*/
/* FUN_0035a200 @ 0x0035a200   (est. sk_syscall_a200_stub)
 * Ghidra: void FUN_0035a200(void)
 * Empty exception-entry stub.
 * Confidence: medium */
void sk_syscall_a200_stub(void)
{
    /* no-op */
}

/*--------------------------------------------------------------------*/
/* FUN_0035a20c @ 0x0035a20c   (est. sk_syscall_a20c_stub)
 * Ghidra: void FUN_0035a20c(void)
 * Empty exception-entry stub.
 * Confidence: medium */
void sk_syscall_a20c_stub(void)
{
    /* no-op */
}

/*--------------------------------------------------------------------*/
/* FUN_0035a218 @ 0x0035a218   (est. sk_syscall_a218_stub)
 * Ghidra: void FUN_0035a218(void)
 * Empty exception-entry stub.
 * Confidence: medium */
void sk_syscall_a218_stub(void)
{
    /* no-op */
}

/*--------------------------------------------------------------------*/
/* FUN_0035a224 @ 0x0035a224   (est. sk_syscall_a224_bump_count)
 * Ghidra: void FUN_0035a224(undefined8 param_1)
 * Stores param_1 into (x26+0x10) and increments a 32-bit counter at
 * (x26+0x24). Records an argument and counts invocations in a per-cpu
 * object.
 * Confidence: medium.
 * Notes: unaff_x26 caller-saved object base; count at +0x24. */
void sk_syscall_a224_bump_count(uint64_t arg)
{
    uint64_t *obj = (uint64_t *)0x0;   /* unaff_x26 */
    (void)obj;
    /* *(undefined8 *)(unaff_x26 + 0x10) = arg;
     * *(int *)(unaff_x26 + 0x24) = *(int *)(unaff_x26 + 0x24) + 1; */
}

/*--------------------------------------------------------------------*/
/* FUN_0035a238 @ 0x0035a238   (est. sk_syscall_a238_stub)
 * Ghidra: void FUN_0035a238(void)
 * Empty exception-entry stub.
 * Confidence: medium */
void sk_syscall_a238_stub(void)
{
    /* no-op */
}

/*--------------------------------------------------------------------*/
/* FUN_0035a244 @ 0x0035a244   (est. sk_syscall_a244_stub)
 * Ghidra: void FUN_0035a244(void)
 * Empty exception-entry stub.
 * Confidence: medium */
void sk_syscall_a244_stub(void)
{
    /* no-op */
}

/*--------------------------------------------------------------------*/
/* FUN_0035a250 @ 0x0035a250   (est. sk_syscall_a250_const_30)
 * Ghidra: undefined8 FUN_0035a250(void)
 * Returns the constant 0x30. Object/struct size or field-offset
 * accessor.
 * Confidence: medium. */
uint64_t sk_syscall_a250_const_30(void)
{
    return 0x30;
}

/*--------------------------------------------------------------------*/
/* FUN_0035a25c @ 0x0035a25c   (est. sk_syscall_a25c_stub)
 * Ghidra: void FUN_0035a25c(void)
 * Empty exception-entry stub.
 * Confidence: medium */
void sk_syscall_a25c_stub(void)
{
    /* no-op */
}

/*--------------------------------------------------------------------*/
/* FUN_0035a268 @ 0x0035a268   (est. sk_syscall_a268_stub)
 * Ghidra: void FUN_0035a268(void)
 * Empty exception-entry stub.
 * Confidence: medium */
void sk_syscall_a268_stub(void)
{
    /* no-op */
}

/*--------------------------------------------------------------------*/
/* FUN_0035a274 @ 0x0035a274   (est. sk_syscall_a274_stub)
 * Ghidra: void FUN_0035a274(void)
 * Empty exception-entry stub.
 * Confidence: medium */
void sk_syscall_a274_stub(void)
{
    /* no-op */
}

/*--------------------------------------------------------------------*/
/* FUN_0035a280 @ 0x0035a280   (est. sk_syscall_a280_stub)
 * Ghidra: void FUN_0035a280(void)
 * Empty exception-entry stub.
 * Confidence: medium */
void sk_syscall_a280_stub(void)
{
    /* no-op */
}

/*--------------------------------------------------------------------*/
/* FUN_0035a28c @ 0x0035a28c   (est. sk_syscall_a28c_stub)
 * Ghidra: void FUN_0035a28c(void)
 * Empty exception-entry stub.
 * Confidence: medium */
void sk_syscall_a28c_stub(void)
{
    /* no-op */
}

/*--------------------------------------------------------------------*/
/* FUN_0035a298 @ 0x0035a298   (est. sk_syscall_a298_stub)
 * Ghidra: void FUN_0035a298(void)
 * Empty exception-entry stub.
 * Confidence: medium */
void sk_syscall_a298_stub(void)
{
    /* no-op */
}

/*--------------------------------------------------------------------*/
/* FUN_0035a2ac @ 0x0035a2ac   (est. sk_syscall_a2ac_stub)
 * Ghidra: void FUN_0035a2ac(void)
 * Empty exception-entry stub.
 * Confidence: medium */
void sk_syscall_a2ac_stub(void)
{
    /* no-op */
}

/*--------------------------------------------------------------------*/
/* FUN_0035a2b8 @ 0x0035a2b8   (est. sk_syscall_a2b8_store_arg)
 * Ghidra: void FUN_0035a2b8(undefined8 param_1)
 * Spills param_1 into the frame at -0x68. Prologue fragment.
 * Confidence: low. */
void sk_syscall_a2b8_store_arg(uint64_t arg)
{
    /* *(undefined8 *)(unaff_x29 + -0x68) = arg; */
}

/*--------------------------------------------------------------------*/
/* FUN_0035a2c4 @ 0x0035a2c4   (est. sk_syscall_a2c4_stub)
 * Ghidra: void FUN_0035a2c4(void)
 * Empty exception-entry stub.
 * Confidence: medium */
void sk_syscall_a2c4_stub(void)
{
    /* no-op */
}

/*--------------------------------------------------------------------*/
/* FUN_0035a2d0 @ 0x0035a2d0   (est. sk_syscall_a2d0_stub)
 * Ghidra: void FUN_0035a2d0(void)
 * Empty exception-entry stub.
 * Confidence: medium */
void sk_syscall_a2d0_stub(void)
{
    /* no-op */
}

/*--------------------------------------------------------------------*/
/* FUN_0035a2dc @ 0x0035a2dc   (est. sk_syscall_a2dc_load_field)
 * Ghidra: undefined8 FUN_0035a2dc(void)
 * Returns the word at (x19 + 0x10). Reads a single field of an object
 * whose base is in caller-saved x19.
 * Confidence: low. */
uint64_t sk_syscall_a2dc_load_field(void)
{
    return *(uint64_t *)(0x0 + 0x10);   /* *(unaff_x19 + 0x10) */
}

/*--------------------------------------------------------------------*/
/* FUN_0035a2f0 @ 0x0035a2f0   (est. sk_syscall_a2f0_stub)
 * Ghidra: void FUN_0035a2f0(void)
 * Empty exception-entry stub.
 * Confidence: medium */
void sk_syscall_a2f0_stub(void)
{
    /* no-op */
}

/*--------------------------------------------------------------------*/
/* FUN_0035a2fc @ 0x0035a2fc   (est. sk_syscall_a2fc_stub)
 * Ghidra: void FUN_0035a2fc(void)
 * Empty exception-entry stub.
 * Confidence: medium */
void sk_syscall_a2fc_stub(void)
{
    /* no-op */
}

/*--------------------------------------------------------------------*/
/* FUN_0035a310 @ 0x0035a310   (est. sk_syscall_a310_stub)
 * Ghidra: void FUN_0035a310(void)
 * Empty exception-entry stub.
 * Confidence: medium */
void sk_syscall_a310_stub(void)
{
    /* no-op */
}

/*--------------------------------------------------------------------*/
/* FUN_0035a31c @ 0x0035a31c   (est. sk_syscall_a31c_stub)
 * Ghidra: void FUN_0035a31c(void)
 * Empty exception-entry stub.
 * Confidence: medium */
void sk_syscall_a31c_stub(void)
{
    /* no-op */
}

/*--------------------------------------------------------------------*/
/* FUN_0035a328 @ 0x0035a328   (est. sk_syscall_a328_stub)
 * Ghidra: void FUN_0035a328(void)
 * Empty exception-entry stub.
 * Confidence: medium */
void sk_syscall_a328_stub(void)
{
    /* no-op */
}

/*--------------------------------------------------------------------*/
/* FUN_0035a334 @ 0x0035a334   (est. sk_vector_compare_16)
 * Ghidra: undefined2 FUN_0035a334(undefined1 param_1[16],undefined1
 *        param_2[16],undefined1 param_3[16],undefined1 param_4[16])
 * Compares two 16-byte vectors (a=param_1/param_2 vs b=param_3/param_4)
 * lane-by-lane (8 x 32-bit lanes) for "less than" and returns nonzero
 * (0xffff) if any lane is strictly less, else 0. A bounds/ordering
 * check over two 128-bit values.
 * Confidence: medium
 * Notes: NEON_umaxv(...,2) over the 8 16-bit per-lane compare masks
 *   reduces to an OR; -(ushort)(x<y) yields 0xffff/0. */
uint16_t sk_vector_compare_16(sk_pair_t a_lo, sk_pair_t b_lo)
{
    /* 8 x 32-bit lanes: lo pair = param_2 vs param_3,
     * hi pair = param_1 vs param_4. */
    uint32_t *p2 = (uint32_t *)&a_lo.lo;  /* param_2 lanes */
    uint32_t *p3 = (uint32_t *)&b_lo.lo;  /* param_3 lanes */
    uint32_t *p1 = (uint32_t *)&a_lo.hi;  /* param_1 lanes */
    uint32_t *p4 = (uint32_t *)&b_lo.hi;  /* param_4 lanes */
    bool any = false;
    for (int i = 0; i < 4; i++) {
        any |= (p2[i] < p3[i]);
        any |= (p1[i] < p4[i]);
    }
    return any ? 0xffff : 0;
}

/*--------------------------------------------------------------------*/
/* FUN_0035a348 @ 0x0035a348   (est. sk_syscall_a348_stub)
 * Ghidra: void FUN_0035a348(void)
 * Empty exception-entry stub.
 * Confidence: medium */
void sk_syscall_a348_stub(void)
{
    /* no-op */
}

/*--------------------------------------------------------------------*/
/* FUN_0035a354 @ 0x0035a354   (est. sk_syscall_a354_stub)
 * Ghidra: void FUN_0035a354(void)
 * Empty exception-entry stub.
 * Confidence: medium */
void sk_syscall_a354_stub(void)
{
    /* no-op */
}

/*--------------------------------------------------------------------*/
/* FUN_0035a360 @ 0x0035a360   (est. sk_syscall_a360_stub)
 * Ghidra: void FUN_0035a360(void)
 * Empty exception-entry stub.
 * Confidence: medium */
void sk_syscall_a360_stub(void)
{
    /* no-op */
}

/*--------------------------------------------------------------------*/
/* FUN_0035a36c @ 0x0035a36c   (est. sk_syscall_a36c_stub)
 * Ghidra: void FUN_0035a36c(void)
 * Empty exception-entry stub.
 * Confidence: medium */
void sk_syscall_a36c_stub(void)
{
    /* no-op */
}

/*--------------------------------------------------------------------*/
/* FUN_0035a380 @ 0x0035a380   (est. sk_syscall_a380_stub)
 * Ghidra: void FUN_0035a380(void)
 * Empty exception-entry stub.
 * Confidence: medium */
void sk_syscall_a380_stub(void)
{
    /* no-op */
}

/*--------------------------------------------------------------------*/
/* FUN_0035a38c @ 0x0035a38c   (est. sk_syscall_a38c_stub)
 * Ghidra: void FUN_0035a38c(void)
 * Empty exception-entry stub.
 * Confidence: medium */
void sk_syscall_a38c_stub(void)
{
    /* no-op */
}

/*--------------------------------------------------------------------*/
/* FUN_0035a3a0 @ 0x0035a3a0   (est. sk_syscall_a3a0_stub)
 * Ghidra: void FUN_0035a3a0(void)
 * Empty exception-entry stub.
 * Confidence: medium */
void sk_syscall_a3a0_stub(void)
{
    /* no-op */
}

/*--------------------------------------------------------------------*/
/* FUN_0035a3ac @ 0x0035a3ac   (est. sk_syscall_a3ac_stub)
 * Ghidra: void FUN_0035a3ac(void)
 * Empty exception-entry stub.
 * Confidence: medium */
void sk_syscall_a3ac_stub(void)
{
    /* no-op */
}

/*--------------------------------------------------------------------*/
/* FUN_0035a3b8 @ 0x0035a3b8   (est. sk_syscall_a3b8_stub)
 * Ghidra: void FUN_0035a3b8(void)
 * Empty exception-entry stub.
 * Confidence: medium */
void sk_syscall_a3b8_stub(void)
{
    /* no-op */
}

/*--------------------------------------------------------------------*/
/* FUN_0035a3c4 @ 0x0035a3c4   (est. sk_syscall_a3c4_stub)
 * Ghidra: void FUN_0035a3c4(void)
 * Empty exception-entry stub.
 * Confidence: medium */
void sk_syscall_a3c4_stub(void)
{
    /* no-op */
}

/*--------------------------------------------------------------------*/
/* FUN_0035a3d0 @ 0x0035a3d0   (est. sk_syscall_a3d0_stub)
 * Ghidra: void FUN_0035a3d0(void)
 * Empty exception-entry stub.
 * Confidence: medium */
void sk_syscall_a3d0_stub(void)
{
    /* no-op */
}

/*--------------------------------------------------------------------*/
/* FUN_0035a3dc @ 0x0035a3dc   (est. sk_syscall_a3dc_stub)
 * Ghidra: void FUN_0035a3dc(void)
 * Empty exception-entry stub.
 * Confidence: medium */
void sk_syscall_a3dc_stub(void)
{
    /* no-op */
}

/*--------------------------------------------------------------------*/
/* FUN_0035a3e8 @ 0x0035a3e8   (est. sk_syscall_a3e8_stub)
 * Ghidra: void FUN_0035a3e8(void)
 * Empty exception-entry stub.
 * Confidence: medium */
void sk_syscall_a3e8_stub(void)
{
    /* no-op */
}

/*--------------------------------------------------------------------*/
/* FUN_0035a3f4 @ 0x0035a3f4   (est. sk_syscall_a3f4_stub)
 * Ghidra: void FUN_0035a3f4(void)
 * Empty exception-entry stub.
 * Confidence: medium */
void sk_syscall_a3f4_stub(void)
{
    /* no-op */
}

/*--------------------------------------------------------------------*/
/* FUN_0035a400 @ 0x0035a400   (est. sk_syscall_a400_stub)
 * Ghidra: void FUN_0035a400(void)
 * Empty exception-entry stub.
 * Confidence: medium */
void sk_syscall_a400_stub(void)
{
    /* no-op */
}

/*--------------------------------------------------------------------*/
/* FUN_0035a40c @ 0x0035a40c   (est. sk_syscall_a40c_stub)
 * Ghidra: void FUN_0035a40c(void)
 * Empty exception-entry stub.
 * Confidence: medium */
void sk_syscall_a40c_stub(void)
{
    /* no-op */
}

/*--------------------------------------------------------------------*/
/* FUN_0035a420 @ 0x0035a420   (est. sk_syscall_a420_load_pair)
 * Ghidra: undefined1 [16] FUN_0035a420(void)
 * Returns the 16-byte value stored in the frame buffer at x29-0x60.
 * Reads a saved 128-bit register pair.
 * Confidence: low. */
sk_pair_t sk_syscall_a420_load_pair(void)
{
    return *(sk_pair_t *)(0x0 - 0x60);   /* *(unaff_x29 - 0x60) */
}

/*--------------------------------------------------------------------*/
/* FUN_0035a42c @ 0x0035a42c   (est. sk_syscall_a42c_stub)
 * Ghidra: void FUN_0035a42c(void)
 * Empty exception-entry stub.
 * Confidence: medium */
void sk_syscall_a42c_stub(void)
{
    /* no-op */
}

/*--------------------------------------------------------------------*/
/* FUN_0035a438 @ 0x0035a438   (est. sk_syscall_a438_deref_add)
 * Ghidra: long FUN_0035a438(long param_1)
 * Returns (*(*x19 + 0x10)) + param_1: dereferences a double pointer,
 * reads offset 0x10, adds the argument. Computes a pointer into an
 * indirection table.
 * Confidence: low.
 * Notes: unaff_x19 holds a pointer to the table base pointer. */
uint64_t sk_syscall_a438_deref_add(uint64_t param_1)
{
    uint64_t **base = (uint64_t **)0x0;   /* unaff_x19 */
    (void)base;
    return 0x0 + param_1;   /* *( *(*base + 0x10)) + param_1 */
}

/*--------------------------------------------------------------------*/
/* FUN_0035a44c @ 0x0035a44c   (est. sk_syscall_a44c_dispatch)
 * Ghidra: void FUN_0035a44c(void)
 * Thin wrapper: tail-calls the no-arg helper FUN_00310a14. Callers:
 * FUN_00224180, FUN_00226320, FUN_00237f7c, FUN_00311038,
 * FUN_00311344.
 * Confidence: medium.
 * Notes: out-of-slice callee FUN_00310a14. */
void sk_syscall_a44c_dispatch(void)
{
    sk_helper_00310a14();   /* FUN_00310a14 */
}

/*--------------------------------------------------------------------*/
/* FUN_0035a464 @ 0x0035a464   (est. sk_syscall_a464_stub)
 * Ghidra: void FUN_0035a464(void)
 * Empty exception-entry stub.
 * Confidence: medium */
void sk_syscall_a464_stub(void)
{
    /* no-op */
}

/*--------------------------------------------------------------------*/
/* FUN_0035a478 @ 0x0035a478   (est. sk_syscall_a478_dispatch)
 * Ghidra: void FUN_0035a478(void)
 * Thin wrapper: tail-calls the no-arg helper FUN_0008f6f4. Callers:
 * FUN_001b2264, FUN_001b593c, FUN_0021ea88, FUN_00224180, FUN_00232068,
 * FUN_00294f80, FUN_002b8e34, FUN_00311344.
 * Confidence: medium.
 * Notes: out-of-slice callee FUN_0008f6f4. */
void sk_syscall_a478_dispatch(void)
{
    sk_helper_0008f6f4();   /* FUN_0008f6f4 */
}

/*--------------------------------------------------------------------*/
/* FUN_0035a490 @ 0x0035a490   (est. sk_syscall_a490_stub)
 * Ghidra: void FUN_0035a490(void)
 * Empty exception-entry stub.
 * Confidence: medium */
void sk_syscall_a490_stub(void)
{
    /* no-op */
}

/*--------------------------------------------------------------------*/
/* FUN_0035a49c @ 0x0035a49c   (est. sk_syscall_a49c_lane_addr)
 * Ghidra: long FUN_0035a49c(void)
 * Returns a base (x28) plus a 32-bit lane at (x22+0x30). Table/vector
 * element address helper.
 * Confidence: low.
 * Notes: unaff_x22/x28 caller-saved. */
uint64_t sk_syscall_a49c_lane_addr(void)
{
    return 0x0 + *(int *)(0x0 + 0x30);   /* x28 + *(int *)(x22+0x30) */
}

/*--------------------------------------------------------------------*/
/* FUN_0035a4a8 @ 0x0035a4a8   (est. sk_syscall_a4a8_stub)
 * Ghidra: void FUN_0035a4a8(void)
 * Empty exception-entry stub.
 * Confidence: medium */
void sk_syscall_a4a8_stub(void)
{
    /* no-op */
}

/*--------------------------------------------------------------------*/
/* FUN_0035a4bc @ 0x0035a4bc   (est. sk_syscall_a4bc_stub)
 * Ghidra: void FUN_0035a4bc(void)
 * Empty exception-entry stub.
 * Confidence: medium */
void sk_syscall_a4bc_stub(void)
{
    /* no-op */
}

/*--------------------------------------------------------------------*/
/* FUN_0035a4c8 @ 0x0035a4c8   (est. sk_syscall_a4c8_stub)
 * Ghidra: void FUN_0035a4c8(void)
 * Empty exception-entry stub.
 * Confidence: medium */
void sk_syscall_a4c8_stub(void)
{
    /* no-op */
}

/*--------------------------------------------------------------------*/
/* FUN_0035a4d4 @ 0x0035a4d4   (est. sk_syscall_a4d4_stub)
 * Ghidra: void FUN_0035a4d4(void)
 * Empty exception-entry stub.
 * Confidence: medium */
void sk_syscall_a4d4_stub(void)
{
    /* no-op */
}

/*--------------------------------------------------------------------*/
/* FUN_0035a4e0 @ 0x0035a4e0   (est. sk_syscall_a4e0_stub)
 * Ghidra: void FUN_0035a4e0(void)
 * Empty exception-entry stub.
 * Confidence: medium */
void sk_syscall_a4e0_stub(void)
{
    /* no-op */
}

/*--------------------------------------------------------------------*/
/* FUN_0035a4ec @ 0x0035a4ec   (est. sk_syscall_a4ec_stub)
 * Ghidra: void FUN_0035a4ec(void)
 * Empty exception-entry stub.
 * Confidence: medium */
void sk_syscall_a4ec_stub(void)
{
    /* no-op */
}

/*--------------------------------------------------------------------*/
/* FUN_0035a4f8 @ 0x0035a4f8   (est. sk_syscall_a4f8_stub)
 * Ghidra: void FUN_0035a4f8(void)
 * Empty exception-entry stub.
 * Confidence: medium */
void sk_syscall_a4f8_stub(void)
{
    /* no-op */
}

/*--------------------------------------------------------------------*/
/* FUN_0035a504 @ 0x0035a504   (est. sk_syscall_a504_stub)
 * Ghidra: void FUN_0035a504(void)
 * Empty exception-entry stub.
 * Confidence: medium */
void sk_syscall_a504_stub(void)
{
    /* no-op */
}

/*--------------------------------------------------------------------*/
/* FUN_0035a518 @ 0x0035a518   (est. sk_syscall_a518_addr_pair)
 * Ghidra: undefined1 [16] FUN_0035a518(long param_1)
 * Returns a 16-byte address pair: lo = x28 + *(int *)(in_x9+0x24),
 * hi = x25 + param_1. Computes a tagged address pair (table index +
 * running value).
 * Confidence: low (frame params dropped).
 * Notes: unaff_x25/x28, in_x9 caller-saved; *(int *)(in_x9+0x24) lane. */
sk_pair_t sk_syscall_a518_addr_pair(uint64_t param_1)
{
    sk_pair_t r;
    r.lo = 0x0 + *(int *)(0x0 + 0x24);  /* x28 + *(int *)(in_x9+0x24) */
    r.hi = 0x0 + param_1;                /* x25 + param_1 */
    return r;
}

/*--------------------------------------------------------------------*/
/* FUN_0035a52c @ 0x0035a52c   (est. sk_syscall_a52c_stub)
 * Ghidra: void FUN_0035a52c(void)
 * Empty exception-entry stub.
 * Confidence: medium */
void sk_syscall_a52c_stub(void)
{
    /* no-op */
}

/*--------------------------------------------------------------------*/
/* FUN_0035a540 @ 0x0035a540   (est. sk_syscall_a540_stub)
 * Ghidra: void FUN_0035a540(void)
 * Empty exception-entry stub.
 * Confidence: medium */
void sk_syscall_a540_stub(void)
{
    /* no-op */
}

/*--------------------------------------------------------------------*/
/* FUN_0035a54c @ 0x0035a54c   (est. sk_syscall_a54c_table_pair)
 * Ghidra: undefined1 [16] FUN_0035a54c(void)
 * Returns the 16-byte pair {base = &DAT_004e7d70, size = 0x800}.
 * Exposes a 2 KiB region's base and size as a pair.
 * Confidence: low.
 * Notes: DAT_004e7d70 table base; size 0x800. */
sk_pair_t sk_syscall_a54c_table_pair(void)
{
    sk_pair_t r;
    r.lo = (uint64_t)sk_tbl_004e7d70;   /* &DAT_004e7d70 */
    r.hi = 0x800;
    return r;
}

/*--------------------------------------------------------------------*/
/* FUN_0035a560 @ 0x0035a560   (est. sk_syscall_a560_load_arg)
 * Ghidra: undefined8 FUN_0035a560(void)
 * Loads a word from the saved frame at -0x58 and returns it.
 * Confidence: low. */
uint64_t sk_syscall_a560_load_arg(void)
{
    return *(uint64_t *)(0x0 - 0x58);   /* *(unaff_x29 - 0x58) */
}

/*--------------------------------------------------------------------*/
/* FUN_0035a56c @ 0x0035a56c   (est. sk_syscall_a56c_stub)
 * Ghidra: void FUN_0035a56c(void)
 * Empty exception-entry stub.
 * Confidence: medium */
void sk_syscall_a56c_stub(void)
{
    /* no-op */
}

/*--------------------------------------------------------------------*/
/* FUN_0035a578 @ 0x0035a578   (est. sk_syscall_a578_stub)
 * Ghidra: void FUN_0035a578(void)
 * Empty exception-entry stub.
 * Confidence: medium */
void sk_syscall_a578_stub(void)
{
    /* no-op */
}

/*--------------------------------------------------------------------*/
/* FUN_0035a584 @ 0x0035a584   (est. sk_syscall_a584_stub)
 * Ghidra: void FUN_0035a584(void)
 * Empty exception-entry stub.
 * Confidence: medium */
void sk_syscall_a584_stub(void)
{
    /* no-op */
}

/*--------------------------------------------------------------------*/
/* FUN_0035a590 @ 0x0035a590   (est. sk_syscall_a590_load_arg)
 * Ghidra: undefined8 FUN_0035a590(void)
 * Loads a word from the saved frame at -0xe0 and returns it.
 * Confidence: low. */
uint64_t sk_syscall_a590_load_arg(void)
{
    return *(uint64_t *)(0x0 - 0xe0);   /* *(unaff_x29 - 0xe0) */
}

/*--------------------------------------------------------------------*/
/* FUN_0035a59c @ 0x0035a59c   (est. sk_syscall_a59c_stub)
 * Ghidra: void FUN_0035a59c(void)
 * Empty exception-entry stub.
 * Confidence: medium */
void sk_syscall_a59c_stub(void)
{
    /* no-op */
}

/*--------------------------------------------------------------------*/
/* FUN_0035a5a8 @ 0x0035a5a8   (est. sk_syscall_a5a8_load_arg)
 * Ghidra: undefined8 FUN_0035a5a8(void)
 * Loads a word from the saved frame at -0x80 and returns it.
 * Confidence: low. */
uint64_t sk_syscall_a5a8_load_arg(void)
{
    return *(uint64_t *)(0x0 - 0x80);   /* *(unaff_x29 - 0x80) */
}

/*--------------------------------------------------------------------*/
/* FUN_0035a5b4 @ 0x0035a5b4   (est. sk_syscall_a5b4_stub)
 * Ghidra: void FUN_0035a5b4(void)
 * Empty exception-entry stub.
 * Confidence: medium */
void sk_syscall_a5b4_stub(void)
{
    /* no-op */
}

/*--------------------------------------------------------------------*/
/* FUN_0035a5c0 @ 0x0035a5c0   (est. sk_syscall_a5c0_stub)
 * Ghidra: void FUN_0035a5c0(void)
 * Empty exception-entry stub.
 * Confidence: medium */
void sk_syscall_a5c0_stub(void)
{
    /* no-op */
}

/*--------------------------------------------------------------------*/
/* FUN_0035a5cc @ 0x0035a5cc   (est. sk_syscall_a5cc_stub)
 * Ghidra: void FUN_0035a5cc(void)
 * Empty exception-entry stub.
 * Confidence: medium */
void sk_syscall_a5cc_stub(void)
{
    /* no-op */
}

/*--------------------------------------------------------------------*/
/* FUN_0035a5d8 @ 0x0035a5d8   (est. sk_syscall_a5d8_frame_ptr)
 * Ghidra: long FUN_0035a5d8(void)
 * Returns a pointer to the saved frame buffer at x29-0x80.
 * Confidence: low. */
uint64_t sk_syscall_a5d8_frame_ptr(void)
{
    return 0x0 - 0x80;   /* unaff_x29 - 0x80 */
}

/*--------------------------------------------------------------------*/
/* FUN_0035a5e4 @ 0x0035a5e4   (est. sk_syscall_a5e4_frame_ptr)
 * Ghidra: long FUN_0035a5e4(void)
 * Returns a pointer to the saved frame buffer at x29-0xa0.
 * Confidence: low. */
uint64_t sk_syscall_a5e4_frame_ptr(void)
{
    return 0x0 - 0xa0;   /* unaff_x29 - 0xa0 */
}

/*--------------------------------------------------------------------*/
/* FUN_0035a5f0 @ 0x0035a5f0   (est. sk_syscall_a5f0_stub)
 * Ghidra: void FUN_0035a5f0(void)
 * Empty exception-entry stub.
 * Confidence: medium */
void sk_syscall_a5f0_stub(void)
{
    /* no-op */
}

/*--------------------------------------------------------------------*/
/* FUN_0035a5fc @ 0x0035a5fc   (est. sk_syscall_a5fc_pair)
 * Ghidra: undefined1 [16] FUN_0035a5fc(undefined8 param_1)
 * Returns the 16-byte pair {*(x29-0x58), param_1}: packs a saved word
 * and the argument into a register pair.
 * Confidence: low. */
sk_pair_t sk_syscall_a5fc_pair(uint64_t param_1)
{
    sk_pair_t r;
    r.lo = *(uint64_t *)(0x0 - 0x58);   /* *(unaff_x29 - 0x58) */
    r.hi = param_1;
    return r;
}

/*--------------------------------------------------------------------*/
/* FUN_0035a608 @ 0x0035a608   (est. sk_syscall_a608_stub)
 * Ghidra: void FUN_0035a608(void)
 * Empty exception-entry stub.
 * Confidence: medium */
void sk_syscall_a608_stub(void)
{
    /* no-op */
}

/*--------------------------------------------------------------------*/
/* FUN_0035a614 @ 0x0035a614   (est. sk_syscall_a614_stub)
 * Ghidra: void FUN_0035a614(void)
 * Empty exception-entry stub.
 * Confidence: medium */
void sk_syscall_a614_stub(void)
{
    /* no-op */
}

/*--------------------------------------------------------------------*/
/* FUN_0035a620 @ 0x0035a620   (est. sk_syscall_a620_stub)
 * Ghidra: void FUN_0035a620(void)
 * Empty exception-entry stub.
 * Confidence: medium */
void sk_syscall_a620_stub(void)
{
    /* no-op */
}

/*--------------------------------------------------------------------*/
/* FUN_0035a634 @ 0x0035a634   (est. sk_syscall_a634_stub)
 * Ghidra: void FUN_0035a634(void)
 * Empty exception-entry stub.
 * Confidence: medium */
void sk_syscall_a634_stub(void)
{
    /* no-op */
}

/*--------------------------------------------------------------------*/
/* FUN_0035a640 @ 0x0035a640   (est. sk_syscall_a640_stub)
 * Ghidra: void FUN_0035a640(void)
 * Empty exception-entry stub.
 * Confidence: medium */
void sk_syscall_a640_stub(void)
{
    /* no-op */
}

/*--------------------------------------------------------------------*/
/* FUN_0035a64c @ 0x0035a64c   (est. sk_syscall_a64c_stub)
 * Ghidra: void FUN_0035a64c(void)
 * Empty exception-entry stub.
 * Confidence: medium */
void sk_syscall_a64c_stub(void)
{
    /* no-op */
}

/*--------------------------------------------------------------------*/
/* FUN_0035a658 @ 0x0035a658   (est. sk_syscall_a658_stub)
 * Ghidra: void FUN_0035a658(void)
 * Empty exception-entry stub.
 * Confidence: medium */
void sk_syscall_a658_stub(void)
{
    /* no-op */
}

/*--------------------------------------------------------------------*/
/* FUN_0035a664 @ 0x0035a664   (est. sk_syscall_a664_stub)
 * Ghidra: void FUN_0035a664(void)
 * Empty exception-entry stub.
 * Confidence: medium */
void sk_syscall_a664_stub(void)
{
    /* no-op */
}

/*--------------------------------------------------------------------*/
/* FUN_0035a670 @ 0x0035a670   (est. sk_syscall_a670_store_two)
 * Ghidra: void FUN_0035a670(void)
 * Spills caller-saved x9 (at -0x70) and x25 (at -0x68). Prologue.
 * Confidence: low. */
void sk_syscall_a670_store_two(void)
{
    /* *(undefined8 *)(unaff_x29 + -0x70) = in_x9; */
    /* *(undefined8 *)(unaff_x29 + -0x68) = unaff_x25; */
}

/*--------------------------------------------------------------------*/
/* FUN_0035a684 @ 0x0035a684   (est. sk_syscall_a684_stub)
 * Ghidra: void FUN_0035a684(void)
 * Empty exception-entry stub.
 * Confidence: medium */
void sk_syscall_a684_stub(void)
{
    /* no-op */
}

/*--------------------------------------------------------------------*/
/* FUN_0035a690 @ 0x0035a690   (est. sk_syscall_a690_add)
 * Ghidra: long FUN_0035a690(void)
 * Returns x22 + x24: sums two caller-saved registers. Address addition.
 * Confidence: low. */
uint64_t sk_syscall_a690_add(void)
{
    return 0x0 + 0x0;   /* unaff_x22 + unaff_x24 */
}

/*--------------------------------------------------------------------*/
/* FUN_0035a69c @ 0x0035a69c   (est. sk_syscall_a69c_stub)
 * Ghidra: void FUN_0035a69c(void)
 * Empty exception-entry stub.
 * Confidence: medium */
void sk_syscall_a69c_stub(void)
{
    /* no-op */
}

/*--------------------------------------------------------------------*/
/* FUN_0035a6a8 @ 0x0035a6a8   (est. sk_syscall_a6a8_stub)
 * Ghidra: void FUN_0035a6a8(void)
 * Empty exception-entry stub.
 * Confidence: medium */
void sk_syscall_a6a8_stub(void)
{
    /* no-op */
}

/*--------------------------------------------------------------------*/
/* FUN_0035a6b4 @ 0x0035a6b4   (est. sk_syscall_a6b4_stub)
 * Ghidra: void FUN_0035a6b4(void)
 * Empty exception-entry stub.
 * Confidence: medium */
void sk_syscall_a6b4_stub(void)
{
    /* no-op */
}

/*--------------------------------------------------------------------*/
/* FUN_0035a6c0 @ 0x0035a6c0   (est. sk_syscall_a6c0_stub)
 * Ghidra: void FUN_0035a6c0(void)
 * Empty exception-entry stub.
 * Confidence: medium */
void sk_syscall_a6c0_stub(void)
{
    /* no-op */
}

/*--------------------------------------------------------------------*/
/* FUN_0035a6d4 @ 0x0035a6d4   (est. sk_syscall_a6d4_stub)
 * Ghidra: void FUN_0035a6d4(void)
 * Empty exception-entry stub.
 * Confidence: medium */
void sk_syscall_a6d4_stub(void)
{
    /* no-op */
}

/*--------------------------------------------------------------------*/
/* FUN_0035a6e8 @ 0x0035a6e8   (est. sk_syscall_a6e8_stub)
 * Ghidra: void FUN_0035a6e8(void)
 * Empty exception-entry stub.
 * Confidence: medium */
void sk_syscall_a6e8_stub(void)
{
    /* no-op */
}

/*--------------------------------------------------------------------*/
/* FUN_0035a6f4 @ 0x0035a6f4   (est. sk_syscall_a6f4_stub)
 * Ghidra: void FUN_0035a6f4(void)
 * Empty exception-entry stub.
 * Confidence: medium */
void sk_syscall_a6f4_stub(void)
{
    /* no-op */
}

/*--------------------------------------------------------------------*/
/* FUN_0035a700 @ 0x0035a700   (est. sk_syscall_a700_stub)
 * Ghidra: void FUN_0035a700(void)
 * Empty exception-entry stub.
 * Confidence: medium */
void sk_syscall_a700_stub(void)
{
    /* no-op */
}

/*--------------------------------------------------------------------*/
/* FUN_0035a70c @ 0x0035a70c   (est. sk_syscall_a70c_stub)
 * Ghidra: void FUN_0035a70c(void)
 * Empty exception-entry stub.
 * Confidence: medium */
void sk_syscall_a70c_stub(void)
{
    /* no-op */
}

/*--------------------------------------------------------------------*/
/* FUN_0035a718 @ 0x0035a718   (est. sk_syscall_a718_stub)
 * Ghidra: void FUN_0035a718(void)
 * Empty exception-entry stub.
 * Confidence: medium */
void sk_syscall_a718_stub(void)
{
    /* no-op */
}

/*--------------------------------------------------------------------*/
/* FUN_0035a724 @ 0x0035a724   (est. sk_syscall_a724_stub)
 * Ghidra: void FUN_0035a724(void)
 * Empty exception-entry stub.
 * Confidence: medium */
void sk_syscall_a724_stub(void)
{
    /* no-op */
}

/*--------------------------------------------------------------------*/
/* FUN_0035a738 @ 0x0035a738   (est. sk_syscall_a738_stub)
 * Ghidra: void FUN_0035a738(void)
 * Empty exception-entry stub.
 * Confidence: medium */
void sk_syscall_a738_stub(void)
{
    /* no-op */
}

/*--------------------------------------------------------------------*/
/* FUN_0035a744 @ 0x0035a744   (est. sk_syscall_a744_set_flag)
 * Ghidra: void FUN_0035a744(long param_1)
 * Writes a byte value 1 into a table indexed by a 32-bit field at
 * (param_1 + 0x24), with base in caller-saved x19. Marks a slot/flag
 * as present in a per-index array.
 * Confidence: low.
 * Notes: unaff_x19 table base; index *(int *)(param_1 + 0x24). */
void sk_syscall_a744_set_flag(uint64_t param_1)
{
    uint8_t *table = (uint8_t *)0x0;   /* unaff_x19 */
    (void)table;
    /* *(undefined2 *)(unaff_x19 + *(int *)(param_1 + 0x24)) = 1; */
}

/*--------------------------------------------------------------------*/
/* FUN_0035a758 @ 0x0035a758   (est. sk_syscall_a758_pass)
 * Ghidra: undefined8 FUN_0035a758(undefined8 param_1)
 * Identity: returns its argument unchanged.
 * Confidence: medium. */
uint64_t sk_syscall_a758_pass(uint64_t arg)
{
    return arg;
}

/*--------------------------------------------------------------------*/
/* FUN_0035a76c @ 0x0035a76c   (est. sk_syscall_a76c_stub)
 * Ghidra: void FUN_0035a76c(void)
 * Empty exception-entry stub.
 * Confidence: medium */
void sk_syscall_a76c_stub(void)
{
    /* no-op */
}

/*--------------------------------------------------------------------*/
/* FUN_0035a778 @ 0x0035a778   (est. sk_syscall_a778_stub)
 * Ghidra: void FUN_0035a778(void)
 * Empty exception-entry stub.
 * Confidence: medium */
void sk_syscall_a778_stub(void)
{
    /* no-op */
}

/*--------------------------------------------------------------------*/
/* FUN_0035a784 @ 0x0035a784   (est. sk_syscall_a784_stub)
 * Ghidra: void FUN_0035a784(void)
 * Empty exception-entry stub.
 * Confidence: medium */
void sk_syscall_a784_stub(void)
{
    /* no-op */
}

/*--------------------------------------------------------------------*/
/* FUN_0035a798 @ 0x0035a798   (est. sk_syscall_a798_stub)
 * Ghidra: void FUN_0035a798(void)
 * Empty exception-entry stub.
 * Confidence: medium */
void sk_syscall_a798_stub(void)
{
    /* no-op */
}

/*--------------------------------------------------------------------*/
/* FUN_0035a7a4 @ 0x0035a7a4   (est. sk_syscall_a7a4_stub)
 * Ghidra: void FUN_0035a7a4(void)
 * Empty exception-entry stub.
 * Confidence: medium */
void sk_syscall_a7a4_stub(void)
{
    /* no-op */
}

/*--------------------------------------------------------------------*/
/* FUN_0035a7c0 @ 0x0035a7c0   (est. sk_syscall_a7c0_stub)
 * Ghidra: void FUN_0035a7c0(void)
 * Empty exception-entry stub.
 * Confidence: medium */
void sk_syscall_a7c0_stub(void)
{
    /* no-op */
}

/*--------------------------------------------------------------------*/
/* FUN_0035a7d4 @ 0x0035a7d4   (est. sk_syscall_a7d4_stub)
 * Ghidra: void FUN_0035a7d4(void)
 * Empty exception-entry stub.
 * Confidence: medium */
void sk_syscall_a7d4_stub(void)
{
    /* no-op */
}

/*--------------------------------------------------------------------*/
/* FUN_0035a7e8 @ 0x0035a7e8   (est. sk_syscall_a7e8_stub)
 * Ghidra: void FUN_0035a7e8(void)
 * Empty exception-entry stub.
 * Confidence: medium */
void sk_syscall_a7e8_stub(void)
{
    /* no-op */
}

/*--------------------------------------------------------------------*/
/* FUN_0035a7f4 @ 0x0035a7f4   (est. sk_syscall_a7f4_rawvalue_assert)
 * Ghidra: void FUN_0035a7f4(void)
 * Calls the counter/assert logger with the "rawValue" string and
 * operands (0xb, 1). Caller: FUN_002667a8. Likely a debug assert on a
 * raw capability value.
 * Confidence: medium
 * Notes: s__rawValue__005ce327 = "rawValue"; callee FUN_001a89a8. */
void sk_syscall_a7f4_rawvalue_assert(void)
{
    sk_count_log_001a89a8("rawValue", 0xb, 1);   /* FUN_001a89a8 */
}

/*--------------------------------------------------------------------*/
/* FUN_0035a808 @ 0x0035a808   (est. sk_syscall_a808_register)
 * Ghidra: void FUN_0035a808(void)
 * Registers function FUN_00656240 with argument &DAT_004e8098 via
 * FUN_00027614. Caller: FUN_0024cda8. A syscall handler / capability
 * method registration.
 * Confidence: low (artifact identities unknown).
 * Notes: FUN_00656240 code address; DAT_004e8098 data arg. */
void sk_syscall_a808_register(void)
{
    sk_register_00027614(sk_str_00656240, sk_tbl_004e8098);
    /* FUN_00027614(FUN_00656240, &DAT_004e8098) */
}

/*--------------------------------------------------------------------*/
/* FUN_0035a81c @ 0x0035a81c   (est. sk_syscall_a81c_dispatch_record)
 * Ghidra: void FUN_0035a81c(undefined8 param_1)
 * Builds a 4-word dispatch record into caller-saved object x22:
 *   +0x20 = param_1
 *   +0x28 = (in_x10 & 0xffffffffffff) | 0xd000000000000000   (tag 0xd cap)
 *   +0x30 = in_x9
 *   +0x38 = 0
 * then tail-calls the post-build dispatch helper FUN_0036986c.
 * Callers: FUN_001d0100, FUN_001d01f4. Marshals a capability/operation
 * descriptor with the 0xd<<60 type tag before dispatch.
 * Confidence: medium.
 * Notes: 0xd000000000000000 tag = capability type; callee FUN_0036986c. */
void sk_syscall_a81c_dispatch_record(uint64_t arg0)
{
    uint64_t *obj = (uint64_t *)0x0;   /* unaff_x22 */
    (void)obj;
    /* *(obj + 0x20) = arg0;
     * *(obj + 0x28) = (in_x10 & 0xffffffffffff) | 0xd000000000000000;
     * *(obj + 0x30) = in_x9;
     * *(obj + 0x38) = 0; */
    sk_dispatch_0036986c();            /* FUN_0036986c */
}

/*--------------------------------------------------------------------*/
/* FUN_0035a830 @ 0x0035a830   (est. sk_syscall_a830_register)
 * Ghidra: void FUN_0035a830(void)
 * Registers symbol &DAT_006575a0 with arg &DAT_004f1930 via
 * FUN_00002534. Syscall/capability handler registration pair.
 * Confidence: low (artifact identities unknown).
 * Notes: DAT_006575a0 string/symbol; DAT_004f1930 data arg. */
void sk_syscall_a830_register(void)
{
    sk_register_00002534(sk_str_006575a0, sk_tbl_004f1930);
    /* FUN_00002534(&DAT_006575a0, &DAT_004f1930) */
}

/*--------------------------------------------------------------------*/
/* FUN_0035a844 @ 0x0035a844   (est. sk_syscall_a844_panic)
 * Ghidra: void FUN_0035a844(void)
 * Calls the noreturn abort/panic FUN_001afa84; does not return.
 * Callers: FUN_002e62f0, FUN_002e6330. Invoked on an unrecoverable
 * error path.
 * Confidence: medium.
 * Notes: callee FUN_001afa84 is noreturn. */
void sk_syscall_a844_panic(void)
{
    sk_panic_001afa84();   /* FUN_001afa84 (noreturn) */
}

/*--------------------------------------------------------------------*/
/* FUN_0035a858 @ 0x0035a858   (est. sk_syscall_a858_dispatch)
 * Ghidra: void FUN_0035a858(void)
 * Thin wrapper: tail-calls the no-arg helper FUN_001a983c. Callers:
 * FUN_001a9b28, FUN_001a9b8c.
 * Confidence: medium.
 * Notes: out-of-slice callee FUN_001a983c. */
void sk_syscall_a858_dispatch(void)
{
    sk_helper_001a983c();   /* FUN_001a983c */
}

/*--------------------------------------------------------------------*/
/* FUN_0035a86c @ 0x0035a86c   (est. sk_syscall_a86c_dispatch)
 * Ghidra: void FUN_0035a86c(void)
 * Thin wrapper: tail-calls helper FUN_001d9840(1). Caller: FUN_001cc9c8.
 * Confidence: medium.
 * Notes: out-of-slice callee FUN_001d9840. */
void sk_syscall_a86c_dispatch(void)
{
    sk_helper_001d9840(1);   /* FUN_001d9840(1) */
}

/*--------------------------------------------------------------------*/
/* FUN_0035a880 @ 0x0035a880   (est. sk_syscall_a880_register)
 * Ghidra: void FUN_0035a880(void)
 * Registers symbol &DAT_00657588 with arg &DAT_004f1918 via
 * FUN_00002534. Syscall/capability handler registration pair.
 * Confidence: low (artifact identities unknown).
 * Notes: DAT_00657588 string/symbol; DAT_004f1918 data arg. */
void sk_syscall_a880_register(void)
{
    sk_register_00002534(sk_str_00657588, sk_tbl_004f1918);
    /* FUN_00002534(&DAT_00657588, &DAT_004f1918) */
}

/*--------------------------------------------------------------------*/
/* FUN_0035a894 @ 0x0035a894   (est. sk_syscall_a894_panic)
 * Ghidra: void FUN_0035a894(void)
 * Calls the noreturn abort/panic FUN_001afa84; does not return.
 * Invoked on an unrecoverable error path.
 * Confidence: medium.
 * Notes: callee FUN_001afa84 is noreturn. */
void sk_syscall_a894_panic(void)
{
    sk_panic_001afa84();   /* FUN_001afa84 (noreturn) */
}

/*--------------------------------------------------------------------*/
/* FUN_0035a8a8 @ 0x0035a8a8   (est. sk_syscall_a8a8_count_assert)
 * Ghidra: void FUN_0035a8a8(void)
 * Calls the counter/assert logger with the "__count" string and
 * operands (9, 1). Callers: FUN_003202a0, FUN_003215b8. Likely a debug
 * count consistency assert.
 * Confidence: medium
 * Notes: s___count__005d2d90 = "__count"; callee FUN_001a89a8. */
void sk_syscall_a8a8_count_assert(void)
{
    sk_count_log_001a89a8("__count", 9, 1);   /* FUN_001a89a8 */
}

/*--------------------------------------------------------------------*/
/* FUN_0035a8bc @ 0x0035a8bc   (est. sk_syscall_a8bc_invoke)
 * Ghidra: void FUN_0035a8bc(undefined8 param_1,undefined8 param_2,
 *        undefined8 param_3)
 * Spills the three arguments into the frame and tail-calls the 2-arg
 * capability invoke helper FUN_002a9ba8(param_2, param_3). Callers:
 * FUN_0029f00c, FUN_0029f764.
 * Confidence: medium.
 * Notes: out-of-slice callee FUN_002a9ba8. */
void sk_syscall_a8bc_invoke(uint64_t a, uint64_t b, uint64_t c)
{
    /* *(undefined8 *)(unaff_x29 + -0x18) = a; */
    sk_invoke_002a9ba8(b, c);   /* FUN_002a9ba8(param_2, param_3) */
}
