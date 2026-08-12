/* FUN_0047d6e0 @ 0x0047d6e0   (est. sk_r28_release_self_words)
 * Ghidra: void FUN_0047d6e0(void)
 * Releases the two self-owned words at self+0x10 and self+0x18 via the shared
 * refcount-release helper. Confidence: medium.
 * Notes: unaff_x20 = self; FUN_0036b118 = refcount release. */
void sk_r28_0047d6e0(void)
{
    uint64_t self = 0;                 /* unaff_x20 */
    sk_x_004abf50(*(uint64_t *)(self + 0x10));
    sk_x_0036b118();
    sk_x_0036b118(*(uint64_t *)(self + 0x18));
}

/* FUN_0047d70c @ 0x0047d70c   (est. sk_r28_dtor_70c)
 * Ghidra: void FUN_0047d70c(void)
 * Destructor thunk: releases the self words then runs two cleanup helpers.
 * Confidence: medium. Notes: unaff_x20 = self. */
void sk_r28_0047d70c(void)
{
    sk_r28_0047d6e0();
    sk_x_000dce50();
    sk_x_0036b6ac();
}

/* FUN_0047d710 @ 0x0047d710   (est. sk_r28_dtor_710)
 * Ghidra: void FUN_0047d710(void)
 * Destructor thunk (identical to 0047d70c). Confidence: medium. */
void sk_r28_0047d710(void)
{
    sk_r28_0047d6e0();
    sk_x_000dce50();
    sk_x_0036b6ac();
}

/* FUN_0047d73c @ 0x0047d73c   (est. sk_r28_regex_err_string)
 * Ghidra: undefined1[16] FUN_0047d73c(undefined8,undefined8,uint)
 * Builds a 16-byte Swift error/description descriptor for a regex parse
 * error kind (param_3 low byte): kind 0 → "> expected Regex<…", kind 1 →
 * a compacted tag pair; otherwise a generic failure descriptor.
 * Confidence: medium.
 * Notes: thunk_FUN_002acbb8 dispatch; string constant 0x5e2180. */
sk_pair_t sk_r28_0047d73c(uint64_t a1, uint64_t a2, uint32_t a3)
{
    sk_x_0008409c();
    if ((a3 & 0xff) == 0) {
        sk_x_00100c04();
        sk_x_002a4ab4(0x38);
        sk_x_002acbb8(0xd00000000000001e, 0x80000000005e2140);
        sk_x_004ac318();
        sk_x_00208418();
        sk_x_002acbb8();
        sk_x_003a25d4(0);
        sk_x_004ac348((uint64_t)"s_>___expected__Regex<_005e2180");
        sk_x_002acbb8();
        sk_x_0035354c();
        sk_x_00208418();
        sk_x_00465294();
        sk_x_003a25d4();
        return (sk_pair_t){ 0x273e, 0xe200000000000000 };
    }
    if ((a3 & 0xff) != 1) {
        return (sk_pair_t){ 0x80000000005e2180, 0xd000000000000034 };
    }
    sk_x_00100c04();
    sk_x_002a4ab4(0x32);
    sk_x_003a25d4(0);
    sk_x_004ab968(0x27);
    sk_x_00084180();
    sk_x_002acbb8();
    sk_x_002acbb8(0xd00000000000002f, 0x80000000005e2110);
    return (sk_pair_t){ 0x80000000005e2110, 0xd00000000000002f };
}

/* FUN_0047d8ec @ 0x0047d8ec   (est. sk_r28_regex_flag_apply)
 * Ghidra: void FUN_0047d8ec(void)
 * Applies a regex flag kind (in_w3 low byte): 0 enables a default flag;
 * 1 enables a second flag; otherwise no-op. Confidence: medium.
 * Notes: thunk_FUN_002298d4 = vspace wait/sync; in_w3 = flag byte. */
void sk_r28_0047d8ec(void)
{
    uint32_t in_w3 = 0;                /* unmodeled flag-byte register */
    uint64_t u = sk_x_00350b54();
    if ((in_w3 & 0xff) == 0) {
        sk_x_002298d4(1);
        sk_x_002298d4();
    } else if ((in_w3 & 0xff) == 1) {
        sk_x_002298d4(2);
        sk_x_003504a0(u);
        sk_x_001b9084();
        return;
    }
    sk_x_002298d4();
}

