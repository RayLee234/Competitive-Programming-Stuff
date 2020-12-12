//
//  main.cpp
//  Sightseeing Cows POJ3621
//
//  Created by Ruining Li on 2020/9/25.
//  Copyright © 2020 Ruining Li. All rights reserved.
//

#include <iostream>
#include <vector>
#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;
int l, p, m, u[5001], v[5001], D[1001][1001], cnt[1001];
bool jud[1001];
double f[1001], t[5001], ans, L, R = 1000, d[1001];
vector < pair<int,int> > g[1001];
bool SPFA(double mid) {
    for(int i=1;i<=l;++i) cnt[i] = 0, d[i] = 1e7;
    memset(jud, 0, sizeof(jud));
    priority_queue < pair<int,int>, vector < pair<int,int> >, greater < pair<int,int> > > q;
    for(int i=1;i<=l;++i)
        if(!jud[i]) {
            d[i] = 0;
            q.push(make_pair(d[1], 1));
            while(!q.empty()) {
                int x = q.top().second; jud[x] = 1; q.pop();
                if(cnt[x] > l) return 1;
                for(int i=0;i<g[x].size();++i) {
                    int y = g[x][i].first;
                    double len = mid * g[x][i].second - f[x];
                    if(d[y] > d[x] + len) {
                        d[y] = d[x] + len, cnt[y] = cnt[x] + 1;
                        q.push(make_pair(d[y], y));
                    }
                }
            }
        }
    return 0;
}
int main() {
    memset(D, 15, sizeof(D));
    cin >> l >> p;
    for(int i=1;i<=l;++i) cin >> f[i];
    for(int i=1;i<=p;++i) {
        int x, y, z; cin >> x >> y >> z;
        if(D[x][y] > z) D[x][y] = z;
    }
    for(int i=1;i<=l;++i)
        for(int j=1;j<=l;++j)
            if(D[i][j] <= 1000) g[i].push_back(make_pair(j,D[i][j]));
    while(R - L >= 1e-5) {
        double mid = (L + R) / 2;
        if(SPFA(mid)) { ans = mid; L = mid; }
        else R = mid;
    }
    if(ans == 0) puts("0");
    else printf("%.2f\n", ans);
    return 0;
}
