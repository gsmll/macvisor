/* Recreated from exclavecore_bundle.t8142.RELEASE.im4p (cL4 Secure Kernel,
 * arm64e, image base 0) — the cL4 (Apple seL4-derived) microkernel (GL1),
 * "cL4 (679.100.61)". Ground truth: Ghidra FUN_ names + addresses in program
 * cl4_kernel.raw.
 *
 * Slice 03: 0x80000-0x100000 caps region. This slice (0x8d350-0x8ebc0)
 * contains the kernel's generic data-structure layer (growable arrays of
 * cap records, sorted key/value maps, slot bitmaps) plus a dense band of
 * small register-glue / arithmetic helper primitives that the caps code
 * shares with the syscall/parse layer.
 *
 * SeL4/cL4 vocabulary is used for naming (CNode, cap, slot, TCB, endpoint,
 * notification, vspace, sched). Confidence is medium unless a string matches.
 * The many one- or two-instruction "glue" helpers communicate results through
 * caller-reserved registers or the condition flags rather than x0, so the
 * decompiler collapses them to `return;`. Those bodies are reconstructed
 * faithfully from disassembly and marked Confidence: low with the register
 * contract in Notes (fallback: disassemble_function).
 */

#include "sk_internal.h"

#include <stdint.h>
#include <stddef.h>
#include <string.h>

/* ------------------------------------------------------------------ *
 * Out-of-slice cL4 helper declarations (extern with a one-line note).
 * ------------------------------------------------------------------ */

/* FUN_0036a940 — cL4 allocation of a typed object of `size` bytes with kind
 * tag `kind`; returns zeroed memory. */
extern void *cL4_obj_alloc_typed(unsigned long size, unsigned long tag, int kind);
/* FUN_0036b118 — release/free a dynamic-array / object header (LO release). */
extern void cL4_arr_header_release(void *hdr);
/* FUN_0036b270 — release a reference on an object (LO refcount decrement). */
extern void cL4_ref_dec(unsigned long obj);
/* FUN_00002534 — resolve a class/type descriptor (magic at addr, index
 * table); returns the type record used for allocation / dispatch. */
extern unsigned long cL4_type_desc(unsigned long magic, unsigned long table);
/* thunk_FUN_000126e8 — set up / validate a fresh object allocation (returns
 * the object's usable base pointer). */
extern void *cL4_obj_init(void *obj);
/* FUN_00117d14 — byte copy (memcpy) of `n` bytes from src to dst. */
extern void cL4_memcpy(void *dst, const void *src, unsigned long n);
/* FUN_00089684 — fetch the current dynamic-array descriptor / container
 * header; returns a 16-byte {base, length} pair. */
extern cl4_result_t cL4_vec_current(void);
/* FUN_0036a1a0 — cL4 formatted log/assert printer (fmt + args, kind, flags). */
extern void cL4_log_print(unsigned long fmt, unsigned long args, int kind, int flags);
/* FUN_0035dc24 — retain an object given its destructor/type fn (x0,obj,x1,fn)
 * returns the retained object. */
extern unsigned long cL4_obj_retain(unsigned long obj, unsigned long type_fn);
/* FUN_0035d334 — release an object given its destructor/type fn. */
extern unsigned long cL4_obj_release_type(unsigned long obj, unsigned long type_fn);
/* FUN_0007bf80 — fetch the current object/vtable pointer (returns object in
 * a caller-reserved register x16); the method at vtable+off is then invoked. */
extern unsigned long cL4_vtable_of(void);
/* FUN_000b0888 — invoke a method with (kind, arg, extra) via the object
 * dispatch mechanism. */
extern void cL4_dispatch(unsigned long kind, unsigned long arg, unsigned long extra);
/* FUN_0036b340 — helper consulted at 0x8e3ec (opaque to this slice). */
extern void cL4_helper_b340(void);
/* FUN_000725c8 / FUN_00258c60 / FUN_002a0cf8 / FUN_0006a4c0 — opaque
 * out-of-slice utilities invoked by glue helpers below. */
extern void cL4_helper_725c8(void);
extern void cL4_helper_258c60(void);
extern void cL4_helper_2a0cf8(void);
extern void cL4_helper_6a4c0(void);
/* FUN_000827c4 / FUN_000827ec — begin/end an access window over a range
 * (fault handling for direct memory access). */
extern void cL4_access_begin(unsigned long size);
extern void cL4_access_end(unsigned long size);
/* FUN_000900ac / FUN_000900f8 / FUN_000900d0 / FUN_000900bc / FUN_00090054 —
 * per-cpu / exception-state helpers used by the error paths. */
extern cl4_result_t cL4_state_get(void);
extern void cL4_state_put(void);
extern cl4_result_t cL4_state_peek(void);
extern void cL4_state_push(void);
extern void cL4_state_halt(unsigned long code);
/* FUN_0005c278 — zero `size` bytes at `addr` (bzero). */
extern unsigned long cL4_bzero(unsigned long addr, unsigned long size);
/* FUN_00103a84 — decommit / release a zeroed range back to the allocator. */
extern void cL4_bzero_release(unsigned long size, unsigned long addr);
/* FUN_003a261c — read the per-cpu volatile state word (returns 16 bytes). */
extern cl4_result_t cL4_cpu_state(void);
/* FUN_0008f6c0 / FUN_0008f6f4 / FUN_0008f728 / FUN_0008f758 / FUN_0008f630 —
 * entry/exit and setup helpers of the launch path (0x8f6xx region, out of
 * this slice). */
extern void cL4_launch_enter(unsigned long arg);
extern unsigned long cL4_launch_state(void);
extern unsigned long cL4_launch_build(void);
extern unsigned long cL4_launch_body(unsigned long state);
/* FUN_00377824 / FUN_00377bec — construct a task/thread descriptor. */
extern long cL4_task_create(unsigned long a, unsigned long b, unsigned long c,
                            unsigned long d, unsigned long e);
extern unsigned long cL4_task_link(unsigned long a, unsigned long b, unsigned long c,
                                   unsigned long d, void *e);
/* thunk_FUN_00103cb0 — allocate a fresh kernel object (returns its address). */
extern void *cL4_kobj_alloc(unsigned long kind);
/* FUN_0007d054 — bind / associate the current thread with an object. */
extern void cL4_thread_bind(unsigned long kind, unsigned long obj);
/* FUN_0007c1c4 — finalize / commit a thread's context switch. */
extern void cL4_thread_commit(unsigned long a, unsigned long b, unsigned long c);
/* FUN_0008e5d8 @ 0x8e5d8 — (in slice, below) resolve an object's entry point. */
/* FUN_0008e070 — (in slice) cL4_scan_finish; the cap-scan publish step. */
extern void cL4_scan_publish(word_t result);   /* commit scan count to caller x30 */
extern void cL4_fatal_error(unsigned long a, unsigned long b, int c, int d,
                            int e, int f, cl4_result_t st, unsigned long len);
extern long cL4_entry_resolve(unsigned long p);   /* FUN_0008e5d8 (in slice) */
extern void cL4_kobj_initialize(void *obj);      /* FUN_0008e640 (in slice) */

/* In-slice helpers used across the file (decompiled below their first use):
 *   0x8e518 cL4_save_regs / 0x8e500 cL4_restore_regs — prologue/epilogue.
 *   0x8e2a0 cL4_ctz_inc — ctz(x25), x26++ (find lowest set bit).
 *   0x8df78 / 0x8e3c0 cL4_bitfield_mask — load & mask a packed bit field.
 */
extern void cL4_save_regs(void);
extern void cL4_restore_regs(void);
extern word_t cL4_ctz_inc(void);
extern word_t cL4_bitfield_mask(void);
extern void cL4_slot_row_setup(void);   /* FUN_0008e22c (in slice, defined below) */

/* The kernel's "empty" / default handler table base (_DAT_00657778). */
extern unsigned long cL4_default_handler;

/* Global fault/exception state for SoftwareBreakpoint(1,code) sites. */
#define CL4_FAULT(code) __builtin_trap()

/* ------------------------------------------------------------------ *
 * Array / map primitives (the cap-table data-structure layer).
 * ------------------------------------------------------------------ */

/* FUN_0008d350 @ 0x0008d350   (est. cL4_caps_scan_and_collect)
 * Ghidra: void FUN_0008d350(undefined8 param_1, undefined8 param_2, long param_3)
 * Scans the capability table row-by-row: each row (x23) is a 64-bit slot
 * bitmap (x25) whose set bits address 6-word (0x30-byte) cap records in the
 * table at *container+0x38. Every set slot's record is copied verbatim into
 * a caller-supplied record vector (x22). The scan stops once `param_3`
 * records have been collected (or the bitmap is exhausted if param_3 <= 0)
 * and the final row count is published to the caller's result word (x30).
 * Side effects: consumes the row bitmap via cL4_ctz_inc (lowest-set-bit),
 * advances a cursor (x27) through the rows, and finally commits the count.
 * Confidence: medium
 * Notes: row bitmap / cursor / limit live in caller-reserved registers
 *   (x20..x30) and the per-record bit index (x8) is register-forwarded;
 *   bounds and overflow faults trap via SoftwareBreakpoint
 *   (0x8d438 / 0x8d43c). */
void cL4_caps_scan_and_collect(word_t kind, word_t opts, long limit)
{
    unsigned long obj = 0;       /* unaff_x20 (caller object base) */
    unsigned long *dest = 0;     /* unaff_x22 (caller record vector) */
    unsigned long row_table = 0; /* unaff_x23 (row-bitmap table base) */
    word_t bitmap = 0;           /* unaff_x25 (current row bitmap) */
    unsigned long collected = 0; /* unaff_x26 (count collected) */
    word_t row = 0;              /* unaff_x27 (row cursor) */
    unsigned long row_count = 0; /* unaff_x28 (row bound) */
    word_t flag, col, bitidx;
    unsigned long *src;

    cL4_save_regs();
    flag = cL4_bitfield_mask();          /* FUN_0008df78 -> extraout_x1 */
    if (flag == 0) {
        row = 0;
    } else {
        if (limit < 0) {
            CL4_FAULT(0x8d43c);          /* negative limit is a fault */
        }
        if (limit == 0) {
            row = 0;
        } else {
            cL4_slot_row_setup();        /* primes x22-x28 (incl. bitmap) */
            while (1) {
                while (bitmap == 0) {
                    col = row + 1;
                    if (col < row) {
                        CL4_FAULT(0x8d438);   /* row cursor overflow */
                    }
                    if (row_count <= col) {
                        goto scan_done;
                    }
                    row = col;
                    bitmap = *(unsigned long *)(row_table + col * 8);
                }
                cL4_ctz_inc();           /* x26++; ctz(x25) -> x8 */
                bitidx = 0;              /* extraout_x8 (register-forwarded) */
                bitmap = bitmap - 1 & bitmap;
                /* copy the 6-word (0x30-byte) cap record at
                 * *(obj+0x38) + (bitidx | row<<6)*0x30 into the dest vector */
                src = (unsigned long *)(*(unsigned long *)(obj + 0x38) +
                                        (bitidx | row << 6) * 0x30);
                dest[1] = src[1];
                dest[0] = src[0];
                dest[2] = src[2];
                dest[3] = src[3];
                dest[4] = src[4];
                *((unsigned char *)dest + 0x28) = *((unsigned char *)src + 0x28);
                if (collected == (unsigned long)limit) {
                    break;
                }
                dest += 6;
                cL4_ref_dec(0);          /* FUN_0036b270() */
            }
            cL4_ref_dec(0);              /* FUN_0036b270() */
        }
    }

scan_done:
    cL4_scan_publish(row);   /* commit final row count to caller state (x30) */
    cL4_restore_regs();
}

