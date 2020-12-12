//
//  main.cpp
//  扑克牌 CH5E26 计数类DP+容斥原理
//
//  Created by Ruining Li on 2020/8/1.
//  Copyright © 2020 Ruining Li. All rights reserved.
//

#include <iostream>
#include <cstring>
#include <cstdio>
#define ull unsigned long long
using namespace std;
int T, c[14], num[5], t;
ull f[14][14][14][14];
ull solve(int a, int b, int c, int d) {
    if(f[a][b][c][d] != -1) return f[a][b][c][d];
    ull cnt = 0;
    if(a > 0) cnt += a * solve(a-1, b, c, d);
    if(b > 0) cnt += b * 2 * solve(a+1, b-1, c, d) - b * 2 * solve(a, b-1, c, d);
    if(c > 0) cnt += c * 3 * solve(a, b+1, c-1, d) - c * 6 * solve(a+1, b, c-1, d) + c * 6 * solve(a, b, c-1, d);
    if(d > 0) cnt += d * 4 * solve(a, b, c+1, d-1) - d * 12 * solve(a, b+1, c, d-1) + d * 24 * solve(a+1, b, c, d-1) - d * 24 * solve(a, b, c, d-1);
    return f[a][b][c][d] = cnt;
}
signed main() {
    cin >> T;
    memset(f, -1, sizeof(f));
    f[0][0][0][0] = 1;
    while(T--) {
        memset(c, 0, sizeof(c));
        memset(num, 0, sizeof(num));
        int n;
        scanf("%d", &n);
        for(register int i=1;i<=n;++i) {
            char card[3];
            scanf("%s", card);
            if(card[0] >= '2' && card[0] <= '9') ++c[card[0]-'0'];
            else if(card[0] == 'A') ++c[1];
            else if(card[0] == 'T') ++c[10];
            else if(card[0] == 'J') ++c[11];
            else if(card[0] == 'Q') ++c[12];
            else if(card[0] == 'K') ++c[13];
        }
        for(register int i=1;i<=13;++i) ++num[c[i]];
        printf("Case #%d: %llu\n", ++t, solve(num[1], num[2], num[3], num[4]));
    }
    return 0;
}
