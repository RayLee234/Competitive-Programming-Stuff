//
//  main.cpp
//  BLO LUOGU3469
//
//  Created by Ruining Li on 2020/10/6.
//  Copyright © 2020 Ruining Li. All rights reserved.
//

#include <iostream>
#include <cstdio>
#define int long long
using namespace std;
int n, m, tot, ver[1000010], Next[1000010], Head[100010], ans[100010], dfn[100010], low[100010], Size[100010], t;
bool cut[100010];
void add(int x, int y) {
    ver[++tot] = y, Next[tot] = Head[x], Head[x] = tot;
}
void tarjan(int x) {
    int flag = 0, cnt = 0;
    low[x] = dfn[x] = ++t;
    Size[x] = 1;
    for(int i=Head[x];i;i=Next[i]) {
        int y = ver[i];
        if(!dfn[y]) {
            tarjan(y);
            low[x] = min(low[x], low[y]);
            Size[x] += Size[y];
            if(dfn[x] <= low[y]) {
                ++flag;
                if(x != 1 || flag > 1) {
                    cut[x] = 1;
                    cnt += Size[y];
                    ans[x] += Size[y] * (n - Size[y]);
                }
            }
        }
        else low[x] = min(low[x], dfn[y]);
    }
    ans[x] += (n-1-cnt) * (cnt + 1) + (n-1);
}
signed main() {
    scanf("%d %d", &n, &m);
    for(int i=1;i<=m;++i) {
        int x, y; cin >> x >> y;
        add(x, y), add(y, x);
    }
    tarjan(1);
    for(int i=1;i<=n;++i) printf("%lld\n", ans[i]);
    return 0;
}
