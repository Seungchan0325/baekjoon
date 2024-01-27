#include <bits/stdc++.h>

using namespace std;

const int INF = 987654321;
const int MAXN = 200005;

int dist[MAXN];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int n, k;
    cin >> n >> k;

    fill(dist, dist + MAXN, INF);
    dist[n] = 0;

    priority_queue<pair<int, int>> q;
    q.emplace(0, n);
    while(!q.empty()) {
        auto [cost, cur] = q.top(); q.pop();
        cost = -cost;

        if(2 * cur < MAXN && cost < dist[2 * cur]) q.emplace(-(dist[2 * cur] = cost), 2 * cur);
        if(0 <= cur - 1 && cost + 1 < dist[cur - 1]) q.emplace(-(dist[cur - 1] = (cost + 1)), cur - 1);
        if(cur + 1 < MAXN && cost + 1 < dist[cur + 1]) q.emplace(-(dist[cur + 1] = (cost + 1)), cur + 1);
    }

    cout << dist[k];
}