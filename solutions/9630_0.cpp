#include <bits/stdc++.h>

using namespace std;

using ll = long long;

#define X first
#define Y second

int N, D;

ll ccw(ll x1, ll y1, ll x2, ll y2, ll x3, ll y3)
{
    return (x2 - x1) * (y3 - y1) - (x3 - x1) * (y2 - y1);
}

double cross(double x1, double y1, double x2, double y2)
{
    if(abs(x1 - x2) <= FLT_EPSILON) return x1;
    double p = -y1 * (x1 - x2) / (y1 - y2) + x1;
    return p;
}

double update(tuple<double, int, int>& p, ll x2, ll y2)
{
    auto& [mx, x1, y1] = p;
    mx = max(mx, cross(x1, y1, x2, y2));
    return mx;
}

vector<pair<double, double>> compute(vector<tuple<int, int, int>> v)
{
    vector<pair<double, double>> ret;
    vector<tuple<double, int, int>> s;
    v.emplace_back(0, D, 1e9 + 9);
    for(int i = 0; i < N; i++) {
        auto [l, x, h] = v[i];
        while((s.size() && get<2>(s.end()[-1]) <= h) || (s.size() >= 2 && update(s.end()[-2], x,  h) <= update(s.end()[-1], x, h))) s.pop_back();
        if(l) s.emplace_back(x, x, h);
        if(s.size()) {
            // double l = cross(x, h, get<1>(s.end()[-1]), get<2>(s.end()[-1]));
            double l = update(s.end()[-1], x, h);
            double r = get<1>(v[i+1]);
            if(l <= r) ret.emplace_back(l, r);
        }
    }
    return ret;
}

int main()
{
    cin >> N >> D;
    vector<tuple<int, int, int>> v(N);
    for(auto& [l, x, h] : v) cin >> l >> x >> h;
    auto range1 = compute(v);
    for(auto& [l, x, h] : v) x = D - x;
    reverse(v.begin(), v.end());
    auto range2 = compute(v);
    for(auto& [l, r] : range2) {
        swap(l, r);
        l = D - l;
        r = D - r;
    }
    vector<pair<double, double>> range;
    range.insert(range.end(), range1.begin(), range1.end());
    range.insert(range.end(), range2.begin(), range2.end());
    sort(range.begin(), range.end());

    double ans = 0;
    double mn = -1;
    double mx = -1;
    for(auto [l, r] : range)
    {
        if(l <= mx) {
            mx = max(r, mx);
        } else {
            ans += mx - mn;
            mn = l;
            mx = r;
        }
    }
    ans += mx - mn;
    // cout << round(ans);
    cout << setprecision(10) << fixed;
    cout << ans << "\n";
}