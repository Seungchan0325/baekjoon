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
        ll l = dy*rhs.dx;
        ll r = rhs.dy*dx;
        return tie(l, i, j) < tie(r, rhs.i, rhs.j);
    }
    bool operator == (const Line& rhs) const
    {
        return dy*rhs.dx == rhs.dy*dx;
    }
};

const int MAXN = 2005;

int N, pos[MAXN];

double compute(Point p1, Point p2, Line line)
{
    double dx = line.dx;
    double dy = line.dy;
    auto [x1, y1] = p1;
    auto [x2, y2] = p2;
    return abs(dy*(x1-x2)/2 - dx*(y1-y2)/2)/sqrt(dx*dx+dy*dy);
}

int main()
{
    ios_base::sync_with_stdio(0); cin.tie(0);

    cin >> N;
    vector<Point> A(N);
    for(auto& [x, y] : A) cin >> x >> y;
    sort(A.begin(), A.end());

    vector<Line> v, vv;
    for(int i = 0; i < N; i++) {
        for(int j = i+1; j < N; j++) {
            Line l(i, j, A[i], A[j]);
            v.emplace_back(l);

            swap(l.dx, l.dy);
            l.dx = -l.dx;
            if(l.dx < 0) l.dx = -l.dx, l.dy = -l.dy;
            if(l.dx == 0 && l.dy < 0) l.dy = -l.dy;
            vv.emplace_back(l);
        }
    }
    sort(v.begin(), v.end());
    sort(vv.begin(), vv.end());

    for(int i = 0; i < N; i++) pos[i] = i;

    double ans = 0;

    int j = 0, k = 0;
    for(int i = 0; i < v.size();) {
        while(j < v.size() && v[j] == v[i]) j++;
        
        while(k < vv.size() && vv[k] < v[i]) {
            auto p = vv[k].i;
            auto q = vv[k].j;
            if(pos[p] > pos[q]) swap(p, q);
            if(pos[p] + 1 == pos[q]) {
                ans = max(ans, compute(A[pos[p]], A[pos[q]], vv[k]));
            }
            k++;
        }

        vector<int> upd;
        for(; i < j; i++) {
            auto p = v[i].i;
            auto q = v[i].j;
            swap(A[pos[p]], A[pos[q]]);
            swap(pos[p], pos[q]);
            upd.push_back(p);
            upd.push_back(q);
        }

        for(auto p : upd) {
            if(pos[p] > 0) ans = max(ans, compute(A[pos[p]], A[pos[p]-1], v[j-1]));
            if(pos[p] < N-1) ans = max(ans, compute(A[pos[p]], A[pos[p]+1], v[j-1]));
        }
    }

    while(k < vv.size()) {
        auto p = vv[k].i;
        auto q = vv[k].j;
        if(pos[p] > pos[q]) swap(p, q);
        if(pos[p] + 1 == pos[q]) {
            ans = max(ans, compute(A[pos[p]], A[pos[q]], vv[k]));
        }
        k++;
    }

    cout << fixed << setprecision(16) << ans;
}