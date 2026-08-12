/* Recreated from exclavecore_bundle.t8142.RELEASE.im4p (cL4 Secure Kernel,
 * arm64e, image base 0) — the cL4 microkernel (GL1), "cL4 (679.100.61)".
 * Ground truth: Ghidra FUN_ names + addresses in program cl4_kernel.raw.
 * This region (0x39fcc4-0x3a68a4) is a cL4 kernel-object dispatch layer: the
 * bodies are selector-based dispatchers (the first word of the object selects
 * a handler), plumbing between the capability/object stores at 0x67b0a8 /
 * 0x67c068 / 0x67c0d0 / 0x67c1c8 / 0x67c230, and small object/service helpers.
 * All names are estimates unless string-matched. */
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdbool.h>

/* cL4 returns many values as a 16-byte pair (two 64-bit words in x0/x1).
 * Model it as a struct so callers can carry both halves. */
typedef struct { unsigned long lo, hi; } cL4_w16_t;

/* SoftwareBreakpoint(1, addr) fail-closed trap (brk #1). */
#define CL4_SW_BP(addr)  __asm__ volatile("brk #1" ::: "memory")

/* ------------------------------------------------------------------ *
 * Extern declarations for callees outside this region and forward
 * declarations for in-region callees (signatures from the bodies).
 * ------------------------------------------------------------------ */

typedef void (*fn_void)(void);
typedef unsigned int *(*sk_obj_emit_fn)(long *, unsigned char *, unsigned int *, unsigned int *, unsigned int **);
static const char s_alloc_failed[] = "Allocation failed";
static const char s_smallvec_overflow[] = "SmallVector capacity overflow during allocation";
static const char s_smallvec_unable[] = "SmallVector capacity unable to grow";
static const char s_log_fmt[] = "%.*s: file %.*s, line %u, column %u";

/* Globals referenced by the bodies (Ghidra DAT_ refs renamed; extern here). */
extern unsigned long sizeofcmds;
extern long g_lock_state;              /* _DAT_006c0b18 */
extern unsigned long g_log_enabled;    /* DAT_006c0b10 */
extern unsigned long __thread_vars;    /* Ghidra TLS-variable artifact */
extern void cL4_runtime_fatal(void);

/* callees outside this region */
extern unsigned long FUN_003766b4();
extern unsigned long FUN_00374de4();
extern unsigned long FUN_00374d80();
extern unsigned long FUN_003743d0();
extern unsigned long FUN_0036a358();
extern unsigned int FUN_0000456c();
extern long FUN_00019850();
extern unsigned long FUN_00118cf8();
extern unsigned long thunk_FUN_00115080();
extern void FUN_003bd1f4();
extern void thunk_FUN_00012568();
extern long thunk_FUN_00114c60();
extern long FUN_000101a0();
extern void FUN_00117cc8();
extern int FUN_00116bb4();
extern unsigned long FUN_0035bd48();
extern void FUN_00361528();
extern void FUN_0037d1d8();
extern unsigned long FUN_003895e0();
extern void FUN_0036805c();
extern void FUN_003680cc();
extern void FUN_0011d7e8();
extern void FUN_003d3dd8();
extern void FUN_004b9e2c();
extern unsigned long FUN_00111890();
extern void FUN_0036b118();
extern void FUN_003766fc();
extern void FUN_004b9ed8();
extern long FUN_0036b8b0();
extern void FUN_0036b5c4();
extern void FUN_00117cc4();
extern cL4_w16_t FUN_0036aae4();
extern unsigned long FUN_0036b250();
extern int FUN_0006e064();
extern cL4_w16_t FUN_0036f878();
extern unsigned long *FUN_00369b18(unsigned long a, unsigned long b, unsigned long c);
extern void FUN_0036b2d0();
extern void *FUN_000102f4(void *ptr, unsigned long size, unsigned long tag);
extern void FUN_0037e58c();
extern void FUN_0037e614();
extern void FUN_0037eb4c();
extern void FUN_0037e8e8();
extern void FUN_004ba3a8();
extern void FUN_0036b340();
extern void FUN_004b9ccc();
extern int FUN_00369b0c();
extern void thunk_FUN_00369b04();
extern void FUN_004b9d68();
extern void FUN_00362ea4();
extern void FUN_0037364c();
extern void FUN_003bc9a4();
extern void FUN_003d2b40();
extern unsigned long FUN_004ba5a4();
extern int thunk_FUN_001145b0();
extern void FUN_003b0f48();
extern void FUN_003b0b7c();
extern long FUN_003b0e1c();
extern unsigned long FUN_00365660();
extern int FUN_003b0ec4();
extern void FUN_003b0fb8();
extern unsigned long DAT_004f2748;
extern void FUN_003ad810();
extern void FUN_00363f70();
extern void FUN_003ac394();
extern long FUN_003ad478();
extern void FUN_003a6c28();
extern void FUN_003a75e4();
extern void FUN_003a7818();
extern void FUN_003a7d9c();
extern void FUN_003a81e8();
extern void FUN_003a8868();
extern void FUN_003a8ab4();
extern void FUN_003a9944();
extern void FUN_003aa804();
extern unsigned long FUN_003ab218();
extern void FUN_003ab40c();
extern void FUN_003ab780();
extern void FUN_003ab7f4();
extern void FUN_003abad0();
extern void FUN_003ab948();
extern long FUN_003b02dc();
extern long FUN_003abc48();
extern void FUN_003abd1c();
extern void FUN_003abef0();
extern void FUN_003abf88();
extern long FUN_003ac2d0();
extern unsigned long FUN_003b05c8();
extern void FUN_003b03c0();
extern unsigned long FUN_003ac580();
extern unsigned long FUN_003ac430();
extern unsigned long FUN_003ac4a4();
extern unsigned long FUN_003acd3c();
extern unsigned long FUN_003acda0();
extern unsigned long FUN_003ace50();
extern unsigned long FUN_003ace08();
extern unsigned long FUN_003acefc();
extern unsigned long FUN_003acfb4();
extern unsigned long FUN_003ad724();
extern unsigned long FUN_003ad874();
extern unsigned long FUN_003ad5a4();
extern unsigned long FUN_003ad61c();
extern unsigned long FUN_003ad560();
extern unsigned long FUN_003bed8c();

/* forward declarations for in-region bodies */
unsigned long FUN_0039fcc4(unsigned long *tag_ptr);
unsigned long FUN_0039fcd8(unsigned long arg_a, unsigned long *tag_ptr, unsigned long arg_b);
unsigned long FUN_0039ff2c(unsigned long *obj_in);
unsigned long FUN_003a017c(unsigned long *param_1, unsigned long param_2, unsigned long *param_3);
unsigned long FUN_003a0440(unsigned long *obj_in, unsigned long param_2);
void FUN_003a0690(unsigned long param_1, unsigned long param_2, unsigned long *param_3, unsigned long param_4, unsigned long param_5, unsigned long param_6, unsigned long param_7);
unsigned long FUN_003a0968(unsigned long param_1, unsigned long param_2);
unsigned long FUN_003a0b04(unsigned long param_1, unsigned long param_2);
char *FUN_003a0c90(unsigned long *tag_ptr);
unsigned long FUN_003a0dec(void);
unsigned long FUN_003a0e44(unsigned long param_1);
cL4_w16_t FUN_003a0ed4(unsigned long *param_1, unsigned long *param_2);
unsigned long FUN_003a0fcc(unsigned long *param_1);
cL4_w16_t FUN_003a1098(long param_1, unsigned long param_2, long *param_3, unsigned long *param_4);
void FUN_003a11c0(unsigned long *param_1, long *param_2, unsigned long param_3, unsigned long param_4, unsigned long param_5);
void FUN_003a12d8(long *obj);
void FUN_003a1310(long *param_1);
unsigned int FUN_003a13c4(long param_1);
unsigned int FUN_003a1480(long param_1, unsigned long param_2);
cL4_w16_t FUN_003a1518(long param_1, unsigned long param_2, unsigned long *param_3, unsigned long *param_4);
void FUN_003a156c(unsigned long *param_1, long *param_2, unsigned long param_3);
void FUN_003a160c(long *param_1, unsigned long param_2, unsigned long param_3);
void FUN_003a18c8(unsigned long param_1);
void FUN_003a1958(long param_1);
void FUN_003a1a18(long param_1);
void FUN_003a1ae4(long param_1);
void FUN_003a1b0c(unsigned long *param_1, long *param_2, long *param_3, unsigned long param_4);
bool FUN_003a1cbc(long param_1);
void FUN_003a1dac(unsigned long *param_1, long param_2, unsigned long param_3, unsigned long *param_4, unsigned long *param_5);
unsigned long FUN_003a1f60(long param_1);
unsigned int FUN_003a2044(long obj);
unsigned long FUN_003a20cc(long param_1, unsigned long index);
cL4_w16_t FUN_003a21a0(long param_1, unsigned long param_2, unsigned long *param_3, unsigned long *param_4);
void FUN_003a21f4(unsigned long param_1, long *param_2, unsigned long param_3);
long FUN_003a2290(long *obj);
void FUN_003a232c(long *obj, long amount);
void FUN_003a23b4(long *obj, long amount, unsigned long param_3, unsigned long param_4);
bool FUN_003a2468(long obj);
void FUN_003a24d0(long *out, long obj);
void FUN_003a2554(void);
unsigned long FUN_003a2578(unsigned long param_1);
unsigned long FUN_003a25a0(unsigned long *param_1);
unsigned long FUN_003a25b8(unsigned long *param_1);
void FUN_003a25d4(unsigned long param_1);
unsigned long FUN_003a25e0(unsigned long param_1);
void FUN_003a2610(unsigned long p);
bool FUN_003a261c(long p);
bool FUN_003a265c(long p);
bool FUN_003a26a0(unsigned long p);
unsigned long FUN_003a26e8(long obj);
void FUN_003a27f0(unsigned long *out);
cL4_w16_t FUN_003a2898(long p);
void FUN_003a28a8(void);
void FUN_003a28ac(unsigned long arg1, unsigned long arg2, unsigned long arg3, unsigned long fmt);
unsigned long FUN_003a28e8(unsigned long param_1, long param_2);
void FUN_003a294c(unsigned long *buf, long static_buf, unsigned long req_cap, long elem_size);
void FUN_003a2a38(unsigned long *buf, long static_buf, unsigned long req_cap, long elem_size);
void FUN_003a2b38(long src, long len);
unsigned long * FUN_003a2c18(unsigned long *out);
long * FUN_003a2cf0(long *obj);
unsigned long FUN_003a2d38(unsigned long *param_1, unsigned long param_2, unsigned long param_3);
void FUN_003a2da8(unsigned long *param_1, unsigned long *param_2, unsigned long param_3, unsigned long param_4, unsigned long param_5);
void FUN_003a2e9c(unsigned long *param_1, unsigned long param_2, unsigned long param_3, unsigned long param_4);
cL4_w16_t FUN_003a2fd4(unsigned long param_1, unsigned long param_2, unsigned long param_3);
unsigned long FUN_003a3040(unsigned int param_1);
unsigned long FUN_003a3124(int param_1);
void FUN_003a31d8(unsigned char *param_1);
unsigned long FUN_003a3224(unsigned long param_1, unsigned long param_2);
unsigned long FUN_003a32a0(long param_1, unsigned long param_2, unsigned long param_3, unsigned long param_4);
void FUN_003a3380(unsigned long *param_1);
unsigned long FUN_003a33cc(long *param_1);
void FUN_003a3430(unsigned long param_1, unsigned short param_2);
void FUN_003a3460(unsigned int *param_1, long param_2, unsigned long param_3);
void FUN_003a3578(long param_1, long *param_2, unsigned int *param_3, unsigned long param_4);
void FUN_003a3628(long *param_1, unsigned int param_2);
void FUN_003a36a0(long *param_1, unsigned int param_2, long param_3);
void FUN_003a36d8(unsigned char (*param_1)[16], unsigned long param_2);
unsigned short *FUN_003a3748(unsigned short *param_1, unsigned long param_2, int param_3);
void FUN_003a3814(long *param_1);
unsigned long FUN_003a3898(unsigned long param_1, unsigned long param_2);
void FUN_003a3944(unsigned long param_1, unsigned short param_2, unsigned long param_3);
void FUN_003a3980(unsigned long param_1, unsigned short param_2, unsigned long param_3, unsigned long param_4);
void FUN_003a39c8(unsigned long param_1, unsigned short param_2, unsigned long *param_3);
long *FUN_003a3a10(unsigned long param_1, unsigned short param_2, long param_3);
void FUN_003a3a70(long *param_1, unsigned long param_2, long param_3, unsigned long param_4);
void FUN_003a3aec(long param_1, long *param_2, unsigned int *param_3, unsigned long param_4);
void FUN_003a3b9c(long *param_1, unsigned long param_2, unsigned long param_3);
void FUN_003a3c20(long *param_1, unsigned long param_2, unsigned long param_3);
long *FUN_003a3d18(long *param_1, long param_2, unsigned long param_3, unsigned long param_4, unsigned long param_5);
long *FUN_003a3de4(long *param_1);
long FUN_003a3e54(long param_1, short *param_2, unsigned long param_3, unsigned long param_4);
unsigned long FUN_003a4094(long param_1);
unsigned long FUN_003a4110(long param_1, int (*param_2)(unsigned short));
long FUN_003a4180(long param_1);
long FUN_003a4b38(unsigned long param_1, unsigned short param_2, long param_3);
long FUN_003a4b98(unsigned long param_1, unsigned short param_2, long param_3, long param_4);
long FUN_003a4c14(unsigned long param_1, unsigned short param_2, long p3, long p4, long p5);
long FUN_003a4ca8(unsigned long param_1, unsigned short param_2, long p3, long p4, long p5, long p6);
unsigned long *FUN_003a4d5c(unsigned long param_1, unsigned long *param_2, unsigned short param_3);
long FUN_003a4ea4(long param_1);
long FUN_003a4f5c(long param_1, long *param_2);
long FUN_003a5518(long param_1, int param_2);
long FUN_003a56a0(long param_1);
unsigned long FUN_003a58b0(long param_1);
unsigned long *FUN_003a5908(long param_1);
unsigned long FUN_003a599c(unsigned long *param_1);
unsigned long FUN_003a5aa0(unsigned long *param_1);
long FUN_003a6090(unsigned long *param_1, unsigned long param_2);
long FUN_003a613c(unsigned long *param_1);
void FUN_003a61d8(unsigned long *param_1);
long FUN_003a62f8(unsigned long *param_1);
void FUN_003a63d8(unsigned long *param_1);
void FUN_003a644c(unsigned long *param_1);
void FUN_003a64f0(unsigned long *param_1);
void FUN_003a6560(unsigned long *param_1);
void FUN_003a65d4(unsigned long *param_1);
long FUN_003a663c(unsigned long *param_1);
long FUN_003a672c(unsigned long *param_1);
void FUN_003a6874(unsigned long *param_1, unsigned long param_2);
unsigned long *FUN_003a68a4(unsigned long *param_1);

/* FUN_0039fcc4 @ 0x0039fcc4   (est. read_syscall_tag)
 * Ghidra: ulong FUN_0039fcc4(ulong *param_1)
 * Reads the 32-bit message tag word at *param_1. If the tag value is below 0x800 it
 * returns the value masked to 32 bits, otherwise returns 0. No side effects.
 * Confidence: high
 * Notes: none (no SW_BP, no string refs). */
unsigned long FUN_0039fcc4(unsigned long *tag_ptr)
{
    unsigned long ret = 0;
    if (*tag_ptr < 0x800) {
        ret = *tag_ptr & 0xffffffff;
    }
    return ret;
}
/* FUN_0039fcd8 @ 0x0039fcd8   (est. sk_syscall_dispatch_r)
 * Ghidra: ulong FUN_0039fcd8(undefined8 param_1,ulong *param_2,undefined8 param_3)
 * Message-tag dispatcher. Resolves a (msg,tag) pair via FUN_003a0ed4, overrides the
 * object with param_2 when non-null, then dispatches on the tag: 0x201/0x202 route to
 * FUN_003a1cbc, 0x200 to FUN_003a13c4, 0x300 validates the object is the special
 * 0x67b0a8 root and a range check, 0x301 returns obj[1]; unknown tags fall to a common
 * handler FUN_003a2044 at 0x67c230; invalid/unsupported tags trap. Returns a status.
 * Confidence: medium
 * Notes: SW_BP trap at 0x39fd58 (fail-closed). Handler tables at literal 0x67c1c8 /
 * 0x67c0d0 / 0x67c230. Walk loop over FUN_003a25a0 when param_2==0. */
unsigned long FUN_0039fcd8(unsigned long arg_a, unsigned long *tag_ptr, unsigned long arg_b)
{
    unsigned long *slot;
    long node;
    long *nptr;
    int tag;
    unsigned long *obj;
    unsigned long *msg_hi;
    cL4_w16_t pair;
    unsigned long addr_slot;

    pair = FUN_003a0ed4((unsigned long *)arg_b, (unsigned long *)arg_a);
    msg_hi = (unsigned long *)pair.hi;
    obj = (unsigned long *)pair.lo;
    if (tag_ptr != (unsigned long *)0x0) {
        obj = tag_ptr;
    }
    tag = 0;
    if (*obj < 0x800) {
        tag = (int)*obj;
    }

    if (tag < 0x203) {
        if (tag - 0x201U < 2) {
            addr_slot = 0x67c1c8;
            return FUN_003a1cbc((long)&addr_slot);
        }
        if (tag != 0) {
            if (tag != 0x200) {
                return 0;
            }
            addr_slot = 0x67c0d0;
            return FUN_003a13c4((long)&addr_slot);
        }
    } else if (tag < 0x301) {
        if (tag != 0x203) {
            if (tag != 0x300) {
                return 0;
            }
            if ((obj != (unsigned long *)0x67b0a8) ||
                (0xfffffffffffff800 < **(long **)*msg_hi - 0x800U)) {
                return 0;
            }
            if (tag_ptr == (unsigned long *)0x0) {
                node = FUN_003a25a0((unsigned long *)0);
                while ((*(long *)(node + 0x28) == 0 || (*(long *)(node + 0x28) == 0))) {
                    nptr = (long *)(node + 8);
                    node = 0;
                    if (*nptr != 0) {
                        node = *nptr;
                    }
                }
            }
            slot = (unsigned long *)0x67b0a8;
            obj = (unsigned long *)0x67b0a8;
            goto common;
        }
    } else {
        if (tag < 0x305) {
            if (tag != 0x301) {
                return 0;
            }
            return obj[1];
        }
        if (tag != 0x305) {
            if ((1 < tag - 0x500U) && (tag != 0x400)) {
                return 0;
            }
            /* noreturn fail-closed trap (brk #1) */
            CL4_SW_BP(0x39fd58);
            return 0; /* unreachable */
        }
    }

    if (tag_ptr == (unsigned long *)0x0) {
        node = FUN_003a25a0((unsigned long *)*msg_hi);
        while ((*(long *)(node + 0x28) == 0 || (*(long *)(node + 0x28) == 0))) {
            nptr = (long *)(node + 8);
            node = 0;
            if (*nptr != 0) {
                node = *nptr;
            }
        }
    }
    slot = &addr_slot;
common:
    addr_slot = 0x67c230;
    return FUN_003a2044((long)slot);
}
/* FUN_0039ff2c @ 0x0039ff2c   (est. sk_syscall_dispatch2)
 * Ghidra: ulong FUN_0039ff2c(ulong *param_1)
 * Sibling dispatcher to FUN_0039fcd8 (same tag-switch skeleton) but its common fallback
 * handler is FUN_003a2290 and it takes only the object pointer. 0x201/0x202 route to
 * FUN_003a1cbc, 0x200 to FUN_003a13c4, 0x300 validates the 0x67b0a8 root + range check,
 * 0x301 returns obj[1]; unsupported tags trap. Returns a status.
 * Confidence: medium
 * Notes: SW_BP trap at 0x39ffa8. Handler tables at 0x67c1c8 / 0x67c0d0 / 0x67c230. */
unsigned long FUN_0039ff2c(unsigned long *obj_in)
{
    unsigned long *slot;
    long node;
    long *nptr;
    int tag;
    unsigned long *obj;
    unsigned long *msg_hi;
    cL4_w16_t pair;
    unsigned long addr_slot;

    pair = FUN_003a0ed4((unsigned long *)obj_in, (unsigned long *)0);
    msg_hi = (unsigned long *)pair.hi;
    obj = (unsigned long *)pair.lo;
    if (obj_in != (unsigned long *)0x0) {
        obj = obj_in;
    }
    tag = 0;
    if (*obj < 0x800) {
        tag = (int)*obj;
    }

    if (tag < 0x203) {
        if (tag - 0x201U < 2) {
            addr_slot = 0x67c1c8;
            return FUN_003a1cbc((long)&addr_slot);
        }
        if (tag != 0) {
            if (tag != 0x200) {
                return 0;
            }
            addr_slot = 0x67c0d0;
            return FUN_003a13c4((long)&addr_slot);
        }
    } else if (tag < 0x301) {
        if (tag != 0x203) {
            if (tag != 0x300) {
                return 0;
            }
            if ((obj != (unsigned long *)0x67b0a8) ||
                (0xfffffffffffff800 < **(long **)*msg_hi - 0x800U)) {
                return 0;
            }
            if (obj_in == (unsigned long *)0x0) {
                node = FUN_003a25a0((unsigned long *)0);
                while ((*(long *)(node + 0x28) == 0 || (*(long *)(node + 0x28) == 0))) {
                    nptr = (long *)(node + 8);
                    node = 0;
                    if (*nptr != 0) {
                        node = *nptr;
                    }
                }
            }
            slot = (unsigned long *)0x67b0a8;
            obj = (unsigned long *)0x67b0a8;
            goto common;
        }
    } else {
        if (tag < 0x305) {
            if (tag != 0x301) {
                return 0;
            }
            return obj[1];
        }
        if (tag != 0x305) {
            if ((1 < tag - 0x500U) && (tag != 0x400)) {
                return 0;
            }
            /* noreturn fail-closed trap (brk #1) */
            CL4_SW_BP(0x39ffa8);
            return 0; /* unreachable */
        }
    }

    if (obj_in == (unsigned long *)0x0) {
        node = FUN_003a25a0((unsigned long *)*msg_hi);
        while ((*(long *)(node + 0x28) == 0 || (*(long *)(node + 0x28) == 0))) {
            nptr = (long *)(node + 8);
            node = 0;
            if (*nptr != 0) {
                node = *nptr;
            }
        }
    }
    slot = &addr_slot;
common:
    addr_slot = 0x67c230;
    return FUN_003a2290((long *)slot);
}
/* FUN_003a017c @ 0x003a017c   (est. sk_syscall_dispatch_w)
 * Ghidra: undefined8 FUN_003a017c(ulong *param_1,undefined8 param_2,undefined8 *param_3)
 * Message-tag dispatcher that fills a caller-supplied result record at param_3.
 * 0x201/0x202 store a 1 into the result type word and return 0; 0x200 fills the record
 * from FUN_003a160c; 0x300 validates the 0x67b0a8 root + range check then routes to
 * FUN_003a23b4; 0x301 routes to FUN_003a1098; unsupported tags trap. On return the
 * epilogue writes result-status bits (flags) into the record at offsets 16/17.
 * Confidence: medium
 * Notes: SW_BP traps at 0x3a01fc, 0x3a0438, 0x3a0440. FUN_003a160c fills the 8-byte
 * local_60 plus a 3-byte local_48 field (modelled as separate locals). Result record
 * at param_3: [0]=value, [1]=aux, [2]=flags (16-bit), +0x11 = one status bit. */
unsigned long FUN_003a017c(unsigned long *param_1, unsigned long param_2, unsigned long *param_3)
{
    unsigned char bv1;
    unsigned long *pu5;
    int iv6;
    unsigned long *pu7;
    cL4_w16_t av8;
    unsigned long loc60;
    unsigned long *puStack_58;
    unsigned long loc50 = 0; /* return slot (uninitialized in the 0x200 decompile path) */
    unsigned int loc48 = 0;  /* 3-byte field filled by FUN_003a160c */
    long node;
    long *nptr;

    av8 = FUN_003a0ed4((unsigned long *)param_1, (unsigned long *)0);
    pu5 = (unsigned long *)av8.hi;
    puStack_58 = (unsigned long *)av8.lo;
    if (param_1 != (unsigned long *)0x0) {
        puStack_58 = param_1;
    }
    iv6 = 0;
    if (*puStack_58 < 0x800) {
        iv6 = (int)*puStack_58;
    }

    if (iv6 < 0x203) {
        if (iv6 - 0x201U < 2) {
            *(unsigned short *)(param_3 + 2) = 1;
            return 0;
        }
        if (iv6 != 0) {
            if (iv6 != 0x200) {
                goto LAB_003a0434;
            }
            FUN_003a160c((long *)&loc60, (unsigned long)puStack_58, (unsigned long)param_2);
            *param_3 = loc60;
            param_3[1] = 0;
            *(unsigned char *)(param_3 + 2) = (loc48 < 0x10000);
            bv1 = (unsigned char)(loc48 >> 8);
            goto LAB_003a03d0;
        }
LAB_003a02e8:
        if (param_1 == (unsigned long *)0x0) {
            node = FUN_003a25a0((unsigned long *)*pu5);
            while ((*(long *)(node + 0x28) == 0 || (*(long *)(node + 0x28) == 0))) {
                nptr = (long *)(node + 8);
                node = 0;
                if (*nptr != 0) {
                    node = *nptr;
                }
            }
        }
        pu7 = &loc60;
LAB_003a030c:
        loc60 = 0x67c230;
        loc50 = (unsigned long)pu5;
        FUN_003a23b4((long *)pu7, (long)&loc60, (unsigned long)param_2, (unsigned long)param_3);
        av8.lo = 0;
        av8.hi = 0;
    } else {
        if (iv6 < 0x301) {
            if (iv6 == 0x203) {
                goto LAB_003a02e8;
            }
            if (((iv6 != 0x300) || (puStack_58 != (unsigned long *)0x67b0a8)) ||
                (0xfffffffffffff800 < **(long **)*pu5 - 0x800U)) {
                goto LAB_003a0434;
            }
            if (param_1 == (unsigned long *)0x0) {
                node = FUN_003a25a0((unsigned long *)0);
                while ((*(long *)(node + 0x28) == 0 || (*(long *)(node + 0x28) == 0))) {
                    nptr = (long *)(node + 8);
                    node = 0;
                    if (*nptr != 0) {
                        node = *nptr;
                    }
                }
            }
            pu7 = (unsigned long *)0x67b0a8;
            puStack_58 = (unsigned long *)0x67b0a8;
            goto LAB_003a030c;
        }
        if (0x304 < iv6) {
            if (0x305 < iv6) {
                if ((1 < iv6 - 0x500U) && (iv6 != 0x306)) {
                    /* noreturn fail-closed trap (brk #1) */
                    CL4_SW_BP(0x3a01fc);
                    return 0; /* unreachable */
                }
LAB_003a0434:
                /* noreturn fail-closed trap (brk #1) */
                CL4_SW_BP(0x3a0438);
                return 0; /* unreachable */
            }
            goto LAB_003a02e8;
        }
        if (iv6 != 0x301) {
            /* noreturn fail-closed trap (brk #1) */
            CL4_SW_BP(0x3a0440);
            return 0; /* unreachable */
        }
        loc60 = 0x67c068;
        loc50 = (unsigned long)pu5;
        av8 = FUN_003a1098((long)&loc60, (unsigned long)&loc60, (long *)param_2, (unsigned long *)param_3);
    }

    loc50 = av8.lo;
    *(unsigned char *)(param_3 + 2) = (av8.hi & 0xff0000) == 0;
    bv1 = ((unsigned char *)&av8)[9];
LAB_003a03d0:
    *(unsigned char *)((unsigned long)param_3 + 0x11) = bv1 & 1;
    return loc50;
}
/* FUN_003a0440 @ 0x003a0440   (est. sk_syscall_dispatch_idx)
 * Ghidra: ulong FUN_003a0440(ulong *param_1,ulong param_2)
 * Tag dispatcher with indexed access: 0x201/0x202 return 0, 0x200 routes to FUN_003a1480,
 * 0x300 validates the 0x67b0a8 root + range check, 0x301 returns obj[(param_2&0xffffffff)*2+4]
 * when param_2 is within [0, obj[1]]; 0x203/0x305 and tag 0 fall to the common handler
 * FUN_003a232c at 0x67c230. Unsupported tags trap. Returns a status/indexed value.
 * Confidence: medium
 * Notes: SW_BP traps at 0x3a0690, 0x3a0688, 0x3a04bc. Handler table at 0x67c0d0 / 0x67c230. */
unsigned long FUN_003a0440(unsigned long *obj_in, unsigned long param_2)
{
    long node;
    long *nptr;
    int iv5;
    unsigned long *pu6;
    cL4_w16_t av7;
    unsigned long loc58;
    unsigned long *puStack_50;
    unsigned long *loc48;

    av7 = FUN_003a0ed4((unsigned long *)obj_in, (unsigned long *)0);
    loc48 = (unsigned long *)av7.hi;
    puStack_50 = (unsigned long *)av7.lo;
    if (obj_in != (unsigned long *)0x0) {
        puStack_50 = obj_in;
    }
    iv5 = 0;
    if (*puStack_50 < 0x800) {
        iv5 = (int)*puStack_50;
    }

    if (iv5 < 0x203) {
        if (iv5 - 0x201U < 2) {
            return 0;
        }
        if (iv5 != 0) {
            if (iv5 == 0x200) {
                loc58 = 0x67c0d0;
                return FUN_003a1480((long)&loc58, (unsigned long)&loc58);
            }
            goto LAB_003a0684;
        }
    } else if (iv5 < 0x301) {
        if (iv5 != 0x203) {
            if (((iv5 != 0x300) || (puStack_50 != (unsigned long *)0x67b0a8)) ||
                (0xfffffffffffff800 < **(long **)*loc48 - 0x800U)) {
                goto LAB_003a0684;
            }
            if (obj_in == (unsigned long *)0x0) {
                node = FUN_003a25a0((unsigned long *)0);
                while ((*(long *)(node + 0x28) == 0 || (*(long *)(node + 0x28) == 0))) {
                    nptr = (long *)(node + 8);
                    node = 0;
                    if (*nptr != 0) {
                        node = *nptr;
                    }
                }
            }
            pu6 = (unsigned long *)0x67b0a8;
            puStack_50 = (unsigned long *)0x67b0a8;
            goto LAB_003a05a4;
        }
    } else {
        if (iv5 < 0x305) {
            if (iv5 != 0x301) {
                /* noreturn fail-closed trap (brk #1) */
                CL4_SW_BP(0x3a0690);
                return 0; /* unreachable */
            }
            if ((-1 < (long)param_2) && (param_2 <= puStack_50[1])) {
                return puStack_50[(param_2 & 0xffffffff) * 2 + 4];
            }
LAB_003a0684:
            /* noreturn fail-closed trap (brk #1) */
            CL4_SW_BP(0x3a0688);
            return 0; /* unreachable */
        }
        if (0x305 < iv5) {
            if ((1 < iv5 - 0x500U) && (iv5 != 0x306)) {
                /* noreturn fail-closed trap (brk #1) */
                CL4_SW_BP(0x3a04bc);
                return 0; /* unreachable */
            }
            goto LAB_003a0684;
        }
    }

    if (obj_in == (unsigned long *)0x0) {
        node = FUN_003a25a0((unsigned long *)*loc48);
        while ((*(long *)(node + 0x28) == 0 || (*(long *)(node + 0x28) == 0))) {
            nptr = (long *)(node + 8);
            node = 0;
            if (*nptr != 0) {
                node = *nptr;
            }
        }
    }
    pu6 = &loc58;
LAB_003a05a4:
    loc58 = 0x67c230;
    FUN_003a232c((long *)pu6, (long)&loc58);
    return 0;
}
/* FUN_003a0690 @ 0x003a0690   (est. sk_syscall_dispatch_v)
 * Ghidra: void FUN_003a0690(undefined8 param_1,undefined8 param_2,ulong *param_3,undefined8 param_4,undefined8 param_5,undefined8 param_6,undefined8 param_7)
 * Void tag dispatcher. 0x201/0x202 route to FUN_003a1dac, 0x200 to FUN_003a156c,
 * 0x301 to FUN_003a11c0, 0x300 validates the 0x67b0a8 root + range check, and the
 * common fallback handler is FUN_003a21f4 at 0x67c230. Unsupported tags trap.
 * Confidence: medium
 * Notes: SW_BP traps at 0x3a0960, 0x3a0968, 0x3a0720. Handler tables at 0x67c1c8 /
 * 0x67c0d0 / 0x67c068 / 0x67c230. */
