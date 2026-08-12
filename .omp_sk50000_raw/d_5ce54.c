
void FUN_0005ce54(undefined8 *param_1)

{
  uint uVar1;
  ulong uVar2;
  undefined8 uVar3;
  undefined8 in_xzr;
  
  uVar3 = *param_1;
  uVar2 = FUN_00060524();
  if ((((uint)(uVar2 >> 0xe) ^ (uint)uVar3) & 0xffffff) != 0) {
                    /* WARNING: Subroutine does not return */
    FUN_0005b190(0,s_tried_to_unlock_lock_I_did_not_o_005bc719);
  }
  uVar3 = FUN_00060524();
  FUN_0005b05c(uVar3,param_1,&stack0xfffffffffffffff0);
  if (*(short *)((long)param_1 + 0xc) == 0) {
    uVar3 = *param_1;
    *param_1 = in_xzr;
    LORelease();
    if (((uint)uVar3 >> 0x18 & 1) != 0) {
      uVar1 = (uint)param_1 >> 4 & 0xf;
      if (*(byte *)(param_1 + 1) != 0) {
        uVar1 = *(byte *)(param_1 + 1) - 1;
      }
      FUN_0005dd70(uVar1 & 0xff,param_1,3,0);
      return;
    }
  }
  else {
    *(short *)((long)param_1 + 0xc) = *(short *)((long)param_1 + 0xc) + -1;
    *(short *)((long)param_1 + 0xe) = *(short *)((long)param_1 + 0xe) + 1;
  }
  return;
}

