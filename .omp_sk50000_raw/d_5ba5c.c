
void FUN_0005ba5c(long *param_1)

{
  code *pcVar1;
  long *plVar2;
  long lVar3;
  
  lVar3 = tpidr_el0;
  plVar2 = *(long **)(lVar3 + 0x10);
  while (*param_1 == 0) {
    if (plVar2 + 1 < plVar2) goto LAB_0005baa8;
    lVar3 = *plVar2;
    *param_1 = lVar3;
    if (*plVar2 == lVar3) {
      *plVar2 = (long)param_1;
      return;
    }
  }
  FUN_004b6864();
LAB_0005baa8:
                    /* WARNING: Does not return */
  pcVar1 = (code *)SoftwareBreakpoint(0x5519,0x5baac);
  (*pcVar1)();
}

