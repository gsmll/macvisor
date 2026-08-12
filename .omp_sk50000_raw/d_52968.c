
void FUN_00052968(void)

{
  int iVar1;
  long lVar2;
  undefined8 uVar3;
  undefined8 *extraout_x8;
  
  lVar2 = FUN_00034f70();
  if (lVar2 != 0) {
    return;
  }
  lVar2 = FUN_004b5e48();
  if (lVar2 != 0) {
    FUN_004b23d8();
    return;
  }
  uVar3 = FUN_004b5e60();
  iVar1 = (int)uVar3;
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
    uVar3 = 3;
  }
  FUN_0005c650(uVar3);
  return;
}

