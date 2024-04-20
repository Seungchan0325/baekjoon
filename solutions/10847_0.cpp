#include <bits/stdc++.h>

using namespace std;

const int MAXN = 30005;

int N, M, dp[MAXN], S, T;
vector<int> P[MAXN];

int main()
{
    cin >> N >> M;
    for(int i = 0; i < M; i++) {
        int Bi, Pi;
        cin >> Bi >> Pi;
        if(i == 0) S = Bi;
        if(i == 1) T = Bi;
        P[Bi].push_back(Pi);
    }

    for(int i = 0; i < N; i++) {
        sort(P[i].begin(), P[i].end());
        P[i].erase(unique(P[i].begin(), P[i].end()), P[i].end());
    }

    memset(dp, 0x7F, sizeof(dp));

    priority_queue<pair<int, int>> pq;
    dp[S] = 0;
    pq.emplace(0, S);

    while(!pq.empty()) {
        auto [dist, u] = pq.top(); pq.pop();
        dist = -dist;
        if(dp[u] < dist) continue;
        for(auto p : P[u]) {
            for(int i = 1; ; i++) {
                int v = u + p * i;
                if(v > N) break;

                if(dist + i < dp[v]) {
                    dp[v] = dist + i;
                    pq.emplace(-dp[v], v);
                }
                if(binary_search(P[v].begin(), P[v].end(), p)) break;
            }

            for(int i = 1; ; i++) {
                int v = u - p * i;
                if(v < 0) break;

                if(dist + i < dp[v]) {
                    dp[v] = dist + i;
                    pq.emplace(-dp[v], v);
                }
                if(binary_search(P[v].begin(), P[v].end(), p)) break;
            }
        }
    }

    if(dp[T] >= 0x7F000000) cout << -1;
    else cout << dp[T];
}