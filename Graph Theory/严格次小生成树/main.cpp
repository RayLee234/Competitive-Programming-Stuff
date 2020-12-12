//
//  main.cpp
//  严格次小生成树 LUOGU4180
//
//  Created by Ruining Li on 2020/9/20.
//  Copyright © 2020 Ruining Li. All rights reserved.
//

#include <iostream>
#include <algorithm>
#include <vector>
#define int long long
using namespace std;
int n, m, tot, u[300010], v[300010], w[300010], fa[100010], dep[100010], f[100010][20], d[100010][20][2], jud[300010], MST, ans = 1e18;
int MAX[2];
struct edge {
    int x, y, z;
}e[300010];
vector < pair<int,int> > g[100010];
int find(int x) {
    if(fa[x] == x) return x;
    return fa[x] = find(fa[x]);
}
bool cmp(edge x, edge y) {
    return x.z < y.z;
}
void dfs(int x) {
    for(int i=0;i<g[x].size();++i) {
        int y = g[x][i].first, dis = g[x][i].second;
        if(dep[y]) continue;
        dep[y] = dep[x] + 1;
        f[y][0] = x;
        d[y][0][0] = dis, d[y][0][1] = -1e9;
        for(int j=1;j<20;++j) {
            f[y][j] = f[f[y][j-1]][j-1];
            d[y][j][0] = max(d[y][j-1][0], d[f[y][j-1]][j-1][0]);
            if(d[y][j-1][0] == d[f[y][j-1]][j-1][0]) d[y][j][1] = max(d[y][j-1][1], d[f[y][j-1]][j-1][1]);
            else if(d[y][j-1][0] < d[f[y][j-1]][j-1][0]) d[y][j][1] = max(d[y][j-1][0], d[f[y][j-1]][j-1][1]);
            else d[y][j][1] = max(d[y][j-1][1], d[f[y][j-1]][j-1][0]);
        }
        dfs(y);
    }
}
void lca(int x, int y) {
    MAX[0] = 0, MAX[1] = -1e9;
    if(dep[x] < dep[y]) swap(x, y);
    for(int i=19;i>=0;--i)
        if(dep[f[x][i]] >= dep[y]) {
            if(MAX[0] == d[x][i][0]) MAX[1] = max(MAX[1], d[x][i][1]);
            else if(MAX[0] < d[x][i][0]) MAX[1] = max(MAX[0], d[x][i][1]);
            else MAX[1] = max(MAX[1], d[x][i][0]);
            MAX[0] = max(MAX[0], d[x][i][0]);
            x = f[x][i];
        }
    if(x == y) return;
    for(int i=19;i>=0;--i)
        if(f[x][i] != f[y][i]) {
            if(MAX[0] == d[x][i][0]) MAX[1] = max(MAX[1], d[x][i][1]);
            else if(MAX[0] < d[x][i][0]) MAX[1] = max(MAX[0], d[x][i][1]);
            else MAX[1] = max(MAX[1], d[x][i][0]);
            MAX[0] = max(MAX[0], d[x][i][0]);
            x = f[x][i];
            if(MAX[0] == d[y][i][0]) MAX[1] = max(MAX[1], d[y][i][1]);
            else if(MAX[0] < d[y][i][0]) MAX[1] = max(MAX[0], d[y][i][1]);
            else MAX[1] = max(MAX[1], d[y][i][0]);
            MAX[0] = max(MAX[0], d[y][i][0]);
            y = f[y][i];
        }
    if(d[x][0][0] < MAX[0]) MAX[1] = max(MAX[1], d[x][0][0]);
    else if(d[x][0][0] > MAX[0]) MAX[1] = MAX[0];
    MAX[0] = max(MAX[0], d[x][0][0]);
    if(d[y][0][0] < MAX[0]) MAX[1] = max(MAX[1], d[y][0][0]);
    else if(d[y][0][0] > MAX[0]) MAX[1] = MAX[0];
    MAX[0] = max(MAX[0], d[y][0][0]);
}
signed main() {
    cin >> n >> m;
    for(int i=1;i<=n;++i) fa[i] = i;
    for(int i=1;i<=m;++i) {
        int x, y, z; cin >> x >> y >> z;
        if(x != y) e[++tot].x = x, e[tot].y = y, e[tot].z = z;
    }
    sort(e+1, e+tot+1, cmp);
    for(int i=1;i<=tot;++i) {
        int fx = find(e[i].x), fy = find(e[i].y);
        if(fx != fy) {
            fa[fx] = fy;
            jud[i] = 1; MST += e[i].z;
        }
    }
    for(int i=1;i<=tot;++i)
        if(jud[i]) {
            int x = e[i].x, y = e[i].y, z = e[i].z;
            g[x].push_back(make_pair(y, z)), g[y].push_back(make_pair(x, z));
        }
    dep[1] = 1;
    dfs(1);
    for(int i=1;i<=tot;++i)
        if(!jud[i]) {
            int x = e[i].x, y = e[i].y, z = e[i].z;
            lca(x, y);
            if(MAX[0] < z) ans = min(ans, MST - MAX[0] + z);
            else ans = min(ans, MST - MAX[1] + z);
        }
    cout << ans << endl;
    return 0;
}
