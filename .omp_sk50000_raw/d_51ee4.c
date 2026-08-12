
ulong FUN_00051ee4(long param_1,undefined8 param_2)

{
  ulong uVar1;
  code *pcVar2;
  int iVar3;
  ulong uVar4;
  ulong uVar5;
  
  uVar5 = 0;
  uVar4 = 0;
  uVar1 = param_1 + 0x48;
  do {
    if (uVar4 == 0) {
      if (*(int *)(param_1 + 0x40) == 0) {
        return 0;
      }
      uVar4 = uVar1;
      if (param_1 + 0x98U < uVar1) goto LAB_00051f9c;
    }
    else {
      if ((uVar5 < uVar4 + 0x50) || (uVar4 + 0x50 < uVar4)) goto LAB_00051f9c;
      if (*(uint *)(param_1 + 0x40) == 0) {
        return 0;
      }
      if (uVar4 < uVar1) {
        return 0;
      }
      if (param_1 + -8 + (ulong)*(uint *)(param_1 + 0x40) * 0x50 <= uVar4) {
        return 0;
      }
      uVar4 = uVar4 + 0x50;
    }
    if (uVar4 == 0) {
      return 0;
    }
    uVar5 = uVar4 + 0x50;
    iVar3 = thunk_FUN_00114e50(param_2,uVar4,0x10);
  } while (iVar3 != 0);
  if (uVar4 <= uVar5) {
    return uVar4;
  }
LAB_00051f9c:
                    /* WARNING: Does not return */
  pcVar2 = (code *)SoftwareBreakpoint(0x5519,0x51fa0);
  (*pcVar2)();
}

