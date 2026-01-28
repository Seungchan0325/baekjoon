#ifdef LSC_ENV
#include "grader.cpp"
#endif

#include "squirrel.h"
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
 
const int MAXN = 505050;

ll n, d[MAXN], h[MAXN], w[MAXN];

ll fly(vector<int> D, vector<int> H, vector<int> W, int L, int R) {
    n = D.size();
    for(int i = 1; i < n; i++) {
        if(H[i-1] < D[i]-D[i-1]) return -1;
    }
    for(int i = 0; i < n; i++) {
        d[i+1] = D[i];
        h[i+1] = H[i];
        w[i+1] = W[i];
    }
    d[0] = w[0] = 0;
    h[0] = L;
    h[n+1] = d[n+1] = d[n] + R;
    w[n+1] = 0;
    
    for(int i = n; i >= 0; i--) {
        h[i] += d[i];
        h[i] = min(h[i], h[i+1]);
    }

    ll ans = 0;
    deque<int> dq;
    dq.push_back(0);
    ll height = 0;
    for(int i = 1; i <= n+1; i++) {
        ll dh = d[i]-d[i-1];
        while(dh) {
            assert(dq.size());
            int j = dq.front();
            if(height == h[j]) {
                dq.pop_front();
                assert(dq.size());
                continue;
            }
            int x = min(h[j]-height, dh);
            dh -= x;
            ans += x * w[j];
            height += x;
        }
        while(dq.size() && w[dq.back()] >= w[i]) dq.pop_back();
        dq.push_back(i);
    }
    return ans;
}
