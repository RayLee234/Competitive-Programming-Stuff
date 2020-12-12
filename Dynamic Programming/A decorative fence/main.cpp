//
//  main.cpp
//  A decorative fence
//
//  Created by Ruining Li on 2020/7/20.
//  Copyright © 2020 Ruining Li. All rights reserved.
//

#include <iostream>
#include <cstring>
#include <vector>
#define int long long
using namespace std;
int T, n, c, f[21][21][2], ans[21];
bool used[21];
void init() {
    f[1][1][0] = f[1][1][1] = 1;
    for(int i=2;i<=20;++i)
        for(int j=1;j<=i;++j) {
            for(int k=1;k<j;++k) f[i][j][1] += f[i-1][k][0];
            for(int k=j;k<i;++k) f[i][j][0] += f[i-1][k][1];
        }
}
signed main() {
    init();
    cin >> T;
    while(T--) {
        cin >> n >> c;
        memset(used, 0, sizeof(used));
        bool rising;
        for(int i=1;i<=n;++i) {
            if(f[n][i][1] >= c) { ans[1] = i; used[i] = 1; rising = 0; break; }
            c -= f[n][i][1];
            if(f[n][i][0] >= c) { ans[1] = i; used[i] = 1; rising = 1; break; }
            c -= f[n][i][0];
        }
        for(int i=2;i<=n;++i)
            if(rising) {
                for(int j=ans[i-1]+1;j<=n;++j)
                    if(!used[j]) {
                        int ranking = j;
                        for(int k=1;k<j;++k)
                            if(used[k]) --ranking;
                        if(f[n-i+1][ranking][1] >= c) { ans[i] = j; used[j] = 1; rising = 0; break; }
                        c -= f[n-i+1][ranking][1];
                    }
            }
            else {
                for(int j=1;j<ans[i-1];++j)
                    if(!used[j]) {
                        int ranking = j;
                        for(int k=1;k<j;++k)
                            if(used[k]) --ranking;
                        if(f[n-i+1][ranking][0] >= c) { ans[i] = j; used[j] = 1; rising = 1; break; }
                        c -= f[n-i+1][ranking][0];
                    }
            }
        for(int i=1;i<=n;++i) cout << ans[i] << ' ' ;
        cout << endl;
    }
    return 0;
}
