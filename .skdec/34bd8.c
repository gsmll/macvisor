
undefined1  [16] FUN_00034bd8(long param_1)

{
  int iVar1;
  undefined8 uVar2;
  undefined8 uVar3;
  ulong uVar4;
  ulong uVar5;
  undefined1 auVar6 [16];
  
  uVar2 = thunk_FUN_00060524();
  iVar1 = thunk_FUN_000539c0(uVar2,*(undefined8 *)(param_1 + 0x10));
  if (iVar1 == 0) {
    iVar1 = FUN_00118164(param_1);
    if (iVar1 != 0) {
                    /* WARNING: Subroutine does not return */
      FUN_004afae4(s__VAS_abort_in_function__s_at_lin_005aed68);
    }
    if (*(long *)(param_1 + 0x10) != 0) {
                    /* WARNING: Subroutine does not return */
      FUN_004afae4(s__VAS_abort_in_function__s_at_lin_005b144d);
    }
    uVar5 = *(ulong *)(param_1 + 0x18);
    if ((uVar5 & 0xff) != 0) {
                    /* WARNING: Subroutine does not return */
      FUN_004afae4(s__VAS_abort_in_function__s_at_lin_005b14d8);
    }
    uVar4 = uVar5 + 0x100;
    uVar2 = thunk_FUN_00060524();
    uVar3 = 0;
    *(undefined8 *)(param_1 + 0x10) = uVar2;
    *(ulong *)(param_1 + 0x18) = uVar5 + 0x101;
  }
  else {
    uVar4 = *(ulong *)(param_1 + 0x18);
    if (((uint)uVar4 & 0xff) == 0xff) {
                    /* WARNING: Subroutine does not return */
      FUN_004afae4(s__VAS_abort_in_function__s_at_lin_005b13b9);
    }
    if ((uVar4 & 0xff) == 0) {
                    /* WARNING: Subroutine does not return */
      FUN_004afae4(s__VAS_abort_in_function__s_at_lin_005b133b);
    }
    *(ulong *)(param_1 + 0x18) = uVar4 + 1;
    uVar3 = 1;
  }
  auVar6._8_8_ = uVar4;
  auVar6._0_8_ = uVar3;
  return auVar6;
}