/* FUN_0047d96c @ 0x0047d96c   (est. sk_r28_regex_flag_run)
 * Ghidra: void FUN_0047d96c(void)
 * Runs a regex flag-setup pass: hashes the options, applies flags.
 * Confidence: medium. Notes: FUN_001a84f4/001a8564 hash pair. */
void sk_r28_0047d96c(void)
{
    uint8_t st[72];
    sk_x_004080b0();
    sk_x_00350548(st);
    sk_r28_0047d8ec();
    sk_x_001a8564();
}

/* FUN_0047d9e8 @ 0x0047d9e8   (est. sk_r28_str_build)
 * Ghidra: void FUN_0047d9e8(undefined8,undefined8,undefined1)
 * Packs two words + a tag byte into a string descriptor and hands it to a
 * shared string-builder helper. Confidence: medium.
 * Notes: FUN_00369efc build; tag constant DAT_005a4990. */
void sk_r28_0047d9e8(uint64_t a1, uint64_t a2, uint8_t a3)
{
    uint64_t w[2]; uint8_t b;
    w[0] = a1; w[1] = a2; b = a3;
    sk_x_00369efc(&w, 0x687498, &sk_g_005a4990);
}

/* FUN_0047da48 @ 0x0047da48   (est. sk_r28_regex_flag_run2)
 * Ghidra: void FUN_0047da48(void)
 * Regex flag-setup pass variant (hash + apply), like 0047d96c.
 * Confidence: medium. */
void sk_r28_0047da48(void)
{
    uint8_t st[72];
    sk_x_001a84f4(st);
    sk_x_00350878(st);
    sk_r28_0047d8ec();
    sk_x_001a8564();
}

/* FUN_0047dac4 @ 0x0047dac4   (est. sk_r28_prop_decode)
 * Ghidra: uint FUN_0047dac4(void)
 * Decodes a scalar-property token: parses a 0xb0-byte string view, reads its
 * kind via FUN_0049e2f0/FUN_00458af8, and classifies it (0x2d/0x5f special
 * tokens, leading-byte width decode). Returns {value, flag} packed as
 * value & 0xff | flag<<8. Confidence: low.
 * Notes: FUN_002a0cf8 string compare; DAT_005a5538; register-heavy. */
uint32_t sk_r28_0047dac4(void)
{
    bool flag_ZR = false;              /* carry/zero flag artifact */
    uint64_t x26 = 0;
    sk_pair_t p = sk_x_00463f94();
    uint8_t v[0xb0];
    sk_x_00117cc4(p.lo, p.hi, 0xb0);
    int k = sk_x_004ac210(v);
    uint8_t s1[0x99], s2[0x99], s3[0x99];
    uint32_t value = 0, flag = 0;
    if (flag_ZR) {
        uint64_t w = sk_x_0049e2f0(v);
        sk_x_00117cc4(s1, w, 0x99);
        sk_x_00117cc4(s2, w, 0x99);
        int k2 = sk_x_00458af8(s2);
        if (k2 == 4) {
            sk_x_00458b14(s2);
            sk_x_004176bc();
            value = sk_x_0034ecc8();
            if (flag_ZR) goto wide;
            if (value < 0x80) { flag = 0; goto ret; }
        } else if (k2 == 1) {
            uint32_t *p8 = (uint32_t *)sk_x_00458b14(s2);
            value = *p8;
            if (value < 0x80) { flag = 0; goto ret; }
        }
        sk_x_00117cc4(s3, s1, 0x99);
        int k3 = sk_x_00458af8(s3);
        if (k3 == 0) {
            int64_t *pl = (int64_t *)sk_x_00458b14(s3);
            if (*pl != 0xa0d || pl[1] != (int64_t)-0x1e00000000000000) {
                sk_x_0009461c();
                sk_x_004aa890();
                uint64_t c = sk_x_002a0cf8();
                if ((c & 1) == 0) {
                    sk_x_0009461c();
                    value = sk_x_002bd8f0();
                    flag = value >> 8 & 0xff;
                    goto ret;
                }
            }
        }
    } else {
        if (k == 1) {
            sk_x_0049e2f0(v);
            sk_x_004abc0c();
            value = 0;
            flag = 1;
            goto ret;
        }
        if (k == 0) {
            int64_t *pl = (int64_t *)sk_x_0049e2f0(v);
            if (*pl != 0xa0d || pl[1] != (int64_t)-0x1e00000000000000) {
                sk_x_0009461c();
                sk_x_004aa890();
                uint64_t c = sk_x_002a0cf8();
                if ((c & 1) == 0) {
                    sk_x_0009461c();
                    value = sk_x_002bd8f0();
                    flag = value >> 8 & 0xff;
                    goto ret;
                }
            }
        }
    }
wide:
    value = 0; flag = 1;
ret:
    return value & 0xff | flag << 8;
}

