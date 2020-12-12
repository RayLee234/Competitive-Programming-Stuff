//
//  main.cpp
//  能量项链 CH5E09
//
//  Created by Ruining Li on 2020/6/21.
//  Copyright © 2020 Ruining Li. All rights reserved.
//

#include <iostream>
using namespace std;
int n, l[201], r[201], f[201][201], ans;
int main() {
    cin >> n >> l[1];
    for(int i=2;i<=n;++i) cin >> l[i], r[i-1] = l[i];
    r[n] = l[1];
    for(int i=1;i<=n;++i) l[i+n] = l[i], r[i+n] = r[i];
    for(int k=2;k<=n;++k)
        for(int i=1;i<=2*n-k+1;++i) {
            int j = i + k -1;
            for(int t=i;t<j;++t) f[i][j] = max(f[i][j], f[i][t] + f[t+1][j] + l[i] * r[t] * r[j]);
        }
    for(int i=1;i<=n;++i) ans = max(ans, f[i][i+n-1]);
    cout << ans << endl;
    return 0;
}
