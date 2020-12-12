//
//  main.cpp
//  选课 CH5402
//
//  Created by Ruining Li on 2020/5/18.
//  Copyright © 2020 Ruining Li. All rights reserved.
//

#include <iostream>
#include <vector>
using namespace std;
int n, m, c[301], pre[301], f[301][301];
vector <int> son[301];
void dp(int x) {
    for(int i=0;i<son[x].size();++i) {
        int y = son[x][i];
        dp(y);
        for(int t=m;t>0;--t)
            for(int j=0;j<=t;++j) f[x][t] = max(f[x][t], f[x][t-j] + f[y][j]);
    }
    if(x != 0)
        for(int t=m;t>0;--t) f[x][t] = f[x][t-1] + c[x];
}
int main() {
    cin >> n >> m;
    for(int i=1;i<=n;++i) {
        cin >> pre[i] >> c[i];
        son[pre[i]].push_back(i);
    }
    dp(0);
    cout << f[0][m] << endl;
    return 0;
}
