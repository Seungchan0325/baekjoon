#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int MAXN = 202020;

ll sum[MAXN], up[MAXN], dp[MAXN];
int n, q, r, sz[MAXN], par[MAXN], in[MAXN], out[MAXN], dfsn;
vector<int> g[MAXN], t[MAXN];

void dfs(int u, int p)
{
    in[u] = ++dfsn;
    sz[u] = 1;
    for(auto v : g[u]) {
        if(v == p) continue;
        par[v] = u;
        dfs(v, u);
        t[u].push_back(v);
        sz[u] += sz[v];
    }
    out[u] = ++dfsn;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> n >> q;
    for(int i = 1; i < n; i++) {
        int u, v; cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    r = 1;
    dfs(1, -1);
    for(int i = 1; i <= n; i++) {
        int gsz = g[i].size();
        ll s = 1;
        for(int j = 0; j < gsz; j++) {
            int k = g[i][j];
            ll sub = 0;
            if(k == par[i]) sub = n - sz[i];
            else sub = sz[k];
            sum[i] += s * sub;
            s += sub;
        }
    }

    while(q--) {
        int op, x;
        cin >> op >> x;
        if(op == 1) {
            r = x;
        } else {
            if(r == x) {
                cout << sum[x] << "\n";
            } else if(!(in[x] <= in[r] && out[r] <= out[x])) {
                ll m = n - sz[x];
                ll ans = sum[x] - sz[x] * m;
                cout << ans << "\n";
            } else {
                int lo = 0;
                int hi = ssize(t[x]);
                while(lo + 1 < hi) {
                    int mid = (lo + hi) / 2;
                    if(in[t[x][mid]] <= in[r]) lo = mid;
                    else hi = mid;
                }
                ll m = sz[t[x][lo]];
                ll p = n - m;
                ll ans = sum[x] - p * m;
                cout << ans << "\n";
            }
        }
    }
}