#include "cyberland.h"

#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const double inf = 1e18;

double solve(int N, int M, int K, int H, std::vector<int> x, std::vector<int> y, std::vector<int> c, std::vector<int> arr) {
    vector<vector<pair<int, double>>> g(N);
    for(int i = 0; i < M; i++) {
        g[x[i]].emplace_back(y[i], c[i]);
        g[y[i]].emplace_back(x[i], c[i]);
    }

    priority_queue<pair<double, int>> pq;
    auto dijkstra = [&](vector<double>& dist) {
        while(!pq.empty()) {
            auto [d, u] = pq.top(); pq.pop();
            d = -d;
            if(d > dist[u] || u == H) continue;
            for(auto [v, w] : g[u]) {
                if(d + w < dist[v]) {
                    dist[v] = d + w;
                    pq.emplace(-dist[v], v);
                }
            }
        }
    };

    K = min(K, 70);
    vector<double> dist(N, inf);
    dist[0] = 0;
    pq.emplace(0, 0);
    dijkstra(dist);

    for(int i = 0; i < N; i++) {
        if(dist[i] < inf && arr[i] == 0) {
            dist[i] = 0;
            pq.emplace(-dist[i], i);
        }
    }
    dijkstra(dist);

    vector<int> v;
    for(int i = 0; i < N; i++) {
        if(dist[i] < inf && arr[i] == 2) {
            v.push_back(i);
        }
    }
    
    for(int i = 1; i <= K; i++) {
        for(auto j : v) {
            pq.emplace(-(dist[j] / 2.0), j);
        }
        dijkstra(dist);
    }
    if(dist[H] >= inf) return -1;
    return dist[H];
}