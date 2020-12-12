//
//  main.cpp
//  石头游戏 CH3401
//
//  Created by Ruining Li on 2020/3/14.
//  Copyright © 2020 Ruining Li. All rights reserved.
//

#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;
int n,m,t,p;
char s[9][9],r[10][7];
void mul(long long f[65], long long a[65][65]) {
    long long c[65];
    memset(c, 0, sizeof(c));
    for(int j=0;j<=n*m;j++)
        for(int k=0;k<=n*m;k++)
            c[j] += f[k]*a[k][j];
    memcpy(f, c, sizeof(c));
}
void selfmul(long long a[65][65]) {
    long long c[65][65];
    memset(c, 0, sizeof(c));
    for(int i=0;i<=n*m;i++)
        for(int j=0;j<=n*m;j++)
            for(int k=0;k<=n*m;k++)
                c[i][j] += a[i][k]*a[k][j];
    memcpy(a, c, sizeof(c));
}
int num(int i, int j) {
    return (i-1)*m+j;
}
int main() {
    scanf("%d%d%d%d",&n,&m,&t,&p);
    for(int i=1;i<=n;i++) scanf("%s",s[i]+1);
    for(int i=0;i<p;i++) scanf("%s",r[i]);
    long long f[65];
    memset(f, 0, sizeof(f));
    f[0] = 1;
    long long a[61][65][65];
    memset(a, 0, sizeof a);
    for(int k=1;k<=60;k++) {
        a[k][0][0] = 1;
        for(int i=1;i<=n;i++)
            for(int j=1;j<=m;j++) {
                char c = r[s[i][j]-'0'][(k-1)%strlen(r[s[i][j]-'0'])];
                if(c=='N' && i>1) a[k][num(i,j)][num(i-1,j)] = 1;
                if(c=='E' && j<m) a[k][num(i,j)][num(i,j+1)] = 1;
                if(c=='W' && j>1) a[k][num(i,j)][num(i,j-1)] = 1;
                if(c=='S' && i<n) a[k][num(i,j)][num(i+1,j)] = 1;
                if(c>='0' && c<='9') {
                    a[k][0][num(i,j)] = c-'0';
                    a[k][num(i,j)][num(i,j)] = 1;
                }
            }
    }
    long long A[65][65];
    memset(A, 0, sizeof A);
    for(int i=0;i<=n*m;i++) A[i][i] = 1;
    for(int w=1;w<=60;w++) {
        long long c[n*m+1][n*m+1];
        memset(c, 0, sizeof(c));
        for(int i=0;i<=n*m;i++)
            for(int j=0;j<=n*m;j++)
                for(int k=0;k<=n*m;k++)
                    c[i][j] += A[i][k] * a[w][k][j];
        memcpy(A,c,sizeof(c));
    }
    int cnt = t/60;
    while(cnt>0) {
        if(cnt&1) mul(f, A);
        cnt >>= 1;
        selfmul(A);
    }
    for(int i=1;i<=t%60;i++) mul(f,a[i]);
    long long ans = 0;
    for(int i=1;i<=n*m;i++) ans = max(ans,f[i]);
    printf("%lld\n",ans);
    return 0;
}
