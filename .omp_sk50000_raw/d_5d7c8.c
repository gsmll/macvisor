
void FUN_0005d7c8(long *param_1)

{
  code *pcVar1;
  char cVar2;
  long lVar3;
  undefined1 auVar4 [16];
  
  lVar3 = FUN_00034f70();
  if (param_1 + 1 < param_1) {
                    /* WARNING: Does not return */
    pcVar1 = (code *)SoftwareBreakpoint(0x5519,0x5d82c);
    (*pcVar1)();
  }
  *param_1 = lVar3;
  if (lVar3 != 0) {
    auVar4 = FUN_00034a2c();
    cVar2 = (**(code **)(auVar4._8_8_ + 0x48))(auVar4._0_8_,*param_1);
    if (cVar2 == '\0') {
      return;
    }
                    /* WARNING: Subroutine does not return */
    FUN_0005b190(0,s_xrt__sync_space_init____vas_root_005bcb5b);
  }
                    /* WARNING: Subroutine does not return */
  FUN_0005b190(0,s__space_top_init____vas_slot_allo_005bcb30);
}

