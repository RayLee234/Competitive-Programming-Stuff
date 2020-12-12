//
//  main.cpp
//  计算系数 LUOGU1313
//
//  Created by Ruining Li on 2020/3/16.
//  Copyright © 2020 Ruining Li. All rights reserved.
//

#include <iostream>
#include <cstdio>
using namespace std;
const int mod = 10007;
int a,b,k,n,m,ans = 1;
int exp(int x, int y) {
    int r = 1;
    while(y>0) {
        if(y&1) r = r * x % mod;
        y >>= 1;
        x = x * x % mod;
    }
    return r;
}
int inv(int x) {
    return exp(x,mod-2);
}
int main() {
    scanf("%d%d%d%d%d",&a,&b,&k,&n,&m);
    a %= mod; b %= mod;
    ans = exp(a,n) * exp(b,m) % mod;
    for(int i=k;i>k-n;i--) ans = ans * i % mod;
    for(int i=1;i<=n;i++) ans = ans * inv(i) % mod;
    printf("%d\n",ans);
    return 0;
}
