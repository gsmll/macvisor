
undefined8 FUN_00053568(void)

{
  code *pcVar1;
  undefined8 *puVar2;
  undefined8 uVar3;
  
  puVar2 = (undefined8 *)FUN_00053598();
  uVar3 = 0;
  if (puVar2 != (undefined8 *)0x0) {
    if (puVar2 + 1 < puVar2) {
                    /* WARNING: Does not return */
      pcVar1 = (code *)SoftwareBreakpoint(0x5519,0x53598);
      (*pcVar1)();
    }
    uVar3 = *puVar2;
  }
  return uVar3;
}

