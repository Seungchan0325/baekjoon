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
    // ios_base::sync_with_stdio(false); cin.tie(NULL);

    int N, R;
    cin >> N >> R;
    vector<pair<ll, ll>> v(N);
    for(auto& [x, y] : v) cin >> x >> y;

    convexHull(v);

    int n = v.size();

    auto tmp = v;
    v.insert(v.end(), tmp.begin(), tmp.end());

    double ans = 1e18;
    int lst = 0;
    for(int i = 0; i < n; i++) {
        while(lst < v.size() - 2 && ccw(v[i], v[i+1], v[lst+1] - v[lst] + v[i+1]) >= 0) {
            lst++;
        }
        pair<ll, ll> v1 = v[i+1] - v[i];
        pair<ll, ll> v2 = v[lst] - v[i];
        ans = min(ans, abs(v1.X*v2.Y - v1.Y*v2.X)/sqrt(v1.X*v1.X + v1.Y*v1.Y));
    }

    printf("%0.5lf", ans);
}