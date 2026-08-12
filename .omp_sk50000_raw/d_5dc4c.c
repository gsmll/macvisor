
undefined8 FUN_0005dc4c(ulong param_1)

{
  long lVar1;
  
  lVar1 = FUN_0005acac(0x6b2698,1,4);
  DataMemoryBarrier(2,3);
  return *(undefined8 *)(lVar1 + (param_1 & 0xffffffff) * 8);
}

