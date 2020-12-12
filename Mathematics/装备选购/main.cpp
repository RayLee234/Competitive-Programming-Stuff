//
//  main.cpp
//  装备选购 LUOGU3265
//
//  Created by Ruining Li on 2020/3/15.
//  Copyright © 2020 Ruining Li. All rights reserved.
//

#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;
int n,m,p[501];
double a[501][501];
int main() {
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            scanf("%lf",&a[i][j]);
    for(int i=1;i<=n;i++) scanf("%d",&p[i]);
    p[0] = 2147483647;
    int cur = 0, num = 0, ans = 0;
    for(int i=1;i<=m;i++) {
        int R = 0;
        for(int j=cur+1;j<=n;j++)
            if(fabs(a[j][i])>1e-4 && p[j]<p[R]) R = j;
        if(!R) continue;
        num++; ans+=p[R];
        for(int j=1;j<=m;j++) swap(a[R][j],a[cur+1][j]);
        swap(p[R],p[cur+1]);
        for(int j=1;j<=n;j++)
            if(j!=cur+1) {
                double v = a[j][i]/a[cur+1][i];
                for(int k=1;k<=m;k++) a[j][k] -= v*a[cur+1][k];
            }
        cur++;
    }
    printf("%d %d\n",num,ans);
    return 0;
}
