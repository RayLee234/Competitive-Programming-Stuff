//
//  main.cpp
//  金字塔 CH5302
//
//  Created by Ruining Li on 2020/5/17.
//  Copyright © 2020 Ruining Li. All rights reserved.
//

#include <iostream>
#include <cstdio>
#include <cstring>
#define ll long long
using namespace std;
char S[350];
int f[301][301], len;
const int mod = 1000000000;
int solve(int l, int r) {
    if(l > r) return 0;
    if(l == r) return 1;
    if(f[l][r] != -1) return f[l][r];
    if(S[r] != S[l]) return f[l][r] = 0;
    int c = 0;
    for(int k=l+2;k<=r;++k) c = (c + (ll)solve(l+1, k-1) * solve(k, r)) % mod;
    return f[l][r] = c;
}
int main() {
    scanf("%s", S+1);
    len = strlen(S+1);
    memset(f, -1, sizeof(f));
    cout << solve(1, len) << endl;
    return 0;
}
