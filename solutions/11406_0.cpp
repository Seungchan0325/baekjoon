#include <bits/stdc++.h>

using namespace std;

const int INF = 987654321;
const int MAXN = 105;
const int MAXM = 105;
const int SIZE = 2*MAXN + 2*MAXM;

const int s = 0;
const int e = SIZE - 1;

bool inQ[SIZE];
int N, M, cost[SIZE][SIZE], dist[SIZE], f[SIZE][SIZE], c[SIZE][SIZE], par[SIZE];
vector<int> g[SIZE];

void AddEdge(int u, int v, int _cost, int cap)
{
    g[u].push_back(v);
    g[v].push_back(u);
    cost[u][v] += _cost;
    cost[v][u] -= _cost;
    c[u][v] += cap;
}

int main()
{
    cin >> N >> M;
    for(int i = 1; i <= N; i++) {
        AddEdge(s, 2*i, 0, INF);
        int Ai; cin >> Ai;
        AddEdge(2*i, 2*i+1, 0, Ai);
    }
    for(int i = 1; i <= M; i++) {
        AddEdge(2*i+1 + 2*MAXN, e, 0, INF);
        int Bi; cin >> Bi;
        AddEdge(2*i + 2*MAXN, 2*i+1 + 2*MAXN, 0, Bi);
    }

    for(int u = 1; u <= M; u++) {
        for(int v = 1; v <= N; v++) {
            int cap; cin >> cap;
            AddEdge(2*v+1, 2*u + 2*MAXN, 0, cap);
        }
    }

    int ans = 0, sum = 0;
    while(true) {
        memset(par, -1, sizeof(par));
        memset(inQ, 0, sizeof(inQ));
        fill_n(dist, sizeof(dist) / sizeof(int), INF);
        queue<int> q;
        q.push(s);
        dist[s] = 0;

        while(!q.empty()) {
            int now = q.front(); q.pop();
            inQ[now] = false;
            for(auto nxt : g[now]) {
                if(c[now][nxt] - f[now][nxt] > 0 && dist[now] + cost[now][nxt] < dist[nxt]) {
                    dist[nxt] = dist[now] + cost[now][nxt];
                    par[nxt] = now;
                    if(!inQ[nxt]) {
                        q.push(nxt);
                        inQ[nxt] = true;
                    }
                }
            }
        }

        if(par[e] == -1) break;

        int flow = INF;
        for(int i = e; i != s; i = par[i]) {
            flow = min(c[par[i]][i] - f[par[i]][i], flow);
        }

        for(int i = e; i != s; i = par[i]) {
            sum += flow * cost[par[i]][i];
            f[par[i]][i] += flow;
            f[i][par[i]] -= flow;
        }
        ans += flow;
    }
    cout << ans << "\n";
    // cout << sum << "\n";
}