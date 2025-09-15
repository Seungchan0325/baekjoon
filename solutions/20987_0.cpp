#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const ll MAXN = 101010;
const ll MAXM = 202020;
const ll INF = 0x3f3f3f3f3f3f3f3f;

ll N, M, U[MAXM], V[MAXM], C[MAXM], P[MAXM], D[MAXN];
vector<pair<ll, ll>> g[MAXN];
unordered_map<ll, vector<pair<ll, ll>>> gg[MAXN];
unordered_map<ll, ll> cost[MAXN];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N >> M;
    for(ll i = 1; i <= M; i++) cin >> U[i] >> V[i] >> C[i] >> P[i];
    for(ll i = 1; i <= M; i++) cost[U[i]][C[i]] += P[i], cost[V[i]][C[i]] += P[i];
    for(ll i = 1; i <= M; i++) {
        g[U[i]].push_back({V[i], min(P[i], cost[U[i]][C[i]] - P[i])});
        g[V[i]].push_back({U[i], min(P[i], cost[V[i]][C[i]] - P[i])});
    }

    for(ll i = 1; i <= M; i++) gg[U[i]][C[i]].emplace_back(P[i], V[i]);
    for(ll i = 1; i <= M; i++) gg[V[i]][C[i]].emplace_back(P[i], U[i]);

    for(ll i = 1; i <= N; i++)
        for(auto& [c, v] : gg[i])
            sort(v.begin(), v.end(), greater<>());
    for(ll i = 1; i <= M; i++) {
        ll j = 0;
        while(j < gg[V[i]][C[i]].size() && gg[V[i]][C[i]][j].second == U[i]) j++;
        if(j < gg[V[i]][C[i]].size()) {
            ll W = gg[V[i]][C[i]][j].second;
            ll VP = gg[V[i]][C[i]][j].first;
            g[U[i]].push_back({W, cost[V[i]][C[i]] - VP});
        }
    }
    for(ll i = 1; i <= M; i++) {
        ll j = 0;
        while(j < gg[U[i]][C[i]].size() && gg[U[i]][C[i]][j].second == V[i]) j++;
        if(j < gg[U[i]][C[i]].size()) {
            ll W = gg[U[i]][C[i]][j].second;
            ll VP = gg[U[i]][C[i]][j].first;
            g[V[i]].push_back({W, cost[U[i]][C[i]] - VP});
        }
    }
    memset(D, 0x3f, sizeof(D));
    priority_queue<pair<ll, ll>> pq;
    D[1] = 0;
    pq.emplace(-D[1], 1);
    while(!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        d = -d;
        if(d > D[u]) continue;
        for(auto [v, w] : g[u]) {
            if(D[v] > D[u] + w) {
                D[v] = D[u] + w;
                pq.emplace(-D[v], v);
            }
        }
    }
    
    if(D[N] >= INF) cout << "-1\n";
    else cout << D[N];
}