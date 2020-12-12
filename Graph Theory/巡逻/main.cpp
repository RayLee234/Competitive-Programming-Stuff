//
//  main.cpp
//  巡逻 LUOGU3629
//
//  Created by Ruining Li on 2020/8/13.
//  Copyright © 2020 Ruining Li. All rights reserved.
//

#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;
int n, k, d[100010], f[100010], l1, l2;
bool c[100010], v[100010];
queue <int> q;
vector < pair<int,int> > g[100010];
void dfs(int x) {
    v[x] = 1;
    if(x != 1 && g[x].size() == 1) {
        d[x] = f[x] = 0;
        return;
    }
    for(int i=0;i<g[x].size();++i) {
        int y = g[x][i].first;
        if(v[y]) continue;
        dfs(y);
        l2 = max(l2, d[x] + d[y] + (c[g[x][i].second] ? -1 : 1) );
        d[x] = max(d[x], d[y] + (c[g[x][i].second] ? -1 : 1) );
    }
}
int main() {
    cin >> n >> k;
    for(int i=1;i<n;++i) {
        int x, y; cin >> x >> y;
        g[x].push_back(make_pair(y,i)), g[y].push_back(make_pair(x,i));
    }
    q.push(1);
    memset(d, -1, sizeof(d)); d[1] = 0;
    while(!q.empty()) {
        int x = q.front(); q.pop();
        for(int i=0;i<g[x].size();++i) {
            int y = g[x][i].first;
            if(d[y] >= 0) continue;
            d[y] = d[x] + 1;
            q.push(y);
        }
    }
    int s = 0;
    for(int i=1;i<=n;++i)
        if(d[i] > d[s]) s = i;
    q.push(s);
    memset(d, -1, sizeof(d)); d[s] = 0;
    while(!q.empty()) {
        int x = q.front(); q.pop();
        for(int i=0;i<g[x].size();++i) {
            int y = g[x][i].first;
            if(d[y] >= 0) continue;
            d[y] = d[x] + 1;
            f[y] = x;
            q.push(y);
        }
    }
    int t = 0;
    for(int i=1;i<=n;++i)
        if(d[i] > d[t]) t = i;
    l1 = d[t];
    while(t != s) {
        for(int i=0;i<g[t].size();++i)
            if(g[t][i].first == f[t]) { c[g[t][i].second] = 1; break; }
        t = f[t];
    }
    for(int i=1;i<=n;++i) f[i] = d[i] = -1e5;
    memset(v, 0, sizeof(v));
    dfs(1);
    if(k == 1) cout << 2 * (n-1) - (l1 - 1) << endl;
    if(k == 2) cout << 2 * (n-1) - (l1 - 1) - (l2 - 1) << endl;
    return 0;
}
