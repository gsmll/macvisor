
undefined8 FUN_0005dab8(code *param_1,ulong param_2,undefined1 *param_3,undefined8 param_4)

{
  code *pcVar1;
  ulong uVar2;
  undefined8 uVar3;
  ulong uVar4;
  long lVar5;
  
  uVar2 = FUN_00060524();
  if (param_2 == uVar2) {
    uVar4 = uVar2;
    if (uVar2 + 0x178 < param_2) {
                    /* WARNING: Does not return */
      pcVar1 = (code *)SoftwareBreakpoint(0x5519,0x5db7c);
      (*pcVar1)();
    }
  }
  else {
    uVar4 = param_2;
    if (param_3 != (undefined1 *)0x0) {
      lVar5 = *(long *)(uVar2 + 0x70);
      uVar2 = FUN_0005fdac(param_2,lVar5);
      if ((uVar2 & 1) == 0) {
        *param_3 = 1;
        return 0;
      }
      goto LAB_0005db2c;
    }
  }
  lVar5 = *(long *)(uVar4 + 0x28);
LAB_0005db2c:
  uVar3 = (*param_1)(lVar5,param_4);
  uVar2 = FUN_00060524();
  if ((param_3 != (undefined1 *)0x0) && (param_2 != uVar2)) {
    do {
      CallSupervisor(4);
    } while (lVar5 == 1);
  }
  return uVar3;
}

