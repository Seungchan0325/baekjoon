#include <bits/stdc++.h>

using namespace std;

using ll = long long;

int main()
{
    int n;
    cin >> n;
    vector<int> l(n);
    vector<int> v;
    for(auto& i : l) cin >> i, v.push_back(i);

    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());

    vector<int> c(v.size());
    for(auto i : l) {
        int idx = lower_bound(v.begin(), v.end(), i) - v.begin();
        c[idx]++;
    }

    map<int, ll> m;
    for(int i = 0; i < v.size(); i++) {
        m[2*v[i]] += (ll)v[i]*v[i]*(c[i]/2);
        for(int j = i+1; j < v.size(); j++) {
            m[v[i] + v[j]] += (ll)v[i]*v[j]*min(c[i], c[j]);
        }
    }

    ll ans = 0;
    for(auto [k, i] : m) ans = max(ans, i);
    cout << ans;
}