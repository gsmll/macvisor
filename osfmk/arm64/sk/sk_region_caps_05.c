/* Recreated from cl4_kernel.raw (cL4 Secure Kernel, arm64e, image base 0) —
 * the cL4 microkernel (GL1). Ground truth: Ghidra FUN_ names + addresses.
 * All names are estimates unless string/header matched.
 * Slice 05: 0x92774-0x98624 caps region.
 *
 * This slice is the ExclaveLauncher device-tree (DT) / DART (IOMMU) mapping
 * layer: it parses device-tree "dart_id"/"dart_sid"/"dart_baseaddr"/
 * "dart_length" properties and builds IOMMU (DART) mappings for exclaves.
 * SeL4/cL4 vocabulary is used; confidence is medium unless a string matches.
 * Many referenced lock/alloc/log helpers are out of slice and declared extern
 * with one-line notes. */
#include "sk_internal.h"

/* ------------------------------------------------------------------ */
/* Out-of-slice kernel helpers (declared extern; bodies live elsewhere) */
/* ------------------------------------------------------------------ */

/* Lock acquire on the given lock word (masks bit 63). */
extern void FUN_0036b270(unsigned long);
/* Lock release / refcount drop on the given lock word. */
extern void FUN_0036b118(unsigned long);
/* Acquire the per-field lock described by (field, lock-word); loads field under lock. */
extern unsigned long FUN_0036a1a0(void *field, void *tmp, long op, void *arg);
/* Release the per-field lock acquired by FUN_0036a1a0. */
extern void FUN_0036a20c(void *tmp);
/* Zone allocator: allocate an object of the given type/size. */
extern unsigned long FUN_0036a940(unsigned long a, ...);
/* Zone allocator with explicit type/size args (returns new object). */
extern unsigned long FUN_0036a9a0(unsigned long type, void *tmp);
/* Drop one reference to an object (paired with FUN_0036a1a0-style acquire). */
extern void FUN_0036a2610(unsigned long obj, long kind);
/* Refcount get / read of an object's refcount (returns 0/1 flags). */
extern unsigned long FUN_0036a261c(unsigned long obj);
/* Release an object (OSLog/refcount drop of the given tagged value). */
extern void FUN_003a25d4(unsigned long obj);
/* Refcount read (returns 0 if zero, else flags). */
extern unsigned long FUN_003a261c(unsigned long obj);
/* Resolve an object pointer from a handle (returns 0 if absent). */
extern long FUN_0036b8b0(unsigned long handle);
/* Resolve an object pointer from a handle (FUN_0036b8c0 variant). */
extern void FUN_0036b8c0(unsigned long handle);
/* Drain/log side effect; no return value used. */
extern void FUN_0036b6ac(unsigned long a, ...);
/* Register/notify a completions object; no return value used. */
extern void FUN_0036b588(unsigned long obj);
/* Lock/release helper over obj+0x10. */
extern void FUN_0036b7f8(unsigned long obj);
/* Refcount bump on an object (2-way). */
extern void FUN_0036b2d0(unsigned long obj, long kind);
/* Store value into the object field at handle. */
extern void FUN_0036b834(unsigned long handle, unsigned long value);
/* Side-effect helper (no-op footprint); used in teardown paths. */
extern void FUN_0036b21c(void);

/* Fatal-error formatter (noreturn): prints "Fatal error" + file/line and halts. */
extern void FUN_001afa84(unsigned long a, long b, long c, unsigned long d,
                          unsigned long e, unsigned long f, long g, long h, ...);
/* Get the current thread/context object (extraout_x16 is the receiver). */
extern unsigned long FUN_000027e8(void);
/* Object type check: returns a 16-byte {type, flags} descriptor. */
extern unsigned long FUN_00072664(unsigned long obj);
/* Lookup a named key in a DT dictionary; returns 16-byte {value, tag}. */
extern unsigned long FUN_0006ae9c(unsigned long key_lo, unsigned long key_hi);
/* Generic object/array lookup helper (FUN_0006a4c0). */
extern unsigned long FUN_0006a4c0(unsigned long a, unsigned long b);
/* Lookup a class/global by name (FUN_00002534). */
extern unsigned long FUN_00002534(unsigned long a, unsigned long b);
/* Copy n bytes from src to dst (memcpy, FUN_00117cc4). */
extern void FUN_00117cc4(void *dst, void *src, unsigned long n);
/* Grow a counted array to hold a new element (FUN_00258c60). */
extern unsigned long FUN_00258c60(unsigned long a, unsigned long b, unsigned long c);
/* Array/vector append: insert (value, tag) at slot in array obj. */
extern void FUN_00081c1c(unsigned long a, unsigned long b, unsigned long c,
                         unsigned long d, unsigned long e);
/* Array/vector append variant (8-byte slots). */
extern void FUN_00081b9c(unsigned long a, unsigned long b, unsigned long c,
                         unsigned long d, unsigned long e);
/* Fatal abort (noreturn) for invalid array state. */
extern void FUN_002591b4(unsigned long file);
/* Array allocator that returns a growable vector object (FUN_0007371c). */
extern unsigned long FUN_0007371c(unsigned long a, unsigned long b, unsigned long c, void *d);
/* Array allocator variant (FUN_000737a8). */
extern unsigned long FUN_000737a8(unsigned long a, unsigned long b, unsigned long c, void *d);
/* Reserve capacity in a growable vector (FUN_00082504). */
extern unsigned long FUN_00082504(unsigned long a, unsigned long b, unsigned long c);
/* Grow a growable vector (FUN_001a0774). */
extern void FUN_001a0774(unsigned long grow, unsigned long count, unsigned long c);
/* Grow a growable vector and return its base (FUN_001a1564). */
extern void FUN_001a1564(void);
/* Vector capacity helper (FUN_0006b42c). */
extern unsigned long FUN_0006b42c(void);
/* String parse helper for signed/hex accumulation. */
extern unsigned long FUN_002a9ba8(unsigned long s, unsigned long t);
/* Parse a string as integer base 10 into {value, flags} (thunk). */
extern unsigned long FUN_000b077c(unsigned long s, unsigned long t, unsigned long base);
/* Parse a string as integer base 16 into {value, flags} (thunk). */
extern unsigned long FUN_000b02dc(unsigned long s, unsigned long t, unsigned long base);
/* Char-class helper: process one digit/char of a string. */
extern void FUN_00084000(unsigned long len);
extern void FUN_0008e0f4(void);
extern void FUN_0008e0e8(void);
/* Allocate an object via the zone type passed (FUN_00139574). */
extern unsigned long FUN_00139574(unsigned long a);
/* Build a wrapped/launcher object (FUN_001227bc). */
extern unsigned long FUN_001227bc(unsigned long a, unsigned long b, unsigned long c,
                                  unsigned long d, ...);
/* Get the launcher's current object (FUN_00167a6c). */
extern unsigned long FUN_00167a6c(unsigned long a);
/* Notify/log "optional" resolution (FUN_001a6a8c). */
extern void FUN_001a6a8c(unsigned long obj, unsigned long fmt);
/* Object-specific resolve (FUN_00027724). */
extern unsigned long FUN_00027724(unsigned long a);
/* Release/teardown of a launcher object (FUN_001ebfb0). */
extern unsigned long FUN_001ebfb0(void *a, unsigned long b, unsigned long c);
/* Log format emit (FUN_002a4ab4). */
extern void FUN_002a4ab4(unsigned long kind);
/* Log string-part emit (thunk_FUN_002acbb8). */
extern unsigned long thunk_FUN_002acbb8(unsigned long lo, unsigned long hi);
/* Log tag/flush (FUN_0026b434). */
extern void FUN_0026b434(unsigned long obj, unsigned long a, unsigned long b,
                          unsigned long c, unsigned long d);
/* Log/format (FUN_00205844). */
extern unsigned long FUN_00205844(void *buf, void *out, unsigned long a,
                                  unsigned long b, unsigned long c);
/* Log emit for string values (FUN_0008396c). */
extern void FUN_0008396c(unsigned long a, unsigned long b, unsigned long c);
/* Log emit helper (FUN_0007c0b8). */
extern void FUN_0007c0b8(void);
/* Notify/mark side effect (FUN_0001e790). */
extern void FUN_0001e790(void);
/* Post a resolve/log completion (FUN_000026e8). */
extern void FUN_000026e8(unsigned long a);
/* Logging enable flag (DAT_006add10): when 1, emits verbose launcher logs. */
extern volatile unsigned char DAT_006add10;
/* Log format string objects. */
extern unsigned long FUN_00002688(void);
/* ObjC-style message log helper (FUN_0008f840). */
extern void FUN_0008f840(unsigned long a, unsigned long b);
/* DT list builder (FUN_0007b5f4). */
extern void FUN_0007b5f4(unsigned long a);
/* Convert value to tagged string (FUN_0008e5d8). */
extern unsigned long FUN_0008e5d8(unsigned long a);
/* Per-CPU state getters. */
extern unsigned long FUN_001071f4(void);
extern unsigned long FUN_0010720c(void);
extern unsigned long FUN_00107200(void);
extern unsigned long FUN_0013f770(void);
extern unsigned long FUN_0013f77c(void);
extern unsigned long FUN_0013f764(void);
extern unsigned long FUN_0013f758(void);
/* Get value for the given op code (FUN_00157308). */
extern unsigned long FUN_00157308(unsigned long a);
/* Lookup object by handle (FUN_001000b8). */
extern unsigned long FUN_001000b8(unsigned long a);
/* Log/notify (FUN_000fd5d8). */
extern void FUN_000fd5d8(unsigned long a);
/* Register a teardown hook (FUN_0002f94c). */
extern void FUN_0002f94c(void);
/* Reset an object field to an empty sentinel (FUN_0000456c). */
extern void FUN_0000456c(void);
/* Create/resolve the exclave-launcher external object (FUN_000902c4). */
extern unsigned long FUN_000902c4(void);
/* DART map lookup (FUN_0009cf58). */
extern void FUN_0009cf58(unsigned long *a);
/* Object field acquire helper (FUN_00084100). */
extern void FUN_00084100(unsigned long a);
/* Object field release helper (FUN_0008e3b0). */
extern void FUN_0008e3b0(unsigned long a);
/* Object field init helper (FUN_0009e228). */
extern void FUN_0009e228(unsigned long a, unsigned long b);
/* Object field snapshot helper (FUN_0009d014). */
extern void FUN_0009d014(void *a, void *b);
/* Object field reset helper (FUN_0009e1e8). */
extern void FUN_0009e1e8(void);
/* Object teardown (FUN_0000276c). */
extern void FUN_0000276c(void *a);
/* Build DT mapping context (FUN_0006e7c0). */
extern void FUN_0006e7c0(unsigned long a, void *b);
/* DT array helper (FUN_0007b1f0). */
extern void FUN_0007b1f0(void);
/* DT array index (FUN_0007b324). */
extern void FUN_0007b324(unsigned long a);
/* Side-effect (FUN_0008e328). */
extern void FUN_0008e328(void);
/* Map lookup (FUN_000f6d88). */
extern unsigned long FUN_000f6d88(unsigned long a, unsigned long b, unsigned long c,
                                  unsigned long d);
/* Class/global init helper (FUN_0014aedc). */
extern long FUN_0014aedc(unsigned long a, unsigned long b);
/* Log emit (FUN_0014afe0). */
extern void FUN_0014afe0(void *a, unsigned long b, unsigned long c, unsigned long d,
                         unsigned long e, unsigned long f);
/* Log buffer allocator (FUN_0001a1c8). */
extern unsigned long FUN_0001a1c8(unsigned long a, ...);
/* Notify/log "not... " (FUN_0007608c). */
extern void FUN_0007608c(unsigned long a, unsigned long b, unsigned long c,
                         unsigned long d);
/* Log field read (FUN_00097220 returns 0x677790) and base read
 * (FUN_00097204 returns 0x6776f0) are implemented in this slice. */
/* Soft-assert helper (FUN_002a0cf8). */
extern void FUN_002a0cf8(unsigned long a);
/* Software breakpoint / halt (opaque). */
extern unsigned long SoftwareBreakpoint(unsigned long code, unsigned long pc);
/* CallSupervisor SVC (opaque). */
extern unsigned long CallSupervisor(unsigned long num);

/* Per-CPU base register. */
#define tpidrro_el0 0UL

/* Additional out-of-slice helpers referenced below. */
extern void FUN_00077770(unsigned long);
extern void FUN_0012540c(unsigned long, unsigned long);
extern unsigned long FUN_000ddbc4(void);
extern void FUN_000986d4(unsigned long, unsigned long, unsigned long, unsigned long,
                         unsigned long, unsigned long, unsigned long, unsigned long,
                         unsigned long, unsigned char);
extern void FUN_00151a6c(unsigned long, unsigned long, unsigned long, unsigned long,
                         unsigned long, unsigned long, unsigned long, unsigned long);
extern void FUN_001fc840(void *, void *, unsigned long, unsigned long, unsigned long);
extern void FUN_001a0774(unsigned long, unsigned long, unsigned long);
extern void FUN_001a6a8c(unsigned long, unsigned long);
extern unsigned long FUN_001f0130(unsigned long, unsigned long, unsigned long, unsigned long);
extern void FUN_0008e328(void);
extern void FUN_000026e8(unsigned long);
extern void FUN_0007b5f4(unsigned long);
extern void FUN_0008f840(unsigned long, unsigned long);
extern unsigned long FUN_00002688(void);
extern void FUN_0008396c(unsigned long, unsigned long, unsigned long);
extern void FUN_0009d014(void *, void *);
extern void FUN_0009e1e8(void);
extern void FUN_0000276c(void *);
extern void FUN_0006e7c0(unsigned long, void *);
extern unsigned long FUN_001ebfb0(void *, unsigned long, unsigned long);
extern unsigned long FUN_00027724(unsigned long);
extern unsigned long FUN_000737a8(unsigned long, unsigned long, unsigned long, void *);
extern unsigned long FUN_00082504(unsigned long, unsigned long, unsigned long);
extern void FUN_0009e228(unsigned long, unsigned long);
extern void FUN_00084100(unsigned long);
extern void FUN_002a0cf8(unsigned long);
extern void FUN_003a2610(unsigned long, unsigned long);

/* ExclaveLauncher local forward declarations. */
static void sk_launcher_external_forward(void);
static unsigned char sk_cap_table_insert(unsigned long value, unsigned long tag,
                                         unsigned long cap);
static void sk_exclave_launcher_external(unsigned long *out, long launcher);
static void sk_lock_acquire_masked(unsigned long);
static void sk_lock_release_masked(unsigned long);
static long sk_bitmask_shift(unsigned long);
static void sk_percpu_slot_store(long, unsigned long);
static void sk_supervisor_call0(unsigned long, unsigned long);
static unsigned long sk_log_base_ptr(void);
static void sk_noop_94548(void);
static void sk_field_lock_noop(void);
static void sk_noop_9456c(void);
static void sk_fatal_external_launcher(void);
static void sk_noop_9461c(void);
static void sk_stack_clear_16(void);
static void sk_noop_970d4(void);
static void sk_noop_970ec(void);
static void sk_fatal_dt_resol(unsigned long);
static void sk_noop_97154(void);
static void sk_log_string_push(long);
static void sk_noop_97188(void);
static void sk_noop_97198(void);
static void sk_noop_971a4(void);
static void sk_noop_971b8(void);
static void sk_noop_971c4(void);
static void sk_noop_971e8(void);
static unsigned long sk_log_base_ptr2(void);
static unsigned long sk_log_base_ptr3(void);
static void sk_noop_9724c(void);
static void sk_obj_drop(void);
static void sk_noop_97274(void);
static unsigned long sk_soft_assert(void);
static void sk_noop_972b0(void);
static void sk_noop_972c4(void);
static unsigned long sk_log_resol_base(void);
static long sk_tagged_ptr_deref8(unsigned long);
static long sk_tagged_ptr_deref_c(unsigned long);
static long sk_tagged_ptr_deref4(unsigned long);
static unsigned long sk_stack_pair_desc(void);
static unsigned long sk_stack_descriptor(void);
static unsigned long sk_log_contains(void);
static bool sk_vec_needs_grow(unsigned long);
static void sk_release_strings_by_kind(unsigned long, unsigned long, unsigned long,
                                       unsigned long, unsigned long, unsigned long,
                                       unsigned long, unsigned long, unsigned char);
