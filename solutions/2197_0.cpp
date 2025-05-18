#include <bits/stdc++.h>

using namespace std;

const int MAXN = 200;

int n, m, dp[MAXN][MAXN];
vector<int> g[MAXN];

void dfs(int u, int p)
{
    for(int i = 0; i <= m; i++) dp[u][i] = 1e9;
    dp[u][1] = 0;
    for(auto v : g[u]) {
        if(v == p) continue;
        dfs(v, u);
        for(int i = m; i >= 0; i--) {
            int k = 1e9;
            for(int j = 0; j <= i; j++) {
                k = min(k, dp[u][i-j] + dp[v][j]);
            }
            dp[u][i] = min(dp[u][i]+1, k);
        }
    }
}

int main()
{
    cin >> n >> m;
    for(int i = 1; i < n; i++) {
        int u, v; cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    int ans = 1e9;
    for(int i = 1; i <= n; i++) {
        dfs(i, -1);
        ans = min(ans, dp[i][m]);
    }
    cout << ans;
}