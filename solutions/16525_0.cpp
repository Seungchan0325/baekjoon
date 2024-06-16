#include <bits/stdc++.h>

using namespace std;

using ll = long long ;
using pll = pair<ll, ll>;

#define X first
#define Y second

pll operator+(pll a, pll b)
{
    return {a.X + b.X, a.Y + b.Y};
}

pll operator-(pll a, pll b)
{
    return {a.X - b.X, a.Y-b.Y};
}

ll ccw(pll a, pll b, pll c)
{
    return a.X*b.Y + b.X*c.Y + c.X*a.Y - a.Y*b.X - b.Y*c.X - c.Y*a.X;
}

int main()
{
    int N;
    cin >> N;
    vector<pll> v(N);
    for(auto& [x, y] : v) {
        cin >> x >> y;
    }

    auto tmp = v;
    v.insert(v.end(), tmp.begin(), tmp.end());

    ll ans = 0;
    int lst = 0;
    for(int i = 1; i <= N; i++) {
        while(lst + 2 < v.size() && ccw(v[i-1], v[i], v[lst+2] - v[lst+1] + v[i]) >= 0) {
            lst++;
        }

        int m = lst - i + 1;
        ans += (ll)m * (m - 1) / 2;
    }

    ans = (ll)N * (N-1) * (N-2) / 6 - ans;
    cout << ans;
}