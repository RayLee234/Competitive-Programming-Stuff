//
//  main.cpp
//  Tree POJ1741
//
//  Created by Ruining Li on 2020/3/27.
//  Copyright © 2020 Ruining Li. All rights reserved.
//

#pragma GCC optimize(2)
#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;
int n,k,s[10001],b[10001],d[10001],a[10001],cnt[10001],c,num,ans,tot;
bool v[10001],w[10001];
vector < pair<int,int> > g[10001];
inline int read() {
    int r = 0; char ch = getchar();
    while(ch<'0' || ch>'9') ch = getchar();
    while(ch>='0' && ch<='9') r = (r<<3)+(r<<1)+ch-'0', ch = getchar();
    return r;
}
inline bool cmp(int x, int y) {
    return d[x] < d[y];
}
inline void G(int size, int x) {
    s[x] = 1; v[x] = 1;
    int maxson = 0;
    for(register int i=0;i<g[x].size();++i) {
        int y = g[x][i].first;
        if(v[y] || w[y]) continue;
        G(size, y);
        s[x] += s[y];
        maxson = max(maxson, s[y]);
    }
    maxson = max(maxson, size-s[x]);
    if(maxson < num) {
        num = maxson;
        c = x;
    }
}
inline void init(int x) {
    v[x] = 1;
    for(register int i=0;i<g[x].size();++i) {
        int y = g[x][i].first, len = g[x][i].second;
        if(v[y] || w[y]) continue;
        a[++tot] = y;
        b[y] = b[x];
        d[y] = d[x] + len;
        cnt[b[y]]++;
        init(y);
    }
}
inline void dfs(int size, int x) {
    memset(v, 0, sizeof(v));
    num = size;
    G(size,x);
    memset(cnt, 0, sizeof(cnt));
    memset(d, 0, sizeof(d));
    memset(v, 0, sizeof(v));
    b[c] = c; a[tot = 1] = c; w[c] = 1; cnt[c]++;
    for(register int i=0;i<g[c].size();++i) {
        int y = g[c][i].first, len = g[c][i].second;
        if(v[y] || w[y]) continue;
        d[y] = len;
        a[++tot] = y;
        b[y] = y;
        cnt[b[y]]++;
        init(y);
    }
    sort(a+1,a+tot+1,cmp);
    int l = 1, r = tot;
    --cnt[b[a[l]]];
    while(l<r) {
        while(d[a[l]]+d[a[r]] > k) {
            --cnt[b[a[r]]];
            r--;
        }
        ans += r-l-cnt[b[a[l]]];
        --cnt[b[a[l+1]]];
        l++;
    }
    int now = c;
    for(register int i=0;i<g[now].size();++i) {
        int y = g[now][i].first;
        if(w[y]) continue;
        dfs(s[y],y);
    }
}
int main() {
    while(scanf("%d%d",&n,&k) && n && k) {
        ans = 0;
        for(register int i=1;i<=n;++i) g[i].clear();
        memset(w, 0, sizeof(w));
        for(register int i=1;i<n;++i) {
            int u = read(), v = read(), l = read();
            g[u].push_back(make_pair(v,l));
            g[v].push_back(make_pair(u,l));
        }
        dfs(n,1);
        printf("%d\n",ans);
    }
    return 0;
}
