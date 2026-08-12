
ulong FUN_00054418(ulong param_1)

{
  long lVar1;
  ulong uVar2;
  ulong local_18;
  
  local_18 = param_1;
  lVar1 = FUN_0005bc48(&local_18,0);
  if (lVar1 == 0) {
    uVar2 = 0xffff000000000000;
  }
  else {
    uVar2 = (ulong)*(ushort *)(lVar1 + 0x40) << 0x30;
  }
  return local_18 & 0xffffffffffff | uVar2;
}

