//
//  main.cpp
//  233 Matrix HDOJ5015
//
//  Created by Ruining Li on 2020/3/21.
//  Copyright © 2020 Ruining Li. All rights reserved.
//

#include <iostream>
#include <cstdio>
#include <cstring>
#define ll long long
using namespace std;
int n,m,f[12],A[12][12];
const int mod = 10000007;
void mul(int a[12], int b[12][12]) {
    int r[12]; memset(r, 0, sizeof(r));
    for(int i=0;i<=n+1;i++)
        for(int k=0;k<=n+1;k++)
            r[i] = (r[i] + (ll)a[k] * b[k][i]) % mod;
    memcpy(a, r, sizeof(r));
}
void mulself(int a[12][12]) {
    int r[12][12]; memset(r, 0, sizeof(r));
    for(int i=0;i<=n+1;i++)
        for(int j=0;j<=n+1;j++)
            for(int k=0;k<=n+1;k++)
                r[i][j] = (r[i][j] + (ll)a[i][k] * a[k][j]) % mod;
    memcpy(a, r, sizeof(r));
}
int main() {
    while(scanf("%d%d",&n,&m)!=EOF) {
        memset(f,0,sizeof f);
        memset(A,0,sizeof A);
        for(int i=2;i<=n+1;i++) scanf("%d",&f[i]), f[i] %= mod;
        f[1] = 23; f[0] = 1;
        A[0][0] = 1; for(int i=1;i<=n+1;i++) A[0][i] = 3, A[1][i] = 10;
        for(int i=2;i<=n+1;i++)
            for(int j=i;j<=n+1;j++) A[i][j] = 1;
        while(m) {
            if(m&1) mul(f,A);
            m >>= 1;
            mulself(A);
        }
        printf("%d\n",f[n+1]);
    }
    return 0;
}
