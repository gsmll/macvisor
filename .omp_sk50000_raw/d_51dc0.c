
ulong FUN_00051dc0(long param_1)

{
  ulong uVar1;
  ulong uVar2;
  int *piVar3;
  ulong uVar4;
  
  uVar4 = (ulong)*(uint *)(param_1 + 0x10);
  if (*(uint *)(param_1 + 0x10) == 0) {
    return 0;
  }
  piVar3 = (int *)(param_1 + 0x20);
  uVar1 = 0;
  do {
    uVar2 = uVar1;
    if ((*piVar3 == 0x19) &&
       (uVar2 = *(long *)(piVar3 + 8) + *(long *)(piVar3 + 6),
       (ulong)(*(long *)(piVar3 + 8) + *(long *)(piVar3 + 6)) <= uVar1)) {
      uVar2 = uVar1;
    }
    piVar3 = (int *)((long)piVar3 + (ulong)(uint)piVar3[1]);
    uVar4 = uVar4 - 1;
    uVar1 = uVar2;
  } while (uVar4 != 0);
  return uVar2;
}

