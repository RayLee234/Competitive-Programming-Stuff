//
//  main.cpp
//  Island LUOGU4381
//
//  Created by Ruining Li on 2020/9/22.
//  Copyright © 2020 Ruining Li. All rights reserved.
//

#include <iostream>
#include <vector>
#include <cstring>
#include <cstdio>
#include <queue>
#define int long long
using namespace std;
int n, d[1000010], a[1000010], s[1000010], Q[1000010], deg[1000010], D, ans, u[2000010], w[2000010], len;
bool v[1000010], isLoop[1000010];
queue <int> q;
vector < pair<int,int> > g[1000010];
vector <int> loop;
void toposort() {
    for(register int i=1;i<=n;++i)
        if(deg[i] == 0) q.push(i);
    while(!q.empty()) {
        int x = q.front(); isLoop[x] = 0; q.pop();
        if(--deg[a[x]] == 0) q.push(a[x]);
    }
}
void dfs(int x) {
    v[x] = 1;
    if(isLoop[x]) loop.push_back(x);
    for(register int i=0;i<g[x].size();++i) {
        int y = g[x][i].first, dis = g[x][i].second;
        if(v[y]) {
            if(isLoop[y]) len = s[x] + dis;
            continue;
        }
        if(isLoop[y]) s[y] = s[x] + dis;
        dfs(y);
        if(!isLoop[y]) D = max(D, d[x] + d[y] + dis), d[x] = max(d[x], d[y] + dis);
    }
}
signed main() {
    scanf("%d", &n);
    for(register int i=1;i<=n;++i) {
        int l; scanf("%d %d", &a[i], &l);
        ++deg[a[i]];
        g[a[i]].push_back(make_pair(i, l));
    }
    memset(isLoop, 1, sizeof(isLoop));
    toposort();
    for(register int i=1;i<=n;++i)
        if(isLoop[i] && !v[i]) {
            D = 0;
            loop.clear(), loop.push_back(-1);
            dfs(i);
            int m = loop.size() - 1;
            for(register int j=1;j<=m;++j) u[j] = loop[j], w[j] = s[loop[j]];
            w[m+1] = len, u[m+1] = u[1];
            for(register int j=m+2;j<=2*m;++j) u[j] = u[j-m], w[j] = w[j-1] + w[j-m] - w[j-m-1];
            int cur = 1, L = 0, R = -1;
            for(register int j=m+1;j<=2*m;++j) {
                while(L <= R && j - Q[L] >= m) ++L;
                while(w[j] - w[cur] >= (len+1) / 2) {
                    if(j - cur >= m) { ++cur; continue; }
                    while(L <= R && d[u[Q[R]]] - w[Q[R]] <= d[u[cur]] - w[cur]) --R;
                    Q[++R] = cur; ++cur;
                }
                if(L <= R) D = max(D, d[u[Q[L]]] + d[u[j]] + w[j] - w[Q[L]]);
            }
            ans += D;
        }
    printf("%lld\n", ans);
    return 0;
}
