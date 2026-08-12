
void FUN_00054c9c(undefined8 param_1,undefined8 param_2)

{
  code *pcVar1;
  long lVar2;
  undefined8 local_28;
  
  local_28 = param_1;
  lVar2 = FUN_0005bc48(&local_28,1);
  if (lVar2 != 0) {
    if (*(ulong *)(lVar2 + 0x60) >> 4 < *(ulong *)(lVar2 + 0x58)) {
                    /* WARNING: Does not return */
      pcVar1 = (code *)SoftwareBreakpoint(0x5519,0x54cfc);
      (*pcVar1)();
    }
    FUN_000520f0(local_28,param_2,*(ulong *)(lVar2 + 0x58),*(undefined8 *)(lVar2 + 0x68),
                 *(undefined8 *)(lVar2 + 0x70));
  }
  return;
}

