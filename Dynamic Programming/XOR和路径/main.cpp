//
//  main.cpp
//  XOR和路径 LUOGU3211
//
//  Created by Ruining Li on 2020/6/23.
//  Copyright © 2020 Ruining Li. All rights reserved.
//

#include <iostream>
#include <cstdio>
#include <vector>
#include <cmath>
#include <cstring>
using namespace std;
int n, m, c[101];
long double ans, a[101][101], s[101];
vector < pair<int,int> > g[101];
int main() {
    // NOTE multiple edges and self loops!
    scanf("%d %d", &n, &m);
    for(int i=1;i<=m;++i) {
        int x, y, v; scanf("%d %d %d", &x, &y, &v);
        if(x == y) ++c[x], g[x].push_back(make_pair(x, v));
        else ++c[x], ++c[y], g[x].push_back(make_pair(y, v)), g[y].push_back(make_pair(x, v));
    }
    for(int x=0;x<30;++x) {
        // calculate the Gauss matrix
        memset(a, 0, sizeof(a));
        for(int i=1;i<n;++i) {
            for(int j=0;j<g[i].size();++j) {
                int y = g[i][j].first, d = (g[i][j].second >> x) & 1;
                if(y == n) a[i][n] += d;
                else if(d == 1) --a[i][y], ++a[i][n];
                else ++a[i][y];
            }
            a[i][i] -= c[i];
            a[i][n] *= -1;
        }
        // do the Gauss elimination
        for(int i=1;i<=n-1;++i) {
            for(int j=i;j<=n-1;++j)
                if(fabs(a[j][i]) > 1e-9) {
                    for(int k=1;k<=n;++k) swap(a[j][k], a[i][k]);
                    break;
                }
            for(int j=1;j<=n-1;++j) {
                if(i == j) continue;
                long double rate = a[j][i] / a[i][i];
                for(int k=1;k<=n;++k) a[j][k] -= a[i][k] * rate;
            }
        }
        ans += ((1 << x) * a[1][n] / a[1][1]);
    }
    printf("%.3Lf\n", ans);
    return 0;
}
