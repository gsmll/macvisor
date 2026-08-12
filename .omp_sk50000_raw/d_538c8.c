
int FUN_000538c8(undefined8 param_1,ulong param_2,ulong param_3,undefined8 param_4)

{
  bool bVar1;
  ulong uVar2;
  code *pcVar3;
  int iVar4;
  long lVar5;
  ulong uVar6;
  ulong uVar7;
  int iVar8;
  
  lVar5 = thunk_FUN_001144a0(param_2,0);
  uVar7 = param_3;
  if ((lVar5 == 0) || (uVar7 = lVar5 - param_2, uVar7 <= param_3)) {
    iVar8 = 0;
    while( true ) {
      if (uVar7 == 0) {
        return iVar8;
      }
      FUN_0011883c(param_1,param_4);
      lVar5 = thunk_FUN_001144a0(param_2,10,uVar7);
      uVar2 = uVar7;
      if (lVar5 != 0) {
        uVar2 = lVar5 - param_2;
      }
      if (uVar7 < uVar2) break;
      uVar6 = FUN_00118abc(param_2,uVar2,1,param_4);
      iVar8 = iVar8 + (int)uVar6;
      if (uVar6 < uVar2) {
        return iVar8;
      }
      iVar4 = FUN_001187f4(10,param_4);
      if (iVar4 == -1) {
        return iVar8;
      }
      uVar6 = param_2 + uVar2 + 1;
      if ((param_2 + uVar7 < uVar6) ||
         (uVar7 = uVar7 - (uVar2 + 1), bVar1 = uVar6 < param_2, param_2 = uVar6, bVar1)) break;
    }
  }
                    /* WARNING: Does not return */
  pcVar3 = (code *)SoftwareBreakpoint(0x5519,0x539a4);
  (*pcVar3)();
}

