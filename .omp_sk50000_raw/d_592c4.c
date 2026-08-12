
void FUN_000592c4(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)tpidrro_el0;
  *puVar1 = param_2;
  puVar1[1] = param_3;
  puVar1[2] = param_4;
  CallSupervisor(0);
  *puVar1 = param_2;
  return;
}

