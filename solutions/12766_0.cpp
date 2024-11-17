#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int MAXN = 5050;

int N, B, S, R;
ll D[MAXN], DP[MAXN][MAXN];
vector<pair<int, int>> graph[MAXN], rgraph[MAXN];

vector<int> dijkstra(int s, vector<pair<int, int>> graph[])
{
    vector<int> D(N+1, 1e9);
    priority_queue<pair<int, int>> pq;
    pq.emplace(D[s] = 0, s);
    while(!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        d = -d;
        if(D[u] < d) continue;
        for(auto [v, w] : graph[u]) {
            if(d + w < D[v]) {
                D[v] = d + w;
                pq.emplace(-D[v], v);
            }
        }
    }
    return D;
}

void DnC(int k, int s, int e, int optL, int optR)
{
    if(e < s) return;

    int m = (s + e) / 2;
    ll opt = 1e18;
    int optI = -1;
    for(int i = optL; i <= min(optR, m); i++) {
        ll cand = DP[k-1][i-1] + (m - i) * (D[m] - D[i-1]);
        if(cand < opt) {
            opt = cand;
            optI = i;
        }
    }

    DP[k][m] = opt;

    DnC(k, s, m-1, optL, optI);
    DnC(k, m+1, e, optI, optR);
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N >> B >> S >> R;
    for(int i = 1; i <= R; i++) {
        int u, v, l;
        cin >> u >> v >> l;
        graph[u].emplace_back(v, l);
        rgraph[v].emplace_back(u, l);
    }

    for(int i = 1; i <= N; i++) D[i] = 1e18;

    auto d1 = dijkstra(B+1, graph);
    auto d2 = dijkstra(B+1, rgraph);
    for(int i = 1; i <= N; i++) {
        D[i] = d1[i] + d2[i];
    }

    sort(D+1, D+B+1);
    for(int i = 1; i <= B; i++) {
        D[i] += D[i-1];
        DP[0][i] = 1e18;
    }

    for(int i = 1; i <= S; i++) {
        DnC(i, 1, B, 1, B);
    }

    cout << DP[S][B];
}