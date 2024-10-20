#include <bits/stdc++.h>

using namespace std;

using ll = long long;

struct Point {
    ll x, y;
    bool operator < (const Point& rhs) const {
        return tie(x, y) < tie(rhs.x, rhs.y);
    }
};

struct Line {
    ll i, j, dx, dy;
    Line(ll i, ll j, Point p, Point q) : i(i), j(j), dx(q.x-p.x), dy(q.y-p.y) {}
    bool operator < (const Line& rhs) const {
        ll l = dy*rhs.dx;
        ll r = rhs.dy*dx;
        return tie(l, i, j) < tie(r, rhs.i, rhs.j);
    }

    bool operator == (const Line& rhs) const {
        return dy*rhs.dx == rhs.dy*dx;
    }
};

const int MAXN = 2005;

int N, pos[MAXN];
Point A[MAXN];

ll area(Point p1, Point p2, Point p3)
{
    return abs((p2.x - p1.x) * (p3.y - p1.y) - (p3.x - p1.x) * (p2.y - p1.y));
}

void solve()
{
    sort(A+1, A+N+1);
    for(int i = 1; i <= N; i++) pos[i] = i;

    vector<Line> v;
    for(int i = 1; i <= N; i++) {
        for(int j = i+1; j <= N; j++) {
            v.emplace_back(i, j, A[i], A[j]);
        }
    }
    sort(v.begin(), v.end());

    ll mn = 1e18, mx = -1e18;
    for(int i = 0, j = 0; i < v.size(); i = j) {
        while(j < v.size() && v[i] == v[j]) j++;
        for(; i < j; i++) {
            auto p = v[i].i;
            auto q = v[i].j;
            swap(A[pos[p]], A[pos[q]]);
            swap(pos[p], pos[q]);
            if(pos[p] > pos[q]) swap(p, q);
            if(pos[p] > 1) {
                mn = min(area(A[pos[p]], A[pos[q]], A[pos[p]-1]), mn);
                mx = max(area(A[pos[p]], A[pos[q]], A[1]), mx);
            }
            if(pos[q] < N) {
                mn = min(area(A[pos[p]], A[pos[q]], A[pos[q]+1]), mn);
                mx = max(area(A[pos[p]], A[pos[q]], A[N]), mx);
            }
        }
    }

    cout << mn/2 << "." << mn%2*5 << " ";
    cout << mx/2 << "." << mx%2*5 << "\n";
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    while(true) {
        cin >> N;
        if(N == 0) break;
        for(int i = 1; i <= N; i++) {
            cin >> A[i].x >> A[i].y;
        }
        solve();
    }
}