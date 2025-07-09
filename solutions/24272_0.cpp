#include <bits/stdc++.h>

using namespace std;

const int MAXN = 101010;

struct T {
    int mn;
    int mncnt;
};

map<pair<int, int>, int> dir;
int n, lazy[4*MAXN], in[MAXN], out[MAXN], pv;
vector<int> g[MAXN];
T tree[4*MAXN];

T merge(T a, T b)
{
    if(a.mn == b.mn) return {a.mn, a.mncnt+b.mncnt};
    return (a.mn < b.mn) ? a : b;
}

void init(int s = 1, int e = n+1, int idx = 1)
{
    if(s == e) {
        tree[idx].mn = 0;
        tree[idx].mncnt = 1;
        return;
    }
    int m = (s + e) / 2;
    init(s, m, 2*idx);
    init(m+1, e, 2*idx+1);
    tree[idx] = merge(tree[2*idx], tree[2*idx+1]);
}

void propagate(int s, int e, int idx)
{
    if(lazy[idx]) {
        tree[idx].mn += lazy[idx];
        if(s != e) {
            lazy[2*idx] += lazy[idx];
            lazy[2*idx+1] += lazy[idx];
        }
        lazy[idx] = 0;
    }
}

void update(int l, int r, int v, int s = 1, int e = n+1, int idx = 1)
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
    tree[idx] = merge(tree[2*idx], tree[2*idx+1]);
}

void dfs(int u, int p)
{
    in[u] = ++pv;
    for(auto v : g[u]) {
        if(v == p) continue;
        dfs(v, u);
    }
    out[u] = pv;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    vector<tuple<int, int, int>> edges;
    for(int i = 1; i < n; i++) {
        int u, v;
        string s;
        cin >> u >> s >> v;
        int d;
        if(s == "<-") d = -1;
        else if(s == "->") d = 1;
        else if(s == "--") d = 0;

        g[u].push_back(v);
        g[v].push_back(u);
        edges.emplace_back(u, v, d);
    }
    dfs(1, -1);
    
    init();
    
    auto upd = [&](int u, int v, int d, int x) {
        if(d < 0) {
            update(1, in[v]-1, x);
            update(out[v]+1, n, x);
        }
        else if(d > 0) {
            update(in[v], out[v], x);
        }
    };

    for(auto [u, v, d] : edges) {
        if(in[u] > in[v]) swap(u, v), d = -d;
        dir[pair(u, v)] = d;
        upd(u, v, d, 1);
    }

    int q; cin >> q;
    while(q--) {
        int u, v;
        string s;
        cin >> u >> s >> v;
        int d;
        if(s == "<-") d = -1;
        else if(s == "->") d = 1;
        else if(s == "--") d = 0;
        if(in[u] > in[v]) swap(u, v), d = -d;
        upd(u, v, dir[pair(u, v)], -1);
        dir[pair(u, v)] = d;
        upd(u, v, dir[pair(u, v)], 1);
        cout << tree[1].mncnt - 1 << "\n";
    }
}