//
//  main.cpp
//  Naptime POJ2228
//
//  Created by Ruining Li on 2020/6/18.
//  Copyright © 2020 Ruining Li. All rights reserved.
//

#include <iostream>
#include <cstring>
using namespace std;
int n, b, u[4000], f[2][4000][2], ans;
int main() {
    cin >> n >> b;
    for(int i=1;i<=n;++i) cin >> u[i];
    memset(f, 128, sizeof(f));
    f[1][0][0] = f[1][1][1] = 0;
    for(int i=2;i<=n;++i) {
        f[i%2][0][0] = 0;
        for(int j=1;j<=b;++j) {
            f[i%2][j][0] = max(f[(i-1)%2][j][0], f[(i-1)%2][j][1]);
            f[i%2][j][1] = max(f[(i-1)%2][j-1][0], f[(i-1)%2][j-1][1] + u[i]);
        }
    }
    ans = max(f[n%2][b][0], f[n%2][b][1]);
    memset(f, 128, sizeof(f));
    f[1][1][1] = u[1];
    for(int i=2;i<=n;++i)
        for(int j=1;j<=b;++j) {
            f[i%2][j][0] = max(f[(i-1)%2][j][0], f[(i-1)%2][j][1]);
            f[i%2][j][1] = max(f[(i-1)%2][j-1][0], f[(i-1)%2][j-1][1] + u[i]);
        }
    ans = max(ans, f[n%2][b][1]);
    cout << ans << endl;
    return 0;
}
