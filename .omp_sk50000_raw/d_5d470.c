
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0005d470(uint *param_1,code *param_2,undefined8 param_3)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  code *pcVar4;
  uint uVar5;
  ulong uVar6;
  long lVar7;
  undefined8 uVar8;
  ulong uVar9;
  
  if (*param_1 != 0xffffffff) {
    uVar2 = (uint)param_1 >> 4 & 0xf;
    uVar6 = FUN_00060524();
    uVar9 = _DAT_006ad900 >> 10;
    lVar7 = FUN_00060524();
    *(ulong *)(lVar7 + 0x78) = uVar9;
    uVar8 = FUN_0005dc4c(uVar2);
    uVar1 = (uint)(uVar6 >> 0xc) & 0x3fffffc;
    uVar5 = *param_1;
    if (uVar5 == 0) {
      *param_1 = uVar1 | 1;
      (*param_2)(param_3);
      uVar5 = *param_1;
      *param_1 = 0xffffffff;
      LORelease();
      if (uVar5 == (uVar1 | 3)) {
        FUN_0005dd70(uVar2,param_1,6,0);
        return;
      }
    }
    else {
      uVar3 = uVar5 >> 2 & 0xffffff;
      uVar1 = uVar5;
      if (((uVar5 >> 2 & 0xffffff) << 2 | 1) == uVar5) {
        uVar8 = FUN_0005dc4c(uVar2);
        uVar1 = *param_1;
        if (uVar1 == uVar5) {
          *param_1 = uVar3 << 2 | 3;
          goto LAB_0005d584;
        }
      }
      while (uVar1 != 0xffffffff) {
LAB_0005d584:
        uVar6 = FUN_000606b0(uVar3);
        if (uVar6 + 0x178 < uVar6) {
                    /* WARNING: Does not return */
          pcVar4 = (code *)SoftwareBreakpoint(0x5519,0x5d5dc);
          (*pcVar4)();
        }
        FUN_0005dc8c(uVar2,param_1,uVar8,uVar6,0);
        uVar1 = *param_1;
      }
    }
  }
  return;
}

