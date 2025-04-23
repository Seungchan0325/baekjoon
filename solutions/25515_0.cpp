#include <bits/stdc++.h>

using namespace std;

#define int long long

int n, a[101010];
vector<int> g[101010];

int dfs(int u, int p)
{
    int dp = a[u];
    for(auto v : g[u]) {
        if(v == p) continue;
        dp += max(dfs(v, u), 0LL);
    }
    return dp;
}

signed main()
{
    cin >> n;
    for(int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    for(int i = 0; i < n; i++) cin >> a[i];

    int ans = dfs(0, -1);
    cout << ans;
}