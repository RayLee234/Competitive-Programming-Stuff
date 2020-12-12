//
//  main.cpp
//  Picnic Planning POJ1639
//
//  Created by Ruining Li on 2020/8/11.
//  Copyright © 2020 Ruining Li. All rights reserved.
//

#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <cstring>
#include <queue>
using namespace std;
int n = 1, m, g[31][31], s, t, c[31], f[31], ans, minToPark[31], maxToPark[31];
bool v[31], chosen[1000];
map <string, int> p;
struct edge { int x, y, z; } e[1000];
queue <int> q;
bool cmp(edge x, edge y) {
    return x.z < y.z;
}
void dfs(int x, int block) {
    v[x] = 1, c[x] = block;
    for(int i=2;i<=n;++i)
        if(g[x][i] > 0 && !v[i]) dfs(i, block);
}
int find(int x) {
    if(f[x] == x) return x;
    return f[x] = find(f[x]);
}
int main() {
    cin >> m;
    p.insert(pair<string,int>("Park", 1));
    for(int i=1;i<=m;++i) {
        string x, y; int z;
        cin >> x >> y >> z;
        if(p[x] == 0) p[x] = ++n;
        if(p[y] == 0) p[y] = ++n;
        e[i].x = p[x], e[i].y = p[y], e[i].z = z;
        g[p[x]][p[y]] = g[p[y]][p[x]] = z;
    }
    sort(e+1, e+m+1, cmp);
    cin >> s;
    for(int i=2;i<=n;++i)
        if(!v[i]) dfs(i, ++t);
    for(int i=1;i<=n;++i) f[i] = i;
    for(int i=1;i<=t;++i)
        for(int j=1;j<=m;++j)
            if(c[e[j].x] == i && c[e[j].y] == i) {
                int fx = find(e[j].x), fy = find(e[j].y);
                if(fx == fy) continue;
                f[fx] = fy;
                chosen[j] = 1, ans += e[j].z;
            }
    for(int i=1;i<=m;++i)
        if(e[i].x == 1 && (minToPark[c[e[i].y]] == 0 || e[i].z < e[minToPark[c[e[i].y]]].z)) minToPark[c[e[i].y]] = i;
        else if(e[i].y == 1 && (minToPark[c[e[i].x]] == 0 || e[i].z < e[minToPark[c[e[i].x]]].z)) minToPark[c[e[i].x]] = i;
    for(int i=1;i<=t;++i) ans += e[minToPark[i]].z, chosen[minToPark[i]] = 1;
    for(int i=1;i<=s-t;++i) {
        pair<int,int> gg[31][31];
        for(int j=1;j<=m;++j)
            if(chosen[j]) gg[e[j].x][e[j].y] = gg[e[j].y][e[j].x] = make_pair(e[j].z, j);
        memset(maxToPark, 0, sizeof(maxToPark)), memset(v, 0, sizeof(v));
        q.push(1); v[1] = 1;
        while(!q.empty()) {
            int cur = q.front(); q.pop();
            for(int j=2;j<=n;++j)
                if(gg[cur][j].second > 0 && !v[j]) {
                    q.push(j); v[j] = 1;
                    if(e[maxToPark[cur]].z < gg[cur][j].first) maxToPark[j] = gg[cur][j].second;
                    else maxToPark[j] = maxToPark[cur];
                }
        }
        int r = 0, ed;
        for(int j=1;j<=m;++j)
            if(!chosen[j] && (e[j].x == 1 || e[j].y == 1)) {
                if(e[j].x == 1 && e[maxToPark[e[j].y]].z - e[j].z > r) r = e[maxToPark[e[j].y]].z - e[j].z, ed = j;
                if(e[j].y == 1 && e[maxToPark[e[j].x]].z - e[j].z > r) r = e[maxToPark[e[j].x]].z - e[j].z, ed = j;
            }
        if(r == 0) break;
        ans -= r, chosen[ed] = 1;
        if(e[ed].x == 1) chosen[maxToPark[e[ed].y]] = 0;
        else chosen[maxToPark[e[ed].x]] = 0;
    }
    cout << "Total miles driven: " << ans << endl;
    return 0;
}
