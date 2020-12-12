//
//  main.cpp
//  Network POJ3417
//
//  Created by Ruining Li on 2020/8/14.
//  Copyright © 2020 Ruining Li. All rights reserved.
//

#pragma GCC optimize(3)
#pragma GCC optimize("inline")
#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#define ll long long
using namespace std;
int n, m, lca[100010], v[100010], fa[100010], a[100010], b[100010], head[200010], ver[200010], nex[200010], tot;
ll ans, s[100010];
vector < pair<int,int> > q[100010];
void add(int x, int y) {
    ver[++tot] = y;
    nex[tot] = head[x], head[x] = tot;
}
inline int read() {
    int x = 0; char c = getchar();
    while(c < '0' || c > '9') c = getchar();
    while(c >= '0' && c <= '9') x = (x<<3)+(x<<1)+c-'0', c = getchar();
    return x;
}
inline int find(int x) {
    if(x == fa[x]) return x;
    return fa[x] = find(fa[x]);
}
inline void tarjan(int x) {
    v[x] = 1;
    for(register int i=head[x];i;i=nex[i])  {
        int y = ver[i];
        if(v[y]) continue;
        tarjan(y);
        fa[y] = x;
    }
    for(register int i=0;i<q[x].size();++i) {
        int y = q[x][i].first, id = q[x][i].second;
        if(v[y] == 2) lca[id] = find(y);
    }
    v[x] = 2;
}
inline void dfs(int x) {
    v[x] = 1;
    for(register int i=head[x];i;i=nex[i]) {
        int y = ver[i];
        if(v[y]) continue;
        dfs(y);
        if(s[y] == 1) ++ans;
        if(s[y] == 0) ans += m;
        s[x] += s[y];
    }
}
int main() {
    n = read(), m = read();
    for(register int i=1;i<=n;++i) fa[i] = i;
    for(register int i=1;i<n;++i) {
        int x = read(), y = read();
        add(x, y), add(y, x);
    }
    for(register int i=1;i<=m;++i) {
        a[i] = read(), b[i] = read();
        if(a[i] == b[i]) lca[i] = a[i];
        else q[a[i]].push_back( make_pair(b[i], i) ), q[b[i]].push_back( make_pair(a[i], i) );
    }
    tarjan(1);
    for(register int i=1;i<=m;++i) ++s[a[i]], ++s[b[i]], s[lca[i]]-=2;
    memset(v, 0, sizeof(v));
    dfs(1);
    printf("%lld\n", ans);
    return 0;
}
