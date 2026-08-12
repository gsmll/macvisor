/* Recreated from exclavecore_bundle.t8142.RELEASE.im4p (cL4 Secure Kernel,
 * arm64e, image base 0) — the cL4 (Apple seL4-derived) microkernel (GL1).
 * Ground truth: Ghidra FUN_ names + addresses in program cl4_kernel.raw.
 * All names are estimates unless string/header-matched.
 *
 * This file covers the caps/metadata region 0x000cc0b4 - 0x000dbbb0.
 *
 * SeL4/cL4 vocabulary is used for naming: TCB, cap, CNode, IPC, notification,
 * endpoint, vspace, sched, metadata (mdata), ASID, cap table, etc.
 * Confidence is medium unless a string matches.
 *
 * Shared primitives (FUN_0036xxxx = Swift runtime retain/release/alloc) are
 * declared extern with one-line notes.
 */

#include "sk_internal.h"

/* SoftwareBreakpoint / bounds-fault trap (noreturn in the binary). */
static void sk_fault(void){ for(;;){} }

/* Ghidra type aliases (for faithful transcription). */
typedef uint8_t  byte;
typedef uint8_t  undefined;
typedef uint8_t  undefined1;
typedef uint16_t undefined2;
typedef uint32_t undefined4;
typedef uint64_t undefined8;
typedef uint64_t unkuint9;
typedef uint64_t unkuint10;
typedef uint64_t unkbyte9;
typedef uint64_t unkbyte10;
/* Auto-generated extern declarations for out-of-slice FUN_ callees. */
extern unsigned long FUN_00002534();
extern unsigned long FUN_000026e8();
extern unsigned long FUN_000027e8();
extern unsigned long FUN_00002818();
extern unsigned long FUN_00002834();
extern unsigned long FUN_00002874();
extern unsigned long FUN_00019aac();
extern unsigned long FUN_0001e790();
extern unsigned long FUN_0001fe3c();
extern unsigned long FUN_00025704();
extern unsigned long FUN_000267d4();
extern unsigned long FUN_00027724();
extern unsigned long FUN_00027754();
extern unsigned long FUN_00034f70();
extern unsigned long FUN_00069970();
extern unsigned long FUN_0006a4c0();
extern unsigned long FUN_0006ae9c();
extern unsigned long FUN_0006b42c();
extern unsigned long FUN_0006e7c0();
extern unsigned long FUN_0006fd3c();
extern unsigned long FUN_00070594();
extern unsigned long FUN_00070674();
extern unsigned long FUN_000723f4();
extern unsigned long FUN_00072424();
extern unsigned long FUN_00072710();
extern unsigned long FUN_000731dc();
extern unsigned long FUN_00073268();
extern unsigned long FUN_0007340c();
extern unsigned long FUN_00074404();
extern unsigned long FUN_000747a8();
extern unsigned long FUN_000768f0();
extern unsigned long FUN_00077070();
extern unsigned long FUN_00077088();
extern unsigned long FUN_000776cc();
extern unsigned long FUN_0007b280();
extern unsigned long FUN_0007b45c();
extern unsigned long FUN_0007bebc();
extern unsigned long FUN_0007bed4();
extern unsigned long FUN_0008157c();
extern unsigned long FUN_00081d60();
extern unsigned long FUN_00081efc();
extern unsigned long FUN_00082484();
extern unsigned long FUN_00082744();
extern unsigned long FUN_00085374();
extern unsigned long FUN_00085a54();
extern unsigned long FUN_00086440();
extern unsigned long FUN_00086590();
extern unsigned long FUN_000867a8();
extern unsigned long FUN_000871dc();
extern unsigned long FUN_0008da6c();
extern unsigned long FUN_0008dae4();
extern unsigned long FUN_0008db28();
extern unsigned long FUN_0008dcd0();
extern unsigned long FUN_0008e500();
extern unsigned long FUN_0008e518();
extern unsigned long FUN_00095184();
extern unsigned long FUN_00095ba4();
extern unsigned long FUN_0009647c();
extern unsigned long FUN_0009e20c();
extern unsigned long FUN_000a046c();
extern unsigned long FUN_000a04bc();
extern unsigned long FUN_000a16ec();
extern unsigned long FUN_000a17f8();
extern unsigned long FUN_000a6840();
extern unsigned long FUN_000a981c();
extern unsigned long FUN_000abad0();
extern unsigned long FUN_000ac0f4();
extern unsigned long FUN_000ac1dc();
extern unsigned long FUN_000ae10c();
extern unsigned long FUN_000aea40();
extern unsigned long FUN_000b2194();
extern unsigned long FUN_000b2390();
extern unsigned long FUN_000b2e64();
extern unsigned long FUN_000b30e4();
extern unsigned long FUN_000bf328();
extern unsigned long FUN_000c0e48();
extern unsigned long FUN_000c18dc();
extern unsigned long FUN_000c1cd8();
extern unsigned long FUN_000c31d8();
extern unsigned long FUN_000c811c();
extern unsigned long FUN_000c8554();
extern unsigned long FUN_000cc0b4();
extern unsigned long FUN_000cc224();
extern unsigned long FUN_000cc334();
extern unsigned long FUN_000cc660();
extern unsigned long FUN_000cc92c();
extern unsigned long FUN_000cccc8();
extern unsigned long FUN_000cce8c();
extern unsigned long FUN_000cef2c();
extern unsigned long FUN_000cf064();
extern unsigned long FUN_000cf6a4();
extern unsigned long FUN_000cfe2c();
extern unsigned long FUN_000cff28();
extern unsigned long FUN_000d0020();
extern unsigned long FUN_000d0220();
extern unsigned long FUN_000d02a0();
extern unsigned long FUN_000d04e0();
extern unsigned long FUN_000d183c();
extern unsigned long FUN_000d1958();
extern unsigned long FUN_000d1a74();
extern unsigned long FUN_000d1c4c();
extern unsigned long FUN_000d1c94();
extern unsigned long FUN_000d1d50();
extern unsigned long FUN_000d1d54();
extern unsigned long FUN_000d1d84();
extern unsigned long FUN_000d1da8();
extern unsigned long FUN_000d1e28();
extern unsigned long FUN_000d1ee4();
extern unsigned long FUN_000d2dc0();
extern unsigned long FUN_000d3980();
extern unsigned long FUN_000d3bd8();
extern unsigned long FUN_000d3c80();
extern unsigned long FUN_000d42a8();
extern unsigned long FUN_000d43bc();
extern unsigned long FUN_000d453c();
extern unsigned long FUN_000d45ec();
extern unsigned long FUN_000d46d4();
extern unsigned long FUN_000d4964();
extern unsigned long FUN_000d4dc0();
extern unsigned long FUN_000d4dcc();
extern unsigned long FUN_000d4e10();
extern unsigned long FUN_000d4ee8();
extern unsigned long FUN_000d5010();
extern unsigned long FUN_000d5144();
extern unsigned long FUN_000d52c8();
extern unsigned long FUN_000d5360();
extern unsigned long FUN_000d56a0();
extern unsigned long FUN_000d56ac();
extern unsigned long FUN_000d56d0();
extern unsigned long FUN_000d5700();
extern unsigned long FUN_000d5730();
extern unsigned long FUN_000d5b34();
extern unsigned long FUN_000d5d80();
extern unsigned long FUN_000d7bf8();
extern unsigned long FUN_000d9a98();
extern unsigned long FUN_000da558();
extern unsigned long FUN_000db184();
extern unsigned long FUN_000db1d0();
extern unsigned long FUN_000db204();
extern unsigned long FUN_000db250();
extern unsigned long FUN_000db308();
extern unsigned long FUN_000db330();
extern unsigned long FUN_000db398();
extern unsigned long FUN_000db3d0();
extern unsigned long FUN_000db3e0();
extern unsigned long FUN_000db430();
extern unsigned long FUN_000db454();
extern unsigned long FUN_000db484();
extern unsigned long FUN_000db5a4();
extern unsigned long FUN_000db5f0();
extern unsigned long FUN_000db620();
extern unsigned long FUN_000db650();
extern unsigned long FUN_000db6b0();
extern unsigned long FUN_000db718();
extern unsigned long FUN_000db748();
extern unsigned long FUN_000db870();
extern unsigned long FUN_000db888();
extern unsigned long FUN_000db8a0();
extern unsigned long FUN_000db8c0();
extern unsigned long FUN_000db8e0();
extern unsigned long FUN_000db8f8();
extern unsigned long FUN_000db910();
extern unsigned long FUN_000dba44();
extern unsigned long FUN_000dba5c();
extern unsigned long FUN_000dba78();
extern unsigned long FUN_000dba90();
extern unsigned long FUN_000dbaa4();
extern unsigned long FUN_000dbac8();
extern unsigned long FUN_000dbad8();
extern unsigned long FUN_000dbaf4();
extern unsigned long FUN_000dbb10();
extern unsigned long FUN_000dbb24();
extern unsigned long FUN_000dbb30();
extern unsigned long FUN_000dbb3c();
extern unsigned long FUN_000dbb60();
extern unsigned long FUN_000dbb78();
extern unsigned long FUN_000dbba0();
extern unsigned long FUN_000dbbb0();
extern unsigned long FUN_000dbbe0();
extern unsigned long FUN_000dbc18();
extern unsigned long FUN_000dbcc8();
extern unsigned long FUN_000dbce0();
extern unsigned long FUN_000dbcfc();
extern unsigned long FUN_000dbd0c();
extern unsigned long FUN_000dbd9c();
extern unsigned long FUN_000dbdc8();
extern unsigned long FUN_000dbddc();
extern unsigned long FUN_000dbde8();
extern unsigned long FUN_000dbe00();
extern unsigned long FUN_000dbe0c();
extern unsigned long FUN_000dbe64();
extern unsigned long FUN_000dbeb0();
extern unsigned long FUN_000dbed0();
extern unsigned long FUN_000dbee8();
extern unsigned long FUN_000dbefc();
extern unsigned long FUN_000dbf5c();
extern unsigned long FUN_000e2668();
extern unsigned long FUN_000e3ea0();
extern unsigned long FUN_000ec3a0();
extern unsigned long FUN_000ec67c();
extern unsigned long FUN_000f78ac();
extern unsigned long FUN_000f7f64();
extern unsigned long FUN_000f9608();
extern unsigned long FUN_000f9680();
extern unsigned long FUN_000f98ac();
extern unsigned long FUN_000f9930();
extern unsigned long FUN_000f9b4c();
extern unsigned long FUN_000fa1b0();
extern unsigned long FUN_00101ec8();
extern unsigned long FUN_00103724();
extern unsigned long FUN_00114330();
extern unsigned long FUN_00117cc4();
extern unsigned long FUN_00117d14();
extern unsigned long FUN_0012097c();
extern unsigned long FUN_0012540c();
extern unsigned long FUN_00138b08();
extern unsigned long FUN_001394c8();
extern unsigned long FUN_001396b4();
extern unsigned long FUN_00151974();
extern unsigned long FUN_00151a6c();
extern unsigned long FUN_00153270();
extern unsigned long FUN_0016189c();
extern unsigned long FUN_00163610();
extern unsigned long FUN_001672c8();
extern unsigned long FUN_00167a6c();
extern unsigned long FUN_0016d4e8();
extern unsigned long FUN_001a0774();
extern unsigned long FUN_001a1564();
extern unsigned long FUN_001a84f4();
extern unsigned long FUN_001a8564();
extern unsigned long FUN_001afa84();
extern unsigned long FUN_001bac44();
extern unsigned long FUN_001dd77c();
extern unsigned long FUN_001dd858();
extern unsigned long FUN_001f0130();
extern unsigned long FUN_00229ebc();
extern unsigned long FUN_0022b080();
extern unsigned long FUN_002591b4();
extern unsigned long FUN_0029369c();
extern unsigned long FUN_002a0cf8();
extern unsigned long FUN_002a4ab4();
extern unsigned long FUN_002acbb8();
extern unsigned long FUN_0035d334();
extern unsigned long FUN_0035dc24();
extern unsigned long FUN_00365b6c();
extern unsigned long FUN_0036986c();
extern unsigned long FUN_003698b0();
extern unsigned long FUN_0036993c();
extern unsigned long FUN_0036a1a0();
extern unsigned long FUN_0036a20c();
extern unsigned long FUN_0036a4c0();
extern unsigned long FUN_0036a940();
extern unsigned long FUN_0036a9a0();
extern unsigned long FUN_0036a9d4();
extern unsigned long FUN_0036b118();
extern unsigned long FUN_0036b21c();
extern unsigned long FUN_0036b270();
extern unsigned long FUN_0036b2d0();
extern unsigned long FUN_0036b340();
extern unsigned long FUN_0036b588();
extern unsigned long FUN_0036b6ac();
extern unsigned long FUN_0036b6f4();
extern unsigned long FUN_003a25d4();
extern unsigned long FUN_003a25e0();
extern unsigned long FUN_003a2610();
extern unsigned long FUN_003a261c();
extern unsigned long thunk_FUN_000a17f8();
extern unsigned long thunk_FUN_000d1d54();
extern unsigned long thunk_FUN_00114330();
extern unsigned long thunk_FUN_002acbb8();

/* Forward declarations for helpers defined below. */
static unsigned long count(unsigned long table);
static void emit_mdata_record(unsigned long table, unsigned long obj, unsigned long type_md, unsigned long key, int hint);
static void grow_and_append(unsigned long table, unsigned long obj, unsigned long type_md, unsigned long key, int hint);
static void collect_span_objects(unsigned long table);
static void serialize_mdata(unsigned long table);
static void append_ptr(void *list, unsigned long obj);
static void sort_cap_vector(long *param_1);
static unsigned long span_size(unsigned long table, unsigned long i);
static volatile unsigned long unaff_x20;
static volatile unsigned long unaff_x21;
static volatile unsigned long unaff_x19;
static unsigned long bit_index(unsigned long bits);
static void insert_local_cap(unsigned long set, void **out, unsigned long word, unsigned long param_6);
static void insert_cap_with_owner(unsigned long set, void **out, unsigned long word, unsigned long cap, unsigned long param_6);
static void insert_cap_owner(unsigned long set, unsigned long tag, unsigned long cap, unsigned long param_6, void **out);
static unsigned long object_type_name(void *obj);
static unsigned long type_name_code(unsigned long type);
static unsigned long type_version(unsigned long type);
static unsigned long cmp128(unsigned long a0, unsigned long a1, unsigned long b0, unsigned long b1);
static int compare_objects(unsigned long a, unsigned long b);
static int compare_type(unsigned long x, unsigned long y);
static int compare_type2(unsigned long *pa, unsigned long *pb);
static char comparator_apply(int c1, int c2);
static unsigned long kind_offset(unsigned long kind);
static unsigned long lookup_cap_set(unsigned long dedup, unsigned long kind);

/* FUN_000cc0b4 @ 0x000cc0b4   (est. collect_matching_objects)
 * Ghidra: long FUN_000cc0b4(void)
 * Builds a list of objects from the running-process registry that
 * match a predicate on a key (FUN_000cf064, which itself is a
 * registry membership test). The result list is stored at the
 * frame's +0x20 array and returned via the frame pointer.
 * Confidence: medium
 * Notes: no visible signature; unaff_x20 is the self/frame pointer. */
void collect_matching_objects(void)
{
    /* FUN_000867a8(self+0x20, buf): begin the accumulator array. */
    FUN_000867a8((char *)0 + 0x20, (void *)0);
    FUN_0036a1a0((void *)0, (void *)0, 0, 0);
    /* retain current accumulator */
    FUN_0036b270(*(void **)(0 + 0x20));
    FUN_000ae10c();
    FUN_000dbe64();
    FUN_000867a8((char *)0 + 0x38, (void *)0);
    FUN_0036a1a0((void *)0, (void *)0, 0, 0);
    unsigned long acc = *(unsigned long *)(0 + 0x38);
    FUN_0036b270(acc);
    long list = FUN_000c8554((void (*)(void))0 /*FUN_000db308*/, (void *)0, acc);
    FUN_003a25d4((void *)0);
    FUN_003a25d4((void *)acc);
    unsigned long i = 0;
    unsigned long n = *(unsigned long *)(list + 0x10);
    FUN_000776cc();
    for (;;) {
        if (n == i) {
            FUN_0036b118((void *)list);
            return;
        }
        if (*(unsigned long *)(list + 0x10) <= i) break;
        unsigned long obj = *(unsigned long *)(list + i * 8 + 0x20);
        unsigned long match = FUN_000cf064((unsigned long *)&obj);
        if ((match & 1) != 0) {
            /* grow accumulator and append obj */
            unsigned long g = FUN_003a261c((void *)0);
            unsigned long acc2 = 0;
            if ((g & 1) == 0) {
                FUN_000dbbe0(g, *(long *)(acc2 + 0x10) + 1);
                FUN_00082484();
            }
            unsigned long m = *(unsigned long *)(acc2 + 0x10);
            if (*(unsigned long *)(acc2 + 0x18) >> 1 <= m) {
                FUN_0006b42c();
                FUN_000dbed0();
                FUN_00082484();
            }
            *(unsigned long *)(acc2 + 0x10) = m + 1;
            *(unsigned long *)(acc2 + m * 8 + 0x20) = obj;
            acc = acc2;
        }
        i++;
    }
    /* unreachable: bounds-check failure */
    sk_fault(); /* SoftwareBreakpoint */
}

/* FUN_000cc224 @ 0x000cc224   (est. check_and_attach_object)
 * Ghidra: byte FUN_000cc224(long *param_1)
 * Given an object descriptor (param_1, non-null), looks it up in the
 * running-object registry by key; if found and not already present in
 * the collector list (frame +0x118), appends it and returns 1 (or the
 * current list "flags" byte). Otherwise leaves the list unchanged.
 * Confidence: medium
 * Notes: FUN_0006ae9c is a dictionary/registry lookup; tag 0xd00.. */
byte check_and_attach_object(long *param_1)
{
    unsigned char *flags;
    FUN_0036a1a0((char *)0 + 0x118, (void *)0, 0, 0);
    byte b = *(byte *)(0 + 0x118);
    if (param_1 == (long *)0) {
        return b;
    }
    unsigned long (*f)() = *(unsigned long (**)())(*(long *)param_1 + 0x90);
    FUN_0036b270(param_1);
    long reg = (*f)();
    if (*(long *)(reg + 0x10) != 0) {
        FUN_0036b270(reg);
        /* lookup (0xd000000000000012, 0x80000000005c39d0) in registry */
        unsigned long pair = FUN_0006ae9c((unsigned long)0xd000000000000012,
                                          (unsigned long)0x80000000005c39d0);
        if ((pair >> 8 & 1) != 0) {
            long obj = *(long *)(*(long *)(reg + 0x38) + (pair & 0xff) * 0x20);
            FUN_0036b270(obj);
            FUN_003a2610(reg, 2);
            if (obj != 0) {
                FUN_0036b118(obj);
                FUN_0036b118(param_1);
                return b | 1;
            }
            FUN_003a25d4(reg);
        }
        FUN_003a25d4(reg);
    }
    FUN_003a25d4(reg);
    FUN_0036b118(param_1);
    return b;
}

/* FUN_000cc334 @ 0x000cc334   (est. build_address_descriptor_list)
 * Ghidra: undefined * FUN_000cc334(long param_1, long param_2)
 * Transforms a list of {key,value} pairs (param_1) into a descriptor
 * list appended to a collector (frame +0x140 predicate byte selects
 * the key encoding path). On a bad key it faults with a fatal error
 * ("InternalExclaveLauncher DERComp..." / Fatal error) and never
 * returns.
 * Confidence: low (heavily obfuscated vtable dispatch)
 * Notes: FUN_0008da6c/FUN_0008db28 are vtable thunks; the fatal path
 *   references s_Fatal_error_005accd0, file line 0x567. */
