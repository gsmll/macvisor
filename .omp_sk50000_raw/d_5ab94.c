
undefined4 FUN_0005ab94(ulong param_1,uint param_2)

{
  char *pcVar1;
  code *pcVar2;
  long lVar3;
  undefined8 uVar4;
  undefined4 uVar5;
  ulong local_28;
  
  local_28 = 0;
  lVar3 = FUN_0006562c(s_xrt__runflags_005bc12a,&local_28);
  if (lVar3 == 0) {
    uVar5 = 0;
  }
  else {
    if (local_28 < (param_1 & 0xffffffff)) {
      uVar4 = FUN_00060524();
                    /* WARNING: Subroutine does not return */
      FUN_0005b190(uVar4,s_xrt_runflag_metadata_not_long_en_005bc138);
    }
    pcVar1 = (char *)(lVar3 + (param_1 & 0xffffffff));
    if ((char *)(lVar3 + local_28) <= pcVar1) {
                    /* WARNING: Does not return */
      pcVar2 = (code *)SoftwareBreakpoint(0x5519,0x5ac1c);
      (*pcVar2)();
    }
    uVar5 = 1;
    if (((uint)(int)*pcVar1 >> (ulong)(param_2 & 0x1f) & 1) == 0) {
      uVar5 = 2;
    }
  }
  return uVar5;
}

