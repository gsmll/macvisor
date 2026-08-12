
void FUN_00013af0(ulong param_1)

{
  uint uVar1;
  ulong uVar2;
  undefined1 auVar3 [16];
  
  uVar2 = FUN_00013be4();
  if (uVar2 == 0) {
    FUN_004b01b8();
LAB_00013b78:
    FUN_004b0188();
  }
  else {
    if (param_1 < uVar2) goto LAB_00013b78;
    if (param_1 <= uVar2 + 0x370) {
      auVar3 = SEXT816((long)(param_1 - uVar2)) * SEXT816(0x4a7904a7904a7905);
      uVar1 = 1 << (ulong)((int)(auVar3._8_8_ >> 7) - (auVar3._12_4_ >> 0x1f) & 0x1f);
      if ((*(ulong *)(uVar2 + 0x528) & (long)(int)uVar1) != 0) {
        *(ulong *)(uVar2 + 0x528) = *(ulong *)(uVar2 + 0x528) & (long)(int)~uVar1;
        return;
      }
      goto LAB_00013b80;
    }
  }
  FUN_004b0158();
LAB_00013b80:
  auVar3 = FUN_004b0128();
  if (auVar3._8_8_ != 0) {
    uVar2 = 0;
    do {
      FUN_004b23d8(*(undefined8 *)(auVar3._0_8_ + uVar2 * 8));
      FUN_0005ed18(uVar2,0);
      uVar2 = (ulong)((int)uVar2 + 1);
    } while (uVar2 < auVar3._8_8_);
  }
  return;
}

