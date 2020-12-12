//
//  main.cpp
//  Katu Puzzle POJ3678
//
//  Created by Ruining Li on 2020/10/10.
//  Copyright © 2020 Ruining Li. All rights reserved.
//

#include <iostream>
#include <vector>
#include <string>
#include <cstdio>
#include <stack>
using namespace std;
int n, m, low[2010], dfn[2010], c[2010], t, cnt;
bool vis[2010];
stack <int> S;
vector <int> g[2010];
void tarjan(int x) {
    low[x] = dfn[x] = ++t;
    S.push(x);
    vis[x] = 1;
    for(int i=0;i<g[x].size();++i) {
        int y = g[x][i];
        if(!dfn[y]) {
            tarjan(y);
            low[x] = min(low[x], low[y]);
        }
        else if(vis[y]) low[x] = min(low[x], dfn[y]);
    }
    if(low[x] == dfn[x]) {
        ++cnt;
        while(S.top()!= x) {
            int z = S.top(); S.pop();
            c[z] = cnt, vis[z] = 0;
        }
        S.pop(), c[x] = cnt, vis[x] = 0;
    }
}
int main() {
    scanf("%d %d", &n, &m);
    for(int i=1;i<=m;++i) {
        int a, b, c; string op;
        scanf("%d %d %d", &a, &b, &c); cin >> op;
        if(c == 0 && op[0] == 'A') g[a+n].push_back(b), g[b+n].push_back(a);
        if(c == 1 && op[0] == 'A') g[a+n].push_back(b+n), g[b+n].push_back(a+n), g[a].push_back(a+n), g[b].push_back(b+n);
        if(c == 0 && op[0] == 'O') g[a].push_back(b), g[b].push_back(a), g[a+n].push_back(a), g[b+n].push_back(b);
        if(c == 1 && op[0] == 'O') g[a].push_back(b+n), g[b].push_back(a+n);
        if(c == 0 && op[0] == 'X') g[a].push_back(b), g[b].push_back(a), g[a+n].push_back(b+n), g[b+n].push_back(a+n);
        if(c == 1 && op[0] == 'X') g[a].push_back(b+n), g[b].push_back(a+n), g[a+n].push_back(b), g[b+n].push_back(a);
    }
    for(int i=0;i<2*n;++i) if(!dfn[i]) tarjan(i);
    for(int i=0;i<n;++i)
        if(c[i] == c[i+n]) { cout << "NO\n" ; return 0; }
    cout << "YES\n";
    return 0;
}
