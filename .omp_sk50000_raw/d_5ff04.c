
void FUN_0005ff04(undefined8 *param_1,ulong param_2,uint param_3)

{
  long lVar1;
  code *pcVar2;
  int iVar3;
  ulong uVar4;
  long lVar5;
  uint uVar6;
  undefined1 auVar7 [16];
  ulong local_78;
  undefined8 local_70;
  long lStack_68;
  undefined1 local_60 [8];
  long local_58;
  long local_50;
  undefined4 local_48;
  undefined4 local_44;
  
  lVar1 = param_2 + 0x4000;
  if (param_2 < 0xffffffffffffc000) {
    local_60[0] = 0x11;
    thunk_FUN_00114330((ulong)local_60 | 1,0xf);
    local_48 = 0xc;
    local_44 = 0x20;
    uVar6 = param_3 & 0xf;
    if ((param_3 & 0xe) == 0) {
      uVar6 = 1;
    }
    local_50 = lVar1;
    if ((uVar6 & uVar6 - 1) == 0) {
      uVar6 = 0x40c8;
      if ((param_3 & 2) != 0) {
        uVar6 = 0x44c8;
      }
      local_70 = 0;
      lStack_68 = 0;
      auVar7 = FUN_00034a2c();
      uVar4 = (**(code **)(auVar7._8_8_ + 0x30))
                        (auVar7._0_8_,(param_3 & 4) << 0xb | (param_3 >> 3 & 1) << 9 | uVar6,
                         local_60,&local_70,0,local_60);
      uVar4 = uVar4 & 0xff;
      if (uVar4 == 0) {
        local_78 = param_2;
        uVar4 = (**(code **)(lStack_68 + 0x18))(local_70,&local_78);
        uVar4 = uVar4 & 0xff;
        if (uVar4 == 0) {
          lVar5 = FUN_0005bb68();
          iVar3 = *(int *)(lVar5 + 0x88);
          *(int *)(lVar5 + 0x88) = iVar3 + 1;
          if (iVar3 != -1) {
            *param_1 = local_70;
            param_1[1] = lStack_68;
            *(uint *)(param_1 + 2) = param_3 & 0xffffffdf | (uint)((param_3 & 0xf) == 0);
            *(undefined4 *)((long)param_1 + 0x14) = 0;
            param_1[3] = local_58;
            param_1[4] = local_58 + lVar1;
            param_1[5] = lVar1;
            *(int *)(param_1 + 6) = iVar3 + 1;
            *(undefined4 *)((long)param_1 + 0x34) = 0;
            return;
          }
          FUN_004b6ff0();
        }
        else if (((undefined8 *)0x64cb3f < &DAT_0064cb40 + uVar4 &&
                 &DAT_0064cb48 + uVar4 < (undefined8 *)0x64cb81) &&
                 &DAT_0064cb40 + uVar4 <= &DAT_0064cb48 + uVar4) {
                    /* WARNING: Subroutine does not return */
          FUN_004afae4(s_failed_to_bump_new_stack_with_at_005bd27b);
        }
      }
      else if ((((undefined8 *)0x64cb3f < &DAT_0064cb40 + uVar4) &&
               (&DAT_0064cb48 + uVar4 < (undefined8 *)0x64cb81)) &&
              (&DAT_0064cb40 + uVar4 <= &DAT_0064cb48 + uVar4)) {
                    /* WARNING: Subroutine does not return */
        FUN_004afae4(s_failed_to_allocate_stack_with_at_005bd243);
      }
                    /* WARNING: Does not return */
      pcVar2 = (code *)SoftwareBreakpoint(0x5519,0x600f0);
      (*pcVar2)();
    }
  }
  else {
    FUN_004b7008();
  }
                    /* WARNING: Subroutine does not return */
  FUN_004afae4(s_more_than_one_mapping_type_speci_005bd219);
}

