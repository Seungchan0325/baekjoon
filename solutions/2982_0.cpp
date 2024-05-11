#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1005;

int N, M, A, B, K, G, king[MAXN], t[MAXN], dist[MAXN];
vector<pair<int, int>> graph[MAXN];

int main()
{
    cin >> N >> M;
    cin >> A >> B >> K >> G;
    for(int i = 0; i < G; i++) cin >> king[i];
    
    for(int i = 0; i < M; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        graph[u].emplace_back(v, w);
        graph[v].emplace_back(u, w);
    }

    t[0] -= K;
    for(int i = 0; i < G; i++) {
        for(auto [u, w] : graph[king[i]]) {
            if(u == king[i+1]) {
                t[i+1] = w;
                break;
            }
        }
        t[i+1] += t[i];
    }

    memset(dist, 0x7F, sizeof(dist));

    priority_queue<pair<int, int>> pq;
    dist[A] = 0;
    pq.emplace(0, A);

    while(!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        d = -d;
        if(d > dist[u]) continue;

        int kpos = upper_bound(t, t + G + 1, d) - t - 1;
        for(auto [v, w] : graph[u]) {
            int nd = d + w;
            if(u == king[kpos] && v == king[kpos + 1]) nd = t[kpos+1] + w;
            else if(v == king[kpos] && u == king[kpos + 1]) nd = t[kpos+1] + w;

            if(nd < dist[v]) {
                dist[v] = nd;
                pq.emplace(-nd, v);
            }
        }
    }

    cout << dist[B];
}