//
//  main.cpp
//  Widget Factory POJ2947
//
//  Created by Ruining Li on 2020/3/21.
//  Copyright © 2020 Ruining Li. All rights reserved.
//

#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>
using namespace std;
int n,m,a[301][301],b[301];
int day(string x) {
    if(x[0]=='M') return 1;
    if(x[0]=='W') return 3;
    if(x[0]=='F') return 5;
    if(x[1]=='A') return 6;
    if(x[1]=='H') return 4;
    if(x[2]=='E') return 2;
    return 7;
}
int exp(int x, int y) {
    int r = 1;
    x %= 7;
    while(y) {
        if(y&1) r = (r * x) % 7;
        y >>= 1;
        x = x * x % 7;
    }
    return r;
}
int main() {
    while(scanf("%d%d",&n,&m)) {
        if(n==0) return 0;
        memset(a, 0, sizeof(a));
        for(int i=1;i<=m;i++) {
            int w; string p,q;
            scanf("%d",&w);
            cin >> p >> q;
            b[i] = (day(q)-day(p)+1+7) % 7;
            while(w--) {
                int x; scanf("%d",&x);
                ++a[i][x];
            }
        }
        for(int i=1;i<=m;i++)
            for(int j=1;j<=n;j++) a[i][j] %= 7;
        int cur = 0;
        for(int i=1;i<=n;i++) {
            bool find = 0;
            for(int j=cur+1;j<=m;j++)
                if(a[j][i]!=0) {
                    find = 1;
                    swap(b[cur+1],b[j]);
                    for(int k=1;k<=n;k++) swap(a[cur+1][k],a[j][k]);
                    break;
                }
            if(!find) continue;
            for(int j=1;j<=m;j++)
                if(j!=cur+1) {
                    int c = a[j][i], d = a[cur+1][i];
                    for(int k=1;k<=n;k++) a[j][k] = ((a[j][k] * d - a[cur+1][k] * c) % 7 + 7) % 7;
                    b[j] = ((b[j] * d - b[cur+1] * c) % 7 + 7) % 7;
                }
            ++cur;
        }
        bool ok = 1, mul = 0;
        int cnt[301], tot = 0; memset(cnt,0,sizeof cnt);
        for(int i=1;i<=m;i++)
            for(int j=1;j<=n;j++)
                if(a[i][j]!=0) ++cnt[i];
        for(int i=1;i<=m;i++)
            if(cnt[i]==0 && b[i]!=0) {
                ok = 0;
                break;
            }
        if(!ok) {
            puts("Inconsistent data.");
            continue;
        }
        for(int i=1;i<=m;i++) {
            if(cnt[i]>1) mul = 1;
            if(cnt[i]>0) ++tot;
        }
        if(mul || tot<n) {
            puts("Multiple solutions.");
            continue;
        }
        for(int i=1;i<=m;i++)
            if(cnt[i]) printf("%d ",exp(a[i][i],5)*b[i]%7>=3 ? exp(a[i][i],5)*b[i]%7 : exp(a[i][i],5)*b[i]%7+7);
        putchar('\n');
    }
    return 0;
}
