
undefined8 FUN_0005d154(long param_1,long *param_2)

{
  code *pcVar1;
  undefined8 uVar2;
  long local_28;
  
  if (param_1 == 0) {
    local_28 = 0;
    uVar2 = FUN_0006562c(s___COMPONENTNAME_005bba0f,&local_28);
  }
  else {
    uVar2 = *(undefined8 *)(param_1 + 0x20);
    local_28 = thunk_FUN_00115080(uVar2);
    if (local_28 < 0) {
                    /* WARNING: Does not return */
      pcVar1 = (code *)SoftwareBreakpoint(0x5519,0x5d184);
      (*pcVar1)();
    }
  }
  *param_2 = local_28;
  return uVar2;
}

