//
//  main.cpp
//  LCIS CH5101
//
//  Created by Ruining Li on 2020/5/1.
//  Copyright © 2020 Ruining Li. All rights reserved.
//

#include <iostream>
using namespace std;
int n, a[3001], b[3001], f[3001][3001], ans;
int main() {
    cin >> n;
    for(int i=1;i<=n;++i) cin >> a[i];
    for(int j=1;j<=n;++j) cin >> b[j];
    a[0] = b[0] = -2147483648;
    for(int i=1;i<=n;++i) {
        int val = 0;
        for(int j=1;j<=n;++j) {
            if(a[i] != b[j]) f[i][j] = f[i-1][j];
            else f[i][j] = val + 1;
            if(b[j] < a[i]) val = max(val, f[i-1][j]);
        }
    }
    for(int j=1;j<=n;++j) ans = max(ans, f[n][j]);
    cout << ans << endl;
    return 0;
}
