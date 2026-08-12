
void FUN_0005ed18(uint param_1,undefined8 param_2)

{
  long lVar1;
  long lVar2;
  code *pcVar3;
  
  if (3 < param_1) {
                    /* WARNING: Subroutine does not return */
    FUN_0005b190(0,s_set_src_cap_register__d_out_of_b_005bce30);
  }
  lVar2 = tpidrro_el0;
  lVar1 = lVar2 + (ulong)param_1 * 8;
  if ((undefined1 *)(lVar1 + 0x1c8U) <= (undefined1 *)(lVar2 + 0x1e0U) &&
      (undefined1 *)(lVar1 + 0x1c0U) <= (undefined1 *)(lVar1 + 0x1c8U)) {
    *(undefined1 *)(lVar1 + 0x1c0U) = (char)param_2;
    *(char *)(lVar1 + 0x1c5) = (char)((ulong)param_2 >> 0x28);
    *(char *)(lVar1 + 0x1c3) = (char)((ulong)param_2 >> 0x18);
    *(char *)(lVar1 + 0x1c2) = (char)((ulong)param_2 >> 0x10);
    *(char *)(lVar1 + 0x1c1) = (char)((ulong)param_2 >> 8);
    *(char *)(lVar1 + 0x1c4) = (char)((ulong)param_2 >> 0x20);
    *(char *)(lVar1 + 0x1c7) = (char)((ulong)param_2 >> 0x38);
    *(char *)(lVar1 + 0x1c6) = (char)((ulong)param_2 >> 0x30);
    return;
  }
                    /* WARNING: Does not return */
  pcVar3 = (code *)SoftwareBreakpoint(0x5519,0x5ed84);
  (*pcVar3)();
}

