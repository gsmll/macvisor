
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00054414(long param_1,ulong param_2)

{
  ulong uVar1;
  ulong uVar2;
  ulong uVar3;
  code *pcVar4;
  ulong uVar5;
  long lStack_60;
  long lStack_58;
  
  uVar5 = 0;
  lStack_58 = -0x2c8502b44bfffed6;
  while( true ) {
    uVar2 = param_2 - uVar5;
    if (param_2 < uVar5 || uVar2 == 0) {
      if (lStack_58 == -0x2c8502b44bfffed6) {
        return;
      }
                    /* WARNING: Subroutine does not return */
      FUN_0011d7e8();
    }
    uVar3 = _DAT_006bf5b0 * 5;
    uVar1 = _DAT_006bf5b0 * 0x280;
    _DAT_006bf5b8 = _DAT_006bf5b8 ^ _DAT_006bf5b0;
    _DAT_006bf5b0 =
         (_DAT_006bf5b0 >> 0x28 | _DAT_006bf5b0 << 0x18) ^ _DAT_006bf5b8 << 0x10 ^ _DAT_006bf5b8;
    _DAT_006bf5b8 = _DAT_006bf5b8 >> 0x1b | _DAT_006bf5b8 << 0x25;
    lStack_60 = (uVar3 >> 0x39 | uVar1) * 9;
    if (7 < uVar2) {
      uVar2 = 8;
    }
    uVar1 = param_1 + uVar5;
    FUN_00117cc4(uVar1,&lStack_60,uVar2);
    if (uVar1 + uVar2 < uVar1) break;
    uVar5 = uVar2 + uVar5;
  }
                    /* WARNING: Does not return */
  pcVar4 = (code *)SoftwareBreakpoint(0x5519,0x116d5c);
  (*pcVar4)();
}

