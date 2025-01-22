#include <bits/stdc++.h>

using namespace std;

const int MAXN = 201010;

bool erased[MAXN];
int N, K, ans = 1e9, sz[MAXN];
vector<pair<int, int>> g[MAXN];

void dfs(int u, int p)
{
    sz[u] = 1;
    for(auto [v, w] : g[u]) {
        if(v == p || erased[v]) continue;
        dfs(v, u);
        sz[u] += sz[v];
    }
}

int get_cent(int n, int u, int p)
{
    for(auto [v, w] : g[u]) {
        if(v == p || erased[v]) continue;
        if(sz[v] > n/2) return get_cent(n, v, u);
    }
    return u;
}

void dfs0(int u, int p, int dist, int c, map<int, int>& d)
{
    if(!d.count(dist)) d[dist] = 1e9;
    d[dist] = min(d[dist], c);
    for(auto [v, w] : g[u]) {
        if(v == p || erased[v]) continue;
        dfs0(v, u, dist + w, c + 1, d);
    }
}

void DnC(int u)
{
    dfs(u, -1);
    int cent = get_cent(sz[u], u, -1);
    erased[cent] = true;

    map<int, int> s;
    s[0] = 0;
    for(auto [v, w] : g[cent]) {
        if(erased[v]) continue;
        map<int, int> d;
        dfs0(v, -1, w, 1, d);
        for(auto [k, i] : d) {
            if(s.count(K-k)) {
                ans = min(ans, s[K-k] + i);
            }
        }
        dfs0(v, -1, w, 1, s);
    }

    for(auto [v, w] : g[cent])
        if(!erased[v]) DnC(v);
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> N >> K;
    for(int i = 1; i < N; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        g[u].emplace_back(v, w);
        g[v].emplace_back(u, w);
    }

    DnC(1);

    if(ans >= 1e9) cout << "-1";
    else cout << ans;
}