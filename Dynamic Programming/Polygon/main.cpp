//
//  main.cpp
//  Polygon LUOGU4342
//
//  Created by Ruining Li on 2020/5/17.
//  Copyright © 2020 Ruining Li. All rights reserved.
//

#include <iostream>
#include <cstdio>
using namespace std;
int n, a[101], f[101][101][2];
char c[101];
int main() {
    cin >> n;
    for(int i=1;i<=n;++i) cin >> c[i] >> a[i], c[i+n] = c[i], a[i+n] = a[i];
    for(int i=1;i<=2*n;++i) for(int j=1;j<=2*n;++j) f[i][j][0] = -1e9, f[i][j][1] = 1e9;
    for(int i=1;i<=2*n;++i) f[i][i][0] = f[i][i][1] = a[i];
    for(int len=2;len<=n;++len)
        for(int l=1;l<=2*n-len+1;++l) {
            int r = l+len-1;
            for(int k=l;k<r;++k) {
                if(c[k+1] == 't') {
                    f[l][r][0] = max(f[l][r][0], f[l][k][0] + f[k+1][r][0]);
                    f[l][r][1] = min(f[l][r][1], f[l][k][1] + f[k+1][r][1]);
                }
                else if(c[k+1] == 'x'){
                    f[l][r][0] = max(f[l][r][0], max( max(f[l][k][0] * f[k+1][r][0], f[l][k][1] * f[k+1][r][1]), max(f[l][k][0] * f[k+1][r][1], f[l][k][1] * f[k+1][r][0]) ) );
                    f[l][r][1] = min(f[l][r][1], min( min(f[l][k][0] * f[k+1][r][0], f[l][k][1] * f[k+1][r][1]), min(f[l][k][0] * f[k+1][r][1], f[l][k][1] * f[k+1][r][0]) ) );
                }
            }
        }
    int maxAns = -1e9;
    for(int i=1;i<=n;++i) maxAns = max(maxAns, f[i][i+n-1][0]);
    cout << maxAns << endl;
    for(int i=1;i<=n;++i)
        if(f[i][i+n-1][0] == maxAns) cout << i << ' ';
    cout << endl;
    return 0;
}
