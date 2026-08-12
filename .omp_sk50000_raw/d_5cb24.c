
void FUN_0005cb24(undefined8 param_1,ulong param_2,undefined1 (*param_3) [16],ulong param_4)

{
  ulong uVar1;
  ulong uVar2;
  undefined1 auVar3 [16];
  undefined8 local_80;
  undefined8 uStack_78;
  undefined8 local_70;
  undefined8 uStack_68;
  undefined8 uStack_60;
  ulong local_58;
  ulong local_50;
  long lStack_48;
  undefined8 uStack_40;
  undefined8 uStack_38;
  
  lStack_48 = 0;
  local_50 = 0;
  uStack_38 = 0;
  uStack_40 = 0;
  uStack_68 = 0;
  local_70 = 0;
  local_58 = 0;
  uStack_60 = 0;
  uStack_78 = 0;
  local_80 = 0;
  FUN_0005c764(param_1,&local_80);
  uVar1 = 0;
  if (local_58 != 0) {
    uVar1 = param_2 / local_58;
  }
  uVar2 = 0;
  if (local_50 != 0) {
    uVar2 = (lStack_48 * (param_2 - uVar1 * local_58)) / local_50;
  }
  auVar3._8_8_ = uVar2;
  auVar3._0_8_ = uVar1;
  if ((param_4 & 1) == 0) {
    auVar3 = FUN_0019ae9c(uVar1,uVar2,local_80,uStack_78);
  }
  *param_3 = auVar3;
  return;
}

