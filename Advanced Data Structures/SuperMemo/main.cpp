//
//  main.cpp
//  SuperMemo POJ3580
//
//  Created by Ruining Li on 2020/4/8.
//  Copyright © 2020 Ruining Li. All rights reserved.
//

#include <iostream>
#include <cstdio>
using namespace std;
int n,m,s[100010],root,tot;
const int INF = 2147483647;
struct tree {
    int lc, rc, fa;
    int size, val, mark, add, minV;
}a[200010];
void pushdown(int x) {
    if(a[x].mark) {
        swap(a[x].lc, a[x].rc);
        if(a[x].lc) a[a[x].lc].mark ^= 1;
        if(a[x].rc) a[a[x].rc].mark ^= 1;
        a[x].mark = 0;
    }
    if(a[x].add) {
        if(a[x].lc) a[a[x].lc].add += a[x].add, a[a[x].lc].val += a[x].add, a[a[x].lc].minV += a[x].add;
        if(a[x].rc) a[a[x].rc].add += a[x].add, a[a[x].rc].val += a[x].add, a[a[x].rc].minV += a[x].add;
        a[x].add = 0;
    }
}
void update(int x) {
    a[x].size = a[a[x].lc].size + a[a[x].rc].size + 1;
    a[x].minV = a[x].val;
    if(a[x].lc) a[x].minV = min(a[x].minV, a[a[x].lc].minV);
    if(a[x].rc) a[x].minV = min(a[x].minV, a[a[x].rc].minV);
}
int build(int l, int r, int f) {
    if(l > r) return 0;
    int mid = (l+r) >> 1, p = ++tot;
    a[p].fa = f;
    a[p].val = s[mid];
    a[p].lc = build(l, mid-1, p);
    a[p].rc = build(mid+1, r, p);
    update(p);
    return p;
}
int find(int now, int rank) {
    pushdown(now);
    if(a[a[now].lc].size + 1 == rank) return now;
    if(a[a[now].lc].size >= rank) return find(a[now].lc, rank);
    else return find(a[now].rc, rank - a[a[now].lc].size - 1);
}
void rotate(int x) {
    if(!a[x].fa) return;
    int fx = a[x].fa, ffx = a[fx].fa;
    pushdown(x), pushdown(fx);
    if(a[fx].rc == x) {
        a[fx].rc = a[x].lc;
        a[a[x].lc].fa = fx;
        a[x].lc = fx;
    }
    else {
        a[fx].lc = a[x].rc;
        a[a[x].rc].fa = fx;
        a[x].rc = fx;
    }
    a[fx].fa = x;
    a[x].fa = ffx;
    if(ffx) {
        if(a[ffx].lc == fx) a[ffx].lc = x;
        else a[ffx].rc = x;
    }
    update(fx), update(x);
}
void splay(int x, int f) {
    while(a[x].fa != f) {
        if(a[a[x].fa].fa == f) rotate(x);
        else if(a[a[a[a[x].fa].fa].lc].lc == x || a[a[a[a[x].fa].fa].rc].rc == x) rotate(a[x].fa), rotate(x);
        else rotate(x), rotate(x);
    }
    if(f == 0) root = x;
}
void add(int l, int r, int x) {
    int L = find(root, l), R = find(root, r+2);
    splay(L, 0), splay(R, L);
    if(a[R].lc) a[a[R].lc].add += x, a[a[R].lc].val += x, a[a[R].lc].minV += x;
}
void reverse(int l, int r) {
    int L = find(root, l), R = find(root, r+2);
    splay(L, 0), splay(R, L);
    if(a[R].lc) a[a[R].lc].mark ^= 1;
}
int getMin(int l, int r) {
    int L = find(root, l), R = find(root, r+2);
    splay(L, 0), splay(R, L);
    return a[a[R].lc].minV;
}
void insert(int rank, int x) {
    int now = find(root, rank+1);
    splay(now, 0);
    if(a[now].rc == 0) {
        a[now].rc = ++tot;
        a[tot].fa = now;
        a[tot].val = a[tot].minV = x;
        a[tot].size = 1;
        update(now);
        return;
    }
    now = a[now].rc;
    pushdown(now);
    while(a[now].lc) now = a[now].lc, pushdown(now);
    a[now].lc = ++tot;
    a[tot].fa = now;
    a[tot].val = a[tot].minV = x;
    a[tot].size = 1;
    while(now != root) update(now), now = a[now].fa;
    update(root);
}
void remove(int rank) {
    int now = find(root, rank+1);
    splay(now, 0);
    if(a[now].lc == 0) {
        a[a[now].rc].fa = 0;
        root = a[now].rc;
        return;
    }
    if(a[now].rc == 0) {
        a[a[now].lc].fa = 0;
        root = a[now].lc;
        return;
    }
    now = a[now].rc;
    pushdown(now);
    while(a[now].lc) now = a[now].lc, pushdown(now);
    a[root].val = a[now].val;
    if(now == a[a[now].fa].lc) a[a[now].fa].lc = a[now].rc;
    else a[a[now].fa].rc = a[now].rc;
    if(a[now].rc != 0) a[a[now].rc].fa = a[now].fa;
    now = a[now].fa;
    while(now != root) update(now), now = a[now].fa;
    update(root);
}
void revolve(int w, int x, int y, int z) {
    if(w > x || y > z) return;
    int Y = find(root, y), Z = find(root, z+2);
    splay(Y, 0), splay(Z, Y);
    int temp = a[Z].lc;
    a[Z].lc = 0;
    update(Z), update(Y);
    int W1 = find(root, w), W2 = find(root, w+1);
    splay(W1, 0), splay(W2, W1);
    a[W2].lc = temp, a[temp].fa = W2;
    update(W2), update(W1);
}
int main() {
    scanf("%d",&n);
    s[1] = -INF, s[n+2] = INF;
    for(int i=2;i<=n+1;++i) scanf("%d", &s[i]);
    root = build(1, n+2, 0);
    scanf("%d", &m);
    while(m--) {
        char op[10]; scanf("%s", op);
        if(op[0] == 'A') {
            int x,y,d; scanf("%d %d %d", &x, &y, &d);
            add(x, y, d);
        }
        if(op[0] == 'I') {
            int x,p; scanf("%d %d", &x, &p);
            insert(x,p);
        }
        if(op[0] == 'D') {
            int x; scanf("%d", &x);
            remove(x);
        }
        if(op[0] == 'M') {
            int x,y; scanf("%d %d", &x, &y);
            printf("%d\n", getMin(x, y));
        }
        if(op[0] == 'R' && op[3] == 'E') {
            int x,y; scanf("%d %d", &x, &y);
            reverse(x, y);
        }
        if(op[0] == 'R' && op[3] == 'O') {
            int x,y,t; scanf("%d %d %d", &x, &y, &t);
            int len = y-x+1; t = (t%len+len)%len;
            revolve(x, y-t, y-t+1, y);
        }
    }
}