/* FUN_0008d43c @ 0x0008d43c   (est. cL4_array_grow_reserve)
 * Ghidra: undefined * FUN_0008d43c(void)
 * Ensures the dynamic array described by the current container has capacity
 * for `cL4_vec_current().len` 4-word elements, growing (allocating a fresh
 * array via cL4_obj_alloc_typed, copying the live prefix, freeing the old
 * one) when the resident capacity is exhausted. Returns the array header.
 * The growth preserves elements while updating the header's used-count field
 * (bits [1..] at +0x18) and resets the dangling extra-data pointer (+0x10).
 * Confidence: high (verified against fresh decompile; placeholder gaps filled)
 * Notes: element stride 0x20; allocates uVar15*0x20+0x20 bytes of kind 7;
 *   faults at SoftwareBreakpoint 0x8d5ec/0x8d5f0/0x8d5f8/0x8d5f4. */
void *cL4_array_grow_reserve(void)
{
    cl4_result_t cur = cL4_vec_current();        /* FUN_00089684 */
    unsigned long count = cur.hi;
    long src = cur.lo;
    long idx = 0;
    unsigned long used = *(unsigned long *)(src + 0x10);
    unsigned char *arr = (unsigned char *)&cL4_default_handler;   /* DAT_00657778 */
    unsigned long *dst = (unsigned long *)(src + count * 0x20 + 0x38);
    unsigned long *out = (unsigned long *)&cL4_default_handler;   /* DAT_00657798 */
    unsigned long elem_count = count;

    while (1) {
        if (used == elem_count) {
            /* exhausted the source: trim the destination header and return */
            cL4_arr_header_release(arr);         /* FUN_0036b118 */
            if (1 < *(unsigned long *)(&cL4_default_handler + 0x18)) {
                unsigned long n = *(unsigned long *)(&cL4_default_handler + 0x18) >> 1;
                if (n < idx) {
                    CL4_FAULT(0x8d5fc);
                }
                *(unsigned long *)((char *)&cL4_default_handler + 0x10) = n - idx;
            }
            return arr;
        }
        if ((long)count < 0) {
            CL4_FAULT(0x8d5ec);
        }
        if (used <= elem_count) {
            CL4_FAULT(0x8d5f0);
        }
        /* read the 4-word source record */
        unsigned long w0 = dst[-3];
        unsigned long w1 = dst[-2];
        unsigned long w2 = dst[-1];
        unsigned long w3 = *dst;

        if (idx == 0) {
            /* first element: allocate the backing array if not yet present */
            unsigned long cap = *(unsigned long *)(&cL4_default_handler + 0x18);
            if ((long)((cap >> 1) + 0x4000000000000000) < 0) {
                CL4_FAULT(0x8d5f8);
            }
            unsigned long want = cap & 0xfffffffffffffffe;
            if ((long)cap < 2) {
                want = 1;
            }
            unsigned long td = cL4_type_desc(0x64f5a8, 0x4c0ff0);   /* FUN_00002534 */
            unsigned char *fresh = cL4_obj_alloc_typed(td, want * 0x20 + 0x20, 7);
            cL4_ref_dec(w0);                        /* thunk_FUN_0036b270 */
            arr = cL4_obj_init(fresh);              /* thunk_FUN_000126e8 */
            unsigned long n = ((unsigned long)arr - 0x20) / 0x20;
            *(unsigned long *)(arr + 0x10) = want;
            *(unsigned long *)(arr + 0x18) = n << 1;
            /* copy the live prefix from the old header */
            unsigned long keep = *(unsigned long *)(&cL4_default_handler + 0x18) >> 1;
            unsigned char *prev_out = arr + 0x20 + keep * 0x20;   /* DAT_00657798 update */
            idx = (n & 0x7fffffffffffffff) - keep;
            if (*(long *)((char *)&cL4_default_handler + 0x10) != 0) {
                if (arr != (unsigned char *)&cL4_default_handler ||
                    (unsigned char *)&cL4_default_handler + 0x20 + keep * 0x20 <= arr + 0x20) {
                    cL4_memcpy(arr + 0x20, (unsigned char *)&cL4_default_handler + 0x20,
                               keep << 5);          /* FUN_00117d14 */
                }
                *(unsigned long *)((char *)&cL4_default_handler + 0x10) = 0;
            }
            cL4_arr_header_release((unsigned char *)&cL4_default_handler);   /* FUN_0036b118 */
            out = (unsigned long *)prev_out;
            arr = fresh;
        } else {
            cL4_ref_dec(w0);                        /* thunk_FUN_0036b270 */
        }
        /* append the 4-word record */
        if (idx < 1) {
            CL4_FAULT(0x8d5f4);
        }
        idx = idx - 1;
        *out = w0;
        out[1] = w1;
        out[2] = w2;
        out[3] = w3;
        out += 4;
        dst += 4;
        elem_count = elem_count + 1;
    }
}

/* FUN_0008d64c @ 0x0008d64c   (est. cL4_map_merge_arrays)
 * Ghidra: undefined * FUN_0008d64c(long param_1,long param_2,code *param_3,
 *                                  undefined8 param_4,undefined8 param_5)
 * Merges two key/value arrays (param_1, param_2) into one, element-by-element
 * producing 2-word pairs; the destination is grown on demand. The two source
 * arrays may differ in length — the shorter prefix is interleaved, then the
 * tail of the longer one is copied straight through. Returns the merged array
 * header. param_3 is the allocation callback for the initial (and every
 * grown) backing store; param_4/param_5 describe the array type.
 * Confidence: medium
 * Notes: element stride 0x10, fields at +0x20/+0x28; faults at 0x8d888/
 *   0x8d88c/0x8d890/0x8d894/0x8d898/0x8d89c.  +0x10 used count, +0x18 = 2x
 *   capacity marker.  FUN_0008e3f8() after init in the grow path is dropped
 *   (arg lost by decompiler; see cL4_count_to_cap @0x8e3f8). */
void *cL4_map_merge_arrays(void *a, void *b, void *(*alloc)(unsigned long, int),
                           unsigned long type_magic, unsigned long type_table)
{
    unsigned long na = *(unsigned long *)((char *)a + 0x10);
    unsigned long nb = *(unsigned long *)((char *)b + 0x10);
    unsigned long n = (na < nb) ? na : nb;

    void *dst;
    if (n == 0) {
        dst = (void *)&cL4_default_handler;
    } else {
        dst = alloc(n, 0);
        cL4_ref_dec(0);   /* FUN_0036b270() — release ref on the new array */
    }
    unsigned long *out = (unsigned long *)dst + 4;
    unsigned long cap = *(unsigned long *)((char *)dst + 0x18) >> 1;
    cL4_arr_header_release(dst);

    if (n != 0) {
        unsigned long *pa = (unsigned long *)a + 4;
        unsigned long *pb = (unsigned long *)b + 4;
        unsigned long i = 0;
        do {
            if (na == 0) {
                CL4_FAULT(0x8d888);
            }
            unsigned long kv = *pb;
            cap -= 1;
            *out = *pa;
            out[1] = kv;
            cL4_ref_dec(0);    /* FUN_0036b270() — release key */
            cL4_ref_dec(kv);   /* FUN_0036b270(value) */
            out += 2;
            na -= 1;
            i += 1;
            pa += 1;
            pb += 1;
        } while (i != n);
    }
    /* copy the tail of the longer array straight through */
    for (; na != n; n += 1) {
        if (na <= n) {
            CL4_FAULT(0x8d88c);
        }
        if (nb == n) {
            break;
        }
        if (nb <= n) {
            CL4_FAULT(0x8d890);
        }
        unsigned long k = *(unsigned long *)((char *)a + 0x20 + n * 8);
        unsigned long v = *(unsigned long *)((char *)b + 0x20 + n * 8);
        if (cap == 0) {
            /* grow the destination array (capacity doubles) */
            unsigned long old = *(unsigned long *)((char *)dst + 0x18);
            if ((long)((old >> 1) + 0x4000000000000000) < 0) {
                CL4_FAULT(0x8d898);
            }
            unsigned long want = old & ~1ull;
            if ((long)old < 2) {
                want = 1;
            }
            unsigned long td = cL4_type_desc(type_magic, type_table);
            void *fresh = cL4_obj_alloc_typed(td, want * 0x10 + 0x20, 7);
            cL4_ref_dec(k);
            cL4_ref_dec(v);
            cL4_obj_init(fresh);
            *(unsigned long *)((char *)fresh + 0x10) = want;      /* new capacity */
            *(unsigned long *)((char *)fresh + 0x18) = 2 * want;  /* 2x marker */
            unsigned long oldn = *(unsigned long *)((char *)dst + 0x18) >> 1;
            out = (unsigned long *)((char *)fresh + 0x20 + oldn * 0x10);
            cap = want - oldn;
            if (*(long *)((char *)dst + 0x10) != 0) {
                if (fresh != dst ||
                    (char *)dst + 0x20 + oldn * 0x10 <= (char *)fresh + 0x20) {
                    cL4_memcpy((char *)fresh + 0x20, (char *)dst + 0x20, oldn << 4);
                }
                *(unsigned long *)((char *)dst + 0x10) = 0;
            }
            cL4_arr_header_release(dst);
            dst = fresh;
        } else {
            cL4_ref_dec(k);
            cL4_ref_dec(v);
        }
        if (cap == 0) {
            CL4_FAULT(0x8d894);
        }
        *out = k;
        out[1] = v;
        out += 2;
        cap -= 1;
    }
    if (1 < *(unsigned long *)((char *)dst + 0x18)) {
        unsigned long used = *(unsigned long *)((char *)dst + 0x18) >> 1;
        if (used < cap) {
            CL4_FAULT(0x8d89c);
        }
        *(unsigned long *)((char *)dst + 0x10) = used - cap;
    }
    return dst;
}

