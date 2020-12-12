//
//  main.cpp
//  Desert King POJ2728
//
//  Created by Ruining Li on 2020/8/11.
//  Copyright © 2020 Ruining Li. All rights reserved.
//

#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
using namespace std;
int n;
double a[1001][1001], b[1001][1001], c[1001][1001], d[1001];
bool v[1001];
struct point { int x, y, z; } p[1001];
double getDist(int i, int j) {
    return sqrt((p[i].x-p[j].x) * (p[i].x-p[j].x) + (p[i].y-p[j].y) * (p[i].y - p[j].y));
}
int main() {
    while(scanf("%d", &n)) {
        double L = 0, R = 0;
        if(!n) return 0;
        for(int i=1;i<=n;++i) scanf("%d %d %d", &p[i].x, &p[i].y, &p[i].z);
        for(int i=1;i<=n;++i)
            for(int j=i;j<=n;++j) R += (a[i][j] = a[j][i] = abs((double)p[i].z - p[j].z)), b[i][j] = b[j][i] = getDist(i, j);
        while(L + 1e-6 <= R) {
            double mid = (L + R) / 2, tot = 0;
            for(int i=1;i<=n;++i)
                for(int j=i+1;j<=n;++j) c[i][j] = c[j][i] = a[i][j] - mid * b[i][j];
            memset(v, 0, sizeof(v));
            for(int i=1;i<=n;++i) d[i] = 0x3f3f3f3f;
            d[1] = 0;
            while(1) {
                int x = 0;
                for(register int i=1;i<=n;++i)
                    if(!v[i] && (x == 0 || d[x] > d[i])) x = i;
                if(!x) break;
                v[x] = 1, tot += d[x];
                for(register int i=1;i<=n;++i)
                    if(!v[i]) d[i] = min(d[i], c[x][i]);
            }
            if(tot < 0) R = mid;
            else L = mid;
        }
        printf("%.3f\n", L);
    }
}
