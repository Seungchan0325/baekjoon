#include <bits/stdc++.h>

using namespace std;

using ll = long long;

struct Line {
    ll a, b;
    double x;
    ll get(ll _x)
    {
        return a * _x + b;
    }
};

double cross(Line a, Line b)
{
    return (double)(b.b - a.b) / (a.a - b.a);
}

const ll INF = 1e18;
const ll MAXN = 100005;

ll N, x[MAXN], h[MAXN], L[MAXN], R[MAXN];

int main()
{
    cout << fixed << setprecision(2);
    int tc;
    cin >> tc;
    while(tc--) {
        cin >> N;
        for(int i = 1; i <= N; i++) {
            cin >> x[i] >> h[i];
        }

        L[N+1] = -INF;
        for(int i = N; i >= 1; i--) {
            L[i] = max(L[i+1], 2*(-x[i]+h[i]));
        }

        R[0] = -INF;
        for(int i = 1; i <= N; i++) {
            R[i] = max(R[i-1], 2*(x[i]+h[i]));
        }

        ll ans = 0;

        vector<Line> v;
        v.push_back({L[1]/2, L[1]*L[1]/4, -INF});
        for(int i = 1; i <= N; i++) {
            int lo = 0;
            int hi = v.size();
            while(lo + 1 < hi) {
                int mid = (lo + hi) / 2;
                if(v[mid].x <= R[i]) lo = mid;
                else hi = mid;
            }

            ll area = v[lo].get(R[i]) + R[i]*R[i]/4;
            if(i == N) ans = area;

            ll l = L[i+1];
            Line line;
            line.a = l/2;
            line.b = area + l*l/4;

            while(v.size() >= 2 && v.back().x >= cross(v.back(), line)) {
                v.pop_back();
            }

            if(v.size() && v.back().a == line.a) {
                if(v.back().b < line.b) continue;
                v.pop_back();
            }
            line.x = cross(v.back(), line);
            v.push_back(line);
        }

        cout << (long double)ans/4 << "\n";
    }
}