#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int MAXN = 303030;

ll n, m, c[MAXN], p[MAXN], xz[MAXN];
vector<pair<int, ll>> g[MAXN];
priority_queue<ll> pq[MAXN];

void dfs(int u) {
    for(auto [v, w] : g[u]) {
        dfs(v);
        if(pq[v].empty()) {
            pq[v].push(w);
            pq[v].push(w);
        } else {
            ll optR = pq[v].top(); pq[v].pop();
            ll optL = pq[v].top(); pq[v].pop();
            pq[v].push(optL + w);
            pq[v].push(optR + w);
        }
        while(pq[u].size() < pq[v].size()) swap(pq[u], pq[v]);
        xz[u] += xz[v] + w;
        while(pq[v].size()) {
            pq[u].push(pq[v].top()); pq[v].pop();
        }
    }
    for(int i = 1; i < g[u].size(); i++) {
        pq[u].pop();
    }
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m;
    for(int i = 2; i <= n+m; i++) {
        cin >> p[i] >> c[i];
        g[p[i]].push_back({i, c[i]});
    }
    dfs(1); pq[1].pop();
    vector<ll> v;
    while(pq[1].size()) {
        v.push_back(pq[1].top()); pq[1].pop();
    }
    ll ans = xz[1];
    ll px = 0;
    for(int i = ssize(v)-1; i >= 0; i--) {
        ans -= (v[i]-px) * (i+1);
        px = v[i];
    }
    cout << ans << "\n";
}
