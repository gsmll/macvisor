
undefined8 FUN_00053aa4(undefined8 *param_1,uint param_2)

{
  code *pcVar1;
  
  if (param_1 <= param_1 + 2) {
    *param_1 = 0;
    param_1[1] = 0;
    if ((param_2 >> 1 & 1) != 0) {
      FUN_0005cf08(param_1,0x100);
    }
    return 0;
  }
                    /* WARNING: Does not return */
  pcVar1 = (code *)SoftwareBreakpoint(0x5519,0x53ae0);
  (*pcVar1)();
}

