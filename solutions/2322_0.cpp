#include <bits/stdc++.h>

using namespace std;
using ll = long long;

const ll MAXN = 101010;

ll n, a[MAXN];

vector<tuple<ll, ll, ll>> decomp(vector<ll> v)
{
    ll n = v.size();
    vector<bool> chk(n);
    vector<tuple<ll, ll, ll>> ret;
    for(ll i = 0; i < n; i++) {
        if(chk[i]) continue;

        ll mn = 1e18;
        ll sum = 0;
        ll sz = 0;
        ll j = i;
        while(!chk[j]) {
            chk[j] = true;
            mn = min(mn, a[j]);
            sum += a[j];
            sz++;
            j = v[j];
        }
        ret.emplace_back(mn, sum, sz);
    }
    return ret;
}

int main()
{
    cin >> n;

    ll M = 1e18;
    vector<ll> v; v.reserve(n);
    for(ll i = 0; i < n; i++) {
        cin >> a[i];
        M = min(M, a[i]);
        v.push_back(a[i]);
    }
    sort(v.begin(), v.end());

    vector<ll> dst(n);
    for(ll i = 0; i < n; i++) {
        dst[i] = lower_bound(v.begin(), v.end(), a[i]) - v.begin();
    }
    auto cyc = decomp(dst);

    ll ans = 0;
    for(ll i = 0; i < cyc.size(); i++) {
        auto [m, s, k] = cyc[i];
        ans += min(s + (k - 2) * m, s + m + (k + 1) * M);
    }
    cout << ans;
}