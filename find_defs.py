import re

fn = 'osfmk/arm64/sk/sk_region_sched.c'
lines = open(fn).read().split('\n')

# conflicting symbols from clang
conflicts = ['FUN_00181b3c','FUN_00186094','FUN_00186460','FUN_001866dc','FUN_00186aa8',
'FUN_00186e3c','FUN_001871d0','FUN_0018758c','FUN_00187820','FUN_00187aac','FUN_0018e38c',
'FUN_0019da34','FUN_0019e93c','FUN_0019f1ec','sk_r4_001c1388','sk_r4_001c877c','sk_r4_001cd1e0',
'sk_r4_001cd70c','sk_swift_array_reserve','sk_swift_fatal']

# For each symbol, find: (a) forward decl line `TYPE SYM();`, (b) definition `TYPE SYM(args) {`
defsig = {}
for i,l in enumerate(lines):
    for sym in conflicts:
        # definition: line starts with a type then sym( ... )
        m = re.match(r'^([A-Za-z_][\w\s\*]*?)\b%s\((.*?)\)$' % re.escape(sym), l)
        if m and '(' in l and l.rstrip().endswith(')') and '{' not in l:
            # could be a prototype with ;  -> skip; definition usually has params and next line {
            if l.rstrip().endswith(';'):
                continue
            # definition without trailing ';' and no '{' (brace on next line)
            if sym not in defsig:
                defsig[sym] = (i, m.group(1).strip(), m.group(2).strip())
for sym,(i,rt,args) in sorted(defsig.items()):
    print(sym, 'def@',i, 'ret=',repr(rt), 'args=',repr(args))