static void sk_log_resolve_edge(unsigned long, long *, unsigned long *);
static void sk_log_dart_val(unsigned long, unsigned long, unsigned long);
static void sk_log_resolve_edge_pair(unsigned long, long *, long *);
static void sk_log_offset(unsigned long, unsigned long, unsigned long, unsigned long);
static void sk_log_dart_resolve(unsigned long, unsigned long, unsigned long);
static void sk_log_dart_prop(unsigned long, unsigned long, unsigned long,
                             unsigned long, char);
static void sk_log_dart_prop_a(unsigned long, unsigned long, unsigned long,
                               unsigned long, char);

/* Thin wrappers exposing the exact Ghidra FUN_ names for call sites in the
 * big DT/DART mappers (0x95184/0x95ba4/0x9647c/0x96c74) that dispatch to
 * these in-slice helpers by their original name. */
static void FUN_00092990(void) { sk_exclave_launcher_external(0, 0); }
static void FUN_00093c58(unsigned long l) { sk_lock_acquire_masked(l); }
static void FUN_00093c60(unsigned long l) { sk_lock_release_masked(l); }
static long FUN_00093c68(unsigned long i) { return sk_bitmask_shift(i); }
static void FUN_00093c74(long i, unsigned long v) { sk_percpu_slot_store(i, v); }
static void FUN_00093c84(unsigned long a, unsigned long b) { sk_supervisor_call0(a, b); }
static unsigned long FUN_00094654(void) { return sk_log_base_ptr(); }
static void FUN_00094548(void) { sk_noop_94548(); }
static void FUN_0009455c(unsigned long a) { sk_field_lock_noop(); }
static void FUN_0009456c(unsigned long a) { sk_noop_9456c(); }
static void FUN_00094588(void) { sk_fatal_external_launcher(); }
static void FUN_0009461c(void) { sk_noop_9461c(); }
static void FUN_00094634(void) { sk_stack_clear_16(); }
static void FUN_000970d4(void) { sk_noop_970d4(); }
static void FUN_000970ec(void) { sk_noop_970ec(); }
static void FUN_00097100(unsigned long c) { sk_fatal_dt_resol(c); }
static void FUN_00097128(void) { sk_log_resol_base(); }
static void FUN_00097154(void) { sk_noop_97154(); }
static void FUN_00097170(long v) { sk_log_string_push(v); }
static void FUN_00097188(void) { sk_noop_97188(); }
static void FUN_00097198(void) { sk_noop_97198(); }
static void FUN_000971a4(void) { sk_noop_971a4(); }
static void FUN_000971b8(void) { sk_noop_971b8(); }
static void FUN_000971c4(void) { sk_noop_971c4(); }
static void FUN_000971e8(void) { sk_noop_971e8(); }
static void FUN_00097204(void) { sk_log_base_ptr2(); }
static void FUN_00097220(void) { sk_log_base_ptr3(); }
static void FUN_0009724c(void) { sk_noop_9724c(); }
static void FUN_0009725c(void) { sk_obj_drop(); }
static void FUN_00097274(void) { sk_noop_97274(); }
static unsigned long FUN_00097298(void) { return sk_soft_assert(); }
static void FUN_000972b0(void) { sk_noop_972b0(); }
static void FUN_000972c4(void) { sk_noop_972c4(); }
static long FUN_00096f78(unsigned long p) { return sk_tagged_ptr_deref8(p); }
static long FUN_00097074(unsigned long p) { return sk_tagged_ptr_deref_c(p); }
static long FUN_000970a4(unsigned long p) { return sk_tagged_ptr_deref4(p); }
static unsigned long FUN_00097268(void) { return sk_stack_pair_desc(); }
static unsigned long FUN_0009723c(void) { return sk_stack_descriptor(); }
static unsigned long FUN_00097280(void) { return sk_log_contains(); }
static bool FUN_000972d0(unsigned long c, ...) { return sk_vec_needs_grow(c); }
static void FUN_00096fa8(unsigned long a, unsigned long b, unsigned long c,
                         unsigned long d, unsigned long e, unsigned long f,
                         unsigned long g, unsigned long h, unsigned char k)
{ sk_release_strings_by_kind(a, b, c, d, e, f, g, h, k); }
static void FUN_00094a18(unsigned long a, long *o1, unsigned long *o2)
{ sk_log_resolve_edge(a, o1, o2); }
static void FUN_00094bdc(unsigned long a, unsigned long b, unsigned long c)
{ sk_log_dart_val(a, b, c); }
static void FUN_00094d04(unsigned long a, long *o1, long *o2)
{ sk_log_resolve_edge_pair(a, o1, o2); }
static void FUN_00094e94(unsigned long a, unsigned long b, unsigned long c,
                         unsigned long d) { sk_log_offset(a, b, c, d); }
static void FUN_0009503c(unsigned long a, unsigned long b, unsigned long c)
{ sk_log_dart_resolve(a, b, c); }
static void FUN_00094668(unsigned long a, unsigned long b, unsigned long c,
                         unsigned long d, char e) { sk_log_dart_prop(a, b, c, d, e); }
static void FUN_00094840(unsigned long a, unsigned long b, unsigned long c,
                         unsigned long d, char e) { sk_log_dart_prop_a(a, b, c, d, e); }

/* In-slice forward declarations used across functions. */
static void sk_dt_log_string(unsigned long value);

/* ------------------------------------------------------------------ */
/* Function bodies (ascending address order)                            */
/* ------------------------------------------------------------------ */

/* FUN_00092774 @ 0x00092774   (est. sk_call_under_lock4)
 * Ghidra: undefined1 [16] FUN_00092774(long, undefined8, undefined8, undefined8, undefined8)
 * Holds the object's lock (stored at +0x28) and invokes the stored function
 * pointer at +0x20 with the four supplied arguments, releasing the lock on
 * return. A generic "call this callback while holding the object lock" wrapper
 * used across the launcher.
 * Confidence: medium
 * Notes: lock acquire = FUN_0036b270, release = FUN_0036b118 (out of slice). */
static unsigned long sk_call_under_lock4(long self, unsigned long a, unsigned long b,
                                         unsigned long c, unsigned long d)
{
    void (*fn)(unsigned long, unsigned long, unsigned long, unsigned long);
    unsigned long lock;

    fn = *(void (**)(unsigned long, unsigned long, unsigned long, unsigned long))(self + 0x20);
    lock = *(unsigned long *)(self + 0x28);
    FUN_0036b270(lock);                                    /* acquire lock */
    fn(a, b, c, d);                                        /* invoke callback */
    FUN_0036b118(lock);                                    /* release lock */
    return 0;
}

/* FUN_000927f0 @ 0x000927f0   (est. sk_cap_slot_lookup)
 * Ghidra: undefined8 FUN_000927f0(undefined8, long)
 * Looks up a capability slot object from a launcher: resolves the object
 * stored at param_2+0x10, then the sub-object at +0x88, and if the capability
 * word (param_1) grants access, dereferences the per-slot table at +0x38 and
 * returns the stored value at +0x48 of the matching slot. Returns 0 when the
 * object chain is empty or the cap is not permitted.
 * Confidence: low
 * Notes: FUN_0036b8b0 resolve, thunk_FUN_00072664 cap check, FUN_0036a1a0/a20c
 * field-lock pairs. */
static unsigned long sk_cap_slot_lookup(unsigned long cap, long launcher)
{
    long obj, slot_obj, slot;
    unsigned long value;
    unsigned long desc;   /* 16-byte {index, flags} from cap check */

    FUN_0036a1a0((void *)(launcher + 0x10), 0, 0, 0);
    obj = FUN_0036b8b0(launcher + 0x10);
    if (obj == 0) {
        return 0;
    }
    FUN_0036a1a0((void *)(obj + 0x88), 0, 0x20, 0);
    slot_obj = *(long *)(obj + 0x88);
    if ((*(long *)(slot_obj + 0x10) == 0) ||
        ((desc = FUN_00072664(cap), (desc & 1) == 0))) {
        FUN_0036a20c(0);
        return 0;
    }
    slot = *(long *)(*(long *)(slot_obj + 0x38) + (desc & 0xffffffff) * 0x10 + 8);
    FUN_0036a20c(0);
    FUN_0036b270(slot);
    FUN_0036b118(slot_obj);
    value = *(unsigned long *)(slot + 0x48);
    FUN_0036b118(slot);
    return value;
}

/* FUN_000928c4 @ 0x000928c4   (est. sk_call_under_lock1)
 * Ghidra: undefined8 FUN_000928c4(long, undefined8)
 * Holds the lock at +0x28 and calls the function pointer at +0x20 with one
 * argument, releasing the lock afterwards. One-argument variant of
 * sk_call_under_lock4.
 * Confidence: medium
 * Notes: same lock pair as 0x92774. */
static unsigned long sk_call_under_lock1(long self, unsigned long a)
{
    unsigned long (*fn)(unsigned long);
    unsigned long lock, ret;

    fn = *(unsigned long (**)(unsigned long))(self + 0x20);
    lock = *(unsigned long *)(self + 0x28);
    FUN_0036b270(lock);
    ret = fn(a);
    FUN_0036b118(lock);
    return ret;
}

/* FUN_00092914 @ 0x00092914   (est. sk_launcher_fetch_external)
 * Ghidra: undefined8 FUN_00092914(void)
 * Dispatches the +0x80 vtable method of the current launcher context, passing
 * the callback FUN_00093a60 and the external-object type tag 0x64f850, and
 * returns whatever the method produced. Used to lazily obtain the launcher
 * external helper.
 * Confidence: low
 * Notes: FUN_000027e8 supplies the receiver in x16. */
static unsigned long sk_launcher_fetch_external(void)
{
    unsigned long self;
    unsigned long (*fn)(unsigned long, unsigned long, unsigned long, unsigned long);
    unsigned long local;

    self = FUN_000027e8();
    fn = *(unsigned long (**)(unsigned long, unsigned long, unsigned long, unsigned long))(self + 0x80);
    return fn((unsigned long)&local, (unsigned long)&sk_launcher_external_forward, 0, 0x64f850);
}

/* FUN_00092990 @ 0x00092990   (est. sk_exclave_launcher_external)
 * Ghidra: void FUN_00092990(undefined8 *, long)
 * Get-or-create the "ExclaveLauncher_External" helper object. If the slot at
 * param_2+0x98 is empty, allocates a 0x58-byte object, creates the external
 * via FUN_000902c4 under the object lock, and stores it; otherwise raises a
 * fatal error ("InternalExclaveLauncher_External") because the singleton
 * already exists.
 * Confidence: medium
 * Notes: string s_InternalExclaveLauncher_External_005c0dc0; alloc tag 0x64f850. */
static void sk_exclave_launcher_external(unsigned long *out, long launcher)
{
    long obj;
    unsigned long created;

    obj = FUN_0036b8b0(launcher + 0x98);
    if (obj == 0) {
        FUN_0036a940(0x64f850, 0x58, 7);          /* allocate external object */
        FUN_0036b270(launcher);
        created = FUN_000902c4();
        FUN_0036b834(launcher + 0x98, created);
        *out = created;
        return;
    }
    FUN_0036b118(obj);
    /* Fatal error: external launcher singleton already exists. */
    FUN_001afa84(0x5accd0, 0xb, 2, 0x2079646165726c41, 0xef2164657361656c,
                 0x5c0dc0, 0x39, 2, 300, 0);
}

/* FUN_00092a68 @ 0x00092a68   (est. sk_cap_insert_small)
 * Ghidra: void FUN_00092a68(undefined8, undefined8, undefined8)
 * Reads an operation code via FUN_00157308(param_3); if it is below 0x100,
 * acquires the object's field lock and inserts (op, launcher, out) into the
 * cap table through FUN_00093b24, then releases. Larger codes hit a breakpoint
 * (invalid table index).
 * Confidence: low
 * Notes: SoftwareBreakpoint(1, 0x92af8) on invalid op. */
static void sk_cap_insert_small(unsigned long a, unsigned long b, unsigned long c)
{
    unsigned long op;

    op = FUN_00157308(c);
    if (op < 0x100) {
        FUN_0036a1a0((void *)(0 + 0x88), 0, 0x21, 0);
        FUN_0036b270(b);
        sk_cap_table_insert(op, b, a);
        FUN_0036a20c(0);
        FUN_0036b118(0);
        return;
    }
    SoftwareBreakpoint(1, 0x92af8);          /* invalid cap-table op */
}

/* FUN_00092af8 @ 0x00092af8   (est. sk_notify_handle)
 * Ghidra: void FUN_00092af8(void)
 * Resolves a handle from the current thread (FUN_001000b8(0)), takes the
 * object lock, and posts a notify via FUN_000fd5d8.
 * Confidence: low */
static void sk_notify_handle(void)
{
    unsigned long h;

    h = FUN_001000b8(0);
    FUN_0036b270(0);
    FUN_000fd5d8(h);
}

/* FUN_00092b3c @ 0x00092b3c   (est. sk_launcher_teardown)
 * Ghidra: void FUN_00092b3c(void)
 * Tears down the launcher object: clears the +0xa0 marker and the +0x90
 * sub-object; if +0x90 was non-null, resets the +0xf8 and +0xe8 completion
 * hooks to a no-op sentinel (FUN_0000456c) and clears their stored values,
 * releasing the prior refs. A destructor for the launcher's child objects.
 * Confidence: medium
 * Notes: FUN_0009456c/FUN_0036a1a0 field lock helpers. */
static void sk_launcher_teardown(void)
{
    long launcher = 0;   /* unaff_x20 */
    unsigned long v;

    FUN_0009456c(launcher + 0xa0);
    FUN_0036a1a0(0, 0, 0, 0);
    *(unsigned long *)(launcher + 0xa0) = 0;
    FUN_0036a1a0((void *)(launcher + 0x90), 0, 0, 0);
    if (*(long *)(launcher + 0x90) != 0) {
        FUN_0002f94c();
        FUN_0009456c(launcher + 0xf8);
        FUN_0036a1a0(0, 0, 0, 0);
        v = *(unsigned long *)(launcher + 0x100);
        *(unsigned long *)(launcher + 0xf8) = (unsigned long)&FUN_0000456c;
        *(unsigned long *)(launcher + 0x100) = 0;
        FUN_0036b118(v);
        FUN_0009456c(launcher + 0xe8);
        FUN_0036a1a0(0, 0, 0, 0);
        v = *(unsigned long *)(launcher + 0xf0);
        *(unsigned long *)(launcher + 0xe8) = (unsigned long)&FUN_0000456c;
        *(unsigned long *)(launcher + 0xf0) = 0;
        FUN_0036b118(v);
    }
}

/* FUN_00092be8 @ 0x00092be8   (est. sk_launcher_teardown_fatal)
 * Ghidra: void FUN_00092be8(void)
 * Runs the teardown entry hook (FUN_00094588, which is itself a fatal-error
 * path) and never returns; a breakpoint is emitted at the tail.
 * Confidence: low */
static void sk_launcher_teardown_fatal(void)
{
    FUN_00094588();
    SoftwareBreakpoint(1, 0x92c00);
}

/* FUN_00092c00 @ 0x00092c00   (est. sk_percpu_mask_check)
 * Ghidra: undefined1 FUN_00092c00(uint)
 * Checks a set of per-CPU status words against a mask (param_1): for each
 * level, verifies that all bits of the mask are set (i.e. `*word & ~mask == 0`),
 * selecting a per-CPU byte from the deepest matching level and returning it.
 * Selects among FUN_0013f770/77c/764/758 based on which words are saturated.
 * Confidence: low
 * Notes: per-cpu base getters FUN_001071f4/0720c/07200. */
