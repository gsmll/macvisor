
undefined8 FUN_000529d4(undefined8 param_1)

{
  int iVar1;
  undefined8 uVar2;
  
  iVar1 = (int)param_1;
  if (iVar1 != 1) {
    if (iVar1 != 6) {
      if (iVar1 == 4) {
        uVar2 = FUN_0005c924(2);
        return uVar2;
      }
      return 0xffffffffffffffff;
    }
    param_1 = 3;
  }
  uVar2 = FUN_0005c924(param_1);
  return uVar2;
}

