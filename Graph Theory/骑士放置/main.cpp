//
//  main.cpp
//  骑士放置 CH6901
//
//  Created by Ruining Li on 2020/10/13.
//  Copyright © 2020 Ruining Li. All rights reserved.
//

#include <iostream>
#include <vector>
#include <cstring>
using namespace std;
int n, m, t, u[8] = {1, 1, -1, -1, 2, 2, -2, -2}, v[8] = {2, -2, 2, -2, 1, -1, 1, -1}, ans, match[10010];
bool a[101][101], vis[10010];
int num(int r, int c) {
    return (r - 1) * m + c;
}
vector <int> g[10010];
bool valid(int r, int c) {
    return r > 0 && r <= n && c > 0 && c <= m && !a[r][c];
}
bool dfs(int x) {
    for(int i=0;i<g[x].size();++i) {
        int y = g[x][i];
        if(vis[y]) continue;
        vis[y] = 1;
        if(!match[y] || dfs(match[y])) {
            match[y] = x; return 1;
        }
    }
    return 0;
}
int main() {
    cin >> n >> m >> t;
    for(int i=1;i<=t;++i) {
        int x, y; cin >> x >> y;
        a[x][y] = 1;
    }
    for(int i=1;i<=n;++i)
        for(int j=1;j<=m;++j) {
            if(a[i][j]) continue;
            for(int k=0;k<8;++k) {
                int x = i + u[k], y = j + v[k];
                if(valid(x,y) && (i + j) % 2 == 0) g[num(i,j)].push_back(num(x,y));
            }
        }
    for(int i=1;i<=n;++i)
        for(int j=1;j<=m;++j)
            if(!a[i][j] && (i + j) % 2 == 0) {
                memset(vis, 0, sizeof(vis));
                if(dfs(num(i,j))) ans++;
            }
    cout << n * m - t - ans << endl;
    return 0;
}
