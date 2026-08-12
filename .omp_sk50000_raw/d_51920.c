
byte FUN_00051920(long param_1,ulong param_2)

{
  ulong uVar1;
  short *psVar2;
  ulong uVar3;
  code *pcVar4;
  byte bVar5;
  ulong uVar6;
  
  if (param_1 != 0) {
    if ((param_2 & 0x3fff) != 0) {
                    /* WARNING: Does not return */
      pcVar4 = (code *)SoftwareBreakpoint(1,0x519c8);
      (*pcVar4)();
    }
    if (param_2 < 0xffffffffffffc000) {
      bVar5 = 0;
      uVar1 = param_2 + 0x4000;
      uVar6 = (ulong)*(ushort *)(param_1 + 4);
      do {
        uVar3 = 0;
        if (uVar6 != 0) {
          uVar3 = (param_2 - *(long *)(param_1 + 8)) / uVar6;
        }
        if (*(ushort *)(param_1 + 0x14) <= uVar3) {
          return bVar5;
        }
        psVar2 = (short *)(param_1 + 0x16 + uVar3 * 2);
        if (psVar2 + 1 < psVar2 ||
            (short *)(param_1 + 0x16 + (ulong)*(ushort *)(param_1 + 0x14) * 2) < psVar2 + 1) {
                    /* WARNING: Does not return */
          pcVar4 = (code *)SoftwareBreakpoint(0x5519,0x519c4);
          (*pcVar4)();
        }
        bVar5 = *psVar2 != -1 | bVar5;
        param_2 = param_2 + uVar6;
      } while (param_2 < uVar1);
      return bVar5;
    }
  }
  return 0;
}

