
void FUN_000139ac(undefined8 *param_1)

{
  if ((*(byte *)((long)param_1 + 0x29) & 1) == 0) {
    if (param_1[6] == 0) {
      FUN_00012d70(param_1);
      FUN_00013af0(*param_1);
    }
    *param_1 = 0;
    param_1[6] = 0;
    param_1[3] = 0;
    param_1[4] = 0;
    param_1[2] = 0;
    *(undefined1 *)((long)param_1 + 0x29) = 1;
  }
  return;
}

