#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const ll MAXN = 303030;

struct SegTree {
    ll n;
    ll mod;
    vector<ll> tree;
    void init(ll _n, ll _mod = 1e9 + 7) {
        n = _n;
        mod = _mod;
        tree.resize(2*n, 0);
    }
    void update(ll x, ll v) {
        x += n; tree[x] += v;
        while(x >>= 1) tree[x] = (tree[x<<1] + tree[x<<1|1]) % mod;
    }
    ll query(ll l, ll r) {
        ll ret = 0;
        for(l+=n, r+=n; l <= r; l>>=1, r>>=1) {
            if(l&1) ret += tree[l++], ret %= mod;
            if(~r&1) ret += tree[r--], ret %= mod;
        }
        return ret;
    }
};

ll pw(ll x, ll n, ll mod)
{
    if(n == 0) return 1;
    if(n&1) return (long long)pw(x, n-1, mod) * x % mod;
    long long half = pw(x, n/2, mod);
    return half * half % mod;
}

ll n, m, a[MAXN], w[MAXN], in[MAXN], out[MAXN], sz[MAXN], pv;
vector<ll> g[MAXN];

void dfs(ll u)
{
    sz[u] = 1;
    in[u] = ++pv;
    for(auto v : g[u]) {
        dfs(v);
        sz[u] += sz[v];
    }
    out[u] = pv;
}

const ll mod = 1e9 + 7;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> n >> m;
    ll rt;
    for(ll i = 1; i <= n; i++) {
        ll p; cin >> p;
        if(p) g[p].push_back(i);
        else rt = i;
    }
    for(ll i = 1; i <= n; i++) cin >> a[i];
    for(ll i = 1; i <= n; i++) cin >> w[i];

    dfs(rt);

    vector<pair<ll, ll>> v;
    for(ll i = 1; i <= n; i++) {
        v.emplace_back(a[i], i);
    }
    sort(v.begin(), v.end());

    vector<pair<ll, ll>> q;
    for(ll i = 1; i <= n; i++) {
        q.emplace_back(a[i] + w[i], i);
    }
    sort(q.begin(), q.end());
    
    ll idx = 0;
    SegTree ans; ans.init(n+1);
    SegTree seg; seg.init(n+1);
    for(auto [au, u] : q) {
        while(idx < n && v[idx].first <= a[u] + w[u]) {
            seg.update(in[v[idx].second], 1);
            idx++;
        }
        long long k = seg.query(in[u], out[u]);
        long long s = sz[u];
        ans.update(in[u], k * pw(s, mod-2, mod) % mod);
    }
    for(auto i = 0; i < m; i++) {
        ll u; cin >> u;
        ll a = ans.query(in[u], out[u]);
        cout << a << "\n";
    }
}