//
//  main.cpp
//  自然数拆分Lunatic版 CH5202
//
//  Created by Ruining Li on 2020/5/15.
//  Copyright © 2020 Ruining Li. All rights reserved.
//

#include <iostream>
using namespace std;
int n;
unsigned int f[4001], mod = 2147483648u;
int main() {
    cin >> n;
    f[0] = 1;
    for(int i=1;i<=n;++i)
        for(int j=i;j<=n;++j) f[j] = (f[j] + f[j-i]) % mod;
    cout << (f[n]>0 ? f[n]-1 : mod) << endl;
    return 0;
}
