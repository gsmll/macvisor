
void FUN_00056064(long param_1,undefined8 param_2)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)tpidrro_el0;
  *puVar1 = param_2;
  do {
    CallSupervisor(0);
    *puVar1 = param_2;
  } while (param_1 == 1);
  return;
}

