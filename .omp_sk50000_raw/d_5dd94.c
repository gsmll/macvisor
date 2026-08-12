
void FUN_0005dd94(uint param_1,undefined8 param_2,uint param_3,ulong param_4)

{
  long *plVar1;
  code *pcVar2;
  ulong uVar3;
  long lVar4;
  undefined8 local_58;
  undefined8 uStack_50;
  long local_48;
  
  local_48 = -0x2c8502b44bfffed6;
  uVar3 = FUN_00060524();
  if ((int)param_3 < 5) {
    if (param_3 == 3) goto LAB_0005de28;
    if (param_3 != 4) {
LAB_0005de10:
                    /* WARNING: Subroutine does not return */
      FUN_0005b190(0,s_invalid_sync_wake_selector__u_005bc90e);
    }
    if (param_4 != 0) {
      param_3 = 4;
      uVar3 = param_4;
      goto LAB_0005de28;
    }
  }
  else if (param_3 != 5) {
    if (param_3 != 6) goto LAB_0005de10;
    goto LAB_0005de28;
  }
  param_3 = 5;
LAB_0005de28:
  lVar4 = FUN_0005acac(0x6b2698,1,4);
  plVar1 = (long *)(lVar4 + (ulong)param_1 * 8);
  *plVar1 = *plVar1 + 1;
  LORelease();
  uStack_50 = *(undefined8 *)(lVar4 + (ulong)param_1 * 8);
  local_58 = param_2;
  if (uVar3 + 0x178 < uVar3) {
                    /* WARNING: Does not return */
    pcVar2 = (code *)SoftwareBreakpoint(0x5519,0x5deb0);
    (*pcVar2)();
  }
  lVar4 = FUN_0005d64c(uVar3,(param_3 | param_1 << 0xc) & 0xffff,&local_58,0);
  if (local_48 == -0x2c8502b44bfffed6) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  FUN_0011d7e8(lVar4 != 5);
}