/* FUN_0047dc1c @ 0x0047dc1c   (est. sk_r28_identifier_scan)
 * Ghidra: void FUN_0047dc1c(undefined8,undefined8,ulong,ulong)
 * Scans an identifier/operator token stream: walks scalar-by-scalar,
 * handling `-`/`_` continuations and comparison operators, and commits the
 * result (equal/not) via the shared helper. Confidence: low.
 * Notes: register-heavy (unaff_x26/x30); FUN_00267510 scalar parse;
 *   FUN_001b798c advance; SoftwareBreakpoint-free. */
void sk_r28_0047dc1c(uint64_t a1, uint64_t a2, uint64_t a3, uint64_t a4)
{
    uint64_t x26 = 0;                  /* unaff_x26: continuation flag */
    uint64_t x30 = 0;                  /* unaff_x30: caller result slot */
    sk_x_0035193c();
    sk_pair_t av = sk_x_00077888();
    bool b3 = (a4 & 0x2000000000000000) == 0;
    uint64_t len = a3 & 0xffffffffffff;
    if (!b3) len = a4 >> 0x38 & 0xf;
    sk_x_003532b8();
    uint64_t u5 = 0xf, u6 = 0;
    bool result = false;
    do {
        if (len * 4 <= u6 >> 0xe) { result = false; goto commit; }
        sk_x_004aaa78();
        sk_x_00267510();
        sk_x_002bd9ac();
        sk_x_00464e64();
        if ((x26 & 1) == 0) {
            sk_x_004aaa78();
            sk_pair_t t = sk_x_00267510();
            int64_t t8 = t.hi;
            if (t.lo == 0x2d && t8 == (int64_t)-0x1f00000000000000) {
                sk_x_003a25d4(t8);
            } else {
                sk_x_000b44cc(t.lo, t8, 0x2d);
                sk_x_00464e64();
                if ((x26 & 1) == 0) {
                    sk_x_004aaa78();
                    t = sk_x_00267510();
                    t8 = t.hi;
                    if (t.lo == 0x5f && t8 == (int64_t)-0x1f00000000000000) {
                        sk_x_003a25d4(t8);
                    } else {
                        sk_x_000b44cc(t.lo, t8, 0x5f);
                        sk_x_00464e64();
                        if ((x26 & 1) == 0) break;
                    }
                }
            }
        }
        sk_x_004aaa78();
        u6 = sk_x_001b798c();
    } while (1);
    u6 = sk_x_001b798c();
commit:
    sk_x_00351774(result, x30);
}

/* FUN_0047dee8 @ 0x0047dee8   (est. sk_r28_err_canceled)
 * Ghidra: void FUN_0047dee8(undefined8,undefined8,long)
 * Builds a "L4ErrorCode.canceled" error object when param_3 has pending
 * work: allocates an error context (string "L4_ErrorCodeCanceled"),
 * chains it and dispatches. Traps if param_3 is empty. Confidence: medium.
 * Notes: SoftwareBreakpoint(1,0x47dfc4); DAT_00688688 string. */
