
void FUN_0005d394(ulong *param_1,int param_2)

{
  bool bVar1;
  uint uVar2;
  uint uVar3;
  ushort uVar4;
  code *pcVar5;
  uint uVar6;
  undefined4 uVar7;
  int iVar8;
  ulong uVar9;
  ulong uVar10;
  ulong uVar11;
  
  uVar2 = (uint)param_1 >> 4 & 0xf;
  if ((byte)param_1[1] != 0) {
    uVar2 = (byte)param_1[1] - 1;
  }
  if (param_1 + 2 < param_1) {
                    /* WARNING: Does not return */
    pcVar5 = (code *)SoftwareBreakpoint(0x5519,0x5d470);
    (*pcVar5)();
  }
  uVar9 = *param_1;
  uVar6 = (uint)(uVar9 >> 0x20);
  uVar4 = (ushort)(uVar9 >> 0x30);
  uVar3 = uVar6 & 0xffff;
  if (uVar4 + 1 < (uVar6 & 0xffff)) {
    uVar3 = uVar4 + 1;
  }
  uVar11 = uVar9 >> 0x20;
  if (param_2 == 0) {
    uVar11 = (ulong)uVar3;
  }
  uVar10 = *param_1;
  if (uVar10 == uVar9) {
    *param_1 = (ulong)((int)uVar9 + 1) | uVar11 << 0x30 | uVar9 & 0xffff00000000;
  }
  else {
    do {
      uVar6 = (uint)(uVar10 >> 0x20);
      uVar4 = (ushort)(uVar10 >> 0x30);
      iVar8 = (int)uVar10;
      uVar3 = uVar6 & 0xffff;
      if (uVar4 + 1 < (uVar6 & 0xffff)) {
        uVar3 = uVar4 + 1;
      }
      uVar9 = uVar10 >> 0x20;
      if (param_2 == 0) {
        uVar9 = (ulong)uVar3;
      }
      uVar11 = uVar10 & 0xffff00000000;
      bVar1 = *param_1 != uVar10;
      uVar10 = *param_1;
    } while (bVar1);
    *param_1 = (ulong)(iVar8 + 1) | uVar9 << 0x30 | uVar11;
  }
  if ((uint)uVar4 < (uVar6 & 0xffff)) {
    uVar7 = 6;
    if (param_2 == 0) {
      uVar7 = 4;
    }
    FUN_0005dd70(uVar2 & 0xff,param_1,uVar7,0);
    return;
  }
  return;
}

