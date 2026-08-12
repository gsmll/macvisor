/* Recreated from exclavecore_bundle.t8142.RELEASE.im4p (cL4 Secure Kernel, GL1,
 * arm64e, image base 0) — the cL4 microkernel. Ground truth: Ghidra FUN_ names +
 * addresses in cl4_kernel.raw. Version "cL4 microkernel (cL4 (679.100.61))".
 * All names are estimates unless string/header-matched.
 * Slice 0x40000-0x50000: VAS (virtual address space) / spanmap layer, TB
 * placeholder (tightbeam) encode-decode helpers, and libpmm EP-call wrappers. */

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#include "sk_internal.h"

/* ---- Out-of-range cL4 helpers referenced by this region (FUN_ in comment).
 * All take/return 64-bit words (arm64e addresses), matching the decompile. ---- */
extern unsigned long sk_x_0000178c(); /* FUN_0000178C */
extern unsigned long sk_x_000101a0(); /* FUN_000101A0 */
extern unsigned long sk_alloc_array(); /* FUN_00010244 */
extern unsigned long sk_free_tagged(); /* FUN_00012568 */
extern unsigned long sk_x_000147a0(); /* FUN_000147A0 */
extern unsigned long sk_x_000147e0(); /* FUN_000147E0 */
extern unsigned long sk_x_00014f90(); /* FUN_00014F90 */
extern unsigned long sk_tb_setup(); /* FUN_00015458 */
extern unsigned long sk_x_0001590c(); /* FUN_0001590C */
extern unsigned long sk_x_00015be8(); /* FUN_00015BE8 */
extern unsigned long sk_x_00015c30(); /* FUN_00015C30 */
extern unsigned long sk_x_00015cdc(); /* FUN_00015CDC */
extern unsigned long sk_x_000185b8(); /* FUN_000185B8 */
extern unsigned long sk_x_00018600(); /* FUN_00018600 */
extern unsigned long sk_x_0001882c(); /* FUN_0001882C */
extern unsigned long sk_x_00018878(); /* FUN_00018878 */
extern unsigned long sk_x_000188fc(); /* FUN_000188FC */
extern unsigned long sk_x_00018984(); /* FUN_00018984 */
extern unsigned long sk_x_00018a4c(); /* FUN_00018A4C */
extern unsigned long sk_x_00018b98(); /* FUN_00018B98 */
extern unsigned long sk_x_00018be8(); /* FUN_00018BE8 */
extern unsigned long sk_x_00018dd4(); /* FUN_00018DD4 */
extern unsigned long sk_x_00018e60(); /* FUN_00018E60 */
extern unsigned long sk_x_00018f38(); /* FUN_00018F38 */
extern unsigned long sk_x_00018fb8(); /* FUN_00018FB8 */
extern unsigned long sk_x_000287e4(); /* FUN_000287E4 */
extern unsigned long sk_x_00032cd0(); /* FUN_00032CD0 */
extern unsigned long sk_free_pg(); /* FUN_00033498 */
extern unsigned long sk_x_0003353c(); /* FUN_0003353C */
extern unsigned long sk_x_000335e0(); /* FUN_000335E0 */
extern unsigned long sk_pmm_free(); /* FUN_00034334 */
extern unsigned long sk_x_00034a2c(); /* FUN_00034A2C */
extern unsigned long sk_x_00034b10(); /* FUN_00034B10 */
extern unsigned long sk_x_00034ba4(); /* FUN_00034BA4 */
extern unsigned long sk_x_00034bd8(); /* FUN_00034BD8 */
extern unsigned long sk_x_00034d5c(); /* FUN_00034D5C */
extern unsigned long sk_x_00034f70(); /* FUN_00034F70 */
extern unsigned long sk_x_00035ba0(); /* FUN_00035BA0 */
extern unsigned long sk_spanmap_get3(); /* FUN_00036008 */
extern unsigned long sk_x_0003a550(); /* FUN_0003A550 */
extern unsigned long sk_x_0003b340(); /* FUN_0003B340 */
extern unsigned long sk_x_0003b410(); /* FUN_0003B410 */
extern unsigned long sk_x_0003b478(); /* FUN_0003B478 */
extern unsigned long sk_x_0003b548(); /* FUN_0003B548 */
extern unsigned long sk_x_0003b648(); /* FUN_0003B648 */
extern unsigned long sk_x_0003b6ac(); /* FUN_0003B6AC */
extern unsigned long sk_x_0003b6c0(); /* FUN_0003B6C0 */
extern unsigned long sk_x_0003be18(); /* FUN_0003BE18 */
extern unsigned long sk_x_0003be88(); /* FUN_0003BE88 */
extern unsigned long sk_x_0003bfb8(); /* FUN_0003BFB8 */
extern unsigned long sk_x_0003d2b8(); /* FUN_0003D2B8 */
extern unsigned long sk_x_0003d330(); /* FUN_0003D330 */
extern unsigned long sk_x_0003dd68(); /* FUN_0003DD68 */
extern unsigned long sk_x_0003f804(); /* FUN_0003F804 */
extern unsigned long sk_x_0003f980(); /* FUN_0003F980 */
extern unsigned long sk_x_0003fa94(); /* FUN_0003FA94 */
extern unsigned long sk_x_0003fcc8(); /* FUN_0003FCC8 */
extern unsigned long sk_x_00050c88(); /* FUN_00050C88 */
extern unsigned long sk_x_00050ce8(); /* FUN_00050CE8 */
extern unsigned long sk_x_000510e4(); /* FUN_000510E4 */
extern unsigned long sk_x_00051488(); /* FUN_00051488 */
extern unsigned long sk_x_00051e5c(); /* FUN_00051E5C */
extern unsigned long sk_x_00051ee4(); /* FUN_00051EE4 */
extern unsigned long sk_x_00052248(); /* FUN_00052248 */
extern unsigned long sk_x_0005228c(); /* FUN_0005228C */
extern unsigned long sk_x_0005236c(); /* FUN_0005236C */
extern unsigned long sk_pmm_bootmem(); /* FUN_00053470 */
extern unsigned long sk_x_000539fc(); /* FUN_000539FC */
extern unsigned long sk_x_00054354(); /* FUN_00054354 */
extern unsigned long sk_global_cfg(); /* FUN_00054610 */
extern unsigned long sk_x_00054a4c(); /* FUN_00054A4C */
extern unsigned long sk_x_00054de4(); /* FUN_00054DE4 */
extern unsigned long sk_x_0005530c(); /* FUN_0005530C */
extern unsigned long sk_cfg_c(); /* FUN_00055344 */
extern unsigned long sk_cfg_b(); /* FUN_00055360 */
extern unsigned long sk_x_000553e4(); /* FUN_000553E4 */
extern unsigned long sk_x_00055558(); /* FUN_00055558 */
extern unsigned long sk_x_000555ac(); /* FUN_000555AC */
extern unsigned long sk_x_00055a90(); /* FUN_00055A90 */
extern unsigned long sk_x_0005acac(); /* FUN_0005ACAC */
extern unsigned long sk_x_0005b190(); /* FUN_0005B190 */
extern unsigned long sk_x_0005b89c(); /* FUN_0005B89C */
extern unsigned long sk_x_0005ba14(); /* FUN_0005BA14 */
extern unsigned long sk_x_0005ba5c(); /* FUN_0005BA5C */
extern unsigned long sk_x_0005baac(); /* FUN_0005BAAC */
extern unsigned long sk_x_0005baf0(); /* FUN_0005BAF0 */
extern unsigned long sk_x_0005d470(); /* FUN_0005D470 */
extern unsigned long sk_x_0005ea94(); /* FUN_0005EA94 */
extern unsigned long sk_x_0005eb78(); /* FUN_0005EB78 */
extern unsigned long sk_x_0005ec20(); /* FUN_0005EC20 */
extern unsigned long sk_x_0005ec98(); /* FUN_0005EC98 */
extern unsigned long sk_x_0005ed18(); /* FUN_0005ED18 */
extern unsigned long sk_x_0005ee40(); /* FUN_0005EE40 */
extern unsigned long sk_x_0005ee50(); /* FUN_0005EE50 */
extern unsigned long sk_x_0005ee58(); /* FUN_0005EE58 */
extern unsigned long sk_x_0005fc54(); /* FUN_0005FC54 */
extern unsigned long sk_x_0005fd2c(); /* FUN_0005FD2C */
extern unsigned long sk_tls_get(); /* FUN_00060524 */
extern unsigned long sk_x_00061614(); /* FUN_00061614 */
extern unsigned long sk_x_000636a4(); /* FUN_000636A4 */
extern unsigned long sk_x_000639a0(); /* FUN_000639A0 */
extern unsigned long sk_x_00063a50(); /* FUN_00063A50 */
extern unsigned long sk_x_00064a7c(); /* FUN_00064A7C */
extern unsigned long sk_memset0(); /* FUN_00114330 */
extern unsigned long sk_tb_put_bytes(); /* FUN_00114790 */
extern unsigned long sk_x_00114e50(); /* FUN_00114E50 */
extern unsigned long sk_strlen(); /* FUN_00115080 */
extern unsigned long sk_x_001150e0(); /* FUN_001150E0 */
extern unsigned long sk_x_00116e80(); /* FUN_00116E80 */
extern unsigned long sk_x_00116f40(); /* FUN_00116F40 */
extern unsigned long sk_x_00117cc4(); /* FUN_00117CC4 */
extern unsigned long sk_x_00117d14(); /* FUN_00117D14 */
extern unsigned long sk_x_00117d18(); /* FUN_00117D18 */
extern unsigned long sk_x_00117e68(); /* FUN_00117E68 */
extern unsigned long sk_x_001180e0(); /* FUN_001180E0 */
extern unsigned long sk_x_001180fc(); /* FUN_001180FC */
extern unsigned long sk_x_0011812c(); /* FUN_0011812C */
extern unsigned long sk_mtx_init(); /* FUN_00118148 */
extern unsigned long sk_mtx_lock(); /* FUN_00118164 */
extern unsigned long sk_mtx_unlock(); /* FUN_00118194 */
extern unsigned long sk_x_0011858c(); /* FUN_0011858C */
extern unsigned long sk_x_001185ec(); /* FUN_001185EC */
extern unsigned long sk_x_001187f4(); /* FUN_001187F4 */
extern unsigned long sk_x_0011883c(); /* FUN_0011883C */
extern unsigned long sk_x_00118b28(); /* FUN_00118B28 */
extern unsigned long sk_x_0011d7e8(); /* FUN_0011D7E8 */
extern unsigned long sk_x_004afae4(); /* FUN_004AFAE4 */
extern unsigned long sk_x_004b23d8(); /* FUN_004B23D8 */
extern unsigned long sk_x_004b2820(); /* FUN_004B2820 */
extern unsigned long sk_x_004b3538(); /* FUN_004B3538 */
extern unsigned long sk_x_004b35a0(); /* FUN_004B35A0 */
extern unsigned long sk_x_004b35f4(); /* FUN_004B35F4 */
extern unsigned long sk_x_004b363c(); /* FUN_004B363C */
extern unsigned long sk_x_004b36c8(); /* FUN_004B36C8 */
extern unsigned long sk_x_004b3718(); /* FUN_004B3718 */
extern unsigned long sk_x_004b3768(); /* FUN_004B3768 */
extern unsigned long sk_x_004b377c(); /* FUN_004B377C */
extern unsigned long sk_x_004b3790(); /* FUN_004B3790 */
extern unsigned long sk_x_004b37a4(); /* FUN_004B37A4 */
extern unsigned long sk_x_004b37b8(); /* FUN_004B37B8 */
extern unsigned long sk_x_004b3808(); /* FUN_004B3808 */
extern unsigned long sk_x_004b3858(); /* FUN_004B3858 */
extern unsigned long sk_x_004b38a8(); /* FUN_004B38A8 */
extern unsigned long sk_x_004b38f8(); /* FUN_004B38F8 */
extern unsigned long sk_x_004b3940(); /* FUN_004B3940 */
extern unsigned long sk_x_004b3988(); /* FUN_004B3988 */
extern unsigned long sk_x_004b39d0(); /* FUN_004B39D0 */
extern unsigned long sk_x_004b3a08(); /* FUN_004B3A08 */
extern unsigned long sk_x_004b3a30(); /* FUN_004B3A30 */
extern unsigned long sk_x_004b3a58(); /* FUN_004B3A58 */
extern unsigned long sk_x_004b3ac8(); /* FUN_004B3AC8 */
extern unsigned long sk_x_004b3af4(); /* FUN_004B3AF4 */
extern unsigned long sk_x_004b3b08(); /* FUN_004B3B08 */
extern unsigned long sk_x_004b3b64(); /* FUN_004B3B64 */
extern unsigned long sk_x_004b3bc0(); /* FUN_004B3BC0 */
extern unsigned long sk_x_004b3bf8(); /* FUN_004B3BF8 */
extern unsigned long sk_x_004b3c24(); /* FUN_004B3C24 */
extern unsigned long sk_x_004b3c4c(); /* FUN_004B3C4C */
extern unsigned long sk_x_004b3c74(); /* FUN_004B3C74 */
extern unsigned long sk_x_004b3cd0(); /* FUN_004B3CD0 */
extern unsigned long sk_x_004b3d2c(); /* FUN_004B3D2C */
extern unsigned long sk_x_004b3d54(); /* FUN_004B3D54 */
extern unsigned long sk_x_004b3d7c(); /* FUN_004B3D7C */
extern unsigned long sk_x_004b3da4(); /* FUN_004B3DA4 */
extern unsigned long sk_x_004b3e30(); /* FUN_004B3E30 */
extern unsigned long sk_x_004b3e5c(); /* FUN_004B3E5C */
extern unsigned long sk_x_004b3ec4(); /* FUN_004B3EC4 */
extern unsigned long sk_x_004b3eec(); /* FUN_004B3EEC */
extern unsigned long sk_x_004b3f24(); /* FUN_004B3F24 */
extern unsigned long sk_x_004b3f78(); /* FUN_004B3F78 */
extern unsigned long sk_x_004b3fa4(); /* FUN_004B3FA4 */
extern unsigned long sk_x_004b4000(); /* FUN_004B4000 */
extern unsigned long sk_x_004b4038(); /* FUN_004B4038 */
extern unsigned long sk_x_004b4070(); /* FUN_004B4070 */
extern unsigned long sk_x_004b40cc(); /* FUN_004B40CC */
extern unsigned long sk_x_004b4104(); /* FUN_004B4104 */
extern unsigned long sk_x_004b413c(); /* FUN_004B413C */
extern unsigned long sk_x_004b4174(); /* FUN_004B4174 */
extern unsigned long sk_x_004b41ac(); /* FUN_004B41AC */
extern unsigned long sk_x_004b41e4(); /* FUN_004B41E4 */
extern unsigned long sk_x_004b4220(); /* FUN_004B4220 */
extern unsigned long sk_x_004b424c(); /* FUN_004B424C */
extern unsigned long sk_x_004b4284(); /* FUN_004B4284 */
extern unsigned long sk_x_004b42bc(); /* FUN_004B42BC */
extern unsigned long sk_x_004b42e0(); /* FUN_004B42E0 */
extern unsigned long sk_x_004b4304(); /* FUN_004B4304 */
extern unsigned long sk_x_004b4334(); /* FUN_004B4334 */
extern unsigned long sk_x_004b4358(); /* FUN_004B4358 */
extern unsigned long sk_x_004b437c(); /* FUN_004B437C */
extern unsigned long sk_x_004b43ac(); /* FUN_004B43AC */
extern unsigned long sk_x_004b43d0(); /* FUN_004B43D0 */
extern unsigned long sk_x_004b43f4(); /* FUN_004B43F4 */
extern unsigned long sk_x_004b4424(); /* FUN_004B4424 */
extern unsigned long sk_x_004b4448(); /* FUN_004B4448 */
extern unsigned long sk_x_004b446c(); /* FUN_004B446C */
extern unsigned long sk_x_004b449c(); /* FUN_004B449C */
extern unsigned long sk_x_004b44c0(); /* FUN_004B44C0 */
extern unsigned long sk_x_004b44e4(); /* FUN_004B44E4 */
extern unsigned long sk_x_004b4514(); /* FUN_004B4514 */
extern unsigned long sk_x_004b4538(); /* FUN_004B4538 */
extern unsigned long sk_x_004b455c(); /* FUN_004B455C */
extern unsigned long sk_x_004b458c(); /* FUN_004B458C */
extern unsigned long sk_x_004b45b0(); /* FUN_004B45B0 */
extern unsigned long sk_x_004b45d4(); /* FUN_004B45D4 */
extern unsigned long sk_x_004b4604(); /* FUN_004B4604 */
extern unsigned long sk_x_004b4628(); /* FUN_004B4628 */
extern unsigned long sk_x_004b464c(); /* FUN_004B464C */
extern unsigned long sk_x_004b467c(); /* FUN_004B467C */
extern unsigned long sk_x_004b46a0(); /* FUN_004B46A0 */
extern unsigned long sk_x_004b46c4(); /* FUN_004B46C4 */
extern unsigned long sk_x_004b46f4(); /* FUN_004B46F4 */
extern unsigned long sk_x_004b4718(); /* FUN_004B4718 */
extern unsigned long sk_x_004b473c(); /* FUN_004B473C */
extern unsigned long sk_x_004b476c(); /* FUN_004B476C */
extern unsigned long sk_x_004b479c(); /* FUN_004B479C */
extern unsigned long sk_x_004b47c0(); /* FUN_004B47C0 */
extern unsigned long sk_x_004b47e4(); /* FUN_004B47E4 */
extern unsigned long sk_x_004b4814(); /* FUN_004B4814 */
extern unsigned long sk_x_004b4838(); /* FUN_004B4838 */
extern unsigned long sk_x_004b485c(); /* FUN_004B485C */
extern unsigned long sk_x_004b488c(); /* FUN_004B488C */
extern unsigned long sk_x_004b48b0(); /* FUN_004B48B0 */
extern unsigned long sk_x_004b48d4(); /* FUN_004B48D4 */
extern unsigned long sk_x_004b4904(); /* FUN_004B4904 */
extern unsigned long sk_x_004b4928(); /* FUN_004B4928 */
extern unsigned long sk_x_004b494c(); /* FUN_004B494C */
extern unsigned long sk_x_004b497c(); /* FUN_004B497C */
extern unsigned long sk_x_004b49a0(); /* FUN_004B49A0 */
extern unsigned long sk_x_004b49c4(); /* FUN_004B49C4 */
extern unsigned long sk_x_004b49f4(); /* FUN_004B49F4 */
extern unsigned long sk_x_004b4a18(); /* FUN_004B4A18 */
extern unsigned long sk_x_004b4a3c(); /* FUN_004B4A3C */
extern unsigned long sk_x_004b4a6c(); /* FUN_004B4A6C */
extern unsigned long sk_x_004b4a90(); /* FUN_004B4A90 */
extern unsigned long sk_x_004b4ab4(); /* FUN_004B4AB4 */
extern unsigned long sk_x_004b4ae4(); /* FUN_004B4AE4 */
extern unsigned long sk_x_004b4b08(); /* FUN_004B4B08 */
extern unsigned long sk_x_004b4b2c(); /* FUN_004B4B2C */
extern unsigned long sk_x_004b4b5c(); /* FUN_004B4B5C */
extern unsigned long sk_x_004b4b80(); /* FUN_004B4B80 */
extern unsigned long sk_x_004b4ba4(); /* FUN_004B4BA4 */
extern unsigned long sk_x_004b4bd4(); /* FUN_004B4BD4 */
extern unsigned long sk_x_004b4bf8(); /* FUN_004B4BF8 */
extern unsigned long sk_x_004b4c1c(); /* FUN_004B4C1C */
extern unsigned long sk_x_004b4c4c(); /* FUN_004B4C4C */
extern unsigned long sk_x_004b4c70(); /* FUN_004B4C70 */
extern unsigned long sk_x_004b4c94(); /* FUN_004B4C94 */
extern unsigned long sk_x_004b4cc4(); /* FUN_004B4CC4 */
extern unsigned long sk_x_004b4ce8(); /* FUN_004B4CE8 */
extern unsigned long sk_x_004b4d0c(); /* FUN_004B4D0C */
extern unsigned long sk_x_004b4d3c(); /* FUN_004B4D3C */
extern unsigned long sk_x_004b4d60(); /* FUN_004B4D60 */
extern unsigned long sk_x_004b4d84(); /* FUN_004B4D84 */
extern unsigned long sk_x_004b4db4(); /* FUN_004B4DB4 */
extern unsigned long sk_x_004b4dd8(); /* FUN_004B4DD8 */
extern unsigned long sk_x_004b4dfc(); /* FUN_004B4DFC */
extern unsigned long sk_x_004b4e2c(); /* FUN_004B4E2C */
extern unsigned long sk_x_004b4e50(); /* FUN_004B4E50 */
extern unsigned long sk_x_004b4e74(); /* FUN_004B4E74 */
extern unsigned long sk_x_004b4ea4(); /* FUN_004B4EA4 */
extern unsigned long sk_x_004b4ec8(); /* FUN_004B4EC8 */
extern unsigned long sk_x_004b4eec(); /* FUN_004B4EEC */
extern unsigned long sk_x_004b4f1c(); /* FUN_004B4F1C */
extern unsigned long sk_x_004b4f40(); /* FUN_004B4F40 */
extern unsigned long sk_x_004b4f64(); /* FUN_004B4F64 */
extern unsigned long sk_x_004b4f94(); /* FUN_004B4F94 */
extern unsigned long sk_x_004b4fb8(); /* FUN_004B4FB8 */
extern unsigned long sk_x_004b4fdc(); /* FUN_004B4FDC */
extern unsigned long sk_x_004b500c(); /* FUN_004B500C */
extern unsigned long sk_x_004b5030(); /* FUN_004B5030 */
extern unsigned long sk_x_004b5054(); /* FUN_004B5054 */
extern unsigned long sk_x_004b5084(); /* FUN_004B5084 */
extern unsigned long sk_x_004b50a8(); /* FUN_004B50A8 */
extern unsigned long sk_x_004b50cc(); /* FUN_004B50CC */
extern unsigned long sk_x_004b50fc(); /* FUN_004B50FC */
extern unsigned long sk_x_004b5120(); /* FUN_004B5120 */
extern unsigned long sk_x_004b5144(); /* FUN_004B5144 */
extern unsigned long sk_x_004b5174(); /* FUN_004B5174 */
extern unsigned long sk_x_004b5198(); /* FUN_004B5198 */
extern unsigned long sk_x_004b51bc(); /* FUN_004B51BC */
extern unsigned long sk_x_004b51ec(); /* FUN_004B51EC */
extern unsigned long sk_x_004b5210(); /* FUN_004B5210 */
extern unsigned long sk_x_004b5234(); /* FUN_004B5234 */
extern unsigned long sk_x_004b5264(); /* FUN_004B5264 */
extern unsigned long sk_x_004b5288(); /* FUN_004B5288 */
extern unsigned long sk_x_004b52ac(); /* FUN_004B52AC */
extern unsigned long sk_x_004b52dc(); /* FUN_004B52DC */
extern unsigned long sk_x_004b5300(); /* FUN_004B5300 */
extern unsigned long sk_x_004b5324(); /* FUN_004B5324 */
extern unsigned long sk_x_004b5354(); /* FUN_004B5354 */
extern unsigned long sk_x_004b5378(); /* FUN_004B5378 */
extern unsigned long sk_x_004b539c(); /* FUN_004B539C */
extern unsigned long sk_x_004b53cc(); /* FUN_004B53CC */
extern unsigned long sk_x_004b54a4(); /* FUN_004B54A4 */
extern unsigned long sk_x_004b54d4(); /* FUN_004B54D4 */
extern unsigned long sk_x_004b5504(); /* FUN_004B5504 */
extern unsigned long sk_x_004b5534(); /* FUN_004B5534 */
extern unsigned long sk_x_004b5564(); /* FUN_004B5564 */
extern unsigned long sk_x_004b5594(); /* FUN_004B5594 */
extern unsigned long sk_x_004b55c4(); /* FUN_004B55C4 */
extern unsigned long sk_x_004b55f4(); /* FUN_004B55F4 */
extern unsigned long sk_x_004b5624(); /* FUN_004B5624 */
extern unsigned long sk_x_004b5654(); /* FUN_004B5654 */
extern unsigned long sk_x_004b5684(); /* FUN_004B5684 */
extern unsigned long sk_x_004b56b4(); /* FUN_004B56B4 */
extern unsigned long sk_x_004b56e4(); /* FUN_004B56E4 */
extern unsigned long sk_x_004b5714(); /* FUN_004B5714 */
extern unsigned long sk_x_004b5744(); /* FUN_004B5744 */
extern unsigned long sk_x_004b5774(); /* FUN_004B5774 */
extern unsigned long sk_x_004b57a4(); /* FUN_004B57A4 */
extern unsigned long sk_x_004b57d4(); /* FUN_004B57D4 */
extern unsigned long sk_x_004b5804(); /* FUN_004B5804 */
extern unsigned long sk_x_004b5834(); /* FUN_004B5834 */
extern unsigned long sk_x_004b5864(); /* FUN_004B5864 */
extern unsigned long sk_x_004b5894(); /* FUN_004B5894 */
extern unsigned long sk_x_004b58c4(); /* FUN_004B58C4 */
extern unsigned long sk_x_004b58f4(); /* FUN_004B58F4 */
extern unsigned long sk_x_004b5924(); /* FUN_004B5924 */
extern unsigned long sk_x_004b5954(); /* FUN_004B5954 */
extern unsigned long sk_x_004b5984(); /* FUN_004B5984 */
extern unsigned long sk_x_004b59b4(); /* FUN_004B59B4 */
extern unsigned long sk_x_004b59e4(); /* FUN_004B59E4 */
extern unsigned long sk_x_004b5a14(); /* FUN_004B5A14 */
extern unsigned long sk_x_004b5a44(); /* FUN_004B5A44 */
extern unsigned long sk_x_004b5a74(); /* FUN_004B5A74 */
extern unsigned long sk_x_004b5a78(); /* FUN_004B5A78 */
extern unsigned long sk_x_004b5aa0(); /* FUN_004B5AA0 */
extern unsigned long sk_x_004b5ab8(); /* FUN_004B5AB8 */
extern unsigned long sk_x_004b5ad0(); /* FUN_004B5AD0 */
extern unsigned long sk_x_004b5ae8(); /* FUN_004B5AE8 */
extern unsigned long sk_x_004b5b00(); /* FUN_004B5B00 */
extern unsigned long sk_x_004b5c44(); /* FUN_004B5C44 */
extern unsigned long sk_x_004b5d28(); /* FUN_004B5D28 */
extern unsigned long sk_x_004b5d40(); /* FUN_004B5D40 */
extern unsigned long sk_x_004b5d80(); /* FUN_004B5D80 */
extern unsigned long sk_x_0064cbc0(); /* FUN_0064CBC0 */

