//
//  main.cpp
//  BUY LOW, BUY LOWER POJ1952
//
//  Created by Ruining Li on 2020/6/19.
//  Copyright © 2020 Ruining Li. All rights reserved.
//

#include <iostream>
#include <map>
#include <vector>
using namespace std;
long long n, a[5010], f[5010], g[5010], len, cnt;
map <long long, bool> s;
vector <long long> c;
int main() {
    cin >> n;
    for(int i=1;i<=n;++i) cin >> a[i];
    g[1] = f[1] = 1;
    for(int i=2;i<=n;++i) {
        f[i] = g[i] = 1;
        for(int j=i-1;j>0;--j)
            if(a[j] > a[i]) {
                if(f[j] + 1 > f[i]) f[i] = f[j] + 1, g[i] = g[j], s[a[j]] = true, c.push_back(a[j]);
                else if(f[j] + 1 == f[i] && s[a[j]] == false) g[i] += g[j], s[a[j]] = true, c.push_back(a[j]);
            }
        for(int j=0;j<c.size();++j) s[c[j]] = false;
        c.clear();
    }
    for(int i=1;i<=n;++i) len = max(len, f[i]);
    for(int i=n;i>0;--i) if(f[i] == len && s[a[i]] == false) cnt += g[i], s[a[i]] = true;
    cout << len << ' ' << cnt << endl;
    return 0;
}
