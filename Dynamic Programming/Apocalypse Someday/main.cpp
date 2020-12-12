//
//  main.cpp
//  Apocalypse Someday POJ3208
//
//  Created by Ruining Li on 2020/7/21.
//  Copyright © 2020 Ruining Li. All rights reserved.
//

#include <iostream>
#define int long long
using namespace std;
int T, n, f[19][4];
void init() {
    f[0][0] = 1;
    f[1][3] = f[1][2] = 0, f[1][1] = 1, f[1][0] = 9;
    for(int i=2;i<=18;++i) f[i][3] = 10 * f[i-1][3] + f[i-1][2], f[i][2] = f[i-1][1], f[i][1] = f[i-1][0], f[i][0] = 9 * (f[i-1][0] + f[i-1][1] + f[i-1][2]);
}
signed main() {
    cin >> T;
    init();
    while(T--) {
        cin >> n;
        int d = 3, k = 0;
        while(f[d][3] < n) ++d;
        for(int i=1;i<=d;++i) {
            for(int j=0;j<=9;++j) {
                if(k == 3) {
                    if(f[d-i][0] + f[d-i][1] + f[d-i][2] + f[d-i][3] >= n) { cout << j; break; }
                    else n -= f[d-i][0] + f[d-i][1] + f[d-i][2] + f[d-i][3];
                }
                else if(k == 2) {
                    if(j != 6) {
                        if(f[d-i][3] >= n) { cout << j; k = 0; break; }
                        else n -= f[d-i][3];
                    }
                    else {
                        if(f[d-i][0] + f[d-i][1] + f[d-i][2] + f[d-i][3] >= n) { cout << j; k = 3; break; }
                        else n -= f[d-i][0] + f[d-i][1] + f[d-i][2] + f[d-i][3];
                    }
                }
                else if(k == 1) {
                    if(j != 6) {
                        if(f[d-i][3] >= n) { cout << j; k = 0; break; }
                        else n -= f[d-i][3];
                    }
                    else {
                        if(f[d-i][1] + f[d-i][2] + f[d-i][3] >= n) { cout << j; k = 2; break; }
                        else n -= f[d-i][1] + f[d-i][2] + f[d-i][3];
                    }
                }
                else {
                    if(j != 6) {
                        if(f[d-i][3] >= n) { cout << j; break; }
                        else n -= f[d-i][3];
                    }
                    else {
                        if(f[d-i][2] + f[d-i][3] >= n) { cout << j; k = 1; break; }
                        else n -= f[d-i][2] + f[d-i][3];
                    }
                }
            }
        }
        cout << endl;
    }
    return 0;
}
