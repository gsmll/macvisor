
undefined8 FUN_00050ce8(long *param_1,long param_2,ushort *param_3)

{
  ushort *puVar1;
  undefined1 uVar2;
  byte bVar3;
  byte bVar4;
  byte bVar5;
  byte bVar6;
  undefined1 uVar7;
  undefined1 uVar8;
  undefined1 uVar9;
  undefined1 uVar10;
  undefined1 uVar11;
  undefined1 uVar12;
  undefined1 uVar13;
  byte bVar14;
  undefined1 uVar15;
  byte bVar16;
  ushort uVar17;
  ushort uVar18;
  ushort uVar19;
  ushort uVar20;
  ushort uVar21;
  ushort uVar22;
  code *pcVar23;
  char cVar24;
  int iVar25;
  ushort *puVar26;
  ulong uVar27;
  ulong uVar28;
  long lVar29;
  undefined1 auVar30 [16];
  undefined1 local_90 [8];
  long local_88;
  ulong local_80;
  undefined8 uStack_78;
  undefined8 local_70;
  long local_68;
  
  if (*(byte *)(param_2 + 0x117) >> 2 != 0) {
                    /* WARNING: Subroutine does not return */
    FUN_001150e0(s_integer_overflow_005bb5bd);
  }
  puVar1 = param_3 + 0xc0;
  uVar20 = param_3[0xc2];
  uVar2 = *(undefined1 *)(param_2 + 0x104);
  uVar17 = *(ushort *)(param_2 + 0x108);
  bVar3 = *(byte *)(param_2 + 0x10b);
  bVar4 = *(byte *)(param_2 + 0x10a);
  uVar19 = *(ushort *)(param_2 + 0x10c);
  bVar5 = *(byte *)(param_2 + 0x10f);
  bVar6 = *(byte *)(param_2 + 0x10e);
  uVar28 = (ulong)bVar4 << 0x10 | (ulong)bVar3 << 0x18 | (ulong)uVar17 |
           (ulong)((uint)bVar6 << 0x10 | (uint)bVar5 << 0x18 | (uint)uVar19) << 0x20;
  uVar27 = ((ulong)*(byte *)(param_2 + 0x112) << 0x10 | (ulong)*(byte *)(param_2 + 0x113) << 0x18 |
            (ulong)*(ushort *)(param_2 + 0x110) |
           (ulong)((uint)*(byte *)(param_2 + 0x116) << 0x10 |
                   (uint)*(byte *)(param_2 + 0x117) << 0x18 | (uint)*(ushort *)(param_2 + 0x114)) <<
           0x20) * 0x40;
  if (uVar27 < (ulong)param_1[1]) {
    lVar29 = uVar27 + *param_1;
  }
  else {
    lVar29 = 0;
  }
  uVar7 = *(undefined1 *)(param_2 + 0x102);
  uVar8 = *(undefined1 *)(param_2 + 0x106);
  uVar21 = param_3[0xc1];
  uVar22 = param_3[0xc3];
  uVar9 = *(undefined1 *)(param_2 + 0x101);
  uVar10 = *(undefined1 *)(param_2 + 0x100);
  uVar11 = *(undefined1 *)(param_2 + 0x103);
  uVar12 = *(undefined1 *)(param_2 + 0x105);
  uVar13 = *(undefined1 *)(param_2 + 0x107);
  uVar18 = param_3[0xc0];
  bVar14 = *(byte *)((long)param_3 + 0x183);
  uVar15 = *(undefined1 *)((long)param_3 + 0x185);
  bVar16 = *(byte *)((long)param_3 + 0x187);
  iVar25 = thunk_FUN_00114e50(param_2,s___CAPABILITY_ONLY___005bb7b6,0x100);
  if (iVar25 != 0) {
    local_70 = 0;
    local_68 = 0;
    local_90[0] = 0x11;
    thunk_FUN_00114330((ulong)local_90 | 1,0xf);
    uStack_78 = 9;
    local_80 = uVar28;
    auVar30 = FUN_00034a2c();
    cVar24 = (**(code **)(auVar30._8_8_ + 0x30))(auVar30._0_8_,0x1a08,local_90,&local_70,0,0);
    if (cVar24 != '\0') {
      return 0;
    }
    FUN_000510e4(lVar29,local_70,local_68,uVar28);
    if (local_68 == 0) {
                    /* WARNING: Subroutine does not return */
      FUN_00054354();
    }
    (**(code **)(local_68 + 8))(local_70,local_90);
    lVar29 = local_88;
  }
  puVar26 = param_3 + ((ulong)(byte)uVar21 << 0x10 | (ulong)bVar14 << 0x18 | (ulong)uVar18 |
                      (ulong)((uint)(byte)uVar22 << 0x10 | (uint)bVar16 << 0x18 |
                             (uint)CONCAT11(uVar15,(char)uVar20)) << 0x20) * 0xc;
  if (((param_3 <= puVar26) && (puVar26 + 0xc <= puVar1)) && (puVar26 <= puVar26 + 0xc)) {
    *(char *)((long)puVar26 + 0x15) = (char)((ulong)lVar29 >> 0x28);
    *(char *)(puVar26 + 8) = (char)lVar29;
    *(char *)((long)puVar26 + 0x13) = (char)((ulong)lVar29 >> 0x18);
    *(char *)(puVar26 + 9) = (char)((ulong)lVar29 >> 0x10);
    *(char *)((long)puVar26 + 0x11) = (char)((ulong)lVar29 >> 8);
    *(char *)(puVar26 + 10) = (char)((ulong)lVar29 >> 0x20);
    *(char *)((long)puVar26 + 0x17) = (char)((ulong)lVar29 >> 0x38);
    *(char *)(puVar26 + 0xb) = (char)((ulong)lVar29 >> 0x30);
    *(char *)((long)puVar26 + 0xd) = (char)(uVar19 >> 8);
    *(char *)(puVar26 + 4) = (char)uVar17;
    *(byte *)((long)puVar26 + 0xb) = bVar3;
    *(byte *)(puVar26 + 5) = bVar4;
    *(char *)((long)puVar26 + 9) = (char)(uVar17 >> 8);
    *(char *)(puVar26 + 6) = (char)uVar19;
    *(byte *)((long)puVar26 + 0xf) = bVar5;
    *(byte *)(puVar26 + 7) = bVar6;
    *(undefined1 *)puVar26 = uVar10;
    *(undefined1 *)((long)puVar26 + 5) = uVar12;
    *(undefined1 *)((long)puVar26 + 3) = uVar11;
    *(undefined1 *)(puVar26 + 1) = uVar7;
    *(undefined1 *)((long)puVar26 + 1) = uVar9;
    *(undefined1 *)(puVar26 + 2) = uVar2;
    *(undefined1 *)((long)puVar26 + 7) = uVar13;
    *(undefined1 *)(puVar26 + 3) = uVar8;
    lVar29 = ((ulong)(byte)param_3[0xc1] << 0x10 | (ulong)*(byte *)((long)param_3 + 0x183) << 0x18 |
              (ulong)*puVar1 |
             (ulong)((uint)(byte)param_3[0xc3] << 0x10 |
                     (uint)*(byte *)((long)param_3 + 0x187) << 0x18 | (uint)param_3[0xc2]) << 0x20)
             + 1;
    *(char *)puVar1 = (char)lVar29;
    *(byte *)(param_3 + 0xc3) = (byte)((ulong)lVar29 >> 0x30);
    *(char *)((long)param_3 + 0x187) = (char)((ulong)lVar29 >> 0x38);
    *(char *)(param_3 + 0xc2) = (char)((ulong)lVar29 >> 0x20);
    *(char *)((long)param_3 + 0x185) = (char)((ulong)lVar29 >> 0x28);
    *(byte *)(param_3 + 0xc1) = (byte)((ulong)lVar29 >> 0x10);
    *(char *)((long)param_3 + 0x183) = (char)((ulong)lVar29 >> 0x18);
    *(char *)((long)param_3 + 0x181) = (char)((ulong)lVar29 >> 8);
    return 1;
  }
                    /* WARNING: Does not return */
  pcVar23 = (code *)SoftwareBreakpoint(0x5519,0x510d4);
  (*pcVar23)();
}

