//
//  main.cpp
//  任务安排1 CH5A01
//
//  Created by Ruining Li on 2020/7/13.
//  Copyright © 2020 Ruining Li. All rights reserved.
//

#include <iostream>
#include <cstring>
#define ll long long
using namespace std;
int n, s, t[5010], sumT[5010], c[5010], sumC[5010];
ll f[5010];
int main() {
    cin >> n >> s;
    for(int i=1;i<=n;++i) cin >> t[i] >> c[i], sumT[i] = sumT[i-1] + t[i], sumC[i] = sumC[i-1] + c[i];
    memset(f, 15, sizeof(f));
    f[0] = s * sumC[n];
    for(int i=1;i<=n;++i) {
        int k;
        for(int j=0;j<i;++j) {
            if(f[j] + sumT[i] * (sumC[i] - sumC[j]) + s * (sumC[n] - sumC[i]) < f[i]) {
                f[i] = f[j] + sumT[i] * (sumC[i] - sumC[j]) + s * (sumC[n] - sumC[i]);
                k = j;
            }
        }
        cout << f[i] << ' ' << k << endl;
    }
    cout << f[n] << endl;
    return 0;
}
