
/* WARNING: Type propagation algorithm not settling */

undefined8 FUN_0005417c(ulong param_1,ulong param_2,undefined1 (*param_3) [16],uint param_4)

{
  long lVar1;
  char cVar2;
  uint uVar3;
  int iVar4;
  undefined4 *puVar5;
  byte *pbVar6;
  undefined8 uVar7;
  undefined4 uVar8;
  long lVar9;
  long lVar10;
  ulong uVar11;
  long lVar12;
  undefined1 auVar13 [16];
  long local_70;
  ulong local_68 [5];
  
  if (param_3 == (undefined1 (*) [16])0x0) {
    auVar13 = FUN_00034a2c();
    auVar13 = (**(code **)(auVar13._8_8_ + 0x38))(auVar13._0_8_,param_1,0,0);
  }
  else {
    auVar13 = *param_3;
  }
  lVar10 = auVar13._8_8_;
  lVar9 = auVar13._0_8_;
  local_68[2] = 0;
  local_68[1] = 0;
  local_68[4] = 0;
  local_68[3] = 0;
  if (lVar9 == 0) {
LAB_00054210:
    puVar5 = (undefined4 *)thunk_FUN_0006037c();
    uVar8 = 0x16;
LAB_00054220:
    uVar7 = 0;
    *puVar5 = uVar8;
  }
  else {
    if (lVar10 == 0) goto LAB_0005434c;
    uVar3 = (**(code **)(lVar10 + 8))(lVar9,local_68 + 1);
    if ((((param_1 < local_68[2]) || (local_68[3] < param_2)) ||
        (local_68[3] + local_68[2] <= param_1)) || (local_68[3] + local_68[2] < param_2 + param_1))
    goto LAB_00054210;
    uVar11 = param_1 - local_68[2] & 0xffffffffffffc000;
    lVar12 = (param_2 + 0x3fff + (param_1 - local_68[2]) & 0xffffffffffffc000) - uVar11;
    if ((param_4 & 0xc) == 0) {
LAB_000542e8:
      if ((param_4 & 3) == 0) {
        cVar2 = '\0';
      }
      else {
        lVar1 = 0x20;
        if ((param_4 & 1) != 0) {
          lVar1 = 0x30;
        }
        local_70 = lVar12;
        local_68[0] = uVar11;
        cVar2 = (**(code **)(lVar10 + lVar1))(lVar9,local_68,&local_70);
        if ((local_68[0] != uVar11) || (local_70 != lVar12)) {
          FUN_004b5f30();
LAB_0005434c:
                    /* WARNING: Subroutine does not return */
          FUN_00054354();
        }
      }
    }
    else {
      if ((uVar3 >> 0x10 & 1) == 0) {
        puVar5 = (undefined4 *)thunk_FUN_0006037c();
        uVar8 = 0x2d;
        goto LAB_00054220;
      }
      cVar2 = (**(code **)(lVar10 + 0x50))(lVar9,param_4 >> 1 & 4,uVar11,lVar12);
      pbVar6 = (byte *)FUN_00054610();
      if ((*pbVar6 & 1) == 0) {
        iVar4 = FUN_000640e4();
      }
      else {
        iVar4 = 0;
      }
      if (cVar2 == '\0') {
        if ((param_4 & 4) == 0) {
          iVar4 = 1;
        }
        if (iVar4 == 0) {
          param_4 = 2;
        }
        goto LAB_000542e8;
      }
    }
    uVar7 = FUN_00054034(cVar2);
  }
  return uVar7;
}

