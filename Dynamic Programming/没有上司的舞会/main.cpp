//
//  main.cpp
//  没有上司的舞会 CH5401
//
//  Created by Ruining Li on 2020/5/18.
//  Copyright © 2020 Ruining Li. All rights reserved.
//

#include <iostream>
#include <vector>
using namespace std;
int n, a[6010], f[6010][2], root;
vector <int> son[6010];
bool jud[6010];
void dp(int x) {
    f[x][0] = 0;
    f[x][1] = a[x];
    for(int i=0;i<son[x].size();++i) {
        int y = son[x][i];
        dp(y);
        f[x][1] += f[y][0];
        f[x][0] += max(f[y][0], f[y][1]);
    }
}
int main() {
    cin >> n;
    for(int i=1;i<=n;++i) cin >> a[i];
    for(int i=1;i<=n;++i) {
        int x, y; cin >> x >> y;
        if(x != 0 && y != 0) son[y].push_back(x);
        jud[x] = 1;
    }
    for(int i=1;i<=n;++i)
        if(!jud[i]) {
            root = i;
            break;
        }
    dp(root);
    cout << max(f[root][0], f[root][1]) << endl;
    return 0;
}
