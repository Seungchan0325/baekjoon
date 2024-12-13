#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100005;
const int MAXM = 300005;
const int INF = 1e9;

bool used[MAXM];
int N, M;
vector<tuple<int, int, int>> edges;
vector<tuple<int, int, int>> graph[MAXN];

tuple<vector<int>, vector<int>, vector<int>> dijkstra(int start)
{
    vector<int> D(N+1, INF);
    vector<int> P(N+1, -1);
    vector<int> E(N+1, -1);
    priority_queue<pair<int, int>> pq;

    pq.emplace(D[start] = 0, start);
    while(!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        d = -d;

        if(d > D[u]) continue;

        for(auto [v, w, idx] : graph[u]) {
            if(d + w < D[v]) {
                P[v] = u;
                E[v] = idx;
                D[v] = d + w;
                pq.emplace(-D[v], v);
            }
        }
    }

    return make_tuple(D, P, E);
}

int main()
{
    cin >> N >> M;
    for(int i = 0; i < M; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        graph[u].emplace_back(v, w, i);
        graph[v].emplace_back(u, w, i);
        edges.emplace_back(u, v, w);
    }

    auto [D1, P1, E1] = dijkstra(1);
    if(D1[N] >= INF) {
        cout << -1;
        return 0;
    }

    for(int i = N; i != -1; i = P1[i]) {
        if(E1[i] >= 0)
            used[E1[i]] = true;
    }

    auto [D2, P2, E2] = dijkstra(N);

    int mn = INF;
    for(int i = 0; i < M; i++) {
        if(!used[i]) {
            auto [u, v, w] = edges[i];
            mn = min({mn, D1[u] + D2[v] + w, D2[u] + D1[v] + w});
        }
    }

    if(mn >= INF) {
        cout << -1;
        return 0;
    }

    int ans = D1[N] + mn;
    cout << ans;
}