
void FUN_0005bce0(long param_1)

{
  code *pcVar1;
  
  if (param_1 + 8U <= param_1 + 0xcU) {
    FUN_0005d470(param_1 + 8U,FUN_0005bd10);
    return;
  }
                    /* WARNING: Does not return */
  pcVar1 = (code *)SoftwareBreakpoint(0x5519,0x5bd10);
  (*pcVar1)();
}

