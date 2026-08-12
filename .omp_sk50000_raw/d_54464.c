
void FUN_00054464(long param_1)

{
  int iVar1;
  undefined8 uVar2;
  
  uVar2 = FUN_00060524();
  if ((param_1 == -0x14e5fd406ebfed46 || param_1 == -0x55e9fc042d7fffe4) &&
     (iVar1 = FUN_00062848(), iVar1 != 0)) {
    FUN_0006285c(uVar2,*(undefined8 *)(param_1 + 0x58));
    return;
  }
  FUN_00118164(*(undefined8 *)(param_1 + 0x58));
  return;
}

