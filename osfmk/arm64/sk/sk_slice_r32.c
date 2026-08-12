/* Recreated from exclavecore_bundle.t8142.RELEASE.im4p (cL4 Secure Kernel, GL1,
 * arm64e, image base 0) — the cL4 microkernel. Ground truth: Ghidra FUN_ names +
 * addresses in cl4_kernel.raw. Version "cL4 microkernel (cL4 (679.100.61))".
 * All names are estimates unless string/header-matched.
 * Slice: 0x0049a51c-0x0049ee70 (SKR32) — the object-table / hash-set layer.
 * The dense low-address run (0x49a51c-0x49a82c) are generic resizable
 * vector/array growth wrappers keyed by element stride; 0x49a91c-0x49ae44 are
 * hash-set insert/lookup helpers (open-addressing sets of 8-byte words,
 * 32-bit ints, and 16-byte key/value pairs) with growth via
 * 0x49af70/0x49b180/0x49b390 and compacting copies via 0x49b5b8/0x49b6fc/
 * 0x49b840; 0x49b99c/0x49bbf0/0x49be44 are in-place growing rehashers.
 * 0x49c0a8-0x49c5f8 are small set/vector element ops (mark, pop, push,
 * reserve). The 0x49c8xx-0x49ee70 tail is a large syscall/collection dispatch
 * region (swift-style runtime metadata, tagged-storage setters, bitmap
 * state words at +0x98/+0x148, and many 16-byte metadata-word shuffles that
 * hand 6-11 word structs through FUN_004aac88/FUN_0049c904). */

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <string.h>

#include "sk_internal.h"

/* ------------------------------------------------------------------ *
 * Hardware / intrinsic helpers (same semantics as the Ghidra pseudo-ops
 * used in the decompiles).
 * ------------------------------------------------------------------ */
static inline unsigned sk_clz64(uint64_t x) { return (unsigned)__builtin_clzll(x); }
#define LZCOUNT(x) sk_clz64((uint64_t)(x))
static inline void sk_break(uint64_t a, uint64_t b) __attribute__((noreturn))
{ (void)a; (void)b; __asm__ volatile("brk #1"); }
#define SoftwareBreakpoint(a,b) sk_break((uint64_t)(a),(uint64_t)(b))
static inline int sk_scarry8(int64_t a, int64_t b) { int64_t r; return __builtin_add_overflow(a, b, &r); }
static inline int sk_sborrow8(int64_t a, int64_t b) { int64_t r; return __builtin_sub_overflow(a, b, &r); }
#define SCARRY8(a,b) sk_scarry8((int64_t)(a),(int64_t)(b))
#define SBORROW8(a,b) sk_sborrow8((int64_t)(a),(int64_t)(b))
#define CONCAT71(hi7, lo1) (((uint64_t)(hi7) << 8) | (uint64_t)(uint8_t)(lo1))

/* ------------------------------------------------------------------ *
 * Shared 16-byte word pair (aarch64e ABI). Many functions in this slice
 * return / hand a 16-byte object in x0:x1. lo lands in x0, hi in x1. hi
 * usually carries an object-type tag in its top byte plus a value/pointer;
 * lo is a small constant or an 8-byte ASCII name.
 * ------------------------------------------------------------------ */
typedef struct {
    uint64_t lo;   /* x0 */
    uint64_t hi;   /* x1 */
} cl4_pair_t;

/* ------------------------------------------------------------------ *
 * Out-of-range cL4 helpers called from this slice (declared extern with a
 * one-line note; their bodies are reconstructed by the range workers that own
 * them). Ground truth FUN_ address in comment. Old-style () = unspecified
 * parameter list so calls of any arity compile; return type is set where the
 * helper's value is consumed.
 * ------------------------------------------------------------------ */

/* 0x0000xxxx low kernel / hash base helpers. */
extern unsigned long FUN_00002534();                 /* alloc/alloc-class by (meta, kind) */
extern void         FUN_000026e8();                  /* lock release (x19+0x18 key) */
extern void         FUN_00021480();                  /* small no-arg release */
extern void         FUN_00027614();                  /* init/register by (key, kind) */
extern void         FUN_00071fe4();                  /* memmove */
extern void         FUN_00084220();                  /* cpu/domain save */
extern void         FUN_00084234();                  /* cpu/domain restore */
extern void         FUN_0008e500();                  /* launch/report pair */
extern cl4_pair_t   FUN_0008e518();                  /* launch image pair */
extern void         FUN_000b02c0();                  /* memset of bitmap words */
extern void         FUN_000b3910();                  /* hash-set commit (set mark) */
extern void         FUN_000b394c();                  /* hash-set commit (set mark, pair) */
extern void         FUN_000b4390();                  /* guard-level entry */
extern void         FUN_000dce50();                  /* per-cpu dealloc */

/* 0x0010xxxx hashing / hash-set primitives. */
extern void         FUN_00117cc4();                  /* memcpy */
extern void         FUN_00117d14();                  /* memmove */
extern void         FUN_001a84f4();                  /* hash context save */
extern unsigned long FUN_001a8564();                 /* hash step result */
extern void         FUN_001b9084();                  /* hash feed pair */

/* 0x0020xxxx hash-set / allocation helpers. */
extern void         FUN_0022995c();                  /* hash feed int */
extern unsigned long FUN_00258c60();                 /* grow bucket allocation */
extern void         FUN_002591b4();                  /* panic (kind) */
extern unsigned long FUN_0025a840();                 /* bucket array grow */
extern unsigned long FUN_0025b994();                 /* bucket array (re)alloc */
extern void         FUN_0025bddc();                  /* panic (kind) */
extern unsigned long FUN_002a0cf8();                 /* key pair compare */

/* 0x0030xxxx runtime / metadata helpers. */
extern void         FUN_0032b65c();                  /* memcpy */
extern void         FUN_0034b07c();                  /* vmethod slot */
extern cl4_pair_t   FUN_0034b264();                  /* metadata context pair */
extern void         FUN_0034be0c();                  /* obj retain */
extern cl4_pair_t   FUN_0034f2f4();                  /* metadata pair */
extern cl4_pair_t   FUN_003504d0();                  /* metadata pair */
extern void         FUN_003509c8();                  /* dispatch on fn ptr */
extern cl4_pair_t   FUN_00350a04();                  /* metadata pair */
extern void         FUN_00350af4();                  /* metadata init */
extern void         FUN_00350bfc();                  /* metadata step */
extern void         FUN_00350c5c();                  /* metadata enter */
extern cl4_pair_t   FUN_00351274();                  /* metadata pair */
extern void         FUN_00351774();                  /* runtime tail */
extern void         FUN_0035193c();                  /* metadata pre */
extern void         FUN_00351aec();                  /* metadata pre2 */
extern cl4_pair_t   FUN_00352b20();                  /* runtime pair */
extern void         FUN_003540d0();                  /* 3-arg runtime call */
extern void         FUN_00355538();                  /* runtime tail2 */
extern void         FUN_0035bc70();                  /* memset */
extern void         FUN_0036b118();                  /* obj release */
extern void         FUN_0036b21c();                  /* runtime tail / return */
extern void         FUN_0036b270();                  /* obj retain */
extern void         FUN_00374104();                  /* register / add-observation */
extern void         FUN_00376820();                  /* runtime lazy init */
extern void         FUN_003a25d4();                  /* obj release (value) */
extern unsigned long FUN_003a261c();                 /* obj retain (value) */

