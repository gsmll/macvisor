
int * FUN_00051fbc(long param_1)

{
  ulong uVar1;
  int *piVar2;
  
  uVar1 = (ulong)*(uint *)(param_1 + 0x10);
  if (*(uint *)(param_1 + 0x10) != 0) {
    piVar2 = (int *)(param_1 + 0x20);
    do {
      if (*piVar2 == 0x1b) {
        return piVar2 + 2;
      }
      piVar2 = (int *)((long)piVar2 + (ulong)(uint)piVar2[1]);
      uVar1 = uVar1 - 1;
    } while (uVar1 != 0);
  }
  return (int *)0x0;
}