static unsigned char sk_percpu_mask_check(unsigned int mask)
{
    unsigned int *word;
    unsigned char *byte;

    word = (unsigned int *)FUN_001071f4();
    if ((*word & (mask ^ 0xffffffffu)) == 0) {
        word = (unsigned int *)FUN_0010720c();
        if ((*word & (mask ^ 0xffffffffu)) == 0) {
            byte = (unsigned char *)FUN_0013f770();
        } else {
            word = (unsigned int *)FUN_00107200();
            if ((*word & (mask ^ 0xffffffffu)) == 0)
                byte = (unsigned char *)FUN_0013f77c();
            else
                byte = (unsigned char *)FUN_0013f764();
        }
    } else {
        byte = (unsigned char *)FUN_0013f758();
    }
    return *byte;
}

/* FUN_00092d40 @ 0x00092d40   (est. sk_launcher_get_field40)
 * Ghidra: undefined8 FUN_00092d40(void)
 * Plain field getter: returns the value stored at +0x40 of the launcher.
 * Confidence: medium */
static unsigned long sk_launcher_get_field40(void)
{
    return *(unsigned long *)(0 + 0x40);   /* unaff_x20 + 0x40 */
}

/* FUN_00093060 @ 0x00093060   (est. sk_dt_ctx_copy)
 * Ghidra: void FUN_00093060(undefined8, undefined8 *, undefined8)
 * Copies a 0xf8-byte DT-resolve context struct from param_2 into param_1, and
 * additionally copies a 0xb8-byte scratch region from param_3 to a local.
 * The 0xf8-byte context carries {a 16-byte pair, several 8-byte words, a byte
 * chain} mirroring the launcher's resolve state.
 * Confidence: medium
 * Notes: FUN_00117cc4 = memcpy. */
static void sk_dt_ctx_copy(unsigned long out, unsigned long *src, unsigned long other)
{
    unsigned char scratch[0xb8];
    unsigned char ctx[0xf8];

    (void)ctx; (void)scratch;
    FUN_00117cc4(scratch, (void *)other, 0xb8);
    FUN_00117cc4((void *)out, src, 0xf8);
}

/* FUN_000930c0 @ 0x000930c0   (est. sk_launcher_lock_get10)
 * Ghidra: undefined8 FUN_000930c0(void)
 * Reads the +0x10 field and acquires its lock (via FUN_00093c58). Getter that
 * returns the value while holding the corresponding lock.
 * Confidence: medium */
static unsigned long sk_launcher_lock_get10(void)
{
    unsigned long v;

    v = *(unsigned long *)(0 + 0x10);   /* unaff_x20 */
    FUN_00093c58(v);
    return v;
}

/* FUN_000930ec @ 0x000930ec   (est. sk_launcher_get_flag18)
 * Ghidra: undefined1 FUN_000930ec(void)
 * Acquires the +0x18 field lock and returns the byte stored there. Getter for
 * a boolean/flag field.
 * Confidence: medium
 * Notes: FUN_00084100 field-lock helper. */
static unsigned char sk_launcher_get_flag18(void)
{
    FUN_00084100(0 + 0x18);
    return *(unsigned char *)(0 + 0x18);
}

/* FUN_00093114 @ 0x00093114   (est. sk_launcher_set_flag18)
 * Ghidra: void FUN_00093114(undefined1)
 * Sets the +0x18 flag field to param_1 under the field lock.
 * Confidence: medium
 * Notes: FUN_0008e3b0 field-lock helper. */
static void sk_launcher_set_flag18(unsigned char value)
{
    FUN_0008e3b0(0 + 0x18);
    *(unsigned char *)(0 + 0x18) = value;
}

/* FUN_00093148 @ 0x00093148   (est. sk_launcher_flag18_descriptor)
 * Ghidra: undefined1 [16] FUN_00093148(void)
 * Acquires the +0x18 field lock and returns a {LAB_0006f910, &self+0x18}
 * descriptor pair — the vtable-typed accessor for the flag field.
 * Confidence: low */
static unsigned long sk_launcher_flag18_descriptor(void)
{
    FUN_0009455c(0 + 0x18);
    return (unsigned long)(0 + 0x18);   /* descriptor tail = field address */
}

/* FUN_0009318c @ 0x0009318c   (est. sk_alloc_init)
 * Ghidra: void FUN_0009318c(undefined8)
 * Allocates an object, stores param_1 at +0x10 and clears +0x18. A small
 * initializer for a two-field launcher helper.
 * Confidence: low
 * Notes: FUN_0036a940 zone alloc. */
static void sk_alloc_init(unsigned long value)
{
    unsigned long obj;

    obj = FUN_0036a940(0, 0, 0);
    *(unsigned long *)(obj + 0x10) = value;
    *(unsigned char *)(obj + 0x18) = 0;
}

/* FUN_000931d4 @ 0x000931d4   (est. sk_vtable_call_b8)
 * Ghidra: undefined8 FUN_000931d4(void)
 * Dispatches the +0xb8 vtable method of the current launcher object under its
 * lock and returns the method's result.
 * Confidence: low */
static unsigned long sk_vtable_call_b8(void)
{
    unsigned long self, (*fn)(void);

    FUN_00094548();
    self = 0;                              /* extraout_x16 receiver */
    fn = *(unsigned long (**)(void))(self + 0xb8);
    FUN_0036b270(0);
    return fn();
}

/* FUN_00093230 @ 0x00093230   (est. sk_vtable_call_c0)
 * Ghidra: undefined8 FUN_00093230(void)
 * Dispatches the +0xc0 vtable method of the current launcher object under its
 * lock and returns the method's result.
 * Confidence: low */
static unsigned long sk_vtable_call_c0(void)
{
    unsigned long self, (*fn)(void);

    FUN_00094548();
    self = 0;                              /* extraout_x16 receiver */
    fn = *(unsigned long (**)(void))(self + 0xc0);
    FUN_0036b270(0);
    return fn();
}

/* FUN_0009328c @ 0x0009328c   (est. sk_vtable_call_c8)
 * Ghidra: undefined8 FUN_0009328c(void)
 * Dispatches the +0xc8 (200) vtable method of the current launcher object
 * under its lock, then returns a fresh completion value.
 * Confidence: low */
static unsigned long sk_vtable_call_c8(void)
{
    unsigned long self, (*fn)(void);

    FUN_00094548();
    self = 0;                              /* extraout_x16 receiver */
    fn = *(unsigned long (**)(void))(self + 200);
    FUN_0036b270(0);
    fn();
    return FUN_000ddbc4();
}

/* FUN_000932ec @ 0x000932ec   (est. sk_vtable_call_d0)
 * Ghidra: undefined1 [16] FUN_000932ec(void)
 * Dispatches the +0xd0 vtable method of the current launcher object under its
 * lock and returns the method's 16-byte result.
 * Confidence: low */
static unsigned long sk_vtable_call_d0(void)
{
    unsigned long self, (*fn)(void);

    FUN_00094548();
    self = 0;                              /* extraout_x16 receiver */
    fn = *(unsigned long (**)(void))(self + 0xd0);
    FUN_0036b270(0);
    return fn();
}

/* FUN_00093358 @ 0x00093358   (est. sk_exclave_describe)
 * Ghidra: undefined1 [16] FUN_00093358(undefined8, undefined8, undefined8)
 * Formats a human-readable description of an exclave for logging: builds a
 * string of the form "ExclaveX <size>:0x.., vsize:0x.., type:.., pmem:..}" by
 * querying vtable methods (+0x68 size, +0x70 vsize, +0x80 type, +0x78 pmem)
 * of the current object and emitting a log line. Returns the accumulated
 * log tag pair.
 * Confidence: low
 * Notes: heavy log-emit helpers FUN_002a4ab4/thunk_FUN_002acbb8/FUN_003a25d4;
 * constants are the log tag/kind values. */
static unsigned long sk_exclave_describe(unsigned long a, unsigned long b,
                                         unsigned long c)
{
    unsigned long type = 0x436576616c637845;   /* "ExclaveX" or "ExclaveK" */
    unsigned long err = 0xeb0000000065726f;    /* "ore..." error tag */

    if (*(long *)(0 + 0x10) > 0x7fffffffffffffffL)
        type = 0x4b6576616c637845;             /* "ExclaveK" */
    if (*(long *)(0 + 0x10) > 0x7fffffffffffffffL)
        err = 0xea00000000007469;              /* "it..." error tag */

    FUN_002a4ab4(0x3f);
    thunk_FUN_002acbb8(0x6765524d56747845, 0xec0000007b6e6f69);   /* "ExtVMRe..." */
    thunk_FUN_002acbb8(type, err);
    FUN_003a25d4(err);
    thunk_FUN_002acbb8(0x73616276203a3a3a, 0xed00007830203a65);   /* "::: vba..." */
    FUN_0007c0b8();
    FUN_0001e790();
    FUN_00094634();
    thunk_FUN_002acbb8(0, 0);
    FUN_003a25d4(0);
    thunk_FUN_002acbb8(0x3a657a697376202c, 0xeb00000000783020);   /* ", vsize:..." */
    FUN_0007c0b8();
    FUN_00094634();
    thunk_FUN_002acbb8(0, 0);
    FUN_003a25d4(0);
    thunk_FUN_002acbb8(0x3a65707974202c, 0xe700000000000000);     /* ", type:..." */
    FUN_0007c0b8();
    FUN_00094634();
    FUN_00205844(0, 0, 0x667ae0, 0x6756a8, 0x66e1b8);
    FUN_0008396c(0, 0, c);
    thunk_FUN_002acbb8(0x3a736d726570202c, 0xe900000000000020);   /* ", pmrs:..." */
    FUN_0007c0b8();
    FUN_00094634();
    thunk_FUN_002acbb8(0x7d, 0xe100000000000000);                 /* "}" */
    return 0;
}

/* FUN_000935fc @ 0x000935fc   (est. sk_launcher_lock_release10)
 * Ghidra: void FUN_000935fc(void)
 * Releases the lock on the +0x10 field.
 * Confidence: medium */
static void sk_launcher_lock_release10(void)
{
    FUN_00093c60(*(unsigned long *)(0 + 0x10));
}

/* FUN_00093600 @ 0x00093600   (est. sk_launcher_lock_release10b)
 * Ghidra: void FUN_00093600(void)
 * Releases the lock on the +0x10 field (duplicate of 0x935fc).
 * Confidence: medium */
static void sk_launcher_lock_release10b(void)
{
    FUN_00093c60(*(unsigned long *)(0 + 0x10));
}

/* FUN_0009361c @ 0x0009361c   (est. sk_launcher_release_notify10)
 * Ghidra: void FUN_0009361c(void)
 * Releases the +0x10 lock and posts a notify side effect.
 * Confidence: low */
static void sk_launcher_release_notify10(void)
{
    FUN_00093c60(*(unsigned long *)(0 + 0x10));
    FUN_0036b6ac(0);
}

/* FUN_00093620 @ 0x00093620   (est. sk_launcher_release_notify10b)
 * Ghidra: void FUN_00093620(void)
 * Releases the +0x10 lock and posts a notify side effect (duplicate).
 * Confidence: low */
static void sk_launcher_release_notify10b(void)
{
    FUN_00093c60(*(unsigned long *)(0 + 0x10));
    FUN_0036b6ac(0);
}

/* FUN_00093648 @ 0x00093648   (est. sk_vtable_call_88)
 * Ghidra: void FUN_00093648(void)
 * Dispatches the +0x88 vtable method of the current launcher object.
 * Confidence: low */
static void sk_vtable_call_88(void)
{
    unsigned long self, (*fn)(void);

    FUN_000027e8();
    self = 0;                              /* extraout_x16 receiver */
    fn = *(unsigned long (**)(void))(self + 0x88);
    fn();
}

/* FUN_0009374c @ 0x0009374c   (est. sk_launcher_lock_18)
 * Ghidra: void FUN_0009374c(void)
 * Acquires the lock stored at +0x18 of the launcher, then runs a no-op hook.
 * Confidence: low */
static void sk_launcher_lock_18(void)
{
    FUN_0036b270(*(unsigned long *)(0 + 0x18));
    FUN_0009461c();
}

/* FUN_000937b8 @ 0x000937b8   (est. sk_dt_parse_symbols)
 * Ghidra: void FUN_000937b8(undefined8 *, long *)
 * Parses a device-tree "symbols" node into the caller's 0xf8-byte context.
 * Invokes the +0x1f0 vtable method to obtain a property list, accumulates the
 * resolved object's index/value pairs through FUN_0006a4c0/FUN_0008e5d8, emits
 * the per-CPU bitmask state via FUN_00093c68/74/84 and an internal assert, and
 * finally writes the 0xf8-byte context out to param_1. Fatals if the object
 * chain is empty.
 * Confidence: low
 * Notes: SoftwareBreakpoint(1,0x939ac) and (1,0x939b0) on null objects;
 * FUN_00151a6c assert with s_AppleInternal_Library_BuildRoot_005c0e90. */
static void sk_dt_parse_symbols(unsigned long *out, long *prop)
{
    void (*get)(void *, long, long, void *, void *);
    unsigned long obj, base, tmp;
    unsigned char ctx[0xf8];
    unsigned long b0, b1, mask;

    (void)ctx;
    base = 0;
    get = *(void (**)(void *, long, long, void *, void *))(*prop + 0x1f0);
    get(&base, 0x12, 0, 0, &base);
    FUN_0007b5f4((unsigned long)&base);
    FUN_0036a1a0((void *)0x6ad9a0, 0, 0, 0);
    FUN_0008f840(0x6ad9a0, (unsigned long)&base);
    obj = base;
    if (obj == 0)
        SoftwareBreakpoint(1, 0x939ac);
    FUN_0006a4c0((unsigned long)&base, obj);
    FUN_0001e790();
    FUN_0008e5d8(0);
    FUN_00094654();
    FUN_000026e8((unsigned long)&base);
    FUN_0008f840(0x6ad9a0, (unsigned long)&base);
    obj = base;
    if (obj == 0)
        SoftwareBreakpoint(1, 0x939b0);
    FUN_0006a4c0((unsigned long)&base, obj);
    FUN_0008e5d8(0);
    FUN_00094654();

    b0 = FUN_00093c68(0);
    b1 = FUN_00093c68(1);
    FUN_00093c74(0, base);
    FUN_00093c74(1, base);
    FUN_00093c84(base, b1 | b0);
    FUN_00151a6c(0xf61dc, 0, 0x5c0e90, 0x105, 2, 0x29d, 0, 0);
    /* write 0xf8-byte context to out */
    (void)mask; (void)tmp;
}

/* FUN_000939d0 @ 0x000939d0   (est. sk_launcher_resolve_drop10)
 * Ghidra: void FUN_000939d0(void)
 * Resolves the +0x10 field and drops it.
 * Confidence: low */
static void sk_launcher_resolve_drop10(void)
{
    FUN_0036b8c0(0 + 0x10);
    FUN_0036b21c();
}

/* FUN_000939d4 @ 0x000939d4   (est. sk_launcher_resolve_drop10b)
 * Ghidra: void FUN_000939d4(void)
 * Resolves the +0x10 field and drops it (duplicate).
 * Confidence: low */
static void sk_launcher_resolve_drop10b(void)
{
    FUN_0036b8c0(0 + 0x10);
    FUN_0036b21c();
}

/* FUN_00093a60 @ 0x00093a60   (est. sk_launcher_external_forward)
 * Ghidra: void FUN_00093a60(void)
 * Forwards to sk_exclave_launcher_external (get-or-create the external helper).
 * Confidence: medium */
static void sk_launcher_external_forward(void)
{
    FUN_00092990();
}

