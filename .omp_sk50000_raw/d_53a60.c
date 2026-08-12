
undefined4 FUN_00053a60(ulong param_1,ulong param_2)

{
  code *pcVar1;
  int iVar2;
  undefined4 uVar3;
  
  if ((param_1 <= param_1 + 0x10) && (param_2 <= param_2 + 0x10)) {
    iVar2 = FUN_0005d38c();
    uVar3 = 0;
    if (iVar2 == 0) {
      uVar3 = 4;
    }
    return uVar3;
  }
                    /* WARNING: Does not return */
  pcVar1 = (code *)SoftwareBreakpoint(0x5519,0x53aa0);
  (*pcVar1)();
}

