
void FUN_00035a78(long param_1,long param_2,long param_3)

{
  long lVar1;
  code *pcVar2;
  ulong uVar3;
  undefined8 local_60;
  undefined8 uStack_58;
  undefined1 local_50;
  undefined4 local_4f;
  undefined3 uStack_4b;
  long local_48;
  long lStack_40;
  undefined1 local_38;
  undefined4 local_37;
  undefined3 uStack_33;
  
  if ((DAT_006af190 & 1) == 0) {
    FUN_00031868();
    FUN_0004158c(param_1,param_2,param_3);
    FUN_00033780();
    FUN_0003c09c();
    lVar1 = (param_2 - param_1) + param_3 * 0x40;
    FUN_0003548c(param_1,param_2 - param_1,lVar1);
    FUN_00041d9c();
    local_50 = 4;
    local_4f = 0;
    uStack_4b = 0;
    local_38 = 0xff;
    local_37 = 0;
    uStack_33 = 0;
    local_60 = 0;
    uStack_58 = 0;
    local_48 = param_1;
    lStack_40 = lVar1;
    uVar3 = FUN_0003c510(0x1000001,&local_50,&local_60,0,0);
    uVar3 = uVar3 & 0xff;
    if (uVar3 != 0) {
      if (((undefined8 *)0x64cb3f < &DAT_0064cb40 + uVar3) &&
         (&DAT_0064cb48 + uVar3 < (undefined8 *)0x64cb81 &&
          &DAT_0064cb40 + uVar3 <= &DAT_0064cb48 + uVar3)) {
                    /* WARNING: Subroutine does not return */
        FUN_004afae4(s__VAS_abort_in_function__s_at_lin_005b20a7);
      }
                    /* WARNING: Does not return */
      pcVar2 = (code *)SoftwareBreakpoint(0x5519,0x35b98);
      (*pcVar2)();
    }
    FUN_00033bb0();
    DAT_006af190 = 1;
  }
  return;
}

