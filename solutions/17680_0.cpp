// #pragma GCC optimize("O3")
// #pragma GCC optimize("Ofast")
// #pragma GCC optimization("unroll-loops")
// #pragma GCC target("avx,avx2,fma")
#include <bits/stdc++.h>

using namespace std;

const int MAXN = 101010;
const int INF = 1e9;

struct node {
    int mn, mx;
};

struct Fenwick {
    int N;
    vector<int> tree;
    void init(int _n)
    {
        N = _n;
        tree.resize(N+1);
    }

    void upd(int x, int v)
    {
        while(x <= N) {
            tree[x] += v;
            x += x & -x;
        }
    }

    int qry(int x)
    {
        int ret = 0;
        while(x > 0) {
            ret += tree[x];
            x -= x & -x;
        }
        return ret;
    }
};

int N, C[MAXN], dep[MAXN], par[MAXN], sz[MAXN], top[MAXN], s[MAXN], e[MAXN], pv, lazy[4*MAXN];
vector<pair<int, int>> edges;
vector<int> g[MAXN], t[MAXN];
node tree[4*MAXN];
Fenwick ft;

node merge(node l, node r)
{
    return {min(l.mn, r.mn), max(l.mx, r.mx)};
}

void propagate(int s, int e, int idx)
{
    if(lazy[idx]) {
        tree[idx].mn = tree[idx].mx = lazy[idx];
        if(s != e) {
            lazy[2*idx] = lazy[idx];
            lazy[2*idx+1] = lazy[idx];
        }
        lazy[idx] = 0;
    }
}

void update(int l, int r, int v, int s = 0, int e = N, int idx = 1)
{
    propagate(s, e, idx);
    if(e < l || r < s) return;
    if(l <= s && e <= r) {
        lazy[idx] = v;
        propagate(s, e, idx);
        return;
    }
    int m = (s + e) / 2;
    update(l, r, v, s, m, 2*idx);
    update(l, r, v, m+1, e, 2*idx+1);
    tree[idx] = merge(tree[2*idx], tree[2*idx+1]);
}

node queryx(int l, int r, int s = 0, int e = N, int idx = 1)
{
    propagate(s, e, idx);
    if(l <= s && e <= r) return tree[idx];
    int m = (s + e) / 2;
    if(r <= m) return queryx(l, r, s, m, 2*idx);
    if(m+1 <= l) return queryx(l, r, m+1, e, 2*idx+1);
    return merge(queryx(l, r, s, m, 2*idx), queryx(l, r, m+1, e, 2*idx+1));
}

// pair<int, int> query(int r, node& n, int s = 0, int e = N, int idx = 1)
// {
//     propagate(s, e, idx);
//     if(e <= r && tree[idx].mn == tree[idx].mx) return {-1, -1};
//     if(e <= r && )
//     if(s == e) return {s, tree[idx].mx};

//     int m = (s + e) / 2;
//     if(r <= m) return query(r, s, m, 2*idx);
//     auto x = query(r, m+1, e, 2*idx+1);
//     if(x.first != -1) return x;
//     return query(r, s, m, 2*idx);
// }

int query(int r, node& n, int s = 0, int e = N, int idx = 1)
{
    propagate(s, e, idx);
    if(r < s) return 0;
    if(auto t = merge(n, tree[idx]); e <= r && t.mn == t.mx) {
        n = merge(n, tree[idx]);
        return 0;
    }
    if(s == e) return s;
    int m = (s + e) / 2;
    auto x = query(r, n, m+1, e, 2*idx+1);
    if(x != 0) return x;
    return query(r, n, s, m, 2*idx);
}

// pair<int, int> query(int r)
// {
//     int lo = 0, hi = r;
//     while(lo + 1 < hi) {
//         int mid = (lo + hi) / 2;
//         if(auto q = queryx(mid, r); q.mn == q.mx) hi = mid;
//         else lo = mid;
//     }
//     int x = queryx(hi, hi).mn;
//     return {lo, x};
// }

void dfs0(int u, int p)
{
    sz[u] = 1;
    for(auto& v : g[u]) {
        if(v == p) continue;
        t[u].push_back(v);
        dfs0(v, u);
    }
}

void dfs1(int u)
{
    sz[u] = 1;
    for(auto& v : t[u]) {
        dep[v] = dep[u] + 1; par[v] = u;
        dfs1(v); sz[u] += sz[v];
        if(sz[v] > sz[t[u][0]]) swap(v, t[u][0]);
    }
}

void dfs2(int u)
{
    s[u] = ++pv;
    for(auto v : t[u]) {
        top[v] = v == t[u][0] ? top[u] : v;
        dfs2(v);
    }
    e[u] = pv;
}

void hld_update(int u, int v)
{
    do {
        int st = top[u];
        update(s[st], s[u], v);
        u = par[st];
    } while(u);
}

vector<tuple<int, int, int>> hld_query(int u)
{
    int i, j, x;
    vector<tuple<int, int, int>> v;
    do {
        int st = top[u];
        i = j = s[u];
        while(i >= s[st]) {
            node nd = {INF, -INF};
            j = query(i, nd);
            j = max(j, s[st]-1);
            v.emplace_back(queryx(i, i).mn, i, i - j);
            i = j;
        }
        u = par[st];
    } while(u);
    return v;
}

int main()
{
    // ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> N;
    for(int i = 1; i <= N; i++) cin >> C[i];
    for(int i = 0; i < N-1; i++) {
        int u, v;
        cin >> u >> v;
        edges.emplace_back(u, v);
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dfs0(1, -1);
    dfs1(1);
    dfs2(top[1] = 1);
    update(0, 0, -1);
    ft.init(N);
    hld_update(1, C[1]);
    for(int i = 0; i < N-1; i++) {
        auto [u, v] = edges[i];
        auto a = hld_query(u);
        sort(a.begin(), a.end());
        long long ans = 0;
        for(auto [x, idx, c] : a) {
            ans += c * (ft.qry(ft.N) - ft.qry(idx));
            ft.upd(idx, c);
        }
        hld_update(v, C[v]);
        for(auto [x, idx, c] : a) {
            ft.upd(idx, -c);
        }
        cout << ans << "\n";
    }
}