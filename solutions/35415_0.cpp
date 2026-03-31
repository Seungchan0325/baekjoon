#include <bits/stdc++.h>
#include <vector>

using namespace std;

using ll = long long;

const int MAXN = 101010;

int N, M, K, T;
vector<pair<int, ll>> g[MAXN];

vector<ll> dijkstra(int s)
{
    vector<ll> D(N+1, 1e18);
    priority_queue<pair<ll, int>> pq;
    pq.push({0, s});
    while(!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        d = -d;
        if(D[u] < d) continue;
        for(auto [v, w] : g[u]) {
            if(D[v] > d + w) {
                D[v] = d + w;
                pq.push({-D[v], v});
            }
        }
    }
    return D;
}

int main()
{
    cin >> N >> M >> K >> T;
    for(int i = 0; i < M; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        g[u].push_back({v, w});
        g[v].push_back({u, w});
    }

    auto d1 = dijkstra(1);
    auto dn = dijkstra(N);
    auto dk = dijkstra(K);
    ll ans = d1[K] + dn[K];
    for(int i = 1; i <= N; i++) {
        if(dk[i] <= T) {
            ll cand = d1[i] + dn[i] + T;
            ans = min(ans, cand);
        }
    }
    if(ans >= 1e18) cout << "-1\n";
    else cout << ans << "\n";
}
