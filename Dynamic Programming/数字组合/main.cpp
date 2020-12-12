//
//  main.cpp
//  数字组合 CH5201
//
//  Created by Ruining Li on 2020/5/15.
//  Copyright © 2020 Ruining Li. All rights reserved.
//

#include <iostream>
using namespace std;
int n,m,a[101],f[10001];
int main() {
    cin >> n >> m;
    for(int i=1;i<=n;++i) cin >> a[i];
    f[0] = 1;
    for(int i=1;i<=n;++i)
        for(int j=m;j>=a[i];--j) f[j] += f[j-a[i]];
    cout << f[m] << endl;
    return 0;
}
