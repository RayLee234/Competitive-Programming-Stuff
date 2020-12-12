//
//  main.cpp
//  陨石的秘密 POJ1187
//
//  Created by Ruining Li on 2020/6/20.
//  Copyright © 2020 Ruining Li. All rights reserved.
//

#include <iostream>
using namespace std;
int a, b, c, d, f[11][11][11][31];
const int mod = 11380;
int main() {
    cin >> a >> b >> c >> d;
    for(int i=0;i<=a;++i)
        for(int j=0;j<=b;++j)
            for(int k=0;k<=c;++k)
                for(int depth=0;depth<=d;++depth) {
                    if(i == 0 && j == 0 && k == 0) {
                        f[i][j][k][depth] = 1;
                        continue;
                    }
                    if(depth == 0) continue;
                    for(int x=0;x<i;++x)
                        for(int y=0;y<=j;++y)
                            for(int z=0;z<=k;++z) (f[i][j][k][depth] += f[x][y][z][depth-1] * f[i-x-1][j-y][k-z][depth]) %= mod;
                    for(int y=0;y<j;++y)
                        for(int z=0;z<=k;++z) (f[i][j][k][depth] += f[0][y][z][depth-1] * f[i][j-y-1][k-z][depth]) %= mod;
                    for(int z=0;z<k;++z) (f[i][j][k][depth] += f[0][0][z][depth-1] * f[i][j][k-z-1][depth]) %= mod;
                }
    cout << (f[a][b][c][d] - f[a][b][c][d-1] + mod) % mod << endl;
    return 0;
}
