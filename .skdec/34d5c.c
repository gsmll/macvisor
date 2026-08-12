
void FUN_00034d5c(long param_1,byte param_2,ulong param_3)

{
  int iVar1;
  undefined8 uVar2;
  
  uVar2 = thunk_FUN_00060524();
  iVar1 = thunk_FUN_000539c0(uVar2,*(undefined8 *)(param_1 + 0x10));
  if (iVar1 == 0) {
                    /* WARNING: Subroutine does not return */
    FUN_004afae4(s__VAS_abort_in_function__s_at_lin_005b1554);
  }
  if (param_3 + 1 != *(long *)(param_1 + 0x18)) {
                    /* WARNING: Subroutine does not return */
    FUN_004afae4(s__VAS_abort_in_function__s_at_lin_005b15c4);
  }
  if (((param_3 & 0xff) != 0) != (bool)(param_2 & 1)) {
                    /* WARNING: Subroutine does not return */
    FUN_004afae4(s__VAS_abort_in_function__s_at_lin_005b165f);
  }
  if ((param_2 & 1) == 0) {
    (**(code **)(param_1 + 0x20))(*(undefined8 *)(param_1 + 0x28));
    uVar2 = thunk_FUN_00060524();
    iVar1 = thunk_FUN_000539c0(uVar2,*(undefined8 *)(param_1 + 0x10));
    if (iVar1 == 0) {
                    /* WARNING: Subroutine does not return */
      FUN_004afae4(s__VAS_abort_in_function__s_at_lin_005b1554);
    }
    if (param_3 + 1 != *(long *)(param_1 + 0x18)) {
                    /* WARNING: Subroutine does not return */
      FUN_004afae4(s__VAS_abort_in_function__s_at_lin_005b15c4);
    }
    if ((param_3 & 0xff) != 0) {
                    /* WARNING: Subroutine does not return */
      FUN_004afae4(s__VAS_abort_in_function__s_at_lin_005b165f);
    }
    *(undefined8 *)(param_1 + 0x10) = 0;
    *(ulong *)(param_1 + 0x18) = param_3;
    iVar1 = FUN_00118194(param_1);
    if (iVar1 != 0) {
                    /* WARNING: Subroutine does not return */
      FUN_004afae4(s__VAS_abort_in_function__s_at_lin_005aed68);
    }
  }
  else {
    *(ulong *)(param_1 + 0x18) = param_3;
  }
  return;
}

