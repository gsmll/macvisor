
void FUN_00052a04(ulong param_1)

{
  byte bVar1;
  ushort uVar2;
  uint3 uVar3;
  ushort uVar4;
  code *pcVar5;
  long lVar6;
  ushort *puVar7;
  ulong uVar8;
  ushort *puVar9;
  
  if (param_1 <= param_1 + 0x4000) {
    lVar6 = FUN_0005baac(4,4);
    if (lVar6 == 0) {
      uRam000000000064cc60 = param_1;
                    /* WARNING: Read-only address (ram,0x0064cc60) is written */
      FUN_0005ba5c();
                    /* WARNING: Read-only address (ram,0x0064cc80) is written */
      uRam000000000064cc80 = 0x6af8e0;
      FUN_0005ba5c();
      for (puVar7 = (ushort *)FUN_0005acac(0x6aff18,2,4); puVar7 != (ushort *)0xffffffffffffffff;
          puVar7 = (ushort *)
                   ((ulong)(byte)puVar7[5] << 0x10 | (ulong)*(byte *)((long)puVar7 + 0xb) << 0x18 |
                    (ulong)puVar7[4] |
                   (ulong)((uint)(byte)puVar7[7] << 0x10 |
                           (uint)*(byte *)((long)puVar7 + 0xf) << 0x18 | (uint)puVar7[6]) << 0x20))
      {
        if (puVar7 + 0x2000 < puVar7) goto LAB_00052c48;
        if ((((char)puVar7[1] != '\0' || *(char *)((long)puVar7 + 3) != '\0') || *puVar7 != 0) ||
            (((char)puVar7[3] != '\0' || *(char *)((long)puVar7 + 7) != '\0') || puVar7[2] != 0)) {
          uVar8 = 0;
          puVar9 = puVar7 + 0x10;
          do {
            if ((puVar9 != (ushort *)0x0) &&
               (((puVar9 < puVar7 + 0x10 || (puVar7 + 0x2000 < puVar9 + 0x10)) ||
                (puVar9 + 0x10 < puVar9)))) goto LAB_00052c48;
            uVar3 = *(uint3 *)(puVar9 + 2);
            if (*(char *)((long)puVar9 + 7) == '\v') {
              if (puVar9 + 0x10 < puVar9) goto LAB_00052c48;
              uVar2 = *puVar9;
              bVar1 = *(byte *)((long)puVar9 + 3);
              uVar4 = puVar9[1];
              lVar6 = FUN_0005acac(0x6af8d8,2,5);
              *(ulong *)(lVar6 + 0x2a0) =
                   (ulong)(byte)uVar4 << 0x10 | (ulong)bVar1 << 0x18 | (ulong)uVar2 |
                   (ulong)uVar3 << 0x20;
            }
            uVar8 = uVar8 + 1;
            puVar9 = puVar9 + 0x10;
          } while (uVar8 < ((ulong)(byte)puVar7[1] << 0x10 |
                            (ulong)*(byte *)((long)puVar7 + 3) << 0x18 | (ulong)*puVar7 |
                           (ulong)((uint)(byte)puVar7[3] << 0x10 |
                                   (uint)*(byte *)((long)puVar7 + 7) << 0x18 | (uint)puVar7[2]) <<
                           0x20));
        }
      }
    }
    return;
  }
LAB_00052c48:
                    /* WARNING: Does not return */
  pcVar5 = (code *)SoftwareBreakpoint(0x5519,0x52c4c);
  (*pcVar5)();
}

