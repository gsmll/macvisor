
/* WARNING: Type propagation algorithm not settling */

undefined1  [16] FUN_0003a7d4(long *param_1,long *param_2,long param_3,long *param_4)

{
  long *plVar1;
  long *plVar2;
  ulong uVar3;
  undefined8 uVar4;
  uint uVar5;
  long lVar6;
  long lVar7;
  code *pcVar8;
  int iVar9;
  ulong uVar10;
  ulong uVar11;
  long *plVar12;
  ulong uVar13;
  long lVar14;
  long lVar15;
  undefined8 uVar16;
  ulong uVar17;
  undefined1 auVar18 [16];
  undefined1 auVar19 [16];
  undefined8 uStack_2b0;
  undefined8 uStack_2a8;
  undefined8 uStack_2a0;
  undefined8 uStack_298;
  undefined8 uStack_290;
  undefined8 uStack_288;
  undefined8 uStack_280;
  undefined8 uStack_278;
  undefined8 uStack_270;
  undefined8 uStack_268;
  undefined8 uStack_260;
  undefined8 uStack_258;
  undefined8 uStack_250;
  long lStack_240;
  long alStack_238 [13];
  ulong local_138 [13];
  long local_d0;
  long local_c8 [12];
  long local_68;
  
  local_68 = -0x2c8502b44bfffed6;
  if (param_3 == 0x65b648) {
    local_d0 = 0;
    local_c8[0] = 0;
    lVar15 = param_1[10];
    uVar13 = param_2[1];
    lVar14 = lVar15;
    plVar12 = param_1;
    if (uVar13 < (ulong)param_1[1]) {
      if (param_1 + 0x16 < param_1) goto LAB_0003abe8;
      uVar13 = param_1[1];
      lVar14 = param_2[10];
      plVar12 = param_2;
      param_2 = param_1;
    }
    if (lVar14 == param_2[10]) {
      if (*(uint *)(plVar12 + 4) == *(uint *)(param_2 + 4)) {
        if ((*(uint *)(plVar12 + 4) & 0xd000800) == 0) {
          if (uVar13 == 0) {
            uVar10 = 0x75c0001;
          }
          else {
            uVar10 = 0;
            if (plVar12[2] + plVar12[1] != uVar13) {
              uVar10 = 0x75d0001;
            }
          }
        }
        else {
          uVar10 = 0x75b0001;
        }
      }
      else {
        uVar10 = 0x75a0001;
      }
    }
    else {
      uVar10 = 0x7590001;
    }
    auVar18._8_8_ = 0;
    auVar18._0_8_ = uVar10;
    if ((uVar10 & 0xff) == 0) {
      uVar5 = *(uint *)(plVar12 + 4) >> 0x10 & 1;
      local_138[0xb] = 0;
      local_138[8] = 0;
      local_138[7] = 0;
      local_138[10] = 0;
      local_138[9] = 0;
      local_138[4] = 0;
      local_138[3] = 0;
      local_138[6] = 0;
      local_138[5] = 0;
      iVar9 = FUN_0003b820(local_138 + 3,lVar15,0,*(uint *)(plVar12 + 4) != 0,uVar5,uVar5);
      if (iVar9 != 0) {
        local_c8[8] = 0;
        local_c8[7] = 0;
        local_c8[10] = 0;
        local_c8[9] = 0;
        local_c8[4] = 0;
        local_c8[3] = 0;
        local_c8[6] = 0;
        local_c8[5] = 0;
        local_c8[2] = 0;
        local_c8[1] = 0;
        FUN_00044dec(lVar15,local_c8 + 1,plVar12[1],param_2[2] + plVar12[2]);
        plVar1 = plVar12 + 0x10;
        if (plVar1 <= plVar12 + 0x12) {
          iVar9 = FUN_00118164(plVar1);
          if (iVar9 != 0) {
                    /* WARNING: Subroutine does not return */
            FUN_004afae4(s__VAS_abort_in_function__s_at_lin_005aed68);
          }
          plVar2 = param_2 + 0x10;
          if (plVar2 <= param_2 + 0x12) {
            iVar9 = FUN_00118164(plVar2);
            if (iVar9 != 0) {
                    /* WARNING: Subroutine does not return */
              FUN_004afae4(s__VAS_abort_in_function__s_at_lin_005aed68);
            }
            FUN_0003bd70(local_138 + 3,lVar15,local_c8 + 1);
            auVar18 = FUN_0003f41c(local_138 + 3,lVar15,plVar12,param_2,local_c8,&local_d0);
            FUN_0003bfb8(local_138 + 3,lVar15);
            lVar6 = local_c8[0];
            lVar14 = local_d0;
            if (local_c8[0] != 0) {
              local_138[0] = 0;
              local_138[1] = 0;
              local_138[2] = 0;
              FUN_000367a8(local_138,*(undefined8 *)(local_c8[0] + 0x78),
                           *(undefined8 *)(local_d0 + 0x78));
              uVar13 = local_138[0] & 0xff;
              if (uVar13 != 0) {
                if ((((undefined8 *)0x64cb3f < &DAT_0064cb40 + uVar13) &&
                    (&DAT_0064cb48 + uVar13 < (undefined8 *)0x64cb81)) &&
                   (&DAT_0064cb40 + uVar13 <= &DAT_0064cb48 + uVar13)) {
                    /* WARNING: Subroutine does not return */
                  FUN_004afae4(s__VAS_abort_in_function__s_at_lin_005b4674);
                }
                goto LAB_0003abe8;
              }
              *(ulong *)(lVar6 + 0x78) = local_138[2];
              *(undefined8 *)(lVar14 + 0x78) = DAT_004bc1f0;
            }
            iVar9 = FUN_00118194(plVar1);
            if (iVar9 != 0) {
                    /* WARNING: Subroutine does not return */
              FUN_004afae4(s__VAS_abort_in_function__s_at_lin_005aed68);
            }
            iVar9 = FUN_00118194(plVar2);
            if (iVar9 != 0) {
                    /* WARNING: Subroutine does not return */
              FUN_004afae4(s__VAS_abort_in_function__s_at_lin_005aed68);
            }
            FUN_00044ff4(lVar15,local_c8 + 1);
            if (local_d0 != 0) {
              *(undefined8 *)(local_d0 + 0x50) = 0;
              FUN_00033148();
            }
            uVar13 = auVar18._0_8_ & 0xff;
            if (local_c8[0] == 0) {
              if (uVar13 != 0) {
                *param_4 = 0;
                param_4[1] = 0;
                goto LAB_0003aa78;
              }
            }
            else {
              if (uVar13 == 0) {
                *param_4 = local_c8[0];
                param_4[1] = 0x65b648;
                goto LAB_0003aa78;
              }
              FUN_004b30ac();
            }
            auVar18 = FUN_004b30e4();
            uVar13 = auVar18._8_8_;
            lVar14 = auVar18._0_8_;
            alStack_238[0xb] = -0x2c8502b44bfffed6;
            alStack_238[0] = 0;
            lStack_240 = 0;
            uVar5 = *(uint *)(lVar14 + 0x20);
            if ((uVar5 & 0xd000800) == 0) {
              uVar10 = 0x7fb0001;
              if (uVar13 != 0) {
                uVar10 = 0;
              }
              uVar17 = 0x7f80001;
              if (uVar13 < *(ulong *)(lVar14 + 0x10)) {
                uVar17 = uVar10;
              }
            }
            else {
              uVar17 = 0x7f60001;
            }
            auVar19._8_8_ = 0;
            auVar19._0_8_ = uVar17;
            if ((uVar17 & 0xff) == 0) {
              uVar16 = *(undefined8 *)(lVar14 + 0x50);
              uVar4 = 0;
              if (uVar5 != 0) {
                uVar4 = 2;
              }
              uVar5 = uVar5 >> 0x10 & 1;
              uStack_250 = 0;
              uStack_268 = 0;
              uStack_270 = 0;
              uStack_258 = 0;
              uStack_260 = 0;
              uStack_288 = 0;
              uStack_290 = 0;
              uStack_278 = 0;
              uStack_280 = 0;
              uVar10 = FUN_0003b820(&uStack_290,uVar16,1,uVar4,uVar5,uVar5);
              if ((uVar10 & 1) == 0) {
                auVar19 = ZEXT816(0x85f0002);
              }
              else {
                lVar15 = *(long *)(lVar14 + 8);
                alStack_238[8] = 0;
                alStack_238[7] = 0;
                alStack_238[10] = 0;
                alStack_238[9] = 0;
                alStack_238[4] = 0;
                alStack_238[3] = 0;
                alStack_238[6] = 0;
                alStack_238[5] = 0;
                alStack_238[2] = 0;
                alStack_238[1] = 0;
                FUN_00044dec(uVar16,alStack_238 + 1,lVar15,*(undefined8 *)(lVar14 + 0x10));
                uVar10 = lVar14 + 0x80;
                if (lVar14 + 0x90U < uVar10) goto LAB_0003aeb4;
                iVar9 = FUN_00118164(uVar10);
                if (iVar9 != 0) {
                    /* WARNING: Subroutine does not return */
                  FUN_004afae4(s__VAS_abort_in_function__s_at_lin_005aed68);
                }
                FUN_0003bd70(&uStack_290,uVar16,alStack_238 + 1);
                auVar19 = FUN_0003ee4c(&uStack_290,uVar16,lVar14,uVar13,alStack_238,&lStack_240);
                FUN_0003bfb8(&uStack_290,uVar16);
                lVar7 = alStack_238[0];
                lVar6 = lStack_240;
                uVar17 = auVar19._0_8_ & 0xff;
                if (uVar17 == 0) {
                  if (alStack_238[0] != lVar14) {
                    /* WARNING: Subroutine does not return */
                    FUN_004afae4(s__VAS_abort_in_function__s_at_lin_005b47ec);
                  }
                  uVar3 = lStack_240 + 0x80;
                  if (lStack_240 + 0x90U < uVar3) {
LAB_0003aeb4:
                    /* WARNING: Does not return */
                    pcVar8 = (code *)SoftwareBreakpoint(0x5519,0x3aeb8);
                    (*pcVar8)();
                  }
                  iVar9 = FUN_00118164(uVar3);
                  if (iVar9 != 0) {
                    /* WARNING: Subroutine does not return */
                    FUN_004afae4(s__VAS_abort_in_function__s_at_lin_005aed68);
                  }
                  uVar11 = FUN_00032cd0(uVar16);
                  uStack_2a8 = 0;
                  uStack_2b0 = 0;
                  uStack_298 = 0;
                  uStack_2a0 = 0;
                  if (uVar11 + 0xd0 < uVar11) goto LAB_0003aeb4;
                  FUN_00036a94(&uStack_2b0,*(undefined8 *)(lVar14 + 0x78),
                               (int)((lVar15 + uVar13) - *(long *)(uVar11 + 0x28) >> 0xe) + 1);
                  *(undefined8 *)(lVar7 + 0x78) = uStack_2a0;
                  *(undefined8 *)(lVar6 + 0x78) = uStack_298;
                  iVar9 = FUN_00118194(uVar3);
                  if (iVar9 != 0) {
                    /* WARNING: Subroutine does not return */
                    FUN_004afae4(s__VAS_abort_in_function__s_at_lin_005aed68);
                  }
                }
                iVar9 = FUN_00118194(uVar10);
                if (iVar9 != 0) {
                    /* WARNING: Subroutine does not return */
                  FUN_004afae4(s__VAS_abort_in_function__s_at_lin_005aed68);
                }
                FUN_00044ff4(uVar16,alStack_238 + 1);
                if (uVar17 == 0) {
                  if ((alStack_238[0] == 0) || (lStack_240 == 0)) {
                    /* WARNING: Subroutine does not return */
                    FUN_004afae4(s__VAS_abort_in_function__s_at_lin_005b48a0);
                  }
                  *plVar12 = alStack_238[0];
                  plVar12[1] = 0x65b648;
                  *param_2 = lStack_240;
                  param_2[1] = 0x65b648;
                }
                else if (alStack_238[0] != 0 || lStack_240 != 0) {
                    /* WARNING: Subroutine does not return */
                  FUN_004afae4(s__VAS_abort_in_function__s_at_lin_005b493d);
                }
              }
            }
            if (alStack_238[0xb] != -0x2c8502b44bfffed6) {
                    /* WARNING: Subroutine does not return */
              FUN_0011d7e8();
            }
            return auVar19;
          }
        }
LAB_0003abe8:
                    /* WARNING: Does not return */
        pcVar8 = (code *)SoftwareBreakpoint(0x5519,0x3abec);
        (*pcVar8)();
      }
      auVar18 = ZEXT816(0x7bf0002);
    }
  }
  else {
    auVar18 = ZEXT816(0x7a60001);
  }
LAB_0003aa78:
  if (local_68 != -0x2c8502b44bfffed6) {
                    /* WARNING: Subroutine does not return */
    FUN_0011d7e8();
  }
  return auVar18;
}

