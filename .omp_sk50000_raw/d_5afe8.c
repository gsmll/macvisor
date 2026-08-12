
void FUN_0005afe8(long param_1,undefined8 param_2,undefined8 param_3)

{
  char *pcVar1;
  ulong uVar2;
  
  pcVar1 = (char *)FUN_0005acac(0x6b04b8,1,3);
  if ((*pcVar1 != '\x02') || (uVar2 = FUN_004b5fb8(param_1,param_3,param_2), (uVar2 & 1) != 0)) {
    *(long *)(param_1 + 0x58) = *(long *)(param_1 + 0x58) + 1;
  }
  return;
}

