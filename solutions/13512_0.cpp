#include <bits/stdc++.h>

using namespace std;

const int INF = 987654321;
const int MAXN = 100005;

struct T {
    pair<int, int> mn;
    T() : mn({INF, -1}) {}
    T(pair<int, int> v) : mn(v) {}
} tree[2*MAXN];

T merge(T a, T b)
{
    return {min(a.mn, b.mn)};
}

bool c[MAXN];
int N, M, dep[MAXN], sz[MAXN], par[MAXN], top[MAXN], in[MAXN], pv;
vector<int> g[MAXN], inp[MAXN];

void update(int pos, T v)
{
    for(tree[pos += N] = v; pos > 1; pos >>= 1) {
        tree[pos>>1] = merge(tree[pos], tree[pos^1]);
    }
}

T query(int l, int r)
{
    T ret;
    for(l+=N, r+=N; l <= r; l>>=1, r>>=1) {
        if(l&1) ret = merge(tree[l++], ret);
        if(~r&1) ret = merge(tree[r--], ret);
    }
    return ret;
}

void dfs(int u, int p)
{
    for(auto v : inp[u]) {
        if(v == p) continue;
        g[u].push_back(v);
        dfs(v, u);
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

void dfs2(int u)
{
    in[u] = ++pv;
    for(auto v : g[u]) {
        top[v] = v == g[u][0] ? top[u] : v;
        dfs2(v);
    }
}

int hld_query(int u)
{
    T ret;
    while(u) {
        ret = merge(query(in[top[u]], in[u]), ret);
        u = par[top[u]];
    }
    return ret.mn.second;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N;
    for(int i = 1; i < N; i++) {
        int u, v;
        cin >> u >> v;
        inp[u].push_back(v);
        inp[v].push_back(u);
    }

    dfs(1, -1);
    dfs1(1);
    dfs2(top[1] = 1);

    cin >> M;
    while(M--) {
        int op;
        cin >> op;

        if(op == 1) {
            int i;
            cin >> i;
            if(c[i]) {
                update(in[i], {});
                c[i] = false;
            } else {
                update(in[i], {{dep[i], i}});
                c[i] = true;
            }
        } else {
            int v;
            cin >> v;
            int result = hld_query(v);
            cout << result << "\n";
        }
    }
}