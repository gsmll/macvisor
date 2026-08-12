
void FUN_00054a4c(long param_1,undefined8 param_2,long param_3,undefined8 param_4,undefined8 param_5
                 ,undefined8 param_6)

{
  code *pcVar1;
  long lVar2;
  long lVar3;
  ulong uVar4;
  undefined8 local_68;
  undefined8 local_60;
  long lStack_58;
  
  lVar2 = FUN_00051d3c(param_2);
  lVar3 = FUN_00051dc0(param_2);
  local_60 = 0;
  lStack_58 = 0;
  local_68 = 0;
  FUN_00051ff4(param_2,&lStack_58,&local_60,&local_68);
  *(undefined8 *)(param_1 + 0x48) = param_5;
  *(undefined8 *)(param_1 + 0x50) = param_4;
  *(long *)(param_1 + 0x20) = param_3;
  *(long *)(param_1 + 0x28) = lVar2 + param_3;
  *(long *)(param_1 + 0x30) = lVar3 - lVar2;
  *(undefined8 *)(param_1 + 0x38) = param_2;
  *(long *)(param_1 + 0x58) = lStack_58;
  *(long *)(param_1 + 0x60) = lStack_58 << 4;
  *(undefined8 *)(param_1 + 0x68) = local_60;
  *(undefined8 *)(param_1 + 0x70) = local_68;
  *(undefined8 *)(param_1 + 8) = param_6;
  uVar4 = FUN_00051fbc(param_2);
  if (uVar4 == 0) {
    thunk_FUN_00114330(param_1 + 0x10,0x10);
  }
  else if ((uVar4 + 0x10 < uVar4) ||
          (FUN_00117cc4(param_1 + 0x10U,uVar4,0x10), param_1 + 0x20U < param_1 + 0x10U)) {
                    /* WARNING: Does not return */
    pcVar1 = (code *)SoftwareBreakpoint(0x5519,0x54b1c);
    (*pcVar1)();
  }
  return;
}

