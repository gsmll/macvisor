
void FUN_000508e8(long *param_1)

{
  long lVar1;
  byte bVar2;
  undefined1 uVar3;
  byte bVar4;
  ushort uVar5;
  ushort uVar6;
  ushort uVar7;
  ushort uVar8;
  code *pcVar9;
  ulong uVar10;
  ushort *puVar11;
  ulong *puVar12;
  ulong uVar13;
  undefined1 auVar14 [16];
  undefined1 auVar15 [16];
  undefined8 local_a0;
  long local_98;
  undefined1 local_90 [8];
  ulong local_88;
  ulong local_80;
  undefined8 uStack_78;
  ulong local_70 [2];
  
  if (param_1 == (long *)0x0) {
    return;
  }
  auVar14 = FUN_0004ed84();
  uVar10 = FUN_0004ed48();
  if ((uVar10 == 0) || (uVar10 <= uVar10 + 8)) {
    local_70[1] = 0;
    local_70[0] = uVar10;
    do {
      puVar11 = (ushort *)FUN_0004eb4c(local_70);
      if (puVar11 == (ushort *)0x0) {
        return;
      }
      if (puVar11 + 6 < puVar11) goto LAB_00050c80;
    } while (((uint)(byte)puVar11[1] << 0x10 | (uint)*(byte *)((long)puVar11 + 3) << 0x18 |
             (uint)*puVar11) != 10);
    if (0x17 < ((ulong)(byte)puVar11[3] << 0x10 | (ulong)*(byte *)((long)puVar11 + 7) << 0x18 |
                (ulong)puVar11[2] |
               (ulong)((uint)(byte)puVar11[5] << 0x10 | (uint)*(byte *)((long)puVar11 + 0xb) << 0x18
                      | (uint)puVar11[4]) << 0x20) - 0x18) {
      FUN_00118b28(s__s__warning__found__zu_subgraphs_005bb874);
    }
    puVar11 = (ushort *)FUN_0004e7b8(puVar11,0);
    uVar6 = puVar11[8];
    uVar5 = puVar11[10];
    bVar2 = *(byte *)((long)puVar11 + 0x17);
    uVar7 = puVar11[0xb];
    if (bVar2 >> 2 != 0) {
                    /* WARNING: Subroutine does not return */
      FUN_001150e0(s_integer_overflow_005bb5bd);
    }
    uVar3 = *(undefined1 *)((long)puVar11 + 0x11);
    bVar4 = *(byte *)((long)puVar11 + 0x13);
    uVar8 = puVar11[9];
    uVar13 = ((ulong)(byte)puVar11[1] << 0x10 | (ulong)*(byte *)((long)puVar11 + 3) << 0x18 |
              (ulong)*puVar11 |
             (ulong)((uint)(byte)puVar11[3] << 0x10 | (uint)*(byte *)((long)puVar11 + 7) << 0x18 |
                    (uint)puVar11[2]) << 0x20) + 0x3fff +
             ((ulong)(byte)puVar11[5] << 0x10 | (ulong)*(byte *)((long)puVar11 + 0xb) << 0x18 |
              (ulong)puVar11[4] |
             (ulong)((uint)(byte)puVar11[7] << 0x10 | (uint)*(byte *)((long)puVar11 + 0xf) << 0x18 |
                    (uint)puVar11[6]) << 0x20) & 0xffffffffffffc000;
    local_90[0] = 0x11;
    thunk_FUN_00114330((ulong)local_90 | 1,0xf);
    uStack_78 = 0xf;
    local_a0 = 0;
    local_98 = 0;
    local_80 = uVar13;
    auVar15 = FUN_00034a2c();
    uVar10 = (**(code **)(auVar15._8_8_ + 0x30))(auVar15._0_8_,0x1800,local_90,&local_a0,0,0);
    uVar10 = uVar10 & 0xff;
    if (uVar10 == 0) {
      uVar10 = (ulong)(byte)uVar8 << 0x10 | (ulong)bVar4 << 0x18 |
               (ulong)CONCAT11(uVar3,(char)uVar6) |
               (ulong)((uint)(byte)uVar7 << 0x10 | (uint)bVar2 << 0x18 | (uint)uVar5) << 0x20;
      lVar1 = auVar14._0_8_ + uVar10 * 0x40;
      if (auVar14._8_8_ <= uVar10 << 6) {
        lVar1 = 0;
      }
      FUN_000510e4(lVar1,local_a0,local_98,uVar13);
      if (local_98 == 0) {
                    /* WARNING: Subroutine does not return */
        FUN_00054354();
      }
      (**(code **)(local_98 + 8))(local_a0,local_90);
      uVar10 = (ulong)(byte)puVar11[1] << 0x10 | (ulong)*(byte *)((long)puVar11 + 3) << 0x18 |
               (ulong)*puVar11 |
               (ulong)((uint)(byte)puVar11[3] << 0x10 | (uint)*(byte *)((long)puVar11 + 7) << 0x18 |
                      (uint)puVar11[2]) << 0x20;
      if (local_88 <= local_88 + uVar10) {
        puVar12 = (ulong *)*param_1;
        *puVar12 = local_88;
        puVar12[1] = uVar10;
        local_88 = local_88 + uVar10;
        if ((local_88 == 0) || (local_88 <= local_88 + 8)) {
          puVar12[2] = local_88;
          return;
        }
      }
    }
    else if ((((undefined8 *)0x64cb3f < &DAT_0064cb40 + uVar10) &&
             (&DAT_0064cb48 + uVar10 < (undefined8 *)0x64cb81)) &&
            (&DAT_0064cb40 + uVar10 <= &DAT_0064cb48 + uVar10)) {
                    /* WARNING: Subroutine does not return */
      FUN_0005b190(0,s_Failed_to_map_memory_for_subgrap_005bb8ca);
    }
  }
LAB_00050c80:
                    /* WARNING: Does not return */
  pcVar9 = (code *)SoftwareBreakpoint(0x5519,0x50c84);
  (*pcVar9)();
}

