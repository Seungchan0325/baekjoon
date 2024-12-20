#include <bits/stdc++.h>

using namespace std;

const int MAXN = 10050;

int n, m, c[MAXN], D[MAXN];
vector<pair<int, int>> graph[MAXN];

int main()
{
    cin >> n >> m;
    for(int i = 1; i <= n; i++) cin >> c[i];
    for(int i = 0; i < m; i++) {
        int a, x, y;
        cin >> a >> x >> y;
        graph[x].emplace_back(a, y);
        graph[y].emplace_back(a, x);
    }

    priority_queue<pair<int, int>> pq;
    for(int i = 1; i <= n; i++) {
        D[i] = c[i];
        pq.emplace(-D[i], i);
    }

    while(!pq.empty()) {
        auto [d, x] = pq.top(); pq.pop();
        d = -d;

        if(d > D[x]) continue;

        for(auto [a, y] : graph[x]) {
            if(D[x] + D[y] < D[a]) {
                D[a] = D[x] + D[y];
                pq.emplace(-D[a], a);
            }
        }
    }

    cout << D[1];
}