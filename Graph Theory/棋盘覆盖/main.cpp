//
//  main.cpp
//  棋盘覆盖 CH6801
//
//  Created by Ruining Li on 2020/10/11.
//  Copyright © 2020 Ruining Li. All rights reserved.
//

#include <iostream>
#include <cstring>
#include <vector>
using namespace std;
int n, t, c[10010], ans, match[10010];
bool a[101][101], vis[10010];
int num(int i, int j) {
    return (i-1) * n + j;
}
vector <int> g[10010];
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
    cin >> n >> t;
    for(int i=1;i<=t;++i) {
        int x, y; cin >> x >> y;
        a[x][y] = 1;
    }
    for(int i=1;i<=n;++i)
        for(int j=1;j<=n;++j) {
            if(a[i][j]) continue;
            if(i < n && !a[i+1][j]) g[num(i, j)].push_back(num(i+1, j));
            if(i > 1 && !a[i-1][j]) g[num(i, j)].push_back(num(i-1, j));
            if(j < n && !a[i][j+1]) g[num(i, j)].push_back(num(i, j+1));
            if(j > 1 && !a[i][j-1]) g[num(i, j)].push_back(num(i, j-1));
        }
    for(int i=1;i<=n*n;++i) {
        int x = (i-1) / n + 1, y = i % n; if(!y) y = n;
        if((x + y) % 2 == 0) c[i] = 1;
        else c[i] = 2;
    }
    for(int i=1;i<=n*n;++i) {
        memset(vis, 0, sizeof(vis));
        if(c[i] == 1 && dfs(i)) ++ans;
    }
    cout << ans << endl;
    return 0;
}
