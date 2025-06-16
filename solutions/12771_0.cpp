#include <bits/stdc++.h>

using namespace std;

using ll = long long;

struct Point {
    ll x, y;
    Point(ll _x, ll _y) : x(_x), y(_y) {}
    auto operator<=>(const Point& other) const = default;
};

Point getSymmetry(Point src, Point dst)
{
    return Point(-dst.x + 2 * src.x, -dst.y + 2 * src.y);
}

ll ccw(Point a, Point b, Point c)
{
    return (b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y);
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int n;
    cin >> n;
    vector<Point> ps;
    vector<tuple<ll, ll, ll>> segments(n);
    for(auto& [x0, x1, y] : segments) {
        cin >> x0 >> x1 >> y;
        if(x0 > x1) swap(x0, x1);
        ps.emplace_back(x0, y);
        ps.emplace_back(x1, y);
    }

    ll ans = 0;
    for(int i = 0; i < ps.size(); i++) {
        ll s = 0;
        vector<pair<Point, ll>> v;
        for(auto [x0, x1, y] : segments) {
            if(y < ps[i].y) {
                v.emplace_back(getSymmetry(ps[i], Point(x0, y)), -(x1 - x0));
                v.emplace_back(getSymmetry(ps[i], Point(x1, y)), (x1 - x0));
            } else if(y > ps[i].y) {
                v.emplace_back(Point(x0, y), (x1 - x0));
                v.emplace_back(Point(x1, y), -(x1 - x0));
            } else {
                if(x0 <= ps[i].x && ps[i].x <= x1) s += x1 - x0;
            }
        }
        sort(v.begin(), v.end(), [&](pair<Point, ll> a, pair<Point, ll> b){
            if(ccw(a.first, ps[i], b.first) != 0) return ccw(a.first, ps[i], b.first) > 0;
            return a.second > b.second;
        });

        ans = max(ans, s);
        for(auto [p, x] : v) {
            s += x;
            ans = max(ans, s);
        }
    }
    cout << ans;
}