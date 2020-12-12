//
//  main.cpp
//  Fotile模拟赛L CH4913
//
//  Created by Ruining Li on 2020/4/7.
//  Copyright © 2020 Ruining Li. All rights reserved.
//

#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
#define ll long long
using namespace std;
int n,m,s[12010],root[12010],last[2000010],trie[2000010][2],tot,ans;
int pos[12010],st[150],ed[150],cnt,f[150][150];
inline int read() {
    int x = 0, sign = 1; char c = getchar();
    while(c < '0' || c > '9') {
        if(c == '-') sign = -1;
        c = getchar();
    }
    while(c >= '0' && c <= '9') x = (x<<3)+(x<<1)+c-'0', c = getchar();
    return x * sign;
}
inline void insert(int i, int k, int p, int q) {
    if(k < 0) {
        last[q] = i;
        return;
    }
    int c = s[i] >> k & 1;
    if(p) trie[q][c^1] = trie[p][c^1];
    trie[q][c] = ++tot;
    insert(i, k-1, trie[p][c], trie[q][c]);
    last[q] = max(last[trie[q][0]], last[trie[q][1]]);
}
inline int ask(int now, int k, int val, int limit) {
    if(k < 0) return s[last[now]] xor val;
    int c = val >> k & 1;
    if(k == 31) {
        if(trie[now][c] > 0 && last[trie[now][c]] >= limit) return ask(trie[now][c], k-1, val, limit);
        else return 0;
    }
    if(trie[now][c^1] > 0 && last[trie[now][c^1]] >= limit) return ask(trie[now][c^1], k-1, val, limit);
    else return ask(trie[now][c], k-1, val, limit);
}
inline void init() {
    cnt = (int)sqrt(n+1);
    for(register int i=1;i<=cnt;++i) st[i] = (i-1) * cnt, ed[i] = i * cnt - 1;
    if(ed[cnt] < n) cnt++, ed[cnt] = n, st[cnt] = ed[cnt-1]+1;
    for(register int i=1;i<=cnt;++i)
        for(register int j=st[i];j<=ed[i];++j) pos[j] = i;
    memset(f, 0, sizeof(f));
    for(register int i=1;i<=cnt;++i)
        for(register int j=st[i]+1;j<=ed[i];++j) f[i][i] = max(f[i][i], ask(root[j-1], 31, s[j], st[i]));
    for(register int k=1;k<cnt;++k)
        for(register int i=1;i<=cnt-k;++i) {
            int j = i+k;
            f[i][j] = max(f[i+1][j], f[i][j-1]);
            for(register int p=st[j];p<=ed[j];++p) f[i][j] = max(f[i][j], ask(root[ed[i]], 31, s[p], st[i]));
        }
}
int main() {
    n = read(), m = read();
    root[0] = ++tot;
    insert(0, 31, 0, 1);
    for(register int i=1;i<=n;++i) {
        int x = read();
        s[i] = s[i-1] xor x;
        root[i] = ++tot;
        insert(i, 31, root[i-1], root[i]);
    }
    init();
    while(m--) {
        int x, y; scanf("%d %d", &x, &y);
        int l = (x + (ll)ans) % n + 1, r = (y + (ll)ans) % n + 1;
        if(l > r) swap(l,r);
        --l;
        ans = 0;
        if(pos[r] - pos[l] <= 1) {
            for(register int i=l+1;i<=r;++i) ans = max(ans, ask(root[i-1], 31, s[i], l));
        }
        else {
            ans = f[pos[l]+1][pos[r]-1];
            for(register int i=l;i<=ed[pos[l]];++i) ans = max(ans, ask(root[r], 31, s[i], i+1));
            for(register int i=st[pos[r]];i<=r;++i) ans = max(ans, ask(root[i-1], 31, s[i], l));
        }
        printf("%d\n", ans);
    }
}
