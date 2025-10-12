#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int MAXN = 101010;

ll N, M, a[MAXN], d[MAXN];
vector<pair<ll, ll>> g[MAXN];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N >> M;
    for(int i = 0; i < N; i++) cin >> a[i];
    for(int i = 0; i < M; i++) {
        int u, v, w; cin >> u >> v >> w;
        g[u].emplace_back(v, w);
        g[v].emplace_back(u, w);
    }
    priority_queue<pair<ll, ll>> pq;
    for(int i = 0; i < N; i++) d[i] = 1e18;
    d[0] = 0;
    pq.emplace(-d[0], 0);
    while(pq.size()) {
        auto [dist, u] = pq.top(); pq.pop();
        dist = -dist;
        if(dist > d[u] || a[u]) continue;
        for(auto [v, w] : g[u]) {
            if(d[u]+w < d[v]) {
                d[v] = d[u] + w;
                pq.emplace(-d[v], v);
            }
        }
    }

    if(d[N-1] >= 1e18) cout << "-1\n";
    else cout << d[N-1] << "\n";
}