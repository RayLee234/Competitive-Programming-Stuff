//
//  main.cpp
//  划分大理石 CH5E07
//
//  Created by Ruining Li on 2020/6/21.
//  Copyright © 2020 Ruining Li. All rights reserved.
//

#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
int a[7];
int num[60010];
bool f[60010];
int main() {
    while(scanf("%d %d %d %d %d %d", &a[1], &a[2], &a[3], &a[4], &a[5], &a[6])) {
        if(a[1] + a[2] + a[3] + a[4] + a[5] + a[6] == 0) return 0;
        int sum = a[1] + 2*a[2] + 3*a[3] + 4*a[4] + 5*a[5] + 6*a[6];
        if(sum % 2 == 1) {
            puts("Can't");
            continue;
        }
        int v = sum / 2;
        f[0] = 1;
        for(int i=1;i<=6;++i) {
            memset(num, 0, sizeof(num));
            for(int j=0;j<=v;++j)
                if(!f[j] && f[j-i] && num[j-i] < a[i]) f[j] = 1, num[j] = num[j-i] + 1;
        }
        if(f[v]) puts("Can");
        else puts("Can't");
    }
    return 0;
}
