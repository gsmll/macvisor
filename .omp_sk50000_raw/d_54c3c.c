
void FUN_00054c3c(ulong param_1)

{
  code *pcVar1;
  long lVar2;
  
  lVar2 = FUN_0005bb7c();
  if (lVar2 == 0) {
    thunk_FUN_00114330(param_1,0x10);
    return;
  }
  FUN_00117cc4(param_1,lVar2 + 0x10,0x10);
  if (param_1 <= param_1 + 0x10) {
    return;
  }
                    /* WARNING: Does not return */
  pcVar1 = (code *)SoftwareBreakpoint(0x5519,0x54c9c);
  (*pcVar1)();
}

