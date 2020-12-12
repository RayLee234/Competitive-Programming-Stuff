//
//  main.cpp
//  K-Anonymous Sequence POJ3709
//
//  Created by Ruining Li on 2020/7/27.
//  Copyright © 2020 Ruining Li. All rights reserved.
//

#include <iostream>
#include <cstdio>
#include <cstring>
#define int long long
using namespace std;
int T, n, k, a[500010], s[500010], f[500010], q[500010];
signed main() {
    scanf("%lld", &T);
    while(T--) {
        scanf("%lld %lld", &n, &k);
        for(int i=1;i<=n;++i) scanf("%lld", &a[i]), s[i] = s[i-1] + a[i];
        int L = 0, R = -1;
        q[++R] = 0;
        for(int i=k;i<=n;++i) {
            if(i-k >= k) {
                while(L < R && (f[q[R]]-s[q[R]]+q[R]*a[q[R]+1]-f[q[R-1]]+s[q[R-1]]-q[R-1]*a[q[R-1]+1]) *  (a[i-k+1]-a[q[R]+1]) >= (f[i-k]-s[i-k]+(i-k)*a[i-k+1]-f[q[R]]+s[q[R]]-q[R]*a[q[R]+1]) * (a[q[R]+1]-a[q[R-1]+1])) --R;
                q[++R] = i-k;
            }
            while(L < R && (f[q[L+1]]-s[q[L+1]]+q[L+1]*a[q[L+1]+1]-f[q[L]]+s[q[L]]-q[L]*a[q[L]+1]) < i * (a[q[L+1]+1]-a[q[L]+1])) ++L;
            f[i] = f[q[L]] + s[i] - s[q[L]] - (i-q[L])*a[q[L]+1];
        }
        printf("%lld\n", f[n]);
    }
    return 0;
}
