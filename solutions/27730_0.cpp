#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int MAXN = 101010;

ll N, M, dp[MAXN<<1], sz[MAXN<<1], ans[MAXN<<1];
vector<pair<int, ll>> g[MAXN<<1];

void dfs(int u, int p)
{
    sz[u] = 1;
    for(auto [v, w] : g[u]) {
        if(v == p) continue;
        dfs(v, u);
        sz[u] += sz[v];
        dp[u] += dp[v] + w * sz[v];
    }
}

void updfs(int u, int p, ll udp, int n)
{
    ans[u] = dp[u] + udp;
    for(auto [v, w] : g[u]) {
        if(v == p) continue;
        ll nxt = udp + dp[u] - dp[v] - w * sz[v] + w * (n - sz[v]);
        updfs(v, u, nxt, n);
    }
}

int main()
{
    cin >> N;
    for(int i = 1; i < N; i++) {
        int u, v, w; cin >> u >> v >> w;
        g[u].emplace_back(v, w);
        g[v].emplace_back(u, w);
    }
    cin >> M;
    for(int i = 1; i < M; i++) {
        int u, v, w; cin >> u >> v >> w;
        u+=N; v+=N;
        g[u].emplace_back(v, w);
        g[v].emplace_back(u, w);
    }

    dfs(1, -1);
    dfs(N+1, -1);
    updfs(1, -1, 0, N);
    updfs(N+1, -1, 0, M);

    int i = min_element(ans+1, ans+N+1) - ans;
    int j = min_element(ans+N+1, ans+N+M+1) - ans;
    cout << i << " " << j-N << "\n";
    cout << ans[i] * M + ans[j] * N + N * M;
}