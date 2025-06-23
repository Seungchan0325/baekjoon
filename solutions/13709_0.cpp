#include <bits/stdc++.h>

using namespace std;

using ll = long long;

int main()
{
    int n; cin >> n;
    vector<ll> a(n);
    for(auto& i : a) cin >> i;

    ll ans = 0;
    for(int i = 60; i >= 0; i--) {
        ll x = 0;
        for(auto j : a) {
            if(j&(1LL<<i)) {
                x = j;
                break;
            }
        }

        if(x) {
            if(~ans & (1LL<<i))
                ans ^= x;
            for(auto& j : a) {
                if(j&(1LL<<i)) {
                    j ^= x;
                }
            }
        }
    }

    cout << ans << "\n";
}