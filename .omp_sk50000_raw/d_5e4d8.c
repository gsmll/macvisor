
void FUN_0005e4d8(long param_1,undefined8 param_2,undefined8 param_3,ulong param_4)

{
  ulong uVar1;
  code *pcVar2;
  bool bVar3;
  ulong uVar4;
  long lVar5;
  undefined8 local_50;
  undefined8 uStack_48;
  
  local_50 = param_2;
  uStack_48 = param_3;
  FUN_0005e8a4(&local_50,0,s____s___s_at_PC__0x_012zx__LR__0x_005bcb91);
  if ((param_4 & 1) == 0) {
    FUN_0005e8a4(&local_50,1,s_Address_space_ID__0x_016llx_005bcbb9);
    FUN_0005e8a4(&local_50,1,s_Component_ID__0x_016llx_005bcbd6);
    FUN_0005e8a4(&local_50,1,s_Component_selector__0x_016llx_005bcbef);
    FUN_0005e958(*(undefined4 *)(param_1 + 0xd8));
    FUN_0005e958(*(undefined4 *)(param_1 + 0xe0));
    FUN_0005e958(*(undefined4 *)(param_1 + 0xdc));
    FUN_0005e958(*(undefined4 *)(param_1 + 0xe4));
    FUN_0005e8a4(&local_50,1,s_space_endpoint_component_name_ID_005bcc0e);
    FUN_0005e8a4(&local_50,1,s_Thread_stack_range__0x_012zx__0x_005bcc3d);
    FUN_0005e8a4(&local_50,1,s_Thread_call_stack__0x_012zx__0x__005bcc65);
    FUN_0005e8a4(&local_50,1,s_Thread_address__0x_012zx_005bcc8c);
    FUN_0005e8a4(&local_50,1,s_Thread_TSS_base__0x_012zx_005bcca6);
    FUN_0005e8a4(&local_50,1,s_Thread_IPC_buffer__0x_012zx_005bccc1);
    FUN_0005e8a4(&local_50,1,s_Thread_SCID__0x_016llx_005bccde);
    FUN_0005e8a4(&local_50,1,s_Thread_ECID__0x_016llx_005bccf6);
    FUN_0005e8a4(&local_50,1,s_Thread_numeric_ID__0x_016llx_005bcd0e);
    FUN_0005e8a4(&local_50,1,s_Thread_EPID__0x_016llx_005bcd2c);
    FUN_0005e8a4(&local_50,1,s_Panic_backtrace__005bcd44);
    uVar4 = param_1 + 0x160;
    lVar5 = -0xc;
    do {
      if (param_1 + 0x1b8U < uVar4) {
LAB_0005e8a0:
                    /* WARNING: Does not return */
        pcVar2 = (code *)SoftwareBreakpoint(0x5519,0x5e8a4);
        (*pcVar2)();
      }
      uVar1 = param_1 + 0x158U + (*(ulong *)(uVar4 - 8) >> 0x30) * 0x10;
      if (2 < *(ulong *)(uVar4 - 8) >> 0x31 || uVar1 == 0) {
        return;
      }
      if ((((((uVar1 < param_1 + 0x158U || param_1 + 0x1b8U < uVar1 + 0x10) || uVar1 + 0x10 < uVar1)
            || (uVar1 + 1 < uVar1)) || (uVar1 + 2 < uVar1)) ||
          (((uVar1 + 3 < uVar1 || (uVar1 + 4 < uVar1)) ||
           ((uVar1 + 5 < uVar1 || ((uVar1 + 6 < uVar1 || (uVar1 + 7 < uVar1)))))))) ||
         ((uVar1 + 8 < uVar1 ||
          (((((uVar1 + 9 < uVar1 || (uVar1 + 10 < uVar1)) || (uVar1 + 0xb < uVar1)) ||
            ((uVar1 + 0xc < uVar1 || (uVar1 + 0xd < uVar1)))) ||
           ((uVar1 + 0xe < uVar1 || (uVar1 + 0xf < uVar1)))))))) goto LAB_0005e8a0;
      FUN_0005e8a4(&local_50,1,s_____02zd___02hhX_02hhX_02hhX_02h_005bcd56);
      uVar4 = uVar4 + 8;
      bVar3 = lVar5 != -1;
      lVar5 = lVar5 + 1;
    } while (bVar3);
  }
  return;
}

