
void FUN_00053ae0(ulong param_1)

{
  code *pcVar1;
  
  if (param_1 <= param_1 + 0x10) {
    FUN_0005cb9c();
    return;
  }
                    /* WARNING: Does not return */
  pcVar1 = (code *)SoftwareBreakpoint(0x5519,0x53af4);
  (*pcVar1)();
}

