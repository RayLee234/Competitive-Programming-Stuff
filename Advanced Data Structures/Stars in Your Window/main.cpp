//
//  main.cpp
//  Stars in Your Window POJ2482
//
//  Created by Ruining Li on 2020/3/25.
//  Copyright © 2020 Ruining Li. All rights reserved.
//

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
unsigned int n,w,h,a[200001],b[200001],c[200001],x1[200001],x2[200001],y1[200001],y2[200001],cnt,y[400001];
struct line {
    unsigned int x, bottom, top;
    int c;
}s[400001];
bool cmp(line x, line y) {
    return (x.x < y.x) || (x.x==y.x && x.c>y.c);
}
struct tree {
    unsigned int l, r;
    long long v, mark;
}t[1600001];
void build(int p, unsigned int l, int r) {
    t[p].l = l; t[p].r = r; t[p].v = t[p].mark = 0;
    if(l==r) return;
    int mid = (l+r)>>1;
    build(p*2,l,mid);
    build(p*2+1,mid+1,r);
}
void spread(int p) {
    if(t[p].mark!=0) {
        t[p*2].v += t[p].mark;
        t[p*2+1].v += t[p].mark;
        t[p*2].mark += t[p].mark;
        t[p*2+1].mark += t[p].mark;
        t[p].mark = 0;
    }
}
void add(int p, int l, int r, int val) {
    if(t[p].l>=l && t[p].r<=r) {
        t[p].v += val;
        t[p].mark += val;
        return;
    }
    if(t[p].l>r || t[p].r<l) return;
    spread(p);
    add(p*2,l,r,val);
    add(p*2+1,l,r,val);
    t[p].v = max(t[p*2].v,t[p*2+1].v);
}
int main() {
    while(scanf("%d%d%d",&n,&w,&h)!=EOF) {
        long long ans = 0;
        cnt = 0;
        for(int i=1;i<=n;i++) {
            scanf("%d%d%d",&a[i],&b[i],&c[i]);
            x1[i] = a[i]; y1[i] = b[i];
            x2[i] = a[i]+w-1; y2[i] = b[i]+h-1;
            y[++cnt] = y1[i]; y[++cnt] = y2[i];
        }
        if(w==0 || h==0) {
            puts("0");
            continue;
        }
        sort(y+1,y+cnt+1);
        cnt = unique(y+1,y+cnt+1) - (y+1);
        for(int i=1;i<=n;i++) {
            y1[i] = lower_bound(y+1, y+cnt+1, y1[i]) - y;
            y2[i] = lower_bound(y+1, y+cnt+1, y2[i]) - y;
            s[i*2-1].x = x1[i]; s[i*2-1].bottom = y1[i]; s[i*2-1].top = y2[i]; s[i*2-1].c = c[i];
            s[i*2].x = x2[i]; s[i*2].bottom = y1[i]; s[i*2].top = y2[i]; s[i*2].c = -c[i];
        }
        n *= 2;
        sort(s+1,s+n+1,cmp);
        build(1,1,cnt);
        for(int i=1;i<n;i++) {
            add(1,s[i].bottom,s[i].top,s[i].c);
            ans = max(ans,t[1].v);
        }
        printf("%lld\n",ans);
    }
    return 0;
}
