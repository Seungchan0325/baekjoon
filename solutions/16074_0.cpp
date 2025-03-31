#include <bits/stdc++.h>

using namespace std;

const int MAXN = 505;

using t4i = tuple<int, int, int, int>;

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

int n, m, q, h[MAXN][MAXN];

int main()
{
    cin >> n >> m >> q;
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            cin >> h[i][j];
        }
    }
    vector<pair<int, t4i>> edges;
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            edges.emplace_back(h[i][j], tuple{i, j, i, j});
            if(i + 1 <= n) {
                edges.emplace_back(max(h[i][j], h[i+1][j]), tuple{i, j, i+1, j});
            }
            if(j + 1 <= m) {
                edges.emplace_back(max(h[i][j], h[i][j+1]), tuple{i, j, i, j+1});
            }
        }
    }
    sort(edges.begin(), edges.end(), [](pair<int, t4i> a, pair<int, t4i> b) {
        return a < b;
    });
    int e = edges.size();

    vector<t4i> qrys(q);
    vector<int> l(q, 0), r(q, e);
    for(auto& [si, sj, ei, ej] : qrys) cin >> si >> sj >> ei >> ej;

    while(true) {
        bool isdone = true;
        vector<vector<int>> d(e);
        for(int i = 0; i < q; i++) {
            if(l[i] + 1 < r[i]) {
                isdone = false;
                int mid = (l[i] + r[i]) / 2;
                d[mid].push_back(i);
            }
        }

        if(isdone) break;

        DSU dsu((n+5)*(m+5));
        for(int i = 0; i < e; i++) {
            auto [i1, j1, i2, j2] = edges[i].second;
            dsu.merge(i1*m+j1, i2*m+j2);
            for(auto j : d[i]) {
                auto [si, sj, ei, ej] = qrys[j];
                if(dsu.find(si*m+sj) == dsu.find(ei*m+ej)) r[j] = i;
                else l[j] = i;
            }
        }
    }

    for(int i = 0; i < q; i++) {
        auto [si, sj, ei, ej] = qrys[i];
        if(tie(si, sj) == tie(ei, ej)) cout << h[si][sj] << "\n";
        else cout << edges[r[i]].first << "\n";
    }
}