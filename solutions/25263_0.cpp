#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int MAXN = 200005;

bool ans[MAXN];
int N, M, s[MAXN], root[MAXN];
ll sz[MAXN];
vector<int> vt[MAXN];
vector<pair<int, int>> edges;

int find(int u)
{
    if(root[u] == u) return u;
    return root[u] = find(root[u]);
}

void merge(int u, int v, bool is_v_remain)
{
    u = find(u);
    v = find(v);

    if(u == v) return;

    root[v] = u;
    sz[u] += sz[v];
    if(is_v_remain) {
        if(vt[u].size() < vt[v].size()) swap(vt[u], vt[v]);
        vt[u].insert(vt[u].end(), vt[v].begin(), vt[v].end());
    }
}

int main()
{
    cin >> N >> M;
    for(int i = 1; i <= N; i++) {
        cin >> s[i];
    }
    edges.resize(M);
    for(auto& [u, v] : edges) {
        cin >> u >> v;
        if(s[u] < s[v]) swap(u, v);
    }

    sort(edges.begin(), edges.end(), [](pair<int, int> a, pair<int, int> b) {
        return make_pair(s[a.first], s[a.second]) < make_pair(s[b.first], s[b.second]);
    });

    for(int i = 1; i <= N; i++) {
        root[i] = i;
        sz[i] = s[i];
        vt[i].push_back(i);
    }

    for(auto [u, v] : edges) {
        merge(u, v, sz[find(v)] >= s[u]);
    }

    for(auto i : vt[find(1)]) {
        ans[i] = true;
    }

    for(int i = 1; i <= N; i++) {
        cout << ans[i];
    }
}