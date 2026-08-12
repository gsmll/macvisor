
void FUN_0005ace4(void)

{
  code *pcVar1;
  long lVar2;
  ulong uVar3;
  undefined8 uVar4;
  
  lVar2 = FUN_00054610();
  uVar3 = *(ulong *)(lVar2 + 0x108);
  if (uVar3 == 0) {
    uVar4 = FUN_00060524();
                    /* WARNING: Subroutine does not return */
    FUN_0005b190(uVar4,s_No_commpage_was_supplied_005bc16c);
  }
  if (uVar3 <= uVar3 + 0x30) {
    return;
  }
                    /* WARNING: Does not return */
  pcVar1 = (code *)SoftwareBreakpoint(0x5519,0x5ad14);
  (*pcVar1)();
}

