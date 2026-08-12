
void FUN_0005bd7c(code *param_1,undefined8 param_2)

{
  code *pcVar1;
  ulong uVar2;
  int iVar3;
  long lVar4;
  ulong *puVar5;
  undefined1 local_31;
  
  local_31 = 0;
  do {
    iVar3 = FUN_00060570(&local_31);
  } while (iVar3 == 0);
  lVar4 = FUN_0005acac(0x6b2568,1,1);
  puVar5 = *(ulong **)(lVar4 + 0x10);
  if (puVar5 == (ulong *)0x0) {
    uVar2 = 0;
    goto LAB_0005bdf4;
  }
  do {
    uVar2 = *puVar5;
    if ((uVar2 >> 0x25 & 1) != 0) break;
    puVar5 = (ulong *)(uVar2 & 0xfffffffff);
  } while (puVar5 != (ulong *)0x0);
  do {
    while( true ) {
      if (puVar5 + 0x2f < puVar5) {
                    /* WARNING: Does not return */
        pcVar1 = (code *)SoftwareBreakpoint(0x5519,0x5be48);
        (*pcVar1)();
      }
LAB_0005bdf4:
      if (puVar5 == (ulong *)0x0) {
        FUN_000605f8(&local_31);
        return;
      }
      (*param_1)(param_2);
      puVar5 = (ulong *)(uVar2 & 0xfffffffff);
      if (puVar5 != (ulong *)0x0) break;
      uVar2 = 0;
    }
    do {
      uVar2 = *puVar5;
      if ((uVar2 >> 0x25 & 1) != 0) break;
      puVar5 = (ulong *)(uVar2 & 0xfffffffff);
    } while (puVar5 != (ulong *)0x0);
  } while( true );
}

