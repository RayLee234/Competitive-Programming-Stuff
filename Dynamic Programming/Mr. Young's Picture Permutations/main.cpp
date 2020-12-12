//
//  main.cpp
//  Mr. Young's Picture Permutations POJ2279
//
//  Created by Ruining Li on 2020/5/1.
//  Copyright © 2020 Ruining Li. All rights reserved.
//

#include <iostream>
#include <cstring>
using namespace std;
int k, a[6];
int main() {
    while(cin >> k && k) {
        memset(a, 0, sizeof(a));
        for(int i=1;i<=k;++i) cin >> a[i];
        unsigned int f[a[1]+1][a[2]+1][a[3]+1][a[4]+1][a[5]+1];
        memset(f, 0, sizeof(f));
        f[0][0][0][0][0] = 1;
        for(int i=0;i<=a[1];++i)
            for(int j=0;j<=a[2];++j)
                for(int m=0;m<=a[3];++m)
                    for(int n=0;n<=a[4];++n)
                        for(int w=0;w<=a[5];++w) {
                            if(i < a[1]) f[i+1][j][m][n][w] += f[i][j][m][n][w];
                            if(j < a[2] && j < i) f[i][j+1][m][n][w] += f[i][j][m][n][w];
                            if(m < a[3] && m < j) f[i][j][m+1][n][w] += f[i][j][m][n][w];
                            if(n < a[4] && n < m) f[i][j][m][n+1][w] += f[i][j][m][n][w];
                            if(w < a[5] && w < n) f[i][j][m][n][w+1] += f[i][j][m][n][w];
                        }
        cout << f[a[1]][a[2]][a[3]][a[4]][a[5]] << endl;
    }
    return 0;
}