/* FUN_0008d5fc @ 0x0008d5fc   (est. cL4_map_merge_defaultA)
 * Ghidra: void FUN_0008d5fc(undefined8 param_1, undefined8 param_2)
 * Merge two cap arrays with the default comparator/allocator (type magic
 * 0x64e710, table 0x4c0560). Thin wrapper over cL4_map_merge_arrays.
 * Confidence: medium */
void *cL4_map_merge_defaultA(unsigned long a, unsigned long b)
{
    return cL4_map_merge_arrays((void *)a, (void *)b,
                                (void *(*)(unsigned long, int))0x71e4c,
                                0x64e710, 0x4c0560);
}

/* FUN_0008d624 @ 0x0008d624   (est. cL4_map_merge_defaultB)
 * Ghidra: void FUN_0008d624(undefined8 param_1, undefined8 param_2)
 * Merge two cap arrays with the alternate comparator/allocator (type magic
 * 0x64e728, table 0x4c0578). Thin wrapper over cL4_map_merge_arrays.
 * Confidence: medium */
void *cL4_map_merge_defaultB(unsigned long a, unsigned long b)
{
    return cL4_map_merge_arrays((void *)a, (void *)b,
                                (void *(*)(unsigned long, int))0x71e60,
                                0x64e728, 0x4c0578);
}

/* FUN_0008d89c @ 0x0008d89c   (est. cL4_map_flatten_list)
 * Ghidra: undefined * FUN_0008d89c(long param_1)
 * Flattens a list of key/value arrays into one: `param_1` points to a header
 * whose +0x10 is the element count and +0x20.. holds pointers to the member
 * arrays. Every member array's 2-word pairs (+0x20/+0x28 per element, stride
 * 0x10) are appended to a freshly built result array, growing on demand.
 * Returns the merged array header. Null member pointers are skipped.
 * Confidence: medium
 * Notes: element stride 0x10; type magic 0x64e6a8, table 0x4c25d0; faults at
 *   0x8da60/0x8da64/0x8da68/0x8da5c/0x8da6c. */
void *cL4_map_flatten_list(void *list)
{
    unsigned long used = 0;
    unsigned long cap = 0;
    void *out = (void *)&cL4_default_handler;
    void *cur = (void *)&cL4_default_handler;
    unsigned long i = 0;

    while (1) {
        /* copy the current member array's pairs into the result */
        for (; cur != 0 && (i != *(unsigned long *)((char *)cur + 0x10)); i += 1) {
            if (*(unsigned long *)((char *)cur + 0x10) <= i) {
                CL4_FAULT(0x8da60);
            }
            unsigned char *elem = (unsigned char *)cur + i * 0x10;
            unsigned long val = *(unsigned long *)(elem + 0x28);
            unsigned long key = *(unsigned long *)(elem + 0x20);
            if (cap == 0) {
                /* grow */
                unsigned long want = *(unsigned long *)((char *)out + 0x18) & ~1ull;
                if (*(unsigned long *)((char *)out + 0x18) < 2) {
                    want = 1;
                }
                unsigned long td = cL4_type_desc(0x64e6a8, 0x4c25d0);
                void *fresh = cL4_obj_alloc_typed(td, want * 0x10 + 0x20, 7);
                cL4_ref_dec(key);
                cL4_obj_init(fresh);
                cL4_arr_header_release(out);
                out = fresh;
                cap = want;
                /* copy live prefix into fresh */
            } else {
                cL4_ref_dec(key);
            }
            if (cap == 0) {
                CL4_FAULT(0x8da64);
            }
            *(unsigned long *)((char *)out + 0x20 + used * 8) = key;
            *(unsigned long *)((char *)out + 0x20 + used * 8 + 8) = val;
            used += 1;
            cap -= 1;
        }
        /* advance to the next member array */
        if (i == *(unsigned long *)((char *)list + 0x10)) {
            cL4_arr_header_release(cur);
            if (1 < *(unsigned long *)((char *)out + 0x18)) {
                unsigned long total = *(unsigned long *)((char *)out + 0x18) >> 1;
                if (total < cap) {
                    CL4_FAULT(0x8da68);
                }
                *(unsigned long *)((char *)out + 0x10) = total - cap;
            }
            return out;
        }
        if (*(unsigned long *)((char *)list + 0x10) <= i) {
            break;
        }
        cur = *(void **)((char *)list + 0x20 + i * 8);
        cL4_ref_dec((unsigned long)cur);
        cL4_arr_header_release(cur);
        i = 0;
        i += 1;
    }
    CL4_FAULT(0x8da5c);
    return 0;
}

/* FUN_0008da6c @ 0x0008da6c   (est. cL4_array_end_ptr)
 * Ghidra: long FUN_0008da6c(unsigned long param_1)
 * Returns the end address of a growable array: given the array pointer
 * (possibly tagged with bit 0, in which case the real pointer is read from
 * *p), the end is base + 0xc + the signed 32-bit length stored at +0xc.
 * Confidence: high (pattern is fully explicit). */
long cL4_array_end_ptr(unsigned long p)
{
    if (p & 1) {
        p = *(unsigned long *)(p & ~1ull);
    }
    return (long)(p + 0xc) + (long)*(int *)(p + 0xc);
}

/* FUN_0008da9c @ 0x0008da9c   (est. cL4_array_end_ptr14)
 * Ghidra: long FUN_0008da9c(unsigned long param_1)
 * Same as cL4_array_end_ptr but the base offset is +0x14.
 * Confidence: high */
long cL4_array_end_ptr14(unsigned long p)
{
    if (p & 1) {
        p = *(unsigned long *)(p & ~1ull);
    }
    return (long)(p + 0x14) + (long)*(int *)(p + 0x14);
}

/* FUN_0008dacc @ 0x0008dacc   (est. cL4_obj_release_masked)
 * Ghidra: void FUN_0008dacc(unsigned long param_1)
 * Releases an object reference: if the low 3 bits of param_1 (and the
 * tag-mask check) match the "plain" encoding the object is kept; otherwise
 * the reference is dropped via cL4_arr_header_release(p & 0x7fffffffffffffff).
 * Confidence: low (tag-bit test is opaque). */
void cL4_obj_release_masked(unsigned long p)
{
    if (((p ^ ~0ull) & 0xf000000000000007ull) == 0) {
        return;
    }
    cL4_arr_header_release((void *)(p & 0x7fffffffffffffff));
}

/* FUN_0008dae4 @ 0x0008dae4   (est. cL4_pair_conditional)
 * Ghidra: undefined1 [16] FUN_0008dae4(undefined8,undefined8,undefined8)
 * Builds a 16-byte {key,value} pair: value = FUN_0039c70c(b,c) (a lookup),
 * key = param_1 only when the lookup returned non-null, else zero.
 * Confidence: medium (lookup helper out of slice). */
cl4_result_t cL4_pair_conditional(unsigned long key, unsigned long a, unsigned long b)
{
    unsigned long v = 0;   /* FUN_0039c70c(a,b) — out of slice lookup */
    if (v != 0) {
        v = v;
    }
    cl4_result_t r;
    r.lo = (v != 0) ? key : 0;
    r.hi = v;
    return r;
}

/* FUN_0008db28 @ 0x0008db28   (est. cL4_array_end_ptr8)
 * Ghidra: long FUN_0008db28(unsigned long param_1)
 * Same as cL4_array_end_ptr but with base offset +0x8.
 * Confidence: high */
long cL4_array_end_ptr8(unsigned long p)
{
    if (p & 1) {
        p = *(unsigned long *)(p & ~1ull);
    }
    return (long)(p + 8) + (long)*(int *)(p + 8);
}

/* FUN_0008db58 @ 0x0008db58   (est. cL4_obj_retain_caps)
 * Ghidra: undefined8 FUN_0008db58(undefined8 param_1, undefined8 param_2)
 * Retain the cap-list object param_2 given its destructor function (at
 * 0x65fc78) and returns the retained object. Wrapper over cL4_obj_retain.
 * Confidence: low-medium */
unsigned long cL4_obj_retain_caps(unsigned long a, unsigned long obj)
{
    return cL4_obj_retain(obj, 0x65fc78);
}

/* FUN_0008db90 @ 0x0008db90   (est. cL4_obj_release_capsA)
 * Ghidra: undefined8 FUN_0008db90(undefined8 param_1)
 * Release the cap-list object param_1 with its destructor (0x65fc78).
 * Confidence: low-medium */
unsigned long cL4_obj_release_capsA(unsigned long obj)
{
    return cL4_obj_release_type(obj, 0x65fc78);
}

/* FUN_0008dbc0 @ 0x0008dbc0   (est. cL4_obj_release_capsB)
 * Ghidra: undefined8 FUN_0008dbc0(undefined8 param_1)
 * Release the cap-list object param_1 with its alternate destructor
 * (0x65fbf0).
 * Confidence: low-medium */
unsigned long cL4_obj_release_capsB(unsigned long obj)
{
    return cL4_obj_release_type(obj, 0x65fbf0);
}

/* FUN_0008dc1c @ 0x0008dc1c   (est. cL4_obj_method50)
 * Ghidra: void FUN_0008dc1c(void)
 * Dispatches the virtual method at vtable offset +0x50 of the current object
 * (fetched by cL4_vtable_of) and stores its result into the object slot at
 * *x19. Generic virtual call helper.
 * Confidence: low (register-based object/method dispatch). */
void cL4_obj_method50(void)
{
    unsigned long obj = cL4_vtable_of();
    unsigned long result = (*(unsigned long (**)(void))(obj + 0x50))();
    ((volatile unsigned long *)0)[0] = result;   /* *x19 = result */
}

/* FUN_0008dc58 @ 0x0008dc58   (est. cL4_obj_method68)
 * Ghidra: void FUN_0008dc58(void)
 * Dispatches the virtual method at vtable offset +0x68 of the current object
 * and stores the result into the object slot at *x19.
 * Confidence: low (register-based object/method dispatch). */
void cL4_obj_method68(void)
{
    unsigned long obj = cL4_vtable_of();
    unsigned long result = (*(unsigned long (**)(void))(obj + 0x68))();
    ((volatile unsigned long *)0)[0] = result;   /* *x19 = result */
}

/* FUN_0008dc94 @ 0x0008dc94   (est. cL4_obj_method80)
 * Ghidra: void FUN_0008dc94(void)
 * Dispatches the virtual method at vtable offset +0x80 of the current object
 * and stores the result into the object slot at *x19.
 * Confidence: low (register-based object/method dispatch). */
void cL4_obj_method80(void)
{
    unsigned long obj = cL4_vtable_of();
    unsigned long result = (*(unsigned long (**)(void))(obj + 0x80))();
    ((volatile unsigned long *)0)[0] = result;   /* *x19 = result */
}

