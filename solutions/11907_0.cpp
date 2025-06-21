#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int MAXN = 101010;

bool cottage[MAXN], erased[MAXN];
int n, m, sz[MAXN];
ll k;
vector<pair<int, int>> g[MAXN];
vector<int> cen[MAXN];
vector<vector<int>> sub[MAXN];

void get_sz(int u, int p)
{
    sz[u] = 1;
    for(auto [v, w] : g[u]) {
        if(v == p || erased[v]) continue;
        get_sz(v, u);
        sz[u] += sz[v];
    }
}

int get_cent(int u, int p, int m)
{
    for(auto [v, w] : g[u]) {
        if(v == p || erased[v]) continue;
        if(sz[v] > m) return get_cent(v, u, m);
    }
    return u;
}

void dfs(int u, int p, int d, vector<int>& m)
{
    if(cottage[u]) {
        m.push_back(d);
    }
    for(auto [v, w] : g[u]) {
        if(v == p || erased[v]) continue;
        dfs(v, u, d+w, m);
    }
}

void build(int u)
{
    get_sz(u, -1);
    int c = get_cent(u, -1, sz[u]/2);

    cen[c].reserve(sz[u]);
    dfs(c, -1, 0, cen[c]);
    sort(cen[c].begin(), cen[c].end());
    for(auto [v, w] : g[c]) {
        if(erased[v]) continue;
        vector<int> dist; dist.reserve(sz[v]);
        dfs(v, c, w, dist);
        sort(dist.begin(), dist.end());
        sub[c].push_back(dist);
    }

    erased[c] = true;
    for(auto [v, w] : g[c]) {
        if(erased[v]) continue;
        build(v);
    }
}

ll count(int k, const vector<int>& src, const vector<int>& dst)
{
    ll ans = 0;
    int idx = ssize(dst) - 1;
    for(auto i : src) {
        while(idx >= 0 && dst[idx] + i > k) {
            idx--;
        }
        ans += idx + 1;
    }
    return ans;
}

ll query(int k)
{
    ll ans = 0;
    for(int i = 1; i <= n; i++) {
        ans += count(k, cen[i], cen[i]);
        if(cottage[i]) ans--;
        for(auto& s : sub[i]) {
            ans -= count(k, s, s);
        }
    }
    return ans / 2;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> n >> m >> k;
    for(int i = 2; i <= n; i++) {
        int p, d; cin >> p >> d;
        g[i].emplace_back(p, d);
        g[p].emplace_back(i, d);
    }
    for(int i = 0; i < m; i++) {
        int u; cin >> u;
        cottage[u] = true;
    }

    build(1);

    int lo = 0;
    int hi = 1e8;
    while(lo + 1 < hi) {
        int mid = (lo + hi) / 2;
        if(query(mid) < k) lo = mid;
        else hi = mid;
    }
    cout << hi << "\n";
}