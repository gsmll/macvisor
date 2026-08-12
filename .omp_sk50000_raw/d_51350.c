
void FUN_00051350(undefined8 param_1,byte param_2)

{
  char *pcVar1;
  
  if (9 < param_2) {
    FUN_00117cc4(param_1,&DAT_004bccc0,0x20);
    FUN_0000178c(param_1,0x20);
    return;
  }
  switch(param_2) {
  default:
    pcVar1 = s_L4_ErrorCodeSuccess_004bcb80;
    break;
  case 1:
    pcVar1 = s_L4_ErrorCodePreempted_004bcba0;
    break;
  case 2:
    pcVar1 = s_L4_ErrorCodeCanceled_004bcbc0;
    break;
  case 3:
    pcVar1 = s_L4_ErrorCodeTruncated_004bcbe0;
    break;
  case 4:
    pcVar1 = s_L4_ErrorCodeCapInvalid_004bcc00;
    break;
  case 5:
    pcVar1 = s_L4_ErrorCodeSlotInvalid_004bcc20;
    break;
  case 6:
    pcVar1 = s_L4_ErrorCodeMethodInvalid_004bcc40;
    break;
  case 7:
    pcVar1 = s_L4_ErrorCodeArgumentInvalid_004bcc60;
    break;
  case 8:
    pcVar1 = s_L4_ErrorCodeOperationInvalid_004bcc80;
    break;
  case 9:
    pcVar1 = s_L4_ErrorCodePermissionInvalid_004bcca0;
  }
  FUN_00117cc4(param_1,pcVar1,0x20);
  return;
}

