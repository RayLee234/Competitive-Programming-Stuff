//
//  main.cpp
//  蒲公英 LUOGU4168
//
//  Created by Ruining Li on 2020/3/26.
//  Copyright © 2020 Ruining Li. All rights reserved.
//

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
using namespace std;
int n,m;
int a[40001],l[40001],r[40001],pos[40001],x[40001],t,c[40][40][40001],ans[40][40];
int main() {
    scanf("%d%d",&n,&m);
    for(register int i=1;i<=n;++i) {
        scanf("%d",&a[i]);
        x[++t] = a[i];
    }
    sort(x+1,x+t+1);
    t = unique(x+1,x+t+1) - (x+1);
    for(register int i=1;i<=n;++i) a[i] = lower_bound(x+1,x+t+1,a[i]) - x;
    int cnt = pow((double)n,(double)1/3);
    int len = cnt ? n/cnt:n;
    for(register int i=1;i<=cnt;++i) {
        l[i] = (i-1) * len + 1;
        r[i] = i * len;
    }
    if(r[cnt]<n) ++cnt, l[cnt] = r[cnt-1]+1, r[cnt] = n;
    for(register int i=1;i<=cnt;++i)
        for(register int j=l[i];j<=r[i];++j) pos[j] = i;
    for(register int i=1;i<=cnt;++i)
        for(register int j=i;j<=cnt;++j) {
            for(register int k=l[i];k<=r[j];++k) ++c[i][j][a[k]];
            for(register int k=1;k<=t;++k)
                if(c[i][j][k]>c[i][j][ans[i][j]]) ans[i][j] = k;
        }
    int result = 0;
    while(m--) {
        int p, q, num = 0, y = 0, z = 0; scanf("%d%d",&p,&q);
        p = (p + x[result] - 1) % n + 1; q = (q + x[result] - 1) % n + 1;
        if(p>q) swap(p,q);
        int pos1 = pos[p], pos2 = pos[q];
        if(pos1+1>=pos2) {
            for(register int i=p;i<=q;++i) {
                ++c[y][z][a[i]];
                if(c[y][z][a[i]] > num || (c[y][z][a[i]]==num && a[i]<result)) {
                    num = c[y][z][a[i]];
                    result = a[i];
                }
            }
            for(register int i=p;i<=q;++i) --c[y][z][a[i]];
            printf("%d\n",x[result]);
        }
        else {
            y = pos1+1; z = pos2-1;
            result = ans[y][z]; num = c[y][z][result];
            for(register int i=p;i<=r[pos1];++i) {
                ++c[y][z][a[i]];
                if(c[y][z][a[i]]>num || (c[y][z][a[i]]==num && a[i]<result)) {
                    num = c[y][z][a[i]];
                    result = a[i];
                }
            }
            for(register int i=l[pos2];i<=q;++i) {
                ++c[y][z][a[i]];
                if(c[y][z][a[i]]>num || (c[y][z][a[i]]==num && a[i]<result)) {
                    num = c[y][z][a[i]];
                    result = a[i];
                }
            }
            for(register int i=p;i<=r[pos1];i++) --c[y][z][a[i]];
            for(register int i=l[pos2];i<=q;i++) --c[y][z][a[i]];
            printf("%d\n",x[result]);
        }
    }
    return 0;
}
