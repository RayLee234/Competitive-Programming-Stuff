//
//  main.cpp
//  舞动的夜晚 CH#17C
//
//  Created by Ruining Li on 2020/10/26.
//  Copyright © 2020 Ruining Li. All rights reserved.
//

#include <iostream>
#include <queue>
#include <cstring>
#include <stack>
#include <vector>
using namespace std;
const int inf = (1 << 29);
int n, m, t, s, e;
int ver[300010], head[20010], Next[300010], edge[300010], tot = 1, maxflow;
int d[20010], now[20010];
void add(int x, int y, int z) {
    ver[++tot] = y, edge[tot] = z, Next[tot] = head[x], head[x] = tot;
    ver[++tot] = x, edge[tot] = 0, Next[tot] = head[y], head[y] = tot;
}
bool bfs() {
    cout << 1 << endl;
    getchar();
    queue <int> q;
    memset(d, 0, sizeof(d));
    q.push(s); d[s] = 1; now[s] = head[s];
    while(!q.empty()) {
        int x = q.front(); q.pop();
        for(int i=head[x];i;i=Next[i]) {
            int y = ver[i];
            if(d[y] || edge[i] <= 0) continue;
            d[y] = d[x] + 1;
            now[y] = head[y];
            if(y == e) return 1;
            q.push(y);
        }
    }
    return 0;
}
int dinic(int x, int flow) {
    cout << x << ' ' << flow << endl;
    if(x == t) return flow;
    int rest = flow, k, i;
    for(i=now[x];i && rest;i=Next[i]) {
        int y = ver[i];
        if(d[y] != d[x] + 1 || edge[i] <= 0) continue;
        k = dinic(y, min(rest, edge[i]));
        if(k == 0) d[y] = 0;
        edge[i] -= k;
        edge[i xor 1] += k;
        rest -= k;
    }
    now[x] = i;
    return flow - rest;
}
stack <int> S;
vector <int> scc[20010];
int dfn[20010], low[20010], T, c[20010], cnt;
bool vis[20010];
void tarjan(int x) {
    low[x] = dfn[x] = ++T;
    S.push(x);
    vis[x] = 1;
    for(int i=head[x];i;i=Next[i]) {
        int y = ver[i];
        if(edge[i] <= 0) continue;
        if(!dfn[y]) {
            tarjan(y);
            low[x] = min(low[x], low[y]);
        }
        else if(vis[y]) low[x] = min(low[x], dfn[y]);
    }
    if(low[x] == dfn[x]) {
        ++cnt;
        while(S.top() != x) {
            int tmp = S.top(); S.pop();
            c[tmp] = cnt;
            scc[cnt].push_back(tmp);
            S.pop(); vis[tmp] = 0;
        }
        vis[x] = 0, S.pop(), c[x] = cnt, scc[cnt].push_back(x);
    }
}
int main() {
    cin >> n >> m >> t;
    s = 0, e = n + m + 1;
    for(int i=1;i<=t;++i) {
        int x, y; cin >> x >> y;
        add(x, y+m, 1);
    }
    for(int i=1;i<=n;++i) add(s, i, 1);
    for(int i=n+1;i<=n+m;++i) add(i, e, 1);
    int flow = 0;
    while(bfs()) {
        while(flow = dinic(s, inf)) maxflow += flow;
    }
    int ans = 0;
    for(int i=1;i<=n;++i) {
        for(int j=head[i];j;j=Next[j]) {
            if(edge[j] == 0 || c[ver[j]] == c[i]) ans++;
        }
    }
    cout << t - ans << endl;
    return 0;
}
