
void FUN_0005fe48(void)

{
  long lVar1;
  char cVar2;
  ulong extraout_x18;
  ulong extraout_x18_00;
  ulong uVar3;
  
  lVar1 = FUN_00060524();
  cVar2 = *(char *)(lVar1 + 0x69);
  uVar3 = extraout_x18;
  if (cVar2 != '\0') {
    if (cVar2 != -1) goto LAB_0005fe84;
    lVar1 = FUN_004b6fc0();
    uVar3 = extraout_x18_00;
  }
  if ((uVar3 & 1) != 0) {
                    /* WARNING: Subroutine does not return */
    FUN_004afae4(s_already_enabled___lx_005bd1ee);
  }
  cVar2 = *(char *)(lVar1 + 0x69);
LAB_0005fe84:
  *(char *)(lVar1 + 0x69) = cVar2 + '\x01';
  return;
}