void FUN_003a0690(unsigned long param_1, unsigned long param_2, unsigned long *param_3,
                  unsigned long param_4, unsigned long param_5, unsigned long param_6,
                  unsigned long param_7)
{
    long node;
    long *nptr;
    int iv4;
    cL4_w16_t av5;
    unsigned long loc68;
    unsigned long *puStack_60;
    unsigned long *loc58;

    av5 = FUN_003a0ed4((unsigned long *)param_7, (unsigned long *)param_2);
    loc58 = (unsigned long *)av5.hi;
    puStack_60 = (unsigned long *)av5.lo;
    if (param_3 != (unsigned long *)0x0) {
        puStack_60 = param_3;
    }
    iv4 = 0;
    if (*puStack_60 < 0x800) {
        iv4 = (int)*puStack_60;
    }

    if (iv4 < 0x203) {
        if (iv4 - 0x201U < 2) {
            loc68 = 0x67c1c8;
            FUN_003a1dac((unsigned long *)param_1, (long)&loc68, (unsigned long)loc58, (unsigned long *)param_5, (unsigned long *)param_6);
            return;
        }
        if (iv4 != 0) {
            if (iv4 == 0x200) {
                loc68 = 0x67c0d0;
                FUN_003a156c((unsigned long *)param_1, (long *)&loc68, (unsigned long)param_4);
                return;
            }
LAB_003a095c:
            /* noreturn fail-closed trap (brk #1) */
            CL4_SW_BP(0x3a0960);
            return; /* unreachable */
        }
    } else if (iv4 < 0x301) {
        if (iv4 != 0x203) {
            if (((iv4 != 0x300) || (puStack_60 != (unsigned long *)0x67b0a8)) ||
                (0xfffffffffffff800 < **(long **)*loc58 - 0x800U)) {
                goto LAB_003a095c;
            }
            if (param_3 == (unsigned long *)0x0) {
                node = FUN_003a25a0((unsigned long *)0);
                while ((*(long *)(node + 0x28) == 0 || (*(long *)(node + 0x28) == 0))) {
                    nptr = (long *)(node + 8);
                    node = 0;
                    if (*nptr != 0) {
                        node = *nptr;
                    }
                }
            }
            puStack_60 = (unsigned long *)0x67b0a8;
            goto LAB_003a0810;
        }
    } else {
        if (iv4 < 0x305) {
            if (iv4 == 0x301) {
                loc68 = 0x67c068;
                FUN_003a11c0((unsigned long *)param_1, (long *)&loc68, (unsigned long)param_4, (unsigned long)param_5, (unsigned long)param_6);
                return;
            }
            /* noreturn fail-closed trap (brk #1) */
            CL4_SW_BP(0x3a0968);
            return; /* unreachable */
        }
        if (0x305 < iv4) {
            if ((1 < iv4 - 0x500U) && (iv4 != 0x306)) {
                /* noreturn fail-closed trap (brk #1) */
                CL4_SW_BP(0x3a0720);
                return; /* unreachable */
            }
            goto LAB_003a095c;
        }
    }

    if (param_3 == (unsigned long *)0x0) {
        node = FUN_003a25a0((unsigned long *)*loc58);
        while ((*(long *)(node + 0x28) == 0 || (*(long *)(node + 0x28) == 0))) {
            nptr = (long *)(node + 8);
            node = 0;
            if (*nptr != 0) {
                node = *nptr;
            }
        }
    }
LAB_003a0810:
    loc68 = 0x67c230;
    FUN_003a21f4((unsigned long)param_1, (long *)&loc68, (unsigned long)param_4);
    return;
}
/* FUN_003a0968 @ 0x003a0968   (est. sk_syscall_kind_letter)
 * Ghidra: undefined8 FUN_003a0968(undefined8 param_1,undefined8 param_2)
 * Maps a message tag to a one-character kind code (returned as a small integer):
 * 0x200 -> 0x73('s'), 0x201/0x202 -> 0x65('e'), 0x203 -> 0x66('f'), 0x204 -> 0x66,
 * 0x300 -> 0x63('c') or 0 after validating the 0x67b0a8 root, 0x301 -> 0x74('t'),
 * 0x306 -> 0; default (walk) path returns 0x63('c'). Unknown tags return 0 or trap.
 * Confidence: medium
 * Notes: SW_BP trap at 0x3a0a08. Range checks via **(long**)*pair.hi against 0x800. */
unsigned long FUN_003a0968(unsigned long param_1, unsigned long param_2)
{
    long node;
    long *nptr;
    int iv4;
    unsigned long v5;
    cL4_w16_t av6;

    av6 = FUN_003a0ed4((unsigned long *)param_2, (unsigned long *)param_1);
    v5 = *(unsigned long *)av6.lo;
    iv4 = 0;
    if (v5 < 0x800) {
        iv4 = (int)v5;
    }
    if (iv4 < 0x300) {
        if (iv4 < 0x201) {
            if (iv4 != 0) {
                if (iv4 != 0x200) {
                    return 0;
                }
                return 0x73;
            }
        } else {
            if (iv4 - 0x201U < 2) {
                return 0x65;
            }
            if (iv4 != 0x203) {
                if (iv4 != 0x204) {
                    return 0;
                }
                return 0x66;
            }
        }
    } else {
        if (iv4 < 0x305) {
            if (iv4 != 0x300) {
                if (iv4 != 0x301) {
                    return 0;
                }
                return 0x74;
            }
            if ((unsigned long *)av6.lo == (unsigned long *)0x67b0a8) {
                if (**(long **)(*(unsigned long *)av6.hi) - 0x800U < 0xfffffffffffff801) {
                    node = FUN_003a25a0((unsigned long *)0);
                    while ((*(long *)(node + 0x28) == 0 || (*(long *)(node + 0x28) == 0))) {
                        nptr = (long *)(node + 8);
                        node = 0;
                        if (*nptr != 0) {
                            node = *nptr;
                        }
                    }
                    return 99;
                }
                return 0;
            }
            return 0;
        }
        if (0x305 < iv4) {
            if (iv4 == 0x306) {
                return 0;
            }
            if ((1 < iv4 - 0x500U) && (iv4 != 0x400)) {
                /* noreturn fail-closed trap (brk #1) */
                CL4_SW_BP(0x3a0a08);
                return 0; /* unreachable */
            }
        }
    }
    node = FUN_003a25a0((unsigned long *)*(unsigned long *)av6.hi);
    while ((*(long *)(node + 0x28) == 0 || (*(long *)(node + 0x28) == 0))) {
        nptr = (long *)(node + 8);
        node = 0;
        if (*nptr != 0) {
            node = *nptr;
        }
    }
    return 99;
}
/* FUN_003a0b04 @ 0x003a0b04   (est. sk_syscall_check)
 * Ghidra: undefined8 FUN_003a0b04(undefined8 param_1,undefined8 param_2)
 * Tag validation/check dispatcher: 0x201/0x202 route to FUN_003a1f60, 0x300 requires the
 * object be the 0x67b0a8 root and pass a range check, then walks; tags 0, 0x203, 0x305
 * and the 0x300 walk path fall through to a common walk and return 0. Returns a status
 * (0 = ok). Unknown tags return 0 or trap.
 * Confidence: medium
 * Notes: SW_BP trap at 0x3a0c90. Range check via **(long**)*pair.hi - 0x800U. */
unsigned long FUN_003a0b04(unsigned long param_1, unsigned long param_2)
{
    long node;
    long *nptr;
    unsigned long v4;
    int iv5;
    unsigned long v6;
    unsigned long loc28;
    cL4_w16_t auStack_20;

    auStack_20 = FUN_003a0ed4((unsigned long *)param_2, (unsigned long *)param_1);
    v6 = *(unsigned long *)auStack_20.lo;
    iv5 = 0;
    if (v6 < 0x800) {
        iv5 = (int)v6;
    }
    if (iv5 < 0x203) {
        if (iv5 - 0x201U < 2) {
            loc28 = 0x67c1c8;
            v4 = FUN_003a1f60((long)&loc28);
            return v4;
        }
        if (iv5 != 0) {
            return 0;
        }
    } else if (iv5 < 0x305) {
        if (iv5 != 0x203) {
            if (iv5 != 0x300) {
                return 0;
            }
            if ((unsigned long *)auStack_20.lo != (unsigned long *)0x67b0a8) {
                return 0;
            }
            if (0xfffffffffffff800 < **(long **)(*(unsigned long *)auStack_20.hi) - 0x800U) {
                return 0;
            }
            node = FUN_003a25a0((unsigned long *)0);
            while ((*(long *)(node + 0x28) == 0 || (*(long *)(node + 0x28) == 0))) {
                nptr = (long *)(node + 8);
                node = 0;
                if (*nptr != 0) {
                    node = *nptr;
                }
            }
            return 0;
        }
    } else if (iv5 != 0x305) {
        if ((1 < iv5 - 0x500U) && (iv5 != 0x400)) {
            /* noreturn fail-closed trap (brk #1) */
            CL4_SW_BP(0x3a0c90);
            return 0; /* unreachable */
        }
    }
    node = FUN_003a25a0((unsigned long *)*(unsigned long *)auStack_20.hi);
    while ((*(long *)(node + 0x28) == 0 || (*(long *)(node + 0x28) == 0))) {
        nptr = (long *)(node + 8);
        node = 0;
        if (*nptr != 0) {
            node = *nptr;
        }
    }
    return 0;
}
/* FUN_003a0c90 @ 0x003a0c90   (est. swift_metadata_kind_name)
 * Ghidra: char * FUN_003a0c90(ulong *param_1)
 * Returns a human-readable kind-name string for a metadata/type tag: reads the 32-bit tag
 * at *param_1 and maps it to one of several literal strings (Opaque Value, Tuple,
 * Function, Existential, Objective-C Class Wrapper, Existential Metatype, Foreign Class,
 * Foreign Reference Type, Heap Local Variable, Heap Generic Local Variable, ErrorType
 * Object, Extended Existential) or "Unknown" for unrecognized values. NULL for a few
 * reserved tags. No side effects.
 * Confidence: medium
 * Notes: String literals at 0x5d64ed-0x5d65d7 (rendered as literal char* addresses). */
char *FUN_003a0c90(unsigned long *tag_ptr)
{
    int iv1;

    iv1 = 0;
    if (*tag_ptr < 0x800) {
        iv1 = (int)*tag_ptr;
    }
    if (iv1 < 0x302) {
        if (iv1 < 0x203) {
            if (iv1 - 0x200U < 3 || iv1 == 0) {
                return (char *)0x0;
            }
        } else if (iv1 < 0x300) {
            if (iv1 == 0x203) {
                return (char *)0x5d6550; /* "Foreign Class" */
            }
            if (iv1 == 0x204) {
                return (char *)0x5d6560; /* "Foreign Reference Type" */
            }
        } else {
            if (iv1 == 0x300) {
                return (char *)0x5d64ed; /* "Opaque Value" */
            }
            if (iv1 == 0x301) {
                return (char *)0x5d64fc; /* "Tuple" */
            }
        }
    } else if (iv1 < 0x306) {
        if (iv1 < 0x304) {
            if (iv1 == 0x302) {
                return (char *)0x5d6504; /* "Function" */
            }
            if (iv1 == 0x303) {
                return (char *)0x5d650f; /* "Existential" */
            }
        } else {
            if (iv1 == 0x304) {
                return (char *)0x0;
            }
            if (iv1 == 0x305) {
                return (char *)0x5d651d; /* "Objective-C Class Wrapper" */
            }
        }
    } else if (iv1 < 0x400) {
        if (iv1 == 0x306) {
            return (char *)0x5d6539; /* "Existential Metatype" */
        }
        if (iv1 == 0x307) {
            return (char *)0x5d65c0; /* "Extended Existential" */
        }
    } else {
        if (iv1 == 0x400) {
            return (char *)0x5d6579; /* "Heap Local Variable" */
        }
        if (iv1 == 0x500) {
            return (char *)0x5d658f; /* "Heap Generic Local Variable" */
        }
        if (iv1 == 0x501) {
            return (char *)0x5d65ad; /* "ErrorType Object" */
        }
    }
    return (char *)0x5d65d7; /* "Unknown" */
}
/* FUN_003a0dec @ 0x003a0dec   (est. sk_env_check)
 * Ghidra: undefined8 FUN_003a0dec(void)
 * Reads a capability/environment word from FUN_0000456c. If bit 8 (0x100) of the upper
 * half is clear, returns 0. Otherwise walks via FUN_00019850, requires bit 0x100 set or
 * traps, then re-walks and returns FUN_00118cf8(). A boot/environment presence check.
 * Confidence: medium
 * Notes: SW_BP trap at 0x3a0e40. Uses FUN_0000456c (uint), FUN_00019850, FUN_00118cf8. */
unsigned long FUN_003a0dec(void)
{
    unsigned int flags;
    unsigned long ret;
    long node;
    unsigned short short_flags;

    flags = FUN_0000456c();
    short_flags = (unsigned short)flags;
    if ((flags >> 8 & 1) == 0) {
        ret = 0;
    } else {
        node = FUN_00019850(&short_flags);
        ret = 0;
        if (node != 0) {
            if ((short_flags & 0x100) == 0) {
                /* noreturn fail-closed trap (brk #1) */
                CL4_SW_BP(0x3a0e40);
                return 0; /* unreachable */
            }
            FUN_00019850(&short_flags);
            ret = FUN_00118cf8();
        }
    }
    return ret;
}
/* FUN_003a0e44 @ 0x003a0e44   (est. sk_obj_resolve)
 * Ghidra: undefined8 FUN_003a0e44(undefined8 param_1)
 * Resolves an object descriptor into a capability/result. Calls thunk_FUN_00115080 to get
 * a current value, packs (param_1, value) via FUN_003bd1f4 into a small record, then
 * inspects the record's status byte (cStack_21): negative -> returns FUN_00118cf8(local_38)
 * if the 8-byte local_30 word is nonzero else 0, then clears the top bit of the
 * concatenated word via thunk_FUN_00012568; zero -> returns 0; positive -> returns
 * FUN_00118cf8(&local_38).
 * Confidence: medium
 * Notes: FUN_003bd1f4 writes a record spanning local_38/local_30/local_28/cStack_21.
 * CONCAT17(cStack_21, local_28) modelled as an 8-byte little-endian value (local_28
 * bytes are undefined/don't-care). */
unsigned long FUN_003a0e44(unsigned long param_1)
{
    unsigned long v1;
    unsigned long loc38;
    long loc30;
    unsigned char loc28[7] = {0, 0, 0, 0, 0, 0, 0};
    char cStack_21;
    unsigned long concat;
    unsigned char buf[8];

    v1 = thunk_FUN_00115080();
    FUN_003bd1f4(&loc38, param_1, v1);
    if (cStack_21 < '\0') {
        if (loc30 == 0) {
            v1 = 0;
        } else {
            v1 = FUN_00118cf8(loc38);
        }
        buf[0] = loc28[0];
        buf[1] = loc28[1];
        buf[2] = loc28[2];
        buf[3] = loc28[3];
        buf[4] = loc28[4];
        buf[5] = loc28[5];
        buf[6] = loc28[6];
        buf[7] = (unsigned char)cStack_21;
        concat = *(unsigned long *)buf & 0x7fffffffffffffffUL;
        thunk_FUN_00012568(loc38, concat);
    } else if (cStack_21 == '\0') {
        v1 = 0;
    } else {
        v1 = FUN_00118cf8(&loc38);
    }
    return v1;
}
/* FUN_003a0ed4 @ 0x003a0ed4   (est. sk_tag_pair_resolve)
 * Ghidra: undefined1 [16] FUN_003a0ed4(ulong *param_1,undefined8 *param_2)
 * Resolves a (msg, tag) pair into a 16-byte {obj, aux} pair, following indirect/boxed
 * reference chains. Returns {param_1, param_2} directly for most tags; for tag 0x303 it
 * re-derives both via FUN_00374de4/FUN_00374d80; for tag 0x307 it inspects the byte at
 * param_1[1] and unwraps: 0 -> {param_2[3], FUN_0036a358(param_2)}, 1 -> FUN_003a25b8,
 * 2 -> {FUN_003743d0(*param_2), ...}, 3 traps. Loops until a concrete pair is produced.
 * Confidence: medium
 * Notes: SW_BP trap at 0x3a0fc0 for ref-kind 3. Recurse/loop via labeled loop. */
cL4_w16_t FUN_003a0ed4(unsigned long *param_1, unsigned long *param_2)
{
    unsigned char bv1;
    unsigned long *pu3;
    int iv4;
    cL4_w16_t av5;

loop:
    iv4 = 0;
    if (*param_1 < 0x800) {
        iv4 = (int)*param_1;
    }
    for (;;) {
        while (1) {
            if (iv4 != 0x307) {
                if (iv4 != 0x303) {
                    av5.hi = (unsigned long)param_2;
                    av5.lo = (unsigned long)param_1;
                    return av5;
                }
                pu3 = (unsigned long *)FUN_00374de4(param_1, param_2);
                param_2 = (unsigned long *)FUN_00374d80(param_1, param_2);
                param_1 = pu3;
                goto loop;
            }
            bv1 = *(unsigned char *)param_1[1];
            if (bv1 < 2) {
                break;
            }
            if (bv1 == 2) {
                param_1 = (unsigned long *)FUN_003743d0(*param_2);
                goto loop;
            }
            if (bv1 == 3) {
                /* noreturn fail-closed trap (brk #1) */
                CL4_SW_BP(0x3a0fc0);
                return av5; /* unreachable */
            }
        }
        if (bv1 == 0) {
            param_1 = (unsigned long *)param_2[3];
            param_2 = (unsigned long *)FUN_0036a358(param_2);
            goto loop;
        }
        break; /* bVar1 == 1 */
    }
    param_1 = (unsigned long *)FUN_003a25b8((unsigned long *)*param_2);
    goto loop;
}
/* FUN_003a0fcc @ 0x003a0fcc   (est. sk_memo_lookup)
 * Ghidra: undefined8 FUN_003a0fcc(undefined8 *param_1)
 * Memoized lookup: if the slot at *param_1 is empty, resolves and caches a node via
 * FUN_003a25a0(**(param_1[1])) using the walk loop, storing it into *param_1. Then
 * returns the value at **(param_1[2]). A lazy cached indirection read.
 * Confidence: medium
 * Notes: Uses the standard walk loop (node+0x28 check). */
unsigned long FUN_003a0fcc(unsigned long *param_1)
{
    long node;
    long *nptr;

    if (*(long *)*param_1 == 0) {
        node = FUN_003a25a0((unsigned long *)**(unsigned long **)param_1[1]);
        while ((*(long *)(node + 0x28) == 0 || (*(long *)(node + 0x28) == 0))) {
            nptr = (long *)(node + 8);
            node = 0;
            if (*nptr != 0) {
                node = *nptr;
            }
        }
        *(long *)*param_1 = node;
    }
    return **(unsigned long **)param_1[2];
}
/* FUN_003a1098 @ 0x003a1098   (est. sk_syscall_table_entry)
 * Ghidra: undefined1 [16] FUN_003a1098(long param_1,ulong param_2,long *param_3,undefined8 *param_4)
 * Fetches a syscall/table entry for index param_2: validates param_2 is non-negative and
 * within the table size at *(*(param_1+8)+8) else traps. If a string-table base at
 * *(*(param_1+8)+0x10) exists, walks to the param_2-th string (length-prefixed via
 * thunk_FUN_00114c60, 0x20-prefix), copies it into a freshly allocated buffer
 * (FUN_000101a0/FUN_00117cc8) and stores the buffer in *param_3; otherwise fills *param_3
 * from FUN_003a1310. Sets *param_4 to a fallback code pointer and returns a 16-byte
 * {entry_word, 0x100} pair.
 * Confidence: low
 * Notes: SW_BP trap at 0x3a11c0 on out-of-range index. String walk uses 0x20-byte
 * header stride; alloc size constant 0x100004077774924. *param_4 = &LAB_003a13b8
 * rendered as literal code address 0x3a13b8. */
cL4_w16_t FUN_003a1098(long param_1, unsigned long param_2, long *param_3, unsigned long *param_4)
{
    long lv2;
    long lv3;
    unsigned long v4;
    long lv5;
    long lv6;
    cL4_w16_t av7;
    long loc58;

    if (((long)param_2 < 0) ||
        (lv6 = *(long *)(param_1 + 8), *(unsigned long *)(lv6 + 8) < param_2)) {
        /* noreturn fail-closed trap (brk #1) */
        CL4_SW_BP(0x3a11c0);
        return av7; /* unreachable */
    }
    lv3 = *(long *)(lv6 + 0x10);
    if (lv3 != 0) {
        lv2 = thunk_FUN_00114c60(lv3, 0x20);
        v4 = param_2;
        while ((lv5 = lv2, v4 != 0 && (lv5 = 0, lv2 != 0))) {
            v4 = v4 - 1;
            lv3 = lv2 + 1;
            lv2 = thunk_FUN_00114c60(lv3, 0x20);
        }
        if (lv2 != 0 && lv3 != lv5) {
            lv5 = lv5 - lv3;
            lv2 = FUN_000101a0(lv5 + 1, 0x100004077774924);
            FUN_00117cc8(lv2, lv3, lv5, lv5 + 1);
            *(unsigned char *)(lv2 + lv5) = 0;
            *param_3 = lv2;
            goto LAB_003a1180;
        }
    }
    FUN_003a1310((long *)&loc58);
    *param_3 = loc58;
LAB_003a1180:
    *param_4 = (unsigned long)0x3a13b8; /* &LAB_003a13b8: fallback code pointer */
    av7.lo = *(unsigned long *)(lv6 + (param_2 & 0xffffffff) * 0x10 + 0x18);
    av7.hi = 0x100;
    return av7;
}
/* FUN_003a11c0 @ 0x003a11c0   (est. sk_table_method_invoke)
 * Ghidra: void FUN_003a11c0(undefined8 *param_1,long *param_2,undefined8 param_3,undefined8 param_4,undefined8 param_5)
 * Invokes two method slots on a vtable at *param_2: slot +0x10 (no-arg getter, result in
 * lVar1) and slot +0x18 (method with 4 args). Calls FUN_003766b4 on the second result to
 * build a 24-byte descriptor, then invokes a vtable slot at (*(local_48-8))+0x10 passing
 * (uVar2, lVar3+lVar1). Fills the caller record param_1: [0]=w0, [1]=w1, [2]=w2, [3]=the
 * second-method result. Table dispatch / method thunking helper.
 * Confidence: low
 * Notes: Uses indirect (vtable) calls through literal slot offsets 0x10/0x18. */
void FUN_003a11c0(unsigned long *param_1, long *param_2, unsigned long param_3,
                  unsigned long param_4, unsigned long param_5)
{
    long lv1;
    unsigned long v2;
    long lv3;
    unsigned long loc60;
    unsigned long uStack_58;
    unsigned long uStack_50;
    long loc48;

    lv1 = (**(long (**)(void))(*param_2 + 0x10))();
    loc48 = (**(long (**)(long *, unsigned long, unsigned long, unsigned long))
                (*param_2 + 0x18))(param_2, param_3, param_4, param_5);
    lv3 = param_2[2];
    v2 = FUN_003766b4(loc48, &loc60);
    (**(void (**)(unsigned long, long))(*(long *)(loc48 + -8) + 0x10))
        (v2, lv3 + lv1);
    param_1[1] = uStack_58;
    param_1[0] = loc60;
    param_1[3] = loc48;
    param_1[2] = uStack_50;
    return;
}
/* FUN_003a12d8 @ 0x003a12d8   (est. vtbl_method_dispatch)
 * Ghidra: void FUN_003a12d8(long *param_1)
 * Dispatches through the object's vtable: reads the vtable pointer from the
 * object and calls the virtual method at vtable offset 0x18 with no arguments.
 * Return value of the virtual call is discarded. obj->vtbl is dereferenced but
 * the object itself is only used to reach the vtable.
 * Confidence: medium
 * Notes: no software breakpoints, no strings referenced. */
void FUN_003a12d8(long *obj)
{
    ((void (*)(void))(*obj + 0x18))();
}
/* FUN_003a1310 @ 0x003a1310   (est. swift_string_format)
 * Ghidra: void FUN_003a1310(long *param_1)
 * Builds a formatted string into a freshly allocated buffer. First queries the
 * size with FUN_00116bb4(0,0,&fmt,"") using the format string at 0x5d65e1,
 * then allocates iVar1+1 bytes via FUN_000101a0 and re-formats into it. On
 * success the buffer pointer is stored at *param_1 (out); on any failure
 * *param_1 stays 0 (or the buffer is freed via thunk_FUN_00012568).
 * Confidence: medium
 * Notes: &DAT_005d65e1 is a format-string literal; &stack0x00000000 is the
 * Ghidra placeholder for a vararg tail and is rendered as a zero. */
void FUN_003a1310(long *param_1)
{
    int size;
    unsigned long buf;

    size = FUN_00116bb4(0, 0, (unsigned long)0x005d65e1, 0);
    *param_1 = 0;
    if (size >= 0) {
        buf = FUN_000101a0((unsigned long)(size + 1), 0x100004077774924UL);
        if (buf != 0) {
            size = FUN_00116bb4(buf, (unsigned long)(size + 1),
                                (unsigned long)0x005d65e1, 0);
            if (size < 0) {
                thunk_FUN_00012568(buf);
            } else {
                *param_1 = buf;
            }
        }
    }
}
/* FUN_003a13c4 @ 0x003a13c4   (est. swift_metadata_get)
 * Ghidra: undefined4 FUN_003a13c4(long param_1)
 * Reads a value from a metadata structure hanging off param_1+8. The node is
 * *(*(param_1+8)+8); if the entry at node+0x10 is non-zero and not the
 * negated node-address sentinel, returns the 32-bit field at node+0x14.
 * Otherwise returns 0. The `-0x10 - node` compare is the decompiler's
 * rendering of the sentinel -(node+0x10) (end-of-list marker).
 * Confidence: medium
 * Notes: sentinel check `(long)*(int *)(lVar2+0x10) == -0x10 - lVar2`. */
unsigned int FUN_003a13c4(long param_1)
{
    long node;
    long probe;

    node = *(long *)(*(long *)(param_1 + 8) + 8);
    probe = node;
    if (node == 0) {
        probe = 0;
    }
    if (*(int *)(probe + 0x10) != 0 &&
        (long)*(int *)(probe + 0x10) != -0x10 - probe) {
        if (node == 0) {
            node = 0;
        }
        return *(unsigned int *)(node + 0x14);
    }
    return 0;
}
/* FUN_003a1480 @ 0x003a1480   (est. swift_metadata_index)
 * Ghidra: undefined4 FUN_003a1480(long param_1,ulong param_2)
 * Indexes into the metadata's command table using param_2 as an index. The
 * bounds are checked against either the TLS command-count (`sizeofcmds`) when
 * the node is null, or the node's own 32-bit count at +0x14. The returned
 * 32-bit slot is at base + (count@node+0x18)*8 + param_2*4. Out-of-range
 * indices hit a fail-closed brk #1 trap at 0x3a1518.
 * Confidence: medium
 * Notes: CL4_SW_BP(0x3a1518); the label `load` is only reachable via goto --
 * the trap is the fall-through path for the failing bounds checks. */
unsigned int FUN_003a1480(long param_1, unsigned long param_2)
{
    long node;

    if ((long)param_2 >= 0) {
        node = *(long *)(*(long *)(param_1 + 8) + 8);
        if (node == 0) {
            if (param_2 <= sizeofcmds) {
                node = 0;
                goto load;
            }
        } else if (param_2 <= *(unsigned int *)(node + 0x14)) {
            goto load;
        }
    }
    /* fail-closed trap on out-of-range index (noreturn in the binary) */
    CL4_SW_BP(0x3a1518);
load:
    return *(unsigned int *)(*(long *)(param_1 + 8)
            + (unsigned long)*(unsigned int *)(node + 0x18) * 8 + param_2 * 4);
}
/* FUN_003a1518 @ 0x003a1518   (est. swift_metadata_info)
 * Ghidra: undefined1 [16] FUN_003a1518(long param_1,undefined8 param_2,undefined8 *param_3,undefined8 *param_4)
 * Thin wrapper over FUN_003a160c: decodes the metadata at *(param_1+8) into a
 * 16-byte slot, stores the first output word into *param_3, zeroes *param_4,
 * and returns a 16-byte value whose low 11 bytes are an uninitialized stack
 * buffer (decompiler artifact of an ignored struct-return slot) and whose
 * high 5 bytes are zero. Callers normally only use the *param_3 output.
 * Confidence: low
 * Notes: auVar1._0_11_ = local_30 (uninitialized stack buf) and
 * auVar1._11_5_ = 0; rebuilt byte-wise as cL4_w16_t. */
cL4_w16_t FUN_003a1518(long param_1, unsigned long param_2,
                       unsigned long *param_3, unsigned long *param_4)
{
    unsigned long slot[2];
    unsigned char buf[11];
    cL4_w16_t ret;

    FUN_003a160c((long *)slot, (unsigned long)*(unsigned long *)(param_1 + 8), (unsigned long)0);
    *param_3 = slot[0];
    *param_4 = 0;
    ret.lo = (unsigned long)buf[0] | ((unsigned long)buf[1] << 8)
           | ((unsigned long)buf[2] << 16) | ((unsigned long)buf[3] << 24)
           | ((unsigned long)buf[4] << 32) | ((unsigned long)buf[5] << 40)
           | ((unsigned long)buf[6] << 48) | ((unsigned long)buf[7] << 56);
    ret.hi = (unsigned long)buf[8] | ((unsigned long)buf[9] << 8)
           | ((unsigned long)buf[10] << 16);
    return ret;
}
/* FUN_003a156c @ 0x003a156c   (est. swift_metadata_resolve)
 * Ghidra: void FUN_003a156c(undefined8 param_1,long *param_2,undefined8 param_3)
 * Resolves a Swift reference through param_2's vtable. Calls the virtual
 * method at vtable+0x18 (returns a 16-byte value) and the virtual method at
 * vtable+0x10 with (param_2, param_3) (returns an offset). Computes
 * param_2[2] + that offset as the target and passes it plus the low/high
 * halves of the 16-byte result into FUN_003a1b0c as an out-format call.
 * Confidence: low
 * Notes: FUN_003a1b0c receives (param_1, target, auVar3.lo, auVar3.hi &
 * 0xffffff); the pointer-typed params of the callee are fed integer values
 * (Ghidra looseness), rendered here with casts. */
void FUN_003a156c(unsigned long *param_1, long *param_2, unsigned long param_3)
{
    long offset;
    long base;
    cL4_w16_t v;

    v = ((cL4_w16_t (*)(void))(*param_2 + 0x18))();
    base = param_2[2];
    offset = ((long (*)(long *, unsigned long))(*param_2 + 0x10))(param_2, param_3);
    FUN_003a1b0c((unsigned long *)param_1, (long *)(base + offset), (long *)v.lo, (unsigned long)v.hi & 0xffffff);
}
/* FUN_003a160c @ 0x003a160c   (est. swift_metadata_decode)
 * Ghidra: void FUN_003a160c(long *param_1,undefined8 param_2,ulong param_3)
 * The core Swift runtime metadata decoder. Fetches the runtime base via
 * FUN_0035bd48, walks the +0x10 size header to the target, and indexes to a
 * 12-byte-per-entry record using param_3. Emits a 0x20-byte result struct at
 * param_1: a name/descriptor pointer, a length/kind word, a flag word, and
 * packed byte flags at +0x18..0x1a. Missing/empty metadata degrades to the
 * "unknown" sentinel (0x67b148) with a warning log (FUN_003a18c8). The
 * non-trivial path decodes a reference with FUN_003a31d8/FUN_003895e0 and may
 * release intermediate objects. Stack canary is checked before return.
 * Confidence: medium
 * Notes: strings at 0x5d668b / 0x5d65e6 (warnings) and 0x5d671d ("unknown");
 * canary -0x2c8502b44bfffed6; local_180 is a decompiler-register artifact
 * defaulted to the stack buffer so the cleanup test is skipped. */
void FUN_003a160c(long *param_1, unsigned long param_2, unsigned long param_3)
{
    unsigned long canary = -0x2c8502b44bfffed6UL;
    unsigned long base;
    int iv4;
    long lv1;
    long lv6;
    long lv9;
    unsigned long v7;
    unsigned int v2;
    unsigned char bv3;
    int *pi8;
    unsigned char auStack_198[16];
    unsigned char auStack_170[264];
    unsigned long loc188 = 0;
    unsigned char *loc180 = auStack_170;
    unsigned long loc1b8 = 0;
    short loc1a0 = 0;
    unsigned char loc1a8 = 0;
    unsigned long (*pcStack_1b0)(long, unsigned long, unsigned long) = 0;
    unsigned long loc1d8, loc1f8;
    unsigned long *loc1c0, *loc1e0;
    unsigned char *puStack_1f0, *puStack_1d0;

    base = FUN_0035bd48();
    if (base != 0) {
        iv4 = *(int *)(base + 0x10);
        base = base + 0x10 + (long)iv4;
        if (iv4 != 0 && base != 0) {
            /* main decode path */
            base = base + (param_3 & 0xffffffff) * 0xc;
            iv4 = *(int *)(base + 0x18);
            lv1 = 0;
            if (iv4 != 0) {
                lv1 = (long)iv4 + base + 0x18;
            }
            if (lv1 == 0) {
                lv6 = 0;
            } else {
                lv6 = thunk_FUN_00115080();
            }
            pi8 = (int *)(base + 0x14);
            iv4 = *pi8;
            if (iv4 == 0 || (long)iv4 == -(long)pi8) {
                /* simple path: no reference indirection */
                v2 = *(unsigned int *)(base + 0x10);
                *param_1 = lv1;
                param_1[1] = lv6;
                param_1[2] = 0;
                *(unsigned char *)((long)param_1 + 0x1a) = 0;
                *(unsigned short *)(param_1 + 3) = (unsigned short)v2 & 1;
            } else {
                /* complex path: indirect reference decode */
                cL4_w16_t av10 = { 0, 0 };
                FUN_003a31d8((unsigned char *)(long)iv4 + (long)pi8);
                FUN_0037d1d8(auStack_198, param_2);
                loc1c0 = &loc1d8;
                loc1d8 = 0x67c138;
                loc1e0 = &loc1f8;
                loc1f8 = 0x67c180;
                puStack_1f0 = auStack_198;
                puStack_1d0 = auStack_198;
                FUN_003895e0(&loc1b8, 0, av10.lo, av10.hi, loc188,
                             &loc1d8, &loc1f8);
                FUN_0036805c(&loc1f8);
                FUN_003680cc(&loc1d8);
                lv9 = loc1b8;
                if (loc1a0 != 0) {
                    if (loc1a0 == 1) {
                        v7 = pcStack_1b0(loc1b8, 0, 0);
                        FUN_003a18c8((unsigned long)0x005d65e6);
                        pcStack_1b0(loc1b8, 1, v7);
                        loc1a8 = 0;
                        lv9 = 0x67b148;
                    } else {
                        loc1a8 = 0;
                        lv9 = 0;
                    }
                }
                bv3 = *(unsigned char *)(base + 0x10);
                *param_1 = lv1;
                param_1[1] = lv6;
                param_1[2] = lv9;
                *(unsigned char *)(param_1 + 3) = bv3 & 1;
                *(unsigned char *)((long)param_1 + 0x19) = (bv3 >> 1) & 1;
                *(unsigned char *)((long)param_1 + 0x1a) = loc1a8;
                if (loc1a0 == 1) {
                    pcStack_1b0(loc1b8, 3, 0);
                }
                if (loc180 != auStack_170) {
                    thunk_FUN_00012568(0);
                }
            }
            goto canary_check;
        }
    }
    /* warning path: runtime not found / empty metadata */
    FUN_00361528(param_2, 1);
    FUN_003a18c8((unsigned long)0x005d668b);
    *param_1 = (long)0x005d671d;
    param_1[1] = 7;
    param_1[2] = 0x67b148;
    *(unsigned short *)(param_1 + 3) = 0;
    *(unsigned char *)((long)param_1 + 0x1a) = 0;
canary_check:
    if (canary == -0x2c8502b44bfffed6UL) {
        return;
    }
    /* stack canary mismatch: noreturn */
    FUN_0011d7e8();
}
/* FUN_003a18c8 @ 0x003a18c8   (est. swift_warning_log)
 * Ghidra: void FUN_003a18c8(undefined8 param_1)
 * Logs a Swift runtime warning string (param_1 = pointer to the message).
 * Lazily initializes a spinlock/state word g_lock_state (if still -1) with
 * FUN_003d3dd8 passing the address of a static template at 0x3a1acc. If the
 * enable flag g_log_enabled is set (== 1), forwards the message via
 * FUN_004b9e2c(0, msg, 0) to the printer.
 * Confidence: medium
 * Notes: _DAT_006c0b18 (state) / DAT_006c0b10 (enable) globals renamed to
 * g_lock_state / g_log_enabled with the literal addresses kept in comments;
 * &DAT_003a1acc rendered as literal 0x3a1acc. */
