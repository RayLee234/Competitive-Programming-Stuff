//
//  main.cpp
//  排列计数 LUOGU4071
//
//  Created by Ruining Li on 2020/3/21.
//  Copyright © 2020 Ruining Li. All rights reserved.
//

#include <iostream>
#include <cstdio>
#define ll long long
using namespace std;
int T,f[1000001],jc[1000001],inv[1000001];
const int mod = 1e9+7;
int exp(int x, int y) {
    int r = 1;
    while(y) {
        if(y&1) r = (ll)r * x % mod;
        y >>= 1;
        x = (ll)x * x % mod;
    }
    return r;
}
void init() {
    f[0] = 1; f[1] = 0;
    for(int i=2;i<=1000000;i++)
        f[i] = (ll)(i-1) * ( (f[i-1] + f[i-2]) % mod ) % mod;
    jc[0] = 1;
    for(int i=1;i<=1000000;i++) jc[i] = (ll)i * jc[i-1] % mod;
    for(int i=0;i<=1000000;i++) inv[i] = exp(jc[i],mod-2);
}
int main() {
    scanf("%d",&T);
    init();
    while(T--) {
        int n,m;
        scanf("%d%d",&n,&m);
        if(m>n) {
            puts("0");
            continue;
        }
        printf("%lld\n",(ll)jc[n] * inv[m] % mod * inv[n-m] % mod * f[n-m] % mod);
    }
    return 0;
}
