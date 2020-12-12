//
//  main.cpp
//  疫情控制 LUOGU1084
//
//  Created by Ruining Li on 2020/9/20.
//  Copyright © 2020 Ruining Li. All rights reserved.
//

#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
#define int long long
using namespace std;
int n, m, sum, ans = -1, pos[50010], f[50010][17], d[50010][17], v[50010], hasSoldier[50010], minRestIdx[50010];
vector < pair<int,int> > g[50010];
struct soldier {
    int idx, s, rest;
    bool valid;
};
vector <soldier> S;
vector < pair<int,int> > H;
void dfs(int x) {
    v[x] = 1;
    for(int i=0;i<g[x].size();++i) {
        int y = g[x][i].first, dis = g[x][i].second;
        if(v[y]) continue;
        f[y][0] = x, d[y][0] = dis;
        for(int j=1;j<17;++j) f[y][j] = f[f[y][j-1]][j-1], d[y][j] = d[y][j-1] + d[f[y][j-1]][j-1];
        dfs(y);
    }
}
void dfs2(int x) {
    v[x] = hasSoldier[x];
    bool ok = 1;
    for(int i=0;i<g[x].size();++i) {
        int y = g[x][i].first;
        if(v[y] >= 0) continue;
        dfs2(y);
        if(v[y] != 1) ok = 0;
    }
    if((g[x].size() > 1 || x == 1) && v[x] == 0 && ok) v[x] = 1;
}
pair<int,int> highest(int x, int dis) {
    for(int i=16;i>=0;--i)
        if(f[x][i] != 1 && f[x][i] != 0 && d[x][i] <= dis) { dis -= d[x][i]; x = f[x][i]; }
    return make_pair(x, dis);
}
bool cmp1(soldier x, soldier y) {
    return x.rest - d[x.s][0] < y.rest - d[y.s][0];
}
bool cmp2(pair<int,int> x, pair<int,int> y) {
    return d[x.first][0] < d[y.first][0];
}
bool valid(int x) {
    memset(hasSoldier, 0, sizeof(hasSoldier));
    S.clear(), H.clear();
    for(int i=1;i<=m;++i) {
        int position = highest(pos[i], x).first, restDis = highest(pos[i], x).second;
        if(d[position][0] > restDis) hasSoldier[position] = 1;
        else {
            soldier cur; cur.idx = i, cur.s = position, cur.rest = restDis, cur.valid = 1;
            S.push_back(cur);
        }
    }
    memset(v, -1, sizeof(v));
    memset(minRestIdx, -1, sizeof(minRestIdx));
    dfs2(1);
    for(int i=0;i<g[1].size();++i)
        if(v[g[1][i].first] != 1) H.push_back(make_pair(g[1][i].first, 1));
    for(int i=0;i<S.size();++i)
        if(minRestIdx[S[i].s] == -1 || S[minRestIdx[S[i].s]].rest > S[i].rest) minRestIdx[S[i].s] = i;
    for(int i=0;i<H.size();++i)
        if(minRestIdx[H[i].first] != -1 && S[minRestIdx[H[i].first]].rest <= 2 * d[H[i].first][0]) H[i].second = 0, S[minRestIdx[H[i].first]].valid = 0;
    sort(S.begin(), S.end(), cmp1);
    sort(H.begin(), H.end(), cmp2);
    int ps = 0, ph = 0; bool ok = 0;
    while(ps < S.size()) {
        while(ph < H.size() && !H[ph].second) ++ph;
        if(ph >= H.size()) { ok = 1; break; }
        if(!S[ps].valid) { ++ps; continue; }
        if(S[ps].rest - d[S[ps].s][0] >= d[H[ph].first][0]) {
            ++ps; ++ph;
            while(ph < H.size() && !H[ph].second) ++ph;
            if(ph >= H.size()) { ok = 1; break; }
            continue;
        }
        ++ps;
    }
    return ok;
}
signed main() {
    cin >> n;
    for(int i=1;i<n;++i) {
        int x, y, z; cin >> x >> y >> z;
        g[x].push_back(make_pair(y, z)), g[y].push_back(make_pair(x, z));
        sum += z;
    }
    cin >> m;
    for(int i=1;i<=m;++i) cin >> pos[i];
    dfs(1);
    int l = 0, r = sum;
    while(l <= r) {
        int mid = (l + r) >> 1;
        if(valid(mid)) ans = mid, r = mid - 1;
        else l = mid + 1;
    }
    cout << ans << endl;
    return 0;
}
