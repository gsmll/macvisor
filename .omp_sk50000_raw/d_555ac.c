
void FUN_000555ac(undefined8 param_1,undefined8 param_2,undefined8 param_3)

{
  long lVar1;
  
  lVar1 = FUN_000549ac();
                    /* WARNING: Could not recover jumptable at 0x000555f4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(lVar1 + 0x90))(param_1,param_2,param_3);
  return;
}

