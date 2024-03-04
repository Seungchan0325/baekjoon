#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const ll MAXV = 200005;
const ll INF = 1e18;

ll V, E, ans[MAXV];
vector<ll> inp[MAXV];
vector<tuple<ll, ll, ll, ll>> edges, mst, non_mst;

ll root[MAXV];

ll find(ll x)
{
    if(root[x] == x) return x;
    return root[x] = find(root[x]);
}

bool Union(ll x, ll y)
{
    x = find(x);
    y = find(y);
    if(x == y) return false;
    root[y] = x;
    return true;
}

struct T {
    ll mx1, mx2;
    T() : mx1(-1), mx2(-1) {}
    T(ll v) : mx1(v), mx2(-1) {}
    T(ll _mx1, ll _mx2) : mx1(_mx1), mx2(_mx2) {}
};

T merge(T a, T b)
{
    if(a.mx1 < b.mx1) swap(a, b);
    if(a.mx1 == b.mx1) return {a.mx1, max(a.mx2, b.mx2)};
    return {a.mx1, {max(a.mx2, b.mx1)}};
}

T tree[4*MAXV];

void update(ll pos, T value)
{
    for(tree[pos += V] = value; pos > 1; pos >>= 1) {
        tree[pos>>1] = merge(tree[pos], tree[pos^1]);
    }
}

T query(ll l, ll r)
{
    T ret = {};
    for(l+=V, r+=V; l <= r; l>>=1, r>>=1) {
        if(l&1) ret = merge(tree[l++], ret); 
        if(~r&1) ret = merge(tree[r--], ret);
    }
    return ret;
}

bool visited[MAXV];
ll pv, par[MAXV], top[MAXV], sz[MAXV], dep[MAXV], in[MAXV];
vector<ll> g[MAXV];

void dfs(ll u)
{
    visited[u] = true;
    for(auto v : inp[u]) {
        if(visited[v]) continue;
        dfs(v);
        g[u].push_back(v);
    }
}

void dfs1(ll u)
{
    sz[u] = 1;
    for(auto& v : g[u]) {
        dep[v] = dep[u] + 1; par[v] = u;
        dfs1(v); sz[u] += sz[v];
        if(sz[v] > sz[g[u][0]]) swap(v, g[u][0]);
    }
}

void dfs2(ll u)
{
    in[u] = ++pv;
    for(auto v : g[u]) {
        top[v] = (v == g[u][0]) ? top[u] : v;
        dfs2(v);
    }
}

T hld_query(ll u, ll v)
{
    T ret = {};
    while(top[u] ^ top[v]) {
        if(dep[top[u]] < dep[top[v]]) swap(u, v);
        ret = merge(query(in[top[u]], in[u]), ret);
        u = par[top[u]];
    }
    if(dep[u] > dep[v]) swap(u, v);
    ret = merge(query(in[u]+1, in[v]), ret);
    return ret;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> V >> E;
    edges.resize(E);
    int i = 0;
    for(auto& [w, u, v, idx] : edges) {
        cin >> u >> v >> w;
        idx = i++;
    }

    ll MST = 0;
    iota(root, root + MAXV, 0);
    sort(edges.begin(), edges.end());
    for(auto [w, u, v, idx] : edges) {
        if(Union(u, v)) {
            MST += w;
            inp[u].push_back(v);
            inp[v].push_back(u);
            mst.emplace_back(u, v, w, idx);
        } else {
            non_mst.emplace_back(u, v, w, idx);
        }
    }

    dfs(get<0>(mst[0]));
    dfs1(get<0>(mst[0]));
    top[get<0>(mst[0])] = get<0>(mst[0]); dfs2(get<0>(mst[0]));

    for(auto [u, v, w, idx] : mst) {
        if(dep[u] < dep[v]) swap(u, v);
        update(in[u], {w});
        ans[idx] = MST;
    }

    for(auto [u, v, w, idx] : non_mst) {
        T alt = hld_query(u, v);
        ans[idx] = MST + w - alt.mx1;
    }

    for(int i = 0; i < E; i++) {
        cout << ans[i] << "\n";
    }
}