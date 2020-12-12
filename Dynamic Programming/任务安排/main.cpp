//
//  main.cpp
//  Batch Scheduling & 任务安排 POJ1180 & LUOGU5785
//
//  Created by Ruining Li on 2020/7/13.
//  Copyright © 2020 Ruining Li. All rights reserved.
//

#include <iostream>
#include <cstring>
#define ll long long
using namespace std;
ll n, s, t[300010], sumT[300010], c[300010], sumC[300010], f[300010], q[300010], L, R = -1;
int main() {
    cin >> n >> s;
    for(int i=1;i<=n;++i) cin >> t[i] >> c[i], sumT[i] = sumT[i-1] + t[i], sumC[i] = sumC[i-1] + c[i];
    memset(f, 15, sizeof(f));
    f[0] = s * sumC[n];
    q[++R] = 0;
    for(int i=1;i<=n;++i) {
        ll k = sumT[i], l = L, r = R, x = L;
        while(l <= r) {
            int mid = (l+r+1) >> 1;
            if(mid - 1 < L) { x = mid; break; }
            if(f[q[mid]]-f[q[mid-1]] < k * (sumC[q[mid]]-sumC[q[mid-1]])) x = mid, l = mid + 1;
            else r = mid - 1;
        }
        f[i] = f[q[x]] + s * (sumC[n] - sumC[i]) + sumT[i] * (sumC[i] - sumC[q[x]]);
        while(L < R && (f[i] - f[q[R]]) * (sumC[q[R]] - sumC[q[R-1]]) <= (f[q[R]] - f[q[R-1]]) * (sumC[i] - sumC[q[R]])) --R;
        q[++R] = i;
    }
    cout << f[n] << endl;
    return 0;
}
