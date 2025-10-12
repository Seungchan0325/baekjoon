#include <bits/stdc++.h>

using namespace std;

using ll = long long;

ll n, t;

int main()
{
    cin >> n >> t;

    ll mx = -1e18;
    ll ans = 0;
    vector<pair<ll, ll>> v(n);
    for(auto&[x,h]:v)cin>>x>>h;
    sort(v.begin(), v.end());
    for(auto[x,h]:v){
        ans += clamp(-t*x+mx, 0LL, h);
        mx = max(t*x+h, mx);
    }
    cout << ans << "\n";
}