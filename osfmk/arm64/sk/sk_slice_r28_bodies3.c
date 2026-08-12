
/* FUN_0047e8ec @ 0x0047e8ec   (est. sk_r28_case_fold)
 * Ghidra: undefined1 FUN_0047e8ec(uint,undefined1,ulong)
 * ASCII case-folding helper: if param_3 flag set, folds an ASCII letter
 * (uppercase<->lowercase) by the standard +/-0x20 delta; leaves param_2
 * unchanged and returns it. Confidence: medium.
 * Notes: FUN_004950f0 = scalar emit; in_CY/in_ZR = flag bits. */
uint8_t sk_r28_0047e8ec(uint32_t a1, uint8_t a2, uint64_t a3)
{
    sk_x_004950f0(a1);
    if ((a3 & 1) != 0) {
        sk_x_004ac7ec(a1 - 0x40);
        if (CY && !ZR) {
            if (0x19 < (a1 - 0x61 & 0xff)) return a2;
            a1 = a1 - 0x20;
        } else {
            a1 = a1 | 0x20;
        }
        sk_x_004950f0(a1);
    }
    return a2;
}

/* FUN_0047e96c @ 0x0047e96c   (est. sk_r28_range_contains)
 * Ghidra: uint FUN_0047e96c(byte,byte,uint)
 * Scans the inclusive range [param_1, param_2] and returns param_3&1 if any
 * value equals the loop counter (i.e. tests range membership of the counter);
 * traps if param_2 < param_1 or the scan overflows past 0xff. Confidence: medium.
 * Notes: SoftwareBreakpoint(1,0x47ea18) / (1,0x47ea08). */
uint32_t sk_r28_0047e96c(uint8_t a1, uint8_t a2, uint32_t a3)
{
    if (a2 < a1)
        SoftwareBreakpoint(1, 0x47ea18);
    uint64_t i = a1;
    for (;;) {
        uint32_t lo = (uint32_t)i;
        if (a2 == i) return a3 & 1;
        i = i + 1;
        if ((lo & 0xff) == 0xff)
            SoftwareBreakpoint(1, 0x47ea08);
    }
}

/* FUN_0047ea18 @ 0x0047ea18   (est. sk_r28_scalar_validate)
 * Ghidra: bool FUN_0047ea18(uint)
 * Validates that a scalar encodes/round-trips: builds the UTF-8 sequence for
 * param_1 (1/2/3-byte by magnitude), decodes it back, and reports whether the
 * original scalar equals the decoded value. Traps on invalid continuation.
 * Confidence: medium.
 * Notes: FUN_00255d4c utf8 encode; FUN_00294cb4 decode; SWBP(1,0x47eaa8). */
bool sk_r28_0047ea18(uint32_t a1)
{
    uint64_t v;
    if (a1 < 0x80) v = (uint64_t)(a1 + 1);
    else if (a1 < 0x800) v = sk_x_004abff8();
    else v = sk_x_004aacf8(((a1 & 0x3f) << 8 | a1 >> 6 & 0x3f) << 8);
    sk_pair_t au = sk_x_00255d4c(v);
    uint64_t box = au.lo;
    if (au.hi >= 0) {
        sk_x_00294cb4(&box);
        uint64_t r = sk_r28_0047edf4();
        sk_x_003a25d4(0);
        return r >> 0x20 == 0 && a1 == (uint32_t)r;
    }
    SoftwareBreakpoint(1, 0x47eaa8);
    return false;
}

/* FUN_0047ead4 @ 0x0047ead4   (est. sk_r28_range_ci)
 * Ghidra: void FUN_0047ead4(undefined8 x 9)
 * Case-insensitive scalar range test: decodes the next scalar from the UTF-8
 * stream (handling 1/2/3-byte continuations), optionally applies ASCII
 * case-fold, then tests membership in [param_5, param_6]; if the range is a
 * case pair it tries both cases via 0047ef1c/0047ee98. Commits result.
 * Confidence: low.
 * Notes: register-heavy (unaff_x24/x25/x30); SoftwareBreakpoint(1,0x47ed00). */
