/* sk_slice_06_frag_opdispatch.c — VAS op-dispatch wrappers (0x2ee90-0x2f780). */

/* FUN_0002ee90 @ 0x0002ee90  (est. sk_vas_op_0)
 * Ghidra: void FUN_0002ee90(long,undefined8,undefined8,undefined8,long)
 * Reserves a VAS op slot tagged 0x100000012, runs the out-of-slice VAS helper
 * FUN_0002e7c4 with (slots, vas+0x40, vas+0x48, a2, a3), packs the result code
 * into the slot and calls the completion callback at param_5+0x10.
 * Confidence: medium */
static void sk_vas_op_0(uint64_t vas, uint64_t a2, uint64_t a3, uint64_t a4, void *cb)
{
    extern uint64_t sk_vas_op_call(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t); /* FUN_0002e7c4 */
    sk_vas_slots_t *slots = sk_vas_slots(vas);
    uint64_t *slot = sk_vas_slot_reserve(slots);
    sk_vas_res_t res = {0};
    if (slot) {
        slot[0] = 0x100000012;
        slot[1] = a2;
        slot[2] = a3;
        slot[3] = slot[4] = slot[5] = 0;
    }
    sk_vm_lock_acquire();
    uint64_t code = sk_vas_op_call((uint64_t)slots, *(uint64_t *)(vas + 0x40),
                                   *(uint64_t *)(vas + 0x48), a2, a3);
    sk_vm_lock_release();
    if (!slot) {
        if ((code & 0xff) == 0) { sk_vas_res_clear(&res); }
        else {
            sk_vas_check_result(code);
            slot_res_store(slot, code);
            sk_vas_res_clear(&res);
        }
    } else {
        if ((code & 0xff) == 0) {
            *(uint8_t *)((char *)slot + 4) = 0; slot[4] = slot[5] = 0;
            sk_vas_res_clear(&res);
        } else {
            sk_vas_check_result(code);
            slot_res_store(slot, code);
            sk_vas_res_set(&res, (uint32_t)code & 0xffff00ff);
        }
    }
    sk_vas_done(cb, 0, *(uint32_t *)&res);
}

/* FUN_0002f09c @ 0x0002f09c  (est. sk_vas_op_1)
 * Ghidra: void FUN_0002f09c(long,long)
 * Reserves a 32-bit-tagged slot (tag 0xd), runs the backend +0x20 vtable method
 * (no args), packs the result and calls the completion callback at param_2+0x10.
 * Confidence: medium */
static void sk_vas_op_1(uint64_t vas, void *cb)
{
    sk_vas_slots_t *slots = sk_vas_slots(vas);
    uint64_t *slot = sk_vas_slot_reserve(slots);
    sk_vas_res_t res = {0};
    if (slot) {
        *(uint32_t *)slot = 0xd;
        *(uint8_t *)((char *)slot + 4) = 1;
        *(uint64_t *)((char *)slot + 0xd) = 0;
        *(uint64_t *)((char *)slot + 5) = 0;
        *(uint64_t *)((char *)slot + 0x1d) = 0;
        *(uint64_t *)((char *)slot + 0x15) = 0;
        *(uint64_t *)(slot + 10) = 0;
        *(uint64_t *)(slot + 8) = 0;
    }
    sk_vm_lock_acquire();
    uint64_t (*op)(void) = *(uint64_t (**)(void))(*(uint64_t *)(*(uint64_t *)(vas + 0x38) + 0x20) + 0x10);
    uint64_t code = op();
    sk_vm_lock_release();
    if (!slot) {
        if ((code & 0xff) == 0) { sk_vas_res_clear(&res); }
        else { sk_vas_check_result(code); slot_res_store(slot, code); sk_vas_res_clear(&res); }
    } else {
        if ((code & 0xff) == 0) {
            *(uint8_t *)(slot + 1) = 0; slot[8] = slot[10] = 0;
            sk_vas_res_clear(&res);
        } else { sk_vas_check_result(code); slot_res_store(slot, code); sk_vas_res_set(&res, (uint32_t)code & 0xffff00ff); }
    }
    sk_vas_done(cb, 0, *(uint32_t *)&res);
}