void FUN_003a18c8(unsigned long param_1)
{
    if (g_lock_state > -1) {
        FUN_003d3dd8(&g_lock_state, (unsigned long)0x003a1acc);
    }
    if (g_log_enabled == 1) {
        FUN_004b9e2c(0, param_1, 0);
    }
}
/* FUN_003a1958 @ 0x003a1958   (est. swift_obj_alloc_tag1)
 * Ghidra: void FUN_003a1958(long param_1)
 * Allocates a 16-byte object via FUN_00111890 (tag 0xa1c40bd48d6d6) and
 * initializes it as a tagged wrapper: word0 = the 0x67c138 type-tag constant,
 * word1 = the value copied from *(param_1+8). Return value is discarded.
 * Confidence: high
 * Notes: allocation tag constant kept verbatim; 0x67c138 is a literal type
 * tag address used as a value. */
void FUN_003a1958(long param_1)
{
    unsigned long *obj = (unsigned long *)FUN_00111890(0x10, 0xa1c40bd48d6d6UL);
    unsigned long val = *(unsigned long *)(param_1 + 8);

    obj[0] = 0x67c138;
    obj[1] = val;
}
/* FUN_003a1a18 @ 0x003a1a18   (est. swift_obj_alloc_tag2)
 * Ghidra: void FUN_003a1a18(long param_1)
 * Identical shape to FUN_003a1958 but tags the new 16-byte object with the
 * 0x67c180 type constant instead of 0x67c138. Allocates via FUN_00111890 and
 * copies *(param_1+8) into word1; result pointer is discarded.
 * Confidence: high
 * Notes: allocation tag 0xa1c40bd48d6d6 kept verbatim. */
void FUN_003a1a18(long param_1)
{
    unsigned long *obj = (unsigned long *)FUN_00111890(0x10, 0xa1c40bd48d6d6UL);
    unsigned long val = *(unsigned long *)(param_1 + 8);

    obj[0] = 0x67c180;
    obj[1] = val;
}
/* FUN_003a1ae4 @ 0x003a1ae4   (est. swift_release)
 * Ghidra: void FUN_003a1ae4(long param_1)
 * Releases the object held at *(param_1+8) by forwarding it to FUN_0036b118.
 * The Ghidra output shows a leftover extraout register pair (x9/x10) from the
 * call being written back as a bool; that is a decompiler register artifact
 * and is not reconstructable as meaningful C, so it is omitted.
 * Confidence: low
 * Notes: `*(bool *)extraout_x9 = extraout_x10 == 0;` dropped as a register
 * leftover; no semantic loss for the observable call. */
void FUN_003a1ae4(long param_1)
{
    FUN_0036b118(*(unsigned long *)(param_1 + 8));
}
/* FUN_003a1b0c @ 0x003a1b0c   (est. swift_ref_format)
 * Ghidra: void FUN_003a1b0c(undefined8 *param_1,long *param_2,long *param_3,ulong param_4)
 * Formats a Swift reference described by param_3 into a 0x20-byte out struct
 * at param_1. If param_3's type word is 0x304 (and its size field selects the
 * fast range), the value is dispatched straight to the vtable handler at
 * (param_3[-1]+0x10). Otherwise param_4's reference-kind byte (bits 16-23)
 * picks a path: kind 1 resolves via FUN_0036b8b0, kind 2 releases+repacks via
 * FUN_0036b5c4, kind 4 and the zero kind take the vtable handler, and an
 * unrecognized kind logs "Value with unrecognized reference..." (0x5d6725),
 * unwinds via FUN_003766fc, and substitutes the 0x67b148 sentinel. The
 * trailing payload (lVar3-8 bytes) is copied with FUN_00117cc4.
 * Confidence: medium
 * Notes: gotos mirror the Ghidra label flow (ba4/c00/call_vtable/error/done);
 * string at 0x5d6725; sentinel 0x67b148. */
void FUN_003a1b0c(unsigned long *param_1, long *param_2, long *param_3,
                  unsigned long param_4)
{
    unsigned int kind;
    long *pl2;
    long lv3;
    int iv4;
    unsigned long v5;
    void (*pc6)(long *, long *, long *);
    unsigned long loc60 = 0, uStack_58 = 0, uStack_50 = 0;
    long *loc48;

    loc48 = param_3;
    pl2 = (long *)FUN_003766b4((unsigned long)param_3, &loc60);
    if (*param_3 == 0x304) {
        v5 = *(unsigned long *)param_3[1];
        iv4 = 0;
        if (v5 < 0x800) {
            iv4 = (int)v5;
        }
        if ((2u < (unsigned int)iv4 - 0x301U) &&
            (2u < (unsigned int)iv4 - 0x200U)) {
            goto ba4;
        }
        pc6 = *(void (**)(long *, long *, long *))(param_3[-1] + 0x10);
        param_2 = param_3 + 1;
        goto call_vtable;
    }
ba4:
    kind = (unsigned int)(param_4 >> 0x10) & 0xff;
    if (kind == 1 || (param_4 & 0xff0000) == 0) {
        if ((param_4 & 0xff0000) == 0) {
            goto c00;
        }
        if (kind != 1) {
            goto error;
        }
        lv3 = FUN_0036b8b0(param_2);
        *pl2 = lv3;
        lv3 = *(long *)(param_3[-1] + 0x40);
    } else {
        if (kind != 2) {
            if (kind != 4) {
                goto error;
            }
            goto c00;
        }
        lv3 = *param_2;
        FUN_0036b5c4(lv3);
        *pl2 = lv3;
        lv3 = *(long *)(param_3[-1] + 0x40);
    }
    FUN_00117cc4(pl2 + 1, param_2 + 1, lv3 - 8);
    goto done;
c00:
    pc6 = *(void (**)(long *, long *, long *))(param_3[-1] + 0x10);
    /* fall through to call_vtable */
call_vtable:
    pc6(pl2, param_2, param_3);
    goto done;
error:
    FUN_004b9ed8(0, (unsigned long)0x005d6725);
    FUN_003766fc((unsigned long)param_3, &loc60);
    loc48 = (long *)0x67b148;
done:
    param_1[1] = uStack_58;
    *param_1 = loc60;
    param_1[3] = (unsigned long)loc48;
    param_1[2] = uStack_50;
}
/* FUN_003a1cbc @ 0x003a1cbc   (est. swift_metadata_valid)
 * Ghidra: bool FUN_003a1cbc(long param_1)
 * Returns whether the metadata node for param_1 has a usable field. The node
 * is *(*(param_1+8)+8); if its +0x10 entry is zero or the negated-address
 * sentinel, the answer is false. Otherwise, if param_1+0x10 is non-null, the
 * vtable method at (*(param_1+8)-8)+0x58 is invoked and the result is fed to
 * FUN_003a160c; the flag word (slot[2]) of the decoded struct determines the
 * result.
 * Confidence: medium
 * Notes: sentinel check `-0x10 - lVar3` is the -(node+0x10) end marker. */
bool FUN_003a1cbc(long param_1)
{
    bool bv1;
    unsigned long v2;
    long lv3;
    unsigned char auStack_40[16];
    long loc30 = 0;

    lv3 = *(long *)(*(long *)(param_1 + 8) + 8);
    if (lv3 == 0) {
        lv3 = 0;
    }
    if (*(int *)(lv3 + 0x10) == 0 || (long)*(int *)(lv3 + 0x10) == -0x10 - lv3) {
        bv1 = false;
    } else {
        bv1 = false;
        if (*(long *)(param_1 + 0x10) != 0) {
            v2 = (*(unsigned long (**)(void))(
                        *(long *)(*(long *)(param_1 + 8) - 8) + 0x58))();
            FUN_003a160c((long *)auStack_40, (unsigned long)*(unsigned long *)(param_1 + 8), (unsigned long)v2);
            bv1 = loc30 != 0;
        }
    }
    return bv1;
}
/* FUN_003a1dac @ 0x003a1dac   (est. swift_metadata_ref_build)
 * Ghidra: void FUN_003a1dac(undefined8 *param_1,long param_2,undefined8 param_3,undefined8 *param_4,undefined8 *param_5)
 * Builds and materializes a Swift metadata reference for param_2. Decodes the
 * metadata via FUN_003a160c, re-acquires it with FUN_003766b4, and drives the
 * vtable handlers at (*(param_2+8)-8)+0x10/+0x58/+0x60 to resolve and attach
 * the value. Depending on the local flag byte local_68, uses the 0x67b0a8
 * default owner or the decoded owner (local_70), wraps it with FUN_0036aae4,
 * and links the result back into *(param_2+0x10). Emits a 0x20-byte out
 * struct at param_1 (from local_a0/uStack_58/uStack_50) and stores the first
 * decode word into *param_4 while *param_5 is zeroed.
 * Confidence: low
 * Notes: several stack slots (local_68/local_70) are decompiler-register
 * artifacts, defaulted to 0; literal owner 0x67b0a8; vtable offsets 0x10/0x20/
 * 0x58/0x60. */
void FUN_003a1dac(unsigned long *param_1, long param_2, unsigned long param_3,
                  unsigned long *param_4, unsigned long *param_5)
{
    unsigned long v2;
    unsigned long lv1;
    unsigned long *pu3;
    cL4_w16_t av4;
    unsigned long loca0 = 0, uStack_98 = 0, uStack_90 = 0;
    long loc88 = 0;
    unsigned long loc80[2] = {0, 0};
    long loc70 = 0;
    unsigned char loc68 = 0;

    v2 = (*(unsigned long (**)(unsigned long))(
                *(long *)(*(long *)(param_2 + 8) - 8) + 0x58))(
                    *(unsigned long *)(param_2 + 0x10));
    FUN_003a160c((long *)loc80, (unsigned long)*(unsigned long *)(param_2 + 8), (unsigned long)v2);
    v2 = FUN_003766b4(*(unsigned long *)(param_2 + 8), loc80);
    (*(void (**)(unsigned long, unsigned long))(
        *(long *)(*(long *)(param_2 + 8) - 8) + 0x10))(
            v2, *(unsigned long *)(param_2 + 0x10));
    lv1 = 0x67b0a8;
    if ((loc68 & 1) == 0) {
        lv1 = loc70;
    }
    av4 = FUN_0036aae4(lv1);
    pu3 = (unsigned long *)av4.hi;
    (*(void (**)(unsigned long))(
        *(long *)(*(long *)(param_2 + 8) - 8) + 0x60))(v2);
    (*(void (**)(unsigned long *, unsigned long, unsigned long))(
        *(long *)(lv1 - 8) + 0x20))(pu3, v2, lv1);
    FUN_003766fc(*(unsigned long *)(param_2 + 8), loc80);
    *(unsigned long **)(param_2 + 0x10) = pu3;
    if ((loc68 & 1) != 0) {
        v2 = FUN_0036b250(*pu3);
        *(unsigned long *)(param_2 + 0x10) = v2;
    }
    *param_4 = loc80[0];
    *param_5 = 0;
    loc88 = loc70;
    v2 = FUN_003766b4((unsigned long)loc70, &loca0);
    (*(void (**)(unsigned long, unsigned long))(
        *(long *)(loc88 - 8) + 0x10))(
            v2, *(unsigned long *)(param_2 + 0x10));
    FUN_0036b118(av4.lo);
    param_1[1] = uStack_98;
    *param_1 = loca0;
    param_1[3] = (unsigned long)loc88;
    param_1[2] = uStack_90;
}
/* FUN_003a1f60 @ 0x003a1f60   (est. swift_metadata_field)
 * Ghidra: undefined8 FUN_003a1f60(long param_1)
 * Returns the leading word of the decoded metadata for param_1. The node is
 * *(*(param_1+8)+8); if its +0x10 entry is zero or the negated-address
 * sentinel, returns 0. Otherwise invokes the vtable method at
 * (*(param_1+8)-8)+0x58 with *(param_1+0x10) and feeds the result into
 * FUN_003a160c, returning the first word of the decoded struct.
 * Confidence: medium
 * Notes: sentinel check `-0x10 - lVar2` is the -(node+0x10) end marker. */
unsigned long FUN_003a1f60(long param_1)
{
    unsigned long v1;
    long lv2;
    unsigned long loc40[4] = {0, 0, 0, 0};

    lv2 = *(long *)(*(long *)(param_1 + 8) + 8);
    if (lv2 == 0) {
        lv2 = 0;
    }
    if (*(int *)(lv2 + 0x10) == 0 || (long)*(int *)(lv2 + 0x10) == -0x10 - lv2) {
        loc40[0] = 0;
    } else {
        v1 = (*(unsigned long (**)(unsigned long))(
                    *(long *)(*(long *)(param_1 + 8) - 8) + 0x58))(
                        *(unsigned long *)(param_1 + 0x10));
        FUN_003a160c((long *)loc40, (unsigned long)*(unsigned long *)(param_1 + 8), (unsigned long)v1);
    }
    return loc40[0];
}
/* FUN_003a2044 @ 0x003a2044   (est. cnode/object field accessor)
 * Ghidra: undefined4 FUN_003a2044(long param_1)
 * Reads a 32-bit field at offset +0x24 of the object reached via (param_1+8)->+0x28,
 * after validating the pointer's tag at +0x10 (zero or a back-pointer sentinel makes it
 * invalid and yields 0). Returns the requested count/limit field, else 0.
 * Confidence: medium
 * Notes: sentinel check `(long)*(int*)(p+0x10) == -0x10 - p` is the cL4 tagged-pointer
 * validity test (tag pointing to -0x10 before the base). */
unsigned int FUN_003a2044(long obj)
{
    long inner;
    long valid;
    inner = *(long *)(*(long *)(obj + 8) + 0x28);
    valid = inner;
    if (inner == 0) {
        valid = 0;
    }
    if (*(int *)(valid + 0x10) == 0 || (long)*(int *)(valid + 0x10) == -0x10 - valid) {
        return 0;
    }
    if (inner == 0) {
        inner = 0;
    }
    return *(unsigned int *)(inner + 0x24);
}
/* FUN_003a20cc @ 0x003a20cc   (est. tagged array indexed read)
 * Ghidra: undefined8 FUN_003a20cc(long param_1,ulong param_2)
 * Indexes a 64-bit element array held by the object at param_1+8. Bounds-checks the
 * index against the count field at (+0x28)->+0x24, takes a lock via FUN_0006e064, then
 * computes the element base (offset table at +0x28; a flag bit at +0x28's +3 selects
 * whether an indirect base from FUN_0036f878 is added). Fails closed on out-of-range or
 * lock failure by trapping.
 * Confidence: medium
 * Notes: SoftwareBreakpoint(1,0x3a21a0) noreturn trap on the failure path;
 * extraout_x1 models the x1 (hi) half of FUN_0036f878's 128-bit result. */
unsigned long FUN_003a20cc(long param_1, unsigned long index)
{
    long base;
    int locked;
    long table;
    unsigned int off;
    cL4_w16_t h;

    base = *(long *)(param_1 + 8);
    if (((-1 < (long)index) && (index <= *(unsigned int *)(*(long *)(base + 0x28) + 0x24))) &&
        (locked = FUN_0006e064(base), locked != 0)) {
        table = *(long *)(base + 0x28);
        if (table == 0) {
            table = 0;
        }
        if ((*(unsigned char *)(table + 3) >> 5 & 1) == 0) {
            off = *(unsigned int *)(table + 0x28);
        } else {
            h = FUN_0036f878();
            off = *(int *)(table + 0x28) + (int)(h.hi >> 3);
        }
        return *(unsigned long *)(base + (unsigned long)off * 8 + index * 8);
    }
    /* noreturn fail-closed trap (brk #1) */
    CL4_SW_BP(0x3a21a0);
    return 0;
}
/* FUN_003a21a0 @ 0x003a21a0   (est. descriptor build returning uninitialized padding)
 * Ghidra: undefined1  [16] FUN_003a21a0(long param_1,undefined8 param_2,undefined8 *param_3,undefined8 *param_4)
 * Calls FUN_003a160c to fill a 16-byte pair from (param_1+8); stores the low word into
 * *param_3 and 0 into *param_4. The 16-byte return value is mostly uninitialized
 * (11 garbage bytes) with the top 5 bytes zeroed.
 * Confidence: low
 * Notes: auVar1._0_11_/._11_5_ are 16-byte return-slot sub-slices; local_30 is
 * uninitialized, so the returned low bytes are undefined — represented as 0 here. */
cL4_w16_t FUN_003a21a0(long param_1, unsigned long param_2, unsigned long *param_3, unsigned long *param_4)
{
    unsigned long loc40[2];
    cL4_w16_t ret;

    FUN_003a160c((long *)loc40, (unsigned long)*(unsigned long *)(param_1 + 8), (unsigned long)0);
    *param_3 = loc40[0];
    *param_4 = 0;
    ret.lo = 0; /* original returns 11 uninitialized bytes here (local_30) */
    ret.hi = 0; /* bytes 11..15 zeroed (auVar1._11_5_ = 0) */
    return ret;
}
/* FUN_003a21f4 @ 0x003a21f4   (est. vtable dispatch accumulate+emit)
 * Ghidra: void FUN_003a21f4(undefined8 param_1,long *param_2,undefined8 param_3)
 * Dispatches two vtable methods on param_2 (at +0x18 returning a 16-byte value, and at
 * +0x10 returning a long), sums the +0x10 result with the value at param_2[2], and
 * passes it plus the low word and masked (hi & 0xffffff) high word of the +0x18 result
 * to FUN_003a1b0c.
 * Confidence: medium
 * Notes: auVar3 is a 16-byte (w16) vtable method return; 0xffffff mask on the high word. */
void FUN_003a21f4(unsigned long param_1, long *param_2, unsigned long param_3)
{
    cL4_w16_t v;
    long n;
    long m;

    v = (*(cL4_w16_t (**)(void))(*param_2 + 0x18))();
    n = *(long *)param_2[2];
    m = (*(long (**)(long *, unsigned long))(*param_2 + 0x10))(param_2, param_3);
    FUN_003a1b0c((unsigned long *)param_1, (long *)n + m, (long *)v.lo, (unsigned long)v.hi & 0xffffff);
}
/* FUN_003a2290 @ 0x003a2290   (est. recursive chain size/accumulate)
 * Ghidra: long FUN_003a2290(long *param_1)
 * If the object has a deeper link (FUN_003a2468), builds a sub-descriptor via
 * FUN_003a24d0, recurses into it to get the nested total, and adds it to this object's
 * +0x08 vtable method result. Otherwise just returns the +0x08 method result.
 * Confidence: medium
 * Notes: FUN_003a2468 is called with param_1 — the decompiler dropped the argument;
 * the indirect jump at 0x003a2328 is a vtable dispatch (+0x08). */
long FUN_003a2290(long *obj)
{
    long stackbuf[3];
    long sub;
    long cur;

    if (FUN_003a2468((long)obj) != 0) {
        FUN_003a24d0((long *)stackbuf, (long)obj);
        sub = FUN_003a2290((long *)stackbuf);
        cur = (*(long (**)(long *))(*obj + 8))(obj);
        return cur + sub;
    }
    cur = (*(long (**)(long *))(*obj + 8))(obj);
    return cur;
}
/* FUN_003a232c @ 0x003a232c   (est. recursive subtract-then-dispatch)
 * Ghidra: void FUN_003a232c(long *param_1,long param_2)
 * Subtracts the nested chain total (FUN_003a2290 over a sub-descriptor) from the given
 * amount; if the amount is smaller than the nested total, recurses with the sub-descriptor
 * and returns. Otherwise dispatches the +0x10 vtable method with the remaining amount.
 * Confidence: medium
 * Notes: FUN_003a2468 arg dropped by decompiler (passes param_1). */
void FUN_003a232c(long *obj, long amount)
{
    long stackbuf[3];
    long sub;
    long rem;

    rem = amount;
    if (FUN_003a2468((long)obj) != 0) {
        FUN_003a24d0((long *)stackbuf, (long)obj);
        sub = FUN_003a2290((long *)stackbuf);
        rem = amount - sub;
        if (amount < sub) {
            FUN_003a232c((long *)stackbuf, (long)amount);
            return;
        }
    }
    (*(void (**)(long *, long))(*obj + 0x10))(obj, rem);
}
/* FUN_003a23b4 @ 0x003a23b4   (est. recursive subtract-then-dispatch, 4-arg)
 * Ghidra: void FUN_003a23b4(long *param_1,long param_2,undefined8 param_3,undefined8 param_4)
 * Same subtract/consume pattern as FUN_003a232c but dispatches the +0x18 vtable method
 * with the remaining amount plus two extra arguments; recurses into the sub-descriptor
 * when the amount is below the nested total.
 * Confidence: medium
 * Notes: FUN_003a2468 arg dropped by decompiler (passes param_1). */
void FUN_003a23b4(long *obj, long amount, unsigned long param_3, unsigned long param_4)
{
    long stackbuf[3];
    long sub;
    long rem;

    rem = amount;
    if (FUN_003a2468((long)obj) != 0) {
        FUN_003a24d0((long *)stackbuf, (long)obj);
        sub = FUN_003a2290((long *)stackbuf);
        rem = amount - sub;
        if (amount < sub) {
            FUN_003a23b4((long *)stackbuf, (long)amount, (unsigned long)param_3, (unsigned long)param_4);
            return;
        }
    }
    (*(void (**)(long *, long, unsigned long, unsigned long))(*obj + 0x18))(obj, rem, param_3, param_4);
}
/* FUN_003a2468 @ 0x003a2468   (est. has-deeper-link predicate)
 * Ghidra: bool FUN_003a2468(long param_1)
 * Reports whether the object has a valid deeper chain link: the tag at (+0x28)->+0x14
 * must be valid (nonzero and not the -0x14 back-pointer sentinel) and the link pointer
 * at (param_1+8)->+8 must be nonzero.
 * Confidence: medium
 * Notes: shared sentinel validity test with FUN_003a2044/24d0; return collapses to true
 * when the final link pointer was already verified nonzero. */
bool FUN_003a2468(long obj)
{
    long inner;
    int tag;
    long link;

    inner = *(long *)(*(long *)(obj + 8) + 0x28);
    tag = *(int *)(inner + 0x14);
    if ((tag != 0 && (long)tag != -0x14 - inner) &&
        (link = *(long *)(*(long *)(obj + 8) + 8), link != 0)) {
        return link != 0;
    }
    return false;
}
/* FUN_003a24d0 @ 0x003a24d0   (est. build sub-descriptor)
 * Ghidra: void FUN_003a24d0(undefined8 *param_1,long param_2)
 * Validates the +0x14 tag and the link pointer at (param_2+8)->+8; on success writes a
 * 3-word descriptor into *param_1: vtable 0x67c230, the link pointer, and 0. Fails
 * closed by trapping if validation fails.
 * Confidence: medium
 * Notes: SoftwareBreakpoint(1,0x3a2554) noreturn trap on failure; 0x67c230 is a literal
 * vtable/object address, kept as a constant. */
void FUN_003a24d0(long *out, long obj)
{
    long inner;
    int tag;
    long link;

    inner = *(long *)(*(long *)(obj + 8) + 0x28);
    tag = *(int *)(inner + 0x14);
    if (((tag != 0 && (long)tag != -0x14 - inner) &&
        (link = *(long *)(*(long *)(obj + 8) + 8), link != 0)) && (link != 0)) {
        out[0] = 0x67c230;
        out[1] = link;
        out[2] = 0;
        return;
    }
    /* noreturn fail-closed trap (brk #1) */
    CL4_SW_BP(0x3a2554);
}
/* FUN_003a2554 @ 0x003a2554   (est. thread-local function-pointer dispatch)
 * Ghidra: void FUN_003a2554(void)
 * Calls through a function pointer held in thread-local storage (__thread_vars).
 * Confidence: low
 * Notes: __thread_vars is a Ghidra TLS-variable artifact; the target is determined by
 * TLS, not statically. */
void FUN_003a2554(void)
{
    (*(void (**)(void))__thread_vars)();
}
/* FUN_003a2578 @ 0x003a2578   (est. indirect result fetch)
 * Ghidra: undefined8 FUN_003a2578(undefined8 param_1)
 * Calls FUN_00369b18 with (0, param_1, frame-pointer artifact) and returns the first
 * word of the object it points at.
 * Confidence: low
 * Notes: &stack0x00000000 is the caller's frame-pointer artifact — modeled as 0. */
unsigned long FUN_003a2578(unsigned long param_1)
{
    unsigned long *p;

    p = (unsigned long *)FUN_00369b18(0, param_1, 0);
    return *p;
}
/* FUN_003a25a0 @ 0x003a25a0   (est. first-word getter)
 * Ghidra: undefined8 FUN_003a25a0(undefined8 *param_1)
 * Returns the first 64-bit word of the pointed-to object.
 * Confidence: high
 * Notes: trivial load. */
unsigned long FUN_003a25a0(unsigned long *param_1)
{
    return *param_1;
}
/* FUN_003a25b8 @ 0x003a25b8   (est. first-word getter)
 * Ghidra: undefined8 FUN_003a25b8(undefined8 *param_1)
 * Returns the first 64-bit word of the pointed-to object.
 * Confidence: high
 * Notes: trivial load; identical shape to FUN_003a25a0. */
unsigned long FUN_003a25b8(unsigned long *param_1)
{
    return *param_1;
}
/* FUN_003a25d4 @ 0x003a25d4   (est. address-mask release)
 * Ghidra: void FUN_003a25d4(ulong param_1)
 * Passes the input masked with 0x8ffffffffffffff8 (clearing low tag bits and top bits)
 * to FUN_0036b118, discarding the result.
 * Confidence: medium
 * Notes: the 0x8...8 mask strips a capability tag/pac bits; likely an object release. */
void FUN_003a25d4(unsigned long param_1)
{
    FUN_0036b118(param_1 & 0x8ffffffffffffff8);
}
/* FUN_003a25e0 @ 0x003a25e0   (est. address-mask release returning input)
 * Ghidra: ulong FUN_003a25e0(ulong param_1)
 * Passes the input masked with 0x8ffffffffffffff8 to FUN_0036b2d0, then returns the
 * original (unmasked) input value.
 * Confidence: medium
 * Notes: companion to FUN_003a25d4; returns the pre-mask pointer. */
unsigned long FUN_003a25e0(unsigned long param_1)
{
    FUN_0036b2d0(param_1 & 0x8ffffffffffffff8);
    return param_1;
}
/* FUN_003a2610 @ 0x003a2610   (est. release/clear of a masked object pointer)
 * Ghidra: void FUN_003a2610(ulong param_1)
 * Clears the low tag bits of the passed pointer by masking it with
 * 0x8ffffffffffffff8 (keeping the object/VA bits, dropping capability-tag and
 * low-address bits) and handing the result to FUN_0036b340. A thin mask-and-delegate
 * wrapper with no other side effects.
 * Confidence: medium
 * Notes: literal mask constant 0x8ffffffffffffff8. */
void FUN_003a2610(unsigned long p)
{
    FUN_0036b340(p & 0x8ffffffffffffff8);
}
/* FUN_003a261c @ 0x003a261c   (est. capability-tag validity check)
 * Ghidra: bool FUN_003a261c(long param_1)
 * Reads the capability tag word at offset +8 of the given object. If the tag is
 * negative (a special/indirect tag), a value of exactly -1 means "absent" (returns
 * false); otherwise the tag is an index into a table at base 0x10, and validity is
 * the table entry having both bit 0x100000000 clear and its upper 0x3f bits zero.
 * A non-negative tag is valid when its upper 32 bits are zero. Returns whether the
 * tag denotes a valid, present capability.
 * Confidence: medium
 * Notes: tag table access `*(ulong *)(tag * 8 + 0x10)`. */
bool FUN_003a261c(long p)
{
    unsigned long tag;
    bool ok;

    tag = *(unsigned long *)(p + 8);
    if ((long)tag < 0) {
        if ((int)tag == -1) {
            return false;
        }
        tag = *(unsigned long *)(tag * 8 + 0x10);
        ok = (tag & 0x100000000) == 0 && tag >> 0x21 == 0;
    }
    else {
        ok = tag >> 0x20 == 0;
    }
    return ok;
}
/* FUN_003a265c @ 0x003a265c   (est. capability-tag validity check, null-safe)
 * Ghidra: bool FUN_003a265c(long param_1)
 * Same tag-validity test as FUN_003a261c but guards against a null object pointer
 * first: a null input yields false without touching memory. A tag of exactly -1 is
 * treated as absent (false); otherwise the indirect-tag table entry is checked for
 * bit 0x100000000 clear and a zero upper 0x3f bits, or for non-negative tags simply
 * a zero upper 32 bits.
 * Confidence: medium
 * Notes: mirrors FUN_003a261c plus the param_1 != 0 guard. */
bool FUN_003a265c(long p)
{
    unsigned long tag;
    bool ok;

    ok = false;
    if (p != 0) {
        tag = *(unsigned long *)(p + 8);
        if ((long)tag < 0) {
            if ((int)tag == -1) {
                return false;
            }
            tag = *(unsigned long *)(tag * 8 + 0x10);
            ok = (tag & 0x100000000) == 0 && tag >> 0x21 == 0;
        }
        else {
            ok = tag >> 0x20 == 0;
        }
    }
    return ok;
}
/* FUN_003a26a0 @ 0x003a26a0   (est. capability-tag validity check on masked pointer)
 * Ghidra: bool FUN_003a26a0(ulong param_1)
 * Same tag-validity test as FUN_003a261c, but first masks the input pointer with
 * 0x8ffffffffffffff8 before dereferencing the tag word at +8. Used to validate a
 * capability pointer that carries tag/low-address bits. Returns false for an absent
 * (-1) tag and for an invalid indirect-table entry.
 * Confidence: medium
 * Notes: mask 0x8ffffffffffffff8 applied before the tag load. */
bool FUN_003a26a0(unsigned long p)
{
    unsigned long tag;
    bool ok;

    tag = *(unsigned long *)((p & 0x8ffffffffffffff8) + 8);
    if ((long)tag < 0) {
        if ((int)tag == -1) {
            return false;
        }
        tag = *(unsigned long *)(tag * 8 + 0x10);
        ok = (tag & 0x100000000) == 0 && tag >> 0x21 == 0;
    }
    else {
        ok = tag >> 0x20 == 0;
    }
    return ok;
}
/* FUN_003a26e8 @ 0x003a26e8   (est. per-object code-stub emitter / patch setup)
 * Ghidra: undefined8 FUN_003a26e8(long param_1)
 * If the object is null, or its capability tag denotes an empty/valid-present entry
 * (absent -1 tag, or a valid table entry), returns 0 and does nothing. Otherwise it
 * obtains a scratch buffer handle via FUN_003a27f0, selects a code-emit mode with
 * FUN_004b9ccc(2), and if FUN_00369b0c() is nonzero fills a 128-byte buffer with a
 * hand-encoded AArch64 instruction stub (11 instruction words, base = local_80) and
 * hands it to thunk_FUN_00369b04. Finally it notifies FUN_004b9d68(1,handle) and
 * frees the handle, returning 1 to signal that a stub was emitted.
 * Confidence: low
 * Notes: code words are raw AArch64; mapped code[0]=local_80 .. code[10]=local_30.
 * The 16-word buffer is only partially populated (indices 0..10). */