void sk_r28_0047dee8(uint64_t a1, uint64_t a2, int64_t a3)
{
    uint64_t x19 = 0, x20 = 0;         /* unaff_x19/x20 = self words */
    int64_t x8 = 0;                    /* extraout_x8 */
    bool ZR = false;
    if (*(int64_t *)(a3 + 0x10) != 0) {
        sk_x_003504d0();
        sk_x_004aa734(*(uint32_t *)(a3 + x8 * 4 + 0x1c));
        uint64_t (*fn)(void) = (void*)sk_r28_0047f5d0;
        if (!ZR) fn = (void*)x16;
        sk_x_00002834((uint64_t)"s_L4_ErrorCodeCanceled_00688688");
        int64_t e = sk_x_0036a940();
        *(uint64_t *)(e + 0x10) = x20;
        *(uint64_t *)(e + 0x18) = x19;
        sk_x_0036b270();
        (*fn)((uint64_t)sk_x_004a4158, e);
        sk_x_00351a50();
        sk_x_0036b118(e);
        sk_x_0009461c();
        return;
    }
    SoftwareBreakpoint(1, 0x47dfc4);
}

/* FUN_0047dfc4 @ 0x0047dfc4   (est. sk_r28_op_dispatch2)
 * Ghidra: void FUN_0047dfc4(void)
 * Large op-dispatch switch on self kind byte (self+0x20): handles message
 * op kinds 0..0xf — error-code mapping, regex/unicode metadata builds,
 * cancellation, TODO-flag reports — constructing the matching error/context
 * object and committing it. Confidence: low.
 * Notes: heavy switch; unaff_x20 = self; thunk_FUN_0044f818 dispatch. */
void sk_r28_0047dfc4(void)
{
    uint64_t *x20 = 0;                 /* unaff_x20: self word array */
    uint64_t x16 = 0;
    sk_pair_t au = sk_x_004acb3c();
    int64_t obj = au.lo;
    if (*(int64_t *)(obj + 0x10) == 0)
        SoftwareBreakpoint(1, 0x47e59c);
    uint32_t u1 = *(uint32_t *)(obj + *(int64_t *)(obj + 0x10) * 4 + 0x1c);
    uint64_t (*fn)(void) = (void*)sk_r28_0047f5d0;
    if ((u1 & 0x10000) != 0) fn = (void*)sk_r28_0047f808;
    uint64_t w0 = x20[0], f1 = x20[1], f2 = x20[2];
    switch ((char)x20[4]) {
    case 0: /* default */
        sk_r28_0047fa44(obj);
        goto commit;
    case 1:
        sk_r28_004801f8(obj);
        sk_x_00355d6c();
        goto commit;
    case 2:
        sk_x_004ab1fc(0x687ff8);
        sk_x_0036a940();
        sk_x_004ac93c();
        fn = (void*)sk_x_004a3eac;
        break;
    case 3:
        sk_x_004ab1fc(0x687fd0);
        sk_x_0036a940();
        sk_x_004ac93c();
        fn = (void*)sk_x_004a3e68;
        break;
    case 4:
        sk_x_00350624(w0);
        sk_r28_0047dee8();
        goto commit2;
    case 5:
        sk_x_004ab1fc(0x687f58);
        sk_x_0036a940();
        sk_x_004ac93c();
        fn = (void*)sk_x_004a3d8c;
        break;
    case 6:
        sk_x_0036a940(0x687f80, 0x18, 7);
        fn = (void*)sk_x_004a3dcc;
        break;
    case 7:
        sk_x_0036a940();
        sk_x_004ac584();
        fn = (void*)sk_x_004a3c94;
        break;
    case 8:
        sk_x_004ab1fc(0x687f30);
        sk_x_0036a940();
        sk_x_004ac93c();
        fn = (void*)sk_x_004a3d60;
        break;
    case 9:
        sk_x_00002834(0x687fa8);
        sk_x_0036a940();
        fn = (void*)sk_x_004a3e20;
        break;
    case 10:
        sk_x_000b430c();
        sk_x_002a4ab4(0x13);
        sk_x_004ab650();
        sk_x_002acbb8(0xd000000000000011, 0x80000000005e2e90);
        goto commit2;
    case 11:
        sk_r28_00480864(obj, w0);
        goto commit2;
    case 12:
        sk_x_000b430c();
        sk_x_002a4ab4(0x1a);
        sk_x_004ab650();
        sk_x_004ac008((uint64_t)"s_TODO__map_PCRE_special__005e2e90");
        goto commit2;
    case 13:
        sk_x_000b430c();
        sk_x_002a4ab4(0x1a);
        sk_x_004ab650();
        sk_x_004ac008((uint64_t)"s_TODO__map_Java_special__005e2e70");
        goto commit2;
    case 14:
        sk_x_004ab6b8(0xd000000000000017);
        goto commit2;
    case 15:
        if ((f1 == 0 && x20[3] == 0) && f2 == 0 && w0 == 0) {
            f2 = 0; f1 = (uint64_t)sk_r28_0047f9c4;
        } else if (w0 == 1 && (f1 == 0 && x20[3] == 0) && f2 == 0) {
            (*fn)((uint64_t)sk_r28_0047f9f0, 0);
            goto commit2;
        } else {
            f2 = 0;
            f1 = (uint64_t)sk_r28_0047f630;
            if ((u1 & 0x10000) != 0) f1 = (uint64_t)sk_r28_0047f868;
        }
        goto commit;
    default:
        goto commit;
    }
    (*fn)((uint64_t)fn, 0);
commit:
    sk_x_00355d6c();
commit2:
    sk_x_004acb20(f1, f2, au.hi);
}

