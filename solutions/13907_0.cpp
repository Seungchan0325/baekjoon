#include <bits/stdc++.h>

using namespace std;

using ll = long long;

int N, M, K, S, D, p[30303];
vector<tuple<int, int, ll>> edges;

pair<ll, int> dijkstra(const vector<tuple<int, int, ll>>& e)
{
    vector<vector<pair<int, ll>>> g(N+1);
    for(auto [u, v, w] : e) {
        g[u].emplace_back(v, w);
        g[v].emplace_back(u, w);
    }
    vector<ll> dist(N+1, 1e18), c(N+1);
    dist[S] = 0;
    priority_queue<pair<ll, int>> pq;
    pq.emplace(-dist[S], S);
    while(!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        d = -d;
        if(d > dist[u]) continue;
        for(auto [v, w] : g[u]) {
            if(d+w < dist[v]) {
                dist[v] = d+w;
                c[v] = c[u] + 1;
                pq.emplace(-dist[v], v);
            }
        }
    }
    return {dist[D], c[D]};
}

vector<tuple<int, int, ll>> add(vector<tuple<int, int, ll>> e, ll x)
{
    for(auto& [u, v, w] : e) w += x;
    return e;
}

int nxt(int a)
{
    int prv = dijkstra(add(edges, a)).second;
    int lo = a;
    int hi = p[K] + 1;
    while(lo + 1 < hi) {
        int mid = (lo + hi) / 2;
        if(dijkstra(add(edges, mid)).second == prv) lo = mid;
        else hi = mid;
    }
    return lo;
}

int main()
{
    cin >> N >> M >> K;
    cin >> S >> D;
    for(int i = 0; i < M; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        edges.emplace_back(u, v, w);
    }
    for(int i = 1; i <= K; i++) cin >> p[i], p[i] += p[i-1];
    int n = nxt(0);
    auto [d, c] = dijkstra(edges);
    cout << dijkstra(edges).first << "\n";
    for(int i = 1; i <= K; i++) {
        if(p[i] > n) {
            tie(d, c) = dijkstra(add(edges, p[i]));
            n = nxt(p[i]);
        }
        else d += c * (p[i] - p[i-1]);
        cout << d << "\n";
    }
}