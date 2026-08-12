
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0005be84(ulong *param_1,int param_2)

{
  long lVar1;
  ulong *puVar2;
  ulong uVar3;
  
  lVar1 = FUN_0005acac(0x6b2568,1,1);
  if (param_2 == 0) {
    puVar2 = (ulong *)(lVar1 + 0x10);
    *(long *)(lVar1 + 0x18) = *(long *)(lVar1 + 0x18) + 1;
  }
  else {
    puVar2 = (ulong *)(lVar1 + 0x20);
  }
  do {
    uVar3 = *puVar2;
    *param_1 = uVar3 & 0xfffffffff | 0x2000000000;
  } while (*puVar2 != uVar3);
  *puVar2 = (ulong)param_1;
  if (_DAT_006b2560 == (code *)0x0) {
    return;
  }
                    /* WARNING: Could not recover jumptable at 0x0005bf10. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*_DAT_006b2560)(param_1,1);
  return;
}

