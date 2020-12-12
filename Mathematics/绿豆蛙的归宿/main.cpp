//
//  main.cpp
//  绿豆蛙的归宿 CH3802
//
//  Created by Ruining Li on 2020/3/18.
//  Copyright © 2020 Ruining Li. All rights reserved.
//

#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
using namespace std;
inline int read() {
    int r = 0; char c = getchar();
    while(c<'0' || c>'9') c = getchar();
    while(c>='0' && c<='9') r = (r<<3)+(r<<1)+c-'0', c = getchar();
    return r;
}
int n,m,in[100001],out[100001],topo[100001];
long double s[100001];
vector <int> g[100001];
vector < pair<int,int> > f[100001];
int main() {
    n = read(); m = read();
    for(int i=1;i<=m;i++) {
        int a = read(), b = read(), c = read();
        out[a]++; in[b]++;
        g[a].push_back(b);
        f[b].push_back(make_pair(a,c));
    }
    queue <int> q;
    q.push(1);
    int cur = 0;
    while(!q.empty()) {
        int x = q.front(); topo[++cur] = x; q.pop();
        for(int i=0;i<g[x].size();i++) {
            int y = g[x][i];
            if(--in[y]==0) q.push(y);
        }
    }
    for(int i=n;i>0;i--) {
        int x = topo[i];
        for(int j=0;j<f[x].size();j++) {
            int y = f[x][j].first, len = f[x][j].second;
            s[y] += (long double)(s[x]+len)/out[y];
        }
    }
    long double ans = (long long)(s[1]*100+0.5)/100.0;
    printf("%.2Lf\n",ans);
    return 0;
}
