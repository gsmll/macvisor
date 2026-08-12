import re, sys
for i in range(8):
    f=f'osfmk/arm64/sk/sk_region_sched_{i}.c'
    lines=open(f).read().splitlines()
    zero=set(); param=set()
    for ln in lines:
        s=ln.strip()
        # zero-arg forward decl: <type> FUN_xxxx();
        m=re.match(r'^(?:extern\s+)?[A-Za-z_][\w\s\*]*?\b(FUN_[0-9a-f]{6})\(\)\s*;\s*$', s)
        if m:
            zero.add(m.group(1))
        # any decl with '('
        m2=re.match(r'^(?:extern\s+)?[\w\s\*]*?\b(FUN_[0-9a-f]{6})\(', s)
        if m2:
            param.add(m2.group(1))
    only_zero=zero-param
    print(i, 'zero',len(zero),'param',len(param),'only_in_zero',len(only_zero), sorted(only_zero)[:10])
