//
//  main.cpp
//  传纸条 LUOGU1006
//
//  Created by Ruining Li on 2020/5/2.
//  Copyright © 2020 Ruining Li. All rights reserved.
//

#include <iostream>
#include <cstring>
using namespace std;
int m,n,a[61][61],f[110][61][61];
int main() {
    memset(f,-1,sizeof f);
    cin >> m >> n;
    for(int i=1;i<=m;i++)
        for(int j=1;j<=n;j++)
            cin >> a[i][j];
    f[2][1][1]=0;
    for(int k=3;k<m+n;k++)
        for(int i=1;i<n;i++)
            for(int j=i+1;j<=n;j++) {
                int temp = f[k][i][j];
                if(f[k-1][i][j] > temp) temp = f[k-1][i][j];
                if(f[k-1][i-1][j] > temp) temp = f[k-1][i-1][j];
                if(f[k-1][i][j-1] > temp) temp = f[k-1][i][j-1];
                if(f[k-1][i-1][j-1] > temp) temp = f[k-1][i-1][j-1];
                if(temp == -1) f[k][i][j]=-1;
                else if(k-i > 0 && k-i <= m && k-j > 0 && k-j <= m) f[k][i][j]=temp+a[k-i][i]+a[k-j][j];
            }
    cout << f[m+n-1][n-1][n]<<endl;
    return 0;
}
