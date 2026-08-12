
void FUN_00034ad0(void)

{
  code *pcVar1;
  int iVar2;
  long lVar3;
  ulong uVar4;
  undefined8 uVar5;
  undefined1 auVar6 [16];
  
  uVar5 = 8;
  lVar3 = FUN_0005acac(0x6af188,4);
  if (*(int *)(lVar3 + 0x48) != 0) {
    *(int *)(lVar3 + 0x48) = *(int *)(lVar3 + 0x48) + -1;
    FUN_000348d0();
    return;
  }
  auVar6 = FUN_004b26d4();
  uVar4 = auVar6._0_8_;
  if (uVar4 <= uVar4 + 0x10) {
    iVar2 = FUN_00118148(uVar4,0);
    if (iVar2 == 0) {
      *(undefined8 *)(uVar4 + 0x10) = 0;
      *(undefined8 *)(uVar4 + 0x18) = 0x100;
      *(long *)(uVar4 + 0x20) = auVar6._8_8_;
      *(undefined8 *)(uVar4 + 0x28) = uVar5;
      return;
    }
                    /* WARNING: Subroutine does not return */
    FUN_004afae4(s__VAS_abort_in_function__s_at_lin_005aed68);
  }
                    /* WARNING: Does not return */
  pcVar1 = (code *)SoftwareBreakpoint(0x5519,0x34b70);
  (*pcVar1)();
}

