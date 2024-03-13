#include <bits/stdc++.h>

using namespace std;

using llint = long long int;

const int INF = 1e9 + 5;
const int MAXN = 100005;

// Segment Tree
int tree[4*MAXN], lazy[4*MAXN];
// HLD
bool visited[MAXN];
int pv, dep[MAXN], par[MAXN], sz[MAXN], top[MAXN], in[MAXN];
vector<int> graph[MAXN];
//
int N, Q;
vector<int> inp[MAXN];

void propagate(int s, int e, int idx)
{
    if(lazy[idx]) {
        tree[idx] += lazy[idx];
        if(s != e) {
            lazy[2*idx] += lazy[idx];
            lazy[2*idx+1] += lazy[idx];
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
    tree[idx] = max(tree[2*idx], tree[2*idx+1]);
}

int query(int l, int r, int s = 1, int e = N, int idx = 1)
{
    propagate(s, e, idx);
    if(e < l || r < s) return 0;
    if(l <= s && e <= r) return tree[idx];
    int m = (s + e) >> 1;
    return max(query(l, r, s, m, 2*idx), query(l, r, m+1, e, 2*idx+1));
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
    int ret = 0;
    while(top[u] ^ top[v]) {
        if(dep[top[u]] < dep[top[v]]) swap(u, v);
        ret = max(query(in[top[u]], in[u]), ret);
        u = par[top[u]];
    }
    if(dep[u] > dep[v]) swap(u, v);
    ret = max(query(in[u]+1, in[v]), ret);
    return ret;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N >> Q;
    for(int i = 1; i < N; i++) {
        int u, v;
        cin >> u >> v;
        inp[u].push_back(v);
        inp[v].push_back(u);
    }
    dfs(1);
    dfs1(1);
    top[1] = 1; dfs2(1);
    while(Q--) {
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        hld_update(a, b, 1);
        int result = hld_query(c, d);
        hld_update(a, b, -1);
        if(result) cout << "NO\n";
        else cout << "YES\n";
    }
}