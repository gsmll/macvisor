
void FUN_0005d64c(long param_1,undefined2 param_2,undefined8 *param_3,ulong param_4)

{
  bool bVar1;
  long lVar2;
  ulong uVar3;
  undefined8 uVar4;
  char *pcVar5;
  char local_71;
  undefined2 local_70;
  undefined2 local_6e;
  undefined2 local_6c;
  undefined2 local_6a;
  undefined8 local_68;
  undefined8 uStack_60;
  undefined8 local_58;
  ulong local_50;
  undefined1 auStack_48 [32];
  long local_28;
  
  local_28 = -0x2c8502b44bfffed6;
  local_6e = 0;
  local_6c = 0;
  local_6a = 0;
  uStack_60 = param_3[1];
  local_68 = *param_3;
  local_58 = 0;
  local_50 = 0;
  local_70 = param_2;
  if ((param_4 & 1) == 0) {
    bVar1 = false;
    pcVar5 = (char *)0x0;
  }
  else {
    lVar2 = FUN_00060524();
    pcVar5 = &local_71;
    bVar1 = param_1 != lVar2;
    if (!bVar1) {
      pcVar5 = (char *)0x0;
    }
  }
  local_50 = (ulong)bVar1;
  local_71 = '\0';
  uVar3 = FUN_0005dab8(FUN_0005dfa8,param_1,pcVar5,&local_70);
  if ((uVar3 & 0xff) == 0) {
    uVar4 = 5;
    if (local_71 == '\0') {
      uVar4 = local_58;
    }
    if (local_28 == -0x2c8502b44bfffed6) {
      return;
    }
  }
  else {
    uVar4 = FUN_004b6938(uVar3,auStack_48);
  }
                    /* WARNING: Subroutine does not return */
  FUN_0011d7e8(uVar4);
}

