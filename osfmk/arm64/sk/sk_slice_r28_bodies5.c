
/* FUN_004811b4 @ 0x004811b4   (est. sk_r28_prop_test_j)
 * Ghidra: bool FUN_004811b4(int)
 * True if the general category (FUN_002bc5bc) is 0x16 (number) or the arg
 * equals 9. Confidence: medium. */
bool sk_r28_004811b4(int a1)
{
    char c = (char)sk_x_002bc5bc();
    return c == 0x16 || a1 == 9;
}

/* FUN_004811e8 @ 0x004811e8   (est. sk_r28_string_advance)
 * Ghidra: void FUN_004811e8(ulong,ulong)
 * String iterator advance: moves the cursor (self+0x18/+0x20) forward by one
 * scalar, handling the direct / table-indirect storage forms, and updates the
 * position + completion flag. Traps on invalid advance. Confidence: low.
 * Notes: unaff_x20 = self; SoftwareBreakpoint(1,0x481320). */
void sk_r28_004811e8(uint64_t a1, uint64_t a2)
{
    if (*(char *)(self + 0x28) == 0x01)
        SoftwareBreakpoint(1, 0x481320);
    uint64_t cur = *(uint64_t *)(self + 0x18);
    *(uint64_t *)(self + 8) = *(uint64_t *)(self + 0x20);
    *(uint8_t *)(self + 0x10) = 0;
    uint64_t npos;
    if (cur >> 0xe == *(uint64_t *)(self + 0x20) >> 0xe) {
        npos = 0; cur = 0;
        *(uint64_t *)(self + 0x18) = cur;
        *(uint64_t *)(self + 0x20) = npos;
        *(uint8_t *)(self + 0x28) = 1;
        return;
    }
    if (*(char *)(self + 0x29) == 0x01) {
        sk_x_003504a0();
        npos = sk_x_002ab130();
        if ((int64_t)npos < 0x4000)
            SoftwareBreakpoint(1, 0x4812f8);
        int64_t base;
        if ((a2 >> 0x3c & 1) == 0) {
            if ((a2 >> 0x3d & 1) == 0) {
                if ((a1 >> 0x3c & 1) == 0) { sk_x_00084180(); base = sk_x_002a9ba8(); }
                else base = (a2 & 0xfffffffffffffff) + 0x20;
                int64_t end;
                sk_x_004ab054(base, npos);
                end = x8;
                if ((int64_t)npos != 0x4000 && ((int64_t)(npos - 0x4000) < 0) == 0)
                    goto skip;
                do { sk_x_00356930(); end = x8; } while (0);
skip:
                npos = sk_x_004abf00(end);
            } else {
                sk_x_004ab054(&stack);
                npos = sk_x_004abf00(x8);
            }
        } else {
            sk_x_003504a0();
            npos = sk_x_002ae098();
        }
    } else {
        sk_x_003504a0();
        npos = sk_x_0029c058();
    }
    if (npos >> 0xe < cur >> 0xe)
        SoftwareBreakpoint(1, 0x4812f4);
    *(uint64_t *)(self + 0x18) = cur;
    *(uint64_t *)(self + 0x20) = npos;
    *(uint8_t *)(self + 0x28) = 0;
}

/* FUN_00481320 @ 0x00481320   (est. sk_r28_mask_bits)
 * Ghidra: ulong FUN_00481320(uint)
 * Packs a 32-bit arg's low byte plus two flag bits into a 64-bit value: if
 * (arg & 0xff00) == 0x100 sets bit 53, else 0; ORs in bit 54 from (arg>>16)&1
 * and bit 55 from (arg>>24)&1. Confidence: high (pure bit field combiner). */
uint64_t sk_r28_00481320(uint32_t a1)
{
    uint64_t v = 0x20000000000000;
    if ((a1 & 0xff00) != 0x100)
        v = 0;
    return v | (a1 & 0xff) | (uint64_t)((a1 & 0x10000) >> 0x10) << 0x36 |
           (uint64_t)((a1 & 0x1000000) >> 0x18) << 0x37;
}

/* FUN_00481354 @ 0x00481354   (est. sk_r28_shift_mask)
 * Ghidra: undefined4 FUN_00481354(ulong)
 * Selects a byte from the constant 0x304020100 by (arg & 7)<<3, clamped to 4
 * when arg > 4. Confidence: high. */
uint32_t sk_r28_00481354(uint64_t a1)
{
    uint32_t v = (uint32_t)(0x304020100 >> ((a1 & 7) << 3));
    if (4 < a1) v = 4;
    return v;
}

/* FUN_00481378 @ 0x00481378   (est. sk_r28_table_get)
 * Ghidra: undefined8 FUN_00481378(ulong)
 * Returns table entry DAT_005a5e90[(arg & 0xff) * 8]. Confidence: high. */
uint64_t sk_r28_00481378(uint64_t a1)
{
    return *(uint64_t *)(&sk_g_005a5e90 + (a1 & 0xff) * 8);
}

/* FUN_00481394 @ 0x00481394   (est. sk_r28_table_wait)
 * Ghidra: void FUN_00481394(ulong)
 * Hashes the table entry for (arg & 0xff) then waits/syncs on it.
 * Confidence: medium. Notes: FUN_001a84f4/001a8564 hash pair. */
