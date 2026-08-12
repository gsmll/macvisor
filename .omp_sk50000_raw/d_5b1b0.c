
void FUN_0005b1b0(ulong param_1,undefined8 param_2,undefined8 param_3)

{
  long lVar1;
  undefined2 *puVar2;
  undefined2 uVar3;
  undefined2 uVar4;
  undefined8 uVar5;
  undefined8 uVar6;
  code *pcVar7;
  ulong uVar8;
  long lVar9;
  undefined8 uVar10;
  undefined8 uVar11;
  undefined8 uVar12;
  undefined8 uVar13;
  undefined8 uVar14;
  long *plVar15;
  char *pcVar16;
  ulong uVar17;
  ulong uVar18;
  ulong *puVar19;
  ulong uVar20;
  ulong uVar21;
  ulong unaff_x30;
  ulong local_270;
  undefined8 uStack_268;
  undefined8 local_240;
  undefined8 uStack_238;
  undefined8 local_230;
  undefined1 auStack_228 [128];
  undefined8 local_1a8;
  undefined1 auStack_1a0 [64];
  undefined8 local_160;
  undefined8 local_158;
  undefined4 local_150;
  undefined4 local_14c;
  undefined4 local_148;
  undefined4 local_144;
  ulong local_140;
  undefined8 uStack_138;
  undefined8 local_130;
  undefined8 uStack_128;
  ulong local_120;
  undefined8 uStack_118;
  undefined8 local_110;
  undefined8 uStack_108;
  undefined8 local_100;
  undefined8 uStack_f8;
  ulong local_f0;
  ulong uStack_e8;
  undefined8 local_e0;
  undefined8 uStack_d8;
  undefined8 local_d0;
  ulong auStack_c8 [11];
  ulong local_70 [2];
  
  uVar8 = FUN_00060524();
  if (((param_1 != 0) || (param_1 = uVar8, uVar8 <= uVar8 + 0x178)) &&
     (*(ulong *)(param_1 + 0x48) = *(ulong *)(param_1 + 0x48) | 0x20, uVar8 <= uVar8 + 0x178)) {
    *(ulong *)(uVar8 + 0x48) = *(ulong *)(uVar8 + 0x48) | 0x40;
    uVar21 = uVar8 >> 0xe & 0xffffff;
    uVar17 = param_1 >> 0xe & 0xffffff;
    FUN_001185ec(0xeb1a02bf914012ba,s__xrt_0x_06x__Thread_requested_pa_005bc486);
    FUN_00118abc(s__xrt_0x06x__Full_panic_message___005bc4b5,0x20,1,0xeb1a02bf914012ba);
    FUN_00118c38(0xeb1a02bf914012ba,param_2,param_3);
    FUN_00118abc(&DAT_005bc4d6,2,1,0xeb1a02bf914012ba);
    if (param_1 == uVar8) {
      FUN_00062474(s_Panic_requested_005bc4d9,0x3d,0xeb1a02bf914012ba,param_1,1,0,0,0,uVar21,uVar17)
      ;
    }
    thunk_FUN_00114330(auStack_228,0x1b8);
    FUN_00116bb4(auStack_228,0x80,param_2,param_3);
    uVar17 = *(ulong *)(param_1 + 8);
    local_230 = 0;
    if (uVar17 <= uVar17 + 0x28) {
      lVar9 = FUN_0005d154(uVar17,&local_230);
      if (lVar9 == 0) {
        lVar9 = FUN_0005acac(0x6b2568,1,1);
        if (*(long *)(lVar9 + 0x78) == 0) {
          pcVar16 = s_Unknown_005bc4ee;
        }
        else {
          pcVar16 = &DAT_005bc4e9;
        }
      }
      else {
        pcVar16 = &DAT_005bc4e9;
      }
      FUN_0005b824(auStack_1a0,0x130,0x40,pcVar16);
      lVar9 = FUN_0005acac(0x6b2568,1,1);
      local_1a8 = *(undefined8 *)(lVar9 + 0x40);
      local_160 = FUN_0019afb0(uVar17);
      local_158 = *(undefined8 *)(param_1 + 0x10);
      local_150 = FUN_0005b8c8();
      local_14c = FUN_0019afbc(uVar17);
      local_148 = FUN_00063970(*(undefined8 *)(param_1 + 0xa8));
      local_144 = *(undefined4 *)(param_1 + 0x118);
      local_240 = 0;
      uStack_238 = 0;
      FUN_000615fc(param_1,&uStack_238,&local_240);
      uStack_268 = 0;
      local_270 = 0;
      FUN_000619c8(&local_270,param_1);
      local_70[0] = 0;
      if (param_1 == uVar8) {
        local_270 = 0x5b40c;
        local_70[0] = unaff_x30;
      }
      uVar10 = FUN_000614f8(param_1);
      uVar11 = FUN_00061488(param_1);
      uVar12 = FUN_00061638(param_1);
      uVar13 = FUN_0006198c(param_1);
      uVar6 = uStack_238;
      uVar5 = local_240;
      uVar14 = FUN_0006132c(param_1);
      lVar9 = FUN_0005bc48(local_70,0);
      if (lVar9 == 0) {
        uVar17 = 0xffff000000000000;
      }
      else {
        uVar17 = (ulong)*(ushort *)(lVar9 + 0x40) << 0x30;
      }
      uVar17 = local_70[0] & 0xffffffffffff | uVar17;
      local_70[0] = local_270;
      lVar9 = FUN_0005bc48(local_70,0);
      if (lVar9 == 0) {
        uStack_e8 = 0xffff000000000000;
      }
      else {
        uStack_e8 = (ulong)*(ushort *)(lVar9 + 0x40) << 0x30;
      }
      uStack_e8 = local_70[0] & 0xffffffffffff | uStack_e8;
      local_110 = 0;
      uStack_108 = uVar6;
      local_100 = uVar5;
      local_e0 = uStack_268;
      uStack_d8 = 0;
      local_140 = param_1;
      uStack_138 = uVar10;
      local_130 = uVar11;
      uStack_128 = uVar12;
      local_120 = param_1;
      uStack_118 = uVar13;
      uStack_f8 = uVar14;
      local_f0 = uVar17;
      if (*(long *)(param_1 + 0xa8) != 0) {
        local_110 = FUN_00063910();
      }
      uVar21 = FUN_00061044(param_1,0,&local_d0,0xc,0);
      uVar17 = 0;
      if (uVar21 != 0) {
        uVar17 = 0;
        puVar19 = &local_d0;
        uVar18 = uVar21;
        do {
          if (((puVar19 < &local_d0) || (local_70 < puVar19 + 1)) || (puVar19 + 1 < puVar19))
          goto LAB_0005b820;
          uVar20 = (ulong)*(ushort *)((long)puVar19 + 6);
          if (uVar17 <= uVar20 && uVar20 != 0xffff) {
            uVar17 = uVar20 + 1;
          }
          puVar19 = puVar19 + 1;
          uVar18 = uVar18 - 1;
        } while (uVar18 != 0);
      }
      lVar9 = 0;
      if (uVar17 < 7) {
        lVar9 = 6 - uVar17;
      }
      if (uVar21 < (ulong)(lVar9 << 1)) {
        if ((local_70 < auStack_c8 + uVar21) || (auStack_c8 + uVar21 < &local_d0 + uVar21))
        goto LAB_0005b820;
        *(undefined2 *)((long)auStack_c8 + uVar21 * 8 + -2) = 6;
      }
      else {
        uVar21 = lVar9 << 1;
      }
      if (uVar17 < 7) {
        lVar9 = 6 - uVar17;
        plVar15 = (long *)FUN_0005acac(0x6b2568,1,1);
        for (plVar15 = (long *)*plVar15; plVar15 != (long *)0x0; plVar15 = (long *)*plVar15) {
          if ((*(char *)(plVar15 + 1) < '\0') &&
             (uVar18 = (ulong)*(ushort *)(plVar15 + 8), uVar18 < uVar17)) {
            puVar19 = &local_d0 + lVar9 * 2 + uVar18 * 2;
            if ((puVar19 < &local_d0 || local_70 < puVar19 + 2) || puVar19 + 2 < puVar19)
            goto LAB_0005b820;
            uVar18 = (lVar9 + uVar18) * 0x10 + 0x158;
            lVar1 = 0;
            if (uVar18 < 0x1b9) {
              lVar1 = 0x1b8 - uVar18;
            }
            uVar18 = FUN_00117cc8(puVar19,plVar15 + 2,0x10,lVar1);
            if (uVar18 + 0x10 < uVar18) goto LAB_0005b820;
          }
        }
      }
      else {
        lVar9 = 0;
      }
      if (uVar21 != 0) {
        puVar19 = &local_d0;
        do {
          if (((puVar19 < &local_d0) || (local_70 < puVar19 + 1)) || (puVar19 + 1 < puVar19))
          goto LAB_0005b820;
          *puVar19 = *puVar19 + (lVar9 << 0x30);
          uVar21 = uVar21 - 1;
          puVar19 = puVar19 + 1;
        } while (uVar21 != 0);
      }
      if (*(code **)(uVar8 + 0xa0) == (code *)0x0) {
        pcVar16 = s__xrt_0x_06x__Thread_has_no_panic_005bc520;
      }
      else {
        (**(code **)(uVar8 + 0xa0))(auStack_228);
        pcVar16 = s__xrt_0x_06x__Thread_panic_handle_005bc4f6;
      }
      FUN_001185ec(0xeb1a02bf914012ba,pcVar16);
      FUN_0005e4d8(auStack_228,0x6b04d0,0x2000,0);
      FUN_000538c8(s__Exclave__005bc54e,0x6b04d0,0x2000,0xeb1a02bf914012ba);
      lVar9 = 0;
      while (lVar9 != 0x2000) {
        pcVar16 = (char *)(lVar9 + 0x6b04d0);
        lVar9 = lVar9 + 1;
        if (*pcVar16 == '\0') {
          FUN_0011883c(0x6b04d0,0xaa1603fbd280001c);
          lVar9 = FUN_00053444();
          if (lVar9 != 0) {
            FUN_000552c0(lVar9,6,0x6b04d0);
          }
          lVar9 = FUN_000533ec();
          if (lVar9 != 0) {
            puVar2 = (undefined2 *)tpidrro_el0;
            uVar3 = *puVar2;
            uVar4 = puVar2[2];
            CallSupervisor(0);
            *(char *)puVar2 = (char)uVar3;
            *(undefined1 *)((long)puVar2 + 7) = *(undefined1 *)((long)puVar2 + 7);
            *(undefined1 *)(puVar2 + 3) = *(undefined1 *)(puVar2 + 3);
            *(char *)((long)puVar2 + 5) = (char)((ushort)uVar4 >> 8);
            *(char *)(puVar2 + 2) = (char)uVar4;
            *(undefined1 *)((long)puVar2 + 3) = *(undefined1 *)((long)puVar2 + 3);
            *(undefined1 *)(puVar2 + 1) = *(undefined1 *)(puVar2 + 1);
            *(char *)((long)puVar2 + 1) = (char)((ushort)uVar3 >> 8);
          }
          FUN_001185ec(0xeb1a02bf914012ba,s__xrt_0x_06x__Unable_to_trigger_d_005bc559);
                    /* WARNING: Does not return */
          pcVar7 = (code *)SoftwareBreakpoint(1,0x5b820);
          (*pcVar7)();
        }
      }
    }
  }
LAB_0005b820:
                    /* WARNING: Does not return */
  pcVar7 = (code *)SoftwareBreakpoint(0x5519,0x5b824);
  (*pcVar7)();
}

