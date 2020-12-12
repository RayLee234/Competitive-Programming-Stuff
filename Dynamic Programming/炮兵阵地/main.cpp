//
//  main.cpp
//  炮兵阵地 POJ1185
//
//  Created by Ruining Li on 2020/6/24.
//  Copyright © 2020 Ruining Li. All rights reserved.
//

#include <iostream>
#include <cstdio>
#include <vector>
using namespace std;
int n, m, f[101][100][100], ans;
bool in_s[1<<10];
char g[101][11];
bool valid(int r, int x) {
    if(!in_s[x]) return 0;
    for(int i=0;i<m;++i)
        if(((x>>i) & 1) && g[r][i] != 'P') return 0;
    return 1;
}
int count(int x) {
    int cnt = 0;
    for(int i=0;i<m;++i)
        if((x>>i) & 1) ++cnt;
    return cnt;
}
vector <int> s;
int main() {
    scanf("%d %d", &n, &m);
    for(int i=1;i<=n;++i) scanf("%s", g[i]);
    for(int i=0;i<(1<<m);++i) {
        bool ok = 1; int last1 = -5;
        for(int j=0;j<m;++j)
            if((i>>j) & 1) {
                if(j-last1 < 3) { ok = 0; break; }
                last1 = j;
            }
        if(ok) in_s[i] = 1, s.push_back(i);
    }
    int t = s.size();
    if(n == 1) {
        for(int i=0;i<t;++i)
            if(valid(1,s[i])) ans = max(ans, count(s[i]));
        cout << ans << endl;
        return 0;
    }
    for(int i=0;i<t;++i)
        for(int j=0;j<t;++j)
            if((s[i]&s[j]) == 0 && valid(1,s[j]) && valid(2, s[i])) f[2][i][j] = count(s[i]) + count(s[j]);
            else f[2][i][j] = -1000;
    for(int r=3;r<=n;++r)
        for(int i=0;i<t;++i)
            for(int j=0;j<t;++j) {
                if(!valid(r,s[i]) || !valid(r-1,s[j]) || (s[i]&s[j]) != 0) { f[r][i][j] = -1000; continue; }
                for(int k=0;k<t;++k)
                    if((s[k]&s[i]) == 0) f[r][i][j] = max(f[r][i][j], f[r-1][j][k] + count(s[i]));
            }
    for(int i=0;i<t;++i)
        for(int j=0;j<t;++j) ans = max(ans, f[n][i][j]);
    cout << ans << endl;
    return 0;
}
