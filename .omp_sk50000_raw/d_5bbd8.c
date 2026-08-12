
ulong FUN_0005bbd8(long param_1,long *param_2)

{
  ulong uVar1;
  ulong uVar2;
  bool bVar3;
  code *pcVar4;
  long lVar5;
  long lVar6;
  ulong uVar7;
  
  lVar6 = *(long *)(param_1 + 0x48);
  uVar7 = *(ulong *)(param_1 + 0x50);
  do {
    lVar5 = thunk_FUN_001144a0(uVar7,0x2f,lVar6);
    if (lVar5 == 0) {
      *param_2 = lVar6;
      return uVar7;
    }
    uVar1 = lVar5 + 1;
    uVar2 = uVar7 + lVar6;
    lVar6 = ~(lVar5 - uVar7) + lVar6;
    bVar3 = uVar7 <= uVar1;
    uVar7 = uVar1;
  } while (uVar1 <= uVar2 && bVar3);
                    /* WARNING: Does not return */
  pcVar4 = (code *)SoftwareBreakpoint(0x5519,0x5bc30);
  (*pcVar4)();
}

