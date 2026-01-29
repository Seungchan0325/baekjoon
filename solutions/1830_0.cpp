#include <bits/stdc++.h>

using namespace std;

#define int long long

const int MAXN = 101010;
const int inf = 1e9;

struct Point {
    int x, y;
    Point(int x = 0, int y = 0) : x(x), y(y) {};
    auto operator <=> (const Point& rhs) const {
        return pair(x, y) <=> pair(rhs.x, rhs.y);
    }
    Point operator + (const Point& rhs) const {
        return Point(x+rhs.x, y+rhs.y);
    }
    Point operator - (const Point& rhs) const {
        return Point(x-rhs.x, y-rhs.y);
    }
};

struct YCmp {
    bool operator() (const Point& a, const Point& b) const {
        return a.y < b.y;
    }
};

int ccw(Point a, Point b, Point c)
{
    return (b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y);
}

int euclidean_distance(Point p, Point q)
{
    return (p.x - q.x) * (p.x - q.x) + (p.y - q.y) * (p.y - q.y);
}

int chebyshev_distance(Point p, Point q)
{
    return max(abs(p.x - q.x), abs(p.y - q.y));
}

int euclidean_closest_pair(vector<Point> ps)
{
    sort(ps.begin(), ps.end());
    int d = inf;
    int p = 0;
    multiset<Point, YCmp> s;
    for(int i = 0; i < ps.size(); i++) {
        while(p < i && (ps[i].x - ps[p].x) * (ps[i].x - ps[p].x) > d) {
            s.erase(s.find(ps[p]));
            p++;
        }
        int ly = ps[i].y - sqrt(d) - 1;
        int ry = ps[i].y + sqrt(d) + 1;
        for(auto it = s.lower_bound(Point(-inf, ly)); it != s.end() && it->y <= ry; it++)
            d = min(d, euclidean_distance(ps[i], *it));
        s.insert(ps[i]);
    }
    return d;
}

vector<Point> get_convex_hull(vector<Point> ps)
{
    sort(ps.begin(), ps.end());
    vector<Point> up, dw;
    for(int i = 0; i < ps.size(); i++) {
        while(up.size() >= 2 && ccw(up.end()[-2], up.end()[-1], ps[i]) >= 0) up.pop_back();
        while(dw.size() >= 2 && ccw(dw.end()[-2], dw.end()[-1], ps[i]) <= 0) dw.pop_back();
        up.push_back(ps[i]);
        dw.push_back(ps[i]);
    }
    for(int i = ssize(up)-2; i >= 1; i--) dw.push_back(up[i]);
    return dw;
}

int euclidean_farthest_pair(vector<Point> ps)
{
    auto cvx = get_convex_hull(ps);
    int j = 0;
    int n = cvx.size();
    int d = 0;
    for(int i = 0; i < cvx.size(); i++) {
        while(j-i < cvx.size() && ccw(cvx[(i-1+n)%n], cvx[i%n], cvx[j%n]-cvx[(j-1+n)%n]+cvx[i%n]) >= 0) {
            d = max(d, euclidean_distance(cvx[i%n], cvx[j%n]));
            d = max(d, euclidean_distance(cvx[(i-1+n)%n], cvx[j%n]));
            j++;
        }
    }
    return d;
}

int chebyshev_closest_pair(vector<Point> ps)
{
    sort(ps.begin(), ps.end());
    int d = inf;
    int p = 0;
    multiset<Point, YCmp> s;
    for(int i = 0; i < ps.size(); i++) {
        while(p < i && abs(ps[i].x - ps[p].x) > d) {
            s.erase(s.find(ps[p]));
            p++;
        }
        int ly = ps[i].y - d - 1;
        int ry = ps[i].y + d + 1;
        for(auto it = s.lower_bound(Point(-inf, ly)); it != s.end() && it->y <= ry; it++)
            d = min(d, chebyshev_distance(ps[i], *it));
        s.insert(ps[i]);
    }
    return d;
}

int chebyshev_farthest_pair(vector<Point> ps)
{
    int mnx = 0;
    int mxx = 0;
    int mny = 0;
    int mxy = 0;
    for(int i = 0; i < ps.size(); i++) {
        if(ps[i].x < ps[mnx].x) mnx = i;
        if(ps[i].x > ps[mxx].x) mxx = i;
        if(ps[i].y < ps[mny].y) mny = i;
        if(ps[i].y > ps[mxy].y) mxy = i;
    }
    int d = 0;
    for(int i = 0; i < ps.size(); i++) {
        d = max(d, chebyshev_distance(ps[mnx], ps[i]));
        d = max(d, chebyshev_distance(ps[mxx], ps[i]));
        d = max(d, chebyshev_distance(ps[mny], ps[i]));
        d = max(d, chebyshev_distance(ps[mxy], ps[i]));
    }
    return d;
}

signed main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n;
    cin >> n;
    vector<Point> ps(n);
    vector<Point> rp;
    for(auto& [x, y] : ps) {
        cin >> x >> y;
        rp.push_back(Point(x-y, x+y));
    }
    cout << euclidean_farthest_pair(ps) << "\n";
    cout << euclidean_closest_pair(ps) << "\n";
    cout << chebyshev_farthest_pair(rp) << "\n";
    cout << chebyshev_closest_pair(rp) << "\n";
    cout << chebyshev_farthest_pair(ps) << "\n";
    cout << chebyshev_closest_pair(ps) << "\n";
}