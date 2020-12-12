//
//  main.cpp
//  Cleaning Shifts POJ2376
//
//  Created by Ruining Li on 2020/6/26.
//  Copyright © 2020 Ruining Li. All rights reserved.
//


/*
// DP + Segment Tree AC_735ms
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;
int n, t, l[25010], r[25010], s[25010], f[1000010];
const int inf = 252645135;
struct tree {
    int l, r;
    int minV;
}a[4000010];
void build(int root, int ll, int rr) {
    a[root].l = ll, a[root].r = rr;
    if(ll == rr) {
        a[root].minV = f[ll];
        return;
    }
    int mid = (ll + rr) >> 1;
    build(root*2, ll, mid);
    build(root*2+1, mid+1, rr);
    a[root].minV = min(a[root*2].minV, a[root*2+1].minV);
}
void modify(int root, int x, int v) {
    if(a[root].l > x || a[root].r < x) return;
    if(a[root].l == x && a[root].r == x) {
        a[root].minV = v;
        return;
    }
    modify(root*2, x, v);
    modify(root*2+1, x, v);
    a[root].minV = min(a[root*2].minV, a[root*2+1].minV);
}
int ask(int root, int ll, int rr) {
    if(a[root].l > rr || a[root].r < ll) return inf;
    if(a[root].l >= ll && a[root].r <= rr) return a[root].minV;
    return min(ask(root*2, ll, rr), ask(root*2+1, ll, rr));
}
bool cmp(int x, int y) {
    return r[x] < r[y];
}
int main() {
    cin >> n >> t;
    for(int i=1;i<=n;++i) {
        cin >> l[i] >> r[i];
        r[i] = min(r[i], t);
        s[i] = i;
    }
    sort(s+1, s+n+1, cmp);
    memset(f, 15, sizeof(f));
    f[0] = 0;
    build(1, 0, t);
    for(int i=1;i<=n;++i) {
        f[r[s[i]]] = min(f[r[s[i]]], ask(1, l[s[i]]-1, r[s[i]]-1) + 1);
        modify(1, r[s[i]], f[r[s[i]]]);
    }
    if(f[t] <= 1e6) cout << f[t] << endl;
    else cout << -1 << endl;
    return 0;
}
 */

// Greedy Algorithm AC_360ms
#include <iostream>
#include <algorithm>
using namespace std;
int n, t, minL[25010];
struct cow {
    int l, r;
}a[25010];
bool cmp(cow x, cow y) {
    return x.r < y.r;
}
int main() {
    cin >> n >> t;
    for(int i=1;i<=n;++i) cin >> a[i].l >> a[i].r, a[i].r = min(a[i].r, t);
    sort(a+1, a+n+1, cmp);
    minL[n+1] = 1e9;
    for(int i=n;i>0;--i) minL[i] = min(minL[i+1], a[i].l);
    int cur = 0, cow = 1, cnt = 0;
    while(cur < t) {
        if(minL[cow] > cur + 1) {
            puts("-1");
            return 0;
        }
        while(minL[cow+1] <= cur+1) ++cow;
        cur = a[cow++].r;
        cnt++;
    }
    cout << cnt << endl;
    return 0;
}
