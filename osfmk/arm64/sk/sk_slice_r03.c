/* 003ccd3c @ 0x003ccd3c   (est. cL4_ipc_emit_mb)
 * Ghidra: void FUN_003ccd3c(int *result, long tcb, void *msg, int depth)
 * Decode the single message word in `msg` (kind-1/5 check) and emit it as a
 * tagged IPC message-register record with tag "MB"; on parse error leave
 * the result word set, else clear it. Confidence: medium. Notes:  */
void cL4_ipc_emit_mb(int *result, unsigned long tcb, unsigned long msg, unsigned long depth)
{
    cL4_msg_one(result, tcb, (long*)msg, depth + 1);
    if (*result == 0) {
        cL4_mr_emit_tag(tcb + 0x2140, &"MB", 2, *(unsigned long *)(tcb + 0x2150));
        *result = 0; result[2] = 0; result[3] = 0; result[4] = 0;
    }
}

/* 003ccd98 @ 0x003ccd98   (est. cL4_ipc_emit_mf)
 * Ghidra: void FUN_003ccd98(int *result, long tcb, void *msg, int depth)
 * Decode the single message word in `msg` (kind-1/5 check) and emit it as a
 * tagged IPC message-register record with tag "MF"; on parse error leave
 * the result word set, else clear it. Confidence: medium. Notes:  */
void cL4_ipc_emit_mf(int *result, unsigned long tcb, unsigned long msg, unsigned long depth)
{
    cL4_msg_one(result, tcb, (long*)msg, depth + 1);
    if (*result == 0) {
        cL4_mr_emit_tag(tcb + 0x2140, &"MF", 2, *(unsigned long *)(tcb + 0x2150));
        *result = 0; result[2] = 0; result[3] = 0; result[4] = 0;
    }
}

/* 003ccdf4 @ 0x003ccdf4   (est. cL4_ipc_emit_ma)
 * Ghidra: void FUN_003ccdf4(int *result, long tcb, void *msg, int depth)
 * Decode the single message word in `msg` (kind-1/5 check) and emit it as a
 * tagged IPC message-register record with tag "MA"; on parse error leave
 * the result word set, else clear it. Confidence: medium. Notes:  */
void cL4_ipc_emit_ma(int *result, unsigned long tcb, unsigned long msg, unsigned long depth)
{
    cL4_msg_one(result, tcb, (long*)msg, depth + 1);
    if (*result == 0) {
        cL4_mr_emit_tag(tcb + 0x2140, &"MA", 2, *(unsigned long *)(tcb + 0x2150));
        *result = 0; result[2] = 0; result[3] = 0; result[4] = 0;
    }
}

/* 003cce50 @ 0x003cce50   (est. cL4_ipc_emit_mc)
 * Ghidra: void FUN_003cce50(int *result, long tcb, void *msg, int depth)
 * Decode the single message word in `msg` (kind-1/5 check) and emit it as a
 * tagged IPC message-register record with tag "MC"; on parse error leave
 * the result word set, else clear it. Confidence: medium. Notes:  */
void cL4_ipc_emit_mc(int *result, unsigned long tcb, unsigned long msg, unsigned long depth)
{
    cL4_msg_one(result, tcb, (long*)msg, depth + 1);
    if (*result == 0) {
        cL4_mr_emit_tag(tcb + 0x2140, &"MC", 2, *(unsigned long *)(tcb + 0x2150));
        *result = 0; result[2] = 0; result[3] = 0; result[4] = 0;
    }
}

/* 003ccf08 @ 0x003ccf08   (est. cL4_ipc_emit_tc)
 * Ghidra: void FUN_003ccf08(int *result, long tcb, void *msg, int depth)
 * Decode the single message word in `msg` (kind-1/5 check) and emit it as a
 * tagged IPC message-register record with tag "Tc"; on parse error leave
 * the result word set, else clear it. Confidence: medium. Notes:  */
void cL4_ipc_emit_tc(int *result, unsigned long tcb, unsigned long msg, unsigned long depth)
{
    cL4_msg_one(result, tcb, (long*)msg, depth + 1);
    if (*result == 0) {
        cL4_mr_emit_tag(tcb + 0x2140, &"Tc", 2, *(unsigned long *)(tcb + 0x2150));
        *result = 0; result[2] = 0; result[3] = 0; result[4] = 0;
    }
}

/* 003ccfe0 @ 0x003ccfe0   (est. cL4_ipc_emit_tj)
 * Ghidra: void FUN_003ccfe0(int *result, long tcb, void *msg, int depth)
 * Decode the single message word in `msg` (kind-1/5 check) and emit it as a
 * tagged IPC message-register record with tag "Tj"; on parse error leave
 * the result word set, else clear it. Confidence: medium. Notes:  */
void cL4_ipc_emit_tj(int *result, unsigned long tcb, unsigned long msg, unsigned long depth)
{
    cL4_msg_one(result, tcb, (long*)msg, depth + 1);
    if (*result == 0) {
        cL4_mr_emit_tag(tcb + 0x2140, &"Tj", 2, *(unsigned long *)(tcb + 0x2150));
        *result = 0; result[2] = 0; result[3] = 0; result[4] = 0;
    }
}

/* 003cd03c @ 0x003cd03c   (est. cL4_ipc_emit_tq)
 * Ghidra: void FUN_003cd03c(int *result, long tcb, void *msg, int depth)
 * Decode the single message word in `msg` (kind-1/5 check) and emit it as a
 * tagged IPC message-register record with tag "Tq"; on parse error leave
 * the result word set, else clear it. Confidence: medium. Notes:  */
void cL4_ipc_emit_tq(int *result, unsigned long tcb, unsigned long msg, unsigned long depth)
{
    cL4_msg_one(result, tcb, (long*)msg, depth + 1);
    if (*result == 0) {
        cL4_mr_emit_tag(tcb + 0x2140, &"Tq", 2, *(unsigned long *)(tcb + 0x2150));
        *result = 0; result[2] = 0; result[3] = 0; result[4] = 0;
    }
}

/* 003ce4f8 @ 0x003ce4f8   (est. cL4_ipc_emit_mq)
 * Ghidra: void FUN_003ce4f8(int *result, long tcb, void *msg, int depth)
 * Decode the single message word in `msg` (kind-1/5 check) and emit it as a
 * tagged IPC message-register record with tag "MQ"; on parse error leave
 * the result word set, else clear it. Confidence: medium. Notes:  */
void cL4_ipc_emit_mq(int *result, unsigned long tcb, unsigned long msg, unsigned long depth)
{
    cL4_msg_one(result, tcb, (long*)msg, depth + 1);
    if (*result == 0) {
        cL4_mr_emit_tag(tcb + 0x2140, &"MQ", 2, *(unsigned long *)(tcb + 0x2150));
        *result = 0; result[2] = 0; result[3] = 0; result[4] = 0;
    }
}

