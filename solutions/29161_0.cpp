#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int MAXN = 202020;

bool erased[MAXN];
int N, M, sz[MAXN], ans[MAXN];
vector<int> t[MAXN];
vector<pair<int, ll>> qry[MAXN], g[MAXN];

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

void compute_xor(int u, int p, ll d, map<ll, int>& xors)
{
    xors[d] ^= u;
    for(auto [v, w] : g[u]) {
        if(v == p || erased[v]) continue;
        compute_xor(v, u, d + w, xors);
    }
}

void parse_query(int u, int p, ll d, vector<pair<int, ll>>& qs)
{
    for(auto [idx, di] : qry[u]) qs.emplace_back(idx, di - d);
    for(auto [v, w] : g[u]) {
        if(v == p || erased[v]) continue;
        parse_query(v, u, d + w, qs);
    }
}

void DnC(int u)
{
    get_sz(u, -1);
    int c = get_cent(sz[u], u, -1);

    int m = t[c].size();
    map<ll, int> xorall;
    xorall[0] ^= c;
    vector<map<ll, int>> xors(m);
    for(int i = 0; i < m; i++) {
        auto [v, w] = g[c][i];
        if(erased[v]) continue;
        compute_xor(v, c, w, xors[i]);
        compute_xor(v, c, w, xorall);
    }

    for(auto [idx, d] : qry[c]) {
        ans[idx] ^= xorall[d];
    }

    for(int i = 0; i < m; i++) {
        auto [v, w] = g[c][i];
        if(erased[v]) continue;

        vector<pair<int, ll>> qs;
        parse_query(v, c, w, qs);

        for(auto [idx, d] : qs) {
            ans[idx] ^= xorall[d] ^ xors[i][d];
        }
    }
    
    erased[c] = true;
    for(auto v : t[c]) {
        if(erased[v]) continue;
        DnC(v);
    }
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N >> M;
    for(int i = 1; i < N; i++) {
        int u, v;
        ll w;
        cin >> u >> v >> w;
        t[u].push_back(v);
        t[v].push_back(u);
        g[u].emplace_back(v, w);
        g[v].emplace_back(u, w);
    }
    for(int i = 1; i <= M; i++) {
        int x;
        ll d;
        cin >> x >> d;
        qry[x].emplace_back(i, d);
    }
    DnC(1);
    for(int i = 1; i <= M; i++) {
        cout << ans[i] << "\n";
    }
}