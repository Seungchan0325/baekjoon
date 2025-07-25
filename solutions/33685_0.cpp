#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const ll mod = 998244353;

map<tuple<int, int, array<int, 20>>, ll> cache;

ll pw(ll x, ll n)
{
    ll ans = 1;
    while(n) {
        if(n&1) ans = ans * x % mod;
        x = x * x % mod;
        n>>=1;
    }
    return ans;
}

// ll pw(ll x, ll n)
// {
//     if(n == 0) return 1;
//     if(n&1) return x * pw(x, n-1) % mod;
//     ll half = pw(x, n/2);
//     return half * half % mod;
// }

int N, M, X, Y, H[122];

ll dp(int n, int y, array<int, 20> s, int sum)
{
    sum -= s[0];
    s[0] = 0;
    if(y == 0) return 1;
    if(n == 0) return 0;
    if(cache.contains(tuple(n, y, s))) return cache[tuple(n, y, s)];
    ll& ret = cache[tuple(n, y, s)];
    for(int i = 1; i < 20; i++) {
        if(s[i]) {
            s[i]--;
            s[i-1]++;
            ret = (ret + dp(n-1, y, s, sum)) % mod;
            s[i]++;
            s[i-1]--;
        }
    }
    ret = (ret + dp(n-1, y-1, s, sum)) % mod;
    ret = ret * pw(sum, mod-2) % mod;
    return ret;
}

int main()
{
    cin >> N >> M >> X >> Y;
    for(int i = 1; i <= M; i++) cin >> H[i], H[i] = (H[i] + X - 1) / X;
    Y = (Y + X - 1) / X;
    array<int, 20> a = {};
    for(int i = 1; i <= M; i++) {
        if(H[i] < 20) a[H[i]]++;
    }
    ll ans = dp(N, Y, a, M+1);
    cout << ans << "\n";

    for(auto [k, i] : cache) {
        cout << get<0>(k) << " " << get<1>(k) << " [";
        for(auto j : get<2>(k)) cout << j << ", ";
        cout << "] = " << i << "\n";
    }
}