#include <bits/stdc++.h>

using namespace std;

using ll = long long;

struct Point {
    double x, y;
    Point(double _x = 0.0, double _y = 0.0) : x(_x), y(_y) {}
    Point operator + (const Point& rhs) const {
        return Point(x + rhs.x, y + rhs.y);
    }
    Point operator - (const Point& rhs) const {
        return Point(x - rhs.x, y - rhs.y);
    }
    Point operator * (double rhs) const {
        return Point(x * rhs, y * rhs);
    }
    Point operator / (double rhs) const {
        return Point(x / rhs, y / rhs);
    }
    bool operator < (const Point& rhs) const {
        return pair(x, y) < pair(rhs.x, rhs.y);
    }
};

double distance(Point a, Point b)
{
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

bool isInCircle(Point o, double r, vector<Point>& ps)
{
    for(auto p : ps) {
        if(distance(o, p) > r) return false;
    }
    return true;
}

Point getCenter(Point A, Point B, Point C) {
    double D = 2.0 * ( A.x*(B.y - C.y)
                     + B.x*(C.y - A.y)
                     + C.x*(A.y - B.y) );

    double a2 = A.x*A.x + A.y*A.y;
    double b2 = B.x*B.x + B.y*B.y;
    double c2 = C.x*C.x + C.y*C.y;

    double ux = ( a2*(B.y - C.y)
                + b2*(C.y - A.y)
                + c2*(A.y - B.y) ) / D;

    double uy = ( a2*(C.x - B.x)
                + b2*(A.x - C.x)
                + c2*(B.x - A.x) ) / D;

    return Point(ux, uy);
}

int main()
{
    int n;
    cin >> n;
    vector<Point> v(n);
    for(auto& i : v) cin >> i.x >> i.y;

    pair<double, Point> ans = {1e18, Point()};
    for(int i = 0; i < n; i++) {
        for(int j = i+1; j < n; j++) {
            Point o = (v[i] + v[j]) / 2;
            double r = distance(v[i], v[j]) / 2;
            if(isInCircle(o, r, v)) ans = min(ans, pair(r, o));
        }
    }
    for(int i = 0; i < n; i++) {
        for(int j = i+1; j < n; j++) {
            for(int k = j+1; k < n; k++) {
                Point o = getCenter(v[i], v[j], v[k]);
                double r = distance(o, v[i]);
                if(isInCircle(o, r, v)) ans = min(ans, pair(r, o));
            }
        }
    }

    cout << fixed << setprecision(10);
    cout << ans.second.x << " " << ans.second.y << " " << ans.first;
}