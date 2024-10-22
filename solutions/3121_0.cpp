#include <bits/stdc++.h>

using namespace std;

using ll = long long;

struct Point {
    ll x, y, w;
    bool operator < (const Point& rhs) const {
        return tie(x, y) < tie(rhs.x, rhs.y);
    }
};

struct Line {
    ll i, j, dx, dy;
    Line(ll i, ll j, Point pi, Point pj) : i(i), j(j), dx(pj.x-pi.x), dy(pj.y-pi.y) {}
    bool operator < (const Line& rhs) const {
        ll l = dy*rhs.dx;
        ll r = rhs.dy*dx;
        return tie(l, i, j) < tie(r, rhs.i, rhs.j);
    }
    bool operator == (const Line& rhs) const {
        return dy*rhs.dx == rhs.dy*dx;
    }
};

struct T {
    ll lmx, rmx, lrmx, mx;
    T() : lmx(0), rmx(0), lrmx(0), mx(0) {}
    T(ll v) : lmx(v), rmx(v), lrmx(v), mx(v) {}
};

T merge(T l, T r)
{
    T ret;
    ret.lmx = max(l.lmx, l.lrmx + r.lmx);
    ret.rmx = max(r.rmx, r.lrmx + l.rmx);
    ret.lrmx = l.lrmx + r.lrmx;
    ret.mx = max({l.mx, r.mx, l.rmx + r.lmx});
    return ret;
}

const int MAXN = 1005;

int N, pos[MAXN];
ll ans;
Point A[MAXN];
T tree[4*MAXN];

void update(int x, T v, int s = 1, int e = N, int idx = 1)
{
    if(e < x || x < s) return;

    if(s == e) {
        tree[idx] = v;
        return;
    }

    int m = (s + e) / 2;
    update(x, v, s, m, 2*idx);
    update(x, v, m+1, e, 2*idx+1);
    tree[idx] = merge(tree[2*idx], tree[2*idx+1]);
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N;
    for(int i = 1; i <= N; i++) {
        char rb;
        cin >> A[i].x >> A[i].y >> rb;
        if(rb == 'R') A[i].w = 1;
        else A[i].w = -1e9;
    }

    sort(A+1, A+N+1);
    for(int i = 1; i <= N; i++) {
        pos[i] = i;
        update(i, T(A[i].w));
    }
    vector<Line> v;
    for(int i = 1; i <= N; i++) {
        for(int j = i+1; j <= N; j++) {
            v.emplace_back(i, j, A[i], A[j]);
        }
    }
    ans = max(ans, tree[1].mx);
    sort(v.begin(), v.end());
    for(int i = 0, j = 0; i < v.size(); i = j) {
        while(j < v.size() && v[i] == v[j]) j++;
        for(; i < j; i++) {
            auto p = v[i].i;
            auto q = v[i].j;
            update(pos[p], T(A[pos[q]].w));
            update(pos[q], T(A[pos[p]].w));
            swap(A[pos[p]], A[pos[q]]);
            swap(pos[p], pos[q]);
        }
        ans = max(ans, tree[1].mx);
    }
    cout << ans;
}