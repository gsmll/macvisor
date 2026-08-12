
void FUN_0005c0ac(void)

{
  code *pcVar1;
  long lVar2;
  ulong *puVar3;
  ulong uVar4;
  
  lVar2 = FUN_0005acac(0x6b2568,1,1);
  while( true ) {
    puVar3 = *(ulong **)(lVar2 + 0x20);
    if (puVar3 == (ulong *)0x0) {
      return;
    }
    if ((puVar3 + 0x2f < puVar3) || (uVar4 = *puVar3 & 0xfffffffff, uVar4 + 0x178 < uVar4)) break;
    if (*(ulong **)(lVar2 + 0x20) == puVar3) {
      *(ulong *)(lVar2 + 0x20) = uVar4;
      *puVar3 = 0;
      return;
    }
  }
                    /* WARNING: Does not return */
  pcVar1 = (code *)SoftwareBreakpoint(0x5519,0x5c11c);
  (*pcVar1)();
}

