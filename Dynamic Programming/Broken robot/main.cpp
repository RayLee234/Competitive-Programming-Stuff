//
//  main.cpp
//  Broken robot Codeforces24D
//
//  Created by Ruining Li on 2020/6/18.
//  Copyright © 2020 Ruining Li. All rights reserved.
//

#include <iostream>
using namespace std;
int n, m, x, y;
long double f[1010], a[1010][1010];
void init() {
    a[1][1] = a[m][m] = 2;
    for(int i=2;i<m;++i) a[i][i] = 3;
    a[1][2] = a[m][m-1] = -1;
    for(int i=2;i<m;++i) a[i][i+1] = a[i][i-1] = -1;
}
int main() {
    cin >> n >> m >> x >> y;
    if(m == 1) {
        cout << 2 * (n - x) << ".0000000000" << endl;
        return 0;
    }
    int curR = n;
    while(curR != x) {
        init();
        a[1][m+1] = f[1] + 3, a[m][m+1] = f[m] + 3;
        for(int i=2;i<m;++i) a[i][m+1] = f[i] + 4;
        for(int i=1;i<m;++i) {
            a[i+1][i+1] = a[i+1][i+1] * a[i][i] - a[i][i+1] * a[i+1][i], a[i+1][m+1] = a[i+1][m+1] * a[i][i] - a[i][m+1] * a[i+1][i];
            a[i+1][i] = 0;
            if(i != m-1) a[i+1][i+2] *= a[i][i];
        }
        f[m] = a[m][m+1] / a[m][m];
        for(int i=m-1;i>0;--i) f[i] = (a[i][m+1] - f[i+1] * a[i][i+1]) / a[i][i];
        curR--;
    }
    printf("%.10Lf\n", f[y]);
    return 0;
}
