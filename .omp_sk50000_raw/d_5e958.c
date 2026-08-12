
undefined8 FUN_0005e958(undefined4 param_1)

{
  byte *pbVar1;
  byte bVar2;
  code *pcVar3;
  long lVar4;
  long lVar5;
  uint uVar6;
  undefined4 *puVar7;
  byte *pbVar8;
  byte bStack_11;
  undefined4 local_10;
  undefined4 uStack_c;
  undefined8 local_8;
  
  local_10 = param_1;
  uStack_c = 0;
  lVar4 = 0;
  do {
    bVar2 = *(byte *)((long)&local_10 + lVar4);
    if (bVar2 == 0) {
      if (lVar4 == 0) {
        lVar4 = 4;
        lVar5 = 4;
        puVar7 = &local_10;
        goto LAB_0005e9e8;
      }
      break;
    }
    uVar6 = (uint)bVar2;
    if (((9 < uVar6 - 0x30 && 0x19 < (bVar2 & 0xffffffdf) - 0x41) &&
        (0x3c < uVar6 - 0x23 || (1L << ((ulong)(uVar6 - 0x23) & 0x3f) & 0x1000000000000587U) == 0))
       && (uVar6 != 0x7e)) {
      *(undefined1 *)((long)&local_10 + lVar4) = 0x3f;
    }
    lVar4 = lVar4 + 1;
  } while (lVar4 != 4);
  goto LAB_0005ea08;
  while( true ) {
    *(undefined1 *)puVar7 = 0x3f;
    lVar5 = lVar5 + -1;
    puVar7 = (undefined4 *)((long)puVar7 + 1);
    if (lVar5 == 0) break;
LAB_0005e9e8:
    if (((undefined1 *)((long)&uStack_c + 1) <= puVar7) || (puVar7 < &local_10)) goto LAB_0005ea90;
  }
LAB_0005ea08:
  pbVar8 = (byte *)((long)&local_10 + lVar4);
  if ((pbVar8 < (byte *)((long)&uStack_c + 1)) && (&local_10 <= pbVar8)) {
    *pbVar8 = 0;
    local_8 = 0;
    pbVar8 = (byte *)&local_8;
    while( true ) {
      pbVar1 = &bStack_11 + lVar4;
      if ((((byte *)((long)&uStack_c + 1) <= pbVar1) || (pbVar1 < &local_10)) ||
         (((byte *)((ulong)&local_8 | 5) <= pbVar8 || (pbVar8 < &local_8)))) break;
      *pbVar8 = *pbVar1;
      lVar4 = lVar4 + -1;
      pbVar8 = pbVar8 + 1;
      if (lVar4 == 0) {
        return local_8;
      }
    }
  }
LAB_0005ea90:
                    /* WARNING: Does not return */
  pcVar3 = (code *)SoftwareBreakpoint(0x5519,0x5ea94);
  (*pcVar3)();
}

