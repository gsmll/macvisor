
void FUN_0003573c(ulong param_1,long param_2,undefined8 param_3,undefined8 param_4)

{
  ulong uVar1;
  long *plVar2;
  ulong uVar3;
  long lVar4;
  code *pcVar5;
  int iVar6;
  long *plVar7;
  long *plVar8;
  undefined8 uVar9;
  undefined8 uVar10;
  long *plVar11;
  long *plVar12;
  long *plVar13;
  undefined1 auVar14 [16];
  undefined2 uStack_d0;
  undefined4 uStack_ce;
  undefined2 uStack_ca;
  long lStack_c8;
  undefined8 uStack_c0;
  undefined8 uStack_b8;
  undefined1 *puStack_b0;
  code *pcStack_a8;
  char *local_a0;
  undefined8 local_98;
  char *local_90;
  undefined *local_88;
  long local_80;
  ulong uStack_78;
  long local_70;
  undefined8 uStack_68;
  
  uVar10 = 8;
  plVar7 = (long *)FUN_0005acac(0x6af188,4,8);
  local_90 = (char *)(param_1 & 0x3f);
  if (local_90 != (char *)0x0) {
    uStack_68 = 0x40;
    local_80 = 0;
    local_88 = &DAT_005ae75a;
    local_a0 = s_vas__mark_cap_slots_allocated_005b1c91;
    local_98 = 0x308;
    uStack_78 = param_1;
    local_70 = param_2;
                    /* WARNING: Subroutine does not return */
    FUN_004afae4(s__VAS_abort_in_function__s_at_lin_005b1c12);
  }
  uVar3 = param_2 + param_1;
  if ((0xffffffffffffffbf < uVar3) || (uVar3 < param_1)) {
    local_98 = 0x30a;
    local_90 = s_end_>_SIZE_MAX___L4_CapSize____e_005b1d15;
    local_a0 = s_vas__mark_cap_slots_allocated_005b1c91;
    local_88 = (undefined *)param_1;
    local_80 = param_2;
                    /* WARNING: Subroutine does not return */
    FUN_004afae4(s__VAS_abort_in_function__s_at_lin_005b1caf);
  }
  auVar14 = FUN_00034bd8(*(undefined8 *)(*plVar7 + 0x10));
  if ((auVar14._0_8_ & 1) != 0) {
    auVar14 = FUN_004b2780();
    lStack_c8 = auVar14._0_8_;
    pcStack_a8 = FUN_00035944;
    puStack_b0 = &stack0xfffffffffffffff0;
    if (lStack_c8 != 0) {
      uStack_d0 = 0x100;
      uStack_ce = 0;
      uStack_ca = 0;
      uStack_c0 = 0;
      uStack_b8 = param_4;
      FUN_00032520(&uStack_d0,0,auVar14._8_8_,uVar10);
      return;
    }
    uVar9 = FUN_004b27b8();
    FUN_00032c68(uVar9,uVar10,param_4);
    return;
  }
  plVar8 = (long *)FUN_00035418(param_1);
  if (param_1 < uVar3) {
    plVar13 = plVar8 + 9;
    plVar12 = plVar8;
    do {
      uVar1 = param_1 + 0x40;
      if (plVar12 == (long *)0x0) {
LAB_00035800:
        plVar8 = (long *)FUN_00035418(param_1);
        plVar13 = plVar8 + 9;
        plVar12 = plVar8;
        if (plVar8 != (long *)0x0) goto LAB_00035818;
        plVar12 = (long *)0x0;
        lVar4 = 0;
        if ((uVar1 & 0x3fff) != 0) {
          lVar4 = 0x4000;
        }
        param_1 = lVar4 + (uVar1 & 0xffffffffffffc000);
      }
      else {
        if ((plVar13 < plVar12 + 9) || (plVar12 < plVar8)) goto LAB_000358dc;
        if (plVar12[5] + 0x4000U <= param_1) goto LAB_00035800;
LAB_00035818:
        if (((plVar13 < plVar12 + 9) || (plVar12 + 9 < plVar12)) || (plVar12 < plVar8)) {
LAB_000358dc:
                    /* WARNING: Does not return */
          pcVar5 = (code *)SoftwareBreakpoint(0x5519,0x358e0);
          (*pcVar5)();
        }
        iVar6 = FUN_00035684(plVar12,param_1);
        param_1 = uVar1;
        if ((iVar6 != 0) && (plVar11 = plVar7, (short)plVar12[4] == 0x100)) {
          do {
            plVar2 = plVar11 + 6;
            if (plVar11 + 7 < plVar2) goto LAB_000358dc;
            plVar11 = (long *)*plVar2;
          } while (plVar11 != (long *)0x0 && plVar11 != plVar12);
          if (plVar11 == plVar12) {
            *plVar2 = plVar12[6];
          }
        }
      }
    } while (param_1 < uVar3);
  }
  FUN_00034d5c(*(undefined8 *)(*plVar7 + 0x10),auVar14._0_8_,auVar14._8_8_);
  return;
}

