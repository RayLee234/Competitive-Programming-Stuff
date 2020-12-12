//
//  main.cpp
//  魔法珠 CH3B16
//
//  Created by Ruining Li on 2020/3/21.
//  Copyright © 2020 Ruining Li. All rights reserved.
//

#include <iostream>
#include <cmath>
#include <cstdio>
#include <cstring>
using namespace std;
int n,a[101],f[1001];
int SG(int x) {
    if(f[x]>=0) return f[x];
    if(x==1) return f[x] = 0;
    int t = sqrt(x);
    int p[1001], cnt = 0;
    for(int i=1;i<=t;i++)
        if(x%i==0) {
            p[++cnt] = i;
            if(x/i!=i && i!=1) p[++cnt] = x/i;
        }
    bool flag[101];
    memset(flag,0,sizeof flag);
    for(int i=1;i<=cnt;i++) {
        int cur = 0;
        for(int j=1;j<=cnt;j++)
            if(i!=j) cur = cur xor SG(p[j]);
        flag[cur] = 1;
    }
    int r = 0;
    while(flag[r]) ++r;
    return f[x] = r;
}
int main() {
    memset(f,-1,sizeof f);
    while(scanf("%d",&n)!=EOF) {
        int ans = 0;
        for(int i=1;i<=n;++i) scanf("%d",&a[i]), ans = ans xor SG(a[i]);
        if(ans==0) puts("rainbow");
        else puts("freda");
    }
    return 0;
}
