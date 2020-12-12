//
//  main.cpp
//  开车旅行 LUOGU1081
//
//  Created by Ruining Li on 2020/6/26.
//  Copyright © 2020 Ruining Li. All rights reserved.
//

#include <iostream>
#include <cstdio>
#include <set>
#include <cmath>
#define ll long long
using namespace std;
set < pair<int,int> > s, t;
int n, h[100010], ga[100010], gb[100010], f[18][100010][2], m;
ll da[18][100010][2], db[18][100010][2];
int dist(int i, int j) {
    return abs(h[i] - h[j]);
}
void init() {
    for(int i=1;i<=n;++i) f[0][i][0] = ga[i], f[0][i][1] = gb[i];
    for(int i=1;i<=n;++i) {
        if(f[0][i][0] == -1) f[1][i][0] = -1;
        else f[1][i][0] = f[0][f[0][i][0]][1];
        if(f[0][i][1] == -1) f[1][i][1] = -1;
        else f[1][i][1] = f[0][f[1][i][1]][0];
    }
    for(int i=2;i<=17;++i)
        for(int j=1;j<=n;++j) {
            if(f[i-1][j][0] == -1) f[i][j][0] = -1;
            else f[i][j][0] = f[i-1][f[i-1][j][0]][0];
            if(f[i-1][j][1] == -1) f[i][j][1] = -1;
            else f[i][j][1] = f[i-1][f[i-1][j][1]][1];
        }
    for(int i=1;i<=n;++i) {
        if(f[0][i][0] != -1) da[0][i][0] = dist(i, f[0][i][0]);
        if(f[0][i][1] != -1) db[0][i][1] = dist(i, f[0][i][1]);
    }
    for(int i=1;i<=n;++i) {
        if(f[1][i][0] != -1) da[1][i][0] = da[0][i][0], db[1][i][0] = db[0][f[0][i][0]][1];
        if(f[1][i][1] != -1) db[1][i][1] = db[0][i][1], da[1][i][1] = da[0][f[0][i][1]][0];
    }
    for(int i=2;i<=17;++i)
        for(int j=1;j<=n;++j) {
            if(f[i][j][0] != -1) da[i][j][0] = da[i-1][j][0] + da[i-1][f[i-1][j][0]][0], db[i][j][0] = db[i-1][j][0] + db[i-1][f[i-1][j][0]][0];
            if(f[i][j][1] != -1) da[i][j][1] = da[i-1][j][1] + da[i-1][f[i-1][j][1]][1], db[i][j][1] = db[i-1][j][1] + db[i-1][f[i-1][j][1]][1];
        }
}
int main() {
    scanf("%d", &n);
    for(int i=1;i<=n;++i) scanf("%d", &h[i]);
    for(int i=n;i>0;--i) {
        set< pair<int,int> >::iterator itup = s.upper_bound(make_pair(h[i], i)), itlow = t.upper_bound(make_pair(-h[i],i));
        if(itup == s.end() && itlow == t.end()) ga[i] = gb[i] = -1;
        else if(itup == s.end()) {
            gb[i] = (*itlow).second;
            set< pair<int,int> >::iterator itlowlow = t.upper_bound(*itlow);
            if(itlowlow == t.end()) ga[i] = -1;
            else ga[i] = (*itlowlow).second;
        }
        else if(itlow == t.end()) {
            gb[i] = (*itup).second;
            set< pair<int,int> >::iterator itupup = s.upper_bound(*itup);
            if(itupup == s.end()) ga[i] = -1;
            else ga[i] = (*itupup).second;
        }
        else {
            int choice;
            if((*itlow).first + h[i] <= (*itup).first - h[i]) gb[i] = (*itlow).second, choice = -1;
            else gb[i] = (*itup).second, choice = 1;
            set< pair<int,int> >::iterator itlowlow = t.upper_bound(*itlow), itupup = s.upper_bound(*itup);
            if(itlowlow == t.end() && itupup == s.end()) ga[i] = choice < 0 ? (*itup).second : (*itlow).second;
            else if(itlowlow == t.end()) {
                if(choice < 0) ga[i] = (*itup).second;
                else ga[i] = (*itlow).first + h[i] <= (*itupup).first - h[i] ? (*itlow).second : (*itupup).second;
            }
            else if(itupup == s.end()) {
                if(choice > 0) ga[i] = (*itlow).second;
                else ga[i] = (*itlowlow).first + h[i] <= (*itup).first - h[i] ? (*itlowlow).second : (*itup).second;
            }
            else {
                if(choice > 0) ga[i] = (*itlow).first + h[i] <= (*itupup).first - h[i] ? (*itlow).second : (*itupup).second;
                if(choice < 0) ga[i] = (*itlowlow).first + h[i] <= (*itup).first - h[i] ? (*itlowlow).second : (*itup).second;
            }
        }
        s.insert(make_pair(h[i],i)), t.insert(make_pair(-h[i],i));
    }
    init();
    int x;
    scanf("%d", &x);
    double ratio = 2e9; int startCity = 0; h[0] = -2e9;
    for(int i=1;i<=n;++i) {
        int /*nowPerson = 0,*/ nowCity = i, disA = 0, disB = 0;
        for(int j=17;j>=0;--j)
            if(f[j][nowCity][0] != -1 && disA + disB + da[j][nowCity][0] + db[j][nowCity][0] <= x) {
                disA += da[j][nowCity][0], disB += db[j][nowCity][0];
                nowCity = f[j][nowCity][0];
            }
        if(disB == 0 && ratio == 2e9 && h[startCity] < h[i]) { startCity = i; continue; }
        if((double)disA / disB < ratio) ratio = (double)disA / disB, startCity = i;
        else if((double)disA / disB == ratio && h[startCity] < h[i]) startCity = i;
    }
    printf("%d\n", startCity);
    scanf("%d", &m);
    while(m--) {
        int startCity; scanf("%d %d", &startCity, &x);
        int nowCity = startCity, disA = 0, disB = 0;
        for(int i=17;i>=0;--i)
            if(f[i][nowCity][0] != -1 && disA + disB + da[i][nowCity][0] + db[i][nowCity][0] <= x) {
                disA += da[i][nowCity][0], disB += db[i][nowCity][0];
                nowCity = f[i][nowCity][0];
            }
        printf("%d %d\n", disA, disB);
    }
    return 0;
}
