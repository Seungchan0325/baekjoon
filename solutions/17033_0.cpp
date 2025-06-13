#include <bits/stdc++.h>

using namespace std;

const int MAXN = 101010;

struct SegTree {
    int n = MAXN;
    int tree[MAXN<<1] = {};

    void update(int x, int v)
    {
        x++;
        x += n;
        tree[x] = v;
        while(x >>= 1) tree[x] = tree[x<<1] ^ tree[x<<1|1];
    }

    int query(int l, int r)
    {
        int ans = 0;
        l++; r++;
        l += n;
        r += n;
        for(; l <= r; l>>=1, r>>=1) {
            if(l&1) ans ^= tree[l++];
            if(~r&1) ans ^= tree[r--];
        }
        return ans;
    }
};

int n, m, e[MAXN], dfsn, sz[MAXN], in[MAXN], out[MAXN], dep[MAXN], top[MAXN], par[MAXN];
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

int query(int u, int v)
{
    int ans = 0;
    while(top[u] != top[v]) {
        if(dep[top[u]] < dep[top[v]]) swap(u, v);
        ans ^= seg.query(in[top[u]], in[u]);
        u = par[top[u]];
    }
    if(dep[u] > dep[v]) swap(u, v);
    ans ^= seg.query(in[u], in[v]);
    return ans;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> n >> m;
    for(int i = 1; i <= n; i++) cin >> e[i];
    for(int i = 1; i < n; i++) {
        int u, v; cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    dfs(1, -1);
    dfs2(1);
    dfs3(top[1] = 1);

    for(int i = 1; i <= n; i++) {
        seg.update(in[i], e[i]);
    }

    while(m--) {
        int op;
        cin >> op;
        if(op == 1) {
            int i, v;
            cin >> i >> v;
            seg.update(in[i], v);
        } else if(op == 2) {
            int i, j;
            cin >> i >> j;
            int ans = query(i, j);
            cout << ans << "\n";
        } else {
            assert(0);
        }
    }
}