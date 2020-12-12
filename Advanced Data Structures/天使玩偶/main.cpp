//
//  main.cpp
//  天使玩偶 LUOGU4169
//
//  Created by Ruining Li on 2020/3/29.
//  Copyright © 2020 Ruining Li. All rights reserved.
//

#pragma GCC optimize(2)
#pragma GCC optimize("inline")
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int n,m,maxy,ans[600010],c[2000010];

inline int read() {
    int r = 0; char ch = getchar();
    while(ch>'9' || ch<'0') ch = getchar();
    while(ch>='0' && ch<='9') r = (r<<3)+(r<<1)+ch-'0', ch = getchar();
    return r;
}
inline void output(int x) {
    if(x > 9) output(x/10);
    putchar('0' + x%10);
}

struct P {
    int t, x, y;
}a[600010], b[600010];

const int INF = (1<<29);

inline int lowerbit(int x) {
    return x & (-x);
}

inline void add(int y, int val) {
    while(y<maxy) {
        c[y] = max(c[y],val);
        y += lowerbit(y);
    }
}

inline void re(int y) {
    while(y<maxy) {
        c[y] = -INF;
        y += lowerbit(y);
    }
}

inline int getMax(int y) {
    int r = -INF;
    while(y) {
        r = max(c[y], r);
        y -= lowerbit(y);
    }
    return r;
}

inline bool cmp(P x, P y) {
    return x.x < y.x || (x.x == y.x && x.y < y.y);
}

inline void workLeftDown(int num) {
    for(register int i=1;i<=num;++i) {
        if(a[b[i].t].t == 1) add(b[i].y, b[i].x + b[i].y);
        else ans[b[i].t] = min(ans[b[i].t], b[i].x + b[i].y - getMax(b[i].y));
    }
    for(register int i=1;i<=num;++i)
        if(a[b[i].t].t == 1) re(b[i].y);
}

inline void workRightUp(int num) {
    for(register int i=num;i>0;--i) {
        if(a[b[i].t].t == 1) add(maxy-b[i].y, -b[i].x - b[i].y);
        else ans[b[i].t] = min(ans[b[i].t], -getMax(maxy-b[i].y) - b[i].x - b[i].y);
    }
    for(register int i=num;i>0;--i)
        if(a[b[i].t].t == 1) re(maxy-b[i].y);
}

inline void workLeftUp(int num) {
    for(register int i=1;i<=num;++i) {
        if(a[b[i].t].t == 1) add(maxy-b[i].y, b[i].x - b[i].y);
        else ans[b[i].t] = min(ans[b[i].t], b[i].x - b[i].y - getMax(maxy - b[i].y));
    }
    for(register int i=1;i<=num;++i)
        if(a[b[i].t].t == 1) re(maxy-b[i].y);
}

inline void workRightDown(int num) {
    for(register int i=num;i>0;--i) {
        if(a[b[i].t].t == 1) add(b[i].y, b[i].y - b[i].x);
        else ans[b[i].t] = min(ans[b[i].t], b[i].y - b[i].x - getMax(b[i].y));
    }
    for(register int i=1;i<=num;++i)
        if(a[b[i].t].t == 1) re(b[i].y);
}

inline void CDQ(int l, int r) {
    int mid = (l+r)>>1;
    if(l < mid) CDQ(l, mid);
    if(mid+1 < r) CDQ(mid+1, r);
    int tot = 0;
    for(register int i=l;i<=r;++i)
        if( (i<=mid && a[i].t==1) || (i>mid && a[i].t==2) ) {
            b[++tot] = a[i];
            b[tot].t = i;
        }
    sort(b+1, b+tot+1, cmp);
    workLeftDown(tot);
    workRightUp(tot);
    workLeftUp(tot);
    workRightDown(tot);
}

int main() {
    n = read(); m = read();
    for(register int i=1;i<=n;++i) {
        a[i].x = read() + 1; a[i].y = read() + 1;
        maxy = max(maxy, a[i].y);
        a[i].t = 1;
    }
    for(register int i=1;i<=m;++i) {
        a[i+n].t = read(); a[i+n].x = read() + 1; a[i+n].y = read() + 1;
        maxy = max(maxy, a[i+n].y);
    }
    ++maxy;
    memset(ans, 0x3f, sizeof(ans));
    memset(c, 0xcf, sizeof(c));
    CDQ(1, m+n);
    for(register int i=n+1;i<=n+m;++i)
        if(a[i].t == 2) {
            output(ans[i]);
            putchar('\n');
        }
    return 0;
}
