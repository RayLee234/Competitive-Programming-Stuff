//
//  main.cpp
//  球形空间产生器 LUOGU4035
//
//  Created by Ruining Li on 2020/3/14.
//  Copyright © 2020 Ruining Li. All rights reserved.
//

#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;
int n;
double a[12][12],b[12][12],c[12];
int main() {
    scanf("%d",&n);
    for(int i=1;i<=n+1;i++)
        for(int j=1;j<=n;j++) scanf("%lf",&a[i][j]);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++) {
            b[i][j] = 2*(a[i][j]-a[i+1][j]);
            c[i] += a[i][j]*a[i][j]-a[i+1][j]*a[i+1][j];
        }
    for(int i=1;i<=n;i++) {
        for(int j=i;j<=n;j++)
            if(fabs(b[j][i])>1e-8) {
                for(int k=1;k<=n;k++) swap(b[i][k],b[j][k]);
                swap(c[i],c[j]);
                break;
            }
        for(int j=1;j<=n;j++)
            if(j!=i) {
                double v = b[j][i]/b[i][i];
                for(int k=1;k<=n;k++) b[j][k] -= b[i][k]*v;
                c[j] -= c[i]*v;
            }
    }
    for(int i=1;i<=n;i++) printf("%.3f ",c[i]/b[i][i]);
    putchar('\n');
    return 0;
}
