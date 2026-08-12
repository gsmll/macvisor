
void FUN_0005b05c(long param_1,undefined8 param_2)

{
  char *pcVar1;
  
  pcVar1 = (char *)FUN_0005acac(0x6b04b8,1,3);
  if (*pcVar1 == '\x02') {
    FUN_004b6194(param_1,param_2);
  }
  *(long *)(param_1 + 0x58) = *(long *)(param_1 + 0x58) + -1;
  return;
}

