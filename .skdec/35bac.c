
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00035bac(ulong *param_1,ulong param_2,undefined8 param_3,ulong param_4,uint param_5)

{
  ulong uVar1;
  ulong *puVar2;
  ulong uVar3;
  code *pcVar4;
  bool bVar5;
  long lVar6;
  ulong *puVar7;
  ulong *puVar8;
  ulong uVar9;
  uint uVar10;
  ulong uVar11;
  uint uVar12;
  ulong *puVar13;
  ulong *puVar14;
  ulong *puVar15;
  undefined1 auVar16 [16];
  
  uVar10 = (uint)param_3;
  if (0x3fffff < uVar10) {
    *param_1 = 0;
    param_1[1] = 0;
    uVar11 = _DAT_004bc1b0;
    param_1[3] = uRam00000000004bc1b8;
    param_1[2] = uVar11;
    goto LAB_00035e88;
  }
  uVar12 = (uint)param_2;
  if ((uVar12 & 3) == 1 || (param_2 & 3) == 0) {
    if ((param_2 & 3) == 0) {
      uVar11 = param_4 << 0x1c;
      *(undefined8 *)((long)param_1 + 0x11) = 0;
      *(undefined8 *)((long)param_1 + 9) = 0;
      if (param_5 == 0) {
        param_4 = 0;
      }
      *param_1 = param_4;
      *(char *)(param_1 + 1) = (char)param_5;
      uVar11 = (uVar10 << 6 | 1) | uVar11;
      if (param_5 == 0) {
        uVar11 = param_2;
      }
      goto LAB_00035fc8;
    }
    if ((uVar12 >> 6 & 0x3fffff) == uVar10) {
      uVar11 = param_2 >> 0x1c;
LAB_00035e80:
      *param_1 = uVar11;
      param_1[1] = 0;
      param_1[2] = 0;
      param_1[3] = 0;
      goto LAB_00035e88;
    }
    if ((param_5 & 1) == 0) goto LAB_00035e24;
    lVar6 = FUN_000347c4();
    auVar16 = FUN_00036bd4(lVar6,param_2,8,0);
    if (((auVar16._0_8_ & 0xff) != 0) ||
       (auVar16 = FUN_00036bd4(lVar6,(ulong)(uVar10 << 6 | 1) | param_4 << 0x1c,8,0),
       (auVar16._0_8_ & 0xff) != 0)) goto LAB_00035e18;
    *param_1 = param_4;
    uVar11 = lVar6 << 0x1c | 10;
    *(undefined1 *)(param_1 + 1) = 1;
LAB_00035ffc:
    *(undefined8 *)((long)param_1 + 0x11) = 0;
LAB_00035fc4:
    *(undefined8 *)((long)param_1 + 9) = 0;
LAB_00035fc8:
    param_1[3] = 0;
    param_1[4] = uVar11;
    return;
  }
  puVar13 = (ulong *)(param_2 >> 0x1c);
  if ((uVar12 & 3) == 2) {
    puVar7 = puVar13 + 8;
    if ((puVar7 < (ulong *)(param_2 >> 0x1c)) ||
       ((puVar13 != (ulong *)0x0 && ((long)puVar7 - (long)puVar13 < 0x39)))) goto LAB_00036004;
    lVar6 = 0;
    puVar2 = (ulong *)0x0;
    if (puVar13 != (ulong *)0x0) {
      puVar2 = puVar7;
    }
    do {
      puVar7 = (ulong *)((long)puVar13 + lVar6);
      if ((puVar7 < puVar13 || puVar2 < puVar7 + 1) || puVar7 + 1 < puVar7) goto LAB_00036004;
      uVar11 = *puVar7;
      if (((uint)uVar11 & 3) == 1) {
        if (((uint)uVar11 >> 6 & 0x3fffff) == uVar10) {
          uVar11 = uVar11 >> 0x1c;
          goto LAB_00035e80;
        }
      }
      else if ((uVar11 & 3) == 0) break;
      lVar6 = lVar6 + 8;
    } while (lVar6 != 0x40);
    if ((param_5 & 1) != 0) {
      uVar11 = (ulong)(uVar10 << 6 | 1) | param_4 << 0x1c;
      uVar10 = uVar12 >> 2 & 0xf;
      bVar5 = (ulong)((long)puVar2 - (long)puVar13) < 0x39;
      if (uVar10 < 8) {
        if (puVar13 != (ulong *)0x0 && bVar5) goto LAB_00036004;
        auVar16 = FUN_00036bd4(puVar13,uVar11,8,0);
        if ((auVar16._0_8_ & 0xff) == 0) {
          *param_1 = param_4;
          *(undefined1 *)(param_1 + 1) = 1;
          uVar11 = param_2 & 0xffffffffffffffc3 | (ulong)(uVar10 * 4 + 4);
          goto LAB_00035ffc;
        }
LAB_00035e18:
        *param_1 = 0;
        param_1[1] = 0;
        *(undefined1 (*) [16])(param_1 + 2) = auVar16;
        goto LAB_00035e88;
      }
      if (puVar13 != (ulong *)0x0 && bVar5) goto LAB_00036004;
      puVar7 = (ulong *)FUN_000347c4();
      puVar15 = (ulong *)0x0;
      if (puVar7 != (ulong *)0x0) {
        puVar15 = puVar7 + 8;
      }
      if (puVar15 < puVar7 + 1) goto LAB_00036004;
      lVar6 = 0;
      *puVar7 = *puVar7 & 0xffffffffffffffc3 | 0xc;
      puVar14 = puVar7;
      do {
        puVar8 = (ulong *)((long)puVar13 + lVar6);
        if ((puVar8 < puVar13 || puVar2 < puVar8 + 1) || puVar8 + 1 < puVar8) goto LAB_00036004;
        if ((*puVar8 & 3) == 1) {
          if (((puVar15 < puVar7) || (puVar7 < puVar14)) ||
             ((puVar7 != (ulong *)0x0 && ((ulong)((long)puVar15 - (long)puVar7) < 0x39))))
          goto LAB_00036004;
          puVar8 = (ulong *)FUN_00036d58(puVar7);
          bVar5 = puVar8 != (ulong *)0x0;
          puVar7 = (ulong *)0x0;
          if (bVar5) {
            puVar7 = puVar8;
          }
          puVar15 = (ulong *)0x0;
          if (bVar5) {
            puVar15 = puVar8 + 8;
          }
          puVar14 = (ulong *)0x0;
          if (bVar5) {
            puVar14 = puVar8;
          }
        }
        lVar6 = lVar6 + 8;
      } while (lVar6 != 0x40);
      FUN_0003481c(puVar13);
      if (((puVar15 < puVar7) || (puVar7 < puVar14)) ||
         ((puVar7 != (ulong *)0x0 && ((long)puVar15 - (long)puVar7 < 0x39)))) goto LAB_00036004;
      uVar9 = (ulong)puVar7 & 0xfffffffff;
      uVar1 = uVar9 + 0x40;
      if ((uVar1 < uVar9) || ((uVar9 != 0 && ((long)(uVar1 - uVar9) < 0x39)))) goto LAB_00036004;
      uVar3 = 0;
      if (uVar9 != 0) {
        uVar3 = uVar1;
      }
      if ((uVar3 < uVar9) || ((uVar9 != 0 && (uVar3 - uVar9 < 0x39)))) goto LAB_00036004;
      lVar6 = FUN_00036d58(uVar9,uVar11);
      uVar11 = (ulong)(uVar10 * 0x40 + 0x40);
      *param_1 = param_4;
      *(undefined1 *)(param_1 + 1) = 1;
      goto LAB_00035fb8;
    }
  }
  else {
    puVar7 = puVar13 + 8;
    if ((puVar7 < (ulong *)(param_2 >> 0x1c)) ||
       ((puVar13 != (ulong *)0x0 && ((long)puVar7 - (long)puVar13 < 0x39)))) {
LAB_00036004:
                    /* WARNING: Does not return */
      pcVar4 = (code *)SoftwareBreakpoint(0x5519,0x36008);
      (*pcVar4)();
    }
    puVar2 = (ulong *)0x0;
    if (puVar13 != (ulong *)0x0) {
      puVar2 = puVar7;
    }
    if ((puVar2 < puVar13) ||
       ((puVar13 != (ulong *)0x0 && ((ulong)((long)puVar2 - (long)puVar13) < 0x39))))
    goto LAB_00036004;
    auVar16 = FUN_0003652c(puVar13,param_3);
    puVar7 = auVar16._0_8_;
    if ((auVar16._8_8_ & 0xf8) == 0) {
      puVar2 = (ulong *)0x0;
      if (puVar7 != (ulong *)0x0) {
        puVar2 = puVar7 + 8;
      }
      puVar15 = puVar7 + (auVar16._8_8_ & 7);
      if (((puVar15 < puVar7) || (puVar2 < puVar15 + 1)) || (puVar15 + 1 < puVar15))
      goto LAB_00036004;
      uVar11 = *puVar15 >> 0x1c;
      if ((uVar11 != 0) && (((uint)*puVar15 >> 6 & 0x3fffff) == uVar10)) goto LAB_00035e80;
    }
    if ((param_5 & 1) != 0) {
      lVar6 = FUN_00036d58(puVar13,(ulong)(uVar10 << 6 | 1) | param_4 << 0x1c);
      uVar11 = (ulong)(uVar12 + 0x40) & 0xfffffc0;
      *param_1 = param_4;
      *(undefined1 *)(param_1 + 1) = 1;
LAB_00035fb8:
      *(undefined8 *)((long)param_1 + 0x11) = 0;
      uVar11 = uVar11 | lVar6 << 0x1c | 3;
      goto LAB_00035fc4;
    }
  }
LAB_00035e24:
  param_1[1] = 0;
  *param_1 = 0;
  param_1[3] = 0;
  param_1[2] = 0;
LAB_00035e88:
  param_1[4] = param_2;
  return;
}

