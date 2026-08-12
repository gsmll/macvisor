
ulong FUN_00051e5c(undefined8 param_1,undefined8 param_2)

{
  code *pcVar1;
  int iVar2;
  ulong uVar3;
  ulong uVar4;
  
  uVar4 = 0;
  uVar3 = 0;
  do {
    if ((uVar3 != 0) && ((uVar4 < uVar3 + 0x48 || (uVar3 + 0x48 < uVar3)))) goto LAB_00051ee0;
    uVar3 = FUN_00051e0c(param_1,uVar3);
    if (uVar3 == 0) {
      return 0;
    }
    uVar4 = uVar3 + 0x48;
    iVar2 = thunk_FUN_00114e50(param_2,uVar3 + 8,0x10);
  } while (iVar2 != 0);
  if (uVar3 <= uVar4) {
    return uVar3;
  }
LAB_00051ee0:
                    /* WARNING: Does not return */
  pcVar1 = (code *)SoftwareBreakpoint(0x5519,0x51ee4);
  (*pcVar1)();
}

