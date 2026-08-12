
void FUN_00032888(long param_1)

{
  ulong *puVar1;
  long *plVar2;
  long *plVar3;
  ulong uVar4;
  byte bVar5;
  byte bVar6;
  code *pcVar7;
  int iVar8;
  long lVar9;
  undefined8 *puVar10;
  long lVar11;
  long lVar12;
  ulong *puVar13;
  ulong *puVar14;
  ulong uVar15;
  long *plVar16;
  long lVar17;
  undefined1 auVar18 [16];
  undefined8 local_a0;
  undefined8 uStack_98;
  undefined8 local_90;
  undefined8 uStack_88;
  undefined8 local_80;
  undefined8 uStack_78;
  undefined1 local_70 [16];
  
  local_70 = (*(code *)&SUB_dac10230d29ed7b1)();
  if (local_70._0_8_ != 0) {
    uVar15 = 0;
    do {
      auVar18 = (**(code **)local_70._8_8_)(local_70);
      lVar9 = auVar18._8_8_;
      lVar17 = auVar18._0_8_;
      if (lVar17 != 0) {
        uStack_88 = 0;
        local_90 = 0;
        uStack_78 = 0;
        local_80 = 0;
        if (lVar9 == 0) {
                    /* WARNING: Subroutine does not return */
          FUN_00054354();
        }
        (**(code **)(lVar9 + 8))(lVar17,&local_90);
        local_a0 = local_80;
        uStack_98 = 0;
        uVar15 = uVar15 & 0xff;
        if (uVar15 != 0) {
          if (((undefined8 *)0x64cb3f < &DAT_0064cb40 + uVar15 &&
              &DAT_0064cb48 + uVar15 < (undefined8 *)0x64cb81) &&
              &DAT_0064cb40 + uVar15 <= &DAT_0064cb48 + uVar15) {
                    /* WARNING: Subroutine does not return */
            FUN_004afae4(s__VAS_abort_in_function__s_at_lin_005b0277);
          }
          goto LAB_00032c60;
        }
        uVar15 = (**(code **)(lVar9 + 0x30))(lVar17,&uStack_98,&local_a0);
        uVar4 = uVar15 & 0xff;
        if (uVar4 != 0) {
          if (((undefined8 *)0x64cb3f < &DAT_0064cb40 + uVar4 &&
              &DAT_0064cb48 + uVar4 < (undefined8 *)0x64cb81) &&
              &DAT_0064cb40 + uVar4 <= &DAT_0064cb48 + uVar4) {
                    /* WARNING: Subroutine does not return */
            FUN_004afae4(s__VAS_abort_in_function__s_at_lin_005b02d7);
          }
          goto LAB_00032c60;
        }
      }
    } while (local_70._0_8_ != 0);
  }
  *(undefined8 *)(param_1 + 0x130) = 0;
  FUN_000459d4(param_1);
  FUN_0003c32c(param_1 + 0x58);
  bVar5 = *(byte *)(param_1 + 9);
  *(undefined8 *)(param_1 + 0x138) = 0;
  if (param_1 + 0x138U <= param_1 + 0x140U) {
    *(ulong *)(param_1 + 0x140) = param_1 + 0x138U;
    puVar1 = (ulong *)(param_1 + 0x148);
    puVar13 = puVar1;
    if (puVar1 <= param_1 + 0x1c8U) {
      do {
        lVar17 = 0;
        puVar13[8] = 0;
        do {
          puVar14 = puVar13 + lVar17 + 9;
          if (puVar13 + 0x10 < puVar14 + 1 || puVar14 + 1 < puVar14) goto LAB_00032c60;
          plVar16 = (long *)*puVar14;
          *puVar14 = 0;
          puVar14 = puVar13 + lVar17 + 1;
          if (puVar13 + 8 < puVar14 + 1 || puVar14 + 1 < puVar14) goto LAB_00032c60;
          *puVar14 = 0;
          if (plVar16 != (long *)0x0) {
            plVar16[7] = 0;
            plVar16[2] = 0;
            puVar10 = (undefined8 *)plVar16[3];
            if (puVar10 != (undefined8 *)0x0) {
              *puVar10 = 0;
              puVar10[1] = 0;
              puVar10[2] = 0;
            }
            *(undefined2 *)(plVar16[1] + 6) = 0;
            FUN_001143a0(plVar16[5],0,(ulong)*(byte *)((long)plVar16 + 0x42) << 3);
            lVar9 = FUN_0005acac(0x6af010,4,10);
            uVar15 = lVar9 + 0xb0;
            if (lVar9 + 0xc0U < uVar15) goto LAB_00032c60;
            iVar8 = FUN_00118164(uVar15);
            if (iVar8 != 0) {
LAB_00032b68:
                    /* WARNING: Subroutine does not return */
              FUN_004afae4(s__VAS_abort_in_function__s_at_lin_005aed68);
            }
            lVar12 = 0;
            lVar11 = *plVar16;
            do {
              plVar2 = (long *)(lVar11 + lVar12 + 0x20);
              plVar3 = (long *)(lVar11 + lVar12 + 0x28);
              if ((long *)(lVar11 + 0xa0) < plVar3 || plVar3 < plVar2) goto LAB_00032c60;
              if (*plVar2 == plVar16[1]) {
                if (*(char *)(lVar11 + 0x1a) == '\0') {
                  FUN_004b20e8();
                  goto LAB_00032b68;
                }
                bVar6 = *(char *)(lVar11 + 0x1a) - 1;
                *(byte *)(lVar11 + 0x1a) = bVar6;
                plVar2 = (long *)(lVar11 + 0x20) + bVar6;
                if ((plVar2 < (long *)(lVar11 + 0x20) || (long *)(lVar11 + 0xa0) < plVar2 + 1) ||
                    plVar2 + 1 < plVar2) goto LAB_00032c60;
                *(long *)(lVar11 + lVar12 + 0x20) = *plVar2;
                *plVar2 = 0;
                break;
              }
              lVar12 = lVar12 + 8;
            } while (lVar12 != 0x80);
            *plVar16 = 0;
            if (*(long *)(lVar9 + 0xa0) != lVar11) {
              *(long *)(lVar9 + 0xa0) = lVar9;
            }
            iVar8 = FUN_00118194(uVar15);
            if (iVar8 != 0) {
                    /* WARNING: Subroutine does not return */
              FUN_004afae4(s__VAS_abort_in_function__s_at_lin_005aed68);
            }
            if ((bVar5 & 1) == 0) {
              FUN_00033e00();
            }
            else {
              FUN_000341f4(plVar16);
            }
          }
          lVar17 = lVar17 + 1;
        } while (lVar17 != 7);
        puVar14 = (ulong *)*puVar13;
        if (puVar13 != puVar1) {
          FUN_000333f4();
        }
        puVar13 = puVar14;
        if (puVar14 == (ulong *)0x0) {
          *(undefined2 *)(param_1 + 0x1d0) = 0;
          *(undefined8 *)(param_1 + 0x1c8) = 0;
          FUN_00042808(param_1 + 0x60);
          return;
        }
      } while( true );
    }
  }
LAB_00032c60:
                    /* WARNING: Does not return */
  pcVar7 = (code *)SoftwareBreakpoint(0x5519,0x32c64);
  (*pcVar7)();
}

