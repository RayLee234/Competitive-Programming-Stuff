//
//  main.cpp
//  Trip POJ1934
//
//  Created by Ruining Li on 2020/6/19.
//  Copyright © 2020 Ruining Li. All rights reserved.
//

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstring>
#include <map>
using namespace std;
string a, b, ans_reversed[300010], ans[300010], cur;
int la, lb, f[82][82], cnt;
vector < int > preI[82][82], preJ[82][82];
map < pair< string, pair<int,int> >, bool > s;
inline void dfs(int x, int y) {
    if(s[make_pair(cur, make_pair(x, y))] == true) return;
    if(cur.length() == f[la][lb]) {
        ans_reversed[cnt++] = cur;
        return;
    }
    for(register int i=0;i<preI[x][y].size();++i) {
        if(x == preI[x][y][i] + 1 && y == preJ[x][y][i] + 1) cur.push_back(b[y-1]);
        dfs(preI[x][y][i], preJ[x][y][i]);
        s[make_pair(cur, make_pair(preI[x][y][i], preJ[x][y][i]))] = true;
        if(x == preI[x][y][i] + 1 && y == preJ[x][y][i] + 1) cur.erase(cur.length()-1, 1);
    }
}
int main() {
    cin >> a >> b;
    la = a.length(); lb = b.length();
    for(register int i=1;i<=la;++i)
        for(register int j=1;j<=lb;++j) {
            if(a[i-1] == b[j-1]) {
                f[i][j] = f[i-1][j-1] + 1;
                preI[i][j].push_back(i-1), preJ[i][j].push_back(j-1);
                if(f[i-1][j] == f[i][j]) preI[i][j].push_back(i-1), preJ[i][j].push_back(j);
                if(f[i][j-1] == f[i][j]) preI[i][j].push_back(i), preJ[i][j].push_back(j-1);
            }
            else {
                if(f[i-1][j] > f[i][j-1]) {
                    f[i][j] = f[i-1][j];
                    preI[i][j].push_back(i-1), preJ[i][j].push_back(j);
                }
                else if(f[i-1][j] < f[i][j-1]) {
                    f[i][j] = f[i][j-1];
                    preI[i][j].push_back(i), preJ[i][j].push_back(j-1);
                }
                else {
                    f[i][j] = f[i-1][j];
                    preI[i][j].push_back(i), preJ[i][j].push_back(j-1);
                    preI[i][j].push_back(i-1), preJ[i][j].push_back(j);
                }
            }
        }
    dfs(la, lb);
    for(register int i=0;i<cnt;++i)
        for(register int j=f[la][lb]-1;j>=0;--j) ans[i].push_back(ans_reversed[i][j]);
    sort(ans, ans + cnt);
    int num = unique(ans, ans + cnt) - ans;
    for(register int i=0;i<num;++i) cout << ans[i] << endl;
    return 0;
}
