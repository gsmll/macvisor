
undefined8 FUN_00054094(long param_1,long param_2,undefined1 (*param_3) [16])

{
  char cVar1;
  undefined8 uVar2;
  undefined4 *puVar3;
  long lVar4;
  undefined8 *puVar5;
  undefined1 auVar6 [16];
  undefined8 local_50;
  long lStack_48;
  long local_40;
  undefined8 uStack_38;
  
  if (param_3 == (undefined1 (*) [16])0x0) {
    auVar6 = FUN_00034a2c();
    auVar6 = (**(code **)(auVar6._8_8_ + 0x38))(auVar6._0_8_,param_1,0,0);
  }
  else {
    auVar6 = *param_3;
  }
  puVar5 = auVar6._8_8_;
  lVar4 = auVar6._0_8_;
  lStack_48 = 0;
  local_50 = 0;
  uStack_38 = 0;
  local_40 = 0;
  if (lVar4 != 0) {
    if (puVar5 == (undefined8 *)0x0) {
                    /* WARNING: Subroutine does not return */
      FUN_00054354();
    }
    (*(code *)puVar5[1])(lVar4,&local_50);
    if ((lStack_48 == param_1) && (local_40 == param_2)) {
      cVar1 = (*(code *)*puVar5)(lVar4);
      if (cVar1 != '\0') {
        uVar2 = FUN_00054034();
        return uVar2;
      }
      puVar3 = (undefined4 *)thunk_FUN_0006037c(0);
      *puVar3 = 0;
      return 1;
    }
  }
  puVar3 = (undefined4 *)thunk_FUN_0006037c();
  *puVar3 = 0x16;
  return 0;
}

