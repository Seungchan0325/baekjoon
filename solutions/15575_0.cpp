#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1010101;

using ll = long long;

int N;
double dp[MAXN][2];
vector<ll> xs, mn, mx;

double dist(ll x1, ll y1, ll x2, ll y2)
{
    return sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
}

int main()
{
    cin >> N;
    vector<pair<ll, ll>> p(N);
    for(auto& [x, y] : p) {
        cin >> x >> y;
        xs.push_back(x);
    }
    sort(xs.begin(), xs.end());
    xs.erase(unique(xs.begin(), xs.end()), xs.end());
    mn.resize(xs.size(), 1e9);
    mx.resize(xs.size(), -1e9);
    for(auto& [x, y] : p) {
        int i = lower_bound(xs.begin(), xs.end(), x) - xs.begin();
        mn[i] = min(mn[i], y);
        mx[i] = max(mx[i], y);
    }

    for(int i = 1; i < xs.size(); i++) {
        dp[i][0] = max(
            dp[i-1][0] + dist(xs[i-1], mn[i-1], xs[i], mn[i]),
            dp[i-1][1] + dist(xs[i-1], mx[i-1], xs[i], mn[i])
        );
        dp[i][1] = max(
            dp[i-1][0] + dist(xs[i-1], mn[i-1], xs[i], mx[i]),
            dp[i-1][1] + dist(xs[i-1], mx[i-1], xs[i], mx[i])
        );
    }

    cout << fixed << setprecision(10);
    cout << max(dp[ssize(xs)-1][0], dp[ssize(xs)-1][1]);
}