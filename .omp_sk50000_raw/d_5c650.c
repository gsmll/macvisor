
void FUN_0005c650(undefined8 *param_1,ulong param_2)

{
  long lVar1;
  long lVar2;
  undefined1 auVar3 [16];
  undefined8 local_80;
  undefined8 uStack_78;
  undefined8 local_70;
  undefined8 uStack_68;
  undefined8 uStack_60;
  undefined8 uStack_58;
  undefined8 local_50;
  undefined8 uStack_48;
  undefined8 uStack_40;
  undefined8 uStack_38;
  
  lVar2 = 0;
  lVar1 = 0x64db60;
  do {
    if (((uint)lVar2 - 1 & 0xff) < 3) {
      FUN_0005c764((uint)lVar2 & 0xff,lVar1);
    }
    lVar2 = lVar2 + 1;
    lVar1 = lVar1 + 0x50;
  } while (lVar2 != 4);
  uStack_48 = 0;
  local_50 = 0;
  uStack_38 = 0;
  uStack_40 = 0;
  uStack_68 = 0;
  local_70 = 0;
  uStack_58 = 0;
  uStack_60 = 0;
  uStack_78 = 0;
  local_80 = 0;
  FUN_0005c764(param_2,&local_80);
  FUN_0005c86c(param_2,&local_80,0,1);
  auVar3._8_8_ = uStack_48;
  auVar3._0_8_ = local_50;
  auVar3 = NEON_ext(auVar3,auVar3,8,1);
  param_1[1] = auVar3._8_8_;
  *param_1 = auVar3._0_8_;
  param_1[2] = param_2 & 0xffffffff;
  return;
}

