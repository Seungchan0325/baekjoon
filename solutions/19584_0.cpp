#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const ll MAXN = 2e5;

ll n, m;
ll cities[MAXN];
vector<tuple<ll, ll, ll>> edges;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> n >> m;
    for(ll i = 0; i < n; i++) {
        ll x, y;
        cin >> x >> y;
        cities[i] = y;
    }
    for(ll i = 0; i < m; i++) {
        ll u, v, c;
        cin >> u >> v >> c;
        u--; v--;
        edges.emplace_back(u, v, c);
    }

    vector<ll> vec(cities, cities + n);
    sort(vec.begin(), vec.end());
    vec.erase(unique(vec.begin(), vec.end()), vec.end());

    vector<ll> vv(vec.size() + 1);
    for(auto [u, v, c] : edges) {
        if(cities[u] > cities[v]) swap(u, v);
        ll start = lower_bound(vec.begin(), vec.end(), cities[u]) - vec.begin();
        ll end = lower_bound(vec.begin(), vec.end(), cities[v]) - vec.begin();
        vv[start] += c;
        vv[end + 1] -= c;
    }

    ll ans = vv[0];
    for(ll i = 1; i <= vec.size(); i++) {
        vv[i] += vv[i - 1];
        ans = max(vv[i], ans);
    }
    cout << ans;
}