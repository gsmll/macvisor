
void FUN_000553b0(undefined8 param_1)

{
  long lVar1;
  
  lVar1 = FUN_000549ac();
                    /* WARNING: Could not recover jumptable at 0x000553e0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(lVar1 + 0x48))(param_1);
  return;
}

