
void FUN_00054b44(undefined8 *param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                 undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                 undefined8 param_9)

{
  code *pcVar1;
  undefined8 *puVar2;
  
  *param_1 = 0;
  param_1[1] = param_9;
  param_1[3] = 0;
  param_1[5] = param_4;
  param_1[6] = param_5;
  param_1[7] = param_3;
  param_1[8] = 0;
  param_1[9] = param_8;
  param_1[10] = param_7;
  param_1[0xb] = 0;
  param_1[0xc] = 0;
  param_1[0xd] = 0;
  param_1[0xe] = 0;
  puVar2 = param_1 + 2;
  *puVar2 = 0;
  param_1[4] = param_6;
  FUN_00117cc4(puVar2,param_2,0x10);
  if (puVar2 <= param_1 + 4) {
    return;
  }
                    /* WARNING: Does not return */
  pcVar1 = (code *)SoftwareBreakpoint(0x5519,0x54ba8);
  (*pcVar1)();
}

