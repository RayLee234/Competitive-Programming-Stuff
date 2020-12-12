//
//  main.cpp
//  Rainbow的信号 CH3801
//
//  Created by Ruining Li on 2020/3/18.
//  Copyright © 2020 Ruining Li. All rights reserved.
//

#include <iostream>
#include <cstdio>
using namespace std;
int n, a[100001];
long double A,B,C; // A: xor; B: and; C: or
int main() {
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    // Case 1: l == r
    for(int i=1;i<=n;i++)
        for(int k=0;k<31;k++)
            if((1<<k)&a[i]) {
                long double x = (long double)(1<<k)/n/n;
                A += x; B += x; C += x;
            }
    // Case 2: l!=r
    for(int k=0;k<31;k++) {
        int last[2] = {0,0}, s = 0, t = 0; // s: current interval; t: adjacent interval
        for(int i=1;i<=n;i++) {
            int cur = 0;
            if((1<<k)&a[i]) cur = 1;
            if(cur) {
                A += (long double)(1<<k)*s*2/n/n;
                B += (long double)(1<<k)*(i-last[0]-1)*2/n/n;
                C += (long double)(1<<k)*(i-1)*2/n/n;
            }
            else {
                A +=(long double)(1<<k)*t*2/n/n;
                C += (long double)(1<<k)*last[1]*2/n/n;
            }
            last[cur] = i;
            ++s;
            if(cur) swap(s,t);
        }
    }
    A = (long long)(A*1000+0.5)/1000.0; B = (long long)(B*1000+0.5)/1000.0; C = (long long)(C*1000+0.5)/1000.0;
    printf("%.3Lf %.3Lf %.3Lf\n",A,B,C);
    return 0;
}
