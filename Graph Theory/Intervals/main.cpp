//
//  main.cpp
//  Intervals POJ1201
//
//  Created by Ruining Li on 2020/10/6.
//  Copyright © 2020 Ruining Li. All rights reserved.
//

#include <iostream>
#include <vector>
#include <cstring>
#include <queue>
#include <cstdio>
using namespace std;
int n, d[50010], R;
bool v[50010];
vector < pair<int,int> > g[50010];
inline int read() {
    int x = 0; char ch = getchar();
    while(ch < '0' || ch > '9') ch = getchar();
    while(ch >= '0' && ch <= '9') x = (x << 3) + (x << 1) + ch - '0', ch = getchar();
    return x;
}
int main() {
    n = read();
    // Part 1: s[b] - s[a-1] >= c
    for(register int i=1;i<=n;++i) {
        int a = read(), b = read(), c = read();
        ++a, ++b;
        R = max(R, b);
        g[a-1].push_back(make_pair(b, c));
    }
    // Part 2: s[i-1] - s[i] >= -1
    for(register int i=1;i<=R;++i) g[i].push_back(make_pair(i-1, -1));
    // Part 3: s[i] - s[i-1] >= 0
    for(register int i=1;i<=R;++i) g[i-1].push_back(make_pair(i, 0));
    for(register int i=1;i<=R;++i) d[i] = -100;
    queue <int> q;
    v[0] = 1, q.push(0);
    while(!q.empty()) {
        int x = q.front(); q.pop(); v[x] = 0;
        for(register int i=0;i<g[x].size();++i) {
            int y = g[x][i].first, len = g[x][i].second;
            if(d[y] < d[x] + len) {
                d[y] = d[x] + len;
                if(!v[y]) v[y] = 1, q.push(y);
            }
        }
    }
    printf("%d\n", d[R]);
    return 0;
}
