#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int MAXN = 200050;
const ll INF = 1e18;

ll N, M, K, s[MAXN], idx[MAXN], D[2][MAXN], nxt[MAXN];
vector<ll> p[MAXN];
vector<pair<ll, ll>> graph[MAXN];

int main()
{
    cin >> N >> M >> K;
    for(ll i = 0; i < M; i++) {
        ll u, v, w;
        cin >> u >> v >> w;
        graph[u].emplace_back(v, w);
    }

    memset(idx, -1, sizeof(idx));
    for(ll i = 0; i < K; i++) {
        cin >> s[i];
        for(ll j = 0; j < s[i]; j++) {
            ll pij;
            cin >> pij;
            if(j > 0) nxt[p[i].back()] = pij;
            p[i].push_back(pij);
            idx[pij] = i;
        }
    }

    for(int i = 0; i <= N; i++) {
        D[0][i] = D[1][i] = INF;
    }
    priority_queue<tuple<ll, ll, ll>> pq;
    if(idx[1] != -1 && p[idx[1]].front() == 1) {
        pq.emplace(0, 1, 1);
        D[1][1] = 0;
    } else {
        pq.emplace(0, 0, 1);
        D[0][1] = 0;
    }

    while(!pq.empty()) {
        auto [d, b, u] = pq.top(); pq.pop();
        d = -d;
        if(d > D[b][u]) continue;

        for(auto [v, w] : graph[u]) {
            if(b && v == nxt[u]) {
                if(p[idx[v]].back() == v) continue;
                if(d + w < D[1][v]) {
                    D[1][v] = d + w;
                    pq.emplace(-D[1][v], 1, v);
                }
            } else {
                if(idx[v] != -1 && p[idx[v]].front() == v) {
                    if(d + w < D[1][v]) {
                        D[1][v] = d + w;
                        pq.emplace(-D[1][v], 1, v);
                    }
                } else {
                    if(d + w < D[0][v]) {
                        D[0][v] = d + w;
                        pq.emplace(-D[0][v], 0, v);
                    }
                }
            }
        }
    }

    for(ll i = 1; i <= N; i++) {
        ll d = min(D[0][i], D[1][i]);
        if(d >= INF) cout << "-1 ";
        else cout << d << " ";
    }
}