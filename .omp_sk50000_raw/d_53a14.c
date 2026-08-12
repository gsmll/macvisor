
undefined8 FUN_00053a14(undefined8 *param_1)

{
  code *pcVar1;
  
  if (param_1 <= param_1 + 2) {
    *param_1 = 0;
    param_1[1] = 0;
    return 0;
  }
                    /* WARNING: Does not return */
  pcVar1 = (code *)SoftwareBreakpoint(0x5519,0x53a30);
  (*pcVar1)();
}