/* 0x0045xxxx collection / syscall helpers. */
extern void         FUN_004588cc();                  /* dispatch */
extern void         FUN_00458940();                  /* dispatch */
extern void         FUN_00458db4();                  /* dispatch */
extern void         FUN_00459138();                  /* dispatch case 7 */
extern void         FUN_004592dc();                  /* dispatch case 4 */
extern void         FUN_004593ac();                  /* dispatch */
extern void         FUN_0045a1f8();                  /* dispatch case 4 */
extern void         FUN_0045a4b4();                  /* dispatch case 7 */
extern void         FUN_0045c160();                  /* dispatch */
extern void         FUN_0045c1e0();                  /* dispatch */

/* 0x0046xxxx collection / runtime helpers. */
extern void         FUN_00462b6c();                  /* dispatch pre */
extern void         FUN_00462fec();                  /* dispatch */
extern cl4_pair_t   FUN_00463028();                  /* metadata pair */
extern void         FUN_00463080();                  /* dispatch */
extern void         FUN_004630d8();                  /* metadata enter */
extern void         FUN_00463810();                  /* dispatch */
extern void         FUN_00464864();                  /* dispatch */
extern void         FUN_00466104();                  /* dispatch tail */

/* 0x0049xxxx below this slice (owned by earlier range workers). */
extern void         FUN_00490b14();                  /* metadata error path */
extern void         FUN_00491db4();                  /* object table release */
extern void         FUN_00498328();                  /* value carrier (pair copy) */
extern unsigned long FUN_0049849c();                 /* object alloc */
extern void         FUN_00498500();                  /* memmove */
extern void         FUN_0049860c();                  /* object init */
extern void         FUN_00498cc8();                  /* value carrier */
extern unsigned long FUN_00498e50();                  /* carrier getter */
extern unsigned long FUN_00498f0c();                  /* carrier getter */
extern void         FUN_00499158();                  /* set mark / grow */
extern unsigned long FUN_0049952c();                  /* carrier getter */
extern unsigned long FUN_004995e4();                  /* carrier getter */
extern unsigned long FUN_004996a8();                  /* carrier getter */
extern unsigned long FUN_0049976c();                  /* carrier getter */
extern void         FUN_00499a0c();                  /* value carrier */
extern void         FUN_00499cfc();                  /* compact move */
extern void         FUN_00499d38();                  /* compact move */
extern void         FUN_00499d7c();                  /* compact move */
extern cl4_pair_t   FUN_00499f0c();                  /* object 16-byte pair */
extern void         FUN_00499fcc();                  /* object release pair */
extern void         FUN_0049a348();                  /* vector grow (stride 8) */
extern void         FUN_0049a3c0();                  /* vector grow (stride) */
extern void         FUN_0049a468();                  /* vector ensure writable */
extern void         FUN_0049a4b8();                  /* vector ensure writable */

/* 0x004axxxx collection / runtime helpers above this slice. */
extern void         FUN_004a2754();                  /* set slot */
extern void         FUN_004a3550();                  /* vector copy-in */
extern void         FUN_004a4b14();                  /* metadata emit */
extern void         FUN_004aaa88();                  /* dispatch */
extern void         FUN_004aabb8();                  /* metadata build */
extern void         FUN_004aac88();                  /* big dispatch (12-16 words) */
extern void         FUN_004aadb8();                  /* metadata context */
extern void         FUN_004aae88();                  /* dispatch tail */
extern void         FUN_004ab10c();                  /* metadata init */
extern void         FUN_004ab13c();                  /* metadata pre */
extern void         FUN_004ab150();                  /* metadata init */
extern unsigned long FUN_004ab2dc();                 /* metadata slot ptr */
extern void         FUN_004ab600();                  /* metadata step */
extern void         FUN_004ab67c();                  /* big dispatch (6-8 words) */
extern void         FUN_004ab868();                  /* metadata tail */
extern void         FUN_004ab954();                  /* metadata release */
extern void         FUN_004ab9a4();                  /* metadata alloc */
extern void         FUN_004abb1c();                  /* 4-word dispatch */
extern void         FUN_004abb64();                  /* metadata init */
extern void         FUN_004abdd0();                  /* dispatch tail */
extern void         FUN_004abdec();                  /* dispatch tail */
extern void         FUN_004abe08();                  /* dispatch tail */
extern void         FUN_004abe40();                  /* dispatch tail */
extern void         FUN_004abf50();                  /* obj release slot */
extern void         FUN_004ac050();                  /* bitmap fill */
extern void         FUN_004ac264();                  /* metadata enter */
extern void         FUN_004ac390();                  /* metadata enter */
extern void         FUN_004ac3a8();                  /* metadata enter */
extern void         FUN_004ac3c0();                  /* metadata enter */
extern void         FUN_004ac87c();                  /* dispatch */
extern void         FUN_004ac908();                  /* dispatch */
extern void         FUN_004aca6c();                  /* metadata enter */
extern void         FUN_004acac0();                  /* metadata enter */
extern void         FUN_004acacc();                  /* runtime report */
extern cl4_pair_t   FUN_004acae8();                  /* metadata pair */
extern void         FUN_004acb80();                  /* metadata pre */

/* Thunk wrappers to the retained/release pairs (per contract, old-style). */
extern void         thunk_FUN_00114330();
extern void         thunk_FUN_002298d4();
extern void         thunk_FUN_0036b270();

/* Forward declarations for mutually-referencing in-slice functions. */
void FUN_0049ac48(uint64_t param_1, uint64_t param_2, uint64_t param_3);
void FUN_0049ad48(uint64_t param_1, uint64_t param_2, uint64_t param_3);
void FUN_0049ae44(long param_1, long param_2, uint64_t param_3, uint64_t param_4);
void FUN_0049af70(long param_1);
void FUN_0049b180(long param_1);
void FUN_0049b390(long param_1);
void FUN_0049b5b8(void);
void FUN_0049b6fc(void);
void FUN_0049b840(void);
void FUN_0049b99c(void);
void FUN_0049bbf0(void);
void FUN_0049be44(void);
void FUN_0049c0a8(uint64_t param_1, uint64_t param_2, long param_3);

/* ================================================================== *
 * Resizable vector / set growth wrappers (0x49a51c-0x49a82c).
 * ================================================================== */

/* FUN_0049a51c @ 0x0049a51c
 * Ghidra: void FUN_0049a51c(long param_1)
 * Grow the word set under x20 by appending the element at param_1+0x10 via
 * FUN_00499158 (mark-and-grow). Confidence: medium.
 * Notes: vector state at x20: +0x10 = length, +0x18 = capacity. */
void FUN_0049a51c(long param_1)
{
    FUN_00499158(0, *(uint64_t *)(param_1 + 0x10), 0, param_1);
}

/* FUN_0049a530 @ 0x0049a530
 * Ghidra: void FUN_0049a530(void)
 * Store the result of the getter FUN_00498f0c into *x20 (the head word of
 * the current collection context). Confidence: medium. */
void FUN_0049a530(void)
{
    uint64_t value;
    uint64_t *head;
    value = FUN_00498f0c();
    *head = value;
}

/* FUN_0049a550 @ 0x0049a550
 * Ghidra: void FUN_0049a550(void)
 * Store the result of the getter FUN_00498e50 into *x20. Confidence: medium. */
