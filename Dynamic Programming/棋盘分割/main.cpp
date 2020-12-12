//
//  main.cpp
//  棋盘分割 POJ1191
//
//  Created by Ruining Li on 2020/6/22.
//  Copyright © 2020 Ruining Li. All rights reserved.
//

#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;
int n, a[9][9], s[9][9], sum;
double avg, f[9][9][9][9][15];
int main() {
    cin >> n;
    for(int i=1;i<=8;++i)
        for(int j=1;j<=8;++j) cin >> a[i][j], s[i][j] = s[i-1][j] + s[i][j-1] - s[i-1][j-1] + a[i][j];
    avg = (double)s[8][8] / n;
    for(int i=1;i<=8;++i) for(int j=1;j<=8;++j) for(int k=1;k<=8;++k) for(int x=1;x<=8;++x) for(int v=1;v<=n;++v) f[i][j][k][x][v] = 100000000;
    for(int i=1;i<=8;++i)
        for(int j=1;j<=8;++j) f[i][i][j][j][1] = (a[i][j] - avg) * (a[i][j] - avg);
    for(int i=1;i<=8;++i)
        for(int j=1;j<=8;++j) {
            if(i == 1 && j == 1) continue;
            for(int u=1;u<=8-i+1;++u) {
                int d = u + i - 1;
                for(int l=1;l<=8-j+1;++l) {
                    int r = l + j - 1;
                    f[u][d][l][r][1] = (s[d][r] - s[u-1][r] - s[d][l-1] + s[u-1][l-1] - avg) * (s[d][r] - s[u-1][r] - s[d][l-1] + s[u-1][l-1] - avg);
                    for(int x=2;x<=n;++x) {
                        for(int k=u;k<d;++k) {
                            f[u][d][l][r][x] = min(f[u][d][l][r][x], f[u][k][l][r][1] + f[k+1][d][l][r][x-1]);
                            f[u][d][l][r][x] = min(f[u][d][l][r][x], f[u][k][l][r][x-1] + f[k+1][d][l][r][1]);
                        }
                        for(int k=l;k<r;++k) {
                            f[u][d][l][r][x] = min(f[u][d][l][r][x], f[u][d][l][k][1] + f[u][d][k+1][r][x-1]);
                            f[u][d][l][r][x] = min(f[u][d][l][r][x], f[u][d][l][k][x-1] + f[u][d][k+1][r][1]);
                        }
                    }
                }
            }
        }
    printf("%.3f\n", sqrt(f[1][8][1][8][n] / n) );
    return 0;
}
