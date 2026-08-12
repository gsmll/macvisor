
/* FUN_0047f1b4 @ 0x0047f1b4   (est. sk_r28_prop_test_b)
 * Ghidra: void FUN_0047f1b4(undefined8,undefined8)
 * Calls the general-category getter FUN_002bc5bc and forwards its result to a
 * shared test helper. Confidence: medium. */
void sk_r28_0047f1b4(uint64_t a1, uint64_t a2)
{
    uint64_t u = sk_x_002bc5bc();
    sk_x_000abbdc(u, a2);
}

/* FUN_0047f1e0 @ 0x0047f1e0   (est. sk_r28_prop_test_ci)
 * Ghidra: undefined8 FUN_0047f1e0(undefined8)
 * Tests property bit 18 (FUN_002bc058); if set returns the result of the
 * scalar case-fold helper FUN_002bbf24, else 0. Confidence: medium. */
uint64_t sk_r28_0047f1e0(uint64_t a1)
{
    uint64_t u = sk_x_002bc058();
    if ((u & 1) != 0)
        return sk_x_002bbf24(a1);
    return 0;
}

/* FUN_0047f448 @ 0x0047f448   (est. sk_r28_prop_test_d)
 * Ghidra: bool FUN_0047f448(undefined8)
 * If property bit 7 (FUN_002bbf08) is set returns true; else runs a
 * decompose pass and returns the negated carry flag. Confidence: medium. */
bool sk_r28_0047f448(uint64_t a1)
{
    uint64_t u = sk_x_002bbf08();
    if ((u & 1) == 0) {
        sk_x_002bd724(a1);
        sk_x_0046511c();
        return !ZR;
    }
    return true;
}

/* FUN_0047f488 @ 0x0047f488   (est. sk_r28_prop_test_e)
 * Ghidra: bool FUN_0047f488(undefined8)
 * True unless property bit 37 (FUN_002bc234) is clear AND the general
 * category is one of 0x19/0x1b/0x1d (punctuation classes). Confidence: medium. */
bool sk_r28_0047f488(uint64_t a1)
{
    uint64_t u = sk_x_002bc234();
    if ((u & 1) == 0) {
        char c = (char)sk_x_002bc5bc(a1);
        if (c != 0x19) {
            c = (char)sk_x_002bc5bc(a1);
            if (c != 0x1b) {
                c = (char)sk_x_002bc5bc(a1);
                return c != 0x1d;
            }
        }
    }
    return false;
}

/* FUN_0047f4f4 @ 0x0047f4f4   (est. sk_r28_prop_test_f)
 * Ghidra: bool FUN_0047f4f4(void)
 * Returns whether the general category is not 0x19. Confidence: medium. */
bool sk_r28_0047f4f4(void)
{
    return (char)sk_x_002bc5bc() != 0x19;
}

/* FUN_0047f4f8 @ 0x0047f4f8   (est. sk_r28_prop_test_f2)
 * Ghidra: bool FUN_0047f4f8(void)
 * Identical to 0047f4f4. Confidence: medium. */
bool sk_r28_0047f4f8(void)
{
    return (char)sk_x_002bc5bc() != 0x19;
}

/* FUN_0047f518 @ 0x0047f518   (est. sk_r28_prop_test_g)
 * Ghidra: undefined8 FUN_0047f518(undefined8)
 * If property bit 7 clear, runs a decompose pass and, if both flags set and
 * property bit 24 (FUN_002bc100) clear, returns the scalar-mapping helper
 * result; otherwise returns 1. Confidence: medium. */
uint64_t sk_r28_0047f518(uint64_t a1)
{
    uint64_t u = sk_x_002bbf08();
    if ((u & 1) == 0) {
        sk_x_002bd724(a1);
        sk_x_0046511c();
        if (ZR) {
            u = sk_x_002bc100(a1);
            if ((u & 1) == 0)
                return sk_x_002bbf78(a1);
        }
    }
    return 1;
}

