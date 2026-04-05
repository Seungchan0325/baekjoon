#include <bits/stdc++.h>
#include <queue>

using namespace std;

using ll = long long;

const int MAXN = 101010;

int N, M, Q, sparse[20][MAXN], dep[MAXN], num[MAXN], pv;
ll sparsew[20][MAXN];
vector<int> vtx;
vector<pair<int, ll>> g[MAXN];

void dfs(int u, int p)
{
    num[u] = ++pv;
    for(int i = 1; i < 20; i++) {
        sparse[i][u] = sparse[i-1][sparse[i-1][u]];
        sparsew[i][u] = sparsew[i-1][u] + sparsew[i-1][sparse[i-1][u]];
    }
    for(auto [v, w] : g[u]) {
        if(num[v]) {
            if(v != p && num[v] < num[u]) {
                vtx.push_back(u);
            }
            continue;
        }
        sparse[0][v] = u;
        sparsew[0][v] = w;
        dep[v] = dep[u] + 1;
        dfs(v, u);
    }
}

ll lca(int u, int v)
{
    if(dep[u] < dep[v]) swap(u, v);
    int diff = dep[u] - dep[v];
    ll w = 0;
    for(int i = 0; i < 20; i++) {
        if(diff&(1<<i)) {
            w += sparsew[i][u];
            u = sparse[i][u];
        }
    }
    if(u == v) return w;
    for(int i = 19; i >= 0; i--) {
        if(sparse[i][u] != sparse[i][v]) {
            w += sparsew[i][u];
            w += sparsew[i][v];
            u = sparse[i][u];
            v = sparse[i][v];
        }
    }
    w += sparsew[0][u];
    w += sparsew[0][v];
    u = sparse[0][u];
    return w;
}

vector<ll> dijkstra(int s)
{
    vector<ll> D(N+1);
    for(int i = 1; i <= N; i++) D[i] = 1e18;
    priority_queue<pair<ll, int>> pq;
    D[s] = 0;
    pq.push({0, s});
    while(!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        d = -d;
        if(d > D[u]) continue;
        for(auto [v, w] : g[u]) {
            if(d+w < D[v]) {
                D[v] = d+w;
                pq.push({-D[v], v});
            }
        }
    }
    return D;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N >> M;
    for(int i = 0; i < M; i++) {
        int u, v, w; cin >> u >> v >> w;
        g[u].push_back({v, w});
        g[v].push_back({u, w});
    }

    dfs(1, -1);
    sort(vtx.begin(), vtx.end());
    vtx.erase(unique(vtx.begin(), vtx.end()), vtx.end());
    vector<vector<ll>> dvtx;
    for(int i = 0; i < vtx.size(); i++) {
        dvtx.push_back(dijkstra(vtx[i]));
    }

    cin >> Q;
    while(Q--) {
        int s, e; cin >> s >> e;
        ll ans = lca(s, e);
        for(int i = 0; i < vtx.size(); i++) {
            ans = min(ans, dvtx[i][s] + dvtx[i][e]);
        }
        cout << ans << "\n";
    }
}