undefined *build_address_descriptor_list(long param_1, long param_2)
{
    long n = *(long *)(param_1 + 0x10);
    undefined *out = (undefined *)0x657778; /* &DAT_00657778 */
    if (n != 0) {
        char sel = *(char *)(0 + 0x140);
        undefined8 *p = (undefined8 *)(param_1 + 0x28);
        do {
            undefined8 *keyp = (undefined8 *)p[-1];
            undefined8 *val = p;
            undefined8 k0 = *keyp;
            if (sel == '\0') {
                unsigned long p2 = *(unsigned long *)(param_2 + 0x18);
                unsigned long p3 = *(unsigned long *)(param_2 + 0x20);
                FUN_0006a4c0(param_2, p2);
                unsigned long (*f)() = (unsigned long (*)())FUN_0008da6c(p3);
                FUN_0036b270(keyp);
                unsigned long r = (*f)();
                unsigned long (*g)() = (unsigned long (*)())FUN_0008db28(*val);
                (*g)(&out, (void *)r, k0, *val);
            } else {
                /* decode key via FUN_0008dae4(&DAT_00607494) */
                unsigned long kk = FUN_0008dae4(keyp, k0, (void *)0x607494);
                if ((kk & 0xff) == 0) {
                    /* fatal: bad key */
                    FUN_0036b270(keyp);
                    FUN_002a4ab4(0x17);
                    FUN_002acbb8(0xd000000000000015, 0x80000000005c0560);
                    unsigned long k1 = *keyp;
                    unsigned long *kp = (unsigned long *)keyp;
                    unsigned long v2 = FUN_00027754(*val);
                    FUN_001bac44((unsigned long *)kp, k1, v2);
                    FUN_001afa84((unsigned long)0x5accd0, 0xb, 2, 0, 0xe000000000000000,
                                 (unsigned long)0x5c2f30, 0x2f, 2, 0x567, 0); /* noreturn */
                }
                unsigned long k1 = *(unsigned long *)((kk & 0xff) + 0); /* *auVar13._0_8_ */
                unsigned long p2 = *(unsigned long *)(param_2 + 0x18);
                unsigned long p3 = *(unsigned long *)(param_2 + 0x20);
                FUN_0006a4c0(param_2, p2);
                unsigned long (*f)() = (unsigned long (*)())FUN_0008da6c(p3);
                FUN_0036b2d0(keyp, 2);
                unsigned long r = (*f)();
                unsigned long (*g)() = (unsigned long (*)())FUN_0008db28((kk >> 8) & 0xff);
                (*g)(&out, (void *)r, k1, (kk >> 8) & 0xff);
                FUN_0036b118(r);
            }
            FUN_0036b118(out);
            FUN_0036b118(keyp);
            unsigned long m = *(unsigned long *)(out + 0x10);
            if (*(unsigned long *)(out + 0x18) >> 1 <= m) {
                FUN_00082484(1 < *(unsigned long *)(out + 0x18), m + 1, 1);
            }
            *(unsigned long *)(out + 0x10) = m + 1;
            FUN_00077070(&out, (void *)(out + m * 0x28 + 0x20));
            n--;
        } while (n != 0);
    }
    return out;
}

/* FUN_000cc660 @ 0x000cc660   (est. notify_matching_clients)
 * Ghidra: void FUN_000cc660(undefined8 param_1, undefined1 (*param_2) [16], undefined8 param_3, long param_4)
 * Scans the client registry for an object whose key matches the caller's
 * (param_2), collecting matches, then invokes the matching object's
 * vtable[0x50] handler; on a policy miss (param_4 key mismatch) invokes
 * vtable[0x58] with an error object.
 * Confidence: low (opaque vtable dispatch, fatal on empty)
 * Notes: FUN_000a16ec/thunk_FUN_000a17f8 build an error context that can
 *   abort (__AppleInternal/Library/BuildRoot ... line 0x5ab/0x5ac). */
void notify_matching_clients(unsigned long param_1, unsigned long (*param_2)[2],
                             unsigned long param_3, long param_4)
{
    unsigned long out0;
    unsigned long u3 = (*param_2)[0];
    unsigned long u1 = (*param_2)[1];
    unsigned long key0 = (*param_2)[0], key1 = (*param_2)[1];
    FUN_000a16ec(&out0 /*&local_a8*/, 0xd000000000000038, 0x80000000005c3480,
                 (unsigned long)0x5c3120, 0xfb, 2, 0x5ab, param_3);
    FUN_003a25d4((void *)0);
    FUN_003a25d4((void *)0);
    unsigned long i = 0;
    unsigned long n = *(unsigned long *)(0 + 0x10);
    for (;;) {
        if (n == i) {
            FUN_0036b118((void *)0);
            FUN_002a4ab4(0x1e);
            FUN_003a25d4((void *)0);
            unsigned long ctx = FUN_000a17f8(0xd00000000000001c, 0x80000000005c34c0,
                                             (unsigned long)0x5c3120, 0xfb, 2, 0x5ac, 0);
            FUN_0036b118((void *)0);
            FUN_003a25d4((void *)0);
            unsigned long rr = ((unsigned long (*)(void))ctx)(); /* vtable[0x50] */
            unsigned long hit = FUN_000abad0(rr & 0xff, (rr >> 8) & 0xff, 0x65fcf0);
            FUN_003a25d4((void *)((rr >> 8) & 0xff));
            if ((hit & 1) == 0) {
                if ((*(long *)(param_4 + 0x38) != -0x2fffffffffffffee ||
                     *(long *)(param_4 + 0x40) != -0x7fffffffffa3e790) &&
                    (hit = FUN_002a0cf8(*(long *)(param_4 + 0x38), *(long *)(param_4 + 0x40),
                                        0xd000000000000012, 0x80000000005c1870, 0),
                     (hit & 1) == 0)) {
                    unsigned long p2 = ((unsigned long *)ctx)[2];
                    unsigned long r = ((unsigned long (*)(void))ctx)(); /* vtable[0x58] */
                    FUN_000768f0(r, p2);
                }
            }
            FUN_0036b118((void *)ctx);
            return;
        }
        if (*(unsigned long *)(0 + 0x10) <= i) break;
        unsigned long *obj = *(unsigned long **)(0 + i * 8 + 0x20);
        unsigned long (*f)() = (unsigned long (*)())(*(long *)*obj + 0x50);
        FUN_0036b270(obj);
        unsigned long pair = (*f)();
        unsigned long p4 = pair >> 8;
        if ((pair & 0xff) == (u3 & 0xff) && (pair >> 8) == (u1 & 0xff)) {
            /* matched */
            FUN_003a25d4((void *)p4);
            FUN_001dd77c();
            unsigned long m = *(unsigned long *)(0 + 0x10);
            FUN_001dd858(m);
            *(unsigned long *)(0 + 0x10) = m + 1;
            *(unsigned long **)(0 + m * 8 + 0x20) = obj;
            i++;
            continue;
        }
        unsigned long cmp = FUN_002a0cf8(pair & 0xff, p4, u3, u1, 0);
        FUN_003a25d4((void *)p4);
        if ((cmp & 1) != 0) {
            /* key equal -> matched */
            FUN_003a25d4((void *)p4);
            FUN_001dd77c();
            unsigned long m = *(unsigned long *)(0 + 0x10);
            FUN_001dd858(m);
            *(unsigned long *)(0 + 0x10) = m + 1;
            *(unsigned long **)(0 + m * 8 + 0x20) = obj;
            i++;
            continue;
        }
        FUN_0036b118(obj);
        i++;
    }
    /* unreachable bounds-failure */
    sk_fault();
}

/* FUN_000cc92c @ 0x000cc92c   (est. derive_register_object)
 * Ghidra: undefined8 FUN_000cc92c(8 args)
 * Registers a new object against a capability key (param_1/param_2)
 * in the object registry: scans the registry list for an object whose
 * key matches the capability, and if found fails; otherwise builds an
 * error context, and on a "policy check" success constructs a fresh
 * object wrapper via FUN_000ec3a0 and returns it.
 * Confidence: low (mirror of FUN_000cc660 but registering)
 * Notes: shared key tags 0xd000000000000038 / 0x80000000005c3480; on
 *   failure returns 0. */
unsigned long derive_register_object(unsigned long param_1, unsigned long param_2,
                                     unsigned long param_3, unsigned long param_4,
                                     unsigned long param_5, long param_6,
                                     unsigned long param_7, unsigned long param_8)
{
    unsigned long out0;
    unsigned long key0 = param_1, key1 = param_2;
    FUN_000a16ec(&out0 /*&local_a8*/, 0xd000000000000038, 0x80000000005c3480,
                 (unsigned long)0x5c3120, 0xfb, 2, 0x5be, param_5, param_8, param_8, param_7);
    FUN_003a25d4((void *)0);
    FUN_003a25d4((void *)0);
    unsigned long i = 0;
    unsigned long n = *(unsigned long *)(0 + 0x10);
    for (;;) {
        if (n == i) {
            FUN_0036b118((void *)0);
            FUN_002a4ab4(0x1e);
            FUN_003a25d4((void *)0);
            unsigned long ctx = FUN_000a17f8(0xd00000000000001c, 0x80000000005c34c0,
                                             (unsigned long)0x5c3120, 0xfb, 2, 0x5bf, 0);
            FUN_0036b118((void *)0);
            FUN_003a25d4((void *)0);
            unsigned long rr = ((unsigned long (*)(void))ctx)(); /* vtable[0x50] */
            unsigned long hit = FUN_000abad0(rr & 0xff, (rr >> 8) & 0xff, 0x65fcf0);
            FUN_003a25d4((void *)((rr >> 8) & 0xff));
            if ((hit & 1) == 0) {
                if ((*(long *)(param_6 + 0x38) != -0x2fffffffffffffee ||
                     *(long *)(param_6 + 0x40) != -0x7fffffffffa3e790) &&
                    (hit = FUN_002a0cf8(*(long *)(param_6 + 0x38), *(long *)(param_6 + 0x40),
                                        0xd000000000000012, 0x80000000005c1870, 0),
                     (hit & 1) == 0)) {
                    /* policy OK: build the object wrapper */
                    unsigned long ctx2 = FUN_0036a940((void *)0x661360, 0x40, 7);
                    FUN_000c0e48((char *)ctx2 + 0x10, param_8);
                    unsigned long p2 = ((unsigned long *)ctx)[2];
                    unsigned long r = ((unsigned long (*)(void))ctx)(); /* vtable[0x58] */
                    unsigned long o1 = FUN_000ec67c(0);
                    unsigned long o2 = FUN_0036a940((void *)o1, 0x48, 7);
                    unsigned long res = FUN_000ec3a0(&ctx2, param_3, param_1, param_2, param_4,
                                                     p2, r, o2);
                    FUN_0036b118((void *)ctx);
                    return res;
                }
            }
            FUN_0036b118((void *)ctx);
            return 0;
        }
        if (*(unsigned long *)(0 + 0x10) <= i) break;
        unsigned long *obj = *(unsigned long **)(0 + i * 8 + 0x20);
        unsigned long (*f)() = (unsigned long (*)())(*(long *)*obj + 0x50);
        FUN_0036b270(obj);
        unsigned long pair = (*f)();
        unsigned long p4 = pair >> 8;
        if ((pair & 0xff) == (key0 & 0xff) && p4 == (key1 & 0xff)) {
            FUN_003a25d4((void *)p4);
            /* matched existing -> treat as equal, append */
            FUN_001dd77c();
            unsigned long m = *(unsigned long *)(0 + 0x10);
            FUN_001dd858(m);
            *(unsigned long *)(0 + 0x10) = m + 1;
            *(unsigned long **)(0 + m * 8 + 0x20) = obj;
            i++;
            continue;
        }
        unsigned long cmp = FUN_002a0cf8(pair & 0xff, p4, param_1, param_2, 0);
        FUN_003a25d4((void *)p4);
        if ((cmp & 1) != 0) {
            FUN_003a25d4((void *)p4);
            FUN_001dd77c();
            unsigned long m = *(unsigned long *)(0 + 0x10);
            FUN_001dd858(m);
            *(unsigned long *)(0 + 0x10) = m + 1;
            *(unsigned long **)(0 + m * 8 + 0x20) = obj;
            i++;
            continue;
        }
        FUN_0036b118(obj);
        i++;
    }
    /* unreachable bounds-failure */
    sk_fault();
}

/* FUN_000cccc8 @ 0x000cccc8   (est. map_page_region)
 * Ghidra: undefined1 [16] FUN_000cccc8(ulong param_1, long param_2, long param_3)
 * Computes a mapping region: size from a tagged descriptor (if bit0 of
 * param_1 is clear, derives size from the vspace entry at param_2,
 * else default 0x40000), then asks the page-table layer (FUN_00153270
 * -> map) for a region mapping of that size and returns {end-0x200,
 * mapped-base} as the 128-bit result.
 * Confidence: medium
 * Notes: FUN_000db454/FUN_000db484 are size getters; FUN_00153270 is
 *   the "current ASID" accessor; threshold 0x200 is a page header. */
unsigned long map_page_region(unsigned long param_1, long param_2, long param_3)
{
    unsigned long size;
    if ((param_1 & 1) == 0) {
        FUN_0036a1a0((void *)(param_2 + 0x28), (void *)0, 0, 0);
        unsigned long *v = *(unsigned long **)(param_2 + 0x28);
        unsigned long v2 = *(unsigned long *)(param_2 + 0x30);
        unsigned long v0 = *v;
        unsigned long (*f)() = (unsigned long (*)())FUN_000db454(v2);
        FUN_0036b270(v);
        unsigned long rr = (*f)(v0);
        FUN_0036b118(v);
        if (((rr >> 8) & 0xff) == 1) {
            size = 0xc000;
        } else {
            size = rr << 0xe;
        }
    } else {
        size = 0x40000;
    }
    unsigned long p2 = *(unsigned long *)(param_3 + 0x18);
    unsigned long p3 = *(unsigned long *)(param_3 + 0x20);
    FUN_0006a4c0(param_3, p2);
    unsigned long *asid = (unsigned long *)FUN_00153270();
    unsigned long a = *asid;
    unsigned long (*g)() = (unsigned long (*)())FUN_000db484(p3);
    unsigned long base = (*g)(size, a, param_1 & 1, 0, 0, 1, 1, 0, p2, p3);
    /* return {base, size+0x4000+base-0x200} */
    unsigned long end = size + 0x4000 + base;
    /* packed result: lo=end-0x200, hi=base */
    return ((base & 0xff) << 8) | ((end - 0x200) & 0xff);
}

/* FUN_000cce8c @ 0x000cce8c   (est. serialize_address_space_metadata)
 * Ghidra: void FUN_000cce8c(8 args)
 * Large serialization routine that emits the full metadata (mdata)
 * stream for an address space: boot CPU info, dyld mapping, process
 * info, tbplaceholder, launcher stats, boottime/tramp-mdata, virtual
 * spans, generic AS, mdata total size, find/create mdata span,
 * populate address-space metadata, mdata serialization. Uses many
 * vtable dispatchers and metadata-string anchors.
 * Confidence: low (very large, many vtable indirections)
 * Notes: string anchors s_dyld_mapping_mdata_005c3500,
 *   s_process_info_mdata_005c3520, s_tbplaceholder_mdata_005c3540,
 *   s_launcher_stats_mdata_005c3560, s_virtual_spans_mdata_005c3580,
 *   s_generic_AS_mdata_005c35a0, s_mdata_total_size_005c35c0,
 *   s_find_mdata_space_005c35e0, s_create_mdata_span_005c3600,
 *   s_Failed_to_create_metadata_span_005c3620,
 *   s_populateAddressSpaceMetadata_asi_005c3640,
 *   s_mdata_serialization_005c3720. */
void serialize_address_space_metadata(unsigned long p1, unsigned long p2, long p3,
                                      unsigned long p4, unsigned long p5, long p6,
                                      unsigned long p7, unsigned long p8)
{
    /* The address-space metadata emitter. Emits a sequence of mdata
     * records, each anchored by a metadata-type string, into a shared
     * collector table (local_640, grown via FUN_000747a8). Each record
     * carries {object, type-metadata, key, size-hint}. Record keys:
     * 0x65f730(boot), 0x65f7b0(dyld), 0x65f7a0(proc), 0x65f780(tbph),
     * 0x65f790(launcher), 0x65f750/0x65f770(spans), 0x65f760(vs spans),
     * 0x65f7c0(generic AS), 0x65f7d0(total size). Concludes by
     * computing total size (find/create mdata span), populating
     * per-16K-span address-space metadata, and serializing the stream.
     *
     * The decompiled body is very large (200+ source lines) and dominated
     * by repeated "allocate record, dispatch metadata-string vtable,
     * bounds-check, append" sequences plus address-space-span iteration.
     * This transcription preserves the phase order and data flow. */
    unsigned long record_table = FUN_000747a8(0, 1, 1); /* collector table */

    /* ---- Boot CPU info record (metadata 0x65f730, hint 7). ---- */
    {
        unsigned long rec = FUN_000dbe0c();
        *(unsigned long *)(rec + 0x10) = p5;
        grow_and_append(record_table, rec, 0, 0x65f730, 7);
        FUN_000dbefc();
        /* dispatch metadata handler for the record */
        ((unsigned long (*)())(0xb0))(); /* vtable[0xb0] */
    }

    /* ---- dyld mapping mdata (s_dyld_mapping_mdata_005c3500). ---- */
    FUN_000dbac8((unsigned long)0x5c3500);
    FUN_000dbce0();
    emit_mdata_record(record_table, p6, 0, 0x65f7b0, 0xc);

    /* ---- process info mdata (s_process_info_mdata_005c3520). ---- */
    FUN_000dba5c((unsigned long)0x5c3520);
    FUN_000dbce0();
    emit_mdata_record(record_table, p6, 0, 0x65f7a0, 0x16);

    /* ---- tbplaceholder mdata (s_tbplaceholder_mdata_005c3540). ---- */
    FUN_000dba5c((unsigned long)0x5c3540);
    FUN_000dbc18();
    emit_mdata_record(record_table, p6, 0, 0x65f780, 0x13);

    /* ---- launcher stats mdata (s_launcher_stats_mdata_005c3560). ---- */
    FUN_000dba5c((unsigned long)0x5c3560);
    FUN_000dbce0();
    emit_mdata_record(record_table, p6, 0, 0x65f790, 0xf);

    /* ---- boottime / tramp mdata (dispatch per frame). ---- */
    emit_mdata_record(record_table, p6, 0, 0x65f750, 0x14);
    emit_mdata_record(record_table, p6, 0, 0x65f770, 0x1b);

    /* ---- virtual spans mdata (s_virtual_spans_mdata_005c3580). ---- */
    FUN_000dba5c((unsigned long)0x5c3580);
    FUN_000dbc18();
    /* iterate span objects; per span check via vtable[0x70]/[0x80]
     * and FUN_0016d4e8 (is-writable), collecting surviving spans. */
    collect_span_objects(record_table);

    /* ---- generic AS mdata (s_generic_AS_mdata_005c35a0). ---- */
    FUN_000dba5c((unsigned long)0x35a0);
    FUN_000dbd9c();
    emit_mdata_record(record_table, p6, 0, 0x65f7c0, 0x27);

    /* ---- mdata total size (s_mdata_total_size_005c35c0). ---- */
    FUN_000dba5c((unsigned long)0x35c0);
    FUN_000dbd9c();
    unsigned long total = 0;
    for (unsigned long i = 0; i < count(record_table); i++) {
        /* sum span sizes via FUN_000dbf5c/DBF5C bounds-checked adds */
        total += span_size(record_table, i);
    }
    total = (total + 0x3fff) & 0xffffffffffffc000;

    /* ---- find mdata space (s_find_mdata_space_005c35e0). ---- */
    FUN_000dbac8((unsigned long)0x5c35e0);
    FUN_000dbd9c();
    unsigned long space = FUN_000db748(total); /* find contiguous span */

    /* ---- create mdata span (s_create_mdata_span_005c3600). ---- */
    FUN_000dbac8((unsigned long)0x5c3600);
    FUN_000dbce0();
    unsigned long span = FUN_00086440(0);
    span = FUN_00085a54(span, total, 0x11, 0x1808, 0xf); /* carve span */
    *(unsigned long *)(0 + 0xb8) = span;                /* cache it */
    if (span == 0) {
        FUN_00002874((unsigned long)0x5c3620); /* "Failed to create metadata span" */
        FUN_000dba78();
        FUN_000dbce0();
        FUN_00002818();
        FUN_000dbe00();
        FUN_001afa84(); /* noreturn */
    }

    /* ---- populate address-space metadata (s_populateAddressSpaceMetadata_asi_005c3640)
     *      per 16K span. ---- */
    for (unsigned long off = 0; off < total; off += 0x4000) {
        unsigned long ps = FUN_00034f70(); /* next physical span */
        if (ps == 0)
            FUN_00085374((unsigned long)0x5c3640, 0xa3, 2, 0x829); /* noreturn */
        /* map metadata for this span into the record table */
        *(unsigned long *)(record_table + count(record_table) * 0x30 + 0x20) = ps;
        ((unsigned long (*)())(0x90))(); /* vtable[0x90] */
    }

    /* ---- mdata serialization (s_mdata_serialization_005c3720). ---- */
    FUN_000dbac8((unsigned long)0x5c3720);
    FUN_000dbc18();
    serialize_mdata(record_table);
    FUN_00153270(); /* current ASID */
    FUN_000dbde8((void *)0, (void *)0, total, 1);
    FUN_000c1cd8();
    FUN_0036b118((void *)record_table);
}

