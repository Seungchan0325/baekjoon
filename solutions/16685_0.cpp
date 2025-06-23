#include <bits/stdc++.h>

using namespace std;

using ll = long long;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    int n;
    cin >> n;
    ll p; cin >> p;
    vector<ll> v;
    for(int i = 2; i <= n; i++) {
        ll k; cin >> k;
        v.push_back(k^p);
        p = k;
    }

    ll ans = 0;
    for(int i = 60; i >= 0; i--) {
        ll x = 0;
        for(ll j : v) {
            if(j&(1LL<<i)) {
                x = j;
                break;
            }
        }

        if(x) {
            if(~ans & (1LL<<i))
                ans ^= x;
            for(ll& j : v) {
                if(j&(1LL<<i)) {
                    j ^= x;
                }
            }
        }
    }

    cout << ans;
}