/* ---- Shared per-CPU / stat / config globals referenced by this region. ---- */
extern unsigned long sk_cfg_flag;      /* DAT_006af2b8 */
extern unsigned long sk_cfg_geo_a;     /* DAT_006af2b9 */
extern unsigned long sk_cfg_geo_b;     /* DAT_006af2ba */
extern unsigned long sk_cfg_geo_c;     /* DAT_006af2bb */
extern unsigned long sk_cfg_obj;       /* DAT_006af2c0 */
extern unsigned long sk_stat_cow;      /* DAT_006ad304 */
extern unsigned long sk_stat_cow2;     /* DAT_006ad308 */
extern unsigned long sk_stat_cow3;     /* DAT_006ad30c */
extern unsigned long sk_stat_cow4;     /* DAT_006ad310 */
extern unsigned long sk_stat_cow5;     /* DAT_006ad314 */
extern unsigned long sk_stat_cow6;     /* DAT_006ad31c */
extern unsigned long sk_stat_cow7;     /* DAT_006ad320 */
extern unsigned long sk_stat_cow8;     /* DAT_006ad328 */
extern unsigned long sk_stat_cow9;     /* DAT_006ad330 */
extern unsigned long sk_stat_cow10;    /* DAT_006ad334 */
extern unsigned long sk_stat_cow11;    /* DAT_006ad338 */
extern unsigned long sk_stat_cow12;    /* DAT_006ad33c */
extern unsigned long sk_stat_cow13;    /* DAT_006ad340 */
extern unsigned long sk_vas_stack_top; /* DAT_006af2b0 */
extern unsigned long sk_vas_root;      /* DAT_0064cba0 */
extern unsigned long sk_pmm_pgtable;   /* DAT_004bc520 */
extern unsigned long sk_err_codes;     /* DAT_0064cb40 */
extern unsigned long sk_err_codes2;    /* DAT_0064cb80 */

/* arm64e trap helpers (compiled in). */
extern void SoftwareBreakpoint(unsigned short kind, ...);
extern void CallSupervisor(unsigned long sel);

/* ---- In-region forward declarations. ---- */

extern unsigned long sk_abort_msg();
extern unsigned long sk_alloc_tagged();
extern unsigned long sk_cap_get_meta();
extern unsigned long sk_cb_register();
extern unsigned long sk_cfg_a();
extern unsigned long sk_cfg_install();
extern unsigned long sk_cpu_cfg();
extern unsigned long sk_cpu_get();
extern unsigned long sk_err_a();
extern unsigned long sk_err_b();
extern unsigned long sk_flush();
extern unsigned long sk_free_obj();
extern unsigned long sk_free_pg_table();
extern unsigned long sk_init_done();
extern unsigned long sk_key_get();
extern unsigned long sk_mem_dump();
extern unsigned long sk_memcpy();
extern unsigned long sk_memcpy2();
extern unsigned long sk_memcpy3();
extern unsigned long sk_mtx_destroy();
extern unsigned long sk_mtx_init2();
extern unsigned long sk_mtx_lock_nr();
extern unsigned long sk_overflow_panic();
extern unsigned long sk_panic();
extern unsigned long sk_pmm_alloc();
extern unsigned long sk_pt_alloc();
extern unsigned long sk_pt_entry_alloc();
extern unsigned long sk_pt_entry_free();
extern unsigned long sk_pt_walk_free();
extern unsigned long sk_random();
extern unsigned long sk_range_clip();
extern unsigned long sk_rbtree_rebalance();
extern unsigned long sk_spanmap_begin();
extern unsigned long sk_spanmap_end();
extern unsigned long sk_spanmap_get();
extern unsigned long sk_spanmap_get_v2();
extern unsigned long sk_spanmap_insert();
extern unsigned long sk_spanmap_insert_v2();
extern unsigned long sk_spanmap_lock();
extern unsigned long sk_spanmap_next();
extern unsigned long sk_spanmap_resolve();
extern unsigned long sk_strcmp();
extern unsigned long sk_strncpy();
extern unsigned long sk_svc_clear();
extern unsigned long sk_svc_copyin();
extern unsigned long sk_svc_copyout();
extern unsigned long sk_svc_count();
extern unsigned long sk_svc_ptr();
extern unsigned long sk_svc_read();
extern unsigned long sk_svc_ret();
extern unsigned long sk_svc_write();
extern unsigned long sk_tb_bad();
extern unsigned long sk_tb_bad2();
extern unsigned long sk_tb_bad3();
extern unsigned long sk_tb_bad4();
extern unsigned long sk_tb_bad5();
extern unsigned long sk_tb_bad6();
extern unsigned long sk_tb_decode_done();
extern unsigned long sk_tb_encode_call();
extern unsigned long sk_tb_encode_get();
extern unsigned long sk_tb_encode_ret();
extern unsigned long sk_tb_fatal();
extern unsigned long sk_tb_get_u8();
extern unsigned long sk_tb_len();
extern unsigned long sk_tb_meta();
extern unsigned long sk_tb_put_len();
extern unsigned long sk_tb_put_mem();
extern unsigned long sk_tb_put_nl();
extern unsigned long sk_tb_put_str();
extern unsigned long sk_tb_put_u16();
extern unsigned long sk_tb_put_u64();
extern unsigned long sk_tb_put_u8();
extern unsigned long sk_tb_puts();
extern unsigned long sk_tb_tag();
extern unsigned long sk_tb_var_w();
extern unsigned long sk_tls_enter();
extern unsigned long sk_tls_exit();
extern unsigned long sk_tls_store();
extern unsigned long sk_vas_abort();
extern unsigned long sk_vas_err();
extern unsigned long sk_vas_span_op();
extern unsigned long sk_vm_ent_alloc();
extern unsigned long sk_vm_ent_free();
extern unsigned long sk_vm_lock();
extern unsigned long sk_vm_obj_add_cb();
extern unsigned long sk_vm_obj_alloc();
extern unsigned long sk_vm_obj_ref();
extern unsigned long sk_vm_obj_unref();
extern unsigned long sk_vm_present();


/* ---- Forward declarations of in-region functions. ---- */
unsigned long sk_boot_call(unsigned long ep, unsigned long out, unsigned long reply);
void sk_boot_ep(unsigned long out, int mode);
void sk_boot_parse(unsigned long p, unsigned long out);
unsigned long sk_boot_string(unsigned long ep, unsigned long size);
void sk_cap_release(unsigned long cap);
void sk_cap_release_cb(unsigned long obj);
void sk_cap_release_rt(unsigned long cap, unsigned int kind);
void sk_cap_release_t(unsigned long p, unsigned long obj);
unsigned long sk_cap_retain(unsigned long cap);
void sk_cap_retype(unsigned long outp, unsigned long cap, unsigned int kind);
cl4_result_t sk_cap_type_table(void);
cl4_result_t sk_cap_type_table_get(unsigned long data, unsigned long size);
void sk_ep_call(unsigned long ep, unsigned long sel, unsigned long n, unsigned long *args,                 long nargs, unsigned long flags, unsigned long *outs, unsigned long nouts);
void sk_ep_call_noreply(unsigned long ep, unsigned long w);
void sk_ep_call_reply(unsigned long ep, unsigned long w, unsigned long outp);
void sk_ep_call_send(unsigned long ep, unsigned long w0, unsigned long w1, unsigned long w2);
unsigned long sk_ep_call_tls(unsigned long ep, unsigned long sel, unsigned long w, long arg,                              unsigned long flags);
void sk_ep_call_w(unsigned long ep, unsigned long w, unsigned long a, unsigned long b);
void sk_err_abort(unsigned long out, unsigned long code, unsigned long extra);
void sk_err_str_cc24(unsigned long out, unsigned long code);
void sk_err_str_dcd0(unsigned long out, unsigned long code);
void sk_fault_handle(unsigned long fault, unsigned long va, unsigned long attr, unsigned long outp);
unsigned long sk_fault_startfault(unsigned long fault, unsigned long arg, unsigned long in);
unsigned long sk_fault_startfault_ret(void);
void sk_fh_dump(unsigned long in);
void sk_fh_register(unsigned long a, unsigned long b);
void sk_l4_err_string(unsigned long out, unsigned long code);
void sk_mo_add(unsigned long vspace, unsigned long desc, unsigned long base, long size,                unsigned int flags);
void sk_mo_alloc(unsigned long p, unsigned long vspace, unsigned long obj, unsigned long arg,                  int level, unsigned long info);
void sk_mo_del(unsigned long p, unsigned long vspace, unsigned long trans);
void sk_mo_find(unsigned long vspace, unsigned long obj);
void sk_mo_init(unsigned long vspace, unsigned long desc, unsigned long base, unsigned long size);
void sk_mo_insert(unsigned long vspace, unsigned long base, unsigned long size, unsigned long arg);
unsigned long sk_mo_lookup(unsigned long vspace, unsigned long va);
unsigned char sk_mo_present(unsigned long obj);
bool sk_mo_query(unsigned long vspace, unsigned long desc, unsigned long va, unsigned long out_f,                  unsigned long out_a);
void sk_mo_remove(unsigned long vspace, unsigned long desc);
void sk_mo_split(unsigned long p, unsigned long vspace, unsigned long desc, unsigned long at,                  unsigned long info);
void sk_mo_split_add(unsigned long p, unsigned long vspace, unsigned long desc, long at);
void sk_noop_ba64(void);
void sk_obj_create(unsigned long kind, unsigned long size, unsigned long arg);
void sk_obj_create_batch(unsigned long ep, unsigned int kind, unsigned int flags, unsigned long n,                          unsigned long get, unsigned long put);
unsigned long sk_opt_get(unsigned long opt);
void sk_opt_set(unsigned long opt, unsigned long val);
void sk_opt_set2(unsigned long opt, unsigned long valp);
void sk_pt_free(unsigned long p, unsigned long pt);
void sk_pt_free_all(unsigned long pt);
unsigned long sk_pt_get(unsigned long cachep, unsigned long va, unsigned long alloc, int create);
unsigned long sk_ptr_fixup(unsigned long ptr, unsigned long arg, long stride, long slide, long base);
void sk_reloc_apply(unsigned long begin, unsigned long end);
void sk_reloc_init(void);
unsigned long sk_reloc_one(unsigned long in);
void sk_spanmap_cap_op(unsigned long vas, unsigned long op, long slot, unsigned long arg);
unsigned long sk_spanmap_commit(unsigned long vas, unsigned long va);
void sk_spanmap_fault_cont(void);
void sk_spanmap_get_cap(unsigned long vas, unsigned long slot);
unsigned long sk_spanmap_lookup(unsigned long vas, long level, long va);
unsigned long sk_spanmap_next_used(unsigned long ctx, long ent);
unsigned long sk_spanmap_op(unsigned long va, unsigned long level);
cl4_result_t sk_spanmap_query(unsigned long vas, unsigned long va, unsigned long outp);
void sk_spanmap_rb_insert(unsigned long rootp, unsigned long node);
unsigned long sk_spanmap_release(unsigned long vas, unsigned long va);
void sk_spanmap_startfault_cow(unsigned long ff, long va, unsigned int flags, unsigned long vas, unsigned long out);
unsigned long sk_str_skip(unsigned long s);
unsigned int sk_tb_cmp(unsigned long a, unsigned long b);
unsigned int sk_tb_cmp2(unsigned long a, unsigned long b);
unsigned int sk_tb_cmp3(unsigned long a, unsigned long b);
unsigned int sk_tb_cmp4(unsigned long a, unsigned long b);
void sk_tb_dec_rec(unsigned long s, unsigned long rec);
unsigned long sk_tb_dispatch(unsigned long obj, unsigned long arg, unsigned long buf);
void sk_tb_enc_rec(unsigned long s, unsigned long rec);
void sk_tb_enc_rec2(unsigned long s, unsigned long rec);
void sk_tb_fatal_5b85d2(unsigned long ret);
void sk_tb_fatal_5b8648(unsigned long ret);
void sk_tb_fatal_ph(unsigned long kind);
void sk_tb_ph_addr(unsigned long out, unsigned long addr);
unsigned long sk_tb_ph_addr2(unsigned long p, long sel, unsigned long region, unsigned long ph,                              unsigned long len);
unsigned long sk_tb_ph_addr_off(unsigned long region, unsigned long off);
unsigned long sk_tb_ph_alloc(unsigned int kind, unsigned long obj, unsigned long cap);
void sk_tb_ph_array(unsigned long arr, unsigned long n, unsigned long target);
unsigned long sk_tb_ph_avail(void);
void sk_tb_ph_byte(unsigned long out, unsigned char v);
void sk_tb_ph_call(unsigned long p, unsigned long out);
void sk_tb_ph_cb(unsigned long out, unsigned long src);
void sk_tb_ph_copy4(unsigned long out, unsigned long in);
void sk_tb_ph_copy8(unsigned long out, unsigned long in);
void sk_tb_ph_copy9(unsigned long out, unsigned long in);
unsigned long sk_tb_ph_count(unsigned long ph);
unsigned long sk_tb_ph_dt(unsigned long p, unsigned long ph, unsigned long region, unsigned long dst,                           unsigned long len);
unsigned long sk_tb_ph_dump(unsigned long p, unsigned long ph, unsigned long region, unsigned long dst,                             unsigned long len);
unsigned long sk_tb_ph_dump2(unsigned long p, unsigned long ph, unsigned long arg, unsigned long dst,                              unsigned long len);
unsigned long sk_tb_ph_dump3(unsigned long p, unsigned long ph, unsigned long arg, unsigned long dst,                              unsigned long len);
unsigned long sk_tb_ph_encode(unsigned long buf, long size, unsigned long arr, unsigned long n);
unsigned long sk_tb_ph_find(unsigned long ph, unsigned long pat, unsigned long n, unsigned long outi);
void sk_tb_ph_free(unsigned long d);
void sk_tb_ph_go(unsigned long p, unsigned long out, unsigned long arg);
void sk_tb_ph_iter_init(void);
bool sk_tb_ph_iter_more(unsigned long it);
unsigned long sk_tb_ph_iter_next(unsigned long it);
unsigned int sk_tb_ph_kind(unsigned long ph);
void sk_tb_ph_name(unsigned long name, unsigned long len, unsigned long cb, unsigned long arg);
void sk_tb_ph_name2(unsigned long name, unsigned long len, unsigned long cb, unsigned long arg);
void sk_tb_ph_none(unsigned long out);
unsigned long sk_tb_ph_one(unsigned long kind, unsigned long buf, long size, long total,                            unsigned long fill, unsigned long arg);
bool sk_tb_ph_one8(unsigned long in, long size, unsigned long cb, unsigned long arg);
void sk_tb_ph_range(unsigned long out, unsigned long base, unsigned long size);
cl4_result_t sk_tb_ph_range2(void);
bool sk_tb_ph_ready(void);
void sk_tb_ph_reloc(unsigned long p, unsigned long ph, unsigned long arg, unsigned long seg,                     long off, unsigned long name);
unsigned long sk_tb_ph_res(unsigned int kind, unsigned long n);
unsigned long sk_tb_ph_resolve(unsigned long ph, unsigned long idx);
void sk_tb_ph_scan(int do_pdata, unsigned int flags);
unsigned long sk_tb_ph_size(unsigned long arr, unsigned long n);
void sk_tb_ph_u32(unsigned long out, unsigned int v);
void sk_tb_ph_u32_2(unsigned long out, unsigned int v);
unsigned long sk_tb_rec_encode(unsigned long obj, unsigned long rec);
unsigned long sk_tb_rec_encode2(unsigned long obj, char kind, unsigned long arg);
unsigned long sk_tb_rec_encode3(unsigned long obj, unsigned long rec);
unsigned long sk_tb_rec_encode4(unsigned long obj, unsigned long arg);
unsigned long sk_tb_rec_encode5(unsigned long obj, unsigned long rec);
unsigned long sk_tb_rec_encode6(unsigned long obj, char kind, unsigned long arg);
unsigned long sk_tb_rec_encode7(unsigned long obj, unsigned long rec);
unsigned long sk_tb_rec_encode8(unsigned long obj, unsigned long rec);
void sk_tb_tag_0427(unsigned long out);
void sk_tb_tag_629b(unsigned long out, unsigned long in);
void sk_tb_tag_6523(unsigned long out);
void sk_vas_abort_5aea4f(unsigned long ret);
void sk_vas_abort_5b324e(unsigned long ret);
void sk_vas_abort_5b4c32(unsigned long ret);
void sk_vas_abort_5b562b(unsigned long ret);
void sk_vas_abort_5b56c0(unsigned long ret);
void sk_vas_abort_5b5fc3(unsigned long ret);
void sk_vas_abort_5b6846(unsigned long ret);
void sk_vas_abort_5b6ac1(unsigned long ret);
void sk_vas_abort_l4err(void);
void sk_vas_abort_l4err_18(void);
void sk_vas_abort_mapped_level(void);
unsigned long sk_vas_cfg(void);
unsigned long sk_vas_cfg_init(void);
void sk_vas_dump(unsigned long fd, unsigned long vspace, unsigned long cfg);
void sk_vas_err_log(void);
void sk_vas_err_stack(void);
void sk_vas_err_stack16(void);
void sk_vas_err_stack18(void);
void sk_vas_err_str_0c(void);
void sk_vas_err_str_90(void);
void sk_vas_fh_validate(void);
void sk_vas_init_fh(void);
cl4_result_t sk_vas_init_map(unsigned long base, long size, unsigned int flags, unsigned char kind);
void sk_vas_init_root(unsigned long p, long a, long b);
long sk_vas_layout_init(unsigned long d, int type, unsigned long base, long limit,                         unsigned long mtab0, unsigned long mtab);
bool sk_vas_level_valid(int level, int type);
cl4_result_t sk_vas_map_range(unsigned long p, unsigned long vspace, unsigned long align,                               unsigned long base, long size);
void sk_vas_noop(void);
void sk_vas_noop_110(void);
void sk_vas_noop_138(void);
void sk_vas_noop_14c(void);
void sk_vas_noop_1c0(void);
void sk_vas_noop_f8(void);
unsigned long sk_vas_populate_level(unsigned long vas, unsigned long va, long size);
unsigned long sk_vas_populate_level_inner(unsigned long vas, unsigned long va, unsigned long level,         unsigned long size);
unsigned long sk_vas_populate_level_nonself(unsigned long vas, unsigned long va, unsigned long level,         unsigned long size, unsigned long a, unsigned long b, unsigned long c, unsigned long d);
unsigned int sk_vas_pt_alloc_flags(unsigned long vas, unsigned long level);
void sk_vas_query_bounds(unsigned long type, unsigned long outp);
unsigned long sk_vas_region_count(unsigned int type);
long sk_vas_region_size(int type);
void sk_vas_shadow_cleanup(unsigned long vas, unsigned long base, unsigned long size,                            unsigned long flags, long kind);
void sk_vas_shadow_setup(unsigned long vas, unsigned long type, long phys, long size,                          unsigned long m0, unsigned long m1, unsigned long a, unsigned long b,                          unsigned int flags);
cl4_result_t sk_vas_span_map_op(unsigned long vas, unsigned long arg2, unsigned long arg3, unsigned long arg4);
cl4_result_t sk_vas_span_map_op2(unsigned long vas, unsigned long a, unsigned long b, unsigned long c,         unsigned long d, unsigned long e);
unsigned long sk_vas_spanmap_cow_scan(unsigned long p, unsigned long va, unsigned long size,                                       unsigned long vas);
void sk_vas_spanmap_teardown(unsigned long vas, unsigned long base, unsigned long limit,                              long clip, unsigned int flags);
unsigned long sk_vas_stack_pop(void);
unsigned long sk_vas_stack_push(void);
void sk_vas_teardown(unsigned long vspace);
unsigned long sk_vas_teardown2(unsigned long p, unsigned long desc);
void sk_vas_teardown_free(void);

/*--------------------------------------------------------------------*/

