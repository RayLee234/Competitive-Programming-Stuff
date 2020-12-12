//
//  main.cpp
//  Network_2 POJ3694
//
//  Created by Ruining Li on 2020/10/6.
//  Copyright © 2020 Ruining Li. All rights reserved.
//

#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
int n, m, q, ver[400001], Head[100001], Next[400001], tot, c[100001], dfn[100001], low[100001], t, typ, ans;
int ver_c[400001], Head_c[400001], Next_c[400001], tot_c;
int f[100001], d[100001], Case;
bool bridge[400001], v[100001], up_bridge[100001];
void add(int x, int y) {
    ver[++tot] = y, Next[tot] = Head[x], Head[x] = tot;
}
void add_c(int x, int y) {
    ver_c[++tot_c] = y, Next_c[tot_c] = Head_c[x], Head_c[x] = tot_c;
}
void tarjan(int x, int index) {
    low[x] = dfn[x] = ++t;
    for(int i=Head[x];i;i=Next[i]) {
        int y = ver[i];
        if(!dfn[y]) {
            tarjan(y, i);
            low[x] = min(low[x], low[y]);
            if(dfn[x] < low[y]) bridge[i] = bridge[i xor 1] = 1;
        }
        else if(index != (i xor 1) ) low[x] = min(low[x], dfn[y]);
    }
}
void dfs(int x, int num) {
    c[x] = num;
    for(int i=Head[x];i;i=Next[i]) {
        int y = ver[i];
        if(c[y] || bridge[i]) continue;
        dfs(y, num);
    }
}
void dfs_find_father(int x) {
    v[x] = 1;
    for(int i=Head_c[x];i;i=Next_c[i]) {
        int y = ver_c[i];
        if(v[y]) continue;
        f[y] = x;
        d[y] = d[x] + 1;
        up_bridge[y] = 1;
        dfs_find_father(y);
    }
}
int main() {
    while(scanf("%d %d", &n, &m)) {
        if(n == 0) return 0;
        printf("Case %d:\n", ++Case);
        memset(bridge, 0, sizeof(bridge));
        memset(ver, 0, sizeof(ver)), memset(ver_c, 0, sizeof(ver_c));
        memset(Head, 0, sizeof(Head)), memset(Head_c, 0, sizeof(Head_c));
        memset(Next, 0, sizeof(Next)), memset(Next_c, 0, sizeof(Next_c));
        memset(c, 0, sizeof(c));
        tot = tot_c = 1;
        ans = typ = t = 0;
        for(int i=1;i<=m;++i) {
            int x, y; scanf("%d %d", &x, &y);
            add(x, y), add(y, x);
        }
        tarjan(1, 0);
        for(int i=1;i<=n;++i)
            if(!c[i]) dfs(i, ++typ);
        for(int i=2;i<=tot;++i) {
            int x = ver[i xor 1], y = ver[i];
            if(bridge[i]) ++ans, add_c(c[x], c[y]);
        }
        memset(v, 0, sizeof(v));
        dfs_find_father(1);
        ans /= 2;
        scanf("%d", &q);
        while(q--) {
            int x, y; scanf("%d %d", &x, &y);
            int a = c[x], b = c[y];
            if(a == b) printf("%d\n", ans);
            else {
                if(d[a] < d[b]) swap(a, b);
                while(d[a] > d[b]) {
                    if(up_bridge[a]) --ans;
                    up_bridge[a] = 0;
                    a = f[a];
                }
                while(a != b) {
                    if(up_bridge[a]) --ans;
                    if(up_bridge[b]) --ans;
                    up_bridge[a] = up_bridge[b] = 0;
                    a = f[a], b = f[b];
                }
                printf("%d\n", ans);
            }
        }
    }
    return 0;
}
