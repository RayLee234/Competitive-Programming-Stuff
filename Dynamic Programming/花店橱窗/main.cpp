//
//  main.cpp
//  花店橱窗 CH5E02
//
//  Created by Ruining Li on 2020/6/18.
//  Copyright © 2020 Ruining Li. All rights reserved.
//

#include <iostream>
#include <cstring>
using namespace std;
int n, m, a[101][101], f[101][101][2], pre1[101][101][2], pre2[101][101][2], pre3[101][101][2], ans[101];
int main() {
    cin >> n >> m;
    for(int i=1;i<=n;++i)
        for(int j=1;j<=m;++j) cin >> a[i][j];
    memset(f, 128, sizeof(f));
    for(int i=0;i<=m;++i) f[0][i][0] = 0;
    for(int i=1;i<=n;++i)
        for(int j=1;j<=m;++j) {
            pre1[i][j][0] = i, pre1[i][j][1] = i-1, pre2[i][j][0] = pre2[i][j][1] = j-1;
            if(f[i][j-1][0] >= f[i][j-1][1]) f[i][j][0] = f[i][j-1][0], pre3[i][j][0] = 0;
            else f[i][j][0] = f[i][j-1][1], pre3[i][j][0] = 1;
            if(f[i-1][j-1][0] >= f[i-1][j-1][1]) f[i][j][1] = f[i-1][j-1][0] + a[i][j], pre3[i][j][1] = 0;
            else f[i][j][1] = f[i-1][j-1][1] + a[i][j], pre3[i][j][1] = 1;
        }
    int cur1 = n, cur2 = m, cur3;
    if(f[n][m][0] >= f[n][m][1]) cout << f[n][m][0] << endl, cur3 = 0;
    else cout << f[n][m][1] << endl, cur3 = 1;
    while(cur1 > 0) {
        int temp1 = cur1, temp2 = cur2, temp3 = cur3;
        if(cur3 == 1) ans[cur1] = cur2;
        cur1 = pre1[temp1][temp2][temp3], cur2 = pre2[temp1][temp2][temp3], cur3 = pre3[temp1][temp2][temp3];
    }
    for(int i=1;i<=n;++i) cout << ans[i] << ' ';
    cout << endl;
    return 0;
}
