
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0005eec4(ulong *param_1,undefined8 param_2,ulong param_3,long param_4,int param_5)

{
  bool bVar1;
  undefined4 uVar2;
  ushort uVar3;
  uint uVar4;
  undefined1 uVar5;
  undefined1 uVar6;
  undefined1 uVar7;
  undefined1 uVar8;
  undefined1 uVar9;
  undefined1 uVar10;
  undefined1 uVar11;
  uint uVar12;
  undefined1 *puVar13;
  undefined1 uVar14;
  undefined8 uVar15;
  code *pcVar16;
  char cVar17;
  char cVar18;
  byte bVar19;
  int iVar20;
  long lVar21;
  ulong uVar22;
  undefined8 uVar23;
  ulong uVar24;
  long lVar25;
  long *plVar26;
  long lVar27;
  char *pcVar28;
  uint uVar29;
  undefined8 extraout_x8;
  uint uVar30;
  uint uVar31;
  ushort *puVar32;
  undefined1 in_wzr;
  undefined1 auVar33 [16];
  ulong local_c8;
  undefined8 local_c0;
  undefined8 *local_b8;
  undefined1 auStack_b0 [32];
  undefined8 local_90;
  long local_88;
  long local_80;
  undefined8 uStack_78;
  long local_70;
  
  local_70 = -0x2c8502b44bfffed6;
  lVar21 = FUN_0005bb68();
  puVar32 = (ushort *)(lVar21 + 0x38);
  uVar3 = *puVar32;
  *puVar32 = uVar3 + 1;
  if (uVar3 < 0x400) {
    uVar22 = FUN_0005c0ac();
    if (uVar22 != 0) {
      FUN_0005db7c();
      goto LAB_0005ef44;
    }
    local_80 = 0x24000;
    uStack_78 = 0x200000000c;
    local_90 = 0x11;
    local_88 = 0;
    local_c0 = 0;
    local_b8 = (undefined8 *)0x0;
    iVar20 = FUN_00054de4();
    uVar2 = 0x40c8;
    if (iVar20 == 0) {
      uVar2 = 0x41140c8;
    }
    auVar33 = FUN_00034a2c();
    cVar17 = (**(code **)(auVar33._8_8_ + 0x30))(auVar33._0_8_,uVar2,&local_90,&local_c0,0,0);
    uVar22 = FUN_00054de4();
    if (((uVar22 & 1) == 0) &&
       (cVar18 = (*(code *)local_b8[10])(local_c0,0,0x4000,0x20000), cVar18 != '\0')) {
LAB_0005f95c:
      pcVar28 = s__xrt__Failed_to_make_thread_stac_005bd182;
LAB_0005f974:
                    /* WARNING: Subroutine does not return */
      FUN_0005b190(0,pcVar28);
    }
    if (cVar17 != '\0') {
      _DAT_006b26a4 = _DAT_006b26a4 + 1;
      goto LAB_0005ef24;
    }
    if (local_b8 == (undefined8 *)0x0) {
                    /* WARNING: Subroutine does not return */
      FUN_00054354();
    }
    (*(code *)local_b8[1])(local_c0,&local_90);
    uVar22 = FUN_000612e0(local_88,local_80);
    if (uVar22 + 0x178 < uVar22) goto LAB_0005f584;
    lVar21 = FUN_000613ec(uVar22,0);
    uVar24 = (local_88 - lVar21) + local_80;
    if (0x1ffff < uVar24) {
      pcVar28 = s__xrt__Thread_stack_allocation_si_005bd1af;
      goto LAB_0005f974;
    }
    local_c8 = uVar24;
    iVar20 = FUN_00054de4();
    if (iVar20 != 0) {
      local_c8 = 0x20000;
    }
    cVar17 = (*(code *)local_b8[3])(local_c0,&local_c8);
    if (cVar17 == '\0') {
      FUN_001143a0(uVar22,0,0x178);
      *(undefined8 *)(uVar22 + 0x30) = local_c0;
      *(undefined8 **)(uVar22 + 0x38) = local_b8;
      *(long *)(uVar22 + 0x138) = local_80;
      *(long *)(uVar22 + 0x130) = local_88;
      *(long *)(uVar22 + 0x140) = lVar21;
      *(long *)(uVar22 + 0x168) = local_88 + 0x4000;
      *(long *)(uVar22 + 0x170) = lVar21;
      uVar23 = FUN_00061488(uVar22);
      lVar21 = FUN_00034f70();
      if (lVar21 == 0) {
        _DAT_006b26ac = _DAT_006b26ac + 1;
      }
      else {
        auVar33 = FUN_00034a2c();
        cVar17 = (**(code **)(auVar33._8_8_ + 0x40))(auVar33._0_8_,uVar23,1,lVar21);
        if (cVar17 == '\0') {
          lVar25 = FUN_00034f70();
          *(long *)(uVar22 + 0x70) = lVar25;
          if (lVar25 == 0) {
            _DAT_006b26b4 = _DAT_006b26b4 + 1;
          }
          else {
            uVar24 = FUN_0019ae2c(6);
            *(ulong *)(uVar22 + 0x28) = uVar24;
            if (uVar24 == 0) {
              _DAT_006b26b8 = _DAT_006b26b8 + 1;
            }
            else {
              puVar13 = (undefined1 *)tpidrro_el0;
              *puVar13 = (char)lVar21;
              uVar5 = (undefined1)((ulong)lVar21 >> 8);
              puVar13[1] = uVar5;
              uVar8 = (undefined1)((ulong)lVar21 >> 0x20);
              puVar13[4] = uVar8;
              uVar6 = (undefined1)((ulong)lVar21 >> 0x28);
              puVar13[5] = uVar6;
              uVar9 = (undefined1)((ulong)lVar21 >> 0x10);
              puVar13[2] = uVar9;
              uVar7 = (undefined1)((ulong)lVar21 >> 0x18);
              puVar13[3] = uVar7;
              uVar10 = (undefined1)((ulong)lVar21 >> 0x30);
              puVar13[6] = uVar10;
              uVar11 = (undefined1)((ulong)lVar21 >> 0x38);
              puVar13[7] = uVar11;
              puVar13[0xd] = (char)((ulong)uVar23 >> 0x28);
              puVar13[8] = (char)uVar23;
              puVar13[0xb] = (char)((ulong)uVar23 >> 0x18);
              puVar13[10] = (char)((ulong)uVar23 >> 0x10);
              puVar13[9] = (char)((ulong)uVar23 >> 8);
              puVar13[0xc] = (char)((ulong)uVar23 >> 0x20);
              puVar13[0xf] = (char)((ulong)uVar23 >> 0x38);
              puVar13[0xe] = (char)((ulong)uVar23 >> 0x30);
              CallSupervisor(0);
              *puVar13 = (char)lVar21;
              puVar13[7] = uVar11;
              puVar13[6] = uVar10;
              puVar13[5] = uVar6;
              puVar13[4] = uVar8;
              puVar13[3] = uVar7;
              puVar13[2] = uVar9;
              puVar13[1] = uVar5;
              if ((uVar24 & 0xff) != 0) {
                bVar19 = FUN_004b6e24(uVar24,auStack_b0);
                if (bVar19 < 10) {
                  switch(bVar19) {
                  default:
                    pcVar28 = s_L4_ErrorCodeSuccess_004be1b0;
                    break;
                  case 1:
                    pcVar28 = s_L4_ErrorCodePreempted_004be1d0;
                    break;
                  case 2:
                    pcVar28 = s_L4_ErrorCodeCanceled_004be1f0;
                    break;
                  case 3:
                    pcVar28 = s_L4_ErrorCodeTruncated_004be210;
                    break;
                  case 4:
                    pcVar28 = s_L4_ErrorCodeCapInvalid_004be230;
                    break;
                  case 5:
                    pcVar28 = s_L4_ErrorCodeSlotInvalid_004be250;
                    break;
                  case 6:
                    pcVar28 = s_L4_ErrorCodeMethodInvalid_004be270;
                    break;
                  case 7:
                    pcVar28 = s_L4_ErrorCodeArgumentInvalid_004be290;
                    break;
                  case 8:
                    pcVar28 = s_L4_ErrorCodeOperationInvalid_004be2b0;
                    break;
                  case 9:
                    pcVar28 = s_L4_ErrorCodePermissionInvalid_004be2d0;
                  }
                  FUN_00117cc4(extraout_x8,pcVar28,0x20);
                  return;
                }
                FUN_00117cc4(extraout_x8,&DAT_004be2f0,0x20);
                FUN_0000178c(extraout_x8,0x20);
                return;
              }
              if (uVar24 == 0) {
                lVar25 = *(long *)(uVar22 + 0x28);
                uVar23 = FUN_0005d77c(0,0xb);
                *puVar13 = (char)uVar23;
                uVar5 = (undefined1)((ulong)uVar23 >> 8);
                puVar13[1] = uVar5;
                uVar8 = (undefined1)((ulong)uVar23 >> 0x20);
                puVar13[4] = uVar8;
                uVar6 = (undefined1)((ulong)uVar23 >> 0x28);
                puVar13[5] = uVar6;
                uVar9 = (undefined1)((ulong)uVar23 >> 0x10);
                puVar13[2] = uVar9;
                uVar7 = (undefined1)((ulong)uVar23 >> 0x18);
                puVar13[3] = uVar7;
                uVar10 = (undefined1)((ulong)uVar23 >> 0x30);
                puVar13[6] = uVar10;
                uVar11 = (undefined1)((ulong)uVar23 >> 0x38);
                puVar13[7] = uVar11;
                CallSupervisor(0);
                *puVar13 = (char)uVar23;
                puVar13[7] = uVar11;
                puVar13[6] = uVar10;
                puVar13[5] = uVar6;
                puVar13[4] = uVar8;
                puVar13[3] = uVar7;
                puVar13[2] = uVar9;
                puVar13[1] = uVar5;
                if (lVar25 == 0) {
                  uVar24 = FUN_00064c24(uVar22,9);
                  if ((uVar24 & 1) == 0) {
LAB_0005f938:
                    FUN_004b6e88();
                  }
                  else {
                    lVar25 = FUN_000603c4();
                    if (lVar25 == 0) {
LAB_0005ef44:
                      uVar23 = FUN_000604fc();
                      *(undefined8 *)(uVar22 + 0x120) = uVar23;
                      uVar30 = (uint)uVar23 + (((uint)uVar23 >> 3 & 0x1fff) / 0x7d) * -1000;
                      uVar29 = 0x54;
                      uVar31 = 1000;
                      do {
                        uVar4 = uVar31 / 10;
                        uVar12 = 0;
                        if (uVar4 != 0) {
                          uVar12 = (uVar30 & 0xffff) / uVar4;
                        }
                        uVar29 = uVar12 + 0x30 & 0xffff | uVar29 << 8;
                        uVar30 = uVar30 - uVar12 * uVar4;
                        bVar1 = 0x13 < uVar31;
                        uVar31 = uVar4;
                      } while (bVar1);
                      *(uint *)(uVar22 + 0x118) = uVar29;
                      *(ulong *)(uVar22 + 0x128) = uVar22;
                      uVar24 = *(ulong *)(uVar22 + 0x28);
                      puVar13 = (undefined1 *)tpidrro_el0;
                      uVar5 = (undefined1)uVar22;
                      *puVar13 = uVar5;
                      uVar9 = (undefined1)(uVar22 >> 0x20);
                      puVar13[4] = uVar9;
                      uVar6 = (undefined1)(uVar22 >> 8);
                      puVar13[1] = uVar6;
                      uVar10 = (undefined1)(uVar22 >> 0x10);
                      puVar13[2] = uVar10;
                      uVar7 = (undefined1)(uVar22 >> 0x28);
                      puVar13[5] = uVar7;
                      uVar11 = (undefined1)(uVar22 >> 0x30);
                      puVar13[6] = uVar11;
                      uVar8 = (undefined1)(uVar22 >> 0x18);
                      puVar13[3] = uVar8;
                      uVar14 = (undefined1)(uVar22 >> 0x38);
                      puVar13[7] = uVar14;
                      CallSupervisor(0);
                      *puVar13 = uVar5;
                      puVar13[7] = uVar14;
                      puVar13[6] = uVar11;
                      puVar13[5] = uVar7;
                      puVar13[4] = uVar9;
                      puVar13[3] = uVar8;
                      puVar13[2] = uVar10;
                      puVar13[1] = uVar6;
                      if ((uVar24 & 0xff) != 0) {
                        FUN_004b6ed0(uVar24,&local_90);
                        goto LAB_0005f95c;
                      }
                      *(undefined8 *)(uVar22 + 0x18) = param_2;
                      *(ulong *)(uVar22 + 0x20) = param_3;
                      *(undefined8 *)(uVar22 + 0x90) = 0;
                      *(undefined8 *)(uVar22 + 0x40) = 0;
                      *(undefined8 *)(uVar22 + 0x48) = 0;
                      *(undefined8 *)(uVar22 + 0x50) = 0;
                      *(undefined8 *)(uVar22 + 0x58) = 0;
                      *(undefined1 *)(uVar22 + 0x80) = in_wzr;
                      *(undefined4 *)(uVar22 + 0x84) = 0;
                      *(undefined8 *)(uVar22 + 0xa8) = 0;
                      *(undefined8 *)(uVar22 + 8) = 0;
                      *(undefined8 *)(uVar22 + 0x10) = 0;
                      if (uVar22 + 0x178 < uVar22) {
LAB_0005f584:
                    /* WARNING: Does not return */
                        pcVar16 = (code *)SoftwareBreakpoint(0x5519,0x5f588);
                        (*pcVar16)();
                      }
                      lVar21 = FUN_0006156c(uVar22,8);
                      lVar25 = FUN_00063ffc();
                      if (lVar25 == 0) {
                        lVar21 = 0;
                      }
                      else {
                        FUN_0006402c(lVar21);
                      }
                      plVar26 = (long *)FUN_000614f8(uVar22);
                      FUN_001143a0(plVar26,0,0x100);
                      plVar26[0x1f] = 0;
                      *plVar26 = lVar21;
                      plVar26[1] = uVar22;
                      lVar27 = FUN_00063a50();
                      lVar25 = tpidr_el0;
                      if (*(long *)(lVar27 + 0x208) == -1) {
                        FUN_004b6f48();
                      }
                      else if (*(long *)(lVar25 + 0xf8) == 0) {
                        plVar26[2] = *(long *)(lVar25 + 0x10);
                        if (plVar26 + 0x20 < plVar26) goto LAB_0005f584;
                        FUN_00063cfc(plVar26);
                        auVar33 = FUN_000613ec(uVar22,param_4);
                        uVar23 = auVar33._8_8_;
                        uVar24 = auVar33._0_8_;
                        if ((*(long *)(uVar22 + 0x130) - uVar24) + *(long *)(uVar22 + 0x138) <
                            0x20000) {
                          if (param_4 != 0) {
                            if ((((param_3 + param_4 < param_3) || (uVar24 + param_4 < uVar24)) ||
                                (FUN_00117cc4(uVar24,param_3,param_4), uVar24 + param_4 < uVar24))
                               || ((uVar24 != 0 && (uVar24 + param_4 <= uVar24))))
                            goto LAB_0005f584;
                            *(ulong *)(uVar22 + 0x20) = uVar24;
                          }
                          FUN_000612d8(uVar22,FUN_004b6430);
                          puVar13[0x15] = uVar7;
                          puVar13[0x10] = uVar5;
                          puVar13[0x13] = uVar8;
                          puVar13[0x12] = uVar10;
                          puVar13[0x14] = uVar9;
                          puVar13[0x11] = uVar6;
                          puVar13[0x17] = uVar14;
                          puVar13[0x16] = uVar11;
                          thunk_FUN_00114330(puVar13 + 0x18,0x10);
                          puVar13[0x2d] = 0;
                          puVar13[0x28] = 0xbc;
                          puVar13[0x29] = 0xfa;
                          puVar13[0x2b] = 0;
                          puVar13[0x2a] = 5;
                          puVar13[0x2c] = 0;
                          puVar13[0x2f] = 0;
                          puVar13[0x2e] = 0;
                          puVar13[0x35] = auVar33[5];
                          puVar13[0x30] = auVar33[0];
                          puVar13[0x31] = auVar33[1];
                          puVar13[0x33] = auVar33[3];
                          puVar13[0x32] = auVar33[2];
                          puVar13[0x34] = auVar33[4];
                          puVar13[0x37] = auVar33[7];
                          puVar13[0x36] = auVar33[6];
                          puVar13[0x3d] = (char)((ulong)plVar26 >> 0x28);
                          puVar13[0x38] = (char)plVar26;
                          puVar13[0x39] = (char)((ulong)plVar26 >> 8);
                          puVar13[0x3b] = (char)((ulong)plVar26 >> 0x18);
                          puVar13[0x3a] = (char)((ulong)plVar26 >> 0x10);
                          puVar13[0x3c] = (char)((ulong)plVar26 >> 0x20);
                          puVar13[0x3f] = (char)((ulong)plVar26 >> 0x38);
                          puVar13[0x3e] = (char)((ulong)plVar26 >> 0x30);
                          uVar23 = FUN_00061488(uVar22);
                          puVar13[0x45] = (char)((ulong)uVar23 >> 0x28);
                          puVar13[0x40] = (char)uVar23;
                          puVar13[0x43] = (char)((ulong)uVar23 >> 0x18);
                          puVar13[0x42] = (char)((ulong)uVar23 >> 0x10);
                          puVar13[0x41] = (char)((ulong)uVar23 >> 8);
                          puVar13[0x44] = (char)((ulong)uVar23 >> 0x20);
                          puVar13[0x47] = (char)((ulong)uVar23 >> 0x38);
                          puVar13[0x46] = (char)((ulong)uVar23 >> 0x30);
                          uVar15 = uRam00000000004be1a8;
                          uVar23 = _DAT_004be1a0;
                          lVar21 = *(long *)(uVar22 + 0x28);
                          *puVar13 = (char)_DAT_004be1a0;
                          puVar13[8] = (char)uVar15;
                          puVar13[10] = (char)((ulong)uVar15 >> 0x10);
                          puVar13[0xb] = (char)((ulong)uVar15 >> 0x18);
                          puVar13[9] = (char)((ulong)uVar15 >> 8);
                          puVar13[0xd] = (char)((ulong)uVar15 >> 0x28);
                          puVar13[1] = (char)((ulong)uVar23 >> 8);
                          puVar13[0xc] = (char)((ulong)uVar15 >> 0x20);
                          puVar13[0xe] = (char)((ulong)uVar15 >> 0x30);
                          puVar13[0xf] = (char)((ulong)uVar15 >> 0x38);
                          puVar13[2] = (char)((ulong)uVar23 >> 0x10);
                          puVar13[3] = (char)((ulong)uVar23 >> 0x18);
                          puVar13[4] = (char)((ulong)uVar23 >> 0x20);
                          puVar13[5] = (char)((ulong)uVar23 >> 0x28);
                          puVar13[6] = (char)((ulong)uVar23 >> 0x30);
                          puVar13[7] = (char)((ulong)uVar23 >> 0x38);
                          uVar23 = 4;
                          CallSupervisor(0);
                          *puVar13 = 0;
                          puVar13[7] = 0;
                          puVar13[6] = 0;
                          puVar13[5] = 0;
                          puVar13[4] = 0;
                          puVar13[3] = 0;
                          puVar13[2] = 0;
                          puVar13[1] = 0;
                          if (lVar21 == 0) {
                            iVar20 = FUN_00060540();
                            if ((param_5 != 0) && (iVar20 == 0)) {
                              FUN_0005d84c(uVar22,1);
                            }
                            FUN_0005be84(uVar22,0);
                            *param_1 = uVar22;
                            goto LAB_0005f4b4;
                          }
                        }
                        FUN_004b6d60(uVar22,uVar23);
                        goto LAB_0005ef24;
                      }
                      FUN_004b6f20();
                      puVar32 = (ushort *)(uVar22 >> 0x38);
                      goto LAB_0005f938;
                    }
                    lVar27 = *(long *)(uVar22 + 0x28);
                    puVar13[1] = 0;
                    puVar13[4] = 0;
                    puVar13[5] = 0;
                    puVar13[2] = 0;
                    puVar13[3] = 0;
                    *puVar13 = 1;
                    puVar13[6] = 0;
                    puVar13[7] = 0;
                    puVar13[0xd] = (char)((ulong)lVar25 >> 0x28);
                    puVar13[8] = (char)lVar25;
                    puVar13[0xb] = (char)((ulong)lVar25 >> 0x18);
                    puVar13[10] = (char)((ulong)lVar25 >> 0x10);
                    puVar13[9] = (char)((ulong)lVar25 >> 8);
                    puVar13[0xc] = (char)((ulong)lVar25 >> 0x20);
                    puVar13[0xf] = (char)((ulong)lVar25 >> 0x38);
                    puVar13[0xe] = (char)((ulong)lVar25 >> 0x30);
                    CallSupervisor(0);
                    *puVar13 = 1;
                    puVar13[7] = 0;
                    puVar13[6] = 0;
                    puVar13[5] = 0;
                    puVar13[4] = 0;
                    puVar13[3] = 0;
                    puVar13[2] = 0;
                    puVar13[1] = 0;
                    if (lVar27 == 0) goto LAB_0005ef44;
                    FUN_004b6e74(lVar27,0x13);
                  }
                  FUN_004b6e9c(uVar22);
                }
                else {
                  _DAT_006b26bc = _DAT_006b26bc + 1;
                }
              }
              FUN_0019ae60(*(undefined8 *)(uVar22 + 0x28),6);
            }
            FUN_004b23d8(*(undefined8 *)(uVar22 + 0x70));
          }
        }
        else {
          _DAT_006b26b0 = _DAT_006b26b0 + 1;
        }
        FUN_004b23d8(lVar21);
      }
    }
    else {
      _DAT_006b26a8 = _DAT_006b26a8 + 1;
    }
    (*(code *)*local_b8)(local_c0);
  }
LAB_0005ef24:
  *puVar32 = *puVar32 - 1;
LAB_0005f4b4:
  if (local_70 == -0x2c8502b44bfffed6) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  FUN_0011d7e8();
}

