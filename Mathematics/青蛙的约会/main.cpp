//
//  main.cpp
//  青蛙的约会 POJ1061
//
//  Created by Ruining Li on 2020/3/21.
//  Copyright © 2020 Ruining Li. All rights reserved.
//

#include <iostream>
#include <cstdio>
#include <cstring>
#define ll long long
using namespace std;
ll exgcd(ll a, ll b, ll &p, ll &q) {
    if(b==0) {
        p = 1; q = 0;
        return a;
    }
    ll d = exgcd(b,a%b,p,q);
    long long temp = p; p = q; q = temp - a / b * q;
    return d;
}
ll x,y,m,n,L;
int main() {
    cin >> x >> y >> m >> n >> L;
    if(m<n) {
        swap(x,y);
        swap(m,n);
    }
    ll s = m-n, d = (y-x+L)%L, p, q;
    ll gcd= exgcd(s,L,p,q);
    if(d%gcd!=0) {
        puts("Impossible");
        return 0;
    }
    p *= d / gcd;
    q *= d / gcd;
    long long delta = L / gcd;
    cout << (p%delta+delta)%delta << endl;
    return 0;
}
