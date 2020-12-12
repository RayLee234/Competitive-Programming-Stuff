//
//  main.cpp
//  作诗 LUOGU4135
//
//  Created by Ruining Li on 2020/4/8.
//  Copyright © 2020 Ruining Li. All rights reserved.
//

#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
using namespace std;
int n, c, m, a[100010];
int pos[100010], st[400], ed[400], tot;
int cnt[400][100010], s[400][400];
void init() {
    tot = (int)sqrt(n);
    for(int i=1;i<=tot;++i) st[i] = (i-1) * tot + 1, ed[i] = i * tot;
    if(ed[tot] < n) st[tot+1] = ed[tot] + 1, ed[++tot] = n;
    for(int i=1;i<=tot;++i)
        for(int j=st[i];j<=ed[i];++j) pos[j] = i;
    for(int i=st[1];i<=ed[1];++i) ++cnt[1][a[i]];
    for(int i=2;i<=tot;++i) {
        memcpy(cnt[i], cnt[i-1], sizeof(cnt[i-1]));
        for(int j=st[i];j<=ed[i];++j) ++cnt[i][a[j]];
    }
    for(int i=1;i<=tot;++i) {
        for(int j=1;j<=c;++j)
            if(cnt[i][j] - cnt[i-1][j] > 0 && (cnt[i][j] - cnt[i-1][j]) % 2 == 0) ++s[i][i];
        for(int j=i+1;j<=tot;++j) {
            s[i][j] = s[i][j-1];
            for(int k=st[j];k<=ed[j];++k) {
                --cnt[i-1][a[k]];
                if((cnt[j-1][a[k]] - cnt[i-1][a[k]]) % 2 == 0) ++s[i][j];
                else if(cnt[j-1][a[k]] - cnt[i-1][a[k]] != 1) --s[i][j];
            }
            for(int k=st[j];k<=ed[j];++k) ++cnt[i-1][a[k]];
        }
    }
}
int main() {
    scanf("%d %d %d", &n, &c, &m);
    for(int i=1;i<=n;++i) scanf("%d", &a[i]);
    init();
    int ans = 0;
    while(m--) {
        int x,y; scanf("%d %d", &x, &y);
        int l = (x + ans) % n + 1, r = (y + ans) % n + 1;
        if(l > r) swap(l,r);
        int L = pos[l], R = pos[r];
        if(R - L <= 1) {
            ans = 0;
            int temp[100010];
            memset(temp, 0, sizeof(temp));
            for(int i=l;i<=r;++i) {
                ++temp[a[i]];
                if(temp[a[i]] % 2 == 0) ++ans;
                else if(temp[a[i]] != 1) --ans;
            }
        }
        else {
            ans = s[L+1][R-1];
            for(int i=l;i<=ed[L];++i) {
                --cnt[L][a[i]];
                if((cnt[R-1][a[i]] - cnt[L][a[i]]) % 2 == 0) ++ans;
                else if(cnt[R-1][a[i]] - cnt[L][a[i]] != 1) --ans;
            }
            for(int i=st[R];i<=r;++i) {
                --cnt[L][a[i]];
                if((cnt[R-1][a[i]] - cnt[L][a[i]]) % 2 == 0) ++ans;
                else if(cnt[R-1][a[i]] - cnt[L][a[i]] != 1) --ans;
            }
            for(int i=l;i<=ed[L];++i) ++cnt[L][a[i]];
            for(int i=st[R];i<=r;++i) ++cnt[L][a[i]];
        }
        printf("%d\n", ans);
    }
    return 0;
}
