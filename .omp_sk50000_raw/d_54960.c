
void FUN_00054960(undefined8 param_1)

{
  long lVar1;
  
  lVar1 = FUN_0005baac(2,6);
  if (lVar1 != 0) {
    return;
  }
  uRam000000000064cd10 = param_1;
                    /* WARNING: Read-only address (ram,0x0064cd10) is written */
  FUN_0005ba5c();
  return;
}