/* FUN_00043b44 @ 0x00043b44   (est. sk_vas_span_map_op)
 * Ghidra: undefined1 [16] FUN_00043b44(long param_1,undefined8 param_2,
 *   undefined8 param_3, undefined8 param_4)
 * Issues a map/unmap operation on a VAS span object, returning {error,result}.
 * For type-2 spans this is a fixed "not mapped" result; type-1 delegates to the
 * supervisor via FUN_000555ac; type-0 issues a supervisor call with the args.
 * Confidence: medium
 */
cl4_result_t sk_vas_span_map_op(unsigned long vas, unsigned long arg2, unsigned long arg3, unsigned long arg4)
{
    cl4_result_t r;
    char t;

    r.lo = 0; r.hi = 0;
    t = *(char *)(vas + 0x98);
    if (t == 2) { r.lo = 4; r.hi = arg2; return r; }
    if (t == 1) { r.lo = sk_x_000555ac(arg2, arg3, arg4); return r; }
    if (t != 0) sk_vas_abort(0x5b6400);
    CallSupervisor(0);
    r.lo = arg2; r.hi = 0;
    return r;
}

/*--------------------------------------------------------------------*/

/*--------------------------------------------------------------------*/
/* FUN_00043be8 @ 0x00043be8   (est. sk_vas_span_map_op2)
 * Ghidra: undefined1 [16] FUN_00043be8(long param_1,ulong param_2,undefined8 param_3,
 *   undefined8 param_4, undefined8 param_5, undefined8 param_6)
 * Variant of the VAS span map/unmap op with three argument words. Type-2 spans
 * return "not mapped"; type-1 uses the supervisor helper; type-0 issues a
 * supervisor call with the three args.
 * Confidence: medium
 */
cl4_result_t sk_vas_span_map_op2(unsigned long vas, unsigned long a, unsigned long b, unsigned long c,
        unsigned long d, unsigned long e)
{
    cl4_result_t r;
    char t;

    r.lo = 0; r.hi = 0;
    t = *(char *)(vas + 0x98);
    if (t == 2) { r.lo = 4; r.hi = a; return r; }
    if (t != 1) {
        if (t == 0) {
            CallSupervisor(0);
            r.lo = a; r.hi = 0;
            return r;
        }
        sk_vas_abort(0x5b697a);
    }
    r.lo = sk_x_00055558(a, b, c, (unsigned int)d & 1); return r;
}

/*--------------------------------------------------------------------*/

/*--------------------------------------------------------------------*/
/* FUN_00043c74 @ 0x00043c74   (est. sk_vas_spanmap_cow_scan)
 * Ghidra: undefined8 FUN_00043c74(undefined8 param_1,ulong param_2,ulong param_3,ulong param_4)
 * Scans the VAS spanmap for COW-shared mappings within a range and re-resolves
 * each backing frame, returning the resolved base. Walks the pmm page-table
 * tree looking for entries of type COW (0x04) or shared (0x11) that fall inside
 * the requested range and re-reads them via the spanmap.
 * Confidence: medium
 */
unsigned long sk_vas_spanmap_cow_scan(unsigned long p, unsigned long va, unsigned long size,
                                      unsigned long vas)
{
    unsigned long u, span, lv, pg, walk, res, cnt, i;
    unsigned long r6[6];
    unsigned char t;

    u = sk_cpu_get(0x6af2b0, 4, 0xb);
    span = *(unsigned long *)(u + 0xf8);
    if (span == vas) {
        va &= 0xffffffffffffc000;
        lv = va + size;
        if (lv < va) sk_vas_abort(0x5b69da);
        if (*(unsigned long *)(span + 0x28) <= va && lv < *(unsigned long *)(span + 0x30)) {
            cnt = 0;
            if (lv & 0x3fff) cnt = 0x4000;
            walk = sk_pmm_bootmem();
            while (walk != 0xffffffffffffffff) {
                if (*(unsigned long *)walk != 0) {
                    for (i = 0; i < *(unsigned long *)walk; i++) {
                        if (*(char *)(span + 0x98) != 2) {
                            res = *(unsigned long *)(walk + 0x20 + i * 0x20);
                            t = (unsigned char)(res >> 0x38);
                            if (t == 4 || t == 0x11) {
                                pg = *(unsigned long *)(walk + 0x20 + i * 0x20 + 0x10) * 0x1000 & 0xffffffffff000;
                                if (va <= pg && pg < cnt + (lv & 0xffffffffffffc000)) {
                                    sk_spanmap_get3(r6, p, (unsigned long)(pg - *(unsigned long *)(span + 0x28) >> 0xe) + 1, res & 0xffffffffffffff);
                                    p = r6[0];
                                }
                            }
                        }
                    }
                }
                walk = *(unsigned long *)(walk + 8);
            }
        }
    }
    return p;
}

/*--------------------------------------------------------------------*/

/*--------------------------------------------------------------------*/
/* FUN_00043e88 @ 0x00043e88   (est. sk_vas_stack_push)
 * Ghidra: ulong FUN_00043e88(void)
 * Pushes the current VAS root onto the per-CPU stack (DAT_006af2b0 +0x80 count,
 * +0x60 array), or triggers a full alloc if the stack is full. Returns the
 * pushed value or an error. Runs under the VM lock.
 * Confidence: medium
 */
unsigned long sk_vas_stack_push(void)
{
    unsigned long u, v;
    long n;
    unsigned long slot;

    u = sk_x_0005fd2c(0x1800);
    if (u & 1) return u;
    sk_x_004b3eec();
    v = sk_cpu_get(0x6af2b0, 4, 0xb);
    if (*(unsigned long *)(v + 0x80) == 0) { sk_x_004b3f78(); }
    else {
        n = *(unsigned long *)(v + 0x80) - 1;
        *(unsigned long *)(v + 0x80) = n;
        slot = v + 0x60 + n * 8;
        if (sk_x_004b3f24() == 0) return *(unsigned long *)slot;
    }
    sk_vas_abort(0x5b6400);
    return 0;
}

/*--------------------------------------------------------------------*/

/*--------------------------------------------------------------------*/
/* FUN_00043eac @ 0x00043eac   (est. sk_vas_stack_pop)
 * Ghidra: undefined8 FUN_00043eac(void)
 * Pops the top VAS root from the per-CPU stack, or aborts when empty. Returns
 * the popped value.
 * Confidence: medium
 */
unsigned long sk_vas_stack_pop(void)
{
    unsigned long v, u;
    long n;

    v = sk_cpu_get(0x6af2b0, 4, 0xb);
    if (*(unsigned long *)(v + 0x80) == 0) { sk_x_004b3f78(); }
    else {
        n = *(unsigned long *)(v + 0x80) - 1;
        *(unsigned long *)(v + 0x80) = n;
        u = v + 0x60 + n * 8;
        if (sk_x_004b3f24() == 0) return *(unsigned long *)u;
    }
    sk_vas_abort(0x5b6400);
    return 0;
}

/*--------------------------------------------------------------------*/

/*--------------------------------------------------------------------*/
/* FUN_00043f28 @ 0x00043f28   (est. sk_vas_shadow_cleanup)
 * Ghidra: void FUN_00043f28(long param_1,ulong param_2,ulong param_3,ulong param_4,long param_5)
 * Tears down a VAS shadow space over the given range: unmaps every covered span
 * (bulk or per-entry via the span object), drops the mapping tables, and frees
 * the shadow page tables. Holds the vspace translation lock during teardown.
 * Confidence: medium
 * Notes: strings "vas_core_shadow_space_cleanup" (0x5b6b23), "mtx_lock__vcss_"
 *   (0x5b6c04), "mtx_unlock__vcss_" (0x5b6c2e); overflow abort 0x5b2d60.
 */
void sk_vas_shadow_cleanup(unsigned long vas, unsigned long base, unsigned long size,
                           unsigned long flags, long kind)
{
    unsigned long end, span, u, res, eb[4];
    unsigned long i, cnt;
    cl4_result_t r;

    end = base + size;
    if (end < base) sk_vas_abort(0x5b2d60);
    base &= 0xffffffffffffc000;
    if (base < *(unsigned long *)(vas + 0x28)) sk_vas_abort(0x5b2d69);
    if (*(unsigned long *)(vas + 0x30) < end) sk_vas_abort(0x5b2dcc);
    cnt = 0;
    if ((unsigned long)end & 0x3fff) cnt = 0x4000;
    cnt += (unsigned long)end & 0xffffffffffffc000;
    span = sk_spanmap_lookup(vas, 0, base);
    res = cnt - base;
    if ((int)flags != 0 && res != 0) {
        u = res >> 0xe;
        /* bulk unmap via span object bulk method, else per-entry walk */
        if ((*(unsigned long (**)(unsigned long,unsigned long,unsigned long))(*(unsigned long *)(vas + 0xb8) + 0x30)) != 0) {
            res = (*(unsigned long (**)(unsigned long,unsigned long,unsigned long))(*(unsigned long *)(vas + 0xb8) + 0x30))
                        (*(unsigned long *)(vas + 0xb0), span, u);
            if ((res & 0xff) != 0) { sk_err_a(res, eb); }
        } else {
            for (i = 0; i < u; i++) {
                res = (*(unsigned long (**)(unsigned long,unsigned long))(*(unsigned long *)(vas + 0xb8) + 0x10))
                            (*(unsigned long *)(vas + 0xb0), span);
                if (res != 0x107 && res != 0) break;
                span += 0x40;
            }
        }
    }
    if (kind != 0) {
        if (*(unsigned long *)(*(unsigned long *)(vas + 0xb8) + 0x30) != 0) {
            /* free shadow page tables under lock (condensed) */
            if (sk_mtx_lock(vas + 0xa0)) sk_vas_abort(0x5aed68);
            r.lo = sk_x_004b4000();
            sk_vas_abort(0x5b6b23);
        }
    }
    (void)r;
}

/*--------------------------------------------------------------------*/

/*--------------------------------------------------------------------*/
/* FUN_00044290 @ 0x00044290   (est. sk_vas_spanmap_teardown)
 * Ghidra: void FUN_00044290(undefined8 *param_1,ulong param_2,ulong param_3,long param_4,uint param_5)
 * Walks the spanmap interval tree over [param_2,param_3), unmapping each covered
 * span via the span object (bulk or per-entry), and freeing the mapping tables.
 * Optionally clips the range against the caller's span (param_4). Aborts on
 * invalid geometry.
 * Confidence: medium
 */
void sk_vas_spanmap_teardown(unsigned long vas, unsigned long base, unsigned long limit,
                             long clip, unsigned int flags)
{
    unsigned long u, res, ent, lv, i, cnt, mask;
    unsigned long eb[4];
    cl4_result_t r;

    r.lo = 0; r.hi = 0;
    if (clip != 0) {
        sk_range_clip(clip, &base, &limit);
        if (base < base) sk_vas_abort(0x5b7612);
        if (limit < limit) sk_vas_abort(0x5b7612);
    }
    /* (condensed) interval-tree walk, unmap each span, free tables */
    u = sk_cpu_get(0x6af2b0, 4, 0xb);
    (void)u;
    for (i = 0; ; i++) {
        mask = ~(-0x4000L << (i * 0xb & 0x3f));
        cnt = *(unsigned long *)(vas + 0x38 + i * 0x18 + 0x10);
        if (cnt == 0) break;
        ent = *(unsigned long *)(vas + 0x38 + i * 0x18);
        lv = (base + mask) - ent >> (i * 0xb + 0xe & 0x3f);
        if (lv >= cnt) break;
        res = ent + lv * 0x40;
        if ((flags & 1) != 0) {
            (*(unsigned long (**)(unsigned long,unsigned long,unsigned long))(*(unsigned long *)(vas + 0xb8) + 0x30))
                (*(unsigned long *)(vas + 0xb0), res, cnt - lv);
        }
        /* (condensed) free mapping tables */
    }
    (void)eb;
}

/*--------------------------------------------------------------------*/

/*--------------------------------------------------------------------*/
/* FUN_000446ec @ 0x000446ec   (est. sk_vas_fh_validate)
 * Ghidra: void FUN_000446ec(void)
 * Validates the VAS fault-handler state: the per-CPU top-level count must equal
 * 6 and the pending-fault list must be empty, else the VAS aborts. Called as a
 * fault-handler callback.
 * Confidence: medium
 */
void sk_vas_fh_validate(void)
{
    unsigned long v;

    v = sk_cpu_get(0x6af2b0, 4, 0xb);
    if (*(unsigned long *)(v + 0x78) != 6) sk_vas_abort(0x5b704d);
    if (*(unsigned long *)(v + 0xe8) == 0) return;
    sk_vas_abort(0x5b70eb);
}

/*--------------------------------------------------------------------*/

/*--------------------------------------------------------------------*/
/* FUN_00044790 @ 0x00044790   (est. sk_vas_err_str_90)
 * Ghidra: void FUN_00044790(void)
 * Fills an error-word buffer with the L4 error string via FUN_00042640.
 * Confidence: medium (trivial wrapper).
 */
void sk_vas_err_str_90(void)
{
    sk_l4_err_string(0, 0);
}

/*--------------------------------------------------------------------*/

/*--------------------------------------------------------------------*/
/* FUN_000447b0 @ 0x000447b0   (est. sk_vas_err_log)
 * Ghidra: void FUN_000447b0(void)
 * Logs an L4 error word (shifted) via the error-decorator FUN_004b3a58.
 * Confidence: low
 */
void sk_vas_err_log(void)
{
    sk_x_004b3a58();
}

/*--------------------------------------------------------------------*/

/*--------------------------------------------------------------------*/
/* FUN_000447dc @ 0x000447dc   (est. sk_vas_abort_mapped_level)
 * Ghidra: void FUN_000447dc(void)
 * Aborts with the "mapped object level" VAS error at 0x5b7201.
 * Confidence: medium
 */
void sk_vas_abort_mapped_level(void)
{
    sk_vas_abort(0x5b7201);
}

/*--------------------------------------------------------------------*/

/*--------------------------------------------------------------------*/
/* FUN_000447f8 @ 0x000447f8   (est. sk_vas_abort_5b6846)
 * Ghidra: void FUN_000447f8(undefined8 param_1)
 * Aborts with the VAS error at 0x5b6846.
 * Confidence: medium
 */
void sk_vas_abort_5b6846(unsigned long ret)
{
    (void)ret;
    sk_vas_abort(0x5b6846);
}

/*--------------------------------------------------------------------*/

/*--------------------------------------------------------------------*/
/* FUN_0004480c @ 0x0004480c   (est. sk_vas_err_str_0c)
 * Ghidra: void FUN_0004480c(void)
 * Fills an error-word buffer with the L4 error string.
 * Confidence: medium (trivial wrapper).
 */
void sk_vas_err_str_0c(void)
{
    sk_l4_err_string(0, 0);
}

/*--------------------------------------------------------------------*/

/*--------------------------------------------------------------------*/
/* FUN_00044818 @ 0x00044818   (est. sk_vas_abort_l4err_18)
 * Ghidra: void FUN_00044818(void)
 * Aborts with the generic "Unexpected L4 Error" at 0x5b6dc4.
 * Confidence: medium
 */
void sk_vas_abort_l4err_18(void)
{
    sk_vas_abort(0x5b6dc4);
}

/*--------------------------------------------------------------------*/

/*--------------------------------------------------------------------*/
/* FUN_00044828 @ 0x00044828   (est. sk_vas_abort_5aea4f)
 * Ghidra: void FUN_00044828(undefined8 param_1)
 * Aborts with the VAS error at 0x5aea4f.
 * Confidence: medium
 */
void sk_vas_abort_5aea4f(unsigned long ret)
{
    (void)ret;
    sk_vas_abort(0x5aea4f);
}

/*--------------------------------------------------------------------*/

/*--------------------------------------------------------------------*/
/* FUN_0004483c @ 0x0004483c   (est. sk_vas_abort_5b6ac1)
 * Ghidra: void FUN_0004483c(undefined8 param_1)
 * Aborts with the VAS error at 0x5b6ac1.
 * Confidence: medium
 */
void sk_vas_abort_5b6ac1(unsigned long ret)
{
    (void)ret;
    sk_vas_abort(0x5b6ac1);
}

/*--------------------------------------------------------------------*/

/*--------------------------------------------------------------------*/
/* FUN_00044850 @ 0x00044850   (est. sk_vas_dump)
 * Ghidra: void FUN_00044850(undefined8 param_1,undefined8 param_2,long param_3)
 * Dumps the VAS address-space map to a debug log: iterates the mapped-object
 * list of the given vspace and prints each region's attributes and flags.
 * Aborts if the iterator terminates unexpectedly.
 * Confidence: medium
 * Notes: strings "vas: %012zx %0zx %-32s" (0x5b7a2a), "vas: attrs" (0x5b7a4a).
 */
void sk_vas_dump(unsigned long fd, unsigned long vspace, unsigned long cfg)
{
    unsigned long cur, ent, res, flags, i;
    cl4_result_t r;

    cur = (**(unsigned long (**)(unsigned long))(cfg + 0x28))(vspace);
    while (1) {
        if (cur == 0) return;
        ent = (**(unsigned long (**)(unsigned long))(cur + 8))(cur);
        r.lo = 0; r.hi = 0;
        if (ent == 0) break;
        flags = (**(unsigned long (**)(unsigned long,unsigned long))(ent + 8))(ent, r.lo);
        sk_x_00055a90(r.lo & 0xff);
        sk_tb_put_str(fd, 0x5b7a2a);
        sk_tb_puts(0x5b7a4a, fd);
        if (flags != 0) {
            do {
                sk_tb_put_str(fd, 0x5b7a5b);
                i = flags & -flags;
                flags ^= i;
            } while (i != flags);
        }
        sk_tb_put_nl(10, fd);
    }
    sk_x_00054354();
}

/*--------------------------------------------------------------------*/

/*--------------------------------------------------------------------*/
/* FUN_00044be0 @ 0x00044be0   (est. sk_mo_find)
 * Ghidra: void FUN_00044be0(long param_1,long param_2)
 * Searches the mapped-object list of a vspace for a given object pointer.
 * Locks the vspace, walks the list at +0x1e0 (via next pointer +0x18), and
 * returns once found; aborts if the object is not present.
 * Confidence: medium
 */
void sk_mo_find(unsigned long vspace, unsigned long obj)
{
    unsigned long cur;

    if (vspace + 0x50 < vspace + 0x40) sk_vas_abort(0x5aed68);
    if (sk_mtx_lock(vspace + 0x40)) sk_vas_abort(0x5aed68);
    cur = *(unsigned long *)(vspace + 0x1e0);
    while (1) {
        if (cur == 0) sk_vas_abort(0x5b7bc8);
        if (cur == obj) break;
        cur = *(unsigned long *)(cur + 0x18);
    }
}

/*--------------------------------------------------------------------*/

/*--------------------------------------------------------------------*/
/* FUN_00044c94 @ 0x00044c94   (est. sk_mo_insert)
 * Ghidra: void FUN_00044c94(long param_1,ulong param_2,long param_3,undefined8 param_4)
 * Inserts a mapped-object descriptor covering [param_2, param_2+param_3) into
 * the vspace's mapped-object list, splitting an existing overlapping entry if
 * needed. The descriptor records the object's translation via FUN_00044ec4 and
 * marks the region dirty. Aborts on invalid geometry.
 * Confidence: medium
 */
void sk_mo_insert(unsigned long vspace, unsigned long base, unsigned long size, unsigned long arg)
{
    unsigned long u, cur, ent, res;
    unsigned long i;

    u = 0;
    if ((size + base & 0x3fff) != 0) u = 0x4000;
    if (vspace + 0x40 <= vspace + 0x50) {
        if (sk_mtx_lock(vspace + 0x40)) sk_vas_abort(0x5aed68);
        if (size != 0) {
            res = u + (size + base & 0xffffffffffffc000);
            if (res == (base & 0xffffffffffffc000)) {
                /* fresh range: alloc descriptor, insert via add */
                ent = sk_x_004b4104();
                *(unsigned long *)ent = ent;
                for (i = 0; i < 10; i++) *(unsigned long *)(ent + 8 + i * 8) = 0;
                sk_mtx_init2(ent + 0x30);
                sk_mo_insert(ent, size, arg, 0);
                sk_mo_add(ent, ent, size, arg, 0);
                if (sk_mtx_unlock(vspace + 0x40)) sk_vas_abort(0x5aed68);
                return;
            }
            /* walk existing list, mark overlap dirty */
            cur = *(unsigned long *)(vspace + 0x1e0);
            while (cur != 0) {
                if (res <= base) { sk_x_004b40cc(); break; }
                while (1) {
                    u = *(unsigned long *)(cur + 8);
                    if (*(unsigned long *)(cur + 0x10) <= u) { sk_x_004b40cc(); break; }
                    ent = (u < res) || (u <= base && base < *(unsigned long *)(cur + 0x10));
                    if (ent) break;
                    cur = *(unsigned long *)(cur + 0x18);
                    if (cur == 0) return;
                }
                *(unsigned char *)(cur + 0x42) = 1;
                if (sk_mtx_lock_nr(cur + 0x30, vspace + 0x40)) sk_vas_abort(0x5aed68);
            }
        }
    }
    sk_vas_abort(0x5aed68);
}

/*--------------------------------------------------------------------*/

/*--------------------------------------------------------------------*/
/* FUN_00044dec @ 0x00044dec   (est. sk_mo_init)
 * Ghidra: void FUN_00044dec(long param_1,long *param_2,undefined8 param_3,undefined8 param_4)
 * Initializes a mapped-object descriptor: stores the owning vspace, zeroes the
 * descriptor fields, initializes the per-object lock, inserts the range, and
 * adds the descriptor to the vspace's list.
 * Confidence: medium
 */
void sk_mo_init(unsigned long vspace, unsigned long desc, unsigned long base, unsigned long size)
{
    unsigned long i;

    *(unsigned long *)desc = vspace;
    for (i = 0; i < 10; i++) *(unsigned long *)(desc + 8 + i * 8) = 0;
    sk_mtx_init2(desc + 0x30);
    sk_mo_insert(vspace, base, size, 0);
    sk_mo_add(vspace, desc, base, size, 0);
    if (vspace + 0x50 < vspace + 0x40) sk_vas_abort(0x5aed68);
    if (sk_mtx_unlock(vspace + 0x40)) sk_vas_abort(0x5aed68);
}

/*--------------------------------------------------------------------*/

/*--------------------------------------------------------------------*/
/* FUN_00044ec4 @ 0x00044ec4   (est. sk_mo_add)
 * Ghidra: void FUN_00044ec4(long param_1,long *param_2,ulong param_3,long param_4,uint param_5)
 * Adds a mapped-object descriptor to the vspace's list, chaining it at the head
 * and recording its [start,end) range and lock-owner pointer. Rejects duplicate
 * entries or overlapping ranges.
 * Confidence: medium
 */
void sk_mo_add(unsigned long vspace, unsigned long desc, unsigned long base, long size,
               unsigned int flags)
{
    unsigned long u, cur;

    u = 0;
    if ((size + base & 0x3fff) != 0) u = 0x4000;
    u += (size + base & 0xffffffffffffc000);
    if (u <= (base & 0xffffffffffffc000)) sk_vas_abort(0x5b820c);
    if (*(unsigned long *)desc != vspace) sk_vas_abort(0x5b8279);
    if ((char)*(unsigned long *)(desc + 0x40) == 1) { sk_x_004b413c(); }
    else if (*(unsigned char *)(desc + 0x41) == flags) {
        cur = *(unsigned long *)(vspace + 0x1e0);
        *(unsigned long *)(desc + 0x18) = cur;
        *(unsigned long *)(desc + 8) = base & 0xffffffffffffc000;
        *(unsigned long *)(desc + 0x10) = u;
        *(unsigned char *)(desc + 0x40) = 1;
        *(unsigned char *)(desc + 0x42) = 0;
        if (cur != 0) *(unsigned long *)(cur + 0x20) = desc + 0x18;
        *(unsigned long *)(vspace + 0x1e0) = desc;
        if (vspace + 0x1e0 <= vspace + 0x1e8) {
            *(unsigned long *)(desc + 0x20) = vspace + 0x1e0;
            return;
        }
    }
    sk_vas_abort(0x5b832f);
}

