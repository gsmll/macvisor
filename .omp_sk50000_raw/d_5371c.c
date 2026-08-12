
void FUN_0005371c(void)

{
  code *pcVar1;
  long lVar2;
  ulong uVar3;
  
  lVar2 = FUN_0005acac(0x6af8d8,2,5);
  if (lVar2 + 0x288U < lVar2 + 0x238U) {
                    /* WARNING: Does not return */
    pcVar1 = (code *)SoftwareBreakpoint(0x5519,0x537a0);
    (*pcVar1)();
  }
  if (*(char *)(lVar2 + 0x278) == '\x02') {
    *(undefined1 *)(lVar2 + 0x278) = 3;
    for (uVar3 = *(ulong *)(lVar2 + 600); uVar3 < *(ulong *)(lVar2 + 0x260); uVar3 = uVar3 + 0x40) {
      FUN_004b23d8(uVar3);
    }
    return;
  }
  *(undefined1 *)(lVar2 + 0x279) = 2;
                    /* WARNING: Subroutine does not return */
  FUN_004afae4(s_cna__p__expected_state__d__was___005bbd35);
}

