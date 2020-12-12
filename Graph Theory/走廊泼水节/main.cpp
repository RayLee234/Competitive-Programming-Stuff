//
//  main.cpp
//  走廊泼水节 CH6201
//
//  Created by Ruining Li on 2020/8/11.
//  Copyright © 2020 Ruining Li. All rights reserved.
//

#include <iostream>
#include <algorithm>
using namespace std;
int T, n, f[6010], s[6010];
struct edge {
    int x, y, z;
}e[6010];
bool cmp(edge x, edge y) {
    return x.z < y.z;
}
int find(int x) {
    if(f[x] == x) return x;
    return f[x] = find(f[x]);
}
int main() {
    cin >> T;
    while(T--) {
        int ans = 0;
        cin >> n;
        for(int i=1;i<n;++i) cin >> e[i].x >> e[i].y >> e[i].z;
        sort(e+1, e+n, cmp);
        for(int i=1;i<=n;++i) f[i] = i, s[i] = 1;
        for(int i=1;i<n;++i) {
            int fx = find(e[i].x), fy = find(e[i].y);
            ans += (s[fx] * s[fy] - 1) * (e[i].z + 1);
            f[fx] = fy;
            s[fy] += s[fx];
        }
        cout << ans << endl;
    }
    return 0;
}
