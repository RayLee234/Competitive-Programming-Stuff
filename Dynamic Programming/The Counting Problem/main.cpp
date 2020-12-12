//
//  main.cpp
//  The Counting Problem POJ2282
//
//  Created by Ruining Li on 2020/7/23.
//  Copyright © 2020 Ruining Li. All rights reserved.
//

#include <iostream>
#include <cstring>
using namespace std;
int a, b, f[10][10], pow[10] = {1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000}, l[10], r[10];
void init() {
    for(int i=1;i<10;++i) f[1][i] = 1;
    for(int i=2;i<10;++i) {
        for(int j=1;j<10;++j) {
            for(int k=1;k<i;++k) f[i][j] += 9 * f[k][j];
            f[i][j] += pow[i-1];
        }
        for(int k=0;k<i;++k) f[i][0] += 9 * (f[k][0] + (i-k-1) * (pow[k] - pow[k-1]));
    }
}
void solveL(int x) {
    int d = 0, cnt[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    if(x == 0) { memcpy(l, cnt, sizeof(cnt)); return; }
    while(pow[d] <= x) ++d;
    for(int i=1;i<d;++i)
        for(int j=0;j<10;++j) cnt[j] += f[i][j];
    int cur = x / pow[d-1];
    x %= pow[d-1];
    for(int j=1;j<cur;++j) cnt[j] += pow[d-1];
    for(int j=0;j<10;++j) cnt[j] += (cur-1) * (d-1) * pow[d-2];
    cnt[cur] += x + 1;
    for(int i=d-2;i>=0;--i) {
        cur = x / pow[i];
        x %= pow[i];
        for(int j=0;j<cur;++j) cnt[j] += pow[i];
        for(int j=0;j<10;++j) cnt[j] += cur * i * pow[i-1];
        cnt[cur] += x + 1;
    }
    memcpy(l, cnt, sizeof(cnt));
}
void solveR(int x) {
    int d = 0, cnt[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    while(pow[d] <= x) ++d;
    for(int i=1;i<d;++i)
        for(int j=0;j<10;++j) cnt[j] += f[i][j];
    int cur = x / pow[d-1];
    x %= pow[d-1];
    for(int j=1;j<cur;++j) cnt[j] += pow[d-1];
    for(int j=0;j<10;++j) cnt[j] += (cur-1) * (d-1) * pow[d-2];
    cnt[cur] += x + 1;
    for(int i=d-2;i>=0;--i) {
        cur = x / pow[i];
        x %= pow[i];
        for(int j=0;j<cur;++j) cnt[j] += pow[i];
        for(int j=0;j<10;++j) cnt[j] += cur * i * pow[i-1];
        cnt[cur] += x + 1;
    }
    memcpy(r, cnt, sizeof(cnt));
}
int main() {
    init();
    while(cin >> a >> b) {
        if(a == 0 && b == 0) return 0;
        if(a > b) swap(a, b);
        solveL(a-1), solveR(b);
        for(int i=0;i<10;++i) cout << r[i] - l[i] << ' ';
        cout << endl;
    }
}
