#include <bits/stdc++.h>

using namespace std;

using ll = long long;

struct Point {
    ll x, y;
    bool operator < (const Point& rhs) const {
        return tie(x, y) < tie(rhs.x, rhs.y);
    }
    Point operator + (const Point& rhs) const {
        return {x + rhs.x, y + rhs.y};
    }
    Point operator - (const Point& rhs) const {
        return {x - rhs.x, y - rhs.y};
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

bool isInConvexHull(Point p, const vector<Point>& poly)
{
    if(poly.size() == 2) {
        return ccw(poly[0], poly[1], p) == 0 && min(poly[0], poly[1]) < p && p < max(poly[0], poly[1]);
    }
    int lo = 1;
    int hi = poly.size();
    if(ccw(poly[0], poly.back(), p) == 0) return min(poly[0].x, poly.back().x) <= p.x && p.x <= max(poly[0].x, poly.back().x) && min(poly[0].y, poly.back().y) <= p.y && p.y <= max(poly[0].y, poly.back().y);
    while(lo + 1 < hi) {
        int mid = (lo + hi) / 2;
        if(ccw(poly[0], poly[mid], p) >= 0) lo = mid;
        else hi = mid;
    }
    if(hi == poly.size()) return false;
    return ccw(poly[0], poly[lo], p) >= 0 && ccw(poly[0], poly[hi], p) <= 0 && ccw(poly[lo], poly[hi], p) >= 0;
}

ll getArea(const vector<Point>& poly)
{
    ll area = 0;
    int n = poly.size();
    for(int i = 0; i < n; i++) {
        area += poly[i].x * poly[(i+1)%n].y;
        area -= poly[i].y * poly[(i+1)%n].x;
    }
    return abs(area);
}

int N, DP[100];
vector<vector<Point>> rects;

int main()
{
    cin >> N;
    for(int i = 0; i < N; i++) {
        vector<Point> rect;
        for(int j = 0; j < 4; j++) {
            Point p;
            cin >> p.x >> p.y;
            rect.push_back(p);
        }
        rect = convexHull(rect);
        rects.push_back(rect);
    }

    sort(rects.begin(), rects.end(), [](vector<Point> a, vector<Point> b){
        return getArea(a) < getArea(b);
    });

    int ans = 1;
    for(int i = 0; i < N; i++) {
        DP[i] = 1;
        for(int j = 0; j < i; j++) {
            bool isin = true;
            for(int k = 0; k < 4; k++) {
                if(!isInConvexHull(rects[j][k], rects[i])) isin = false;
            }
            if(isin) {
                DP[i]++;
            }
        }
        ans = max(ans, DP[i]);
    }
    cout << ans;
}