
void FUN_00051488(long *param_1,long param_2,undefined1 *param_3)

{
  undefined1 uVar1;
  undefined1 uVar2;
  undefined1 uVar3;
  undefined1 uVar4;
  undefined1 uVar5;
  undefined1 uVar6;
  undefined1 uVar7;
  undefined1 uVar8;
  undefined2 uVar9;
  undefined2 uVar10;
  undefined2 uVar11;
  undefined2 uVar12;
  ulong uVar13;
  long lVar14;
  long lVar15;
  
  if (*(byte *)(param_2 + 0x107) >> 2 != 0) {
                    /* WARNING: Subroutine does not return */
    FUN_001150e0(s_integer_overflow_005bb5bd);
  }
  uVar13 = ((ulong)*(byte *)(param_2 + 0x102) << 0x10 | (ulong)*(byte *)(param_2 + 0x103) << 0x18 |
            (ulong)*(ushort *)(param_2 + 0x100) |
           (ulong)((uint)*(byte *)(param_2 + 0x106) << 0x10 |
                   (uint)*(byte *)(param_2 + 0x107) << 0x18 | (uint)*(ushort *)(param_2 + 0x104)) <<
           0x20) * 0x40;
  if (uVar13 < (ulong)param_1[1]) {
    lVar14 = uVar13 + *param_1;
  }
  else {
    lVar14 = 0;
  }
  uVar13 = (ulong)*(byte *)(param_2 + 0x10a) << 0x10 | (ulong)*(byte *)(param_2 + 0x10b) << 0x18 |
           (ulong)*(ushort *)(param_2 + 0x108) |
           (ulong)((uint)*(byte *)(param_2 + 0x10e) << 0x10 |
                   (uint)*(byte *)(param_2 + 0x10f) << 0x18 | (uint)*(ushort *)(param_2 + 0x10c)) <<
           0x20;
  if (uVar13 != 0) {
    if (*(byte *)(param_2 + 0x10f) >> 2 != 0) {
                    /* WARNING: Subroutine does not return */
      FUN_001150e0(s_integer_overflow_005bb5bd);
    }
    uVar13 = uVar13 * 0x40;
    if (uVar13 < (ulong)param_1[1]) {
      lVar15 = uVar13 + *param_1;
      goto LAB_00051578;
    }
  }
  lVar15 = 0;
LAB_00051578:
  *param_3 = (char)lVar14;
  param_3[5] = (char)((ulong)lVar14 >> 0x28);
  param_3[3] = (char)((ulong)lVar14 >> 0x18);
  param_3[2] = (char)((ulong)lVar14 >> 0x10);
  param_3[1] = (char)((ulong)lVar14 >> 8);
  param_3[4] = (char)((ulong)lVar14 >> 0x20);
  param_3[7] = (char)((ulong)lVar14 >> 0x38);
  param_3[6] = (char)((ulong)lVar14 >> 0x30);
  param_3[0xed] = (char)((ulong)lVar15 >> 0x28);
  param_3[0xe8] = (char)lVar15;
  param_3[0xeb] = (char)((ulong)lVar15 >> 0x18);
  param_3[0xea] = (char)((ulong)lVar15 >> 0x10);
  param_3[0xe9] = (char)((ulong)lVar15 >> 8);
  param_3[0xec] = (char)((ulong)lVar15 >> 0x20);
  param_3[0xef] = (char)((ulong)lVar15 >> 0x38);
  param_3[0xee] = (char)((ulong)lVar15 >> 0x30);
  uVar9 = *(undefined2 *)(param_2 + 0x110);
  uVar1 = *(undefined1 *)(param_2 + 0x113);
  uVar2 = *(undefined1 *)(param_2 + 0x112);
  uVar10 = *(undefined2 *)(param_2 + 0x114);
  uVar3 = *(undefined1 *)(param_2 + 0x117);
  uVar4 = *(undefined1 *)(param_2 + 0x116);
  uVar11 = *(undefined2 *)(param_2 + 0x118);
  uVar5 = *(undefined1 *)(param_2 + 0x11b);
  uVar6 = *(undefined1 *)(param_2 + 0x11a);
  uVar12 = *(undefined2 *)(param_2 + 0x11c);
  uVar7 = *(undefined1 *)(param_2 + 0x11f);
  uVar8 = *(undefined1 *)(param_2 + 0x11e);
  param_3[0xf0] = (char)uVar9;
  param_3[0xfd] = (char)((ushort)uVar12 >> 8);
  param_3[0xf9] = (char)((ushort)uVar11 >> 8);
  param_3[0xf5] = (char)((ushort)uVar10 >> 8);
  param_3[0xf3] = uVar1;
  param_3[0xf2] = uVar2;
  param_3[0xf1] = (char)((ushort)uVar9 >> 8);
  param_3[0xf8] = (char)uVar11;
  param_3[0xfb] = uVar5;
  param_3[0xf4] = (char)uVar10;
  param_3[0xfa] = uVar6;
  param_3[0xf7] = uVar3;
  param_3[0xf6] = uVar4;
  param_3[0xfc] = (char)uVar12;
  param_3[0xff] = uVar7;
  param_3[0xfe] = uVar8;
  return;
}