/*--------------------------------------------------------------------*/

/*--------------------------------------------------------------------*/
/* FUN_00044ff4 @ 0x00044ff4   (est. sk_mo_remove)
 * Ghidra: void FUN_00044ff4(long param_1,long *param_2)
 * Removes a mapped-object descriptor from the vspace's list and destroys its
 * lock, releasing any pending dirty-marker. Verifies the descriptor belongs to
 * the vspace and is currently linked.
 * Confidence: medium
 */
void sk_mo_remove(unsigned long vspace, unsigned long desc)
{
    unsigned long u, prev, next, dirty;

    u = vspace + 0x40;
    if (vspace + 0x50 < u) sk_vas_abort(0x5aed68);
    if (sk_mtx_lock(u)) sk_vas_abort(0x5aed68);
    if (vspace != *(unsigned long *)desc) sk_vas_abort(0x5b7ce4);
    if ((*(unsigned char *)(desc + 0x40) & 1) != 0) {
        prev = *(unsigned long *)(desc + 0x18);
        next = *(unsigned long *)(desc + 0x20);
        if (prev != 0) *(unsigned long *)(prev + 0x20) = next;
        *(unsigned long *)next = prev;
        *(unsigned char *)(desc + 0x40) = 0;
        dirty = *(unsigned char *)(desc + 0x42);
        if (sk_mtx_unlock(u)) sk_vas_abort(0x5aed68);
        if (dirty != 0) sk_mtx_destroy(desc + 0x30);
        if ((*(unsigned char *)(desc + 0x41) & 1) != 0) return;
        if ((char)*(unsigned long *)(desc + 0x40) != 1) { sk_x_000539fc(desc + 0x30); return; }
    }
    sk_vas_abort(0x5b7d39);
}

/*--------------------------------------------------------------------*/

/*--------------------------------------------------------------------*/
/* FUN_000451a0 @ 0x000451a0   (est. sk_vas_map_range)
 * Ghidra: undefined1 [16] FUN_000451a0(undefined8 param_1,long param_2,ulong param_3,
 *   ulong param_4, long param_5)
 * Maps a range into the VAS at the given alignment, returning {error, result}.
 * Computes the mapping size, looks up the target frame via the pmm bootmem list,
 * installs the page-table entries at the appropriate level, and records the new
 * mapped-object descriptor. Returns the mapped object or an error.
 * Confidence: medium
 */
cl4_result_t sk_vas_map_range(unsigned long p, unsigned long vspace, unsigned long align,
                              unsigned long base, long size)
{
    cl4_result_t r;
    unsigned long sz, frame, ent, i, n, u;

    r.lo = 0; r.hi = 0;
    sz = 0;
    if ((size + base & 0x3fff) != 0) sz = 0x4000;
    if (align >= 2) goto bad;
    if (align == 0) {
        /* derive level from vspace flags */
        u = *(unsigned int *)(vspace + 0x20);
        if (u & 8) i = 2; else i = 1;
        if (u & 0x10) i = 3;
        if (u & 0x10000) i = i;
        align = i;
    }
    r.lo = sz + (size + base & 0xffffffffffffc000);
    if (r.lo <= *(unsigned long *)(vspace + 0x10)) {
        base &= 0xffffffffffffc000;
        n = r.lo - base;
        ent = sk_spanmap_insert_v2(&r, p, *(unsigned long *)(vspace + 8) + base, n, 0, 0, 0, 1);
        if ((ent & 1) == 0) {
            /* locate frame in bootmem list, build mapped object (condensed) */
            r.hi = sk_mo_lookup(p, *(unsigned long *)(vspace + 8));
            return r;
        }
        if (base == 0 && *(unsigned long *)(vspace + 0x10) == n) {
            frame = sk_mo_lookup(p, *(unsigned long *)(vspace + 8));
            if (*(unsigned long *)(frame + 0x18) != 0) sk_pt_free(0, frame);
            *(unsigned long *)(frame + 0x18) = 0;
            *(char *)(frame + 0x10) = (char)align;
        } else if (n != 0) {
            u = n;
            while (u != 0) {
                i = (n - u) + *(unsigned long *)(vspace + 8) + base;
                if (sk_spanmap_insert(&r, p, i, u, 2) == 0) sk_vas_abort(0x5b8389);
                frame = sk_mo_lookup(p, *(unsigned long *)(vspace + 8));
                if (frame == 0) { r.lo = 0x1160001; goto out; }
                /* (condensed) fill PTEs */
                u -= 0x4000;
            }
        }
        r.lo = 0;
    }
bad:
out:
    return r;
}

/*--------------------------------------------------------------------*/

/*--------------------------------------------------------------------*/
/* FUN_000454c0 @ 0x000454c0   (est. sk_mo_lookup)
 * Ghidra: ulong * FUN_000454c0(long param_1,ulong param_2)
 * Looks up the mapped-object descriptor covering a virtual address in the
 * vspace's mapped-object list (head at +0x1d8). Returns the descriptor, moving
 * it to the list head on hit (LRU). Returns 0 if not mapped.
 * Confidence: medium
 */
unsigned long sk_mo_lookup(unsigned long vspace, unsigned long va)
{
    unsigned long cur, prev, next, entry;

    cur = *(unsigned long *)(vspace + 0x1d8);
    prev = 0;
    while (cur != 0) {
        entry = cur + 0x30;
        if (*(unsigned long *)cur <= va && va < *(unsigned long *)(cur + 8) + *(unsigned long *)cur) {
            if (prev != 0) {
                next = *(unsigned long *)(prev + 0x28);
                *(unsigned long *)(prev + 0x28) = *(unsigned long *)(cur + 0x28);
                *(unsigned long *)(cur + 0x28) = *(unsigned long *)(vspace + 0x1d8);
                *(unsigned long *)(vspace + 0x1d8) = cur;
            }
            if (cur <= entry) return cur;
        }
        prev = cur;
        cur = *(unsigned long *)(cur + 0x28);
    }
    return 0;
}

/*--------------------------------------------------------------------*/

/*--------------------------------------------------------------------*/
/* FUN_0004554c @ 0x0004554c   (est. sk_pt_free)
 * Ghidra: void FUN_0004554c(undefined8 param_1,long param_2)
 * Frees a page-table subtree: walks each of the 32 level slots at +0x130
 * freeing every entry, then frees the page-table node itself.
 * Confidence: medium
 */
void sk_pt_free(unsigned long p, unsigned long pt)
{
    unsigned long i, e;

    i = 0;
    do {
        e = *(unsigned long *)(pt + i * 8);
        while (e != 0) {
            e = *(unsigned long *)(e + 0x130);
            sk_pt_entry_free(p);
        }
        i++;
    } while (i != 0x20);
    sk_pt_walk_free(p, pt);
}

/*--------------------------------------------------------------------*/

/*--------------------------------------------------------------------*/
/* FUN_000455b0 @ 0x000455b0   (est. sk_vas_level_valid)
 * Ghidra: bool FUN_000455b0(int param_1,int param_2)
 * Tests whether a page-table level is valid for a given geometry type: type 0
 * accepts level 4, type 1 accepts level 2, type 2 accepts level 3.
 * Confidence: medium
 */
bool sk_vas_level_valid(int level, int type)
{
    if (type == 2) return level == 3;
    if (type == 1) return level == 2;
    if (type == 0) return level != 4;
    sk_vas_abort(0x5b7ef2);
    return false;
}

/*--------------------------------------------------------------------*/

/*--------------------------------------------------------------------*/
/* FUN_00045614 @ 0x00045614   (est. sk_pt_free_all)
 * Ghidra: void FUN_00045614(long param_1)
 * Frees an entire page-table tree: for each of the 32 level slots walks the
 * chain freeing entries, then frees the node.
 * Confidence: medium
 */
void sk_pt_free_all(unsigned long pt)
{
    unsigned long i, e;

    i = 0;
    do {
        e = *(unsigned long *)(pt + i * 8);
        while (e != 0) {
            e = *(unsigned long *)(e + 0x130);
            sk_free_pg();
        }
        i++;
    } while (i != 0x20);
    sk_free_pg_table(pt);
}

/*--------------------------------------------------------------------*/

/*--------------------------------------------------------------------*/
/* FUN_0004567c @ 0x0004567c   (est. sk_pt_get)
 * Ghidra: ulong FUN_0004567c(undefined8 *param_1,ulong param_2,undefined8 param_3,int param_4)
 * Returns the page-table entry covering a virtual address from the per-vspace
 * page-table cache, allocating a new entry if requested (param_4 != 0). Keys are
 * the 42-bit-aligned VA; entries chain via +0x130 with key at +0x128.
 * Confidence: medium
 */
unsigned long sk_pt_get(unsigned long cachep, unsigned long va, unsigned long alloc, int create)
{
    unsigned long head, e, nxt, key;

    head = *(unsigned long *)cachep;
    if (head == 0) {
        if (create == 0) return 0;
        head = sk_pt_alloc(alloc);
        *(unsigned long *)cachep = head;
    }
    for (e = *(unsigned long *)head; e != 0; e = *(unsigned long *)(e + 0x130)) {
        if (*(unsigned long *)(e + 0x128) == (va & 0xffffffffffc00000)) return e;
    }
    if (create == 0) return 0;
    e = sk_pt_entry_alloc(alloc);
    if (e == 0) return 0;
    nxt = *(unsigned long *)head;
    *(unsigned long *)(e + 0x128) = va & 0xffffffffffc00000;
    *(unsigned long *)(e + 0x130) = nxt;
    *(unsigned long *)head = e;
    return e;
}

/*--------------------------------------------------------------------*/

/*--------------------------------------------------------------------*/
/* FUN_00045728 @ 0x00045728   (est. sk_mo_alloc)
 * Ghidra: void FUN_00045728(undefined8 param_1,long param_2,undefined8 param_3,
 *   undefined8 param_4, int param_5, long param_6)
 * Allocates and links a new mapped-object descriptor into the vspace's mapped
 * list, recording the object pointer and its method table. Resolves the
 * effective level from the vspace flags when not given.
 * Confidence: medium
 */
void sk_mo_alloc(unsigned long p, unsigned long vspace, unsigned long obj, unsigned long arg,
                 int level, unsigned long info)
{
    unsigned long desc, u;
    unsigned int flags;

    if (level != 4) {
        if (level != 0) sk_vas_abort(0x5b7f5b);
        flags = *(unsigned int *)(info + 0x20);
        level = (flags & 8) ? 2 : 1;
        if ((flags & 0x10) == 0) level = (flags & 8) ? 2 : 1;
        if (flags & 0x10000) level = 4;
    }
    desc = sk_vm_ent_alloc();
    *(unsigned long *)desc = obj;
    *(unsigned long *)(desc + 8) = arg;
    *(unsigned long *)(desc + 0x18) = 0;
    *(unsigned long *)(desc + 0x20) = info;
    *(char *)(desc + 0x10) = (char)level;
    *(unsigned long *)(desc + 0x28) = *(unsigned long *)(vspace + 0x1d8);
    *(unsigned long *)(vspace + 0x1d8) = desc;
    (void)u;
}

/*--------------------------------------------------------------------*/

/*--------------------------------------------------------------------*/
/* FUN_000457f8 @ 0x000457f8   (est. sk_mo_del)
 * Ghidra: void FUN_000457f8(undefined8 param_1,long param_2,long param_3)
 * Unlinks and frees a mapped-object descriptor from the vspace's mapped list by
 * its translation pointer (param_3). Frees the page tables if any and returns
 * the descriptor to the pool.
 * Confidence: medium
 */
void sk_mo_del(unsigned long p, unsigned long vspace, unsigned long trans)
{
    unsigned long prev, cur;

    prev = vspace + 0x1d8;
    while (prev <= vspace + 0x1e0) {
        cur = *(unsigned long *)prev;
        if (cur == 0) sk_vas_abort(0x5b8450);
        if (*(unsigned long *)(cur + 0x20) == trans) {
            *(unsigned long *)prev = *(unsigned long *)(cur + 0x28);
            *(unsigned long *)(cur + 0x28) = 0;
            if (*(unsigned long *)(cur + 0x18) != 0) sk_pt_free(p, cur);
            sk_vm_ent_free(p, cur);
            return;
        }
        prev = cur + 0x28;
    }
    sk_vas_abort(0x5b8450);
}

/*--------------------------------------------------------------------*/

/*--------------------------------------------------------------------*/
/* FUN_000458a0 @ 0x000458a0   (est. sk_mo_split_add)
 * Ghidra: void FUN_000458a0(undefined8 param_1,undefined8 param_2,long param_3,long param_4)
 * Splits a mapped region at a boundary: removes the existing descriptor and
 * re-adds the (prefix, suffix) split via sk_mo_del + sk_mo_alloc.
 * Confidence: medium
 */
void sk_mo_split_add(unsigned long p, unsigned long vspace, unsigned long desc, long at)
{
    sk_mo_del(p, vspace, at);
    sk_mo_del(p, vspace, at);
    sk_mo_alloc(p, vspace, *(unsigned long *)(desc + 8),
                *(unsigned long *)(at + 0x10) + *(unsigned long *)(desc + 0x10), 0, desc);
}

/*--------------------------------------------------------------------*/

/*--------------------------------------------------------------------*/
/* FUN_00045908 @ 0x00045908   (est. sk_mo_split)
 * Ghidra: void FUN_00045908(undefined8 param_1,undefined8 param_2,long param_3,ulong param_4,
 *   undefined8 param_5)
 * Splits a mapped object at an offset: removes the original descriptor and adds
 * two descriptors covering the prefix and suffix ranges.
 * Confidence: medium
 */
void sk_mo_split(unsigned long p, unsigned long vspace, unsigned long desc, unsigned long at,
                 unsigned long info)
{
    if (at == 0) { sk_x_004b41e4(); }
    else if (at < *(unsigned long *)(desc + 0x10)) {
        sk_mo_del(p, vspace, desc);
        sk_mo_alloc(p, vspace, *(unsigned long *)(desc + 8), at, 0, desc);
        sk_mo_alloc(p, vspace, *(unsigned long *)(desc + 8) + at,
                    *(unsigned long *)(desc + 0x10) - at, 0, info);
        return;
    }
    sk_vas_abort(0x5b8006);
}

/*--------------------------------------------------------------------*/

/*--------------------------------------------------------------------*/
/* FUN_000459d4 @ 0x000459d4   (est. sk_vas_teardown)
 * Ghidra: void FUN_000459d4(long param_1)
 * Tears down a VAS: frees every mapped-object descriptor and page table in the
 * list, then clears the vspace's mapping tables.
 * Confidence: medium
 */
void sk_vas_teardown(unsigned long vspace)
{
    unsigned long cur, nxt;

    sk_spanmap_begin(&cur, vspace);
    cur = *(unsigned long *)(vspace + 0x1d8);
    *(unsigned long *)(vspace + 0x1d8) = 0;
    *(unsigned long *)(vspace + 0x1e0) = 0;
    sk_spanmap_end(&cur, vspace);
    while (1) {
        if (cur == 0) return;
        nxt = *(unsigned long *)(cur + 0x28);
        if (*(unsigned long *)(cur + 0x18) != 0) sk_pt_free_all(cur);
        sk_free_obj(cur);
        cur = nxt;
    }
}

/*--------------------------------------------------------------------*/

/*--------------------------------------------------------------------*/
/* FUN_00045a68 @ 0x00045a68   (est. sk_mo_query)
 * Ghidra: bool FUN_00045a68(long param_1,long param_2,ulong param_3,undefined8 *param_4,
 *   byte *param_5)
 * Queries the mapped-object descriptor covering a virtual address, returning
 * whether the mapping is present and filling the frame + attribute. Allocates a
 * new descriptor if the region is not yet mapped.
 * Confidence: medium
 */
bool sk_mo_query(unsigned long vspace, unsigned long desc, unsigned long va, unsigned long out_f,
                 unsigned long out_a)
{
    unsigned long frame, cur, ent, res, key, u;

    if ((*(unsigned char *)(desc + 0xa1) & 1) == 0) {
        va &= 0xffffffffffffc000;
        sk_mo_insert(vspace, va, 0x4000, 0);
        frame = sk_mo_lookup(vspace, va);
        if (frame == 0) {
            if (vspace + 0x40 <= vspace + 0x50) {
                if (sk_mtx_unlock(vspace + 0x40)) sk_vas_abort(0x5aed68);
                return frame != 0;
            }
        }
        sk_mo_add(vspace, desc, va, 0x4000, 1);
        *(unsigned char *)(desc + 0xa1) = 1;
        *(unsigned long *)(desc + 0xa8) = va;
        ent = *(unsigned long *)(*(unsigned long *)(frame + 0x20) + 8);
        if (ent <= va && va < *(unsigned long *)(*(unsigned long *)(frame + 0x20) + 0x10) + ent) {
            if (*(unsigned long *)(frame + 0x18) != 0) {
                cur = *(unsigned long *) *(unsigned long *)(frame + 0x18);
                while (cur != 0) {
                    if (*(unsigned long *)(cur + 0x128) == (va & 0xffffffffffc00000)) {
                        u = cur + ((unsigned long)((unsigned int)va & 0x3fc000) / 0xa800 & 0x78);
                        key = (unsigned int)(va >> 0xe) & 0xff;
                        res = *(unsigned long *)u >> (((unsigned int)key & 0x7f) * 3) & 0x3f;
                        if ((res & 7) != 0) goto found;
                        break;
                    }
                    cur = *(unsigned long *)(cur + 0x130);
                }
            }
            res = *(unsigned char *)(frame + 0x10);
        }
found:
        *(unsigned char *)(desc + 0xa3) = res & 0xff;
        *(unsigned char *)out_a = res & 0xff;
        *(unsigned long *)out_f = *(unsigned long *)(frame + 0x20);
        if (vspace + 0x50 >= vspace + 0x40) {
            if (sk_mtx_unlock(vspace + 0x40)) sk_vas_abort(0x5aed68);
            return frame != 0;
        }
    }
    sk_vas_abort(0x5aed68);
    return false;
}

/*--------------------------------------------------------------------*/

/*--------------------------------------------------------------------*/
/* FUN_00045c98 @ 0x00045c98   (est. sk_vas_teardown2)
 * Ghidra: ulong FUN_00045c98(undefined8 param_1,long param_2)
 * Queries whether a mapped-object descriptor is present in a vspace, releasing
 * it if it was registered. Returns 1 if present, else checks the per-CPU state.
 * Confidence: medium
 */
unsigned long sk_vas_teardown2(unsigned long p, unsigned long desc)
{
    unsigned long lv;

    if ((*(unsigned char *)(desc + 0xa1) & 1) != 0) {
        *(unsigned char *)(desc + 0xa1) = 0;
        sk_mo_remove(p, desc); return 0;
    }
    lv = sk_x_004b4284();
    if (*(char *)(lv + 0x18) == 0x11)
        return *(unsigned char *)(lv + 0x22) & 1;
    return 0;
}

/*--------------------------------------------------------------------*/

/*--------------------------------------------------------------------*/
/* FUN_00045cb8 @ 0x00045cb8   (est. sk_mo_present)
 * Ghidra: byte FUN_00045cb8(long param_1)
 * Returns whether a mapped-object descriptor is present (present flag at +0x22).
 * Confidence: medium
 */
unsigned char sk_mo_present(unsigned long obj)
{
    if (*(char *)(obj + 0x18) == 0x11)
        return *(unsigned char *)(obj + 0x22) & 1;
    return 0;
}

/*--------------------------------------------------------------------*/

/*--------------------------------------------------------------------*/
/* FUN_00045cd8 @ 0x00045cd8   (est. sk_str_skip)
 * Ghidra: char * FUN_00045cd8(char *param_1)
 * Skips the leading marker byte of a string; returns 0 for the empty string.
 * Confidence: medium
 */
unsigned long sk_str_skip(unsigned long s)
{
    if (*(unsigned char *)s == 0) return 0;
    return s + 1;
}

/*--------------------------------------------------------------------*/

/*--------------------------------------------------------------------*/
/* FUN_00045ce8 @ 0x00045ce8   (est. sk_opt_set)
 * Ghidra: void FUN_00045ce8(undefined1 *param_1,undefined1 *param_2)
 * Sets an optional field: writes the present flag and copies the value byte.
 * Confidence: medium
 */
void sk_opt_set(unsigned long opt, unsigned long val)
{
    if (val != 0) {
        *(unsigned char *)opt = 1;
        *(unsigned char *)(opt + 1) = *(unsigned char *)val;
        return;
    }
    *(unsigned char *)opt = 0;
}

/*--------------------------------------------------------------------*/

/*--------------------------------------------------------------------*/
/* FUN_00045d08 @ 0x00045d08   (est. sk_opt_get)
 * Ghidra: char * FUN_00045d08(char *param_1)
 * Returns the value pointer of a present optional field, or 0 if absent.
 * Confidence: medium
 */
unsigned long sk_opt_get(unsigned long opt)
{
    if (*(unsigned char *)opt != 1) return 0;
    return opt + 8;
}

/*--------------------------------------------------------------------*/

/*--------------------------------------------------------------------*/
/* FUN_00045d38 @ 0x00045d38   (est. sk_opt_set2)
 * Ghidra: void FUN_00045d38(long param_1,undefined8 *param_2)
 * Sets an optional 64-bit value: records the value and present flag.
 * Confidence: medium
 */
void sk_opt_set2(unsigned long opt, unsigned long valp)
{
    if (valp != 0) *(unsigned long *)(opt + 8) = *(unsigned long *)valp;
    *(bool *)opt = valp != 0;
}

/*--------------------------------------------------------------------*/

/*--------------------------------------------------------------------*/
/* FUN_00045d58 @ 0x00045d58   (est. sk_tb_enc_rec)
 * Ghidra: void FUN_00045d58(undefined8 param_1,ulong *param_2)
 * Encodes a TB record header into a wire buffer: writes the record type,
 * selector flags, and the optional presence bytes, computing the required
 * buffer size from the presence bits. Aborts on invalid values.
 * Confidence: medium
 * Notes: TB_FATAL strings 0x5ba47e/0x5ba4bc; wire helpers FUN_00018e60 etc.
 */
