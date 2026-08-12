
void FUN_00057644(long param_1)

{
  undefined8 *puVar1;
  undefined8 uVar2;
  
  puVar1 = (undefined8 *)tpidrro_el0;
  uVar2 = *puVar1;
  do {
    CallSupervisor(0);
    *puVar1 = uVar2;
  } while (param_1 == 1);
  return;
}