/* FUN_00093a64 @ 0x00093a64   (est. sk_launcher_external_forwardb)
 * Ghidra: void FUN_00093a64(void)
 * Forwards to sk_exclave_launcher_external (duplicate).
 * Confidence: medium */
static void sk_launcher_external_forwardb(void)
{
    FUN_00092990();
}

/* FUN_00093a88 @ 0x00093a88   (est. sk_cap_slot_read)
 * Ghidra: undefined1 FUN_00093a88(void)
 * Reads the capability slot of the current launcher: if the cap word grants
 * access (thunk_FUN_00072664 bit 0), computes an index and rebuilds the slot
 * descriptor via FUN_001fc840; otherwise returns an empty (0) slot byte.
 * Confidence: low
 * Notes: FUN_003a261c reads object refcount; FUN_00002534 class lookup. */
static unsigned char sk_cap_slot_read(void)
{
    unsigned long desc, idx, obj, cls;
    unsigned char slot;

    desc = FUN_00072664(0);
    if ((desc & 1) == 0) {
        slot = 0;
    } else {
        obj = *(unsigned long *)(0);            /* unaff_x20[0] */
        FUN_003a261c(obj);
        cls = FUN_00002534(0x64e878, 0x4c06d0);
        FUN_001fc840(0, &slot, desc & 0xffffffff, 0, cls);
        *(unsigned long *)(0) = obj;
        idx = 0; (void)idx;
    }
    return slot;
}

/* FUN_00093b24 @ 0x00093b24   (est. sk_cap_table_insert)
 * Ghidra: undefined1 FUN_00093b24(undefined8, undefined8, undefined8)
 * Inserts a (value, tag) pair into the launcher's capability table at the slot
 * index derived from param_3's cap word. Grows the +0x10 element count when
 * needed (SCARRY8 checked -> breakpoint), validates the resulting index, and
 * writes {byte cap, value} into *(obj+0x38)+idx*0x10. Returns the previous
 * slot byte (0 if the table was grown/empty).
 * Confidence: low
 * Notes: SoftwareBreakpoint(1,0x93c48) on overflow; FUN_002591b4(0x677790)
 * fatal on index mismatch; FUN_00258c60 grows the table. */
static unsigned char sk_cap_table_insert(unsigned long value, unsigned long tag,
                                         unsigned long cap)
{
    unsigned long obj, count, desc, idx, cls;
    unsigned char *slot, prev;

    obj = *(unsigned long *)(0);                /* unaff_x20[0] */
    FUN_003a261c(obj);
    desc = FUN_00072664(cap);
    idx = desc & 0xffffffff;
    count = *(unsigned long *)(obj + 0x10);
    if (count + 1 < count)                      /* SCARRY8 overflow */
        SoftwareBreakpoint(1, 0x93c48);
    cls = FUN_00002534(0x64e878, 0x4c06d0);
    if ((FUN_00258c60(FUN_003a261c(obj), count + 1, cls) & 1) != 0) {
        /* re-derive index after growth */
        idx = FUN_00072664(cap) & 0xffffffff;
    }
    if ((desc & 1) == 0) {
        FUN_00081c1c(idx, cap, value, tag, obj);
        prev = 0;
    } else {
        slot = (unsigned char *)(*(long *)(obj + 0x38) + idx * 0x10);
        prev = *slot;
        *slot = (unsigned char)value;
        *(unsigned long *)(slot + 8) = tag;
    }
    *(unsigned long *)(0) = obj;
    return prev;
}

/* FUN_00093c58 @ 0x00093c58   (est. sk_lock_acquire_masked)
 * Ghidra: void FUN_00093c58(ulong)
 * Acquires a lock word, clearing the bit-63 tag before the acquire.
 * Confidence: high
 * Notes: used everywhere to lock launcher/object words. */
static void sk_lock_acquire_masked(unsigned long lock)
{
    FUN_0036b270(lock & 0x7fffffffffffffffUL);
}

/* FUN_00093c60 @ 0x00093c60   (est. sk_lock_release_masked)
 * Ghidra: void FUN_00093c60(ulong)
 * Releases a lock word, clearing the bit-63 tag before the release.
 * Confidence: high */
static void sk_lock_release_masked(unsigned long lock)
{
    FUN_0036b118(lock & 0x7fffffffffffffffUL);
}

/* FUN_00093c68 @ 0x00093c68   (est. sk_bitmask_shift)
 * Ghidra: long FUN_00093c68(ulong)
 * Returns 1 << (param_1 & 0x3f): a bitmask for a per-CPU bit index.
 * Confidence: high */
static long sk_bitmask_shift(unsigned long index)
{
    return 1L << (index & 0x3f);
}

/* FUN_00093c74 @ 0x00093c74   (est. sk_percpu_slot_store)
 * Ghidra: void FUN_00093c74(long, undefined8)
 * Stores param_2 into the per-CPU slot array at index param_1: writes
 * tpidrro_el0 + param_1*8 + 0x10.
 * Confidence: high
 * Notes: tpidrro_el0 = per-CPU base. */
static void sk_percpu_slot_store(long index, unsigned long value)
{
    unsigned long base;

    base = (unsigned long)tpidrro_el0;
    *(unsigned long *)(base + index * 8 + 0x10) = value;
}

/* FUN_00093c84 @ 0x00093c84   (est. sk_supervisor_call0)
 * Ghidra: void FUN_00093c84(undefined8, undefined8)
 * Stashes (0, param_2) into the per-CPU slots, issues CallSupervisor(0), and
 * clears the slots — an SVC into a lower/guard level passing one argument.
 * Confidence: high
 * Notes: CallSupervisor(0) is the GEXIT-style supervisor entry. */
static void sk_supervisor_call0(unsigned long a, unsigned long b)
{
    unsigned long *slots;

    slots = (unsigned long *)tpidrro_el0;
    slots[0] = 0;
    slots[1] = b;
    CallSupervisor(0);
    slots[0] = 0;
}

/* FUN_00093ca0 @ 0x00093ca0   (est. sk_vtable_call_48_flag)
 * Ghidra: void FUN_00093ca0(byte *)
 * Dispatches the +0x48 vtable method of the current launcher and stores the
 * low bit of its result into *param_1.
 * Confidence: low */
static void sk_vtable_call_48_flag(unsigned char *out)
{
    unsigned long self, (*fn)(void);

    FUN_000027e8();
    self = 0;                              /* extraout_x16 receiver */
    fn = *(unsigned long (**)(void))(self + 0x48);
    *out = (unsigned char)(fn() & 1);
}

/* FUN_00093ce4 @ 0x00093ce4   (est. sk_vtable_call_50)
 * Ghidra: void FUN_00093ce4(undefined1 *)
 * Dispatches the +0x50 vtable method of the current launcher, passing the byte
 * at *param_1 as its argument.
 * Confidence: low */
static void sk_vtable_call_50(unsigned char *arg)
{
    unsigned long self, (*fn)(unsigned long);

    FUN_000027e8();
    self = 0;                              /* extraout_x16 receiver */
    fn = *(unsigned long (**)(unsigned long))(self + 0x50);
    fn(*arg);
}

/* FUN_00093e98 @ 0x00093e98   (est. sk_dt_log_string_ref)
 * Ghidra: void FUN_00093e98(void)
 * Logs the DT string constant 0x64f8c0.
 * Confidence: low
 * Notes: FUN_00077770 string logger. */
static void sk_dt_log_string_ref(void)
{
    FUN_00077770(0x64f8c0);
}

/* FUN_00094374 @ 0x00094374   (est. sk_cap_table_insert64)
 * Ghidra: undefined8 FUN_00094374(undefined8, undefined8, undefined8)
 * Inserts an 8-byte capability value into the launcher's table at the slot
 * index from param_2/param_3, growing the table when needed. Returns the
 * previous 8-byte slot value (0 if the table was grown). Mirrors
 * sk_cap_table_insert but with 8-byte slots and a different tag source.
 * Confidence: low
 * Notes: SoftwareBreakpoint(1,0x94498) on count overflow;
 * FUN_002591b4(0x6753a0) fatal on index mismatch. */
static unsigned long sk_cap_table_insert64(unsigned long value, unsigned long a,
                                           unsigned long b)
{
    unsigned long obj, count, desc, idx, cls, prev, *slot;

    obj = *(unsigned long *)(0);                /* unaff_x20[0] */
    FUN_003a261c(obj);
    desc = FUN_0006ae9c(a, b);
    idx = desc & 0xffffffff;
    count = *(unsigned long *)(obj + 0x10);
    if (count + 1 < count)                      /* SCARRY8 overflow */
        SoftwareBreakpoint(1, 0x94498);
    cls = FUN_00002534(0x64f950, 0x4c1418);
    if ((FUN_00258c60(FUN_003a261c(obj), count + 1, cls) & 1) != 0) {
        idx = FUN_0006ae9c(a, b) & 0xffffffff;
    }
    if ((desc & 1) == 0) {
        FUN_00081b9c(idx, a, b, value, obj);
        FUN_0036b270(b);
        prev = 0;
    } else {
        slot = (unsigned long *)(*(long *)(obj + 0x38) + idx * 8);
        prev = *slot;
        *slot = value;
    }
    *(unsigned long *)(0) = obj;
    return prev;
}

/* FUN_000944a8 @ 0x000944a8   (est. sk_identity_u32)
 * Ghidra: undefined4 FUN_000944a8(undefined4)
 * Identity: returns its 32-bit argument unchanged.
 * Confidence: high */
static unsigned int sk_identity_u32(unsigned int v)
{
    return v;
}

/* FUN_000944b4 @ 0x000944b4   (est. sk_vtable_indirect_call)
 * Ghidra: void FUN_000944b4(undefined8 *, undefined8, undefined8, undefined8, undefined8)
 * Indirect call through an object's vtable slot at param_1[2] (offset 0),
 * passing the object's data words and four extra args.
 * Confidence: low
 * Notes: jumptable not recovered by the decompiler. */
static void sk_vtable_indirect_call(unsigned long *obj, unsigned long a,
                                    unsigned long b, unsigned long c, unsigned long d)
{
    void (*fn)(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long);

    fn = *(void (**)(unsigned long, unsigned long, unsigned long, unsigned long,
                     unsigned long))(obj[2]);
    fn(obj[0], obj[1], a, b, c);
}

/* FUN_000944d8 @ 0x000944d8   (est. sk_vtable_indirect_call8)
 * Ghidra: void FUN_000944d8(undefined8 *, undefined8)
 * Indirect call through the vtable slot at param_1[2]+8, passing the object's
 * data words, param_2, and a trailing 0.
 * Confidence: low
 * Notes: jumptable not recovered. */
static void sk_vtable_indirect_call8(unsigned long *obj, unsigned long a)
{
    void (*fn)(unsigned long, unsigned long, unsigned long, unsigned long);

    fn = *(void (**)(unsigned long, unsigned long, unsigned long, unsigned long))(obj[2] + 8);
    fn(obj[0], obj[1], a, 0);
}

/* FUN_000944f8 @ 0x000944f8   (est. sk_vtable_call58)
 * Ghidra: void FUN_000944f8(undefined8, long, undefined8)
 * Indirect call through the vtable slot at param_2+0x58, passing param_1 and
 * param_3.
 * Confidence: low
 * Notes: jumptable not recovered. */
static void sk_vtable_call58(unsigned long a, long obj, unsigned long b)
{
    void (*fn)(unsigned long, unsigned long);

    fn = *(void (**)(unsigned long, unsigned long))(obj + 0x58);
    fn(a, b);
}

/* FUN_00094548 @ 0x00094548   (est. sk_noop_94548)
 * Ghidra: void FUN_00094548(void)
 * Empty no-op function (decompiles to a bare return).
 * Confidence: high */
static void sk_noop_94548(void)
{
}

/* FUN_0009455c @ 0x0009455c   (est. sk_field_lock_noop)
 * Ghidra: void FUN_0009455c(void)
 * Acquires a field lock (FUN_0036a1a0) with no visible effect.
 * Confidence: low */
static void sk_field_lock_noop(void)
{
    FUN_0036a1a0(0, 0, 0, 0);
}

/* FUN_0009456c @ 0x0009456c   (est. sk_noop_9456c)
 * Ghidra: void FUN_0009456c(void)
 * Empty no-op function.
 * Confidence: high */
static void sk_noop_9456c(void)
{
}

/* FUN_00094578 @ 0x00094578   (est. sk_zone_alloc_noop)
 * Ghidra: void FUN_00094578(void)
 * Allocates via FUN_0036a940 and discards the result.
 * Confidence: low */
static void sk_zone_alloc_noop(void)
{
    FUN_0036a940(0, 0, 0);
}

/* FUN_00094588 @ 0x00094588   (est. sk_fatal_external_launcher)
 * Ghidra: void FUN_00094588(void)
 * Fatal-error path: emits "Fatal error" for the ExternalExclaveLauncher and
 * never returns (the passed code 0x162 / 0xd00000000000001c mark the failure).
 * Confidence: medium
 * Notes: noreturn via FUN_001afa84. */
static void sk_fatal_external_launcher(void)
{
    FUN_001afa84(0x5accd0, 0xb, 2, 0xd00000000000001c, 0x80000000005c0de0,
                 0x5c0dc0, 0x39, 2);
}

/* FUN_000945d0 @ 0x000945d0   (est. sk_noop_945d0)
 * Ghidra: void FUN_000945d0(void)
 * Empty no-op function.
 * Confidence: high */
static void sk_noop_945d0(void)
{
}

/* FUN_0009461c @ 0x0009461c   (est. sk_noop_9461c)
 * Ghidra: void FUN_0009461c(void)
 * Empty no-op function.
 * Confidence: high */
static void sk_noop_9461c(void)
{
}

/* FUN_00094628 @ 0x00094628   (est. sk_field_lock_10)
 * Ghidra: void FUN_00094628(long)
 * Acquires the lock over the object field at param_1+0x10.
 * Confidence: low
 * Notes: FUN_0036b7f8 lock helper. */
static void sk_field_lock_10(long obj)
{
    FUN_0036b7f8(obj + 0x10);
}

/* FUN_00094634 @ 0x00094634   (est. sk_stack_clear_16)
 * Ghidra: void FUN_00094634(void)
 * Zero-initializes a 16-byte stack region (used before log emission).
 * Confidence: low
 * Notes: FUN_001ebfb0 zero-fill. */
static void sk_stack_clear_16(void)
{
    FUN_001ebfb0((void *)0, 0x10, 0);
}

/* FUN_00094654 @ 0x00094654   (est. sk_log_base_ptr)
 * Ghidra: undefined8 FUN_00094654(void)
 * Returns the log base pointer constant 0x677790.
 * Confidence: high */
static unsigned long sk_log_base_ptr(void)
{
    return 0x677790;
}

/* FUN_00094668 @ 0x00094668   (est. sk_log_dart_prop)
 * Ghidra: void FUN_00094668(undefined8, undefined8, undefined8, undefined8, char)
 * When the verbose log flag (DAT_006add10) is set, formats and emits a log
 * line about a "dart_..." property value: builds a log object, pushes the
 * value's key/tag parts plus the value text ("(none)" or a formatted value),
 * and emits it. Otherwise just drops the value reference.
 * Confidence: low
 * Notes: heavy log-emit helpers; the constants are log tag/kind values. */