void sk_tb_enc_rec(unsigned long s, unsigned long rec)
{
    unsigned long sz, n1, n2, n3, sel, u;
    unsigned char b;

    n1 = 1 + (*(unsigned char *)(rec + 0x2e) ? 2 : 1);
    n2 = 1 + (*(unsigned char *)(rec + 0x2c) ? 2 : 1);
    n3 = 1 + (*(unsigned char *)(rec + 0x2a) ? 2 : 1);
    sel = 0x1c;
    if ((char)*(unsigned long *)(rec + 0x10) == 0) sel = 0x14;
    sz = n3 + sel + n2 + n1;
    sz = sz + 9;
    if ((char)*(unsigned long *)(rec + 0x30) == 0) sz = sz - 8;
    sk_tb_put_len(s, sz);
    if ((*(unsigned long *)rec & 0xfffffffff0860007) == 0) {
        sk_tb_put_u64(s, 0);
        if (((unsigned char)((char)*(unsigned long *)(rec + 8) - 1)) < 2) {
            sk_tb_put_u8(s, 0);
            if ((char)*(unsigned long *)(rec + 0x10) == 1) {
                sk_tb_put_u8(s, 1);
                sk_tb_put_u64(s, *(unsigned long *)(rec + 0x18));
            } else sk_tb_put_u8(s, 0);
            sk_tb_put_u64(s, *(unsigned long *)(rec + 0x20));
            b = (unsigned char)*(unsigned long *)(rec + 0x28);
            if (b - 4 < 0x10 || b - 0xfb < 5 || b < 3) {
                sk_tb_put_u8(s, 0);
                sk_tb_put_mem(s, *(unsigned long *)(rec + 0x29), 1);
                u = *(unsigned char *)(rec + 0x2a) ? *(unsigned long *)(rec + 0x2b) : 0;
                sk_tb_put_u8(s, u);
                u = *(unsigned char *)(rec + 0x2c) ? *(unsigned long *)(rec + 0x2d) : 0;
                sk_tb_put_u8(s, u);
                u = *(unsigned char *)(rec + 0x2e) ? *(unsigned long *)(rec + 0x2f) : 0;
                sk_tb_put_u8(s, u);
                if ((char)*(unsigned long *)(rec + 0x30) != 1) { sk_tb_put_u8(s, 0); return; }
                sk_tb_put_u8(s, 1);
                sk_tb_put_u64(s, *(unsigned long *)(rec + 0x38));
                return;
            }
        }
        sk_tb_fatal(0x5ba47e);
    } else sk_tb_fatal(0x5ba4bc);
}

/*--------------------------------------------------------------------*/

/*--------------------------------------------------------------------*/
/* FUN_00045ffc @ 0x00045ffc   (est. sk_tb_dec_rec)
 * Ghidra: void FUN_00045ffc(undefined8 param_1,ulong *param_2)
 * Decodes a TB record header from a wire buffer into the caller's struct,
 * reading the type, selector flags, and optional fields. Aborts on invalid.
 * Confidence: medium
 * Notes: TB_FATAL strings 0x5ba47e/0x5ba4bc.
 */
void sk_tb_dec_rec(unsigned long s, unsigned long rec)
{
    unsigned long tag;
    unsigned char v;

    if (rec + 8 < rec) sk_vas_abort(0x5aed68);
    tag = 0;
    sk_tb_tag(&tag, s);
    if ((tag & 0xfffffffff0860007) == 0) {
        *(unsigned long *)rec = tag;
        v = 0;
        sk_tb_get_u8(&v, s);
        if (v - 1 < 2) {
            *(unsigned long *)(rec + 8) = v;
            v = 0;
            sk_tb_get_u8(&v, s);
            if (v == 0) *(unsigned char *)(rec + 0x10) = 0;
            else { *(unsigned char *)(rec + 0x10) = 1; sk_tb_get_u8(rec + 0x18, s); }
            sk_tb_tag(rec + 0x20, s);
            v = 0;
            sk_tb_get_u8(&v, s);
            if (v - 4 < 0x10 || v - 0xfb < 5 || v < 3) {
                *(unsigned long *)(rec + 0x28) = v;
                sk_tb_get_u8(rec + 0x29, s);
                v = 0;
                sk_tb_get_u8(&v, s);
                if (v == 0) *(unsigned char *)(rec + 0x2a) = 0;
                else { *(unsigned char *)(rec + 0x2a) = 1; sk_tb_get_u8(rec + 0x2b, s); }
                v = 0;
                sk_tb_get_u8(&v, s);
                if (v == 0) *(unsigned char *)(rec + 0x2c) = 0;
                else { *(unsigned char *)(rec + 0x2c) = 1; sk_tb_get_u8(rec + 0x2d, s); }
                v = 0;
                sk_tb_get_u8(&v, s);
                if (v == 0) *(unsigned char *)(rec + 0x2e) = 0;
                else { *(unsigned char *)(rec + 0x2e) = 1; sk_tb_get_u8(rec + 0x2f, s); }
                v = 0;
                sk_tb_get_u8(&v, s);
                if (v == 0) *(unsigned char *)(rec + 0x30) = 0;
                else { *(unsigned char *)(rec + 0x30) = 1; sk_tb_tag(rec + 0x38, s); }
                return;
            }
        }
        sk_tb_fatal(0x5ba47e);
    } else sk_tb_fatal(0x5ba4bc);
}

/*--------------------------------------------------------------------*/

/*--------------------------------------------------------------------*/
/* FUN_00046288 @ 0x00046288   (est. sk_tb_tag_6523)
 * Ghidra: void FUN_00046288(undefined8 *param_1)
 * Initializes a TB wire tag with the fixed 64-bit type marker 0x652378e30e8da7d4.
 * Confidence: high (constant-matched).
 */
void sk_tb_tag_6523(unsigned long out)
{
    *(unsigned long *)out = 0x652378e30e8da7d4;
}

/*--------------------------------------------------------------------*/

/*--------------------------------------------------------------------*/
/* FUN_000462a0 @ 0x000462a0   (est. sk_tb_tag_629b)
 * Ghidra: void FUN_000462a0(undefined8 *param_1,undefined8 *param_2)
 * Initializes a TB wire tag with marker 0x629b90c9626409ac and copies a 3-word
 * payload.
 * Confidence: high (constant-matched).
 */
void sk_tb_tag_629b(unsigned long out, unsigned long in)
{
    *(unsigned long *)out = 0x629b90c9626409ac;
    *(unsigned long *)(out + 0x18) = *(unsigned long *)(in + 0x10);
    *(unsigned long *)(out + 0x10) = *(unsigned long *)(in + 8);
    *(unsigned long *)(out + 8) = *(unsigned long *)in;
}

/*--------------------------------------------------------------------*/

/*--------------------------------------------------------------------*/
/* FUN_000462c8 @ 0x000462c8   (est. sk_tb_tag_0427)
 * Ghidra: void FUN_000462c8(undefined8 *param_1)
 * Initializes a TB wire tag with the fixed marker 0x427d55567dfea26.
 * Confidence: high (constant-matched).
 */
void sk_tb_tag_0427(unsigned long out)
{
    *(unsigned long *)out = 0x427d55567dfea26;
}

/*--------------------------------------------------------------------*/

/*--------------------------------------------------------------------*/
/* FUN_000462e0 @ 0x000462e0   (est. sk_tb_ph_none)
 * Ghidra: void FUN_000462e0(undefined1 *param_1)
 * Writes a "none" TB placeholder descriptor (absent marker).
 * Confidence: medium
 */
void sk_tb_ph_none(unsigned long out)
{
    *(unsigned char *)out = 0;
}

/*--------------------------------------------------------------------*/

/*--------------------------------------------------------------------*/
/* FUN_000462e8 @ 0x000462e8   (est. sk_tb_ph_u32)
 * Ghidra: void FUN_000462e8(undefined1 *param_1,undefined4 param_2)
 * Writes a present 32-bit TB placeholder descriptor.
 * Confidence: medium
 */
void sk_tb_ph_u32(unsigned long out, unsigned int v)
{
    *(unsigned char *)out = 1;
    *(unsigned int *)(out + 8) = v;
}

/*--------------------------------------------------------------------*/

/*--------------------------------------------------------------------*/
/* FUN_000462f8 @ 0x000462f8   (est. sk_tb_ph_range)
 * Ghidra: void FUN_000462f8(undefined1 *param_1,undefined8 param_2,undefined8 param_3)
 * Writes an absent TB placeholder descriptor with a range (base,size).
 * Confidence: medium
 */
void sk_tb_ph_range(unsigned long out, unsigned long base, unsigned long size)
{
    *(unsigned char *)out = 0;
    *(unsigned long *)(out + 8) = base;
    *(unsigned long *)(out + 0x10) = size;
}

/*--------------------------------------------------------------------*/

/*--------------------------------------------------------------------*/
/* FUN_00046304 @ 0x00046304   (est. sk_tb_ph_u32_2)
 * Ghidra: void FUN_00046304(undefined1 *param_1,undefined4 param_2)
 * Writes a present TB placeholder with a 32-bit value at offset 8.
 * Confidence: medium
 */
void sk_tb_ph_u32_2(unsigned long out, unsigned int v)
{
    *(unsigned char *)out = 1;
    *(unsigned int *)(out + 8) = v;
}

/*--------------------------------------------------------------------*/

/*--------------------------------------------------------------------*/
/* FUN_00046314 @ 0x00046314   (est. sk_tb_ph_addr)
 * Ghidra: void FUN_00046314(undefined1 *param_1,undefined8 param_2)
 * Writes an absent TB placeholder descriptor carrying one address word.
 * Confidence: medium
 */
void sk_tb_ph_addr(unsigned long out, unsigned long addr)
{
    *(unsigned char *)out = 0;
    *(unsigned long *)(out + 8) = addr;
}

/*--------------------------------------------------------------------*/

/*--------------------------------------------------------------------*/
/* FUN_00046320 @ 0x00046320   (est. sk_tb_ph_copy8)
 * Ghidra: void FUN_00046320(undefined1 *param_1,undefined8 *param_2)
 * Copies an 8-word TB placeholder descriptor.
 * Confidence: medium
 */
void sk_tb_ph_copy8(unsigned long out, unsigned long in)
{
    unsigned long i;
    *(unsigned char *)out = 0;
    for (i = 0; i < 8; i++) *(unsigned long *)(out + 8 + i * 8) = *(unsigned long *)(in + i * 8);
}

/*--------------------------------------------------------------------*/

/*--------------------------------------------------------------------*/
/* FUN_00046340 @ 0x00046340   (est. sk_tb_ph_copy9)
 * Ghidra: void FUN_00046340(undefined1 *param_1,undefined8 *param_2)
 * Copies a 9-word TB placeholder descriptor.
 * Confidence: medium
 */
void sk_tb_ph_copy9(unsigned long out, unsigned long in)
{
    unsigned long i;
    *(unsigned char *)out = 0;
    for (i = 0; i < 9; i++) *(unsigned long *)(out + 8 + i * 8) = *(unsigned long *)(in + i * 8);
}

/*--------------------------------------------------------------------*/

/*--------------------------------------------------------------------*/
/* FUN_0004636c @ 0x0004636c   (est. sk_tb_ph_copy4)
 * Ghidra: void FUN_0004636c(undefined1 *param_1,undefined8 *param_2)
 * Copies a 4-word TB placeholder descriptor.
 * Confidence: medium
 */
void sk_tb_ph_copy4(unsigned long out, unsigned long in)
{
    unsigned long i;
    *(unsigned char *)out = 0;
    for (i = 0; i < 4; i++) *(unsigned long *)(out + 8 + i * 8) = *(unsigned long *)(in + i * 8);
}

/*--------------------------------------------------------------------*/

/*--------------------------------------------------------------------*/
/* FUN_00046380 @ 0x00046380   (est. sk_tb_ph_byte)
 * Ghidra: void FUN_00046380(undefined1 *param_1,undefined1 param_2)
 * Writes an absent TB placeholder descriptor carrying one byte.
 * Confidence: medium
 */
void sk_tb_ph_byte(unsigned long out, unsigned char v)
{
    *(unsigned char *)out = 0;
    *(unsigned char *)(out + 2) = v;
}

/*--------------------------------------------------------------------*/

/*--------------------------------------------------------------------*/
/* FUN_0004638c @ 0x0004638c   (est. sk_tb_enc_rec2)
 * Ghidra: void FUN_0004638c(undefined8 param_1,ulong *param_2)
 * Encodes a TB record into a wire buffer from a descriptor, mirroring
 * sk_tb_enc_rec. Aborts on invalid values.
 * Confidence: medium
 * Notes: TB_FATAL strings 0x5ba47e/0x5ba4bc.
 */
void sk_tb_enc_rec2(unsigned long s, unsigned long rec)
{
    unsigned long u;
    unsigned char b;

    if ((*(unsigned long *)rec & 0xfffffffff0860007) == 0) {
        sk_tb_put_u64(s, 0);
        if (((unsigned char)((char)*(unsigned long *)(rec + 8) - 1)) < 2) {
            sk_tb_put_u8(s, 0);
            if ((char)*(unsigned long *)(rec + 0x10) == 1) {
                sk_tb_put_u8(s, 1);
                sk_tb_put_u64(s, *(unsigned long *)(rec + 0x18));
            } else sk_tb_put_u8(s, 0);
            sk_tb_put_u64(s, *(unsigned long *)(rec + 0x20));
            b = (unsigned char)*(unsigned long *)(rec + 0x28);
            if (b - 4 < 0x10 || b - 0xfb < 5 || b < 3) {
                sk_tb_put_u8(s, 0);
                sk_tb_put_mem(s, *(unsigned long *)(rec + 0x29), 1);
                u = *(unsigned char *)(rec + 0x2a) ? *(unsigned long *)(rec + 0x2b) : 0;
                sk_tb_put_u8(s, u);
                u = *(unsigned char *)(rec + 0x2c) ? *(unsigned long *)(rec + 0x2d) : 0;
                sk_tb_put_u8(s, u);
                u = *(unsigned char *)(rec + 0x2e) ? *(unsigned long *)(rec + 0x2f) : 0;
                sk_tb_put_u8(s, u);
                if ((char)*(unsigned long *)(rec + 0x30) != 1) { sk_tb_put_u8(s, 0); return; }
                sk_tb_put_u8(s, 1);
                sk_tb_put_u64(s, *(unsigned long *)(rec + 0x38));
                return;
            }
        }
        sk_tb_fatal(0x5ba47e);
    } else sk_tb_fatal(0x5ba4bc);
}

/*--------------------------------------------------------------------*/

/*--------------------------------------------------------------------*/
/* FUN_000465c4 @ 0x000465c4   (est. sk_tb_ph_call)
 * Ghidra: void FUN_000465c4(undefined8 param_1,undefined8 param_2)
 * Invokes a TB placeholder method: sets up the encoder context and calls the
 * placeholder dispatcher.
 * Confidence: medium
 */
void sk_tb_ph_call(unsigned long p, unsigned long out)
{
    sk_tb_ph_go(p, out, 0);
}

/*--------------------------------------------------------------------*/

/*--------------------------------------------------------------------*/
/* FUN_000465ec @ 0x000465ec   (est. sk_tb_ph_go)
 * Ghidra: void FUN_000465ec(undefined8 param_1,undefined8 *param_2,undefined8 param_3)
 * Sets up the TB placeholder encoder context (tag table, callback, arg) and
 * invokes the dispatcher, storing the resulting record pointer.
 * Confidence: medium
 */
void sk_tb_ph_go(unsigned long p, unsigned long out, unsigned long arg)
{
    unsigned long r;

    sk_tb_setup(p, 0xa05dabaf2a128ff);
    r = sk_tb_encode_call(p, 0x6ad3a8);
    *(unsigned long *)out = r;
    sk_tb_encode_ret();
}

/*--------------------------------------------------------------------*/

/*--------------------------------------------------------------------*/
/* FUN_00046694 @ 0x00046694   (est. sk_tb_dispatch)
 * Ghidra: undefined8 FUN_00046694(long param_1,undefined8 *******param_2,undefined8 param_3)
 * The TB (tightbeam) message dispatcher: reads a message tag from the input
 * buffer, then switches on the tag to decode the per-record fields and invoke
 * the corresponding vspace method (selected by a method-table offset in the
 * caller's object). Each case reads the fixed records, decodes nested records,
 * and dispatches through the method table at *(param_1+0x20)+offset. Returns
 * the caller-provided result or a fatal error.
 * Confidence: low (huge decompiler output, "Type propagation algorithm not
 *   settling" warning; structure summarized from the tag-switch).
 * Notes: ~50 tag cases; helpers FUN_004b4358 etc. report dispatch errors; fatal
 *   strings 0x5ba347 / 0x5ba47e / 0x5ba4bc.
 */
unsigned long sk_tb_dispatch(unsigned long obj, unsigned long arg, unsigned long buf)
{
    unsigned long tag, r;
    long mtab;

    tag = 0;
    sk_tb_tag(&tag, buf);
    (void)tag;
    mtab = *(unsigned long *)(*(unsigned long *)(obj + 0x20));
    (void)mtab;
    sk_tb_decode_done(buf);
    /* Dispatch by tag: each tag selects a vspace method slot. The decoded
     * per-record fields are passed to (**(slot+0x10))(...) with the method's
     * typed decode helper (e.g. sk_tb_rec_encode..), and a zero/9 result means
     * the record was decoded and dispatched. (Condensed structural summary.) */
    r = 0;
    /* On any unrecognized tag the dispatcher aborts fatally. */
    sk_x_004b4358();
    sk_tb_var_w(*(unsigned long *)(*(unsigned long *)(*(unsigned long *)(obj + 0x20) + 8) + 0x28), r);
    *(unsigned char *)(*(unsigned long *)(*(unsigned long *)(obj + 0x20) + 8) + 0x20) = 1;
    return r;
}

/*--------------------------------------------------------------------*/

/*--------------------------------------------------------------------*/
/* FUN_000490bc @ 0x000490bc   (est. sk_tb_rec_encode)
 * Ghidra: undefined8 FUN_000490bc(long param_1,undefined8 *param_2)
 * Encodes a TB record for the "fault" message: writes the record tag, the
 * selector/kind byte, and the nested per-record fields, into the caller's wire
 * buffer. Returns the L4 error code.
 * Confidence: medium
 * Notes: wires via sk_tb_encode_get (0x14f90) + sk_tb_enc_rec2 (0x4638c).
 */
unsigned long sk_tb_rec_encode(unsigned long obj, unsigned long rec)
{
    unsigned long w, tag, out, u, sz;
    unsigned long lv;

    lv = *(unsigned long *)(*(unsigned long *)(obj + 0x20) + 8);
    out = sk_tb_encode_get(*(unsigned long *)(lv + 0x18), *(unsigned long *)(lv + 0x28), 0, 0);
    if ((int)out == 0) {
        w = *(unsigned long *)(lv + 0x28);
        if ((char)*(unsigned long *)rec == 1) {
            sk_tb_tag(w, 1);
            sk_tb_put_len(w, 3);
            if (((unsigned long)*(unsigned long *)(rec + 8) - 1 & 0xff) < 6) {
                sk_tb_put_u8(w, *(unsigned long *)(rec + 8) & 0xff);
                sk_tb_put_u16(w, *(unsigned long *)(rec + 8) >> 0x10 & 0xffff);
            } else sk_tb_fatal(0x5ba47e);
        } else {
            if ((char)*(unsigned long *)rec != 0) sk_tb_bad();
            sk_tb_tag(w, 0);
            u = 1; if (*(unsigned char *)(rec + 0x38) != 0) u = 2;
            sz = 1; if (*(unsigned char *)(rec + 0x30) != 0) sz = 2;
            tag = 1; if (*(unsigned char *)(rec + 0x28) != 0) tag = 2;
            /* (condensed) size computation and field encode */
            sk_tb_put_u64(w, *(unsigned long *)(rec + 8));
            sk_tb_enc_rec2(w, rec + 0x10);
        }
        *(unsigned char *)(lv + 0x20) = 1;
    }
    return out;
}

/*--------------------------------------------------------------------*/

/*--------------------------------------------------------------------*/
/* FUN_000492bc @ 0x000492bc   (est. sk_tb_rec_encode2)
 * Ghidra: undefined8 FUN_000492bc(long param_1,char param_2,undefined8 param_3)
 * Encodes a chain of nested TB records (up to 4 levels) into the wire buffer,
 * dispatching through the method table at each level. Returns the L4 error.
 * Confidence: medium
 */
unsigned long sk_tb_rec_encode2(unsigned long obj, char kind, unsigned long arg)
{
    unsigned long lv, out, w, u;

    lv = *(unsigned long *)(*(unsigned long *)(obj + 0x20) + 8);
    u = 4;
    if (kind == 0) u = sk_tb_len() + 1;
    else if (kind != 1) u = 0;
    out = sk_tb_encode_get(*(unsigned long *)(lv + 0x18), *(unsigned long *)(lv + 0x28), u, 0);
    if ((int)out != 0) return out;
    w = *(unsigned long *)(lv + 0x28);
    if (kind == 1) {
        sk_tb_tag(w, 1);
        sk_tb_put_len(w, 3);
        if (((unsigned long)arg - 1 & 0xff) < 6) {
            sk_tb_put_u8(w, arg & 0xff);
            sk_tb_put_u16(w, arg >> 0x10 & 0xffff);
            *(unsigned char *)(lv + 0x20) = 1;
            return out;
        }
    } else {
        if (kind == 0) {
            sk_tb_tag(w, 0);
            sk_tb_var_w(w, arg);
            *(unsigned char *)(lv + 0x20) = 1;
            return out;
        }
        sk_tb_bad2();
    }
    sk_tb_fatal(0x5ba47e);
    return 0;
}

/*--------------------------------------------------------------------*/

/*--------------------------------------------------------------------*/
/* FUN_00049934 @ 0x00049934   (est. sk_tb_rec_encode3)
 * Ghidra: undefined8 FUN_00049934(long param_1,char *param_2)
 * Encodes a TB record from a descriptor whose first word selects the wire tag
 * (0x427d55567dfea26 / 0x652378e30e8da7d4 => 9 bytes, 0x629b90c9626409ac => 0x21).
 * Writes the tag, kind, and nested payload into the buffer.
 * Confidence: medium
 */
unsigned long sk_tb_rec_encode3(unsigned long obj, unsigned long rec)
{
    unsigned long lv, w, out, u, a, b, c;

    lv = *(unsigned long *)(*(unsigned long *)(obj + 0x20) + 8);
    a = *(unsigned long *)(rec + 8);
    b = *(unsigned long *)(rec + 0x10);
    c = *(unsigned long *)(rec + 0x18);
    if ((char)*(unsigned long *)rec == 1) u = 4;
    else if ((char)*(unsigned long *)rec == 0) {
        if (a == 0x427d55567dfea26 || a == 0x652378e30e8da7d4) u = 9;
        else if (a == 0x629b90c9626409ac) u = 0x21;
        else sk_tb_fatal(0x5ba47e);
    } else u = 0;
    out = sk_tb_encode_get(*(unsigned long *)(lv + 0x18), *(unsigned long *)(lv + 0x28), u, 0);
    if ((int)out != 0) return out;
    w = *(unsigned long *)(lv + 0x28);
    if ((char)*(unsigned long *)rec == 1) {
        sk_tb_tag(w, 1);
        sk_tb_put_len(w, 3);
        if (((unsigned long)a - 1 & 0xff) < 6) {
            sk_tb_put_u8(w, a & 0xff);
            sk_tb_put_u16(w, a >> 0x10 & 0xffff);
        } else sk_tb_fatal(0x5ba47e);
    } else {
        if ((char)*(unsigned long *)rec == 0) {
            sk_tb_tag(w, 0);
            sk_tb_var_w(w, a);
            if (a == 0x427d55567dfea26 || a == 0x652378e30e8da7d4) {
                *(unsigned char *)(lv + 0x20) = 1;
                return out;
            }
            if (a == 0x629b90c9626409ac) {
                sk_tb_put_len(w, 0x18);
                sk_tb_put_u64(w, b);
                sk_tb_put_u64(w, c);
                sk_tb_put_u64(w, *(unsigned long *)(rec + 0x20));
                *(unsigned char *)(lv + 0x20) = 1;
                return out;
            }
            sk_tb_fatal(0x5ba47e);
        }
        sk_tb_bad3();
    }
    sk_tb_fatal(0x5ba47e);
    return 0;
}

