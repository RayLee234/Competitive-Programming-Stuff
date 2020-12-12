//
//  main.cpp
//  Parity game POJ1733
//
//  Created by Ruining Li on 2020/3/24.
//  Copyright © 2020 Ruining Li. All rights reserved.
//

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
int n,m,l[5001],r[5001],a[10001],f[10001],d[10001],t;
bool ans[5001]; // 0: even; 1: odd
int find(int x) {
    if(f[x]==x) return x;
    int y = find(f[x]);
    d[x] ^= d[f[x]];
    return f[x] = y;
}
int main() {
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;++i) {
        char temp[5];
        scanf("%d%d%s",&l[i],&r[i],temp);
        a[++t] = l[i]-1; a[++t] = r[i];
        if(temp[0]=='o') ans[i] = 1;
    }
    sort(a+1,a+t+1);
    n = unique(a+1,a+t+1) - (a+1);
    for(int i=1;i<=n;i++) f[i] = i;
    int i;
    for(i=1;i<=m;++i) {
        int x = lower_bound(a+1,a+n+1,l[i]-1) - a, y = lower_bound(a+1,a+n+1,r[i]) - a;
        int fx = find(x), fy = find(y);
        if(fx==fy && (d[x]^d[y])!=ans[i]) break;
        if(fx!=fy) f[fx] = fy, d[fx] = d[x] ^ d[y] ^ ans[i];
    }
    cout << i-1 << endl;
    return 0;
}
