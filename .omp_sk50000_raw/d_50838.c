
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 FUN_00050838(long *param_1,undefined8 *param_2,ulong *param_3)

{
  code *pcVar1;
  undefined8 uVar2;
  undefined1 *local_38;
  
  local_38 = &DAT_006af868;
  FUN_0005d470(0x6af880,FUN_000508e8,&local_38);
  uVar2 = _DAT_006af870;
  if ((_DAT_006af868 == 0) || (_DAT_006af878 == 0)) {
    uVar2 = 0;
  }
  else {
    *param_1 = _DAT_006af868;
    *param_2 = uVar2;
    if ((_DAT_006af878 != 0 && _DAT_006af878 + 8 <= _DAT_006af878) &&
        (_DAT_006af878 == 0 || _DAT_006af878 != _DAT_006af878 + 8)) {
                    /* WARNING: Does not return */
      pcVar1 = (code *)SoftwareBreakpoint(0x5519,0x508e8);
      (*pcVar1)();
    }
    *param_3 = _DAT_006af878;
    uVar2 = 1;
  }
  return uVar2;
}