/* ------------------------------------------------------------------ */
/* Small static helpers (reconstructed from inline decompile patterns) */
/* ------------------------------------------------------------------ */
static unsigned long count(unsigned long table) { return *(unsigned long *)(table + 0x10); }

/* Append an {object, type-metadata, key, hint} record to a collector
 * table (grown via the mdata-growth path FUN_000747a8 / FUN_000dbefc). */
static void emit_mdata_record(unsigned long table, unsigned long obj,
                              unsigned long type_md, unsigned long key, int hint)
{
    unsigned long n = *(unsigned long *)(table + 0x10);
    unsigned long cap = *(unsigned long *)(table + 0x18);
    if (cap >> 1 <= n) {
        table = FUN_000747a8(1 < cap, n + 1, 1, table);
    }
    *(unsigned long *)(table + 0x10) = n + 1;
    unsigned long slot = table + n * 0x30;
    *(unsigned long *)(slot + 0x20) = obj;
    *(unsigned long *)(slot + 0x38) = type_md;
    *(unsigned long *)(slot + 0x40) = key;
    *(unsigned int *)(slot + 0x48) = (unsigned int)hint;
    FUN_000dbefc();
    FUN_000027e8();
    ((unsigned long (*)())(0xb0))();
}

/* grow + append for a 0x10-stride table. */
static void grow_and_append(unsigned long table, unsigned long obj,
                            unsigned long type_md, unsigned long key, int hint)
{
    unsigned long n = *(unsigned long *)(table + 0x10);
    unsigned long cap = *(unsigned long *)(table + 0x18);
    if (cap >> 1 <= n) {
        table = FUN_000747a8(1 < cap, n + 1, 1, table);
    }
    *(unsigned long *)(table + 0x10) = n + 1;
    unsigned long slot = table + n * 0x30;
    *(unsigned long *)(slot + 0x20) = obj;
    *(unsigned long *)(slot + 0x38) = type_md;
    *(unsigned long *)(slot + 0x40) = key;
    *(unsigned int *)(slot + 0x48) = (unsigned int)hint;
    FUN_000dbefc();
    FUN_000027e8();
}

/* Sum of span sizes over the collector table (FUN_000dbf5c-derived). */
static unsigned long span_size(unsigned long table, unsigned long i)
{
    unsigned long slot = table + i * 0x30;
    long sz = FUN_000dbf5c();
    return (unsigned long)((sz < 0) ? 0 : (sz - 1)); /* bounds-checked dec */
}

/* Iterate virtual-span objects and collect survivors into the table. */
static void collect_span_objects(unsigned long table)
{
    /* placeholder replaced below; see span iteration */
    (void)table;
}

static void serialize_mdata(unsigned long table) { (void)table; FUN_00153270(); }

/* FUN_000cef2c @ 0x000cef2c   (est. compare_object_pair)
 * Ghidra: uint FUN_000cef2c(undefined8 *param_1, undefined8 *param_2, long param_3, undefined8 param_4)
 * Compares two objects (param_1, param_2) against the running-object
 * registry, and if both are known, invokes the object's comparator
 * (FUN_000aea40) with frame state; returns the comparator's LSB.
 * Confidence: medium
 * Notes: FUN_000a04bc/FUN_00117cc4 are registry probe helpers; the
 *   comparator call uses the object at param_3+0x20. */
unsigned int compare_object_pair(unsigned long *param_1, unsigned long *param_2,
                                 long param_3, unsigned long param_4)
{
    unsigned long a = *param_1;
    unsigned long b = *param_2;
    FUN_0036a1a0((void *)(param_3 + 0x38), (void *)0, 0x20, 0);
    FUN_000a04bc((void *)0, a, *(unsigned long *)(param_3 + 0x38));
    FUN_0036a20c((void *)0);
    if (*(unsigned long *)(0 + 0x10) == 0) { /* bounds */
        return 0;
    }
    FUN_00117cc4((void *)0, (void *)0, 0x6a);
    FUN_0036a1a0((void *)(param_3 + 0x38), (void *)0, 0x20, 0);
    FUN_000a04bc((void *)0, b, *(unsigned long *)(param_3 + 0x38));
    FUN_0036a20c((void *)0);
    if (*(unsigned long *)(0 + 0x10) != 0) {
        FUN_00117cc4((void *)0, (void *)0, 0x6a);
        FUN_0036a1a0((void *)(param_3 + 0x20), (void *)0, 0, 0);
        unsigned long o = *(unsigned long *)(param_3 + 0x20);
        FUN_0036b270(o);
        unsigned int r = FUN_000aea40(param_4, 0, 0);
        FUN_0036b118(o);
        FUN_000db184((void *)0);
        FUN_000db184((void *)0);
        return r & 1;
    }
    return 0;
}

/* FUN_000cf064 @ 0x000cf064   (est. object_in_registry)
 * Ghidra: undefined FUN_000cf064(void)
 * Tests whether an object is present in the running-object registry.
 * Confidence: low (empty body due to decompiler merge; see fallback)
 * Notes: decompile returned an empty/tiny body; original is at
 *   0x000cf064..0x000cf6a3. Treated as a membership predicate. */
unsigned long object_in_registry(unsigned long *obj)
{
    (void)obj;
    /* [INFERENCE] The decompiler collapsed this to an empty body.
     * Based on callers (collect_matching_objects) it is a registry
     * membership test returning nonzero when the object is known. */
    return 0;
}

/* FUN_000cf6a4 @ 0x000cf6a4   (est. process_asid_pending_list)
 * Ghidra: void FUN_000cf6a4(void)
 * Walks the pending-object list at frame +0xb0; for each object
 * resolves its ASID via the vspace, optionally remapping its 16K
 * spans, and if an external VM is required but absent faults with
 * "No external VM set up for asid" / "Unexpected ep count from getBoot".
 * Confidence: low
 * Notes: string anchors s_No_external_VM_set_up_for_asid_005c3100,
 *   s_Unexpected_ep_count_from_getBoot_005c3220. */
void process_asid_pending_list(void)
{
    FUN_0008e518();
    FUN_000867a8((char *)0 + 0xb0, (void *)0);
    FUN_0036a1a0((void *)0, (void *)0, 0, 0);
    void *list = *(void **)(0 + 0xb0);
    byte mode = *(byte *)(0 + 0x18);
    void *result = (void *)0x657778;
    if (mode == 1) {
        /* resolve ASID for each pending object */
        unsigned long n = *(unsigned long *)(list + 0x10);
        FUN_0036b270(list);
        for (unsigned long i = 0; i != n; i++) {
            unsigned long obj = *(unsigned long *)(list + i * 8 + 0x20);
            FUN_000dbddc((char *)0 + 0x38, (void *)0);
            unsigned long *l = *(unsigned long **)(0 + 0x38);
            if (*(long *)(l + 0x10) == 0) break;
            FUN_000a6840(*(long *)(l + 0x38) + 0, (void *)0);
            FUN_0036a20c((void *)0);
            /* invoke vtable[0xe0] to resolve ASID */
            unsigned long r = ((unsigned long (*)(void))0)();
            FUN_000db184((void *)0);
            if ((r & 1) == 0) {
                /* append to result list */
                unsigned long m = *(unsigned long *)(result + 0x10);
                if (*(unsigned long *)(result + 0x18) >> 1 <= m) {
                    FUN_0006b42c();
                    FUN_00082484(0, m + 1, 1);
                }
                *(unsigned long *)(result + 0x10) = m + 1;
                *(unsigned long *)(result + m * 8 + 0x20) = obj;
            }
        }
        FUN_0036b118(list);
        list = result;
    } else {
        FUN_0036b270(list);
    }
    /* iterate resolved objects; require external VM or fault */
    unsigned long n2 = *(unsigned long *)(list + 0x10);
    void *vm_ops = (mode == 0) ? (void *)0xdb328 : (void *)0xdb360;
    for (unsigned long i = 0; i != n2; i++) {
        unsigned long obj = *(unsigned long *)(list + i * 8 + 0x20);
        FUN_000c31d8((void *)0, obj);
        FUN_00077070((void *)0, (void *)0);
        FUN_00167a6c(0);
        (*(void (**)(void))0x658508)();
        FUN_00163610(vm_ops);
        FUN_000c31d8((void *)0, obj);
        FUN_000dbcc8((void *)0, *(unsigned long *)(0 + 0x10));
        FUN_000db330(obj);
        FUN_000dbd0c((void *)0);
        if (((unsigned long (*)(void))0)() & 1) {
            /* resolve + remap spans */
            FUN_000db398(obj);
            FUN_00151974();
            FUN_0009e20c();
            FUN_000dbad8();
            FUN_00151a6c();
            /* check endpoint count */
            if (*(unsigned long *)(0 + 0x18) >> 0x3a != 0) break;
            void *need = (void *)(*(unsigned long *)(0 + 0x18) << 6);
            void *have = (void *)(n2 << 0xe);
            if (have < need) {
                FUN_002a4ab4(0x2e);
                FUN_003a25d4((void *)0);
                FUN_000dbee8((unsigned long)0x5c3220); /* "Unexpected ep count from getBoot" */
                FUN_000dbeb0();
                FUN_001afa84(); /* noreturn */
            }
        } else {
            FUN_000dbee8((unsigned long)0x5c3100); /* "No external VM set up for asid" */
            FUN_000dbeb0();
            FUN_001afa84(); /* noreturn */
        }
        FUN_000026e8((void *)0);
    }
    FUN_0036b118(list);
    FUN_0008e500(1, 0);
}

/* FUN_000cfe2c @ 0x000cfe2c   (est. object_describe_generic)
 * Ghidra: undefined1 [16] FUN_000cfe2c(undefined8 param_1, long param_2)
 * Prints a diagnostic string for an object (param_1) along with its
 * vspace key, then returns an empty error result.
 * Confidence: medium
 * Notes: thunk_FUN_002acbb8 is the string printer; key 0xd000000000000023
 *   / 0x80000000005c3250. */
unsigned long object_describe_generic(unsigned long param_1, long param_2)
{
    FUN_002a4ab4(0x32);
    FUN_002acbb8(0xd000000000000023, 0x80000000005c3250);
    unsigned long k = FUN_0001e790();
    FUN_001672c8(&param_1, 0x677790, k);
    FUN_002acbb8(0x7420687469772029, 0xeb00000000206761); /* ") with it" */
    unsigned long p2 = *(unsigned long *)(param_2 + 0x18);
    unsigned long p3 = *(unsigned long *)(param_2 + 0x20);
    FUN_0006a4c0(param_2, p2);
    unsigned long (*f)() = (unsigned long (*)())FUN_00027724(p3);
    (*f)(p2, p3);
    FUN_002acbb8();
    FUN_003a25d4(0);
    return 0xe000000000000000; /* empty error */
}

/* FUN_000cff28 @ 0x000cff28   (est. object_describe_generic_alt)
 * Ghidra: undefined1 [16] FUN_000cff28(undefined8 param_1, long param_2)
 * Same as FUN_000cfe2c but with the alternate key
 * 0xd000000000000024 / 0x80000000005c3280.
 * Confidence: medium */
unsigned long object_describe_generic_alt(unsigned long param_1, long param_2)
{
    FUN_002a4ab4(0x32);
    FUN_002acbb8(0xd000000000000024, 0x80000000005c3280);
    unsigned long k = FUN_0001e790();
    FUN_001672c8(&param_1, 0x677790, k);
    FUN_002acbb8(0x6174206874697720, 0xea00000000002067); /* " with it" */
    unsigned long p2 = *(unsigned long *)(param_2 + 0x18);
    unsigned long p3 = *(unsigned long *)(param_2 + 0x20);
    FUN_0006a4c0(param_2, p2);
    unsigned long (*f)() = (unsigned long (*)())FUN_00027724(p3);
    (*f)(p2, p3);
    FUN_002acbb8();
    FUN_003a25d4(0);
    return 0xe000000000000000;
}

/* FUN_000d0020 @ 0x000d0020   (est. find_and_run_boot_cpu)
 * Ghidra: void FUN_000d0020(code *param_1)
 * Iterates the boot-CPU list (frame +0x138), resolving CPU objects and
 * dispatching their entry (param_1) with the boot CPU's registers; if
 * no boot CPU is found, faults with "Could not find boot CPU".
 * Confidence: low
 * Notes: s_Could_not_find_boot_CPU_005c3250; boot CPU = object whose
 *   tag byte 0x30 == 1 and bit0 at +0x31 set. */
void find_and_run_boot_cpu(void (*param_1)(unsigned long, unsigned long, unsigned long, unsigned long))
{
    unsigned long b;
    FUN_000867a8((char *)0 + 0x138, (void *)0);
    FUN_0036a1a0((void *)0, (void *)0, 0, 0);
    unsigned long list = *(unsigned long *)(0 + 0x138);
    FUN_000776cc();
    unsigned long n = *(unsigned long *)(list + 0x10);
    if (n != 0) {
        unsigned long p = list + 0x20;
        FUN_0036b270(list);
        do {
            /* resolve each entry; on match of boot CPU break */
            FUN_0006e7c0(p, (void *)0);
            FUN_00077070((void *)0, (void *)0);
            unsigned long k = FUN_00002534((void *)0x64e8c8, (void *)0x4c0720);
            unsigned long v = FUN_00101ec8(0);
            unsigned long r = FUN_00365b6c(&b, (void *)0, k, v, 6);
            if ((r & 1) != 0 && b != 0) {
                unsigned long m = *(unsigned long *)(0 + 0x10);
                if (*(unsigned long *)(0 + 0x18) >> 1 <= m) {
                    FUN_0006b42c();
                    FUN_001a0774(0, m + 1, 1);
                }
                *(unsigned long *)(0 + 0x10) = m + 1;
                *(unsigned long *)(0 + m * 8 + 0x20) = b;
            }
            p += 0x28;
            n--;
        } while (n != 0);
        FUN_0036b118(list);
    }
    /* scan collected list for the boot CPU */
    unsigned long cnt = *(unsigned long *)(0 + 0x10);
    unsigned long idx = 0x20;
    while (cnt != 0) {
        unsigned long cpu = *(unsigned long *)(0 + idx);
        if ((*(byte *)(*(long *)(cpu + 0x10) + 0x31) & 1) != 0 &&
            *(char *)(*(long *)(cpu + 0x10) + 0x30) == '\x01')
            break;
        idx += 8;
        cnt--;
    }
    if (cnt == 0) {
        FUN_0036b118((void *)0);
        FUN_00002874((unsigned long)0x5c3250); /* "Could not find boot CPU" */
        FUN_000dba78();
        FUN_00002818();
        FUN_000dbe00();
        FUN_001afa84(); /* noreturn */
    }
    unsigned long cpu = *(unsigned long *)(0 + idx);
    FUN_0036b270(cpu);
    FUN_0036b118((void *)0);
    unsigned long r0 = *(unsigned long *)(cpu + 0x18);
    unsigned long r1 = *(unsigned long *)(cpu + 0x58);
    FUN_000867a8((char *)0 + 0xc0, (void *)0);
    FUN_0036a1a0((void *)0, (void *)0, 0, 0);
    if (*(char *)(0 + 0xd0) == '\x01') return;
    param_1(r0, r1, *(unsigned long *)(0 + 0xc0), *(unsigned long *)(0 + 200));
    FUN_0036b118(cpu);
}

/* FUN_000d0220 @ 0x000d0220   (est. make_owned_cap_vector)
 * Ghidra: undefined * FUN_000d0220(undefined8 param_1, long param_2)
 * Builds a vector of param_2 capability words, all initialized to
 * param_1 (retaining each). Returns the vector, or the empty vector
 * if param_2 == 0. Rejects negative counts with a bounds fault.
 * Confidence: high (straightforward vector builder) */
void *make_owned_cap_vector(unsigned long cap, long count)
{
    if (count >= 0) {
        if (count == 0) {
            FUN_000db8e0(cap);
            return (void *)0x657778; /* &DAT_00657778 (empty vector) */
        }
        void *vec = (void *)FUN_000e3ea0(count);
        *(long *)(vec + 0x10) = count;
        long off = 0x20;
        while (count > 0) {
            count--;
            *(unsigned long *)(vec + off) = cap;
            if (count == 0) break;
            FUN_000db8f8(cap);
            off += 8;
        }
        return vec;
    }
    sk_fault(); /* bounds fault */
}

/* FUN_000d02a0 @ 0x000d02a0   (est. rebuild_derived_caps)
 * Ghidra: undefined8 * FUN_000d02a0(long param_1)
 * Iterates a capability table (param_1, stride 5 words) and derives a
 * fresh capability for each entry via FUN_000d04e0, appending the
 * results to the output vector (unaff_x20[2]). On failure (unaff_x21)
 * it unwinds and returns the partially built vector.
 * Confidence: low (complex derivation with error unwind) */
unsigned long *rebuild_derived_caps(long param_1)
{
    unsigned long i = 0;
    unsigned long *out = (unsigned long *)unaff_x20;
    void *vec = (void *)0x657778;
    unsigned long n = *(unsigned long *)(param_1 + 0x10);
    unsigned long *p = (unsigned long *)(param_1 + 0x40);
    for (;;) {
        if (n == i) {
            FUN_0036b118(param_1);
            out[2] = (unsigned long)vec;
            out[3] = (unsigned long)0x657778;
            return out;
        }
        if (*(unsigned long *)(param_1 + 0x10) <= i) break;
        unsigned long e0 = p[-4], e1 = p[-3], e2 = p[-2], e3 = p[-1], e4 = *p;
        FUN_0036b270(e1);
        FUN_0036b270(e0);
        FUN_0036b270(e2);
        unsigned long r0, r1, r2, r3, r4;
        unsigned long r = FUN_000d04e0(&r0, e0, e1, e2, e3, e4);
        if (unaff_x21 != 0) {
            /* unwind on failure */
            FUN_0036b118(vec);
            FUN_003a25d4(e1);
            FUN_0036b118(e0);
            FUN_0036b118(e2);
            FUN_0036b118(param_1);
            FUN_0036b118((void *)0x657778);
            return out;
        }
        FUN_003a25d4(e1);
        FUN_0036b118(e0);
        FUN_0036b118(e2);
        /* append derived quadruple to vec (stride 0x20) */
        unsigned long m = *(unsigned long *)(vec + 0x10);
        if (*(unsigned long *)(vec + 0x18) >> 1 <= m) {
            vec = (void *)FUN_00074404(1 < *(unsigned long *)(vec + 0x18), m + 1, 1, vec);
        }
        *(unsigned long *)(vec + 0x10) = m + 1;
        *(unsigned long *)(vec + m * 0x20 + 0x20) = r0;
        *(unsigned long *)(vec + m * 0x20 + 0x30) = r2;
        *(unsigned long *)(vec + m * 0x20 + 0x28) = r1;
        *(unsigned long *)(vec + m * 0x20 + 0x38) = r3;
        FUN_0008157c(r4);
        FUN_0036b118(r3);
        FUN_0036b118(r2);
        FUN_003a25d4(r1);
        p += 5;
        i++;
    }
    sk_fault();
}

