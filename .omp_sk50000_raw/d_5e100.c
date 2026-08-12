
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0005e100(ulong param_1,undefined1 *param_2)

{
  uint uVar1;
  undefined8 uVar2;
  undefined8 uVar3;
  ushort uVar4;
  byte bVar5;
  undefined8 uVar6;
  char *pcVar7;
  uint uVar8;
  ulong uVar9;
  ulong uVar10;
  uint uVar11;
  ulong uVar12;
  int iVar13;
  undefined8 local_80;
  undefined8 uStack_78;
  undefined8 local_70;
  undefined8 uStack_68;
  undefined1 auStack_58 [32];
  long local_38;
  
  local_38 = -0x2c8502b44bfffed6;
  uVar6 = FUN_00034f70();
  uVar3 = uRam00000000004be038;
  uVar2 = _DAT_004be030;
  iVar13 = (int)param_2;
  if (iVar13 < 9) {
    if (iVar13 != 6) {
      if (iVar13 != 8) goto LAB_0005e490;
      param_2 = (undefined1 *)tpidrro_el0;
      uStack_78 = uRam00000000004be038;
      local_80 = _DAT_004be030;
      *param_2 = (char)_DAT_004be030;
      param_2[0xd] = (char)((ulong)uVar3 >> 0x28);
      param_2[8] = (char)uVar3;
      param_2[0xb] = (char)((ulong)uVar3 >> 0x18);
      param_2[10] = (char)((ulong)uVar3 >> 0x10);
      param_2[9] = (char)((ulong)uVar3 >> 8);
      param_2[5] = (char)((ulong)uVar2 >> 0x28);
      param_2[3] = (char)((ulong)uVar2 >> 0x18);
      param_2[2] = (char)((ulong)uVar2 >> 0x10);
      param_2[0xc] = (char)((ulong)uVar3 >> 0x20);
      param_2[1] = (char)((ulong)uVar2 >> 8);
      param_2[0xf] = (char)((ulong)uVar3 >> 0x38);
      param_2[0xe] = (char)((ulong)uVar3 >> 0x30);
      param_2[4] = (char)((ulong)uVar2 >> 0x20);
      param_2[7] = (char)((ulong)uVar2 >> 0x38);
      param_2[6] = (char)((ulong)uVar2 >> 0x30);
      param_2[0x15] = 0;
      param_2[0x11] = 0;
      param_2[0x10] = 0;
      param_2[0x13] = 0;
      param_2[0x12] = 0;
      param_2[0x14] = 0;
      param_2[0x17] = 0;
      param_2[0x16] = 0;
      CallSupervisor(3);
      if ((param_1 & 0xff) != 0) {
        FUN_004b6c50(param_1,auStack_58,1);
        goto LAB_0005e22c;
      }
      goto LAB_0005e33c;
    }
  }
  else {
LAB_0005e22c:
    uVar3 = uRam00000000004bb1a8;
    uVar2 = _DAT_004bb1a0;
    if ((int)param_2 == 9) {
      param_2 = (undefined1 *)tpidrro_el0;
      uStack_68 = uRam00000000004bb1a8;
      local_70 = _DAT_004bb1a0;
      *param_2 = (char)_DAT_004bb1a0;
      param_2[0xd] = (char)((ulong)uVar3 >> 0x28);
      param_2[8] = (char)uVar3;
      param_2[0xb] = (char)((ulong)uVar3 >> 0x18);
      param_2[10] = (char)((ulong)uVar3 >> 0x10);
      param_2[9] = (char)((ulong)uVar3 >> 8);
      param_2[5] = (char)((ulong)uVar2 >> 0x28);
      param_2[3] = (char)((ulong)uVar2 >> 0x18);
      param_2[2] = (char)((ulong)uVar2 >> 0x10);
      param_2[0xc] = (char)((ulong)uVar3 >> 0x20);
      param_2[1] = (char)((ulong)uVar2 >> 8);
      param_2[0xf] = (char)((ulong)uVar3 >> 0x38);
      param_2[0xe] = (char)((ulong)uVar3 >> 0x30);
      param_2[4] = (char)((ulong)uVar2 >> 0x20);
      param_2[7] = (char)((ulong)uVar2 >> 0x38);
      param_2[6] = (char)((ulong)uVar2 >> 0x30);
      param_2[0x15] = 0;
      param_2[0x11] = 0;
      param_2[0x10] = 0;
      param_2[0x13] = 0;
      param_2[0x12] = 0;
      param_2[0x14] = 0;
      param_2[0x17] = 0;
      param_2[0x16] = 0;
      CallSupervisor(3);
      if ((param_1 & 0xff) != 0) {
        bVar5 = FUN_004b6c04(param_1,auStack_58,1);
        if (9 < bVar5) {
          FUN_00117cc4(&local_80,&DAT_004be180,0x20);
          FUN_0000178c(&local_80,0x20);
          return;
        }
        switch(bVar5) {
        default:
          pcVar7 = s_L4_ErrorCodeSuccess_004be040;
          break;
        case 1:
          pcVar7 = s_L4_ErrorCodePreempted_004be060;
          break;
        case 2:
          pcVar7 = s_L4_ErrorCodeCanceled_004be080;
          break;
        case 3:
          pcVar7 = s_L4_ErrorCodeTruncated_004be0a0;
          break;
        case 4:
          pcVar7 = s_L4_ErrorCodeCapInvalid_004be0c0;
          break;
        case 5:
          pcVar7 = s_L4_ErrorCodeSlotInvalid_004be0e0;
          break;
        case 6:
          pcVar7 = s_L4_ErrorCodeMethodInvalid_004be100;
          break;
        case 7:
          pcVar7 = s_L4_ErrorCodeArgumentInvalid_004be120;
          break;
        case 8:
          pcVar7 = s_L4_ErrorCodeOperationInvalid_004be140;
          break;
        case 9:
          pcVar7 = s_L4_ErrorCodePermissionInvalid_004be160;
        }
        FUN_00117cc4(&local_80,pcVar7,0x20);
        return;
      }
LAB_0005e33c:
      param_2[0x1c0] = (char)uVar6;
      param_2[0x1c5] = (char)((ulong)uVar6 >> 0x28);
      param_2[0x1c3] = (char)((ulong)uVar6 >> 0x18);
      param_2[0x1c2] = (char)((ulong)uVar6 >> 0x10);
      param_2[0x1c1] = (char)((ulong)uVar6 >> 8);
      param_2[0x1c4] = (char)((ulong)uVar6 >> 0x20);
      param_2[0x1c7] = (char)((ulong)uVar6 >> 0x38);
      param_2[0x1c6] = (char)((ulong)uVar6 >> 0x30);
      uVar4 = _DAT_00689e9c;
      uVar9 = (ulong)_DAT_00689e9c;
      uVar10 = (ulong)DAT_00689e9f;
      uVar12 = (ulong)DAT_00689e9e;
      uVar1 = (uint)(ushort)s_L4_ErrorCodeMethodInvalid_00689ea0._0_2_;
      uVar8 = (uint)(byte)s_L4_ErrorCodeMethodInvalid_00689ea0[2];
      uVar11 = (uint)(byte)s_L4_ErrorCodeMethodInvalid_00689ea0[3];
      *param_2 = 0x40;
      param_2[1] = 0;
      param_2[4] = 0;
      param_2[5] = 0;
      param_2[2] = 3;
      param_2[3] = 0;
      param_2[6] = 0;
      param_2[7] = 0;
      CallSupervisor(0);
      *param_2 = 0x40;
      param_2[7] = 0;
      param_2[6] = 0;
      param_2[5] = 0;
      param_2[4] = 0;
      param_2[3] = 0;
      param_2[2] = 3;
      param_2[1] = 0;
      if ((uVar4 & 0xff) != 0) {
        FUN_004b6c9c(uVar12 << 0x10 | uVar10 << 0x18 | uVar9 |
                     (ulong)(uVar8 << 0x10 | uVar11 << 0x18 | uVar1) << 0x20,auStack_58);
LAB_0005e490:
                    /* WARNING: Subroutine does not return */
        FUN_0005b190(0,s_invalid_cap_type_to_identify___u_005bcac1);
      }
      if (local_38 == -0x2c8502b44bfffed6) {
        FUN_004b23d8(uVar6,0);
        return;
      }
      goto LAB_0005e484;
    }
    if ((int)param_2 != 0xd) goto LAB_0005e490;
  }
  if (local_38 == -0x2c8502b44bfffed6) {
    return;
  }
LAB_0005e484:
                    /* WARNING: Subroutine does not return */
  FUN_0011d7e8();
}

