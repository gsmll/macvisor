
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

long FUN_00013cfc(void)

{
  long *plVar1;
  long *plVar2;
  code *pcVar3;
  long lVar4;
  long lVar5;
  char *pcVar6;
  ulong uVar7;
  ulong uVar8;
  
  lVar4 = FUN_00013be4();
  if (lVar4 == 0) {
    lVar5 = FUN_00060524();
    lVar4 = 0x6ae1d0;
    if (_DAT_006ae1c0 != lVar5) {
      if (_DAT_006ae1c0 == 0) {
        thunk_FUN_00114330(&DAT_006ae1c8,0xa68);
        lVar4 = 0x6ae1d0;
        _DAT_006ae1c0 = lVar5;
      }
      else {
        lVar4 = _DAT_006ae1c8;
        if ((_DAT_006ae1c8 == lVar5) || (lVar4 = lVar5, _DAT_006ae1c8 == 0)) {
          _DAT_006ae1c8 = lVar4;
          lVar4 = 0x6ae700;
        }
        else {
          lVar4 = FUN_00013ea8();
        }
      }
    }
    uVar8 = _DAT_006ae1b0;
    if (0x1f < _DAT_006ae1b0) {
                    /* WARNING: Subroutine does not return */
      FUN_00115424(s_key_<__XRT__THREAD_TSS_MAX_KEYS_005ab392,
                   s__AppleInternal_Library_BuildRoot_005ab177,s_xrt_thread_tss_set_005ab3b2,0x1f0);
    }
    lVar5 = FUN_00063a50();
    plVar1 = (long *)tpidr_el0;
    if (plVar1[0x1f] != 0) {
      pcVar6 = s_setting_key__lu_while_destructor_005ab3c5;
LAB_00013e68:
                    /* WARNING: Subroutine does not return */
      FUN_0005b190(0,pcVar6);
    }
    plVar2 = plVar1 + (uVar8 - 1);
    if ((plVar2 < plVar1 || plVar1 + 0x1f < plVar2 + 1) || plVar2 + 1 < plVar2) {
                    /* WARNING: Does not return */
      pcVar3 = (code *)SoftwareBreakpoint(0x5519,0x13e84);
      (*pcVar3)();
    }
    if (*plVar2 != lVar4) {
      if ((*plVar2 == 0) &&
         (plVar1 = (long *)(lVar5 + (uVar8 - 1) * 8 + 0x1f8), lVar5 = *plVar1, *plVar1 = lVar5 + 1,
         lVar5 == -1)) {
        pcVar6 = s_setting_key__lu_which_is_deleted_005ab3ef;
        goto LAB_00013e68;
      }
      *plVar2 = lVar4;
    }
  }
  uVar7 = *(ulong *)(lVar4 + 0x528);
  uVar8 = (~uVar7 & 0xaaaaaaaaaaaaaaaa) >> 1 | (~uVar7 & 0x5555555555555555) << 1;
  uVar8 = (uVar8 & 0xcccccccccccccccc) >> 2 | (uVar8 & 0x3333333333333333) << 2;
  uVar8 = (uVar8 & 0xf0f0f0f0f0f0f0f0) >> 4 | (uVar8 & 0xf0f0f0f0f0f0f0f) << 4;
  uVar8 = (uVar8 & 0xff00ff00ff00ff00) >> 8 | (uVar8 & 0xff00ff00ff00ff) << 8;
  uVar8 = (uVar8 & 0xffff0000ffff0000) >> 0x10 | (uVar8 & 0xffff0000ffff) << 0x10;
  uVar8 = LZCOUNT(uVar8 >> 0x20 | uVar8 << 0x20);
  if (uVar7 != 0xffffffffffffffff && uVar8 < 3) {
    *(ulong *)(lVar4 + 0x528) = uVar7 | (uint)(1 << (ulong)((uint)uVar8 & 0x1f));
    return lVar4 + uVar8 * 0x1b8;
  }
  FUN_00118b28(s_TB_FATAL__no_available_per_threa_005ab34c);
                    /* WARNING: Does not return */
  pcVar3 = (code *)SoftwareBreakpoint(1,0x13ea8);
  (*pcVar3)();
}

