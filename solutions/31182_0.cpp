#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const ll INF = 1e9;
const ll MAXN = 1e5 + 5;

ll N, a[MAXN], t[MAXN], dp[MAXN][2];
vector<ll> graph[MAXN];

void dfs(ll u, ll p)
{
    dp[u][0] = dp[u][1] = 0;
    ll sum = 0;
    pair<ll, ll> mx1 = {-INF, 0}, mx2 = {-INF, 0};
    for(auto v : graph[u]) {
        if(v == p) continue;

        dfs(v, u);

        dp[u][0] = max(dp[u][0], a[v]);
        sum += dp[v][0];

        if(t[v] == 3) {
            if(a[v] >= mx1.first) {
                mx2 = mx1;
                mx1 = {a[v], v};
            } else if(a[v] >= mx2.first) {
                mx2 = {a[v], v};
            }
        }
    }

    dp[u][0] += sum;
    dp[u][1] = sum;
    for(auto v : graph[u]) {
        if(v == p) continue;

        bool flip = false;
        if(mx1.second == v) { swap(mx1, mx2); flip = true; }
        dp[u][0] = max(dp[u][0], sum - dp[v][0] + dp[v][1] + a[v] + mx1.first);
        if(flip) swap(mx1, mx2);
    }
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    ll T;
    cin >> T;
    while(T--) {
        cin >> N;
        for(ll i = 1; i <= N; i++) cin >> a[i];
        for(ll i = 1; i <= N; i++) cin >> t[i];

        for(ll i = 1; i < N; i++) {
            ll u, v;
            cin >> u >> v;
            graph[u].push_back(v);
            graph[v].push_back(u);
        }

        dfs(1, -1);

        cout << dp[1][0] + a[1] << "\n";

        for(ll i = 1; i <= N; i++) {
            graph[i].clear();
        }
    }
}