//
//  main.cpp
//  Mokia LUOGU4390
//
//  Created by Ruining Li on 2020/3/29.
//  Copyright © 2020 Ruining Li. All rights reserved.
//

#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
int w, tot, c[2000010];

struct P {
    int typ, id;
    int x, y, c;
}p[200010];
struct Opt {
    int typ;
    int x, y, X, Y, c;
}a[200010];

long long ans[200010];

inline int read() {
    int r = 0; char ch = getchar();
    while(ch>'9' || ch<'0') ch = getchar();
    while(ch>='0' && ch<='9') r = (r<<3)+(r<<1)+ch-'0', ch = getchar();
    return r;
}

inline bool cmp(P x, P y) {
    return x.x < y.x || (x.x == y.x && x.y < y.y) || (x.x == y.x && x.y == y.y && x.typ == 0 && y.typ != 0);
}

inline int lowerbit(int x) {
    return x & (-x);
}
inline void add(int y, int val) {
    while(y<=w) {
        c[y] += val;
        y += lowerbit(y);
    }
}
inline int sum(int y) {
    int r = 0;
    while(y) {
        r += c[y];
        y -= lowerbit(y);
    }
    return r;
}
inline void work(int num) {
    for(register int i=1;i<=num;++i) {
        if(p[i].typ == 0) add(p[i].y, p[i].c);
        else ans[p[i].id] += p[i].typ * (long long)sum(p[i].y);
    }
    for(register int i=1;i<=num;++i)
        if(p[i].typ == 0) add(p[i].y, -p[i].c);
}

inline void CDQ(int l, int r) {
    int mid = (l+r)>>1;
    if(l < mid) CDQ(l,mid);
    if(mid+1 < r) CDQ(mid+1, r);
    int cnt = 0;
    for(register int i=l;i<=r;++i) {
        if(i<=mid && a[i].typ==1) {
            p[++cnt].x = a[i].x, p[cnt].y = a[i].y, p[cnt].c = a[i].c, p[cnt].typ = 0;
            p[cnt].id = i;
        }
        if(i>mid && a[i].typ==2) {
            p[++cnt].x = a[i].x-1, p[cnt].y = a[i].y-1, p[cnt].typ = 1, p[cnt].id = i;
            p[++cnt].x = a[i].X, p[cnt].y = a[i].y-1, p[cnt].typ = -1, p[cnt].id = i;
            p[++cnt].x = a[i].x-1, p[cnt].y = a[i].Y, p[cnt].typ = -1, p[cnt].id = i;
            p[++cnt].x = a[i].X, p[cnt].y = a[i].Y, p[cnt].typ = 1, p[cnt].id = i;
        }
    }
    sort(p+1,p+cnt+1,cmp);
    work(cnt);
}

int main() {
    int opt;
    while(scanf("%d",&opt)) {
        if(opt == 3) break;
        if(opt == 0) w = read();
        if(opt == 1) {
            a[++tot].x = read(); a[tot].y = read(); a[tot].c = read();
            a[tot].typ = 1;
        }
        if(opt == 2) {
            a[++tot].x = read(); a[tot].y = read(); a[tot].X = read(); a[tot].Y = read();
            a[tot].typ = 2;
        }
    }
    CDQ(1,tot);
    for(register int i=1;i<=tot;++i)
        if(a[i].typ == 2) cout << ans[i] << endl;
    return 0;
}
