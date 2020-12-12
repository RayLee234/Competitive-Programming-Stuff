//
//  main.cpp
//  K-th Number (Persistent Segment Tree) POJ2104
//
//  Created by Ruining Li on 2020/4/6.
//  Copyright © 2020 Ruining Li. All rights reserved.
//

#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
int n,m,a[200010],x[200010],root[200010],tot;
struct Tree {
    int lc, rc;
    int cnt;
}t[8000010];
int build(int l, int r) {
    int p = ++tot;
    t[p].cnt = 0;
    if(l == r) return p;
    int mid = (l+r) >> 1;
    t[p].lc = build(l, mid);
    t[p].rc = build(mid+1, r);
    return p;
}
int add(int now, int l, int r, int val) {
    int p = ++tot;
    t[p] = t[now];
    if(l == r) {
        t[p].cnt++;
        return p;
    }
    int mid = (l+r) >> 1;
    if(val <= mid) t[p].lc = add(t[now].lc, l, mid, val);
    else t[p].rc = add(t[now].rc, mid+1, r, val);
    t[p].cnt = t[t[p].lc].cnt + t[t[p].rc].cnt;
    return p;
}
int ask(int p, int q, int l, int r, int k) {
    if(l == r) return l;
    int mid = (l+r) >> 1;
    int lcnt = t[t[q].lc].cnt - t[t[p].lc].cnt;
    if(k <= lcnt) return ask(t[p].lc, t[q].lc, l, mid, k);
    else return ask(t[p].rc, t[q].rc, mid+1, r, k-lcnt);
}
int main() {
    scanf("%d %d",&n, &m);
    for(int i=1;i<=n;++i) scanf("%d", &a[i]), x[i] = a[i];
    sort(x+1, x+n+1);
    for(int i=1;i<=n;++i) a[i] = lower_bound(x+1, x+n+1, a[i]) - x;
    root[0] = build(1, n);
    for(int i=1;i<=n;++i) root[i] = add(root[i-1], 1, n, a[i]);
    while(m--) {
        int l, r, k; scanf("%d %d %d", &l, &r, &k);
        printf("%d\n", x[ask(root[l-1], root[r], 1, n, k)]);
    }
    return 0;
}
