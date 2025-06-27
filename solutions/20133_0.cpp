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
    return (b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y);
}

struct Cmp {
    Point o;
    Cmp(Point _o) : o(_o) {}
    bool operator() (const Point& a, const Point& b) const {
        if((a < o) != (b < o)) return a < b;
        return ccw(o, a, b) > 0;
    }
};

ll nC3(ll n)
{
    return n * (n-1) * (n-2) / 6;
}

ll nC4(ll n)
{
    return n * (n-1) * (n-2) * (n-3) / 24;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int n;
    cin >> n;
    vector<Point> ps(n);
    for(auto& [x, y] : ps) cin >> x >> y;

    ll ans = 0;
    for(int i = 0; i < n; i++) {
        vector<Point> v;
        for(int j = 0; j < n; j++) if(i != j) v.push_back(ps[j]);
        sort(v.begin(), v.end(), Cmp(ps[i]));

        ll outter = 0;
        int m = n-1;
        int c = m-1;
        int j = 1;
        for(int k = 0; k < m; k++) {
            while(c > 0 && (ccw(ps[i], v[k], v[j]) > 0 || c >= m)) {
                j++;
                j%=m;
                c--;
            }
            outter += nC3(c);
            c++;
        }

        ans += outter;
        ans += 2 * (nC4(m) - outter);
    }
    cout << ans << "\n";
}