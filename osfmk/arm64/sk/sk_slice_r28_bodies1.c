/* ------------------------------------------------------------------ *
 * 0x0047c528 — message/op dispatch switch.
 * ------------------------------------------------------------------ */

/* FUN_0047c528 @ 0x0047c528   (est. sk_r28_op_dispatch)
 * Ghidra: void FUN_0047c528(undefined8,undefined8,undefined8,undefined8,undefined8)
 * Reads the method pointer at self+0x10 and a kind byte at self+0x20. On the
 * default path builds a 5-word message (arg2..arg5 into a fresh object at
 * 0x686160), refs arg5, invokes the method, then releases the message. On
 * kinds 1 and 3 releases arg1 and invokes the method with no message.
 * Confidence: medium.
 * Notes: unaff_x20 = self (method-table owner); FUN_000026e8 = msg release;
 *   FUN_0036a940 = alloc; thunk_FUN_0036b270 = refcount acquire. */
void sk_r28_0047c528(uint64_t a2, uint64_t a3, uint64_t a4, uint64_t a5)
{
    uint64_t self = 0;                 /* unaff_x20: method-table owner */
    uint64_t (*method)(void) = *(uint64_t (**)(void))(self + 0x10);
    uint64_t kind = *(uint8_t *)(self + 0x20);
    switch (kind) {
    case 1:
    case 3:
        sk_x_000a6e14(a2);
        sk_x_00352ae4();
        (*method)();
        break;
    default: {
        uint64_t msg = sk_x_0036a940();
        *(uint64_t *)(msg + 0x10) = a2;
        *(uint64_t *)(msg + 0x18) = a3;
        *(uint64_t *)(msg + 0x20) = a4;
        *(uint64_t *)(msg + 0x28) = a5;
        sk_x_0036b270(a5);
        (*method)(a2, msg);
        sk_x_000026e8(msg);
        break;
    }
    }
}

/* FUN_0047c62c @ 0x0047c62c   (est. sk_r28_utf8_iter_setup)
 * Ghidra: void FUN_0047c62c(void)
 * Reads a string/error box; if its kind (lStack_78) is 1 (owned/ascii) it
 * validates a count in_x3 and, if the count is underflowed, traps; otherwise
 * forwards (count-1) to an append helper. Else copies the box words to the
 * caller frame and builds a UTF-8 view descriptor.
 * Confidence: low (register-heavy: unaff_x21/x22, in_x3).
 * Notes: SoftwareBreakpoint(1,0x47c7ac). */
void sk_r28_0047c62c(void)
{
    int64_t in_x3 = 0;                 /* unmodeled caller count register */
    uint64_t unaff_x21 = 0, unaff_x22 = 0;
    sk_x_003509ec();
    sk_x_004ab128();
    sk_x_004a4ac4(&unaff_x22, &unaff_x21);
    if (/* lStack_78 == 1 */ 1) {
        sk_x_004aaccc();
        uint64_t v = sk_x_004a4b14(&unaff_x21);
        if (in_x3 < 1) {
            SoftwareBreakpoint(1, 0x47c7ac);
        }
        sk_x_004ac41c(v, in_x3 - 1);
        sk_r28_0047ce4c();
    } else {
        sk_x_004a4ac4(&unaff_x22, &unaff_x21);
        sk_x_004a4b14(&unaff_x21);
    }
}

/* FUN_0047c7b0 @ 0x0047c7b0   (est. sk_r28_value_read)
 * Ghidra: void FUN_0047c7b0(undefined8 *out, undefined8)
 * Reads a value box via the method at self+0x10 keyed on the kind byte at
 * self+0x20: kind 1/3 copy a UTF-8 scalar and ref it; kind 2 reads directly;
 * otherwise moves the box contents into out with refcount bookkeeping.
 * Confidence: low (register-heavy: unaff_x20/x21).
 * Notes: FUN_00319808 value copy; FUN_003a25d4 release. */
