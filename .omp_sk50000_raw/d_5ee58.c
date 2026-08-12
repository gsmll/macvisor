
ulong FUN_0005ee58(ulong param_1,ulong param_2,uint param_3,int param_4)

{
  ulong uVar1;
  
  uVar1 = 0x1000;
  if (param_4 == 0) {
    uVar1 = 0;
  }
  return param_1 & 0x3f | (param_2 & 7) << 6 | (ulong)param_3 << 0x10 | uVar1;
}

