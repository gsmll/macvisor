
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0005dd70(void)

{
  if (_DAT_006b2690 == 0) {
    _DAT_006b2690 = 0x65c560;
  }
                    /* WARNING: Could not recover jumptable at 0x0005dd90. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(_DAT_006b2690 + 0x18))();
  return;
}

