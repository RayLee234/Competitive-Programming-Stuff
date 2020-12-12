//
//  main.cpp
//  守卫者的挑战 CH3B13
//
//  Created by Ruining Li on 2020/3/22.
//  Copyright © 2020 Ruining Li. All rights reserved.
//

#include <iostream>
#include <cstdio>
using namespace std;
int n,l,k,a[201],p[201],s[201],t[201],cnt1,cnt2,tot;
long double f[201][201],g[2][201][200001];
int main() {
    scanf("%d%d%d",&n,&l,&k);
    tot = k;
    for(int i=1;i<=n;i++) scanf("%d",&p[i]);
    for(int i=1;i<=n;i++) {
        scanf("%d",&a[i]);
        if(a[i]==-1) s[++cnt1] = i;
        else {
            t[++cnt2] = i;
            tot += a[i];
        }
    }
    f[0][0] = 1; g[0][0][k] = 1;
    for(int i=1;i<=cnt1;i++) {
        int cur = s[i];
        f[i][0] = f[i-1][0] * (1.0 - p[cur]/100.0);
        for(int j=1;j<=i;j++) {
            f[i][j] = f[i-1][j-1] * p[cur]/100.0;
            if(i-1>=j) f[i][j] += f[i-1][j] * (1.0 - p[cur]/100.0);
        }
    }
    for(int i=1;i<=cnt2;i++) {
        int cur = t[i];
        g[i%2][0][k] = g[(i%2)^1][0][k] * (1.0 - p[cur]/100.0);
        for(int j=1;j<=i;j++)
            for(int w=k;w<=tot;w++) {
                if(i-1>=j) g[i%2][j][w] = g[(i%2)^1][j][w] * (1.0 - p[cur]/100.0);
                if(w-a[cur]>=k) g[i%2][j][w] += g[(i%2)^1][j-1][w-a[cur]] * p[cur]/100.0;
            }
    }
    long double ans = 0;
    for(int i=max(l-cnt1,0);i<=cnt2;i++) {
        int c = max(l-i,0);
        for(int j=c;j<=tot;j++)
            for(int w=c;w<=min(cnt1,j);w++)
                ans += g[cnt2%2][i][j] * f[cnt1][w];
    }
    printf("%.6f\n",(int)(ans*1000000+0.5)/1000000.0);
    return 0;
}
