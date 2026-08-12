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
extern unsigned long FUN_00376820();                 /* runtime lazy init (returns ptr) */
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
extern unsigned long FUN_0049860c();                 /* object init (returns count) */
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
extern unsigned long FUN_0049a468();                 /* vector ensure writable (returns ptr) */
extern unsigned long FUN_0049a4b8();                 /* vector ensure writable (returns ptr) */

/* 0x004axxxx collection / runtime helpers above this slice. */
extern void         FUN_004a2754();                  /* set slot */
extern void         FUN_004a3550();                  /* vector copy-in */
extern void         FUN_004a4b14();                  /* metadata emit */
extern void         FUN_004aaa88();                  /* dispatch */
extern cl4_pair_t   FUN_004aabb8();                  /* metadata build (returns pair) */
extern void         FUN_004aac88();                  /* big dispatch (12-16 words) */
extern unsigned long FUN_004aadb8();                 /* metadata context (returns ctx) */
extern void         FUN_004aae88();                  /* dispatch tail */
extern cl4_pair_t   FUN_004ab10c();                  /* metadata init (returns pair) */
extern void         FUN_004ab13c();                  /* metadata pre */
extern void         FUN_004ab150();                  /* metadata init */
extern unsigned long FUN_004ab2dc();                 /* metadata slot ptr */
extern void         FUN_004ab600();                  /* metadata step */
extern void         FUN_004ab67c();                  /* big dispatch (6-8 words) */
extern unsigned long FUN_004ab868();                 /* metadata tail (returns ptr) */
extern void         FUN_004ab954();                  /* metadata release */
extern unsigned long FUN_004ab9a4();                 /* metadata alloc (returns ptr) */
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
extern void         FUN_004acc70();                  /* dispatch tail */
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
void FUN_0049b99c(long param_1);
void FUN_0049bbf0(long param_1);
void FUN_0049be44(long param_1);
void FUN_0049c0a8(uint64_t param_1, uint64_t param_2, long param_3);

uint64_t FUN_0049cc64(void);
uint64_t FUN_0049cd98(void);
void FUN_0049d320();
void FUN_0049d538();
void FUN_0049d690();
void FUN_0049c0a8(uint64_t param_1, uint64_t param_2, long param_3);

/* Forward declarations for in-slice functions referenced before definition. */
void FUN_0049c904();
void FUN_0049cb88(uint64_t param_1, uint64_t param_2, uint8_t param_3);
void FUN_0049ce9c();
void FUN_0049cd00();
uint64_t FUN_0049c714(uint64_t param_1);

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
            FUN_0049b99c(*(uint64_t *)(*(uint64_t *)0 + 0x10) + 1);
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
            FUN_0049bbf0(*(uint64_t *)(*(uint64_t *)0 + 0x10) + 1);
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
            FUN_0049be44(*(uint64_t *)(*(uint64_t *)0 + 0x10) + 1);
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

/* FUN_0049b5b8 @ 0x0049b5b8
 * Ghidra: void FUN_0049b5b8(void)
 * Compact-grow the 8-byte-word set under x20: allocate a larger bucket array
 * (FUN_0025b994), memmove the old bitmap into it, then copy every live value
 * from the old value array into the new array at the same slot index (no
 * rehash — the bitmap is moved verbatim). The old set is released. Aborts at
 * SoftwareBreakpoint 0x49b6fc on overflow. Confidence: medium. */
void FUN_0049b5b8(void)
{
    long   old;
    long   new_set;
    uint64_t word_count;
    uint64_t bitmap;
    uint64_t shift;
    long   w;
    long   w2;
    uint64_t bit;
    uint64_t slot;

    FUN_00002534((void*)0x657d70, (void*)0x5a4b38);
    old = *(long *)0;
    new_set = FUN_0025b994(old);
    if (*(long *)(old + 0x10) != 0) {
        word_count = (1ULL << ((uint64_t)*(uint8_t *)(new_set + 0x20) & 0x3f)) + 0x3f >> 6;
        if (new_set != old || (old + 0x38) + word_count * 8 <= (new_set + 0x38)) {
            FUN_00117d14(new_set + 0x38, old + 0x38, word_count << 3);
        }
        w = 0;
        *(uint64_t *)(new_set + 0x10) = *(uint64_t *)(old + 0x10);
        shift = 1ULL << ((uint64_t)*(uint8_t *)(old + 0x20) & 0x3f);
        bitmap = 0xffffffffffffffff;
        if ((*(uint8_t *)(old + 0x20) & 0x3f) < 6) {
            bitmap = ~(-1ULL << (shift & 0x3f));
        }
        bitmap = bitmap & *(uint64_t *)(old + 0x38);
        do {
            w2 = w;
            if (bitmap == 0) {
                do {
                    w2 = w + 1;
                    if (SCARRY8(w, 1)) {
                        SoftwareBreakpoint(1, 0x49b6fc);
                    }
                    if ((long)(shift + 0x3f >> 6) <= w2) goto done;
                    bitmap = *(uint64_t *)((old + 0x38) + w2 * 8);
                    w = w + 1;
                } while (bitmap == 0);
                bit = (bitmap & 0xaaaaaaaaaaaaaaaa) >> 1 | (bitmap & 0x5555555555555555) << 1;
                bit = (bit & 0xcccccccccccccccc) >> 2 | (bit & 0x3333333333333333) << 2;
                bit = (bit & 0xf0f0f0f0f0f0f0f0) >> 4 | (bit & 0xf0f0f0f0f0f0f0f) << 4;
                bit = (bit & 0xff00ff00ff00ff00) >> 8 | (bit & 0xff00ff00ff00ff) << 8;
                bit = (bit & 0xffff0000ffff0000) >> 0x10 | (bit & 0xffff0000ffff) << 0x10;
                bitmap = bitmap - 1 & bitmap;
                bit = LZCOUNT(bit >> 0x20 | bit << 0x20) | w2 * 0x40;
            } else {
                bit = (bitmap & 0xaaaaaaaaaaaaaaaa) >> 1 | (bitmap & 0x5555555555555555) << 1;
                bit = (bit & 0xcccccccccccccccc) >> 2 | (bit & 0x3333333333333333) << 2;
                bit = (bit & 0xf0f0f0f0f0f0f0f0) >> 4 | (bit & 0xf0f0f0f0f0f0f0f) << 4;
                bit = (bit & 0xff00ff00ff00ff00) >> 8 | (bit & 0xff00ff00ff00ff) << 8;
                bit = (bit & 0xffff0000ffff0000) >> 0x10 | (bit & 0xffff0000ffff) << 0x10;
                bitmap = bitmap - 1 & bitmap;
                bit = LZCOUNT(bit >> 0x20 | bit << 0x20) | w << 6;
            }
            slot = bit;
            *(uint64_t *)(*(long *)(new_set + 0x30) + slot * 8) =
                *(uint64_t *)(*(long *)(old + 0x30) + slot * 8);
        } while (true);
    }
done:
    FUN_0036b118(old);
    *(uint64_t *)0 = new_set;
}

/* FUN_0049b6fc @ 0x0049b6fc
 * Ghidra: void FUN_0049b6fc(void)
 * Compact-grow the 32-bit-int set under x20: larger bucket array, memmove the
 * bitmap, copy every live int to the same slot index. Old set released.
 * Aborts at SoftwareBreakpoint 0x49b840 on overflow. Confidence: medium. */
void FUN_0049b6fc(void)
{
    long   old;
    long   new_set;
    uint64_t word_count;
    uint64_t bitmap;
    uint64_t shift;
    long   w;
    long   w2;
    uint64_t bit;
    uint64_t slot;

    FUN_00002534((void*)0x657e00, (void*)0x5a4c00);
    old = *(long *)0;
    new_set = FUN_0025b994(old);
    if (*(long *)(old + 0x10) != 0) {
        word_count = (1ULL << ((uint64_t)*(uint8_t *)(new_set + 0x20) & 0x3f)) + 0x3f >> 6;
        if (new_set != old || (old + 0x38) + word_count * 8 <= (new_set + 0x38)) {
            FUN_00117d14(new_set + 0x38, old + 0x38, word_count << 3);
        }
        w = 0;
        *(uint64_t *)(new_set + 0x10) = *(uint64_t *)(old + 0x10);
        shift = 1ULL << ((uint64_t)*(uint8_t *)(old + 0x20) & 0x3f);
        bitmap = 0xffffffffffffffff;
        if ((*(uint8_t *)(old + 0x20) & 0x3f) < 6) {
            bitmap = ~(-1ULL << (shift & 0x3f));
        }
        bitmap = bitmap & *(uint64_t *)(old + 0x38);
        do {
            w2 = w;
            if (bitmap == 0) {
                do {
                    w2 = w + 1;
                    if (SCARRY8(w, 1)) {
                        SoftwareBreakpoint(1, 0x49b840);
                    }
                    if ((long)(shift + 0x3f >> 6) <= w2) goto done;
                    bitmap = *(uint64_t *)((old + 0x38) + w2 * 8);
                    w = w + 1;
                } while (bitmap == 0);
                bit = (bitmap & 0xaaaaaaaaaaaaaaaa) >> 1 | (bitmap & 0x5555555555555555) << 1;
                bit = (bit & 0xcccccccccccccccc) >> 2 | (bit & 0x3333333333333333) << 2;
                bit = (bit & 0xf0f0f0f0f0f0f0f0) >> 4 | (bit & 0xf0f0f0f0f0f0f0f) << 4;
                bit = (bit & 0xff00ff00ff00ff00) >> 8 | (bit & 0xff00ff00ff00ff) << 8;
                bit = (bit & 0xffff0000ffff0000) >> 0x10 | (bit & 0xffff0000ffff) << 0x10;
                bitmap = bitmap - 1 & bitmap;
                bit = LZCOUNT(bit >> 0x20 | bit << 0x20) | w2 * 0x40;
            } else {
                bit = (bitmap & 0xaaaaaaaaaaaaaaaa) >> 1 | (bitmap & 0x5555555555555555) << 1;
                bit = (bit & 0xcccccccccccccccc) >> 2 | (bit & 0x3333333333333333) << 2;
                bit = (bit & 0xf0f0f0f0f0f0f0f0) >> 4 | (bit & 0xf0f0f0f0f0f0f0f) << 4;
                bit = (bit & 0xff00ff00ff00ff00) >> 8 | (bit & 0xff00ff00ff00ff) << 8;
                bit = (bit & 0xffff0000ffff0000) >> 0x10 | (bit & 0xffff0000ffff) << 0x10;
                bitmap = bitmap - 1 & bitmap;
                bit = LZCOUNT(bit >> 0x20 | bit << 0x20) | w << 6;
            }
            slot = bit;
            *(uint32_t *)(*(long *)(new_set + 0x30) + slot * 4) =
                *(uint32_t *)(*(long *)(old + 0x30) + slot * 4);
        } while (true);
    }
done:
    FUN_0036b118(old);
    *(uint64_t *)0 = new_set;
}

/* FUN_0049b840 @ 0x0049b840
 * Ghidra: void FUN_0049b840(void)
 * Compact-grow the 16-byte key/value map under x20: larger bucket array,
 * memmove bitmap, copy each live pair to the same slot. Old set released.
 * Aborts at SoftwareBreakpoint 0x49b99c on overflow. Confidence: medium. */
