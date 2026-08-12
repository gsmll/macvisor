
void FUN_000553e4(undefined8 param_1,undefined8 param_2)

{
  long lVar1;
  
  lVar1 = FUN_000549ac();
                    /* WARNING: Could not recover jumptable at 0x0005541c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(lVar1 + 0x50))(param_1,param_2);
  return;
}

