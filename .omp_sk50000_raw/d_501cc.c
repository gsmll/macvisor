
void FUN_000501cc(int param_1,int param_2)

{
  ulong uVar1;
  code *pcVar2;
  long *plVar3;
  ulong uVar4;
  ushort *puVar5;
  uint uVar6;
  ulong uVar7;
  ulong uVar8;
  ulong local_80 [2];
  undefined1 local_70 [16];
  
  plVar3 = (long *)FUN_0005ba14();
  uVar4 = FUN_0004ed48();
  if ((uVar4 != 0) && (uVar4 + 8 < uVar4)) {
LAB_00050440:
                    /* WARNING: Does not return */
    pcVar2 = (code *)SoftwareBreakpoint(0x5519,0x50444);
    (*pcVar2)();
  }
  local_70 = FUN_0004ed84();
  do {
    if (plVar3 == (long *)0x0) {
      return;
    }
    if (*(char *)(plVar3 + 1) < '\0') {
      uVar7 = plVar3[7];
      local_80[1] = 0;
      local_80[0] = uVar4;
      puVar5 = (ushort *)FUN_0004eb4c(local_80);
      if (puVar5 != (ushort *)0x0) {
        uVar1 = uVar7 + 0x20;
        do {
          if (puVar5 + 6 < puVar5) goto LAB_00050440;
          uVar8 = (ulong)(byte)puVar5[3] << 0x10 | (ulong)*(byte *)((long)puVar5 + 7) << 0x18 |
                  (ulong)puVar5[2] |
                  (ulong)((uint)(byte)puVar5[5] << 0x10 |
                          (uint)*(byte *)((long)puVar5 + 0xb) << 0x18 | (uint)puVar5[4]) << 0x20;
          uVar6 = (uint)(byte)puVar5[1] << 0x10 | (uint)*(byte *)((long)puVar5 + 3) << 0x18 |
                  (uint)*puVar5;
          if ((param_2 != 0) && (uVar6 == 0)) {
            if (uVar1 < uVar7) goto LAB_00050440;
            FUN_0004fed0(uVar4,puVar5,local_70,uVar7,plVar3[4],s___DATA_005bb23b);
            if (uVar8 < ((ulong)(byte)puVar5[3] << 0x10 | (ulong)*(byte *)((long)puVar5 + 7) << 0x18
                         | (ulong)puVar5[2] |
                        (ulong)((uint)(byte)puVar5[5] << 0x10 |
                                (uint)*(byte *)((long)puVar5 + 0xb) << 0x18 | (uint)puVar5[4]) <<
                        0x20)) goto LAB_00050440;
            uVar6 = (uint)(byte)puVar5[1] << 0x10 | (uint)*(byte *)((long)puVar5 + 3) << 0x18 |
                    (uint)*puVar5;
          }
          if (uVar6 != 0) {
            if (param_1 != 0) {
              if (uVar1 < uVar7) goto LAB_00050440;
              FUN_0004fed0(uVar4,puVar5,local_70,uVar7,plVar3[4],s___PDATA_005bb7ae);
            }
            if ((uVar8 < ((ulong)(byte)puVar5[3] << 0x10 |
                          (ulong)*(byte *)((long)puVar5 + 7) << 0x18 | (ulong)puVar5[2] |
                         (ulong)((uint)(byte)puVar5[5] << 0x10 |
                                 (uint)*(byte *)((long)puVar5 + 0xb) << 0x18 | (uint)puVar5[4]) <<
                         0x20)) || (uVar1 < uVar7)) goto LAB_00050440;
            FUN_0004fed0(uVar4,puVar5,local_70,uVar7,plVar3[4],s___DATA_005bb23b);
          }
          puVar5 = (ushort *)FUN_0004eb4c(local_80);
        } while (puVar5 != (ushort *)0x0);
      }
    }
    plVar3 = (long *)*plVar3;
  } while( true );
}

