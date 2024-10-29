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
        c[u][v] += cap;
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

int N;

int main()
{
    cin >> N;
    G g(256);
    for(int i = 1; i <= N; i++) {
        char u, v;
        int c;
        cin >> u >> v >> c;
        g.add_edge(u, v, c);
        g.add_edge(v, u, c);
    }

    cout << g.mf('A', 'Z');
}