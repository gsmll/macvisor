
undefined8 FUN_00055a24(uint param_1)

{
  undefined8 *puVar1;
  code *pcVar2;
  long lVar3;
  undefined8 uVar4;
  undefined8 *puVar5;
  
  if (((int)param_1 < 0) || (lVar3 = FUN_000549ac(), *(byte *)(lVar3 + 0x178) <= param_1)) {
    uVar4 = 0;
  }
  else {
    lVar3 = FUN_000549ac();
    puVar5 = *(undefined8 **)(lVar3 + 0x188);
    puVar1 = puVar5 + param_1;
    if ((puVar1 < puVar5 || puVar5 + *(byte *)(lVar3 + 0x178) < puVar1 + 1) || puVar1 + 1 < puVar1)
    {
                    /* WARNING: Does not return */
      pcVar2 = (code *)SoftwareBreakpoint(0x5519,0x55a90);
      (*pcVar2)();
    }
    uVar4 = *puVar1;
  }
  return uVar4;
}

