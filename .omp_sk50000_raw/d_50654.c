
long FUN_00050654(undefined8 param_1,ulong param_2)

{
  code *pcVar1;
  short *psVar2;
  ushort *puVar3;
  ulong uVar4;
  ulong uVar5;
  undefined1 auVar6 [16];
  undefined8 local_60;
  undefined8 uStack_58;
  
  auVar6 = FUN_0004ed84();
  uStack_58 = 0;
  local_60 = param_1;
  psVar2 = (short *)FUN_0004eb4c(&local_60);
  do {
    if (psVar2 == (short *)0x0) {
      return 0;
    }
    if (psVar2 + 6 < psVar2) {
                    /* WARNING: Does not return */
      pcVar1 = (code *)SoftwareBreakpoint(0x5519,0x5082c);
      (*pcVar1)();
    }
    if ((((char)psVar2[1] == '\0' && *(char *)((long)psVar2 + 3) == '\0') && *psVar2 == 0) &&
       (uVar4 = (ulong)*(byte *)(psVar2 + 3) << 0x10 | (ulong)*(byte *)((long)psVar2 + 7) << 0x18 |
                (ulong)(ushort)psVar2[2] |
                (ulong)((uint)*(byte *)(psVar2 + 5) << 0x10 |
                        (uint)*(byte *)((long)psVar2 + 0xb) << 0x18 | (uint)(ushort)psVar2[4]) <<
                0x20, 0x10f < uVar4)) {
      uVar5 = 0;
      do {
        puVar3 = (ushort *)FUN_0004e7b8(psVar2,uVar5);
        if (((ulong)(byte)puVar3[1] << 0x10 | (ulong)*(byte *)((long)puVar3 + 3) << 0x18 |
             (ulong)*puVar3 |
            (ulong)((uint)(byte)puVar3[3] << 0x10 | (uint)*(byte *)((long)puVar3 + 7) << 0x18 |
                   (uint)puVar3[2]) << 0x20) == param_2) {
          if (*(byte *)((long)puVar3 + 0x10f) >> 2 != 0) {
                    /* WARNING: Subroutine does not return */
            FUN_001150e0(s_integer_overflow_005bb5bd);
          }
          uVar4 = (ulong)(byte)puVar3[0x85] << 0x10 | (ulong)*(byte *)((long)puVar3 + 0x10b) << 0x18
                  | (ulong)puVar3[0x84] |
                  (ulong)((uint)(byte)puVar3[0x87] << 0x10 |
                          (uint)*(byte *)((long)puVar3 + 0x10f) << 0x18 | (uint)puVar3[0x86]) <<
                  0x20;
          if (uVar4 << 6 < auVar6._8_8_) {
            return auVar6._0_8_ + uVar4 * 0x40;
          }
          return 0;
        }
        uVar5 = uVar5 + 1;
      } while (uVar5 < uVar4 / 0x110);
    }
    psVar2 = (short *)FUN_0004eb4c(&local_60);
  } while( true );
}

