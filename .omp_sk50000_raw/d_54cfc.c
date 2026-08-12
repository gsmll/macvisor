
ulong FUN_00054cfc(void)

{
  code *pcVar1;
  int iVar2;
  ulong uVar3;
  ushort *puVar4;
  undefined1 local_30 [16];
  
  iVar2 = FUN_0004fe80();
  if (iVar2 != 0) {
    uVar3 = FUN_0004ed48();
    if ((uVar3 != 0) && (uVar3 + 8 < uVar3)) {
LAB_00054de0:
                    /* WARNING: Does not return */
      pcVar1 = (code *)SoftwareBreakpoint(0x5519,0x54de4);
      (*pcVar1)();
    }
    local_30 = FUN_0004eb44();
    uVar3 = FUN_0004eb4c(local_30);
    while (uVar3 != 0) {
      if (uVar3 + 0xc < uVar3) goto LAB_00054de0;
      iVar2 = FUN_0004e88c(uVar3);
      if (iVar2 == 0x19) {
        puVar4 = (ushort *)FUN_0004e7b8(uVar3,0);
        if (puVar4 != (ushort *)0x0) {
          return (ulong)(byte)puVar4[1] << 0x10 | (ulong)*(byte *)((long)puVar4 + 3) << 0x18 |
                 (ulong)*puVar4 |
                 (ulong)((uint)(byte)puVar4[3] << 0x10 | (uint)*(byte *)((long)puVar4 + 7) << 0x18 |
                        (uint)puVar4[2]) << 0x20;
        }
      }
      uVar3 = FUN_0004eb4c(local_30);
    }
  }
  return 0;
}

