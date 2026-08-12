
undefined8
FUN_0003b820(undefined8 *param_1,undefined8 param_2,ulong param_3,ulong param_4,ulong param_5,
            ulong param_6)

{
  byte bVar1;
  long lVar2;
  undefined8 *puVar3;
  ulong uVar4;
  undefined1 in_wzr;
  
  if (3 < param_3) {
                    /* WARNING: Subroutine does not return */
    FUN_004afae4(s__VAS_abort_in_function__s_at_lin_005b27c9);
  }
  if (3 < param_4) {
                    /* WARNING: Subroutine does not return */
    FUN_004afae4(s__VAS_abort_in_function__s_at_lin_005b2844);
  }
  if (3 < param_5) {
                    /* WARNING: Subroutine does not return */
    FUN_004afae4(s__VAS_abort_in_function__s_at_lin_005b28a3);
  }
  *param_1 = param_2;
  param_1[6] = 0;
  param_1[5] = 0;
  param_1[2] = 0;
  param_1[1] = 0;
  param_1[4] = 0;
  param_1[3] = 0;
  param_1[7] = 0;
  *(ushort *)(param_1 + 8) =
       (ushort)param_3 | (ushort)((int)param_4 << 4) | (ushort)((int)param_5 << 8) |
       (ushort)((int)param_6 << 0xc);
  *(undefined4 *)((long)param_1 + 0x42) = 0;
  *(undefined2 *)((long)param_1 + 0x46) = 0;
  while (*(byte *)(param_1 + 6) < param_3) {
    lVar2 = FUN_00032e44();
    if (lVar2 == 0) goto LAB_0003b968;
    FUN_0003ba58(param_1,lVar2);
  }
  uVar4 = (ulong)*(byte *)((long)param_1 + 0x31);
  while (uVar4 < param_4) {
    puVar3 = (undefined8 *)FUN_00030cc8(param_2);
    if (puVar3 == (undefined8 *)0x0) goto LAB_0003b968;
    *(undefined1 *)(puVar3 + 3) = in_wzr;
    bVar1 = *(byte *)((long)param_1 + 0x31);
    if (2 < bVar1) {
                    /* WARNING: Subroutine does not return */
      FUN_004afae4(s__VAS_abort_in_function__s_at_lin_005b346f);
    }
    *puVar3 = param_1[2];
    param_1[2] = puVar3;
    uVar4 = (ulong)bVar1 + 1;
    *(char *)((long)param_1 + 0x31) = (char)uVar4;
  }
  while (*(byte *)((long)param_1 + 0x32) < param_5) {
    lVar2 = FUN_00033594();
    if (lVar2 == 0) goto LAB_0003b968;
    FUN_0003b410(param_1,lVar2);
  }
  if (param_6 != 0 || param_5 != 0) {
    lVar2 = FUN_000334f0();
    if (lVar2 == 0) goto LAB_0003b968;
    FUN_0003b548(param_1,lVar2);
  }
  while( true ) {
    if (param_6 <= (ulong)param_1[7]) {
      return 1;
    }
    lVar2 = FUN_0003344c();
    if (lVar2 == 0) break;
    FUN_0003b648(param_1,lVar2);
  }
LAB_0003b968:
  FUN_0003bac0(param_1);
  return 0;
}

