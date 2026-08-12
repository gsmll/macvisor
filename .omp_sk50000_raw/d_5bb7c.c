
ulong * FUN_0005bb7c(void)

{
  ulong *puVar1;
  code *pcVar2;
  ulong *puVar3;
  
  puVar3 = (ulong *)FUN_0005acac(0x6b2568,1,1);
  puVar1 = (ulong *)*puVar3;
  if (*puVar3 == 0) {
    puVar3 = (ulong *)0x65c4e8;
  }
  else {
    do {
      puVar3 = puVar1;
      if (*puVar3 == 0) break;
      puVar1 = (ulong *)*puVar3;
    } while ((*(byte *)(puVar3 + 1) & 1) == 0);
    if (puVar3 + 0xf < puVar3) {
                    /* WARNING: Does not return */
      pcVar2 = (code *)SoftwareBreakpoint(0x5519,0x5bbc8);
      (*pcVar2)();
    }
  }
  return puVar3;
}

