//
//  main.cpp
//  Knights of the Round Table POJ2942
//
//  Created by Ruining Li on 2020/10/6.
//  Copyright © 2020 Ruining Li. All rights reserved.
//

#include <iostream>
#include <cstring>
#include <cstdio>
#include <stack>
#include <vector>
using namespace std;
int n, m, ver[2000010], head[1001], Next[2000010], low[1001], dfn[1001], tot, cnt, t, c[1001];
stack <int> S;
bool g[1001][1001], cut[1001], ok[1001], contains[1001];
vector <int> block[1001];
void add(int x, int y) {
    ver[++tot] = y, Next[tot] = head[x], head[x] = tot;
}
void tarjan(int x, int root) {
    int flag = 0;
    low[x] = dfn[x] = ++t;
    S.push(x);
    if(x == root && head[x] == 0) { block[++cnt].push_back(x); return; }
    for(int i=head[x];i;i=Next[i]) {
        int y = ver[i];
        if(!dfn[y]) {
            tarjan(y, root);
            low[x] = min(low[x], low[y]);
            if(dfn[x] <= low[y]) {
                ++flag;
                if(x != root || flag > 1) cut[x] = 1;
                cnt++;
                int z;
                do {
                    z = S.top(); S.pop();
                    block[cnt].push_back(z);
                } while(z != y);
                block[cnt].push_back(x);
            }
        }
        else low[x] = min(low[x], dfn[y]);
    }
}
bool dfs(int x, int color) {
    c[x] = color;
    for(int i=head[x];i;i=Next[i]) {
        int y = ver[i];
        if(contains[y] && !c[y] && dfs(y, 3-color)) return 1;
        else if(contains[y] && c[y] && c[y] != 3-color) return 1;
    }
    return 0;
}
int main() {
    while(scanf("%d %d", &n, &m)) {
        if(n == 0) return 0;
        for(int i=0;i<=cnt;++i) block[i].clear();
        tot = 1, cnt = 0;
        int ans = n;
        while(!S.empty()) S.pop();
        memset(g, 0, sizeof(g)), memset(cut, 0, sizeof(cut));
        memset(ver, 0, sizeof(ver)), memset(head, 0, sizeof(head)), memset(Next, 0, sizeof(head));
        memset(dfn, 0, sizeof(dfn));
        memset(ok, 0, sizeof(ok)), memset(c, 0, sizeof(c));
        for(int i=1;i<=m;++i) {
            int x, y; scanf("%d %d", &x, &y);
            g[x][y] = g[y][x] = 1;
        }
        for(int i=1;i<n;++i) for(int j=i+1;j<=n;++j) if(!g[i][j]) add(i, j), add(j, i);
        for(int i=1;i<=n;++i) if(!dfn[i]) tarjan(i, i);
        for(int i=1;i<=cnt;++i) {
            for(int j=0;j<block[i].size();++j) contains[block[i][j]] = 1;
            bool can_attend = dfs(block[i][0], 1);
            for(int j=0;j<block[i].size();++j) {
                contains[block[i][j]] = c[block[i][j]] = 0;
                if(can_attend) ok[block[i][j]] = 1;
            }
        }
        for(int i=1;i<=n;++i) if(ok[i]) --ans;
        printf("%d\n", ans);
    }
}