static void sk_log_dart_prop(unsigned long a, unsigned long klo, unsigned long khi,
                             unsigned long v, char fmt)
{
    unsigned long cls, obj, tag, vlo;

    if (DAT_006add10 == 1) {
        cls = FUN_00002534(0x64c040, 0x4bbf40);
        obj = FUN_0036a9a0(cls, 0);
        *(unsigned long *)(obj + 0x10) = 0x4baeb0;
        *(unsigned long *)(obj + 0x18) = 0x4baeb8;
        FUN_002a4ab4(0x37);
        thunk_FUN_002acbb8(0xd00000000000001c, 0x80000000005c1290);
        thunk_FUN_002acbb8(klo, khi);
        thunk_FUN_002acbb8(0xd000000000000017, 0x80000000005c12b0);
        if (fmt == 1) {
            tag = 0xe600000000000000;
            vlo = 0x29656e6f6e28;              /* "(none)" */
        } else {
            vlo = FUN_00027724(0x671848);
            tag = vlo; (void)tag;
        }
        thunk_FUN_002acbb8(vlo, tag);
        FUN_003a25d4(tag);
        *(unsigned long *)(obj + 0x38) = 0x6753a0;
        *(unsigned long *)(obj + 0x20) = 0;
        *(unsigned long *)(obj + 0x28) = 0xe000000000000000;
        FUN_0026b434(obj, 0x20, 0xe100000000000000, 10, 0xe100000000000000);
        FUN_0036b588(obj);
        FUN_0036b6ac(FUN_00002688(), 0x20, 7);
        FUN_003a25d4(khi);
        return;
    }
    FUN_003a25d4(khi);
}

/* FUN_00094840 @ 0x00094840   (est. sk_log_dart_prop_a)
 * Ghidra: void FUN_00094840(undefined8, undefined8, undefined8, undefined8, char)
 * Verbose log of another "dart_..." property value (sibling of 0x94668 with a
 * different log kind). Same structure; drops the value when logging is off.
 * Confidence: low
 * Notes: log kind 0x35 in FUN_002a4ab4. */
static void sk_log_dart_prop_a(unsigned long a, unsigned long klo, unsigned long khi,
                               unsigned long v, char fmt)
{
    unsigned long cls, obj, tag, vlo;

    if (DAT_006add10 == 1) {
        cls = FUN_00002534(0x64c040, 0x4bbf40);
        obj = FUN_0036a9a0(cls, 0);
        *(unsigned long *)(obj + 0x10) = 0x4baeb0;
        *(unsigned long *)(obj + 0x18) = 0x4baeb8;
        FUN_002a4ab4(0x35);
        thunk_FUN_002acbb8(0xd00000000000001a, 0x80000000005c12d0);
        thunk_FUN_002acbb8(klo, khi);
        thunk_FUN_002acbb8(0xd000000000000017, 0x80000000005c12b0);
        if (fmt == 1) {
            tag = 0xe600000000000000;
            vlo = 0x29656e6f6e28;              /* "(none)" */
        } else {
            vlo = FUN_00027724(0x671848);
            tag = vlo; (void)tag;
        }
        thunk_FUN_002acbb8(vlo, tag);
        FUN_003a25d4(tag);
        *(unsigned long *)(obj + 0x38) = 0x6753a0;
        *(unsigned long *)(obj + 0x20) = 0;
        *(unsigned long *)(obj + 0x28) = 0xe000000000000000;
        FUN_0026b434(obj, 0x20, 0xe100000000000000, 10, 0xe100000000000000);
        FUN_0036b588(obj);
        FUN_0036b6ac(FUN_00002688(), 0x20, 7);
        FUN_003a25d4(khi);
        return;
    }
    FUN_003a25d4(khi);
}

/* FUN_00094a18 @ 0x00094a18   (est. sk_log_resolve_edge)
 * Ghidra: void FUN_00094a18(undefined8, long *, undefined8 *)
 * Verbose "[RESOLVE ... -> ...]" log of a DART edge resolution: runs the
 * +0xf8 vtable method of two objects and prints their results joined by
 * " -> ". Always releases the two object refs at the end.
 * Confidence: low
 * Notes: strings "[RESOLVE" (0x45564c4f5345525b) and " -> " (0x203e2d20). */
static void sk_log_resolve_edge(unsigned long a, long *o1, unsigned long *o2)
{
    unsigned long cls, obj;
    void (*fn)(void);
    unsigned long *inner;

    if (DAT_006add10 == 1) {
        cls = FUN_00002534(0x64c040, 0x4bbf40);
        obj = FUN_0036a9a0(cls, 0);
        *(unsigned long *)(obj + 0x10) = 0x4baeb0;
        *(unsigned long *)(obj + 0x18) = 0x4baeb8;
        FUN_002a4ab4(0x15);
        FUN_003a25d4(0xe000000000000000);
        fn = *(void (**)(void))(*o1 + 0xf8);
        fn();
        thunk_FUN_002acbb8(0, 0);
        FUN_003a25d4(0);
        thunk_FUN_002acbb8(0x203e2d20, 0xe400000000000000);   /* " -> " */
        inner = (unsigned long *)*o2;
        fn = *(void (**)(void))(*inner + 0xf8);
        FUN_0036b270((unsigned long)inner);
        fn();
        thunk_FUN_002acbb8(0, 0);
        FUN_0036b118((unsigned long)inner);
        FUN_003a25d4(0);
        *(unsigned long *)(obj + 0x38) = 0x6753a0;
        *(unsigned long *)(obj + 0x20) = 0x45564c4f5345525b;  /* "[RESOLVE" */
        *(unsigned long *)(obj + 0x28) = 0xed0000203a205d44;  /* "...] : " */
        FUN_0026b434(obj, 0x20, 0xe100000000000000, 10, 0xe100000000000000);
        FUN_0036b588(obj);
        FUN_0036b6ac(FUN_00002688(), 0x20, 7);
        FUN_0036b118((unsigned long)o1);
        return;
    }
    FUN_0036b118((unsigned long)o1);
}

/* FUN_00094bdc @ 0x00094bdc   (est. sk_log_dart_val)
 * Ghidra: void FUN_00094bdc(undefined8, undefined8, undefined8)
 * Verbose log of a DART value pair: emits the key/tag and value parts when the
 * log flag is set, else drops the value ref.
 * Confidence: low
 * Notes: log kind 0x21 in FUN_002a4ab4. */
static void sk_log_dart_val(unsigned long a, unsigned long vlo, unsigned long vhi)
{
    unsigned long cls, obj;

    if (DAT_006add10 == 1) {
        cls = FUN_00002534(0x64c040, 0x4bbf40);
        obj = FUN_0036a9a0(cls, 0);
        *(unsigned long *)(obj + 0x10) = 0x4baeb0;
        *(unsigned long *)(obj + 0x18) = 0x4baeb8;
        FUN_002a4ab4(0x21);
        FUN_003a25d4(0xe000000000000000);
        thunk_FUN_002acbb8(vlo, vhi);
        *(unsigned long *)(obj + 0x38) = 0x6753a0;
        *(unsigned long *)(obj + 0x20) = 0xd00000000000001f;
        *(unsigned long *)(obj + 0x28) = 0x80000000005c12f0;
        FUN_0026b434(obj, 0x20, 0xe100000000000000, 10, 0xe100000000000000);
        FUN_0036b588(obj);
        FUN_0036b6ac(FUN_00002688(), 0x20, 7);
        FUN_003a25d4(vhi);
        return;
    }
    FUN_003a25d4(vhi);
}

/* FUN_00094d04 @ 0x00094d04   (est. sk_log_resolve_edge_pair)
 * Ghidra: void FUN_00094d04(undefined8, long *, long *)
 * Verbose "[RESOLVE ... -> ...]" log of a two-sided DART edge resolution (both
 * sides run their +0xf8 vtable method). Releases both object refs at the end.
 * Confidence: low
 * Notes: same "[RESOLVE"/" -> " strings as 0x94a18. */
static void sk_log_resolve_edge_pair(unsigned long a, long *o1, long *o2)
{
    unsigned long cls, obj;
    void (*fn)(void);

    if (DAT_006add10 == 1) {
        cls = FUN_00002534(0x64c040, 0x4bbf40);
        obj = FUN_0036a9a0(cls, 0);
        *(unsigned long *)(obj + 0x10) = 0x4baeb0;
        *(unsigned long *)(obj + 0x18) = 0x4baeb8;
        FUN_002a4ab4(0x15);
        FUN_003a25d4(0xe000000000000000);
        fn = *(void (**)(void))(*o1 + 0xf8);
        fn();
        thunk_FUN_002acbb8(0, 0);
        FUN_003a25d4(0);
        thunk_FUN_002acbb8(0x203e2d20, 0xe400000000000000);   /* " -> " */
        fn = *(void (**)(void))(*o2 + 0xf8);
        fn();
        thunk_FUN_002acbb8(0, 0);
        FUN_003a25d4(0);
        *(unsigned long *)(obj + 0x38) = 0x6753a0;
        *(unsigned long *)(obj + 0x20) = 0x45564c4f5345525b;  /* "[RESOLVE" */
        *(unsigned long *)(obj + 0x28) = 0xed0000203a205d44;  /* "...] : " */
        FUN_0026b434(obj, 0x20, 0xe100000000000000, 10, 0xe100000000000000);
        FUN_0036b588(obj);
        FUN_0036b6ac(FUN_00002688(), 0x20, 7);
    }
    FUN_0036b118((unsigned long)o1);
    FUN_0036b118((unsigned long)o2);
}

/* FUN_00094e94 @ 0x00094e94   (est. sk_log_offset)
 * Ghidra: void FUN_00094e94(undefined8, undefined8, undefined8, undefined8)
 * Verbose log of an "Offset ..." message (with a formatted value) when the log
 * flag is set; else drops the value ref.
 * Confidence: low
 * Notes: "Offset " string 0x2074657366664f; log kind 0x38. */
static void sk_log_offset(unsigned long a, unsigned long b, unsigned long c,
                          unsigned long d)
{
    unsigned long cls, obj, tag, vlo;

    if (DAT_006add10 == 1) {
        cls = FUN_00002534(0x64c040, 0x4bbf40);
        obj = FUN_0036a9a0(cls, 0);
        *(unsigned long *)(obj + 0x10) = 0x4baeb0;
        *(unsigned long *)(obj + 0x18) = 0x4baeb8;
        FUN_002a4ab4(0x38);
        thunk_FUN_002acbb8(0x2074657366664f, 0xe700000000000000);  /* "Offset " */
        vlo = FUN_00027724(0x671848);
        tag = vlo; (void)tag;
        thunk_FUN_002acbb8(0, 0);
        FUN_003a25d4(0);
        thunk_FUN_002acbb8(0xd00000000000002d, 0x80000000005c1100);
        thunk_FUN_002acbb8(c, d);
        *(unsigned long *)(obj + 0x38) = 0x6753a0;
        *(unsigned long *)(obj + 0x20) = 0;
        *(unsigned long *)(obj + 0x28) = 0xe000000000000000;
        FUN_0026b434(obj, 0x20, 0xe100000000000000, 10, 0xe100000000000000);
        FUN_0036b588(obj);
        FUN_0036b6ac(FUN_00002688(), 0x20, 7);
        FUN_003a25d4(d);
        return;
    }
    FUN_003a25d4(d);
}

/* FUN_0009503c @ 0x0009503c   (est. sk_log_dart_resolve)
 * Ghidra: void FUN_0009503c(undefined8, undefined8, undefined8)
 * Verbose log of a DART resolve result; else drops the value ref.
 * Confidence: low
 * Notes: log kind 0x34 in FUN_002a4ab4. */
static void sk_log_dart_resolve(unsigned long a, unsigned long vlo, unsigned long vhi)
{
    unsigned long cls, obj;

    if (DAT_006add10 == 1) {
        cls = FUN_00002534(0x64c040, 0x4bbf40);
        obj = FUN_0036a9a0(cls, 0);
        *(unsigned long *)(obj + 0x10) = 0x4baeb0;
        *(unsigned long *)(obj + 0x18) = 0x4baeb8;
        FUN_002a4ab4(0x34);
        thunk_FUN_002acbb8(0xd000000000000032, 0x80000000005c1130);
        thunk_FUN_002acbb8(vlo, vhi);
        *(unsigned long *)(obj + 0x38) = 0x6753a0;
        *(unsigned long *)(obj + 0x20) = 0;
        *(unsigned long *)(obj + 0x28) = 0xe000000000000000;
        FUN_0026b434(obj, 0x20, 0xe100000000000000, 10, 0xe100000000000000);
        FUN_0036b588(obj);
        FUN_0036b6ac(FUN_00002688(), 0x20, 7);
        FUN_003a25d4(vhi);
        return;
    }
    FUN_003a25d4(vhi);
}

/* FUN_00095184 @ 0x00095184   (est. sk_dart_map_parse)
 * Ghidra: void FUN_00095184(long *, undefined8 *, undefined8, undefined8)
 * Core DART/IOMMU mapping parser. Walks the device-tree properties of a DART
 * node: reads its type tag (vtable +0x88 == '\t' selects the DART path),
 * gathers "symbol" (0x6c6f626d7973), "dart_id" (0x64695f74726164),
 * "dart_sid" (0x6469735f74726164), "dart_baseaddr" (0x7361625f74726164),
 * "dart_length" (0x6e656c5f74726164) properties from the DT, validates each
 * (DART edge referencing DT mapper / that does not match DT DART ID), and
 * builds an exclave DART mapping object via FUN_001227bc. On success returns
 * the mapping through *param_1; on failure fatals with the mapped error code.
 * Confidence: low
 * Notes: strings s_DART_edge_referencing_DT_mapper_005c1250 and
 * s_that_does_not_match_DT_DART_ID_005c1280; many vtable +0x88/a0/58/70/110
 * method calls; heavy log/format helpers. */