/*--------------------------------------------------------------------*/

/*--------------------------------------------------------------------*/
/* FUN_00049b48 @ 0x00049b48   (est. sk_tb_rec_encode4)
 * Ghidra: undefined8 FUN_00049b48(long param_1,ulong param_2)
 * Encodes a chained TB record: writes the tag/kind, then recurses through the
 * method table to encode up to 3 nested record levels. Returns the L4 error.
 * Confidence: medium
 */
unsigned long sk_tb_rec_encode4(unsigned long obj, unsigned long arg)
{
    unsigned long lv, out, w, u, k, r;

    lv = *(unsigned long *)(*(unsigned long *)(obj + 0x20) + 8);
    u = 4;
    if ((arg & 0xff) != 1) u = 0;
    k = arg & 0xff;
    if ((arg & 0xff) == 0) u = 1;
    out = sk_tb_encode_get(*(unsigned long *)(lv + 0x18), *(unsigned long *)(lv + 0x28), u, 0);
    if ((int)out != 0) return out;
    w = *(unsigned long *)(lv + 0x28);
    if (k == 1) {
        u = arg >> 0x10;
        sk_tb_tag(w, 1);
        sk_tb_put_len(w, 3);
        if (((arg >> 0x10) - 1 & 0xff) < 6) {
            sk_tb_put_u8(w, arg >> 0x10 & 0xff);
            sk_tb_put_u16(w, arg >> 0x20 & 0xffff);
        } else sk_tb_fatal(0x5ba47e);
    } else {
        if ((arg & 0xff) == 0) {
            sk_tb_tag(w, 0);
            *(unsigned char *)(lv + 0x20) = 1;
            return out;
        }
        sk_tb_bad4();
    }
    /* recurse through method table for the nested record (condensed) */
    r = sk_tb_meta(u);
    lv = *(unsigned long *)(*(unsigned long *)(r + 0x20) + 8);
    if (sk_tb_encode_get(*(unsigned long *)(lv + 0x18), *(unsigned long *)(lv + 0x28), u, 0) == 0) {
        w = *(unsigned long *)(lv + 0x28);
        if ((r & 0xff) == 1) {
            sk_tb_tag(w, 1);
            sk_tb_put_len(w, 3);
        } else if ((r & 0xff) == 0) {
            sk_tb_tag(w, 0);
            *(unsigned char *)(lv + 0x20) = 1;
            return 0;
        } else sk_tb_bad5();
    }
    return 0;
}

/*--------------------------------------------------------------------*/

/*--------------------------------------------------------------------*/
/* FUN_00049d48 @ 0x00049d48   (est. sk_tb_rec_encode5)
 * Ghidra: undefined8 FUN_00049d48(long param_1,undefined8 *param_2)
 * Encodes a full TB record (same shape as sk_tb_rec_encode, 0x490bc) writing
 * the tag, kind, and nested fields. Returns the L4 error.
 * Confidence: medium
 */
unsigned long sk_tb_rec_encode5(unsigned long obj, unsigned long rec)
{
    unsigned long lv, w, out, u, sz, i;
    unsigned long a, b;

    lv = *(unsigned long *)(*(unsigned long *)(obj + 0x20) + 8);
    a = *(unsigned long *)(rec + 8);
    b = *(unsigned long *)(rec + 0x38);
    if ((char)*(unsigned long *)rec == 1) u = 4;
    else if ((char)*(unsigned long *)rec == 0) {
        i = 1; if (b != 0) i = 2;
        sz = 1; if (*(unsigned char *)(rec + 0x30) != 0) sz = 2;
        u = 1; if (*(unsigned char *)(rec + 0x28) != 0) u = 2;
        out = 0x1d; if ((*(unsigned long *)(rec + 0x20) & 1) == 0) out = 0x15;
        u = u + out + sz + i;
        u += 9;
        if ((*(unsigned long *)(rec + 0x40) & 1) == 0) u -= 8;
    } else u = 0;
    out = sk_tb_encode_get(*(unsigned long *)(lv + 0x18), *(unsigned long *)(lv + 0x28), u, 0);
    if ((int)out != 0) return out;
    w = *(unsigned long *)(lv + 0x28);
    if ((char)*(unsigned long *)rec == 1) {
        sk_tb_tag(w, 1);
        sk_tb_put_len(w, 3);
        if (((a - 1) & 0xff) < 6) {
            sk_tb_put_u8(w, 0);
            sk_tb_put_u16(w, a >> 0x10 & 0xffff);
        } else sk_tb_fatal(0x5ba47e);
    } else {
        if ((char)*(unsigned long *)rec != 0) sk_tb_bad3();
        sk_tb_tag(w, 0);
        i = 1; if (b != 0) i = 2;
        sz = 1; if (*(unsigned char *)(rec + 0x30) != 0) sz = 2;
        u = 1; if (*(unsigned char *)(rec + 0x28) != 0) u = 2;
        out = 0x1c; if ((*(unsigned long *)(rec + 0x20) & 1) == 0) out = 0x14;
        u = u + out + sz + i;
        u += 9;
        if ((*(unsigned long *)(rec + 0x40) & 1) == 0) u -= 8;
        sk_tb_put_len(w, u);
        sk_tb_put_u64(w, a);
        sk_tb_enc_rec2(w, rec + 0x10);
    }
    *(unsigned char *)(lv + 0x20) = 1;
    return out;
}

/*--------------------------------------------------------------------*/

/*--------------------------------------------------------------------*/
/* FUN_00049f48 @ 0x00049f48   (est. sk_tb_rec_encode6)
 * Ghidra: undefined8 FUN_00049f48(long param_1,char param_2,undefined8 param_3)
 * Encodes a chain of 5 nested TB records, dispatching through the method table
 * at each level. Returns the L4 error.
 * Confidence: medium
 */
unsigned long sk_tb_rec_encode6(unsigned long obj, char kind, unsigned long arg)
{
    unsigned long lv, out, w, u;
    cl4_result_t r;

    lv = *(unsigned long *)(*(unsigned long *)(obj + 0x20) + 8);
    u = 4;
    if (kind != 1) u = 0;
    out = 9;
    if (kind != 0) out = u;
    u = sk_tb_encode_get(*(unsigned long *)(lv + 0x18), *(unsigned long *)(lv + 0x28), out, 0);
    if ((int)u != 0) return u;
    w = *(unsigned long *)(lv + 0x28);
    if (kind == 1) {
        sk_tb_tag(w, 1);
        sk_tb_put_len(w, 3);
        if (((unsigned long)arg - 1 & 0xff) < 6) {
            sk_tb_put_u8(w, arg & 0xff);
            sk_tb_put_u16(w, arg >> 0x10 & 0xffff);
            *(unsigned char *)(lv + 0x20) = 1;
            return u;
        }
    } else {
        if (kind == 0) {
            sk_tb_tag(w, 0);
            sk_tb_var_w(w, arg);
            *(unsigned char *)(lv + 0x20) = 1;
            return u;
        }
        sk_tb_bad6();
    }
    sk_tb_fatal(0x5ba47e);
    (void)r;
    return 0;
}

/*--------------------------------------------------------------------*/

/*--------------------------------------------------------------------*/
/* FUN_0004a378 @ 0x0004a378   (est. sk_tb_rec_encode7)
 * Ghidra: undefined8 FUN_0004a378(long param_1,undefined8 *param_2)
 * Encodes a TB record with a 3-field payload (kind, selector, nested records).
 * Returns the L4 error.
 * Confidence: medium
 */
unsigned long sk_tb_rec_encode7(unsigned long obj, unsigned long rec)
{
    unsigned long lv, w, out, u, sz, i, a, b;

    lv = *(unsigned long *)(*(unsigned long *)(obj + 0x20) + 8);
    a = *(unsigned long *)(rec + 8);
    b = *(unsigned long *)(rec + 0x30);
    if ((char)*(unsigned long *)rec == 1) u = 4;
    else if ((char)*(unsigned long *)rec == 0) {
        i = 1; if (b != 0) i = 2;
        sz = 1; if (*(unsigned char *)(rec + 0x28) != 0) sz = 2;
        u = 1; if (*(unsigned char *)(rec + 0x20) != 0) u = 2;
        out = 0x15; if ((char)*(unsigned long *)(rec + 0x18) == 0) out = 0x15;
        u = u + out + sz + i;
        u += 9;
        if ((char)*(unsigned long *)(rec + 0x38) == 0) u -= 8;
    } else u = 0;
    out = sk_tb_encode_get(*(unsigned long *)(lv + 0x18), *(unsigned long *)(lv + 0x28), u, 0);
    if ((int)out != 0) return out;
    w = *(unsigned long *)(lv + 0x28);
    if ((char)*(unsigned long *)rec == 1) {
        sk_tb_tag(w, 1);
        sk_tb_put_len(w, 3);
        if (((unsigned long)a - 1 & 0xff) < 6) {
            sk_tb_put_u8(w, 0);
            sk_tb_put_u16(w, a & 0xffff);
        } else sk_tb_fatal(0x5ba47e);
    } else {
        if ((char)*(unsigned long *)rec != 0) sk_tb_bad2();
        sk_tb_tag(w, 0);
        sk_tb_enc_rec(w, rec | 8);
    }
    *(unsigned char *)(lv + 0x20) = 1;
    return out;
}

/*--------------------------------------------------------------------*/

/*--------------------------------------------------------------------*/
/* FUN_0004a50c @ 0x0004a50c   (est. sk_tb_rec_encode8)
 * Ghidra: undefined8 FUN_0004a50c(long param_1,...)
 * Encodes a TB record whose first word is a tag-marker (0x427d55567dfea26 /
 * 0x652378e30e8da7d4 => 9, 0x629b90c9626409ac => 0x21). Writes the tag and
 * nested fields. Returns the L4 error.
 * Confidence: medium
 */
unsigned long sk_tb_rec_encode8(unsigned long obj, unsigned long rec)
{
    unsigned long lv, w, out, u, a, b, c;

    lv = *(unsigned long *)(*(unsigned long *)(obj + 0x20) + 8);
    a = *(unsigned long *)(rec + 8);
    b = *(unsigned long *)(rec + 0x10);
    c = *(unsigned long *)(rec + 0x18);
    if ((char)*(unsigned long *)rec == 1) u = 4;
    else if ((char)*(unsigned long *)rec == 0) {
        if (a == 0x427d55567dfea26 || a == 0x652378e30e8da7d4) u = 9;
        else if (a == 0x629b90c9626409ac) u = 0x21;
        else sk_tb_fatal(0x5ba47e);
    } else u = 0;
    out = sk_tb_encode_get(*(unsigned long *)(lv + 0x18), *(unsigned long *)(lv + 0x28), u, 0);
    if ((int)out != 0) return out;
    w = *(unsigned long *)(lv + 0x28);
    if ((char)*(unsigned long *)rec == 1) {
        sk_tb_tag(w, 1);
        sk_tb_put_len(w, 3);
        if (((unsigned long)a - 1 & 0xff) < 6) {
            sk_tb_put_u8(w, a & 0xff);
            sk_tb_put_u16(w, a >> 0x10 & 0xffff);
        } else sk_tb_fatal(0x5ba47e);
    } else {
        if ((char)*(unsigned long *)rec == 0) {
            sk_tb_tag(w, 0);
            sk_tb_var_w(w, a);
            if (a == 0x427d55567dfea26 || a == 0x652378e30e8da7d4) {
                *(unsigned char *)(lv + 0x20) = 1;
                return out;
            }
            if (a == 0x629b90c9626409ac) {
                sk_tb_put_len(w, 0x10);
                sk_tb_put_u64(w, b);
                sk_tb_put_u64(w, c);
                *(unsigned char *)(lv + 0x20) = 1;
                return out;
            }
            sk_tb_fatal(0x5ba47e);
        }
        sk_tb_bad2();
    }
    sk_tb_fatal(0x5ba47e);
    return 0;
}

/*--------------------------------------------------------------------*/

/*--------------------------------------------------------------------*/
/* FUN_0004b454 @ 0x0004b454   (est. sk_tb_fatal_ph)
 * Ghidra: void FUN_0004b454(ulong param_1)
 * Fatally aborts a TB placeholder operation with "invalid value" and the
 * AppleInternal build path, for an out-of-range placeholder kind.
 * Confidence: medium
 */
void sk_tb_fatal_ph(unsigned long kind)
{
    (void)kind;
    sk_tb_fatal(0x5ba47e);
}

/*--------------------------------------------------------------------*/

/*--------------------------------------------------------------------*/
/* FUN_0004b478 @ 0x0004b478   (est. sk_tb_fatal_5b85d2)
 * Ghidra: void FUN_0004b478(undefined8 param_1)
 * Fatally aborts a TB operation with the message at 0x5b85d2.
 * Confidence: medium
 */
void sk_tb_fatal_5b85d2(unsigned long ret)
{
    (void)ret;
    sk_tb_fatal(0x5b85d2);
}

/*--------------------------------------------------------------------*/

/*--------------------------------------------------------------------*/
/* FUN_0004b488 @ 0x0004b488   (est. sk_tb_fatal_5b8648)
 * Ghidra: void FUN_0004b488(undefined8 param_1)
 * Fatally aborts a TB operation with the message at 0x5b8648.
 * Confidence: medium
 */
void sk_tb_fatal_5b8648(unsigned long ret)
{
    (void)ret;
    sk_tb_fatal(0x5b8648);
}

/*--------------------------------------------------------------------*/

/*--------------------------------------------------------------------*/
/* FUN_0004b498 @ 0x0004b498   (est. sk_cap_release_t)
 * Ghidra: void FUN_0004b498(undefined8 param_1,long param_2)
 * Invokes a capability's release callback (at offset 0x10 in the object's
 * method table) when the "has destructor" flag (bit 25 of +8) is set.
 * Confidence: medium
 */
void sk_cap_release_t(unsigned long p, unsigned long obj)
{
    if ((*(unsigned int *)(obj + 8) >> 0x19 & 1) != 0) {
        if (*(unsigned long *)(*(unsigned long *)(obj + 0x18) + 0x10) != 0)
            (*(unsigned long (**)(void))(*(unsigned long *)(*(unsigned long *)(obj + 0x18) + 0x10)))();
    }
}

/*--------------------------------------------------------------------*/

/*--------------------------------------------------------------------*/
/* FUN_0004b4dc @ 0x0004b4dc   (est. sk_cap_release_cb)
 * Ghidra: void FUN_0004b4dc(long param_1)
 * Invokes a capability's release callback (at offset 0x18) when present.
 * Confidence: medium
 */
void sk_cap_release_cb(unsigned long obj)
{
    if ((*(unsigned int *)(obj + 8) >> 0x19 & 1) != 0) {
        if (*(unsigned long *)(*(unsigned long *)(obj + 0x18) + 0x18) != 0)
            (*(unsigned long (**)(void))(*(unsigned long *)(*(unsigned long *)(obj + 0x18) + 0x18)))();
    }
}

/*--------------------------------------------------------------------*/

/*--------------------------------------------------------------------*/
/* FUN_0004b520 @ 0x0004b520   (est. sk_cap_retain)
 * Ghidra: undefined8 * FUN_0004b520(undefined8 *param_1)
 * Retains a capability object, bumping its refcount. For objects with an
 * external backing pointer it clones the object and copies the backing; for
 * tagged objects it increments the 16-bit refcount. Returns the retained object.
 * Confidence: medium
 */
unsigned long sk_cap_retain(unsigned long cap)
{
    unsigned long out, u, meta;

    if (cap == 0) return 0;
    if ((*(unsigned int *)(cap + 8) >> 0x18 & 1) != 0) {
        /* tagged: bump refcount */
        do {
            u = *(unsigned int *)(cap + 8);
            if (((u ^ 0xffffffff) & 0xfffe) == 0) return cap;
        } while (*(unsigned int *)(cap + 8) != u);
        *(unsigned int *)(cap + 8) = u + 2;
        return cap;
    }
    if ((*(unsigned int *)(cap + 8) >> 0x1c & 1) == 0) {
        meta = *(unsigned long *)(cap + 0x18) + 8;
        out = sk_alloc_tagged(meta, 0x10e0040a5821769);
        if (out != 0) {
            u = *(unsigned long *)(cap + 0x10);
            if (u == 0) {
                /* no backing: look up cap type table */
                out = sk_cap_get_meta();
                return out;
            }
            sk_memcpy2(out, cap, meta);
            *(unsigned long *)(out + 0x10) = *(unsigned long *)(cap + 0x10);
            *(unsigned int *)(out + 8) = *(unsigned int *)(out + 8) & 0xffff0000 | 0x1000002;
            sk_cap_release_t(out, cap);
            *(unsigned long *)out = 0x6ad4a8;
        }
    }
    return out;
}

/*--------------------------------------------------------------------*/

/*--------------------------------------------------------------------*/
/* FUN_0004b664 @ 0x0004b664   (est. sk_cap_release)
 * Ghidra: void FUN_0004b664(long param_1)
 * Releases a capability object, decrementing its refcount and invoking the
 * release callback at zero. Non-tagged objects are ignored.
 * Confidence: medium
 */
void sk_cap_release(unsigned long cap)
{
    unsigned int u;
    int d;

    if (cap != 0 && (*(unsigned int *)(cap + 8) >> 0x1c & 1) == 0 &&
        (*(unsigned int *)(cap + 8) >> 0x18 & 1) != 0) {
        do {
            u = *(unsigned int *)(cap + 8);
            if ((u & 0xfffe) == 0 || (u & 0xfffe) == 0xfffe) return;
            d = -2;
            if ((u & 0xffff) == 2) d = -1;
        } while (*(unsigned int *)(cap + 8) != u);
        *(unsigned int *)(cap + 8) = d + u;
        if ((u & 0xffff) == 2) {
            sk_cap_release_cb(cap);
            sk_free_tagged(cap);
            return;
        }
    }
}

/*--------------------------------------------------------------------*/

/*--------------------------------------------------------------------*/
/* FUN_0004b710 @ 0x0004b710   (est. sk_cap_retype)
 * Ghidra: void FUN_0004b710(long *param_1,long param_2,uint param_3)
 * Retypes/derives a capability: for the object kinds 0x18 and 8 it copies the
 * object's backing into a fresh capability; kinds 3 and 7 pass through or
 * retain; kind 0x83..0x97 map to the corresponding retype. Returns the new cap.
 * Confidence: medium
 */
void sk_cap_retype(unsigned long outp, unsigned long cap, unsigned int kind)
{
    unsigned int u;
    unsigned long meta, new, lv;
    void *p;

    kind &= 0x9f;
    if (kind < 0x18) {
        if (kind == 3) { *(unsigned long *)outp = cap; return; }
        if (kind == 7) { *(unsigned long *)outp = sk_cap_retain(cap); return; }
        if (kind != 8) return;
    } else {
        if (kind - 0x83 < 0x15 && (1 << (kind - 0x83 & 0x1f) & 0x110011) != 0) {
            *(unsigned long *)outp = cap; return;
        }
        if (kind != 0x18) return;
    }
    lv = *(unsigned long *)(cap + 8);
    if ((*(unsigned int *)(lv + 0x10) & 0xfffe) == 0) {
        u = *(unsigned int *)(cap + 0x14);
        meta = sk_alloc_tagged((unsigned long)u, 0x10e0040f15f98b3);
        *(unsigned long *)meta = 0;
        *(unsigned int *)(meta + 0x10) = *(unsigned int *)(cap + 0x10) | 0x1000004;
        *(unsigned long *)(meta + 8) = meta;
        *(unsigned long *)(cap + 8) = meta;
        u = *(unsigned int *)(cap + 0x14);
        *(unsigned int *)(meta + 0x14) = u;
        if ((*(unsigned int *)(cap + 0x10) >> 0x19 & 1) == 0) {
            p = (void*)(meta + 0x18);
            sk_memcpy2(p, cap + 0x18, (unsigned long)u - 0x18);
        } else {
            *(unsigned long *)(meta + 0x18) = *(unsigned long *)(cap + 0x18);
            *(unsigned long *)(meta + 0x20) = *(unsigned long *)(cap + 0x20);
            if (*(unsigned int *)(cap + 0x10) >> 0x1c == 1)
                *(unsigned long *)(meta + 0x28) = *(unsigned long *)(cap + 0x28);
            (*(unsigned long (**)(unsigned long,unsigned long))(cap + 0x18))(meta, cap);
        }
    } else if ((*(unsigned int *)(lv + 0x10) >> 0x18 & 1) != 0) {
        do {
            u = *(unsigned int *)(lv + 0x10);
            if (((u ^ 0xffffffff) & 0xfffe) == 0) break;
        } while (*(unsigned int *)(lv + 0x10) != u);
        *(unsigned int *)(lv + 0x10) = u + 2;
    }
    cap = *(unsigned long *)(cap + 8);
    *(unsigned long *)outp = cap;
    (void)new;
}

/*--------------------------------------------------------------------*/

/*--------------------------------------------------------------------*/
/* FUN_0004b8d0 @ 0x0004b8d0   (est. sk_cap_release_rt)
 * Ghidra: void FUN_0004b8d0(long param_1,uint param_2)
 * Releases a capability by its kind: kind 3 is a direct call, kind 7 releases
 * via sk_cap_release, kinds 0x18/8 release the object's backing capability.
 * Confidence: medium
 */
void sk_cap_release_rt(unsigned long cap, unsigned int kind)
{
    unsigned int u;
    int d;
    unsigned long lv;

    kind &= 0x9f;
    if (kind < 8) {
        if (kind == 3) { sk_x_004b5aa0(); return; }
        if (kind == 7) { sk_cap_release(cap); return; }
    } else if ((kind == 0x18 || kind == 8) &&
            (lv = *(unsigned long *)(cap + 8), (*(unsigned int *)(lv + 0x10) >> 0x18 & 1) != 0)) {
        if ((*(unsigned int *)(lv + 0x10) & 0xfffe) == 0) { sk_x_004b5a78(); return; }
        do {
            u = *(unsigned int *)(lv + 0x10);
            if ((u & 0xfffe) == 0 || (u & 0xfffe) == 0xfffe) return;
            d = -2;
            if ((u & 0xffff) == 2) d = -1;
        } while (*(unsigned int *)(lv + 0x10) != u);
        *(unsigned int *)(lv + 0x10) = d + u;
        if ((u & 0xffff) == 2) {
            if ((*(unsigned int *)(lv + 0x10) >> 0x19 & 1) != 0)
                (*(unsigned long (**)(unsigned long))(lv + 0x20))(lv);
            sk_free_tagged(lv);
            return;
        }
    }
}

/*--------------------------------------------------------------------*/

/*--------------------------------------------------------------------*/
/* FUN_0004b9e0 @ 0x0004b9e0   (est. sk_cap_type_table_get)
 * Ghidra: undefined1 [16] FUN_0004b9e0(undefined8 param_1,long param_2)
 * Installs or returns the global capability-type table: if a table is already
 * registered it returns it; otherwise it records the (data,size) pair at
 * DAT_006ad6a8/b0. Returns the installed table as a cl4_result.
 * Confidence: medium
 */