void FUN_0049b840(void)
{
    long   old;
    long   new_set;
    uint64_t word_count;
    uint64_t bitmap;
    uint64_t shift;
    long   w;
    long   w2;
    uint64_t bit;
    uint64_t slot;
    uint64_t value;

    FUN_00002534((void*)0x657728, (void*)0x4f2238);
    old = *(long *)0;
    new_set = FUN_0025b994(old);
    if (*(long *)(old + 0x10) != 0) {
        word_count = (1ULL << ((uint64_t)*(uint8_t *)(new_set + 0x20) & 0x3f)) + 0x3f >> 6;
        if (new_set != old || (old + 0x38) + word_count * 8 <= (new_set + 0x38)) {
            FUN_00117d14(new_set + 0x38, old + 0x38, word_count << 3);
        }
        w = 0;
        *(uint64_t *)(new_set + 0x10) = *(uint64_t *)(old + 0x10);
        shift = 1ULL << ((uint64_t)*(uint8_t *)(old + 0x20) & 0x3f);
        bitmap = 0xffffffffffffffff;
        if ((*(uint8_t *)(old + 0x20) & 0x3f) < 6) {
            bitmap = ~(-1ULL << (shift & 0x3f));
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
                bit = LZCOUNT(bit) | w << 6;
                value = *(uint64_t *)(*(long *)(old + 0x30) + bit * 0x10 + 8);
                *(uint64_t *)(*(long *)(new_set + 0x30) + bit * 0x10) =
                    *(uint64_t *)(*(long *)(old + 0x30) + bit * 0x10);
                *(uint64_t *)(*(long *)(new_set + 0x30) + bit * 0x10 + 8) = value;
                thunk_FUN_0036b270();
                if (bitmap != 0) break;
next_word:
                do {
                    w2 = w + 1;
                    if (SCARRY8(w, 1)) {
                        SoftwareBreakpoint(1, 0x49b99c);
                    }
                    if ((long)(shift + 0x3f >> 6) <= w2) goto done;
                    bitmap = *(uint64_t *)((old + 0x38) + w2 * 8);
                    w = w + 1;
                } while (bitmap == 0);
                bit = (bitmap & 0xaaaaaaaaaaaaaaaa) >> 1 | (bitmap & 0x5555555555555555) << 1;
                bit = (bit & 0xcccccccccccccccc) >> 2 | (bit & 0x3333333333333333) << 2;
                bit = (bit & 0xf0f0f0f0f0f0f0f0) >> 4 | (bit & 0xf0f0f0f0f0f0f0f) << 4;
                bit = (bit & 0xff00ff00ff00ff00) >> 8 | (bit & 0xff00ff00ff00ff) << 8;
                bit = (bit & 0xffff0000ffff0000) >> 0x10 | (bit & 0xffff0000ffff) << 0x10;
                bit = bit >> 0x20 | bit << 0x20;
                bitmap = bitmap - 1 & bitmap;
                w = w2;
            }
        } while (true);
    }
done:
    FUN_0036b118(old);
    *(uint64_t *)0 = new_set;
}

/* FUN_0049b99c @ 0x0049b99c
 * Ghidra: void FUN_0049b99c(long param_1)
 * In-place growing rehash of the 8-byte-word set under x20. Grows to at least
 * param_1 slots via FUN_0025a840(flag=1); rehashes every live entry into the
 * new array (hash thunk_FUN_002298d4 of key>>0xe), then CLEARS the old set's
 * occupancy bitmap (FUN_000b02c0 or a direct fill) and zeroes its length,
 * effectively handing the entries to the new array. Aborts at SoftwareBreakpoint
 * 0x49bbbc/bbec/bbf0. Confidence: medium. */