static void sk_dart_map_parse(long *out, unsigned long *launcher, unsigned long a,
                              unsigned long b)
{
    unsigned long *top, *sub;
    unsigned char c;
    unsigned long desc, vlo, vhi, sys, dart_id, dart_sid, dart_base, dart_len;
    unsigned long result, alloc, wrap, base;
    long obj;
    int code = 0;

    (void)a; (void)b;
    top = (unsigned long *)*launcher;
    c = (unsigned char)((*(unsigned long (**)(void))(*top + 0x88))());
    if (c != '\t') {
        *out = (long)top;
        FUN_0036b270((unsigned long)top);
        return;
    }
    obj = *top;
    sys = (*(unsigned long (**)(void))(obj + 0xa0))();   /* get symbol list */
    FUN_00097198();
    if (sys != 0) {
        FUN_0036b270((unsigned long)top);
        desc = FUN_0006ae9c(0xd000000000000010, 0x80000000005c11d0);
        if ((desc & 1) != 0) {
            FUN_000971b8();
            vlo = *(unsigned long *)(sys + 0);
            vhi = *(unsigned long *)(sys + 8);
            FUN_0036b270(0);
            FUN_0009725c();
            sys = (*(unsigned long (**)(void))(obj + 0xa0))();
            FUN_00097198();
            if (sys != 0) {
                FUN_0036b270((unsigned long)top);
                desc = FUN_0006ae9c(0x6c6f626d7973, 0xe600000000000000);   /* "symbol" */
                if ((desc & 1) != 0) {
                    FUN_000971b8();
                    dart_id = *(unsigned long *)(sys + 0);
                    dart_sid = *(unsigned long *)(sys + 8);
                    FUN_0036b270(0);
                    FUN_0009725c();
                    FUN_000970a4(b);
                    FUN_00097268();
                    sys = (*(unsigned long (**)(void))(obj + 0xa0))();
                    FUN_00097198();
                    if (sys != 0) {
                        FUN_0036b270((unsigned long)top);
                        desc = FUN_0006ae9c(0x64695f74726164, 0xe700000000000000); /* "dart_id" */
                        if ((desc & 1) != 0) {
                            FUN_000971b8();
                            vlo = *(unsigned long *)(sys + 0);
                            dart_sid = *(unsigned long *)(sys + 8);
                            FUN_0036b270(dart_sid);
                            FUN_0009725c();
                            FUN_000970d4();
                            FUN_00097204();
                            FUN_00097268();
                            sub = (unsigned long *)sys;
                            FUN_003a25d4((unsigned long)sub);
                            if (FUN_00097298() & 1) {
                                FUN_003a25d4(dart_sid);
                                sys = (*(unsigned long (**)(void))(obj + 0xa0))();
                                FUN_00097198();
                                if (sys != 0) {
                                    FUN_0036b270((unsigned long)top);
                                    desc = FUN_0006ae9c(0x6469735f74726164, 0xe800000000000000); /* "dart_sid" */
                                    if ((desc & 1) != 0) {
                                        FUN_000971b8();
                                        vlo = *(unsigned long *)(sys + 0);
                                        dart_sid = *(unsigned long *)(sys + 8);
                                        FUN_0036b270(dart_sid);
                                        FUN_0009725c();
                                        FUN_000970d4();
                                        FUN_00097204();
                                        FUN_00097268();
                                        FUN_003a25d4(dart_sid);
                                        sys = (*(unsigned long (**)(void))(obj + 0xa0))();
                                        FUN_00097198();
                                        if (sys != 0) {
                                            desc = FUN_0006ae9c(0x7361625f74726164, 0xed00007264646165); /* "dart_baseaddr" */
                                            if ((desc & 1) != 0) {
                                                FUN_000971b8();
                                                vlo = *(unsigned long *)(sys + 0);
                                                vhi = *(unsigned long *)(sys + 8);
                                                FUN_0036b270(vhi);
                                                FUN_003a25d4((unsigned long)top);
                                                FUN_0036a940(0, 0, 0);
                                                FUN_00094668(0, vlo, vhi, 0, 0);
                                            } else {
                                                FUN_003a25d4((unsigned long)top);
                                            }
                                        } else {
                                            FUN_003a25d4((unsigned long)top);
                                        }
                                        sys = (*(unsigned long (**)(void))(obj + 0xa0))();
                                        FUN_00097198();
                                        if (sys != 0) {
                                            desc = FUN_0006ae9c(0x6e656c5f74726164, 0xeb00000000687467); /* "dart_length" */
                                            if ((desc & 1) == 0) {
                                                FUN_003a25d4((unsigned long)top);
                                            } else {
                                                FUN_000971b8();
                                                vlo = *(unsigned long *)(sys + 0);
                                                vhi = *(unsigned long *)(sys + 8);
                                                FUN_0036b270(vhi);
                                                FUN_003a25d4((unsigned long)top);
                                                FUN_0036a940(0, 0, 0);
                                                FUN_00094840(0, vlo, vhi, 0, 0);
                                            }
                                        } else {
                                            FUN_003a25d4((unsigned long)top);
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    /* Build the exclave DART mapping object. */
    base = (*(unsigned long (**)(void))(obj + 0x58))();
    FUN_00097274();
    wrap = (*(unsigned long (**)(void))(obj + 0x70))();
    alloc = FUN_00002534(0x64f958, 0x4c1430);
    obj = FUN_0036a9a0(alloc, 0);
    *(unsigned long *)(obj + 0x10) = 0x4c1420;
    *(unsigned long *)(obj + 0x18) = 0x4c1428;
    *(unsigned long *)(obj + 0x20) = 0x6c6f626d7973;    /* "symbol" */
    *(unsigned long *)(obj + 0x28) = 0xe600000000000000;
    *(unsigned long *)(obj + 0x30) = dart_id;
    *(unsigned long *)(obj + 0x38) = dart_sid;
    *(unsigned long *)(obj + 0x40) = 0xd000000000000010;
    *(unsigned long *)(obj + 0x48) = 0x80000000005c11d0;
    *(unsigned long *)(obj + 0x50) = dart_len;
    *(unsigned long *)(obj + 0x58) = dart_base;
    *(unsigned long *)(obj + 0x60) = 0x64695f74726164;  /* "dart_id" */
    *(unsigned long *)(obj + 0x68) = 0xe700000000000000;
    FUN_000970d4();
    result = FUN_001f0130(obj, 0x6753a0, 0x6753a0, 0x66dfb8);
    wrap = FUN_00139574(0);
    alloc = FUN_0036a940(wrap, 0x30, 7);
    obj = FUN_001227bc(base, wrap, 9, result, alloc);
    *out = obj;
    /* optional sub-resolution hooks */
    if (0 != 0) {   /* local_80 != 1 */
        FUN_00097154();
        FUN_00027724(0);
        FUN_00097220();
        FUN_000972c4();
        FUN_00097220();
    }
    if (0 != 0) {   /* local_70 != 1 */
        FUN_00097154();
        FUN_00027724(0);
        FUN_00097220();
        FUN_000972c4();
    }
    wrap = FUN_00167a6c(0);
    FUN_0036b270((unsigned long)top);
    FUN_00094a18(wrap, (long *)top, &obj);
    *out = obj;
    (void)code; (void)result;
}

/* FUN_00095ba4 @ 0x00095ba4   (est. sk_dart_edge_map)
 * Ghidra: void FUN_00095ba4(undefined8 *, undefined8 *, undefined8 *, undefined8)
 * Resolves a DART edge mapping: collects the "dt_name"/"dt_compatible" props,
 * accumulates up to two "symbol" and "dt_comp... compatible" entries plus a
 * "dart_id"/"dart_reg_index" numeric value into a growable list, parses the
 * index value (decimal), and on match invokes the map callback. On failure
 * logs "Offset ..." and fatals. Returns the resulting object via *param_1.
 * Confidence: low
 * Notes: strings dt_name (0x656d616e5f7464), dt_compatible (0x61706d6f635f7464),
 * dt_reg_index (0x695f6765725f7464); the "+/-/digit" parser; heavy log helpers. */
static void sk_dart_edge_map(unsigned long *out, unsigned long *launcher,
                             unsigned long *props, unsigned long b)
{
    long *top, *list, *slot;
    unsigned long count, cap, vlo, vhi, idx, val, kind;
    unsigned char c;
    void (*get_props)(void);
    void (*notify)(unsigned long, unsigned long);
    long *(*get_props_r)(void);

    (void)b;
    (void)get_props;
    top = (long *)*launcher;
    FUN_000972c4();
    c = (unsigned char)((*(unsigned long (**)(void))(0 + 0x88))());
    if (c != '\x04') {
        *out = (unsigned long)top;
        FUN_0036b270((unsigned long)top);
        return;
    }
    get_props_r = *(long *(**)(void))(*top + 0xa0);
    list = get_props_r();
    if (*(long *)(list + 0x10) == 0) {
        FUN_003a25d4((unsigned long)list);
        list = 0;
    } else {
        FUN_0036b270((unsigned long)list);
        if ((FUN_0006ae9c(0x656d616e5f7464, 0xe700000000000000) & 1) == 0) {
            FUN_0036a2610((unsigned long)list, 2);
            list = 0;
        } else {
            slot = (long *)(*(long *)(list + 0x38) + 0);
            vlo = slot[0]; vhi = slot[1];
            FUN_0036b270(vhi);
            FUN_0036a2610((unsigned long)list, 2);
            count = *(unsigned long *)(0 + 0x10);
            if (*(unsigned long *)(0 + 0x18) >> 1 <= count)
                FUN_000972d0(0);
            *(unsigned long *)(0 + 0x10) = count + 1;
            *(unsigned long *)(0 + count * 0x18 + 0x20) = vlo;
            *(unsigned long *)(0 + count * 0x18 + 0x28) = vhi;
            *(unsigned char *)(0 + count * 0x18 + 0x30) = 1;
        }
    }
    /* second property: dt_compatible */
    list = get_props_r();
    if (*(long *)(list + 0x10) != 0) {
        FUN_0036b270((unsigned long)list);
        if ((FUN_0006ae9c(0x61706d6f635f7464, 0xed0000656c626974) & 1) != 0) {
            slot = (long *)(*(long *)(list + 0x38) + 0);
            vlo = slot[0]; vhi = slot[1];
            FUN_0036b270(vhi);
            FUN_0036a2610((unsigned long)list, 2);
            count = *(unsigned long *)(0 + 0x10);
            if (*(unsigned long *)(0 + 0x18) >> 1 <= count)
                FUN_000972d0(0);
            *(unsigned long *)(0 + 0x10) = count + 1;
            *(unsigned long *)(0 + count * 0x18 + 0x20) = vlo;
            *(unsigned long *)(0 + count * 0x18 + 0x28) = vhi;
            *(unsigned char *)(0 + count * 0x18 + 0x30) = 0;
        }
    }
    /* numeric "dart_id"/"dt_reg_index" resolution + callback (simplified) */
    FUN_0036b270((unsigned long)top);
    FUN_0036b118(0);
    *out = (unsigned long)top;
    (void)cap; (void)idx; (void)val; (void)kind; (void)notify;
}

/* FUN_0009647c @ 0x0009647c   (est. sk_dart_index_parse)
 * Ghidra: void FUN_0009647c(long *, long *, undefined8 *, undefined8)
 * Parses a DART "reg-index" numeric property into a value, matching the "dart"
 * node type (\x04). Handles decimal and hexadecimal ("0x") and sign prefixes,
 * validates the result, and either maps it or logs an "Offset ..." fatal.
 * Returns the resulting mapping via *param_1.
 * Confidence: low
 * Notes: SoftwareBreakpoint(1,0x96b38/48/44/3c/40) on malformed strings;
 * FUN_000b02dc base-16 parse; heavy log helpers. */
static void sk_dart_index_parse(long *out, long *launcher, unsigned long *props,
                                unsigned long b)
{
    long top, list, count;
    unsigned long vlo, vhi, val;
    unsigned char c;

    (void)b;
    top = *launcher;
    FUN_000972c4();
    c = (unsigned char)((*(unsigned long (**)(void))(0 + 0x88))());
    if (c != '\x04') {
        *out = top;
        FUN_0036b270((unsigned long)top);
        return;
    }
    FUN_00097274();
    list = *(long *)(0 + 0xa0);
    FUN_00097198();
    FUN_0036b270((unsigned long)top);
    if ((FUN_0006ae9c(0xd000000000000017, 0x80000000005c1060) & 1) == 0) {
        FUN_003a25d4((unsigned long)top);
        *out = top;
        FUN_0036b270((unsigned long)top);
        return;
    }
    FUN_000971b8();
    vlo = *(unsigned long *)(0 + 0);
    vhi = *(unsigned long *)(0 + 8);
    FUN_0036b270(vhi);
    FUN_0009725c();
    /* decimal/hex parse of the value (simplified faithful skeleton) */
    val = vlo;
    FUN_003a25d4(vhi);
    FUN_003a25d4((unsigned long)top);
    FUN_0036b270((unsigned long)top);
    FUN_0036b118(0);
    *out = top;
    (void)list; (void)count; (void)val; (void)c;
}

/* FUN_00096c74 @ 0x00096c74   (est. sk_dart_map_collect)
 * Ghidra: void FUN_00096c74(long *, undefined8, undefined8, undefined8)
 * Top-level DART mapping collector: pulls the launcher's three DT lists
 * (vtable +0xa0) and, for each non-empty symbol/edge list, runs the
 * corresponding parse (sk_dart_map_parse / sk_dart_edge_map /
 * sk_dart_index_parse), collecting non-null results into an output growable
 * list. Finally builds a mapping object and returns it.
 * Confidence: low
 * Notes: three nested list-drain loops; SoftwareBreakpoint(1,0x96f4c/50/54)
 * on out-of-bounds; FUN_0012540c final mapping build. */
static void sk_dart_map_collect(long *out, unsigned long a, unsigned long b,
                                unsigned long c)
{
    unsigned long *l1, *l2, *l3, *res;
    unsigned long i1, i2, i3, n1, n2, n3, item, count;

    (void)a; (void)b; (void)c;
    res = 0;
    l1 = (unsigned long *)((*(unsigned long (**)(void))(*(long *)0 + 0xa0))());
    n1 = *(unsigned long *)(l1 + 0x10);
    for (i1 = 0; i1 < n1; i1++) {
        item = *(unsigned long *)(l1 + i1 * 8 + 0x20);
        FUN_0036b270(item);
        sk_dart_map_parse(out, &item, b, c);
        FUN_0036b118(item);
        if (*out != 0) {
            count = *(unsigned long *)(res + 0x10);
            if (*(unsigned long *)(res + 0x18) >> 1 <= count)
                FUN_001a0774(0, count + 1, 1);
            *(unsigned long *)(res + 0x10) = count + 1;
            *(unsigned long *)(res + count * 8 + 0x20) = *out;
        }
    }
    l2 = (unsigned long *)((*(unsigned long (**)(void))(*(long *)0 + 0xa0))());
    n2 = *(unsigned long *)(l2 + 0x10);
    for (i2 = 0; i2 < n2; i2++) {
        item = *(unsigned long *)(l2 + i2 * 8 + 0x20);
        FUN_0036b270(item);
        sk_dart_edge_map((unsigned long *)out, &item, &b, c);
        FUN_0036b118(item);
        if (*out != 0) {
            count = *(unsigned long *)(res + 0x10);
            if (*(unsigned long *)(res + 0x18) >> 1 <= count)
                FUN_001a0774(0, count + 1, 1);
            *(unsigned long *)(res + 0x10) = count + 1;
            *(unsigned long *)(res + count * 8 + 0x20) = *out;
        }
    }
    l3 = (unsigned long *)((*(unsigned long (**)(void))(*(long *)0 + 0xa0))());
    n3 = *(unsigned long *)(l3 + 0x10);
    for (i3 = 0; i3 < n3; i3++) {
        item = *(unsigned long *)(l3 + i3 * 8 + 0x20);
        FUN_0036b270(item);
        sk_dart_index_parse(out, (long *)&item, &b, c);
        FUN_0036b118(item);
        if (*out != 0) {
            count = *(unsigned long *)(res + 0x10);
            if (*(unsigned long *)(res + 0x18) >> 1 <= count)
                FUN_001a0774(0, count + 1, 1);
            *(unsigned long *)(res + 0x10) = count + 1;
            *(unsigned long *)(res + count * 8 + 0x20) = *out;
        }
    }
    FUN_0036b118((unsigned long)l1);
    FUN_0036b118((unsigned long)l2);
    FUN_0036b118((unsigned long)l3);
    FUN_0012540c((*(unsigned long (**)(void))(*(long *)0 + 0x88))(), (unsigned long)res);
    (void)n2; (void)n3; (void)i3;
}

/* FUN_00096f78 @ 0x00096f78   (est. sk_tagged_ptr_deref8)
 * Ghidra: long FUN_00096f78(ulong)
 * Untags a tagged pointer (clears bit 0, dereferencing the stored base if
 * tagged) and returns base+8 + *(int*)(base+8): the payload pointer of a
 * tagged value whose length word sits at offset 8.
 * Confidence: high */
static long sk_tagged_ptr_deref8(unsigned long p)
{
    if ((p & 1) != 0)
        p = *(unsigned long *)(p & 0xfffffffffffffffeUL);
    return (long)(p + 8) + (long)*(int *)(p + 8);
}

/* FUN_00096fa8 @ 0x00096fa8   (est. sk_release_strings_by_kind)
 * Ghidra: void FUN_00096fa8(undefined8, undefined8, undefined8, undefined8,
 *                           undefined8, undefined8, undefined8, undefined8, byte)
 * Releases a set of string/object refs selected by a small kind byte
 * (0..7 switch): for some kinds drops param_4/param_6/param_7 and param_2.
 * Confidence: low
 * Notes: degenerate switch collapsing to two FUN_003a25d4 releases. */
static void sk_release_strings_by_kind(unsigned long p1, unsigned long p2,
                                       unsigned long p3, unsigned long p4,
                                       unsigned long p5, unsigned long p6,
                                       unsigned long p7, unsigned long p8,
                                       unsigned char kind)
{
    unsigned long a, b;

    (void)p1; (void)p3; (void)p5; (void)p8;
    if (kind > 7)
        return;
    switch (kind) {
    case 1: case 6: case 7:
        FUN_003a25d4(p4);
        a = p6; b = p2;
        break;
    case 2:
        a = p2; b = p4;
        break;
    case 3:
        a = p2; b = p4;
        break;
    case 4: case 5:
        FUN_003a25d4(p4);
        a = p7; b = p2;
        break;
    default:
        a = p2; b = p2;
        break;
    }
    FUN_003a25d4(a);
    FUN_003a25d4(b);
}

/* FUN_00097074 @ 0x00097074   (est. sk_tagged_ptr_deref_c)
 * Ghidra: long FUN_00097074(ulong)
 * Untags a tagged pointer and returns base+0xc + *(int*)(base+0xc): payload
 * pointer with length word at offset 0xc.
 * Confidence: high */
static long sk_tagged_ptr_deref_c(unsigned long p)
{
    if ((p & 1) != 0)
        p = *(unsigned long *)(p & 0xfffffffffffffffeUL);
    return (long)(p + 0xc) + (long)*(int *)(p + 0xc);
}

/* FUN_000970a4 @ 0x000970a4   (est. sk_tagged_ptr_deref4)
 * Ghidra: long FUN_000970a4(ulong)
 * Untags a tagged pointer and returns base+4 + *(int*)(base+4): payload
 * pointer with length word at offset 4.
 * Confidence: high */
static long sk_tagged_ptr_deref4(unsigned long p)
{
    if ((p & 1) != 0)
        p = *(unsigned long *)(p & 0xfffffffffffffffeUL);
    return (long)(p + 4) + (long)*(int *)(p + 4);
}

/* FUN_000970d4 @ 0x000970d4   (est. sk_noop_970d4)
 * Ghidra: void FUN_000970d4(void)
 * Empty no-op function.
 * Confidence: high */
static void sk_noop_970d4(void)
{
}

/* FUN_000970ec @ 0x000970ec   (est. sk_noop_970ec)
 * Ghidra: void FUN_000970ec(void)
 * Empty no-op function.
 * Confidence: high */
static void sk_noop_970ec(void)
{
}

/* FUN_00097100 @ 0x00097100   (est. sk_fatal_dt_resol)
 * Ghidra: void FUN_00097100(undefined8)
 * Fatal-error formatter for the dt_resol source: emits "Fatal error" with the
 * passed code and never returns.
 * Confidence: medium
 * Notes: noreturn FUN_001afa84; string s_InternalExclaveLauncher_dt_resol_005c10c0. */
static void sk_fatal_dt_resol(unsigned long code)
{
    FUN_001afa84(0x5accd0, 0xb, 2, 0, 0, 0x5c10c0, 0x2b, 2, code);
}

/* FUN_00097128 @ 0x00097128   (est. sk_log_resol_base)
 * Ghidra: undefined1 [16] FUN_00097128(void)
 * Returns the log base descriptor {0x6776f0, 0x671298} and stores w8 into the
 * caller's stack slot.
 * Confidence: low */
static unsigned long sk_log_resol_base(void)
{
    return 0x6776f0;
}

/* FUN_00097154 @ 0x00097154   (est. sk_noop_97154)
 * Ghidra: void FUN_00097154(void)
 * Empty no-op function.
 * Confidence: high */
static void sk_noop_97154(void)
{
}

/* FUN_00097170 @ 0x00097170   (est. sk_log_string_push)
 * Ghidra: void FUN_00097170(long)
 * Pushes a tagged string part (tag 0xd0..., value param_1-0x20 | hi-bit) onto
 * the log buffer.
 * Confidence: low */
static void sk_log_string_push(long v)
{
    thunk_FUN_002acbb8(0xd000000000000020, (unsigned long)(v - 0x20) | 0x8000000000000000UL);
}

/* FUN_00097188 @ 0x00097188   (est. sk_noop_97188)
 * Ghidra: void FUN_00097188(void)
 * Empty no-op function.
 * Confidence: high */
static void sk_noop_97188(void)
{
}

/* FUN_00097198 @ 0x00097198   (est. sk_noop_97198)
 * Ghidra: void FUN_00097198(void)
 * Empty no-op function.
 * Confidence: high */
static void sk_noop_97198(void)
{
}

/* FUN_000971a4 @ 0x000971a4   (est. sk_noop_971a4)
 * Ghidra: void FUN_000971a4(void)
 * Empty no-op function.
 * Confidence: high */
static void sk_noop_971a4(void)
{
}

/* FUN_000971b8 @ 0x000971b8   (est. sk_noop_971b8)
 * Ghidra: void FUN_000971b8(void)
 * Empty no-op function.
 * Confidence: high */
static void sk_noop_971b8(void)
{
}

/* FUN_000971c4 @ 0x000971c4   (est. sk_noop_971c4)
 * Ghidra: void FUN_000971c4(void)
 * Empty no-op function.
 * Confidence: high */
static void sk_noop_971c4(void)
{
}

/* FUN_000971e8 @ 0x000971e8   (est. sk_noop_971e8)
 * Ghidra: void FUN_000971e8(void)
 * Empty no-op function.
 * Confidence: high */
static void sk_noop_971e8(void)
{
}

/* FUN_00097204 @ 0x00097204   (est. sk_log_base_ptr2)
 * Ghidra: undefined8 FUN_00097204(void)
 * Returns the log base pointer constant 0x6776f0.
 * Confidence: high */
static unsigned long sk_log_base_ptr2(void)
{
    return 0x6776f0;
}

/* FUN_00097220 @ 0x00097220   (est. sk_log_base_ptr3)
 * Ghidra: undefined8 FUN_00097220(void)
 * Returns the log base pointer constant 0x677790.
 * Confidence: high */
static unsigned long sk_log_base_ptr3(void)
{
    return 0x677790;
}

/* FUN_0009723c @ 0x0009723c   (est. sk_stack_descriptor)
 * Ghidra: undefined1 [16] FUN_0009723c(void)
 * Returns a {&fp-0x48, 0x10} descriptor pair (a stack buffer + length).
 * Confidence: low */
static unsigned long sk_stack_descriptor(void)
{
    return 0x10;
}

/* FUN_0009724c @ 0x0009724c   (est. sk_noop_9724c)
 * Ghidra: void FUN_0009724c(void)
 * Empty no-op function.
 * Confidence: high */
static void sk_noop_9724c(void)
{
}

/* FUN_0009725c @ 0x0009725c   (est. sk_obj_drop)
 * Ghidra: void FUN_0009725c(void)
 * Drops a reference via FUN_003a2610.
 * Confidence: low */
static void sk_obj_drop(void)
{
    FUN_003a2610(0, 0);
}

/* FUN_00097268 @ 0x00097268   (est. sk_stack_pair_desc)
 * Ghidra: undefined1 [16] FUN_00097268(void)
 * Returns a {stack-arg, *(fp-0x48)} descriptor pair.
 * Confidence: low */
static unsigned long sk_stack_pair_desc(void)
{
    return *(unsigned long *)(0 - 0x48);
}

/* FUN_00097274 @ 0x00097274   (est. sk_noop_97274)
 * Ghidra: void FUN_00097274(void)
 * Empty no-op function.
 * Confidence: high */
static void sk_noop_97274(void)
{
}

/* FUN_00097280 @ 0x00097280   (est. sk_log_contains)
 * Ghidra: undefined1 [16] FUN_00097280(void)
 * Returns the tagged string " contains " ({0x6e6961746e6f6320, 0x2073}).
 * Confidence: high */
static unsigned long sk_log_contains(void)
{
    return 0x6e6961746e6f6320;
}

/* FUN_00097298 @ 0x00097298   (est. sk_soft_assert)
 * Ghidra: void FUN_00097298(void)
 * Runs a soft assert check on the passed value.
 * Confidence: low
 * Notes: FUN_002a0cf8 assert helper. */
static unsigned long sk_soft_assert(void)
{
    FUN_002a0cf8(0);
    return 0;
}

/* FUN_000972b0 @ 0x000972b0   (est. sk_noop_972b0)
 * Ghidra: void FUN_000972b0(void)
 * Empty no-op function.
 * Confidence: high */
static void sk_noop_972b0(void)
{
}

/* FUN_000972c4 @ 0x000972c4   (est. sk_noop_972c4)
 * Ghidra: void FUN_000972c4(void)
 * Empty no-op function.
 * Confidence: high */
static void sk_noop_972c4(void)
{
}

/* FUN_000972d0 @ 0x000972d0   (est. sk_vec_needs_grow)
 * Ghidra: bool FUN_000972d0(ulong)
 * Returns true if the element count is > 1 (capacity growth check).
 * Confidence: high */
static bool sk_vec_needs_grow(unsigned long count)
{
    return count > 1;
}

/* FUN_000972e4 @ 0x000972e4   (est. sk_launcher_construct)
 * Ghidra: long FUN_000972e4(long *, undefined8, undefined8, long, undefined8, undefined8)
 * Constructs a launcher object at the current object: initializes its field
 * slots (lock words, empty list heads, flag), stores the four context words,
 * resolves the launcher class, allocates the launcher object and a completion
 * object, and wires up their vtable pointers. Returns the new object; fatals
 * if the class registration fails.
 * Confidence: low
 * Notes: FUN_0014aedc class lookup; SoftwareBreakpoint(1,0x9770c) on failure;
 * many FUN_0036a1a0/a20c field-lock pairs. */
static long sk_launcher_construct(long *arg1, unsigned long arg2, unsigned long arg3,
                                  long arg4, unsigned long arg5, unsigned long arg6)
{
    unsigned long self;
    long obj, cls, list, l2, v;
    unsigned long base, data, hold;
    void *(*alloc)(long, unsigned long, unsigned long, unsigned long);
    unsigned long (*get)(void);
    void (*release)(unsigned long);

    self = 0;                                /* unaff_x20 */
    *(unsigned long *)(self + 0x30) = 0;
    *(unsigned long *)(self + 0x70) = 0;
    *(unsigned long *)(self + 0x38) = 0;
    *(unsigned char *)(self + 0x78) = 1;
    *(unsigned long *)(self + 0x88) = 0;     /* empty list head */
    *(unsigned long *)(self + 0x90) = 0;
    *(unsigned long *)(self + 0x98) = 0;
    *(unsigned long *)(self + 0x10) = (unsigned long)arg1;
    *(unsigned long *)(self + 0x18) = arg2;
    *(unsigned long *)(self + 0x20) = arg3;
    FUN_0036a1a0((void *)(self + 0x30), 0, 1, 0);
    *(unsigned long *)(self + 0x30) = 1;
    FUN_0006e7c0(arg4, (void *)(self + 0x48));
    FUN_0036a1a0((void *)(self + 0x98), 0, 1, 0);
    *(unsigned long *)(self + 0x98) = arg6;
    FUN_0036b2d0((unsigned long)arg1, 2);
    FUN_0036b270(arg2);
    FUN_0036b270(arg3);
    cls = FUN_0014aedc(0x665f60, 0x665cd8);
    if (cls < 0)
        SoftwareBreakpoint(1, 0x9770c);
    /* allocate launcher + completion objects */
    base = (*(unsigned long (**)(void))(*arg1 + 0x48))();
    FUN_0036b118((unsigned long)arg1);
    list = (*(unsigned long (**)(void))(*arg1 + 0x38))();
    FUN_0036b118((unsigned long)arg1);
    *(unsigned long *)(self + 0x40) = list;
    v = FUN_0014aedc(0x665f60, 0x665cd8);
    FUN_0036b118(arg3);
    FUN_0036b118(arg2);
    FUN_0036b118((unsigned long)arg1);
    *(unsigned long *)(self + 0x28) = v;
    *(unsigned long *)(self + 0x80) = arg5;
    FUN_0036a1a0((void *)(self + 0x38), 0, 1, 0);
    *(unsigned long *)(self + 0x38) = 1;
    FUN_000026e8(arg4);
    return self;
    (void)obj; (void)l2; (void)data; (void)hold; (void)alloc; (void)get; (void)release;
}

/* FUN_0009781c @ 0x0009781c   (est. sk_launcher_construct_wrap)
 * Ghidra: undefined8 FUN_0009781c(undefined8, undefined8, undefined8, undefined8)
 * Wrapper that constructs a launcher object: builds a context, resolves the
 * class, allocates a 0xa0-byte launcher, and calls sk_launcher_construct,
 * releasing the three lock refs afterwards.
 * Confidence: low
 * Notes: FUN_0006e7c0/FUN_0008e328 context build; FUN_0036a940 alloc. */
static unsigned long sk_launcher_construct_wrap(unsigned long a, unsigned long b,
                                                unsigned long c, unsigned long d)
{
    unsigned long ctx[5], cls, self, v;

    FUN_0006e7c0(d, ctx);
    FUN_0008e328();
    FUN_0036b270(a);
    FUN_0036b270(b);
    FUN_0036b270(c);
    v = (*(unsigned long (**)(void))(0 + 0x38))();
    cls = FUN_00002534(0x64fc88, 0x4c1540);
    self = FUN_0036a940(cls, 0xa0, 7);
    v = sk_launcher_construct((long *)a, b, c, (long)d, v, 0x1e);
    FUN_0036b118(c);
    FUN_0036b118(b);
    FUN_0036b118(a);
    FUN_000026e8(d);
    return self;
    (void)ctx; (void)v;
}

/* FUN_00097920 @ 0x00097920   (est. sk_log_resolve_final)
 * Ghidra: void FUN_00097920(undefined8, undefined8)
 * Verbose "[RESOLVE ... ]" log of the final resolved object (via FUN_001a6a8c)
 * when the log flag is set; always releases the object ref.
 * Confidence: low
 * Notes: log kind 0x22; string tag 0xd000000000000020 / 0x80000000005c17c0. */
static void sk_log_resolve_final(unsigned long a, unsigned long obj)
{
    unsigned long cls, l2;

    if (DAT_006add10 == 1) {
        cls = FUN_00002534(0x64c040, 0x4bbf40);
        l2 = FUN_0036a9a0(cls, 0);
        *(unsigned long *)(l2 + 0x10) = 0x4baeb0;
        *(unsigned long *)(l2 + 0x18) = 0x4baeb8;
        FUN_002a4ab4(0x22);
        FUN_003a25d4(0xe000000000000000);
        FUN_001a6a8c(obj, 0x6619c0);
        thunk_FUN_002acbb8(0, 0);
        FUN_003a25d4(0);
        *(unsigned long *)(l2 + 0x38) = 0x6753a0;
        *(unsigned long *)(l2 + 0x20) = 0xd000000000000020;
        *(unsigned long *)(l2 + 0x28) = 0x80000000005c17c0;
        FUN_0026b434(l2, 0x20, 0xe100000000000000, 10, 0xe100000000000000);
        FUN_0036b588(l2);
        FUN_0036b6ac(FUN_00002688(), 0x20, 7);
        FUN_0036b118(obj);
        return;
    }
    FUN_0036b118(obj);
}

/* FUN_00097a58 @ 0x00097a58   (est. sk_log_resolve_final_a)
 * Ghidra: void FUN_00097a58(undefined8, undefined8)
 * Verbose "[RESOLVE ... ]" log variant (kind 0x39) with a different string tag;
 * always releases the object ref.
 * Confidence: low
 * Notes: string tag 0x80000000005c17f0. */
static void sk_log_resolve_final_a(unsigned long a, unsigned long obj)
{
    unsigned long cls, l2;

    if (DAT_006add10 == 1) {
        cls = FUN_00002534(0x64c040, 0x4bbf40);
        l2 = FUN_0036a9a0(cls, 0);
        *(unsigned long *)(l2 + 0x10) = 0x4baeb0;
        *(unsigned long *)(l2 + 0x18) = 0x4baeb8;
        FUN_002a4ab4(0x39);
        thunk_FUN_002acbb8(0xd000000000000037, 0x80000000005c17f0);
        FUN_001a6a8c(obj, 0x6619c0);
        thunk_FUN_002acbb8(0, 0);
        FUN_003a25d4(0);
        *(unsigned long *)(l2 + 0x38) = 0x6753a0;
        *(unsigned long *)(l2 + 0x20) = 0;
        *(unsigned long *)(l2 + 0x28) = 0xe000000000000000;
        FUN_0026b434(l2, 0x20, 0xe100000000000000, 10, 0xe100000000000000);
        FUN_0036b588(l2);
        FUN_0036b6ac(FUN_00002688(), 0x20, 7);
        FUN_0036b118(obj);
        return;
    }
    FUN_0036b118(obj);
}

/* FUN_00097b94 @ 0x00097b94   (est. sk_log_resolve_final_b)
 * Ghidra: void FUN_00097b94(undefined8, undefined8)
 * Verbose "[RESOLVE ... ]" log variant (kind 0x24); always releases obj.
 * Confidence: low
 * Notes: string tag 0x80000000005c1890. */
static void sk_log_resolve_final_b(unsigned long a, unsigned long obj)
{
    unsigned long cls, l2;

    if (DAT_006add10 == 1) {
        cls = FUN_00002534(0x64c040, 0x4bbf40);
        l2 = FUN_0036a9a0(cls, 0);
        *(unsigned long *)(l2 + 0x10) = 0x4baeb0;
        *(unsigned long *)(l2 + 0x18) = 0x4baeb8;
        FUN_002a4ab4(0x24);
        FUN_003a25d4(0xe000000000000000);
        FUN_001a6a8c(obj, 0x6619c0);
        thunk_FUN_002acbb8(0, 0);
        FUN_003a25d4(0);
        *(unsigned long *)(l2 + 0x38) = 0x6753a0;
        *(unsigned long *)(l2 + 0x20) = 0xd000000000000022;
        *(unsigned long *)(l2 + 0x28) = 0x80000000005c1890;
        FUN_0026b434(l2, 0x20, 0xe100000000000000, 10, 0xe100000000000000);
        FUN_0036b588(l2);
        FUN_0036b6ac(FUN_00002688(), 0x20, 7);
        FUN_0036b118(obj);
        return;
    }
    FUN_0036b118(obj);
}

/* FUN_00097ccc @ 0x00097ccc   (est. sk_log_resolve_addr)
 * Ghidra: void FUN_00097ccc(undefined8, long)
 * Verbose log of a resolve address (reads two words at param_2+0xb0/b8);
 * always releases the object.
 * Confidence: low
 * Notes: log kind 0x1a. */
static void sk_log_resolve_addr(unsigned long a, long obj)
{
    unsigned long cls, l2;

    if (DAT_006add10 == 1) {
        cls = FUN_00002534(0x64c040, 0x4bbf40);
        l2 = FUN_0036a9a0(cls, 0);
        *(unsigned long *)(l2 + 0x10) = 0x4baeb0;
        *(unsigned long *)(l2 + 0x18) = 0x4baeb8;
        FUN_002a4ab4(0x1a);
        FUN_003a25d4(0xe000000000000000);
        thunk_FUN_002acbb8(*(unsigned long *)(obj + 0xb0), *(unsigned long *)(obj + 0xb8));
        thunk_FUN_002acbb8(0xd000000000000017, 0x80000000005c16e0);
        *(unsigned long *)(l2 + 0x38) = 0x6753a0;
        *(unsigned long *)(l2 + 0x20) = 0x5b;
        *(unsigned long *)(l2 + 0x28) = 0xe100000000000000;
        FUN_0026b434(l2, 0x20, 0xe100000000000000, 10, 0xe100000000000000);
        FUN_0036b588(l2);
        FUN_0036b6ac(FUN_00002688(), 0x20, 7);
        FUN_0036b118(obj);
        return;
    }
    FUN_0036b118(obj);
}

/* FUN_00097dfc @ 0x00097dfc   (est. sk_vtable_call_1d0)
 * Ghidra: void FUN_00097dfc(undefined8 *, undefined8 *)
 * Acquires the lock on *param_1 and calls the +0x1d0 vtable method of the
 * object at *param_2.
 * Confidence: low */
static void sk_vtable_call_1d0(unsigned long *a, unsigned long *b)
{
    void (*fn)(void);

    fn = *(void (**)(void))(*(long *)*b + 0x1d0);
    FUN_0036b270(*a);
    fn();
}

/* FUN_00097e58 @ 0x00097e58   (est. sk_launcher_lock_get90)
 * Ghidra: void FUN_00097e58(void)
 * Acquires the field lock on +0x90 and locks the stored value.
 * Confidence: low */
static void sk_launcher_lock_get90(void)
{
    FUN_00084100(0 + 0x90);
    FUN_0036b270(*(unsigned long *)(0 + 0x90));
}

/* FUN_00097e84 @ 0x00097e84   (est. sk_launcher_set90)
 * Ghidra: void FUN_00097e84(undefined8)
 * Replaces the +0x90 field, releasing the prior value under the field lock.
 * Confidence: low */
static void sk_launcher_set90(unsigned long value)
{
    unsigned long old;

    FUN_0008e3b0(0 + 0x90);
    old = *(unsigned long *)(0 + 0x90);
    *(unsigned long *)(0 + 0x90) = value;
    FUN_0036b118(old);
}

/* FUN_00097ec0 @ 0x00097ec0   (est. sk_launcher_field90_desc)
 * Ghidra: undefined1 [16] FUN_00097ec0(undefined8)
 * Initializes the +0x90 field with param_1 and returns a {&DAT_0007bf58,
 * &self+0x90} descriptor.
 * Confidence: low */
static unsigned long sk_launcher_field90_desc(unsigned long v)
{
    FUN_0009e228(0 + 0x90, v);
    FUN_0036a1a0(0, 0, 0, 0);
    return 0 + 0x90;
}

/* FUN_00097f14 @ 0x00097f14   (est. sk_vtable_call_1e8)
 * Ghidra: void FUN_00097f14(undefined8 *, undefined8 *)
 * Acquires the lock on *param_1 and calls the +0x1e8 vtable method of the
 * object at *param_2.
 * Confidence: low */
static void sk_vtable_call_1e8(unsigned long *a, unsigned long *b)
{
    void (*fn)(void);

    fn = *(void (**)(void))(*(long *)*b + 0x1e8);
    FUN_0036b270(*a);
    fn();
}

/* FUN_00097f70 @ 0x00097f70   (est. sk_launcher_lock_geta8)
 * Ghidra: void FUN_00097f70(void)
 * Acquires the field lock on +0xa8 and locks the stored value.
 * Confidence: low */
static void sk_launcher_lock_geta8(void)
{
    FUN_00084100(0 + 0xa8);
    FUN_0036b270(*(unsigned long *)(0 + 0xa8));
}

/* FUN_00097f9c @ 0x00097f9c   (est. sk_launcher_seta8)
 * Ghidra: void FUN_00097f9c(undefined8)
 * Replaces the +0xa8 field, releasing the prior value under the field lock.
 * Confidence: low */
static void sk_launcher_seta8(unsigned long value)
{
    unsigned long old;

    FUN_0008e3b0(0 + 0xa8);
    old = *(unsigned long *)(0 + 0xa8);
    *(unsigned long *)(0 + 0xa8) = value;
    FUN_0036b118(old);
}

/* FUN_00097fd8 @ 0x00097fd8   (est. sk_launcher_fielda8_desc)
 * Ghidra: undefined1 [16] FUN_00097fd8(undefined8)
 * Initializes the +0xa8 field with param_1 and returns a {&DAT_0007bf58,
 * &self+0xa8} descriptor.
 * Confidence: low */
static unsigned long sk_launcher_fielda8_desc(unsigned long v)
{
    FUN_0009e228(0 + 0xa8, v);
    FUN_0036a1a0(0, 0, 0, 0);
    return 0 + 0xa8;
}

/* FUN_00098024 @ 0x00098024   (est. sk_launcher_getb0)
 * Ghidra: undefined1 [16] FUN_00098024(void)
 * Reads the +0xb0 16-byte descriptor and locks +0xb8.
 * Confidence: low */
static unsigned long sk_launcher_getb0(void)
{
    FUN_0036b270(*(unsigned long *)(0 + 0xb8));
    return *(unsigned long *)(0 + 0xb0);
}

/* FUN_0009805c @ 0x0009805c   (est. sk_launcher_lock_getc8)
 * Ghidra: undefined8 FUN_0009805c(void)
 * Acquires the field lock on +200 (0xc8) and returns its value.
 * Confidence: low */
static unsigned long sk_launcher_lock_getc8(void)
{
    FUN_00084100(0 + 200);
    return *(unsigned long *)(0 + 200);
}

/* FUN_00098084 @ 0x00098084   (est. sk_launcher_setc8)
 * Ghidra: void FUN_00098084(undefined8)
 * Sets the +200 (0xc8) field under the field lock.
 * Confidence: low */
static void sk_launcher_setc8(unsigned long value)
{
    FUN_0008e3b0(0 + 200);
    *(unsigned long *)(0 + 200) = value;
}

/* FUN_000980b8 @ 0x000980b8   (est. sk_launcher_fieldc8_desc)
 * Ghidra: undefined1 [16] FUN_000980b8(undefined8)
 * Initializes the +200 (0xc8) field with param_1 and returns a {&LAB_0006f910,
 * &self+200} descriptor.
 * Confidence: low */
static unsigned long sk_launcher_fieldc8_desc(unsigned long v)
{
    FUN_0009e228(0 + 200, v);
    FUN_0036a1a0(0, 0, 0, 0);
    return 0 + 200;
}

/* FUN_00098120 @ 0x00098120   (est. sk_launcher_get80)
 * Ghidra: undefined8 FUN_00098120(void)
 * Acquires the +0x80 field lock, returns the stored value and resolves it via
 * FUN_0009cf58, releasing the lock.
 * Confidence: low */
static unsigned long sk_launcher_get80(void)
{
    unsigned long v;

    FUN_0036a1a0((void *)(0 + 0x80), 0, 0, 0);
    v = *(unsigned long *)(0 + 0x80);
    FUN_0036b2d0(v, 2);
    FUN_0009cf58(&v);
    FUN_0036b118(v);
    return v;
}

/* FUN_000981a4 @ 0x000981a4   (est. sk_collect_symbols)
 * Ghidra: void FUN_000981a4(undefined8 *)
 * Collects the launcher's symbol list (vtable +0x1e0) into a single growable
 * list of 0xf8-byte records, merging each source list's records with bounds and
 * overlap checks. Returns the merged list via *param_1.
 * Confidence: low
 * Notes: FUN_00117cc4 memcpy of 0xf8-byte records; many SoftwareBreakpoint
 * bounds checks (0x98334/38/3c/40/44/48/4c). */
static void sk_collect_symbols(unsigned long *out)
{
    unsigned long src, n, i, rec, *list, count, grow, rc;
    unsigned long *dst;

    (void)rec;
    src = (*(unsigned long (**)(void))(0 + 0x1e0))();
    n = *(unsigned long *)(src + 0x10);
    list = 0;
    count = *(unsigned long *)(list + 0x10);
    for (i = 0; i < n; i++) {
        rec = *(unsigned long *)(src + i * 8 + 0x20);
        FUN_0036b270(rec);
        grow = *(unsigned long *)(list + 0x18) >> 1;
        if (grow - *(long *)(list + 0x10) < 1)
            list = (unsigned long *)FUN_000737a8(0, count + 1, 1, list);
        count = *(unsigned long *)(list + 0x10);
        *(unsigned long *)(list + 0x10) = count + 1;
        FUN_00117cc4((void *)(list + count * 0xf8 + 0x20), (void *)(rec + 0x20), 0xf8);
        FUN_0036b118(rec);
    }
    FUN_0036b118(src);
    *out = (unsigned long)list;
    (void)dst; (void)rc; (void)count;
}

/* FUN_0009834c @ 0x0009834c   (est. sk_collect_dt_records)
 * Ghidra: void FUN_0009834c(undefined8 *)
 * Collects up to N 0x50-byte DT records from the launcher's +0x1e0 list,
 * keeping records whose flag byte has bit0 set and bit6-7 clear, into a
 * growable list. Returns the collected records via *param_1; the last record
 * is zeroed if none matched.
 * Confidence: low
 * Notes: FUN_0009d014 record validation; SoftwareBreakpoint(1,0x98534) bounds. */
static void sk_collect_dt_records(unsigned long *out)
{
    unsigned long src, n, i, rec, *list, count, grow;
    unsigned char *flags;

    src = (*(unsigned long (**)(void))(0 + 0x1e0))();
    n = *(unsigned long *)(src + 0x10);
    list = 0;
    count = 0;
    for (i = 0; i < n; i++) {
        rec = *(unsigned long *)(src + i * 0x50 + 0x20);
        flags = (unsigned char *)(rec + 0x20);
        if ((flags[0x30 - 0x30] & 0xc0) == 0 && (flags[0x30 - 0x30] & 1) != 0) {
            /* copy 0x50-byte record; simplified faithful merge */
            count = *(unsigned long *)(list + 0x10);
            if (*(unsigned long *)(list + 0x18) >> 1 <= count)
                list = (unsigned long *)FUN_00082504(0, count + 1, 1);
            *(unsigned long *)(list + 0x10) = count + 1;
            FUN_00117cc4((void *)(list + count * 0x50 + 0x20), (void *)(rec + 0x20), 0x50);
        }
    }
    FUN_0036b118(src);
    *out = (unsigned long)list;
    (void)grow;
}

/* FUN_00098534 @ 0x00098534   (est. sk_launcher_read_record)
 * Ghidra: void FUN_00098534(undefined8 *)
 * Reads a launcher record via the +0x228 vtable method into an 8-word result:
 * if the record exists, copies its 16-byte descriptor words (with NEON-ext
 * double-word handling for the single-record case); else fills the result with
 * zeros and a 0xff flag byte.
 * Confidence: low
 * Notes: NEON_ext emulates 128-bit double-word extraction. */
static void sk_launcher_read_record(unsigned long *out)
{
    unsigned long buf[8], v0, v1, v2, v3, v4, v5, v6, v7;
    unsigned char flag;
    long rec, n;

    FUN_000027e8();
    (*(void (**)(void *))(0 + 0x228))(buf);
    rec = 0;
    n = *(long *)(rec + 0x10);
    if (n == 0) {
        FUN_0009e1e8();
        FUN_0000276c(buf);
        v0 = v1 = v2 = v3 = v4 = v5 = v6 = 0;
        flag = 0xff;
    } else {
        v0 = *(unsigned long *)(rec + 0x20);
        v1 = *(unsigned long *)(rec + 0x28);
        v2 = *(unsigned long *)(rec + 0x30);
        v3 = *(unsigned long *)(rec + 0x38);
        v4 = *(unsigned long *)(rec + 0x40);
        v5 = *(unsigned long *)(rec + 0x48);
        v6 = *(unsigned long *)(rec + 0x50);
        flag = *(unsigned char *)(rec + 0x58);
        FUN_0009e1e8();
        FUN_0000276c(buf);
    }
    out[0] = v0; out[1] = v1; out[2] = v2; out[3] = v3;
    out[4] = v4; out[5] = v5; out[6] = v6;
    *(unsigned char *)(out + 7) = flag;
}

/* FUN_00098624 @ 0x00098624   (est. sk_launcher_op_construct)
 * Ghidra: undefined8 FUN_00098624(undefined8, ..., undefined1)
 * Allocates an object and forwards the ten arguments to the +0x... op
 * initializer (FUN_000986d4). Thin allocation wrapper.
 * Confidence: low
 * Notes: FUN_0036a940 alloc; FUN_000986d4 op init (out of slice). */
static unsigned long sk_launcher_op_construct(unsigned long a, unsigned long b,
                                              unsigned long c, unsigned long d,
                                              unsigned long e, unsigned long f,
                                              unsigned long g, unsigned long h,
                                              unsigned long j, unsigned char k)
{
    unsigned long obj;

    obj = FUN_0036a940(0, 0, 0);
    FUN_000986d4(a, b, c, d, e, f, g, h, j, k);
    return obj;
}










