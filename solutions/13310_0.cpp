#include <bits/stdc++.h>

using namespace std;

using ll = long long;

#define X first
#define Y second

ll ccw(pair<ll, ll> a, pair<ll, ll> b, pair<ll, ll> c)
{
    return (b.X - a.X) * (c.Y - a.Y) - (c.X - a.X) * (b.Y - a.Y);
}

void convexHull(vector<pair<ll, ll>>& v)
{
    int N = v.size();
    sort(v.begin(), v.end());
    vector<pair<ll, ll>> up, dw;
    for(int i = 0; i < N; i++) {
        while(up.size() >= 2 && ccw(up.end()[-2], up.end()[-1], v[i]) >= 0) up.pop_back();
        while(dw.size() >= 2 && ccw(dw.end()[-2], dw.end()[-1], v[i]) <= 0) dw.pop_back();
        up.push_back(v[i]);
        dw.push_back(v[i]);
    }

    v = dw;
    for(int i = up.size() - 2; i >= 1; i--) v.push_back(up[i]);
}

pair<ll, ll> operator+(pair<ll, ll> a, pair<ll, ll> b)
{
    return {a.X + b.X, a.Y + b.Y};
}

pair<ll, ll> operator-(pair<ll, ll> a, pair<ll, ll> b)
{
    return {a.X - b.X, a.Y - b.Y};
}

ll rotatingCalipers(vector<pair<ll, ll>> v)
{
    convexHull(v);

    auto tmp = v;
    v.insert(v.end(), tmp.begin(), tmp.end());

    ll ans = 0;
    int n = v.size();
    int lst = 0;
    for(int i = 0; i < n - 1; i++) {
        while(lst < n - 2 && ccw(v[i], v[i+1], v[lst+2] - v[lst+1] + v[i+1]) >= 0) {
            lst++;
            ans = max(ans, (v[lst].X-v[i].X)*(v[lst].X-v[i].X) + (v[lst].Y-v[i].Y)*(v[lst].Y-v[i].Y));
        }
    }

    return ans;
}

ll f(const vector<tuple<ll, ll, ll, ll>>& vs, ll t)
{
    vector<pair<ll, ll>> v;
    for(auto [x, y, dx, dy] : vs) {
        v.emplace_back(x + dx * t, y + dy * t);
    }

    return rotatingCalipers(v);
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int N, T;
    cin >> N >> T;
    vector<tuple<ll, ll, ll, ll>> v(N);
    for(auto& [x, y, dx, dy] : v) cin >> x >> y >> dx >> dy;

    int lo = 0;
    int hi = T;

    while(lo + 2 < hi) {
        int p = (2*lo + hi) / 3;
        int q = (lo + 2*hi) / 3;
        if(f(v, p) <= f(v, q)) {
            hi = q;
        } else {
            lo = p;
        }
    }

    pair<ll, ll> mn = {1e18, 1e18};
    for(int i = lo; i <= hi; i++) {
        mn = min({f(v, i), i}, mn);
    }
    
    cout << mn.second << "\n" << mn.first;
}