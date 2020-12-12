//
//  main.cpp
//  Cookies CH5105
//
//  Created by Ruining Li on 2020/5/2.
//  Copyright © 2020 Ruining Li. All rights reserved.
//

#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;
int n, m, s[31], f[31][5001], num[31], r[31];
pair<int,int> pre[31][5001], g[31];
bool cmp(pair<int,int> x, pair<int,int> y) {
    return x > y;
}
int main() {
    cin >> n >> m;
    for(int i=1;i<=n;++i) cin >> g[i].first, g[i].second = i;
    sort(g+1, g+n+1, cmp);
    for(int i=1;i<=n;++i) s[i] = s[i-1] + g[i].first;
    memset(f, 5, sizeof(f));
    for(int i=0;i<=n;++i) f[i][i] = 0;
    for(int i=1;i<=n;++i)
        for(int j=i+1;j<=m;++j) {
            if(f[i][j] > f[i][j-i]) f[i][j] = f[i][j-i], pre[i][j] = make_pair(i, j-i);
            for(int k=1;k<=i;++k) // k: # of 1
                if(f[i][j] > f[i-k][j-k] + (i-k) * (s[i] - s[i-k])) f[i][j] = f[i-k][j-k] + (i-k) * (s[i] - s[i-k]), pre[i][j] = make_pair(i-k, j-k);
        }
    cout << f[n][m] << endl;
    int curP = n, curC = m, cnt = 1;
    while(curP > 0) {
        while(pre[curP][curC].first == curP) curC = pre[curP][curC].second, ++cnt;
        for(int i=pre[curP][curC].first+1;i<=curP;++i) num[i] = cnt;
        int nowP = curP, nowC = curC;
        curP = pre[nowP][nowC].first, curC = pre[nowP][nowC].second;
    }
    for(int i=1;i<=n;++i) r[g[i].second] = num[i];
    for(int i=1;i<=n;++i) cout << r[i] << ' ';
    cout << endl;
    return 0;
}