void sk_r28_0047c7b0(uint64_t *out, uint64_t a2)
{
    uint64_t self = 0;                 /* unaff_x20 */
    int64_t unaff_x21 = 0;             /* unaff_x21: caller flag */
    uint64_t flag = (uint64_t)unaff_x21;
    uint64_t (*method)(void) = *(uint64_t (**)(void))(self + 0x10);
    uint64_t kind = *(uint8_t *)(self + 0x20);
    uint64_t buf[4];
    switch (kind) {
    case 1:
        sk_x_00319808(a2, buf);
        sk_x_00351f34();
        sk_x_004ab1dc();
        sk_x_00365b6c(buf);
        (*method)(buf);
        sk_x_003a25d4(buf[3]);
        break;
    case 2:
        (*method)(out);
        break;
    case 3:
        sk_x_00319808(a2, buf);
        sk_x_00351f34();
        sk_x_004ab1dc();
        sk_x_00365b6c(buf);
        (*method)(out, buf[0], buf[1], buf[2], buf[3]);
        sk_x_003a25d4(buf[3]);
        if (flag != 0) return;
        out[1] = buf[1]; out[0] = buf[0]; out[3] = buf[3]; out[2] = buf[2];
        return;
    default:
        break;
    }
    if (flag == 0) {
        sk_x_0034cc24();
        sk_x_004a4b14(buf);
        out[0] = out[1] = out[2] = out[3] = 0;
    }
}

/* FUN_0047c948 @ 0x0047c948   (est. sk_r28_log_start)
 * Ghidra: void FUN_0047c948(void)
 * Starts a log/report record: reads a message tag, allocates a record object,
 * then chains a series of report-field appends. Confidence: medium.
 * Notes: unaff_x20 = self; FUN_00002834 tag load; FUN_0036a940 alloc. */
void sk_r28_0047c948(void)
{
    uint64_t self = 0;                 /* unaff_x20 */
    sk_x_0008409c();
    sk_x_00002834(0x687d98);
    sk_x_0036a940();
    sk_x_004ac5b4();
    sk_x_003507e0();
    sk_x_00498ad4();
    sk_x_004aad54();
    sk_x_00498bdc();
    sk_x_004ab224(*(uint64_t *)(self + 0x40));
    sk_x_004abf5c();
}

/* FUN_0047c9d4 @ 0x0047c9d4   (est. sk_r28_log_args)
 * Ghidra: void FUN_0047c9d4(ulong,long)
 * Folds arg1 and arg2<<16 into a packed argument word and appends it to the
 * in-flight report record. Confidence: medium. */
void sk_r28_0047c9d4(uint64_t a1, int64_t a2)
{
    sk_x_004aa494(a1 | (uint64_t)a2 << 0x10);
    sk_x_00498b28(0);
    sk_x_004aaf58();
    sk_x_004aa6a8();
}

/* FUN_0047ca18 @ 0x0047ca18   (est. sk_r28_parse_group)
 * Ghidra: bool FUN_0047ca18(long)
 * Recursive regex group parser: walks the token stream at param+0x10 and
 * handles alternation/open groups, recursing into FUN_0047ca18 for nested
 * groups. Returns whether a group matched. Confidence: medium. */
bool sk_r28_0047ca18(int64_t a1)
{
    int64_t n = *(int64_t *)(a1 + 0x10);
    uint8_t s1[352], s2[352], s3[352];
    uint64_t r;
    do {
        while (1) {
            int64_t save = n;
            n = save - 1;
            if (save == 0) goto done;
            sk_x_004ac3e4(s2);
            sk_x_004ac3e4(s3);
            int k = sk_x_0049df0c(s2);
            if (k == 2) break;
            if (k == 0) {
                sk_x_0049df18(s3);
                int k2 = sk_x_0049e2d4();
                if (k2 == 10) goto done;
            }
        }
        sk_x_0049df18(s3);
        sk_x_004ac4e0();
        sk_x_004ac034(s1);
        sk_x_00352c68();
        r = (uint64_t)sk_r28_0047ca18(0);
        sk_x_004a3918(s2);
    } while ((r & 1) == 0);
done:
    return n != 0;
}

