
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 FUN_0005236c(long param_1,ulong param_2,long param_3)

{
  ushort *puVar1;
  ushort *puVar2;
  ushort *puVar3;
  ushort *puVar4;
  ushort *puVar5;
  long lVar6;
  undefined8 *puVar7;
  ushort uVar8;
  undefined8 *puVar9;
  undefined1 uVar10;
  undefined1 uVar11;
  code *pcVar12;
  bool bVar13;
  int iVar14;
  ulong uVar15;
  undefined8 uVar16;
  byte *pbVar17;
  undefined8 *puVar18;
  ulong uVar19;
  ulong uVar20;
  long lVar21;
  undefined1 auVar22 [16];
  undefined8 local_a8;
  undefined8 local_a0;
  undefined8 local_98;
  ushort *local_90;
  long lStack_88;
  ulong local_80;
  long lStack_78;
  undefined1 *local_70;
  undefined8 uStack_68;
  
  if (DAT_006ad6ea == '\x01') {
    uVar15 = FUN_00051740(param_1,param_2,param_3);
    if ((uVar15 & 1) != 0) {
      return 1;
    }
    FUN_004b5e20();
  }
  puVar1 = (ushort *)(param_1 + 0x18);
  uVar15 = (ulong)(uint)*(ushort *)(param_1 + 0x16);
  puVar2 = (ushort *)(param_1 + uVar15 * 4 + (ulong)*(ushort *)(param_1 + 0x14) * 2 + 0x18);
  if (puVar1 <= puVar2) {
    uVar19 = (ulong)*(byte *)(param_1 + 0xe) << 0x10 | (ulong)*(byte *)(param_1 + 0xf) << 0x18 |
             (ulong)*(ushort *)(param_1 + 0xc) |
             (ulong)((uint)*(byte *)(param_1 + 0x12) << 0x10 |
                     (uint)*(byte *)(param_1 + 0x13) << 0x18 | (uint)*(ushort *)(param_1 + 0x10)) <<
             0x20;
    uVar20 = uVar19 + _DAT_006ad6e0;
    if (param_2 < uVar20 ||
        _DAT_006ad6e0 + (ulong)*(ushort *)(param_1 + 0x14) * 0x4000 + uVar19 <= param_2) {
LAB_00052570:
      uVar16 = FUN_004b5e20();
      uStack_68 = 0x52574;
      if ((DAT_006af8d0 & 1) == 0) {
        local_90 = puVar1;
        lStack_88 = param_1;
        local_80 = param_2;
        lStack_78 = param_3;
        local_70 = &stack0xfffffffffffffff0;
        pbVar17 = (byte *)FUN_00054610();
        if ((*pbVar17 & 1) == 0) {
          local_98 = 0;
          uVar16 = FUN_0006562c(s___COMPONENTNAME_005bba0f,&local_98);
          if (*(long *)(pbVar17 + 0xc0) == 0) {
            FUN_0004dfd0(local_98,uVar16);
          }
        }
        uVar11 = DAT_006ad6e9;
        uVar10 = DAT_006ad6e8;
        _DAT_006ad6f0 = FUN_00063aa8(FUN_00052968,0x52988,0);
        uVar16 = FUN_000537c4();
        puVar9 = (undefined8 *)tpidr_el0;
        puVar7 = puVar9 + _DAT_006ad6f0;
        puVar18 = puVar7 + -1;
        if ((puVar18 < puVar9 || puVar9 + 0x1f < puVar7) || puVar7 < puVar18) {
                    /* WARNING: Does not return */
          pcVar12 = (code *)SoftwareBreakpoint(0x5519,0x52718);
          (*pcVar12)();
        }
        *puVar18 = uVar16;
        iVar14 = FUN_0004fe80();
        if (iVar14 != 0) {
          FUN_0004ffd0(uVar11,uVar10);
        }
        local_a0 = 0;
        local_98 = 0;
        local_a8 = 0;
        FUN_00053634(&local_98,&local_a0,&local_a8);
        FUN_00035a78(local_98,local_a0,local_a8);
        FUN_0005371c();
        FUN_0004d39c();
        FUN_0004d8ec();
        if (_DAT_006af8c8 != (code *)0x0) {
          (*_DAT_006af8c8)();
        }
        FUN_0005ee7c();
        iVar14 = FUN_0004fe80();
        if (iVar14 != 0) {
          FUN_000501cc(uVar11,uVar10);
        }
        FUN_00060524();
        uVar16 = FUN_00061630();
        auVar22 = FUN_0004ba18();
        (**(code **)(auVar22._8_8_ + 0x20))(uVar16,auVar22._0_8_);
        FUN_00011d7c(0);
        FUN_001190fc();
        uVar16 = FUN_0005cb18(0);
        DAT_006af8d0 = 1;
      }
      return uVar16;
    }
    uVar20 = param_2 - uVar20 >> 0xe;
    puVar3 = puVar1 + uVar20;
    if ((puVar1 <= puVar3 && puVar3 + 1 <= puVar2) && puVar3 <= puVar3 + 1) {
      uVar8 = *puVar3;
      if (uVar8 == 0xfffe) {
        if (*(ushort *)(param_1 + 0x16) != 0) {
          uVar19 = 0;
          lVar21 = param_1;
          do {
            lVar6 = lVar21 + (ulong)*(ushort *)(param_1 + 0x14) * 2;
            puVar3 = (ushort *)(lVar6 + 0x18);
            puVar4 = (ushort *)(lVar6 + 0x1a);
            bVar13 = puVar3 < puVar1;
            puVar5 = (ushort *)(lVar6 + 0x1c);
            if (((((bVar13 || puVar2 < puVar4) || puVar4 < puVar3) || puVar2 <= puVar5) &&
                 (((bVar13 || puVar2 < puVar4) || puVar4 < puVar3) || puVar5 != puVar2) ||
                puVar5 <= puVar4) &&
                ((((bVar13 || puVar2 < puVar4) || puVar4 < puVar3) || puVar2 <= puVar5) &&
                 (((bVar13 || puVar2 < puVar4) || puVar4 < puVar3) || puVar5 != puVar2) ||
                puVar4 != puVar5)) goto LAB_0005256c;
            if (uVar20 == *puVar3) {
              FUN_0004d150(param_3 + (ulong)*puVar4,param_2 & 0xffffffffffffc000,
                           *(undefined2 *)(param_1 + 2),-_DAT_006ad6e0);
              uVar15 = (ulong)*(ushort *)(param_1 + 0x16);
            }
            uVar19 = uVar19 + 1;
            lVar21 = lVar21 + 4;
          } while (uVar19 < uVar15);
        }
      }
      else {
        if (uVar8 == 0xffff) goto LAB_00052570;
        FUN_0004d150(param_3 + (ulong)uVar8,param_2 & 0xffffffffffffc000,
                     *(undefined2 *)(param_1 + 2),-_DAT_006ad6e0);
      }
      return 1;
    }
  }
LAB_0005256c:
                    /* WARNING: Does not return */
  pcVar12 = (code *)SoftwareBreakpoint(0x5519,0x52570);
  (*pcVar12)();
}

