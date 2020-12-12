//
//  main.cpp
//  股票交易 LUOGU2569
//
//  Created by Ruining Li on 2020/7/22.
//  Copyright © 2020 Ruining Li. All rights reserved.
//

#include <iostream>
#include <cstring>
using namespace std;
int T, P, W, f[2010][2010], L, R, q[2010];
int main() {
    cin >> T >> P >> W;
    memset(f, 128, sizeof(f));
    f[0][0] = 0;
    for(int i=1;i<=T;++i) {
        int ap, bp, as, bs; cin >> ap >> bp >> as >> bs;
        for(int j=0;j<=as;++j) f[i][j] = max(f[i][j], -j*ap);
        for(int j=0;j<=P;++j) f[i][j] = max(f[i][j], f[i-1][j]);
        if(i <= W) continue;
        L = 0, R = -1;
        for(int j=0;j<=P;++j) {
            while(L <= R && q[L] < j - as) ++L;
            if(L <= R) f[i][j] = max(f[i][j], f[i-W-1][q[L]] - ap*(j-q[L]));
            while(L <= R && f[i-W-1][q[R]] + ap*q[R] <= f[i-W-1][j] + ap*j) --R;
            q[++R] = j;
        }
        L = 0, R = -1;
        for(int j=P;j>=0;--j) {
            while(L <= R && q[L] > j + bs) ++L;
            if(L <= R) f[i][j] = max(f[i][j], f[i-W-1][q[L]] + bp*(q[L]-j));
            while(L <= R && f[i-W-1][q[R]] + bp*q[R] <= f[i-W-1][j] + bp*j) --R;
            q[++R] = j;
        }
    }
    cout << f[T][0] << endl;
    return 0;
}
