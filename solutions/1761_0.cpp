#include <bits/stdc++.h>

using namespace std;

using pii = pair<int, int>;

const int MAXN = 40005;
const int LOGN = 16;

int n, m, parents[MAXN][LOGN + 1], dist[MAXN][LOGN + 1], depths[MAXN];
vector<pii> graph[MAXN];

void dfs(int node, int depth, int parent)
{
    depths[node] = depth;
    for(int i = 1; i <= LOGN; i++) {
        parents[node][i] = parents[parents[node][i-1]][i-1];
        dist[node][i] = dist[node][i-1] + dist[parents[node][i-1]][i-1];
    }

    for(auto [next, distance] : graph[node]) {
        if(next == parent) continue;
        
        parents[next][0] = node;
        dist[next][0] = distance;
        dfs(next, depth + 1, node);
    }
}

int lca(int u, int v)
{
    if(depths[u] < depths[v]) swap(u, v);

    int ret = 0;

    int diff = depths[u] - depths[v];
    for(int i = 0; i < 32; i++) {
        if(diff & (1<<i)) {
            ret += dist[u][i];
            u = parents[u][i];
        }
    }

    if(u != v) {
        for(int i = LOGN; i >= 0; i--) {
            if(parents[u][i] != parents[v][i]) {
                ret += dist[u][i] + dist[v][i];
                u = parents[u][i];
                v = parents[v][i];
            }
        }
        ret += dist[u][0] + dist[v][0];
    }
    return ret;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> n;
    for(int i = 1; i < n; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        graph[u].emplace_back(v, w);
        graph[v].emplace_back(u, w);
    }
    
    dfs(1, 0, -1);
    cin >> m;
    for(int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        cout << lca(u, v) << "\n";
    }
}