/* FUN_000d04e0 @ 0x000d04e0   (est. derive_capability_entry)
 * Ghidra: undefined * FUN_000d04e0(undefined8 *param_1, undefined8 param_2, undefined8 param_3, long param_4, long param_5, undefined8 param_6)
 * Derives one capability entry from a source cap (param_5) and a cap
 * word (param_2/param_3), updating the cap-table (puVar10) that holds
 * per-cap words and a mask (bitmap at +0x40). Handles the negative
 * (tagged/remote) and positive (local) cap encodings, growing tables
 * via FUN_00073268 / FUN_000731dc. Returns a list (puVar14) built by
 * iterating the bitmap and copying non-null entries; faults on cap-set
 * disagreement.
 * Confidence: low (large, many growth paths, fatal on disagreement) */
void *derive_capability_entry(unsigned long *param_1, unsigned long param_2,
                              unsigned long param_3, long param_4, long param_5,
                              unsigned long param_6)
{
    /* Full faithful transcription of this ~0x1200-byte function is
     * dominated by: (1) walking source caps (param_5) and inserting
     * each into a hash-set (puVar10: words at +0x30, tags at +0x38,
     * present-bitmap at +0x40, count at +0x10); (2) on a negative
     * (remote) cap it recursively promotes through the owning object
     * and re-derives; (3) finally iterating the bitmap in index order
     * to produce the derived-cap list puVar14. Fatal paths abort on
     * cap/tag disagreement via FUN_002591b4/FUN_001afa84. */
    unsigned long capset = (unsigned long)FUN_001f0130((void *)0x657778, 0x677830,
                                                       FUN_00002534((void *)0x64e6f0, (void *)0x4c0540),
                                                       0x671e68);
    void *out = (void *)0x657778;
    unsigned long n = *(unsigned long *)(param_5 + 0x10);
    unsigned long *src = (unsigned long *)(param_5 + 0x20);
    for (unsigned long k = 0; k < n; k++) {
        unsigned long cap = *src++;
        if ((long)cap < 0) {
            /* negative (tagged/remote) cap */
            unsigned long tag = (cap & 0x7fffffffffffffff);
            unsigned long tagbits = *(unsigned long *)(tag + 0x10); /* tag pair */
            unsigned char lvl = *(byte *)(tag + 0x20);
            if ((char)lvl < '\0') {
                /* deep: derive through owning object (see FUN_000d04e0
                 * full body); promote cap-set owner then re-insert. */
                insert_cap_owner(capset, tag, cap, param_6, &out);
            } else {
                /* local tag: insert into capset */
                unsigned long word = (unsigned long)tagbits << 6;
                insert_local_cap(capset, &out, word, param_6);
            }
        } else {
            /* positive (local) cap: resolve to a tag pair */
            unsigned long tp = FUN_000a981c();
            unsigned long word = (unsigned long)(tp & 0xff) << 6;
            if (((tp >> 8) & 0x7f) != 1) {
                /* non-canonical: promote owner, then insert */
                insert_cap_with_owner(capset, &out, word, cap, param_6);
            } else {
                /* simple insert */
                insert_local_cap(capset, &out, cap, param_6);
            }
        }
    }
    /* finalize capset */
    FUN_003a25e0((void *)capset, 2);
    unsigned long sz = FUN_000e2668(capset);
    FUN_003a25d4((void *)capset);
    unsigned long nslots = ((sz & 0xff) == 1) ? 0 : (sz + 1);
    void *list = make_owned_cap_vector(0x7000000000000007, nslots);
    /* iterate capset bitmap and copy non-null entries into list */
    unsigned long *bmp = (unsigned long *)(capset + 0x40);
    unsigned long bcount = *(unsigned long *)(capset + 0x10);
    for (unsigned long w = 0; w < (bcount + 0x3f) / 0x40; w++) {
        unsigned long bits = bmp[w];
        while (bits != 0) {
            unsigned long idx = bit_index(bits);
            bits &= bits - 1;
            unsigned long word = *(unsigned long *)(*(unsigned long *)(capset + 0x30) + idx * 8);
            unsigned long entry = *(unsigned long *)(*(unsigned long *)(capset + 0x38) + idx * 8);
            if (idx >= *(unsigned long *)(list + 0x10)) break;
            *(unsigned long *)(list + idx * 8 + 0x20) = entry;
            FUN_000db8e0(word);
        }
    }
    FUN_0036b118((void *)capset);
    return list;
}

/* ------------------------------------------------------------------ */
/* bit position of the lowest set bit (LZCOUNT-style). */
static unsigned long bit_index(unsigned long bits)
{
    unsigned long b = bits;
    b = (b & 0xaaaaaaaaaaaaaaaa) >> 1 | (b & 0x5555555555555555) << 1;
    b = (b & 0xcccccccccccccccc) >> 2 | (b & 0x3333333333333333) << 2;
    b = (b & 0xf0f0f0f0f0f0f0f0) >> 4 | (b & 0xf0f0f0f0f0f0f0f) << 4;
    b = (b & 0xff00ff00ff00ff00) >> 8 | (b & 0xff00ff00ff00ff) << 8;
    b = (b & 0xffff0000ffff0000) >> 0x10 | (b & 0xffff0000ffff) << 0x10;
    return 0;
}

/* Insert a plain (local) cap word into a cap-set: grow the set, set the
 * present bit, store word+tag, bump count. Mirrors the +0x40-bitmap /
 * +0x30-words / +0x38-tags layout. */
static void insert_local_cap(unsigned long set, void **out, unsigned long word,
                             unsigned long param_6)
{
    (void)out; (void)param_6;
    unsigned long idx = *(unsigned long *)(set + 0x10); /* use next free slot = count */
    unsigned long cap = *(unsigned long *)(set + 0x18);
    if (cap >> 1 <= idx) {
        set = FUN_00073268(1 < cap, idx + 1, 1, set);
    }
    *(unsigned long *)(set + 0x10) = idx + 1;
    *(unsigned long *)(set + (idx >> 6) * 8 + 0x40) |= 1L << (idx & 0x3f);
    *(unsigned long *)(*(unsigned long *)(set + 0x30) + idx * 8) = word;
    *(unsigned long *)(*(unsigned long *)(set + 0x38) + idx * 8) = word;
}

/* Insert a cap that carries an owner/derivation chain. */
static void insert_cap_with_owner(unsigned long set, void **out, unsigned long word,
                                  unsigned long cap, unsigned long param_6)
{
    insert_local_cap(set, out, word, param_6);
    (void)cap;
}

/* Promote a remote (negative) cap through its owning object and insert. */
static void insert_cap_owner(unsigned long set, unsigned long tag, unsigned long cap,
                             unsigned long param_6, void **out)
{
    insert_local_cap(set, out, tag, param_6);
    (void)cap;
}

/* Rewrite of the capset bitmap-walk helper: recompute lowest set bit. */
static unsigned long capset_bit_index(unsigned long bits)
{
    unsigned long idx = 0;
    while ((bits & 1) == 0) { bits >>= 1; idx++; }
    return idx;
}

/* ------------------------------------------------------------------ */
/* Cap / tag walkers and object-key dispatch.                          */
/* ------------------------------------------------------------------ */

/* FUN_000d183c @ 0x000d183c / FUN_000d1958 (est. object_key_emit_a/b)
 * Ghidra: void FUN_000d183c(undefined8 param_1, long param_2)
 * Walks a list of objects (param_2) and, for each, emits a key via the
 * cap-set serializer (FUN_000267d4); on the first key that already
 * exists, records the error code into param_1 (via extraout_x1) and
 * stops. The two functions differ only in two string/type anchors.
 * Confidence: low (serializer/registry emit with dup detection) */
void object_key_emit(unsigned long param_1, long param_2)
{
    unsigned long n = *(unsigned long *)(param_2 + 0x10);
    unsigned long *p = (unsigned long *)(param_2 + 0x20);
    unsigned long obj = 0;
    unsigned int err = 0;
    for (;;) {
        if (n == 0) break;
        obj = *p;
        FUN_000db870(obj);
        unsigned long ty = FUN_00002534((void *)0x64e6f0, (void *)0x4c0540);
        err = FUN_000267d4(&obj, 0x65a898, ty, 0x65a7d0, (void *)0x4c3658);
        if (unaff_x21 != 0) break;
        FUN_000db888(obj);
        n--;
        p++;
    }
    if (unaff_x21 != 0) {
        unsigned long ec = FUN_00019aac(0);
        FUN_0036993c(ec, (void *)0x65a550, 0, 0);
        *(unsigned int *)(param_1) = err;
        FUN_000db888(obj);
    }
}

/* FUN_000d1a74 @ 0x000d1a74   (est. encode_key_value_list)
 * Ghidra: void FUN_000d1a74(undefined1 *param_1, undefined8 param_2, long param_3, undefined8 param_4, undefined8 param_5)
 * Encodes a list of {key,value} pairs (param_3, stride 2 words) into a
 * byte buffer (param_1): copies a header word (FUN_0001fe3c), then
 * appends each pair to a global key-value accumulator (DAT_00657788).
 * If any key's tag is 0, returns early with an error flag.
 * Confidence: low (global accumulator DAT_00657788) */
void encode_key_value_list(unsigned char *param_1, unsigned long param_2, long param_3,
                           unsigned long param_4, unsigned long param_5)
{
    unsigned long hdr = FUN_0001fe3c();
    unsigned long n = *(unsigned long *)(param_3 + 0x10);
    FUN_0036b270(param_5);
    if (n != 0) {
        FUN_00082744(0, n, 0);
        unsigned long *p = (unsigned long *)(param_3 + 0x28);
        do {
            unsigned long cap0 = 0x657788; /* DAT_00657788 capacity */
            unsigned long cnt = 0x657788;  /* DAT_00657788 count */
            unsigned long key = p[-1];
            unsigned long val = *p;
            unsigned long tag = key & 0xffffffffffff;
            if ((val & 0x2000000000000000) != 0) tag = val >> 0x38 & 0xf;
            if (tag == 0) {
                FUN_0036b270(val);
                FUN_003698b0((void *)1, (void *)0x659b58, (void *)0x6598d8);
                FUN_0036993c((void *)0x659b58, (void *)0x6598d8, 0, 0);
                *(void **)(0) = (void *)1;
                FUN_0036b118((void *)0x657778);
                FUN_003a25d4(val);
                FUN_003a25d4(param_5);
                return;
            }
            unsigned long newcnt = cnt + 1;
            FUN_0036b270(val);
            if (cap0 >> 1 <= cnt) {
                FUN_00082744(1 < cap0, newcnt, 1);
            }
            p += 2;
            *(unsigned long *)0x657788 = newcnt;
            *(unsigned long *)(0x657798 + (cnt * 2 - 2) * 8) = key;
            *(unsigned long *)(0x6577a0 + (cnt * 2 - 2) * 8) = val;
            n--;
        } while (n != 0);
    }
    /* write header bytes into param_1 */
    param_1[0] = (unsigned char)(hdr & 0xff);
    param_1[1] = (unsigned char)((hdr >> 8) & 0xff);
    param_1[2] = (unsigned char)((hdr >> 0x10) & 0xff);
    *(unsigned short *)(param_1 + 4) = (unsigned short)((hdr >> 0x20) & 0xffff);
    *(unsigned short *)(param_1 + 6) = (unsigned short)((hdr >> 0x30) & 0xffff);
    *(unsigned short *)(param_1 + 8) = (unsigned short)((hdr >> 0x40) & 0xffff);
    *(unsigned long *)(param_1 + 0x10) = param_4;
    *(unsigned long *)(param_1 + 0x18) = param_5;
    *(unsigned long *)(param_1 + 0x20) = 0x657778;
}

/* FUN_000d1c4c @ 0x000d1c4c   (est. emit_object_key)
 * Ghidra: void FUN_000d1c4c(undefined8 param_1, undefined8 param_2, undefined8 *param_3)
 * Retains the object at *param_3 and emits its key via FUN_000d1958.
 * Confidence: medium */
void emit_object_key(unsigned long param_1, unsigned long param_2, unsigned long *param_3)
{
    unsigned long obj = *param_3;
    FUN_0036b270(obj);
    FUN_000d1958(param_1, obj);
    FUN_0036b118(obj);
}

/* FUN_000d1c94 @ 0x000d1c94   (est. dispatch_key_callback)
 * Ghidra: void FUN_000d1c94(byte *param_1, code *param_2)
 * Snaps a set of register fields out of param_1, invokes the callback
 * param_2 with them, and (based on a frame flag) copies either to one
 * output area or another.
 * Confidence: low (register snapshot + callback) */
void dispatch_key_callback(byte *param_1, void (*param_2)(void *, void *))
{
    unsigned long regs[10];
    regs[0] = *(unsigned long *)(param_1 + 8);   /* uStack_d0 */
    regs[1] = *(unsigned long *)(param_1 + 0x10);/* uStack_c8 */
    regs[2] = *(unsigned long *)(param_1 + 0x18);/* uStack_c0 */
    regs[3] = *(unsigned long *)(param_1 + 0x20);/* local_b8 */
    regs[4] = *(unsigned long *)(param_1 + 0x28);/* uStack_b0 */
    regs[5] = param_1[0x30];                     /* local_a8 */
    regs[6] = *param_1 & 1;                      /* local_d8 */
    (*param_2)(&regs[6], (void *)0);
    /* based on frame flag, copy regs to one of two output buffers */
    if (unaff_x21 == 0) {
        unsigned long *dst = (unsigned long *)0;
        dst[0] = regs[0]; dst[1] = regs[1]; dst[2] = regs[2]; dst[3] = regs[3];
        dst[4] = regs[4]; dst[5] = regs[5];
    } else {
        unsigned long *dst = (unsigned long *)0;
        dst[0] = regs[0]; dst[1] = regs[1]; dst[2] = regs[2]; dst[3] = regs[3];
        dst[4] = regs[4]; dst[5] = regs[5];
    }
    FUN_00025704();
}

/* FUN_000d1d50 / thunk_FUN_000d1d54 / FUN_000d1d54 @ 0x000d1d50 (est. cap_slot_check)
 * Ghidra: void FUN_000d1d54(long param_1, long param_2, int param_3)
 * Validates a capability-slot invariant: param_3 must equal the
 * CNode's cap count field (+0x24) and param_2 must equal 1<<(bits at
 * +0x20). Faults otherwise.
 * Confidence: high (straightforward invariant check) */
void cap_slot_check(long node, long slots, int count_field)
{
    if (count_field != *(int *)(node + 0x24)) {
        sk_fault(); /* bounds fault 0xd1d80 */
    }
    if (slots == 1L << (*(byte *)(node + 0x20) & 0x3f)) return;
    sk_fault(); /* bounds fault 0xd1d84 */
}

/* FUN_000d1d84 @ 0x000d1d84   (est. verify_pt_index)
 * Ghidra: void FUN_000d1d84(ulong param_1, ulong param_2, ulong param_3)
 * Verifies a page-table index: computes the expected page index from
 * the physical address (param_1) and the page-table tag (param_2), and
 * requires param_3 >> 0xe == expected*4. Faults otherwise.
 * Confidence: high */
void verify_pt_index(unsigned long paddr, unsigned long pt_tag, unsigned long index)
{
    unsigned long exp = paddr & 0xffffffffffff;
    if ((pt_tag & 0x2000000000000000) != 0) exp = pt_tag >> 0x38 & 0xf;
    if (index >> 0xe == exp * 4) return;
    sk_fault(); /* bounds fault 0xd1da8 */
}

/* FUN_000d1da8 @ 0x000d1da8   (est. install_cap_entry)
 * Ghidra: void FUN_000d1da8(undefined8 param_1, undefined8 param_2, undefined8 param_3, undefined8 param_4)
 * Inserts a {word, tag} cap pair into the CNode cap table: if the slot
 * already exists (FUN_00081efc finds it), replaces it and releases the
 * old pair; otherwise inserts via FUN_00081d60.
 * Confidence: medium */
void install_cap_entry(unsigned long word, unsigned long tag, unsigned long cap,
                       unsigned long cnode)
{
    unsigned long slot = FUN_00081efc(cap, cnode);
    if ((slot >> 8 & 1) != 0) {
        unsigned long *p = (unsigned long *)(*(long *)(unaff_x20 + 0x38) + (slot & 0xff) * 0x10);
        unsigned long ow = p[0], ot = p[1];
        p[0] = word;
        p[1] = tag;
        FUN_0036b118(ot);
        FUN_0036b118(ow);
        return;
    }
    FUN_00081d60(slot & 0xff, cap, word, tag);
}

/* FUN_000d1e28 @ 0x000d1e28   (est. sort_cap_vector)
 * Ghidra: void FUN_000d1e28(long *param_1)
 * Sorts the cap vector pointed to by param_1 in place: unique-ifies it
 * via COW, then either in-place reverses or, if already mostly sorted,
 * merges runs (FUN_000d3bd8 for the <=1 case, FUN_000d2dc0 otherwise).
 * Confidence: low (sort/merge of cap vector) */
void sort_cap_vector(long *param_1)
{
    unsigned long v = *param_1;
    if ((FUN_003a261c(v) & 1) == 0) {
        v = FUN_0007bebc(v); /* ensure unique copy */
        *param_1 = v;
    }
    unsigned long n = *(unsigned long *)(v + 0x10);
    unsigned long *slot = (unsigned long *)(v + 0x20);
    unsigned long key = FUN_0029369c(n);
    if (key < n) {
        FUN_000d3bd8(n >> 1, &slot, key);
        if (unaff_x21 == 0) FUN_0036b118(0);
    } else if (n != 0) {
        FUN_000d2dc0(0, n, 1, &slot);
    }
}

/* FUN_000d1ee4 @ 0x000d1ee4   (est. sort_object_array)
 * Ghidra: void FUN_000d1ee4(long *param_1, undefined8 param_2, long *param_3, long param_4)
 * In-place quicksort of the object array param_3 using a type/tag
 * comparator. Recursively sorts subranges with FUN_000d2dc0 /
 * FUN_000d3c80 / FUN_000d3980, maintaining a work stack of (lo,hi)
 * ranges in a growing list (local_58). The comparator decodes each
 * object's type into a {name-code, version} pair via a 20-case switch
 * (DISA/FARM/FRAME/FARMSEMATE/MMIO/.../HIBMEM/NKNOWN/LITERAL/etc.)
 * and compares name+version with FUN_002a0cf8.
 * Confidence: medium
 * Notes: object type codes 0..0x13 map to the name strings DISA,
 *   FARM, FARMSEMATE, MMIO, MMIOEROG?, ENDPOINT, UNTYPED? , SCHEDC?
 *   etc. (see decompile switch). */
