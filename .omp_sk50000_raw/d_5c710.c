
void FUN_0005c710(void)

{
  long lVar1;
  long lVar2;
  
  lVar2 = 0;
  lVar1 = 0x64db60;
  do {
    if (((uint)lVar2 - 1 & 0xff) < 3) {
      FUN_0005c764((uint)lVar2 & 0xff,lVar1);
    }
    lVar2 = lVar2 + 1;
    lVar1 = lVar1 + 0x50;
  } while (lVar2 != 4);
  return;
}

