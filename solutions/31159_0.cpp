#include <bits/stdc++.h>

using namespace std;

using ll = long long;

int main()
{
    ll n;
    cin >> n;
    vector<tuple<int, int, int>> v;
    for(ll i = 0; i < 2*n; i++) {
        ll a, b;
        cin >> a >> b;
        if(a < b) swap(a, b);
        v.emplace_back(a+b, a, b);
    }
    sort(v.begin(), v.end());
    ll ans = 0;
    for(int i = 0; i < n; i++) {
        ans -= get<2>(v[i]);
        ans += get<1>(v[i+n]);
    }
    cout << ans;
}