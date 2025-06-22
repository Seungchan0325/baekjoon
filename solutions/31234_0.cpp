#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int MAXN = 101010;

struct SegTree {
    int n = MAXN;
    ll tree[MAXN<<2] = {};
    ll lazy[MAXN<<2] = {};

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

    void update(int l, int r, ll v, int s, int e, int idx)
    {
        propagate(s, e, idx);
        if(e < l || r < s) return;
        if(l <= s && e <= r) {
            lazy[idx] += v;
            propagate(s, e, idx);
            return;
        }
        int m = (s + e) / 2;
        update(l, r, v, s, m, 2*idx);
        update(l, r, v, m+1, e, 2*idx+1);
        tree[idx] = max(tree[2*idx], tree[2*idx+1]);
    }

    ll query(int l, int r, int s, int e, int idx)
    {
        propagate(s, e, idx);
        if(e < l || r < s) return 0;
        if(l <= s && e <= r) return tree[idx];
        int m = (s + e) / 2;
        return max(query(l, r, s, m, 2*idx), query(l, r, m+1, e, 2*idx+1));
    }

    void update(int l, int r, ll v) { return update(l, r, v, 1, n, 1); }
    ll query(int l, int r) { return query(l, r, 1, n, 1); }
};

int N, M, A[MAXN], par[MAXN], in[MAXN], out[MAXN], sz[MAXN], top[MAXN], dep[MAXN], pv;
vector<int> inp[MAXN], g[MAXN];
SegTree seg;


void dfs1(int u, int p)
{
    for(auto v : inp[u]) {
        if(v == p) continue;
        g[u].push_back(v);
        dfs1(v, u);
    }
}

void dfs2(int u)
{
    sz[u] = 1;
    for(auto& v : g[u]) {
        dep[v] = dep[u] + 1;
        par[v] = u;
        dfs2(v);
        sz[u] += sz[v];
        if(sz[v] > sz[g[u][0]]) swap(v, g[u][0]);
    }
}

void dfs3(int u)
{
    in[u] = ++pv;
    for(auto v : g[u]) {
        top[v] = v == g[u][0] ? top[u] : v;
        dfs3(v);
    }
    out[u] = pv;
}

void hld_update(int u, int v, int w)
{
    while(top[u] != top[v]) {
        if(dep[top[u]] < dep[top[v]]) swap(u, v);
        seg.update(in[top[u]], in[u], w);
        u = par[top[u]];
    }
    if(dep[u] > dep[v]) swap(u, v);
    seg.update(in[u], in[v], w);
}

int main()
{
    cin >> N >> M;
    for(int i = 1; i < N; i++) {
        int u, v; cin >> u >> v;
        inp[u].push_back(v);
        inp[v].push_back(u);
    }
    for(int i = 1; i <= N; i++) cin >> A[i];

    dfs1(1, -1);
    dfs2(1);
    dfs3(top[1] = 1);

    for(int i = 1; i <= N; i++) {
        seg.update(in[i], in[i], -A[i]);
    }

    int ans = M;
    for(int i = 0; i < M; i++) {
        int x, y, w;
        cin >> x >> y >> w;
        hld_update(x, y, w);
        if(seg.query(1, N) > 0) {
            ans = min(ans, i);
        }
    }
    cout << ans;
}