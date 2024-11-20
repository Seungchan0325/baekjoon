#include <bits/stdc++.h>

using namespace std;

const int MAXN = 505;
const int MAXQ = MAXN*MAXN;

struct DSU {
    int n;
    vector<int> root;
    DSU(int n) : n(n), root(n) {
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
        root[u] = v;
    }
};

int N, M, Q, C[MAXN], idx[MAXN][MAXN], S[MAXQ], E[MAXQ], L[MAXQ], R[MAXQ];
vector<int> graph[MAXN];

int main()
{
    cin >> N >> M;
    for(int i = 1; i <= N; i++) cin >> C[i];
    for(int i = 0; i < M; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    vector<tuple<int, int, int>> v;
    for(int i = 1; i <= N; i++) {
        for(int j = 1; j <= N; j++) {
            v.emplace_back(C[i] * C[j], i, j);
        }
    }
    sort(v.begin(), v.end());
    for(int i = 0; i < v.size(); i++) {
        auto [c, a, b] = v[i];
        idx[a][b] = i;
    }

    cin >> Q;
    for(int i = 1; i <= Q; i++) {
        cin >> S[i] >> E[i];
        L[i] = 0;
        R[i] = v.size();
    }

    while(true) {
        bool isdone = true;
        vector<vector<int>> q(v.size());
        for(int i = 1; i <= Q; i++) {
            if(L[i] + 1 < R[i]) {
                isdone = false;
                int m = (L[i] + R[i]) / 2;
                q[m].push_back(i);
            }
        }
        if(isdone) break;

        DSU dsu(v.size());
        for(int i = 0; i < v.size(); i++) {
            auto [c, a, b] = v[i];
            for(auto v : graph[a]) {
                if(idx[v][b] < i) {
                    dsu.merge(idx[v][b], i);
                }
            }
            for(auto v : graph[b]) {
                if(idx[a][v] < i) {
                    dsu.merge(idx[a][v], i);
                }
            }

            for(auto j : q[i]) {
                if(dsu.find(idx[S[j]][E[j]]) == dsu.find(idx[E[j]][S[j]])) {
                    R[j] = i;
                } else {
                    L[j] = i;
                }
            }
        }
    }

    for(int i = 1; i <= Q; i++) {
        cout << get<0>(v[L[i]]) << "\n";
    }
}