
void FUN_000529a0(undefined8 *param_1,undefined8 param_2)

{
  int iVar1;
  
  iVar1 = (int)param_2;
  if (iVar1 != 1) {
    if (iVar1 != 6) {
      if (iVar1 == 4) {
        FUN_0005c650(2);
        return;
      }
      param_1[1] = 0;
      param_1[2] = 0;
      *param_1 = 0;
      return;
    }
    param_2 = 3;
  }
  FUN_0005c650(param_2);
  return;
}

