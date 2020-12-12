//
//  main.cpp
//  True Liars POJ1417
//
//  Created by Ruining Li on 2020/4/2.
//  Copyright © 2020 Ruining Li. All rights reserved.
//

#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int n,p,q,f[1201],d[1201],c,belong[1201],s[1201],t[1201],ans[1201],cnt;
unsigned long long g[1201][601];
bool now[1201][601];
int find(int x) {
    if(f[x] == x) return x;
    int y = find(f[x]);
    d[x] ^= d[f[x]];
    return f[x] = y;
}
int main() {
    while(scanf("%d %d %d",&n, &p, &q) && (n || p || q) ) {
        memset(d, 0, sizeof(d));
        for(int i=1;i<=p+q;++i) f[i] = i;
        while(n--) {
            int x, y; char reply[4];
            scanf("%d %d %s", &x, &y, reply);
            int fx = find(x), fy = find(y);
            if(fx == fy) continue;
            if(reply[0] == 'y') d[fy] = d[x] xor d[y], f[fy] = fx;
            else d[fy] = d[x] xor d[y] xor 1, f[fy] = fx;
        }
        c = 0;
        memset(belong, 0, sizeof(belong));
        memset(s, 0, sizeof(s));
        memset(t, 0, sizeof(t));
        for(int i=1;i<=p+q;++i) {
            int cur = find(i);
            if(belong[cur] == 0) {
                belong[cur] = ++c;
                if(d[i]) ++t[c]; else ++s[c];
            }
            else {
                if(d[i]) ++t[belong[cur]];
                else ++s[belong[cur]];
            }
        }
        memset(g, 0, sizeof(g)); g[0][0] = 1;
        memset(now, 0, sizeof(now));
        for(int i=1;i<=c;++i)
            for(int j=0;j<=p;++j) {
                if(j >= s[i]) g[i][j] += g[i-1][j-s[i]];
                if(j >= t[i]) g[i][j] += g[i-1][j-t[i]];
                if(j >= t[i] && g[i-1][j-t[i]] > 0) now[i][j] = 1;
            }
        if(g[c][p] > 1) puts("no");
        else {
            int curc = c, curp = p; cnt = 0;
            while(curc) {
                for(int i=1;i<=p+q;++i)
                    if(belong[f[i]] == curc && d[i] == now[curc][curp]) ans[++cnt] = i;
                if(now[curc][curp]) curp -= t[curc];
                else curp -= s[curc];
                --curc;
            }
            sort(ans+1, ans+cnt+1);
            for(int i=1;i<=cnt;++i) printf("%d\n",ans[i]);
            puts("end");
        }
    }
    return 0;
}
