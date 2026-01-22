#include <bits/stdc++.h>

using namespace std;

const int MAXN = 101010;

struct DSU {
    vector<int> uf;
    void init(int n)
    {
        uf.resize(n);
        iota(uf.begin(), uf.end(), 0);
    }
    int find(int x)
    {
        if(uf[x] == x) return x;
        return uf[x] = find(uf[x]);
    }
    void merge(int x, int y)
    {
        x = find(x);
        y = find(y);
        uf[y] = x;
    }
};

int N, M, num[MAXN], low[MAXN], pv;
DSU p1, p2;
vector<int> g[MAXN];
vector<pair<int, int>> ans;

void dfs(int u, int p)
{
    bool pe = false;
    num[u] = low[u] = ++pv;
    for(auto v : g[u]) {
        if(v == p && !pe) {
            pe = true;
            continue;
        }
        if(!num[v]) {
            dfs(v, u);
            if(low[v] > num[u]) ans.push_back({u, v});
            low[u] = min(low[u], low[v]);
        } else {
            low[u] = min(low[u], num[v]);
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N >> M;
    p1.init(N+1);
    p2.init(N+1);
    for(int i = 0; i < M; i++) {
        int u, v;
        cin >> u >> v;
        if(p1.find(u) != p1.find(v)) {
            p1.merge(u, v);
            g[u].push_back(v);
            g[v].push_back(u);
        } else if(p2.find(u) != p2.find(v)) {
            p2.merge(u, v);
            g[u].push_back(v);
            g[v].push_back(u);
        }
    }
    for(int i = 1; i <= N; i++) {
        if(!num[i])
            dfs(i, -1);
    }
    for(auto [u, v] : ans) cout << u << " " << v << "\n";
}