//
//  main.cpp
//  Briding FIPA POJ3345
//
//  Created by Ruining Li on 2020/6/22.
//  Copyright © 2020 Ruining Li. All rights reserved.
//

#include <map>
#include <cstdio>
#include <vector>
#include <cstring>
#include <sstream>
#include <iostream>
#include <algorithm>
using namespace std;
map <string, int> dict;
char s[110];
bool v[201];
vector <int> son[201];
int n, m, a[201], f[201][201], c[201], ans;
void dp(int x) {
    f[x][0] = 0;
    if(son[x].size() == 0) {
        f[x][1] = a[x];
        c[x] = 1;
        return;
    }
    for(int i=0;i<son[x].size();++i) {
        int y = son[x][i];
        dp(y);
        c[x] += c[y];
        for(int j=n;j>0;--j)
            for(int k=1;k<=j;++k) f[x][j] = min(f[x][j], f[y][k] + f[x][j-k]);
    }
    ++c[x];
    f[x][c[x]] = min(f[x][c[x]], a[x]);
}
int main() {
    while(fgets(s, sizeof(s), stdin) && s[0] != '#') {
        ans = 1e9;
        sscanf(s, "%d %d", &n, &m);
        int num = 0;
        dict.clear();
        for(int i=0;i<=n;++i) son[i].clear();
        memset(v, 1, sizeof(v));
        for(int i=1;i<=n;++i) {
            int d;
            scanf("%s %d", s, &d);
            if(dict.find(s) == dict.end()) dict[s] = ++num;
            int x = dict[s];
            a[x] = d;
            fgets(s, sizeof(s), stdin);
            stringstream ss(s);
            string str;
            while(ss >> str) {
                if(dict.find(str) == dict.end()) dict[str] = ++num;
                int y = dict[str];
                v[y] = 0;
                son[x].push_back(y);
            }
        }
        for(int i=1;i<=n;++i)
            if(v[i]) son[0].push_back(i);
        a[0] = 1e9;
        memset(f, 15, sizeof(f));
        memset(c, 0, sizeof(c));
        dp(0);
        for(int i=m;i<=n;++i) ans = min(ans, f[0][i]);
        cout << ans << endl;
    }
    return 0;
}
