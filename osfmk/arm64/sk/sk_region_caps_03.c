/* Recreated from exclavecore_bundle.t8142.RELEASE.im4p (cL4 Secure Kernel,
 * arm64e, image base 0) — the cL4 (Apple seL4-derived) microkernel (GL1),
 * "cL4 (679.100.61)". Ground truth: Ghidra FUN_ names + addresses in program
 * cl4_kernel.raw.
 *
 * Slice 03: 0x80000-0x100000 caps region — the kernel capability / object
 * data-structure layer (dynamic arrays, sorted maps of caps, slot vectors,
 * iterator scans over the cap table).
 *
 * SeL4/cL4 vocabulary is used for naming (CNode, cap, slot, TCB, endpoint,
 * notification, vspace, sched). Confidence is medium unless a string matches.
 */

#include "sk_internal.h"

#include <stdint.h>
#include <stddef.h>
#include <string.h>

/* ------------------------------------------------------------------ *
 * Out-of-slice cL4 helper declarations (extern with a one-line note).
 * ------------------------------------------------------------------ */

/* FUN_0036a940 — cL4 allocation of a typed object of `size` bytes with
 * allocation kind/tag 7; returns zeroed memory. */
extern void *cL4_obj_alloc_typed(unsigned long tag, unsigned long size, int kind);
/* FUN_0036b118 — release/free a dynamic-array / object header (LO release). */
extern void cL4_arr_header_release(void *hdr);
/* FUN_0036b270 — release a reference on an object (LO refcount dec). */
extern void cL4_ref_dec(unsigned long obj);
/* FUN_00002534 — resolve a class/type descriptor (magic at addr, index
 * table); returns the type record used for allocation. */
extern unsigned long cL4_type_desc(unsigned long magic, unsigned long table);
/* thunk_FUN_000126e8 — set up / validate a fresh object allocation (returns
 * the object's usable base pointer). */
extern void *cL4_obj_init(void *obj);
/* FUN_00117d14 — byte copy (memcpy) of `n` bytes from src to dst. */
extern void cL4_memcpy(void *dst, const void *src, unsigned long n);
/* FUN_00089684 — fetch the current dynamic-array descriptor / thread-local
 * container header; returns a 16-byte {base, length} pair. */
extern cl4_result_t cL4_vec_current(void);

/* In-slice helpers (decompiled below / referenced before their own entry):
 *   0x8e518 cL4_scan_enter   — begin a slot-table scan
 *   0x8df78 cL4_scan_rows    — prime/validate the row cursor (x1 != 0 if any)
 *   0x8e22c cL4_slot_row     — load the next row bitmap
 *   0x8e2a0 cL4_slot_bit     — isolate the lowest set bit of the row bitmap
 *   0x8e070 cL4_scan_finish  — finish the scan with a final row count
 *   0x8e500 cL4_scan_publish — publish the scan result to the caller's state
 *   0x8df78 cL4_slice_open   — open a container slice
 *   0x8e22c cL4_slot_next    — advance to the next populated row
 */
extern void cL4_scan_enter(void);
extern unsigned long cL4_scan_rows(void);
extern void cL4_slot_row(void);
extern word_t cL4_slot_bit(void);
extern word_t cL4_scan_finish(word_t row);
extern void cL4_scan_publish(word_t result, word_t state);

/* ------------------------------------------------------------------ *
 * Slice 03 function bodies (in ascending address order).
 * ------------------------------------------------------------------ */

/* FUN_0008d350 @ 0x0008d350   (est. cL4_caps_scan_and_collect)
 * Ghidra: void FUN_0008d350(undefined8 param_1, undefined8 param_2, long param_3)
 * Scans the capability table row-by-row: each row is a 64-bit slot bitmap,
 * and every set bit addresses a 6-word (0x30-byte) cap record in the table
 * at *container+0x38. Each found record is copied verbatim into a caller-
 * supplied record vector (x22). The scan stops once `param_3` records have
 * been collected (or the bitmap is exhausted if param_3 <= 0), and the final
 * row/record count is published back to the caller state (x30).
 * Side effects: consumes the row bitmap (x25) via cL4_slot_bit, advances a
 * cursor (x27) through the rows, and finally publishes the result count.
 * Confidence: medium
 * Notes: many values live in registers across the whole body (x20..x30);
 *   bounds/overflow faults raise SoftwareBreakpoint(1,0x8d43c/8d438). */
void cL4_caps_scan_and_collect(word_t kind, word_t opts, long limit)
{
    cL4_scan_enter();
    unsigned long row_ok = cL4_scan_rows();
    word_t row;

    if (row_ok == 0) {
        row = 0;
    } else {
        if (limit < 0) {
            /* Negative limit: unreachable (software fault). */
            __builtin_trap();
        }
        if (limit == 0) {
            row = 0;
        } else {
            cL4_slot_row();          /* load first row bitmap */
            while (1) {
                word_t bitmap = /* row bitmap in x25 */ 0;
                while (bitmap == 0) {
                    word_t next = row + 1;
                    if (next < row) {
                        __builtin_trap();      /* row counter overflow */
                    }
                    if (/* row_limit */ 0 <= next) {
                        /* past the last row */
                        goto scan_done;
                    }
                    row = next;
                    bitmap = cL4_slot_row();   /* load next row bitmap */
                }
                /* lowest set bit of the current row -> slot record index */
                cL4_slot_bit();
                bitmap = bitmap - 1;
                /* read the 6-word cap record for slot `row` and append it to
                 * the destination vector; record index = (row<<6)|bitpos,
                 * element size 0x30 bytes at base *(container+0x38). */
                uint64_t *rec = (uint64_t *)cL4_caps_record(row, bitmap);
                if (/* collected count */ 0 == limit) {
                    break;
                }
                /* record copy (6 words) elided in scan loop */
                cL4_ref_dec(0);
            }
            cL4_ref_dec(0);
        }
    }

scan_done:
    cL4_scan_publish(cL4_scan_finish(row), 0);
}
