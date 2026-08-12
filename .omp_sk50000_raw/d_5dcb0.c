
void FUN_0005dcb0(uint param_1,undefined8 param_2,undefined8 param_3,long param_4,uint param_5)

{
  ulong uVar1;
  ulong uVar2;
  char *pcVar3;
  uint uVar4;
  undefined8 local_38;
  undefined8 uStack_30;
  long local_28;
  
  local_28 = -0x2c8502b44bfffed6;
  uVar4 = 1;
  if (param_5 != 0) {
    uVar4 = 2;
  }
  local_38 = param_2;
  uStack_30 = param_3;
  if (param_4 == 0) {
    param_4 = FUN_00060524();
  }
  uVar2 = FUN_0005d64c(param_4,uVar4 | (param_1 & 0xf) << 0xc,&local_38,1);
  uVar1 = 0;
  if (uVar2 != 5) {
    uVar1 = uVar2;
  }
  if (uVar1 < 4) {
    if (((param_5 & 1) != 0) || (uVar1 != 3)) {
      if (local_28 == -0x2c8502b44bfffed6) {
        return;
      }
                    /* WARNING: Subroutine does not return */
      FUN_0011d7e8();
    }
    pcVar3 = s_Unexpected_wait_interruption_005bc8f1;
  }
  else {
    pcVar3 = s_unexpected_return_from_xrt__sync_005bc8ca;
  }
                    /* WARNING: Subroutine does not return */
  FUN_0005b190(0,pcVar3);
}

