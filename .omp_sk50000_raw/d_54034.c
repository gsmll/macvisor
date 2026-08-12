
bool FUN_00054034(int param_1)

{
  undefined4 uVar1;
  bool bVar2;
  undefined4 *puVar3;
  undefined4 uVar4;
  
  uVar4 = 0x2d;
  if (param_1 != 5) {
    uVar4 = 0x16;
  }
  uVar1 = 0;
  if (param_1 != 0) {
    uVar1 = uVar4;
  }
  bVar2 = 1 < param_1 - 2U;
  uVar4 = 0xc;
  if (bVar2) {
    uVar4 = uVar1;
  }
  puVar3 = (undefined4 *)thunk_FUN_0006037c();
  *puVar3 = uVar4;
  return bVar2 && param_1 == 0;
}

