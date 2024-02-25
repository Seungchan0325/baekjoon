#include <bits/stdc++.h>

using namespace std;

const int MAXN = 30005;

bool visited[MAXN];
int N, Q, penguins[MAXN];
vector<tuple<string, int, int>> queries;
int root[MAXN];
int tree[4*MAXN];
int sz[MAXN], dep[MAXN], par[MAXN], top[MAXN], in[MAXN], out[MAXN];
vector<int> g[MAXN], inp[MAXN];

int find(int x)
{
    if(root[x] == x) return x;
    return root[x] = find(root[x]);
}

bool merge(int x, int y)
{
    x = find(x);
    y = find(y);
    if(x == y) return false;
    root[y] = x;
    return true;
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

void update(int pos, int value, int s = 1, int e = N, int idx = 1)
{
    if(e < pos || pos < s) return;
    if(s == e) {
        tree[idx] = value;
        return;
    }
    int m = (s + e) >> 1;
    update(pos, value, s, m, 2*idx);
    update(pos, value, m+1, e, 2*idx+1);
    tree[idx] = tree[2*idx] + tree[2*idx+1];
}

int query(int l, int r, int s = 1, int e = N, int idx = 1)
{
    if(e < l || r < s) return 0;
    if(l <= s && e <= r) return tree[idx];
    int m = (s + e) >> 1;
    return query(l, r, s, m, 2*idx) + query(l, r, m+1, e, 2*idx+1);
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
    ret += query(in[u], in[v]);
    return ret;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N;
    for(int i = 1; i <= N; i++) {
        cin >> penguins[i];
    }

    iota(root, root + N + 1, 0);
    cin >> Q;
    for(int i = 0; i < Q; i++) {
        string command;
        int a, b;
        cin >> command >> a >> b;
        queries.emplace_back(command, a, b);
        if(command == "bridge") {
            if(merge(a, b)) {
                inp[a].push_back(b);
                inp[b].push_back(a);
            }
        }
    }

    for(int i = 1; i <= N; i++) {
        if(visited[i]) continue;
        dfs(i);
        dfs1(i);
        dfs2(i);
    }
    for(int i = 1; i <= N; i++) {
        update(in[i], penguins[i]);
    }
    iota(root, root + N + 1, 0);
    for(auto [command, a, b] : queries) {
        if(command == "bridge") {
            if(merge(a, b)) {
                cout << "yes\n";
            } else {
                cout << "no\n";
            }
        } else if(command == "penguins") {
            update(in[a], b);
        } else if(command == "excursion") {
            if(find(a) == find(b)) {
                int result = hld_query(a, b);
                cout << result << "\n";
            } else {
                cout << "impossible\n";
            }
        }
    }
}