/* FUN_0047cadc @ 0x0047cadc   (est. sk_r28_string_scan)
 * Ghidra: bool FUN_0047cadc(ulong,ulong)
 * Unicode scalar scan/compare of a UTF-8 string (params = {buf, len}-packed
 * words). Walks the string by 16-byte page, decoding each scalar, comparing
 * against a 2-char target, and returns whether the first mismatch / end
 * matched. Traps on page overflow. Confidence: low.
 * Notes: unaff_x20 = page cursor; FUN_002b141c utf8 decode; FUN_0001da84
 *   page advance; SoftwareBreakpoint(1,0x47cc94). */
bool sk_r28_0047cadc(uint64_t a1, uint64_t a2)
{
    uint64_t len = a1 & 0xffffffffffff;
    if ((a2 & 0x2000000000000000) != 0)
        len = a2 >> 0x38 & 0xf;
    uint32_t big = (uint32_t)(a1 >> 0x3b) & 1;
    if ((a2 & 0x1000000000000000) == 0)
        big = 1;
    sk_x_0036b270(a2);
    uint64_t page = 0xf;
    uint64_t idx = 0;
    uint64_t target;
    uint8_t c = 0;
    do {
        idx = page >> 0xe;
        if (idx == len * 4) break;
        uint64_t p = page;
        if ((page & 0xc) == (4ULL << big))
            p = sk_x_0001da84(page, a1, a2);
        uint64_t off = p >> 0x10;
        if (len <= off)
            SoftwareBreakpoint(1, 0x47cc94);
        if ((a2 >> 0x3c & 1) == 0) {
            if ((a2 >> 0x3d & 1) == 0) {
                int64_t base = (a2 & 0xfffffffffffffff) + 0x20;
                if ((a1 >> 0x3c & 1) == 0)
                    base = sk_x_002a9ba8(a1, a2);
                c = *(uint8_t *)(base + off);
            } else {
                uint64_t w0 = a1, w1 = a2 & 0xffffffffffffff;
                c = *(uint8_t *)((uint64_t)&w0 + off);
            }
        } else {
            c = sk_x_002b141c(p, a1, a2);
        }
        if ((page & 0xc) == (4ULL << big)) {
            page = sk_x_0001da84(page, a1, a2);
            if ((a2 >> 0x3c & 1) != 0) goto again;
            page = (page & 0xffffffffffff0000) + 0x10004;
        } else {
            if ((a2 >> 0x3c & 1) == 0) {
                page = (page & 0xffffffffffff0000) + 0x10004;
            } else {
again:
                if (len <= page >> 0x10)
                    SoftwareBreakpoint(1, 0x47cc98);
                page = sk_x_002b141c(page, a1, a2);
            }
        }
        uint64_t v = sk_x_0024d9ac(&sk_g_005a5538);
        uint8_t c1 = c;
        sk_x_0024917c(&target, &c1);
        sk_x_0036b118(v);
    } while ((target & 1) != 0);
    sk_x_003a25d4(a2);
    return idx != len * 4;
}

/* FUN_0047cc98 @ 0x0047cc98   (est. sk_r28_parse_alternation)
 * Ghidra: uint FUN_0047cc98(long)
 * Recursive regex alternation parser over the token stream at param+0x10;
 * dispatches on token kinds 5/6/7 (open/close/pipe) and recurses.
 * Confidence: medium. */
