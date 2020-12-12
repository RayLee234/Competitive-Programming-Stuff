//
//  main.cpp
//  Muddy Fields POJ2226
//
//  Created by Ruining Li on 2020/10/13.
//  Copyright © 2020 Ruining Li. All rights reserved.
//

#include <iostream>
#include <vector>
#include <cstring>
using namespace std;
int n, m, a[51][51];
int hr[2000], hs[2000], ht[2000], h_cnt, vc[2000], vs[2000], vt[2000], v_cnt, ans, match[2000];
bool vis[2000];
vector <int> g[2000];
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
    cin >> n >> m;
    for(int i=1;i<=n;++i)
        for(int j=1;j<=m;++j) {
            char ch; cin >> ch;
            if(ch == '*') a[i][j] = 1;
        }
    for(int i=1;i<=n;++i) {
        int start = 0;
        for(int j=1;j<=m;++j) {
            if(a[i][j] && !start) start = j;
            if(!a[i][j] && start) hr[++h_cnt] = i, hs[h_cnt] = start, ht[h_cnt] = j-1, start = 0;
        }
        if(start) hr[++h_cnt] = i, hs[h_cnt] = start, ht[h_cnt] = m;
    }
    for(int j=1;j<=m;++j) {
        int start = 0;
        for(int i=1;i<=n;++i) {
            if(a[i][j] && !start) start = i;
            if(!a[i][j] && start) vc[++v_cnt] = j, vs[v_cnt] = start, vt[v_cnt] = i-1, start = 0;
        }
        if(start) vc[++v_cnt] = j, vs[v_cnt] = start, vt[v_cnt] = n;
    }
    for(int i=1;i<=n;++i)
        for(int j=1;j<=m;++j) {
            if(!a[i][j]) continue;
            int idx1, idx2;
            for(int k=1;k<=h_cnt;++k) if(hr[k] == i && hs[k] <= j && ht[k] >= j) { idx1 = k; break; }
            for(int k=1;k<=v_cnt;++k) if(vc[k] == j && vs[k] <= i && vt[k] >= i) { idx2 = k; break; }
            g[idx1].push_back(idx2);
        }
    for(int i=1;i<=h_cnt;++i) {
        memset(vis, 0, sizeof(vis));
        if(dfs(i)) ++ans;
    }
    cout << ans << endl;
    return 0;
}
