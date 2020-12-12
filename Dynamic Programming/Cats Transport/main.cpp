//
//  main.cpp
//  Cats Transport Codeforces311B
//
//  Created by Ruining Li on 2020/7/13.
//  Copyright © 2020 Ruining Li. All rights reserved.
//

#include <iostream>
#include <cstring>
#include <algorithm>
#define int long long
using namespace std;
int n, m, p, d[200010], h[100010], t[100010], a[100010], s[100010], f[101][100010], q[100010];
signed main() {
    cin >> n >> m >> p;
    for(int i=2;i<=n;++i) cin >> d[i], d[i] += d[i-1];
    for(int i=1;i<=m;++i) cin >> h[i] >> t[i], a[i] = t[i] - d[h[i]];
    sort(a+1, a+m+1);
    for(int i=1;i<=m;++i) s[i] = s[i-1] + a[i], f[1][i] = a[i] * i - s[i];
    for(int i=2;i<=p;++i) {
        int L = 0, R = -1;
        q[++R] = 0;
        for(int j=1;j<=m;++j) {
            while(L < R && f[i-1][q[L]]+s[q[L]]-f[i-1][q[L+1]]-s[q[L+1]] >= a[j] * (q[L]-q[L+1])) ++L;
            f[i][j] = f[i-1][q[L]] + a[j]*(j-q[L]) - (s[j]-s[q[L]]);
            while(L < R && (f[i-1][j]+s[j]-f[i-1][q[R]]-s[q[R]]) * (q[R]-q[R-1]) <= (f[i-1][q[R]]+s[q[R]]-f[i-1][q[R-1]]-s[q[R-1]]) * (j-q[R])) --R;
            q[++R] = j;
        }
    }
    cout << f[p][m] << endl;
    return 0;
}
