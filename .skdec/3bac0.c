
void FUN_0003bac0(undefined8 *param_1)

{
  char cVar1;
  code *pcVar2;
  ulong uVar3;
  undefined8 uVar4;
  
  uVar4 = *param_1;
  cVar1 = *(char *)(param_1 + 6);
  while (cVar1 != '\0') {
    uVar3 = FUN_0003c21c(param_1);
    if (uVar3 + 0xb0 < uVar3) goto LAB_0003bbec;
    *(undefined8 *)(uVar3 + 0x50) = 0;
    FUN_00033148();
    cVar1 = *(char *)(param_1 + 6);
  }
  if (param_1[1] != 0) {
                    /* WARNING: Subroutine does not return */
    FUN_004afae4(s__VAS_abort_in_function__s_at_lin_005b34cf);
  }
  while( true ) {
    if (*(char *)((long)param_1 + 0x31) == '\0') {
      if (param_1[2] != 0) {
                    /* WARNING: Subroutine does not return */
        FUN_004afae4(s__VAS_abort_in_function__s_at_lin_005b353c);
      }
      while (*(char *)((long)param_1 + 0x32) != '\0') {
        FUN_0003b340(param_1);
        FUN_000335e0();
      }
      if (param_1[3] != 0) {
                    /* WARNING: Subroutine does not return */
        FUN_004afae4(s__VAS_abort_in_function__s_at_lin_005b3598);
      }
      while (*(char *)((long)param_1 + 0x33) != '\0') {
        FUN_0003b478(param_1);
        FUN_0003353c();
      }
      if (param_1[4] != 0) {
                    /* WARNING: Subroutine does not return */
        FUN_004afae4(s__VAS_abort_in_function__s_at_lin_005b35f3);
      }
      while (param_1[7] != 0) {
        FUN_0003b5b0(param_1);
        FUN_00033498();
      }
      if (param_1[5] != 0) {
                    /* WARNING: Subroutine does not return */
        FUN_004afae4(s__VAS_abort_in_function__s_at_lin_005b3655);
      }
      FUN_001143a0(param_1,0xffffffc0,8);
      return;
    }
    uVar3 = FUN_0003e640(param_1);
    if (uVar3 + 0x20 < uVar3) break;
    FUN_00031594(uVar4,uVar3);
  }
LAB_0003bbec:
                    /* WARNING: Does not return */
  pcVar2 = (code *)SoftwareBreakpoint(0x5519,0x3bbf0);
  (*pcVar2)();
}

