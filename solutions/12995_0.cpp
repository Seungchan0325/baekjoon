#include <bits/stdc++.h>

using namespace std;

const int mod = 1e9 + 7;

const int MAXN = 55;

int n, k, dp[MAXN][MAXN];
vector<int> g[MAXN];

void dfs(int u, int p)
{
    dp[u][1] = 1;
    for(auto v : g[u]) {
        if(v == p) continue;
        dfs(v, u);
        for(int i = k; i >= 0; i--) {
            for(int j = i; j >= 0; j--) {
                dp[u][i] += ((long long)dp[u][i-j] * dp[v][j]) % mod;
                dp[u][i] %= mod;
            }
        }
    }
}

int main()
{
    cin >> n >> k;
    for(int i = 1; i < n; i++) {
        int u, v; cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    int ans = 0;
    dfs(1, -1);
    for(int i = 1; i <= n; i++) {
        ans = (ans + dp[i][k]) % mod;
    }
    cout << ans;
}