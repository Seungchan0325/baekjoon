#include <bits/stdc++.h>

using namespace std;

const int MAXN = 101010;

struct SegTree {
    int n = MAXN;
    int tree[MAXN<<2] = {};
    int lazy[MAXN<<2] = {};

    void propagate(int s, int e, int idx)
    {
        if(lazy[idx]) {
            tree[idx] += (e - s + 1) * lazy[idx];
            if(s != e) {
                lazy[2*idx] += lazy[idx];
                lazy[2*idx+1] += lazy[idx];
            }
            lazy[idx] = 0;
        }
    }

    void update(int l, int r, int v, int s, int e, int idx)
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
        tree[idx] = tree[2*idx] + tree[2*idx+1];
    }

    int query(int l, int r, int s, int e, int idx)
    {
        propagate(s, e, idx);
        if(e < l || r < s) return 0;
        if(l <= s && e <= r) return tree[idx];
        int m = (s + e) / 2;
        return query(l, r, s, m, 2*idx) + query(l, r, m+1, e, 2*idx+1);
    }

    void update(int l, int r, int v) { return update(l, r, v, 1, n, 1); }
    int query(int l, int r) { return query(l, r, 1, n, 1); }
};

int n, m, dfsn, sz[MAXN], in[MAXN], out[MAXN], dep[MAXN], top[MAXN], par[MAXN];
SegTree seg;
vector<int> g[MAXN], t[MAXN];

void dfs(int u, int p)
{
    for(auto v : g[u]) {
        if(v == p) continue;
        t[u].push_back(v);
        dfs(v, u);
    }
}

void dfs2(int u)
{
    sz[u] = 1;
    for(auto& v : t[u]) {
        dep[v] = dep[u] + 1;
        par[v] = u;
        dfs2(v);
        sz[u] += sz[v];
        if(sz[v] > sz[t[u][0]]) swap(v, t[u][0]);
    }
}

void dfs3(int u)
{
    in[u] = ++dfsn;
    for(auto v : t[u]) {
        top[v] = v == t[u][0] ? top[u] : v;
        dfs3(v);
    }
    out[u] = dfsn;
}

void update(int u, int v, int value)
{
    while(top[u] != top[v]) {
        if(dep[top[u]] < dep[top[v]]) swap(u, v);
        seg.update(in[top[u]], in[u], value);
        u = par[top[u]];
    }
    if(dep[u] > dep[v]) swap(u, v);
    seg.update(in[u]+1, in[v], value);
}

int query(int u, int v)
{
    int ans = 0;
    while(top[u] != top[v]) {
        if(dep[top[u]] < dep[top[v]]) swap(u, v);
        ans += seg.query(in[top[u]], in[u]);
        u = par[top[u]];
    }
    if(dep[u] > dep[v]) swap(u, v);
    ans += seg.query(in[u]+1, in[v]);
    return ans;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> n >> m;
    for(int i = 1; i < n; i++) {
        int u, v; cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    dfs(1, -1);
    dfs2(1);
    dfs3(top[1] = 1);

    while(m--) {
        char op;
        int u, v;
        cin >> op >> u >> v;
        if(op == 'P') {
            update(u, v, 1);
        } else {
            int ans = query(u, v);
            cout << ans << "\n";
        }
    }
}