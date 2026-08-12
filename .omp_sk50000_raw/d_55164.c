
void FUN_00055164(undefined8 param_1)

{
  code *pcVar1;
  ulong uVar2;
  
  uVar2 = FUN_00055b7c(param_1,0x6ad740);
  if (((((((uVar2 & 1) == 0) && (uVar2 = FUN_00056098(param_1,0x6ad740), (uVar2 & 1) == 0)) &&
        (uVar2 = FUN_0005680c(param_1,0x6ad740), (uVar2 & 1) == 0)) &&
       ((uVar2 = FUN_00056f84(param_1,0x6ad740), (uVar2 & 1) == 0 &&
        (uVar2 = FUN_00057708(param_1,0x6ad740), (uVar2 & 1) == 0)))) &&
      ((uVar2 = FUN_00057e8c(param_1,0x6ad740), (uVar2 & 1) == 0 &&
       ((uVar2 = FUN_0005860c(param_1,0x6ad740), (uVar2 & 1) == 0 &&
        (uVar2 = FUN_00058d8c(param_1,0x6ad740), (uVar2 & 1) == 0)))))) &&
     ((uVar2 = FUN_0005950c(param_1,0x6ad740), (uVar2 & 1) == 0 &&
      ((uVar2 = FUN_00059c8c(param_1,0x6ad740), (uVar2 & 1) == 0 &&
       (uVar2 = FUN_0005a40c(param_1,0x6ad740), (uVar2 & 1) == 0)))))) {
                    /* WARNING: Does not return */
    pcVar1 = (code *)SoftwareBreakpoint(1,0x5526c);
    (*pcVar1)();
  }
  FUN_00054960(0x6ad740);
  return;
}