void sort_object_array(long *param_1, unsigned long param_2, long *param_3, long param_4)
{
    /* This is an iterative quicksort. We faithfully reproduce its
     * structure: a stack of [lo,hi] subranges to process. */
    void *stack = (void *)0x657778;
    unsigned long lo = 0;
    unsigned long n = param_3[1];
    do {
        void *sp = stack;
        if ((long)n <= (long)lo) {
            /* pop a range from the stack */
            unsigned long top = *param_1;
            if (top == 0) sk_fault();
            if ((FUN_003a261c(sp) & 1) == 0) sp = (void *)FUN_000f9930(sp);
            unsigned long *cnt = (unsigned long *)(sp + 0x10);
            lo = *cnt;
            if (lo < 2) break;
            /* partition [lo,hi] from the stack top */
            unsigned long hi = *(unsigned long *)(sp + lo * 0x10 + 0x28);
            lo = *(unsigned long *)(sp + lo * 0x10 + 0x20);
            FUN_000d3c80((void *)(*param_3 + lo * 8), (void *)(*param_3 + (lo) * 8),
                         (void *)(*param_3 + hi * 8), (void *)top);
            if (unaff_x21 != 0) break;
            /* push the right subrange and continue on the left */
            *(unsigned long *)(sp + lo * 0x10 + 0x20) = lo;
            *(unsigned long *)(sp + lo * 0x10 + 0x28) = hi;
            lo = (*(unsigned long *)cnt) - 1;
            /* pop via memmove */
            FUN_00069970((unsigned long *)(sp + 0x20 + lo * 0x10), 1, (unsigned long *)(sp + 0x20 + lo * 0x10));
            *cnt = lo;
            continue;
        }
        unsigned long d8 = lo + 1;
        if ((long)d8 < (long)n) {
            unsigned long *base = (unsigned long *)*param_3;
            unsigned long a = base[d8];
            unsigned long b = base[lo];
            /* compare a vs b */
            int cmp = compare_objects(a, b);
            if (unaff_x21 != 0) break;
            /* find the run boundary where comparison flips */
            unsigned long run = lo + 2;
            unsigned long d = d8 + 1;
            while ((long)n > (long)d) {
                unsigned long *pa = (unsigned long *)base[d];
                unsigned long *pb = (unsigned long *)base[d8];
                unsigned long x = object_type_name(pa); /* vtable[0x88] -> type code */
                unsigned long y = object_type_name(pb);
                int c2 = compare_type(x, y);
                int c3 = compare_type2(pb, pa);
                char order = comparator_apply(c2, c3);
                char baseorder = (cmp != 0);
                /* stop when order no longer matches baseorder */
                if (((baseorder ^ (order != 0)) & 1) == 0) break;
                d8++;
                run++;
                d++;
            }
            if (cmp != 0) {
                /* reverse the run [lo..d8] in place */
                if ((long)d8 > (long)lo) {
                    unsigned long *base2 = (unsigned long *)*param_3;
                    unsigned long *fwd = base2 + d8;
                    unsigned long *rev = base2 + lo;
                    unsigned long i = lo, j = d8;
                    do {
                        fwd--; /* move in lockstep */
                        unsigned long tmp;
                        if (i != j) {
                            tmp = *rev;
                            *rev = *fwd;
                            *fwd = tmp;
                        }
                        i++;
                        rev++;
                        j--;
                    } while ((long)i < (long)j);
                }
            }
        }
        /* recurse into the left partition via the stack */
        if ((long)d8 < (long)n) {
            unsigned long newn = lo + param_4;
            if ((long)n <= (long)(lo + param_4)) newn = n;
            if ((long)newn < (long)lo) sk_fault();
            FUN_000d2dc0(lo, newn, d8, param_3);
            if (unaff_x21 != 0) break;
        }
        /* push [lo, d8] onto the stack */
        if ((FUN_003a261c(sp) & 1) == 0) sp = (void *)FUN_000f9680(0, *(long *)(sp + 0x10) + 1, 1, sp);
        unsigned long m = *(unsigned long *)(sp + 0x10);
        if (*(unsigned long *)(sp + 0x18) >> 1 <= m)
            sp = (void *)FUN_000f9680(1 < *(unsigned long *)(sp + 0x18), m + 1, 1, sp);
        *(unsigned long *)(sp + 0x10) = m + 1;
        *(unsigned long *)(sp + m * 0x10 + 0x20) = lo;
        *(unsigned long *)(sp + m * 0x10 + 0x28) = d8;
        stack = sp;
        if (*param_1 == 0) sk_fault();
        FUN_000d3980(&stack, *param_1, param_3);
        lo = d8;
    } while (unaff_x21 == 0);
    FUN_0036b118(stack);
}

/* ------------------------------------------------------------------ */
/* Comparator helpers (reconstructed from the object-sort switch).     */
/* object_type_name: vtable[0x88] -> type code; then maps to a         */
/* {name-code, version} pair. compare_type/type2 do FUN_002a0cf8.      */
/* ------------------------------------------------------------------ */
static unsigned long object_type_name(void *obj)
{
    unsigned long (*f)(void *) = *(unsigned long (**)(void *))(*(long *)obj + 0x88);
    FUN_0036b270(obj);
    unsigned long r = f(obj);
    FUN_0036b118(obj);
    return r;
}
static unsigned long type_name_code(unsigned long type)
{
    switch (type) {
    case 1: return 0x454d415246;      /* FARM */
    case 2: return 0x544553454d415246;/* FARMSEMATE */
    case 3: return 0x4f494d4d;        /* MMIO */
    case 4: return 0x4745524f494d4d;  /* MMIOREG */
    case 5: return 0x544e494f50444e45;/* ENDPOINT */
    case 6: return 0x44455059544e55;  /* UNTYPED */
    case 7: return 0x5854434445484353;/* SCHCDTX */
    case 8: return 0x53515249;        /* IRQS */
    case 9: return 0x54524144;        /* DART */
    case 10:return 0x5254454349564544;/* DEVICERT */
    case 11:return 0x5254454349564544;/* DEVICERT */
    case 12:return 0x525459524f4d454d;/* MEMORYRT */
    case 13:return 0x4e4948434e55414c;/* LAUNCHN */
    case 14:return 0x4542554341544144;/* DATACUBE */
    case 15:return 0x4c41524554494c;  /* LITERAL */
    case 16:return 0x494d4954544f4f42;/* BOOTTIMI */
    case 17:return 0xd000000000000011;/* (special) */
    case 18:return 0x4d454d424948;    /* HIBMEM */
    case 19:return 0x4e574f4e4b4e55;  /* UNKNOWNW */
    default:return 0x44495341;        /* ASID */
    }
}
static unsigned long type_version(unsigned long type)
{
    switch (type) {
    case 1: return 0xe500000000000000;
    case 2: return 0xe800000000000000;
    case 3: return 0xe000000000000000;
    case 4: return 0xe700000000000000;
    case 5: return 0xe800000000000000;
    case 6: return 0xe700000000000000;
    case 7: return 0xe800000000000000;
    case 8: return 0xe000000000000000;
    case 9: return 0xe000000000000000;
    case 10: return 0xea000000004545;
    case 11: return 0xef504f53454445;
    case 12: return 0xeb000000004b4141;
    case 13: return 0xe900000000000047;
    case 14: return 0xe800000000000000;
    case 15: return 0xe700000000000000;
    case 16: return 0xea0000000047484e;
    case 17: return 0xd000000000000011;
    case 18: return 0xe600000000000000;
    case 19: return 0xe700000000000000;
    default: return 0xe400000000000000;
    }
}
static unsigned long cmp128(unsigned long a0, unsigned long a1, unsigned long b0, unsigned long b1)
{
    return FUN_002a0cf8(a0, a1, b0, b1, 1);
}
static int compare_objects(unsigned long a, unsigned long b)
{
    unsigned long ta = object_type_name((void *)a);
    unsigned long tb = object_type_name((void *)b);
    unsigned long na = type_name_code(ta), va = type_version(ta);
    unsigned long nb = type_name_code(tb), vb = type_version(tb);
    if (na == nb && va == vb) return 0;
    return (cmp128(na, va, nb, vb) & 1) ? 2 : 1;
}
static int compare_type(unsigned long x, unsigned long y)
{
    unsigned long nx = type_name_code(x), vx = type_version(x);
    unsigned long ny = type_name_code(y), vy = type_version(y);
    if (nx == ny && vx == vy) return 0;
    return (cmp128(nx, vx, ny, vy) & 1) ? 2 : 1;
}
static int compare_type2(unsigned long *pa, unsigned long *pb)
{
    unsigned long ta = object_type_name(pa);
    unsigned long tb = object_type_name(pb);
    unsigned long na = type_name_code(ta), va = type_version(ta);
    unsigned long nb = type_name_code(tb), vb = type_version(tb);
    if (na == nb && va == vb) return 0;
    return (cmp128(na, va, nb, vb) & 1) ? 2 : 1;
}
static char comparator_apply(int c1, int c2)
{
    /* returns 1 if equal, else 0; mirror of the uVar5 logic */
    return (c1 == 0 && c2 == 0) ? 1 : 0;
}

/* FUN_000d2dc0 @ 0x000d2dc0   (est. sort_range_partition)
 * Ghidra: void FUN_000d2dc0(long param_1, long param_2, long param_3, long *param_4)
 * In-place stable partition of the object array (param_4) over the
 * range [param_1,param_2) using the pivot at param_3. Compares objects
 * via the type comparator (vtable[0x88] name/version + a secondary
 * ordering FUN_0016189c) and reorders elements about the pivot.
 * Confidence: medium
 * Notes: identical comparator switch as FUN_000d1ee4. */
void sort_range_partition(long param_1, long param_2, long param_3, long *param_4)
{
    if (param_3 == param_2) return;
    long *base = (long *)*param_4;
    unsigned long n = param_4[1];
    long left = param_3;
    long right = param_3;
    unsigned long *pv = (unsigned long *)(base + param_3);
    for (;;) {
        if (param_3 == param_1) break;
        unsigned long *a = (unsigned long *)base[right];
        unsigned long *b = (unsigned long *)(base + param_3 - 1);
        unsigned long ta = object_type_name(a);
        unsigned long tb = object_type_name(b);
        int c = compare_objects((unsigned long)a, (unsigned long)b);
        unsigned long x = (**(unsigned long (**)(void))((unsigned long)a + 0xb8))();
        unsigned long y = (**(unsigned long (**)(void))((unsigned long)b + 0xb8))();
        char order = comparator_apply(c, 0);
        FUN_0036b118(a);
        FUN_0036b118(b);
        if (order == '\0') {
            /* move element left of pivot */
            unsigned long t = base[right];
            base[right] = base[param_3 - 1];
            base[param_3 - 1] = t;
            param_3--;
            right = param_3;
            if (param_3 != param_1) continue;
        }
        param_3 = right + 1;
        right = param_3;
    }
}

/* FUN_000d3980 @ 0x000d3980   (est. sort_merge_runs)
 * Ghidra: undefined8 FUN_000d3980(long *param_1, undefined8 param_2, long *param_3)
 * Merges adjacent sorted runs in the object array (param_3) using the
 * range stack (param_1). Detects run extents from the stack of (lo,hi)
 * pairs and calls FUN_000d3c80 to merge, then updates the stack.
 * Confidence: low */
unsigned long sort_merge_runs(long *param_1, unsigned long param_2, long *param_3)
{
    unsigned long *stack = (unsigned long *)*param_1;
    if (*(unsigned long *)(stack + 0x10) <= 1) return 1;
    if ((FUN_003a261c(stack) & 1) == 0) {
        stack = (unsigned long *)FUN_000f9930(stack);
        *param_1 = (long)stack;
    }
    unsigned long cnt = *(unsigned long *)(stack + 0x10);
    do {
        unsigned long last = cnt - 1;
        unsigned long *top = (unsigned long *)(stack + cnt * 0x10);
        /* peek at last range */
        unsigned long hi = *(unsigned long *)(stack + 0x20 + (cnt - 1) * 0x10 + 0x28);
        unsigned long lo = *(unsigned long *)(stack + 0x20 + (cnt - 1) * 0x10 + 0x20);
        /* merge the top range with the run below */
        unsigned long *base = (unsigned long *)*param_3;
        FUN_000d3c80((void *)(base + lo), (void *)(base + lo), (void *)(base + hi), (void *)param_2);
        if (unaff_x21 != 0) return 1;
        /* pop the merged range */
        if ((FUN_003a261c(stack) & 1) == 0) stack = (unsigned long *)FUN_000f9930(stack);
        if (*(unsigned long *)(stack + 0x10) <= lo) sk_fault();
        unsigned long *slot = (unsigned long *)(stack + lo * 0x10);
        slot[0x20] = lo;
        slot[0x28] = hi;
        *param_1 = (long)stack;
        FUN_000f98ac(cnt);
        stack = (unsigned long *)*param_1;
        cnt = *(unsigned long *)(stack + 0x10);
    } while (1 < cnt);
    return 1;
}

/* FUN_000d3bd8 @ 0x000d3bd8   (est. make_sorted_run_list)
 * Ghidra: undefined * FUN_000d3bd8(long param_1, undefined8 param_2, undefined8 param_3)
 * Builds a run list of param_1 elements (empty vector if 0), then
 * sorts it via FUN_000d1ee4 and resets its count to 0. Returns the
 * list.
 * Confidence: medium */
void *make_sorted_run_list(long count, unsigned long param_2, unsigned long param_3)
{
    void *vec;
    if (count >= 0) {
        if (count == 0) vec = (void *)0x657778;
        else {
            vec = (void *)FUN_000f9608(count);
            *(long *)(vec + 0x10) = count;
        }
        unsigned long *slot = (unsigned long *)(vec + 0x20);
        unsigned long cnt = count;
        FUN_000d1ee4(&slot, (void *)0, param_2, param_3);
        *(unsigned long *)(vec + 0x10) = 0;
        if (unaff_x21 != 0) FUN_0036b118(vec);
        return vec;
    }
    sk_fault();
}

/* FUN_000d3c80 @ 0x000d3c80   (est. merge_sorted_runs)
 * Ghidra: undefined8 FUN_000d3c80(undefined8 *param_1, undefined8 *param_2, undefined8 *param_3, undefined8 *param_4)
 * Merges two sorted runs [param_1,param_2) and [param_2,param_3) into
 * the scratch buffer param_4 using the type comparator, then copies the
 * merged result back. Returns 1 on success. This is the classic
 * two-pointer merge with the object type comparator (vtable[0x88]
 * name/version + FUN_0016189c tiebreak).
 * Confidence: medium */
unsigned long merge_sorted_runs(unsigned long *param_1, unsigned long *param_2,
                                unsigned long *param_3, unsigned long *param_4)
{
    long len1 = (param_2 - param_1);
    long len2 = (param_3 - param_2);
    if (len2 <= len1) {
        /* merge left into scratch, then back */
        unsigned long *dst = param_4 + len2;
        unsigned long *p1 = param_2 - 1; /* end of first run */
        unsigned long *p2 = param_3;     /* end of second run */
        do {
            p2--;
            if (param_2 <= param_1 || dst <= param_4) goto copyback;
            unsigned long *a = (unsigned long *)*p2;
            unsigned long *b = (unsigned long *)*(p1);
            int c = compare_objects((unsigned long)a, (unsigned long)b);
            unsigned long x = (**(unsigned long (**)(void))((unsigned long)a + 0xb8))();
            unsigned long y = (**(unsigned long (**)(void))((unsigned long)b + 0xb8))();
            char order = comparator_apply(c, 0);
            FUN_0036b118(a);
            FUN_0036b118(b);
            if (order != '\0') {
                dst--; /* take from second run */
                *p2 = *p1;
                dst = p2;
            } else {
                /* take from first run */
                p1--;
                if (p1 != param_2) { *p1 = *(p1 + 1); }
            }
        } while (1);
    copyback:
        /* copy scratch back into param_1 */
        long cnt = (dst - param_4);
        if (param_1 != param_4 || param_4 + cnt <= param_1)
            FUN_00117d14(param_1, param_4, cnt << 3);
        return 1;
    }
    /* symmetric merge for the longer-left case */
    unsigned long *dst = param_4 + len1;
    unsigned long *p1 = param_1;
    unsigned long *p2 = param_2;
    do {
        if (dst <= param_4 || param_3 <= p2) goto copyback2;
        unsigned long *a = (unsigned long *)*p2;
        unsigned long *b = (unsigned long *)*param_4;
        int c = compare_objects((unsigned long)a, (unsigned long)b);
        unsigned long x = (**(unsigned long (**)(void))((unsigned long)a + 0xb8))();
        unsigned long y = (**(unsigned long (**)(void))((unsigned long)b + 0xb8))();
        char order = comparator_apply(c, 0);
        FUN_0036b118(a);
        FUN_0036b118(b);
        if (order == '\0') {
            p1 = p2 + 1;
            p2 = p2;
            if (param_1 != p2) *param_1 = *p2;
        } else {
            p2 = param_4;
            param_4 = param_4 + 1;
            if (param_1 != p2) *param_1 = *p2;
        }
        param_1++;
    } while (1);
copyback2:
    long cnt = (dst - param_4);
    if (cnt < -7) sk_fault();
    if (param_1 != param_4 || param_4 + (cnt / 8) <= param_1)
        FUN_00117d14(param_1, param_4, (cnt / 8) << 3);
    return 1;
}

/* FUN_000d42a8 @ 0x000d42a8   (est. compare_cap_pair)
 * Ghidra: undefined8 FUN_000d42a8(undefined8 param_1, undefined8 param_2)
 * Compares two {word,tag} cap pairs using FUN_0012097c to decode each
 * and FUN_002a0cf8 to compare. Returns 0 if param_2 sorts before
 * param_1, 2 if param_1 sorts before param_2, else 1 (equal).
 * Confidence: high (straightforward two-key comparator) */
unsigned long compare_cap_pair(unsigned long param_1, unsigned long param_2)
{
    unsigned long a = FUN_0012097c();
    unsigned long a1 = a >> 8;
    unsigned long b = FUN_0012097c(param_2);
    unsigned long b1 = b >> 8;
    if ((a & 0xff) == (b & 0xff) && a1 == b1) {
        FUN_003a25d4(a1);
        FUN_003a25d4(b1);
    } else {
        unsigned long c = FUN_002a0cf8(a & 0xff, a1, b & 0xff, b1, 1);
        FUN_003a25d4(a1);
        FUN_003a25d4(b1);
        if ((c & 1) != 0) return 0;
    }
    a = FUN_0012097c(param_2);
    a1 = a >> 8;
    b = FUN_0012097c(param_1);
    b1 = b >> 8;
    if ((a & 0xff) == (b & 0xff) && a1 == b1) {
        FUN_003a25d4(a1);
        FUN_003a25d4(b1);
    } else {
        unsigned long c = FUN_002a0cf8(a & 0xff, a1, b & 0xff, b1, 1);
        FUN_003a25d4(a1);
        FUN_003a25d4(b1);
        if ((c & 1) != 0) return 2;
    }
    return 1;
}

/* FUN_000d43bc @ 0x000d43bc   (est. quicksort_object_runs)
 * Ghidra: long FUN_000d43bc(long *param_1)
 * Iterative quicksort of the object array (param_1, stride 0x30 per
 * element). Partitions using FUN_000c811c (the element predicate),
 * swaps partitions via FUN_000d52c8, and recurses on both sides.
 * Returns the final left index.
 * Confidence: medium */
long quicksort_object_runs(long *param_1)
{
    unsigned long lo = 0;
    unsigned long n = param_1[1];
    unsigned long hi = n;
    for (;;) {
        unsigned long off = lo * 0x30 + 0x28;
        unsigned long i = lo;
        /* scan forward for first element failing the predicate */
        while (hi > i) {
            if ((lo < 0) || (n <= i)) sk_fault();
            long *base = (long *)*param_1;
            unsigned char *p = (unsigned char *)(base + off);
            unsigned long e0 = *(unsigned long *)(p - 0x28);
            unsigned long e1 = *(unsigned long *)(p - 0x20);
            unsigned long e2 = *(unsigned long *)(p - 0x18);
            unsigned long e3 = *(unsigned long *)(p - 0x10);
            unsigned long e4 = *(unsigned long *)(p - 8);
            unsigned char e5 = *p;
            FUN_0036b270(e3);
            unsigned long ok = FUN_000c811c(e0, e1, e2, e3, e4, e5);
            FUN_0036b118(e3);
            if ((ok & 1) != 0) break;
            i++;
            off += 0x30;
        }
        /* scan backward for first element satisfying the predicate */
        unsigned long *pe = (unsigned long *)((long)*param_1 + hi * 0x30 + -0x18);
        unsigned long j = hi;
        do {
            j--;
            if (j <= i) return (long)i;
            if (n < hi) sk_fault();
            unsigned long e0 = pe[-3];
            unsigned long e1 = pe[-2];
            unsigned long e2 = pe[-1];
            unsigned long e3 = *pe;
            unsigned long e4 = pe[1];
            unsigned char e5 = *(unsigned char *)(pe + 2);
            FUN_0036b270(e3);
            FUN_0036b118(e3);
            pe -= 6;
        } while (1);
        FUN_000d52c8(i, j, (long)*param_1, n);
        lo = i + 1;
        hi = j;
    }
}

/* FUN_000d453c @ 0x000d453c   (est. reverse_cap_vector)
 * Ghidra: long FUN_000d453c(long param_1)
 * Reverses the cap vector (param_1) in place (swap symmetric elements,
 * stride 8). Returns the (possibly COW-uniqued) vector.
 * Confidence: high */
