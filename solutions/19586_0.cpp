#include <bits/stdc++.h>

using namespace std;

using ll = long long;

struct Point {
    ll x, y;
    Point operator + (const Point& rhs) const {
        return {x + rhs.x, y + rhs.y};
    }
    Point operator - (const Point& rhs) const {
        return {x - rhs.x, y - rhs.y};
    }
};

ll d(Point a, Point b) {
    return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}
ll ccw(Point a, Point b, Point c)
{
    ll ret = (b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y);
    if(ret < 0) return -1;
    if(ret > 0) return 1;
    return 0;
}

void convex_hull(vector<Point>& v)
{
    sort(v.begin(), v.end(), [](Point a, Point b){return a.x < b.x;});
    vector<Point> up, dw;
    for(auto p : v) {
        while(up.size() >= 2 && ccw(up.end()[-2], up.end()[-1], p) <= 0) up.pop_back();
        while(dw.size() >= 2 && ccw(dw.end()[-2], dw.end()[-1], p) >= 0) dw.pop_back();
        up.push_back(p);
        dw.push_back(p);
    }
    v = up;
    for(int i = (int)dw.size()-2; i >= 1; i--) v.push_back(dw[i]);
}

double dist(double a, double b, double c, Point p)
{
    return abs(a * p.x + b * p.y + c) / sqrt(a*a + b*b);
}

int main()
{
    int n;
    cin >> n;
    vector<Point> v(n);
    for(auto& [x, y] : v)cin >> x >> y;
    convex_hull(v);
    v.insert(v.end(), v.begin(), v.end());
    n = v.size();
    int j = 0;
    int l = 0;
    int r = 0;
    double ans = 1e18;
    if(v.size()/2 <= 1) ans = 0;
    if(v.size()/2 == 2) ans = 2 * sqrt(d(v[0], v[1]));
    for(int i = 0; i < n/2; i++) {
        while(j < n-1 && ccw(v[i], v[i+1], v[j+1] - v[j] + v[i+1]) >= 0) j++;
        while(l < n-1 && d(v[i], v[l+1]-v[l]+v[i+1]) >= d(v[i], v[i+1]) + d(v[i+1], v[l+1]-v[l]+v[i+1])) l++;
        r = max(r, j);
        while(r < n-1 && d(v[i+1], v[r+1]-v[r]+v[i]) >= d(v[i], v[i+1]) + d(v[i], v[r+1]-v[r]+v[i])) r++;
        double a = v[i].y - v[i+1].y;
        double b = -(v[i].x - v[i+1].x);
        double c = v[i].y * (v[i].x - v[i+1].x) - v[i].x * (v[i].y - v[i+1].y);
        double height = dist(a, b, c, v[j]);
        double width = dist(-b, a, b*v[i].x - a*v[i].y, v[l]) + dist(-b, a, b*v[i].x - a*v[i].y, v[r]);
        ans = min(ans, 2*(height+width));
    }
    cout << setprecision(10) << fixed << ans;
}