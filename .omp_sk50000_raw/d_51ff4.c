
void FUN_00051ff4(long param_1,ulong *param_2,ulong *param_3,long *param_4)

{
  ulong uVar1;
  ulong uVar2;
  uint uVar3;
  code *pcVar4;
  long lVar5;
  long lVar6;
  ulong uVar7;
  long lVar8;
  int *piVar9;
  
  lVar5 = FUN_00051e5c(param_1,s___TEXT_005bb905);
  uVar7 = (ulong)*(uint *)(param_1 + 0x10);
  if (*(uint *)(param_1 + 0x10) != 0) {
    lVar5 = *(long *)(lVar5 + 0x18);
    piVar9 = (int *)(param_1 + 0x20);
    do {
      if (*piVar9 == 2) {
        lVar6 = FUN_00051e5c(param_1,s___LINKEDIT_005bb90c);
        if ((lVar6 == 0) || (uVar7 = (ulong)(uint)piVar9[3], piVar9[3] == 0)) goto LAB_00052068;
        lVar8 = *(long *)(lVar6 + 0x28);
        lVar5 = *(long *)(lVar6 + 0x18) + (param_1 - lVar5);
        uVar1 = (lVar5 - lVar8) + (ulong)(uint)piVar9[2];
        uVar2 = uVar1 + uVar7 * 0x10;
        if ((uVar2 < uVar1) || ((ulong)((long)(uVar2 - uVar1) >> 4) < uVar7)) {
                    /* WARNING: Does not return */
          pcVar4 = (code *)SoftwareBreakpoint(0x5519,0x520f0);
          (*pcVar4)();
        }
        uVar3 = piVar9[4];
        *param_2 = uVar7;
        *param_3 = uVar1;
        lVar5 = ((ulong)uVar3 - lVar8) + lVar5;
        goto LAB_00052074;
      }
      piVar9 = (int *)((long)piVar9 + (ulong)(uint)piVar9[1]);
      uVar7 = uVar7 - 1;
    } while (uVar7 != 0);
  }
  FUN_00051e5c(param_1,s___LINKEDIT_005bb90c);
LAB_00052068:
  lVar5 = 0;
  *param_2 = 0;
  *param_3 = 0;
LAB_00052074:
  *param_4 = lVar5;
  return;
}

