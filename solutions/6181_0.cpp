#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const ll MAXM = 100005;

bool visited[MAXM];
ll M, D, root[MAXM], sz[MAXM];
vector<pair<ll, ll>> v;

ll find(ll u)
{
    if(u == root[u]) return u;
    return root[u] = find(root[u]);
}

void merge(ll u, ll v)
{
    u = find(u);
    v = find(v);
    if(u == v) return;
    root[v] = u;
    sz[u] += sz[v];
}

int main()
{
    cin >> M >> D;
    for(ll i = 0; i < M; i++) {
        ll x, y;
        cin >> x >> y;
        v.emplace_back(x - y, x + y);
    }

    sort(v.begin(), v.end());
    fill(sz, sz + M, 1);
    iota(root, root + M, 0);

    ll l = 0;
    set<pair<ll, ll>> s;
    for(ll i = 0; i < M; i++) {
        while(v[l].first < v[i].first - D) s.erase({v[l].second, l++});
        auto it = s.lower_bound({v[i].second - D, 0});
        if(it != s.end() && it->first <= v[i].second + D) merge(it->second, i);
        it = s.lower_bound({v[i].second + D + 1, 0});
        if(it != s.begin() && v[i].second - D <= prev(it)->first) merge(i, prev(it)->second);
        s.insert({v[i].second, i});
    }

    ll cnt = 0;
    ll mx = -1;
    for(ll i = 0; i < M; i++) {
        ll p = find(i);
        if(!visited[p]) {
            cnt++;
            mx = max(mx, sz[p]);
            visited[p] = true;
        }
    }

    cout << cnt << " " << mx;
}