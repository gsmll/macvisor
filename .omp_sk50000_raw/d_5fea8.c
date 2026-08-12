
void FUN_0005fea8(void)

{
  char cVar1;
  long lVar2;
  ulong extraout_x18;
  
  lVar2 = FUN_00060524();
  cVar1 = *(char *)(lVar2 + 0x69);
  if (cVar1 == '\0') {
    FUN_004b6fd8();
  }
  else {
    *(char *)(lVar2 + 0x69) = cVar1 + -1;
    if ((cVar1 != '\x01') || ((extraout_x18 & 1) != 0)) {
      return;
    }
  }
                    /* WARNING: Subroutine does not return */
  FUN_004afae4(s_already_disabled___lx_005bd203);
}

