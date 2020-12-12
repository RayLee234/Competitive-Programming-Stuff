//
//  main.cpp
//  Longge's problem POJ2480
//
//  Created by Ruining Li on 2020/3/21.
//  Copyright © 2020 Ruining Li. All rights reserved.
//

#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;
int n;
int phi(int x) {
    int r = x, t = sqrt((double)x);
    for(register int i=2;i<=t;++i) {
        if(x%i==0) r = r / i * (i-1);
        while(x%i==0) x /= i;
    }
    if(x>1) r = r / x * (x-1);
    return r;
}
int main() {
    while(scanf("%d",&n)!=EOF) {
        long long ans = 0;
        int t = sqrt((double)n);
        for(register int i=1;i<=t;++i)
            if(n%i==0) {
                ans += (long long)phi(n/i) * i;
                if(n/i!=i) ans += (long long)phi(i) * (n/i);
            }
        printf("%lld\n",ans);
    }
    return 0;
}
