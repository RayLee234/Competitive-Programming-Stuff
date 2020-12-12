//
//  main.cpp
//  Matrix Power Series POJ3233
//
//  Created by Ruining Li on 2020/3/21.
//  Copyright © 2020 Ruining Li. All rights reserved.
//

#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
int n,k,m,A[31][31],B[31][31];
inline void mul(int a[31][31], int b[31][31]) {
    int r[31][31];
    memset(r, 0, sizeof(r));
    for(register int i=1;i<=n;++i)
        for(register int j=1;j<=n;++j)
            for(register int k=1;k<=n;++k)
                r[i][j] = (r[i][j] + a[i][k] * b[k][j]) % m;
    memcpy(a, r, sizeof(r));
}
inline void solve(int r) {
    if(r==1) return;
    solve(r/2);
    if(r&1) {
        int a[31][31]; memcpy(a, A, sizeof(A));
        int b[31][31]; memcpy(b, B, sizeof(B));
        int c[31][31]; memcpy(c, B, sizeof(B));
        int last[31][31]; memset(last, 0, sizeof(last)); for(int i=1;i<=n;i++) last[i][i] = 1;
        int x = r/2;
        while(x) {
            if(x&1) mul(c,a);
            x >>= 1;
            mul(a,a);
        }
        memcpy(a, A, sizeof(A));
        x = r;
        while(x) {
            if(x&1) mul(last,a);
            x >>= 1;
            mul(a,a);
        }
        for(register int i=1;i<=n;++i)
            for(register int j=1;j<=n;++j) B[i][j] = (b[i][j] + c[i][j] + last[i][j]) % m;
    }
    else {
        int a[31][31]; memcpy(a, A, sizeof(A));
        int b[31][31]; memcpy(b, B, sizeof(B));
        int c[31][31]; memcpy(c, B, sizeof(B));
        int x = r/2;
        while(x) {
            if(x&1) mul(c,a);
            x >>= 1;
            mul(a,a);
        }
        for(register int i=1;i<=n;++i)
            for(register int j=1;j<=n;++j) B[i][j] = (b[i][j] + c[i][j]) % m;
    }
}
int main() {
    scanf("%d%d%d",&n,&k,&m);
    for(register int i=1;i<=n;++i)
        for(register int j=1;j<=n;++j) scanf("%d",&A[i][j]), A[i][j] %= m;
    memcpy(B, A, sizeof(A));
    solve(k);
    for(register int i=1;i<=n;++i) {
        for(register int j=1;j<=n;++j) printf("%d ", B[i][j]);
        putchar('\n');
    }
    return 0;
}
