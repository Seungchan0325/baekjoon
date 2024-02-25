#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const ll MAXN = 200005;

ll N, C, Q, t = 0, D[MAXN], S[MAXN], E[MAXN], tree[4*MAXN];
vector<ll> g[MAXN];

void dfs(ll u, ll p, ll d)
{
    S[u] = ++t;
    D[u] = d;
    for(auto v : g[u]) {
        if(v != p) dfs(v, u, d + 1);
    }
    E[u] = t;
}

void update(ll pos, ll delta, ll s = 1, ll e = N, ll idx = 1)
{
    if(e < pos || pos < s) return;

    if(s == e) {
        tree[idx] += delta;
        return;
    }

    ll m = (s + e) / 2;
    update(pos, delta, s, m, 2*idx);
    update(pos, delta, m+1, e, 2*idx+1);
    tree[idx] = tree[2*idx] + tree[2*idx+1];
}

ll query(ll l, ll r, ll s = 1, ll e = N, ll idx = 1)
{
    if(e < l || r < s) return 0;
    if(l <= s && e <= r) return tree[idx];
    ll m = (s + e) / 2;
    return query(l, r, s, m, 2*idx) + query(l, r, m+1, e, 2*idx+1);
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N >> C;
    for(ll i = 1; i < N; i++) {
        ll u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dfs(C, -1, 1);

    cin >> Q;
    while(Q--) {
        ll type, A;
        cin >> type >> A;
        if(type == 1) {
            update(S[A], 1);
        } else {
            ll result = D[A] * query(S[A], E[A]);
            cout << result << "\n";
        }
    }
}