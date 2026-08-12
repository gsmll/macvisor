
void FUN_0005c764(ulong param_1,long param_2)

{
  long lVar1;
  code *pcVar2;
  ulong uVar3;
  ulong uVar4;
  ulong uVar5;
  ulong uVar6;
  
  lVar1 = (param_1 & 0xffffffff) * 0x50;
  uVar4 = lVar1 + 0x64db60;
  uVar5 = lVar1 + 0x64dbb0;
  if ((uVar4 < 0x64db60 || 0x64dca0 < uVar5) || uVar5 < uVar4) {
                    /* WARNING: Does not return */
    pcVar2 = (code *)SoftwareBreakpoint(0x5519,0x5c858);
    (*pcVar2)();
  }
  FUN_00117cc4(param_2,uVar4,0x50);
  if ((*(char *)(param_2 + 0x20) == '\x01') && (*(long *)(param_2 + 0x28) != 0)) {
    return;
  }
  if ((int)param_1 - 1U < 3) {
    uVar3 = FUN_00055b20();
    *(ulong *)(param_2 + 0x28) = uVar3;
    uVar5 = uVar3;
    uVar4 = 1000000000;
    do {
      uVar6 = uVar4;
      uVar4 = 0;
      if (uVar6 != 0) {
        uVar4 = uVar5 / uVar6;
      }
      uVar4 = uVar5 - uVar4 * uVar6;
      uVar5 = uVar6;
    } while (uVar4 != 0);
    uVar5 = 0;
    if (uVar6 != 0) {
      uVar5 = uVar3 / uVar6;
    }
    uVar4 = 0;
    if (uVar6 != 0) {
      uVar4 = 1000000000 / uVar6;
    }
    *(ulong *)(param_2 + 0x30) = uVar5;
    *(ulong *)(param_2 + 0x38) = uVar4;
    FUN_0005cb24(param_1,0xffffffffffffffff,param_2 + 0x10,0);
    return;
  }
                    /* WARNING: Subroutine does not return */
  FUN_0005b190(0,s_invalid_timebase__u_005bc6d7);
}

