
void FUN_000549c0(ulong param_1,long param_2)

{
  long lVar1;
  code *pcVar2;
  ulong uVar3;
  
  if (param_2 != 0) {
    lVar1 = param_2 * 0x78;
    uVar3 = param_1;
    do {
      if (((uVar3 < param_1) || (param_1 + lVar1 < uVar3 + 0x78)) || (uVar3 + 0x78 < uVar3)) {
                    /* WARNING: Does not return */
        pcVar2 = (code *)SoftwareBreakpoint(0x5519,0x54a4c);
        (*pcVar2)();
      }
      if (((uint)*(undefined8 *)(uVar3 + 8) >> 7 & 1) != 0) {
        FUN_00054a4c(uVar3,*(undefined8 *)(uVar3 + 0x38),*(undefined8 *)(uVar3 + 0x20),
                     *(undefined8 *)(uVar3 + 0x50),*(undefined8 *)(uVar3 + 0x48));
      }
      FUN_0005baf0(uVar3);
      uVar3 = uVar3 + 0x78;
      param_2 = param_2 + -1;
    } while (param_2 != 0);
  }
  return;
}

