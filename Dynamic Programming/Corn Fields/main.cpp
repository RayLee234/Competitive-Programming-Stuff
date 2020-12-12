//
//  main.cpp
//  Corn Fields POJ3254
//
//  Created by Ruining Li on 2020/6/24.
//  Copyright © 2020 Ruining Li. All rights reserved.
//

#include <iostream>
using namespace std;
int n, m, g[13][12], f[13][1<<12], ans;
const int mod = 1e8;
bool valid(int r, int x) {
    int last1 = -10;
    for(int i=0;i<m;++i)
        if((x>>i) & 1) {
            if(i-last1 == 1 || g[r][i] == 0) return 0;
            last1 = i;
        }
    return 1;
}
int main() {
    cin >> n >> m;
    for(int i=1;i<=n;++i)
        for(int j=0;j<m;++j) cin >> g[i][j];
    f[0][0] = 1;
    for(int i=1;i<=n;++i)
        for(int j=0;j<(1<<m);++j)
            for(int k=0;k<(1<<m);++k)
                if((j&k) == 0 && valid(i,j) && valid(i-1,k)) (f[i][j] += f[i-1][k]) %= mod;
    for(int i=0;i<(1<<m);++i) (ans += f[n][i]) %= mod;
    cout << ans << endl;
    return 0;
}