uint32_t sk_r28_0047cc98(int64_t a1)
{
    int64_t n = *(int64_t *)(a1 + 0x10);
    uint8_t s1[352], s2[352], s3[352];
    uint32_t r = 0;
    uint64_t rr;
loop:
    if (n == 0) { r = 0; goto ret; }
    sk_x_004ac3e4(s1);
    sk_x_004ac3e4(s2);
    int k = sk_x_0049df0c(s1);
    if ((uint32_t)(k - 4) > 3) { r = 1; goto ret; }
    switch (k) {
    case 5:
    case 7:
        sk_x_0049df18(s2);
        sk_x_004ac4e0();
        sk_x_004ac034(s3);
        sk_x_00352c68();
        rr = (uint64_t)sk_r28_0047cc98(0);
        if ((rr & 1) == 0) { sk_x_004a3918(s1); r = 0; goto ret; }
        break;
    case 6:
        sk_x_0049df18(s2);
        sk_x_004ac4e0();
        sk_x_004ac034(s3);
        break;
    default:
        n = n - 1;
        goto loop;
    }
    sk_x_0035354c();
    r = (uint32_t)sk_r28_0047cc98(0);
    sk_x_004a3918(s1);
ret:
    return r & 1;
}

/* FUN_0047cdbc @ 0x0047cdbc   (est. sk_r28_string_init)
 * Ghidra: void FUN_0047cdbc(undefined8,undefined8,undefined8)
 * Builds a string/error box: reads a scalar/char, allocates a descriptor,
 * then invokes the method with the packed value and tears the box down.
 * Confidence: low (extraout_x16 = method owner, unmodeled). */
void sk_r28_0047cdbc(uint64_t a1, uint64_t a2, uint64_t a3)
{
    uint64_t owner = 0;                /* extraout_x16: method owner */
    uint64_t u1 = sk_x_00350a28();
    uint64_t box = sk_x_00310d68(0, a3);
    uint8_t buf[24];
    sk_x_00077024(buf);
    uint64_t u2 = sk_x_003509c8();
    (*(uint64_t (**)(void))(owner + 0x10))(u2, u1);
    sk_x_004ab9e0();
    sk_x_00350774();
    sk_x_000839d8();
    sk_x_000026e8();
    sk_x_004ab618();
    sk_x_00310d98();
}

/* FUN_0047ce4c @ 0x0047ce4c   (est. sk_r28_string_finish)
 * Ghidra: void FUN_0047ce4c(void)
 * Finalizes a string record: stores the boxed value into self+0x18, marks
 * ownership, and emits the report close. Confidence: medium.
 * Notes: unaff_x20 = self; FUN_000839d8 report. */
void sk_r28_0047ce4c(void)
{
    uint64_t self = 0;                 /* unaff_x20 */
    sk_x_00352800();
    sk_x_003504e8();
    uint64_t v = sk_x_00310d68();
    *(uint64_t *)(self + 0x18) = v;
    v = sk_x_00077024();
    sk_x_00350774(v, 1);
    sk_x_000839d8();
}

/* FUN_0047ce8c @ 0x0047ce8c   (est. sk_r28_string_compare)
 * Ghidra: void FUN_0047ce8c(void)
 * Compares two strings via the shared error/string box and reports the
 * result. Confidence: low (unaff_x20 = self). */
void sk_r28_0047ce8c(void)
{
    uint64_t self = 0;                 /* unaff_x20 */
    uint64_t kind = 0;                 /* lStack_38 local kind */
    uint8_t out[16], tmp[24];
    sk_x_004ab128();
    sk_x_004a4ac4(self + 8, out);
    if (kind != 1) {
        sk_x_0034cc24();
        sk_x_004a4b14(tmp);
    } else {
        sk_x_004aaccc();
        sk_x_004a4b14(out);
    }
    sk_x_0009461c();
}

