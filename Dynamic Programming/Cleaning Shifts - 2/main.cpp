//
//  main.cpp
//  Cleaning Shifts - 2 LUOGU4644
//
//  Created by Ruining Li on 2020/6/27.
//  Copyright © 2020 Ruining Li. All rights reserved.
//

#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#define LL long long
using namespace std;
int n, s, t, l[10010], r[10010], p[10010], a[10010];
LL f[100000];
const int inf = 5e10;
bool cmp(int x, int y) {
    return r[x] < r[y];
}
struct tree {
    int l, r;
    LL minV;
}S[400000];
void build(int root, int ll, int rr) {
    S[root].l = ll, S[root].r = rr;
    if(ll == rr) {
        S[root].minV = f[ll];
        return;
    }
    int mid = (ll + rr) >> 1;
    build(root*2, ll, mid);
    build(root*2+1, mid+1, rr);
    S[root].minV = min(S[root*2].minV, S[root*2+1].minV);
}
void modify(int root, int x, LL v) {
    if(S[root].l > x || S[root].r < x) return;
    if(S[root].l == x && S[root].r == x) {
        S[root].minV = v;
        return;
    }
    modify(root*2, x, v);
    modify(root*2+1, x, v);
    S[root].minV = min(S[root*2].minV, S[root*2+1].minV);
}
LL ask(int root, int ll, int rr) {
    if(S[root].l > rr || S[root].r < ll) return inf;
    if(S[root].l >= ll && S[root].r <= rr) return S[root].minV;
    return min(ask(root*2, ll, rr), ask(root*2+1, ll, rr));
}
int main() {
    cin >> n >> s >> t;
    for(int i=1;i<=n;++i) cin >> l[i] >> r[i] >> p[i], l[i] = max(l[i], s) + 1, r[i] = min(r[i], t) + 1, a[i] = i;
    ++s, ++t;
    sort(a+1, a+n+1, cmp);
    memset(f, 15, sizeof(f));
    f[s-1] = 0;
    build(1, s-1, t);
    for(int i=1;i<=n;++i) {
        f[r[a[i]]] = min(f[r[a[i]]], ask(1, l[a[i]]-1, r[a[i]]-1) + p[a[i]]);
        modify(1, r[a[i]], f[r[a[i]]]);
    }
    if(f[t] <= 5e8) cout << f[t] << endl;
    else puts("-1");
    return 0;
}
