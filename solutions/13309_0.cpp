#include <bits/stdc++.h>

using namespace std;

const int MAXN = 200005;

int pv, N, Q, root[MAXN], par[MAXN], dep[MAXN], in[MAXN], out[MAXN], sz[MAXN], top[MAXN], tree[2*MAXN];
vector<int> g[MAXN];

void dfs(int u)
{
    sz[u] = 1;
    for(auto& v : g[u]) {
        dep[v] = dep[u] + 1;
        dfs(v); sz[u] += sz[v];
        if(sz[v] > sz[g[u][0]]) swap(g[u][0], v);
    }
}

void dfs1(int u)
{
    in[u] = ++pv;
    for(auto v : g[u]) {
        top[v] = (v == g[u][0] ? top[u] : v);
        dfs1(v);
    }
}

void update(int pos, int delta)
{
    pos--;
    for(tree[pos+=N] += delta; pos > 1; pos>>=1) {
        tree[pos>>1] = tree[pos] + tree[pos^1];
    }
}

int query(int l, int r)
{
    l--; r--;
    int ret = 0;
    for(l+=N, r+=N; l <= r; l>>=1, r>>=1) {
        if(l&1) ret += tree[l++];
        if(~r&1) ret += tree[r--];
    }
    return ret;
}

int hld_query(int u, int v)
{
    int ret = 0;
    while(top[u] ^ top[v]) {
        if(dep[top[u]] < dep[top[v]]) swap(u, v);
        ret += query(in[top[u]], in[u]);
        u = par[top[u]];
    }
    if(dep[u] > dep[v]) swap(u, v);
    ret += query(in[u]+1, in[v]);
    return ret;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N >> Q;
    for(int i = 2; i <= N; i++) {
        cin >> par[i];
        g[par[i]].push_back(i);
    }

    dfs(1);
    dfs1(top[1] = 1);

    while(Q--) {
        int t, u, v;
        cin >> u >> v >> t;

        int removed = hld_query(u, v);
        if(removed == 0) {
            cout << "YES\n";
            if(t == 1) {
                update(in[u], 1);
            }
        } else {
            cout << "NO\n";
            if(t == 1) {
                update(in[v], 1);
            }
        }
    }
}