void sk_r28_0047ead4(uint64_t a1, uint64_t a2, uint64_t a3, uint64_t a4,
                     uint32_t a5, uint32_t a6, uint64_t a7, uint64_t a8, uint64_t a9)
{
    sk_x_00077698();
    uint32_t u11 = (uint32_t)a4;
    uint64_t u5 = a3;
    sk_x_00407ab8();
    u5 = sk_r28_0047ed40(0, (u11 ^ 0xffffffff) & 1);
    uint64_t scalar = 0;
    if ((~u11 & 1) == 0) {
        sk_x_00351300(a3);
        sk_x_00267510();
        scalar = sk_r28_0047edf4();
        sk_x_003a25d4(0);
        if (scalar >> 0x20 == 0) goto decode_done;
    } else {
        sk_x_00351300(a3);
        scalar = sk_x_00167404();
        if ((x24 >> 0x3c & 1) != 0) {
            sk_x_00351300(scalar & 0xffffffffffff0000);
            scalar = sk_x_002a49a8();
            goto decode_done;
        }
        if ((x24 >> 0x3d & 1) != 0) {
            uint8_t b = *(uint8_t *)((uint64_t)&stack0 + (scalar >> 0x10));
            scalar = (uint64_t)b; u11 = b; a9 = x25;
            if ((int8_t)b < 0) {
                sk_x_00352af0();
                switch (x16_cont) {
                case 1: goto cont1;
                case 2: goto cont2;
                case 3: goto cont3;
                }
            }
            goto decode_done;
        }
        if ((x25 >> 0x3c & 1) == 0) {
            sk_x_00350618();
            sk_x_002a9ba8();
        } else {
            sk_x_002a9ba8();
        }
        uint8_t b = *(uint8_t *)(x8 + (scalar >> 0x10));
        scalar = (uint64_t)b; u11 = b;
        if ((int8_t)b >= 0) goto decode_done;
        sk_x_00352af0();
        switch (x16) {
cont1:
        case 1:
            sk_x_00353ff4();
            scalar = (uint64_t)(x8 & 0xfffff800 | x8 & 0x3f | (u11 & 0x1f) << 6);
            break;
cont2:
        case 2:
            sk_x_00352e9c();
            u11 = (u11 & 0xf) << 0xc | (x9 & 0x3f) << 6;
            scalar = (uint64_t)(u11 | x8 & 0x3f);
            break;
cont3:
        case 3:
            sk_x_0034c6d4();
            u11 = (u11 & 0xf) << 0x12 | (x9 & 0x3f) << 0xc | (x10 & 0x3f) << 6;
            scalar = (uint64_t)(u11 | x8 & 0x3f);
            break;
        }
    }
decode_done:
    if (a6 < a5)
        SoftwareBreakpoint(1, 0x47ed00);
    u11 = (uint32_t)scalar;
    bool u4 = a5 <= u11 && a6 == u11;
    uint64_t u9;
    if (a5 <= u11 && u11 <= a6) {
        u9 = 0;
    } else {
        if ((a7 & 1) != 0) {
            uint64_t c1 = sk_x_002bc330(scalar);
            if ((c1 & 1) != 0) {
                sk_x_0029d560(scalar);
                uint64_t r = (a4 & 1) == 0 ? sk_r28_0047ef1c() : sk_r28_0047ee98();
                sk_x_003a25d4(0);
                sk_x_004ab11c(r & 0xff00000000);
                u11 = (uint32_t)r;
                bool b2 = !u4;
                u4 = (!u4 && a5 <= u11) && a6 == u11;
                if ((b2 && a5 <= u11) && u11 <= a6) { u9 = 0; goto commit; }
            }
            uint64_t c2 = sk_x_002bc34c(scalar);
            if ((c2 & 1) != 0) {
                sk_x_0029da50(scalar);
                uint64_t r = (a4 & 1) == 0 ? sk_r28_0047ef1c() : sk_r28_0047ee98();
                sk_x_003a25d4(0);
                sk_x_004ab11c(r & 0xff00000000);
                if ((!u4 && a5 <= (uint32_t)r) && (uint32_t)r <= a6) { u9 = 0; goto commit; }
            }
        }
        u5 = 0; u9 = 1;
    }
commit:
    sk_x_0007767c(u5, u9, x30);
}

