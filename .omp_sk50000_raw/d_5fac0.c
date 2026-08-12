
void FUN_0005fac0(long param_1)

{
  int *piVar1;
  ushort *puVar2;
  ushort uVar3;
  int iVar4;
  uint uVar5;
  code *pcVar6;
  undefined8 uVar7;
  ulong uVar8;
  long lVar9;
  
  (**(code **)(param_1 + 0x18))(*(undefined8 *)(param_1 + 0x20));
  uVar7 = FUN_0005fad8();
  uVar8 = FUN_00060524();
  if (uVar8 <= uVar8 + 0x178) {
    FUN_0005b0bc();
    FUN_00063dd4();
    *(undefined8 *)(uVar8 + 0x40) = uVar7;
    *(undefined1 *)(uVar8 + 0x80) = 1;
    piVar1 = (int *)(uVar8 + 0x84);
    uVar5 = (uint)piVar1 >> 4 & 0xf;
    uVar7 = FUN_0005dc4c(uVar5);
    iVar4 = *(int *)(uVar8 + 0x84);
    while (iVar4 == 0) {
      FUN_0005dc8c(uVar5,piVar1,uVar7,0,0);
      uVar7 = FUN_0005dc4c(uVar5);
      iVar4 = *piVar1;
    }
    FUN_0005dd70((uint)(uVar8 + 0x80) >> 4 & 0xf,uVar8 + 0x80,5,0);
    if (iVar4 == 2) {
      FUN_0005bf20(uVar8);
      lVar9 = FUN_0005bb68();
      puVar2 = (ushort *)(lVar9 + 0x38);
      uVar3 = *puVar2;
      *puVar2 = uVar3 - 1;
      FUN_0005be84(CONCAT44((int)((ulong)puVar2 >> 0x20),(uint)uVar3),uVar8,1);
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

