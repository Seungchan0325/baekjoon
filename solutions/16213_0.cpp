#include <bits/stdc++.h>

using namespace std;

const int MAXN = 200005;
const int MAXQ = 200005;

int N, M, Q, ans[MAXQ], root[MAXN], L[MAXQ], R[MAXQ], U[MAXQ], V[MAXQ];
vector<tuple<int, int, int>> edges;

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

int main()
{
    cin >> N >> M >> Q;
    for(int i = 1; i <= M; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        edges.emplace_back(u, v, w);
    }

    sort(edges.begin(), edges.end(), [](tuple<int, int, int> a, tuple<int, int, int> b) {
        return get<2>(a) > get<2>(b);
    });

    for(int i = 0; i < Q; i++) {
        cin >> U[i] >> V[i];
        L[i] = -1;
        R[i] = M;
    }

    while(true) {
        iota(root, root + N + 1, 0);
        vector<vector<int>> q(M);
        bool isdone = true;
        for(int i = 0; i < Q; i++) {
            if(L[i] + 1 == R[i]) {
                continue;
            }

            isdone = false;
            int m = (L[i] + R[i]) / 2;
            q[m].push_back(i);
        }

        if(isdone) break;

        for(int i = 0; i < M; i++) {
            auto [u, v, w] = edges[i];
            merge(u, v);

            for(auto j : q[i]) {
                if(find(U[j]) == find(V[j])) {
                    R[j] = i;
                } else {
                    L[j] = i;
                }
            }
        }
    }

    for(int i = 0; i < Q; i++) {
        cout << get<2>(edges[R[i]]) << "\n";
    }
}