/* FUN_0008dcd0 @ 0x0008dcd0   (est. cL4_const_pair_e3f0)
 * Ghidra: undefined1 [16] FUN_0008dcd0(void)
 * Returns the constant 16-byte pair {0x64f3e0, 0} (an address + zero).
 * Confidence: medium */
cl4_result_t cL4_const_pair_e3f0(void)
{
    cl4_result_t r = { 0x64f3e0, 0 };
    return r;
}

/* FUN_0008dce0 @ 0x0008dce0   (est. cL4_const_pair_e4a8)
 * Ghidra: undefined1 [16] FUN_0008dce0(void)
 * Returns the constant 16-byte pair {0x64f4a8, 0}.
 * Confidence: medium */
cl4_result_t cL4_const_pair_e4a8(void)
{
    cl4_result_t r = { 0x64f4a8, 0 };
    return r;
}

/* FUN_0008de50 @ 0x0008de50   (est. cL4_obj_destroy_typed)
 * Ghidra: undefined8 FUN_0008de50(undefined8 param_1)
 * Destroys an object of the type described by the descriptor resolved from
 * (0x64f0e0, 0x4c1000): resolves the type record, then invokes its destructor
 * (the code pointer at *(type-8)+8) with (object, type). Returns the object.
 * Confidence: low-medium */
unsigned long cL4_obj_destroy_typed(unsigned long obj)
{
    long type = cL4_type_desc(0x64f0e0, 0x4c1000);
    (*(void (**)(unsigned long, long))(*(long *)(type - 8) + 8))(obj, type);
    return obj;
}

/* FUN_0008deb0 @ 0x0008deb0   (est. cL4_obj_retain_capsB)
 * Ghidra: undefined8 FUN_0008deb0(undefined8 param_1, undefined8 param_2)
 * Retain the cap-list object param_2 given the alternate destructor
 * (0x65fbf0) and returns the retained object.
 * Confidence: low-medium */
unsigned long cL4_obj_retain_capsB(unsigned long a, unsigned long obj)
{
    return cL4_obj_retain(obj, 0x65fbf0);
}

/* FUN_0008def0 @ 0x0008def0   (est. thunk cL4_bitwise_and)
 * Ghidra: uint thunk_FUN_0008cc7c(uint param_1, uint param_2)
 * Thunk: returns param_2 & param_1 (32-bit bitwise AND).
 * Confidence: high */
unsigned int cL4_bitwise_and(unsigned int a, unsigned int b)
{
    return b & a;
}

/* FUN_0008defc @ 0x0008defc   (est. cL4_fatal_arg_setup)
 * Ghidra: void FUN_0008defc(void)
 * Register-glue stub: sets up arguments (x0=x21, x1=&"Fatal error" string at
 * 0x5c0550, w2=0x2d, w3=0x1) for a subsequent call and returns. The caller
 * tail-invokes a panic printer with these prepared registers.
 * Confidence: low (register-returning stub; fallback disassemble). */
void cL4_fatal_arg_setup(void)
{
    /* x0 = x21 (caller object); x1 = 0x5c0550; w2 = 0x2d; w3 = 0x1; ret */
}

/* FUN_0008df14 @ 0x0008df14   (est. cL4_fatal_error_str)
 * Ghidra: char * FUN_0008df14(void)
 * Returns the constant string pointer "Fatal error" (s_Fatal_error_005accd0).
 * Confidence: high (string address matched). */
const char *cL4_fatal_error_str(void)
{
    return (const char *)0x5accd0;   /* s_Fatal_error_005accd0 */
}

/* FUN_0008df28 @ 0x0008df28   (est. cL4_add_or_zero)
 * Ghidra: void FUN_0008df28(void)
 * Returns (in x8) x2 + x0, or 0 when x2 == 0. Register-returning glue.
 * Confidence: low (fallback disassemble). */
long cL4_add_or_zero(long x0, long x2)
{
    return (x2 == 0) ? 0 : (x2 + x0);
}

/* FUN_0008df38 @ 0x0008df38   (est. cL4_init_handler_table)
 * Ghidra: void FUN_0008df38(void)
 * Initializes the kernel's default handler table: FUN_001f0130(&DAT_00657778,
 * 0x677830, 0x677790, 0x671e68). Registers three handler addresses into the
 * default-handler table at _DAT_00657778.
 * Confidence: low (handler-table init; target out of slice). */
void cL4_init_handler_table(void)
{
    /* FUN_001f0130(&cL4_default_handler, 0x677830, 0x677790, 0x671e68) */
}

/* FUN_0008df68 @ 0x0008df68   (est. cL4_is_digit_adv)
 * Ghidra: void FUN_0008df68(void)
 * Digit test on the byte at *x8 (post-incrementing x8): subtracts '0' (0x30)
 * and compares to 9, leaving the condition flags for the caller. Sets NZCV
 * so the caller branches; value in w11. Register/flag glue.
 * Confidence: low (flag-returning; fallback disassemble). */
void cL4_is_digit_adv(void)
{
    /* w11 = *(byte*)x8++; w11 -= 0x30; cmp w11, #9; ret (flags) */
}

/* FUN_0008df78 @ 0x0008df78   (est. cL4_bitfield_mask)
 * Ghidra: void FUN_0008df78(void)
 * Reads a 64-bit packed word at [x3+0x40] and a field size byte at [x3+0x20],
 * builds a low-mask of that size, and returns the masked field in x25. Used
 * to extract variable-length bit fields from the cap table rows.
 * Confidence: low (register-returning; fallback disassemble). */
word_t cL4_bitfield_mask(void)
{
    /* x8 = *[x3+0x40]; w9 = byte[x3+0x20]; mask = ~0 << w9;
     * x25 = (wrap-guarded mask) & x8; ret */
    return 0;
}

/* FUN_0008dfac @ 0x0008dfac   (est. cL4_is_digit)
 * Ghidra: void FUN_0008dfac(void)
 * Digit test on the byte at *x8 (no increment): subtracts '0' and compares to
 * 9, leaving condition flags for the caller. Register/flag glue.
 * Confidence: low (fallback disassemble). */
void cL4_is_digit(void)
{
    /* w11 = *(byte*)x8; w10 = w11 - 0x30; cmp w10, #9; ret (flags) */
}

/* FUN_0008dfbc @ 0x0008dfbc   (est. cL4_arg_setup_b)
 * Ghidra: void FUN_0008dfbc(void)
 * Register-glue stub setting w1=0xb, w2=0x2, w6=0x2d, w7=0x2 for a subsequent
 * call. Register-returning.
 * Confidence: low (fallback disassemble). */
void cL4_arg_setup_b(void)
{
    /* w1 = 0xb; w2 = 0x2; w6 = 0x2d; w7 = 0x2; ret */
}

/* FUN_0008dfd0 @ 0x0008dfd0   (est. cL4_mul10_acc)
 * Ghidra: void FUN_0008dfd0(void)
 * Accumulator: x12 = x27*10; x27 += w11 (zero-extended byte). Part of a
 * decimal-parse loop ("accumulate digit into x27"). Register glue.
 * Confidence: low (fallback disassemble). */
void cL4_mul10_acc(void)
{
    /* x12 = x27*10; adds x27, x12, w11, UXTB; ret (flags) */
}

/* FUN_0008dfe0 @ 0x0008dfe0   (est. cL4_sel_bits4)
 * Ghidra: void FUN_0008dfe0(void)
 * Selects either the low 48 bits of x0 or the 4-bit field at bit 56 of x1,
 * depending on the tag bit (bit 61) of x1; result in x9. Tag-encoded pointer
 * disambiguation.
 * Confidence: low (fallback disassemble). */
void cL4_sel_bits4(void)
{
    /* x2 = x0 & 0xffffffffffff; x8 = ubfx(x1,#56,#4);
     * tst x1, #0x2000000000000000; x9 = eq ? x2 : x8; ret */
}

/* FUN_0008dff4 @ 0x0008dff4   (est. cL4_state_advance16)
 * Ghidra: undefined1 [16] FUN_0008dff4(void)
 * Advances a 16-byte state record: reads the record header at [x19+0x40],
 * extracts the base (at +0x18) and a word (at +0x20), drives the word through
 * the cL4 state machine (cL4_helper_6a4c0 + cL4_array_end_ptr), and returns
 * the resulting 16-byte {word, base} pair.
 * Confidence: low (register/state based; fallback notes). */
cl4_result_t cL4_state_advance16(void)
{
    long rec = *(long *)((char *)0 + 0x40);   /* [x19+0x40] */
    unsigned long w = *(unsigned long *)(rec + 0x20);
    cL4_helper_6a4c0();
    cL4_array_end_ptr(w);
    cl4_result_t r;
    r.hi = *(unsigned long *)(rec + 0x18);
    r.lo = w;
    return r;
}

/* FUN_0008e02c @ 0x0008e02c   (est. cL4_pac_setup)
 * Ghidra: void FUN_0008e02c(void)
 * PAC setup glue: signs the code pointer at (0x661000+0xea8) with key B
 * (pacda x16, x17; x17 = 0xb830) and moves the result into x1. Register glue.
 * Confidence: low (fallback disassemble). */
void cL4_pac_setup(void)
{
    /* x16 = 0x661ea8; x17 = 0xb830; pacda x16, x17; x1 = x16; ret */
}

/* FUN_0008e048 @ 0x0008e048   (est. cL4_dispatch_1)
 * Ghidra: void FUN_0008e048(undefined8 param_1)
 * Dispatch helper: cL4_dispatch(1, &param_1, param_1).
 * Confidence: low-medium */
void cL4_dispatch_1(unsigned long p)
{
    cL4_dispatch(1, (unsigned long)&p, p);
}

/* FUN_0008e058 @ 0x0008e058   (est. cL4_const_msg_kind)
 * Ghidra: undefined1 [16] FUN_0008e058(void)
 * Returns the constant 16-byte pair {0x6c616e6f6974706f, 0xe800000000000000}
 * — a little-endian "option" tag ("option" = 0x6c616e6f6974706f) with a high
 * tag word. Likely an option/parameter record sentinel.
 * Confidence: medium (ASCII decodes to "option"). */
cl4_result_t cL4_const_msg_kind(void)
{
    cl4_result_t r = { 0x6c616e6f6974706full, 0xe800000000000000ull };
    return r;
}

/* FUN_0008e070 @ 0x0008e070   (est. cL4_scan_finish)
 * Ghidra: void FUN_0008e070(void)
 * Finish helper: returns the count produced by the preceding scan (no body —
 * the result is carried in a caller register). The call site at 0x8d350 uses
 * this as the final row count before publishing.
 * Confidence: low (empty body; caller-carried result). */
word_t cL4_scan_finish(word_t row)
{
    return row;
}

