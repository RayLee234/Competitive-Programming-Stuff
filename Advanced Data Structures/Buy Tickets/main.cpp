//
//  main.cpp
//  Buy Tickets POJ2828
//
//  Created by Ruining Li on 2020/4/2.
//  Copyright © 2020 Ruining Li. All rights reserved.
//

#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
int n, c[200010], t[200010];
struct P {
    int pos, val;
}a[200010];
void add(int x, int v) {
    while(x<=n) {
        c[x] += v;
        x += x & (-x);
    }
}
int ask(int x) {
    int r = 0;
    while(x) {
        r += c[x];
        x -= x & (-x);
    }
    return r;
}
int main() {
    while(scanf("%d",&n)!=EOF) {
        for(int i=1;i<=n;++i) scanf("%d %d", &a[i].pos, &a[i].val), add(i,1);
        memset(t, -1, sizeof(t));
        for(int i=n;i>0;--i) {
            int l = 1, r = n, index;
            while(l<=r) {
                int mid = (l+r)>>1;
                int s = ask(mid-1);
                if(s == a[i].pos && t[mid] == -1) {
                    index = mid;
                    break;
                }
                if(s <= a[i].pos) l = mid + 1;
                else r = mid - 1;
            }
            t[index] = a[i].val;
            add(index, -1);
        }
        for(int i=1;i<=n;++i) printf("%d ",t[i]);
        putchar('\n');
    }
    return 0;
}
