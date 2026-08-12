
void FUN_00050444(undefined8 param_1)

{
  byte bVar1;
  byte bVar2;
  ushort uVar3;
  ushort uVar4;
  ushort uVar5;
  ushort uVar6;
  code *pcVar7;
  ulong uVar8;
  ushort *puVar9;
  long lVar10;
  ushort *puVar11;
  bool bVar12;
  long lVar13;
  ulong local_70 [2];
  
  uVar8 = FUN_0004ed48();
  if ((uVar8 != 0) && (uVar8 + 8 < uVar8)) {
LAB_00050650:
                    /* WARNING: Does not return */
    pcVar7 = (code *)SoftwareBreakpoint(0x5519,0x50654);
    (*pcVar7)();
  }
  local_70[1] = 0;
  local_70[0] = uVar8;
  puVar9 = (ushort *)FUN_0004eb4c(local_70);
  if (puVar9 != (ushort *)0x0) {
    bVar12 = false;
    do {
      if (puVar9 + 6 < puVar9) goto LAB_00050650;
      if (((uint)(byte)puVar9[1] << 0x10 | (uint)*(byte *)((long)puVar9 + 3) << 0x18 | (uint)*puVar9
          ) == 0xb) {
        uVar3 = puVar9[2];
        bVar1 = *(byte *)((long)puVar9 + 7);
        uVar5 = puVar9[3];
        uVar4 = puVar9[4];
        bVar2 = *(byte *)((long)puVar9 + 0xb);
        uVar6 = puVar9[5];
        lVar10 = FUN_0004e8b0(puVar9);
        if (lVar10 != 0) {
          lVar13 = 0;
          do {
            if (((ulong)(byte)uVar5 << 0x10 | (ulong)bVar1 << 0x18 | (ulong)uVar3 |
                (ulong)((uint)(byte)uVar6 << 0x10 | (uint)bVar2 << 0x18 | (uint)uVar4) << 0x20) <
                ((ulong)(byte)puVar9[3] << 0x10 | (ulong)*(byte *)((long)puVar9 + 7) << 0x18 |
                 (ulong)puVar9[2] |
                (ulong)((uint)(byte)puVar9[5] << 0x10 | (uint)*(byte *)((long)puVar9 + 0xb) << 0x18
                       | (uint)puVar9[4]) << 0x20)) goto LAB_00050650;
            puVar11 = (ushort *)FUN_0004e7b8(puVar9,lVar13);
            FUN_0005cf4c((ulong)(byte)puVar11[1] << 0x10 |
                         (ulong)*(byte *)((long)puVar11 + 3) << 0x18 | (ulong)*puVar11 |
                         (ulong)((uint)(byte)puVar11[3] << 0x10 |
                                 (uint)*(byte *)((long)puVar11 + 7) << 0x18 | (uint)puVar11[2]) <<
                         0x20,param_1);
            lVar13 = lVar13 + 1;
          } while (lVar10 != lVar13);
        }
        bVar12 = true;
      }
      puVar9 = (ushort *)FUN_0004eb4c(local_70);
    } while (puVar9 != (ushort *)0x0);
    if (bVar12) {
      return;
    }
  }
  FUN_0005cf4c(0x706c6174,param_1);
  return;
}

