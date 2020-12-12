//
//  main.cpp
//  古代猪文 LUOGU2480
//
//  Created by Ruining Li on 2020/3/16.
//  Copyright © 2020 Ruining Li. All rights reserved.
//

#include <iostream>
#include <cstdio>
#include <cmath>
#define ll long long
using namespace std;
ll n,g,f1[3],f2[4],f3[4680],f4[35618],f_inv1[3],f_inv2[4],f_inv3[4680],f_inv4[35618];
const ll mod = 999911659;
ll exp(ll x, ll y, ll p) {
    ll r = 1;
    while(y>0) {
        if(y&1) r = r * x % p;
        y >>= 1;
        x = x * x % p;
    }
    return r;
}
ll inv(ll x, ll p) {
    return exp(x,p-2,p);
}
ll exgcd(ll a, ll b, ll &x, ll &y) {
    if(b==0) {
        x = 1; y = 0;
        return a;
    }
    ll d = exgcd(b,a%b,x,y);
    ll z = x; x = y; y = z - a/b * y;
    return d;
}
void init() {
    f1[0] = f2[0] = f3[0] = f4[0] = 1;
    for(int i=1;i<2;i++) f1[i] = f1[i-1] * i % 2;
    for(int i=1;i<3;i++) f2[i] = f2[i-1] * i % 3;
    for(int i=1;i<4679;i++) f3[i] = f3[i-1] * i % 4679;
    for(int i=1;i<35617;i++) f4[i] = f4[i-1] * i % 35617;
    f_inv1[1] = inv(f1[1],2); f_inv2[2] = inv(f2[2],3); f_inv3[4678] = inv(f3[4678],4679); f_inv4[35616] = inv(f4[35616],35617);
    for(int i=0;i>=0;i--) f_inv1[i] = f_inv1[i+1] * (i+1) % 2;
    for(int i=1;i>=0;i--) f_inv2[i] = f_inv2[i+1] * (i+1) % 3;
    for(int i=4677;i>=0;i--) f_inv3[i] = f_inv3[i+1] * (i+1) % 4679;
    for(int i=35615;i>=0;i--) f_inv4[i] = f_inv4[i+1] * (i+1) % 35617;
}
ll C(ll x, ll y, ll p) {
    if(x<y) return 0ll;
    if(x==0) return 1ll;
    if(x<p && y<p) {
        if(p==2) return f1[x] * f_inv1[x-y] % p * f_inv1[y] % p;
        if(p==3) return f2[x] * f_inv2[x-y] % p * f_inv2[y] % p;
        if(p==4679) return f3[x] * f_inv3[x-y] % p * f_inv3[y] % p;
        if(p==35617) return f4[x] * f_inv4[x-y] % p * f_inv4[y] % p;
    }
    return C(x%p,y%p,p) * C(x/p,y/p,p) % p;
}
// 999911658 = 2 * 3 * 4679 * 35617
int main() {
    scanf("%lld%lld",&n,&g);
    if(g==mod) {
        puts("0");
        return 0;
    }
    init();
    int ans = 0;
    for(int i=1;i*i<=n;i++)
        if(n%i==0) {
            ll a1 = C(n,n/i,2), a2 = C(n,n/i,3), a3 = C(n,n/i,4679), a4 = C(n,n/i,35617);
            ll w = 0;
            w = (w + (mod-1)/2 * inv((mod-1)/2,2) % (mod-1) * a1 % (mod-1)) % (mod-1);
            w = (w + (mod-1)/3 * inv((mod-1)/3,3) % (mod-1) * a2 % (mod-1)) % (mod-1);
            w = (w + (mod-1)/4679 * inv((mod-1)/4679,4679) % (mod-1) * a3 % (mod-1)) % (mod-1);
            w = (w + (mod-1)/35617 * inv((mod-1)/35617,35617) % (mod-1) * a4 % (mod-1)) % (mod-1);
            ans = (ans + w) % (mod-1);
            if(i!=n/i) {
                ll a1 = C(n,i,2), a2 = C(n,i,3), a3 = C(n,i,4679), a4 = C(n,i,35617);
                ll w = 0;
                w = (w + (mod-1)/2 * inv((mod-1)/2,2) % (mod-1) * a1 % (mod-1)) % (mod-1);
                w = (w + (mod-1)/3 * inv((mod-1)/3,3) % (mod-1) * a2 % (mod-1)) % (mod-1);
                w = (w + (mod-1)/4679 * inv((mod-1)/4679,4679) % (mod-1) * a3 % (mod-1)) % (mod-1);
                w = (w + (mod-1)/35617 * inv((mod-1)/35617,35617) % (mod-1) * a4 % (mod-1)) % (mod-1);
                ans = (ans + w) % (mod-1);
            }
        }
    printf("%lld\n",exp(g,ans,mod));
    return 0;
}
