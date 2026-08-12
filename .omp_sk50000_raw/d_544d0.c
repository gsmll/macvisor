
ulong FUN_000544d0(long param_1)

{
  int iVar1;
  undefined8 uVar2;
  ulong uVar3;
  
  uVar2 = FUN_00060524();
  if ((param_1 == -0x14e5fd406ebfed46 || param_1 == -0x55e9fc042d7fffe4) &&
     (iVar1 = FUN_00062848(), iVar1 != 0)) {
    uVar3 = FUN_000628d8(uVar2,*(undefined8 *)(param_1 + 0x58));
  }
  else {
    iVar1 = FUN_0011817c(*(undefined8 *)(param_1 + 0x58));
    uVar3 = (ulong)(iVar1 != 0);
  }
  return uVar3;
}

