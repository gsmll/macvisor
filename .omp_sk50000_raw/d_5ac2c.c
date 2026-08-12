
ulong FUN_0005ac2c(void)

{
  int iVar1;
  ulong uVar2;
  byte *pbVar3;
  long lVar4;
  undefined8 local_18;
  
  uVar2 = FUN_00055b60();
  if ((int)uVar2 != 0) {
    pbVar3 = (byte *)FUN_00054610();
    if ((*pbVar3 & 1) == 0) {
      local_18 = 0;
      lVar4 = FUN_0006562c(s_sec_transition_005bc15d,&local_18);
      if ((lVar4 == 0) || (iVar1 = thunk_FUN_00114e50(lVar4,&DAT_005cf0f4,local_18), iVar1 == 0)) {
        iVar1 = FUN_0005ab94(2,1);
        uVar2 = (ulong)(iVar1 == 1);
      }
      else {
        uVar2 = 1;
      }
    }
    else {
      uVar2 = 0;
    }
  }
  return uVar2;
}

