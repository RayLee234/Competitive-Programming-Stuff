//
//  main.cpp
//  天天爱跑步 LUOGU1600
//
//  Created by Ruining Li on 2020/9/19.
//  Copyright © 2020 Ruining Li. All rights reserved.
//

#include <iostream>
#include <cstring>
#include <vector>
using namespace std;
int n, m, w[300010], d[300010], s[300010], t[300010], lca[300010], f[300010], fa[300010], v[300010], c[600010], ans[300010];
vector <int> g[300010], add[300010], del[300010];
vector < pair<int,int> > query[300010];
int find(int x) {
    if(f[x] == x) return x;
    return f[x] = find(f[x]);
}
void tarjan(int x) {
    v[x] = 1;
    for(int i=0;i<g[x].size();++i) {
        int y = g[x][i];
        if(v[y]) continue;
        d[y] = d[x] + 1;
        tarjan(y);
        f[y] = fa[y] = x;
    }
    for(int i=0;i<query[x].size();++i) {
        int y = query[x][i].first, id = query[x][i].second;
        if(v[y] == 2) lca[id] = find(y);
    }
    v[x] = 2;
}
void dfs1(int x) {
    int cnt = c[d[x] + w[x]];
    for(int i=0;i<add[x].size();++i) ++c[add[x][i]];
    for(int i=0;i<del[x].size();++i) --c[del[x][i]];
    for(int i=0;i<g[x].size();++i) {
        int y = g[x][i];
        if(d[y] <= d[x]) continue;
        dfs1(y);
    }
    ans[x] += c[d[x] + w[x]] - cnt;
}
void dfs2(int x) {
    int cnt = c[w[x] - d[x] + 300000];
    for(int i=0;i<add[x].size();++i) ++c[add[x][i]];
    for(int i=0;i<del[x].size();++i) --c[del[x][i]];
    for(int i=0;i<g[x].size();++i) {
        int y = g[x][i];
        if(d[y] <= d[x]) continue;
        dfs2(y);
    }
    ans[x] += c[w[x] - d[x] + 300000] - cnt;
}
int main() {
    cin >> n >> m;
    for(int i=1;i<n;++i) {
        int x, y; cin >> x >> y;
        g[x].push_back(y), g[y].push_back(x);
    }
    for(int i=1;i<=n;++i) cin >> w[i], f[i] = i;
    for(int i=1;i<=m;++i) {
        cin >> s[i] >> t[i];
        if(s[i] == t[i]) lca[i] = s[i];
        else query[s[i]].push_back(make_pair(t[i], i)), query[t[i]].push_back(make_pair(s[i], i));
    }
    tarjan(1);
    // first half: d[s] - d[x] = w[x] ==> d[s] = d[x] + w[x]
    for(int i=1;i<=m;++i) {
        add[s[i]].push_back(d[s[i]]);
        if(fa[lca[i]]) del[fa[lca[i]]].push_back(d[s[i]]);
    }
    dfs1(1);
    // second half: d[x] + d[s] - 2 * d[lca] = w[x] ==> d[s] - 2 * d[lca] = w[x] - d[x]
    memset(c, 0, sizeof(c));
    for(int i=1;i<=n;++i) add[i].clear(), del[i].clear();
    for(int i=1;i<=m;++i) add[t[i]].push_back(d[s[i]] - 2 * d[lca[i]] + 300000), del[lca[i]].push_back(d[s[i]] - 2 * d[lca[i]] + 300000);
    dfs2(1);
    for(int i=1;i<=n;++i) cout << ans[i] << ' ';
    cout << endl;
    return 0;
}
