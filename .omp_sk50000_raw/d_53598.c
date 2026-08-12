
ulong FUN_00053598(long param_1)

{
  ulong uVar1;
  code *pcVar2;
  long lVar3;
  long lVar4;
  
  if (param_1 == 1) {
    lVar4 = 0x2b8;
  }
  else {
    if (param_1 == 2) {
      lVar4 = FUN_0005acac(0x6af8d8,2,5);
      uVar1 = lVar4 + 0x2c0;
      if (uVar1 == 0) {
        return 0;
      }
      if ((uVar1 <= lVar4 + 0x2c8U) && (lVar4 + 0x2b0U <= uVar1)) {
        return uVar1;
      }
                    /* WARNING: Does not return */
      pcVar2 = (code *)SoftwareBreakpoint(0x5519,0x53604);
      (*pcVar2)();
    }
    if (param_1 != 3) {
      return 0;
    }
    lVar4 = 0x2b0;
  }
  lVar3 = FUN_0005acac(0x6af8d8,2,5);
  return lVar3 + lVar4;
}

