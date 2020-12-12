//
//  main.cpp
//  Estimation HDOJ4261
//
//  Created by Ruining Li on 2020/7/22.
//  Copyright © 2020 Ruining Li. All rights reserved.
//

#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
int n, m, a[2010], s[2010], median[2010][2010], c[2010][2010], num[20010], sum[20010], f[2010][30];
void update(int x) {
    while(x <= 20001) num[x]++, x += x & (-x);
}
void update2(int x, int val) {
    while(x <= 20001) sum[x] += val, x += x & (-x);
}
int ask(int x) {
    int r = 0;
    while(x > 0) r += num[x], x -= x & (-x);
    return r;
}
int ask2(int x) {
    int r = 0;
    while(x > 0) r += sum[x], x -= x & (-x);
    return r;
}
int main() {
    while(cin >> n >> m) {
        if(n == 0 && m == 0) return 0;
        for(int i=1;i<=n;++i) scanf("%d", &a[i]), a[i] += 10001;
        for(int i=1;i<=n;++i) {
            memset(num, 0, sizeof(num)), memset(sum, 0, sizeof(sum));
            for(int j=i;j<=n;++j) {
                update(a[j]), update2(a[j], a[j]);
                int l = 1, r = 20001, tot = j-i+1;
                while(l <= r) {
                    int mid = (l + r) >> 1;
                    if(ask(mid) >= tot/2+1 && ask(mid-1) < tot/2+1) {
                        int cnt = ask(mid);
                        median[i][j] = mid, c[i][j] = cnt * mid - ask2(mid) + ask2(20001) - ask2(mid) - (tot-cnt) * mid;
                        break;
                    }
                    if(ask(mid) >= tot/2+1) r = mid - 1;
                    else l = mid+1;
                }
            }
        }
        memset(f, 15, sizeof(f));
        f[0][0] = 0;
        for(int i=1;i<=n;++i)
            for(int j=1;j<=m && j<=i;++j)
                for(int k=0;k<i;++k) f[i][j] = min(f[i][j], f[k][j-1]+c[k+1][i]);
        printf("%d\n", f[n][m]);
    }
    return 0;
}
