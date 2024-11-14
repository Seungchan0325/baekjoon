#include <bits/stdc++.h>

using namespace std;

const int MAXN = 250005;

int N, M, sz[MAXN], dep[MAXN], in[MAXN], out[MAXN], par[MAXN], top[MAXN], pv;
int tree[4*MAXN], lazy[4*MAXN];
vector<int> inp[MAXN], graph[MAXN];

void dfs1(int u = 1, int p = -1)
{
    for(auto v : inp[u]) {
        if(v == p) continue;
        graph[u].push_back(v);
        dfs1(v, u);
    }
}

void dfs2(int u = 1, int p = -1)
{
    sz[u] = 1;
    for(auto& v : graph[u]) {
        dep[v] = dep[u] + 1;
        par[v] = u;
        dfs2(v, u);
        sz[u] += sz[v];
        if(sz[v] > sz[graph[u][0]]) swap(graph[u][0], v);
    }
}

void dfs3(int u = 1, int p = -1)
{
    in[u] = ++pv;
    for(auto v : graph[u]) {
        top[v] = v == graph[u][0] ? top[u] : v;
        dfs3(v, u);
    }
    out[u] = pv;
}

void propagate(int s, int e, int idx)
{
    if(lazy[idx] != -1) {
        tree[idx] = lazy[idx] * (e - s + 1);
        if(s != e) {
            lazy[2*idx] = lazy[idx];
            lazy[2*idx+1] = lazy[idx];
        }
        lazy[idx] = -1;
    }
}

void upd(int l, int r, int v, int s = 1, int e = N, int idx = 1)
{
    propagate(s, e, idx);
    if(e < l || r < s) return;

    if(l <= s && e <= r) {
        lazy[idx] = v;
        propagate(s, e, idx);
        return;
    }
    int m = (s + e) / 2;
    upd(l, r, v, s, m, 2*idx);
    upd(l, r, v, m+1, e, 2*idx+1);
    tree[idx] = tree[2*idx] + tree[2*idx+1];
}

int qry(int l, int r, int s = 1, int e = N, int idx = 1)
{
    propagate(s, e, idx);
    if(e < l || r < s) return 0;

    if(l <= s && e <= r) return tree[idx];

    int m = (s + e) / 2;
    return qry(l, r, s, m, 2*idx) + qry(l, r, m+1, e, 2*idx+1);
}

void hld_upd(int u, int v, int value)
{
    while(top[u] != top[v]) {
        if(dep[top[u]] < dep[top[v]]) swap(u, v);
        int st = top[u];
        upd(in[st], in[u], value);
        u = par[st];
    }
    if(dep[u] > dep[v]) swap(u, v);
    upd(in[u]+1, in[v], value);
}

int hld_qry(int u, int v)
{
    int ret = 0;
    while(top[u] != top[v]) {
        if(dep[top[u]] < dep[top[v]]) swap(u, v);
        int st = top[u];
        ret += qry(in[st], in[u]);
        u = par[st];
    }
    if(dep[u] > dep[v]) swap(u, v);
    ret += qry(in[u]+1, in[v]);
    return ret;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    memset(lazy, -1, sizeof(lazy));

    cin >> N;
    for(int i = 1; i < N; i++) {
        int u, v;
        cin >> u >> v;
        inp[u].push_back(v);
    }

    top[1] = 1;
    dfs1(); dfs2(); dfs3();
    upd(1, N, 1);
    // upd(1, 1, 0);

    cin >> M;
    M += N-1;

    while(M--) {
        char op;
        cin >> op;

        if(op == 'A') {
            int a, b;
            cin >> a >> b;
            hld_upd(a, b, 0);
        } else {
            int a;
            cin >> a;
            int result = hld_qry(1, a);
            cout << result << "\n";
        }
    }
}