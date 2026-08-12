
int * FUN_00051e0c(long param_1,int *param_2)

{
  code *pcVar1;
  int *piVar2;
  int *piVar3;
  ulong uVar4;
  
  uVar4 = (ulong)*(uint *)(param_1 + 0x10);
  if (*(uint *)(param_1 + 0x10) != 0) {
    piVar2 = (int *)(param_1 + 0x20);
    do {
      piVar3 = param_2;
      if (*piVar2 == 0x19) {
        if (param_2 == (int *)0x0) {
          if (piVar2 + 0x12 < piVar2) {
                    /* WARNING: Does not return */
            pcVar1 = (code *)SoftwareBreakpoint(0x5519,0x51e5c);
            (*pcVar1)();
          }
          return piVar2;
        }
        piVar3 = (int *)0x0;
        if (param_2 != piVar2) {
          piVar3 = param_2;
        }
      }
      piVar2 = (int *)((long)piVar2 + (ulong)(uint)piVar2[1]);
      uVar4 = uVar4 - 1;
      param_2 = piVar3;
    } while (uVar4 != 0);
  }
  return (int *)0x0;
}

