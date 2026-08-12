
long FUN_0005c5b4(undefined8 param_1)

{
  long lVar1;
  long lVar2;
  undefined1 auVar3 [16];
  
  lVar1 = FUN_00034f70();
  if (lVar1 != 0) {
    auVar3 = FUN_0004ba18();
    lVar2 = (*(code *)*auVar3._8_8_)(auVar3._0_8_,param_1,lVar1,lVar1,0);
    if (lVar2 != 0) {
      FUN_004b23d8(lVar1);
      lVar1 = 0;
    }
  }
  return lVar1;
}

