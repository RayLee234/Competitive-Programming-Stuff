//
//  main.cpp
//  Telephone Lines POJ3662
//
//  Created by Ruining Li on 2020/8/8.
//  Copyright © 2020 Ruining Li. All rights reserved.
//

#include <iostream>
#include <vector>
#include <cstring>
#include <cstdio>
#include <queue>
using namespace std;
int n, p, k, u[10010], v[10010], len[10010], f[10010], ans = 1e6+1;
vector < pair<int,int> > g[1001];
int main() {
    scanf("%d %d %d", &n, &p, &k);
    for(int i=1;i<=p;++i) scanf("%d %d %d", &u[i], &v[i], &len[i]);
    int l = 0, r = 1e6;
    while(l <= r) {
        int mid = (l+r) >> 1;
        for(int i=1;i<=n;++i) g[i].clear();
        for(int i=1;i<=p;++i)
            if(len[i] > mid) {
                g[u[i]].push_back(make_pair(v[i], 1));
                g[v[i]].push_back(make_pair(u[i], 1));
            }
            else {
                g[u[i]].push_back(make_pair(v[i], 0));
                g[v[i]].push_back(make_pair(u[i], 0));
            }
        // Calculate shortest path:
        deque <int> q;
        memset(f, 15, sizeof(f)); f[1] = 0;
        q.push_front(1);
        while(!q.empty()) {
            int now = q.front(); q.pop_front();
            for(int i=0;i<g[now].size();++i)
                if(f[g[now][i].first] > f[now] + g[now][i].second) {
                    f[g[now][i].first] = f[now] + g[now][i].second;
                    if(g[now][i].second == 0) q.push_front(g[now][i].first);
                    else q.push_back(g[now][i].first);
                }
        }
        if(f[n] <= k) { ans = mid; r = mid-1; }
        else l = mid + 1;
    }
    if(ans > 1e6) puts("-1");
    else printf("%d\n", ans);
    return 0;
}
