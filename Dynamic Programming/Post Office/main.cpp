//
//  main.cpp
//  Post Office POJ1160
//
//  Created by Ruining Li on 2020/7/28.
//  Copyright © 2020 Ruining Li. All rights reserved.
//

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
int n, m, d[3010], s[3010], pre[3010][3010], f[3010][310], c[3010][310];
int main() {
    scanf("%d %d", &n, &m);
    for(register int i=1;i<=n;++i) scanf("%d", &d[i]), s[i] = s[i-1] + d[i];
    sort(d+1, d+n+1);
    d[0] = -2147483648;
    for(register int i=1;i<n;++i)
        for(register int j=i+1;j<=n;++j) {
            int L = i+1, R = j-1, res = j;
            while(L <= R) {
                int mid = (L+R) >> 1;
                if(d[j] - d[mid] >= d[mid] - d[i]) L = mid + 1;
                else res = mid, R = mid - 1;
            }
            pre[i][j] = s[res-1] - s[i] - d[i] * (res-i-1) + (j-res+1) * d[j] - s[j] + s[res-1];
        }
    for(int i=1;i<=n;++i) pre[0][i] = d[i] * i - s[i];
    memset(f, 15, sizeof(f));
    f[0][0] = f[1][1] = 0;
    for(register int i=2;i<=n;++i)
        for(register int j=1;j<=min(i,m);++j)
            for(register int k=max(j-1,c[i][j-1]);k<i;++k)
                if(f[i][j] > f[k][j-1] + pre[k][i]) f[i][j] = f[k][j-1] + pre[k][i], c[i][j] = k;
    int ans = 1e9;
    for(register int i=m;i<=n;++i) ans = min(ans, f[i][m] + s[n] - s[i] - (n-i)*d[i]);
    printf("%d\n", ans);
    return 0;
}
