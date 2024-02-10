#include <bits/stdc++.h>

using namespace std;

const int INF = 987654321;
const int MAXN = 1005;
const int MAXM = 1005;

const int s = 0;
const int e = MAXN + MAXM - 1;

int N, M, flow[MAXN+MAXM][MAXN+MAXM], cap[MAXN+MAXM][MAXM+MAXM], par[MAXN+MAXM];
vector<int> g[MAXN+MAXM];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N >> M;
    for(int i = 1; i <= N; i++) {
        cap[s][i] = 1;
        g[s].push_back(i);
        g[i].push_back(s);
        int n; cin >> n;
        for(int j = 0; j < n; j++) {
            int job; cin >> job;
            job += MAXN;
            g[i].push_back(job);
            g[job].push_back(i);
            cap[i][job] = 1;
        }
    }

    for(int i = 1; i <= M; i++) {
        cap[i+MAXN][e] = 1;
        g[i+MAXN].push_back(e);
        g[e].push_back(i+MAXN);
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
                if(cap[now][nxt] - flow[now][nxt] > 0) {
                    par[nxt] = now;
                    q.push(nxt);
                }
            }
        }
        if(par[e] == -1) break;

        int cost = INF;
        for(int i = e; i != s; i = par[i]) {
            cost = min(cap[par[i]][i] - flow[par[i]][i], cost);
        }

        for(int i = e; i != s; i = par[i]) {
            flow[par[i]][i] += cost;
            flow[i][par[i]] -= cost;
        }
        ans += cost;
    }
    cout << ans;
}