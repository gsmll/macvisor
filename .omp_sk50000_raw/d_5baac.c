
long FUN_0005baac(int param_1,int param_2)

{
  long lVar1;
  long lVar2;
  long *plVar3;
  
  lVar2 = tpidr_el0;
  plVar3 = (long *)**(long **)(lVar2 + 0x10);
  if (plVar3 == (long *)0x0) {
    lVar2 = 0;
  }
  else {
    lVar1 = 0;
    do {
      lVar2 = plVar3[3];
      if ((int)plVar3[2] != param_2 || (int)plVar3[1] != param_1) {
        lVar2 = lVar1;
      }
      plVar3 = (long *)*plVar3;
      lVar1 = lVar2;
    } while (plVar3 != (long *)0x0);
  }
  return lVar2;
}

