
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined1 * FUN_00054624(long param_1)

{
  code *pcVar1;
  ulong uVar2;
  long lVar3;
  ulong uVar4;
  long lVar5;
  
  lVar3 = 0;
  uVar2 = 0;
  _DAT_006b0410 = 0;
  _DAT_006b0448 = 0x400;
  do {
    lVar5 = *(long *)(param_1 + lVar3);
    if (lVar5 - 1U < 0x2b) {
      uVar4 = ((long *)(param_1 + lVar3))[1];
      switch(lVar5) {
      default:
        _DAT_006b0350 = uVar4;
        break;
      case 2:
        _DAT_006b0358 = uVar4;
        break;
      case 3:
        _DAT_006b0360 = uVar4;
        break;
      case 4:
      case 5:
      case 6:
      case 10:
      case 0xb:
      case 0xd:
      case 0x19:
        break;
      case 7:
        _DAT_006b03a0 = uVar4;
        break;
      case 8:
        _DAT_006b03a8 = uVar4;
        break;
      case 9:
        _DAT_006b03b0 = uVar4;
        break;
      case 0xc:
        _DAT_006b03b8 = uVar4;
        break;
      case 0xe:
        _DAT_006b03d8 = uVar4;
        break;
      case 0xf:
        _DAT_006b03e0 = uVar4;
        break;
      case 0x10:
        _DAT_006b03e8 = uVar4;
        break;
      case 0x11:
        _DAT_006b03f0 = uVar4;
        break;
      case 0x12:
        _DAT_006b03f8 = uVar4;
        break;
      case 0x13:
        _DAT_006b03c0 = uVar4;
        break;
      case 0x14:
        _DAT_006b03c8 = uVar4;
        break;
      case 0x15:
        DAT_006b0348 = uVar4 == 0;
        _DAT_006b0400 = uVar4;
        break;
      case 0x16:
        uVar2 = uVar4;
        break;
      case 0x17:
        _DAT_006b0410 = uVar4;
        break;
      case 0x18:
        DAT_006b0420 = (undefined1)uVar4;
        break;
      case 0x1a:
        _DAT_006b0428 = uVar4;
        break;
      case 0x1b:
        _DAT_006b0430 = uVar4;
        break;
      case 0x1c:
        _DAT_006b0438 = uVar4;
        break;
      case 0x1d:
        _DAT_006b0450 = uVar4;
      case 0x1e:
        _DAT_006b0458 = uVar4;
        break;
      case 0x1f:
        _DAT_006b0460 = uVar4;
        break;
      case 0x20:
        _DAT_006b03d0 = uVar4;
        break;
      case 0x21:
        _DAT_006b0468 = uVar4;
        break;
      case 0x22:
        _DAT_006b0470 = uVar4;
        break;
      case 0x23:
        _DAT_006b0478 = uVar4;
        break;
      case 0x24:
        _DAT_006b0480 = uVar4;
        break;
      case 0x25:
        _DAT_006b0488 = uVar4;
        break;
      case 0x26:
        _DAT_006b0490 = uVar4;
        break;
      case 0x27:
        _DAT_006b0418 = uVar4;
        break;
      case 0x28:
        _DAT_006b0378 = uVar4;
        break;
      case 0x29:
        _DAT_006b0388 = uVar4;
        break;
      case 0x2a:
        _DAT_006b0498 = uVar4;
        break;
      case 0x2b:
        _DAT_006b04a0 = uVar4;
      }
    }
    lVar3 = lVar3 + 0x10;
  } while (lVar3 != 0x400);
  _DAT_006b0440 = param_1;
  if ((uVar2 != 0) && (uVar2 + _DAT_006b0410 * 0x78 < uVar2 + 0x78 || uVar2 + 0x78 < uVar2)) {
                    /* WARNING: Does not return */
    pcVar1 = (code *)SoftwareBreakpoint(0x5519,0x548b4);
    (*pcVar1)();
  }
  lRam000000000064ccd0 = param_1;
  _DAT_006b0408 = uVar2;
                    /* WARNING (jumptable): Read-only address (ram,0x0064ccd0) is written */
                    /* WARNING: Read-only address (ram,0x0064ccd0) is written */
  FUN_0005ba5c(0x64ccb8);
                    /* WARNING (jumptable): Read-only address (ram,0x0064ccf0) is written */
                    /* WARNING: Read-only address (ram,0x0064ccf0) is written */
  puRam000000000064ccf0 = &DAT_006b0348;
  FUN_0005ba5c();
  return &DAT_006b0348;
}

