#include <bits/stdc++.h>

using namespace std;

using ll = long long;

ll com1(ll n, ll a, ll b, ll c, ll d)
{
    ll ret = 1e18;
    for(ll i = 0; i < 100000; i++) {
        ll m = n - a * i;
        ll j = (m + c - 1) / c;
        ret = min(ret, max(b*i, 0LL)+max(d*j, 0LL));
    }
    return ret;
}

int main()
{
    ll N, A, B, C, D;
    cin >> N >> A >> B >> C >> D;
    ll ans = min({com1(N, A, B, C, D), com1(N, C, D, A, B)});
    cout << ans;
}