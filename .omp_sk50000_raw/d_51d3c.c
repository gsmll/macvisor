
ulong FUN_00051d3c(long param_1)

{
  int iVar1;
  ulong uVar2;
  ulong uVar3;
  ulong uVar4;
  int *piVar5;
  
  uVar4 = (ulong)*(uint *)(param_1 + 0x10);
  if (*(uint *)(param_1 + 0x10) == 0) {
    uVar3 = 0xffffffffffffffff;
  }
  else {
    piVar5 = (int *)(param_1 + 0x20);
    uVar2 = 0xffffffffffffffff;
    do {
      uVar3 = uVar2;
      if (((*piVar5 == 0x19) &&
          (iVar1 = thunk_FUN_00114e50(piVar5 + 2,s___PAGEZERO_005bb8fa,0x10), iVar1 != 0)) &&
         (uVar3 = *(ulong *)(piVar5 + 6), uVar2 <= *(ulong *)(piVar5 + 6))) {
        uVar3 = uVar2;
      }
      piVar5 = (int *)((long)piVar5 + (ulong)(uint)piVar5[1]);
      uVar4 = uVar4 - 1;
      uVar2 = uVar3;
    } while (uVar4 != 0);
  }
  return uVar3;
}

