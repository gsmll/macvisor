
void FUN_0005fad8(undefined8 param_1)

{
  int *piVar1;
  ushort *puVar2;
  ushort uVar3;
  int iVar4;
  uint uVar5;
  code *pcVar6;
  ulong uVar7;
  undefined8 uVar8;
  long lVar9;
  
  uVar7 = FUN_00060524();
  if (uVar7 <= uVar7 + 0x178) {
    FUN_0005b0bc();
    FUN_00063dd4();
    *(undefined8 *)(uVar7 + 0x40) = param_1;
    *(undefined1 *)(uVar7 + 0x80) = 1;
    piVar1 = (int *)(uVar7 + 0x84);
    uVar5 = (uint)piVar1 >> 4 & 0xf;
    uVar8 = FUN_0005dc4c(uVar5);
    iVar4 = *(int *)(uVar7 + 0x84);
    while (iVar4 == 0) {
      FUN_0005dc8c(uVar5,piVar1,uVar8,0,0);
      uVar8 = FUN_0005dc4c(uVar5);
      iVar4 = *piVar1;
    }
    FUN_0005dd70((uint)(uVar7 + 0x80) >> 4 & 0xf,uVar7 + 0x80,5,0);
    if (iVar4 == 2) {
      FUN_0005bf20(uVar7);
      lVar9 = FUN_0005bb68();
      puVar2 = (ushort *)(lVar9 + 0x38);
      uVar3 = *puVar2;
      *puVar2 = uVar3 - 1;
      FUN_0005be84(CONCAT44((int)((ulong)puVar2 >> 0x20),(uint)uVar3),uVar7,1);
    }
    FUN_00060524();
    FUN_0005db7c();
                    /* WARNING: Subroutine does not return */
    FUN_0005b190(0,s_suspend_should_not_return_005bd02d);
  }
                    /* WARNING: Does not return */
  pcVar6 = (code *)SoftwareBreakpoint(0x5519,0x5fbc0);
  (*pcVar6)();
}

