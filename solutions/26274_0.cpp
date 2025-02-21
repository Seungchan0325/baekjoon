#include <bits/stdc++.h>

using namespace std;

using ll = long long;

#define int ll

const int MAXN = 101010;
const int LOGN = 20;

bool sinsa[MAXN], erased[MAXN];
int N, K, Q, par[MAXN], sz[MAXN], dep[MAXN], group[MAXN][LOGN], dist[MAXN][LOGN], mycent[MAXN][LOGN];
vector<int> g[MAXN];
vector<ll> d[MAXN];
vector<int> c[MAXN];
vector<vector<ll>> ds[MAXN];
vector<vector<int>> cs[MAXN];

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

void dfs(int u, int p, int cent, int cent_dep, int group_id, int depth, vector<ll>& d, vector<int>& c)
{
    while((int)d.size()-1 < depth) d.push_back(0);
    while((int)c.size()-1 < depth) c.push_back(0);

    mycent[u][cent_dep] = cent;
    group[u][cent_dep] = group_id;
    dist[u][cent_dep] = depth;

    if(sinsa[u]) {
        d[depth] += depth;
        c[depth] += 1;
    }

    for(auto v : g[u]) {
        if(v == p || erased[v]) continue;
        dfs(v, u, cent, cent_dep, group_id, depth + 1, d, c);
    }
}

void DnC(int now, int p)
{
    get_sz(now, -1);
    int u = get_cent(sz[now], now, -1);
    par[u] = p;
    dep[u] = dep[p] + 1;

    group[u][dep[u]] = g[u].size();
    mycent[u][dep[u]] = u;

    d[u].push_back(0);
    c[u].push_back(0);

    if(sinsa[u]) {
        c[u][0]++;
    }

    ds[u].resize(g[u].size()+1);
    cs[u].resize(g[u].size()+1);

    ds[u][g[u].size()].push_back(0);
    cs[u][g[u].size()].push_back(0);

    for(int i = 0; i < g[u].size(); i++) {
        int v = g[u][i];
        if(erased[v]) continue;
        
        dfs(v, u, u, dep[u], i, 1, ds[u][i], cs[u][i]);
        while((int)d[u].size() < (int)ds[u][i].size()) d[u].push_back(0);
        while((int)c[u].size() < (int)cs[u][i].size()) c[u].push_back(0);

        for(int j = 1; j < ds[u][i].size(); j++) {
            d[u][j] += ds[u][i][j];
            c[u][j] += cs[u][i][j];
            ds[u][i][j] += ds[u][i][j-1];
            cs[u][i][j] += cs[u][i][j-1];
        }
    }

    for(int i = 1; i < d[u].size(); i++) {
        d[u][i] += d[u][i-1];
        c[u][i] += c[u][i-1];
    }
    
    erased[u] = true;
    for(auto v : g[u]) {
        if(erased[v]) continue;
        DnC(v, u);
    }
}

int nearst_sinsa(int A)
{
    int ret = 1e9;
    int u = A;
    while(u != 0) {
        int lo = -1;
        int hi = d[u].size();
        int id = group[A][dep[u]];
        while(lo + 1 < hi) {
            int mid = (lo + hi) / 2;
            int d = min(mid, (int)ds[u][id].size()-1);
            if(c[u][mid] - cs[u][id][d] > 0) hi = mid;
            else lo = mid;
        }
        if(hi != d[u].size()) ret = min(ret, hi + dist[A][dep[u]]);
        u = par[u];
    }
    return ret;
}

int get_distance(int A, int B)
{
    int u = A;
    while(u != 0) {
        if(mycent[A][dep[u]] == mycent[B][dep[u]]) {
            return dist[A][dep[u]] + dist[B][dep[u]];
        }
        u = par[u];
    }
    assert(0);
}

pair<ll, int> sinsa_query(int A, int limit)
{
    ll dsum = 0;
    int csum = 0;
    int u = A;
    while(u != 0) {
        int l = min(limit - dist[A][dep[u]], (int)d[u].size()-1);
        if(l >= 0) {
            dsum += d[u][l] + (ll)dist[A][dep[u]] * c[u][l];
            csum += c[u][l];
            
            int id = group[A][dep[u]];
            l = min(l, (int)ds[u][id].size()-1);
            dsum -= ds[u][id][l] + (ll)dist[A][dep[u]] * cs[u][id][l];
            csum -= cs[u][id][l];
        }
        
        u = par[u];
    }
    return {dsum, csum};
}

signed main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N >> K >> Q;
    for(int i = 1; i < N; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    for(int i = 1; i <= K; i++) {
        int u;
        cin >> u;
        sinsa[u] = true;
    }

    DnC(1, 0);

    while(Q--) {
        int A, B;
        cin >> A >> B;

        double lo = 0;
        double hi = N;
        for(int iter = 0; iter < 50; iter++) {
            double mid = (lo + hi) / 2;
            auto [dsum, csum] = sinsa_query(B, mid + 1e-9);
            if(K + dsum - csum * mid <= 0) hi = mid;
            else lo = mid;
        }

        double result = min((double)get_distance(A, B), nearst_sinsa(A) + lo);
        cout << setprecision(10) << fixed << result << "\n";
    }
}