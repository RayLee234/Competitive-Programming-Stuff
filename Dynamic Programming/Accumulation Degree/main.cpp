//
//  main.cpp
//  Accumulation Degree POJ3585
//
//  Created by Ruining Li on 2020/5/18.
//  Copyright © 2020 Ruining Li. All rights reserved.
//

#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>
using namespace std;
int T, n, d[200010], f[200010], deg[200010];
bool v[200010];
vector < pair<int,int> > g[200010];
void dp(int x) {
    v[x] = 1;
    for(int i=0;i<g[x].size();++i) {
        int y = g[x][i].first, c = g[x][i].second;
        if(v[y]) continue;
        dp(y);
        if(deg[y] == 1) d[x] += c;
        else d[x] += min(c, d[y]);
    }
}
void dfs(int x) {
    v[x] = 1;
    for(int i=0;i<g[x].size();++i) {
        int y = g[x][i].first, c = g[x][i].second;
        if(v[y]) continue;
        if(deg[x] == 1) f[y] = d[y] + c;
        else f[y] = d[y] + min(f[x] - min(c, d[y]), c);
        dfs(y);
    }
}
int main() {
    scanf("%d", &T);
    while(T--) {
        scanf("%d", &n);
        for(int i=1;i<=n;++i) g[i].clear();
        memset(deg, 0, sizeof(deg));
        for(int i=1;i<n;++i) {
            int x, y, c; scanf("%d %d %d", &x, &y, &c);
            ++deg[x], ++deg[y];
            g[x].push_back(make_pair(y, c)), g[y].push_back(make_pair(x, c));
        }
        memset(d, 0, sizeof(d));
        memset(v, 0, sizeof(v));
        dp(n);
        memset(v, 0, sizeof(v));
        memset(f, 0, sizeof(f));
        f[n] = d[n];
        dfs(n);
        int ans = 0;
        for(int i=1;i<=n;++i) ans = max(ans, f[i]);
        printf("%d\n", ans);
    }
    return 0;
}
