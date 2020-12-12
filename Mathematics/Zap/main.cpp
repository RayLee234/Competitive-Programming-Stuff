//
//  main.cpp
//  Zap LUOGU3455
//
//  Created by Ruining Li on 2020/3/17.
//  Copyright © 2020 Ruining Li. All rights reserved.
//

#include <iostream>
#include <cstring>
using namespace std;
inline long long read() {
    long long r = 0; char c = getchar();
    while(c>'9' || c<'0') c = getchar();
    while(c>='0' && c<='9') r = (r<<3)+(r<<1)+c-'0', c = getchar();
    return r;
}
bool v[50001];
long long n,miu[50001],f[50001];
inline void init() {
    for(int i=1;i<=50000;++i) miu[i] = 1;
    for(int i=2;i<=50000;++i) {
        if(v[i]) continue;
        miu[i] = -1;
        for(int j=2*i;j<=50000;j+=i) {
            v[j] = 1;
            if(j/i%i==0) miu[j] = 0;
            else miu[j] *= -1;
        }
    }
    for(int i=1;i<=50000;i++) f[i] = f[i-1] + miu[i];
}
int main() {
    n = read();
    init();
    while(n--) {
        long long a = read(), b = read(), d = read();
        a /= d; b /= d;
        long long ans = 0;
        for(long long x=1,gx; x<=a && x<=b; x=gx+1) {
            gx = min(a/(a/x),b/(b/x));
            ans += (a/x)*(b/x)*(f[gx]-f[x-1]);
        }
        printf("%lld\n",ans);
    }
    return 0;
}