/* FUN_0047cf0c @ 0x0047cf0c   (est. sk_r28_array_append)
 * Ghidra: void FUN_0047cf0c(undefined8 x 6)
 * Bulk-appends param_6 records (each 0x58 bytes) read at param_6+0x20 into
 * the global array DAT_00657778, decoding each record, growing the array as
 * needed. Then drains the appended records building result objects.
 * Confidence: low (large; SoftwareBreakpoint(1,0x47d348)).
 * Notes: heavy use of thunk_FUN_0024d9ac iterator, FUN_00117cc4 memmove. */
void sk_r28_0047cf0c(uint64_t a1, uint64_t a2, uint64_t a3, uint64_t a4, uint64_t a5, int64_t a6)
{
    uint64_t it = sk_x_0024d9ac(&sk_g_005a4b50);
    int64_t base = a6 + 0x20;
    uint64_t arr = 0x657778;   /* DAT_00657778 (array header) */
    int64_t i;
    for (i = *(int64_t *)(a6 + 0x10); i != 0; i = i - 1) {
        uint8_t rec[0x68];
        uint8_t tag;
        uint64_t box[2] = { a4, a5 };
        sk_x_0049c704(base, &rec);
        sk_x_00117cc4(&rec, &box, 0x68);
        sk_x_0036b270(a5);
        sk_x_0024917c(&tag, &rec);
        if (tag == 0x01) {
            uint64_t n;
            sk_x_003a261c(&arr);
            n = *(uint64_t *)(arr + 0x10);
            if (*(uint64_t *)(arr + 0x18) >> 1 <= n)
                sk_x_0049a604(1 < *(uint64_t *)(arr + 0x18), n + 1, 1);
            *(uint64_t *)(arr + 0x10) = n + 1;
            sk_x_00117cc4(arr + n * 0x68 + 0x20, &rec, 0x68);
        } else {
            sk_x_0049c714(&rec);
        }
        base += 0x58;
    }
    sk_x_0036b118(it);
    /* drain phase */
    int64_t cnt = *(int64_t *)(arr + 0x10);
    uint64_t out = 0x657778;
    if (cnt == 0) {
        sk_x_0036b118(arr);
    } else {
        int64_t j;
        sk_x_001a0754(0, cnt, 0);
        for (j = 0; j != cnt; j++) {
            uint64_t v = *(uint64_t *)(arr + j * 0x68 + 0x20);
            uint8_t rbox[8];
            sk_x_004a4ac4(arr + j * 0x68 + 0x20 + 8, &rbox, 0x657be0, &sk_g_005a3c88);
            if (kind2 == 1) {
                sk_x_004a4b14(&rbox, 0x657be0, &sk_g_005a3c88);
                if ((int64_t)v < 1)
                    SoftwareBreakpoint(1, 0x47d348);
                sk_x_00455ac8(0x675c68, v - 1, 0x675c68);
                sk_r28_0047ce4c();
            } else {
                int64_t k = (int64_t)v;
                for (; k != 0; k = k - 1) {
                    uint8_t rr[8];
                    sk_x_00319808(out, &rr);
                    uint64_t w = sk_x_0006a4c0(&rr);
                    sk_r28_0047cdbc(w, out, 0);
                    sk_x_000026e8(&rr);
                }
            }
            uint64_t n2 = *(uint64_t *)(out + 0x10);
            if (*(uint64_t *)(out + 0x18) >> 1 <= n2)
                sk_x_001a0754(1 < *(uint64_t *)(out + 0x18), n2 + 1, 1);
            *(uint64_t *)(out + 0x10) = n2 + 1;
            sk_x_00310d98(out, out + n2 * 0x20 + 0x20);
        }
        int64_t n3 = *(int64_t *)(arr + 0x10);
        sk_x_0036b118(arr);
        if (cnt != n3)
            SoftwareBreakpoint(1, 0x47d290);
    }
    /* final: if single element, copy it out; else build an error object */
    if (*(int64_t *)(out + 0x10) == 1) {
        sk_x_00319808(out + 0x20, a1);
        sk_x_0036b118(out);
    } else {
        uint64_t u2 = sk_x_00002534(0x657be8, &sk_g_005a3c98);
        uint64_t u4 = sk_x_004a42a0(0x657bf0, 0x657be8, &sk_g_005a3c98, &sk_g_004e824c);
        sk_x_0045567c(a1, &out, u2, u4);
    }
}

