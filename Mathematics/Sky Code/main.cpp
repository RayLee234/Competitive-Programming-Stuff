//
//  main.cpp
//  Sky Code POJ3904
//
//  Created by Ruining Li on 2020/3/21.
//  Copyright © 2020 Ruining Li. All rights reserved.
//

#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
using namespace std;
int a[10001],cnt[10001],mu[10001],n;
bool v[10001];
void init() {
    for(int i=1;i<=10000;i++) mu[i] = 1;
    for(int i=2;i<=10000;i++) {
        if(v[i]) continue;
        mu[i] = -1;
        for(int j=2*i;j<=10000;j+=i) {
            v[j] = 1;
            if(j/i%i==0) mu[j] = 0;
            else mu[j] *= -1;
        }
    }
}
int main() {
    init();
//    for(int i=1;i<=20;i++) cout << mu[i] << ' ';
    while(scanf("%d",&n)!=EOF) {
        long long ans = 0;
        memset(cnt, 0, sizeof(cnt));
        memset(a, 0, sizeof(a));
        for(int i=1;i<=n;i++) {
            int x;
            scanf("%d",&x);
            ++cnt[x];
        }
        for(int i=1;i<=10000;i++)
            for(int j=i;j<=10000;j+=i) a[i]+=cnt[j];
        for(int i=1;i<=10000;i++) ans += (long long)a[i]*(a[i]-1)*(a[i]-2)*(a[i]-3)/24*mu[i];
        printf("%lld\n",ans);
    }
    return 0;
}
