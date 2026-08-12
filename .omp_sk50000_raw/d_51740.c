
undefined8 FUN_00051740(long param_1,ulong param_2,long param_3)

{
  ulong uVar1;
  long lVar2;
  ushort *puVar3;
  ulong *puVar4;
  long lVar5;
  ushort uVar6;
  short sVar7;
  code *pcVar8;
  ulong uVar9;
  long lVar10;
  long lVar11;
  ulong uVar12;
  undefined8 uVar13;
  ulong uVar14;
  ulong uVar15;
  ulong *puVar16;
  ulong *puVar17;
  long lVar18;
  
  if (param_1 != 0) {
    if ((param_2 & 0x3fff) != 0) {
LAB_0005191c:
                    /* WARNING: Does not return */
      pcVar8 = (code *)SoftwareBreakpoint(1,0x51920);
      (*pcVar8)();
    }
    if (param_2 < 0xffffffffffffc000) {
      uVar13 = 0;
      uVar1 = param_2 + 0x4000;
      lVar11 = *(long *)(param_1 + 8);
      uVar12 = (ulong)*(ushort *)(param_1 + 4);
      uVar6 = *(ushort *)(param_1 + 0x14);
      lVar2 = param_2 + uVar12;
      lVar10 = 0;
      do {
        uVar9 = 0;
        if (uVar12 != 0) {
          uVar9 = (param_2 - lVar11) / uVar12;
        }
        if (uVar6 <= uVar9) {
          return uVar13;
        }
        puVar3 = (ushort *)(param_1 + 0x16 + uVar9 * 2);
        if (puVar3 + 1 < puVar3 || (ushort *)(param_1 + 0x16 + (ulong)uVar6 * 2) < puVar3 + 1) {
LAB_00051918:
                    /* WARNING: Does not return */
          pcVar8 = (code *)SoftwareBreakpoint(0x5519,0x5191c);
          (*pcVar8)();
        }
        uVar9 = (ulong)*puVar3;
        if (uVar9 != 0xffff) {
          sVar7 = *(short *)(param_1 + 6);
          if ((sVar7 != 0xc) && (sVar7 != 7)) goto LAB_0005191c;
          puVar4 = (ulong *)(lVar10 + param_3);
          puVar16 = (ulong *)((long)puVar4 + uVar9);
          if (puVar16 != (ulong *)0x0) {
            lVar5 = 2;
            if (sVar7 != 7) {
              lVar5 = 3;
            }
            do {
              uVar14 = *puVar16;
              uVar15 = uVar14 >> 0x33 & 0x7ff;
              lVar18 = uVar15 << lVar5;
              if (uVar15 == 0) {
                puVar17 = (ulong *)0x0;
                if (-1 < (long)uVar14) goto LAB_00051848;
LAB_0005187c:
                uVar14 = uVar14 & 0xffffffff;
              }
              else {
                puVar17 = (ulong *)((long)puVar4 + (uVar9 & 0xffff) + lVar18);
                if ((puVar17 != (ulong *)0x0) &&
                   ((puVar17 < puVar4 || (ulong *)((long)puVar4 + uVar12) < puVar17 + 1) ||
                    puVar17 + 1 < puVar17)) goto LAB_00051918;
                if ((long)uVar14 < 0) goto LAB_0005187c;
LAB_00051848:
                uVar14 = uVar14 & 0x7ffffffffff | (uVar14 >> 0x2b) << 0x38;
              }
              uVar9 = (ulong)(uint)((int)uVar9 + (int)lVar18);
              *puVar16 = uVar14;
              puVar16 = puVar17;
            } while (puVar17 != (ulong *)0x0);
          }
          uVar13 = 1;
        }
        param_2 = lVar10 + lVar2;
        lVar10 = lVar10 + uVar12;
        if (uVar1 <= param_2) {
          return uVar13;
        }
      } while( true );
    }
  }
  return 0;
}

