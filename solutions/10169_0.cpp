#include <bits/stdc++.h>

using namespace std;

using llint = long long int;

const int INF = 1e9 + 5;
const int MAXN = 100005;
const int MAXM = 300005;

// Union-Find
int root[MAXN];
// Segment Tree
int tree[4*MAXN], lazy[4*MAXN];
// HLD
bool visited[MAXN];
int pv, dep[MAXN], par[MAXN], sz[MAXN], top[MAXN], in[MAXN];
vector<int> graph[MAXN];
//
int N, M;
llint ans[MAXM];
vector<int> inp[MAXN];
vector<tuple<int, int, int, int>> edges, mst, non_mst;

int find(int u)
{
    if(root[u] == u) return u;
    return root[u] = find(root[u]);
}

bool Union(int u, int v)
{
    u = find(u);
    v = find(v);
    if(u == v) return false;
    root[v] = u;
    return true;
}

void init(int s = 1, int e = N, int idx = 1)
{
    if(s == e) {
        tree[idx] = INF;
        return;
    }

    int m = (s + e) >> 1;
    init(s, m, 2*idx); init(m+1, e, 2*idx+1);
    tree[idx] = min(tree[2*idx], tree[2*idx+1]);
}

void propagate(int s, int e, int idx)
{
    if(lazy[idx]) {
        tree[idx] = min(lazy[idx], tree[idx]);
        if(s != e) {
            for(auto nidx : {2*idx, 2*idx+1})
                if((lazy[nidx] == 0) != (lazy[nidx] > lazy[idx]))
                    lazy[nidx] = lazy[idx];
        }
        lazy[idx] = 0;
    }
}

void update(int l, int r, int v, int s = 1, int e = N, int idx = 1)
{
    propagate(s, e, idx);
    if(e < l || r < s) return;
    if(l <= s && e <= r) {
        lazy[idx] = v;
        propagate(s, e, idx);
        return;
    }

    int m = (s + e) >> 1;
    update(l, r, v, s, m, 2*idx);
    update(l, r, v, m+1, e, 2*idx+1);
    tree[idx] = min(tree[2*idx], tree[2*idx+1]);
}

int query(int l, int r, int s = 1, int e = N, int idx = 1)
{
    propagate(s, e, idx);
    if(e < l || r < s) return INF;
    if(l <= s && e <= r) return tree[idx];
    int m = (s + e) >> 1;
    return min(query(l, r, s, m, 2*idx), query(l, r, m+1, e, 2*idx+1));
}

void dfs(int u)
{
    visited[u] = true;
    for(auto v : inp[u]) {
        if(visited[v]) continue;
        dfs(v);
        graph[u].push_back(v);
    }
}

void dfs1(int u)
{
    sz[u] = 1;
    for(auto& v : graph[u]) {
        dep[v] = dep[u] + 1; par[v] = u;
        dfs1(v); sz[u] += sz[v];
        if(sz[v] > sz[graph[u][0]]) swap(v, graph[u][0]);
    }
}

void dfs2(int u)
{
    in[u] = ++pv;
    for(auto v : graph[u]) {
        top[v] = (v == graph[u][0]) ? top[u] : v;
        dfs2(v);
    }
}

void hld_update(int u, int v, int value)
{
    while(top[u] ^ top[v]) {
        if(dep[top[u]] < dep[top[v]]) swap(u, v);
        update(in[top[u]], in[u], value);
        u = par[top[u]];
    }
    if(dep[u] > dep[v]) swap(u, v);
    update(in[u]+1, in[v], value);
}

int hld_query(int u, int v)
{
    int ret = INF;
    while(top[u] ^ top[v]) {
        if(dep[top[u]] < dep[top[v]]) swap(u, v);
        ret = min(query(in[top[u]], in[u]), ret);
        u = par[top[u]];
    }
    if(dep[u] > dep[v]) swap(u, v);
    ret = min(query(in[u]+1, in[v]), ret);
    return ret;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N >> M;
    edges.resize(M);
    int last = 0;
    for(auto& [w, u, v, idx] : edges) {
        cin >> u >> v >> w;
        idx = last++;
    }
    sort(edges.begin(), edges.end());
    iota(root, root + N + 1, 0);
    llint MST = 0;
    for(auto [w, u, v, idx] : edges) {
        if(Union(u, v)) {
            MST += w;
            mst.emplace_back(w, u, v, idx);
            inp[u].push_back(v);
            inp[v].push_back(u);
        } else {
            non_mst.emplace_back(w, u, v, idx);
        }
    }

    dfs(1);
    dfs1(1);
    top[1] = 1; dfs2(1);

    init();
    for(auto [w, u, v, idx] : non_mst) {
        hld_update(u, v, w);
        ans[idx] = MST;
    }

    for(auto [w, u, v, idx] : mst) {
        int alternative = hld_query(u, v);
        if(alternative >= INF) ans[idx] = -1;
        else ans[idx] = MST - w + alternative;
    }

    for(int i = 0; i < M; i++) cout << ans[i] << "\n";
}