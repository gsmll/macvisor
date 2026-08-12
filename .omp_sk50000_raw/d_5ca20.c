
undefined8 FUN_0005ca20(uint param_1)

{
  int iVar1;
  code *pcVar2;
  long lVar3;
  long lVar4;
  int *piVar5;
  undefined8 *puVar6;
  undefined8 *puVar7;
  undefined8 uVar8;
  
  lVar4 = (ulong)param_1 * 0x50;
  if ((lVar4 + 0x64db60U < 0x64db60 || 0x64dca0 < lVar4 + 0x64dbb0U) ||
      lVar4 + 0x64dbb0U < lVar4 + 0x64db60U) goto LAB_0005cb14;
  puVar6 = *(undefined8 **)(lVar4 + 0x64dba0);
  if (puVar6 == (undefined8 *)0x0) {
    lVar3 = FUN_0005ad24();
    if (lVar3 == 0) {
LAB_0005caa8:
      puVar6 = *(undefined8 **)(lVar4 + 0x64dba0);
      if (puVar6 == (undefined8 *)0x0) {
        return 0;
      }
    }
    else {
      if (param_1 == 2) {
        if ((*(byte *)(lVar3 + 8) >> 1 & 1) == 0) goto LAB_0005caa8;
        lVar3 = FUN_0005ace4();
        puVar6 = (undefined8 *)(lVar3 + 0x20);
        puVar7 = (undefined8 *)(lVar3 + 0x28);
      }
      else {
        if ((param_1 != 1) || ((*(byte *)(lVar3 + 8) & 1) == 0)) goto LAB_0005caa8;
        lVar3 = FUN_0005ace4();
        puVar6 = (undefined8 *)(lVar3 + 0x18);
        puVar7 = (undefined8 *)(lVar3 + 0x20);
      }
      if (puVar7 < puVar6) goto LAB_0005cb14;
      *(undefined8 **)(lVar4 + 0x64dba0) = puVar6;
      *(undefined1 *)(lVar4 + 0x64dba8) = 1;
    }
  }
  uVar8 = *puVar6;
  if (*(char *)(lVar4 + 0x64dba8) == '\x01') {
    lVar4 = FUN_0005ace4();
    iVar1 = *(int *)(lVar4 + 4);
    piVar5 = (int *)FUN_0005ace4();
    if (iVar1 != *piVar5) {
      FUN_004b68a4();
LAB_0005cb14:
                    /* WARNING: Does not return */
      pcVar2 = (code *)SoftwareBreakpoint(0x5519,0x5cb18);
      (*pcVar2)();
    }
  }
  return uVar8;
}

