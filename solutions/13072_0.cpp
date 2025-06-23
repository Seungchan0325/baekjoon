#include <bits/stdc++.h>

using namespace std;

using ll = long long;

struct Point {
    ll x, y;
    Point(ll _x = 0, ll _y = 0) : x(_x), y(_y) {}
    auto operator <=> (const Point& rhs) const {
        return pair(x, y) <=> pair(rhs.x, rhs.y);
    }
};

ll ccw(Point a, Point b, Point c)
{
    ll ret = (b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y);
    if(ret < 0) return -1;
    if(ret > 0) return 1;
    return 0;
}

vector<Point> convexHull(vector<Point> p)
{
    int n = p.size();
    sort(p.begin(), p.end());
    vector<Point> up, dw;
    for(int i = 0; i < n; i++) {
        while(up.size() >= 2 && ccw(up.end()[-2], up.end()[-1], p[i]) >= 0) up.pop_back();
        while(dw.size() >= 2 && ccw(dw.end()[-2], dw.end()[-1], p[i]) <= 0) dw.pop_back();
        up.push_back(p[i]);
        dw.push_back(p[i]);
    }
    for(int i = up.size()-2; i >= 1; i--) dw.push_back(up[i]);
    return dw;
}


int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    while(true) {
        int n; cin >> n;
        if(n == 0) break;
        vector<Point> v(n);
        for(auto& [x, y] : v) cin >> x >> y;
        v = convexHull(v);
        n = v.size();
        if(n == 1) {
            cout << "4 0\n";
            continue;
        }
        ll a = 0;
        ll b = 0;
        for(int i = 1; i <= n; i++) {
            ll dx = abs(v[i%n].x - v[i-1].x);
            ll dy = abs(v[i%n].y - v[i-1].y);
            a += max(dx, dy) - min(dx, dy);
            b += min(dx, dy);
        }
        cout << a << " " << b << "\n";
    }
}