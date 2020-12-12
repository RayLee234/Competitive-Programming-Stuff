//
//  main.cpp
//  SUBSTRACT POJ1722
//
//  Created by Ruining Li on 2020/6/20.
//  Copyright © 2020 Ruining Li. All rights reserved.
//

#include <iostream>
using namespace std;
int n, t, a[101], f[101][20010], temp[101], s[101];
int main() {
    cin >> n >> t;
    for(int i=1;i<=n;++i) cin >> a[i];
    f[1][a[1]+10000] = 1, f[2][a[1]-a[2]+10000] = -1;
    for(int i=3;i<=n;++i)
        for(int j=0;j<=20000;++j)
            if(j+a[i] <= 20000 && f[i-1][j+a[i]] != 0) f[i][j] = -1;
            else if(j-a[i] >= 0 && f[i-1][j-a[i]] != 0) f[i][j] = 1;
    int cur = n, val = t+10000, cnt = 0;
    while(cur > 0)
        if(f[cur][val] == -1) s[cur] = -1, val += a[cur--];
        else s[cur] = 1, val -= a[cur--];
    for(int i=2;i<=n;++i)
        if(s[i] == 1) cout << i-1-cnt << endl, ++cnt;
    for(int i=cnt+1;i<n;++i) cout << 1 << endl;
    return 0;
}