/* FUN_0047e5dc @ 0x0047e5dc   (est. sk_r28_regex_loop)
 * Ghidra: void FUN_0047e5dc(void)
 * Regex match loop: iterates the token stream, decoding scalars, and
 * compares against anchor tokens (0x2d/0x5f), a CRLF pair (0xa0d), and
 * character classes; recurses into 0047dac4/0047e96c/0047e8ec. Confidence: low.
 * Notes: SoftwareBreakpoint on overflow; unaff_w25. */
void sk_r28_0047e5dc(void)
{
    uint32_t w25 = 0;                  /* unaff_w25 */
    uint64_t x1 = 0;                   /* extraout_x1 */
    sk_pair_t au = sk_x_0008e518();
    int64_t obj = au.lo;
    uint8_t b1[360], b2[352], b3[352];
    sk_x_004ab31c(b1);
    sk_x_00117cc4();
    sk_x_004ab31c(b2);
    sk_x_00117cc4();
    int k = sk_x_0049df0c(b2);
    uint64_t res = 2;
    if (k == 3) {
        sk_x_0049df18(b2);
        sk_x_004ab430();
        sk_x_00117cc4(b3, b1, 0x160);
        int64_t l8 = sk_x_0049df18(b3);
        sk_x_0036b270(*(uint64_t *)(l8 + 8));
        for (;;) {
            sk_x_0029fb80();
            if (x1 == 0) { res = au.hi & 1; break; }
            sk_pair_t t = sk_x_004ac960();
            if (t.lo == 0xa0d && t.hi == (int64_t)-0x1e00000000000000) {
                sk_x_004a3918();
                sk_x_003a25d4();
                res = 2; break;
            }
            sk_x_003512c0();
            sk_x_004aa890();
            uint64_t c = sk_x_002a0cf8();
            if ((c & 1) != 0) { res = 2; break; }
            sk_x_003512c0();
            sk_x_004aa890();
            c = sk_x_002a0cf8();
            if ((c & 1) == 0) {
                sk_x_003512c0();
                c = sk_x_002bd848();
                if ((c & 1) != 0) {
                    sk_x_003512c0();
                    c = sk_x_0016749c();
                    if ((c & 0xff00000000) == 0x100000000)
                        SoftwareBreakpoint(1, 0x47e8e0);
                    if ((c & 0xffffff80) == 0) {
                        sk_x_003512c0();
                        c = sk_x_0016749c();
                        if ((c & 0xff00000000) == 0x100000000)
                            SoftwareBreakpoint(1, 0x47e8e4);
                        sk_x_004ac2d0();
                        sk_x_003a25d4();
                        if ((w25 & 0xffffff00) != 0)
                            SoftwareBreakpoint(1, 0x47e8dc);
                        continue;
                    }
                }
                sk_x_003a25d4();
                res = 2; break;
            }
            sk_x_003a25d4();
            w25 = 0;
        }
    } else if (k == 1) {
        res = sk_r28_0047dac4() & 1;
    } else if (k == 0) {
        sk_x_0049df18(b2);
        res = sk_r28_0047dac4() & 1;
    }
    sk_x_00350b84(res);
    sk_x_0008e500();
}
