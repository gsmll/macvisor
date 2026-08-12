
long FUN_00054e54(long param_1,char *param_2,long param_3)

{
  char *pcVar1;
  undefined1 uVar2;
  undefined1 uVar3;
  undefined1 uVar4;
  undefined1 uVar5;
  undefined1 uVar6;
  undefined1 uVar7;
  char cVar8;
  char cVar9;
  undefined1 uVar10;
  undefined1 uVar11;
  undefined1 uVar12;
  undefined1 uVar13;
  undefined1 uVar14;
  undefined1 uVar15;
  undefined1 *puVar16;
  undefined1 uVar17;
  undefined2 uVar18;
  code *pcVar19;
  long lVar20;
  long lVar21;
  undefined8 uVar22;
  long lVar23;
  undefined1 auVar24 [16];
  
  if ((param_1 != 0x64cd78) || (lVar20 = FUN_0004cdc0(param_2,param_3), lVar20 != 0)) {
    auVar24 = thunk_FUN_000533ec();
    uVar22 = auVar24._8_8_;
    lVar20 = auVar24._0_8_;
    puVar16 = (undefined1 *)tpidrro_el0;
    uVar3 = puVar16[9];
    uVar2 = puVar16[8];
    uVar4 = puVar16[0xb];
    uVar5 = puVar16[10];
    uVar18 = *(undefined2 *)(puVar16 + 0xc);
    uVar6 = puVar16[0xf];
    uVar7 = puVar16[0xe];
    if (param_3 != 0) {
      lVar23 = 0;
      do {
        if ((param_1 == 0x64d038) && (lVar21 = FUN_00055b44(lVar20,uVar22), lVar21 != 0)) {
          uVar22 = FUN_00055b44();
          pcVar1 = param_2 + lVar23;
          if ((param_2 + param_3 <= pcVar1) || (pcVar1 < param_2)) {
LAB_00055160:
                    /* WARNING: Does not return */
            pcVar19 = (code *)SoftwareBreakpoint(0x5519,0x55164);
            (*pcVar19)();
          }
          cVar8 = *pcVar1;
          *puVar16 = (char)uVar22;
          uVar10 = (undefined1)((ulong)uVar22 >> 0x28);
          puVar16[5] = uVar10;
          uVar11 = (undefined1)((ulong)uVar22 >> 0x18);
          puVar16[3] = uVar11;
          uVar12 = (undefined1)((ulong)uVar22 >> 0x10);
          puVar16[2] = uVar12;
          uVar13 = (undefined1)((ulong)uVar22 >> 8);
          puVar16[1] = uVar13;
          uVar15 = (undefined1)((ulong)uVar22 >> 0x20);
          puVar16[4] = uVar15;
          uVar17 = (undefined1)((ulong)uVar22 >> 0x38);
          puVar16[7] = uVar17;
          uVar14 = (undefined1)((ulong)uVar22 >> 0x30);
          puVar16[6] = uVar14;
          cVar9 = (char)cVar8 >> 7;
          puVar16[0xd] = cVar9;
          puVar16[8] = cVar8;
          puVar16[0xb] = cVar9;
          puVar16[10] = cVar9;
          puVar16[9] = cVar9;
          puVar16[0xc] = cVar9;
          puVar16[0xf] = cVar8 >> 7;
          puVar16[0xe] = cVar9;
          do {
            CallSupervisor(0);
            *puVar16 = (char)uVar22;
            puVar16[5] = uVar10;
            puVar16[3] = uVar11;
            puVar16[2] = uVar12;
            puVar16[1] = uVar13;
            puVar16[4] = uVar15;
            puVar16[7] = uVar17;
            puVar16[6] = uVar14;
          } while (lVar20 == 1);
        }
        else {
          pcVar1 = param_2 + lVar23;
          if ((param_2 + param_3 <= pcVar1) || (pcVar1 < param_2)) goto LAB_00055160;
          cVar8 = *pcVar1;
          puVar16[5] = 0;
          puVar16[3] = 0;
          puVar16[2] = 0;
          puVar16[1] = 0;
          puVar16[4] = 0;
          *puVar16 = 0;
          puVar16[7] = 0;
          puVar16[6] = 0;
          cVar9 = (char)cVar8 >> 7;
          puVar16[0xd] = cVar9;
          puVar16[8] = cVar8;
          puVar16[0xb] = cVar9;
          puVar16[10] = cVar9;
          puVar16[9] = cVar9;
          puVar16[0xc] = cVar9;
          puVar16[0xf] = cVar8 >> 7;
          puVar16[0xe] = cVar9;
          do {
            CallSupervisor(0);
            *puVar16 = 0;
            puVar16[5] = 0;
            puVar16[3] = 0;
            puVar16[2] = 0;
            puVar16[1] = 0;
            puVar16[4] = 0;
            puVar16[7] = 0;
            puVar16[6] = 0;
          } while (lVar20 == 1);
        }
        uVar22 = 0;
        lVar23 = lVar23 + 1;
      } while (lVar23 != param_3);
    }
    puVar16[8] = uVar2;
    puVar16[0xd] = (char)((ushort)uVar18 >> 8);
    puVar16[0xb] = uVar4;
    puVar16[10] = uVar5;
    puVar16[9] = uVar3;
    puVar16[0xc] = (char)uVar18;
    puVar16[0xf] = uVar6;
    puVar16[0xe] = uVar7;
  }
  return param_3;
}