unsigned long FUN_003a26e8(long obj)
{
    int sel;
    unsigned long tag;
    unsigned long handle;
    unsigned long code[16];

    if (obj == 0) {
        return 0;
    }
    tag = *(unsigned long *)(obj + 8);
    if ((long)tag < 0) {
        if (((int)tag != -1) &&
            (tag = *(unsigned long *)(tag * 8 + 0x10),
             tag >> 0x21 == 0 && (tag & 0x100000000) == 0))
            return 0;
    }
    else if (tag >> 0x20 == 0) {
        return 0;
    }
    FUN_003a27f0((unsigned long *)&handle);
    FUN_004b9ccc(2);
    sel = FUN_00369b0c();
    if (sel != 0) {
        code[0] = 0x52808001910023e0;   /* local_80 */
        code[1] = 0x710196df94000340;   /* uStack_78 */
        code[2] = 0x71019edf540005a0;   /* uStack_70 */
        code[3] = 0x71019adf54000240;   /* uStack_68 */
        code[4] = 0x39400288540007c1;   /* local_60 */
        code[5] = 0x940001c937000048;   /* uStack_58 */
        code[6] = 0x340000a879400688;   /* uStack_50 */
        code[7] = 0x540000607101b11f;   /* uStack_48 */
        code[8] = 0x54000ee17101311f;   /* local_40 */
        code[9] = 0xfd400100940001cc;   /* uStack_38 */
        code[10] = 0x940001df940001af;  /* local_30 */
        thunk_FUN_00369b04(1, handle, code);
    }
    FUN_004b9d68(1, handle);
    thunk_FUN_00012568(handle);
    return 1;
}
/* FUN_003a27f0 @ 0x003a27f0   (est. formatted-string buffer allocation)
 * Ghidra: void FUN_003a27f0(long *param_1)
 * Allocates and formats a string buffer into *param_1. First measures the formatted
 * length of the log format via FUN_00116bb4(NULL, 0, ...); if the length is
 * non-negative, allocates length+1 bytes (tag 0x100004077774924), reformats into the
 * buffer, and stores it in *param_1. On format error the buffer is freed and *param_1
 * stays 0; if the length is negative *param_1 is initialized to 0.
 * Confidence: medium
 * Notes: format string s_log_fmt = "%.*s: file %.*s, line %u, column %u". */
void FUN_003a27f0(unsigned long *out)
{
    int n;
    long p;
    void *dummy_va;

    n = FUN_00116bb4((void *)0, (unsigned long)0, (char *)s_log_fmt, &dummy_va);
    *out = 0;
    if (n > -1) {
        p = (long)FUN_000101a0((unsigned long)(n + 1), 0x100004077774924);
        if (p != 0) {
            n = FUN_00116bb4((void *)p, (unsigned long)(n + 1), (char *)s_log_fmt, &dummy_va);
            if (n < 0) {
                thunk_FUN_00012568((unsigned long)p);
            }
            else {
                *out = (unsigned long)p;
            }
        }
    }
}
/* FUN_003a2898 @ 0x003a2898   (est. range [start, start+len) getter)
 * Ghidra: undefined1  [16] FUN_003a2898(long param_1)
 * Reads two 32-bit fields at offsets +0x14 and +0x18 of the object and returns them
 * as a 128-bit range: the low word is the zero-extended start (offset +0x14) and the
 * high word is the zero-extended length (end at +0x18 minus start). A pure accessor
 * producing a (start, length) pair.
 * Confidence: high
 * Notes: 16-byte return modeled as cL4_w16_t (.lo=start, .hi=length). */
cL4_w16_t FUN_003a2898(long p)
{
    unsigned long start;
    cL4_w16_t r;

    start = (unsigned long)*(unsigned int *)(p + 0x14);
    r.lo = start;
    r.hi = (unsigned long)*(unsigned int *)(p + 0x18) - start;
    return r;
}
/* FUN_003a28a8 @ 0x003a28a8   (est. empty no-op stub)
 * Ghidra: void FUN_003a28a8(void)
 * A do-nothing function that immediately returns. Likely a placeholder or a void
 * callback slot that requires no work in this build.
 * Confidence: high
 * Notes: empty body. */
void FUN_003a28a8(void)
{
    return;
}
/* FUN_003a28ac @ 0x003a28ac   (est. formatted-print into fixed 0x400 buffer)
 * Ghidra: void FUN_003a28ac(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4)
 * Formats the string given by param_4 into a caller-provided buffer (param_1) with a
 * maximum size of 0x400 bytes using FUN_00116bb4. param_2 and param_3 are unused by
 * the body. The result of the formatting call is discarded.
 * Confidence: medium
 * Notes: only args 1 and 4 are consumed; size constant 0x400. */
void FUN_003a28ac(unsigned long arg1, unsigned long arg2, unsigned long arg3, unsigned long fmt)
{
    void *dummy_va;

    FUN_00116bb4((void *)arg1, (unsigned long)0x400, (char *)fmt, &dummy_va);
}
/* FUN_003a28e8 @ 0x003a28e8   (est. small-vector capacity computation)
 * Ghidra: ulong FUN_003a28e8(ulong param_1,long param_2)
 * Computes a grown capacity for a small-vector. If param_1 fits in 32 bits and the
 * current capacity param_2 is not the -1 sentinel, it bumps param_1 up to
 * param_2*2+1 when smaller, clamps to 0xffffffff, and returns it. Otherwise it raises
 * a fatal panic ("SmallVector capacity overflow during allocation" for a 64-bit
 * request, or "SmallVector capacity unable to grow" for the -1 sentinel), which never
 * returns.
 * Confidence: high
 * Notes: panic FUN_004ba3a8 is noreturn; a defensive `return 0` follows for the
 * compiler. Strings recovered verbatim from the binary. */
unsigned long FUN_003a28e8(unsigned long param_1, long param_2)
{
    char *pc1;

    if (param_1 >> 0x20 == 0) {
        if (param_2 != 0xffffffff) {
            if (param_1 < (unsigned long)((param_2 << 1) | 1U)) {
                param_1 = (unsigned long)(param_2 * 2 + 1);
            }
            if (0xfffffffe < param_1) {
                param_1 = 0xffffffff;
            }
            return param_1;
        }
        pc1 = (char *)s_smallvec_unable;
    }
    else {
        pc1 = (char *)s_smallvec_overflow;
    }
    /* FUN_004ba3a8 does not return */
    FUN_004ba3a8(pc1, 1);
    return 0;
}
/* FUN_003a294c @ 0x003a294c   (est. small-vector grow / reallocate)
 * Ghidra: void FUN_003a294c(long *param_1,long param_2,undefined8 param_3,long param_4)
 * Grows a small-vector buffer. Computes the new capacity with FUN_003a28e8 from the
 * request and the stored capacity at offset +0xc, then the new byte size. If the
 * current buffer is the inline/static buffer (param_2), allocates fresh (tag
 * 0x8c556d9c), copies the old contents (count * elem_size), and on failure allocates a
 * single byte when size is 0. Otherwise reallocates in place (tag 0x48319b8). On
 * success updates the buffer pointer and stored capacity; on allocation failure panics
 * with "Allocation failed".
 * Confidence: medium
 * Notes: copy FUN_00117cc8; panic FUN_004ba3a8 is noreturn. */
void FUN_003a294c(unsigned long *buf, long static_buf, unsigned long req_cap, long elem_size)
{
    unsigned long newcap;
    long nbytes;
    long newbuf;

    newcap = FUN_003a28e8((unsigned long)req_cap, (long)*(int *)((long)buf + 0xc));
    nbytes = newcap * elem_size;
    if (*buf == (unsigned long)static_buf) {
        newbuf = (long)FUN_000101a0((unsigned long)nbytes, 0x8c556d9c);
        if (newbuf == 0) {
            if (nbytes != 0) {
                /* FUN_004ba3a8 does not return */
                FUN_004ba3a8((char *)s_alloc_failed, 1);
                return;
            }
            nbytes = 1;
            newbuf = (long)FUN_000101a0(1, 0x8c556d9c);
            if (newbuf == 0) {
                /* FUN_004ba3a8 does not return */
                FUN_004ba3a8((char *)s_alloc_failed, 1);
                return;
            }
        }
        FUN_00117cc8((void *)newbuf, (void *)*buf,
                     elem_size * (unsigned long)*(unsigned int *)(buf + 1),
                     (unsigned long)nbytes);
    }
    else {
        newbuf = (long)FUN_000102f4((void *)*buf, (unsigned long)nbytes, 0x48319b8);
        if ((newbuf == 0) &&
            ((nbytes != 0 || (newbuf = (long)FUN_000101a0(1, 0x8c556d9c), newbuf == 0)))) {
            /* FUN_004ba3a8 does not return */
            FUN_004ba3a8((char *)s_alloc_failed, 1);
            return;
        }
    }
    *buf = (unsigned long)newbuf;
    *(int *)((long)buf + 0xc) = (int)newcap;
}
/* FUN_003a2a38 @ 0x003a2a38   (est. small-vector grow with capacity field)
 * Ghidra: void FUN_003a2a38(long *param_1,long param_2,ulong param_3,long param_4)
 * Grows a small-vector whose capacity lives at buf[2]. A stored capacity of -1 is
 * fatal ("SmallVector capacity unable to grow"). Otherwise the request is bumped to
 * cur*2+1 when smaller, giving a byte size of cap*elem_size. If the buffer is the
 * inline/static buffer it is freshly allocated (tag 0x8c556d9c) and copied
 * (count*elem_size bytes); else reallocated in place (tag 0x48319b8). A zero-size
 * request allocates a single byte. On success the pointer and capacity are updated;
 * on failure it panics with "Allocation failed".
 * Confidence: medium
 * Notes: panic FUN_004ba3a8 is noreturn. */
void FUN_003a2a38(unsigned long *buf, long static_buf, unsigned long req_cap, long elem_size)
{
    long cur_cap;
    long nbytes;
    long newbuf;

    cur_cap = (long)buf[2];
    if (cur_cap == -1) {
        /* FUN_004ba3a8 does not return */
        FUN_004ba3a8((char *)s_smallvec_unable, 1);
        return;
    }
    if (req_cap < (unsigned long)((cur_cap << 1) | 1U)) {
        req_cap = (unsigned long)(cur_cap * 2 + 1);
    }
    nbytes = req_cap * elem_size;
    if (*buf == (unsigned long)static_buf) {
        newbuf = (long)FUN_000101a0((unsigned long)nbytes, 0x8c556d9c);
        if (newbuf != 0) {
            FUN_00117cc8((void *)newbuf, (void *)*buf, buf[1] * elem_size, (unsigned long)nbytes);
            *buf = (unsigned long)newbuf;
            buf[2] = req_cap;
            return;
        }
        if (nbytes == 0) {
            nbytes = 1;
            newbuf = (long)FUN_000101a0(1, 0x8c556d9c);
            if (newbuf != 0) {
                FUN_00117cc8((void *)newbuf, (void *)*buf, buf[1] * elem_size, (unsigned long)nbytes);
                *buf = (unsigned long)newbuf;
                buf[2] = req_cap;
                return;
            }
        }
    }
    else {
        newbuf = (long)FUN_000102f4((void *)*buf, (unsigned long)nbytes, 0x48319b8);
        if (newbuf != 0 ||
            (nbytes == 0 && (newbuf = (long)FUN_000101a0(1, 0x8c556d9c), newbuf != 0))) {
            *buf = (unsigned long)newbuf;
            buf[2] = req_cap;
            return;
        }
    }
    /* FUN_004ba3a8 does not return */
    FUN_004ba3a8((char *)s_alloc_failed, 1);
}
/* FUN_003a2b38 @ 0x003a2b38   (est. optimized large-memory copy)
 * Ghidra: void FUN_003a2b38(long param_1,long param_2)
 * Copies param_2 bytes from param_1 using an optimized, buffer-assisted path when the
 * length exceeds 0x40 bytes: it initializes a 56-byte workspace and copies in 0x40-byte
 * blocks via FUN_0037e58c/FUN_0037e614, finishes any trailing partial block from the
 * end, and finalizes with FUN_0037eb4c. Short copies (<= 0x40 bytes) fall through to
 * the simple FUN_0037e8e8. End pointer is param_1+param_2.
 * Confidence: medium
 * Notes: workspace is 56 bytes; constant 0xf9000a63a9000a61 passed to FUN_0037e58c. */
void FUN_003a2b38(long src, long len)
{
    unsigned long total;
    unsigned long remaining;
    unsigned long work[7];

    len = src + len;
    total = len - src;
    if (0x40 < total) {
        remaining = total & 0xffffffffffffffc0;
        FUN_0037e58c(work, (unsigned long)src, 0xf9000a63a9000a61);
        do {
            remaining -= 0x40;
            if (remaining == 0) {
                break;
            }
            src += 0x40;
            FUN_0037e614(work, (unsigned long)src);
        } while (1);
        if ((total & 0x3f) != 0) {
            FUN_0037e614(work, (unsigned long)(len - 0x40));
        }
        FUN_0037eb4c(work, total);
        return;
    }
    FUN_0037e8e8((unsigned long)src, total);
}
/* FUN_003a2c18 @ 0x003a2c18   (est. object constructor / allocate + init)
 * Ghidra: undefined8 * FUN_003a2c18(undefined8 *param_1)
 * Allocates a 0x240-byte object (tag 0x10f1c40caa97c64) and initializes it: the
 * leading type/kind pointer to the literal 0x67c398, the size field at word 4 to
 * 0x960, and clears a large contiguous region of 8-byte words (indices 0xb..0x42 plus
 * the byte at +0x30, the short at +0x50 and the int at +0x218). Stores the new object
 * in *param_1 and returns param_1.
 * Confidence: medium
 * Notes: literal type pointer 0x67c398; bulk zeroing reproduced field-by-field as in
 * the decompile. */
unsigned long * FUN_003a2c18(unsigned long *out)
{
    unsigned long *obj;

    obj = (unsigned long *)FUN_00111890(0x240, 0x10f1c40caa97c64);
    obj[1] = 0;
    obj[2] = 0;
    obj[3] = 0;
    obj[4] = 0x960;
    obj[5] = 0;
    *(unsigned char *)(obj + 6) = 0;
    obj[0] = 0x67c398;
    obj[0x47] = 0;
    obj[8] = 0;
    obj[9] = 0;
    obj[7] = 0;
    *(unsigned short *)(obj + 10) = 0;
    obj[0xe] = 0;
    obj[0xd] = 0;
    obj[0x10] = 0;
    obj[0xf] = 0;
    obj[0x12] = 0;
    obj[0x11] = 0;
    obj[0x14] = 0;
    obj[0x13] = 0;
    obj[0x16] = 0;
    obj[0x15] = 0;
    obj[0x18] = 0;
    obj[0x17] = 0;
    obj[0x1a] = 0;
    obj[0x19] = 0;
    obj[0x1c] = 0;
    obj[0x1b] = 0;
    obj[0x1e] = 0;
    obj[0x1d] = 0;
    obj[0x20] = 0;
    obj[0x1f] = 0;
    *(unsigned int *)(obj + 0x43) = 0;
    *out = (unsigned long)obj;
    obj[0xc] = 0;
    obj[0xb] = 0;
    obj[0x22] = 0;
    obj[0x21] = 0;
    obj[0x24] = 0;
    obj[0x23] = 0;
    obj[0x26] = 0;
    obj[0x25] = 0;
    obj[0x28] = 0;
    obj[0x27] = 0;
    obj[0x2a] = 0;
    obj[0x29] = 0;
    obj[0x2c] = 0;
    obj[0x2b] = 0;
    obj[0x2e] = 0;
    obj[0x2d] = 0;
    obj[0x30] = 0;
    obj[0x2f] = 0;
    obj[0x32] = 0;
    obj[0x31] = 0;
    obj[0x34] = 0;
    obj[0x33] = 0;
    obj[0x36] = 0;
    obj[0x35] = 0;
    obj[0x38] = 0;
    obj[0x37] = 0;
    obj[0x3a] = 0;
    obj[0x39] = 0;
    obj[0x3c] = 0;
    obj[0x3b] = 0;
    obj[0x3e] = 0;
    obj[0x3d] = 0;
    obj[0x40] = 0;
    obj[0x3f] = 0;
    obj[0x42] = 0;
    obj[0x41] = 0;
    return out;
}
/* FUN_003a2cf0 @ 0x003a2cf0   (est. vtable-method invoke / object finalize)
 * Ghidra: long * FUN_003a2cf0(long *param_1)
 * If the object's first word is non-null, treats it as a vtable pointer and invokes
 * the method stored at vtable+8 (the second slot) with no arguments. Returns the
 * object pointer unchanged. A small dispatch/finalization helper.
 * Confidence: medium
 * Notes: indirect call `(**(code **)(*(long *)*param_1 + 8))()` modeled via a
 * function-pointer typedef. */
long * FUN_003a2cf0(long *obj)
{
    fn_void cb;

    if (*obj != (long)0) {
        cb = (fn_void)(*(unsigned long *)(*obj + 8));
        cb();
    }
    return obj;
}
/* FUN_003a2d38 @ 0x003a2d38   (est. wrapper around an out-of-object message decode)
 * Ghidra: undefined8 FUN_003a2d38(undefined8 *param_1,undefined8 param_2,undefined8 param_3)
 * Thin wrapper: forwards *param_1 plus two args to FUN_003a3e54 into a 24-byte stack
 * slot, destroys that slot with FUN_00362ea4, and returns the caller's status. The
 * stack guard (0x2c8502b44bfffed6) is validated at return and trips the noreturn trap
 * FUN_0011d7e8 if corrupted.
 * Confidence: medium
 * Notes: stack-protector pattern; local_30 is set but never used. */
unsigned long FUN_003a2d38(unsigned long *param_1, unsigned long param_2, unsigned long param_3)
{
    unsigned long ret;
    unsigned char slot[24];
    long stack_guard;
    unsigned long loc30;

    stack_guard = -0x2c8502b44bfffed6;
    loc30 = 0;
    ret = FUN_003a3e54((long)*param_1, (short *)param_2, (unsigned long)param_3, (unsigned long)slot);
    FUN_00362ea4(slot);
    if (stack_guard == -0x2c8502b44bfffed6) {
        return ret;
    }
    FUN_0011d7e8(); /* noreturn */
    return 0;       /* unreachable: stack-guard trap */
}
/* FUN_003a2da8 @ 0x003a2da8   (est. install/decode a message into an object descriptor)
 * Ghidra: void FUN_003a2da8(undefined8 *param_1,undefined8 *param_2,undefined8 param_3,undefined8 param_4,undefined8 param_5)
 * Decodes *param_2 with params 3-4 via FUN_003a3e54 into a 24-byte slot, destroys the
 * slot, then depending on the status either forwards the saved word pair into the
 * descriptor at param_1 or reports failure through FUN_003bc9a4/FUN_0037364c. On a
 * negative kind byte it releases a masked copy of the message via thunk_FUN_00012568.
 * Confidence: low
 * Notes: CONCAT17(bStack_41,local_48) is the 8 bytes spanning the local_48/bStack_41
 * stack region (low 7 + sign byte); stack-guard trap FUN_0011d7e8 at return. */
void FUN_003a2da8(unsigned long *param_1, unsigned long *param_2, unsigned long param_3,
                  unsigned long param_4, unsigned long param_5)
{
    unsigned long v1;
    long status;
    unsigned char slot[24];      /* local_58,uStack_50,local_48,bStack_41 region */
    unsigned long loc68;
    unsigned long uStack_60;
    long stack_guard;

    stack_guard = -0x2c8502b44bfffed6;
    loc68 = param_3;
    uStack_60 = param_4;
    status = FUN_003a3e54((long)*param_2, (short *)param_3, (unsigned long)param_4, (unsigned long)slot);
    FUN_00362ea4(slot);
    if (status == 0) {
        FUN_0037364c(param_1, &loc68);
    } else {
        FUN_003bc9a4(slot, status, param_5);
        v1 = *(unsigned long *)(slot + 8);           /* uStack_50 */
        if (-1 < (char)slot[23]) {                       /* bStack_41 sign check */
            v1 = (unsigned long)slot[23];
        }
        if (v1 == 0) {
            FUN_0037364c(param_1, &loc68);
            if ((char)slot[23] < 0) {
                /* CONCAT17(bStack_41, local_48) with top sign bit cleared */
                thunk_FUN_00012568(*(unsigned long *)(slot + 0),
                                   *(unsigned long *)(slot + 16) & 0x7fffffffffffffff);
            }
        } else {
            param_1[1] = *(unsigned long *)(slot + 8);  /* uStack_50 */
            param_1[0] = *(unsigned long *)(slot + 0);  /* local_58 */
            param_1[2] = *(unsigned long *)(slot + 16); /* CONCAT17 */
        }
    }
    if (stack_guard == -0x2c8502b44bfffed6) {
        return;
    }
    FUN_0011d7e8(); /* noreturn stack-guard trap */
}
/* FUN_003a2e9c @ 0x003a2e9c   (est. allocate + initialise a descriptor object)
 * Ghidra: void FUN_003a2e9c(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4)
 * Allocates a 0x240-byte object via FUN_00111890, zero-fills most fields, stamps the
 * type marker 0x67c398 at offset 0 and an 0x960 word at [4], then calls FUN_003a2da8 to
 * decode param_2..4 into the caller descriptor at param_1. Finally dispatches through a
 * method table: calls the function pointer stored at *(0x67c398+8) with the object.
 * Confidence: low
 * Notes: huge zero-init block preserved verbatim; indirect jump through object vtable
 * (0x67c398+8) rendered as a call; FUN_003a2da8 is a same-chunk callee. */
void FUN_003a2e9c(unsigned long *param_1, unsigned long param_2, unsigned long param_3,
                  unsigned long param_4)
{
    long *obj;
    long *loc48;

    obj = (long *)FUN_00111890(0x240, 0x10f1c40caa97c64);
    obj[1] = 0;
    obj[2] = 0;
    obj[3] = 0;
    obj[4] = 0x960;
    obj[5] = 0;
    *(unsigned char *)(obj + 6) = 0;
    *obj = 0x67c398;
    obj[0x47] = 0;
    obj[8] = 0;
    obj[9] = 0;
    obj[7] = 0;
    *(unsigned short *)(obj + 10) = 0;
    obj[0xe] = 0;
    obj[0xd] = 0;
    obj[0x10] = 0;
    obj[0xf] = 0;
    obj[0x12] = 0;
    obj[0x11] = 0;
    obj[0x14] = 0;
    obj[0x13] = 0;
    obj[0x16] = 0;
    obj[0x15] = 0;
    obj[0x18] = 0;
    obj[0x17] = 0;
    obj[0x1a] = 0;
    obj[0x19] = 0;
    obj[0x1c] = 0;
    obj[0x1b] = 0;
    obj[0x1e] = 0;
    obj[0x1d] = 0;
    obj[0x20] = 0;
    obj[0x1f] = 0;
    *(unsigned int *)(obj + 0x43) = 0;
    obj[0xc] = 0;
    obj[0xb] = 0;
    obj[0x22] = 0;
    obj[0x21] = 0;
    obj[0x24] = 0;
    obj[0x23] = 0;
    obj[0x26] = 0;
    obj[0x25] = 0;
    obj[0x28] = 0;
    obj[0x27] = 0;
    obj[0x2a] = 0;
    obj[0x29] = 0;
    obj[0x2c] = 0;
    obj[0x2b] = 0;
    obj[0x2e] = 0;
    obj[0x2d] = 0;
    obj[0x30] = 0;
    obj[0x2f] = 0;
    obj[0x32] = 0;
    obj[0x31] = 0;
    obj[0x34] = 0;
    obj[0x33] = 0;
    obj[0x36] = 0;
    obj[0x35] = 0;
    obj[0x38] = 0;
    obj[0x37] = 0;
    obj[0x3a] = 0;
    obj[0x39] = 0;
    obj[0x3c] = 0;
    obj[0x3b] = 0;
    obj[0x3e] = 0;
    obj[0x3d] = 0;
    obj[0x40] = 0;
    obj[0x3f] = 0;
    obj[0x42] = 0;
    obj[0x41] = 0;
    loc48 = obj;
    FUN_003a2da8((unsigned long *)param_1, (unsigned long *)&loc48, (unsigned long)param_2, (unsigned long)param_3, (unsigned long)param_4);
    /* indirect dispatch: (**(code **)(*obj + 8))(obj) */
    ((void (*)(long *))*(unsigned long *)((unsigned long)*obj + 8))(obj);
}
/* FUN_003a2fd4 @ 0x003a2fd4   (est. validate a node/kind code against allowed ranges)
 * Ghidra: undefined8 FUN_003a2fd4(undefined8 param_1,undefined8 param_2,undefined8 param_3)
 * Builds a 24-byte local via FUN_003d2b40, then asks FUN_004ba5a4 for a status code and
 * tests whether that code lies in a set of legal values encoded as bitmasks over
 * sub-ranges: [0x48,0x86), [0,0x40), [0x96,0xc1), [0xd7,0x10f), [0x144,0x17a). Returns 1
 * if the code is in any legal set, else 0. param_1/param_2 are unused on this path.
 * Confidence: low
 * Notes: classic sparse-switch legality check via shift+mask; the 16-byte return is
 * modelled as cL4_w16_t even though only the caller's usage matters here. The string at
 * 0x5d68d5 is the "assertion failed for Node" format used as an argument label. */
cL4_w16_t FUN_003a2fd4(unsigned long param_1, unsigned long param_2, unsigned long param_3)
{
    unsigned long v1;
    unsigned long ok;
    unsigned int v3;
    unsigned long v4;
    unsigned char loc58[24];

    FUN_003d2b40(loc58, param_3);
    v1 = FUN_004ba5a4(0, "assertion failed for Node");   /* string @0x5d68d5 */
    ok = 1;
    v3 = (unsigned int)v1;
    if ((int)v3 < 0x96) {
        if ((v3 - 0x48 < 0x3e) &&
            ((1L << ((unsigned long)(v3 - 0x48) & 0x3f) & 0x2c04000650000043U) != 0)) {
            return (cL4_w16_t){ .lo = ok, .hi = 0 };
        }
        if (0x3f < v3) {
            return (cL4_w16_t){ .lo = 0, .hi = 0 };
        }
        v4 = 0x8030000542200003;
    } else {
        if ((v3 - 0x96 < 0x2b) &&
            ((1L << ((unsigned long)(v3 - 0x96) & 0x3f) & 0x7c03803f801U) != 0)) {
            return (cL4_w16_t){ .lo = ok, .hi = 0 };
        }
        if ((v3 - 0xd7 < 0x38) &&
            ((1L << ((unsigned long)(v3 - 0xd7) & 0x3f) & 0x930000c0039003U) != 0)) {
            return (cL4_w16_t){ .lo = ok, .hi = 0 };
        }
        v1 = (unsigned long)(v3 - 0x144);
        if (0x35 < v3 - 0x144) {
            return (cL4_w16_t){ .lo = 0, .hi = 0 };
        }
        v4 = 0x30000000000801;
    }
    if ((1L << (v1 & 0x3f) & v4) != 0) {
        return (cL4_w16_t){ .lo = ok, .hi = 0 };
    }
    return (cL4_w16_t){ .lo = 0, .hi = 0 };
}
/* FUN_003a3040 @ 0x003a3040   (est. validate a code value against allowed ranges)
 * Ghidra: undefined8 FUN_003a3040(uint param_1)
 * Returns 1 if param_1 lies in any of the legality sets encoded as shift/mask bitmaps
 * over the sub-ranges [0x48,0x86), [0,0x40), [0x96,0xc1), [0xd7,0x10f), [0x144,0x17a),
 * otherwise 0. This is the direct (non-querying) sibling of FUN_003a2fd4.
 * Confidence: medium
 * Notes: pure sparse-switch legality check; no side effects. */
unsigned long FUN_003a3040(unsigned int param_1)
{
    unsigned long ok;
    unsigned long v2;

    ok = 1;
    if ((int)param_1 < 0x96) {
        if ((param_1 - 0x48 < 0x3e) &&
            ((1L << ((unsigned long)(param_1 - 0x48) & 0x3f) & 0x2c04000650000043U) != 0)) {
            return ok;
        }
        if (0x3f < param_1) {
            return 0;
        }
        v2 = 0x8030000542200003;
    } else {
        if ((param_1 - 0x96 < 0x2b) &&
            ((1L << ((unsigned long)(param_1 - 0x96) & 0x3f) & 0x7c03803f801U) != 0)) {
            return ok;
        }
        if ((param_1 - 0xd7 < 0x38) &&
            ((1L << ((unsigned long)(param_1 - 0xd7) & 0x3f) & 0x930000c0039003U) != 0)) {
            return ok;
        }
        param_1 = param_1 - 0x144;
        if (0x35 < param_1) {
            return 0;
        }
        v2 = 0x30000000000801;
    }
    if ((1L << ((unsigned long)param_1 & 0x3f) & v2) != 0) {
        return ok;
    }
    return 0;
}
/* FUN_003a3124 @ 0x003a3124   (est. validate a tag/selector against allowed ranges)
 * Ghidra: undefined8 FUN_003a3124(int param_1)
 * Returns 1 if param_1 is one of the legal values encoded as shift/mask bitmaps over
 * [0x37,0x63), [0x14e,0x177), [0x99,0xb6), [0x10d,0x12f); else 0.
 * Confidence: medium
 * Notes: sparse-switch legality check, pure. */
unsigned long FUN_003a3124(int param_1)
{
    unsigned int v1;
    unsigned long ok;
    unsigned long v3;

    ok = 1;
    if (param_1 < 0x99) {
        v1 = param_1 - 0x37;
        if (0x2b < v1) {
            return 0;
        }
        v3 = 0xdc6010000ef;
    } else {
        if ((param_1 - 0x14eU < 0x29) &&
            ((1L << ((unsigned long)(param_1 - 0x14eU) & 0x3f) & 0x18000206e01U) != 0)) {
            return ok;
        }
        if ((param_1 - 0x99U < 0x1d) &&
            ((1 << (param_1 - 0x99U & 0x1f) & 0x18220001U) != 0)) {
            return ok;
        }
        v1 = param_1 - 0x10d;
        if (0x21 < v1) {
            return 0;
        }
        v3 = 0x300400001;
    }
    if ((1L << ((unsigned long)v1 & 0x3f) & v3) == 0) {
        return 0;
    }
    return ok;
}
/* FUN_003a31d8 @ 0x003a31d8   (est. walk a length-prefixed UTF-8-ish string)
 * Ghidra: void FUN_003a31d8(byte *param_1)
 * Advances a pointer through a NUL-terminated string. Each element contributes an
 * encoded advance: bytes with (b & 0xf8) == 0x18 advance 8, else 0; if the byte is
 * >0x17 the advance is that value, otherwise 4; plus 1 for the element. Stops at NUL.
 * Confidence: low
 * Notes: no explicit length bound on the buffer being walked -- caller must guarantee
 * the string is terminated before running off the end (potential OOB read). */
void FUN_003a31d8(unsigned char *param_1)
{
    long step8;
    long step;
    unsigned char bv3;

    if (param_1 != (unsigned char *)0x0) {
        bv3 = *param_1;
        while (bv3 != 0) {
            step8 = 8;
            if ((bv3 & 0xf8) != 0x18) {
                step8 = 0;
            }
            step = 4;
            if (0x17 < bv3) {
                step = step8;
            }
            param_1 = param_1 + step + 1;
            bv3 = *param_1;
        }
    }
}
/* FUN_003a3224 @ 0x003a3224   (est. match a key against a static descriptor table)
 * Ghidra: ulong FUN_003a3224(undefined8 param_1,ulong param_2)
 * Iterates a fixed table at 0x67c2e8 of {name-len, name-ptr} entries (stride 16 bytes,
 * 8 entries): for each entry whose stored length is <= param_2 (and nonzero) compares
 * param_1 against the entry's name pointer via thunk_FUN_001145b0; returns the entry
 * length on the first exact match, else 0.
 * Confidence: low
 * Notes: literal table address 0x67c2e8 kept as a constant; puVar3[-1] is the name ptr
 * preceding the length word. */
unsigned long FUN_003a3224(unsigned long param_1, unsigned long param_2)
{
    int cmp;
    unsigned long len;
    unsigned long *entry;
    long remaining;

    if (param_2 != 0) {
        entry = (unsigned long *)0x67c2e8;
        remaining = 0x80;
        do {
            len = *entry;
            if (len <= param_2) {
                if (len == 0) {
                    return 0;
                }
                cmp = thunk_FUN_001145b0(param_1, entry[-1], len);
                if (cmp == 0) {
                    return len;
                }
            }
            entry = entry + 2;
            remaining = remaining + -0x10;
        } while (remaining != 0);
    }
    return 0;
}
/* FUN_003a32a0 @ 0x003a32a0   (est. pop an entry from a descriptor's backing array)
 * Ghidra: undefined8 FUN_003a32a0(long param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4)
 * Builds a temp slot (FUN_003b0f48/FUN_003a3d18/FUN_00362ea4/FUN_003a3de4) around the
 * given args, then checks the descriptor's element count (int at +0x60). If nonzero,
 * pops the top element from the array at *(param_1+0x58): returns the value, decrements
 * the count, and if the next element is non-null it re-pops once more (and yields 0).
 * Confidence: low
 * Notes: two-level pop; +0x58 is the element array, +0x60 the count; stack-guard trap. */
unsigned long FUN_003a32a0(long param_1, unsigned long param_2, unsigned long param_3,
                           unsigned long param_4)
{
    unsigned int v1;
    int count;
    long lv3;
    unsigned long ret;
    unsigned char auStack_c0[32];
    unsigned char auStack_a0[104];
    long stack_guard;

    stack_guard = -0x2c8502b44bfffed6;
    FUN_003b0f48(auStack_c0, param_4);
    FUN_003a3d18((long *)auStack_a0, (long)param_1, (unsigned long)param_2, (unsigned long)param_3, (unsigned long)auStack_c0);
    FUN_00362ea4(auStack_c0);
    count = FUN_003a4094((long)param_1);
    if ((count == 0) || (count = *(int *)(param_1 + 0x60), count == 0)) {
        ret = 0;
    } else {
        v1 = count - 1;
        ret = *(unsigned long *)(*(long *)(param_1 + 0x58) + (unsigned long)v1 * 8);
        *(unsigned int *)(param_1 + 0x60) = v1;
        if ((v1 != 0) &&
            (lv3 = *(long *)(*(long *)(param_1 + 0x58) + (unsigned long)(count - 2U) * 8),
             *(unsigned int *)(param_1 + 0x60) = count - 2U, lv3 != 0)) {
            ret = 0;
        }
    }
    FUN_003a3de4((long *)auStack_a0);
    if (stack_guard != -0x2c8502b44bfffed6) {
        FUN_0011d7e8(); /* noreturn stack-guard trap */
    }
    return ret;
}
/* FUN_003a3380 @ 0x003a3380   (est. teardown/initialise a descriptor)
 * Ghidra: void FUN_003a3380(undefined8 *param_1)
 * Stores the type marker 0x67c398 at *param_1, destroys the slot at param_1+0x44 via
 * FUN_00362ea4, then runs the object teardown FUN_003b0b7c on the descriptor.
 * Confidence: medium
 * Notes: mirrors the initialise path's marker stamping. */
