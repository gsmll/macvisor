
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00031bf4(long param_1)

{
  ulong *puVar1;
  long *plVar2;
  bool bVar3;
  bool bVar4;
  code *pcVar5;
  int iVar6;
  ulong uVar7;
  undefined8 uVar8;
  ulong uVar9;
  long *plVar10;
  long lVar11;
  long lVar12;
  long lVar13;
  long lVar14;
  long *plVar15;
  long lVar16;
  long lVar17;
  long lVar18;
  long lVar19;
  long local_c0;
  undefined8 uStack_b8;
  ulong local_b0;
  undefined8 uStack_a8;
  undefined8 local_a0;
  long local_90;
  long local_88;
  long local_70;
  
  local_70 = -0x2c8502b44bfffed6;
  if ((*(byte *)(param_1 + 9) & 1) == 0) {
    FUN_004b2084();
LAB_00031ffc:
                    /* WARNING: Subroutine does not return */
    FUN_004afae4(s__VAS_abort_in_function__s_at_lin_005aed68);
  }
  if ((*(byte *)(param_1 + 0x1d0) & 1) == 0) {
    bVar4 = false;
    *(undefined1 *)(param_1 + 0x1d0) = 1;
    plVar15 = (long *)(param_1 + 0x148);
    do {
      if (plVar15[8] == 0) {
        uStack_b8 = uRam00000000004bc030;
        local_c0 = _DAT_004bc028;
        uStack_a8 = uRam00000000004bc040;
        local_b0 = _DAT_004bc038;
        local_90 = 0;
        local_88 = 0;
        iVar6 = FUN_00118194(param_1 + 0x40);
        if (iVar6 != 0) {
                    /* WARNING: Subroutine does not return */
          FUN_004afae4(s__VAS_abort_in_function__s_at_lin_005aed68);
        }
        uVar7 = (*(code *)&SUB_90000010f9002830)(param_1,0x1800,&local_c0,&local_90,0,&local_c0);
        uVar7 = uVar7 & 0xff;
        if (uVar7 != 0) {
          if (((undefined8 *)0x64cb3f < &DAT_0064cb40 + uVar7 &&
              &DAT_0064cb48 + uVar7 < (undefined8 *)0x64cb81) &&
              &DAT_0064cb40 + uVar7 <= &DAT_0064cb48 + uVar7) {
                    /* WARNING: Subroutine does not return */
            FUN_004afae4(s__VAS_abort_in_function__s_at_lin_005afade);
          }
LAB_0003245c:
                    /* WARNING: Does not return */
          pcVar5 = (code *)SoftwareBreakpoint(0x5519,0x32460);
          (*pcVar5)();
        }
        if (local_88 != 0x65b648) {
                    /* WARNING: Subroutine does not return */
          FUN_004afae4(s__VAS_abort_in_function__s_at_lin_005afb3f);
        }
        iVar6 = FUN_00118164(param_1 + 0x40);
        if (iVar6 != 0) {
                    /* WARNING: Subroutine does not return */
          FUN_004afae4(s__VAS_abort_in_function__s_at_lin_005aed68);
        }
        if (plVar15[8] != 0) {
                    /* WARNING: Subroutine does not return */
          FUN_004afae4(s__VAS_abort_in_function__s_at_lin_005afba3);
        }
        plVar15[8] = local_90;
        bVar4 = true;
      }
      lVar14 = 0;
      lVar19 = 0;
      plVar10 = plVar15 + 9;
      lVar18 = 1;
      bVar3 = bVar4;
      do {
        if (plVar15 + 0x10 < plVar10 + 1 || plVar10 + 1 < plVar10) goto LAB_0003245c;
        lVar13 = *plVar10;
        if (lVar13 == 0) break;
        if (*(long *)(lVar13 + 0x10) == 0) {
          if ((*(byte *)(param_1 + 9) & 1) == 0) {
            FUN_004b205c();
LAB_00032318:
                    /* WARNING: Subroutine does not return */
            FUN_004afae4(s__VAS_abort_in_function__s_at_lin_005afcfb);
          }
          lVar17 = plVar15[8];
          if (lVar17 == 0) {
                    /* WARNING: Subroutine does not return */
            FUN_004afae4(s__VAS_abort_in_function__s_at_lin_005afc10);
          }
          lVar11 = *(long *)(param_1 + 0x1c8);
          if (lVar11 != 0) {
            if (*(long *)(lVar11 + 0x10) == 0) {
                    /* WARNING: Subroutine does not return */
              FUN_004afae4(s__VAS_abort_in_function__s_at_lin_005afc68);
            }
            if (*(long *)(*(long *)(lVar11 + 0x18) + 8) != 0) goto LAB_00032318;
          }
          uVar7 = *(ulong *)(lVar13 + 0x18);
          if (uVar7 == 0 || (uVar7 & 0x3fff) != 0) {
                    /* WARNING: Subroutine does not return */
            FUN_004afae4(s__VAS_abort_in_function__s_at_lin_005afdb8);
          }
          lVar16 = *(long *)(lVar17 + 8);
          iVar6 = FUN_00118194(param_1 + 0x40);
          if (iVar6 != 0) goto LAB_00031ffc;
          uVar9 = lVar17 + 0x80;
          if (lVar17 + 0x90U < uVar9) goto LAB_0003245c;
          iVar6 = FUN_00118164(uVar9);
          if (iVar6 != 0) {
                    /* WARNING: Subroutine does not return */
            FUN_004afae4(s__VAS_abort_in_function__s_at_lin_005aed68);
          }
          local_a0 = 0;
          uStack_b8 = 0;
          local_c0 = 0;
          uStack_a8 = 0;
          local_b0 = 0;
          FUN_000287e4(&local_c0,*(undefined8 *)(lVar17 + 0x78),
                       (int)((ulong)(lVar14 + (lVar16 - *(long *)(param_1 + 0x88))) >> 0xe) + 1);
          lVar12 = local_c0;
          *(undefined8 *)(lVar17 + 0x78) = local_a0;
          iVar6 = FUN_00118194(uVar9);
          if (lVar12 == 0) {
            if (iVar6 != 0) {
                    /* WARNING: Subroutine does not return */
              FUN_004afae4(s__VAS_abort_in_function__s_at_lin_005aed68);
            }
            if ((((undefined8 *)0x64cb3f < &DAT_0064cb40 + (local_b0 & 0xff)) &&
                (&DAT_0064cb48 + (local_b0 & 0xff) < (undefined8 *)0x64cb81)) &&
               (&DAT_0064cb40 + (local_b0 & 0xff) <= &DAT_0064cb48 + (local_b0 & 0xff))) {
                    /* WARNING: Subroutine does not return */
              FUN_004afae4(s_spanmap_could_not_alloc_a_cap____005afea1);
            }
            goto LAB_0003245c;
          }
          if (iVar6 != 0) {
                    /* WARNING: Subroutine does not return */
            FUN_004afae4(s__VAS_abort_in_function__s_at_lin_005aed68);
          }
          lVar17 = lVar14 + lVar16;
          uVar8 = FUN_00042abc(param_1 + 0x60,1,lVar17);
          uVar9 = FUN_00042c20(param_1 + 0x60,uVar8);
          if ((uVar9 & 1) == 0) {
                    /* WARNING: Subroutine does not return */
            FUN_004afae4(s__VAS_abort_in_function__s_at_lin_005afecd);
          }
          uVar7 = (*(code *)&SUB_f9002c30dac10230)(&DAT_0064c3f0,uVar7,0,lVar12);
          uVar7 = uVar7 & 0xff;
          if (uVar7 != 0) {
            if ((((undefined8 *)0x64cb3f < &DAT_0064cb40 + uVar7) &&
                (&DAT_0064cb48 + uVar7 < (undefined8 *)0x64cb81)) &&
               (&DAT_0064cb40 + uVar7 <= &DAT_0064cb48 + uVar7)) {
                    /* WARNING: Subroutine does not return */
              FUN_004afae4(s__VAS_abort_in_function__s_at_lin_005aff2f);
            }
            goto LAB_0003245c;
          }
          uVar7 = FUN_00043be8(param_1 + 0x60,uVar8,lVar12,lVar17,0,0);
          if ((uVar7 & 0xff) == 4) {
            uVar7 = FUN_000436fc(param_1 + 0x60,lVar17);
            if ((uVar7 & 1) == 0) {
                    /* WARNING: Subroutine does not return */
              FUN_004afae4(s__VAS_abort_in_function__s_at_lin_005affa4);
            }
            uVar7 = FUN_00043be8(param_1 + 0x60,uVar8,lVar12,lVar17,0,0);
          }
          if ((uVar7 & 0xff) != 0) {
            FUN_00032d08(&local_90);
            FUN_004b1c84(0xeb1a02bf914012ba);
            FUN_00032d08(&local_90,uVar7);
                    /* WARNING: Subroutine does not return */
            FUN_004afae4(s_Unexpected_L4_Error___s__zu__err_005b010f);
          }
          iVar6 = FUN_00118164(param_1 + 0x40);
          if (iVar6 != 0) {
                    /* WARNING: Subroutine does not return */
            FUN_004afae4(s__VAS_abort_in_function__s_at_lin_005aed68);
          }
          if (*(long *)(lVar13 + 0x10) != 0) {
                    /* WARNING: Subroutine does not return */
            FUN_004afae4(s__VAS_abort_in_function__s_at_lin_005b0136);
          }
          puVar1 = *(ulong **)(lVar13 + 0x18);
          plVar2 = *(long **)(lVar13 + 0x20);
          if (0x3fff < (ulong)((long)plVar2 - (long)puVar1)) {
                    /* WARNING: Subroutine does not return */
            FUN_004afae4(s__VAS_abort_in_function__s_at_lin_005b0195);
          }
          lVar12 = *(long *)(lVar13 + 8);
          if (0x4000 < (lVar12 - (long)puVar1) + 0x3fe0U) {
                    /* WARNING: Subroutine does not return */
            FUN_004afae4(s__VAS_abort_in_function__s_at_lin_005b01eb);
          }
          uVar7 = (long)plVar2 + lVar14 + (lVar16 - (long)puVar1);
          *(undefined1 *)(puVar1 + 2) = 1;
          if ((uVar7 + 1 < uVar7) ||
             ((long)puVar1 +
              lVar18 + ((((long)plVar2 - (long)puVar1) + lVar19 * 0x4000) - (long)plVar2) < 1))
          goto LAB_0003245c;
          *puVar1 = uVar7;
          *(undefined2 *)((long)puVar1 + 0x11) = 0x101;
          *plVar2 = lVar14 + ((lVar16 + lVar12) - (long)puVar1);
          if (lVar11 != 0) {
            *(long *)(*(long *)(lVar11 + 0x18) + 8) = lVar17;
          }
          *(long *)(param_1 + 0x1c8) = lVar13;
          *(long *)(lVar13 + 0x10) = lVar17;
          bVar3 = true;
        }
        lVar19 = lVar19 + 1;
        lVar14 = lVar14 + 0x4000;
        lVar18 = lVar18 + -0x4000;
        plVar10 = plVar10 + 1;
      } while (lVar14 != 0x1c000);
      plVar10 = (long *)*plVar15;
      plVar15 = plVar10;
      if (plVar10 == (long *)0x0) {
        plVar15 = (long *)(param_1 + 0x148);
      }
      bVar4 = (bool)(plVar10 != (long *)0x0 & bVar3);
    } while ((plVar10 != (long *)0x0) || (bVar3));
    if ((*(byte *)(param_1 + 0x1d0) & 1) == 0) {
                    /* WARNING: Subroutine does not return */
      FUN_004afae4(s__VAS_abort_in_function__s_at_lin_005afa56);
    }
    *(undefined2 *)(param_1 + 0x1d0) = 0x100;
  }
  if (local_70 == -0x2c8502b44bfffed6) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  FUN_0011d7e8();
}

