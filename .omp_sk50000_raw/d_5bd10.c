
void FUN_0005bd10(ulong *param_1)

{
  code *pcVar1;
  ulong uVar2;
  ulong uVar3;
  
  uVar2 = FUN_0005acac(0x6b2568,1,1);
  while ((uVar3 = *(ulong *)(uVar2 + 0x28), uVar3 <= uVar3 + 0x28 &&
         (*param_1 = uVar3, uVar2 <= uVar2 + 0x90))) {
    if (*(ulong *)(uVar2 + 0x28) == uVar3) {
      *(ulong *)(uVar2 + 0x28) = (ulong)param_1;
      return;
    }
  }
                    /* WARNING: Does not return */
  pcVar1 = (code *)SoftwareBreakpoint(0x5519,0x5bd7c);
  (*pcVar1)();
}

