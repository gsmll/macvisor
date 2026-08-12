
void FUN_00053634(ulong *param_1,long *param_2,ulong *param_3)

{
  code *pcVar1;
  long lVar2;
  ulong uVar3;
  ulong uVar4;
  long lVar5;
  
  lVar2 = FUN_0005acac(0x6af8d8,2,5);
  if (lVar2 + 0x238U <= lVar2 + 0x288U) {
    if (*(char *)(lVar2 + 0x278) != '\x01') {
      *(undefined1 *)(lVar2 + 0x279) = 1;
                    /* WARNING: Subroutine does not return */
      FUN_004afae4(s_cna__p__expected_state__d__was___005bbd35);
    }
    *(undefined1 *)(lVar2 + 0x278) = 2;
    uVar3 = *(ulong *)(lVar2 + 0x238);
    uVar4 = *(ulong *)(lVar2 + 0x240);
    if ((((((uint)uVar3 | (uint)uVar4) & 0x3fff) == 0) && (uVar4 == *(ulong *)(lVar2 + 0x270))) &&
       (uVar3 <= *(ulong *)(lVar2 + 0x268) && *(ulong *)(lVar2 + 0x268) <= uVar4)) {
      *param_1 = uVar3;
      lVar5 = *(long *)(lVar2 + 0x268);
      *param_2 = lVar5;
      *param_3 = (ulong)(*(long *)(lVar2 + 0x270) - lVar5) >> 6;
      return;
    }
    FUN_004b5e9c();
  }
                    /* WARNING: Does not return */
  pcVar1 = (code *)SoftwareBreakpoint(0x5519,0x536f8);
  (*pcVar1)();
}