void FUN_0049a550(void)
{
    uint64_t value;
    uint64_t *head;
    value = FUN_00498e50();
    *head = value;
}

/* FUN_0049a5ac @ 0x0049a5ac
 * Ghidra: void FUN_0049a5ac(void)
 * Store the result of the getter FUN_0049952c into *x20. Confidence: medium. */
void FUN_0049a5ac(void)
{
    uint64_t value;
    uint64_t *head;
    value = FUN_0049952c();
    *head = value;
}

/* FUN_0049a5e4 @ 0x0049a5e4
 * Ghidra: void FUN_0049a5e4(void)
 * Store the result of the getter FUN_004996a8 into *x20. Confidence: medium. */
void FUN_0049a5e4(void)
{
    uint64_t value;
    uint64_t *head;
    value = FUN_004996a8();
    *head = value;
}

/* FUN_0049a5e8 @ 0x0049a5e8
 * Ghidra: void FUN_0049a5e8(void)
 * Identical to 0049a5e4: store the getter FUN_004996a8 result into *x20.
 * Confidence: medium. */
void FUN_0049a5e8(void)
{
    uint64_t value;
    uint64_t *head;
    value = FUN_004996a8();
    *head = value;
}

/* FUN_0049a604 @ 0x0049a604
 * Ghidra: void FUN_0049a604(void)
 * Store the result of the getter FUN_0049976c into *x20. Confidence: medium. */
void FUN_0049a604(void)
{
    uint64_t value;
    uint64_t *head;
    value = FUN_0049976c();
    *head = value;
}

/* FUN_0049a624 @ 0x0049a624
 * Ghidra: void FUN_0049a624(void)
 * Store the result of the getter FUN_004995e4 into *x20. Confidence: medium. */
void FUN_0049a624(void)
{
    uint64_t value;
    uint64_t *head;
    value = FUN_004995e4();
    *head = value;
}

/* FUN_0049a644 @ 0x0049a644
 * Ghidra: void FUN_0049a644(long param_1)
 * Grow the collection under x20 and append the element described by param_1.
 * The element's stride is 0x160 bytes (from the +0x18 slot of the owning
 * bucket object); a free slot at *x20+0x10 is located by scanning the
 * occupancy bitmap at +0x38, then the new element is copied in from
 * param_1+0x20. Aborts at SoftwareBreakpoint 0x49a748/74c/750/754/758 on
 * any overflow or capacity mismatch. Confidence: medium. */
void FUN_0049a644(long param_1)
{
    uint64_t count;          /* uVar3 = *(param_1+0x10) */
    uint64_t capacity_head;  /* *unaff_x20 */
    uint64_t avail;          /* uVar1 */
    long   bucket;           /* lVar4 = *unaff_x20 */

    capacity_head = *(uint64_t *)0;         /* *unaff_x20 (collection head) */
    count = *(uint64_t *)(param_1 + 0x10);
    if (SCARRY8(*(long *)(capacity_head + 0x10), count)) {
        SoftwareBreakpoint(1, 0x49a748);
    }
    FUN_0049a3c0(*(long *)(capacity_head + 0x10) + count, 1,
                 FUN_00498328, (void *)0x49853c, FUN_00499a0c, FUN_00498e50);
    bucket = *(long *)0;                    /* *unaff_x20 */
    avail = (*(uint64_t *)(bucket + 0x18) >> 1) - *(long *)(bucket + 0x10);
    if (avail >= (uint64_t)0x8000000000000000) {
        /* -1 < (long)avail was false -> avail is negative */
        SoftwareBreakpoint(1, 0x49a74c);
    }
    if (*(long *)(param_1 + 0x10) == 0) {
        FUN_0036b118(param_1);
        if (count != 0) {
            SoftwareBreakpoint(1, 0x49a750);
        }
    } else {
        if (avail < count) {
            SoftwareBreakpoint(1, 0x49a754);
        }
        FUN_00499d38(param_1 + 0x20, count,
                     bucket + *(long *)(bucket + 0x10) * 0x160 + 0x20);
        FUN_0036b118(param_1);
        if (count != 0) {
            if (SCARRY8(*(long *)(bucket + 0x10), count)) {
                SoftwareBreakpoint(1, 0x49a758);
            }
            *(uint64_t *)(bucket + 0x10) = *(long *)(bucket + 0x10) + count;
        }
    }
    *(uint64_t *)0 = bucket;                /* *unaff_x20 = lVar4 */
}

/* FUN_0049a758 @ 0x0049a758
 * Ghidra: void FUN_0049a758(long param_1)
 * Grow the 8-byte-word vector under x20 and append the element from param_1
 * (stride 8). Free-slot scan, copy-in from param_1+0x20, and capacity checks
 * as in 0049a644 but with the stride-8 compact move FUN_00499cfc and grower
 * FUN_0049a348. Aborts at SoftwareBreakpoint 0x49a81c/820/824/828/82c.
 * Confidence: medium. */
void FUN_0049a758(long param_1)
{
    uint64_t count;
    uint64_t capacity_head;
    uint64_t avail;
    long   bucket;

    capacity_head = *(uint64_t *)0;         /* *unaff_x20 */
    count = *(uint64_t *)(param_1 + 0x10);
    if (SCARRY8(*(long *)(capacity_head + 0x10), count)) {
        SoftwareBreakpoint(1, 0x49a81c);
    }
    FUN_0049a348(*(long *)(capacity_head + 0x10) + count, 1, FUN_00498f0c);
    bucket = *(long *)0;
    avail = (*(uint64_t *)(bucket + 0x18) >> 1) - *(long *)(bucket + 0x10);
    if (avail >= (uint64_t)0x8000000000000000) {
        SoftwareBreakpoint(1, 0x49a820);
    }
    if (*(long *)(param_1 + 0x10) == 0) {
        FUN_0036b118(param_1);
        if (count != 0) {
            SoftwareBreakpoint(1, 0x49a824);
        }
    } else {
        if (avail < count) {
            SoftwareBreakpoint(1, 0x49a828);
        }
        FUN_00499cfc(param_1 + 0x20, count,
                     bucket + *(long *)(bucket + 0x10) * 8 + 0x20);
        FUN_0036b118(param_1);
        if (count != 0) {
            if (SCARRY8(*(long *)(bucket + 0x10), count)) {
                SoftwareBreakpoint(1, 0x49a82c);
            }
            *(uint64_t *)(bucket + 0x10) = *(long *)(bucket + 0x10) + count;
        }
    }
    *(uint64_t *)0 = bucket;
}

/* FUN_0049a82c @ 0x0049a82c
 * Ghidra: void FUN_0049a82c(long param_1)
 * Grow the 24-byte-element vector under x20 and append the element from
 * param_1 (stride 0x18). Uses the metadata-function grower FUN_0049a3c0 with
 * data descriptors &DAT_00657e40 / &DAT_005a5578 / &DAT_00688878 and the
 * getter FUN_0049952c; compact move FUN_00499d7c. Aborts at SoftwareBreakpoint
 * 0x49a90c/910/914/918/91c. Confidence: medium. */
