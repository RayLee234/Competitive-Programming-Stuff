//
//  main.cpp
//  Sorting It All Out POJ1094
//
//  Created by Ruining Li on 2020/8/9.
//  Copyright © 2020 Ruining Li. All rights reserved.
//

#pragma GCC optimize(3)
#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;
int n, m, d[30][30], s[30];
char e[100000][4];
int main() {
    while(scanf("%d %d", &n, &m)) {
        if(n == 0 && m == 0) return 0;
        for(int i=1;i<=m;++i) scanf("%s", e[i]);
        int L = 1, R = m, ans = -1;
        while(L <= R) {
            int mid = (L + R) >> 1;
            memset(d, 0, sizeof(d));
            for(register int i=1;i<=mid;++i)
                if(e[i][1] == '<') d[e[i][0] - 'A' + 1][e[i][2] - 'A' + 1] = 1;
                else d[e[i][2] - 'A' + 1][e[i][0] - 'A' + 1] = 1;
            for(register int k=1;k<=n;++k)
                for(register int i=1;i<=n;++i)
                    for(register int j=1;j<=n;++j) d[i][j] |= d[i][k] & d[k][j];
            bool ok = 1;
            for(register int i=1;i<=n;++i) {
                for(register int j=i+1;j<=n;++j)
                    if(d[i][j] + d[j][i] != 1) { ok = 0; break; }
                if(!ok) break;
            }
            if(ok) { ans = mid; R = mid - 1; }
            else L = mid + 1;
        }
        if(ans != -1) {
            memset(d, 0, sizeof(d));
            for(register int i=1;i<=ans;++i)
                if(e[i][1] == '<') d[e[i][0] - 'A' + 1][e[i][2] - 'A' + 1] = 1;
                else d[e[i][2] - 'A' + 1][e[i][0] - 'A' + 1] = 1;
            for(register int k=1;k<=n;++k)
                for(register int i=1;i<=n;++i)
                    for(register int j=1;j<=n;++j) d[i][j] |= d[i][k] & d[k][j];
            for(register int i=1;i<=n;++i)
                for(register int j=1;j<=n;++j) {
                    int cnt = 0;
                    for(register int k=1;k<=n;++k)
                        if(d[k][j] == 1) ++cnt;
                    if(cnt == i-1) s[i] = j;
                }
            printf("Sorted sequence determined after %d relations: ", ans);
            for(register int i=1;i<=n;++i) putchar(s[i] + 'A' - 1);
            puts(".");
            continue;
        }
        L = 1, R = m, ans = -1;
        while(L <= R) {
            int mid = (L + R) >> 1;
            memset(d, 0, sizeof(d));
            for(register int i=1;i<=mid;++i)
                if(e[i][1] == '<') d[e[i][0] - 'A' + 1][e[i][2] - 'A' + 1] = 1;
                else d[e[i][2] - 'A' + 1][e[i][0] - 'A' + 1] = 1;
            for(register int k=1;k<=n;++k)
                for(register int i=1;i<=n;++i)
                    for(register int j=1;j<=n;++j) d[i][j] |= d[i][k] & d[k][j];
            bool ok = 0;
            for(register int i=1;i<=n;++i) {
                for(register int j=i+1;j<=n;++j)
                    if(d[i][j] + d[j][i] == 2) { ok = 1; break; }
                if(ok) break;
            }
            if(ok) { ans = mid; R = mid - 1; }
            else L = mid + 1;
        }
        if(ans != -1) printf("Inconsistency found after %d relations.\n", ans);
        else puts("Sorted sequence cannot be determined.");
    }
    return 0;
}
