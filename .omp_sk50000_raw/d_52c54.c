
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00052c54(void)

{
  ushort *puVar1;
  ushort *puVar2;
  byte bVar3;
  uint3 uVar4;
  ushort uVar5;
  ushort uVar6;
  ushort uVar7;
  code *pcVar8;
  uint uVar9;
  uint uVar10;
  uint uVar11;
  ushort *puVar12;
  long lVar13;
  long lVar14;
  ulong *puVar15;
  ulong uVar16;
  long lVar17;
  uint uVar18;
  ulong uVar19;
  ushort *puVar20;
  ulong uVar21;
  
  uVar9 = FUN_000552a4();
  uVar10 = FUN_00055780();
  uVar11 = FUN_00055858();
  puVar12 = (ushort *)FUN_0005acac(0x6aff18,2,4);
  lVar13 = FUN_0005acac(0x6af8d8,2,5);
  if ((*(byte *)(lVar13 + 0x630) & 1) != 0) {
    return;
  }
  while( true ) {
    if (puVar12 == (ushort *)0xffffffffffffffff) {
      if (*(char *)(lVar13 + 0x278) != '\0') {
        *(undefined1 *)(lVar13 + 0x279) = 0;
                    /* WARNING: Subroutine does not return */
        FUN_004afae4(s_cna__p__expected_state__d__was___005bbd35);
      }
      if (*(char *)(lVar13 + 0x27a) == '\x01') {
                    /* WARNING: Subroutine does not return */
        FUN_004afae4(s_non_contiguous_cnodes_found_at___005bbbc5);
      }
      uVar21 = *(ulong *)(lVar13 + 0x240);
      if (*(ulong *)(lVar13 + 0x238) == uVar21) {
        FUN_004b5e78();
      }
      else {
        uVar19 = *(ulong *)(lVar13 + 0x250);
        if (*(ulong *)(lVar13 + 0x238) == *(ulong *)(lVar13 + 0x248)) {
          if (uVar21 < uVar19) {
                    /* WARNING: Subroutine does not return */
            FUN_004afae4(s_cnode_range____zx____zx__must_co_005bbc81);
          }
          if (0x3ff < uVar21 - uVar19) {
            *(ulong *)(lVar13 + 600) = uVar19;
            lVar14 = (uVar21 - uVar19 & 0xffffffffffffffc0) + uVar19;
            lVar17 = lVar14 + -0x400;
            *(long *)(lVar13 + 0x260) = lVar17;
            *(long *)(lVar13 + 0x268) = lVar17;
            *(long *)(lVar13 + 0x270) = lVar14;
            *(undefined1 *)(lVar13 + 0x278) = 1;
            *(undefined1 *)(lVar13 + 0x630) = 1;
            return;
          }
                    /* WARNING: Subroutine does not return */
          FUN_004afae4(s_expected__zd_free_slots__only__z_005bbcc3);
        }
      }
                    /* WARNING: Subroutine does not return */
      FUN_004afae4(s_cnode_range____zx____zx__and_boo_005bbc29);
    }
    if (puVar12 + 0x2000 < puVar12) break;
    if ((((byte)puVar12[1] != 0 || *(byte *)((long)puVar12 + 3) != 0) || *puVar12 != 0) ||
        (((byte)puVar12[3] != 0 || *(byte *)((long)puVar12 + 7) != 0) || puVar12[2] != 0)) {
      uVar21 = 0;
      puVar20 = puVar12 + 0x10;
      do {
        if ((puVar20 != (ushort *)0x0) &&
           (((puVar20 < puVar12 + 0x10 || (puVar12 + 0x2000 < puVar20 + 0x10)) ||
            (puVar20 + 0x10 < puVar20)))) goto LAB_000532f0;
        uVar18 = (uint)*(byte *)((long)puVar20 + 7);
        uVar19 = (ulong)(byte)puVar20[1] << 0x10 | (ulong)*(byte *)((long)puVar20 + 3) << 0x18 |
                 (ulong)*puVar20 | (ulong)*(uint3 *)(puVar20 + 2) << 0x20;
        if ((*(ulong *)(lVar13 + 0x248) == 0) && (*(long *)(lVar13 + 0x250) == 0)) {
          *(ulong *)(lVar13 + 0x248) = uVar19;
LAB_00052de4:
          *(ulong *)(lVar13 + 0x250) = uVar19 + 0x40;
        }
        else {
          if (uVar19 < *(ulong *)(lVar13 + 0x248)) {
            *(ulong *)(lVar13 + 0x248) = uVar19;
          }
          if (*(ulong *)(lVar13 + 0x250) < uVar19 + 0x40) goto LAB_00052de4;
        }
        puVar1 = puVar20 + 0x10;
        if (uVar18 < 0x12) {
          switch(uVar18) {
          case 1:
          case 2:
          case 3:
          case 5:
          case 8:
          case 9:
          case 0xf:
          case 0x10:
            goto switchD_00052e18_caseD_1;
          case 4:
            if (puVar20 <= puVar1) {
              uVar7 = puVar20[8];
              bVar3 = *(byte *)((long)puVar20 + 0x13);
              uVar5 = puVar20[9];
              uVar6 = puVar20[10];
              lVar14 = FUN_0005acac(0x6af8d8,2,5);
              if (lVar14 + 0x238U <= lVar14 + 0x288U) {
                if (*(char *)(lVar14 + 0x278) != '\0') {
                  *(undefined1 *)(lVar14 + 0x279) = 0;
                    /* WARNING: Subroutine does not return */
                  FUN_004afae4(s_cna__p__expected_state__d__was___005bbd35);
                }
                uVar19 = ((ulong)(byte)uVar5 << 0x10 | (ulong)bVar3 << 0x18 | (ulong)uVar7) << 0xc |
                         (ulong)(byte)uVar6 << 0x2c;
                if (*(long *)(lVar14 + 0x238) == 0 && *(ulong *)(lVar14 + 0x240) == 0) {
                  *(ulong *)(lVar14 + 0x238) = uVar19;
                  *(ulong *)(lVar14 + 0x240) = uVar19 + 0x4000;
                }
                else if (*(ulong *)(lVar14 + 0x240) == uVar19) {
                  *(ulong *)(lVar14 + 0x240) = uVar19 + 0x4000;
                }
                else if ((*(byte *)(lVar14 + 0x27a) & 1) == 0) {
                  *(undefined1 *)(lVar14 + 0x27a) = 1;
                  *(ulong *)(lVar14 + 0x280) = uVar19;
                }
                goto LAB_00052ff4;
              }
            }
            goto LAB_000532f0;
          case 6:
            if (puVar1 < puVar20) goto LAB_000532f0;
            lVar14 = FUN_0005acac(0x6af8d8,2,5);
            *(ulong *)(lVar14 + 0x288) = uVar19;
            break;
          case 7:
            if (puVar1 < puVar20) goto LAB_000532f0;
            lVar14 = FUN_0005acac(0x6af8d8,2,5);
            *(ulong *)(lVar14 + 0x290) = uVar19;
            break;
          case 10:
            if (puVar1 < puVar20) goto LAB_000532f0;
            lVar14 = FUN_0005acac(0x6af8d8,2,5);
            puVar15 = (ulong *)(lVar14 + 0x38U) + _DAT_006aff20 * 2;
            if (((puVar15 < (ulong *)(lVar14 + 0x38U)) || ((ulong *)(lVar14 + 0x238U) < puVar15 + 2)
                ) || (puVar15 + 2 < puVar15)) goto LAB_000532f0;
            uVar7 = puVar20[8];
            *puVar15 = uVar19;
            *(ushort *)(puVar15 + 1) = CONCAT11(*(byte *)((long)puVar20 + 0x11),(byte)uVar7);
            _DAT_006aff20 = _DAT_006aff20 + 1;
            break;
          case 0xb:
            if (puVar1 < puVar20) goto LAB_000532f0;
            lVar14 = FUN_0005acac(0x6af8d8,2,5);
            *(ulong *)(lVar14 + 0x2a0) = uVar19;
            break;
          case 0xc:
            *(ulong *)(lVar13 + 0x28) = uVar19;
            *(undefined8 *)(lVar13 + 0x30) = 0;
            break;
          case 0xd:
            uVar16 = ((ulong)(byte)puVar20[9] << 0x10 |
                      (ulong)*(byte *)((long)puVar20 + 0x13) << 0x18 | (ulong)puVar20[8]) << 0xc |
                     (ulong)(byte)puVar20[10] << 0x2c;
            if (*(ulong *)(lVar13 + 0x20) <= uVar16) {
              *(ulong *)(lVar13 + 0x18) = uVar19;
              *(ulong *)(lVar13 + 0x20) = uVar16;
            }
            break;
          case 0xe:
            uVar16 = ((ulong)(byte)puVar20[9] << 0x10 |
                      (ulong)*(byte *)((long)puVar20 + 0x13) << 0x18 | (ulong)puVar20[8]) << 0xc |
                     (ulong)(byte)puVar20[10] << 0x2c;
            if (*(ulong *)(lVar13 + 0x10) <= uVar16) {
              *(ulong *)(lVar13 + 8) = uVar19;
              *(ulong *)(lVar13 + 0x10) = uVar16;
            }
            break;
          case 0x11:
            if (puVar1 < puVar20) goto LAB_000532f0;
LAB_00052ff4:
            FUN_00053858(puVar20);
          }
        }
        else {
switchD_00052e18_caseD_1:
          if (uVar9 == uVar18) {
            if (puVar1 < puVar20) goto LAB_000532f0;
            lVar14 = FUN_0005acac(0x6af8d8,2,5);
            *(ulong *)(lVar14 + 0x2a8) = uVar19;
          }
          else if (uVar10 == uVar18) {
            if (puVar1 < puVar20) goto LAB_000532f0;
            lVar14 = FUN_0005acac(0x6af8d8,2,5);
            *(ulong *)(lVar14 + 0x298) = uVar19;
          }
          else if (uVar11 == uVar18) {
            if (puVar1 < puVar20) goto LAB_000532f0;
            FUN_00055948(puVar20);
            puVar15 = (ulong *)FUN_00053598();
            if (puVar15 + 1 < puVar15) goto LAB_000532f0;
            *puVar15 = (ulong)(byte)puVar20[1] << 0x10 | (ulong)*(byte *)((long)puVar20 + 3) << 0x18
                       | (ulong)*puVar20 | (ulong)*(uint3 *)(puVar20 + 2) << 0x20;
          }
          else {
            if (uVar18 != 5) goto switchD_00052e18_caseD_0;
            if (puVar1 < puVar20) goto LAB_000532f0;
            lVar14 = FUN_0005acac(0x6af8d8,2,5);
            lVar17 = *(long *)(lVar14 + 0x628);
            puVar15 = (ulong *)(lVar14 + 0x2c8U) + lVar17 * 3;
            if (puVar15 < (ulong *)(lVar14 + 0x2c8U)) goto LAB_000532f0;
            if (((ulong *)(lVar14 + 0x628U) < puVar15 + 3) || (puVar15 + 3 < puVar15))
            goto LAB_000532f0;
            uVar4 = *(uint3 *)(puVar20 + 8);
            *puVar15 = uVar19;
            puVar15[1] = (ulong)uVar4;
            puVar2 = puVar20 + 0xc;
            if ((puVar1 < puVar2) || (puVar2 < puVar20)) goto LAB_000532f0;
            *(byte *)(puVar15 + 2) = (byte)*puVar2 & 1;
            *(ulong *)(lVar14 + 0x628U) = lVar17 + 1;
          }
        }
switchD_00052e18_caseD_0:
        uVar21 = uVar21 + 1;
        puVar20 = puVar20 + 0x10;
      } while (uVar21 < ((ulong)(byte)puVar12[1] << 0x10 |
                         (ulong)*(byte *)((long)puVar12 + 3) << 0x18 | (ulong)*puVar12 |
                        (ulong)((uint)(byte)puVar12[3] << 0x10 |
                                (uint)*(byte *)((long)puVar12 + 7) << 0x18 | (uint)puVar12[2]) <<
                        0x20));
    }
    puVar12 = (ushort *)
              ((ulong)(byte)puVar12[5] << 0x10 | (ulong)*(byte *)((long)puVar12 + 0xb) << 0x18 |
               (ulong)puVar12[4] |
              (ulong)((uint)(byte)puVar12[7] << 0x10 | (uint)*(byte *)((long)puVar12 + 0xf) << 0x18
                     | (uint)puVar12[6]) << 0x20);
  }
LAB_000532f0:
                    /* WARNING: Does not return */
  pcVar8 = (code *)SoftwareBreakpoint(0x5519,0x532f4);
  (*pcVar8)();
}

