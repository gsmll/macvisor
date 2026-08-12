
undefined8 FUN_0005fd2c(ulong param_1)

{
  code *pcVar1;
  long lVar2;
  
  lVar2 = FUN_00060524();
  if ((*(undefined1 **)(lVar2 + 0x168) <= &stack0xfffffffffffffff0) &&
     (&stack0xfffffffffffffff0 < *(undefined1 **)(lVar2 + 0x170))) {
    if (param_1 <= (ulong)((long)&stack0xfffffffffffffff0 - (long)*(undefined1 **)(lVar2 + 0x168)))
    {
      return 1;
    }
                    /* WARNING: Subroutine does not return */
    FUN_004afae4(s_requested__zu_stack_bytes__only_h_005bd047);
  }
                    /* WARNING: Does not return */
  pcVar1 = (code *)SoftwareBreakpoint(1,0x5fd90);
  (*pcVar1)();
}

