
void FUN_0005b8c8(void)

{
  byte *pbVar1;
  code *pcVar2;
  uint uVar3;
  long lVar4;
  ulong uVar5;
  long lVar6;
  ulong local_30;
  ulong uStack_28;
  undefined1 local_20;
  byte abStack_1f [7];
  long local_18;
  
  local_18 = -0x2c8502b44bfffed6;
  lVar4 = FUN_0005acac(0x6b2568,1,1);
  lVar6 = 0;
  uVar3 = 0;
  uVar5 = (ulong)*(ushort *)(lVar4 + 0x40);
  local_20 = 0;
  local_30 = (ulong)(byte)s_0123456789abcdef_005bc6c6[2] << 0x10 |
             (ulong)(byte)s_0123456789abcdef_005bc6c6[3] << 0x18 |
             (ulong)(ushort)s_0123456789abcdef_005bc6c6._0_2_ |
             (ulong)((uint)(byte)s_0123456789abcdef_005bc6c6[6] << 0x10 |
                     (uint)(byte)s_0123456789abcdef_005bc6c6[7] << 0x18 |
                    (uint)(ushort)s_0123456789abcdef_005bc6c6._4_2_) << 0x20;
  uStack_28 = (ulong)(byte)s_0123456789abcdef_005bc6c6[10] << 0x10 |
              (ulong)(byte)s_0123456789abcdef_005bc6c6[0xb] << 0x18 |
              (ulong)(ushort)s_0123456789abcdef_005bc6c6._8_2_ |
              (ulong)((uint)(byte)s_0123456789abcdef_005bc6c6[0xe] << 0x10 |
                      (uint)(byte)s_0123456789abcdef_005bc6c6[0xf] << 0x18 |
                     (uint)(ushort)s_0123456789abcdef_005bc6c6._12_2_) << 0x20;
  while( true ) {
    pbVar1 = (byte *)((long)&local_30 + (uVar5 & 0xf));
    if ((abStack_1f <= pbVar1) || (pbVar1 < &local_30)) break;
    uVar3 = (uint)*pbVar1 << (ulong)((uint)lVar6 & 0x1f) | uVar3;
    uVar5 = uVar5 >> 4;
    lVar6 = lVar6 + 8;
    if (lVar6 == 0x20) {
      if (local_18 == -0x2c8502b44bfffed6) {
        return;
      }
                    /* WARNING: Subroutine does not return */
      FUN_0011d7e8(uVar3);
    }
  }
                    /* WARNING: Does not return */
  pcVar2 = (code *)SoftwareBreakpoint(0x5519,0x5ba10);
  (*pcVar2)();
}

