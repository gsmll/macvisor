
undefined4 FUN_00053af4(ulong param_1)

{
  code *pcVar1;
  int iVar2;
  undefined4 uVar3;
  
  if (param_1 <= param_1 + 0x10) {
    iVar2 = FUN_0005cdbc();
    uVar3 = 0;
    if (iVar2 == 0) {
      uVar3 = 3;
    }
    return uVar3;
  }
                    /* WARNING: Does not return */
  pcVar1 = (code *)SoftwareBreakpoint(0x5519,0x53b28);
  (*pcVar1)();
}

