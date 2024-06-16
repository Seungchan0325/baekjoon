#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100005;

int N, M, H[MAXN], root[MAXN], ans[MAXN], dep[MAXN], par[MAXN];
vector<tuple<int, int, int>> edges;
vector<int> graph[MAXN];

int find(int u)
{
    if(root[u] == u) return u;
    return root[u] = find(root[u]);
}

bool Union(int u, int v)
{
    u = find(u);
    v = find(v);
    if(u == v) return false;
    if(dep[u] > dep[v]) swap(u, v);
    root[v] = u;
    return true;
}

void dfs(int u, int p) 
{
    for(auto v : graph[u]) {
        if(v == p) continue;
        par[v] = u;
        dep[v] = dep[u] + 1;
        dfs(v, u);
    }
}

void LCA(int w, int u, int v)
{
    u = find(u);
    v = find(v);
    vector<int> upd;
    while(u != v) {
        if(dep[u] < dep[v]) swap(u, v);
        upd.push_back(u);
        Union(u, par[u]);
        u = find(par[u]);
    }
    upd.push_back(u);
    for(auto i : upd) {
        if(ans[i] == -1) {
            ans[i] = w;
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N >> M;
    for(int i = 1; i <= N; i++) cin >> H[i];
    for(int i = 0; i < M; i++) {
        int u, v;
        cin >> u >> v;
        edges.emplace_back(abs(H[u] - H[v]), u, v);
    }

    memset(ans, -1, sizeof(ans));
    iota(root, root + N + 1, 0);
    sort(edges.begin(), edges.end());

    vector<tuple<int, int, int>> nonmst;

    for(auto [w, u, v] : edges) {
        if(Union(u, v)) {
            graph[u].push_back(v);
            graph[v].push_back(u);
        } else {
            nonmst.emplace_back(w, u, v);
        }
    }

    dep[1] = 1;
    dfs(1, -1);

    iota(root, root + N + 1, 0);
    for(auto [w, u, v] : nonmst) {
        LCA(w, u, v);
    }

    for(int i = 1; i <= N; i++) {
        cout << ans[i] << " ";
    }
}