#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using pii = pair<ll, ll>;

const ll MAXN = 1005;
const ll MAXM = 2005;
const ll INF = 1e20;

bool visited[MAXN];
ll n, m, a, b, k, t[105][MAXM], dist[105][MAXN];
ll adj[MAXN][MAXN];

void dijkstra(int start) {
    memset(dist, 0x7F, sizeof(dist));

    priority_queue<pair<ll, pii>, vector<pair<ll, pii>>, greater<>> pq;
    dist[0][start] = 0;
    pq.push({0, {start, 0}});
    while(!pq.empty()) {
        ll ndist = pq.top().first;
        ll node = pq.top().second.first;
        ll litk = pq.top().second.second;
        pq.pop();

        if(dist[litk][node] < ndist) continue;      //최적화

        for(int next=1; next<=n; next++) {
            if(adj[node][next] == -1) continue;
            for(int i=litk; i<=k; i++) {
                ll next_dist = ndist + t[i][adj[node][next]];
                if(next_dist < dist[i][next]) {
                    dist[i][next] = next_dist;
                    pq.push({next_dist, {next, i}});
                }
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    memset(adj, 0xff, sizeof(adj));
    cin>>n>>m>>a>>b;
    for(int i=1; i<=m; i++) {
        ll u, v; cin>>u>>v>>t[0][i];
        adj[u][v] = i;
        adj[v][u] = i;
    }
    cin>>k;
    for(int i=1; i<=k; i++) {
        for(int j=1; j<=m; j++) {
            cin>>t[i][j];
        }
    }

    dijkstra(a);

    ll ans = INF;
    for(int i=0; i<=k; i++) {
        ans = min(dist[i][b], ans);
    }
    cout<<ans;
}