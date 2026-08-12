
void FUN_0005db7c(long param_1)

{
  int iVar1;
  long lVar2;
  undefined1 local_39;
  undefined8 local_38;
  undefined8 uStack_30;
  long local_28;
  
  local_28 = -0x2c8502b44bfffed6;
  if ((*(byte *)(param_1 + 0x48) >> 3 & 1) != 0) {
    lVar2 = FUN_00060524();
    local_39 = 0;
    if (param_1 == lVar2) {
      local_38 = 0;
      uStack_30 = 0;
      FUN_0005d64c(param_1,0xd,&local_38,1);
      *(ulong *)(param_1 + 0x48) = *(ulong *)(param_1 + 0x48) & 0xfffffffffffffff7;
    }
    else {
      do {
        iVar1 = FUN_00060570(&local_39);
      } while (iVar1 == 0);
      local_38 = 0;
      uStack_30 = 0;
      FUN_0005d64c(param_1,0xc,&local_38,1);
      *(ulong *)(param_1 + 0x48) = *(ulong *)(param_1 + 0x48) & 0xfffffffffffffff7;
      FUN_000605f8(&local_39);
    }
  }
  if (local_28 == -0x2c8502b44bfffed6) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  FUN_0011d7e8();
}

