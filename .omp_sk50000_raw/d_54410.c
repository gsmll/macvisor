
void thunk_FUN_0006037c(void)

{
  code *pcVar1;
  long lVar2;
  
  lVar2 = FUN_00060524();
  if (lVar2 + 0x104U <= lVar2 + 0x108U) {
    return;
  }
                    /* WARNING: Does not return */
  pcVar1 = (code *)SoftwareBreakpoint(0x5519,0x603ac);
  (*pcVar1)();
}

