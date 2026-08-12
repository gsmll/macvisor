
void FUN_000555f8(undefined8 param_1)

{
  long lVar1;
  
  lVar1 = FUN_000549ac();
                    /* WARNING: Could not recover jumptable at 0x00055628. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(lVar1 + 0x98))(param_1);
  return;
}

