#include <bits/stdc++.h>

using namespace std;

using ll = long long;

struct Point {
    ll x, y;
    Point() : x(0), y(0) {}
    Point(ll _x, ll _y) : x(_x), y(_y) {}
    Point operator + (const Point& rhs) const {
        return Point(x + rhs.x, y + rhs.y);
    }
    Point operator - (const Point& rhs) const {
        return Point(x - rhs.x, y - rhs.y);
    }
    bool operator < (const Point& rhs) const {
        if(x == rhs.x) return y < rhs.y;
        return x < rhs.x;
    }
};

ll dist(Point p1, Point p2)
{
    ll x = p1.x - p2.x;
    ll y = p1.y - p2.y;
    return x * x + y * y;
}

ll ccw(Point p1, Point p2, Point p3)
{
    ll cross = (p2.x - p1.x) * (p3.y - p1.y) - (p3.x - p1.x) * (p2.y - p1.y);
    if(cross < 0) return -1;
    if(cross > 0) return 1;
    return 0;
}

struct cmp {
    Point p;
    cmp(Point _p) : p(_p) {}
    bool operator() (Point p1, Point p2) {
        if((p1 < p) != (p2 < p)) return p1 < p2;
        return ccw(p, p1, p2) > 0;
    }
};

const int MAXN = 2005;

ll N;
Point p[MAXN];

int main()
{
    cin >> N;
    for(int i = 1; i <= N; i++) {
        cin >> p[i].x >> p[i].y;
    }

    ll ans = 0;
    for(int i = 1; i <= N; i++) {
        vector<Point> v;
        for(int j = 1; j <= N; j++) {
            if(j == i) continue;
            v.push_back(p[j]);
        }
        sort(v.begin(), v.end(), cmp(p[i]));

        int k = -1;
        int c = 0;
        for(int j = 0; j < N-1; j++) {
            while(ccw(p[i], v[j], v[(k+1)%(N-1)]) >= 0 && c < N-1) {
                k++;
                c++;
            }
            ans += (c-1) * (c-2) / 2;
            c--;
        }
    }

    ll apb = N * (N-1) * (N-2) * (N-3) / 4 / 3 / 2;
    ans -= 3 * apb;
    cout << 2*ans;
}