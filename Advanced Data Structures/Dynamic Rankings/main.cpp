//
//  main.cpp
//  Dynamic Rankings LUOGU2617
//
//  Created by Ruining Li on 2020/3/31.
//  Copyright © 2020 Ruining Li. All rights reserved.
//

#include <iostream>
#include <cstdio>
using namespace std;
struct Opt {
    int typ;
    int x, y, z;
}q[300010],lq[300010],rq[300010];
int n,m,a[100010],t,ans[100010], c[100010];
int INF = 1e9;
bool flag[100010];
void add(int x, int val) {
    while(x<=n) {
        c[x] += val;
        x += x & (-x);
    }
}
int ask(int x) {
    int r = 0;
    while(x) {
        r += c[x];
        x -= x & (-x);
    }
    return r;
}
void solve(int lval, int rval, int st, int ed) {
    if(st > ed) return;
    if(lval == rval) {
        for(int i=st;i<=ed;++i)
            if(q[i].typ > 0) ans[q[i].typ] = lval;
        return;
    }
    int mid = (lval + rval) >> 1;
    int rt = 0, lt = 0;
    for(int i=st;i<=ed;++i) {
        if(q[i].typ <= 0) {
            if(q[i].y <= mid) add(q[i].x, q[i].typ == 0 ? 1 : -1), lq[++lt] = q[i];
            else rq[++rt] = q[i];
        }
        else {
            int cnt = ask(q[i].y) - ask(q[i].x-1);
            if(cnt >= q[i].z) lq[++lt] = q[i];
            else rq[++rt] = q[i], rq[rt].z -= cnt;
        }
    }
    for(int i=st;i<=ed;++i)
        if(q[i].typ <= 0 && q[i].y <= mid) add(q[i].x, q[i].typ == 0 ? -1 : 1);
    for(int i=st;i<st+lt;++i) q[i] = lq[i-st+1];
    for(int i=st+lt;i<=ed;++i) q[i] = rq[i-st-lt+1];
    solve(lval, mid, st, st+lt-1);
    solve(mid+1, rval, st+lt, ed);
}
int main() {
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i) {
        scanf("%d",&a[i]);
        q[++t].typ = 0, q[t].x = i, q[t].y = a[i];
    }
    for(int i=1;i<=m;++i) {
        char op[2]; int x,y,k;
        scanf("%s%d%d",op,&x,&y);
        if(op[0] == 'C') {
            q[++t].typ = -1, q[t].x = x, q[t].y = a[x];
            q[++t].typ = 0, q[t].x = x, q[t].y = y;
            a[x] = y;
        }
        else {
            scanf("%d",&k);
            flag[i] = 1;
            q[++t].typ = i, q[t].x = x, q[t].y = y, q[t].z = k;
        }
    }
    solve(0,INF,1,t);
    for(int i=1;i<=m;++i)
        if(flag[i]) printf("%d\n",ans[i]);
//    cout << t << endl;
    return 0;
}
