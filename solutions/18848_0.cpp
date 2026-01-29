#include <bits/stdc++.h>

using namespace std;

const int MAXN = 202020;

bool erased[MAXN], chk[MAXN];
int N, K, C[MAXN], sz[MAXN], uf[MAXN], cnt[MAXN], par[MAXN], ans = 1e9;
vector<int> G[MAXN];
vector<int> D[MAXN];

int find(int x)
{
    if(uf[x] == x) return x;
    return uf[x] = find(uf[x]);
}

void mrg(int x, int y)
{
    x = find(x);
    y = find(y);
    uf[y] = x;
}

void get_sz(int u, int p)
{
    sz[u] = 1;
    for(auto v : G[u]) {
        if(v == p || erased[v]) continue;
        get_sz(v, u);
        sz[u] += sz[v];
    }
}

int get_cent(int u, int p, int n)
{
    for(auto v : G[u]) {
        if(v == p || erased[v]) continue;
        if(sz[v] > n/2) return get_cent(v, u, n);
    }
    return u;
}

void init(int u, int p)
{
    uf[u] = u;
    par[u] = p;
    chk[C[u]] = 0;
    cnt[C[u]] = 0;
    for(auto v : G[u]) {
        if(v == p || erased[v]) continue;
        init(v, u);
    }
}

void dfs(int u, int p)
{
    cnt[C[u]]++;
    for(auto v : G[u]) {
        if(v == p || erased[v]) continue;
        dfs(v, u);
    }
}

void solve(int c)
{
    init(c, -1);
    dfs(c, -1);
    queue<int> q;
    int num = 0;
    auto push = [&](int u) {
        int c = C[u];
        if(chk[c]) return 0;
        chk[c] = true;
        num++;
        if(cnt[c] != D[c].size()) return -1;
        for(auto v : D[c]) q.push(v);
        return 0;
    };
    if(push(c) < 0) return;
    while(!q.empty()) {
        auto u = q.front(); q.pop();
        if(par[u] < 1) continue;
        if(push(find(par[u])) < 0) return;
        mrg(par[u], u);
    }
    ans = min(ans, num-1);
}

void dnc(int u)
{
    get_sz(u, -1);
    int c = get_cent(u, -1, sz[u]);

    solve(c);

    erased[c] = true;
    for(auto v : G[c]) {
        if(erased[v]) continue;
        dnc(v);
    }
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N >> K;
    for(int i = 1; i < N; i++) {
        int u, v; cin >> u >> v;
        G[u].push_back(v);
        G[v].push_back(u);
    }
    for(int i = 1; i <= N; i++) cin >> C[i];
    for(int i = 1; i <= N; i++) D[C[i]].push_back(i);
    dnc(1);
    cout << ans << "\n";
}