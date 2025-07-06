#include <bits/stdc++.h>

using namespace std;

using ll = long long;

struct Point {
    long double x, y;
    Point(long double _x = 0.0, long double _y = 0.0) : x(_x), y(_y) {}
    Point operator + (const Point& rhs) const {
        return Point(x + rhs.x, y + rhs.y);
    }
    Point operator - (const Point& rhs) const {
        return Point(x - rhs.x, y - rhs.y);
    }
    Point operator * (long double rhs) const {
        return Point(x * rhs, y * rhs);
    }
    Point operator / (long double rhs) const {
        return Point(x / rhs, y / rhs);
    }
    bool operator < (const Point& rhs) const {
        return pair(x, y) < pair(rhs.x, rhs.y);
    }
};

long double distance(Point a, Point b)
{
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

bool isInCircle(Point o, long double r, vector<Point>& ps)
{
    for(auto p : ps) {
        if(distance(o, p) > r) return false;
    }
    return true;
}

Point getCenter(Point a, Point b){ return Point((a.x+b.x)/2, (a.y+b.y)/2); }
Point getCenter(Point A, Point B, Point C) {
    long double D = 2.0 * ( A.x*(B.y - C.y)
                     + B.x*(C.y - A.y)
                     + C.x*(A.y - B.y) );

    long double a2 = A.x*A.x + A.y*A.y;
    long double b2 = B.x*B.x + B.y*B.y;
    long double c2 = C.x*C.x + C.y*C.y;

    long double ux = ( a2*(B.y - C.y)
                + b2*(C.y - A.y)
                + c2*(A.y - B.y) ) / D;

    long double uy = ( a2*(C.x - B.x)
                + b2*(A.x - C.x)
                + c2*(B.x - A.x) ) / D;

    return Point(ux, uy);
}

long double dst(Point a, Point b){
    auto dx = a.x - b.x, dy = a.y - b.y;
    return sqrt(dx*dx + dy*dy);
}

pair<Point, long double> solve(vector<Point> v)
{
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 generator(seed);
    shuffle(v.begin(), v.end(), generator);
    
    int n = v.size();
    Point p;
    long double r = 0;
    for(int i = 0; i < n; i++) if(dst(v[i], p) > r) {
        p = v[i];
        r = 0;
        for(int j = 0; j < i; j++) if(dst(v[j], p) > r) {
            p = getCenter(v[i], v[j]);
            r = dst(v[j], p);
            for(int k = 0; k < j; k++) if(dst(v[k], p) > r) {
                p = getCenter(v[i], v[j], v[k]);
                r = dst(v[k], p);
            }
        }
    }
    return pair(p, r);
}

int main()
{
    int n;
    cin >> n;
    vector<Point> v(n);
    for(auto& i : v) cin >> i.x >> i.y;

    auto [p, r] = solve(v);

    cout << fixed;
    cout.precision(3);
    if(abs(p.x) < 1e-7) p.x = 0;
    if(abs(p.y) < 1e-7) p.y = 0;
    if(abs(r) < 1e-7) r = 0;
    cout << p.x << " " << p.y << "\n" << r;
}