
void FUN_0005ad58(long param_1)

{
  code *pcVar1;
  undefined8 uVar2;
  ulong uVar3;
  ulong uVar4;
  long in_xzr;
  ulong local_28;
  
  if (*(ulong *)(param_1 + 0x48) < *(ulong *)(param_1 + 0x28)) {
    uVar3 = *(ulong *)(param_1 + 0x50);
    uVar4 = *(ulong *)(param_1 + 0x48);
    if ((uVar4 < uVar3 || uVar4 - uVar3 == 0) || ((uVar4 - uVar3) + *(long *)(param_1 + 0x60) < 5))
    {
      if (uVar4 <= uVar3) {
        uVar4 = uVar3;
      }
      local_28 = uVar4 + 5;
      if (*(ulong *)(param_1 + 0x28) <= uVar4 + 5) {
        local_28 = *(ulong *)(param_1 + 0x28);
      }
      local_28 = local_28 << 6;
      uVar4 = (**(code **)(*(long *)(param_1 + 0x38) + 0x18))
                        (*(undefined8 *)(param_1 + 0x30),&local_28);
      uVar4 = uVar4 & 0xff;
      if (uVar4 != 0) {
        uVar2 = FUN_00060524();
        if ((&DAT_0064cb40 <= &DAT_0064cb40 + uVar4 && &DAT_0064cb48 + uVar4 <= &DAT_0064cb80) &&
            &DAT_0064cb40 + uVar4 <= &DAT_0064cb48 + uVar4) {
                    /* WARNING: Subroutine does not return */
          FUN_0005b190(uVar2,s_Failed_to_allocate_trace_memory__005bc391);
        }
                    /* WARNING: Does not return */
        pcVar1 = (code *)SoftwareBreakpoint(0x5519,0x5ae4c);
        (*pcVar1)();
      }
      *(ulong *)(param_1 + 0x48) = local_28 >> 6;
      *(long *)(param_1 + 0x50) = *(long *)(param_1 + 0x50) + in_xzr;
      LORelease();
    }
  }
  return;
}

