#include <bits/stdc++.h>

using namespace std;

using ll = long long;

struct Point {
    ll x, y, idx;
    Point operator + (const Point& rhs) const
    {
        return {x + rhs.x, y + rhs.y};
    }
    Point operator - (const Point& rhs) const
    {
        return {x - rhs.x, y - rhs.y};
    }

    bool operator < (const Point& rhs) const
    {
        return tie(x, y) < tie(rhs.x, rhs.y);
    }
};

int ccw(Point p1, Point p2, Point p3)
{
    ll ret = (p2.x - p1.x) * (p3.y - p1.y) - (p3.x - p1.x) * (p2.y - p1.y);
    if(ret > 0) return 1;
    if(ret < 0) return -1;
    return 0;
}

const int MAXN = 1005;

int N;
ll D[MAXN][MAXN], P[MAXN][MAXN], Q[MAXN][MAXN];

struct Comparator {
    Point p;
    Comparator(Point p) : p(p) {}
    bool operator () (const Point& p1, const Point& p2) const
    {
        if((p1 < p) != (p2 < p)) return p1 < p2;
        return ccw(p, p1, p2) > 0;
    }
};

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N;
    vector<Point> dots(N);
    int _idx = 0;
    for(auto& [x, y, idx] : dots) cin >> x >> y, idx = _idx++;

    for(int i = 0; i < N; i++) {
        vector<Point> v;
        for(int j = 0; j < N; j++) {
            if(i == j) continue;
            v.push_back(dots[j]);
        }
        sort(v.begin(), v.end(), Comparator(dots[i]));

        int k = 1;
        for(int j = 0; j < N-1; j++) {
            while(ccw(dots[i], v[j], v[k%(N-1)]) >= 0 && k-j < N-1) k++;
            ll l = max(k - j - 2, 0);
            D[i][v[j].idx] = l;
        }
    }

    for(int i = 0; i < N; i++) {
        vector<Point> v;
        for(int j = 0; j < N; j++) {
            if(i == j) continue;
            v.push_back(dots[j]);
        }
        sort(v.begin(), v.end(), Comparator(dots[i]));

        ll s = 0;
        for(int j = 0; j < N-1; j++) {
            s += D[i][v[j].idx];
        }

        int k = -1;
        ll c1 = 0;
        ll c2 = 0;
        for(int j = 0; j < N-1; j++) {
            while(ccw(dots[i], v[j], v[(k+1)%(N-1)]) >= 0 && (k+1)-j+1 <= N-1) {
                k++;
                c1 += D[i][v[k%(N-1)].idx];
                c2 += D[v[k%(N-1)].idx][i];
            }
            c2 -= D[v[j].idx][i];
            P[i][v[j].idx] = c2 + s - c1;
            c1 -= D[i][v[j].idx];
        }
    }

    ll mx = -1;
    ll apb = (ll)(N-2) * (N-3) / 2;
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            if(i == j) continue;

            ll s = P[i][j] + P[j][i];

            mx = max(mx, (s - 2*apb) / 2);
            if((s-2*apb)%2 != 0) assert(false);
        }
    }
    cout << mx;
}