/* FUN_0002f240 @ 0x0002f240  (est. sk_vas_op_2)
 * Ghidra: void FUN_0002f240(long,undefined8,undefined8,undefined8,long)
 * Reserves a slot tagged 0x10000000e, runs the backend +0x28 vtable method with
 * (a2,a3,a4), packs the result, calls the completion callback.
 * Confidence: medium */
static void sk_vas_op_2(uint64_t vas, uint64_t a2, uint64_t a3, uint64_t a4, void *cb)
{
    sk_vas_slots_t *slots = sk_vas_slots(vas);
    uint64_t *slot = sk_vas_slot_reserve(slots);
    sk_vas_res_t res = {0};
    if (slot) {
        slot[0] = 0x10000000e; slot[1] = a2; slot[2] = slot[3] = slot[4] = slot[5] = 0;
    }
    sk_vm_lock_acquire();
    uint64_t obj = *(uint64_t *)(*(uint64_t *)(vas + 0x38) + 0x28);
    uint64_t (*op)(uint64_t, uint64_t, uint64_t, uint64_t) = *(uint64_t (**)(uint64_t, uint64_t, uint64_t, uint64_t))(obj + 0x10);
    uint64_t code = op(obj, a2, a3, a4);
    sk_vm_lock_release();
    if (!slot) {
        if ((code & 0xff) == 0) { sk_vas_res_clear(&res); }
        else { sk_vas_check_result(code); slot_res_store(slot, code); sk_vas_res_clear(&res); }
    } else {
        if ((code & 0xff) == 0) {
            *(uint8_t *)((char *)slot + 4) = 0; slot[4] = slot[5] = 0;
            sk_vas_res_clear(&res);
        } else { sk_vas_check_result(code); slot_res_store(slot, code); sk_vas_res_set(&res, (uint32_t)code & 0xffff00ff); }
    }
    sk_vas_done(cb, 0, *(uint32_t *)&res);
}

/* FUN_0002f3fc @ 0x0002f3fc  (est. sk_vas_op_3)
 * Ghidra: void FUN_0002f3fc(long,undefined8,undefined8,long)
 * Reserves a slot tagged 0x10000000f, runs the backend +0x30 vtable method with
 * (a2,a3), packs the result, calls the completion callback.
 * Confidence: medium */
static void sk_vas_op_3(uint64_t vas, uint64_t a2, uint64_t a3, void *cb)
{
    sk_vas_slots_t *slots = sk_vas_slots(vas);
    uint64_t *slot = sk_vas_slot_reserve(slots);
    sk_vas_res_t res = {0};
    if (slot) {
        slot[0] = 0x10000000f; slot[1] = a2; slot[2] = slot[3] = slot[4] = slot[5] = 0;
    }
    sk_vm_lock_acquire();
    uint64_t obj = *(uint64_t *)(*(uint64_t *)(vas + 0x38) + 0x30);
    uint64_t (*op)(uint64_t, uint64_t, uint64_t) = *(uint64_t (**)(uint64_t, uint64_t, uint64_t))(obj + 0x10);
    uint64_t code = op(obj, a2, a3);
    sk_vm_lock_release();
    if (!slot) {
        if ((code & 0xff) == 0) { sk_vas_res_clear(&res); }
        else { sk_vas_check_result(code); slot_res_store(slot, code); sk_vas_res_clear(&res); }
    } else {
        if ((code & 0xff) == 0) {
            *(uint8_t *)((char *)slot + 4) = 0; slot[4] = slot[5] = 0;
            sk_vas_res_clear(&res);
        } else { sk_vas_check_result(code); slot_res_store(slot, code); sk_vas_res_set(&res, (uint32_t)code & 0xffff00ff); }
    }
    sk_vas_done(cb, 0, *(uint32_t *)&res);
}

