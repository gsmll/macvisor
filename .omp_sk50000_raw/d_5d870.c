
void FUN_0005d870(long param_1,int param_2)

{
  undefined1 *puVar1;
  byte bVar2;
  long lVar3;
  ulong uVar4;
  char *pcVar5;
  undefined8 extraout_x8;
  undefined1 auStack_58 [32];
  long local_38;
  
  local_38 = -0x2c8502b44bfffed6;
  if ((param_2 == 0) || ((*(byte *)(param_1 + 0x48) >> 3 & 1) != 0)) {
    return;
  }
  lVar3 = FUN_00034f70();
  if (lVar3 != 0) {
    uVar4 = FUN_00061630(param_1);
    puVar1 = (undefined1 *)tpidrro_el0;
    puVar1[5] = 0;
    puVar1[3] = 0;
    puVar1[2] = 0;
    puVar1[1] = 2;
    *puVar1 = 0;
    puVar1[4] = 0;
    puVar1[7] = 0;
    puVar1[6] = 0;
    CallSupervisor(3);
    if ((uVar4 & 0xff) != 0) {
      bVar2 = FUN_004b6984(uVar4,auStack_58,0x200);
      if (bVar2 < 10) {
        switch(bVar2) {
        default:
          pcVar5 = s_L4_ErrorCodeSuccess_004be040;
          break;
        case 1:
          pcVar5 = s_L4_ErrorCodePreempted_004be060;
          break;
        case 2:
          pcVar5 = s_L4_ErrorCodeCanceled_004be080;
          break;
        case 3:
          pcVar5 = s_L4_ErrorCodeTruncated_004be0a0;
          break;
        case 4:
          pcVar5 = s_L4_ErrorCodeCapInvalid_004be0c0;
          break;
        case 5:
          pcVar5 = s_L4_ErrorCodeSlotInvalid_004be0e0;
          break;
        case 6:
          pcVar5 = s_L4_ErrorCodeMethodInvalid_004be100;
          break;
        case 7:
          pcVar5 = s_L4_ErrorCodeArgumentInvalid_004be120;
          break;
        case 8:
          pcVar5 = s_L4_ErrorCodeOperationInvalid_004be140;
          break;
        case 9:
          pcVar5 = s_L4_ErrorCodePermissionInvalid_004be160;
        }
        FUN_00117cc4(extraout_x8,pcVar5,0x20);
        return;
      }
      FUN_00117cc4(extraout_x8,&DAT_004be180,0x20);
      FUN_0000178c(extraout_x8,0x20);
      return;
    }
    FUN_004b69d0(puVar1,lVar3,(byte *)(param_1 + 0x48));
  }
  if (local_38 == -0x2c8502b44bfffed6) {
    FUN_004b23d8(lVar3);
    return;
  }
                    /* WARNING: Subroutine does not return */
  FUN_0011d7e8();
}

