#include <bits/stdc++.h>

using namespace std;

const int INF = 987654321;
const int MAXN = 405;

const int s = 1;
const int e = 2;

int N, P, c[MAXN][MAXN], f[MAXN][MAXN], par[MAXN];
vector<int> g[MAXN];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N >> P;
    for(int i = 0; i < P; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
        c[u][v] = 1;
    }

    int ans = 0;
    while(true) {
        memset(par, -1, sizeof(par));
        queue<int> q;
        q.push(s);
        while(!q.empty()) {
            int now = q.front(); q.pop();
            for(auto nxt : g[now]) {
                if(par[nxt] != -1) continue;
                if(c[now][nxt] - f[now][nxt] > 0) {
                    par[nxt] = now;
                    q.push(nxt);
                }
            }
        }
        if(par[e] == -1) break;

        int flow = INF;
        for(int i = e; i != s; i = par[i]) {
            flow = min(c[par[i]][i] - f[par[i]][i], flow);
        }

        for(int i = e; i != s; i = par[i]) {
            f[par[i]][i] += flow;
            f[i][par[i]] -= flow;
        }
        ans += flow;
    }
    cout << ans;
}