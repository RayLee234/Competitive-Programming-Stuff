//
//  main.cpp
//  Machine Schedule POJ1325
//
//  Created by Ruining Li on 2020/10/13.
//  Copyright © 2020 Ruining Li. All rights reserved.
//

#include <iostream>
#include <vector>
#include <cstring>
using namespace std;
int n, m, k, match[100];
bool vis[100];
vector <int> g[100];
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
    while(cin >> n) {
        if(!n) return 0;
        cin >> m >> k;
        memset(match, 0, sizeof(match));
        for(int i=0;i<100;++i) g[i].clear();
        for(int i=1;i<=k;++i) {
            int trash, a, b; cin >> trash >> a >> b;
            if(a == 0 || b == 0) continue;
            g[a].push_back(b);
        }
        int ans = 0;
        for(int i=1;i<=n;++i) {
            memset(vis, 0, sizeof(vis));
            if(dfs(i)) ++ans;
        }
        cout << ans << endl;
    }
    return 0;
}
