#include <bits/stdc++.h>

using namespace std;

using ullint = unsigned long long;

const int MAXN = 500005;
const ullint MOD = 1ULL<<32;

bool visited[MAXN];
int N, Q;
int sz[MAXN], dep[MAXN], par[MAXN], top[MAXN], in[MAXN], out[MAXN];
vector<int> g[MAXN], inp[MAXN];
ullint tree[4*MAXN], lazy[4*MAXN][2];

ullint merge(ullint a, ullint b)
{
    return (a + b) % MOD;
}

void propagate(int s, int e, int idx)
{
    ullint& a1 = lazy[idx][0];
    ullint& b1 = lazy[idx][1];
    tree[idx] = ((a1 * tree[idx]) % MOD + ((e - s + 1) * b1) % MOD) % MOD;
    if(s != e) {
        for(auto i : {2*idx, 2*idx+1}) {
            ullint& a0 = lazy[i][0];
            ullint& b0 = lazy[i][1];
            a0 = (a0 * a1) % MOD;
            b0 = ((a1 * b0) % MOD + b1) % MOD;
        }
    }
    a1 = 1;
    b1 = 0;
}

void update(int l, int r, ullint mul, ullint sum, int s = 1, int e = N, int idx = 1)
{
    propagate(s, e, idx);
    if(e < l || r < s) return;

    if(l <= s && e <= r) {
        assert(lazy[idx][0] == 1 && lazy[idx][1] == 0);
        lazy[idx][0] = mul;
        lazy[idx][1] = sum;
        propagate(s, e, idx);
        return;
    }

    int m = (s + e) >> 1;
    update(l, r, mul, sum, s, m, 2*idx);
    update(l, r, mul, sum, m+1, e, 2*idx+1);
    tree[idx] = merge(tree[2*idx], tree[2*idx+1]);
}

ullint query(int l, int r, int s = 1, int e = N, int idx = 1)
{
    propagate(s, e, idx);
    if(e < l || r < s) return 0;
    if(l <= s && e <= r) return tree[idx];
    int m = (s + e) >> 1;
    return merge(query(l, r, s, m, 2*idx), query(l, r, m+1, e, 2*idx+1));
}

void dfs(int u)
{
    visited[u] = true;
    for(auto v : inp[u]) {
        if(visited[v]) continue;
        dfs(v);
        g[u].push_back(v);
    }
}

void dfs1(int u)
{
    sz[u] = 1;
    for(auto& v : g[u]) {
        dep[v] = dep[u] + 1; par[v] = u;
        dfs1(v); sz[u] += sz[v];
        if(sz[v] > sz[g[u][0]]) swap(v, g[u][0]);
    }
}

int pv = 0;
void dfs2(int u)
{
    in[u] = ++pv;
    for(auto v : g[u]) {
        top[v] = (v == g[u][0]) ? top[u] : v;
        dfs2(v);
    }
    out[u] = pv;
}

void hld_update(int u, int v, ullint mul, ullint sum)
{
    while(top[u] ^ top[v]) {
        if(dep[top[u]] < dep[top[v]]) swap(u, v);
        update(in[top[u]], in[u], mul, sum);
        u = par[top[u]];
    }
    if(dep[u] > dep[v]) swap(u, v);
    update(in[u], in[v], mul, sum);
}

ullint hld_query(int u, int v)
{
    ullint ret = 0;
    while(top[u] ^ top[v]) {
        if(dep[top[u]] < dep[top[v]]) swap(u, v);
        ret = merge(query(in[top[u]], in[u]), ret);
        u = par[top[u]];
    }
    if(dep[u] > dep[v]) swap(u, v);
    ret = merge(query(in[u], in[v]), ret);
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
        int t;
        cin >> t;
        if(t == 1) {
            int X, V;
            cin >> X >> V;
            update(in[X], out[X], 1, V);
        } else if(t == 2) {
            int X, Y, V;
            cin >> X >> Y >> V;
            hld_update(X, Y, 1, V);
        } else if(t == 3) {
            int X, V;
            cin >> X >> V;
            update(in[X], out[X], V, 0);
        } else if(t == 4) {
            int X, Y, V;
            cin >> X >> Y >> V;
            hld_update(X, Y, V, 0);
        } else if(t == 5) {
            int X;
            cin >> X;
            auto result = query(in[X], out[X]);
            cout << result << "\n";
        } else if(t == 6) {
            int X, Y;
            cin >> X >> Y;
            auto result = hld_query(X, Y);
            cout << result << "\n";
        }
    }
}