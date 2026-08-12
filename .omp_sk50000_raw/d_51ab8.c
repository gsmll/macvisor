
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00051ab8(uint *param_1,ulong param_2)

{
  uint *puVar1;
  uint *puVar2;
  uint *puVar3;
  uint *puVar4;
  uint *puVar5;
  uint uVar6;
  long lVar7;
  code *pcVar8;
  long lVar9;
  long lVar10;
  long lVar11;
  ulong *puVar12;
  ulong uVar13;
  ulong uVar14;
  ulong uVar15;
  
  lVar7 = _DAT_006ad6e0;
  if (param_2 < 0x1c) {
                    /* WARNING: Does not return */
    pcVar8 = (code *)SoftwareBreakpoint(1,0x51d3c);
    (*pcVar8)();
  }
  puVar3 = (uint *)((long)param_1 + param_2);
  puVar4 = (uint *)((long)param_1 + (ulong)param_1[1]);
  if (puVar4 == (uint *)0x0) {
    uVar14 = 0;
  }
  else if (((puVar4 + 1 < puVar4 || puVar4 < param_1) || puVar3 < puVar4 + 1) ||
          (uVar14 = (ulong)*puVar4, (ulong)((long)((param_2 - param_1[1]) + -4) >> 2) < uVar14)) {
LAB_00051b24:
                    /* WARNING: Does not return */
    pcVar8 = (code *)SoftwareBreakpoint(0x5519,0x51b28);
    (*pcVar8)();
  }
  DAT_006af888 = 1;
  _DAT_006af890 = param_1;
  _DAT_006af898 = puVar4;
  _DAT_006af8b0 = param_1;
  _DAT_006af8b8 = param_2;
  lVar9 = FUN_00051e5c(0,s___DATA_005bb23b);
  lVar10 = FUN_00051e5c(0,s___DATA_CONST_005bb242);
  if ((int)uVar14 != 0) {
    uVar15 = 0;
    puVar1 = puVar4 + 1;
    do {
      puVar5 = puVar1 + uVar15;
      if ((puVar5 < puVar1 || puVar5 + 1 < puVar5) || puVar1 + *puVar4 < puVar5 + 1)
      goto LAB_00051b24;
      uVar6 = *puVar5;
      if (uVar6 != 0) {
        puVar5 = (uint *)((long)param_1 + (ulong)uVar6 + (ulong)param_1[1]);
        if ((puVar5 != (uint *)0x0) &&
           ((puVar2 = puVar5 + 6,
            (((puVar2 < puVar5 || puVar5 < param_1) || puVar3 < puVar2) ||
            puVar3 <= (uint *)((long)puVar5 + 0x16U)) &&
            (((puVar2 < puVar5 || puVar5 < param_1) || puVar3 < puVar2) ||
            (uint *)((long)puVar5 + 0x16U) != puVar3) ||
            ((ulong)((long)((param_2 - 0x16) - ((ulong)uVar6 + (ulong)param_1[1])) >> 1) <
             (ulong)(ushort)puVar5[5])))) goto LAB_00051b24;
        lVar11 = *(long *)(puVar5 + 2);
        if (DAT_006ad6e8 == '\x01') {
          if ((lVar9 == 0) ||
             (*(ulong *)(lVar9 + 0x20) <= (ulong)(lVar11 - (lVar7 + *(long *)(lVar9 + 0x18))))) {
            if ((lVar10 == 0) ||
               (*(ulong *)(lVar10 + 0x20) <= (ulong)(lVar11 - (lVar7 + *(long *)(lVar10 + 0x18)))))
            goto LAB_00051cdc;
            if ((puVar5 != (uint *)0x0) &&
               ((puVar5 + 6 < puVar5 ||
                ((uint *)((long)puVar5 + (ulong)(ushort)puVar5[5] * 2 + 0x16) < puVar5 + 6))))
            goto LAB_00051b24;
            puVar12 = (ulong *)&DAT_006af8a8;
          }
          else {
            if ((puVar5 != (uint *)0x0) &&
               ((puVar5 + 6 < puVar5 ||
                ((uint *)((long)puVar5 + (ulong)(ushort)puVar5[5] * 2 + 0x16) < puVar5 + 6))))
            goto LAB_00051b24;
            puVar12 = (ulong *)&DAT_006af8a0;
          }
          *puVar12 = (ulong)puVar5;
        }
        else {
LAB_00051cdc:
          if ((short)puVar5[5] != 0) {
            uVar13 = 0;
            do {
              FUN_00051740(puVar5,lVar11,lVar11);
              uVar13 = uVar13 + 1;
              lVar11 = lVar11 + 0x4000;
            } while (uVar13 < (ushort)puVar5[5]);
          }
        }
      }
      uVar15 = uVar15 + 1;
    } while (uVar15 != uVar14);
  }
  return;
}

