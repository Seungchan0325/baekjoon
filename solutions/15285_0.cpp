#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100005;

bool visited[MAXN];
vector<int> g1[MAXN], g2[MAXN];
vector<pair<int, int>> remains;
multiset<pair<int, int>> edges;

void dfs1(int u)
{
    visited[u] = true;
    for(auto v : g1[u]) {
        if(visited[v]) continue;
        remains.emplace_back(u, v);
        dfs1(v);
    }
}

void dfs2(int u)
{
    visited[u] = true;
    for(auto v : g2[u]) {
        if(visited[v]) continue;
        remains.emplace_back(v, u);
        dfs2(v);
    }
}

int main()
{
    int tc;
    cin >> tc;
    while(tc--) {
        int n, m;
        cin >> n >> m;
        for(int i = 0; i < m; i++) {
            int u, v;
            cin >> u >> v;
            g1[u].push_back(v);
            g2[v].push_back(u);
            edges.insert({u, v});
        }

        memset(visited, 0, sizeof(visited));
        dfs1(1);
        memset(visited, 0, sizeof(visited));
        dfs2(1);

        assert(remains.size() == 2 * (n - 1));

        for(auto i : remains) edges.erase(i);
        while(edges.size() != m - 2*n) edges.erase(edges.begin());

        // assert(edges.size() == m - 2*n);

        for(auto [u, v] : edges) {
            cout << u << " " << v << "\n";
        }

        edges.clear();
        remains.clear();
        for(int i = 1; i <= n; i++) {
            g1[i].clear();
            g2[i].clear();
        }
    }
}