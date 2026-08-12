/* Recreated from txm.macosx.release.im4p (TXM, arm64e, image base 0) — the
 * Trusted Execution Monitor (GL0). Ground truth: Ghidra FUN_ names + addresses.
 * This file covers the trust-cache + txm_enter-dispatch region 0x2a000-0x35000
 * (txm_waves/T2.txt, 268 functions). All names are estimates unless
 * string/header-matched; see docs/sptm/manifest.json.
 *
 * The region comprises: (a) DT /chosen + /defaults boot-config getters
 * (0x2a000-0x2ab00), (b) the txm_enter selector dispatch hub (0x2adec) and its
 * per-op handlers (0x2b380-0x2c3f8), (c) address-range translate/copy helpers
 * and image4 dispatch (0x2c464-0x2d200), (d) a fortified libc (memset/memcmp/
 * strcmp/strlen/strlcpy/printf family + bounded copies) (0x2d214-0x2f0ec),
 * (e) boot-arg / trust-cache state accessors (0x2f190-0x2f960), and
 * (f) the AppleImage4 trust-evaluation / code-signing verification stack
 * (0x2fa00-0x34ff8): CodeDirectory/superblob parsing, CEContext, AMFI CMS
 * verify, entitlements.
 *
 * Security-relevant observations are logged to docs/sptm/findings.md. */

/* ---- shared TXM/kernel/hardware externs (one-line notes) ---- */
typedef unsigned long ulong;
typedef unsigned int  uint;
typedef unsigned char uchar;
typedef unsigned short ushort;

#define GENTER()          /* GENTER opcode 0x00201420: enters GL0 (TXM); the
                             selector in x16 selects the dispatch endpoint */
#define GEXIT()           /* GEXIT opcode 0x00201400: returns from GL0 */
#define CallSupervisor(n) /* svc #n: supervisor call to the kernel */
#define DC_ZVA(p)         /* dc zva: data-cache zero by virtual address */
#define NEON_uminv(a,n)   /* neon uminv: unsigned minimum across vector */
#define LZCOUNT(x)        /* clz: count leading zeros */
#define SoftwareBreakpoint(code, addr) ((void*)0)  /* brk #code (debug trap) */
#define DataSynchronizationBarrier(a,b,c)  __asm__ volatile("dsb sy")
#define InstructionSynchronizationBarrier() __asm__ volatile("isb")

/* Device-tree node/property lookup (dt accessors, 0x4e8b4 / 0x4eb24). */
extern int dt_find_node(void *tree, int parent, const char *name, void **out);
extern int dt_get_property(void *tree, void *node, const char *name, void **out, int *len);
/* Log a message; assert/panic. */
extern void txm_log(const char *fmt, ...);
extern void txm_assert_fail(const char *assertion, const char *file,
                            const char *func, int line);
extern void txm_panic(unsigned long code, unsigned long arg);
extern void txm_assert(unsigned long code);   /* FUN_29a3c: bounds assert */
extern void txm_stack_check_fail(void);       /* FUN_2f13c: canary mismatch */
extern void txm_panic_str(const char *msg);   /* FUN_29730: noreturn panic */
extern void txm_deny_executable_mapping(void);/* FUN_25c6c: log + deny */
extern unsigned long txm_syscall_26(void);    /* FUN_2d200: svc #0x26 */
extern unsigned long txm_errno_slot(void);    /* FUN_29750: errno */
extern long txm_secure_memcmp(const void*, const void*, unsigned long); /* 2d5f0 */
extern unsigned long txm_strlen(const char*); /* 2dbe0 */
extern unsigned long txm_strlen_v(const char*);/* 2dc80 */
extern void *txm_memcpy(void*, const void*, unsigned long);  /* 2d6b0 */
extern void txm_memset(void*, int, unsigned long);           /* 2d2b0 */
extern void txm_bzero(void*, unsigned long);                 /* 2d240 */

/* AppleImage4 / code-signing callees (reside outside this region). */
extern unsigned long img4_dispatch_get_handler(void);   /* 535e0 */
extern unsigned long img4_dispatch_get_input_size(long);/* 53cb0 */
extern long chain_crypt(int kind, const void*, ulong, int, int, void*); /* 3a210 etc */
extern int crypto_hash(int kind, const void *data, ulong len, void *digest); /* 439d0 family */
extern void crypto_hash_ctx_init(void*, const void*, const void*, const void*); /* 37f5c */

/* TXM global state block (DAT_00070008). */
extern unsigned char txm_state_block[];   /* DAT_70008 */
extern unsigned long txm_state_handoff(void); /* thunk 299fc: get handoff */
extern unsigned long txm_state_get(long *out);  /* 2f8fc */
extern unsigned long txm_state_base(void);      /* 2f8ec */

/* The various global descriptor tables referenced by name getters (2fe84..2ff78). */
extern unsigned char DAT_0000da98[]; extern unsigned char DAT_0000daa8[];
extern unsigned char DAT_0000dab8[]; extern unsigned char DAT_0000dac8[];
extern unsigned char DAT_0000dad8[]; extern unsigned char DAT_00015598[];
extern unsigned char DAT_000163e0[]; extern unsigned char DAT_00016a60[];
extern unsigned char DAT_000170e0[]; extern unsigned char DAT_00016da0[];
extern unsigned char DAT_00017420[]; extern unsigned char DAT_00017e00[];
extern unsigned char DAT_00018290[]; extern unsigned char DAT_000197c8[];

/* per-op global flag bytes for the txm_enter dispatch state. */
extern unsigned char DAT_000104e8; /* txm feature flags byte */
extern unsigned char DAT_000104e9; /* txm enabled flag  (==1 when active) */
extern unsigned char DAT_000104ef; /* internal device variant flag */
extern unsigned long DAT_00010500; /* reserved slot */
extern unsigned long DAT_00010518; /* security-boot-mode data */
extern unsigned long DAT_00010520, DAT_00010528;
extern void *DAT_00010530;         /* DT root handle */
extern unsigned long DAT_00010590; /* txm dispatch state base */
extern unsigned long DAT_000105c0, DAT_00010608, DAT_00010610;
extern unsigned long DAT_00010678; /* device feature set */
extern unsigned long DAT_000107d8;
extern unsigned long DAT_000107e8;
extern unsigned long DAT_00010800; /* global allow flag (entitlement gate) */
extern unsigned long DAT_00006cf0; /* stack canary */
extern unsigned long DAT_00070690; /* dispatch armed/disabled byte */
extern unsigned long DAT_00070694, DAT_00070698;
extern unsigned long DAT_0007101c, DAT_00071020, DAT_00071024, DAT_00071028;
extern unsigned long DAT_00071030, DAT_00071034, DAT_00071038;
extern unsigned long DAT_00070fa8, DAT_00070fb0;
extern unsigned long DAT_00070008, DAT_00070028, DAT_00070038;

/* Fixed error/marker values (little-endian byte-packed status words used by
 * the AppleImage4 API: low byte = op id, 2nd byte = sub-error, high bits = class). */
static const ulong ERR_NOENT          = 0x0000e1UL; /* CEContext errno codes are
                                                       packed; kept as magic */
static const ulong s_chosen[] = {0};   /* "/chosen" (0x18d7) */

/* ---- function bodies ---- */
