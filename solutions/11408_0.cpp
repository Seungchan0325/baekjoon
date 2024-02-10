#include <bits/stdc++.h>

using namespace std;

const int INF = 987654321;
const int MAXN = 405;
const int MAXM = 405;
const int SIZE = MAXN + MAXM;

const int s = 0;
const int e = MAXN + MAXM - 1;

bool inQ[SIZE];
int N, M, cost[SIZE][SIZE], dist[SIZE], f[SIZE][SIZE], c[SIZE][SIZE], par[SIZE];
vector<int> g[SIZE];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N >> M;
    for(int i = 1; i <= N; i++) {
        c[s][i] = 1;
        g[s].push_back(i);
        g[i].push_back(s);
        int n; cin >> n;
        for(int j = 0; j < n; j++) {
            int job; cin >> job;
            int pay; cin >> pay;
            job += MAXN;
            g[i].push_back(job);
            g[job].push_back(i);
            c[i][job] = 1;
            cost[i][job] = pay;
            cost[job][i] = -pay;
        }
    }

    for(int i = 1; i <= M; i++) {
        c[i+MAXN][e] = 1;
        g[i+MAXN].push_back(e);
        g[e].push_back(i+MAXN);
    }

    int ans = 0, sum = 0;
    while(true) {
        memset(par, -1, sizeof(par));
        memset(dist, 0x7F, sizeof(dist));
        memset(inQ, 0, sizeof(inQ));
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
    cout << sum << "\n";
}