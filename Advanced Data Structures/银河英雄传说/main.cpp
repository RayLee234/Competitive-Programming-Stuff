//
//  main.cpp
//  银河英雄传说 LUOGU1196
//
//  Created by Ruining Li on 2020/3/24.
//  Copyright © 2020 Ruining Li. All rights reserved.
//

#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
using namespace std;
int T,f[30001],d[30001],s[30001];
int find(int x) {
    if(f[x]==x) return x;
    int y = find(f[x]);
    d[x] += d[f[x]];
    return f[x] = y;
}
void merge(int x, int y) {
    int fx = find(x), fy = find(y); // x-->y
    d[fx] = s[fy];
    f[fx] = fy;
    s[fy] += s[fx];
}
int main() {
    for(int i=1;i<=30000;i++) f[i] = i, s[i] = 1;
    scanf("%d",&T);
    while(T--) {
        char c; int x,y;
        cin >> c >> x >> y;
        if(c=='M') merge(x,y);
        else {
            int fx = find(x), fy = find(y);
            if(fx!=fy) puts("-1");
            else printf("%d\n",abs(d[x]-d[y])-1);
        }
    }
    return 0;
}