/* FUN_0008e088 @ 0x0008e088   (est. cL4_arg_setup_f9)
 * Ghidra: void FUN_0008e088(void)
 * Register-glue stub: x0 = x16, x2 = 0x5c0610, w3 = 0xf9, w4 = 0x2, then
 * returns to a caller that invokes a routine with these prepared arguments
 * (x2 points at the "/AppleInternal/L..." path string).
 * Confidence: low (fallback disassemble). */
void cL4_arg_setup_f9(void)
{
    /* x0 = x16; x2 = 0x5c0610; w3 = 0xf9; w4 = 0x2; ret */
}

/* FUN_0008e0a0 @ 0x0008e0a0   (est. cL4_slot_set)
 * Ghidra: void FUN_0008e0a0(undefined8 param_1)
 * Sets one slot of the cap table: given the slot index (x25), table base
 * (x20), a bitmap word (x22) and key (x24), sets the slot's bit in the row
 * bitmap at (base + (x25>>6)*8 + 0x40), stores the key at *(base+0x30) +
 * x25*8 and the value param_1 at *(base+0x38) + x25*8. Core cap-slot insert.
 * Confidence: medium (bitmap/slot layout explicit). */
void cL4_slot_set(word_t value)
{
    /* x20 = table base; x22 = slot bitmap word; x24 = key; x25 = slot index */
    unsigned long base = 0;              /* x20 (caller-reserved) */
    unsigned long key = 0;               /* x24 */
    unsigned long slot = 0;              /* x25 */
    unsigned long bitw = 0;              /* x22 */
    unsigned long *row = (unsigned long *)(base + (slot >> 6) * 8);
    row[0x40 / 8] |= bitw << (slot & 0x3f);
    *(unsigned long *)(*(long *)(base + 0x30) + slot * 8) = key;
    *(unsigned long *)(*(long *)(base + 0x38) + slot * 8) = value;
}

/* FUN_0008e0d4 @ 0x0008e0d4   (est. cL4_type_dispatch_c040)
 * Ghidra: void FUN_0008e0d4(void)
 * Resolves the type descriptor (0x64c040, 0x4bbf40) — a tail call into the
 * type-resolution routine. Register/type setup glue.
 * Confidence: low (tail call; target out of slice). */
void cL4_type_dispatch_c040(void)
{
    cL4_type_desc(0x64c040, 0x4bbf40);
}

/* FUN_0008e0e8 @ 0x0008e0e8   (est. cL4_is_lower_hex)
 * Ghidra: void FUN_0008e0e8(void)
 * Hex-digit test for lowercase a-f: w10 = w11 - 0x61, compare to 5. Leaves
 * condition flags for the caller. Register/flag glue.
 * Confidence: low (fallback disassemble). */
void cL4_is_lower_hex(void)
{
    /* w10 = w11 - 0x61; cmp w10, #5; ret (flags) */
}

/* FUN_0008e0f4 @ 0x0008e0f4   (est. cL4_is_upper_hex)
 * Ghidra: void FUN_0008e0f4(void)
 * Hex-digit test for uppercase A-F: w10 = w11 - 0x41, compare to 5. Leaves
 * condition flags for the caller. Register/flag glue.
 * Confidence: low (fallback disassemble). */
void cL4_is_upper_hex(void)
{
    /* w10 = w11 - 0x41; cmp w10, #5; ret (flags) */
}

/* FUN_0008e100 @ 0x0008e100   (est. cL4_mul10)
 * Ghidra: void FUN_0008e100(void)
 * Computes x12 = x27*10 (via x27 + x27<<2 then <<1). Register glue used by
 * the decimal-parse accumulation loop.
 * Confidence: low (fallback disassemble). */
void cL4_mul10(void)
{
    /* x12 = x27*10; ret */
}

/* FUN_0008e10c @ 0x0008e10c   (est. cL4_mul_ovf_check)
 * Ghidra: void FUN_0008e10c(void)
 * Multiply-overflow check: x12 = umulh(x27, x10); negs xzr, x12 sets the
 * carry flag if the high product is non-zero (i.e. the 64-bit multiply
 * overflowed). Register/flag glue.
 * Confidence: low (fallback disassemble). */
void cL4_mul_ovf_check(void)
{
    /* x12 = umulh(x27, x10); negs xzr, x12; ret (carry = overflow) */
}

/* FUN_0008e118 @ 0x0008e118   (est. cL4_reg_shuffle_args)
 * Ghidra: void FUN_0008e118(void)
 * Register-shuffle glue: moves the six argument registers from the caller's
 * preserved registers (x26..x28, x20, x22, x27, x23, x25) into x0-x6 and
 * stores the previous x0 into x20. Prepares a 7-argument call.
 * Confidence: low (fallback disassemble). */
void cL4_reg_shuffle_args(void)
{
    /* x7 = x0; x0=x26; x1=x23; x2=x25; x3=x20; x4=x22; x5=x27; x6=x28;
     * x20 = x7; ret */
}

/* FUN_0008e140 @ 0x0008e140   (est. cL4_flag_config_e140)
 * Ghidra: void FUN_0008e140(void)
 * Loads the config byte at 0x6add10, compares it to 1, and returns with the
 * condition flags set (no value written to x0). Caller branches on the flag.
 * Confidence: low (flag-returning; fallback disassemble). */
void cL4_flag_config_e140(void)
{
    /* w8 = *(byte*)0x6add10; cmp w8, #1; ret (flags) */
}

/* FUN_0008e154 @ 0x0008e154   (est. cL4_arg_setup_f9b)
 * Ghidra: void FUN_0008e154(void)
 * Register-glue stub: sets w3 = 0xf9, w4 = 0x2 for a subsequent call.
 * Confidence: low (fallback disassemble). */
void cL4_arg_setup_f9b(void)
{
    /* w3 = 0xf9; w4 = 0x2; ret */
}

/* FUN_0008e160 @ 0x0008e160   (est. cL4_stack_alloc20)
 * Ghidra: void FUN_0008e160(void)
 * Allocates 0x20 bytes of stack: x8 = sp; x1 = sp-0x20; sp = x1. Sets up a
 * scratch frame for the caller. Register glue.
 * Confidence: low (fallback disassemble). */
void cL4_stack_alloc20(void)
{
    /* sp -= 0x20; x1 = new sp; ret */
}

/* FUN_0008e170 @ 0x0008e170   (est. cL4_sp_tag10)
 * Ghidra: void FUN_0008e170(void)
 * Sets x9 = sp | 1 (a tagged stack pointer) and w10 = 0xa. Register glue.
 * Confidence: low (fallback disassemble). */
void cL4_sp_tag10(void)
{
    /* x9 = sp | 1; w10 = 0xa; ret */
}

/* FUN_0008e180 @ 0x0008e180   (est. cL4_is_digit_adv2)
 * Ghidra: void FUN_0008e180(void)
 * Digit test on the byte at *x8 (post-incrementing x8): subtracts '0' and
 * compares to 9, leaving flags. Register/flag glue.
 * Confidence: low (fallback disassemble). */
void cL4_is_digit_adv2(void)
{
    /* w10 = *(byte*)x8++; w10 -= 0x30; cmp w10, #9; ret (flags) */
}

/* FUN_0008e190 @ 0x0008e190   (est. cL4_arg_setup_shift)
 * Ghidra: void FUN_0008e190(void)
 * Register-glue: saves x0->x6, x1->x7, and sets w9 = 0x20 for a call.
 * Confidence: low (fallback disassemble). */
void cL4_arg_setup_shift(void)
{
    /* x6 = x0; x7 = x1; w9 = 0x20; ret */
}

/* FUN_0008e1a0 @ 0x0008e1a0   (est. cL4_obj_load_x16)
 * Ghidra: void FUN_0008e1a0(void)
 * Loads the object at [x19] into x16 and stores x19 into x17, preparing a
 * virtual dispatch. Also saves x0 -> x22. Register glue.
 * Confidence: low (fallback disassemble). */
void cL4_obj_load_x16(void)
{
    /* x22 = x0; x16 = *[x19]; x17 = x19; ret */
}

/* FUN_0008e1b0 @ 0x0008e1b0   (est. cL4_store_records5)
 * Ghidra: undefined8 FUN_0008e1b0(undefined8 param_1, undefined8 *param_2,
 *   undefined8 param_3, undefined8 param_4, undefined8 param_5)
 * Writes a 5-word record into the output buffer param_2: {param_5, param_1,
 * ~x9, x11, x10}, where x9/x10/x11 are caller-reserved registers. Returns
 * param_4.
 * Confidence: low (register-sourced fields). */
unsigned long cL4_store_records5(unsigned long p1, unsigned long *out,
                                 unsigned long p3, unsigned long p4, unsigned long p5)
{
    out[0] = p5;
    out[1] = p1;
    out[2] = ~0ull;    /* ~in_x9 */
    out[3] = 0;        /* in_x11 */
    out[4] = 0;        /* in_x10 */
    return p4;
}

/* FUN_0008e1c8 @ 0x0008e1c8   (est. cL4_ptr_inc_cnt)
 * Ghidra: void FUN_0008e1c8(void)
 * Increments x8 and decrements x9 (with flag update). Register glue used in
 * a copy/decode loop.
 * Confidence: low (fallback disassemble). */
void cL4_ptr_inc_cnt(void)
{
    /* x8 += 1; subs x9, x9, #1; ret (flags) */
}

/* FUN_0008e1d4 @ 0x0008e1d4   (est. cL4_mov_x16_save)
 * Ghidra: void FUN_0008e1d4(void)
 * Register glue: x1 = x16, x20 = x19. Prepares a call.
 * Confidence: low (fallback disassemble). */
void cL4_mov_x16_save(void)
{
    /* x1 = x16; x20 = x19; ret */
}

/* FUN_0008e1e0 @ 0x0008e1e0   (est. cL4_arg_setup_610)
 * Ghidra: void FUN_0008e1e0(void)
 * Register glue: sets x2 = 0x5c0610 (the "/AppleInternal/L..." path).
 * Confidence: low (fallback disassemble). */
void cL4_arg_setup_610(void)
{
    /* x2 = 0x5c0610; ret */
}

/* FUN_0008e1ec @ 0x0008e1ec   (est. cL4_mov_x0_x2)
 * Ghidra: void FUN_0008e1ec(void)
 * Register glue: x8 = x0, x2 = x1.
 * Confidence: low (fallback disassemble). */
void cL4_mov_x0_x2(void)
{
    /* x8 = x0; x2 = x1; ret */
}

/* FUN_0008e1f8 @ 0x0008e1f8   (est. cL4_arg_setup_x20_a)
 * Ghidra: void FUN_0008e1f8(void)
 * Register glue: x1 = x20, w2 = 0xa.
 * Confidence: low (fallback disassemble). */
void cL4_arg_setup_x20_a(void)
{
    /* x1 = x20; w2 = 0xa; ret */
}

