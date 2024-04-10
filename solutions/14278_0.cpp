#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const ll MOD = 1e9 + 7;

int w, h;
ll cache[1<<10][11];

ll f(int prv, int cur, int idx, int height);

ll dp(int prv, int height)
{
    if(height == 0) return 1;

    ll& ret = cache[prv][height];
    if(ret != -1) return ret;

    ret = f(prv, 0, 0, height);

    return ret;
}

ll f(int prv, int cur, int idx, int height)
{
    if(idx == w+1) return dp(cur, height-1);
    ll ret = f(prv, cur, idx+1, height);
    if(prv & (1<<idx)) {
        if(prv & (1<<(idx+2))) ret = (ret + f(prv, cur | (0b111<<idx), idx+3, height)) % MOD;
        if(prv & (1<<(idx+1))) ret = (ret + f(prv, cur | (0b11<<idx), idx+2, height)) % MOD;
        if(prv & (1<<(idx))) ret = (ret + f(prv, cur | (0b1<<idx), idx+1, height)) % MOD;
    }
    return ret;
}

int main()
{
    cin >> w >> h;
    memset(cache, -1, sizeof(cache));

    ll result = dp((1<<w)-1, h);
    cout << result;
}