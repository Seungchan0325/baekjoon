#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const ll MAXN = 505050;
const ll inf = 1e18;

ll N, M, par[MAXN], dist[MAXN], W[MAXN];
vector<pair<ll, ll>> g[MAXN];

signed main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> N >> M;
    for(ll i = 0; i < M; i++) {
        ll u, v, t;
        cin >> u >> v >> t;
        g[u].emplace_back(v, t);
        g[v].emplace_back(u, t);
    }

    for(ll i = 1; i <= N; i++) dist[i] = W[i] = inf;
    dist[1] = 0;
    priority_queue<tuple<ll, ll, ll>> pq;
    pq.emplace(0, 0, 1);
    while(!pq.empty()) {
        auto [d, a, u] = pq.top(); pq.pop();
        d = -d;
        a = -a;
        if(pair(dist[u], W[u]) < pair(d, a)) continue;
        for(auto [v, w] : g[u]) {
            if(pair(dist[v], W[v]) > pair(d + w, w)) {
                dist[v] = d + w;
                W[v] = w;
                pq.emplace(-dist[v], -w, v);
                par[v] = u;
            }
        }
    }
    ll ans = 0;
    for(int i = 2; i <= N; i++) {
        ans += W[i];
    }
    cout << ans;
}