/* FUN_0002f5b0 @ 0x0002f5b0  (est. sk_vas_op_4)
 * Ghidra: void FUN_0002f5b0(long,undefined8,undefined8,ulong,undefined8,long)
 * Reserves a slot tagged 0x100000010, runs the backend +0x38 vtable method with
 * (a2,a3,a4,a5), packs the result, calls the completion callback.
 * Confidence: medium */
static void sk_vas_op_4(uint64_t vas, uint64_t a2, uint64_t a3, uint64_t a4, uint64_t a5, void *cb)
{
    sk_vas_slots_t *slots = sk_vas_slots(vas);
    uint64_t *slot = sk_vas_slot_reserve(slots);
    sk_vas_res_t res = {0};
    if (slot) {
        slot[0] = 0x100000010; slot[1] = a2; slot[2] = a3; slot[3] = a4 & 0xffffffff;
        slot[4] = slot[5] = 0;
    }
    sk_vm_lock_acquire();
    uint64_t obj = *(uint64_t *)(*(uint64_t *)(vas + 0x38) + 0x38);
    uint64_t (*op)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t) =
        *(uint64_t (**)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t))(obj + 0x10);
    uint64_t code = op(obj, a2, a3, a4, a5);
    sk_vm_lock_release();
    if (!slot) {
        if ((code & 0xff) == 0) { sk_vas_res_clear(&res); }
        else { sk_vas_check_result(code); slot_res_store(slot, code); sk_vas_res_clear(&res); }
    } else {
        if ((code & 0xff) == 0) {
            *(uint8_t *)((char *)slot + 4) = 0; slot[4] = slot[5] = 0;
            sk_vas_res_clear(&res);
        } else { sk_vas_check_result(code); slot_res_store(slot, code); sk_vas_res_set(&res, (uint32_t)code & 0xffff00ff); }
    }
    sk_vas_done(cb, 0, *(uint32_t *)&res);
}

/* FUN_0002f780 @ 0x0002f780  (est. sk_vas_op_5)
 * Ghidra: void FUN_0002f780(long,undefined8,undefined8,undefined8,undefined8,long)
 * Reserves a slot tagged 0x100000011, runs the backend +0x40 vtable method with
 * (a2,a3,a4,a5), packs the result, calls the completion callback.
 * Confidence: medium */
static void sk_vas_op_5(uint64_t vas, uint64_t a2, uint64_t a3, uint64_t a4, uint64_t a5, void *cb)
{
    sk_vas_slots_t *slots = sk_vas_slots(vas);
    uint64_t *slot = sk_vas_slot_reserve(slots);
    sk_vas_res_t res = {0};
    if (slot) {
        slot[0] = 0x100000011; slot[1] = a2; slot[2] = a4; slot[3] = a5;
        slot[4] = slot[5] = 0;
    }
    sk_vm_lock_acquire();
    uint64_t obj = *(uint64_t *)(*(uint64_t *)(vas + 0x38) + 0x40);
    uint64_t (*op)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t) =
        *(uint64_t (**)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t))(obj + 0x10);
    uint64_t code = op(obj, a2, a3, a4, a5);
    sk_vm_lock_release();
    if (!slot) {
        if ((code & 0xff) == 0) { sk_vas_res_clear(&res); }
        else { sk_vas_check_result(code); slot_res_store(slot, code); sk_vas_res_clear(&res); }
    } else {
        if ((code & 0xff) == 0) {
            *(uint8_t *)((char *)slot + 4) = 0; slot[4] = slot[5] = 0;
            sk_vas_res_clear(&res);
        } else { sk_vas_check_result(code); slot_res_store(slot, code); sk_vas_res_set(&res, (uint32_t)code & 0xffff00ff); }
    }
    sk_vas_done(cb, 0, *(uint32_t *)&res);
}
