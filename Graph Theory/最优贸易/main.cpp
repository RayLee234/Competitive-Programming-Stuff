//
//  main.cpp
//  最优贸易 LUOGU1073
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
int n, m, a[100010], f[100010], d[100010], ans;
vector <int> g1[100010], g2[100010];
int main() {
    scanf("%d %d", &n, &m);
    for(int i=1;i<=n;++i) scanf("%d", &a[i]);
    for(int i=1;i<=m;++i) {
        int x, y, z; scanf("%d %d %d", &x, &y, &z);
        if(z == 1) g1[x].push_back(y), g2[y].push_back(x);
        else g1[x].push_back(y), g1[y].push_back(x), g2[x].push_back(y), g2[y].push_back(x);
    }
    memset(f, 15, sizeof(f)), memset(d, -1, sizeof(d));
    queue <int> q;
    q.push(1); f[1] = a[1];
    while(!q.empty()) {
        int now = q.front(); q.pop();
        for(int i=0;i<g1[now].size();++i)
            if(f[g1[now][i]] > min(f[now], a[g1[now][i]])) {
                f[g1[now][i]] = min(f[now], a[g1[now][i]]);
                q.push(g1[now][i]);
            }
    }
    q.push(n); d[n] = a[n];
    while(!q.empty()) {
        int now = q.front(); q.pop();
        for(int i=0;i<g2[now].size();++i)
            if(d[g2[now][i]] < max(d[now], a[g2[now][i]])) {
                d[g2[now][i]] = max(d[now], a[g2[now][i]]);
                q.push(g2[now][i]);
            }
    }
    for(int i=1;i<=n;++i)
        if(f[i] <= 100 && d[i] > -1) ans = max(ans, d[i] - f[i]);
    printf("%d\n", ans);
    return 0;
}
