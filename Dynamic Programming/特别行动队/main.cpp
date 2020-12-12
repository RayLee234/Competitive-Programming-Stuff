//
//  main.cpp
//  特别行动队 LUOGU3628
//
//  Created by Ruining Li on 2020/7/27.
//  Copyright © 2020 Ruining Li. All rights reserved.
//

#include <iostream>
#define int long long
using namespace std;
int n, a, b, c, p[1000010], s[1000010], f[1000010], q[1000010];
signed main() {
    cin >> n >> a >> b >> c;
    for(int i=1;i<=n;++i) cin >> p[i], s[i] = s[i-1] + p[i];
    int L = 0, R = -1;
    q[++R] = 0;
    for(int i=1;i<=n;++i) {
        while(L < R && f[q[L+1]]+a*s[q[L+1]]*s[q[L+1]]-b*s[q[L+1]]-f[q[L]]-a*s[q[L]]*s[q[L]]+b*s[q[L]] > 2*a*s[i]*(s[q[L+1]]-s[q[L]])) ++L;
        f[i] = f[q[L]] + a * (s[i]-s[q[L]]) * (s[i]-s[q[L]]) + b * (s[i] - s[q[L]]) + c;
        while(L < R && (f[q[R]]+a*s[q[R]]*s[q[R]]-b*s[q[R]]-f[q[R-1]]-a*s[q[R-1]]*s[q[R-1]]+b*s[q[R-1]]) * (s[i]-s[q[R]]) <= (f[i]+a*s[i]*s[i]-b*s[i]-f[q[R]]-a*s[q[R]]*s[q[R]]+b*s[q[R]]) * (s[q[R]]-s[q[R-1]])) --R;
        q[++R] = i;
    }
    cout << f[n] << endl;
    return 0;
}
