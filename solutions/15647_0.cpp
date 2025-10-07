#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int MAXN = 303030;

ll N, dp[MAXN], sz[MAXN], ans[MAXN];
vector<pair<int, int>> g[MAXN];

void dfs(int u, int p)
{
    sz[u] = 1;
    for(auto [v, w] : g[u]) {
        if(v == p) continue;
        dfs(v, u);
        sz[u] += sz[v];
        dp[u] += dp[v] + sz[v] * w;
    }
}

void dfs1(int u, int p, ll udp)
{
    ans[u] = udp + dp[u];
    for(auto [v, w] : g[u]) {
        if(v == p) continue;
        dfs1(v, u, udp + dp[u] - (dp[v] + w * sz[v]) + w * (N-sz[v]));
    }
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N;
    for(int i = 1; i < N; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        g[u].emplace_back(v, w);
        g[v].emplace_back(u, w);
    }

    dfs(1, -1);
    dfs1(1, -1, 0);

    for(int i = 1; i <= N; i++) {
        cout << ans[i] << "\n";
    }
}