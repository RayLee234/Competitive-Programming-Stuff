//
//  main.cpp
//  Priest John's Busiest Day POJ3683
//
//  Created by Ruining Li on 2020/10/10.
//  Copyright © 2020 Ruining Li. All rights reserved.
//

#include <iostream>
#include <cstdio>
#include <vector>
#include <string>
#include <cstring>
#include <stack>
#include <algorithm>
using namespace std;
int n, s[1001], e[1001], t[1001], low[2010], dfn[2010], c[2010], cnt, TIME, val[2010], ans[1001][4];
bool vis[2010];
bool valid(int x, int y, int X, int Y) {
    return x >= Y || X >= y;
}
vector <int> g[2010];
stack <int> stk;
void tarjan(int x) {
    low[x] = dfn[x] = ++TIME;
    vis[x] = 1;
    stk.push(x);
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
        while(stk.top() != x) {
            int z = stk.top(); stk.pop();
            c[z] = cnt, vis[z] = 0;
        }
        stk.pop(); c[x] = cnt, vis[x] = 0;
    }
}
int main() {
    cin >> n;
    for(int i=1;i<=n;++i) {
        int a, b, c, d; scanf("%d:%d %d:%d %d", &a, &b, &c, &d, &t[i]);
        s[i] = a * 60 + b, e[i] = c * 60 + d;
    }
    for(int i=1;i<n;++i)
        for(int j=i+1;j<=n;++j) {
            if(!valid(s[i], s[i] + t[i], s[j], s[j] + t[j])) g[i].push_back(j+n), g[j].push_back(i+n);
            if(!valid(s[i], s[i] + t[i], e[j] - t[j], e[j])) g[i].push_back(j), g[j+n].push_back(i+n);
            if(!valid(e[i] - t[i], e[i], s[j], s[j] + t[j])) g[i+n].push_back(j+n), g[j].push_back(i);
            if(!valid(e[i] - t[i], e[i], e[j] - t[j], e[j])) g[i+n].push_back(j), g[j+n].push_back(i);
        }
    for(int i=1;i<=2*n;++i) if(!dfn[i]) tarjan(i);
    memset(val, -1, sizeof(val));
    for(int i=1;i<=n;++i) {
        if(c[i] == c[i+n]) { puts("NO"); return 0; }
        if(val[c[i]] != -1) continue;
        val[c[i]] = (c[i] > c[i+n]);
    }
    for(int i=1;i<=n;++i)
        if(val[c[i]] == 0) ans[i][0] = s[i] / 60, ans[i][1] = s[i] % 60, ans[i][2] = (s[i] + t[i]) / 60, ans[i][3] = (s[i] + t[i]) % 60;
        else ans[i][0] = (e[i] - t[i]) / 60, ans[i][1] = (e[i] - t[i]) % 60, ans[i][2] = e[i] / 60, ans[i][3] = e[i] % 60;
    puts("YES");
    for(int i=1;i<=n;++i) {
        if(ans[i][0] < 10) cout << 0; cout << ans[i][0] << ":";
        if(ans[i][1] < 10) cout << 0; cout << ans[i][1] << " ";
        if(ans[i][2] < 10) cout << 0; cout << ans[i][2] << ":";
        if(ans[i][3] < 10) cout << 0; cout << ans[i][3] << "\n";
    }
    return 0;
}
