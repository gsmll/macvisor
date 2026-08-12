
undefined8 FUN_00053a30(ulong param_1)

{
  code *pcVar1;
  
  if (param_1 <= param_1 + 0x10) {
    FUN_0005d394(param_1,0);
    return 0;
  }
                    /* WARNING: Does not return */
  pcVar1 = (code *)SoftwareBreakpoint(0x5519,0x53a60);
  (*pcVar1)();
}

