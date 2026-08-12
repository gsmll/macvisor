
void FUN_0005ae4c(undefined8 param_1,long param_2,undefined8 param_3,int param_4)

{
  code *pcVar1;
  long lVar2;
  ulong uVar3;
  long *plVar4;
  undefined8 local_90;
  long local_88;
  undefined1 auStack_7c [20];
  long local_68;
  
  local_68 = -0x2c8502b44bfffed6;
  FUN_000618cc(param_1,auStack_7c);
  FUN_00118b28(s__xrt__Thread__s__s__p_005bc3bf);
  if ((param_4 != 0) && (*(long *)(param_2 + 0x38) != 0)) {
    uVar3 = 0;
    plVar4 = (long *)(param_2 + 0x10);
    do {
      if (((plVar4 < (long *)(param_2 + 0x10)) || ((long *)(param_2 + 0x38) < plVar4 + 1)) ||
         (plVar4 + 1 < plVar4)) {
                    /* WARNING: Does not return */
        pcVar1 = (code *)SoftwareBreakpoint(0x5519,0x5afe4);
        (*pcVar1)();
      }
      local_88 = *plVar4;
      lVar2 = FUN_0005bc48(&local_88,1);
      if (lVar2 == 0) break;
      local_90 = 0;
      FUN_00054c9c(*plVar4,&local_90);
      FUN_00118b28(s__xrt___p_acquired_at__02hhX_02hh_005bc3d6);
      uVar3 = uVar3 + 1;
      plVar4 = plVar4 + 1;
    } while (uVar3 < *(ulong *)(param_2 + 0x38));
  }
  if (local_68 == -0x2c8502b44bfffed6) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  FUN_0011d7e8();
}

