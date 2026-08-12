import re

fn = 'osfmk/arm64/sk/sk_region_sched.c'
lines = open(fn).read().split('\n')

# symbol -> definition signature (ret, args) gathered from find_defs.py output
sig = {
 'FUN_00181b3c': ('void','uint64_t p1, uint64_t p2, char p3, uint64_t p4, uint64_t p5'),
 'FUN_00186094': ('uint64_t','uint8_t p1, uint64_t p2, long p3'),
 'FUN_00186460': ('void','uint8_t p1, uint64_t p2'),
 'FUN_001866dc': ('uint64_t','uint8_t p1, uint64_t p2, long p3'),
 'FUN_00186aa8': ('void','uint8_t p1, uint64_t p2, uint64_t *p3'),
 'FUN_00186e3c': ('void','uint8_t p1, uint64_t p2, uint64_t *p3'),
 'FUN_001871d0': ('void','uint8_t p1, uint64_t p2, long p3'),
 'FUN_0018758c': ('void','uint8_t p1, uint8_t p2, uint64_t p3'),
 'FUN_00187820': ('uint64_t','uint8_t p1, uint64_t p2'),
 'FUN_00187aac': ('uint8_t','uint8_t p1'),
 'FUN_0018e38c': ('void','uint8_t *out, uint8_t v'),
 'FUN_0019da34': ('void','unsigned long param_1,long param_2,unsigned long param_3, ...'),
 'FUN_0019e93c': ('long','param_1'),
 'FUN_0019f1ec': ('void','unsigned long param_1, ...'),
 'sk_r4_001c877c': ('void','float2 p1'),
 'sk_r4_001cd1e0': ('void','uint64_t p1,uint64_t p2,uint64_t p3,uint8_t p4'),
 'sk_r4_001cd70c': ('void','uint64_t p1,uint64_t p2,uint64_t p3,uint8_t p4'),
 'sk_swift_array_reserve': ('void','void'),
 'sk_swift_fatal': ('void','const char *p1, uint64_t p2, uint32_t p3, ...'),
}
# sk_r4_001c1388 def not captured; handle separately

for sym,(rt,args) in sig.items():
    for i,l in enumerate(lines):
        # forward decl: TYPE SYM();  (no args)
        m = re.match(r'^([A-Za-z_][\w\s\*]*?)\b%s\(\)\s*;\s*$' % re.escape(sym), l)
        if m:
            old = l
            if args == 'void':
                new = f'{rt} {sym}(void);'
            else:
                new = f'{rt} {sym}({args});'
            lines[i] = new
            print(f'{sym}: replaced fwd decl "{old.strip()}" -> "{new}"')
            break

open(fn,'w').write('\n'.join(lines))
print('done')
