
long FUN_0005fdac(long param_1,undefined8 param_2)

{
  long lVar1;
  char cVar2;
  ulong extraout_x18;
  ulong extraout_x18_00;
  ulong uVar3;
  undefined1 local_59;
  undefined1 auStack_58 [32];
  long local_38;
  
  local_38 = -0x2c8502b44bfffed6;
  local_59 = 0;
  lVar1 = FUN_00060570(&local_59);
  if ((int)lVar1 == 0) {
LAB_0005fe0c:
    if (local_38 == -0x2c8502b44bfffed6) {
      return lVar1;
    }
                    /* WARNING: Subroutine does not return */
    FUN_0011d7e8();
  }
  CallSupervisor(2);
  if ((*(ulong *)(param_1 + 0x28) & 0xff) == 0) {
    FUN_000605f8(&local_59,param_2);
    goto LAB_0005fe0c;
  }
  FUN_004b6f70(*(ulong *)(param_1 + 0x28),auStack_58);
  lVar1 = FUN_00060524();
  cVar2 = *(char *)(lVar1 + 0x69);
  uVar3 = extraout_x18;
  if (cVar2 != '\0') {
    if (cVar2 != -1) goto LAB_0005fe84;
    lVar1 = FUN_004b6fc0();
    uVar3 = extraout_x18_00;
  }
  if ((uVar3 & 1) != 0) {
                    /* WARNING: Subroutine does not return */
    FUN_004afae4(s_already_enabled___lx_005bd1ee);
  }
  cVar2 = *(char *)(lVar1 + 0x69);
LAB_0005fe84:
  *(char *)(lVar1 + 0x69) = cVar2 + '\x01';
  return lVar1;
}

