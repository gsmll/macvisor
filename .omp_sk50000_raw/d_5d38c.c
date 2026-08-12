
ushort FUN_0005d38c(ulong *param_1,undefined8 param_2)

{
  ushort uVar1;
  uint uVar2;
  ushort uVar3;
  code *pcVar4;
  bool bVar5;
  int iVar6;
  undefined8 uVar7;
  ushort uVar8;
  int iVar9;
  ulong uVar10;
  ulong uVar11;
  ulong uVar12;
  uint uVar13;
  
  uVar2 = (uint)param_1 >> 4 & 0xf;
  if ((byte)param_1[1] != 0) {
    uVar2 = (byte)param_1[1] - 1;
  }
  uVar7 = FUN_0005dc4c(uVar2 & 0xff);
  if (param_1 + 2 < param_1) {
                    /* WARNING: Does not return */
    pcVar4 = (code *)SoftwareBreakpoint(0x5519,0x5d38c);
    (*pcVar4)();
  }
  uVar10 = *param_1;
  uVar13 = (int)(uVar10 >> 0x20) + 1;
  iVar9 = (int)uVar10;
  uVar12 = *param_1;
  if (*param_1 == uVar10) {
    *param_1 = uVar10 & 0xffff000000000000 | uVar10 & 0xffffffff | (ulong)(uVar13 & 0xffff) << 0x20;
    FUN_0005ce54(param_2);
    uVar12 = uVar10;
  }
  else {
    do {
      uVar11 = uVar12;
      uVar13 = (int)(uVar11 >> 0x20) + 1;
      uVar12 = *param_1;
    } while (*param_1 != uVar11);
    *param_1 = uVar11 & 0xffff000000000000 | uVar11 & 0xffffffff | (ulong)(uVar13 & 0xffff) << 0x20;
    FUN_0005ce54(param_2);
    uVar12 = uVar11;
    if ((int)uVar11 != iVar9) {
      uVar8 = 1;
      goto LAB_0005d2f0;
    }
  }
  iVar6 = FUN_0005dc8c(uVar2 & 0xff,param_1,uVar7,0,1);
  if (iVar6 == 3) {
    uVar8 = 0;
    uVar11 = uVar10;
  }
  else {
    do {
      uVar7 = FUN_0005dc4c(uVar2 & 0xff);
      uVar12 = *param_1;
      bVar5 = (int)uVar12 != iVar9;
      uVar8 = (ushort)bVar5;
      uVar11 = uVar12;
      if (bVar5) break;
      iVar6 = FUN_0005dc8c(uVar2 & 0xff,param_1,uVar7,0,1);
      uVar11 = uVar10;
    } while (iVar6 != 3);
    uVar13 = (uint)(uVar12 >> 0x20);
  }
LAB_0005d2f0:
  uVar3 = (ushort)(uVar12 >> 0x30);
  uVar1 = 0;
  if (uVar8 <= uVar3) {
    uVar1 = uVar3 - uVar8;
  }
  uVar10 = *param_1;
  if (uVar10 == (uVar12 & 0xffff000000000000 | (ulong)(uVar13 & 0xffff) << 0x20 |
                uVar11 & 0xffffffff)) {
    *param_1 = (ulong)(uVar13 - 1 & 0xffff) << 0x20 | (ulong)uVar1 << 0x30 | uVar11 & 0xffffffff;
  }
  else {
    do {
      uVar3 = (ushort)(uVar10 >> 0x30);
      uVar1 = 0;
      if (uVar8 <= uVar3) {
        uVar1 = uVar3 - uVar8;
      }
      uVar12 = uVar10 + 0xffff00000000;
      uVar11 = uVar10 & 0xffffffff;
      bVar5 = *param_1 != uVar10;
      uVar10 = *param_1;
    } while (bVar5);
    *param_1 = uVar12 & 0xffff00000000 | (ulong)uVar1 << 0x30 | uVar11;
  }
  FUN_0005cb9c(param_2);
  return uVar8;
}

