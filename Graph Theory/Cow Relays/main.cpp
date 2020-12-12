//
//  main.cpp
//  Cow Relays POJ3613
//
//  Created by Ruining Li on 2020/8/10.
//  Copyright © 2020 Ruining Li. All rights reserved.
//

#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int n, t, s, e, u[201], a[201], c[101], d[201][201], num, ans[201][201];
void mulself(int v[201][201]) {
    int w[201][201];
    memset(w, 30, sizeof(w));
    for(int i=1;i<=num;++i)
        for(int j=1;j<=num;++j)
            for(int k=1;k<=num;++k) w[i][j] = min(w[i][j], v[i][k] + v[k][j]);
    memcpy(v, w, sizeof(w));
}
void mul(int v[201][201], int w[201][201]) {
    int x[201][201];
    memset(x, 30, sizeof(x));
    for(int i=1;i<=num;++i)
        for(int j=1;j<=num;++j)
            for(int k=1;k<=num;++k) x[i][j] = min(x[i][j], v[i][k] + w[k][j]);
    memcpy(v, x, sizeof(x));
}
int main() {
    scanf("%d %d %d %d", &n, &t, &s, &e);
    for(int i=1;i<=t;++i) scanf("%d %d %d", &c[i], &u[2*i-1], &u[2*i]);
    memcpy(a, u, sizeof(u));
    sort(a+1, a+2*t+1);
    num = unique(a+1, a+2*t+1) - a - 1;
    for(int i=1;i<=2*t;++i) u[i] = lower_bound(a+1, a+num+1, u[i]) - a;
    s = lower_bound(a+1, a+num+1, s) - a, e = lower_bound(a+1, a+num+1, e) - a;
    memset(d, 30, sizeof(d));
    for(int i=1;i<=t;++i) d[u[2*i-1]][u[2*i]] = d[u[2*i]][u[2*i-1]] = c[i];
    memset(ans, 30, sizeof(ans));
    for(int i=1;i<=num;++i) ans[i][i] = 0;
    while(n > 0) {
        if(n & 1) mul(ans, d);
        n >>= 1;
        mulself(d);
    }
    printf("%d\n", ans[s][e]);
    return 0;
}
