
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

long FUN_00013be4(void)

{
  long *plVar1;
  long *plVar2;
  ulong uVar3;
  code *pcVar4;
  long lVar5;
  char *pcVar6;
  
  uVar3 = _DAT_006ae1b0;
  if (_DAT_006ae1b0 < 0x20) {
    lVar5 = FUN_00063a50();
    plVar2 = (long *)tpidr_el0;
    if (*(long *)(lVar5 + (uVar3 - 1) * 8 + 0x1f8) != -1) {
      if (plVar2[0x1f] == 0) {
        plVar1 = plVar2 + (uVar3 - 1);
        if ((plVar2 <= plVar1 && plVar1 + 1 <= plVar2 + 0x1f) && plVar1 <= plVar1 + 1) {
          return *plVar1;
        }
                    /* WARNING: Does not return */
        pcVar4 = (code *)SoftwareBreakpoint(0x5519,0x13c88);
        (*pcVar4)();
      }
      pcVar6 = s_getting_key__lu_while_destructor_005ab2c6;
      goto LAB_00013c7c;
    }
  }
  else {
    FUN_004b01e8();
  }
  pcVar6 = s_getting_key__lu_which_is_deleted_005ab2a5;
LAB_00013c7c:
                    /* WARNING: Subroutine does not return */
  FUN_0005b190(0,pcVar6);
}

