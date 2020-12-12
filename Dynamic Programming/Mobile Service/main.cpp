//
//  main.cpp
//  Mobile Service CH5102
//
//  Created by Ruining Li on 2020/5/1.
//  Copyright © 2020 Ruining Li. All rights reserved.
//

#include <iostream>
#include <cstring>
using namespace std;
int l, n, c[201][201], p[1001], f[1001][201][201], ans = 2e9;
int main() {
    cin >> l >> n;
    for(int i=1;i<=l;++i)
        for(int j=1;j<=l;++j) cin >> c[i][j];
    for(int i=1;i<=n;++i) cin >> p[i];
    p[0] = 3;
    memset(f, 5, sizeof(f));
    f[0][1][2] = 0;
    for(int i=0;i<n;++i)
        for(int x=1;x<=l;++x)
            for(int y=1;y<=l;++y) {
                if(x == p[i] || y == p[i] || x == y) continue;
                f[i+1][x][y] = min(f[i+1][x][y], f[i][x][y] + c[p[i]][p[i+1]]);
                f[i+1][p[i]][y] = min(f[i+1][p[i]][y], f[i][x][y] + c[x][p[i+1]]);
                f[i+1][x][p[i]] = min(f[i+1][x][p[i]], f[i][x][y] + c[y][p[i+1]]);
            }
    for(int x=1;x<=l;++x)
        for(int y=1;y<=l;++y) ans = min(ans, f[n][x][y]);
    cout << ans << endl;
    return 0;
}