/* FUN_0047ed40 @ 0x0047ed40   (est. sk_r28_scalar_next)
 * Ghidra: void FUN_0047ed40(void)
 * Advances to the next scalar in a UTF-8 string: reads the next scalar,
 * handling the direct / table-indirect / inline-string storage forms.
 * Confidence: low. Notes: register-heavy; unaff_x19/x20 = string words. */
void sk_r28_0047ed40(void)
{
    sk_x_00077888();
    if ((x1 & 1) == 0) {
        sk_x_00350624();
        sk_x_001b798c();
        return;
    }
    sk_x_00350624();
    sk_x_00167404();
    if ((x19 >> 0x3c & 1) != 0) {
        sk_x_00350624();
        sk_x_002a49a8();
        return;
    }
    if (((x19 >> 0x3d & 1) == 0) && ((x20 >> 0x3c & 1) == 0)) {
        sk_x_0007c1c4();
        sk_x_002a9ba8();
    }
    sk_x_004abcdc();
    sk_x_004abd2c(x8 + x9);
}

/* FUN_0047edf4 @ 0x0047edf4   (est. sk_r28_utf16_decode)
 * Ghidra: ulong FUN_0047edf4(void)
 * Decodes a UTF-16 scalar: reads two 16-bit words and, if they form a
 * surrogate pair, combines them; returns {scalar, 0x100000000 flag}.
 * Confidence: medium.
 * Notes: FUN_002be300/002be23c/002be12c utf16 read; FUN_00343c20 finalize. */
uint64_t sk_r28_0047edf4(void)
{
    uint8_t st[104];
    sk_x_002be300();
    sk_x_002be23c(st);
    sk_x_003a25d4(x3);
    uint64_t v1 = sk_x_002be12c();
    if ((v1 & 0xff00000000) == 0x100000000) {
        sk_x_00343c20(st);
    } else {
        uint64_t v2 = sk_x_002be12c();
        sk_x_00343c20(st);
        if ((v2 & 0xff00000000) == 0x100000000) {
            v2 = 0; v1 = 0;
            return 0x100000000;
        }
    }
    return 0x100000000;
}

/* FUN_0047ee98 @ 0x0047ee98   (est. sk_r28_utf8_decode_c)
 * Ghidra: ulong FUN_0047ee98(void)
 * Decodes the next scalar from a UTF-8 string, handling the inline-copy
 * storage form; returns {scalar, 0x100000000 flag}. Traps if the buffer is
 * exhausted. Confidence: low.
 * Notes: SoftwareBreakpoint(1,0x47ef1c); unaff_x20. */
uint64_t sk_r28_0047ee98(void)
{
    sk_x_003532b8();
    int64_t len = x8;
    if (!ZR) len = x9;
    if (len != 0) {
        sk_x_003504d0();
        sk_x_00350624(0xf);
        uint64_t v = sk_x_001b798c();
        if (v >> 0xe == (uint64_t)len * 4) {
            sk_x_0007c1c4();
            sk_x_001aea6c();
            if (x1 == 0)
                SoftwareBreakpoint(1, 0x47ef1c);
            sk_r28_0047edf4();
            sk_x_00351d18();
            sk_x_003a25d4();
            return (x20 & 0xffffffff) | 0x100000000;
        }
    }
    return 0x100000000;
}

/* FUN_0047ef1c @ 0x0047ef1c   (est. sk_r28_utf8_decode)
 * Ghidra: ulong FUN_0047ef1c(void)
 * Decodes the next scalar from a UTF-8 string, handling both inline and
 * indirect buffer storage, with continuation-byte assembly; returns
 * {scalar, 0x100000000 flag}. Confidence: low.
 * Notes: SoftwareBreakpoint(1,0x47efb8); unaff_x19/x20. */
