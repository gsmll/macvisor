
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8
FUN_00053db8(ulong *param_1,ulong param_2,uint param_3,int param_4,long *param_5,ulong param_6,
            uint param_7)

{
  uint5 uVar1;
  undefined3 uVar2;
  undefined2 uVar3;
  code *pcVar4;
  char cVar5;
  ulong uVar6;
  byte *pbVar7;
  ulong uVar8;
  undefined4 *puVar9;
  undefined8 uVar10;
  undefined1 uVar11;
  uint uVar12;
  uint uVar13;
  undefined1 auVar14 [16];
  undefined8 local_90;
  ulong uStack_88;
  ulong local_80;
  undefined8 local_78;
  undefined8 local_70;
  ulong local_68;
  undefined8 local_60;
  undefined8 uStack_58;
  
  uStack_88 = 0;
  local_90 = 0;
  local_78 = 0;
  local_80 = 0;
  if ((((param_5 == (long *)0x0) || (0x3e < param_3)) || (param_1 == (ulong *)0x0)) ||
     ((param_6 & 1) == 0)) goto LAB_00053f50;
  if (param_5 + 2 < param_5) {
LAB_0005402c:
                    /* WARNING: Does not return */
    pcVar4 = (code *)SoftwareBreakpoint(0x5519,0x54030);
    (*pcVar4)();
  }
  if (*param_5 != 0) goto LAB_00053f50;
  local_90 = 0x11;
  if (param_4 - 1U < 6) {
    uVar11 = (undefined1)*(undefined4 *)(&DAT_004bcce0 + (ulong)(param_4 - 1U) * 4);
  }
  else {
    uVar11 = 2;
  }
  local_78._0_2_ = (undefined2)CONCAT41(0x20000000,uVar11);
  uVar3 = (undefined2)local_78;
  local_78._0_3_ = CONCAT12((char)param_3,(undefined2)local_78);
  uVar1 = CONCAT23(0x2000,(undefined3)local_78);
  local_78 = (ulong)uVar1;
  local_80 = param_2;
  if ((param_7 >> 3 & 1) == 0) {
    uVar13 = 0;
    uVar2 = (undefined3)(uVar1 >> 0x10);
    local_78._0_2_ = CONCAT11((param_7 & 0x10) == 0,uVar11);
    local_78 = (ulong)CONCAT32(uVar2,(undefined2)local_78);
    if ((param_2 >> 0x1e == 0) && ((param_7 & 0x10) == 0)) {
      local_78 = (ulong)CONCAT32(uVar2,uVar3);
      if (_DAT_006b0340 == 0) {
        local_60 = 0x4000;
        uStack_58 = 0x2000000102;
        local_70 = 0x11;
        local_68 = 0;
        auVar14 = FUN_00034a2c();
        uVar6 = (**(code **)(auVar14._8_8_ + 0x30))(auVar14._0_8_,8,&local_70,0x6b0330,0,&local_70);
        uVar6 = uVar6 & 0xff;
        if (uVar6 != 0) {
          if ((((undefined8 *)0x64cb3f < &DAT_0064cb40 + uVar6) &&
              (&DAT_0064cb48 + uVar6 < (undefined8 *)0x64cb81)) &&
             (&DAT_0064cb40 + uVar6 <= &DAT_0064cb48 + uVar6)) {
            FUN_004b5ef8();
          }
          goto LAB_0005402c;
        }
        _DAT_006b0340 = local_68;
      }
      uVar13 = 0x20000;
      uStack_88 = _DAT_006b0340;
    }
  }
  else {
    uStack_88 = *param_1;
    uVar13 = 1;
  }
  uVar6 = uStack_88;
  if ((param_7 & 1) == 0) goto LAB_00053f50;
  uVar13 = ((uint)param_6 & 2 | (uint)(param_6 >> 2) & 1) << 3 | uVar13;
  if ((param_7 >> 1 & 1) == 0) {
    uVar13 = uVar13 | 0x20;
  }
  else {
    if ((param_7 >> 5 & 1) == 0) {
      uVar12 = 0x2010000;
    }
    else {
      pbVar7 = (byte *)FUN_00054610();
      if (((*pbVar7 & 1) == 0) && (uVar8 = FUN_000640e4(), (uVar8 & 1) != 0)) {
        uVar13 = uVar13 | 0x10000;
        goto LAB_00053f48;
      }
      uVar12 = 0x10020;
    }
    uVar13 = uVar13 | uVar12;
  }
LAB_00053f48:
  if (!CARRY8(uVar6,param_2)) {
    auVar14 = FUN_00034a2c();
    cVar5 = (**(code **)(auVar14._8_8_ + 0x30))
                      (auVar14._0_8_,uVar13 | (param_7 & 4) << 0x14,&local_90,param_5,0,0);
    if (cVar5 != '\0') {
      uVar10 = FUN_00054034();
      return uVar10;
    }
    if (param_5[1] != 0) {
      (**(code **)(param_5[1] + 8))(*param_5,&local_90);
      *param_1 = uStack_88;
      puVar9 = (undefined4 *)thunk_FUN_0006037c();
      *puVar9 = 0;
      return 1;
    }
                    /* WARNING: Subroutine does not return */
    FUN_00054354(0);
  }
LAB_00053f50:
  puVar9 = (undefined4 *)thunk_FUN_0006037c();
  *puVar9 = 0x16;
  return 0;
}

