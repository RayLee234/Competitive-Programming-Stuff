//
//  main.cpp
//  Picture POJ1177
//
//  Created by Ruining Li on 2020/4/2.
//  Copyright © 2020 Ruining Li. All rights reserved.
//

#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
int n, X1[5000], Y1[5000], X2[5000], Y2[5000];
struct Tree {
    int l, r;
    int cnt, mark;
}s[80010];
struct verticalLine {
    int x, p, q, c;
}a[10000];
bool cmp1(verticalLine x, verticalLine y) {
    return x.x < y.x || (x.x == y.x && x.c > y.c);
}
struct horizontalLine {
    int y, p, q, c;
}b[10000];
bool cmp2(horizontalLine x, horizontalLine y) {
    return x.y < y.y || (x.y == y.y && x.c > y.c);
}
int cnt, ans;
void build(int root, int l, int r) {
    s[root].l = l, s[root].r = r, s[root].cnt = s[root].mark = 0;
    if(l == r) return;
    int mid = (l+r) >> 1;
    build(root*2, l, mid);
    build(root*2+1, mid+1, r);
}
void spread(int root) {
    if(s[root].mark != 0) {
        s[root*2].cnt += s[root].mark;
        s[root*2+1].cnt += s[root].mark;
        s[root*2].mark += s[root].mark;
        s[root*2+1].mark += s[root].mark;
        s[root].mark = 0;
    }
}
int calc(int root) {
    if(s[root].cnt > 0) return 0;
    if(s[root].l == s[root].r && s[root].cnt == 0) return 1;
    spread(root);
    return calc(root*2) + calc(root*2+1);
}
void add(int root, int l, int r, int val) {
    if(s[root].l >= l && s[root].r <= r) {
        s[root].cnt += val;
        s[root].mark += val;
        return;
    }
    if(s[root].l > r || s[root].r < l) return;
    spread(root);
    add(root*2, l, r, val);
    add(root*2+1, l, r, val);
}
int ask(int root, int l, int r) {
    if(s[root].l >= l && s[root].r <= r) return calc(root);
    if(s[root].l > r || s[root].r < l) return 0;
    spread(root);
    return ask(root*2, l, r) + ask(root*2+1, l, r);
}
int main() {
    scanf("%d", &n);
    for(int i=1;i<=n;++i) {
        scanf("%d %d %d %d", &X1[i], &Y1[i], &X2[i], &Y2[i]);
        X1[i] += 10000, X2[i] += 10000, Y1[i] += 10000, Y2[i] += 10000;
    }
    build(1,1,20000);
    for(int i=1;i<=n;++i) {
        a[++cnt].x = X1[i], a[cnt].p = Y1[i], a[cnt].q = Y2[i], a[cnt].c = 1;
        a[++cnt].x = X2[i], a[cnt].p = Y1[i], a[cnt].q = Y2[i], a[cnt].c = -1;
    }
    sort(a+1, a+cnt+1, cmp1);
    for(int i=1;i<=cnt;++i) {
        if(a[i].c == 1) {
            ans += ask(1, a[i].p+1, a[i].q);
            add(1, a[i].p+1, a[i].q, 1);
        }
        else {
            add(1, a[i].p+1, a[i].q, -1);
            ans += ask(1, a[i].p+1, a[i].q);
        }
    }
    build(1,1,20000);
    cnt = 0;
    for(int i=1;i<=n;++i) {
        b[++cnt].y = Y1[i], b[cnt].p = X1[i], b[cnt].q = X2[i], b[cnt].c = 1;
        b[++cnt].y = Y2[i], b[cnt].p = X1[i], b[cnt].q = X2[i], b[cnt].c = -1;
    }
    sort(b+1, b+cnt+1, cmp2);
    for(int i=1;i<=cnt;++i) {
        if(b[i].c == 1) {
            ans += ask(1, b[i].p+1, b[i].q);
            add(1, b[i].p+1, b[i].q, 1);
        }
        else {
            add(1, b[i].p+1, b[i].q, -1);
            ans += ask(1, b[i].p+1, b[i].q);
        }
    }
    printf("%d\n", ans);
    return 0;
}