void FUN_0049a82c(long param_1)
{
    uint64_t count;
    uint64_t capacity_head;
    uint64_t avail;
    long   bucket;

    capacity_head = *(uint64_t *)0;         /* *unaff_x20 */
    count = *(uint64_t *)(param_1 + 0x10);
    if (SCARRY8(*(long *)(capacity_head + 0x10), count)) {
        SoftwareBreakpoint(1, 0x49a90c);
    }
    FUN_0049a3c0(*(long *)(capacity_head + 0x10) + count, 1,
                 (void *)0x657e40, (void *)0x5a5578, (void *)0x688878, FUN_0049952c);
    bucket = *(long *)0;
    avail = (*(uint64_t *)(bucket + 0x18) >> 1) - *(long *)(bucket + 0x10);
    if (avail >= (uint64_t)0x8000000000000000) {
        SoftwareBreakpoint(1, 0x49a910);
    }
    if (*(long *)(param_1 + 0x10) == 0) {
        FUN_0036b118(param_1);
        if (count != 0) {
            SoftwareBreakpoint(1, 0x49a914);
        }
    } else {
        if (avail < count) {
            SoftwareBreakpoint(1, 0x49a918);
        }
        FUN_00499d7c(param_1 + 0x20, count,
                     bucket + *(long *)(bucket + 0x10) * 0x18 + 0x20);
        FUN_0036b118(param_1);
        if (count != 0) {
            if (SCARRY8(*(long *)(bucket + 0x10), count)) {
                SoftwareBreakpoint(1, 0x49a91c);
            }
            *(uint64_t *)(bucket + 0x10) = *(long *)(bucket + 0x10) + count;
        }
    }
    *(uint64_t *)0 = bucket;
}

/* FUN_0049a91c @ 0x0049a91c
 * Ghidra: bool FUN_0049a91c(ulong *param_1, ulong param_2)
 * Open-addressing set lookup for an 8-byte word keyed by its page index
 * (value >> 0xe). Starting from the hash slot FUN_001a8564 (seeded by
 * param_2's page and the set's hash context at +0x28), walk the occupancy
 * bitmap (+0x38) probing each set slot at +0x30. If a slot with the same
 * page index is found, return it in *param_1 (found, returns false). If a
 * hole is reached, insert via FUN_0049ac48 and return the hole index (true =
 * newly inserted). Confidence: medium. */
bool FUN_0049a91c(uint64_t *param_1, uint64_t param_2)
{
    uint64_t slot;
    uint64_t mask;
    uint64_t element;
    uint64_t insert_flag;      /* uVar3 = FUN_003a261c(*unaff_x20) */
    long   set;                 /* lVar5 = *unaff_x20 */
    long   local_98[9];

    set = *(long *)0;           /* *unaff_x20 */
    FUN_001a84f4(local_98, *(uint64_t *)(set + 0x28));
    thunk_FUN_002298d4(param_2 >> 0xe);
    slot = FUN_001a8564();
    while (true) {
        slot = slot & ~(-1ULL << ((uint64_t)*(uint8_t *)(set + 0x20) & 0x3f));
        mask = 1ULL << (slot & 0x3f) & *(uint64_t *)(set + 0x38 + (slot >> 6) * 8);
        if (mask == 0) break;
        element = *(uint64_t *)(*(long *)(set + 0x30) + slot * 8);
        if (param_2 >> 0xe == element >> 0xe) goto found;
        slot = slot + 1;
    }
    insert_flag = FUN_003a261c(*(uint64_t *)0);
    local_98[0] = *(long *)0;
    FUN_0049ac48(param_2, slot, insert_flag);
    *(long *)0 = local_98[0];
    element = param_2;
found:
    *param_1 = element;
    return mask == 0;
}

/* FUN_0049aa14 @ 0x0049aa14
 * Ghidra: bool FUN_0049aa14(int *param_1, undefined8 param_2)
 * Open-addressing set lookup for 32-bit int keys. Probe the occupancy bitmap
 * from the hash of param_2 (FUN_0022995c), compare int values at +0x30.
 * Insert via FUN_0049ad48 on a hole. Returns true if newly inserted.
 * Confidence: medium. */
bool FUN_0049aa14(int *param_1, uint64_t param_2)
{
    uint64_t slot;
    uint64_t mask;
    uint64_t insert_flag;
    long   set;
    long   local_98[9];

    set = *(long *)0;           /* *unaff_x20 */
    FUN_001a84f4(local_98, *(uint64_t *)(set + 0x28));
    FUN_0022995c(param_2);
    slot = FUN_001a8564();
    while (true) {
        slot = slot & ~(-1ULL << ((uint64_t)*(uint8_t *)(set + 0x20) & 0x3f));
        mask = 1ULL << (slot & 0x3f) & *(uint64_t *)(set + 0x38 + (slot >> 6) * 8);
        if (mask == 0) break;
        if (*(int *)(*(long *)(set + 0x30) + slot * 4) == (int)param_2) goto found;
        slot = slot + 1;
    }
    insert_flag = FUN_003a261c(*(uint64_t *)0);
    local_98[0] = *(long *)0;
    FUN_0049ad48(param_2, slot, insert_flag);
    *(long *)0 = local_98[0];
found:
    *param_1 = (int)param_2;
    return mask == 0;
}

/* FUN_0049ab00 @ 0x0049ab00
 * Ghidra: bool FUN_0049ab00(long *param_1, long param_2, long param_3)
 * Open-addressing map lookup for 16-byte key/value pairs. Probe from the
 * hash of (param_2,param_3) using FUN_001b9084; on a matching pair (equal or
 * the key-compare FUN_002a0cf8 with bit 0 set) return it via *param_1 and
 * *param_1[1]; on a hole insert via FUN_0049ae44 (retaining param_3 first,
 * thunk_FUN_0036b270). Returns true if newly inserted. Confidence: medium. */
bool FUN_0049ab00(long *param_1, long param_2, long param_3)
{
    long  *entry;
    uint64_t mask;
    long   key_lo, key_hi;
    long   set;
    long   cmp;
    uint8_t shift;
    uint64_t slot;
    uint64_t reserve;
    long   local_a8[9];

    set = *(long *)0;           /* *unaff_x20 */
    FUN_001a84f4(local_a8, *(uint64_t *)(set + 0x28));
    FUN_001b9084(local_a8, param_2, param_3);
    slot = FUN_001a8564();
    shift = *(uint8_t *)(set + 0x20);
    do {
        slot = slot & ~(-1ULL << ((uint64_t)shift & 0x3f));
        mask = 1ULL << (slot & 0x3f) & *(uint64_t *)(set + 0x38 + (slot >> 6) * 8);
        if (mask == 0) {
            reserve = FUN_003a261c(*(uint64_t *)0);
            local_a8[0] = *(long *)0;
            thunk_FUN_0036b270(param_3);
            FUN_0049ae44(param_2, param_3, slot, reserve);
            *(long *)0 = local_a8[0];
            *param_1 = param_2;
            param_1[1] = param_3;
            return mask == 0;
        }
        entry = (long *)(*(long *)(set + 0x30) + slot * 0x10);
        key_lo = *entry;
        key_hi = entry[1];
        if ((key_lo == param_2 && key_hi == param_3) ||
            (cmp = FUN_002a0cf8(key_lo, key_hi, param_2, param_3, 0), (cmp & 1) != 0)) {
            FUN_003a25d4(param_3);
            entry = (long *)(*(long *)(set + 0x30) + slot * 0x10);
            set = entry[1];
            *param_1 = *entry;
            param_1[1] = set;
            thunk_FUN_0036b270();
            return mask == 0;
        }
        slot = slot + 1;
    } while (true);
}

