#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int MAXN = 101010;

struct DSU {
    int N;
    vector<int> root;
    DSU(int _N) : N(_N) {
        root.resize(N+1);
        iota(root.begin(), root.end(), 0);
    }

    int find(int x)
    {
        if(root[x] == x) return x;
        return root[x] = find(root[x]);
    }

    void merge(int x, int y)
    {
        x = find(x);
        y = find(y);
        root[y] = x;
    }
};

ll N, M, C, dist[MAXN], par[MAXN];
vector<pair<int, ll>> g[MAXN];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> N >> M >> C;
    ll ans = 1e18;
    ll sum = 0;
    for(int i = 0; i < M; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        g[u].emplace_back(v, w);
        g[v].emplace_back(u, w);
        sum += w;
    }

    for(int i = 1; i <= N; i++) dist[i] = 1e18;
    
    DSU dsu(N);
    priority_queue<pair<ll, int>> pq;
    dist[1] = 0;
    pq.emplace(0, 1);
    while(pq.size()) {
        auto [d, u] = pq.top(); pq.pop();
        d = -d;
        if(d > dist[u]) continue;

        for(auto [v, w] : g[u]) {
            if(dsu.find(v) == dsu.find(par[u])) {
                sum -= w;
            }
        }
        dsu.merge(par[u], u);

        ans = min(ans, sum + C * d);

        for(auto [v, w] : g[u]) {
            if(dist[v] > d + w) {
                dist[v] = d + w;
                pq.emplace(-dist[v], v);
                par[v] = u;
            }
        }
    }

    cout << ans << "\n";
}