/* FUN_0047f580 @ 0x0047f580   (est. sk_r28_prop_ret)
 * Ghidra: undefined1 FUN_0047f580(undefined4,undefined8)
 * Reads a 32-bit word through the property iterator, runs a predicate, and
 * returns the 1-byte predicate result. Confidence: medium.
 * Notes: thunk_FUN_0024d9ac iterator; FUN_0024917c predicate. */
uint8_t sk_r28_0047f580(uint32_t a1, uint64_t a2)
{
    uint64_t it = sk_x_0024d9ac(a2);
    uint32_t w = a1;
    uint8_t out;
    sk_x_0024917c(&out, &w);
    sk_x_0036b118(it);
    return out;
}

/* FUN_0047f5d0 @ 0x0047f5d0   (est. sk_r28_err_build)
 * Ghidra: void FUN_0047f5d0(void)
 * Builds an error object: reads a message tag (DAT_00688638), allocates an
 * error context, stores the two self words, refs them and commits.
 * Confidence: medium. Notes: unaff_x19/x20 = self words. */
void sk_r28_0047f5d0(void)
{
    sk_x_003504d0();
    sk_x_00002834((uint64_t)&sk_g_00688638);
    int64_t e = sk_x_0036a940();
    *(uint64_t *)(e + 0x10) = x20;
    *(uint64_t *)(e + 0x18) = x19;
    sk_x_0036b270();
    sk_x_0006b6f4();
}

/* FUN_0047f630 @ 0x0047f630   (est. sk_r28_utf8_decode_err)
 * Ghidra: void FUN_0047f630(undefined8,undefined8,undefined8)
 * Decodes the next scalar from a UTF-8 string and appends it to a string
 * builder, handling 1/2/3-byte continuations; emits a type-conversion report
 * on the decoded scalar. Confidence: low.
 * Notes: register-heavy (unaff_x19/x21); FUN_0034b3f8 scalar accumulate. */
void sk_r28_0047f630(uint64_t a1, uint64_t a2, uint64_t a3)
{
    sk_x_0008409c();
    sk_x_003504a0(a3);
    uint64_t v = sk_x_00167404();
    if ((x19 >> 0x3c & 1) != 0) {
        sk_x_003504a0(v & 0xffffffffffff0000);
        sk_x_002a49a8();
        goto done;
    }
    if ((x19 >> 0x3d & 1) == 0) {
        int64_t base;
        if ((x21 >> 0x3c & 1) == 0) { sk_x_00084180(); base = sk_x_002a9ba8(); }
        else base = sk_x_00356364();
        sk_x_004abbb8(base + (v >> 0x10));
        if (x9 >= 0) goto done;
        sk_x_003527b8();
        switch (x16) {
        case 1:
            sk_x_00353ff4();
            break;
        case 2:
            sk_x_00352e9c();
            break;
        case 3:
            sk_x_0034c6d4();
            sk_x_004abfc8();
            break;
        }
    } else {
        sk_x_004abbb8(&stack + (v >> 0x10));
        if (x9 >= 0) goto done;
        sk_x_003527b8();
        switch (x16_00) {
        case 1: sk_x_00353ff4(); break;
        case 2: sk_x_00352e9c(); break;
        case 3: sk_x_0034c6d4(); sk_x_004abfc8(); break;
        }
    }
done:
    uint64_t it = sk_x_0024d9ac(&sk_g_005a4c30);
    uint8_t tag;
    sk_x_0024917c(&tag, &stack);
    sk_x_0036b118(it);
    if (tag == 0x01) {
        sk_x_00100efc();
        uint64_t v2 = sk_x_00167404();
        if ((x19 >> 0x3c & 1) == 0) {
            uint64_t off = v2 >> 0x10;
            int64_t base;
            if ((x19 >> 0x3d & 1) == 0) {
                if ((x21 >> 0x3c & 1) == 0) { sk_x_00084180(); base = sk_x_002a9ba8(); }
                else base = sk_x_00356364();
            } else {
                base = (int64_t)&stack;
            }
            uint8_t b = *(uint8_t *)(base + off);
            sk_x_0034b3f8(b, 0, 0);
            sk_x_004abd2c(off + x8);
        } else {
            sk_x_003504a0();
            sk_x_002a49a8();
        }
    } else {
        sk_x_00068e14();
    }
}

