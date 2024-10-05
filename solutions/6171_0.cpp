#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const ll INF = 1e18;
const ll MAXN = 50005;

struct Line {
    ll a, b;
    double c;
    ll get(ll x)
    {
        return a * x + b;
    }
};

ll N, dp[MAXN];

double cross(Line a, Line b)
{
    return (double)(a.b - b.b) / (b.a - a.a);
}

signed main()
{
    cin >> N;
    vector<pair<ll, ll>> g(N);
    for(auto& [w, h] : g) cin >> w >> h;

    sort(g.begin(), g.end());

    vector<pair<ll, ll>> st;
    for(auto [w, h] : g) {
        while(st.size() && st.back().second <= h) st.pop_back();
        st.emplace_back(w, h);
    }

    vector<Line> v;
    for(ll i = 0; i < st.size(); i++) {
        Line line;
        line.a = st[i].second;
        line.b = dp[i-1];

        while(v.size() >= 2 && v.back().c >= cross(v.back(), line))
            v.pop_back();

        if(v.empty()) line.c = -INF;
        else line.c = cross(v.back(), line);
        v.push_back(line);

        ll x = st[i].first;
        ll lo = 0;
        ll hi = v.size();
        while(lo + 1 < hi) {
            ll mid = (lo + hi) / 2;
            if(v[mid].c <= x) lo = mid;
            else hi = mid;
        }

        dp[i] = v[lo].get(x);
    }

    cout << dp[st.size()-1];
}