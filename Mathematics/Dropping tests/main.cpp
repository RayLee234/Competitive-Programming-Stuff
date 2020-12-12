//
//  main.cpp
//  Dropping tests POJ2976
//
//  Created by Ruining Li on 2020/3/19.
//  Copyright © 2020 Ruining Li. All rights reserved.
//

#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
int n,k;
long long a[1001],b[1001];
int main() {
    while(scanf("%d%d",&n,&k) && n) {
        for(int i=1;i<=n;i++) scanf("%lld",&a[i]), a[i] *= 100;
        for(int i=1;i<=n;i++) scanf("%lld",&b[i]);
        double l = 0, r = 100;
        while(r-l>1e-2) {
            double mid = (l+r)/2, sum = 0, c[1001];
            for(int i=1;i<=n;i++) c[i] = a[i]-mid*b[i], sum += c[i];
            sort(c+1,c+n+1);
            for(int i=1;i<=k;i++) {
                if(c[i]>0) break;
                sum -= c[i];
            }
            if(sum>=0) l = mid;
            else r = mid;
        }
        printf("%d\n",(int)(l+0.5));
    }
    return 0;
}
