//
//  main.cpp
//  GCD LUOGU2568
//
//  Created by Ruining Li on 2020/3/21.
//  Copyright © 2020 Ruining Li. All rights reserved.
//

#include <iostream>
#include <cstdio>
using namespace std;
bool v[10000001];
int n,cnt,p[664580],mu[10000001],sum[10000001];
long long ans;
inline void init() {
    for(register int i=1;i<=n;++i) mu[i] = 1;
    for(register int i=2;i<=n;++i) {
        if(v[i]) continue;
        mu[i] = -1;
        p[++cnt] = i;
        for(int j=i*2;j<=n;j+=i) {
            v[j] = 1;
            if(j/i%i==0) mu[j] = 0;
            else mu[j] *= -1;
        }
    }
    for(register int i=1;i<=n;++i) sum[i] = sum[i-1] + mu[i];
}
int main() {
    scanf("%d",&n);
    init();
    for(register int i=1;i<=cnt;++i) {
        int t = n / p[i];
        for(int x=1,gx;x<=t;x=gx+1) {
            gx = min(t/(t/x),t);
            ans += (long long)(sum[gx]-sum[x-1]) * (t/x) * (t/x);
        }
    }
    printf("%lld\n",ans);
    return 0;
}