/* FUN_0049ac48 @ 0x0049ac48
 * Ghidra: void FUN_0049ac48(ulong param_1, ulong param_2, ulong param_3)
 * Commit an 8-byte-word insert into the set under x20 at slot param_2,
 * growing the bucket array first if full (param_2 >= capacity): if the
 * caller flag (param_3 bit 0) is clear, grow via FUN_0049af70 (count+1) else
 * FUN_0049b99c; then recompute the hash, rescan for an existing equal page
 * index (aborting via FUN_0025bddc(0x675628) if present — a duplicate), and
 * finally mark the slot with FUN_000b3910. Confidence: medium. */
void FUN_0049ac48(uint64_t param_1, uint64_t param_2, uint64_t param_3)
{
    uint64_t slot;
    long   set;
    uint8_t bucket[72];

    if (*(uint64_t *)(*(uint64_t *)0 + 0x10) < *(uint64_t *)(*(uint64_t *)0 + 0x18)) {
        if ((param_3 & 1) == 0) {
            FUN_0049b5b8();
        }
    } else {
        if ((param_3 & 1) == 0) {
            FUN_0049af70(*(uint64_t *)(*(uint64_t *)0 + 0x10) + 1);
        } else {
            FUN_0049b99c();
        }
        set = *(long *)0;
        FUN_001a84f4(bucket, *(uint64_t *)(set + 0x28));
        thunk_FUN_002298d4(param_1 >> 0xe);
        param_2 = FUN_001a8564();
        while (param_2 = param_2 & ~(-1ULL << ((uint64_t)*(uint8_t *)(set + 0x20) & 0x3f)),
               (*(uint64_t *)(set + 0x38 + (param_2 >> 6) * 8) >> (param_2 & 0x3f) & 1) != 0) {
            if (param_1 >> 0xe == *(uint64_t *)(*(long *)(set + 0x30) + param_2 * 8) >> 0xe) {
                FUN_0025bddc(0x675628);      /* duplicate insert -> panic */
            }
            param_2 = param_2 + 1;
        }
    }
    FUN_000b3910(param_1, param_2, *(uint64_t *)0);
}

/* FUN_0049ad48 @ 0x0049ad48
 * Ghidra: void FUN_0049ad48(undefined8 param_1, ulong param_2, ulong param_3)
 * Commit a 32-bit-int insert into the set under x20 at slot param_2. Grows via
 * FUN_0049b6fc (count+1, flag clear) or FUN_0049bbf0 (flag set), rescans for
 * a duplicate int (FUN_0025bddc(0x6740f8) abort), then marks with
 * FUN_0049c0a8. Confidence: medium. */
void FUN_0049ad48(uint64_t param_1, uint64_t param_2, uint64_t param_3)
{
    uint64_t slot;
    long   set;
    uint8_t bucket[72];

    if (*(uint64_t *)(*(uint64_t *)0 + 0x10) < *(uint64_t *)(*(uint64_t *)0 + 0x18)) {
        if ((param_3 & 1) == 0) {
            FUN_0049b6fc();
        }
    } else {
        if ((param_3 & 1) == 0) {
            FUN_0049b180(*(uint64_t *)(*(uint64_t *)0 + 0x10) + 1);
        } else {
            FUN_0049bbf0();
        }
        set = *(long *)0;
        FUN_001a84f4(bucket, *(uint64_t *)(set + 0x28));
        FUN_0022995c(param_1);
        param_2 = FUN_001a8564();
        while (param_2 = param_2 & ~(-1ULL << ((uint64_t)*(uint8_t *)(set + 0x20) & 0x3f)),
               (*(uint64_t *)(set + 0x38 + (param_2 >> 6) * 8) >> (param_2 & 0x3f) & 1) != 0) {
            if (*(int *)(*(long *)(set + 0x30) + param_2 * 4) == (int)param_1) {
                FUN_0025bddc(0x6740f8);      /* duplicate insert -> panic */
            }
            param_2 = param_2 + 1;
        }
    }
    FUN_0049c0a8(param_1, param_2, *(uint64_t *)0);
}

/* FUN_0049ae44 @ 0x0049ae44
 * Ghidra: void FUN_0049ae44(long param_1, long param_2, ulong param_3, ulong param_4)
 * Commit a 16-byte key/value insert into the set under x20 at slot param_3.
 * Grows via FUN_0049b840 (count+1, flag clear), FUN_0049b390 or FUN_0049be44
 * (flag set); rescans for a duplicate pair (abort via FUN_0025bddc(0x6728f0)),
 * then marks with FUN_000b394c. Confidence: medium. */
void FUN_0049ae44(long param_1, long param_2, uint64_t param_3, uint64_t param_4)
{
    long  *entry;
    long   key_lo, key_hi;
    uint8_t shift;
    uint64_t slot;
    long   set;
    uint8_t bucket[72];

    if (*(uint64_t *)(*(uint64_t *)0 + 0x10) < *(uint64_t *)(*(uint64_t *)0 + 0x18)) {
        if ((param_4 & 1) == 0) {
            FUN_0049b840();
        }
    } else {
        if ((param_4 & 1) == 0) {
            FUN_0049b390(*(uint64_t *)(*(uint64_t *)0 + 0x10) + 1);
        } else {
            FUN_0049be44();
        }
        set = *(long *)0;
        FUN_001a84f4(bucket, *(uint64_t *)(set + 0x28));
        FUN_001b9084(bucket, param_1, param_2);
        param_3 = FUN_001a8564();
        shift = *(uint8_t *)(set + 0x20);
        while (param_3 = param_3 & ~(-1ULL << ((uint64_t)shift & 0x3f)),
               (*(uint64_t *)(set + 0x38 + (param_3 >> 6) * 8) >> (param_3 & 0x3f) & 1) != 0) {
            entry = (long *)(*(long *)(set + 0x30) + param_3 * 0x10);
            key_lo = *entry;
            key_hi = entry[1];
            if ((key_lo == param_1 && key_hi == param_2) ||
                (param_4 = FUN_002a0cf8(key_lo, key_hi, param_1, param_2, 0), (param_4 & 1) != 0)) {
                FUN_0025bddc(0x6728f0);      /* duplicate insert -> panic */
            }
            param_3 = param_3 + 1;
        }
    }
    FUN_000b394c(param_1, param_2, param_3, *(uint64_t *)0);
}

/* FUN_0049af70 @ 0x0049af70
 * Ghidra: void FUN_0049af70(long param_1)
 * Grow the 8-byte-word open-addressing set under x20 to at least param_1
 * slots and rehash every live entry from the old bitmap into the new bucket
 * array. Old set at lVar13, new at FUN_0025a840-allocated lVar5. Each entry
 * is re-inserted by recomputing its hash (thunk_FUN_002298d4 of key>>0xe)
 * and setting the first free bitmap bit (bit-reversal to find the lowest
 * free bit at the probe index). Occupancy bitmap at +0x38 (word bits), value
 * array at +0x30 (8-byte stride). The final array may overlap the old one;
 * the old set is released with FUN_0036b118. Aborts at SoftwareBreakpoint
 * 0x49b148/17c/180 on overflows. Confidence: medium. */
