
void FUN_00052994(void)

{
  int iVar1;
  undefined8 uVar2;
  undefined8 *extraout_x8;
  
  uVar2 = FUN_004b5e60();
  iVar1 = (int)uVar2;
  if (iVar1 != 1) {
    if (iVar1 != 6) {
      if (iVar1 == 4) {
        FUN_0005c650(2);
        return;
      }
      extraout_x8[1] = 0;
      extraout_x8[2] = 0;
      *extraout_x8 = 0;
      return;
    }
    uVar2 = 3;
  }
  FUN_0005c650(uVar2);
  return;
}

