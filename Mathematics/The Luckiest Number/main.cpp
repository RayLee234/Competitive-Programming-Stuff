//
//  main.cpp
//  The Luckiest Number POJ3696
//
//  Created by Ruining Li on 2020/3/13.
//  Copyright © 2020 Ruining Li. All rights reserved.
//

#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;
long long L;
long long gcd(long long x, long long y) {
    if(x<y) swap(x,y);
    if(!y) return x;
    return gcd(y,x%y);
}
long long phi(long long x) {
    long long ans = x;
    for(int i=2;i<=sqrt((double)x);i++)
        if(x%i==0) {
            ans = ans/i*(i-1);
            while(x%i==0) x/=i;
        }
    if(x>1) ans = ans/x*(x-1);
    return ans;
}
long long multiply(long long x, long long y) {
    long long ans = 0, base = x;
    while(y>0) {
        if(y&1) ans = (ans+base)%L;
        y >>= 1;
        base = (base+base)%L;
    }
    return ans;
}
long long exp(long long x, long long y) {
    long long ans = 1, base = x;
    while(y>0) {
        if(y&1) ans = multiply(ans, base);
        y >>= 1;
        base = multiply(base, base);
    }
    return ans;
}
int T;
int main() {
    while(scanf("%lld",&L)) {
        if(L==0) return 0;
        long long d = gcd(L,8ll);
        L = 9*L/d;
        if(L%2==0 || L%5==0) {
            printf("Case %d: 0\n",++T);
            continue;
        }
        long long n = phi(L), ans = n;
        for(int i=1;i<=sqrt((double)n);i++)
            if(n%i==0) {
                if(exp(10ll,i)==1) ans = min(ans,(long long)i);
                if(exp(10ll,n/i)==1) ans = min(ans,n/i);
            }
        printf("Case %d: %lld\n",++T,ans);
    }
    return 0;
}
