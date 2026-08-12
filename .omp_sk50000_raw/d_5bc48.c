
void FUN_0005bc48(ulong *param_1,int param_2)

{
  long *plVar1;
  ulong uVar2;
  
  plVar1 = (long *)FUN_0005acac(0x6b2568,1,1);
  plVar1 = (long *)*plVar1;
  do {
    if (plVar1 == (long *)0x0) {
      return;
    }
    if (param_2 == 0) {
      uVar2 = *param_1;
      if (((ulong)plVar1[5] <= uVar2) && (uVar2 - plVar1[5] < (ulong)plVar1[6])) {
        uVar2 = uVar2 - plVar1[4];
        goto LAB_0005bcd0;
      }
    }
    else if (*(short *)(plVar1 + 8) == (short)(*param_1 >> 0x30)) {
      uVar2 = *param_1 & 0xffffffffffff;
LAB_0005bcd0:
      *param_1 = uVar2;
      return;
    }
    plVar1 = (long *)*plVar1;
  } while( true );
}

