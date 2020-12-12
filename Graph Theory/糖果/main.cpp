//
//  main.cpp
//  糖果 LUOGU3275
//
//  Created by Ruining Li on 2020/10/8.
//  Copyright © 2020 Ruining Li. All rights reserved.
//

#include <iostream>
#include <stack>
#include <queue>
#include <vector>
#define int long long
using namespace std;
int n, m, d[100001], low[100001], dfn[100001], t, ver[200001], Next[200001], head[100001], val[200001], tot, in[100001], c[100001], cnt, num[100001];
bool vis[100001], is_1[100001];
stack <int> S;
queue <int> q;
void add(int x, int y, int type) {
    ver[++tot] = y, val[tot] = type, Next[tot] = head[x], head[x] = tot;
}
vector < pair<int,int> > g[100001];
void tarjan(int x) {
    low[x] = dfn[x] = ++t;
    vis[x] = 1;
    S.push(x);
    for(int i=head[x];i;i=Next[i]) {
        int y = ver[i];
        if(!dfn[y]) {
            tarjan(y);
            low[x] = min(low[x], low[y]);
        }
        else if(vis[y]) low[x] = min(low[x], dfn[y]);
    }
    if(low[x] == dfn[x]) {
        ++cnt;
        int pre_num = S.size();
        while(S.top() != x) c[S.top()] = cnt, vis[S.top()] = 0, S.pop();
        c[x] = cnt, vis[x] = 0, S.pop();
        num[cnt] = pre_num - S.size();
    }
}
signed main() {
    cin >> n >> m;
    for(int i=1;i<=m;++i) {
        int x, a, b; cin >> x >> a >> b;
        if(x == 1) add(a, b, 0), add(b, a, 0);
        if(x == 2) add(a, b, 1);
        if(x == 3) add(b, a, 0);
        if(x == 4) add(b, a, 1);
        if(x == 5) add(a, b, 0);
    }
    for(int i=1;i<=n;++i) if(!dfn[i]) tarjan(i);
    for(int x=1;x<=n;++x)
        for(int j=head[x];j;j=Next[j]) {
            int y = ver[j];
            if(c[x] == c[y] && val[j] == 1) { cout << -1 << endl; return 0; }
            if(c[x] == c[y]) continue;
            ++in[c[y]];
            g[c[x]].push_back(make_pair(c[y], val[j]));
        }
    for(int i=1;i<=cnt;++i) if(!in[i]) { q.push(i); d[i] = 1; }
    while(!q.empty()) {
        int x = q.front(); q.pop();
        for(int i=0;i<g[x].size();++i) {
            int y = g[x][i].first, dis = g[x][i].second;
            d[y] = max(d[y], d[x] + dis);
            if(--in[y] == 0) q.push(y);
        }
    }
    int ans = 0;
    for(int i=1;i<=cnt;++i) ans += d[i] * num[i];
    cout << ans << endl;
    return 0;
}
