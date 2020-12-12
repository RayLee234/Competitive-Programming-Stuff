//
//  main.cpp
//  石子合并 LUOGU1880
//
//  Created by Ruining Li on 2020/5/17.
//  Copyright © 2020 Ruining Li. All rights reserved.
//

#include <iostream>
#include <cstring>
using namespace std;
int n, f[201][201], g[201][201], a[201], s[201];
int main() {
    cin >> n;
    for(int i=1;i<=n;++i) cin >> a[i], a[i+n] = a[i];
    for(int i=1;i<=2*n;++i) s[i] = s[i-1] + a[i];
    memset(f, 5, sizeof(f));
    for(int i=1;i<=2*n;++i) f[i][i] = 0;
    for(int len=2;len<=n;++len)
        for(int l=1;l<=2*n-len+1;++l) {
            int r = l+len-1;
            for(int k=l;k<r;++k) f[l][r] = min(f[l][r], f[l][k] + f[k+1][r] + s[r] - s[l-1]), g[l][r] = max(g[l][r], g[l][k] + g[k+1][r] + s[r] - s[l-1]);
        }
    int minAns = 2e9, maxAns = 0;
    for(int i=1;i<=n;++i) minAns = min(minAns, f[i][i+n-1]), maxAns = max(maxAns, g[i][i+n-1]);
    cout << minAns << endl << maxAns << endl;
    return 0;
}
