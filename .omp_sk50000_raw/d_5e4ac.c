
void FUN_0005e4ac(byte param_1)

{
  char *pcVar1;
  
  if (9 < param_1) {
    FUN_00117cc4(&stack0x00000010,&DAT_004be180,0x20);
    FUN_0000178c(&stack0x00000010,0x20);
    return;
  }
  switch(param_1) {
  default:
    pcVar1 = s_L4_ErrorCodeSuccess_004be040;
    break;
  case 1:
    pcVar1 = s_L4_ErrorCodePreempted_004be060;
    break;
  case 2:
    pcVar1 = s_L4_ErrorCodeCanceled_004be080;
    break;
  case 3:
    pcVar1 = s_L4_ErrorCodeTruncated_004be0a0;
    break;
  case 4:
    pcVar1 = s_L4_ErrorCodeCapInvalid_004be0c0;
    break;
  case 5:
    pcVar1 = s_L4_ErrorCodeSlotInvalid_004be0e0;
    break;
  case 6:
    pcVar1 = s_L4_ErrorCodeMethodInvalid_004be100;
    break;
  case 7:
    pcVar1 = s_L4_ErrorCodeArgumentInvalid_004be120;
    break;
  case 8:
    pcVar1 = s_L4_ErrorCodeOperationInvalid_004be140;
    break;
  case 9:
    pcVar1 = s_L4_ErrorCodePermissionInvalid_004be160;
  }
  FUN_00117cc4(&stack0x00000010,pcVar1,0x20);
  return;
}

