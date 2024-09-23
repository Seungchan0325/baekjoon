#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const ll INF = 1e18;
const ll MAXN = 500005;
const ll LOGN = 19;

ll N, Q, in[MAXN], D[MAXN], pv, sparse[MAXN][LOGN+1], dep[MAXN], dp[MAXN][2], type[MAXN];
vector<pair<ll, ll>> graph[MAXN], tree[MAXN];

void dfs(ll u, ll p)
{
    for(ll i = 1; i <= LOGN; i++) {
        sparse[u][i] = sparse[sparse[u][i-1]][i-1];
    }
    in[u] = ++pv;
    for(auto [v, w] : graph[u]) {
        if(v == p) continue;
        dep[v] = dep[u] + 1;
        sparse[v][0] = u;
        D[v] = D[u] + w;
        dfs(v, u);
    }
}

ll lca(ll u, ll v)
{
    if(dep[u] < dep[v]) swap(u, v);
    ll diff = dep[u] - dep[v];
    for(ll i = 0; i <= LOGN; i++) {
        if(diff&(1<<i)) u = sparse[u][i];
    }

    if(u == v) return u;

    for(ll i = LOGN; i >= 0; i--) {
        if(sparse[u][i] != sparse[v][i]) {
            u = sparse[u][i];
            v = sparse[v][i];
        }
    }

    return sparse[u][0];
}

void dfs1(ll u)
{
    dp[u][0] = dp[u][1] = INF;
    for(auto [v, w] : tree[u]) {
        dfs1(v);
        dp[u][0] = min(dp[u][0], dp[v][0] + w);
        dp[u][1] = min(dp[u][1], dp[v][1] + w);
    }
    if(type[u]) dp[u][type[u]-1] = 0;
}

void dfs2(ll u, ll d0, ll d1)
{
    if(type[u]) dp[u][type[u]-1] = 0;
    dp[u][0] = min(dp[u][0], d0);
    dp[u][1] = min(dp[u][1], d1);
    for(auto [v, w] : tree[u]) {
        dfs2(v, d0 + 2, d1 + w);
    }
}

signed main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N >> Q;
    for(ll i = 1; i < N; i++) {
        ll u, v, w;
        cin >> u >> v >> w;
        u++; v++;
        graph[u].emplace_back(v, w);
        graph[v].emplace_back(u, w);
    }

    dfs(1, -1);

    while(Q--) {
        ll S, T;
        cin >> S >> T;
        vector<ll> X(S), Y(T), A;
        for(auto& i : X) { cin >> i; i++; A.push_back(i); type[i] = 1; }
        for(auto& i : Y) { cin >> i; i++; A.push_back(i); type[i] = 2; }
        
        sort(A.begin(), A.end(), [](ll a, ll b) { return in[a] < in[b]; });
        ll sz = A.size();
        for(ll i = 1; i < sz; i++) {
            A.push_back(lca(A[i-1], A[i]));
        }
        sort(A.begin(), A.end(), [](ll a, ll b) { return in[a] < in[b]; });
        A.erase(unique(A.begin(), A.end()), A.end());
        for(ll i = 1; i < A.size(); i++) {
            ll u = lca(A[i-1], A[i]);
            tree[u].emplace_back(A[i], D[A[i]] - D[u]);
        }

        dfs1(A[0]);
        dfs2(A[0], INF, INF);

        ll mn = INF;
        for(auto u : A) {
            mn = min(mn, dp[u][0] + dp[u][1]);
        }

        cout << mn << "\n";

        for(auto u : A) {
            dp[u][0] = dp[u][1] = 0;
            tree[u].clear();
            type[u] = 0;
        }
    }
}