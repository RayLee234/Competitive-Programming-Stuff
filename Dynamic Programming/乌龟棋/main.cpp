//
//  main.cpp
//  乌龟棋 CH5E01
//
//  Created by Ruining Li on 2020/6/18.
//  Copyright © 2020 Ruining Li. All rights reserved.
//

#include <iostream>
using namespace std;
int n, m, a[351], c[5], f[41][41][41][41];
int main() {
    cin >> n >> m;
    for(int i=1;i<=n;++i) cin >> a[i];
    for(int i=1;i<=m;++i) {
        int x; cin >> x;
        ++c[x];
    }
    f[0][0][0][0] = a[1];
    for(int i=0;i<=c[1];++i)
        for(int j=0;j<=c[2];++j)
            for(int k=0;k<=c[3];++k)
                for(int w=0;w<=c[4];++w) {
                    if(i + j + k + w == 0) continue;
                    int now = 1 + i + 2*j + 3*k + 4*w;
                    if(i > 0) f[i][j][k][w] = max(f[i][j][k][w], f[i-1][j][k][w] + a[now]);
                    if(j > 0) f[i][j][k][w] = max(f[i][j][k][w], f[i][j-1][k][w] + a[now]);
                    if(k > 0) f[i][j][k][w] = max(f[i][j][k][w], f[i][j][k-1][w] + a[now]);
                    if(w > 0) f[i][j][k][w] = max(f[i][j][k][w], f[i][j][k][w-1] + a[now]);
                }
    cout << f[c[1]][c[2]][c[3]][c[4]] << endl;
    return 0;
}
