//
//  main.cpp
//  Watchcow POJ2230
//
//  Created by Ruining Li on 2020/10/8.
//  Copyright © 2020 Ruining Li. All rights reserved.
//

#include <iostream>
using namespace std;
int n, m, ver[100010], Next[100010], head[10010], tot = 1;
int stack[100010], ans[100010], top, cnt;
void add(int x, int y) {
    ver[++tot] = y, Next[tot] = head[x], head[x] = tot;
}
void euler() {
    stack[++top] = 1;
    while(top > 0) {
        int x = stack[top], y = ver[head[x]];
        if(y == 0) {
            top--;
            ans[++cnt] = x;
        }
        else {
            head[x] = Next[head[x]];
            stack[++top] = y;
        }
    }
}
int main() {
    cin >> n >> m;
    for(int i=1;i<=m;++i) {
        int x, y; cin >> x >> y;
        add(x, y), add(y, x);
    }
    euler();
    for(int i=cnt;i;i--) cout << ans[i] << endl;
    return 0;
}
