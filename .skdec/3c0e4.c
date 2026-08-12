
void FUN_0003c0e4(long param_1,ulong param_2,ulong param_3)

{
  long lVar1;
  code *pcVar2;
  ulong uVar3;
  undefined8 *puVar4;
  undefined8 local_80;
  undefined8 uStack_78;
  undefined8 uStack_70;
  undefined8 uStack_68;
  undefined8 local_60;
  undefined8 uStack_58;
  undefined8 uStack_50;
  undefined8 uStack_48;
  undefined8 local_40;
  
  local_40 = 0;
  uStack_58 = 0;
  local_60 = 0;
  uStack_48 = 0;
  uStack_50 = 0;
  uStack_78 = 0;
  local_80 = 0;
  uStack_68 = 0;
  uStack_70 = 0;
  uVar3 = FUN_0003b820(&local_80,param_1,1,0,0,0);
  if ((uVar3 & 1) == 0) {
                    /* WARNING: Subroutine does not return */
    FUN_004afae4(s__VAS_abort_in_function__s_at_lin_005b2bbb);
  }
  FUN_0003bca0(&local_80,param_1,0,0);
  puVar4 = (undefined8 *)FUN_0003c21c(&local_80);
  lVar1 = param_3 - param_2;
  if (param_2 <= param_3 && lVar1 != 0) {
    *(ulong *)(param_1 + 0x28) = param_2;
    *(ulong *)(param_1 + 0x30) = param_3;
    if (puVar4 <= puVar4 + 0x16) {
      *puVar4 = 0;
      puVar4[1] = param_2;
      puVar4[2] = lVar1;
      puVar4[4] = 0;
      puVar4[3] = 0;
      puVar4[6] = 0;
      puVar4[5] = 0;
      puVar4[8] = 0;
      puVar4[7] = 0;
      puVar4[9] = 0;
      puVar4[10] = param_1;
      puVar4[0xb] = 0;
      puVar4[0xc] = 0;
      puVar4[0xd] = lVar1;
      puVar4[0xf] = 0;
      puVar4[0xe] = 0;
      puVar4[0x11] = 0;
      puVar4[0x10] = 0;
      puVar4[0x13] = 0;
      puVar4[0x12] = 0;
      puVar4[0x15] = 0;
      puVar4[0x14] = 0;
      FUN_0003c2ec(&local_80);
      FUN_0003bfb8(&local_80,param_1);
      return;
    }
                    /* WARNING: Does not return */
    pcVar2 = (code *)SoftwareBreakpoint(0x5519,0x3c1c8);
    (*pcVar2)();
  }
                    /* WARNING: Subroutine does not return */
  FUN_004afae4(s__VAS_abort_in_function__s_at_lin_005b2c70);
}