void FUN_003a3380(unsigned long *param_1)
{
    *param_1 = 0x67c398;
    FUN_00362ea4(param_1 + 0x44);
    FUN_003b0b7c(param_1);
}
/* FUN_003a33cc @ 0x003a33cc   (est. validate a capability chain)
 * Ghidra: undefined8 FUN_003a33cc(long *param_1)
 * Walks a singly-linked chain. Each node's kind word (ushort at +16) must be 0xf4
 * (recurse into next), 0x16b, or in (0xbf,0xc1]; anything else fails. For 0xf4 nodes it
 * additionally requires the sub-kind byte at +0x12 to be 0 or 1 (if 2..4 fails; if 5 the
 * count at param_1[1] must be nonzero) before following *param_1. Returns 1 on success,
 * 0 on any invalid node or a NULL chain.
 * Confidence: low
 * Notes: chain-follow; guard against NULL head but not cycle detection. */
unsigned long FUN_003a33cc(long *param_1)
{
    unsigned short kind;

    do {
        if (param_1 == (long *)0x0) {
            return 0;
        }
        kind = *(unsigned short *)(param_1 + 2);
        if (kind != 0xf4) {
            if ((1 < kind - 0xbf) && (kind != 0x16b)) {
                return 0;
            }
            return 1;
        }
        if (1 < *(unsigned char *)((long)param_1 + 0x12) - 1) {
            if (*(unsigned char *)((long)param_1 + 0x12) != 5) {
                return 0;
            }
            if ((int)param_1[1] == 0) {
                return 0;
            }
            param_1 = (long *)*param_1;
        }
        param_1 = (long *)*param_1;
    } while (1);
}
/* FUN_003a3430 @ 0x003a3430   (est. create a leaf descriptor with a payload)
 * Ghidra: void FUN_003a3430(undefined8 param_1,undefined2 param_2)
 * Looks up/allocates a descriptor via FUN_003a3898(param_1, 1), stores the 16-bit value
 * param_2 at +0x10 and clears the kind byte at +0x12.
 * Confidence: medium
 * Notes: thin field initialiser. */
void FUN_003a3430(unsigned long param_1, unsigned short param_2)
{
    long node;

    node = FUN_003a3898((unsigned long)param_1, (unsigned long)1);
    *(unsigned short *)(node + 0x10) = param_2;
    *(unsigned char *)(node + 0x12) = 0;
}
/* FUN_003a3460 @ 0x003a3460   (est. growable-vector push / descriptor append)
 * Ghidra: void FUN_003a3460(uint *param_1,long param_2,undefined8 param_3)
 * Appends element param_2 to the vector described by param_1 (data ptr at +0, count at
 * [2], capacity at [3], kind byte at +0x12). Kind 5 grows then stores at index count.
 * Kind 2 migrates a 3-element inline payload into heap storage then marks kind 5.
 * Kind 0 initialises a single-element inline vector; kind 1 stores one element. When
 * param_2 == 0, instead it reallocates the *caller's* descriptor using the generic grow
 * helper (the "Child" branch), bumping the recorded size.
 * Confidence: low
 * Notes: vector growth via FUN_003b0e1c + FUN_00117cc4 copy; string refs s_Child_005d6a0a
 * and s__AppleInternal_Library_BuildRoot_005d693f appear only as labels. */
void FUN_003a3460(unsigned int *param_1, long param_2, unsigned long param_3)
{
    unsigned long v1;
    unsigned long v2;
    unsigned long v3;
    unsigned char kind;
    long lv5;
    long *pl6;
    char *pc7;
    unsigned char v8;
    unsigned int v9;
    unsigned long v10;
    cL4_w16_t av11;

    if (param_2 == 0) {
        pc7 = "Child";                                   /* s_Child_005d6a0a */
        av11 = FUN_003a2fd4((unsigned long)"AppleInternal Library BuildRoot",
                               0x175, 0);                   /* s__AppleInternal..._005d693f */
        pl6 = (long *)av11.hi;                        /* _8_8_ */
        lv5 = (long)av11.lo;                           /* _0_8_ */
        v9 = *param_1;
        v10 = (unsigned long)v9;
        if ((*pl6 + v10 * 8 == *(long *)(lv5 + 8)) &&
            (v1 = *(long *)(lv5 + 8) + (long)pc7 * 8, v1 <= *(unsigned long *)(lv5 + 0x10))) {
            *(unsigned long *)(lv5 + 8) = v1;
        } else {
            if (pc7 <= (char *)(unsigned long)(v9 << 1)) {
                pc7 = (char *)(unsigned long)(v9 << 1);
            }
            if (pc7 < (char *)0x5) {
                pc7 = (char *)0x4;
            }
            lv5 = FUN_003b0e1c(lv5, (unsigned long)pc7 + v10);
            if (v9 != 0) {
                FUN_00117cc4(lv5, *pl6, v10 << 3);
            }
            *pl6 = lv5;
            v9 = *param_1;
        }
        *param_1 = v9 + (unsigned int)(unsigned long)pc7;
        return;
    }
    kind = *(unsigned char *)((long)param_1 + 0x12);
    if (kind < 2) {
        if (kind == 0) {
            *(long *)param_1 = param_2;
            param_1[2] = 0;
            param_1[3] = 0;
            v8 = 1;
        } else {
            if (kind != 1) {
                return;
            }
            *(long *)(param_1 + 2) = param_2;
            v8 = 2;
        }
    } else {
        if (kind != 2) {
            if (kind != 5) {
                return;
            }
            v9 = param_1[2];                              /* count */
            if (param_1[3] <= v9) {                        /* capacity <= count: grow */
                FUN_003a3578((long)param_3, (long *)param_1, (unsigned int *)param_1 + 3, (unsigned long)1);
                v9 = param_1[2];
            }
            param_1[2] = v9 + 1;
            *(long *)(*(long *)param_1 + (unsigned long)v9 * 8) = param_2;
            return;
        }
        v2 = *(unsigned long *)param_1;                    /* data ptr */
        v3 = *(unsigned long *)(param_1 + 2);              /* long at +8 */
        param_1[0] = 0;
        param_1[1] = 0;
        param_1[2] = 0;
        param_1[3] = 0;
        FUN_003a3578((long)param_3, (long *)param_1, (unsigned int *)param_1 + 3, (unsigned long)3);       /* grow to 3 + count */
        **(unsigned long **)param_1 = v2;
        *(unsigned long *)(*(long *)param_1 + 8) = v3;
        *(long *)(*(long *)param_1 + 0x10) = param_2;
        param_1[2] = 3;
        v8 = 5;
    }
    *(unsigned char *)((long)param_1 + 0x12) = v8;
    return;
}
/* FUN_003a3578 @ 0x003a3578   (est. generic growable-array ensure-capacity)
 * Ghidra: void FUN_003a3578(long param_1,long *param_2,uint *param_3,ulong param_4)
 * Ensures room for param_4 more 8-byte elements in the array described by param_1
 * (capacity at +0x10). If the current end (*param_2 + count*8) equals the recorded end
 * and adding param_4 stays within capacity, just bumps the end. Otherwise reallocates
 * via FUN_003b0e1c to max(count*2, max(param_4,4)) + count, copies the old data, and
 * updates *param_2. Records the new count in *param_3.
 * Confidence: medium
 * Notes: capacity doubling; potential overflow if count/param_4 grow large. */
void FUN_003a3578(long param_1, long *param_2, unsigned int *param_3, unsigned long param_4)
{
    unsigned long v1;
    long lv2;
    unsigned int v3;
    unsigned long v4;

    v3 = *param_3;
    v4 = (unsigned long)v3;
    if ((*param_2 + v4 * 8 == *(long *)(param_1 + 8)) &&
        (v1 = *(long *)(param_1 + 8) + param_4 * 8, v1 <= *(unsigned long *)(param_1 + 0x10))) {
        *(unsigned long *)(param_1 + 8) = v1;
    } else {
        if (param_4 <= v3 << 1) {
            param_4 = (unsigned long)(v3 << 1);
        }
        if (param_4 < 5) {
            param_4 = 4;
        }
        lv2 = FUN_003b0e1c(param_1, param_4 + v4);
        if (v3 != 0) {
            FUN_00117cc4(lv2, *param_2, v4 << 3);
        }
        *param_2 = lv2;
        v3 = *param_3;
    }
    *param_3 = v3 + (unsigned int)param_4;
    return;
}
/* FUN_003a3628 @ 0x003a3628   (est. remove an element from a descriptor array)
 * Ghidra: void FUN_003a3628(long *param_1,uint param_2)
 * Removes element at index param_2 from the array described by param_1. Kind 5 shifts
 * the tail down by one over the gap and decrements the count (param_1[1]). Kind 2 with
 * index 0 repoints the head to param_1[1] and demotes the kind to 1; kind 1 demotes to 0.
 * Confidence: low
 * Notes: array-remove with shift; param_1[1] doubles as count and as the pushed-out
 * element pointer depending on kind. */
void FUN_003a3628(long *param_1, unsigned int param_2)
{
    unsigned int v1;
    char kind;
    unsigned int v3;

    kind = *(char *)((long)param_1 + 0x12);
    if (kind == 5) {
        v3 = (unsigned int)param_1[1] - 1;
        if (param_2 != v3) {
            do {
                v1 = param_2 + 1;
                *(unsigned long *)(*param_1 + (unsigned long)param_2 * 8) =
                     *(unsigned long *)(*param_1 + (unsigned long)v1 * 8);
                param_2 = v1;
            } while (v3 != v1);
            v3 = (unsigned int)param_1[1] - 1;
        }
        *(unsigned int *)(param_1 + 1) = v3;
    } else {
        if (kind == 2) {
            if (param_2 == 0) {
                *param_1 = param_1[1];
            }
            *(unsigned char *)((long)param_1 + 0x12) = 1;
            return;
        }
        if (kind == 1) {
            *(unsigned char *)((long)param_1 + 0x12) = 0;
            return;
        }
    }
    return;
}
/* FUN_003a36a0 @ 0x3a36a0   (est. object-field store by tag kind)
 * Ghidra: void FUN_003a36a0(long *param_1,uint param_2,long param_3)
 * Stores a value into a field of an object whose layout is chosen by the "kind"
 * byte at offset 0x12 of *param_1. Kind 5 stores into an external indirection
 * array (index param_2, 8-byte stride); kind 2 stores into the local array at
 * index param_2; kind 1 stores the whole value at offset 0. param_3 is the value.
 * Confidence: high
 * Notes: kind byte at 0x12 is the same "tag" discriminator used across this layer. */
void FUN_003a36a0(long *param_1, unsigned int param_2, long param_3)
{
    char cv1;

    cv1 = *(char *)((long)param_1 + 0x12);
    if (cv1 == '\x05') {
        *(long *)(*param_1 + (unsigned long)param_2 * 8) = param_3;
        return;
    }
    if (cv1 == '\x02') {
        param_1[param_2] = param_3;
    } else if (cv1 == '\x01') {
        *param_1 = param_3;
        return;
    }
    return;
}
/* FUN_003a36d8 @ 0x3a36d8   (est. value-array element remove / 16-byte rotate)
 * Ghidra: void FUN_003a36d8(undefined1 (*param_1) [16],ulong param_2)
 * Operates on a tagged value whose 16 bytes sit at *param_1; the "kind" byte at
 * offset 0x12 selects the action. Kind 5: remove the element at index param_2 from
 * an external 8-byte-stride array (compact by swapping with the last element).
 * Kind 2 with param_2==0: rotate the 16-byte value left by 8 bytes (swap its two
 * 64-bit halves) and store back into the value's first 16 bytes.
 * Confidence: high
 * Notes: NEON_ext(*param_1,*param_1,8,1) is modelled as a half-swap of the value. */
void FUN_003a36d8(unsigned char (*param_1)[16], unsigned long param_2)
{
    unsigned long *pu1;
    unsigned long *pu2;
    unsigned long *pu3;
    unsigned long *pu4;
    unsigned long v5;
    unsigned long old_lo;
    unsigned long old_hi;

    if (((unsigned char *)param_1)[0x12] == 0x05) {
        pu1 = (unsigned long *)(*(long *)*param_1 + param_2 * 8);
        pu2 = (unsigned long *)((*(long *)*param_1 +
                                    (unsigned long)*(unsigned int *)(*param_1 + 8) * 8) - 8);
        if (param_2 != *(unsigned int *)(*param_1 + 8) && pu1 < pu2) {
            do {
                pu4 = pu1 + 1;
                v5 = *pu1;
                *pu1 = *pu2;
                pu3 = pu2 + -1;
                *pu2 = v5;
                pu2 = pu3;
                pu1 = pu4;
            } while (pu4 < pu3);
        }
    } else if (((unsigned char *)param_1)[0x12] == 0x02 && param_2 == 0) {
        /* NEON_ext(*param_1,*param_1,8,1): rotate 16-byte value left by 8 bytes
           => swap the two 8-byte halves. */
        old_lo = *(unsigned long *)*param_1;        /* bytes 0-7  (auVar6.hi) */
        old_hi = *(unsigned long *)(*param_1 + 8);  /* bytes 8-15 (auVar6.lo) */
        *(long *)(*param_1 + 8) = old_lo;           /* auVar6._8_8_ */
        *(long *)*param_1 = old_hi;                 /* auVar6._0_8_ */
        return;
    }
    return;
}
/* FUN_003a3748 @ 0x3a3748   (est. recursive radix/tree node search by key)
 * Ghidra: ushort * FUN_003a3748(ushort *param_1,undefined8 param_2,int param_3)
 * Recursively searches a tree of tagged nodes for the key param_2. First compares
 * the node's own key at offset 16 with param_2, returning the node on a match. The
 * kind byte at offset 18 (param_1[9]) selects the child layout: kind 1 = single
 * child at offset 0; kind 2 = two children at offsets 0 and 8; kind 5 = an external
 * child array whose start is *param_1 and whose count is at offset 8. Depth is
 * bounded by param_3; returns NULL when exhausted or a zero depth is hit.
 * Confidence: high
 * Notes: recursion depth param_3-1; compares key values narrowed to 32 bits. */
unsigned short *FUN_003a3748(unsigned short *param_1, unsigned long param_2, int param_3)
{
    unsigned char bv1;
    unsigned short *pu2;
    unsigned short *pu3;
    unsigned short *pu4;

    pu3 = param_1 + 8;
    if ((unsigned int)*pu3 == (unsigned int)param_2) {
        return param_1;
    }
    if (param_3 < 1) {
        return (unsigned short *)0x0;
    }
    bv1 = (unsigned char)param_1[9];
    pu4 = param_1;
    if (bv1 - 1 < 2) {
        goto recheck;
    }
    if (bv1 != 5) {
        pu4 = (unsigned short *)0x0;
        goto recheck;
    }
    pu3 = *(unsigned short **)param_1;
    pu4 = pu3;
    pu3 = pu3 + (unsigned long)*(unsigned int *)(param_1 + 4) * 4;
    goto search_loop;

recheck:
    if (bv1 == 1) {
        pu3 = param_1 + 4;
        goto search_loop;
    }
    pu2 = pu4;
    if (bv1 == 2) {
        goto search_step;
    }
    if (bv1 != 5) {
        pu3 = (unsigned short *)0x0;
        goto search_loop;
    }
    pu3 = *(unsigned short **)param_1;
    pu3 = pu3 + (unsigned long)*(unsigned int *)(param_1 + 4) * 4;

search_loop:
    do {
        pu2 = pu4;
        if (pu4 == pu3) {
            return (unsigned short *)0x0;
        }
search_step:
        pu4 = pu2 + 4;
        pu2 = (unsigned short *)FUN_003a3748((unsigned short *)*(unsigned long *)pu2, (unsigned long)param_2, (int)param_3 - 1);
    } while (pu2 == (unsigned short *)0x0);
    return pu2;
}
/* FUN_003a3814 @ 0x3a3814   (est. walk linked list invoking a callback per node)
 * Ghidra: void FUN_003a3814(long *param_1)
 * Walks a singly-linked list where each node's next pointer is at offset 0,
 * invoking thunk_FUN_00012568() once per node after advancing to the next link.
 * The callback (likely a per-node release/free) receives no explicit argument from
 * this loop.
 * Confidence: high
 * Notes: the list head may be NULL (empty list); loop terminates on a NULL link. */
void FUN_003a3814(long *param_1)
{
    while (param_1 != (long *)0x0) {
        param_1 = (long *)*param_1;
        thunk_FUN_00012568();
    }
    return;
}
/* FUN_003a3898 @ 0x3a3898   (est. dynamic buffer slot reserve / grow)
 * Ghidra: void FUN_003a3898(long param_1,long param_2)
 * Reserves space for param_2 fixed-size (0x18-byte) slots in a growable buffer
 * described by param_1. Rounds the current write position at offset 8 up to an
 * 8-byte boundary; if the buffer cannot hold pos+param_2*0x18 bytes, it grows by
 * doubling the capacity field (offset 0x20), allocating a new block via
 * FUN_000101a0 (tag 0x2004093837f09), linking the old block at the new one's
 * offset 0, updating the end pointer at 0x10 and the block head at 0x18. Advances
 * the write position by the requested size.
 * Confidence: high
 * Notes: 0x2004093837f09 is an allocation tag; masks round to 8-byte alignment.
 * Ghidra types the return as void, but every caller uses the returned slot pointer
 * (the aligned write position before the size is added); we return that slot. */
unsigned long FUN_003a3898(unsigned long param_1, unsigned long param_2)
{
    unsigned long *pu1;
    unsigned long v2;
    unsigned long v3;

    param_2 = param_2 * 0x18;
    v2 = (*(long *)(param_1 + 8) + 7U) & 0xfffffffffffffff8ULL;
    *(unsigned long *)(param_1 + 8) = v2;
    if ((v2 == 0) || (*(unsigned long *)(param_1 + 0x10) < v2 + param_2)) {
        v3 = *(long *)(param_1 + 0x20) * 2;
        v2 = param_2 + 8;
        if (v3 < v2 || v3 - v2 == 0) {
            v3 = v2;
        }
        *(unsigned long *)(param_1 + 0x20) = v3;
        pu1 = (unsigned long *)FUN_000101a0(v3 + 8, 0x2004093837f09ULL);
        *pu1 = *(unsigned long *)(param_1 + 0x18);
        v2 = ((unsigned long)pu1 + 0xfU) & 0xfffffffffffffff8ULL;
        *(unsigned long *)(param_1 + 0x10) = (unsigned long)pu1 + v3 + 8;
        *(unsigned long **)(param_1 + 0x18) = pu1;
    }
    *(unsigned long *)(param_1 + 8) = v2 + param_2;
    return (unsigned long)v2;
}
/* FUN_003a3944 @ 0x3a3944   (est. append kind-4 single-payload record)
 * Ghidra: void FUN_003a3944(undefined8 param_1,undefined2 param_2,undefined8 param_3)
 * Reserves one 0x18-byte slot in the growable buffer param_1 and fills it as a
 * record: a 16-bit field at offset 16 holds param_2, the kind byte at offset 18 is
 * set to 4, and the payload at offset 0 is param_3.
 * Confidence: high
 * Notes: slot written via the shared FUN_003a3898 reserve helper. */
void FUN_003a3944(unsigned long param_1, unsigned short param_2, unsigned long param_3)
{
    unsigned long *pu1;

    pu1 = (unsigned long *)FUN_003a3898((unsigned long)param_1, (unsigned long)1);
    *(unsigned short *)(pu1 + 2) = param_2;
    *(unsigned char *)((long)pu1 + 0x12) = 4;
    *pu1 = param_3;
    return;
}
/* FUN_003a3980 @ 0x3a3980   (est. append kind-3 two-payload record)
 * Ghidra: void FUN_003a3980(undefined8 param_1,undefined2 param_2,undefined8 param_3,undefined8 param_4)
 * Reserves one 0x18-byte slot in the growable buffer param_1 and fills it as a
 * record: 16-bit field at offset 16 holds param_2, kind byte at offset 18 is 3,
 * and the two payload words at offsets 0 and 8 hold param_3 and param_4.
 * Confidence: high
 * Notes: slot written via the shared FUN_003a3898 reserve helper. */
void FUN_003a3980(unsigned long param_1, unsigned short param_2, unsigned long param_3, unsigned long param_4)
{
    unsigned long *pu1;

    pu1 = (unsigned long *)FUN_003a3898((unsigned long)param_1, (unsigned long)1);
    *(unsigned short *)(pu1 + 2) = param_2;
    *(unsigned char *)((long)pu1 + 0x12) = 3;
    *pu1 = param_3;
    pu1[1] = param_4;
    return;
}
/* FUN_003a39c8 @ 0x3a39c8   (est. append kind-3 record from a {word,count} source)
 * Ghidra: void FUN_003a39c8(undefined8 param_1,undefined2 param_2,undefined8 *param_3)
 * Copies a {payload, count} pair out of the source *param_3 (a 64-bit word at
 * offset 0 plus a 32-bit count at offset 8), then reserves one 0x18-byte slot in
 * the buffer param_1 and writes a kind-3 record with that pair (offset 0 = word,
 * offset 8 = zero-extended count) and the 16-bit field param_2 at offset 16.
 * Confidence: high
 * Notes: reads the source before reserving the destination slot. */
void FUN_003a39c8(unsigned long param_1, unsigned short param_2, unsigned long *param_3)
{
    unsigned int v1;
    unsigned long *pu2;
    unsigned long v3;

    v3 = *param_3;
    v1 = *(unsigned int *)(param_3 + 1);
    pu2 = (unsigned long *)FUN_003a3898((unsigned long)param_1, (unsigned long)1);
    *(unsigned short *)(pu2 + 2) = param_2;
    *(unsigned char *)((long)pu2 + 0x12) = 3;
    *pu2 = v3;
    pu2[1] = (unsigned long)v1;
    return;
}
/* FUN_003a3a10 @ 0x3a3a10   (est. append kind-3 string record with computed length)
 * Ghidra: long * FUN_003a3a10(undefined8 param_1,undefined2 param_2,long param_3)
 * Reserves one 0x18-byte slot in the buffer param_1 and writes a kind-3 string
 * record: 16-bit field param_2 at offset 16, kind byte 3 at offset 18, the string
 * pointer param_3 at offset 0, and its computed length (via thunk_FUN_00115080, or
 * 0 when param_3 is NULL) at offset 8. Returns the filled slot.
 * Confidence: high
 * Notes: thunk_FUN_00115080 is a string-length helper. */
long *FUN_003a3a10(unsigned long param_1, unsigned short param_2, long param_3)
{
    long *pl1;
    long lv2;

    pl1 = (long *)FUN_003a3898((unsigned long)param_1, (unsigned long)1);
    if (param_3 == 0) {
        lv2 = 0;
    } else {
        lv2 = thunk_FUN_00115080(param_3);
    }
    *(unsigned short *)(pl1 + 2) = param_2;
    *(unsigned char *)((long)pl1 + 0x12) = 3;
    *pl1 = param_3;
    pl1[1] = lv2;
    return pl1;
}
/* FUN_003a3a70 @ 0x3a3a70   (est. append bytes to dynamic buffer)
 * Ghidra: void FUN_003a3a70(long *param_1,undefined8 param_2,long param_3,undefined8 param_4)
 * Appends param_3 bytes copied from param_2 into the growable buffer described by
 * *param_1, growing it via FUN_003a3aec when the current length plus param_3 would
 * exceed the capacity at offset 0xc. Copies through FUN_00117cc4 at the current
 * write position and advances the length field at offset 8 by param_3.
 * Confidence: high
 * Notes: FUN_00117cc4 is a memcpy-style helper (dst, src, n). */
void FUN_003a3a70(long *param_1, unsigned long param_2, long param_3, unsigned long param_4)
{
    unsigned long v1;

    v1 = (unsigned long)*(unsigned int *)(param_1 + 1);
    if ((unsigned long)*(unsigned int *)((long)param_1 + 0xc) < param_3 + v1) {
        FUN_003a3aec((long)param_4, (long *)param_1, (unsigned int *)((long)param_1 + 0xc), (unsigned long)param_3);
        v1 = (unsigned long)*(unsigned int *)(param_1 + 1);
    }
    FUN_00117cc4(*param_1 + v1, param_2, param_3);
    *(int *)(param_1 + 1) = (int)param_1[1] + (int)param_3;
    return;
}
/* FUN_003a3aec @ 0x3a3aec   (est. grow dynamic buffer / ensure capacity)
 * Ghidra: void FUN_003a3aec(long param_1,long *param_2,uint *param_3,ulong param_4)
 * Ensures the buffer described by param_1 can append param_4 more bytes after the
 * current position *param_3 (used-count at *param_2). Fast path: if the used block
 * ends exactly at the buffer's write position (offset 8) and growing fits within
 * the end pointer (offset 0x10), just advance the position. Otherwise double the
 * used count as the new capacity (min 5, floor 4), allocate a larger block via
 * FUN_00365660, copy the old contents across (FUN_00117cc4) when non-empty, and
 * update *param_2 to the new block. Finally bumps *param_3 by param_4.
 * Confidence: high
 * Notes: FUN_00365660 is an allocation/grow helper returning the new block. */
void FUN_003a3aec(long param_1, long *param_2, unsigned int *param_3, unsigned long param_4)
{
    unsigned long v1;
    long lv2;
    unsigned int v3;
    unsigned long v4;

    v3 = *param_3;
    v4 = (unsigned long)v3;
    if ((*param_2 + v4 == *(long *)(param_1 + 8)) &&
        (v1 = *(long *)(param_1 + 8) + param_4,
         v1 <= *(unsigned long *)(param_1 + 0x10))) {
        *(unsigned long *)(param_1 + 8) = v1;
    } else {
        if (param_4 <= v3 << 1) {
            param_4 = (unsigned long)(v3 << 1);
        }
        if (param_4 < 5) {
            param_4 = 4;
        }
        lv2 = FUN_00365660(param_1, param_4 + v4);
        if (v3 != 0) {
            FUN_00117cc4(lv2, *param_2, v4);
        }
        *param_2 = lv2;
        v3 = *param_3;
    }
    *param_3 = v3 + (int)param_4;
    return;
}
/* FUN_003a3b9c @ 0x3a3b9c   (est. append signed integer as decimal text)
 * Ghidra: void FUN_003a3b9c(long *param_1,ulong param_2,undefined8 param_3)
 * Appends the decimal representation of the signed value param_2 into the buffer
 * described by *param_1, growing via FUN_003a3aec if needed (11 bytes). Prepends a
 * '-' when param_2 is negative (taking the two's-complement magnitude), then emits
 * the digits through FUN_003b0ec4, advancing the length by the digit count.
 * Confidence: high
 * Notes: FUN_003b0ec4 formats an unsigned value to digits and returns the count. */
void FUN_003a3b9c(long *param_1, unsigned long param_2, unsigned long param_3)
{
    int iv1;
    unsigned char *pu2;
    unsigned int v3;

    v3 = *(unsigned int *)(param_1 + 1);
    if (*(unsigned int *)((long)param_1 + 0xc) < v3 + 0xb) {
        FUN_003a3aec((long)param_3, (long *)param_1, (unsigned int *)((long)param_1 + 0xc), (unsigned long)0xb);
        v3 = *(unsigned int *)(param_1 + 1);
    }
    pu2 = (unsigned char *)(*param_1 + (unsigned long)v3);
    if ((int)param_2 < 0) {
        *pu2 = 0x2d;
        param_2 = (unsigned long)(unsigned int)-(int)param_2;
        pu2 = pu2 + 1;
    }
    iv1 = FUN_003b0ec4(param_2, pu2);
    *(int *)(param_1 + 1) = (int)param_1[1] + iv1;
    return;
}
/* FUN_003a3c20 @ 0x3a3c20   (est. append unsigned integer as decimal text)
 * Ghidra: void FUN_003a3c20(long *param_1,ulong param_2,undefined8 param_3)
 * Appends the decimal representation of the unsigned value param_2 into the buffer
 * described by *param_1, growing via FUN_003a3aec if needed (0x15 bytes). Special
 * case: param_2==0 emits a single '0'. Otherwise writes the least-significant digit
 * first into the buffer, NUL-terminates, then reverses the digit run in place,
 * advancing the buffer length by the digit count.
 * Confidence: high
 * Notes: digit extraction is decimal, so the reverse step produces big-endian text. */
void FUN_003a3c20(long *param_1, unsigned long param_2, unsigned long param_3)
{
    unsigned char bv1;
    bool bv2;
    int iv3;
    unsigned int v4;
    unsigned char *pbVar5;
    unsigned char *pbVar6;
    unsigned char *pbVar7;

    v4 = *(unsigned int *)(param_1 + 1);
    if (*(unsigned int *)((long)param_1 + 0xc) < v4 + 0x15) {
        FUN_003a3aec((long)param_3, (long *)param_1, (unsigned int *)((long)param_1 + 0xc), (unsigned long)0x15);
        v4 = *(unsigned int *)(param_1 + 1);
    }
    pbVar5 = (unsigned char *)(*param_1 + (unsigned long)v4);
    if (param_2 == 0) {
        pbVar5[0] = 0x30;
        pbVar5[1] = 0;
        iv3 = 1;
    } else {
        iv3 = 0;
        pbVar6 = pbVar5;
        do {
            pbVar7 = pbVar6;
            pbVar6 = pbVar7 + 1;
            *pbVar7 = ((char)param_2 + (char)(param_2 / 10) * -10) | 0x30;
            iv3 = iv3 + 1;
            bv2 = 9 < param_2;
            param_2 = param_2 / 10;
        } while (bv2);
        *pbVar6 = 0;
        if (pbVar5 < pbVar6) {
            do {
                bv1 = *pbVar7;
                *pbVar7 = *pbVar5;
                *pbVar5 = bv1;
                bv2 = pbVar5 + 1 < pbVar7;
                pbVar5 = pbVar5 + 1;
                pbVar7 = pbVar7 + -1;
            } while (bv2);
        }
    }
    *(int *)(param_1 + 1) = (int)param_1[1] + iv3;
    return;
}
/* FUN_003a3d18 @ 0x3a3d18   (est. snapshot capture of an object's mutable state)
 * Ghidra: long * FUN_003a3d18(long *param_1,long param_2,undefined8 param_3,undefined8 param_4,undefined8 param_5)
 * Captures a snapshot of the object at param_2 into the caller's record *param_1:
 * copies the address, several pairs of 64-bit fields (offsets 0x58/0x60, 0x68/0x70,
 * 0x38/0x40, 0x48), the 32-bit field at 0x218, and the sub-structure at 0x220 (via
 * FUN_003b0f48). It then resets the source object: the two field pairs and 0x218 are
 * cleared (re-allocated ids via FUN_003b0e1c and the sentinel DAT_004f2748), 0x38
 * becomes param_3, 0x40 param_4, 0x48 cleared, and 0x220 re-initialised to param_5.
 * Confidence: medium
 * Notes: this is a capture-and-clear ("claim") of a mutable object state region. */
long *FUN_003a3d18(long *param_1, long param_2, unsigned long param_3, unsigned long param_4,
                   unsigned long param_5)
{
    unsigned long v1;
    unsigned long v2;
    long lv3;

    *param_1 = param_2;
    lv3 = *(long *)(param_2 + 0x58);
    param_1[2] = *(long *)(param_2 + 0x60);
    param_1[1] = lv3;
    lv3 = *(long *)(param_2 + 0x68);
    param_1[4] = *(long *)(param_2 + 0x70);
    param_1[3] = lv3;
    *(unsigned int *)(param_1 + 5) = *(unsigned int *)(param_2 + 0x218);
    lv3 = *(long *)(param_2 + 0x38);
    param_1[7] = *(long *)(param_2 + 0x40);
    param_1[6] = lv3;
    param_1[8] = *(long *)(param_2 + 0x48);
    FUN_003b0f48((unsigned long)(param_1 + 9), (unsigned long)(param_2 + 0x220));
    v1 = FUN_003b0e1c(param_2, 0x10);
    *(unsigned long *)(param_2 + 0x58) = v1;
    v1 = DAT_004f2748;
    *(unsigned long *)(param_2 + 0x60) = DAT_004f2748;
    v2 = FUN_003b0e1c(param_2, 0x10);
    *(unsigned long *)(param_2 + 0x68) = v2;
    *(unsigned long *)(param_2 + 0x70) = v1;
    *(unsigned int *)(param_2 + 0x218) = 0;
    *(unsigned long *)(param_2 + 0x38) = param_3;
    *(unsigned long *)(param_2 + 0x40) = param_4;
    *(unsigned long *)(param_2 + 0x48) = 0;
    FUN_003b0fb8((unsigned long)(param_2 + 0x220), param_5);
    return param_1;
}
/* FUN_003a3de4 @ 0x3a3de4   (est. snapshot restore back into the object)
 * Ghidra: long * FUN_003a3de4(long *param_1)
 * Restores the state captured by FUN_003a3d18 back into the object whose address is
 * stored at *param_1: copies back the pairs at offsets 0x58/0x60, 0x68/0x70,
 * 0x38/0x40 and the single fields 0x218 and 0x48, and re-initialises the sub-struct
 * at 0x220 from the snapshot (FUN_003b0fb8). Then releases the snapshot record's
 * sub-struct via FUN_00362ea4 and returns the snapshot pointer.
 * Confidence: medium
 * Notes: inverse of FUN_003a3d18; FUN_00362ea4 tears down/frees the snapshot's data. */
