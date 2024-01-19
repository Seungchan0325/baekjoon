#include <bits/stdc++.h>

using namespace std;

const long long INF = 1e18;
const long long MAXN = 105;

bool visited[MAXN];
long long n, m, dist[MAXN];
vector<long long> path[MAXN], graph[MAXN];
vector<tuple<long long, long long, long long>> edges;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> n >> m;
    for(long long i = 0; i < m; i++) {
        long long u, v, w;
        cin >> u >> v >> w;
        graph[v].emplace_back(u);
        edges.emplace_back(u, v, w);
    }

    queue<long long> q;
    q.push(n);
    while(!q.empty()) {
        long long cur = q.front();
        q.pop();
        visited[cur] = true;
        for(auto prev : graph[cur]) {
            if(visited[prev]) continue;
            q.push(prev);
        }
    }

    if(visited[1] == false) goto NOT_FOUND;

    fill(dist, dist + MAXN, -INF);
    dist[1] = 0;
    path[1].push_back(1);
    for(long long i = 0; i <= n; i++) {
        for(auto [from, to, cost] : edges) {
            if(-INF < dist[from] && dist[to] < dist[from] + cost) {
                dist[to] = dist[from] + cost;
                path[to] = path[from];
                path[to].push_back(to);
                if(i == n && visited[to]) goto NOT_FOUND;
            }
        }
    }

    for(auto i : path[n]) {
        cout << i << " ";
    }
    return 0;
NOT_FOUND:
    cout << "-1";
}