#include <bits/stdc++.h>

using namespace std;

const int MAXN = 202020;

struct DSU {
    int N;
    vector<int> root;
    DSU(int _N) : N(_N) {
        root.resize(N+1);
        iota(root.begin(), root.end(), 0);
    }

    int find(int x)
    {
        if(root[x] == x) return x;
        return root[x] = find(root[x]);
    }

    void merge(int x, int y)
    {
        x = find(x);
        y = find(y);
        root[y] = x;
    }
};

int N, M, sparse[MAXN][20], dep[MAXN];
vector<int> g[MAXN];

void dfs(int u, int p)
{
    for(int i = 1; i < 20; i++)
        sparse[u][i] = sparse[sparse[u][i-1]][i-1];
    for(auto v : g[u]) {
        if(v == p) continue;
        dep[v] = dep[u] + 1;
        sparse[v][0] = u;
        dfs(v, u);
    }
}

int lca(int u, int v)
{
    if(dep[u] < dep[v]) swap(u, v);
    int diff = dep[u] - dep[v];
    for(int i = 0; i < 20; i++)
        if(diff & (1<<i))
            u = sparse[u][i];
    
    if(u == v) return u;

    for(int i = 19; i >= 0; i--) {
        if(sparse[u][i] != sparse[v][i]) {
            u = sparse[u][i];
            v = sparse[v][i];
        }
    }
    return sparse[u][0];
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> N >> M;
    DSU dsu(N);
    for(int i = 0; i < M; i++) {
        int u, v;
        cin >> u >> v;
        if(dsu.find(u) != dsu.find(v)) {
            dsu.merge(u, v);
            g[u].push_back(v);
            g[v].push_back(u);
        }
    }
    dfs(1, -1);

    int q;
    cin >> q;
    while(q--) {
        int s, e;
        cin >> s >> e;

        int r = lca(s, e);

        int d = dep[s] + dep[e] - 2 * dep[r] - 1;
        cout << d << "\n";
    }
}