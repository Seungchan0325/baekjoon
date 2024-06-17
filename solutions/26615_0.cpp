#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const ll MAXN = 100005;
const ll LOGN = 17;
const ll MAXT = 100005;

ll N, M, T, K, psum[MAXT], DP[MAXN][LOGN+1], dep[MAXN];
vector<ll> graph[MAXN];

void dfs(ll u, ll p)
{
    for(ll i = 1; i <= LOGN; i++) {
        DP[u][i] = DP[DP[u][i-1]][i-1];
    }
    for(auto v : graph[u]) {
        if(v == p) continue;

        dep[v] = dep[u] + 1;
        DP[v][0] = u;
        dfs(v, u);
    }
}

ll LCA(ll u, ll v)
{
    if(dep[u] < dep[v]) swap(u, v);
    ll diff = dep[u] - dep[v];
    for(ll i = 0; i <= LOGN; i++) {
        if(diff & (1<<i)) {
            u = DP[u][i];
        }
    }

    if(u == v) return u;

    for(ll i = LOGN; i >= 0; i--) {
        if(DP[u][i] != DP[v][i]) {
            u = DP[u][i];
            v = DP[v][i];
        }
    }

    return DP[u][0];
}

int main()
{
    cin >> N >> M >> T;
    for(ll i = 0; i < N - 1; i++) {
        for(ll j = 0; j < M; j++) {
            ll x;
            cin >> x;
            if(x == 0) {
                ll u = M * i + j;
                ll v = M * (i + 1) + j;
                graph[u].push_back(v);
                graph[v].push_back(u);
            }
        }
    }

    for(ll i = 0; i < N; i++) {
        for(ll j = 0; j < M - 1; j++) {
            ll x;
            cin >> x;
            if(x == 0) {
                ll u = M * i + j;
                ll v = M * i + j + 1;
                graph[u].push_back(v);
                graph[v].push_back(u);
            }
        }
    }

    dfs(0, -1);

    cin >> K;
    for(ll i = 0; i < K; i++) {
        ll s, e, a, b, c, d, val;
        cin >> s >> e >> a >> b >> c >> d >> val;

        ll u = a * M + b;
        ll v = c * M + d;
        ll lca = LCA(u, v);
        ll len = dep[u] + dep[v] - 2*dep[lca] + 1;

        psum[s] += val * len;
        psum[e + 1] -= val * len;
    }

    for(ll i = 1; i <= T; i++) {
        psum[i] += psum[i-1];
        cout << psum[i] << "\n";
    }
}