void FUN_0049af70(long param_1)
{
    long   old_len;            /* lVar5 */
    long   new_set;            /* lVar13 */
    uint64_t bitmap;           /* uVar15 */
    uint64_t bit;
    uint64_t idx;              /* uVar7: bit-reversed index */
    uint64_t probe;            /* uVar6 */
    uint64_t cap_mask;         /* uVar11 */
    long   word;               /* lVar14 */
    long   old;
    uint64_t num_words;        /* uVar7 (scan bound) */
    bool   wrapped;
    uint64_t probe_word;       /* uVar8 */
    uint64_t entry;
    long   w2;
    uint8_t stk[72];

    old = *(long *)0;          /* *unaff_x20 */
    old_len = *(long *)(old + 0x18);
    if (*(long *)(old + 0x18) <= param_1) {
        old_len = param_1;
    }
    FUN_00002534((void*)0x657d70, (void*)0x5a4b38);
    new_set = FUN_0025a840(old, old_len, 0, FUN_00002534((void*)0x657d70, (void*)0x5a4b38));
    if (*(long *)(old + 0x10) == 0) {
        FUN_0036b118(old);
        *(uint64_t *)0 = new_set;
        return;
    }
    word = 0;
    cap_mask = 1ULL << ((uint64_t)*(uint8_t *)(old + 0x20) & 0x3f);
    bitmap = 0xffffffffffffffff;
    if ((*(uint8_t *)(old + 0x20) & 0x3f) < 6) {
        bitmap = ~(-1ULL << (cap_mask & 0x3f));
    }
    bitmap = bitmap & *(uint64_t *)(old + 0x38);
    if (bitmap == 0) goto next_word;
    do {
        /* bit-reverse the bitmap word to enumerate set bits low-to-high */
        bit = (bitmap & 0xaaaaaaaaaaaaaaaa) >> 1 | (bitmap & 0x5555555555555555) << 1;
        bit = (bit & 0xcccccccccccccccc) >> 2 | (bit & 0x3333333333333333) << 2;
        bit = (bit & 0xf0f0f0f0f0f0f0f0) >> 4 | (bit & 0xf0f0f0f0f0f0f0f) << 4;
        bit = (bit & 0xff00ff00ff00ff00) >> 8 | (bit & 0xff00ff00ff00ff) << 8;
        bit = (bit & 0xffff0000ffff0000) >> 0x10 | (bit & 0xffff0000ffff) << 0x10;
        bit = bit >> 0x20 | bit << 0x20;
        bitmap = bitmap - 1 & bitmap;
        while (true) {
            entry = *(uint64_t *)(*(long *)(old + 0x30) +
                                  (LZCOUNT(bit) | word << 6) * 8);
            FUN_001a84f4(stk, *(uint64_t *)(new_set + 0x28));
            thunk_FUN_002298d4(entry >> 0xe);
            probe = FUN_001a8564();
            cap_mask = -1ULL << ((uint64_t)*(uint8_t *)(new_set + 0x20) & 0x3f);
            probe = probe & (cap_mask ^ 0xffffffffffffffff);
            probe_word = probe >> 6;
            idx = -1ULL << (probe & 0x3f) &
                  (*(uint64_t *)(new_set + 0x38 + probe_word * 8) ^ 0xffffffffffffffff);
            if (idx == 0) {
                /* No free bit in the probe word: wrap-scan forward for a
                 * non-full word. num_words = capacity>>6. */
                wrapped = false;
                num_words = 0x3f - cap_mask >> 6;
                do {
                    probe = probe_word + 1;
                    if ((probe == num_words) && (wrapped)) {
                        SoftwareBreakpoint(1, 0x49b180);   /* table full */
                    }
                    probe_word = 0;
                    if (probe != num_words) {
                        probe_word = probe;
                    }
                    wrapped = (bool)(probe == num_words | wrapped);
                    probe = *(uint64_t *)(new_set + 0x38 + probe_word * 8);
                } while (probe == 0xffffffffffffffff);
                probe = ~probe;
                idx = (probe & 0xaaaaaaaaaaaaaaaa) >> 1 | (probe & 0x5555555555555555) << 1;
                idx = (idx & 0xcccccccccccccccc) >> 2 | (idx & 0x3333333333333333) << 2;
                idx = (idx & 0xf0f0f0f0f0f0f0f0) >> 4 | (idx & 0xf0f0f0f0f0f0f0f) << 4;
                idx = (idx & 0xff00ff00ff00ff00) >> 8 | (idx & 0xff00ff00ff00ff) << 8;
                idx = (idx & 0xffff0000ffff0000) >> 0x10 | (idx & 0xffff0000ffff) << 0x10;
                idx = LZCOUNT(idx >> 0x20 | idx << 0x20) | probe_word << 6;
            } else {
                idx = (idx & 0xaaaaaaaaaaaaaaaa) >> 1 | (idx & 0x5555555555555555) << 1;
                idx = (idx & 0xcccccccccccccccc) >> 2 | (idx & 0x3333333333333333) << 2;
                idx = (idx & 0xf0f0f0f0f0f0f0f0) >> 4 | (idx & 0xf0f0f0f0f0f0f0f) << 4;
                idx = (idx & 0xff00ff00ff00ff00) >> 8 | (idx & 0xff00ff00ff00ff) << 8;
                idx = (idx & 0xffff0000ffff0000) >> 0x10 | (idx & 0xffff0000ffff) << 0x10;
                idx = LZCOUNT(idx >> 0x20 | idx << 0x20) | probe & 0x7fffffffffffffc0;
            }
            probe_word = idx >> 3 & 0x1ffffffffffffff8;
            *(uint64_t *)(new_set + 0x38 + probe_word) =
                1ULL << (idx & 0x3f) | *(uint64_t *)(new_set + 0x38 + probe_word);
            *(uint64_t *)(*(long *)(new_set + 0x30) + idx * 8) = entry;
            *(long *)(new_set + 0x10) = *(long *)(new_set + 0x10) + 1;
            if (bitmap != 0) break;
next_word:
            do {
                w2 = word + 1;
                if (SCARRY8(word, 1)) {
                    SoftwareBreakpoint(1, 0x49b17c);
                }
                if ((long)(cap_mask + 0x3f >> 6) <= w2) {
                    FUN_0036b118(old);
                    *(uint64_t *)0 = new_set;
                    return;
                }
                bitmap = ((uint64_t *)(old + 0x38))[w2];
                word = word + 1;
            } while (bitmap == 0);
            bit = (bitmap & 0xaaaaaaaaaaaaaaaa) >> 1 | (bitmap & 0x5555555555555555) << 1;
            bit = (bit & 0xcccccccccccccccc) >> 2 | (bit & 0x3333333333333333) << 2;
            bit = (bit & 0xf0f0f0f0f0f0f0f0) >> 4 | (bit & 0xf0f0f0f0f0f0f0f) << 4;
            bit = (bit & 0xff00ff00ff00ff00) >> 8 | (bit & 0xff00ff00ff00ff) << 8;
            bit = (bit & 0xffff0000ffff0000) >> 0x10 | (bit & 0xffff0000ffff) << 0x10;
            bit = bit >> 0x20 | bit << 0x20;
            bitmap = bitmap - 1 & bitmap;
            word = w2;
        }
    } while (true);
}

/* FUN_0049b180 @ 0x0049b180
 * Ghidra: void FUN_0049b180(long param_1)
 * Grow the 32-bit-int open-addressing set under x20 to at least param_1 slots
 * and rehash every live entry. 32-bit value array at +0x30, occupancy bitmap
 * at +0x38. Hash via FUN_0022995c; free-bit scan identical to 0049af70 but
 * storing 32-bit ints. Aborts at SoftwareBreakpoint 0x49b358/38c/390 on
 * overflow / table-full. Confidence: medium. */
