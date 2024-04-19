#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const ll INF = 1e18;
const ll MAXN = 200005;

ll N, M, S, T, L, K, dpS[MAXN], dpT[MAXN];
vector<pair<ll, ll>> graph[MAXN];

void dijkstra(ll s, ll dp[])
{
    fill(dp, dp + N, INF);
    dp[s] = 0;
    priority_queue<pair<ll, ll>, vector<pair<ll, ll>>, greater<pair<ll, ll>>> pq;
    pq.emplace(0, s);
    while(!pq.empty()) {
        auto [dist, u] = pq.top(); pq.pop();
        if(dp[u] < dist) continue;
        for(auto [v, w] : graph[u]) {
            if(dist + w < dp[v]) {
                dp[v] = dist + w;
                pq.emplace(dp[v], v);
            }
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N >> M;
    cin >> S >> T >> L >> K;
    S--; T--;
    for(ll i = 0; i < M; i++) {
        ll u, v, w;
        cin >> u >> v >> w;
        u--; v--;
        graph[u].emplace_back(v, w);
        graph[v].emplace_back(u, w);
    }

    dijkstra(S, dpS);
    dijkstra(T, dpT);

    if(dpS[T] <= K) {
        cout << N*(N-1)/2;
        return 0;
    }

    sort(dpT, dpT + N);

    ll ans = 0;
    for(ll u = 0; u < N; u++) {
        ll cand = upper_bound(dpT, dpT+N, K - L - dpS[u]) - dpT;
        ans += cand;
    }
    cout << ans;
}