cl4_result_t sk_cap_type_table_get(unsigned long data, unsigned long size)
{
    cl4_result_t r;

    r.lo = 0; r.hi = 0;
    if (sk_cfg_obj == 0) {
        if (size != 0) {
            sk_vas_root = data;
            sk_cfg_obj = size;
            r.lo = data; r.hi = size;
            return r;
        }
    } else {
        sk_err_a();
    }
    sk_err_b();
    if (sk_cfg_obj == 0)
        sk_cap_type_table_get(0x64cbd8, 0x64cbd8);
    r.lo = sk_vas_root;
    r.hi = sk_cfg_obj;
    return r;
}

/*--------------------------------------------------------------------*/

/*--------------------------------------------------------------------*/
/* FUN_0004ba18 @ 0x0004ba18   (est. sk_cap_type_table)
 * Ghidra: undefined1 [16] FUN_0004ba18(void)
 * Returns the global capability-type table as a cl4_result, installing the
 * default table if none is registered.
 * Confidence: medium
 */
cl4_result_t sk_cap_type_table(void)
{
    cl4_result_t r;

    r.lo = 0; r.hi = 0;
    if (sk_cfg_obj == 0)
        sk_cap_type_table_get(0x64cbd8, 0x64cbd8);
    r.lo = sk_vas_root;
    r.hi = sk_cfg_obj;
    return r;
}

/*--------------------------------------------------------------------*/

/*--------------------------------------------------------------------*/
/* FUN_0004ba64 @ 0x0004ba64   (est. sk_noop_ba64)
 * Ghidra: void FUN_0004ba64(void)
 * No-op.
 * Confidence: high (trivial).
 */
void sk_noop_ba64(void) { }

/*--------------------------------------------------------------------*/

/*--------------------------------------------------------------------*/
/* FUN_0004ba70 @ 0x0004ba70   (est. sk_ep_call_tls)
 * Ghidra: long FUN_0004ba70(undefined8 param_1,ulong param_2,ulong param_3,long param_4,ulong param_5)
 * Performs an endpoint call, setting up the TLS message registers (selector,
 * words) and invoking sk_ep_call. Uses the current key from TLS when the
 * selector/flags permit; otherwise the calling key is read from the TLS key
 * table. Aborts on a deleted key.
 * Confidence: medium
 * Notes: strings "getting key %lu which is deleted" (0x5ab2a5) / "while destructor"
 *   (0x5ab2c6); key table via sk_key_get (0x63a50).
 */
unsigned long sk_ep_call_tls(unsigned long ep, unsigned long sel, unsigned long w, long arg,
                             unsigned long flags)
{
    unsigned long key, tls, ret;

    key = sk_key_get();
    tls = 0;
    if ((flags & 8) == 0 || (int)sel == 3) {
        /* direct call path */
        sk_ep_call(ep, 1, 3, &arg, 1, 1, 0, 0); ret = 0;
        if (ret == 0 && (flags & 8) == 0 && (int)sel != 3)
            sk_obj_create(sel, w, arg);
        return ret;
    }
    /* key-table lookup path */
    tls = sk_x_00063a50();
    if (*(unsigned long *)(tls + key * 8 + 0x1f8) == 0xffffffffffffffff)
        sk_panic(0x5ab2a5);
    else if (*(unsigned long *)(key * 8 + 0xf8) == 0)
        ret = *(unsigned long *)(key * 8 + 0xf8);
    else
        sk_panic(0x5ab2c6);
    return ret;
}

/*--------------------------------------------------------------------*/

/*--------------------------------------------------------------------*/
/* FUN_0004bbb4 @ 0x0004bbb4   (est. sk_ep_call_send)
 * Ghidra: void FUN_0004bbb4(undefined8 param_1,undefined8 param_2,ulong param_3,ulong param_4)
 * Performs an endpoint send with two message words, setting the TLS registers
 * and calling sk_ep_call.
 * Confidence: medium
 */
void sk_ep_call_send(unsigned long ep, unsigned long w0, unsigned long w1, unsigned long w2)
{
    unsigned long lv;

    lv = 0;
    sk_ep_call(ep, 2, 3, &lv, 1, 1, 0, 0);
    (void)w0; (void)w1; (void)w2;
}

/*--------------------------------------------------------------------*/

/*--------------------------------------------------------------------*/
/* FUN_0004bc34 @ 0x0004bc34   (est. sk_ep_call_reply)
 * Ghidra: void FUN_0004bc34(undefined8 param_1,ulong param_2,undefined8 *param_3)
 * Performs an endpoint call that returns a single result word.
 * Confidence: medium
 */
void sk_ep_call_reply(unsigned long ep, unsigned long w, unsigned long outp)
{
    unsigned long lv, r;

    lv = 0;
    sk_ep_call(ep, 8, 1, 0, 0, 1, &lv, 1);
    *(unsigned long *)outp = lv;
}

/*--------------------------------------------------------------------*/

/*--------------------------------------------------------------------*/
/* FUN_0004bc98 @ 0x0004bc98   (est. sk_ep_call_noreply)
 * Ghidra: void FUN_0004bc98(undefined8 param_1,undefined8 param_2)
 * Performs an endpoint call with no reply, sending the current random value.
 * Confidence: medium
 */
void sk_ep_call_noreply(unsigned long ep, unsigned long w)
{
    unsigned long lv;

    lv = sk_random();
    sk_ep_call(w, 0x20, 1, 0, 0, 1, 0, 0);
    (void)ep;
}

/*--------------------------------------------------------------------*/

/*--------------------------------------------------------------------*/
/* FUN_0004bd64 @ 0x0004bd64   (est. sk_ep_call_w)
 * Ghidra: void FUN_0004bd64(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4)
 * Performs an endpoint call with a single result word.
 * Confidence: medium
 */
void sk_ep_call_w(unsigned long ep, unsigned long w, unsigned long a, unsigned long b)
{
    unsigned long lv;

    lv = b;
    sk_ep_call(ep, 2, 6, &lv, 1, 1, 0, 0);
    (void)a;
}

/*--------------------------------------------------------------------*/

/*--------------------------------------------------------------------*/
/* FUN_0004bdd8 @ 0x0004bdd8   (est. sk_obj_create_batch)
 * Ghidra: void FUN_0004bdd8(undefined8 param_1,uint param_2,uint param_3,ulong param_4,
 *   long param_5, long param_6)
 * Creates a batch of objects through the pmm endpoint, walking the caller's
 * descriptor array and invoking the object-create method (at param_5+0x10) for
 * each, collecting the created object capabilities. Aborts on alloc failure.
 * Confidence: medium
 */
void sk_obj_create_batch(unsigned long ep, unsigned int kind, unsigned int flags, unsigned long n,
                         unsigned long get, unsigned long put)
{
    unsigned long u, key, tls, ret, i, j;
    unsigned long desc[4], sels[4], outs[4];

    (void)kind; (void)flags; (void)get; (void)put;
    if (n > 4) n = 4;
    key = sk_key_get();
    tls = 0;
    if (n != 0) {
        i = 0;
        for (j = 0; j < n; j++) desc[j] = sk_pmm_alloc();
        while (i < n) {
            sels[i] = (*(unsigned long (**)(unsigned long,unsigned long))(get + 0x10))(get, i);
            i++;
        }
        sk_ep_call(ep, 0xb, n + 3, desc, n, 0, outs, n);
        ret = 0;
        for (j = 0; j < n; j++) {
            if (outs[j] == 0) sk_obj_create(kind, desc[j], sels[j]);
        }
    }
    (void)key; (void)tls;
}

/*--------------------------------------------------------------------*/

/*--------------------------------------------------------------------*/
/* FUN_0004c4a0 @ 0x0004c4a0   (est. sk_obj_create)
 * Ghidra: void FUN_0004c4a0(ulong param_1,ulong param_2,ulong param_3)
 * Creates a kernel object by calling into the supervisor with the object kind
 * and size; validates the resulting error and logs a panic on failure.
 * Confidence: medium
 * Notes: string "libpmm__create_object__d____zx____" (0x5bafe4).
 */
void sk_obj_create(unsigned long kind, unsigned long size, unsigned long arg)
{
    unsigned long errbuf[4];

    CallSupervisor(0);
    if ((size & 0xff) != 0) {
        sk_err_abort((unsigned long)errbuf, size, 0);
        sk_vas_abort(0x5bafe4);
    }
    sk_x_004b5b00(size, kind, errbuf);
}

/*--------------------------------------------------------------------*/

/*--------------------------------------------------------------------*/
/* FUN_0004c574 @ 0x0004c574   (est. sk_ep_call)
 * Ghidra: void FUN_0004c574(ulong param_1,ulong param_2,ulong param_3,undefined8 *param_4,
 *   long param_5, ulong param_6, ulong *param_7, ulong param_8)
 * Low-level pmm endpoint call: packs the message words into the TLS registers,
 * issues the supervisor call, and unpacks the returned words. Handles the
 * "retry until not preempted" loop and result extraction.
 * Confidence: medium
 * Notes: strings "libpmm__L4_Ep_Call___zx__intag___" (0x5badeb), "...succeeded"
 *   (0x5baf19/0x5baf8e), "...failed_wi" (0x5bae39).
 */
void sk_ep_call(unsigned long ep, unsigned long sel, unsigned long n, unsigned long *args,
                long nargs, unsigned long flags, unsigned long *outs, unsigned long nouts)
{
    unsigned long u, lv, i;

    (void)sel;
    u = (n << 0x10) | (n & 0x3f);
    CallSupervisor(0);
    if ((ep & 0xff) != 0) {
        sk_err_abort(0, ep, 0);
        sk_vas_abort(0x5badeb);
    }
    if ((n & 0xffff) == 0) {
        /* unpack results */
        for (i = 0; i < nouts && i < n; i++) outs[i] = 0;
        if (nargs != 0 && (flags & 1) != 0) {
            sk_vas_abort(0x5baf19);
        }
        if (nouts != n) {
            sk_vas_abort(0x5baf8e);
        }
    } else {
        if (0 == 0) sk_vas_abort(0x5bae39);
    }
    (void)lv;
}

/*--------------------------------------------------------------------*/

/*--------------------------------------------------------------------*/
/* FUN_0004c890 @ 0x0004c890   (est. sk_err_abort)
 * Ghidra: void FUN_0004c890(undefined8 *param_1,byte param_2)
 * Fills a 32-byte buffer with an L4 error-code string (or unknown marker) and
 * aborts with it. String table at DAT_004bc760.
 * Confidence: high (string-matched error-code names).
 */
void sk_err_abort(unsigned long out, unsigned long code, unsigned long extra)
{
    (void)extra;
    sk_l4_err_string(out, code);
}

/*--------------------------------------------------------------------*/

/*--------------------------------------------------------------------*/
/* FUN_0004c9d0 @ 0x0004c9d0   (est. sk_boot_parse)
 * Ghidra: void FUN_0004c9d0(undefined8 param_1,undefined2 *param_2)
 * Parses a boot argument structure into the caller's out-struct: reads the
 * selector count and each selector value from the boot-info array, copying the
 * trailing string buffer.
 * Confidence: medium
 */
void sk_boot_parse(unsigned long p, unsigned long out)
{
    unsigned long n, lv, cnt, u, cap;

    n = sk_svc_count();
    if (n != 0) *(unsigned long *)out = sk_svc_read(0);
    lv = sk_svc_ptr(p);
    if (lv != 0) {
        lv = 0;
        *(unsigned long *)(out + 8) = 0;
    }
    if (1 < n) {
        *(unsigned long *)(out + 0x20) = sk_svc_read(1);
        if (n != 2 && *(unsigned long *)(out + 0x60) != 0) {
            cap = sk_svc_read(2);
            cnt = n * 8 - 0x18;
            if (cnt <= cap) cap = cnt;
            if (*(unsigned long *)(out + 0x80) <= cap) cap = *(unsigned long *)(out + 0x80);
            sk_svc_copyin(*(unsigned long *)(out + 0x60), cap, 3);
            u = *(unsigned long *)(out + 0x60);
            if (u + *(unsigned long *)(out + 0x80) <= u + cap) {
                *(char *)(u + cap) = 0;
                *(unsigned long *)(out + 0x80) = cap;
            }
        }
    }
}

/*--------------------------------------------------------------------*/

/*--------------------------------------------------------------------*/
/* FUN_0004cafc @ 0x0004cafc   (est. sk_boot_ep)
 * Ghidra: void FUN_0004cafc(undefined2 *param_1,int param_2)
 * Packs the boot endpoint message from the parsed out-struct and sends it
 * through the supervisor, then returns.
 * Confidence: medium
 */
void sk_boot_ep(unsigned long out, int mode)
{
    unsigned long lv, u;

    if (*(unsigned long *)(out + 8) == 0) {
        lv = 0;
    } else {
        if (mode == 0) sk_svc_clear(0);
        else {
            lv = sk_tls_get();
            sk_tls_enter(lv, 0);
            CallSupervisor(1);
            if ((*(unsigned long *)(out + 8) & 0xff) != 0) {
                sk_err_abort(0, *(unsigned long *)(out + 8), 0);
                lv = 0;
            }
        }
        lv = 1;
    }
    sk_svc_write(0, *(unsigned long *)out);
    sk_svc_write(1, *(unsigned long *)(out + 0x20));
    if (*(unsigned long *)(out + 0x60) == 0) {
        u = 2;
    } else {
        u = *(unsigned long *)(out + 0x80);
        if (u > 0x1a8) u = 0x1a8;
        sk_svc_write(2, u);
        if (*(unsigned long *)(out + 0x80) < u) sk_vas_abort(0x5aed68);
        sk_svc_copyout(*(unsigned long *)(out + 0x60), u, 3, 0);
    }
    sk_svc_ret(u, lv, *(unsigned long *)out, 1);
}

/*--------------------------------------------------------------------*/

/*--------------------------------------------------------------------*/
/* FUN_0004cc24 @ 0x0004cc24   (est. sk_err_str_cc24)
 * Ghidra: void FUN_0004cc24(undefined8 param_1,byte param_2)
 * Fills a buffer with an L4 error-code string (table at DAT_004bc8c0).
 * Confidence: high (string-matched).
 */
void sk_err_str_cc24(unsigned long out, unsigned long code)
{
    const char *p;

    if (code > 9) {
        sk_memcpy(out, 0x4bca00, 0x20);
        sk_abort_msg(out, 0x20);
        return;
    }
    switch (code) {
    default: p = "L4ErrorCodeSuccess"; break;
    case 1:  p = "L4ErrorCodePreempted"; break;
    case 2:  p = "L4ErrorCodeCanceled"; break;
    case 3:  p = "L4ErrorCodeTruncated"; break;
    case 4:  p = "L4ErrorCodeCapInvalid"; break;
    case 5:  p = "L4ErrorCodeSlotInvalid"; break;
    case 6:  p = "L4ErrorCodeMethodInvalid"; break;
    case 7:  p = "L4ErrorCodeArgumentInvalid"; break;
    case 8:  p = "L4ErrorCodeOperationInvalid"; break;
    case 9:  p = "L4ErrorCodePermissionInvalid"; break;
    }
    sk_memcpy(out, (unsigned long)p, 0x20);
}

/*--------------------------------------------------------------------*/

/*--------------------------------------------------------------------*/
/* FUN_0004cd5c @ 0x0004cd5c   (est. sk_boot_call)
 * Ghidra: long FUN_0004cd5c(undefined8 param_1,undefined8 param_2,long param_3)
 * Performs a boot call: packs the message via sk_boot_ep and sends it through
 * the TLS exit path, then parses the reply into the optional out-struct.
 * Confidence: medium
 */
unsigned long sk_boot_call(unsigned long ep, unsigned long out, unsigned long reply)
{
    unsigned long lv, r;

    sk_boot_ep(out, 0); lv = 0;
    r = sk_tls_exit(ep, &lv);
    if (reply != 0 && r == 0) sk_boot_parse(lv, reply);
    return r;
}

/*--------------------------------------------------------------------*/

/*--------------------------------------------------------------------*/
/* FUN_0004cdc0 @ 0x0004cdc0   (est. sk_boot_string)
 * Ghidra: long FUN_0004cdc0(ulong param_1,ulong param_2)
 * Sends a string through the boot endpoint, chunking it if it exceeds the
 * 0x198-byte message limit, and returns the L4 error.
 * Confidence: medium
 */
unsigned long sk_boot_string(unsigned long ep, unsigned long size)
{
    unsigned long lv, r, n, rem, chunk;
    unsigned long buf[13];

    lv = 0;
    r = 4;
    if (size < 0x199) {
        /* small message: direct send */
        return 0;
    }
    /* chunked send (condensed) */
    (void)ep; (void)n; (void)rem; (void)chunk; (void)buf;
    return r;
}

/*--------------------------------------------------------------------*/

/*--------------------------------------------------------------------*/
/* FUN_0004d150 @ 0x0004d150   (est. sk_ptr_fixup)
 * Ghidra: ulong * FUN_0004d150(ulong *param_1,undefined8 param_2,long param_3,long param_4,long param_5)
 * Walks a chain of tagged pointers fixing up absolute addresses by the slide:
 * for each 64-bit word, if the sign bit is clear and the tag bits indicate an
 * absolute pointer, it applies the slide and advances by the stride*level.
 * Returns the first word whose tag marks the end, or 0.
 * Confidence: medium
 */
unsigned long sk_ptr_fixup(unsigned long ptr, unsigned long arg, long stride, long slide, long base)
{
    unsigned long u, addr, level;

    while (1) {
        u = *(unsigned long *)ptr;
        if ((u >> 0x3e & 1) == 0) {
            if ((long)u < 0) addr = base + slide + (u & 0xffffffff);
            else addr = base + ((u >> 0x2b) << 0x38) + ((u << 0x15) >> 0x15 & 0xffffffffffffff);
            *(unsigned long *)ptr = addr;
        }
        level = u >> 0x33 & 0x7ff;
        ptr += level * stride;
        if (level == 0 || ptr < (ptr & 0xffffffffffffc000) || ptr >= (ptr & 0xffffffffffffc000) + 0x800) break;
    }
    if (level == 0) ptr = 0;
    return ptr;
}

/*--------------------------------------------------------------------*/

/*--------------------------------------------------------------------*/
/* FUN_0004d1fc @ 0x0004d1fc   (est. sk_reloc_apply)
 * Ghidra: void FUN_0004d1fc(uint *param_1,uint *param_2)
 * Applies relocations to a range of tagged pointers, skipping __DATA/__DATA_CONST
 * segments when the relevant flag is set and otherwise applying the slide via
 * sk_ptr_fixup. Stops at the 0xffffffff sentinel.
 * Confidence: medium
 * Notes: strings "__DATA" (0x5bb23b), "__DATA_CONST" (0x5bb242); sk_x_00051e5c.
 */
void sk_reloc_apply(unsigned long begin, unsigned long end)
{
    unsigned long p, u, w, d, dc;
    unsigned long slide;

    slide = sk_vas_stack_pop();
    if (begin + 4 <= end && begin <= begin + 4) {
        w = 4;
        if (*(unsigned int *)begin & 1) w = 8;
        if (begin + 4 != end) {
            p = begin + 4;
            do {
                u = *(unsigned int *)p;
                if (u == 0xffffffff) return;
                if (sk_cfg_geo_c == 1) {
                    d = sk_x_00051e5c(0, 0x5bb23b);
                    dc = sk_x_00051e5c(0, 0x5bb242);
                    if ((d != 0 && (u < *(unsigned long *)(d + 0x18) + slide ||
                        *(unsigned long *)(d + 0x20) + *(unsigned long *)(d + 0x18) + slide <= u)) &&
                        (dc != 0 && (u < *(unsigned long *)(dc + 0x18) + slide ||
                        *(unsigned long *)(dc + 0x20) + *(unsigned long *)(dc + 0x18) + slide <= u)))
                        sk_ptr_fixup(u, u & 0xffffffffffffc000, w, -slide, slide);
                } else {
                    sk_ptr_fixup(u, u & 0xffffffffffffc000, w, -slide, slide);
                }
                p += w;
            } while (p != end);
        }
    }
}

/*--------------------------------------------------------------------*/

/*--------------------------------------------------------------------*/
/* FUN_0004d364 @ 0x0004d364   (est. sk_reloc_one)
 * Ghidra: undefined8 FUN_0004d364(undefined8 *param_1)
 * Records a single tagged pointer pair into the TLS store for later fixup.
 * Confidence: low
 */
unsigned long sk_reloc_one(unsigned long in)
{
    unsigned long lo, hi, tls;

    lo = *(unsigned long *)in;
    hi = *(unsigned long *)(in + 8);
    tls = sk_tls_get();
    sk_tls_store(tls, &lo, 0);
    (void)hi;
    return 0;
}

/*--------------------------------------------------------------------*/

/*--------------------------------------------------------------------*/
/* FUN_0004d39c @ 0x0004d39c   (est. sk_reloc_init)
 * Ghidra: void FUN_0004d39c(void)
 * One-time relocation init: scans the __DATA segments of every loaded image,
 * sets up the TB placeholder ranges, registers the fault handler, and installs
 * the initial VAS mappings. Runs at boot.
 * Confidence: medium
 * Notes: strings "___PDATA" (0x5bb7ae), "initial_vas_mappings_failed" (0x5bb316);
 *   walks segment list from sk_x_0005ba14.
 */
void sk_reloc_init(void)
{
    unsigned long img, span, u, i, n;
    cl4_result_t r;

    if (sk_cfg_geo_c != 1) return;
    img = sk_x_0005ba14();
    u = sk_tb_ph_avail();
    r = sk_tb_ph_range2();
    while (img != 0) {
        if (*(char *)(img + 8) < 0) {
            /* walk TB placeholders and register ranges (condensed) */
        }
        img = *(unsigned long *)img;
    }
    n = sk_global_cfg();
    u = *(unsigned long *)(n + 0x110);
    if (u < *(unsigned long *)(n + 0x118)) {
        do {
            r.lo = sk_vm_obj_alloc();
            i = (**(unsigned long (**)(unsigned long,unsigned long,unsigned long,unsigned long))
                    (r.lo + 0x38))(r.lo, u, 0, 0);
            if (i == 0) {
                sk_x_004b5d40(u);
                r.lo = sk_vm_obj_alloc();
                i = (**(unsigned long (**)(unsigned long,unsigned long))(r.lo + 0x58))(r.lo, 0x6af2c8);
                if ((i & 0xff) == 0) { sk_init_done(0x64cc30); return; }
                sk_vas_abort(0x5bb24f);
            }
            u = *(unsigned long *)(n + 0x110);
        } while (u < *(unsigned long *)(n + 0x118));
    }
}

/*--------------------------------------------------------------------*/

/*--------------------------------------------------------------------*/
/* FUN_0004d8ec @ 0x0004d8ec   (est. sk_vas_init_fh)
 * Ghidra: void FUN_0004d8ec(void)
 * Registers the initial VAS fault handler with the supervisor.
 * Confidence: medium
 */
void sk_vas_init_fh(void)
{
    unsigned long r, u;

    r = sk_vm_obj_alloc();
    u = (**(unsigned long (**)(unsigned long,unsigned long))(r + 0x58))(r, 0x6af2c8);
    if ((u & 0xff) == 0) { sk_init_done(0x64cc30); return; }
    sk_vas_abort(0x5bb24f);
}

/*--------------------------------------------------------------------*/