/* 003ce554 @ 0x003ce554   (est. cL4_ipc_emit_ho)
 * Ghidra: void FUN_003ce554(int *result, long tcb, void *msg, int depth)
 * Decode the single message word in `msg` (kind-1/5 check) and emit it as a
 * tagged IPC message-register record with tag "Ho"; on parse error leave
 * the result word set, else clear it. Confidence: medium. Notes:  */
void cL4_ipc_emit_ho(int *result, unsigned long tcb, unsigned long msg, unsigned long depth)
{
    cL4_msg_one(result, tcb, (long*)msg, depth + 1);
    if (*result == 0) {
        cL4_mr_emit_tag(tcb + 0x2140, &"Ho", 2, *(unsigned long *)(tcb + 0x2150));
        *result = 0; result[2] = 0; result[3] = 0; result[4] = 0;
    }
}

/* 003ce5b0 @ 0x003ce5b0   (est. cL4_ipc_emit_mg)
 * Ghidra: void FUN_003ce5b0(int *result, long tcb, void *msg, int depth)
 * Decode the single message word in `msg` (kind-1/5 check) and emit it as a
 * tagged IPC message-register record with tag "Mg"; on parse error leave
 * the result word set, else clear it. Confidence: medium. Notes:  */
void cL4_ipc_emit_mg(int *result, unsigned long tcb, unsigned long msg, unsigned long depth)
{
    cL4_msg_one(result, tcb, (long*)msg, depth + 1);
    if (*result == 0) {
        cL4_mr_emit_tag(tcb + 0x2140, &"Mg", 2, *(unsigned long *)(tcb + 0x2150));
        *result = 0; result[2] = 0; result[3] = 0; result[4] = 0;
    }
}

/* 003ce60c @ 0x003ce60c   (est. cL4_ipc_emit_mh)
 * Ghidra: void FUN_003ce60c(int *result, long tcb, void *msg, int depth)
 * Decode the single message word in `msg` (kind-1/5 check) and emit it as a
 * tagged IPC message-register record with tag "Mh"; on parse error leave
 * the result word set, else clear it. Confidence: medium. Notes:  */
void cL4_ipc_emit_mh(int *result, unsigned long tcb, unsigned long msg, unsigned long depth)
{
    cL4_msg_one(result, tcb, (long*)msg, depth + 1);
    if (*result == 0) {
        cL4_mr_emit_tag(tcb + 0x2140, &"Mh", 2, *(unsigned long *)(tcb + 0x2150));
        *result = 0; result[2] = 0; result[3] = 0; result[4] = 0;
    }
}

/* 003ce668 @ 0x003ce668   (est. cL4_ipc_emit_mj)
 * Ghidra: void FUN_003ce668(int *result, long tcb, void *msg, int depth)
 * Decode the single message word in `msg` (kind-1/5 check) and emit it as a
 * tagged IPC message-register record with tag "Mj"; on parse error leave
 * the result word set, else clear it. Confidence: medium. Notes:  */
void cL4_ipc_emit_mj(int *result, unsigned long tcb, unsigned long msg, unsigned long depth)
{
    cL4_msg_one(result, tcb, (long*)msg, depth + 1);
    if (*result == 0) {
        cL4_mr_emit_tag(tcb + 0x2140, &"Mj", 2, *(unsigned long *)(tcb + 0x2150));
        *result = 0; result[2] = 0; result[3] = 0; result[4] = 0;
    }
}

/* 003ce6c4 @ 0x003ce6c4   (est. cL4_ipc_emit_mk)
 * Ghidra: void FUN_003ce6c4(int *result, long tcb, void *msg, int depth)
 * Decode the single message word in `msg` (kind-1/5 check) and emit it as a
 * tagged IPC message-register record with tag "Mk"; on parse error leave
 * the result word set, else clear it. Confidence: medium. Notes:  */
void cL4_ipc_emit_mk(int *result, unsigned long tcb, unsigned long msg, unsigned long depth)
{
    cL4_msg_one(result, tcb, (long*)msg, depth + 1);
    if (*result == 0) {
        cL4_mr_emit_tag(tcb + 0x2140, &"Mk", 2, *(unsigned long *)(tcb + 0x2150));
        *result = 0; result[2] = 0; result[3] = 0; result[4] = 0;
    }
}

/* 003ce8e4 @ 0x003ce8e4   (est. cL4_ipc_emit_mb2)
 * Ghidra: void FUN_003ce8e4(int *result, long tcb, void *msg, int depth)
 * Decode the single message word in `msg` (kind-1/5 check) and emit it as a
 * tagged IPC message-register record with tag "Mb"; on parse error leave
 * the result word set, else clear it. Confidence: medium. Notes:  */
void cL4_ipc_emit_mb2(int *result, unsigned long tcb, unsigned long msg, unsigned long depth)
{
    cL4_msg_one(result, tcb, (long*)msg, depth + 1);
    if (*result == 0) {
        cL4_mr_emit_tag(tcb + 0x2140, &"Mb", 2, *(unsigned long *)(tcb + 0x2150));
        *result = 0; result[2] = 0; result[3] = 0; result[4] = 0;
    }
}

/* 003ce940 @ 0x003ce940   (est. cL4_ipc_emit_mk2)
 * Ghidra: void FUN_003ce940(int *result, long tcb, void *msg, int depth)
 * Decode the single message word in `msg` (kind-1/5 check) and emit it as a
 * tagged IPC message-register record with tag "MK"; on parse error leave
 * the result word set, else clear it. Confidence: medium. Notes:  */
void cL4_ipc_emit_mk2(int *result, unsigned long tcb, unsigned long msg, unsigned long depth)
{
    cL4_msg_one(result, tcb, (long*)msg, depth + 1);
    if (*result == 0) {
        cL4_mr_emit_tag(tcb + 0x2140, &"MK", 2, *(unsigned long *)(tcb + 0x2150));
        *result = 0; result[2] = 0; result[3] = 0; result[4] = 0;
    }
}

/* 003ce99c @ 0x003ce99c   (est. cL4_ipc_emit_mn)
 * Ghidra: void FUN_003ce99c(int *result, long tcb, void *msg, int depth)
 * Decode the single message word in `msg` (kind-1/5 check) and emit it as a
 * tagged IPC message-register record with tag "MN"; on parse error leave
 * the result word set, else clear it. Confidence: medium. Notes:  */
void cL4_ipc_emit_mn(int *result, unsigned long tcb, unsigned long msg, unsigned long depth)
{
    cL4_msg_one(result, tcb, (long*)msg, depth + 1);
    if (*result == 0) {
        cL4_mr_emit_tag(tcb + 0x2140, &"MN", 2, *(unsigned long *)(tcb + 0x2150));
        *result = 0; result[2] = 0; result[3] = 0; result[4] = 0;
    }
}