/* FUN_0047f808 @ 0x0047f808   (est. sk_r28_err_build2)
 * Ghidra: void FUN_0047f808(void)
 * Error-object builder variant of 0047f5d0 with tag DAT_00688690.
 * Confidence: medium. Notes: unaff_x19/x20 = self words. */
void sk_r28_0047f808(void)
{
    sk_x_003504d0();
    sk_x_00002834((uint64_t)&sk_g_00688660);
    int64_t e = sk_x_0036a940();
    *(uint64_t *)(e + 0x10) = x20;
    *(uint64_t *)(e + 0x18) = x19;
    sk_x_0036b270();
    sk_x_0006b6f4();
}

/* FUN_0047f868 @ 0x0047f868   (est. sk_r28_utf8_decode_err2)
 * Ghidra: void FUN_0047f868(undefined8,undefined8,undefined8)
 * UTF-8 scalar decode variant that builds a string from the decoded scalar,
 * handling an ASCII literal fast path. Confidence: low.
 * Notes: unaff_x30; SoftwareBreakpoint(1,0x47f944). */
void sk_r28_0047f868(uint64_t a1, uint64_t a2, uint64_t a3)
{
    sk_x_00357cb4();
    sk_x_0035056c(a3);
    sk_x_00267510();
    uint64_t v = sk_x_00417aa0();
    sk_x_003a25d4(0);
    sk_pair_t r;
    if ((v & 1) != 0) {
        sk_pair_t av = sk_x_000b4390();
        sk_x_00267510(av.lo, av.hi, 0);
        v = sk_x_001ae8a8();
        sk_x_003a25d4(0);
        sk_x_004ab11c(v & 0xff00000000);
        if (ZR)
            SoftwareBreakpoint(1, 0x47f944);
        uint64_t it = sk_x_0024d9ac(&sk_g_005a4c30);
        uint32_t w = (uint32_t)v;
        uint8_t tag;
        sk_x_0024917c(&tag, &w);
        sk_x_0036b118(it);
        if (tag == 0x01) {
            sk_pair_t av2 = sk_x_000b4390();
            v = sk_x_001b798c(av2.lo, av2.hi, 0);
            r = (sk_pair_t){ v, 0 };
        } else {
            r = sk_x_00068e14();
        }
    } else {
        r = sk_x_00068e14();
    }
    sk_x_00357c74(r.lo, r.hi, x30);
}

/* FUN_0047f944 @ 0x0047f944   (est. sk_r28_dispatch_guard)
 * Ghidra: void FUN_0047f944(undefined8 x 7)
 * Dispatch guard: invokes param_5 (a function pointer) and, if the carry
 * flag is set, applies a flag transform and advances the scalar; else
 * reports failure. Confidence: low.
 * Notes: SoftwareBreakpoint(1,0x47f9c4). */
void sk_r28_0047f944(uint64_t a1, uint64_t a2, uint64_t a3, uint64_t a4,
                     uint64_t fn, uint64_t a6, int64_t a7)
{
    sk_x_0008409c();
    (*(void (*)(void))fn)();
    sk_x_00351db4();
    if (ZR) {
        if (*(int64_t *)(a7 + 0x10) == 0)
            SoftwareBreakpoint(1, 0x47f9c4);
        sk_x_0035063c(a3, (*(uint32_t *)(a7 + *(int64_t *)(a7 + 0x10) * 4 + 0x1c) & 0x10000) == 0);
        sk_r28_0047ed40();
    } else {
        sk_x_00068e14();
    }
}

/* FUN_0047f9c4 @ 0x0047f9c4   (est. sk_r28_forward)
 * Ghidra: void FUN_0047f9c4(undefined8,undefined8,undefined8)
 * Forwarding thunk: calls the shared advance helper with (a3, a1, a2).
 * Confidence: medium. */
