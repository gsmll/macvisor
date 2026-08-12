
void FUN_0005edac(uint param_1,undefined8 param_2)

{
  long lVar1;
  long lVar2;
  code *pcVar3;
  
  if (3 < param_1) {
                    /* WARNING: Subroutine does not return */
    FUN_0005b190(0,s_set_dst_cap_register__d_out_of_b_005bce60);
  }
  lVar2 = tpidrro_el0;
  lVar1 = lVar2 + (ulong)param_1 * 8;
  if ((undefined1 *)(lVar1 + 0x1e8U) <= (undefined1 *)(lVar2 + 0x200U) &&
      (undefined1 *)(lVar1 + 0x1e0U) <= (undefined1 *)(lVar1 + 0x1e8U)) {
    *(undefined1 *)(lVar1 + 0x1e0U) = (char)param_2;
    *(char *)(lVar1 + 0x1e5) = (char)((ulong)param_2 >> 0x28);
    *(char *)(lVar1 + 0x1e3) = (char)((ulong)param_2 >> 0x18);
    *(char *)(lVar1 + 0x1e2) = (char)((ulong)param_2 >> 0x10);
    *(char *)(lVar1 + 0x1e1) = (char)((ulong)param_2 >> 8);
    *(char *)(lVar1 + 0x1e4) = (char)((ulong)param_2 >> 0x20);
    *(char *)(lVar1 + 0x1e7) = (char)((ulong)param_2 >> 0x38);
    *(char *)(lVar1 + 0x1e6) = (char)((ulong)param_2 >> 0x30);
    return;
  }
                    /* WARNING: Does not return */
  pcVar3 = (code *)SoftwareBreakpoint(0x5519,0x5ee18);
  (*pcVar3)();
}