/* 003ce9f8 @ 0x003ce9f8   (est. cL4_ipc_emit_mj2)
 * Ghidra: void FUN_003ce9f8(int *result, long tcb, void *msg, int depth)
 * Decode the single message word in `msg` (kind-1/5 check) and emit it as a
 * tagged IPC message-register record with tag "MJ"; on parse error leave
 * the result word set, else clear it. Confidence: medium. Notes:  */
void cL4_ipc_emit_mj2(int *result, unsigned long tcb, unsigned long msg, unsigned long depth)
{
    cL4_msg_one(result, tcb, (long*)msg, depth + 1);
    if (*result == 0) {
        cL4_mr_emit_tag(tcb + 0x2140, &"MJ", 2, *(unsigned long *)(tcb + 0x2150));
        *result = 0; result[2] = 0; result[3] = 0; result[4] = 0;
    }
}

/* 003cec20 @ 0x003cec20   (est. cL4_ipc_emit_mz)
 * Ghidra: void FUN_003cec20(int *result, long tcb, void *msg, int depth)
 * Decode the single message word in `msg` (kind-1/5 check) and emit it as a
 * tagged IPC message-register record with tag "Mz"; on parse error leave
 * the result word set, else clear it. Confidence: medium. Notes:  */
void cL4_ipc_emit_mz(int *result, unsigned long tcb, unsigned long msg, unsigned long depth)
{
    cL4_msg_one(result, tcb, (long*)msg, depth + 1);
    if (*result == 0) {
        cL4_mr_emit_tag(tcb + 0x2140, &"Mz", 2, *(unsigned long *)(tcb + 0x2150));
        *result = 0; result[2] = 0; result[3] = 0; result[4] = 0;
    }
}

/* 003cf160 @ 0x003cf160   (est. cL4_ipc_emit_yk)
 * Ghidra: void FUN_003cf160(int *result, long tcb, void *msg, int depth)
 * Decode the single message word in `msg` (kind-1/5 check) and emit it as a
 * tagged IPC message-register record with tag "Yk"; on parse error leave
 * the result word set, else clear it. Confidence: medium. Notes:  */
void cL4_ipc_emit_yk(int *result, unsigned long tcb, unsigned long msg, unsigned long depth)
{
    cL4_msg_one(result, tcb, (long*)msg, depth + 1);
    if (*result == 0) {
        cL4_mr_emit_tag(tcb + 0x2140, &"Yk", 2, *(unsigned long *)(tcb + 0x2150));
        *result = 0; result[2] = 0; result[3] = 0; result[4] = 0;
    }
}

/* 003cf28c @ 0x003cf28c   (est. cL4_ipc_emit_yt)
 * Ghidra: void FUN_003cf28c(int *result, long tcb, void *msg, int depth)
 * Decode the single message word in `msg` (kind-1/5 check) and emit it as a
 * tagged IPC message-register record with tag "Yt"; on parse error leave
 * the result word set, else clear it. Confidence: medium. Notes:  */
void cL4_ipc_emit_yt(int *result, unsigned long tcb, unsigned long msg, unsigned long depth)
{
    cL4_msg_one(result, tcb, (long*)msg, depth + 1);
    if (*result == 0) {
        cL4_mr_emit_tag(tcb + 0x2140, &"Yt", 2, *(unsigned long *)(tcb + 0x2150));
        *result = 0; result[2] = 0; result[3] = 0; result[4] = 0;
    }
}

/* 003d003c @ 0x003d003c   (est. cL4_ipc_emit_yg)
 * Ghidra: void FUN_003d003c(int *result, long tcb, void *msg, int depth)
 * Decode the single message word in `msg` (kind-1/5 check) and emit it as a
 * tagged IPC message-register record with tag "Yg"; on parse error leave
 * the result word set, else clear it. Confidence: medium. Notes:  */
void cL4_ipc_emit_yg(int *result, unsigned long tcb, unsigned long msg, unsigned long depth)
{
    cL4_msg_one(result, tcb, (long*)msg, depth + 1);
    if (*result == 0) {
        cL4_mr_emit_tag(tcb + 0x2140, &"Yg", 2, *(unsigned long *)(tcb + 0x2150));
        *result = 0; result[2] = 0; result[3] = 0; result[4] = 0;
    }
}

/* 003cceac @ 0x003cceac   (est. cL4_ipc_emit_fp)
 * Ghidra: void FUN_003cceac(int *result, long tcb, void *msg, int depth)
 * Decode the argument LIST in `msg` (each word via cL4_arg_decode) and emit a
 * tagged IPC record with tag "fp" carrying 2 words; clear result on
 * success. Confidence: medium. Notes:  */
void cL4_ipc_emit_fp(int *result, unsigned long tcb, unsigned long msg, unsigned long depth)
{
    cL4_msg_args(result, tcb, (long*)msg, depth + 1);
    if (*result == 0) {
        cL4_mr_emit_tag(tcb + 0x2140, &"fp", 2, *(unsigned long *)(tcb + 0x2150));
        *result = 0; result[2] = 0; result[3] = 0; result[4] = 0;
    }
}

/* 003cd4e0 @ 0x003cd4e0   (est. cL4_ipc_emit_yk2)
 * Ghidra: void FUN_003cd4e0(int *result, long tcb, void *msg, int depth)
 * Decode the argument LIST in `msg` (each word via cL4_arg_decode) and emit a
 * tagged IPC record with tag "YK" carrying 2 words; clear result on
 * success. Confidence: medium. Notes:  */
void cL4_ipc_emit_yk2(int *result, unsigned long tcb, unsigned long msg, unsigned long depth)
{
    cL4_msg_args(result, tcb, (long*)msg, depth + 1);
    if (*result == 0) {
        cL4_mr_emit_tag(tcb + 0x2140, &"YK", 2, *(unsigned long *)(tcb + 0x2150));
        *result = 0; result[2] = 0; result[3] = 0; result[4] = 0;
    }
}

/* 003ce888 @ 0x003ce888   (est. cL4_ipc_emit_mm)
 * Ghidra: void FUN_003ce888(int *result, long tcb, void *msg, int depth)
 * Decode the argument LIST in `msg` (each word via cL4_arg_decode) and emit a
 * tagged IPC record with tag "MM" carrying 2 words; clear result on
 * success. Confidence: medium. Notes:  */
void cL4_ipc_emit_mm(int *result, unsigned long tcb, unsigned long msg, unsigned long depth)
{
    cL4_msg_args(result, tcb, (long*)msg, depth + 1);
    if (*result == 0) {
        cL4_mr_emit_tag(tcb + 0x2140, &"MM", 2, *(unsigned long *)(tcb + 0x2150));
        *result = 0; result[2] = 0; result[3] = 0; result[4] = 0;
    }
}

