//
//  main.cpp
//  Cutting Game POJ2311
//
//  Created by Ruining Li on 2020/3/19.
//  Copyright © 2020 Ruining Li. All rights reserved.
//

#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
int n,m,f[201][201];
bool flag[201];
int SG(int x, int y) {
    if(f[x][y]!=-1) return f[x][y];
    if(f[y][x]!=-1) return f[y][x];
    memset(flag, 0, sizeof(flag));
    for(int i=2;i<x-1;i++) flag[SG(i,m) xor SG(x-i,m)] = 1;
    for(int j=2;j<y-1;j++) flag[SG(n,j) xor SG(n,y-j)] = 1;
    for(int i=0;;i++)
        if(!flag[i]) return f[x][y] = i;
}
int main() {
    memset(f,-1,sizeof f);
    f[2][2] = f[2][3] = f[3][2] = 0;
    while(scanf("%d%d",&n,&m)!=EOF) {
        if(SG(n,m)==0) puts("LOSE");
        else puts("WIN");
    }
    return 0;
}