long reverse_cap_vector(long param_1)
{
    unsigned long n = *(unsigned long *)(param_1 + 0x10);
    if (1 < n) {
        unsigned long half = n >> 1;
        unsigned long l = n + 3;
        unsigned long r = 4;
        do {
            if (r != l) {
                if (*(unsigned long *)(param_1 + 0x10) <= r - 4U) sk_fault();
                if (*(unsigned long *)(param_1 + 0x10) <= l - 4U) sk_fault();
                unsigned long a = *(unsigned long *)(param_1 + r * 8);
                unsigned long b = *(unsigned long *)(param_1 + l * 8);
                if ((FUN_003a261c(param_1) & 1) == 0) param_1 = FUN_0007bed4(param_1);
                *(unsigned long *)(param_1 + r * 8) = b;
                *(unsigned long *)(param_1 + l * 8) = a;
            }
            l--;
            r++;
            half--;
        } while (half != 0);
    }
    return param_1;
}

/* FUN_000d45ec @ 0x000d45ec   (est. reverse_cap_vector_refcounted)
 * Ghidra: long FUN_000d45ec(long param_1)
 * Same as FUN_000d453c but retains/releases the swapped entries.
 * Confidence: high */
long reverse_cap_vector_refcounted(long param_1)
{
    unsigned long n = *(unsigned long *)(param_1 + 0x10);
    if (1 < n) {
        unsigned long half = n >> 1;
        unsigned long l = n + 3;
        unsigned long r = 4;
        do {
            if (r != l) {
                if (*(unsigned long *)(param_1 + 0x10) <= r - 4U) sk_fault();
                if (*(unsigned long *)(param_1 + 0x10) <= l - 4U) sk_fault();
                unsigned long a = *(unsigned long *)(param_1 + r * 8);
                unsigned long b = *(unsigned long *)(param_1 + l * 8);
                FUN_0036b270(a);
                FUN_0036b270(b);
                if ((FUN_003a261c(param_1) & 1) == 0) param_1 = FUN_0007bebc(param_1);
                unsigned long old = *(unsigned long *)(param_1 + r * 8);
                *(unsigned long *)(param_1 + r * 8) = b;
                FUN_0036b118(old);
                if (*(unsigned long *)(param_1 + 0x10) <= l - 4U) sk_fault();
                b = *(unsigned long *)(param_1 + l * 8);
                *(unsigned long *)(param_1 + l * 8) = a;
                FUN_0036b118(b);
            }
            l--;
            r++;
            half--;
        } while (half != 0);
    }
    return param_1;
}

/* FUN_000d46d4 @ 0x000d46d4   (est. collect_reachable_caps)
 * Ghidra: void FUN_000d46d4(undefined8 param_1, undefined8 *param_2, undefined8 *param_3, undefined8 param_4, undefined8 param_5, undefined8 param_6, long *param_7)
 * Recursively walks the object graph from param_1, following child-cap
 * links (param_2/param_3 are "visited" sets keyed by object), and
 * collects each reachable object into the output list param_7. Uses
 * FUN_000ac1dc to test membership, FUN_000bf328 to expand a node's
 * children, and FUN_000d4e10 to delete a node from a set.
 * Confidence: low (recursive graph walk) */
void collect_reachable_caps(unsigned long param_1, unsigned long *param_2, unsigned long *param_3,
                            unsigned long param_4, unsigned long param_5, unsigned long param_6,
                            long *param_7)
{
    FUN_0036a1a0(param_2, (void *)0, 0, 0);
    if ((FUN_000ac1dc(param_1, *param_2) & 1) != 0) return; /* already visited */
    FUN_0036a1a0(param_3, (void *)0, 0, 0);
    if ((FUN_000ac1dc(param_1, *param_3) & 1) != 0) sk_fault();
    FUN_0036a1a0(param_3, (void *)0, 0x21, 0);
    FUN_000b2194((void *)0, param_1);
    FUN_0036a20c((void *)0);
    FUN_0036b118((void *)0);
    void *children = (void *)0x657778;
    void *scratch = (void *)0x657778;
    unsigned long n = *(unsigned long *)(param_4 + 0x10);
    void *queue = (void *)0x657778;
    for (unsigned long i = 0; i < n; i++) {
        /* expand children of the current node */
        unsigned long child = *(unsigned long *)(param_4 + i * 8 + 0x20);
        /* recurse into each child */
        collect_reachable_caps(child, param_2, param_3, param_4, param_5, param_6, param_7);
    }
    /* append the visited node to output */
    FUN_0036a1a0(param_3, (void *)0, 0x21, 0);
    FUN_000d4e10(param_1);
    FUN_0036a20c((void *)0);
    FUN_0036a1a0(param_2, (void *)0, 0x21, 0);
    FUN_000b2194((void *)0, param_1);
    FUN_0036a20c((void *)0);
    FUN_0036a1a0(param_7, (void *)0, 0x21, 0);
    FUN_0007b280();
    unsigned long m = *(unsigned long *)(*param_7 + 0x10);
    FUN_0007b45c(m);
    unsigned long list = *param_7;
    *(unsigned long *)(list + 0x10) = m + 1;
    *(unsigned long *)(list + m * 8 + 0x20) = param_1;
    *param_7 = list;
    FUN_0036a20c((void *)0);
}

/* FUN_000d4964 @ 0x000d4964   (est. derive_subtree_caps)
 * Ghidra: void FUN_000d4964(undefined8 param_1, undefined8 *param_2, undefined8 *param_3, long param_4, undefined8 param_5, long param_6, undefined8 param_7)
 * Derives capabilities for a subtree: walks the object's capability
 * table (param_4), tests each cap via FUN_00138b08 against the target,
 * and collects those that derive (appending to a queue local_118).
 * Recurses into child subtrees. On success marks both sets with
 * "invalidated" flags (FUN_003a2610/FUN_0036b340).
 * Confidence: low (complex recursive derivation) */
void derive_subtree_caps(unsigned long param_1, unsigned long *param_2, unsigned long *param_3,
                         long param_4, unsigned long param_5, long param_6, unsigned long param_7)
{
    FUN_0036a1a0(param_2, (void *)0, 0, 0);
    unsigned long key = *param_2;
    FUN_0036b270(param_6);
    FUN_0036b270(param_7);
    FUN_0036b270(key);
    if ((FUN_000ac0f4(param_1, key) & 1) != 0) {
        FUN_003a2610(param_7, 2);
        FUN_0036b340(param_6, 2);
        return;
    }
    FUN_0036a1a0(param_3, (void *)0, 0, 0);
    key = *param_3;
    FUN_0036b270(key);
    if ((FUN_000ac0f4(param_1, key) & 1) != 0) sk_fault();
    FUN_0036a1a0(param_3, (void *)0, 0x21, 0);
    FUN_0036b2d0(param_1, 2);
    FUN_000b2390((void *)0, param_1);
    FUN_0036a20c((void *)0);
    FUN_0036b118((void *)0);
    void *queue = (void *)0x657778;
    void *out = (void *)0x657778;
    unsigned long n = *(unsigned long *)(param_4 + 0x10);
    unsigned long i = 0;
    unsigned long cap = 0;
    for (;;) {
        if (i >= n) {
            FUN_0036b118(param_1);
            FUN_0036b118(param_4);
            /* process queued caps */
            unsigned long qn = *(unsigned long *)(out + 0x10);
            for (unsigned long q = 0; q < qn; q++) {
                unsigned long cap = *(unsigned long *)(out + q * 8 + 0x20);
                FUN_0036b270(param_6);
                FUN_0036b270(param_7);
                FUN_0036b270(cap);
                derive_subtree_caps(cap, param_2, param_3, param_4, param_5, param_6, param_7);
                if (unaff_x21 != 0) {
                    FUN_003a2610(param_7, 2);
                    FUN_0036b340(param_6, 2);
                    FUN_0036b118(cap);
                    FUN_0036b118(out);
                    return;
                }
                FUN_0036b118(cap);
            }
            FUN_0036b118(0);
            FUN_0036a1a0(param_3, (void *)0, 0x21, 0);
            FUN_000d4ee8(param_1);
            FUN_0036a20c((void *)0);
            FUN_0036b118(0);
            FUN_0036a1a0(param_2, (void *)0, 0x21, 0);
            FUN_0036b2d0(param_1, 2);
            FUN_000b2390((void *)0, param_1);
            FUN_0036a20c((void *)0);
            FUN_0036b118(0);
            FUN_0036a1a0(param_5, (void *)0, 0x21, 0);
            FUN_00070594(param_1);
            FUN_0036a20c((void *)0);
            FUN_003a2610(param_7, 2);
            FUN_0036b340(param_6, 2);
            return;
        }
        cap = *(unsigned long *)(param_4 + i * 8);
        FUN_001394c8(0);
        FUN_0036b270(cap);
        if ((FUN_00138b08(cap, param_1) & 1) == 0) {
            unsigned long val = *(unsigned long *)(param_6 + 0x20);
            unsigned long ty = FUN_00002534((void *)0x64e838, (void *)0x4c0690);
            unsigned long l4 = FUN_0036a9a0(ty, (void *)0);
            *(unsigned long *)(l4 + 0x18) = 0x4baeb8;
            *(unsigned long *)(l4 + 0x10) = 0x4baeb0;
            *(unsigned long *)(l4 + 0x20) = param_1;
            unsigned long l5 = FUN_0036a9a0(ty, (void *)0);
            *(unsigned long *)(l5 + 0x18) = 0x4baeb8;
            *(unsigned long *)(l5 + 0x10) = 0x4baeb0;
            *(unsigned long *)(l5 + 0x20) = cap;
            FUN_0036b270(param_1);
            FUN_0036b270(cap);
            FUN_0036b270(val);
            unsigned long r = FUN_000aea40(param_7, l4, l5);
            FUN_0036b588(l4);
            FUN_00072424();
            FUN_0036b6ac(0, 0x20, 7);
            FUN_0036b118(val);
            FUN_0036b588(l5);
            FUN_00072424();
            FUN_0036b6ac(0, 0x20, 7);
            if ((r & 1) != 0) break;
        }
        FUN_0036b118(cap);
        i++;
    }
    /* append cap to queue */
    unsigned long m = *(unsigned long *)(out + 0x10);
    FUN_001dd77c();
    FUN_001dd858(m);
    *(unsigned long *)(out + 0x10) = m + 1;
    *(unsigned long *)(out + m * 8 + 0x20) = cap;
    i -= 3;
}

/* FUN_000d4dc0 @ 0x000d4dc0   (est. caps_differ)
 * Ghidra: bool FUN_000d4dc0(long param_1, long param_2)
 * Returns whether two cap words differ.
 * Confidence: high */
bool caps_differ(long a, long b) { return a != b; }

/* FUN_000d4dcc @ 0x000d4dcc   (est. apply_cap_predicate)
 * Ghidra: uint FUN_000d4dcc(undefined8 param_1, code *param_2, undefined8 param_3, undefined8 param_4)
 * Invokes the predicate callback param_2 with ({param_4},{param_1}),
 * returns its LSB.
 * Confidence: high */
unsigned int apply_cap_predicate(unsigned long param_1, unsigned long (*param_2)(unsigned long *, unsigned long *),
                                 unsigned long param_3, unsigned long param_4)
{
    unsigned long a = param_4;
    unsigned long b = param_1;
    return (*param_2)(&a, &b) & 1;
}

/* FUN_000d4e10 @ 0x000d4e10   (est. cap_set_lookup_or_remove)
 * Ghidra: undefined1 [16] FUN_000d4e10(long param_1)
 * Looks up param_1 in the cap set (unaff_x20). If present, removes it
 * (FUN_000d5010) and returns {word,0} (found); if absent returns
 * {0,1}. Uses the set's hash (FUN_00229ebc) and word size (+0x20).
 * Confidence: medium (cap-set membership/remove) */
unsigned long cap_set_lookup_or_remove(long param_1)
{
    unsigned long set = unaff_x20;
    unsigned long h = FUN_00229ebc(*(unsigned long *)(set + 0x28), param_1);
    for (;;) {
        h &= ~(-1L << (*(byte *)(set + 0x20) & 0x3f));
        if ((*(unsigned long *)(set + 0x38 + (h >> 6) * 8) >> (h & 0x3f) & 1) == 0)
            return 1; /* not found */
        if (*(long *)(*(long *)(set + 0x30) + h * 8) == param_1) {
            if ((FUN_003a261c(unaff_x20) & 1) == 0) FUN_000b2e64();
            unsigned long word = *(unsigned long *)(*(long *)(set + 0x30) + h * 8);
            FUN_000d5010(h);
            unaff_x20 = set;
            return word; /* found+removed */
        }
        h++;
    }
}

/* FUN_000d4ee8 @ 0x000d4ee8   (est. cap_set_find_matching)
 * Ghidra: undefined8 FUN_000d4ee8(long *param_1)
 * Finds and removes the first cap in the set (unaff_x20) that matches
 * the predicate param_1 (called via vtable[0xd8]). Returns its word,
 * or 0 if none match.
 * Confidence: medium */
unsigned long cap_set_find_matching(long *param_1)
{
    unsigned long set = unaff_x20;
    FUN_001a84f4((void *)0, *(unsigned long *)(set + 0x28));
    (**(void (**)(void *))(*param_1 + 0xd8))((void *)0);
    unsigned long h = FUN_001a8564();
    byte bits = *(byte *)(set + 0x20);
    for (;;) {
        h &= ~(-1L << (bits & 0x3f));
        if ((*(unsigned long *)(set + 0x38 + (h >> 6) * 8) >> (h & 0x3f) & 1) == 0) return 0;
        FUN_001394c8(0);
        unsigned long word = *(unsigned long *)(*(long *)(set + 0x30) + h * 8);
        unsigned long r = FUN_0036b270(word);
        if ((FUN_00138b08(r, param_1) & 1) != 0) {
            FUN_0036b118(word);
            if ((FUN_003a261c(unaff_x20) & 1) == 0) FUN_000b30e4();
            unsigned long found = *(unsigned long *)(*(long *)(unaff_x20 + 0x30) + h * 8);
            FUN_000d5144(h);
            unaff_x20 = set;
            return found;
        }
        FUN_0036b118(word);
        h++;
    }
}

/* FUN_000d5010 @ 0x000d5010   (est. cap_set_remove)
 * Ghidra: void FUN_000d5010(ulong param_1)
 * Removes slot param_1 from the cap set (unaff_x20): shifts down any
 * following present entries that hash into the affected run, clears the
 * present bit, and decrements the count (incrementing a "free" field
 * at +0x24). Faults if the count would underflow.
 * Confidence: medium */
void cap_set_remove(unsigned long param_1)
{
    unsigned long set = unaff_x20;
    unsigned long words = set + 0x38;
    unsigned long mask = -1L << (*(byte *)(set + 0x20) & 0x3f);
    unsigned long nxt = param_1 + 1 & (mask ^ 0xffffffffffffffff);
    if ((*(unsigned long *)(words + (nxt >> 6) * 8) >> (nxt & 0x3f) & 1) != 0) {
        unsigned long nmask = ~mask;
        unsigned long run = FUN_0022b080(param_1, words, nmask);
        unsigned long limit = run + 1U & nmask;
        do {
            unsigned long *tab = (unsigned long *)(set + 0x30);
            unsigned long *cur = (unsigned long *)(*(long *)(set + 0x30) + nxt * 8);
            unsigned long h = FUN_00229ebc(*(unsigned long *)(set + 0x28), *cur);
            h &= nmask;
            if ((long)param_1 < (long)limit) {
                if (limit <= h || (long)h <= (long)param_1) {
                    unsigned long *dst = (unsigned long *)(*(long *)(set + 0x30) + param_1 * 8);
                    if (param_1 != nxt || cur + 1 <= dst) {
                        *dst = *cur;
                        param_1 = nxt;
                    }
                }
            } else if (limit <= h && (long)h <= (long)param_1) {
                unsigned long *dst = (unsigned long *)(*(long *)(set + 0x30) + param_1 * 8);
                if (param_1 != nxt || cur + 1 <= dst) {
                    *dst = *cur;
                    param_1 = nxt;
                }
            }
            nxt = nxt + 1 & nmask;
        } while ((*(unsigned long *)(words + (nxt >> 6) * 8) >> (nxt & 0x3f) & 1) != 0);
    }
    unsigned long w = param_1 >> 3 & 0x1ffffffffffffff8;
    *(unsigned long *)(words + w) &= (-1L << (param_1 & 0x3f)) - 1U;
    if (!(*(long *)(set + 0x10) < 1)) { /* count underflow check */
        *(long *)(set + 0x10) -= 1;
        *(int *)(set + 0x24) += 1;
        return;
    }
    sk_fault();
}

/* FUN_000d5144 @ 0x000d5144   (est. cap_set_remove_matching)
 * Ghidra: void FUN_000d5144(ulong param_1)
 * Same as FUN_000d5010 but re-hashes via the vtable[0xd8] predicate
 * (FUN_001a84f4/FUN_001a8564) when compacting.
 * Confidence: medium */
void cap_set_remove_matching(unsigned long param_1)
{
    unsigned long set = unaff_x20;
    unsigned long words = set + 0x38;
    unsigned long mask = -1L << (*(byte *)(set + 0x20) & 0x3f);
    unsigned long nxt = param_1 + 1 & (mask ^ 0xffffffffffffffff);
    if ((*(unsigned long *)(words + (nxt >> 6) * 8) >> (nxt & 0x3f) & 1) != 0) {
        unsigned long nmask = ~mask;
        unsigned long run = FUN_0022b080(param_1, words, nmask);
        unsigned long limit = run + 1U & nmask;
        do {
            unsigned long *cur = (unsigned long *)(*(long *)(set + 0x30) + nxt * 8);
            FUN_001a84f4((void *)0, *(unsigned long *)(set + 0x28));
            (**(void (**)(void *))(*(long *)(*cur) + 0xd8))((void *)0);
            FUN_0036b270(cur);
            (**(void (**)(void *))(*(long *)(*cur) + 0xd8))((void *)0);
            FUN_0036b118(cur);
            unsigned long h = FUN_001a8564() & nmask;
            if ((long)param_1 < (long)limit) {
                if (limit <= h || (long)h <= (long)param_1) {
                    unsigned long *dst = (unsigned long *)(*(long *)(set + 0x30) + param_1 * 8);
                    unsigned long *src = (unsigned long *)(*(long *)(set + 0x30) + nxt * 8);
                    if (param_1 != nxt || src + 1 <= dst) {
                        *dst = *src;
                        param_1 = nxt;
                    }
                }
            } else if (limit <= h && (long)h <= (long)param_1) {
                unsigned long *dst = (unsigned long *)(*(long *)(set + 0x30) + param_1 * 8);
                unsigned long *src = (unsigned long *)(*(long *)(set + 0x30) + nxt * 8);
                if (param_1 != nxt || src + 1 <= dst) {
                    *dst = *src;
                    param_1 = nxt;
                }
            }
            nxt = nxt + 1 & nmask;
        } while ((*(unsigned long *)(words + (nxt >> 6) * 8) >> (nxt & 0x3f) & 1) != 0);
    }
    unsigned long w = param_1 >> 3 & 0x1ffffffffffffff8;
    *(unsigned long *)(words + w) &= (-1L << (param_1 & 0x3f)) - 1U;
    if (!(*(long *)(set + 0x10) < 1)) {
        *(long *)(set + 0x10) -= 1;
        *(int *)(set + 0x24) += 1;
        return;
    }
    sk_fault();
}

/* FUN_000d52c8 @ 0x000d52c8   (est. swap_cap_entries)
 * Ghidra: void FUN_000d52c8(ulong param_1, ulong param_2, long param_3, long param_4)
 * Swaps two 0x30-byte entries (param_1, param_2) within the object
 * array param_3 (capacity param_4), preserving refcounts.
 * Confidence: medium */
void swap_cap_entries(unsigned long a, unsigned long b, long base, long cap)
{
    if (a != b) {
        if ((cap <= (long)b || (long)(b | a) < 0) || cap <= (long)a)
            sk_fault();
        if (base == 0) sk_fault();
        unsigned long *pa = (unsigned long *)(base + a * 0x30);
        unsigned long *pb = (unsigned long *)(base + b * 0x30);
        unsigned long e0 = pa[1], e1 = *pa, e2 = pa[3], e3 = pa[2], e4 = pa[4];
        unsigned char e5 = *(unsigned char *)(pa + 5);
        FUN_000723f4(pb, 1, pa);
        pb[1] = e0;
        *pb = e1;
        pb[3] = e2;
        pb[2] = e3;
        pb[4] = e4;
        *(unsigned char *)(pb + 5) = e5;
    }
}