/* 003cea54 @ 0x003cea54   (est. cL4_ipc_emit_wz)
 * Ghidra: void FUN_003cea54(int *result, long tcb, void *msg, int depth)
 * Decode the argument LIST in `msg` (each word via cL4_arg_decode) and emit a
 * tagged IPC record with tag "WZ" carrying 2 words; clear result on
 * success. Confidence: medium. Notes:  */
void cL4_ipc_emit_wz(int *result, unsigned long tcb, unsigned long msg, unsigned long depth)
{
    cL4_msg_args(result, tcb, (long*)msg, depth + 1);
    if (*result == 0) {
        cL4_mr_emit_tag(tcb + 0x2140, &"WZ", 2, *(unsigned long *)(tcb + 0x2150));
        *result = 0; result[2] = 0; result[3] = 0; result[4] = 0;
    }
}

/* 003ceab0 @ 0x003ceab0   (est. cL4_ipc_emit_wz2)
 * Ghidra: void FUN_003ceab0(int *result, long tcb, void *msg, int depth)
 * Decode the argument LIST in `msg` (each word via cL4_arg_decode) and emit a
 * tagged IPC record with tag "Wz" carrying 2 words; clear result on
 * success. Confidence: medium. Notes:  */
void cL4_ipc_emit_wz2(int *result, unsigned long tcb, unsigned long msg, unsigned long depth)
{
    cL4_msg_args(result, tcb, (long*)msg, depth + 1);
    if (*result == 0) {
        cL4_mr_emit_tag(tcb + 0x2140, &"Wz", 2, *(unsigned long *)(tcb + 0x2150));
        *result = 0; result[2] = 0; result[3] = 0; result[4] = 0;
    }
}

/* 003cd5bc @ 0x003cd5bc   (est. cL4_ipc_emit_woy)
 * Ghidra: void FUN_003cd5bc(int *result, long tcb, void *msg, int depth)
 * Decode the argument LIST in `msg` (each word via cL4_arg_decode) and emit a
 * tagged IPC record with tag "WOy" carrying 3 words; clear result on
 * success. Confidence: medium. Notes:  */
void cL4_ipc_emit_woy(int *result, unsigned long tcb, unsigned long msg, unsigned long depth)
{
    cL4_msg_args(result, tcb, (long*)msg, depth + 1);
    if (*result == 0) {
        cL4_mr_emit_tag(tcb + 0x2140, &"WOy", 3, *(unsigned long *)(tcb + 0x2150));
        *result = 0; result[2] = 0; result[3] = 0; result[4] = 0;
    }
}

/* 003cd674 @ 0x003cd674   (est. cL4_ipc_emit_wor)
 * Ghidra: void FUN_003cd674(int *result, long tcb, void *msg, int depth)
 * Decode the argument LIST in `msg` (each word via cL4_arg_decode) and emit a
 * tagged IPC record with tag "WOr" carrying 3 words; clear result on
 * success. Confidence: medium. Notes:  */
void cL4_ipc_emit_wor(int *result, unsigned long tcb, unsigned long msg, unsigned long depth)
{
    cL4_msg_args(result, tcb, (long*)msg, depth + 1);
    if (*result == 0) {
        cL4_mr_emit_tag(tcb + 0x2140, &"WOr", 3, *(unsigned long *)(tcb + 0x2150));
        *result = 0; result[2] = 0; result[3] = 0; result[4] = 0;
    }
}

/* 003cd6d0 @ 0x003cd6d0   (est. cL4_ipc_emit_wos)
 * Ghidra: void FUN_003cd6d0(int *result, long tcb, void *msg, int depth)
 * Decode the argument LIST in `msg` (each word via cL4_arg_decode) and emit a
 * tagged IPC record with tag "WOs" carrying 3 words; clear result on
 * success. Confidence: medium. Notes:  */
void cL4_ipc_emit_wos(int *result, unsigned long tcb, unsigned long msg, unsigned long depth)
{
    cL4_msg_args(result, tcb, (long*)msg, depth + 1);
    if (*result == 0) {
        cL4_mr_emit_tag(tcb + 0x2140, &"WOs", 3, *(unsigned long *)(tcb + 0x2150));
        *result = 0; result[2] = 0; result[3] = 0; result[4] = 0;
    }
}

/* 003cd72c @ 0x003cd72c   (est. cL4_ipc_emit_wob)
 * Ghidra: void FUN_003cd72c(int *result, long tcb, void *msg, int depth)
 * Decode the argument LIST in `msg` (each word via cL4_arg_decode) and emit a
 * tagged IPC record with tag "WOb" carrying 3 words; clear result on
 * success. Confidence: medium. Notes:  */
void cL4_ipc_emit_wob(int *result, unsigned long tcb, unsigned long msg, unsigned long depth)
{
    cL4_msg_args(result, tcb, (long*)msg, depth + 1);
    if (*result == 0) {
        cL4_mr_emit_tag(tcb + 0x2140, &"WOb", 3, *(unsigned long *)(tcb + 0x2150));
        *result = 0; result[2] = 0; result[3] = 0; result[4] = 0;
    }
}

/* 003cd788 @ 0x003cd788   (est. cL4_ipc_emit_woc)
 * Ghidra: void FUN_003cd788(int *result, long tcb, void *msg, int depth)
 * Decode the argument LIST in `msg` (each word via cL4_arg_decode) and emit a
 * tagged IPC record with tag "WOc" carrying 3 words; clear result on
 * success. Confidence: medium. Notes:  */
void cL4_ipc_emit_woc(int *result, unsigned long tcb, unsigned long msg, unsigned long depth)
{
    cL4_msg_args(result, tcb, (long*)msg, depth + 1);
    if (*result == 0) {
        cL4_mr_emit_tag(tcb + 0x2140, &"WOc", 3, *(unsigned long *)(tcb + 0x2150));
        *result = 0; result[2] = 0; result[3] = 0; result[4] = 0;
    }
}

/* 003cd7e4 @ 0x003cd7e4   (est. cL4_ipc_emit_wod)
 * Ghidra: void FUN_003cd7e4(int *result, long tcb, void *msg, int depth)
 * Decode the argument LIST in `msg` (each word via cL4_arg_decode) and emit a
 * tagged IPC record with tag "WOd" carrying 3 words; clear result on
 * success. Confidence: medium. Notes:  */
void cL4_ipc_emit_wod(int *result, unsigned long tcb, unsigned long msg, unsigned long depth)
{
    cL4_msg_args(result, tcb, (long*)msg, depth + 1);
    if (*result == 0) {
        cL4_mr_emit_tag(tcb + 0x2140, &"WOd", 3, *(unsigned long *)(tcb + 0x2150));
        *result = 0; result[2] = 0; result[3] = 0; result[4] = 0;
    }
}

