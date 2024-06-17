#include <bits/stdc++.h>

using namespace std;

const int MAXN = 200005;

bool visited[MAXN];
int N, M, Q, par[MAXN], dep[MAXN], A[MAXN];
vector<int> graph[MAXN];

struct DSU {
    int root[MAXN];

    DSU(int N)
    {
        iota(root, root + N + 1, 0);
    }

    int find(int u)
    {
        if(root[u] == u) return u;
        return root[u] = find(root[u]);
    }

    void merge(int u, int v)
    {
        u = find(u);
        v = find(v);

        if(u == v) return;

        if(dep[u] > dep[v]) swap(u, v);

        root[v] = u;
    }
};

void dfs(int u, int p)
{
    visited[u] = true;
    for(auto v : graph[u]) {
        if(v == p) continue;

        dep[v] = dep[u] + 1;
        par[v] = u;
        dfs(v, u);
    }
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N >> M >> Q;

    set<pair<int, int>> edges;
    for(int i = 0; i < M; i++) {
        int u, v;
        cin >> u >> v;
        if(u > v) swap(u, v);
        edges.emplace(u, v);
    }

    vector<pair<int, int>> removed_edges;
    removed_edges.reserve(Q);
    for(int i = 0; i < Q; i++) {
        int u, v;
        cin >> u >> v;
        if(u > v) swap(u, v);
        edges.erase({u, v});
        removed_edges.emplace_back(u, v);
    }

    vector<pair<int, int>> nonst, tree(edges.begin(), edges.end());
    nonst.reserve(M);

    DSU st(N);
    for(auto [u, v] : tree) {
        if(st.find(u) != st.find(v)) {
            st.merge(u, v);
            graph[u].push_back(v);
            graph[v].push_back(u);
        } else {
            nonst.emplace_back(u, v);
        }
    }

    for(int i = Q-1; i >= 0; i--) {
        auto [u, v] = removed_edges[i];
        if(st.find(u) != st.find(v)) {
            st.merge(u, v);
            graph[u].push_back(v);
            graph[v].push_back(u);
        }
    }

    for(int i = 1; i <= N; i++) {
        if(!visited[i]) {
            dfs(i, -1);
        }
    }
    
    DSU con(N);
    DSU lca(N);
    int ans = 0;
    for(auto [u, v] : tree) {
        if(con.find(u) != con.find(v)) {
            con.merge(u, v);
            ans++;
        } else {
            u = lca.find(u);
            v = lca.find(v);
            while(u != v) {
                if(dep[u] < dep[v]) swap(u, v);
                assert(u != 0);
                ans--;
                lca.merge(par[u], u);
                u = lca.find(par[u]);
            }
        }
    }

    for(int i = Q-1; i >= 0; i--) {
        A[i] = ans;
        auto [u, v] = removed_edges[i];
        if(con.find(u) != con.find(v)) {
            con.merge(u, v);
            ans++;
        } else {
            u = lca.find(u);
            v = lca.find(v);
            while(u != v) {
                if(dep[u] < dep[v]) swap(u, v);
                assert(u != 0);
                ans--;
                lca.merge(par[u], u);
                u = lca.find(par[u]);
            }
        }
    }

    for(int i = 0; i < Q; i++) {
        cout << A[i] << "\n";
    }
}