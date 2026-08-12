
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 FUN_0005cc3c(ulong *param_1,undefined8 param_2)

{
  ulong uVar1;
  uint uVar2;
  code *pcVar3;
  int iVar4;
  ulong uVar5;
  undefined8 uVar6;
  long lVar7;
  ulong uVar8;
  ulong uVar9;
  
  uVar2 = (uint)param_1 >> 4 & 0xf;
  if ((byte)param_1[1] != 0) {
    uVar2 = (byte)param_1[1] - 1;
  }
  uVar5 = FUN_00060524();
  uVar6 = FUN_0005dc4c(uVar2 & 0xff);
  uVar8 = _DAT_006ad900 >> 10;
  lVar7 = FUN_00060524();
  *(ulong *)(lVar7 + 0x78) = uVar8;
  uVar9 = uVar5 >> 0xe & 0xffffff;
  uVar8 = *param_1;
  if (uVar8 == 0) {
    *param_1 = uVar9;
  }
  if ((uVar8 != 0) && ((((uint)uVar8 ^ (uint)(uVar5 >> 0xe)) & 0xffffff) == 0)) {
    uVar6 = FUN_00060524();
                    /* WARNING: Subroutine does not return */
    FUN_0005b190(uVar6,s_mutex_recursion_limit_exceeded_005bc73c);
  }
  if (uVar8 != 0) {
    uVar5 = 0;
    do {
      while (((uint)uVar8 >> 0x18 & 1) == 0) {
        uVar1 = *param_1;
        if (uVar1 == uVar8) {
          *param_1 = uVar8 | 0x1000000;
          break;
        }
        uVar8 = uVar1;
        if ((uVar1 == 0) && (uVar8 = *param_1, uVar8 == 0)) {
          *param_1 = uVar5 | uVar9;
          goto LAB_0005ccc8;
        }
      }
      uVar8 = FUN_000606b0((uint)uVar8 & 0xffffff);
      if (uVar8 + 0x178 < uVar8) {
                    /* WARNING: Does not return */
        pcVar3 = (code *)SoftwareBreakpoint(0x5519,0x5cdac);
        (*pcVar3)();
      }
      iVar4 = FUN_0005dc8c(uVar2 & 0xff,param_1,uVar6,uVar8,param_2);
      if (iVar4 == 1) {
        uVar5 = 0;
      }
      else if (iVar4 == 2) {
        uVar5 = 0x1000000;
      }
      else if (iVar4 == 3) {
        return 0;
      }
      uVar6 = FUN_0005dc4c(uVar2 & 0xff);
      uVar8 = *param_1;
    } while (uVar8 != 0);
    *param_1 = uVar5 | uVar9;
  }
LAB_0005ccc8:
  uVar6 = FUN_00060524();
  FUN_0005afe8(uVar6,param_1,&stack0xfffffffffffffff0);
  return 1;
}

