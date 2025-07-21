#include <bits/stdc++.h>

using namespace std;

const int MAXN = 10101;

int n, dp[MAXN][2], a[MAXN], b[MAXN], pv;
vector<int> g[MAXN];

void dfs(int u, int p)
{
    if(p == -1) {
        a[u] = ++pv;
        b[u] = ++pv;
    } else {
        b[u] = ++pv;
    }
    for(auto v : g[u]) {
        if(v == p) continue;
        a[v] = b[u];
        dfs(v, u);
        swap(a[u], b[u]);
    }
}

int main()
{
    cin >> n;
    for(int i = 1; i < n; i++) {
        int u, v; cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    if(n == 2) {
        cout << "0 1\n0 1\n";
        return 0;
    }

    dfs(1, -1);

    for(int i = 1; i <= n; i++) cout << a[i] << " " << b[i] << "\n";
}