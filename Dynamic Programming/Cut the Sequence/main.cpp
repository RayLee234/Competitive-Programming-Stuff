//
//  main.cpp
//  Cut the Sequence POJ3017
//
//  Created by Ruining Li on 2020/6/28.
//  Copyright © 2020 Ruining Li. All rights reserved.
//

#include <iostream>
#include <cstdio>
#include <queue>
#include <cstring>
#define ll long long
using namespace std;
int n, c[100010], u[100010];
ll m, a[100010], s[100010], f[100010], st[100010][20];
void init_c() {
    for(int i=1;i<=n;++i) {
        int l = 1, r = i-1, res = 0;
        while(l <= r) {
            int mid = (l + r) >> 1;
            if(s[i] - s[mid-1] > m) { res = mid; l = mid + 1; }
            else r = mid - 1;
        }
        c[i] = res;
    }
}
void init_st() {
    memset(st, -1, sizeof(st));
    for(int i=1;i<=n;++i) st[i][0] = a[i];
    for(int j=1;j<20;++j)
        for(int i=1;i<=n;++i)
            if(i + (1 << j) - 1 <= n) st[i][j] = max(st[i][j-1], st[i+(1<<(j-1))][j-1]);
    for(int i=1;i<=n;++i) {
        int x = 0;
        while((1 << (x+1)) <= i) ++x;
        u[i] = x;
    }
}
ll ask_max(int l, int r) {
    int len = r - l + 1;
    return max(st[l][u[len]], st[r-(1<<u[len])+1][u[len]]);
}
int main() {
    freopen("40.in", "r", stdin);
    freopen("1.out", "w", stdout);
    cin >> n >> m;
    for(int i=1;i<=n;++i) {
        scanf("%lld", &a[i]);
        if(a[i] > m) { puts("-1"); return 0; }
        s[i] = s[i-1] + a[i];
    }
    init_c();
    init_st();
    for(int i=1;i<=n;++i) f[i] = f[c[i]] + ask_max(c[i]+1, i);
    deque <int> q;
    deque <int>::iterator it;
    for(int i=1;i<=n;++i) {
        while(!q.empty() && s[i] - s[q.front()] > m) q.pop_front();
        for(it=q.begin();it<q.end();++it) f[i] = min(f[i], f[*it]+ask_max((*it)+1, i));
        while(!q.empty() && a[q.back()] <= a[i]) q.pop_back();
        q.push_back(i);
    }
    for(int i=1;i<=n;++i) cout << f[i] << ' ';
    cout << endl;
    printf("%lld\n", f[n]);
    return 0;
}
