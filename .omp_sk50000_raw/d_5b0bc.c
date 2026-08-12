
void FUN_0005b0bc(long param_1)

{
  char *pcVar1;
  
  pcVar1 = (char *)FUN_0005acac(0x6b04b8,1,3);
  if (*pcVar1 == '\x02') {
    FUN_004b63cc(param_1);
  }
  if (*(long *)(param_1 + 0x58) == 0) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  FUN_0005b190(0,s_thread_holds_locks_after_return_f_005bc367);
}

