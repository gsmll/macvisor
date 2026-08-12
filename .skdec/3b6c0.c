
bool FUN_0003b6c0(long param_1,long param_2,undefined8 param_3,undefined8 param_4,ulong param_5)

{
  bool bVar1;
  int iVar2;
  long lVar3;
  
  if (*(long *)(param_2 + 0x50) != param_1) {
                    /* WARNING: Subroutine does not return */
    FUN_004afae4(s__VAS_abort_in_function__s_at_lin_005b274a);
  }
  if (*(ulong *)(param_1 + 0x38) < param_5) {
    *(undefined8 *)(param_2 + 0x50) = 0;
    iVar2 = FUN_00118194(param_2 + 0x40);
    if (iVar2 != 0) {
                    /* WARNING: Subroutine does not return */
      FUN_004afae4(s__VAS_abort_in_function__s_at_lin_005aed68);
    }
    if (*(ulong *)(param_1 + 0x38) < param_5) {
      do {
        lVar3 = FUN_0003344c();
        bVar1 = lVar3 != 0;
        if (lVar3 == 0) break;
        FUN_0003b648(param_1,lVar3);
      } while (*(ulong *)(param_1 + 0x38) < param_5);
    }
    else {
      bVar1 = true;
    }
    FUN_00044c94(param_2,param_3,param_4);
    if (*(long *)(param_2 + 0x50) != 0) {
                    /* WARNING: Subroutine does not return */
      FUN_004afae4(s__VAS_abort_in_function__s_at_lin_005b274a);
    }
    *(long *)(param_2 + 0x50) = param_1;
  }
  else {
    bVar1 = true;
  }
  return bVar1;
}

