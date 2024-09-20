#include <bits/stdc++.h>

using namespace std;

const int INF = 1e9;
const int MAXN = 1005;

int N, M, D[MAXN];
vector<tuple<int, int, int>> edges;

int main()
{
    cin >> N >> M;
    for(int i = 1; i <= N; i++) {
        edges.emplace_back(0, i, 1000000);
        edges.emplace_back(i, 0, -1);
    }
    for(int i = 1; i <= M; i++) {
        int a, op, b, x;
        cin >> a >> op >> b >> x;
        if(op == 0) {
            edges.emplace_back(b, a, x);
        } else {
            edges.emplace_back(a, b, -x);
        }
    }

    fill(D, D + N + 1, INF);
    D[0] = 0;
    for(int i = 0; i < N; i++) {
        for(auto [u, v, w] : edges) {
            if(D[u] >= INF) continue;
            if(D[u] + w < D[v]) {
                D[v] = D[u] + w;
            }
        }
    }

    for(auto [u, v, w] : edges) {
        if(D[u] >= INF) continue;
        if(D[u] + w < D[v]) {
            cout << "-1";
            return 0;
        }
    }

    for(int i = 1; i <= N; i++) {
        cout << D[i] << "\n";
    }
}