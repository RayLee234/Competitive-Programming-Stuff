//
//  main.cpp
//  开关问题 POJ1830
//
//  Created by Ruining Li on 2020/3/14.
//  Copyright © 2020 Ruining Li. All rights reserved.
//

#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
using namespace std;
int T,n,a[30][30],s[30],t[30],c[30];
int main() {
    scanf("%d",&T);
    while(T--) {
        scanf("%d",&n);
        memset(a,0,sizeof(a));
        for(int i=1;i<=n;i++) scanf("%d",&s[i]);
        for(int i=1;i<=n;i++) scanf("%d",&t[i]);
        int x,y;
        while(scanf("%d%d",&x,&y) && x && y) a[y][x] = 1;
        for(int i=1;i<=n;i++) c[i] = (s[i] xor t[i]), a[i][i] = 1;
        int cur = 0;
        for(int i=1;i<=n;i++) {
            bool find = 0;
            for(int j=cur+1;j<=n;j++)
                if(a[j][i]>0) {
                    find = 1;
                    for(int k=1;k<=n;k++) swap(a[cur+1][k],a[j][k]);
                    swap(c[cur+1],c[j]);
                    break;
                }
            if(!find) continue;
            for(int j=1;j<=n;j++)
                if(cur+1!=j && (a[cur+1][i] xor a[j][i])==0) {
                    for(int k=1;k<=n;k++) a[j][k] = a[j][k] xor a[cur+1][k];
                    c[j] = c[j] xor c[cur+1];
                }
            ++cur;
        }
        bool ok = 1; int cnt = 0;
        for(int i=1;i<=n;i++) {
            bool all0 = 1;
            for(int j=1;j<=n;j++)
                if(a[i][j]) all0 = 0;
            if(all0 && c[i]) {
                ok = 0;
                break;
            }
            else if(all0) cnt++;
        }
        if(!ok) puts("Oh,it\'s impossible~!!");
        else printf("%d\n",(1<<cnt));
    }
    return 0;
}
