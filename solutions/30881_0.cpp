#include <bits/stdc++.h>

using namespace std;

using ll = long long;

ll dijkstra(int s, int e, ll n, vector<tuple<ll, ll, ll>>& edges)
{
    vector<ll> D(n+1, 2e18);
    vector<vector<pair<ll, ll>>> g(n+1);
    for(auto [u, v, w] : edges) {
        g[u].emplace_back(v, w);
    }

    priority_queue<pair<ll, ll>> pq;
    D[s] = 0;
    pq.emplace(0, s);
    while(!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        d = -d;
        if(d > D[u]) continue;
        for(auto [v, w] : g[u]) {
            if(d + w < D[v]) {
                pq.emplace(-d-w, v);
                D[v] = d + w;
            }
        }
    }

    return D[e];
}

const ll MAXN = 101010;

ll T, RD[MAXN], D[MAXN];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> T;
    for(ll i = 1; i <= T; i++) {
        ll n, m;
        cin >> n >> m;
        vector<tuple<ll, ll, ll>> e;
        for(int j = 0; j < m; j++) {
            int u, v, w;
            cin >> u >> v >> w;
            if(w < 0) {
                e.emplace_back(u, v, D[-w]);
                e.emplace_back(v, u, RD[-w]);
            } else {
                e.emplace_back(u, v, w);
            }
        }
        D[i] = dijkstra(1, 2, n, e);
        RD[i] = dijkstra(2, 1, n, e);
    }
    if(D[T] > 1e18) cout << "-1\n";
    else cout << D[T] << "\n";
}