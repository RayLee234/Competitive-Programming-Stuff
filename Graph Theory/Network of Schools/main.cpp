//
//  main.cpp
//  Network of Schools POJ1236
//
//  Created by Ruining Li on 2020/10/8.
//  Copyright © 2020 Ruining Li. All rights reserved.
//

#include <iostream>
#include <stack>
using namespace std;
int n, m, ver[20010], Next[20010], head[101], tot, c[101], dfn[101], low[101], cnt, in[101], out[101], A, B, t;
bool vis[101];
stack <int> S;
void add(int x, int y) {
    ver[++tot] = y, Next[tot] = head[x], head[x] = tot;
}
void tarjan(int x) {
    low[x] = dfn[x] = ++t;
    vis[x] = 1;
    S.push(x);
    for(int i=head[x];i;i=Next[i]) {
        int y = ver[i];
        if(!dfn[y]) {
            tarjan(y);
            low[x] = min(low[x], low[y]);
        }
        else if(vis[y]) low[x] = min(low[x], dfn[y]);
    }
    if(low[x] == dfn[x]) {
        ++cnt;
        while(S.top() != x) {
            c[S.top()] = cnt;
            vis[S.top()] = 0;
            S.pop();
        }
        c[x] = cnt, vis[x] = 0, S.pop();
    }
}
int main() {
    cin >> n;
    for(int x=1;x<=n;++x) {
        int y;
        while(cin >> y) {
            if(!y) break;
            add(x, y);
        }
    }
    for(int i=1;i<=n;++i) if(!dfn[i]) tarjan(i);
    for(int x=1;x<=n;++x)
        for(int j=head[x];j;j=Next[j]) {
            int y = ver[j];
            if(c[x] == c[y]) continue;
            ++in[c[y]], ++out[c[x]];
        }
    for(int i=1;i<=cnt;++i) {
        if(!in[i]) ++A;
        if(!out[i]) ++B;
    }
    cout << A << endl;
    if(cnt == 1) cout << 0 << endl;
    else cout << max(A, B) << endl;
    return 0;
}
