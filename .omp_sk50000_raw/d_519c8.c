
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

ulong FUN_000519c8(long param_1,ulong param_2)

{
  ulong uVar1;
  uint *puVar2;
  ulong uVar3;
  ulong uVar4;
  uint uVar5;
  code *pcVar6;
  ulong uVar7;
  uint *puVar8;
  
  if ((_DAT_006af890 != 0) && (uVar7 = (ulong)*_DAT_006af898, *_DAT_006af898 != 0)) {
    puVar8 = _DAT_006af898 + 1;
    puVar2 = puVar8 + uVar7;
    uVar3 = _DAT_006af8b0 + _DAT_006af8b8;
    do {
      if (puVar2 < puVar8 + 1 || puVar8 + 1 < puVar8) {
LAB_00051ab4:
                    /* WARNING: Does not return */
        pcVar6 = (code *)SoftwareBreakpoint(0x5519,0x51ab8);
        (*pcVar6)();
      }
      uVar5 = *puVar8;
      if (uVar5 != 0) {
        uVar4 = _DAT_006af8b0 + *(uint *)(_DAT_006af890 + 4) + (ulong)uVar5;
        if ((uVar4 != 0) &&
           ((uVar1 = uVar4 + 0x18,
            (((uVar1 < uVar4 || uVar4 < _DAT_006af8b0) || uVar3 < uVar1) || uVar3 <= uVar4 + 0x16)
            && (((uVar1 < uVar4 || uVar4 < _DAT_006af8b0) || uVar3 < uVar1) || uVar4 + 0x16 != uVar3
               ) || ((ulong)((long)((_DAT_006af8b8 -
                                    ((ulong)uVar5 + (ulong)*(uint *)(_DAT_006af890 + 4))) + -0x16)
                            >> 1) < (ulong)*(ushort *)(uVar4 + 0x14))))) goto LAB_00051ab4;
        if (*(long *)(uVar4 + 8) == param_1) {
          if ((ulong)*(ushort *)(uVar4 + 0x14) * (ulong)*(ushort *)(uVar4 + 4) <= param_2) {
            return uVar4;
          }
                    /* WARNING: Does not return */
          pcVar6 = (code *)SoftwareBreakpoint(1,0x51ab4);
          (*pcVar6)();
        }
      }
      puVar8 = puVar8 + 1;
      uVar7 = uVar7 - 1;
    } while (uVar7 != 0);
  }
  return 0;
}

