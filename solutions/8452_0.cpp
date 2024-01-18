#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1005;
const int MAXM = 100005;
const int MAXQ = 200005;

int n, m, q, dist[MAXN];
bool not_use[MAXM];
vector<int> graph[MAXN];
pair<int, int> edges[MAXM];
pair<char, int> queries[MAXQ];

void bfs() {
    queue<int> q;
    q.push(1);

    memset(dist, 0x7F, sizeof(dist));
    dist[1] = 0;

    while(!q.empty()) {
        int node = q.front(); q.pop();

        for(auto next : graph[node])
            if(dist[node]+1 < dist[next]) {
                dist[next] = dist[node] + 1;
                q.push(next);
            }
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m >> q;
    for(int i = 1; i <= m; i++) {
        int u, v; cin >> u >> v;
        edges[i] = make_pair(u, v);
    }

    for(int i = 1; i <= q; i++) {
        auto& [t, d] = queries[i];
        cin >> t >> d;
        if(t == 'U') {
            not_use[d] = true;
        }
    }

    for(int i = 1; i <= m; i++) {
        if(not_use[i]) continue;
        auto [u, v] = edges[i];
        graph[u].push_back(v);
    }
    
    bfs();
    stack<int> ans;
    for(int i = q; i >= 1; i--) {
        auto [t, d] = queries[i];
        if(t == 'U') {
            auto [u, v] = edges[d];
            graph[u].push_back(v);
            if(dist[v] - dist[u] <= 1) continue;
            bfs();
        } else {
            if(dist[d] > MAXM) ans.push(-1);
            else ans.push(dist[d]);
        }
    }

    while(!ans.empty()) {
        cout << ans.top() << "\n";
        ans.pop();
    }
}