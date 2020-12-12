//
//  main.cpp
//  石子合并 O(n^2)算法
//
//  Created by Ruining Li on 2020/7/15.
//  Copyright © 2020 Ruining Li. All rights reserved.
//

#include <iostream>
#include <cstdio>
#include <cstring>
int n, a[4010], s[4010], k[4001][4001], f[4001][4001];
inline int read() {
    int x = 0; char c = getchar();
    while(c < '0' || c > '9') c = getchar();
    while(c >= '0' && c <= '9') x = (x<<3)+(x<<1)+c-'0', c = getchar();
    return x;
}
int main() {
    n = read();
    memset(f, 35, sizeof(f));
    for(register int i=1;i<=n;++i) a[i] = read(), s[i] = a[i] + s[i-1], k[i][i] = i, f[i][i] = 0;
    for(register int d=2;d<=n;++d)
        for(register int l=1;l<=n-d+1;++l) {
            int r = l+d-1;
            for(register int p=k[l][r-1];p<=k[l+1][r];++p)
                if(p < r && f[l][r] > f[l][p] + f[p+1][r] + s[r] - s[l-1]) {
                    f[l][r] = f[l][p] + f[p+1][r] + s[r] - s[l-1];
                    k[l][r] = p;
                }
        }
    printf("%d\n", f[1][n]);
    return 0;
}
