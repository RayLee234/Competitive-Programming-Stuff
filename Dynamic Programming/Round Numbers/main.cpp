//
//  main.cpp
//  Round Numbers POJ3252
//
//  Created by Ruining Li on 2020/8/5.
//  Copyright © 2020 Ruining Li. All rights reserved.
//

#include <iostream>
using namespace std;
int a, b, f[35][35], da, db;
void init() {
    f[0][0] = 1;
    for(int i=1;i<=33;++i) {
        f[i][0] = 1;
        for(int j=1;j<=i;++j) f[i][j] = f[i-1][j] + f[i-1][j-1];
    }
}
int solve(int x) {
    if(x == 0) return 0;
    int cnt = 0, d = 1;
    while(d <= 30 && (1 << d) <= x) ++d;
    for(int i=1;i<d;++i)
        for(int j=i-1;j>=i-j;--j) cnt += f[i-1][j];
    int num0 = 0, num1 = 1;
    for(int i=d-2;i>=0;--i) {
        if((x >> i) & 1) {
            ++num0;
            for(int j=i;j+num0>=d-j-num0;--j) cnt += f[i][j];
            --num0;
            ++num1;
        }
        else ++num0;
    }
    if(num0 >= num1) cnt++;
    return cnt;
}
int main() {
    init();
    cin >> a >> b;
    cout << solve(b) - solve(a-1) << endl;
    return 0;
}
