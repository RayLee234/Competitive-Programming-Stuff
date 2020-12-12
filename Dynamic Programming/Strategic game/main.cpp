//
//  main.cpp
//  Strategic game POJ1463
//
//  Created by Ruining Li on 2020/6/22.
//  Copyright © 2020 Ruining Li. All rights reserved.
//

#include <iostream>
#include <vector>
#include <cstdio>
#include <cstring>
#include <string>
using namespace std;
int n, fa[1510], f[1510][2];
vector <int> son[1510];
int toInt(string s, int l, int r) {
    int ans = 0;
    for(int i=l;i<=r;++i) ans = ans * 10 + s[i] - '0';
    return ans;
}
void dp(int x) {
    if(son[x].size() == 0) {
        f[x][0] = 0, f[x][1] = 1;
        return;
    }
    for(int i=0;i<son[x].size();++i) {
        int y = son[x][i];
        dp(y);
        f[x][0] += f[y][1];
        f[x][1] += min(f[y][0], f[y][1]);
    }
    f[x][1]++;
}
int main() {
    while(cin >> n) {
        for(int i=0;i<n;++i) son[i].clear();
        memset(fa, -1, sizeof(fa));
        memset(f, 0, sizeof(f));
        for(int i=1;i<=n;++i) {
            string s;
            cin >> s;
            int x;
            for(x=0;;++x)
                if(s[x] == ':') break;
            int node = toInt(s, 0, x-1);
            for(++x;;++x)
                if(s[x] >= '0' && s[x] <= '9') break;
            int num = toInt(s, x, s.length()-2);
            for(int i=1;i<=num;++i) {
                int p; cin >> p;
                son[node].push_back(p);
                fa[p] = node;
            }
        }
        int root;
        for(int i=0;i<n;++i)
            if(fa[i] == -1) {
                root = i;
                break;
            }
        dp(root);
        cout << min(f[root][0], f[root][1]) << endl;
    }
    return 0;
}
