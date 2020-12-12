se//
//  main.cpp
//  Fibonacci POJ3070
//
//  Created by Ruining Li on 2020/3/14.
//  Copyright © 2020 Ruining Li. All rights reserved.
//

#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
int n;
const int mod = 10000;
void mul(int f[2], int a[2][2]) {
    int r[2];
    memset(r,0,sizeof r);
    for(int j=0;j<2;j++)
        for(int k=0;k<2;k++)
            (r[j] += f[k]*a[k][j]) %= mod;
    memcpy(f, r, sizeof r);
}
void selfmul(int a[2][2]) {
    int r[2][2];
    memset(r,0,sizeof r);
    for(int i=0;i<2;i++)
        for(int j=0;j<2;j++)
            for(int k=0;k<2;k++)
                (r[i][j] += a[i][k]*a[k][j]) %= mod;
    memcpy(a, r, sizeof r);
}
int main() {
    while(scanf("%d",&n)) {
        if(n==-1) return 0;
        int f[2] = {1,0};
        int a[2][2] = {{1,1},{1,0}};
        while(n>0) {
            if(n&1) mul(f,a);
            n >>= 1;
            selfmul(a);
        }
        printf("%d\n",f[1]);
    }
}
