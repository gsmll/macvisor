
void FUN_0005fccc(long param_1)

{
  char cVar1;
  undefined8 local_18;
  
  local_18 = 0x20000;
  cVar1 = (**(code **)(*(long *)(param_1 + 0x38) + 0x18))(*(undefined8 *)(param_1 + 0x30),&local_18)
  ;
  if (cVar1 == '\0') {
    return;
  }
                    /* WARNING: Subroutine does not return */
  FUN_0005b190(0,s_failed_to_populate_stack_005bd169);
}

