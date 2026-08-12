
undefined8 FUN_00013a08(undefined8 *param_1,undefined8 param_2,ulong param_3)

{
  undefined8 uVar1;
  undefined8 *puVar2;
  
  puVar2 = (undefined8 *)param_1[6];
  if (puVar2 == (undefined8 *)0x0) {
    if (0x1b8 < param_3) {
      return 5;
    }
    FUN_00012d70(param_1);
    FUN_00013af0(*param_1);
    FUN_0005d470(0x6ae1b8,&DAT_00013c88,0);
    uVar1 = FUN_00013cfc();
    *param_1 = uVar1;
  }
  else {
    if ((ulong)puVar2[1] < param_3) {
      return 5;
    }
    *param_1 = *puVar2;
  }
  param_1[2] = 0;
  param_1[3] = param_3;
  *(undefined2 *)((long)param_1 + 0x2a) = 0;
  return 0;
}

