
void FUN_0005d03c(long *param_1,ulong param_2)

{
  code *pcVar1;
  ulong uVar2;
  ulong uVar3;
  ulong uVar4;
  
  uVar3 = param_1[3];
  if (uVar3 != 0) {
    uVar4 = 0;
    do {
      uVar2 = *(ulong *)(param_1[2] + uVar4 * 8);
      if (uVar2 != 0) {
        if (uVar2 + 0x38 < uVar2) {
                    /* WARNING: Does not return */
          pcVar1 = (code *)SoftwareBreakpoint(0x5519,0x5d130);
          (*pcVar1)();
        }
        FUN_0005d03c(uVar2,param_2);
        uVar3 = param_1[3];
      }
      uVar4 = uVar4 + 1;
    } while (uVar4 < uVar3);
  }
  if ((param_2 & 1) == 0) {
    if ((param_1[4] != 1) && ((code *)param_1[1] != (code *)0x0)) {
      if (*param_1 == 0x706c6174) {
        (*(code *)param_1[1])();
      }
      else {
        FUN_000600f0(0x40000,&DAT_0005d130,param_1);
      }
      param_1[4] = 1;
    }
  }
  else if ((param_1[5] != 1) && ((code *)param_1[6] != (code *)0x0)) {
    (*(code *)param_1[6])();
    param_1[5] = 1;
  }
  return;
}

