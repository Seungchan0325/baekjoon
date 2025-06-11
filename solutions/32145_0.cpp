#include <bits/stdc++.h>

using namespace std;
using ll = long long;

ll ccw(pair<ll, ll> a, pair<ll, ll> b, pair<ll, ll> c)
{
    return (b.first - a.first) * (c.second - a.second) - (c.first - a.first) * (b.second - a.second);
}

void convexHull(vector<pair<ll, ll>>& v)
{
    int N = v.size();
    sort(v.begin(), v.end());
    vector<pair<ll, ll>> up, dw;
    for(int i = 0; i < N; i++) {
        while(up.size() >= 2 && ccw(up.end()[-2], up.end()[-1], v[i]) > 0) up.pop_back();
        while(dw.size() >= 2 && ccw(dw.end()[-2], dw.end()[-1], v[i]) < 0) dw.pop_back();
        up.push_back(v[i]);
        dw.push_back(v[i]);
    }

    v = dw;
    for(int i = up.size() - 2; i >= 1; i--) v.push_back(up[i]);
}

int n;

int main()
{
    cin >> n;
    vector<pair<ll, ll>> v(n);
    for(auto& [x, y] : v) cin >> x >> y;

    if(n == 1) {
        cout << "0\n";
        return 0;
    }
    convexHull(v);
    int k = v.size();
    cout << 3*n - k - 3;
}