void sk_r28_0047f9c4(uint64_t a1, uint64_t a2, uint64_t a3)
{
    sk_x_001b798c(a3, a1, a2);
}

/* FUN_0047f9c8 @ 0x0047f9c8   (est. sk_r28_forward2)
 * Ghidra: void FUN_0047f9c8(undefined8,undefined8,undefined8)
 * Identical forwarding thunk to 0047f9c4. Confidence: medium. */
void sk_r28_0047f9c8(uint64_t a1, uint64_t a2, uint64_t a3)
{
    sk_x_001b798c(a3, a1, a2);
}

/* FUN_0047f9f0 @ 0x0047f9f0   (est. sk_r28_prop_test_h)
 * Ghidra: bool FUN_0047f9f0(void)
 * Returns whether the general category is not 0x1d. Confidence: medium. */
bool sk_r28_0047f9f0(void)
{
    return (char)sk_x_002bc5bc() != 0x1d;
}

/* FUN_0047f9f4 @ 0x0047f9f4   (est. sk_r28_prop_test_h2)
 * Ghidra: bool FUN_0047f9f4(void)
 * Identical to 0047f9f0. Confidence: medium. */
bool sk_r28_0047f9f4(void)
{
    return (char)sk_x_002bc5bc() != 0x1d;
}

/* FUN_0047fa44 @ 0x0047fa44   (est. sk_r28_err_code)
 * Ghidra: void FUN_0047fa44(long)
 * L4 error-code → Swift error-object factory: reads the error code from the
 * box at param+0x10 and maps it (0..0x25) to the matching error message
 * string and constructor, allocating an error context object and dispatching.
 * Confidence: high (strings "L4_ErrorCode*" match the error enum).
 * Notes: DAT_006884xx string table; FUN_0036a940 alloc; thunk_FUN_0036b270
 *   refcount; SoftwareBreakpoint-free. */
