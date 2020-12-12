//
//  main.cpp
//  Folding POJ2176
//
//  Created by Ruining Li on 2020/6/21.
//  Copyright © 2020 Ruining Li. All rights reserved.
//

#include <iostream>
#include <string>
#include <cstring>
using namespace std;
string s, ans[101][101];
int f[101][101], mul[101][101], l;
bool judge(int x, int y, int num) {
    if((y-x+1) % num != 0) return 0;
    for(int i=x;i<x + (y-x+1)/num;++i)
        for(int j=i;j<=y;j+=(y-x+1)/num)
            if(s[j-1] != s[i-1]) return 0;
    return 1;
}
int digits(int x) {
    int r = 0;
    while(x > 0) {
        ++r;
        x /= 10;
    }
    return r;
}
string toString(int x) {
    string r, z; r.clear();
    while(x > 0) {
        r += x % 10 + '0';
        x /= 10;
    }
    for(int i=r.length()-1;i>=0;--i) z += r[i];
    return z;
}
int main() {
    cin >> s;
    l = s.length();
    memset(f, 5, sizeof(f));
    for(int i=1;i<=l;++i) f[i][i] = mul[i][i] = 1, ans[i][i] = s[i-1];
    for(int k=2;k<=l;++k)
        for(int i=1;i<=l-k+1;++i) {
            int j = i + k - 1;
            for(int num=2;num<=k;++num)
                if(judge(i, j, num)) {
                    int r = i + (j-i+1)/num - 1;
                    if(mul[i][r] == 1) {
                        if(f[i][j] > f[i][r] + 2 + digits(num)) {
                            f[i][j] = f[i][r] + 2 + digits(num);
                            mul[i][j] = num;
                            ans[i][j] = toString(num);
                            ans[i][j] += '(';
                            ans[i][j] += ans[i][r];
                            ans[i][j] += ')';
                        }
                    }
                    else {
                        if(f[i][j] > f[i][r] + digits(num * mul[i][r]) - digits(mul[i][r])) {
                            f[i][j] = f[i][r] + digits(num * mul[i][r]) - digits(mul[i][r]);
                            mul[i][j] = num * mul[i][r];
                            ans[i][j] = toString(mul[i][j]);
                            ans[i][j] += ans[i][r].substr(digits(mul[i][r]), ans[i][r].length() - digits(mul[i][r]));
                        }
                    }
                }
            for(int mid=i;mid<j;++mid)
                if(f[i][j] > f[i][mid] + f[mid+1][j]) {
                    f[i][j] = f[i][mid] + f[mid+1][j];
                    mul[i][j] = 1;
                    ans[i][j] = ans[i][mid];
                    ans[i][j] += ans[mid+1][j];
                }
        }
    cout << ans[1][l] << endl;
    return 0;
}
