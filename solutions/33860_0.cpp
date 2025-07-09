#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int MAXNM = 202020;

ll n, m, c, p, t[MAXNM], h[MAXNM];

int main()
{
    cin >> n >> m >> c >> p;
    for(int i = 1; i <= n+m; i++) cin >> t[i] >> h[i];

    ll s = 0;
    for(int i = 1; i <= n+m; i++) {
        if(t[i] == 2) h[i] += s;
        else s += h[i];
    }

    vector<int> v = {1};
    for(int i = 1; i <= n+m; i++) {
        if(t[i] == 2) v.push_back(h[i]);
    }
    sort(v.begin(), v.end());

    s = 0;
    ll mx = 0;
    for(int i = 1; i < v.size(); i++) {
        s += p - c * (v[i] - v[i-1]);
        mx = max(mx, s);
    }
    cout << mx << "\n";
}