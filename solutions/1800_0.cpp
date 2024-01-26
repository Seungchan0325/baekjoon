#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1005;

int n, p, k, dist[MAXN][MAXN];
vector<tuple<int, int>> graph[MAXN];
// vector<tuple<int, int, int>> edges;

int main()
{
    cin >> n >> p >> k;
    // edges.reserve(p);
    for(int i = 0; i < p; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        // edges.emplace_back(u, v, w);
        graph[u].emplace_back(v, w);
        graph[v].emplace_back(u, w);
    }

    memset(dist, 0x7F, sizeof(dist));
    // cnt_free, cost, cur
    priority_queue<tuple<int, int, int>> pq;
    pq.emplace(0, 0, 1);
    dist[1][0] = 0;

    while(!pq.empty()) {
        auto [cnt_free, cost, cur] = pq.top();
        cost = -cost;
        pq.pop();
        for(auto [next, ncost] : graph[cur]) {
            if(cnt_free < k && dist[next][cnt_free + 1] > cost) {
                dist[next][cnt_free + 1] = cost;
                pq.emplace(cnt_free + 1, -dist[next][cnt_free + 1], next);
            }

            if(dist[next][cnt_free] > max(cost, ncost)) {
                dist[next][cnt_free] = max(cost, ncost);
                pq.emplace(cnt_free, -dist[next][cnt_free], next);
            }
        }
    }

    int min_v = 987654321;
    for(int i = 0; i <= k; i++) {
        min_v = min(dist[n][i], min_v);
    }

    if(min_v >= 987654321) cout << -1;
    else cout << min_v;
}