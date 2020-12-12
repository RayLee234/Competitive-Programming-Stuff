//
//  main.cpp
//  Ants POJ3565
//
//  Created by Ruining Li on 2020/10/11.
//  Copyright © 2020 Ruining Li. All rights reserved.
//

#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
using namespace std;
int n, match[101], ans[101];
double w[101][101], la[101], lb[101], upd[101];
bool va[101], vb[101];
struct point {
    int x, y;
}a[101], b[101];
bool dfs(int x) {
    va[x] = 1;
    for(int y=1;y<=n;++y) {
        if(vb[y]) continue;
        if(fabs(la[x] + lb[y] - w[x][y]) < 1e-8) {
            vb[y] = 1;
            if(!match[y] || dfs(match[y])) {
                match[y] = x; return 1;
            }
        }
        else upd[y] = min(upd[y], la[x] + lb[y] - w[x][y]);
    }
    return 0;
}
int main() {
    scanf("%d", &n);
    for(int i=1;i<=n;++i) scanf("%d %d", &a[i].x, &a[i].y);
    for(int i=1;i<=n;++i) scanf("%d %d", &b[i].x, &b[i].y);
    for(int i=1;i<=n;++i)
        for(int j=1;j<=n;++j) w[i][j] = -sqrt((a[i].x-b[j].x) * (a[i].x-b[j].x) * 1.0 + (a[i].y-b[j].y) * (a[i].y-b[j].y) * 1.0);
    for(int i=1;i<=n;++i) {
        la[i] = -1e10;
        for(int j=1;j<=n;++j) la[i] = max(la[i], w[i][j]);
    }
    for(int i=1;i<=n;++i) {
        while(true) {
            memset(va, 0, sizeof(va)), memset(vb, 0, sizeof(vb));
            for(int j=1;j<=n;++j) upd[j] = 1e10;
            if(dfs(i)) break;
            double delta = 1e10;
            for(int j=1;j<=n;++j)
                if(!vb[j]) delta = min(delta, upd[j]);
            for(int j=1;j<=n;++j) {
                if(va[j]) la[j] -= delta;
                if(vb[j]) lb[j] += delta;
            }
        }
    }
    for(int i=1;i<=n;++i) ans[match[i]] = i;
    for(int i=1;i<=n;++i) printf("%d\n", ans[i]);
    return 0;
}
