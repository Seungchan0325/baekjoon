#include <bits/stdc++.h>

using namespace std;

using pii = pair<int, int>;

const int INF = 987654321;

int n, m, dist[1005], dp[1005];
vector<pii> adjlist[1005];

void dijkstra(int start) {
    for(int i=1; i<=n; i++) dist[i] = INF;
    dist[start] = 0;
    priority_queue<pii, vector<pii>, greater<pii>> pq;
    pq.push({start, 0});

    while(!pq.empty()) {
        int current = pq.top().first;
        int distance = pq.top().second;
        pq.pop();

        if(dist[current] < distance) continue;
        for(auto [next, cost] : adjlist[current]) {
            int next_distance = distance + cost;
            if(next_distance < dist[next]) {
                dist[next] = next_distance;
                pq.push({next, next_distance});
            }
        }
    }
}

int dfs(int node) {
    if(node == 2) return 1;

    int& ret = dp[node];
    if(ret != -1) return ret;

    ret = 0;
    for(auto [next, cost] : adjlist[node])
        if(dist[next] < dist[node])
            ret += dfs(next);
    return ret;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin>>n>>m;
    for(int i=0; i<m; i++) {
        int a, b, c; cin>>a>>b>>c;
        adjlist[a].push_back({b, c});
        adjlist[b].push_back({a, c});
    }

    dijkstra(2);

    memset(dp, -1, sizeof(dp));
    int result = dfs(1);

    cout<<result;
}