void sk_r28_00481394(uint64_t a1)
{
    uint8_t st[72];
    sk_x_001a84f4(st, 0);
    sk_x_002298d4(*(uint64_t *)(&sk_g_005a5e90 + (a1 & 0xff) * 8));
    sk_x_001a8564();
}

/* FUN_004813f0 @ 0x004813f0   (est. sk_r28_wait_byte)
 * Ghidra: void FUN_004813f0(undefined8,undefined1)
 * Waits/syncs on the byte arg via the vspace sync helper. Confidence: medium. */
void sk_r28_004813f0(uint64_t a1, uint8_t a2)
{
    sk_x_002298d4(a2);
}

/* FUN_00481418 @ 0x00481418   (est. sk_r28_table_wait2)
 * Ghidra: void FUN_00481418(undefined8,ulong)
 * Waits/syncs on the table entry DAT_005a5e90[(arg & 0xff)*8].
 * Confidence: medium. */
void sk_r28_00481418(uint64_t a1, uint64_t a2)
{
    sk_x_002298d4(*(uint64_t *)(&sk_g_005a5e90 + (a2 & 0xff) * 8));
}

/* FUN_0048144c @ 0x0048144c   (est. sk_r28_wait2)
 * Ghidra: void FUN_0048144c(undefined8,undefined8)
 * Waits/syncs on arg2. Confidence: medium. */
void sk_r28_0048144c(uint64_t a1, uint64_t a2)
{
    sk_x_002298d4(a2);
}

/* FUN_0048147c @ 0x0048147c   (est. sk_r28_wait3)
 * Ghidra: void FUN_0048147c(undefined8,undefined8)
 * Hash-wrap: hashes a 72-byte frame then waits/syncs on arg2.
 * Confidence: medium. */
void sk_r28_0048147c(uint64_t a1, uint64_t a2)
{
    uint8_t st[72];
    sk_x_001a84f4(st);
    sk_x_002298d4(a2);
    sk_x_001a8564();
}

/* FUN_004814c0 @ 0x004814c0   (est. sk_r28_table_wait3)
 * Ghidra: void FUN_004814c0(undefined8,ulong)
 * Hash-wrap + wait/sync on table entry DAT_005a5e90[(arg & 0xff)*8].
 * Confidence: medium. */
void sk_r28_004814c0(uint64_t a1, uint64_t a2)
{
    uint8_t st[72];
    sk_x_001a84f4(st);
    sk_x_002298d4(*(uint64_t *)(&sk_g_005a5e90 + (a2 & 0xff) * 8));
    sk_x_001a8564();
}

/* FUN_00481510 @ 0x00481510   (est. sk_r28_wait4)
 * Ghidra: void FUN_00481510(undefined8,undefined1)
 * Hash-wrap + wait/sync on the byte arg. Confidence: medium. */
void sk_r28_00481510(uint64_t a1, uint8_t a2)
{
    uint8_t st[72];
    sk_x_001a84f4(st);
    sk_x_002298d4(a2);
    sk_x_001a8564();
}

/* FUN_00481554 @ 0x00481554   (est. sk_r28_store_byte)
 * Ghidra: void FUN_00481554(void)
 * Computes the shift-mask byte (FUN_00481354) and stores it through unaff_x19.
 * Confidence: medium. Notes: unaff_x19 = out slot. */
void sk_r28_00481554(void)
{
    sk_x_00351124();
    uint8_t v = (uint8_t)sk_r28_00481354(0);
    *x19 = v;
}

/* FUN_00481580 @ 0x00481580   (est. sk_r28_store_get)
 * Ghidra: void FUN_00481580(undefined8 *)
 * Reads the table entry for the byte at unaff_x20 and stores it into *out.
 * Confidence: medium. Notes: unaff_x20 = index byte. */
void sk_r28_00481580(uint64_t *out)
{
    uint64_t v = sk_r28_00481378(*x20);
    *out = v;
}

/* FUN_004815ac @ 0x004815ac   (est. sk_r28_index_calc)
 * Ghidra: long FUN_004815ac(ulong)
 * Computes an index: adds bits 19-26 and 27-34 of arg; returns -1 if bits
 * 18-26 equal 1, else the sum. Confidence: high (pure index computation). */
int64_t sk_r28_004815ac(uint64_t a1)
{
    int64_t v = (int64_t)((a1 >> 0x13 & 0xff) + (a1 >> 0x1b & 0xff));
    if ((a1 >> 0x12 & 0x1ff) == 1)
        v = -1;
    return v;
}

/* FUN_004815cc @ 0x004815cc   (est. sk_r28_lz_mask)
 * Ghidra: ulong FUN_004815cc(ulong)
 * Selects a byte from the packed constant 0x300020100 by bits 35-37 of arg,
 * but only if that 3-bit field is a valid index in {0..4}; otherwise traps.
 * Confidence: high. Notes: SoftwareBreakpoint(1,0x481600). */
uint64_t sk_r28_004815cc(uint64_t a1)
{
    uint64_t idx = a1 >> 0x23 & 7;
    if ((idx < 5) && ((0x17U >> idx & 1) != 0))
        return 0x300020100 >> (idx << 3);
    SoftwareBreakpoint(1, 0x481600);
    return 0;
}
