
undefined8 FUN_000534ec(long param_1,undefined8 *param_2,undefined1 *param_3)

{
  undefined8 uVar1;
  code *pcVar2;
  long lVar3;
  undefined8 *puVar4;
  
  lVar3 = FUN_0005acac(0x6af8d8,2,5);
  puVar4 = (undefined8 *)(lVar3 + 0x2c8U) + param_1 * 3;
  if (((undefined8 *)(lVar3 + 0x2c8U) <= puVar4 && puVar4 + 3 <= (undefined8 *)(lVar3 + 0x628U)) &&
      puVar4 <= puVar4 + 3) {
    uVar1 = puVar4[1];
    *param_2 = *puVar4;
    *param_3 = *(undefined1 *)(puVar4 + 2);
    return uVar1;
  }
                    /* WARNING: Does not return */
  pcVar2 = (code *)SoftwareBreakpoint(0x5519,0x53568);
  (*pcVar2)();
}

