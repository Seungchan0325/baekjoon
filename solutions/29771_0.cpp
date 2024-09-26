#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const ll INF = 1e18;
const ll MAXN = 500005;
const ll LOGN = 19;

ll N, Q, in[MAXN], D[MAXN], pv, sparse[MAXN][LOGN+1], dep[MAXN];
vector<ll> graph[MAXN], tree[MAXN];

void dfs(ll u, ll p)
{
    for(ll i = 1; i <= LOGN; i++) {
        sparse[u][i] = sparse[sparse[u][i-1]][i-1];
    }
    in[u] = ++pv;
    for(auto v : graph[u]) {
        if(v == p) continue;
        dep[v] = dep[u] + 1;
        sparse[v][0] = u;
        D[v] = D[u] + v - 1;
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

signed main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N;
    for(ll i = 2; i <= N; i++) {
        ll p, c; cin >> p >> c;
        graph[p+1].emplace_back(c+1);
    }

    dfs(1, -1);

    cin >> Q;
    while(Q--) {
        ll k;
        cin >> k;
        vector<ll> A(k);
        for(auto& i : A) { cin >> i; i++; }
        
        ll ansv = 0, anss = 0;

        sort(A.begin(), A.end(), [](ll a, ll b) { return in[a] < in[b]; });
        ll sz = A.size();
        for(ll i = 1; i < sz; i++) {
            A.push_back(lca(A[i-1], A[i]));
        }
        sort(A.begin(), A.end(), [](ll a, ll b) { return in[a] < in[b]; });
        A.erase(unique(A.begin(), A.end()), A.end());
        for(ll i = 1; i < A.size(); i++) {
            ll u = lca(A[i-1], A[i]);
            anss += D[A[i]] - D[u];
            ansv += dep[A[i]] - dep[u];
        }

        anss += A[0] - 1;
        ansv += 1;

        cout << ansv << " " << anss << "\n";
    }
}