/* 003cd840 @ 0x003cd840   (est. cL4_ipc_emit_wof)
 * Ghidra: void FUN_003cd840(int *result, long tcb, void *msg, int depth)
 * Decode the argument LIST in `msg` (each word via cL4_arg_decode) and emit a
 * tagged IPC record with tag "WOf" carrying 3 words; clear result on
 * success. Confidence: medium. Notes:  */
void cL4_ipc_emit_wof(int *result, unsigned long tcb, unsigned long msg, unsigned long depth)
{
    cL4_msg_args(result, tcb, (long*)msg, depth + 1);
    if (*result == 0) {
        cL4_mr_emit_tag(tcb + 0x2140, &"WOf", 3, *(unsigned long *)(tcb + 0x2150));
        *result = 0; result[2] = 0; result[3] = 0; result[4] = 0;
    }
}

/* 003cd89c @ 0x003cd89c   (est. cL4_ipc_emit_woh)
 * Ghidra: void FUN_003cd89c(int *result, long tcb, void *msg, int depth)
 * Decode the argument LIST in `msg` (each word via cL4_arg_decode) and emit a
 * tagged IPC record with tag "WOh" carrying 3 words; clear result on
 * success. Confidence: medium. Notes:  */
void cL4_ipc_emit_woh(int *result, unsigned long tcb, unsigned long msg, unsigned long depth)
{
    cL4_msg_args(result, tcb, (long*)msg, depth + 1);
    if (*result == 0) {
        cL4_mr_emit_tag(tcb + 0x2140, &"WOh", 3, *(unsigned long *)(tcb + 0x2150));
        *result = 0; result[2] = 0; result[3] = 0; result[4] = 0;
    }
}

/* 003cfa08 @ 0x003cfa08   (est. cL4_ipc_emit_wog)
 * Ghidra: void FUN_003cfa08(int *result, long tcb, void *msg, int depth)
 * Decode the argument LIST in `msg` (each word via cL4_arg_decode) and emit a
 * tagged IPC record with tag "WOg" carrying 3 words; clear result on
 * success. Confidence: medium. Notes:  */
void cL4_ipc_emit_wog(int *result, unsigned long tcb, unsigned long msg, unsigned long depth)
{
    cL4_msg_args(result, tcb, (long*)msg, depth + 1);
    if (*result == 0) {
        cL4_mr_emit_tag(tcb + 0x2140, &"WOg", 3, *(unsigned long *)(tcb + 0x2150));
        *result = 0; result[2] = 0; result[3] = 0; result[4] = 0;
    }
}

/* 003cfa64 @ 0x003cfa64   (est. cL4_ipc_emit_wob2)
 * Ghidra: void FUN_003cfa64(int *result, long tcb, void *msg, int depth)
 * Decode the argument LIST in `msg` (each word via cL4_arg_decode) and emit a
 * tagged IPC record with tag "WOB" carrying 3 words; clear result on
 * success. Confidence: medium. Notes:  */
void cL4_ipc_emit_wob2(int *result, unsigned long tcb, unsigned long msg, unsigned long depth)
{
    cL4_msg_args(result, tcb, (long*)msg, depth + 1);
    if (*result == 0) {
        cL4_mr_emit_tag(tcb + 0x2140, &"WOB", 3, *(unsigned long *)(tcb + 0x2150));
        *result = 0; result[2] = 0; result[3] = 0; result[4] = 0;
    }
}

/* 003cfac0 @ 0x003cfac0   (est. cL4_ipc_emit_woc2)
 * Ghidra: void FUN_003cfac0(int *result, long tcb, void *msg, int depth)
 * Decode the argument LIST in `msg` (each word via cL4_arg_decode) and emit a
 * tagged IPC record with tag "WOC" carrying 3 words; clear result on
 * success. Confidence: medium. Notes:  */
void cL4_ipc_emit_woc2(int *result, unsigned long tcb, unsigned long msg, unsigned long depth)
{
    cL4_msg_args(result, tcb, (long*)msg, depth + 1);
    if (*result == 0) {
        cL4_mr_emit_tag(tcb + 0x2140, &"WOC", 3, *(unsigned long *)(tcb + 0x2150));
        *result = 0; result[2] = 0; result[3] = 0; result[4] = 0;
    }
}

/* 003cfb1c @ 0x003cfb1c   (est. cL4_ipc_emit_wod2)
 * Ghidra: void FUN_003cfb1c(int *result, long tcb, void *msg, int depth)
 * Decode the argument LIST in `msg` (each word via cL4_arg_decode) and emit a
 * tagged IPC record with tag "WOD" carrying 3 words; clear result on
 * success. Confidence: medium. Notes:  */
void cL4_ipc_emit_wod2(int *result, unsigned long tcb, unsigned long msg, unsigned long depth)
{
    cL4_msg_args(result, tcb, (long*)msg, depth + 1);
    if (*result == 0) {
        cL4_mr_emit_tag(tcb + 0x2140, &"WOD", 3, *(unsigned long *)(tcb + 0x2150));
        *result = 0; result[2] = 0; result[3] = 0; result[4] = 0;
    }
}

/* 003cfb78 @ 0x003cfb78   (est. cL4_ipc_emit_wof2)
 * Ghidra: void FUN_003cfb78(int *result, long tcb, void *msg, int depth)
 * Decode the argument LIST in `msg` (each word via cL4_arg_decode) and emit a
 * tagged IPC record with tag "WOF" carrying 3 words; clear result on
 * success. Confidence: medium. Notes:  */
void cL4_ipc_emit_wof2(int *result, unsigned long tcb, unsigned long msg, unsigned long depth)
{
    cL4_msg_args(result, tcb, (long*)msg, depth + 1);
    if (*result == 0) {
        cL4_mr_emit_tag(tcb + 0x2140, &"WOF", 3, *(unsigned long *)(tcb + 0x2150));
        *result = 0; result[2] = 0; result[3] = 0; result[4] = 0;
    }
}

/* 003cfbd4 @ 0x003cfbd4   (est. cL4_ipc_emit_woh2)
 * Ghidra: void FUN_003cfbd4(int *result, long tcb, void *msg, int depth)
 * Decode the argument LIST in `msg` (each word via cL4_arg_decode) and emit a
 * tagged IPC record with tag "WOH" carrying 3 words; clear result on
 * success. Confidence: medium. Notes:  */
void cL4_ipc_emit_woh2(int *result, unsigned long tcb, unsigned long msg, unsigned long depth)
{
    cL4_msg_args(result, tcb, (long*)msg, depth + 1);
    if (*result == 0) {
        cL4_mr_emit_tag(tcb + 0x2140, &"WOH", 3, *(unsigned long *)(tcb + 0x2150));
        *result = 0; result[2] = 0; result[3] = 0; result[4] = 0;
    }
}

