
/* WARNING: Removing unreachable block (ram,0x0005c998) */
/* WARNING: Removing unreachable block (ram,0x0005c9a0) */
/* WARNING: Removing unreachable block (ram,0x0005c9b8) */
/* WARNING: Removing unreachable block (ram,0x0005c9a8) */
/* WARNING: Removing unreachable block (ram,0x0005c9b0) */
/* WARNING: Removing unreachable block (ram,0x0005c9bc) */
/* WARNING: Removing unreachable block (ram,0x0005c9c8) */
/* WARNING: Removing unreachable block (ram,0x0005ca04) */

long FUN_0005c924(undefined8 param_1)

{
  long lVar1;
  long lVar2;
  long lVar3;
  
  if ((int)param_1 == 3) {
    lVar1 = FUN_00055afc();
    return lVar1;
  }
  lVar1 = FUN_0005ca20(param_1);
  if (((int)param_1 - 1U & 0xff) < 2) {
    do {
      lVar2 = lVar1;
      lVar3 = FUN_00055afc();
      lVar1 = FUN_0005ca20(param_1);
    } while (lVar1 != lVar2);
    return lVar2 + lVar3;
  }
                    /* WARNING: Subroutine does not return */
  FUN_0005b190(0,s_invalid_timebase__u_005bc6d7);
}

