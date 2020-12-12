//
//  main.cpp
//  扑克牌 CH3803
//
//  Created by Ruining Li on 2020/3/18.
//  Copyright © 2020 Ruining Li. All rights reserved.
//

#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
double f[16][16][16][16][5][5];
int s[4];
double min4(double a, double b, double c, double d) {
    return min(a,min(b,min(c,d)));
}
double dfs(int a, int b, int c, int d, int x, int y) {
    if(f[a][b][c][d][x][y]<=80) return f[a][b][c][d][x][y];
    if(a+(x==0)+(y==0)>=s[0] && b+(x==1)+(y==1)>=s[1] && c+(x==2)+(y==2)>=s[2] && d+(x==3)+(y==3)>=s[3])
        return f[a][b][c][d][x][y] = 0;
    int sum = 54-a-b-c-d-(x!=4)-(y!=4);
    double e = 0;
    if(a<13) e += (dfs(a+1,b,c,d,x,y)+1)*(13-a)/sum;
    if(b<13) e += (dfs(a,b+1,c,d,x,y)+1)*(13-b)/sum;
    if(c<13) e += (dfs(a,b,c+1,d,x,y)+1)*(13-c)/sum;
    if(d<13) e += (dfs(a,b,c,d+1,x,y)+1)*(13-d)/sum;
    if(x==4) e += (min4(dfs(a,b,c,d,0,y),dfs(a,b,c,d,1,y),dfs(a,b,c,d,2,y),dfs(a,b,c,d,3,y))+1)/sum;
    if(y==4) e += (min4(dfs(a,b,c,d,x,0),dfs(a,b,c,d,x,1),dfs(a,b,c,d,x,2),dfs(a,b,c,d,x,3))+1)/sum;
    return f[a][b][c][d][x][y] = e;
}
int main() {
    for(int i=0;i<4;i++) cin >> s[i];
    if(s[0]+s[1]+s[2]+s[3]>54 || max(s[0]-13,0)+max(s[1]-13,0)+max(s[2]-13,0)+max(s[3]-13,0)>2) {
        puts("-1.000");
        return 0;
    }
    memset(f, 80, sizeof(f));
    double ans = dfs(0,0,0,0,4,4);
    if(ans>80) puts("-1.000");
    else printf("%.3f\n",(int)(ans*1000+0.5)/1000.0);
    return 0;
}
