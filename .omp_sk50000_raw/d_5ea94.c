
long FUN_0005ea94(undefined8 param_1,ulong param_2,ulong param_3,uint param_4)

{
  undefined1 *puVar1;
  undefined1 *puVar2;
  code *pcVar3;
  char *pcVar4;
  ulong uVar5;
  
  if (param_3 < 0x37) {
    uVar5 = param_3 * -8 + 0x1b8;
    if (param_2 + param_4 <= uVar5) {
      puVar2 = (undefined1 *)tpidrro_el0;
      if (param_2 <= uVar5) {
        puVar1 = puVar2 + param_3 * 8 + 8;
        FUN_00117cc4(puVar1,param_1,param_2);
        if (puVar1 <= puVar1 + param_2) {
          if (param_4 != 0) {
            puVar1 = puVar1 + param_2;
            if ((puVar2 + 0x1c0 <= puVar1) || (puVar1 < puVar2)) goto LAB_0005eae4;
            *puVar1 = 0;
          }
          return param_3 + (param_2 + param_4 + 7 >> 3);
        }
      }
LAB_0005eae4:
                    /* WARNING: Does not return */
      pcVar3 = (code *)SoftwareBreakpoint(0x5519,0x5eae8);
      (*pcVar3)();
    }
    pcVar4 = s_size_0x_zx_bigger_than_available_005bcebc;
  }
  else {
    pcVar4 = s_offset_0x_zx_bigger_than_message_005bce90;
  }
                    /* WARNING: Subroutine does not return */
  FUN_0005b190(0,pcVar4);
}

