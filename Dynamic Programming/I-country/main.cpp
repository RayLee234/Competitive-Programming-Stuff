//
//  main.cpp
//  I-country CH5104
//
//  Created by Ruining Li on 2020/5/2.
//  Copyright © 2020 Ruining Li. All rights reserved.
//

#include <iostream>
using namespace std;
int n, m, k, a[16][16], f[16][226][16][16][2][2], s[16][16], prel[16][226][16][16][2][2], prer[16][226][16][16][2][2], prex[16][226][16][16][2][2], prey[16][226][16][16][2][2];
int main() {
    cin >> n >> m >> k;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;++j) cin >> a[i][j], s[i][j] = s[i][j-1] + a[i][j];
    for(int i=1;i<=n;++i)
        for(int j=1;j<=k;++j)
            for(int l=1;l<=m;++l)
                for(int r=l;r<=m;++r) {
                    if(j < r-l+1) continue;
                    for(int p=l;p<=r;++p)
                        for(int q=p;q<=r;++q)
                            if(f[i][j][l][r][0][1] < f[i-1][j-(r-l+1)][p][q][0][1] + s[i][r] - s[i][l-1]) {
                                f[i][j][l][r][0][1] = f[i-1][j-(r-l+1)][p][q][0][1] + s[i][r] - s[i][l-1];
                                prel[i][j][l][r][0][1] = p; prer[i][j][l][r][0][1] = q; prex[i][j][l][r][0][1] = 0; prey[i][j][l][r][0][1] = 1;
                            }
                    for(int p=l;p<=r;++p)
                        for(int q=r;q<=m;++q) {
                            if(f[i][j][l][r][0][0] < f[i-1][j-(r-l+1)][p][q][0][0] + s[i][r] - s[i][l-1]) {
                                f[i][j][l][r][0][0] = f[i-1][j-(r-l+1)][p][q][0][0] + s[i][r] - s[i][l-1];
                                prel[i][j][l][r][0][0] = p; prer[i][j][l][r][0][0] = q; prex[i][j][l][r][0][0] = 0; prey[i][j][l][r][0][0] = 0;
                            }
                            if(f[i][j][l][r][0][0] < f[i-1][j-(r-l+1)][p][q][0][1] + s[i][r] - s[i][l-1]) {
                                f[i][j][l][r][0][0] = f[i-1][j-(r-l+1)][p][q][0][1] + s[i][r] - s[i][l-1];
                                prel[i][j][l][r][0][0] = p; prer[i][j][l][r][0][0] = q; prex[i][j][l][r][0][0] = 0; prey[i][j][l][r][0][0] = 1;
                            }
                        }
                    for(int p=1;p<=l;++p)
                        for(int q=l;q<=r;++q) {
                            if(f[i][j][l][r][1][1] < f[i-1][j-(r-l+1)][p][q][1][1] + s[i][r] - s[i][l-1]) {
                                f[i][j][l][r][1][1] = f[i-1][j-(r-l+1)][p][q][1][1] + s[i][r] - s[i][l-1];
                                prel[i][j][l][r][1][1] = p; prer[i][j][l][r][1][1] = q; prex[i][j][l][r][1][1] = 1; prey[i][j][l][r][1][1] = 1;
                            }
                            if(f[i][j][l][r][1][1] < f[i-1][j-(r-l+1)][p][q][0][1] + s[i][r] - s[i][l-1]) {
                                f[i][j][l][r][1][1] = f[i-1][j-(r-l+1)][p][q][0][1] + s[i][r] - s[i][l-1];
                                prel[i][j][l][r][1][1] = p; prer[i][j][l][r][1][1] = q; prex[i][j][l][r][1][1] = 0; prey[i][j][l][r][1][1] = 1;
                            }
                        }
                    for(int p=1;p<=l;++p)
                        for(int q=r;q<=m;++q) {
                            if(f[i][j][l][r][1][0] < f[i-1][j-(r-l+1)][p][q][0][1] + s[i][r] - s[i][l-1]) {
                                f[i][j][l][r][1][0] = f[i-1][j-(r-l+1)][p][q][0][1] + s[i][r] - s[i][l-1];
                                prel[i][j][l][r][1][0] = p; prer[i][j][l][r][1][0] = q; prex[i][j][l][r][1][0] = 0; prey[i][j][l][r][1][0] = 1;
                            }
                            if(f[i][j][l][r][1][0] < f[i-1][j-(r-l+1)][p][q][1][1] + s[i][r] - s[i][l-1]) {
                                f[i][j][l][r][1][0] = f[i-1][j-(r-l+1)][p][q][1][1] + s[i][r] - s[i][l-1];
                                prel[i][j][l][r][1][0] = p; prer[i][j][l][r][1][0] = q; prex[i][j][l][r][1][0] = 1; prey[i][j][l][r][1][0] = 1;
                            }
                            if(f[i][j][l][r][1][0] < f[i-1][j-(r-l+1)][p][q][1][0] + s[i][r] - s[i][l-1]) {
                                f[i][j][l][r][1][0] = f[i-1][j-(r-l+1)][p][q][1][0] + s[i][r] - s[i][l-1];
                                prel[i][j][l][r][1][0] = p; prer[i][j][l][r][1][0] = q; prex[i][j][l][r][1][0] = 1; prey[i][j][l][r][1][0] = 0;
                            }
                            if(f[i][j][l][r][1][0] < f[i-1][j-(r-l+1)][p][q][0][0] + s[i][r] - s[i][l-1]) {
                                f[i][j][l][r][1][0] = f[i-1][j-(r-l+1)][p][q][0][0] + s[i][r] - s[i][l-1];
                                prel[i][j][l][r][1][0] = p; prer[i][j][l][r][1][0] = q; prex[i][j][l][r][1][0] = 0; prey[i][j][l][r][1][0] = 0;
                            }
                        }
                }
    int ans = 0, curN, curL, curR, curX, curY, curK = k;
    for(int i=1;i<=n;++i)
        for(int l=1;l<=m;++l)
            for(int r=l;r<=m;++r) {
                if(ans < f[i][k][l][r][0][1]) {
                    ans = f[i][k][l][r][0][1];
                    curN = i; curL = l; curR = r; curX = 0; curY = 1;
                }
                if(ans < f[i][k][l][r][0][0]) {
                    ans = f[i][k][l][r][0][0];
                    curN = i; curL = l; curR = r; curX = 0; curY = 0;
                }
                if(ans < f[i][k][l][r][1][1]) {
                    ans = f[i][k][l][r][1][1];
                    curN = i; curL = l; curR = r; curX = 1; curY = 1;
                }
                if(ans < f[i][k][l][r][1][0]) {
                    ans = f[i][k][l][r][1][0];
                    curN = i; curL = l; curR = r; curX = 1; curY = 0;
                }
            }
    cout << "Oil : " << ans << endl;
    while(curK > 0) {
        for(int i=curL;i<=curR;++i) cout << curN << ' ' << i << endl;
        int nowN = curN, nowL = curL, nowR = curR, nowX = curX, nowY = curY, nowK = curK;
        --curN; curK -= nowR - nowL + 1;
        curL = prel[nowN][nowK][nowL][nowR][nowX][nowY]; curR = prer[nowN][nowK][nowL][nowR][nowX][nowY];
        curX = prex[nowN][nowK][nowL][nowR][nowX][nowY]; curY = prey[nowN][nowK][nowL][nowR][nowX][nowY];
    }
    return 0;
}