/* 003cd098 @ 0x003cd098   (est. cL4_ipc_emit_tl)
 * Ghidra: void FUN_003cd098(int *result, long tcb, long *msg, int depth)
 * Read the first word of `msg` (deref through kind-5 array), decode it via
 * cL4_arg_decode, and emit tag "TL" (3 words) on success. Confidence:
 * medium. Notes:  */
void cL4_ipc_emit_tl(int *result, unsigned long tcb, unsigned long *msg, unsigned long depth)
{
    unsigned long word;
    if (1 < *(unsigned char *)((long)msg + 0x12) - 1) {
        if ((*(unsigned char *)((long)msg + 0x12) != 5) || ((int)msg[1] == 0)) {
            word = 0; goto emit;
        }
        msg = (unsigned long*)*msg;
    }
    word = *msg;
emit:
    cL4_arg_decode(result, tcb, word, depth + 1);
    if (*result == 0) {
        cL4_mr_emit_tag(tcb + 0x2140, &"TL", 3, *(unsigned long *)(tcb + 0x2150));
        *result = 0; result[2] = 0; result[3] = 0; result[4] = 0;
    }
}

/* 003cdb7c @ 0x003cdb7c   (est. cL4_ipc_emit_mxm)
 * Ghidra: void FUN_003cdb7c(int *result, long tcb, long *msg, int depth)
 * Read the first word of `msg` (deref through kind-5 array), decode it via
 * cL4_arg_decode, and emit tag "MXM" (3 words) on success. Confidence:
 * medium. Notes:  */
void cL4_ipc_emit_mxm(int *result, unsigned long tcb, unsigned long *msg, unsigned long depth)
{
    unsigned long word;
    if (1 < *(unsigned char *)((long)msg + 0x12) - 1) {
        if ((*(unsigned char *)((long)msg + 0x12) != 5) || ((int)msg[1] == 0)) {
            word = 0; goto emit;
        }
        msg = (unsigned long*)*msg;
    }
    word = *msg;
emit:
    cL4_arg_decode(result, tcb, word, depth + 1);
    if (*result == 0) {
        cL4_mr_emit_tag(tcb + 0x2140, &"MXM", 3, *(unsigned long *)(tcb + 0x2150));
        *result = 0; result[2] = 0; result[3] = 0; result[4] = 0;
    }
}

/* 003cdc10 @ 0x003cdc10   (est. cL4_ipc_emit_mxe)
 * Ghidra: void FUN_003cdc10(int *result, long tcb, long *msg, int depth)
 * Read the first word of `msg` (deref through kind-5 array), decode it via
 * cL4_arg_decode, and emit tag "MXE" (3 words) on success. Confidence:
 * medium. Notes:  */
void cL4_ipc_emit_mxe(int *result, unsigned long tcb, unsigned long *msg, unsigned long depth)
{
    unsigned long word;
    if (1 < *(unsigned char *)((long)msg + 0x12) - 1) {
        if ((*(unsigned char *)((long)msg + 0x12) != 5) || ((int)msg[1] == 0)) {
            word = 0; goto emit;
        }
        msg = (unsigned long*)*msg;
    }
    word = *msg;
emit:
    cL4_arg_decode(result, tcb, word, depth + 1);
    if (*result == 0) {
        cL4_mr_emit_tag(tcb + 0x2140, &"MXE", 3, *(unsigned long *)(tcb + 0x2150));
        *result = 0; result[2] = 0; result[3] = 0; result[4] = 0;
    }
}

/* 003ce7f4 @ 0x003ce7f4   (est. cL4_ipc_emit_qo)
 * Ghidra: void FUN_003ce7f4(int *result, long tcb, long *msg, int depth)
 * Read the first word of `msg` (deref through kind-5 array), decode it via
 * cL4_arg_decode, and emit tag "QO" (2 words) on success. Confidence:
 * medium. Notes:  */
void cL4_ipc_emit_qo(int *result, unsigned long tcb, unsigned long *msg, unsigned long depth)
{
    unsigned long word;
    if (1 < *(unsigned char *)((long)msg + 0x12) - 1) {
        if ((*(unsigned char *)((long)msg + 0x12) != 5) || ((int)msg[1] == 0)) {
            word = 0; goto emit;
        }
        msg = (unsigned long*)*msg;
    }
    word = *msg;
emit:
    cL4_arg_decode(result, tcb, word, depth + 1);
    if (*result == 0) {
        cL4_mr_emit_tag(tcb + 0x2140, &"QO", 2, *(unsigned long *)(tcb + 0x2150));
        *result = 0; result[2] = 0; result[3] = 0; result[4] = 0;
    }
}

/* 003cf418 @ 0x003cf418   (est. cL4_ipc_emit_mq2)
 * Ghidra: void FUN_003cf418(int *result, long tcb, long *msg, int depth)
 * Read the first word of `msg` (deref through kind-5 array), decode it via
 * cL4_arg_decode, and emit tag "Mq" (2 words) on success. Confidence:
 * medium. Notes:  */
void cL4_ipc_emit_mq2(int *result, unsigned long tcb, unsigned long *msg, unsigned long depth)
{
    unsigned long word;
    if (1 < *(unsigned char *)((long)msg + 0x12) - 1) {
        if ((*(unsigned char *)((long)msg + 0x12) != 5) || ((int)msg[1] == 0)) {
            word = 0; goto emit;
        }
        msg = (unsigned long*)*msg;
    }
    word = *msg;
emit:
    cL4_arg_decode(result, tcb, word, depth + 1);
    if (*result == 0) {
        cL4_mr_emit_tag(tcb + 0x2140, &"Mq", 2, *(unsigned long *)(tcb + 0x2150));
        *result = 0; result[2] = 0; result[3] = 0; result[4] = 0;
    }
}


/* FUN_003a6c28 @ 0x3a6c28   (est. sk_parse_function_type)
 * Ghidra: undefined8 FUN_003a6c28(long param_1)
 * Parses a function-type signature from the stream context st, building a
 * tagged node tree under a wrapper node (tag 0x77). Consumes the calling
 * convention/ownership prefix (s|I), the parameter list, generic params,
 * result, and trailing markers (e/A/ownership glyph, block/closure/method
 * kind, yield A/G/I, _Sendable h, _async H, T). Returns the wrapper node, or
 * 0 on malformed input. The grammar is Swift-metadata-style: single-letter
 * stream tokens select the tags applied to the emitted nodes.
 * Confidence: medium
 * Notes: string refs s__callee_guaranteed_005d6e4e, s__convention_thin__005d6e6f,
 *   s__callee_owned_005d6e61, s__callee_unowned_005d6e3e, s_block_005d6e81,
 *   s_closure_005d6e9a, s_method_005d6e87, s_objc_method_005d6e8e,
 *   s_witness_method_005d6ea2, s_yield_once_005d57a1, s_yield_many_005d57b9,
 *   s_yield_once_2_005d57ac, s__Sendable_005d6eb1, s__async_005d6ebb;
 *   helpers FUN_003ad724/003a4d5c/003ad048/003add54/003ae134/003adff0/
 *   003ae05c/003ae0c8/003adf20/003a3a10/00115080. */
