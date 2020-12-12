//
//  main.cpp
//  小Z的袜子 LUOGU1494
//
//  Created by Ruining Li on 2020/3/26.
//  Copyright © 2020 Ruining Li. All rights reserved.
//

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
using namespace std;
int n,m,a[50001],s[50001],l[50001],r[50001],answer[50001];
struct Q {
    int l, r;
}q[50001];
bool cmp1(int x, int y) {
    return q[x].l < q[y].l;
}
bool cmp2(int x, int y) {
    return q[x].r < q[y].r;
}
int gcd(int x, int y) {
    if(y==0) return x;
    return gcd(y,x%y);
}
int main() {
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i) scanf("%d",&a[i]);
    for(int i=1;i<=m;++i) scanf("%d%d",&q[i].l,&q[i].r), s[i] = i;
    sort(s+1,s+m+1,cmp1);
    int len = sqrt(n), t = len ? n/len:n, cur = 1;
    for(int i=1;i<=t;i++) {
        int L = (i-1) * len + 1, R = i * len;
        int temp = cur;
        while(cur<=n && q[s[cur]].l>=L && q[s[cur]].l<=R) cur++;
        if(temp==cur) l[i] = r[i] = -1;
        else {
            l[i] = temp; r[i] = cur-1;
            sort(s+temp,s+cur,cmp2);
        }
    }
    if(cur<=m) {
        l[++t] = cur; r[t] = n;
        sort(s+cur,s+n+1,cmp2);
    }
    for(int i=1;i<=t;i++) {
        if(l[i]==-1) continue;
        int c[50001];
        memset(c, 0, sizeof(c));
        int L = q[s[l[i]]].l, R = q[s[l[i]]].r, ans = 0;
        for(int j=L;j<=R;j++) ++c[a[j]];
        for(int j=1;j<=n;j++) ans += (long long)c[j]*(c[j]-1)/2;
        answer[s[l[i]]] = ans;
        for(int j=l[i]+1;j<=r[i];j++) {
            int newL = q[s[j]].l, newR = q[s[j]].r;
            while(R < newR) {
                ++R;
                ans += c[a[R]];
                ++c[a[R]];
            }
            while(L < newL) {
                ans -= c[a[L]] - 1;
                --c[a[L]];
                ++L;
            }
            while(L > newL) {
                --L;
                ans += c[a[L]];
                c[a[L]]++;
            }
            answer[s[j]] = ans;
        }
    }
    for(int i=1;i<=m;i++) {
        if(answer[i]==0) {
            puts("0/1");
            continue;
        }
        int tot = (long long)(q[i].r-q[i].l+1) * (q[i].r-q[i].l) / 2;
        int d = gcd(tot,answer[i]);
        printf("%d/%d\n",answer[i]/d,tot/d);
    }
    return 0;
}
