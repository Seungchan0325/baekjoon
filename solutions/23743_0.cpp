#include <bits/stdc++.h>

using namespace std;

int N, M;

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

const int MAXN = 202020;

int main()
{
    cin >> N >> M;
    vector<tuple<int, int, int>> edges;
    for(int i = 1; i <= M; i++) {
        int u, v, c;
        cin >> u >> v >> c;
        edges.emplace_back(c, u, v);
    }
    for(int i = 1; i <= N; i++) {
        int t;
        cin >> t;
        edges.emplace_back(t, i, N+1);
    }

    sort(edges.begin(), edges.end());
    DSU dsu(N+1);
    int ans = 0;
    for(auto [c, u, v] : edges) {
        if(dsu.find(u) != dsu.find(v)) {
            ans += c;
            dsu.merge(u, v);
        }
    }
    cout << ans;
}