/* FUN_0008e204 @ 0x0008e204   (est. cL4_inc_x9_a)
 * Ghidra: void FUN_0008e204(void)
 * Register glue: x9 = x0 + 1, w10 = 0xa.
 * Confidence: low (fallback disassemble). */
void cL4_inc_x9_a(void)
{
    /* x9 = x0 + 1; w10 = 0xa; ret */
}

/* FUN_0008e210 @ 0x0008e210   (est. cL4_save_args4)
 * Ghidra: void FUN_0008e210(void)
 * Register glue: saves x0->x20, x1->x22, x2->x27, x3->x28, compares x24 to 0,
 * loads [sp+8] into x8.
 * Confidence: low (fallback disassemble). */
void cL4_save_args4(void)
{
    /* x20=x0; x22=x1; x27=x2; x28=x3; cmp x24,#0; x8=[sp+8]; ret */
}

/* FUN_0008e22c @ 0x0008e22c   (est. cL4_slot_row_setup)
 * Ghidra: void FUN_0008e22c(void)
 * Slot-row iterator setup: x22 = x1, x26 = 0, x27 = 0, x28 = (0x3f - x24)>>6.
 * Primes the row/bit counters for a bitmap walk. Register glue.
 * Confidence: low (fallback disassemble). */
void cL4_slot_row_setup(void)
{
    /* x22 = x1; x26 = 0; x27 = 0; w8 = 0x3f; x8 = 0x3f - x24; x28 = x8>>6; ret */
}

/* FUN_0008e248 @ 0x0008e248   (est. cL4_dispatch_1b)
 * Ghidra: void FUN_0008e248(undefined8 param_1)
 * Dispatch helper: cL4_dispatch(1, param_1).
 * Confidence: low-medium */
void cL4_dispatch_1b(unsigned long p)
{
    cL4_dispatch(1, p, 0);
}

/* FUN_0008e254 @ 0x0008e254   (est. cL4_is_plus)
 * Ghidra: void FUN_0008e254(void)
 * Tests whether the byte at *x8 is '+' (0x2b), leaving condition flags.
 * Register/flag glue.
 * Confidence: low (fallback disassemble). */
void cL4_is_plus(void)
{
    /* w9 = *(byte*)x8; cmp w9, #0x2b; ret (flags) */
}

/* FUN_0008e260 @ 0x0008e260   (est. cL4_state_frame_setup)
 * Ghidra: void FUN_0008e260(void)
 * Sets up a stack frame: x8 = 0xe000000000000000, stp xzr,x8,[sp+0x50],
 * x20 = sp+0x50. Register glue.
 * Confidence: low (fallback disassemble). */
void cL4_state_frame_setup(void)
{
    /* x8 = 0xe000000000000000; stp xzr, x8, [sp,#0x50]; x20 = sp+0x50; ret */
}

/* FUN_0008e270 @ 0x0008e270   (est. cL4_mul10_acc_x22)
 * Ghidra: void FUN_0008e270(void)
 * Accumulator: x12 = x22*10; adds x22, x12, w11, UXTB. Decimal-parse glue.
 * Confidence: low (fallback disassemble). */
void cL4_mul10_acc_x22(void)
{
    /* x12 = x22*10; adds x22, x12, w11, UXTB; ret (flags) */
}

/* FUN_0008e280 @ 0x0008e280   (est. cL4_stack_alloc20b)
 * Ghidra: void FUN_0008e280(void)
 * Allocates 0x20 bytes of stack; x22 = new sp. Register glue.
 * Confidence: low (fallback disassemble). */
void cL4_stack_alloc20b(void)
{
    /* sp -= 0x20; x22 = sp; ret */
}

/* FUN_0008e290 @ 0x0008e290   (est. cL4_inc1)
 * Ghidra: long FUN_0008e290(long param_1)
 * Returns param_1 + 1.
 * Confidence: high */
long cL4_inc1(long x)
{
    return x + 1;
}

/* FUN_0008e2a0 @ 0x0008e2a0   (est. cL4_ctz_inc)
 * Ghidra: void FUN_0008e2a0(void)
 * Increments x26 and computes the count of trailing zeroes of x25
 * (rbit+clz = ctz), returning it in x8. Used as the "lowest set bit" step of
 * the cap-row scan.
 * Confidence: medium (explicit ctz; register glue). */
word_t cL4_ctz_inc(void)
{
    /* x26 += 1; x8 = clz(rbit(x25)); ret */
    return 0;
}

/* FUN_0008e2b0 @ 0x0008e2b0   (est. cL4_mul10_acc_x21)
 * Ghidra: void FUN_0008e2b0(void)
 * Accumulator: x12 = x21*10; adds x21, x12, w11, UXTB. Decimal-parse glue.
 * Confidence: low (fallback disassemble). */
void cL4_mul10_acc_x21(void)
{
    /* x12 = x21*10; adds x21, x12, w11, UXTB; ret (flags) */
}

/* FUN_0008e2c0 @ 0x0008e2c0   (est. cL4_mov_args20)
 * Ghidra: void FUN_0008e2c0(void)
 * Register glue: x0 = x20, x1 = x26, x20 = x21.
 * Confidence: low (fallback disassemble). */
void cL4_mov_args20(void)
{
    /* x0 = x20; x1 = x26; x20 = x21; ret */
}

/* FUN_0008e2d0 @ 0x0008e2d0   (est. cL4_type_dispatch_f5b0)
 * Ghidra: void FUN_0008e2d0(void)
 * Tail call into cL4_type_desc(0x64f5b0, 0x4c1008): resolves a type
 * descriptor. Register/type setup glue.
 * Confidence: low (tail call). */
void cL4_type_dispatch_f5b0(void)
{
    cL4_type_desc(0x64f5b0, 0x4c1008);
}

/* FUN_0008e2ec @ 0x0008e2ec   (est. cL4_stack_frame_setup)
 * Ghidra: void FUN_0008e2ec(void)
 * Sets up a fault/error stack frame: x8 -= 0x20, x9 = 0xd000000000000017,
 * sp -= 0x10, [sp+8] = 0. Register glue for the error path.
 * Confidence: low (fallback disassemble). */
void cL4_stack_frame_setup(void)
{
    /* x8 -= 0x20; x9 = 0xd000000000000017; sp -= 0x10; [sp+8] = 0; ret */
}

/* FUN_0008e304 @ 0x0008e304   (est. cL4_obj_set_type)
 * Ghidra: void FUN_0008e304(long param_1)
 * Writes the constant code pointer 0x6753a0 into the object's type/isa field
 * at offset +0x38, tagging param_1 with its object type.
 * Confidence: low-medium */
void cL4_obj_set_type(long obj)
{
    *(unsigned long *)(obj + 0x38) = 0x6753a0;
}

/* FUN_0008e31c @ 0x0008e31c   (est. cL4_mul_ovf_check_x22)
 * Ghidra: void FUN_0008e31c(void)
 * Multiply-overflow check on x22,x10: x12 = umulh(x22,x10); negs sets carry
 * if the high product is non-zero. Register/flag glue.
 * Confidence: low (fallback disassemble). */
void cL4_mul_ovf_check_x22(void)
{
    /* x12 = umulh(x22, x10); negs xzr, x12; ret (carry = overflow) */
}

/* FUN_0008e328 @ 0x0008e328   (est. cL4_obj_load_x16b)
 * Ghidra: void FUN_0008e328(void)
 * Loads the object at [x22] into x16 and stores x22 into x17, preparing a
 * virtual dispatch. Register glue.
 * Confidence: low (fallback disassemble). */
void cL4_obj_load_x16b(void)
{
    /* x16 = *[x22]; x17 = x22; ret */
}

/* FUN_0008e334 @ 0x0008e334   (est. cL4_mul_w23_ovf)
 * Ghidra: void FUN_0008e334(void)
 * 32-bit multiply overflow test: x12 = umull(w23, w10); tst x12,
 * #0xffffffff00000000 sets flags if the 64-bit product exceeds 32 bits.
 * Register/flag glue.
 * Confidence: low (fallback disassemble). */
void cL4_mul_w23_ovf(void)
{
    /* x12 = umull(w23, w10); tst x12, #-0x100000000; ret (flags) */
}

/* FUN_0008e340 @ 0x0008e340   (est. cL4_mul_w21_ovf)
 * Ghidra: void FUN_0008e340(void)
 * 32-bit multiply overflow test on w21,w10: x12 = umull(w21,w10); tst x12,
 * #0xffffffff00000000. Register/flag glue.
 * Confidence: low (fallback disassemble). */
void cL4_mul_w21_ovf(void)
{
    /* x12 = umull(w21, w10); tst x12, #-0x100000000; ret (flags) */
}

/* FUN_0008e34c @ 0x0008e34c   (est. cL4_align64)
 * Ghidra: void FUN_0008e34c(void)
 * Aligns x20 down to 56 bits and adds 0x20: x8 = (x20 & 0xfffffffffffffff)
 * + 0x20. Register glue.
 * Confidence: low (fallback disassemble). */
void cL4_align64(void)
{
    /* x8 = (x20 & 0xfffffffffffffff) + 0x20; ret */
}

/* FUN_0008e358 @ 0x0008e358   (est. cL4_state_select)
 * Ghidra: void FUN_0008e358(void)
 * Selects a state word: x26 = x0, x8 = 0xe000000000000000, x25 = (x24==0) ?
 * x8 : x24, x0 = x21. Register glue.
 * Confidence: low (fallback disassemble). */
void cL4_state_select(void)
{
    /* x26 = x0; x8 = 0xe000000000000000; csel x25, x8, x24, eq; x0 = x21; ret */
}

/* FUN_0008e370 @ 0x0008e370   (est. cL4_is_plus_b)
 * Ghidra: void FUN_0008e370(void)
 * Tests whether low byte of w0 is '+' (0x2b), leaving flags. Register glue.
 * Confidence: low (fallback disassemble). */
void cL4_is_plus_b(void)
{
    /* w9 = w0 & 0xff; cmp w9, #0x2b; ret (flags) */
}

/* FUN_0008e37c @ 0x0008e37c   (est. cL4_mul_ovf_check_x21)
 * Ghidra: void FUN_0008e37c(void)
 * Multiply-overflow check on x21,x10: x12 = umulh(x21,x10); negs sets carry.
 * Register/flag glue.
 * Confidence: low (fallback disassemble). */
void cL4_mul_ovf_check_x21(void)
{
    /* x12 = umulh(x21, x10); negs xzr, x12; ret (carry = overflow) */
}

/* FUN_0008e388 @ 0x0008e388   (est. cL4_mov_x0_x1)
 * Ghidra: void FUN_0008e388(void)
 * Register glue: x0 = x21, x1 = x23.
 * Confidence: low (fallback disassemble). */
void cL4_mov_x0_x1(void)
{
    /* x0 = x21; x1 = x23; ret */
}

