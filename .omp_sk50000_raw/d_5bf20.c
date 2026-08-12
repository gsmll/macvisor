
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0005bf20(ulong *param_1)

{
  code *pcVar1;
  long lVar2;
  ulong uVar3;
  ulong *puVar4;
  ulong *puVar5;
  ulong *puVar6;
  ulong uVar7;
  ulong uVar8;
  undefined1 local_21;
  
  lVar2 = FUN_0005acac(0x6b2568,1,1);
  *param_1 = *param_1 & 0xfffffffff;
  local_21 = 0;
  do {
    uVar3 = FUN_00060570(&local_21);
  } while ((uVar3 & 1) == 0);
  do {
    while( true ) {
      puVar6 = *(ulong **)(lVar2 + 0x10);
      if (puVar6 == (ulong *)0x0) goto LAB_0005c06c;
      if (param_1 != puVar6) break;
      if ((puVar6 + 0x2f < param_1) || (uVar3 = *param_1 & 0xfffffffff, uVar3 + 0x178 < uVar3)) {
LAB_0005c0a8:
                    /* WARNING: Does not return */
        pcVar1 = (code *)SoftwareBreakpoint(0x5519,0x5c0ac);
        (*pcVar1)();
      }
      if (*(ulong **)(lVar2 + 0x10) == puVar6) {
        *(ulong *)(lVar2 + 0x10) = uVar3;
        goto LAB_0005c06c;
      }
    }
    if (puVar6 + 0x2f < puVar6) goto LAB_0005c0a8;
    do {
      uVar3 = *puVar6;
      if ((uVar3 >> 0x25 & 1) != 0) break;
      puVar6 = (ulong *)(uVar3 & 0xfffffffff);
    } while (puVar6 != (ulong *)0x0 && param_1 != puVar6);
    if (puVar6 + 0x2f < puVar6) goto LAB_0005c0a8;
    puVar5 = puVar6;
    uVar8 = uVar3;
    if (puVar6 == (ulong *)0x0) goto LAB_0005c06c;
    do {
      uVar7 = uVar8;
      puVar4 = puVar5;
      puVar5 = puVar4;
      if (puVar4 == param_1) break;
      uVar8 = 0;
      puVar5 = (ulong *)(uVar7 & 0xfffffffff);
      if ((puVar5 != (ulong *)0x0) && (param_1 != puVar5)) {
        do {
          uVar8 = *puVar5;
          if ((uVar8 >> 0x25 & 1) != 0) break;
          puVar5 = (ulong *)(uVar8 & 0xfffffffff);
        } while (puVar5 != (ulong *)0x0 && param_1 != puVar5);
      }
      if (puVar5 + 0x2f < puVar5) goto LAB_0005c0a8;
      puVar6 = puVar4;
      uVar3 = uVar7;
    } while (puVar5 != (ulong *)0x0);
    if (puVar5 == (ulong *)0x0) goto LAB_0005c06c;
  } while ((puVar6 == (ulong *)0x0) || (*puVar6 != uVar3));
  *puVar6 = *param_1 & 0xfff0000000000000 |
            *param_1 & 0xfffffffff | (uVar3 >> 0x24 & 0xffff) << 0x24;
LAB_0005c06c:
  FUN_000605f8(&local_21);
  FUN_00060650();
  *param_1 = 0;
  if (_DAT_006b2560 != (code *)0x0) {
    (*_DAT_006b2560)(param_1,0);
  }
  return;
}

