
char * FUN_00050c88(char *param_1,long param_2)

{
  char cVar1;
  char *pcVar2;
  code *pcVar3;
  long lVar4;
  
  lVar4 = thunk_FUN_00114fe0();
  if (lVar4 == param_2) {
    param_1 = (char *)0x0;
  }
  else {
    if (param_2 == 0) {
LAB_00050ce4:
                    /* WARNING: Does not return */
      pcVar3 = (code *)SoftwareBreakpoint(0x5519,0x50ce8);
      (*pcVar3)();
    }
    pcVar2 = param_1;
    do {
      if (param_1 + param_2 < pcVar2 + 1) goto LAB_00050ce4;
      cVar1 = *pcVar2;
      pcVar2 = pcVar2 + 1;
    } while (cVar1 != '\0');
  }
  return param_1;
}

