#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100005;

int N, M, sz[MAXN], dep[MAXN], par[MAXN], parw[MAXN], top[MAXN], in[MAXN], out[MAXN], tree[2*MAXN];
vector<pair<int, int>> inp[MAXN];
vector<int> g[MAXN];
vector<tuple<int, int, int>> edges;

bool visited[MAXN];

void dfs(int u, int p)
{
    visited[u] = true;
    for(auto [v, w] : inp[u]) {
        if(v == p || visited[v]) continue;
        visited[v] = true;
        g[u].push_back(v);
        parw[v] = w;
        dfs(v, u);
    }
}

void dfs1(int u)
{
    // assert(sz[u] == 0);
    assert(visited[u] == false);
    sz[u] = 1;
    visited[u] = true;
    for(auto& v : g[u]) {
        // if(visited[v]) continue;
        // visited[v] = true;
        dep[v] = dep[u] + 1; par[v] = u;
        dfs1(v); sz[u] += sz[v];
        if(sz[v] > sz[g[u][0]]) swap(v, g[u][0]);
    }
}

int pv = 0;
void dfs2(int u)
{
    // assert(in[u] == 0);
    assert(visited[u] == false);
    in[u] = ++pv;
    visited[u] = true;
    for(auto v : g[u]) {
        // if(visited[v]) continue;
        // visited[v] = true;
        top[v] = (v == g[u][0]) ? top[u] : v;
        dfs2(v);
    }
    out[u] = pv;
}

void update(int pos, int value)
{
    pos--;
    for(tree[pos += N] = value; pos > 1; pos >>= 1)
        tree[pos >> 1] = max(tree[pos], tree[pos^1]);
}

int query(int l, int r)
{
    int ret = 0; l--;
    for(l += N, r += N; l < r; l >>= 1, r >>= 1) {
        if(l&1) ret = max(tree[l++], ret);
        if(r&1) ret = max(tree[--r], ret);
    }
    return ret;
}

int hld_query(int u, int v)
{
    int ret = 0;
    int iter = 0;
    while(top[u] ^ top[v]) {
        if(dep[top[u]] < dep[top[v]]) swap(u, v);
        int st = top[u];
        ret = max(query(in[st], in[u]), ret);
        u = par[st];
        iter++;
        // assert(iter < 30);
    }
    if(dep[u] > dep[v]) swap(u, v);
    ret = max(query(in[u]+1, in[v]), ret);
    return ret;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N;
    for(int i = 1; i < N; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        edges.emplace_back(u, v, w);
        inp[u].emplace_back(v, w);
        inp[v].emplace_back(u, w);
    }

    dfs(1, -1);
    memset(visited, 0, sizeof(visited));
    dfs1(1);
    memset(visited, 0, sizeof(visited));
    dfs2(1);

    for(int i = 2; i <= N; i++) {
        update(in[i], parw[i]);
    }

    cin >> M;
    for(int i = 0; i < M; i++) {
        int t;
        cin >> t;
        if(t == 1) {
            int i, c;
            cin >> i >> c;
            auto [u, v, w] = edges[i-1];
            if(par[v] == u) swap(u, v);
            update(in[u], c);
        } else {
            int u, v;
            cin >> u >> v;
            int result = hld_query(u, v);
            cout << result << "\n";
        }
    }
}