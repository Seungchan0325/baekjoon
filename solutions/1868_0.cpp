#include <bits/stdc++.h>

using namespace std;

const int MAXN = 50505;

int N, r[MAXN], dp[MAXN][20];
vector<int> g[MAXN];

void dfs(int u, int p)
{
    for(auto v : g[u]) {
        if(v == p) continue;
        dfs(v, u);
        for(int i = 1; i < 20; i++) {
            dp[u][i] += dp[v][i];
        }
    }
    r[u] = 1;
    for(int i = 1; i < 20; i++) {
        if(dp[u][i] >= 2) r[u] = max(i+1, r[u]);
    }
    for(int i = r[u]; i < 20; i++) {
        if(dp[u][i]) continue;
        else {
            r[u] = i;
            break;
        }
    }
    for(int i = 1; i < r[u]; i++) {
        dp[u][i] = 0;
    }
    dp[u][r[u]] = 1;
    for(int i = r[u]; i < 20; i++) {
        if(dp[u][i]) dp[u][i] = 1;
    }
}

int main()
{
    cin >> N;
    for(int i = 1; i < N; i++) {
        int u, v; cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    dfs(1, -1);

    int mx = 0;
    for(int i = 1; i <= N; i++) mx = max(mx, r[i]);
    cout << mx-1 << "\n";
}