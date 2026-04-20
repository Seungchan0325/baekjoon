#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int MAXN = 202020;

template<int SZ>
struct Fenwick {
    ll t[SZ+1];
    void upd(ll x, ll v)
    {
        while(x <= SZ) {
            t[x] += v;
            x += x & -x;
        }
    }
    ll qry(ll x)
    {
        ll ret = 0;
        while(x > 0) {
            ret += t[x];
            x -= x & -x;
        }
        return ret;
    }
};

ll N, T[MAXN], C[MAXN], R[MAXN], X[MAXN], ans[MAXN], D[MAXN], in[MAXN], out[MAXN], pv;
Fenwick<MAXN> f;
vector<pair<ll, ll>> g[MAXN];

void dfs(int u, int p)
{
    in[u] = ++pv;
    for(auto [v, w] : g[u]) {
        if(v == p) continue;
        D[v] = D[u] + w;
        dfs(v, u);
    }
    out[u] = pv;
}

void dnc(int l, int r, vector<int> v)
{
    if(l == r) {
        for(int i : v) ans[i] = l;
        return;
    }
    int m = (l+r)/2;
    vector<int> left, right, rv;
    for(auto i : v) {
        while(rv.size() && out[rv.back()] < in[i]) {
            int j = rv.back(); rv.pop_back();
            f.upd(R[j], -X[j]);
        }
        if(l <= T[i] && T[i] <= m) {
            f.upd(R[i], X[i]);
            rv.push_back(i);
            left.push_back(i);
            continue;
        }
        ll t = f.qry(MAXN) - f.qry(D[i]);
        if(t >= C[i]) {
            f.upd(R[i], X[i]);
            rv.push_back(i);
            left.push_back(i);
        } else {
            C[i] -= t;
            right.push_back(i);
        }
    }
    while(rv.size()) {
        int j = rv.back(); rv.pop_back();
        f.upd(R[j], -X[j]);
    }
    dnc(l, m, left);
    dnc(m+1, r, right);
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N;
    for(int i = 1; i < N; i++) {
        int u, v, w; cin >> u >> v >> w;
        g[u].push_back({v, w});
        g[v].push_back({u, w});
    }
    for(int i = 1; i <= N; i++) {
        int x; cin >> x;
        T[x] = i;
    }
    for(int i = 1; i <= N; i++) cin >> C[i] >> R[i] >> X[i];

    dfs(1, -1);

    vector<ll> ds;
    for(int i = 1; i <= N; i++) ds.push_back(D[i]);
    ds.push_back(1e18);
    sort(ds.begin(), ds.end());
    ds.erase(unique(ds.begin(), ds.end()), ds.end());
    for(int i = 1; i <= N; i++) {
        R[i] = upper_bound(ds.begin(), ds.end(), D[i]+R[i]) - ds.begin() + 1;
        D[i] = lower_bound(ds.begin(), ds.end(), D[i]) - ds.begin() + 1;
    }

    vector<int> v(N);
    iota(v.begin(), v.end(), 1);
    sort(v.begin(), v.end(), [](int i, int j) { return in[i] < in[j]; });
    dnc(1, N, v);
    for(int i = 1; i <= N; i++) cout << ans[i] << " ";
}
