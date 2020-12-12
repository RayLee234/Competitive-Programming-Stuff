//
//  main.cpp
//  计算器 LUOGU2485
//
//  Created by Ruining Li on 2020/3/21.
//  Copyright © 2020 Ruining Li. All rights reserved.
//

#include <iostream>
#include <cstdio>
#include <cmath>
#include <map>
#define ll long long
using namespace std;
int T,k;
int exp(int a, int b, int p) {
    int r = 1;
    while(b) {
        if(b&1) r = (ll)r * a % p;
        b >>= 1;
        a = (ll)a * a % p;
    }
    return r;
}
int baby_step_giant_step(int a, int b, int p) {
    map <int,int> H; H.clear();
    b %= p;
    int t = (int)sqrt(p)+1;
    for(int j=0;j<t;j++) {
        int val = (ll)b * exp(a,j,p) % p;
        H[val] = j;
    }
    a = exp(a,t,p);
    if(a==0) return -1;
    for(int i=0;i<=t;i++) {
        int val = exp(a,i,p);
        int j = H.find(val) == H.end() ? -1 : H[val];
        if(j>=0 && i*t-j>=0) return i*t-j;
    }
    return -1;
}
int main() {
    scanf("%d%d",&T,&k);
    int y,z,p;
    while(T--) {
        scanf("%d%d%d",&y,&z,&p);
        if(k==1) printf("%d\n",exp(y,z,p));
        if(k==2) {
            if(y%p==0){
                if(z==0) puts("0");
                else puts("Orz, I cannot find x!");
            }
            else printf("%lld\n",exp(y,p-2,p)*(ll)z%p);
        }
        if(k==3) {
            int ans = baby_step_giant_step(y, z, p);
            if(ans==-1) puts("Orz, I cannot find x!");
            else printf("%d\n",ans);
        }
    }
    return 0;
}
