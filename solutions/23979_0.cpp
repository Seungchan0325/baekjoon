#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const ll MAXN = 100005;
const ll INF = 987654321;
const ll LOGN = 17;

ll N, Q, dp[MAXN][LOGN+1], d[MAXN][LOGN+1], dep[MAXN];
pair<ll, ll> mx[MAXN][LOGN+1];
vector<pair<ll, ll>> graph[MAXN];

void dfs(ll u, ll p)
{
    for(ll i = 1; i <= LOGN; i++) {
        dp[u][i] = dp[dp[u][i-1]][i-1];
        d[u][i] = d[u][i-1] + d[dp[u][i-1]][i-1];
        mx[u][i] = max(mx[u][i-1], mx[dp[u][i-1]][i-1]);
    }

    for(auto [v, w] : graph[u]) {
        if(v == p) continue;
        dep[v] = dep[u] + 1;
        dp[v][0] = u;
        d[v][0] = w;
        mx[v][0] = {w, v};
        dfs(v, u);
    }
}

ll LCA(ll u, ll v)
{
    if(dep[u] < dep[v]) swap(u, v);

    ll diff = dep[u] - dep[v];
    for(ll i = 0; i <= LOGN; i++) {
        if(diff & (1<<i)) {
            u = dp[u][i];
        }
    }

    if(u != v) {
        for(ll i = LOGN; i >= 0; i--) {
            if(dp[u][i] != dp[v][i]) {
                u = dp[u][i];
                v = dp[v][i];
            }
        }
        u = dp[u][0];
        v = dp[v][0];
    }
    return u;
}

// 거리, mx간선 밑 노드
pair<ll, ll> path(ll u, ll v)
{
    if(dep[u] < dep[v]) swap(u, v);
    ll w = 0;
    pair<ll, ll> mxv = {-INF, 0};
    ll diff = dep[u] - dep[v];
    for(ll i = 0; i <= LOGN; i++) {
        if(diff & (1<<i)) {
            w += d[u][i];
            mxv = max(mxv, mx[u][i]);
            u = dp[u][i];
        }
    }

    if(u != v) {
        for(ll i = LOGN; i >= 0; i--) {
            if(dp[u][i] != dp[v][i]) {
                w += d[u][i];
                w += d[v][i];
                mxv = max(mxv, mx[u][i]);
                mxv = max(mxv, mx[v][i]);
                u = dp[u][i];
                v = dp[v][i];
            }
        }
        w += d[u][0];
        w += d[v][0];
        mxv = max({mxv, mx[u][0], mx[v][0]});
    }

    return {w, mxv.second};
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N >> Q;
    for(ll i = 1; i < N; i++) {
        ll u, v, w;
        cin >> u >> v >> w;
        graph[u].emplace_back(v, w);
        graph[v].emplace_back(u, w);
    }

    dfs(1, -1);

    while(Q--) {
        ll u, v, w, a, b;
        cin >> u >> v >> w >> a >> b;

        if(dep[u] < dep[v]) swap(u, v);
        if(dep[a] < dep[b]) swap(a, b);

        ll s;
        ll mxv = path(u, v).second;
        if(dp[u][0] == v) {
            s = path(a, b).first;
            if(((LCA(u, a) == u) ^ (LCA(u, b) == u))) {
                s -= d[u][0];
                s += w;
            }
        } else if(!((LCA(mxv, a) == mxv) ^ (LCA(mxv, b) == mxv))) {
            s = path(a, b).first;
        } else {
            if(LCA(mxv, u) != mxv) swap(u, v);
            if(LCA(mxv, a) != mxv) swap(a, b);
            s = path(a, u).first + path(b, v).first + w;
        }

        cout << s << "\n";
    }
}