#include <bits/stdc++.h>

using namespace std;

#define int long long

const int MAXN = 55;

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

int n, a[MAXN], b[MAXN], c[MAXN], r;
char g[MAXN][MAXN];

signed main()
{
    cin >> n;
    for(int i = 1; i <= n; i++) cin >> a[i];
    for(int i = 1; i <= n; i++) cin >> b[i];
    for(int i = 1; i <= n; i++) cin >> c[i];
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            cin >> g[i][j];
        }
    }
    cin >> r;

    int ans = 0;
    for(int i = 1; i <= n; i++) {
        ans += c[i] * ((a[i] + b[i] - 1) * (b[i] - a[i])) / 2;
    }

    DSU dsu(n+1);
    vector<tuple<int, int, int>> edges;
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j < i; j++) {
            if(g[i][j] == 'Y') {
                dsu.merge(i, j);
                if(c[i] < c[j]) ans += (b[i] - a[i]) * c[i] * b[j] + (b[j] - a[j]) * c[j] * a[i];
                else ans += (b[i] - a[i]) * c[i] * a[j] + (b[j] - a[j]) * c[j] * b[i];
            } else {
                int w = r * (a[i] + a[j]);
                if(c[i] < c[j]) w += (b[i] - a[i]) * c[i] * b[j] + (b[j] - a[j]) * c[j] * a[i];
                else w += (b[i] - a[i]) * c[i] * a[j] + (b[j] - a[j]) * c[j] * b[i];
                edges.emplace_back(w, i, j);
            }
        }
    }

    sort(edges.begin(), edges.end());
    for(auto [w, i, j] : edges) {
        if(dsu.find(i) != dsu.find(j)) {
            dsu.merge(i, j);
            ans += w;
        }
    }

    cout << ans;
}