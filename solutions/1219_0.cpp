#include <bits/stdc++.h>

using namespace std;

using llint = long long;

const llint INF = 1e18;

bool cango[55];
llint s, e, N, M, weight[55], dist[55];
vector<int> graph[55];
vector<tuple<llint, llint, llint>> edges;


bool visited[55];
void dfs(int u)
{
    visited[u] = true;
    for(auto v : graph[u]) {
        if(visited[v]) continue;
        dfs(v);
    }
}

int main()
{
    cin >> N >> s >> e >> M;
    for(llint i = 0; i < M; i++) {
        llint u, v, w;
        cin >> u >> v >> w;
        edges.emplace_back(u, v, -w);
        graph[u].push_back(v);
    }
    for(llint i = 0; i < N; i++) {
        cin >> weight[i];
    }

    for(int u = 0; u < N; u++) {
        memset(visited, 0, sizeof(visited));
        dfs(u);
        if(visited[e]) cango[u] = true;
    }

    if(!cango[s]) {
        cout << "gg";
        return 0;
    }

    fill(dist, dist + N, -INF);
    dist[s] = weight[s];
    for(llint i = 1; i < N; i++) {
        for(auto [u, v, w] : edges) {
            if(dist[u] <= -INF) continue;
            llint cand = dist[u] + w + weight[v];
            dist[v] = max(cand, dist[v]);
        }
    }

    bool is_inf = false;
    for(llint i = 0; i <= 50*N; i++) {
        for(auto [u, v, w] : edges) {
            if(dist[v] <= -INF) continue;
            llint cand = dist[u] + w + weight[v];
            if(cango[v] && dist[v] < cand) {
                is_inf = true;
                break;
            }
            dist[v] = max(cand, dist[v]);
        }
        if(is_inf) break;
    }

    if(is_inf) cout << "Gee";
    else if(dist[e] <= -INF) cout << "gg";
    else cout << dist[e];
}