//
//  main.cpp
//  Fence Obstacle Course POJ2374
//
//  Created by Ruining Li on 2020/7/21.
//  Copyright © 2020 Ruining Li. All rights reserved.
//

#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
using namespace std;
int n, s, a[50010], b[50010], L[50010], R[50010], f[50010][2], ans = 1e9;
struct tree {
    int l, r, val, mark;
}S[800010];
void build(int root, int l, int r) {
    S[root].l = l, S[root].r = r, S[root].val = S[root].mark = 0;
    if(l == r) return;
    int mid = (l+r) >> 1;
    build(root*2, l, mid);
    build(root*2+1, mid+1, r);
}
void pushdown(int root) {
    if(S[root].mark == 0) return;
    S[root*2].val = S[root*2+1].val = S[root*2].mark = S[root*2+1].mark = S[root].mark;
    S[root].mark = 0;
}
void update(int root, int l, int r, int val) {
    if(S[root].l > r || S[root].r < l) return;
    if(S[root].l >= l && S[root].r <= r) {
        S[root].val = S[root].mark = val;
        return;
    }
    pushdown(root);
    update(root*2, l, r, val);
    update(root*2+1, l, r, val);
    S[root].val = max(S[root*2].val, S[root*2+1].val);
}
int ask(int root, int x) {
    if(S[root].l == x && S[root].r == x) return S[root].val;
    pushdown(root);
    int mid = (S[root].l + S[root].r) >> 1;
    if(mid < x) return ask(root*2+1, x);
    else return ask(root*2, x);
}
int main() {
    scanf("%d %d", &n, &s);
    s += 1e5+1;
    build(1, 1, 200001);
    for(int i=1;i<=n;++i) {
        scanf("%d %d", &a[i], &b[i]);
        a[i] += 1e5+1, b[i] += 1e5+1;
        L[i] = ask(1, a[i]), R[i] = ask(1, b[i]);
        update(1, a[i], b[i], i);
    }
    memset(f, 15, sizeof(f));
    f[n][0] = s - a[n], f[n][1] = b[n] - s;
    for(int i=n;i>1;--i) {
        f[L[i]][0] = min(f[L[i]][0], f[i][0] + abs(a[i]-a[L[i]]) );
        f[L[i]][1] = min(f[L[i]][1], f[i][0] + abs(a[i]-b[L[i]]) );
        f[R[i]][0] = min(f[R[i]][0], f[i][1] + abs(b[i]-a[R[i]]) );
        f[R[i]][1] = min(f[R[i]][1], f[i][1] + abs(b[i]-b[R[i]]) );
    }
    for(int i=1;i<=n;++i) {
        if(L[i] == 0) ans = min(ans, f[i][0]+abs(a[i]-100001) );
        if(R[i] == 0) ans = min(ans, f[i][1]+abs(b[i]-100001) );
    }
    printf("%d\n", ans);
    return 0;
}
