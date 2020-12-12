//
//  main.cpp
//  The Battle of Chibi HDOJ5542
//
//  Created by Ruining Li on 2020/6/27.
//  Copyright © 2020 Ruining Li. All rights reserved.
//

#include <iostream>
#include <cstring>
#include <algorithm>
#include <cstdio>
using namespace std;
int T, n, m, a[1010], b[1010], f[1010][1010], c[1010], CASE;
const int mod = 1e9 + 7;
void add(int x, int v) {
    while(x <= n+1) {
        (c[x] += v) %= mod;
        x += x & (-x);
    }
}
int sum(int x) {
    int r = 0;
    while(x > 0) {
        (r += c[x]) %= mod;
        x -= x & (-x);
    }
    return r;
}
int main() {
    cin >> T;
    while(T--) {
        scanf("%d %d", &n, &m);
        for(int i=1;i<=n;++i) scanf("%d", &a[i]), b[i] = a[i];
        sort(b+1, b+n+1);
        int t = unique(b+1, b+n+1) - b - 1;
        for(int i=1;i<=n;++i) a[i] = lower_bound(b+1, b+t+1, a[i]) - b + 1;
        a[0] = 1;
        memset(f, 0, sizeof(f));
        f[0][0] = 1;
        for(int i=1;i<=m;++i) {
            memset(c, 0, sizeof(c));
            add(a[0], f[i-1][0]);
            for(int j=1;j<=n;++j) {
                f[i][j] = sum(a[j] - 1);
                add(a[j], f[i-1][j]);
            }
        }
        int ans = 0;
        for(int i=1;i<=n;++i) (ans += f[m][i]) %= mod;
        printf("Case #%d: %d\n", ++CASE, ans);
    }
    return 0;
}
