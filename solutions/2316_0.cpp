#include <bits/stdc++.h>

using namespace std;

const int INF = 987654321;
const int MAXN = 405;
const int SIZE = 2*MAXN;

const int s = 1;
const int e = 2;

int N, P, par[SIZE], c[SIZE][SIZE], f[SIZE][SIZE];
vector<int> g[SIZE];

void addEdge(int u, int v, int cap)
{
    g[u].push_back(v);
    g[v].push_back(u);
    c[u][v] += cap;
}

int main()
{
    cin >> N >> P;
    addEdge(2*s, 2*s+1, INF);
    addEdge(2*e, 2*e+1, INF);
    for(int i = 3; i <= N; i++) {
        addEdge(2*i, 2*i+1, 1);
    }
    for(int i = 0; i < P; i++) {
        int u, v;
        cin >> u >> v;
        addEdge(2*u+1, 2*v, INF);
        addEdge(2*v+1, 2*u, INF);
    }

    int ans = 0;
    while(true) {
        memset(par, -1, sizeof(par));
        queue<int> q;
        q.push(2*s);
        while(!q.empty()) {
            int now = q.front(); q.pop();
            for(auto nxt : g[now]) {
                if(par[nxt] != -1) continue;
                if(c[now][nxt] - f[now][nxt] > 0) {
                    q.push(nxt);
                    par[nxt] = now;
                }
            }
        }
        if(par[2*e+1] == -1) break;

        int flow = INF;
        for(int i = 2*e+1; i != 2*s; i = par[i])
            flow = min(flow, c[par[i]][i] - f[par[i]][i]);
        
        for(int i = 2*e+1; i != 2*s; i = par[i]) {
            f[par[i]][i] += flow;
            f[i][par[i]] -= flow;
        }
        ans += flow;
    }
    cout << ans;
}