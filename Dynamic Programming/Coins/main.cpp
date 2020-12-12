//
//  main.cpp
//  Coins POJ1742
//
//  Created by Ruining Li on 2020/5/15.
//  Copyright © 2020 Ruining Li. All rights reserved.
//

#include <iostream>
#include <cstring>
using namespace std;
int n, m, a[101], c[101], used[100001];
bool f[100001];
int main() {
    while(cin >> n >> m) {
        if(n == 0) return 0;
        for(int i=1;i<=n;++i) cin >> a[i];
        for(int i=1;i<=n;++i) cin >> c[i];
        memset(f, 0, sizeof(f));
        f[0] = 1;
        for(int i=1;i<=n;++i) {
            memset(used, 0, sizeof(used));
            for(int j=a[i];j<=m;++j)
                if(!f[j] && f[j-a[i]] && used[j-a[i]] < c[i]) f[j] = 1, used[j] = used[j-a[i]] + 1;
        }
        int ans = 0;
        for(int i=1;i<=m;++i) ans += f[i];
        cout << ans << endl;
    }
    return 0;
}
