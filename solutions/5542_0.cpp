#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100005;

struct DSU {
    int n;
    vector<int> root;
    DSU(int n) : n(n), root(n+1)
    {
        iota(root.begin(), root.end(), 0);
    }

    int find(int u)
    {
        if(root[u] == u) return u;
        return root[u] = find(root[u]);
    }

    void merge(int u, int v)
    {
        u = find(u);
        v = find(v);
        root[v] = u;
    }
};

int N, M, K, Q, D[MAXN], L[MAXN], R[MAXN], S[MAXN], E[MAXN];
vector<pair<int, int>> graph[MAXN];
vector<pair<int, int>> edges;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N >> M >> K >> Q;
    for(int i = 1; i <= M; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        graph[u].emplace_back(v, w);
        graph[v].emplace_back(u, w);
        edges.emplace_back(u, v);
    }
    
    for(int i = 1; i <= N; i++) D[i] = 1e9;
    priority_queue<pair<int, int>> q;
    for(int i = 1; i <= K; i++) {
        int u;
        cin >> u;
        q.emplace(0, u);
        D[u] = 0;
    }

    while(!q.empty()) {
        auto [d, u] = q.top(); q.pop();
        d = -d;
        if(d > D[u]) continue;

        for(auto [v, w] : graph[u]) {
            if(d + w < D[v]) {
                D[v] = d + w;
                q.emplace(-D[v], v);
            }
        }
    }

    sort(edges.begin(), edges.end(), [](pair<int, int> a, pair<int, int> b){
        return min(D[a.first], D[a.second]) > min(D[b.first], D[b.second]);
    });

    for(int i = 1; i <= Q; i++) {
        cin >> S[i] >> E[i];
        L[i] = 0;
        R[i] = M;
    }

    while(true) {
        bool isdone = true;
        vector<vector<int>> q(M);
        for(int i = 1; i <= Q; i++) {
            if(L[i] + 1 < R[i]) {
                isdone = false;
                int m = (L[i] + R[i]) / 2;
                q[m].push_back(i);
            }
        }
        if(isdone) break;

        DSU dsu(N);
        for(int i = 0; i < M; i++) {
            dsu.merge(edges[i].first, edges[i].second);
            for(auto j : q[i]) {
                if(dsu.find(S[j]) == dsu.find(E[j])) {
                    R[j] = i;
                } else {
                    L[j] = i;
                }
            }
        }
    }

    for(int i = 1; i <= Q; i++) {
        auto [u, v] = edges[R[i]];
        int d = min(D[u], D[v]);
        cout << d << "\n";
    }
}