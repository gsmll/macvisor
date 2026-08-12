
undefined1  [16] FUN_0005dfa8(ulong param_1,ushort *param_2)

{
  ulong uVar1;
  ulong uVar2;
  undefined8 uVar3;
  undefined8 uVar4;
  ushort uVar5;
  undefined1 uVar6;
  undefined1 *puVar7;
  bool bVar8;
  undefined1 auVar9 [16];
  
  uVar5 = *param_2;
  uVar3 = *(undefined8 *)(param_2 + 4);
  uVar4 = *(undefined8 *)(param_2 + 8);
  puVar7 = (undefined1 *)tpidrro_el0;
  puVar7[4] = 0;
  puVar7[2] = 0;
  puVar7[5] = 0;
  puVar7[3] = 0;
  puVar7[6] = 0;
  puVar7[7] = 0;
  *puVar7 = (char)uVar5;
  uVar6 = (undefined1)(uVar5 >> 8);
  puVar7[1] = uVar6;
  puVar7[0xd] = (char)((ulong)uVar3 >> 0x28);
  puVar7[8] = (char)uVar3;
  puVar7[0xb] = (char)((ulong)uVar3 >> 0x18);
  puVar7[10] = (char)((ulong)uVar3 >> 0x10);
  puVar7[9] = (char)((ulong)uVar3 >> 8);
  puVar7[0xc] = (char)((ulong)uVar3 >> 0x20);
  puVar7[0xf] = (char)((ulong)uVar3 >> 0x38);
  puVar7[0xe] = (char)((ulong)uVar3 >> 0x30);
  puVar7[0x15] = (char)((ulong)uVar4 >> 0x28);
  puVar7[0x10] = (char)uVar4;
  puVar7[0x13] = (char)((ulong)uVar4 >> 0x18);
  puVar7[0x12] = (char)((ulong)uVar4 >> 0x10);
  puVar7[0x11] = (char)((ulong)uVar4 >> 8);
  puVar7[0x14] = (char)((ulong)uVar4 >> 0x20);
  puVar7[0x17] = (char)((ulong)uVar4 >> 0x38);
  puVar7[0x16] = (char)((ulong)uVar4 >> 0x30);
  CallSupervisor(0);
  *puVar7 = (char)uVar5;
  puVar7[7] = 0;
  puVar7[6] = 0;
  puVar7[5] = 0;
  puVar7[4] = 0;
  puVar7[3] = 0;
  puVar7[2] = 0;
  puVar7[1] = uVar6;
  bVar8 = ((byte)param_2[0x10] & param_1 == 8) == 0;
  uVar1 = 0;
  if (bVar8) {
    uVar1 = (ulong)uVar5;
  }
  uVar2 = 0;
  if (bVar8) {
    uVar2 = param_1;
  }
  *(ulong *)(param_2 + 0xc) = uVar1;
  auVar9._8_8_ = 0;
  auVar9._0_8_ = uVar2;
  return auVar9;
}

