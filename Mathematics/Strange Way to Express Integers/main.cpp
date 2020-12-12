//
//  main.cpp
//  Strange Way to Express Integers POJ2891
//
//  Created by Ruining Li on 2020/3/13.
//  Copyright © 2020 Ruining Li. All rights reserved.
//

#include <iostream>
#include <cstdio>
#define ll long long
using namespace std;
int k;
ll exgcd(ll a, ll b, ll &x, ll &y) {
    if(b==0) {
        x = 1; y = 0;
        return a;
    }
    ll d = exgcd(b,a%b,x,y);
    ll z = x; x = y; y = z-(a/b)*y;
    return d;
}
int main() {
    while(scanf("%d",&k)!=EOF) {
        bool ok = 1;
        ll x = 0, lcm = 1;
        ll a,r;
        for(int i=1;i<=k;i++) {
            scanf("%lld%lld",&a,&r);
            ll w, s, t;
            w = exgcd(lcm, a, s, t);
            if((r-x)%w) ok = 0;
            if(ok) {
                s *= (r-x)/w;
                a /= w;
                s = (s%a+a)%a;
                x += lcm*s;
                lcm *= a;
            }
        }
        if(!ok) puts("-1");
        else printf("%lld\n",x==0?lcm:x);
    }
    return 0;
}