uint64_t sk_r28_0047ef1c(void)
{
    sk_x_003532b8();
    int64_t len = x8;
    if (!ZR) len = x9;
    if (len == 0)
        return 0x100000000;
    sk_x_003504d0();
    sk_x_00350624(0xf);
    uint64_t v = sk_x_00167404();
    uint64_t r;
    if ((x19 >> 0x3c & 1) == 0) {
        v = v >> 0x10;
        int64_t base;
        if ((x19 >> 0x3d & 1) == 0) {
            if ((x20 >> 0x3c & 1) == 0) { sk_x_0007c1c4(); base = sk_x_002a9ba8(); }
            else base = sk_x_00356364();
        } else {
            sk_x_004aad94();
            base = x8_01;
        }
        uint8_t b = *(uint8_t *)(base + v);
        sk_x_0034b3f8(b);
        r = (v + x8_02) * 0x10000;
    } else {
        sk_x_00350624();
        r = sk_x_002a49a8();
    }
    if (x8_00 * 4 - (r >> 0xe) == 0) {
        sk_x_0007c1c4();
        r = sk_x_001ae8a8();
        if ((r & 0xff00000000) == 0x100000000)
            SoftwareBreakpoint(1, 0x47efb8);
        return r & 0xff00000000 | r & 0xffffffff;
    }
    return 0x100000000;
}

/* FUN_0047eff4 @ 0x0047eff4   (est. sk_r28_script_rawvalue)
 * Ghidra: undefined8 FUN_0047eff4(void)
 * Emits the "Unknown script rawValue" diagnostic: prints the message and
 * calls the rawValue getter, then returns the read scalar. Confidence: medium.
 * Notes: string s_Unknown_script_rawValue__005e2ef0; FUN_00027724 getter. */
uint64_t sk_r28_0047eff4(void)
{
    uint64_t r = sk_x_004ace08();
    sk_x_000b430c();
    sk_x_002a4ab4(0x1b);
    sk_x_003a25d4(0);
    sk_x_00086840((uint64_t)"s_Unknown_script_rawValue__005e2ef0");
    uint64_t (*fn)(void) = (void*)sk_x_00027724(0x670738);
    (*fn)(&sk_g_006775b0, 0x670738);
    sk_x_004ac0cc();
    sk_x_003a25d4(0x670738);
    sk_x_003a25d4(0);
    return r;
}

/* FUN_0047f0a8 @ 0x0047f0a8   (est. sk_r28_capture_copy)
 * Ghidra: void FUN_0047f0a8(void)
 * Copies a captured byte sequence into a fresh buffer: reads the source via
 * FUN_00357cb4, allocates a tag object (0x21 bytes, kind 7) if the source is
 * a scalar, otherwise copies the byte run into an array (growing as needed).
 * Confidence: low.
 * Notes: unaff_x19 = dest; SK_CANARY stack check; DAT_00657e20. */
void sk_r28_0047f0a8(void)
{
    sk_pair_t au = sk_x_00357cb4();
    int64_t canary = -0x2c8502b44bfffed6;
    uint8_t tag = 0;
    uint8_t *src = (uint8_t *)sk_x_004ace88(au.lo, &tag);
    uint64_t dst;
    if (src == 0) {
        uint64_t u4 = sk_x_00002534(&sk_g_00657e20, &sk_g_005a5530);
        dst = sk_x_0036a940(u4, 0x21, 7);
        *(uint64_t *)(dst + 0x18) = x_bae8;
        *(uint64_t *)(dst + 0x10) = x_beb0;
        *(uint8_t *)(dst + 0x20) = sk_r28_0047eff4(au.lo);
    } else {
        uint64_t n = (uint64_t)tag;
        if (n == 0) {
            sk_x_000a6fe0();
        } else {
            sk_x_004ac27c();
            dst = sk_x_00499468();
            do {
                uint8_t b = *src;
                uint64_t c = *(uint64_t *)(dst + 0x10);
                if (*(uint64_t *)(dst + 0x18) >> 1 <= c) {
                    uint64_t u4 = sk_x_0006b42c();
                    sk_x_00350774(u4, c + 1);
                    dst = sk_x_00499468();
                }
                *(uint64_t *)(dst + 0x10) = c + 1;
                *(uint8_t *)(dst + c + 0x20) = b;
                n = n - 1;
                src = src + 1;
            } while (n != 0);
        }
    }
    if (canary != -0x2c8502b44bfffed6)
        sk_x_0011d7e8();
    sk_x_00357c74(dst, au.hi);
}
