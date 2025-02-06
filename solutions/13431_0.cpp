#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int MAXN = 101010;

bool erased[MAXN], chk[MAXN];
int N, Q, sz[MAXN], par[MAXN], cnt[MAXN];
ll s[MAXN];
vector<int> t[MAXN];
vector<pair<int, ll>> g[MAXN];
map<int, ll> dist[MAXN];
map<int, int> group[MAXN];
vector<int> cnts[MAXN];
vector<ll> ss[MAXN];

void get_sz(int u, int p)
{
    sz[u] = 1;
    for(auto v : t[u]) {
        if(v == p || erased[v]) continue;
        get_sz(v, u);
        sz[u] += sz[v];
    }
}

int get_cent(int n, int u, int p)
{
    for(auto v : t[u]) {
        if(v == p || erased[v]) continue;
        if(sz[v] > n/2) return get_cent(n, v, u);
    }
    return u;
}

void dfs(int u, int p, int idx, ll d, map<int, ll>& dist, map<int, int>& group)
{
    group[u] = idx;
    dist[u] = d;
    for(auto [v, w] : g[u]) {
        if(v == p || erased[v]) continue;
        dfs(v, u, idx, d + w, dist, group);
    }
}

void DnC(int u, int p)
{
    get_sz(u, -1);
    int c = get_cent(sz[u], u, -1);
    par[c] = p;
    int m = g[c].size();
    cnts[c].resize(m+1);
    ss[c].resize(m+1);
    group[c][c] = m;
    dist[c][c] = 0;
    for(int i = 0; i < m; i++) {
        auto [v, w] = g[c][i];
        if(erased[v]) continue;
        dfs(v, c, i, w, dist[c], group[c]);
    }
    erased[c] = true;
    for(auto v : t[c]) {
        if(erased[v]) continue;
        DnC(v, c);
    }
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N >> Q;
    for(int i = 1; i < N; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        t[u].push_back(v);
        t[v].push_back(u);
        g[u].emplace_back(v, w);
        g[v].emplace_back(u, w);
    }
    DnC(0, -1);
    for(int i = 1; i <= Q; i++) {
        int op, x;
        cin >> op >> x;
        if(op == 1) {
            if(chk[x]) continue;
            chk[x] = true;
            int u = x;
            while(u != -1) {
                s[u] += dist[u][x];
                ss[u][group[u][x]] += dist[u][x];
                cnt[u]++;
                cnts[u][group[u][x]]++;
                u = par[u];
            }
        } else {
            ll result = 0;
            int u = x;
            while(u != -1) {
                if(u == x) result += s[u] + cnt[u] * dist[u][x];
                else result += s[u] - ss[u][group[u][x]] + (cnt[u] - cnts[u][group[u][x]]) * dist[u][x];
                u = par[u];
            }
            cout << result << "\n";
        }
    }
}