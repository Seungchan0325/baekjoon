#include <bits/stdc++.h>

using namespace std;

const int INF = 987654321;
const int MAXN = 1005;
const int MAXM = 1005;
const int MAXK = 1005;

const int SIZE = MAXN + MAXM + MAXK;

const int s = 0;
const int e = SIZE - 1;

int N, M, K, flow[SIZE][SIZE], cap[SIZE][SIZE], par[SIZE];
vector<int> g[SIZE];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N >> M >> K;
    
    for(int i = 1; i <= K; i++) {
        int u = i + MAXN + MAXM;
        cap[s][u] = 1;
        g[s].push_back(u);
        g[u].push_back(s);
    }

    for(int i = 1; i <= N; i++) {
        cap[s][i] = 1;
        g[s].push_back(i);
        g[i].push_back(s);
        for(int j = 1; j <= K; j++) {
            int u = j + MAXN + MAXM;
            cap[u][i] = 1;
            g[u].push_back(i);
            g[i].push_back(u);
        }
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
        int u = i + MAXN;
        cap[u][e] = 1;
        g[u].push_back(e);
        g[e].push_back(u);
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