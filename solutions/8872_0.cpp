#include <bits/stdc++.h>

using namespace std;

const int MAXN = 101010;

bool chk[MAXN];
int N, M, L, dp[MAXN];
vector<pair<int, int>> g[MAXN];
vector<int> vst;

void dfs(int u, int p)
{
    dp[u] = 0;
    chk[u] = true;
    vst.push_back(u);
    for(auto [v, w] : g[u]) {
        if(v == p) continue;
        dfs(v, u);
        dp[u] = max(dp[u], dp[v] + w);
    }
}

void rdfs(int u, int p, int up)
{
    vector<int> lef(g[u].size()), rig(g[u].size());
    for(int i = 0; i < g[u].size(); i++) {
        auto [v, w] = g[u][i];
        if(v == p) continue;
        lef[i] = rig[i] = dp[v] + w;
    }
    for(int i = 1; i < g[u].size(); i++) lef[i] = max(lef[i], lef[i-1]);
    for(int i = ssize(g[u])-2; i >= 0; i--) rig[i] = max(rig[i], rig[i+1]);
    for(int i = 0; i < g[u].size(); i++) {
        auto [v, w] = g[u][i];
        if(v == p) continue;
        int mx = up;
        if(i>0) mx = max(mx, lef[i-1]);
        if(i+1<g[u].size()) mx = max(mx, rig[i+1]);
        rdfs(v, u, mx + w);
    }
    dp[u] = max(dp[u], up);
}

int main()
{
    cin >> N >> M >> L;
    for(int i = 0; i < M; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        g[u].emplace_back(v, w);
        g[v].emplace_back(u, w);
    }

    int ans = 0;
    vector<int> a;
    for(int i = 0; i < N; i++) {
        if(!chk[i]) {
            vst.clear();
            dfs(i, -1);
            rdfs(i, -1, 0);
            int mn = 1e9, mx = 0;
            for(auto j : vst) mn = min(mn, dp[j]), mx = max(mx, dp[j]);
            ans = max(ans, mx);
            a.push_back(mn);
        }
    }
    sort(a.begin(), a.end(), greater<>());
    ans = max(ans, a[0]);
    if(a.size()>=2) ans = max(ans, a[0] + a[1] + L);
    if(a.size()>=3) ans = max(ans, a[1] + a[2] + L + L);
    cout << ans;
}