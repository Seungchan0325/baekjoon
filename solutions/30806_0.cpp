#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const ll mod = 998'244'353;

const ll MAXN = 1010101;

ll N, fac[MAXN], inv[MAXN];
map<ll, ll> S;

ll pw(ll x, ll n)
{
    if(n == 0) return 1;
    if(n&1) return x * pw(x, n-1) % mod;
    ll half = pw(x, n/2);
    return half * half % mod;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    fac[0] = 1;
    for(int i = 1; i < MAXN; i++) fac[i] = fac[i-1] * i % mod;
    inv[MAXN-1] = pw(fac[MAXN-1], mod-2);
    for(int i = MAXN-2; i >= 0; i--) inv[i] = inv[i+1] * (i+1) % mod;

    cin >> N;
    for(int i = 0; i < N; i++) {
        int k;
        cin >> k;
        for(int j = 0; j < k; j++) {
            int a; cin >> a;
            S[a]++;
        }
    }

    for(int i = 1; i <= N; i++) {
        vector<ll> erased;
        ll ans = 0;
        for(auto [k, j] : S) {
            if(j < i) erased.push_back(k);
            else ans += fac[j] * (inv[j-i] * inv[i] % mod) % mod;
            ans %= mod;
        }
        for(auto k : erased) S.erase(k);
        cout << ans << "\n";
    }
}