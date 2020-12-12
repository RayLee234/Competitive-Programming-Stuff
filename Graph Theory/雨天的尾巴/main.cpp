//
//  main.cpp
//  雨天的尾巴 LUOGU4556
//
//  Created by Ruining Li on 2020/8/14.
//  Copyright © 2020 Ruining Li. All rights reserved.
//

#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <queue>
#include <cstring>
using namespace std;
struct SegmentTree {
    int lc, rc, dat, pos;
} tr[100010 * 20 * 4];
vector <int> g[100010];
vector < pair<int,int> > query[100010];
int n, m, tot, cnt, f[100010], fa[100010], d[100010], root[100010], lca[100010], X[100010], Y[100010], Z[100010], val[100010], v[100010];
int find(int x) {
    if(f[x] == x) return x;
    return f[x] = find(f[x]);
}
void tarjan(int x) {
    v[x] = 1;
    for(int i=0;i<g[x].size();++i) {
        int y = g[x][i];
        if(v[y]) continue;
        tarjan(y);
        f[y] = fa[y] = x;
    }
    for(int i=0;i<query[x].size();++i) {
        int y = query[x][i].first, id = query[x][i].second;
        if(v[y] == 2) lca[id] = find(y);
    }
    v[x] = 2;
}
void insert(int p, int l, int r, int val, int delta) {
    if (l == r) {
        tr[p].dat += delta;
        tr[p].pos = tr[p].dat ? l : 0;
        return;
    }
    int mid = (l + r) >> 1;
    if (val <= mid) {
        if (!tr[p].lc) tr[p].lc = ++tot;
        insert(tr[p].lc, l, mid, val, delta);
    }
    else {
        if (!tr[p].rc) tr[p].rc = ++tot;
        insert(tr[p].rc, mid + 1, r, val, delta);
    }
    tr[p].dat = max(tr[tr[p].lc].dat, tr[tr[p].rc].dat);
    tr[p].pos = tr[tr[p].lc].dat >= tr[tr[p].rc].dat ? tr[tr[p].lc].pos : tr[tr[p].rc].pos;
}

int merge(int p, int q, int l, int r) {
    if (!p) return q;
    if (!q) return p;
    if (l == r) {
        tr[p].dat += tr[q].dat;
        tr[p].pos = tr[p].dat ? l : 0;
        return p;
    }
    int mid = (l + r) >> 1;
    tr[p].lc = merge(tr[p].lc, tr[q].lc, l, mid);
    tr[p].rc = merge(tr[p].rc, tr[q].rc, mid + 1, r);
    tr[p].dat = max(tr[tr[p].lc].dat, tr[tr[p].rc].dat);
    tr[p].pos = tr[tr[p].lc].dat >= tr[tr[p].rc].dat ? tr[tr[p].lc].pos : tr[tr[p].rc].pos;
    return p;
}
void dfs(int x) {
    v[x] = 1;
    for (int i = 0; i < g[x].size(); i++) {
        int y = g[x][i];
        if (v[y]) continue;
        dfs(y);
        root[x] = merge(root[x], root[y], 1, cnt);
    }
}
int main() {
    cin >> n >> m;
    for (int i = 1; i < n; i++) {
        int x, y; cin >> x >> y;
        g[x].push_back(y), g[y].push_back(x);
    }
    for (int i = 1; i <= n; i++) root[i] = ++tot, f[i] = i;
    for (int i = 1; i <= m; i++) {
        cin >> X[i]  >> Y[i] >> Z[i];
        if(X[i] == Y[i]) lca[i] = X[i];
        else query[X[i]].push_back(make_pair(Y[i], i)), query[Y[i]].push_back(make_pair(X[i], i));
        val[i] = Z[i];
    }
    tarjan(1);
    sort(val + 1, val + m + 1);
    cnt = unique(val + 1, val + m + 1) - val - 1;
    for (int i = 1; i <= m; i++) {
        int x = X[i], y = Y[i], p = lca[i];
        int z = lower_bound(val + 1, val + cnt + 1, Z[i]) - val;
        insert(root[x], 1, cnt, z, 1);
        insert(root[y], 1, cnt, z, 1);
        insert(root[p], 1, cnt, z, -1);
        if(fa[p]) insert(root[fa[p]], 1, cnt, z, -1);
    }
    memset(v, 0, sizeof(v));
    dfs(1);
    for(int i=1;i<=n;i++) printf("%d\n", val[tr[root[i]].pos]);
}
