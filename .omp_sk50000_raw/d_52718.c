
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00052718(undefined8 param_1)

{
  undefined1 *puVar1;
  int iVar2;
  long lVar3;
  long lVar4;
  
  if (_DAT_006af8c8 == 0) {
    _DAT_006af8c8 = param_1;
    return;
  }
  lVar3 = FUN_004b5e30();
  lVar4 = FUN_00054610();
  FUN_000545a8(*(byte *)(lVar4 + 0xd8) & 1);
  FUN_000528c4(lVar3 != 0,1);
  FUN_000528c4(lVar3 != 0,0);
  if ((lVar3 == 0) && (iVar2 = FUN_00060564(), iVar2 != 0)) {
    iVar2 = FUN_000600f0(0x40000,&DAT_00052930,lVar4);
  }
  else {
    FUN_0005295c(lVar4);
    iVar2 = FUN_00001378();
  }
  if (iVar2 == 0) {
    FUN_00060524();
    FUN_0005b0bc();
    if (lVar3 != 0) {
      return;
    }
    FUN_0005b89c();
    FUN_00118b28(s_Userspace____04hx__is_inited__Wa_005bb99f);
    iVar2 = FUN_0005ab94(1,2);
    if (iVar2 == 1) {
      FUN_00065020();
    }
    puVar1 = (undefined1 *)tpidrro_el0;
    puVar1[1] = 0;
    *puVar1 = 0;
    puVar1[4] = 0;
    puVar1[2] = 0;
    puVar1[5] = 0;
    puVar1[3] = 0;
    puVar1[6] = 0;
    puVar1[7] = 0;
    CallSupervisor(0);
    *puVar1 = 0;
    puVar1[7] = 0;
    puVar1[6] = 0;
    puVar1[5] = 0;
    puVar1[4] = 0;
    puVar1[3] = 0;
    puVar1[2] = 0;
    puVar1[1] = 0;
                    /* WARNING: Subroutine does not return */
    FUN_001150e0(s_exclave_is_scheduled_after_suspe_005bb9d8,1);
  }
                    /* WARNING: Subroutine does not return */
  FUN_004afae4(s_xrt_init_failed_with___d_005bb986);
}

