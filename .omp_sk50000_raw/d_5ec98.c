
ulong FUN_0005ec98(uint param_1)

{
  long lVar1;
  
  if (param_1 < 0x37) {
    lVar1 = tpidrro_el0;
    lVar1 = lVar1 + (ulong)param_1 * 8;
    return (ulong)*(byte *)(lVar1 + 10) << 0x10 | (ulong)*(byte *)(lVar1 + 0xb) << 0x18 |
           (ulong)*(ushort *)(lVar1 + 8) |
           (ulong)((uint)*(byte *)(lVar1 + 0xe) << 0x10 | (uint)*(byte *)(lVar1 + 0xf) << 0x18 |
                  (uint)*(ushort *)(lVar1 + 0xc)) << 0x20;
  }
                    /* WARNING: Subroutine does not return */
  FUN_0005b190(0,s_get_message_register__d_out_of_b_005bce00);
}

