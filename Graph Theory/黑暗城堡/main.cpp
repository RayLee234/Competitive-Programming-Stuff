//
//  main.cpp
//  黑暗城堡 CH6202
//
//  Created by Ruining Li on 2020/8/11.
//  Copyright © 2020 Ruining Li. All rights reserved.
//

#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;
int n, m, dist[1010], g[1010][1010], s[1010], ans = 1;
const int mod = 2147483647;
bool cmp(int x, int y) {
    return dist[x] < dist[y];
}
bool vis[1010];
int main() {
    cin >> n >> m;
    memset(g, 61, sizeof(g)), memset(dist, 61, sizeof(dist));
    for(int i=1;i<=n;++i) g[i][i] = 0;
    for(int i=1;i<=m;++i) {
        int x, y, z; cin >> x >> y >> z;
        g[x][y] = g[y][x] = min(g[x][y], z);
    }
    dist[1] = 0;
    for(int i=1;i<=n;++i) {
        int x = 0;
        for(int j=1;j<=n;++j)
            if(!vis[j] && (x == 0 || dist[j] < dist[x])) x = j;
        for(int j=1;j<=n;++j)
            if(dist[j] > dist[x] + g[x][j]) dist[j] = dist[x] + g[x][j];
        vis[x] = 1;
    }
    memset(vis, 0, sizeof(vis));
    vis[1] = 1;
    for(int i=1;i<=n;++i) s[i] = i;
    sort(s+1, s+n+1, cmp);    for(int i=2;i<=n;++i) {
        int x = s[i], cnt = 0;
        for(int j=1;j<=n;++j)
            if(vis[j] && dist[x] == dist[j] + g[x][j]) ++cnt;
        ans = (long long)ans * cnt % mod;
        vis[x] = 1;
    }
    cout << ans << endl;
    return 0;
}
