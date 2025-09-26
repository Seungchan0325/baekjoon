#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int MAXN = 202020;
const ll mod = 1e9 + 7;

int n, f[MAXN], appear[MAXN];
ll fac[MAXN], inv[MAXN];

ll pw(ll x, ll n)
{
    ll ret = 1;
    while(n) {
        if(n&1) ret = (ret * x) % mod;
        x = (x * x) % mod;
        n >>= 1;
    }
    return ret;
}

int main()
{
    fac[0] = 1;
    for(int i = 1; i < MAXN; i++) fac[i] = (fac[i-1] * i) % mod;
    inv[MAXN-1] = pw(fac[MAXN-1], mod-2);
    for(int i = MAXN-2; i >= 0; i--) inv[i] = (inv[i+1] * (i+1)) % mod;

    cin >> n;
    for(int i = 1; i <= n; i++) cin >> f[i];
    for(int i = 1; i <= n; i++) appear[f[i]]++;

    ll g = 1;
    for(int i = 1; i <= n; i++) {
        g = (g * fac[appear[i]]) % mod;
    }

    ll h = 1;
    ll remains = n;
    for(int i = 1; i <= n; i++) if(appear[i]) remains--, appear[i]--;
    for(int i = 1; i <= n; i++) {
        if(appear[i]) {
            ll nCr = fac[remains] * inv[appear[i]] % mod * inv[remains - appear[i]] % mod;
            h = h * nCr % mod;
            remains -= appear[i];
        }
    }
    

    ll ans = h * g % mod;
    cout << ans << "\n";
}