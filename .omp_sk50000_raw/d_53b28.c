
undefined8 FUN_00053b28(ulong param_1)

{
  code *pcVar1;
  
  if (param_1 <= param_1 + 0x10) {
    FUN_0005ce54();
    return 0;
  }
                    /* WARNING: Does not return */
  pcVar1 = (code *)SoftwareBreakpoint(0x5519,0x53b54);
  (*pcVar1)();
}