void FUN_0049b180(long param_1)
{
    long   old_len;
    long   new_set;
    uint64_t bitmap;
    uint64_t bit;
    uint64_t idx;
    uint64_t probe;
    uint64_t cap_mask;
    long   word;
    long   old;
    uint64_t num_words;
    bool   wrapped;
    uint64_t probe_word;
    uint32_t entry;
    long   w2;
    uint8_t stk[72];

    old = *(long *)0;
    old_len = *(long *)(old + 0x18);
    if (*(long *)(old + 0x18) <= param_1) {
        old_len = param_1;
    }
    FUN_00002534((void*)0x657e00, (void*)0x5a4c00);
    new_set = FUN_0025a840(old, old_len, 0,
                           FUN_00002534((void*)0x657e00, (void*)0x5a4c00));
    if (*(long *)(old + 0x10) == 0) {
        FUN_0036b118(old);
        *(uint64_t *)0 = new_set;
        return;
    }
    word = 0;
    cap_mask = 1ULL << ((uint64_t)*(uint8_t *)(old + 0x20) & 0x3f);
    bitmap = 0xffffffffffffffff;
    if ((*(uint8_t *)(old + 0x20) & 0x3f) < 6) {
        bitmap = ~(-1ULL << (cap_mask & 0x3f));
    }
    bitmap = bitmap & *(uint64_t *)(old + 0x38);
    if (bitmap == 0) goto next_word;
    do {
        bit = (bitmap & 0xaaaaaaaaaaaaaaaa) >> 1 | (bitmap & 0x5555555555555555) << 1;
        bit = (bit & 0xcccccccccccccccc) >> 2 | (bit & 0x3333333333333333) << 2;
        bit = (bit & 0xf0f0f0f0f0f0f0f0) >> 4 | (bit & 0xf0f0f0f0f0f0f0f) << 4;
        bit = (bit & 0xff00ff00ff00ff00) >> 8 | (bit & 0xff00ff00ff00ff) << 8;
        bit = (bit & 0xffff0000ffff0000) >> 0x10 | (bit & 0xffff0000ffff) << 0x10;
        bit = bit >> 0x20 | bit << 0x20;
        bitmap = bitmap - 1 & bitmap;
        while (true) {
            entry = *(uint32_t *)(*(long *)(old + 0x30) +
                                  (LZCOUNT(bit) | word << 6) * 4);
            FUN_001a84f4(stk, *(uint64_t *)(new_set + 0x28));
            FUN_0022995c(entry);
            probe = FUN_001a8564();
            cap_mask = -1ULL << ((uint64_t)*(uint8_t *)(new_set + 0x20) & 0x3f);
            probe = probe & (cap_mask ^ 0xffffffffffffffff);
            probe_word = probe >> 6;
            idx = -1ULL << (probe & 0x3f) &
                  (*(uint64_t *)(new_set + 0x38 + probe_word * 8) ^ 0xffffffffffffffff);
            if (idx == 0) {
                wrapped = false;
                num_words = 0x3f - cap_mask >> 6;
                do {
                    probe = probe_word + 1;
                    if ((probe == num_words) && (wrapped)) {
                        SoftwareBreakpoint(1, 0x49b390);   /* table full */
                    }
                    probe_word = 0;
                    if (probe != num_words) {
                        probe_word = probe;
                    }
                    wrapped = (bool)(probe == num_words | wrapped);
                    probe = *(uint64_t *)(new_set + 0x38 + probe_word * 8);
                } while (probe == 0xffffffffffffffff);
                probe = ~probe;
                idx = (probe & 0xaaaaaaaaaaaaaaaa) >> 1 | (probe & 0x5555555555555555) << 1;
                idx = (idx & 0xcccccccccccccccc) >> 2 | (idx & 0x3333333333333333) << 2;
                idx = (idx & 0xf0f0f0f0f0f0f0f0) >> 4 | (idx & 0xf0f0f0f0f0f0f0f) << 4;
                idx = (idx & 0xff00ff00ff00ff00) >> 8 | (idx & 0xff00ff00ff00ff) << 8;
                idx = (idx & 0xffff0000ffff0000) >> 0x10 | (idx & 0xffff0000ffff) << 0x10;
                idx = LZCOUNT(idx >> 0x20 | idx << 0x20) | probe_word << 6;
            } else {
                idx = (idx & 0xaaaaaaaaaaaaaaaa) >> 1 | (idx & 0x5555555555555555) << 1;
                idx = (idx & 0xcccccccccccccccc) >> 2 | (idx & 0x3333333333333333) << 2;
                idx = (idx & 0xf0f0f0f0f0f0f0f0) >> 4 | (idx & 0xf0f0f0f0f0f0f0f) << 4;
                idx = (idx & 0xff00ff00ff00ff00) >> 8 | (idx & 0xff00ff00ff00ff) << 8;
                idx = (idx & 0xffff0000ffff0000) >> 0x10 | (idx & 0xffff0000ffff) << 0x10;
                idx = LZCOUNT(idx >> 0x20 | idx << 0x20) | probe & 0x7fffffffffffffc0;
            }
            probe_word = idx >> 3 & 0x1ffffffffffffff8;
            *(uint64_t *)(new_set + 0x38 + probe_word) =
                1ULL << (idx & 0x3f) | *(uint64_t *)(new_set + 0x38 + probe_word);
            *(uint32_t *)(*(long *)(new_set + 0x30) + idx * 4) = entry;
            *(long *)(new_set + 0x10) = *(long *)(new_set + 0x10) + 1;
            if (bitmap != 0) break;
next_word:
            do {
                w2 = word + 1;
                if (SCARRY8(word, 1)) {
                    SoftwareBreakpoint(1, 0x49b38c);
                }
                if ((long)(cap_mask + 0x3f >> 6) <= w2) {
                    FUN_0036b118(old);
                    *(uint64_t *)0 = new_set;
                    return;
                }
                bitmap = ((uint64_t *)(old + 0x38))[w2];
                word = word + 1;
            } while (bitmap == 0);
            bit = (bitmap & 0xaaaaaaaaaaaaaaaa) >> 1 | (bitmap & 0x5555555555555555) << 1;
            bit = (bit & 0xcccccccccccccccc) >> 2 | (bit & 0x3333333333333333) << 2;
            bit = (bit & 0xf0f0f0f0f0f0f0f0) >> 4 | (bit & 0xf0f0f0f0f0f0f0f) << 4;
            bit = (bit & 0xff00ff00ff00ff00) >> 8 | (bit & 0xff00ff00ff00ff) << 8;
            bit = (bit & 0xffff0000ffff0000) >> 0x10 | (bit & 0xffff0000ffff) << 0x10;
            bit = bit >> 0x20 | bit << 0x20;
            bitmap = bitmap - 1 & bitmap;
            word = w2;
        }
    } while (true);
}

/* FUN_0049b390 @ 0x0049b390
 * Ghidra: void FUN_0049b390(long param_1)
 * Grow the 16-byte key/value open-addressing map under x20 to at least
 * param_1 slots and rehash every live pair. Pair array at +0x30 (0x10 stride),
 * occupancy bitmap at +0x38. Hash via FUN_001b9084 (+ thunk_FUN_0036b270 to
 * retain the value before the feed). Aborts at SoftwareBreakpoint
 * 0x49b580/5b4/5b8 on overflow / table-full. Confidence: medium. */