/* FUN_0008e394 @ 0x0008e394   (est. cL4_helper_2a0cf8_wrap)
 * Ghidra: void FUN_0008e394(void)
 * Wraps the out-of-slice helper cL4_helper_2a0cf8.
 * Confidence: low */
void cL4_helper_2a0cf8_wrap(void)
{
    cL4_helper_2a0cf8();
}

/* FUN_0008e3a4 @ 0x0008e3a4   (est. cL4_log_33)
 * Ghidra: void FUN_0008e3a4(undefined8 param_1, undefined8 param_2)
 * Logs a formatted message: cL4_log_print(param_1, param_2, 0x21, 0).
 * Confidence: low-medium */
void cL4_log_33(unsigned long a, unsigned long b)
{
    cL4_log_print(a, b, 0x21, 0);
}

/* FUN_0008e3b0 @ 0x0008e3b0   (est. cL4_log_1)
 * Ghidra: void FUN_0008e3b0(undefined8 param_1)
 * Logs a formatted message: cL4_log_print(param_1, &param_1, 1, 0).
 * Confidence: low-medium */
void cL4_log_1(unsigned long a)
{
    cL4_log_print(a, (unsigned long)&a, 1, 0);
}

/* FUN_0008e3c0 @ 0x0008e3c0   (est. cL4_bitfield_mask_b)
 * Ghidra: void FUN_0008e3c0(void)
 * Bitfield mask helper (variant): reads word at [x3+0x40] and field size
 * byte at [x3+0x20], returns the masked field in x10. Register glue.
 * Confidence: low (fallback disassemble). */
void cL4_bitfield_mask_b(void)
{
    /* x8 = x3; x10 = *[x3+0x40]; w9 = byte[x3+0x20]; mask; x10 = mask & x10 */
}

/* FUN_0008e3ec @ 0x0008e3ec   (est. cL4_helper_b340_wrap)
 * Ghidra: void FUN_0008e3ec(void)
 * Wraps the out-of-slice helper cL4_helper_b340.
 * Confidence: low */
void cL4_helper_b340_wrap(void)
{
    cL4_helper_b340();
}

/* FUN_0008e3f8 @ 0x0008e3f8   (est. cL4_count_to_cap)
 * Ghidra: void FUN_0008e3f8(void)
 * Computes x8 = ((x0 - 0x20) / 0x10) * 2 — the "used-count" encoding written
 * into a grown array header (element count in bits [1..]). Register glue.
 * Confidence: low (fallback disassemble). */
long cL4_count_to_cap(long x0)
{
    return ((x0 - 0x20) / 0x10) * 2;
}

/* FUN_0008e40c @ 0x0008e40c   (est. cL4_index_encode)
 * Ghidra: void FUN_0008e40c(void)
 * Encodes an index: x8 = ctz(x26) | (x23 << 9), composed from a bit position
 * and a base index. Register glue for the cap-table slot encoding.
 * Confidence: low (fallback disassemble). */
void cL4_index_encode(void)
{
    /* x8 = clz(rbit(x26)); x9 = x23 << 9; x8 = x9 | (x8 << 3); ret */
}

/* FUN_0008e420 @ 0x0008e420   (est. cL4_clear_w23)
 * Ghidra: void FUN_0008e420(void)
 * Register glue: w23 = 0, w10 = 0xa.
 * Confidence: low (fallback disassemble). */
void cL4_clear_w23(void)
{
    /* w23 = 0; w10 = 0xa; ret */
}

/* FUN_0008e42c @ 0x0008e42c   (est. cL4_cmp_x1_x0)
 * Ghidra: void FUN_0008e42c(void)
 * Register glue: w23 = 0, cmp x1, x0 leaves flags.
 * Confidence: low (fallback disassemble). */
void cL4_cmp_x1_x0(void)
{
    /* w23 = 0; cmp x1, x0; ret (flags) */
}

/* FUN_0008e438 @ 0x0008e438   (est. cL4_clear_w21)
 * Ghidra: void FUN_0008e438(void)
 * Register glue: w21 = 0, w10 = 0xa.
 * Confidence: low (fallback disassemble). */
void cL4_clear_w21(void)
{
    /* w21 = 0; w10 = 0xa; ret */
}

/* FUN_0008e444 @ 0x0008e444   (est. cL4_cmp_x1_x0_b)
 * Ghidra: void FUN_0008e444(void)
 * Register glue: w21 = 0, cmp x1, x0 leaves flags.
 * Confidence: low (fallback disassemble). */
void cL4_cmp_x1_x0_b(void)
{
    /* w21 = 0; cmp x1, x0; ret (flags) */
}

/* FUN_0008e450 @ 0x0008e450   (est. cL4_subsys_dart)
 * Ghidra: undefined8 FUN_0008e450(void)
 * Returns the constant 0x74726164 — the little-endian ASCII "dart". A
 * subsystem-name tag for the DART (I/O MMU) component.
 * Confidence: high (constant decodes to "dart"). */
unsigned long cL4_subsys_dart(void)
{
    return 0x74726164;   /* 'd','a','r','t' */
}

/* FUN_0008e45c @ 0x0008e45c   (est. cL4_clear_x24)
 * Ghidra: void FUN_0008e45c(void)
 * Register glue: x24 = 0, cmp x1, x0 leaves flags.
 * Confidence: low (fallback disassemble). */
void cL4_clear_x24(void)
{
    /* x24 = 0; cmp x1, x0; ret (flags) */
}

/* FUN_0008e468 @ 0x0008e468   (est. cL4_mov_x20_x17)
 * Ghidra: void FUN_0008e468(void)
 * Register glue: x20 = x0, x17 = x0.
 * Confidence: low (fallback disassemble). */
void cL4_mov_x20_x17(void)
{
    /* x20 = x0; x17 = x0; ret */
}

/* FUN_0008e474 @ 0x0008e474   (est. cL4_setup_5cb90)
 * Ghidra: void FUN_0008e474(void)
 * Register glue: x20 = x0, x8 = 0x5cb90 (a string/data address).
 * Confidence: low (fallback disassemble). */
void cL4_setup_5cb90(void)
{
    /* x20 = x0; x8 = 0x5c0000 + 0xbb0 - 0x20; ret */
}

/* FUN_0008e488 @ 0x0008e488   (est. cL4_tag_check)
 * Ghidra: void FUN_0008e488(void)
 * Tests the tag bits of x20: extracts the 4-bit field at bit 56 and tests
 * bit 61, leaving flags. Tag-encoded pointer disambiguation.
 * Confidence: low (fallback disassemble). */
void cL4_tag_check(void)
{
    /* x8 = ubfx(x20,#56,#4); tst x20, #0x2000000000000000; ret (flags) */
}

/* FUN_0008e494 @ 0x0008e494   (est. cL4_clear_x27)
 * Ghidra: void FUN_0008e494(void)
 * Register glue: x27 = 0, w10 = 0xa.
 * Confidence: low (fallback disassemble). */
void cL4_clear_x27(void)
{
    /* x27 = 0; w10 = 0xa; ret */
}

/* FUN_0008e4a0 @ 0x0008e4a0   (est. cL4_sp_tag_stack)
 * Ghidra: void FUN_0008e4a0(void)
 * Register glue: x27 = 0, x9 = (sp+0x18) | 1, w10 = 0xa.
 * Confidence: low (fallback disassemble). */
void cL4_sp_tag_stack(void)
{
    /* x27 = 0; x9 = (sp+0x18) | 1; w10 = 0xa; ret */
}

/* FUN_0008e4b4 @ 0x0008e4b4   (est. cL4_clear_x21)
 * Ghidra: void FUN_0008e4b4(void)
 * Register glue: x21 = 0, cmp x1, x0 leaves flags.
 * Confidence: low (fallback disassemble). */
void cL4_clear_x21(void)
{
    /* x21 = 0; cmp x1, x0; ret (flags) */
}

/* FUN_0008e4c0 @ 0x0008e4c0   (est. cL4_clear_x22)
 * Ghidra: void FUN_0008e4c0(void)
 * Register glue: x22 = 0, w10 = 0xa.
 * Confidence: low (fallback disassemble). */
void cL4_clear_x22(void)
{
    /* x22 = 0; w10 = 0xa; ret */
}

/* FUN_0008e4cc @ 0x0008e4cc   (est. cL4_cmp_x1_x0_c)
 * Ghidra: void FUN_0008e4cc(void)
 * Register glue: x22 = 0, cmp x1, x0 leaves flags.
 * Confidence: low (fallback disassemble). */
void cL4_cmp_x1_x0_c(void)
{
    /* x22 = 0; cmp x1, x0; ret (flags) */
}

/* FUN_0008e4d8 @ 0x0008e4d8   (est. cL4_load_add_sel)
 * Ghidra: void FUN_0008e4d8(void)
 * Register glue: x8 = *[x20+0x10]; x9 = ~w1 & 1; adds x28, x8, x9 leaves
 * flags. Increments a counter with the bitwise complement of w1's low bit.
 * Confidence: low (fallback disassemble). */
void cL4_load_add_sel(void)
{
    /* x8 = *[x20+0x10]; w9 = mvn(w1) & 1; adds x28, x8, x9; ret (flags) */
}

/* FUN_0008e4ec @ 0x0008e4ec   (est. cL4_helper_725c8_wrap)
 * Ghidra: void FUN_0008e4ec(void)
 * Wraps the out-of-slice helper cL4_helper_725c8.
 * Confidence: low */
void cL4_helper_725c8_wrap(void)
{
    cL4_helper_725c8();
}

/* FUN_0008e500 @ 0x0008e500   (est. cL4_restore_regs)
 * Ghidra: void FUN_0008e500(void)
 * Function epilogue helper: restores the callee-saved registers x19-x28 from
 * the stack (the mirror of cL4_save_regs). Register glue.
 * Confidence: high (disassembly is a clean register restore). */
void cL4_restore_regs(void)
{
    /* ldp x20,x19,[sp,#0x40]; ldp x22,x21,[sp,#0x30]; ldp x24,x23,[sp,#0x20];
     * ldp x26,x25,[sp,#0x10]; ldp x28,x27,[sp],#0x60; ret */
}

/* FUN_0008e518 @ 0x0008e518   (est. cL4_save_regs)
 * Ghidra: void FUN_0008e518(void)
 * Function prologue helper: saves the callee-saved registers x19-x28 to the
 * stack (allocating 0x60 bytes). Register glue.
 * Confidence: high (disassembly is a clean register save). */
void cL4_save_regs(void)
{
    /* stp x28,x27,[sp,#-0x60]!; stp x26,x25,[sp,#0x10]; stp x24,x23,[sp,#0x20];
     * stp x22,x21,[sp,#0x30]; stp x20,x19,[sp,#0x40]; ret */
}

