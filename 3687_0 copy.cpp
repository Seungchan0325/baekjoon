#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const ll INF = 1e15;

ll cache[105];
int cost[10] = {6, 2, 5, 5, 4, 5, 6, 3, 7, 6};

ll dp(int remain) {
    ll& ret = cache[remain];
    if(ret != -1) return ret;

    ret = INF;
    for(int i = 0; i < 10; i++) {
        if(remain - cost[i] < 0) continue;
        
        if(remain - cost[i] == 0 && i != 0) ret = min((ll)i, ret);
        else ret = min(10*dp(remain - cost[i]) + i, ret);
    }

    return ret;
}

int main() {
    memset(cache, -1, sizeof(cache));
    int tc; cin >> tc;
    while(tc--) {
        int n; cin >> n;

        cout << dp(n) << " ";

        if(n % 2 == 1) {
            cout << '7';
            n -= 3;
        }

        while(n > 0) {
            cout << '1';
            n -= 2;
        }
        cout << "\n";
    }
}