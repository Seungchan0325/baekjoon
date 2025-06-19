#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int MAXN = 202020;

int n, p[MAXN], rp[MAXN], par[MAXN], dep[MAXN], sparse[MAXN][21];
ll dp[MAXN];
vector<int> g[MAXN];

void dfs(int u, int p)
{
    sparse[u][0] = p;
    for(int i = 1; i <= 20; i++)
        sparse[u][i] = sparse[sparse[u][i-1]][i-1];
    for(auto v : g[u]) {
        if(v == p) continue;
        dep[v] = dep[u] + 1;
        dfs(v, u);
    }
}

int find(int x)
{
    if(par[x] == x) return x;
    return par[x] = find(par[x]);
}

int lca(int u, int v)
{
    if(dep[u] < dep[v]) swap(u, v);
    int diff = dep[u] - dep[v];
    for(int i = 0; i <= 20; i++) {
        if(diff&(1<<i)) {
            u = sparse[u][i];
        }
    }

    if(u == v) return u;

    for(int i = 20; i >= 0; i--) {
        if(sparse[u][i] != sparse[v][i]) {
            u = sparse[u][i];
            v = sparse[v][i];
        }
    }
    return sparse[u][0];
}

void merge(int x, int y)
{
    x = find(x);
    y = find(y);
    par[y] = x;
    dp[x] = max(dp[x], dp[y] + dep[x] + dep[y] - 2 * dep[lca(x, y)]);
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> n;
    for(int i = 1; i <= n; i++) cin >> p[i], rp[p[i]] = i;
    for(int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    iota(par, par + n + 1, 0);

    dfs(1, 0);

    for(int i = 1; i <= n; i++) {
        int j = rp[i];
        for(auto k : g[j]) {
            if(p[k] < i) {
                merge(j, k);
            }
        }
    }

    cout << dp[rp[n]];
}