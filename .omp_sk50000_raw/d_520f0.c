
long FUN_000520f0(ulong param_1,long *param_2,long param_3,long param_4,long param_5)

{
  long lVar1;
  long *plVar2;
  long lVar3;
  long lVar4;
  
  if (param_3 == 0) {
    lVar1 = 0;
    lVar3 = 0;
  }
  else {
    lVar3 = 0;
    lVar1 = 0;
    plVar2 = (long *)(param_4 + 8);
    do {
      if ((((*(byte *)((long)plVar2 + -4) & 0xee) == 0xe) && (lVar4 = *plVar2, lVar4 - 1U < param_1)
          ) && (param_1 - lVar4 < param_1 - lVar3)) {
        lVar1 = (ulong)*(uint *)(plVar2 + -1) + param_5;
        lVar3 = lVar4;
      }
      plVar2 = plVar2 + 2;
      param_3 = param_3 + -1;
    } while (param_3 != 0);
  }
  *param_2 = lVar3;
  return lVar1;
}

