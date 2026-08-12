
void FUN_00054be8(void)

{
  code *pcVar1;
  ulong uVar2;
  ulong local_18;
  
  local_18 = 0;
  uVar2 = FUN_0005b860(&local_18);
  if (((uVar2 != 0) || (uVar2 = FUN_0005d154(0,&local_18), uVar2 != 0)) &&
     (uVar2 + local_18 < uVar2 || (uVar2 + local_18) - uVar2 < local_18)) {
                    /* WARNING: Does not return */
    pcVar1 = (code *)SoftwareBreakpoint(0x5519,0x54c2c);
    (*pcVar1)();
  }
  return;
}

