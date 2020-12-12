//
//  main.cpp
//  Counting Swaps CH3602
//
//  Created by Ruining Li on 2020/3/16.
//  Copyright © 2020 Ruining Li. All rights reserved.
//

#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
int T,n,a[100001],cnt;
const int mod = 1e9+9;
long long exp(long long x, long long y) {
    long long r = 1;
    while(y>0) {
        if(y&1) r = r * x % mod;
        y >>= 1;
        x = x * x % mod;
    }
    return r;
}
long long inv(long long x) {
    return exp(x,mod-2);
}
long long ans, jc[100001], jc_inv[100001];
bool flag[100001];
int main() {
    scanf("%d",&T);
    jc[0] = 1;
    for(int i=1;i<=100000;i++) jc[i] = jc[i-1] * i % mod;
    jc_inv[100000] = inv(jc[100000]);
    for(int i=99999;i>=0;i--) jc_inv[i] = jc_inv[i+1] * (i+1) % mod;
    while(T--) {
        scanf("%d",&n);
        cnt = 0; ans = 1;
        memset(flag, 0, sizeof(flag));
        for(int i=1;i<=n;i++) scanf("%d",&a[i]);
        for(int i=1;i<=n;i++)
            if(!flag[i]) {
                int cur = i, tot = 0;
                while(!flag[cur]) {
                    flag[cur] = 1;
                    cur = a[cur];
                    ++tot;
                }
                ans = ans * exp(tot,tot-2) % mod * jc_inv[tot-1] % mod;
                ++cnt;
            }
        ans = (ans * jc[n-cnt]) % mod;
        printf("%lld\n",ans);
    }
    return 0;
}
