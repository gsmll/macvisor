
void FUN_0005e8a4(ulong *param_1,ulong param_2,undefined8 param_3)

{
  ulong uVar1;
  ulong uVar2;
  ulong uVar3;
  code *pcVar4;
  uint uVar5;
  ulong uVar6;
  undefined1 uStack_29;
  
  if (1 < param_1[1]) {
    if ((param_2 & 1) == 0) {
      uVar6 = param_1[1];
    }
    else {
      uVar5 = FUN_00116bb4(&uStack_29,1,param_3,&stack0x00000000);
      if ((int)uVar5 < 0) {
        return;
      }
      uVar6 = param_1[1];
      if (uVar6 <= uVar5) {
        return;
      }
    }
    uVar5 = FUN_00116bb4(*param_1,uVar6,param_3,&stack0x00000000);
    uVar6 = (ulong)(uVar5 & ((int)uVar5 >> 0x1f ^ 0xffffffffU));
    uVar2 = *param_1;
    uVar3 = param_1[1];
    if (uVar3 <= uVar6) {
      uVar6 = uVar3 - 1;
    }
    uVar1 = uVar2 + uVar6;
    if (uVar2 + uVar3 < uVar1 || uVar1 < uVar2) {
                    /* WARNING: Does not return */
      pcVar4 = (code *)SoftwareBreakpoint(0x5519,0x5e940);
      (*pcVar4)();
    }
    *param_1 = uVar1;
    param_1[1] = uVar3 - uVar6;
  }
  return;
}

