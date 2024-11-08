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

ll area(Point p1, Point p2, Point p3)
{
    return abs((p2.x - p1.x) * (p3.y - p1.y) - (p3.x - p1.x) * (p2.y - p1.y));
}

template<typename Iter, typename Comp>
Iter par_search(Iter l, Iter r, Comp comp)
{
    l--;
    while(l+1 < r) {
        auto mid = l + (r - l) / 2;
        if(comp(*mid)) l = mid;
        else r = mid;
    }
    return l;
}

const int MAXN = 2005;

int N, pos[MAXN];
ll A, B;

int main()
{
    cin >> N >> A >> B;
    vector<Point> P(N);
    for(auto& [x, y] : P) cin >> x >> y;
    sort(P.begin(), P.end());

    vector<Line> v;
    for(int i = 0; i < N; i++) {
        for(int j = i+1; j < N; j++) {
            v.emplace_back(i, j, P[i], P[j]);
        }
    }
    sort(v.begin(), v.end());

    for(int i = 0; i < N; i++) pos[i] = i;

    ll ans = 0;
    int j = 0;
    for(int i = 0; i < v.size();) {
        while(j < v.size() && v[j] == v[i]) j++;
        for(; i < j; i++) {
            auto p = v[i].i;
            auto q = v[i].j;

            swap(P[pos[p]], P[pos[q]]);
            swap(pos[p], pos[q]);

            if(pos[p] > pos[q]) swap(p, q);

            auto cmpA = [&](Point pk) {
                return area(P[pos[p]], P[pos[q]], pk) >= A;
            };
            auto cmpB = [&](Point pk) {
                return area(P[pos[p]], P[pos[q]], pk) > B;
            };
            int l = par_search(P.begin(), P.begin() + pos[p], cmpA) - P.begin();
            int r = par_search(P.begin(), P.begin() + pos[p], cmpB) - P.begin();
            ans += l - r;

            l = par_search(P.rbegin(), P.rbegin() + N - pos[q], cmpA) - P.rbegin();
            r = par_search(P.rbegin(), P.rbegin() + N - pos[q], cmpB) - P.rbegin();
            ans += l - r;
        }
    }

    cout << ans/3;
}