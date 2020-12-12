//
//  main.cpp
//  可持久化并查集 LUOGU3402
//
//  Created by Ruining Li on 2020/4/6.
//  Copyright © 2020 Ruining Li. All rights reserved.
//

#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
int n,m,totF,totR;
struct Fa {
    int lc, rc;
    int fa;
}f[5000010];
struct Rank {
    int lc, rc;
    int rank;
}ra[5000010];
inline int read() {
    int r = 0; char c = getchar();
    while(c < '0' || c > '9') c = getchar();
    while(c >= '0' && c <= '9') r = (r<<3)+(r<<1)+c-'0', c = getchar();
    return r;
}
inline int buildFa(int l, int r) {
    int p = ++totF;
    if(l == r) {
        f[p].fa = l;
        return p;
    }
    int mid = (l+r) >> 1;
    f[p].lc = buildFa(l, mid);
    f[p].rc = buildFa(mid+1, r);
    return p;
}
inline int buildRank(int l, int r) {
    int p = ++totR;
    if(l == r) {
        ra[p].rank = 1;
        return p;
    }
    int mid = (l+r) >> 1;
    ra[p].lc = buildRank(l, mid);
    ra[p].rc = buildRank(mid+1, r);
    return p;
}
inline int getFa(int now, int l, int r, int x) {
    if(l == r) return f[now].fa;
    int mid = (l+r) >> 1;
    if(x <= mid) return getFa(f[now].lc, l, mid, x);
    else return getFa(f[now].rc, mid+1, r, x);
}
inline int getRank(int now, int l, int r, int x) {
    if(l == r) return ra[now].rank;
    int mid = (l+r) >> 1;
    if(x <= mid) return getRank(ra[now].lc, l, mid, x);
    else return getRank(ra[now].rc, mid+1, r, x);
}
inline int changeFa(int now, int l, int r, int x, int val) {
    int p = ++totF;
    f[p] = f[now];
    if(l == r) {
        f[p].fa = val;
        return p;
    }
    int mid = (l+r) >> 1;
    if(x <= mid) f[p].lc = changeFa(f[now].lc, l, mid, x, val);
    else f[p].rc = changeFa(f[now].rc, mid+1, r, x, val);
    return p;
}
inline int changeRank(int now, int l, int r, int x, int val) {
    int p = ++totR;
    ra[p] = ra[now];
    if(l == r) {
        ra[p].rank = val;
        return p;
    }
    int mid = (l+r) >> 1;
    if(x <= mid) ra[p].lc = changeRank(ra[now].lc, l, mid, x, val);
    else ra[p].rc = changeRank(ra[now].rc, mid+1, r, x, val);
    return p;
}
int rootF[200010], rootR[200010];
int store;
int main() {
    n = read(), m = read();
    rootF[0] = buildFa(1, n);
    rootR[0] = buildRank(1, n);
    int nowF = rootF[0], nowR = rootR[0];
    for(register int i=1;i<=m;++i) {
        int opt = read();
        if(opt == 1) {
            int a = read(), b = read();
            int temp = a;
            while( (store = getFa(nowF, 1, n, temp)) != temp ) temp = store;
            int fa = temp;
            temp = b;
            while( (store = getFa(nowF, 1, n, temp)) != temp ) temp = store;
            int fb = temp;
            if(fa == fb) rootF[i] = rootF[i-1], rootR[i] = rootR[i-1];
            else {
                int ra = getRank(nowR, 1, n, fa), rb = getRank(nowR, 1, n, fb);
                if(ra < rb) nowF = rootF[i] = changeFa(nowF, 1, n, fa, fb), rootR[i] = rootR[i-1];
                else if(ra > rb) nowF = rootF[i] = changeFa(nowF, 1, n, fb, fa), rootR[i] = rootR[i-1];
                else nowF = rootF[i] = changeFa(nowF, 1, n, fa, fb), nowR = rootR[i] = changeRank(nowR, 1, n, fb, rb+1);
            }
        }
        else if(opt == 2) {
            int k = read();
            nowF = rootF[i] = rootF[k], nowR = rootR[i] = rootR[k];
        }
        else {
            int a = read(), b = read();
            int temp = a;
            while( (store = getFa(nowF, 1, n, temp)) != temp ) temp = store;
            int fa = temp;
            temp = b;
            while( (store = getFa(nowF, 1, n, temp)) != temp ) temp = store;
            int fb = temp;
            if(fa == fb) puts("1");
            else puts("0");
            rootF[i] = rootF[i-1], rootR[i] = rootR[i-1];
        }
    }
    return 0;
}
