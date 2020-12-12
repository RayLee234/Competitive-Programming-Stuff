//
//  main.cpp
//  Jury Compromise POJ1015
//
//  Created by Ruining Li on 2020/5/15.
//  Copyright © 2020 Ruining Li. All rights reserved.
//

#pragma GCC optimize(2)
#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;
int n, m, d[201], p[201];
int f[201][21][801], preJ[201][21][801], preK[201][21][801], minV, ansD, ansP, T, chosen[21];
int abs(int x) {
    return x > 0 ? x : -x;
}
int main() {
    while(scanf("%d %d", &n, &m)) {
        if(n == 0) return 0;
        for(register int i=1;i<=n;++i) scanf("%d %d", &p[i], &d[i]);
        memset(f, -1, sizeof(f));
        memset(preJ, -1, sizeof(preJ));
        memset(preK, -1, sizeof(preK));
        f[0][0][400] = 0;
        minV = 460;
        for(register int i=1;i<=n;++i) {
            f[i][0][400] = 0;
            for(register int j=1;j<=m && j<=i;++j)
                for(register int k=0;k<=800;++k) {
                    if(f[i-1][j][k] == -1 && (k+p[i]-d[i] < 0 || k+p[i]-d[i] > 800 || f[i-1][j-1][k+p[i]-d[i]] == -1) ) continue;
                    if(f[i-1][j][k] == -1) {
                        f[i][j][k] = f[i-1][j-1][k+p[i]-d[i]]+d[i]+p[i];
                        preJ[i][j][k] = j-1, preK[i][j][k] = k+p[i]-d[i];
                    }
                    else if(k+p[i]-d[i] < 0 || k+p[i]-d[i] > 800 || f[i-1][j-1][k+p[i]-d[i]] == -1) {
                        f[i][j][k] = f[i-1][j][k];
                        preJ[i][j][k] = j, preK[i][j][k] = k;
                    }
                    else {
                        if(f[i-1][j][k] < f[i-1][j-1][k+p[i]-d[i]]+d[i]+p[i]) {
                            f[i][j][k] = f[i-1][j-1][k+p[i]-d[i]]+d[i]+p[i];
                            preJ[i][j][k] = j-1, preK[i][j][k] = k+p[i]-d[i];
                        }
                        else {
                            f[i][j][k] = f[i-1][j][k];
                            preJ[i][j][k] = j, preK[i][j][k] = k;
                        }
                    }
                }
        }
        int curI = n, curJ = m, curK;
        for(register int k=0;k<=800;++k)
            if(f[n][m][k] != -1 && (abs(k - 400) < minV || (abs(k - 400) == minV && ansD + ansP < f[n][m][k]) ) ) {
                curK = k;
                minV = abs(k - 400);
                ansD = (f[n][m][k] + k - 400) / 2;
                ansP = (f[n][m][k] + 400 - k) / 2;
            }
        printf("Jury #%d\n", ++T);
        printf("Best jury has value %d for prosecution and value %d for defence:\n", ansP, ansD);
        int num = 0;
        while(curI > 0) {
            if(preJ[curI][curJ][curK] != -1 && preJ[curI][curJ][curK] == curJ - 1) chosen[++num] = curI;
            int I = curI, J = curJ, K = curK;
            --curI, curJ = preJ[I][J][K], curK = preK[I][J][K];
        }
        for(register int i=m;i>0;--i) printf(" %d", chosen[i]);
        putchar('\n');
    }
    return 0;
}