long *FUN_003a3de4(long *param_1)
{
    long lv1;
    long lv2;

    lv1 = *param_1;
    lv2 = param_1[1];
    *(long *)(lv1 + 0x60) = param_1[2];
    *(long *)(lv1 + 0x58) = lv2;
    lv1 = *param_1;
    lv2 = param_1[3];
    *(long *)(lv1 + 0x70) = param_1[4];
    *(long *)(lv1 + 0x68) = lv2;
    lv1 = *param_1;
    *(int *)(lv1 + 0x218) = (int)param_1[5];
    lv2 = param_1[6];
    *(long *)(lv1 + 0x40) = param_1[7];
    *(long *)(lv1 + 0x38) = lv2;
    lv1 = *param_1;
    *(long *)(lv1 + 0x48) = param_1[8];
    FUN_003b0fb8((unsigned long)(lv1 + 0x220), (unsigned long)(param_1 + 9));
    FUN_00362ea4((unsigned long)(param_1 + 9));
    return param_1;
}
/* FUN_003a3e54 @ 0x3a3e54   (est. sk_token_select_finish — parse a selector/value
 *                            pair into a tagged object and coalesce list nodes)
 * Ghidra: long FUN_003a3e54(long param_1,short *param_2,ulong param_3,undefined8 param_4)
 * Sets context flag bytes 0x50/0x51 from the selector (0x6524/0x545f tags), advances
 * the read offset by the selector length, then drains the accumulated token list and
 * folds adjacent (tag==0xe9/0xf4) nodes into a single 0x65-tagged node. Returns the
 * produced node, or 0 if nothing could be produced.
 * Confidence: medium
 * Notes: stack canary (local_58) with FUN_0011d7e8 on mismatch; 0x6524 = 'd$' tag,
 * 0x545f = '_T'. */
long FUN_003a3e54(long param_1, short *param_2, unsigned long param_3, unsigned long param_4)
{
    bool bv1;
    unsigned int v2;
    int iv3;
    long lv4;
    long *pl5;
    unsigned long v6;
    long lv7;
    long lv8;
    long lv9;
    unsigned long *pu10;
    unsigned long auStack_e0[4];
    unsigned long auStack_c0[13];
    long loc58;

    loc58 = -0x2c8502b44bfffed6L;
    FUN_003b0f48(auStack_e0, param_4);
    FUN_003a3d18((long *)auStack_c0, (long)param_1, (unsigned long)param_2, (unsigned long)param_3, (unsigned long)auStack_e0);
    FUN_00362ea4(auStack_e0);
    v2 = FUN_003a3224((unsigned long)param_2, (unsigned long)param_3);
    if (v2 != 0) {
        if (param_3 < 2) {
            bv1 = false;
        } else {
            if (*param_2 == 0x6524) {
                *(unsigned char *)(param_1 + 0x51) = 1;
            }
            bv1 = *param_2 == 0x545f;
        }
        *(bool *)(param_1 + 0x50) = bv1;
        *(unsigned long *)(param_1 + 0x48) =
            (unsigned long)*(long *)(param_1 + 0x48) + (unsigned long)v2;
        iv3 = FUN_003a4094((long)param_1);
        if (iv3 != 0) {
            lv4 = FUN_003a3898((unsigned long)param_1, (unsigned long)1);
            *(unsigned short *)(lv4 + 0x10) = 0x65;
            *(unsigned char *)(lv4 + 0x12) = 0;
            v2 = *(unsigned int *)(param_1 + 0x60);
            v6 = (unsigned long)v2;
            if (v2 != 0) {
                v2 = v2 - 1;
                lv7 = *(long *)(*(long *)(param_1 + 0x58) + (unsigned long)v2 * 8);
                lv8 = lv4;
                if (*(short *)(lv7 + 0x10) != 0xe9) {
                    lv7 = 0;
LAB_003a3f74:
                    do {
                        v2 = (int)v6 - 1;
                        pu10 = *(unsigned long **)(param_1 + 0x58);
                        lv9 = (long)pu10[v2];
                        iv3 = FUN_003a3124((int)*(unsigned short *)(lv9 + 0x10));
                        if (iv3 == 0) {
                            lv9 = v6 << 3;
                            goto LAB_003a3fc0;
                        }
                        *(unsigned int *)(param_1 + 0x60) = v2;
                        FUN_003a3460((unsigned int *)lv8, (long)lv9, (unsigned long)param_1);
                        if ((*(unsigned short *)(lv9 + 0x10) & 0xfffe) != 0xb4) {
                            lv9 = lv8;
                        }
                        lv8 = lv9;
                        v6 = (unsigned long)*(unsigned int *)(param_1 + 0x60);
                    } while (*(unsigned int *)(param_1 + 0x60) != 0);
                    goto LAB_003a4018;
                }
                *(unsigned int *)(param_1 + 0x60) = v2;
                v6 = (unsigned long)v2;
                if (v2 != 0) goto LAB_003a3f74;
                goto LAB_003a401c;
            }
        }
    }
    goto LAB_003a404c;
LAB_003a3fc0:
    do {
        pl5 = (long *)*pu10;
        if ((short)pl5[2] == 0xf4) {
            if (1 < *(unsigned char *)((long)pl5 + 0x12) - 1) {
                if ((*(unsigned char *)((long)pl5 + 0x12) != 5) ||
                    ((int)pl5[1] == 0)) {
                    pl5 = (long *)0;
                    goto LAB_003a4000;
                }
                pl5 = (long *)*pl5;
            }
            pl5 = (long *)*pl5;
        }
LAB_003a4000:
        FUN_003a3460((unsigned int *)lv8, (long)pl5, (unsigned long)param_1);
        pu10 = pu10 + 1;
        lv9 = lv9 + -8;
    } while (lv9 != 0);
LAB_003a4018:
    if (lv7 != 0) {
LAB_003a401c:
        FUN_003a3460((unsigned int *)lv4, (long)lv7, (unsigned long)param_1);
    }
    if ((*(unsigned char *)(lv4 + 0x12) - 1 < 2) ||
        ((*(unsigned char *)(lv4 + 0x12) == 5 && (*(int *)(lv4 + 8) != 0))))
        goto LAB_003a4050;
LAB_003a404c:
    lv4 = 0;
LAB_003a4050:
    FUN_003a3de4((long *)auStack_c0);
    if (loc58 != -0x2c8502b44bfffed6L) {
        /* stack smashing detected — FUN_0011d7e8 is noreturn */
        cL4_runtime_fatal();
    }
    return lv4;
}
/* FUN_003a4094 @ 0x3a4094   (est. sk_token_drain — repeatedly tokenize and emit
 *                            nodes until the buffered stream is exhausted)
 * Ghidra: undefined8 FUN_003a4094(long param_1)
 * Loops while the read offset (param_1+0x48) is below the limit (param_1+0x40) and
 * the current stream byte is nonzero; each iteration tokenizes one node via
 * FUN_003a4180 and pushes it onto the list at param_1+0x58. Returns 0 if a
 * tokenization returned no node, else 1.
 * Confidence: medium
 * Notes: returns 1 (success) / 0 (stopped). */
unsigned long FUN_003a4094(long param_1)
{
    unsigned long v1;
    unsigned long v2;
    long loc28;

    v1 = *(unsigned long *)(param_1 + 0x40);
    v2 = *(unsigned long *)(param_1 + 0x48);
    while ((v2 < v1) &&
           (v2 < *(unsigned long *)(param_1 + 0x40)) &&
           (*(char *)(*(long *)(param_1 + 0x38) + v2) != '\0')) {
        loc28 = FUN_003a4180((long)param_1);
        if (loc28 == 0) {
            return 0;
        }
        FUN_003ad810((unsigned long *)(param_1 + 0x58), &loc28,
                     (unsigned long)param_1);
        v2 = *(unsigned long *)(param_1 + 0x48);
    }
    return 1;
}
/* FUN_003a4110 @ 0x3a4110   (est. sk_token_peek_pop — invoke a per-tag callback on
 *                            the top node and pop it if accepted)
 * Ghidra: undefined8 FUN_003a4110(long param_1,code *param_2)
 * If the stack at param_1+0x60 is non-empty, calls the callback with the tag word of
 * the top node; if the callback returns nonzero and the stack is still non-empty,
 * pops and returns the node, else returns 0.
 * Confidence: medium
 * Notes: callback takes the (unsigned short) tag of node+0x10. */
unsigned long FUN_003a4110(long param_1, int (*param_2)(unsigned short))
{
    unsigned int v1;
    int iv2;
    unsigned long v3;

    if (*(int *)(param_1 + 0x60) != 0) {
        iv2 = (*param_2)(*(unsigned short *)
                            (*(long *)(*(long *)(param_1 + 0x58) +
                                       (unsigned long)(*(int *)(param_1 + 0x60) - 1) * 8)
                             + 0x10));
        if ((iv2 == 0) || (*(int *)(param_1 + 0x60) == 0)) {
            v3 = 0;
        } else {
            v1 = *(int *)(param_1 + 0x60) - 1;
            v3 = *(unsigned long *)(*(long *)(param_1 + 0x58) +
                                       (unsigned long)v1 * 8);
            *(unsigned int *)(param_1 + 0x60) = v1;
        }
        return v3;
    }
    return 0;
}
/* FUN_003a4180 @ 0x3a4180   (est. sk_tokenize — byte-dispatch stream tokenizer)
 * Ghidra: void FUN_003a4180(long param_1)
 * Reads one stream byte and dispatches it to the appropriate token-emit helper or
 * inline node-construction routine. A large set of byte values (0xd-0x6b) fall to a
 * common "invalid/unconsumed" path; opcodes build tagged nodes (tag words like
 * 0x87/0x88/0x89/0x44/0x46/0x11d-0x122 etc.) and push them onto the stack.
 * Ghidra types this void, but the caller (FUN_003a4094) reads its return value, so
 * it is modeled here as returning long; all emit paths are rendered returning 0.
 * Confidence: low
 * Notes: opcode 0x73 emits a 5-byte "Swift" string; opcode 0x48 is a sub-dispatch
 * over a second byte; case 0x2e emits a raw-length node via FUN_00363f70. */
long FUN_003a4180(long param_1)
{
    unsigned long v1;
    unsigned long v2;
    unsigned char bv3;
    int iv4;
    unsigned int *pu5;
    unsigned long *pu6;
    unsigned int v7;
    unsigned long v8;
    unsigned short v9;
    unsigned long v10;
    long lv11;
    unsigned long v12;

    v2 = *(unsigned long *)(param_1 + 0x40);
    v12 = *(unsigned long *)(param_1 + 0x48);
    v1 = v12;
    if (v12 <= v2) {
        v1 = v2;
    }
LAB_003a41a4:
    v10 = v1;
    if (v1 != v12) {
        v10 = v12 + 1;
        *(unsigned long *)(param_1 + 0x48) = v10;
        lv11 = *(long *)(param_1 + 0x38);
        v7 = (unsigned int)*(unsigned char *)(lv11 + v12);
        if (0x79 < v7 - 1) goto code_r0x003a41c8;
        switch (v7) {
        default:
            /* decompile shows FUN_003a5518(param_1) with the selector dropped;
             * any selector outside {1,2,9,0xa,0xb,0xc} yields 0, so pass 0. */
            FUN_003a5518((long)param_1, (int)0);
            return 0;
        case 0xd:
        case 0xe:
        case 0xf:
        case 0x10:
        case 0x11:
        case 0x12:
        case 0x13:
        case 0x14:
        case 0x15:
        case 0x16:
        case 0x17:
        case 0x18:
        case 0x19:
        case 0x1a:
        case 0x1b:
        case 0x1c:
        case 0x1d:
        case 0x1e:
        case 0x1f:
        case 0x20:
        case 0x21:
        case 0x22:
        case 0x23:
        case 0x25:
        case 0x26:
        case 0x27:
        case 0x28:
        case 0x29:
        case 0x2a:
        case 0x2b:
        case 0x2c:
        case 0x2d:
        case 0x2f:
        case 0x30:
        case 0x31:
        case 0x32:
        case 0x33:
        case 0x34:
        case 0x35:
        case 0x36:
        case 0x37:
        case 0x38:
        case 0x39:
        case 0x3a:
        case 0x3b:
        case 0x3c:
        case 0x3d:
        case 0x3e:
        case 0x3f:
        case 0x40:
        case 0x4a:
        case 0x55:
        case 0x5b:
        case 0x5c:
        case 0x5d:
        case 0x5e:
        case 0x60:
        case 0x62:
        case 0x65:
        case 0x6a:
        case 0x6b:
            goto switchD_003a41f4_caseD_d;
        case 0x24:
            FUN_003ac394(param_1);
            return 0;
        case 0x2e:
            v1 = v2;
            if (v12 <= v2) {
                v1 = v12;
            }
            *(unsigned long *)(param_1 + 0x48) = v2;
            FUN_00363f70((unsigned long)param_1, 0xe9, lv11 + (long)v1,
                         v2 - v1);
            return 0;
        case 0x41:
            FUN_003a599c((unsigned long *)param_1);
            return 0;
        case 0x42:
            FUN_003a5aa0((unsigned long *)param_1);
            return 0;
        case 0x43:
            v8 = 0x19;
            break;
        case 0x44:
            FUN_003a4ea4((long)param_1);
            return 0;
        case 0x45:
            FUN_003a613c((unsigned long *)param_1);
            return 0;
        case 0x46:
            FUN_003a61d8((unsigned long *)param_1);
            return 0;
        case 0x47:
            FUN_003a62f8((unsigned long *)param_1);
            return 0;
        case 0x48:
            if (v10 < v2) {
                v12 = v12 + 2;
                *(unsigned long *)(param_1 + 0x48) = v12;
                bv3 = *(unsigned char *)(lv11 + (long)v10);
                v10 = v12;
                if (bv3 < 0x50) {
                    if (bv3 < 0x46) {
                        if (bv3 == 0x41) {
                            FUN_003a63d8((unsigned long *)param_1);
                            return 0;
                        }
                        if (bv3 == 0x43) {
                            FUN_003a644c((unsigned long *)param_1);
                            return 0;
                        }
                        if (bv3 == 0x44) {
                            FUN_003a64f0((unsigned long *)param_1);
                            return 0;
                        }
                    } else {
                        if (bv3 == 0x46) {
                            lv11 = FUN_003a3898((unsigned long)param_1, (unsigned long)1);
                            v9 = 0x159;
                            goto LAB_003a45e8;
                        }
                        if (bv3 == 0x49) {
                            FUN_003a6560((unsigned long *)param_1);
                            return 0;
                        }
                        if (bv3 == 0x4f) {
                            FUN_003a65d4((unsigned long *)param_1);
                            return 0;
                        }
                    }
                } else if (bv3 < 0x6e) {
                    if (bv3 == 0x50) {
                        lv11 = FUN_003a663c((unsigned long *)(unsigned long)param_1);
                        v8 = 0xc2;
                        goto LAB_003a478c;
                    }
                    if (bv3 == 0x58) {
                        lv11 = FUN_003ad478((unsigned long)param_1);
                        v8 = 0x1c;
                        goto LAB_003a478c;
                    }
                    if (bv3 == 99) {
                        lv11 = FUN_003a672c((unsigned long *)(unsigned long)param_1);
                        v8 = 200;
                        goto LAB_003a478c;
                    }
                } else if (bv3 < 0x70) {
                    if (bv3 == 0x6e) {
                        FUN_003a6874((unsigned long *)(unsigned long)param_1, (unsigned long)0xa9);
                        return 0;
                    }
                    if (bv3 == 0x6f) {
                        if (*(int *)(param_1 + 0x60) == 0) {
                            lv11 = 0;
                        } else {
                            v7 = *(int *)(param_1 + 0x60) - 1;
                            lv11 = *(long *)(*(long *)(param_1 + 0x58) +
                                               (unsigned long)v7 * 8);
                            *(unsigned int *)(param_1 + 0x60) = v7;
                        }
                        v8 = 0x13e;
                        goto LAB_003a478c;
                    }
                } else {
                    if (bv3 == 0x70) {
                        lv11 = FUN_003a663c((unsigned long *)(unsigned long)param_1);
                        v8 = 0xc3;
                        goto LAB_003a478c;
                    }
                    if (bv3 == 0x72) {
                        lv11 = FUN_003a663c((unsigned long *)(unsigned long)param_1);
                        v8 = 0xc6;
                        goto LAB_003a478c;
                    }
                }
            }
            lv11 = v10 - 2;
            goto LAB_003a4218;
        case 0x49:
            FUN_003a6c28(param_1);
            return 0;
        case 0x4b:
            lv11 = FUN_003a3898((unsigned long)param_1, (unsigned long)1);
            v9 = 0x11e;
            goto LAB_003a45e8;
        case 0x4c:
            FUN_003a75e4(param_1);
            return 0;
        case 0x4d:
            FUN_003a7818(param_1);
            return 0;
        case 0x4e:
            if (*(int *)(param_1 + 0x60) == 0) {
LAB_003a4760:
                lv11 = 0;
            } else {
                v7 = *(int *)(param_1 + 0x60) - 1;
                lv11 = *(long *)(*(long *)(param_1 + 0x58) + (unsigned long)v7 * 8);
                if (*(short *)(lv11 + 0x10) != 0xf4) goto LAB_003a4760;
                *(unsigned int *)(param_1 + 0x60) = v7;
            }
            v8 = 0xf9;
            goto LAB_003a478c;
        case 0x4f:
            v8 = 0x3f;
            break;
        case 0x50:
            v8 = 0xbf;
            break;
        case 0x51:
            FUN_003a7d9c(param_1);
            return 0;
        case 0x52:
            FUN_003a81e8(param_1);
            return 0;
        case 0x53:
            FUN_003a8868(param_1);
            return 0;
        case 0x54:
            FUN_003a8ab4(param_1);
            return 0;
        case 0x56:
            v8 = 0xe7;
            break;
        case 0x57:
            FUN_003a9944(param_1);
            return 0;
        case 0x58:
            FUN_003aa804(param_1);
            return 0;
        case 0x59:
            FUN_003a56a0((long)param_1);
            return 0;
        case 0x5a:
            if (*(int *)(param_1 + 0x60) == 0) {
LAB_003a47a0:
                lv11 = 0;
            } else {
                v7 = *(int *)(param_1 + 0x60) - 1;
                lv11 = *(long *)(*(long *)(param_1 + 0x58) + (unsigned long)v7 * 8);
                if ((*(short *)(lv11 + 0x10) != 0xf4) &&
                    (iv4 = FUN_003a3040((unsigned int)0), iv4 == 0))
                    goto LAB_003a47a0;
                *(unsigned int *)(param_1 + 0x60) = v7;
            }
            v8 = 0xe6;
            goto LAB_003a478c;
        case 0x5f:
            lv11 = FUN_003a3898((unsigned long)param_1, (unsigned long)1);
            v9 = 0x121;
            goto LAB_003a45e8;
        case 0x61:
            v8 = 0xf6;
            break;
        case 99:
            FUN_003ab218((unsigned long)param_1, 0x54, 0);
            return 0;
        case 100:
            lv11 = FUN_003a3898((unsigned long)param_1, (unsigned long)1);
            v9 = 0x122;
            goto LAB_003a45e8;
        case 0x66:
            FUN_003ab40c(param_1);
            return 0;
        case 0x67:
            FUN_003ab780(param_1);
            return 0;
        case 0x68:
            lv11 = FUN_003a58b0((long)param_1);
            v8 = 0xdc;
            goto LAB_003a477c;
        case 0x69:
            FUN_003ab7f4(param_1);
            return 0;
        case 0x6c:
            v8 = 0;
            goto LAB_003a46cc;
        case 0x6d:
            if (*(int *)(param_1 + 0x60) == 0) {
LAB_003a4770:
                lv11 = 0;
            } else {
                v7 = *(int *)(param_1 + 0x60) - 1;
                lv11 = *(long *)(*(long *)(param_1 + 0x58) + (unsigned long)v7 * 8);
                if (*(short *)(lv11 + 0x10) != 0xf4) goto LAB_003a4770;
                *(unsigned int *)(param_1 + 0x60) = v7;
            }
            v8 = 0x9a;
            goto LAB_003a477c;
        case 0x6e:
            lv11 = FUN_003a58b0((long)param_1);
            v8 = 0xdd;
            goto LAB_003a477c;
        case 0x6f:
            FUN_003abad0(param_1);
            return 0;
        case 0x70:
            lv11 = FUN_003b02dc((unsigned long)param_1);
            goto LAB_003a4780;
        case 0x71:
            lv11 = FUN_003abc48((unsigned long)param_1);
            goto LAB_003a4780;
        case 0x72:
            v8 = 1;
LAB_003a46cc:
            FUN_003ab948((unsigned long)param_1, v8);
            return 0;
        case 0x73:
            pu5 = (unsigned int *)FUN_00365660((unsigned long)param_1, 5);
            *pu5 = 0x66697753;                 /* "Swi" */
            *((unsigned char *)pu5 + 4) = 0x74; /* 't' — "Swift" */
            pu6 = (unsigned long *)FUN_003a3898((unsigned long)param_1, (unsigned long)1);
            *(unsigned short *)(pu6 + 2) = 0xa3;
            *(unsigned char *)((long)pu6 + 0x12) = 3;
            *pu6 = (unsigned long)pu5;
            pu6[1] = 5;
            return 0;
        case 0x74:
            FUN_003abd1c(param_1);
            return 0;
        case 0x75:
            FUN_003abef0(param_1);
            return 0;
        case 0x76:
            v8 = FUN_003b05c8((unsigned long)param_1, 0x10b);
            FUN_003b03c0((unsigned long)param_1, v8);
            return 0;
        case 0x77:
            FUN_003abf88(param_1);
            return 0;
        case 0x78:
            lv11 = FUN_003ac2d0((unsigned long)param_1, 0, 0);
            goto LAB_003a4780;
        case 0x79:
            lv11 = FUN_003a3898((unsigned long)param_1, (unsigned long)1);
            v9 = 0x120;
            goto LAB_003a45e8;
        case 0x7a:
            lv11 = FUN_003a58b0((long)param_1);
            v8 = 0x80;
            goto LAB_003a477c;
LAB_003a45e8:
            *(unsigned short *)(lv11 + 0x10) = v9;
            *(unsigned char *)(lv11 + 0x12) = 0;
            return 0;
LAB_003a477c:
            lv11 = FUN_003a4b38((unsigned long)param_1, (unsigned short)v8, (long)lv11);
LAB_003a4780:
            v8 = 0xf4;
LAB_003a478c:
            FUN_003a4b38((unsigned long)param_1, (unsigned short)v8, (long)lv11);
            return 0;
        }
        FUN_003a6090((unsigned long *)(unsigned long)param_1, (unsigned long)v8);
        return 0;
    }
    goto switchD_003a41f4_caseD_d;
code_r0x003a41c8:
    v12 = v10;
    if (v7 != 0xff) {
switchD_003a41f4_caseD_d:
        lv11 = v10 - 1;
LAB_003a4218:
        *(long *)(param_1 + 0x48) = lv11;
        FUN_003a68a4((unsigned long *)(unsigned long)param_1);
        return 0;
    }
    goto LAB_003a41a4;
}
/* FUN_003a4b38 @ 0x3a4b38   (est. sk_node_single — allocate a 1-child tagged node)
 * Ghidra: long FUN_003a4b38(undefined8 param_1,undefined2 param_2,long param_3)
 * Allocates a node tagged param_2 and, if param_3 is nonzero, links one child
 * (param_3) onto it via FUN_003a3460. Returns the node, or 0 if no child given.
 * Confidence: medium
 * Notes: node layout: tag at +0x10, kind byte at +0x12, child list via FUN_003a3460. */
long FUN_003a4b38(unsigned long param_1, unsigned short param_2, long param_3)
{
    long lv1;

    if (param_3 == 0) {
        lv1 = 0;
    } else {
        lv1 = FUN_003a3898((unsigned long)param_1, (unsigned long)1);
        *(unsigned short *)(lv1 + 0x10) = param_2;
        *(unsigned char *)(lv1 + 0x12) = 0;
        FUN_003a3460((unsigned int *)lv1, (long)param_3, (unsigned long)param_1);
    }
    return lv1;
}
/* FUN_003a4b98 @ 0x3a4b98   (est. sk_node_two — allocate a 2-child tagged node)
 * Ghidra: long FUN_003a4b98(undefined8 param_1,undefined2 param_2,long param_3,long param_4)
 * Allocates a node tagged param_2 and links two children (param_3, param_4) when
 * both are nonzero; returns the node or 0.
 * Confidence: medium */
long FUN_003a4b98(unsigned long param_1, unsigned short param_2,
                  long param_3, long param_4)
{
    long lv1;

    lv1 = 0;
    if ((param_3 != 0) && (param_4 != 0)) {
        lv1 = FUN_003a3898((unsigned long)param_1, (unsigned long)1);
        *(unsigned short *)(lv1 + 0x10) = param_2;
        *(unsigned char *)(lv1 + 0x12) = 0;
        FUN_003a3460((unsigned int *)lv1, (long)param_3, (unsigned long)param_1);
        FUN_003a3460((unsigned int *)lv1, (long)param_4, (unsigned long)param_1);
    }
    return lv1;
}
/* FUN_003a4c14 @ 0x3a4c14   (est. sk_node_three — allocate a 3-child tagged node)
 * Ghidra: long FUN_003a4c14(undefined8 param_1,undefined2 param_2,long param_3,long param_4,long param_5)
 * Allocates a node tagged param_2 and links three children when all are nonzero.
 * Confidence: medium */
long FUN_003a4c14(unsigned long param_1, unsigned short param_2,
                  long p3, long p4, long p5)
{
    long lv1;

    lv1 = 0;
    if (((p3 != 0) && (p4 != 0)) && (p5 != 0)) {
        lv1 = FUN_003a3898((unsigned long)param_1, (unsigned long)1);
        *(unsigned short *)(lv1 + 0x10) = param_2;
        *(unsigned char *)(lv1 + 0x12) = 0;
        FUN_003a3460((unsigned int *)lv1, (long)p3, (unsigned long)param_1);
        FUN_003a3460((unsigned int *)lv1, (long)p4, (unsigned long)param_1);
        FUN_003a3460((unsigned int *)lv1, (long)p5, (unsigned long)param_1);
    }
    return lv1;
}
/* FUN_003a4ca8 @ 0x3a4ca8   (est. sk_node_four — allocate a 4-child tagged node)
 * Ghidra: long FUN_003a4ca8(undefined8 param_1,undefined2 param_2,long param_3,long param_4,long param_5,long param_6)
 * Allocates a node tagged param_2 and links four children when all are nonzero.
 * Confidence: medium */
long FUN_003a4ca8(unsigned long param_1, unsigned short param_2,
                  long p3, long p4, long p5, long p6)
{
    long lv1;

    lv1 = 0;
    if ((((p3 != 0) && (p4 != 0)) && (p5 != 0)) && (p6 != 0)) {
        lv1 = FUN_003a3898((unsigned long)param_1, (unsigned long)1);
        *(unsigned short *)(lv1 + 0x10) = param_2;
        *(unsigned char *)(lv1 + 0x12) = 0;
        FUN_003a3460((unsigned int *)lv1, (long)p3, (unsigned long)param_1);
        FUN_003a3460((unsigned int *)lv1, (long)p4, (unsigned long)param_1);
        FUN_003a3460((unsigned int *)lv1, (long)p5, (unsigned long)param_1);
        FUN_003a3460((unsigned int *)lv1, (long)p6, (unsigned long)param_1);
    }
    return lv1;
}
/* FUN_003a4d5c @ 0x3a4d5c   (est. sk_node_copy — clone a node's payload under a new tag)
 * Ghidra: undefined8 * FUN_003a4d5c(undefined8 param_1,undefined8 *param_2,undefined2 param_3)
 * Allocates a node tagged param_3, copying the payload words (kind-dependent: 1 or 2
 * words, or a derived child list) from source node param_2, and re-links the source's
 * children (per its kind byte at +0x12). Returns 0 if the source is null.
 * Confidence: medium
 * Notes: kind 4/3 copy the leading payload words; kinds 1/2/5 walk the child list. */
unsigned long *FUN_003a4d5c(unsigned long param_1, unsigned long *param_2,
                            unsigned short param_3)
{
    unsigned long v1;
    unsigned char bv2;
    unsigned long *pu3;
    unsigned long *pu4;
    unsigned long *pu5;
    unsigned long v6;

    if (param_2 == (unsigned long *)0) {
        return (unsigned long *)0;
    }
    if (*(char *)((long)param_2 + 0x12) == '\x04') {
        v6 = *param_2;
        pu3 = (unsigned long *)FUN_003a3898((unsigned long)param_1, (unsigned long)1);
        *(unsigned short *)(pu3 + 2) = param_3;
        *(unsigned char *)((long)pu3 + 0x12) = 4;
        *pu3 = v6;
    } else if (*(char *)((long)param_2 + 0x12) == '\x03') {
        v6 = *param_2;
        v1 = param_2[1];
        pu3 = (unsigned long *)FUN_003a3898((unsigned long)param_1, (unsigned long)1);
        *(unsigned short *)(pu3 + 2) = param_3;
        *(unsigned char *)((long)pu3 + 0x12) = 3;
        *pu3 = v6;
        pu3[1] = v1;
    } else {
        pu3 = (unsigned long *)FUN_003a3898((unsigned long)param_1, (unsigned long)1);
        *(unsigned short *)(pu3 + 2) = param_3;
        *(unsigned char *)((long)pu3 + 0x12) = 0;
    }
    bv2 = *(unsigned char *)((long)param_2 + 0x12);
    pu5 = param_2;
    if (bv2 - 1 < 2) {
LAB_003a4e34:
        if (bv2 == 1) {
            pu4 = param_2 + 1;
            goto LAB_003a4e84;
        }
        if (bv2 == 2) {
            pu4 = param_2 + 2;
            goto LAB_003a4e84;
        }
        if (bv2 != 5) {
            pu4 = (unsigned long *)0;
            goto LAB_003a4e84;
        }
        pu4 = (unsigned long *)*param_2;
    } else {
        if (bv2 != 5) {
            pu5 = (unsigned long *)0;
            goto LAB_003a4e34;
        }
        pu4 = (unsigned long *)*param_2;
        pu5 = pu4;
    }
    pu4 = pu4 + *(unsigned int *)(param_2 + 1);
LAB_003a4e84:
    for (; pu5 != pu4; pu5 = pu5 + 1) {
        FUN_003a3460((unsigned int *)(long)pu3, (long)*pu5, (unsigned long)param_1);
    }
    return pu3;
}
/* FUN_003a4ea4 @ 0x3a4ea4   (est. sk_node_emit_pair — pop a stack node, wrap it and a
 *                            resolved node into a 0xf8-tagged 2-child node)
 * Ghidra: long FUN_003a4ea4(long param_1)
 * Pops the top 0xf4-tagged node from the stack (if present), resolves it via
 * FUN_003a4f5c, and builds a 0xf8-tagged node with the resolved node and the popped
 * node as children. Returns the new node (or 0).
 * Confidence: medium
 * Notes: tag 0xf8 node; child order is (resolved, popped). */
long FUN_003a4ea4(long param_1)
{
    unsigned int v1;
    long lv2;
    long lv3;
    long lv4;

    if (*(int *)(param_1 + 0x60) != 0) {
        v1 = *(int *)(param_1 + 0x60) - 1;
        lv4 = *(long *)(*(long *)(param_1 + 0x58) + (unsigned long)v1 * 8);
        if (*(short *)(lv4 + 0x10) == 0xf4) {
            *(unsigned int *)(param_1 + 0x60) = v1;
            goto LAB_003a4ee8;
        }
    }
    lv4 = 0;
LAB_003a4ee8:
    lv2 = FUN_003a4f5c((long)param_1, (long *)lv4);
    lv3 = FUN_003a3898((unsigned long)param_1, (unsigned long)1);
    *(unsigned short *)(lv3 + 0x10) = 0xf8;
    *(unsigned char *)(lv3 + 0x12) = 0;
    if ((lv2 != 0) && (lv3 != 0)) {
        FUN_003a3460((unsigned int *)lv3, (long)lv2, (unsigned long)param_1);
    }
    lv2 = 0;
    if ((lv4 != 0) && (lv3 != 0)) {
        FUN_003a3460((unsigned int *)lv3, (long)lv4, (unsigned long)param_1);
        lv2 = lv3;
    }
    return lv2;
}
/* FUN_003a4f5c @ 0x3a4f5c   (est. sk_node_resolve — reduce a 0xf4 node/list into a
 *                            concrete tagged node per selector)
 * Ghidra: long FUN_003a4f5c(long param_1,long *param_2)
 * Walks the node/child structure of a list node (tags 0xf4/0x2d/0x54/0x43) to select
 * one child, then re-emits a 0x130-tagged node whose children are the selector-matched
 * leaves. Handles list-kind byte 1/2/5 and 0x50-flag mode which switches between the
 * context stack and the passed node. Returns the emitted node (or 0).
 * Confidence: low
 * Notes: deeply nested tag comparison (0x89/0x45/0x87/0x88/0x46/0x11e/0x11f/0x44/0x11d/
 * 0xeb/0xed/0x121/0x67); FUN_003a3628 is an invalid-selector fatal. */
