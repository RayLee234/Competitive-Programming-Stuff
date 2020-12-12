//
//  main.cpp
//  Vani和Cl2捉迷藏 CH6902
//
//  Created by Ruining Li on 2020/10/14.
//  Copyright © 2020 Ruining Li. All rights reserved.
//

#include <iostream>
#include <cstring>
using namespace std;
int n, m, g[201][201], ans, match[201], hide[201];
bool vis[201], e[201];
bool dfs(int x) {
    for(int y=1;y<=n;++y)
        if(g[x][y] && !vis[y]) {
            vis[y] = 1;
            if(!match[y] || dfs(match[y])) {
                match[y] = x; return 1;
            }
        }
    return 0;
}
int main() {
    cin >> n >> m;
    for(int i=1;i<=m;++i) {
        int x, y; cin >> x >> y;
        g[x][y] = 1;
    }
    for(int i=1;i<=n;++i) g[i][i] = 1;
    for(int k=1;k<=n;++k)
        for(int i=1;i<=n;++i)
            for(int j=1;j<=n;++j)
                if(g[i][k] == 1 && g[k][j] == 1) g[i][j] = 1;
    for(int i=1;i<=n;++i) g[i][i] = 0;
    for(int i=1;i<=n;++i) {
        memset(vis, 0, sizeof(vis));
        if(!dfs(i)) ++ans;
    }
    cout << ans << endl;
    memset(e, 1, sizeof(e));
    for(int i=1;i<=n;++i) e[match[i]] = 0;
    int k = 0;
    for(int i=1;i<=n;++i)
        if(e[i]) hide[++k] = i;
    bool modify = 1;
    while(modify) {
        modify = 0;
        memset(vis, 0, sizeof(vis));
        for(int i=1;i<=k;++i)
            for(int j=1;j<=n;++j)
                if(g[hide[i]][j]) vis[j] = 1;
        for(int i=1;i<=k;++i)
            if(vis[hide[i]]) {
                modify = true;
                while(vis[hide[i]]) hide[i] = match[hide[i]];
            }
    }
    for(int i=1;i<=k;++i) cout << hide[i] << ' ';
    cout << endl;
    return 0;
}
