
undefined8 FUN_0005cdbc(ulong *param_1)

{
  code *pcVar1;
  ulong uVar2;
  ulong uVar3;
  
  uVar3 = *param_1;
  uVar2 = FUN_00060524();
  if (uVar2 + 0x178 < uVar2) {
                    /* WARNING: Does not return */
    pcVar1 = (code *)SoftwareBreakpoint(0x5519,0x5ce54);
    (*pcVar1)();
  }
  if ((((uint)(uVar2 >> 0xe) ^ (uint)uVar3) & 0xffffff) == 0) {
    if (*(short *)((long)param_1 + 0xe) != 0) {
      *(short *)((long)param_1 + 0xe) = *(short *)((long)param_1 + 0xe) + -1;
      *(short *)((long)param_1 + 0xc) = *(short *)((long)param_1 + 0xc) + 1;
      goto LAB_0005ce2c;
    }
  }
  else {
    do {
      if (uVar3 != 0) {
        return 0;
      }
      uVar3 = *param_1;
    } while (uVar3 != 0);
    *param_1 = uVar2 >> 0xe & 0xffffff;
    if (*(short *)((long)param_1 + 0xc) == 0) {
LAB_0005ce2c:
      FUN_0005afe8(uVar2,param_1,&stack0xfffffffffffffff0);
      return 1;
    }
  }
  return 0;
}

