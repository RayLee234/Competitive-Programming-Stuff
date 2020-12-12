//
//  main.cpp
//  Xiao 9*大战朱最学 CH3B04
//
//  Created by Ruining Li on 2020/3/21.
//  Copyright © 2020 Ruining Li. All rights reserved.
//

#include <iostream>
#define ll long long
using namespace std;
int n;
ll a[11],b[11],A = 1,ans;
ll exgcd(ll p, ll q, ll &x, ll &y) {
    if(q==0) {
        x = 1; y = 0;
        return p;
    }
    ll d = exgcd(q,p%q,x,y);
    ll z = x; x = y; y = z - y * (p/q);
    return d;
}
int main() {
    cin >> n;
    for(int i=1;i<=n;i++) cin >> a[i] >> b[i], A *= a[i];
    for(int i=1;i<=n;i++) {
        ll x, y;
        exgcd(A/a[i],a[i],x,y);
        ans += A/a[i] * x * b[i];
    }
    ans = (ans % A + A) % A;
    printf("%lld\n",ans);
    return 0;
}
