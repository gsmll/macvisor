
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

ulong FUN_0005228c(long param_1,ulong param_2)

{
  short *psVar1;
  short *psVar2;
  short *psVar3;
  code *pcVar4;
  ulong uVar5;
  
  if (DAT_006ad6ea == '\x01') {
    uVar5 = FUN_00051920();
    return uVar5;
  }
  psVar1 = (short *)(param_1 + 0x18);
  psVar2 = (short *)(param_1 + ((ulong)*(byte *)(param_1 + 0x16) << 2 |
                               (ulong)*(byte *)(param_1 + 0x17) << 10) +
                     (ulong)*(ushort *)(param_1 + 0x14) * 2 + 0x18);
  if (psVar1 <= psVar2) {
    uVar5 = ((ulong)*(byte *)(param_1 + 0xe) << 0x10 | (ulong)*(byte *)(param_1 + 0xf) << 0x18 |
             (ulong)*(ushort *)(param_1 + 0xc) |
            (ulong)((uint)*(byte *)(param_1 + 0x12) << 0x10 |
                    (uint)*(byte *)(param_1 + 0x13) << 0x18 | (uint)*(ushort *)(param_1 + 0x10)) <<
            0x20) + _DAT_006ad6e0;
    if (param_2 < uVar5 || uVar5 + (ulong)*(ushort *)(param_1 + 0x14) * 0x4000 <= param_2) {
      return 0;
    }
    psVar3 = psVar1 + (param_2 - uVar5 >> 0xe);
    if ((psVar1 <= psVar3 && psVar3 + 1 <= psVar2) && psVar3 <= psVar3 + 1) {
      return (ulong)(*psVar3 != -1);
    }
  }
                    /* WARNING: Does not return */
  pcVar4 = (code *)SoftwareBreakpoint(0x5519,0x5236c);
  (*pcVar4)();
}

