#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int MAXN = 202020;
const int LOGN = 18;

bool erased[MAXN], isdummy[MAXN];
int N, M, sz[MAXN], depth[MAXN], sparse[MAXN][LOGN+1], par[MAXN];
vector<int> g[MAXN], dep[MAXN];
vector<vector<int>> deps[MAXN];
unordered_map<int, int> group[MAXN];

void build_lca(int u, int p)
{
    for(int i = 1; i <= LOGN; i++) {
        sparse[u][i] = sparse[sparse[u][i-1]][i-1];
    }
    for(auto v : g[u]) {
        if(v == p) continue;
        sparse[v][0] = u;
        depth[v] = depth[u] + 1;
        build_lca(v, u);
    }
}

int lca(int u, int v)
{
    if(depth[u] < depth[v]) swap(u, v);
    int diff = depth[u] - depth[v];
    for(int i = 0; i <= LOGN; i++) {
        if(diff & (1<<i)) {
            u = sparse[u][i];
        }
    }

    if(u == v) return u;

    for(int i = LOGN; i >= 0; i--) {
        if(sparse[u][i] != sparse[v][i]) {
            u = sparse[u][i];
            v = sparse[v][i];
        }
    }
    return sparse[u][0];
}

int dist(int u, int v)
{
    int w = lca(u, v);
    return depth[u] + depth[v] - 2 * depth[w];
}

pair<int, int> get_center(pair<int, int> vr1, pair<int, int> vr2)
{
    auto [u, r1] = vr1;
    auto [v, r2] = vr2;
    int w = lca(u, v);

    int d = depth[u] + depth[v] - 2 * depth[w];

    if(r1 - d >= r2) return vr2;
    if(r2 - d >= r1) return vr1;

    int r = (r1 + r2 - d) / 2;

    int target = (d + r1 - r2) / 2;

    if(depth[u] - depth[w] < target) {
        swap(u, v);
        target = d - target;
    }

    for(int i = 0; i <= LOGN; i++) {
        if(target & (1<<i)) {
            u = sparse[u][i];
        }
    }

    return {u, r};
}

void get_sz(int u, int p)
{
    sz[u] = 1;
    for(auto v : g[u]) {
        if(v == p || erased[v]) continue;
        get_sz(v, u);
        sz[u] += sz[v];
    }
}

int get_cent(int n, int u, int p)
{
    for(auto v : g[u]) {
        if(v == p || erased[v]) continue;
        if(sz[v] > n/2) return get_cent(n, v, u);
    }
    return u;
}

int get_depth(int u, int p)
{
    int ret = 1;
    for(auto v : g[u]) {
        if(v == p || erased[v]) continue;
        ret = max(ret, get_depth(v, u) + 1);
    }
    return ret;
}

void dfs(int u, int p, int d, vector<int>& dep, int idx, unordered_map<int, int>& group)
{
    group[u] = idx;
    if(!isdummy[u])
        dep[d]++;
    for(auto v : g[u]) {
        if(v == p || erased[v]) continue;
        dfs(v, u, d + 1, dep, idx, group);
    }
}

void DnC(int u, int p)
{
    get_sz(u, -1);
    int c = get_cent(sz[u], u, -1);
    par[c] = p;
    erased[c] = true;
    
    dep[c].resize(get_depth(c, -1)+1);
    deps[c].resize(g[c].size());

    if(!isdummy[c])
        dep[c][0]++;
    group[c][c] = -1;

    for(int i = 0; i < g[c].size(); i++) {
        int v = g[c][i];
        if(erased[v]) continue;

        deps[c][i].resize(get_depth(v, c)+1);
        dfs(v, c, 1, deps[c][i], i, group[c]);

        for(int j = 1; j < deps[c][i].size(); j++) {
            dep[c][j] += deps[c][i][j];
            deps[c][i][j] += deps[c][i][j-1];
        }
    }

    for(int i = 1; i < dep[c].size(); i++) {
        dep[c][i] += dep[c][i-1];
    }

    for(auto v : g[c]) {
        if(erased[v]) continue;
        DnC(v, c);
    }
}

int query(pair<int, int> vr)
{
    auto [v, r] = vr;
    int ret = 0;
    int u = v;
    while(u != -1) {
        int d = min(r - dist(v, u), (int)dep[u].size()-1);
        if(0 <= d) {
            ret += dep[u][d];
            if(u != v) {
                int g = group[u][v];
                d = min(d, (int)deps[u][g].size()-1);
                ret -= deps[u][g][d];
            }
        }
        u = par[u];
    }
    return ret;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N;
    for(int i = 1; i < N; i++) {
        int u, v;
        cin >> u >> v;
        int w = N + i;
        isdummy[w] = true;
        g[u].push_back(w);
        g[w].push_back(u);
        g[v].push_back(w);
        g[w].push_back(v);
    }

    build_lca(1, -1);
    DnC(1, -1);

    cin >> M;
    while(M--) {
        int k;
        cin >> k;

        vector<pair<int, int>> preffix(k), suffix(k);
        for(int i = 0; i < k; i++) {
            int v, r;
            cin >> v >> r;
            r *= 2;
            preffix[i] = {v, r};
            suffix[i] = {v, r};
        }

        if(k == 1) {
            cout << query(preffix[0]) << "\n";
            continue;
        }
        
        for(int i = 1; i < k; i++) {
            preffix[i] = get_center(preffix[i-1], preffix[i]);
        }
        for(int i = k-2; i >= 0; i--) {
            suffix[i] = get_center(suffix[i+1], suffix[i]);
        }

        ll ans = query(suffix[1]) + query(preffix[k-2]);
        for(int i = 1; i < k-1; i++) {
            auto vr = get_center(preffix[i-1], suffix[i+1]);
            ans += query(vr);
        }
        ans -= (ll)(k-1) * query(suffix[0]);
        cout << ans << "\n";
    }
}