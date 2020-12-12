//
//  main.cpp
//  Computer HDOJ2196
//
//  Created by Ruining Li on 2020/6/23.
//  Copyright © 2020 Ruining Li. All rights reserved.
//

#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;
int n, fa[10001], toFa[10001], f[10001], g[10001], s[10001], t[10001];
vector < pair<int,int> > son[10001];
void dfs(int x) {
    if(son[x].size() == 0) return;
    for(int i=0;i<son[x].size();++i) {
        int y = son[x][i].first, d = son[x][i].second;
        dfs(y);
        if(f[y] + d >= f[x]) g[x] = f[x], t[x] = s[x], f[x] = f[y] + d, s[x] = y;
        else if(f[y] + d > g[x]) g[x] = f[y] + d, t[x] = y;
    }
}
void dfs2(int x) {
    for(int i=0;i<son[x].size();++i) {
        int y = son[x][i].first, d = son[x][i].second;
        if(s[x] != y) {
            if(f[y] <= f[x] + d) f[y] = f[x] + d, s[y] = 0;
            else if(g[y] <= f[x] + d) g[y] = f[x] + d, t[y] = 0;
        }
        else {
            if(f[y] <= g[x] + d) f[y] = g[x] + d, s[y] = 0;
            else if(g[y] <= g[x] + d) g[y] = g[x] + d, t[y] = 0;
        }
        dfs2(y);
    }
}
int main() {
    while(scanf("%d", &n) != EOF) {
        memset(f, 0, sizeof(f));
        memset(g, 0, sizeof(g));
        memset(s, 0, sizeof(s));
        memset(t, 0, sizeof(t));
        for(int i=1;i<=n;++i) son[i].clear();
        for(int i=2;i<=n;++i) {
            scanf("%d %d", &fa[i], &toFa[i]);
            son[fa[i]].push_back(make_pair(i, toFa[i]));
        }
        dfs(1);
        dfs2(1);
        for(int i=1;i<=n;++i) printf("%d\n", f[i]);
    }
    return 0;
}
