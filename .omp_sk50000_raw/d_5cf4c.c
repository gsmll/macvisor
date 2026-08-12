
/* WARNING: Removing unreachable block (ram,0x0005cf94) */
/* WARNING: Removing unreachable block (ram,0x0005cfa4) */
/* WARNING: Removing unreachable block (ram,0x0005cfb0) */
/* WARNING: Removing unreachable block (ram,0x0005cfbc) */

void FUN_0005cf4c(long param_1,undefined8 param_2)

{
  long *plVar1;
  long lVar2;
  
  if (((int)param_2 == 0) || ((DAT_006ad6e8 & 1) == 0)) {
    lVar2 = 2;
    plVar1 = &__shared_cache;
    do {
      if (*plVar1 == param_1) {
        FUN_0005d03c(plVar1,param_2);
      }
      plVar1 = plVar1 + 7;
      lVar2 = lVar2 + -1;
    } while (lVar2 != 0);
  }
  return;
}

