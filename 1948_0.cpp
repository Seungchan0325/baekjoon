#include <bits/stdc++.h>

using namespace std;

using pii = pair<int, int>;

const int INF = 987654321;
const int MAXN = 10005;
const int MAXM = 100005;

struct Edge {
    int to;
    int time;

    bool operator<(const Edge& other) {
        return time > other.time;
    }
};

bool visited[MAXN];
int n, m, s, e, dist[MAXN];
vector<Edge> edges[MAXM], re_edges[MAXM];

int count_cases(int node) {
    visited[node] = true;

    int ret = 0;
    for(auto [next, time] : re_edges[node])
        if(dist[next] == dist[node] - time) {
            if(!visited[next]) ret += count_cases(next);
            ret += 1;
        }
    
    return ret;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin>>n;
    cin>>m;
    for(int i=0; i<m; i++) {
        int from, to, time; cin>>from>>to>>time;
        edges[from].push_back({to, time});
        re_edges[to].push_back({from, time});
    }
    cin>>s>>e;

    for(int i=1; i<=n; i++) dist[i] = -INF;

    priority_queue<pii> pq;
    pq.push({0, s});

    dist[s] = 0;
    while(!pq.empty()) {
        auto [time, node] = pq.top(); pq.pop();

        for(auto [next, ntime] : edges[node]) {
            if(dist[next] < time + ntime) {
                dist[next] = time + ntime;
                pq.push({time + ntime, next});
            }
        }
    }

    int cases = count_cases(e);
    cout<<dist[e]<<"\n";
    cout<<cases<<"\n";
}