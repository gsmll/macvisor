
void FUN_000554bc(undefined8 param_1)

{
  long lVar1;
  
  lVar1 = FUN_000549ac();
                    /* WARNING: Could not recover jumptable at 0x000554ec. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(lVar1 + 0x70))(param_1);
  return;
}

