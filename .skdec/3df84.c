
void FUN_0003df84(char *param_1,ulong param_2,long param_3)

{
  long lVar1;
  undefined8 uVar2;
  ulong uVar3;
  undefined8 *puVar4;
  char *pcVar5;
  ulong uVar6;
  ulong uVar7;
  ulong uVar8;
  undefined8 local_b0;
  undefined8 local_a8;
  code *local_a0;
  undefined8 uStack_98;
  ulong local_90;
  ulong uStack_88;
  char *local_80;
  ulong uStack_78;
  
  uVar2 = DAT_004bbfd8;
  puVar4 = *(undefined8 **)(param_1 + 0x50);
  pcVar5 = (char *)puVar4[0x26];
  if ((*param_1 != '\x11' || pcVar5 == (char *)0x0) || param_1 == pcVar5) {
    return;
  }
  if (param_2 < *(ulong *)(param_1 + 0x10)) {
    if (param_3 - 1U < *(ulong *)(param_1 + 0x10) - param_2) {
      uVar8 = *(long *)(param_1 + 8) + param_2 + param_3;
      uVar3 = *(long *)(param_1 + 8) + param_2 >> 3 & 0x1fffffffffffc000;
      lVar1 = 0;
      if ((uVar8 & 0x1fff8) != 0) {
        lVar1 = 0x4000;
      }
      uVar8 = lVar1 + (uVar8 >> 0x11) * 0x4000;
      uVar6 = uVar3 - *(long *)(pcVar5 + 8);
      if (uVar6 < *(ulong *)(pcVar5 + 0x10)) {
        uVar7 = uVar8 - uVar3;
        if (*(ulong *)(pcVar5 + 0x10) - uVar6 < uVar7) {
                    /* WARNING: Subroutine does not return */
          FUN_004afae4(s__VAS_abort_in_function__s_at_lin_005b6078);
        }
        if (uVar8 == uVar3) {
          return;
        }
        uVar8 = 0;
        do {
          local_b0 = 0x6ad3a8;
          local_a8 = uVar2;
          local_a0 = FUN_00040f80;
          uStack_98 = 0x65b770;
          local_90 = uVar6;
          uStack_88 = uVar8;
          local_80 = pcVar5;
          uStack_78 = uVar7;
          if (puVar4 == &DAT_0064c3f0) {
            FUN_00033b50(&local_b0);
          }
          else {
            FUN_00040f80();
          }
          uVar8 = uVar8 + 0x4000;
        } while (uVar8 < uVar7);
        return;
      }
      goto LAB_0003e0dc;
    }
  }
  else {
    FUN_004b326c();
  }
  FUN_004b3294();
LAB_0003e0dc:
                    /* WARNING: Subroutine does not return */
  FUN_004afae4(s__VAS_abort_in_function__s_at_lin_005b6078);
}

