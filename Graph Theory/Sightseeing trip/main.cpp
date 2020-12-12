//
//  main.cpp
//  Sightseeing trip POJ1734
//
//  Created by Ruining Li on 2020/8/10.
//  Copyright © 2020 Ruining Li. All rights reserved.
//

#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>
using namespace std;
int n, m, ans = 9999999, g[101][101], d[101][101], pos[101][101];
vector <int> path;
void get_path(int x, int y) {
    int k = pos[x][y];
    if(k == 0) return;
    get_path(x, k);
    path.push_back(k);
    get_path(k, y);
}
int main() {
    scanf("%d %d", &n, &m);
    for(int i=1;i<=n;++i) for(int j=1;j<=n;++j) g[i][j] = 9999999;
    for(int i=1;i<=n;++i) g[i][i] = 0;
    for(int i=1;i<=m;++i) {
        int x, y, z; scanf("%d %d %d", &x, &y, &z);
        g[x][y] = g[y][x] = min(g[x][y], z);
    }
    memcpy(d, g, sizeof(g));
    for(int k=1;k<=n;++k) {
        for(int i=1;i<k;++i)
            for(int j=i+1;j<k;++j)
                if(ans > d[i][j] + g[j][k] + g[k][i]) {
                    ans = d[i][j] + g[j][k] + g[k][i];
                    path.clear();
                    path.push_back(i);
                    get_path(i, j);
                    path.push_back(j);
                    path.push_back(k);
                }
        for(int i=1;i<=n;++i)
            for(int j=1;j<=n;++j)
                if(d[i][j] > d[i][k] + d[k][j]) {
                    d[i][j] = d[i][k] + d[k][j];
                    pos[i][j] = k;
                }
    }
    if(ans == 9999999) puts("No solution.");
    else for(int i=0;i<path.size();++i) printf("%d ", path[i]);
    return 0;
}