void sk_r28_0047fa44(int64_t box)
{
    if (*(int64_t *)(box + 0x10) == 0)
        SoftwareBreakpoint(1, 0x480160);
    sk_x_004aa734(*(uint32_t *)(box + *(int64_t *)(box + 0x10) * 4 + 0x1c));
    uint64_t (*fn)(void) = sk_r28_0047f5d0;
    if (!ZR) fn = (void*)x16;
    uint64_t tag, ctor;
    switch (x1 & 0xff) {
    case 1: ctor = 0x004aa204; tag = 0x006884d0; sk_x_004ab1fc(&sk_g_006884d0); break;
    case 2: ctor = 0x004aa204; tag = 0x00688498; break;   /* s_L4_ErrorCodePermissionInvalid */
    case 3: ctor = 0x004aa204; tag = 0x00688478; break;   /* s_L4_ErrorCodeOperationInvalid */
    case 4: ctor = 0x004aa204; tag = 0x00688458; break;   /* s_L4_ErrorCodeArgumentInvalid */
    case 5: ctor = 0x004aa204; tag = 0x00688430; break;
    case 6: ctor = 0x004aa240; tag = 0x006885f8; break;
    case 7: ctor = 0x004a3f30; tag = 0x006884d8; break;   /* s_L4_ErrorCodeSuccess */
    case 8: ctor = 0x004aa204; tag = 0x006883f8; break;   /* s_L4_ErrorCodeCapInvalid */
    case 9: ctor = 0x004aa204; tag = 0x006883d8; break;   /* s_L4_ErrorCodeTruncated */
    case 10: ctor = 0x004aa204; tag = 0x006883b8; break;  /* s_L4_ErrorCodeCanceled */
    case 11: ctor = 0x004aa204; tag = 0x00688390; break;
    case 12: ctor = 0x004aa204; tag = 0x00688368; break;
    case 13: ctor = 0x004aa240; tag = 0x006885d8; break;
    case 14: ctor = 0x004aa204; tag = 0x00688338; break;
    case 15: ctor = 0x004aa204; tag = 0x00688318; break;
    case 16: ctor = 0x004aa204; tag = 0x006882d8; break;  /* s_L4_ErrorCodeMethodInvalid */
    case 17: ctor = 0x004aa240; tag = 0x00688598; break;
    case 18: ctor = 0x004aa204; tag = 0x006882b8; break;  /* s_L4_ErrorCodeSlotInvalid */
    case 19: ctor = 0x004aa204; tag = 0x00688298; break;  /* s_L4_ErrorCodeCapInvalid */
    case 20: ctor = 0x004aa204; tag = 0x00688278; break;  /* s_L4_ErrorCodeTruncated */
    case 21: ctor = 0x004aa240; tag = 0x00688558; break;
    case 22: ctor = 0x004aa204; tag = 0x00688250; break;
    case 23: ctor = 0x004aa204; tag = 0x00688218; break;  /* s_L4_ErrorCodeSuccess */
    case 24: ctor = 0x004aa204; tag = 0x00688200; break;
    case 25: ctor = 0x004aa204; tag = 0x006881d8; break;
    case 26: ctor = 0x004aa204; tag = 0x006881b0; break;
    case 27: ctor = 0x004aa204; tag = 0x00688188; break;
    case 28: ctor = 0x004aa204; tag = 0x00688160; break;
    case 29: ctor = 0x004aa240; tag = 0x00688578; break;
    case 30: ctor = 0x004aa204; tag = 0x00688138; break;
    case 31: ctor = 0x004aa204; tag = 0x00688110; break;
    case 32: ctor = 0x004aa204; tag = 0x006880e8; break;
    case 33: ctor = 0x004aa204; tag = 0x006880c0; break;
    case 34: ctor = 0x004aa240; tag = 0x00688538; break;
    case 35: ctor = 0x004aa204; tag = 0x00688098; break;
    case 36: ctor = 0x004aa204; tag = 0x00688070; break;
    case 37: ctor = 0x004aa204; tag = 0x00688048; break;
    default: ctor = 0x004aa240; tag = 0x00688510; break;
    }
    int64_t err = sk_x_0036a940();
    *(uint8_t *)(err + 0x10) = (uint8_t)code_byte;
    (*fn)(ctor, tag);
    sk_x_00354f1c();
    sk_x_0036b118(tag);
    sk_x_00351450();
}

/* FUN_004801f8 @ 0x004801f8   (est. sk_r28_regex_err2)
 * Ghidra: void FUN_004801f8(long)
 * Regex/Unicode error-code factory: maps the error code from the box to the
 * matching property-test / TODO-report path (categories with dedicated
 * messages), else emits the "TODO: map <code>" report. Confidence: low.
 * Notes: SoftwareBreakpoint(1,0x480758); DAT_0047f2xx fn-ptr table. */
