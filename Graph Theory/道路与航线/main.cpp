//
//  main.cpp
//  道路与航线 LUOGU3008
//
//  Created by Ruining Li on 2020/8/8.
//  Copyright © 2020 Ruining Li. All rights reserved.
//

#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>
#include <queue>
using namespace std;
int n, r, p, s, c[25001], t, d[25001], deg[25001];
bool v[25001];
vector < pair<int,int> > g[25001];
vector <int> belong[25001];
void dfs(int x, int block) {
    v[x] = 1; c[x] = block; belong[block].push_back(x);
    for(int i=0;i<g[x].size();++i)
        if(!v[g[x][i].first]) dfs(g[x][i].first, block);
}
queue <int> Q;
int main() {
    scanf("%d %d %d %d", &n, &r, &p, &s);
    for(int i=1;i<=r;++i) {
        int a, b, cost; scanf("%d %d %d", &a, &b, &cost);
        g[a].push_back(make_pair(b, cost)), g[b].push_back(make_pair(a, cost));
    }
    for(int i=1;i<=n;++i)
        if(!v[i]) dfs(i, ++t);
    for(int i=1;i<=p;++i) {
        int a, b, cost; scanf("%d %d %d", &a, &b, &cost);
        g[a].push_back(make_pair(b,cost));
        ++deg[c[b]];
    }
    for(int i=1;i<=t;++i) if(deg[i] == 0) Q.push(i);
    for(int i=1;i<=n;++i) d[i] = 2e9;
    d[s] = 0;
    memset(v, 0, sizeof(v));
    while(!Q.empty()) {
        int now = Q.front(); Q.pop();
        priority_queue< pair<int,int>, vector< pair<int,int> >, greater< pair<int,int> > > q;
        for(int i=0;i<belong[now].size();++i) q.push(make_pair(d[belong[now][i]], belong[now][i]));
        while(!q.empty()) {
            int cur = q.top().second; q.pop();
            if(v[cur] == 1) continue;
            v[cur] = 1;
            for(int i=0;i<g[cur].size();++i) {
                if(d[g[cur][i].first] > d[cur] + g[cur][i].second) {
                    d[g[cur][i].first] = d[cur] + g[cur][i].second;
                    if(c[g[cur][i].first] == now) q.push(make_pair(d[g[cur][i].first], g[cur][i].first));
                }
                if(c[g[cur][i].first] != now) {
                    --deg[c[g[cur][i].first]];
                    if(deg[c[g[cur][i].first]] == 0) Q.push(c[g[cur][i].first]);
                }
            }
        }
    }
    for(int i=1;i<=n;++i)
        if(d[i] <= 1e9)printf("%d\n", d[i]);
        else puts("NO PATH");
    return 0;
}