long FUN_003a4f5c(long param_1, long *param_2)
{
    unsigned long v1;
    unsigned long v2;
    unsigned char bv3;
    bool bv4;
    long lv5;
    unsigned long v6;
    unsigned long *pu7;
    unsigned long *pu8;
    unsigned int v9;
    unsigned long *pu10;
    unsigned int v11;
    long *pl12;
    unsigned long v13;
    unsigned long v14;
    unsigned int v15;

    if ((((*(unsigned char *)(param_1 + 0x50) & 1) == 0) &&
         (*(int *)(param_1 + 0x60) != 0)) &&
        (v15 = *(int *)(param_1 + 0x60) - 1,
         *(short *)(*(long *)(*(long *)(param_1 + 0x58) +
                              (unsigned long)v15 * 8) + 0x10) == 0x120)) {
        *(unsigned int *)(param_1 + 0x60) = v15;
LAB_003a4fac:
        lv5 = FUN_003a3898((unsigned long)param_1, (unsigned long)1);
        *(unsigned short *)(lv5 + 0x10) = 0x130;
        *(unsigned char *)(lv5 + 0x12) = 0;
    } else {
        if ((param_2 != (long *)0) && ((short)param_2[2] == 0xf4)) {
            if (*(unsigned char *)((long)param_2 + 0x12) - 1 < 2) {
LAB_003a5000:
                param_2 = (long *)*param_2;
            } else {
                if ((*(unsigned char *)((long)param_2 + 0x12) == 5) &&
                    ((int)param_2[1] != 0)) {
                    param_2 = (long *)*param_2;
                    goto LAB_003a5000;
                }
                param_2 = (long *)0;
            }
            if ((short)param_2[2] == 0x2d) {
                if (*(char *)((long)param_2 + 0x12) == '\x02') {
LAB_003a503c:
                    pu7 = (unsigned long *)param_2[1];
                } else {
                    if ((*(char *)((long)param_2 + 0x12) == '\x05') &&
                        (1 < *(unsigned int *)(param_2 + 1))) {
                        param_2 = (long *)*param_2;
                        goto LAB_003a503c;
                    }
                    pu7 = (unsigned long *)0;
                }
                if (1 < *(unsigned char *)((long)pu7 + 0x12) - 1) {
                    if ((*(unsigned char *)((long)pu7 + 0x12) != 5) ||
                        (*(int *)(pu7 + 1) == 0)) {
                        param_2 = (long *)0;
                        goto LAB_003a5078;
                    }
                    pu7 = (unsigned long *)*pu7;
                }
                param_2 = (long *)*pu7;
            }
LAB_003a5078:
            if (((short)param_2[2] == 0x54) || ((short)param_2[2] == 0x43)) {
                bv3 = *(unsigned char *)((long)param_2 + 0x12);
                v15 = bv3 - 1;
                pl12 = param_2;
                if (1 < v15) {
                    pl12 = (long *)*param_2;
                }
                bv4 = *(short *)(*pl12 + 0x10) == 0x89;
                v11 = (unsigned int)bv4;
                if (v15 < 2) {
                    pl12 = param_2;
                    if (*(short *)(param_2[bv4] + 0x10) == 0x45) {
                        v11 = v11 + 1;
                    }
                } else {
                    pl12 = (long *)*param_2;
                    if (*(short *)(pl12[bv4] + 0x10) == 0x45) {
                        v11 = v11 + 1;
                    }
                }
                if (*(short *)(pl12[v11] + 0x10) == 0x87) {
                    v11 = v11 + 1;
                }
                if (v15 < 2) {
                    if (*(short *)(param_2[v11] + 0x10) == 0x88) {
                        v11 = v11 + 1;
                    }
                    pl12 = param_2;
                    if (*(short *)(param_2[v11] + 0x10) == 0x46) {
                        v11 = v11 + 1;
                    }
                } else {
                    pl12 = (long *)*param_2;
                    if (*(short *)(pl12[v11] + 0x10) == 0x88) {
                        v11 = v11 + 1;
                    }
                    if (*(short *)(pl12[v11] + 0x10) == 0x46) {
                        v11 = v11 + 1;
                    }
                }
                v13 = (unsigned long)v11;
                if (*(short *)(pl12[v13] + 0x10) == 0x11e) {
LAB_003a517c:
                    v13 = (unsigned long)(v11 + 1);
                } else {
                    pl12 = param_2;
                    if (1 < v15) {
                        pl12 = (long *)*param_2;
                    }
                    if (*(short *)(pl12[v13] + 0x10) == 0x11f) goto LAB_003a517c;
                }
                v11 = (unsigned int)v13;
                if (bv3 == 5) {
                    v14 = (unsigned long)*(unsigned int *)(param_2 + 1);
                    if (*(short *)(*(long *)(*param_2 + v13 * 8) + 0x10) == 0x44) {
                        v11 = v11 + 1;
                    }
                    if (*(short *)(*(long *)(*param_2 + (unsigned long)v11 * 8) + 0x10) == 0x11d) {
                        v11 = v11 + 1;
                    }
                    v13 = (unsigned long)v11;
                } else if (bv3 == 2) {
                    if (*(short *)(param_2[v13] + 0x10) == 0x44) {
                        v11 = v11 + 1;
                    }
                    if (*(short *)(param_2[v11] + 0x10) == 0x11d) {
                        v11 = v11 + 1;
                    }
                    v13 = (unsigned long)v11;
                    v14 = 2;
                } else {
                    if (*(short *)(param_2[v13] + 0x10) == 0x44) {
                        v11 = v11 + 1;
                    }
                    v13 = (unsigned long)(*(short *)(param_2[v11] + 0x10) == 0x11d);
                    v14 = 1;
                }
                if (v13 < v14) {
                    if (1 < v15) {
                        param_2 = (long *)*param_2;
                    }
                    pu7 = (unsigned long *)param_2[v13];
                } else {
                    pu7 = (unsigned long *)0;
                }
                pu8 = pu7;
                if (*(unsigned char *)((long)pu7 + 0x12) - 1 < 2) {
LAB_003a5250:
                    pl12 = (long *)*pu8;
                } else {
                    if ((*(unsigned char *)((long)pu7 + 0x12) == 5) &&
                        (*(int *)(pu7 + 1) != 0)) {
                        pu8 = (unsigned long *)*pu7;
                        goto LAB_003a5250;
                    }
                    pl12 = (long *)0;
                }
                if (*(unsigned char *)((long)pl12 + 0x12) - 1 < 2) {
LAB_003a5280:
                    lv5 = *pl12;
                } else {
                    if ((*(unsigned char *)((long)pl12 + 0x12) == 5) &&
                        ((int)pl12[1] != 0)) {
                        pl12 = (long *)*pl12;
                        goto LAB_003a5280;
                    }
                    lv5 = 0;
                }
                if (*(short *)(lv5 + 0x10) == 0xeb) {
                    bv3 = *(unsigned char *)(lv5 + 0x12);
                    v15 = (unsigned int)bv3;
                    if (bv3 != 1) {
                        if (bv3 == 5) {
                            v15 = *(unsigned int *)(lv5 + 8);
                            if (v15 != 0) goto LAB_003a52bc;
                        } else if (bv3 == 2) goto LAB_003a52bc;
                        goto LAB_003a54f4;
                    }
                } else {
                    v15 = 1;
                }
LAB_003a52bc:
                lv5 = FUN_003a3898((unsigned long)param_1, (unsigned long)1);
                *(unsigned short *)(lv5 + 0x10) = 0x130;
                *(unsigned char *)(lv5 + 0x12) = 0;
                if (*(unsigned char *)((long)pu7 + 0x12) - 1 < 2) {
LAB_003a52fc:
                    pl12 = (long *)*pu7;
                } else {
                    if ((*(unsigned char *)((long)pu7 + 0x12) == 5) &&
                        (*(int *)(pu7 + 1) != 0)) {
                        pu7 = (unsigned long *)*pu7;
                        goto LAB_003a52fc;
                    }
                    pl12 = (long *)0;
                }
                if (*(unsigned char *)((long)pl12 + 0x12) - 1 < 2) {
LAB_003a532c:
                    pu7 = (unsigned long *)*pl12;
                } else {
                    if ((*(unsigned char *)((long)pl12 + 0x12) == 5) &&
                        ((int)pl12[1] != 0)) {
                        pl12 = (long *)*pl12;
                        goto LAB_003a532c;
                    }
                    pu7 = (unsigned long *)0;
                }
                if (*(char *)(param_1 + 0x50) == '\x01') {
                    if (pu7 == (unsigned long *)0) {
                        return lv5;
                    }
                    if (*(short *)(pu7 + 2) != 0xeb) {
                        return lv5;
                    }
                }
                v13 = 0;
                v11 = 0;
                bv4 = false;
                do {
                    if (*(char *)(param_1 + 0x50) == '\x01') {
                        bv3 = *(unsigned char *)((long)pu7 + 0x12);
                        v14 = (unsigned long)bv3;
                        v9 = (unsigned int)bv3;
                        if (v9 == 1) {
LAB_003a53cc:
                            if (v14 <= v13) goto LAB_003a53ec;
                            pu8 = pu7;
                            if (1 < v9 - 1) {
                                pu8 = (unsigned long *)*pu7;
                            }
                            pu8 = (unsigned long *)pu8[v13];
                        } else {
                            if (v9 == 5) {
                                v14 = (unsigned long)*(unsigned int *)(pu7 + 1);
                                goto LAB_003a53cc;
                            }
                            if (bv3 == 2) {
                                v14 = 2;
                                goto LAB_003a53cc;
                            }
LAB_003a53ec:
                            pu8 = (unsigned long *)0;
                        }
                        bv3 = *(unsigned char *)((long)pu8 + 0x12);
                        v14 = (unsigned long)bv3;
                        if (bv3 == 1) {
LAB_003a5420:
                            v6 = 0;
                            do {
                                pu10 = pu8;
                                if (1 < bv3 - 1) {
                                    pu10 = (unsigned long *)*pu8;
                                }
                                pu10 = (unsigned long *)pu10[v6];
                                if (*(short *)(pu10 + 2) == 0xed) {
                                    FUN_003a3628((long *)0, (unsigned int)0);
                                    v1 = *pu10;
                                    v2 = pu10[1];
                                    pu8 = (unsigned long *)FUN_003a3898((unsigned long)param_1, (unsigned long)1);
                                    *(unsigned short *)(pu8 + 2) = 0x67;
                                    *(unsigned char *)((long)pu8 + 0x12) = 3;
                                    *pu8 = v1;
                                    pu8[1] = v2;
                                    goto LAB_003a54a0;
                                }
                                v6 = v6 + 1;
                            } while (v14 != v6);
                        } else if (bv3 == 5) {
                            v14 = (unsigned long)*(unsigned int *)(pu8 + 1);
                            if (*(unsigned int *)(pu8 + 1) != 0) goto LAB_003a5420;
                        } else if (bv3 == 2) {
                            v14 = 2;
                            goto LAB_003a5420;
                        }
                        pu8 = (unsigned long *)FUN_003a3898((unsigned long)param_1, (unsigned long)1);
                        *(unsigned short *)(pu8 + 2) = 0x121;
                        *(unsigned char *)((long)pu8 + 0x12) = 0;
                    } else {
                        if (*(int *)(param_1 + 0x60) == 0) goto LAB_003a54f4;
                        v9 = *(int *)(param_1 + 0x60) - 1;
                        pu8 = *(unsigned long **)(*(long *)(param_1 + 0x58) +
                                                     (unsigned long)v9 * 8);
                        *(unsigned int *)(param_1 + 0x60) = v9;
                        if ((pu8 == (unsigned long *)0) ||
                            ((*(short *)(pu8 + 2) != 0x121 &&
                              (*(short *)(pu8 + 2) != 0x67))))
                            goto LAB_003a54f4;
                    }
LAB_003a54a0:
                    FUN_003a3460((unsigned int *)lv5, (long)pu8, (unsigned long)param_1);
                    bv4 = (bool)(bv4 | (*(short *)(pu8 + 2) != 0x121));
                    v11 = v11 + 1;
                    v13 = v13 + 1;
                } while (v11 != v15);
                if (bv4) {
                    if ((*(unsigned char *)(param_1 + 0x50) & 1) != 0) {
                        return lv5;
                    }
                    FUN_003a36d8((unsigned char (*)[16])lv5, (unsigned long)0);
                    return lv5;
                }
                goto LAB_003a4fac;
            }
        }
LAB_003a54f4:
        lv5 = 0;
    }
    return lv5;
}
/* FUN_003a5518 @ 0x3a5518   (est. sk_token_emit_ext — emit an extended token via an
 *                            object-method table)
 * Ghidra: long FUN_003a5518(long param_1,int param_2)
 * Reads a 4-byte payload word from the stream; maps selector param_2 (1/2/9/0xa/0xb/0xc)
 * to a (kind,flags) descriptor and dispatches through the method table at param_1+0x238
 * (vtable+0x30). If the returned node is tagged 0x13c/0x144 it is returned directly,
 * else it is pushed onto the list at param_1+0x68. Returns the node or 0.
 * Confidence: low
 * Notes: indirect call through *( *(param_1+0x238) + 0x30 ); accepts only the listed
 * selector values (else returns 0). */
long FUN_003a5518(long param_1, int param_2)
{
    unsigned long v1;
    long *pl2;
    unsigned int *pu3;
    unsigned char bv4;
    unsigned char bv5;
    unsigned int loc44;
    unsigned int uStack_40;
    unsigned char loc39;
    unsigned int *loc38;
    sk_obj_emit_fn emit_fn;

    v1 = *(long *)(param_1 + 0x48) + 4;
    if (v1 <= *(unsigned long *)(param_1 + 0x40)) {
        loc38 = (unsigned int *)(*(long *)(param_1 + 0x38) + *(long *)(param_1 + 0x48));
        loc44 = *loc38;
        *(unsigned long *)(param_1 + 0x48) = v1;
        if (param_2 < 10) {
            if (param_2 == 1) {
                bv5 = 0; loc39 = 0; uStack_40 = 0; bv4 = 1;
            } else if (param_2 == 2) {
                bv5 = 0; loc39 = 0; bv4 = 1; uStack_40 = 1;
            } else {
                if (param_2 != 9) return 0;
                bv4 = 0; bv5 = 0; uStack_40 = 0; loc39 = 1;
            }
        } else if (param_2 == 10) {
            bv4 = 0; bv5 = 0; uStack_40 = 0; loc39 = 2;
        } else if (param_2 == 0xb) {
            bv4 = 0; bv5 = 0; uStack_40 = 0; loc39 = 3;
        } else {
            if (param_2 != 0xc) return 0;
            bv4 = 0; uStack_40 = 0; loc39 = 4; bv5 = 1;
        }
        pl2 = *(long **)(param_1 + 0x238);
        if (pl2 != (long *)0) {
            emit_fn = *(sk_obj_emit_fn *)(*pl2 + 0x30);
            pu3 = emit_fn(pl2, &loc39, &uStack_40, &loc44, &loc38);
            if (pu3 == (unsigned int *)0) {
                return 0;
            }
            if (!(bool)(bv4 | bv5)) {
                return (long)pu3;
            }
            if (*(short *)(pu3 + 4) == 0x13c) {
                return (long)pu3;
            }
            if (*(short *)(pu3 + 4) == 0x144) {
                return (long)pu3;
            }
            loc38 = pu3;
            FUN_003ad810((unsigned long *)(param_1 + 0x68), (long *)&loc38,
                         (unsigned long)param_1);
            return (long)pu3;
        }
    }
    return 0;
}
/* FUN_003a56a0 @ 0x3a56a0   (est. sk_token_simple — single-byte tag to node)
 * Ghidra: long FUN_003a56a0(long param_1)
 * Reads one stream byte and maps it to a tagged node (tag words 0x87/0x88/0x89/0x11d/
 * 0x44, or 0x45/0x177/0x84/0x155/0x15a/0x86/0x11f via a wrapper that links a popped
 * 0xf4 node). Byte 0x6a routes to FUN_003a5908. Returns the node or 0.
 * Confidence: medium
 * Notes: two-level byte switch; many opcodes consume a following sub-token. */
long FUN_003a56a0(long param_1)
{
    unsigned long v1;
    unsigned char bv2;
    unsigned long v3;
    long lv4;
    unsigned long v5;
    unsigned short v6;

    v1 = *(unsigned long *)(param_1 + 0x48);
    if (*(unsigned long *)(param_1 + 0x40) <= v1) {
        return 0;
    }
    *(unsigned long *)(param_1 + 0x48) = v1 + 1;
    bv2 = *(unsigned char *)(*(long *)(param_1 + 0x38) + v1);
    if (bv2 < 99) {
        if (bv2 < 0x54) {
            if (bv2 == 0x41) {
                lv4 = FUN_003a3898((unsigned long)param_1, (unsigned long)1);
                v6 = 0x87;
            } else {
                if (bv2 != 0x43) {
                    if (bv2 != 0x4b) {
                        return 0;
                    }
                    v3 = FUN_003a58b0((long)param_1);
                    v5 = 0x11f;
                    goto LAB_003a5840;
                }
                lv4 = FUN_003a3898((unsigned long)param_1, (unsigned long)1);
                v6 = 0x88;
            }
        } else if (bv2 == 0x54) {
            lv4 = FUN_003a3898((unsigned long)param_1, (unsigned long)1);
            v6 = 0x89;
        } else if (bv2 == 0x61) {
            lv4 = FUN_003a3898((unsigned long)param_1, (unsigned long)1);
            v6 = 0x11d;
        } else {
            if (bv2 != 0x62) {
                return 0;
            }
            lv4 = FUN_003a3898((unsigned long)param_1, (unsigned long)1);
            v6 = 0x44;
        }
        *(unsigned short *)(lv4 + 0x10) = v6;
        *(unsigned char *)(lv4 + 0x12) = 0;
        return lv4;
    }
    if (bv2 < 0x6a) {
        if (bv2 == 99) {
            v3 = FUN_003a58b0((long)param_1);
            v5 = 0x45;
            goto LAB_003a5840;
        }
        if (bv2 == 0x67) {
            v3 = FUN_003a58b0((long)param_1);
            v5 = 0x177;
        } else {
            if (bv2 != 0x69) {
                return 0;
            }
            v3 = FUN_003a58b0((long)param_1);
            v5 = 0x84;
        }
    } else if (bv2 < 0x74) {
        if (bv2 == 0x6a) {
            lv4 = (long)FUN_003a5908((long)param_1);
            return lv4;
        }
        if (bv2 != 0x6b) {
            return 0;
        }
        v3 = FUN_003a58b0((long)param_1);
        v5 = 0x155;
    } else if (bv2 == 0x74) {
        v3 = FUN_003a58b0((long)param_1);
        v5 = 0x15a;
    } else {
        if (bv2 != 0x75) {
            return 0;
        }
        v3 = FUN_003a58b0((long)param_1);
        v5 = 0x86;
    }
    v3 = (unsigned long)FUN_003a4b38((unsigned long)param_1, (unsigned short)v5,
                                       (long)v3);
    v5 = 0xf4;
LAB_003a5840:
    lv4 = FUN_003a4b38((unsigned long)param_1, (unsigned short)v5, (long)v3);
    return lv4;
}
/* FUN_003a58b0 @ 0x3a58b0   (est. sk_pop_single — pop a 1-element 0xf4 list node)
 * Ghidra: undefined8 FUN_003a58b0(long param_1)
 * Pops the top 0xf4-tagged node from the stack (param_1+0x60) and returns its single
 * child value (handling list-kind bytes 1 and 5). Returns 0 if the stack is empty or
 * the top node is not a 0xf4 list.
 * Confidence: medium */
unsigned long FUN_003a58b0(long param_1)
{
    unsigned int v1;
    unsigned long *pu2;

    if (*(int *)(param_1 + 0x60) != 0) {
        v1 = *(int *)(param_1 + 0x60) - 1;
        pu2 = *(unsigned long **)(*(long *)(param_1 + 0x58) + (unsigned long)v1 * 8);
        if (*(short *)(pu2 + 2) == 0xf4) {
            *(unsigned int *)(param_1 + 0x60) = v1;
            if (*(char *)((long)pu2 + 0x12) != '\x01') {
                if (*(char *)((long)pu2 + 0x12) != '\x05') {
                    return 0;
                }
                if (*(int *)(pu2 + 1) != 1) {
                    return 0;
                }
                pu2 = (unsigned long *)*pu2;
            }
            return *pu2;
        }
    }
    return 0;
}
/* FUN_003a5908 @ 0x3a5908   (est. sk_token_indexed — map a stream byte through the
 *                            keyword table at DAT_004f2960)
 * Ghidra: undefined8 * FUN_003a5908(long param_1)
 * Reads one stream byte, computes (byte - 100) and a rotate-right-by-1 index into a
 * bitmask (0x93) to validate the index, then emits a 0x46-tagged node whose payload is
 * the 8-byte table entry at 0x4f2960[index]. Returns the node or 0.
 * Confidence: low
 * Notes: literal table base 0x4f2960; bitmask 0x93 gates indices 0..7. */
unsigned long *FUN_003a5908(long param_1)
{
    unsigned long v1;
    unsigned int v2;
    unsigned long *pu3;
    unsigned int v4;
    unsigned long v5;

    v1 = *(unsigned long *)(param_1 + 0x48);
    if (v1 < *(unsigned long *)(param_1 + 0x40)) {
        *(unsigned long *)(param_1 + 0x48) = v1 + 1;
        v4 = (unsigned int)((int)*(char *)(*(long *)(param_1 + 0x38) + v1) - 100);
    } else {
        v4 = 0xffffff9c;
    }
    pu3 = (unsigned long *)0;
    v2 = v4 >> 1 | v4 << 0x1f;
    if ((v2 < 8) && ((0x93U >> (unsigned long)(v4 >> 1 & 0x1f) & 1) != 0)) {
        v5 = *(unsigned long *)(0x4f2960 + (unsigned long)v2 * 8);
        pu3 = (unsigned long *)FUN_003a3898((unsigned long)param_1, (unsigned long)1);
        *(unsigned short *)(pu3 + 2) = 0x46;
        *(unsigned char *)((long)pu3 + 0x12) = 4;
        *pu3 = v5;
    }
    return pu3;
}
/* FUN_003a599c @ 0x003a599c   (est. parse_qualified_selector)
 * Ghidra: undefined8 FUN_003a599c(long param_1)
 * Scans an identifier made of lowercase letters, folding them into a
 * selector accumulator via FUN_003ac580 and pushing results onto the
 * node stack (+0x58). Uppercase letters extend the accumulator and return;
 * '_' indexes the result list (+0x68) at accumulator+0x1b and returns the
 * entry; any other character resets the position and reparses as a name.
 * Returns the resolved selector value, or 0 on any failure / end of input.
 * Confidence: medium
 * Notes: parser context at param_1: +0x38 string, +0x40 length, +0x48 pos,
 * +0x58 node stack, +0x60 depth, +0x68 result list, +0x70 list length. */
unsigned long FUN_003a599c(unsigned long *param_1)
{
    unsigned int v1;
    char cv2;
    unsigned long v3;
    unsigned long v4;
    int iv5;
    long loc28;

    v4 = *(unsigned long *)((char *)param_1 + 0x48);
    if (*(unsigned long *)((char *)param_1 + 0x40) <= v4) {
        return 0;
    }
    v3 = 0xffffffff;
    do {
        *(unsigned long *)((char *)param_1 + 0x48) = v4 + 1;
        cv2 = *(char *)(*(long *)((char *)param_1 + 0x38) + v4);
        iv5 = (int)cv2;
        if (iv5 == 0) {
            return 0;
        }
        if (((unsigned int)(iv5 - 0x61) & 0xff) < 0x1a) {
            /* lowercase letter a-z: fold into selector, push onto stack */
            loc28 = FUN_003ac580(param_1, v3, (long)iv5 + -0x61);
            if (loc28 == 0) {
                return 0;
            }
            FUN_003ad810((char *)param_1 + 0x58, &loc28, param_1);
            v3 = 0xffffffff;
        } else {
            if (((unsigned int)(iv5 - 0x41) & 0xff) < 0x1a) {
                /* uppercase letter A-Z: extend selector and return it */
                v3 = FUN_003ac580(param_1, v3, (long)iv5 + -0x41);
                return v3;
            }
            if (cv2 == '_') {
                v1 = (unsigned int)v3 + 0x1b;
                if (*(unsigned int *)((char *)param_1 + 0x70) <= v1) {
                    return 0;
                }
                return *(unsigned long *)(*(long *)((char *)param_1 + 0x68) +
                                          (unsigned long)v1 * 8);
            }
            *(unsigned long *)((char *)param_1 + 0x48) = v4;
            v3 = FUN_003ac430(param_1);
            if ((int)v3 < 0) {
                return 0;
            }
        }
        v4 = *(unsigned long *)((char *)param_1 + 0x48);
        if (*(unsigned long *)((char *)param_1 + 0x40) <= v4) {
            return 0;
        }
    } while (1);
}
/* FUN_003a5aa0 @ 0x003a5aa0   (est. parse_builtin_type_name)
 * Ghidra: undefined8 FUN_003a5aa0(long param_1)
 * Reads a single builtin-type letter token and materialises the matching
 * builtin type-name string (via FUN_00365660 allocation + memcpy of the
 * string constants such as "IntLiteral", "UnsafeValueBuffer", "Executor"),
 * then packages the name into a fresh node (tag 0x14) and registers it
 * with FUN_003a4b38(tag 0xf4). Special letters: 'T' builds an empty 0x15
 * node; 'V' pops two 0xf4 stack nodes and packs them into a 0x16 node;
 * 'f'/'i'/'v' build FPIEEE/Int/Vec names through the string-builder
 * helpers. Returns the registered node or 0 on a parse error.
 * Confidence: medium
 * Notes: string constant addresses 0x5d6f37..0x5d6f67 (builtin names) are
 * literal ROM addresses; the memcpy() lengths match Ghidra's CONCAT byte
 * reconstructions exactly. */
unsigned long FUN_003a5aa0(unsigned long *param_1)
{
    unsigned long v13;
    unsigned char bv2;
    unsigned long v3;
    unsigned long v4;
    unsigned long v6;
    int iv5;
    unsigned long v1;
    unsigned char *pc7;
    unsigned long *pu8;
    long *pl9;
    unsigned int v10;
    unsigned char *pc11;
    long lv12;
    long lv14;
    unsigned char loc41;
    unsigned char *loc40;
    unsigned long loc38;

    pc7 = 0;
    v13 = 0;
    pu8 = 0;
    v13 = *(unsigned long *)((char *)param_1 + 0x48);
    if (*(unsigned long *)((char *)param_1 + 0x40) <= v13) {
        return 0;
    }
    v6 = 0;
    *(unsigned long *)((char *)param_1 + 0x48) = v13 + 1;
    bv2 = *(unsigned char *)(*(long *)((char *)param_1 + 0x38) + v13);
    v10 = (unsigned int)bv2;
    if (bv2 < 0x54) {
        if (v10 != 0x48 && 0x47 < bv2) {
            if (v10 == 0x49) {
                /* 'I' -> "IntLiteral" */
                v13 = 0x12;
                pc7 = (unsigned char *)FUN_00365660(param_1, 0x12);
                pc7[0x10] = 'a';
                pc7[0x11] = 'l';
                pc11 = (unsigned char *)0x5d6f37;
            } else {
                if (v10 == 0x4f) {
                    /* 'O' -> "UnknownObject" */
                    pc7 = (unsigned char *)FUN_00365660(param_1, 0x15);
                    pc11 = (unsigned char *)0x5d425f;
                    goto LAB_003a5cc4;
                }
                if (v10 != 0x50) {
                    return 0;
                }
                /* 'P' -> "PackIndex" */
                v13 = 0x11;
                pc7 = (unsigned char *)FUN_00365660(param_1, 0x11);
                pc7[0x10] = 'x';
                pc11 = (unsigned char *)0x5d6f67;
            }
            goto LAB_003a5f94;
        }
        if (v10 != 0x41) {
            if (v10 == 0x42) {
                /* 'B' -> "UnsafeValueBuffer" (25 bytes) */
                v13 = 0x19;
                pc7 = (unsigned char *)FUN_00365660(param_1, 0x19);
                __builtin_memcpy(pc7, (const void *)0x5d4245, 0x19);
            } else {
                if (v10 != 0x44) {
                    return 0;
                }
                /* 'D' -> "DefaultActorStorage" (27 bytes) */
                v13 = 0x1b;
                pc7 = (unsigned char *)FUN_00365660(param_1, 0x1b);
                __builtin_memcpy(pc7, (const void *)0x5d4293, 0x1b);
            }
            goto LAB_003a5fd0;
        }
        /* 'A' -> "ImplicitActor" (21 bytes) */
        pc7 = (unsigned char *)FUN_00365660(param_1, 0x15);
        pc11 = (unsigned char *)0x5d6f06;
LAB_003a5cc4:
        v13 = 0x15;
        __builtin_memcpy(pc7, pc11, 0x15);
        goto LAB_003a5fd0;
    }
    if (0x15 < v10 - 0x62) {
        if (v10 == 0x54) {
            /* 'T': empty 0x15 node */
            pu8 = (unsigned long *)FUN_003a3898((unsigned long)param_1, (unsigned long)1);
            *(unsigned short *)((char *)pu8 + 0x10) = 0x15;
            *(unsigned char *)((char *)pu8 + 0x12) = 0;
        } else {
            if (v10 != 0x56) {
                return 0;
            }
            /* 'V': pack two 0xf4 stack nodes into a 0x16 node */
            iv5 = *(int *)((char *)param_1 + 0x60);
            if (iv5 == 0) {
                return 0;
            }
            v10 = (unsigned int)(iv5 - 1);
            lv12 = *(long *)(*(long *)((char *)param_1 + 0x58) + (unsigned long)v10 * 8);
            if (*(short *)((char *)lv12 + 0x10) != 0xf4) {
                return 0;
            }
            *(unsigned int *)((char *)param_1 + 0x60) = v10;
            if (v10 == 0) {
                return 0;
            }
            lv14 = *(long *)(*(long *)((char *)param_1 + 0x58) + (unsigned long)(iv5 - 2U) * 8);
            if (*(short *)((char *)lv14 + 0x10) != 0xf4) {
                return 0;
            }
            *(unsigned int *)((char *)param_1 + 0x60) = (unsigned int)(iv5 - 2U);
            pu8 = (unsigned long *)FUN_003a3898((unsigned long)param_1, (unsigned long)1);
            *(unsigned short *)((char *)pu8 + 0x10) = 0x16;
            *(unsigned char *)((char *)pu8 + 0x12) = 0;
            FUN_003a3460((unsigned int *)pu8, (long)lv14, (unsigned long)param_1);
            FUN_003a3460((unsigned int *)pu8, (long)lv12, (unsigned long)param_1);
        }
        goto LAB_003a5ff4;
    }
    switch (v10) {
    default: /* 'b' -> "BridgeObject" + "ject" */
        pc7 = (unsigned char *)FUN_00365660(param_1, 0x14);
        memcpy((char *)pc7 + 0x10, "ject", 4);
        pc11 = (unsigned char *)0x5d421d;
        goto LAB_003a5d28;
    case 99: /* 'c' -> "RawUnsafeContinuation" (29 bytes) */
        v13 = 0x1d;
        pc7 = (unsigned char *)FUN_00365660(param_1, 0x1d);
        __builtin_memcpy(pc7, (const void *)0x5d4275, 0x1d);
        break;
    case 100: /* 'd' -> "NonDefaultDistributedActor" (41 bytes) */
        v13 = 0x29;
        pc7 = (unsigned char *)FUN_00365660(param_1, 0x29);
        __builtin_memcpy(pc7, (const void *)0x5d42af, 0x29);
        break;
    case 0x65: /* 'e' -> "Executor" */
        v13 = 0x10;
        pc7 = (unsigned char *)FUN_00365660(param_1, 0x10);
        pc11 = (unsigned char *)0x5d42d9;
        goto LAB_003a5f94;
    case 0x66: /* 'f' -> "FPIEEE" + width */
        iv5 = FUN_003ac4a4(param_1);
        if (0xfff < (unsigned int)(iv5 - 2U)) {
            return 0;
        }
        pc11 = (unsigned char *)0x5d6f1c;
        v6 = 0xe;
        goto LAB_003a5f4c;
    case 0x67:
    case 0x68:
    case 0x6b:
    case 0x6c:
    case 0x6d:
    case 0x6e:
    case 0x71:
    case 0x72:
    case 0x73:
    case 0x75:
        goto switchD_003a5b0c_caseD_67;
    case 0x69: /* 'i' -> "Int" + width */
        iv5 = FUN_003ac4a4(param_1);
        if (0xfff < (unsigned int)(iv5 - 2U)) {
            return 0;
        }
        pc11 = (unsigned char *)0x5d6f2b;
        v6 = 0xb;
LAB_003a5f4c:
        loc38 = 0;
        loc40 = (unsigned char *)0x0;
        FUN_003a3a70((long *)&loc40, (unsigned long)pc11, (long)v6, (unsigned long)param_1);
        FUN_003a3b9c((long *)&loc40, (unsigned long)(iv5 + -1), (unsigned long)param_1);
LAB_003a5f64:
        v13 = loc38 & 0xffffffff;
        pc7 = loc40;
        break;
    case 0x6a: /* 'j' -> "Job" + ".Job" */
        v13 = 0xb;
        pc7 = (unsigned char *)FUN_00365660(param_1, 0xb);
        memcpy((char *)pc7 + 7, ".Job", 4);
        pc11 = (unsigned char *)0x5d42ea;
        goto LAB_003a5fc8;
    case 0x6f: /* 'o' -> "NativeObject" + "ject" */
        pc7 = (unsigned char *)FUN_00365660(param_1, 0x14);
        memcpy((char *)pc7 + 0x10, "ject", 4);
        pc11 = (unsigned char *)0x5d4208;
LAB_003a5d28:
        v13 = 0x14;
        __builtin_memcpy(pc7, pc11, 0x10);
        pu8 = (unsigned long *)FUN_003a3898((unsigned long)param_1, (unsigned long)1);
        *(unsigned short *)((char *)pu8 + 0x10) = 0x14;
        goto LAB_003a5fe8;
    case 0x70: /* 'p' -> "RawPointer" + "er" */
        v13 = 0x12;
        pc7 = (unsigned char *)FUN_00365660(param_1, 0x12);
        pc7[0x10] = 'e';
        pc7[0x11] = 'r';
        pc11 = (unsigned char *)0x5d4232;
        goto LAB_003a5f94;
    case 0x74: /* 't' -> "SILToken" */
        v13 = 0x10;
        pc7 = (unsigned char *)FUN_00365660(param_1, 0x10);
        pc11 = (unsigned char *)0x5d6f56;
LAB_003a5f94:
        __builtin_memcpy(pc7, pc11, 0x10);
        break;
    case 0x76: /* 'v' -> "Vec" : name = "Vec" + width + 'x' + Builtin.<name> */
        iv5 = FUN_003ac4a4(param_1);
        if ((unsigned int)(iv5 - 0x1002U) < 0xfffff000U) {
            return 0;
        }
        pl9 = (long *)FUN_003a58b0((long)param_1);
        if (pl9 == (long *)0x0) {
            return 0;
        }
        if ((short)pl9[2] != 0x14) {
            return 0;
        }
        if ((unsigned long)pl9[1] < 8) {
            return 0;
        }
        if (*(long *)*pl9 != 0x2e6e69746c697542UL) { /* "Builtin." */
            return 0;
        }
        loc40 = (unsigned char *)0x0;
        loc38 = 0;
        FUN_003a3a70((long *)&loc40, (unsigned long)0x5d6f4a, (long)0xb, (unsigned long)param_1); /* "Vec" */
        FUN_003a3b9c((long *)&loc40, (unsigned long)(iv5 + -1), (unsigned long)param_1);
        loc41 = 0x78; /* 'x' */
        FUN_003acd3c(&loc40, &loc41, param_1);
        v1 = pl9[1];
        v13 = v1;
        if (7 < v1) {
            v13 = 8;
        }
        FUN_003a3a70((long *)&loc40, (unsigned long)v13 + *pl9, (long)v1 - v13, (unsigned long)param_1);
        goto LAB_003a5f64;
    case 0x77: /* 'w' -> "Word" + "Word" tail */
        v13 = 0xc;
        pc7 = (unsigned char *)FUN_00365660(param_1, 0xc);
        memcpy((char *)pc7 + 8, "Word", 4);
        pc11 = (unsigned char *)0x5d41a5;
LAB_003a5fc8:
        __builtin_memcpy(pc7, pc11, 8);
    }
LAB_003a5fd0:
    pu8 = (unsigned long *)FUN_003a3898((unsigned long)param_1, (unsigned long)1);
    *(unsigned short *)((char *)pu8 + 0x10) = 0x14;
LAB_003a5fe8:
    *(unsigned char *)((char *)pu8 + 0x12) = 3;
    *pu8 = (unsigned long)pc7;
    pu8[1] = v13;
LAB_003a5ff4:
    v6 = FUN_003a4b38((unsigned long)param_1, (unsigned short)0xf4, (long)pu8);
switchD_003a5b0c_caseD_67:
    return v6;
}
/* FUN_003a6090 @ 0x003a6090   (est. parse_identifier_type_ref)
 * Ghidra: long FUN_003a6090(long param_1,undefined8 param_2)
 * Pops a stack node whose tag passes FUN_003acda0 (identifier token),
 * gathers the current name (FUN_003ace50), builds a node via
 * FUN_003a4b98(tag param_2) wrapping it and the popped element, then
 * registers the resulting 0xf4 node into the result list (+0x68) if built.
 * Returns the registered node, or 0 on failure.
 * Confidence: medium
 * Notes: parser context offsets: +0x58 node stack, +0x60 depth,
 * +0x68 result list. */