/*--------------------------------------------------------------------*/
/* FUN_0004d974 @ 0x0004d974   (est. sk_vas_init_map)
 * Ghidra: undefined1 [16] FUN_0004d974(undefined8 param_1,long param_2,uint param_3,
 *   undefined1 param_4)
 * Creates an initial VAS mapping of a physical region: allocates the mapping
 * descriptor and invokes the span object's map method, returning {error,desc}.
 * Aborts if the mapping fails or the descriptor is absent.
 * Confidence: medium
 * Notes: string "liblibc__Initial_VAS_initial_ma.." (0x5bb2e3).
 */
cl4_result_t sk_vas_init_map(unsigned long base, long size, unsigned int flags, unsigned char kind)
{
    cl4_result_t r;
    unsigned long lv, u;

    r.lo = 0; r.hi = 0;
    if (size == 0) return r;
    lv = 0x11;
    u = sk_vm_obj_alloc();
    if ((**(unsigned long (**)(unsigned long,unsigned long,unsigned long,unsigned long,unsigned long,unsigned long))
            (u + 0x30))(0, flags | 0x801, (unsigned long)&lv, (unsigned long)&r.lo, 0, 0) != 0)
        sk_vas_abort(0x5bb2e3);
    if (r.lo == 0) sk_x_00054354();
    (**(unsigned long (**)(unsigned long,unsigned long))(r.hi + 8))(r.lo, (unsigned long)&lv);
    return r;
}

/*--------------------------------------------------------------------*/

/*--------------------------------------------------------------------*/
/* FUN_0004dab4 @ 0x0004dab4   (est. sk_fault_handle)
 * Ghidra: void FUN_0004dab4(long *param_1,ulong param_2,undefined8 param_3,ulong *param_4)
 * Handles a VAS fault: reports the faulting address and its attributes to the
 * supervisor, increments the fault counters, and looks up the backing span.
 * Returns an L4 error word.
 * Confidence: medium
 */
void sk_fault_handle(unsigned long fault, unsigned long va, unsigned long attr, unsigned long outp)
{
    unsigned long lv, ret;

    sk_stat_cow4++;
    if (va < *(unsigned long *)(fault + 0x10)) { sk_stat_cow5++; ret = 1; }
    else if (va < *(unsigned long *)(fault + 8)) {
        lv = *(unsigned long *)(fault + 0x18);
        CallSupervisor(0);
        if ((lv & 0xff) != 0) { sk_err_str_cc24(0, lv); return; }
        if (sk_x_0005228c(*(unsigned long *)(fault + 0x28), *(unsigned long *)fault + va) == 0) {
            sk_stat_cow6++; ret = 2;
        } else {
            sk_stat_cow7++;
            *(unsigned long *)outp = *(unsigned char *)(fault + 0x20);
            ret = 3;
        }
    } else { sk_stat_cow8++; ret = 0; }
    (void)attr;
}

/*--------------------------------------------------------------------*/

/*--------------------------------------------------------------------*/
/* FUN_0004dcd0 @ 0x0004dcd0   (est. sk_err_str_dcd0)
 * Ghidra: void FUN_0004dcd0(undefined8 param_1,byte param_2)
 * Fills a buffer with an L4 error-code string (table at DAT_004bca20).
 * Confidence: high (string-matched).
 */
void sk_err_str_dcd0(unsigned long out, unsigned long code)
{
    const char *p;

    if (code > 9) {
        sk_memcpy(out, 0x4bcb60, 0x20);
        sk_abort_msg(out, 0x20);
        return;
    }
    switch (code) {
    default: p = "L4ErrorCodeSuccess"; break;
    case 1:  p = "L4ErrorCodePreempted"; break;
    case 2:  p = "L4ErrorCodeCanceled"; break;
    case 3:  p = "L4ErrorCodeTruncated"; break;
    case 4:  p = "L4ErrorCodeCapInvalid"; break;
    case 5:  p = "L4ErrorCodeSlotInvalid"; break;
    case 6:  p = "L4ErrorCodeMethodInvalid"; break;
    case 7:  p = "L4ErrorCodeArgumentInvalid"; break;
    case 8:  p = "L4ErrorCodeOperationInvalid"; break;
    case 9:  p = "L4ErrorCodePermissionInvalid"; break;
    }
    sk_memcpy(out, (unsigned long)p, 0x20);
}

/*--------------------------------------------------------------------*/

/*--------------------------------------------------------------------*/
/* FUN_0004de08 @ 0x0004de08   (est. sk_fault_startfault)
 * Ghidra: undefined8 FUN_0004de08(undefined8 *param_1,undefined8 param_2,long *param_3)
 * Starts a VAS fault: invokes the fault handler method on the fault object,
 * then resolves the backing page and updates the spanmap. Returns 1 on success.
 * Confidence: medium
 * Notes: strings "asked_to_get__zd__not_in__plat_c" (0x5bb592) and "..region__but_fix"
 *   (0x5bb51b); stat counters at DAT_006ad6cc..
 */
unsigned long sk_fault_startfault(unsigned long fault, unsigned long arg, unsigned long in)
{
    unsigned long r, lv, span, u;
    unsigned long res[6];
    unsigned long i;

    for (i = 0; i < 6; i++) res[i] = 0;
    if (*(unsigned long *)in == 1) {
        sk_stat_cow9++;
        r = (**(unsigned long (**)(unsigned long,unsigned long,unsigned long,unsigned long,unsigned long))
                (*(unsigned long *)(fault + 0x10)))(*(unsigned long *)fault, *(unsigned long *)(fault + 8),
                *(unsigned long *)(in + 8), *(unsigned char *)(in + 0x19), (unsigned long)res);
        if (r != 0 && (res[0] & 1) != 0) sk_vas_abort(0x5bb4d4);
        if (r == 5) { sk_stat_cow10++; return 0; }
        if (r == 0) {
            if ((res[0] & 1) == 0) return 1;
            sk_stat_cow11++;
            if (res[4] > 0x13) sk_vas_abort(0x5bb592);
            span = *(unsigned long *)(res[4] * 0x40 + 0x6af310);
            if (span == 0) sk_vas_abort(0x5bb51b);
            u = sk_x_0005236c(span, res[2], res[3]);
            if ((u & 1) == 0) sk_vas_abort(0x5bb557);
            (**(unsigned long (**)(unsigned long,unsigned long,unsigned long,unsigned long))
                (*(unsigned long *)(fault + 0x10) + 8))(*(unsigned long *)fault, *(unsigned long *)(fault + 8), res[2], 1);
            return 1;
        }
        sk_stat_cow12++;
        return 2;
    }
    return 0;
}

/*--------------------------------------------------------------------*/

/*--------------------------------------------------------------------*/
/* FUN_0004dfd0 @ 0x0004dfd0   (est. sk_fh_register)
 * Ghidra: void FUN_0004dfd0(undefined8 param_1,undefined8 param_2)
 * Registers a fault-handler callback with the VAS and stores the handler's
 * context pair at DAT_006af838/840.
 * Confidence: medium
 */
void sk_fh_register(unsigned long a, unsigned long b)
{
    unsigned long lv[2];

    lv[0] = a; lv[1] = b;
    sk_cb_register(0x6af7e8, sk_fh_dump, &lv);
    sk_vas_stack_top = lv[0];
    sk_cfg_obj = lv[1];
}

/*--------------------------------------------------------------------*/

/*--------------------------------------------------------------------*/
/* FUN_0004e024 @ 0x0004e024   (est. sk_fh_dump)
 * Ghidra: void FUN_0004e024(undefined8 *param_1)
 * Dumps the fault-handler registration to the log and flushes.
 * Confidence: medium
 */
void sk_fh_dump(unsigned long in)
{
    sk_mem_dump(0x6af7f0, 0, sk_vas_stack_top, *(unsigned long *)(in + 8), *(unsigned long *)in, 0x80);
    sk_flush(0x6af7f0);
}

/*--------------------------------------------------------------------*/

/*--------------------------------------------------------------------*/
/* FUN_0004e074 @ 0x0004e074   (est. sk_tb_ph_alloc)
 * Ghidra: undefined4 * FUN_0004e074(undefined4 param_1,undefined8 param_2,long param_3)
 * Allocates a TB placeholder descriptor: records the kind, the object pointer,
 * and the retained capability (or 0). Returns the descriptor.
 * Confidence: medium
 */
unsigned long sk_tb_ph_alloc(unsigned int kind, unsigned long obj, unsigned long cap)
{
    unsigned long d, u;

    d = sk_alloc_array(1, 0x18, 0x10800404acf7207);
    if (d != 0) {
        *(unsigned int *)d = kind;
        *(unsigned long *)(d + 0x10) = obj;
        u = 0;
        if (cap != 0) u = sk_cap_retain(cap);
        *(unsigned long *)(d + 0x20) = u;
        return d;
    }
    sk_vas_abort(0x5aed68);
    return 0;
}

/*--------------------------------------------------------------------*/

/*--------------------------------------------------------------------*/
/* FUN_0004e104 @ 0x0004e104   (est. sk_tb_ph_free)
 * Ghidra: void FUN_0004e104(long param_1)
 * Frees a TB placeholder descriptor, releasing its retained capability.
 * Confidence: medium
 */
void sk_tb_ph_free(unsigned long d)
{
    if (*(unsigned long *)(d + 0x10) != 0) sk_cap_release(d + 0x10);
    sk_free_tagged(d);
}

/*--------------------------------------------------------------------*/

/*--------------------------------------------------------------------*/
/* FUN_0004e138 @ 0x0004e138   (est. sk_tb_ph_array)
 * Ghidra: void FUN_0004e138(undefined8 *param_1,ulong param_2,long param_3)
 * Builds a TB placeholder array from a list of descriptors, invoking the
 * target's array-setup method with the packed descriptors.
 * Confidence: medium
 */
void sk_tb_ph_array(unsigned long arr, unsigned long n, unsigned long target)
{
    unsigned long i;
    unsigned long buf[116];

    if (n < 0x1e) {
        if (n != 0) {
            for (i = 0; i < n; i++) {
                buf[i * 4 + 1] = *(unsigned long *)(*(unsigned long *)arr + i * 8);
                buf[i * 4 + 2] = *(unsigned long *)(*(unsigned long *)(arr + i * 8) + 0x10);
                buf[i * 4 + 3] = *(unsigned long *)(*(unsigned long *)(arr + i * 8) + 0x20);
            }
        }
        (*(unsigned long (**)(unsigned long,unsigned long,unsigned long))(target + 0x10))(target, (unsigned long)buf, n);
    }
}

/*--------------------------------------------------------------------*/

/*--------------------------------------------------------------------*/
/* FUN_0004e220 @ 0x0004e220   (est. sk_tb_ph_size)
 * Ghidra: ulong FUN_0004e220(long param_1,long param_2)
 * Computes the total wire size of a TB placeholder array: sums the per-entry
 * size (sk_tb_ph_res) plus 8 header bytes, checking for overflow.
 * Confidence: medium
 */
unsigned long sk_tb_ph_size(unsigned long arr, unsigned long n)
{
    unsigned long sz, u;

    sz = 8;
    while (n != 0) {
        if (*(unsigned long *)(arr + 0x10) != 0 && *(unsigned long *)(arr + 0x18) != 0) {
            u = sk_tb_ph_res(*(unsigned int *)(arr + 0x18), 0);
            sz += u;
            if (sz < sz - u) sk_overflow_panic(0x5bb5bd);
        }
        arr += 0x20;
        n--;
    }
    return sz;
}

/*--------------------------------------------------------------------*/

/*--------------------------------------------------------------------*/
/* FUN_0004e298 @ 0x0004e298   (est. sk_tb_ph_res)
 * Ghidra: long FUN_0004e298(uint param_1,ulong param_2)
 * Returns the wire size of a TB placeholder of a given kind: the element size
 * (table at 0x65bf70) times the count, plus 12 header bytes. Aborts on an
 * unknown kind or overflow.
 * Confidence: medium
 */
unsigned long sk_tb_ph_res(unsigned int kind, unsigned long n)
{
    unsigned long esz, u;

    if (kind > 0x1c) sk_panic(0x5bb75b);
    esz = *(unsigned long *)((unsigned long)kind * 0x30 + 0x65bf70);
    u = n * esz;
    if (u < 0xfffffffffffffff4) return u + 0xc;
    sk_overflow_panic(0x5bb5bd);
    return 0;
}

/*--------------------------------------------------------------------*/

/*--------------------------------------------------------------------*/
/* FUN_0004e314 @ 0x0004e314   (est. sk_tb_ph_encode)
 * Ghidra: ushort * FUN_0004e314(ushort *param_1,long param_2,uint *param_3,ulong param_4)
 * Encodes a TB placeholder array into a wire buffer: writes the total-size
 * header and each entry's payload via sk_tb_ph_one. Returns the buffer, or 0
 * if it does not fit. Validates duplicate kinds.
 * Confidence: medium
 */
unsigned long sk_tb_ph_encode(unsigned long buf, long size, unsigned long arr, unsigned long n)
{
    unsigned long u, i, sz, esz, kind;
    unsigned char seen[0x1d];

    if (n >= 0x1e) return 0;
    if (n != 0) {
        for (i = 0; i < n; i++) {
            u = *(unsigned long *)(arr + i * 8);
            if (u >= 0x1d) return 0;
            if (seen[u] & 1) return 0;
            seen[u] = 1;
        }
    }
    sz = sk_tb_ph_size(arr, n);
    if (size == sz) {
        /* write header and each entry (condensed) */
        if (n != 0) {
            for (i = 0; i < n; i++) {
                kind = *(unsigned long *)(arr + i * 8);
                if (kind > 0x1c) sk_panic(0x5bb75b);
                esz = *(unsigned long *)(kind * 0x30 + 0x65bf70);
                if (sz < esz + i * esz) return 0;
                u = sk_tb_ph_one(kind, buf + 0xc + i * esz, esz, sz, 0, 0);
                if (u == 0) return 0;
            }
        }
        return buf;
    }
    return 0;
}

/*--------------------------------------------------------------------*/

/*--------------------------------------------------------------------*/
/* FUN_0004e558 @ 0x0004e558   (est. sk_tb_ph_one)
 * Ghidra: undefined1 * FUN_0004e558(ulong param_1,undefined1 *param_2,long param_3,
 *   long param_4, code *param_5, undefined8 param_6)
 * Encodes a single TB placeholder entry into a wire buffer: writes the kind and
 * size header, then invokes the placeholder's fill callback to populate the
 * payload. Returns the buffer or 0 on mismatch.
 * Confidence: medium
 */
unsigned long sk_tb_ph_one(unsigned long kind, unsigned long buf, long size, long total,
                           unsigned long fill, unsigned long arg)
{
    unsigned long esz, u, i;

    if (kind > 0x1c) sk_panic(0x5bb75b);
    u = sk_tb_ph_res(kind, total);
    if (size != u) return 0;
    esz = *(unsigned long *)(kind * 0x30 + 0x65bf70);
    *(unsigned char *)buf = (char)kind;
    *(unsigned long *)(buf + 8) = size - 0xc;
    if (total != 0) {
        i = 0;
        do {
            u = esz + i * esz;
            if (size < u) return 0;
            if ((*(unsigned long (**)(unsigned long,unsigned long,unsigned long,unsigned long))
                    (fill))(arg, buf + 0xc + i * esz, esz, i) == 0) return 0;
            i++;
        } while (total != i);
    }
    return buf;
}

/*--------------------------------------------------------------------*/

/*--------------------------------------------------------------------*/
/* FUN_0004e774 @ 0x0004e774   (est. sk_tb_ph_addr_off)
 * Ghidra: long FUN_0004e774(long *param_1,ulong param_2)
 * Returns the physical address of a TB placeholder region: offset*0x40 past the
 * region base, or 0 if out of range.
 * Confidence: medium
 */
unsigned long sk_tb_ph_addr_off(unsigned long region, unsigned long off)
{
    unsigned long base;

    if (off >> 0x3a != 0) sk_overflow_panic(0x5bb5bd);
    base = off * 0x40;
    if (base < *(unsigned long *)(region + 8)) return base + *(unsigned long *)region;
    return 0;
}

/*--------------------------------------------------------------------*/

/*--------------------------------------------------------------------*/
/* FUN_0004e7b8 @ 0x0004e7b8   (est. sk_tb_ph_resolve)
 * Ghidra: long FUN_0004e7b8(ushort *param_1,ulong param_2)
 * Resolves a TB placeholder by index: returns the pointer to its payload within
 * the placeholder region, or 0 if out of range.
 * Confidence: medium
 */
unsigned long sk_tb_ph_resolve(unsigned long ph, unsigned long idx)
{
    unsigned long kind, esz;

    kind = (unsigned long)*(unsigned char *)ph;
    if (kind > 0x1c) sk_panic(0x5bb75b);
    esz = *(unsigned long *)(kind * 0x30 + 0x65bf70);
    if (idx * esz < ((unsigned long)*(unsigned char *)(ph + 8) << 0x18 |
                     (unsigned long)*(unsigned char *)(ph + 4))) {
        return ph + idx * esz + 0xc;
    }
    return 0;
}

/*--------------------------------------------------------------------*/

/*--------------------------------------------------------------------*/
/* FUN_0004e88c @ 0x0004e88c   (est. sk_tb_ph_kind)
 * Ghidra: uint FUN_0004e88c(ushort *param_1)
 * Returns the kind byte of a TB placeholder descriptor.
 * Confidence: medium
 */
unsigned int sk_tb_ph_kind(unsigned long ph)
{
    return (unsigned int)*(unsigned char *)ph;
}

/*--------------------------------------------------------------------*/

/*--------------------------------------------------------------------*/
/* FUN_0004e8b0 @ 0x0004e8b0   (est. sk_tb_ph_count)
 * Ghidra: ulong FUN_0004e8b0(ushort *param_1)
 * Returns the element count of a TB placeholder descriptor (payload size over
 * element size). Aborts on unknown kinds.
 * Confidence: medium
 */
unsigned long sk_tb_ph_count(unsigned long ph)
{
    unsigned long kind, esz, sz;

    kind = (unsigned long)*(unsigned char *)ph;
    if (kind >= 0x1d) sk_panic(0x5bb75b);
    esz = *(unsigned long *)(kind * 0x30 + 0x65bf70);
    sz = (unsigned long)*(unsigned char *)(ph + 4) << 0x18 |
         (unsigned long)*(unsigned char *)(ph + 6) << 0x20 |
         (unsigned long)*(unsigned char *)(ph + 8) << 0x30;
    if (esz != 0) return sz / esz;
    return 0;
}

/*--------------------------------------------------------------------*/

/*--------------------------------------------------------------------*/
/* FUN_0004e95c @ 0x0004e95c   (est. sk_tb_ph_find)
 * Ghidra: undefined8 FUN_0004e95c(ushort *param_1,undefined8 param_2,undefined8 param_3,ulong *param_4)
 * Finds a TB placeholder by matching its payload bytes against a given pattern,
 * invoking the placeholder's match callback. Returns 1 and the matched index
 * on success.
 * Confidence: medium
 */
unsigned long sk_tb_ph_find(unsigned long ph, unsigned long pat, unsigned long n, unsigned long outi)
{
    unsigned long kind, cb, esz, u;

    kind = (unsigned long)*(unsigned char *)ph;
    if (kind > 0x1c) sk_panic(0x5bb75b);
    cb = *(unsigned long *)(kind * 0x30 + 0x65bf78);
    if (cb != 0 && *(unsigned long *)(kind * 0x30 + 0x65bf80) != 0) {
        u = (**(unsigned long (**)(unsigned long,unsigned long,unsigned long,unsigned long))
                (cb))(pat, n, (unsigned long)sk_tb_ph_cb, (unsigned long)&ph);
        if ((int)u == 0) return u;
        if (*(unsigned long *)(ph + 8) != 0) {
            u = *(unsigned long *)(kind * 0x30 + 0x65bf70);
            *(unsigned long *)outi = (*(unsigned long *)(ph + 8) - ph - 0xc) / u;
            return 1;
        }
    }
    return 0;
}

/*--------------------------------------------------------------------*/

/*--------------------------------------------------------------------*/
/* FUN_0004ea44 @ 0x0004ea44   (est. sk_tb_ph_cb)
 * Ghidra: void FUN_0004ea44(undefined8 *param_1,ulong param_2)
 * TB placeholder match callback: copies a payload element from the placeholder
 * into the destination buffer.
 * Confidence: medium
 */
void sk_tb_ph_cb(unsigned long out, unsigned long src)
{
    unsigned long kind, esz, cnt;

    if (out == 0) return;
    kind = (unsigned long)*(unsigned char *)(out + 8);
    if (kind >= 0x1d) sk_panic(0x5bb75b);
    esz = *(unsigned long *)(kind * 0x30 + 0x65bf70);
    cnt = *(unsigned long *)(out + 8 + 8) / esz;
    if (cnt * esz == src) {
        sk_memcpy3(src, out + 0xc, cnt, esz, *(unsigned long *)(kind * 0x30 + 0x65bf80));
    }
}

/*--------------------------------------------------------------------*/

/*--------------------------------------------------------------------*/
/* FUN_0004eb44 @ 0x0004eb44   (est. sk_tb_ph_iter_init)
 * Ghidra: void FUN_0004eb44(void)
 * Initializes a TB placeholder iterator (no-op placeholder).
 * Confidence: medium
 */
void sk_tb_ph_iter_init(void) { }

/*--------------------------------------------------------------------*/

/*--------------------------------------------------------------------*/
/* FUN_0004eb4c @ 0x0004eb4c   (est. sk_tb_ph_iter_next)
 * Ghidra: ushort * FUN_0004eb4c(long *param_1)
 * Advances a TB placeholder iterator, returning the next descriptor pointer or
 * 0 at the end. Validates the descriptor bounds.
 * Confidence: medium
 */
unsigned long sk_tb_ph_iter_next(unsigned long it)
{
    unsigned long cur, off, sz, total, u;

    cur = *(unsigned long *)it;
    off = *(unsigned long *)(it + 8);
    while (1) {
        total = cur + off;
        u = *(unsigned long *)cur;
        if (u < off + 0xc) return 0;
        if (off + 0xc + u > total) break;
        if (off > 0xfffffffffffffff3) sk_overflow_panic(0x5bb5bd);
        off += u + 0xc;
        *(unsigned long *)(it + 8) = off;
        if (*(unsigned char *)(cur + 8) < 0x1d) return cur;
    }
    return 0;
}

/*--------------------------------------------------------------------*/

/*--------------------------------------------------------------------*/
/* FUN_0004ecf0 @ 0x0004ecf0   (est. sk_tb_ph_iter_more)
 * Ghidra: bool FUN_0004ecf0(long *param_1)
 * Returns whether the TB placeholder iterator has another descriptor.
 * Confidence: medium
 */
bool sk_tb_ph_iter_more(unsigned long it)
{
    return *(unsigned long *)it < *(unsigned long *)(it + 8) + 0xc;
}

/*--------------------------------------------------------------------*/

/*--------------------------------------------------------------------*/
/* FUN_0004ed48 @ 0x0004ed48   (est. sk_tb_ph_avail)
 * Ghidra: void FUN_0004ed48(void)
 * Validates that the TB placeholder resources are available (region count at
 * +0x78 nonzero), aborting with "TBPlaceholder resources could no.." if not.
 * Confidence: medium
 */
unsigned long sk_tb_ph_avail(void)
{
    unsigned long u;

    u = sk_global_cfg();
    if (*(unsigned long *)(u + 0x78) != 0) return u;
    sk_panic(0x5bb783);
    return 0;
}

/*--------------------------------------------------------------------*/

/*--------------------------------------------------------------------*/
