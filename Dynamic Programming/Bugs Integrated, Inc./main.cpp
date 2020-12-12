//
//  main.cpp
//  Bugs Integrated, Inc. POJ1038
//
//  Created by Ruining Li on 2020/6/24.
//  Copyright © 2020 Ruining Li. All rights reserved.
//

#pragma GCC optimize(2)
#pragma GCC optimize("inline")
#include <iostream>
#include <cstring>
#include <vector>
#include <cstdio>
using namespace std;
int t, n, m, f[151][5177], s[5177];
bool g[151][11];
vector < pair<short int,short int> > chosable[5177];
inline bool valid(int r, int x) {
    for(register int i=1;i<=m;++i) {
        if(x % 4 != 0 && g[r][i] > 0) return 0;
        x /= 4;
    }
    return 1;
}
inline bool valid2(int x, int y) { // x: current line; y: previous line
    int cnt = 0;
    for(register int i=1;i<=m;++i) {
        int a = x % 4, b = y % 4;
        x /= 4, y /= 4;
        if(b == 3 && a != 2) return 0;
        if(b == 2 && a != 1) return 0;
        if(a == 1 && b != 2) return 0;
        if(a == 2 && b != 3) ++cnt;
        else {
            if(cnt % 3 != 0) return 0;
            cnt = 0;
        }
    }
    return 1;
}
inline int count(int x, int y) { // x: current line; y: previous line
    int X = x, num = 0, cnt = 0;
    for(register int i=1;i<=m;++i) {
        int a = X % 4; X /= 4;
        if(a == 3) ++num;
        else cnt += num / 2, num = 0;
    }
    cnt += num / 2, num = 0;
    for(register int i=1;i<=m;++i) {
        int a = x % 4, b = y % 4;
        x /= 4, y /= 4;
        if(a == 2 && b != 3) ++num;
        else cnt += num / 3, num = 0;
    }
    cnt += num / 3;
    return cnt;
}
inline bool only0and1(int x) {
    for(int i=1;i<=m;++i) {
        if(x % 4 >= 2) return 0;
        x /= 4;
    }
    return 1;
}
inline int read() {
    int r = 0; char c = getchar();
    while(c < '0' || c > '9') c = getchar();
    while(c >= '0' && c <= '9') r = (r<<3) + (r<<1) + c - '0', c = getchar();
    return r;
}
int main() {
    t = read();
    while(t--) {
        memset(g, 0, sizeof(g));
        memset(f, 0, sizeof(f));
        int v, num = 0;
        n = read(), m = read(), v = read();
        while(v--) {
            int x = read(), y = read();
            g[x][y] = 1;
        }
        for(register int i=0;i<(1<<(2*m));++i) {
            int now = i, cnt = 0, lastDigit = -1; bool ok = 1;
            for(int i=1;i<=m;++i) {
                int digit = now % 4;
                now /= 4;
                if(digit != lastDigit) {
                    if(lastDigit == 3 && cnt % 2 != 0) { ok = 0; break; }
                    if(lastDigit != 0 && cnt == 1) { ok = 0; break; }
                    lastDigit = digit;
                    cnt = 1;
                }
                else ++cnt;
            }
            if(lastDigit == 3 && cnt % 2 != 0) ok = 0;
            else if(lastDigit != 0 && cnt == 1) ok = 0;
            if(ok) s[num++] = i;
        }
        for(register int i=0;i<num;++i) chosable[i].clear();
        for(register int i=0;i<num;++i)
            for(register int j=0;j<num;++j)
                if(valid2(s[i], s[j])) chosable[i].push_back(make_pair(j, count(s[i],s[j])));
        for(register int i=1;i<num;++i) f[0][i] = -250;
        for(register int i=1;i<=n;++i)
            for(register int j=0;j<num;++j) {
                if(!valid(i,s[j])) { f[i][j] = -250; continue; }
                for(register int k=0;k<chosable[j].size();++k) f[i][j] = max(f[i][j], f[i-1][chosable[j][k].first] + chosable[j][k].second);
            }
        int ans = 0;
        for(register int i=0;i<num;++i)
            if(only0and1(s[i])) ans = max(ans, f[n][i]);
        printf("%d\n", ans);
    }
    return 0;
}
