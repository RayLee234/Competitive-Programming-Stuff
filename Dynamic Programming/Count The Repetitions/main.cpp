//
//  main.cpp
//  Count The Repetitions CH5702
//
//  Created by Ruining Li on 2020/6/26.
//  Copyright © 2020 Ruining Li. All rights reserved.
//

#include <iostream>
#include <string>
#define ll long long
using namespace std;
int n, m, ls, lt;
ll f[101][28];
string s, t;
bool valid() {
    for(int i=0;i<lt;++i) {
        bool ok = 0;
        for(int j=0;j<ls;++j)
            if(s[j] == t[i]) ok = 1;
        if(!ok) return 0;
    }
    return 1;
}
int init(int x) {
    int p = x, q = 0, len = 0;
    while(q < lt) {
        if(s[p] == t[q]) q++;
        p = (p+1) % ls; len++;
    }
    return len;
}
int main() {
    while(cin >> t >> m >> s >> n) {
        ls = s.length(), lt = t.length();
        if(!valid()) { puts("0"); continue; }
        for(int i=0;i<ls;++i) f[i][0] = init(i);
        for(int j=1;j<=27;++j)
            for(int i=0;i<ls;++i) f[i][j] = f[i][j-1] + f[(i+f[i][j-1])%ls][j-1];
        int now = 0, pos = 0, ans = 0;
        for(int j=27;j>=0;j--)
            if(now + f[pos][j] <= n * ls) {
                now += f[pos][j];
                ans += (1<<j);
                pos = now % ls;
            }
        cout << ans / m << endl;
    }
    return 0;
}
