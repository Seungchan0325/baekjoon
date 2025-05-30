#include <bits/stdc++.h>

using namespace std;
using ll = long long;

const int MAXN = 250505;
const ll inf = 1e18;

int N, M, K;
ll cost[5*MAXN], dist[5*MAXN];
vector<int> g[5*MAXN];

struct SegTree {
    vector<int> seg[2*MAXN];

    void update(int l, int r, int x)
    {
        for(l+=N, r+=N; l <= r; l>>=1, r>>=1) {
            if(l&1) seg[l++].push_back(x);
            if(~r&1) seg[r--].push_back(x);
        }
    }
};

SegTree in, out;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    
    cin >> N >> M >> K; K--;
    for(int i = 0; i < M; i++) {
        int a, b, c, d, e;
        cin >> a >> b >> c >> d >> e;
        b--; c--; d--; e--;
        out.update(b, c, i);
        in.update(d, e, i);
        cost[4*N+i] = a;
    }
    for(int i = 2; i < 2*N; i++) {
        g[i].push_back(i/2);
        g[i/2+2*N].push_back(i+2*N);
    }
    for(int i = 1; i < 2*N; i++) {
        for(auto j : out.seg[i]) g[i].push_back(4*N+j);
        for(auto j : in.seg[i]) g[4*N+j].push_back(2*N+i);
    }
    for(int i = 0; i < N; i++) {
        g[i+3*N].push_back(i+N);
    }

    for(int i = 0; i < 4*N+M; i++) dist[i] = inf;
    priority_queue<pair<ll, int>> pq;
    dist[N+K] = 0;
    pq.emplace(-dist[N+K], N+K);
    while(!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        d = -d;
        if(d > dist[u]) continue;
        for(auto v : g[u]) {
            if(d + cost[v] < dist[v]) {
                dist[v] = d + cost[v];
                pq.emplace(-dist[v], v);
            }
        }
    }

    for(int i = 0; i < N; i++) {
        if(dist[N+i] >= inf) cout << "-1 ";
        else cout << dist[N+i] << " ";
    }
}