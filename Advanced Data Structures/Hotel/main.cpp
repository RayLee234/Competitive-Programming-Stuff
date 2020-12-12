//
//  main.cpp
//  Hotel POJ3667
//
//  Created by Ruining Li on 2020/4/2.
//  Copyright © 2020 Ruining Li. All rights reserved.
//

#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("inline")
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
int n,m;
struct Tree {
    int l, r;
    int lc, rc, c;
    int mark;
}t[200010];
inline int read() {
    int r = 0; char ch = getchar();
    while(ch < '0' || ch > '9') ch = getchar();
    while(ch >= '0' && ch <= '9') r = (r<<3)+(r<<1)+ch-'0', ch = getchar();
    return r;
}
inline void output(int x) {
    if(x>=10) output(x/10);
    putchar('0' + x % 10);
}
inline void build(int root, int l, int r) {
    t[root].l = l, t[root].r = r, t[root].mark = 0;
    if(l == r) {
        t[root].lc = t[root].rc = t[root].c = 1;
        t[root].mark = 0;
        return;
    }
    int mid = (l+r) >> 1;
    build(root*2, l, mid);
    build(root*2+1, mid+1, r);
    if(t[root*2].lc == t[root*2].r - t[root*2].l + 1) t[root].lc = t[root*2].lc + t[root*2+1].lc;
    else t[root].lc = t[root*2].lc;
    if(t[root*2+1].rc == t[root*2+1].r - t[root*2+1].l + 1) t[root].rc = t[root*2+1].rc + t[root*2].rc;
    else t[root].rc = t[root*2+1].rc;
    t[root].c = max(t[root*2].rc + t[root*2+1].lc, max(t[root*2].c, t[root*2+1].c) );
}
inline void spread(int root) {
    if(t[root].mark == 1) {
        t[root*2].mark = t[root*2+1].mark = 1;
        t[root*2].lc = t[root*2].rc = t[root*2].c = t[root*2].r - t[root*2].l + 1;
        t[root*2+1].lc = t[root*2+1].rc = t[root*2+1].c = t[root*2+1].r - t[root*2+1].l + 1;
        t[root].mark = 0;
    }
    if(t[root].mark == -1) {
        t[root*2].mark = t[root*2+1].mark = -1;
        t[root*2].lc = t[root*2].rc = t[root*2].c = 0;
        t[root*2+1].lc = t[root*2+1].rc = t[root*2+1].c = 0;
        t[root].mark = 0;
    }
}
inline pair<int,pair<int,int> > ask(int root, int l, int r) {
    if(t[root].l >= l && t[root].r <= r) return make_pair(t[root].c, make_pair(t[root].lc, t[root].rc));
    if(t[root].l > r || t[root].r < l) return make_pair(0, make_pair(0,0));
    spread(root);
    pair<int, pair<int,int> > p, q, res;
    p = ask(root*2, l, r);
    q = ask(root*2+1, l, r);
    res.first = max(p.second.second + q.second.first, max(p.first, q.first));
    if(p.second.first == t[root*2].r - t[root*2].l + 1) res.second.first = p.second.first + q.second.first;
    else res.second.first = p.second.first;
    if(q.second.second == t[root*2+1].r - t[root*2+1].l + 1) res.second.second = q.second.second + p.second.second;
    else res.second.second = q.second.second;
    return res;
}
inline void change(int root, int l, int r, int val) {
    if(t[root].l >= l && t[root].r <= r) {
        if(val == 1) {
            t[root].c = t[root].lc = t[root].rc = t[root].r - t[root].l + 1;
            t[root].mark = 1;
        }
        if(val == -1) {
            t[root].c = t[root].lc = t[root].rc = 0;
            t[root].mark = -1;
        }
        return;
    }
    if(t[root].l > r || t[root].r < l) return;
    spread(root);
    change(root*2, l, r, val);
    change(root*2+1, l, r, val);
    if(t[root*2].lc == t[root*2].r - t[root*2].l + 1) t[root].lc = t[root*2].lc + t[root*2+1].lc;
    else t[root].lc = t[root*2].lc;
    if(t[root*2+1].rc == t[root*2+1].r - t[root*2+1].l + 1) t[root].rc = t[root*2+1].rc + t[root*2].rc;
    else t[root].rc = t[root*2+1].rc;
    t[root].c = max(t[root*2].rc + t[root*2+1].lc, max(t[root*2].c, t[root*2+1].c) );
}
int main() {
    n = read(), m = read();
    build(1, 1, n);
    while(m--) {
        int op = read(), x = read();
        if(op == 1) {
            int front = x, rear = n, ans = x-1;
            while(front <= rear) {
                int mid = (front + rear) >> 1;
                int sum = ask(1, 1, mid).first;
                if(sum >= x) ans = mid, rear = mid - 1;
                else front = mid + 1;
            }
            output(ans - x + 1);
            putchar('\n');
            if(ans >= x) change(1, ans-x+1, ans, -1);
        }
        else {
            int y; scanf("%d", &y);
            change(1, x, x+y-1, 1);
        }
    }
    return 0;
}
