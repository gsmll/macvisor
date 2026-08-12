
void FUN_0005ec20(uint param_1,undefined8 param_2)

{
  long lVar1;
  
  if (param_1 < 0x37) {
    lVar1 = tpidrro_el0;
    lVar1 = lVar1 + (ulong)param_1 * 8;
    *(char *)(lVar1 + 8) = (char)param_2;
    *(char *)(lVar1 + 0xd) = (char)((ulong)param_2 >> 0x28);
    *(char *)(lVar1 + 0xb) = (char)((ulong)param_2 >> 0x18);
    *(char *)(lVar1 + 10) = (char)((ulong)param_2 >> 0x10);
    *(char *)(lVar1 + 9) = (char)((ulong)param_2 >> 8);
    *(char *)(lVar1 + 0xc) = (char)((ulong)param_2 >> 0x20);
    *(char *)(lVar1 + 0xf) = (char)((ulong)param_2 >> 0x38);
    *(char *)(lVar1 + 0xe) = (char)((ulong)param_2 >> 0x30);
    return;
  }
                    /* WARNING: Subroutine does not return */
  FUN_0005b190(0,s_set_message_register__d_out_of_b_005bcdd0);
}

