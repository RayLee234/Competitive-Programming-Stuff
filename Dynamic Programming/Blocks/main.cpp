//
//  main.cpp
//  Blocks POJ1390
//
//  Created by Ruining Li on 2020/6/22.
//  Copyright © 2020 Ruining Li. All rights reserved.
//

#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;
int T, n, a[201], color[201], num[201], c, f[201][201][201], cur;
int solve(int l, int r, int k) {
    if(f[l][r][k]) return f[l][r][k];
    if(l == r) return (num[l] + k) * (num[l] + k);
    f[l][r][k] = solve(l, r-1, 0) + (num[r] + k) * (num[r] + k);
    for(int i=l;i<r;++i)
        if(color[i] == color[r]) f[l][r][k] = max(f[l][r][k], solve(l, i, num[r]+k) + solve(i+1, r-1, 0));
    return f[l][r][k];
}
int main() {
    cin >> T;
    while(T--) {
        cin >> n;
        c = 0;
        memset(f, 0, sizeof(f));
        for(int i=1;i<=n;++i) {
            cin >> a[i];
            if(a[i] != a[i-1]) color[++c] = a[i], num[c] = 1;
            else ++num[c];
        }
        printf("Case %d: %d\n", ++cur, solve(1, c, 0));
    }
    return 0;
}
