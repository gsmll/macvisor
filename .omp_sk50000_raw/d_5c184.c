
ulong FUN_0005c184(undefined8 param_1,ulong param_2)

{
  ulong uVar1;
  long lVar2;
  code *pcVar3;
  long *plVar4;
  ulong *puVar5;
  ulong *puVar6;
  
  lVar2 = tpidr_el0;
  plVar4 = (long *)**(long **)(lVar2 + 0x10);
  if (plVar4 == (long *)0x0) {
    puVar6 = (ulong *)0x0;
  }
  else {
    puVar5 = (ulong *)0x0;
    do {
      puVar6 = (ulong *)plVar4[3];
      if ((int)plVar4[2] != 5 || (int)plVar4[1] != 1) {
        puVar6 = puVar5;
      }
      plVar4 = (long *)*plVar4;
      puVar5 = puVar6;
    } while (plVar4 != (long *)0x0);
  }
  puVar5 = puVar6 + 0x10;
  if (puVar5 <= puVar6 + 0x12) {
    FUN_0005cb9c(puVar5);
    if ((param_2 < 0x79) && (*puVar6 <= 0x78 - param_2)) {
      uVar1 = (long)puVar6 + *puVar6 + 8;
      FUN_00117cc4(uVar1,param_1,param_2);
      if (uVar1 + param_2 < uVar1) goto LAB_0005c274;
      *puVar6 = *puVar6 + param_2;
    }
    else {
      param_2 = 0;
    }
    if (puVar6 <= puVar6 + 0x12) {
      FUN_0005ce54(puVar5);
      return param_2;
    }
  }
LAB_0005c274:
                    /* WARNING: Does not return */
  pcVar3 = (code *)SoftwareBreakpoint(0x5519,0x5c278);
  (*pcVar3)();
}

