
void FUN_00034a5c(void)

{
  long lVar1;
  
  lVar1 = FUN_0005acac(0x6af188,4,8);
  if (*(uint *)(lVar1 + 0x48) < 0xffff) {
    *(uint *)(lVar1 + 0x48) = *(uint *)(lVar1 + 0x48) + 1;
    FUN_000348d0();
    return;
  }
                    /* WARNING: Subroutine does not return */
  FUN_004afae4(s__VAS_abort_in_function__s_at_lin_005b11ec);
}

