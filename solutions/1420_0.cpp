#include <bits/stdc++.h>

using namespace std;

struct G {
    int N;
    vector<vector<int>> graph;
    vector<unordered_map<int, int>> c;
    G(int N) : N(N), graph(N+1), c(N+1) {}

    void add_edge(int u, int v, int cap)
    {
        graph[u].push_back(v);
        graph[v].push_back(u);
        c[u][v] = cap;
    }

    int mf(int s, int t)
    {
        int ret = 0;
        vector<unordered_map<int, int>> f(N+1);
        while(true) {
            vector<int> par(N+1, -1);
            queue<int> q;
            q.push(s);
            par[s] = -1;
            while(q.size()) {
                int u = q.front(); q.pop();
                for(auto v : graph[u]) {
                    if(par[v] == -1 && c[u][v] - f[u][v] > 0) {
                        q.push(v); par[v] = u;
                    }
                }
            }
            if(par[t] == -1) break;

            int flow = 1e9;
            for(int i = t; i != s; i = par[i]) {
                flow = min(c[par[i]][i] - f[par[i]][i], flow);
            }

            for(int i = t; i != s; i = par[i]) {
                f[par[i]][i] += flow;
                f[i][par[i]] -= flow;
            }
            ret += flow;
        }
        return ret;
    }
};

const int di[] = {0, 0, 1, -1};
const int dj[] = {1, -1, 0, 0};

int N, M, inV[105][105], outV[105][105];
char A[105][105];

int main()
{
    cin >> N >> M;
    int idx = 0;
    for(int i = 1; i <= N; i++) {
        for(int j = 1; j <= M; j++) {
            cin >> A[i][j];
            inV[i][j] = ++idx;
            outV[i][j] = ++idx;
        }
    }
    int s, t;
    G g(idx);
    for(int i = 1; i <= N; i++) {
        for(int j = 1; j <= M; j++) {
            if(A[i][j] == '#') continue;

            if(A[i][j] == 'K') {
                g.add_edge(inV[i][j], outV[i][j], 1e9);
                s = inV[i][j];
            }
            else if(A[i][j] == 'H') {
                g.add_edge(inV[i][j], outV[i][j], 1e9);
                t = outV[i][j];
            }
            else g.add_edge(inV[i][j], outV[i][j], 1);

            for(int k = 0; k < 4; k++) {
                int ni = i + di[k];
                int nj = j + dj[k];

                if(ni <= 0 || ni > N || nj <= 0 || nj > M || A[ni][nj] == '#') continue;
                g.add_edge(outV[i][j], inV[ni][nj], 1e9);
            }
        }
    }

    int ans = g.mf(s, t);
    if(ans >= 1e9) cout << "-1";
    else cout << ans;
}