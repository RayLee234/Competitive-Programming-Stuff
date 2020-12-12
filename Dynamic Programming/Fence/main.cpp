//
//  main.cpp
//  Fence POJ1821
//
//  Created by Ruining Li on 2020/6/28.
//  Copyright © 2020 Ruining Li. All rights reserved.
//

#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;
int n, m, f[101][16001];
struct worker {
    int l, p, s;
}a[101];
bool cmp(worker x, worker y) {
    return x.s < y.s;
}
int calc(int i, int k) {
    return f[i-1][k] - k * a[i].p;
}
int main() {
    cin >> m >> n;
    for(int i=1;i<=n;++i) cin >> a[i].l >> a[i].p >> a[i].s;
    sort(a+1, a+n+1, cmp);
    for(int i=1;i<=n;++i) {
        deque <int> q;
        int l = 1 - a[i].l, r = a[i].s - 1;
        for(int j=max(l,0);j<=r;++j) {
            while(!q.empty() && calc(i, q.back()) <= calc(i, j)) q.pop_back();
            q.push_back(j);
        }
        for(int j=1;j<=m;++j) {
            if(j >= a[i].s && !q.empty()) f[i][j] = j * a[i].p + calc(i, q.front());
            while(!q.empty() && q.front() < j + 1 - a[i].l) q.pop_front();
            f[i][j] = max(f[i][j], max(f[i-1][j], f[i][j-1]));
        }
    }
    cout << f[n][m] << endl;
    return 0;
}
