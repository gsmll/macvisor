
void FUN_0003c32c(long *param_1)

{
  code *pcVar1;
  long lVar2;
  
  lVar2 = *param_1;
  if (lVar2 != 0) {
    if (*(long *)(lVar2 + 0x58U) != 0) {
      if ((long *)(lVar2 + 0x60U) < (long *)(lVar2 + 0x58U)) goto LAB_0003c3b8;
      FUN_0003c32c();
    }
    if (*(long *)(lVar2 + 0x60U) != 0) {
      if ((long *)(lVar2 + 0x68U) < (long *)(lVar2 + 0x60U)) {
LAB_0003c3b8:
                    /* WARNING: Does not return */
        pcVar1 = (code *)SoftwareBreakpoint(0x5519,0x3c3bc);
        (*pcVar1)();
      }
      FUN_0003c32c();
    }
    if (*(long *)(lVar2 + 0x70) != 0) {
      FUN_00031594(*(undefined8 *)(lVar2 + 0x50));
      *(undefined8 *)(lVar2 + 0x70) = 0;
    }
    FUN_0003c3bc(lVar2);
    *(undefined8 *)(lVar2 + 0x50) = 0;
    FUN_00033148(lVar2);
    *param_1 = 0;
  }
  return;
}

