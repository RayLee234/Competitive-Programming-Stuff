//
//  main.cpp
//  导弹防御塔 CH6803
//
//  Created by Ruining Li on 2020/10/11.
//  Copyright © 2020 Ruining Li. All rights reserved.
//

#include <iostream>
#include <vector>
#include <cstdio>
#include <cmath>
#include <cstring>
using namespace std;
int n, m, t2, v, s[60], t[60], match[60], vis[60], tot;
double t1, ans;
struct something {
    int x, y;
}a[60], b[60]; // a: Invader;   b: Defense Tower;
double reach_time(int i, int j) { // (the distance between the i-th invader and the j-th defense tower) / v
    return sqrt((a[i].x - b[j].x) * (a[i].x - b[j].x) + (a[i].y - b[j].y) * (a[i].y - b[j].y)) / v;
}
vector <int> g[200000];
bool dfs(int x) {
    for(int i=0;i<g[x].size();++i) {
        int y = g[x][i];
        if(vis[y - tot]) continue;
        vis[y - tot] = 1;
        if(!match[y - tot] || dfs(match[y - tot])) {
            match[y - tot] = x; return 1;
        }
    }
    return 0;
}
int main() {
    cin >> n >> m >> t1 >> t2 >> v; t1 /= 60;
    for(int i=1;i<=m;++i) cin >> a[i].x >> a[i].y;
    for(int i=1;i<=n;++i) cin >> b[i].x >> b[i].y;
    double l = 0, r = (double)m / n * t2 * 40000 / v;
    while(r - l > 1e-8) {
        memset(match, 0, sizeof(match));
        double mid = (l + r) / 2;
        for(int i=1;i<=tot;++i) g[i].clear();
        int cnt = (int)((mid - t1) / (t1 + t2)) + 1;
        tot = cnt * n;
        for(int i=1;i<=n;++i) s[i] = (i-1) * cnt + 1, t[i] = i * cnt;
        for(int i=1;i<=n;++i)
            for(int j=s[i];j<=t[i];++j) {
                double rest = mid - (t1 + (j - s[i]) * (t1 + t2));
                for(int k=1;k<=m;++k) if(reach_time(k, i) <= rest) g[j].push_back(tot + k);
            }
        cnt = 0;
        for(int i=1;i<=tot;++i) {
            memset(vis, 0, sizeof(vis));
            if(dfs(i)) ++cnt;
        }
        if(cnt >= m) ans = mid, r = mid;
        else l = mid;
    }
    printf("%.6f\n", ans);
    return 0;
}