void FUN_0049b99c(long param_1)
{
    long   old;
    long   new_set;
    long   old_len;
    uint64_t bitmap;
    uint64_t bit;
    uint64_t idx;
    uint64_t probe;
    uint64_t cap_mask;
    long   word;
    uint64_t num_words;
    bool   wrapped;
    uint64_t probe_word;
    uint64_t entry;
    long   w2;
    uint8_t stk[72];

    old = *(long *)0;
    old_len = *(long *)(old + 0x18);
    if (*(long *)(old + 0x18) <= param_1) {
        old_len = param_1;
    }
    FUN_00002534((void*)0x657d70, (void*)0x5a4b38);
    new_set = FUN_0025a840(old, old_len, 1, FUN_00002534((void*)0x657d70, (void*)0x5a4b38));
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
                wrapped = false;
                num_words = 0x3f - cap_mask >> 6;
                do {
                    probe = probe_word + 1;
                    if ((probe == num_words) && (wrapped)) {
                        SoftwareBreakpoint(1, 0x49bbf0);
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
                    SoftwareBreakpoint(1, 0x49bbec);
                }
                if ((long)(cap_mask + 0x3f >> 6) <= w2) {
                    bitmap = 1ULL << ((uint64_t)*(uint8_t *)(old + 0x20) & 0x3f);
                    if ((*(uint8_t *)(old + 0x20) & 0x3f) < 6) {
                        *(uint64_t *)(old + 0x38) = -1ULL << (bitmap & 0x3f);
                    } else {
                        FUN_000b02c0(0, bitmap + 0x3f >> 6, (void *)(old + 0x38));
                    }
                    *(uint64_t *)(old + 0x10) = 0;
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

/* FUN_0049bbf0 @ 0x0049bbf0
 * Ghidra: void FUN_0049bbf0(long param_1)
 * In-place growing rehash of the 32-bit-int set under x20 (analogue of
 * 0049b99c for int values; hash via FUN_0022995c). Old bitmap cleared.
 * Aborts at SoftwareBreakpoint 0x49be10/be40/be44. Confidence: medium. */
void FUN_0049bbf0(long param_1)
{
    long   old;
    long   new_set;
    long   old_len;
    uint64_t bitmap;
    uint64_t bit;
    uint64_t idx;
    uint64_t probe;
    uint64_t cap_mask;
    long   word;
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
    new_set = FUN_0025a840(old, old_len, 1, FUN_00002534((void*)0x657e00, (void*)0x5a4c00));
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
                        SoftwareBreakpoint(1, 0x49be44);
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
                    SoftwareBreakpoint(1, 0x49be40);
                }
                if ((long)(cap_mask + 0x3f >> 6) <= w2) {
                    bitmap = 1ULL << ((uint64_t)*(uint8_t *)(old + 0x20) & 0x3f);
                    if ((*(uint8_t *)(old + 0x20) & 0x3f) < 6) {
                        *(uint64_t *)(old + 0x38) = -1ULL << (bitmap & 0x3f);
                    } else {
                        FUN_000b02c0(0, bitmap + 0x3f >> 6, (void *)(old + 0x38));
                    }
                    *(uint64_t *)(old + 0x10) = 0;
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

/* FUN_0049be44 @ 0x0049be44
 * Ghidra: void FUN_0049be44(long param_1)
 * In-place growing rehash of the 16-byte key/value map under x20 (analogue
 * of 0049b99c for pairs; hash via FUN_001b9084). Old bitmap cleared.
 * Aborts at SoftwareBreakpoint 0x49c074/c0a4/c0a8. Confidence: medium. */
void FUN_0049be44(long param_1)
{
    long   old;
    long   new_set;
    long   old_len;
    uint64_t bitmap;
    uint64_t bit;
    uint64_t idx;
    uint64_t probe;
    uint64_t cap_mask;
    long   word;
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
    new_set = FUN_0025a840(old, old_len, 1, FUN_00002534((void*)0x657728, (void*)0x4f2238));
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
                        SoftwareBreakpoint(1, 0x49c0a8);
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
            *(uint64_t *)(*(long *)(new_set + 0x30) + idx * 0x10) = key;
            *(uint64_t *)(*(long *)(new_set + 0x30) + idx * 0x10 + 8) = value;
            *(long *)(new_set + 0x10) = *(long *)(new_set + 0x10) + 1;
            if (bitmap != 0) break;
next_word:
            do {
                w2 = word + 1;
                if (SCARRY8(word, 1)) {
                    SoftwareBreakpoint(1, 0x49c0a4);
                }
                if ((long)(cap_mask + 0x3f >> 6) <= w2) {
                    bitmap = 1ULL << ((uint64_t)*(uint8_t *)(old + 0x20) & 0x3f);
                    if ((*(uint8_t *)(old + 0x20) & 0x3f) < 6) {
                        *(uint64_t *)(old + 0x38) = -1ULL << (bitmap & 0x3f);
                    } else {
                        FUN_000b02c0(0, bitmap + 0x3f >> 6, (void *)(old + 0x38));
                    }
                    *(uint64_t *)(old + 0x10) = 0;
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

/* FUN_0049c0a8 @ 0x0049c0a8
 * Ghidra: void FUN_0049c0a8(undefined4 param_1, ulong param_2, long param_3)
 * Mark a slot of the 32-bit-int set: set bit param_2 in the occupancy bitmap
 * at param_3+0x38+(param_2>>6)*8 and store the int at +0x30. Increments the
 * length; aborts at SoftwareBreakpoint 0x49c0e4 on length overflow.
 * Confidence: medium. */
void FUN_0049c0a8(uint64_t param_1, uint64_t param_2, long param_3)
{
    long   bitmap_word;

    bitmap_word = param_3 + (param_2 >> 6) * 8;
    *(uint64_t *)(bitmap_word + 0x38) =
        *(uint64_t *)(bitmap_word + 0x38) | 1ULL << (param_2 & 0x3f);
    *(uint32_t *)(*(long *)(param_3 + 0x30) + param_2 * 4) = (uint32_t)param_1;
    if (!SCARRY8(*(long *)(param_3 + 0x10), 1)) {
        *(long *)(param_3 + 0x10) = *(long *)(param_3 + 0x10) + 1;
        return;
    }
    SoftwareBreakpoint(1, 0x49c0e4);
}

/* FUN_0049c0e4 @ 0x0049c0e4
 * Ghidra: undefined1 [16] FUN_0049c0e4(undefined8 param_1, undefined8 param_2)
 * Dictionary insert-or-return: hash param_2 with FUN_00499f0c to get a key
 * index; if the object is shared (bit 1 of the pair flag set), copy-on-write
 * grow via FUN_00258c60 and re-derive the index; otherwise store param_1 at
 * the object's slot (+0x38 array) and return the previous value. Returns a
 * 16-byte pair {previous, flag} where bit 0 of the hi byte indicates whether
 * the caller must release the old value. Aborts at SoftwareBreakpoint
 * 0x49c1f0 on length overflow. Confidence: medium. */
cl4_pair_t FUN_0049c0e4(uint64_t param_1, uint64_t param_2)
{
    bool      released;
    uint64_t  value;
    cl4_pair_t meta;
    long      obj;
    long      hash_state;
    uint64_t  key_index;
    long      slot_off;
    cl4_pair_t out;
    cl4_pair_t meta2;

    value = FUN_003a261c(*(uint64_t *)0);
    obj = *(long *)0;
    meta = FUN_00499f0c(param_2);
    key_index = meta.lo;
    hash_state = *(long *)(obj + 0x10);
    if (SCARRY8(hash_state, (uint64_t)~meta.hi & 1)) {
        SoftwareBreakpoint(1, 0x49c1f0);
    }
    value = FUN_00002534((void*)0x657dd8, (void*)0x5a4bc8);
    hash_state = FUN_00258c60(value, hash_state + ((uint64_t)~meta.hi & 1), value);
    if ((hash_state & 1) != 0) {
        meta2 = FUN_00499f0c(param_2);
        key_index = meta2.lo;
        if ((meta.hi & 1) != (meta2.hi & 1)) {
            FUN_002591b4(0x686a38);      /* metadata changed -> panic */
        }
    }
    released = (meta.hi & 2) == 0;
    if (released) {
        FUN_00499fcc(key_index, param_2, param_1, obj);
        value = 0;
    } else {
        value = *(uint64_t *)(*(long *)(obj + 0x38) + key_index * 8);
        *(uint64_t *)(*(long *)(obj + 0x38) + key_index * 8) = param_1;
    }
    *(long *)0 = obj;
    out.lo = value;
    out.hi = (uint64_t)(released ? 1 : 0) | (meta.hi & 0xff00);
    return out;
}

/* FUN_0049c200 @ 0x0049c200
 * Ghidra: void FUN_0049c200(long param_1, long param_2)
 * Remove a range [param_1, param_2) of 0x48-byte elements from the vector
 * under x20. Validates indices (param_1 >= 0, param_2 <= length, no borrow),
 * grows capacity via FUN_0049a348 (with carrier FUN_00498cc8), memmoves the
 * tail down with FUN_0035bc70(0x688ea0), and decrements the length by the
 * removed count. Aborts at SoftwareBreakpoint 0x49c288..49c358 on any index
 * overflow. Confidence: medium. */
void FUN_0049c200(long param_1, long param_2)
{
    long   len;
    long   removed;
    long   neg_removed;
    long   obj;
    long   tail_src;

    if (param_1 < 0) {
        SoftwareBreakpoint(1, 0x49c288);
    }
    len = *(long *)(*(uint64_t *)0 + 0x10);
    if (len < param_2) {
        SoftwareBreakpoint(1, 0x49c28c);
    }
    if (SBORROW8(param_2, param_1)) {
        SoftwareBreakpoint(1, 0x49c290);
    }
    removed = param_2 - param_1;
    neg_removed = -removed;
    if (SBORROW8(0, removed)) {
        SoftwareBreakpoint(1, 0x49c294);
    }
    if (SCARRY8(len, neg_removed)) {
        SoftwareBreakpoint(1, 0x49c298);
    }
    FUN_0049a348(len + neg_removed, 1, FUN_00498cc8);
    removed = param_2 - param_1;
    if (SBORROW8(param_2, param_1)) {
        SoftwareBreakpoint(1, 0x49c348);
    }
    if (removed < 0) {
        SoftwareBreakpoint(1, 0x49c34c);
    }
    obj = *(long *)0;
    tail_src = obj + 0x20 + param_1 * 0x48;
    FUN_0035bc70(tail_src, removed, (void*)0x688ea0);
    neg_removed = -removed;
    if (SBORROW8(0, removed)) {
        SoftwareBreakpoint(1, 0x49c350);
    }
    if (neg_removed != 0) {
        if (SBORROW8(*(long *)(obj + 0x10), param_2)) {
            SoftwareBreakpoint(1, 0x49c354);
        }
        FUN_00498500(obj + 0x20 + param_2 * 0x48,
                     *(long *)(obj + 0x10) - param_2, tail_src);
        if (SCARRY8(*(long *)(obj + 0x10), neg_removed)) {
            SoftwareBreakpoint(1, 0x49c358);
        }
        *(long *)(obj + 0x10) = *(long *)(obj + 0x10) + neg_removed;
    }
}

/* FUN_0049c35c @ 0x0049c35c
 * Ghidra: undefined * FUN_0049c35c(undefined8 param_1, undefined8 param_2, long param_3)
 * Build and return a fresh object representation for a vector of lVar5 =
 * *(param_3+0x10) elements: allocate an object of that length via
 * FUN_0049849c, initialize it with FUN_0049860c from the source element
 * descriptors, and run the object-registration chain. On failure, aborts at
 * SoftwareBreakpoint 0x49c4b0/4b4. Returns a pointer to the (possibly empty,
 * &DAT_00657778) object. Confidence: medium. */
uint8_t *FUN_0049c35c(uint64_t param_1, uint64_t param_2, long param_3)
{
    long      count;
    uint8_t  *result;
    uint64_t  ok;
    long      ctx;
    long      stk_58;
    uint64_t  local_70, local_68, local_60;
    uint64_t  slot_0;

    count = *(long *)(param_3 + 0x10);
    if (count == 0) {
        result = (uint8_t *)0x657778;
    } else {
        result = (uint8_t *)FUN_0049849c(count, 0);
        ok = FUN_0049860c(&local_70, result + 0x20, count,
                          param_1, param_2, param_3);
        if (stk_58 == *(long *)(local_60 + 0x10)) {
            slot_0 = 0;
            (void)0;
            thunk_FUN_0036b270(param_2);
            FUN_0036b270(param_3);
            FUN_0036b118(local_60);
            FUN_003a25d4(local_68);
            FUN_004a4b14((void *)&slot_0, (void*)0x657d28, (void*)0x5a4ad8);
        } else {
            FUN_00490b14((void *)&slot_0, stk_58, local_70, local_68, local_60);
            if (slot_0 != 0) {
                SoftwareBreakpoint(1, 0x49c4b4);
            }
            thunk_FUN_0036b270(param_2);
            FUN_0036b270(param_3);
            FUN_0036b118(local_60);
            FUN_003a25d4(local_68);
            FUN_004a4b14((void *)&slot_0, (void*)0x657d28, (void*)0x5a4ad8);
        }
        if (ok != (uint64_t)count) {
            SoftwareBreakpoint(1, 0x49c4b0);
        }
    }
    return result;
}

/* FUN_0049c4b4 @ 0x0049c4b4
 * Ghidra: undefined4 FUN_0049c4b4(ulong param_1)
 * Remove and return the 32-bit element at index param_1 of the int vector
 * under x20. If the object is shared (bit 0 of FUN_003a261c flag), copy it
 * via FUN_0049a4b8; memmove the tail down (FUN_00071fe4) and decrement the
 * length. Aborts at SoftwareBreakpoint 0x49c52c on out-of-range.
 * Confidence: medium. */
uint32_t FUN_0049c4b4(uint64_t param_1)
{
    uint64_t flag;
    long     obj;
    long     count;
    long     slot;
    uint32_t value;

    obj = *(long *)0;
    flag = FUN_003a261c(obj);
    if ((flag & 1) == 0) {
        obj = FUN_0049a4b8(obj);
    }
    if (param_1 < *(uint64_t *)(obj + 0x10)) {
        count = *(uint64_t *)(obj + 0x10) - 1;
        slot = obj + param_1 * 4;
        value = *(uint32_t *)(slot + 0x20);
        FUN_00071fe4(slot + 0x24, count - param_1);
        *(long *)(obj + 0x10) = count;
        *(long *)0 = obj;
        return value;
    }
    SoftwareBreakpoint(1, 0x49c52c);
}

/* FUN_0049c52c @ 0x0049c52c
 * Ghidra: void FUN_0049c52c(undefined8 param_1)
 * Pop the last 0x48-byte element off the vector under x20 and release the
 * head (FUN_00117cc4). If shared, copy first via FUN_0049a468. Aborts at
 * SoftwareBreakpoint 0x49c5a0 when empty. Confidence: medium. */
void FUN_0049c52c(uint64_t param_1)
{
    uint64_t flag;
    long     obj;
    long     count;

    obj = *(long *)0;
    flag = FUN_003a261c(obj);
    if ((flag & 1) == 0) {
        obj = FUN_0049a468(obj);
    }
    count = *(long *)(obj + 0x10);
    if (count != 0) {
        FUN_00117cc4(param_1, obj + count * 0x48 - 0x28, 0x48);
        *(long *)(obj + 0x10) = count - 1;
        *(long *)0 = obj;
        return;
    }
    SoftwareBreakpoint(1, 0x49c5a0);
}

/* FUN_0049c5a0 @ 0x0049c5a0
 * Ghidra: undefined4 FUN_0049c5a0(void)
 * Pop and return the last 32-bit element off the int vector under x20.
 * If shared, copy first via FUN_0049a4b8. Aborts at SoftwareBreakpoint
 * 0x49c5f8 when empty. Confidence: medium. */
uint32_t FUN_0049c5a0(void)
{
    uint32_t value;
    uint64_t flag;
    long     obj;
    long     count;

    obj = *(long *)0;
    flag = FUN_003a261c(obj);
    if ((flag & 1) == 0) {
        obj = FUN_0049a4b8(obj);
    }
    if (*(long *)(obj + 0x10) != 0) {
        count = *(long *)(obj + 0x10) - 1;
        value = *(uint32_t *)(obj + count * 4 + 0x20);
        *(long *)(obj + 0x10) = count;
        *(long *)0 = obj;
        return value;
    }
    SoftwareBreakpoint(1, 0x49c5f8);
}

/* FUN_0049c5f8 @ 0x0049c5f8
 * Ghidra: void FUN_0049c5f8(undefined8 *param_1)
 * Populate a 16-byte out record (*param_1) from the ring buffer / queue under
 * x20. If the queue is empty (byte at x20+0x38 == 1), zero the 16 output
 * words; otherwise copy the head element (0x38 bytes at +0x30 slot), advance
 * the read pointer (+0x20), and copy the 0x48-byte element into the caller's
 * +7 word with FUN_004a3550. Aborts at SoftwareBreakpoint 0x49c700/704 on
 * index or overflow. Confidence: medium. */
void FUN_0049c5f8(uint64_t *param_1)
{
    uint64_t idx;
    long     lk;
    uint64_t read_ptr;
    uint64_t rd;
    long     src;
    uint64_t v1, v2, v3, v4, v5, v6;
    uint8_t  v7;

    if (*(char *)(((long)0) + 0x38) == '\x01') {   /* empty marker at x20+0x38 */
        *(uint64_t *)((long)param_1 + 0x71) = 0;
        *(uint64_t *)((long)param_1 + 0x69) = 0;
        param_1[0xb] = 0;
        param_1[10] = 0;
        param_1[0xd] = 0;
        param_1[0xc] = 0;
        param_1[7] = 0;
        param_1[6] = 0;
        param_1[9] = 0;
        param_1[8] = 0;
        param_1[3] = 0;
        param_1[2] = 0;
        param_1[5] = 0;
        param_1[4] = 0;
        param_1[1] = 0;
        *param_1 = 0;
    } else {
        read_ptr = *(uint64_t *)(((long)0) + 0x20);
        if (read_ptr != *(uint64_t *)(((long)0) + 0x18) >> 1) {
            if ((long)(*(uint64_t *)(((long)0) + 0x18) >> 1) <= (long)read_ptr ||
                (long)read_ptr < *(long *)(((long)0) + 0x10)) {
                SoftwareBreakpoint(1, 0x49c700);
            }
            src = *(long *)(((long)0) + 8) + read_ptr * 0x38;
            v1 = *(uint64_t *)(src + 8);
            v2 = *(uint64_t *)(src + 0x10);
            v3 = *(uint64_t *)(src + 0x18);
            v4 = *(uint64_t *)(src + 0x20);
            v5 = *(uint64_t *)(src + 0x28);
            v6 = *(uint64_t *)(src + 0x30);
            v7 = *(uint8_t *)(src + 0x38);
            *(uint64_t *)(((long)0) + 0x20) = read_ptr + 1;
            lk = *(long *)(((long)0) + 0x28);
            read_ptr = *(uint64_t *)(((long)0) + 0x30);
            rd = *(uint64_t *)(lk + 0x10);
            if (read_ptr != rd) {
                if (read_ptr < rd) {
                    *(uint64_t *)(((long)0) + 0x30) = read_ptr + 1;
                    param_1[1] = v1;
                    *param_1 = v2;
                    param_1[2] = v3;
                    param_1[4] = v4;
                    param_1[3] = v5;
                    param_1[5] = v6;
                    *(uint8_t *)(param_1 + 6) = v7;
                    FUN_004a3550(lk + read_ptr * 0x48 + 0x20, param_1 + 7);
                    thunk_FUN_0036b270(v1);
                    return;
                }
                SoftwareBreakpoint(1, 0x49c704);
            }
        }
        *(uint8_t *)(((long)0) + 0x38) = 1;
        param_1[1] = 0;
        *param_1 = 0;
        param_1[3] = 0;
        param_1[2] = 0;
        param_1[5] = 0;
        param_1[4] = 0;
        param_1[7] = 0;
        param_1[6] = 0;
        param_1[9] = 0;
        param_1[8] = 0;
        param_1[0xb] = 0;
        param_1[10] = 0;
        param_1[0xd] = 0;
        param_1[0xc] = 0;
        *(uint64_t *)((long)param_1 + 0x71) = 0;
        *(uint64_t *)((long)param_1 + 0x69) = 0;
    }
}

/* FUN_0049c704 @ 0x0049c704
 * Ghidra: void FUN_0049c704(undefined8 param_1, undefined8 param_2)
 * Set a slot: forward to FUN_004a2754(param_2, param_1). Confidence: medium. */
void FUN_0049c704(uint64_t param_1, uint64_t param_2)
{
    FUN_004a2754(param_2, param_1);
}

/* FUN_0049c714 @ 0x0049c714
 * Ghidra: undefined8 FUN_0049c714(undefined8 param_1)
 * Return param_1 unchanged after tearing down a metadata/collection object via
 * FUN_0049ce9c. Confidence: medium. */
uint64_t FUN_0049c714(uint64_t param_1)
{
    FUN_0049ce9c();
    return param_1;
}

/* FUN_0049c73c @ 0x0049c73c
 * Ghidra: void FUN_0049c73c(void)
 * Release the collection's owned sub-object at x20+0x28, run the runtime
 * teardown FUN_00355538, and tail-return. Confidence: medium. */
void FUN_0049c73c(void)
{
    FUN_003a25d4(*(uint64_t *)(((long)0) + 0x28));
    FUN_00355538();
    FUN_0036b21c();
}

/* FUN_0049c740 @ 0x0049c740
 * Ghidra: void FUN_0049c740(void)
 * Identical twin of 0049c73c (release x20+0x28, teardown, tail-return).
 * Confidence: medium. */
void FUN_0049c740(void)
{
    FUN_003a25d4(*(uint64_t *)(((long)0) + 0x28));
    FUN_00355538();
    FUN_0036b21c();
}

/* FUN_0049c770 @ 0x0049c770
 * Ghidra: void FUN_0049c770(void)
 * Release the object at x20+0x20, dealloc per-cpu (FUN_000dce50), tail-return.
 * Confidence: medium. */
void FUN_0049c770(void)
{
    FUN_0036b118(*(uint64_t *)(((long)0) + 0x20));
    FUN_000dce50();
    FUN_0036b21c();
}

/* FUN_0049c774 @ 0x0049c774
 * Ghidra: void FUN_0049c774(void)
 * Identical twin of 0049c770 (release x20+0x20, per-cpu dealloc, tail-return).
 * Confidence: medium. */
void FUN_0049c774(void)
{
    FUN_0036b118(*(uint64_t *)(((long)0) + 0x20));
    FUN_000dce50();
    FUN_0036b21c();
}

/* FUN_0049c794 @ 0x0049c794
 * Ghidra: void FUN_0049c794(void)
 * Dispatch through the object's method table: invoke the method pointer at
 * (fn_table+8) on the object slot selected by the byte at (fn_table+0x50),
 * after a pre-dispatch (FUN_003509c8). Tail-return. Confidence: low (heavy
 * register-indirect dispatch). */
void FUN_0049c794(void)
{
    long fn_table;

    FUN_003509c8(*(uint64_t *)(((long)0) + 0x10));
    fn_table = 0;      /* extraout_x16: function-table base (unrecovered) */
    (*(void (**)(long))((long)(*(uint64_t *)(fn_table + 8))))(0);
    FUN_0036b21c();
}

/* FUN_0049c7fc @ 0x0049c7fc
 * Ghidra: void FUN_0049c7fc(void)
 * Forward to the object-table release FUN_00491db4. Confidence: medium. */
void FUN_0049c7fc(void)
{
    FUN_00491db4();
}

/* FUN_0049c800 @ 0x0049c800
 * Ghidra: void FUN_0049c800(void)
 * Identical twin of 0049c7fc (object-table release). Confidence: medium. */
void FUN_0049c800(void)
{
    FUN_00491db4();
}

/* FUN_0049c838 @ 0x0049c838
 * Ghidra: void FUN_0049c838(long param_1)
 * Set the object-type tag in the state word at param_1+0x98 to 0x7 (upper
 * bits), preserving the low bits (mask 0xf3). Confidence: medium. */
void FUN_0049c838(long param_1)
{
    *(uint64_t *)(param_1 + 0x98) =
        *(uint64_t *)(param_1 + 0x98) & 0xf3 | 0x7000000000000000;
}

/* FUN_0049c850 @ 0x0049c850
 * Ghidra: void FUN_0049c850(long param_1)
 * Clear the object-type tag bits in the two state words at param_1+0x98 and
 * param_1+0x148, preserving the low 8 bits (mask 0xf0000000000000f3).
 * Confidence: medium. */
void FUN_0049c850(long param_1)
{
    *(uint64_t *)(param_1 + 0x98) = *(uint64_t *)(param_1 + 0x98) & 0xf0000000000000f3;
    *(uint64_t *)(param_1 + 0x148) = *(uint64_t *)(param_1 + 0x148) & 0xf0000000000000f3;
}

/* FUN_0049c874 @ 0x0049c874
 * Ghidra: void FUN_0049c874(void)
 * Small release shim to FUN_00021480. Confidence: medium. */
void FUN_0049c874(void)
{
    FUN_00021480();
}

/* FUN_0049c88c @ 0x0049c88c
 * Ghidra: void FUN_0049c88c(void)
 * Release the object at x20+0x10 (via FUN_004abf50), release the head object,
 * tail-return. Confidence: medium. */
void FUN_0049c88c(void)
{
    FUN_004abf50(*(uint64_t *)(((long)0) + 0x10));
    FUN_0036b118();
    FUN_0036b21c();
}

/* FUN_0049c890 @ 0x0049c890
 * Ghidra: void FUN_0049c890(void)
 * Identical twin of 0049c88c. Confidence: medium. */
void FUN_0049c890(void)
{
    FUN_004abf50(*(uint64_t *)(((long)0) + 0x10));
    FUN_0036b118();
    FUN_0036b21c();
}

/* FUN_0049c8bc @ 0x0049c8bc
 * Ghidra: void FUN_0049c8bc(void)
 * Tear down a metadata object: run the pre-teardown, dispatch the 6 owned
 * words (x20+0x50..+0xa0) through FUN_004ab67c, then the metadata / runtime
 * steps FUN_0049c904 and FUN_00466104, and tail-return. Confidence: medium. */
void FUN_0049c8bc(void)
{
    FUN_004ab13c();
    FUN_004ab67c(*(uint64_t *)(((long)0) + 0x50), *(uint64_t *)(((long)0) + 0x60),
                 *(uint64_t *)(((long)0) + 0x70), *(uint64_t *)(((long)0) + 0x80),
                 *(uint64_t *)(((long)0) + 0x90), *(uint64_t *)(((long)0) + 0xa0));
    FUN_0049c904(0,0,0,0,0,0,0,0);
    FUN_00466104();
    FUN_0036b21c();
}

/* FUN_0049c904 @ 0x0049c904
 * Ghidra: void FUN_0049c904(param_1..param_4)
 * Tagged-teardown dispatcher: switch on the type-tag in stack bit 0x3c (top
 * 4 bits of an 8-word code). Default releases param_2; kind 4 releases via
 * FUN_004592dc; kind 6 releases param_4 and in_x7; kind 7 via FUN_00459138;
 * kinds 1/2/3/5 no-op. Confidence: medium (switch on register-tag). */
void FUN_0049c904(uint64_t param_1, uint64_t param_2, uint64_t param_3, uint64_t param_4,
                 uint64_t param_5, uint64_t param_6, uint64_t param_7, uint64_t param_8)
{
    uint64_t in_x7;
    uint64_t tag;

    (void)param_1; (void)param_3; (void)param_5; (void)param_6; (void)param_7; (void)param_8;
    tag = 0;   /* in_stack_00000058: tag word (unrecovered register) */
    if (7 < (uint32_t)(tag >> 0x3c)) {
        return;
    }
    switch (tag >> 0x34) {
    default:
        FUN_003a25d4(param_2);
        return;
    case 1:
    case 2:
    case 3:
    case 5:
        return;
    case 4:
        FUN_004592dc();
        return;
    case 6:
        FUN_0036b118(param_4);
        FUN_0036b118(in_x7);
        return;
    case 7:
        FUN_00459138();
        return;
    }
}

/* FUN_0049c9fc @ 0x0049c9fc
 * Ghidra: void FUN_0049c9fc(long param_1)
 * Set the object-type tag in the state word at param_1+0x98 to 0x3.
 * Confidence: medium. */
void FUN_0049c9fc(long param_1)
{
    *(uint64_t *)(param_1 + 0x98) =
        *(uint64_t *)(param_1 + 0x98) & 0xf3 | 0x3000000000000000;
}

/* FUN_0049ca14 @ 0x0049ca14
 * Ghidra: void FUN_0049ca14(long param_1)
 * Set the object-type tag in the state word at param_1+0x98 to 0x1.
 * Confidence: medium. */
void FUN_0049ca14(long param_1)
{
    *(uint64_t *)(param_1 + 0x98) =
        *(uint64_t *)(param_1 + 0x98) & 0xf3 | 0x1000000000000000;
}

/* FUN_0049ca2c @ 0x0049ca2c
 * Ghidra: void FUN_0049ca2c(long param_1)
 * Set the object-type tag in the state word at param_1+0x98 to 0x2.
 * Confidence: medium. */
void FUN_0049ca2c(long param_1)
{
    *(uint64_t *)(param_1 + 0x98) =
        *(uint64_t *)(param_1 + 0x98) & 0xf3 | 0x2000000000000000;
}

/* FUN_0049ca44 @ 0x0049ca44
 * Ghidra: void FUN_0049ca44(long param_1)
 * Clear the object-type tag in the state word at param_1+0x98 (mask 0xf3
 * preserves low 8 bits, no tag set). Confidence: medium. */
void FUN_0049ca44(long param_1)
{
    *(uint64_t *)(param_1 + 0x98) = *(uint64_t *)(param_1 + 0x98) & 0xf3;
}

/* FUN_0049ca58 @ 0x0049ca58
 * Ghidra: void FUN_0049ca58(long param_1)
 * Set the object-type tag in the state word at param_1+0x98 to 0x5.
 * Confidence: medium. */
void FUN_0049ca58(long param_1)
{
    *(uint64_t *)(param_1 + 0x98) =
        *(uint64_t *)(param_1 + 0x98) & 0xf3 | 0x5000000000000000;
}

/* FUN_0049ca74 @ 0x0049ca74
 * Ghidra: void FUN_0049ca74(void)
 * Release the object at x20+0x10 and tail-return. Confidence: medium. */
void FUN_0049ca74(void)
{
    FUN_0036b118(*(uint64_t *)(((long)0) + 0x10));
    FUN_0036b21c();
}

/* FUN_0049ca78 @ 0x0049ca78
 * Ghidra: void FUN_0049ca78(void)
 * Identical twin of 0049ca74. Confidence: medium. */
void FUN_0049ca78(void)
{
    FUN_0036b118(*(uint64_t *)(((long)0) + 0x10));
    FUN_0036b21c();
}

/* FUN_0049caa0 @ 0x0049caa0
 * Ghidra: void FUN_0049caa0(void)
 * Release the object at x20+0x58 (via FUN_004abf50), release the head,
 * tail-return. Confidence: medium. */
void FUN_0049caa0(void)
{
    FUN_004abf50(*(uint64_t *)(((long)0) + 0x58));
    FUN_0036b118();
    FUN_0036b21c();
}

/* FUN_0049caa4 @ 0x0049caa4
 * Ghidra: void FUN_0049caa4(void)
 * Identical twin of 0049caa0. Confidence: medium. */
void FUN_0049caa4(void)
{
    FUN_004abf50(*(uint64_t *)(((long)0) + 0x58));
    FUN_0036b118();
    FUN_0036b21c();
}

/* FUN_0049cad0 @ 0x0049cad0
 * Ghidra: void FUN_0049cad0(void)
 * Tear down a metadata object: pre-teardown, FUN_004acb80, release the object
 * at x20+0x68, release head, tail-return. Confidence: medium. */
void FUN_0049cad0(void)
{
    FUN_004ab13c();
    FUN_004acb80();
    FUN_004abf50(*(uint64_t *)(((long)0) + 0x68));
    FUN_0036b118();
    FUN_0036b21c();
}

/* FUN_0049cb10 @ 0x0049cb10
 * Ghidra: void FUN_0049cb10(void)
 * Release the object at x20+0x10 and tail-return. Confidence: medium. */
void FUN_0049cb10(void)
{
    FUN_0036b118(*(uint64_t *)(((long)0) + 0x10));
    FUN_0036b21c();
}

/* FUN_0049cb14 @ 0x0049cb14
 * Ghidra: void FUN_0049cb14(void)
 * Identical twin of 0049cb10. Confidence: medium. */
void FUN_0049cb14(void)
{
    FUN_0036b118(*(uint64_t *)(((long)0) + 0x10));
    FUN_0036b21c();
}

/* FUN_0049cb3c @ 0x0049cb3c
 * Ghidra: void FUN_0049cb3c(void)
 * Tear down a 3-slot metadata object: release x20+0x18, release x20+0x30 via
 * FUN_004abf50, release head, and if the tag at x20+0x38 is nonzero release
 * the triplet (x20+0x48/0x50/0x58) via FUN_0049cb88. Tail-return.
 * Confidence: medium. */
void FUN_0049cb3c(void)
{
    FUN_003a25d4(*(uint64_t *)(((long)0) + 0x18));
    FUN_004abf50(*(uint64_t *)(((long)0) + 0x30));
    FUN_0036b118();
    if (*(long *)(((long)0) + 0x38) != 0) {
        FUN_0049cb88(*(uint64_t *)(((long)0) + 0x48), *(uint64_t *)(((long)0) + 0x50),
                     *(uint8_t *)(((long)0) + 0x58));
    }
    FUN_0036b21c();
}

/* FUN_0049cb40 @ 0x0049cb40
 * Ghidra: void FUN_0049cb40(void)
 * Identical twin of 0049cb3c. Confidence: medium. */
void FUN_0049cb40(void)
{
    FUN_003a25d4(*(uint64_t *)(((long)0) + 0x18));
    FUN_004abf50(*(uint64_t *)(((long)0) + 0x30));
    FUN_0036b118();
    if (*(long *)(((long)0) + 0x38) != 0) {
        FUN_0049cb88(*(uint64_t *)(((long)0) + 0x48), *(uint64_t *)(((long)0) + 0x50),
                     *(uint8_t *)(((long)0) + 0x58));
    }
    FUN_0036b21c();
}

/* FUN_0049cb88 @ 0x0049cb88
 * Ghidra: void FUN_0049cb88(undefined8 param_1, undefined8 param_2, byte param_3)
 * If the kind tag param_3 is < 4, release param_2; otherwise no-op.
 * Confidence: medium. */
void FUN_0049cb88(uint64_t param_1, uint64_t param_2, uint8_t param_3)
{
    if (param_3 < 4) {
        FUN_0036b118(param_2);
        return;
    }
}

/* FUN_0049cba0 @ 0x0049cba0
 * Ghidra: void FUN_0049cba0(void)
 * Initialize a metadata/registration object: FUN_0049cd00(0x657c30,
 * &DAT_0049cbe8, &DAT_004eb078). Confidence: medium. */
void FUN_0049cba0(void)
{
    FUN_0049cd00(0x657c30, (void*)0x49cbe8, (void*)0x4eb078);
}

/* FUN_0049cba4 @ 0x0049cba4
 * Ghidra: void FUN_0049cba4(void)
 * Identical twin of 0049cba0. Confidence: medium. */
void FUN_0049cba4(void)
{
    FUN_0049cd00(0x657c30, (void*)0x49cbe8, (void*)0x4eb078);
}

/* FUN_0049cbf8 @ 0x0049cbf8
 * Ghidra: void FUN_0049cbf8(void)
 * Lazily initialize the global at 0x657c40 from FUN_00376820(key 0x5a3d38,
 * 0x6865e0) and store the result (write to the "read-only" 0x657c40 is a
 * decompiler artifact — it is a mutable global). Confidence: medium. */
void FUN_0049cbf8(void)
{
    *(uint64_t *)0x657c40 = FUN_00376820((void*)0x5a3d38, 0x6865e0);
}

/* FUN_0049cbfc @ 0x0049cbfc
 * Ghidra: void FUN_0049cbfc(void)
 * Identical twin of 0049cbf8 (lazy global 0x657c40 init). Confidence: medium. */
void FUN_0049cbfc(void)
{
    *(uint64_t *)0x657c40 = FUN_00376820((void*)0x5a3d38, 0x6865e0);
}

/* FUN_0049cc3c @ 0x0049cc3c
 * Ghidra: void FUN_0049cc3c(long param_1)
 * Store the value from FUN_0049cc64 into param_1+8. Confidence: medium. */
void FUN_0049cc3c(long param_1)
{
    uint64_t value;
    value = FUN_0049cc64();
    *(uint64_t *)(param_1 + 8) = value;
}

/* FUN_0049cc64 @ 0x0049cc64
 * Ghidra: void FUN_0049cc64(void)
 * Store a magic constant into the global 0x657c48. Confidence: low (decompile
 * shows a literal SUB stub; the "sub_dac1..." symbol is an address artifact). */
uint64_t FUN_0049cc64(void)
{
    return *(uint64_t *)0x657c48;
}

/* FUN_0049ccb8 @ 0x0049ccb8
 * Ghidra: void FUN_0049ccb8(void)
 * Initialize a metadata object: FUN_0049cd00(0x657c50, FUN_0049cc64,
 * &DAT_004eb028). Confidence: medium. */
void FUN_0049ccb8(void)
{
    FUN_0049cd00(0x657c50, (void*)FUN_0049cc64, (void*)0x4eb028);
}

/* FUN_0049ccbc @ 0x0049ccbc
 * Ghidra: void FUN_0049ccbc(void)
 * Identical twin of 0049ccb8. Confidence: medium. */
void FUN_0049ccbc(void)
{
    FUN_0049cd00(0x657c50, (void*)FUN_0049cc64, (void*)0x4eb028);
}

/* FUN_0049cd00 @ 0x0049cd00
 * Ghidra: void FUN_0049cd00(void)
 * Register a metadata/collection object with the runtime: query the metadata
 * table via FUN_00352b20; if unset, register it (FUN_00027614) and run the
 * object's constructor method, then lazily init and store the result through
 * *x19. Confidence: medium. */
void FUN_0049cd00(void)
{
    cl4_pair_t meta;
    uint64_t   value;
    uint64_t  *target;

    meta = FUN_00352b20();
    if (meta.lo == 0) {
        FUN_00027614(0x657c38, (void*)0x5a3d30);
        value = ((uint64_t(*)(void))meta.hi)();
        FUN_00350af4(value, meta.hi, &value);
        target = (uint64_t *)0;
        *target = FUN_00376820();
    }
}

/* FUN_0049cd70 @ 0x0049cd70
 * Ghidra: void FUN_0049cd70(long param_1)
 * Store the value from FUN_0049cd98 into param_1+8. Confidence: medium. */
void FUN_0049cd70(long param_1)
{
    uint64_t value;
    value = FUN_0049cd98();
    *(uint64_t *)(param_1 + 8) = value;
}

/* FUN_0049cd98 @ 0x0049cd98
 * Ghidra: void FUN_0049cd98(void)
 * Store a magic constant into the global 0x657c58. Confidence: low. */
uint64_t FUN_0049cd98(void)
{
    return *(uint64_t *)0x657c58;
}

/* FUN_0049cdfc @ 0x0049cdfc
 * Ghidra: void FUN_0049cdfc(void)
 * Swap two owned words (x20+8 with the source x1+8; x20+0x10 with the source
 * x19+0x10), releasing the old values. Confidence: medium. */
void FUN_0049cdfc(void)
{
    long   src;
    uint64_t v;

    FUN_0034b264();
    src = 0;                 /* extraout_x1 (unrecovered) */
    v = *(uint64_t *)(((long)0) + 8);
    *(uint64_t *)(((long)0) + 8) = *(uint64_t *)(src + 8);
    thunk_FUN_0036b270();
    FUN_003a25d4(v);
    v = *(uint64_t *)(((long)0) + 0x10);
    *(uint64_t *)(((long)0) + 0x10) = *(uint64_t *)(((long)0) + 0x10);
    FUN_0036b270();
    FUN_0036b118(v);
}

/* FUN_0049ce9c @ 0x0049ce9c
 * Ghidra: void FUN_0049ce9c(long param_1)
 * Tear down a 3-owner object at param_1: if the refcount at param_1+0x30
 * exceeds 1, release the lock at param_1+0x18; release param_1+0x40 and
 * param_1+0x60. Confidence: medium. */
void FUN_0049ce9c(long param_1)
{
    if (1 < *(uint64_t *)(param_1 + 0x30)) {
        FUN_000026e8(param_1 + 0x18);
    }
    FUN_003a25d4(*(uint64_t *)(param_1 + 0x40));
    FUN_003a25d4(*(uint64_t *)(param_1 + 0x60));
}

/* FUN_0049cee0 @ 0x0049cee0
 * Ghidra: void FUN_0049cee0(undefined8 param_1, undefined8 param_2, long param_3)
 * Build a metadata object into x19 from the source at x20: run the runtime
 * steps (FUN_00350c5c, FUN_004ac3c0), then either set up a sub-object method
 * (param_3==0 via FUN_004ab10c) or copy the source's method word, dispatch
 * the sub-object, and copy the source's +0x58/+0x60 owned words. Confidence:
 * medium (register-heavy metadata shuffle). */
void FUN_0049cee0(uint64_t param_1, uint64_t param_2, long param_3)
{
    cl4_pair_t meta;

    FUN_00350c5c();
    FUN_004ac3c0();
    if (0) {                 /* in_ZR branch (unrecovered) */
        FUN_004ac3a8();
    } else {
        if (param_3 == 0) {
            meta = FUN_004ab10c();
            *(void **)(((long)0) + 0x28) = (void *)meta.lo;
        } else {
            *(long *)(((long)0) + 0x30) = param_3;
            FUN_0034b07c();
            (*(void (**)(long, long))((long)0))(((long)0) + 0x18, ((long)0) + 0x18);
        }
    }
    FUN_004abe08();
    *(uint64_t *)(((long)0) + 0x58) = *(uint64_t *)(((long)0) + 0x58);
    *(uint64_t *)(((long)0) + 0x60) = *(uint64_t *)(((long)0) + 0x60);
    thunk_FUN_0036b270();
    thunk_FUN_0036b270(*(uint64_t *)(((long)0) + 0x60));
}

/* FUN_0049cf68 @ 0x0049cf68
 * Ghidra: void FUN_0049cf68(undefined8 param_1, long param_2, long param_3)
 * Copy a metadata object from param_2 into x19 with type-based dispatch: based
 * on the two refcount words at (+0x30 of each side), run the matching copy
 * path (single-owner vs shared), copy the +0x38/+0x58/+0x60 owned words, and
 * release the old values. Confidence: medium (large branchy metadata copy). */
void FUN_0049cf68(uint64_t param_1, long param_2, long param_3)
{
    cl4_pair_t meta;
    long       src_ref;
    long       dst_ref;

    meta = FUN_0034f2f4();
    dst_ref = *(long *)(meta.hi + 0x30);
    src_ref = *(long *)(meta.lo + 0x30);
    if (src_ref == 1) {
        if (dst_ref == 1) {
            FUN_004abe40();
            goto common;
        }
        FUN_004acac0();
        param_3 = *(long *)(param_2 + 0x30);
        if (param_3 != 0) {
            *(long *)(((long)0) + 0x30) = param_3;
            FUN_0034b07c();
            (*(void (**)(long, long))((long)0))(((long)0) + 0x18, param_2 + 0x18);
            goto common;
        }
    } else {
        if (dst_ref == 1) {
            FUN_004aaa88();
            FUN_004a4b14(((long)0) + 8);
            FUN_004abb64();
            goto common;
        }
        FUN_004ac390();
        if (0 == 0) goto check3;
        if (param_3 != 0) {
            FUN_0032b65c(((long)0) + 0x18, param_2 + 0x18);
            goto common;
        }
        FUN_000026e8(((long)0) + 0x18);
    }
check3:
    FUN_004ab954();
common:
    *(uint64_t *)(((long)0) + 0x38) = *(uint64_t *)(param_2 + 0x38);
    FUN_004aae88();
    thunk_FUN_0036b270();
    FUN_003a25d4();
    FUN_004abdec();
    *(uint64_t *)(((long)0) + 0x58) = *(uint64_t *)(param_2 + 0x58);
    *(uint64_t *)(((long)0) + 0x60) = *(uint64_t *)(param_2 + 0x60);
    thunk_FUN_0036b270();
    FUN_003a25d4(*(uint64_t *)(((long)0) + 0x60));
}

/* FUN_0049d06c @ 0x0049d06c
 * Ghidra: void FUN_0049d06c(void)
 * Tear down / deallocate the metadata object at x19 based on the refcount at
 * x20+0x30: shared path releases the method word and lock, single-owner path
 * releases the head words; then release the +0x58/+0x60 owned words.
 * Confidence: medium. */
void FUN_0049d06c(void)
{
    uint64_t old_60;

    FUN_00350c5c();
    FUN_004ac264();
    if (0) {                 /* in_ZR path (unrecovered) */
    } else {
        if (*(long *)(((long)0) + 0x30) != 1) {
            FUN_004acac0();
            if (0 != 0) {
                FUN_000026e8(((long)0) + 0x18);
            }
            FUN_004ab10c();
            goto done;
        }
        FUN_004aaa88();
        FUN_004a4b14(((long)0) + 8);
    }
    FUN_004aca6c();
done:
    FUN_004acc70();
    FUN_004abdd0();
    old_60 = *(uint64_t *)(((long)0) + 0x60);
    *(uint64_t *)(((long)0) + 0x58) = *(uint64_t *)(((long)0) + 0x58);
    *(uint64_t *)(((long)0) + 0x60) = *(uint64_t *)(((long)0) + 0x60);
    FUN_003a25d4(old_60);
}

/* FUN_0049d190 @ 0x0049d190
 * Ghidra: void FUN_0049d190(long param_1)
 * Register an observation / add a sub-object: FUN_00374104(param_1, 0, 3,
 * &local_kinds, param_1+0x40) with the kind strings at 0x5a3fe8/0x5a4000 and
 * address 0x67a6f0. Confidence: medium. */
void FUN_0049d190(long param_1)
{
    void *kinds[2];

    kinds[0] = (void*)0x5a3fe8;
    kinds[1] = (void*)0x5a4000;
    FUN_00374104(param_1, 0, 3, &kinds, param_1 + 0x40);
}

/* FUN_0049d1ec @ 0x0049d1ec
 * Ghidra: void FUN_0049d1ec(void)
 * Release shim to FUN_00021480. Confidence: medium. */
void FUN_0049d1ec(void)
{
    FUN_00021480();
}

/* FUN_0049d204 @ 0x0049d204
 * Ghidra: void FUN_0049d204(long param_1)
 * Register an observation with a single kind: FUN_00374104(param_1, 0, 1,
 * &kind, param_1+0x40) where kind = 0x5a4048. Confidence: medium. */
void FUN_0049d204(long param_1)
{
    void *kind;
    kind = (void*)0x5a4048;
    FUN_00374104(param_1, 0, 1, &kind, param_1 + 0x40);
}

/* FUN_0049d248 @ 0x0049d248
 * Ghidra: void FUN_0049d248(void)
 * Release shim to FUN_00021480. Confidence: medium. */
void FUN_0049d248(void)
{
    FUN_00021480();
}

/* FUN_0049d2d8 @ 0x0049d2d8
 * Ghidra: void FUN_0049d2d8(void)
 * Swap the head words of x19 and x20, releasing the old head, and copy the
 * byte at x19+8 into x20's +1 byte. Confidence: medium. */
void FUN_0049d2d8(void)
{
    cl4_pair_t meta;
    uint64_t   old_head;

    meta = FUN_003504d0();
    old_head = *(uint64_t *)(meta.lo);
    *((uint64_t *)0) = *(uint64_t *)(meta.hi);
    FUN_0036b118(old_head);
    *(uint8_t *)(((long)0) + 1) = *(uint8_t *)(((long)0) + 8);
}

/* FUN_0049d320 @ 0x0049d320
 * Ghidra: void FUN_0049d320(param_1..param_8)
 * Tagged syscall/teardown dispatcher: switch on the type tag (stack word
 * 0x108 bits 0x39..0x3b). Kind 1 forwards to FUN_0049d538 with the 8 stack
 * words; kinds 2/5/6/7 release; kinds 3/4 release param_2; default forwards
 * to FUN_0049d538(param_1..param_8). Confidence: medium. */
void FUN_0049d320(uint64_t p1, uint64_t p2, uint64_t p3, uint64_t p4,
                  uint64_t p5, uint64_t p6, uint64_t p7, uint64_t p8)
{
    uint64_t s70, s78, s80, s88, s90, s98, sa0, sa8;
    uint64_t tag;

    tag = 0;   /* in_stack_00000108: tag word (unrecovered) */
    switch (tag >> 0x39 & 7) {
    default:
        break;
    case 1:
        FUN_0049d538(0,0,0,0,0,0,0,0);
        p1 = s70; p2 = s78; p3 = s80; p4 = s88;
        p5 = s90; p6 = s98; p7 = sa0; p8 = sa8;
        break;
    case 2:
    case 5:
    case 6:
    case 7:
        FUN_0036b270();
        return;
    case 3:
    case 4:
        thunk_FUN_0036b270(p2);
        return;
    }
    FUN_0049d538(p1, p2, p3, p4, p5, p6, p7, p8);
}

/* FUN_0049d538 @ 0x0049d538
 * Ghidra: void FUN_0049d538(param_1..param_4)
 * Tagged teardown dispatcher (analogue of 0049c904). Default releases param_2;
 * kind 4 via FUN_0045a1f8; kind 6 releases param_4 and in_x7; kind 7 via
 * FUN_0045a4b4; kinds 1/2/3/5 no-op. Confidence: medium. */
void FUN_0049d538(uint64_t p1, uint64_t p2, uint64_t p3, uint64_t p4,
                 uint64_t p5, uint64_t p6, uint64_t p7, uint64_t p8)
{
    uint64_t in_x7;
    uint64_t tag;

    (void)p1; (void)p3; (void)p5; (void)p6; (void)p7; (void)p8;
    tag = 0;   /* in_stack_00000058 tag word */
    if (7 < (uint32_t)(tag >> 0x3c)) {
        return;
    }
    switch (tag >> 0x34) {
    default:
        thunk_FUN_0036b270(p2);
        return;
    case 1:
    case 2:
    case 3:
    case 5:
        return;
    case 4:
        FUN_0045a1f8();
        return;
    case 6:
        FUN_0036b270(p4);
        FUN_0036b270(in_x7);
        return;
    case 7:
        FUN_0045a4b4();
        return;
    }
}

/* FUN_0049d630 @ 0x0049d630
 * Ghidra: void FUN_0049d630(void)
 * Dispatch the metadata context (FUN_004aadb8) through FUN_004aac88 with the
 * 8 owned words at +0x40..+0xb0, then the tagged teardown FUN_0049d690.
 * Confidence: medium. */
void FUN_0049d630(void)
{
    long   ctx;

    ctx = FUN_004aadb8();
    FUN_004aac88(*(uint64_t *)(ctx + 0x40), *(uint64_t *)(ctx + 0x50),
                 *(uint64_t *)(ctx + 0x60), *(uint64_t *)(ctx + 0x70),
                 *(uint64_t *)(ctx + 0x80), *(uint64_t *)(ctx + 0x90),
                 *(uint64_t *)(ctx + 0xa0), *(uint64_t *)(ctx + 0xb0));
    FUN_0049d690(0,0,0,0,0,0,0,0);
}

/* FUN_0049d690 @ 0x0049d690
 * Ghidra: void FUN_0049d690(param_1..param_8)
 * Tagged dispatcher (analogue of 0049d320). Kind 1 forwards to FUN_0049c904;
 * kinds 2/5/6/7 release; kinds 3/4 release param_2; default forwards to
 * FUN_0049c904(param_1..param_8). Confidence: medium. */
void FUN_0049d690(uint64_t p1, uint64_t p2, uint64_t p3, uint64_t p4,
                  uint64_t p5, uint64_t p6, uint64_t p7, uint64_t p8)
{
    uint64_t s70, s78, s80, s88, s90, s98, sa0, sa8;
    uint64_t tag;

    tag = 0;   /* in_stack_00000108 tag word */
    switch (tag >> 0x39 & 7) {
    default:
        break;
    case 1:
        FUN_0049c904(0,0,0,0,0,0,0,0);
        p1 = s70; p2 = s78; p3 = s80; p4 = s88;
        p5 = s90; p6 = s98; p7 = sa0; p8 = sa8;
        break;
    case 2:
    case 5:
    case 6:
    case 7:
        FUN_0036b118();
        return;
    case 3:
    case 4:
        FUN_003a25d4(p2);
        return;
    }
    FUN_0049c904(p1, p2, p3, p4, p5, p6, p7, p8);
}

/* FUN_0049d8a8 @ 0x0049d8a8
 * Ghidra: void FUN_0049d8a8(void)
 * Dispatch the launch-image metadata pair through the collection pipeline:
 * save the 36 words at +0x40..+0x158 of the source (from FUN_0008e518), run
 * the runtime steps (FUN_000b4390, FUN_00350bfc, FUN_004abb1c, FUN_0049d320,
 * FUN_00462fec), then write the 36 words back into the destination +0x40..
 * +0x158, and report via FUN_0008e500. Confidence: medium. */
void FUN_0049d8a8(void)
{
    cl4_pair_t img;
    long       dst, src;
    uint64_t   w[36];

    img = FUN_0008e518();
    src = img.hi;
    dst = img.lo;
    for (int i = 0; i < 36; i++) {
        w[i] = *(uint64_t *)(src + 0x40 + i * 8);
    }
    FUN_000b4390();
    FUN_00350bfc();
    FUN_004abb1c();
    FUN_0049d320(0,0,0,0,0,0,0,0);
    FUN_00462fec();
    for (int i = 0; i < 36; i++) {
        *(uint64_t *)(dst + 0x40 + i * 8) = w[i];
    }
    FUN_0008e500(dst, 0);
}

/* FUN_0049dac8 @ 0x0049dac8
 * Ghidra: void FUN_0049dac8(void)
 * Dispatch the launch-image metadata pair through a larger pipeline: save the
 * 44 words at +0..+0x2b0 of the source, run FUN_00351274 and the tagged
 * dispatcher FUN_0049d320, swap 44 words between source and destination
 * (rotating them), dispatch 16 of them through FUN_004aac88, run the tagged
 * FUN_0049d690, and report via FUN_0008e500. Confidence: medium. */
void FUN_0049dac8(void)
{
    cl4_pair_t img;
    uint64_t  *src, *dst;
    uint64_t   w[44];
    uint64_t   tmp;
    int        i;

    img = FUN_0008e518();
    src = (uint64_t *)img.hi;
    dst = (uint64_t *)img.lo;
    for (i = 0; i < 44; i++) {
        w[i] = src[i];
    }
    img = FUN_00351274();
    FUN_0049d320(img.lo, img.hi, w[2], w[3], w[4], w[5], w[6], w[7]);
    /* rotate dst<->src in word triples */
    for (i = 0; i < 6; i++) {
        tmp = dst[i * 2];
        dst[i * 2] = w[i * 2];
        w[i * 2] = tmp;
    }
    for (i = 0; i < 6; i++) {
        tmp = dst[12 + i * 2];
        dst[12 + i * 2] = w[8 + i * 2];
        w[8 + i * 2] = tmp;
    }
    for (i = 0; i < 6; i++) {
        dst[0x18 + i * 2] = w[0x14 + i * 2];
    }
    FUN_004aac88(w[8], w[9], w[12], w[13], w[16], w[17], w[20], w[21],
                 w[1], w[2], w[3], w[4], w[5], w[6], w[7], w[10]);
    FUN_0049d690(0,0,0,0,0,0,0,0);
    FUN_0008e500(dst, 0);
}

/* FUN_0049dd58 @ 0x0049dd58
 * Ghidra: void FUN_0049dd58(undefined1 param_1 [16], undefined1 param_2 [16], undefined8 param_3, undefined8 param_4)
 * Shuffle the 44-word metadata struct at x19: run FUN_00352b20 + FUN_00463028,
 * then overwrite the 44 words from the extraout_x8 source (releasing the
 * prior owned values via FUN_004aac88 + FUN_0049d690). Confidence: medium. */
void FUN_0049dd58(uint8_t param_1[16], uint8_t param_2[16], uint64_t param_3, uint64_t param_4)
{
    cl4_pair_t meta;
    cl4_pair_t r;
    uint64_t  *dst;
    uint64_t  *src;
    int        i;

    (void)param_1; (void)param_2; (void)param_3; (void)param_4;
    meta = FUN_00352b20(param_4);
    r = FUN_00463028(meta.lo, ((uint64_t*)0)[1], ((uint64_t*)0)[2]);
    dst = (uint64_t *)0;
    src = (uint64_t *)0;      /* extraout_x8: 44-word source */
    for (i = 0; i < 22; i++) {
        dst[i * 2] = src[i * 2];
        dst[i * 2 + 1] = src[i * 2 + 1];
    }
    FUN_004aac88(r.lo, 0, ((uint64_t*)0)[0xc], ((uint64_t*)0)[0xe],
                 ((uint64_t*)0)[0x10], ((uint64_t*)0)[0x12],
                 ((uint64_t*)0)[0x14], ((uint64_t*)0)[0x16]);
    FUN_0049d690(0,0,0,0,0,0,0,0);
}

/* FUN_0049de60 @ 0x0049de60
 * Ghidra: void FUN_0049de60(undefined8 *param_1, uint param_2, int param_3)
 * Initialize a small metadata/object array of param_2 entries: if the count's
 * high bit is set (grow flag), zero the 11 header words, build the per-entry
 * method via FUN_004aabb8(param_2 & 0x7fffffff) filling 5 slots, and set the
 * flag at +0x2c when param_3 is negative. Otherwise store the count and (if
 * param_2 nonzero) run FUN_004ac050 and zero a 0xc0-byte region at +0x14.
 * Confidence: medium. */
void FUN_0049de60(uint64_t *param_1, uint32_t param_2, int param_3)
{
    cl4_pair_t m;

    if ((int)param_2 < 0) {
        param_1[0x2b] = 0;
        param_1[0x20] = 0;
        param_1[0x1f] = 0;
        param_1[0x1e] = 0;
        param_1[0x1d] = 0;
        param_1[0x1c] = 0;
        param_1[0x1b] = 0;
        param_1[0x1a] = 0;
        param_1[0x19] = 0;
        param_1[0x18] = 0;
        param_1[0x17] = 0;
        param_1[0x16] = 0;
        param_1[0x15] = 0;
        m = FUN_004aabb8(param_2 & 0x7fffffff);
        *(void **)(param_1 + 0x29) = (void *)m.lo;
        *(void **)(param_1 + 0x27) = (void *)m.lo;
        *(void **)(param_1 + 0x25) = (void *)m.lo;
        *(void **)(param_1 + 0x23) = (void *)m.lo;
        *(void **)(param_1 + 0x21) = (void *)m.lo;
        *param_1 = 0;
        if (param_3 < 0) {
            *(uint8_t *)(param_1 + 0x2c) = 1;
        }
    } else {
        if (param_3 < 0) {
            *(uint8_t *)(param_1 + 0x2c) = 0;
        }
        if (param_2 != 0) {
            FUN_004ac050();
            param_1[0x13] = 0;
            thunk_FUN_00114330(param_1 + 0x14, 0xc0);
            return;
        }
    }
}

/* FUN_0049df0c @ 0x0049df0c
 * Ghidra: ulong FUN_0049df0c(long param_1)
 * Return the object-type tag (bits 0x39..0x3b) of the state word at
 * param_1+0x148. Confidence: medium. */
uint64_t FUN_0049df0c(long param_1)
{
    return *(uint64_t *)(param_1 + 0x148) >> 0x39 & 7;
}

/* FUN_0049df18 @ 0x0049df18
 * Ghidra: void FUN_0049df18(long param_1)
 * Clear the object-type tag (bits 0x39..0x3b) of the state word at
 * param_1+0x148. Confidence: medium. */
void FUN_0049df18(long param_1)
{
    *(uint64_t *)(param_1 + 0x148) =
        *(uint64_t *)(param_1 + 0x148) & 0xf1ffffffffffffff;
}

/* FUN_0049df60 @ 0x0049df60
 * Ghidra: void FUN_0049df60(void)
 * Dispatch the metadata context (FUN_004aadb8) through FUN_004ab67c with the
 * 6 owned words at +0x40..+0x90, then the tagged teardown FUN_0049c904.
 * Confidence: medium. */
void FUN_0049df60(void)
{
    long ctx;

    ctx = FUN_004aadb8();
    FUN_004ab67c(*(uint64_t *)(ctx + 0x40), *(uint64_t *)(ctx + 0x50),
                 *(uint64_t *)(ctx + 0x60), *(uint64_t *)(ctx + 0x70),
                 *(uint64_t *)(ctx + 0x80), *(uint64_t *)(ctx + 0x90));
    FUN_0049c904(0,0,0,0,0,0,0,0);
}

/* FUN_0049dfa0 @ 0x0049dfa0
 * Ghidra: void FUN_0049dfa0(void)
 * Dispatch a metadata object from FUN_004acae8: run the 4-word pre-dispatch
 * (FUN_004abb1c), the tagged teardown FUN_0049d538, then write the owned
 * words +0x40..+0x58 and +0x80..+0xa8 into the destination, run FUN_004ac908
 * and the report FUN_004acacc. Confidence: medium. */
void FUN_0049dfa0(void)
{
    cl4_pair_t meta;
    long       dst;
    uint64_t  *src;

    meta = FUN_004acae8();
    src = (uint64_t *)meta.hi;
    dst = meta.lo;
    FUN_004abb1c(src[0], src[1], src[2], src[3]);
    FUN_0049d538(0,0,0,0,0,0,0,0);
    FUN_00462fec();
    *(uint64_t *)(dst + 0x40) = src[8];
    *(uint64_t *)(dst + 0x48) = src[9];
    *(uint64_t *)(dst + 0x50) = src[10];
    *(uint64_t *)(dst + 0x58) = src[11];
    FUN_004ac908();
    *(uint64_t *)(dst + 0x80) = 0;
    *(uint64_t *)(dst + 0x88) = src[0x11];
    *(uint64_t *)(dst + 0x90) = src[0x12];
    *(uint64_t *)(dst + 0x98) = src[0x13];
    *(uint64_t *)(dst + 0xa0) = src[0x14];
    *(uint64_t *)(dst + 0xa8) = src[0x15];
    FUN_004acacc(dst, 0);
}

/* FUN_0049e090 @ 0x0049e090
 * Ghidra: void FUN_0049e090(void)
 * Dispatch a metadata object from FUN_004acae8 through the runtime pipeline:
 * save the 12 source words, run FUN_00350a04/FUN_00351aec and the tagged
 * teardown FUN_0049d538, swap the 12 words into the destination, dispatch 12
 * through FUN_004ac908, then FUN_004ab67c + FUN_0049c904, and report via
 * FUN_004acacc. Confidence: medium. */
void FUN_0049e090(void)
{
    cl4_pair_t meta;
    uint64_t  *src, *dst;
    uint64_t   w[12];
    int        i;

    meta = FUN_004acae8();
    src = (uint64_t *)meta.hi;
    dst = (uint64_t *)meta.lo;
    for (i = 0; i < 12; i++) w[i] = src[i];
    FUN_00350a04();
    FUN_00351aec();
    FUN_0049d538(0,0,0,0,0,0,0,0);
    for (i = 0; i < 6; i++) {
        uint64_t t = dst[i*2];
        dst[i*2] = w[i*2];
        w[i*2] = t;
    }
    FUN_004ac908(w[8], w[9], dst[0xc], dst[0xe], w[1], w[2], w[3], w[4],
                 w[5], w[6], w[7], w[10]);
    dst[0x10] = 0;
    dst[0x11] = src[0x11];
    dst[0x12] = src[0x12];
    dst[0x13] = src[0x13];
    dst[0x14] = src[0x14];
    dst[0x15] = src[0x15];
    FUN_004ab67c();
    FUN_0049c904(0,0,0,0,0,0,0,0);
    FUN_004acacc(dst, 0);
}

/* FUN_0049e1ac @ 0x0049e1ac
 * Ghidra: void FUN_0049e1ac(undefined1 param_1 [16], undefined1 param_2 [16])
 * Shuffle the 22-word metadata struct at x19: run FUN_00352b20 + FUN_00463028,
 * copy the 22 words from the source (extraout_x1), dispatch 6 through
 * FUN_004ab67c + FUN_0049c904. Confidence: medium. */
void FUN_0049e1ac(uint8_t param_1[16], uint8_t param_2[16])
{
    cl4_pair_t meta;
    cl4_pair_t r;
    uint64_t  *dst, *src;
    int        i;

    (void)param_1; (void)param_2;
    meta = FUN_00352b20();
    r = FUN_00463028(((uint64_t*)0)[1], meta.lo, meta.hi, ((uint64_t*)0)[2]);
    dst = (uint64_t *)0;
    src = (uint64_t *)0;      /* extraout_x1: 22-word source */
    for (i = 0; i < 11; i++) {
        dst[i*2] = src[i*2];
        dst[i*2+1] = src[i*2+1];
    }
    FUN_004ab67c(r.lo, 0, ((uint64_t*)0)[0xc], ((uint64_t*)0)[0xe],
                 ((uint64_t*)0)[0x10], ((uint64_t*)0)[0x12]);
    FUN_0049c904(0,0,0,0,0,0,0,0);
}

/* FUN_0049e274 @ 0x0049e274
 * Ghidra: void FUN_0049e274(undefined8 *param_1, uint param_2, int param_3)
 * Initialize a compact metadata/object array of param_2 entries: if the
 * count's high bit is set (grow flag), zero the +0x15 header word, build the
 * per-entry method via FUN_004aabb8(param_2 & 0x7fffffff), and set the flag
 * at +0x16 when param_3 is negative. Otherwise store the count (zeroing
 * +0x13/+0x14/+0x15 and running FUN_004ac050). Confidence: medium. */
void FUN_0049e274(uint64_t *param_1, uint32_t param_2, int param_3)
{
    cl4_pair_t m;

    if ((int)param_2 < 0) {
        param_1[0x15] = 0;
        m = FUN_004aabb8(param_2 & 0x7fffffff, 0);
        *param_1 = m.lo;
        if (param_3 < 0) {
            *(uint8_t *)(param_1 + 0x16) = 1;
        }
    } else {
        if (param_3 < 0) {
            *(uint8_t *)(param_1 + 0x16) = 0;
        }
        if (param_2 != 0) {
            FUN_004ac050();
            param_1[0x14] = 0;
            param_1[0x15] = 0;
            param_1[0x13] = 0;
        }
    }
}

/* FUN_0049e2d4 @ 0x0049e2d4
 * Ghidra: uint FUN_0049e2d4(int *param_1)
 * Return the object-type tag: either 8 (default) or the top 4 bits of the
 * +0x26-word if it is non-negative. Confidence: medium. */
uint32_t FUN_0049e2d4(int *param_1)
{
    uint32_t tag;

    tag = *param_1 + 8;
    if (-1 < *(long *)(param_1 + 0x26)) {
        tag = (uint32_t)((uint64_t)*(long *)(param_1 + 0x26) >> 0x3c);
    }
    return tag;
}

/* FUN_0049e2f0 @ 0x0049e2f0
 * Ghidra: void FUN_0049e2f0(long param_1)
 * Clear the object-type tag (all 60 high bits) of the state word at
 * param_1+0x98, keeping the low 8 bits. Confidence: medium. */
void FUN_0049e2f0(long param_1)
{
    *(uint64_t *)(param_1 + 0x98) =
        *(uint64_t *)(param_1 + 0x98) & 0xfffffffffffffff;
}

/* FUN_0049e300 @ 0x0049e300
 * Ghidra: void FUN_0049e300(ulong *param_1, long param_2)
 * Store an element count / type tag into a metadata word: if param_2 < 8,
 * pack it into the top byte of +0x13 (with a 0xf3 low mask); else store the
 * count-8 in *param_1, zero the 0x90-byte body at +1, and set the grow bit
 * (0x8000000000000000) in +0x13, zeroing +0x14/+0x15. Confidence: medium. */
void FUN_0049e300(uint64_t *param_1, long param_2)
{
    uint64_t v;

    if ((uint32_t)param_2 < 8) {
        v = param_1[0x13] & 0xf3 | (uint64_t)((uint32_t)param_2) << 0x3c;
    } else {
        *param_1 = (uint64_t)((uint32_t)param_2 - 8);
        thunk_FUN_00114330(param_1 + 1, 0x90);
        v = 0x8000000000000000;
        param_1[0x14] = 0;
        param_1[0x15] = 0;
    }
    param_1[0x13] = v;
}

/* FUN_0049e634 @ 0x0049e634
 * Ghidra: void FUN_0049e634(void)
 * Get the metadata context (FUN_004aadb8) and run the dispatch FUN_00458db4.
 * Confidence: medium. */
void FUN_0049e634(void)
{
    FUN_004aadb8();
    FUN_00458db4();
}

/* FUN_0049e66c @ 0x0049e66c
 * Ghidra: void FUN_0049e66c(void)
 * Rebuild a metadata object at x19: run the runtime steps (FUN_0035193c,
 * FUN_004630d8, FUN_00462b6c, FUN_00464864, FUN_0045c1e0, FUN_00463080,
 * FUN_00463810), then store the new +0x40/+0x48/+0x50 words and run
 * FUN_00458db4 + FUN_00351774. Confidence: medium. */
void FUN_0049e66c(void)
{
    uint8_t flag;

    FUN_0035193c();
    FUN_004630d8();
    flag = 0;                /* (uint)*(byte*)(extraout_x1+0x50) */
    FUN_00462b6c();
    FUN_00464864();
    FUN_0045c1e0();
    FUN_00463080();
    FUN_00463810(*(uint64_t *)(((long)0) + 0x40));
    *(uint64_t *)(((long)0) + 0x40) = 0;
    *(uint64_t *)(((long)0) + 0x48) = 0;
    *(char *)(((long)0) + 0x50) = (char)flag;
    FUN_00458db4();
    FUN_00351774();
}

/* FUN_0049e6f0 @ 0x0049e6f0
 * Ghidra: undefined8 * FUN_0049e6f0(undefined8 *param_1, undefined8 *param_2)
 * Swap the 11-word metadata struct at param_1 with the one at param_2,
 * dispatching the old 11 words through FUN_00458db4. Returns param_1.
 * Confidence: medium. */
uint64_t *FUN_0049e6f0(uint64_t *param_1, uint64_t *param_2)
{
    uint64_t old[11];
    int      i;

    for (i = 0; i < 11; i++) old[i] = param_1[i];
    for (i = 0; i < 11; i++) param_1[i] = param_2[i];
    FUN_00458db4(old[0], old[1], old[2], old[3], old[4], old[5], old[6],
                 old[7], old[8], old[9], old[10]);
    return param_1;
}

/* FUN_0049e7d0 @ 0x0049e7d0
 * Ghidra: void FUN_0049e7d0(void)
 * Get the metadata context (FUN_004aadb8), dispatch its 3 words (+0x40/0x50/
 * 0x60) through FUN_003540d0, then FUN_004593ac. Confidence: medium. */
void FUN_0049e7d0(void)
{
    long ctx;

    ctx = FUN_004aadb8();
    FUN_003540d0(*(uint64_t *)(ctx + 0x40), *(uint64_t *)(ctx + 0x50),
                 *(uint64_t *)(ctx + 0x60));
    FUN_004593ac();
}

/* FUN_0049e80c @ 0x0049e80c
 * Ghidra: void FUN_0049e80c(void)
 * Rebuild a metadata object at x19 from the runtime context: run the runtime
 * steps and store the 6 owned words at +0x40..+0x78 (a 6-slot variant of
 * 0049e66c). Confidence: medium. */
void FUN_0049e80c(void)
{
    FUN_004630d8();
    FUN_00462b6c();
    FUN_00464864();
    FUN_0045c160();
    FUN_00463810();
    *(uint64_t *)(((long)0) + 0x40) = 0;
    *(uint64_t *)(((long)0) + 0x48) = 0;
    *(uint64_t *)(((long)0) + 0x50) = 0;
    *(uint64_t *)(((long)0) + 0x58) = 0;
    *(uint64_t *)(((long)0) + 0x60) = 0;
    *(uint64_t *)(((long)0) + 0x68) = 0;
    *(uint64_t *)(((long)0) + 0x70) = 0;
    *(uint64_t *)(((long)0) + 0x78) = 0;
}

/* FUN_0049e8b8 @ 0x0049e8b8
 * Ghidra: void FUN_0049e8b8(void)
 * Rebuild a metadata object at x19 with a 4-arg dispatch (FUN_00463810 with
 * 4 source words), storing 6 owned words at +0x40..+0x78, then dispatch
 * FUN_003540d0 + FUN_004593ac. Confidence: medium. */
void FUN_0049e8b8(void)
{
    FUN_004630d8();
    FUN_00462b6c();
    FUN_00464864();
    FUN_0045c160();
    FUN_00463080();
    FUN_00463810(*(uint64_t *)(((long)0) + 0x70), *(uint64_t *)(((long)0) + 0x40),
                 *(uint64_t *)(((long)0) + 0x50), *(uint64_t *)(((long)0) + 0x60));
    *(uint64_t *)(((long)0) + 0x40) = 0;
    *(uint64_t *)(((long)0) + 0x48) = 0;
    *(uint64_t *)(((long)0) + 0x50) = 0;
    *(uint64_t *)(((long)0) + 0x58) = 0;
    *(uint64_t *)(((long)0) + 0x60) = 0;
    *(uint64_t *)(((long)0) + 0x68) = 0;
    *(uint64_t *)(((long)0) + 0x70) = 0;
    *(uint64_t *)(((long)0) + 0x78) = 0;
    FUN_003540d0();
    FUN_004593ac();
}

/* FUN_0049eac8 @ 0x0049eac8
 * Ghidra: void FUN_0049eac8(void)
 * Swap the metadata slot value at the pointer from FUN_004ab2dc with the new
 * value, releasing the old (tag-masked) and retaining the new (tag-masked).
 * Confidence: medium. */
void FUN_0049eac8(void)
{
    uint64_t *slot;
    uint64_t  old;
    uint64_t  newv;

    slot = (uint64_t *)FUN_004ab2dc();
    old = *slot;
    newv = 0;                /* extraout_x8: new value (unrecovered) */
    *slot = newv;
    FUN_0036b270(newv & 0xfffffffffffffff);
    FUN_0036b118(old & 0xfffffffffffffff);
}

/* FUN_0049eb04 @ 0x0049eb04
 * Ghidra: void FUN_0049eb04(void)
 * Swap the metadata slot value, releasing only the old (tag-masked) value.
 * Confidence: medium. */
void FUN_0049eb04(void)
{
    uint64_t *slot;
    uint64_t  old;
    uint64_t  newv;

    slot = (uint64_t *)FUN_004ab2dc();
    old = *slot;
    newv = 0;                /* extraout_x8 */
    *slot = newv;
    FUN_0036b118(old & 0xfffffffffffffff);
}

/* FUN_0049eb44 @ 0x0049eb44
 * Ghidra: void FUN_0049eb44(void)
 * Copy a metadata object's 4 owned words (+0x10..+0x28) and the +0x30/+0x38
 * words into x20, after the runtime steps FUN_003504d0, FUN_004ab600,
 * FUN_0034be0c and FUN_004588cc. Confidence: medium. */
void FUN_0049eb44(void)
{
    uint64_t w10, w18, w20, w28;
    uint64_t w30, w38;

    FUN_003504d0();
    FUN_004ab600();
    w10 = 0; w18 = 0; w20 = 0; w28 = 0;   /* extraout_x1 source words */
    FUN_0034be0c(w10);
    FUN_004588cc();
    *(uint64_t *)(((long)0) + 0x10) = w10;
    *(uint64_t *)(((long)0) + 0x18) = w18;
    *(uint64_t *)(((long)0) + 0x20) = w20;
    *(uint64_t *)(((long)0) + 0x28) = w28;
    w30 = 0; w38 = 0;
    *(uint64_t *)(((long)0) + 0x38) = w38;
    *(uint64_t *)(((long)0) + 0x30) = w30;
}

/* FUN_0049eba0 @ 0x0049eba0
 * Ghidra: void FUN_0049eba0(void)
 * Rebuild a metadata object at x20 from the FUN_0034b264 context: copy the
 * 4 owned words, dispatch the old 4 through FUN_00458940, and copy the
 * +0x30/+0x38 words. Confidence: medium. */
void FUN_0049eba0(void)
{
    cl4_pair_t meta;
    uint64_t   w10, w18, w20, w28;
    uint64_t   old10, old18, old20, old28;

    meta = FUN_0034b264();
    *(uint64_t *)(meta.lo + 8) = *(uint64_t *)(meta.hi + 8);
    w10 = 0; w18 = 0; w20 = 0; w28 = 0;    /* extraout source words */
    FUN_0034be0c(w10);
    FUN_004588cc();
    old10 = 0; old18 = 0; old20 = 0; old28 = 0;
    *(uint64_t *)(((long)0) + 0x10) = w10;
    *(uint64_t *)(((long)0) + 0x18) = w18;
    *(uint64_t *)(((long)0) + 0x20) = w20;
    *(uint64_t *)(((long)0) + 0x28) = w28;
    FUN_00458940(old10, old18, old20, old28);
    *(uint64_t *)(((long)0) + 0x30) = 0;
    *(uint64_t *)(((long)0) + 0x38) = 0;
}

/* FUN_0049ec14 @ 0x0049ec14
 * Ghidra: void FUN_0049ec14(void)
 * Swap a 4-word metadata struct at x20 with the one at x19, dispatch the
 * swapped words through FUN_004ac87c and FUN_00458940, then copy the +0x14
 * word. Confidence: medium. */
void FUN_0049ec14(void)
{
    uint64_t old[4];
    uint64_t src[4];
    int      i;

    FUN_003504d0();
    for (i = 0; i < 4; i++) src[i] = ((uint64_t*)0)[i];
    for (i = 0; i < 4; i++) { old[i] = ((uint64_t*)0)[i]; ((uint64_t*)0)[i] = src[i]; }
    FUN_004ac87c(0, old[3], ((uint64_t*)0)[4], ((uint64_t*)0)[5]);
    FUN_00458940();
    ((uint64_t*)0)[6] = 0;
    ((uint64_t*)0)[7] = 0;
}

/* FUN_0049ec7c @ 0x0049ec7c
 * Ghidra: void FUN_0049ec7c(void)
 * Rebuild a 5-word metadata struct at x20: run FUN_00084220/FUN_003504d0,
 * retain the 5 source words via FUN_0034be0c + FUN_0045a1f8, store them, run
 * FUN_004ab868, and restore via FUN_00084234. Confidence: medium. */
void FUN_0049ec7c(void)
{
    uint64_t w[4];
    uint8_t  flag;
    uint64_t v;
    int      i;

    FUN_00084220();
    FUN_003504d0();
    for (i = 0; i < 4; i++) w[i] = 0;      /* extraout_x1 words */
    flag = 0;
    FUN_0034be0c(w[0]);
    FUN_0045a1f8();
    for (i = 0; i < 4; i++) ((uint64_t*)0)[i] = w[i];
    *(uint8_t *)(((long)0) + 4) = flag;
    v = FUN_004ab868();
    FUN_00084234(v, 0);
}

/* FUN_0049ecd8 @ 0x0049ecd8
 * Ghidra: void FUN_0049ecd8(void)
 * Rebuild a larger metadata struct at x20 from the runtime context: run
 * FUN_00084220/FUN_003504d0, retain the 5 source words, dispatch the old 5
 * via FUN_004592dc, copy the 5+7 words from x19, restore via FUN_00084234.
 * Confidence: medium. */
void FUN_0049ecd8(void)
{
    uint64_t w[4];
    uint8_t  flag;
    uint64_t old[5];
    uint8_t  oldflag;
    int      i;

    FUN_00084220();
    FUN_003504d0();
    for (i = 0; i < 4; i++) w[i] = 0;
    flag = 0;
    FUN_0034be0c(w[0]);
    FUN_0045a1f8();
    for (i = 0; i < 4; i++) { old[i] = ((uint64_t*)0)[i]; ((uint64_t*)0)[i] = w[i]; }
    oldflag = *(uint8_t *)(((long)0) + 4);
    *(uint8_t *)(((long)0) + 4) = flag;
    FUN_004592dc(old[0], old[1], old[2], old[3], oldflag);
    for (i = 0; i < 4; i++) ((uint64_t*)0)[5 + i] = ((uint64_t*)0)[0x28 + i];
    ((uint64_t*)0)[9] = 0;
    ((uint64_t*)0)[10] = 0;
    ((uint64_t*)0)[11] = 0;
    FUN_00084234();
}

/* FUN_0049ed6c @ 0x0049ed6c
 * Ghidra: void FUN_0049ed6c(void)
 * Swap a 5-word metadata struct at x20 with x19, dispatch the old 5 via
 * FUN_004592dc, run FUN_004ab868. Confidence: medium. */
void FUN_0049ed6c(void)
{
    cl4_pair_t meta;
    uint8_t    newflag;
    uint8_t    oldflag;
    uint64_t   old[5];
    uint64_t   w[5];
    int        i;

    meta = FUN_003504d0();
    newflag = *(uint8_t *)(meta.hi + 0x20);
    for (i = 0; i < 4; i++) { old[i] = ((uint64_t*)0)[i]; ((uint64_t*)0)[i] = ((uint64_t*)0)[i]; }
    oldflag = *(uint8_t *)(((long)0) + 4);
    *(uint8_t *)(((long)0) + 4) = newflag;
    FUN_004592dc(meta.lo, old[1], old[2], old[3], oldflag);
    FUN_004ab868();
}

/* FUN_0049ee1c @ 0x0049ee1c
 * Ghidra: long FUN_0049ee1c(long param_1)
 * Copy a metadata object's +0x18..+0x38 words into param_1 from the source
 * (extraout_x1), retaining the new and releasing the old. Returns param_1.
 * Confidence: medium. */
long FUN_0049ee1c(long param_1)
{
    uint64_t w18, w20, w28, w30, w38;

    FUN_004ab150();
    w18 = 0; w20 = 0; w28 = 0; w30 = 0; w38 = 0;   /* extraout_x1 words */
    *(uint64_t *)(param_1 + 0x18) = w18;
    *(uint64_t *)(param_1 + 0x28) = w28;
    *(uint64_t *)(param_1 + 0x20) = w20;
    *(uint8_t *)(param_1 + 0x30) = (uint8_t)w30;
    *(uint64_t *)(param_1 + 0x38) = w38;
    FUN_0036b270();
    FUN_0036b270(w38);
    return param_1;
}

/* FUN_0049ee70 @ 0x0049ee70
 * Ghidra: void FUN_0049ee70(void)
 * Rebuild a metadata object at x20 from the FUN_003504d0 context: allocate
 * and copy the head pair via FUN_004ab9a4, swap +0x18 (release old), copy
 * the +0x20/+0x28/+0x30 words and +0x38 (release old). Confidence: medium. */
void FUN_0049ee70(void)
{
    uint64_t *head;
    uint64_t  old18;
    uint64_t  old38;

    FUN_003504d0();
    head = (uint64_t *)FUN_004ab9a4(0);
    head[1] = 0;
    head[0] = 0;
    old18 = *(uint64_t *)(((long)0) + 0x18);
    *(uint64_t *)(((long)0) + 0x18) = 0;
    FUN_0036b270();
    FUN_0036b118(old18);
    *(uint8_t *)(((long)0) + 0x30) = 0;
    *(uint64_t *)(((long)0) + 0x28) = 0;
    *(uint64_t *)(((long)0) + 0x20) = 0;
    old38 = *(uint64_t *)(((long)0) + 0x38);
    *(uint64_t *)(((long)0) + 0x38) = 0;
    FUN_0036b270();
    FUN_0036b118(old38);
}
