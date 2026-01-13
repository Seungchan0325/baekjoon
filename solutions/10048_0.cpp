#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int MAXN = 101010;
const ll inf = 0x3f3f3f3f3f3f3f3f;

ll N, M, X, H[MAXN], h[MAXN];
vector<pair<ll, ll>> g[MAXN];

int main()
{
    cin >> N >> M >> X;
    for(int i = 1; i <= N; i++) cin >> H[i];
    for(int i = 1; i <= M; i++) {
        ll u, v, w;
        cin >> u >> v >> w;
        if(H[u] >= w) g[u].push_back({v, w});
        if(H[v] >= w) g[v].push_back({u, w});
    }
    
    memset(h, 0x3f, sizeof(h));
    priority_queue<pair<ll, ll>> pq;
    pq.emplace(X, 1);
    while(pq.size()) {
        auto [d, u] = pq.top(); pq.pop();
        if(h[u] != inf) continue;
        h[u] = d;
        for(auto [v, w] : g[u]) {
            if(h[v] != inf) continue;
            pq.emplace(min(h[u] - w, H[v]), v);
        }
    }
    if(h[N] == inf) cout << "-1\n";
    else cout << X + H[N] - 2 * h[N] << "\n";
}