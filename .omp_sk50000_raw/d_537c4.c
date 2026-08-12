
ulong * FUN_000537c4(void)

{
  ulong uVar1;
  code *pcVar2;
  long lVar3;
  ulong *puVar4;
  
  lVar3 = FUN_0005acac(0x6af8d8,2,5);
  if (lVar3 + 0x288U < lVar3 + 0x238U) {
                    /* WARNING: Does not return */
    pcVar2 = (code *)SoftwareBreakpoint(0x5519,0x53830);
    (*pcVar2)();
  }
  if (*(char *)(lVar3 + 0x278) == '\x01') {
    puVar4 = *(ulong **)(lVar3 + 0x268);
    if (puVar4 < *(ulong **)(lVar3 + 0x270)) {
      *(ulong **)(lVar3 + 0x268) = puVar4 + 8;
      return puVar4;
    }
    lVar3 = FUN_004b5ee0();
    uVar1 = (((ulong)*(byte *)(lVar3 + 0x12) << 0x10 | (ulong)*(byte *)(lVar3 + 0x13) << 0x18 |
             (ulong)*(ushort *)(lVar3 + 0x10)) << 0xc | (ulong)*(byte *)(lVar3 + 0x14) << 0x2c) +
            0x4000;
    puVar4 = (ulong *)FUN_0005acac(0x6af8d8,2,5);
    if (*puVar4 < uVar1) {
      *puVar4 = uVar1;
    }
    return puVar4;
  }
  *(undefined1 *)(lVar3 + 0x279) = 1;
                    /* WARNING: Subroutine does not return */
  FUN_004afae4(s_cna__p__expected_state__d__was___005bbd35);
}

