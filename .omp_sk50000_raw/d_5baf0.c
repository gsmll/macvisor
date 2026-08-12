
void FUN_0005baf0(ulong *param_1)

{
  short sVar1;
  code *pcVar2;
  ulong *puVar3;
  ulong uVar4;
  
  puVar3 = (ulong *)FUN_0005acac(0x6b2568,1,1);
  sVar1 = (short)puVar3[1];
  *(short *)(puVar3 + 1) = sVar1 + 1;
  *(short *)(param_1 + 8) = sVar1;
  while ((uVar4 = *puVar3, uVar4 <= uVar4 + 0x78 && (*param_1 = uVar4, puVar3 <= puVar3 + 0x12))) {
    if (*puVar3 == uVar4) {
      *puVar3 = (ulong)param_1;
      return;
    }
  }
                    /* WARNING: Does not return */
  pcVar2 = (code *)SoftwareBreakpoint(0x5519,0x5bb68);
  (*pcVar2)();
}

