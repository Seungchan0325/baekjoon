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

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int tc; cin >> tc;
    while(tc--) {
        int N;
        cin >> N;
        vector<pair<ll, ll>> v(N);
        for(auto& [x, y] : v) cin >> x >> y;

        convexHull(v);

        auto tmp = v;
        v.insert(v.end(), tmp.begin(), tmp.end());

        tuple<ll, int, int> mx = {-1, -1, -1};
        int n = v.size();
        int lst = 0;
        for(int i = 0; i < n - 1; i++) {
            while(lst < n - 2 && ccw(v[i], v[i+1], v[lst+2] - v[lst+1] + v[i+1]) >= 0) {
                lst++;
                ll dist = (v[lst].X-v[i].X)*(v[lst].X-v[i].X) + (v[lst].Y-v[i].Y)*(v[lst].Y-v[i].Y);
                mx = max({dist, i, lst}, mx);
            }
        }

        auto [dist, i, j] = mx;
        auto [x0, y0] = v[i];
        auto [x1, y1] = v[j];
        cout << x0 << " " << y0 << " " << x1 << " " << y1 << "\n";
    }
}