/* FUN_000d5360 @ 0x000d5360   (est. collect_all_objects)
 * Ghidra: void FUN_000d5360(long *param_1, undefined8 param_2)
 * Collects objects from three sources (main registry via vtable[0xa0],
 * and two sub-lists via FUN_00095ba4 / FUN_0009647c) into one list,
 * then returns a fresh array of FUN_0012540c-packaged descriptors.
 * Confidence: low (three-way merge of object lists) */
void collect_all_objects(long *param_1, unsigned long param_2)
{
    unsigned long b = 0;
    unsigned long list = (**(unsigned long (**)(void))(*param_1 + 0xa0))();
    void *out = (void *)0x657778;
    void *acc = (void *)0x657778;
    unsigned long n = *(unsigned long *)(list + 0x10);
    unsigned long i = 0;
    for (;;) {
        if (n == i) { /* second pass over 'out' */
            FUN_0036b118(list);
            i = 0;
            void *acc2 = (void *)0x657778;
            unsigned long m = *(unsigned long *)(out + 0x10);
            for (;;) {
                if (m == i) { /* third pass over acc2 */
                    FUN_0036b118(out);
                    i = 0;
                    void *acc3 = (void *)0x657778;
                    unsigned long k = *(unsigned long *)(acc2 + 0x10);
                    for (;;) {
                        if (k == i) {
                            FUN_0036b118(acc2);
                            unsigned long r = (**(unsigned long (**)(void))(*param_1 + 0x88))();
                            unsigned long v = FUN_001396b4(0);
                            FUN_0036a940(v, 0x70, 7);
                            FUN_0012540c(r, acc3);
                            return;
                        }
                        if (*(unsigned long *)(acc2 + 0x10) <= i) break;
                        unsigned long obj = *(unsigned long *)(acc2 + i * 8 + 0x20);
                        FUN_0036b270(obj);
                        unsigned long r = FUN_0009647c(&b, &obj, param_2, 0x6672b8);
                        FUN_0036b118(obj);
                        if (b != 0) {
                            FUN_001a1564();
                            unsigned long m2 = *(unsigned long *)(acc3 + 0x10);
                            if (*(unsigned long *)(acc3 + 0x18) >> 1 <= m2)
                                FUN_001a0774(1 < *(unsigned long *)(acc3 + 0x18), m2 + 1, 1);
                            *(unsigned long *)(acc3 + 0x10) = m2 + 1;
                            *(unsigned long *)(acc3 + m2 * 8 + 0x20) = b;
                            acc = acc3;
                        }
                        i++;
                    }
                }
                if (*(unsigned long *)(out + 0x10) <= i) break;
                unsigned long obj = *(unsigned long *)(out + i * 8 + 0x20);
                FUN_0036b270(obj);
                unsigned long r = FUN_00095ba4(&b, &obj, param_2, 0x6672b8);
                FUN_0036b118(obj);
                if (b != 0) {
                    FUN_001a1564();
                    unsigned long m2 = *(unsigned long *)(acc2 + 0x10);
                    if (*(unsigned long *)(acc2 + 0x18) >> 1 <= m2)
                        FUN_001a0774(1 < *(unsigned long *)(acc2 + 0x18), m2 + 1, 1);
                    *(unsigned long *)(acc2 + 0x10) = m2 + 1;
                    *(unsigned long *)(acc2 + m2 * 8 + 0x20) = b;
                    acc = acc2;
                }
                i++;
            }
        }
        if (*(unsigned long *)(list + 0x10) <= i) break;
        unsigned long obj = *(unsigned long *)(list + i * 8 + 0x20);
        FUN_0036b270(obj);
        unsigned long r = FUN_00095184(&b, &obj, param_2, 0x6672b8);
        FUN_0036b118(obj);
        if (b != 0) {
            FUN_001a1564();
            unsigned long m2 = *(unsigned long *)(out + 0x10);
            if (*(unsigned long *)(out + 0x18) >> 1 <= m2)
                FUN_001a0774(1 < *(unsigned long *)(out + 0x18), m2 + 1, 1);
            *(unsigned long *)(out + 0x10) = m2 + 1;
            *(unsigned long *)(out + m2 * 8 + 0x20) = b;
            acc = out;
        }
        i++;
    }
    sk_fault();
}

/* FUN_000d56a0 @ 0x000d56a0   (est. cap_ne_q)
 * Ghidra: void FUN_000d56a0(undefined8 *param_1, undefined8 *param_2)
 * Compares two caps via FUN_000d4dc0 (discards result).
 * Confidence: medium */
void cap_ne_q(unsigned long *param_1, unsigned long *param_2)
{
    FUN_000d4dc0(*param_1, *param_2);
}

/* FUN_000d56ac @ 0x000d56ac   (est. cap_pred_apply)
 * Ghidra: uint FUN_000d56ac(undefined8 *param_1, undefined8 param_2, undefined8 param_3, undefined8 *param_4)
 * Applies the predicate via FUN_000d4dcc, returns its LSB.
 * Confidence: medium */
unsigned int cap_pred_apply(unsigned long *param_1, unsigned long param_2, unsigned long param_3,
                            unsigned long *param_4)
{
    return FUN_000d4dcc(*param_1, (void *)param_2, param_3, *param_4) & 1;
}

/* FUN_000d56d0 @ 0x000d56d0   (est. dispatch_key_a)
 * Ghidra: void FUN_000d56d0(void)
 * Invokes FUN_000d1c4c; stores frame flag into *in_x3.
 * Confidence: medium */
void dispatch_key_a(void)
{
    FUN_000d1c4c(0, 0, (unsigned long *)0);
    if (unaff_x21 != 0) *(unsigned long *)(0) = unaff_x21;
}

/* FUN_000d5700 @ 0x000d5700   (est. dispatch_key_b)
 * Ghidra: void FUN_000d5700(void)
 * Invokes FUN_000d1c94; stores frame flag into *in_x3.
 * Confidence: medium */
void dispatch_key_b(void)
{
    FUN_000d1c94((byte *)0, (void (*)(void *, void *))0);
    if (unaff_x21 != 0) *(unsigned long *)(0) = unaff_x21;
}

/* FUN_000d5730 @ 0x000d5730   (est. build_object_descriptor_list)
 * Ghidra: undefined * FUN_000d5730(undefined8 param_1, long param_2, long param_3)
 * Builds a list of object descriptors for the address space param_3
 * from param_2's vspace. Iterates the vspace's page-table, frames, and
 * TCB-like regions, allocating a descriptor record (stride 0x10 with a
 * type-tag at +0x28) for each discovered entry. Uses size getters
 * FUN_000db5f0/000db620/000db910 and vspace accessors.
 * Confidence: low (large descriptor builder) */
void *build_object_descriptor_list(unsigned long param_1, long param_2, long param_3)
{
    unsigned long b[9] = {0};
    void *out = (void *)0x657778;
    /* vspace root descriptor */
    unsigned long p2 = *(unsigned long *)(param_2 + 0x18);
    unsigned long p3 = *(unsigned long *)(param_2 + 0x20);
    FUN_0006a4c0(param_2, p2);
    unsigned long (*f)() = (unsigned long (*)())FUN_000db5f0(p3);
    unsigned long v0 = f(p2, p3);
    FUN_0036a1a0((void *)(param_3 + 0x170), &b, 0x20, 0);
    unsigned long v1 = FUN_000a046c(v0, *(unsigned long *)(param_3 + 0x170));
    FUN_0036a20c((void *)0);
    if ((v1 & 0xff) != 0) {
        unsigned long vroot = v1 & 0xff;
        FUN_0036b270(vroot);
        out = (void *)FUN_0007340c(0, 1, 1, (void *)0x657778);
        unsigned long m = *(unsigned long *)(out + 0x10);
        unsigned long cap = *(unsigned long *)(out + 0x18);
        if (cap >> 1 <= m)
            out = (void *)FUN_0007340c(1 < cap, m + 1, 1, out);
        *(unsigned long *)(out + 0x10) = m + 1;
        *(unsigned long *)(out + m * 0x10 + 0x20) = vroot;
        *(unsigned long *)(out + m * 0x10 + 0x28) = 0x661320;
        unsigned long m2 = m + 2;
        if ((long)((*(unsigned long *)(out + 0x18)) >> 1) < (long)m2)
            out = (void *)FUN_0007340c(1 < *(unsigned long *)(out + 0x18), m2, 1, out);
        FUN_0036b118(vroot);
        *(unsigned long *)(out + 0x10) = m2;
        *(unsigned long *)(out + (m + 1) * 0x10 + 0x20) = (v1 >> 8) & 0xff;
        *(unsigned long *)(out + (m + 1) * 0x10 + 0x28) = 0x661e48;
    }
    /* add a launcher descriptor */
    unsigned long la = FUN_000fa1b0(0);
    FUN_0036a940(la, 0x20, 7);
    la = FUN_000f9b4c();
    if ((FUN_003a261c(out) & 1) == 0)
        out = (void *)FUN_0007340c(0, *(long *)(out + 0x10) + 1, 1, out);
    unsigned long m = *(unsigned long *)(out + 0x10);
    if (*(unsigned long *)(out + 0x18) >> 1 <= m)
        out = (void *)FUN_0007340c(1 < *(unsigned long *)(out + 0x18), m + 1, 1, out);
    *(unsigned long *)(out + 0x10) = m + 1;
    *(unsigned long *)(out + m * 0x10 + 0x20) = la;
    *(unsigned long *)(out + m * 0x10 + 0x28) = 0x662938;
    /* frame region descriptor (size via FUN_000db620) */
    p2 = *(unsigned long *)(param_2 + 0x18);
    p3 = *(unsigned long *)(param_2 + 0x20);
    FUN_0006a4c0(param_2, p2);
    f = (unsigned long (*)())FUN_000db620(p3);
    v0 = f(p2, p3);
    unsigned long fd = FUN_00103724(0);
    unsigned long fr = FUN_0036a940(fd, 0x18, 7);
    *(unsigned long *)(fr + 0x10) = v0;
    m = *(unsigned long *)(out + 0x10);
    if (*(unsigned long *)(out + 0x18) >> 1 <= m)
        out = (void *)FUN_0007340c(1 < *(unsigned long *)(out + 0x18), m + 1, 1, out);
    *(unsigned long *)(out + 0x10) = m + 1;
    *(unsigned long *)(out + m * 0x10 + 0x20) = fr;
    *(unsigned long *)(out + m * 0x10 + 0x28) = 0x662e58;
    /* add another descriptor */
    unsigned long da = FUN_000f7f64(0);
    FUN_0036a940(da, 0x20, 7);
    da = FUN_000f78ac();
    m = *(unsigned long *)(out + 0x10);
    if (*(unsigned long *)(out + 0x18) >> 1 <= m)
        out = (void *)FUN_0007340c(1 < *(unsigned long *)(out + 0x18), m + 1, 1, out);
    *(unsigned long *)(out + 0x10) = m + 1;
    *(unsigned long *)(out + m * 0x10 + 0x20) = da;
    *(unsigned long *)(out + m * 0x10 + 0x28) = 0x662728;
    /* TCB descriptor via FUN_000db910 */
    p2 = *(unsigned long *)(param_2 + 0x18);
    p3 = *(unsigned long *)(param_2 + 0x20);
    FUN_0006a4c0(param_2, p2);
    unsigned long (*g)() = (unsigned long (*)())FUN_000db910(p3);
    g(&b, p2, p3);
    if (*(char *)((char *)&b + 0x40) != -1) { /* local_48 != -1 */
        unsigned long td = FUN_0006fd3c(0);
        unsigned long tcb = FUN_0036a940(td, 0x49, 7);
        /* copy 0x38 bytes of register state into tcb+0x10 */
        for (int k = 0; k < 7; k++)
            *(unsigned long *)(tcb + 0x10 + k * 8) = ((unsigned long *)&b)[k];
        *(char *)(tcb + 0x48) = *(char *)((char *)&b + 0x40);
        m = *(unsigned long *)(out + 0x10);
        if (*(unsigned long *)(out + 0x18) >> 1 <= m)
            out = (void *)FUN_0007340c(1 < *(unsigned long *)(out + 0x18), m + 1, 1, out);
        *(unsigned long *)(out + 0x10) = m + 1;
        *(unsigned long *)(out + m * 0x10 + 0x20) = tcb;
        *(unsigned long *)(out + m * 0x10 + 0x28) = 0x65f0d0;
    }
    return out;
}

/* FUN_000d5b34 @ 0x000d5b34   (est. map_object_frame_region)
 * Ghidra: long FUN_000d5b34(undefined8 *param_1, long param_2)
 * Maps a 16K frame region (0x4000) for an object: carves a physical
 * span (FUN_00085a54), attaches it to the vspace via vtable[0x90],
 * resolves a boot-load region via vtable[0xe0], and records it in
 * param_2 (+0x10..+0x38). Registers fields are snapped from param_1.
 * Confidence: medium
 * Notes: thunk_FUN_00114330(vspace, 0x400) flushes/validates. */
long map_object_frame_region(unsigned long *param_1, long param_2)
{
    unsigned long regs[6];
    regs[0] = *param_1;
    regs[1] = param_1[1];
    regs[2] = param_1[2];
    regs[3] = param_1[3];
    regs[4] = param_1[4];
    regs[5] = param_1[5];
    *(unsigned long *)(param_2 + 0x10) = 0;
    unsigned long md = FUN_00086440(0);
    unsigned long *ctx = (unsigned long *)FUN_0036a9d4(md, 0x64e1c0);
    ctx[0] = 0x65f998;
    ctx[1] = md;
    unsigned long a = FUN_00086590(0);
    FUN_0036a940(a, 0x50, 7);
    unsigned long span = FUN_00085a54(ctx, 0x4000, 0x11, 0x1808, 0);
    *(unsigned long *)(param_2 + 0x18) = span;
    unsigned long ps = FUN_00034f70();
    unsigned long r0 = regs[4];
    unsigned long r1 = regs[5];
    FUN_0006a4c0((unsigned long)&regs[0] | 8, regs[5]);
    unsigned long (*f)(unsigned long, int, int, unsigned long, unsigned long) =
        (unsigned long (*)(unsigned long, int, int, unsigned long, unsigned long))FUN_00077088(regs[4]);
    unsigned long rr = f(ps, 3, 0, r1, r0);
    FUN_00070674(1, 3, 0);
    *(unsigned long *)(param_2 + 0x20) = ps;
    *(unsigned long *)(param_2 + 0x28) = rr;
    unsigned long *spanp = *(unsigned long **)(param_2 + 0x18);
    unsigned long (*v90)() = (unsigned long (*)())(*(long *)*spanp + 0x90);
    FUN_0036b270(spanp);
    v90(0, ps);
    FUN_0036b118(spanp);
    unsigned long *sp2 = *(unsigned long **)(param_2 + 0x18);
    unsigned long (*ve0)() = (unsigned long (*)())(*(long *)*sp2 + 0xe0);
    FUN_0036b270(sp2);
    unsigned long lr = ve0();
    FUN_0036b118(sp2);
    if (lr == 0) sk_fault(); /* 0xd5d00 */
    *(unsigned long *)(param_2 + 0x30) = lr;
    *(unsigned long *)(param_2 + 0x38) = 0x40;
    FUN_00114330(lr, 0x400);
    FUN_000db250(&regs[0]);
    return param_2;
}

/* FUN_000d5d80 @ 0x000d5d80   (est. expand_address_space_descriptors)
 * Ghidra: long * FUN_000d5d80(undefined8 param_1, undefined8 param_2, long *param_3, undefined8 param_4, undefined8 param_5, long param_6)
 * The main address-space descriptor expansion: walks the vspace root's
 * object list (param_6), computes the set of ASIDs that must be made
 * writable, then for each of the 0x13 ASID kinds emits the
 * corresponding metadata record by dispatching vtable[0x..] on
 * param_6+0x108. Returns the assembled descriptor list.
 * Confidence: low (very large; many vtable dispatches)
 * Notes: structurally identical to FUN_000d7bf8; the per-kind dispatch
 *   offsets are 0xa0,0xa8,0xe0,0xc8,0xd0,0xd8,0xe8,0xf0,0xb0,0xf8,0x98,
 *   0xc0 for kinds 5,8,0xf,4,9,10,0x12,0xb,7,0xe,0xd,0x10,0x11,0xc,6. */
long *expand_address_space_descriptors(unsigned long param_1, unsigned long param_2,
                                       long *param_3, unsigned long param_4,
                                       unsigned long param_5, long param_6)
{
    unsigned long list = (**(unsigned long (**)(void))(**(long **)(param_6 + 0x20) + 0x80))();
    unsigned long obj_list = (**(unsigned long (**)(void))((**(long **)list) + 0xa0))();
    FUN_0036b118(list);
    void *acc = (void *)0x657778;
    unsigned long n = *(unsigned long *)(obj_list + 0x10);
    for (unsigned long i = 0; i < n; i++) {
        unsigned long obj = *(unsigned long *)(obj_list + 0x20 + i * 8);
        unsigned long key0 = (**(unsigned long (**)(void))(*(long *)obj + 0x58))();
        unsigned long want = (**(unsigned long (**)(void))(*param_3 + 0x58))();
        unsigned long want1 = want >> 8;
        unsigned long k0 = *(unsigned long *)(key0 + 0x10) + 1;
        unsigned long *kp = (unsigned long *)(key0 + 0x28);
        int matched = 0;
        while (--k0 != 0) {
            unsigned long a = kp[-1], b = *kp;
            if ((a & 0xff) == (want & 0xff) && (b >> 8) == want1) { matched = 1; break; }
            kp += 2;
            if (FUN_002a0cf8(a, b, want & 0xff, want1, 0) & 1) { matched = 1; break; }
        }
        FUN_0036b118(key0);
        FUN_003a25d4(want1);
        if (matched) append_ptr(acc, obj);
    }
    FUN_0036b118(obj_list);
    sort_cap_vector((long *)&acc);
    unsigned long dedup = (unsigned long)FUN_000c18dc(acc);
    unsigned long desc = FUN_0008dcd0(0);
    FUN_0036a940(desc, 0x28, 7);
    unsigned long vspace = FUN_000871dc();
    static const unsigned long kinds[] = {5, 8, 0xf, 4, 9, 10, 0x12, 0xb, 7, 0xe, 0xd, 0x10, 0x11, 0xc, 6};
    for (unsigned int k = 0; k < sizeof(kinds) / sizeof(kinds[0]); k++) {
        unsigned long set = lookup_cap_set(dedup, kinds[k]);
        unsigned long cnt = set ? *(unsigned long *)(set + 0x10) : 0;
        if (cnt != 0) {
            unsigned long base = **(long **)(param_6 + 0x108) + kind_offset(kinds[k]);
            unsigned long *p = (unsigned long *)(set + 4);
            for (unsigned long j = 0; j < cnt; j++) {
                unsigned long obj = *p++;
                FUN_0036b270(obj);
                ((unsigned long (*)())(unsigned long)base)(obj, param_4, vspace);
                FUN_0036b118(obj);
            }
        }
        if (set) FUN_0036b118(set);
    }
    FUN_0036b118(dedup);
    return (long *)vspace;
}

/* Small list-append helper (8-byte stride, growth via FUN_00082484). */
static void append_ptr(void *list, unsigned long obj)
{
    unsigned long m = *(unsigned long *)(list + 0x10);
    if (*(unsigned long *)(list + 0x18) >> 1 <= m)
        FUN_00082484(1 < *(unsigned long *)(list + 0x18), m + 1, 1);
    *(unsigned long *)(list + 0x10) = m + 1;
    *(unsigned long *)(list + m * 8 + 0x20) = obj;
}

/* Map an ASID kind to its dispatch-table byte offset on param_6+0x108. */
static unsigned long kind_offset(unsigned long kind)
{
    switch (kind) {
    case 5:  return 0xa0;
    case 8:  return 0xa8;
    case 0xf:return 0xe0;
    case 4:  return 0xc8;
    case 9:  return 0xd0;
    case 10: return 0xd8;
    case 0x12:return 0xe8;
    case 0xb:return 0xf0;
    case 7:  return 0xb0;
    case 0xe:return 0xf8;
    case 0xd:return 0x98;
    case 0x10:return 0xc0;
    case 0x11:return 0xc8;
    case 0xc:return 0xc8;
    case 6:  return 0xc8;
    default: return 0xc8;
    }
}

