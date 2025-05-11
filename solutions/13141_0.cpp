#include <bits/stdc++.h>

using namespace std;

const int MAXN = 202;

int N, M;
vector<pair<int, int>> g[MAXN];
vector<tuple<int, int, int>> edges;

int solve(int start)
{
    vector<int> D(N+1, 1e9);
    priority_queue<pair<int, int>> pq;
    D[start] = 0;
    pq.emplace(D[start], start);
    while(!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        d = -d;
        if(d > D[u]) continue;
        for(auto [v, w] : g[u]) {
            if(d + w < D[v]) {
                D[v] = d + w;
                pq.emplace(-D[v], v);
            }
        }
    }
    int ans = 0;
    for(auto [u, v, w] : edges) {
        if(D[u] > D[v]) swap(u, v);
        ans = max(ans, D[u] + (w-(D[u]-D[v]))/2);
    }
    return ans;
}

int main()
{
    cin >> N >> M;
    for(int i = 1; i <= M; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        w += w;
        g[u].emplace_back(v, w);
        g[v].emplace_back(u, w);
        edges.emplace_back(u, v, w);
    }
    int ans = 1e9;
    for(int i = 1; i <= N; i++) {
        ans = min(ans, solve(i));
    }
    cout << ans/2 << "." << 5*(ans%2) << "\n";
}