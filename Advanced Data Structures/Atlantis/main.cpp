//
//  main.cpp
//  Atlantis POJ1151
//
//  Created by Ruining Li on 2020/3/25.
//  Copyright © 2020 Ruining Li. All rights reserved.
//

#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
int n,cnt,T;
double x_1[101],x_2[101],y_1[101],y_2[101],y[201];
struct line {
    double x;
    int bottom, top, c;
}s[201];
bool cmp(line x, line y) {
    return x.x < y.x;
}
struct tree {
    int l,r;
    int cnt;
}t[400001];
void build(int p, int l, int r) {
    t[p].l = l; t[p].r = r; t[p].cnt = 0;
    if(l==r) return;
    int mid = (l+r)/2;
    build(p*2,l,mid);
    build(p*2+1,mid+1,r);
}
void add(int p, int l, int r, int v) {
    if(t[p].l>=l && t[p].r<=r) {
        t[p].cnt += v;
        return;
    }
    if(t[p].l>r || t[p].r<l) return;
    add(p*2,l,r,v);
    add(p*2+1,l,r,v);
}
double len(int p) {
    if(t[p].cnt>0) return y[t[p].r+1]-y[t[p].l];
    if(t[p].l==t[p].r) return 0;
    return len(p*2)+len(p*2+1);
}
int main() {
    while(scanf("%d",&n) && n) {
        cnt = 0;
        double ans = 0;
        for(int i=1;i<=n;i++) {
            cin >> x_1[i] >> y_1[i] >> x_2[i] >> y_2[i];
            y[++cnt] = y_1[i]; y[++cnt] = y_2[i];
        }
        sort(y+1,y+cnt+1);
        cnt = unique(y+1, y+cnt+1) - (y+1);
        for(int i=1;i<=n;i++) y_1[i] = lower_bound(y+1, y+cnt+1, y_1[i]) - y, y_2[i] = lower_bound(y+1, y+cnt+1, y_2[i]) - y;
        build(1,1,cnt-1);
        for(int i=1;i<=n;i++) {
            s[2*i-1].x = x_1[i]; s[2*i-1].bottom = y_1[i]; s[2*i-1].top = y_2[i]; s[2*i-1].c = 1;
            s[2*i].x = x_2[i]; s[2*i].bottom = y_1[i]; s[2*i].top = y_2[i]; s[2*i].c = -1;
        }
        n *= 2;
        sort(s+1,s+n+1,cmp);
        for(int i=1;i<n;i++) {
            add(1,s[i].bottom,s[i].top-1,s[i].c);
            ans += len(1) * (s[i+1].x - s[i].x);
        }
        printf("Test case #%d\nTotal explored area: %.2f\n\n", ++T, ans);
    }
    return 0;
}
