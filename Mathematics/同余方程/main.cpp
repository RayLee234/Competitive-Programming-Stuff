//
//  main.cpp
//  同余方程 NOIP2012
//
//  Created by Ruining Li on 2020/3/13.
//  Copyright © 2020 Ruining Li. All rights reserved.
//

#include <iostream>
using namespace std;
int a,b,s,t;
int exgcd(int p, int q, int &x, int &y) {
    if(q==0) {
        x = 1; y = 0;
        return p;
    }
    int d = exgcd(q,p%q,x,y);
    int z = x; x = y; y = z-(p/q)*y;
    return d;
}
int main() {
    cin >> a >> b;
    exgcd(a,b,s,t);
    while(s<=0) s+=b;
    cout << s << endl;
    return 0;
}
