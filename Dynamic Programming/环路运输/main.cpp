//
//  main.cpp
//  环路运输 CH5501
//
//  Created by Ruining Li on 2020/6/18.
//  Copyright © 2020 Ruining Li. All rights reserved.
//

#include <iostream>
#include <queue>
using namespace std;
int n, a[2000010], ans;
deque < pair<int,int> > q;
int main() {
    cin >> n;
    for(int i=1;i<=n;++i) cin >> a[i], a[i+n] = a[i];
    q.push_back(make_pair(2 + a[2], 2));
    for(int i=3;i<=1+n/2;++i) {
        while(!q.empty() && q.back().first <= i+a[i]) q.pop_back();
        q.push_back(make_pair(i + a[i], i));
    }
    for(int i=1;i<=n;++i) {
        ans = max(ans, q.front().first - i + a[i]);
        while(!q.empty() && q.front().second == i+1) q.pop_front();
        while(!q.empty() && q.back().first <= i+1+n/2 + a[i+1+n/2]) q.pop_back();
        q.push_back(make_pair(i+1+n/2 + a[i+1+n/2], i+1+n/2));
    }
    cout << ans << endl;
    return 0;
}
