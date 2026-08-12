
void FUN_000556e4(undefined8 param_1)

{
  long lVar1;
  
  lVar1 = FUN_000549ac();
                    /* WARNING: Could not recover jumptable at 0x00055714. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(lVar1 + 0xd8))(param_1);
  return;
}

