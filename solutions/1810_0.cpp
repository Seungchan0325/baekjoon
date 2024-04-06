#include <bits/stdc++.h>

using namespace std;

const int INF = 987654321;
const int MAXN = 50005;
const int MAXY = 1000005;

int N, F, X[MAXN], Y[MAXN];
vector<double> dist;
vector<pair<int, double>> g[MAXN];
set<pair<int, int>> p[MAXY];

int main()
{
    cin >> N >> F;
    dist.resize(N + 1, INFINITY);

    for(int i = 1; i <= N; i++) {
        cin >> X[i] >> Y[i];
        p[Y[i]].insert({X[i], i});
    }

    for(int i = 0; i <= N; i++) {
        for(int ny = Y[i]; ny <= Y[i] + 2; ny++) {
            auto it = p[ny].lower_bound({X[i] - 2, 0});
            while(it != p[ny].end() && it->first <= X[i] + 2) {
                if(it->second != i) {
                    int j = it->second;
                    double dist = sqrt((X[i] - X[j]) * (X[i] - X[j]) + (Y[i] - Y[j]) * (Y[i] - Y[j]));
                    g[i].emplace_back(j, dist);
                    g[j].emplace_back(i, dist);
                }
                it++;
            }
        }
    }

    priority_queue<pair<double, int>, vector<pair<double, int>>, greater<>> pq;
    pq.emplace(0, 0);
    dist[0] = 0;

    double ans = INFINITY;

    while(!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        for(auto [v, dv] : g[u]) {
            if(dist[v] > d + dv) {
                if(Y[v] == F) ans = min(ans, d + dv);
                pq.emplace(d + dv, v);
                dist[v] = d + dv;
            }
        }
    }

    if(ans >= INFINITY) {
        cout << -1;
    }
    else {
        cout << round(ans + 1e-6);
    }
}