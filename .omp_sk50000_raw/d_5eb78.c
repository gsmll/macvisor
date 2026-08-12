
long FUN_0005eb78(ulong param_1,ulong param_2,ulong param_3)

{
  long lVar1;
  code *pcVar2;
  char *pcVar3;
  
  if (param_3 < 0x37) {
    if (param_2 <= param_3 * -8 + 0x1b8) {
      lVar1 = tpidrro_el0;
      FUN_00117cc4(param_1,lVar1 + param_3 * 8 + 8,param_2);
      if (param_1 <= param_1 + param_2) {
        return param_3 + (param_2 + 7 >> 3);
      }
                    /* WARNING: Does not return */
      pcVar2 = (code *)SoftwareBreakpoint(0x5519,0x5ec20);
      (*pcVar2)();
    }
    pcVar3 = s_size_0x_zx_bigger_than_available_005bcebc;
  }
  else {
    pcVar3 = s_offset_0x_zx_bigger_than_message_005bce90;
  }
                    /* WARNING: Subroutine does not return */
  FUN_0005b190(0,pcVar3);
}

