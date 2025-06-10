#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int mod = 1e9 + 7;

const int MAXN = 10101010;

ll f[MAXN], inv[MAXN];

ll pw(ll x, ll n)
{
    if(n == 0) return 1;
    if(n&1) return (ll)pw(x, n-1) * x % mod;
    ll half = pw(x, n/2);
    return half * half % mod;
}

int main()
{
    f[0] = 1;
    for(int i = 1; i < MAXN; i++) f[i] = f[i-1] * i % mod;
    inv[MAXN-1] = pw(f[MAXN-1], mod-2);
    for(int i = MAXN-2; i >= 0; i--) inv[i] = inv[i+1] * (i+1) % mod;

    int n, k;
    cin >> n >> k;

    ll ans = 0;
    for(int i = 1; i <= min(n, k); i++) {
        ans += f[k] * inv[i] % mod * inv[k-i] % mod;
        ans %= mod;
    }
    cout << ans;
}