/* FUN_0008e530 @ 0x0008e530   (est. cL4_helper_258c60_wrap)
 * Ghidra: void FUN_0008e530(void)
 * Wraps the out-of-slice helper cL4_helper_258c60.
 * Confidence: low */
void cL4_helper_258c60_wrap(void)
{
    cL4_helper_258c60();
}

/* FUN_0008e544 @ 0x0008e544   (est. cL4_state_step)
 * Ghidra: void FUN_0008e544(void)
 * Steps the cL4 state machine: drives cL4_helper_6a4c0 then cL4_array_end_ptr
 * (state advance). Wrapper.
 * Confidence: low-medium */
void cL4_state_step(void)
{
    cL4_helper_6a4c0();
    cL4_array_end_ptr(0);
}

/* FUN_0008e570 @ 0x0008e570   (est. cL4_dispatch_via_entry)
 * Ghidra: void FUN_0008e570(undefined8,undefined8,undefined8,undefined8,
 *   undefined8,undefined8)
 * Resolves the dispatch entry point for param_5 via cL4_entry_resolve
 * (FUN_0008e5d8) and jumps through it with (param_1, param_4, param_6,
 * param_3, param_5). Indirect-jump dispatch (decompiler could not recover
 * the jump table at 0x8e5d4).
 * Confidence: low (indirect jump; fallback notes). */
void cL4_dispatch_via_entry(unsigned long p1, unsigned long p2, unsigned long p3,
                            unsigned long p4, unsigned long p5, unsigned long p6)
{
    unsigned long entry = cL4_entry_resolve(p5);
    (*(void (**)(unsigned long, unsigned long, unsigned long, unsigned long,
                 unsigned long))entry)(p1, p4, p6, p3, p5);
}

/* FUN_0008e5d8 @ 0x0008e5d8   (est. cL4_entry_resolve)
 * Ghidra: long FUN_0008e5d8(unsigned long param_1)
 * Resolves an entry point: given a (possibly tagged) object pointer, returns
 * base + 4 + the signed 32-bit offset stored at base+4 — i.e. the object's
 * indirection/entry target.
 * Confidence: high (explicit pointer arithmetic). */
long cL4_entry_resolve(unsigned long p)
{
    if (p & 1) {
        p = *(unsigned long *)(p & ~1ull);
    }
    return (long)(p + 4) + (long)*(int *)(p + 4);
}

/* FUN_0008e608 @ 0x0008e608   (est. cL4_obj_alloc_init)
 * Ghidra: undefined8 FUN_0008e608(void)
 * Allocates a 0x10-byte object of kind 7 (via cL4_obj_alloc_typed) and
 * initializes it through cL4_obj_init (FUN_0008e640). Returns the object.
 * Confidence: medium */
void *cL4_obj_alloc_init(void)
{
    void *obj = cL4_obj_alloc_typed(0, 0x10, 7);
    cL4_kobj_initialize(obj);
    return obj;
}

/* FUN_0008e640 @ 0x0008e640   (est. cL4_obj_init)
 * Ghidra: void FUN_0008e640(undefined8,undefined8,undefined8,unsigned long param_4)
 * Initializes a freshly allocated object: opens an access window over a
 * 0x30-byte region, zeroes the object's 6 words, then (optionally) decommits
 * the zeroed range back to the allocator. Includes fatal-error handling when
 * the zero fill returns short. param_4 carries a length/ownership word.
 * Confidence: medium
 * Notes: faults at SoftwareBreakpoint 0x8e724/0x8e728/0x8e72c/0x8e730; the
 *   object base is computed from caller registers x22/x23. */
void cL4_kobj_initialize(void *obj)
{
    cL4_access_begin(0x30);
    cl4_result_t st = cL4_state_get();
    unsigned long len = 0;   /* param_4 */
    cL4_access_end(0x30);
    unsigned long *p = (unsigned long *)obj;   /* x22 + x23 (caller regs) */
    p[0] = p[1] = p[2] = p[3] = p[4] = p[5] = 0;

    if ((long)(len >> 1) < 0) {
        CL4_FAULT(0x8e724);
    }
    if ((len & 1) == 0) {
        cL4_state_put();
        cL4_state_get();
    }
    if ((long)((len >> 1)) < 0) {
        CL4_FAULT(0x8e728);
    }
    long n = cL4_bzero((unsigned long)obj, 0x30);
    if (n != 0x30) {
        /* fatal: internal exclave launcher prng_swi error */
        cL4_fatal_error(0xd000000000000036, 0x80000000005c0d60, 0x22, 2, 0x23, 0, st, len);
    }
    if (!(len >> 1 < 0)) {
        if (((len & 1) == 0) || ((cL4_cpu_state().lo & 1) == 0)) {
            cL4_state_put();
            cL4_state_get();
        }
        if (-1 < (long)((len >> 1))) {
            cL4_bzero_release(0x30, (unsigned long)obj);
            cL4_arr_header_release(0);
            return;
        }
        CL4_FAULT(0x8e730);
    }
    CL4_FAULT(0x8e72c);
}

/* FUN_0008e77c @ 0x0008e77c   (est. cL4_launch_thread)
 * Ghidra: void FUN_0008e77c(undefined8,undefined8,undefined8)
 * Launches a new thread/task: enters the launch path, builds a task
 * descriptor via cL4_task_create, resolves the launch body, builds the
 * thread-context record, and either commits the new thread (cL4_thread_commit
 * path) or halts the kernel on failure (SoftwareBreakpoint 0x8e958).
 * Confidence: low (complex launch glue; decompiler artifacts at SUB_911a...).
 * Notes: direct register/stack manipulation and an unrecovered address
 *   (SUB_911a421090000010) make a fully faithful C body impractical here. */
void cL4_launch_thread(unsigned long a, unsigned long b, unsigned long c)
{
    cL4_launch_enter(c);
    unsigned long state = cL4_launch_state();
    long task = cL4_task_create(0, state, b, 0x60e3fc, 0x60e40c);
    /* ... build launch record, link task, resolve body (0x8f728), etc. ... */
    void *kobj = cL4_kobj_alloc(0);
    if (kobj != 0) {
        cL4_thread_commit(state, b, (unsigned long)kobj);
        cL4_task_link(b, c, (unsigned long)kobj, a, (void *)0x66d208);
        return;
    }
    cL4_state_halt(0x2e);
    CL4_FAULT(0x8e958);
}

/* FUN_0008e958 @ 0x0008e958   (est. cL4_launch_finalize)
 * Ghidra: void FUN_0008e958(undefined4 *param_1, undefined8 param_2,
 *   undefined8 *param_3, long param_4)
 * Finalizes a launch: if the function pointer at *param_3 is set, invokes it
 * with (param_3, type-of-param_4, param_2) and stores the 32-bit result into
 * *param_1; otherwise faults (SoftwareBreakpoint 0x8e9bc).
 * Confidence: low-medium */
void cL4_launch_finalize(unsigned int *out, unsigned long arg,
                         unsigned long (*fn)(void *, unsigned long, unsigned long),
                         long type)
{
    if (fn != 0) {
        *out = fn((void *)&fn, *(unsigned long *)(type - 8) + 0x48, arg);
        return;
    }
    CL4_FAULT(0x8e9bc);
}

/* FUN_0008e9bc @ 0x0008e9bc   (est. cL4_launch_step)
 * Ghidra: void FUN_0008e9bc(void)
 * Steps the launch/thread-commit state machine: drives the launch body with
 * a freshly built stack frame, and if the owner (x21) is non-null invokes the
 * type's +0x20 virtual method with (x7, frame, x4) to finish the commit.
 * Confidence: low (register/stack glue; SUB_911a... artifact). */
void cL4_launch_step(void)
{
    long type = 0;   /* in_x4 - 8 (caller-reserved) */
    /* build frame, run launch body (extraout_x12), then:
     * if (owner) (**(type+0x20))(x7, frame, x4); */
}

/* FUN_0008ea84 @ 0x0008ea84   (est. cL4_thread_commit_region)
 * Ghidra: void FUN_0008ea84(undefined8,undefined8,long,ulong)
 * Commits a thread-context region: allocates a kernel object (faults if
 * allocation fails), binds the current thread to param_1, validates the
 * ownership word, and on success performs the final commit (cL4_thread_commit)
 * releasing the region. On invalid state it faults (0x8eb30/34/38).
 * Confidence: low (register/state based).
 * Notes: faults at SoftwareBreakpoint 0x8eb30/0x8eb34/0x8eb38/0x8eb48. */
void cL4_thread_commit_region(unsigned long a, unsigned long b, long base, unsigned long len)
{
    long *kobj = cL4_kobj_alloc(0);
    if (kobj == 0) {
        cL4_state_halt(0x3c);
        CL4_FAULT(0x8eb48);
    }
    cL4_thread_bind(0, a);
    if (!(len >> 1 < base)) {
        cL4_state_peek();
        /* validate ownership / state flags */
        if (-1 < (long)((len >> 1) - base)) {
            if (*kobj != 0) {
                cL4_thread_commit(0, 0, 0);   /* cL4_state_peek().lo/hi + base */
                cL4_state_push();
                return;
            }
            CL4_FAULT(0x8eb38);
        }
        CL4_FAULT(0x8eb34);
    }
    CL4_FAULT(0x8eb30);
}

/* FUN_0008eb48 @ 0x0008eb48   (est. cL4_obj_vtable40)
 * Ghidra: void FUN_0008eb48(void)
 * Invokes the virtual method at vtable offset +0x40 of the object whose
 * vtable pointer is *x20. Generic virtual call helper.
 * Confidence: low (register-based dispatch). */
void cL4_obj_vtable40(void)
{
    (*(void (**)(void))(*(long *)(*((volatile unsigned long *)0)) + 0x40))();
}

/* FUN_0008eb84 @ 0x0008eb84   (est. cL4_obj_vtable48)
 * Ghidra: void FUN_0008eb84(void)
 * Invokes the virtual method at vtable offset +0x48 of the object whose
 * vtable pointer is *x20.
 * Confidence: low (register-based dispatch). */
void cL4_obj_vtable48(void)
{
    (*(void (**)(void))(*(long *)(*((volatile unsigned long *)0)) + 0x48))();
}

/* FUN_0008ebc0 @ 0x0008ebc0   (est. cL4_list_node_create)
 * Ghidra: void FUN_0008ebc0(undefined8 param_1, undefined8 param_2)
 * Creates a list-node object: allocates an object, stores param_1 at +0x10
 * and param_2 at +0x18, and links the default handler table at +0x20.
 * Confidence: medium */
void cL4_list_node_create(unsigned long a, unsigned long b)
{
    unsigned long node = (unsigned long)cL4_obj_alloc_typed(0, 0, 0);
    *(unsigned long *)(node + 0x10) = a;
    *(unsigned long *)(node + 0x18) = b;
    *(unsigned long **)(node + 0x20) = &cL4_default_handler;
}
