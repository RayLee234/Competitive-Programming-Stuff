//
//  main.cpp
//  普通平衡树 LUOGU3369
//
//  Created by Ruining Li on 2020/3/28.
//  Copyright © 2020 Ruining Li. All rights reserved.
//

#include <iostream>
#include <cstdio>
#include <stdlib.h>
using namespace std;
int n;
struct Treap {
    int l, r;
    int val, dat;
    int cnt, size;
}a[100010];

int tot, root;
const int INF = (1<<30);

int New(int val) {
    a[++tot].val = val;
    a[tot].dat = rand();
    a[tot].cnt = a[tot].size = 1;
    return tot;
}

void Update(int p) {
    a[p].size = a[a[p].l].size + a[a[p].r].size + a[p].cnt;
}

void Build() {
    New(-INF); New(INF);
    root = 1; a[1].r = 2;
    Update(root);
}

int GetRankByValue(int p, int val) {
    if(p == 0) return 0;
    if(a[p].val == val) return a[a[p].l].size + 1;
    if(a[p].val > val) return GetRankByValue(a[p].l, val);
    return a[a[p].l].size + a[p].cnt + GetRankByValue(a[p].r, val);
}

int GetValueByRank(int p, int rank) {
    if(p == 0) return INF;
    if(a[a[p].l].size >= rank) return GetValueByRank(a[p].l, rank);
    if(a[a[p].l].size + a[p].cnt >= rank) return a[p].val;
    return GetValueByRank(a[p].r, rank - a[a[p].l].size - a[p].cnt);
}

void zig(int &p) {
    int q = a[p].l;
    a[p].l = a[q].r; a[q].r = p; p = q;
    Update(a[p].r); Update(p);
}

void zag(int &p) {
    int q = a[p].r;
    a[p].r = a[q].l; a[q].l = p; p = q;
    Update(a[p].l); Update(p);
}

void insert(int &p, int val) {
    if(p==0) {
        p = New(val);
        return;
    }
    if(val == a[p].val) {
        a[p].cnt++; Update(p);
        return;
    }
    if(val < a[p].val) {
        insert(a[p].l, val);
        if(a[p].dat < a[a[p].l].dat) zig(p);
    }
    else {
        insert(a[p].r, val);
        if(a[p].dat < a[a[p].r].dat) zag(p);
    }
    Update(p);
}

int GetPre(int val) {
    int ans = 1;
    int p = root;
    while(p) {
        if(val == a[p].val) {
            if(a[p].l > 0) {
                p = a[p].l;
                while(a[p].r > 0) p = a[p].r;
                ans = p;
            }
            break;
        }
        if(a[p].val < val && a[p].val > a[ans].val) ans = p;
        p = a[p].val > val ? a[p].l : a[p].r;
    }
    return a[ans].val;
}

int GetNext(int val) {
    int ans = 2;
    int p = root;
    while(p) {
        if(a[p].val == val) {
            if(a[p].r > 0) {
                p = a[p].r;
                while(a[p].l > 0) p = a[p].l;
                ans = p;
            }
            break;
        }
        if(a[p].val > val && a[p].val < a[ans].val) ans = p;
        p = a[p].val > val ? a[p].l : a[p].r;
    }
    return a[ans].val;
}

void remove(int &p, int val) {
    if(p == 0) return;
    if(val == a[p].val) {
        if(a[p].cnt > 1) {
            a[p].cnt--; Update(p);
            return;
        }
        if(a[p].l || a[p].r) {
            if(a[p].r == 0 || a[a[p].l].dat > a[a[p].r].dat)
                zig(p), remove(a[p].r, val);
            else
                zag(p), remove(a[p].l, val);
            Update(p);
        }
        else p = 0;
        return;
    }
    val < a[p].val ? remove(a[p].l, val) : remove(a[p].r, val);
    Update(p);
}

int main() {
    scanf("%d",&n);
    Build();
    while(n--) {
        int opt, x; scanf("%d%d", &opt, &x);
        if(opt == 1) insert(root, x);
        if(opt == 2) remove(root, x);
        if(opt == 3) printf("%d\n",GetRankByValue(root, x)-1);
        if(opt == 4) printf("%d\n",GetValueByRank(root, x+1));
        if(opt == 5) printf("%d\n",GetPre(x));
        if(opt == 6) printf("%d\n",GetNext(x));
    }
    return 0;
}
