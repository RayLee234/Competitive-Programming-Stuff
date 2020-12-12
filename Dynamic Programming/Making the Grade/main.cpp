//
//  main.cpp
//  Making the Grade POJ3666
//
//  Created by Ruining Li on 2020/5/1.
//  Copyright © 2020 Ruining Li. All rights reserved.
//

#include <iostream>
#include <algorithm>
#include <cstring>
#include <cmath>
#define ll long long
using namespace std;
int n;
ll a[2001], b[2001], f[2001][2001], ans = 2000000000000000LL;
ll cost(int x, int y) {
    return labs(b[x] - b[y]);
}
int main() {
    cin >> n;
    for(int i=1;i<=n;++i) cin >> a[i], b[i] = a[i];
    sort(b+1, b+n+1);
    memset(f, 32, sizeof f);
    int t = unique(b+1, b+n+1) - b - 1;
    for(int i=1;i<=n;++i) a[i] = lower_bound(b+1, b+t+1, a[i]) - b;
    for(int j=1;j<=t;++j) f[1][j] = cost(a[1], j);
    for(int i=2;i<=n;++i)
        for(int j=1;j<=t;++j) {
            f[i][j] = f[i-1][j] + cost(a[i], j);
            f[i][j] = min(f[i][j], f[i][j-1] - cost(a[i], j-1) + cost(a[i], j));
        }
    for(int j=1;j<=t;++j) ans = min(ans, f[n][j]);
    cout << ans << endl;
    return 0;
}
