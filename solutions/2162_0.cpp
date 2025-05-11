#include <bits/stdc++.h>

using namespace std;

using ll = long long;

struct DSU {
    ll N;
    vector<ll> root;
    DSU(ll _N) : N(_N) {
        root.resize(N);
        iota(root.begin(), root.end(), 0);
    }

    ll find(ll x)
    {
        if(root[x] == x) return x;
        return root[x] = find(root[x]);
    }

    void merge(ll x, ll y)
    {
        x = find(x);
        y = find(y);
        root[y] = x;
    }
};

struct Point {
    ll x, y;
    strong_ordering operator <=> (const Point& rhs) const {
        if(x != rhs.x) return x <=> rhs.x;
        return y <=> rhs.y;
    }
};

ll ccw(Point a, Point b, Point c)
{
    b.x -= a.x;
    b.y -= a.y;
    c.x -= a.x;
    c.y -= a.y;
    ll cross = b.x * c.y - c.x * b.y;
    return (cross > 0) - (cross < 0);
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    ll n;
    cin >> n;
    vector<pair<Point, Point>> v(n);
    for(auto& [p, q] : v) {
        cin >> p.x >> p.y >> q.x >> q.y;
        if(p > q) swap(p, q);
    }
    DSU dsu(n);
    for(ll i = 0; i < n; i++) {
        for(ll j = i+1; j < n; j++) {
            ll p = ccw(v[i].first, v[i].second, v[j].first) * ccw(v[i].first, v[i].second, v[j].second);
            ll q = ccw(v[j].first, v[j].second, v[i].first) * ccw(v[j].first, v[j].second, v[i].second);
            if(p == 0 && q == 0) {
                if(v[i].first <= v[j].second && v[j].first <= v[i].second)
                    dsu.merge(i, j);
            }
            else if(p <= 0 && q <= 0) dsu.merge(i, j);
        }
    }

    vector<ll> cnt(n);
    for(ll i = 0; i < n; i++) cnt[dsu.find(i)]++;
    vector<ll> g;
    for(ll i = 0; i < n; i++) {
        if(dsu.find(i) == i) {
            g.push_back(cnt[dsu.find(i)]);
        }
    }
    cout << g.size() << "\n";
    cout << *max_element(g.begin(), g.end()) << "\n";
}