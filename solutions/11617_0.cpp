#include <bits/stdc++.h>

using namespace std;

const int MAXN = 303030;

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

int n, m, q;
int deg[MAXN], cnt_deg[MAXN];
int mxdeg[MAXN], cnt_node[MAXN], cnt_edge[MAXN], is_cycle[MAXN];
int ansn, ansm, cnt_cycles, reportn[MAXN], reportm[MAXN];
DSU dsu(MAXN);

void update(int u)
{
    cnt_deg[deg[u]]--;
    if(deg[u] == 0) ansn++;
    cnt_deg[++deg[u]]++;
    mxdeg[dsu.find(u)] = max(mxdeg[dsu.find(u)], deg[u]);
}

void merge(int u, int v)
{
    ansm++;
    update(u); update(v);
    u = dsu.find(u);
    v = dsu.find(v);
    if(is_cycle[u]) cnt_cycles--, is_cycle[u] = false;
    if(is_cycle[v]) cnt_cycles--, is_cycle[v] = false;
    dsu.merge(u, v);
    if(u != v) {
        mxdeg[dsu.find(u)] = max(mxdeg[u], mxdeg[v]);
        cnt_node[dsu.find(u)] = cnt_node[u] + cnt_node[v];
        cnt_edge[dsu.find(u)] = cnt_edge[u] + cnt_edge[v];
    }
    cnt_edge[dsu.find(u)]++;

    u = dsu.find(u);
    if(cnt_node[u] == cnt_edge[u] && mxdeg[u] == 2) {
        cnt_cycles++;
        is_cycle[u] = true;
    }
}

int main()
{
    cin >> n >> m;
    vector<tuple<int, int, int>> edges(m);
    for(auto& [w, u, v] : edges) cin >> u >> v >> w;
    sort(edges.begin(), edges.end(), greater<>());
    cin >> q;
    vector<pair<int, int>> k(q);
    for(int i = 0; i < q; i++) {
        cin >> k[i].first; k[i].second = i;
    }
    sort(k.begin(), k.end(), greater<>());

    for(int i = 1; i <= n; i++) cnt_node[i] = 1;

    cnt_deg[0] = n;
    int idx = 0;
    for(int i = 0; i < q; i++) {
        while(idx < m && get<0>(edges[idx]) >= k[i].first) {
            auto [w, u, v] = edges[idx];
            merge(u, v);
            idx++;
        }
        reportn[k[i].second] = ansn - cnt_deg[2] + cnt_cycles;
        reportm[k[i].second] = ansm - cnt_deg[2] + cnt_cycles;
    }

    for(int i = 0; i < q; i++) {
        cout << reportn[i] << " " << reportm[i] << "\n";
    }
}