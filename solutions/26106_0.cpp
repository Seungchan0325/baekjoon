#include <bits/stdc++.h>

using namespace std;

const int MAXN = 30005;
const int MAXM = 10 * MAXN;

int m, n, k, s, e, D[MAXM];
vector<tuple<int, int, int>> edges;
vector<int> _link[MAXN], rlink[MAXN];
vector<int> graph[MAXM];

int main()
{
    cin >> m >> n >> k;
    cin >> s >> e;
    for(int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        edges.emplace_back(u, v, w);
        _link[u].push_back(i);
        rlink[v].push_back(i);
    }

    set<tuple<int, int, int>> forbidden;
    for(int i = 0; i < k; i++) {
        int x, y, z;
        cin >> x >> y >> z;
        forbidden.emplace(x, y, z);
    }

    if(s == e) {
        cout << "0";
        return 0;
    }

    for(int i = 0; i < m; i++) {
        auto [u, v, w] = edges[i];
        for(auto nxt : _link[v]) {
            auto [u1, v1, w1] = edges[nxt];
            if(forbidden.count(tie(u, v, v1)) == 0) {
                graph[i].push_back(nxt);
            }
        }
    }

    fill(D, D + m, 1e9);
    priority_queue<pair<int, int>> pq;
    for(auto i : _link[s]) {
        auto [u, v, w] = edges[i];
        pq.emplace(-w, i);
        D[i] = w;
    }

    while(!pq.empty()) {
        auto [d, i] = pq.top(); pq.pop();
        d = -d;

        if(D[i] < d) continue;

        auto [u, v, w] = edges[i];
        for(auto nxt : graph[i]) {
            auto [u1, v1, w1] = edges[nxt];
            if(d + w1 < D[nxt]) {
                D[nxt] = d + w1;
                pq.emplace(-D[nxt], nxt);
            }
        }
    }

    int ans = 1e9;
    for(auto i : rlink[e]) {
        ans = min(ans, D[i]);
    }

    if(ans == 1e9) cout << "-1";
    else cout << ans;
}