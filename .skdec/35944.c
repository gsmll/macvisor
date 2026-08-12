
void FUN_00035944(long param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4)

{
  undefined8 uVar1;
  undefined2 local_30;
  undefined4 local_2e;
  undefined2 local_2a;
  long local_28;
  undefined8 uStack_20;
  undefined8 local_18;
  
  if (param_1 != 0) {
    local_30 = 0x100;
    local_2e = 0;
    local_2a = 0;
    uStack_20 = 0;
    local_28 = param_1;
    local_18 = param_4;
    FUN_00032520(&local_30,0,param_2,param_3);
    return;
  }
  uVar1 = FUN_004b27b8();
  FUN_00032c68(uVar1,param_3,param_4);
  return;
}

