#include <bits/stdc++.h>

using namespace std;

const int INF = 987654321;
const int MAXN = 505;
const int MAXM = 10005;

int n, m, s, t, par[MAXN], c[MAXN][MAXN], f[MAXN][MAXN];
vector<int> g[MAXN];

int main()
{
    cin >> n >> m;
    for(int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        g[u].push_back(v);
        g[v].push_back(u);
        c[u][v] = w;
        c[v][u] = w;
    }
    cin >> s >> t;
    
    int ans = 0;
    while(true) {
        memset(par, -1, sizeof(par));
        queue<int> q;
        q.push(s);
        while(!q.empty()) {
            int u = q.front(); q.pop();
            for(auto v : g[u]) {
                if(par[v] == -1 && c[u][v] - f[u][v] > 0) {
                    q.push(v); par[v] = u;
                }

            }
        }
        if(par[t] == -1) break;

        int flow = INF;
        for(int i = t; i != s; i = par[i]) {
            flow = min(c[par[i]][i] - f[par[i]][i], flow);
        }

        for(int i = t; i != s; i = par[i]) {
            f[par[i]][i] += flow;
            f[i][par[i]] -= flow;
        }
        ans += flow;
    }
    cout << ans;
}