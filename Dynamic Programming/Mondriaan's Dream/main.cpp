//
//  main.cpp
//  Mondriaan's Dream POJ2411
//
//  Created by Ruining Li on 2020/6/24.
//  Copyright © 2020 Ruining Li. All rights reserved.
//

#include <iostream>
#include <cstring>
using namespace std;
int n, m;
long long f[12][1<<11];
bool in_s[1<<11];
int main() {
    while(cin >> n >> m) {
        if(n == 0 && m == 0) return 0;
        memset(f, 0, sizeof(f));
        f[0][0] = 1;
        for(int i=0;i<(1<<m);++i) {
            bool ok = 1; int cnt = 0;
            for(int j=0;j<m;++j)
                if((i>>j) & 1) {
                    if(cnt % 2 == 1) { ok = 0; break; }
                    cnt = 0;
                }
                else ++cnt;
            if(cnt % 2 == 1) ok = 0;
            in_s[i] = ok;
        }
        for(int i=1;i<=n;++i)
            for(int j=0;j<(1<<m);++j)
                for(int k=0;k<(1<<m);++k)
                    if((k&j) == 0 && in_s[k|j]) f[i][j] += f[i-1][k];
        cout << f[n][0] << endl;
    }
    return 0;
}