void FUN_0049b390(long param_1)
{
    long   old_len;
    long   new_set;
    uint64_t bitmap;
    uint64_t bit;
    uint64_t idx;
    uint64_t probe;
    uint64_t cap_mask;
    long   word;
    long   old;
    uint64_t num_words;
    bool   wrapped;
    uint64_t probe_word;
    uint64_t key, value;
    long   w2;
    uint8_t stk[72];

    old = *(long *)0;
    old_len = *(long *)(old + 0x18);
    if (*(long *)(old + 0x18) <= param_1) {
        old_len = param_1;
    }
    FUN_00002534((void*)0x657728, (void*)0x4f2238);
    new_set = FUN_0025a840(old, old_len, 0,
                           FUN_00002534((void*)0x657728, (void*)0x4f2238));
    if (*(long *)(old + 0x10) == 0) {
        FUN_0036b118(old);
        *(uint64_t *)0 = new_set;
        return;
    }
    word = 0;
    cap_mask = 1ULL << ((uint64_t)*(uint8_t *)(old + 0x20) & 0x3f);
    bitmap = 0xffffffffffffffff;
    if ((*(uint8_t *)(old + 0x20) & 0x3f) < 6) {
        bitmap = ~(-1ULL << (cap_mask & 0x3f));
    }
    bitmap = bitmap & *(uint64_t *)(old + 0x38);
    if (bitmap == 0) goto next_word;
    do {
        bit = (bitmap & 0xaaaaaaaaaaaaaaaa) >> 1 | (bitmap & 0x5555555555555555) << 1;
        bit = (bit & 0xcccccccccccccccc) >> 2 | (bit & 0x3333333333333333) << 2;
        bit = (bit & 0xf0f0f0f0f0f0f0f0) >> 4 | (bit & 0xf0f0f0f0f0f0f0f) << 4;
        bit = (bit & 0xff00ff00ff00ff00) >> 8 | (bit & 0xff00ff00ff00ff) << 8;
        bit = (bit & 0xffff0000ffff0000) >> 0x10 | (bit & 0xffff0000ffff) << 0x10;
        bit = bit >> 0x20 | bit << 0x20;
        bitmap = bitmap - 1 & bitmap;
        while (true) {
            key = *(uint64_t *)(*(long *)(old + 0x30) +
                                (LZCOUNT(bit) | word << 6) * 0x10);
            value = *(uint64_t *)(*(long *)(old + 0x30) +
                                  (LZCOUNT(bit) | word << 6) * 0x10 + 8);
            FUN_001a84f4(stk, *(uint64_t *)(new_set + 0x28));
            thunk_FUN_0036b270(value);
            FUN_001b9084(stk, key, value);
            probe = FUN_001a8564();
            cap_mask = -1ULL << ((uint64_t)*(uint8_t *)(new_set + 0x20) & 0x3f);
            probe = probe & (cap_mask ^ 0xffffffffffffffff);
            probe_word = probe >> 6;
            idx = -1ULL << (probe & 0x3f) &
                  (*(uint64_t *)(new_set + 0x38 + probe_word * 8) ^ 0xffffffffffffffff);
            if (idx == 0) {
                wrapped = false;
                num_words = 0x3f - cap_mask >> 6;
                do {
                    probe = probe_word + 1;
                    if ((probe == num_words) && (wrapped)) {
                        SoftwareBreakpoint(1, 0x49b5b8);   /* table full */
                    }
                    probe_word = 0;
                    if (probe != num_words) {
                        probe_word = probe;
                    }
                    wrapped = (bool)(probe == num_words | wrapped);
                    probe = *(uint64_t *)(new_set + 0x38 + probe_word * 8);
                } while (probe == 0xffffffffffffffff);
                probe = ~probe;
                idx = (probe & 0xaaaaaaaaaaaaaaaa) >> 1 | (probe & 0x5555555555555555) << 1;
                idx = (idx & 0xcccccccccccccccc) >> 2 | (idx & 0x3333333333333333) << 2;
                idx = (idx & 0xf0f0f0f0f0f0f0f0) >> 4 | (idx & 0xf0f0f0f0f0f0f0f) << 4;
                idx = (idx & 0xff00ff00ff00ff00) >> 8 | (idx & 0xff00ff00ff00ff) << 8;
                idx = (idx & 0xffff0000ffff0000) >> 0x10 | (idx & 0xffff0000ffff) << 0x10;
                idx = LZCOUNT(idx >> 0x20 | idx << 0x20) | probe_word << 6;
            } else {
                idx = (idx & 0xaaaaaaaaaaaaaaaa) >> 1 | (idx & 0x5555555555555555) << 1;
                idx = (idx & 0xcccccccccccccccc) >> 2 | (idx & 0x3333333333333333) << 2;
                idx = (idx & 0xf0f0f0f0f0f0f0f0) >> 4 | (idx & 0xf0f0f0f0f0f0f0f) << 4;
                idx = (idx & 0xff00ff00ff00ff00) >> 8 | (idx & 0xff00ff00ff00ff) << 8;
                idx = (idx & 0xffff0000ffff0000) >> 0x10 | (idx & 0xffff0000ffff) << 0x10;
                idx = LZCOUNT(idx >> 0x20 | idx << 0x20) | probe & 0x7fffffffffffffc0;
            }
            probe_word = idx >> 3 & 0x1ffffffffffffff8;
            *(uint64_t *)(new_set + 0x38 + probe_word) =
                1ULL << (idx & 0x3f) | *(uint64_t *)(new_set + 0x38 + probe_word);
            key = *(uint64_t *)(*(long *)(new_set + 0x30) + idx * 0x10);
            *(uint64_t *)(*(long *)(new_set + 0x30) + idx * 0x10) = key;
            (void)key;
            *(uint64_t *)(*(long *)(new_set + 0x30) + idx * 0x10 + 8) = value;
            *(long *)(new_set + 0x10) = *(long *)(new_set + 0x10) + 1;
            if (bitmap != 0) break;
next_word:
            do {
                w2 = word + 1;
                if (SCARRY8(word, 1)) {
                    SoftwareBreakpoint(1, 0x49b5b4);
                }
                if ((long)(cap_mask + 0x3f >> 6) <= w2) {
                    FUN_0036b118(old);
                    *(uint64_t *)0 = new_set;
                    return;
                }
                bitmap = ((uint64_t *)(old + 0x38))[w2];
                word = word + 1;
            } while (bitmap == 0);
            bit = (bitmap & 0xaaaaaaaaaaaaaaaa) >> 1 | (bitmap & 0x5555555555555555) << 1;
            bit = (bit & 0xcccccccccccccccc) >> 2 | (bit & 0x3333333333333333) << 2;
            bit = (bit & 0xf0f0f0f0f0f0f0f0) >> 4 | (bit & 0xf0f0f0f0f0f0f0f) << 4;
            bit = (bit & 0xff00ff00ff00ff00) >> 8 | (bit & 0xff00ff00ff00ff) << 8;
            bit = (bit & 0xffff0000ffff0000) >> 0x10 | (bit & 0xffff0000ffff) << 0x10;
            bit = bit >> 0x20 | bit << 0x20;
            bitmap = bitmap - 1 & bitmap;
            word = w2;
        }
    } while (true);
}
