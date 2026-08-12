
ulong FUN_0005c278(ulong param_1,ulong param_2)

{
  ulong *puVar1;
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
    lVar2 = *puVar6 - param_2;
    if (*puVar6 < param_2) {
      param_2 = 0;
    }
    else {
      puVar1 = (ulong *)((long)(puVar6 + 1) + lVar2);
      if (((0x78U - lVar2 < param_2 || puVar5 < puVar1) || puVar1 < puVar6 + 1) ||
         (FUN_00117cc4(param_1,puVar1,param_2), param_1 + param_2 < param_1)) goto LAB_0005c320;
      thunk_FUN_00114330(puVar1,param_2);
      *puVar6 = *puVar6 - param_2;
    }
    if (puVar6 <= puVar6 + 0x12) {
      FUN_0005ce54(puVar5);
      return param_2;
    }
  }
LAB_0005c320:
                    /* WARNING: Does not return */
  pcVar3 = (code *)SoftwareBreakpoint(0x5519,0x5c324);
  (*pcVar3)();
}

