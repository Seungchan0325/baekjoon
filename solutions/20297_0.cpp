#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const ll INF = 1e18;
const ll MAXN = 101010;
const ll LOGN = 20;

ll N, in[MAXN], pv, sparse[MAXN][LOGN+1], dep[MAXN], type[MAXN];
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

ll dfs0(ll u, ll& ans)
{
    ll mn1 = INF;
    ll mn2 = INF;
    for(auto [v, w] : tree[u]) {
        ll a = dfs0(v, ans) + w;
        if(a < mn1) {
            mn2 = mn1; mn1 = a;
        }
        else if(a < mn2) mn2 = a;
        ans = min(ans, mn1 + mn2);
    }
    if(type[u]) {
        ans = min(ans, mn1);
        mn1 = 0;
    }
    return mn1;
}

signed main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N;
    map<ll, vector<ll>> q;
    for(ll i = 1; i <= N; i++) {
        ll c; cin >> c;
        q[c].push_back(i);
    }
    for(ll i = 1; i < N; i++) {
        ll u, v, w = 1;
        cin >> u >> v;
        graph[u].emplace_back(v, w);
        graph[v].emplace_back(u, w);
    }

    dfs(1, -1);

    ll ans = INF;
    for(auto [k, A] : q) {
        for(auto i : A) type[i] = 1;
        sort(A.begin(), A.end(), [](ll a, ll b) { return in[a] < in[b]; });
        ll sz = A.size();
        for(ll i = 1; i < sz; i++) {
            A.push_back(lca(A[i-1], A[i]));
        }
        sort(A.begin(), A.end(), [](ll a, ll b) { return in[a] < in[b]; });
        A.erase(unique(A.begin(), A.end()), A.end());
        for(ll i = 1; i < A.size(); i++) {
            ll u = lca(A[i-1], A[i]);
            tree[u].emplace_back(A[i], dep[A[i]] - dep[u]);
        }

        dfs0(A[0], ans);

        for(auto i : A) {
            type[i] = 0;
            tree[i].clear();
        }
    }
    cout << ans << "\n";
}