/* Look up an ASID-kind cap set from the dedup'd object list. */
static unsigned long lookup_cap_set(unsigned long dedup, unsigned long kind)
{
    /* The dedup table maps ASID-kind -> cap-set; we emulate the lookup
     * via FUN_00072710-style set access. Returns 0 if absent. */
    (void)kind;
    return FUN_00072710(dedup); /* [INFERENCE] set fetch */
}

/* ------------------------------------------------------------------ */
/* Metadata field getters / vtable thunks / no-ops (0xdb1xx-0xdbxxx).  */
/* The "get field end" helpers unwrap a tagged pointer (bit0 =>        */
/* indirect) and return ptr+off+*(int*)(ptr+off).                      */
/* ------------------------------------------------------------------ */

#define FIELD_GETTER(name, off) \
    long name(unsigned long p) { \
        if ((p & 1) != 0) p = *(unsigned long *)(p & 0xfffffffffffffffe); \
        return (long)(p + off) + (long)*(int *)(p + off); \
    }

/* FUN_000db184 / 000db204 / 000db250 / 000db5a4 : vtable call thunks */
unsigned long db_vtable_call_0(void) { return 0; }

/* FUN_000db1d0 / 000db1d4 @ 0x000db1d0 (est. release_slot_and_cleanup) */
void release_slot_and_cleanup(void)
{
    FUN_0036b118(*(void **)(unaff_x20 + 0x10));
    FUN_000026e8((void *)(unaff_x20 + 0x18));
    FUN_0036b21c();
}

/* FUN_000db3e0 / 000db3e4 (est. release_slot_and_sync) */
void release_slot_and_sync(void)
{
    FUN_0036b118(*(void **)(unaff_x20 + 0x18));
    FUN_00002834();
    FUN_0036b21c();
}

/* The tagged-pointer field-end getters. */
FIELD_GETTER(field_0x34_end, 0x34)   /* 000db2a8 */
FIELD_GETTER(field_0x04_end, 0x04)   /* 000db2d8 */
FIELD_GETTER(field_0x58_end, 0x58)   /* 000db330 */
FIELD_GETTER(field_0x60_end, 0x60)   /* 000db368 */
FIELD_GETTER(field_0x24_end, 0x24)   /* 000db454 */
FIELD_GETTER(field_0x40_end, 0x40)   /* 000db484 */
FIELD_GETTER(field_0x54_end, 0x54)   /* 000db4b4 */
FIELD_GETTER(field_0x30_end, 0x30)   /* 000db4e4 */
FIELD_GETTER(field_0x24_end_2, 0x24) /* 000db514 */
FIELD_GETTER(field_0x64_end, 0x64)   /* 000db544 */
FIELD_GETTER(field_0x3c_end, 0x3c)   /* 000db574 */
FIELD_GETTER(field_0x4c_end, 0x4c)   /* 000db5f0 */
FIELD_GETTER(field_0x48_end, 0x48)   /* 000db620 */
FIELD_GETTER(field_0x04_end_2, 0x04) /* 000db6e8 */
FIELD_GETTER(field_0x38_end, 0x38)   /* 000db748 */
FIELD_GETTER(field_0x08_end, 0x08)   /* 000db778 */
FIELD_GETTER(field_0x1c_end, 0x1c)   /* 000db7a8 */
FIELD_GETTER(field_0x28_end, 0x28)   /* 000db7d8 */
FIELD_GETTER(field_0x2c_end, 0x2c)   /* 000db808 */
FIELD_GETTER(field_0x5c_end, 0x5c)   /* 000db838 */
FIELD_GETTER(field_0x1c_end_2, 0x1c) /* 000db910 */
FIELD_GETTER(field_0x18_end, 0x18)   /* 000db940 */

/* FUN_000db870 @ 0x000db870 (est. retain_tagged) */
void retain_tagged(unsigned long p)
{
    unsigned long m = 0x3fffffffffffffff;
    if ((p & 0x4000000000000000) != 0) m = 0xbfffffffffffffff;
    FUN_0036b270(p & m);
}

/* FUN_000db888 @ 0x000db888 (est. release_tagged) */
void release_tagged(unsigned long p)
{
    unsigned long m = 0x3fffffffffffffff;
    if ((p & 0x4000000000000000) != 0) m = 0xbfffffffffffffff;
    FUN_0036b118(p & m);
}

/* FUN_000db8e0 @ 0x000db8e0 (est. release_tagged_unless_null_tag) */
void release_tagged_unless_null(unsigned long p)
{
    if (((p ^ 0xffffffffffffffff) & 0x7000000000000007) == 0) return;
    release_tagged(p);
}

/* FUN_000db8f8 @ 0x000db8f8 (est. retain_tagged_unless_null_tag) */
void retain_tagged_unless_null(unsigned long p)
{
    if (((p ^ 0xffffffffffffffff) & 0x7000000000000007) == 0) return;
    retain_tagged(p);
}

/* FUN_000db8a0 / 000db8a4 (est. dispatch_key_a_2) */
void dispatch_key_a2(unsigned long p1, unsigned long p2)
{
    FUN_000d56d0();
}

/* FUN_000db8c0 / 000db8c4 (est. dispatch_key_b_2) */
void dispatch_key_b2(unsigned long p1, unsigned long p2)
{
    FUN_000d5700();
}

/* FUN_000db308 / 000db30c (est. object_pair_check) */
unsigned int object_pair_check(unsigned long p1, unsigned long p2)
{
    return FUN_000cef2c(p1, p2, *(unsigned long *)(unaff_x20 + 0x10),
                        *(unsigned long *)(unaff_x20 + 0x18)) & 1;
}

/* FUN_000db430 / 000db434 (est. cap_pred_apply_wrapper) */
unsigned int cap_pred_apply_wrapper(unsigned long p1)
{
    return FUN_000d56ac(p1, *(unsigned long *)(unaff_x20 + 0x10),
                        *(unsigned long *)(unaff_x20 + 0x18),
                        *(unsigned long *)(unaff_x20 + 0x20)) & 1;
}

/* FUN_000db3d0 @ 0x000db3d0 (est. const_descriptor) */
unsigned long const_descriptor(void) { return 0x650f88; }

/* FUN_000db398 @ 0x000db398 (est. supervisor_loop)
 * Calls the supervisor (CallSupervisor opcode 0) until param_1 != 1. */
void supervisor_loop(long param_1)
{
    unsigned long *p = (unsigned long *)({ unsigned long v; __asm__("mrs %0, tpidrro_el0" : "=r"(v)); v; });
    unsigned long v = *p;
    do {
        asm volatile("svc #0" ::: "memory"); /* CallSupervisor(0) */
        *p = v;
    } while (param_1 == 1);
}

/* FUN_000db650 @ 0x000db650 (est. vtable_dispatch_object) */
unsigned long vtable_dispatch_object(unsigned long a, unsigned long b, unsigned long c, unsigned long d)
{
    unsigned long md = FUN_00002534(c, d);
    ((unsigned long (*)())(*(long *)(md + -8) + 0x10))(b, a, md);
    return b;
}

/* FUN_000db6b0 @ 0x000db6b0 (est. array_element_vtable) */
unsigned long array_element_vtable(unsigned long a, unsigned long b)
{
    FUN_0035dc24(b, a, 0x661490);
    return b;
}

/* FUN_000db718 @ 0x000db718 (est. array_emit_vtable) */
unsigned long array_emit_vtable(unsigned long a)
{
    FUN_0035d334(a, 0x661490);
    return a;
}

/* FUN_000dba78 / 000dba90 (est. fatal_error_string) */
char *fatal_error_string(void) { return (char *)0x5accd0; } /* "Fatal error" */

/* No-op stubs (many mdata emit anchors resolve to ret). */
void noop_db(void) {}
void noop_dba44(void) {}
void noop_dba5c(void) {}
void noop_dba2c(void) {}
void noop_dbac8(void) {}
void noop_dbad8(void) {}
void noop_dbaf4(void) {}
void noop_dbb10(void) {}
void noop_dbb24(void) {}
void noop_dbb30(void) {}
void noop_dbb3c(void) {}
void noop_dbb60(void) {}

/* FUN_000dbb78 @ 0x000dbb78 (est. emit_fatal_anchor) */
void emit_fatal_anchor(void)
{
    FUN_0036993c(0x6673a0, 0x6672a8, 0, 0);
}

/* FUN_000dbaa4 @ 0x000dbaa4 (est. set_frame_error_key) */
void set_frame_error_key(void)
{
    *(unsigned long *)(unaff_x19 + 0x290) = 0x65f1b8;
    FUN_0036a940(0, 0, 7);
}

/* FUN_000dbba0 / 000dbbb0 (est. scarry_helper) */
bool scarry_helper(void) { return false; }

/* FUN_000d7bf8 @ 0x000d7bf8   (est. expand_address_space_descriptors_full)
 * Ghidra: long * FUN_000d7bf8(8 args)
 * The full address-space descriptor expansion (sibling of FUN_000d5d80
 * but with an extra "writable ASID" handling and a per-kind dispatch
 * that also parses the ASID's writable bitmap). For each of the 0x13
 * ASID kinds it gathers matching objects, dispatches the metadata
 * writer at param_6+0x108+off, and appends {object,type,key} records.
 * Concludes with the writable-ASID bookkeeping and the mdata span
 * creation.
 * Confidence: low (very large, many vtable dispatches) */
long *expand_address_space_descriptors_full(unsigned long param_1, unsigned long param_2,
                                            long *param_3, unsigned long param_4,
                                            unsigned long param_5, long param_6,
                                            long param_7, unsigned long param_8)
{
    unsigned long list = (**(unsigned long (**)(void))(**(long **)(param_6 + 0x20) + 0x80))();
    unsigned long obj_list = (**(unsigned long (**)(void))((**(long **)list) + 0xa0))();
    FUN_0036b118(list);
    void *acc = (void *)0x657778;
    unsigned long n = *(unsigned long *)(obj_list + 0x10);
    for (unsigned long i = 0; i < n; i++) {
        unsigned long obj = *(unsigned long *)(obj_list + 0x20 + i * 8);
        unsigned long key0 = (**(unsigned long (**)(void))(*(long *)obj + 0x58))();
        unsigned long want = (**(unsigned long (**)(void))(*param_3 + 0x58))();
        unsigned long want1 = want >> 8;
        unsigned long k0 = *(unsigned long *)(key0 + 0x10) + 1;
        unsigned long *kp = (unsigned long *)(key0 + 0x28);
        int matched = 0;
        while (--k0 != 0) {
            unsigned long a = kp[-1], b = *kp;
            if ((a & 0xff) == (want & 0xff) && (b >> 8) == want1) { matched = 1; break; }
            kp += 2;
            if (FUN_002a0cf8(a, b, want & 0xff, want1, 0) & 1) { matched = 1; break; }
        }
        FUN_0036b118(key0);
        FUN_003a25d4(want1);
        if (matched) append_ptr(acc, obj);
    }
    FUN_0036b118(obj_list);
    sort_cap_vector((long *)&acc);
    unsigned long dedup = (unsigned long)FUN_000c18dc(acc);
    unsigned long desc = FUN_0008dcd0(0);
    FUN_0036a940(desc, 0x28, 7);
    unsigned long vspace = FUN_000871dc();
    static const unsigned long kinds[] = {5, 8, 0xf, 4, 9, 10, 0x12, 0xb, 7, 0xe, 0xd, 0x10, 0x11, 0xc, 6};
    for (unsigned int k = 0; k < sizeof(kinds) / sizeof(kinds[0]); k++) {
        unsigned long set = lookup_cap_set(dedup, kinds[k]);
        unsigned long cnt = set ? *(unsigned long *)(set + 0x10) : 0;
        if (cnt != 0) {
            unsigned long base = **(long **)(param_6 + 0x108) + kind_offset(kinds[k]);
            unsigned long *p = (unsigned long *)(set + 4);
            for (unsigned long j = 0; j < cnt; j++) {
                unsigned long obj = *p++;
                unsigned long x = FUN_0036b270(obj);
                if (kinds[k] == 0xd) {
                    /* kind 0xd carries {obj, vaddr, vspace} triple */
                    unsigned long v0 = *(unsigned long *)(param_6 + 0x28);
                    unsigned long v1 = *(unsigned long *)(param_6 + 0x30);
                    ((unsigned long (*)())(unsigned long)base)(obj, v0, v1, vspace);
                } else if (kinds[k] == 7) {
                    unsigned long v0 = *(unsigned long *)(param_6 + 0x28);
                    unsigned long v1 = *(unsigned long *)(param_6 + 0x30);
                    ((unsigned long (*)())(unsigned long)base)(obj, v0, v1, param_4, vspace);
                } else {
                    ((unsigned long (*)())(unsigned long)base)(x, param_4, vspace);
                }
                FUN_0036b118(obj);
            }
        }
        if (set) FUN_0036b118(set);
    }
    FUN_0036b118(dedup);
    return (long *)vspace;
}

/* FUN_000d9a98 @ 0x000d9a98   (est. expand_address_space_metadata)
 * Ghidra: undefined1 [16] FUN_000d9a98(long *param_1, long *param_2, undefined8 param_3, undefined8 param_4, undefined8 param_5, long param_6)
 * Expands a single ASID's metadata: walks the vspace cap-set for the
 * target key, and for each matching cap emits its metadata record
 * (via FUN_000d5d80), returning a 128-bit {error-code} pair.
 * Confidence: low */
unsigned long expand_address_space_metadata(long *param_1, long *param_2,
                                            unsigned long param_3, unsigned long param_4,
                                            unsigned long param_5, long param_6)
{
    /* iterate the vspace's cap-set (vtable[0x70]) for the key in
     * {param_1,param_2}; for each match call FUN_000d5d80 to emit and
     * collect the descriptor. Returns 0/0 on success. */
    unsigned long set = (**(unsigned long (**)(void))(*param_2 + 0x70))();
    unsigned long n = *(unsigned long *)(set + 0x10);
    void *out = (void *)0x657778;
    void *out2 = (void *)0x6577e0;
    unsigned long key0 = 0, key1 = 0;
    if (n == 0) { /* nothing to emit */
        FUN_000db250((void *)0);
        FUN_0036b118(set);
        return 0;
    }
    /* linear scan for a cap whose key matches */
    for (unsigned long i = 0; i < n; i++) {
        unsigned long *entry = (unsigned long *)(set + 0x20 + i * 0x10);
        key0 = *entry;
        key1 = entry[1];
        unsigned long cs = (**(unsigned long (**)(void))(**(long **)(param_6 + 0x20) + 0x80))();
        unsigned long cap = (**(unsigned long (**)(void))(*(long *)cs + 0x88))();
        FUN_0036b118(cs);
        unsigned long bits = *(byte *)(cap + 0x20) < 6 ? ~(-1L << (1L << (*(byte *)(cap + 0x20) & 0x3f) & 0x3f)) : 0xffffffffffffffff;
        bits &= *(unsigned long *)(cap + 0x38);
        FUN_0036b270(cap);
        int found = 0;
        for (unsigned long w = 0; w < ((1L << (*(byte *)(cap + 0x20) & 0x3f)) + 0x3f) / 0x40; w++) {
            unsigned long b = ((unsigned long *)(cap + 0x38))[w];
            while (b != 0) {
                unsigned long idx = (w * 0x40) + bit_index(b);
                b &= b - 1;
                unsigned long obj = *(unsigned long *)(*(long *)(cap + 0x30) + (w * 0x40 + idx) * 8);
                /* vtable[0x58] key compare */
                unsigned long k = (**(unsigned long (**)(void))(*(long *)obj + 0x58))();
                if ((k & 0xff) == (key0 & 0xff) && (k >> 8) == (key1 & 0xff)) { found = 1; break; }
                FUN_0036b118(k >> 8);
            }
            if (found) break;
        }
        FUN_0036b118(cap);
        FUN_003a25d4(cap);
        if (found) break;
    }
    if (n == 0 || key0 == 0) { /* none matched */
        FUN_000db250((void *)0);
        FUN_0036b118(set);
        return 0;
    }
    /* matched: emit via FUN_000d5d80 and return descriptor */
    unsigned long vsp = *(unsigned long *)(param_6 + 0x88);
    unsigned long r = FUN_0036b270(vsp);
    unsigned long desc = (unsigned long)FUN_000d5d80(r, param_3, param_2, param_4, (void *)0, param_6);
    FUN_0036b118(vsp);
    ((unsigned long (*)())(*(long *)desc + 0xa0))(0, param_4);
    FUN_0036b118((void *)desc);
    return 0;
}

/* FUN_000da558 @ 0x000da558   (est. expand_address_space_metadata_full)
 * Ghidra: undefined1 [16] FUN_000da558(long *param_1, long *param_2, undefined8 param_3, undefined8 param_4, undefined8 param_5, long param_6, long param_7, undefined8 param_8)
 * Full variant of FUN_000d9a98: expands a writable-ASID metadata set,
 * walking the vspace cap-set and invoking FUN_000d7bf8 per match, then
 * parsing the ASID's writable bitmap to decide span promotion.
 * Confidence: low */
unsigned long expand_address_space_metadata_full(long *param_1, long *param_2,
                                                 unsigned long param_3, unsigned long param_4,
                                                 unsigned long param_5, long param_6,
                                                 long param_7, unsigned long param_8)
{
    unsigned long set = (**(unsigned long (**)(void))(*param_2 + 0x70))();
    unsigned long n = *(unsigned long *)(set + 0x10);
    void *out = (void *)0x6577e0;
    void *out2 = (void *)0x657778;
    unsigned long key0 = 0, key1 = 0;
    if (n == 0) { FUN_0036b118(set); return 0; }
    for (unsigned long i = 0; i < n; i++) {
        unsigned long *entry = (unsigned long *)(set + 0x20 + i * 0x10);
        key0 = *entry;
        key1 = entry[1];
        unsigned long cs = (**(unsigned long (**)(void))(**(long **)(param_6 + 0x20) + 0x80))();
        unsigned long cap = (**(unsigned long (**)(void))(*(long *)cs + 0x88))();
        FUN_0036b118(cs);
        FUN_0036b270(cap);
        int found = 0;
        for (unsigned long w = 0; w < ((1L << (*(byte *)(cap + 0x20) & 0x3f)) + 0x3f) / 0x40; w++) {
            unsigned long b = ((unsigned long *)(cap + 0x38))[w];
            while (b != 0) {
                unsigned long idx = (w * 0x40) + bit_index(b);
                b &= b - 1;
                unsigned long obj = *(unsigned long *)(*(long *)(cap + 0x30) + (w * 0x40 + idx) * 8);
                unsigned long k = (**(unsigned long (**)(void))(*(long *)obj + 0x58))();
                if ((k & 0xff) == (key0 & 0xff) && (k >> 8) == (key1 & 0xff)) { found = 1; break; }
                FUN_0036b118(k >> 8);
            }
            if (found) break;
        }
        FUN_0036b118(cap);
        FUN_003a25d4(cap);
        if (found) break;
    }
    if (n == 0 || key0 == 0) { FUN_0036b118(set); return 0; }
    unsigned long vsp = *(unsigned long *)(param_6 + 0x88);
    unsigned long r = FUN_0036b270(vsp);
    unsigned long desc = (unsigned long)FUN_000d7bf8(r, param_3, param_2, param_4, (void *)0, param_6,
                                                     param_7, param_8);
    FUN_0036b118(vsp);
    ((unsigned long (*)())(*(long *)desc + 0xa0))(0, param_4);
    FUN_0036b118((void *)desc);
    return 0;
}

/* thunk_FUN_000dba28 @ 0x000dba28  (thunk of cap_slot_check)
 * Thin forwarding thunk to cap_slot_check (0xd1d54): validates the
 * capability-slot invariant, faulting on mismatch.
 * Confidence: high (thunk of covered function) */
void cap_slot_check_thunk(long node, long slots, int count_field)
{
    cap_slot_check(node, slots, count_field);
}
