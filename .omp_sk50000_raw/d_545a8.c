
void FUN_000545a8(int param_1)

{
  if (param_1 != 0) {
                    /* WARNING: Read-only address (ram,0x0064cd88) is written */
    uRam000000000064cd88 = 0;
                    /* WARNING: Read-only address (ram,0x0064cee8) is written */
    uRam000000000064cee8 = 0;
  }
  FUN_00118148(0x6ad700,2);
  FUN_00118148(0x6ad710,2);
  FUN_00118148(0x6ad720,2);
  FUN_00118148(0x6ad730,2);
  return;
}

