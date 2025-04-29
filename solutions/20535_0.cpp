#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const ll MAXN = 505050;
const ll LOGN = 20;

ll N, Q, P[MAXN], sparse[MAXN][LOGN+1], in[MAXN], dep[MAXN], pv;
ll dp[MAXN];
vector<ll> g[MAXN], t[MAXN];

void dfs(ll u)
{
    for(ll i = 1; i <= LOGN; i++)
        sparse[u][i] = sparse[sparse[u][i-1]][i-1];
    in[u] = ++pv;
    for(auto v : g[u]) {
        sparse[v][0] = u;
        dep[v] = dep[u] + 1;
        dfs(v);
    }
}

ll lca(ll u, ll v)
{
    if(dep[u] < dep[v]) swap(u, v);
    ll diff = dep[u] - dep[v];
    for(ll i = 0; i <= LOGN; i++)
        if(diff&(1<<i)) u = sparse[u][i];
    if(u == v) return u;
    for(ll i = LOGN; i >= 0; i--)
        if(sparse[u][i] != sparse[v][i]) {
            u = sparse[u][i];
            v = sparse[v][i];
        }
    return sparse[u][0];
}

ll solve(ll u)
{
    ll ans = 0;
    ll cnt = 0;
    for(auto v : t[u]) {
        ans += solve(v);
        cnt += dp[u] * dp[v];
        dp[u] += dp[v];
    }
    ans += dep[u] * cnt;
    return ans;
}

signed main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N >> Q;
    for(ll i = 2; i <= N; i++) {
        cin >> P[i];
        g[P[i]].push_back(i);
    }

    dfs(1);

    while(Q--) {
        ll k;
        cin >> k;
        vector<ll> v(k);
        for(auto& vi : v) {
            cin >> vi;
            dp[vi]++;
        }

        sort(v.begin(), v.end(), [](ll i, ll j){return in[i] < in[j];});
        ll sz = ssize(v);
        for(ll i = 1; i < sz; i++) {
            ll u = lca(v[i-1], v[i]);
            v.push_back(u);
        }
        sort(v.begin(), v.end(), [](ll i, ll j){return in[i] < in[j];});
        v.erase(unique(v.begin(), v.end()), v.end());
        for(ll i = 1; i < ssize(v); i++) {
            ll u = lca(v[i-1], v[i]);
            t[u].push_back(v[i]);
        }

        ll ans = solve(v[0]);
        cout << ans << "\n";

        for(auto vi : v) {
            t[vi].clear();
            dp[vi] = 0;
        }
    }
}