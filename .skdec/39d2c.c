
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined1  [16] FUN_00039d2c(long param_1,undefined8 *param_2)

{
  _DAT_006ad39c = _DAT_006ad39c + 1;
  if (param_2[10] != param_1) {
                    /* WARNING: Subroutine does not return */
    FUN_004afae4(s__VAS_abort_in_function__s_at_lin_005b5f52);
  }
  if (*(char *)((long)param_2 + 0xa1) == '\x01') {
    FUN_004b2f58();
  }
  else {
    FUN_00039e34(param_2[0xb]);
    FUN_00039e34(param_2[0xe]);
    FUN_004b23d8(param_2[0x12]);
    FUN_004b23d8(param_2[0x13]);
    if (*(char *)(param_2 + 8) != '\x01') {
      thunk_FUN_000539fc(param_2 + 6);
      param_2[0x15] = 0;
      param_2[0x14] = 0;
      param_2[0x17] = 0;
      param_2[0x16] = 0;
      param_2[0x11] = 0;
      param_2[0x10] = 0;
      param_2[0x13] = 0;
      param_2[0x12] = 0;
      param_2[0xd] = 0;
      param_2[0xc] = 0;
      param_2[0xf] = 0;
      param_2[0xe] = 0;
      param_2[9] = 0;
      param_2[8] = 0;
      param_2[0xb] = 0;
      param_2[10] = 0;
      param_2[5] = 0;
      param_2[4] = 0;
      param_2[7] = 0;
      param_2[6] = 0;
      param_2[1] = 0;
      *param_2 = 0;
      param_2[3] = 0;
      param_2[2] = 0;
      FUN_00033684(param_2);
      return ZEXT816(0);
    }
  }
                    /* WARNING: Subroutine does not return */
  FUN_004afae4(s__VAS_abort_in_function__s_at_lin_005b4c86);
}

