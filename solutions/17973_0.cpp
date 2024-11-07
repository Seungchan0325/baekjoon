#include <bits/stdc++.h>

using namespace std;

using ll = long long;

struct Point {
    ll x, y;
    bool operator < (const Point& rhs) const
    {
        return tie(x, y) < tie(rhs.x, rhs.y);
    }
};

struct Line {
    ll i, j, dx, dy;
    Line(ll i, ll j, Point pi, Point pj) : i(i), j(j), dx(pj.x-pi.x), dy(pj.y-pi.y) {}

    bool operator < (const Line& rhs) const
    {
        ll l = dy * rhs.dx;
        ll r = rhs.dy * dx;
        return tie(l, i, j) < tie(r, rhs.i, rhs.j);
    }

    bool operator == (const Line& rhs) const
    {
        return dy * rhs.dx == rhs.dy * dx;
    }
};

ll ccw(Point p1, Point p2, Point p3)
{
    ll ret = (p2.x - p1.x) * (p3.y - p1.y) - (p3.x - p1.x) * (p2.y - p1.y);
    if(ret > 0) return 1;
    if(ret < 0) return -1;
    return 0;
}

struct Comparator {
    Point p;
    Comparator(Point p) : p(p) {}
    bool operator () (const Point& p1, const Point& p2) const
    {
        if((p1 < p) != (p2 < p)) return p1 < p2;
        return ccw(p, p1, p2) > 0;
    }
};

const int MAXN = 1005;

int N, pos[MAXN], a[MAXN];

ll getArea(Point p1, Point p2, Point p3)
{
    return abs((p2.x-p1.x)*(p3.y-p1.y)-(p3.x-p1.x)*(p2.y-p1.y));
}

bool isConvex(vector<Point> poly)
{
    int n = poly.size();
    for(int i = 0; i < n; i++) {
        if(ccw(poly[i], poly[(i+1)%n], poly[(i+2)%n]) >= 0) return false;
    }
    return true;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N;
    vector<Point> A(N);
    for(auto& [x, y] : A) cin >> x >> y;
    sort(A.begin(), A.end());

    vector<Line> v;
    for(int i = 0; i < N; i++) {
        for(int j = i+1; j < N; j++) {
            v.emplace_back(i, j, A[i], A[j]);
        }
    }

    ll ans = 0;

    ll mn = 1e19;
    ll cnt = 0;

    iota(pos, pos+N, 0);
    sort(v.begin(), v.end());
    for(int i = 0; i < v.size(); i++) {
        auto p = v[i].i;
        auto q = v[i].j;
        swap(A[pos[p]], A[pos[q]]);
        swap(pos[p], pos[q]);
        if(pos[p] > pos[q]) swap(p, q);

        ans += pos[p] * (N-pos[q]-1);

        if(pos[p] > 0 && pos[q] < N-1) {
            ll uparea = getArea(A[pos[p]], A[pos[q]], A[pos[p]-1]);
            ll dwarea = getArea(A[pos[p]], A[pos[q]], A[pos[q]+1]);

            if(uparea + dwarea > mn) continue;

            if(uparea + dwarea != mn) mn = uparea + dwarea, cnt = 0;

            vector<Point> up, dw;

            int l = pos[p];
            while(l > 0 && getArea(A[pos[p]], A[pos[q]], A[l-1]) == uparea) {
                l--;
                up.push_back(A[l]);
            }
            int r = pos[q];
            while(r < N-1 && getArea(A[pos[p]], A[pos[q]], A[r+1]) == dwarea) {
                r++;
                dw.push_back(A[r]);
            }

            for(auto u : up) {
                for(auto d : dw) {
                    vector<Point> poly = {A[pos[p]], u, A[pos[q]], d};
                    if(!isConvex(poly)) cnt += 2;
                    else cnt++;
                }
            }
        }
    }

    ans += cnt;
    cout << ans;
}