#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const long double inf = 1e12;

struct Point {
    ll x = 0, y = 0;
    auto operator <=> (const Point& rhs) {
        return pair(x, y) <=> pair(rhs.x, rhs.y);
    }
};

struct Line {
    ll a = 0, b = 0;
    long double inter = -inf;
};

long double cross(Line a, Line b)
{
    return (long double)(b.b - a.b) / (a.a - b.a);
}

int main()
{
    int n;
    cin >> n;
    vector<Point> ps(n);
    for(auto& [x, y] : ps) cin >> x >> y;
    sort(ps.begin(), ps.end());

    ll ans = 0;
    vector<Line> v;
    v.push_back(Line{ps[0].x, ps[0].y, -inf});
    for(int i = 1; i < n; i++) {
        int lo = 0;
        int hi = ssize(v);
        while(lo + 1 < hi) {
            int mid = (lo + hi) / 2;
            if(v[mid].inter <= (long double)ps[i].x/ps[i].y) lo = mid;
            else hi = mid;
        }
        ans = max(ans, v[lo].a * ps[i].x + v[lo].b * ps[i].y);
        Line nw;
        nw.a = ps[i].x;
        nw.b = ps[i].y;
        while(v.size() && (nw.a == v.back().a || cross(v.back(), nw) <= v.back().inter)) v.pop_back();
        if(v.size()) nw.inter = cross(v.back(), nw);
        v.push_back(nw);
    }
    cout << ans;
}