
void FUN_0005ee7c(void)

{
  long lVar1;
  uint uVar2;
  
  if ((DAT_006b26a0 & 1) == 0) {
    uVar2 = FUN_0006054c();
    if ((uVar2 & 1) == 0) {
      FUN_00064108();
    }
    lVar1 = FUN_0005bb68();
    *(short *)(lVar1 + 0x38) = *(short *)(lVar1 + 0x38) + 1;
    DAT_006b26a0 = 1;
  }
  return;
}

