//
//  main.cpp
//  Georgia and Bob POJ1704
//
//  Created by Ruining Li on 2020/3/22.
//  Copyright © 2020 Ruining Li. All rights reserved.
//

#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
int T,a[1001],c[1001];
int main() {
    scanf("%d",&T);
    while (T--) {
        int n;
        scanf("%d",&n);
        for(int i=1;i<=n;i++) scanf("%d",&a[i]);
        sort(a+1,a+n+1);
        for(int i=1;i<=n;i++) c[i] = a[i] - a[i-1] - 1;
        int ans = 0;
        for(int i=n;i>=1;i-=2) ans = ans xor c[i];
        if(ans>0) puts("Georgia will win");
        else puts("Bob will win");
    }
    return 0;
}
