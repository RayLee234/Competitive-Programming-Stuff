//
//  main.cpp
//  创世纪 CH6401
//
//  Created by Ruining Li on 2020/9/24.
//  Copyright © 2020 Ruining Li. All rights reserved.
//

#include <iostream>
#include <vector>
#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;
int n, a[1000010], deg[1000010], p, ans, v[1000010], f[1000010][2], F[1000010][2];
bool isLoop[1000010];
vector <int> g[1000010];
void toposort() {
    queue <int> q;
    for(int i=1;i<=n;++i)
        if(deg[i] == 0) q.push(i);
    while(!q.empty()) {
        int x = q.front(); q.pop();
        isLoop[x] = 0;
        if(--deg[a[x]] == 0) q.push(a[x]);
    }
}
void dfs(int x) {
    int cnt = 0;
    vector <int> sons;
    v[x] = f[x][1] = 1;
    for(int i=0;i<g[x].size();++i) {
        int y = g[x][i];
        if(x == a[p] && y == p) continue;
        if(v[y]) continue;
        sons.push_back(y);
        dfs(y);
        if(f[y][0] >= f[y][1]) f[x][0] += f[y][0], f[x][1] += f[y][0], ++cnt;
        else f[x][0] += f[y][1], f[x][1] += f[y][1];
    }
    if(sons.size() == 0) f[x][1] = -1e6;
    if(!cnt && sons.size() > 0) {
        int minus = 1e6;
        for(int i=0;i<sons.size();++i) {
            int y = sons[i];
            if(f[y][1] - f[y][0] < minus) minus = f[y][1] - f[y][0];
        }
        f[x][1] -= minus;
    }
}
void dfs2(int x) {
    int cnt = 0;
    vector <int> sons;
    v[x] = 2;
    F[x][1] = 1;
    for(int i=0;i<g[x].size();++i) {
        int y = g[x][i];
        if(x == a[p] && y == p) continue;
        if(v[y] == 2) continue;
        sons.push_back(y);
        dfs2(y);
        if(F[y][0] >= F[y][1]) F[x][0] += F[y][0], F[x][1] += F[y][0], ++cnt;
        else F[x][0] += F[y][1], F[x][1] += F[y][1];
    }
    if(sons.size() == 0 && x != a[p]) F[x][1] = -1e6;
    if(!cnt && x != a[p] && sons.size() > 0) {
        int minus = 1e6;
        for(int i=0;i<sons.size();++i) {
            int y = sons[i];
            if(F[y][1] - F[y][0] < minus) minus = F[y][1] - F[y][0];
        }
        F[x][1] -= minus;
    }
}
int main() {
    scanf("%d", &n);
    for(int i=1;i<=n;++i) scanf("%d", &a[i]), ++deg[a[i]], g[a[i]].push_back(i);
    memset(isLoop, 1, sizeof(isLoop));
    toposort();
    for(int i=1;i<=n;++i) {
        if(!v[i] && isLoop[i]) {
            p = i;
            dfs(p);
            int sum = max(f[p][0], f[p][1]);
            dfs2(p);
            ans += max(sum, F[p][0]);
        }
    }
    cout << ans << endl;
    return 0;
}