/* FUN_0047d358 @ 0x0047d358   (est. sk_r28_cap_capture)
 * Ghidra: void FUN_0047d358(void)
 * Captures a capability/context: reads two words from self, refs them, builds
 * an error context object (0x30 bytes, kind 7), records a tag word, and
 * either commits to a report frame (0x90 bytes) or tears down. Confidence: low.
 * Notes: unaff_x20/x21 = self/flag; FUN_0036a940 alloc; DAT_00687d10 label. */
void sk_r28_0047d358(void)
{
    uint64_t self = 0;                 /* unaff_x20 */
    int64_t unaff_x21 = 0;             /* unaff_x21: commit flag */
    uint64_t frame[16] = {0};
    uint8_t rep[0x90] = {0};
    uint64_t slot = 0;
    uint64_t u2 = sk_x_00353cfc();
    uint64_t w1 = *(uint64_t *)(self + 0x18);
    uint64_t w0 = *(uint64_t *)(self + 0x10);
    sk_x_0036b270(w1);
    sk_x_00493354(w0);
    sk_pair_t p0 = sk_x_00002534(&sk_g_00657d88, &sk_g_005a4b78);
    uint64_t v = sk_x_004abdc4(p0.lo, p0.hi, p0.lo);
    sk_x_004ab288(v, 0x6728f0);
    sk_x_001f0130();
    sk_x_00002534(0x64e078, &sk_g_005a4b80);
    sk_pair_t p1 = sk_x_00002534(&sk_g_00657d90, &sk_g_005a4b88);
    sk_x_004a35b8();
    sk_pair_t p2 = sk_x_0035060c();
    sk_x_001f0130(p2.lo, p2.hi, p1.lo);
    uint64_t h = sk_x_0001a1c8();
    sk_x_00002534(&sk_g_00657da0, &sk_g_005a4b90);
    sk_pair_t p3 = sk_x_001f0130();
    sk_x_0035060c(p3.lo, p3.hi, 0x677880);
    sk_x_001f0130();
    sk_x_0036b118(h);
    uint64_t f1 = w1, f2 = w1;
    uint8_t stack[0xe0];
    sk_x_004a363c(&f1, frame);
    sk_x_004a364c(&f2);
    sk_x_00117cc4(stack, &f1, 0xe0);
    uint64_t w = *(uint64_t *)(self + 0x10);
    if ((((uint32_t)(w >> 0x3b) & 0x1e) | (uint32_t)w >> 2 & 1) == 0xe) {
        /* zero local_2b8/local_2b0 */
    }
    sk_x_00473244(w);
    if (unaff_x21 == 0) {
        frame[0] = 0x687d10;
        uint8_t b = sk_x_004934a8(frame, w);
        sk_x_0036b118(frame[0]);
        uint8_t tag = b & 0xfd;
        uint64_t n;
        sk_x_003a261c(slot);
        n = *(uint64_t *)(slot + 0x10);
        if (*(uint64_t *)(slot + 0x18) >> 1 <= n) {
            sk_x_000ec004();
            slot = sk_x_00499158();
        }
        *(uint64_t *)(slot + 0x10) = n + 1;
        *(uint64_t *)(slot + n * 8 + 0x20) = 0x1c00000000000000;
        sk_x_00474fe8(rep);
        sk_x_0036b118();
        sk_x_004a364c(stack);
        sk_x_00117cc4(rep, rep, 0x90);
    } else {
        sk_x_0036b118();
        sk_x_004a364c(stack);
    }
    sk_x_00353d14(u2);
}
