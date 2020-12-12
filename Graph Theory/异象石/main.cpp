//
//  main.cpp
//  异象石 CH#56C
//
//  Created by Ruining Li on 2020/9/20.
//  Copyright © 2020 Ruining Li. All rights reserved.
//

#include <iostream>
#include <vector>
#include <set>
#include <queue>
#define int long long
using namespace std;
int n, m, d[100010], dep[100010], f[100010][20], t[100010], v[100010], cur, ans;
vector < pair<int,int> > g[100010];
set < pair<int,int> > s;
set < pair<int,int> >::iterator it;
queue <int> q;
void dfs(int x) {
    t[x] = ++cur;
    for(int i=0;i<g[x].size();++i) {
        int y = g[x][i].first, dis = g[x][i].second;
        if(dep[y] > 0) continue;
        dep[y] = dep[x] + 1;
        d[y] = d[x] + dis;
        f[y][0] = x;
        for(int j=1;j<20;++j) f[y][j] = f[f[y][j-1]][j-1];
        dfs(y);
    }
}
int lca(int x, int y) {
    if(dep[x] < dep[y]) swap(x, y);
    for(int i=19;i>=0;--i)
        if(dep[f[x][i]] >= dep[y]) x = f[x][i];
    if(x == y) return x;
    for(int i=19;i>=0;--i)
        if(f[x][i] != f[y][i]) { x = f[x][i]; y = f[y][i]; }
    return f[x][0];
}
int dist(int x, int y) {
    return d[x] + d[y] - 2 * d[lca(x,y)];
}
signed main() {
    cin >> n;
    for(int i=1;i<n;++i) {
        int x, y, z; cin >> x >> y >> z;
        g[x].push_back(make_pair(y, z)), g[y].push_back(make_pair(x, z));
    }
    dep[1] = 1;
    dfs(1);
    cin >> m;
    while(m--) {
        char ch; cin >> ch;
        if(ch == '?') cout << ans / 2 << endl;
        else if(ch == '+') {
            int x; cin >> x;
            if(s.size() == 0) s.insert(make_pair(t[x], x));
            else if(s.size() == 1) {
                it = s.begin();
                int y = (*it).second;
                ans += 2 * dist(x, y);
                s.insert(make_pair(t[x], x));
            }
            else {
                int a, b;
                it = s.upper_bound(make_pair(t[x], x));
                if(it == s.end() || it == s.begin()) {
                    it = s.end(); it--;
                    a = (*s.begin()).second, b = (*it).second;
                }
                else {
                    a = (*it).second; it--;
                    b = (*it).second;
                }
                ans -= dist(a, b);
                ans += dist(a, x), ans += dist(b, x);
                s.insert(make_pair(t[x], x));
            }
        }
        else {
            int x; cin >> x;
            if(s.size() <= 2) ans = 0, s.erase(s.find(make_pair(t[x], x)));
            else {
                int a, b;
                it = s.find(make_pair(t[x], x));
                if(it == s.begin()) {
                    it++; a = (*it).second;
                    it = s.end(); it--; b = (*it).second;
                }
                else {
                    it--; a = (*it).second;
                    it++; it++;
                    if(it == s.end()) it = s.begin();
                    b = (*it).second;
                }
                ans -= dist(x, a), ans -= dist(x, b);
                ans += dist(a, b);
                s.erase(s.find(make_pair(t[x], x)));
            }
        }
    }
    return 0;
}