void sk_r28_004801f8(int64_t box)
{
    if (*(int64_t *)(box + 0x10) == 0)
        SoftwareBreakpoint(1, 0x480758);
    sk_x_004aa734(*(uint32_t *)(box + *(int64_t *)(box + 0x10) * 4 + 0x1c));
    uint64_t (*fn)(void) = sk_r28_0047f5d0;
    if (!ZR) fn = (void*)x16;
    uint64_t target = (uint64_t)sk_r28_0047f1e0;
    switch (x1 & 0xff) {
    case 1: target = 0x0047f220; break;
    case 2: target = 0x0047f22c; break;
    case 3: target = 0x0047f238; break;
    case 4: target = 0x0047f244; break;
    case 6: target = 0x0047f250; break;
    case 7: target = 0x0047f25c; break;
    case 8: target = 0x0047f268; break;
    case 9: target = 0x0047f274; break;
    case 10: target = 0x0047f280; break;
    case 11: target = 0x0047f28c; break;
    case 12: target = 0x0047f298; break;
    case 13: target = 0x0047f2a4; break;
    case 14: target = 0x0047f2b0; break;
    case 15: target = 0x0047f2bc; break;
    case 16: target = 0x0047f2c8; break;
    case 17: target = 0x0047f2d4; break;
    case 19: target = 0x0047f2e0; break;
    case 20: target = 0x0047f2ec; break;
    case 21: target = 0x0047f2f8; break;
    case 22: target = 0x0047f304; break;
    case 24: target = 0x0047f310; break;
    case 25: target = 0x0047f31c; break;
    case 26: target = 0x0047f328; break;
    case 28: target = 0x004aa2c4; break;
    case 30: target = 0x0047f334; break;
    case 31: target = 0x0047f340; break;
    case 32: target = 0x0047f34c; break;
    case 33: target = 0x0047f358; break;
    case 34: target = 0x0047f364; break;
    case 35: target = 0x0047f370; break;
    case 36: target = 0x0047f37c; break;
    case 37: target = 0x0047f388; break;
    case 38: target = 0x0047f394; break;
    case 39: target = 0x0047f3a0; break;
    case 48: target = 0x0047f3ac; break;
    case 49: target = 0x0047f3b8; break;
    case 51: target = 0x0047f3c4; break;
    case 52: target = 0x0047f3d0; break;
    case 53: target = 0x00480ff0; break;
    case 54: target = 0x0047f3dc; break;
    case 55: target = 0x0047f3e8; break;
    case 56: target = 0x0047f3f4; break;
    case 57: target = 0x0047f400; break;
    case 58: target = 0x0047f40c; break;
    case 59: target = 0x0047f418; break;
    case 60: target = 0x0047f424; break;
    case 61: target = 0x0047f430; break;
    case 62: target = 0x0047f43c; break;
    case 5:
    case 18:
    case 23:
    case 27:
    case 29:
    case 40:
    case 41:
    case 42:
    case 43:
    case 44:
    case 45:
    case 46:
    case 47:
    case 50:
        sk_x_00100c04((uint64_t)sk_r28_0047f1e0);
        sk_x_002a4ab4(0x11);
        sk_pair_t av = sk_x_002acbb8(0x616d203a4f444f54, 0xef20706f72702070);
        sk_x_000f4a9c(av.lo, av.hi, 0x685848);
        sk_x_00205844(&tag, &outbox);
        sk_x_004ab6b8(outbox.lo, outbox.hi);
        sk_x_004ab6ac(outbox);
        goto emit;
    case 63:
    case 64:
    case 65:
    case 66:
        sk_x_00100c04((uint64_t)sk_r28_0047f1e0);
        sk_x_002a4ab4(0x16);
        sk_x_004ac348((uint64_t)"s_Unicode_deprecated__005e2ed0");
        sk_pair_t av2 = sk_x_002acbb8();
        sk_x_000f4a9c(av2.lo, av2.hi, 0x685848);
        sk_x_00205844(&tag, &outbox);
        sk_x_004ab6b8(outbox.lo, outbox.hi);
        sk_x_004ab6ac(outbox);
emit:
        sk_x_0044f818();
        sk_x_004aa370();
        sk_x_004aaf9c();
        sk_x_004abe68();
        return;
    default:
        break;
    }
    (*fn)(target, 0);
}

/* FUN_00480864 @ 0x00480864   (est. sk_r28_regex_kind)
 * Ghidra: void FUN_00480864(long,ulong)
 * Regex kind lookup: reads the kind code from the box and, when the box has
 * pending work, forwards it through the property test and error builder.
 * Confidence: medium. Notes: SoftwareBreakpoint(1,0x4808d0). */
void sk_r28_00480864(int64_t box, uint64_t a2)
{
    if (*(int64_t *)(box + 0x10) != 0) {
        uint64_t u = sk_x_004aa734(*(uint32_t *)(box + *(int64_t *)(box + 0x10) * 4 + 0x1c),
                                   *(uint64_t *)(&sk_g_006898b0 + (a2 & 0xff) * 8));
        uint64_t (*fn)(void) = sk_r28_0047f5d0;
        if (!ZR) fn = (void*)x16;
        (*fn)(u, 0);
        return;
    }
    SoftwareBreakpoint(1, 0x4808d0);
}
