//
//  main.cpp
//  Largest Submatrix HDOJ2870
//
//  Created by Ruining Li on 2020/7/27.
//  Copyright © 2020 Ruining Li. All rights reserved.
//

#pragma GCC optimize(3)
#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;
int n, m, ans, f[1001][1001], s[1001][1001];
char g[1001][1001];
int main() {
    while(scanf("%d %d", &n, &m)!=EOF) {
        ans = 0;
        for(register int i=1;i<=n;++i)
            for(register int j=1;j<=m;++j) cin >> g[i][j];
        // All changed into 'a'
        for(register int i=1;i<=n;++i)
            for(register int j=1;j<=m;++j) {
                s[i][j] = s[i-1][j] + s[i][j-1] - s[i-1][j-1];
                if(g[i][j] == 'a' || g[i][j] == 'w' || g[i][j] == 'y' || g[i][j] == 'z') ++s[i][j];
            }
        for(register int c=1;c<=m;++c)
            for(register int i=1;i<=n;++i)
                for(register int j=i;j<=n;++j) {
                    if(s[j][c] - s[i-1][c] - s[j][c-1] + s[i-1][c-1] < j-i+1) break;
                    int r = c + (ans-1) / (j-i+1);
                    if(f[i][j] >= c || r > m || s[j][r] - s[i-1][r] - s[j][c-1] + s[i-1][c-1] < (r-c+1)*(j-i+1)) continue;
                    int L = r+1, R = m, far = r;
                    while(L <= R) {
                        int mid = (L+R) >> 1;
                        if(s[j][mid] - s[i-1][mid] - s[j][c-1] + s[i-1][c-1] == (mid-c+1)*(j-i+1)) far = mid, L = mid+1;
                        else R = mid-1;
                    }
                    f[i][j] = far;
                    ans = (far-c+1)*(j-i+1);
                }
        memset(s, 0, sizeof(s)), memset(f, 0, sizeof(f));
        // All changed into 'b'
        for(register int i=1;i<=n;++i)
            for(register int j=1;j<=m;++j) {
                s[i][j] = s[i-1][j] + s[i][j-1] - s[i-1][j-1];
                if(g[i][j] == 'a' || g[i][j] == 'w' || g[i][j] == 'x' || g[i][j] == 'z') ++s[i][j];
            }
        for(register int c=1;c<=m;++c)
            for(register int i=1;i<=n;++i)
                for(register int j=i;j<=n;++j) {
                    if(s[j][c] - s[i-1][c] - s[j][c-1] + s[i-1][c-1] < j-i+1) break;
                    int r = c + (ans-1) / (j-i+1);
                    if(f[i][j] >= c || r > m || s[j][r] - s[i-1][r] - s[j][c-1] + s[i-1][c-1] < (r-c+1)*(j-i+1)) continue;
                    int L = r+1, R = m, far = r;
                    while(L <= R) {
                        int mid = (L+R) >> 1;
                        if(s[j][mid] - s[i-1][mid] - s[j][c-1] + s[i-1][c-1] == (mid-c+1)*(j-i+1)) far = mid, L = mid+1;
                        else R = mid-1;
                    }
                    f[i][j] = far;
                    ans = (far-c+1)*(j-i+1);
                }
        memset(s, 0, sizeof(s)), memset(f, 0, sizeof(f));
        // All changed into 'c'
        for(register int i=1;i<=n;++i)
            for(register int j=1;j<=m;++j) {
                s[i][j] = s[i-1][j] + s[i][j-1] - s[i-1][j-1];
                if(g[i][j] == 'a' || g[i][j] == 'z' || g[i][j] == 'x' || g[i][j] == 'y') ++s[i][j];
            }
        for(register int c=1;c<=m;++c)
            for(register int i=1;i<=n;++i)
                for(register int j=i;j<=n;++j) {
                    if(s[j][c] - s[i-1][c] - s[j][c-1] + s[i-1][c-1] < j-i+1) break;
                    int r = c + (ans-1) / (j-i+1);
                    if(f[i][j] >= c || r > m || s[j][r] - s[i-1][r] - s[j][c-1] + s[i-1][c-1] < (r-c+1)*(j-i+1)) continue;
                    int L = r+1, R = m, far = r;
                    while(L <= R) {
                        int mid = (L+R) >> 1;
                        if(s[j][mid] - s[i-1][mid] - s[j][c-1] + s[i-1][c-1] == (mid-c+1)*(j-i+1)) far = mid, L = mid+1;
                        else R = mid-1;
                    }
                    f[i][j] = far;
                    ans = (far-c+1)*(j-i+1);
                }
        memset(s, 0, sizeof(s)), memset(f, 0, sizeof(f));
        printf("%d\n", ans);
    }
    return 0;
}
