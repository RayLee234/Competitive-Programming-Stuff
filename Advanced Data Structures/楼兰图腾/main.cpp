//
//  main.cpp
//  楼兰图腾 CH4201
//
//  Created by Ruining Li on 2020/3/25.
//  Copyright © 2020 Ruining Li. All rights reserved.
//

#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
int n,a[200001],c[200001],l[200001],r[200001];
long long ans1, ans2;
int lowbit(int x) {
    return x&(-x);
}
int sum(int x) {
    int r = 0;
    while(x>0) {
        r += c[x];
        x -= lowbit(x);
    }
    return r;
}
void add(int x) {
    while(x<=n) {
        ++c[x];
        x += lowbit(x);
    }
}
int main() {
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    for(int i=1;i<=n;i++) {
        l[i] = sum(n)-sum(a[i]);
        add(a[i]);
    }
    memset(c, 0, sizeof(c));
    for(int i=n;i>0;i--) {
        r[i] = sum(n)-sum(a[i]);
        add(a[i]);
    }
    memset(c, 0, sizeof(c));
    for(int i=1;i<=n;i++) ans1 += (long long)l[i] * r[i];
    cout << ans1 << ' ';
    for(int i=1;i<=n;i++) {
        l[i] = sum(a[i]);
        add(a[i]);
    }
    memset(c, 0, sizeof(c));
    for(int i=n;i>0;i--) {
        r[i] = sum(a[i]);
        add(a[i]);
    }
    for(int i=1;i<=n;i++) ans2 += (long long)l[i] * r[i];
    cout << ans2 << endl;
    return 0;
}
