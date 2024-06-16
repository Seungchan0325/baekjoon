#include <bits/stdc++.h>

using namespace std;

using ll = long long;

#define X first
#define Y second

ll ccw(pair<ll, ll> a, pair<ll, ll> b, pair<ll, ll> c)
{
    return (b.X - a.X) * (c.Y - a.Y) - (c.X - a.X) * (b.Y - a.Y);
}

void convexHull(vector<pair<ll, ll>>& v)
{
    int N = v.size();
    sort(v.begin(), v.end());
    vector<pair<ll, ll>> up, dw;
    for(int i = 0; i < N; i++) {
        while(up.size() >= 2 && ccw(up.end()[-2], up.end()[-1], v[i]) >= 0) up.pop_back();
        while(dw.size() >= 2 && ccw(dw.end()[-2], dw.end()[-1], v[i]) <= 0) dw.pop_back();
        up.push_back(v[i]);
        dw.push_back(v[i]);
    }

    v = dw;
    for(int i = up.size() - 2; i >= 1; i--) v.push_back(up[i]);
}

double dot(pair<ll, ll> a, pair<ll, ll> b)
{
    return a.X * b.X + a.Y * b.Y;
}

double dist(pair<ll, ll> a, pair<ll, ll> b)
{
    double x = a.X - b.X;
    double y = a.Y - b.Y;
    return sqrt(x * x + y * y);
}

int main() {
    int N, L;
    cin >> N >> L;
    vector<pair<ll, ll>> v(N);
    for(auto& [x, y] : v) cin >> x >> y;

    convexHull(v);

    double sum = 0;
    int n = v.size();

    for(int i = 1; i <= n; i++) {
        sum += dist(v[i-1], v[i%n]);
    }

    for(int i = 2; i <= n+1; i++) {
        pair<ll, ll> a = {v[(i-2)%n].X - v[(i-1)%n].X, v[(i-2)%n].Y - v[(i-1)%n].Y};
        pair<ll, ll> b = {v[i%n].X - v[(i-1)%n].X, v[i%n].Y - v[(i-1)%n].Y};
        ll inner = dot(a, b);
        double theta = acos((double)inner / sqrt(a.X*a.X+a.Y*a.Y) / sqrt(b.X*b.X+b.Y*b.Y));
        theta = M_PI - theta;
        sum += L * theta;
    }

    printf("%.0lf", sum);
}