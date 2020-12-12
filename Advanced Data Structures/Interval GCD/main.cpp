//
//  main.cpp
//  Interval GCD CH4302
//
//  Created by Ruining Li on 2020/3/25.
//  Copyright © 2020 Ruining Li. All rights reserved.
//

#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#define ll long long
using namespace std;
ll n,m;
ll a[500001],b[500001],c[500001];
ll gcd(ll x, ll y) {
    if(y==0) return x;
    return gcd(y,x%y);
}
ll lowbit(ll x) {
    return x&(-x);
}
struct tree {
    ll l,r;
    ll g;
}t[2000001];
void plusc(ll x, ll val) {
    while(x<=n) {
        c[x] += val;
        x += lowbit(x);
    }
}
ll sumc(ll x) {
    ll r = 0;
    while(x>0) {
        r += c[x];
        x -= lowbit(x);
    }
    return r;
}
void build(ll root, ll l, ll r) {
    t[root].l = l; t[root].r = r;
    if(l==r) {
        t[root].g = b[l];
        return;
    }
    ll mid = (l+r)/2;
    build(root*2,l,mid);
    build(root*2+1,mid+1,r);
    t[root].g = gcd(t[root*2].g,t[root*2+1].g);
}
void add(ll root, ll x, ll val) {
    if(t[root].l==x && x==t[root].r) {
        t[root].g += val;
        return;
    }
    ll mid = (t[root].l+t[root].r)/2;
    if(x<=mid) add(root*2,x,val);
    else add(root*2+1,x,val);
    t[root].g = gcd(t[root*2].g,t[root*2+1].g);
}
ll solve(ll root, ll l, ll r) {
    if(t[root].l>=l && t[root].r<=r) return t[root].g;
    if(t[root].l>r || t[root].r<l) return 0ll;
    return abs( gcd(solve(root*2,l,r), solve(root*2+1,l,r)) );
}
int main() {
    scanf("%lld%lld",&n,&m);
    for(ll i=1;i<=n;i++) scanf("%lld",&a[i]), b[i] = a[i]-a[i-1];
    build(1,1,n);
    while(m--) {
        char typ;
        cin >> typ;
        if(typ=='C') {
            ll l,r,d; scanf("%lld%lld%lld",&l,&r,&d);
            plusc(l, d); if(r<n) plusc(r+1, -d);
            add(1,l,d); if(r<n) add(1,r+1,-d);
        }
        else {
            ll l,r; scanf("%lld%lld",&l,&r);
            ll a_l = a[l] + sumc(l);
            printf("%lld\n",gcd(a_l,solve(1, l+1, r)));
        }
    }
    return 0;
}
