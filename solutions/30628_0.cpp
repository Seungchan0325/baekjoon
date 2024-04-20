#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100005;

int N, M, K, dp[MAXN][12];
vector<pair<int, int>> graph[MAXN];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N >> M >> K;
    for(int i = 0; i < M; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        graph[u].emplace_back(v, w);
        graph[v].emplace_back(u, w);
    }

    memset(dp, 0x3F, sizeof(dp));
    dp[1][0] = 0;
    priority_queue<tuple<int, int, int>> pq;
    pq.emplace(0, 1, 0);
    while(!pq.empty()) {
        auto [dist, u, r] = pq.top(); pq.pop();
        dist = -dist;
        if(dp[u][r] < dist) continue;

        for(auto [v, w] : graph[u]) {
            int ndist = dist + w;
            int nr = (r + w) % 12;
            if(ndist < dp[v][nr]) {
                dp[v][nr] = ndist;
                pq.emplace(-ndist, v, nr);
            }
        }
    }

    if(dp[N][K%12] <= K) cout << "YES";
    else cout << "NO";
}