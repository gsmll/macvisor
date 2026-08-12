
void FUN_000510e4(long param_1,undefined8 param_2,long param_3,ulong param_4)

{
  undefined1 *puVar1;
  uint uVar2;
  code *pcVar3;
  long lVar4;
  ulong uVar5;
  char *pcVar6;
  ulong uVar7;
  undefined1 auStack_88 [32];
  long local_68;
  
  local_68 = -0x2c8502b44bfffed6;
  lVar4 = FUN_00034f70();
  if (0x3fff < param_4) {
    uVar7 = 0;
    puVar1 = (undefined1 *)tpidrro_el0;
    do {
      puVar1[4] = 0;
      puVar1[1] = 0;
      puVar1[5] = 0;
      puVar1[2] = 0;
      puVar1[3] = 0;
      *puVar1 = 0x11;
      puVar1[6] = 0;
      puVar1[7] = 0;
      puVar1[0xd] = (char)(uVar7 >> 0x1a);
      puVar1[8] = 0;
      puVar1[9] = (char)(uVar7 << 6);
      puVar1[0xb] = (char)(uVar7 >> 10);
      puVar1[10] = (char)(uVar7 >> 2);
      puVar1[0xc] = (char)(uVar7 >> 0x12);
      uVar2 = (uint)(uVar7 >> 0x20);
      puVar1[0xf] = (char)(uVar2 >> 10);
      puVar1[0xe] = (char)(uVar2 >> 2);
      puVar1[0x15] = (char)((ulong)lVar4 >> 0x28);
      puVar1[0x10] = (char)lVar4;
      puVar1[0x13] = (char)((ulong)lVar4 >> 0x18);
      puVar1[0x12] = (char)((ulong)lVar4 >> 0x10);
      puVar1[0x11] = (char)((ulong)lVar4 >> 8);
      puVar1[0x14] = (char)((ulong)lVar4 >> 0x20);
      puVar1[0x17] = (char)((ulong)lVar4 >> 0x38);
      puVar1[0x16] = (char)((ulong)lVar4 >> 0x30);
      CallSupervisor(0);
      puVar1[7] = 0;
      puVar1[6] = 0;
      puVar1[5] = 0;
      puVar1[4] = 0;
      puVar1[3] = 0;
      puVar1[2] = 0;
      *puVar1 = 0x11;
      puVar1[1] = 0;
      if (param_1 != 0) {
        FUN_00051350(auStack_88,param_1,0);
        pcVar6 = s_Failed_to_create_frame__zu_from_u_005bb7ca;
LAB_00051340:
                    /* WARNING: Subroutine does not return */
        FUN_0005b190(0,pcVar6);
      }
      uVar5 = (**(code **)(param_3 + 0x28))(param_2,uVar7 << 0xe,lVar4);
      uVar5 = uVar5 & 0xff;
      if (uVar5 != 0) {
        if (((&DAT_0064cb40 + uVar5 < &DAT_0064cb40) || (&DAT_0064cb80 < &DAT_0064cb48 + uVar5)) ||
           (&DAT_0064cb48 + uVar5 < &DAT_0064cb40 + uVar5)) {
                    /* WARNING: Does not return */
          pcVar3 = (code *)SoftwareBreakpoint(0x5519,0x51350);
          (*pcVar3)();
        }
        pcVar6 = s_Failed_to_map_the_frame_idx___zu_005bb805;
        goto LAB_00051340;
      }
      do {
        CallSupervisor(4);
      } while (lVar4 == 1);
      uVar7 = uVar7 + 1;
    } while (uVar7 != param_4 >> 0xe);
  }
  if (local_68 == -0x2c8502b44bfffed6) {
    FUN_004b23d8(lVar4);
    return;
  }
                    /* WARNING: Subroutine does not return */
  FUN_0011d7e8();
}

