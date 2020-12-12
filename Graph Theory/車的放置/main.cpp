//
//  main.cpp
//  車的放置 CH6802
//
//  Created by Ruining Li on 2020/10/11.
//  Copyright © 2020 Ruining Li. All rights reserved.
//

#include <iostream>
#include <cstring>
#include <vector>
using namespace std;
int n, m, t, match[401], ans;
bool a[201][201], vis[401];
vector <int> g[401];
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
        for(int j=1;j<=m;++j)
            if(!a[i][j]) g[i].push_back(n+j);
    for(int i=1;i<=n;++i) {
        memset(vis, 0, sizeof(vis));
        if(dfs(i)) ++ans;
    }
    cout << ans << endl;
    return 0;
}
