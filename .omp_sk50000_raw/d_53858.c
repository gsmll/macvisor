
void FUN_00053858(long param_1)

{
  ulong uVar1;
  ulong *puVar2;
  
  uVar1 = (((ulong)*(byte *)(param_1 + 0x12) << 0x10 | (ulong)*(byte *)(param_1 + 0x13) << 0x18 |
           (ulong)*(ushort *)(param_1 + 0x10)) << 0xc | (ulong)*(byte *)(param_1 + 0x14) << 0x2c) +
          0x4000;
  puVar2 = (ulong *)FUN_0005acac(0x6af8d8,2,5);
  if (*puVar2 < uVar1) {
    *puVar2 = uVar1;
  }
  return;
}