long FUN_003a6090(unsigned long *param_1, unsigned long param_2)
{
    unsigned int v1;
    int iv2;
    unsigned long v3;
    long lv4;
    long loc38;

    if (*(int *)((char *)param_1 + 0x60) != 0) {
        v1 = *(int *)((char *)param_1 + 0x60) - 1;
        lv4 = *(long *)(*(long *)((char *)param_1 + 0x58) + (unsigned long)v1 * 8);
        iv2 = FUN_003acda0(*(unsigned short *)((char *)lv4 + 0x10));
        if (iv2 != 0) {
            *(unsigned int *)((char *)param_1 + 0x60) = v1;
            goto LAB_003a60dc;
        }
    }
    lv4 = 0;
LAB_003a60dc:
    v3 = FUN_003ace50(param_1);
    v3 = FUN_003a4b98((unsigned long)param_1, (unsigned short)param_2, (long)v3, (long)lv4);
    lv4 = FUN_003a4b38((unsigned long)param_1, (unsigned short)0xf4, (long)v3);
    if (lv4 != 0) {
        loc38 = lv4;
        FUN_003ad810((char *)param_1 + 0x68, &loc38, param_1);
    }
    return lv4;
}
/* FUN_003a613c @ 0x003a613c   (est. parse_tuple_type)
 * Ghidra: long FUN_003a613c(long param_1)
 * Pops a 0x2c-tagged node if present, gathers two name/type components via
 * FUN_003ace08 and FUN_003acefc, and builds a 0x49-tagged tuple node with
 * FUN_003a4b98. If both the popped element and the built node are nonzero
 * the element is attached as the tuple's payload (FUN_003a3460).
 * Returns the built node, or 0 on failure.
 * Confidence: medium */
long FUN_003a613c(unsigned long *param_1)
{
    unsigned int v1;
    unsigned long v2;
    unsigned long v3;
    long lv4;
    long lv5;

    if (*(int *)((char *)param_1 + 0x60) != 0) {
        v1 = *(int *)((char *)param_1 + 0x60) - 1;
        lv5 = *(long *)(*(long *)((char *)param_1 + 0x58) + (unsigned long)v1 * 8);
        if (*(short *)((char *)lv5 + 0x10) == 0x2c) {
            *(unsigned int *)((char *)param_1 + 0x60) = v1;
            goto LAB_003a6180;
        }
    }
    lv5 = 0;
LAB_003a6180:
    v2 = FUN_003ace08(param_1);
    v3 = FUN_003acefc(param_1);
    lv4 = FUN_003a4b98((unsigned long)param_1, (unsigned short)0x49, (long)v2, (long)v3);
    if ((lv5 != 0) && (lv4 != 0)) {
        FUN_003a3460((unsigned int *)lv4, (long)lv5, (unsigned long)param_1);
    }
    return lv4;
}
/* FUN_003a61d8 @ 0x003a61d8   (est. parse_application_type)
 * Ghidra: void FUN_003a61d8(long param_1)
 * Pops a 0x2c element if present, builds a 0x54 node and applies it
 * (FUN_003a4f5c); if the popped element existed it is wrapped into a 0x2d
 * node then registered as 0xf4. A second element passing FUN_003acda0 is
 * popped, then the whole application is emitted through FUN_003a4c14
 * (tag 0x4e) or, on a prior non-null result, FUN_003a4ca8, and handed to
 * FUN_003acfb4 with the byte at +0x51.
 * Confidence: medium */
void FUN_003a61d8(unsigned long *param_1)
{
    unsigned int v1;
    int iv2;
    unsigned long v3;
    long lv4;
    unsigned long v5;
    long lv6;

    if (*(int *)((char *)param_1 + 0x60) == 0) {
LAB_003a621c:
        lv6 = 0;
    } else {
        v1 = *(int *)((char *)param_1 + 0x60) - 1;
        lv6 = *(long *)(*(long *)((char *)param_1 + 0x58) + (unsigned long)v1 * 8);
        if (*(short *)((char *)lv6 + 0x10) != 0x2c) {
            goto LAB_003a621c;
        }
        *(unsigned int *)((char *)param_1 + 0x60) = v1;
    }
    v3 = FUN_003ab218(param_1, 0x54, 0);
    lv4 = FUN_003a4f5c((long)param_1, (long *)v3);
    if (lv6 != 0) {
        v3 = FUN_003a4b98((unsigned long)param_1, (unsigned short)0x2d, (long)lv6, (long)v3);
        v3 = FUN_003a4b38((unsigned long)param_1, (unsigned short)0xf4, (long)v3);
    }
    if (*(int *)((char *)param_1 + 0x60) != 0) {
        v1 = *(int *)((char *)param_1 + 0x60) - 1;
        lv6 = *(long *)(*(long *)((char *)param_1 + 0x58) + (unsigned long)v1 * 8);
        iv2 = FUN_003acda0(*(unsigned short *)((char *)lv6 + 0x10));
        if (iv2 != 0) {
            *(unsigned int *)((char *)param_1 + 0x60) = v1;
            goto LAB_003a629c;
        }
    }
    lv6 = 0;
LAB_003a629c:
    v5 = FUN_003ace50(param_1);
    if (lv4 == 0) {
        v5 = FUN_003a4c14((unsigned long)param_1, (unsigned short)0x4e, (long)v5, (long)lv6, (long)v3);
    } else {
        v5 = FUN_003a4ca8((unsigned long)0, (unsigned short)0, (long)0, (long)0, (long)0, (long)0);
    }
    FUN_003acfb4(param_1, v5, v3, *(unsigned char *)((char *)param_1 + 0x51));
    return;
}
/* FUN_003a62f8 @ 0x003a62f8   (est. parse_named_type_ref)
 * Ghidra: long FUN_003a62f8(long param_1)
 * Builds a 4-element attribute descriptor (FUN_003b0e1c) seeded with the
 * literal at DAT_004f2740, parses it with FUN_003ad724, then fetches the
 * type via FUN_003acefc and resolves a reference with FUN_003ad874. On
 * success a 0xf4 node is allocated (tag 0xf4), the resolved type attached,
 * and the node pushed onto the result list (+0x68). Returns the node or 0.
 * Confidence: low
 * Notes: DAT_004f2740 is a literal global seed; used only to initialise
 * the local descriptor (its value is not otherwise consumed). */
long FUN_003a62f8(unsigned long *param_1)
{
    int iv1;
    long lv2;
    long lv3;
    unsigned long loc50;
    unsigned long loc48;
    long loc40;
    long loc38;

    loc50 = FUN_003b0e1c(param_1, 4);
    loc48 = *(unsigned long *)0x4f2740; /* DAT_004f2740 */
    iv1 = FUN_003ad724(param_1, &loc50, &loc40);
    if (((iv1 == 0) || (lv2 = FUN_003acefc(param_1), lv2 == 0)) ||
        (lv2 = FUN_003ad874(param_1, lv2, &loc50, 0), lv2 == 0)) {
        lv3 = 0;
    } else {
        if (loc40 != 0) {
            FUN_003a3460((unsigned int *)lv2, (long)loc40, (unsigned long)param_1);
        }
        lv3 = FUN_003a3898((unsigned long)param_1, (unsigned long)1);
        *(unsigned short *)((char *)lv3 + 0x10) = 0xf4;
        *(unsigned char *)((char *)lv3 + 0x12) = 0;
        FUN_003a3460((unsigned int *)lv3, (long)lv2, (unsigned long)param_1);
        loc38 = lv3;
        FUN_003ad810((char *)param_1 + 0x68, &loc38, param_1);
    }
    return lv3;
}
/* FUN_003a63d8 @ 0x003a63d8   (est. parse_optional_generic)
 * Ghidra: void FUN_003a63d8(long param_1)
 * Fetches two string fragments (FUN_003ad5a4, FUN_003ad61c) and, if the
 * top stack element's tag is one of 0x30..0x32, pops it. Emits the result
 * through FUN_003a4c14(tag 0x32) with the popped element, the second
 * fragment, and the first fragment as operands.
 * Confidence: medium */
void FUN_003a63d8(unsigned long *param_1)
{
    unsigned int v1;
    unsigned long v2;
    unsigned long v3;
    long lv4;

    v2 = FUN_003ad5a4();
    v3 = FUN_003ad61c(param_1);
    if (*(int *)((char *)param_1 + 0x60) != 0) {
        v1 = *(int *)((char *)param_1 + 0x60) - 1;
        lv4 = *(long *)(*(long *)((char *)param_1 + 0x58) + (unsigned long)v1 * 8);
        if (*(unsigned short *)((char *)lv4 + 0x10) - 0x30 < 3) {
            *(unsigned int *)((char *)param_1 + 0x60) = v1;
            goto LAB_003a6430;
        }
    }
    lv4 = 0;
LAB_003a6430:
    FUN_003a4c14((unsigned long)param_1, (unsigned short)0x32, (long)lv4, (long)v3, (long)v2);
    return;
}
/* FUN_003a644c @ 0x003a644c   (est. parse_closure_type)
 * Ghidra: void FUN_003a644c(long param_1)
 * Fetches a fragment (FUN_003ad478) and pops the top element if its tag is
 * 0xc2 or 0xc3 (otherwise fetches one via FUN_003ad560). A following 0xf4
 * element is popped as well. Emits through FUN_003a4c14(tag 0x1b) with the
 * popped nodes and the fragment.
 * Confidence: medium */
void FUN_003a644c(unsigned long *param_1)
{
    unsigned int v1;
    unsigned long v2;
    long lv3;
    long lv4;

    v2 = FUN_003ad478();
    if (*(int *)((char *)param_1 + 0x60) == 0) {
LAB_003a649c:
        lv4 = FUN_003ad560(param_1);
        v1 = *(unsigned int *)((char *)param_1 + 0x60);
    } else {
        v1 = *(int *)((char *)param_1 + 0x60) - 1;
        lv4 = *(long *)(*(long *)((char *)param_1 + 0x58) + (unsigned long)v1 * 8);
        if ((*(short *)((char *)lv4 + 0x10) != 0xc3) && (*(short *)((char *)lv4 + 0x10) != 0xc2)) {
            goto LAB_003a649c;
        }
        *(unsigned int *)((char *)param_1 + 0x60) = v1;
    }
    if (v1 != 0) {
        lv3 = *(long *)(*(long *)((char *)param_1 + 0x58) + (unsigned long)(v1 - 1) * 8);
        if (*(short *)((char *)lv3 + 0x10) == 0xf4) {
            *(unsigned int *)((char *)param_1 + 0x60) = v1 - 1;
            goto LAB_003a64d4;
        }
    }
    lv3 = 0;
LAB_003a64d4:
    FUN_003a4c14((unsigned long)param_1, (unsigned short)0x1b, (long)lv3, (long)lv4, (long)v2);
    return;
}
/* FUN_003a64f0 @ 0x003a64f0   (est. parse_subscript_bracket)
 * Ghidra: void FUN_003a64f0(long param_1)
 * Fetches a fragment (FUN_003ad5a4) and the current type operand
 * (FUN_003a663c), pops a 0xf4 element if present, and emits the result
 * through FUN_003a4c14(tag 0x30).
 * Confidence: medium */
void FUN_003a64f0(unsigned long *param_1)
{
    unsigned int v1;
    unsigned long v2;
    unsigned long v3;
    long lv4;

    v2 = FUN_003ad5a4();
    v3 = FUN_003a663c((unsigned long *)param_1);
    if (*(int *)((char *)param_1 + 0x60) != 0) {
        v1 = *(int *)((char *)param_1 + 0x60) - 1;
        lv4 = *(long *)(*(long *)((char *)param_1 + 0x58) + (unsigned long)v1 * 8);
        if (*(short *)((char *)lv4 + 0x10) == 0xf4) {
            *(unsigned int *)((char *)param_1 + 0x60) = v1;
            goto LAB_003a6544;
        }
    }
    lv4 = 0;
LAB_003a6544:
    FUN_003a4c14((unsigned long)param_1, (unsigned short)0x30, (long)lv4, (long)v3, (long)v2);
    return;
}
/* FUN_003a6560 @ 0x003a6560   (est. parse_subscript_digit)
 * Ghidra: void FUN_003a6560(long param_1)
 * Fetches a fragment (FUN_003ad5a4) and the current type operand
 * (FUN_003a663c), pops an element whose tag is in 0x30..0x32, and emits
 * through FUN_003a4c14(tag 0x31).
 * Confidence: medium */
void FUN_003a6560(unsigned long *param_1)
{
    unsigned int v1;
    unsigned long v2;
    unsigned long v3;
    long lv4;

    v2 = FUN_003ad5a4();
    v3 = FUN_003a663c((unsigned long *)param_1);
    if (*(int *)((char *)param_1 + 0x60) != 0) {
        v1 = *(int *)((char *)param_1 + 0x60) - 1;
        lv4 = *(long *)(*(long *)((char *)param_1 + 0x58) + (unsigned long)v1 * 8);
        if (*(unsigned short *)((char *)lv4 + 0x10) - 0x30 < 3) {
            *(unsigned int *)((char *)param_1 + 0x60) = v1;
            goto LAB_003a65b8;
        }
    }
    lv4 = 0;
LAB_003a65b8:
    FUN_003a4c14((unsigned long)param_1, (unsigned short)0x31, (long)lv4, (long)v3, (long)v2);
    return;
}
/* FUN_003a65d4 @ 0x003a65d4   (est. parse_subscript_pair)
 * Ghidra: void FUN_003a65d4(long param_1)
 * Pops a 0xf4 element (if the top has that tag) and then an element whose
 * tag is in 0x30..0x32, and builds a 0x33-tagged node from the pair via
 * FUN_003a4b98. Guards against underflowing the stack when only one
 * element is available.
 * Confidence: medium */
void FUN_003a65d4(unsigned long *param_1)
{
    unsigned int v1;
    long lv2;
    long lv3;
    unsigned int v4;

    v4 = *(unsigned int *)((char *)param_1 + 0x60);
    if (v4 == 0) {
        lv3 = 0;
    } else {
        v1 = v4 - 1;
        lv3 = *(long *)(*(long *)((char *)param_1 + 0x58) + (unsigned long)v1 * 8);
        if (*(short *)((char *)lv3 + 0x10) == 0xf4) {
            *(unsigned int *)((char *)param_1 + 0x60) = v1;
            v4 = v1;
            if (v1 == 0) {
                goto LAB_003a6630;
            }
        } else {
            lv3 = 0;
        }
        lv2 = *(long *)(*(long *)((char *)param_1 + 0x58) + (unsigned long)(v4 - 1) * 8);
        if (*(unsigned short *)((char *)lv2 + 0x10) - 0x30 < 3) {
            *(unsigned int *)((char *)param_1 + 0x60) = v4 - 1;
            goto LAB_003a6634;
        }
    }
LAB_003a6630:
    lv2 = 0;
LAB_003a6634:
    FUN_003a4b98((unsigned long)param_1, (unsigned short)0x33, (long)lv2, (long)lv3);
    return;
}
/* FUN_003a663c @ 0x003a663c   (est. parse_type_operand)
 * Ghidra: long FUN_003a663c(long param_1)
 * Pops the top stack element if it is a directly usable operand: tag 0xc0
 * or 0x16b (returned as-is), or tag 0xf4 (validated: element count byte at
 * +0x12 and payload checks, plus FUN_003a33cc acceptance), or a token
 * passing FUN_003acda0 (in which case the current name is gathered and a
 * 0xbf-tagged node built and registered as 0xf4). Returns the operand node
 * or 0 when the top is not a usable type.
 * Confidence: medium */
long FUN_003a663c(unsigned long *param_1)
{
    short sVar1;
    unsigned int v2;
    int iv3;
    unsigned long v4;
    long lv5;

    if (*(int *)((char *)param_1 + 0x60) != 0) {
        v2 = *(int *)((char *)param_1 + 0x60) - 1;
        lv5 = *(long *)(*(long *)((char *)param_1 + 0x58) + (unsigned long)v2 * 8);
        sVar1 = *(short *)((char *)lv5 + 0x10);
        if ((sVar1 == 0xc0) || (sVar1 == 0x16b)) {
            *(unsigned int *)((char *)param_1 + 0x60) = v2;
            return lv5;
        }
        if (sVar1 == 0xf4) {
            *(unsigned int *)((char *)param_1 + 0x60) = v2;
            if ((1 < (unsigned char)(*(unsigned char *)((char *)lv5 + 0x12) - 1)) &&
                ((*(unsigned char *)((char *)lv5 + 0x12) != 5) ||
                 (*(int *)((char *)lv5 + 8) == 0))) {
                return 0;
            }
            iv3 = FUN_003a33cc((long *)lv5);
            if (iv3 != 0) {
                return lv5;
            }
            return 0;
        }
        iv3 = FUN_003acda0();
        if (iv3 != 0) {
            *(unsigned int *)((char *)param_1 + 0x60) = v2;
            goto LAB_003a66e8;
        }
    }
    lv5 = 0;
LAB_003a66e8:
    v4 = FUN_003ace50(param_1);
    v4 = FUN_003a4b98((unsigned long)param_1, (unsigned short)0xbf, (long)v4, (long)lv5);
    lv5 = FUN_003a4b38((unsigned long)param_1, (unsigned short)0xf4, (long)v4);
    return lv5;
}
/* FUN_003a672c @ 0x003a672c   (est. parse_generic_type)
 * Ghidra: long FUN_003a672c(long param_1)
 * Pops a 0x2c element, then the base type (FUN_003a663c) and up to two
 * more stack elements (0xf4-tagged or, in one position, 0x67-tagged), all
 * gated against stack underflow. If the 0x2c element was present it is
 * wrapped (0x2d) and registered as 0xf4. The assembled generic is emitted
 * via FUN_003a4c14(tag 0xc1) and, if both it and a 0x67 element are
 * present, that element is attached as its payload. Returns the node or 0.
 * Confidence: low
 * Notes: intricate comma-operator conditionals in the decompile reproduce
 * the exact side-effect ordering (stack pop + assignment + test). */
long FUN_003a672c(unsigned long *param_1)
{
    unsigned long v1;
    unsigned long v2;
    long lv3;
    unsigned long v4;
    long lv5;
    unsigned int v6;
    unsigned int v7;
    long lv8;
    long lv9;

    if (*(int *)((char *)param_1 + 0x60) == 0) {
LAB_003a6770:
        lv8 = 0;
    } else {
        v7 = *(int *)((char *)param_1 + 0x60) - 1;
        lv8 = *(long *)(*(long *)((char *)param_1 + 0x58) + (unsigned long)v7 * 8);
        if (*(short *)((char *)lv8 + 0x10) != 0x2c) {
            goto LAB_003a6770;
        }
        *(unsigned int *)((char *)param_1 + 0x60) = v7;
    }
    v1 = FUN_003ace08(param_1);
    v2 = FUN_003a663c((unsigned long *)param_1);
    v7 = *(unsigned int *)((char *)param_1 + 0x60);
    if (v7 == 0) {
        lv9 = 0;
LAB_003a67ec:
        lv5 = 0;
        lv3 = lv9;
    } else {
        lv3 = 0;
        v6 = v7 - 1;
        lv9 = *(long *)(*(long *)((char *)param_1 + 0x58) + (unsigned long)v6 * 8);
        if (*(short *)((char *)lv9 + 0x10) != 0xf4) {
            if ((*(short *)((char *)lv9 + 0x10) == 0x67) &&
                ((*(unsigned int *)((char *)param_1 + 0x60) = v6),
                 (lv3 = lv9), (v7 = v6), (v6 == 0))) {
                goto LAB_003a67ec;
            }
            v6 = v7 - 1;
            lv9 = *(long *)(*(long *)((char *)param_1 + 0x58) + (unsigned long)v6 * 8);
            if (*(short *)((char *)lv9 + 0x10) != 0xf4) {
                lv5 = 0;
                goto joined_r0x003a67f0;
            }
        }
        *(unsigned int *)((char *)param_1 + 0x60) = v6;
        lv5 = lv9;
    }
joined_r0x003a67f0:
    if (lv8 != 0) {
        v4 = FUN_003a4b98((unsigned long)param_1, (unsigned short)0x2d, (long)lv8, (long)0);
        lv5 = FUN_003a4b38((unsigned long)param_1, (unsigned short)0xf4, (long)v4);
    }
    lv8 = FUN_003a4c14((unsigned long)param_1, (unsigned short)0xc1, (long)lv5, (long)v2, (long)v1);
    if ((lv3 != 0) && (lv8 != 0)) {
        FUN_003a3460((unsigned int *)lv8, (long)lv3, (unsigned long)param_1);
    }
    return lv8;
}
/* FUN_003a6874 @ 0x003a6874   (est. emit_ref_drop)
 * Ghidra: void FUN_003a6874(long param_1,undefined8 param_2)
 * If the top stack element is 0xf4-tagged it is popped and registered via
 * FUN_003a4b38() with no arguments; otherwise FUN_003a4b38 is called with
 * (param_1, param_2, 0). Both paths finalise a reference emission.
 * Confidence: medium */
void FUN_003a6874(unsigned long *param_1, unsigned long param_2)
{
    unsigned int v1;

    if (*(int *)((char *)param_1 + 0x60) != 0) {
        v1 = *(int *)((char *)param_1 + 0x60) - 1;
        if (*(short *)(*(long *)(*(long *)((char *)param_1 + 0x58) + (unsigned long)v1 * 8) + 0x10) == 0xf4) {
            *(unsigned int *)((char *)param_1 + 0x60) = v1;
            FUN_003a4b38((unsigned long)0, (unsigned short)0, (long)0);
            return;
        }
    }
    FUN_003a4b38((unsigned long)param_1, (unsigned short)param_2, (long)0);
    return;
}
/* FUN_003a68a4 @ 0x003a68a4   (est. parse_numeric_or_identifier)
 * Ghidra: undefined8 * FUN_003a68a4(long param_1)
 * Parser entry that consumes a numeric literal ('0'..'9', handling a
 * leading "00" prefix and '_' separators) or an identifier, building a
 * name buffer through the string-builder helpers (FUN_003a3a70 /
 * FUN_003a3b9c / FUN_003acd3c). Digit runs become integer literals
 * (optionally via the big-number decoder FUN_003bed8c for the "0"-
 * prefixed path), while identifiers are interned into the name table at
 * +0x78 (up to 0x1a entries, counted at +0x218). On success a 0x67 node
 * is built (element count 3) and pushed onto the result list (+0x68).
 * Returns the node, or 0 on any parse error.
 * Confidence: low
 * Notes: thunk_FUN_00012568 frees the big-number buffer after use on the
 * "00"-prefixed numeric path; the identifier interning loop tracks word
 * boundaries with a signed 0xffffffff start marker. */
unsigned long *FUN_003a68a4(unsigned long *param_1)
{
    unsigned long *pu1;
    long lv2;
    long *pl3;
    unsigned int v4;
    bool bv5;
    unsigned int v8;
    int iv9;
    unsigned long v11;
    bool bv12;
    int iv13;
    unsigned int v14;
    unsigned long v15;
    unsigned int v16;
    bool bv18;
    unsigned long *loc88;
    unsigned long uStack_80;
    unsigned long loc78;
    unsigned long *loc70;
    unsigned long loc68;

    v11 = *(unsigned long *)((char *)param_1 + 0x48);
    if (v11 < *(unsigned long *)((char *)param_1 + 0x40)) {
        v8 = (unsigned int)*(unsigned char *)(*(long *)((char *)param_1 + 0x38) + v11);
        if (v8 - 0x30 < 10) {
            /* leading digit */
            if (v8 == 0x30) {
                v15 = v11 + 1;
                *(unsigned long *)((char *)param_1 + 0x48) = v15;
                if ((v15 < *(unsigned long *)((char *)param_1 + 0x40)) &&
                    (*(char *)(*(long *)((char *)param_1 + 0x38) + v15) == '0')) {
                    bv12 = false;
                    *(unsigned long *)((char *)param_1 + 0x48) = v11 + 2;
                    bv5 = true;
                    v11 = v11 + 2;
                } else {
                    bv5 = false;
                    bv12 = true;
                    v11 = v15;
                }
            } else {
                bv5 = false;
                bv12 = false;
            }
            loc70 = (unsigned long *)0x0;
            loc68 = 0;
            do {
                if (bv12) {
                    /* consume a run of name characters, interning table entries */
                    do {
                        v11 = *(unsigned long *)((char *)param_1 + 0x48);
                        if ((*(unsigned long *)((char *)param_1 + 0x40) <= v11) ||
                            (0x19 < ((*(unsigned char *)(*(long *)((char *)param_1 + 0x38) + v11) & 0xdf) - 0x41))) {
                            bv18 = true;
                            goto LAB_003a69d8;
                        }
                        *(unsigned long *)((char *)param_1 + 0x48) = v11 + 1;
                        iv13 = (int)*(char *)(*(long *)((char *)param_1 + 0x38) + v11);
                        v8 = (unsigned int)(iv13 - 0x61);
                        iv9 = -0x61;
                        if (0x19 < v8) {
                            iv9 = -0x41;
                        }
                        iv9 = iv9 + iv13;
                        if (*(int *)((char *)param_1 + 0x218) <= iv9) {
                            return (unsigned long *)0x0;
                        }
                        pu1 = (unsigned long *)((char *)param_1 + 0x78 + (long)iv9 * 0x10);
                        FUN_003a3a70((long *)&loc70, (unsigned long)*pu1, (long)pu1[1], (unsigned long)param_1);
                    } while ((v8 & 0xff) < 0x1a);
                    bv18 = false;
                    v11 = *(unsigned long *)((char *)param_1 + 0x48);
                } else {
                    bv18 = false;
                }
LAB_003a69d8:
                if ((v11 < *(unsigned long *)((char *)param_1 + 0x40)) &&
                    (*(char *)(*(long *)((char *)param_1 + 0x38) + v11) == '0')) {
                    *(unsigned long *)((char *)param_1 + 0x48) = v11 + 1;
                    break;
                }
                v8 = FUN_003ac430(param_1);
                if ((int)v8 < 1) {
                    return (unsigned long *)0x0;
                }
                v11 = *(unsigned long *)((char *)param_1 + 0x48);
                if (bv5) {
                    /* "0"-prefixed big-number path */
                    if ((v11 < *(unsigned long *)((char *)param_1 + 0x40)) &&
                        (*(char *)(*(long *)((char *)param_1 + 0x38) + v11) == '_')) {
                        v11 = v11 + 1;
                        *(unsigned long *)((char *)param_1 + 0x48) = v11;
                    }
                    if (*(unsigned long *)((char *)param_1 + 0x40) < v11 + v8) {
                        return (unsigned long *)0x0;
                    }
                    loc88 = (unsigned long *)0x0;
                    uStack_80 = 0;
                    loc78 = 0;
                    iv9 = FUN_003bed8c(*(long *)((char *)param_1 + 0x38) + v11, v8, &loc88);
                    if (iv9 == 0) {
                        if (-1 < (long)loc78) {
                            return (unsigned long *)0x0;
                        }
                        thunk_FUN_00012568(loc88, loc78 & 0x7fffffffffffffffUL);
                        return (unsigned long *)0x0;
                    }
                    v11 = uStack_80;
                    if (-1 < (long)loc78) {
                        v11 = loc78 >> 0x38;
                        FUN_003a3a70((long *)&loc70, (unsigned long)&loc88, (long)v11, (unsigned long)param_1);
                    } else {
                        FUN_003a3a70((long *)&loc70, (unsigned long)loc88, (long)v11, (unsigned long)param_1);
                    }
                    if ((long)loc78 < 0) {
                        thunk_FUN_00012568(loc88, loc78 & 0x7fffffffffffffffUL);
                    }
                } else {
                    /* plain identifier path with word-boundary interning */
                    if (*(unsigned long *)((char *)param_1 + 0x40) < v11 + v8) {
                        return (unsigned long *)0x0;
                    }
                    lv2 = *(long *)((char *)param_1 + 0x38) + v11;
                    FUN_003a3a70((long *)&loc70, (unsigned long)lv2, (long)(unsigned long)v8, (unsigned long)param_1);
                    v11 = 0;
                    v15 = 0xffffffff;
                    do {
                        v14 = (unsigned int)v15;
                        if (v11 < v8) {
                            v16 = (unsigned int)*(unsigned char *)(lv2 + v11);
                            if ((int)v14 < 0) {
                                goto LAB_003a6b64;
                            }
LAB_003a6b00:
                            if (((v16 == 0) || (v16 == 0x5f)) ||
                                ((v16 - 0x41 < 0x1a &&
                                  (*(unsigned char *)(lv2 + v11 + -1) - 0x5b < 0xffffffe6)))) {
                                if (1 < (int)(v11 + -v14)) {
                                    iv9 = *(int *)((char *)param_1 + 0x218);
                                    if (iv9 < 0x1a) {
                                        *(int *)((char *)param_1 + 0x218) = iv9 + 1;
                                        pl3 = (long *)((char *)param_1 + 0x78 + (long)iv9 * 0x10);
                                        *pl3 = lv2 + v15;
                                        pl3[1] = (long)(v11 + -v14) & 0xffffffff;
                                    }
                                }
                                v14 = 0xffffffff;
                                goto LAB_003a6b64;
                            }
                        } else {
                            v16 = 0;
                            if (-1 < (int)v14) {
                                goto LAB_003a6b00;
                            }
LAB_003a6b64:
                            v4 = (unsigned int)v11;
                            if ((0xfffffff5 < v16 - 0x3a || v16 == 0) || v16 == 0x5f) {
                                v4 = v14;
                            }
                            v15 = (unsigned long)v4;
                        }
                        v11 = v11 + 1;
                    } while (v8 + 1 != v11);
                }
                v11 = *(long *)((char *)param_1 + 0x48) + (unsigned long)v8;
                *(unsigned long *)((char *)param_1 + 0x48) = v11;
                bv12 = true;
            } while (bv18);
            if ((int)loc68 != 0) {
                unsigned long *node;
                node = (unsigned long *)FUN_003a3898((unsigned long)param_1, (unsigned long)1);
                *(unsigned short *)((char *)node + 0x10) = 0x67;
                *(unsigned char *)((char *)node + 0x12) = 3;
                *node = (unsigned long)loc70;
                node[1] = loc68 & 0xffffffff;
                loc88 = node;
                FUN_003ad810((char *)param_1 + 0x68, &loc88, param_1);
                return node;
            }
        }
    }
    return (unsigned long *)0x0;
}