static uint64_t *sk_parse_function_type(uint64_t *st)
{
    uint64_t *root;      /* wrapper node (tag 0x77) */
    uint64_t *sub;       /* transient node */
    uint64_t *item;      /* child node from the value stack */
    uint64_t *parsed;    /* value parsed from the stream */
    long extra = 0;      /* optional trailing parsed value */
    uint64_t pos, end;
    uint64_t v;          /* generic/param accumulation */
    uint32_t cnt;
    char c;

    root = sk_node_alloc(st, 1);
    NODE_SETTAG(root, 0x77); NODE_SETSUBT(root, 0);

    end = STREAM_END(st); pos = STREAM_POS(st);

    /* 's' prefix: single value result  -> emit '|' node {',', parsed} */
    if (pos < end && STREAM_DATA(st)[pos] == 's') {
        STREAM_POS(st) = pos + 1;
        parsed = NULL; extra = 0;
        if (!sk_parse_value(st, &parsed, &extra)) return 0;
        if (STACK_CNT(st) == 0) return 0;
        cnt = STACK_CNT(st) - 1;
        item = STACK_BASE(st)[cnt];
        if (NODE_TAG(item) != 0x2c) return 0;
        STACK_CNT(st) = cnt;
        sub = sk_node_alloc(st, 1);
        NODE_SETTAG(sub, 0x7c); NODE_SETSUBT(sub, 0);
        sk_node_add(sub, item, st);
        sk_node_add(sub, parsed, st);
        if (extra) sk_node_add(sub, extra, st);
        sk_node_add(root, sub, st);
        end = STREAM_END(st); pos = STREAM_POS(st);
    }

    /* 'I' prefix: async function -> emit 'y' node {parsed[, extra]} */
    if (pos < end && STREAM_DATA(st)[pos] == 'I') {
        STREAM_POS(st) = pos + 1;
        parsed = NULL; extra = 0;
        if (!sk_parse_value(st, &parsed, &extra)) return 0;
        sub = sk_node_alloc(st, 1);
        NODE_SETTAG(sub, 0x79); NODE_SETSUBT(sub, 0);
        if (extra != 1) return 0;
        sk_node_add(sub, parsed, st);
        if (extra) sk_node_add(sub, extra, st);
        sk_node_add(root, sub, st);
    }

    /* pop the (optional) parameter group; 'P' converts ',' -> '/' */
    if (STACK_CNT(st) == 0) { item = 0; }
    else {
        cnt = STACK_CNT(st) - 1;
        item = STACK_BASE(st)[cnt];
        if (NODE_TAG(item) != 0x2c) item = 0;
        else {
            STACK_CNT(st) = cnt;
            pos = STREAM_POS(st);
            if (pos < STREAM_END(st) && STREAM_DATA(st)[pos] == 'P') {
                STREAM_POS(st) = pos + 1;
                item = sk_tag_convert(st, item, 0x2f);
            }
        }
    }

    /* optional markers: 'e' -> 'k' node, 'A' -> 'n' node */
    end = STREAM_END(st); pos = STREAM_POS(st);
    if (pos < end && STREAM_DATA(st)[pos] == 'e') {
        STREAM_POS(st) = pos + 1;
        sub = sk_node_alloc(st, 1);
        NODE_SETTAG(sub, 0x6b); NODE_SETSUBT(sub, 0);
        sk_node_add(root, sub, st);
        end = STREAM_END(st); pos = STREAM_POS(st);
    }
    if (pos < end && STREAM_DATA(st)[pos] == 'A') {
        STREAM_POS(st) = pos + 1;
        sub = sk_node_alloc(st, 1);
        NODE_SETTAG(sub, 0x6e); NODE_SETSUBT(sub, 0);
        sk_node_add(root, sub, st);
        end = STREAM_END(st); pos = STREAM_POS(st);
    }

    /* one-byte scalar argument (token in the 8-bit set) -> 'm' node, sub 4 */
    {
        uint8_t tok = (pos < end) ? (uint8_t)STREAM_DATA(st)[pos] : 0x9c;
        uint8_t idx = (uint8_t)((tok - 100) >> 1 & 0x7f | (tok - 100 & 1) << 7);
        if (idx < 8 && (1u << (idx & 0x1f) & 0x93u)) {
            uint64_t bv = (pos < end) ? (uint64_t)(int8_t)STREAM_DATA(st)[pos] : 0;
            if (pos < end) STREAM_POS(st) = pos + 1;
            sub = sk_node_alloc(st, 1);
            NODE_SETTAG(sub, 0x6d); NODE_SETSUBT(sub, 4);
            sub[0] = bv;
            sk_node_add(root, sub, st);
            end = STREAM_END(st); pos = STREAM_POS(st);
        }
    }

    /* calling-convention/ownership glyph: g/t/x/y -> 'l' string node, sub 3 */
    if (end <= pos) return 0;
    STREAM_POS(st) = pos + 1;
    c = STREAM_DATA(st)[pos];
    const char *cc;
    if ((uint8_t)c < 0x78) {
        if (c == 'g') cc = s__callee_guaranteed_005d6e4e;
        else if (c != 't') return 0;
        else cc = s__convention_thin__005d6e6f;
    } else if (c == 'x') cc = s__callee_owned_005d6e61;
    else if (c != 'y') return 0;
    else cc = s__callee_unowned_005d6e3e;
    sub = sk_node_alloc(st, 1);
    sub[0] = (uint64_t)cc;
    sub[1] = sk_len_query(cc);
    NODE_SETTAG(sub, 0x6c); NODE_SETSUBT(sub, 3);
    sk_node_add(root, sub, st);

    /* function-kind marker: B/C/K/M/O/W/z -> 'u' node; 'z'+B/C adds a
     * string argument node (0x18) */
    end = STREAM_END(st); pos = STREAM_POS(st);
    {
        uint64_t newpos = pos;
        bool hasarg = false;
        const char *kind;
        if (newpos < end) {
            uint8_t k = STREAM_DATA(st)[newpos];
            if (k < 0x4d) {
                if (k == 0x42) { kind = s_block_005d6e81; }
                else if (k == 0x43) { kind = DAT_005d6cd7; }
                else if (k != 0x4b) goto skipkind;
                else { kind = s_closure_005d6e9a; }
            } else if (k < 0x57) {
                if (k == 0x4d) { kind = s_method_005d6e87; }
                else if (k != 0x4f) goto skipkind;
                else { kind = s_objc_method_005d6e8e; }
            } else if (k == 0x57) { kind = s_witness_method_005d6ea2; }
            else if (k != 0x7a) goto skipkind;
            else {
                /* 'z' + B/C: two-char kind with an optional following arg */
                uint64_t p2 = newpos + 2;
                if (end <= newpos + 1) { newpos -= 2; goto skipkind; }
                STREAM_POS(st) = p2;
                if (STREAM_DATA(st)[newpos + 1] == 'B') kind = s_block_005d6e81;
                else if (STREAM_DATA(st)[newpos + 1] != 'C') { newpos -= 2; goto skipkind; }
                else kind = DAT_005d6cd7;
                hasarg = true;
            }
            sub = sk_node_alloc(st, 1);
            NODE_SETTAG(sub, 0x75); NODE_SETSUBT(sub, 0);
            sk_node_add(sub, sk_node_make(st, 0x76, kind), st);
            if (hasarg) {
                uint64_t *argnode = sk_parse_string_token(st);
                if (argnode) sk_node_add(sub, argnode, st);
            }
            sk_node_add(root, sub, st);
            end = STREAM_END(st); newpos = STREAM_POS(st);
        }
skipkind:
        pos = newpos;
    }

    /* yield markers: A/G/I -> 'x' node */
    if (pos < end) {
        c = STREAM_DATA(st)[pos];
        const char *y;
        if (c == 'A') y = s_yield_once_005d57a1;
        else if (c == 'G') y = s_yield_many_005d57b9;
        else if (c != 'I') goto noyield;
        else y = s_yield_once_2_005d57ac;
        STREAM_POS(st) = pos + 1;
        sk_node_add(root, sk_node_make(st, 0x78, y), st);
        end = STREAM_END(st); pos = STREAM_POS(st);
    }
noyield:

    /* attribute nodes: 'h' -> _Sendable (0x74,sub3), 'H' -> _async, 'T' -> 0x6f */
    if (pos < end && STREAM_DATA(st)[pos] == 'h') {
        STREAM_POS(st) = pos + 1;
        sub = sk_node_alloc(st, 1);
        sub[0] = (uint64_t)s__Sendable_005d6eb1;
        sub[1] = 9;
        NODE_SETTAG(sub, 0x74); NODE_SETSUBT(sub, 3);
        sk_node_add(root, sub, st);
        end = STREAM_END(st); pos = STREAM_POS(st);
    }
    if (pos < end && STREAM_DATA(st)[pos] == 'H') {
        STREAM_POS(st) = pos + 1;
        sub = sk_node_alloc(st, 1);
        sub[0] = (uint64_t)s__async_005d6ebb;
        sub[1] = 6;
        NODE_SETTAG(sub, 0x74); NODE_SETSUBT(sub, 3);
        sk_node_add(root, sub, st);
        end = STREAM_END(st); pos = STREAM_POS(st);
    }
    if (pos < end && STREAM_DATA(st)[pos] == 'T') {
        STREAM_POS(st) = pos + 1;
        sub = sk_node_alloc(st, 1);
        NODE_SETTAG(sub, 0x6f); NODE_SETSUBT(sub, 0);
        sk_node_add(root, sub, st);
    }

    /* parameter list and result: 0x7b groups (with optional e/f/3 args) and
     * 0x7d results; each iteration emits one child and bumps the count */
    if (item) sk_node_add(root, item, st);
    {
        uint32_t n = 0;
        sub = sk_parse_group(st, 0x7b);
        while (sub) {
            sk_node_add(root, sub, st);
            uint64_t *a = sk_parse_arg_7b(st);
            if (a) sk_node_add(sub, a, st);
            a = sk_parse_arg_7d(st);
            if (a) sk_node_add(sub, a, st);
            a = sk_parse_arg_7e(st);
            if (a) sk_node_add(sub, a, st);
            a = sk_parse_arg_7f(st);
            if (a) sk_node_add(sub, a, st);
            n++;
            sub = sk_parse_group(st, 0x7b);
        }
        sub = sk_parse_group(st, 0x7d);
        while (sub) {
            sk_node_add(root, sub, st);
            uint64_t *a = sk_parse_arg_7b(st);
            if (a) sk_node_add(sub, a, st);
            n++;
            sub = sk_parse_group(st, 0x7d);
        }
        /* 'Y' repetitions */
        end = STREAM_END(st); pos = STREAM_POS(st);
        if (pos < end) {
            c = STREAM_DATA(st)[pos];
            while (c == 'Y') {
                n++;
                STREAM_POS(st) = pos + 1;
                sub = sk_parse_group(st, 0x7e);
                if (!sub) return 0;
                sk_node_add(root, sub, st);
                end = STREAM_END(st); pos = STREAM_POS(st);
                if (end <= pos) break;
                c = STREAM_DATA(st)[pos];
            }
        }
        /* 'z' trailer */
        if (pos < end && STREAM_DATA(st)[pos] == 'z') {
            STREAM_POS(st) = pos + 1;
            sub = sk_parse_group(st, 0x7f);
            if (!sub) return 0;
            sk_node_add(root, sub, st);
            n++;
            end = STREAM_END(st); pos = STREAM_POS(st);
        }
        /* final '_' then consume n compound children in reverse order */
        if (end <= pos || STREAM_DATA(st)[pos] != '_') return 0;
        STREAM_POS(st) = pos + 1;
        if ((int)n > 0) {
            uint32_t i = 0;
            int64_t ri = -1;
            do {
                if (STACK_CNT(st) == 0) return 0;
                cnt = STACK_CNT(st) - 1;
                item = STACK_BASE(st)[cnt];
                if (NODE_TAG(item) != 0xf4) return 0;
                STACK_CNT(st) = cnt;
                uint8_t st2 = NODE_SUBT(root);
                uint64_t val = 0;
                if (st2 == 5) {
                    uint64_t hi = (uint64_t)NODE_VAL(root);
                    uint64_t j = (uint64_t)ri + hi;
                    while (j < hi) {
                        uint64_t *base = (st2 - 1 > 1) ? (uint64_t *)NODE_DATA(root) : root;
                        val = base[j];
                        if (j >= hi) break;
                        j++;
                    }
                } else if (st2 == 2) {
                    uint64_t j = 1 - i; uint64_t hi = 2;
                    while (j < hi) { val = NODE_DATA(root)[j]; j++; }
                } else if (st2 == 1) {
                    uint64_t j = (uint64_t)(-i); uint64_t hi = 1;
                    while (j < hi) { val = NODE_DATA(root)[j]; j++; }
                }
                sk_node_add(val, item, st);
                i++; ri--;
            } while ((uint64_t)n + ri != (uint64_t)-1);
        }
    }
    return sk_node_push(st, 0xf4, root);
}