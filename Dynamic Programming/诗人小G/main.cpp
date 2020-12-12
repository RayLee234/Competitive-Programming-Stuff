//
//  main.cpp
//  诗人小G LUOGU1912
//
//  Created by Ruining Li on 2020/7/14.
//  Copyright © 2020 Ruining Li. All rights reserved.
//

#include <iostream>
#include <string>
#include <cstring>
#include <cmath>
#include <cstdio>
#define ld long double
using namespace std;
int T, n, l, p, len[100010], sum[100010], c[100010];
pair <int, pair<int,int> > q[300010];
ld f[100010];
inline ld power(ld x, int y) {
    ld base = x, res = 1;
    while(y > 0) {
        if(y & 1) res *= base;
        y >>= 1;
        base *= base;
    }
    return res;
}
inline ld calc(int x, int y) {
    return (ld)f[x] + power(abs(sum[y] - (ld)sum[x] + y - x - 1 - l), p);
}
string s[100010], ans[300010];
int main() {
    scanf("%d", &T);
    while(T--) {
        scanf("%d %d %d", &n, &l, &p);
        for(int i=1;i<=n;++i) cin >> s[i], len[i] = s[i].length(), sum[i] = sum[i-1] + len[i];
        int L = 0, R = -1;
        q[++R] = make_pair(0, make_pair(1,n));
        for(int i=1;i<=n;++i) {
            while(L < R && q[L].second.second < i) ++L;
            q[L].second.first = i;
            c[i] = q[L].first;
            f[i] = calc(q[L].first, i);
            int pos = -1;
            while(L < R && calc(i, q[R].second.first) < calc(q[R].first, q[R].second.first)) pos = q[R--].second.first;
            if(calc(i, q[R].second.second) > calc(q[R].first, q[R].second.second)) {
                if(pos != -1) q[++R] = make_pair(i, make_pair(pos, n));
                continue;
            }
            int x = q[R].second.first, y = q[R].second.second;
            while(x <= y) {
                int mid = (x+y) >> 1;
                if(calc(i, mid) < calc(q[R].first, mid)) pos = mid, y = mid - 1;
                else x = mid + 1;
            }
            if(pos != -1) {
                q[R].second.second = pos - 1;
                q[++R] = make_pair(i, make_pair(pos,n));
            }
        }
        if(f[n] > 1e18) {
            puts("Too hard to arrange");
            puts("--------------------");
            continue;
        }
        printf("%.0LF\n", f[n]);
        int line = 0, cur = n;
        while(cur > 0) {
            ans[++line].clear();
            for(int i=c[cur]+1;i<cur;++i) ans[line] += s[i], ans[line] += ' ';
            ans[line] += s[cur];
            cur = c[cur];
        }
        for(int i=line;i>0;--i) cout << ans[i] << endl;
        puts("--------------------");
    }
    return 0;
}
