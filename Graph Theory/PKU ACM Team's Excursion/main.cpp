//
//  main.cpp
//  PKU ACM Team's Excursion CH6703
//
//  Created by Ruining Li on 2020/10/9.
//  Copyright © 2020 Ruining Li. All rights reserved.
//

#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
using namespace std;
const int P = 1e9 + 7;
int T, n, m, s, t, q, in[100000], rin[100000], fs[100000], ft[100000], d[100000], pre[100000], preD[100000];
int fw[100000], bw[100000];
inline int read() {
    int x = 0; char ch = getchar();
    while(ch > '9' || ch < '0') ch = getchar();
    while(ch >= '0' && ch <= '9') x = (x << 3) + (x << 1) + ch - '0', ch = getchar();
    return x;
}
queue <int> Q;
vector < pair<int,int> > g[100000];
vector <int> rg[100000], path;
int main() {
    T = read();
    while(T--) {
        memset(fw, 0, sizeof(fw)), memset(bw, 0, sizeof(bw)), memset(in, 0, sizeof(in)), memset(rin, 0, sizeof(rin));
        n = read(), m = read(), s = read(), t = read(), q = read();
        for(int i=0;i<n;++i) g[i].clear(), rg[i].clear(), fs[i] = ft[i] = 0, d[i] = P;
        for(int i=1;i<=m;++i) {
            int x = read(), y = read(), z = read();
            g[x].push_back(make_pair(y, z)), rg[y].push_back(x);
            ++in[y], ++rin[x];
        }
        fs[s] = 1, d[s] = 0;
        for(int i=0;i<n;++i) if(!in[i]) Q.push(i);
        while(Q.size()) {
            int x = Q.front(); Q.pop();
            for(int i=0;i<g[x].size();++i) {
                int y = g[x][i].first, dis = g[x][i].second;
                (fs[y] += fs[x]) %= P;
                if(d[y] > d[x] + dis) d[y] = d[x] + dis, pre[y] = x, preD[y] = dis;
                if(!--in[y]) Q.push(y);
            }
        }
        if(d[t] > 1e9) { cout << -1 << endl; continue; }
        ft[t] = 1;
        for(int i=0;i<n;++i) if(!rin[i]) Q.push(i);
        while(Q.size()) {
            int x = Q.front(); Q.pop();
            for(int i=0;i<rg[x].size();++i) {
                int y = rg[x][i];
                (ft[y] += ft[x]) %= P;
                if(!--rin[y]) Q.push(y);
            }
        }
        path.clear();
        int cur = t;
        while(cur != s) {
            path.push_back(cur);
            cur = pre[cur];
        }
        path.push_back(s);
        int ans = 0;
        for(int i=0;i<path.size()-1;++i) if((long long)fs[path[i+1]] * ft[path[i]] % P == fs[t]) ans += preD[path[i]];
        int L1 = 0, L2 = 0, p = path.size()-1;
        for(int i = path.size()-2;i>0;--i) {
            fw[i] = fw[i+1];
            int y = path[i], x = pre[y];
            bool danger = ((long long)fs[x] * ft[y] % P == fs[t]);
            if(danger) L1 += preD[y];
            else L2 += preD[y];
            while(L1 + L2 > q) {
                --p;
                bool flag = ((long long)fs[path[p+1]] * ft[path[p]] % P == fs[t]);
                if(flag) L1 -= preD[path[p]];
                else L2 -= preD[path[p]];
            }
            if(L1 + L2 == q || p == path.size() - 1) fw[i] = max(fw[i], L1);
            else {
                if((long long)fs[path[p+1]] * ft[path[p]] % P == fs[t]) fw[i] = max(fw[i], q - L2);
                else fw[i] = max(fw[i], L1);
            }
        }
        L1 = L2 = 0, p = 0;
        for(int i=1;i<path.size()-1;++i) {
            bw[i] = bw[i-1];
            int y = path[i-1], x = pre[y];
            bool danger = ((long long)fs[x] * ft[y] % P == fs[t]);
            if(danger) L1 += preD[y];
            else L2 += preD[y];
            while(L1 + L2 > q) {
                ++p;
                bool flag = ((long long)fs[path[p]] * ft[path[p-1]] % P == fs[t]);
                if(flag) L1 -= preD[path[p-1]];
                else L2 -= preD[path[p-1]];
            }
            if(L1 + L2 == q || p == 0) bw[i] = max(bw[i], L1);
            else {
                if((long long)fs[path[p]] * ft[path[p-1]] % P == fs[t]) bw[i] = max(bw[i], q - L2);
                else bw[i] = max(bw[i], L1);
            }
        }
        int reduce = 0;
        for(int i=1;i<path.size()-1;++i) reduce = max(reduce, fw[i] + bw[i]);
        printf("%d\n", ans - reduce);
    }
}
