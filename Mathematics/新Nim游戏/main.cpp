//
//  main.cpp
//  新Nim游戏 LUOGU4301
//
//  Created by Ruining Li on 2020/3/22.
//  Copyright © 2020 Ruining Li. All rights reserved.
//

#include <iostream>
#include <cstdio>
#define ll long long
using namespace std;
int n,b[101],a[101][32];
ll ans;
int main() {
    scanf("%d",&n);
    for(int i=1;i<=n;i++) {
        scanf("%d",&b[i]);
        for(int j=1;j<=31;j++) a[i][j] = (((1<<(31-j))&b[i])>0);
    }
    int cur = 0;
    for(int i=1;i<=31;i++) {
        int r = 0;
        for(int j=cur+1;j<=n;j++)
            if(a[j][i]>0 && b[j]>b[r]) r = j;
        if(r==0) continue;
        swap(b[cur+1],b[r]);
        for(int j=1;j<=31;j++) swap(a[cur+1][j],a[r][j]);
        for(int j=1;j<=n;j++)
            if(j!=cur+1 && a[j][i]>0)
                for(int k=1;k<=31;k++)
                    a[j][k] = a[j][k] xor a[cur+1][k];
        ++cur;
    }
    for(int i=cur+1;i<=n;i++) ans = ans + b[i];
    printf("%lld\n",ans);
    return 0;
}
