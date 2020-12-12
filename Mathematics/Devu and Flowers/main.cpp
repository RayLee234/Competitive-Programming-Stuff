//
//  main.cpp
//  Devu and Flowers CF451E
//
//  Created by Ruining Li on 2020/3/17.
//  Copyright © 2020 Ruining Li. All rights reserved.
//

#include <iostream>
#include <cstdio>
#define ll long long
using namespace std;
const int mod = 1e9+7;
int n, ans;
ll s, f[21], inv[21];
int exp(int a, int b) {
    int r = 1;
    while(b>0) {
        if(b&1) r = (ll)r * a % mod;
        b >>= 1;
        a = (ll)a * a % mod;
    }
    return r;
}
int C(ll a, int b) {
    if(a<b || a<0 || b<0) return 0;
    int r = 1;
    for(int i=0;i<b;i++) r = (a-i) % mod * (ll)r % mod;
    for(int i=1;i<=b;i++) r = (ll)r * inv[i] % mod;
    return r;
}
int main() {
    scanf("%d%lld",&n,&s);
    for(int i=1;i<=n;i++) scanf("%lld",&f[i]);
    for(int i=1;i<=n;i++) inv[i] = exp(i,mod-2);
    for(int i=0;i<(1<<n);i++) {
        ll t = s + n, p = 0;
        if(i==0) {
            ans = (ans + C(s+n-1,n-1)) % mod;
            continue;
        }
        for(int j=0;j<n;j++)
            if(i&(1<<j)) {
                ++p;
                t -= f[j+1];
            }
        t -= p+1;
        if(p&1) ans = ((ans - C(t,n-1)) % mod + mod) % mod;
        else ans = (ans + C(t,n-1)) % mod;
    }
    printf("%d\n",ans);
    return 0;
}
