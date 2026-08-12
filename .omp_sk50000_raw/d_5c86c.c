
long FUN_0005c86c(undefined8 param_1,undefined1 (*param_2) [16],undefined1 (*param_3) [16],
                 ulong param_4)

{
  ulong uVar1;
  undefined8 uVar2;
  undefined8 uVar3;
  int iVar4;
  long lVar5;
  undefined1 auVar6 [16];
  undefined8 local_90;
  undefined8 uStack_88;
  undefined8 local_80;
  undefined8 uStack_78;
  undefined8 uStack_70;
  long local_68;
  long local_60;
  ulong uStack_58;
  undefined8 uStack_50;
  undefined8 uStack_48;
  
  uStack_58 = 0;
  local_60 = 0;
  uStack_48 = 0;
  uStack_50 = 0;
  uStack_78 = 0;
  local_80 = 0;
  local_68 = 0;
  uStack_70 = 0;
  uStack_88 = 0;
  local_90 = 0;
  FUN_0005c764(param_1,&local_90);
  uVar3 = uStack_78;
  uVar2 = local_80;
  iVar4 = FUN_0019af88(*(undefined8 *)*param_2,*(undefined8 *)(*param_2 + 8),local_80,uStack_78);
  if (iVar4 < 1) {
    auVar6 = *param_2;
    if ((param_4 & 1) == 0) {
      auVar6 = FUN_0019af14(*(undefined8 *)*param_2,*(undefined8 *)(*param_2 + 8),local_90,uStack_88
                           );
    }
    uVar1 = 0;
    if (uStack_58 != 0) {
      uVar1 = (ulong)(local_60 * auVar6._8_8_) / uStack_58;
    }
    lVar5 = uVar1 + local_68 * auVar6._0_8_;
  }
  else {
    if (param_3 != (undefined1 (*) [16])0x0) {
      auVar6 = FUN_0019af14(*(undefined8 *)*param_2,*(undefined8 *)(*param_2 + 8),uVar2,uVar3);
      *param_3 = auVar6;
    }
    lVar5 = -1;
  }
  return lVar5;
}

