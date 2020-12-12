//
//  main.cpp
//  Gerald and Giant Chess Codeforces559C
//
//  Created by Ruining Li on 2020/7/20.
//  Copyright © 2020 Ruining Li. All rights reserved.
//

#include <iostream>
#include <algorithm>
#define ll long long
using namespace std;
int h, w, n, f[2010], jc[200010], jcinv[200010];
const int mod = 1e9 + 7;
int power(int x, int y) {
    int base = x, res = 1;
    while(y > 0) {
        if(y & 1) res = (ll)res * base % mod;
        y >>= 1;
        base = (ll)base * base % mod;
    }
    return res;
}
void init() {
    jc[0] = 1;
    for(int i=1;i<=200000;++i) jc[i] = (ll)jc[i-1] * i % mod;
    for(int i=0;i<=200000;++i) jcinv[i] = power(jc[i], mod-2);
}
int C(int x, int y) {
    return (ll)jc[y] * jcinv[y-x] % mod * (ll)jcinv[x] % mod;
}
pair<int,int> a[2010];
int main() {
    cin >> h >> w >> n;
    for(int i=1;i<=n;++i) cin >> a[i].first >> a[i].second;
    sort(a+1, a+n+1);
    init();
    for(int i=1;i<=n;++i) {
        f[i] = C(a[i].first-1, a[i].first+a[i].second-2);
        for(int j=1;j<i;++j)
            if(a[j].first <= a[i].first && a[j].second <= a[i].second) f[i] = (f[i] - f[j] * (ll)C(a[i].first-a[j].first, a[i].first+a[i].second-a[j].first-a[j].second)+ mod) % mod;
    }
    int ans = C(h-1, h+w-2);
    for(int i=1;i<=n;++i) ans = (ans - f[i] * (ll)C(h-a[i].first, h+w-a[i].first-a[i].second) % mod + mod) % mod;
    cout << ans << endl;
    return 0;
}
